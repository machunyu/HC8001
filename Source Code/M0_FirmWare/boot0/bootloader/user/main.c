#include <string.h>
#include <stdint.h>
#include "cfg.h"
#include "gpio.h"
#include "uart_driver.h"


#define APPLICATION_ADDRESS     (uint32_t)0x20000000
typedef  void (*pFunction)(void);

pFunction Jump_To_Application;
uint32_t JumpAddress;


__asm void MSR_MSP(uint32_t addr) 
{
    MSR MSP, r0 //set Main Stack value
    BX r14
}

int main(void)
{
	uint32_t CodeSize;
			
    DSP_CTRL |= 0x01;//enable dsp block clock
	
	GPIO0_CTRL |= 0x01;//enable gpio0 block clock
	
	rGPIODIR |= (1<<1);
	
	rGPIO1DATA &=~(1<<1);
		
    while(DSP_CUR_STA!=0x81)//µÈ´ýFlash copy ready
	{
		if((DSP_ERR_STATUS&0x01)==1)//Check read Flash timeout
		{
			rGPIO1DATA |= (1<<1);
		}
	}	
	CodeSize = USER_CODE_SIZE;
	
    memcpy((void*)0x20000000,(void*)0x30000000,CodeSize);//copy BL1 user code to iram
	
	/* Test if user code is programmed starting from address "APPLICATION_ADDRESS" */
    if (((*(volatile uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000 ) == 0x20000000)
    {
		JumpAddress = *(volatile uint32_t*) (APPLICATION_ADDRESS + 4);
		Jump_To_Application = (pFunction) JumpAddress;
		MSR_MSP(*(volatile uint32_t*) APPLICATION_ADDRESS);
		Jump_To_Application();  
	}	
}


