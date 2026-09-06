#include "common.h"
extern s32 f(void);
s32 k10(s32 w) { u32 x = f(); x -= 0x100; return (u8)x + w; }
