#include "common.h"
/* g5: parameter copy + self-update + single use inside a bigger body with a call (spills present) */
extern void h(s32);
s32 g5(s32 y, s32 w, s32 k) { s32 x; x = y; x = x * 4; h(k); return (x * 8) + w; }
