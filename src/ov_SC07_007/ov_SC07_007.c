#include "common.h"
#include "../shared/engine_core.h"

DEFINE_func_80128158()  /* dedup: shared engine-core @0x80128158 (src/shared) */


DEFINE_func_80128178()  /* dedup: shared engine-core @0x80128178 (src/shared) */


DEFINE_func_80128198()  /* dedup: shared engine-core @0x80128198 (src/shared) */


DEFINE_func_801281B8()  /* dedup: shared engine-core @0x801281b8 (src/shared) */


DEFINE_func_801281D8()  /* dedup: shared engine-core @0x801281d8 (src/shared) */


DEFINE_func_801281F8()  /* dedup: shared engine-core @0x801281f8 (src/shared) */




s32 func_80128218(void) {

    extern s32 D_801C5348;
    return D_801C5348;
}


DEFINE_func_80128228()  /* dedup: shared engine-core @0x80128228 (src/shared) */


DEFINE_func_80128248()  /* dedup: shared engine-core @0x80128248 (src/shared) */


DEFINE_func_80128268()  /* dedup: shared engine-core @0x80128268 (src/shared) */




void func_80128288(void) {

    extern u16 D_800B99F6;
    extern void (*D_801831C8[])(void);
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_801831C8[v1]();
    }
}


DEFINE_func_801282CC()  /* dedup: shared engine-core @0x801282cc (src/shared) */


DEFINE_func_801282EC()  /* dedup: shared engine-core @0x801282ec (src/shared) */


DEFINE_func_8012832C()  /* dedup: shared engine-core @0x8012832c (src/shared) */


DEFINE_func_80128420()  /* dedup: shared engine-core @0x80128420 (src/shared) */


DEFINE_func_801284B8()  /* dedup: shared engine-core @0x801284b8 (src/shared) */


DEFINE_func_801284F0()  /* dedup: shared engine-core @0x801284f0 (src/shared) */


DEFINE_func_8012853C()  /* dedup: shared engine-core @0x8012853c (src/shared) */


DEFINE_func_80128564()  /* dedup: shared engine-core @0x80128564 (src/shared) */


DEFINE_func_801285D4()  /* dedup: shared engine-core @0x801285d4 (src/shared) */



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


DEFINE_func_80128678()  /* dedup: shared engine-core @0x80128678 (src/shared) */


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


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_801287B8);



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


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_80128998);



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


DEFINE_func_80128C14()  /* dedup: shared engine-core @0x80128c14 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_80128C98);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_80128CFC);

DEFINE_func_80128D60()  /* dedup: shared engine-core @0x80128d60 (src/shared) */


DEFINE_func_80128DB4()  /* dedup: shared engine-core @0x80128db4 (src/shared) */


void func_80128EA8(s32 a0, s32 a1, s32 a2) {
    *(s32 *)(a1 + 0x0) = a2;                       /* sw a2, 0x0(a1) */
    *(s16 *)(a1 + 0x4) = 0;                         /* sh zero, 0x4(a1) */
    *(s16 *)(a1 + 0x6) = (*(s32 *)(a2 + 0x4)) & 0x3F; /* lw; andi 0x3F; sh 0x6(a1) */
    *(s16 *)(a0 + 0x28) = *(u16 *)(a2 + 0x0);      /* lhu 0x0(a2); sh 0x28(a0) */
    *(s16 *)(a0 + 0x2A) = *(u16 *)(a2 + 0x2);      /* lhu 0x2(a2); sh 0x2A(a0) */
}


DEFINE_func_80128ED8()  /* dedup: shared engine-core @0x80128ed8 (src/shared) */



void func_80128FAC(u16 *arg0) {

    extern M2C_UNK D_801C534C;
    func_8001534C(4, &D_801C534C, 0x80, 0x90, 0, 0);
    func_800153CC(5, *arg0, 0xA8, 0x90, 0x40, 0);
}


DEFINE_func_80129010()  /* dedup: shared engine-core @0x80129010 (src/shared) */


DEFINE_func_801290DC()  /* dedup: shared engine-core @0x801290dc (src/shared) */


DEFINE_func_8012913C()  /* dedup: shared engine-core @0x8012913c (src/shared) */


