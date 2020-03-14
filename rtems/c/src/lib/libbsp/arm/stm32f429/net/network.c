#include <string.h>

#include <rtems.h>
#include <rtems/rtems_bsdnet.h>
#include <rtems/status-checks.h>
#include <rtems/rtems_mii_ioctl.h>
#include <rtems/bspIo.h>
#include <rtems/malloc.h>

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/sockio.h>
#include <sys/mbuf.h>

#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>

#include <bsp/irq.h>
#include <bsp/rcc.h>
#include <bsp/stm32f4_eth.h>
#include <bsp/stm32f4.h>


#define NET_DEBUG


typedef enum {
	ETH_STATE_NOT_INITIALIZED,
	ETH_STATE_UP,
	ETH_STATE_DOWN
}eth_state;

typedef struct {
	stm32f4_rcc_index mac;
	stm32f4_rcc_index tx;
	stm32f4_rcc_index rx;
}eth_clock;

/*
 * Ethernet driver strructrue
 */
typedef struct {
	struct arpcom  arpcom;
	struct rtems_mdio_info mdio;
	int anlpar;

	rtems_id	tx_thread;
	rtems_id	rx_thread;
	rtems_id	i_thread;
	int	 txbuf_nums;
	int  rxbuf_nums;
	volatile stm32f4_eth_desc *tx_desc;
	volatile stm32f4_eth_desc *rx_desc;
	struct mbuf **rx_mbuf;
	struct mbuf **tx_mbuf;
	int  tx_index;
	void *buf_area;

#ifdef NET_DEBUG
	volatile stm32f4_eth *reg;
#endif
	int  vector;
	eth_clock clock;
	eth_state  status;

/* Statistics infomation for ethernet */	
	uint32_t	rx_frames;
	uint32_t	tx_frames;
	uint32_t	rx_bytes;
	uint32_t	tx_bytes;
	uint32_t	rx_interrupts;
	uint32_t	tx_interrupts;
	uint32_t	err_tx_interrupts;

	uint32_t	tx_descriptor_invalid;
	uint32_t	err_crc;
	uint32_t	err_receive;
	uint32_t	err_overflow;
	uint32_t	err_late_collision;
	uint32_t	err_watchdog_timeout;

	int phy;
}eth_driver_control;


/* */
#ifdef NET_DEBUG
#define net_print  printk
#else
#define net_print(...)
#endif


#define WATCHDOG_TIMEOUT  10

/* */
#define ETH_TX_BUF_COUNT  10
#define ETH_RX_BUF_COUNT  15

/* Ethernet event */
#define ETH_EVENT_TX_START      RTEMS_EVENT_0
#define ETH_EVENT_TX_STOP       RTEMS_EVENT_1
#define ETH_EVENT_TX_INTERRUPT  RTEMS_EVENT_2
#define ETH_EVENT_TX_INIT       RTEMS_EVENT_3

#define ETH_EVENT_RX_START      RTEMS_EVENT_5
#define ETH_EVENT_RX_STOP       RTEMS_EVENT_6
#define ETH_EVENT_RX_INTERRUPT  RTEMS_EVENT_7
#define ETH_EVENT_RX_INIT       RTEMS_EVENT_8

#define ETH_EVENT_TX \
	ETH_EVENT_TX_START |\
	ETH_EVENT_TX_STOP | \
	ETH_EVENT_TX_INTERRUPT | \
	ETH_EVENT_TX_INIT 

#define ETH_EVENT_RX \
	ETH_EVENT_RX_START | \
	ETH_EVENT_RX_STOP | \
	ETH_EVENT_RX_INTERRUPT | \
	ETH_EVENT_RX_INIT



/* 
 *  Ethernet error code
 */
#define  ETH_ERR_NO_MBUF   1
static eth_driver_control _Bsp_eth_Controller;


static void eth_software_reset(void)
{
	STM32F4_ETH->dma_bmr |= 0x1;
	while (STM32F4_ETH->dma_bmr & 0x1)
		;
}

static void eth_clock_set(eth_driver_control *softc, bool en)
{
	eth_clock *clk = &softc->clock;
	
	stm32f4_rcc_set_clock(clk->mac, en);
	stm32f4_rcc_set_clock(clk->tx, en);
	stm32f4_rcc_set_clock(clk->rx, en);
}

static int mdio_busy_wait(void)
{
	int sec = rtems_clock_get_ticks_per_second();
	int ticks = 0;

	while (ETH_MII_BUSY() && ticks++ < sec) 
		rtems_task_wake_after(1);

	return (ticks >= sec)? -1: 0;
}

static int eth_mdio_read(int phy, void *arg, unsigned reg, uint32_t *val)
{
	int eno = 0;
    (void)arg;
	
	if (phy >= 0 && phy <= 31) {
		int treg = STM32F4_ETH->mac_miiar;
		
		treg &= ~STM32F4_ETH_MACMIIAR_CR_MASK;
		treg |= STM32F4_ETH_MACMIIAR_PHY(phy) | STM32F4_ETH_MACMIIAR_REG(reg);
		treg = (treg & ~STM32F4_ETH_MACMIIAR_MW) | STM32F4_ETH_MACMIIAR_MB;
		STM32F4_ETH->mac_miiar = treg;
		
		eno = mdio_busy_wait();
		if (eno != 0)
			return eno;
		
		*val = STM32F4_ETH->mac_miidr;
	}else {
		eno = EINVAL;
	}
	
	return eno;
}

