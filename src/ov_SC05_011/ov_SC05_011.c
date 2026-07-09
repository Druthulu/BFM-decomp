#include "common.h"
#include "../shared/engine_core.h"

DEFINE_func_80128158()  /* dedup: shared engine-core @0x80128158 (src/shared) */

DEFINE_func_80128178()  /* dedup: shared engine-core @0x80128178 (src/shared) */

DEFINE_func_80128198()  /* dedup: shared engine-core @0x80128198 (src/shared) */

DEFINE_func_801281B8()  /* dedup: shared engine-core @0x801281B8 (src/shared) */

DEFINE_func_801281D8()  /* dedup: shared engine-core @0x801281D8 (src/shared) */

DEFINE_func_801281F8()  /* dedup: shared engine-core @0x801281F8 (src/shared) */


extern s32 D_8019AB88;

s32 func_80128218(void) {
    return D_8019AB88;
}


DEFINE_func_80128228()  /* dedup: shared engine-core @0x80128228 (src/shared) */

DEFINE_func_80128248()  /* dedup: shared engine-core @0x80128248 (src/shared) */

DEFINE_func_80128268()  /* dedup: shared engine-core @0x80128268 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80128288);

DEFINE_func_801282CC()  /* dedup: shared engine-core @0x801282CC (src/shared) */

DEFINE_func_801282EC()  /* dedup: shared engine-core @0x801282EC (src/shared) */

DEFINE_func_8012832C()  /* dedup: shared engine-core @0x8012832C (src/shared) */

DEFINE_func_80128420()  /* dedup: shared engine-core @0x80128420 (src/shared) */

DEFINE_func_801284B8()  /* dedup: shared engine-core @0x801284B8 (src/shared) */

DEFINE_func_801284F0()  /* dedup: shared engine-core @0x801284F0 (src/shared) */

DEFINE_func_8012853C()  /* dedup: shared engine-core @0x8012853C (src/shared) */

DEFINE_func_80128564()  /* dedup: shared engine-core @0x80128564 (src/shared) */

DEFINE_func_801285D4()  /* dedup: shared engine-core @0x801285D4 (src/shared) */


extern s32 func_800D18DC(void);
extern void func_8014607C(void);
extern void func_801287B8(void);
extern s32 func_80011A3C(void);
extern s32 D_8019BD2C;

void func_801285E4(void)
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
        "jal   func_800D18DC\n"
        "lui   $at, %%hi(D_8019BD2C)\n"
        "sw    $v0, %%lo(D_8019BD2C)($at)\n"
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
        "lui   $v0, %%hi(D_8019BD2C)\n"
        "lw    $v0, %%lo(D_8019BD2C)($v0)\n"
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


// @class: other
// @stuck: none — MATCH (handwritten full inline-asm scratchpad-stack-switch wrapper w/ branch)
/*
 * HANDWRITTEN scratchpad-stack-switch dispatcher (same idiom as func_80128564 /
 * the func_8014ED28 family): repoints $sp into the D-cache scratchpad stack held
 * at *(0x1F8003FC), calls func_800D19F0, stashes its $v0 result through D_8019BD2C,
 * restores $sp, then dispatches on the stored value:
 *   if (D_8019BD2C != 0)  { func_8001903C(); func_80018FC8(); }
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
        "lui   $at, %%hi(D_8019BD2C)\n"
        "sw    $v0, %%lo(D_8019BD2C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_8019BD2C)\n"
        "lw    $v0, %%lo(D_8019BD2C)($v0)\n"
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
// @stuck: none — MATCH (62 ins). D_8019D170 read needed the address REMATERIALIZED
//   (lui;addiu;lw 0(reg), not the folded lui;lw %lo) AND pinned to $a0. volatile forces the
//   remat; register __asm__("$4") forces the a0 allocation (gcc otherwise picks v0). Both levers
//   required — pin-alone folds, volatile-alone lands in v0.

extern s32 D_80126B58;
extern s32 D_8019D170;
extern u16 D_800B99DA;
extern u8 D_800B9A64;

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
        /* D_8019D170 read: the target materializes &sym into $a0 then lw 0($a0) (not the folded
         * lui;lw %lo). volatile forces the rematerialize; the $4 pin forces the a0 allocation. */
        register volatile s32 *p __asm__("$4") = &D_8019D170;
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
extern s32 D_8019AB88;
extern u8 D_800AEFD0;

s32 func_801288B0(void) {
    func_8001ABBC(0, 0, &D_800AEFD0, D_8019AB88, 0);
}



// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x60 store AND arg5; writing D_800C7C60=0x60 directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AF558;
extern int D_8019AB88;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int func_801288E8(int arg0)
{
    int *p = &D_800C7C60;
    *p = 0x60;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AF558, D_8019AB88, p);
}




// @class: remat
// @stuck: none — MATCH (pointer-var forces single materialization of &D_800C7C60, reused as store base + arg5)

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern u8 D_800AF560;
extern s32 D_8019AB88;

s32 func_80128940(s32 _arg0)
{
    s32 *p = &D_800C7C60;
    *p = 0x5E;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(s32, s32, void *, s32, void *))func_8001ABBC)(0, 0, &D_800AF560, D_8019AB88, p);
}




// @class: remat
// @stuck: none — MATCH. &D_800C7C60 must be CSE'd once (pointer local `p`) so the same reg feeds the *p=13 store AND arg5; writing D_800C7C60=13 directly emits a 2nd address materialization (+1 ins).

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AECB0;
extern s32 D_8019AB88;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_80128998(void)
{
    int *p = &D_800C7C60;
    *p = 13;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AECB0, D_8019AB88, p);
}



extern s32 D_8019AB88;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_801289F0(void) {
    func_8001ABBC(0, 0, &D_800AECB8, D_8019AB88, 0);
}


extern void func_80011B7C(int);
extern void func_80011C10(void);
extern u16 D_800B99F6;
extern s16 D_800B9A00;
extern M2C_UNK (*D_8017DCEC)();
extern s16 (*D_8017DCF0)();

