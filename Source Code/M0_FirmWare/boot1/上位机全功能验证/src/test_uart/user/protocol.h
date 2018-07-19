#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <stdint.h>

#define WRITE_OK         0x00000000
#define WRITE_FAIL       0x00000001
#define READ_OK          0x00000002
#define READ_FAIL        0x00000003
#define CRC8_FAIL        0x00000004


#define WRITE_REG        0x00000001
#define READ_REG         0x00000002
#define DOWNLOAD_TEMP    0x00000003
#define UPLOAD_TEMP      0x00000004
#define UPLOAD_IMAG      0x00000005
#define DOWNLOAD_IMAG    0x00000006


#define READ_ONLY        0x00000000
#define READ_WRITE       0x00000001
#define WRITE_ONLY       0x00000002


extern void hs_uart_protocol(void);
extern uint8_t IrisEncoded(uint32_t index);

#endif
