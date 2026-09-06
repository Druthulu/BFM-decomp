#include "common.h"
s32 k16(s16 *p, s32 w) { s32 x = *p; x -= 0x100; return (u8)x + w; }
