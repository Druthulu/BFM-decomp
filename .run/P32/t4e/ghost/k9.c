#include "common.h"
void k9(u16 *p, u8 *q, s32 c) { u32 x = *p; if (c) x -= 0x100; *q = x; }
