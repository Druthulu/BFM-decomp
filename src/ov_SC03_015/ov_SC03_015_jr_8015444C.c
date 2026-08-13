#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
DEFINE_func_8015444C()  /* dedup: shared engine-core @0x8015444C (src/shared) */




/*
 * func_801549F8 — scan param->b4[] (s32[], length = the u8 at param->bc),
 * stepping the index by 1 or 2 per entry via the 27-entry jump table
 * jtbl_801D89A4; count the default/out-of-range entries. Returns (u8) count.
 *
 * REDRAFT NOTE (the decay fix, 2 levers — both required, both source-level):
 *
 *  1. `u8 n` (NOT `s32 n`) — THE fix for the stored draft's 3-off residual.
 *     The stored draft's whole residual was the position of the loop-bound
 *     keep-alive copy `addu $a3,$v0,$zero` among the three preheader insns:
 *     draft emitted [lw base][copy][lui/addiu jtbl], target wants
 *     [lw base][lui/addiu jtbl][copy].  The loop-invariant jtbl address is
 *     moved by loop.c and lands AFTER every preheader source statement, so as
 *     long as the copy is an ordinary preheader statement it can never follow
 *     the hoist.  Making `n` a u8 changes the RTL for `n = *(u8*)(p+0xBC)`:
 *     cse1 no longer converts it into a plain reg-reg copy in place, and the
 *     copy that ultimately feeds the exit test is emitted at loop_start AFTER
 *     move_movables (post-loop pass), i.e. after the hoisted lui/addiu — the
 *     target order.  Nothing else in the function changes.
 *
 *  2. The `j = i` / `i = j + k` index form BLOCKS strength reduction, which
 *     is what the stored draft's `register s32 i __asm__("$3")` pin was for.
 *     Unblocked, -O2 turns base[i] into a walking pointer (2nd biv, 33 ins);
 *     the target keeps the INDEX form (sll $v0,$v1,2; addu $v0,$v0,$a0; lw).
 *     `j` is a mult=1/add=0 giv of the biv `i`, so SR declines and i/j get
 *     coalesced into $v1 — no extra insn.  This replaces the hard-register
 *     pin, so the match is pin-free and safe to travel to sibling overlays.
 *     (The pinned form — keep `register s32 i __asm__("$3")` + `i += 1/2` and
 *     just change `n` to u8 — also MATCHes, 31 ins, if a pin is ever wanted.)
 *
 * OPT LEVEL: plain -O2.  The unfilled load-delay nops are this psx gcc's
 * default, not an -O1 tell.
 *
 * VERIFIED: python3 tools/match_one.py func_801549F8 --c .run/uc/func_801549F8.c
 *           --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8015444C
 *           -> MATCH (31 ins)
 */
s32 func_801549F8(s32 param_1, s32 _arg1, s32 _arg2)
{
    s32 i, j;
    u8 n;
    u8 count;
    s32 *base;

    count = 0;
    i = 0;
    if (*(u8 *)(param_1 + 0xBC) != 0) {
        base = *(s32 **)(param_1 + 0xB4);
        n = *(u8 *)(param_1 + 0xBC);
        do {
            j = i;
            switch (base[j]) {
            case 0:  case 2:  case 7:  case 8:  case 9:  case 10:
            case 0xd: case 0x10: case 0x11: case 0x12: case 0x13:
            case 0x14: case 0x19: case 0x1a:
                i = j + 1;
                break;
            case 3: case 4: case 5: case 6: case 0xb: case 0xc:
            case 0xe: case 0xf: case 0x15: case 0x16:
                i = j + 2;
                break;
            default:
                i = j + 1;
                count += 1;
                break;
            }
        } while (i != n);
    }
    return count;
}

DEFINE_func_80154A74()  /* dedup: shared engine-core @0x80154A74 (src/shared) */

DEFINE_func_80154AB4()  /* dedup: shared engine-core @0x80154AB4 (src/shared) */

DEFINE_func_80154AE0()  /* dedup: shared engine-core @0x80154AE0 (src/shared) */

DEFINE_func_80154B20()  /* dedup: shared engine-core @0x80154B20 (src/shared) */

DEFINE_func_80154B4C()  /* dedup: shared engine-core @0x80154B4C (src/shared) */

DEFINE_func_80154B7C()  /* dedup: shared engine-core @0x80154B7C (src/shared) */

DEFINE_func_80154B98()  /* dedup: shared engine-core @0x80154B98 (src/shared) */

DEFINE_func_80154BC8()  /* dedup: shared engine-core @0x80154BC8 (src/shared) */

DEFINE_func_80154BE4()  /* dedup: shared engine-core @0x80154BE4 (src/shared) */
