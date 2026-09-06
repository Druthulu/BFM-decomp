#include "common.h"
s32 h1(u16 *p, s32 w) { u32 x = *p; x &= 0xFFFF; return (u16)x + w; }
