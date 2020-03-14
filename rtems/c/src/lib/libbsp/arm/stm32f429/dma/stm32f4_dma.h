#ifndef STM32F4_DMA_H
#define STM32F4_DMA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef void (*dma_interrutp_handler)(int, void *);

typedef struct {
	struct {
		int	device:4;
		int	stream:4;
		int	channel:4;
		int	direct:3;
		int vector:17;
	}dma;
	dma_interrutp_handler handler;
	void	    *arg;
	rtems_id	mutex;
	rtems_id	thread_id;
	uint32_t	src_address;
	uint32_t    des_address;
	uint32_t	size;
}dma_message;


typedef struct {
	uint32_t	cr;
	uint32_t	ndtr;
	uint32_t	par;
	uint32_t	mar0;
	uint32_t	mar1;
	uint32_t	fcr;
}stm32f4_dma_stream;

typedef struct {
	uint32_t	l_isr;
	uint32_t	h_isr;
	uint32_t	l_ifcr;
	uint32_t	h_ifcr;

	stm32f4_dma_stream	stream[8];
}stm32f4_dma;

typedef enum {
	STM32F4_DMA_SREAM0 = 0,
	STM32F4_DMA_SREAM1,
	STM32F4_DMA_SREAM2,
	STM32F4_DMA_SREAM3,
	STM32F4_DMA_SREAM4,
	STM32F4_DMA_SREAM5,
	STM32F4_DMA_SREAM6,
	STM32F4_DMA_SREAM7
}stm32f4_dma_stream_ch;


typedef union {
	struct dma_cfg_reg {
		uint32_t	dma_en:1;
		uint32_t    dma_dmeie:1;
		uint32_t    dma_teie:1;
		uint32_t    dma_htie:1;
		uint32_t    dma_tcie:1;
		uint32_t    dma_pfctrl:1;
		uint32_t    dma_dir:2;
		uint32_t    dma_circ:1;
		uint32_t    dma_pinc:1;
		uint32_t    dma_minc:1;
		uint32_t    dma_psize:2;
		uint32_t    dma_msize:2;
		uint32_t    dma_pincos:1;
		uint32_t    dma_pl:2;
		uint32_t	dma_dbm:1;
		uint32_t    dma_ct:1;
		uint32_t	dma_reserved:1;
		uint32_t    dma_pburst:2;
		uint32_t    dma_mburst:2;
		uint32_t    dma_chsel:3;
	}reg;
	uint32_t  config;
}dma_config;


typedef int (*dma_init)(stm32f4_dma_stream *stream, bool eni, void *data);


/*@ */
#define  DMA_PERIPHERY_TO_MEM   0x0
#define  DMA_MEM_TO_PERIPHERY   0x1
#define  DMA_MEM0_TO_MEM1       0x2


/********************  Bits definition for STM32F4_DMA_SxCR register  *****************/ 
#define STM32F4_DMA_SxCR_CHSEL_0                     (0x0ul << 25)
#define STM32F4_DMA_SxCR_CHSEL_1                     (0x1ul << 25)
#define STM32F4_DMA_SxCR_CHSEL_2                     (0x2ul << 25) 
#define STM32F4_DMA_SxCR_CHSEL_3                     (0x3ul << 25) 
#define STM32F4_DMA_SxCR_CHSEL_4                     (0x4ul << 25) 
#define STM32F4_DMA_SxCR_CHSEL_5                     (0x5ul << 25) 
#define STM32F4_DMA_SxCR_CHSEL_6                     (0x6ul << 25) 
#define STM32F4_DMA_SxCR_CHSEL_7                     (0x7ul << 25) 
#define STM32F4_DMA_SxCR_CHSEL_MSK                  (0x7ul << 25)

