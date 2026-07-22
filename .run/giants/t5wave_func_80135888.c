// @class: regalloc-order
// @stuck: none -- MATCH (113 ins, relocation-masked)
//
// Levers used (all byte-gated by match_one):
//  * frame 0x50: an unused BLKmode local (s32 pad_[8]) reserves the 32 bytes of
//    locals the original frame carries (cookbook "reserved local sets the frame size",
//    here confirmed at -O2 as well as -O0).
//  * register pins $17/$18/$19/$20/$21 fix the callee-saved allocation order
//    (arg0->$s3, arg1->$s1, mode->$s2, base->$s4, arg3->$s5).
//  * register s32 m __asm__("$2") keeps the AND result alive in $v0 across the
//    lui of 0x80000000, which forces that constant into $v1 (local-alloc otherwise
//    allocates the shorter-lived constant first and takes $v0).
//  * the success tail (func_80136A94 + return 1) is written out at BOTH the peeled
//    call site and inside the loop; gcc cross-jumps them into the single tail with
//    the two entry points .L80135984 / .L80135988 the target has, and keeps the
//    loop copy (so the loop test is beqz-fallthrough, not bnez).
//  * __asm__ __volatile__("") between the peeled "sp = *sp" and the while-guard is a
//    CROSS-JUMP barrier (jump.c find_cross_jump compares insn streams backwards):
//    without it gcc merges the peeled advance+guard block into the loop's advance
//    block and the peel disappears (113 -> 110 ins).
#include "common.h"

extern s32 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
extern s32 func_80135EB0(s32 a0, s32 a1);
extern int func_80134A74(int, s16, s16, int);
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);

extern u16 *D_80193B64;
extern u16 *D_80193B68;
extern s16 *D_80193B70;
extern s32 D_801D3C5C;
extern s32 D_801D3C7C;

s32 func_80135888(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 pad_[8];
    register s32 m __asm__("$2");
    s32 sp;
    register s32 p1   __asm__("$17");
    register s32 mode __asm__("$18");
    register s32 p0   __asm__("$19");
    register s32 base __asm__("$20");
    register s32 p3   __asm__("$21");

    p0 = arg0;
    p1 = arg1;
    p3 = arg3;

    switch (func_80135480((void *)arg0, arg1, (s16 *)arg2, (s16 *)arg3)) {
    case 0:
        return 0;
    case 1:
        base = p0 + 0x34;
        m = p1 & 0xFFFFFFF;
        sp = m | 0x80000000;
        mode = 0;
        break;
    case 2:
        base = p0 + 0x34;
        m = p1 & 0xFFFFFFF;
        sp = m | 0x80000000;
        mode = 1;
        break;
    case 3:
        base = p0 + 0x34;
        sp = (s32)&D_801D3C7C;
        mode = 0;
        break;
    case 4:
        base = (s32)&D_801D3C5C;
        sp = (s32)&D_801D3C7C;
        mode = 1;
        break;
    }

    if (p1 < 0) {
        if (func_80135EB0(sp, 0) != 0) {
            func_80136A94(mode, p0, p3, base);
            return 1;
        }
        sp = *(s32 *)sp;
        __asm__ __volatile__("");
        while (sp != 0) {
            if (func_80135EB0(sp, 0) != 0) {
hit:
                func_80136A94(mode, p0, p3, base);
                return 1;
            }
            sp = *(s32 *)sp;
        }
        return 0;
    }
    {
        u16 *pb = D_80193B68;
        u16 *pa = D_80193B64;
        s16 *pc = D_80193B70;
        pc[0] = pb[0] - pa[0];
        pc[1] = pb[1] - pa[1];
        pc[2] = pb[2] - pa[2];
        if (func_80134A74(0, (s16)pa[0], (s16)pa[2], sp) == 0) {
            return 0;
        }
    }
    goto hit;
}
