#ifndef _UART_H_
#define _UART_H_
	
//UART Register

#define rUARTDR                        *((volatile uint32_t*)0x40001000)
#define rUARTRSR                       *((volatile uint32_t*)0x40001004)
#define rUARTECR                       *((volatile uint32_t*)0x40001004)
#define rUARTFR                        *((volatile uint32_t*)0x40001018)
#define rUARTILPR                      *((volatile uint32_t*)0x40001020)
#define rUARTIBRD                      *((volatile uint32_t*)0x40001024)
#define rUARTFBRD                      *((volatile uint32_t*)0x40001028)
#define rUARTLCR_H                     *((volatile uint32_t*)0x4000102C)
#define rUARTCR                        *((volatile uint32_t*)0x40001030)
#define rUARTIFLS                      *((volatile uint32_t*)0x40001034)
#define rUARTIMSC                      *((volatile uint32_t*)0x40001038)
#define rUARTRIS                       *((volatile uint32_t*)0x4000103C)
#define rUARTMIS                       *((volatile uint32_t*)0x40001040)
#define rUARTICR                       *((volatile uint32_t*)0x40001044)
	
#endif