#define STM32F4_DMA_SxCR_MBURST_SINGLE            (0x0ul << 23)
#define STM32F4_DMA_SxCR_MBURST_INCR4              (0x1ul << 23)
#define STM32F4_DMA_SxCR_MBURST_INCR8              (0x2ul << 23)
#define STM32F4_DMA_SxCR_MBURST_INCR16             (0x3ul << 23)
#define STM32F4_DMA_SxCR_PBURST_SINGLE             (0x0ul << 21)
#define STM32F4_DMA_SxCR_PBURST_INCR4               (0x1ul << 21)
#define STM32F4_DMA_SxCR_PBURST_INCR8               (0x2ul << 21)
#define STM32F4_DMA_SxCR_PBURST_INCR16              (0x3ul << 21)

#define STM32F4_DMA_SxCR_ACK                         (0x1ul << 20)
#define STM32F4_DMA_SxCR_CT                          (0x1ul << 19)  
#define STM32F4_DMA_SxCR_DBM                         (0x1ul << 18)

#define STM32F4_DMA_SxCR_PL_0                     (0x0ul << 16)   
#define STM32F4_DMA_SxCR_PL_1                     (0x1ul << 16)  
#define STM32F4_DMA_SxCR_PL_2					  (0x2ul << 16)
#define STM32F4_DMA_SxCR_PL_3                     (0x3ul << 16)
#define STM32F4_DMA_SxCR_PINCOS                   (0x1ul << 15)
#define STM32F4_DMA_SxCR_MSIZE_8                  (0x0ul << 13)
#define STM32F4_DMA_SxCR_MSIZE_16                 (0x1ul << 13)
#define STM32F4_DMA_SxCR_MSIZE_32                 (0x2ul << 13)
#define STM32F4_DMA_SxCR_PSIZE_8                  (0x0ul << 11)
#define STM32F4_DMA_SxCR_PSIZE_16                 (0x1ul << 11) 
#define STM32F4_DMA_SxCR_PSIZE_32                 (0x2ul << 11)

#define STM32F4_DMA_SxCR_MINC                       (0x1ul << 10)
#define STM32F4_DMA_SxCR_PINC                       (0x1ul << 9)
#define STM32F4_DMA_SxCR_CIRC                       (0x1ul << 8)

#define STM32F4_DMA_SxCR_DIR_OUT                   (0x1ul << 6)
#define STM32F4_DMA_SxCR_DIR_IN                     (0x0ul << 6)
#define STM32F4_DMA_SxCR_DIR_INER                  (0x2ul << 6)
#define STM32F4_DMA_SxCR_DIR_MSK                    (0x3ul << 6)

#define STM32F4_DMA_SxCR_PFCTRL                     (0x1ul << 5)

#define STM32F4_DMA_SxCR_TCIE                        (0x1ul << 4)
#define STM32F4_DMA_SxCR_HTIE                        (0x1ul << 3)
#define STM32F4_DMA_SxCR_TEIE                        (0x1ul << 2)
#define STM32F4_DMA_SxCR_DMEIE                       (0x1ul << 1)
#define STM32F4_DAM_SxCR_IMASK         				 (0xful << 1)         

#define STM32F4_DMA_SxCR_EN                           (0x1ul << 0)

/********************  Bits definition for STM32F4_DMA_SxCNDTR register  **************/
#define STM32F4_DMA_SxNDT                            ((uint32_t)0x0000FFFF)
#define STM32F4_DMA_SxNDT_0                          ((uint32_t)0x00000001)
#define STM32F4_DMA_SxNDT_1                          ((uint32_t)0x00000002)
#define STM32F4_DMA_SxNDT_2                          ((uint32_t)0x00000004)
#define STM32F4_DMA_SxNDT_3                          ((uint32_t)0x00000008)
#define STM32F4_DMA_SxNDT_4                          ((uint32_t)0x00000010)
#define STM32F4_DMA_SxNDT_5                          ((uint32_t)0x00000020)
#define STM32F4_DMA_SxNDT_6                          ((uint32_t)0x00000040)
#define STM32F4_DMA_SxNDT_7                          ((uint32_t)0x00000080)
#define STM32F4_DMA_SxNDT_8                          ((uint32_t)0x00000100)
#define STM32F4_DMA_SxNDT_9                          ((uint32_t)0x00000200)
#define STM32F4_DMA_SxNDT_10                         ((uint32_t)0x00000400)
#define STM32F4_DMA_SxNDT_11                         ((uint32_t)0x00000800)
#define STM32F4_DMA_SxNDT_12                         ((uint32_t)0x00001000)
#define STM32F4_DMA_SxNDT_13                         ((uint32_t)0x00002000)
#define STM32F4_DMA_SxNDT_14                         ((uint32_t)0x00004000)
#define STM32F4_DMA_SxNDT_15                         ((uint32_t)0x00008000)

