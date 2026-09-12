#include "common.h"
#include "../shared/engine_prelude.h"

#include "../shared/ov/func_80128158.h"


#include "../shared/ov/func_80128178.h"


#include "../shared/ov/func_80128198.h"


#include "../shared/ov/func_801281B8.h"


#include "../shared/ov/func_801281D8.h"


#include "../shared/ov/func_801281F8.h"




s32 func_80128218(void) {

    extern s32 D_801C7200;
    return D_801C7200;
}


#include "../shared/ov/func_80128228.h"


#include "../shared/ov/func_80128248.h"


#include "../shared/ov/func_80128268.h"




void func_80128288(void) {

    extern u16 D_800B99F6;
    extern void (*D_80183EA4[])(void);
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_80183EA4[v1]();
    }
}


#include "../shared/ov/func_801282CC.h"


#include "../shared/ov/func_801282EC.h"


extern s32 func_80128998(void);
#include "../shared/ov/func_8012832C.h"


#include "../shared/ov/func_80128420.h"


#include "../shared/ov/func_801284B8.h"


#include "../shared/ov/func_801284F0.h"


#include "../shared/ov/func_8012853C.h"


#include "../shared/ov/func_80128564.h"


#include "../shared/ov/func_801285D4.h"



extern s32 func_800D18DC(void);
extern void func_8014607C(void);
extern void func_801287B8(void);
extern s32 func_80011A3C(void);

void func_801285E4(void)
{

    extern s32 D_801C83AC;
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_800D18DC\n"
        "lui   $at, %%hi(D_801C83AC)\n"
        "sw    $v0, %%lo(D_801C83AC)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "jal   func_8014607C\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_801287B8\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C83AC)\n"
        "lw    $v0, %%lo(D_801C83AC)($v0)\n"
        "nop\n"
        "beqz  $v0, 1f\n"
        "nop\n"
        "jal   func_80011A3C\n"
        "1:\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_80128678.h"


extern void func_80128564(void);

// @class: other
// @unstuck(P36): none — MATCH (handwritten full inline-asm scratchpad-stack-switch wrapper w/ branch)
/*
 * HANDWRITTEN scratchpad-stack-switch dispatcher (same idiom as func_80128564 /
 * the func_8014ED28 family): repoints $sp into the D-cache scratchpad stack held
 * at *(0x1F8003FC), calls func_800D19F0, stashes its $v0 result through D_801C83AC,
 * restores $sp, then dispatches on the stored value:
 *   if (D_801C83AC != 0)  { func_8001903C(); func_80018FC8(); }
 *   else                  { func_8014607C(); <scratchpad-switch> func_801287B8(); }
 * Manipulating $sp is not expressible in C; full inline asm (manages its own frame).
 *
 * NOTE (maspsx --aspsx-version=2.56): the inline ".set noreorder" is written with a
 * SPACE, so maspsx's own is_reorder tracker stays True and it auto-fills EVERY
 * jal/j/branch delay slot with a nop (GNU as honors noreorder and adds none). So do
 * NOT write explicit delay-slot nops after jal/j/bne — that yields a double nop.
 * bnez is written as `bne $v0,$zero` so maspsx recognizes it (bnez isn't in its
 * branch set). The load-delay nop after `lw $v0,%lo(...)($v0)` is auto-inserted too.
 * %hi/%lo escaped as %%hi/%%lo (bare % is an operand placeholder).
 */
void func_80128714(void) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_800D19F0\n"
        "lui   $at, %%hi(D_801C83AC)\n"
        "sw    $v0, %%lo(D_801C83AC)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C83AC)\n"
        "lw    $v0, %%lo(D_801C83AC)($v0)\n"
        "bne   $v0, $zero, 1f\n"
        "jal   func_8014607C\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_801287B8\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "j     2f\n"
        "1:\n"
        "jal   func_8001903C\n"
        "jal   func_80018FC8\n"
        "2:\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}




// @class: remat
// @unstuck(P36): none — MATCH (62 ins). D_801C9A78 read needed the address REMATERIALIZED
//   (lui;addiu;lw 0(reg), not the folded lui;lw %lo) AND pinned to $a0. volatile forces the
//   remat; register __asm__("$4") forces the a0 allocation (gcc otherwise picks v0). Both levers
//   required — pin-alone folds, volatile-alone lands in v0.


extern void func_80129CF8(void);
extern void func_8017849C(void);
extern void func_8014FDF4(struct S8014FDF4 *a0);
extern s32 func_801505FC(s32 a0);
extern s32 func_801508B4(s32);
extern void func_80165E90(void);
extern void func_801627E8(void);
extern void func_80162B1C(void);
extern void func_80165CA0(void);
extern void func_80129010(void);
extern void func_8013CA14(void);
extern void func_800190AC(void);
extern void func_8012956C(void);
extern s32 func_8016E95C();
extern void func_801754A8(void);
extern void func_8013BC7C();
extern void func_8013BCDC(void);
extern void func_801379FC(void);
extern void func_8001212C(void);

void func_801287B8(void) {
    extern s32 D_80126B58;
    extern s32 D_801C9A78;
    extern u16 D_800B99DA;
    extern u8 D_800B9A64;
    func_80129CF8();
    func_8017849C();
    ((void (*)(void *))func_8014FDF4)(&D_80126B58);
    ((void (*)(void *))func_801505FC)(&D_80126B58);
    func_801508B4(&D_80126B58);
    func_80165E90();
    func_801627E8();
    func_80162B1C();
    func_80165CA0();
    func_80129010();
    func_8013CA14();
    func_800190AC();
    func_8012956C();
    func_8016E95C();
    func_801754A8();
    {
        s32 *p = &D_801C9A78;

        if (*p == 0) {
            ((void (*)(void *))func_8013BC7C)(p);
        }
    }
    func_8013BCDC();
    func_801379FC();
    D_800B99DA++;
    if (D_800B9A64 != 0) {
        func_8001212C();
    }
}




extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_801288B0(void) {

    extern s32 D_801C7200;
    extern u8 D_800AEFD0;
    func_8001ABBC(0, 0, &D_800AEFD0, D_801C7200, 0);
}



// @class: remat
// @unstuck(P36): none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x60 store AND arg5; writing D_800C7C60=0x60 directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.


extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int func_801288E8(int arg0)
{

    extern int D_800C7C60;
    extern int *D_800C7C64;
    extern int D_800A2E20;
    extern int D_800AF558;
    extern int D_801C7200;
    int *p = &D_800C7C60;
    *p = 0x60;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AF558, D_801C7200, p);
}



// @class: remat
// @unstuck(P36): none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x5e store AND arg5; writing D_800C7C60=0x5e directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.


extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int func_80128940(int arg0)
{

    extern int D_800C7C60;
    extern int *D_800C7C64;
    extern int D_800A2E20;
    extern int D_800AF560;
    extern int D_801C7200;
    int *p = &D_800C7C60;
    *p = 0x5e;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AF560, D_801C7200, p);
}


extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_80128998(void)
{
    extern int D_800C7C60;
    extern int *D_800C7C64;
    extern int D_800A2E20;
    extern int D_800AECB0;
    extern s32 D_801C7200;

    int *p = &D_800C7C60;
    *p = 13;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AECB0, D_801C7200, p);
}




extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_801289F0(void) {

    extern s32 D_801C7200;
    extern u8 D_800AECB8;
    func_8001ABBC(0, 0, &D_800AECB8, D_801C7200, 0);
}


