#ifndef _HS_DSP_H_
#define _HS_DSP_H_
#include <stdint.h>
#include "dsp_cfg.h"

extern uint8_t IrisEncoded(uint16_t index,EyeType eye,EncodeQuaulityLevel level,EncodeType type,RamType ram);
extern uint8_t IrisMatch(uint16_t index,EyeType eye,EncodeQuaulityLevel level,EncodeType type,RamType ram,TempMatchMode mode);
extern uint8_t IrisEraseOneTemp(uint16_t index);
extern uint8_t IrisEraseAllTemp(void);

#endif