/********************  Bits definition for STM32F4_DMA_SxFCR register  ****************/ 
#define STM32F4_DMA_SxFCR_FEIE                       ((uint32_t)0x00000080)
#define STM32F4_DMA_SxFCR_FS                         ((uint32_t)0x00000038)
#define STM32F4_DMA_SxFCR_FS_0                       ((uint32_t)0x00000008)
#define STM32F4_DMA_SxFCR_FS_1                       ((uint32_t)0x00000010)
#define STM32F4_DMA_SxFCR_FS_2                       ((uint32_t)0x00000020)
#define STM32F4_DMA_SxFCR_DMDIS                      ((uint32_t)0x00000004)
#define STM32F4_DMA_SxFCR_FTH                        ((uint32_t)0x00000003)
#define STM32F4_DMA_SxFCR_FTH_0                      ((uint32_t)0x00000001)
#define STM32F4_DMA_SxFCR_FTH_1                      ((uint32_t)0x00000002)

/********************  Bits definition for STM32F4_DMA_LISR register  *****************/ 
#define STM32F4_DMA_LISR_TCIF3                       ((uint32_t)0x08000000)
#define STM32F4_DMA_LISR_HTIF3                       ((uint32_t)0x04000000)
#define STM32F4_DMA_LISR_TEIF3                       ((uint32_t)0x02000000)
#define STM32F4_DMA_LISR_DMEIF3                      ((uint32_t)0x01000000)
#define STM32F4_DMA_LISR_FEIF3                       ((uint32_t)0x00400000)
#define STM32F4_DMA_LISR_TCIF2                       ((uint32_t)0x00200000)
#define STM32F4_DMA_LISR_HTIF2                       ((uint32_t)0x00100000)
#define STM32F4_DMA_LISR_TEIF2                       ((uint32_t)0x00080000)
#define STM32F4_DMA_LISR_DMEIF2                      ((uint32_t)0x00040000)
#define STM32F4_DMA_LISR_FEIF2                       ((uint32_t)0x00010000)
#define STM32F4_DMA_LISR_TCIF1                       ((uint32_t)0x00000800)
#define STM32F4_DMA_LISR_HTIF1                       ((uint32_t)0x00000400)
#define STM32F4_DMA_LISR_TEIF1                       ((uint32_t)0x00000200)
#define STM32F4_DMA_LISR_DMEIF1                      ((uint32_t)0x00000100)
#define STM32F4_DMA_LISR_FEIF1                       ((uint32_t)0x00000040)
#define STM32F4_DMA_LISR_TCIF0                       ((uint32_t)0x00000020)
#define STM32F4_DMA_LISR_HTIF0                       ((uint32_t)0x00000010)
#define STM32F4_DMA_LISR_TEIF0                       ((uint32_t)0x00000008)
#define STM32F4_DMA_LISR_DMEIF0                      ((uint32_t)0x00000004)
#define STM32F4_DMA_LISR_FEIF0                       ((uint32_t)0x00000001)