extern void func_80011B7C(int);
extern void func_80011C10(void);

void func_80128A28(void) {

    extern u16 D_800B99F6;
    extern s16 D_800B9A00;
    extern M2C_UNK (*D_80183BE0)();
    extern s16 (*D_80183BE4)();
    s16 temp_v0;

    switch (D_800B99F6) {                           /* irregular */
    case 1:
        D_80183BE0();
        /* fallthrough */
    case 0:
        func_80011C10();
        return;
    case 2:
        temp_v0 = D_80183BE4();
        if (temp_v0 != 0) {
            if (temp_v0 < 0) {
                func_80011B7C(0);
                D_800B9A00 = 1;
                return;
            }
            func_80010DE0();
        } else {
            return;
        }
        break;
    }
}


extern void func_80011B7C(int);
extern void func_80011C10(void);
extern void func_8002AEF8(void);
extern void func_800CFBBC(void);

void func_80128AF4(void) {

    extern u16 D_800B99F6;
    extern M2C_UNK (*D_80183BEC)();
    extern s32 (*D_80183BF0)();
    extern s32 D_801C83A8;
    switch (D_800B99F6) {                           /* irregular */
    case 0:
        D_801C83A8 = func_8002AF08();
        func_80011C10();
        return;
    case 1:
        D_80183BEC();
        func_80011C10();
        return;
    case 2:
        if ((D_80183BF0() << 0x10) != 0) {
            if (D_801C83A8 == 1) {
                if (func_800CFBE8() != 0) {
                    func_800CFBBC();
                    func_80011B7C(0x13);
                } else {
                    func_80011B7C(4);
                }
            } else {
                func_80010DE0();
            }
            func_8002AEF8();
        }
        return;
    }
}


#include "../shared/ov/func_80128C14.h"




extern CdFileLoc cdFileLocTable[];
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_80128C98(s32 arg0) {

    extern s16 D_80183EBC[];
    extern s32 D_801C7200;
    s16 idx = D_80183EBC[arg0];

    if (idx >= 0) {
        func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[idx], D_801C7200, 0);
    } else {
        return 1;
    }
}




extern CdFileLoc cdFileLocTable[];
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_80128CFC(s32 arg0) {

    extern s16 D_80183ECC[];
    extern s32 aD801C7200_80128CFC __asm__("D_801C7200");
    s16 idx = D_80183ECC[arg0];

    if (idx >= 0) {
        func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[idx], aD801C7200_80128CFC, 0);
    } else {
        return 1;
    }
}


#include "../shared/ov/func_80128D60.h"


#include "../shared/ov/func_80128DB4.h"


#include "../shared/ov/func_80128EA8.h"


#include "../shared/ov/func_80128ED8.h"



void func_80128FAC(u16 *arg0) {

    extern M2C_UNK D_801C7204;
    func_8001534C(4, &D_801C7204, 0x80, 0x90, 0, 0);
    func_800153CC(5, *arg0, 0xA8, 0x90, 0x40, 0);
}


#include "../shared/ov/func_80129010.h"


#include "../shared/ov/func_801290DC.h"


#include "../shared/ov/func_8012913C.h"


#include "../shared/ov/func_801291C0.h"


#include "../shared/ov/func_80129220.h"


#include "../shared/ov/func_80129248.h"


#include "../shared/ov/func_80129258.h"


#include "../shared/ov/func_8012927C.h"


#include "../shared/ov/func_801292C8.h"


#include "../shared/ov/func_8012931C.h"


#include "../shared/ov/func_80129350.h"


#include "../shared/ov/func_80129374.h"


#include "../shared/ov/func_80129398.h"


#include "../shared/ov/func_80129428.h"


#include "../shared/ov/func_8012943C.h"


#include "../shared/ov/func_8012944C.h"






extern void func_801299C8();
extern void func_80015B6C(s32, s16, s32, s16, s32, s32, s32, s32, s32, s32);
extern void GsSortBg(s32 *, void *, u16, s32 *);
extern void GsSortFastBg(s32 *, void *, u16, s32 *);

void func_8012956C(void) {

    extern s32 D_801C83AC;

    extern s16 D_80114EE0;
    extern u8 D_800B9A78;
    extern u8 D_801C83AD[];
    extern u8 D_801C83AE[];
    extern u8 D_801C83B0[];
    extern u8 D_801C83B1[];
    extern u8 D_801C83B2[];
    extern u8 D_801C9A58;
    extern u8 D_800AF630[];
    extern u8 D_800A6518[];
    s32 *sp10;
    u8 *afbase;
    s32 *sp0;
    Ent_956C *base;
    s32 i;

    sp10 = (s32 *)0x1F800010;
    sp0 = (s32 *)0x1F800000;
    afbase = (u8 *)&D_800AF630;
    if (D_80114EE0 == 0) {
        return;
    }
    base = (Ent_956C *)&D_800B9A78;
    i = 0;
    do {
        s32 idx = i * 8 + 4;
        switch (base->f34) {
        case 0x7FFF:
            break;
        case 0x7FFD:
            if (i == 0) {
                func_801299C8(D_801C9A58, 1, base);
            }
            func_80015B6C(-0xA0, -0x74, 0x140, 0x8C,
                          D_801C83B0[0], D_801C83B0[1], D_801C83B0[2],
                          D_801C83B0[4], D_801C83B0[5], D_801C83B0[6]);
            func_80015B6C(-0xA0, 0x18, 0x140, 0x3C,
                          D_801C83B0[4], D_801C83B0[5], D_801C83B0[6],
                          D_801C83B0[8], D_801C83B0[9], D_801C83B0[0xA]);
            func_80015B6C(-0xA0, 0x54, 0x140, 0x28,
                          D_801C83B0[8], D_801C83B0[9], D_801C83B0[0xA],
                          D_801C83B0[0xC], D_801C83B0[0xD], D_801C83B0[0xE]);
            break;
        case 0x7FFE:
            func_801299C8(D_801C9A58, (s16)(i * 2), base);
            func_80015B6C(-0xA0, *(s16 *)&base->f3A, 0x140, base->f3E,
                          ((u8 *)&D_801C83AC)[idx], D_801C83AD[idx], D_801C83AE[idx],
                          D_801C83B0[idx], D_801C83B1[idx], D_801C83B2[idx]);
            break;
        default:
            base->f1C = base->f40 + base->f38;
            base->f1E = base->f42 + base->f3A;
            func_801299C8(D_801C9A58, (s16)(i + 3), base);
            *(Blk16_956C *)sp0 = *(Blk16_956C *)base;
            {
                s32 *dst = sp10;
                s32 *src = (s32 *)((u8 *)base + 0x10);
                s32 *end = (s32 *)((u8 *)base + 0x30);
                do {
                    *(Blk16_956C *)dst = *(Blk16_956C *)src;
                    src += 4;
                    dst += 4;
                } while (src != end);
                *dst = *src;
                sp10[5] = (s32)sp0;
                if (base->f36 == 0) {
                    GsSortFastBg(sp10, &D_800A6518[(*(u16 *)(afbase + 0xA3D2)) * 0x14], base->f34, dst);
                } else {
                    GsSortBg(sp10, &D_800A6518[(*(u16 *)(afbase + 0xA3D2)) * 0x14], base->f34, dst);
                }
            }
            break;
        }
        base += 1;
        i += 1;
    } while (i < 2);
}