void func_80128A28(void) {
    s16 temp_v0;

    switch (D_800B99F6) {                           /* irregular */
    case 1:
        D_8017DCEC();
        /* fallthrough */
    case 0:
        func_80011C10();
        return;
    case 2:
        temp_v0 = D_8017DCF0();
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


extern u16 D_800B99F6;
extern M2C_UNK (*D_8017DCF8)();
extern s32 (*D_8017DCFC)();
extern s32 D_8019BD28;

void func_80128AF4(void) {
    switch (D_800B99F6) {                           /* irregular */
    case 0:
        D_8019BD28 = func_8002AF08();
        func_80011C10();
        return;
    case 1:
        D_8017DCF8();
        func_80011C10();
        return;
    case 2:
        if ((D_8017DCFC() << 0x10) != 0) {
            if (D_8019BD28 == 1) {
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


DEFINE_func_80128C14()  /* dedup: shared engine-core @0x80128C14 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80128C98);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80128CFC);

DEFINE_func_80128D60()  /* dedup: shared engine-core @0x80128D60 (src/shared) */

DEFINE_func_80128DB4()  /* dedup: shared engine-core @0x80128DB4 (src/shared) */

DEFINE_func_80128EA8()  /* dedup: shared engine-core @0x80128EA8 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80128ED8);

extern M2C_UNK D_8019AB8C;

void func_80128FAC(u16 *arg0) {
    func_8001534C(4, &D_8019AB8C, 0x80, 0x90, 0, 0);
    func_800153CC(5, *arg0, 0xA8, 0x90, 0x40, 0);
}


DEFINE_func_80129010()  /* dedup: shared engine-core @0x80129010 (src/shared) */

DEFINE_func_801290DC()  /* dedup: shared engine-core @0x801290DC (src/shared) */

DEFINE_func_8012913C()  /* dedup: shared engine-core @0x8012913C (src/shared) */

DEFINE_func_801291C0()  /* dedup: shared engine-core @0x801291C0 (src/shared) */

DEFINE_func_80129220()  /* dedup: shared engine-core @0x80129220 (src/shared) */

DEFINE_func_80129248()  /* dedup: shared engine-core @0x80129248 (src/shared) */

DEFINE_func_80129258()  /* dedup: shared engine-core @0x80129258 (src/shared) */

DEFINE_func_8012927C()  /* dedup: shared engine-core @0x8012927C (src/shared) */

DEFINE_func_801292C8()  /* dedup: shared engine-core @0x801292C8 (src/shared) */

DEFINE_func_8012931C()  /* dedup: shared engine-core @0x8012931C (src/shared) */

DEFINE_func_80129350()  /* dedup: shared engine-core @0x80129350 (src/shared) */

DEFINE_func_80129374()  /* dedup: shared engine-core @0x80129374 (src/shared) */

DEFINE_func_80129398()  /* dedup: shared engine-core @0x80129398 (src/shared) */

DEFINE_func_80129428()  /* dedup: shared engine-core @0x80129428 (src/shared) */

DEFINE_func_8012943C()  /* dedup: shared engine-core @0x8012943C (src/shared) */

DEFINE_func_8012944C()  /* dedup: shared engine-core @0x8012944C (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012956C);

DEFINE_func_801298F4()  /* dedup: shared engine-core @0x801298F4 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801299C8);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80129C40);

DEFINE_func_80129CF8()  /* dedup: shared engine-core @0x80129CF8 (src/shared) */

DEFINE_func_80129FF4()  /* dedup: shared engine-core @0x80129FF4 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012A018);

DEFINE_func_8012A048()  /* dedup: shared engine-core @0x8012A048 (src/shared) */

DEFINE_func_8012A094()  /* dedup: shared engine-core @0x8012A094 (src/shared) */

DEFINE_func_8012A0E0()  /* dedup: shared engine-core @0x8012A0E0 (src/shared) */

DEFINE_func_8012A100()  /* dedup: shared engine-core @0x8012A100 (src/shared) */

DEFINE_func_8012A110()  /* dedup: shared engine-core @0x8012A110 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012A1BC);

DEFINE_func_8012A2F4()  /* dedup: shared engine-core @0x8012A2F4 (src/shared) */

DEFINE_func_8012A304()  /* dedup: shared engine-core @0x8012A304 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012A328);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012A418);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012A464);

DEFINE_func_8012A4BC()  /* dedup: shared engine-core @0x8012A4BC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012A568);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012A598);

DEFINE_func_8012A5F8()  /* dedup: shared engine-core @0x8012A5F8 (src/shared) */

DEFINE_func_8012A62C()  /* dedup: shared engine-core @0x8012A62C (src/shared) */

DEFINE_func_8012A68C()  /* dedup: shared engine-core @0x8012A68C (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012A6D0);

DEFINE_func_8012A758()  /* dedup: shared engine-core @0x8012A758 (src/shared) */

DEFINE_func_8012A79C()  /* dedup: shared engine-core @0x8012A79C (src/shared) */

DEFINE_func_8012A7D4()  /* dedup: shared engine-core @0x8012A7D4 (src/shared) */

DEFINE_func_8012A828()  /* dedup: shared engine-core @0x8012A828 (src/shared) */

DEFINE_func_8012A860()  /* dedup: shared engine-core @0x8012A860 (src/shared) */

DEFINE_func_8012A8B0()  /* dedup: shared engine-core @0x8012A8B0 (src/shared) */

DEFINE_func_8012A8E8()  /* dedup: shared engine-core @0x8012A8E8 (src/shared) */

DEFINE_func_8012A908()  /* dedup: shared engine-core @0x8012A908 (src/shared) */

DEFINE_func_8012A988()  /* dedup: shared engine-core @0x8012A988 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012AAAC);


extern void func_8012AAAC(void);
extern M2C_UNK D_8017E044;

void func_8012ACA0(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_8017E044;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s16 *, 0x9A) = 0;
    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
    func_8012AAAC();
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012ACE0);

DEFINE_func_8012AD44()  /* dedup: shared engine-core @0x8012AD44 (src/shared) */

DEFINE_func_8012AD50()  /* dedup: shared engine-core @0x8012AD50 (src/shared) */



void func_8012AD64(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x34) = a1;
}


DEFINE_func_8012AD6C()  /* dedup: shared engine-core @0x8012AD6C (src/shared) */

DEFINE_func_8012AD80()  /* dedup: shared engine-core @0x8012AD80 (src/shared) */

DEFINE_func_8012ADE4()  /* dedup: shared engine-core @0x8012ADE4 (src/shared) */

DEFINE_func_8012AE00()  /* dedup: shared engine-core @0x8012AE00 (src/shared) */

DEFINE_func_8012AF0C()  /* dedup: shared engine-core @0x8012AF0C (src/shared) */

DEFINE_func_8012B030()  /* dedup: shared engine-core @0x8012B030 (src/shared) */

DEFINE_func_8012B0B4()  /* dedup: shared engine-core @0x8012B0B4 (src/shared) */

DEFINE_func_8012B14C()  /* dedup: shared engine-core @0x8012B14C (src/shared) */

DEFINE_func_8012B178()  /* dedup: shared engine-core @0x8012B178 (src/shared) */

DEFINE_func_8012B1B4()  /* dedup: shared engine-core @0x8012B1B4 (src/shared) */

DEFINE_func_8012B200()  /* dedup: shared engine-core @0x8012B200 (src/shared) */

DEFINE_func_8012B21C()  /* dedup: shared engine-core @0x8012B21C (src/shared) */

DEFINE_func_8012B23C()  /* dedup: shared engine-core @0x8012B23C (src/shared) */

DEFINE_func_8012B260()  /* dedup: shared engine-core @0x8012B260 (src/shared) */

DEFINE_func_8012B2CC()  /* dedup: shared engine-core @0x8012B2CC (src/shared) */

DEFINE_func_8012B370()  /* dedup: shared engine-core @0x8012B370 (src/shared) */

DEFINE_func_8012B414()  /* dedup: shared engine-core @0x8012B414 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012B4B8);

DEFINE_func_8012B608()  /* dedup: shared engine-core @0x8012B608 (src/shared) */

DEFINE_func_8012B6D4()  /* dedup: shared engine-core @0x8012B6D4 (src/shared) */

DEFINE_func_8012B70C()  /* dedup: shared engine-core @0x8012B70C (src/shared) */

DEFINE_func_8012B744()  /* dedup: shared engine-core @0x8012B744 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012B77C);

DEFINE_func_8012B864()  /* dedup: shared engine-core @0x8012B864 (src/shared) */

DEFINE_func_8012B8A4()  /* dedup: shared engine-core @0x8012B8A4 (src/shared) */

DEFINE_func_8012B8E4()  /* dedup: shared engine-core @0x8012B8E4 (src/shared) */

DEFINE_func_8012BA10()  /* dedup: shared engine-core @0x8012BA10 (src/shared) */

DEFINE_func_8012BB3C()  /* dedup: shared engine-core @0x8012BB3C (src/shared) */

DEFINE_func_8012BC60()  /* dedup: shared engine-core @0x8012BC60 (src/shared) */

DEFINE_func_8012BCCC()  /* dedup: shared engine-core @0x8012BCCC (src/shared) */

DEFINE_func_8012BD14()  /* dedup: shared engine-core @0x8012BD14 (src/shared) */

DEFINE_func_8012BD3C()  /* dedup: shared engine-core @0x8012BD3C (src/shared) */

DEFINE_func_8012BDBC()  /* dedup: shared engine-core @0x8012BDBC (src/shared) */

DEFINE_func_8012BE54()  /* dedup: shared engine-core @0x8012BE54 (src/shared) */

DEFINE_func_8012BE98()  /* dedup: shared engine-core @0x8012BE98 (src/shared) */

DEFINE_func_8012BEE8()  /* dedup: shared engine-core @0x8012BEE8 (src/shared) */

DEFINE_func_8012BF10()  /* dedup: shared engine-core @0x8012BF10 (src/shared) */


void func_8012BF4C(s32 *a0, s32 a1) {
    *(s32*)((s32)a0 + 0x1C) = a1;
}


DEFINE_func_8012BF54()  /* dedup: shared engine-core @0x8012BF54 (src/shared) */

DEFINE_func_8012BF68()  /* dedup: shared engine-core @0x8012BF68 (src/shared) */

DEFINE_func_8012BF7C()  /* dedup: shared engine-core @0x8012BF7C (src/shared) */

DEFINE_func_8012BFA8()  /* dedup: shared engine-core @0x8012BFA8 (src/shared) */

DEFINE_func_8012C044()  /* dedup: shared engine-core @0x8012C044 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012C098);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012C0EC);

DEFINE_func_8012C194()  /* dedup: shared engine-core @0x8012C194 (src/shared) */

DEFINE_func_8012C1B8()  /* dedup: shared engine-core @0x8012C1B8 (src/shared) */

DEFINE_func_8012C1DC()  /* dedup: shared engine-core @0x8012C1DC (src/shared) */

DEFINE_func_8012C218()  /* dedup: shared engine-core @0x8012C218 (src/shared) */

DEFINE_func_8012C284()  /* dedup: shared engine-core @0x8012C284 (src/shared) */

DEFINE_func_8012C2D0()  /* dedup: shared engine-core @0x8012C2D0 (src/shared) */

DEFINE_func_8012C31C()  /* dedup: shared engine-core @0x8012C31C (src/shared) */

DEFINE_func_8012C354()  /* dedup: shared engine-core @0x8012C354 (src/shared) */

DEFINE_func_8012C438()  /* dedup: shared engine-core @0x8012C438 (src/shared) */

DEFINE_func_8012C51C()  /* dedup: shared engine-core @0x8012C51C (src/shared) */

DEFINE_func_8012C588()  /* dedup: shared engine-core @0x8012C588 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012C658);

DEFINE_func_8012C724()  /* dedup: shared engine-core @0x8012C724 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012C750);

DEFINE_func_8012C820()  /* dedup: shared engine-core @0x8012C820 (src/shared) */


// @class: schedule
// @stuck: none — MATCH (149 ins). Counter (*(u16 *)&D_801270C4): gcc CSE's the two reads (store to
//   dst+0x36 assumed non-aliasing the global) AND folds %lo per-access — target instead RELOADS
//   and keeps &(*(u16 *)&D_801270C4) in one reg. Fix = pin a `u16*` to $v1 (register asm "$3"), read via
//   `*(volatile u16*)pc` (defeats CSE -> 2 loads) but STORE via plain `*pc` (non-volatile store
//   schedules store-before-sll, no extra `move`). count is s16 so `count==0` -> `sll 16;bnez`.
//   else-block obj must be a BLOCK-LOCAL (gcc then picks $a1, not the shared if-branch $a0).

extern s32   D_80181528;
extern s16 D_801270C4;
extern u16   D_801274E4[];
extern s32   D_8011DB08;
extern void  func_80016714(void *a0, s32 a1);

s32 func_8012C890(s32 a0, s32 a1, s32 a2) {
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
    *(s32 *)(dst + 0x78) = (s32)&D_80181528;
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


DEFINE_func_8012CAE4()  /* dedup: shared engine-core @0x8012CAE4 (src/shared) */

DEFINE_func_8012CB64()  /* dedup: shared engine-core @0x8012CB64 (src/shared) */

DEFINE_func_8012CBA4()  /* dedup: shared engine-core @0x8012CBA4 (src/shared) */

DEFINE_func_8012CBCC()  /* dedup: shared engine-core @0x8012CBCC (src/shared) */

DEFINE_func_8012CBF4()  /* dedup: shared engine-core @0x8012CBF4 (src/shared) */

DEFINE_func_8012CC1C()  /* dedup: shared engine-core @0x8012CC1C (src/shared) */

DEFINE_func_8012CC40()  /* dedup: shared engine-core @0x8012CC40 (src/shared) */

DEFINE_func_8012CC64()  /* dedup: shared engine-core @0x8012CC64 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012CC88);

DEFINE_func_8012CE2C()  /* dedup: shared engine-core @0x8012CE2C (src/shared) */

DEFINE_func_8012CEB0()  /* dedup: shared engine-core @0x8012CEB0 (src/shared) */

DEFINE_func_8012CFA8()  /* dedup: shared engine-core @0x8012CFA8 (src/shared) */

DEFINE_func_8012D098()  /* dedup: shared engine-core @0x8012D098 (src/shared) */

DEFINE_func_8012D38C()  /* dedup: shared engine-core @0x8012D38C (src/shared) */

DEFINE_func_8012D3AC()  /* dedup: shared engine-core @0x8012D3AC (src/shared) */

DEFINE_func_8012D3B4()  /* dedup: shared engine-core @0x8012D3B4 (src/shared) */

DEFINE_func_8012D4B4()  /* dedup: shared engine-core @0x8012D4B4 (src/shared) */

DEFINE_func_8012D5DC()  /* dedup: shared engine-core @0x8012D5DC (src/shared) */

DEFINE_func_8012D5E4()  /* dedup: shared engine-core @0x8012D5E4 (src/shared) */

DEFINE_func_8012D624()  /* dedup: shared engine-core @0x8012D624 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012D664);

DEFINE_func_8012D714()  /* dedup: shared engine-core @0x8012D714 (src/shared) */



extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);
extern M2C_UNK D_8017E05C;
extern M2C_UNK D_8017E064;

s32 func_8012DB84(void)
{
    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, &D_8017E05C, &D_8017E064);
}


DEFINE_func_8012DBD0()  /* dedup: shared engine-core @0x8012DBD0 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012DDA4);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012DE2C);

DEFINE_func_8012DEB8()  /* dedup: shared engine-core @0x8012DEB8 (src/shared) */

DEFINE_func_8012DF34()  /* dedup: shared engine-core @0x8012DF34 (src/shared) */

DEFINE_func_8012DFBC()  /* dedup: shared engine-core @0x8012DFBC (src/shared) */

DEFINE_func_8012DFCC()  /* dedup: shared engine-core @0x8012DFCC (src/shared) */

DEFINE_func_8012DFD4()  /* dedup: shared engine-core @0x8012DFD4 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012E014);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012E138);


s32 func_8012E27C(void) {
    return 1;
}


DEFINE_func_8012E284()  /* dedup: shared engine-core @0x8012E284 (src/shared) */

DEFINE_func_8012E28C()  /* dedup: shared engine-core @0x8012E28C (src/shared) */

DEFINE_func_8012E32C()  /* dedup: shared engine-core @0x8012E32C (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012E364);

DEFINE_func_8012E470()  /* dedup: shared engine-core @0x8012E470 (src/shared) */

DEFINE_func_8012E4C8()  /* dedup: shared engine-core @0x8012E4C8 (src/shared) */

DEFINE_func_8012E504()  /* dedup: shared engine-core @0x8012E504 (src/shared) */

DEFINE_func_8012E544()  /* dedup: shared engine-core @0x8012E544 (src/shared) */

DEFINE_func_8012E57C()  /* dedup: shared engine-core @0x8012E57C (src/shared) */


// @class: schedule
// @stuck: none — MATCH
extern u8 D_800AF648;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8012E5CC(s32 param_1, u16 param_2, u16 param_3)
{
    struct { short xy[2]; int sp14; int flag; } f;
    register void *p __asm__("$4");
    p = &D_800AF648;
    func_8004914C(p);
    func_800491AC(&D_800AF648);
    RotTransPers(param_1, (s32)f.xy, &f.sp14, &f.flag);
    if (f.flag >= 0 && (u16)(f.xy[0] + 199) < 399 && (u16)(f.xy[1] + 0xA9) < 0x153) {
        func_8002D4C8(param_2, param_3);
    }
}


DEFINE_func_8012E688()  /* dedup: shared engine-core @0x8012E688 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012E778);

DEFINE_func_8012E88C()  /* dedup: shared engine-core @0x8012E88C (src/shared) */

DEFINE_func_8012E8A8()  /* dedup: shared engine-core @0x8012E8A8 (src/shared) */

DEFINE_func_8012E8C4()  /* dedup: shared engine-core @0x8012E8C4 (src/shared) */

DEFINE_func_8012E8E0()  /* dedup: shared engine-core @0x8012E8E0 (src/shared) */



// @class: other
// @stuck: none — MATCH (branch-polarity invert: `0x78 != 0` puts compute block as fall-through)

extern void func_8016AA50(int, int);
extern void func_8016B428(int);
extern void func_80019064(void *);
extern int D_8017E06C;

void func_8012E9C0(int param_1)
{
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
            func_80019064(&D_8017E06C);
        }
    }
    return;
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012EA90);

DEFINE_func_8012EC04()  /* dedup: shared engine-core @0x8012EC04 (src/shared) */

DEFINE_func_8012EECC()  /* dedup: shared engine-core @0x8012EECC (src/shared) */

DEFINE_func_8012EF34()  /* dedup: shared engine-core @0x8012EF34 (src/shared) */

DEFINE_func_8012EF70()  /* dedup: shared engine-core @0x8012EF70 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012EFB8);


// @class: other
// @stuck: none — MATCH (33 ins, match_one verified)

extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);

void func_8012F038(int param_1, short *param_2, short *param_3) {
    int in[3];
    int out[3];

    in[0] = (int)param_2[0] - *(int *)(param_1 + 0x14);
    in[1] = (int)param_2[1] - *(int *)(param_1 + 0x18);
    in[2] = (int)param_2[2] - *(int *)(param_1 + 0x1c);
    ApplyTransposeMatrixLV((void *)param_1, in, out);
    param_3[0] = out[0];
    param_3[1] = out[1];
    param_3[2] = out[2];
}


DEFINE_func_8012F0BC()  /* dedup: shared engine-core @0x8012F0BC (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (clone of confirmed func_8012F214 template; passthrough a0)
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);

void func_8012F14C(s32 a0, s32 a1, s32 a2)
{
    s32 buf[2];
    func_8004914C((void *)a0);
    func_800491AC((void *)a0);
    RotTransSV(a1, a2, buf);
}


DEFINE_func_8012F1A4()  /* dedup: shared engine-core @0x8012F1A4 (src/shared) */

DEFINE_func_8012F214()  /* dedup: shared engine-core @0x8012F214 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012F274);

DEFINE_func_8012F2E8()  /* dedup: shared engine-core @0x8012F2E8 (src/shared) */

DEFINE_func_8012F374()  /* dedup: shared engine-core @0x8012F374 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012F40C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012F49C);

DEFINE_func_8012F568()  /* dedup: shared engine-core @0x8012F568 (src/shared) */

DEFINE_func_8012F5F4()  /* dedup: shared engine-core @0x8012F5F4 (src/shared) */

DEFINE_func_8012F68C()  /* dedup: shared engine-core @0x8012F68C (src/shared) */

DEFINE_func_8012F75C()  /* dedup: shared engine-core @0x8012F75C (src/shared) */

DEFINE_func_8012F7B4()  /* dedup: shared engine-core @0x8012F7B4 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (pending gate)
extern void func_80131170();
extern void func_80131CA8();
extern unsigned char D_8017E088[];

void func_8012F828(int param_1)
{
    *(unsigned char *)(param_1 + 0xC1) = 4;
    if (*(unsigned int *)(param_1 + 0xB4) & 8) {
        func_80131170(param_1, D_8017E088, 0xB);
    }
    func_80131CA8(param_1, 9);
}


DEFINE_func_8012F87C()  /* dedup: shared engine-core @0x8012F87C (src/shared) */


extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern void func_80131CA8(int a0, int a1);
extern u8 D_8017E094[];

void func_8012F8C8(u8* arg0) {
    *(u8*)(arg0 + 0xC1) = 7;
    if (*(u32*)(arg0 + 0xB4) & 0x80) {
        ((void (*)(void*, void*, s32))func_80131170)(arg0, D_8017E094, 0xB);
    }
    ((void (*)(void*, s32))func_80131CA8)(arg0, 0x16);
}


DEFINE_func_8012F91C()  /* dedup: shared engine-core @0x8012F91C (src/shared) */

DEFINE_func_8012F968()  /* dedup: shared engine-core @0x8012F968 (src/shared) */

DEFINE_func_8012FB54()  /* dedup: shared engine-core @0x8012FB54 (src/shared) */

DEFINE_func_8012FC30()  /* dedup: shared engine-core @0x8012FC30 (src/shared) */

DEFINE_func_8012FCA4()  /* dedup: shared engine-core @0x8012FCA4 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8012FCC4);

DEFINE_func_8012FDA8()  /* dedup: shared engine-core @0x8012FDA8 (src/shared) */

DEFINE_func_8012FE70()  /* dedup: shared engine-core @0x8012FE70 (src/shared) */

DEFINE_func_8012FF00()  /* dedup: shared engine-core @0x8012FF00 (src/shared) */

DEFINE_func_8012FF4C()  /* dedup: shared engine-core @0x8012FF4C (src/shared) */

DEFINE_func_8012FF98()  /* dedup: shared engine-core @0x8012FF98 (src/shared) */

DEFINE_func_8013001C()  /* dedup: shared engine-core @0x8013001C (src/shared) */

DEFINE_func_80130088()  /* dedup: shared engine-core @0x80130088 (src/shared) */

DEFINE_func_801300F4()  /* dedup: shared engine-core @0x801300F4 (src/shared) */

DEFINE_func_801301E8()  /* dedup: shared engine-core @0x801301E8 (src/shared) */

DEFINE_func_80130278()  /* dedup: shared engine-core @0x80130278 (src/shared) */

DEFINE_func_80130314()  /* dedup: shared engine-core @0x80130314 (src/shared) */

DEFINE_func_80130360()  /* dedup: shared engine-core @0x80130360 (src/shared) */

DEFINE_func_801303A0()  /* dedup: shared engine-core @0x801303A0 (src/shared) */

DEFINE_func_801303EC()  /* dedup: shared engine-core @0x801303EC (src/shared) */

DEFINE_func_80130438()  /* dedup: shared engine-core @0x80130438 (src/shared) */

DEFINE_func_80130514()  /* dedup: shared engine-core @0x80130514 (src/shared) */

DEFINE_func_801305CC()  /* dedup: shared engine-core @0x801305CC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80130650);

DEFINE_func_80130740()  /* dedup: shared engine-core @0x80130740 (src/shared) */

DEFINE_func_801307B0()  /* dedup: shared engine-core @0x801307B0 (src/shared) */

DEFINE_func_80130858()  /* dedup: shared engine-core @0x80130858 (src/shared) */

DEFINE_func_80130898()  /* dedup: shared engine-core @0x80130898 (src/shared) */

DEFINE_func_801308DC()  /* dedup: shared engine-core @0x801308DC (src/shared) */

DEFINE_func_80130974()  /* dedup: shared engine-core @0x80130974 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80130A18);

DEFINE_func_80130AC4()  /* dedup: shared engine-core @0x80130AC4 (src/shared) */

DEFINE_func_80130AF0()  /* dedup: shared engine-core @0x80130AF0 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80130C08);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80130D0C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80130D48);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131170);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801312D0);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131340);

DEFINE_func_801319E0()  /* dedup: shared engine-core @0x801319E0 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131A34);

DEFINE_func_80131AC8()  /* dedup: shared engine-core @0x80131AC8 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131B14);

DEFINE_func_80131C78()  /* dedup: shared engine-core @0x80131C78 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131CA8);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131CF4);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131D68);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131E00);

DEFINE_func_80131E38()  /* dedup: shared engine-core @0x80131E38 (src/shared) */

DEFINE_func_80131E7C()  /* dedup: shared engine-core @0x80131E7C (src/shared) */

DEFINE_func_80131EE4()  /* dedup: shared engine-core @0x80131EE4 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131EEC);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131F28);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131F64);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131FA0);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80131FDC);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80132018);

DEFINE_func_801320D0()  /* dedup: shared engine-core @0x801320D0 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int D_8017E248;

void func_801320D8(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8017E248;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80132144);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801321B0);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013221C);

DEFINE_func_80132288()  /* dedup: shared engine-core @0x80132288 (src/shared) */

DEFINE_func_8013240C()  /* dedup: shared engine-core @0x8013240C (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801325B8);

DEFINE_func_8013277C()  /* dedup: shared engine-core @0x8013277C (src/shared) */

DEFINE_func_80132784()  /* dedup: shared engine-core @0x80132784 (src/shared) */

DEFINE_func_80132DC4()  /* dedup: shared engine-core @0x80132DC4 (src/shared) */

DEFINE_func_80132E6C()  /* dedup: shared engine-core @0x80132E6C (src/shared) */

DEFINE_func_80132EC4()  /* dedup: shared engine-core @0x80132EC4 (src/shared) */

DEFINE_func_80132EF4()  /* dedup: shared engine-core @0x80132EF4 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80132F40);

DEFINE_func_80133060()  /* dedup: shared engine-core @0x80133060 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801330E0);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80133298);

DEFINE_func_8013339C()  /* dedup: shared engine-core @0x8013339C (src/shared) */

DEFINE_func_8013361C()  /* dedup: shared engine-core @0x8013361C (src/shared) */


// @class: plumbing
// @stuck: none — MATCH

extern s32 D_8019BD98;
extern s32 D_8019BD9C[];
extern int D_8019BDA0;
extern void func_80136BC4(s32 a0);

void func_801336E8(void *a0, int a1, int a2) {
    if (a0 != 0) {
        (*(void * *)&D_8019BD98) = a0;
        ((void (*)(void))func_80136BC4)();
    }
    (*(int *)&D_8019BD9C) = a1;
    D_8019BDA0 = a2;
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013373C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80133784);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80133AB0);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80133CD4);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80134310);