/********************  Bits definition for STM32F4_DMA_HISR register  *****************/ 
#define STM32F4_DMA_HISR_TCIF7                       ((uint32_t)0x08000000)
#define STM32F4_DMA_HISR_HTIF7                       ((uint32_t)0x04000000)
#define STM32F4_DMA_HISR_TEIF7                       ((uint32_t)0x02000000)
#define STM32F4_DMA_HISR_DMEIF7                      ((uint32_t)0x01000000)
#define STM32F4_DMA_HISR_FEIF7                       ((uint32_t)0x00400000)
#define STM32F4_DMA_HISR_TCIF6                       ((uint32_t)0x00200000)
#define STM32F4_DMA_HISR_HTIF6                       ((uint32_t)0x00100000)
#define STM32F4_DMA_HISR_TEIF6                       ((uint32_t)0x00080000)
#define STM32F4_DMA_HISR_DMEIF6                      ((uint32_t)0x00040000)
#define STM32F4_DMA_HISR_FEIF6                       ((uint32_t)0x00010000)
#define STM32F4_DMA_HISR_TCIF5                       ((uint32_t)0x00000800)
#define STM32F4_DMA_HISR_HTIF5                       ((uint32_t)0x00000400)
#define STM32F4_DMA_HISR_TEIF5                       ((uint32_t)0x00000200)
#define STM32F4_DMA_HISR_DMEIF5                      ((uint32_t)0x00000100)
#define STM32F4_DMA_HISR_FEIF5                       ((uint32_t)0x00000040)
#define STM32F4_DMA_HISR_TCIF4                       ((uint32_t)0x00000020)
#define STM32F4_DMA_HISR_HTIF4                       ((uint32_t)0x00000010)
#define STM32F4_DMA_HISR_TEIF4                       ((uint32_t)0x00000008)
#define STM32F4_DMA_HISR_DMEIF4                      ((uint32_t)0x00000004)
#define STM32F4_DMA_HISR_FEIF4                       ((uint32_t)0x00000001)

/********************  Bits definition for STM32F4_DMA_LIFCR register  ****************/ 
#define STM32F4_DMA_LIFCR_CTCIF3                     ((uint32_t)0x08000000)
#define STM32F4_DMA_LIFCR_CHTIF3                     ((uint32_t)0x04000000)
#define STM32F4_DMA_LIFCR_CTEIF3                     ((uint32_t)0x02000000)
#define STM32F4_DMA_LIFCR_CDMEIF3                    ((uint32_t)0x01000000)
#define STM32F4_DMA_LIFCR_CFEIF3                     ((uint32_t)0x00400000)
#define STM32F4_DMA_LIFCR_CTCIF2                     ((uint32_t)0x00200000)
#define STM32F4_DMA_LIFCR_CHTIF2                     ((uint32_t)0x00100000)
#define STM32F4_DMA_LIFCR_CTEIF2                     ((uint32_t)0x00080000)
#define STM32F4_DMA_LIFCR_CDMEIF2                    ((uint32_t)0x00040000)
#define STM32F4_DMA_LIFCR_CFEIF2                     ((uint32_t)0x00010000)
#define STM32F4_DMA_LIFCR_CTCIF1                     ((uint32_t)0x00000800)
#define STM32F4_DMA_LIFCR_CHTIF1                     ((uint32_t)0x00000400)
#define STM32F4_DMA_LIFCR_CTEIF1                     ((uint32_t)0x00000200)
#define STM32F4_DMA_LIFCR_CDMEIF1                    ((uint32_t)0x00000100)
#define STM32F4_DMA_LIFCR_CFEIF1                     ((uint32_t)0x00000040)
#define STM32F4_DMA_LIFCR_CTCIF0                     ((uint32_t)0x00000020)
#define STM32F4_DMA_LIFCR_CHTIF0                     ((uint32_t)0x00000010)
#define STM32F4_DMA_LIFCR_CTEIF0                     ((uint32_t)0x00000008)
#define STM32F4_DMA_LIFCR_CDMEIF0                    ((uint32_t)0x00000004)
#define STM32F4_DMA_LIFCR_CFEIF0                     ((uint32_t)0x00000001)

