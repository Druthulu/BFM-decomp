/* common.h — shared prelude for every matched C translation unit under src/.
 *
 * Created Phase 6 (the asm->c flip): splat emits `#include "common.h"` at the top
 * of each generated src/ file, but does NOT generate the header itself — it is a
 * hand-maintained, COMMITTED file (unlike the gitignored include/ .inc macros).
 *
 * For the all-INCLUDE_ASM scaffold only `include_asm.h` is required; the fixed-width
 * typedefs below are the psyq/sotn convention, here ready for the first matched C.
 * Grow this (PSY-Q types, hardware-register decls, shared structs) as functions match.
 */
#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef short          s16;
typedef int            s32;
typedef float          f32;

#endif /* COMMON_H */