#include "../shared/ov/func_801298F4.h"





// @class: schedule
// @unstuck(P36): none — MATCH (158 ins, match_one relocation-masked)
//
// Levers that landed it (2 iterations, 56 mismatched -> MATCH):
//  1. §43 K&R s16-param definition: `void f(a0,a1,a2) s16 a0; s16 a1; u8 *a2;` reproduces the
//     in-place `sll $a0,$a0,16` zero-test on the arg reg + the raw-$a1 copy (`addu $a3,$a1,$zero`)
//     stashed in the jtbl branch delay slot and RE-extended per use in the case body.
//  2. §18 array-of-struct %lo-fold: three sibling extern arrays D_801C83B0/1/2[] (a 4-row x 3-comp
//     RGB gradient table, stride 4) give `lui $at,%hi(sym); addu $at,$at,idx4; sb $v0,%lo(sym)($at)`
//     for the indexed case and plain `lui/sb %lo(sym+k)` for the constant-index case.
//  3. Switch CASE-ORDER = source order: the jump table dispatches case 1 to the FIRST emitted block,
//     so `case 1:` must be written before `case 0/2:` and `case 3/4:`.
//  4. THE residual (56 -> 0): the case-1 body must be written ROW-MAJOR (BE0[0],BE1[0],BE2[0],
//     BE0[4],BE1[4],BE2[4],...), i.e. the natural table fill. gcc-2.7.2's sched pass then REORDERS
//     the stores itself (BE0,BE1,BE5,BE8,BE4,BEC,BE9,BED,BE2,BE6,BEA,BEE) because the three arrays
//     are distinct declarations => provably non-aliasing. Writing the source in the target's STORE
//     order is the trap: it pins the b*255 / r*143 CSEs at their late store sites instead of letting
//     them hoist into $a0/$v1 at rows 0/1, and mis-schedules the D_801C9978 load.
//  5. Shift signedness: `u32` component locals give `srl` for r*5>>3 and g*25>>1; an explicit
//     `(s32)(x * 255) >> 4` gives `sra` for the *255 / *143 / *45 terms (mixed within one block).

extern u8 D_801C9A72;
extern u8 D_801C999A;
extern u8 D_801C9978;
extern u8 D_801C83B0[];
extern u8 D_801C83B1[];
extern u8 D_801C83B2[];

void func_801299C8(arg0, arg1, arg2)
s16 arg0;
s16 arg1;
u8 *arg2;
{
    u32 r;
    u32 g;
    u32 b;
    s32 i;

    if (arg0 != 0) {
        switch (arg1) {
        case 1:
            r = D_801C9A72;
            g = D_801C999A;
            b = D_801C9978;
            D_801C83B0[0] = r * 5 >> 3;
            D_801C83B1[0] = g << 3;
            D_801C83B2[0] = (s32)(b * 255) >> 4;
            D_801C83B0[4] = (s32)(r * 143) >> 4;
            D_801C83B1[4] = g * 25 >> 1;
            D_801C83B2[4] = (s32)(b * 255) >> 4;
            D_801C83B0[8] = (s32)(r * 255) >> 4;
            D_801C83B1[8] = (s32)(g * 255) >> 4;
            D_801C83B2[8] = (s32)(b * 255) >> 4;
            D_801C83B0[12] = (s32)(r * 143) >> 4;
            D_801C83B1[12] = (s32)(g * 255) >> 4;
            D_801C83B2[12] = (s32)(b * 45) >> 2;
            break;
        case 0:
        case 2:
            i = arg1 * 4;
            D_801C83B0[i] = arg2[0x44] * D_801C9A72 >> 4;
            D_801C83B1[i] = arg2[0x45] * D_801C999A >> 4;
            D_801C83B2[i] = arg2[0x46] * D_801C9978 >> 4;
            i = (arg1 + 1) * 4;
            D_801C83B0[i] = arg2[0x47] * D_801C9A72 >> 4;
            D_801C83B1[i] = arg2[0x48] * D_801C999A >> 4;
            D_801C83B2[i] = arg2[0x49] * D_801C9978 >> 4;
            break;
        case 3:
        case 4:
            arg2[0x20] = D_801C9A72 << 3;
            arg2[0x21] = D_801C999A << 3;
            arg2[0x22] = D_801C9978 << 3;
            break;
        }
    }
}

#include "../shared/ov/func_80129C40.h"


#include "../shared/ov/func_80129CF8.h"


#include "../shared/ov/func_80129FF4.h"


#include "../shared/ov/func_8012A018.h"


#include "../shared/ov/func_8012A048.h"


#include "../shared/ov/func_8012A094.h"


#include "../shared/ov/func_8012A0E0.h"


#include "../shared/ov/func_8012A100.h"


#include "../shared/ov/func_8012A110.h"





// @class: regalloc-order
// @unstuck(P36): none — MATCH (78 ins, relocation-masked). Register pins ($2-$5 reused for
//   the D_x200-x20C words then the D_x220-x226 halfwords; $6-$10 held across for the
//   D_x228/x22A/x294/x298/x29A tail) force the frameless 9-deep allocation the default
//   -O2 pre-reload scheduler otherwise blows to a 3-reg spill (all 720 stmt orders spill
//   without the pins). A single zero-byte scheduling/memory barrier after the 4 word
//   stores stops gcc hoisting the first 8-byte block copy above them.




#include "../shared/ov/func_8012A1BC.h"


#include "../shared/ov/func_8012A2F4.h"


#include "../shared/ov/func_8012A304.h"










#include "../shared/ov/func_8012A328.h"


#include "../shared/ov/func_8012A418.h"


#include "../shared/ov/func_8012A464.h"


#include "../shared/ov/func_8012A4BC.h"


extern void func_8012A598(void *a0);
#include "../shared/ov/func_8012A568.h"


#include "../shared/ov/func_8012A598.h"


#include "../shared/ov/func_8012A5F8.h"


#include "../shared/ov/func_8012A62C.h"


#include "../shared/ov/func_8012A68C.h"


#include "../shared/ov/func_8012A6D0.h"


#include "../shared/ov/func_8012A758.h"


#include "../shared/ov/func_8012A79C.h"


#include "../shared/ov/func_8012A7D4.h"


#include "../shared/ov/func_8012A828.h"


#include "../shared/ov/func_8012A860.h"


#include "../shared/ov/func_8012A8B0.h"


#include "../shared/ov/func_8012A8E8.h"


#include "../shared/ov/func_8012A908.h"


#include "../shared/ov/func_8012A988.h"



extern void func_8012AAAC(void *arg0);

#include "../shared/ov/func_8012AAAC__t6631232b.h"



extern void func_8012AAAC();

void func_8012ACA0(void *arg0) {

    extern M2C_UNK D_80183F38;
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_80183F38;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s16 *, 0x9A) = 0;
    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
    ((void (*)(void))func_8012AAAC)();
}




// @class: iv-combine
// @unstuck(P36): none — MATCH (25 ins). Array-subscript induction o->list[i] fixes preheader hoist order + loop-top load-delay nop; scattered case labels force the jump table (gcc merges contiguous same-target cases, so 6+ non-contiguous nodes needed for the density heuristic).
      /* 8-byte element, cmd @ +4 */
    /* list ptr @ +0x90 */

#include "../shared/ov/func_8012ACE0__t7ff3c5c3.h"

