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
/* wider scalars (Phase 16: m2c's M2C_UNK64 needs s64). Byte-neutral — no existing match uses them. */
typedef unsigned long long u64;
typedef long long          s64;
typedef double             f64;

/* m2c --valid-syntax compat (Phase 16, cookbook §15) — the BYTE-FAITHFUL macros only.
 * M2C_FIELD(p,t,o) == *(t)((s8*)p+o): identical codegen to `p->field`, so m2c struct-heavy
 * output compiles AND byte-matches without a struct definition. The NON-faithful m2c macros
 * (M2C_ERROR/MULT_HI/CLZ/GTE/...) are deliberately left UNDEFINED: a draft using one fails to
 * compile = an early "not m2c-matchable, defer" signal (it could never byte-match anyway). */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#ifndef NULL
#define NULL ((void *)0)   /* m2c emits NULL for null pointers; byte-neutral (== 0) */
#endif

#include "gte_inline.h"   /* Phase 36 T5: the GTE coprocessor macros, one definition each */
#endif /* COMMON_H */