DEFINE_func_801291C0()  /* dedup: shared engine-core @0x801291c0 (src/shared) */


DEFINE_func_80129220()  /* dedup: shared engine-core @0x80129220 (src/shared) */


DEFINE_func_80129248()  /* dedup: shared engine-core @0x80129248 (src/shared) */


DEFINE_func_80129258()  /* dedup: shared engine-core @0x80129258 (src/shared) */


DEFINE_func_8012927C()  /* dedup: shared engine-core @0x8012927c (src/shared) */


DEFINE_func_801292C8()  /* dedup: shared engine-core @0x801292c8 (src/shared) */


DEFINE_func_8012931C()  /* dedup: shared engine-core @0x8012931c (src/shared) */


DEFINE_func_80129350()  /* dedup: shared engine-core @0x80129350 (src/shared) */


DEFINE_func_80129374()  /* dedup: shared engine-core @0x80129374 (src/shared) */


DEFINE_func_80129398()  /* dedup: shared engine-core @0x80129398 (src/shared) */


DEFINE_func_80129428()  /* dedup: shared engine-core @0x80129428 (src/shared) */


DEFINE_func_8012943C()  /* dedup: shared engine-core @0x8012943c (src/shared) */


DEFINE_func_8012944C()  /* dedup: shared engine-core @0x8012944c (src/shared) */






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


DEFINE_func_801298F4()  /* dedup: shared engine-core @0x801298f4 (src/shared) */



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

DEFINE_func_80129C40()  /* dedup: shared engine-core @0x80129c40 (src/shared) */


DEFINE_func_80129CF8()  /* dedup: shared engine-core @0x80129cf8 (src/shared) */


DEFINE_func_80129FF4()  /* dedup: shared engine-core @0x80129ff4 (src/shared) */


extern void func_8012A048(void *a0, s32 a1, u8 a2);

void func_8012A018(s32 a0, s32 a1)
{
    extern u8 D_80126948[];

    func_8012A048(D_80126948, a0, a1);
}


DEFINE_func_8012A048()  /* dedup: shared engine-core @0x8012a048 (src/shared) */


DEFINE_func_8012A094()  /* dedup: shared engine-core @0x8012a094 (src/shared) */


DEFINE_func_8012A0E0()  /* dedup: shared engine-core @0x8012a0e0 (src/shared) */


DEFINE_func_8012A100()  /* dedup: shared engine-core @0x8012a100 (src/shared) */


DEFINE_func_8012A110()  /* dedup: shared engine-core @0x8012a110 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012A1BC);

DEFINE_func_8012A2F4()  /* dedup: shared engine-core @0x8012a2f4 (src/shared) */


DEFINE_func_8012A304()  /* dedup: shared engine-core @0x8012a304 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012A328);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012A418);



typedef struct { s32 w[8]; } Vec8;


void func_8012A464(void)
{

    extern s32 D_801151D4;
    extern Vec8 D_80114F24;
    D_80114F24 = *(Vec8 *)(*(s32 *)&D_801151D4 + 0x3C);
}


DEFINE_func_8012A4BC()  /* dedup: shared engine-core @0x8012a4bc (src/shared) */


extern void func_8012A598(void *a0);
void func_8012A568(void (*a0)(void)) {
    func_8012A598(a0);
    a0();
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012A598);

DEFINE_func_8012A5F8()  /* dedup: shared engine-core @0x8012a5f8 (src/shared) */


DEFINE_func_8012A62C()  /* dedup: shared engine-core @0x8012a62c (src/shared) */


DEFINE_func_8012A68C()  /* dedup: shared engine-core @0x8012a68c (src/shared) */


DEFINE_func_8012A6D0()  /* dedup: shared engine-core @0x8012a6d0 (src/shared) */


DEFINE_func_8012A758()  /* dedup: shared engine-core @0x8012a758 (src/shared) */


DEFINE_func_8012A79C()  /* dedup: shared engine-core @0x8012a79c (src/shared) */


DEFINE_func_8012A7D4()  /* dedup: shared engine-core @0x8012a7d4 (src/shared) */


