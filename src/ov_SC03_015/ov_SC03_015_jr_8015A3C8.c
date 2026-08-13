#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
DEFINE_func_8015A3C8()  /* dedup: shared engine-core @0x8015A3C8 (src/shared) */


DEFINE_func_8015AB7C()  /* dedup: shared engine-core @0x8015AB7C (src/shared) */

DEFINE_func_8015ABD4()  /* dedup: shared engine-core @0x8015ABD4 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (param held in $s0 across 3 calls; lhu 0x16E; &D_8018DB9C arg)
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018DB9C;

void func_8015AC48(s32 arg0)
{
    func_80154150(arg0, 9);
    func_80146DB8((s32 *)arg0, &D_8018DB9C);
    func_80161CD0(arg0, M2C_FIELD(arg0, u16 *, 0x16E));
}


DEFINE_func_8015AC90()  /* dedup: shared engine-core @0x8015AC90 (src/shared) */

DEFINE_func_8015ACC4()  /* dedup: shared engine-core @0x8015ACC4 (src/shared) */

DEFINE_func_8015AD08()  /* dedup: shared engine-core @0x8015AD08 (src/shared) */


DEFINE_func_8015AD3C()  /* dedup: shared engine-core @0x8015AD3C (src/shared) */


DEFINE_func_8015AD78()  /* dedup: shared engine-core @0x8015AD78 (src/shared) */

DEFINE_func_8015ADB0()  /* dedup: shared engine-core @0x8015ADB0 (src/shared) */

