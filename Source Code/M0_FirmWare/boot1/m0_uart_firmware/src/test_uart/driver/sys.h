#ifndef _SYS_H_
#define _SYS_H_
#include <stdint.h>

extern void delay(volatile uint32_t nCount);
extern uint8_t CalCRC8(uint8_t *vptr, uint32_t len);

#endif
