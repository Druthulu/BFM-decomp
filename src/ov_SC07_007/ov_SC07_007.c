#include "common.h"
#include "../shared/engine_prelude.h"

#include "../shared/ov/func_80128158.h"


#include "../shared/ov/func_80128178.h"


#include "../shared/ov/func_80128198.h"


#include "../shared/ov/func_801281B8.h"


#include "../shared/ov/func_801281D8.h"


#include "../shared/ov/func_801281F8.h"




s32 func_80128218(void) {

    extern s32 D_801C5348;
    return D_801C5348;
}


#include "../shared/ov/func_80128228.h"


#include "../shared/ov/func_80128248.h"


#include "../shared/ov/func_80128268.h"




void func_80128288(void) {

    extern u16 D_800B99F6;
    extern void (*D_801831C8[])(void);
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_801831C8[v1]();
    }
}


#include "../shared/ov/func_801282CC.h"


#include "../shared/ov/func_801282EC.h"


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

    extern s32 D_801C64C4;
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
        "lui   $at, %%hi(D_801C64C4)\n"
        "sw    $v0, %%lo(D_801C64C4)($at)\n"
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
        "lui   $v0, %%hi(D_801C64C4)\n"
        "lw    $v0, %%lo(D_801C64C4)($v0)\n"
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
extern void func_801287B8(void);
extern void func_8014607C(void);
extern void func_8014ED28(s32 _arg0);

// @class: other
// @stuck: none — MATCH (handwritten full inline-asm scratchpad-stack-switch wrapper w/ branch)
/*
 * HANDWRITTEN scratchpad-stack-switch dispatcher (same idiom as func_80128564 /
 * the func_8014ED28 family): repoints $sp into the D-cache scratchpad stack held
 * at *(0x1F8003FC), calls func_800D19F0, stashes its $v0 result through D_801C64C4,
 * restores $sp, then dispatches on the stored value:
 *   if (D_801C64C4 != 0)  { func_8001903C(); func_80018FC8(); }
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

    extern s32 D_801C64C4;
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
        "lui   $at, %%hi(D_801C64C4)\n"
        "sw    $v0, %%lo(D_801C64C4)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C64C4)\n"
        "lw    $v0, %%lo(D_801C64C4)($v0)\n"
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
// @stuck: none — MATCH (62 ins). D_801C7AC8 read needed the address REMATERIALIZED
//   (lui;addiu;lw 0(reg), not the folded lui;lw %lo) AND pinned to $a0. volatile forces the
//   remat; register __asm__("$4") forces the a0 allocation (gcc otherwise picks v0). Both levers
//   required — pin-alone folds, volatile-alone lands in v0.


extern void func_80129CF8(void);
extern void func_8017849C(void);
extern void func_8014FDF4(struct S8014FDF4 *a0);
extern s32 func_801505FC(s32 a0);
extern void func_801508B4(void *a0);
extern void func_80165E90(void);
extern void func_801627E8(void);
extern void func_80162B1C(void);
extern void func_80165CA0(void);
extern void func_80129010(void);
extern void func_8013CA14(void);
extern void func_800190AC(void);
extern void func_8012956C(void);
extern void func_8016E95C(void);
extern void func_801754A8(void);
extern void func_8013BC7C(void);
extern void func_8013BCDC(void);
extern void func_801379FC(void);
extern void func_8001212C(void);

void func_801287B8(void) {

    extern s32 D_80126B58;
    extern s32 D_801C7AC8;
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
        /* D_801C7AC8 read: the target materializes &sym into $a0 then lw 0($a0) (not the folded
         * lui;lw %lo). volatile forces the rematerialize; the $4 pin forces the a0 allocation. */
        register volatile s32 *p __asm__("$4") = &D_801C7AC8;
        if (*p == 0) {
            func_8013BC7C();
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

    extern s32 D_801C5348;
    extern u8 D_800AEFD0;
    func_8001ABBC(0, 0, &D_800AEFD0, D_801C5348, 0);
}


extern s32 func_80128998(void);

// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x60 store AND arg5; writing D_800C7C60=0x60 directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.


extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int func_801288E8(int arg0)
{

    extern int D_800C7C60;
    extern int *D_800C7C64;
    extern int D_800A2E20;
    extern int D_800AF558;
    extern int D_801C5348;
    int *p = &D_800C7C60;
    *p = 0x60;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AF558, D_801C5348, p);
}


extern s32 func_80128998(void);

// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x5e store AND arg5; writing D_800C7C60=0x5e directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.


extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int func_80128940(int arg0)
{

    extern int D_800C7C60;
    extern int *D_800C7C64;
    extern int D_800A2E20;
    extern int D_800AF560;
    extern int D_801C5348;
    int *p = &D_800C7C60;
    *p = 0x5e;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AF560, D_801C5348, p);
}



// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0xd store AND arg5; writing D_800C7C60=0xd directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.


extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int aF80128998(int arg0) __asm__("func_80128998");
int aF80128998(int arg0)
{

    extern int D_800C7C60;
    extern int *D_800C7C64;
    extern int D_800A2E20;
    extern int D_800AECB0;
    extern int D_801C5348;
    int *p = &D_800C7C60;
    *p = 0xd;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AECB0, D_801C5348, p);
}




extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_801289F0(void) {

    extern s32 D_801C5348;
    extern u8 D_800AECB8;
    func_8001ABBC(0, 0, &D_800AECB8, D_801C5348, 0);
}


extern void func_80011B7C(int);
extern void func_80011C10(void);

void func_80128A28(void) {

    extern u16 D_800B99F6;
    extern s16 D_800B9A00;
    extern M2C_UNK (*D_80182F04)();
    extern s16 (*D_80182F08)();
    s16 temp_v0;

    switch (D_800B99F6) {                           /* irregular */
    case 1:
        D_80182F04();
        /* fallthrough */
    case 0:
        func_80011C10();
        return;
    case 2:
        temp_v0 = D_80182F08();
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
    extern M2C_UNK (*D_80182F10)();
    extern s32 (*D_80182F14)();
    extern s32 D_801C64C0;
    switch (D_800B99F6) {                           /* irregular */
    case 0:
        D_801C64C0 = func_8002AF08();
        func_80011C10();
        return;
    case 1:
        D_80182F10();
        func_80011C10();
        return;
    case 2:
        if ((D_80182F14() << 0x10) != 0) {
            if (D_801C64C0 == 1) {
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




extern CdFileLoc_80128C98 cdFileLocTable[];
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_80128C98(s32 arg0) {

    extern s16 D_801831E0[];
    extern s32 D_801C5348;
    s16 idx = D_801831E0[arg0];

    if (idx >= 0) {
        func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[idx], D_801C5348, 0);
    } else {
        return 1;
    }
}




extern CdFileLoc cdFileLocTable[];
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_80128CFC(s32 arg0) {

    extern s16 D_801831F0[];
    extern s32 D_801C5348;
    s16 idx = D_801831F0[arg0];

    if (idx >= 0) {
        func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[idx], D_801C5348, 0);
    } else {
        return 1;
    }
}


#include "../shared/ov/func_80128D60.h"


#include "../shared/ov/func_80128DB4.h"


void func_80128EA8(s32 a0, s32 a1, s32 a2) {
    *(s32 *)(a1 + 0x0) = a2;                       /* sw a2, 0x0(a1) */
    *(s16 *)(a1 + 0x4) = 0;                         /* sh zero, 0x4(a1) */
    *(s16 *)(a1 + 0x6) = (*(s32 *)(a2 + 0x4)) & 0x3F; /* lw; andi 0x3F; sh 0x6(a1) */
    *(s16 *)(a0 + 0x28) = *(u16 *)(a2 + 0x0);      /* lhu 0x0(a2); sh 0x28(a0) */
    *(s16 *)(a0 + 0x2A) = *(u16 *)(a2 + 0x2);      /* lhu 0x2(a2); sh 0x2A(a0) */
}


#include "../shared/ov/func_80128ED8.h"



void func_80128FAC(u16 *arg0) {

    extern M2C_UNK D_801C534C;
    func_8001534C(4, &D_801C534C, 0x80, 0x90, 0, 0);
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

    extern s32 D_801C64C4;

    extern s16 D_80114EE0;
    extern u8 D_800B9A78;
    extern u8 D_801C64C5[];
    extern u8 D_801C64C6[];
    extern u8 D_801C64C8[];
    extern u8 D_801C64C9[];
    extern u8 D_801C64CA[];
    extern u8 D_801C7AA8;
    extern u8 D_800AF630[];
    extern u8 D_800A6518[];
    register s32 *sp10 __asm__("$21");
    register u8 *afbase __asm__("$22");
    register s32 *sp0 __asm__("$23");
    Ent_956C *base;
    s32 i;
    s16 a1;
    register u32 temp_a3 __asm__("$7");
    register u32 arg0 __asm__("$4");
    register u32 s __asm__("$2");
    register u32 s2 __asm__("$3");
    register u32 t6 __asm__("$8");
    s32 code;

    sp10 = (s32 *)0x1F800010;
    sp0 = (s32 *)0x1F800000;
    afbase = (u8 *)&D_800AF630;
    if (D_80114EE0 == 0) {
        return;
    }
    base = (Ent_956C *)&D_800B9A78;
    __asm__("" : "=r"(base) : "0"(base));
    i = 0;
    do {
        s32 idx = i * 8 + 4;
        code = base->f34;
        if (code == 0x7FFE) {
            goto case_7FFE;
        }
        if (code < 0x7FFF) {
            a1 = i + 3;
            if (code == 0x7FFD) {
                goto case_7FFD;
            }
            goto do_default;
        }
        a1 = i + 3;
        if (code != 0x7FFF) {
            goto do_default;
        }
        goto next;
    case_7FFD:
        if (i == 0) {
            func_801299C8(D_801C7AA8, 1, base);
        }
        func_80015B6C(-0xA0, -0x74, 0x140, 0x8C,
                      D_801C64C8[0], D_801C64C8[1], D_801C64C8[2],
                      D_801C64C8[4], D_801C64C8[5], D_801C64C8[6]);
        func_80015B6C(-0xA0, 0x18, 0x140, 0x3C,
                      D_801C64C8[4], D_801C64C8[5], D_801C64C8[6],
                      D_801C64C8[8], D_801C64C8[9], D_801C64C8[0xA]);
        func_80015B6C(-0xA0, 0x54, 0x140, 0x28,
                      D_801C64C8[8], D_801C64C8[9], D_801C64C8[0xA],
                      D_801C64C8[0xC], D_801C64C8[0xD], D_801C64C8[0xE]);
        goto next;
    case_7FFE:
        func_801299C8(D_801C7AA8, (s16)(i * 2), base);
        func_80015B6C(-0xA0, *(s16 *)&base->f3A, 0x140, base->f3E,
                      ((u8 *)&D_801C64C4)[idx], D_801C64C5[idx], D_801C64C6[idx],
                      D_801C64C8[idx], D_801C64C9[idx], D_801C64CA[idx]);
        goto next;
    do_default:
        __asm__("");
        arg0 = D_801C7AA8;
        s = base->f40;
        temp_a3 = base->f38;
        s += temp_a3;
        base->f1C = s;
        s2 = base->f42;
        t6 = base->f3A;
        s2 += t6;
        base->f1E = s2;
        ((void (*)(s32, s32, void *, s32))func_801299C8)(arg0, a1, base, temp_a3);
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
    next:
        base += 1;
        i += 1;
    } while (i < 2);
}


#include "../shared/ov/func_801298F4.h"



// @class: schedule
// @stuck: none — MATCH (158 ins, match_one relocation-masked)
//
// Levers that landed it (2 iterations, 56 mismatched -> MATCH):
//  1. §43 K&R s16-param definition: `void f(a0,a1,a2) s16 a0; s16 a1; u8 *a2;` reproduces the
//     in-place `sll $a0,$a0,16` zero-test on the arg reg + the raw-$a1 copy (`addu $a3,$a1,$zero`)
//     stashed in the jtbl branch delay slot and RE-extended per use in the case body.
//  2. §18 array-of-struct %lo-fold: three sibling extern arrays D_801C64C8/1/2[] (a 4-row x 3-comp
//     RGB gradient table, stride 4) give `lui $at,%hi(sym); addu $at,$at,idx4; sb $v0,%lo(sym)($at)`
//     for the indexed case and plain `lui/sb %lo(sym+k)` for the constant-index case.
//  3. Switch CASE-ORDER = source order: the jump table dispatches case 1 to the FIRST emitted block,
//     so `case 1:` must be written before `case 0/2:` and `case 3/4:`.
//  4. THE residual (56 -> 0): the case-1 body must be written ROW-MAJOR (BE0[0],BE1[0],BE2[0],
//     BE0[4],BE1[4],BE2[4],...), i.e. the natural table fill. gcc-2.7.2's sched pass then REORDERS
//     the stores itself (BE0,BE1,BE5,BE8,BE4,BEC,BE9,BED,BE2,BE6,BEA,BEE) because the three arrays
//     are distinct declarations => provably non-aliasing. Writing the source in the target's STORE
//     order is the trap: it pins the b*255 / r*143 CSEs at their late store sites instead of letting
//     them hoist into $a0/$v1 at rows 0/1, and mis-schedules the D_801C79B8 load.
//  5. Shift signedness: `u32` component locals give `srl` for r*5>>3 and g*25>>1; an explicit
//     `(s32)(x * 255) >> 4` gives `sra` for the *255 / *143 / *45 terms (mixed within one block).

extern u8 D_801C7AC2;
extern u8 D_801C79E2;
extern u8 D_801C79B8;
extern u8 D_801C64C8[];
extern u8 D_801C64C9[];
extern u8 D_801C64CA[];

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
            r = D_801C7AC2;
            g = D_801C79E2;
            b = D_801C79B8;
            D_801C64C8[0] = r * 5 >> 3;
            D_801C64C9[0] = g << 3;
            D_801C64CA[0] = (s32)(b * 255) >> 4;
            D_801C64C8[4] = (s32)(r * 143) >> 4;
            D_801C64C9[4] = g * 25 >> 1;
            D_801C64CA[4] = (s32)(b * 255) >> 4;
            D_801C64C8[8] = (s32)(r * 255) >> 4;
            D_801C64C9[8] = (s32)(g * 255) >> 4;
            D_801C64CA[8] = (s32)(b * 255) >> 4;
            D_801C64C8[12] = (s32)(r * 143) >> 4;
            D_801C64C9[12] = (s32)(g * 255) >> 4;
            D_801C64CA[12] = (s32)(b * 45) >> 2;
            break;
        case 0:
        case 2:
            i = arg1 * 4;
            D_801C64C8[i] = arg2[0x44] * D_801C7AC2 >> 4;
            D_801C64C9[i] = arg2[0x45] * D_801C79E2 >> 4;
            D_801C64CA[i] = arg2[0x46] * D_801C79B8 >> 4;
            i = (arg1 + 1) * 4;
            D_801C64C8[i] = arg2[0x47] * D_801C7AC2 >> 4;
            D_801C64C9[i] = arg2[0x48] * D_801C79E2 >> 4;
            D_801C64CA[i] = arg2[0x49] * D_801C79B8 >> 4;
            break;
        case 3:
        case 4:
            arg2[0x20] = D_801C7AC2 << 3;
            arg2[0x21] = D_801C79E2 << 3;
            arg2[0x22] = D_801C79B8 << 3;
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
// @stuck: none — MATCH (78 ins, relocation-masked). Register pins ($2-$5 reused for
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
void func_8012A568(void (*a0)(void)) {
    func_8012A598(a0);
    a0();
}


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

void func_8012AAAC(void *arg0) {
    void *ptr;
    s32 link;
    s32 next;
    s32 saved;
    s32 cnt;
    s32 back;
    s32 head;

    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xBFFF);
    ptr = (void *) (M2C_FIELD(arg0, s32 *, 0x90) + (M2C_FIELD(arg0, s32 *, 0x94) * 8));
    if (M2C_FIELD(ptr, s16 *, 4) < 0) {
        switch (M2C_FIELD(ptr, s16 *, 4)) {
        case -2:
            link = M2C_FIELD(arg0, s32 *, 0x9C);
            if (link == 0) {
                M2C_FIELD(arg0, s16 *, 0x98) = 0;
                break;
            }
            goto pop;
        case -1:
            link = M2C_FIELD(arg0, s32 *, 0x9C);
            if (link != 0) {
pop:
                back = M2C_FIELD(arg0, s16 *, 0x9A);
                M2C_FIELD(arg0, s32 *, 0x90) = link;
                M2C_FIELD(arg0, s32 *, 0x9C) = 0;
                M2C_FIELD(arg0, s16 *, 0x9A) = 0;
                M2C_FIELD(arg0, s32 *, 0x94) = back;
                func_8012AAAC(arg0);
                break;
            }
            M2C_FIELD(arg0, s32 *, 0x94) = 0;
            func_8012AAAC(arg0);
            M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) | 0x4000);
            break;
        case -4:
            head = M2C_FIELD(ptr, s32 *, 0);
            M2C_FIELD(arg0, s32 *, 0x94) = 0;
            M2C_FIELD(arg0, s32 *, 0x9C) = 0;
            M2C_FIELD(arg0, s16 *, 0x9A) = 0;
            M2C_FIELD(arg0, s32 *, 0x90) = head;
            M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
            func_8012AAAC(arg0);
            break;
        case -3:
            cnt = M2C_FIELD(arg0, s32 *, 0x94) + 1;
            M2C_FIELD(arg0, s32 *, 0x94) = cnt;
            if (M2C_FIELD(arg0, s32 *, 0x9C) != 0) {
                func_8012AAAC(arg0);
                break;
            }
            saved = M2C_FIELD(arg0, s32 *, 0x90);
            next = M2C_FIELD(ptr, s32 *, 0);
            M2C_FIELD(arg0, s32 *, 0x94) = 0;
            M2C_FIELD(arg0, s32 *, 0x9C) = 0;
            M2C_FIELD(arg0, s16 *, 0x9A) = 0;
            M2C_FIELD(arg0, s32 *, 0x90) = next;
            M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
            func_8012AAAC(arg0);
            M2C_FIELD(arg0, s32 *, 0x9C) = saved;
            M2C_FIELD(arg0, s16 *, 0x9A) = (s16) cnt;
            break;
        case -50:
            M2C_FIELD(arg0, s32 *, 0x94) = M2C_FIELD(arg0, s32 *, 0x94) + 1;
            func_8012AAAC(arg0);
            M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) | 0x2000);
            break;
        case -5:
            M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) | 0x400);
            M2C_FIELD(arg0, s32 *, 0x94) = M2C_FIELD(arg0, s32 *, 0x94) - 1;
            func_8012AAAC(arg0);
            break;
        }
    } else {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s32 *, 0x20) = M2C_FIELD(ptr, s32 *, 0);
        M2C_FIELD(arg0, s16 *, 0x98) = M2C_FIELD(ptr, s16 *, 4);
    }
}


