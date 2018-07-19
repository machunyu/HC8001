#ifndef _UART_DRIVER_H_
#define _UART_DRIVER_H_
#include <stdint.h>
	 
	 
extern void hs_uart_init(void);
extern void hs_uart_send(uint8_t ch);
extern void hs_uart_send_str(uint8_t *pStr, uint32_t ulStrLength);
	 

#endif
