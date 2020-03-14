#include <stdlib.h>
#include <rtems.h>
#include <rtems/bspIo.h>

#include <bsp/irq-generic.h>
#include <bsp/stm32f4_dma.h>
#include <bsp/rcc.h>

#define  STM32F4_DMA_NSTREAM      16
#define  STM32F4_GET_CONTROLLER(n)  dma_controller[n]


static volatile stm32f4_dma *dma_controller[] = {STM32F4_DMA1, STM32F4_DMA2};
static dma_message *dma_message_block;

static inline bool
stm32f4_dma_is_free(int device, int nstream)
{
	volatile stm32f4_dma *dma = STM32F4_GET_CONTROLLER(device);
	return (dma->stream[nstream].cr & STM32F4_DMA_SxCR_EN)? false: true;
}

int	
stm32f4_dma_startxx(dma_message *msg)
{
	volatile stm32f4_dma *dma = STM32F4_GET_CONTROLLER(msg->dma.device);
	uint32_t  stream  = msg->dma.stream;
	uint32_t  channel = msg->dma.channel;
	uint32_t  direct  = msg->dma.direct;
	uint32_t  reg;
	
	if (!stm32f4_dma_is_free(msg->dma.device, stream))
		goto err;
	
	reg = dma->stream[stream].cr;
	reg &= ~(STM32F4_DMA_SxCR_CHSEL_MSK | STM32F4_DMA_SxCR_DIR_MSK  | STM32F4_DMA_SxCR_EN);
	reg |= ((channel << 25)| (direct << 6));

	switch(direct << 6) {
		case STM32F4_DMA_SxCR_DIR_OUT:
			 dma->stream[stream].par = msg->des_address;
			 dma->stream[stream].mar0 = msg->src_address;
			 break;
		case STM32F4_DMA_SxCR_DIR_IN:
			dma->stream[stream].par = msg->src_address;
			dma->stream[stream].mar0 = msg->des_address;
			break;
		case STM32F4_DMA_SxCR_DIR_INER:
			dma->stream[stream].mar0 = msg->src_address;
			dma->stream[stream].mar1 = msg->des_address;
			break;
		default:
			goto err;
	}
	msg->thread_id = rtems_task_self();
	dma->stream[stream].ndtr = msg->size;
 	dma->stream[stream].cr = reg; 
	dma->stream[stream].cr |= STM32F4_DMA_SxCR_EN;
	
	return 0;
err:
	return -1;
}


int 	
stm32f4_dma_start(int schannel)
{
	int device  = STM32F4_GET_DEVICE(schannel);
	int nstream = STM32F4_GET_STREAM(schannel);
	volatile stm32f4_dma *dma = STM32F4_GET_CONTROLLER(device);
	if (stm32f4_dma_is_free(device, nstream)) {
		dma->stream[nstream].cr |= STM32F4_DMA_SxCR_EN;
		return 0;
	}
	return -1;
}

void  
stm32f4_dma_stop(int device, int nstream)
{
	volatile stm32f4_dma *dma = STM32F4_GET_CONTROLLER(device);
	do {
		dma->stream[nstream].cr &= ~STM32F4_DMA_SxCR_EN;
	}while (dma->stream[nstream].cr & STM32F4_DMA_SxCR_EN);
}

int
stm32f4_dma_remain(int device, int nstream)
{
	volatile stm32f4_dma *dma = STM32F4_GET_CONTROLLER(device);
	return dma->stream[nstream].ndtr;
}

void 
stm32f4_dma_interrupt_set(int device, int nstream, uint32_t itype, bool enable)
{
	volatile stm32f4_dma *dma = STM32F4_GET_CONTROLLER(device);

	if (enable) {
		if (itype & STM32F4_DMA_SxFCR_FEIE)
			dma->stream[nstream].fcr |= STM32F4_DMA_SxFCR_FEIE;
		dma->stream[nstream].cr |= itype & STM32F4_DAM_SxCR_IMASK;
	}else {
		dma->stream[nstream].cr &= ~(itype & STM32F4_DAM_SxCR_IMASK);
		if (itype & STM32F4_DMA_SxFCR_FEIE)
			dma->stream[nstream].fcr &= ~STM32F4_DMA_SxFCR_FEIE;
	}
}

int 
stm32f4_dma_interrupt_clear(int device, int nstream)
{
	const uint8_t rshift[] = {0, 6, 16, 22, 0, 6, 16, 22}; 
	volatile stm32f4_dma *dma = STM32F4_GET_CONTROLLER(device);
	uint32_t  itype = 0x3dul << rshift[nstream];
	int  ret;

    ret = itype  & STM32F4_DMA_FCR_RESERVE_MASK;
	if (nstream >= 4) {
		dma->h_ifcr = ret;
	}else {
		dma->l_ifcr = ret;
	}
	return ret;
}

static void
dma_interrupt_process(void *arg)
{
	dma_message *msg = arg;
	int iflags;

	iflags = stm32f4_dma_interrupt_clear(msg->dma.device, msg->dma.stream);
	if (msg->handler)
		msg->handler(iflags, msg->arg);
	rtems_event_transient_send(msg->thread_id);
}