extern void func_8012AAAC();

void func_8012ACA0(void *arg0) {

    extern M2C_UNK D_8018325C;
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_8018325C;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s16 *, 0x9A) = 0;
    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
    ((void (*)(void))func_8012AAAC)();
}




// @class: iv-combine
// @stuck: none — MATCH (25 ins). Array-subscript induction o->list[i] fixes preheader hoist order + loop-top load-delay nop; scattered case labels force the jump table (gcc merges contiguous same-target cases, so 6+ non-contiguous nodes needed for the density heuristic).
      /* 8-byte element, cmd @ +4 */
    /* list ptr @ +0x90 */

s32 func_8012ACE0(void *o) {
    int i;
    for (i = 0; ; i++) {
        switch (((Owner_8012ACE0 *)o)->list[i].cmd) {
            case -2:
            case -1:
            case 0:
                return i;
            case -50: case -45: case -40: case -35: case -30:   /* scatter -> force jump table (min=-50 sets low bound) */
            default:
                break;
        }
    }
}

#include "../shared/ov/func_8012AD44.h"


#include "../shared/ov/func_8012AD50.h"




void func_8012AD64(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x34) = a1;
}


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



// @class: schedule
// @stuck: none — MATCH (149 ins). Counter (*(u16 *)&D_801270C4): gcc CSE's the two reads (store to
//   dst+0x36 assumed non-aliasing the global) AND folds %lo per-access — target instead RELOADS
//   and keeps &(*(u16 *)&D_801270C4) in one reg. Fix = pin a `u16*` to $v1 (register asm "$3"), read via
//   `*(volatile u16*)pc` (defeats CSE -> 2 loads) but STORE via plain `*pc` (non-volatile store
//   schedules store-before-sll, no extra `move`). count is s16 so `count==0` -> `sll 16;bnez`.
//   else-block obj must be a BLOCK-LOCAL (gcc then picks $a1, not the shared if-branch $a0).

