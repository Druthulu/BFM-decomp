#include "common.h"
s32 k7(u16 *p, s32 w) { u32 x = *p; x -= 0x100; return (u8)x + w; }