static int eth_mdio_write(int phy, void *arg, unsigned reg, uint32_t val)
{
    int eno = 0;
	(void)arg;
	
	if (phy >= 0 && phy <= 31) {
		int treg = STM32F4_ETH->mac_miiar;
		
		treg &= ~STM32F4_ETH_MACMIIAR_CR_MASK;
		treg |= STM32F4_ETH_MACMIIAR_PHY(phy) | STM32F4_ETH_MACMIIAR_REG(reg);
		treg |= STM32F4_ETH_MACMIIAR_MW | STM32F4_ETH_MACMIIAR_MB;

		STM32F4_ETH->mac_miidr = val & 0xffff;
		STM32F4_ETH->mac_miiar = treg;
		
		eno = mdio_busy_wait();
		if (eno != 0)
			return eno;
	}else {
		eno = EINVAL;
	}

	return eno;
}

static int eth_txdesc_init(volatile stm32f4_eth_desc *desc, int count)
{
  int index;

  if (desc == NULL)
  	  return -1;

  for (index = 0 ; index < count; index++) {
  	  desc[index].status = STM32F4_ETH_DMATX_TCH;
	  desc[index].buf = NULL;
	  if (index == count - 1)
		 desc[index].bufnext = (uint32_t)&desc[0];
	  else
		 desc[index].bufnext = (uint32_t)&desc[index+1];
  }
  
  STM32F4_ETH->dma_tdlar = (volatile uint32_t)desc;
  	
  return 0;
}

static int eth_rxdesc_init(volatile stm32f4_eth_desc *desc, int count)
{
  int index;

  if (desc == NULL) 
  	  return -1;
  
  for (index = 0 ; index < count; index++) {
  	   desc[index].bsize = STM32F4_ETH_DMARX_RCH;
	   desc[index].buf = NULL;
	   if (index == count - 1)
	   	  desc[index].bufnext = (uint32_t)&desc[0];
	   else
	   	  desc[index].bufnext = (uint32_t)&desc[index+1];
  }
  
  STM32F4_ETH->dma_rdlar = (volatile uint32_t)desc;
  	
  return 0;
}

static int eth_inc_index(int index, int max)
{
   if (index < max)
   	   index++;
   else
   	   index = 0;
   return index;
}

static void eth_enable_irqtx(void)
{
	rtems_interrupt_level level;
	
	rtems_interrupt_disable(level);
	STM32F4_ETH->dma_ier |= (STM32F4_ETH_DMA_IT_T | STM32F4_ETH_DMA_IT_NIS);
	rtems_interrupt_enable(level);
}

static void eth_disable_irqtx(void)
{
	rtems_interrupt_level level;
	
	rtems_interrupt_disable(level);
	STM32F4_ETH->dma_ier &= ~(STM32F4_ETH_DMA_IT_T | STM32F4_ETH_DMA_IT_NIS);
	rtems_interrupt_enable(level);
}

static void eth_enable_irqrx(void)
{
	rtems_interrupt_level level;
	
	rtems_interrupt_disable(level);
	STM32F4_ETH->dma_ier |= (STM32F4_ETH_DMA_IT_R | STM32F4_ETH_DMA_IT_NIS);
	rtems_interrupt_enable(level);
}

static void eth_disable_irqrx(void)
{
	rtems_interrupt_level level;
	
	rtems_interrupt_disable(level);
	STM32F4_ETH->dma_ier &= ~(STM32F4_ETH_DMA_IT_R | STM32F4_ETH_DMA_IT_NIS);
	rtems_interrupt_enable(level);
}

static rtems_status_code eth_request_completed(
		   eth_driver_control *softc
)
{
	return rtems_event_transient_send(softc->i_thread);
}

static rtems_status_code eth_request(
		   eth_driver_control *softc,
		   rtems_id	thread,
		   rtems_event_set event
)
{
	rtems_status_code sc = RTEMS_SUCCESSFUL;
	uint32_t nest = 0;

	softc->i_thread = rtems_task_self();
	sc = rtems_bsdnet_event_send(thread, event);
	if (sc !=  RTEMS_SUCCESSFUL)
		goto out;
	
	nest = rtems_bsdnet_semaphore_release_recursive();
	rtems_event_transient_receive(RTEMS_WAIT, RTEMS_NO_TIMEOUT);
	rtems_bsdnet_semaphore_obtain_recursive(nest);
	softc->i_thread = 0;
out:	
	return sc;
}

static struct mbuf *eth_new_mbuf(struct ifnet *ifp, bool wait)
{
   struct mbuf *m = NULL;
   int mw = wait? M_WAIT: M_DONTWAIT;

   MGETHDR(m, mw, MT_DATA);
   if (m != NULL) {
  	   MCLGET(m, mw);
	   if (m->m_flags & M_EXT) {
	   	   m->m_pkthdr.rcvif = ifp;
		   m->m_data = mtod(m, char *) + 2;
	   }else {
	       m_free(m);
		   m = NULL;
	   }
   }
   return m;
}

