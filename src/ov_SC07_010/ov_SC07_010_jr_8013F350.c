#include "common.h"
#include "../shared/engine_prelude.h"

extern void guess_ZeroMemory(void *a0, s32 a1);
extern void func_8013C98C(void);
extern void guess_StartPadVibration(void *a0);
extern void func_8013C9C4(void * arg0);
extern void func_8013CA14(void);
extern void func_8013CABC(void);
extern void func_8013CAE8(void);
extern void func_8013CB20(void);
extern void func_8013CB5C(void);
extern s16 currentLocationId;
extern void func_8013DBE4(int param_1);
extern void func_8013D9B0(int param_1);
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);
extern void func_8013CB84(void);
extern void func_8013CF68();
extern void func_8013D064(void);
extern s32 func_8013D13C(void);
extern void func_8013D164(void);
extern void func_8013D53C(void *arg0v);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013D3D4(int param_1, int param_2);
extern void func_800599B8(s32 a0, s32 a1);
extern void func_8013D9B0(int param_1);
extern void func_8013DBE4(int param_1);
extern s32 func_8013E054(void);
extern int SquareRoot12(int a0);
extern int func_8013E064(s16 *a0, s16 *a1);
extern int func_8013E0FC(s16 *a0, s16 *a1);
extern int func_8013E194(s16 *a0, s16 *a1);
extern void Square12(s32 *a0, s32 *a1);
extern s32 func_8013E22C(VecA *a0, struct VecB *a1);
extern s16 D_80126CB0;
extern s32 func_8013E298(s16 *a0);
extern s16 D_80126CAC;
extern short D_80126CAE;
extern int func_8013E2C4(short *a0);
extern void *D_801274CC;
extern s32 func_8013E410(void);
extern s32 func_8013E448(s32 a0);
extern void func_8012C724(s32 a0, s32 a1);
extern void func_8013E370(void);
extern u8 guess_g_ObjectTable[]; // Names ledger: config/names.tsv guess_g_ObjectTable
extern s32 (*D_801274D0)(s32);
extern s32 D_801274D8;
extern s32 D_801274DC;
extern s32 func_800132BC(s32 a0, s32 a1);
extern s32 func_8013E448(s32 param_1);
extern void func_800D24A0(s32 a0);
extern void func_80141788(void);
extern void *D_8011DB24;
extern void func_8013E558(void);
extern s32 func_800D0EC4(void);
extern void func_80141874(void);
extern u8 D_800B9A15;
extern unsigned char guess_g_ActiveMenu; // Names ledger: config/names.tsv guess_g_ActiveMenu
extern u16 guess_g_OpenMenuId; // Names ledger: config/names.tsv guess_g_OpenMenuId
extern unsigned short guess_g_MenuStep; // Names ledger: config/names.tsv guess_g_MenuStep
extern void func_8013E588(void * _arg0);
extern void func_80029444(void);
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
extern void func_80141C04(void);
extern void func_8013E5E8(void);
extern void func_8013E67C(void);
extern void func_8013E83C(void);
extern s32 guess_GetStoryProgress(void);
extern void func_8013E6AC(void);
extern void func_800D24A0(s32 arg);
extern void func_8013E814(void);
extern void func_8013E83C();
extern void func_8013E958();
extern s32 func_80141C50(void);
extern void func_8013F244(void);
extern void func_8013FAF8(s16 a0, s16 a1);
extern void func_80137B80(void);
extern void func_8013E958(void);
extern void guess_RequestSound(s32 a0, s32 a1);
extern short guess_g_DoubleBufferIndex; // Names ledger: config/names.tsv guess_g_DoubleBufferIndex
extern u8 guess_g_MenuPacketBases[]; // Names ledger: config/names.tsv guess_g_MenuPacketBases
extern s32 guess_g_MenuPacketPtr; // Names ledger: config/names.tsv guess_g_MenuPacketPtr
extern u16 guess_g_MenuPanel; // Names ledger: config/names.tsv guess_g_MenuPanel
extern u16 guess_g_MenuPadPressed; // Names ledger: config/names.tsv guess_g_MenuPadPressed
extern s32 guess_g_MenuHelpText; // Names ledger: config/names.tsv guess_g_MenuHelpText
extern s16 D_8011514C;
extern void func_8013EA54(void);
extern s32 func_8013F350(void);   /* §30#2 widened: def returns live $v0; callers discard */
extern s16 guess_GetMenuPanelCursorIndex(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern void guess_CloseTextWindow0(void);
extern s32 guess_OpenTextWindowCenteredAt(int a0, int a1);
extern unsigned char *guess_GetStoryGoalText(void);
extern void func_8013EB7C(void);
extern s32 func_8013F350(void); /* §30#2 widened (discarding caller) */
extern u16 guess_g_MenuStep; // Names ledger: config/names.tsv guess_g_MenuStep
extern void func_8013ED6C(void);
extern s32 func_8013EE10();
extern s32  func_800D0488(s16 a0);
extern void func_800D2624(void);
extern void func_8013EF88(void);
extern void func_8013F138(void);
extern unsigned short D_80115114;
extern unsigned short guess_g_MenuTransitionTimer; // Names ledger: config/names.tsv guess_g_MenuTransitionTimer
extern void func_8013F1BC(void);
extern void func_80141C0C(s32);


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
//     barrier gcc const-propagates &guess_g_MenuPadHeld away and %lo-folds every access
//     (target holds the base: lhu 0($a1) / lhu 4($a1) / sh 4($a1)). The barrier
//     emits zero code; it only hides the pointer's constant value from cse.
//     NOTE: `ps` (&guess_g_MenuPanel) must NOT get the same barrier — it regressed.
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
//     only for the pointer math / `st == 2` — the guess_g_MenuPanelScrollTops index re-reads
//     guess_g_MenuPanel, which is what keeps st free of a masking andi.
//
// Canonical-reconciled (§17a-1) and re-verified MATCH: guess_g_MenuSwapSlot keeps the TU's
// `u16` canonical with `*(s16*)&` at the read sites (target needs lh), and
// guess_GetMenuPanelCursorIndex keeps the canonical s16(s16) decl with s32(s32) call-site casts.
// Def sig is s32(void); engine_core.h canon is `void func_8013F350(void)` and the
// callers already cast (`((short (*)(void))func_8013F350)()`) -> def-side reconcile.

extern u16 guess_g_OpenMenuId; // Names ledger: config/names.tsv guess_g_OpenMenuId
extern u16 guess_g_MenuPanel; // Names ledger: config/names.tsv guess_g_MenuPanel
extern u16 guess_g_MenuPadHeld; // Names ledger: config/names.tsv guess_g_MenuPadHeld
extern u16 guess_g_MenuPadPressed; // Names ledger: config/names.tsv guess_g_MenuPadPressed
extern u16 D_80115120;
extern u16 guess_g_MenuPadRepeatTimer; // Names ledger: config/names.tsv guess_g_MenuPadRepeatTimer
extern s16 guess_g_MenuCategory; // Names ledger: config/names.tsv guess_g_MenuCategory
extern s16 guess_g_MenuExitRequest; // Names ledger: config/names.tsv guess_g_MenuExitRequest
extern u16 guess_g_MenuSwapSlot; // Names ledger: config/names.tsv guess_g_MenuSwapSlot
extern u8  guess_g_MenuPanelScrollTops[]; // Names ledger: config/names.tsv guess_g_MenuPanelScrollTops
extern s16 D_8011514C;
extern s16 D_8011514E;
extern u8  D_80115152;
extern u8 guess_g_MenuPanelSizes[];   /* macro-canonical (§8e) */ // Names ledger: config/names.tsv guess_g_MenuPanelSizes
extern u8 D_8011515C;     /* macro-canonical (§8e) */
extern u8  D_8018305C[];
extern u8  D_80183074[];
extern u16 D_80182F78[];

extern s32 guess_TestGameFlag(s32 arg);
extern s32 guess_GetGameVarByte(s32 arg);
extern s16 guess_GetMenuPanelCursorIndex(s16 a0);
extern void func_8014AA04(s32 a0);
extern void guess_RequestSound(s32 a0, s32 a1);
extern void guess_SwapGameVarSlots(s32 a0, s32 a1);
extern void func_80141C0C(s32 a0);
extern s32 func_80140608(s32 a0);
extern void func_801407F4(void);
extern s32 func_801416D4(s16);  /* macro-canonical (§8e) */

s32 func_8013F350(void) {
    u16 *pd = &guess_g_MenuPadHeld;
    u16 *ps;
    u16 *pf;
    u16 *pg;
    u16 pad;
    u16 st;
    u8 *pcur;
    u8 *pmax;
    u8 *p2e;
    u8 *p3e;
    s32 off;
    s16 i;
    s32 r;
    s16 rs;
    s16 d;
    u8 b;
    u8 bb;
    u8 m;
    s32 chg;

    pad = *pd;
    chg = 0;
    pf = pd + 2;
    if (pad != 0) {
        if (pad == *pf) {
            guess_g_MenuPadRepeatTimer = guess_g_MenuPadRepeatTimer - 1;
            if (guess_g_MenuPadRepeatTimer == 0) {
                guess_g_MenuPadPressed = pad & 0xF000;
                guess_g_MenuPadRepeatTimer = 3;
            }
        } else {
            *pf = pad;
            guess_g_MenuPadRepeatTimer = 6;
        }
    } else {
        D_80115120 = 0;
        guess_g_MenuPadRepeatTimer = 0xC;
    }


    i = 0;
    do {
        if ((guess_TestGameFlag(D_8018305C[i]) & 0xFF) == 0) {
            break;
        }
        i = i + 1;
    } while (i < 6);
    *(u16 *)guess_g_MenuPanelSizes = i | 0x100;

    switch (guess_g_MenuPanel) { /* jtbl_801D8860 */
    case 0:
        r = ((s32 (*)(s32))guess_GetMenuPanelCursorIndex)(0);
        rs = (s16)r;
        if ((guess_TestGameFlag(D_8018305C[rs]) & 0xFF) != 0 && (guess_g_MenuPadPressed & 0x40) != 0) {
            func_8014AA04((r + 1) & 0xFF);
            if (rs != 0) {
                guess_RequestSound(0x461, 0);
            } else {
                guess_RequestSound(0x460, 0);
            }
        }
        break;
    case 1:
        if ((guess_g_MenuPadPressed & 0x40) != 0) {
            guess_g_MenuCategory = ((s32 (*)(s32))guess_GetMenuPanelCursorIndex)(1) + 1;
            guess_g_MenuPanel = 2;
            func_80141C0C(3);
            return 1;
        }
        if (guess_g_MenuCategory != 4) {
            break;
        }
        goto tail7;
    case 2:
        switch (guess_g_MenuCategory) { /* jtbl_801D8880 */
        case 0:
            break;
        case 1:
            r = ((s32 (*)(s32))guess_GetMenuPanelCursorIndex)(2);
            pf = &guess_g_MenuPadPressed;
            if ((*pf & 0x40) != 0) {
                if ((*(s16 *)&guess_g_MenuSwapSlot) == 0) {
                    if ((guess_GetGameVarByte(D_80183074[(s16)r]) & 0xFF) != 0 && (*pf & 0x40) != 0) {
                        guess_g_MenuPanel = 5;
                        *(s16 *)&D_80115152 = 0;
                        func_80141C0C(3);
                        return 1;
                    }
                    func_80141C0C(5);
                } else {
                    guess_SwapGameVarSlots((s16)r, (*(s16 *)&guess_g_MenuSwapSlot) & 0xF);
                    guess_g_MenuSwapSlot = 0;
                    func_80141C0C(3);
                    return 1;
                }
            } else if ((*pf & 0x20) != 0) {
                if ((*(s16 *)&guess_g_MenuSwapSlot) == 0) {
                    guess_g_MenuSwapSlot = r | 0x8000;
                } else {
                    guess_SwapGameVarSlots((s16)r, (*(s16 *)&guess_g_MenuSwapSlot) & 0xF);
                    guess_g_MenuSwapSlot = 0;
                }
                func_80141C0C(3);
            }
            break;
        case 4:
            if ((guess_g_MenuPadPressed & 0xA000) != 0) {
                chg = func_80140608(2);
            }
            func_801407F4();
            break;
        case 2:
            break;
        case 3:
            break;
        }
        if (guess_g_MenuCategory != 0 && (guess_g_MenuPadPressed & 0x10) != 0 && guess_g_OpenMenuId != 1) {
            guess_g_MenuPadPressed = guess_g_MenuPadPressed & 0xFFEF;
            guess_g_MenuPanel = 1;
            guess_g_MenuSwapSlot = 0;
            func_80141C0C(6);
        }
        break;
    case 3:
        if (D_8011514E == 0 && (guess_g_MenuPadPressed & 0x40) != 0) {
            guess_g_MenuPanel = guess_g_MenuPanel + 3;
            func_80141C0C(3);
            return 1;
        }
        break;
    case 5:
        if ((guess_g_MenuPadPressed & 0x40) != 0) {
            rs = (s16)((s32 (*)(s32))func_801416D4)(D_80115152);
            if (rs != 0) {
                if (rs < 0) {
                    guess_g_MenuExitRequest = 1;
                } else {
                    guess_g_MenuPanel = guess_g_MenuPanel - 3;
                    func_80141C0C(4);
                    return 1;
                }
            }
            break;
        }
        if ((guess_g_MenuPadPressed & 0x10) != 0) {
            goto tail6;
        }
        break;
    case 6:
        if ((guess_g_MenuPadPressed & 0x10) == 0) {
            break;
        }
    tail6:
        pg = &guess_g_MenuPadPressed;
        *pg = *pg & 0xFFEF;
        guess_g_MenuPanel = guess_g_MenuPanel - 3;
        func_80141C0C(6);
        return 1;
    case 7:
        if ((guess_g_MenuPadPressed & 0xA000) != 0) {
            chg = func_80140608(7);
        }
    tail7:
        func_801407F4();
        break;
    }

    ps = &guess_g_MenuPanel;
    
    st = *ps;
    off = st << 1;
    p2e = (u8 *)ps + 0x2E;
    p3e = (u8 *)ps + 0x3E;
    pcur = p2e + off;
    pmax = p3e + off;
    if (st == 2 || 1 < pmax[0]) {
        if ((guess_g_MenuPadPressed & 0x1000) != 0) {
            pcur[0] = pcur[0] - 1;
            chg = 1;
            if (0x7F < pcur[0]) {
                if (guess_g_MenuPanel != 3) {
                    pcur[0] = pmax[0] - 1;
                } else {
                    pcur[0] = 0;
                    chg = 0;
                }
            }
        }
        if ((guess_g_MenuPadPressed & 0x4000) != 0) {
            b = pcur[0];
            pcur[0] = b + 1;
            chg = 1;
            if (pmax[0] <= (u8)(b + 1)) {
                if (guess_g_MenuPanel != 3) {
                    pcur[0] = 0;
                } else {
                    pcur[0] = b;
                    chg = 0;
                }
            }
        }
        if (guess_g_MenuPanel == 2 && guess_g_MenuCategory == 1) {
            if ((guess_g_MenuPadPressed & 0x8000) != 0) {
                pcur[1] = pcur[1] - 1;
                chg = 1;
                if (0x7F < pcur[1]) {
                    pcur[1] = pmax[1] - 1;
                }
            }
            if ((guess_g_MenuPadPressed & 0x2000) != 0) {
                pcur[1] = pcur[1] + 1;
                chg = 1;
                if (pmax[1] <= pcur[1]) {
                    pcur[1] = 0;
                }
            }
        } else {
            bb = pcur[0];
            m = guess_g_MenuPanelScrollTops[guess_g_MenuPanel];
            d = (s8)bb - (s8)m;
            if (d > 0) {
                guess_g_MenuPanelScrollTops[guess_g_MenuPanel] = bb;
            } else if (d < 0) {
                guess_g_MenuPanelScrollTops[guess_g_MenuPanel] = bb;
            }
        }
        if (guess_g_MenuPanel == 1) {
            guess_g_MenuCategory = ((s32 (*)(s32))guess_GetMenuPanelCursorIndex)(1) + 1;
            if ((guess_g_MenuPadPressed & 0x5000) != 0) {
                D_8011514C = 0;
            }
        }
        *(u16 *)&D_8011515C = D_80182F78[guess_g_MenuCategory];
        if ((chg << 0x10) != 0) {
            func_80141C0C(1);
        }
    }
    return 0;
}



// @class: regalloc-order
// @unstuck(P36): none — MATCH (312/312, relocation-masked)










extern void  func_80140E6C(void);
extern void  func_80140F00(void);
extern s32  *func_80140958(s32 *, s32, s32);
extern int   func_80141100(int);
extern s16   guess_GetMenuPanelCursorIndex(s16);
extern s32   func_8013FFD8(s16, s32, s32 *);
extern s32 guess_SjisToGlyphCodes(void *a0, void *a1);
extern u32 *func_800D2650(s32 *, void *, s32, s32, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);
extern u8 *func_800D27DC(s32, s32 *, void *, s32, s32);
extern u32 *func_800D29F8(s32, s32, void *, s32, s32);
extern int func_80137D08(int arg0, int arg1, short arg2);
extern s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3);


