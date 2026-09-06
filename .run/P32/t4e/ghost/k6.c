#include "common.h"
s32 k6(u32 *p, s32 w) { u32 x = *p; x &= 0xFFF; return (u16)x + w; }