static struct mbuf *eth_next_fragment(struct ifnet *ifp, struct mbuf *m, uint32_t *ctrl)
{
   struct mbuf *n;

   *ctrl = STM32F4_ETH_DMATX_IC | STM32F4_ETH_DMATX_TCH;
   while (true) {
   	   if (m == NULL) {
   		  IF_DEQUEUE(&ifp->if_snd, m);
   		  if (m == NULL)
   			 return m;

   		*ctrl |= STM32F4_ETH_DMATX_FS;
   	   }

	   if (m->m_len > 0) {
		  break;
	   }else {
		  m_free(m);
	   }
   }
   
   n = m->m_next;
   while (n != NULL && n->m_len <= 0)
   		 n = m_free(n);
   m->m_next = n;
   if (n == NULL)
   	  *ctrl |= STM32F4_ETH_DMATX_LS;
out:
	return m;
}

static bool eth_add_new_mbuf(
				struct ifnet *ifp, 
				volatile stm32f4_eth_desc *desc, 
				struct mbuf **mtbl,
				int index, 
				bool wait
)
{
	struct mbuf *m = NULL;
	
	m = eth_new_mbuf(ifp, wait);
	mtbl[index] = m;
	
	if (m != NULL) {
		desc[index].status = STM32F4_ETH_DMARX_OWN;
		desc[index].bsize = STM32F4_ETH_DMARX_RCH | m->m_len;
		desc[index].buf = mtod(m, uint32_t);
		return true;
	}
	
	return false;
}

#if 0
static int eth_rxset_mbuf(eth_driver_control *softc, bool wait)
{
    struct ifnet *ifp = (struct ifnet *)softc;
	struct mbuf *m;
	struct mbuf **mtbl;
	int  product = 0;
	int  consume = 0;
	bool  ok = false;

    mtbl = softc->rx_mbuf;
	for ( ; product < softc->rxbuf_nums; product++) {
		 if (mtbl[product] != NULL)
		 	 mtbl[consume++] = mtbl[product];
	}
	for ( ; consume < softc->rxbuf_nums; consume++) {
		ok = eth_add_new_mbuf(ifp, softc->rx_desc, mtbl, consume, wait);
		if (!ok)
			return ETH_ERR_NO_MBUF;	
	}
	
    return 0;
}
#endif


static void eth_irq(void *arg)
{
	eth_driver_control *softc = arg;
	uint32_t  intr = STM32F4_ETH->dma_sr;
	uint32_t  imk = STM32F4_ETH->dma_ier;
	rtems_event_set te = 0, re = 0;
	uint32_t ie = 0;
	
	/* Normal interrupt */
	if (intr & STM32F4_ETH_DMASR_NIS) {
		if (intr & STM32F4_ETH_DMASR_RS) {
			ie |= STM32F4_ETH_DMASR_RS;
			++softc->rx_interrupts;
			re |= ETH_EVENT_RX_INTERRUPT;
		}
		if (intr & STM32F4_ETH_DMASR_TS) {
			ie |= STM32F4_ETH_DMASR_TS;
			++softc->tx_interrupts;
			te |= ETH_EVENT_TX_INTERRUPT;
		}
		ie |= STM32F4_ETH_DMASR_NIS;
	}

	/* Abnormal interrupt */
	if (intr & STM32F4_ETH_DMASR_AIS) {
		++softc->err_tx_interrupts;
		if (STM32F4_ETH_DMASR_TPSS) {
			ie |= STM32F4_ETH_DMASR_TPSS;
			te |= ETH_EVENT_TX_INIT;
		}
		if (intr & STM32F4_ETH_DMASR_RPSS) {
			ie |= STM32F4_ETH_DMASR_RPSS;
			re |= ETH_EVENT_RX_INIT;
		}
		ie |= STM32F4_ETH_DMASR_AIS;
	}
	
	/* Event processs */
	if (re != 0)
		rtems_bsdnet_event_send(softc->rx_thread, re);
	if (te != 0)
		rtems_bsdnet_event_send(softc->tx_thread, te);

    /* Update interrupt */
	STM32F4_ETH->dma_ier = (imk & ~ie) | \
						    STM32F4_ETH_DMASR_AIS |  \
						    STM32F4_ETH_DMASR_TPSS | \
						    STM32F4_ETH_DMASR_RPSS | \
						    STM32F4_ETH_DMA_IT_NIS;
	STM32F4_ETH->dma_sr = ie;
	
	net_print("Ethernet interrupt status: %x\r\n", intr);
}

