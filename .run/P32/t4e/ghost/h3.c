#include "common.h"
s32 h3(u16 *p, s32 w) { u32 x = *p; x &= 0xFFFF; return x + w; }