extern void  func_80016714(void *a0, s32 a1);

s32 func_8012C890(s32 a0, s32 a1, s32 a2) {

    extern s32   D_80186740;
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
    *(s32 *)(dst + 0x78) = (s32)&D_80186740;
    *(s32 *)(dst + 0xDC) = v10;

    {
        register u16 *pc __asm__("$3");
        pc = &(*(u16 *)&D_801270C4);
        *(u16 *)(dst + 0x36) = *(volatile u16 *)pc;
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
    extern u8 D_8018326C[];

    u16 s[3];
    int ret;
    int t;

    s[0] = (*(unsigned short *)&D_80126B5E);
    s[1] = (*(unsigned short *)&D_80126B62) - 0x40;
    s[2] = (*(unsigned short *)&D_80126B66);
    ret = ((int (*)())func_800132BC)(arg0, s);
    t = arg1 + 0x20;
    if (ret < t * t) {
        func_8012F568(1, 1, 0, arg2, arg0, &D_8018326C);
        return 1;
    }
    return 0;
}


#include "../shared/ov/func_8012D714.h"




extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);

s32 func_8012DB84(void)
{

    extern M2C_UNK D_80183274;
    extern M2C_UNK D_8018327C;
    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, &D_80183274, &D_8018327C);
}


