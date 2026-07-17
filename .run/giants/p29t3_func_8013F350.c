// @class: regalloc-order
// @stuck: none — MATCH (490 ins, match_one, canonical-typed)
//
// func_8013F350 — 490-ins GIANT (menu/pad state machine, double jump table
// jtbl_801D8860 [8] + jtbl_801D8880 [5]). Load-bearing levers, do NOT "clean up":
//
//  1. `register s32 off __asm__("$4")` — THE crack. gcc otherwise emits pmax
//     before pcur, letting pcur sink into the beq delay slot (target has a nop
//     there) and losing the off/pmax coalesce into $a0. Pinning off cost 0 insns
//     and took the diff 162 -> 13. (`bb` shares $4; live ranges are disjoint.)
//  2. `register u16 *pd __asm__("$5")` + the "=r"/"0" self-barrier — without the
//     barrier gcc const-propagates &D_8011511C away and %lo-folds every access
//     (target holds the base: lhu 0($a1) / lhu 4($a1) / sh 4($a1)). The barrier
//     emits zero code; it only hides the pointer's constant value from cse.
//     NOTE: `ps` (&D_8011511A) must NOT get the same barrier — it regressed.
//  3. `case 0/2/3: break;` in the inner switch are NOT dead — 5 case nodes is
//     what pushes gcc past CASE_VALUES_THRESHOLD into a jump table (jtbl_801D8880)
//     instead of a compare chain (worth 18 instructions).
//  4. case 5 tests (flags & 0x10) with `!= 0 -> goto tail6`, case 6 with
//     `== 0 -> break`. The OPPOSITE polarity is what stops gcc cross-jumping the
//     two tails into one (§5a class, solved by source shape, not an asm barrier).
//  5. `if (d > 0) A; else if (d < 0) A;` — a single `d > 0 || d < 0` is folded to
//     `d != 0` by the FRONT END (andi 0xffff; beqz). Two ifs keep bgtz+bgez; gcc's
//     cross-jump then re-merges the twin store blocks, which is the target's shape.
//  6. 0x1000/0x8000/0x2000 blocks are written in-place (`pcur[0] = pcur[0] - 1`)
//     -> one register + a load-delay nop. The 0x4000 block needs the `b` temp
//     (its ==3 arm restores the original), so it keeps two registers and no nop.
//  7. `s16 d` (not s32 + <<16>>16): the wide form pushed the frame 0x30 -> 0x38.
//  8. `pad` is u16 (its andi 0xFFFF is real) but `st` must stay u16 AND be used
//     only for the pointer math / `st == 2` — the D_80115140 index re-reads
//     D_8011511A, which is what keeps st free of a masking andi.
//
// Canonical-reconciled (§17a-1) and re-verified MATCH: D_8011512E keeps the TU's
// `u16` canonical with `*(s16*)&` at the read sites (target needs lh), and
// func_8014168C keeps the canonical s16(s16) decl with s32(s32) call-site casts.
// Def sig is s32(void); engine_core.h canon is `void func_8013F350(void)` and the
// callers already cast (`((short (*)(void))func_8013F350)()`) -> def-side reconcile.

extern u16 D_80115110;
extern u16 D_8011511A;
extern u16 D_8011511C;
extern u16 D_8011511E;
extern u16 D_80115120;
extern u16 D_80115122;
extern s16 D_80115128;
extern s16 D_8011512A;
extern u16 D_8011512E;
extern u8  D_80115140[];
extern s16 D_8011514C;
extern s16 D_8011514E;
extern u8  D_80115152;
extern u16 D_80115158;
extern u16 D_8011515C;
extern u8  D_80187BB8[];
extern u8  D_80187BD0[];
extern u16 D_80187AD4[];