DEFINE_func_8013435C()  /* dedup: shared engine-core @0x8013435C (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801343C4);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80134510);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801345F8);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801347A0);

DEFINE_func_80134A28()  /* dedup: shared engine-core @0x80134A28 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80134A74);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80134C20);

DEFINE_func_80134FB8()  /* dedup: shared engine-core @0x80134FB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80135004);


// @class: schedule
// @stuck: none — MATCH (62 ins, relocation-masked)


extern u8 D_8017E2AC;
extern u8 D_8017E2A8;
extern s32 D_8017E2B0[];
extern u8 D_8017E2B4;
extern int D_8019BD98;
extern u16 D_8019BDA8;

extern int func_80134A74(int, s16, s16, int);

int func_80135168(u16 arg0, u16 *p1, u16 *p2)
{
    register s16 *pb0 __asm__("$8");
    register s16 *pac __asm__("$6");
    register s16 *pb8 __asm__("$7");
    u16 *pb4;
    u16 a, b;
    int a1v, a2v, d94;

    pb0 = (*(s16 * *)&D_8017E2AC);
    __asm__ __volatile__("" : : "r"(pb0));

    a = p2[0]; pac = (*(s16 * *)&D_8017E2A8); pb0[0] = a; b = p1[0]; pb8 = (*(s16 * *)&D_8017E2B4); pac[0] = b; pb8[0] = a - b;
    a = p2[1]; pb0[1] = a; b = p1[1]; pac[1] = b; pb8[1] = a - b;
    a = p2[2]; pb0[2] = a; b = p1[2]; pac[2] = b; pb8[2] = a - b;

    a1v = pac[0]; a2v = pac[2]; d94 = D_8019BD98;
    __asm__ __volatile__("" ::: "memory");
    D_8019BDA8 = 0;
    if (func_80134A74(arg0, a1v, a2v, d94)) {
        pb4 = (*(u16 * *)&D_8017E2B0);
        p2[0] = pb4[0];
        p2[1] = pb4[1];
        p2[2] = pb4[2];
        p2[3] = D_8019BDA8;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80135260);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80135480);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80135888);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80135A4C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80135D20);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80135EB0);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80136334);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801365B8);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80136824);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80136A94);

DEFINE_func_80136BC4()  /* dedup: shared engine-core @0x80136BC4 (src/shared) */