void func_8013FAF8(s16 arg0, s16 arg1) {

    extern s32    guess_g_MenuPacketPtr; // Names ledger: config/names.tsv guess_g_MenuPacketPtr
    extern u16    guess_g_MenuPanel; // Names ledger: config/names.tsv guess_g_MenuPanel
    extern short guess_g_MenuCategory; // Names ledger: config/names.tsv guess_g_MenuCategory
    extern Hw4    D_8011516A[];
    extern u8     D_80078EC0;
    extern short guess_g_DoubleBufferIndex; // Names ledger: config/names.tsv guess_g_DoubleBufferIndex
    extern Rec20  guess_g_FrontOrderingTables[]; // Names ledger: config/names.tsv guess_g_FrontOrderingTables
    extern Blk60  D_801829C0[];
    extern Blk20  D_80182CC0[];
    extern Prim4  D_80182DC0[];
    extern Prim4  D_80182E30[];
    extern Prim4 *D_80182F24[];
    extern s32    D_80182F44[];
    extern u8 D_80182F64;
    extern s16    D_80183338;
    extern s16    D_8018333A;
    u8 sp18[72];
    s32 sp60[2];
    s32 *ot;
    s16 i;
    s16 j;
    s32 flag;
    s32 addr;
    Prim4 *p;
    s32 r;
    s32 t;
    s16 *pp;
    s32 flag2;
    u16 flag3;

    func_80140E6C();
    func_80140F00();
    ot = func_80140958((s32 *)guess_g_MenuPacketPtr, arg0, arg1);
    if (guess_g_MenuPanel < 6) {
        ot = (s32 *)func_80141100((int)ot);
    }
    for (i = arg0; i < arg1; i++) {
        if (i == guess_g_MenuPanel || i == 2 || i == 4) {
            flag = 0;
        } else {
            flag = 0xFF;
        }
        p = &D_80182DC0[i];
        if (i != 5) {
            if (i == 2) {
                addr = ((s32 *)&D_80182F64)[*(s16 *)&guess_g_MenuCategory];
            } else {
                addr = D_80182F44[i];
            }
        } else {
            addr = func_8013FFD8(2, guess_GetMenuPanelCursorIndex(2), sp60);
        }
        guess_SjisToGlyphCodes(addr, sp18);
        ot = func_800D2650(ot, sp18, (s16)(p->dist + (u16)D_8011516A[i].x), p->kind, 1,
                           flag != 0 ? 0x585858 : 0x808080);
        p = D_80182F24[i];
        j = 0;
        if (p != 0) {
            if (i == 2 && *(s16 *)&guess_g_MenuCategory != 0) {
                p = D_80182E30;
            }
            flag2 = flag;
            for (;;) {
                r = func_8013FFD8(i, j++, sp60);
                if (r == 0) {
                    break;
                }
                if (r < 0) {
                    guess_SjisToGlyphCodes(r, sp18);
                    t = 1;
                    if (i == 0 && (D_80078EC0 & 0x7F) == j) {
                        t = 0xB6;
                    }
                    if (flag2 != 0) {
                        sp60[0] += -0x282828;
                    }
                    ot = func_800D2650(ot, sp18, (s16)(p->dist + (u16)D_8011516A[i].x), p->kind, t, sp60[0]);
                }
                p++;
            }
        }
        func_8005A600((s32)ot, 0, 0, 0x15, 0);
        flag3 = flag;
        *ot = 0x2000000;
        *ot = (guess_g_FrontOrderingTables[*(u16 *)&guess_g_DoubleBufferIndex].f4[2] & 0xFFFFFF) | 0x2000000;
        guess_g_FrontOrderingTables[*(u16 *)&guess_g_DoubleBufferIndex].f4[2] =
            (guess_g_FrontOrderingTables[*(u16 *)&guess_g_DoubleBufferIndex].f4[2] & 0xFF000000) | ((u32)ot & 0xFFFFFF);
        ot = func_800D29F8(flag3,
                           func_800D27DC(flag3 != 0, ot + 10, &D_801829C0[i], 8, D_8011516A[i].x),
                           &D_80182CC0[i], 2, D_8011516A[i].x);
    }
    pp = &D_80183338;
    if (*pp == 0xE) {
        ot = func_80137D08(ot, &guess_g_FrontOrderingTables[*(u16 *)&guess_g_DoubleBufferIndex], 2);
    }
    if (*pp != 0 && D_8018333A != 0) {
        ot = func_8013AB54(ot, guess_g_FrontOrderingTables[*(u16 *)&guess_g_DoubleBufferIndex].f4 + 2, (s32)(pp - 2), 0x8000);
    }
    guess_g_MenuPacketPtr = (s32)ot;
}


