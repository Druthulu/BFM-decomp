/* func_8017D2DC @ ov_SC01_001 (ov_SC01_001_jr_8017BEBC) -- 1,586 ins, 125-case jr switch
 * over the scene-script state D_801F313C (jtbl_801EC46C).  Behemoth #7.
 *
 * STATUS: see the report .run/giants/s21_8017D2DC_report.md for the measured match_one number.
 *
 * gate:  .venv/bin/python tools/match_one.py func_8017D2DC \
 *          --c .run/giants/s21_func_8017D2DC_b1.c \
 *          --asm-subdir asm/ov_SC01_001/nonmatchings/ov_SC01_001_jr_8017BEBC
 *
 * PIN-FREE.  No stack locals (frame 0x18 = 0x10 arg-save + $s0 + $ra).
 *
 * THE RELATIVE (§71, and it is in this very overlay):
 *   src/ov_SC01_001/ov_SC01_001_jr_80178D40.c :: func_80178D40 -- 890 ins, 94-case jr switch,
 *   MATCHED, with a 13-point recipe comment above it.  Levers taken from it verbatim:
 *     #1  NO status variable.  Every case stores `D_801ED9F4 = 0; D_801F313C++;` DIRECTLY;
 *         .L8017EB5C/.L8017EB64/.L8017EB70 are a jump2 CROSS-JUMP merge of those stores
 *         (the merge lives at the tail of case 123, the last case that has one).
 *     #2  after-switch = `func_8017EBCC(); func_80182D04(D_801ED9F0);` -- the out-of-range
 *         default lands there with NO explicit `default:` label.
 *     #7  per-case temporaries are block-local (there are none here).
 *     #8  stack locals in slot order -- there are none; only `pv` (a pointer, $s0).
 *
 * DECODE FACTS (byte-derived):
 *   - the switch bound is `sltiu 0x7D` and the table has 125 entries => max case value is 124,
 *     so `case 124:` EXISTS with an empty body (its entry == the default/after-switch label).
 *     Cases 10/11/12 are ABSENT (their entries are the default label -- indistinguishable
 *     from an empty case, so they are simply omitted).
 *   - cases 19,21,27,31,51,53,57,59,87,89 have the bare tail as their WHOLE body; cross_jump
 *     reduced each block to `j .L8017EB5C` and jump.c's ADDR_VEC follow_jumps pass then
 *     retargeted the table entry straight at .L8017EB5C.
 *   - `pv` (= &D_80126948) is a FUNCTION-SCOPE pointer: the target materialises the address in
 *     the prologue ($s0, callee-saved, live across `jal func_80174E9C` in case 1) and case 1
 *     stores through it with `sw $v0,0x8($s0)`.  An inline `*(s32*)&D_80126948[8]` would emit
 *     lui+sw at the use site instead.
 *   - the head is `pad = func_800149E0(0);` FIRST (unconditional call), then
 *     `if (D_801F313C < 0x7B && (pad & 0x840)) D_801F313C = 0x7B;`  -- the `&&` gives exactly
 *     slti/beqz then andi/beqz; the call cannot be inside the `&&` or it would sit after the
 *     first branch.
 *   - the `pv=` insn is scheduled AFTER the jal in the target: a pseudo set from a SYMBOL_REF
 *     carries no dependence on a CALL_INSN in sched.c, so it is free to fill the load-delay of
 *     `lw $v1,D_801F313C`.  Nothing in the source expresses that; leave the decl first.
 *
 * NEW OBSERVATION worth a cookbook entry (§88 candidate) -- CROSS_JUMP WILL NOT MERGE A COMMON
 * SUFFIX THAT CONTAINS A CALL.  This function contains ~34 BYTE-IDENTICAL 6-insn blocks
 * (`jal func_8017EC18; beqz $v0,.L8017EB5C; j .L8017EB78`) and case 66's sub-0/sub-2 are two
 * byte-identical 12-insn blocks -- NONE of them are merged, while every call-free common tail
 * (.L8017EB5C/EB64/EB70, .L8017E9A0/E9AC/E9B4, .L8017E06C, .L8017DAF0, .L8017E804) IS merged.
 * => write the repeated `if (func_8017EC18() == 0) {...}` cases out longhand; they stay separate.
 */