DEFINE_func_80136C1C()  /* dedup: shared engine-core @0x80136C1C (src/shared) */

DEFINE_func_80136C3C()  /* dedup: shared engine-core @0x80136C3C (src/shared) */

DEFINE_func_80136C44()  /* dedup: shared engine-core @0x80136C44 (src/shared) */

DEFINE_func_80136C4C()  /* dedup: shared engine-core @0x80136C4C (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80136C54);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80136C90);

DEFINE_func_80136D00()  /* dedup: shared engine-core @0x80136D00 (src/shared) */

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136D08 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80136DFC);

DEFINE_func_80136EC4()  /* dedup: shared engine-core @0x80136EC4 (src/shared) */

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ECC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80136F3C);

DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80137178);

DEFINE_func_801372B0()  /* dedup: shared engine-core @0x801372B0 (src/shared) */

DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375EC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80137614);

DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767C (src/shared) */

DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376C8 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801376E8);

DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377B4 (src/shared) */

DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801378F0);

DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379D8 (src/shared) */

DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379EC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801379FC);


// @class: remat
// @stuck: target CSEs &D_801269F0 once for load+call arg; force via local pointer
extern s32 D_80127548[];
extern int D_8017E318;
extern int D_801269F0;
extern void func_80138BE0(int p);