static void net_rx_thread(void *arg)
{
	eth_driver_control *softc = arg;
	volatile stm32f4_eth_desc *desc = softc->rx_desc;
	struct ifnet *ifp = &softc->arpcom.ac_if;
	rtems_status_code sc;
	rtems_event_set event_out;
	uint32_t status;
	int	 list_counter;
	int  frame_len;
	int	 i_frame = 0;
	int  hdr_index;
	

    net_print("Enter in %s\r\n", __func__);
	
	for ( ; ; ) {
		/* Wait for events */
		sc = rtems_bsdnet_event_receive(
			ETH_EVENT_RX,
			RTEMS_EVENT_ANY | RTEMS_WAIT,
			RTEMS_NO_TIMEOUT,
			&event_out
		);
		RTEMS_CHECK_SC(sc, "Ethernet receive event -- net_rx_thread\r\n");
		net_print("Receive thread wake up events: %d\r\n", event_out);

		/* If need to be initialized */
		if ((event_out & ETH_EVENT_RX_INIT) != 0) {
			eth_disable_irqrx();

			/* Disable DMA receiver */
			ETH_DMA_RECEIVE_STOP();

			int i = 0;
			for (list_counter = 0; list_counter < softc->rxbuf_nums; list_counter++) {
				if (softc->rx_mbuf[list_counter] != NULL && list_counter != i)
					softc->rx_mbuf[i++] = softc->rx_mbuf[list_counter];
			}
				
			for ( ; i < softc->rxbuf_nums; i++)
				eth_add_new_mbuf(ifp, desc, softc->rx_mbuf, i, false);

			/* Enable interrupt and start it */
			ETH_DMA_RECEIVE_START();
			eth_enable_irqrx();

			eth_request_completed(softc);
			continue;
		}
		if ((event_out & ETH_EVENT_TX_STOP) != 0) {
			eth_request_completed(softc);
			continue;
		}

		/* */
		list_counter = 0;
		status = desc[list_counter].status;
		while (true) {
			//STM32F4_ETH->dma_sr = STM32F4_ETH_DMASR_RS;
			status = desc[list_counter].status;
			if (list_counter >= softc->rxbuf_nums || status & STM32F4_ETH_DMARX_OWN) {
				eth_enable_irqrx();
				break;
			}
			if (!(status & STM32F4_ETH_DMARX_ES)) {
				if (status & STM32F4_ETH_DMARX_FS) {
					hdr_index = list_counter;
					i_frame++;
				}
				
				if (status & STM32F4_ETH_DMARX_LS) {
					if (i_frame == 1) {
						i_frame--;
						goto recv_proc;
					}else {
						net_print("Receive descriptor error\r\n");
					}
				}
				continue;

		  recv_proc:
				struct mbuf *m = softc->rx_mbuf[list_counter];
				if (eth_add_new_mbuf(ifp, desc, softc->rx_mbuf, list_counter, false)) {
					struct ether_header *eh = mtod(m, struct ether_header*);
					frame_len = ETH_RX_FRAME_LEN(desc[list_counter]);
					frame_len -= (ETHER_HDR_LEN + ETHER_CRC_LEN);

					m->m_len = frame_len;
					m->m_pkthdr.len = frame_len;
					m->m_data = mtod(m, char *) + ETHER_HDR_LEN;
					ether_input(ifp, eh, m);

					softc->rx_frames++;
					net_print("Received frame: %d\r\n", list_counter);
				}
			}else {
				if (status & STM32F4_ETH_DMARX_CE)
					++softc->err_crc;
				if (status & STM32F4_ETH_DMARX_RE)
					++softc->err_receive;
				if (status & STM32F4_ETH_DMARX_LC)
					++softc->err_late_collision;
				if (status & STM32F4_ETH_DMARX_RWT)
					++softc->err_watchdog_timeout;
				if (status & STM32F4_ETH_DMARX_OE)
					++softc->err_overflow;
				net_print("Receive frame error: %d\r\n", list_counter);
			}
			
			list_counter = eth_inc_index(list_counter, softc->rxbuf_nums);
		}
		
	}
}