/********************  Bits definition for STM32F4_DMA_HIFCR  register  ****************/ 
#define STM32F4_DMA_HIFCR_CTCIF7                     ((uint32_t)0x08000000)
#define STM32F4_DMA_HIFCR_CHTIF7                     ((uint32_t)0x04000000)
#define STM32F4_DMA_HIFCR_CTEIF7                     ((uint32_t)0x02000000)
#define STM32F4_DMA_HIFCR_CDMEIF7                    ((uint32_t)0x01000000)
#define STM32F4_DMA_HIFCR_CFEIF7                     ((uint32_t)0x00400000)
#define STM32F4_DMA_HIFCR_CTCIF6                     ((uint32_t)0x00200000)
#define STM32F4_DMA_HIFCR_CHTIF6                     ((uint32_t)0x00100000)
#define STM32F4_DMA_HIFCR_CTEIF6                     ((uint32_t)0x00080000)
#define STM32F4_DMA_HIFCR_CDMEIF6                    ((uint32_t)0x00040000)
#define STM32F4_DMA_HIFCR_CFEIF6                     ((uint32_t)0x00010000)
#define STM32F4_DMA_HIFCR_CTCIF5                     ((uint32_t)0x00000800)
#define STM32F4_DMA_HIFCR_CHTIF5                     ((uint32_t)0x00000400)
#define STM32F4_DMA_HIFCR_CTEIF5                     ((uint32_t)0x00000200)
#define STM32F4_DMA_HIFCR_CDMEIF5                    ((uint32_t)0x00000100)
#define STM32F4_DMA_HIFCR_CFEIF5                     ((uint32_t)0x00000040)
#define STM32F4_DMA_HIFCR_CTCIF4                     ((uint32_t)0x00000020)
#define STM32F4_DMA_HIFCR_CHTIF4                     ((uint32_t)0x00000010)
#define STM32F4_DMA_HIFCR_CTEIF4                     ((uint32_t)0x00000008)
#define STM32F4_DMA_HIFCR_CDMEIF4                    ((uint32_t)0x00000004)
#define STM32F4_DMA_HIFCR_CFEIF4                     ((uint32_t)0x00000001)

#define STM32F4_DMA_FCR_RESERVE_MASK   		0x0F7D0F7D


/*@ DMA stream channel */
#define  STM32F4_SET_CHANNEL(d, s, c)  ((d << 16) | (s << 8) | c) 
#define  STM32F4_GET_CHANNEL(dsc)  (dsc) & 0xff 
#define  STM32F4_GET_STREAM(dsc)   ((dsc) >> 8) & 0xff 
#define  STM32F4_GET_DEVICE(dsc)   ((dsc) >> 16) & 0xff

/*@  DMA1 stream channel */
#define  DMA_SPI3_RX_CHANNEL   		STM32F4_SET_CHANNEL(0, 0, 0)   /*@ stream 0 */
#define  DMA_I2C1_RX_CHANNEL   		STM32F4_SET_CHANNEL(0, 0, 1) 
#define  DMA_TIM4_CHANNEL      		STM32F4_SET_CHANNEL(0, 0, 2)
#define  DMA_I2S3_EXT_RX_CHANNEL 	STM32F4_SET_CHANNEL(0, 0, 3)
#define  DMA_UART5_RX_CHANNEL       STM32F4_SET_CHANNEL(0, 0, 4)
#define  DMA_UART8_TX_CHANNEL       STM32F4_SET_CHANNEL(0, 0, 5)
#define  DMA_TIM5_CH3_UP_CHANNEL    STM32F4_SET_CHANNEL(0, 0, 6)   

#define  DMA_TIM2_CH3_UP_CHANNEL    STM32F4_SET_CHANNEL(0, 1, 3)  /*@ stream 1 */
#define  DMA_USART3_RX_CHANNEL      STM32F4_SET_CHANNEL(0, 1, 4)
#define  DMA_UART7_TX_CHANNEL       STM32F4_SET_CHANNEL(0, 1, 5)
#define  DMA_TIM5_CH4_TRIG_CHANNEL  STM32F4_SET_CHANNEL(0, 1, 6)
#define  DMA_TIM6_UP_CHANNEL        STM32F4_SET_CHANNEL(0, 1, 7) 