/* func_8013FFD8 — 213 ins, double jump-table, per-location family (134 members). */

extern s32 guess_TestGameFlag(s32 arg);
extern s32 guess_GetGameVarByte(s32 arg);


s32 func_8013FFD8(s16 arg0, s32 arg1, s32 *arg2) {

    extern u8  D_8018305C[];
    extern u8  D_80183074[];
    extern short guess_g_MenuCategory; // Names ledger: config/names.tsv guess_g_MenuCategory
    extern u8  D_80183080[];
    extern u8  D_80183087[];
    extern u8  D_80183088[];
    extern s32 D_80182FB0;
    extern s32 D_80182FC8[];
    extern char *D_80182F84;
    extern unsigned short D_80182F98[];
    extern u8 D_80183008;
    extern u8 D_8018300C;
    extern u8 *D_80183018;
    extern s32 guess_g_VillagerNames[]; // Names ledger: config/names.tsv guess_g_VillagerNames
    extern s32 D_8010EDE8[];
    extern u8  D_80115143;
    extern void * D_801A6B04;
    extern void * D_801A6B00;
    s32 ret;

    *arg2 = 0x808080;
    ret = 0;

    switch (arg0) {                                   /* jtbl_801D8898 */
    case 0: {
        s16 s0 = (s16) arg1;
        if (s0 < 6) {
            if ((((s32 (*)(u8))guess_TestGameFlag)(D_8018305C[s0]) & 0xFF) == 0) {
                return 1;
            }
            ret = ((s32 *)&D_80182FB0)[s0];
        }
        break;
    }
    case 1: {
        s16 v1 = (s16) arg1;
        if (v1 < 4) {
            ret = D_80182FC8[v1];
        }
        break;
    }
    case 2:
        switch ((*(s16 *)&guess_g_MenuCategory)) {                         /* jtbl_801D88B8 */
        case 0: {
            s16 v1 = (s16) arg1;
            if (v1 < 5) {
                ret = ((s32 *)&D_80182F84)[v1];
            }
            break;
        }
        case 1: {
            s16 v1 = (s16) arg1;
            if (v1 < 0xC) {
                s32 v3 = ((s32 (*)(u8, s32))guess_GetGameVarByte)(((u8 *)&D_80183074)[v1], arg1) & 0xFF;
                if (v3 == 0) {
                    return 1;
                }
                ret = D_8010EDE8[v3 * 3];
            }
            break;
        }
        case 2: {
            s16 s0 = (s16) arg1;
            if (s0 < 6) {
                if ((((s32 (*)(u8))guess_TestGameFlag)((*(u8 * *)&D_801A6B04)[s0]) & 0xFF) == 0) {
                    return 1;
                }
                ret = (*(s32 * *)&D_801A6B00)[s0];
            }
            break;
        }
        case 3: {
            s16 s0 = (s16) arg1;
            if (s0 < 6) {
                if ((((s32 (*)(u8))guess_TestGameFlag)(D_80183080[s0]) & 0xFF) == 0) {
                    return 1;
                }
                ret = ((s32 *)D_80182F98)[s0];
            }
            break;
        }
        case 4: {
            s16 v1 = (s16) arg1;
            if (v1 < 5) {
                ret = ((s32 *)&D_80183018)[v1];
            }
            break;
        }
        }
        break;
    case 3: {
        s16 t = (s16) arg1;
        if (t <= 0) {
            s16 s0 = t + D_80115143;
            if (s0 != 0) {
                if ((((s32 (*)(u8, s32))guess_GetGameVarByte)(D_80183087[s0], arg1) & 0xFF) == 0) {
                    *arg2 = 0x804040;
                }
                ret = guess_g_VillagerNames[s0];
            } else {
                ret = (*(s32 *)&D_80183008);
            }
        }
        break;
    }
    case 5: {
        s16 v1 = (s16) arg1;
        if (v1 < 3) {
            ret = ((s32 *)&D_8018300C)[v1];
        }
        break;
    }
    case 6: {
        s16 s0 = (s16) arg1;
        if (s0 < 0x28) {
            s32 idx;
            if ((((s32 (*)(u8, s32))guess_GetGameVarByte)(D_80183088[s0], arg1) & 0xFF) == 0) {
                *arg2 = 0x804040;
            }
            idx = s0 + 1;
            ret = guess_g_VillagerNames[idx];
        }
        break;
    }
    case 7: {
        s16 v1 = (s16) arg1;
        if (v1 < 5) {
            ret = ((s32 *)&D_80183018)[v1];
        }
        break;
    }
    }
    return ret;
}