DEFINE_func_8012A828()  /* dedup: shared engine-core @0x8012a828 (src/shared) */


DEFINE_func_8012A860()  /* dedup: shared engine-core @0x8012a860 (src/shared) */


DEFINE_func_8012A8B0()  /* dedup: shared engine-core @0x8012a8b0 (src/shared) */


DEFINE_func_8012A8E8()  /* dedup: shared engine-core @0x8012a8e8 (src/shared) */


DEFINE_func_8012A908()  /* dedup: shared engine-core @0x8012a908 (src/shared) */


DEFINE_func_8012A988()  /* dedup: shared engine-core @0x8012a988 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012AAAC);


extern void func_8012AAAC(void);

void func_8012ACA0(void *arg0) {

    extern M2C_UNK D_8018325C;
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_8018325C;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s16 *, 0x9A) = 0;
    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
    func_8012AAAC();
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012ACE0);

DEFINE_func_8012AD44()  /* dedup: shared engine-core @0x8012ad44 (src/shared) */


DEFINE_func_8012AD50()  /* dedup: shared engine-core @0x8012ad50 (src/shared) */




void func_8012AD64(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x34) = a1;
}


DEFINE_func_8012AD6C()  /* dedup: shared engine-core @0x8012ad6c (src/shared) */


DEFINE_func_8012AD80()  /* dedup: shared engine-core @0x8012ad80 (src/shared) */


DEFINE_func_8012ADE4()  /* dedup: shared engine-core @0x8012ade4 (src/shared) */


DEFINE_func_8012AE00()  /* dedup: shared engine-core @0x8012ae00 (src/shared) */


DEFINE_func_8012AF0C()  /* dedup: shared engine-core @0x8012af0c (src/shared) */


DEFINE_func_8012B030()  /* dedup: shared engine-core @0x8012b030 (src/shared) */


DEFINE_func_8012B0B4()  /* dedup: shared engine-core @0x8012b0b4 (src/shared) */


DEFINE_func_8012B14C()  /* dedup: shared engine-core @0x8012b14c (src/shared) */


DEFINE_func_8012B178()  /* dedup: shared engine-core @0x8012b178 (src/shared) */


DEFINE_func_8012B1B4()  /* dedup: shared engine-core @0x8012b1b4 (src/shared) */


DEFINE_func_8012B200()  /* dedup: shared engine-core @0x8012b200 (src/shared) */


DEFINE_func_8012B21C()  /* dedup: shared engine-core @0x8012b21c (src/shared) */


DEFINE_func_8012B23C()  /* dedup: shared engine-core @0x8012b23c (src/shared) */


DEFINE_func_8012B260()  /* dedup: shared engine-core @0x8012b260 (src/shared) */


DEFINE_func_8012B2CC()  /* dedup: shared engine-core @0x8012b2cc (src/shared) */


DEFINE_func_8012B370()  /* dedup: shared engine-core @0x8012b370 (src/shared) */


DEFINE_func_8012B414()  /* dedup: shared engine-core @0x8012b414 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012B4B8);

DEFINE_func_8012B608()  /* dedup: shared engine-core @0x8012b608 (src/shared) */


DEFINE_func_8012B6D4()  /* dedup: shared engine-core @0x8012b6d4 (src/shared) */


DEFINE_func_8012B70C()  /* dedup: shared engine-core @0x8012b70c (src/shared) */


DEFINE_func_8012B744()  /* dedup: shared engine-core @0x8012b744 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012B77C);

DEFINE_func_8012B864()  /* dedup: shared engine-core @0x8012b864 (src/shared) */


DEFINE_func_8012B8A4()  /* dedup: shared engine-core @0x8012b8a4 (src/shared) */


DEFINE_func_8012B8E4()  /* dedup: shared engine-core @0x8012b8e4 (src/shared) */


DEFINE_func_8012BA10()  /* dedup: shared engine-core @0x8012ba10 (src/shared) */


DEFINE_func_8012BB3C()  /* dedup: shared engine-core @0x8012bb3c (src/shared) */


DEFINE_func_8012BC60()  /* dedup: shared engine-core @0x8012bc60 (src/shared) */


DEFINE_func_8012BCCC()  /* dedup: shared engine-core @0x8012bccc (src/shared) */