#define  DMA_SPI3_RX_CHANNEL        STM32F4_SET_CHANNEL(0, 2, 0)  /*@ stream 2 */ 
#define  DMA_TIM7_UP_CHANNEL        STM32F4_SET_CHANNEL(0, 2, 1) 
#define  DMA_I2S3_EXT_RX_CHANNEL    STM32F4_SET_CHANNEL(0, 2, 2)
#define  DMA_I2C3_RX_CHANNEL        STM32F4_SET_CHANNEL(0, 2, 3)
#define  DMA_UART4_RX_CHANNEL       STM32F4_SET_CHANNEL(0, 2, 4)
#define  DMA_TIM3_CH4_UP_CHANNEL    STM32F4_SET_CHANNEL(0, 2, 5)
#define  DMA_TIM5_CH1_CHANNEL       STM32F4_SET_CHANNEL(0, 2, 6)
#define  DMA_I2C2_RX_CHANNEL        STM32F4_SET_CHANNEL(0, 2, 7)

#define  DMA_SPI2_RX_CHANNEL        STM32F4_SET_CHANNEL(0, 3, 0) /*@ stream 3 */ 
#define  DMA_TIM4_CH2_CHANNEL       STM32F4_SET_CHANNEL(0, 3, 2)
#define  DMA_I2S2_EXT_RX_CHANNEL    STM32F4_SET_CHANNEL(0, 3, 3)
#define  DMA_USART3_TX_CHANNEL      STM32F4_SET_CHANNEL(0, 3, 4)
#define  DMA_UART7_RX_CHANNEL       STM32F4_SET_CHANNEL(0, 3, 5)
//#define  DMA_TIM5_CH4_TRIG_CHANNEL  
#define  DMA_I2C2_RX_CHANNEL        STM32F4_SET_CHANNEL(0, 3, 7)
 
#define  DMA_SPI2_TX_CHANNEL        STM32F4_SET_CHANNEL(0, 4, 0) /*@ stream 4 */ 
#define  DMA_TIM7_UP_CHANNEL        STM32F4_SET_CHANNEL(0, 4, 1)
#define  DMA_I2S2_EXT_TX_CHANNEL    STM32F4_SET_CHANNEL(0, 4, 2)
#define  DMA_I2C3_TX_CHANNEL        STM32F4_SET_CHANNEL(0, 4, 3)
#define  DMA_UART4_TX_CHANNEL       STM32F4_SET_CHANNEL(0, 4, 4)
#define  DMA_TIM3_CH1_TRIG_CHANNEL  STM32F4_SET_CHANNEL(0, 4, 5)
#define  DMA_TIM5_CH1_CHANNEL       STM32F4_SET_CHANNEL(0, 4, 6)
#define  DMA_USART3_TX_CHANNEL      STM32F4_SET_CHANNEL(0, 4, 7)

#define  DMA_SPI3_TX_CHANNEL        STM32F4_SET_CHANNEL(0, 5, 0) /*@ stream 5 */ 
#define  DMA_I2C1_RX_CHANNEL        STM32F4_SET_CHANNEL(0, 5, 1)
#define  DMA_I2S3_EXT_TX_CHANNEL    STM32F4_SET_CHANNEL(0, 5, 2)
#define  DMA_TIM2_CH1_CHANNEL       STM32F4_SET_CHANNEL(0, 5, 3)
#define  DMA_USART2_RX_CHANNEL      STM32F4_SET_CHANNEL(0, 5, 4)
#define  DMA_TIM3_CH2_CHANNEL       STM32F4_SET_CHANNEL(0, 5, 5)
#define  DMA_DAC1_CHANNEL           STM32F4_SET_CHANNEL(0, 5, 7)

#define  DMA_I2C1_TX_CHANNEL        STM32F4_SET_CHANNEL(0, 6, 1) /*@ stream 6 */ 
#define  DMA_TIM4_UP_CHANNEL        STM32F4_SET_CHANNEL(0, 6, 2)
#define  DMA_TIM2_CH24_CHANNEL      STM32F4_SET_CHANNEL(0, 6, 3)
#define  DMA_USART2_TX_CHANNEL      STM32F4_SET_CHANNEL(0, 6, 4)
#define  DMA_UART8_RX_CHANNEL       STM32F4_SET_CHANNEL(0, 6, 5)
#define  DMA_TIM5_UP_CHANNEL        STM32F4_SET_CHANNEL(0, 6, 6)
#define  DMA_DAC2_CHANNEL           STM32F4_SET_CHANNEL(0, 6, 7)  

