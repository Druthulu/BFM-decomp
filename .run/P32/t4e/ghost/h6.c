#include "common.h"
s32 h6(u16 *p, s32 w) { u32 x; u32 y; x = *p; x &= 0xFFFF; y = (u16)x; return y * w; }
