#include "common.h"
s32 h7(u16 *p, s32 w) { u16 x = *p; u16 y; y = x; x = y; return (u16)x + w; }