#include "../shared/ov/func_8012AD44.h"


#include "../shared/ov/func_8012AD50.h"




#include "../shared/ov/func_8012AD64.h"


#include "../shared/ov/func_8012AD6C.h"


#include "../shared/ov/func_8012AD80.h"


#include "../shared/ov/func_8012ADE4.h"


#include "../shared/ov/func_8012AE00.h"


#include "../shared/ov/func_8012AF0C.h"


#include "../shared/ov/func_8012B030.h"


#include "../shared/ov/func_8012B0B4.h"


#include "../shared/ov/func_8012B14C.h"


#include "../shared/ov/func_8012B178.h"


#include "../shared/ov/func_8012B1B4.h"


#include "../shared/ov/func_8012B200.h"


#include "../shared/ov/func_8012B21C.h"


#include "../shared/ov/func_8012B23C.h"


#include "../shared/ov/func_8012B260.h"


#include "../shared/ov/func_8012B2CC.h"


#include "../shared/ov/func_8012B370.h"


#include "../shared/ov/func_8012B414.h"


#include "../shared/ov/func_8012B4B8.h"


#include "../shared/ov/func_8012B608.h"


#include "../shared/ov/func_8012B6D4.h"


#include "../shared/ov/func_8012B70C.h"


#include "../shared/ov/func_8012B744.h"


#include "../shared/ov/func_8012B77C.h"


#include "../shared/ov/func_8012B864.h"


#include "../shared/ov/func_8012B8A4.h"


#include "../shared/ov/func_8012B8E4.h"


#include "../shared/ov/func_8012BA10.h"


#include "../shared/ov/func_8012BB3C.h"


#include "../shared/ov/func_8012BC60.h"


#include "../shared/ov/func_8012BCCC.h"


#include "../shared/ov/func_8012BD14.h"


#include "../shared/ov/func_8012BD3C.h"


#include "../shared/ov/func_8012BDBC.h"


#include "../shared/ov/func_8012BE54.h"


#include "../shared/ov/func_8012BE98.h"


#include "../shared/ov/func_8012BEE8.h"


#include "../shared/ov/func_8012BF10.h"



void func_8012BF4C(s32 *a0, s32 a1) {
    *(s32*)((s32)a0 + 0x1C) = a1;
}


#include "../shared/ov/func_8012BF54.h"


#include "../shared/ov/func_8012BF68.h"


#include "../shared/ov/func_8012BF7C.h"


#include "../shared/ov/func_8012BFA8.h"


#include "../shared/ov/func_8012C044.h"


#include "../shared/ov/func_8012C098.h"


#include "../shared/ov/func_8012C0EC.h"


#include "../shared/ov/func_8012C194.h"


#include "../shared/ov/func_8012C1B8.h"


#include "../shared/ov/func_8012C1DC.h"


#include "../shared/ov/func_8012C218.h"


#include "../shared/ov/func_8012C284.h"


#include "../shared/ov/func_8012C2D0.h"


#include "../shared/ov/func_8012C31C.h"


#include "../shared/ov/func_8012C354.h"


#include "../shared/ov/func_8012C438.h"


#include "../shared/ov/func_8012C51C.h"


#include "../shared/ov/func_8012C588.h"


#include "../shared/ov/func_8012C658.h"


#include "../shared/ov/func_8012C724.h"


#include "../shared/ov/func_8012C750.h"


#include "../shared/ov/func_8012C820.h"


            typedef struct { s8 c[8]; } Blk8_8012C890;

// @class: schedule
// @unstuck(P36): none — MATCH (149 ins). Counter (*(u16 *)&D_801270C4): gcc CSE's the two reads (store to
//   dst+0x36 assumed non-aliasing the global) AND folds %lo per-access — target instead RELOADS
//   and keeps &(*(u16 *)&D_801270C4) in one reg. Fix = pin a `u16*` to $v1 (register asm "$3"), read via
//   `*(volatile u16*)pc` (defeats CSE -> 2 loads) but STORE via plain `*pc` (non-volatile store
//   schedules store-before-sll, no extra `move`). count is s16 so `count==0` -> `sll 16;bnez`.
//   else-block obj must be a BLOCK-LOCAL (gcc then picks $a1, not the shared if-branch $a0).

extern void  func_80016714(void *a0, s32 a1);

s32 func_8012C890(s32 a0, s32 a1, s32 a2) {

    extern s32   D_8018741C;
    extern s16 D_801270C4;
    extern u16   D_801274E4[];
    extern s32   D_8011DB08;
    u8 *src = (u8 *)a0;
    u8 *dst = (u8 *)a1;
    u16 *d;
    s16 count;
    u16 v2, v4;
    s32 v10;
    void *obj;

    *(u16 *)(dst + 0x0)  = *(u16 *)(src + 0x6);
    v2 = *(u16 *)(src + 0x0);
    *(u16 *)(dst + 0x6)  = v2;
    *(u16 *)(dst + 0x88) = v2;
    v2 = *(u16 *)(src + 0x2);
    *(u16 *)(dst + 0xA)  = v2;
    *(u16 *)(dst + 0x8A) = v2;
    v4 = *(u16 *)(src + 0x4);
    *(u16 *)(dst + 0xC)  = 0;
    *(u16 *)(dst + 0x8)  = 0;
    *(u16 *)(dst + 0x4)  = 0;
    *(u16 *)(dst + 0xE)  = v4;
    *(u16 *)(dst + 0x8C) = v4;
    *(u16 *)(dst + 0x70) = *(u16 *)(src + 0x8);
    *(u16 *)(dst + 0x72) = *(u16 *)(src + 0xA) & 0xF7FF;
    *(u16 *)(dst + 0xFC) = *(u16 *)(src + 0xE);
    v10 = *(s32 *)(src + 0x10);
    *(s32 *)(dst + 0x78) = (s32)&D_8018741C;
    *(s32 *)(dst + 0xDC) = v10;

    {
        u16 *pc;
        pc = &(*(u16 *)&D_801270C4);
        *(u16 *)(dst + 0x36) = *(u16 *)pc;
        count = *(volatile u16 *)pc + 1;
        *pc = count;
        if (count == 0) {
            *pc = 1;
        }
    }

    if (a2 != 0) {
        *(s32 *)(dst + 0x64) = a2;
        *(s32 *)(dst + 0x68) = 0;
    } else {
        *(s32 *)(dst + 0x64) = 0;
        *(s32 *)(dst + 0x68) = (s32)src;
    }

    *(u16 *)(src + 0xA) |= 0x8000;
    *(u16 *)(dst + 0x2) = 0;
    d = D_801274E4;
    *d &= 0xFFFE;
    (*(void (**)(void *))(D_8011DB08 + *(u16 *)(dst + 0x0) * 4))(dst);

    if (*d & 1) {
        s32 a1v;
        obj = *(void **)(dst + 0x20);
        if (obj != 0) {
            s32 t = *(u16 *)obj;
            if (t != 1) {
                if (t != 2) {
                    goto done;
                }
                a1v = 0x38;
            } else {
                a1v = 0x84;
            }
            func_80016714(obj, a1v);
        done:;
        }
        func_80016714(dst, 0x10C);
        *(u16 *)(src + 0xA) &= 0x7FFF;
        return 0;
    }

    if (*(s32 *)(dst + 0x64) == 0) {
        void *o = *(void **)(dst + 0x20);
        if (o == 0) {
            return (s32)dst;
        }
        if (*(u16 *)o == 1) {
            s16 c = *(s16 *)(src + 0xC);
            if (c != 0x7FFF) {
                *(s16 *)((u8 *)o + 0x12) = c;
            }
        }
    }
    if (*(s32 *)(dst + 0x20) != 0) {
        *(u16 *)(*(s32 *)(dst + 0x20) + 0x8) = *(u16 *)(dst + 0x6) + *(u16 *)(dst + 0x50);
        *(u16 *)(*(s32 *)(dst + 0x20) + 0xA) = *(u16 *)(dst + 0xA) + *(u16 *)(dst + 0x52);
        *(u16 *)(*(s32 *)(dst + 0x20) + 0xC) = *(u16 *)(dst + 0xE) + *(u16 *)(dst + 0x54);
    }
    return (s32)dst;
}


