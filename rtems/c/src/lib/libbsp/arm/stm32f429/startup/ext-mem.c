#include <bsp/stm32f4.h>
#include <bsp/rcc.h>
#include <bsp/ext-mem.h>

typedef struct {
	uint32_t fmc_bank;					 /*!< Specifies the SDRAM memory bank that will be used.
											This parameter can be a value of @ref FMC_SDRAM_Bank */
	
	uint32_t fmc_column_bitsnum;		 /*!< Defines the number of bits of column address.
											  This parameter can be a value of @ref FMC_ColumnBits_Number. */
											  
	uint32_t fmc_row_bitsnum; 		 /*!< Defines the number of bits of column address..
											  This parameter can be a value of @ref FMC_RowBits_Number. */
											  
	uint32_t fmc_data_width; 	   /*!< Defines the memory device width.
											  This parameter can be a value of @ref FMC_SDMemory_Data_Width. */
											  
	uint32_t fmc_ibank_num;	 /*!< Defines the number of bits of column address.
											  This parameter can be of @ref FMC_InternalBank_Number. */
											  
	uint32_t fmc_cas_latency;			 /*!< Defines the SDRAM CAS latency in number of memory clock cycles.
											  This parameter can be a value of @ref FMC_CAS_Latency. */
											  
	uint32_t fmc_wp;		 /*!< Enables the SDRAM bank to be accessed in write mode.
											  This parameter can be a value of @ref FMC_Write_Protection. */
											  
	uint32_t fmc_clock_period; 		 /*!< Define the SDRAM Clock Period for both SDRAM Banks and they allow to disable
											  the clock before changing frequency.
											  This parameter can be a value of @ref FMC_SDClock_Period. */
											  
	uint32_t fmc_rdburst; 			 /*!< This bit enable the SDRAM controller to anticipate the next read commands 
											  during the CAS latency and stores data in the Read FIFO.
											  This parameter can be a value of @ref FMC_Read_Burst. */
											  
	uint32_t fmc_rdpipe_dely; 		 /*!< Define the delay in system clock cycles on read data path.
											  This parameter can be a value of @ref FMC_ReadPipe_Delay. */
											  	

    uint32_t fmc_lta_delay;	   /*!< Defines the delay between a Load Mode Register command and 
											an active or Refresh command in number of memory clock cycles.
											This parameter can be a value between 1 and 16. */
  
    uint32_t fmc_srf_delay;   /*!< Defines the delay from releasing the self refresh command to 
											issuing the Activate command in number of memory clock cycles.
											This parameter can be a value between 1 and 16. */
   
    uint32_t fmc_srf_time; 	   /*!< Defines the minimum Self Refresh period in number of memory clock 
											cycles.
											This parameter can be a value between 1 and 16. */
											
    uint32_t fmc_rc_delay;		   /*!< Defines the delay between the Refresh command and the Activate command
											and the delay between two consecutive Refresh commands in number of 
											memory clock cycles.
											This parameter can be a value between 1 and 16. */
											
    uint32_t fmc_wr_time;	   /*!< Defines the Write recovery Time in number of memory clock cycles.
											This parameter can be a value between 1 and 16. */
											
    uint32_t fmc_rp_delay; 			   /*!< Defines the delay between a Precharge Command and an other command 
											in number of memory clock cycles.
											This parameter can be a value between 1 and 16. */
											
    uint32_t fmc_rcd_delay;			   /*!< Defines the delay between the Activate Command and a Read/Write command
											in number of memory clock cycles.
											This parameter can be a value between 1 and 16. */
}sdram_config;



