#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
DEFINE_func_8015AE2C()  /* dedup: shared engine-core @0x8015AE2C (src/shared) */

DEFINE_func_8015B6F4()  /* dedup: shared engine-core @0x8015B6F4 (src/shared) */

DEFINE_func_8015B7B4()  /* dedup: shared engine-core @0x8015B7B4 (src/shared) */

DEFINE_func_8015B858()  /* dedup: shared engine-core @0x8015B858 (src/shared) */

DEFINE_func_8015B8F8()  /* dedup: shared engine-core @0x8015B8F8 (src/shared) */

DEFINE_func_8015B950()  /* dedup: shared engine-core @0x8015B950 (src/shared) */

DEFINE_func_8015BD8C()  /* dedup: shared engine-core @0x8015BD8C (src/shared) */

DEFINE_func_8015BDD0()  /* dedup: shared engine-core @0x8015BDD0 (src/shared) */

DEFINE_func_8015BE04()  /* dedup: shared engine-core @0x8015BE04 (src/shared) */



DEFINE_func_8015BE38()  /* dedup: shared engine-core @0x8015BE38 (src/shared) */


DEFINE_func_8015BE74()  /* dedup: shared engine-core @0x8015BE74 (src/shared) */

DEFINE_func_8015BE94()  /* dedup: shared engine-core @0x8015BE94 (src/shared) */

DEFINE_func_8015BEC4()  /* dedup: shared engine-core @0x8015BEC4 (src/shared) */

DEFINE_func_8015BEE4()  /* dedup: shared engine-core @0x8015BEE4 (src/shared) */

DEFINE_func_8015BF04()  /* dedup: shared engine-core @0x8015BF04 (src/shared) */

DEFINE_func_8015BF48()  /* dedup: shared engine-core @0x8015BF48 (src/shared) */

DEFINE_func_8015BF7C()  /* dedup: shared engine-core @0x8015BF7C (src/shared) */

DEFINE_func_8015BFB0()  /* dedup: shared engine-core @0x8015BFB0 (src/shared) */


DEFINE_func_8015BFF4()  /* dedup: shared engine-core @0x8015BFF4 (src/shared) */



/* §71 sibling-first: this is DEFINE_func_8015C0C4 (src/shared/engine_core.h L8919)
 * with the two globals replaced by the second parameter and <<6 -> <<7.
 * The explicit temporary `t` keeps the first lh ahead of the 0x238 store.
 *
 * Signature is the fleet canon `(s32 *a0, s32 a1)` declared by
 * DEFINE_func_8015BFB0 (engine_core.h L16218) — a private `(s32, s16 *)`
 * definition also match_one-MATCHes but breaks the real TU with
 * `conflicting types`.  The s16 reads are cast at the use site. */

DEFINE_func_8015C030()  /* dedup: shared engine-core @0x8015C030 (src/shared) */


DEFINE_func_8015C08C()  /* dedup: shared engine-core @0x8015C08C (src/shared) */

DEFINE_func_8015C0C4()  /* dedup: shared engine-core @0x8015C0C4 (src/shared) */

#include "common.h"



s32 func_8015C128(s32 param_1) {
    extern void func_8015C6E0(int);
    extern void (*D_8018DC08[])(int);

    int sp10[3];
    int sp20[3];
    int temp_s0;
    int temp_v0;

    ((void(*)())func_80149FB0)();
    if (((int(*)(int))func_80148AFC)(((int)param_1)) & 0xFF) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = -0x4000;
        ((void(*)(int, int *, int *))func_8001382C)(*(short *)(*(int *)(((int)param_1) + 0x20) + 0x12), sp10, sp20);
        *(int *)(((int)param_1) + 0x234) += sp20[0];
        *(int *)(((int)param_1) + 0x238) += sp20[1];
        *(int *)(((int)param_1) + 0x23C) += sp20[2];
    }
    ((void(*)(int, int *, int *))func_8001382C)((short)(-*(unsigned short *)(*(int *)(((int)param_1) + 0x20) + 0x12)),
                  (int *)(((int)param_1) + 0x234), sp20);
    ((void(*)(int, int *))func_80146DB8)(((int)param_1), sp20);
    func_80147A84(((int)param_1));
    ((void(*)(int))func_801473EC)(((int)param_1));
    if (!(D_800B99DA & 3)) {
        ((void(*)(int, int))func_8014C010)(((int)param_1), 1);
        ((void(*)(int))func_80147324)(0x65F);
    }
    if (((int(*)(int))func_8014D738)(((int)param_1)) != 0) {
        D_8018DC08[*(u16 *)((int)param_1)](((int)param_1));
        func_8015C6E0(((int)param_1));
        return;
    }
    temp_s0 = ((int(*)(int))func_8014CC28)(((int)param_1));
    temp_v0 = ((int(*)(int))func_8014F3E8)(((int)param_1));
    if (temp_v0 != 0) {
        if ((temp_v0 & 0xFF00) != 0x4000) {
            ((void(*)(int, int))func_80146E90)(((int)param_1), 6);
            ((void(*)(int))func_80146CA0)(((int)param_1));
            return;
        }
        if ((temp_v0 & 0x4000) && ((int(*)(int))func_80146E98)(((int)param_1)) != 0) {
            ((void(*)(int, int))func_80147078)(((int)param_1), 4);
            ((void(*)(int))func_8015C0C4)(((int)param_1));
        }
    } else if (temp_s0 == 0) {
        D_8018DC08[*(u16 *)((int)param_1)](((int)param_1));
        ((void(*)(int, int))func_80147078)(((int)param_1), 3);
        ((void(*)(int))func_8015BE94)(((int)param_1));
    }
}