static void net_tx_thread(void *arg)
{
	eth_driver_control *softc = arg;
	struct ifnet *ifp = &softc->arpcom.ac_if;
	volatile stm32f4_eth_desc *desc;
	rtems_status_code sc;
	rtems_event_set event_out;
	struct mbuf *m = NULL;
	uint32_t  count;
	uint32_t  cst;
	
	for ( ; ; ) {
		sc = rtems_bsdnet_event_receive(
			ETH_EVENT_TX,
			RTEMS_EVENT_ANY | RTEMS_WAIT,
			RTEMS_NO_TIMEOUT,
			&event_out
		);
		RTEMS_CHECK_SC(sc, "Ethernet receive event -- net_tx_thread\r\n");
		net_print("Tansmit thread wake up event: %d\r\n", __func__);

		/* If it need to be initialized */
		if ((event_out & ETH_EVENT_TX_INIT) != 0) {
			eth_disable_irqtx();

			/* Disable DMA receiver */
			ETH_DMA_TRANSMIT_STOP();

			/* Flush FIFO */
			ETH_FIFO_FLUSH();

			for (count = 0; count < softc->txbuf_nums; count++) {
				struct mbuf *vm = softc->tx_mbuf[count];
				if (vm != NULL) {
					m_free(vm);
					softc->tx_mbuf[count] = NULL;
				}
			}

			/* Enable interrupt and start it */
			ETH_DMA_TRANSMIT_START();

			eth_request_completed(softc);			
			continue;
		}
		if ((event_out & ETH_EVENT_TX_STOP) != 0) {
			eth_request_completed(softc);
			break;
		}

		/* Release mbuf that had been used */
		net_print("Free transmit mbuf\r\n");
		for (count = 0; count < softc->txbuf_nums; count++) {
			struct mbuf *victim = softc->tx_mbuf[count];
			if (victim != NULL) {
				m_free(victim);
				softc->tx_mbuf[count] = NULL;
			}
		}

		/* Send packet */
		count = 0;
		while (true) {
			cst = 0;
			
			/* Get next mbuf */
			m = eth_next_fragment(ifp, m, &cst);
			
			if (m == NULL || count == softc->txbuf_nums - 1) {
				if (m == NULL && count == 0) {
					ifp->if_flags &= ~IFF_OACTIVE;
					break;
				}
					
				if (count > 0) {
					/* Enable transmit interrupt */
					eth_enable_irqtx();

					net_print("Start send data packet, cout = %d\r\n", count);
					
					/* Transmit buffer unavailable  */
					if (STM32F4_ETH->dma_sr & STM32F4_ETH_DMASR_TBUS) {
						/* Clear interrupt flag */
						STM32F4_ETH->dma_sr = STM32F4_ETH_DMASR_TBUS;

						/* Start DMA */
						STM32F4_ETH->dma_tpdr = 0; 
					}
					break;
				}

			}

			/* Check desriptor is valid */
			desc = &softc->tx_desc[count];
			if (!(desc->status & STM32F4_ETH_DMATX_OWN)) {
			/* Set transmit descriptor */
				net_print("Fill transmit descriptor\r\n");
				desc->status = cst | STM32F4_ETH_DMATX_OWN;
				desc->bsize = m->m_len & STM32F4_ETH_DMATX_BUF1_SIZE_MASK;
				desc->buf = mtod(m, uint32_t);	
				softc->tx_mbuf[count] = m;				
			}else {
				++softc->tx_descriptor_invalid;
				net_print("Transmit descriptor is invalid %d\r\n", softc->tx_descriptor_invalid);
			}

			m = m->m_next;
			count++; //count = eth_inc_index(count, softc->txbuf_nums);
		}
	}
}

static int eth_phy_get_id(int phy, uint32_t *id)
{
	uint32_t  id1 = 0;
	int eno = eth_mdio_read(phy, NULL, MII_PHYIDR1, &id1);
	if (eno == 0) {
		uint32_t id2 = eth_mdio_read(phy, NULL, MII_PHYIDR2, &id2);
		if (eno == 0) {
			*id = (id1 << 16) | id2;
		}
	}

	return eno;
}

static int eth_phy_down(int phy)
{
	return eth_mdio_write(phy, NULL, MII_BMCR, BMCR_PDOWN); 
}

static int eth_phy_up(int phy)
{
	int eno = 0;
	uint32_t status = 0;
	
	eno = eth_mdio_write(phy, NULL, MII_BMCR, BMCR_AUTOEN);
	if (eno == 0) {
		eno = eth_mdio_read(phy, NULL, MII_BMSR, &status);
		if (eno != 0 || !(status & BMSR_ACOMP))
			goto err;
	}else {
		goto err;
	}

	eno = eth_mdio_read(phy, NULL, PHY_SR, &status);
	if (eno == 0) {
		if (status & PHY_DUPLEX_STATUS)
			STM32F4_ETH->mac_cr |= STM32F4_ETH_MACCR_FULLDUPLEX;
		else
			STM32F4_ETH->mac_cr &= ~STM32F4_ETH_MACCR_HALFDUPLEX;
		
		if (status & PHY_SPEED_STATUS)
			STM32F4_ETH->mac_cr &= ~STM32F4_ETH_MACCR_SPEED_100M;
		else
			STM32F4_ETH->mac_cr |= STM32F4_ETH_MACCR_SPEED_100M;
	}else {
		goto err;
	}

#if 0
	/* Enable output interrupt events to signal via the INT pin */
	eno = eth_mdio_read(phy, NULL, PHY_MICR, &status);
	if (eno == 0) {
		status |= (PHY_MICR_INT_OE | PHY_MICR_INT_EN);
		eno = eth_mdio_write(phy, NULL, PHY_MICR, status);
		if (eno != 0)
			goto out;
	}

	/* Enable Interrupt on change of link status */
	eno = eth_mdio_read(phy, NULL, PHY_MISR, &status);
	if (eno == 0) {
		status |= PHY_MISR_LINK_INT_EN;
		eno = eth_mdio_write(phy, NULL, PHY_MISR, status);
		if (eno != 0)
			goto out;
	}
#endif

	/* Active the LED */
	eno = eth_mdio_read(phy, NULL, 0x19, &status);
	if (eno == 0) {
		status |= (1 << 5);
		eno = eth_mdio_write(phy, NULL, 0x19, status);
	}

err:
	return eno;
}