rtems_status_code
dma_wait_done(dma_message *msg)
{
	rtems_event_transient_receive(RTEMS_WAIT, 0);
	return dma_stream_release(msg->dma.device, msg->dma.stream);
}

int
stm32f4_dma_init(int schannel, const dma_config *data, uint32_t fifo)
{
	int device  = STM32F4_GET_DEVICE(schannel);
	int nstream = STM32F4_GET_STREAM(schannel);
	volatile stm32f4_dma *dma = STM32F4_GET_CONTROLLER(device);
	uint16_t	 stm = (device << 3) + nstream;

	if (data == NULL)
		return 0;
	
	if (dma_message_block == NULL) {
		int  i;
		int  vector;
		dma_message_block = malloc(sizeof(dma_message) * STM32F4_DMA_NSTREAM);
		if (dma_message_block == NULL) {
			printk("Initialize dma message block failed\n");
			return -1;
		}
		memset(dma_message_block, 0, sizeof(dma_message) * STM32F4_DMA_NSTREAM);

		/*@ Initialize dma1 stream vector */
		vector = STM32F4_IRQ_DMA1_STREAM0;
		for (i = 0; i < 7; i++)
			dma_message_block[i].dma.vector = vector++;
		dma_message_block[i].dma.vector = STM32F4_IRQ_DMA1_STREAM7;

		/*@ Initialize dma2 stream vector */
		vector = STM32F4_IRQ_DMA2_STREAM0;
		for (i = 8; i < 5+8; i++)
			dma_message_block[i].dma.vector = vector++;	

		vector = STM32F4_IRQ_DMA2_STREAM5;
		for ( ; i < 8+8; i++)
			dma_message_block[i].dma.vector = vector++;	
	}
	/*@ Enable DMA conroller clock */
	stm32f4_rcc_set_clock((device == 0)? STM32F4_RCC_DMA1: STM32F4_RCC_DMA2, true);
	
	/*@ Clear interrupt flag, if need */
	if (data->config & STM32F4_DAM_SxCR_IMASK) {
		/*@ Enable DMA interrupt */
		stm32f4_dma_interrupt_clear(device, nstream);

		rtems_interrupt_handler_install(
			dma_message_block[stm].dma.vector,
			"DMA-STREAM",
			RTEMS_INTERRUPT_UNIQUE,
			dma_interrupt_process,
			&dma_message_block[stm]
		);

	}
	
	/*@ Configure DMA */
	dma->stream[nstream].fcr = fifo;
	dma->stream[nstream].cr = data->config;
	return 0;
}

dma_message * 
dma_stream_obtain(int device, int nstream)
{
	uint16_t	stm = (device << 3) + nstream;
	rtems_status_code  sc;

	if (dma_message_block[stm].mutex == 0) {
		sc = rtems_semaphore_create(
			rtems_build_name('d', 'm', 'a', '0'+stm),
			1,
			RTEMS_BINARY_SEMAPHORE | RTEMS_FIFO,
			0,
			&dma_message_block[stm].mutex
		);
		if (sc != RTEMS_SUCCESSFUL)
			return NULL;
	}
	sc = rtems_semaphore_obtain(dma_message_block[stm].mutex, RTEMS_WAIT, 0);
	if (sc != RTEMS_SUCCESSFUL) {
		return NULL;
	}

	dma_message_block[stm].dma.device = device;
	dma_message_block[stm].dma.stream = nstream; 
	return dma_message_block + stm;
}

rtems_status_code 
dma_stream_release(int device, int nstream)
{
	uint16_t	stm = (device << 3) + nstream;
	if (dma_message_block[stm].mutex == 0) 
		return RTEMS_SUCCESSFUL;
	return rtems_semaphore_release(dma_message_block[stm].mutex);
}

rtems_status_code
dma_set_interrupt_handler(int device, int nstream, dma_interrutp_handler handler, void *arg)
{
    rtems_status_code sc;
	uint16_t stm = (device << 3) + nstream;
	dma_message * msg;
	
    sc = rtems_semaphore_obtain(
			dma_message_block[stm].mutex, 
			RTEMS_WAIT, 
			0
	);
	if (sc != RTEMS_SUCCESSFUL)
		return sc;
	msg->handler = handler;
	msg->arg = arg;
	rtems_semaphore_release(
		dma_message_block[stm].mutex
	);
	return RTEMS_SUCCESSFUL;
}

int 
dma_copy(int schannel, void *src, void *des, size_t size, uint8_t direct)
{
	int device  = STM32F4_GET_DEVICE(schannel);
	int nstream = STM32F4_GET_STREAM(schannel);
	dma_message * msg;
	int	rc;

	/* Obtain dma stream */
	msg = dma_stream_obtain(device, nstream);
	if (msg ==  NULL)
		return -1;

	/*@  Fill dma message structure */
	msg->dma.channel = STM32F4_GET_CHANNEL(schannel);
	msg->dma.direct  = direct&0x3;
	msg->src_address = (uint32_t)src;
	msg->des_address = (uint32_t)des;
	msg->size = size;

	/*@ Start dma transfer */
	rc = stm32f4_dma_startxx(msg);
	if (rc != 0)
		goto err;

	/*@ Wait dma transfer */
	dma_wait_done(msg);
	return 0;

err:
	dma_stream_release(msg->dma.device, msg->dma.stream);
	return -1;
}