DEFINE_func_8012BD14()  /* dedup: shared engine-core @0x8012bd14 (src/shared) */


DEFINE_func_8012BD3C()  /* dedup: shared engine-core @0x8012bd3c (src/shared) */


DEFINE_func_8012BDBC()  /* dedup: shared engine-core @0x8012bdbc (src/shared) */


DEFINE_func_8012BE54()  /* dedup: shared engine-core @0x8012be54 (src/shared) */


DEFINE_func_8012BE98()  /* dedup: shared engine-core @0x8012be98 (src/shared) */


DEFINE_func_8012BEE8()  /* dedup: shared engine-core @0x8012bee8 (src/shared) */


DEFINE_func_8012BF10()  /* dedup: shared engine-core @0x8012bf10 (src/shared) */



void func_8012BF4C(s32 *a0, s32 a1) {
    *(s32*)((s32)a0 + 0x1C) = a1;
}


DEFINE_func_8012BF54()  /* dedup: shared engine-core @0x8012bf54 (src/shared) */


DEFINE_func_8012BF68()  /* dedup: shared engine-core @0x8012bf68 (src/shared) */


DEFINE_func_8012BF7C()  /* dedup: shared engine-core @0x8012bf7c (src/shared) */


DEFINE_func_8012BFA8()  /* dedup: shared engine-core @0x8012bfa8 (src/shared) */


DEFINE_func_8012C044()  /* dedup: shared engine-core @0x8012c044 (src/shared) */


DEFINE_func_8012C098()  /* dedup: shared engine-core @0x8012c098 (src/shared) */


DEFINE_func_8012C0EC()  /* dedup: shared engine-core @0x8012c0ec (src/shared) */


DEFINE_func_8012C194()  /* dedup: shared engine-core @0x8012c194 (src/shared) */


DEFINE_func_8012C1B8()  /* dedup: shared engine-core @0x8012c1b8 (src/shared) */


DEFINE_func_8012C1DC()  /* dedup: shared engine-core @0x8012c1dc (src/shared) */


DEFINE_func_8012C218()  /* dedup: shared engine-core @0x8012c218 (src/shared) */


DEFINE_func_8012C284()  /* dedup: shared engine-core @0x8012c284 (src/shared) */


DEFINE_func_8012C2D0()  /* dedup: shared engine-core @0x8012c2d0 (src/shared) */


DEFINE_func_8012C31C()  /* dedup: shared engine-core @0x8012c31c (src/shared) */


DEFINE_func_8012C354()  /* dedup: shared engine-core @0x8012c354 (src/shared) */


DEFINE_func_8012C438()  /* dedup: shared engine-core @0x8012c438 (src/shared) */


DEFINE_func_8012C51C()  /* dedup: shared engine-core @0x8012c51c (src/shared) */


DEFINE_func_8012C588()  /* dedup: shared engine-core @0x8012c588 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012C658);

DEFINE_func_8012C724()  /* dedup: shared engine-core @0x8012c724 (src/shared) */


DEFINE_func_8012C750()  /* dedup: shared engine-core @0x8012c750 (src/shared) */


DEFINE_func_8012C820()  /* dedup: shared engine-core @0x8012c820 (src/shared) */



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


DEFINE_func_8012CAE4()  /* dedup: shared engine-core @0x8012cae4 (src/shared) */


DEFINE_func_8012CB64()  /* dedup: shared engine-core @0x8012cb64 (src/shared) */


DEFINE_func_8012CBA4()  /* dedup: shared engine-core @0x8012cba4 (src/shared) */


DEFINE_func_8012CBCC()  /* dedup: shared engine-core @0x8012cbcc (src/shared) */


DEFINE_func_8012CBF4()  /* dedup: shared engine-core @0x8012cbf4 (src/shared) */


DEFINE_func_8012CC1C()  /* dedup: shared engine-core @0x8012cc1c (src/shared) */


DEFINE_func_8012CC40()  /* dedup: shared engine-core @0x8012cc40 (src/shared) */


DEFINE_func_8012CC64()  /* dedup: shared engine-core @0x8012cc64 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012CC88);

DEFINE_func_8012CE2C()  /* dedup: shared engine-core @0x8012ce2c (src/shared) */