void func_80137B80(void) {
    int *p = &D_801269F0;
    (*(int *)&D_80127548) = 0x24;
    if (*p != 0) {
        ((void (*)(int *))func_80138BE0)(p);
    }
    D_8017E318 += 1;
}


DEFINE_func_80137BD8()  /* dedup: shared engine-core @0x80137BD8 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (51 ins). Three globals stored/loaded around 3 calls; &D_801269F0 held in $s1, arg1 in $s0 across calls; return reloads global D_800A5E60.

extern unsigned char D_80126A0E;
extern short D_80126A0A;
extern s16 D_801269F4;
extern int D_800A5E60;
extern int D_8017E318;
extern int D_801269F0;

extern void func_801392FC();
extern void func_80137DD4(s32 a0, u8 *a1, u8 *a2);
extern void func_80139680(s32 a0, u8 *a1);

int func_80137D08(int arg0, int arg1, short arg2)
{
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
        if (D_8017E318 & 4) {
            ((void (*)(void *, int))func_80139680)(&D_801269F0, arg1);
        }
    }
    return D_800A5E60;
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80137DD4);

DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137FD8 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801380E0);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801387B8);

DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */

DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895C (src/shared) */

DEFINE_func_80138AB4()  /* dedup: shared engine-core @0x80138AB4 (src/shared) */

DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138B88 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80138BE0);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80138C30);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80138C60);

DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138D58 (src/shared) */

DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138DB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80138DE0);

DEFINE_func_80138ED0()  /* dedup: shared engine-core @0x80138ED0 (src/shared) */

DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914C (src/shared) */

DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391F0 (src/shared) */

DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */

DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392C8 (src/shared) */

DEFINE_func_801392FC()  /* dedup: shared engine-core @0x801392FC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801395D4);

DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */

DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */

DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */


extern short D_800B9A02;
extern u8 D_800A6518[];
extern u8 D_8017E360;
extern u8 D_8017E3A4;
extern void GsSortSprite(void *a0, u8 *a1, s32 a2);