#include "common.h"

/* ---- shared (resident) callees ------------------------------------------------ */
extern s32  func_800149E0(s32 a0);            /* no fleet canon -- free choice */
extern void func_80016450(s32 a0, s32 a1);    /* no fleet canon -- free choice */
extern int  func_8001AAA0(void);              /* TU canon: (void); called with 1 arg -> §17a-1 cast */
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D0C48(s32 a0);
extern void func_800D1724(s32 a0);
extern void func_8013C9C4(void *a0);
extern s32  func_8013D13C(void);              /* fleet canon: (void); called with 1 arg -> §17a-1 cast */

/* ---- overlay-local callees ---------------------------------------------------- */
extern void func_80174E9C(s32 a0);
extern void func_8017EBA4(void *a0);
extern void func_8017EBCC(void);
extern s32  func_8017EC18(void);
extern void func_8017EC28(s32 a0);
extern void func_8017F1C8(void *a0);
extern void func_8017F1F8(void);
extern void func_80181834(void);
extern void func_80181A28(void);
extern void func_80181A4C(void);
extern void func_80181E04(void);
extern void func_80182238(void);
extern s32  func_80182284(void);
extern void func_801824EC(s32 a0);
extern s32  func_8018275C(void);
extern void func_80182A48(void);
extern void func_80182B68(s32 a0);
extern void func_80182B9C(s32 a0);
extern void func_80182BD0(s32 a0);
extern void func_80182C10(void);
extern void func_80182D04(s32 a0);
extern void func_80182EB0(void *a0, s32 a1);
extern void func_801831EC(void);
extern void func_80183748(void *a0);

/* ---- scalars ------------------------------------------------------------------ */
extern u16 D_800B99D8;
extern u8  D_80126948[];
extern s32 D_80188A90;
extern s32 D_801ED9CC;
extern s32 D_801ED9D4;
extern s32 D_801ED9D8;
extern s32 D_801ED9E0;
extern s32 D_801ED9E4;
extern s32 D_801ED9E8;
extern s32 D_801ED9F0;
extern s32 D_801ED9F4;
extern s32 D_801EDA20;
extern s32 D_801EDA38;
extern s32 D_801EDA3C;
extern s32 D_801EDA40;
extern s32 D_801F3034;
extern s32 D_801F313C;

