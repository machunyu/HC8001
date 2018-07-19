#ifndef _I2C0_DRIVER_H_
#define _I2C0_DRIVER_H_
#include <stdint.h>

extern void i2c0_init(void);
extern void hs_i2c0_send(uint8_t ch);
extern void hs_i2c0_send_str(uint8_t *pStr, uint32_t ulStrLength);


#endif