void func_801397B0(s32 arg0)
{
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
    b164 = (u8 *)&D_8017E360;
    off = ((s32)*(u8 *)(e + 0x20) - 1) << 2;
    b164 = off + b164;

    *(s32 *)((u8 *)buf + 0x00) = 0;

    t2 = *(s16 *)(b164 + 2);
    t0 = *(s16 *)(b164 + 0);
    hi = (t2 & 0x100) >> 4;
    lo = ((t0 & 0x3C0) >> 6) | 0x20;
    *(s16 *)((u8 *)buf + 0x0C) = hi | lo | ((t2 & 0x200) << 2);

    b1A8 = (u8 *)&D_8017E3A4 + off;
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

DEFINE_func_801399A8()  /* dedup: shared engine-core @0x801399A8 (src/shared) */

DEFINE_func_801399F0()  /* dedup: shared engine-core @0x801399F0 (src/shared) */

DEFINE_func_80139A34()  /* dedup: shared engine-core @0x80139A34 (src/shared) */

DEFINE_func_80139A44()  /* dedup: shared engine-core @0x80139A44 (src/shared) */

DEFINE_func_80139A68()  /* dedup: shared engine-core @0x80139A68 (src/shared) */

DEFINE_func_80139A8C()  /* dedup: shared engine-core @0x80139A8C (src/shared) */

DEFINE_func_80139B18()  /* dedup: shared engine-core @0x80139B18 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80139BE0);

DEFINE_func_80139C7C()  /* dedup: shared engine-core @0x80139C7C (src/shared) */

DEFINE_func_80139D04()  /* dedup: shared engine-core @0x80139D04 (src/shared) */

DEFINE_func_80139DC8()  /* dedup: shared engine-core @0x80139DC8 (src/shared) */

DEFINE_func_80139DEC()  /* dedup: shared engine-core @0x80139DEC (src/shared) */

DEFINE_func_80139DF4()  /* dedup: shared engine-core @0x80139DF4 (src/shared) */

DEFINE_func_80139E84()  /* dedup: shared engine-core @0x80139E84 (src/shared) */

DEFINE_func_80139F0C()  /* dedup: shared engine-core @0x80139F0C (src/shared) */

DEFINE_func_80139FBC()  /* dedup: shared engine-core @0x80139FBC (src/shared) */

DEFINE_func_80139FE8()  /* dedup: shared engine-core @0x80139FE8 (src/shared) */

DEFINE_func_8013A0A4()  /* dedup: shared engine-core @0x8013A0A4 (src/shared) */

DEFINE_func_8013A164()  /* dedup: shared engine-core @0x8013A164 (src/shared) */

DEFINE_func_8013A1E8()  /* dedup: shared engine-core @0x8013A1E8 (src/shared) */

DEFINE_func_8013A250()  /* dedup: shared engine-core @0x8013A250 (src/shared) */

DEFINE_func_8013A2BC()  /* dedup: shared engine-core @0x8013A2BC (src/shared) */

DEFINE_func_8013A378()  /* dedup: shared engine-core @0x8013A378 (src/shared) */

DEFINE_func_8013A380()  /* dedup: shared engine-core @0x8013A380 (src/shared) */

DEFINE_func_8013A448()  /* dedup: shared engine-core @0x8013A448 (src/shared) */

DEFINE_func_8013A4C4()  /* dedup: shared engine-core @0x8013A4C4 (src/shared) */

DEFINE_func_8013A530()  /* dedup: shared engine-core @0x8013A530 (src/shared) */

DEFINE_func_8013A860()  /* dedup: shared engine-core @0x8013A860 (src/shared) */

DEFINE_func_8013A8B0()  /* dedup: shared engine-core @0x8013A8B0 (src/shared) */

DEFINE_func_8013A8BC()  /* dedup: shared engine-core @0x8013A8BC (src/shared) */

DEFINE_func_8013A8FC()  /* dedup: shared engine-core @0x8013A8FC (src/shared) */

DEFINE_func_8013A9B4()  /* dedup: shared engine-core @0x8013A9B4 (src/shared) */

DEFINE_func_8013A9F8()  /* dedup: shared engine-core @0x8013A9F8 (src/shared) */

DEFINE_func_8013AA24()  /* dedup: shared engine-core @0x8013AA24 (src/shared) */

DEFINE_func_8013AB54()  /* dedup: shared engine-core @0x8013AB54 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013AD38);

DEFINE_func_8013AF20()  /* dedup: shared engine-core @0x8013AF20 (src/shared) */

DEFINE_func_8013B204()  /* dedup: shared engine-core @0x8013B204 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013B274);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013B568);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013B598);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013B6A0);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013B7AC);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013B7F4);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013B83C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013BC7C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013BCDC);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013BD34);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013BD74);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013C08C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013C0F8);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013C360);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013C414);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013C938);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013C964);


/* ==== Phase-17 canonical-sig layer (tools/derive_canonical_sigs.py) ===================
 * ONE byte-neutral canonical signature per undeclared-stub conflict callee, so the parallel
 * hand-matching wave declares each shared callee consistently and the one-big-TU build stops
 * failing on `conflicting types` (hand-matching-process.md §7c). Form: s32 return (void->s32
 * byte-neutral, §3a-1) + s32 params (matched bodies cast int->ptr), arity from Ghidra-C + asm
 * read-before-write $a0-$a3 (agree on all 14 cached; 6 stubs call-site-validated). LOCAL to
 * this TU on purpose (reach-1 names like func_801809BC differ across overlays, so NOT in the
 * shared engine_core.h). Whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9). */
extern s32 func_8016EC0C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012B4B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3); /* derive-decl, arity 4 */
extern s32 func_80169A4C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8016A8FC(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8012B8E4(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8015E1B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015EE08(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015F7D4(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80160B34(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80165140(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80161CD0(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_80175268(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8017EC7C(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801809BC(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012DE2C(s32 a0);                        /* derive-decl, arity 1 */
extern s32 func_8012DDA4(void);                          /* derive-decl, arity 0 */
extern s32 func_801759D8(void);                          /* derive-decl, arity 0 */
extern s32 func_80175820(void);                          /* derive-decl, arity 0 */
extern s32 func_801758FC(void);                          /* derive-decl, arity 0 */
/* ==== end canonical-sig layer ==================================================== */

extern void func_80016714(void *a0, s32 a1);
extern s32 D_8019BE10;
extern s32 D_801269D4;
extern s32 D_801269C8;

void func_8013C98C(void) {
    func_80016714(&D_8019BE10, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


extern M2C_UNK D_80062BC0;
extern s32 D_8019BE10;
extern s8 D_8019BE14;
extern s8 D_8019BE15;

void func_8013C9C4(void * arg0)
{
    D_8019BE10 = arg0;
    D_8019BE14 = 0;
    D_8019BE15 = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}




extern s32 D_8019BE10;
extern s8 D_8019BE14;
extern s8 D_8019BE15;
extern s32 D_801269C8;
extern s32 D_801269D4;
void func_8013CA14(void)
{
  int *base = &D_8019BE10;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_8019BE15;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_8019BE14)) * 2) + D_8019BE10);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_8019BE15 = (unsigned char) p[1];
      D_8019BE14 = D_8019BE14 + 1;
      if (D_8019BE15 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_8019BE14 = 0;
        *base = 0;
      }
    }
    else
    {
      D_8019BE15 = c - 1;
    }
  }
  return;
}



extern s32 D_8019BE34;
extern s32 D_8019BE28;
extern s32 D_8019BE2C;
extern s32 D_8019BE38;

void func_8013CABC(void) {
    D_8019BE34 = 1;
    D_8019BE28 = 1;
    D_8019BE2C = 0;
    D_8019BE38 = 1;
}



extern s32 D_8019BE28;
extern s32 D_8019BE2C;
extern s32 D_8019BE30;
extern s32 D_8019BE34;
extern s32 D_8019BE38;

void func_8013CAE8(void) {
    D_8019BE28 = 1;
    D_8019BE34 = 0;
    D_8019BE2C = 0;
    D_8019BE30 = -1;
    D_8019BE38 = 0;
}



extern s32 D_8019BE34;
extern s32 D_8019BE38;
extern s32 D_8019BE60;
extern s32 D_8019BE64;

void func_8013CB20(void)
{
    D_8019BE60 = D_8019BE38;
    D_8019BE64 = D_8019BE34;
    D_8019BE38 = 1;
    D_8019BE34 = 0;
}



extern s32 D_8019BE60;
extern s32 D_8019BE64;
extern s32 D_8019BE38;
extern s32 D_8019BE34;

void func_8013CB5C(void) {
    D_8019BE38 = D_8019BE60;
    D_8019BE34 = D_8019BE64;
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013CB84);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013CF68);


// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern s32 D_8019BE40;
extern s32 D_8019BE28;
extern s32 D_8019BE44;
extern s32 D_8019BE34;
extern void func_8013D9B0(void);

void func_8013D064(void)
{
    if (D_8019BE40 != 0) {
        if (D_8019BE40 != 2) {
            if (((D_8019BE40 < 3) && (D_8019BE40 == 1)) &&
                (D_8019BE44 = D_8019BE44 + 1, 0x23a < D_8019BE44)) {
                D_8019BE28 = D_8019BE40;
                D_8019BE40 = 2;
            }
        } else {
            D_8019BE28 = D_8019BE28 + -1;
            if (D_8019BE28 == 0) {
                D_8019BE28 = D_8019BE40;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_8019BE34 == 0) {
                    D_8019BE40 = D_8019BE40 + 1;
                }
            }
        }
    }
    return;
}




extern void func_8013D9B0(void);
extern s32 D_8019BE34;

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_8019BE34;
}



extern s32 D_8019BE40;

void func_8013D164(void) {
    D_8019BE40 = 1;
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013D178);


// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)

extern u8 D_8019D16A;
extern u8 D_8019D1DE;
extern u8 D_8019D092;
extern u8 D_8019D14C;
extern u8 D_8019D070;
extern u8 D_8019D091;
extern s32 D_8019D150;

void func_8013D330(void) {
    if ((D_8019D16A & 0xff) != D_8019D1DE) {
        D_8019D16A = ((D_8019D16A & 0xff) < D_8019D1DE) ? (D_8019D16A + 1) : (D_8019D16A - 1);
    }
    if ((D_8019D092 & 0xff) != D_8019D14C) {
        D_8019D092 = ((D_8019D092 & 0xff) < D_8019D14C) ? (D_8019D092 + 1) : (D_8019D092 - 1);
    }
    if ((D_8019D070 & 0xff) != D_8019D091) {
        D_8019D070 = ((D_8019D070 & 0xff) < D_8019D091) ? (D_8019D070 + 1) : (D_8019D070 - 1);
    }
    D_8019D150 = 1;
}




// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)

extern u8 D_80078E78[];

extern void *D_8019BE18;
extern void *D_8019BE1C;
extern void *D_8019BE20;
extern s32 D_8019BE48;
extern s32 D_8019BE4C;
extern s32 D_8019BE50;
extern s32 D_8019D0C4[];

extern u8 D_8017E558[];
extern u8 D_8017E600[];
extern u8 D_8017E4B0[];
extern u8 D_8017E5AC[];
extern u8 D_8017E62C[];
extern u8 D_8017E504[];

extern void func_8013D53C(void);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{
    u8 *p = D_80078E78;

    D_8019BE48 = param_2;
    D_8019BE4C = (param_2 >> 2) & 3;
    D_8019BE50 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_8019BE18 = D_8017E558;
        D_8019BE1C = D_8017E600;
        D_8019BE20 = D_8017E4B0;
    } else {
        D_8019BE18 = D_8017E5AC;
        D_8019BE1C = D_8017E62C;
        D_8019BE20 = D_8017E504;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_8019BE50 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_8019BE48 & 2) != 0) {
            D_8019D0C4[0] = 0x140;
            D_8019D0C4[3] = 0x80;
            if (p[0x37] == 4) {
                D_8019D0C4[0] = 0x140;
                D_8019D0C4[3] = 0;
            }
            if (p[0x37] == 0) {
                D_8019D0C4[0] = 0x140;
                D_8019D0C4[3] = 0x80;
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013D53C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013D8FC);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013D9B0);


// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_8019BE20)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.

extern void *D_8019BE20;
extern s16 *D_8019BE24;
extern s32 D_8019BE34;
extern s32 D_8019BE54;
extern s32 D_8019BE58;
extern s32 D_8019BE5C;

extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{
    int *p;
    int x, y, z;
    int flag;

    if (D_8019BE24 != 0) {
        D_8019BE34 = 0;
        p = (int *)(param_1 * 12 + (int)D_8019BE20);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_8019BE54 != x) {
            flag = 1;
            if (D_8019BE54 < x) {
                if (x - D_8019BE54 < 5) {
                    D_8019BE54 = x;
                } else {
                    D_8019BE54 = D_8019BE54 + 4;
                }
            } else {
                if (D_8019BE54 - x < 5) {
                    D_8019BE54 = x;
                } else {
                    D_8019BE54 = D_8019BE54 - 4;
                }
            }
        }
        if (D_8019BE58 != y) {
            flag = 1;
            if (D_8019BE58 < y) {
                if (y - D_8019BE58 < 5) {
                    D_8019BE58 = y;
                } else {
                    D_8019BE58 = D_8019BE58 + 4;
                }
            } else {
                if (D_8019BE58 - y < 5) {
                    D_8019BE58 = y;
                } else {
                    D_8019BE58 = D_8019BE58 - 4;
                }
            }
        }
        if (D_8019BE5C != z) {
            flag = 1;
            if (D_8019BE5C < z) {
                if (z - D_8019BE5C < 5) {
                    D_8019BE5C = z;
                } else {
                    D_8019BE5C = D_8019BE5C + 4;
                }
            } else {
                if (D_8019BE5C - z < 5) {
                    D_8019BE5C = z;
                } else {
                    D_8019BE5C = D_8019BE5C - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_8019BE34 = flag;
    }
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013DD68);


extern s32 D_8019BE3C;

s32 func_8013E054(void) {
    return D_8019BE3C;
}


DEFINE_func_8013E064()  /* dedup: shared engine-core @0x8013E064 (src/shared) */

DEFINE_func_8013E0FC()  /* dedup: shared engine-core @0x8013E0FC (src/shared) */

DEFINE_func_8013E194()  /* dedup: shared engine-core @0x8013E194 (src/shared) */

DEFINE_func_8013E22C()  /* dedup: shared engine-core @0x8013E22C (src/shared) */

DEFINE_func_8013E298()  /* dedup: shared engine-core @0x8013E298 (src/shared) */

DEFINE_func_8013E2C4()  /* dedup: shared engine-core @0x8013E2C4 (src/shared) */

DEFINE_func_8013E370()  /* dedup: shared engine-core @0x8013E370 (src/shared) */

DEFINE_func_8013E410()  /* dedup: shared engine-core @0x8013E410 (src/shared) */

DEFINE_func_8013E448()  /* dedup: shared engine-core @0x8013E448 (src/shared) */

DEFINE_func_8013E4B4()  /* dedup: shared engine-core @0x8013E4B4 (src/shared) */

DEFINE_func_8013E558()  /* dedup: shared engine-core @0x8013E558 (src/shared) */

DEFINE_func_8013E588()  /* dedup: shared engine-core @0x8013E588 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013E5E8);

DEFINE_func_8013E67C()  /* dedup: shared engine-core @0x8013E67C (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern u8 D_80078EC0;
extern u16 D_8011511A;
extern u16 D_80115124;
extern u8 D_80115148[];
extern u8 D_80115140[];
extern s32 D_8017F0B8;
extern u16 D_80115110;
extern s32 D_80115188;
extern s16 currentLocationId;
extern s16 D_8017F090;
extern s16 D_8017F092;
extern unsigned short D_80115112;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

void func_8013E6AC(void) {
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
        ep = (s32 *)&D_8017F0B8;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_8017F090 = 2;
        D_8017F092 = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_8017F092 = 0;
        D_8017F090 = 0;
        D_80115112 = 6;
    }
}


DEFINE_func_8013E814()  /* dedup: shared engine-core @0x8013E814 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013E83C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013E958);

DEFINE_func_8013EA54()  /* dedup: shared engine-core @0x8013EA54 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (sVar2 pinned to $v0 forces in-place sll/sra sign-ext scratch)


extern s32 func_80141C50(void);
extern void func_8013F350(void);
extern void func_8013FAF8(s32 a0, s32 a1);
extern s16 func_8014168C(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_801376E8(int a0, int a1);
extern void func_80137B80(void);
extern unsigned char *func_80141CA4(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013E958(void);

extern short D_800B9A02;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern u16 D_8011511A;
extern u16 D_8011511E;
extern short D_80115128;
extern unsigned short D_80115112;
extern s16 D_8011512A;
extern s32 D_80115130;
extern unsigned char D_8017F094;

void func_8013EB7C(void) {
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
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_8017F094));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_8017F094));
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


DEFINE_func_8013ED6C()  /* dedup: shared engine-core @0x8013ED6C (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013EE10);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013EF88);


// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned short D_80115118;
extern unsigned short D_80115112;
extern u16 D_80115110;
extern unsigned char D_8017F094;

extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8017F094);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013F1BC (src/shared) */

DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013F244 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013F350);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013FAF8);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8013FFD8);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8014032C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80140608);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801407F4);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80140958);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80140D68);