static void stm32f4_fmc_sdram_init(sdram_config *sdram)
{
	volatile stm32f4_fmc_bank56  *sdram_bank = STM32F4_FMC_BANK56;
	uint32_t	tpr1;
	uint32_t	tpr2;

	tpr1 = sdram->fmc_column_bitsnum | \
			 sdram->fmc_row_bitsnum | \
			 sdram->fmc_data_width | \
			 sdram->fmc_ibank_num | \
			 sdram->fmc_cas_latency | \
			 sdram->fmc_wp | \
			 sdram->fmc_clock_period | \
			 sdram->fmc_rdburst | \
			 sdram->fmc_rdpipe_dely;

	switch(sdram->fmc_bank) {
		case STM32F4_FMC_SDRAM_BANK1: {
	           tpr2 = (sdram->fmc_lta_delay - 1) | \
						 ((sdram->fmc_srf_delay - 1) << 4) | \
						 ((sdram->fmc_srf_time - 1) << 8) | \
						 ((sdram->fmc_rc_delay - 1) << 12) | \
						 ((sdram->fmc_wr_time - 1) << 16) | \
						 ((sdram->fmc_rp_delay - 1) << 20) | \
						 ((sdram->fmc_rcd_delay - 1) << 24);
				
				sdram_bank->sdcr[sdram->fmc_bank] = tpr1;
				sdram_bank->sdtr[sdram->fmc_bank] = tpr2;
			}
			break;
			
		case STM32F4_FMC_SDRAM_BANK2: {
				uint32_t	tpr3 = sdram->fmc_clock_period | \
									 sdram->fmc_rdburst | \
									 sdram->fmc_rdpipe_dely;
				uint32_t    tpr4 = ((sdram->fmc_rc_delay - 1) << 12) | \
									 ((sdram->fmc_rp_delay - 1) << 20);
				tpr2 = (sdram->fmc_lta_delay - 1) | \
						 ((sdram->fmc_srf_delay - 1) << 4) | \
						 ((sdram->fmc_srf_time - 1) << 8) | \
						 ((sdram->fmc_wr_time - 1) << 16);
				
				sdram_bank->sdcr[STM32F4_FMC_SDRAM_BANK1] = tpr3;
				sdram_bank->sdcr[sdram->fmc_bank] = tpr1;

				sdram_bank->sdtr[STM32F4_FMC_SDRAM_BANK1] = tpr4;
				sdram_bank->sdtr[sdram->fmc_bank] = tpr2;
			}
			break;
	}
}


#define SDRAM_SET_CMD(c) { \
	while (sdram_bank->sdsr & 0x20) \
		; \
		sdram_bank->sdcmr = (c);\
}


static void stm32f4_sdram_cmd_init(void)
{
	volatile stm32f4_fmc_bank56  *sdram_bank = STM32F4_FMC_BANK56;
	int	i;
	uint32_t c, tmp;

	/*@ configure a clock configuration enable command */
	SDRAM_SET_CMD(0x1 | 0x8);

	/*@ delay */
	for (i = 0; i < 1000; i++);

	/*@ configure a PALL (precharge all) command */ 
	SDRAM_SET_CMD(0x2 | 0x8);

	/*@ configure a Auto-Refresh command */ 
	c = 0x3 | 0x8 | (0x7 << 5);
	SDRAM_SET_CMD(c);

	/*@ program the external memory mode register */
	tmp = 0x0 | 0x0 | 0x30 | 0x0 | 0x200;
	c = 0x4 | 0x8 | (tmp << 9);
	SDRAM_SET_CMD(c);

	/*@ set the refresh rate counter */
	sdram_bank->sdrtr |= (683 << 1);
}


void stm32f4_sdram_init(stm32f4_sdram_bank bank) 
{
	sdram_config  sdram_cfg;
	
	/*@ enable fmc clock */
	stm32f4_rcc_set_clock(STM32F4_RCC_FSMCR, true);
	
	/*@ config sdram tim */
	sdram_cfg.fmc_lta_delay = 2;
	sdram_cfg.fmc_srf_delay = 7;
	sdram_cfg.fmc_srf_time  = 4;
	sdram_cfg.fmc_rc_delay  = 7;
	sdram_cfg.fmc_wr_time   = 2;
	sdram_cfg.fmc_rp_delay  = 2;
	sdram_cfg.fmc_rcd_delay = 2;

	/*@ config sdram control */
	sdram_cfg.fmc_bank            = bank;
	sdram_cfg.fmc_column_bitsnum  = 0x0; //8 bits
	sdram_cfg.fmc_row_bitsnum     = 0x4;
	sdram_cfg.fmc_data_width      = 0x10; //16 bit
	sdram_cfg.fmc_ibank_num       = 0x40;
	sdram_cfg.fmc_cas_latency     = 0x180;
	sdram_cfg.fmc_wp              = 0x0;
	sdram_cfg.fmc_clock_period    = 0x800;
	sdram_cfg.fmc_rdburst         = 0x1000;
	sdram_cfg.fmc_rdpipe_dely     = 0x2000;

	stm32f4_fmc_sdram_init(&sdram_cfg);
	stm32f4_sdram_cmd_init();
}

