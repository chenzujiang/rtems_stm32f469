#ifndef _STM32F4_BSP_ETH_H
#define _STM32F4_BSP_ETH_H
#include <stdint.h>
#include <bsp/utility.h>

#ifdef __cplusplus
extern "C"{
#endif

/*
 * STM32F4 Ethernet Control Register
 */
typedef struct {
 /* MAC */
   uint32_t mac_cr;
   uint32_t mac_ffr;
   uint32_t mac_hthr;
   uint32_t mac_htlr;
   uint32_t mac_miiar;
   uint32_t mac_miidr;
   uint32_t mac_fcr;
   uint32_t mac_vlantr;             /*    8 */
   uint32_t      reserved0[2];
   uint32_t mac_pwuffr;             /*   11 */
   uint32_t mac_pmtcsr;
   uint32_t      reserved1[2];
   uint32_t mac_sr;                 /*   15 */
   uint32_t mac_imr;
   uint32_t mac_a0hr;
   uint32_t mac_a0lr;
   uint32_t mac_a1hr;
   uint32_t mac_a1lr;
   uint32_t mac_a2hr;
   uint32_t mac_a2lr;
   uint32_t mac_a3hr;
   uint32_t mac_a3lr;               /*   24 */
   uint32_t      reserved2[40];

 /* MMC */
   uint32_t mmc_cr;                 /*   65 */
   uint32_t mmc_rir;
   uint32_t mmc_tir;
   uint32_t mmc_rimr;
   uint32_t mmc_timr;               /*   69 */
   uint32_t      reserved3[14];
   uint32_t mmc_tgfsccr;            /*   84 */
   uint32_t mmc_tgfmsccr;
   uint32_t      reserved4[5];
   uint32_t mmc_tgfcr;
   uint32_t      reserved5[10];
   uint32_t mmc_rfcecr;
   uint32_t mmc_rfaecr;
   uint32_t      reserved6[10];
   uint32_t mmc_rgufcr;
   uint32_t      reserved7[334];

 /* PTP */
   uint32_t ptp_tscr;
   uint32_t ptp_ssir;
   uint32_t ptp_tshr;
   uint32_t ptp_tslr;
   uint32_t ptp_tshur;
   uint32_t ptp_tslur;
   uint32_t ptp_tsar;
   uint32_t ptp_tthr;
   uint32_t ptp_ttlr;
   uint32_t 	 reserved8;
   uint32_t ptp_tssr;
   uint32_t      reserved9[565];

 /* DMA */
   uint32_t dma_bmr;
   uint32_t dma_tpdr;
   uint32_t dma_rpdr;
   uint32_t dma_rdlar;
   uint32_t dma_tdlar;
   uint32_t dma_sr;
   uint32_t dma_omr;
   uint32_t dma_ier;
   uint32_t dma_mfbocr;
   uint32_t dma_rswtr;
   uint32_t      reserved10[8];
   uint32_t dma_chtdr;
   uint32_t dma_chrdr;
   uint32_t dma_chtbar;
   uint32_t dma_chrbar;
}stm32f4_eth;

#define  STM32F4_ETH  ((volatile stm32f4_eth *)0x40028000)


/*
 * DMA descriptor 
 */
typedef struct {
	uint32_t status;
	uint32_t bsize;
	uint32_t buf;      /* Buffer 1 */
	uint32_t bufnext;  /* Buffer 2 and next descriptor address pointer */
#ifdef STM32F4_ETH_ENHANCE_DES_ENABLE
	uint32_t extstatus;
	uint32_t reserved;
	uint32_t tslow;
	uint32_t tshigh;
#endif
}stm32f4_eth_desc;


/* 
 * DMA descriptor flags  -- TX TDES0 
 */
#define STM32F4_ETH_DMATX_OWN                 0x80000000
#define STM32F4_ETH_DMATX_IC                  0x40000000
#define STM32F4_ETH_DMATX_LS                  0x20000000
#define STM32F4_ETH_DMATX_FS                  0x10000000
#define STM32F4_ETH_DMATX_DC                  0x08000000
#define STM32F4_ETH_DMATX_DP                  0x04000000
#define STM32F4_ETH_DMATX_TTSE                0x02000000
#define STM32F4_ETH_DMATX_CIC                 0x02000000
#define STM32F4_ETH_DMATX_CIC_BYPASS         0x00000000         
#define STM32F4_ETH_DMATX_CIC_IPV4HDR        0x00400000
#define STM32F4_ETH_DMATX_CIC_TUIP_SEG       0x00800000      
#define STM32F4_ETH_DMATX_CIC_TUIP_FULL      0x00C00000
#define STM32F4_ETH_DMATX_TER                 0x00200000
#define STM32F4_ETH_DMATX_TCH                 0x00100000
#define STM32F4_ETH_DMATX_TTSS                0x00020000
#define STM32F4_ETH_DMATX_IHE                 0x00010000
#define STM32F4_ETH_DMATX_ES                  0x00008000
#define STM32F4_ETH_DMATX_JT                  0x00004000
#define STM32F4_ETH_DMATX_FF                  0x00002000
#define STM32F4_ETH_DMATX_PCE                 0x00001000
#define STM32F4_ETH_DMATX_LCA                 0x00000800
#define STM32F4_ETH_DMATX_NC                  0x00000400
#define STM32F4_ETH_DMATX_LCO                 0x00000200
#define STM32F4_ETH_DMATX_EC                  0x00000100
#define STM32F4_ETH_DMATX_VF                  0x00000080
#define STM32F4_ETH_DMATX_CC                  0x00000078
#define STM32F4_ETH_DMATX_ED                  0x00000004
#define STM32F4_ETH_DMATX_UF                  0x00000002
#define STM32F4_ETH_DMATX_DB                  0x00000001

/* TDES1 */
#define STM32F4_ETH_DMATX_BUF2_SIZE_MASK  0x1FFF0000
#define STM32F4_ETH_DMATX_BUF1_SIZE_MASK  0x00001FFF

/* 
 * DMA descriptor flags  -- RX RDES0 
 */
#define STM32F4_ETH_DMARX_OWN                 0x80000000
#define STM32F4_ETH_DMARX_AFM                 0x40000000     
#define STM32F4_ETH_DMARX_FL                  0x3FFF0000
#define STM32F4_ETH_DMARX_ES                  0x00008000
#define STM32F4_ETH_DMARX_DE                  0x00004000
#define STM32F4_ETH_DMARX_SAF                 0x00002000
#define STM32F4_ETH_DMARX_LE                  0x00001000
#define STM32F4_ETH_DMARX_OE                  0x00000800
#define STM32F4_ETH_DMARX_VLAN                0x00000400
#define STM32F4_ETH_DMARX_FS                  0x00000200
#define STM32F4_ETH_DMARX_LS                  0x00000100
#define STM32F4_ETH_DMARX_IPV4HCE             0x00000080
#define STM32F4_ETH_DMARX_LC                  0x00000040
#define STM32F4_ETH_DMARX_FT                  0x00000020
#define STM32F4_ETH_DMARX_RWT                 0x00000010
#define STM32F4_ETH_DMARX_RE                  0x00000008
#define STM32F4_ETH_DMARX_DBE                 0x00000004
#define STM32F4_ETH_DMARX_CE                  0x00000002
#define STM32F4_ETH_DMARX_MAMPCE              0x00000001

/* RDES1 */
#define STM32F4_ETH_DMARX_DIC                 0x80000000
#define STM32F4_ETH_DMARX_RER                 0x00008000
#define STM32F4_ETH_DMARX_RCH                 0x00004000

#define STM32F4_ETH_DMARX_BUF2_SIZE_MASK   0x1FFF0000
#define STM32F4_ETH_DMARX_BUF1_SIZE_MASK   0x00001FFF


/*
 * STM32F4 Ethernet Buffer Setting
 */
#define STM32F4_ETH_MAX_PACKET_SIZE    1524    /*!< ETH_HEADER + ETH_EXTRA + VLAN_TAG + MAX_ETH_PAYLOAD + ETH_CRC */
#define STM32F4_ETH_HEADER               14    /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define STM32F4_ETH_CRC                   4    /*!< Ethernet CRC */
#define STM32F4_ETH_EXTRA                 2    /*!< Extra bytes in some cases */   
#define STM32F4_ETH_VLAN_TAG                  4    /*!< optional 802.1q VLAN Tag */
#define STM32F4_ETH_MIN_PAYLOAD          46    /*!< Minimum Ethernet payload size */
#define STM32F4_ETH_MAX_PAYLOAD        1500    /*!< Maximum Ethernet payload size */
#define STM32F4_ETH_JUMBO_FRAME_PAYLOAD    9000    /*!< Jumbo frame payload size */  


/*
 * STM32F4 Ethernet PHY Basic Control Register
 */
#if 0
#define STM32F4_ETH_PHY_RESET                 0x8000
#define STM32F4_ETH_PHY_LOOPBACK              0x4000
#define STM32F4_ETH_PHY_FULLDUPLEX_100M      0x2100
#define STM32F4_ETH_PHY_HALFDUPLEX_100M      0x2000
#define STM32F4_ETH_PHY_FULLDUPLEX_10M       0x0100
#define STM32F4_ETH_PHY_HALFDUPLEX_10M       0x0000
#define STM32F4_ETH_PHY_AUTONEG               0x1000
#define STM32F4_ETH_PHY_RESTART_AUTONEG      0x0200
#define STM32F4_ETH_PHY_PWR_DOWN              0x0800             
#define STM32F4_ETH_PHY_ISOLATE               0x0400

/*
 * STM32F4 Ethernet PHY Basic Status Register
 */
#define STM32F4_ETH_PHY_AUTONEG_COMPLETE   0x0020 
#define STM32F4_ETH_PHY_LINKED_STATUS      0x0004
#define STM32F4_ETH_PHY_JABBER_DETECTION   0x0002

#define STM32F4_ETH_PHY_READ_TO      0x0004FFFF
#define STM32F4_ETH_PHY_WRITE_TO     0x0004FFFF

#define STM32F4_ETH_PHY_BCR    0          /*!< Transceiver Basic Control Register */
#define STM32F4_ETH_PHY_BSR    1          /*!< Transceiver Basic Status Register */
#endif

/*
 * STM32F4 Ethernet MAC
 */
#define STM32F4_ETH_MACCR_WATCHDOG_ENABLE   0x00000000
#define STM32F4_ETH_MACCR_WATCHDOG_DISABLE  0x00800000   

#define STM32F4_ETH_MACCR_JABBER_ENABLE     0x00000000
#define STM32F4_ETH_MACCR_JABBER_DISABLE    0x00400000

#define STM32F4_ETH_MACCR_FGAP_96Bits     0x00000000
#define STM32F4_ETH_MACCR_FGAP_88Bits     0x00020000
#define STM32F4_ETH_MACCR_FGAP_80Bits     0x00040000
#define STM32F4_ETH_MACCR_FGAP_72Bits     0x00060000
#define STM32F4_ETH_MACCR_FGAP_64Bits     0x00080000
#define STM32F4_ETH_MACCR_FGAP_56Bits     0x000A0000
#define STM32F4_ETH_MACCR_FGAP_48Bits     0x000C0000
#define STM32F4_ETH_MACCR_FGAP_40Bits     0x000E0000

#define STM32F4_ETH_MACCR_SPEED_10M     0x00000000
#define STM32F4_ETH_MACCR_SPEED_100M    0x00004000

#define STM32F4_ETH_MACCR_FULLDUPLEX    0x00000800
#define STM32F4_ETH_MACCR_HALFDUPLEX    0x00000000

#define STM32F4_ETH_MACCR_ENABLE_TX		0x00000008
#define STM32F4_ETH_MACCR_ENABLE_RX     0x00000004

#define STM32F4_ETH_MACCR_CLEAR_MASK    0xFF20810F

/* MAC Filter */
#define STM32F4_ETH_MACFFL_PM  0x00000001  /* Promiscuous Mode */






/*
 * STM32F4 Ethernet DMA Status Flags
 */
#define STM32F4_ETH_DMA_FLAG_TST           0x20000000  /*!< Time-stamp trigger interrupt (on DMA) */
#define STM32F4_ETH_DMA_FLAG_PMT           0x10000000  /*!< PMT interrupt (on DMA) */
#define STM32F4_ETH_DMA_FLAG_MMC           0x08000000  /*!< MMC interrupt (on DMA) */
#define STM32F4_ETH_DMA_FLAG_DATA_TERR    0x00800000  /*!< Error bits 0-Rx DMA, 1-Tx DMA */
#define STM32F4_ETH_DMA_FLAG_RDWR_ERR     0x01000000  /*!< Error bits 0-write trnsf, 1-read transfr */
#define STM32F4_ETH_DMA_FLAG_ASSC_ERR     0x02000000  /*!< Error bits 0-data buffer, 1-desc. access */
#define STM32F4_ETH_DMA_FLAG_NIS           0x00010000  /*!< Normal interrupt summary flag */
#define STM32F4_ETH_DMA_FLAG_AIS           0x00008000  /*!< Abnormal interrupt summary flag */
#define STM32F4_ETH_DMA_FLAG_ER            0x00004000  /*!< Early receive flag */
#define STM32F4_ETH_DMA_FLAG_FBE           0x00002000  /*!< Fatal bus error flag */
#define STM32F4_ETH_DMA_FLAG_ET            0x00000400  /*!< Early transmit flag */
#define STM32F4_ETH_DMA_FLAG_RWT           0x00000200  /*!< Receive watchdog timeout flag */
#define STM32F4_ETH_DMA_FLAG_RPS           0x00000100  /*!< Receive process stopped flag */
#define STM32F4_ETH_DMA_FLAG_RBU           0x00000080  /*!< Receive buffer unavailable flag */
#define STM32F4_ETH_DMA_FLAG_R             0x00000040  /*!< Receive flag */
#define STM32F4_ETH_DMA_FLAG_TU            0x00000020  /*!< Underflow flag */
#define STM32F4_ETH_DMA_FLAG_RO            0x00000010  /*!< Overflow flag */
#define STM32F4_ETH_DMA_FLAG_TJT           0x00000008  /*!< Transmit jabber timeout flag */
#define STM32F4_ETH_DMA_FLAG_TBU           0x00000004  /*!< Transmit buffer unavailable flag */
#define STM32F4_ETH_DMA_FLAG_TPS           0x00000002  /*!< Transmit process stopped flag */
#define STM32F4_ETH_DMA_FLAG_T             0x00000001  /*!< Transmit flag */

/*
 * STM32F4 Ethernet DMA Interrupt Flags
 */
#define STM32F4_ETH_DMA_IT_TST       0x20000000  /*!< Time-stamp trigger interrupt (on DMA) */
#define STM32F4_ETH_DMA_IT_PMT       0x10000000  /*!< PMT interrupt (on DMA) */
#define STM32F4_ETH_DMA_IT_MMC       0x08000000  /*!< MMC interrupt (on DMA) */
#define STM32F4_ETH_DMA_IT_NIS       0x00010000  /*!< Normal interrupt summary */
#define STM32F4_ETH_DMA_IT_AIS       0x00008000  /*!< Abnormal interrupt summary */
#define STM32F4_ETH_DMA_IT_ER        0x00004000  /*!< Early receive interrupt */
#define STM32F4_ETH_DMA_IT_FBE       0x00002000  /*!< Fatal bus error interrupt */
#define STM32F4_ETH_DMA_IT_ET        0x00000400  /*!< Early transmit interrupt */
#define STM32F4_ETH_DMA_IT_RWT       0x00000200  /*!< Receive watchdog timeout interrupt */
#define STM32F4_ETH_DMA_IT_RPS       0x00000100  /*!< Receive process stopped interrupt */
#define STM32F4_ETH_DMA_IT_RBU       0x00000080  /*!< Receive buffer unavailable interrupt */
#define STM32F4_ETH_DMA_IT_R         0x00000040  /*!< Receive interrupt */
#define STM32F4_ETH_DMA_IT_TU        0x00000020  /*!< Underflow interrupt */
#define STM32F4_ETH_DMA_IT_RO        0x00000010  /*!< Overflow interrupt */
#define STM32F4_ETH_DMA_IT_TJT       0x00000008  /*!< Transmit jabber timeout interrupt */
#define STM32F4_ETH_DMA_IT_TBU       0x00000004  /*!< Transmit buffer unavailable interrupt */
#define STM32F4_ETH_DMA_IT_TPS       0x00000002  /*!< Transmit process stopped interrupt */
#define STM32F4_ETH_DMA_IT_T         0x00000001  /*!< Transmit interrupt */

/*
 * STM32F4 Ethernet DMA Transmit Process State
 */
#define STM32F4_ETH_DMA_TPROC_STOPED      0x00000000  /*!< Stopped - Reset or Stop Tx Command issued */
#define STM32F4_ETH_DMA_TPROC_FETCHING    0x00100000  /*!< Running - fetching the Tx descriptor */
#define STM32F4_ETH_DMA_TPROC_WAITING     0x00200000  /*!< Running - waiting for status */
#define STM32F4_ETH_DMA_TPROC_READING     0x00300000  /*!< Running - reading the data from host memory */
#define STM32F4_ETH_DMA_TPROC_SUSPENDED   0x00600000  /*!< Suspended - Tx Descriptor unavailable */
#define STM32F4_ETH_DMA_TPROC_CLOSING     0x00700000  /*!< Running - closing Rx descriptor */

#define STM32F4_ETH_DMA_RPROC_STOPED      0x00000000  /*!< Stopped - Reset or Stop Rx Command issued */
#define STM32F4_ETH_DMA_RPROC_FETCHING    0x00020000  /*!< Running - fetching the Rx descriptor */
#define STM32F4_ETH_DMA_RPROC_WAITING     0x00060000  /*!< Running - waiting for packet */
#define STM32F4_ETH_DMA_RPROC_SUSPENDED   0x00080000  /*!< Suspended - Rx Descriptor unavailable */
#define STM32F4_ETH_DMA_RPROC_CLOSING     0x000A0000  /*!< Running - closing descriptor */
#define STM32F4_ETH_DMA_RPROC_QUEUING     0x000E0000  /*!< Running - queuing the receive frame into host memory */

/*
 *
 */
#define STM32F4_ETH_DMASR_NIS        0x00010000  /* Normal interrupt summary */
#define STM32F4_ETH_DMASR_AIS        0x00008000  /* Abnormal interrupt summary */

#define STM32F4_ETH_DMASR_ERS        0x00004000  /* Early receive status */
#define STM32F4_ETH_DMASR_FBES       0x00002000  /* Fatal bus error status */
#define STM32F4_ETH_DMASR_ETS        0x00000400  /* Early transmit status */
#define STM32F4_ETH_DMASR_RWTS       0x00000200  /* Receive watchdog timeout status */
#define STM32F4_ETH_DMASR_RPSS       0x00000100  /* Receive process stopped status */
#define STM32F4_ETH_DMASR_RBUS       0x00000080  /* Receive buffer unavailable status */
#define STM32F4_ETH_DMASR_RS         0x00000040  /* Receive status */
#define STM32F4_ETH_DMASR_TUS        0x00000020  /* Transmit underflow status */
#define STM32F4_ETH_DMASR_ROS        0x00000010  /* Receive overflow status */
#define STM32F4_ETH_DMASR_TJTS       0x00000008  /* Transmit jabber timeout status */
#define STM32F4_ETH_DMASR_TBUS       0x00000004  /* Transmit buffer unavailable status */
#define STM32F4_ETH_DMASR_TPSS       0x00000002  /* Transmit process stopped status */
#define STM32F4_ETH_DMASR_TS         0x00000001  /* Transmit status */

/* MII */
#define STM32F4_ETH_MACMIIAR_CR_MASK    0xFFFFFFE3
#define STM32F4_ETH_MACMIIAR_REG(val)  ((val) << 6u)
#define STM32F4_ETH_MACMIIAR_PHY(val)  ((val) << 11u)

#define STM32F4_ETH_MACMIIAR_PA   0x0000F800  /* Physical layer address */ 
#define STM32F4_ETH_MACMIIAR_MR   0x000007C0  /* MII register in the selected PHY */ 
#define STM32F4_ETH_MACMIIAR_CR   0x0000001C  /* CR clock range: 6 cases */ 
#define STM32F4_ETH_MACMIIAR_CR_Div42   0x00000000  /* HCLK:60-100 MHz; MDC clock= HCLK/42 */
#define STM32F4_ETH_MACMIIAR_CR_Div62   0x00000004  /* HCLK:100-150 MHz; MDC clock= HCLK/62 */
#define STM32F4_ETH_MACMIIAR_CR_Div16   0x00000008  /* HCLK:20-35 MHz; MDC clock= HCLK/16 */
#define STM32F4_ETH_MACMIIAR_CR_Div26   0x0000000C  /* HCLK:35-60 MHz; MDC clock= HCLK/26 */
#define STM32F4_ETH_MACMIIAR_CR_Div102  0x00000010  /* HCLK:150-168 MHz; MDC clock= HCLK/102 */  
#define STM32F4_ETH_MACMIIAR_MW   0x00000002  /* MII write */ 
#define STM32F4_ETH_MACMIIAR_MB   0x00000001  /* MII busy */

#define ETH_MII_BUSY() \
	(STM32F4_ETH->mac_miiar & STM32F4_ETH_MACMIIAR_MB)

#define ETH_RX_FRAME_LEN(desc) \
	(((desc).status & STM32F4_ETH_DMARX_FL)>>16)

#define ETH_FIFO_FLUSH() do{\
	STM32F4_ETH->dma_omr |= (1u << 20); \
	while (STM32F4_ETH->dma_omr & (1u << 20)); \
}while(0)