#include "../shared/ov/func_8012CAE4.h"


#include "../shared/ov/func_8012CB64.h"


#include "../shared/ov/func_8012CBA4.h"


#include "../shared/ov/func_8012CBCC.h"


#include "../shared/ov/func_8012CBF4.h"


#include "../shared/ov/func_8012CC1C.h"


#include "../shared/ov/func_8012CC40.h"


#include "../shared/ov/func_8012CC64.h"




#include "../shared/ov/func_8012CC88.h"


#include "../shared/ov/func_8012CE2C.h"


#include "../shared/ov/func_8012CEB0.h"


#include "../shared/ov/func_8012CFA8.h"


#include "../shared/ov/func_8012D098.h"


#include "../shared/ov/func_8012D38C.h"


void func_8012D3AC(void) {
}

#include "../shared/ov/func_8012D3B4.h"


#include "../shared/ov/func_8012D4B4.h"


void func_8012D5DC(void) {
}

#include "../shared/ov/func_8012D5E4.h"


#include "../shared/ov/func_8012D624.h"




int func_8012D664(int arg0, int arg1, int arg2)
{
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern s32 func_800132BC(s32 a0, s32 a1);
    extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
    extern u8 D_80183F48[];

    u16 s[3];
    int ret;
    int t;

    s[0] = (*(unsigned short *)&D_80126B5E);
    s[1] = (*(unsigned short *)&D_80126B62) - 0x40;
    s[2] = (*(unsigned short *)&D_80126B66);
    ret = ((int (*)())func_800132BC)(arg0, s);
    t = arg1 + 0x20;
    if (ret < t * t) {
        func_8012F568(1, 1, 0, arg2, arg0, &D_80183F48);
        return 1;
    }
    return 0;
}


#include "../shared/ov/func_8012D714.h"




extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);

s32 func_8012DB84(void)
{

    extern M2C_UNK D_80183F50;
    extern M2C_UNK D_80183F58;
    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, &D_80183F50, &D_80183F58);
}


#include "../shared/ov/func_8012DBD0.h"




// @class: regalloc-order
// @unstuck(P36): none — MATCH




s32 func_8012DDA4()
{

    extern u8 D_80126720[];
    extern Entry_8012DDA4 * D_801C83CC;
    extern Entry_8012DDA4 * D_801C83C8;

    Entry_8012DDA4 *p;
    Entry_8012DDA4 *end = ((Entry_8012DDA4 *)D_80126720);

    while (D_801C83CC != end) {
        p = D_801C83CC;
        if (p->active != 0 && p != D_801C83C8) {
            D_801C83CC = p + 1;
            return p;
        }
        D_801C83CC++;
    }
    D_801C83CC = 0;
    return 0;
}




// @class: plumbing
// @unstuck(P36): none — MATCH (35/35 ins, relocation-masked)


s32 func_8012DE2C(s32 a0) {

    extern u8 D_801202A0[];
    extern u8 * D_801C83CC;
    extern u8 * D_801C83C8;

    u8 *base;
    u8 *end;
    u8 *p;

    base = D_801202A0;
    end = base + 0x6480;
    D_801C83CC = base;
    D_801C83C8 = ((u8 *)a0);

    while (D_801C83CC != end) {
        p = D_801C83CC;
        if (*(u16 *)p != 0 && p != ((u8 *)a0)) {
            D_801C83CC = p + 0x10C;
            return p;
        }
        D_801C83CC += 0x10C;
    }
    D_801C83CC = 0;
    return 0;
}


#include "../shared/ov/func_8012DEB8.h"


#include "../shared/ov/func_8012DF34.h"


#include "../shared/ov/func_8012DFBC.h"


void func_8012DFCC(void) {
}

#include "../shared/ov/func_8012DFD4.h"


#include "../shared/ov/func_8012E014.h"


#include "../shared/ov/func_8012E138.h"



s32 func_8012E27C(void) {
    return 1;
}


void func_8012E284(void) {
}

#include "../shared/ov/func_8012E28C.h"


#include "../shared/ov/func_8012E32C.h"


            typedef struct { s8 c[8]; } Blk8_8012E364;

