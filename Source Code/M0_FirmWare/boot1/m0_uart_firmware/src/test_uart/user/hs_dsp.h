#ifndef _HS_DSP_H_
#define _HS_DSP_H_
#include <stdint.h>
#include "dsp_cfg.h"

#define ENCODE             0x01
#define MATCH              0x02
#define ERASER_ONE_TEMP    0x03
#define ERASER_ALL_TEMP    0x04
#define UPLOAD_TEMPLATE    0x05
#define UPLOAD_IMAGE        0x06


extern uint8_t IrisEncoded(uint32_t index);
extern uint8_t IrisMatch(void);
extern uint8_t IrisEraseOneTemp(uint16_t index);
extern uint8_t IrisEraseAllTemp(void);

#endif