static int eth_up_or_down(eth_driver_control *softc, bool up)
{
	struct ifnet *ifp = &softc->arpcom.ac_if;
	uint32_t treg;
	int eno = 0;
	uint32_t chip = 0;
	
	if (up && softc->status == ETH_STATE_DOWN) {
		int hclk = STM32F4_HCLK;
		//uint32_t status = 0;
		
		/* Enable MAC clock */
		eth_clock_set(softc, true);

		/* Reset */
		eth_software_reset();
		
		/* Set MII clock */
		treg = STM32F4_ETH->mac_miiar & STM32F4_ETH_MACMIIAR_CR_MASK;
		if (hclk > 20000000 && hclk < 35000000)
			treg |= STM32F4_ETH_MACMIIAR_CR_Div16;
		else if (hclk > 35000000 && hclk < 60000000)
			treg |= STM32F4_ETH_MACMIIAR_CR_Div26;
		else if (hclk > 60000000 && hclk < 100000000)
			treg |= STM32F4_ETH_MACMIIAR_CR_Div42;
		else if (hclk > 100000000 && hclk < 150000000)
			treg |= STM32F4_ETH_MACMIIAR_CR_Div62;
		else
			treg |= STM32F4_ETH_MACMIIAR_CR_Div102;
		STM32F4_ETH->mac_miiar = treg;

		/* Reset PHY */
		eno = eth_mdio_write(softc->phy, NULL, MII_BMCR, BMCR_RESET);
		if (eno != 0)
			goto out;
#if  0
		if (eno == 0) {
			eno = eth_mdio_read(softc->phy, NULL, MII_BMSR, &status);
			if (eno != 0 || !(status & BMSR_LINK))
				goto out;
		}else {
			goto out;
		}
#endif
		/* */
		eno = eth_phy_get_id(softc->phy, &chip);
		if (eno != 0)
			goto out;
		printk("Netcard chip id: %x\r\n", chip);
		
		/* PHY up */
		treg = STM32F4_ETH->mac_cr & STM32F4_ETH_MACCR_CLEAR_MASK;
		eno = eth_phy_up(softc->phy);
		if (eno != 0)
			goto out;

		/* MAC Configure */
		STM32F4_ETH->mac_cr = treg | (1u << 13); /* Received own disable */
		STM32F4_ETH->mac_ffr = (1u << 2) | (1u << 6); 	
		STM32F4_ETH->mac_hthr = 0x0;
		STM32F4_ETH->mac_htlr = 0x0;
		STM32F4_ETH->mac_fcr = (1u << 7);      /* Zero-quanta pause disable */
		STM32F4_ETH->mac_vlantr = 0x0;
				 
		/* DMA Configure */
		STM32F4_ETH->dma_omr = (1u << 26) | (1u << 25) | (1u << 21);
		STM32F4_ETH->dma_bmr = (1u << 25) | (32u << 17) | (1u << 16) | (32 << 8);
		STM32F4_ETH->dma_ier |= (STM32F4_ETH_DMA_IT_AIS | STM32F4_ETH_DMA_IT_RPS);

		/* Set MAC address */
		uint8_t *madr = softc->arpcom.ac_enaddr;
		STM32F4_ETH->mac_a0hr = ((uint16_t)madr[5] << 8)  | \
								((uint16_t)madr[4] << 0);
		STM32F4_ETH->mac_a0lr = ((uint32_t)madr[3] << 24) | \
								((uint32_t)madr[2] << 16) | \
								((uint32_t)madr[1] << 8)  | \
								((uint32_t)madr[0] << 0);

		/* DMA Descriptor */
		eth_rxdesc_init(softc->rx_desc, softc->rxbuf_nums);
		eth_txdesc_init(softc->tx_desc, softc->txbuf_nums);
		
		/* Enable MAC Tx/Rx */
		ETH_MAC_TRANSMIT_ENABLE();
		ETH_MAC_RECEIVE_ENABLE();
		
		/* */
		rtems_status_code sc;
		sc = eth_request(softc, softc->tx_thread, ETH_EVENT_TX_INIT);
		if (sc != RTEMS_SUCCESSFUL)
			goto out;
		
		sc = eth_request(softc, softc->rx_thread, ETH_EVENT_RX_INIT);
		if (sc != RTEMS_SUCCESSFUL)
			goto out;

		/* Install ethernet interrupt */
		sc = rtems_interrupt_handler_install(
							softc->vector,
							"Ethernet",
							RTEMS_INTERRUPT_UNIQUE,
							eth_irq,
							softc
		);
		if (sc != RTEMS_SUCCESSFUL)
			goto out;

		/* Start watchdog timer */
		ifp->if_timer = 1;
		
		softc->status = ETH_STATE_UP;
	}
	
	else if (!up && softc->status == ETH_STATE_UP) {
		/* Remove ethernet interrupt handler */
		rtems_interrupt_handler_remove(
					softc->vector, 
					eth_irq,
					softc
		);

		eth_request(softc, softc->tx_thread, ETH_EVENT_TX_STOP);
		eth_request(softc, softc->rx_thread, ETH_EVENT_RX_STOP);

		eth_phy_down(softc->phy);
		eth_software_reset();
		eth_clock_set(softc, false);

		softc->status = ETH_STATE_DOWN;
	}

out:
	return eno;
}