/* func_8012E364 (ov_SC01_077_jr_8012ACE0) — MATCH, 67/67 ins, 0 mismatched (reloc-masked).
 *
 * Verified:
 *   python3 tools/match_one.py func_8012E364 --c .run/near6/wave23/func_8012E364.c \
 *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8012ACE0
 *   -> MATCH (67 ins)  func_8012E364
 *
 * Symbols: sig_hints listed no callees and no data decls for this fn, so the three externs below
 * are derived from the asm's %hi/%lo pairs:
 *   D_80126CE0  -> `lh`  (0x8012E370)  => s16
 *   D_801C83C0  -> `lw`/`sw`           => s32
 *   D_801C83C4  -> `lw`/`sw`           => s32
 * D_80126CE0 is already declared `extern s16 D_80126CE0;` inside ov_SC03_099_jr_8016AB6C.c etc.,
 * so the s16 typing is consistent with the rest of the tree.
 *
 * ---------------------------------------------------------------------------------------------
 * HOW THE LAST 7 SLOTS CAME OFF (wave22 plateaued here at closeness 7; that header's
 * "genuine regalloc hard tail / not C-expressible" verdict was WRONG on both clusters).
 *
 * CLUSTER B - idx 59-62 (`nop`/`negu $v1,$v1` vs `addu $v0,$v1,$zero`/`negu $v0,$v0`): 7 -> 3.
 *   NOT a delay-slot (dbr) residual at all. `mips.md:1526 abssi2` is a 3-instruction `multi`
 *   template that emits its OWN branch AND fills its OWN slot:
 *       REGNO(op0) == REGNO(op1):  "bgez %1,1f%#\n\tsubu %0,%z2,%0\n1:"     (slot -> maspsx nop)
 *       REGNO(op0) != REGNO(op1):  "%(bgez %1,1f\n\tmove %0,%1\n\tsubu %0,%z2,%0\n1:%)"
 *   The target IS the second form (`.set noreorder` + `move` in the slot). So the whole residual
 *   was one question: does the abs DEST get a different hard reg from its SOURCE?
 *   Two edits, both required:
 *     (a) spell the abs as `__builtin_abs(v)` so a real `(abs:SI ...)` insn exists. A hand-rolled
 *         `d = v; if (d<0) d = -d;` is equivalent (cse folds it to the same abs insn - the wave22
 *         draft was ALREADY going through abssi2, it just hit the dest==src arm), but a
 *         `(v<0) ? -v : v` ternary does NOT fold here: 68 ins, 19 off.
 *     (b) PIN the abs result to $2. Unpinned, local-alloc's combine_regs (K8) ties the abs dest
 *         into its dying input `v` -> REGNO(op0)==REGNO(op1) -> the nop form. Measured: the same
 *         file with `s32 d;` instead of the pin is 5 off; with the pin, 3 off.
 *   (Rejected on measurement: `d = v; asm("" :: "r"(v))` dead-read to break the tie = 68 ins/13;
 *    RC-12 `$0`-add opaque copy = 9; pinning d to $3 = 5.)
 *
 * CLUSTER A - idx 43-45 (the D_801C83C4 load vs the 0x20($a2) load, swapped): 3 -> MATCH.
 *   Pure sched1 rank, and it IS steerable (sched.md S2, the birthing boost). The `.i.sched` dump
 *   of the wave22 draft says it outright:
 *       ;; insn[ 104]: priority = 1     (prev = D_801C83C4)
 *       ;; insn[ 107]: priority = 1     (a    = *(arg0+0x20))
 *       ;; ready list at T-17: 107 (1) 104 (7f000001), now 104 107
 *   Equal base priority, but 104 carries the `adjust_priority`/`birthing_insn_p` boost
 *   (sched.c:2506/2469 - `reg_n_sets[dest] == 1`) and 107 does NOT, because wave22 reused ONE
 *   variable `a` for four roles (hint value, division result, both tail entity loads) -> 4 sets.
 *   Backward scheduling means picked-first = placed-LAST, so the boosted 104 got pushed BELOW 107.
 *   Fix: give each tail entity load its own single-set local (`e1`, `e2`). Now both loads are
 *   boosted, the rank falls through to `rank_for_schedule`'s LUID tie-break (sched.c:2427,
 *   "highest LUID first" = ascending source order forward) and the two loads come out in
 *   statement order = the target order.
 *   NB the wave22 header's claim "splitting `a` regresses 2 slots" only applies to splitting the
 *   FIRST two roles (hint value / division result) - those must stay one multi-set cross-block
 *   variable. Splitting only the TAIL roles is what pays.
 *
 * LOAD-BEARING constructs (do not "simplify"):
 *  1. `spd` - a local holding 0x1000 SET BEFORE the if/else chain, so the constant lives in a
 *     pseudo across the branch: `addiu $a3,$zero,0x1000` in the `blez` slot at 0x8012E3DC and the
 *     `sw $a3` / `addu $v1,$v1,$a3` forms at L8012E410.
 *  2. `a` reused for the D_80126CE0 value AND the division result (multi-set, cross-block) - that
 *     is what puts the quotient in $a0 (`subu $a0,$v0,$v1`) instead of coalescing into $v0.
 *  3. `flags` pinned to $2 (dropping it = 13 off) and `prev` pinned to $5 (dropping it = 6 off).
 *  4. `d` pinned to $2 - see CLUSTER B(b).
 *  5. `e1`/`e2` must be SEPARATE single-set locals - see CLUSTER A.
 *  The `arg0` $6 pin is NOT load-bearing any more (verified: still MATCH without it); it is kept
 *  because it costs nothing and documents the target's `addu $a2,$a0,$zero`.
 */

void func_8012E364(s32 arg0_)
{

    extern s16 D_80126CE0;
    extern s32 D_801C83C0;
    extern s32 D_801C83C4;
    s32 arg0;
    s32 prev;
    register u16 flags __asm__("$2");  // !FAKE: pin $2 — holds $2 across the D_801C83C0 chain, so the $2 suggestion d's pin gives v (local-alloc.c:1822) fails in block_alloc's suggested-reg pass (:1472) (P36 S103 c51 minimum-lever)
    s32 a;
    s32 diff;
    s32 v;
    register s32 d __asm__("$2");  // !FAKE: pin $2 — combine_regs (local-alloc.c:1722) otherwise ties d into v, which dies at the abs: abssi2 dest==src arm, nop for move (P36 S103 c51 minimum-lever)
    s32 spd;
    s32 e1;
    s32 e2;

    arg0 = arg0_;
    *(s16 *)(arg0 + 0x5C) = 0;
    a = D_80126CE0;
    if (a == 0) {
        D_801C83C0 = 0x1000;
        D_801C83C4 = 0x1000;
    }
    a = ((0x90 - a) << 12) / 0x90;
    *(s32 *)(arg0 + 0x1C) += 1;
    spd = 0x1000;

    diff = D_801C83C0 - a;
    if (diff > 0) {
        D_801C83C0 -= diff >> 2;
    } else if (diff < 0) {
        D_801C83C0 += (-diff) / 4;
    }

    prev = D_801C83C4;
    e1 = ((s32 *)arg0)[8];
    v = D_801C83C0 - prev + spd;
    D_801C83C4 = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_801C83C0 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;
    e2 = ((s32 *)arg0)[8];
    d = __builtin_abs(v);
    *(s16 *)(e2 + 0x1C) = d;
    *(s16 *)(e2 + 0x18) = d;
    *(s16 *)(((s32 *)arg0)[8] + 0x1A) = 0x1000;
}


#include "../shared/ov/func_8012E470.h"


#include "../shared/ov/func_8012E4C8.h"


#include "../shared/ov/func_8012E504.h"


#include "../shared/ov/func_8012E544.h"


#include "../shared/ov/func_8012E57C.h"


#include "../shared/ov/func_8012E5CC.h"


#include "../shared/ov/func_8012E688.h"



#include "../shared/ov/func_8012E778.h"


#include "../shared/ov/func_8012E88C.h"


#include "../shared/ov/func_8012E8A8.h"


#include "../shared/ov/func_8012E8C4.h"


#include "../shared/ov/func_8012E8E0.h"




// @class: other
// @unstuck(P36): none — MATCH (branch-polarity invert: `0x78 != 0` puts compute block as fall-through)

extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);

void func_8012E9C0(int param_1)
{

    extern int D_80183F60;
    int iVar1;

    if (*(short *)(param_1 + 0x60) != 0) {
        if (*(unsigned char *)(param_1 + 0x5e) == 0x1d) {
            *(short *)(param_1 + 0x82) = 0;
            *(short *)(param_1 + 0x7c) = *(unsigned short *)(param_1 + 6);
            *(short *)(param_1 + 0x7e) = *(unsigned short *)(param_1 + 0xa);
            *(short *)(param_1 + 0x80) = *(unsigned short *)(param_1 + 0xe);
        }
        if (*(int *)(param_1 + 0x78) != 0) {
            iVar1 = *(short *)(param_1 + 0x60) *
                        *(short *)(*(int *)(param_1 + 0x78) + 0x30) >> 0xc;
            if (iVar1 < 1) {
                iVar1 = 1;
            }
        } else {
            iVar1 = *(short *)(param_1 + 0x60);
        }
        func_8016AA50(param_1, iVar1);
        if ((*(unsigned short *)(param_1 + 0x82) & 1) != 0) {
            ((void (*)(int))func_8016B428)(param_1);
            func_80019064(&D_80183F60);
        }
    }
    return;
}


#include "../shared/ov/func_8012EA90.h"


#include "../shared/ov/func_8012EC04.h"


#include "../shared/ov/func_8012EECC.h"


#include "../shared/ov/func_8012EF34.h"