/* ---- address-taken blobs ------------------------------------------------------ */
extern u8 D_80183FB4[];
extern u8 D_80187268[];
extern u8 D_80188B14[];
extern u8 D_80188B34[];
extern u8 D_80188B54[];
extern u8 D_80188C5C[];
extern u8 D_80188CF8[];
extern u8 D_80188D10[];
extern u8 D_80188F54[];
extern u8 D_80188FC0[];
extern u8 D_80189018[];
extern u8 D_80189064[];
extern u8 D_80189088[];
extern u8 D_801890EC[];
extern u8 D_80189168[];
extern u8 D_801891A4[];
extern u8 D_80189208[];
extern u8 D_8018922C[];
extern u8 D_80189264[];
extern u8 D_8018928C[];
extern u8 D_801892D4[];
extern u8 D_80189318[];
extern u8 D_801893A0[];
extern u8 D_801893C8[];
extern u8 D_80189420[];
extern u8 D_80189458[];
extern u8 D_801894C0[];
extern u8 D_80189524[];
extern u8 D_8018957C[];
extern u8 D_801895B8[];
extern u8 D_80189618[];
extern u8 D_80189678[];
extern u8 D_801896D8[];
extern u8 D_80189758[];
extern u8 D_80189874[];
extern u8 D_801898F8[];
extern u8 D_8018996C[];
extern u8 D_80189A18[];
extern u8 D_80189A58[];
extern u8 D_80189B34[];
extern u8 D_80189B64[];
extern u8 D_80189BD4[];
extern u8 D_80189C28[];
extern u8 D_80189C54[];
extern u8 D_80189D2C[];
extern u8 D_80189D6C[];
extern u8 D_80189DDC[];
extern u8 D_80189E4C[];
extern u8 D_80189E8C[];
extern u8 D_801C357C[];
extern u8 D_801C565C[];
extern u8 D_801C5BC8[];
extern u8 D_801C5E94[];
extern u8 D_801C5EC0[];
extern u8 D_801C62A4[];
extern u8 D_801C9584[];
extern u8 D_801CC838[];
extern u8 D_801CC864[];
extern u8 D_801CC890[];
extern u8 D_801CC8BC[];
extern u8 D_801CC8E8[];
extern u8 D_801CC914[];
extern u8 D_801CC940[];
extern u8 D_801CD7F8[];
extern u8 D_801CD824[];
extern u8 D_801CD850[];
extern u8 D_801CDBA8[];
extern u8 D_801CDBD4[];
extern u8 D_801CE38C[];
extern u8 D_801CE3B8[];
extern u8 D_801CE3E4[];
extern u8 D_801CE410[];
extern u8 D_801CE43C[];
extern u8 D_801CE468[];
extern u8 D_801CE494[];
extern u8 D_801CE4C0[];
extern u8 D_801CE4EC[];
extern u8 D_801CE518[];
extern u8 D_801CE544[];
extern u8 D_801CF6D4[];
extern u8 D_801CF700[];
extern u8 D_801CF72C[];
extern u8 D_801CF758[];
extern u8 D_801CF784[];
extern u8 D_801CF7B0[];
extern u8 D_801CFCAC[];
extern u8 D_801D113C[];
extern u8 D_801D1938[];
extern u8 D_801D2470[];
extern u8 D_801D2534[];