// @class: struct
// @stuck: none — MATCH

extern unsigned char D_80078E7F;
extern unsigned char D_80078E7E;
extern unsigned char D_80078E7D;
extern M2C_UNK D_8017ECAC;

extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);

void func_80140E6C(void) {
    void *puVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int uVar4;

    puVar1 = (*(void * *)&D_8017ECAC);
    uVar2 = func_800D2CA8(D_80078E7F, 0x18);
    uVar3 = func_800D2CA8(D_80078E7E, 0xc);
    uVar4 = func_800D2CA8(D_80078E7D, 0);
    func_800D2D10(uVar2 | 0xb00000 | uVar3 | 0xb00 | uVar4, 8, puVar1, 0);
}




// @class: plumbing
// @stuck: none — MATCH (128/128 ins, match_one confirmed)

extern short D_80115128;
extern u8 D_8017ECBC;
extern char *D_8017ECDC;
extern char *D_8017ECE0;
extern char *D_8017ECE4;
extern char *D_8017ECE8;
extern char *D_8017ECEC;

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
    char *p;
    int r;

    if (D_80115128 == 0) {
        p = (*(char * *)&D_8017ECBC);
        r = func_800D2CA8(func_80029FE4() + 1, 0x18);
        func_800D2D10(r, 2, p + 4, 1);
        strcpy(p + 0xA, func_8002AAB4());

        p = D_8017ECDC;
        r = func_800D2CA8(func_8002A26C() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A2B0(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8017ECE0;
        r = func_800D2CA8(func_8002A4B8() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(((int (*)(void))func_8002A4FC)(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8017ECE4;
        r = func_800D2CA8(func_8002A998() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A9DC(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8017ECE8;
        r = func_800D2CA8(func_8002A728() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A76C(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_8017ECEC;
        r = func_800D2CA8(func_80029FD4(), 4);
        func_800D2D10(r, 7, p + 0x18, -1);
    }
}



// @class: other
// @stuck: none — MATCH

extern short D_80115128;
extern unsigned short D_80115172;
extern unsigned short D_8017EB76;
extern unsigned short D_8017EB7A;
extern unsigned short D_8017EB7E;
extern unsigned short D_8017EB82;

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
    short sVar1;
    int iVar7;

    if (D_80115128 == 0) {
        iVar7 = D_80115172 + 0x31;
        sVar1 = D_8017EB76;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A1B4)(), func_8002A28C(), func_8002A27C(), (short)iVar7, (int)sVar1);
        sVar1 = D_8017EB7A;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A400)(), func_8002A4D8(), func_8002A4C8(), (short)iVar7, (int)sVar1);
        sVar1 = D_8017EB7E;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A8E0)(), func_8002A9B8(), func_8002A9A8(), (short)iVar7, (int)sVar1);
        sVar1 = D_8017EB82;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A670)(), func_8002A748(), func_8002A738(), (short)iVar7, (int)sVar1);
    }
    return param_1;
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801412A8);

DEFINE_func_801415C0()  /* dedup: shared engine-core @0x801415C0 (src/shared) */

DEFINE_func_8014168C()  /* dedup: shared engine-core @0x8014168C (src/shared) */

DEFINE_func_801416D4()  /* dedup: shared engine-core @0x801416D4 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80141788);

DEFINE_func_801417C4()  /* dedup: shared engine-core @0x801417C4 (src/shared) */

DEFINE_func_801417F8()  /* dedup: shared engine-core @0x801417F8 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80141874);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801418F8);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80141A60);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80141B90);

DEFINE_func_80141C04()  /* dedup: shared engine-core @0x80141C04 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80141C0C);

DEFINE_func_80141C50()  /* dedup: shared engine-core @0x80141C50 (src/shared) */

DEFINE_func_80141CA4()  /* dedup: shared engine-core @0x80141CA4 (src/shared) */

DEFINE_func_80142414()  /* dedup: shared engine-core @0x80142414 (src/shared) */

DEFINE_func_80142454()  /* dedup: shared engine-core @0x80142454 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801424E4);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801425CC);


// @class: schedule
// @stuck: none — MATCH expected; CAE4 block fallthrough, AD50 block goto-tail

extern void func_8012C1B8(void);
extern s32 func_8012C1DC(s32 a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_8017F130;

void func_80142608(s32 param_1)
{
    register s32 iVar1 __asm__("$16");

    if (*(short *)(param_1 + 0x70) != 0) {
        iVar1 = ((s32 (*)(void))func_8012C1B8)();
    } else {
        iVar1 = func_8012C1DC(*(s32 *)(param_1 + 100));
    }
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CA1C(iVar1, (s32)&D_8017F130);
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


DEFINE_func_801426D4()  /* dedup: shared engine-core @0x801426D4 (src/shared) */

DEFINE_func_80142740()  /* dedup: shared engine-core @0x80142740 (src/shared) */

DEFINE_func_80142778()  /* dedup: shared engine-core @0x80142778 (src/shared) */

DEFINE_func_801427DC()  /* dedup: shared engine-core @0x801427DC (src/shared) */

DEFINE_func_801427E4()  /* dedup: shared engine-core @0x801427E4 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801427EC);

DEFINE_func_80142838()  /* dedup: shared engine-core @0x80142838 (src/shared) */

DEFINE_func_801428CC()  /* dedup: shared engine-core @0x801428CC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8014292C);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80142978);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801429C4);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80142A10);


// @class: struct
// @stuck: none — MATCH (packed-word struct -> lwl/lwr unaligned copy; union byte[] -> $sp-direct lbu; branch-polarity invert -> beqz)

extern u16 D_800B99D8;
extern struct packed_word D_8019B518;
extern u8 D_8019BE78;
extern u8 D_8019BE79;
extern u8 D_8019BE7A;

void func_80142A80(void)
{
    u16 flags;
    union word_bytes local;
    s32 mul;

    flags = D_800B99D8;
    local.pw = D_8019B518;

    if (flags & 0x10) {
        mul = (s8)((flags & 0xf) >> 1) + 9;
    } else {
        mul = 0x10 - (s8)((flags & 0xf) >> 1);
    }

    D_8019BE78 = mul * (local.b[0] >> 4);
    D_8019BE79 = mul * (local.b[1] >> 4);
    D_8019BE7A = mul * (local.b[2] >> 4);
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80142B2C);

DEFINE_func_80142BB4()  /* dedup: shared engine-core @0x80142BB4 (src/shared) */

DEFINE_func_80142C7C()  /* dedup: shared engine-core @0x80142C7C (src/shared) */

DEFINE_func_80142C84()  /* dedup: shared engine-core @0x80142C84 (src/shared) */

DEFINE_func_80142C9C()  /* dedup: shared engine-core @0x80142C9C (src/shared) */

DEFINE_func_80142D38()  /* dedup: shared engine-core @0x80142D38 (src/shared) */

