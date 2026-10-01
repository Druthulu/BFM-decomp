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
 * M2C_FIELD(p,t,o) == *(t)((s8*)p+o): the same LOAD/STORE as `p->field` — but NOT always the
 * same bytes: gcc 2.7.2 marks a member access MEM_IN_STRUCT_P (`/s`) and a cast on a sum not,
 * and its scheduler's alias test reads that flag (sched.c:837-865; the Phase-37 T2 probe: 13 of
 * 139 bodies move when a cast becomes a member — cookbook §458, §351). So m2c struct-heavy
 * output compiles and USUALLY byte-matches without a struct definition; the structs phase
 * replaces every M2C_FIELD with the member it stands for, byte-gated (P37, 2026-09-12 — this
 * note corrected then; it used to claim "identical codegen"). The NON-faithful m2c macros
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

/* Reinterpretation macros (Phase 37 T3, 2026-09-12; sotn's common.h shape): the ONE place a
 * value is read as another width or sign. `*(s16 *)&x` spelled LOH(x) is the same cast and the
 * same bytes (proven by tools/restruct.py's macro probe: cc1's assembly for the macro and for
 * the bare cast is identical) — but the census counts these apart as "reinterpret sites", so a
 * genuine reinterpretation (a word read as two halves, a struct read as bytes) is never a raw
 * pointer cast on a sum. The cast campaign (T6) may only spell a reinterpretation this way. */
#define LOBU(x) (*(u8 *)&(x))
#define LOH(x)  (*(s16 *)&(x))
#define HIH(x)  (((s16 *)&(x))[1])
#define LOHU(x) (*(u16 *)&(x))
#define HIHU(x) (((u16 *)&(x))[1])
#define LOW(x)  (*(s32 *)&(x))
#define LOWU(x) (*(u32 *)&(x))

/* Kept-cast macros (Phase 39 T2, 2026-10-01): the cast campaign's ONLY spelling for a `*(T *)(p + k)` the byte gate
 * refuses as a member. Each expands to the identical cast (same expression tree, same bytes; one make-check IDENTICAL
 * per macro recorded in phase-ends/current/tasks/T2.md) and names ONE cause class. `type_census --check-casts` counts a
 * site by macro name and demands its restruct ledger row (rung S, site verdict KEPT(<class>), R99/R100); a cast outside
 * this set is raw and fails the gate. M2C_FIELD above stays raw (form M). The lvalue reinterpretations LOBU..LOWU above
 * are the set's sixth class, REINTERP.
 *   CAST_ALIAS       SCHED-ALIAS   member spelling (/s) moves the scheduler or cse (cookbook §458)
 *   CAST_SIGN        SIGN          the access's sign differs from the field the layout holds
 *   CAST_WIDTH       WIDTH         overlap loser: a second width at an offset whose layout holds another width
 *   CAST_MISALIGNED  MISALIGNED    the offset is not a multiple of the access width
 *   CAST_NONSTRUCT   NON-STRUCT    the base is arithmetic, not an object the struct map explains */
#define CAST_ALIAS(T, p, k)      (*(T *)((p) + (k)))
#define CAST_SIGN(T, p, k)       (*(T *)((p) + (k)))
#define CAST_WIDTH(T, p, k)      (*(T *)((p) + (k)))
#define CAST_MISALIGNED(T, p, k) (*(T *)((p) + (k)))
#define CAST_NONSTRUCT(T, p, k)  (*(T *)((p) + (k)))

#include "gte_inline.h"   /* Phase 36 T5: the GTE coprocessor macros, one definition each */
#include "struct_types.h" /* Phase 38 T3: the struct map's canonical layouts, one definition each, visible to every space */
#endif /* COMMON_H */