#include "../shared/ov/func_8012EF70.h"


            typedef struct { s8 c[8]; } Blk8_8012EFB8;

/* §37/§124 asm-label alias: the fleet canon declares this `extern void
 * func_8012EFB8(s32 a0);` inside the DEFINE_func_* macros in
 * src/shared/engine_core.h (the one at src/ov_SC01_077/ov_SC01_077_jr_8012ACE0.c:1169
 * comes from DEFINE_func_8012EF70()).  The byte-true body returns s32 and takes
 * TWO pointers, so it conflicts on BOTH the return axis and the arity axis.
 * Aliasing the C name sidesteps both with no header edit and no codegen change.
 * This declaration MUST travel with the body. */
extern s32 func_8012EFB8(void *param_1, void *param_2);

#include "../shared/ov/func_8012EFB8.h"


#include "../shared/ov/func_8012F038.h"


#include "../shared/ov/func_8012F0BC.h"


#include "../shared/ov/func_8012F14C.h"


#include "../shared/ov/func_8012F1A4.h"


#include "../shared/ov/func_8012F214.h"


#include "../shared/ov/func_8012F274.h"


#include "../shared/ov/func_8012F2E8.h"


#include "../shared/ov/func_8012F374.h"





// @class: remat
// @unstuck(P36): none — MATCH

#include "../shared/ov/func_8012F40C.h"


#include "../shared/ov/func_8012F49C.h"


#include "../shared/ov/func_8012F568.h"


#include "../shared/ov/func_8012F5F4.h"


#include "../shared/ov/func_8012F68C.h"


#include "../shared/ov/func_8012F75C.h"


#include "../shared/ov/func_8012F7B4.h"



// @class: plumbing
// @unstuck(P36): none — MATCH (pending gate)
extern void func_80131170();
extern void func_80131CA8();

void func_8012F828(int param_1)
{

    extern unsigned char D_80183F7C[];
    *(unsigned char *)(param_1 + 0xC1) = 4;
    if (*(unsigned int *)(param_1 + 0xB4) & 8) {
        func_80131170(param_1, D_80183F7C, 0xB);
    }
    func_80131CA8(param_1, 9);
}


#include "../shared/ov/func_8012F87C.h"



// @class: plumbing
// @unstuck(P36): none — MATCH (pending gate)
extern void func_80131170();
extern void func_80131CA8();

void func_8012F8C8(int param_1)
{

    extern unsigned char D_80183F88[];
    *(unsigned char *)(param_1 + 0xC1) = 7;
    if (*(unsigned int *)(param_1 + 0xB4) & 128) {
        func_80131170(param_1, D_80183F88, 0xB);
    }
    func_80131CA8(param_1, 22);
}


#include "../shared/ov/func_8012F91C.h"


#include "../shared/ov/func_8012F968.h"


#include "../shared/ov/func_8012FB54.h"


#include "../shared/ov/func_8012FC30.h"


#include "../shared/ov/func_8012FCA4.h"


            typedef struct { s8 c[8]; } Blk8_8012FCC4;

// @class: schedule
// @unstuck(P36): none — MATCH (57 ins), byte-exact via rtu_match on the real TU.
// ROOT CAUSE of the prior 3-off "irreducible schedule-steal": the wave-2 draft had the WRONG ARITY for
//   func_80131B14. It cast the call to (int,int) and passed (param_1, 0x1C), which forced `li a1,0x1C` to be
//   func_80131B14's OWN arg. That premise made the beqz-delay `li a1,0x1C` / jal-delay `move a0,s0` look like an
//   un-reorderable {li,move} schedule-steal (calls.c emits a0 first; sched2 keeps LUID; reorg swaps them).
//   THE FIX: func_80131B14 takes ONE arg — ((void(*)(int))func_80131B14)(param_1). Then:
//     - func_80131B14's own delay slot = `move a0,s0` (its a0 arg), and a1 is NOT live across it.
//     - the `li a1,0x1C` in the beqz(0x100) delay slot is the TERMINAL func_80131CA8(param_1,0x1C)'s arg, which
//       reorg fill_slots_from_thread shares into the delay slot for the beqz-taken (else) edge FOR FREE, because
//       a1 is dead on the fall-through (1-arg func_80131B14 never reads a1) so there is no resource conflict.
//   No barrier, no register pin, no schedule mutation — the correct arity makes the target schedule fall out
//   of stock gcc-2.7.2 reorg. (Lesson for the cookbook: before conceding a delay-slot "steal" as irreducible,
//   re-derive the CALLEE ARITY from the asm — a spurious extra register arg that is live across the call is what
//   blocks reorg from sharing a downstream constant into a branch delay slot.)

extern void func_80131CA8(int a0, int a1);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_80131B14(void);
extern s32 func_80131A34(s32, s32);
extern void func_8012B14C(s32 a0, s32 a1);

void func_8012FCC4(int param_1) {

    extern int  D_80183F94;
    int v1 = *(int *)(param_1 + 0xC4);
    *(char *)(param_1 + 0xC1) = 8;
    if (v1 & 2) {
        *(char *)(param_1 + 0xC1) = 1;
        func_80131CA8(param_1, 3);
        return;
    }
    if (v1 & 1) {
        ((void (*)(int, int))func_80131E00)(param_1, 1);
        return;
    }
    if (*(int *)(param_1 + 0xB4) & 0x100) {
        ((void (*)(int))func_80131B14)(param_1);
        if (*(short *)(param_1 + 0x76) <= 0) {
            ((void (*)(int, int))func_80131E00)(param_1, 0xC);
            return;
        }
        if (func_80131A34(param_1, 4) != 0) {
            *(char *)(param_1 + 0xC2) = 0;
        } else {
            *(short *)(param_1 + 0x98) = 0;
            *(char *)(param_1 + 0xC2) = 1;
        }
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_80183F94);
        *(int *)(param_1 + 0x1C) = 0;
        func_80131CA8(param_1, 0x1C);
        return;
    }
    func_80131CA8(param_1, 0x1C);
}


#include "../shared/ov/func_8012FDA8.h"


#include "../shared/ov/func_8012FE70.h"


#include "../shared/ov/func_8012FF00.h"


#include "../shared/ov/func_8012FF4C.h"


#include "../shared/ov/func_8012FF98.h"


#include "../shared/ov/func_8013001C.h"


#include "../shared/ov/func_80130088.h"


#include "../shared/ov/func_801300F4.h"


#include "../shared/ov/func_801301E8.h"


#include "../shared/ov/func_80130278.h"


#include "../shared/ov/func_80130314.h"


#include "../shared/ov/func_80130360.h"


#include "../shared/ov/func_801303A0.h"


#include "../shared/ov/func_801303EC.h"


#include "../shared/ov/func_80130438.h"


#include "../shared/ov/func_80130514.h"


#include "../shared/ov/func_801305CC.h"


#include "../shared/ov/func_80130650.h"


#include "../shared/ov/func_80130740.h"


#include "../shared/ov/func_801307B0.h"


#include "../shared/ov/func_80130858.h"


#include "../shared/ov/func_80130898.h"


#include "../shared/ov/func_801308DC.h"


#include "../shared/ov/func_80130974.h"


#include "../shared/ov/func_80130A18.h"


#include "../shared/ov/func_80130AC4.h"


#include "../shared/ov/func_80130AF0.h"


#include "../shared/ov/func_80130C08.h"