#define  DMA_SPI3_TX_CHANNEL        STM32F4_SET_CHANNEL(0, 7, 0) /*@ stream 7 */ 
#define  DMA_I2C1_TX_CHANNEL        STM32F4_SET_CHANNEL(0, 7, 1)
#define  DMA_TIM4_CH3_CHANNEL       STM32F4_SET_CHANNEL(0, 7, 2)
#define  DMA_TIM2_CH4_UP_CHANNEL    STM32F4_SET_CHANNEL(0, 7, 3)
#define  DMA_UART5_TX_CHANNEL      STM32F4_SET_CHANNEL(0, 7, 4)
#define  DMA_TIM3_CH3_CHANNEL       STM32F4_SET_CHANNEL(0, 7, 5)
#define  DMA_I2C2_TX_CHANNEL        STM32F4_SET_CHANNEL(0, 7, 7)


/*@  DMA2 stream channel */

#define  DMA_ADC1_CHANNEL           STM32F4_SET_CHANNEL(1, 0, 0) /*@ stream 0 */ 
#define  DMA_ADC3_CHANNEL           STM32F4_SET_CHANNEL(1, 0, 2)
#define  DMA_SPI1_RX_CHANNEL        STM32F4_SET_CHANNEL(1, 0, 3)
#define  DMA_SPI4_RX_CHANNEL        STM32F4_SET_CHANNEL(1, 0, 4)
#define  DMA_TIM1_TRIG_CHANNEL      STM32F4_SET_CHANNEL(1, 0, 6)

#define  DMA_CDMI_CHANNEL           STM32F4_SET_CHANNEL(1, 1, 1) /*@ stream 1 */ 
#define  DMA_ADC3_CHANNEL           STM32F4_SET_CHANNEL(1, 1, 2)
#define  DMA_SPI4_TX_CHANNEL        STM32F4_SET_CHANNEL(1, 1, 4)
#define  DMA_USART6_TX_CHANNEL      STM32F4_SET_CHANNEL(1, 1, 5)
#define  DMA_TIM1_CH1_CHANNLE       STM32F4_SET_CHANNEL(1, 1, 6)
#define  DMA_TIM8_UP_CHANNEL        STM32F4_SET_CHANNEL(1, 1, 7)

#define  DMA_TIM8_CH_123_CHANNEL    STM32F4_SET_CHANNEL(1, 2, 0) /*@ stream 2 */ 
#define  DMA_ADC2_CHANNEL           STM32F4_SET_CHANNEL(1, 2, 1)
#define  DMA_SPI1_RX_CHANNEL        STM32F4_SET_CHANNEL(1, 2, 3)
#define  DMA_USART1_RX_CHANNEL      STM32F4_SET_CHANNEL(1, 2, 4)
#define  DMA_USART6_RX_CHANNEL      STM32F4_SET_CHANNEL(1, 2, 5)
#define  DMA_TIM1_CH2_CHANNEL       STM32F4_SET_CHANNEL(1, 2, 6)
#define  DMA_TIM8_CH1_CHANNEL       STM32F4_SET_CHANNEL(1, 2, 7)

#define  DMA_ADC2_CHANNEL           STM32F4_SET_CHANNEL(1, 3, 1) /*@ stream 3 */ 
#define  DMA_SPI5_RX_CHANNEL        STM32F4_SET_CHANNEL(1, 3, 2)
#define  DMA_SPI1_TX_CHANNEL        STM32F4_SET_CHANNEL(1, 3, 3)
#define  DMA_SDIO_CHANNEL           STM32F4_SET_CHANNEL(1, 3, 4)
#define  DMA_SPI4_RX_CHANNEL        STM32F4_SET_CHANNEL(1, 3, 5)
#define  DMA_TIM1_CH1_CHANNEL       STM32F4_SET_CHANNEL(1, 3, 6)
#define  DMA_TIM8_CH2_CHANNEL       STM32F4_SET_CHANNEL(1, 3, 7)

