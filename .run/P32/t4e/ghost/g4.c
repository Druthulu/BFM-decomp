#include "common.h"
/* g4: self-update via shift/add that combine folds into one insn (x = y; x <<= 2; z = x << 3) */
s32 g4(s32 y, s32 w) { s32 x; x = y; x <<= 2; return (x << 3) + w; }
