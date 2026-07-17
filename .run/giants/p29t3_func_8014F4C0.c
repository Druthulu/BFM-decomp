// @class: plumbing
// @stuck: none — MATCH 141/141 both standalone (match_one) AND byte-verified IN-TU (draft
//         substituted into the real src/ov_SC01_077/ov_SC01_077_after.c, full cpp+cc1+maspsx+as:
//         0 mismatched). Needs ONE byte-neutral decl fix the drafter may not touch:
//           tools/fix_arity_callers.py --apply --funcs func_8014F4C0 --binary ov_SC01_077 \
//                                      --drafts .run/drafts-t3-wave
//         (rewrites ov_SC01_077_after.c:1898 `extern s32 func_8014F4C0(void);` -> `(...)();`.
//          --binary is REQUIRED: the tool defaults to engine_core.h only, but this caller decl
//          lives in the overlay's own .c.) Without it the TU fails `conflicting types for
//          func_8014F4C0` — that lone error is the whole B3 gate gap; with it the TU compiles
//          clean and the bytes are identical.

/* func_8014F4C0 — the simpler twin of the already-banked DEFINE_func_8014F74C()
 * (src/shared/engine_core.h:25443). Same shape: build a PosT probe + a MoveT move vector from
 * the entity, call the collision query func_80133784, then splat one of three canned 8-byte
 * blobs into e+0x120 per the returned hit mask. Every idiom below (PosT/MoveT locals, the
 * x6/xA/xE forwarding temps, *(u8*)&w / (u32)w>>13, __builtin_memcpy for the byte-aligned
 * 8-byte blob copies) is lifted verbatim from that byte-proven sibling, and every extern uses
 * that sibling's canonical type — in particular `extern s16 D_801152B0;` (NOT `u8 D_801152B0[]`),
 * because DEFINE_func_8014F74C() is instantiated later in this same TU
 * (src/ov_SC01_077/ov_SC01_077_after.c:1973) and re-declares it at block scope.
 *
 * NOTE: func_8014F74C is called with NO argument — the asm has a bare `jal func_8014F74C; nop`
 * with no $a0 setup (it inherits the incoming $a0). Declared no-proto to stay compatible with
 * the DEFINE_func_8014F74C() def `int func_8014F74C(s32 arg0)` instantiated later in the TU.
 *
 * DEF-SIG / GATE NOTE: this TU already carries a file-scope `extern s32 func_8014F4C0(void);` at
 * ov_SC01_077_after.c:1898, written only so the inline-asm caller func_8014F468 has a name in
 * scope (its `jal` is inside __asm__, so the decl emits nothing and is byte-neutral). It
 * conflicts with this def's parameter. Return type is s32 and the param is s32 (promotion-safe),
 * so the §17a-3b no-proto rewrite `extern s32 func_8014F4C0();` (fix_arity_callers.py) resolves
 * it; deleting line 1898 outright is equally byte-neutral. */

#include "common.h"

#ifndef BFM_ENGINE_TYPES_H
typedef struct { s16 x, y, z, w; } PosT;
typedef struct { u16 x, y, z, w; } MoveT;
#endif

extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_80029178(s32 arg);
extern int func_8014F74C();
extern u8 D_800D3918[];
extern u8 D_801152A8[];
extern s16 D_801152B0;
extern s32 D_801152BC;

s32 func_8014F4C0(s32 arg0)
{
    PosT  sp10;
    MoveT sp18;
    u16 x6, xA, xE;
    s32 ret;

    if (*(s16 *)(arg0 + 0x146) != 0) {
        return func_8014F74C();
    }

    sp10.x = *(u16 *)(arg0 + 0x88);
    sp10.y = *(u16 *)(arg0 + 0x8A);
    sp10.z = *(u16 *)(arg0 + 0x8C);
    sp18.x = x6 = *(u16 *)(arg0 + 6);
    sp18.y = xA = *(u16 *)(arg0 + 0xA) + 8;
    sp18.z = xE = *(u16 *)(arg0 + 0xE);
    if (*(s16 *)(arg0 + 0x146) != 0) {
        sp18.x = x6 + *(u16 *)(arg0 + 0x140);
        sp18.y = xA + *(u16 *)(arg0 + 0x142);
        sp18.z = xE + *(u16 *)(arg0 + 0x144);
    }

    ret = func_80133784(0, &sp10, (s32)&sp18);
    if (ret != 0) {
        if (*(u8 *)&sp18.w != 0) {
            *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w;
        }
        *(u16 *)(arg0 + 0x16E) = (u32)sp18.w >> 13;
        if (ret == 0x2000) {
            __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_801152A8, 8);
        } else if (ret == 0x4000) {
            __builtin_memcpy((void *)(arg0 + 0x120), (void *)&D_801152B0, 8);
        }
        /* NOT the sibling's `if (x != 0x1D) return ret;` early-return form — that inverts the
         * branch polarity here (beq instead of the target's bne) and costs +2 ins. The
         * short-circuit && is what folds the 0x1D test and the func_80029178 test into the
         * single fallthrough chain the target uses. */
        if (*(u16 *)(arg0 + 0x16C) == 0x1D && (func_80029178(0x21) & 0xFF) == 0) {
            ret &= ~0x2000;
            ret |= 0x4000;
            __builtin_memcpy((void *)&D_801152B0, (void *)D_801152A8, 8);
            D_801152BC = 1;
        }
        return ret;
    }

    /* ret == 0 */
    __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_800D3918, 8);
    if (*(u8 *)&sp18.w != 0) {
        *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w;
    }
    return 0;
}