DEFINE_func_8012CEB0()  /* dedup: shared engine-core @0x8012ceb0 (src/shared) */


DEFINE_func_8012CFA8()  /* dedup: shared engine-core @0x8012cfa8 (src/shared) */


DEFINE_func_8012D098()  /* dedup: shared engine-core @0x8012d098 (src/shared) */


DEFINE_func_8012D38C()  /* dedup: shared engine-core @0x8012d38c (src/shared) */


void func_8012D3AC(void) {
}

DEFINE_func_8012D3B4()  /* dedup: shared engine-core @0x8012d3b4 (src/shared) */


DEFINE_func_8012D4B4()  /* dedup: shared engine-core @0x8012d4b4 (src/shared) */


void func_8012D5DC(void) {
}

DEFINE_func_8012D5E4()  /* dedup: shared engine-core @0x8012d5e4 (src/shared) */


DEFINE_func_8012D624()  /* dedup: shared engine-core @0x8012d624 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012D664);

DEFINE_func_8012D714()  /* dedup: shared engine-core @0x8012d714 (src/shared) */




extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);

s32 func_8012DB84(void)
{

    extern M2C_UNK D_80183274;
    extern M2C_UNK D_8018327C;
    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, &D_80183274, &D_8018327C);
}


DEFINE_func_8012DBD0()  /* dedup: shared engine-core @0x8012dbd0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012DDA4);



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


DEFINE_func_8012DEB8()  /* dedup: shared engine-core @0x8012deb8 (src/shared) */


DEFINE_func_8012DF34()  /* dedup: shared engine-core @0x8012df34 (src/shared) */


DEFINE_func_8012DFBC()  /* dedup: shared engine-core @0x8012dfbc (src/shared) */


void func_8012DFCC(void) {
}

DEFINE_func_8012DFD4()  /* dedup: shared engine-core @0x8012dfd4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012E014);

DEFINE_func_8012E138()  /* dedup: shared engine-core @0x8012E138 (src/shared) */


s32 func_8012E27C(void) {
    return 1;
}


void func_8012E284(void) {
}

DEFINE_func_8012E28C()  /* dedup: shared engine-core @0x8012e28c (src/shared) */


DEFINE_func_8012E32C()  /* dedup: shared engine-core @0x8012e32c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012E364);

DEFINE_func_8012E470()  /* dedup: shared engine-core @0x8012e470 (src/shared) */


DEFINE_func_8012E4C8()  /* dedup: shared engine-core @0x8012e4c8 (src/shared) */


DEFINE_func_8012E504()  /* dedup: shared engine-core @0x8012e504 (src/shared) */


DEFINE_func_8012E544()  /* dedup: shared engine-core @0x8012e544 (src/shared) */


DEFINE_func_8012E57C()  /* dedup: shared engine-core @0x8012e57c (src/shared) */


DEFINE_func_8012E5CC()  /* dedup: shared engine-core @0x8012e5cc (src/shared) */


DEFINE_func_8012E688()  /* dedup: shared engine-core @0x8012e688 (src/shared) */


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

typedef struct { s32 m[3][3]; s32 t[3]; } MATRIX;
typedef struct { s32 vx, vy, vz; } VECTOR;


s32 func_8012E778(int param_1, int param_2)
{

    extern u8 D_800AF648;
    MATRIX *r0;
    int iVarX;
    int iVarY;
    int iVar3;
    int iVar4;
    int sp[6];

    sp[0] = (int)*(short *)(param_1 + 6);
    sp[1] = (int)*(short *)(param_1 + 10);
    sp[2] = (int)*(short *)(param_1 + 0xe);
    r0 = (MATRIX *)&D_800AF648;
    gte_SetRotMatrix(r0);
    gte_SetTransMatrix(r0);
    gte_ldlv0((VECTOR *)sp);
    gte_rtps();
    gte_stsxy((long *)((int)sp + 0x10));

    iVarX = (int)*(short *)((int)sp + 0x10);
    iVar3 = (short)param_2;
    if (iVarX >= 0) {
        if (iVar3 >= iVarX) goto cy;
        return 0;
    }
    if (iVar3 < -iVarX) return 0;
cy:
    iVarY = (int)*(short *)((int)sp + 0x12);
    iVar4 = param_2 >> 0x10;
    if (iVarY >= 0) {
        if (iVar4 >= iVarY) goto c1;
        return 0;
    }
    if (iVar4 < -iVarY) return 0;
c1:
    return 1;
}