#include "../shared/ov/func_8012DBD0.h"




// @class: regalloc-order
// @stuck: none — MATCH




s32 func_8012DDA4(void) {

    extern u8 D_80126720[];
    extern Entry_8012DDA4 * D_801C64E4;
    extern Entry_8012DDA4 * D_801C64E0;

    Entry_8012DDA4 *p;
    Entry_8012DDA4 *end = ((Entry_8012DDA4 *)D_80126720);

    while (D_801C64E4 != end) {
        p = D_801C64E4;
        if (p->active != 0 && p != D_801C64E0) {
            D_801C64E4 = p + 1;
            return p;
        }
        D_801C64E4++;
    }
    D_801C64E4 = 0;
    return 0;
}




// @class: plumbing
// @stuck: none — MATCH (35/35 ins, relocation-masked)


s32 func_8012DE2C(s32 a0) {

    extern u8 D_801202A0[];
    extern u8 * D_801C64E4;
    extern u8 * D_801C64E0;

    u8 *base;
    u8 *end;
    u8 *p;

    base = D_801202A0;
    end = base + 0x6480;
    D_801C64E4 = base;
    D_801C64E0 = ((u8 *)a0);

    while (D_801C64E4 != end) {
        p = D_801C64E4;
        if (*(u16 *)p != 0 && p != ((u8 *)a0)) {
            D_801C64E4 = p + 0x10C;
            return p;
        }
        D_801C64E4 += 0x10C;
    }
    D_801C64E4 = 0;
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
 *   D_801C64D8  -> `lw`/`sw`           => s32
 *   D_801C64DC  -> `lw`/`sw`           => s32
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
 * CLUSTER A - idx 43-45 (the D_801C64DC load vs the 0x20($a2) load, swapped): 3 -> MATCH.
 *   Pure sched1 rank, and it IS steerable (sched.md S2, the birthing boost). The `.i.sched` dump
 *   of the wave22 draft says it outright:
 *       ;; insn[ 104]: priority = 1     (prev = D_801C64DC)
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
    extern s32 D_801C64D8;
    extern s32 D_801C64DC;
    register s32 arg0 __asm__("$6");
    register s32 prev __asm__("$5");
    register u16 flags __asm__("$2");
    s32 a;
    s32 diff;
    s32 v;
    register s32 d __asm__("$2");
    s32 spd;
    s32 e1;
    s32 e2;

    arg0 = arg0_;
    *(s16 *)(arg0 + 0x5C) = 0;
    a = D_80126CE0;
    if (a == 0) {
        D_801C64D8 = 0x1000;
        D_801C64DC = 0x1000;
    }
    a = ((0x90 - a) << 12) / 0x90;
    *(s32 *)(arg0 + 0x1C) += 1;
    spd = 0x1000;

    diff = D_801C64D8 - a;
    if (diff > 0) {
        D_801C64D8 -= diff >> 2;
    } else if (diff < 0) {
        D_801C64D8 += (-diff) / 4;
    }

    prev = D_801C64DC;
    e1 = *(s32 *)(arg0 + 0x20);
    v = D_801C64D8 - prev + spd;
    D_801C64DC = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_801C64D8 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;

    e2 = *(s32 *)(arg0 + 0x20);
    d = __builtin_abs(v);
    *(s16 *)(e2 + 0x1C) = d;
    *(s16 *)(e2 + 0x18) = d;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x1000;
}


