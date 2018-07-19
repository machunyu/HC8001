#ifndef _GPIO_H_
#define _GPIO_H_
	
//GPIO Register

#define rGPIODATA_BASE					0x40006000
#define rGPIO0DATA               *((volatile uint32_t*)0x40006004)
#define rGPIO1DATA               *((volatile uint32_t*)0x40006008)
#define rGPIO2DATA               *((volatile uint32_t*)0x40006010)
#define rGPIO3DATA               *((volatile uint32_t*)0x40006020)
#define rGPIO4DATA               *((volatile uint32_t*)0x40006040)
#define rGPIO5DATA               *((volatile uint32_t*)0x40006080)
#define rGPIO6DATA               *((volatile uint32_t*)0x40006100)
#define rGPIO7DATA               *((volatile uint32_t*)0x40006200)	
#define rGPIODIR                *((volatile uint32_t*)0x40006400)	
#define rGPIOIS                 *((volatile uint32_t*)0x40006404)	
#define rGPIOIBE                *((volatile uint32_t*)0x40006408)	
#define rGPIOIVE                *((volatile uint32_t*)0x4000640c)	
#define rGPIOIE                 *((volatile uint32_t*)0x40006410)	
#define rGPIORIS                *((volatile uint32_t*)0x40006414)	
#define rGPIOMIS                *((volatile uint32_t*)0x40006418)	
#define rGPIOIC                 *((volatile uint32_t*)0x4000641c)	
	
#endif
