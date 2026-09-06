#include "common.h"
s32 k17(u8 *p, s32 w) { u32 x = *p; x -= 0x100; return (x & 0xFF) + w; }