void func_80130D0C(void *a0) {

    extern void (*D_80183F9C[])(void);
    D_80183F9C[*(u8 *)((s32)a0 + 0xC1)]();
}




extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_80183FEC[];
extern s16 D_8018401C[];
extern s16 D_8018407C[];
extern s16 D_80184084[];
extern s16 D_801840A4[];

void func_80130D48(s32 arg0)
{
    s16 *tbl;
    u8 *p = D_80078E78;
    s32 val;
    s32 i;
    s32 j;
    s32 r;
    s32 ret;

    val = func_80131CF4(*(s32 *)((s8 *)arg0 + 0xBC), 0x15);
    if (val == 0) {
        return;
    }

    if (*(u8 *)((s8 *)arg0 + 0x5E) == 0xB) {
        ret = func_8012C658(0x33, 0, arg0);
    } else {
        switch (val & 0xFFFF0000) {
        case 0x10000: {
            u32 x = D_80078EB4;
            u32 y = D_80078EB2;
            u32 b;
            u32 a;

            val = 0;
            if (x == y) {
                val = 0xC;
            } else if ((y >> 1) >= x) {
                val = 3;
            }

            b = *(u16 *)(p + 0x40);
            a = *(u16 *)(p + 0x3E);
            if (b == a) {
                val += 0x18;
            } else if ((a >> 1) >= b) {
                val += 6;
            }
            tbl = D_8018401C + val;

            r = rand() % 100;
            for (i = 0; i < 3; i++, tbl++) {
                if (r < *tbl) {
                    break;
                }
            }

            val = 0;
            switch (i) {
            case 0:
                tbl = D_8018407C;
                val = 0x31;
                break;
            case 1: {
                s32 mx = *(u16 *)(p + 0x3A);
                s32 cur = *(u16 *)(p + 0x3C);
                if (((mx * 7) / 10) >= cur) {
                    val = 4;
                    if ((mx / 2) >= cur) {
                        val = 8;
                        if ((mx / 5) >= cur) {
                            val = 0xC;
                        }
                    }
                }
                tbl = D_80184084 + val;
                val = 0x32;
                break;
            }
            case 2: {
                s32 mx = *(u16 *)(p + 0x3E);
                s32 cur = *(u16 *)(p + 0x40);
                if (((mx * 7) / 10) >= cur) {
                    val = 4;
                    if ((mx / 2) >= cur) {
                        val = 8;
                        if ((mx / 5) >= cur) {
                            val = 0xC;
                        }
                    }
                }
                tbl = D_801840A4 + val;
                val = 0x33;
                break;
            }
            }

            r = rand() % 100;
            for (j = 0; j < 4; j++, tbl++) {
                if (r < *tbl) {
                    break;
                }
            }
            ret = func_8012C658(val, j, arg0);
            break;
        }
        case 0x20000:
            ret = func_8012C658(0x33, 0, arg0);
            break;
        case 0x30000:
            ret = func_8012C658(0x31, 0, arg0);
            break;
        case 0x40000:
            ret = func_8012C658(0x32, 0, arg0);
            break;
        case 0x50000:
            ret = func_8012C658(0x33, 0, arg0);
            break;
        case 0x60000: {
            s32 rr = rand() & 0xFF;
            s32 id;
            tbl = D_80183FEC;
            while (rr >= *tbl) {
                tbl += 3;
            }
            id = tbl[1];
            if (*(u16 *)(p + 0x40) < 4U) {
                id = 0x33;
            }
            ret = func_8012C658(id, tbl[2], arg0);
            break;
        }
        case 0x70000:
            ret = func_8012C658(0x27B, 0, arg0);
            break;
        default:
            return;
        }
    }

    if (ret != 0) {
        *(u16 *)(ret + 0xA) -= 0x20;
    }
}


extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_80131A34(s32, s32);
extern s32 func_80131AC8(void *a0);
extern void func_80131B14(void);
            typedef struct { s8 c[8]; } Blk8_80131170;


// @class: loop-guard
// @unstuck(P36): none — MATCH (88 ins). Keys: duplicate the c!=0/c==0 bodies verbatim (gcc cross-jumps
//   the shared "|=4;goto tail" into L240 on its own); tail dispatch as `if (((s32(*)(s32))func_8012BCCC)(p) <= 0x8FFF)`
//   (the <= polarity makes the >0x8FFF/0x33-first block the bnez'd else=L298, fall-through = 0x32-first);
//   both AC8 tails cross-jump-merge into the shared L2AC final call. Externs aligned to the file's
//   existing decls for gate-safety: func_80131B14(void) [file line 1486], func_8012B14C/func_8012BCCC
//   canonical (s32) [DEFINE macros], ((s32(*)())func_80131AC8)() no-proto (compatible w/ later 1-arg DEFINE, 2-arg call).


void func_80131170(s32 p, s32 b, s32 c) {
    extern u8 D_80183F70[];

    func_80131B14();
    *(u8 *)(((u8 *)p) + 0xC2) = 0;
    *(u8 *)(((u8 *)p) + 0xC3) = 0;
    *(s16 *)(((u8 *)p) + 0x98) = 0;
    if (((u8 *)b) == 0) {
        ((u8 *)b) = D_80183F70;
    }
    func_8012B14C((s32)((u8 *)p), (s32)((u8 *)b));
    *(s32 *)(((u8 *)p) + 0x1C) = 0;
    if (c != 0) {
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), c) != 0) goto tail;
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), 0x24) != 0) goto tail;
        *(s32 *)(((u8 *)p) + 0xC4) &= ~4;
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), 0x20) != 0) {
            *(s32 *)(((u8 *)p) + 0xC4) |= 4;
        } else {
            *(s16 *)(((u8 *)p) + 0x98) = 0;
        }
    } else {
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), 0x24) != 0) goto tail;
        *(s32 *)(((u8 *)p) + 0xC4) &= ~4;
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), 0x20) != 0) {
            *(s32 *)(((u8 *)p) + 0xC4) |= 4;
        } else {
            *(s16 *)(((u8 *)p) + 0x98) = 0;
        }
    }
tail:
    if (*(s16 *)(((u8 *)p) + 0x76) > 0) {
        return;
    }
    if (((s32(*)(s32))func_8012BCCC)((s32)((u8 *)p)) <= 0x8FFF) {
        if (((s32(*)())func_80131AC8)(((u8 *)p), 0x32) != 0) return;
        ((s32(*)())func_80131AC8)(((u8 *)p), 0x33);
    } else {
        if (((s32(*)())func_80131AC8)(((u8 *)p), 0x33) != 0) return;
        ((s32(*)())func_80131AC8)(((u8 *)p), 0x32);
    }
}




// @class: struct
// @unstuck(P36): none — MATCH (8-byte alignment-1 struct copy → lwl/lwr/swl/swr)

   /* size 8, alignment 1 -> unaligned copy */


s32 func_801312D0(s32 param_1, void *param_2)
{
    extern s32 func_80131CF4(s32);
    extern M8 D_801840C4;

    int iVar5;

    iVar5 = ((int (*)(int, int))func_80131CF4)(*(int *)(((int)param_1) + 0xBC), 0x2E);
    if (iVar5 != 0) {
        ((short *)param_2)[2] = 0;
        ((short *)param_2)[0] = 0;
        ((short *)param_2)[1] = (short)iVar5;
    } else {
        *(M8 *)((short *)param_2) = D_801840C4;
    }
}