DEFINE_func_80142DB8()  /* dedup: shared engine-core @0x80142DB8 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (combined store-assign `*(p)=v0=call()` keeps test/store on $v0, copy to $s0 for the else)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);

extern int D_8017F154;

void func_80142DC4(int param_1)
{
    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))func_8012C1B8)();
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, s32))func_8001CA1C)(v0, (s32)&D_8017F154);
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

extern unsigned char D_8017F170[];

void func_80142E38(int param_1)
{
    short sVar1;
    int iVar2;

    *(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))func_8012C1B8)();
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(iVar2, &D_8017F170);
        sVar1 = (*(unsigned short *)(param_1 + 0x70) & 0xf) * 0x600 + 0x1200;
        *(short *)(iVar2 + 0x1a) = sVar1;
        *(short *)(iVar2 + 0x18) = sVar1;
        *(short *)(param_1 + 0xfc) = 0;
        ((void (*)(int))func_80142B2C)(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80142EC0);

DEFINE_func_80142F68()  /* dedup: shared engine-core @0x80142F68 (src/shared) */

DEFINE_func_80142FFC()  /* dedup: shared engine-core @0x80142FFC (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (38 ins). $16=param pin; explicit $17 copy of the call result
//         survives across func_8001CA1C while $v0 serves the pre-call store/test;
//         store BEFORE the s1 copy so the store keeps $v0 (not the saved copy).

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);

extern unsigned char D_8017F35C[];
extern unsigned char D_8017F3BC[];

void func_8014305C(int param_1)
{
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
        ((void (*)(int, void *))func_8001CA1C)(s1_copy, D_8017F35C);
        sVar1 = (*(unsigned short *)(s0_param + 0x70) & 0xf) * 0x600 + 0xc00;
        *(short *)(s1_copy + 0x1a) = sVar1;
        *(short *)(s1_copy + 0x18) = sVar1;
        *(short *)(s0_param + 0xfc) = 0;
        func_8012A828(s0_param, D_8017F3BC);
        ((void (*)(int))func_80142B2C)(s0_param);
    }
}


DEFINE_func_801430F4()  /* dedup: shared engine-core @0x801430F4 (src/shared) */

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

extern u8 D_8019B514;
extern u8 D_8019BE78;
extern u8 D_8019BE7C;

void func_801431E8(s32 param_1) {
    u8 buf[8];
    s32 iVar5;
    u16 uVar2;
    s16 sVar4;

    register s32 d __asm__("$16");
    memcpy(buf, &D_8019B514, 4);
    iVar5 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar5;
    d = iVar5;
    if (iVar5 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001CA88)(d, &D_8019BE78);
        uVar2 = *(u16 *)(param_1 + 0x70);
        *(s16 *)(d + 0x76) = -0x10;
        sVar4 = (uVar2 & 0xf) * 0x600 + 0xc00;
        *(s16 *)(d + 0x1a) = sVar4;
        *(s16 *)(d + 0x18) = sVar4;
        *(u32 *)(d + 4) = *(u32 *)(d + 4) | 0x50000000;
        if (func_8012E504(param_1, 0x33) == 0) {
            *(s16 *)(param_1 + 0xfc) = 1;
            func_800233CC(&D_8019BE78, 0x10);
            memcpy(&D_8019BE7C, buf, 4);
        } else {
            *(s16 *)(param_1 + 0xfc) = 0;
        }
        ((void (*)(s32))func_80142B2C)(param_1);
    }
}


DEFINE_func_801432FC()  /* dedup: shared engine-core @0x801432FC (src/shared) */

DEFINE_func_80143390()  /* dedup: shared engine-core @0x80143390 (src/shared) */

DEFINE_func_801433F0()  /* dedup: shared engine-core @0x801433F0 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80143458);

DEFINE_func_8014350C()  /* dedup: shared engine-core @0x8014350C (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_8014358C);

DEFINE_func_80143640()  /* dedup: shared engine-core @0x80143640 (src/shared) */

DEFINE_func_801437D8()  /* dedup: shared engine-core @0x801437D8 (src/shared) */

DEFINE_func_80143970()  /* dedup: shared engine-core @0x80143970 (src/shared) */

DEFINE_func_80143994()  /* dedup: shared engine-core @0x80143994 (src/shared) */

DEFINE_func_801439C0()  /* dedup: shared engine-core @0x801439C0 (src/shared) */

DEFINE_func_801439FC()  /* dedup: shared engine-core @0x801439FC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80143B30);

DEFINE_func_80143B6C()  /* dedup: shared engine-core @0x80143B6C (src/shared) */

DEFINE_func_80143BDC()  /* dedup: shared engine-core @0x80143BDC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80143C38);

DEFINE_func_80143C74()  /* dedup: shared engine-core @0x80143C74 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80143C98);

DEFINE_func_80143CD4()  /* dedup: shared engine-core @0x80143CD4 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80143D28);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80143E68);

DEFINE_func_80143EA4()  /* dedup: shared engine-core @0x80143EA4 (src/shared) */

DEFINE_func_80143EAC()  /* dedup: shared engine-core @0x80143EAC (src/shared) */

DEFINE_func_80143EB4()  /* dedup: shared engine-core @0x80143EB4 (src/shared) */

DEFINE_func_80143EBC()  /* dedup: shared engine-core @0x80143EBC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80144054);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80144090);

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801442F8);


extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8017F630;

void func_80144364(int param_1) {
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
        func_8001CB6C((u8 *)iVar3, (s32)&D_8017F630, 0x250, 0x1A0);
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




extern void func_80016714(void *a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80128ED8(void *a0, void *a1);
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern s32 D_8017F644;

void func_80144458(void *arg0) {
    s32 temp_s0;
    void *temp_s2;
    void *temp_v0;

    temp_s2 = M2C_FIELD(arg0, void **, 0xCC);
    if (M2C_FIELD(arg0, s16 *, 0x70) == 0) {
        temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x64), void **, 0x20);
        if (temp_v0 != NULL) {
            temp_s0 = (M2C_FIELD(temp_v0, s16 *, 0x12) - 0x400) & 0xFFF;
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (func_80047948(temp_s0) * D_8017F644 * 0x10);
            M2C_FIELD(arg0, s32 *, 0x18) = (s32) (func_8004787C(temp_s0) * -D_8017F644 * 0x10);
            func_8012AD80(arg0);
        }
    }
    M2C_FIELD(temp_s2, u16 *, 8) = (u16) M2C_FIELD(arg0, u16 *, 6);
    M2C_FIELD(temp_s2, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
    M2C_FIELD(temp_s2, u16 *, 0xC) = (u16) M2C_FIELD(arg0, u16 *, 0xE);
    if (func_80128ED8(temp_s2, arg0 + 0xD0) != 0) {
        func_80016714(temp_s2, 0x38);
        func_8012C218(arg0);
    }
}


DEFINE_func_80144558()  /* dedup: shared engine-core @0x80144558 (src/shared) */

DEFINE_func_8014462C()  /* dedup: shared engine-core @0x8014462C (src/shared) */

DEFINE_func_801446A4()  /* dedup: shared engine-core @0x801446A4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (65 ins, match_one). Levers: uVar2/$2 + addr/$3 pins; split (uVar2&0xFFFFFFF) into addr then (addr|0x80000000)+8 deref; %hi/%lo of 0x80000008 via plain 0x80000000+8 (match_one masks the target's D_80000008 reloc, real bytes identical); v1/3 magic-divide; gv+fv reassoc (field-0x30 in own temp) loads field first
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_8017F658;
extern u8 D_8017F664;

void func_8014477C(void *param_1) {
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
    ((void (*)(s32, void *))func_8001CA1C)(v0, &D_8017F658);
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
    ((void (*)(void *, void *))func_8012A828)(param_1, &D_8017F664);
    v1 = (s32)*(s16 *)((s32)param_1 + 0x70) << 0xC;
    *(s16 *)((s32)param_1 + 0x2) = 1;
    *(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) = v1 / 3;
    *(s32 *)((s32)param_1 + 0x1C) = 0x78;
}



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);

extern u8 D_8017F630;
extern u8 D_8017F6A0;

void func_80144880(s32 param_1)
{
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
            func_8001CB6C((u8 *)obj, (s32)&D_8017F630, 0x250, 0x1A0);
            b = 0x14;
        } else {
            func_8001CB6C((u8 *)obj, (s32)&D_8017F6A0, 0x300, 0x1D0);
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

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_801449C8);

DEFINE_func_80144A04()  /* dedup: shared engine-core @0x80144A04 (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80144A2C);

DEFINE_func_80144A68()  /* dedup: shared engine-core @0x80144A68 (src/shared) */

DEFINE_func_80144A90()  /* dedup: shared engine-core @0x80144A90 (src/shared) */

DEFINE_func_80144A98()  /* dedup: shared engine-core @0x80144A98 (src/shared) */

DEFINE_func_80144AEC()  /* dedup: shared engine-core @0x80144AEC (src/shared) */

INCLUDE_ASM("asm/ov_SC05_011/nonmatchings/ov_SC05_011", func_80144B14);
