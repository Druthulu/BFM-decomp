#include "common.h"
/* g3: single-set chain (no self-update) — control: refs are zeroed */
s32 g3(s32 y, s32 w) { s32 x; s32 t; x = y; t = x * 4; return (t * 8) + w; }