DEFINE_func_8012E88C()  /* dedup: shared engine-core @0x8012e88c (src/shared) */


DEFINE_func_8012E8A8()  /* dedup: shared engine-core @0x8012e8a8 (src/shared) */


DEFINE_func_8012E8C4()  /* dedup: shared engine-core @0x8012e8c4 (src/shared) */


DEFINE_func_8012E8E0()  /* dedup: shared engine-core @0x8012e8e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012E9C0);



// @class: regalloc-order
// @stuck: none — MATCH (93 ins)


extern void func_80049CAC(s32 a0, s32 a1);

/* Blk16 lifted to src/shared/engine_types.h (Phase 22). */
typedef struct { s16 h[8]; } Buf;

void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3)
{
    Buf buf;
    s32 iVar4;
    register u32 v __asm__("$17");      /* $s1 */

    iVar4 = *(s32 *)(param_1 + 0x20);
    v = *(u32 *)(iVar4 + 0x20);

    if (v == 0) {
        *(Blk16 *)(param_3)        = *(Blk16 *)(iVar4 + 0x34);
        *(Blk16 *)((s32)param_3 + 0x10) = *(Blk16 *)(iVar4 + 0x44);
    } else if ((v & 0x1000000) != 0) {
        register s32 p __asm__("$16");
        s32 w;
        p = (s32)(v & 0xfeffffff);
        p = p + param_2 * 8;

        buf.h[0] = *(s16 *)(p + 6);
        w = *(s32 *)p;
        buf.h[1] = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8));
        buf.h[2] = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4));
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s8 *)(p + 3);
        param_3[6] = *(s8 *)(p + 4);
        param_3[7] = *(s8 *)(p + 5);
    } else {
        s32 q;
        v = v + param_2 * 0xc;
        q = (s32)v;
        buf.h[0] = *(s16 *)(q + 6);
        buf.h[1] = *(s16 *)(q + 8);
        buf.h[2] = *(s16 *)(q + 0xa);
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s16 *)(q + 0);
        param_3[6] = *(s16 *)(q + 2);
        param_3[7] = *(s16 *)(q + 4);
    }
}


DEFINE_func_8012EC04()  /* dedup: shared engine-core @0x8012ec04 (src/shared) */


DEFINE_func_8012EECC()  /* dedup: shared engine-core @0x8012eecc (src/shared) */


DEFINE_func_8012EF34()  /* dedup: shared engine-core @0x8012ef34 (src/shared) */


DEFINE_func_8012EF70()  /* dedup: shared engine-core @0x8012ef70 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012EFB8);

DEFINE_func_8012F038()  /* dedup: shared engine-core @0x8012f038 (src/shared) */


DEFINE_func_8012F0BC()  /* dedup: shared engine-core @0x8012f0bc (src/shared) */


DEFINE_func_8012F14C()  /* dedup: shared engine-core @0x8012f14c (src/shared) */


DEFINE_func_8012F1A4()  /* dedup: shared engine-core @0x8012f1a4 (src/shared) */


DEFINE_func_8012F214()  /* dedup: shared engine-core @0x8012f214 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012F274);

DEFINE_func_8012F2E8()  /* dedup: shared engine-core @0x8012f2e8 (src/shared) */


DEFINE_func_8012F374()  /* dedup: shared engine-core @0x8012f374 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012F40C);

INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_8012F49C);

DEFINE_func_8012F568()  /* dedup: shared engine-core @0x8012f568 (src/shared) */


DEFINE_func_8012F5F4()  /* dedup: shared engine-core @0x8012f5f4 (src/shared) */


DEFINE_func_8012F68C()  /* dedup: shared engine-core @0x8012f68c (src/shared) */


DEFINE_func_8012F75C()  /* dedup: shared engine-core @0x8012f75c (src/shared) */