#include "../shared/ov/func_8012E470.h"


#include "../shared/ov/func_8012E4C8.h"


#include "../shared/ov/func_8012E504.h"


#include "../shared/ov/func_8012E544.h"


#include "../shared/ov/func_8012E57C.h"


#include "../shared/ov/func_8012E5CC.h"


#include "../shared/ov/func_8012E688.h"


#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_ldlv0(r0) __asm__ volatile (                 \
    "lhu $13, 4( %0 );"                                  \
    "lhu $12, 0( %0 );"                                  \
    "sll $13, $13, 16;"                                  \
    "or $12, $12, $13;"                                  \
    "mtc2 $12, $0;"                                      \
    "lwc2 $1, 8( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13" )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_stsxy(r0) __asm__ volatile (                 \
    "swc2 $14, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )



#include "../shared/ov/func_8012E778.h"


#include "../shared/ov/func_8012E88C.h"


#include "../shared/ov/func_8012E8A8.h"


#include "../shared/ov/func_8012E8C4.h"


#include "../shared/ov/func_8012E8E0.h"




// @class: other
// @stuck: none — MATCH (branch-polarity invert: `0x78 != 0` puts compute block as fall-through)

extern void func_8016AA50(int, int);
extern void func_8016B428(int);
extern void func_80019064(void *);

void func_8012E9C0(int param_1)
{

    extern int D_80183284;
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
            func_8016B428(param_1);
            func_80019064(&D_80183284);
        }
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (93 ins)


extern void func_80049CAC(s32 a0, s32 a1);

/* Blk16 lifted to src/shared/engine_types.h (Phase 22). */

#include "../shared/ov/func_8012EA90.h"


#include "../shared/ov/func_8012EC04.h"


#include "../shared/ov/func_8012EECC.h"


#include "../shared/ov/func_8012EF34.h"


#include "../shared/ov/func_8012EF70.h"


#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_stsxy(r0) __asm__ volatile (                 \
    "swc2 $14, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )
#define gte_SetRotMatrix(r0) __asm__ volatile (          \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_ldv0(r0) __asm__ volatile (                  \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_stsxy(r0) __asm__ volatile (                 \
    "swc2 $14, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )
#define gte_stflg(r0) __asm__ volatile (                 \
    "cfc2 $12, $31;"                                     \
    "nop;"                                               \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )
#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_ldv0(r0) __asm__ volatile (                  \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )
#define gte_stflg(r0) __asm__ volatile (                 \
    "cfc2 $12, $31;"                                     \
    "nop;"                                               \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )

