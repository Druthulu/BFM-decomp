// @class: other
// @stuck: none — MATCH
/* func_80135260 — hit-test dispatcher (136 ins, ov_SC06_018 jr_8012ACE0, class WAVE).
 *
 * Shape: switch on func_80135480()'s mode (jtbl_801D2A48, 5 entries; case 0 == "return 0",
 * default == fall through with the three switch-set locals UNINITIALISED -> that is why
 * $s0/$s2/$s4 are live-in to .L8013531C with no dominating def).
 *
 * Three residuals had to be steered:
 *  1) FRAME. Target frame is 0x68 with the 7 saves at 0x48..0x60 => 0x10 outgoing-arg bytes plus
 *     56 bytes of locals that the body never touches. gcc-2.7.2 still reserves stack for declared
 *     aggregates whose stores are all dead, so a 56-byte unreferenced array (`pad[14]`) reproduces
 *     the frame exactly. (Almost certainly a leftover MATRIX+VECTOR+SVECTOR trio in the original.)
 *  2) CFG / cross-jumping. The pre-loop func_80135EB0(p,0) test and the in-loop one are the same
 *     call with the same args; every structured rendering (do/while, while, or an inline duplicate
 *     of the func_80136A94 tail) lets gcc's cross-jump collapse them into ONE call site with a
 *     back-edge, losing 10 instructions. The target keeps two call sites AND places the
 *     func_80136A94 block (.L8013535C) as the *fallthrough* of the loop's `beqz $v0` — i.e. the
 *     shared tail lives INSIDE the loop and the three other reachers branch to it. Only an explicit
 *     goto CFG (loop:/hit:/cont:) reproduces that: the two call blocks then end in different
 *     jumps (`bnez -> hit` vs `beqz -> cont`) so find_cross_jump refuses to merge them.
 *  3) The 2nd compare block. `(s16)D_80193B68[0]` must REUSE the lhu already loaded for the
 *     0xFF80 compare (target: `sll/sra $a1,16`), not re-load with `lh`. Hoisting it into a local
 *     (`s32 t = q68[0];`) forces the reuse and also fixes the $v0/$v1 operand order of the `bne`.
 *
 * func_80135480 is deliberately called with NO declaration: it is defined later in this TU
 * returning s16, and the target does no sign-extension of the switch value — the implicit `int`
 * declaration is what the original had.
 *
 * VERIFIED: tools/match_one.py func_80135260 --asm-subdir
 *           asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8012ACE0  ->  MATCH (136 ins).
 */
#include "common.h"

s32 func_80135260(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {
    extern u16 *D_80193B64;
    extern u16 *D_80193B68;
    extern s16 *D_80193B70;
    extern s32 D_801D3C5C;
    extern s32 D_801D3C7C;
    extern s32 func_80134A74(s32, s32, s32, s32);
    extern s32 func_80135EB0(s32 *, s32);
    extern s32 func_80136A94(s32, s32, s32, s32);

    s32 pad[14];
    s32 *p;
    s32 mode;
    s32 mtx;

    switch (func_80135480(param_1, param_2, param_3, param_4)) {
    case 0:
        return 0;
    case 1:
        mtx = param_1 + 0x34;
        p = (s32 *)((param_2 & 0xFFFFFFF) | 0x80000000);
        mode = 0;
        break;
    case 2:
        mtx = param_1 + 0x34;
        p = (s32 *)((param_2 & 0xFFFFFFF) | 0x80000000);
        mode = 1;
        break;
    case 3:
        mtx = param_1 + 0x34;
        p = &D_801D3C7C;
        mode = 0;
        break;
    case 4:
        mtx = (s32)&D_801D3C5C;
        p = &D_801D3C7C;
        mode = 1;
        break;
    }

    if (param_2 < 0) {
        if (func_80135EB0(p, 0) != 0) {
            goto hit;
        }
        p = (s32 *)*p;
        if (p == 0) {
            return 0;
        }
    loop:
        if (func_80135EB0(p, 0) == 0) {
            goto cont;
        }
    hit:
        func_80136A94(mode, param_1, param_4, mtx);
        return 1;
    cont:
        p = (s32 *)*p;
        if (p != 0) {
            goto loop;
        }
        return 0;
    } else {
        u16 *p68 = D_80193B68;
        u16 *p64 = D_80193B64;
        s16 *p70 = D_80193B70;
        p70[0] = p68[0] - p64[0];
        p70[1] = p68[1] - p64[1];
        p70[2] = p68[2] - p64[2];
        if (func_80134A74(0, (s16)p64[0], (s16)p64[2], (s32)p) != 0) {
            goto hit;
        }
        {
            u16 *q64 = D_80193B64;
            u16 *q68 = D_80193B68;
            s32 t = q68[0];
            if (((q64[0] & 0xFF80) == (t & 0xFF80)) &&
                ((q64[2] & 0xFF80) == (q68[2] & 0xFF80))) {
                return 0;
            }
            if (func_80134A74(0, (s16)t, (s16)q68[2], (s32)p) != 0) {
                goto hit;
            }
        }
        return 0;
    }
}
