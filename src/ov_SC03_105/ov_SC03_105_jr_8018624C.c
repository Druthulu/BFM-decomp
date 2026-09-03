#include "common.h"
#include "../shared/engine_core.h"

/* ==== S74 overlay split (cookbook §426/§431) ================================
 * Split out of ov_SC03_105_jr_8017C8D0.c at vram 0x8018624C (file offset 0x5E0F4).
 * Reason: that ONE code subseg owned raw gcc switch jump tables in TWO
 * non-adjacent .rodata spans of the data tail —
 *   span 1  0x801B814C-0x801B822C  (func_801806F8, func_80180ABC, func_80180EC0,
 *                                   func_801813BC, func_801818E8, func_80181C84)
 *   span 2  0x801B8240-0x801B8290  (func_8018624C, func_801867D0)
 * A compiled object contributes exactly ONE contiguous .rodata run, so only one
 * span could ever carve and the other span's owners were unbankable at any effort
 * (jtbl_carve.py fails loud on it). This cut puts all six span-1 owners below the
 * boundary and both span-2 owners at/above it, so each piece carves its own span.
 * Contents are VERBATIM from the parent TU; only the INCLUDE_ASM subseg path changed. */

#include "common.h"

extern s32 rand(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A568(void (*a0)(void));
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C51C(void *a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8013C9C4(void *a0);
extern s32 func_80147054(void *a0);
extern s32 func_801789AC(s32 a0);
extern void func_80178D18(void);
extern void func_8017BF08(void *a0, void *a1, s32 a2, s32 a3);
extern void func_8017E08C(u8 *a0);
extern void func_801870B4(void);
extern void func_801871C0(void *a0, s32 a1, s32 a2);
extern void func_801873C8(void);
extern void func_80187434(void *a0);

extern u8 D_800AF630[];
extern s32 D_80126B58;
extern u8 D_8018EDF4[];
extern s16 D_8018EE00;
extern u8 D_8018EE54[];
extern u8 D_8018EE5C;
extern u8 D_801B1DC8[];
extern u8 D_801B2410[];

/* func_8018624C — MATCH (269 ins). State machine on *(u16 *)(ent+0x34), dispatched
 * through jtbl_801B8240 (14 dense entries 0..13; the empty arms are what keeps the
 * table's minval at 0, i.e. `sll $v0,$v1,2` with NO `addiu -N` bias).
 *
 * THREE LOAD-BEARING DIALS — do not "simplify" any of them:
 *
 * 1. `tbl = D_800AF630;` hoisted to the top. The four guards read the same halfword at
 *    +0xA3AA (= D_800B99DA); off a held base pointer that expands to the far-offset form
 *    `lui $at,1 / addu $at,$s6,$at / lhu -0x5C56($at)` (the resident single-base idiom,
 *    cf. src/ov_SC03_105/ov_SC03_105_jr_8017C8D0.c func_80182DCC note #2).
 *
 * 2. `t2 = tmp;` — a DEAD CHAINED COPY, and it is the whole crack (cookbook §193-F /
 *    §148-A, the `move_movables` threshold staircase). The inner loop has three
 *    invariants: the /3 magic 0x55555556, the OR mask -0x8000, and `&D_8018EE54`, and
 *    `move_movables` admits each iff `threshold * savings * lifetime >= insn_count` with
 *    threshold 29 (loop_has_call) decaying -3 per move. All three are life 1 / savings 1,
 *    so the ranks test 29, 26, 23. The target hoists only the first two and recomputes
 *    `la $a0,%hi/%lo(D_8018EE54)` INSIDE the loop, i.e. rank 3 must fail: insn_count >= 24.
 *    Measured with `cc1 -dL`: plain body = 22 real insns (all three hoist, +1 callee-saved
 *    register = frame 0x38 with NINE saves and 271 ins). Routing the func_8012C51C return
 *    through the multiply-set `tmp` buys +1 (23, still hoists), and the second dead copy
 *    into the multiply-set `t2` buys the +1 that reaches 24 -> "not desirable" -> $s7 is
 *    never allocated and the count lands on 269. Both copies are deleted by flow (they run
 *    before it), so they cost ZERO instructions. Collapsing either one re-hoists the symbol.
 *
 * 3. `s32 pad[2];` — dead-local frame pad (§162i1): vars=8 turns frame 0x30 into 0x38.
 *    Same device as the sibling state machine func_80186DDC in this overlay.
 *
 * Init order `j = 0;` BEFORE `off = 0;` is also load-bearing: it is what emits
 * `addu $s1,$zero,$zero` ahead of `addu $s0,$zero,$zero` at the outer-loop top.
 */
void func_8018624C(void *arg0) {
    s32 ent;
    u8 *tbl;
    s32 i;
    s32 j;
    s32 off;
    s32 tmp;
    s32 t2;
    s16 *p;
    s32 pad[2];

    ent = (s32)arg0;
    tbl = D_800AF630;
    switch (*(u16 *)(ent + 0x34)) {
    case 0:
    case 2:
    case 6:
    case 8:
    case 10:
    case 12:
        break;
    case 1:
        if ((*(u16 *)(tbl + 0xA3AA) & 3) == 0) {
            func_8013C9C4(D_8018EDF4);
            func_801871C0((void *)ent, 1, 1);
        }
        break;
    case 3:
        func_8012A828(ent, D_801B1DC8);
        func_8012A828(*(s32 *)(ent + 0x6C), D_801B2410);
        ((void (*)(s32))func_801873C8)(ent);
        *(u16 *)(ent + 0x34) += 1;
        /* fallthrough */
    case 4:
        if ((u32)*(s32 *)(ent + 0x94) < 0x2C && (*(u16 *)(tbl + 0xA3AA) & 3) == 0) {
            func_8013C9C4(D_8018EDF4);
            func_801871C0((void *)ent, 1, 1);
        }
        if (*(s32 *)(ent + 0x94) == 0x2B) {
            for (i = 0; i < 3; i++) {
                j = 0;
                off = 0;
                for (; j < 3; j++) {
                    *(u16 *)(&D_8018EE5C + off) = (rand() % 3 + 1) | -0x8000;
                    tmp = func_8012C51C(D_8018EE54 + off, ent);
                    t2 = tmp;
                    off += 0x14;
                }
            }
            func_801871C0((void *)ent, 0xA, 5);
            func_80187434((void *)ent);
            func_8002D4C8(0x726, 0);
            func_8002D4C8(4, 0x79F);
        }
        if (*(s32 *)(ent + 0x94) == 0x4B) {
            func_8002D4C8(0x727, 0);
        }
        if (*(s32 *)(ent + 0x94) == 0x84) {
            func_8002D4C8(0xC05, 0);
        }
        if (*(s32 *)(ent + 0x94) == 0x5A) {
            func_801871C0((void *)ent, 0xF, 5);
        }
        if (*(s32 *)(ent + 0x94) > 0x78 && (*(u16 *)(tbl + 0xA3AA) & 0xF) == 0) {
            t2 = rand();
            func_801871C0((void *)ent, t2 % 5 + 1, 2);
        }
        break;
    case 5:
        *(s32 *)(ent + 0x1C) = 0x1E;
        *(u16 *)(ent + 0x34) += 1;
        func_8002D4C8(0x72D, 0);
        break;
    case 7:
        func_8012A568((void (*)(void))func_8017E08C);
        *(u16 *)(*(s32 *)(ent + 0xD0) + 0x34) += 1;
        func_8002D4C8(4, 0x733);
        *(u16 *)(ent + 0x34) += 1;
        break;
    case 9:
        tmp = func_8012C658(0x14B, 0, ent);
        *(s32 *)(ent + 0xCC) = tmp;
        func_8012C588(0x3BD, tmp);
        *(u16 *)(ent + 0x34) += 1;
        func_8002D4C8(0x72F, 0);
        break;
    case 11:
        *(u16 *)(ent + 0x34) += 1;
        func_801870B4();
        break;
    case 13:
        p = &D_8018EE00;
        func_8017BF08(p, p + 1, 2, 0x96);
        *(u16 *)(ent + 0x34) += 1;
        break;
    }
    if (*(u16 *)(ent + 0x34) >= 5 && (*(u16 *)(tbl + 0xA3AA) & 0x7F) == 0) {
        func_801871C0((void *)ent, 5, 5);
    }
    if (func_801789AC(ent) == 1) {
        ((void (*)(s32))func_80178D18)(ent);
        *(s16 *)(ent + 0x2) = 3;
        *(s16 *)(*(s32 *)(ent + 0xCC) + 0x2) = 2;
        *(s32 *)(ent + 0x1C) = 0x5A;
        func_80147054(&D_80126B58);
        func_8002D4C8(4, 0x72F);
    }
}


#include "common.h"

extern s32 rand(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_801871C0(void *a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void (*D_8018E8E4[])(void);
extern void (*D_8018E9CC[])(void);

void func_80186680(s32 a0)
{
    s32 v0;

    if ((rand() & 0xFF) == 0) {
        func_801871C0((void *)a0, rand() % 5 + 1, 2);
    }

    if (func_8012BEE8(a0) != 0) {
        if ((rand() & 1) == 0) {
            func_8012A828(a0, D_8018E8E4);
            v0 = *(s32 *)(a0 + 0x6C);
            func_8012A828(v0, D_8018E9CC);
            *(s32 *)(a0 + 0x1C) = 0x72;
            func_801871C0((void *)a0, 7, 3);
            func_8002D4C8(0x728, 0);
        } else {
            *(s32 *)(a0 + 0x1C) = 0x5A;
        }
    }
}


extern void func_8012A828(s32 arg0, void *arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_801B2A58[];
extern u8 D_801B2C40[];

void func_8018676C(s32 a0) {
    s32 s0;

    s0 = a0;
    func_8012A828(a0, D_801B2A58);
    func_8012A828(*(s32 *)(s0 + 0x6C), D_801B2C40);
    func_8012C658(0x222, 0x8000, s0);
    *(s16 *)(s0 + 0x2) = 5;
    *(s16 *)(s0 + 0x34) = 0;
    *(s32 *)(s0 + 0x1C) = 0;
}


#include "common.h"

/* §379/§30 — the `+= 1` on 0x34 must be a COMPONENT_REF (MEM_IN_STRUCT_P `/s`) so
 * sched1 may hoist the fixed-address D_801BCBBC load above the varying-address
 * `sh 0x34($s0)` store.  A plain `*(u16 *)(s0 + 0x34)` cast denies `/s`, the
 * true_dependence drop clause never fires, and the block costs two load-delay
 * nops (the whole function's LENGTH-DRIFT/2). */
struct Ctr34 {
    u16 h;
};

extern void func_8013C9C4(void *a0);
extern void func_801871C0(void *a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012E544(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80187434(void *a0);
extern void func_801870B4(void);
extern s32 func_8012BEE8(s32 a0);
extern s32 D_801BCBBC;
extern u8 D_8018EDF4[];
extern u8 D_8018AAA4[];
extern u8 D_801B2E28[];
extern u8 D_801B2FC0[];
extern u8 D_8018EACC[];
extern u8 D_8018EC24[];
extern u8 D_8018E9BC[];
extern u8 D_8018EAA4[];

void func_801867D0(s32 a0)
{
    s32 s0 = a0;
    s32 v0;

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        if (*(u32 *)(s0 + 0x94) < 0x1F && (*(s32 *)(s0 + 0x1C) & 3) == 0) {
            func_8013C9C4(D_8018EDF4);
            func_801871C0((void *)s0, 2, 2);
        }
        if (*(s32 *)(s0 + 0x94) == 0x13) {
            func_8002D4C8(0xBC2, 0);
        }
        if (*(s32 *)(s0 + 0x94) == 0x24) {
            func_8002D4C8(0xBC3, 0);
        }
        if (*(s32 *)(s0 + 0x94) == 0x32) {
            func_8013C9C4(D_8018AAA4);
            func_801871C0((void *)s0, 10, 5);
        }
        if (func_8012E544(0x222) == 0) {
            func_8012A828(s0, D_801B2E28);
            func_8012A828(*(s32 *)(s0 + 0x6C), D_801B2FC0);
            ((struct Ctr34 *)(s0 + 0x34))->h = ((struct Ctr34 *)(s0 + 0x34))->h + 1;
            D_801BCBBC = D_801BCBBC + 1;
            return;
        }
        *(s32 *)(s0 + 0x1C) = *(s32 *)(s0 + 0x1C) + 1;
        if (*(s32 *)(s0 + 0x1C) >= 0x12C) {
            v0 = func_8012E544(0x222);
            if (v0 != 0) {
                *(s16 *)(v0 + 0x100) = 1;
            }
            func_8012A828(s0, D_8018EACC);
            func_8012A828(*(s32 *)(s0 + 0x6C), D_8018EC24);
            *(u16 *)(s0 + 0x34) = 2;
        }
        return;
    case 1:
        if (*(s32 *)(s0 + 0x94) == 0x14) {
            func_8013C9C4(D_8018AAA4);
            func_801871C0((void *)s0, 10, 5);
            func_80187434((void *)s0);
            func_8002D4C8(0xC8F, 0);
        }
        if (*(s16 *)(s0 + 0x98) != 0) {
            return;
        }
        if (D_801BCBBC < 3) {
            *(s16 *)(s0 + 2) = 6;
        } else {
            *(s16 *)(s0 + 2) = 8;
        }
        return;
    case 2:
        if (*(s16 *)(s0 + 0x98) != 0) {
            return;
        }
        func_8012A828(s0, D_8018E9BC);
        func_8012A828(*(s32 *)(s0 + 0x6C), D_8018EAA4);
        *(s16 *)(*(s32 *)(s0 + 0xCC) + 2) = 1;
        func_8002D4C8(0x72F, 0);
        *(s32 *)(s0 + 0x1C) = 0xA0;
        *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        return;
    case 3:
        if (*(s32 *)(s0 + 0x1C) == 0x64) {
            *(s32 *)(*(s32 *)(*(s32 *)(s0 + 0xCC) + 0x20) + 4) &= 0x7FFFFFFF;
            func_801870B4();
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        /* fall through */
    case 4:
        if (func_8012BEE8(s0) != 0) {
            *(s16 *)(s0 + 2) = 3;
            *(s16 *)(*(s32 *)(s0 + 0xCC) + 2) = 2;
            *(s32 *)(s0 + 0x1C) = 0x5A;
            func_8002D4C8(4, 0x72F);
        }
        break;
    }
}



extern s32 func_80178B18(s32, s32);

void func_80186AE8(void *arg0) {

    extern M2C_UNK D_8018EFBC;
    ((void (*)(void *, void *))func_80178B18)(arg0, &D_8018EFBC);
    *(s16 *)((s32)arg0 + 0x2) = 0x7;
    *(s16 *)((s32)arg0 + 0x34) = 0;
}
