#include "common.h"
/* g2: same but the first set is a MEM load (the copy cannot merge into the shift) */
s32 g2(s32 *p, s32 w) { s32 x; x = *p; x = x * 4; return (x * 8) + w; }