/* §37/§124 asm-label alias: the fleet canon declares this `extern void
 * func_8012EFB8(s32 a0);` inside the DEFINE_func_* macros in
 * src/shared/engine_core.h (the one at src/ov_SC01_077/ov_SC01_077_jr_8012ACE0.c:1169
 * comes from DEFINE_func_8012EF70()).  The byte-true body returns s32 and takes
 * TWO pointers, so it conflicts on BOTH the return axis and the arity axis.
 * Aliasing the C name sidesteps both with no header edit and no codegen change.
 * This declaration MUST travel with the body. */
s32 aF8012EFB8(void *param_1, void *param_2) __asm__("func_8012EFB8");

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
// @stuck: none — MATCH

#include "../shared/ov/func_8012F40C.h"


#include "../shared/ov/func_8012F49C.h"

#include "../shared/ov/func_8012F568.h"


#include "../shared/ov/func_8012F5F4.h"


#include "../shared/ov/func_8012F68C.h"


#include "../shared/ov/func_8012F75C.h"


#include "../shared/ov/func_8012F7B4.h"



// @class: plumbing
// @stuck: none — MATCH (pending gate)
extern void func_80131170();
extern void func_80131CA8();

void func_8012F828(int param_1)
{

    extern unsigned char D_801832A0[];
    *(unsigned char *)(param_1 + 0xC1) = 4;
    if (*(unsigned int *)(param_1 + 0xB4) & 8) {
        func_80131170(param_1, D_801832A0, 0xB);
    }
    func_80131CA8(param_1, 9);
}


#include "../shared/ov/func_8012F87C.h"



// @class: plumbing
// @stuck: none — MATCH (pending gate)
extern void func_80131170();
extern void func_80131CA8();

void func_8012F8C8(int param_1)
{

    extern unsigned char D_801832AC[];
    *(unsigned char *)(param_1 + 0xC1) = 7;
    if (*(unsigned int *)(param_1 + 0xB4) & 128) {
        func_80131170(param_1, D_801832AC, 0xB);
    }
    func_80131CA8(param_1, 22);
}


#include "../shared/ov/func_8012F91C.h"


#include "../shared/ov/func_8012F968.h"


#include "../shared/ov/func_8012FB54.h"


#include "../shared/ov/func_8012FC30.h"


#include "../shared/ov/func_8012FCA4.h"



// @class: schedule
// @stuck: none — MATCH (57 ins), byte-exact via rtu_match on the real TU.
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

    extern int  D_801832B8;
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
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_801832B8);
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



void func_80130D0C(s32 a0) {

    extern void (*D_801832C0[])(void);
    D_801832C0[*(u8 *)((s32)a0 + 0xC1)]();
}





// @class: regalloc-order
// @stuck: none — MATCH (266/266). Levers: pin pa=$s2 p=$s3, tbl=$s0 (NOT s1v — leave natural so switch-mask lands in $v1); tight-block pins for the table-addr temps `register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2")` force offset=$v1/base=$v0 (else compute-into-dest $s0); inline offset `TABLE + s1v*2` (late) keeps the 2-sll delay-slot dup; 0x60000 reuses `tbl` (not a fresh `e`) so it stays $s0 and materializes after rand().
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_80183310[];
extern s16 D_80183340[];
extern s16 D_801833A0[];
extern s16 D_801833A8[];
extern s16 D_801833C8[];

