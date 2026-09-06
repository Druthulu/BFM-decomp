#include "common.h"
s32 h4(u8 *p, s32 w) { u32 x = *p; x &= 0xFF; return (u8)x + w; }
