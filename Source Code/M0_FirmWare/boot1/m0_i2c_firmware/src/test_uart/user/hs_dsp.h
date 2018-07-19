#ifndef _HS_DSP_H_
#define _HS_DSP_H_
#include <stdint.h>
#include "dsp_cfg.h"

extern uint8_t IrisEncoded(uint32_t index);
extern uint8_t IrisMatch(void);
extern uint8_t IrisEraseOneTemp(uint16_t index);
extern uint8_t IrisEraseAllTemp(void);

#endif
