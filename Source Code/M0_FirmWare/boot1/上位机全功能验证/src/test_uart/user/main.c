#include <string.h>
#include <stdint.h>
#include "cfg.h"
#include "gpio.h"
#include "uart_driver.h"
#include "protocol.h"
#include "i2c1_driver.h"
#include "ov2281_driver.h"
#include "ar0237_driver.h"
#include "dsp_cfg.h"
//#include "core_cm0.h"

#define ISP_IMAGE_W_H                   *((volatile uint32_t*)0x4000912C)
#define ISP_IMAGE_OUT_W_H               *((volatile uint32_t*)0x40009130)
	
#define SENSOR_SEL                      *((volatile uint32_t*)0x40009154)

	
#define ICPR                           *((volatile uint32_t*)0xE000E280)	
#define ICER                           *((volatile uint32_t*)0xE000E180)
#define ISER                           *((volatile uint32_t*)0xE000E100)
	
#define ICPR                           *((volatile uint32_t*)0xE000E280)	

#define ISER                           *((volatile uint32_t*)0xE000E100)	
	
#define IPR0                           *((volatile uint32_t*)0xE000E400)
#define IPR1                           *((volatile uint32_t*)0xE000E404)	
#define IPR2                           *((volatile uint32_t*)0xE000E408)	
#define IPR3                           *((volatile uint32_t*)0xE000E40C)	
#define IPR4                           *((volatile uint32_t*)0xE000E410)	
#define IPR5                           *((volatile uint32_t*)0xE000E414)	
#define IPR6                           *((volatile uint32_t*)0xE000E418)	
#define IPR7                           *((volatile uint32_t*)0xE000E41C)


int main(void)
{
	ICER = 0xfff;
	ICPR = 0xfff;
	ISER = 0xfff;
	TEST_KEY = 0x77686873;
	SW_BOOTLINK_EN |= 0x01;//enable bootlink
	DSP_CTRL|=0x01;//dsp enable
	INT_CTRL|= 0xff ;//enable cm0 int
	UART0_CTRL |= 0x01;//enable uart0
	SW_BOOTLINK_EN |= 0x01;//enable bootlink
	
	while(DSP_CUR_STA!=0x81);
	INT_CTRL|=0xff ;//enable cm0 int
	
	IPR0 |= (1<<14); //Set dsp2 interrupt priority 
	I2C1_CTRL |= 0x01;//enable i2c1
	hs_uart_init();
		
	ISP_IMAGE_W_H = 0x04380780;
	ISP_IMAGE_OUT_W_H = 0x00b40140; 
	
	MIPI_CSI_CTRL|=0x02; 
	
	SENSOR_SEL = 0x02;//sensor选择
	
	DSP_WR_EN1 = 0x77686873;
	TMPL_ENCODE_RX_PARA_FAKE_CHK = 0x03d400c8;//关闭活体检测 
	DSP_WR_EN1 = 0x00;
		
	i2c1_init();
	//enable MIPI pclk
    *(volatile int *)(0x40000060    ) = 0x1;//enable dsp

//----------start up mipi csi host------------//
//release mipi csi host from reset, set controller's internal logic to the default state
    *(volatile int *)(0x40008008    ) = 0x0;
    *(volatile int *)(0x40008008    ) = 0x1;

//***************D: config number of active lanes  ***********//
    *(volatile int *)(0x40008004    ) = 0x1; //001 2lane

//***************oprional: config data id  ***********//
    *(volatile int *)(0x40008010    ) = 0x0;
    *(volatile int *)(0x40008014    ) = 0x0;

//***************E: define error mask  ***********//
    *(volatile int *)(0x400080e4    ) = 0xff;
    *(volatile int *)(0x400080f4    ) = 0xff;
    *(volatile int *)(0x40008104    ) = 0xff;
    *(volatile int *)(0x40008114    ) = 0xff;
    *(volatile int *)(0x40008124    ) = 0xff;
    *(volatile int *)(0x40008134    ) = 0xff;

//***************F: release mipi-csi2 host  reset***********//
    *(volatile int *)(0x40008008    ) = 0x0;
    *(volatile int *)(0x40008008    ) = 0x1;

//***************G: check if data lanes are in stop state***********//
//while((*(volatile uint32_t *)(0x4000804c) & 0x03) != 0x3);
	//ar0237_init();
	ov2281_init();	
	//====================================================================

	hs_uart_protocol();
	
}
