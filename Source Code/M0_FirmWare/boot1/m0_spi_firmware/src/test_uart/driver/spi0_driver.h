#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_
#include <stdint.h>

extern void spi0_init(void);
extern void hs_spi0_send(uint8_t ch);
extern void hs_spi0_send_str(uint8_t *pStr, uint32_t ulStrLength);


#endif
