#include "common.h"
s32 k15(u8 *p, u8 *q) { u32 x = *p; x -= 0x100; *q = (u8)x + 1; return 0; }
