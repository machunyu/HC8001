#ifndef _I2C1_DRIVER_H_
#define _I2C1_DRIVER_H_
#include <stdint.h>

extern void i2c1_init(void);
extern void i2c1_wr_data(uint16_t sub_addr,uint16_t wr_dat);
extern uint8_t i2c1_rd_data(uint16_t sub_addr);
extern void i2c1_wr_8data(uint16_t sub_addr,uint8_t wr_dat);


#endif