DEFINE_func_8012F7B4()  /* dedup: shared engine-core @0x8012f7b4 (src/shared) */



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


DEFINE_func_8012F87C()  /* dedup: shared engine-core @0x8012f87c (src/shared) */



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


DEFINE_func_8012F91C()  /* dedup: shared engine-core @0x8012f91c (src/shared) */


DEFINE_func_8012F968()  /* dedup: shared engine-core @0x8012f968 (src/shared) */


DEFINE_func_8012FB54()  /* dedup: shared engine-core @0x8012fb54 (src/shared) */


DEFINE_func_8012FC30()  /* dedup: shared engine-core @0x8012fc30 (src/shared) */


DEFINE_func_8012FCA4()  /* dedup: shared engine-core @0x8012fca4 (src/shared) */



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


DEFINE_func_8012FDA8()  /* dedup: shared engine-core @0x8012fda8 (src/shared) */


DEFINE_func_8012FE70()  /* dedup: shared engine-core @0x8012fe70 (src/shared) */


DEFINE_func_8012FF00()  /* dedup: shared engine-core @0x8012ff00 (src/shared) */


DEFINE_func_8012FF4C()  /* dedup: shared engine-core @0x8012ff4c (src/shared) */


DEFINE_func_8012FF98()  /* dedup: shared engine-core @0x8012ff98 (src/shared) */


DEFINE_func_8013001C()  /* dedup: shared engine-core @0x8013001c (src/shared) */


DEFINE_func_80130088()  /* dedup: shared engine-core @0x80130088 (src/shared) */


DEFINE_func_801300F4()  /* dedup: shared engine-core @0x801300f4 (src/shared) */


DEFINE_func_801301E8()  /* dedup: shared engine-core @0x801301e8 (src/shared) */


DEFINE_func_80130278()  /* dedup: shared engine-core @0x80130278 (src/shared) */


DEFINE_func_80130314()  /* dedup: shared engine-core @0x80130314 (src/shared) */


DEFINE_func_80130360()  /* dedup: shared engine-core @0x80130360 (src/shared) */


DEFINE_func_801303A0()  /* dedup: shared engine-core @0x801303a0 (src/shared) */


DEFINE_func_801303EC()  /* dedup: shared engine-core @0x801303ec (src/shared) */


DEFINE_func_80130438()  /* dedup: shared engine-core @0x80130438 (src/shared) */


DEFINE_func_80130514()  /* dedup: shared engine-core @0x80130514 (src/shared) */


DEFINE_func_801305CC()  /* dedup: shared engine-core @0x801305cc (src/shared) */


DEFINE_func_80130650()  /* dedup: shared engine-core @0x80130650 (src/shared) */


DEFINE_func_80130740()  /* dedup: shared engine-core @0x80130740 (src/shared) */


DEFINE_func_801307B0()  /* dedup: shared engine-core @0x801307b0 (src/shared) */


DEFINE_func_80130858()  /* dedup: shared engine-core @0x80130858 (src/shared) */


DEFINE_func_80130898()  /* dedup: shared engine-core @0x80130898 (src/shared) */


DEFINE_func_801308DC()  /* dedup: shared engine-core @0x801308dc (src/shared) */


DEFINE_func_80130974()  /* dedup: shared engine-core @0x80130974 (src/shared) */


DEFINE_func_80130A18()  /* dedup: shared engine-core @0x80130a18 (src/shared) */


DEFINE_func_80130AC4()  /* dedup: shared engine-core @0x80130ac4 (src/shared) */


DEFINE_func_80130AF0()  /* dedup: shared engine-core @0x80130af0 (src/shared) */


DEFINE_func_80130C08()  /* dedup: shared engine-core @0x80130C08 (src/shared) */



void func_80130D0C(s32 a0) {

    extern void (*D_801832C0[])(void);
    D_801832C0[*(u8 *)((s32)a0 + 0xC1)]();
}


INCLUDE_ASM("asm/ov_SC07_007/nonmatchings/ov_SC07_007", func_80130D48);

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

typedef struct { char _b[8]; } M8;   /* size 8, alignment 1 -> unaligned copy */


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