#define  DMA_ADC1_CHANNEL           STM32F4_SET_CHANNEL(1, 4, 0) /*@ stream 4 */ 
#define  DMA_SPI5_TX_CHANNEL        STM32F4_SET_CHANNEL(1, 4, 2)
#define  DMA_SPI4_RX_CHANNEL        STM32F4_SET_CHANNEL(1, 4, 5)
#define  DMA_TIM1_COM_CH4_TRIG_CHANNEL  STM32F4_SET_CHANNEL(1, 4, 6)
#define  DMA_TIM8_CH3_CHANNEL       STM32F4_SET_CHANNEL(1, 4, 7)

#define  DMA_SPI6_TX_CHANNEL        STM32F4_SET_CHANNEL(1, 5, 1) /*@ stream 5 */ 
#define  DMA_CRYP_OUT_CHANNEL       STM32F4_SET_CHANNEL(1, 5, 2)
#define  DMA_SPI1_TX_CHANNEL        STM32F4_SET_CHANNEL(1, 5, 3)
#define  DMA_USART1_RX_CHANNEL      STM32F4_SET_CHANNEL(1, 5, 4)
#define  DMA_TIM1_UP_CHANNEL        STM32F4_SET_CHANNEL(1, 5, 6)
#define  DMA_SPI5_RX_CHANNEL        STM32F4_SET_CHANNEL(1, 5, 7)

#define  DMA_TIM1_CH_123_CHANNEL    STM32F4_SET_CHANNEL(1, 6, 0) /*@ stream 6 */ 
#define  DMA_SPI6_RX_CHANNEL        STM32F4_SET_CHANNEL(1, 6, 1)
#define  DMA_CRYP_IN_CHANNEL        STM32F4_SET_CHANNEL(1, 6, 2)
#define  DMA_SDIO_CHANNEL           STM32F4_SET_CHANNEL(1, 6, 4)
#define  DMA_USART6_TX_CHANNEL      STM32F4_SET_CHANNEL(1, 6, 5)
#define  DMA_TIM1_CH3_CHANNEL       STM32F4_SET_CHANNEL(1, 6, 6)
#define  DMA_SPI5_TX_CHANNEL        STM32F4_SET_CHANNEL(1, 6, 7)

#define  DMA_DCMI_CHANNEL           STM32F4_SET_CHANNEL(1, 7, 1) /*@ stream 7 */ 
#define  DMA_HASH_IN_CHANNEL        STM32F4_SET_CHANNEL(1, 7, 2)
#define  DMA_USART1_TX_CHANNEL      STM32F4_SET_CHANNEL(1, 7, 4)
#define  DMA_USART6_TX_CHANNEL      STM32F4_SET_CHANNEL(1, 7, 5)
#define  DMA_TIM8_CH4_TRIG_COM_CHANNEL STM32F4_SET_CHANNEL(1, 7, 7)


#define STM32F4_DMA1   ((volatile stm32f4_dma *)0x40026000)
#define STM32F4_DMA2   ((volatile stm32f4_dma *)0x40026400)


int	
stm32f4_dma_startxx(dma_message *msg);

int 	
stm32f4_dma_start(int schannel);

void  
stm32f4_dma_stop(int device, int nstream);

int
stm32f4_dma_remain(int device, int nstream);

void 
stm32f4_dma_interrupt_set(int device, int nstream, uint32_t itype, bool enable);

int 
stm32f4_dma_interrupt_clear(int device, int nstream);

int
stm32f4_dma_init(int schannel, const dma_config *data, uint32_t fifo);

dma_message * 
dma_stream_obtain(int device, int nstream);

rtems_status_code 
dma_stream_release(int device, int nstream);

rtems_status_code
dma_wait_done(dma_message *msg);

rtems_status_code
dma_set_interrupt_handler(int channel, dma_interrutp_handler handler, void *arg);

int 
dma_copy(int schannel, void *src, void *des, size_t size, uint8_t direct);


#ifdef __cplusplus
}
#endif

#endif