void func_80130D48(s32 arg0)
{
    register s16 *tbl __asm__("$16");
    register s32 pa __asm__("$18") = arg0;
    register u8 *p  __asm__("$19") = D_80078E78;
    s32 s1v;
    s32 call_a0;
    s32 call_a1;
    s32 cnt;
    s32 r;
    void *ret;

    s1v = func_80131CF4(*(s32 *)((s8 *)pa + 0xBC), 0x15);
    if (s1v == 0) {
        return;
    }

    if (*(u8 *)((s8 *)pa + 0x5E) == 0xB) {
        call_a0 = 0x33;
        call_a1 = 0;
        goto do_call;
    }

    switch (s1v & 0xFFFF0000) {
    case 0x10000: {
        u32 x = D_80078EB4;
        u32 y = D_80078EB2;
        u32 b;
        u32 a;

        s1v = 0;
        if (x == y) {
            s1v = 0xC;
        } else if ((y >> 1) >= x) {
            s1v = 3;
        }

        b = *(u16 *)(p + 0x40);
        a = *(u16 *)(p + 0x3E);
        if (b == a) {
            s1v += 0x18;
        } else if ((a >> 1) >= b) {
            s1v += 6;
        }
        { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_80183340; tbl = (s16 *)(bp + v1); }

        r = rand() % 100;
        cnt = 0;
    loop27:
        if (r >= *tbl) {
            cnt += 1;
            tbl += 1;
            if (cnt < 3) {
                goto loop27;
            }
        }

        s1v = 0;
        switch (cnt) {
        case 0:
            tbl = D_801833A0;
            s1v = 0x31;
            break;
        case 1: {
            s32 mx = *(u16 *)(p + 0x3A);
            s32 cur = *(u16 *)(p + 0x3C);
            if (((mx * 7) / 10) >= cur) {
                s1v = 4;
                if ((mx / 2) >= cur) {
                    s1v = 8;
                    if ((mx / 5) >= cur) {
                        s1v = 0xC;
                    }
                }
            }
            { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_801833A8; tbl = (s16 *)(bp + v1); }
            s1v = 0x32;
            break;
        }
        case 2: {
            s32 mx = *(u16 *)(p + 0x3E);
            s32 cur = *(u16 *)(p + 0x40);
            if (((mx * 7) / 10) >= cur) {
                s1v = 4;
                if ((mx / 2) >= cur) {
                    s1v = 8;
                    if ((mx / 5) >= cur) {
                        s1v = 0xC;
                    }
                }
            }
            { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_801833C8; tbl = (s16 *)(bp + v1); }
            s1v = 0x33;
            break;
        }
        }

        r = rand() % 100;
        call_a1 = 0;
    loop50:
        if (r >= *tbl) {
            call_a1 += 1;
            tbl += 1;
            if (call_a1 < 4) {
                goto loop50;
            }
        }
        call_a0 = s1v;
        goto do_call;
    }
    case 0x20000:
        call_a0 = 0x33;
        call_a1 = 0;
        goto do_call;
    case 0x30000:
        call_a0 = 0x31;
        call_a1 = 0;
        goto do_call;
    case 0x40000:
        call_a0 = 0x32;
        call_a1 = 0;
        goto do_call;
    case 0x50000:
        call_a0 = 0x33;
        call_a1 = 0;
        goto do_call;
    case 0x60000: {
        s32 rr = rand() & 0xFF;
        tbl = D_80183310;
        if (rr >= *tbl) {
            do {
                tbl += 3;
            } while (rr >= *tbl);
        }
        call_a0 = tbl[1];
        if (*(u16 *)(p + 0x40) < 4U) {
            call_a0 = 0x33;
        }
        call_a1 = tbl[2];
        goto do_call;
    }
    case 0x70000:
        call_a0 = 0x27B;
        call_a1 = 0;
        goto do_call;
    default:
        return;
    }

do_call:
    ret = func_8012C658(call_a0, call_a1, pa);
    if (ret != 0) {
        *(u16 *)((s8 *)ret + 0xA) -= 0x20;
    }
}


extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_80131A34(s32, s32);
extern s32 func_80131AC8(void *a0);
extern void func_80131B14(void);


// @class: loop-guard
// @stuck: none — MATCH (88 ins). Keys: duplicate the c!=0/c==0 bodies verbatim (gcc cross-jumps
//   the shared "|=4;goto tail" into L240 on its own); tail dispatch as `if (((s32(*)(s32))func_8012BCCC)(p) <= 0x8FFF)`
//   (the <= polarity makes the >0x8FFF/0x33-first block the bnez'd else=L298, fall-through = 0x32-first);
//   both AC8 tails cross-jump-merge into the shared L2AC final call. Externs aligned to the file's
//   existing decls for gate-safety: func_80131B14(void) [file line 1486], func_8012B14C/func_8012BCCC
//   canonical (s32) [DEFINE macros], ((s32(*)())func_80131AC8)() no-proto (compatible w/ later 1-arg DEFINE, 2-arg call).


void func_80131170(s32 p, s32 b, s32 c) {
    extern u8 D_80183294[];

    func_80131B14();
    *(u8 *)(((u8 *)p) + 0xC2) = 0;
    *(u8 *)(((u8 *)p) + 0xC3) = 0;
    *(s16 *)(((u8 *)p) + 0x98) = 0;
    if (((u8 *)b) == 0) {
        ((u8 *)b) = D_80183294;
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
// @stuck: none — MATCH (8-byte alignment-1 struct copy → lwl/lwr/swl/swr)

   /* size 8, alignment 1 -> unaligned copy */


s32 func_801312D0(s32 param_1, void *param_2)
{
    extern int func_80131CF4(int, int);
    extern M8 D_801833E8;

    int iVar5;

    iVar5 = func_80131CF4(*(int *)(((int)param_1) + 0xBC), 0x2E);
    if (iVar5 != 0) {
        ((short *)param_2)[2] = 0;
        ((short *)param_2)[0] = 0;
        ((short *)param_2)[1] = (short)iVar5;
    } else {
        *(M8 *)((short *)param_2) = D_801833E8;
    }
}
