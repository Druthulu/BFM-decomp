#include "common.h"
void k18(u8 *p, u8 *q, s32 w) { u32 x = *p; x -= 0x100; q[0] = (u8)x + w; }
