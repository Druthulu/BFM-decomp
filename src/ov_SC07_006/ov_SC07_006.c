#include "common.h"
#include "../shared/engine_core.h"

DEFINE_func_80128158()  /* dedup: shared engine-core @0x80128158 (src/shared) */


DEFINE_func_80128178()  /* dedup: shared engine-core @0x80128178 (src/shared) */


DEFINE_func_80128198()  /* dedup: shared engine-core @0x80128198 (src/shared) */


DEFINE_func_801281B8()  /* dedup: shared engine-core @0x801281b8 (src/shared) */


DEFINE_func_801281D8()  /* dedup: shared engine-core @0x801281d8 (src/shared) */


DEFINE_func_801281F8()  /* dedup: shared engine-core @0x801281f8 (src/shared) */




s32 func_80128218(void) {

    extern s32 D_801F3B6C;
    return D_801F3B6C;
}


DEFINE_func_80128228()  /* dedup: shared engine-core @0x80128228 (src/shared) */


DEFINE_func_80128248()  /* dedup: shared engine-core @0x80128248 (src/shared) */


DEFINE_func_80128268()  /* dedup: shared engine-core @0x80128268 (src/shared) */




void func_80128288(void) {

    extern u16 D_800B99F6;
    extern void (*D_8018A6A4[])(void);
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_8018A6A4[v1]();
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

    extern s32 D_801F4D5C;
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
        "lui   $at, %%hi(D_801F4D5C)\n"
        "sw    $v0, %%lo(D_801F4D5C)($at)\n"
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
        "lui   $v0, %%hi(D_801F4D5C)\n"
        "lw    $v0, %%lo(D_801F4D5C)($v0)\n"
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
 * at *(0x1F8003FC), calls func_800D19F0, stashes its $v0 result through D_801F4D5C,
 * restores $sp, then dispatches on the stored value:
 *   if (D_801F4D5C != 0)  { func_8001903C(); func_80018FC8(); }
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

    extern s32 D_801F4D5C;
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
        "lui   $at, %%hi(D_801F4D5C)\n"
        "sw    $v0, %%lo(D_801F4D5C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801F4D5C)\n"
        "lw    $v0, %%lo(D_801F4D5C)($v0)\n"
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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801287B8);



extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_801288B0(void) {

    extern s32 D_801F3B6C;
    extern u8 D_800AEFD0;
    func_8001ABBC(0, 0, &D_800AEFD0, D_801F3B6C, 0);
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
    extern int D_801F3B6C;
    int *p = &D_800C7C60;
    *p = 0x60;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AF558, D_801F3B6C, p);
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
    extern int D_801F3B6C;
    int *p = &D_800C7C60;
    *p = 0x5e;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AF560, D_801F3B6C, p);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80128998);



extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_801289F0(void) {

    extern s32 D_801F3B6C;
    extern u8 D_800AECB8;
    func_8001ABBC(0, 0, &D_800AECB8, D_801F3B6C, 0);
}


extern void func_80011B7C(int);
extern void func_80011C10(void);

void func_80128A28(void) {

    extern u16 D_800B99F6;
    extern s16 D_800B9A00;
    extern M2C_UNK (*D_8018A3E0)();
    extern s16 (*D_8018A3E4)();
    s16 temp_v0;

    switch (D_800B99F6) {                           /* irregular */
    case 1:
        D_8018A3E0();
        /* fallthrough */
    case 0:
        func_80011C10();
        return;
    case 2:
        temp_v0 = D_8018A3E4();
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
    extern M2C_UNK (*D_8018A3EC)();
    extern s32 (*D_8018A3F0)();
    extern s32 D_801F4D58;
    switch (D_800B99F6) {                           /* irregular */
    case 0:
        D_801F4D58 = func_8002AF08();
        func_80011C10();
        return;
    case 1:
        D_8018A3EC();
        func_80011C10();
        return;
    case 2:
        if ((D_8018A3F0() << 0x10) != 0) {
            if (D_801F4D58 == 1) {
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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80128C98);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80128CFC);

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

    extern M2C_UNK D_801F3B70;
    func_8001534C(4, &D_801F3B70, 0x80, 0x90, 0, 0);
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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012956C);

DEFINE_func_801298F4()  /* dedup: shared engine-core @0x801298f4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801299C8);

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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012A1BC);

DEFINE_func_8012A2F4()  /* dedup: shared engine-core @0x8012a2f4 (src/shared) */


DEFINE_func_8012A304()  /* dedup: shared engine-core @0x8012a304 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012A328);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012A418);



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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012A598);

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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012AAAC);


extern void func_8012AAAC(void);

void func_8012ACA0(void *arg0) {

    extern M2C_UNK D_8018A738;
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_8018A738;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s16 *, 0x9A) = 0;
    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
    func_8012AAAC();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012ACE0);

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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012B4B8);

DEFINE_func_8012B608()  /* dedup: shared engine-core @0x8012b608 (src/shared) */


DEFINE_func_8012B6D4()  /* dedup: shared engine-core @0x8012b6d4 (src/shared) */


DEFINE_func_8012B70C()  /* dedup: shared engine-core @0x8012b70c (src/shared) */


DEFINE_func_8012B744()  /* dedup: shared engine-core @0x8012b744 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012B77C);

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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012C658);

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

    extern s32   D_8018DC1C;
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
    *(s32 *)(dst + 0x78) = (s32)&D_8018DC1C;
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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012CC88);

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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012D664);

DEFINE_func_8012D714()  /* dedup: shared engine-core @0x8012d714 (src/shared) */




extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);

s32 func_8012DB84(void)
{

    extern M2C_UNK D_8018A750;
    extern M2C_UNK D_8018A758;
    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, &D_8018A750, &D_8018A758);
}


DEFINE_func_8012DBD0()  /* dedup: shared engine-core @0x8012dbd0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012DDA4);



// @class: plumbing
// @stuck: none — MATCH (35/35 ins, relocation-masked)


s32 func_8012DE2C(s32 a0) {

    extern u8 D_801202A0[];
    extern u8 * D_801F4D7C;
    extern u8 * D_801F4D78;

    u8 *base;
    u8 *end;
    u8 *p;

    base = D_801202A0;
    end = base + 0x6480;
    D_801F4D7C = base;
    D_801F4D78 = ((u8 *)a0);

    while (D_801F4D7C != end) {
        p = D_801F4D7C;
        if (*(u16 *)p != 0 && p != ((u8 *)a0)) {
            D_801F4D7C = p + 0x10C;
            return p;
        }
        D_801F4D7C += 0x10C;
    }
    D_801F4D7C = 0;
    return 0;
}


DEFINE_func_8012DEB8()  /* dedup: shared engine-core @0x8012deb8 (src/shared) */


DEFINE_func_8012DF34()  /* dedup: shared engine-core @0x8012df34 (src/shared) */


DEFINE_func_8012DFBC()  /* dedup: shared engine-core @0x8012dfbc (src/shared) */


void func_8012DFCC(void) {
}

DEFINE_func_8012DFD4()  /* dedup: shared engine-core @0x8012dfd4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012E014);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012E138);


s32 func_8012E27C(void) {
    return 1;
}


void func_8012E284(void) {
}

DEFINE_func_8012E28C()  /* dedup: shared engine-core @0x8012e28c (src/shared) */


DEFINE_func_8012E32C()  /* dedup: shared engine-core @0x8012e32c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012E364);

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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012E9C0);



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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012EFB8);

DEFINE_func_8012F038()  /* dedup: shared engine-core @0x8012f038 (src/shared) */


DEFINE_func_8012F0BC()  /* dedup: shared engine-core @0x8012f0bc (src/shared) */


DEFINE_func_8012F14C()  /* dedup: shared engine-core @0x8012f14c (src/shared) */


DEFINE_func_8012F1A4()  /* dedup: shared engine-core @0x8012f1a4 (src/shared) */


DEFINE_func_8012F214()  /* dedup: shared engine-core @0x8012f214 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012F274);

DEFINE_func_8012F2E8()  /* dedup: shared engine-core @0x8012f2e8 (src/shared) */


DEFINE_func_8012F374()  /* dedup: shared engine-core @0x8012f374 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012F40C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8012F49C);

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

    extern unsigned char D_8018A77C[];
    *(unsigned char *)(param_1 + 0xC1) = 4;
    if (*(unsigned int *)(param_1 + 0xB4) & 8) {
        func_80131170(param_1, D_8018A77C, 0xB);
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

    extern unsigned char D_8018A788[];
    *(unsigned char *)(param_1 + 0xC1) = 7;
    if (*(unsigned int *)(param_1 + 0xB4) & 128) {
        func_80131170(param_1, D_8018A788, 0xB);
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

    extern int  D_8018A794;
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
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_8018A794);
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


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80130C08);



void func_80130D0C(s32 a0) {

    extern void (*D_8018A79C[])(void);
    D_8018A79C[*(u8 *)((s32)a0 + 0xC1)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80130D48);

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
    extern u8 D_8018A770[];

    func_80131B14();
    *(u8 *)(((u8 *)p) + 0xC2) = 0;
    *(u8 *)(((u8 *)p) + 0xC3) = 0;
    *(s16 *)(((u8 *)p) + 0x98) = 0;
    if (((u8 *)b) == 0) {
        ((u8 *)b) = D_8018A770;
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
    extern M8 D_8018A8C4;

    int iVar5;

    iVar5 = func_80131CF4(*(int *)(((int)param_1) + 0xBC), 0x2E);
    if (iVar5 != 0) {
        ((short *)param_2)[2] = 0;
        ((short *)param_2)[0] = 0;
        ((short *)param_2)[1] = (short)iVar5;
    } else {
        *(M8 *)((short *)param_2) = D_8018A8C4;
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80131340);

DEFINE_func_801319E0()  /* dedup: shared engine-core @0x801319e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80131A34);

DEFINE_func_80131AC8()  /* dedup: shared engine-core @0x80131ac8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80131B14);

DEFINE_func_80131C78()  /* dedup: shared engine-core @0x80131c78 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80131CA8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80131CF4);

DEFINE_func_80131D68()  /* dedup: shared engine-core @0x80131d68 (src/shared) */





void func_80131E00(struct S80131E00 *a0, s32 a1) {

    extern void (*D_8018A8DC[])(struct S80131E00 *a0);
    a0->field_B0 = a1;
    D_8018A8DC[a1](a0);
}


DEFINE_func_80131E38()  /* dedup: shared engine-core @0x80131e38 (src/shared) */


DEFINE_func_80131E7C()  /* dedup: shared engine-core @0x80131e7c (src/shared) */


void func_80131EE4(void) {
}



void func_80131EEC(void *a0) {

    extern void (*D_8018A934[])(void);
    D_8018A934[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131F28(void *a0) {

    extern void (*D_8018A97C[])(void);
    D_8018A97C[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131F64(void *a0) {

    extern void (*D_8018A984[])(void);
    D_8018A984[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131FA0(void *a0) {

    extern void (*D_8018A98C[])(void);
    D_8018A98C[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131FDC(void *a0) {

    extern void (*D_8018A994[])(void);
    D_8018A994[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80132018);

void func_801320D0(void) {
}


// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

void func_801320D8(int param_1)
{

    extern int D_8018A93C;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018A93C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

void func_80132144(int param_1)
{

    extern int D_8018A94C;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018A94C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

void func_801321B0(int param_1)
{

    extern int D_8018A95C;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018A95C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

void func_8013221C(int param_1)
{

    extern int D_8018A96C;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018A96C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}


DEFINE_func_80132288()  /* dedup: shared engine-core @0x80132288 (src/shared) */


DEFINE_func_8013240C()  /* dedup: shared engine-core @0x8013240c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801325B8);

void func_8013277C(void) {
}

DEFINE_func_80132784()  /* dedup: shared engine-core @0x80132784 (src/shared) */


DEFINE_func_80132DC4()  /* dedup: shared engine-core @0x80132dc4 (src/shared) */


DEFINE_func_80132E6C()  /* dedup: shared engine-core @0x80132e6c (src/shared) */


void func_80132EC4(void *a0, s16 a1) {
    while (*(s32 *)a0 != 0) {
        *(s16 *)((s32)a0 + 4) = a1;
        a0 = (void *)((s32)a0 + 8);
    }
}


DEFINE_func_80132EF4()  /* dedup: shared engine-core @0x80132ef4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80132F40);

DEFINE_func_80133060()  /* dedup: shared engine-core @0x80133060 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801330E0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80133298);

DEFINE_func_8013339C()  /* dedup: shared engine-core @0x8013339c (src/shared) */


DEFINE_func_8013361C()  /* dedup: shared engine-core @0x8013361c (src/shared) */



// @class: plumbing
// @stuck: none — MATCH

extern void func_80136BC4(s32 a0);

void func_801336E8(void *a0, int a1, int a2) {

    extern s32 D_801F4DC8;
    extern s32 D_801F4DCC[];
    extern int D_801F4DD0;
    if (a0 != 0) {
        (*(void * *)&D_801F4DC8) = a0;
        ((void (*)(void))func_80136BC4)();
    }
    (*(int *)&D_801F4DCC) = a1;
    D_801F4DD0 = a2;
}




extern void func_80136BC4(s32);

void func_8013373C(s16 arg0) {

    extern s32 D_801F4DCC[];
    extern s32 D_801F4DC8;
    s32 temp = D_801F4DCC[arg0];
    if (temp != 0) {
        D_801F4DC8 = temp;
        func_80136BC4(temp);
    }
}



typedef struct { u16 f0, f2, f4; s16 f6; } Box_80133784;


s32 func_80133784(s32 arg0, void *arg1, s32 arg2) {

    extern s32 D_801F4DC8;
    extern s32 func_80047D3C(s32);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern Box_80133784 * D_8018A99C;
    extern Box_80133784 * D_8018A9A0;
    extern s16 D_801F4DD4;
    extern u16 D_801F4DD8;

    register s32 s1 __asm__("$17");
    s32 s2;
    register s16 s3 __asm__("$19");
    register s32 s4 __asm__("$20");
    register s16 a0v __asm__("$4");
    register s16 arg0s __asm__("$21");
    s32 dx, dy, dz;
    s32 r, ret;

    a0v = ((s16)arg0);
    s1 = 0;
    s3 = 0;
    s4 = 0;
    s2 = 0;
    arg0s = a0v;
    D_8018A99C->f6 = -0x7FFF;
    D_8018A9A0->f6 = 0x7FFF;
    D_8018A99C->f0 = ((Box_80133784 *)arg1)->f0;
    D_8018A99C->f4 = ((Box_80133784 *)arg1)->f4;
    D_8018A9A0->f0 = ((Box_80133784 *)arg2)->f0;
    D_8018A9A0->f4 = ((Box_80133784 *)arg2)->f4;
    D_801F4DD8 = 0;
    D_801F4DD4 = 0;

    if ((s16)a0v == 0) {
        s16 sx = ((Box_80133784 *)arg2)->f0 - ((Box_80133784 *)arg1)->f0;
        s16 sy = ((Box_80133784 *)arg2)->f2 - ((Box_80133784 *)arg1)->f2;
        s16 sz = ((Box_80133784 *)arg2)->f4 - ((Box_80133784 *)arg1)->f4;
        if (sx == 0 && sy == 0) {
            s32 zt = (sz == 0);
            __asm__("addu %0,%1,$zero" : "=r"(s2) : "r"(zt));
        }
        D_8018A99C->f2 = ((Box_80133784 *)arg1)->f2 - 4;
        r = func_80047D3C(sx * sx + sz * sz);
        if (r < 3) {
            r = 4;
        } else if (r < 5) {
            r += 1;
        }
        D_8018A9A0->f2 = ((Box_80133784 *)arg2)->f2 + r + 1;
    } else {
        D_8018A99C->f2 = ((Box_80133784 *)arg1)->f2;
        if ((s16)a0v == 2) {
            D_8018A9A0->f0 = D_8018A99C->f0;
            D_8018A9A0->f2 = D_8018A99C->f2 + 6;
            s2 = 1;
            D_8018A9A0->f4 = D_8018A99C->f4;
        } else {
            D_8018A9A0->f2 = ((Box_80133784 *)arg2)->f2;
        }
    }

    while (1) {
        s32 ret0;
        register s32 retc __asm__("$3");
        __asm__ __volatile__("");
        ret0 = func_80133AB0(arg0s, (s16)D_8018A99C->f0, (s16)D_8018A99C->f4, (*(s32*)&D_801F4DC8));
        __asm__("addu %0,%1,$zero" : "=r"(retc) : "r"(ret0));
        ret = retc;
        if (ret == 0) goto after;
        s4 |= ret;
        if (s2 != 0) goto after;
        {
            s16 oldc = s3;
            s3 = s3 + 1;
            if (oldc >= 5) break;
        }
    }

    D_8018A9A0->f0 = D_8018A99C->f0;
    D_8018A9A0->f2 = D_8018A99C->f2;
    s1 = 0x2000;
    D_8018A9A0->f4 = D_8018A99C->f4;
    goto store_out;

after:
    if ((s16)s4 != 0 || D_801F4DD4 != 0) {
        s16 t;
        __asm__ __volatile__("" :: "r"(s4));
        t = D_8018A99C->f6;
        if (t >= -0xBCB) {
            if (t < -0x578) {
                s1 |= 0x4000;
            } else {
                s1 |= 0x8000;
            }
        }
        if ((s16)D_8018A9A0->f6 < -0xBCB) {
            s1 |= 0x2000;
        }
    store_out:
        ((Box_80133784 *)arg2)->f0 = D_8018A9A0->f0;
        ((Box_80133784 *)arg2)->f2 = D_8018A9A0->f2;
        ((Box_80133784 *)arg2)->f4 = D_8018A9A0->f4;
        ((Box_80133784 *)arg2)->f6 = D_801F4DD8;
        return s1 & 0xFFFF;
    }
    ((Box_80133784 *)arg2)->f6 = D_801F4DD8;
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80133AB0);


s32 func_80133CD4(arg0, cmd, base, arr)
    s16 arg0;
    s16 *cmd;
    s16 *base;
    s32 *arr;
{
    typedef struct { s16 e[4]; } ElemK;

    extern u16 *D_8018A9A0;
    extern u16 *D_8018A99C;
    extern s16 *D_8018A9A8;
    extern s16 *D_8018A9A4;
    extern s32 *D_8018A9B0;
    extern s32 *D_8018A9B4;
    extern u16 D_801F4DD8;
    extern u8  D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern u16 D_801152AE;
    extern u8  D_801152B0;
    extern s32 func_80134310();
    extern s32 func_8013435C();

    s16 *s3 = ((ElemK *)base)[cmd[1]].e;
    s32 s6 = arr[cmd[2]];
    s32 s0var, s1var;
    s32 s2a;
    s16 y;

    if (func_80134310(s3, D_8018A9A0, s6) >= 0)
        return 0;

    s1var = func_80134310(s3, D_8018A99C, s6);
    if (s1var < 0)
        return 0;

    s0var = func_80134310(s3, D_8018A9A8, 0);
    {
        u16 *pac = D_8018A99C;
        s16 *pb8 = D_8018A9A8;
        s16 *pb4 = D_8018A9A4;
        s32 neg = -s1var;
        pb4[0] = pac[0] + neg * pb8[0] / s0var;
        pb4[1] = pac[1] + neg * pb8[1] / s0var;
        pb4[2] = pac[2] + neg * pb8[2] / s0var;
        if (func_8013435C(((ElemK *)base)[cmd[3]].e, pb4, arr[cmd[4]], s3))
            return 0;
    }
    if (func_8013435C(((ElemK *)base)[cmd[5]].e, D_8018A9A4, arr[cmd[6]], s3))
        return 0;
    if (func_8013435C(((ElemK *)base)[cmd[7]].e, D_8018A9A4, arr[cmd[8]], s3))
        return 0;
    if (arg0 < 0) {
        if (func_8013435C(((ElemK *)base)[cmd[9]].e, D_8018A9A4, arr[cmd[10]], s3))
            return 0;
    }
    if (arg0 & 0x10) {
        if (*(u16 *)cmd & 0x100)
            return 0;
    }
    if (*(u16 *)cmd & 0x200) {
        D_801F4DD8 = *(u16 *)cmd;
        return 0;
    }

    {
        s32 ret = func_80134310(s3, D_8018A9A0, s6);
        s32 *pc0;
        s32 *pc4;
        u16 *pb0;
        s32 t, o2;
        s32 q3v;

        {
            s32 *pw = D_8018A9B0;
            ((struct { s32 w; } *)pw)->w = s3[0];
            pw[1] = s3[1];
            pw[2] = s3[2];
        }
        s1var = -ret;

        __asm__ __volatile__(
            "lwc2 $9, 0(%0)\n"
            "lwc2 $10, 4(%0)\n"
            "lwc2 $11, 8(%0)\n"
            "nop\n"
            "nop\n"
            "sqr 0\n"
            : : "r"(D_8018A9B0) : "$9", "$10", "$11", "memory");
        __asm__ __volatile__(
            "swc2 $25, 0(%0)\n"
            "swc2 $26, 4(%0)\n"
            "swc2 $27, 8(%0)\n"
            : : "r"(D_8018A9B4) : "memory");

        pc0 = D_8018A9B0;
        pc4 = D_8018A9B4;
        s0var = pc4[0] + pc4[1] + pc4[2];
        pb0 = D_8018A9A0;
        pb0[0] += s1var * pc0[0] / s0var;
        pb0[1] += s1var * pc0[1] / s0var;
        q3v = s1var * pc0[2] / s0var;

        {
            s32 h;
            h = ((s16 *)pb0)[0];
            s1var = h << 16;
            __asm__("lh %0, 2(%2)" : "=r"(h) : "0"(h), "r"(pb0) : "memory");
            s0var = h << 16;
        }
        pb0[2] += q3v;
        s2a = (s16)pb0[2] << 16;

        t = pc0[0] << 4;
        pc0[0] = t;
        if (t < 0) s1var |= 0xFFFF;
        t = pc0[1] << 4;
        pc0[1] = t;
        if (t < 0) s0var |= 0xFFFF;
        o2 = pc0[2];
        t = o2 << 4;
        pc0[2] = t;
        if (t < 0) s2a |= 0xFFFF;
        s2a += o2 << 5;
        s1var += pc0[0] << 1;
        s0var += pc0[1] << 1;

        do {
            s32 *pl = D_8018A9B0;
            u16 *pb;
            s1var += pl[0];
            s0var += pl[1];
            s2a += pl[2];
            pb = D_8018A9A0;
            pb[0] = s1var >> 16;
            pb[1] = s0var >> 16;
            pb[2] = s2a >> 16;
            ret = func_80134310(s3, pb, s6);
        } while (ret < ((s3[1] < -0xE00) ? 0x1800 : 0x2F00));
    }

    y = s3[1];
    if (y >= -0xBCB) {
        D_8018A99C[3] = y;
        {
            typedef struct { s8 c[8]; } Blk8;
            *(Blk8 *)&D_801152B0 = *(Blk8 *)s3;
        }
        if (*(u8 *)cmd != 0)
            goto ret1;
        return -1;
    }
    {
        typedef struct { u16 h; } H16;
        u16 *s3u = (u16 *)s3;
        u16 *bp = D_8018A9A0;
        u16 w;
        ((H16 *)D_801152A8)->h = s3u[0];
        w = s3u[1];
        bp[3] = w;
        ((H16 *)&D_801152AA)->h = w;
        ((H16 *)&D_801152AC)->h = s3u[2];
        ((H16 *)&D_801152AE)->h = s3u[3];
    }
ret1:
    return 1;
}




typedef struct { s16 x, y, z; } Vec3s;

s32 func_80134310(Vec3s *a0, Vec3s *a1, s32 a2) {
    return a0->x * a1->x + a0->y * a1->y + a0->z * a1->z + a2;
}


DEFINE_func_8013435C()  /* dedup: shared engine-core @0x8013435c (src/shared) */



// @class: schedule
// @stuck: none — MATCH (83 ins, relocation-masked)



s32 func_801343C4(s32 angle, s32 p1, s32 p2)
{

    extern s32 D_801F4DC8;
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern s16 * D_8018A99C;
    extern s16 * D_8018A9A0;
    extern u16 D_801F4DD8;
    extern u16 D_801F4DD4;

    s16 *pac;
    s16 *pb0;
    s16 *pacs, *pb0s;
    u16 *pb0u;
    int a1v, a2v, d94, b0;
    int sangle = ((s16)angle);

    pac = D_8018A99C;
    d94 = D_801F4DC8;
    pb0 = D_8018A9A0;
    pac[0] = ((u16 *)p1)[0];
    pac[1] = ((u16 *)p1)[1];
    pac[2] = ((u16 *)p1)[2];
    pb0[0] = ((u16 *)p2)[0];
    pb0[1] = ((u16 *)p2)[1];
    pb0[2] = ((u16 *)p2)[2];

    a1v = pac[0]; a2v = pac[2];
    __asm__ __volatile__("" ::: "memory");
    D_801F4DD8 = 0;
    D_801F4DD4 = 0;
    if (func_80133AB0(sangle, a1v, a2v, d94)) {
    setdst:
        pb0u = (u16 *)D_8018A9A0;
        ((u16 *)p2)[0] = pb0u[0];
        ((u16 *)p2)[1] = pb0u[1];
        ((u16 *)p2)[2] = pb0u[2];
        ((u16 *)p2)[3] = D_801F4DD8;
        return 1;
    }

    pacs = D_8018A99C;
    pb0s = D_8018A9A0;
    b0 = pb0s[0];
    if ((pacs[0] & 0xFF80) == (b0 & 0xFF80) &&
        (pacs[2] & 0xFF80) == (pb0s[2] & 0xFF80)) {
        return 0;
    }
    if (func_80133AB0(sangle, b0, pb0s[2], D_801F4DC8)) {
        goto setdst;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80134510);


// @class: regalloc-order
// @stuck: 26-mismatch near-miss (structure fully matches: while-loop test-first via j-to-bottom-test, s0=puVar7/s1=cnt/s2=scan/s3=iVar8/s4=iVar9/s5=uVar3/s6=uVar10, a1=param/a0=cc/a3=0x8000 pinned, both range-persist copies present, mult+GPU-index+call all byte-correct). Residual = 4 instances of ONE gcc-2.7.2 regalloc/copy-prop tie-break: target computes a preserved-then-masked value in $v0 and reads $v0 for the mask (`subu $v0; addu $persist,$v0; andi $v0,$v0`), gcc here reads the persist reg (`andi $v0,$t0`). (1) range-check-1 andi reads $t0 not $v0; (2) range-check-2 andi reads $a0 not $v0; (3) `hi=uVar1&0x8000` folds into $a0 — target computes in $v0 + copies to $a0 in the branch-delay (same-block copy, gcc coalesces mine); (4) loop-test `cnt&0xffff` folds to direct `andi $v0,$s1` — target copies `addu $v0,$s1` first. Splitting the value into compare-temp + persist-var produces the copy but gcc forward-propagates the copy DEST into the mask; persist-after-compare kills the copy; explicit `register __asm__` pins fold the whole expr chain into the pinned reg; `=r/0` barriers force bad materialization. Also minor: while-loop header-copy adds a `beqz s1` entry guard vs target `j`, and a2/a3 call-arg setup order. Permuter can't run (register __asm__ pins rejected by pycparser). Genuinely compiler-internal — hand-finish or accept as ceiling.


s32 func_801345F8(s32 arg)
{
    extern int func_801347A0(short, u16 *, int, int);
    extern u16 * D_8018A99C;
    extern u16 D_801F4DD8;

    register u16 *param_1 __asm__("$5") = ((u16 *)arg);
    register u16 *cc __asm__("$4") = D_8018A99C;
    int c8000 = 0x8000;
    register int zr __asm__("$0");
    u32 c1, c2, uVar6, uVar2, cnt, v14;
    u16 *ptmp, *puVar4, *puVar7, uVar1;
    int hi, harg, iVar9, iVar8, uVar3, uVar10, tbl;

    c1 = ((int)(cc[0] + c8000) >> 7 & 0x1ff) - (u32)param_1[0];
    uVar6 = c1 + zr;
    if ((c1 & 0xffff) < (u32)param_1[2]) {
        c2 = ((int)(cc[2] + c8000) >> 7 & 0x1ff) - (u32)param_1[1];
        uVar2 = c2 + zr;
        if ((c2 & 0xffff) < (u32)param_1[3])
            goto do_mult;
        return 0;
      found:
        D_801F4DD8 = *puVar7;
        return 1;
      do_mult:
        tbl = *(int *)(param_1 + 4);
        uVar10 = *(int *)(param_1 + 6);
        uVar3 = *(int *)(param_1 + 8);
        iVar9 = *(int *)(param_1 + 0xc);
        iVar8 = *(int *)(param_1 + 0xe);
        ptmp = (u16 *)((((u32)(u16)uVar2 * (u32)param_1[2] + (u32)(u16)uVar6) * 2 & 0xffff) * 2 + tbl);
        cnt = (u32)ptmp[1];
        v14 = *(int *)(param_1 + 10);
        puVar4 = (u16 *)(v14 + (u32)*ptmp + cnt * 2) - 1;
        while (((cnt-- + zr) & 0xffff) != 0) {
            uVar1 = *puVar4;
            hi = uVar1 & 0x8000;
            harg = hi + zr;
            if (hi == 0)
                puVar7 = (u16 *)(iVar9 + (u32)uVar1 * 0x12);
            else
                puVar7 = (u16 *)(iVar8 + (uVar1 & 0x7fff) * 0x16);
            if (func_801347A0((short)harg, puVar7, uVar3, uVar10) != 0)
                goto found;
            puVar4 = puVar4 - 1;
        }
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801347A0);

DEFINE_func_80134A28()  /* dedup: shared engine-core @0x80134a28 (src/shared) */



int func_80134A74(int param_1, s16 param_2, s16 param_3, int param_4)
{
    extern u16 D_801F4DD8;
    extern s32 func_80134C20(s32, s32, s32, s32);

    u16 *param_4p = (u16 *)param_4;
    register u32 zr __asm__("$0");
    u32 uVar6, uVar2, uVar2c;
    register u32 uVar6c __asm__("$9");
    u16 *puVar4, *ptmp;
    register u32 n __asm__("$18");
    register u32 p0 __asm__("$4");
    register int v14 __asm__("$3");
    u16 *puVar7, uVar1;
    u32 hi, hic;
    int iVar5, iVar9, iVar8, uVar3, uVar10;

    uVar6 = ((int)((param_2 & 0xffff) + 0x8000) >> 7 & 0x1ff) - (u32)param_4p[0];
    uVar6c = uVar6 + zr;
    if ((uVar6 & 0xffff) < (u32)param_4p[2]) {
        uVar2 = ((int)((param_3 & 0xffff) + 0x8000) >> 7 & 0x1ff) - (u32)param_4p[1];
        __asm__("addu %0,%1,$zero" : "=r"(uVar2c) : "r"(uVar2));
        if ((uVar2 & 0xffff) < (u32)param_4p[3]) goto work;
        return 0;
    found:
        D_801F4DD8 = *puVar7;
        return 1;
    work:
        uVar10 = *(int *)(param_4p + 6);
        uVar3 = *(int *)(param_4p + 8);
        iVar9 = *(int *)(param_4p + 0xc);
        iVar8 = *(int *)(param_4p + 0xe);
        ptmp = (u16 *)((((uVar2c & 0xffff) * (u32)param_4p[2] + (uVar6c & 0xffff)) * 2 & 0xffff) * 2 + *(int *)(param_4p + 4));
        v14 = *(int *)(param_4p + 10);
        __asm__ __volatile__("" :: "r"(uVar6c));
        p0 = (u32)*ptmp;
        n = (u32)ptmp[1];
        puVar4 = (u16 *)(v14 + p0 + n * 2) - 1;
        goto test;
    body:
        uVar1 = *puVar4;
        hi = uVar1 & 0x8000;
        hic = hi + zr;
        if (hi == 0)
            puVar7 = (u16 *)(iVar9 + (u32)uVar1 * 0x12);
        else
            puVar7 = (u16 *)(iVar8 + (uVar1 & 0x7fff) * 0x16);
        puVar4 = puVar4 - 1;
        iVar5 = func_80134C20((short)(hic | param_1), (s32)puVar7, uVar3, uVar10);
        if (iVar5 != 0) goto found;
    test:
        {
            u32 m;
            __asm__("addu %0,%1,$zero" : "=r"(m) : "r"(n));
            n--;
            if ((m & 0xffff) != 0) goto body;
        }
    }
    return 0;
}



// @class: regalloc-order
// @try: variant B — direct pins m=$s5($21), c=$s6($22)


s32 func_80134C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    extern u8 D_801152A8[];
    extern s32 func_80134FB8(s32 a0, s32 a1, s32 a2);
    extern void * D_8018A99C;
    extern void * D_8018A9A0;
    extern void * D_8018A9A4;
    extern void * D_8018A9A8;
    extern u16 D_801F4DD8;

    s32 temp_a3;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;
    u16 temp_a1;
    s32 temp_s4;
    s32 c = arg0;
    __asm__ __volatile__("" : "=r"(c) : "0"(c));
    __asm__ __volatile__("" : : "r"(arg0));

    temp_s4 = arg2 + (M2C_FIELD(((void *)arg1), s16 *, 2) * 8);
    temp_s1 = *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 4) * 4));
    var_v0 = 0;
    if (func_80134FB8(temp_s4, (s32) D_8018A9A0, temp_s1) >= 0) {
        return var_v0;
    }
    temp_v0 = func_80134FB8(temp_s4, (s32) D_8018A99C, temp_s1);
    if (temp_v0 < 0) {
        goto block_13;
    }
    temp_v0_2 = func_80134FB8(temp_s4, (s32) D_8018A9A8, 0);
    temp_a3 = -temp_v0;
    {
        u16 *pB4 = (u16 *)D_8018A9A4;
        u16 *pAC = (u16 *)D_8018A99C;
        s16 *pB8 = (s16 *)D_8018A9A8;
        pB4[0] = pAC[0] + (temp_a3 * pB8[0]) / temp_v0_2;
        pB4[1] = pAC[1] + (temp_a3 * pB8[1]) / temp_v0_2;
        pB4[2] = pAC[2] + (temp_a3 * pB8[2]) / temp_v0_2;
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 6) * 8), (s32) pB4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 8) * 4))) < -0x2F00) {
            return var_v0;
        }
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xA) * 8), (s32) D_8018A9A4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0xC) * 4))) < -0x2F00) {
        return var_v0;
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xE) * 8), (s32) D_8018A9A4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x10) * 4))) < -0x2F00) {
        return var_v0;
    }
    if ((arg0 << 16) < 0) {
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0x12) * 8), (s32) D_8018A9A4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x14) * 4))) < -0x2F00) {
            return var_v0;
        }
    }
    if (c & 1) {
        if (!(M2C_FIELD(((void *)arg1), u16 *, 0) & 0x300)) {
            goto block_14;
        }
        return 0;
    }
    temp_a1 = M2C_FIELD(((void *)arg1), u16 *, 0);
    if (!(temp_a1 & 0x200)) {
        goto block_14;
    }
    D_801F4DD8 = temp_a1;
block_13:
    return 0;
block_14:
    __builtin_memcpy(D_801152A8, (void *)temp_s4, 8);
    VectorNormalSS(D_8018A9A8, D_8018A9A8);
    {
        u16 *pB8 = (u16 *)D_8018A9A8;
        u16 *pB4b = (u16 *)D_8018A9A4;
        pB4b[0] = pB4b[0] - ((pB8[0] << 0x10) >> 0x1B);
        var_v0 = 1;
        pB4b[1] = pB4b[1] - ((pB8[1] << 0x10) >> 0x1B);
        pB4b[2] = pB4b[2] - ((pB8[2] << 0x10) >> 0x1B);
    }
    return var_v0;
}


DEFINE_func_80134FB8()  /* dedup: shared engine-core @0x80134fb8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80135004);



// @class: schedule
// @stuck: none — MATCH (62 ins, relocation-masked)



extern int func_80134A74(int, s16, s16, int);

int func_80135168(u16 arg0, u16 *p1, u16 *p2)
{

    extern u8 D_8018A9A0;
    extern u8 D_8018A99C;
    extern s16 *D_8018A9A4;
    extern u8 D_8018A9A8;
    extern int D_801F4DC8;
    extern u16 D_801F4DD8;
    register s16 *pb0 __asm__("$8");
    register s16 *pac __asm__("$6");
    register s16 *pb8 __asm__("$7");
    u16 *pb4;
    u16 a, b;
    int a1v, a2v, d94;

    pb0 = (*(s16 * *)&D_8018A9A0);
    __asm__ __volatile__("" : : "r"(pb0));

    a = p2[0]; pac = (*(s16 * *)&D_8018A99C); pb0[0] = a; b = p1[0]; pb8 = (*(s16 * *)&D_8018A9A8); pac[0] = b; pb8[0] = a - b;
    a = p2[1]; pb0[1] = a; b = p1[1]; pac[1] = b; pb8[1] = a - b;
    a = p2[2]; pb0[2] = a; b = p1[2]; pac[2] = b; pb8[2] = a - b;

    a1v = pac[0]; a2v = pac[2]; d94 = D_801F4DC8;
    __asm__ __volatile__("" ::: "memory");
    D_801F4DD8 = 0;
    if (func_80134A74(arg0, a1v, a2v, d94)) {
        pb4 = (*(u16 * *)&D_8018A9A4);
        p2[0] = pb4[0];
        p2[1] = pb4[1];
        p2[2] = pb4[2];
        p2[3] = D_801F4DD8;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80135260);

extern int func_80135168(u16 arg0, u16 *p1, u16 *p2);

/* func_80135480 — cull + coordinate-transform emitter (258 ins, ov_SC01_077 split _a, ×134 family).
 *
 * NOT a §43 s16-param giant. Params are (void*, s32, s16*, s16*); the sole `sll/sra 16` is the s16
 * RETURN narrowing on $s3 (result), not an in-place arg-reg narrow. So §43's K&R-s16-param map does
 * not apply here — no //@EDIT, no ec_edit. func_80135480 has NO ambient prototype/caller anywhere in
 * src/include, so the s16 return type is free (no void->s32 flip, no engine_core.h edit).
 *
 * THE CRACK (residual class = §31 regalloc/schedule, RC-4/RC-2 in gcc-2.7.2-map/regalloc.md):
 * the two output buffers D_8018A99C / D_8018A9A0 are written through a pointer in each of the two
 * return tails (mode!=0 and mode==0). A single function-scope `s16 *tmp` reused across both tails is a
 * GLOBAL allocno (used in 2 blocks, dies 4x) -> forced onto one hard reg ($a1), which is WRONG and also
 * perturbs the switch's first-`beq` delay-slot fill (extra nop). The target instead allocates each
 * store-group's pointer as a LOCAL-ALLOC pseudo (set once, used 3x, dies once, single block) that picks
 * the lowest-free scratch over its OWN window:
 *     mode!=0 tail:  p_AC -> $v1,  p_B0 -> $v1 (reused, $v0 = the load temp)
 *     mode==0 tail:  p_AC -> $v1,  p_B0 -> $a0 (the sub-scratch occupies $v1, so $v1 is unavailable)
 * Reproduced by giving each of the four store-groups its OWN block-scoped pointer. With the tail
 * allocation correct, the whole schedule (incl. the beq delay slot) re-derives to byte-identical.
 * No register pins (§17 caveat: don't pin $v1 — the target reuses it for the cull; a pin cascades
 * per RC-5). NOTE: the block-scope `s16 *p` intentionally shadows the function-scope `s32 p` (the
 * case-0x20000000 pointer base); scopes never overlap — legal and byte-verified.
 *
 * Zero file-scope footprint (block-scoped typedefs + externs; D_8018A99C/B0 read via the ambient
 * `extern u8` + `*(s16**)&` §30 anon-cast, matching neighbor func_80135168) -> ×134-clean for
 * family_sweep --edit-remap with no cc1 crash.
 *
 * VERIFIED: tools/rtu_match.py func_80135480 --split ov_SC01_077_a  ->  MATCH (258 ins), 3x stable.
 */
s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4)
{

    extern Box_80133784 * D_8018A99C;
    extern Box_80133784 * D_8018A9A0;
    typedef struct { s32 vx, vy, vz, pad; } Vec32;
    typedef struct { s16 vx, vy, vz, pad; } Vec16;
    typedef struct { s32 w0, w4, w8, wC; s16 h10, hpad; s32 t0, t1, t2; } Mat32;
    extern void func_80048EAC(void *m0, void *m1);
    extern void func_8004914C(void *m);
    extern void ApplyTransposeMatrixLV(void *m, void *in, void *out);
    extern void ApplyRotMatrixLV(void *in, void *out);
    extern void ApplyRotMatrix(void *in, void *out);
    extern s32 D_801F4DDC, D_801F4DE0, D_801F4DE4, D_801F4DE8;
    extern s16 D_801F4DEC;
    extern s32 D_801F4DFC;
    extern s16 D_801F4E00, D_801F4E02, D_801F4E04, D_801F4E06, D_801F4E08, D_801F4E0A;

    Vec32 in0, in1, rotout;
    Mat32 mat2;
    Vec16 vecin;
    s32 result;
    s32 mode;
    s32 q1, q2;
    s32 p;
    s32 t18, t1A, t1C;
    s32 *m;

    in0.vx = param_3[0] - *(s32 *)((s32)param_1 + 0x48);
    in0.vz = param_3[2] - *(s32 *)((s32)param_1 + 0x50);
    if ((param_2 & 0x10000000) == 0) {
        if (in0.vx * in0.vx + in0.vz * in0.vz > 0x40000) {
            return 0;
        }
    }
    mode = param_2 & 0x60000000;
    if (mode != 0) {
        result = 1;
        if (param_2 >= 0) {
            mode &= 0x40000000;
        }
        in0.vy = param_3[1] - *(s32 *)((s32)param_1 + 0x4C);
        in1.vx = param_4[0] - *(s32 *)((s32)param_1 + 0x48);
        in1.vy = param_4[1] - *(s32 *)((s32)param_1 + 0x4C);
        in1.vz = param_4[2] - *(s32 *)((s32)param_1 + 0x50);
        switch (mode) {
        case 0x60000000:
            m = &D_801F4DDC;
            *m = 0x1000000 / *(s16 *)((s32)param_1 + 0x18);
            q1 = 0x1000000 / *(s16 *)((s32)param_1 + 0x1A);
            q2 = 0x1000000 / *(s16 *)((s32)param_1 + 0x1C);
            D_801F4DE0 = 0;
            D_801F4DE8 = 0;
            D_801F4DE4 = q1;
            D_801F4DEC = q2;
            func_80048EAC((void *)((s32)param_1 + 0x34), m);
            ApplyTransposeMatrixLV(m, &in0, &in0);
            ApplyRotMatrixLV(&in1, &in1);
            result = 2;
            /* fallthrough */
        case 0x20000000:
            p = (param_2 & 0xFFFFFFF) | 0x80000000;
            t18 = *(s16 *)((s32)param_1 + 0x18);
            t1A = *(s16 *)((s32)param_1 + 0x1A);
            t1C = *(u16 *)((s32)param_1 + 0x1C);
            mat2.w4 = 0;
            mat2.wC = 0;
            mat2.w0 = t18;
            mat2.w8 = t1A;
            mat2.h10 = t1C;
            func_8004914C(&mat2);
            vecin.vx = *(u16 *)(p + 4);
            vecin.vy = *(u16 *)(p + 8);
            vecin.vz = *(u16 *)(p + 0xC);
            ApplyRotMatrix(&vecin, &rotout);
            D_801F4E00 = rotout.vx;
            D_801F4E04 = rotout.vy;
            D_801F4E08 = rotout.vz;
            vecin.vx = *(u16 *)(p + 6);
            vecin.vy = *(u16 *)(p + 0xA);
            vecin.vz = *(u16 *)(p + 0xE);
            ApplyRotMatrix(&vecin, &rotout);
            D_801F4DFC = 0;
            D_801F4E02 = rotout.vx;
            D_801F4E06 = rotout.vy;
            D_801F4E0A = rotout.vz;
            result += 2;
            break;
        case 0x40000000:
            ApplyTransposeMatrixLV((void *)((s32)param_1 + 0x34), &in0, &in0);
            ApplyRotMatrixLV(&in1, &in1);
            result = 2;
            break;
        }
        {
            s16 *p = *(s16 **)&D_8018A99C;
            p[0] = in0.vx;
            p[1] = in0.vy;
            p[2] = in0.vz;
        }
        {
            s16 *p = *(s16 **)&D_8018A9A0;
            p[0] = in1.vx;
            p[1] = in1.vy;
            p[2] = in1.vz;
        }
        return result;
    }
    {
        s16 *p = *(s16 **)&D_8018A99C;
        p[0] = in0.vx;
        p[1] = ((u16 *)param_3)[1] - *(s32 *)((s32)param_1 + 0x4C);
        p[2] = in0.vz;
    }
    {
        s16 *p = *(s16 **)&D_8018A9A0;
        p[0] = ((u16 *)param_4)[0] - *(s32 *)((s32)param_1 + 0x48);
        p[1] = ((u16 *)param_4)[1] - *(s32 *)((s32)param_1 + 0x4C);
        p[2] = ((u16 *)param_4)[2] - *(s32 *)((s32)param_1 + 0x50);
    }
    return 1;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80135888);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80135A4C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80135D20);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80135EB0);


s32 func_80136334(void *arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern Box_80133784 * D_8018A99C;
    extern Box_80133784 * D_8018A9A0;
    extern s16 *D_8018A9A4;
    extern u8 D_8018A9A8;
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;
    register s32 a1v __asm__("$11");
    register s32 a2v __asm__("$12");
    register s32 n __asm__("$5");
    register s16 *b4 __asm__("$7");
    s32 d;
    s32 dx;
    s32 denom;
    s32 result;
    s32 frame_pad[2];
    (void)&frame_pad;
    __asm__("" : "=r"(a1v) : "0"(arg1));
    a2v = arg2;

    if (!(arg1 & 1)) {
        dx = (s16) arg2 - (*(s16 **)&D_8018A99C)[2];
        d = dx;
        denom = -(*(s16 **)&D_8018A9A8)[2];
    } else {
        denom = (*(s16 **)&D_8018A9A8)[2];
        d = (*(s16 **)&D_8018A99C)[2] - (s16) arg2;
        dx = -d;
    }
    n = -d;
    {
        register s16 *b8 __asm__("$6") = *(s16 **)&D_8018A9A8;
        u16 *ac = *(u16 **)&D_8018A99C;
        b4 = D_8018A9A4;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_8018A9A0;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_8018A9A4[2] = a2v + 2;
        __asm__ __volatile__("");
        D_801152AC = 0xFFF;
    } else {
        D_801152AC = -0xFFF;
        D_8018A9A4[2] = a2v - 2;
    }
    __asm__ __volatile__("" :: "r"(a1v), "r"(a2v));
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}



// @class: regalloc-order — F-band exemplar func_801365B8 (x134). Real-TU reconciled (rtu_match).
// D_8018A99C/B0/B8 file-scope `extern u8` holding pointers -> read via *(T**)&sym (§42c-2).
// D_8018A9A4 file-scope `extern s16*` -> use directly. D_80126720 file-scope `extern u8[]`
// -> single store via *(s16*)D_80126720. D_801152A8/AA/AC, D_80126722/24 block-scope externs
// (siblings use block-scope; gcc-2.7.2 does not cross-conflict block-scope externs).
s32 func_801365B8(void *arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern Box_80133784 * D_8018A99C;
    extern Box_80133784 * D_8018A9A0;
    extern s16 *D_8018A9A4;
    extern u8 D_8018A9A8;
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;
    u16 *ac;
    s16 *b8;
    s16 *b4;
    s16 temp_v0;
    s16 temp_v1;
    s32 var_a3;
    s32 temp_a1;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;
    s32 a1c;
    s32 a2c;
    s32 cond;
    register u32 zr __asm__("$0");

    __asm__("addu %0,%1,$zero" : "=r"(a1c) : "r"(arg1));
    cond = arg1 & 1;
    a2c = arg2 + zr;
    if (!cond) {
        var_v1 = (s16) arg2 - (*(s16 **)&D_8018A99C)[0];
        var_a1 = var_v1;
        var_a3 = -(*(s16 **)&D_8018A9A8)[0];
    } else {
        var_a3 = (*(s16 **)&D_8018A9A8)[0];
        var_v1 = (*(s16 **)&D_8018A99C)[0] - (s16) arg2;
        var_a1 = -var_v1;
    }
    ac = *(u16 **)&D_8018A99C;
    b4 = D_8018A9A4;
    b8 = *(s16 **)&D_8018A9A8;
    b4[0] = ac[0] + var_a1;
    temp_a1 = -var_v1;
    b4[1] = ac[1] + (temp_a1 * b8[1]) / var_a3;
    temp_v0 = ac[2] + (temp_a1 * b8[2]) / var_a3;
    b4[2] = temp_v0;
    var_v0 = 0;
    if (temp_v0 < M2C_FIELD(arg0, s16 *, 0xC)) {
        return var_v0;
    }
    if (M2C_FIELD(arg0, s16 *, 0xE) < temp_v0) {
        return var_v0;
    }
    temp_v1 = b4[1];
    if (temp_v1 < M2C_FIELD(arg0, s16 *, 8)) {
        return var_v0;
    }
    if (M2C_FIELD(arg0, s16 *, 0xA) < temp_v1) {
        return var_v0;
    }
    __asm__("" :: "r"(a1c));
    __asm__("" :: "r"(a1c));
    if (a1c & 0x8000) {
        b4[1] = (s16) (*(u16 **)&D_8018A9A0)[1];
        b4[2] = (s16) (*(u16 **)&D_8018A9A0)[2];
    }
    D_801152AC = 0;
    D_801152AA = 0;
    if ((a1c & 1) != 0) {
        *(s16 *)D_801152A8 = 0xFFF;
        M2C_FIELD(D_8018A9A4, s16 *, 0) = a2c + 2;
    } else {
        *(s16 *)D_801152A8 = -0xFFF;
        M2C_FIELD(D_8018A9A4, s16 *, 0) = a2c - 2;
    }
    *(s16 *)D_80126720 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1);
    var_v0 = 1;
    D_80126724 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1);
    return var_v0;
}



// @class: pointer-type — pointer-vs-array reconcile for func_80136824 (ov_SC01_077_a)
// D_8018A99C/B0/B8 are file-scope `extern u8`, D_8018A9A4 is `extern s32 []`; each HOLDS a
// pointer value that the target loads via lw then derefs. Read as pointer via *(T**)&sym.
// D_8018A9A4 must be a SCALAR pointer (not s32[]) — as an array it decays and gcc CSEs the
// base address into a held reg (lui;addiu;lw 0(reg)) across the 3 reloads; as a scalar
// pointer it folds %lo (lui;lw %lo). Retype all 3 file-TU occurrences (byte-neutral: the
// siblings read it once via *(u16**)&sym == direct lw either way).

s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern Box_80133784 * D_8018A99C;
    extern Box_80133784 * D_8018A9A0;
    extern s16 *D_8018A9A4;
    extern u8 D_8018A9A8;
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;

    register u16 *ac __asm__("$4");
    register s16 *b8 __asm__("$6");
    register s16 *b4 __asm__("$9");
    register s32 r __asm__("$3");
    register s32 pos __asm__("$12");
    register s32 a1v __asm__("$5");
    s16 temp_v0;
    s16 temp_v1;
    s32 var_a3;
    s16 var_v0_3;
    s32 temp_a1;
    s32 var_t0;
    s32 var_v1;
    s16 *b4b;
    u16 *p;

    __asm__ ("" : "=r"(a1v) : "0"(arg1));
    pos = arg2;
    if (!(a1v & 1)) {
        var_t0 = (s16) arg2 - (*(s16 **)&D_8018A99C)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_8018A9A8)[1];
    } else {
        var_a3 = (*(s16 **)&D_8018A9A8)[1];
        var_v1 = (*(s16 **)&D_8018A99C)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    b8 = (*(s16 **)&D_8018A9A8);
    ac = (*(u16 **)&D_8018A99C);
    b4 = D_8018A9A4;
    temp_a1 = -var_v1;
    r = (temp_a1 * b8[0]) / var_a3;
    b4[0] = ac[0] + r;
    b4[1] = ac[1] + var_t0;
    r = (temp_a1 * b8[2]) / var_a3;
    temp_v0 = ac[2] + r;
    b4[2] = temp_v0;
    temp_v1 = b4[0];
    if (temp_v1 < M2C_FIELD(((void *)arg0), s16 *, 4)) {
        return 0;
    }
    if (M2C_FIELD(((void *)arg0), s16 *, 6) < temp_v1) {
        return 0;
    }
    if (temp_v0 < M2C_FIELD(((void *)arg0), s16 *, 0xC)) {
        return 0;
    }
    if (M2C_FIELD(((void *)arg0), s16 *, 0xE) < temp_v0) {
        return 0;
    }
    if (arg1 & 0x8000) {
        p = (*(u16 **)&D_8018A9A0);
        b4[0] = (s16) p[0];
        b4[2] = (s16) p[2];
    }
    D_801152AC = 0;
    (*(s16 *)D_801152A8) = 0;
    if (arg1 & 1) {
        b4b = D_8018A9A4;
        D_801152AA = 0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos + 2;
    } else {
        b4b = D_8018A9A4;
        D_801152AA = -0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos - 2;
    }
    b4b[1] = var_v0_3;
    __asm__ __volatile__("" :: "r"(pos));
    (*(s16 *)D_80126720) = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 4) + M2C_FIELD(((void *)arg0), s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 8) + M2C_FIELD(((void *)arg0), s16 *, 0xA)) >> 1);
    D_80126724 = (s16) ((s32) (M2C_FIELD(((void *)arg0), s16 *, 0xC) + M2C_FIELD(((void *)arg0), s16 *, 0xE)) >> 1);
    return 1;
}



// @class: schedule
// @stuck: none — MATCH (76 ins, relocation-masked). Key lever: the D_80126720/22/24 tail is a
//   global-short RMW `+=`. Writing it via a cast `*(u16*)&SYM = *(u16*)&SYM + x` makes gcc CSE
//   the address into a base reg (base-reuse) for ALL three — but the target only base-reuses
//   D_80126720 (a SCHEDULER artifact: its addr-lui fills the load-delay slot after the pb4[4]
//   load, and since $v0 is live it lands in $a0, reused for load+store). D_80126722/24 use the
//   plain inline 2-lui form. Fix = DIRECT scalar RMW `SYM = SYM + x` (no &/cast) → inline %hi/%lo;
//   the scheduler alone forces base-reuse on #1. Also: `s16 D_80126724 = D_80126724 + int` emits
//   LHU (gcc-2.7.2 drops the sign-extend because the sum is truncated to 16b on the sh) — so the
//   canonical s16 decl is byte-safe here (no u16 retype needed, keeps the sign-sensitive callers).



s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern u8 D_801152A8[];
    extern u8 D_80126720[];
    extern s16 *D_8018A9A4;   /* holds a pointer value (*(u16**)&D_8018A9A4) */
    extern void ApplyMatrixSV(void *m, void *v0, void *v1);
    extern void ApplyRotMatrix(void *v0, void *v1);
    extern u16 D_80126722;
    extern s16 D_80126724;
    extern s16 D_801152AA;
    extern s16 D_801152AC;

    s32 out[4];
    u16 *pb4;

    if (a0) {
        ApplyMatrixSV((void *)a3, *(void **)&D_8018A9A4, *(void **)&D_8018A9A4);
        ApplyMatrixSV((void *)a3, (void *)D_80126720, (void *)D_80126720);
        ApplyRotMatrix((void *)D_801152A8, (void *)out);
        *(s16 *)D_801152A8 = out[0];
        D_801152AA = out[1];
        D_801152AC = out[2];
    }

    pb4 = *(u16 **)&D_8018A9A4;
    *(s16 *)(a2)     = pb4[0] + *(s32 *)(a1 + 0x48);
    *(s16 *)(a2 + 2) = pb4[1] + *(s32 *)(a1 + 0x4C);
    *(s16 *)(a2 + 4) = pb4[2] + *(s32 *)(a1 + 0x50);

    *(u16 *)D_80126720 = *(u16 *)D_80126720 + *(s32 *)(a1 + 0x48);
    D_80126722 = D_80126722 + *(s32 *)(a1 + 0x4C);
    D_80126724 = D_80126724 + *(s32 *)(a1 + 0x50);
}


DEFINE_func_80136BC4()  /* dedup: shared engine-core @0x80136bc4 (src/shared) */


DEFINE_func_80136C1C()  /* dedup: shared engine-core @0x80136c1c (src/shared) */


void func_80136C3C(void) {
}

void func_80136C44(void) {
}

void func_80136C4C(void) {
}



void func_80136C54(void)
{

    extern unsigned short D_800B99F0;
    extern void (*D_8018A9B8[])(void);
    D_8018A9B8[D_800B99F0]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80136C90);

void func_80136D00(void) {
}

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136d08 (src/shared) */


DEFINE_func_80136DFC()  /* dedup: shared engine-core @0x80136dfc (src/shared) */


void func_80136EC4(void) {
}

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ecc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80136F3C);

DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80137178);

DEFINE_func_801372B0()  /* dedup: shared engine-core @0x801372b0 (src/shared) */


DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375ec (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80137614);

DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767c (src/shared) */


DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376c8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801376E8);

DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377b4 (src/shared) */


DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801378F0);

DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379d8 (src/shared) */


DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379ec (src/shared) */



// @class: regalloc-order (walker-family, §52/§52a) — PIN-FREE
// Role-swap ($s0<->$s2 between loop1 and loops2/3) is driven by DENSITY (K2), not pins:
//  - loop1 pointer has an extra ref (p != D_80127524 compare) -> wins $s0; index -> $s2
//  - loop2/3 index has >= pointer refs -> wins $s0; pointer -> $s2
// Separate per-loop pointer/index vars => separate pseudos => can take different regs.


extern void func_80138BE0(s32 a0);
extern void func_80137BD8(s32 a0);
extern void func_8013A380(void);

void func_801379FC(void) {

    extern s32 D_80127524;
    extern s32 D_80127548[];
    extern s32 D_801269F0;
    extern s16 D_801269F4;
    extern s32 D_801269F8;
    s32 i;

    (*(s32 *)D_80127548) = 0x24;
    if ((D_80127524 != 0) && (*(s32 *)D_80127524 != 0)) {
        s32 p;
        s32 idx;
        func_80138BE0(D_80127524);
        i = 0;
        p = (s32)&D_801269F0;
        idx = 0;
        do {
            if ((p != D_80127524) && (*(s32 *)((s32)&D_801269F0 + idx) != 0)) {
                func_80138BE0(p);
            }
            p = p + 0x4c;
            i = i + 1;
            idx = idx + 0x4c;
        } while (i < 3);
    } else {
        s32 p;
        s32 idx;
        i = 0;
        p = (s32)&D_801269F0;
        idx = 0;
        do {
            if (*(s32 *)((s32)&D_801269F0 + idx) != 0) {
                func_80138BE0(p);
            }
            p = p + 0x4c;
            i = i + 1;
            idx = idx + 0x4c;
        } while (i < 3);
    }

    {
        s32 p;
        s32 idx;
        s32 flags;
        i = 0;
        p = (s32)&D_801269F0;
        idx = 0;
        do {
            if (*(s16 *)((s32)&D_801269F4 + idx) != 0) {
                if (*(s32 *)((s32)&D_801269F0 + idx) != 0) {
                    flags = *(s32 *)((s32)&D_801269F8 + idx);
                    if ((flags & 0x1000) != 0) {
                        if ((flags & 0x2000) == 0) {
                            func_80137BD8(p);
                        }
                    }
                }
            }
            p = p + 0x4c;
            i = i + 1;
            idx = idx + 0x4c;
        } while (i < 3);
    }

    func_8013A380();
}




// @class: remat
// @stuck: target CSEs &D_801269F0 once for load+call arg; force via local pointer
extern void func_80138BE0(int p);

void func_80137B80(void) {

    extern s32 D_80127548[];
    extern int D_8018AA0C;
    extern int D_801269F0;
    int *p = &D_801269F0;
    (*(int *)&D_80127548) = 0x24;
    if (*p != 0) {
        ((void (*)(int *))func_80138BE0)(p);
    }
    D_8018AA0C += 1;
}


DEFINE_func_80137BD8()  /* dedup: shared engine-core @0x80137bd8 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (51 ins). Three globals stored/loaded around 3 calls; &D_801269F0 held in $s1, arg1 in $s0 across calls; return reloads global D_800A5E60.


extern void func_801392FC();
extern void func_80137DD4(s32 a0, u8 *a1, u8 *a2);
extern void func_80139680(s32 a0, u8 *a1);

int func_80137D08(int arg0, int arg1, short arg2)
{

    extern unsigned char D_80126A0E;
    extern short D_80126A0A;
    extern s16 D_801269F4;
    extern int D_800A5E60;
    extern int D_8018AA0C;
    extern int D_801269F0;
    unsigned char buf[3];

    D_800A5E60 = arg0;
    D_80126A0A = arg2;
    ((void (*)(void *, int, int))func_801392FC)(&D_801269F0, D_80126A0E, arg1);
    if ((*(short *)&D_801269F4) == 7) {
        buf[0] = 0x39;
        buf[1] = 0xFF;
        buf[2] = 0x71;
        ((void (*)(void *, void *, int))func_80137DD4)(&D_801269F0, buf, arg1);
    } else if ((*(short *)&D_801269F4) == 3) {
        if (D_8018AA0C & 4) {
            ((void (*)(void *, int))func_80139680)(&D_801269F0, arg1);
        }
    }
    return D_800A5E60;
}


DEFINE_func_80137DD4()  /* dedup: shared engine-core @0x80137DD4 (src/shared) */

DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137fd8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801380E0);

DEFINE_func_801387B8()  /* dedup: shared engine-core @0x801387B8 (src/shared) */

DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */


DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895c (src/shared) */


DEFINE_func_80138AB4()  /* dedup: shared engine-core @0x80138ab4 (src/shared) */


DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138b88 (src/shared) */



// @class: struct
// @stuck: none — MATCH (match_one: MATCH 20 ins)


void func_80138BE0(int p)
{

    extern void (*D_8018AA10[])(void);
    if (*(unsigned short *)(p + 0xe) != 0) {
        *(unsigned short *)(p + 0xe) -= 1;
    }
    D_8018AA10[*(short *)(p + 4)]();
}


void func_80138C30(void *a0) {
    if (*(s16 *)((s32)a0 + 4) == 4) {
        *(s16 *)((s32)a0 + 4) = 2;
    } else {
        *(u32 *)((s32)a0 + 8) |= 0x800;
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80138C60);

DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138d58 (src/shared) */


DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138db8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80138DE0);

DEFINE_func_80138ED0()  /* dedup: shared engine-core @0x80138ed0 (src/shared) */


DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914c (src/shared) */


DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391f0 (src/shared) */


DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */


DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392c8 (src/shared) */


DEFINE_func_801392FC()  /* dedup: shared engine-core @0x801392fc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801395D4);

DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */


DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */


DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */



extern void GsSortSprite(void *a0, u8 *a1, s32 a2);

void func_801397B0(s32 arg0)
{

    extern short D_800B9A02;
    extern u8 D_800A6518[];
    extern u8 D_8018AA54;
    extern u8 D_8018AA98;
    register u8 *e __asm__("$7");
    register s32 off __asm__("$4");
    s32 buf[12];
    u8 *b164;
    u8 *b1A8;
    s32 sc;
    s32 t2;
    s32 t0;
    s32 hi;
    s32 lo;
    s32 uu;
    s32 vv;

    e = (u8 *)arg0;
    b164 = (u8 *)&D_8018AA54;
    off = ((s32)*(u8 *)(e + 0x20) - 1) << 2;
    b164 = off + b164;

    *(s32 *)((u8 *)buf + 0x00) = 0;

    t2 = *(s16 *)(b164 + 2);
    t0 = *(s16 *)(b164 + 0);
    hi = (t2 & 0x100) >> 4;
    lo = ((t0 & 0x3C0) >> 6) | 0x20;
    *(s16 *)((u8 *)buf + 0x0C) = hi | lo | ((t2 & 0x200) << 2);

    b1A8 = (u8 *)&D_8018AA98 + off;
    *(s16 *)((u8 *)buf + 0x10) = *(u16 *)(b1A8 + 0);
    *(s16 *)((u8 *)buf + 0x12) = *(u16 *)(b1A8 + 2);
    *(u8 *)((u8 *)buf + 0x16) = 0x80;
    *(u8 *)((u8 *)buf + 0x15) = 0x80;
    *(u8 *)((u8 *)buf + 0x14) = 0x80;
    *(s16 *)((u8 *)buf + 0x06) = *(u16 *)(e + 0x32);
    *(s16 *)((u8 *)buf + 0x08) = 0x20;
    *(s16 *)((u8 *)buf + 0x0A) = 0x28;

    uu = (*(u16 *)(b164 + 0) & 0x3F) << 2;
    *(u8 *)((u8 *)buf + 0x0E) = uu;
    vv = *(u16 *)(b164 + 2);
    *(u8 *)((u8 *)buf + 0x0F) = vv;

    if (*(u8 *)(e + 0x22) & 8) {
        *(s16 *)((u8 *)buf + 0x04) =
            *(u16 *)(e + 0x30) + *(u16 *)(e + 0x34) + 0x28;
        sc = -*(u16 *)(e + 0x28);
    } else {
        *(s16 *)((u8 *)buf + 0x04) = *(u16 *)(e + 0x30) - 0x28;
        sc = *(u16 *)(e + 0x28);
    }
    *(s16 *)((u8 *)buf + 0x1C) = sc;
    *(s16 *)((u8 *)buf + 0x1E) = *(u16 *)(e + 0x2A);
    *(s16 *)((u8 *)buf + 0x1A) = 0;
    *(s16 *)((u8 *)buf + 0x18) = 0;
    *(s32 *)((u8 *)buf + 0x20) = 0;

    GsSortSprite(buf, &D_800A6518[(u16)D_800B9A02 * 20],
                 *(u16 *)(e + 0x1A));
}


DEFINE_func_80139914()  /* dedup: shared engine-core @0x80139914 (src/shared) */


DEFINE_func_80139954()  /* dedup: shared engine-core @0x80139954 (src/shared) */


DEFINE_func_801399A8()  /* dedup: shared engine-core @0x801399a8 (src/shared) */


DEFINE_func_801399F0()  /* dedup: shared engine-core @0x801399f0 (src/shared) */


DEFINE_func_80139A34()  /* dedup: shared engine-core @0x80139a34 (src/shared) */


DEFINE_func_80139A44()  /* dedup: shared engine-core @0x80139a44 (src/shared) */


DEFINE_func_80139A68()  /* dedup: shared engine-core @0x80139a68 (src/shared) */


DEFINE_func_80139A8C()  /* dedup: shared engine-core @0x80139a8c (src/shared) */


DEFINE_func_80139B18()  /* dedup: shared engine-core @0x80139b18 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80139BE0);

DEFINE_func_80139C7C()  /* dedup: shared engine-core @0x80139c7c (src/shared) */


DEFINE_func_80139D04()  /* dedup: shared engine-core @0x80139d04 (src/shared) */


DEFINE_func_80139DC8()  /* dedup: shared engine-core @0x80139dc8 (src/shared) */


void func_80139DEC(void) {
}

DEFINE_func_80139DF4()  /* dedup: shared engine-core @0x80139df4 (src/shared) */


DEFINE_func_80139E84()  /* dedup: shared engine-core @0x80139e84 (src/shared) */


DEFINE_func_80139F0C()  /* dedup: shared engine-core @0x80139f0c (src/shared) */


DEFINE_func_80139FBC()  /* dedup: shared engine-core @0x80139fbc (src/shared) */


DEFINE_func_80139FE8()  /* dedup: shared engine-core @0x80139fe8 (src/shared) */


DEFINE_func_8013A0A4()  /* dedup: shared engine-core @0x8013a0a4 (src/shared) */


DEFINE_func_8013A164()  /* dedup: shared engine-core @0x8013a164 (src/shared) */


DEFINE_func_8013A1E8()  /* dedup: shared engine-core @0x8013a1e8 (src/shared) */


DEFINE_func_8013A250()  /* dedup: shared engine-core @0x8013a250 (src/shared) */


DEFINE_func_8013A2BC()  /* dedup: shared engine-core @0x8013a2bc (src/shared) */


void func_8013A378(void) {
}

DEFINE_func_8013A380()  /* dedup: shared engine-core @0x8013a380 (src/shared) */


DEFINE_func_8013A448()  /* dedup: shared engine-core @0x8013a448 (src/shared) */


DEFINE_func_8013A4C4()  /* dedup: shared engine-core @0x8013a4c4 (src/shared) */


DEFINE_func_8013A530()  /* dedup: shared engine-core @0x8013a530 (src/shared) */


DEFINE_func_8013A860()  /* dedup: shared engine-core @0x8013a860 (src/shared) */


DEFINE_func_8013A8B0()  /* dedup: shared engine-core @0x8013a8b0 (src/shared) */


DEFINE_func_8013A8BC()  /* dedup: shared engine-core @0x8013a8bc (src/shared) */


DEFINE_func_8013A8FC()  /* dedup: shared engine-core @0x8013a8fc (src/shared) */


DEFINE_func_8013A9B4()  /* dedup: shared engine-core @0x8013a9b4 (src/shared) */


DEFINE_func_8013A9F8()  /* dedup: shared engine-core @0x8013a9f8 (src/shared) */


DEFINE_func_8013AA24()  /* dedup: shared engine-core @0x8013aa24 (src/shared) */


extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3);
extern void func_8013B274(s32 a0, s32 a1, void *a2);
extern void func_8013AF20();
s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_800A5E60;
    u8 buf[0xE4];          /* spans 0x10 .. 0xF4 */
    s32 neg;
    s32 a, b;
    s32 t4, t6;
    t4 = *(s16 *)(a2 + 4) * 12;
    *(s16 *)(buf + 0xE0) = t4 + 0x10;   /* sp+0xF0 */
    neg = a3 & 0x8000;
    t6 = *(s16 *)(a2 + 6) * 12 + (*(s16 *)(a2 + 6) - 1) * 2;
    *(s16 *)(buf + 0xE2) = t6 + 8;
    if (neg == 0) {
        *(s16 *)(buf + 0xE0) = t4 + 0x38;
        *(s16 *)(buf + 0xE2) = t6 + 0x10;
    }
    a = ((s32)*(s16 *)(buf + 0xE0) << 12) / 154;
    b = ((s32)*(s16 *)(buf + 0xE2) << 12) / 42;
    *(s16 *)(buf + 0xE0) = a;
    *(s16 *)(buf + 0xE2) = b;
    if (neg != 0) {
        *(s16 *)(buf + 0xE0) = -a;
    }
    *(s16 *)(buf + 0xC8) = b;          /* 0xD8 */
    *(s16 *)(buf + 0xC2) = 0;          /* 0xD2 */
    *(s16 *)(buf + 0xC4) = 0;          /* 0xD4 */
    *(s16 *)(buf + 0xC6) = 0;          /* 0xD6 */
    *(s16 *)(buf + 0xCA) = 0;          /* 0xDA */
    *(s16 *)(buf + 0xCC) = 0;          /* 0xDC */
    *(s16 *)(buf + 0xCE) = 0;          /* 0xDE */
    *(s16 *)(buf + 0xD0) = 0x1000;     /* 0xE0 */
    *(s16 *)(buf + 0xC0) = *(u16 *)(buf + 0xE0);   /* 0xD0 */
    *(s32 *)(buf + 0xD4) = *(s16 *)(a2 + 0);       /* 0xE4 */
    *(s32 *)(buf + 0xD8) = *(s16 *)(a2 + 2);       /* 0xE8 */
    *(s32 *)(buf + 0xDC) = 0;                       /* 0xEC */
    __asm__ __volatile__("" ::: "memory");
    {
        register s32 *p __asm__("$2") = (s32 *)(buf + 0xC0);
        __asm__ __volatile__(
            "lw $12, 0(%0)\n"
            "lw $13, 4(%0)\n"
            "ctc2 $12, $0\n"
            "ctc2 $13, $1\n"
            "lw $12, 8(%0)\n"
            "lw $13, 12(%0)\n"
            "lw $14, 16(%0)\n"
            "ctc2 $12, $2\n"
            "ctc2 $13, $3\n"
            "ctc2 $14, $4\n"
            "lw $12, 20(%0)\n"
            "lw $13, 24(%0)\n"
            "ctc2 $12, $5\n"
            "lw $14, 28(%0)\n"
            "ctc2 $13, $6\n"
            "ctc2 $14, $7\n"
            : : "r"(p) : "$12", "$13", "$14", "memory");
    }
    func_8013AD38(buf + 0xE0, 0, buf + 0x00, buf + 0x80);
    D_800A5E60 = a0;
    if (a3 != 0) {
        func_8013B274(a1, 0x80, buf + 0xE0);
    }
    func_8013AF20(a1, a2, buf + 0x00, buf + 0x80);
    return D_800A5E60;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013AD38);

DEFINE_func_8013AF20()  /* dedup: shared engine-core @0x8013af20 (src/shared) */


DEFINE_func_8013B204()  /* dedup: shared engine-core @0x8013b204 (src/shared) */




extern void *func_80010A08(s32);

void func_8013B274(s32 a0, s32 a1, void *a2)
{

    extern s16 D_8018AB54, D_8018AB56, D_8018AB58, D_8018AB5A, D_8018AB5C, D_8018AB5E;
    extern u16 D_800D45F6;
    u8 *p;
    s32 L[10];
    s16 sa;
    s32 quot;
    s16 ang;

    p = (u8 *)func_80010A08(0x28);
    p[3] = 9;
    p[7] = 0x2C;
    p[4] = 0x80;
    p[5] = 0x80;
    p[6] = 0x80;
    *(s16 *)(p + 0x16) = 0x37;
    *(s16 *)(p + 0xE) = 0x6FD6;
    p[0xC] = 0xE0;
    p[0xD] = 0;
    p[0x14] = 0xEF;
    p[0x15] = 0;
    p[0x1C] = 0xE0;
    p[0x1D] = 0xF;
    p[0x24] = 0xEF;
    p[0x25] = 0xF;

    sa = (s16)a1;
    if (sa == 0) {
        *(s16 *)L = 0;
    } else {
        quot = ((s32)sa << 12) / ((s16*)a2)[0];
        ang = (s16)quot;
        if (!(D_8018AB56 < ang)) goto outer_else;
        if (!(ang < D_8018AB5C)) goto inner_else;
        if (ang < D_8018AB58) { *(s16 *)L = D_8018AB58; goto done; }
        if (D_8018AB5A < ang) { *(s16 *)L = D_8018AB5A; goto done; }
        *(s16 *)L = quot;
        goto done;
    outer_else:
        if (ang < D_8018AB54) { *(s16 *)L = D_8018AB54; goto done; }
        *(s16 *)L = quot;
        goto done;
    inner_else:
        if (D_8018AB5E < ang) { *(s16 *)L = D_8018AB5E; goto done; }
        *(s16 *)L = quot;
    done: ;
    }
    *(s16 *)((u8 *)L + 2) = D_800D45F6;

    __asm__ __volatile__(
        "lwc2 $0, 0(%0)\n"
        "lwc2 $1, 4(%0)\n"
        "nop\n" "nop\n"
        "mvmva 1, 0, 0, 0, 0\n"
        : : "r"(L) : "memory");
    __asm__ __volatile__(
        "swc2 $25, 0(%0)\n"
        "swc2 $26, 4(%0)\n"
        "swc2 $27, 8(%0)\n"
        : : "r"((u8 *)L + 8) : "memory");

    if (((s16*)a2)[1] > 0)
        *(s32 *)((u8 *)L + 0xC) -= 1;
    else
        *(s32 *)((u8 *)L + 0xC) += 2;

    *(s16 *)L = 9;
    *(s16 *)((u8 *)L + 2) = 9;
    __asm__ __volatile__(
        "lwc2 $0, 0(%0)\n"
        "lwc2 $1, 4(%0)\n"
        "nop\n" "nop\n"
        "mvmva 1, 0, 0, 3, 0\n"
        : : "r"(L) : "memory");
    __asm__ __volatile__(
        "swc2 $25, 0(%0)\n"
        "swc2 $26, 4(%0)\n"
        "swc2 $27, 8(%0)\n"
        : : "r"((u8 *)L + 0x18) : "memory");

    *(s16 *)(p + 8) = *(volatile s32 *)((u8 *)L + 8);
    *(s16 *)(p + 0xA) = *(volatile s32 *)((u8 *)L + 0xC);
    *(s16 *)(p + 0x10) = *(volatile s32 *)((u8 *)L + 8) + *(volatile s32 *)((u8 *)L + 0x18);
    *(s16 *)(p + 0x12) = *(volatile s32 *)((u8 *)L + 0xC);
    *(s16 *)(p + 0x18) = *(volatile s32 *)((u8 *)L + 8);
    *(s16 *)(p + 0x1A) = *(volatile s32 *)((u8 *)L + 0xC) + *(volatile s32 *)((u8 *)L + 0x1C);
    *(s16 *)(p + 0x20) = *(volatile s32 *)((u8 *)L + 8) + *(volatile s32 *)((u8 *)L + 0x18);
    *(s16 *)(p + 0x22) = *(volatile s32 *)((u8 *)L + 0xC) + *(volatile s32 *)((u8 *)L + 0x1C);

    ((P_TAG *)p)->addr = ((P_TAG *)a0)->addr;
    ((P_TAG *)a0)->addr = (u32)p;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013B568);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013B598);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013B6A0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013B7AC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013B7F4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013B83C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013BC7C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013BCDC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013BD34);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013BD74);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013C08C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013C0F8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013C360);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013C414);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013C938);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013C964);


extern void func_80016714(void *a0, s32 a1);

void func_8013C98C(void) {

    extern s32 D_801F4E40;
    extern s32 D_801269D4;
    extern s32 D_801269C8;
    func_80016714(&D_801F4E40, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013C9C4);


void func_8013CA14(void)
{

    extern s32 D_801F4E40;
    extern s8 D_801F4E44;
    extern s8 D_801F4E45;
    extern s32 D_801269C8;
    extern s32 D_801269D4;
  int *base = &D_801F4E40;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_801F4E45;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_801F4E44)) * 2) + D_801F4E40);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_801F4E45 = (unsigned char) p[1];
      D_801F4E44 = D_801F4E44 + 1;
      if (D_801F4E45 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_801F4E44 = 0;
        *base = 0;
      }
    }
    else
    {
      D_801F4E45 = c - 1;
    }
  }
  return;
}




void func_8013CABC(void) {

    extern s32 D_801F4E64;
    extern s32 D_801F4E58;
    extern s32 D_801F4E5C;
    extern s32 D_801F4E68;
    D_801F4E64 = 1;
    D_801F4E58 = 1;
    D_801F4E5C = 0;
    D_801F4E68 = 1;
}




void func_8013CAE8(void) {

    extern s32 D_801F4E58;
    extern s32 D_801F4E5C;
    extern s32 D_801F4E60;
    extern s32 D_801F4E64;
    extern s32 D_801F4E68;
    D_801F4E58 = 1;
    D_801F4E64 = 0;
    D_801F4E5C = 0;
    D_801F4E60 = -1;
    D_801F4E68 = 0;
}




void func_8013CB20(void)
{

    extern s32 D_801F4E64;
    extern s32 D_801F4E68;
    extern s32 D_801F4E90;
    extern s32 D_801F4E94;
    D_801F4E90 = D_801F4E68;
    D_801F4E94 = D_801F4E64;
    D_801F4E68 = 1;
    D_801F4E64 = 0;
}




void func_8013CB5C(void) {

    extern s32 D_801F4E90;
    extern s32 D_801F4E94;
    extern s32 D_801F4E68;
    extern s32 D_801F4E64;
    D_801F4E68 = D_801F4E90;
    D_801F4E64 = D_801F4E94;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013CB84);



void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_801F6218;
    extern u8 D_801F6219;
    extern u8 D_801F621A;
    extern u8 D_801F621B;
    extern u8 D_801F621C;
    extern u8 D_801F621D;
    extern u8 D_801F621E;
    extern u8 D_801F621F;
    extern u8 D_801F6220;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801F6218; t1 = D_801F6219; t2 = D_801F621A;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801F621B; t1 = D_801F621C; t2 = D_801F621D;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801F621E; t1 = D_801F621F; t2 = D_801F6220;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern void func_8013D9B0();

void func_8013D064(void)
{

    extern s32 D_801F4E70;
    extern s32 D_801F4E58;
    extern s32 D_801F4E74;
    extern s32 D_801F4E64;
    if (D_801F4E70 != 0) {
        if (D_801F4E70 != 2) {
            if (((D_801F4E70 < 3) && (D_801F4E70 == 1)) &&
                (D_801F4E74 = D_801F4E74 + 1, 0x23a < D_801F4E74)) {
                D_801F4E58 = D_801F4E70;
                D_801F4E70 = 2;
            }
        } else {
            D_801F4E58 = D_801F4E58 + -1;
            if (D_801F4E58 == 0) {
                D_801F4E58 = D_801F4E70;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_801F4E64 == 0) {
                    D_801F4E70 = D_801F4E70 + 1;
                }
            }
        }
    }
    return;
}



extern void func_8013D9B0();

s32 func_8013D13C(void) {

    extern s32 D_801F4E64;
    func_8013D9B0();
    return D_801F4E64;
}




void func_8013D164(void) {

    extern s32 D_801F4E70;
    D_801F4E70 = 1;
}



void func_8013D178(void) {

    extern u8 D_801F6218;
    extern u8 D_801F6219;
    extern u8 D_801F621A;
    extern u8 D_801F621B;
    extern u8 D_801F621C;
    extern u8 D_801F621D;
    extern u8 D_801F621E;
    extern u8 D_801F621F;
    extern u8 D_801F6220;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    extern unsigned char D_801F62B8, D_801F62B9, D_801F62BA, D_801F62BB, D_801F62BC, D_801F62BD, D_801F62BE, D_801F62BF, D_801F62C0;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_801F6218; v = *p; t = D_801F62B8;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F6219; v = *p; t = D_801F62B9;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621A; v = *p; t = D_801F62BA;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621B; v = *p; t = D_801F62BB;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621C; v = *p; t = D_801F62BC;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621D; v = *p; t = D_801F62BD;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621E; v = *p; t = D_801F62BE;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F621F; v = *p; t = D_801F62BF;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801F6220; v = *p; t = D_801F62C0;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}




// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)


void func_8013D330(void) {

    extern u8 D_801F62FA;
    extern u8 D_801F636E;
    extern u8 D_801F6222;
    extern u8 D_801F62DC;
    extern u8 D_801F6200;
    extern u8 D_801F6221;
    extern s32 D_801F62E0;
    if ((D_801F62FA & 0xff) != D_801F636E) {
        D_801F62FA = ((D_801F62FA & 0xff) < D_801F636E) ? (D_801F62FA + 1) : (D_801F62FA - 1);
    }
    if ((D_801F6222 & 0xff) != D_801F62DC) {
        D_801F6222 = ((D_801F6222 & 0xff) < D_801F62DC) ? (D_801F6222 + 1) : (D_801F6222 - 1);
    }
    if ((D_801F6200 & 0xff) != D_801F6221) {
        D_801F6200 = ((D_801F6200 & 0xff) < D_801F6221) ? (D_801F6200 + 1) : (D_801F6200 - 1);
    }
    D_801F62E0 = 1;
}



// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)




extern void func_8013D53C(void);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{

    extern u8 D_80078E78[];
    extern void *D_801F4E48;
    extern void *D_801F4E4C;
    extern void *D_801F4E50;
    extern s32 D_801F4E78;
    extern s32 D_801F4E7C;
    extern s32 D_801F4E80;
    extern s32 D_801F6254[];
    extern u8 D_8018AC4C[];
    extern u8 D_8018ACF4[];
    extern u8 D_8018ABA4[];
    extern u8 D_8018ACA0[];
    extern u8 D_8018AD20[];
    extern u8 D_8018ABF8[];
    u8 *p = D_80078E78;

    D_801F4E78 = param_2;
    D_801F4E7C = (param_2 >> 2) & 3;
    D_801F4E80 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_801F4E48 = D_8018AC4C;
        D_801F4E4C = D_8018ACF4;
        D_801F4E50 = D_8018ABA4;
    } else {
        D_801F4E48 = D_8018ACA0;
        D_801F4E4C = D_8018AD20;
        D_801F4E50 = D_8018ABF8;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_801F4E80 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_801F4E78 & 2) != 0) {
            D_801F6254[0] = 0x140;
            D_801F6254[3] = 0x80;
            if (p[0x37] == 4) {
                D_801F6254[0] = 0x140;
                D_801F6254[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801F6254[0] = 0x140;
                D_801F6254[3] = 0x80;
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013D53C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013D8FC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013D9B0);


// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_801F4E50)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.


extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{

    extern void *D_801F4E50;
    extern s16 *D_801F4E54;
    extern s32 D_801F4E64;
    extern s32 D_801F4E84;
    extern s32 D_801F4E88;
    extern s32 D_801F4E8C;
    int *p;
    int x, y, z;
    int flag;

    if (D_801F4E54 != 0) {
        D_801F4E64 = 0;
        p = (int *)(param_1 * 12 + (int)D_801F4E50);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_801F4E84 != x) {
            flag = 1;
            if (D_801F4E84 < x) {
                if (x - D_801F4E84 < 5) {
                    D_801F4E84 = x;
                } else {
                    D_801F4E84 = D_801F4E84 + 4;
                }
            } else {
                if (D_801F4E84 - x < 5) {
                    D_801F4E84 = x;
                } else {
                    D_801F4E84 = D_801F4E84 - 4;
                }
            }
        }
        if (D_801F4E88 != y) {
            flag = 1;
            if (D_801F4E88 < y) {
                if (y - D_801F4E88 < 5) {
                    D_801F4E88 = y;
                } else {
                    D_801F4E88 = D_801F4E88 + 4;
                }
            } else {
                if (D_801F4E88 - y < 5) {
                    D_801F4E88 = y;
                } else {
                    D_801F4E88 = D_801F4E88 - 4;
                }
            }
        }
        if (D_801F4E8C != z) {
            flag = 1;
            if (D_801F4E8C < z) {
                if (z - D_801F4E8C < 5) {
                    D_801F4E8C = z;
                } else {
                    D_801F4E8C = D_801F4E8C + 4;
                }
            } else {
                if (D_801F4E8C - z < 5) {
                    D_801F4E8C = z;
                } else {
                    D_801F4E8C = D_801F4E8C - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_801F4E64 = flag;
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013DD68);



s32 func_8013E054(void) {

    extern s32 D_801F4E6C;
    return D_801F4E6C;
}


DEFINE_func_8013E064()  /* dedup: shared engine-core @0x8013e064 (src/shared) */


DEFINE_func_8013E0FC()  /* dedup: shared engine-core @0x8013e0fc (src/shared) */


DEFINE_func_8013E194()  /* dedup: shared engine-core @0x8013e194 (src/shared) */


DEFINE_func_8013E22C()  /* dedup: shared engine-core @0x8013e22c (src/shared) */


DEFINE_func_8013E298()  /* dedup: shared engine-core @0x8013e298 (src/shared) */


DEFINE_func_8013E2C4()  /* dedup: shared engine-core @0x8013e2c4 (src/shared) */


DEFINE_func_8013E370()  /* dedup: shared engine-core @0x8013e370 (src/shared) */


DEFINE_func_8013E410()  /* dedup: shared engine-core @0x8013e410 (src/shared) */


DEFINE_func_8013E448()  /* dedup: shared engine-core @0x8013e448 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013E4B4);

DEFINE_func_8013E558()  /* dedup: shared engine-core @0x8013e558 (src/shared) */


DEFINE_func_8013E588()  /* dedup: shared engine-core @0x8013e588 (src/shared) */



extern void func_80029444(void);
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
extern void func_80141C04(void);


void func_8013E5E8(void)
{

    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_8018B7C0[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8018B7C0[D_80115112];
    fp();
    func_800190AC();
    func_80141C04();
    D_80115116 += 1;
}


DEFINE_func_8013E67C()  /* dedup: shared engine-core @0x8013e67c (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern s16 currentLocationId;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

void func_8013E6AC(void) {

    extern u8 D_80078EC0;
    extern u16 D_8011511A;
    extern u16 D_80115124;
    extern u8 D_80115148[];
    extern u8 D_80115140[];
    extern s32 D_8018B7AC;
    extern u16 D_80115110;
    extern s32 D_80115188;
    extern s16 D_8018B784;
    extern s16 D_8018B786;
    extern unsigned short D_80115112;
    short i;

    func_8013E83C();
    D_8011511A = 0;
    D_80115124 = D_80078EC0;
    for (i = 0; i < 8; i++) {
        *(s16 *)((char *)&D_80115148 + (i << 1)) = 0;
        D_80115140[i] = 0;
    }
    if (!((u32)func_80029504() < 5 || currentLocationId == 0x302A || currentLocationId == 0x3073)) {
        register s32 *ep __asm__("$8");
        register s32 *fp __asm__("$9");
        fp = (s32 *)&D_80115110;
        ep = (s32 *)&D_8018B7AC;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_8018B784 = 2;
        D_8018B786 = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_8018B786 = 0;
        D_8018B784 = 0;
        D_80115112 = 6;
    }
}


DEFINE_func_8013E814()  /* dedup: shared engine-core @0x8013e814 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (direct u16 global reads fold to lui/lhu; scheduler hoists the D_8011511A read above the prologue, reproduced by -O2)

void func_8013E83C() {

    extern u16 D_80115110;
    extern u16 D_8011511A;
    extern int func_80029178(int);
    extern void func_8002D4C8(int, int);
    extern void func_80141C0C(int);
    extern unsigned short D_80115118;
    extern unsigned short D_80115128;
    extern unsigned short D_8011512E;
    extern unsigned int D_80115130;
    extern unsigned short D_80115158;
    extern unsigned short D_8011515A;
    extern unsigned short D_8011515C;
    extern unsigned short D_8011515E;
    extern unsigned short D_80115162;
    extern unsigned short D_80115166;
    extern void * D_801F4EA0;
    extern void * D_801F4EA4;
    extern unsigned char D_8018B424;
    extern unsigned char D_8018B43C;
    extern unsigned char D_8018B4B0;
    extern unsigned char D_8018B4B8;

    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((func_80029178(0x1c) & 0xFF) == 0) {
        D_801F4EA0 = &D_8018B424;
        D_801F4EA4 = &D_8018B4B0;
    } else {
        D_801F4EA0 = &D_8018B43C;
        D_801F4EA4 = &D_8018B4B8;
    }

    D_8011515A = 0x104;
    D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;

    if (D_80115110 == 3) {
        func_8002D4C8(0x46e, 0);
    } else {
        func_80141C0C(0);
    }
}



// @class: schedule
// @stuck: none — MATCH (63 ins). The idx-32+ residual was a THIRD held base pointer for the
// D_80115188 store: the draft's `((Cell*)&D_80115188)[i].v = v` allocates a pointer, so gcc kept
// three bases (D_80115110/D_8018B7AC/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_8018B7AC -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

void func_8013E958()
{

    extern u8 D_80078EC0;
    extern u16 D_80115110;
    extern unsigned short D_80115112;
    extern u16 D_80115124;
    extern s32 D_80115188;
    extern s32 D_8018B7AC;
    extern void func_80139954(void);
    extern void func_8014AA28(void);
    extern s32 func_800D0488(s32);
    extern void func_80141C0C(s32);

    s16 *p = &(*(s16*)&D_80115124);
    s16 i;
    s32 v;
    s16 m;

    D_800B9A15 = 0;
    func_80139954();
    if (D_80078EC0 != *p) {
        func_8014AA28();
        if ((D_80078EC0 & 0x7F) != 0) {
            m = D_80078EC0 & 0x7F;
            *p = m;
            if (m == 0 || func_800D0488(m) == 0)
                goto loop;
        }
    }
    *p = 0;
loop:
    for (i = 0; i < 5; i++) {
        s32 *q = &((s32 *)&D_80115110)[i];
        v = ((s32 *)&D_8018B7AC)[i] >> 6;
        q[0x16] = v;
        *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
    }
    func_80141C0C(7);
    (*(u16*)&D_80115112) = 4;
}


DEFINE_func_8013EA54()  /* dedup: shared engine-core @0x8013ea54 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (sVar2 pinned to $v0 forces in-place sll/sra sign-ext scratch)


extern s32 func_80141C50(void);
extern void func_8013F350(void);
extern void func_8013FAF8(s16 a0, s16 a1);
extern s16 func_8014168C(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_801376E8(int a0, int a1);
extern void func_80137B80(void);
extern unsigned char *func_80141CA4(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013E958(void);


void func_8013EB7C(void) {

    extern short D_800B9A02;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern u16 D_8011511A;
    extern u16 D_8011511E;
    extern short D_80115128;
    extern unsigned short D_80115112;
    extern s16 D_8011512A;
    extern s32 D_80115130;
    extern unsigned char D_8018B788;
    s32 sp10[2];
    short sVar1;
    register short sVar2 __asm__("$2");
    s32 a0v;
    s32 iVar4;

    if ((s16)func_80141C50() == 0) {
        D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
        sVar1 = ((short (*)(void))func_8013F350)();
        if (D_8011511A >= 4) {
            func_8013FAF8((s16)D_8011511A, (s16)(D_8011511A + 1));
        }
        func_8013FAF8(0, 5);
        if (D_8011511A == 5) {
            sVar2 = ((short (*)(s32))func_8014168C)(2);
            a0v = 2;
        } else {
            sVar2 = ((short (*)(s32))func_8014168C)((s16)D_8011511A);
            a0v = (s16)D_8011511A;
        }
        iVar4 = func_8014032C(a0v, sVar2);
        if (iVar4 != 0) {
            s32 *p130 = &D_80115130;
            if (iVar4 != *p130) {
                *p130 = iVar4;
                func_80139954();
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_8018B788));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_8018B788));
            }
            (*(unsigned short *)&D_80115112) -= 1;
        } else {
            if ((D_8011511E & 0x800) != 0 || D_8011512A != 0) {
                func_8013E958();
            }
        }
    }
    (void)sp10;
}


DEFINE_func_8013ED6C()  /* dedup: shared engine-core @0x8013ed6c (src/shared) */


extern void func_801376E8(int a0, int a1);
extern void func_8013FAF8(s16 a0, s16 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_8018B786` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_8018B784` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.

typedef struct { s32 f0; } E4;



s32 func_8013EE10() {

    extern short D_800B9A02;
    extern unsigned short D_80115112;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern s16 D_8018B784;
    extern s16 D_8018B786;
    extern unsigned char D_8018B788;
    extern E4 aD80115188[] __asm__("D_80115188");
    extern E4 D_80115168[];
    extern unsigned short D_80115118;

    short i;
    u16 *p;
    u16 old;
    s16 *r;
    u16 *c;
    s32 sp10[2];

    D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
    func_8013FAF8(0, 5);
    for (i = 0; i < 5; i++) {
        s32 t = D_80115168[i].f0 * 3 >> 2;
        aD80115188[i].f0 = t;
        D_80115168[i].f0 = D_80115168[i].f0 - t;
    }
    r = &D_8018B786;
    if (*r < 3) {
        *r = *r + 1;
    }
    D_8018B784 = (u16)D_8018B784 + 2;
    p = &D_80115118;
    old = *p;
    *p = old + 1;
    if (old >= 5) {
        ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8018B788);
        for (i = 0; i < 5; i++) {
            s32 *q = (s32 *)((char *)p - 8);
            *(s32 *)((char *)&q[i] + 0x78) = 0;
            D_80115168[i].f0 = 0;
        }
        c = &D_80115112;
        *c += 1;
    }
    (void)sp10;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013EF88);



// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {

    extern unsigned short D_80115118;
    extern unsigned short D_80115112;
    extern u16 D_80115110;
    extern unsigned char D_8018B788;
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8018B788);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013f1bc (src/shared) */


DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013f244 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013F350);


// @class: regalloc-order
// @stuck: none — MATCH (312/312, relocation-masked)








typedef struct { u16 f0; s16 f2; } Prim4;
typedef struct { s16 x; s16 y; } Hw4;
typedef struct { s32 f0; u32 *f4; s32 f8; s32 fC; s32 f10; } Rec20;
typedef struct { u8 d[0x60]; } Blk60;


extern void  func_80140E6C(void);
extern void  func_80140F00(void);
extern s32  *func_80140958(s32 *, s32, s32);
extern int   func_80141100(int);
extern s16   func_8014168C(s16);
extern s32   func_8013FFD8(s16, s32, s32 *);
extern void func_80024054(void *a0, void *a1);
extern s32  *func_800D2650(s32 *, void *, s32, s32, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);
extern s32   func_800D27DC(s32, s32 *, void *, s32, s32);
extern s32  *func_800D29F8(s32, s32, void *, s32, s32);
extern int func_80137D08(int arg0, int arg1, short arg2);
extern s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3);


void func_8013FAF8(s16 arg0, s16 arg1) {

    extern s32    D_801151D0;
    extern u16    D_8011511A;
    extern short D_80115128;
    extern Hw4    D_8011516A[];
    extern u8     D_80078EC0;
    extern short D_800B9A02;
    extern Rec20  D_800AE7B8[];
    extern Blk60  D_8018AE0C[];
    extern Blk20  D_8018B10C[];
    extern Prim4  D_8018B20C[];
    extern Prim4  D_8018B27C[];
    extern Prim4 *D_8018B370[];
    extern s32    D_8018B390[];
    extern u8 D_8018B3B0;
    extern s16    D_8018B784;
    extern s16    D_8018B786;
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
    register s32 flag3 __asm__("$18");

    func_80140E6C();
    func_80140F00();
    ot = func_80140958((s32 *)D_801151D0, arg0, arg1);
    if (D_8011511A < 6) {
        ot = (s32 *)func_80141100((int)ot);
    }
    for (i = arg0; i < arg1; i++) {
        if (i == D_8011511A || i == 2 || i == 4) {
            flag = 0;
        } else {
            flag = 0xFF;
        }
        p = &D_8018B20C[i];
        if (i != 5) {
            if (i == 2) {
                addr = ((s32 *)&D_8018B3B0)[*(s16 *)&D_80115128];
            } else {
                addr = D_8018B390[i];
            }
        } else {
            addr = func_8013FFD8(2, func_8014168C(2), sp60);
        }
        func_80024054(addr, sp18);
        ot = func_800D2650(ot, sp18, (s16)(p->f0 + (u16)D_8011516A[i].x), p->f2, 1,
                           flag != 0 ? 0x585858 : 0x808080);
        p = D_8018B370[i];
        j = 0;
        if (p != 0) {
            if (i == 2 && *(s16 *)&D_80115128 != 0) {
                p = D_8018B27C;
            }
            flag2 = flag;
            for (;;) {
                r = func_8013FFD8(i, j++, sp60);
                if (r == 0) {
                    break;
                }
                if (r < 0) {
                    func_80024054(r, sp18);
                    t = 1;
                    if (i == 0 && (D_80078EC0 & 0x7F) == j) {
                        t = 0xB6;
                    }
                    if (flag2 != 0) {
                        sp60[0] += -0x282828;
                    }
                    ot = func_800D2650(ot, sp18, (s16)(p->f0 + (u16)D_8011516A[i].x), p->f2, t, sp60[0]);
                }
                p++;
            }
        }
        func_8005A600((s32)ot, 0, 0, 0x15, 0);
        flag3 = flag;
        *ot = 0x2000000;
        *ot = (D_800AE7B8[*(u16 *)&D_800B9A02].f4[2] & 0xFFFFFF) | 0x2000000;
        D_800AE7B8[*(u16 *)&D_800B9A02].f4[2] =
            (D_800AE7B8[*(u16 *)&D_800B9A02].f4[2] & 0xFF000000) | ((u32)ot & 0xFFFFFF);
        ot = func_800D29F8(flag3,
                           func_800D27DC(flag3 != 0, ot + 10, &D_8018AE0C[i], 8, D_8011516A[i].x),
                           &D_8018B10C[i], 2, D_8011516A[i].x);
    }
    pp = &D_8018B784;
    if (*pp == 0xE) {
        ot = func_80137D08(ot, &D_800AE7B8[*(u16 *)&D_800B9A02], 2);
    }
    if (*pp != 0 && D_8018B786 != 0) {
        ot = func_8013AB54(ot, D_800AE7B8[*(u16 *)&D_800B9A02].f4 + 2, (s32)(pp - 2), 0x8000);
    }
    D_801151D0 = (s32)ot;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8013FFD8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014032C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80140608);


// @class: iv-combine
// @stuck: none — MATCH (89 ins). Sequential struct fields fed from a running source
//         pointer compile to fixed offsets when written base[0..n]; the target advances
//         the pointer, so use post-increment `*p++` for EVERY field (gcc drops the dead
//         final increment, yielding the "increment N-2 then offset 0/2" tail).


extern s32 func_80028D58(void);
extern s32 func_80028DE0(void);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);

void func_801407F4(void)
{

    extern u8 *D_8018B464;
    extern u8 *D_8018B468;
    extern u8 *D_8018B46C;
    extern u8 *D_8018B470;
    extern u8 *D_8018B474;
    extern u16 *D_8018B478[];
    extern u16 *D_8018B480[];
    extern u16 *D_8018B4A0[];
    u8 *puVar1;
    s32 iVar2;
    u16 *puVar3;

    puVar1 = D_8018B464;
    iVar2 = func_80028D58();
    puVar3 = D_8018B478[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    puVar1 = D_8018B468;
    iVar2 = func_80028DE0();
    puVar3 = D_8018B478[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    iVar2 = func_80028FBC();
    *(s16 *)(D_8018B46C + 0x18) = *D_8018B480[iVar2];
    iVar2 = func_80029000();
    *(s16 *)(D_8018B470 + 0x18) = *D_8018B480[iVar2];

    puVar1 = D_8018B474;
    iVar2 = func_80028D9C();
    puVar3 = D_8018B4A0[iVar2];
    *(s16 *)(puVar1 + 0x12) = *puVar3++;
    *(s16 *)(puVar1 + 0x14) = *puVar3++;
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;
    *(s16 *)(puVar1 + 0x1c) = *puVar3++;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80140958);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80140D68);


// @class: struct
// @stuck: none — MATCH


extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);

void func_80140E6C(void) {

    extern unsigned char D_80078E7F;
    extern unsigned char D_80078E7E;
    extern unsigned char D_80078E7D;
    extern M2C_UNK D_8018B3A0;
    void *puVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int uVar4;

    puVar1 = (*(void * *)&D_8018B3A0);
    uVar2 = func_800D2CA8(D_80078E7F, 0x18);
    uVar3 = func_800D2CA8(D_80078E7E, 0xc);
    uVar4 = func_800D2CA8(D_80078E7D, 0);
    func_800D2D10(uVar2 | 0xb00000 | uVar3 | 0xb00 | uVar4, 8, puVar1, 0);
}




// @class: plumbing
// @stuck: none — MATCH (128/128 ins, match_one confirmed)


extern int func_80029FE4(void);
extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);
extern char *func_8002AAB4(void);
extern char *strcpy(char *, const char *);
extern int func_8002A26C(void);
extern int func_8002A2B0(void);
extern int func_8002A4B8(void);
extern s32 func_8002A4FC(s32 a0);
extern int func_8002A998(void);
extern int func_8002A9DC(void);
extern int func_8002A728(void);
extern int func_8002A76C(void);
extern int func_80029FD4(void);

void func_80140F00(void) {

    extern short D_80115128;
    extern u8 D_8018B3B0;
    extern char *D_8018B3D0;
    extern char *D_8018B3D4;
    extern char *D_8018B3D8;
    extern char *D_8018B3DC;
    extern char *D_8018B3E0;
    char *p;
    int r;

    if (D_80115128 == 0) {
        p = (*(char * *)&D_8018B3B0);
        r = func_800D2CA8(func_80029FE4() + 1, 0x18);
        func_800D2D10(r, 2, p + 4, 1);
        strcpy(p + 0xA, func_8002AAB4());

        p = D_8018B3D0;
        r = func_800D2CA8(func_8002A26C() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A2B0(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8018B3D4;
        r = func_800D2CA8(func_8002A4B8() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(((int (*)(void))func_8002A4FC)(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8018B3D8;
        r = func_800D2CA8(func_8002A998() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A9DC(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8018B3DC;
        r = func_800D2CA8(func_8002A728() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A76C(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8018B3E0;
        r = func_800D2CA8(func_80029FD4(), 4);
        func_800D2D10(r, 7, p + 0x18, -1);
    }
}




// @class: other
// @stuck: none — MATCH


extern s32 func_8002A1B4(void);
extern short func_8002A28C(void);
extern short func_8002A27C(void);
extern s32 func_8002A400(void);
extern short func_8002A4D8(void);
extern short func_8002A4C8(void);
extern s32 func_8002A8E0(void);
extern short func_8002A9B8(void);
extern short func_8002A9A8(void);
extern s32 func_8002A670(void);
extern short func_8002A748(void);
extern short func_8002A738(void);
extern int func_801412A8(int, int, int, int, int, int);

int func_80141100(int param_1)
{

    extern short D_80115128;
    extern unsigned short D_80115172;
    extern unsigned short D_8018B26A;
    extern unsigned short D_8018B26E;
    extern unsigned short D_8018B272;
    extern unsigned short D_8018B276;
    short sVar1;
    int iVar7;

    if (D_80115128 == 0) {
        iVar7 = D_80115172 + 0x31;
        sVar1 = D_8018B26A;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A1B4)(), func_8002A28C(), func_8002A27C(), (short)iVar7, (int)sVar1);
        sVar1 = D_8018B26E;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A400)(), func_8002A4D8(), func_8002A4C8(), (short)iVar7, (int)sVar1);
        sVar1 = D_8018B272;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A8E0)(), func_8002A9B8(), func_8002A9A8(), (short)iVar7, (int)sVar1);
        sVar1 = D_8018B276;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A670)(), func_8002A748(), func_8002A738(), (short)iVar7, (int)sVar1);
    }
    return param_1;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801412A8);

DEFINE_func_801415C0()  /* dedup: shared engine-core @0x801415c0 (src/shared) */


DEFINE_func_8014168C()  /* dedup: shared engine-core @0x8014168c (src/shared) */


DEFINE_func_801416D4()  /* dedup: shared engine-core @0x801416d4 (src/shared) */




void func_80141788(void)
{

    extern unsigned short D_80115112;
    extern void (*D_8018B800[])(void);
    D_8018B800[D_80115112]();
}


DEFINE_func_801417C4()  /* dedup: shared engine-core @0x801417c4 (src/shared) */


DEFINE_func_801417F8()  /* dedup: shared engine-core @0x801417f8 (src/shared) */



extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_80141C04(void);


void func_80141874(void) {

    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_8018B80C[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 → store retires early */
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8018B80C[D_80115112];
    fp();
    func_80141C04();
    D_80115116 += 1;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801418F8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80141A60);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80141B90);

void func_80141C04(void) {
}


// @class: struct
// @stuck: none — MATCH expected (indexed u16 global: (s16)param_1*2 + D_80115110, *2 array stride)

extern void func_8002D4C8(s32 a0, s32 a1);

void func_80141C0C(s32 param_1)
{

    extern u16 D_80115110;
    extern u8 D_8018B760;
    func_8002D4C8(*(u16 *)(&D_8018B760 + (((param_1 << 16) >> 15) + (u32)D_80115110) * 2), 0);
}


DEFINE_func_80141C50()  /* dedup: shared engine-core @0x80141c50 (src/shared) */


DEFINE_func_80141CA4()  /* dedup: shared engine-core @0x80141ca4 (src/shared) */


DEFINE_func_80142414()  /* dedup: shared engine-core @0x80142414 (src/shared) */


DEFINE_func_80142454()  /* dedup: shared engine-core @0x80142454 (src/shared) */



// @class: struct
// @stuck: none — MATCH (58 ins). STRUCT branch reconstruction + 3 levers: (1) §3-T4 branch-polarity
//   invert in the ==0 arm so the func_8012C218 cold path sinks to the tail; (2) *(volatile int*) on
//   the two extra param_1[0x32] reloads to defeat gcc CSE (gcc reloads via register reuse, not a store);
//   (3) param_1[0x7e] pinned to $v1 (register __asm__("$3")) + an input-only scheduling barrier
//   __asm__ __volatile__("" : : "r"(a)) on the 0xA read so the pinned load is anchored AFTER it in the
//   ==0 arm (matches the load2-reused-as-$v1 ordering).

extern void func_8012C218(void *a0);

void func_801424E4(short *param_1) {

    extern void (*D_8018B830[])(void);
    short sVar1;
    int iVar2;
    register unsigned short t __asm__("$3");

    (*D_8018B830[(unsigned short)param_1[1]])();
    if (*(unsigned short *)param_1 != 0) {
        if (param_1[0x38] != 0) {
            iVar2 = *(int *)(param_1 + 0x32);
            if (iVar2 == 0) {
                return;
            }
            *(int *)(param_1 + 2) = *(int *)(iVar2 + 4);
            t = (unsigned short)param_1[0x7e];
            sVar1 = *(unsigned short *)(iVar2 + 10) + t;
            param_1[5] = sVar1;
            *(int *)(param_1 + 6) = *(int *)(iVar2 + 0xc);
        } else {
            unsigned short a;
            iVar2 = *(int *)(param_1 + 0x32);
            if ((iVar2 != 0) && (*(short *)(iVar2 + 0x36) == param_1[0x7f])) {
                *(int *)(param_1 + 2) = *(int *)(iVar2 + 4);
                a = *(unsigned short *)(*(volatile int *)(param_1 + 0x32) + 10);
                __asm__ __volatile__("" : : "r"(a));
                t = (unsigned short)param_1[0x7e];
                sVar1 = a + t;
                iVar2 = *(volatile int *)(param_1 + 0x32);
                param_1[5] = sVar1;
                *(int *)(param_1 + 6) = *(int *)(iVar2 + 0xc);
                return;
            }
            ((void (*)(short *))func_8012C218)(param_1);
        }
    }
    return;
}




void func_801425CC(void *a0) {

    extern void (*D_8018B840[])(void);
    D_8018B840[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: schedule
// @stuck: none — MATCH expected; CAE4 block fallthrough, AD50 block goto-tail

extern void func_8012C1B8(void);
extern s32 func_8012C1DC(s32 a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void *a0);

void func_80142608(s32 param_1)
{

    extern s32 D_8018B824;
    register s32 iVar1 __asm__("$16");

    if (*(short *)(param_1 + 0x70) != 0) {
        iVar1 = ((s32 (*)(void))func_8012C1B8)();
    } else {
        iVar1 = func_8012C1DC(*(s32 *)(param_1 + 100));
    }
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CA1C(iVar1, (s32)&D_8018B824);
        *(short *)(iVar1 + 0x1a) = 0x200;
        *(short *)(iVar1 + 0x18) = 0x200;
        *(short *)(param_1 + 0xfc) = 0x40;
        if (*(short *)(param_1 + 0x70) != 0) {
            goto ad50;
        }
        if (*(s32 *)(param_1 + 100) != 0) {
            *(short *)(param_1 + 0xfe) = *(short *)(*(s32 *)(param_1 + 100) + 0x36);
            goto ad50;
        }
    }
    ((void (*)(s32))func_8012CAE4)(param_1);
    return;
ad50:
    *(short *)(param_1 + 0x98) = 0;
    *(s32 *)(param_1 + 0x90) = 0;
    ((void (*)(s32))func_8012AD50)(param_1);
}


DEFINE_func_801426D4()  /* dedup: shared engine-core @0x801426d4 (src/shared) */


DEFINE_func_80142740()  /* dedup: shared engine-core @0x80142740 (src/shared) */


DEFINE_func_80142778()  /* dedup: shared engine-core @0x80142778 (src/shared) */


void func_801427DC(void) {
}

void func_801427E4(void) {
}


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_801427EC(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_8018B854[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_8018B854[*(u16 *)(param_1 + 2)]();
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80142838);

DEFINE_func_801428CC()  /* dedup: shared engine-core @0x801428cc (src/shared) */



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_8014292C(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_8018B870[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_8018B870[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_80142978(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_8018BA40[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_8018BA40[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_801429C4(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_8018BAF8[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_8018BAF8[*(u16 *)(param_1 + 2)]();
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80142A10);


// @class: struct
// @stuck: none — MATCH (packed-word struct -> lwl/lwr unaligned copy; union byte[] -> $sp-direct lbu; branch-polarity invert -> beqz)


void func_80142A80(void)
{

    extern u16 D_800B99D8;
    extern struct packed_word D_801F44FC;
    extern u8 D_801F4EA8;
    extern u8 D_801F4EA9;
    extern u8 D_801F4EAA;
    u16 flags;
    union word_bytes local;
    s32 mul;

    flags = D_800B99D8;
    local.pw = D_801F44FC;

    if (flags & 0x10) {
        mul = (s8)((flags & 0xf) >> 1) + 9;
    } else {
        mul = 0x10 - (s8)((flags & 0xf) >> 1);
    }

    D_801F4EA8 = mul * (local.b[0] >> 4);
    D_801F4EA9 = mul * (local.b[1] >> 4);
    D_801F4EAA = mul * (local.b[2] >> 4);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80142B2C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80142BB4);

void func_80142C7C(void) {
}

DEFINE_func_80142C84()  /* dedup: shared engine-core @0x80142c84 (src/shared) */


DEFINE_func_80142C9C()  /* dedup: shared engine-core @0x80142c9c (src/shared) */


DEFINE_func_80142D38()  /* dedup: shared engine-core @0x80142d38 (src/shared) */


DEFINE_func_80142DB8()  /* dedup: shared engine-core @0x80142db8 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (combined store-assign `*(p)=v0=call()` keeps test/store on $v0, copy to $s0 for the else)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);


void func_80142DC4(int param_1)
{

    extern int D_8018B848;
    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))func_8012C1B8)();
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, s32))func_8001CA1C)(v0, (s32)&D_8018B848);
        *(short *)(v0 + 0x1a) = 0x1800;
        *(short *)(v0 + 0x18) = 0x1800;
        *(short *)(param_1 + 0xfc) = 0;
        ((void (*)(int))func_80142B2C)(param_1);
    }
}



// @class: regalloc-order
// @stuck: none — MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);


void func_80142E38(int param_1)
{

    extern unsigned char D_8018B864[];
    short sVar1;
    int iVar2;

    *(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))func_8012C1B8)();
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(iVar2, &D_8018B864);
        sVar1 = (*(unsigned short *)(param_1 + 0x70) & 0xf) * 0x600 + 0x1200;
        *(short *)(iVar2 + 0x1a) = sVar1;
        *(short *)(iVar2 + 0x18) = sVar1;
        *(short *)(param_1 + 0xfc) = 0;
        ((void (*)(int))func_80142B2C)(param_1);
    }
}



// @class: regalloc-order
// @stuck: none — MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);


void func_80142EC0(s32 param_1) {

    extern s32 D_8018BA30[];
    register s32 d   __asm__("$16") = param_1;   /* $s0 */
    register s32 obj __asm__("$17");             /* $s1 */
    s32 ret;
    s16 sVar2;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(d + 0x20) = ret;
    obj = ret;
    if (ret == 0) {
        ((void (*)(s32))func_8012CAE4)(d);
    } else {
        func_8001CA1C(obj, 0);
        sVar2 = (s16)((*(u16 *)(d + 0x70) & 0xf) * 0x600 + 0xc00);
        *(s16 *)(obj + 0x1a) = sVar2;
        *(s16 *)(obj + 0x18) = sVar2;
        *(s16 *)(d + 0xfc) = 0;
        ((void (*)(s32, s32))func_8012A828)(d, D_8018BA30[*(u16 *)(d + 0x70) & 0xf]);
        ((void (*)(s32))func_80142B2C)(d);
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80142F68);

DEFINE_func_80142FFC()  /* dedup: shared engine-core @0x80142ffc (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (38 ins). $16=param pin; explicit $17 copy of the call result
//         survives across func_8001CA1C while $v0 serves the pre-call store/test;
//         store BEFORE the s1 copy so the store keeps $v0 (not the saved copy).

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);


void func_8014305C(int param_1)
{

    extern unsigned char D_8018BA50[];
    extern unsigned char D_8018BAB0[];
    register int s0_param __asm__("$16") = param_1;
    register int s1_copy __asm__("$17");
    int iVar2;
    short sVar1;

    iVar2 = ((int (*)(void))func_8012C1B8)();
    *(int *)(s0_param + 0x20) = iVar2;
    s1_copy = iVar2;
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(s0_param);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(s1_copy, D_8018BA50);
        sVar1 = (*(unsigned short *)(s0_param + 0x70) & 0xf) * 0x600 + 0xc00;
        *(short *)(s1_copy + 0x1a) = sVar1;
        *(short *)(s1_copy + 0x18) = sVar1;
        *(short *)(s0_param + 0xfc) = 0;
        func_8012A828(s0_param, D_8018BAB0);
        ((void (*)(int))func_80142B2C)(s0_param);
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801430F4);

DEFINE_func_80143188()  /* dedup: shared engine-core @0x80143188 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (memcpy unaligned copy; $s0 survivor pinned, store-before-copy keeps $v0 for early store/branch)

extern void *memcpy(void *, const void *, u32);

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern int func_8001CA88(int, void *);
extern s32 func_8012E504(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80142B2C(void *arg0);


void func_801431E8(s32 param_1) {

    extern u8 D_801F44F8;
    extern u8 D_801F4EA8;
    extern u8 D_801F4EAC;
    u8 buf[8];
    s32 iVar5;
    u16 uVar2;
    s16 sVar4;

    register s32 d __asm__("$16");
    memcpy(buf, &D_801F44F8, 4);
    iVar5 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar5;
    d = iVar5;
    if (iVar5 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001CA88)(d, &D_801F4EA8);
        uVar2 = *(u16 *)(param_1 + 0x70);
        *(s16 *)(d + 0x76) = -0x10;
        sVar4 = (uVar2 & 0xf) * 0x600 + 0xc00;
        *(s16 *)(d + 0x1a) = sVar4;
        *(s16 *)(d + 0x18) = sVar4;
        *(u32 *)(d + 4) = *(u32 *)(d + 4) | 0x50000000;
        if (func_8012E504(param_1, 0x33) == 0) {
            *(s16 *)(param_1 + 0xfc) = 1;
            func_800233CC(&D_801F4EA8, 0x10);
            memcpy(&D_801F4EAC, buf, 4);
        } else {
            *(s16 *)(param_1 + 0xfc) = 0;
        }
        ((void (*)(s32))func_80142B2C)(param_1);
    }
}


DEFINE_func_801432FC()  /* dedup: shared engine-core @0x801432fc (src/shared) */


DEFINE_func_80143390()  /* dedup: shared engine-core @0x80143390 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801433F0);


// @class: plumbing
// @stuck: none — MATCH (pending gate)


extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_80143458(s32 param_1)
{

    extern u8 D_800D387C[];
    extern u32 D_8018BC08[];
    s32 p;
    u16 v;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_800D387C;

    p = *(s32 *)(param_1 + 0x20);
    if (*(s32 *)(p + 4) == 0) {
        *(s32 *)(p + 4) = 0x50000000;
    }

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x9c;

    v = *(u16 *)(param_1 + 0x34) & 0x7fff;
    if (v != 0) {
        p = *(s32 *)(param_1 + 0x20);
        *(u16 *)(p + 0x1a) = v;
        *(u16 *)(p + 0x18) = v;
    }

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24,
                  D_8018BC08[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014350C);


// @class: plumbing
// @stuck: none — MATCH (pending gate)


extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8014358C(s32 param_1)
{

    extern u8 D_8018BC18[];
    extern u32 D_8018BD14[];
    s32 p;
    u16 v;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_8018BC18;

    p = *(s32 *)(param_1 + 0x20);
    if (*(s32 *)(p + 4) == 0) {
        *(s32 *)(p + 4) = 0x50000000;
    }

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x90;

    v = *(u16 *)(param_1 + 0x34) & 0x7fff;
    if (v != 0) {
        p = *(s32 *)(param_1 + 0x20);
        *(u16 *)(p + 0x1a) = v;
        *(u16 *)(p + 0x18) = v;
    }

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24,
                  D_8018BD14[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


DEFINE_func_80143640()  /* dedup: shared engine-core @0x80143640 (src/shared) */


DEFINE_func_801437D8()  /* dedup: shared engine-core @0x801437d8 (src/shared) */


DEFINE_func_80143970()  /* dedup: shared engine-core @0x80143970 (src/shared) */


DEFINE_func_80143994()  /* dedup: shared engine-core @0x80143994 (src/shared) */


DEFINE_func_801439C0()  /* dedup: shared engine-core @0x801439c0 (src/shared) */


DEFINE_func_801439FC()  /* dedup: shared engine-core @0x801439fc (src/shared) */




void func_80143B30(void *a0) {

    extern void (*D_8018BD30[])(void);
    D_8018BD30[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143B6C()  /* dedup: shared engine-core @0x80143b6c (src/shared) */


DEFINE_func_80143BDC()  /* dedup: shared engine-core @0x80143bdc (src/shared) */




void func_80143C38(void *a0) {

    extern void (*D_8018BD3C[])(void);
    D_8018BD3C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143C74()  /* dedup: shared engine-core @0x80143c74 (src/shared) */




void func_80143C98(void *a0) {

    extern void (*D_8018BD44[])(void);
    D_8018BD44[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143CD4()  /* dedup: shared engine-core @0x80143cd4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80143D28);



void func_80143E68(void *a0) {

    extern void (*D_8018BD8C[])(void);
    D_8018BD8C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80143EA4(void) {
}

void func_80143EAC(void) {
}

void func_80143EB4(void) {
}

DEFINE_func_80143EBC()  /* dedup: shared engine-core @0x80143ebc (src/shared) */




void func_80144054(void *a0) {

    extern void (*D_8018BDA0[])(void);
    D_8018BDA0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80144090);

extern void func_8012C218(void *a0);

// @class: struct
// @stuck: none — MATCH (relocation-masked match_one); fn-ptr dispatch table + 0x1c counter, sibling idiom (func_801427EC/func_80143B30)


void func_801442F8(int param_1)
{

    extern void (*D_8018BDA8[])();
    int iVar1;

    D_8018BDA8[*(u16 *)(param_1 + 2)]();
    iVar1 = *(int *)(param_1 + 0x1c) + 1;
    *(int *)(param_1 + 0x1c) = iVar1;
    if (0x1d < iVar1) {
        func_8012C218(param_1);
    }
}



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);

void func_80144364(int param_1) {

    extern u8 D_8018BD24;
    int iVar3;
    u16 uVar2;
    s16 sVar1;

    iVar3 = ((s32 (*)(void))func_8012C194)();
    if (iVar3 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        uVar2 = *(u16 *)(*(int *)(param_1 + 0x64) + 0x36);
        *(int *)(param_1 + 0xCC) = iVar3;
        *(u16 *)(param_1 + 0xFC) = uVar2;
        func_8001CB6C((u8 *)iVar3, (s32)&D_8018BD24, 0x250, 0x1A0);
        *(s32 *)(iVar3 + 4) = 0x60000000;
        *(u8 *)(iVar3 + 0x27) = 0x14;
        *(u16 *)(iVar3 + 0x10) = 0x400;
        *(u16 *)(iVar3 + 8) = *(u16 *)(*(int *)(param_1 + 0x64) + 6);
        *(u16 *)(iVar3 + 0xA) = *(u16 *)(*(int *)(param_1 + 0x64) + 0xA);
        *(u16 *)(iVar3 + 0xC) = *(u16 *)(*(int *)(param_1 + 0x64) + 0xE);
        sVar1 = *(s16 *)(param_1 + 0x70);
        if (sVar1 != 0) {
            *(s16 *)(iVar3 + 0x1A) = sVar1;
            *(s16 *)(iVar3 + 0x18) = sVar1;
        } else {
            *(u16 *)(iVar3 + 0x1A) = 0x2000;
            *(u16 *)(iVar3 + 0x18) = 0x2000;
        }
        *(u16 *)(param_1 + 2) = 1;
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80144458);

DEFINE_func_80144558()  /* dedup: shared engine-core @0x80144558 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014462C);

DEFINE_func_801446A4()  /* dedup: shared engine-core @0x801446a4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (65 ins, match_one). Levers: uVar2/$2 + addr/$3 pins; split (uVar2&0xFFFFFFF) into addr then (addr|0x80000000)+8 deref; %hi/%lo of 0x80000008 via plain 0x80000000+8 (match_one masks the target's D_80000008 reloc, real bytes identical); v1/3 magic-divide; gv+fv reassoc (field-0x30 in own temp) loads field first
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_8014477C(void *param_1) {

    extern u8 D_8018BD4C;
    extern u8 D_8018BD58;
    s32 v0;
    s32 v1;
    register s32 uVar2 __asm__("$2");
    register s32 addr __asm__("$3");
    s32 gv;
    s32 fv;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(param_1);
        return;
    }
    ((void (*)(s32, void *))func_8001CA1C)(v0, &D_8018BD4C);
    if (*(u16 *)(*(s32 *)((s32)param_1 + 0x64)) != 0) {
        *(s16 *)((s32)param_1 + 0xFC) = *(u16 *)(*(s32 *)((s32)param_1 + 0x64) + 0x36);
        uVar2 = *(s32 *)(*(s32 *)((s32)param_1 + 0x64) + 0x58);
        if (uVar2 != 0) {
            addr = uVar2 & 0xFFFFFFF;
            gv = *(u16 *)((addr | 0x80000000) + 8);
            fv = *(u16 *)((s32)param_1 + 0xA) - 0x30;
            *(u16 *)((s32)param_1 + 0xA) = gv + fv;
        } else {
            *(u16 *)((s32)param_1 + 0xA) = *(u16 *)((s32)param_1 + 0xA) - 0x60;
        }
    }
    ((void (*)(void *, void *))func_8012A828)(param_1, &D_8018BD58);
    v1 = (s32)*(s16 *)((s32)param_1 + 0x70) << 0xC;
    *(s16 *)((s32)param_1 + 0x2) = 1;
    *(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) = v1 / 3;
    *(s32 *)((s32)param_1 + 0x1C) = 0x78;
}



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);


void func_80144880(s32 param_1)
{

    extern u8 D_8018BD24;
    extern u8 D_8018BD94;
    register s32 obj  __asm__("$16");   /* $s0 */
    register s32 self __asm__("$17") = param_1;  /* $s1 */
    register s32 b    __asm__("$2");    /* $v0 */
    s32 e;

    obj = ((s32 (*)(void))func_8012C194)();
    if (obj == 0) {
        ((void (*)(s32))func_8012CAE4)(self);
    } else {
        *(u16 *)(self + 0xFC) = *(u16 *)(*(s32 *)(self + 0x64) + 0x36);
        *(s32 *)(self + 0xCC) = obj;
        if (*(s16 *)(self + 0x70) == 1) {
            func_8001CB6C((u8 *)obj, (s32)&D_8018BD24, 0x250, 0x1A0);
            b = 0x14;
        } else {
            func_8001CB6C((u8 *)obj, (s32)&D_8018BD94, 0x300, 0x1D0);
            b = 0x6A;
        }
        *(u8 *)(obj + 0x27) = (u8)b;
        *(s32 *)(obj + 4) = 0x60000000;
        *(u16 *)(obj + 0x10) = 0x400;
        *(u16 *)(obj + 8) = *(u16 *)(*(s32 *)(self + 0x64) + 6);
        *(u16 *)(obj + 0xA) = *(u16 *)(*(s32 *)(self + 0x64) + 0xA);
        e = *(u16 *)(*(s32 *)(self + 0x64) + 0xE);
        *(u16 *)(obj + 0x1A) = 0x4000;
        *(u16 *)(obj + 0x18) = 0x4000;
        *(u16 *)(obj + 0xC) = (u16)e;
        *(s16 *)(self + 2) = *(s16 *)(self + 2) + 1;
    }
}


DEFINE_func_80144988()  /* dedup: shared engine-core @0x80144988 (src/shared) */




void func_801449C8(void *a0) {

    extern void (*D_8018BDB0[])(void);
    D_8018BDB0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A04()  /* dedup: shared engine-core @0x80144a04 (src/shared) */




void func_80144A2C(void *a0) {

    extern void (*D_8018BDB8[])(void);
    D_8018BDB8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A68()  /* dedup: shared engine-core @0x80144a68 (src/shared) */


void func_80144A90(void) {
}

DEFINE_func_80144A98()  /* dedup: shared engine-core @0x80144a98 (src/shared) */


DEFINE_func_80144AEC()  /* dedup: shared engine-core @0x80144aec (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80144B14);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80144B9C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801457A4);

void func_801458E0(void) {
}

DEFINE_func_801458E8()  /* dedup: shared engine-core @0x801458e8 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_8018C944 block defeats the tail-merge of the two identical D_8018C944 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145934(void) {

    extern u8 D_8018C944;
    extern u8 D_8018C8B4;
    extern u8 D_8018C890;
    extern u8 D_8018C86C;
    extern u8 D_8018C920;
    extern u8 D_8018C8FC;
    extern u8 D_8018C8D8;
    extern u8 D_8018C848;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_8018C944;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_8018C944 load from being
         * tail-merged with the v>=0x384 D_8018C944 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_8018C8B4;
    } else if (v >= 0x578) {
        p = &D_8018C890;
    } else if (v >= 0x514) {
        p = &D_8018C86C;
    } else if (v >= 0x384) {
        p = &D_8018C944;
    } else if (v >= 0x258) {
        p = &D_8018C920;
    } else if (v >= 0xC8) {
        p = &D_8018C8FC;
    } else if (v >= 0xA) {
        p = &D_8018C8D8;
    } else {
        p = &D_8018C848;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_8018C9D4 block defeats the tail-merge of the two identical D_8018C9D4 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145A2C(void) {

    extern u8 D_8018C9D4;
    extern u8 D_8018C8B4;
    extern u8 D_8018C890;
    extern u8 D_8018C86C;
    extern u8 D_8018C9B0;
    extern u8 D_8018C98C;
    extern u8 D_8018C968;
    extern u8 D_8018C848;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_8018C9D4;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_8018C9D4 load from being
         * tail-merged with the v>=0x384 D_8018C9D4 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_8018C8B4;
    } else if (v >= 0x578) {
        p = &D_8018C890;
    } else if (v >= 0x514) {
        p = &D_8018C86C;
    } else if (v >= 0x384) {
        p = &D_8018C9D4;
    } else if (v >= 0x258) {
        p = &D_8018C9B0;
    } else if (v >= 0xC8) {
        p = &D_8018C98C;
    } else if (v >= 0xA) {
        p = &D_8018C968;
    } else {
        p = &D_8018C848;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}


DEFINE_func_80145B24()  /* dedup: shared engine-core @0x80145b24 (src/shared) */


DEFINE_func_80145BF8()  /* dedup: shared engine-core @0x80145bf8 (src/shared) */


DEFINE_func_80145C54()  /* dedup: shared engine-core @0x80145c54 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80145CEC);



// @class: schedule
// @stuck: branch layout — 3-way dispatch on param_1; trying switch form

extern s32 func_80029178(s32 arg);
extern void func_80146014(s32 a0);


void func_80145EE8(s32 param_1)
{

    extern unsigned char D_8018BDCC[];
    extern unsigned char D_8018BDFC[];
    extern unsigned char D_8018BE4C[];
    extern unsigned char D_8018BE7C[];
    extern unsigned char D_8018BEAC[];
    switch (param_1) {
    case 0:
        if (((unsigned char (*)(int))func_80029178)(0x1F) != 0) {
            ((void (*)(void *))func_80146014)(D_8018BDCC);
        }
        if (((unsigned char (*)(int))func_80029178)(0x21) != 0) {
            ((void (*)(void *))func_80146014)(D_8018BDFC);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1E) != 0) {
            ((void (*)(void *))func_80146014)(D_8018BE4C);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1D) != 0) {
            ((void (*)(void *))func_80146014)(D_8018BE7C);
        }
        if (((unsigned char (*)(int))func_80029178)(0x20) == 0) {
            return;
        }
        ((void (*)(void *))func_80146014)(D_8018BEAC);
        break;
    case 1:
        ((void (*)(void *))func_80146014)(D_8018BDCC);
        ((void (*)(void *))func_80146014)(D_8018BDFC);
        ((void (*)(void *))func_80146014)(D_8018BE4C);
        ((void (*)(void *))func_80146014)(D_8018BE7C);
        ((void (*)(void *))func_80146014)(D_8018BEAC);
        break;
    }
}


DEFINE_func_80146014()  /* dedup: shared engine-core @0x80146014 (src/shared) */


void func_80146074(void) {
}


extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0(void);

void func_8014607C(void)
{
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
        "jal   func_80146128\n"
        "lui   $at, %%hi(D_801F4EE8)\n"
        "sw    $v0, %%lo(D_801F4EE8)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801F4EE8)\n"
        "lw    $v0, %%lo(D_801F4EE8)($v0)\n"
        "nop\n"
        "beqz  $v0, .L80146114\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_80146360\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_801463A0\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        ".L80146114:\n"
        "nop\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_80146128()  /* dedup: shared engine-core @0x80146128 (src/shared) */



// @class: struct
// @stuck: none — MATCH (fnptr-table idiom: D_8018BEFC[u8 idx](&arg))

void func_80146360(void)
{

    extern void (*D_8018BEFC[])(void *);
    extern u8 D_80126BA4;
    extern s32 D_80126B58;
    D_8018BEFC[D_80126BA4](&D_80126B58);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801463A0);

DEFINE_func_80146534()  /* dedup: shared engine-core @0x80146534 (src/shared) */


DEFINE_func_80146554()  /* dedup: shared engine-core @0x80146554 (src/shared) */


DEFINE_func_80146578()  /* dedup: shared engine-core @0x80146578 (src/shared) */


DEFINE_func_8014659C()  /* dedup: shared engine-core @0x8014659c (src/shared) */


DEFINE_func_801465C0()  /* dedup: shared engine-core @0x801465c0 (src/shared) */


DEFINE_func_801465E4()  /* dedup: shared engine-core @0x801465e4 (src/shared) */


DEFINE_func_80146608()  /* dedup: shared engine-core @0x80146608 (src/shared) */


DEFINE_func_801466B4()  /* dedup: shared engine-core @0x801466b4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801466F0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80146750);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014680C);

DEFINE_func_801468C8()  /* dedup: shared engine-core @0x801468c8 (src/shared) */


DEFINE_func_80146924()  /* dedup: shared engine-core @0x80146924 (src/shared) */


DEFINE_func_80146994()  /* dedup: shared engine-core @0x80146994 (src/shared) */


DEFINE_func_801469C8()  /* dedup: shared engine-core @0x801469c8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80146A6C);

DEFINE_func_80146AB4()  /* dedup: shared engine-core @0x80146ab4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80146AFC);

DEFINE_func_80146B9C()  /* dedup: shared engine-core @0x80146b9c (src/shared) */


DEFINE_func_80146C3C()  /* dedup: shared engine-core @0x80146c3c (src/shared) */


DEFINE_func_80146C98()  /* dedup: shared engine-core @0x80146c98 (src/shared) */


DEFINE_func_80146CA0()  /* dedup: shared engine-core @0x80146ca0 (src/shared) */


DEFINE_func_80146CB4()  /* dedup: shared engine-core @0x80146cb4 (src/shared) */


DEFINE_func_80146CC8()  /* dedup: shared engine-core @0x80146cc8 (src/shared) */


DEFINE_func_80146D30()  /* dedup: shared engine-core @0x80146d30 (src/shared) */


DEFINE_func_80146D80()  /* dedup: shared engine-core @0x80146d80 (src/shared) */


DEFINE_func_80146D90()  /* dedup: shared engine-core @0x80146d90 (src/shared) */


DEFINE_func_80146DB8()  /* dedup: shared engine-core @0x80146db8 (src/shared) */


DEFINE_func_80146DE8()  /* dedup: shared engine-core @0x80146de8 (src/shared) */


DEFINE_func_80146DF8()  /* dedup: shared engine-core @0x80146df8 (src/shared) */


DEFINE_func_80146E90()  /* dedup: shared engine-core @0x80146e90 (src/shared) */


DEFINE_func_80146E98()  /* dedup: shared engine-core @0x80146e98 (src/shared) */


DEFINE_func_80146EC0()  /* dedup: shared engine-core @0x80146ec0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80146F58);

DEFINE_func_80146FC4()  /* dedup: shared engine-core @0x80146fc4 (src/shared) */


DEFINE_func_8014704C()  /* dedup: shared engine-core @0x8014704c (src/shared) */


DEFINE_func_80147054()  /* dedup: shared engine-core @0x80147054 (src/shared) */


DEFINE_func_80147060()  /* dedup: shared engine-core @0x80147060 (src/shared) */


DEFINE_func_8014706C()  /* dedup: shared engine-core @0x8014706c (src/shared) */


DEFINE_func_80147078()  /* dedup: shared engine-core @0x80147078 (src/shared) */


DEFINE_func_80147084()  /* dedup: shared engine-core @0x80147084 (src/shared) */


DEFINE_func_8014708C()  /* dedup: shared engine-core @0x8014708c (src/shared) */


DEFINE_func_80147098()  /* dedup: shared engine-core @0x80147098 (src/shared) */


DEFINE_func_801470A0()  /* dedup: shared engine-core @0x801470a0 (src/shared) */


DEFINE_func_801470AC()  /* dedup: shared engine-core @0x801470ac (src/shared) */


DEFINE_func_801470B4()  /* dedup: shared engine-core @0x801470b4 (src/shared) */


DEFINE_func_801470C0()  /* dedup: shared engine-core @0x801470c0 (src/shared) */


DEFINE_func_80147118()  /* dedup: shared engine-core @0x80147118 (src/shared) */


DEFINE_func_80147264()  /* dedup: shared engine-core @0x80147264 (src/shared) */


DEFINE_func_80147290()  /* dedup: shared engine-core @0x80147290 (src/shared) */


DEFINE_func_801472B4()  /* dedup: shared engine-core @0x801472b4 (src/shared) */


DEFINE_func_801472C8()  /* dedup: shared engine-core @0x801472c8 (src/shared) */


DEFINE_func_801472DC()  /* dedup: shared engine-core @0x801472dc (src/shared) */


DEFINE_func_801472F0()  /* dedup: shared engine-core @0x801472f0 (src/shared) */


DEFINE_func_80147300()  /* dedup: shared engine-core @0x80147300 (src/shared) */


DEFINE_func_80147324()  /* dedup: shared engine-core @0x80147324 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80147364);

DEFINE_func_801473DC()  /* dedup: shared engine-core @0x801473dc (src/shared) */


DEFINE_func_801473EC()  /* dedup: shared engine-core @0x801473ec (src/shared) */


DEFINE_func_80147460()  /* dedup: shared engine-core @0x80147460 (src/shared) */


DEFINE_func_80147478()  /* dedup: shared engine-core @0x80147478 (src/shared) */


DEFINE_func_801474D8()  /* dedup: shared engine-core @0x801474d8 (src/shared) */


DEFINE_func_801474EC()  /* dedup: shared engine-core @0x801474ec (src/shared) */


DEFINE_func_80147514()  /* dedup: shared engine-core @0x80147514 (src/shared) */


DEFINE_func_80147628()  /* dedup: shared engine-core @0x80147628 (src/shared) */


DEFINE_func_80147718()  /* dedup: shared engine-core @0x80147718 (src/shared) */


DEFINE_func_80147788()  /* dedup: shared engine-core @0x80147788 (src/shared) */


DEFINE_func_801477A8()  /* dedup: shared engine-core @0x801477a8 (src/shared) */


DEFINE_func_801477C8()  /* dedup: shared engine-core @0x801477c8 (src/shared) */


DEFINE_func_801477E8()  /* dedup: shared engine-core @0x801477e8 (src/shared) */


DEFINE_func_80147814()  /* dedup: shared engine-core @0x80147814 (src/shared) */


DEFINE_func_80147860()  /* dedup: shared engine-core @0x80147860 (src/shared) */


DEFINE_func_801478B8()  /* dedup: shared engine-core @0x801478b8 (src/shared) */


DEFINE_func_80147928()  /* dedup: shared engine-core @0x80147928 (src/shared) */


DEFINE_func_80147948()  /* dedup: shared engine-core @0x80147948 (src/shared) */


DEFINE_func_8014799C()  /* dedup: shared engine-core @0x8014799c (src/shared) */


DEFINE_func_801479BC()  /* dedup: shared engine-core @0x801479bc (src/shared) */


DEFINE_func_80147A10()  /* dedup: shared engine-core @0x80147a10 (src/shared) */


DEFINE_func_80147A30()  /* dedup: shared engine-core @0x80147a30 (src/shared) */


DEFINE_func_80147A84()  /* dedup: shared engine-core @0x80147a84 (src/shared) */


DEFINE_func_80147AAC()  /* dedup: shared engine-core @0x80147aac (src/shared) */


DEFINE_func_80147AD4()  /* dedup: shared engine-core @0x80147ad4 (src/shared) */


DEFINE_func_80147B18()  /* dedup: shared engine-core @0x80147b18 (src/shared) */


DEFINE_func_80147B5C()  /* dedup: shared engine-core @0x80147b5c (src/shared) */


DEFINE_func_80147C30()  /* dedup: shared engine-core @0x80147c30 (src/shared) */


DEFINE_func_80147CC8()  /* dedup: shared engine-core @0x80147cc8 (src/shared) */


DEFINE_func_80147D38()  /* dedup: shared engine-core @0x80147d38 (src/shared) */


DEFINE_func_80147DC0()  /* dedup: shared engine-core @0x80147dc0 (src/shared) */


DEFINE_func_80147E44()  /* dedup: shared engine-core @0x80147e44 (src/shared) */


DEFINE_func_80147F50()  /* dedup: shared engine-core @0x80147f50 (src/shared) */


DEFINE_func_80147F78()  /* dedup: shared engine-core @0x80147f78 (src/shared) */


DEFINE_func_80148038()  /* dedup: shared engine-core @0x80148038 (src/shared) */


DEFINE_func_80148094()  /* dedup: shared engine-core @0x80148094 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801483E8);

DEFINE_func_801484B0()  /* dedup: shared engine-core @0x801484b0 (src/shared) */


DEFINE_func_801484E8()  /* dedup: shared engine-core @0x801484e8 (src/shared) */


DEFINE_func_80148534()  /* dedup: shared engine-core @0x80148534 (src/shared) */


DEFINE_func_8014856C()  /* dedup: shared engine-core @0x8014856c (src/shared) */


DEFINE_func_801485B8()  /* dedup: shared engine-core @0x801485b8 (src/shared) */


DEFINE_func_80148634()  /* dedup: shared engine-core @0x80148634 (src/shared) */


DEFINE_func_80148648()  /* dedup: shared engine-core @0x80148648 (src/shared) */


DEFINE_func_801487F4()  /* dedup: shared engine-core @0x801487f4 (src/shared) */


DEFINE_func_80148800()  /* dedup: shared engine-core @0x80148800 (src/shared) */


DEFINE_func_8014880C()  /* dedup: shared engine-core @0x8014880c (src/shared) */


DEFINE_func_80148818()  /* dedup: shared engine-core @0x80148818 (src/shared) */


DEFINE_func_80148824()  /* dedup: shared engine-core @0x80148824 (src/shared) */


DEFINE_func_801488A8()  /* dedup: shared engine-core @0x801488a8 (src/shared) */


DEFINE_func_8014891C()  /* dedup: shared engine-core @0x8014891c (src/shared) */


DEFINE_func_80148980()  /* dedup: shared engine-core @0x80148980 (src/shared) */


DEFINE_func_801489E8()  /* dedup: shared engine-core @0x801489e8 (src/shared) */


DEFINE_func_80148A48()  /* dedup: shared engine-core @0x80148a48 (src/shared) */


DEFINE_func_80148AAC()  /* dedup: shared engine-core @0x80148aac (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (71 ins). switch binary-tree; s1 angle = pin-source-of-copy ($5 temp + retie); 2nd-block double-load + 0x80-clobber via $v1/$v0/$a0 pins + lazy hi-pin reusing dead c80 reg

extern s32 ratan2(s32 a0, s32 a1);

int func_80148AFC(void *a0) {

    extern s32 D_801151D4;
    extern ActorFn D_8018BF04[];
    s32 p = (s32)a0;
    s32 iVar5 = *(s32 *)(p + 0x20);
    register s32 tmp __asm__("$5") = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                        *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 sVar3;
    u8 bVar1;
    __asm__("" : "=r"(tmp) : "0"(tmp));
    sVar3 = tmp;
    bVar1 = *(u8 *)(p + 0xA9);

    switch (bVar1) {
    case 0x41:
        return D_8018BF04[*(u16 *)(p + 0xAA) >> 12](a0) & 0xFF;
    case 0x53:
    case 0x73:
        {
            register u32 bb __asm__("$3");
            register s32 c80 __asm__("$2") = 0x80;
            register s32 lo __asm__("$4");
            register s32 hi __asm__("$2");
            bb = *(u16 *)(p + 0xAE);
            lo = bb & 0xFF;
            if (lo != c80 || (hi = bb >> 8) != 0x80) {
                s32 sVar4;
                __asm__ __volatile__("" : : : "memory");
                sVar4 = ratan2((*(u16 *)(p + 0xAE) & 0xFF) - 0x80, 0x80 - (*(u16 *)(p + 0xAE) >> 8));
                *(u16 *)(iVar5 + 0x12) = (sVar3 + sVar4) & 0xFFF;
                return 1;
            }
            return 0;
        }
    }
}


DEFINE_func_80148C18()  /* dedup: shared engine-core @0x80148c18 (src/shared) */


DEFINE_func_80148C20()  /* dedup: shared engine-core @0x80148c20 (src/shared) */


DEFINE_func_80148C34()  /* dedup: shared engine-core @0x80148c34 (src/shared) */


DEFINE_func_80148C4C()  /* dedup: shared engine-core @0x80148c4c (src/shared) */


DEFINE_func_80148C64()  /* dedup: shared engine-core @0x80148c64 (src/shared) */


DEFINE_func_80148C7C()  /* dedup: shared engine-core @0x80148c7c (src/shared) */


DEFINE_func_80148C84()  /* dedup: shared engine-core @0x80148c84 (src/shared) */


DEFINE_func_80148C9C()  /* dedup: shared engine-core @0x80148c9c (src/shared) */


DEFINE_func_80148CB4()  /* dedup: shared engine-core @0x80148cb4 (src/shared) */


DEFINE_func_80148CCC()  /* dedup: shared engine-core @0x80148ccc (src/shared) */


DEFINE_func_80148CE4()  /* dedup: shared engine-core @0x80148ce4 (src/shared) */


DEFINE_func_80148CEC()  /* dedup: shared engine-core @0x80148cec (src/shared) */


DEFINE_func_80148CF4()  /* dedup: shared engine-core @0x80148cf4 (src/shared) */


DEFINE_func_80148D0C()  /* dedup: shared engine-core @0x80148d0c (src/shared) */


DEFINE_func_80148D24()  /* dedup: shared engine-core @0x80148d24 (src/shared) */


DEFINE_func_80148D3C()  /* dedup: shared engine-core @0x80148d3c (src/shared) */



// @class: schedule
// @stuck: none — MATCH (68 ins)
extern s32 ratan2(s32 a0, s32 a1);

s32 func_80148D44(void) {

    extern s32 D_801151D4;
    extern u8 D_80126C01;
    extern u16 D_80126C02;
    extern u16 D_80126C06;
    extern s32 D_8018BF44[];
    register s32 ang __asm__("$16");
    register s32 a __asm__("$4");
    s32 p;
    s32 res;
    s32 d;

    p = D_801151D4;
    a = (ratan2(*(s32 *)(p + 0x44) - *(s32 *)(p + 0x50),
                  *(s32 *)(p + 0x48) - *(s32 *)(p + 0x3c)) - 0x400) & 0xFFF;
    d = (s32)D_80126C01;
    __asm__ __volatile__("" : : "r"(a));
    ang = a;
    if (d == 0x53) {
        goto final;
    }
    if (d < 0x54) {
        if (d == 0x41) {
            goto call;
        }
        return 0x41;
    }
    if (d != 0x73) {
        return 0x73;
    }
    goto final;
call:
    return (s32)(s16)((s16 (*)())(D_8018BF44[D_80126C02 >> 0xc]))();
final:
    {
        u32 e = D_80126C06;
        if (((e & 0xff) == 0x80) && ((e >> 8) == (e & 0xff))) {
            return -1;
        }
        __asm__ __volatile__("" : : : "memory");
        res = (ang + ratan2((D_80126C06 & 0xff) - 0x80, 0x80 - (D_80126C06 >> 8))) & 0xFFF;
    }
    return res;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80148E54);

DEFINE_func_80148F60()  /* dedup: shared engine-core @0x80148f60 (src/shared) */


DEFINE_func_80148F68()  /* dedup: shared engine-core @0x80148f68 (src/shared) */


DEFINE_func_80148F74()  /* dedup: shared engine-core @0x80148f74 (src/shared) */


DEFINE_func_80148F80()  /* dedup: shared engine-core @0x80148f80 (src/shared) */


DEFINE_func_80148F8C()  /* dedup: shared engine-core @0x80148f8c (src/shared) */


DEFINE_func_80148F98()  /* dedup: shared engine-core @0x80148f98 (src/shared) */


DEFINE_func_80148FA0()  /* dedup: shared engine-core @0x80148fa0 (src/shared) */


DEFINE_func_80148FAC()  /* dedup: shared engine-core @0x80148fac (src/shared) */


DEFINE_func_80148FB8()  /* dedup: shared engine-core @0x80148fb8 (src/shared) */


DEFINE_func_80148FC4()  /* dedup: shared engine-core @0x80148fc4 (src/shared) */


DEFINE_func_80148FD0()  /* dedup: shared engine-core @0x80148fd0 (src/shared) */


DEFINE_func_80148FD8()  /* dedup: shared engine-core @0x80148fd8 (src/shared) */


DEFINE_func_80148FE0()  /* dedup: shared engine-core @0x80148fe0 (src/shared) */


DEFINE_func_80148FEC()  /* dedup: shared engine-core @0x80148fec (src/shared) */


DEFINE_func_80148FF8()  /* dedup: shared engine-core @0x80148ff8 (src/shared) */


DEFINE_func_80149004()  /* dedup: shared engine-core @0x80149004 (src/shared) */


DEFINE_func_8014900C()  /* dedup: shared engine-core @0x8014900c (src/shared) */


DEFINE_func_80149020()  /* dedup: shared engine-core @0x80149020 (src/shared) */


DEFINE_func_80149034()  /* dedup: shared engine-core @0x80149034 (src/shared) */


DEFINE_func_80149048()  /* dedup: shared engine-core @0x80149048 (src/shared) */


DEFINE_func_8014905C()  /* dedup: shared engine-core @0x8014905c (src/shared) */


DEFINE_func_80149078()  /* dedup: shared engine-core @0x80149078 (src/shared) */


DEFINE_func_801490E0()  /* dedup: shared engine-core @0x801490e0 (src/shared) */


DEFINE_func_801490E8()  /* dedup: shared engine-core @0x801490e8 (src/shared) */


DEFINE_func_801490F0()  /* dedup: shared engine-core @0x801490f0 (src/shared) */


DEFINE_func_801490F8()  /* dedup: shared engine-core @0x801490f8 (src/shared) */


DEFINE_func_80149184()  /* dedup: shared engine-core @0x80149184 (src/shared) */


DEFINE_func_801491C4()  /* dedup: shared engine-core @0x801491c4 (src/shared) */


DEFINE_func_80149204()  /* dedup: shared engine-core @0x80149204 (src/shared) */


DEFINE_func_80149210()  /* dedup: shared engine-core @0x80149210 (src/shared) */


DEFINE_func_80149228()  /* dedup: shared engine-core @0x80149228 (src/shared) */


DEFINE_func_80149284()  /* dedup: shared engine-core @0x80149284 (src/shared) */


DEFINE_func_80149290()  /* dedup: shared engine-core @0x80149290 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80149350);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80149374);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801493D0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014942C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80149450);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801494CC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80149544);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80149584);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801495C4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014964C);

DEFINE_func_801496D4()  /* dedup: shared engine-core @0x801496d4 (src/shared) */


DEFINE_func_80149704()  /* dedup: shared engine-core @0x80149704 (src/shared) */


DEFINE_func_80149724()  /* dedup: shared engine-core @0x80149724 (src/shared) */


DEFINE_func_80149744()  /* dedup: shared engine-core @0x80149744 (src/shared) */


DEFINE_func_80149788()  /* dedup: shared engine-core @0x80149788 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801497A8);

DEFINE_func_80149864()  /* dedup: shared engine-core @0x80149864 (src/shared) */


DEFINE_func_80149884()  /* dedup: shared engine-core @0x80149884 (src/shared) */


DEFINE_func_801498C0()  /* dedup: shared engine-core @0x801498c0 (src/shared) */


DEFINE_func_801498E0()  /* dedup: shared engine-core @0x801498e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80149954);

DEFINE_func_80149A64()  /* dedup: shared engine-core @0x80149a64 (src/shared) */


DEFINE_func_80149AA8()  /* dedup: shared engine-core @0x80149aa8 (src/shared) */


DEFINE_func_80149AD4()  /* dedup: shared engine-core @0x80149ad4 (src/shared) */


DEFINE_func_80149B14()  /* dedup: shared engine-core @0x80149b14 (src/shared) */


DEFINE_func_80149B54()  /* dedup: shared engine-core @0x80149b54 (src/shared) */


DEFINE_func_80149BAC()  /* dedup: shared engine-core @0x80149bac (src/shared) */


DEFINE_func_80149BEC()  /* dedup: shared engine-core @0x80149bec (src/shared) */


DEFINE_func_80149C08()  /* dedup: shared engine-core @0x80149c08 (src/shared) */


DEFINE_func_80149C94()  /* dedup: shared engine-core @0x80149c94 (src/shared) */


DEFINE_func_80149CB4()  /* dedup: shared engine-core @0x80149cb4 (src/shared) */


DEFINE_func_80149CD4()  /* dedup: shared engine-core @0x80149cd4 (src/shared) */


DEFINE_func_80149D10()  /* dedup: shared engine-core @0x80149d10 (src/shared) */


DEFINE_func_80149D9C()  /* dedup: shared engine-core @0x80149d9c (src/shared) */


DEFINE_func_80149DD8()  /* dedup: shared engine-core @0x80149dd8 (src/shared) */


DEFINE_func_80149E94()  /* dedup: shared engine-core @0x80149e94 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80149F2C);

void func_80149FA8(void) {
}


// @class: regalloc-order
// @stuck: none — MATCH (38 ins)
extern s16 currentLocationId;

s32 func_80149FB0(s32 a0) {

    extern s32 D_8018BFC4[];
    extern u8 D_80078E78[];
    s32 *p = &D_8018BFC4[0];
    register s32 v __asm__("$3") = *p;
    u8 *q = &D_80078E78[0];
    s32 loc;

    if (v != 0) {
        loc = currentLocationId;
        p = p + 1;
        do {
            if (loc == v) {
                goto ret0;
            }
            v = *p;
            p = p + 1;
        } while (v != 0);
    }

    if ((*(u32 *)(a0 + 0x44) & 0x400) != 0) {
        return 0;
    }
    if (*(s16 *)(a0 + 0x1C8) != 0) {
        return 0;
    }
    if ((*(u16 *)(a0 + 0xAC) & 0x100) == 0) {
    ret0:
        return 0;
    }
    v = q[0x48];
    q[0x48] = v ^ 0x80;
    return 1;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014A048);

DEFINE_func_8014A1B0()  /* dedup: shared engine-core @0x8014a1b0 (src/shared) */


DEFINE_func_8014A218()  /* dedup: shared engine-core @0x8014a218 (src/shared) */


DEFINE_func_8014A238()  /* dedup: shared engine-core @0x8014a238 (src/shared) */


DEFINE_func_8014A2E4()  /* dedup: shared engine-core @0x8014a2e4 (src/shared) */


DEFINE_func_8014A380()  /* dedup: shared engine-core @0x8014a380 (src/shared) */


DEFINE_func_8014A3E0()  /* dedup: shared engine-core @0x8014a3e0 (src/shared) */


DEFINE_func_8014A454()  /* dedup: shared engine-core @0x8014a454 (src/shared) */


DEFINE_func_8014A4B4()  /* dedup: shared engine-core @0x8014a4b4 (src/shared) */


DEFINE_func_8014A4FC()  /* dedup: shared engine-core @0x8014a4fc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014A51C);

DEFINE_func_8014A59C()  /* dedup: shared engine-core @0x8014a59c (src/shared) */


DEFINE_func_8014A638()  /* dedup: shared engine-core @0x8014a638 (src/shared) */


DEFINE_func_8014A674()  /* dedup: shared engine-core @0x8014a674 (src/shared) */


DEFINE_func_8014A680()  /* dedup: shared engine-core @0x8014a680 (src/shared) */


DEFINE_func_8014A69C()  /* dedup: shared engine-core @0x8014a69c (src/shared) */


DEFINE_func_8014A6A8()  /* dedup: shared engine-core @0x8014a6a8 (src/shared) */


DEFINE_func_8014A6C4()  /* dedup: shared engine-core @0x8014a6c4 (src/shared) */


DEFINE_func_8014A71C()  /* dedup: shared engine-core @0x8014a71c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014A738);

DEFINE_func_8014A830()  /* dedup: shared engine-core @0x8014a830 (src/shared) */


DEFINE_func_8014A850()  /* dedup: shared engine-core @0x8014a850 (src/shared) */


DEFINE_func_8014AA04()  /* dedup: shared engine-core @0x8014aa04 (src/shared) */


DEFINE_func_8014AA28()  /* dedup: shared engine-core @0x8014aa28 (src/shared) */


DEFINE_func_8014AB5C()  /* dedup: shared engine-core @0x8014ab5c (src/shared) */


DEFINE_func_8014AB7C()  /* dedup: shared engine-core @0x8014ab7c (src/shared) */


DEFINE_func_8014ABF0()  /* dedup: shared engine-core @0x8014abf0 (src/shared) */


DEFINE_func_8014AC10()  /* dedup: shared engine-core @0x8014ac10 (src/shared) */


DEFINE_func_8014ACC0()  /* dedup: shared engine-core @0x8014acc0 (src/shared) */


DEFINE_func_8014ACE8()  /* dedup: shared engine-core @0x8014ace8 (src/shared) */


DEFINE_func_8014AD30()  /* dedup: shared engine-core @0x8014ad30 (src/shared) */


DEFINE_func_8014AD7C()  /* dedup: shared engine-core @0x8014ad7c (src/shared) */


DEFINE_func_8014ADA8()  /* dedup: shared engine-core @0x8014ada8 (src/shared) */


DEFINE_func_8014ADE0()  /* dedup: shared engine-core @0x8014ADE0 (src/shared) */

DEFINE_func_8014B00C()  /* dedup: shared engine-core @0x8014b00c (src/shared) */


DEFINE_func_8014B034()  /* dedup: shared engine-core @0x8014b034 (src/shared) */


DEFINE_func_8014B084()  /* dedup: shared engine-core @0x8014b084 (src/shared) */


DEFINE_func_8014B12C()  /* dedup: shared engine-core @0x8014b12c (src/shared) */


DEFINE_func_8014B154()  /* dedup: shared engine-core @0x8014b154 (src/shared) */


DEFINE_func_8014B160()  /* dedup: shared engine-core @0x8014b160 (src/shared) */


DEFINE_func_8014B190()  /* dedup: shared engine-core @0x8014b190 (src/shared) */


DEFINE_func_8014B2A8()  /* dedup: shared engine-core @0x8014b2a8 (src/shared) */


DEFINE_func_8014B2D0()  /* dedup: shared engine-core @0x8014b2d0 (src/shared) */


DEFINE_func_8014B2F8()  /* dedup: shared engine-core @0x8014b2f8 (src/shared) */


DEFINE_func_8014B310()  /* dedup: shared engine-core @0x8014b310 (src/shared) */


DEFINE_func_8014B33C()  /* dedup: shared engine-core @0x8014b33c (src/shared) */


DEFINE_func_8014B350()  /* dedup: shared engine-core @0x8014b350 (src/shared) */


DEFINE_func_8014B4C4()  /* dedup: shared engine-core @0x8014b4c4 (src/shared) */


DEFINE_func_8014B4D4()  /* dedup: shared engine-core @0x8014b4d4 (src/shared) */


DEFINE_func_8014B504()  /* dedup: shared engine-core @0x8014b504 (src/shared) */


DEFINE_func_8014B598()  /* dedup: shared engine-core @0x8014b598 (src/shared) */


DEFINE_func_8014B5B0()  /* dedup: shared engine-core @0x8014b5b0 (src/shared) */


DEFINE_func_8014B5B8()  /* dedup: shared engine-core @0x8014b5b8 (src/shared) */


DEFINE_func_8014B5C4()  /* dedup: shared engine-core @0x8014b5c4 (src/shared) */


DEFINE_func_8014B5D0()  /* dedup: shared engine-core @0x8014b5d0 (src/shared) */


DEFINE_func_8014B5D8()  /* dedup: shared engine-core @0x8014b5d8 (src/shared) */


DEFINE_func_8014B6F0()  /* dedup: shared engine-core @0x8014b6f0 (src/shared) */


DEFINE_func_8014B768()  /* dedup: shared engine-core @0x8014b768 (src/shared) */


DEFINE_func_8014B7A4()  /* dedup: shared engine-core @0x8014b7a4 (src/shared) */


DEFINE_func_8014B944()  /* dedup: shared engine-core @0x8014b944 (src/shared) */


DEFINE_func_8014BB0C()  /* dedup: shared engine-core @0x8014bb0c (src/shared) */


DEFINE_func_8014BB24()  /* dedup: shared engine-core @0x8014bb24 (src/shared) */


DEFINE_func_8014BC0C()  /* dedup: shared engine-core @0x8014bc0c (src/shared) */


DEFINE_func_8014BC44()  /* dedup: shared engine-core @0x8014bc44 (src/shared) */


DEFINE_func_8014BC80()  /* dedup: shared engine-core @0x8014bc80 (src/shared) */


DEFINE_func_8014BCC0()  /* dedup: shared engine-core @0x8014bcc0 (src/shared) */


DEFINE_func_8014BCEC()  /* dedup: shared engine-core @0x8014bcec (src/shared) */


DEFINE_func_8014BD24()  /* dedup: shared engine-core @0x8014bd24 (src/shared) */


DEFINE_func_8014BD60()  /* dedup: shared engine-core @0x8014bd60 (src/shared) */


DEFINE_func_8014BD98()  /* dedup: shared engine-core @0x8014bd98 (src/shared) */


DEFINE_func_8014BDC8()  /* dedup: shared engine-core @0x8014bdc8 (src/shared) */


void func_8014BDE0(void) {
}

DEFINE_func_8014BDE8()  /* dedup: shared engine-core @0x8014bde8 (src/shared) */


DEFINE_func_8014BE78()  /* dedup: shared engine-core @0x8014be78 (src/shared) */


DEFINE_func_8014BE9C()  /* dedup: shared engine-core @0x8014be9c (src/shared) */


DEFINE_func_8014BEC0()  /* dedup: shared engine-core @0x8014bec0 (src/shared) */


DEFINE_func_8014BEF8()  /* dedup: shared engine-core @0x8014bef8 (src/shared) */


DEFINE_func_8014BF18()  /* dedup: shared engine-core @0x8014bf18 (src/shared) */


DEFINE_func_8014BF48()  /* dedup: shared engine-core @0x8014bf48 (src/shared) */


DEFINE_func_8014BF6C()  /* dedup: shared engine-core @0x8014bf6c (src/shared) */


DEFINE_func_8014BF8C()  /* dedup: shared engine-core @0x8014bf8c (src/shared) */


DEFINE_func_8014BFB0()  /* dedup: shared engine-core @0x8014bfb0 (src/shared) */


DEFINE_func_8014BFD4()  /* dedup: shared engine-core @0x8014bfd4 (src/shared) */


DEFINE_func_8014BFF4()  /* dedup: shared engine-core @0x8014bff4 (src/shared) */


DEFINE_func_8014C010()  /* dedup: shared engine-core @0x8014c010 (src/shared) */


DEFINE_func_8014C050()  /* dedup: shared engine-core @0x8014c050 (src/shared) */


DEFINE_func_8014C088()  /* dedup: shared engine-core @0x8014c088 (src/shared) */


DEFINE_func_8014C0C8()  /* dedup: shared engine-core @0x8014c0c8 (src/shared) */


DEFINE_func_8014C118()  /* dedup: shared engine-core @0x8014c118 (src/shared) */


DEFINE_func_8014C168()  /* dedup: shared engine-core @0x8014c168 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014C1A0);

DEFINE_func_8014C1C8()  /* dedup: shared engine-core @0x8014c1c8 (src/shared) */


DEFINE_func_8014C278()  /* dedup: shared engine-core @0x8014c278 (src/shared) */


DEFINE_func_8014C2B0()  /* dedup: shared engine-core @0x8014c2b0 (src/shared) */


DEFINE_func_8014C308()  /* dedup: shared engine-core @0x8014c308 (src/shared) */


DEFINE_func_8014C3A4()  /* dedup: shared engine-core @0x8014c3a4 (src/shared) */


DEFINE_func_8014C3D0()  /* dedup: shared engine-core @0x8014c3d0 (src/shared) */


DEFINE_func_8014C43C()  /* dedup: shared engine-core @0x8014c43c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014C4AC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014C568);

DEFINE_func_8014C59C()  /* dedup: shared engine-core @0x8014c59c (src/shared) */



extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);

s16 func_8014C5D0(s32 a0, s32 a1) {

    extern u8 D_8018C054;
    return func_8014C5FC(a0, a1, &D_8018C054);
}


DEFINE_func_8014C5FC()  /* dedup: shared engine-core @0x8014c5fc (src/shared) */


DEFINE_func_8014C6AC()  /* dedup: shared engine-core @0x8014c6ac (src/shared) */


DEFINE_func_8014C6C0()  /* dedup: shared engine-core @0x8014c6c0 (src/shared) */


DEFINE_func_8014C6D0()  /* dedup: shared engine-core @0x8014c6d0 (src/shared) */


DEFINE_func_8014C6E0()  /* dedup: shared engine-core @0x8014c6e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014C6F4);

DEFINE_func_8014C860()  /* dedup: shared engine-core @0x8014c860 (src/shared) */


DEFINE_func_8014C88C()  /* dedup: shared engine-core @0x8014c88c (src/shared) */


DEFINE_func_8014C8C8()  /* dedup: shared engine-core @0x8014c8c8 (src/shared) */


DEFINE_func_8014C8F0()  /* dedup: shared engine-core @0x8014c8f0 (src/shared) */


DEFINE_func_8014C918()  /* dedup: shared engine-core @0x8014c918 (src/shared) */


DEFINE_func_8014C968()  /* dedup: shared engine-core @0x8014c968 (src/shared) */


DEFINE_func_8014C978()  /* dedup: shared engine-core @0x8014c978 (src/shared) */


DEFINE_func_8014C98C()  /* dedup: shared engine-core @0x8014c98c (src/shared) */


DEFINE_func_8014C99C()  /* dedup: shared engine-core @0x8014c99c (src/shared) */


DEFINE_func_8014CA00()  /* dedup: shared engine-core @0x8014ca00 (src/shared) */


DEFINE_func_8014CA14()  /* dedup: shared engine-core @0x8014ca14 (src/shared) */


DEFINE_func_8014CA70()  /* dedup: shared engine-core @0x8014ca70 (src/shared) */


DEFINE_func_8014CA88()  /* dedup: shared engine-core @0x8014ca88 (src/shared) */


DEFINE_func_8014CAE4()  /* dedup: shared engine-core @0x8014cae4 (src/shared) */


DEFINE_func_8014CAFC()  /* dedup: shared engine-core @0x8014cafc (src/shared) */


DEFINE_func_8014CB0C()  /* dedup: shared engine-core @0x8014cb0c (src/shared) */


DEFINE_func_8014CB1C()  /* dedup: shared engine-core @0x8014cb1c (src/shared) */


DEFINE_func_8014CB2C()  /* dedup: shared engine-core @0x8014cb2c (src/shared) */


DEFINE_func_8014CB58()  /* dedup: shared engine-core @0x8014cb58 (src/shared) */


DEFINE_func_8014CB68()  /* dedup: shared engine-core @0x8014cb68 (src/shared) */


DEFINE_func_8014CB7C()  /* dedup: shared engine-core @0x8014cb7c (src/shared) */


DEFINE_func_8014CB8C()  /* dedup: shared engine-core @0x8014cb8c (src/shared) */


DEFINE_func_8014CB9C()  /* dedup: shared engine-core @0x8014cb9c (src/shared) */


DEFINE_func_8014CBD8()  /* dedup: shared engine-core @0x8014cbd8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014CBE8);

DEFINE_func_8014CBF8()  /* dedup: shared engine-core @0x8014cbf8 (src/shared) */


DEFINE_func_8014CC28()  /* dedup: shared engine-core @0x8014cc28 (src/shared) */



extern void func_8014CD0C(u8 *a0);

void func_8014CCB4(void)
{

    extern int D_801F4EF0;
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014CD0C\n"
        "lui   $at, %%hi(D_801F4EF0)\n"
        "sw    $v0, %%lo(D_801F4EF0)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801F4EF0)\n"
        "lw    $v0, %%lo(D_801F4EF0)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014CD0C()  /* dedup: shared engine-core @0x8014cd0c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014CD80);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014CF04);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014D04C);

DEFINE_func_8014D0A4()  /* dedup: shared engine-core @0x8014d0a4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014D12C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014D2A0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014D3E0);

DEFINE_func_8014D438()  /* dedup: shared engine-core @0x8014d438 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014D4C0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014D610);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014D738);

DEFINE_func_8014D790()  /* dedup: shared engine-core @0x8014d790 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014D820);

DEFINE_func_8014DCE0()  /* dedup: shared engine-core @0x8014dce0 (src/shared) */


DEFINE_func_8014DD8C()  /* dedup: shared engine-core @0x8014dd8c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014DF3C);

DEFINE_func_8014DF94()  /* dedup: shared engine-core @0x8014df94 (src/shared) */


DEFINE_func_8014E048()  /* dedup: shared engine-core @0x8014e048 (src/shared) */


DEFINE_func_8014E284()  /* dedup: shared engine-core @0x8014E284 (src/shared) */

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014E434);

DEFINE_func_8014E48C()  /* dedup: shared engine-core @0x8014e48c (src/shared) */


DEFINE_func_8014E514()  /* dedup: shared engine-core @0x8014e514 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014E5B4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014E6A0);

DEFINE_func_8014E6F8()  /* dedup: shared engine-core @0x8014e6f8 (src/shared) */


DEFINE_func_8014E790()  /* dedup: shared engine-core @0x8014e790 (src/shared) */


DEFINE_func_8014E83C()  /* dedup: shared engine-core @0x8014e83c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014E934);

DEFINE_func_8014E98C()  /* dedup: shared engine-core @0x8014e98c (src/shared) */


DEFINE_func_8014EA4C()  /* dedup: shared engine-core @0x8014ea4c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014ED28);

DEFINE_func_8014ED80()  /* dedup: shared engine-core @0x8014ed80 (src/shared) */


DEFINE_func_8014EE14()  /* dedup: shared engine-core @0x8014ee14 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014F1F4);

DEFINE_func_8014F24C()  /* dedup: shared engine-core @0x8014f24c (src/shared) */


DEFINE_func_8014F2E0()  /* dedup: shared engine-core @0x8014f2e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014F3E8);


extern void func_8014F4C0(u8 *a0);

void func_8014F468(void)
{

    extern int D_801F4EF4;
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014F4C0\n"
        "lui   $at, %%hi(D_801F4EF4)\n"
        "sw    $v0, %%lo(D_801F4EF4)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801F4EF4)\n"
        "lw    $v0, %%lo(D_801F4EF4)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014F4C0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014F6F4);

DEFINE_func_8014F74C()  /* dedup: shared engine-core @0x8014f74c (src/shared) */



// @class: other
// @stuck: none — MATCH (full inline-asm $sp-switch trampoline w/ 0x40000 guard, jal func_8014FA70, stash D_801F4EF4; maspsx auto-fills jal delay slot)

extern s32 func_8014FA70(s32 a0);

void func_8014FA04(s32 a0)
{

    extern s32 D_801F4EF4;
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "sw    $ra, 16($sp)\n"
        "lw    $v0, 68($a0)\n"
        "lui   $v1, 0x4\n"
        "and   $v0, $v0, $v1\n"
        "bnez  $v0, 1f\n"
        "addu  $v0, $zero, $zero\n"
        "lui   $a1, 0x1f80\n"
        "ori   $a1, $a1, 0x03fc\n"
        "addu  $t0, $a1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014FA70\n"
        "lui   $at, %%hi(D_801F4EF4)\n"
        "sw    $v0, %%lo(D_801F4EF4)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801F4EF4)\n"
        "lw    $v0, %%lo(D_801F4EF4)($v0)\n"
        "1:\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014FA70()  /* dedup: shared engine-core @0x8014fa70 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014FBC0);

DEFINE_func_8014FC18()  /* dedup: shared engine-core @0x8014fc18 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014FCFC);

DEFINE_func_8014FD54()  /* dedup: shared engine-core @0x8014fd54 (src/shared) */


DEFINE_func_8014FDF4()  /* dedup: shared engine-core @0x8014fdf4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014FE60);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8014FFDC);

DEFINE_func_80150150()  /* dedup: shared engine-core @0x80150150 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80150170);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801502EC);

DEFINE_func_80150460()  /* dedup: shared engine-core @0x80150460 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80150480);

DEFINE_func_801504D8()  /* dedup: shared engine-core @0x801504d8 (src/shared) */


DEFINE_func_80150528()  /* dedup: shared engine-core @0x80150528 (src/shared) */


DEFINE_func_801505FC()  /* dedup: shared engine-core @0x801505fc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801506A4);

DEFINE_func_80150820()  /* dedup: shared engine-core @0x80150820 (src/shared) */


DEFINE_func_8015086C()  /* dedup: shared engine-core @0x8015086c (src/shared) */


DEFINE_func_801508B4()  /* dedup: shared engine-core @0x801508b4 (src/shared) */


DEFINE_func_801508F8()  /* dedup: shared engine-core @0x801508f8 (src/shared) */



extern s32 func_80021174(s32 a0, s32 a1);

s32 func_8015094C(s32 param_1) {

    extern S16 D_801F4500;
    extern s32 D_8018C084;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern u8 D_80126948[];
    struct { s32 x, mid, y; s32 _pad[9]; } arg;   /* 0x30 @ 0x10 */
    S16 local;                                     /* 0x10 @ 0x40 */
    s32 pad1[4];                                    /* 0x10 @ 0x50 */
    register u8 *cam __asm__("$17") = D_80126948;
    s32 ret;

    local = D_801F4500;
    arg.x = *(short *)(param_1 + 6);
    arg.mid = D_80126994;
    arg.y = *(short *)(param_1 + 0xe);
    ret = func_80021174(D_8018C084, (s32)&arg);
    if (ret == 0) {
        {
            short cur = *(short *)(param_1 + 6);
            s32 diff = D_80126990 - cur;
            s32 av = (diff < 0) ? -diff : diff;
            if (av >= 5) {
                *(short *)(param_1 + 6) = (diff >= 0) ? cur + 4 : cur - 4;
            }
        }
        {
            short cur = *(short *)(param_1 + 0xe);
            s32 diff = *(s32 *)(cam + 0x50) - cur;
            s32 av = (diff < 0) ? -diff : diff;
            if (av >= 5) {
                *(short *)(param_1 + 0xe) = (diff >= 0) ? cur + 4 : cur - 4;
            }
        }
        (void)&pad1;
        return 1;
    }
    return 0;
}



extern s32 func_8014FA70(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);

void func_80150A70(s32 a0)
{

    extern s32 D_801F4EF4;
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "addiu $sp, $sp, -24\n"
        "sw    $s0, 16($sp)\n"
        "addu  $s0, $a0, $zero\n"
        "sw    $ra, 20($sp)\n"
        "lh    $v1, 6($s0)\n"
        "lh    $v0, 136($s0)\n"
        "nop\n"
        "bne   $v1, $v0, 1f\n"
        "nop\n"
        "lh    $v1, 10($s0)\n"
        "lh    $v0, 138($s0)\n"
        "nop\n"
        "bne   $v1, $v0, 1f\n"
        "nop\n"
        "lh    $v1, 14($s0)\n"
        "lh    $v0, 140($s0)\n"
        "nop\n"
        "beq   $v1, $v0, 3f\n"
        "nop\n"
    "1:\n"
        "lw    $v0, 68($s0)\n"
        "lui   $v1, 0x4\n"
        "and   $v0, $v0, $v1\n"
        "bnez  $v0, 2f\n"
        "addiu $a0, $s0, 4\n"
        "lui   $a2, 0x1f80\n"
        "ori   $a2, $a2, 0x03fc\n"
        "addu  $t0, $a2, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014FA70\n"
        "addu  $a0, $s0, $zero\n"
        "lui   $at, %%hi(D_801F4EF4)\n"
        "sw    $v0, %%lo(D_801F4EF4)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "addiu $a0, $s0, 4\n"
    "2:\n"
        "jal   func_80015978\n"
        "addiu $a1, $s0, 136\n"
    "3:\n"
        "lw    $ra, 20($sp)\n"
        "lw    $s0, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        ".set\treorder\n"
        : : : "memory");
}



// @class: regalloc-order
// @stuck: none — MATCH (fn-ptr table; split idx-1 into a $v0-pinned temp to stop (idx-1)*4 strength-reducing into a -4 load offset AND land the subtract in $v0)


void func_80150B28(int param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_8018C088[])(void);
    u32 idx;
    register u32 sub __asm__("$2");

    if ((D_800AE6B0 & 0x80FFFFFF) == 0) {
        idx = *(u16 *)(param_1 + 0x16C);
        if (idx != 0 && idx < 0x26) {
            sub = idx - 1;
            D_8018C088[sub]();
        }
    }
    *(u16 *)(param_1 + 0x16C) = 0;
}


void func_80150B9C(void) {
}

DEFINE_func_80150BA4()  /* dedup: shared engine-core @0x80150ba4 (src/shared) */


DEFINE_func_80150BC8()  /* dedup: shared engine-core @0x80150bc8 (src/shared) */


DEFINE_func_80150C48()  /* dedup: shared engine-core @0x80150c48 (src/shared) */


DEFINE_func_80150CA0()  /* dedup: shared engine-core @0x80150ca0 (src/shared) */


DEFINE_func_80150CC4()  /* dedup: shared engine-core @0x80150cc4 (src/shared) */


DEFINE_func_80150CE4()  /* dedup: shared engine-core @0x80150ce4 (src/shared) */


DEFINE_func_80150D04()  /* dedup: shared engine-core @0x80150d04 (src/shared) */


DEFINE_func_80150D24()  /* dedup: shared engine-core @0x80150d24 (src/shared) */


DEFINE_func_80150D44()  /* dedup: shared engine-core @0x80150d44 (src/shared) */


DEFINE_func_80150D64()  /* dedup: shared engine-core @0x80150d64 (src/shared) */


DEFINE_func_80150D84()  /* dedup: shared engine-core @0x80150d84 (src/shared) */


DEFINE_func_80150DA4()  /* dedup: shared engine-core @0x80150da4 (src/shared) */


DEFINE_func_80150DC4()  /* dedup: shared engine-core @0x80150dc4 (src/shared) */


DEFINE_func_80150DE4()  /* dedup: shared engine-core @0x80150de4 (src/shared) */


DEFINE_func_80150E04()  /* dedup: shared engine-core @0x80150e04 (src/shared) */


DEFINE_func_80150E24()  /* dedup: shared engine-core @0x80150e24 (src/shared) */


DEFINE_func_80150E44()  /* dedup: shared engine-core @0x80150e44 (src/shared) */


DEFINE_func_80150E64()  /* dedup: shared engine-core @0x80150e64 (src/shared) */


DEFINE_func_80150E84()  /* dedup: shared engine-core @0x80150e84 (src/shared) */


DEFINE_func_80150EA4()  /* dedup: shared engine-core @0x80150ea4 (src/shared) */


DEFINE_func_80150EC4()  /* dedup: shared engine-core @0x80150ec4 (src/shared) */


void func_80150F78(void) {
}

DEFINE_func_80150F80()  /* dedup: shared engine-core @0x80150f80 (src/shared) */


DEFINE_func_80150FB4()  /* dedup: shared engine-core @0x80150fb4 (src/shared) */


DEFINE_func_80150FD8()  /* dedup: shared engine-core @0x80150fd8 (src/shared) */


DEFINE_func_80151014()  /* dedup: shared engine-core @0x80151014 (src/shared) */


DEFINE_func_80151038()  /* dedup: shared engine-core @0x80151038 (src/shared) */


DEFINE_func_80151070()  /* dedup: shared engine-core @0x80151070 (src/shared) */


DEFINE_func_80151094()  /* dedup: shared engine-core @0x80151094 (src/shared) */


void func_801510B8(void) {
}

void func_801510C0(void) {
}

DEFINE_func_801510C8()  /* dedup: shared engine-core @0x801510c8 (src/shared) */


DEFINE_func_801510EC()  /* dedup: shared engine-core @0x801510ec (src/shared) */


DEFINE_func_80151110()  /* dedup: shared engine-core @0x80151110 (src/shared) */


void func_80151130(void) {
}

DEFINE_func_80151138()  /* dedup: shared engine-core @0x80151138 (src/shared) */


DEFINE_func_8015115C()  /* dedup: shared engine-core @0x8015115c (src/shared) */


DEFINE_func_80151164()  /* dedup: shared engine-core @0x80151164 (src/shared) */


DEFINE_func_80151184()  /* dedup: shared engine-core @0x80151184 (src/shared) */


DEFINE_func_801511A8()  /* dedup: shared engine-core @0x801511a8 (src/shared) */


DEFINE_func_801511C4()  /* dedup: shared engine-core @0x801511c4 (src/shared) */


DEFINE_func_801511E0()  /* dedup: shared engine-core @0x801511e0 (src/shared) */


DEFINE_func_80151204()  /* dedup: shared engine-core @0x80151204 (src/shared) */


DEFINE_func_80151238()  /* dedup: shared engine-core @0x80151238 (src/shared) */


DEFINE_func_8015126C()  /* dedup: shared engine-core @0x8015126c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80151664);

DEFINE_func_801516F0()  /* dedup: shared engine-core @0x801516f0 (src/shared) */


DEFINE_func_8015173C()  /* dedup: shared engine-core @0x8015173c (src/shared) */


DEFINE_func_80151780()  /* dedup: shared engine-core @0x80151780 (src/shared) */


void func_80151878(void) {
}

DEFINE_func_80151880()  /* dedup: shared engine-core @0x80151880 (src/shared) */


DEFINE_func_801518D8()  /* dedup: shared engine-core @0x801518d8 (src/shared) */


DEFINE_func_80151924()  /* dedup: shared engine-core @0x80151924 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80151944);

DEFINE_func_80151980()  /* dedup: shared engine-core @0x80151980 (src/shared) */


DEFINE_func_801519C8()  /* dedup: shared engine-core @0x801519c8 (src/shared) */


DEFINE_func_80151AE4()  /* dedup: shared engine-core @0x80151ae4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80151B98);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80151C54);



void func_80151D24(void *a0) {

    extern void (*D_8018C12C[])(void);
    D_8018C12C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80151D60()  /* dedup: shared engine-core @0x80151d60 (src/shared) */


DEFINE_func_80151DB0()  /* dedup: shared engine-core @0x80151db0 (src/shared) */


DEFINE_func_80151E78()  /* dedup: shared engine-core @0x80151e78 (src/shared) */


DEFINE_func_80151ECC()  /* dedup: shared engine-core @0x80151ecc (src/shared) */


DEFINE_func_80151F38()  /* dedup: shared engine-core @0x80151f38 (src/shared) */


DEFINE_func_80151FB4()  /* dedup: shared engine-core @0x80151fb4 (src/shared) */




void func_80152058(void *a0) {

    extern void (*D_8018C150[])(void);
    D_8018C150[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152094()  /* dedup: shared engine-core @0x80152094 (src/shared) */



extern void func_80019064(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_801472C8(struct S *a0);
extern void func_80147324(s32 a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern int func_80151204(int arg, int a1);

void func_801520DC(s32 arg0)
{

    extern u8 D_80062C04[];
    extern M2C_UNK D_8018C140;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_8018C140);
    func_801477E8(arg0, 0x40000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146A6C(0x10, arg0, M2C_FIELD(arg0, s16 *, 6), M2C_FIELD(arg0, s16 *, 0xA), (s32) M2C_FIELD(arg0, s16 *, 0xE), 0, 0);
    func_80147324(0x441);
    func_80146CA0(arg0);
}


DEFINE_func_80152194()  /* dedup: shared engine-core @0x80152194 (src/shared) */


DEFINE_func_8015220C()  /* dedup: shared engine-core @0x8015220c (src/shared) */


DEFINE_func_80152254()  /* dedup: shared engine-core @0x80152254 (src/shared) */


extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801470AC(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80153C18();
void func_801522CC(s32 a0) {
    s32 v1;
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    func_80154A74(a0, 0x11);
    func_801553C0(a0);
    func_801470AC((s32 *)a0);
    func_801472B4((void *)a0);
    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(a0 + 0x3E) = 0;
    *(s16 *)(a0 + 0x40) = 0;
    *(s16 *)(a0 + 0x42) = 0;
    *(u8 *)(a0 + 0xDD) = 0;
    *(u16 *)(a0 + 0x3C) = *(u16 *)(a0 + 0x3C) & 0xFFFE;
    *(s16 *)(v1 + 0x10) = 0;
    *(u16 *)(a0 + 0x60) = 0x1000;
    *(u16 *)(a0 + 0x62) = 0x1000;
    *(u16 *)(a0 + 0x64) = 0x1000;
    func_801477E8((s32 *)a0, 0);
    func_80153C18(a0);
}




void func_80152370(void *a0) {

    extern void (*D_8018C164[])(void);
    D_8018C164[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801523AC()  /* dedup: shared engine-core @0x801523ac (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (67 ins)

extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80019064(void *a0);
extern int func_80151204(int arg, int a1);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80147324(s32 arg0);
extern void func_80146CA0(void *a0);


void func_801523F4(s32 arg0)
{

    extern u8 D_80062C04[];
    extern M2C_UNK D_800D5880;
    extern s32 D_800D58AC;
    extern u8 D_8018C170[];
    s32 pad[4];
    s32 buf[4];
    register s32 s0a __asm__("$16");                    /* $s0 = buf */
    register s32 s2a __asm__("$18") = (s32)&D_8018C170; /* $s2 = &D_8018C170 */

    ((void (*)(s32, s32))func_80146E90)(arg0, 0);
    func_80019064(&D_80062C04);
    ((void (*)(s32, s32))func_80151204)(arg0, *(s16 *)(arg0 + 0xF2));
    if ((s16)func_80012A60((s32)*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12),
                           (s32)*(s16 *)(arg0 + 0xF4)) >= 0x401) {
        ((void (*)(s32, s32))func_80154274)(arg0, (s32)&D_800D5880);
    } else {
        ((void (*)(s32, s32))func_80154274)(arg0, (s32)&D_800D58AC);
    }
    func_80154A74(arg0, 0x16);
    ((void (*)(s32))func_80149020)(arg0);
    s0a = (s32)buf;
    ((void (*)(s32, s32, s32))func_8001382C)((*(u16 *)(arg0 + 0xF4) - *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF,
                  s2a, s0a);
    ((void (*)(s32, s32))func_80146DB8)(arg0, s0a);
    ((void (*)(s32, s32))func_801477E8)(arg0, *(s32 *)(s2a + 0xC));
    func_80147324(0x451);
    ((void (*)(s32))func_80146CA0)(arg0);
    (void)pad;
}


DEFINE_func_80152500()  /* dedup: shared engine-core @0x80152500 (src/shared) */


DEFINE_func_801525F4()  /* dedup: shared engine-core @0x801525f4 (src/shared) */




void func_80152698(void *a0) {

    extern void (*D_8018C180[])(void);
    D_8018C180[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801526D4()  /* dedup: shared engine-core @0x801526d4 (src/shared) */


DEFINE_func_80152714()  /* dedup: shared engine-core @0x80152714 (src/shared) */


DEFINE_func_80152790()  /* dedup: shared engine-core @0x80152790 (src/shared) */




void func_8015282C(void *a0) {

    extern void (*D_8018C198[])(void);
    D_8018C198[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152868()  /* dedup: shared engine-core @0x80152868 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147324(s32 a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern int func_80151204(int arg, int a1);
extern void func_80154274(s32 *a0, s32 a1);

void func_801528B0(s32 arg0)
{

    extern u8 D_80062C04[];
    extern M2C_UNK D_800D5880;
    extern M2C_UNK D_8018C188;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_8018C188);
    func_801477E8(arg0, 0xFFF00000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}


DEFINE_func_8015294C()  /* dedup: shared engine-core @0x8015294c (src/shared) */


DEFINE_func_80152A08()  /* dedup: shared engine-core @0x80152a08 (src/shared) */


DEFINE_func_80152A50()  /* dedup: shared engine-core @0x80152a50 (src/shared) */


DEFINE_func_80152AC8()  /* dedup: shared engine-core @0x80152ac8 (src/shared) */




void func_80152B6C(void *a0) {

    extern void (*D_8018C1AC[])(void);
    D_8018C1AC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152BA8()  /* dedup: shared engine-core @0x80152ba8 (src/shared) */


DEFINE_func_80152BF0()  /* dedup: shared engine-core @0x80152bf0 (src/shared) */


DEFINE_func_80152C40()  /* dedup: shared engine-core @0x80152c40 (src/shared) */


DEFINE_func_80152C80()  /* dedup: shared engine-core @0x80152c80 (src/shared) */




void func_80152D24(void *a0) {

    extern void (*D_8018C1C8[])(void);
    D_8018C1C8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152D60()  /* dedup: shared engine-core @0x80152d60 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147324(s32 a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern int func_80151204(int arg, int a1);
extern void func_80154274(s32 *a0, s32 a1);

void func_80152DA8(s32 arg0)
{

    extern s32 D_80062C14;
    extern M2C_UNK D_800D5880;
    extern M2C_UNK D_8018C1B8;
    func_80019064(&D_80062C14);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    M2C_FIELD(arg0, s8 *, 0xDF) = 8;
    func_80146DB8(arg0, &D_8018C1B8);
    func_801477E8(arg0, 0xFFE40000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}


DEFINE_func_80152E4C()  /* dedup: shared engine-core @0x80152e4c (src/shared) */


DEFINE_func_80152EFC()  /* dedup: shared engine-core @0x80152efc (src/shared) */


DEFINE_func_80152F44()  /* dedup: shared engine-core @0x80152f44 (src/shared) */


DEFINE_func_80152FBC()  /* dedup: shared engine-core @0x80152fbc (src/shared) */




void func_80153060(void *a0) {

    extern void (*D_8018C1DC[])(void);
    D_8018C1DC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015309C()  /* dedup: shared engine-core @0x8015309c (src/shared) */


DEFINE_func_801530E4()  /* dedup: shared engine-core @0x801530e4 (src/shared) */


DEFINE_func_80153150()  /* dedup: shared engine-core @0x80153150 (src/shared) */


DEFINE_func_801531BC()  /* dedup: shared engine-core @0x801531bc (src/shared) */


DEFINE_func_80153204()  /* dedup: shared engine-core @0x80153204 (src/shared) */


DEFINE_func_8015327C()  /* dedup: shared engine-core @0x8015327c (src/shared) */




void func_80153320(void *a0) {

    extern void (*D_8018C1F0[])(void);
    D_8018C1F0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015335C()  /* dedup: shared engine-core @0x8015335c (src/shared) */


DEFINE_func_801533A4()  /* dedup: shared engine-core @0x801533a4 (src/shared) */


DEFINE_func_80153410()  /* dedup: shared engine-core @0x80153410 (src/shared) */


DEFINE_func_80153490()  /* dedup: shared engine-core @0x80153490 (src/shared) */


DEFINE_func_801534D8()  /* dedup: shared engine-core @0x801534d8 (src/shared) */


DEFINE_func_80153550()  /* dedup: shared engine-core @0x80153550 (src/shared) */


extern void func_80146D90(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014ED28(s32 _arg0);
extern void func_8014FA04(s32 a0);

s32 func_801535F4(void *arg0) {
    s32 var_s1;
    register u32 flags __asm__("$4");
    register u32 fcopy __asm__("$3");
    s32 ret;

    var_s1 = 0;
    if (((s32 (*)(void))func_8014ED28)() != 0) {
        func_80146D90((s32)arg0);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x34) > 0) &&
        (((s32 (*)(s32))func_8014CC28)((s32)arg0) != 0)) {
        var_s1 = 1;
    }
    flags = ((s32 (*)(s32))func_8014FA04)((s32)arg0);
    fcopy = flags;
    if (flags & 0x4000) {
        ret = 2;
    } else if (flags & 0x2000) {
        ret = 1;
    } else {
        ret = 4;
        if ((fcopy & 0x8000) == 0) {
            ret = var_s1;
        }
    }
    __asm__ __volatile__("" : : "r"(flags));
    return ret;
}


DEFINE_func_8015369C()  /* dedup: shared engine-core @0x8015369c (src/shared) */


DEFINE_func_801536DC()  /* dedup: shared engine-core @0x801536dc (src/shared) */


DEFINE_func_80153800()  /* dedup: shared engine-core @0x80153800 (src/shared) */


DEFINE_func_80153978()  /* dedup: shared engine-core @0x80153978 (src/shared) */


DEFINE_func_801539F8()  /* dedup: shared engine-core @0x801539f8 (src/shared) */


DEFINE_func_80153B58()  /* dedup: shared engine-core @0x80153b58 (src/shared) */


DEFINE_func_80153BD8()  /* dedup: shared engine-core @0x80153bd8 (src/shared) */


DEFINE_func_80153BF0()  /* dedup: shared engine-core @0x80153bf0 (src/shared) */


DEFINE_func_80153C18()  /* dedup: shared engine-core @0x80153c18 (src/shared) */


DEFINE_func_80153C30()  /* dedup: shared engine-core @0x80153c30 (src/shared) */


DEFINE_func_80153C44()  /* dedup: shared engine-core @0x80153c44 (src/shared) */


DEFINE_func_80153C74()  /* dedup: shared engine-core @0x80153c74 (src/shared) */


DEFINE_func_80153C8C()  /* dedup: shared engine-core @0x80153c8c (src/shared) */


DEFINE_func_80153C9C()  /* dedup: shared engine-core @0x80153c9c (src/shared) */


DEFINE_func_80153CBC()  /* dedup: shared engine-core @0x80153cbc (src/shared) */



// @class: struct
// @stuck: none — MATCH (expected); dispatch-table %lo-fold via extern fn-ptr array, s0 holds param across both calls
extern void func_80019064(void *a0);

void func_80153CCC(S80153CCC *a0) {

    extern s32 D_8018C204;
    extern void (*D_8018C22C[])(void *a0);
    extern s16 D_8011DB0C;
    extern u16 D_8011F748;
    ((s32 (*)(s32))func_80019064)((s32)&D_8018C204);
    D_8018C22C[a0->idx](a0);
    D_8011DB0C = 0;
    D_8011F748 = 0;
}


DEFINE_func_80153D34()  /* dedup: shared engine-core @0x80153d34 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (33/33)

extern void func_80147324(s32 arg0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
extern s16 currentLocationId;

void func_80153D7C(s32 param_1)
{

    extern u8 D_8018C20C;
    func_80147324(0x451);
    func_80154274((s32 *)param_1, (s32)&D_8018C20C);
    func_80149020((s32 *)param_1);
    *(u16 *)(param_1 + 0x244) = *(u16 *)(param_1 + 6);
    *(u16 *)(param_1 + 0x246) = *(u16 *)(param_1 + 10);
    *(u16 *)(param_1 + 0x248) = *(u16 *)(param_1 + 0xe);
    if (currentLocationId == 0x3075) *(u8 *)(param_1 + 0xde) = 0x14;
    else *(u8 *)(param_1 + 0xde) = 10;
    *(u8 *)(param_1 + 0xdf) = 0;
    __asm__ __volatile__("" ::: "memory");
    func_80146CA0((void *)param_1);
}


DEFINE_func_80153E00()  /* dedup: shared engine-core @0x80153e00 (src/shared) */


DEFINE_func_8015410C()  /* dedup: shared engine-core @0x8015410c (src/shared) */


DEFINE_func_80154134()  /* dedup: shared engine-core @0x80154134 (src/shared) */


DEFINE_func_80154150()  /* dedup: shared engine-core @0x80154150 (src/shared) */


DEFINE_func_80154190()  /* dedup: shared engine-core @0x80154190 (src/shared) */


DEFINE_func_801541D8()  /* dedup: shared engine-core @0x801541d8 (src/shared) */


DEFINE_func_80154218()  /* dedup: shared engine-core @0x80154218 (src/shared) */


DEFINE_func_80154274()  /* dedup: shared engine-core @0x80154274 (src/shared) */


DEFINE_func_801542A4()  /* dedup: shared engine-core @0x801542a4 (src/shared) */


DEFINE_func_801542DC()  /* dedup: shared engine-core @0x801542dc (src/shared) */


DEFINE_func_8015430C()  /* dedup: shared engine-core @0x8015430c (src/shared) */


DEFINE_func_80154358()  /* dedup: shared engine-core @0x80154358 (src/shared) */


DEFINE_func_80154418()  /* dedup: shared engine-core @0x80154418 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015444C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801549F8);

DEFINE_func_80154A74()  /* dedup: shared engine-core @0x80154a74 (src/shared) */


DEFINE_func_80154AB4()  /* dedup: shared engine-core @0x80154ab4 (src/shared) */


DEFINE_func_80154AE0()  /* dedup: shared engine-core @0x80154ae0 (src/shared) */


DEFINE_func_80154B20()  /* dedup: shared engine-core @0x80154b20 (src/shared) */


DEFINE_func_80154B4C()  /* dedup: shared engine-core @0x80154b4c (src/shared) */


DEFINE_func_80154B7C()  /* dedup: shared engine-core @0x80154b7c (src/shared) */


DEFINE_func_80154B98()  /* dedup: shared engine-core @0x80154b98 (src/shared) */


DEFINE_func_80154BC8()  /* dedup: shared engine-core @0x80154bc8 (src/shared) */


DEFINE_func_80154BE4()  /* dedup: shared engine-core @0x80154be4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80154C24);

DEFINE_func_80154ED8()  /* dedup: shared engine-core @0x80154ed8 (src/shared) */


DEFINE_func_80154F9C()  /* dedup: shared engine-core @0x80154f9c (src/shared) */



// @class: struct
// @stuck: none — MATCH (array-of-struct stride-8 base materialize + addu, %lo folded into addiu)

extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_800183E0(s32 a0);


void func_801550FC(s32 arg0)
{

    extern ImgRect8 D_8018C238[];
    if (arg0 & 0x40000000) {
        MoveImage(&D_8018C238[arg0 & 0xFF], 0x200, 0x100);
    } else {
        ((void (*)(void))func_800183E0)();
    }
}


DEFINE_func_80155150()  /* dedup: shared engine-core @0x80155150 (src/shared) */


DEFINE_func_801552F4()  /* dedup: shared engine-core @0x801552f4 (src/shared) */


DEFINE_func_80155344()  /* dedup: shared engine-core @0x80155344 (src/shared) */


DEFINE_func_80155394()  /* dedup: shared engine-core @0x80155394 (src/shared) */


DEFINE_func_801553A8()  /* dedup: shared engine-core @0x801553a8 (src/shared) */


DEFINE_func_801553C0()  /* dedup: shared engine-core @0x801553c0 (src/shared) */


DEFINE_func_80155440()  /* dedup: shared engine-core @0x80155440 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; decrement persists as separate addiu in delay slot


s32 func_80155458(s32 param_1)
{

    extern int (*D_8018C278[])(void);
    int idx;

    idx = *(unsigned char *)(param_1 + 0x4e);
    if (idx != 0) {
        idx = idx - 1;
        if ((*D_8018C278[idx])() == 0) {
            *(unsigned char *)(param_1 + 0x4e) = 0;
        }
    }
    return *(unsigned char *)(param_1 + 0x4e);
}


DEFINE_func_801554B8()  /* dedup: shared engine-core @0x801554b8 (src/shared) */


DEFINE_func_80155518()  /* dedup: shared engine-core @0x80155518 (src/shared) */


DEFINE_func_8015554C()  /* dedup: shared engine-core @0x8015554c (src/shared) */




void func_80155580(void *a0) {

    extern void (*D_8018C27C[])(void);
    D_8018C27C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801555BC()  /* dedup: shared engine-core @0x801555bc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801555F4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80155800);

DEFINE_func_80155A44()  /* dedup: shared engine-core @0x80155a44 (src/shared) */


DEFINE_func_80155B20()  /* dedup: shared engine-core @0x80155b20 (src/shared) */


DEFINE_func_80155B9C()  /* dedup: shared engine-core @0x80155b9c (src/shared) */


DEFINE_func_80155C0C()  /* dedup: shared engine-core @0x80155c0c (src/shared) */


DEFINE_func_80155C64()  /* dedup: shared engine-core @0x80155c64 (src/shared) */


DEFINE_func_80155D70()  /* dedup: shared engine-core @0x80155d70 (src/shared) */


DEFINE_func_80155E30()  /* dedup: shared engine-core @0x80155e30 (src/shared) */


DEFINE_func_80155EA4()  /* dedup: shared engine-core @0x80155ea4 (src/shared) */


void func_80155F58(void) {
}

DEFINE_func_80155F60()  /* dedup: shared engine-core @0x80155f60 (src/shared) */


DEFINE_func_80155F80()  /* dedup: shared engine-core @0x80155f80 (src/shared) */


DEFINE_func_80155FB0()  /* dedup: shared engine-core @0x80155fb0 (src/shared) */


DEFINE_func_80155FD4()  /* dedup: shared engine-core @0x80155fd4 (src/shared) */


DEFINE_func_80155FF8()  /* dedup: shared engine-core @0x80155ff8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80156044);

DEFINE_func_8015616C()  /* dedup: shared engine-core @0x8015616c (src/shared) */


DEFINE_func_80156370()  /* dedup: shared engine-core @0x80156370 (src/shared) */




S801563EC *func_801563EC(u16 idx) {

    extern S801563EC D_8018C470[];
    return &D_8018C470[idx];
}


DEFINE_func_8015640C()  /* dedup: shared engine-core @0x8015640c (src/shared) */


DEFINE_func_801564B0()  /* dedup: shared engine-core @0x801564b0 (src/shared) */


DEFINE_func_801565C0()  /* dedup: shared engine-core @0x801565c0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80156600);

DEFINE_func_80156648()  /* dedup: shared engine-core @0x80156648 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80156670);

DEFINE_func_801567BC()  /* dedup: shared engine-core @0x801567bc (src/shared) */


DEFINE_func_80156848()  /* dedup: shared engine-core @0x80156848 (src/shared) */


DEFINE_func_80156A14()  /* dedup: shared engine-core @0x80156a14 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; D_8011520C indexed by param_2 (byte) folds %lo; D_8018C6E0 indexed halfword folds %lo
extern void func_80147324(s32 arg0);

void func_80156A1C(s32 param_1, s32 param_2)
{

    extern unsigned char D_8011520C[];
    extern unsigned short D_8018C6E0[];
    if (*(unsigned char *)(param_1 + 0xDA) == 0) {
        func_80147324(D_8018C6E0[D_8011520C[param_2]]);
        *(unsigned char *)(param_1 + 0xDA) = *(unsigned char *)(param_1 + 0xDA) + 1;
    }
}


DEFINE_func_80156A88()  /* dedup: shared engine-core @0x80156a88 (src/shared) */


DEFINE_func_80156B74()  /* dedup: shared engine-core @0x80156b74 (src/shared) */


DEFINE_func_80156ECC()  /* dedup: shared engine-core @0x80156ecc (src/shared) */


DEFINE_func_80156FA8()  /* dedup: shared engine-core @0x80156fa8 (src/shared) */


DEFINE_func_80157158()  /* dedup: shared engine-core @0x80157158 (src/shared) */


DEFINE_func_801571C4()  /* dedup: shared engine-core @0x801571c4 (src/shared) */


DEFINE_func_801574DC()  /* dedup: shared engine-core @0x801574dc (src/shared) */


DEFINE_func_80157510()  /* dedup: shared engine-core @0x80157510 (src/shared) */




void func_80157544(void *a0) {

    extern void (*D_8018C6F0[])(void);
    D_8018C6F0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80157580()  /* dedup: shared engine-core @0x80157580 (src/shared) */


DEFINE_func_801575E4()  /* dedup: shared engine-core @0x801575e4 (src/shared) */


DEFINE_func_801576A8()  /* dedup: shared engine-core @0x801576a8 (src/shared) */


DEFINE_func_8015771C()  /* dedup: shared engine-core @0x8015771c (src/shared) */


DEFINE_func_8015773C()  /* dedup: shared engine-core @0x8015773c (src/shared) */



// @class: plumbing
// @stuck: none — MATCH expected (scalar global store + two sequential calls, param_1 saved across)

extern void func_80147078(s32 *a0, s16 a1);
extern void func_801578C0(s32 a0);

void func_80157788(int param_1)
{

    extern int D_801F4F28;
    D_801F4F28 = 300;
    ((void (*)(int, int))func_80147078)(param_1, 7);
    func_801578C0(param_1);
}



// @class: plumbing
// @stuck: none — MATCH expected (scalar global store + two sequential calls, param_1 saved across)

extern void func_80147078(s32 *a0, s16 a1);
extern void func_80157808(s32 a0);

void func_801577C8(int param_1)
{

    extern int D_801F4F28;
    D_801F4F28 = 300;
    ((void (*)(int, int))func_80147078)(param_1, 7);
    func_80157808(param_1);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80157808);

DEFINE_func_80157880()  /* dedup: shared engine-core @0x80157880 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (expected); STUB: param_1 held in $s0 across calls, u8 store of 9 before func_80154274

extern void func_80156648(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147324(s32 arg0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);
extern s32 func_801725A4(u8 *a0);

void func_801578C0(s32 param_1)
{

    extern u8 D_800D5128;
    extern u8 D_8018C6F8;
    ((void (*)(void))func_80156648)();
    *(u8 *)(param_1 + 0x1AA) = 9;
    func_80154274((s32 *)param_1, (s32)&D_800D5128);
    ((void (*)(s32 *, s32))func_80154A74)((s32 *)param_1, 0x15);
    func_80147324(0xC20);
    ((void (*)(s32 *, s32))func_80146DB8)((s32 *)param_1, (s32)&D_8018C6F8);
    ((void (*)(s32, s32 *, s32, s32))func_80146994)(4, (s32 *)param_1, 7, 0);
    ((void (*)(s32, s32 *, s32, s32))func_80146994)(5, (s32 *)param_1, 9, 0);
    ((void (*)(s32 *))func_80146CA0)((s32 *)param_1);
    ((void (*)(s32 *))func_801725A4)((s32 *)param_1);
}



// @class: other
// @stuck: none — MATCH (76 ins). Body is byte-identical with a plain transcription; the only
//   delta was frame size: target frame is 0x30 (saves at 0x20/0x24/0x28), not 0x20. Target reserves
//   a 16-byte UNREFERENCED stack local (no sp refs anywhere in the body) — gcc-2.7.2 does NOT
//   dead-strip an aggregate local even at -O2, so a dead `int frame_pad[4]` reproduces vars=16
//   (.frame $sp,48: vars=16, regs=3, args=16) with zero body footprint. match_one => MATCH.

extern void func_80147A10(int a0, int a1);
extern void func_80147A84(int);
extern void func_801473EC(s32 *a0);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_8014ED28(s32 _arg0);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern int func_80155FF8(int arg, int a1);
extern void func_80154A74(int, int);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern s32 func_801725A4(u8 *a0);


void func_8015795C(int param_1)
{

    extern unsigned char D_800D5178;
    extern unsigned char D_8018C708;
    int frame_pad[4]; /* dead 16-byte local: forces target's 0x30 frame (vars=16); never referenced */
    int iVar1;
    unsigned int uVar2;

    *(unsigned int *)(param_1 + 0x44) = *(unsigned int *)(param_1 + 0x44) | 2;
    ((int (*)(int, int))func_80147A10)(param_1, 0x400);
    if (*(int *)(param_1 + 0x2c) >= 0) {
        *(int *)(param_1 + 0x2c) = 0;
    }
    func_80147A84(param_1);
    ((void (*)(int))func_801473EC)(param_1);
    func_80148038(param_1, 0x1a000);
    func_80147460(param_1);
    iVar1 = ((int (*)(int))func_8014ED28)(param_1);
    if (iVar1 != 0) {
        func_80146D90(param_1);
    }
    uVar2 = ((int (*)(int))func_80161450)(param_1);
    if ((uVar2 & 5) != 0) {
        func_80157A8C(param_1);
        ((void (*)(int, int))func_80146E90)(param_1, 8);
        ((void (*)(int))func_80146CA0)(param_1);
    }
    if (uVar2 == 0) {
        ((void (*)(int, int))func_80155FF8)(param_1, *(unsigned char *)(param_1 + 0x1aa));
        if (*(unsigned char *)(param_1 + 0x1c0) != 0) {
            func_80154A74(param_1, 0x17);
            ((void (*)(int, void *))func_80154274)(param_1, &D_800D5178);
            ((void (*)(int, void *))func_80146DB8)(param_1, &D_8018C708);
            ((void (*)(int, int))func_801477E8)(param_1, 0xfff40000);
            *(short *)(param_1 + 2) = 4;
        }
        ((void (*)(int))func_801725A4)(param_1);
    }
    return;
}


DEFINE_func_80157A8C()  /* dedup: shared engine-core @0x80157a8c (src/shared) */


DEFINE_func_80157AC8()  /* dedup: shared engine-core @0x80157ac8 (src/shared) */


DEFINE_func_80157B74()  /* dedup: shared engine-core @0x80157b74 (src/shared) */


DEFINE_func_80157BC8()  /* dedup: shared engine-core @0x80157bc8 (src/shared) */


DEFINE_func_80157CCC()  /* dedup: shared engine-core @0x80157ccc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80157D20);

DEFINE_func_80157D74()  /* dedup: shared engine-core @0x80157d74 (src/shared) */




void func_80157DC4(void *a0) {

    extern void (*D_8018C758[])(void);
    D_8018C758[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80157E00()  /* dedup: shared engine-core @0x80157e00 (src/shared) */


DEFINE_func_80157E38()  /* dedup: shared engine-core @0x80157e38 (src/shared) */


DEFINE_func_80157EA4()  /* dedup: shared engine-core @0x80157ea4 (src/shared) */


DEFINE_func_80157F64()  /* dedup: shared engine-core @0x80157f64 (src/shared) */




void func_80157FC4(void *a0) {

    extern void (*D_8018C760[])(void);
    D_8018C760[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80158000()  /* dedup: shared engine-core @0x80158000 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (expected); straight-line call sequence with two stores scheduled into jal delay slots

extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147324(s32 arg0);
extern void func_80146CA0(void *a0);


void func_80158038(void * param)
{

    extern s32 D_800D51E0;
    extern s32 D_8018C72C;
    *(u8 *)(param + 0x1aa) = 0xe;
    func_80154274((s32 *)param, (s32)&D_800D51E0);
    func_80154A74(param, 0x15);
    func_80146DB8((s32 *)param, &D_8018C72C);
    *(s32 *)(param + 0x234) = 0;
    func_80146994(5, param, 0xc, 0);
    func_80147324(0x455);
    func_80146CA0((void *)param);
}


DEFINE_func_801580B4()  /* dedup: shared engine-core @0x801580b4 (src/shared) */


DEFINE_func_801581AC()  /* dedup: shared engine-core @0x801581ac (src/shared) */




void func_8015824C(void *a0) {

    extern void (*D_8018C76C[])(void);
    D_8018C76C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80158288()  /* dedup: shared engine-core @0x80158288 (src/shared) */


DEFINE_func_801582C0()  /* dedup: shared engine-core @0x801582c0 (src/shared) */


DEFINE_func_80158344()  /* dedup: shared engine-core @0x80158344 (src/shared) */



// @class: other
// @stuck: none — MATCH (branch-polarity invert on both dispatch ifs + goto block-order to put the v1!=0/L508 paths as fallthrough; phantom 0x10 frame via address-taken frame_pad[4] + (void)& — zero code)

extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern s32 func_801615C4(void *a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern int func_80155FF8(int arg, int a1);


void func_80158434(s32 param_1)
{

    extern u8 D_8018C73C;
    extern u8 D_800D533C;
    u32 uVar1;
    u32 uVar2;
    s32 frame_pad[4];
    (void)&frame_pad;

    *(u32 *)(param_1 + 0x44) = *(u32 *)(param_1 + 0x44) | 2;
    if ((*(u16 *)(param_1 + 0xB8) & 0x4000) != 0) {
        *(s32 *)(param_1 + 0x234) = *(s32 *)(param_1 + 0x234) + 1;
        ((s32 (*)(void))func_8014CBF8)();
        ((void (*)(s32))func_801474EC)(param_1);
        ((void (*)(s32, s32))func_801477E8)(param_1, 0xFFFA0000);
        ((void (*)(s32, s32))func_80146DB8)(param_1, (s32)&D_8018C73C);
    }
    if (*(s32 *)(param_1 + 0x234) != 0) {
        func_80148038(param_1, 0x10000);
        func_80147460(param_1);
        func_80147AD4(param_1, 0, 0, 0);
        ((void (*)(s32))func_801473EC)(param_1);
    }
    uVar1 = ((s32 (*)(s32, s32))func_801615C4)(param_1, 0);
    if (uVar1 != 0) {
        if (uVar1 == 1) goto LAB_80158508;
        uVar2 = uVar1 & 0x2000;
    } else {
        uVar2 = func_80146E98(param_1);
    }
    if (uVar2 == 0) goto LAB_80158528;
LAB_80158508:
    ((void (*)(s32, s32))func_80154274)(param_1, (s32)&D_800D533C);
    ((void (*)(s32))func_80146CA0)(param_1);
    return;
LAB_80158528:
    ((void (*)(s32, s32))func_80155FF8)(param_1, *(u8 *)(param_1 + 0x1AA));
}


DEFINE_func_80158548()  /* dedup: shared engine-core @0x80158548 (src/shared) */


DEFINE_func_801585A4()  /* dedup: shared engine-core @0x801585a4 (src/shared) */


DEFINE_func_801585AC()  /* dedup: shared engine-core @0x801585ac (src/shared) */


DEFINE_func_801585EC()  /* dedup: shared engine-core @0x801585ec (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80158638);

void func_80158794(void) {
}


// @class: plumbing
// @stuck: none — MATCH expected (3 scalar global stores + byte store + 6 calls, source order)

extern void func_80147084(s32 *a0);
extern void func_80147098(s32 *a0);
extern void func_801470AC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80158880(s32 *param);

void func_8015879C(s32 param_1) {

    extern s32 D_801F4F30;
    extern s32 D_801F4F3C;
    extern s32 D_801F4F40;
    D_801F4F30 = 0;
    D_801F4F3C = 1;
    D_801F4F40 = 0;
    *(u8 *)(param_1 + 0xa8) = 0;
    ((void (*)(void))func_80147084)();
    ((void (*)(s32))func_80147098)(param_1);
    ((void (*)(s32))func_801470AC)(param_1);
    ((void (*)(s32, s32))func_80147078)(param_1, 0x1a);
    ((void (*)(s32, s32))func_80146C98)(param_1, 1);
    ((void (*)(s32))func_80158880)(param_1);
}



// @class: plumbing
// @stuck: none — MATCH (STUB: 3 global stores + byte store + 5 calls in source order)

extern void func_80147084(s32 *a0);
extern void func_80147098(s32 *a0);
extern void func_801470AC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80158880(s32 *param);

void func_80158814(void *arg0) {

    extern s32 D_801F4F30;
    extern s32 D_801F4F3C;
    extern s32 D_801F4F40;
    D_801F4F30 = 0;
    D_801F4F3C = 1;
    D_801F4F40 = 0;
    *(s8 *)((s32)arg0 + 0xA8) = 0;
    ((void (*)(void))func_80147084)();
    ((void (*)(void *))func_80147098)(arg0);
    ((void (*)(void *))func_801470AC)(arg0);
    ((void (*)(void *, s32))func_80147078)(arg0, 0x1A);
    ((void (*)(void *))func_80158880)(arg0);
}



extern void func_80149020(s32 *a0);

void func_80158880(s32 *param) {

    extern void (*D_8018C7A8[])(s32 *);
    func_80149020(param);
    D_8018C7A8[*(u8 *)((s32)param + 0x4F)](param);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801588CC);

DEFINE_func_80158AB4()  /* dedup: shared engine-core @0x80158ab4 (src/shared) */


DEFINE_func_80158AE4()  /* dedup: shared engine-core @0x80158ae4 (src/shared) */



extern void func_80146CA0(void *a0);
extern s32 func_801472C8(struct S *a0);
extern void func_80147324(s32 a0);
extern void func_801474D8(s32 *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);

void func_80158BB0(void *arg0) {

    extern M2C_UNK D_800D58D8;
    extern s32 D_801F4F30;
    if (D_801F4F30 == 0) {
        D_801F4F30 = 1;
    }
    func_80147324(0x456);
    func_80154274(arg0, &D_800D58D8);
    func_80154A74(arg0, 0x16);
    M2C_FIELD(arg0, s32 *, 0x234) = 0xE30000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x10) = 0;
    func_801474EC(arg0);
    func_801474D8(arg0);
    func_801472C8(arg0);
    func_80146CA0(arg0);
}


DEFINE_func_80158C40()  /* dedup: shared engine-core @0x80158c40 (src/shared) */


DEFINE_func_80158CD8()  /* dedup: shared engine-core @0x80158cd8 (src/shared) */


DEFINE_func_80158D60()  /* dedup: shared engine-core @0x80158d60 (src/shared) */


DEFINE_func_80158E24()  /* dedup: shared engine-core @0x80158e24 (src/shared) */



// @class: other
// @stuck: none — MATCH (signed %11 magic + word-array %lo fold; ((void (*)(int))func_80146CA0)(param_1) reuses $a0 for the 0x198 store in its jal delay slot)


extern int rand(void);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_80158F00(int param_1) {

    extern s32 D_801F4F3C;
    extern s32 D_8018C77C[];
    int *self = (int *)param_1;
    struct Actor *act = (struct Actor *)self[0x20 / 4];
    int gate = D_801F4F3C;

    act->timer = (u16)((act->timer + 0x16) & 0xfff);

    if (gate == 0) {
        s32 r = rand();
        *(s32 *)(param_1 + 0x198) = func_8013767C(D_8018C77C[r % 0xb]);
        ((void (*)(int))func_80146CA0)(param_1);
    }
}



// @class: plumbing
// @stuck: none — MATCH (51 ins). Key: func_801594E8 takes a 2nd arg = sVar1 (the (short)func_80159464
//        return). $a1 is set by sra BEFORE the beqz and stays live into the jal, so the value is used
//        twice (branch test + arg2) — that 2nd use is what keeps the sll;sra (gcc folds sll;sra;beqz
//        -> sll;beqz otherwise). Also: branch-polarity invert (!=0 -> 594E8 fall-through, else 767C);
//        func_8013767C arg is &(*(u8 *)&D_80110C3C) (lui%hi+addiu%lo, not a literal). Ghidra missed the 2nd arg.


extern u16 func_80148800(s32 *a0);
extern s32 func_801399F0(s32);
extern void func_80139914(s32);
extern s32 func_80159464(void);
extern void func_801594E8(s32, s32);
extern void func_80146C98(s32 *a0, s16 a1);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_80158FA4(s32 param_1)
{

    extern s32 D_801F4F40;
    extern u8 D_80110C3C[];
    s32 v0;
    s16 sVar1;

    v0 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v0 + 0x12) = (*(u16 *)(v0 + 0x12) + 0x16) & 0xfff;
    if (((s32 (*)(void))func_80148800)() & 0xf0) {
        D_801F4F40 = 1;
    }
    if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
        func_80139914(*(s32 *)(param_1 + 0x198));
        *(s32 *)(param_1 + 0x198) = 0;
        sVar1 = ((s32 (*)(s32))func_80159464)(param_1);
        if (sVar1 != 0) {
            func_801594E8(param_1, sVar1);
            ((void (*)(s32, s32))func_80146C98)(param_1, 0xc);
        } else {
            *(s32 *)(param_1 + 0x198) = ((s32 (*)(u8 *))func_8013767C)(&(*(u8 *)&D_80110C3C));
            ((void (*)(s32))func_80146CA0)(param_1);
        }
    }
}


DEFINE_func_80159070()  /* dedup: shared engine-core @0x80159070 (src/shared) */


DEFINE_func_80159120()  /* dedup: shared engine-core @0x80159120 (src/shared) */


DEFINE_func_801592CC()  /* dedup: shared engine-core @0x801592cc (src/shared) */



extern void func_80145BF8(void);
extern void func_80146CA0(void *a0);

void func_8015934C(void *arg0) {

    extern u8 D_800AE6BD;
    extern s32 D_801F4F30;
    extern s32 D_801F4F38;
    void *temp_v1;

    if (D_801F4F30 == 4) {
        D_801F4F30 = 5;
    }
    if (D_801F4F38 != 0) {
        func_80145BF8();
        func_80146CA0(arg0);
        D_800AE6BD += 1;
    }
    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_v1, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_v1, u16 *, 0x12) + 0x16) & 0xFFF);
}


DEFINE_func_801593E4()  /* dedup: shared engine-core @0x801593e4 (src/shared) */


DEFINE_func_80159404()  /* dedup: shared engine-core @0x80159404 (src/shared) */


DEFINE_func_80159434()  /* dedup: shared engine-core @0x80159434 (src/shared) */



extern s16 currentLocationId;
extern s32 func_80029A94(s32);


s32 func_80159464(void) {

    extern Entry D_8018C7E4[];
    Entry *e;

    e = D_8018C7E4;
    while (e->id != 0) {
        if (currentLocationId == e->id) {
            return e->val;
        }
        e++;
    }
    if (func_80029A94(1) != 0) {
        goto ret0;
    }
    if (func_80029A94(0) != 0) {
        goto ret0;
    }
    return -1;
ret0:
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801594E8);



void func_80159698(void *a0) {

    extern void (*D_8018C9F8[])(void);
    D_8018C9F8[*(u8 *)((s32)a0 + 0x15)]();
}


DEFINE_func_801596D4()  /* dedup: shared engine-core @0x801596d4 (src/shared) */



// @class: iv-combine
// @stuck: none — MATCH (97 ins). Recipe: $s0=base=&(*(u8 *)&D_800AF630) hoisted at top; loop1 = for(p=base+0x65A8;
//   p<base+0x9DA8;p+=0xe) p[1]|=... (the +4 field-offset store folds into the reduced IV -> gcc emits the
//   -4 loop-inversion guard + reuses END for END+4). BOTHER: loop2 needs ab=&D_800AFAE8 POST-guard as a
//   shared base for A=ab+1,B=ab+0x22 -> a for-loop hoists it PRE-guard (fold or perm); the fix is a manual
//   guarded do-while `if(base+0x2A8<base+0x65A8){ ... do{}while(q<inline base+0x65AC);}` with a DISTINCT loop
//   var (q, not p) so loop1's biv-elim survives, an INLINE while-bound (frees the delay slot for the OR
//   const), and the OR const HOISTED to a var declared first so it fills the guard delay slot (a3) and A/B
//   fall into a2/a1. Barrier after the two 0x7fff stores fixes their vs the loop-guard-low ordering.


extern void func_80174B6C(void);
extern void func_80129248(s16 a0);
extern void func_8013C938(void);
extern void func_8013CB20(void);
extern void func_8013C98C(void);
extern void func_8002850C(s32, s32, s32);
extern void func_80028620(s32, void *);


s32 func_801596F0(s32 param_1) {

    extern s16 D_800B9AAC[];
    extern s16 D_800B9B00;
    extern u16 D_801270C0;
    extern u8 D_800AF630[];
    extern u32 D_800AFAE8[];
    extern char D_8018C818[];
    u8 *base = &(*(u8 *)&D_800AF630);
    s32 v;
    u32 *p;
    u32 *q;

    v = *(s32 *)(param_1 + 0x28) - 1;
    *(s32 *)(param_1 + 0x28) = v;
    if (v == -1) {
        func_80174B6C();
        (*(s16 *)&D_800B9AAC) = 0x7fff;
        D_800B9B00 = 0x7fff;

        __asm__ __volatile__("" ::: "memory");

        for (p = (u32 *)(base + 0x65A8); p < (u32 *)(base + 0x9DA8); p += 0xe) {
            p[1] |= 0x80000000;
        }

        if ((u32 *)(base + 0x2A8) < (u32 *)(base + 0x65A8)) {
            u32 orc = 0x80000000;
            u32 *ab = D_800AFAE8;
            q = (u32 *)(base + 0x2AC);
            do {
                if (q < ab + 1 || q >= ab + 0x22) {
                    *q |= orc;
                }
                q += 0x21;
            } while (q < (u32 *)(base + 0x65AC));
        }

        (*(s16 *)&D_801270C0) = 3;
        ((void (*)(s32))func_80129248)(0);
        func_8013C938();
        func_8013CB20();
        func_8013C98C();
        func_8002850C(0x800, 0x800, 0x800);
        func_80028620(0, &(*(u8 *)&D_8018C818));
        func_80028620(1, &(*(u8 *)&D_8018C818) + 0x10);
        func_80028620(2, &(*(u8 *)&D_8018C818) + 0x20);
        *(s32 *)(param_1 + 0x28) = 0xff;
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


DEFINE_func_80159874()  /* dedup: shared engine-core @0x80159874 (src/shared) */


DEFINE_func_8015987C()  /* dedup: shared engine-core @0x8015987c (src/shared) */


DEFINE_func_801598BC()  /* dedup: shared engine-core @0x801598bc (src/shared) */


DEFINE_func_801598E0()  /* dedup: shared engine-core @0x801598e0 (src/shared) */




void func_80159968(void *a0) {

    extern void (*D_8018CA9C[])(void);
    D_8018CA9C[*(u8 *)((s32)a0 + 0x4D)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801599A4);

DEFINE_func_801599E0()  /* dedup: shared engine-core @0x801599e0 (src/shared) */


void func_80159A18(void) {
}

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80159A20);

DEFINE_func_80159B08()  /* dedup: shared engine-core @0x80159b08 (src/shared) */


DEFINE_func_80159B3C()  /* dedup: shared engine-core @0x80159b3c (src/shared) */




void func_80159B70(void *a0) {

    extern void (*D_8018CBF0[])(void);
    D_8018CBF0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80159BAC()  /* dedup: shared engine-core @0x80159bac (src/shared) */



// @class: schedule
// @stuck: none — MATCH (40 ins). Duplicate func_80154A74(arg0,K) into BOTH branch arms (not a
//         single shared-join call): forces gcc to cross-jump the jal while keeping per-arm
//         `addu $a0,$s0` setup + a `nop` join delay slot, matching the 40-ins layout. Branch
//         polarity: write `if (flag & 0x200 != 0){5,0x1C} else {4,0x11}` to get the `beqz`.

extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801553A8(s32 *a0);
extern s32 func_80172590(u8 *a0);
extern void func_80146CA0(void *a0);


void func_80159BE4(s32 arg0)
{

    extern unsigned char D_8018CA0C;
    int v;

    ((void (*)(int, void *))func_80146DB8)(arg0, &D_8018CA0C);
    if ((*(unsigned int *)(arg0 + 0x44) & 0x200) != 0) {
        func_80154150(arg0, 5);
        func_80154A74(arg0, 0x1C);
    } else {
        func_80154150(arg0, 4);
        func_80154A74(arg0, 0x11);
    }
    *(int *)(arg0 + 0x234) = 0;
    *(int *)(arg0 + 0x238) = 0;
    func_801553C0(arg0);
    ((void (*)(int))func_801553A8)(arg0);
    ((void (*)(int))func_80172590)(arg0);
    ((void (*)(int))func_80146CA0)(arg0);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80159C84);

DEFINE_func_8015A1C8()  /* dedup: shared engine-core @0x8015a1c8 (src/shared) */


DEFINE_func_8015A1FC()  /* dedup: shared engine-core @0x8015a1fc (src/shared) */


DEFINE_func_8015A230()  /* dedup: shared engine-core @0x8015a230 (src/shared) */




void func_8015A264(void *a0) {

    extern void (*D_8018CBF8[])(void);
    D_8018CBF8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015A2A0()  /* dedup: shared engine-core @0x8015a2a0 (src/shared) */



// @class: other
// @stuck: none — MATCH (60 ins). switch() gives signed slti pivot; per-case duplicated call gives per-case a0 setup + nop jal delay


extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern s32 func_80172608(u8 *a0);
extern void func_80146CA0(void *a0);

void func_8015A2D8(s32 param_1)
{

    extern int D_8018CA1C;
    unsigned char bVar1;

    ((void (*)(int, int *))func_80146DB8)(param_1, &D_8018CA1C);
    if ((*(unsigned int *)(param_1 + 0x44) & 0x200) != 0) {
        func_80154150(param_1, 10);
        func_80154A74(param_1, 0x1c);
        *(int *)(param_1 + 0x2c) = 0xfffc0000;
        goto LAB_8015a38c;
    }
    bVar1 = *(unsigned char *)(param_1 + 0xa9);
    switch (bVar1) {
    case 0x41:
        func_80154150(param_1, 7);
        break;
    case 0x53:
    case 0x73:
        func_80154150(param_1, 6);
        break;
    default:
        *(int *)(param_1 + 0x23c) = 0;
        goto LAB_8015a390;
    }
    func_80154A74(param_1, 0x21);
LAB_8015a38c:
    *(int *)(param_1 + 0x23c) = 0;
LAB_8015a390:
    func_8014C010(param_1, 2);
    ((void (*)(int))func_801553A8)(param_1);
    ((void (*)(int))func_80172608)(param_1);
    ((void (*)(int))func_80146CA0)(param_1);
    return;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015A3C8);

DEFINE_func_8015AB7C()  /* dedup: shared engine-core @0x8015ab7c (src/shared) */


DEFINE_func_8015ABD4()  /* dedup: shared engine-core @0x8015abd4 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (param held in $s0 across 3 calls; lhu 0x16E; &D_8018CA3C arg)
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80161CD0(s32 a0, s32 a1);

void func_8015AC48(s32 arg0)
{

    extern M2C_UNK D_8018CA3C;
    func_80154150(arg0, 9);
    func_80146DB8((s32 *)arg0, &D_8018CA3C);
    func_80161CD0(arg0, M2C_FIELD(arg0, u16 *, 0x16E));
}


DEFINE_func_8015AC90()  /* dedup: shared engine-core @0x8015ac90 (src/shared) */


DEFINE_func_8015ACC4()  /* dedup: shared engine-core @0x8015acc4 (src/shared) */


DEFINE_func_8015AD08()  /* dedup: shared engine-core @0x8015ad08 (src/shared) */




void func_8015AD3C(void *a0) {

    extern void (*D_8018CC00[])(void);
    D_8018CC00[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015AD78()  /* dedup: shared engine-core @0x8015ad78 (src/shared) */


DEFINE_func_8015ADB0()  /* dedup: shared engine-core @0x8015adb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015AE2C);

DEFINE_func_8015B6F4()  /* dedup: shared engine-core @0x8015b6f4 (src/shared) */


DEFINE_func_8015B7B4()  /* dedup: shared engine-core @0x8015b7b4 (src/shared) */


DEFINE_func_8015B858()  /* dedup: shared engine-core @0x8015b858 (src/shared) */


DEFINE_func_8015B8F8()  /* dedup: shared engine-core @0x8015b8f8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015B950);

DEFINE_func_8015BD8C()  /* dedup: shared engine-core @0x8015bd8c (src/shared) */


DEFINE_func_8015BDD0()  /* dedup: shared engine-core @0x8015bdd0 (src/shared) */


DEFINE_func_8015BE04()  /* dedup: shared engine-core @0x8015be04 (src/shared) */




void func_8015BE38(struct Obj *a0) {

    extern void (*D_8018CC1C[])(void);
    D_8018CC1C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015BE74()  /* dedup: shared engine-core @0x8015be74 (src/shared) */


DEFINE_func_8015BE94()  /* dedup: shared engine-core @0x8015be94 (src/shared) */


DEFINE_func_8015BEC4()  /* dedup: shared engine-core @0x8015bec4 (src/shared) */


DEFINE_func_8015BEE4()  /* dedup: shared engine-core @0x8015bee4 (src/shared) */


DEFINE_func_8015BF04()  /* dedup: shared engine-core @0x8015bf04 (src/shared) */


DEFINE_func_8015BF48()  /* dedup: shared engine-core @0x8015bf48 (src/shared) */


DEFINE_func_8015BF7C()  /* dedup: shared engine-core @0x8015bf7c (src/shared) */


DEFINE_func_8015BFB0()  /* dedup: shared engine-core @0x8015bfb0 (src/shared) */




void func_8015BFF4(void *a0) {

    extern void (*D_8018CC28[])(void);
    D_8018CC28[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015C030);

DEFINE_func_8015C08C()  /* dedup: shared engine-core @0x8015c08c (src/shared) */


DEFINE_func_8015C0C4()  /* dedup: shared engine-core @0x8015c0c4 (src/shared) */


extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80147324(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_80147A84(s32 arg0);
extern int func_80148AFC(void *a0);
extern s32 func_80149FB0(s32 a0);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_8014CC28(s32 a0);
extern void func_8014D738(void);
extern void func_8014F3E8(s32 a0);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);



s32 func_8015C128(s32 param_1) {

    extern u16 D_800B99DA;
    extern void func_8015C6E0(int);
    extern void (*D_8018CAA8[])(int);

    int sp10[3];
    int sp20[3];
    int temp_s0;
    int temp_v0;

    ((void(*)())func_80149FB0)();
    if (((int(*)(int))func_80148AFC)(((int)param_1)) & 0xFF) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = -0x4000;
        ((void(*)(int, int *, int *))func_8001382C)(*(short *)(*(int *)(((int)param_1) + 0x20) + 0x12), sp10, sp20);
        *(int *)(((int)param_1) + 0x234) += sp20[0];
        *(int *)(((int)param_1) + 0x238) += sp20[1];
        *(int *)(((int)param_1) + 0x23C) += sp20[2];
    }
    ((void(*)(int, int *, int *))func_8001382C)((short)(-*(unsigned short *)(*(int *)(((int)param_1) + 0x20) + 0x12)),
                  (int *)(((int)param_1) + 0x234), sp20);
    ((void(*)(int, int *))func_80146DB8)(((int)param_1), sp20);
    func_80147A84(((int)param_1));
    ((void(*)(int))func_801473EC)(((int)param_1));
    if (!(D_800B99DA & 3)) {
        ((void(*)(int, int))func_8014C010)(((int)param_1), 1);
        ((void(*)(int))func_80147324)(0x65F);
    }
    if (((int(*)(int))func_8014D738)(((int)param_1)) != 0) {
        D_8018CAA8[*(u16 *)((int)param_1)](((int)param_1));
        func_8015C6E0(((int)param_1));
        return;
    }
    temp_s0 = ((int(*)(int))func_8014CC28)(((int)param_1));
    temp_v0 = ((int(*)(int))func_8014F3E8)(((int)param_1));
    if (temp_v0 != 0) {
        if ((temp_v0 & 0xFF00) != 0x4000) {
            ((void(*)(int, int))func_80146E90)(((int)param_1), 6);
            ((void(*)(int))func_80146CA0)(((int)param_1));
            return;
        }
        if ((temp_v0 & 0x4000) && ((int(*)(int))func_80146E98)(((int)param_1)) != 0) {
            ((void(*)(int, int))func_80147078)(((int)param_1), 4);
            ((void(*)(int))func_8015C0C4)(((int)param_1));
        }
    } else if (temp_s0 == 0) {
        D_8018CAA8[*(u16 *)((int)param_1)](((int)param_1));
        ((void(*)(int, int))func_80147078)(((int)param_1), 3);
        ((void(*)(int))func_8015BE94)(((int)param_1));
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015C32C);

void func_8015C6A4(void) {
}

DEFINE_func_8015C6AC()  /* dedup: shared engine-core @0x8015c6ac (src/shared) */


DEFINE_func_8015C6E0()  /* dedup: shared engine-core @0x8015c6e0 (src/shared) */




void func_8015C714(void *a0) {

    extern void (*D_8018CC34[])(void);
    D_8018CC34[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015C750()  /* dedup: shared engine-core @0x8015c750 (src/shared) */


DEFINE_func_8015C788()  /* dedup: shared engine-core @0x8015c788 (src/shared) */



// @class: struct
// @stuck: none — MATCH (match_one 88/88); fn-ptr-array dispatch, top-level if/else needed branch-polarity invert (small block falls through, big block at L854)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80149704(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);
extern void func_8014C010(s32 a0, s32 a1);


void func_8015C7E4(u16 *param_1)
{

    extern void (*D_8018CAA8[])(void*);
    extern int D_8018CA4C;
    s32 iVar1;
    u32 uVar2;

    iVar1 = ((s32 (*)(u16 *))func_80161B18)(param_1);
    if ((iVar1 == 0) && (iVar1 = ((s32 (*)(u16 *))func_80161B84)(param_1), iVar1 == 0)) {
        iVar1 = ((s32 (*)(u16 *))func_801496D4)(param_1);
        if (iVar1 != 0) {
            ((void (**)(u16*))D_8018CAA8)[*param_1](param_1);
            ((void (*)(u16 *))func_80149704)(param_1);
        } else {
            uVar2 = ((s32 (*)(u16 *))func_801487F4)(param_1);
            if (((uVar2 & 0x80) == 0) && (iVar1 = ((s32 (*)(u16 *))func_801488A8)(param_1), iVar1 == 0)) {
                ((void (**)(u16*))D_8018CAA8)[*param_1](param_1);
                ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
                ((void (*)(u16 *))func_80159B70)(param_1);
            } else {
                iVar1 = ((s32 (*)(u16 *))func_80161240)(param_1);
                if (iVar1 == 0) {
                    iVar1 = ((s32 (*)(u16 *))func_80146E98)(param_1);
                    if (iVar1 != 0) {
                        ((void (*)(u16 *))func_80148AAC)(param_1);
                        ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_8018CA4C);
                        ((void (*)(u16 *, s32))func_80146E90)(param_1, 0x14);
                        ((void (*)(u16 *))func_80146CA0)(param_1);
                    }
                    if ((param_1[0x5c] & 0x2000) != 0) {
                        ((void (*)(u16 *, s32))func_80161C24)(param_1, param_1[0xb7]);
                        ((void (*)(u16 *, s32))func_8014C010)(param_1, 2);
                    }
                }
            }
        }
    }
    return;
}




// @class: struct
// @stuck: none — dispatch + control flow on a single callee-saved param; expect MATCH

extern s32 func_80149FB0(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);


void func_8015C944(int param_1) {

    extern void (*D_8018CAA8[])();
    func_80149FB0(param_1);
    func_80147AD4(param_1, 0, 0, 0);
    ((void (*)(int))func_801473EC)(param_1);
    ((void (*)(int))func_8014D738)(param_1);
    if (*(int *)(param_1 + 0x170) == 0) {
        (*D_8018CAA8[*(unsigned short *)param_1])(param_1);
        ((void (*)(int, int))func_80147078)(param_1, 0);
        ((void (*)(int))func_80159B70)(param_1);
    } else {
        if (((int (*)(int))func_80161240)(param_1) == 0) {
            if (func_80146E98(param_1) != 0) {
                ((void (*)(int))func_80146CA0)(param_1);
            }
            if ((*(unsigned short *)(param_1 + 0xb8) & 0x2000) != 0) {
                func_80161C24(param_1, *(unsigned short *)(param_1 + 0x16e));
            }
        }
    }
}



// @class: schedule
// @stuck: none — MATCH (goto forces the func_80161240 block to the function tail; bnez-to-end layout vs early-return fall-through)


extern s32 func_80149FB0(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80161240(void *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80149704(void);


void func_8015CA28(u16 *param_1) {

    extern void (*D_8018CAA8[])(void*);
    extern int D_8018CA4C;
    ((void (*)(void))func_80149FB0)();
    if (((int (*)(u16 *))func_80161B18)(param_1) != 0) return;
    if (((int (*)(u16 *))func_80161B84)(param_1) != 0) return;
    if (((int (*)(u16 *))func_801496D4)(param_1) != 0) {
        ((void (**)(u16*))D_8018CAA8)[*param_1](param_1);
        ((void (*)(u16 *))func_80149704)(param_1);
        return;
    }
    if ((((u32 (*)(u16 *))func_801487F4)(param_1) & 0x80) != 0 || ((int (*)(u16 *))func_801488A8)(param_1) != 0) {
        if ((((int (*)(u16 *))func_80148AAC)(param_1) & 0xff) != 0) {
            ((void (*)(u16 *, int, int, int))func_80147AD4)(param_1, 0, 0, 0);
            ((void (*)(u16 *))func_801473EC)(param_1);
        }
        if (((int (*)(u16 *))func_8014D738)(param_1) != 0) {
            ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_8018CA4C);
            ((void (*)(u16 *, int))func_80146E90)(param_1, 0x14);
            ((void (*)(u16 *, int))func_80146C98)(param_1, 2);
        }
        if (*(int *)(param_1 + 0xb8) != 0)
            goto do161240;
    }
    ((void (**)(u16*))D_8018CAA8)[*param_1](param_1);
    ((void (*)(u16 *, int))func_80147078)(param_1, 0);
    ((void (*)(u16 *))func_80159B70)(param_1);
    return;
do161240:
    ((void (*)(u16 *))func_80161240)(param_1);
}


DEFINE_func_8015CB94()  /* dedup: shared engine-core @0x8015cb94 (src/shared) */


void func_8015CBCC(void) {
}

void func_8015CBD4(void) {
}

void func_8015CBDC(void) {
}

void func_8015CBE4(void) {
}

void func_8015CBEC(void) {
}

void func_8015CBF4(void) {
}

void func_8015CBFC(void) {
}

void func_8015CC04(void) {
}

DEFINE_func_8015CC0C()  /* dedup: shared engine-core @0x8015cc0c (src/shared) */


DEFINE_func_8015CC40()  /* dedup: shared engine-core @0x8015cc40 (src/shared) */




void func_8015CC74(s32 *a0) {

    extern void (*D_8018CC44[])(void);
    D_8018CC44[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015CCB0()  /* dedup: shared engine-core @0x8015ccb0 (src/shared) */


DEFINE_func_8015CCD0()  /* dedup: shared engine-core @0x8015ccd0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015CD20);

DEFINE_func_8015CF24()  /* dedup: shared engine-core @0x8015cf24 (src/shared) */


DEFINE_func_8015CF58()  /* dedup: shared engine-core @0x8015cf58 (src/shared) */


DEFINE_func_8015CF8C()  /* dedup: shared engine-core @0x8015cf8c (src/shared) */




void func_8015CFC0(s32 *a0) {

    extern void (*D_8018CC7C[])(void);
    D_8018CC7C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015CFFC()  /* dedup: shared engine-core @0x8015cffc (src/shared) */


extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80154274(s32 *a0, s32 a1);

// @class: regalloc-order
// @stuck: none — MATCH (uVar1 pinned $s3, uVar5 pinned $s1; param_1->s2, iVar4->s0 fall out)


void func_8015D01C(int param_1) {
    extern s32 func_801725F4(u8 *a0);
    extern int D_800D550C;
    extern int D_8018CC6C;

    int iVar4;
    register unsigned short uVar1 __asm__("$19");
    register unsigned short uVar5 __asm__("$17");
    short sVar2;
    short sVar3;

    ((void (*)(int, void *))func_80154274)(param_1, &D_800D550C);
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    iVar4 = *(short *)(*(int *)(param_1 + 0x20) + 0x12);
    uVar1 = *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x180) + 0x20) + 0x12);
    uVar5 = (uVar1 + 0x800) & 0xfff;
    sVar2 = func_80012A60(iVar4, (short)uVar1);
    sVar3 = func_80012A60(iVar4, uVar5);
    if (sVar2 < sVar3) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar1;
    } else {
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar5;
    }
    *(int *)(param_1 + 0x38) = (int)&D_8018CC6C | 0x40000000;
    ((void (*)(int))func_801725F4)(param_1);
    ((void (*)(int))func_80146CA0)(param_1);
}




// @class: struct
// @stuck: none — MATCH (pending gate)

extern s32 func_80149FB0(s32 a0);
extern void func_8014FA04(s32 a0);
extern void func_8014E6A0(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_801725F4(u8 *a0);
extern void func_80146CA0(void *a0);

void func_8015D104(void *arg0) {

    extern void (*D_8018CAA8[])(void *);
    ((void (*)(void))func_80149FB0)();
    ((void (*)(void *))func_8014FA04)(arg0);
    if (((s32 (*)(void *))func_8014E6A0)(arg0) == 0) {
        D_8018CAA8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((void (*)(void *))func_801725F4)(arg0);
        *(s32 *)((u8 *)arg0 + 0x234) = 0xFF1D0000;
        *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10) = 0x600;
        *(u16 *)((u8 *)arg0 + 0x244) = *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10);
        func_80146CA0(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015D1B8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015D380);


// @class: plumbing
// @stuck: none — MATCH


extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_8015D414(int param_1)
{

    extern unsigned char D_8018BDBC[];
    *(unsigned char *)(param_1 + 0x1bd) = 8;
    *(unsigned char **)(param_1 + 0x38) = D_8018BDBC;
    *(short *)(param_1 + 0x138) = 0;
    *(short *)(param_1 + 0x13a) = 0;
    *(short *)(param_1 + 0x13c) = 0;
    *(short *)(param_1 + 0x13e) = 0;
    *(short *)(param_1 + 0xA) = *(short *)(param_1 + 0xA) + 0x48;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    ((void (*)(void))func_801553C0)();
    func_80154A74(param_1, 0x11);
}


DEFINE_func_8015D480()  /* dedup: shared engine-core @0x8015d480 (src/shared) */


DEFINE_func_8015D4B4()  /* dedup: shared engine-core @0x8015d4b4 (src/shared) */




s32 func_8015D4E8(s16 *a0) {

    extern void (*D_8018CCE0[])(void);
    D_8018CCE0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015D524()  /* dedup: shared engine-core @0x8015d524 (src/shared) */


DEFINE_func_8015D544()  /* dedup: shared engine-core @0x8015d544 (src/shared) */


DEFINE_func_8015D57C()  /* dedup: shared engine-core @0x8015d57c (src/shared) */



// @class: loose-typing
// @stuck: none — MATCH (field 0xb8 compared as u16 == 0x8000, not s16 == -0x8000)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80154A74(int, int);
extern s32 func_80161208();
extern void func_80154150(int, int);
extern void func_80146CA0(void *a0);
extern void func_80149374(int, int);


void func_8015D5E8(int param_1)
{

    extern unsigned char D_8018CCEC[];
    int iVar1;
    int iVar2;

    if (((int (*)(void))func_80161B18)() != 0)
        return;
    if (((int (*)(int))func_80161B84)(param_1) != 0)
        return;
    if ((*(unsigned short *)(param_1 + 0xb8) & 0x4000) != 0)
        func_80154A74(param_1, 0x17);
    if (((int (*)(int))func_80161208)(param_1) != 0)
        return;
    if (*(unsigned short *)(param_1 + 0xb8) == 0x8000) {
        *(int *)(param_1 + 0x234) = *(int *)(param_1 + 0x234) + -3;
        func_80154150(param_1, 0x1a);
        ((void (*)(int))func_80146CA0)(param_1);
    } else {
        iVar1 = *(int *)(param_1 + 0x178);
        if (iVar1 != 0) {
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 6) =
                (short)((signed char)D_8018CCEC[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xc));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 10) =
                (short)((signed char)D_8018CCEC[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xe));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 0xe) =
                (short)((signed char)D_8018CCEC[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0x10));
            func_80149374(param_1, iVar1 + 4);
        }
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015D738);

DEFINE_func_8015DA5C()  /* dedup: shared engine-core @0x8015da5c (src/shared) */


DEFINE_func_8015DA90()  /* dedup: shared engine-core @0x8015da90 (src/shared) */


DEFINE_func_8015DAC4()  /* dedup: shared engine-core @0x8015dac4 (src/shared) */




void func_8015DAF8(s32 *a0) {

    extern void (*D_8018CD20[])(void);
    D_8018CD20[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015DB34()  /* dedup: shared engine-core @0x8015db34 (src/shared) */


DEFINE_func_8015DB6C()  /* dedup: shared engine-core @0x8015db6c (src/shared) */


extern void func_8015F89C(void *arg0);
extern void func_8015F9A4(void *arg0);

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015DD74(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015DCB8(s32 a0);

void func_8015DBD4(void *arg0) {

    extern void (*D_8018CAA8[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015DD74)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_8018CAA8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015DCB8)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DC84()  /* dedup: shared engine-core @0x8015dc84 (src/shared) */



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015DCB8(s32 param_1) {

    extern s8 D_8018CD28[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_8018CD28[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_8018CD28[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_8018CD28[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015DD74()  /* dedup: shared engine-core @0x8015dd74 (src/shared) */


DEFINE_func_8015DDF0()  /* dedup: shared engine-core @0x8015ddf0 (src/shared) */


DEFINE_func_8015DE24()  /* dedup: shared engine-core @0x8015de24 (src/shared) */




void func_8015DE58(s32 *a0) {

    extern void (*D_8018CD40[])(void);
    D_8018CD40[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015DE94()  /* dedup: shared engine-core @0x8015de94 (src/shared) */


DEFINE_func_8015DECC()  /* dedup: shared engine-core @0x8015decc (src/shared) */


extern void func_8015F89C(void *arg0);
extern void func_8015F9A4(void *arg0);

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015E0D4(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015E018(s32 a0);

void func_8015DF34(void *arg0) {

    extern void (*D_8018CAA8[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015E0D4)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_8018CAA8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015E018)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DFE4()  /* dedup: shared engine-core @0x8015dfe4 (src/shared) */



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015E018(s32 param_1) {

    extern s8 D_8018CD28[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_8018CD28[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_8018CD28[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_8018CD28[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015E0D4()  /* dedup: shared engine-core @0x8015e0d4 (src/shared) */


DEFINE_func_8015E150()  /* dedup: shared engine-core @0x8015e150 (src/shared) */


DEFINE_func_8015E184()  /* dedup: shared engine-core @0x8015e184 (src/shared) */




s32 func_8015E1B8(s32 a0) {

    extern void (*D_8018CD60[])(void);
    D_8018CD60[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015E1F4()  /* dedup: shared engine-core @0x8015e1f4 (src/shared) */


DEFINE_func_8015E22C()  /* dedup: shared engine-core @0x8015e22c (src/shared) */


DEFINE_func_8015E288()  /* dedup: shared engine-core @0x8015e288 (src/shared) */



// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); fn-ptr table folds %lo via extern array, 0x234 single word store


extern void func_8015E40C(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_80161208();
extern void func_8015E5B0(u8*);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);


void func_8015E344(u16 *param_1)
{

    extern void (*D_8018CAA8[])(void*);
    ((s32 (*)(void))func_8015E40C)();
    if (((s32 (*)(u16 *))func_80161B18)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161B84)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161208)(param_1) == 0) {
        if ((param_1[0x5c] & 0x4000) != 0) {
            ((void (*)(u16 *))func_8015E5B0)(param_1);
            *(s32 *)((char *)param_1 + 0x234) = 1;
        }
        if ((param_1[0x5c] & 0x8000) != 0) {
            ((void (**)(u16*))D_8018CAA8)[param_1[0]](param_1);
            ((s32 (*)(u16 *, s32))func_80147078)(param_1, 0);
            ((s32 (*)(u16 *))func_80159BE4)(param_1);
        }
    }
}


DEFINE_func_8015E40C()  /* dedup: shared engine-core @0x8015e40c (src/shared) */



// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); s16 v[3] array forces all 3 locals addressable (reload-from-stack), u16* psVar1 → lhu null/flag check


extern void func_80149350(s32 arg0);
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8015E4B0(s32 param_1)
{

    extern u16 D_8018CD70;
    extern u16 D_8018CD72;
    extern u16 D_8018CD74;
    extern s32 D_8018CD78;
    u16 *psVar1;
    s16 v[3];
    s32 local_10;

    psVar1 = *(u16 **)(param_1 + 0x18c);
    if ((psVar1 != (u16 *)0) && (*psVar1 != 0)) {
        v[0] = D_8018CD70 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0xc);
        v[1] = D_8018CD72 + *(s16 *)(*(s32 *)(psVar1 + 0x3c) + 0xe) * 2;
        v[2] = D_8018CD74 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0x10);
        ((s32 (*)(s32, s16 *, s16 *))func_80149350)(param_1, &v[0], &v[0]);
        ((s32 (*)(s32 *, s32 *))func_80013E94)(&D_8018CD78, &local_10);
        ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x1f, param_1, v[0], v[1], v[2], local_10, 0);
    }
    return;
}


extern s32 func_8013C9C4(s32 *a0);
void func_8015E588(void) {

    extern s32 D_8018CD80;
    func_8013C9C4(&D_8018CD80);
}


DEFINE_func_8015E5B0()  /* dedup: shared engine-core @0x8015e5b0 (src/shared) */



// @class: struct
// @stuck: none — MATCH (clean -O2 reconstruction; table-of-fnptr indexed by param_1[0])


extern s32 func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);

/* function-pointer dispatch table */

void func_8015E698(u16 *param_1)
{

    extern void (*D_8018CAA8[])(void*);
    if (func_80161208() == 0 && (param_1[0x5c] & 0x8000) != 0) {
        ((void (**)(u16*))D_8018CAA8)[param_1[0]](param_1);
        ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
        ((void (*)(u16 *))func_80159BE4)(param_1);
    }
}


DEFINE_func_8015E714()  /* dedup: shared engine-core @0x8015e714 (src/shared) */


DEFINE_func_8015E84C()  /* dedup: shared engine-core @0x8015e84c (src/shared) */


DEFINE_func_8015E880()  /* dedup: shared engine-core @0x8015e880 (src/shared) */


DEFINE_func_8015E8B4()  /* dedup: shared engine-core @0x8015e8b4 (src/shared) */




void func_8015E8E8(s32 *a0) {

    extern void (*D_8018CD94[])(void);
    D_8018CD94[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015E924()  /* dedup: shared engine-core @0x8015e924 (src/shared) */


DEFINE_func_8015E95C()  /* dedup: shared engine-core @0x8015e95c (src/shared) */


DEFINE_func_8015E9B8()  /* dedup: shared engine-core @0x8015e9b8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015EA3C);

DEFINE_func_8015ED6C()  /* dedup: shared engine-core @0x8015ed6c (src/shared) */


DEFINE_func_8015EDA0()  /* dedup: shared engine-core @0x8015eda0 (src/shared) */


DEFINE_func_8015EDD4()  /* dedup: shared engine-core @0x8015edd4 (src/shared) */




s32 func_8015EE08(s32 a0) {

    extern void (*D_8018CD9C[])(void);
    D_8018CD9C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015EE44()  /* dedup: shared engine-core @0x8015ee44 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (straight STUB call sequence; param saved to $s0 across calls)

extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);


void func_8015EE7C(s32 param_1)
{

    extern int D_800D4C48;
    extern int D_8018CA8C;
    ((int (*)(void))func_8014CBF8)();
    ((int (*)(int))func_801474EC)(param_1);
    ((int (*)(int, void *))func_80154274)(param_1, &D_800D4C48);
    ((int (*)(int, void *))func_80146DB8)(param_1, &D_8018CA8C);
    ((int (*)(int, int))func_801477E8)(param_1, 0xFFF40000);
    ((int (*)(int))func_80146CA0)(param_1);
}




extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161418(void *a0);
extern s32 func_801725A4(u8 *a0);

void func_8015EEE0(void *arg0)
{

    extern void (*D_8018CAA8[])(void *);
    ((void (*)(void *, s32))func_80148038)(arg0, 0x10000);
    ((void (*)(void *))func_80147460)(arg0);
    ((void (*)(void *, s32, s32, s32))func_80147AD4)(arg0, 0, 0, 0x1000);
    ((void (*)(void *))func_801473EC)(arg0);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_8018CAA8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s32))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (((s32 (*)(void *))func_80161418)(arg0) == 0) {
            ((void (*)(void *))func_801725A4)(arg0);
        }
    }
}


void func_8015EF9C(void) {
}

DEFINE_func_8015EFA4()  /* dedup: shared engine-core @0x8015efa4 (src/shared) */


DEFINE_func_8015EFD8()  /* dedup: shared engine-core @0x8015efd8 (src/shared) */




void func_8015F00C(s32 *a0) {

    extern void (*D_8018CDA4[])(void);
    D_8018CDA4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015F048()  /* dedup: shared engine-core @0x8015f048 (src/shared) */


DEFINE_func_8015F080()  /* dedup: shared engine-core @0x8015f080 (src/shared) */


extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8014AB5C(void);
extern void func_80159B70(void *a0);
extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern s32 func_80161208(void);
extern int func_80155FF8(int arg, int a1);

void func_8015F118(void *a0) {

    extern s32 D_80062BE8;
    extern void (*D_8018CAA8[])(void *);
    u16 flag;

    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        (*D_8018CAA8[*(u16 *)a0])(a0);
        ((void (*)(void *, s32))func_80147078)(a0, 0);
        func_80159B70(a0);
    } else {
        if (flag & 0x4000) {
            ((void (*)(s32))func_8014AB5C)(0x19);
            ((void (*)(s32))func_8014AB5C)(0x1D);
            func_801466F0(0x19, (s32)a0, 0, 0, 0, 0, 0, 1);
            func_801466F0(0x19, (s32)a0, 0, 0, 0, 1, 0, 1);
            func_801466F0(0x1D, (s32)a0, 0, 0, 0, 0, 0, 1);
            func_80019064(&D_80062BE8);
            func_80147324(0x9DA);
        }
        if (((s32 (*)(s32 *))func_80161208)(a0) == 0) {
            func_80155FF8((int)a0, *(u8 *)((u8 *)a0 + 0x1AA));
        }
    }
}


DEFINE_func_8015F260()  /* dedup: shared engine-core @0x8015f260 (src/shared) */


DEFINE_func_8015F2BC()  /* dedup: shared engine-core @0x8015f2bc (src/shared) */


DEFINE_func_8015F2F0()  /* dedup: shared engine-core @0x8015f2f0 (src/shared) */




void func_8015F324(s32 *a0) {

    extern void (*D_8018CDAC[])(void);
    D_8018CDAC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015F360()  /* dedup: shared engine-core @0x8015f360 (src/shared) */


DEFINE_func_8015F380()  /* dedup: shared engine-core @0x8015f380 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015F448);

DEFINE_func_8015F738()  /* dedup: shared engine-core @0x8015f738 (src/shared) */


DEFINE_func_8015F76C()  /* dedup: shared engine-core @0x8015f76c (src/shared) */


DEFINE_func_8015F7A0()  /* dedup: shared engine-core @0x8015f7a0 (src/shared) */




s32 func_8015F7D4(s32 a0) {

    extern void (*D_8018CDE4[])(void);
    D_8018CDE4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015F810()  /* dedup: shared engine-core @0x8015f810 (src/shared) */


DEFINE_func_8015F848()  /* dedup: shared engine-core @0x8015f848 (src/shared) */



extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern s32 func_80161208(void);

void func_8015F89C(void *arg0) {

    extern void (*D_8018CAA8[])(void *);
    u16 flags = *(u16 *)((u8 *)arg0 + 0xB8);
    if (!(flags & 0x4000)) {
        if (flags & 0x8000) {
            D_8018CAA8[*(u16 *)arg0](arg0);
            func_80147078(arg0, 0);
            func_80159B70(arg0);
            return;
        }
    } else {
        func_801466F0(1, arg0, 0, -0x1E, 0, 0, 0, 0);
    }
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_8015F948()  /* dedup: shared engine-core @0x8015f948 (src/shared) */



extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208(void);

void func_8015F9A4(void *arg0) {

    extern void (*D_8018CAA8[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_8018CAA8[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015FA24()  /* dedup: shared engine-core @0x8015fa24 (src/shared) */


DEFINE_func_8015FA44()  /* dedup: shared engine-core @0x8015fa44 (src/shared) */


DEFINE_func_8015FA78()  /* dedup: shared engine-core @0x8015fa78 (src/shared) */




void func_8015FAAC(s32 *a0) {

    extern void (*D_8018CDF0[])(void);
    D_8018CDF0[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);
extern void func_8015FBE0(s32 *a0);

void func_8015FAE8(void *arg0) {

    extern void (*D_8018CAA8[])(void *);
    s32 v;

    v = func_801612B8(arg0, 0);
    if (v == 0 || v == 0x8000) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_8018CAA8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 3);
        ((void (*)(void *))func_8015BE94)(arg0);
    } else if ((v & 0x4000) != 0) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_8018CAA8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 4);
        ((void (*)(void *))func_8015C0C4)(arg0);
    } else {
        ((void (*)(void *))func_8015FBE0)(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8015FBE0);

extern void func_801599A4(void *a0);

// @class: struct
// @stuck: none — MATCH (indexed fn-ptr table call + byte-offset struct stores; mirrors sibling func_801599A4 idiom)


extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8015FCC8(void *param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_8018CAA8[])(void *);
    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_8018CAA8[*(u16 *)param_1](param_1);
        ((void (*)(void *, s32))func_80147078)(param_1, 0);
        func_80159B70(param_1);
    } else {
        *(u8 *)((s32)param_1 + 0x197) = 0;
        *(u8 *)((s32)param_1 + 0xBE) = 0;
        *(u8 *)((s32)param_1 + 0xBF) = 0;
        *(u8 *)((s32)param_1 + 0x1A0) = (u8)*(s32 *)((s32)param_1 + 0x184);
        ((s32 (*)(void *, s32))func_8014BFF4)(param_1, 1);
        func_80146CA0(param_1);
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple 3-call sequence with global table index


extern void func_80147324(s32 arg0);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_8015FD74(int param_1)
{

    extern unsigned int D_8018CE04[];
    ((int (*)(int))func_80147324)(0x18);
    *(int *)(param_1 + 0x198) = func_8013767C(D_8018CE04[*(unsigned char *)(param_1 + 0x1a0)]);
    ((int (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_8015FDCC()  /* dedup: shared engine-core @0x8015fdcc (src/shared) */



// @class: struct
// @stuck: none — MATCH expected (fn-ptr-table dispatch + ushort struct fields)


extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80161208();

void func_8015FE70(u16 *param_1)
{

    extern void (*D_8018CAA8[])(void*);
    if ((param_1[0x5c] & 0x8000) != 0) {
        if (param_1[0x5d] == 0) {
            ((void (**)())D_8018CAA8)[param_1[0]]();
            ((void (*)(u16 *, s16))func_80147078)(param_1, 0);
            ((void (*)(u16 *))func_80159B70)(param_1);
            return;
        }
        param_1[0x5c] = param_1[0x5d];
    }
    if ((param_1[0x5c] & 0x4000) != 0) {
        ((void (*)(u16 *, s16))func_80154A74)(param_1, 0x11);
    }
    ((void (*)(u16 *))func_80161208)(param_1);
}




extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern u8 func_801656E8(s32 a0, s32 a1);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80165670(s32 a0, s32 a1);
extern void func_80165840(void);
extern void func_801658DC(void);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8016004C(s32 a0);

void func_8015FF20(void *param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_8018CAA8[])(void *);
    extern u8 D_80078EC1;
    extern u8 D_80078EC2;
    extern u16 D_801270C0;
    s32 v2;
    u8 cur;

    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_8018CAA8[*(u16 *)param_1](param_1);
        ((void (*)(void *, s16))func_80147078)(param_1, 0);
        func_80159B70(param_1);
        return;
    }

    v2 = *(s32 *)((s32)param_1 + 0x184);
    if (v2 < 0) {
        func_80150820((s32)param_1, func_801656E8((s32)param_1, v2 & 0xFF) & 0xFF);
    } else {
        if (*(u8 *)((s32)param_1 + 0x1A0) != *(u8 *)((s32)param_1 + 0x196)) {
            *(u8 *)((s32)param_1 + 0x1A0) = (u8)v2;
            *(u8 *)((s32)param_1 + 0x197) = 0;
            *(u8 *)((s32)param_1 + 0xBE) = 0;
            *(u8 *)((s32)param_1 + 0xBF) = 0;
            func_8014BFF4((s32)param_1, 1);
        }

        cur = *(u8 *)((s32)param_1 + 0x1A0);
        D_80078EC1 = cur;
        D_80078EC2 = cur;
        func_80165670((s32)param_1, cur);
        ((void (*)(void *))func_80165840)(param_1);
        ((void (*)(void *))func_801658DC)(param_1);
        func_80154A74((s32)param_1, 0x11);
        D_801270C0 = 1;
    }

    ((void (*)(void *))func_8016004C)(param_1);
}


DEFINE_func_8016004C()  /* dedup: shared engine-core @0x8016004c (src/shared) */


DEFINE_func_8016007C()  /* dedup: shared engine-core @0x8016007c (src/shared) */


DEFINE_func_801600D0()  /* dedup: shared engine-core @0x801600d0 (src/shared) */


DEFINE_func_80160104()  /* dedup: shared engine-core @0x80160104 (src/shared) */




void func_80160138(s32 *a0) {

    extern void (*D_8018CE80[])(void);
    D_8018CE80[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160174()  /* dedup: shared engine-core @0x80160174 (src/shared) */


DEFINE_func_801601AC()  /* dedup: shared engine-core @0x801601ac (src/shared) */


DEFINE_func_801601E4()  /* dedup: shared engine-core @0x801601e4 (src/shared) */


DEFINE_func_80160244()  /* dedup: shared engine-core @0x80160244 (src/shared) */



extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_801602A4(s32 *a0) {

    extern void (*D_8018CAA8[])(void*);
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        ((void (**)())D_8018CAA8)[*(u16 *)a0]();
        func_80154A74((s32)a0, 0x11);
        ((void (*)(s32, s32))func_80147078)((s32)a0, 0);
        func_80159B70(a0);
    } else {
        ((s32 (*)(s32 *))func_80161208)(a0);
    }
}


void func_8016032C(void) {
}

DEFINE_func_80160334()  /* dedup: shared engine-core @0x80160334 (src/shared) */


DEFINE_func_80160368()  /* dedup: shared engine-core @0x80160368 (src/shared) */




void func_8016039C(s32 *a0) {

    extern void (*D_8018CE90[])(void);
    D_8018CE90[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801603D8()  /* dedup: shared engine-core @0x801603d8 (src/shared) */


DEFINE_func_80160410()  /* dedup: shared engine-core @0x80160410 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80160534);

DEFINE_func_801607B8()  /* dedup: shared engine-core @0x801607b8 (src/shared) */


DEFINE_func_801607E4()  /* dedup: shared engine-core @0x801607e4 (src/shared) */


DEFINE_func_80160818()  /* dedup: shared engine-core @0x80160818 (src/shared) */




void func_8016084C(s32 *a0) {

    extern void (*D_8018CE98[])(void);
    D_8018CE98[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160888()  /* dedup: shared engine-core @0x80160888 (src/shared) */


DEFINE_func_801608C0()  /* dedup: shared engine-core @0x801608c0 (src/shared) */



// @class: struct
// @stuck: none — MATCH (function-pointer table folds %lo via extern array indexed by halfword)

typedef void (*code)(unsigned short *);


extern u16 func_801487F4(s32 *a0);
extern s32 func_80161208();
extern void func_80160A74(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_80160920(unsigned short *param_1)
{

    extern void (*D_8018CAA8[])(void*);
    if ((((int (*)(void))func_801487F4)() & 8) == 0) {
        ((code *)D_8018CAA8)[*param_1](param_1);
        ((void (*)(unsigned short *))func_80160A74)(param_1);
    } else {
        if (((int (*)(unsigned short *))func_80161208)(param_1) == 0 && param_1[0x5c] == 0x8000) {
            ((void (*)(unsigned short *, int))func_80154150)(param_1, 0x25);
            ((void (*)(unsigned short *))func_80146CA0)(param_1);
        }
    }
    return;
}




// @class: struct
// @stuck: none — MATCH (pending byte-gate); function-pointer table %lo-fold via extern array


extern u16 func_801487F4(s32 *a0);
extern void func_80160A74(s32 *a0);
extern s32 func_80161208();

/* function-pointer dispatch table; indexed by *param_1 (×4 = ptr size) */

void func_801609B8(u16 *param_1) {

    extern void (*D_8018CAA8[])(void*);
    if ((((u32 (*)(void))func_801487F4)() & 8) == 0) {
        ((void (**)(u16*))D_8018CAA8)[*param_1](param_1);
        ((void (*)(u16 *))func_80160A74)(param_1);
    } else {
        ((void (*)(u16 *))func_80161208)(param_1);
    }
}


DEFINE_func_80160A28()  /* dedup: shared engine-core @0x80160a28 (src/shared) */


DEFINE_func_80160A74()  /* dedup: shared engine-core @0x80160a74 (src/shared) */


DEFINE_func_80160ACC()  /* dedup: shared engine-core @0x80160acc (src/shared) */


DEFINE_func_80160B00()  /* dedup: shared engine-core @0x80160b00 (src/shared) */




s32 func_80160B34(s32 a0) {

    extern void (*D_8018CEA4[])(void);
    D_8018CEA4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160B70()  /* dedup: shared engine-core @0x80160b70 (src/shared) */


DEFINE_func_80160BB4()  /* dedup: shared engine-core @0x80160bb4 (src/shared) */


DEFINE_func_80160C28()  /* dedup: shared engine-core @0x80160c28 (src/shared) */


DEFINE_func_80160CB4()  /* dedup: shared engine-core @0x80160cb4 (src/shared) */


extern void func_8015DBD4(void *arg0);

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015DBD4 in same overlay; dispatch via D_8018CAA8 + func_80147078/func_80159B70 tail, func_80161208 else)

extern u16 func_80148800(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_80160D10(void *arg0) {

    extern void (*D_8018CAA8[])(void *);
    if (*(u32 *)((u8 *)arg0 + 0x44) & 0x10) {
        D_8018CAA8[*(u16 *)arg0](arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x1AC) == 0) {
            if ((((s32 (*)(void *))func_80148800)(arg0) & 0xF0) == 0) {
                goto dd0;
            }
        } else {
            s32 t = *(s32 *)((u8 *)arg0 + 0x1AC) - 0xAAA8;
            *(s32 *)((u8 *)arg0 + 0x1AC) = t;
            if (t >= 0) {
                goto dd0;
            }
        }
        D_8018CAA8[*(u16 *)arg0](arg0);
    }
    ((void (*)(void *, s16))func_80147078)(arg0, 0);
    func_80159B70(arg0);
    return;
dd0:
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_80160DEC()  /* dedup: shared engine-core @0x80160dec (src/shared) */


DEFINE_func_80160E3C()  /* dedup: shared engine-core @0x80160e3c (src/shared) */


DEFINE_func_80160E70()  /* dedup: shared engine-core @0x80160e70 (src/shared) */




void func_80160EA4(void *a0) {

    extern void (*D_8018CEB4[])(void);
    D_8018CEB4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160EE0()  /* dedup: shared engine-core @0x80160ee0 (src/shared) */


DEFINE_func_80160F00()  /* dedup: shared engine-core @0x80160f00 (src/shared) */


DEFINE_func_80160F70()  /* dedup: shared engine-core @0x80160f70 (src/shared) */


DEFINE_func_80160FE0()  /* dedup: shared engine-core @0x80160fe0 (src/shared) */



// @class: struct
// @stuck: none — MATCH

extern void func_80149020(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);

void func_80161034(void *a0)
{

    extern void (*D_8018CAA8[])(void *);
    func_80149020(a0);
    D_8018CAA8[*(u16 *)a0](a0);
    func_80147078(a0, 0);
    func_80159B70(a0);
}


DEFINE_func_80161094()  /* dedup: shared engine-core @0x80161094 (src/shared) */


void func_801610FC(void) {
}

DEFINE_func_80161104()  /* dedup: shared engine-core @0x80161104 (src/shared) */


DEFINE_func_80161124()  /* dedup: shared engine-core @0x80161124 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80161208);

DEFINE_func_80161240()  /* dedup: shared engine-core @0x80161240 (src/shared) */


DEFINE_func_80161278()  /* dedup: shared engine-core @0x80161278 (src/shared) */


DEFINE_func_801612B8()  /* dedup: shared engine-core @0x801612b8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016130C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80161374);

DEFINE_func_80161418()  /* dedup: shared engine-core @0x80161418 (src/shared) */


DEFINE_func_80161450()  /* dedup: shared engine-core @0x80161450 (src/shared) */


DEFINE_func_80161488()  /* dedup: shared engine-core @0x80161488 (src/shared) */


DEFINE_func_801614E4()  /* dedup: shared engine-core @0x801614e4 (src/shared) */


DEFINE_func_8016151C()  /* dedup: shared engine-core @0x8016151c (src/shared) */


DEFINE_func_80161554()  /* dedup: shared engine-core @0x80161554 (src/shared) */


DEFINE_func_8016158C()  /* dedup: shared engine-core @0x8016158c (src/shared) */


DEFINE_func_801615C4()  /* dedup: shared engine-core @0x801615c4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016163C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80161774);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80161888);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016191C);

DEFINE_func_8016197C()  /* dedup: shared engine-core @0x8016197c (src/shared) */


DEFINE_func_801619A4()  /* dedup: shared engine-core @0x801619a4 (src/shared) */


DEFINE_func_801619D0()  /* dedup: shared engine-core @0x801619d0 (src/shared) */


DEFINE_func_80161A00()  /* dedup: shared engine-core @0x80161a00 (src/shared) */


DEFINE_func_80161A30()  /* dedup: shared engine-core @0x80161a30 (src/shared) */


DEFINE_func_80161A60()  /* dedup: shared engine-core @0x80161a60 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80161A90);

DEFINE_func_80161B18()  /* dedup: shared engine-core @0x80161b18 (src/shared) */


DEFINE_func_80161B84()  /* dedup: shared engine-core @0x80161b84 (src/shared) */


DEFINE_func_80161BE0()  /* dedup: shared engine-core @0x80161be0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80161C24);


// @class: struct
// @stuck: none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

extern void func_80147324(s32 arg0);

void func_80161C98(int param_1, u32 param_2)
{

    extern u16 D_8018CEE4[];
    if (param_2 < 8) {
        func_80147324(D_8018CEE4[param_2]);
    }
    return;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80161CD0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80161D20);

DEFINE_func_80161D58()  /* dedup: shared engine-core @0x80161d58 (src/shared) */



// @class: other
// @stuck: none — MATCH (short-circuit && chain; reused 0x80FFFFFF mask const, andi-0xFF on callee ret)

extern s32 func_80029178(s32 arg);
extern void func_80029124(s32, s32);
extern void func_800D1734(void *);

void func_80161D88(void) {

    extern s32 D_800AE6B0;
    extern s32 D_800AE6A8;
    extern s32 D_8018CF48;
    if ((D_800AE6B0 & 0x80FFFFFF) == 0 && (D_800AE6A8 & 0x80FFFFFF) == 0 &&
        (func_80029178(0x141) & 0xFF) != 0) {
        func_80029124(0x141, 0);
        func_80029124(0x95, 1);
        func_800D1734(&D_8018CF48);
    }
}


extern s32 func_800291DC(s32);







void func_80161E08(s32 param_1) {

    extern u8 D_800AF630[];
    extern void func_80024054(void *a0, void *a1);
    extern void func_8001CE28(void *a0, void *a1);
    extern void func_800242D0(s32 a0, void *a1, s32 a2);
    extern void func_8001CE68(void *a0, void *a1);
    extern int func_801620C4(void);
    extern void func_801622C4(void);
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_80078EB0;
    extern u16 D_800B5BD8;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern u16 D_800B5C10;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern u16 D_800B5C48;
    extern s16 D_800B5C74;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern u8 * D_801F4F48[];
    extern u8 D_8018CF14[];
    extern u8 D_8018CF34[];
    extern u8 D_801F4F54[];
    extern u8 D_801F4F7C[];
    extern u8 D_801F4F94[];

    u8 *base = &(*(u8 *)&D_800AF630);
    u8 *p;
    s32 a2;

    if (*((u16 *)param_1) != 0x1A &&
        currentLocationId != 0x3012 &&
        currentLocationId != 0x3054 &&
        currentLocationId != 0x3079 &&
        currentLocationId != 0x3096 &&
        ((a2 = func_800291DC(8)) & 0x8000) != 0) {

        if (D_800B5BD8 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65A8));
            D_801F4F48[0] = p;
            func_80024054(&D_8018CF14, &D_801F4F54);
            func_8001CE28(p, &D_801F4F54);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -(s32)(u16)D_800AF7BE / 2 + 0x28;
        }

        if (D_800B5C10 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65E0));
            D_801F4F48[1] = p;
            func_80024054(&D_8018CF34, &D_801F4F7C);
            func_8001CE28(p, &D_801F4F7C);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -(s32)(u16)D_800AF7BE / 2 + 0x30;
        }

        if (D_800B5C48 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x6618));
            D_801F4F48[2] = p;
            func_800242D0((s16)func_801620C4(), &D_801F4F94, 0x84);
            func_8001CE68(p, &D_801F4F94);
            D_800B5C74 = 1;
            D_800B5C50 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -(s32)(u16)D_800AF7BE / 2 + 0x10;
        }

        func_800242D0((s16)func_801620C4(), &D_801F4F94, 0x84);
        if ((a2 & 0x7FFF) == (s32)D_80078EB0) {
            func_801622C4();
        }
    }
}


DEFINE_func_801620C4()  /* dedup: shared engine-core @0x801620c4 (src/shared) */


DEFINE_func_80162120()  /* dedup: shared engine-core @0x80162120 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_8016216C(void)
{

    extern int D_801F4F48[];
    int *p;
    int i;

    func_800291C8(8, 0);
    i = 0;
    p = D_801F4F48;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}



extern s32 func_800291DC(s32);

s32 func_801621CC(s32 arg0) {

    extern u8 D_80078E78[];
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    extern s32 D_8018CF48;
    register s32 s0 __asm__("$16") = arg0;       /* $s0: arg0, crosses the call */
    register u8 *s1 __asm__("$17") = D_80078E78; /* $s1: base, hoisted for the loop */
    register s32 i __asm__("$5");                /* $a1: counter (pin fixes the i/d swap) */
    u32 a2;
    s32 d;                                       /* $a0: natural alloc; load via $v0 temp */
    s32 v, last, hi, lo;
    char pad[8];                                 /* phantom 8B local -> frame 0x28 (vars=8) */

    a2 = func_800291DC(8);
    if ((a2 & 0x8000) == 0) {
        return 0;
    }
    a2 &= 0x7FFF;
    if (((a2 >> 8) == D_80078EB1) && ((a2 & 0xFF) <= (u32)D_80078EB0)) {
        return (s32)&D_8018CF48;
    }
    d = s1[0x39] - 1;
    i = 0;
    if (s0 <= 0) {
        return 0;
    }
    hi = (a2 >> 8) & 0xFF;
    last = s0 - 1;
    lo = a2 & 0xFF;
    do {
        if ((s8)d < 0) {
            d = 0x17;
        }
        v = (s8)d;
        if (hi == v) {
            if (i != last) {
                return (s32)&D_8018CF48;
            }
            i++;
            if ((u32)s1[0x38] < (u32)lo) {
                return (s32)&D_8018CF48;
            }
            goto bot;
        }
        i++;
    bot:
        d--;
    } while (i < s0);
    return 0;
}



// @class: schedule
// @stuck: none — MATCH
extern void func_80029124(s32, s32);
extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

void func_801622C4(void)
{

    extern int D_801F4F48[];
    int *p;
    int i;

    ((int (*)(int, int))func_80029124)(0x141, 1);
    ((int (*)(int, int))func_800291C8)(8, 0);
    i = 0;
    p = &D_801F4F48;
    do {
        ((int (*)(int, int))func_80016714)(*p, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}




void func_80162330(void *a0) {

    extern void (*D_8018CF6C[])(void);
    D_8018CF6C[*(u8 *)((s32)a0 + 0x15)]();
}


DEFINE_func_8016236C()  /* dedup: shared engine-core @0x8016236c (src/shared) */


DEFINE_func_801623B8()  /* dedup: shared engine-core @0x801623b8 (src/shared) */


DEFINE_func_80162414()  /* dedup: shared engine-core @0x80162414 (src/shared) */


extern s32 func_800291DC(s32);








s32 func_80162438(s32 _unused0) {

    extern s16 D_80078EB0;
    extern u8 D_800AF630[];
    extern void func_80024054(void *, void *);
    extern void func_8001CE28(void *, void *);
    extern void func_8001CE68(void *, void *);
    extern void func_800242D0(s32, void *, s32);
    extern s32 func_801626B8(void);
    extern void func_80162760(void);
    extern u8 D_8018CF78[];
    extern s32 D_8018CF90;
    extern u8 D_801F4FAC[];
    extern u8 D_801F4FD4[];
    extern u8 D_801F4FF0[];
    extern int D_801F4FA0[];
    extern u16 D_800B5BD8;
    extern u16 D_800B5C10;
    extern u16 D_800B5C48;
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern s16 D_800B5C74;

    u32 uVar2;
    register u8 *base __asm__("$18");
    register u8 *item __asm__("$17");

    base = &(*(u8 *)&D_800AF630);
    uVar2 = func_800291DC(0x12);
    if ((uVar2 & 0x8000) != 0) {
        if (D_800B5BD8 == 0) {
            register u8 *t __asm__("$2") = base + 0x65A8;
            item = t;
            D_801F4FA0[0] = (s32)item;
            func_80024054(D_8018CF78, D_801F4FAC);
            func_8001CE28(item, D_801F4FAC);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -D_800AF7BE / 2 + 0x28;
        }
        if (D_800B5C10 == 0) {
            register u8 *t __asm__("$2") = base + 0x65E0;
            item = t;
            D_801F4FA0[1] = (s32)item;
            func_80024054(((u8 *)&D_8018CF90), D_801F4FD4);
            func_8001CE28(item, D_801F4FD4);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -D_800AF7BE / 2 + 0x30;
        }
        if (D_800B5C48 == 0) {
            register u8 *t __asm__("$2") = base + 0x6618;
            item = t;
            D_801F4FA0[2] = (s32)item;
            func_800242D0((s16)func_801626B8(), D_801F4FF0, 0x84);
            func_8001CE68(item, D_801F4FF0);
            D_800B5C74 = 1;
            D_800B5C50 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -D_800AF7BE / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_801F4FF0, 0x84);
        if ((uVar2 & 0x7FFF) == (s32)(*(s16 *)&D_80078EB0)) {
            func_80162760();
        }
    }
}


DEFINE_func_801626B8()  /* dedup: shared engine-core @0x801626b8 (src/shared) */


DEFINE_func_80162714()  /* dedup: shared engine-core @0x80162714 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_80162760(void)
{

    extern int D_801F4FA0[];
    int *p;
    int i;

    func_800291C8(18, 0);
    i = 0;
    p = D_801F4FA0;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}


DEFINE_func_801627C0()  /* dedup: shared engine-core @0x801627c0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801627E8);



void func_80162834(void *a0) {

    extern void (*D_8018CFB4[])(void);
    D_8018CFB4[*(u8 *)((s32)a0 + 0x1)]();
}



// @class: plumbing
// @stuck: none — MATCH (stub: alloc + global init + two calls; $s0 holds param_1 across calls)

extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);


void func_80162870(s32 param_1) {

    extern u8 D_800B5CB8;
    extern s32 D_8018CFA4;
    extern s32 D_800B5CBC;
    extern u8 D_800B5CDF;
    extern s32 D_800B5CEC;
    *(s32 *)(param_1 + 8) = (s32)&D_800B5CB8;
    func_8001CB6C(&D_800B5CB8, (s32)&D_8018CFA4, 0x250, 0x1A0);
    D_800B5CEC = param_1 + 0xC;
    D_800B5CDF = 0x14;
    D_800B5CBC |= 0x60000000;
    func_80162968(param_1);
    func_80162ACC((u8 *)param_1);
}


DEFINE_func_801628F4()  /* dedup: shared engine-core @0x801628f4 (src/shared) */


DEFINE_func_80162968()  /* dedup: shared engine-core @0x80162968 (src/shared) */


DEFINE_func_80162AC0()  /* dedup: shared engine-core @0x80162ac0 (src/shared) */


DEFINE_func_80162ACC()  /* dedup: shared engine-core @0x80162acc (src/shared) */


DEFINE_func_80162AE0()  /* dedup: shared engine-core @0x80162ae0 (src/shared) */


DEFINE_func_80162AF4()  /* dedup: shared engine-core @0x80162af4 (src/shared) */


DEFINE_func_80162B1C()  /* dedup: shared engine-core @0x80162b1c (src/shared) */


void func_80162CC4(void) {
}

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80162CCC);

DEFINE_func_80162D28()  /* dedup: shared engine-core @0x80162d28 (src/shared) */


DEFINE_func_80162D88()  /* dedup: shared engine-core @0x80162d88 (src/shared) */


DEFINE_func_80162DE8()  /* dedup: shared engine-core @0x80162de8 (src/shared) */


DEFINE_func_80162E48()  /* dedup: shared engine-core @0x80162e48 (src/shared) */


DEFINE_func_80162EA8()  /* dedup: shared engine-core @0x80162ea8 (src/shared) */


DEFINE_func_80162F08()  /* dedup: shared engine-core @0x80162f08 (src/shared) */


DEFINE_func_80162F60()  /* dedup: shared engine-core @0x80162f60 (src/shared) */


DEFINE_func_80162F80()  /* dedup: shared engine-core @0x80162f80 (src/shared) */


DEFINE_func_80162FA0()  /* dedup: shared engine-core @0x80162fa0 (src/shared) */


DEFINE_func_80162FC0()  /* dedup: shared engine-core @0x80162fc0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80162FF4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801630C4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80163194);

DEFINE_func_80163234()  /* dedup: shared engine-core @0x80163234 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016325C);

DEFINE_func_801632E0()  /* dedup: shared engine-core @0x801632e0 (src/shared) */


DEFINE_func_801632F0()  /* dedup: shared engine-core @0x801632f0 (src/shared) */


DEFINE_func_80163328()  /* dedup: shared engine-core @0x80163328 (src/shared) */


DEFINE_func_801633A8()  /* dedup: shared engine-core @0x801633a8 (src/shared) */



// @class: struct
// @stuck: none — MATCH (21 ins, relocation-masked)


s32 func_80163408(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {
    extern int func_8016345C(int, unsigned short, int, unsigned short, void *);
    extern unsigned char D_801F478C[8];

    unsigned char sp18[8];
    memcpy(sp18, D_801F478C, 8);
    return func_8016345C(((int)param_1), ((int)param_2), ((int)param_3), ((int)param_4), sp18);
}


DEFINE_func_8016345C()  /* dedup: shared engine-core @0x8016345c (src/shared) */



// @class: struct
// @stuck: none — MATCH (unaligned 8-byte memcpy from global into stack buffer, then forward to callee)


extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5)
{

    extern char D_801F478C[8];
    char buf[8];

    memcpy(buf, D_801F478C, 8);
    ((void (*)(s32, u16, u16, s32, u16, s32))func_80163534)(param_1, param_2, param_3, param_4, param_5, (s32)buf);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80163534);

DEFINE_func_80163664()  /* dedup: shared engine-core @0x80163664 (src/shared) */


DEFINE_func_801636D0()  /* dedup: shared engine-core @0x801636d0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80163764);

DEFINE_func_8016380C()  /* dedup: shared engine-core @0x8016380c (src/shared) */


DEFINE_func_801638A0()  /* dedup: shared engine-core @0x801638a0 (src/shared) */


DEFINE_func_80163950()  /* dedup: shared engine-core @0x80163950 (src/shared) */




void func_80163A58(void *a0) {

    extern void (*D_8018CFBC[])(void);
    D_8018CFBC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80163A94()  /* dedup: shared engine-core @0x80163a94 (src/shared) */


DEFINE_func_80163C2C()  /* dedup: shared engine-core @0x80163c2c (src/shared) */


extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern u16 func_80148800(s32 *a0);
extern void func_80149350(s32 arg0);
extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3);
extern s32 func_8014CA00(s32 a0);
extern u16 func_80156370(u16 a0);
extern void func_80162D88(s32 *a0);

void func_80163EC8(s32 param_1) {
    extern Blk8 D_801F4794;
    extern u16 D_800B99DA;
    extern u8 func_801656D0(s32 a0, s32 a1);
    extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80015978(s32 a0, s32 *a1);
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);

    Blk8 in;
    u16 out[4];
    s16 buf[4];
    s32 psVar6;
    s32 iVar8;
    s32 iVar7;
    register s32 uVar5 __asm__("$2");   /* PIN (flagged): uVar5 -> $v0 */
    u16 uVar4;
    u8 uVar3;

    in = D_801F4794;
    psVar6 = *(s32 *)(param_1 + 0x4c);
    iVar8 = *(s32 *)(param_1 + 0x20);
    func_80162D88((s32 *)param_1);

    if (*(s32 *)(psVar6 + 0x184) == 0) {
        uVar5 = *(s32 *)(psVar6 + 0x44);
        *(s16 *)(psVar6 + 0x18a) = 0;
        *(s16 *)(psVar6 + 0x188) = 0;
        *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
        func_80146CA0((void *)param_1);
        func_80146CA0((void *)param_1);
        return;
    }
    if (*(s16 *)(*(s32 *)(psVar6 + 0x184) + 0x36) == *(u16 *)(psVar6 + 0x194)) {
        goto LAB_matched;
    }
    *(s32 *)(psVar6 + 0x184) = 0;
    uVar5 = *(s32 *)(psVar6 + 0x44);
    *(s16 *)(psVar6 + 0x18a) = 0;
    *(s16 *)(psVar6 + 0x188) = 0;
    *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);
    return;

LAB_matched:
    *(s16 *)(psVar6 + 0x18a) = *(u16 *)(psVar6 + 0x18a) + 1;
    if ((D_800B99DA & 3) == 0) {
        if (*(s16 *)(psVar6 + 0x188) >= *(u8 *)(param_1 + 0x67)) {
            *(s16 *)(psVar6 + 0x188) = *(s16 *)(psVar6 + 0x188) - *(u8 *)(param_1 + 0x67);
        } else {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
        if (*(s16 *)(psVar6 + 0x188) < 0) {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
    }

    *(s16 *)(param_1 + 0x66) = *(u16 *)(param_1 + 0x66) + 0x40;
    uVar5 = func_80148800((s32 *)psVar6);
    if ((uVar5 & 0x80) != 0) {
        *(s16 *)(param_1 + 0x66) = 0;
        uVar3 = func_801656D0(psVar6, func_8014CA00(*(s32 *)(psVar6 + 0x184)) & 0xff);
        *(s16 *)(psVar6 + 0x188) = *(u16 *)(psVar6 + 0x188) + uVar3;
        *(s16 *)(iVar8 + 0x1a) = 0x4000;
        *(s16 *)(iVar8 + 0x18) = 0x4000;
        *(s32 *)(iVar8 + 0x48) = *(s16 *)(param_1 + 0x58);
        *(s32 *)(iVar8 + 0x4c) = *(s16 *)(param_1 + 0x5a);
        *(s32 *)(iVar8 + 0x50) = *(s16 *)(param_1 + 0x5c);
        ((void (*)(s32, s32, s32))func_80149350)(param_1, (s32)&in, (s32)out);
        *(s16 *)(param_1 + 0x6) = out[0];
        *(s16 *)(param_1 + 0xa) = out[1];
        *(s16 *)(param_1 + 0xe) = out[2];
    }

    if (0x80 < *(s16 *)(psVar6 + 0x188)) {
        *(s16 *)(psVar6 + 0x188) = 0x80;
    }
    if (*(s16 *)(psVar6 + 0x188) >= 0x80) {
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0xe);
            func_8014C4AC(iVar7, 0xe, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            func_80146994(0x33, param_1, 0, iVar7);
        }
    } else {
        if (*(s16 *)(psVar6 + 0x18a) < 0x80 && *(u16 *)psVar6 != 0x19) {
            goto LAB_end;
        }
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0x21);
            func_8014C4AC(iVar7, 0x21, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            if ((*(s32 *)(iVar7 + 0xb4) & 0x40000) != 0) {
                func_8014AD30(param_1, (u16 *)buf, 0, *(s16 *)(iVar7 + 0x60));
            }
        }
    }

    uVar5 = func_8014CA00(iVar7);
    *(s32 *)(psVar6 + 0x184) = uVar5;
    if (0x1e < (u32)uVar5) {
        *(s32 *)(psVar6 + 0x184) = 0;
    }
    func_80146E90((s32 *)param_1, 0x20);
    *(s32 *)(psVar6 + 0x44) = *(s32 *)(psVar6 + 0x44) & ~0x20;
    func_80147324(0x449);
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);

LAB_end:
    uVar4 = func_80012F74(*(s16 *)(iVar8 + 0x1a), 0x1800, 3, 1);
    *(s16 *)(iVar8 + 0x1a) = uVar4;
    *(s16 *)(iVar8 + 0x18) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0x6), *(s16 *)(param_1 + 0x58), 8, 1);
    *(s16 *)(param_1 + 0x6) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xa), *(s16 *)(param_1 + 0x5a), 8, 1);
    *(s16 *)(param_1 + 0xa) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xe), *(s16 *)(param_1 + 0x5c), 8, 1);
    *(s16 *)(param_1 + 0xe) = uVar4;
}


DEFINE_func_80164270()  /* dedup: shared engine-core @0x80164270 (src/shared) */


DEFINE_func_801642AC()  /* dedup: shared engine-core @0x801642ac (src/shared) */


DEFINE_func_8016432C()  /* dedup: shared engine-core @0x8016432c (src/shared) */


void func_80164410(void) {
}

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80164418);

DEFINE_func_80164530()  /* dedup: shared engine-core @0x80164530 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected (fn-ptr table dispatch via u16 idx, $s0 holds *(s32*)(p+0x20) across the call)

extern void func_80162D28(s32 *a0);

void func_80164744(s32 param_1)
{

    extern void (*D_8018D010[])(void);
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x20);
    D_8018D010[*(u16 *)(param_1 + 2)]();
    if (iVar1 != 0) {
        ((void (*)(s32))func_80162D28)(param_1);
    }
}



// @class: other
// @stuck: none — MATCH (relocation-masked); key was `if (iVar1 != 0) { big } else { func_80164930 }` (non-zero case first → beqz, not bnez)

extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80146CA0(void *a0);
extern void func_80164930(s32 a);


void func_801647A4(int param_1) {

    extern u16 D_800DF2E0;
    extern s32 D_8018CFD8;
    extern u16 D_8018D00C;
    extern s16 D_8018D00A;
    extern s16 D_8018D008;
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_8018CFD8;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        D_8018D00C = 0x80;
        D_8018D00A = 0x80;
        D_8018D008 = 0x80;
        *(u16 *)(iVar1 + 0x1a) = 0;
        *(u16 *)(param_1 + 0x60) = 0;
        *(u16 *)(param_1 + 0x62) = 0x200;
        ((s32 (*)(s32))func_80164A74)(param_1);
        ((void (*)(s32))func_80146CA0)(param_1);
    } else {
        func_80164930(param_1);
    }
}


DEFINE_func_80164864()  /* dedup: shared engine-core @0x80164864 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80164930);

DEFINE_func_80164A74()  /* dedup: shared engine-core @0x80164a74 (src/shared) */


DEFINE_func_80164ACC()  /* dedup: shared engine-core @0x80164acc (src/shared) */




void func_80164BA0(void *a0) {

    extern void (*D_8018D01C[])(void);
    D_8018D01C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80146578(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80164DB0(void);


void func_80164BDC(s32 param_1)
{

    extern u8 D_801F5000;
    extern u8 D_801F5001;
    extern u8 D_801F5002;
    extern u8 D_801F5003;
    extern u8 D_801F5004;
    extern u8 D_801F5005;
    extern u8 D_801F5006;
    extern u8 D_801F5007;
    register s32 p1   __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base __asm__("$18");  /* $s2 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_801F5000;
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CD50(iVar1, base);
        ((void (*)(s32, s32))func_800233CC)(base, 0x60);
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        D_801F5001 = 0xf0;
        *(u8 *)base = 0xf0;
        D_801F5002 = 0xc0;
        D_801F5006 = 0;
        D_801F5005 = 0;
        D_801F5004 = 0;
        D_801F5007 = 0;
        D_801F5003 = 0;
        *(s16 *)(iVar1 + 0x1e) = 0xccc;
        *(s16 *)(iVar1 + 0x10) = 0x400;
        *(s16 *)(p1 + 0x60) = 0x700;
        *(s16 *)(p1 + 0x62) = -0x60;
        func_80164DD0(p1);
        ((void (*)(s32))func_80146CA0)(p1);
    } else {
        ((void (*)(s32))func_80164DB0)(p1);
    }
}


DEFINE_func_80164CD4()  /* dedup: shared engine-core @0x80164cd4 (src/shared) */


DEFINE_func_80164D4C()  /* dedup: shared engine-core @0x80164d4c (src/shared) */


DEFINE_func_80164DB0()  /* dedup: shared engine-core @0x80164db0 (src/shared) */


DEFINE_func_80164DD0()  /* dedup: shared engine-core @0x80164dd0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80164E40);



void func_80164EA4(void *a0) {

    extern void (*D_8018D02C[])(void);
    D_8018D02C[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

  /* stride 0x10 */

extern void func_80165124(void *a0);
extern void func_80146CA0(void *a0);

void func_80164EE0(int param_1)
{

    extern DStruct D_801F504C[];
    int i;

    for (i = 7; i >= 0; i--) {
        D_801F504C[i].f0 = 0;
    }
    *(short *)(param_1 + 0x2e) = 0x4000;
    *(short *)(param_1 + 0x2c) = 0x4000;
    *(short *)(param_1 + 0x60) = 0;
    *(short *)(param_1 + 0x62) = 0;
    ((void (*)(int))func_80165124)(param_1);
    *(short *)(param_1 + 0x66) = 0;
    ((void (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_80164F44()  /* dedup: shared engine-core @0x80164f44 (src/shared) */


DEFINE_func_80165024()  /* dedup: shared engine-core @0x80165024 (src/shared) */


DEFINE_func_80165064()  /* dedup: shared engine-core @0x80165064 (src/shared) */


DEFINE_func_801650C4()  /* dedup: shared engine-core @0x801650c4 (src/shared) */


DEFINE_func_80165124()  /* dedup: shared engine-core @0x80165124 (src/shared) */



// @class: struct
// @stuck: none — MATCH (30 ins)
//
// Unaligned slot-fill: loop over 8 slots (0x10 stride) of a global table,
// fill the first free one (field @0xC == 0). Two unaligned block copies from
// param_1 (packed struct assigns -> lwl/lwr/swl/swr). Key: recompute
// p = &D_801F5040[i] each iteration (NOT p++) so gcc reduces base+i*0x10 into
// a SINGLE pointer IV with immediate offsets 0/8/0xC. Hand-incrementing p makes
// combine_givs split the field offsets into a second pointer IV (+2 ins).


typedef struct { u8 d[8]; } __attribute__((packed, aligned(1))) B8_80165140;
typedef struct { u8 d[4]; } __attribute__((packed, aligned(1))) B4;
typedef struct { B8_80165140 a; B4 b; s32 used; } Slot;


s32 func_80165140(s32 param_1) {
    extern Slot D_801F5040[8];

    int i;
    Slot *p;
    for (i = 0; i < 8; i++) {
        p = &D_801F5040[i];
        if (p->used == 0) {
            p->used = 8;
            p->a = *(B8_80165140 *)(((u8 *)param_1) + 0x2c);
            p->b = *(B4 *)(((u8 *)param_1) + 0x50);
            return;
        }
    }
}




// @class: schedule
// @stuck: none — MATCH (pins $s2/$s1/$s0 + zero-code barrier hoists $a0 copy into beqz delay slot)

extern s32 func_80165240(s32 a0, s32 a1, s32 a2);

void func_801651B8(void * param_1)
{

    extern s32 D_801F5040;
    register s32 *puVar1 __asm__("$16"); /* $s0 */
    register s32 iVar2 __asm__("$17");   /* $s1 */
    register s32 p __asm__("$18");        /* $s2 */

    p = param_1;
    func_80165240(p, p + 0x2c, p + 0x50);
    iVar2 = 0;
    puVar1 = &D_801F5040;
    do {
        if (puVar1[3] != 0) {
            s32 a0v = p;
            __asm__ __volatile__("" : "=r"(a0v) : "0"(a0v));
            func_80165240(a0v, (s32)puVar1, (s32)(puVar1 + 2));
            puVar1[3] = puVar1[3] + -1;
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 4;
    } while (iVar2 < 8);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80165240);

DEFINE_func_8016533C()  /* dedup: shared engine-core @0x8016533c (src/shared) */


DEFINE_func_80165374()  /* dedup: shared engine-core @0x80165374 (src/shared) */


DEFINE_func_801653B8()  /* dedup: shared engine-core @0x801653b8 (src/shared) */


DEFINE_func_801653F4()  /* dedup: shared engine-core @0x801653f4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (54 ins)

extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);

void func_801654A8(s32 arg0)
{

    extern u8 D_80078E78[];
    extern u8 D_80078EC1;
    extern void (*D_8018D070[])(void);
    u8 *s1 = D_80078E78;

    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 != 0x1A) {
        if ((*(s32 *)(arg0 + 0x1F8) & 0x80FFFFFF) == 0) {
            if (func_80165658(arg0, D_80078EC1) & 0x80) {
                ((void (*)(s32))D_8018D070[D_80078EC1 & 0x7F])(arg0);
            }
        }
    }
    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 == 0x1A) {
        return;
    }
    if (s1[0x49] == 0x19) {
        func_800CAE0C(arg0);
    }
}



// @class: struct
// @stuck: none — MATCH (function-pointer-array dispatch; & 0x80 branch + & 0x7f index fold)

extern void func_80165B28(void *a0);

void func_80165580(s32 _arg0)
{

    extern u8 D_80078EC5;
    extern u8 D_80078EC1;
    extern void (*D_8018D070[])(void);
    if (D_80078EC5 & 0x80) {
        ((void (*)(void))func_80165B28)();
    } else {
        D_8018D070[D_80078EC1 & 0x7F]();
    }
}


DEFINE_func_801655E4()  /* dedup: shared engine-core @0x801655e4 (src/shared) */


DEFINE_func_80165624()  /* dedup: shared engine-core @0x80165624 (src/shared) */




u8 func_80165658(s32 a0, s32 a1) {

    extern u8 D_8018D0EC[];
    return D_8018D0EC[a1 & 0x7F];
}




void func_80165670(s32 a0, s32 a1) {

    extern s32 D_8018D10C[];
    extern s32 D_80078EC8;
    D_80078EC8 = D_8018D10C[a1 & 0x7F];
}


DEFINE_func_80165694()  /* dedup: shared engine-core @0x80165694 (src/shared) */




u8 func_801656D0(s32 a0, s32 a1) {

    extern u8 D_8018D188[];
    return D_8018D188[a1 & 0x7F];
}




u8 func_801656E8(s32 a0, s32 a1) {

    extern u8 D_8018D1A8[];
    return D_8018D1A8[a1 & 0x7F];
}




u8 func_80165700(s32 a0, s32 a1) {

    extern u8 D_8018D1C8[];
    return D_8018D1C8[a1 & 0x7F];
}


DEFINE_func_80165718()  /* dedup: shared engine-core @0x80165718 (src/shared) */


DEFINE_func_80165770()  /* dedup: shared engine-core @0x80165770 (src/shared) */


DEFINE_func_801657A0()  /* dedup: shared engine-core @0x801657a0 (src/shared) */


DEFINE_func_801657D8()  /* dedup: shared engine-core @0x801657d8 (src/shared) */


DEFINE_func_80165840()  /* dedup: shared engine-core @0x80165840 (src/shared) */


DEFINE_func_80165874()  /* dedup: shared engine-core @0x80165874 (src/shared) */


DEFINE_func_801658DC()  /* dedup: shared engine-core @0x801658dc (src/shared) */


DEFINE_func_801658EC()  /* dedup: shared engine-core @0x801658ec (src/shared) */


DEFINE_func_80165900()  /* dedup: shared engine-core @0x80165900 (src/shared) */


DEFINE_func_80165910()  /* dedup: shared engine-core @0x80165910 (src/shared) */


DEFINE_func_80165938()  /* dedup: shared engine-core @0x80165938 (src/shared) */


DEFINE_func_80165958()  /* dedup: shared engine-core @0x80165958 (src/shared) */


DEFINE_func_80165978()  /* dedup: shared engine-core @0x80165978 (src/shared) */


DEFINE_func_80165988()  /* dedup: shared engine-core @0x80165988 (src/shared) */


DEFINE_func_801659A8()  /* dedup: shared engine-core @0x801659a8 (src/shared) */


DEFINE_func_801659B8()  /* dedup: shared engine-core @0x801659b8 (src/shared) */


DEFINE_func_801659CC()  /* dedup: shared engine-core @0x801659cc (src/shared) */




s32 func_801659DC(u8 *a0) {

    extern void (*D_8018D1E8[])(void);
    D_8018D1E8[*(u8 *)((s32)a0 + 0x1A0)]();
}


void func_80165A18(void) {
}

DEFINE_func_80165A20()  /* dedup: shared engine-core @0x80165a20 (src/shared) */


DEFINE_func_80165A50()  /* dedup: shared engine-core @0x80165a50 (src/shared) */


DEFINE_func_80165A78()  /* dedup: shared engine-core @0x80165a78 (src/shared) */




void func_80165AC8(void) {

    extern u8 D_80078EC1;
    extern void (*D_8018D264[])(void);
    D_8018D264[D_80078EC1 & 0x7F]();
}


void func_80165B08(void) {
}

void func_80165B10(void) {
}

void func_80165B18(void) {
}

void func_80165B20(void) {
}



void func_80165B28(void *a0) {

    extern void (*D_8018D2E0[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_8018D2E0[*(u8 *)((s32)a0 + 0x197)]();
}


DEFINE_func_80165B6C()  /* dedup: shared engine-core @0x80165b6c (src/shared) */


DEFINE_func_80165BB4()  /* dedup: shared engine-core @0x80165bb4 (src/shared) */


DEFINE_func_80165BFC()  /* dedup: shared engine-core @0x80165bfc (src/shared) */


DEFINE_func_80165C58()  /* dedup: shared engine-core @0x80165c58 (src/shared) */


DEFINE_func_80165C78()  /* dedup: shared engine-core @0x80165c78 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80165CA0);


void func_80165E2C(u16 *arg0) {

    extern M2C_UNK D_801F479C;
    func_8001534C(0, &D_801F479C, 0x80, 0x80, 0, 0);
    func_800153CC(1, *arg0, 0xA8, 0x80, 0x40, 0);
}


DEFINE_func_80165E90()  /* dedup: shared engine-core @0x80165e90 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80165FA4);



void func_80166018(void *a0) {

    extern void (*D_8018D2EC[])(void);
    D_8018D2EC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80166054);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801661CC);

DEFINE_func_80166244()  /* dedup: shared engine-core @0x80166244 (src/shared) */


DEFINE_func_8016629C()  /* dedup: shared engine-core @0x8016629c (src/shared) */


DEFINE_func_801662F4()  /* dedup: shared engine-core @0x801662f4 (src/shared) */


DEFINE_func_8016634C()  /* dedup: shared engine-core @0x8016634c (src/shared) */


DEFINE_func_801663A4()  /* dedup: shared engine-core @0x801663a4 (src/shared) */




void func_801663FC(void *a0) {

    extern void (*D_8018D2F4[])(void);
    D_8018D2F4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80166438()  /* dedup: shared engine-core @0x80166438 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801665B4);



void func_80166618(void *a0) {

    extern void (*D_8018D3BC[])(void);
    D_8018D3BC[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80166654(void *a0) {

    extern void (*D_8018D3CC[])(void);
    D_8018D3CC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80166690);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80166994);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80166F58);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016706C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801670E4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80167540);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80167714);



void func_801678B4(void *a0) {

    extern void (*D_8018D3DC[])(void);
    D_8018D3DC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801678F0);



void func_80167A9C(void *a0) {

    extern void (*D_8018D3E8[])(void);
    D_8018D3E8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80167AD8(void) {
}

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80167AE0);

extern s32 func_80017758(void *a0, void *a1);
extern int func_80029178(int);


// @class: schedule
// @stuck: none — MATCH. The between-loops f1/f2 store-swap (0x55/0x56) is fixed by writing f2's assign first, then the chained `buf[0x44] = buf[0x45] = buf[0x45] << 1;` — the chain keeps f1's read first (read order fixed by -0x12 in $v0) while emitting f2's store (0x56) ahead of the f1/f0 pair (0x55,0x54). 173/173.

extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);

s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2) {

    extern u16  D_800B99DA;
    extern u8   D_8018D348[];
    extern u8   D_8018D35C[];
    u8 buf[0x54];
    u8 *p;
    s16 i;

    func_80168070(arg0, ((s16 *)arg1), ((s16 *)arg2), buf);

    *(s16 *)(buf + 0x3C) = 0;
    *(s16 *)(buf + 0x34) = 0;
    *(s16 *)(buf + 0x24) = 0;
    *(s16 *)(buf + 0x2C) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    if (D_800B99DA & 1) {
        buf[0x46] = 0x58;
    } else {
        buf[0x46] = 0x48;
    }
    buf[0x45] = buf[0x46] >> 2;
    buf[0x44] = buf[0x45];
    if (((u8 (*)(s32))func_80029178)(0x81) != 0) {
        buf[0x45] = buf[0x45] << 2;
        buf[0x46] = buf[0x46] >> 1;
    }

    p = D_8018D348;
    buf[0x42] = 0;
    buf[0x41] = 0;
    buf[0x40] = 0;
    buf[0x4A] = 0;
    buf[0x49] = 0;
    buf[0x48] = 0;
    buf[0x4E] = 0;
    buf[0x4D] = 0;
    buf[0x4C] = 0;
    *(s32 *)(buf + 0x50) = 0x50000000;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x22) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x32) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3A) = (s8)*p--;
        func_80017758(buf + 0x20, buf);
    }

    p = D_8018D35C;
    *(s16 *)(buf + 0x2C) = -0x12;
    *(s16 *)(buf + 0x3A) = 0;
    *(s16 *)(buf + 0x32) = 0;
    *(s16 *)(buf + 0x22) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    buf[0x46] = buf[0x46] << 1;
    buf[0x44] = buf[0x45] = buf[0x45] << 1;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x24) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x34) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3C) = (s8)*p--;
        if (i == 2) {
            buf[0x4E] = buf[0x46];
            buf[0x4D] = buf[0x44];
            buf[0x4C] = buf[0x4D];
        } else if (i == 3) {
            buf[0x4E] = 0;
            buf[0x4D] = 0;
            buf[0x4C] = buf[0x4D];
            buf[0x42] = buf[0x46];
            buf[0x41] = buf[0x44];
            buf[0x40] = buf[0x44];
        }
        func_80017758(buf + 0x20, buf);
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80168070);


extern s32 func_80029178(s32 arg);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_801681FC(s32 param_1) {

    extern u8 D_8018D3A0[];
    extern u8 D_8018D370[];
    extern u8 D_8018D371[];
    s32 iVar3;
    s32 a3;

    *(s16 *)(param_1 + 0x28) = func_80029178(0x81) & 0xFF;
    *(s32 *)(param_1 + 0x30) = D_8018D3A0[*(s32 *)(param_1 + 0x2C)];
    iVar3 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_8018D370[iVar3];
    *(s32 *)(param_1 + 0x1C) = D_8018D371[iVar3];
    a3 = *(s32 *)(param_1 + 0x2C) & 1;
    *(s32 *)(param_1 + 0x2C) = a3;
    func_80166F58(param_1, 4, 4, a3);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016829C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80168328);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801683D8);


extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80168430(s32 param_1) {

    extern u8 D_8018D3AC[];
    extern u8 D_8018D384[];
    extern u8 D_8018D385[];
    s32 iVar1;

    *(s32 *)(param_1 + 0x30) = D_8018D3AC[*(s32 *)(param_1 + 0x2C)];
    iVar1 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_8018D384[iVar1];
    *(s32 *)(param_1 + 0x1C) = D_8018D385[iVar1];
    func_80166F58(param_1, 5, 0x3B, 2);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801684B4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80168540);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801685EC);

DEFINE_func_80168640()  /* dedup: shared engine-core @0x80168640 (src/shared) */


DEFINE_func_80168664()  /* dedup: shared engine-core @0x80168664 (src/shared) */




void func_80168744(void *a0) {

    extern void (*D_8018D400[])(void);
    D_8018D400[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168780()  /* dedup: shared engine-core @0x80168780 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801687CC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80168828);



void func_801689D8(void *a0) {

    extern void (*D_8018D408[])(void);
    D_8018D408[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168A14()  /* dedup: shared engine-core @0x80168a14 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80168A88);



void func_80168AA8(void *a0) {

    extern void (*D_8018D410[])(void);
    D_8018D410[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168AE4()  /* dedup: shared engine-core @0x80168ae4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80168B70);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80168BDC);



void func_80168D58(void *a0) {

    extern void (*D_8018D418[])(void);
    D_8018D418[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80168D94);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80168EC4);

DEFINE_func_80168F40()  /* dedup: shared engine-core @0x80168f40 (src/shared) */




void func_8016901C(void *a0) {

    extern void (*D_8018D420[])(void);
    D_8018D420[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80169058);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801691B8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80169228);



void func_801693CC(void *a0) {

    extern void (*D_8018D428[])(void);
    D_8018D428[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80169408);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016951C);

DEFINE_func_80169584()  /* dedup: shared engine-core @0x80169584 (src/shared) */


DEFINE_func_801696D8()  /* dedup: shared engine-core @0x801696d8 (src/shared) */




void func_80169830(void *a0) {

    extern void (*D_8018D430[])(void);
    D_8018D430[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016986C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801699D0);

DEFINE_func_80169A4C()  /* dedup: shared engine-core @0x80169a4c (src/shared) */




void func_80169B80(void *a0) {

    extern void (*D_8018D4E4[])(void);
    D_8018D4E4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80169BBC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80169E44);



void func_80169F00(void *a0) {

    extern void (*D_8018D4EC[])(void);
    D_8018D4EC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80169F3C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80169FE0);



void func_8016A020(void *a0) {

    extern void (*D_8018D524[])(void);
    D_8018D524[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016A05C()  /* dedup: shared engine-core @0x8016a05c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016A08C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016A1CC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016A290);



void func_8016A700(void *a0) {

    extern void (*D_8018D530[])(void);
    D_8018D530[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016A73C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016A890);

DEFINE_func_8016A8FC()  /* dedup: shared engine-core @0x8016a8fc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016AA50);



void func_8016AB30(void *a0) {

    extern void (*D_8018D578[])(void);
    D_8018D578[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016AB6C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016AE5C);

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016afb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016B114);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016B234);

DEFINE_func_8016B3F4()  /* dedup: shared engine-core @0x8016b3f4 (src/shared) */


DEFINE_func_8016B428()  /* dedup: shared engine-core @0x8016b428 (src/shared) */


DEFINE_func_8016B448()  /* dedup: shared engine-core @0x8016b448 (src/shared) */




void func_8016B4BC(void *a0) {

    extern void (*D_8018D5F4[])(void);
    D_8018D5F4[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

extern void func_80015978(s32 a0, s32 *a1);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B984(void *a0);
extern void func_8016B91C(int);

void func_8016B4F8(int param_1)
{

    extern int D_801F5360;
    int iVar1;
    int uVar2;
    volatile int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_801F5360);
    if (func_8016B9F8(param_1) == 0) {
        *(int *)(param_1 + 0x18) = 0;
        *(int *)(param_1 + 0x14) = 0;
        *(int *)(param_1 + 0x10) = 0;
        iVar1 = func_8016B834(param_1, 0);
        *(int *)(param_1 + 0x10) = iVar1;
        if (iVar1 != 0) {
            iVar1 = func_8016B834(param_1, 1);
            *(int *)(param_1 + 0x14) = iVar1;
            if (iVar1 != 0) {
                iVar1 = func_8016B834(param_1, 2);
                *(int *)(param_1 + 0x18) = iVar1;
                if (iVar1 != 0) goto success;
            }
        }
    }
    ((void (*)(int))func_8016B984)(param_1);
    return;
success:
    func_8016B91C(param_1);
    uVar2 = *(int *)(param_1 + 0x2c);
    if (uVar2 == 0) {
        uVar2 = 0xf0;
    } else {
        uVar2 = 0x2d0;
    }
    *(int *)(param_1 + 0x1c) = uVar2;
    uVar2 = *(unsigned short *)(param_1 + 2);
    uVar2 = uVar2 + 1;
    *(unsigned short *)(param_1 + 2) = uVar2;
}




// @class: schedule
// @stuck: none — MATCH

extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B984(void *a0);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);


void func_8016B5C0(s32 param_1) {

    extern s16 D_8018D5E8[];
    s32 iVar4;
    s32 iVar2;
    s32 iVar5;
    s16 sVar1;
    s16 *psVar5;
    s32 i;

    iVar4 = *(s32 *)(param_1 + 0x18);
    if (((s32 (*)(void))func_8016B9F8)() != 0) {
        goto L984;
    }
    sVar1 = *(s16 *)(iVar4 + 0x1a) + 0x200;
    *(s16 *)(iVar4 + 0x1a) = sVar1;
    *(s16 *)(iVar4 + 0x18) = sVar1;
    if (*(s32 *)(param_1 + 0x2c) == 0) {
        iVar2 = *(s32 *)(param_1 + 0x1c);
    } else {
        iVar2 = *(s32 *)(param_1 + 0x1c) / 3;
    }
    iVar5 = *(s32 *)(param_1 + 0x1c) + -0x20;
    *(s32 *)(param_1 + 0x1c) = iVar5;
    if (iVar5 >= 0) {
        goto LOOP;
    }
L984:
    ((void (*)(s32))func_8016B984)(param_1);
    return;
LOOP:
    i = 0;
    psVar5 = D_8018D5E8;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016B6BC);


// @class: schedule
// @stuck: none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);


int func_8016B834(int param_1, int param_2) {

    extern int *D_8018D62C[];
    extern unsigned short D_8018D634[];
    extern unsigned short D_8018D63C[];
    extern unsigned char D_801F5368[];
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_801F5368 + param_2 * 0x40);
    puVar3 = D_8018D62C[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_8018D634[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_8018D63C[param_2];
    }
    return iVar1;
}


DEFINE_func_8016B91C()  /* dedup: shared engine-core @0x8016b91c (src/shared) */


DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016b964 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016B984);


// @class: regalloc-order
// @stuck: none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)

extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{

    extern s32 D_801F5360;
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_801F5360, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}


DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016ba48 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016BA68);

DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016badc (src/shared) */




void func_8016BBA4(void *a0) {

    extern void (*D_8018D644[])(void);
    D_8018D644[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016BBE0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016BCC0);

extern void func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);

// @class: struct
// @stuck: none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{

    extern M2C_UNK D_801F549C;
    extern M2C_UNK D_801F54A0;
    extern u8 D_801F549D;
    extern u8 D_801F549E;
    extern u8 D_801F54A1;
    extern u8 D_801F54A2;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    ((void(*)())func_8016BF50)();

    p1 = &(*(u8 *)&D_801F549C);
    if (*p1 != 0) *p1 -= 4;
    if (D_801F549D != 0) D_801F549D -= 4;
    if (D_801F549E != 0) D_801F549E -= 4;
    p2 = &(*(u8 *)&D_801F54A0);
    if (*p2 != 0) *p2 -= 4;
    if (D_801F54A1 != 0) D_801F54A1 -= 4;
    if (D_801F54A2 != 0) D_801F54A2 -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016BEA0);

DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016bf34 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016BF50);


extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_801F5428;
    func_8016BFD0(a0, a1, a2, a3, &D_801F5428);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016BFD0);



void func_8016C14C(void *a0) {

    extern void (*D_8018D674[])(void);
    D_8018D674[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016C188);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016C2C4);

DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016c374 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016C49C);

DEFINE_func_8016C74C()  /* dedup: shared engine-core @0x8016c74c (src/shared) */


DEFINE_func_8016C83C()  /* dedup: shared engine-core @0x8016c83c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016C998);



void func_8016CB84(void *a0) {

    extern void (*D_8018D67C[])(void);
    D_8018D67C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016CBC0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016CF04);



void func_8016D19C(void *a0) {

    extern void (*D_8018D698[])(void);
    D_8018D698[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016D1D8);



void func_8016D428(void *a0) {

    extern void (*D_8018D6A0[])(void);
    D_8018D6A0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016D464()  /* dedup: shared engine-core @0x8016d464 (src/shared) */


DEFINE_func_8016D4DC()  /* dedup: shared engine-core @0x8016d4dc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016D5EC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016D64C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016D688);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016D778);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016D848);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016D984);

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016da04 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);

void func_8016DA30(int param_1)
{

    extern void (*D_8018D708[])(int);
    ((void (*)(void))func_8016DBD8)();
    D_8018D708[*(unsigned short *)(param_1 + 2)](param_1);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016DA7C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016DB34);

DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016dbd8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016DC20);



void func_8016DEA4(void *a0) {

    extern void (*D_8018D73C[])(void);
    D_8018D73C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016DEE0);



void func_8016DF20(void *a0) {

    extern void (*D_8018D744[])(void);
    D_8018D744[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016DF5C);

DEFINE_func_8016E1CC()  /* dedup: shared engine-core @0x8016e1cc (src/shared) */


DEFINE_func_8016E26C()  /* dedup: shared engine-core @0x8016e26c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016E2E8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016E358);

DEFINE_func_8016E3CC()  /* dedup: shared engine-core @0x8016e3cc (src/shared) */


DEFINE_func_8016E460()  /* dedup: shared engine-core @0x8016e460 (src/shared) */




void func_8016E5B8(void *a0) {

    extern void (*D_8018D798[])(void);
    D_8018D798[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016E5F4);

DEFINE_func_8016E688()  /* dedup: shared engine-core @0x8016e688 (src/shared) */


DEFINE_func_8016E6E4()  /* dedup: shared engine-core @0x8016e6e4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016E728);

DEFINE_func_8016E778()  /* dedup: shared engine-core @0x8016e778 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016E7C8);

DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016e8f0 (src/shared) */


DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016e918 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016E95C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016E9EC);


// @class: struct
// @stuck: none — MATCH (31/31 ins, match_one verified)

extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{

    extern u16 D_8018D7CC[];
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_8018D7CC[param_1->f2];
    ((void (*)(void *, int))func_8016EC0C)(param_1, 0x80);
    bVar1 = param_1->f2 + 1;
    param_1->f2 = bVar1;
    if (5 < bVar1) {
        param_1->f2 = 0x20;
        param_1->f1 = param_1->f1 + 1;
    }
}



// @class: loose-typing
// @stuck: none — MATCH (u8 v + 0xFF emits addiu 0xFF; v-1 would emit -1/0xffff)

extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EB3C(s32 p) {

    extern u8 D_8018D7BC[];
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_8018D7BC[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}



// @class: struct
// @stuck: none — MATCH (25 ins). %lo-fold via extern u16 D_8018D7CC[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.


extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{

    extern u16 D_8018D7CC[];
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_8018D7CC[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016EC0C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016ED6C);

DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ed8c (src/shared) */


DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016edbc (src/shared) */


DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016edec (src/shared) */


DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016ee40 (src/shared) */


DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016ee94 (src/shared) */


DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016ef78 (src/shared) */


DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016efa8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016EFC8);

DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016f094 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016F0AC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8016F0E4);

DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016f14c (src/shared) */


DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016f1ac (src/shared) */



// @class: schedule
// @stuck: none — MATCH

extern s16 currentLocationId;

s32 func_8016F1C4(void) {

    extern s32 D_8018D7E8;
    extern s32 D_80126B58;
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_8018D7E8;
    cur = *p;
    if (cur != 0) {
        loc = currentLocationId;
        p = p + 1;
        for (;;) {
            if (loc == cur) {
                return 1;
            }
            cur = *p;
            p = p + 1;
            if (cur == 0) {
                break;
            }
        }
    }
    v = base[0x7E];
    if (((v & 0x80FFFFFF) != 0) && ((v & 0x10000000) != 0)) {
        return 0;
    }
    return base[0x7E] & 0x80FFFFFF;
}


DEFINE_func_8016F250()  /* dedup: shared engine-core @0x8016f250 (src/shared) */


DEFINE_func_8016F264()  /* dedup: shared engine-core @0x8016f264 (src/shared) */


DEFINE_func_8016F288()  /* dedup: shared engine-core @0x8016f288 (src/shared) */


DEFINE_func_8016F2A8()  /* dedup: shared engine-core @0x8016f2a8 (src/shared) */


DEFINE_func_8016F2C8()  /* dedup: shared engine-core @0x8016f2c8 (src/shared) */


DEFINE_func_8016F2EC()  /* dedup: shared engine-core @0x8016f2ec (src/shared) */


DEFINE_func_8016F30C()  /* dedup: shared engine-core @0x8016f30c (src/shared) */


DEFINE_func_8016F330()  /* dedup: shared engine-core @0x8016f330 (src/shared) */


DEFINE_func_8016F350()  /* dedup: shared engine-core @0x8016f350 (src/shared) */


DEFINE_func_8016F374()  /* dedup: shared engine-core @0x8016f374 (src/shared) */


DEFINE_func_8016F388()  /* dedup: shared engine-core @0x8016f388 (src/shared) */


DEFINE_func_8016F398()  /* dedup: shared engine-core @0x8016f398 (src/shared) */


DEFINE_func_8016F410()  /* dedup: shared engine-core @0x8016f410 (src/shared) */


DEFINE_func_8016F44C()  /* dedup: shared engine-core @0x8016f44c (src/shared) */


DEFINE_func_8016F470()  /* dedup: shared engine-core @0x8016f470 (src/shared) */


DEFINE_func_8016F494()  /* dedup: shared engine-core @0x8016f494 (src/shared) */


DEFINE_func_8016F4C4()  /* dedup: shared engine-core @0x8016f4c4 (src/shared) */


void func_8016F4F4(void) {
}

DEFINE_func_8016F4FC()  /* dedup: shared engine-core @0x8016f4fc (src/shared) */


DEFINE_func_8016F540()  /* dedup: shared engine-core @0x8016f540 (src/shared) */


DEFINE_func_8016F578()  /* dedup: shared engine-core @0x8016f578 (src/shared) */


DEFINE_func_8016F5B0()  /* dedup: shared engine-core @0x8016f5b0 (src/shared) */


DEFINE_func_8016F5E0()  /* dedup: shared engine-core @0x8016f5e0 (src/shared) */


DEFINE_func_8016F610()  /* dedup: shared engine-core @0x8016f610 (src/shared) */


DEFINE_func_8016F648()  /* dedup: shared engine-core @0x8016f648 (src/shared) */


DEFINE_func_8016F680()  /* dedup: shared engine-core @0x8016f680 (src/shared) */


DEFINE_func_8016F6B0()  /* dedup: shared engine-core @0x8016f6b0 (src/shared) */




void func_8016F6E0(void *a0) {

    extern void (*D_8018D860[])(void);
    D_8018D860[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F71C()  /* dedup: shared engine-core @0x8016f71c (src/shared) */


DEFINE_func_8016F764()  /* dedup: shared engine-core @0x8016f764 (src/shared) */




void func_8016F798(void *a0) {

    extern void (*D_8018D868[])(void);
    D_8018D868[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F7D4()  /* dedup: shared engine-core @0x8016f7d4 (src/shared) */


DEFINE_func_8016F804()  /* dedup: shared engine-core @0x8016f804 (src/shared) */




void func_8016F834(void *a0) {

    extern void (*D_8018D870[])(void);
    D_8018D870[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F870()  /* dedup: shared engine-core @0x8016f870 (src/shared) */


DEFINE_func_8016F8AC()  /* dedup: shared engine-core @0x8016f8ac (src/shared) */




void func_8016F8E4(void *a0) {

    extern void (*D_8018D878[])(void);
    D_8018D878[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F920()  /* dedup: shared engine-core @0x8016f920 (src/shared) */


DEFINE_func_8016F95C()  /* dedup: shared engine-core @0x8016f95c (src/shared) */




void func_8016F9C4(void *a0) {

    extern void (*D_8018D880[])(void);
    D_8018D880[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FA00()  /* dedup: shared engine-core @0x8016fa00 (src/shared) */


DEFINE_func_8016FA44()  /* dedup: shared engine-core @0x8016fa44 (src/shared) */




void func_8016FA84(void *a0) {

    extern void (*D_8018D888[])(void);
    D_8018D888[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FAC0()  /* dedup: shared engine-core @0x8016fac0 (src/shared) */


DEFINE_func_8016FB10()  /* dedup: shared engine-core @0x8016fb10 (src/shared) */


DEFINE_func_8016FB50()  /* dedup: shared engine-core @0x8016fb50 (src/shared) */




void func_8016FB7C(void *a0) {

    extern void (*D_8018D894[])(void);
    D_8018D894[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FBB8()  /* dedup: shared engine-core @0x8016fbb8 (src/shared) */


DEFINE_func_8016FC24()  /* dedup: shared engine-core @0x8016fc24 (src/shared) */


DEFINE_func_8016FC64()  /* dedup: shared engine-core @0x8016fc64 (src/shared) */




void func_8016FC90(void *a0) {

    extern void (*D_8018D8A0[])(void);
    D_8018D8A0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FCCC()  /* dedup: shared engine-core @0x8016fccc (src/shared) */


DEFINE_func_8016FD08()  /* dedup: shared engine-core @0x8016fd08 (src/shared) */


DEFINE_func_8016FD7C()  /* dedup: shared engine-core @0x8016fd7c (src/shared) */




void func_8016FDB4(void *a0) {

    extern void (*D_8018D8AC[])(void);
    D_8018D8AC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FDF0()  /* dedup: shared engine-core @0x8016fdf0 (src/shared) */


DEFINE_func_8016FE2C()  /* dedup: shared engine-core @0x8016fe2c (src/shared) */


DEFINE_func_8016FE78()  /* dedup: shared engine-core @0x8016fe78 (src/shared) */


DEFINE_func_8016FED0()  /* dedup: shared engine-core @0x8016fed0 (src/shared) */




void func_8016FF30(void *a0) {

    extern void (*D_8018D8BC[])(void);
    D_8018D8BC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FF6C()  /* dedup: shared engine-core @0x8016ff6c (src/shared) */


DEFINE_func_8016FFA8()  /* dedup: shared engine-core @0x8016ffa8 (src/shared) */




void func_8016FFDC(void *a0) {

    extern void (*D_8018D8CC[])(void);
    D_8018D8CC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170018()  /* dedup: shared engine-core @0x80170018 (src/shared) */


DEFINE_func_80170068()  /* dedup: shared engine-core @0x80170068 (src/shared) */


DEFINE_func_801700B8()  /* dedup: shared engine-core @0x801700b8 (src/shared) */


DEFINE_func_80170100()  /* dedup: shared engine-core @0x80170100 (src/shared) */




void func_80170150(void *a0) {

    extern void (*D_8018D8D4[])(void);
    D_8018D8D4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017018C()  /* dedup: shared engine-core @0x8017018c (src/shared) */


DEFINE_func_801701C8()  /* dedup: shared engine-core @0x801701c8 (src/shared) */




void func_80170240(void *a0) {

    extern void (*D_8018D8DC[])(void);
    D_8018D8DC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017027C()  /* dedup: shared engine-core @0x8017027c (src/shared) */


DEFINE_func_801702B8()  /* dedup: shared engine-core @0x801702b8 (src/shared) */




void func_801702FC(void *a0) {

    extern void (*D_8018D8E4[])(void);
    D_8018D8E4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170338()  /* dedup: shared engine-core @0x80170338 (src/shared) */


DEFINE_func_80170374()  /* dedup: shared engine-core @0x80170374 (src/shared) */




void func_801703E0(void *a0) {

    extern void (*D_8018D8EC[])(void);
    D_8018D8EC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017041C()  /* dedup: shared engine-core @0x8017041c (src/shared) */


DEFINE_func_8017044C()  /* dedup: shared engine-core @0x8017044c (src/shared) */




void func_801704B0(void *a0) {

    extern void (*D_8018D8F4[])(void);
    D_8018D8F4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801704EC()  /* dedup: shared engine-core @0x801704ec (src/shared) */


DEFINE_func_8017051C()  /* dedup: shared engine-core @0x8017051c (src/shared) */




void func_80170548(void *a0) {

    extern void (*D_8018D8FC[])(void);
    D_8018D8FC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170584()  /* dedup: shared engine-core @0x80170584 (src/shared) */


DEFINE_func_801705C0()  /* dedup: shared engine-core @0x801705c0 (src/shared) */




void func_801705F8(void *a0) {

    extern void (*D_8018D904[])(void);
    D_8018D904[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170634()  /* dedup: shared engine-core @0x80170634 (src/shared) */


DEFINE_func_80170670()  /* dedup: shared engine-core @0x80170670 (src/shared) */




void func_801706AC(void *a0) {

    extern void (*D_8018D90C[])(void);
    D_8018D90C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801706E8()  /* dedup: shared engine-core @0x801706e8 (src/shared) */


DEFINE_func_80170718()  /* dedup: shared engine-core @0x80170718 (src/shared) */




void func_80170748(void *a0) {

    extern void (*D_8018D914[])(void);
    D_8018D914[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170784()  /* dedup: shared engine-core @0x80170784 (src/shared) */


DEFINE_func_801707D4()  /* dedup: shared engine-core @0x801707d4 (src/shared) */




void func_80170810(void *a0) {

    extern void (*D_8018D91C[])(void);
    D_8018D91C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017084C()  /* dedup: shared engine-core @0x8017084c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801708B0);

DEFINE_func_80170928()  /* dedup: shared engine-core @0x80170928 (src/shared) */


DEFINE_func_80170970()  /* dedup: shared engine-core @0x80170970 (src/shared) */


DEFINE_func_801709B8()  /* dedup: shared engine-core @0x801709b8 (src/shared) */


DEFINE_func_80170A00()  /* dedup: shared engine-core @0x80170a00 (src/shared) */


DEFINE_func_80170A48()  /* dedup: shared engine-core @0x80170a48 (src/shared) */


DEFINE_func_80170A90()  /* dedup: shared engine-core @0x80170a90 (src/shared) */




void func_80170AD8(void *a0) {

    extern void (*D_8018D924[])(void);
    D_8018D924[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170B14()  /* dedup: shared engine-core @0x80170b14 (src/shared) */


DEFINE_func_80170B48()  /* dedup: shared engine-core @0x80170b48 (src/shared) */


DEFINE_func_80170B90()  /* dedup: shared engine-core @0x80170b90 (src/shared) */




void func_80170BD8(void *a0) {

    extern void (*D_8018D92C[])(void);
    D_8018D92C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170C14()  /* dedup: shared engine-core @0x80170c14 (src/shared) */


DEFINE_func_80170C44()  /* dedup: shared engine-core @0x80170c44 (src/shared) */




void func_80170C74(void *a0) {

    extern void (*D_8018D934[])(void);
    D_8018D934[*(u8 *)((s32)a0 + 0x215)]();
}


DEFINE_func_80170CB0()  /* dedup: shared engine-core @0x80170cb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80170CF0);



void func_80170D68(void *a0) {

    extern void (*D_8018D93C[])(void);
    D_8018D93C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170da4 (src/shared) */


DEFINE_func_80170DE0()  /* dedup: shared engine-core @0x80170de0 (src/shared) */




void func_80170E34(void *a0) {

    extern void (*D_8018D944[])(void);
    D_8018D944[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170e70 (src/shared) */


DEFINE_func_80170EAC()  /* dedup: shared engine-core @0x80170eac (src/shared) */




void func_80170EFC(void *a0) {

    extern void (*D_8018D94C[])(void);
    D_8018D94C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170F38()  /* dedup: shared engine-core @0x80170f38 (src/shared) */


DEFINE_func_80170F74()  /* dedup: shared engine-core @0x80170f74 (src/shared) */




void func_80170FB0(void *a0) {

    extern void (*D_8018D954[])(void);
    D_8018D954[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170FEC()  /* dedup: shared engine-core @0x80170fec (src/shared) */


DEFINE_func_80171028()  /* dedup: shared engine-core @0x80171028 (src/shared) */




void func_80171064(void *a0) {

    extern void (*D_8018D95C[])(void);
    D_8018D95C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801710A0()  /* dedup: shared engine-core @0x801710a0 (src/shared) */


DEFINE_func_801710DC()  /* dedup: shared engine-core @0x801710dc (src/shared) */




void func_80171120(void *a0) {

    extern void (*D_8018D964[])(void);
    D_8018D964[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017115C()  /* dedup: shared engine-core @0x8017115c (src/shared) */


DEFINE_func_8017118C()  /* dedup: shared engine-core @0x8017118c (src/shared) */




void func_801711C0(void *a0) {

    extern void (*D_8018D96C[])(void);
    D_8018D96C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801711FC()  /* dedup: shared engine-core @0x801711fc (src/shared) */


DEFINE_func_80171238()  /* dedup: shared engine-core @0x80171238 (src/shared) */




void func_80171260(void *a0) {

    extern void (*D_8018D974[])(void);
    D_8018D974[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017129C);

DEFINE_func_80171384()  /* dedup: shared engine-core @0x80171384 (src/shared) */




void func_801714E4(void *a0) {

    extern void (*D_8018D97C[])(void);
    D_8018D97C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80171520()  /* dedup: shared engine-core @0x80171520 (src/shared) */


DEFINE_func_8017162C()  /* dedup: shared engine-core @0x8017162c (src/shared) */


DEFINE_func_801716AC()  /* dedup: shared engine-core @0x801716ac (src/shared) */


DEFINE_func_801717A0()  /* dedup: shared engine-core @0x801717a0 (src/shared) */


DEFINE_func_801717F4()  /* dedup: shared engine-core @0x801717f4 (src/shared) */


DEFINE_func_80171824()  /* dedup: shared engine-core @0x80171824 (src/shared) */


DEFINE_func_80171854()  /* dedup: shared engine-core @0x80171854 (src/shared) */


DEFINE_func_80171884()  /* dedup: shared engine-core @0x80171884 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801718AC);

DEFINE_func_80171904()  /* dedup: shared engine-core @0x80171904 (src/shared) */


DEFINE_func_80171928()  /* dedup: shared engine-core @0x80171928 (src/shared) */


DEFINE_func_8017196C()  /* dedup: shared engine-core @0x8017196c (src/shared) */


DEFINE_func_8017197C()  /* dedup: shared engine-core @0x8017197c (src/shared) */


DEFINE_func_80171990()  /* dedup: shared engine-core @0x80171990 (src/shared) */


DEFINE_func_801719A4()  /* dedup: shared engine-core @0x801719a4 (src/shared) */


DEFINE_func_80171A04()  /* dedup: shared engine-core @0x80171a04 (src/shared) */


DEFINE_func_80171A10()  /* dedup: shared engine-core @0x80171a10 (src/shared) */


DEFINE_func_80171A1C()  /* dedup: shared engine-core @0x80171a1c (src/shared) */


DEFINE_func_80171A34()  /* dedup: shared engine-core @0x80171a34 (src/shared) */


DEFINE_func_80171A44()  /* dedup: shared engine-core @0x80171a44 (src/shared) */


DEFINE_func_80171A58()  /* dedup: shared engine-core @0x80171a58 (src/shared) */


DEFINE_func_80171A6C()  /* dedup: shared engine-core @0x80171a6c (src/shared) */


DEFINE_func_80171A80()  /* dedup: shared engine-core @0x80171a80 (src/shared) */


DEFINE_func_80171A88()  /* dedup: shared engine-core @0x80171a88 (src/shared) */


DEFINE_func_80171AB0()  /* dedup: shared engine-core @0x80171ab0 (src/shared) */


DEFINE_func_80171B10()  /* dedup: shared engine-core @0x80171b10 (src/shared) */


DEFINE_func_80171B44()  /* dedup: shared engine-core @0x80171b44 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80171B4C);

DEFINE_func_80171C64()  /* dedup: shared engine-core @0x80171c64 (src/shared) */


DEFINE_func_80171CC4()  /* dedup: shared engine-core @0x80171cc4 (src/shared) */


DEFINE_func_80171D1C()  /* dedup: shared engine-core @0x80171d1c (src/shared) */


DEFINE_func_80171D78()  /* dedup: shared engine-core @0x80171d78 (src/shared) */


DEFINE_func_80171E08()  /* dedup: shared engine-core @0x80171e08 (src/shared) */


DEFINE_func_80171EC8()  /* dedup: shared engine-core @0x80171ec8 (src/shared) */



extern s32 func_8017248C(s32, s32);
extern s32 ratan2(s32, s32);
extern void func_80172170(s32, s32);
extern void func_80146D90(s32);

s32 func_80171FFC(short *a0, short *a1, s32 a2)
{
    s32 r;

    r = func_8017248C((s32)a0, (s32)a1);
    if (r != 0) {
        func_80146D90((s32)a0);
        return r;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        (ratan2(a1[0] - a0[3], a1[2] - a0[7]) + 0x800) & 0xFFF;
    func_80172170((s32)a0, a2 & 0xFF);
    return 0;
}


DEFINE_func_8017209C()  /* dedup: shared engine-core @0x8017209c (src/shared) */


DEFINE_func_80172170()  /* dedup: shared engine-core @0x80172170 (src/shared) */


DEFINE_func_801722CC()  /* dedup: shared engine-core @0x801722cc (src/shared) */


DEFINE_func_80172304()  /* dedup: shared engine-core @0x80172304 (src/shared) */


DEFINE_func_80172310()  /* dedup: shared engine-core @0x80172310 (src/shared) */


DEFINE_func_80172358()  /* dedup: shared engine-core @0x80172358 (src/shared) */


DEFINE_func_801723C4()  /* dedup: shared engine-core @0x801723c4 (src/shared) */


DEFINE_func_80172414()  /* dedup: shared engine-core @0x80172414 (src/shared) */


DEFINE_func_8017248C()  /* dedup: shared engine-core @0x8017248c (src/shared) */


DEFINE_func_801724EC()  /* dedup: shared engine-core @0x801724ec (src/shared) */


DEFINE_func_8017250C()  /* dedup: shared engine-core @0x8017250c (src/shared) */


DEFINE_func_80172560()  /* dedup: shared engine-core @0x80172560 (src/shared) */


DEFINE_func_80172588()  /* dedup: shared engine-core @0x80172588 (src/shared) */


DEFINE_func_80172590()  /* dedup: shared engine-core @0x80172590 (src/shared) */


DEFINE_func_801725A4()  /* dedup: shared engine-core @0x801725a4 (src/shared) */


DEFINE_func_801725B8()  /* dedup: shared engine-core @0x801725b8 (src/shared) */


DEFINE_func_801725CC()  /* dedup: shared engine-core @0x801725cc (src/shared) */


DEFINE_func_801725E0()  /* dedup: shared engine-core @0x801725e0 (src/shared) */


DEFINE_func_801725F4()  /* dedup: shared engine-core @0x801725f4 (src/shared) */


DEFINE_func_80172608()  /* dedup: shared engine-core @0x80172608 (src/shared) */


DEFINE_func_8017261C()  /* dedup: shared engine-core @0x8017261c (src/shared) */


DEFINE_func_80172630()  /* dedup: shared engine-core @0x80172630 (src/shared) */


DEFINE_func_80172644()  /* dedup: shared engine-core @0x80172644 (src/shared) */


DEFINE_func_80172658()  /* dedup: shared engine-core @0x80172658 (src/shared) */


DEFINE_func_80172664()  /* dedup: shared engine-core @0x80172664 (src/shared) */


DEFINE_func_80172670()  /* dedup: shared engine-core @0x80172670 (src/shared) */


DEFINE_func_8017267C()  /* dedup: shared engine-core @0x8017267c (src/shared) */


DEFINE_func_80172688()  /* dedup: shared engine-core @0x80172688 (src/shared) */


DEFINE_func_80172694()  /* dedup: shared engine-core @0x80172694 (src/shared) */


DEFINE_func_801726A0()  /* dedup: shared engine-core @0x801726a0 (src/shared) */


DEFINE_func_801726AC()  /* dedup: shared engine-core @0x801726ac (src/shared) */


DEFINE_func_801726B8()  /* dedup: shared engine-core @0x801726b8 (src/shared) */


DEFINE_func_801726C4()  /* dedup: shared engine-core @0x801726c4 (src/shared) */


DEFINE_func_801726D0()  /* dedup: shared engine-core @0x801726d0 (src/shared) */


DEFINE_func_80172710()  /* dedup: shared engine-core @0x80172710 (src/shared) */


DEFINE_func_80172738()  /* dedup: shared engine-core @0x80172738 (src/shared) */


DEFINE_func_80172760()  /* dedup: shared engine-core @0x80172760 (src/shared) */


DEFINE_func_80172780()  /* dedup: shared engine-core @0x80172780 (src/shared) */




s32 func_801727D0(void *a0) {

    extern void (*D_8018D98C[])(void);
    D_8018D98C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_8017280C()  /* dedup: shared engine-core @0x8017280c (src/shared) */


DEFINE_func_80172844()  /* dedup: shared engine-core @0x80172844 (src/shared) */


void func_8017288C(void) {
}

DEFINE_func_80172894()  /* dedup: shared engine-core @0x80172894 (src/shared) */




s32 func_801728E4(void *a0) {

    extern void (*D_8018D998[])(void);
    D_8018D998[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172920()  /* dedup: shared engine-core @0x80172920 (src/shared) */


DEFINE_func_80172958()  /* dedup: shared engine-core @0x80172958 (src/shared) */


void func_801729A8(void) {
}

DEFINE_func_801729B0()  /* dedup: shared engine-core @0x801729b0 (src/shared) */




s32 func_801729F0(void *a0) {

    extern void (*D_8018D9A4[])(void);
    D_8018D9A4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172A2C()  /* dedup: shared engine-core @0x80172a2c (src/shared) */


DEFINE_func_80172A8C()  /* dedup: shared engine-core @0x80172a8c (src/shared) */


DEFINE_func_80172ACC()  /* dedup: shared engine-core @0x80172acc (src/shared) */


void func_80172B0C(void) {
}

DEFINE_func_80172B14()  /* dedup: shared engine-core @0x80172b14 (src/shared) */




s32 func_80172B44(void *a0) {

    extern void (*D_8018D9B4[])(void);
    D_8018D9B4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172B80()  /* dedup: shared engine-core @0x80172b80 (src/shared) */


DEFINE_func_80172BC8()  /* dedup: shared engine-core @0x80172bc8 (src/shared) */


void func_80172C48(void) {
}

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80172C50);



void func_80172CA0(void *a0) {

    extern void (*D_8018D9C0[])(void);
    D_8018D9C0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172CDC()  /* dedup: shared engine-core @0x80172cdc (src/shared) */


DEFINE_func_80172D14()  /* dedup: shared engine-core @0x80172d14 (src/shared) */


void func_80172D60(void) {
}

DEFINE_func_80172D68()  /* dedup: shared engine-core @0x80172d68 (src/shared) */




s32 func_80172DAC(void *a0) {

    extern void (*D_8018D9CC[])(void);
    D_8018D9CC[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172DE8()  /* dedup: shared engine-core @0x80172de8 (src/shared) */


DEFINE_func_80172E20()  /* dedup: shared engine-core @0x80172e20 (src/shared) */


void func_80172E8C(void) {
}

DEFINE_func_80172E94()  /* dedup: shared engine-core @0x80172e94 (src/shared) */


DEFINE_func_80172ED4()  /* dedup: shared engine-core @0x80172ed4 (src/shared) */


DEFINE_func_80172EFC()  /* dedup: shared engine-core @0x80172efc (src/shared) */


DEFINE_func_80172F24()  /* dedup: shared engine-core @0x80172f24 (src/shared) */


DEFINE_func_80172F4C()  /* dedup: shared engine-core @0x80172f4c (src/shared) */


DEFINE_func_80172F9C()  /* dedup: shared engine-core @0x80172f9c (src/shared) */


DEFINE_func_80172FEC()  /* dedup: shared engine-core @0x80172fec (src/shared) */


DEFINE_func_8017303C()  /* dedup: shared engine-core @0x8017303c (src/shared) */




s32 func_80173078(void *a0) {

    extern void (*D_8018D9D8[])(void);
    D_8018D9D8[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801730B4()  /* dedup: shared engine-core @0x801730b4 (src/shared) */


DEFINE_func_801730FC()  /* dedup: shared engine-core @0x801730fc (src/shared) */


void func_8017316C(void) {
}

DEFINE_func_80173174()  /* dedup: shared engine-core @0x80173174 (src/shared) */




s32 func_8017319C(void *a0) {

    extern void (*D_8018D9E4[])(void);
    D_8018D9E4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801731D8()  /* dedup: shared engine-core @0x801731d8 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);

void func_80173220(void * arg0)
{

    extern M2C_UNK D_8018D984;
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x4000) {
        func_80147324(0x516);
        func_80019064(&D_8018D984);
    }
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x8000) {
        func_80171A1C(arg0);
        func_80174650(arg0);
    }
}


void func_80173294(void) {
}

DEFINE_func_8017329C()  /* dedup: shared engine-core @0x8017329c (src/shared) */


DEFINE_func_801732C4()  /* dedup: shared engine-core @0x801732c4 (src/shared) */


DEFINE_func_801732F4()  /* dedup: shared engine-core @0x801732f4 (src/shared) */


DEFINE_func_8017331C()  /* dedup: shared engine-core @0x8017331c (src/shared) */


DEFINE_func_8017334C()  /* dedup: shared engine-core @0x8017334c (src/shared) */


DEFINE_func_80173374()  /* dedup: shared engine-core @0x80173374 (src/shared) */


DEFINE_func_801733A4()  /* dedup: shared engine-core @0x801733a4 (src/shared) */


DEFINE_func_801733CC()  /* dedup: shared engine-core @0x801733cc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801733FC);

DEFINE_func_80173460()  /* dedup: shared engine-core @0x80173460 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801734BC);



void func_80173544(void *a0) {

    extern void (*D_8018D9F0[])(void);
    D_8018D9F0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173580()  /* dedup: shared engine-core @0x80173580 (src/shared) */


DEFINE_func_801735B8()  /* dedup: shared engine-core @0x801735b8 (src/shared) */


DEFINE_func_801735EC()  /* dedup: shared engine-core @0x801735ec (src/shared) */


DEFINE_func_80173648()  /* dedup: shared engine-core @0x80173648 (src/shared) */


void func_801736A8(void) {
}

DEFINE_func_801736B0()  /* dedup: shared engine-core @0x801736b0 (src/shared) */




s32 func_801736FC(void *a0) {

    extern void (*D_8018DA04[])(void);
    D_8018DA04[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173738()  /* dedup: shared engine-core @0x80173738 (src/shared) */


DEFINE_func_80173770()  /* dedup: shared engine-core @0x80173770 (src/shared) */


void func_801737B0(void) {
}

DEFINE_func_801737B8()  /* dedup: shared engine-core @0x801737b8 (src/shared) */




s32 func_801737E8(void *a0) {

    extern void (*D_8018DA10[])(void);
    D_8018DA10[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173824()  /* dedup: shared engine-core @0x80173824 (src/shared) */


DEFINE_func_8017385C()  /* dedup: shared engine-core @0x8017385c (src/shared) */


void func_801738D4(void) {
}

DEFINE_func_801738DC()  /* dedup: shared engine-core @0x801738dc (src/shared) */




s32 func_8017390C(void *a0) {

    extern void (*D_8018DA1C[])(void);
    D_8018DA1C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173948()  /* dedup: shared engine-core @0x80173948 (src/shared) */


DEFINE_func_80173980()  /* dedup: shared engine-core @0x80173980 (src/shared) */


DEFINE_func_801739D8()  /* dedup: shared engine-core @0x801739d8 (src/shared) */


void func_80173A20(void) {
}

DEFINE_func_80173A28()  /* dedup: shared engine-core @0x80173a28 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80173A60);



void func_80173B4C(void *a0) {

    extern void (*D_8018DA2C[])(void);
    D_8018DA2C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173B88()  /* dedup: shared engine-core @0x80173b88 (src/shared) */


DEFINE_func_80173BC0()  /* dedup: shared engine-core @0x80173bc0 (src/shared) */


DEFINE_func_80173C64()  /* dedup: shared engine-core @0x80173c64 (src/shared) */


DEFINE_func_80173CB4()  /* dedup: shared engine-core @0x80173cb4 (src/shared) */


DEFINE_func_80173E1C()  /* dedup: shared engine-core @0x80173e1c (src/shared) */


DEFINE_func_80173EF8()  /* dedup: shared engine-core @0x80173ef8 (src/shared) */


DEFINE_func_80174158()  /* dedup: shared engine-core @0x80174158 (src/shared) */


DEFINE_func_80174188()  /* dedup: shared engine-core @0x80174188 (src/shared) */


DEFINE_func_801741A8()  /* dedup: shared engine-core @0x801741a8 (src/shared) */


DEFINE_func_801741EC()  /* dedup: shared engine-core @0x801741ec (src/shared) */


void func_80174274(void) {
}

DEFINE_func_8017427C()  /* dedup: shared engine-core @0x8017427c (src/shared) */




s32 func_801742A4(void *a0) {

    extern void (*D_8018DA4C[])(void);
    D_8018DA4C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801742E0()  /* dedup: shared engine-core @0x801742e0 (src/shared) */


DEFINE_func_80174318()  /* dedup: shared engine-core @0x80174318 (src/shared) */


void func_80174354(void) {
}

DEFINE_func_8017435C()  /* dedup: shared engine-core @0x8017435c (src/shared) */




s32 func_80174384(void *a0) {

    extern void (*D_8018DA58[])(void);
    D_8018DA58[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801743C0()  /* dedup: shared engine-core @0x801743c0 (src/shared) */


DEFINE_func_801743F0()  /* dedup: shared engine-core @0x801743f0 (src/shared) */


void func_80174430(void) {
}

DEFINE_func_80174438()  /* dedup: shared engine-core @0x80174438 (src/shared) */




s32 func_80174474(void *a0) {

    extern void (*D_8018DA64[])(void);
    D_8018DA64[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801744B0()  /* dedup: shared engine-core @0x801744b0 (src/shared) */


DEFINE_func_801744E0()  /* dedup: shared engine-core @0x801744e0 (src/shared) */


void func_80174524(void) {
}

DEFINE_func_8017452C()  /* dedup: shared engine-core @0x8017452c (src/shared) */


DEFINE_func_80174554()  /* dedup: shared engine-core @0x80174554 (src/shared) */


DEFINE_func_80174584()  /* dedup: shared engine-core @0x80174584 (src/shared) */


DEFINE_func_801745AC()  /* dedup: shared engine-core @0x801745ac (src/shared) */


DEFINE_func_801745DC()  /* dedup: shared engine-core @0x801745dc (src/shared) */


DEFINE_func_80174604()  /* dedup: shared engine-core @0x80174604 (src/shared) */


DEFINE_func_80174630()  /* dedup: shared engine-core @0x80174630 (src/shared) */


DEFINE_func_80174650()  /* dedup: shared engine-core @0x80174650 (src/shared) */


DEFINE_func_80174674()  /* dedup: shared engine-core @0x80174674 (src/shared) */


DEFINE_func_80174684()  /* dedup: shared engine-core @0x80174684 (src/shared) */


DEFINE_func_801746A4()  /* dedup: shared engine-core @0x801746a4 (src/shared) */


DEFINE_func_801746DC()  /* dedup: shared engine-core @0x801746dc (src/shared) */


DEFINE_func_80174714()  /* dedup: shared engine-core @0x80174714 (src/shared) */


DEFINE_func_80174754()  /* dedup: shared engine-core @0x80174754 (src/shared) */


DEFINE_func_80174764()  /* dedup: shared engine-core @0x80174764 (src/shared) */


DEFINE_func_80174774()  /* dedup: shared engine-core @0x80174774 (src/shared) */


DEFINE_func_80174784()  /* dedup: shared engine-core @0x80174784 (src/shared) */


DEFINE_func_801747AC()  /* dedup: shared engine-core @0x801747ac (src/shared) */




s32 func_801747CC(void *a0) {

    extern void (*D_8018DA70[])(void);
    D_8018DA70[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80174808()  /* dedup: shared engine-core @0x80174808 (src/shared) */


void func_8017481C(void) {
}

DEFINE_func_80174824()  /* dedup: shared engine-core @0x80174824 (src/shared) */


DEFINE_func_8017484C()  /* dedup: shared engine-core @0x8017484c (src/shared) */




s32 func_80174888(void *a0) {

    extern void (*D_8018DA78[])(void);
    D_8018DA78[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801748C4()  /* dedup: shared engine-core @0x801748c4 (src/shared) */


void func_801748E4(void) {
}

DEFINE_func_801748EC()  /* dedup: shared engine-core @0x801748ec (src/shared) */




s32 func_8017496C(void *a0) {

    extern void (*D_8018DA80[])(void);
    D_8018DA80[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_801749A8()  /* dedup: shared engine-core @0x801749a8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801749C8);

DEFINE_func_80174B6C()  /* dedup: shared engine-core @0x80174b6c (src/shared) */


DEFINE_func_80174BBC()  /* dedup: shared engine-core @0x80174bbc (src/shared) */



// @class: struct
// @stuck: none — MATCH (27 ins) via func-ptr array fold extern void(*D_8018DA84[])()


void func_80174BF4(void * arg0)
{

    extern void (*D_8018DA84[])();
    M2C_FIELD(arg0, s32 *, 0xC) = 0x12C;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x20) = 0x155;
    M2C_FIELD(arg0, s16 *, 0x22) = 0x800;
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0;
    M2C_FIELD(arg0, s16 *, 0x30) = -0x28;
    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    D_8018DA84[M2C_FIELD(arg0, u8 *, 4)]();
}


DEFINE_func_80174C60()  /* dedup: shared engine-core @0x80174c60 (src/shared) */


DEFINE_func_80174C80()  /* dedup: shared engine-core @0x80174c80 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80174CB0);

DEFINE_func_80174E9C()  /* dedup: shared engine-core @0x80174e9c (src/shared) */


DEFINE_func_80174ED4()  /* dedup: shared engine-core @0x80174ed4 (src/shared) */


DEFINE_func_80174EF0()  /* dedup: shared engine-core @0x80174ef0 (src/shared) */




s32 func_80174F28(void *a0) {

    extern void (*D_8018DA8C[])(void);
    D_8018DA8C[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_80174F64()  /* dedup: shared engine-core @0x80174f64 (src/shared) */


DEFINE_func_80174FBC()  /* dedup: shared engine-core @0x80174fbc (src/shared) */


DEFINE_func_80175014()  /* dedup: shared engine-core @0x80175014 (src/shared) */


DEFINE_func_8017509C()  /* dedup: shared engine-core @0x8017509c (src/shared) */


DEFINE_func_80175114()  /* dedup: shared engine-core @0x80175114 (src/shared) */


DEFINE_func_80175150()  /* dedup: shared engine-core @0x80175150 (src/shared) */



extern s32 func_80175268(s32);

void func_80175184(s32* arg0) {

    extern void (*D_8018DA94[])(void*);
    u16 v1 = *(u16*)((u8*)arg0 + 2);
    if (v1 < 2) {
        D_8018DA94[v1](arg0);
    } else {
        func_80175268((s32)arg0);
    }
}


DEFINE_func_801751D8()  /* dedup: shared engine-core @0x801751d8 (src/shared) */



// @class: struct
// @stuck: none — MATCH (fn-ptr table indexed by D_80078EC0-1; param preserved in $s0 across 1st call)

extern void func_80146CA0(void *a0);

s32 func_80175218(void * param_1)
{

    extern u8 D_80078EC0;
    extern void (*D_8018DA9C[])(s32);
    s32 i = D_80078EC0 - 1;

    D_8018DA9C[i](param_1);
    ((void (*)(s32))func_80146CA0)(param_1);
}




s32 func_80175268(s32 param_1)
{

    extern u8 D_80078EC0;
    extern VoidFn D_8018DAB4[];
    *(u32 *)(param_1 + 0x44) |= 2;
    (*(VoidFn *)((s32)D_8018DAB4 + ((D_80078EC0 - 1) << 2)))();
}


DEFINE_func_801752BC()  /* dedup: shared engine-core @0x801752bc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80175308);

DEFINE_func_80175414()  /* dedup: shared engine-core @0x80175414 (src/shared) */


DEFINE_func_80175454()  /* dedup: shared engine-core @0x80175454 (src/shared) */


DEFINE_func_80175494()  /* dedup: shared engine-core @0x80175494 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801754A8);


extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_8017553C(s32 *param) {

    extern void (*D_8018DC04[])();
    D_8018DC04[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_80175590()  /* dedup: shared engine-core @0x80175590 (src/shared) */


DEFINE_func_80175624()  /* dedup: shared engine-core @0x80175624 (src/shared) */


DEFINE_func_80175668()  /* dedup: shared engine-core @0x80175668 (src/shared) */



extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_80175690(s32 *param) {

    extern void (*D_8018DC10[])();
    D_8018DC10[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_801756E4()  /* dedup: shared engine-core @0x801756e4 (src/shared) */


void func_80175798(void) {
}

DEFINE_func_801757A0()  /* dedup: shared engine-core @0x801757a0 (src/shared) */


DEFINE_func_801757E0()  /* dedup: shared engine-core @0x801757e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80175820);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801758FC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801759D8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80175AB8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80175DA8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80176144);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80176218);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80176734);

DEFINE_func_80176D00()  /* dedup: shared engine-core @0x80176d00 (src/shared) */


DEFINE_func_80176D94()  /* dedup: shared engine-core @0x80176d94 (src/shared) */


DEFINE_func_80176FF4()  /* dedup: shared engine-core @0x80176ff4 (src/shared) */


DEFINE_func_801770E0()  /* dedup: shared engine-core @0x801770e0 (src/shared) */


DEFINE_func_80177340()  /* dedup: shared engine-core @0x80177340 (src/shared) */


DEFINE_func_8017742C()  /* dedup: shared engine-core @0x8017742c (src/shared) */


extern void func_801776EC(u8 *a0);
void func_801775E0(s32 param_1, s32 param_2) {

    extern u8 D_8011F83B;
    extern u8 D_8011F837;
    extern u8 D_8011F7F0;
    s32 s0 = param_1;
    s32 pp = param_2;
    u8 *base = &D_8011F7F0;
    s16 sVar1; s32 t; s32 v;
    s32 c = D_8011F83B;
    if (c != 0) {
        if (c < 0) goto store;
        if (c >= 0xf7) goto store;
        if (c < 0xf3) goto store;
        goto docall;
    }
    if (D_8011F837 != 0x80) {
        *(u8 *)(s0 + 4) = 0xff;
        *(u8 *)(s0 + 6) = 0x10;
        *(u8 *)(s0 + 5) = 0x10;
        goto L684;
    }
    func_801776EC((u8 *)s0);
    goto L684;
docall:
    func_801776EC((u8 *)s0);
    goto L684;
store:
    *(u8 *)(s0 + 5) = 0xff;
    *(u8 *)(s0 + 6) = 0x10;
    *(u8 *)(s0 + 4) = 0x10;
L684:
    sVar1 = (s16)((u32)(base[0x47] * 9) >> 4);
    t = pp + 0x48;
    *(s16 *)(s0 + 0xe) = sVar1;
    *(s16 *)(s0 + 0xa) = t - sVar1;
    if (base[0x47] != 0) { s0 = param_1 + 0x14; v = 0xa0; } else { s0 = param_1 + 0x14; v = 0x40; }
    *(u8 *)(s0 + 6) = v;
    *(s16 *)(s0 + 0xa) = pp;
}


DEFINE_func_801776EC()  /* dedup: shared engine-core @0x801776ec (src/shared) */


DEFINE_func_80177784()  /* dedup: shared engine-core @0x80177784 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801777BC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801778A8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80177940);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80177AD4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80177B5C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80177DA8);

DEFINE_func_80177EA4()  /* dedup: shared engine-core @0x80177ea4 (src/shared) */


DEFINE_func_80177F84()  /* dedup: shared engine-core @0x80177f84 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80178004);

DEFINE_func_80178298()  /* dedup: shared engine-core @0x80178298 (src/shared) */


DEFINE_func_801783D0()  /* dedup: shared engine-core @0x801783d0 (src/shared) */



void func_80178438(u16 *arg0) {

    extern M2C_UNK D_801F49E4;
    func_8001534C(2, &D_801F49E4, 0x80, 0x88, 0, 0);
    func_800153CC(3, *arg0, 0xA8, 0x88, 0x40, 0);
}


DEFINE_func_8017849C()  /* dedup: shared engine-core @0x8017849c (src/shared) */


DEFINE_func_80178608()  /* dedup: shared engine-core @0x80178608 (src/shared) */


DEFINE_func_8017869C()  /* dedup: shared engine-core @0x8017869c (src/shared) */


DEFINE_func_80178744()  /* dedup: shared engine-core @0x80178744 (src/shared) */


DEFINE_func_801787D4()  /* dedup: shared engine-core @0x801787d4 (src/shared) */



// @class: regalloc-order
// @stuck: sll $v0,$s1,2 must be recomputed AFTER the call (target nops the delay slot)

extern void func_80019064(void *a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);


void func_80178840(int param_1) {

    extern int D_8018DC50;
    extern int D_8018DC5C[];
    register int p __asm__("$16");
    register int s1byte __asm__("$17");
    p = param_1;
    if ((*(unsigned short *)(p + 0x5c) & 1) != 0) {
        s1byte = *(unsigned char *)(p + 0x5e);
        if (s1byte == 0xc) {
            ((void (*)(int))func_80019064)((int)&D_8018DC50);
        }
        ((void (*)(int, int))func_80131E00)(p, D_8018DC5C[s1byte]);
    }
}


DEFINE_func_801788B8()  /* dedup: shared engine-core @0x801788b8 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (result pinned to $v0 forces call-result copy to $v1 + delay-slot zero)

extern int func_801789AC(void);

int func_80178970(void)
{

    extern s16 D_801F62F8;
    register int r __asm__("$2");
    int v;

    v = func_801789AC();
    r = 0;
    if (v != 0)
        r = D_801F62F8 == 0;
    return r;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801789AC);

extern void func_8017435C(void);
extern void func_801746A4(void);

// @class: struct
// @stuck: none — MATCH (pointer var forces &(*(int *)&D_8018DD48) into $s0, reused for store + arg-0xC)



s32 func_80178B18(s32 param_1, s32 param_2)
{
    extern void func_80178BF8(void);
    extern void func_80178CBC(s32 arg0, s32 arg1);
    extern u16 D_8018DD48;

    int *p = &(*(int *)&D_8018DD48);
    *p = ((int)param_2);
    func_80178BF8();
    func_801746A4();
    func_8017435C();
    ((void (*)(int, void *))func_80178CBC)(((int)param_1), (char *)p - 0xC);
}




// @class: regalloc-order
// @stuck: none — MATCH (pending verify)

s32 func_80178B70(s32 param_1, s32 param_2)
{
    extern void func_80178BF8();
    extern void func_80178CBC();
    extern int D_8018DD48;

    int *p = &D_8018DD48;
    *p = ((int)param_2);
    func_80178BF8();
    func_80178CBC(((int)param_1), p - 3);
}


DEFINE_func_80178BB8()  /* dedup: shared engine-core @0x80178bb8 (src/shared) */


extern void func_80016714(void *a0, s32 a1);

// @class: other
// @stuck: none — MATCH (49 ins). Key: init loop pointers via &D_SYMBOL (not (T*)0x801da788 raw int, which emits lui+ori instead of lui%hi+addiu%lo).



void func_80178BF8(s32 _unused0, s32 _unused1)
{
    extern void func_8017B1D8(void);
    extern short D_801F636C;
    extern int D_801F5FF8;
    extern short D_801F6008;
    extern short D_801F6004;
    extern short D_801F6000;
    extern short D_801F5FFC;
    extern int D_801F6214;
    extern int D_801F6010;
    extern s16 D_801F5FF0;
    extern short D_801F5FE8;
    extern short D_801F5FEC;
    extern int D_801F62C8;
    extern unsigned int D_801F6060;
    extern unsigned short D_801F5FE6;

    unsigned short *puVar1;
    int iVar2;
    unsigned int *puVar3;

    iVar2 = 9;
    puVar3 = &D_801F6060;
    D_801F636C = 0;
    D_801F5FF8 = 0;
    D_801F6008 = 0;
    D_801F6004 = 0;
    D_801F6000 = 0;
    D_801F5FFC = 0;
    D_801F6214 = 1;
    D_801F6010 = 0;
    (*(short *)&D_801F5FF0) = 0;
    do {
        *puVar3 = 0;
        iVar2 = iVar2 + -1;
        puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
    iVar2 = 0x1ff;
    puVar1 = &D_801F5FE6;
    do {
        *puVar1 = 0;
        iVar2 = iVar2 + -1;
        puVar1 = puVar1 + -1;
    } while (-1 < iVar2);
    D_801F5FE8 = 0;
    D_801F5FEC = 0;
    ((void (*)(int *, int))func_80016714)(&D_801F62C8, 0x14);
    func_8017B1D8();
}


extern M2C_UNK func_80178D40(s32 arg0, s32 arg1);

void func_80178CBC(s32 arg0, s32 arg1) {

    extern s32 D_801F5BE0;
    extern short D_801F636C;
    D_801F5BE0 = arg1;
    do {
        func_80178D40(arg0, D_801F5BE0);
    } while (D_801F636C == 3);
}



extern void func_80174714(void);

void func_80178D18(void) {

    extern short D_801F636C;
    D_801F636C = 0;
    func_80174714();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80178D40);

DEFINE_func_80179B28()  /* dedup: shared engine-core @0x80179b28 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80179B74);

DEFINE_func_80179D30()  /* dedup: shared engine-core @0x80179d30 (src/shared) */


DEFINE_func_80179D78()  /* dedup: shared engine-core @0x80179d78 (src/shared) */


DEFINE_func_80179DCC()  /* dedup: shared engine-core @0x80179dcc (src/shared) */


DEFINE_func_80179DF8()  /* dedup: shared engine-core @0x80179df8 (src/shared) */


DEFINE_func_80179E1C()  /* dedup: shared engine-core @0x80179e1c (src/shared) */


DEFINE_func_80179E48()  /* dedup: shared engine-core @0x80179e48 (src/shared) */


DEFINE_func_80179E74()  /* dedup: shared engine-core @0x80179e74 (src/shared) */


DEFINE_func_80179EA0()  /* dedup: shared engine-core @0x80179ea0 (src/shared) */


DEFINE_func_80179EE8()  /* dedup: shared engine-core @0x80179ee8 (src/shared) */


DEFINE_func_80179F14()  /* dedup: shared engine-core @0x80179f14 (src/shared) */


DEFINE_func_80179F44()  /* dedup: shared engine-core @0x80179f44 (src/shared) */


DEFINE_func_80179F6C()  /* dedup: shared engine-core @0x80179f6c (src/shared) */


DEFINE_func_80179F98()  /* dedup: shared engine-core @0x80179f98 (src/shared) */


DEFINE_func_80179FEC()  /* dedup: shared engine-core @0x80179fec (src/shared) */


DEFINE_func_8017A040()  /* dedup: shared engine-core @0x8017a040 (src/shared) */



extern void func_80179B74(s16 *a0);

void func_8017A094(s32 arg0) {

    extern s32 D_801F600C;
    s16 sp10;

    D_801F600C = arg0;
    sp10 = 0x15;
    func_80179B74(&sp10);
}



extern void func_80179B74(s16 *a0);

void func_8017A0C4(s32 arg0) {

    extern s32 D_801F600C;
    s16 sp10;

    D_801F600C = arg0;
    sp10 = 0x16;
    func_80179B74(&sp10);
}


DEFINE_func_8017A0F4()  /* dedup: shared engine-core @0x8017a0f4 (src/shared) */


DEFINE_func_8017A11C()  /* dedup: shared engine-core @0x8017a11c (src/shared) */



extern void func_80179B74(s16 *a0);

void func_8017A144(s32 a0) {

    extern s32 D_801F6034;
    s16 sp10;
    sp10 = 0x1B;
    func_80179B74(&sp10);
    D_801F6034 = a0;
}


DEFINE_func_8017A180()  /* dedup: shared engine-core @0x8017a180 (src/shared) */


DEFINE_func_8017A1A8()  /* dedup: shared engine-core @0x8017a1a8 (src/shared) */


DEFINE_func_8017A1D0()  /* dedup: shared engine-core @0x8017a1d0 (src/shared) */


DEFINE_func_8017A1F8()  /* dedup: shared engine-core @0x8017a1f8 (src/shared) */


DEFINE_func_8017A220()  /* dedup: shared engine-core @0x8017a220 (src/shared) */


DEFINE_func_8017A248()  /* dedup: shared engine-core @0x8017a248 (src/shared) */


DEFINE_func_8017A270()  /* dedup: shared engine-core @0x8017a270 (src/shared) */


DEFINE_func_8017A298()  /* dedup: shared engine-core @0x8017a298 (src/shared) */


DEFINE_func_8017A2C0()  /* dedup: shared engine-core @0x8017a2c0 (src/shared) */


DEFINE_func_8017A2E8()  /* dedup: shared engine-core @0x8017a2e8 (src/shared) */


DEFINE_func_8017A310()  /* dedup: shared engine-core @0x8017a310 (src/shared) */


DEFINE_func_8017A338()  /* dedup: shared engine-core @0x8017a338 (src/shared) */


DEFINE_func_8017A360()  /* dedup: shared engine-core @0x8017a360 (src/shared) */


DEFINE_func_8017A388()  /* dedup: shared engine-core @0x8017a388 (src/shared) */




s32 func_8017A3B0(void) {

    extern s16 D_801F5FF0;
    switch (D_801F5FF0) {
    case 0:
        return 1;
    case 1:
        return 0;
    default:
        return 1;
    }
}



// @class: regalloc-order
// @stuck: none — MATCH


extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);

int func_8017A3D8(void)
{

    extern short D_801F602C;
    extern short D_801F6028;
    switch (D_801F602C) {
    case 0:
        func_800D0CA0(1);
        D_801F602C = D_801F602C + 1;
        return 0;
    case 100:
    {
        register int a __asm__("$4");
        a = D_801F6028;
        if (a != -1) {
            return func_8001AAA0() != 0;
        }
        return func_800D0CE0() == 1;
    }
    default:
        D_801F602C = D_801F602C + 1;
        if (D_801F602C < 0x1E) {
            return 0;
        }
        D_801F602C = 100;
        return 0;
    }
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017A4AC);

DEFINE_func_8017AD0C()  /* dedup: shared engine-core @0x8017ad0c (src/shared) */


DEFINE_func_8017ADE8()  /* dedup: shared engine-core @0x8017ade8 (src/shared) */


DEFINE_func_8017AE08()  /* dedup: shared engine-core @0x8017ae08 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017AE2C);

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);

// @class: plumbing
// @stuck: none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_801F606C;
    extern s16 D_801F606E;
    extern s16 D_801F6070;
    extern s16 D_801F6064;
    extern s16 D_801F6066;
    extern s16 D_801F6068;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801F606C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801F606E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801F6070, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801F6064, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801F6066, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801F6068, (s32)((s16)param_2));
}


extern void func_8012A418(void);

void func_8017B1D8(void) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern s16 D_801F5FF4;
    extern u16 D_801F6074;
    extern u16 D_801F6076;
    extern u16 D_801F6078;
    extern s16 D_801F62F8;
    func_8012A418();
    D_801F62F8 = 0;
    D_801F5FF4 = 0;
    D_801F6074 = D_80126B5E;
    D_801F6076 = D_80126B62;
    D_801F6078 = D_80126B66;
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8017B614(void *, s32);

// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @stuck: none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.

typedef struct { u8 b[8]; } Blk8_8017B238;

s32 func_8017B238(s32 param_1, s32 param_2)
{

    extern s16 D_801F5FF4;
    extern s16 D_801F62F8;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018DD4C[];
    extern s16 D_801F606C;
    extern s16 D_801F6064;
    extern u8 D_8012694C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238 *)&buf[0] = *(Blk8_8017B238 *)src;
        *(Blk8_8017B238 *)&buf[8] = *(Blk8_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018DD4C[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018DD4C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801F606C;
        s16 *p78C = &D_801F6064;
        *(Blk8_8017B238 *)p794 = *(Blk8_8017B238 *)&buf[0];
        *(Blk8_8017B238 *)p78C = *(Blk8_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801F62F8 = 1;
        D_801F5FF4 = 0;
    }
}



// @class: struct
// @stuck: none — MATCH (74 ins)

typedef struct { s16 a, b, c, d; } SV4_8017B368;      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
typedef struct { SV4_8017B368 x, y; } Pair16;         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{

    extern s16 D_801F5FF4;
    extern s16 D_801F62F8;
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801F6014;
    extern SV4_8017B368 D_801F601C;
    extern s16 D_801F606C;
    extern s16 D_801F6064;
    extern u16 D_8018DD4C;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801F6014;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801F601C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018DD4C)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018DD4C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801F606C) = loc0;
    (*(SV4_8017B368 *)&D_801F6064) = loc1;
    D_801F62F8 = 1;
    D_801F5FF4 = 0;
}




s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801F6014;
    extern SV4_8017B368 D_801F601C;
    extern s16 D_801F606C;
    extern s16 D_801F6064;
    extern u16 D_8018DD4C;
    extern s16 D_801F5FF4;
    extern s16 D_801F62F8;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801F6014;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801F601C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018DD4C)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018DD4C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801F606C) = loc0;
    (*(SV4_8017B368 *)&D_801F6064) = loc1;
    D_801F62F8 = 1;
    D_801F5FF4 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801F606C).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801F606C).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801F606C).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801F6064).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801F6064).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801F6064).c;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017B614);



// @class: plumbing
// @stuck: none — MATCH



void func_8017B7A8(void)
{

    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8 D_8012694C;
    extern s16 D_801F5FF4;
    extern s16 D_801F606C;
    extern s16 D_801F606E;
    extern s16 D_801F6070;
    extern s16 D_801F6064;
    extern s16 D_801F6066;
    extern s16 D_801F6068;
    D_8012694C = 1;
    D_801F5FF4 = 0;
    D_801F606C = (s16) D_80114F30;
    D_801F606E = (s16) D_80114F34;
    D_801F6070 = (s16) D_80114F38;
    D_801F6064 = (s16) D_80114F24;
    D_801F6066 = (s16) D_80114F28;
    D_801F6068 = (s16) D_80114F2C;
}




void func_8017B824(void) {

    extern s32 D_801151D4;
    extern s16 D_801F6084;
    extern s16 D_801F6086;
    extern s16 D_801F6088;
    extern s16 D_801F608C;
    extern s16 D_801F608E;
    extern s16 D_801F6090;
    D_801F6084 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801F6086 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801F6088 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801F608C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801F608E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801F6090 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH



void func_8017B880(void)
{

    extern s16 D_801F6084;
    extern s16 D_801F6086;
    extern s16 D_801F6088;
    extern s16 D_801F608C;
    extern s16 D_801F608E;
    extern s16 D_801F6090;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    D_80114F30 = D_801F6084;
    D_80114F34 = D_801F6086;
    D_80114F38 = D_801F6088;
    D_80114F24 = D_801F608C;
    D_80114F28 = D_801F608E;
    D_80114F2C = D_801F6090;
}



typedef struct { unsigned char b[8]; } S8_8017B8E8;


s32 func_8017B8E8(s32 src) {

    extern s16 D_801F6064;
    extern s16 D_801F606C;
    (*(S8_8017B8E8 *)&D_801F606C) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801F6064) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)




void func_8017B940(void)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u16 D_801F6074;
    extern u16 D_801F6076;
    extern u16 D_801F6078;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8  D_8012694C;
    extern s16 D_801F5FF4;
    extern short D_801F607C;
    extern short D_801F607E;
    extern short D_801F6080;
    extern s16 D_801F606C;
    extern s16 D_801F606E;
    extern s16 D_801F6070;
    extern s16 D_801F6064;
    extern s16 D_801F6066;
    extern s16 D_801F6068;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801F6074);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801F6076);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801F6078);
    (*(s16 *)&D_801F607C) = buf[0];
    (*(s16 *)&D_801F607E) = buf[1];
    (*(s16 *)&D_801F6080) = buf[2];
    D_801F606C = D_80114F30 + buf[0];
    D_801F5FF4 = 0;
    D_801F606E = D_80114F34 + buf[1];
    D_801F6070 = D_80114F38 + buf[2];
    D_801F6064 = D_80114F24 + buf[0];
    D_801F6066 = D_80114F28 + buf[1];
    D_801F6068 = D_80114F2C + buf[2];
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017BA3C);

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_80049CAC(s32 a0, s32 a1);

typedef struct { s16 a, b, c, d; } SV4_8017BB34;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017BB34;



s32 func_8017BB34(s32 param_1, s32 param_2)
{

    extern s32 D_801F6014;
    extern SV4_8017B368 D_801F601C;
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801F601C)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801F6014) = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    (*(SV4_8017BB34*)&D_801F601C) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0


void func_8017BC38(int param_1)
{

    extern void (*D_801F603C[10])(int);
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801F603C;
    do {
        if (*p != (void (*)(int))0) {
            (*p)(param_1);
        }
        i = i + 1;
        p = p + 1;
    } while (i < 10);
    return;
}



// @class: plumbing
// @stuck: none — MATCH (expected); short-typed global increment + signed compare, store-2 on overflow

extern void func_8017B0E4(int, int);

void func_8017BCA0(int param_1) {

    extern s16 D_801F5FF4;
    extern s16 D_801F62F8;
    func_8017B0E4(param_1, 0xC);
    D_801F5FF4 = D_801F5FF4 + 1;
    if (D_801F5FF4 >= 0x1F) {
        D_801F62F8 = 2;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)


extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{

    extern s16 D_801F5FF4;
    extern s16 D_801F62F8;
    func_8017B0E4(param_1, 6);
    D_801F5FF4 = D_801F5FF4 + 1;
    if (0x18 < D_801F5FF4) {
        func_8012A4BC();
        D_801F62F8 = 0;
    }
    return;
}



// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);



void func_8017BD50(int param_1)
{

    extern s16 D_801F5FF4;
    extern void (*D_801F6038)(void);
    extern short D_801F607C;
    extern short D_801F607E;
    extern short D_801F6080;
    extern s16 D_801F62F8;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    func_8017B0E4(param_1, 6);
    D_801F5FF4 = D_801F5FF4 + 1;
    if (D_801F5FF4 >= 0x19) {
        if (D_801F6038 != 0) {
            (*D_801F6038)();
        } else {
            D_80114F30 = D_80114F30 + D_801F607C;
            D_80114F34 = D_80114F34 + D_801F607E;
            D_80114F38 = D_80114F38 + D_801F6080;
            D_80114F24 = D_80114F24 + D_801F607C;
            D_80114F28 = D_80114F28 + D_801F607E;
            D_80114F2C = D_80114F2C + D_801F6080;
            func_8012A4BC();
        }
        D_801F62F8 = 0;
    }
}




void func_8017BE60(void *a0) {

    extern void (*D_8018DDEC[])(void);
    D_8018DDEC[*(u8 *)((s32)a0 + 0x4)]();
}


void func_8017BE9C(void) {
}

void func_8017BEA4(void) {
}

void func_8017BEAC(void) {
}

void func_8017BEB4(void) {
}

/* func_8017BEBC — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
 * Outer loop: per-part bbox -> RTPT/RTPS projection -> g.otz + screen cull.
 * Inner loop: per-prim RTPT -> g.flag/nclip/g.opz cull -> switch(code&7):
 *   4,5=POLY_F3 / 6,7=POLY_FT3 / 0,1=POLY_F4 / 2,3=POLY_FT4 -> OT insert.
 * GTE ops are verbatim PsyQ inline_c.h macro bodies (rtps/rtpt/nclip spelled via
 * the project gas macros from include/gte_macros.inc, pulled in by common.h).*
 * CLOSED 2026-07-13 (Phase 26 session 8, Fable5 Max): match_one MATCH 952/952, PIN-FREE.
 * The close=2 residual (two transposed preheader addius) was a global.c allocno-priority TIE:
 *   pseudo 228 = &g.sz1 (sp+0xD0): refs 13, live_length 783 -> pri int(3*13*10000/783) = 498
 *   pseudo 230 = &g.sz2 (sp+0xD4): refs 13, live_length 782 -> pri int(3*13*10000/782) = 498
 * Tie -> creation-order tie-break -> sz1 allocated first (t8) = swapped. The shipped workaround
 * permuted the stsz3 operand list (creation sz0,sz2,sz1) which fixed allocation but transposed
 * the preheader emission (close=2). TRUE FIX: natural operand order restored (emission correct)
 * + ONE zero-byte `__asm__ volatile ("")` inside the common live range (between two existing GTE
 * volatile asms, so no new cse/sched barrier) -> L 784/783 -> pri 497 vs 498 -> the tie SPLITS
 * toward the shorter-lived allocno (sz2) -> sz2 first -> t8. All 10 grants cascade. The slider
 * emits nothing (#APP/#NO_APP only); the tie can ONLY split toward the target's allocation
 * because the later-defined pseudo always has the shorter range. Cookbook §47.
 */

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv3c(r0) __asm__ volatile (         \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 8( %0 );"                          \
    "lwc2 $3, 12( %0 );"                         \
    "lwc2 $4, 16( %0 );"                         \
    "lwc2 $5, 20( %0 )"                          \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsxy3c(r0) __asm__ volatile (       \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 4( %0 );"                         \
    "swc2 $14, 8( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_f3(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_ft3(r0) __asm__ volatile (    \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_f4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile ( \
    "swc2 $16, 0( %0 );"                         \
    "swc2 $17, 0( %1 );"                         \
    "swc2 $18, 0( %2 );"                         \
    "swc2 $19, 0( %3 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) \
    : "memory" )

#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

void func_8017BEBC(s32 arg0)
{
    typedef struct { s16 vx, vy; } DVECTOR2;
    typedef struct { s16 vx, vy, vz, pad; } SVECTOR2;
    typedef struct { s16 m[3][3]; s32 t[3]; } MATRIX2;
    typedef struct { u32 xx, yy, zz; u32 nprim; u32 *prim; } Part;
    typedef struct { u32 w0, w1, w2; } Prim;
    typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2; } PolyF3;
    typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; } PolyFT3;
    typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2, x3, y3; } PolyF4;
    typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; s16 x3, y3; u16 uv3, p3; } PolyFT4;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;   /* TU-visible spelling (engine_core.h + ov_SC01_000.c col-0); unsigned access forced at use — §8d sub-class (b) */

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 nparts;
    s32 j;
    u32 nprim;
    u32 i;
    Part *part;
    Prim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w, code;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    part = *(Part **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        box[0].vx = mn; box[0].vy = mny;
        box[1].vx = mx; box[1].vy = mny;
        box[2].vx = mn; box[2].vy = mny;
        box[3].vx = mx; box[3].vy = mny;
        box[4].vx = mn; box[4].vy = my;
        box[5].vx = mx; box[5].vy = my;
        box[6].vx = mn; box[6].vy = my;
        box[7].vx = mx; box[7].vy = my;
        wy = wz >> 16;
        box[0].vz = wz;
        box[1].vz = wz;
        box[4].vz = wz;
        box[5].vz = wz;
        box[2].vz = wy;
        box[3].vz = wy;
        box[6].vz = wy;
        box[7].vz = wy;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();
        gte_stsxy(&sxy[3]);
        gte_ldv3c(&box[4]);
        __asm__ volatile ("");   /* §45-B live-length slider: +1 static insn splits the 228/230 allocno-priority tie (498/498 -> 497/498) */
        gte_rtpt();
        gte_stsxy3(&sxy[4], &sxy[5], &sxy[6]);
        gte_ldv0(&box[7]);
        gte_rtps();
        gte_stsxy(&sxy[7]);
        gte_stszotz(&g.otz);

        if (lim >= g.otz) {
            xa32 = sxy[0].vx;
            xb32 = sxy[1].vx;
            if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
            t32 = sxy[2].vx;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            t32 = sxy[3].vx;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            xa32 = sxy[4].vx;
            xb32 = sxy[5].vx;
            if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
            t32 = sxy[6].vx;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            t32 = sxy[7].vx;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            mnc = xmn1;
            if (xmn2 < xmn1) mnc = xmn2;
            mxc = xmx1;
            if (mxc < xmx2) mxc = xmx2;
            if ((s16)mxc >= -0xA0 && (s16)mnc < 0xA1) {
                xa32 = sxy[0].vy;
                xb32 = sxy[1].vy;
                if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
                t32 = sxy[2].vy;
                if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
                t32 = sxy[3].vy;
                if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
                xa32 = sxy[4].vy;
                xb32 = sxy[5].vy;
                if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
                t32 = sxy[6].vy;
                if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
                t32 = sxy[7].vy;
                if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
                mnc = xmn1;
                if (xmn2 < xmn1) mnc = xmn2;
                mxc = xmx1;
                if (mxc < xmx2) mxc = xmx2;
                if ((s16)mxc >= -0x78 && (s16)mnc < 0x79) {
                    prim = (Prim *)part->prim;
                    nprim = part->nprim;
                    for (i = 0; i < nprim; i++, prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        gte_ldv3(va, vb, vc);
                        gte_rtpt();
                        gte_stflg(&g.flag);
                        if (!(g.flag & 0x7F85E000)) {
                            gte_nclip();
                            code = w & 7;
                            vd = vtx + (w & 0xFFF8);
                            gte_stopz(&g.opz);
                            if (g.opz > 0) {
                                switch (code) {
                                case 4:
                                case 5:
                                    gte_stsxy3_f3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((PolyF3 *)pkt)->x0 > ((PolyF3 *)pkt)->x1) {
                                        mx = ((PolyF3 *)pkt)->x0;
                                        mn = ((PolyF3 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyF3 *)pkt)->x0;
                                        mx = ((PolyF3 *)pkt)->x1;
                                    }
                                    if (((PolyF3 *)pkt)->x2 > mx) mx = ((PolyF3 *)pkt)->x2;
                                    else if (((PolyF3 *)pkt)->x2 < mn) mn = ((PolyF3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyF3 *)pkt)->y0 > ((PolyF3 *)pkt)->y1) {
                                            my = ((PolyF3 *)pkt)->y0;
                                            mny = ((PolyF3 *)pkt)->y1;
                                        } else {
                                            mny = ((PolyF3 *)pkt)->y0;
                                            my = ((PolyF3 *)pkt)->y1;
                                        }
                                        if (((PolyF3 *)pkt)->y2 > my) my = ((PolyF3 *)pkt)->y2;
                                        else if (((PolyF3 *)pkt)->y2 < mny) mny = ((PolyF3 *)pkt)->y2;
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za, zb;
                                            u32 *otp;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code != 4) g.opz = za + 0x200;
                                            ((PolyF3 *)pkt)->rgbc = prim->w0;
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x4000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x14;
                                        }
                                    }
                                    break;
                                case 6:
                                case 7:
                                    gte_stsxy3_ft3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((PolyFT3 *)pkt)->x0 > ((PolyFT3 *)pkt)->x1) {
                                        mx = ((PolyFT3 *)pkt)->x0;
                                        mn = ((PolyFT3 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyFT3 *)pkt)->x0;
                                        mx = ((PolyFT3 *)pkt)->x1;
                                    }
                                    if (((PolyFT3 *)pkt)->x2 > mx) mx = ((PolyFT3 *)pkt)->x2;
                                    else if (((PolyFT3 *)pkt)->x2 < mn) mn = ((PolyFT3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyFT3 *)pkt)->y0 > ((PolyFT3 *)pkt)->y1) {
                                            my = ((PolyFT3 *)pkt)->y0;
                                            mny = ((PolyFT3 *)pkt)->y1;
                                        } else {
                                            mny = ((PolyFT3 *)pkt)->y0;
                                            my = ((PolyFT3 *)pkt)->y1;
                                        }
                                        if (((PolyFT3 *)pkt)->y2 > my) my = ((PolyFT3 *)pkt)->y2;
                                        else if (((PolyFT3 *)pkt)->y2 < mny) mny = ((PolyFT3 *)pkt)->y2;
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za, zb;
                                            u32 *otp;
                                            u32 *tp;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code == 7) g.opz = za + 0x200;
                                            tp = (u32 *)prim->w0;
                                            ((PolyFT3 *)pkt)->rgbc = tp[0];
                                            ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                            ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                            ((PolyFT3 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x20;
                                        }
                                    }
                                    break;
                                case 0:
                                case 1:
                                    gte_stsxy3_f4(pkt);
                                    gte_ldv0(vd);
                                    gte_rtps();
                                    if (((PolyF4 *)pkt)->x0 > ((PolyF4 *)pkt)->x1) {
                                        mx = ((PolyF4 *)pkt)->x0;
                                        mn = ((PolyF4 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyF4 *)pkt)->x0;
                                        mx = ((PolyF4 *)pkt)->x1;
                                    }
                                    if (((PolyF4 *)pkt)->x2 > mx) mx = ((PolyF4 *)pkt)->x2;
                                    else if (((PolyF4 *)pkt)->x2 < mn) mn = ((PolyF4 *)pkt)->x2;
                                    if (((PolyF4 *)pkt)->y0 > ((PolyF4 *)pkt)->y1) {
                                        my = ((PolyF4 *)pkt)->y0;
                                        mny = ((PolyF4 *)pkt)->y1;
                                    } else {
                                        mny = ((PolyF4 *)pkt)->y0;
                                        my = ((PolyF4 *)pkt)->y1;
                                    }
                                    if (((PolyF4 *)pkt)->y2 > my) my = ((PolyF4 *)pkt)->y2;
                                    else if (((PolyF4 *)pkt)->y2 < mny) mny = ((PolyF4 *)pkt)->y2;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyF4 *)pkt)->x3);
                                        if (((PolyF4 *)pkt)->x3 < mn) mn = ((PolyF4 *)pkt)->x3;
                                        else if (mx < ((PolyF4 *)pkt)->x3) mx = ((PolyF4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyF4 *)pkt)->y3 < mny) mny = ((PolyF4 *)pkt)->y3;
                                            else if (my < ((PolyF4 *)pkt)->y3) my = ((PolyF4 *)pkt)->y3;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                ((PolyF4 *)pkt)->rgbc = prim->w0;
                                                otp = (u32 *)(((za >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x5000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x18;
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_ldv0(vd);
                                    gte_rtps();
                                    if (tmpxy[0].vx > tmpxy[1].vx) {
                                        mx = tmpxy[0].vx;
                                        mn = tmpxy[1].vx;
                                    } else {
                                        mn = tmpxy[0].vx;
                                        mx = tmpxy[1].vx;
                                    }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (tmpxy[0].vy > tmpxy[1].vy) {
                                        my = tmpxy[0].vy;
                                        mny = tmpxy[1].vy;
                                    } else {
                                        mny = tmpxy[0].vy;
                                        my = tmpxy[1].vy;
                                    }
                                    if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                    else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyFT4 *)pkt)->x3);
                                        if (((PolyFT4 *)pkt)->x3 < mn) mn = ((PolyFT4 *)pkt)->x3;
                                        else if (mx < ((PolyFT4 *)pkt)->x3) mx = ((PolyFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                            else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                u32 *tp;
                                                u32 uvw;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code == 3) g.opz = za + 0x200;
                                                *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4 *)pkt)->rgbc = tp[0];
                                                ((PolyFT4 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((PolyFT4 *)pkt)->uv2 = uvw;
                                                ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    D_800A5E60 = pkt;
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017CD9C);



void func_8017CDBC(void *a0) {

    extern void (*D_8018DE48[])(void);
    D_8018DE48[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017CDF8);


extern s32 func_800167F0(s32 a0);

s32 func_8017CE3C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




void func_8017CE60(void *a0) {

    extern void (*D_8018DE50[])(void);
    D_8018DE50[*(u8 *)((s32)a0 + 0x15)]();
}


s32 func_8017CE9C(void *a0) {
    *(s32 *)((s32)a0 + 0x28) = 0xa;
    *(u8 *)((s32)a0 + 0x15) = *(u8 *)((s32)a0 + 0x15) + 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017CEB8(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_8017CF34(void) {
    func_800D1EBC();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017CF54);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017CF7C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017CFA4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017D040);



void func_8017D0F4(void *a0) {

    extern void (*D_8018DF04[])(void);
    D_8018DF04[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017D130);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017D1D0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017D4E4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017D67C);



void func_8017D868(void *a0) {

    extern void (*D_8018E274[])(void);
    D_8018E274[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017D8A4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017DA30);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017DC1C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017F3D4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017F5D4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017F9AC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8017FDF8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801802EC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801805D4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80180924);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80180CFC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80181148);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8018163C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80181924);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80181C74);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80181E64);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80182000);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80182158);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80182268);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801823F8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801826E0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801828A4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80182B8C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80182D4C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80182F3C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80183374);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80183814);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8018881C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189098);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_801890FC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189708);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8018984C);



void func_80189AC8(void *a0) {

    extern void (*D_8018EB2C[])(void);
    D_8018EB2C[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80189B04(void *a0) {

    extern void (*D_8018EB44[])(void);
    D_8018EB44[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189B40);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189C00);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189C14);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189C28);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189C3C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189C50);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189C64);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189C78);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189C8C);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189CA0);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189CB4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189CC8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189CDC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189CF0);

extern void func_8017D040(s8 a0);
void func_80189D18(void) {
    func_8017D040(0);
}


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189D38);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189D58);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189D78);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189D98);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189DB8);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189EF4);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189F70);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_80189FDC);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8018A124);

INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8018A150);

void func_8018A284(void) {
}



void func_8018A28C(void *a0) {

    extern void (*D_8018EB54[])(void);
    D_8018EB54[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012AD50(void *a0);
    void func_8018A2C8(u8 *a0) {
        *(s16 *)(a0 + 0xFC) = 0;
        *(u16 *)(a0 + 0x72) |= 0x1000;
        ((void (*)(void))func_8012AD50)();
    }


INCLUDE_ASM("asm/ov_SC07_006/nonmatchings/ov_SC07_006", func_8018A2F4);