void func_8017D2DC(void)
{
    s32 *pv = (s32 *)D_80126948;
    s32 pad = func_800149E0(0);

    if (D_801F313C < 0x7B && (pad & 0x840)) {
        D_801F313C = 0x7B;
    }
    func_8017F1F8();

    switch (D_801F313C) {
    case 0:
        D_801ED9CC = 0;
        D_801EDA20 = 0;
        D_801ED9D4 = 0;
        D_801ED9D8 = 1;
        D_801ED9F0 = 0;
        func_80181A28();
        func_80182C10();
        func_80183748(D_80188B14);
        D_80188A90 = 0;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 1:
        D_801ED9E4 = 0x2D;
        D_801ED9E8 = 0x1E;
        func_80174E9C((s32)D_80188C5C);
        pv[2] = 0x100;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 2:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        D_801ED9E8--;
        if (D_801ED9E8 == 0) {
            func_8002D4C8(0xB0A, 0);
            func_8013C9C4(D_80183FB4);
            func_80182EB0(D_80188CF8, 3);
        }
        break;
    case 3:
        func_8017F1C8(D_801C357C);
        func_8017EC28(1);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 4: {
        s32 lim = 0x8A;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            func_8017EBA4(D_80188F54);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 5:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 6: {
        s32 lim = 0x1E;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            func_8017EBA4(D_80188FC0);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 7:
        if (func_8017EC18() == 0) {
            func_8017EC28(2);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 8:
        func_8017EBA4(D_80189018);
        func_8017F1C8(D_801C565C);
        D_801ED9E4 = 0x30;
        D_801ED9F4 = 0;
        D_801F313C++;
        /* fallthrough */
    case 9:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_80182BD0(3);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C = 0xD;
            func_8017EC28(3);
        }
        break;
    case 13:
        func_8017F1C8(D_801C5BC8);
        func_8017EBA4(D_80189064);
        func_80182C10();
        func_80183748(D_80188B34);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 14:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 15:
        func_8017F1C8(D_801C5E94);
        func_8017EBA4(D_80189088);
        func_8017EC28(0xF);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 16:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 17:
        func_8017F1C8(D_801C5EC0);
        func_8017EC28(0x12);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 18: {
        s32 lim = 0x46;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            D_801ED9F4 = 0;
            D_801F313C = 0x21;
        }
        break;
    }
    case 19:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 20:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 21:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 22:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 23:
        func_8017EBA4(D_801891A4);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 24:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 25:
        func_8017F1C8(D_801C62A4);
        func_8017EC28(4);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 26:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 27:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 28:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 29:
        func_8017F1C8(D_801C9584);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 30:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 31:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 32:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 33:
        func_8017EBA4(D_801890EC);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 34:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 35:
        func_8017EBA4(D_80189168);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 36:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 37:
        func_8017F1C8(D_801CC838);
        func_8017EC28(9);
        func_80182BD0(3);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 38:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 39:
        func_8017F1C8(D_801C62A4);
        func_8017EC28(4);
        func_8017EBA4(D_80189208);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 40:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 41:
        func_80182BD0(1);
        func_8017F1C8(D_801CC864);
        func_8017EC28(0xB);
        func_800D0C48(1);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 42: {
        s32 lim = 0x1E;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 43:
        func_8017F1C8(D_801CC890);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 44: {
        s32 lim = 0x1E;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 45:
        func_8017F1C8(D_801CC8BC);
        D_801ED9E0 = 0;
        D_801F3034 = 0;
        func_80181834();
        func_80182238();
        func_8002D4C8(0xB0C, 0);
        D_801ED9E4 = 0x1E;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 46:
        switch (D_801F3034) {
        case 0:
            if (D_801ED9E0 == 0 && (D_800B99D8 & 1) &&
                ((s32 (*)(s32))func_8013D13C)(9) == 0) {
                D_801ED9E0 = 1;
            }
            if (func_80182284() == 0) {
                func_80181A4C();
            } else {
                D_801ED9E4--;
                if (D_801ED9E4 == 0) {
                    func_80016450(0xFF, 0);
                    func_8002D4C8(0xB0D, 0);
                    D_801ED9E4 = 2;
                    D_801F3034++;
                }
            }
            break;
        case 1:
            func_80016450(0xFF, 0);
            D_801ED9E4--;
            if (D_801ED9E4 == 0) {
                func_8013C9C4(D_80183FB4);
                func_801824EC(0);
                func_801824EC(1);
                func_801824EC(2);
                D_801ED9E4 = 8;
                D_801F3034++;
            }
            break;
        case 2:
            D_801ED9E4--;
            if (D_801ED9E4 == 0) {
                func_801824EC(0);
                func_801824EC(1);
            }
            if (func_8018275C() != 0) {
                func_80182A48();
                func_80016450(0xFF, 0);
                D_801EDA38 = 1;
                D_801ED9F4 = 0;
                D_801F313C++;
            }
            break;
        }
        func_80181E04();
        break;
    case 47:
        func_8017F1C8(D_801CC8E8);
        func_80183748(D_80188B54);
        D_801ED9F0 = 0;
        func_80182B9C(2);
        func_8017EC28(0x2424);
        D_801EDA38 = 1;
        ((int (*)(s32))func_8001AAA0)(0x90);
        D_801ED9E4 = 0xFF;
        D_801F3034 = 0;
        D_801ED9F4 = 0;
        D_801F313C++;
        /* fallthrough */
    case 48:
        switch (D_801F3034) {
        case 0:
            ((s32 (*)(s32))func_8013D13C)(1);
            func_80016450(*(u8 *)&D_801ED9E4, 0);
            D_801ED9E4 -= 4;
            if (D_801ED9E4 < 0) {
                func_8017EBA4(D_8018922C);
                D_801EDA3C = 0;
                D_801EDA40 = 0;
                D_801F3034++;
            }
            break;
        case 1:
            if (func_8017EC18() == 0) {
                func_8017F1C8(D_801CC914);
                func_8017EBA4(D_80189264);
                func_801831EC();
                D_801F3034++;
            }
            break;
        case 2:
            func_801831EC();
            if (func_8017EC18() == 0) {
                D_801ED9F4 = 0;
                D_801F313C++;
            }
            break;
        }
        break;
    case 49:
        func_8017F1C8(D_801CC940);
        func_8017EBA4(D_8018928C);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 50:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C = 0x37;
        }
        break;
    case 51:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 52:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 53:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 54:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 55:
        func_8017EBA4(D_801892D4);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 56:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C = 0x3D;
        }
        break;
    case 57:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 58:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 59:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 60:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 61:
        func_8017F1C8(D_801CD7F8);
        func_8017EC28(0x3031);
        func_8017EBA4(D_80189318);
        func_80182B68(2);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 62:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 63:
        func_8017EBA4(D_801893A0);
        func_8017EC28(0x30B);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 64:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x100);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 65:
        func_80182B68(3);
        func_8017EBA4(D_801893C8);
        func_8017EC28(0x3131);
        D_801F3034 = 0;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 66:
        switch (D_801F3034) {
        case 0:
            if (func_8017EC18() == 0) {
                D_801ED9F4 = 0;
                D_801F3034 = 0;
                D_801F313C++;
            }
            break;
        case 1:
            func_8017EC28(0xD);
            func_8017F1C8(D_801C62A4);
            D_801F3034++;
            break;
        case 2:
            if (func_8017EC18() == 0) {
                D_801ED9F4 = 0;
                D_801F3034 = 0;
                D_801F313C++;
            }
            break;
        }
        break;
    case 67:
        switch (D_801F3034) {
        case 0:
            func_8017F1C8(D_801CD824);
            func_8017EBA4(D_80189420);
            func_8017EC28(0x10);
            func_80182C10();
            D_801F3034++;
            break;
        case 1:
            if (func_8017EC18() == 0) {
                D_801F3034++;
            }
            break;
        case 2:
            func_8017F1C8(D_801CD850);
            func_80182B9C(1);
            func_8017EC28(0x11);
            D_801ED9E4 = 0;
            D_801F3034++;
            break;
        case 3:
            if (D_801ED9E4 != 0) {
                D_801ED9F4 = 0;
                D_801F313C++;
            }
            break;
        }
        break;
    case 68: {
        D_801ED9F4++;
        if (D_801ED9F4 > 0x1E) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 69:
        func_8017F1C8(D_801CDBA8);
        func_8017EBA4(D_80189458);
        func_8017EC28(0x3636);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 70:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x3737);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 71:
        func_8017F1C8(D_801CDBD4);
        func_80182BD0(0);
        func_8017EBA4(D_801894C0);
        D_801ED9E4 = 0x64;
        D_801ED9E8 = 0x28;
        D_801ED9F4 = 0;
        D_801F313C++;
        /* fallthrough */
    case 72:
        D_801ED9E8--;
        if (D_801ED9E8 == 0) {
            func_80182BD0(7);
        }
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_80182BD0(2);
            func_8017EC28(0x37B);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 73:
        func_8017F1C8(D_801CE38C);
        func_8017EC28(0x38A);
        func_8017EBA4(D_80189524);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 74:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 75:
        func_8017F1C8(D_801CE3B8);
        func_8017EC28(0x38B);
        func_8017EBA4(D_8018957C);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 76:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 77:
        func_8017F1C8(D_801CE3E4);
        func_8017EC28(0x3939);
        func_8017EBA4(D_801895B8);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 78:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x4040);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 79:
        func_8017F1C8(D_801CE410);
        func_8017EBA4(D_80189618);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 80:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 81:
        func_8017F1C8(D_801CE43C);
        func_8017EC28(0x4141);
        func_8017EBA4(D_80189678);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 82:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 83:
        func_8017F1C8(D_801CE468);
        func_80182B9C(1);
        func_8017EC28(0x4242);
        func_8017EBA4(D_801896D8);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 84:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C = 0x5B;
        }
        break;
    case 85:
        func_8017EC28(0x4747);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 86:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 87:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 88:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 89:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 90:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 91:
        func_8017F1C8(D_801CE494);
        func_8017EBA4(D_80189758);
        func_8017EC28(0x4747);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 92:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x4848);
            func_8017F1C8(D_801CE4C0);
            func_8017EBA4(D_80189874);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 93:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x4949);
            D_801ED9E4 = 0x14;
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 94:
        func_8017F1C8(D_801CE4EC);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 95:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8013C9C4(D_80183FB4);
            func_8002D4C8(0xB0B, 0);
            func_80182EB0(D_80188D10, 7);
        }
        {
            s32 lim = 0x3C;
            D_801ED9F4++;
            if (lim < D_801ED9F4) {
                func_8017EBA4(D_801898F8);
                D_801ED9F4 = 0;
                D_801F313C++;
            }
        }
        break;
    case 96:
        func_8017EC28(0x5050);
        func_8017F1C8(D_801CE518);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 97:
        if (func_8017EC18() == 0) {
            func_8017F1C8(D_801CE544);
            func_8017EBA4(D_8018996C);
            func_8017EC28(0x5151);
            D_801ED9E4 = 0xAA;
            D_801ED9E8 = 0x12C;
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 98:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8017EC28(0x5151B);
        }
        D_801ED9E8--;
        if (D_801ED9E8 == 0) {
            func_8017EC28(0x5151C);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 99:
        D_801ED9F0 = 1;
        func_80182B9C(0);
        func_8017EBA4(D_80189A18);
        func_8017EC28(0x5252);
        D_801ED9E4 = 0x13;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 100:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8017F1C8(D_801CF6D4);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 101:
        func_8017F1C8(D_801CF700);
        func_8017EC28(0x53A);
        func_8017EBA4(D_80189A58);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 102:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 103:
        func_8017F1C8(D_801CF72C);
        func_8017EC28(0x53B);
        func_8017EBA4(D_80189B34);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 104:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 105:
        func_8017F1C8(D_801CF758);
        func_8017EBA4(D_80189B64);
        func_8017EC28(0x53C);
        D_801ED9E4 = 0;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 106:
        switch (D_801ED9E4) {
        case 0:
            if (func_8017EC18() == 0) {
                func_8017EC28(0x5454);
                D_801ED9E8 = 0x10;
                D_801ED9E4++;
            }
            break;
        case 1:
            D_801ED9E8--;
            if (D_801ED9E8 == 0) {
                D_801ED9F0 = 2;
                func_8002D4C8(0xC8D, 0);
                D_801ED9E8 = 0x10;
                D_801ED9E4++;
            }
            break;
        case 2:
            D_801ED9E8--;
            if (D_801ED9E8 == 0) {
                func_8017EC28(0x54B);
                D_801ED9F4 = 0;
                D_801F313C++;
            }
            break;
        }
        break;
    case 107:
        func_8017F1C8(D_801CF784);
        func_8017EC28(0x5555);
        func_8017EBA4(D_80189BD4);
        D_801ED9F4 = 0;
        D_801ED9E4 = 0x59;
        D_801F313C++;
        break;
    case 108:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8017EC28(0x55B);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 109:
        func_8017F1C8(D_801CF7B0);
        func_8017EC28(0x5656);
        func_8017EBA4(D_80189C28);
        func_80182C10();
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 110:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 111:
        func_8017F1C8(D_801CFCAC);
        func_8017EC28(0x57A);
        func_8017EBA4(D_80189C54);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 112:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 113:
        func_8017F1C8(D_801D113C);
        func_8017EBA4(D_80189D2C);
        D_801ED9E4 = 0x1E;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 114:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8017EC28(0x57B);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 115: {
        s32 lim = 0x1E;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            func_8017F1C8(D_801D1938);
            func_8017EC28(0x5858);
            func_8017EBA4(D_80189D6C);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 116:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 117:
        func_8017F1C8(D_801D2470);
        func_8017EC28(0x5959);
        func_80182BD0(3);
        func_8017EBA4(D_80189DDC);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 118:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 119:
        func_8017EBA4(D_80189E4C);
        func_8017F1C8(D_801D2534);
        func_80182C10();
        func_8017EC28(0x6060);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 120:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 121:
        func_8017EBA4(D_80189E8C);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 122:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 123:
        func_800D1724((s32)D_80187268);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 124:
        break;
    }

    func_8017EBCC();
    func_80182D04(D_801ED9F0);
}