static void eth_show(eth_driver_control *softc)
{
	int eno = EIO;
	int media = 0;
	
	if (softc->status == ETH_STATE_UP) {
		media = IFM_MAKEWORD(0, 0, 0, 0);
		eno = rtems_mii_ioctl(&softc->mdio, softc, SIOCGIFMEDIA, &media);
	}

	rtems_bsdnet_semaphore_release();
	if (eno == 0) {
		rtems_ifmedia2str(media, NULL, 0);
		printf("\n");
	}
	
	printf("Received frames: %u\r\n", softc->rx_frames);
	printf("Transimted frames: %u\r\n", softc->tx_frames);
	printf("Received bytes: %u\r\n", softc->rx_bytes);
	printf("Transimted bytes: %u\r\n", softc->tx_bytes);
	printf("Received interrupts: %u\r\n", softc->rx_interrupts);
	printf("Transimted interrupts: %u\r\n", softc->tx_interrupts);
	printf("Transmited error interrupts: %u\r\n", softc->err_tx_interrupts);
	printf("Transmit descriptor invalid: %u\r\n", softc->tx_descriptor_invalid);
	printf("CRC error: %u\r\n", softc->err_crc);
	printf("Receive error: %u\r\n", softc->err_receive);
	printf("Overflow error: %u\r\n", softc->err_overflow);
	printf("Late  collision error: %u\r\n", softc->err_late_collision);
	printf("Watchdog timeout error: %u\r\n", softc->err_watchdog_timeout);

	rtems_bsdnet_semaphore_obtain();
}

static void eth_watchdog(struct ifnet *ifp)
{
	eth_driver_control *softc = ifp->if_softc;
	int eno;
	uint32_t anlpar;

	if (softc->status == ETH_STATE_UP) {
		eno = eth_mdio_read(softc->phy, NULL, MII_ANLPAR, &anlpar);
		if (eno != 0)
			return;
			
		if (softc->anlpar != anlpar) {
			bool full_duplex = false;
			bool speed = false;

			if ((anlpar & ANLPAR_TX_FD) != 0) {
				full_duplex = true;
				speed = true;
			} else if ((anlpar & ANLPAR_T4) != 0) {
				speed = true;
			} else if ((anlpar & ANLPAR_TX) != 0) {
				speed = true;
			} else if ((anlpar & ANLPAR_10_FD) != 0) {
				full_duplex = true;
			}

			if (full_duplex)
				STM32F4_ETH->mac_cr |= STM32F4_ETH_MACCR_FULLDUPLEX;
			else
				STM32F4_ETH->mac_cr &= ~STM32F4_ETH_MACCR_FULLDUPLEX;
			if (speed)	
				STM32F4_ETH->mac_cr |= STM32F4_ETH_MACCR_SPEED_100M;
			else
				STM32F4_ETH->mac_cr &= ~STM32F4_ETH_MACCR_SPEED_100M;
			
			softc->anlpar = anlpar;
		}
	}

	ifp->if_timer = WATCHDOG_TIMEOUT;
}

static int eth_multicast_control(struct arpcom *ac, struct ifreq *ifr, bool add)
{
	int eno = 0;

	if (add)
		eno = ether_addmulti(ifr, ac);
	else
		eno = ether_delmulti(ifr, ac);

	if (eno == ENETRESET) {
		struct ether_multistep step;
		struct ether_multi *enm;

		STM32F4_ETH->mac_hthr = 0;
		STM32F4_ETH->mac_htlr = 0;
		
		ETHER_FIRST_MULTI(step, ac, enm);
		while (enm != NULL) {
			 uint64_t addrlo = 0;
			 uint64_t addrhi = 0;

			 memcpy(&addrlo, enm->enm_addrlo, ETHER_ADDR_LEN);
			 memcpy(&addrhi, enm->enm_addrhi, ETHER_ADDR_LEN);
			 while (addrlo <= addrhi) {
			 	  uint32_t crc = ether_crc32_be((uint8_t *)&addrlo, ETHER_ADDR_LEN);
				  uint32_t index = (crc >> 23) & 0x3f;

				  if (index < 32)
				  	 STM32F4_ETH->mac_htlr = 1u << index;
				  else
				  	 STM32F4_ETH->mac_hthr = 1u << (index - 32);
				  
				  addrlo++;
			 }

			 ETHER_NEXT_MULTI(step, enm);
		}

	}

	return eno;
}

static void eth_init(void *arg)
{

}

static void eth_start(struct ifnet *ifp)
{
	eth_driver_control *softc = ifp->if_softc;

	ifp->if_flags |= IFF_OACTIVE;
	if (softc->status == ETH_STATE_UP) {
		rtems_bsdnet_event_send(softc->tx_thread, ETH_EVENT_TX_START);
		net_print("Start ethernet\r\n");
	}
}

static int eth_ioctl(struct ifnet *ifp, ioctl_command_t cmd, caddr_t data)
{
	eth_driver_control *softc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	int eno = 0;

	net_print("Enter in %s\r\n", __func__);
	switch(cmd) {
		case SIOCGIFMEDIA:
		case SIOCSIFMEDIA:
			rtems_mii_ioctl(&softc->mdio, softc, cmd, &ifr->ifr_media);
			break;
		case SIOCGIFADDR:
		case SIOCSIFADDR:
			ether_ioctl(ifp, cmd, data);
			break;
		case SIOCSIFFLAGS:
			eno = eth_up_or_down(softc, (ifp->if_flags & IFF_UP)? true: false);
			if (eno == 0) {
			}
			break;
		case SIOCADDMULTI:
		case SIOCDELMULTI:
			eno = eth_multicast_control(&softc->arpcom, ifr, (cmd==SIOCADDMULTI)? true: false);
			break;
		case SIO_RTEMS_SHOW_STATS:
			eth_show(softc);
			break;
		default:
			eno = EINVAL;
			break;
	}

	return eno;
}




