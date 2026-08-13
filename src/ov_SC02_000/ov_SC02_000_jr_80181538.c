#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;
typedef void (*Handler)(struct Entry_8016E95C *);
DEFINE_func_80181538()  /* dedup: shared engine-core @0x80181538 (src/shared) */


extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void);
extern void func_8012C218(void *a0);
extern s32 D_801270CC;

void func_801815F4(s32 param_1) {
    ((s32 (*)(s32))func_8012AD80)(param_1);
    if (func_8012BEE8(param_1) == 0) {
        return;
    }
    switch ((s32)((u32)*(u16 *)(param_1 + 0x70) << 0x10) >> 0x18) {
    case 0:
    case 1:
    case 2:
    case 5:
    case 6:
        ((s32 (*)(s32))func_8012C098)(param_1);
        return;
    case 3:
    case 7:
        ((s32 (*)(s32))func_8012C218)(param_1);
        return;
    case 4:
        D_801270CC = D_801270CC + -1;
        ((s32 (*)(s32))func_8012C218)(param_1);
        return;
    default:
        return;
    }
}