extern s32 func_80029178(s32 arg);
extern s32 func_800291B4(s32 arg);
extern s16 func_8014168C(s16 a0);
extern void func_8014AA04(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801415C0(s32 a0, s32 a1);
extern void func_80141C0C(s32 a0);
extern s32 func_80140608(s32 a0);
extern void func_801407F4(void);
extern s32 func_801416D4(s32 a0);

s32 func_8013F350(void) {
    register u16 *pd __asm__("$5") = &D_8011511C;
    u16 *ps;
    u16 *pf;
    u16 *pg;
    u16 pad;
    u16 st;
    u8 *pcur;
    u8 *pmax;
    u8 *p2e;
    u8 *p3e;
    register s32 off __asm__("$4");
    s16 i;
    s32 r;
    s16 rs;
    s16 d;
    u8 b;
    register u8 bb __asm__("$4");
    u8 m;
    s32 chg;

    __asm__ __volatile__("" : "=r"(pd) : "0"(pd));
    pad = *pd;
    chg = 0;
    if (pad != 0) {
        if (pad == pd[2]) {
            D_80115122 = D_80115122 - 1;
            if (D_80115122 == 0) {
                D_8011511E = pad & 0xF000;
                D_80115122 = 3;
            }
        } else {
            pd[2] = pad;
            D_80115122 = 6;
        }
    } else {
        D_80115120 = 0;
        D_80115122 = 0xC;
    }

    i = 0;
    do {
        if ((func_80029178(D_80187BB8[i]) & 0xFF) == 0) {
            break;
        }
        i = i + 1;
    } while (i < 6);
    D_80115158 = i | 0x100;

    switch (D_8011511A) { /* jtbl_801D8860 */
    case 0:
        r = ((s32 (*)(s32))func_8014168C)(0);
        rs = (s16)r;
        if ((func_80029178(D_80187BB8[rs]) & 0xFF) != 0 && (D_8011511E & 0x40) != 0) {
            func_8014AA04((r + 1) & 0xFF);
            if (rs != 0) {
                func_8002D4C8(0x461, 0);
            } else {
                func_8002D4C8(0x460, 0);
            }
        }
        break;
    case 1:
        if ((D_8011511E & 0x40) != 0) {
            D_80115128 = ((s32 (*)(s32))func_8014168C)(1) + 1;
            D_8011511A = 2;
            func_80141C0C(3);
            return 1;
        }
        if (D_80115128 != 4) {
            break;
        }
        goto tail7;
    case 2:
        switch (D_80115128) { /* jtbl_801D8880 */
        case 0:
            break;
        case 1:
            r = ((s32 (*)(s32))func_8014168C)(2);
            pf = &D_8011511E;
            if ((*pf & 0x40) != 0) {
                if ((*(s16 *)&D_8011512E) == 0) {
                    if ((func_800291B4(D_80187BD0[(s16)r]) & 0xFF) != 0 && (*pf & 0x40) != 0) {
                        D_8011511A = 5;
                        *(s16 *)&D_80115152 = 0;
                        func_80141C0C(3);
                        return 1;
                    }
                    func_80141C0C(5);
                } else {
                    func_801415C0((s16)r, (*(s16 *)&D_8011512E) & 0xF);
                    D_8011512E = 0;
                    func_80141C0C(3);
                    return 1;
                }
            } else if ((*pf & 0x20) != 0) {
                if ((*(s16 *)&D_8011512E) == 0) {
                    D_8011512E = r | 0x8000;
                } else {
                    func_801415C0((s16)r, (*(s16 *)&D_8011512E) & 0xF);
                    D_8011512E = 0;
                }
                func_80141C0C(3);
            }
            break;
        case 4:
            if ((D_8011511E & 0xA000) != 0) {
                chg = func_80140608(2);
            }
            func_801407F4();
            break;
        case 2:
            break;
        case 3:
            break;
        }
        if (D_80115128 != 0 && (D_8011511E & 0x10) != 0 && D_80115110 != 1) {
            D_8011511E = D_8011511E & 0xFFEF;
            D_8011511A = 1;
            D_8011512E = 0;
            func_80141C0C(6);
        }
        break;
    case 3:
        if (D_8011514E == 0 && (D_8011511E & 0x40) != 0) {
            D_8011511A = D_8011511A + 3;
            func_80141C0C(3);
            return 1;
        }
        break;
    case 5:
        if ((D_8011511E & 0x40) != 0) {
            rs = (s16)func_801416D4(D_80115152);
            if (rs != 0) {
                if (rs < 0) {
                    D_8011512A = 1;
                } else {
                    D_8011511A = D_8011511A - 3;
                    func_80141C0C(4);
                    return 1;
                }
            }
            break;
        }
        if ((D_8011511E & 0x10) != 0) {
            goto tail6;
        }
        break;
    case 6:
        if ((D_8011511E & 0x10) == 0) {
            break;
        }
    tail6:
        pg = &D_8011511E;
        *pg = *pg & 0xFFEF;
        D_8011511A = D_8011511A - 3;
        func_80141C0C(6);
        return 1;
    case 7:
        if ((D_8011511E & 0xA000) != 0) {
            chg = func_80140608(7);
        }
    tail7:
        func_801407F4();
        break;
    }

    ps = &D_8011511A;
    
    st = *ps;
    p2e = (u8 *)ps + 0x2E;
    p3e = (u8 *)ps + 0x3E;
    off = st << 1;
    pcur = p2e + off;
    pmax = p3e + off;
    if (st == 2 || 1 < pmax[0]) {
        if ((D_8011511E & 0x1000) != 0) {
            pcur[0] = pcur[0] - 1;
            chg = 1;
            if (0x7F < pcur[0]) {
                if (D_8011511A != 3) {
                    pcur[0] = pmax[0] - 1;
                } else {
                    pcur[0] = 0;
                    chg = 0;
                }
            }
        }
        if ((D_8011511E & 0x4000) != 0) {
            b = pcur[0];
            pcur[0] = b + 1;
            chg = 1;
            if (pmax[0] <= (u8)(b + 1)) {
                if (D_8011511A != 3) {
                    pcur[0] = 0;
                } else {
                    pcur[0] = b;
                    chg = 0;
                }
            }
        }
        if (D_8011511A == 2 && D_80115128 == 1) {
            if ((D_8011511E & 0x8000) != 0) {
                pcur[1] = pcur[1] - 1;
                chg = 1;
                if (0x7F < pcur[1]) {
                    pcur[1] = pmax[1] - 1;
                }
            }
            if ((D_8011511E & 0x2000) != 0) {
                pcur[1] = pcur[1] + 1;
                chg = 1;
                if (pmax[1] <= pcur[1]) {
                    pcur[1] = 0;
                }
            }
        } else {
            bb = pcur[0];
            m = D_80115140[D_8011511A];
            d = (s8)bb - (s8)m;
            if (d > 0) {
                D_80115140[D_8011511A] = bb;
            } else if (d < 0) {
                D_80115140[D_8011511A] = bb;
            }
        }
        if (D_8011511A == 1) {
            D_80115128 = ((s32 (*)(s32))func_8014168C)(1) + 1;
            if ((D_8011511E & 0x5000) != 0) {
                D_8011514C = 0;
            }
        }
        D_8011515C = D_80187AD4[D_80115128];
        if ((chg << 0x10) != 0) {
            func_80141C0C(1);
        }
    }
    return 0;
}
