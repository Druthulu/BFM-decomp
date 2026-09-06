#include "common.h"
/* g1: copy + self-update + single use, all foldable by combine (mult chain -> one shift) */
s32 g1(s32 y, s32 w) { s32 x; x = y; x = x * 4; return (x * 8) + w; }