#define ETH_MAC_TRANSMIT_ENABLE() \
	STM32F4_ETH->mac_cr |= (1u << 3)

#define ETH_MAC_RECEIVE_ENABLE() \
	STM32F4_ETH->mac_cr |= (1u << 2)

#define ETH_DMA_TRANSMIT_START() \ 
	STM32F4_ETH->dma_omr |= (1u << 13)
	
#define ETH_DMA_TRANSMIT_STOP() \ 
		STM32F4_ETH->dma_omr &= ~(1u << 13)

#define ETH_DMA_RECEIVE_START() \ 
	STM32F4_ETH->dma_omr |= (1u << 1)

#define ETH_DMA_RECEIVE_STOP() \ 
	STM32F4_ETH->dma_omr &= ~(1u << 1)


/* The DP83848 PHY status register  */
#define DP83848_PHY_ADDR       0x01

#define PHY_SR                 0x10 /* PHY status register Offset */
#define PHY_SPEED_STATUS      0x0002 /* PHY Speed mask */
#define PHY_DUPLEX_STATUS     0x0004 /* PHY Duplex mask */

/* The DP83848 PHY: MII Interrupt Control Register  */
#define PHY_MICR               0x11 /* MII Interrupt Control Register */
#define PHY_MICR_INT_EN       0x0002 /* PHY Enable interrupts */
#define PHY_MICR_INT_OE       0x0001 /* PHY Enable output interrupt events */

/* The DP83848 PHY: MII Interrupt Status and Misc. Control Register */
#define PHY_MISR               0x12 /* MII Interrupt Status and Misc. Control Register */
#define PHY_MISR_LINK_INT_EN  0x0020 /* Enable Interrupt on change of link status */
#define PHY_LINK_STATUS        0x2000 /* PHY link status interrupt mask */


#ifdef __cplusplus
extern "C"{
#endif


#endif
