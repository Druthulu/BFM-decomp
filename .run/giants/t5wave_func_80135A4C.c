// @class: schedule
// @stuck: none — MATCH (181 ins, relocation-masked; also rtu_match MATCH in ov_SC06_018_jr_8012ACE0)
//
// Load-bearing idioms (do NOT "clean up"):
//  * frame_pad[8]  -> the target frame is 0x58 with only s0-s7+ra saved; 32 B of dead
//    locals must be reserved (the TU's own `s32 frame_pad[2]; (void)&frame_pad;` idiom).
//  * `((s32(*)(void))func_80135480)()` -> the call passes NO args (the incoming $a0-$a3 are
//    still live at the jal); the TU's real 4-arg prototype would emit 4 arg moves.
//  * the goto/loop shape + `__asm__ __volatile__("")` between `p = *p` and its test ->
//    cross-jump barrier (§5a). gcc merges the two `lw p; test` blocks otherwise (-7 ins).
//    The barrier MUST sit immediately before the block's branch (a barrier at the TOP of the
//    block only truncates the backward walk in find_cross_jump and still merges).
//  * `*(s16 *)((*(u8 **)&D_80193B64) + 6)` for the f6 stores (NOT `->f6`) -> the cast makes
//    the MEM non-MEM_IN_STRUCT_P, so sched.c's output_dependence() ties the two D_801D3C5x
//    scalar stores AFTER them; `->f6` (in-struct + varying addr) lets them float up and the
//    D_801D3C58/54 pair steals the D_80193B64 load-delay slot (wrong schedule).
//  * `((V3 *)a2)->x` (COMPONENT_REF, in-struct) for the compare loads, NOT `((s16*)a2)[0]`
//    (`p[0]` folds to a plain `*p` -> not in-struct -> the load cannot hoist over the
//    D_801D3C5x stores).
//  * the `addu %0,%1,$zero` asm move -> gcc writes the store-flag straight into `t`; the
//    original keeps the uncoalesced `sltiu $v0` + `move $a0,$v0` (same idiom as the matched
//    sibling func_80133784 in this TU).
#include "common.h"

s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3) {
    typedef struct { u16 f0, f2, f4; s16 f6; } Box;
    typedef struct { s8 c[8]; } Blk8;
    typedef struct { s16 x, y, z; } V3;
    extern s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4);
    extern s32 func_80135EB0(s32 *p, s32 v);
    extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern u8 D_80193B64;
    extern u8 D_80193B68;
    extern s16 *D_80193B6C;
    extern s16 D_801D3C54;
    extern u16 D_801D3C58;
    extern s32 D_801D3C5C;
    extern s32 D_801D3C7C;
    extern u8 D_801152A8[];
    extern u8 D_801152B0;

    s32 *p;
    register s32 s7 __asm__("$23");
    s32 flag;
    s32 acc;
    s16 i;
    s32 eq;
    s32 ret;
    s32 frame_pad[8];
    (void)&frame_pad;

    switch (((s32 (*)(void))func_80135480)()) {
    case 0:
        return 0;
    case 1:
        s7 = a0 + 0x34;
        p = (s32 *)((a1 & 0xFFFFFFF) | 0x80000000);
        flag = 0;
        break;
    case 2:
        s7 = a0 + 0x34;
        p = (s32 *)((a1 & 0xFFFFFFF) | 0x80000000);
        flag = 1;
        break;
    case 3:
        s7 = a0 + 0x34;
        p = (s32 *)&D_801D3C7C;
        flag = 0;
        break;
    case 4:
        s7 = (s32)&D_801D3C5C;
        p = (s32 *)&D_801D3C7C;
        flag = 1;
        break;
    }

    acc = 0;
    if (a1 < 0) {
        if (func_80135EB0(p, -0x8000) == 0) {
            p = (s32 *)*p;
            if (p == 0) return 0;
        loop:
            if (func_80135EB0(p, -0x8000) == 0) goto next;
        }
    docall:
        func_80136A94(flag, a0, a3, s7);
        return 1;
    next:
        p = (s32 *)*p;
        __asm__ __volatile__("");
        if (p != 0) goto loop;
        return 0;
    }

    i = 0;
    *(s16 *)((*(u8 **)&D_80193B64) + 6) = -0x7FFF;
    *(s16 *)((*(u8 **)&D_80193B68) + 6) = 0x7FFF;
    D_801D3C58 = 0;
    D_801D3C54 = 0;
    {
        s32 t = 0;
        if (((V3 *)a2)->x == ((V3 *)a3)->x && ((V3 *)a2)->y == ((V3 *)a3)->y) {
            s32 zt = (((V3 *)a2)->z == ((V3 *)a3)->z);
            __asm__("addu %0,%1,$zero" : "=r"(t) : "r"(zt));
        }
        eq = t;
    }

    while (1) {
        ret = func_80133AB0(0, (s16)(*(Box **)&D_80193B64)->f0, (s16)(*(Box **)&D_80193B64)->f4, (s32)p);
        if (ret == 0) goto out;
        acc |= ret;
        if (eq != 0) goto out;
        {
            s16 old = i;
            i = i + 1;
            if (old >= 5) return 0;
        }
    }

out:
    if ((s16)acc != 0 || D_801D3C54 != 0) {
        if ((*(Box **)&D_80193B64)->f6 >= -0xBCB) {
            *(Blk8 *)D_801152A8 = *(Blk8 *)&D_801152B0;
        }
        (*(Box **)&D_80193B6C)->f0 = (*(Box **)&D_80193B68)->f0;
        (*(Box **)&D_80193B6C)->f2 = (*(Box **)&D_80193B68)->f2;
        (*(Box **)&D_80193B6C)->f4 = (*(Box **)&D_80193B68)->f4;
        goto docall;
    }
    return 0;
}
