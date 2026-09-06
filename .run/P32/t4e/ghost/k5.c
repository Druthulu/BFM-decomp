#include "common.h"
s32 k5(u16 *p, s32 w) { u32 x = *p; x &= 0xFFF; return (u8)x + w; }
