#ifndef _MAIN_H_
#define _MAIN_H_


#define TEST_KEY                     *((volatile uint32_t*)0x40000020)
#define SW_BOOTLINK_EN_TEST          *((volatile uint32_t*)0x40000028)	
	
#define SPI0_SEL          *((volatile uint32_t*)0x4000003C)
#define EXT_CLK_CTRL	  *((volatile uint32_t*)0x40000040)
#define UART0_CTRL        *((volatile uint32_t*)0x40000044)
#define I2C0_CTRL	      *((volatile uint32_t*)0x40000048)
#define SPI0_CTRL	      *((volatile uint32_t*)0x4000004C)
#define TIMER0_CTRL       *((volatile uint32_t*)0x40000050)
#define WDT0_CTRL         *((volatile uint32_t*)0x40000054)
#define GPIO0_CTRL        *((volatile uint32_t*)0x40000058)
#define I2C1_CTRL	      *((volatile uint32_t*)0x4000005C)
#define MIPI_CSI_CTRL	  *((volatile uint32_t*)0x40000060)
#define DSP_CTRL	      *((volatile uint32_t*)0x40000064)
#define PLL_CTRL0         *((volatile uint32_t*)0x40000068)
#define PLL_CTRL1	      *((volatile uint32_t*)0x4000006C)
#define PLL_STA	          *((volatile uint32_t*)0x40000070)	
	
#define DSP_CUR_STA       *((volatile uint32_t*)0x40009304)
#define DSP_ERR_STATUS    *((volatile uint32_t*)0x4000930c)	
#define USER_CODE_SIZE    *((volatile uint32_t*)0x40009124)

#define DSP_SPECIAL_REG_APB_BUS_RW_ENABLE_0   *((volatile uint32_t*)0x40009320)
#define DSP_SPECIAL_REG_APB_BUS_RW_ENABLE_1   *((volatile uint32_t*)0x40009324)
#define DSP_SPECIAL_REG_APB_BUS_RW_ENABLE_2   *((volatile uint32_t*)0x40009328)
#define DSP_SPECIAL_REG_APB_BUS_RW_ENABLE_3   *((volatile uint32_t*)0x4000932C)	
	
#endif
