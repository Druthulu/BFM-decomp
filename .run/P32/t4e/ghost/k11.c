#include "common.h"
void k11(u16 *p, u8 *q) { u32 x = *p; x &= 0xFFF; *q = x; }