static int bsp_eth_attach(struct rtems_bsdnet_ifconfig *config)
{
	eth_driver_control *softc = &_Bsp_eth_Controller;
	struct ifnet *ifp = &softc->arpcom.ac_if;
	char *unit_name = NULL;
	int unit;
	size_t  area_size;
	void *area = NULL;
	char *mtbl = NULL;

	unit = rtems_bsdnet_parse_driver_name(config, &unit_name);
	if (unit < 0) 
		return 0;
	
	if (unit != 0)
		goto out;

	if (config->hardware_address == NULL)
		goto out;

	if (softc->status != ETH_STATE_NOT_INITIALIZED)
		goto out;

	/* Ethernet interrupt vector */
#ifdef NET_DEBUG
	softc->reg = STM32F4_ETH;
#endif
	softc->vector = STM32F4_IRQ_ETH;
	softc->txbuf_nums = ETH_TX_BUF_COUNT;
	softc->rxbuf_nums = ETH_RX_BUF_COUNT;
	softc->phy = DP83848_PHY_ADDR;

	/* */
	softc->clock.mac = STM32F4_RCC_ETHMAC;
	softc->clock.tx = STM32F4_RCC_ETHTX;
	softc->clock.rx = STM32F4_RCC_ETHRX;

    /* Fill ethernet address */
	memcpy(softc->arpcom.ac_enaddr, config->hardware_address, ETHER_ADDR_LEN);

	config->xbuf_count = softc->txbuf_nums;
	config->rbuf_count = softc->rxbuf_nums;
	config->irno = softc->vector;
	config->drv_ctrl = softc;

	/* */
	area_size = softc->txbuf_nums * (sizeof(stm32f4_eth_desc) + sizeof(struct mbuf *)) 
				+ \
				softc->rxbuf_nums * (sizeof(stm32f4_eth_desc) + sizeof(struct mbuf *));

	area = rtems_heap_allocate_aligned_with_boundary(area_size, 4, 0);
	if (area == NULL)
		goto out;

	mtbl = area;
	memset(area, 0, area_size);

	softc->tx_desc = (volatile stm32f4_eth_desc *)mtbl;
	mtbl += (softc->txbuf_nums * sizeof(stm32f4_eth_desc));
	
	softc->rx_desc = (volatile stm32f4_eth_desc *)mtbl;
	mtbl += (softc->rxbuf_nums * sizeof(stm32f4_eth_desc));
	
	softc->tx_mbuf = (struct mbuf **)mtbl;
	mtbl += (softc->txbuf_nums * sizeof(struct mbuf *));
	
	softc->rx_mbuf = (struct mbuf **)mtbl;
	softc->buf_area = area;

	/*
	 * Set MII interface
	 */
	softc->mdio.mdio_r = eth_mdio_read;
	softc->mdio.mdio_w = eth_mdio_write;
	softc->mdio.has_gmii = 0;

	/* 
	 * Set ethernet interface 
	 */
	ifp->if_softc = softc;
	ifp->if_unit = (short)unit;
	ifp->if_name = unit_name;
	ifp->if_mtu = config->mtu > 0? config->mtu: ETHERMTU;
	ifp->if_init = eth_init;
	ifp->if_start = eth_start;
	ifp->if_ioctl = eth_ioctl;
	ifp->if_output = ether_output;
	ifp->if_watchdog = eth_watchdog;
	ifp->if_timer = 0;
	ifp->if_snd.ifq_maxlen = ifqmaxlen;
	ifp->if_flags = IFF_MULTICAST | IFF_BROADCAST | IFF_SIMPLEX;

	/*
	 * Create ethernet thread for driver
	 */
	 softc->tx_thread = rtems_bsdnet_newproc(
	 	"ehtx",
	 	4096,
	 	net_tx_thread,
	 	softc
	 );
	
	 softc->rx_thread = rtems_bsdnet_newproc(
	 	"ehrx",
	 	4096,
	 	net_rx_thread,
	 	softc
	 );

	 /* Change status */
	 ifp->if_flags |= IFF_RUNNING;
	 softc->status = ETH_STATE_DOWN;

	 /* Attach interface and ehernet */
	 if_attach(ifp);
	 ether_ifattach(ifp);

	 return 1;
	
out:
	free(unit_name, 0xdeadbeef);
	free(area, 0xdeadbeef);
	return 0;
	
}

static int bsp_eth_deattach(struct rtems_bsdnet_ifconfig *config)
{
	return 0;
}

int eth_attach(struct rtems_bsdnet_ifconfig *config, int enable)
{
	int rc;
	if (enable > 0)
		rc = bsp_eth_attach(config);
	else
		rc = bsp_eth_deattach(config);

	return rc;
}



