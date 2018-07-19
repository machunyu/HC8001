#include <string.h>
#include <stdint.h>
#include "cfg.h"
#include "gpio.h"
//#include "uart_driver.h"
#include "protocol.h"
#include "i2c1_driver.h"
#include "af0140_driver.h"
#include "ar0237_driver.h"
#include "dsp_cfg.h"
#include "i2c0_driver.h"
//#include "core_cm0.h"

#define ISP_IMAGE_W_H                   *((volatile uint32_t*)0x4000912C)
#define ISP_IMAGE_OUT_W_H               *((volatile uint32_t*)0x40009130)
	
#define SENSOR_SEL                      *((volatile uint32_t*)0x40009154)	
	
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
	DSP_CTRL|=0x01;//dsp enable
	INT_CTRL|= 0xff ;//enable cm0 int
	SPI0_SEL &=~ 0x01;//iic mode
	I2C0_CTRL |= 0x01;//enable spi0
	SW_BOOTLINK_EN |= 0x01;//enable bootlink
	
	while(DSP_CUR_STA!=0x81);
	DSP_CMD |= 0x10000;
	INT_CTRL|=0xff ;//enable cm0 int
	
	IPR0 |= (1<<14); //Set dsp2 interrupt priority 
	I2C1_CTRL |= 0x01;//enable i2c1
	
	i2c0_init();
	
	DSP_WR_EN3 = 0x77686873;
	WRITE_TEMP_TIMEOUT = 0XFFFFFFFF;
	DSP_WR_EN3 = 0x00;
	ISP_IMAGE_W_H = 0x04380780;
	ISP_IMAGE_OUT_W_H = 0x00b40140; 
	
	MIPI_CSI_CTRL|=0x02; 
	
	SENSOR_SEL = 0x03;//sensorÑ¡Ôñ
		
	i2c1_init();

	ar0237_init();	
	
	while(1)
	{
		IrisEncoded(56);
	}
}
