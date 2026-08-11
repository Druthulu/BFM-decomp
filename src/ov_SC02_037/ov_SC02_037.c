#include "common.h"
#include "../shared/engine_core.h"

DEFINE_func_80128158()  /* dedup: shared engine-core @0x80128158 (src/shared) */


DEFINE_func_80128178()  /* dedup: shared engine-core @0x80128178 (src/shared) */


DEFINE_func_80128198()  /* dedup: shared engine-core @0x80128198 (src/shared) */


DEFINE_func_801281B8()  /* dedup: shared engine-core @0x801281b8 (src/shared) */


DEFINE_func_801281D8()  /* dedup: shared engine-core @0x801281d8 (src/shared) */


DEFINE_func_801281F8()  /* dedup: shared engine-core @0x801281f8 (src/shared) */




s32 func_80128218(void) {

    extern s32 D_801C7200;
    return D_801C7200;
}


DEFINE_func_80128228()  /* dedup: shared engine-core @0x80128228 (src/shared) */


DEFINE_func_80128248()  /* dedup: shared engine-core @0x80128248 (src/shared) */


DEFINE_func_80128268()  /* dedup: shared engine-core @0x80128268 (src/shared) */




void func_80128288(void) {

    extern u16 D_800B99F6;
    extern void (*D_80183EA4[])(void);
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_80183EA4[v1]();
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


DEFINE_func_80128678()  /* dedup: shared engine-core @0x80128678 (src/shared) */


extern void func_80128564(void);

// @class: other
// @stuck: none — MATCH (handwritten full inline-asm scratchpad-stack-switch wrapper w/ branch)
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
// @stuck: none — MATCH (62 ins). D_801C9A78 read needed the address REMATERIALIZED
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
extern void func_8013BC7C(void);
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
    ((void (*)(void *))func_801508B4)(&D_80126B58);
    func_80165E90();
    func_801627E8();
    func_80162B1C();
    func_80165CA0();
    func_80129010();
    func_8013CA14();
    func_800190AC();
    func_8012956C();
    ((void (*)(void))func_8016E95C)();
    func_801754A8();
    {
        /* D_801C9A78 read: the target materializes &sym into $a0 then lw 0($a0) (not the folded
         * lui;lw %lo). volatile forces the rematerialize; the $4 pin forces the a0 allocation. */
        register volatile s32 *p __asm__("$4") = &D_801C9A78;
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

    extern s32 D_801C7200;
    extern u8 D_800AEFD0;
    func_8001ABBC(0, 0, &D_800AEFD0, D_801C7200, 0);
}



// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x60 store AND arg5; writing D_800C7C60=0x60 directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.


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
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x5e store AND arg5; writing D_800C7C60=0x5e directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.


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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80128998);



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


DEFINE_func_80128C14()  /* dedup: shared engine-core @0x80128c14 (src/shared) */




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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80128CFC);

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

    extern M2C_UNK D_801C7204;
    func_8001534C(4, &D_801C7204, 0x80, 0x90, 0, 0);
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
        goto next;
    case_7FFE:
        func_801299C8(D_801C9A58, (s16)(i * 2), base);
        func_80015B6C(-0xA0, *(s16 *)&base->f3A, 0x140, base->f3E,
                      ((u8 *)&D_801C83AC)[idx], D_801C83AD[idx], D_801C83AE[idx],
                      D_801C83B0[idx], D_801C83B1[idx], D_801C83B2[idx]);
        goto next;
    do_default:
        __asm__("");
        arg0 = D_801C9A58;
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801299C8);

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





// @class: regalloc-order
// @stuck: none — MATCH (78 ins, relocation-masked). Register pins ($2-$5 reused for
//   the D_x200-x20C words then the D_x220-x226 halfwords; $6-$10 held across for the
//   D_x228/x22A/x294/x298/x29A tail) force the frameless 9-deep allocation the default
//   -O2 pre-reload scheduler otherwise blows to a 3-reg spill (all 720 stmt orders spill
//   without the pins). A single zero-byte scheduling/memory barrier after the 4 word
//   stores stops gcc hoisting the first 8-byte block copy above them.




void func_8012A1BC(void) {

    extern s16 D_80120218;
    extern s16 D_80120222;
    extern s16 D_80120224;
    extern s16 D_80120226;
    extern s16 D_80120228;
    extern s16 D_8012022A;
    extern s16 D_8012029A;
    extern s32 D_80120200, D_80120204, D_80120208, D_8012020C;
    extern s16 D_80120210;
    extern s16 D_80120220;
    extern s32 D_80120294;
    extern s16 D_80120298;
    extern s32 D_80126950, D_80126954, D_80126958, D_8012695C;
    extern Blk8 D_80126960, D_80126968;
    extern u16 D_80126970, D_80126972, D_80126974, D_80126976, D_80126978, D_8012697A;
    extern s32 D_801269E4;
    extern u16 D_801269E8, D_801269EA;
    register s32 r2 __asm__("$2"), r3 __asm__("$3"), r4 __asm__("$4"), r5 __asm__("$5");
    register u16 r6 __asm__("$6"), r7 __asm__("$7");
    register s32 r8 __asm__("$8");
    register u16 r9 __asm__("$9"), r10 __asm__("$10");

    r2 = D_80120200; r3 = D_80120204; r4 = D_80120208; r5 = D_8012020C;
    r6 = (*(u16 *)&D_80120228); r7 = (*(u16 *)&D_8012022A); r8 = D_80120294; r9 = (*(u16 *)&D_80120298); r10 = (*(u16 *)&D_8012029A);
    D_80126950 = r2; D_80126954 = r3; D_80126958 = r4; D_8012695C = r5;
    __asm__ __volatile__("" ::: "memory");
    D_80126960 = (*(Blk8 *)&D_80120210);
    r2 = (*(u16 *)&D_80120220); r3 = (*(u16 *)&D_80120222); r4 = (*(u16 *)&D_80120224); r5 = (*(u16 *)&D_80120226);
    D_80126968 = (*(Blk8 *)&D_80120218);
    D_80126978 = r6; D_8012697A = r7; D_801269E4 = r8; D_801269E8 = r9; D_801269EA = r10;
    D_80126970 = r2; D_80126972 = r3; D_80126974 = r4; D_80126976 = r5;
}


DEFINE_func_8012A2F4()  /* dedup: shared engine-core @0x8012a2f4 (src/shared) */


DEFINE_func_8012A304()  /* dedup: shared engine-core @0x8012a304 (src/shared) */










extern s32 func_80012F74(s32, s32, s32, s32);

void func_8012A328(void)
{

    extern s8 D_801152C0;
    extern s16 D_801152C2;
    extern s16 D_80126940;
    extern s16 D_80126942;
    extern s16 D_80126944;
    extern s32 D_80126B58;
    extern s16 D_80127080;
    extern s16 D_80126CAE;
    Obj_80126B58 *p = (Obj_80126B58 *)&D_80126B58;
    s16 *q;
    s32 a, b;
    if (*(u8 *)&D_801152C0 != 0) {
        a = D_80127080; b = D_80126CAE;
        if (D_801152C2 < ((a - b) < 0 ? (b - a) : (a - b))) {
            q = &D_80126942;
            *q = func_80012F74(*q, p->f156, 4, 1);
        } else {
            q = &D_80126942;
            *q = func_80012F74(*q, D_80127080, 4, 1);
        }
    } else {
        s16 *r = &D_80126942;
        *r = func_80012F74(*r, D_80126CAE, 4, 1);
    }
    D_80126940 = p->f154;
    D_80126944 = p->f158;
}


DEFINE_func_8012A418()  /* dedup: shared engine-core @0x8012a418 (src/shared) */


DEFINE_func_8012A464()  /* dedup: shared engine-core @0x8012a464 (src/shared) */


DEFINE_func_8012A4BC()  /* dedup: shared engine-core @0x8012a4bc (src/shared) */


extern void func_8012A598(void *a0);
void func_8012A568(void (*a0)(void)) {
    func_8012A598(a0);
    a0();
}


DEFINE_func_8012A598()  /* dedup: shared engine-core @0x8012a598 (src/shared) */


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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8012AAAC);



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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8012ACE0);

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


DEFINE_func_8012B4B8()  /* dedup: shared engine-core @0x8012b4b8 (src/shared) */


DEFINE_func_8012B608()  /* dedup: shared engine-core @0x8012b608 (src/shared) */


DEFINE_func_8012B6D4()  /* dedup: shared engine-core @0x8012b6d4 (src/shared) */


DEFINE_func_8012B70C()  /* dedup: shared engine-core @0x8012b70c (src/shared) */


DEFINE_func_8012B744()  /* dedup: shared engine-core @0x8012b744 (src/shared) */


extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

s32 func_8012B77C(s32 out, s32 a1, s32 a2)
{
    register u32 packed __asm__("$20");
    s32 dz;
    s32 dx;
    s32 dy;
    register s32 t __asm__("$16");
    s32 sn;
    s32 cs;
    s32 ang;

    packed &= 0xFFFF;

    dz = *(s16 *)((s32)a2 + 0xA) - *(s16 *)((s32)a1 + 0xA);
    dx = *(s16 *)((s32)a2 + 0x2) - *(s16 *)((s32)a1 + 0x2);
    dy = *(s16 *)((s32)a2 + 0x6) - *(s16 *)((s32)a1 + 0x6);

    ang = ratan2(-dz, dx);
    t = ang - 0x400;
    t &= 0xFFF;
    packed |= (u32)(t << 16);

    sn = func_80047948(t);
    cs = func_8004787C(t);

    dz = (dz * sn + dx * cs) >> 12;
    ang = ratan2(dy, -dz);
    packed &= 0xFFFF0000;
    packed |= (u32)(ang & 0xFFFF);

    {
        u32 addr;
        __asm__("addu %0,%1,$zero" : "=r"(addr) : "r"(out));
        *(u32 *)addr = packed;
    }
}


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


DEFINE_func_8012C658()  /* dedup: shared engine-core @0x8012c658 (src/shared) */


DEFINE_func_8012C724()  /* dedup: shared engine-core @0x8012c724 (src/shared) */


DEFINE_func_8012C750()  /* dedup: shared engine-core @0x8012c750 (src/shared) */


DEFINE_func_8012C820()  /* dedup: shared engine-core @0x8012c820 (src/shared) */


            typedef struct { s8 c[8]; } Blk8_8012C890;

// @class: schedule
// @stuck: none — MATCH (149 ins). Counter (*(u16 *)&D_801270C4): gcc CSE's the two reads (store to
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




DEFINE_func_8012CC88()  /* dedup: shared engine-core @0x8012CC88 (src/shared) */


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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8012D664);

DEFINE_func_8012D714()  /* dedup: shared engine-core @0x8012d714 (src/shared) */




extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);

s32 func_8012DB84(void)
{

    extern M2C_UNK D_80183F50;
    extern M2C_UNK D_80183F58;
    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, &D_80183F50, &D_80183F58);
}


DEFINE_func_8012DBD0()  /* dedup: shared engine-core @0x8012dbd0 (src/shared) */




// @class: regalloc-order
// @stuck: none — MATCH




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
// @stuck: none — MATCH (35/35 ins, relocation-masked)


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


DEFINE_func_8012DEB8()  /* dedup: shared engine-core @0x8012deb8 (src/shared) */


DEFINE_func_8012DF34()  /* dedup: shared engine-core @0x8012df34 (src/shared) */


DEFINE_func_8012DFBC()  /* dedup: shared engine-core @0x8012dfbc (src/shared) */


void func_8012DFCC(void) {
}

DEFINE_func_8012DFD4()  /* dedup: shared engine-core @0x8012dfd4 (src/shared) */


DEFINE_func_8012E014()  /* dedup: shared engine-core @0x8012e014 (src/shared) */


DEFINE_func_8012E138()  /* dedup: shared engine-core @0x8012e138 (src/shared) */



s32 func_8012E27C(void) {
    return 1;
}


void func_8012E284(void) {
}

DEFINE_func_8012E28C()  /* dedup: shared engine-core @0x8012e28c (src/shared) */


DEFINE_func_8012E32C()  /* dedup: shared engine-core @0x8012e32c (src/shared) */


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
    e1 = *(s32 *)(arg0 + 0x20);
    v = D_801C83C0 - prev + spd;
    D_801C83C4 = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_801C83C0 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;

    e2 = *(s32 *)(arg0 + 0x20);
    d = __builtin_abs(v);
    *(s16 *)(e2 + 0x1C) = d;
    *(s16 *)(e2 + 0x18) = d;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x1000;
}


DEFINE_func_8012E470()  /* dedup: shared engine-core @0x8012e470 (src/shared) */


DEFINE_func_8012E4C8()  /* dedup: shared engine-core @0x8012e4c8 (src/shared) */


DEFINE_func_8012E504()  /* dedup: shared engine-core @0x8012e504 (src/shared) */


DEFINE_func_8012E544()  /* dedup: shared engine-core @0x8012e544 (src/shared) */


DEFINE_func_8012E57C()  /* dedup: shared engine-core @0x8012e57c (src/shared) */


DEFINE_func_8012E5CC()  /* dedup: shared engine-core @0x8012e5cc (src/shared) */


DEFINE_func_8012E688()  /* dedup: shared engine-core @0x8012e688 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8012E778);

DEFINE_func_8012E88C()  /* dedup: shared engine-core @0x8012e88c (src/shared) */


DEFINE_func_8012E8A8()  /* dedup: shared engine-core @0x8012e8a8 (src/shared) */


DEFINE_func_8012E8C4()  /* dedup: shared engine-core @0x8012e8c4 (src/shared) */


DEFINE_func_8012E8E0()  /* dedup: shared engine-core @0x8012e8e0 (src/shared) */




// @class: other
// @stuck: none — MATCH (branch-polarity invert: `0x78 != 0` puts compute block as fall-through)

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


DEFINE_func_8012EA90()  /* dedup: shared engine-core @0x8012ea90 (src/shared) */


DEFINE_func_8012EC04()  /* dedup: shared engine-core @0x8012ec04 (src/shared) */


DEFINE_func_8012EECC()  /* dedup: shared engine-core @0x8012eecc (src/shared) */


DEFINE_func_8012EF34()  /* dedup: shared engine-core @0x8012ef34 (src/shared) */


DEFINE_func_8012EF70()  /* dedup: shared engine-core @0x8012ef70 (src/shared) */


            typedef struct { s8 c[8]; } Blk8_8012EFB8;
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

s32 aF8012EFB8(param_1, param_2)
    void *param_1;
    void *param_2;
{
    extern u8 D_800AF648;
    s32 *m;
    s32 flag;

    m = (s32 *)&D_800AF648;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    gte_ldv0(param_1);
    gte_rtps();
    gte_stsxy(param_2);
    gte_stflg(&flag);
    return flag;
}


DEFINE_func_8012F038()  /* dedup: shared engine-core @0x8012f038 (src/shared) */


DEFINE_func_8012F0BC()  /* dedup: shared engine-core @0x8012f0bc (src/shared) */


DEFINE_func_8012F14C()  /* dedup: shared engine-core @0x8012f14c (src/shared) */


DEFINE_func_8012F1A4()  /* dedup: shared engine-core @0x8012f1a4 (src/shared) */


DEFINE_func_8012F214()  /* dedup: shared engine-core @0x8012f214 (src/shared) */


DEFINE_func_8012F274()  /* dedup: shared engine-core @0x8012f274 (src/shared) */


DEFINE_func_8012F2E8()  /* dedup: shared engine-core @0x8012f2e8 (src/shared) */


DEFINE_func_8012F374()  /* dedup: shared engine-core @0x8012f374 (src/shared) */





// @class: remat
// @stuck: none — MATCH

extern void func_8004914C();
extern void func_800491AC();
extern s32 RotTransPers(s32, s32, s32*, s32*);

s32 *func_8012F40C(s32 *param_1, s32 param_2) {

    extern u8 D_800AF648;
    s32 sxy, p, flag;

    sxy = 0;
    /* $a0-pinned scopes force the &D_800AF648 constant to be rematerialized
       (lui/addiu) before each call instead of CSE-hoisting it into a third
       callee-saved register. */
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
    ((s32 (*)(s32, s32 *, s32 *, s32 *))RotTransPers)(param_2, &sxy, &p, &flag);
    if (flag < 0) {
        *param_1 = sxy = 0;
    } else {
        *param_1 = sxy;
    }
    return param_1;
}


DEFINE_func_8012F49C()  /* dedup: shared engine-core @0x8012f49c (src/shared) */


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

    extern unsigned char D_80183F7C[];
    *(unsigned char *)(param_1 + 0xC1) = 4;
    if (*(unsigned int *)(param_1 + 0xB4) & 8) {
        func_80131170(param_1, D_80183F7C, 0xB);
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

    extern unsigned char D_80183F88[];
    *(unsigned char *)(param_1 + 0xC1) = 7;
    if (*(unsigned int *)(param_1 + 0xB4) & 128) {
        func_80131170(param_1, D_80183F88, 0xB);
    }
    func_80131CA8(param_1, 22);
}


DEFINE_func_8012F91C()  /* dedup: shared engine-core @0x8012f91c (src/shared) */


DEFINE_func_8012F968()  /* dedup: shared engine-core @0x8012f968 (src/shared) */


DEFINE_func_8012FB54()  /* dedup: shared engine-core @0x8012fb54 (src/shared) */


DEFINE_func_8012FC30()  /* dedup: shared engine-core @0x8012fc30 (src/shared) */


DEFINE_func_8012FCA4()  /* dedup: shared engine-core @0x8012fca4 (src/shared) */


            typedef struct { s8 c[8]; } Blk8_8012FCC4;

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


DEFINE_func_80130C08()  /* dedup: shared engine-core @0x80130c08 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80130D0C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80130D48);

extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_80131A34(s32, s32);
extern s32 func_80131AC8(void *a0);
extern void func_80131B14(void);
            typedef struct { s8 c[8]; } Blk8_80131170;


// @class: loop-guard
// @stuck: none — MATCH (88 ins). Keys: duplicate the c!=0/c==0 bodies verbatim (gcc cross-jumps
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
// @stuck: none — MATCH (8-byte alignment-1 struct copy → lwl/lwr/swl/swr)

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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80131340);

DEFINE_func_801319E0()  /* dedup: shared engine-core @0x801319e0 (src/shared) */




/* func_80131A34 — MATCH (37/37).
 * Keys:
 *  - func_80131CF4 is the TU's 2-arg canonical `(int,int)` and the SECOND arg is the
 *    incoming `a1` (kind). $a1 already holds it, so the call costs no arg-setup insn --
 *    but the extra arg ref is what breaks the sched2 prologue save-order tie so
 *    `sw $s0` schedules before `sw $ra` (cookbook §52a RC-3 / sched.md S7). Without it
 *    the pair comes out ra-then-s0 (2 mismatches); the `const`-load form of RC-3 fixes
 *    the tie but OVER-frees (the `lw $a0` hoists above both saves, 3 mismatches).
 *  - Declaration is BLOCK-SCOPE on purpose, mirroring func_801312D0 (TU L1619) and
 *    func_80131340 (TU L1822): the later DEFINE_func_80131AC8() re-declares
 *    func_80131CF4 with the stale 1-arg engine_core canonical, so a file-scope 2-arg
 *    decl here is a hard `conflicting types` (cc1 rc=33).
 *  - func_8012A828 is the TU's file-scope canonical (L280) `(s32, void *)`; `p` rides in
 *    $a1 from the return of func_80131CF4, so no move is emitted.
 */
extern void func_8012A828(s32 a0, void *a1);

s32 func_80131A34(s32 a0, s32 a1)
{
    extern s32 func_80131CF4(s32);
    void *p;

    p = (void *)((int (*)(int, int))func_80131CF4)(*(s32 *)(a0 + 0xBC), a1);
    if (p != 0) {
        if (a1 == 0xB || a1 == 8 || a1 == 0x20) {
            *(s32 *)(a0 + 0xC4) |= 4;
        } else {
            *(s32 *)(a0 + 0xC4) &= -5;
        }
        func_8012A828(a0, p);
        return 1;
    }
    return 0;
}


DEFINE_func_80131AC8()  /* dedup: shared engine-core @0x80131ac8 (src/shared) */


extern void func_80019064(void *a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
            typedef struct { s8 c[8]; } Blk8_80131B14;

// @class: regalloc-order
// @stuck: none — MATCH (89 ins). Reconcile: TU canonical decl is `void func_80131B14(void)`
//   (ov_SC01_077_a.c L1676/L1756; callers cast to (void(*)(int)) when passing p), so the def MUST be
//   (void) or cc1 hard-errors `conflicting types` (exit 33). §42c lever #6: capture incoming $a0 into a
//   NORMAL pseudo (`register u8 *a0v __asm__("$4"); u8 *p = a0v;`) so p gets a callee-saved home ($s0).
//   func_8012B2CC/func_8012B23C are file-scope DEFINE'd here (split L740/L744) as void(s32) — do NOT redeclare;
//   the (void(*)(void*)) cast on the bare name is byte-neutral. Body keys: e(0x5E) as s32 not u8 (kills the
//   compare-time andi 0xff); f76 dual-width via per-access casts (lhu in the decrement, lh in the <=0 compare);
//   the p->f20 reload split into TWO separate temps so the 2nd load takes $v0 not $v1.

void func_80131B14(void) {
    register u8 *a0v __asm__("$4");
    u8 *p = a0v;

    extern void func_8002A520(void *);
    extern void func_8002A790(void *);
    extern u8 D_801840CC;

    s32 e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(s16 *)(p + 0x82) = 0;
            *(s16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(s16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(s16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec <= 0) dec = 1;
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
        }
        ((void (*)(void *))func_8016AA50)(p);
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            ((void(*)(void *))func_80019064)(&D_801840CC);
        }
    }

    *(u16 *)(p + 0x5C) = *(u16 *)(p + 0x5C) & 0xFFFE;

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) <= 0) *(s16 *)(p + 0x5C) = 0;

    {
        s32 r = *(s32 *)(p + 0x20);
        *(s16 *)(r + 0x12) = (*(u16 *)(p + 0x62) + 0x800) & 0xFFF;
        {
            s32 r2 = *(s32 *)(p + 0x20);
            *(s16 *)(r2 + 0x14) = 0;
            *(s16 *)(r2 + 0x10) = 0;
        }
    }

    ((void (*)(void *))func_8012B2CC)(p);
    ((void (*)(void *))func_8012B23C)(p);
}


DEFINE_func_80131C78()  /* dedup: shared engine-core @0x80131c78 (src/shared) */


            typedef struct { s8 c[8]; } Blk8_80131CA8;

/* func_80131CA8 — RECONCILE (§37/§124 asm-label alias)
 *
 * Declaration-environment conflict, NOT a body problem:
 *   The TU's DEFINE_func_80131C78() expansion (jr_8012ACE0.c L2232) and the later
 *   DEFINE_func_80131D68() expansion (L2250) each emit the canonical
 *       extern void func_80131CA8(int a0, int a1);
 *   (src/shared/engine_core.h, e.g. L1961/L4131). The byte-correct body is
 *   `s32 f(int)` — it disagrees on BOTH the return axis (s32 vs void) and the
 *   arity axis (1 vs 2), so it collides with the macro-emitted declaration on
 *   either side of the slot. Escape 1 (conform + cast at use) cannot apply: the
 *   conflict is on the DEFINED symbol itself.
 *
 * Fix: define under the C name aF80131CA8 with __asm__("func_80131CA8") so the
 * C-level name never meets the canonical declaration, while the emitted symbol
 * is unchanged. Codegen-neutral — match_one still prints MATCH (19/19).
 * This declaration MUST travel with the body.
 *
 * func_80131CF4 is declared here 1-arg s32, matching the engine_core canonical
 * at engine_core.h L6563; it does not collide anywhere in this TU (verified by
 * a full preprocess+cc1 of the spliced TU: diagnostic-free apart from
 * pre-existing warnings).
 */
extern s32 func_80131CF4(s32 a0);

s32 aF80131CA8(int a0) __asm__("func_80131CA8");

s32 aF80131CA8(int a0)
{
    s32 (*fp)(int) = (s32 (*)(int))func_80131CF4(*(s32 *)((u8 *)a0 + 0xBC));
    if (fp != 0) {
        fp(a0);
        return 1;
    }
    return 0;
}


            typedef struct { s8 c[8]; } Blk8_80131CF4;


/* func_80131CF4 — table lookup: walk (key, value) pairs; key 0xD chains to the
 * next table via value; key == wanted returns value; key 0 terminates.
 *
 * The __asm__ inside the body is a matching pin, not logic. It does two things
 * gcc-2.7.2 -O2 needs in order to reproduce the target's preheader exactly:
 *   1. "0"(0xD) forces the 0xD compare constant to be materialised HERE
 *      (`addiu $v1,$zero,0xD`) instead of being loop-hoisted, which places it
 *      AFTER the preheader load and drops the load-delay nop at the loop head.
 *   2. the "memory" clobber stops CSE folding the preheader re-read of a0[0]
 *      into the guard's read (that CSE costs the second `lw $v0,0x0($a0)`).
 * The asm body is empty, so it emits no instruction of its own.
 *
 * RECONCILE (§37/§124 asm-label alias) — the gate error was
 *   jr_8012ACE0.c:2248 conflicting types for func_80131CF4 || :2164 previous declaration
 * :2164 is `DEFINE_func_80131AC8()`, whose expansion (src/shared/engine_core.h:6563)
 * carries the STALE 1-arg engine-core canonical `extern s32 func_80131CF4(s32 a0);`.
 * That prototype is wrong for this function (the TU's own call sites at L1780/L1903/
 * L2147 all declare and call the real 2-arg form `int func_80131CF4(int, int)`), but
 * it is file-visible before the splice point, so a file-scope definition with the true
 * signature is a hard `conflicting types` (arity AND param type). Conforming the
 * definition to the 1-arg prototype is impossible without changing codegen, and the
 * §42 `register s32 a1 __asm__("$5")` route would still leave the param-type mismatch
 * on a0 (s32 vs s32*). So the definition is given a different C identifier and pinned
 * to the real symbol with an asm label: no declaration ever collides, the emitted
 * label is still `func_80131CF4`, and the callers' `jal func_80131CF4` binds to it.
 * Zero header edits; body byte-identical (match_one: MATCH, 29 ins).
 */
s32 aF80131CF4(s32 *a0, s32 a1) __asm__("func_80131CF4");

s32 aF80131CF4(s32 *a0, s32 a1) {
    s32 v0;
    s32 k;

    if (a0 == 0) {
        return 0;
    }
    goto enter;
found:
    return a0[1];
enter:
    if (a0[0] == 0) {
        return 0;
    }
    __asm__ __volatile__("" : "=r"(k) : "0"(0xD) : "memory");
    v0 = a0[0];
    do {
        if (v0 == k) {
            a0 = (s32 *)a0[1];
        } else {
            if (v0 == a1) {
                goto found;
            }
            a0 = (s32 *)((u8 *)a0 + 8);
        }
        v0 = a0[0];
    } while (v0 != 0);
    return 0;
}


DEFINE_func_80131D68()  /* dedup: shared engine-core @0x80131d68 (src/shared) */





void func_80131E00(struct S80131E00 *a0, s32 a1) {

    extern void (*D_801840DC[])(struct S80131E00 *a0);
    a0->field_B0 = a1;
    D_801840DC[a1](a0);
}


DEFINE_func_80131E38()  /* dedup: shared engine-core @0x80131e38 (src/shared) */


DEFINE_func_80131E7C()  /* dedup: shared engine-core @0x80131e7c (src/shared) */


void func_80131EE4(void) {
}



void func_80131EEC(void *a0) {

    extern void (*D_80184134[])(void);
    D_80184134[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131F28(void *a0) {

    extern void (*D_8018417C[])(void);
    D_8018417C[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131F64(void *a0) {

    extern void (*D_80184184[])(void);
    D_80184184[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131FA0(void *a0) {

    extern void (*D_8018418C[])(void);
    D_8018418C[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80131FDC(void *a0) {

    extern void (*D_80184194[])(void);
    D_80184194[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

/* §37 asm-label aliases: D_80184134 is declared in this TU as `void (*[])(void)`
 * (func_80131EEC's dispatch table) — a conflicting type. The 20-byte-stride view
 * below is this function's own. D_80184138 == D_80184134 + 4 is a SEPARATE
 * per-overlay symbol and is referenced BY NAME, never as base+literal (§84). */

void func_80132018(int param_1)
{

    extern int tbl_D_80187044[][5] __asm__("D_80184134");
    extern int tbl_D_80187048[][5] __asm__("D_80184138");
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
        *(int *)(param_1 + 0x58) = (int)&tbl_D_80187048[*(unsigned short *)(param_1 + 0x70) & 0xfff];
        *(int *)(param_1 + 0xdc) = tbl_D_80187044[*(unsigned short *)(param_1 + 0x70) & 0xfff][0];
        *(short *)(param_1 + 0xfc) = (*(unsigned short *)(param_1 + 0x70) >> 12) << 9;
    }
}


void func_801320D0(void) {
}


// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

void func_801320D8(int param_1)
{

    extern int D_8018413C;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018413C;
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

    extern int D_8018414C;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018414C;
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

    extern int D_8018415C;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018415C;
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

    extern int D_8018416C;
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018416C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}


DEFINE_func_80132288()  /* dedup: shared engine-core @0x80132288 (src/shared) */


DEFINE_func_8013240C()  /* dedup: shared engine-core @0x8013240c (src/shared) */


DEFINE_func_801325B8()  /* dedup: shared engine-core @0x801325b8 (src/shared) */


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


            typedef struct { s8 c[8]; } Blk8_80132F40;

/* func_80132F40 — ov_SC01_077 (jr_8012ACE0 region), 72 ins, -O2.  *** MATCH ***
 *
 * Verified:
 *   python3 tools/match_one.py func_80132F40 --c .run/near6/wave23/func_80132F40.c \
 *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8012ACE0
 *   -> MATCH (72 ins)
 *
 * ---------------------------------------------------------------------------
 * WHAT THE WAVE-22 SEED GOT WRONG (the 6-mismatch plateau, and why s32 "cost 3")
 * ---------------------------------------------------------------------------
 * The seed's note blamed the `addiu $s3,$sp,0x10` hoist on a *whole-function CSE
 * fork keyed on s16-vs-s32 w/h*, and concluded the s32 world was unreachable.
 * Both halves of that are wrong, and the real mechanism is a reusable idiom.
 *
 * The hoisted register is the block-move source-address pseudo (reg 83 =
 * `(plus fp 16)`, created by expand for `v[1] = v[0]`).  Whether it survives is
 * decided by ONE thing: does CSE's *extended basic block* still contain it when
 * CSE reaches the two `&v[0]` call arguments?
 *
 *   cse.c:cse_end_of_basic_block scans `while (p && GET_CODE (p) != CODE_LABEL)`.
 *   It can walk PAST a conditional jump only via
 *     - follow_jumps  : target label preceded by a BARRIER, LABEL_NUSES == 1, or
 *     - skip_blocks   : "branch around a block", no labels inside  (-O2 sets both)
 *   and it BREAKS EARLY on
 *     `if (! after_loop && NOTE_LINE_NUMBER (p) == NOTE_INSN_LOOP_END) break;`
 *
 * With s16 w the min block stayed a *diamond* (jump.c's `if(..) x=a; else x=b;`
 * -> `x=b; if(..) x=a;` at jump.c:699 is blocked when the moved insn carries a
 * REG_EQUAL note — the sign_extend note from the sll/sra pair).  The diamond's
 * BARRIER + join label ended CSE's block before the calls, so `&v[0]` was
 * recomputed at each site.  With s32 w the diamond was flattened in jump1, and
 * skip_blocks then walked CSE straight through to both call sites -> reg 83 was
 * substituted, went live across a call, and took a 5th callee-saved register.
 * So the fork was never about the *type* — it was about the CFG shape at CSE.
 *
 * ---------------------------------------------------------------------------
 * THE NEW LEVER  (cookbook candidate: "zero-instruction CSE path cut")
 * ---------------------------------------------------------------------------
 * `do { } while (0);` emits NOTE_INSN_LOOP_BEG/CONT/END and ZERO instructions.
 * A NOTE_INSN_LOOP_END is exactly what cse1 (after_loop == 0) breaks its
 * extended basic block on.  Dropping one between the struct copy and the call
 * sites cuts the path, kills the hoist, and costs nothing:  73 ins -> 70 ins.
 * (Measured: without it this same file is 75 ins / 58 mismatched.)
 * It is *not* an ordering/pressure hack — 1..8 empty `__asm__ __volatile__("")`
 * barriers, which lengthen live ranges but emit no LOOP notes, changed the hoist
 * by exactly nothing, which refutes the global.c allocno-priority explanation.
 *
 * ---------------------------------------------------------------------------
 * THE MIN BLOCK (idx 37..44)
 * ---------------------------------------------------------------------------
 *      lh   $v1,8($v0)      w        (both loads are SImode sign_extend -> `lh`)
 *      lh   $v0,0xA($v0)    h        (reuses the dying pointer's $v0)
 *      nop                           (load-delay; nothing schedulable)
 *      addu $a0,$v0,$zero   hh = h   (a REAL source-level carrier)
 *      slt  $v0,$v0,$v1     c = h<w  (reuses $v0 because hh now carries h)
 *      beqz $v0,.L80132FF4
 *       addu $s2,$v1,$zero  m = w    (else-arm, moved by jump.c:699 in jump2)
 *      addu $s2,$a0,$zero   m = hh
 *
 * Three locals legitimately share $v0 back-to-back — p dies at h's load, h dies
 * at the slt (hh carries its value), c is born there.  That chain is what makes
 * `slt $v0,$v0,$v1` possible and is why the carrier is mandatory: with h and c
 * on $2 but NO carrier, gcc emits `addu $s2,$v0,$zero` after the slt has already
 * clobbered $v0 — silently wrong code.  Do not remove `hh`.
 *
 * The carrier must be a *pinned* hard register: as a plain pseudo, cse2 (which
 * runs with after_loop == 1 and therefore ignores the LOOP_END) canonicalises it
 * back to h via canon_reg and flow deletes the copy (measured: 71 ins).
 *
 * Ablations (each measured with match_one):
 *   drop the do{}while(0) -> 75 ins / 58     drop `p`  pin -> 71 ins / 40
 *   drop `h`  pin         -> 71 ins / 33     drop `c`  pin -> 70 ins / 36
 *   drop `hh` pin         -> 71 ins / 32     drop `q`  pin -> 72 ins / 12
 *   adding a `w`->$3 pin or an `m`->$18 pin -> still MATCH (so both are omitted)
 *
 * Canonical decls (wave22_targets.json sig_hints) verbatim; D_80126BE0 is
 * declared exactly as the 20+ sibling TUs already declare it.
 */
extern void func_8012F038(int param_1, short *param_2, short *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32, s32, s32, s32);

void func_80132F40(s32 arg0)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u8 D_80126BE0[];

    Svec_80132F40 v[4];
    register Svec_80132F40 *q __asm__("$17");
    register s16 *p __asm__("$2");
    register s32 h __asm__("$2");
    register s32 c __asm__("$2");
    register s32 hh __asm__("$4");
    s32 w;
    s32 m;

    q = &v[1];
    v[0].vx = D_80126B5E;
    v[0].vy = D_80126B62;
    v[0].vz = D_80126B66;
    v[1] = v[0];

    if (func_80135888(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58),
                      (s32)D_80126BE0, (s32)q) != 0) {
        /* zero-instruction NOTE_INSN_LOOP_END: cuts cse1's extended basic block
         * so the block-move address pseudo cannot reach the two &v[0] args. */
        do { } while (0);

        p = (s16 *)((*(s32 *)(arg0 + 0x58) & 0x0FFFFFFF) | 0x80000000);
        w = p[4];
        h = p[5];
        hh = h;
        c = (h < w);
        if (c) { m = hh; } else { m = w; }

        func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34, &v[0], q);
        v[1].vy = m;
        func_8012F14C(*(s32 *)(arg0 + 0x20) + 0x34, q, &v[0]);
        D_80126B5E = v[0].vx;
        D_80126B62 = v[0].vy;
        D_80126B66 = v[0].vz;
    }
}


DEFINE_func_80133060()  /* dedup: shared engine-core @0x80133060 (src/shared) */


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
#define gte_rtv0tr() __asm__ volatile (                  \
    "nop;"                                               \
    "nop;"                                               \
    "mvmva 1, 0, 0, 0, 0"                                \
    :                                                    \
    :                                                    \
    : "memory" )
#define gte_stlvnl(r0) __asm__ volatile (                \
    "swc2 $25, 0( %0 );"                                 \
    "swc2 $26, 4( %0 );"                                 \
    "swc2 $27, 8( %0 )"                                  \
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

DEFINE_func_801330E0()  /* dedup: shared engine-core @0x801330E0 (src/shared) */



/* 32-byte opaque block: drives gcc's movstrsi block-move (4x lw / 4x sw, cookbook
 * struct-fold) instead of 8 serial lw/sw pairs. Locally named (engine_types.h's
 * identical `Blk32` is an anonymous-tag typedef -> a same-name redefinition here
 * is a C89 error in the real TU). */


extern void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2);
extern void func_8012B2CC(s32 a0);
extern void func_8013339C(s16 *a0, s16 *a1);
extern void func_8012F1A4(s32 *a0, s32 a1, s32 *a2);

void func_80133298(s32 *a0)
{

    extern u8 D_80126B5C; /* canonical decl (engine_core.h DEFINE_func_8012BD14) */
    extern s32 D_80126B5C_w __asm__("D_80126B5C"); /* same symbol, s32 view */
    extern s32 D_80126B60;
    extern s32 D_80126B64;
    s32 in[3];
    s32 out[3];
    s32 tmp[3];
    Blk32L m;

    in[0] = D_80126B5C_w;
    in[1] = D_80126B60;
    in[2] = D_80126B64;
    func_8012F0BC((s32 *)(a0[8] + 0x34), in, tmp);
    func_8012B2CC((s32)a0);
    m = *(Blk32L *)(a0[8] + 0x34);
    func_8013339C((s16 *)&m, (s16 *)(a0[8] + 0x18));
    func_8012F1A4((s32 *)&m, (s32)tmp, out);
    D_80126B5C_w = out[0];
    D_80126B60 = out[1];
    D_80126B64 = out[2];
}


DEFINE_func_8013339C()  /* dedup: shared engine-core @0x8013339c (src/shared) */


DEFINE_func_8013361C()  /* dedup: shared engine-core @0x8013361c (src/shared) */



// @class: plumbing
// @stuck: none — MATCH

extern void func_80136BC4(s32 a0);

void func_801336E8(void *a0, int a1, int a2) {

    extern s32 D_801C8418;
    extern s32 D_801C841C[];
    extern int D_801C8420;
    if (a0 != 0) {
        (*(void * *)&D_801C8418) = a0;
        ((void (*)(void))func_80136BC4)();
    }
    (*(int *)&D_801C841C) = a1;
    D_801C8420 = a2;
}


extern char D_801C841C[];

void func_80136BC4(s32 a0);

void func_8013373C(s32 a0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801C8418;
    s32 value;

    a0 = (a0 << 16) >> 14;
    value = *(s32*)(&D_801C841C[a0]);
    if (value != 0) {
        D_801C8418 = value;
        func_80136BC4(value);
    }
}





s32 func_80133784(s32 arg0, void *arg1, s32 arg2) {

    extern s32 D_801C8418;
    extern s32 func_80047D3C(s32);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern Box_80133784 * D_8018419C;
    extern Box_80133784 * D_801841A0;
    extern s16 D_801C8424;
    extern u16 D_801C8428;

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
    D_8018419C->f6 = -0x7FFF;
    D_801841A0->f6 = 0x7FFF;
    D_8018419C->f0 = ((Box_80133784 *)arg1)->f0;
    D_8018419C->f4 = ((Box_80133784 *)arg1)->f4;
    D_801841A0->f0 = ((Box_80133784 *)arg2)->f0;
    D_801841A0->f4 = ((Box_80133784 *)arg2)->f4;
    D_801C8428 = 0;
    D_801C8424 = 0;

    if ((s16)a0v == 0) {
        s16 sx = ((Box_80133784 *)arg2)->f0 - ((Box_80133784 *)arg1)->f0;
        s16 sy = ((Box_80133784 *)arg2)->f2 - ((Box_80133784 *)arg1)->f2;
        s16 sz = ((Box_80133784 *)arg2)->f4 - ((Box_80133784 *)arg1)->f4;
        if (sx == 0 && sy == 0) {
            s32 zt = (sz == 0);
            __asm__("addu %0,%1,$zero" : "=r"(s2) : "r"(zt));
        }
        D_8018419C->f2 = ((Box_80133784 *)arg1)->f2 - 4;
        r = func_80047D3C(sx * sx + sz * sz);
        if (r < 3) {
            r = 4;
        } else if (r < 5) {
            r += 1;
        }
        D_801841A0->f2 = ((Box_80133784 *)arg2)->f2 + r + 1;
    } else {
        D_8018419C->f2 = ((Box_80133784 *)arg1)->f2;
        if ((s16)a0v == 2) {
            D_801841A0->f0 = D_8018419C->f0;
            D_801841A0->f2 = D_8018419C->f2 + 6;
            s2 = 1;
            D_801841A0->f4 = D_8018419C->f4;
        } else {
            D_801841A0->f2 = ((Box_80133784 *)arg2)->f2;
        }
    }

    while (1) {
        s32 ret0;
        register s32 retc __asm__("$3");
        __asm__ __volatile__("");
        ret0 = func_80133AB0(arg0s, (s16)D_8018419C->f0, (s16)D_8018419C->f4, (*(s32*)&D_801C8418));
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

    D_801841A0->f0 = D_8018419C->f0;
    D_801841A0->f2 = D_8018419C->f2;
    s1 = 0x2000;
    D_801841A0->f4 = D_8018419C->f4;
    goto store_out;

after:
    if ((s16)s4 != 0 || D_801C8424 != 0) {
        s16 t;
        __asm__ __volatile__("" :: "r"(s4));
        t = D_8018419C->f6;
        if (t >= -0xBCB) {
            if (t < -0x578) {
                s1 |= 0x4000;
            } else {
                s1 |= 0x8000;
            }
        }
        if ((s16)D_801841A0->f6 < -0xBCB) {
            s1 |= 0x2000;
        }
    store_out:
        ((Box_80133784 *)arg2)->f0 = D_801841A0->f0;
        ((Box_80133784 *)arg2)->f2 = D_801841A0->f2;
        ((Box_80133784 *)arg2)->f4 = D_801841A0->f4;
        ((Box_80133784 *)arg2)->f6 = D_801C8428;
        return s1 & 0xFFFF;
    }
    ((Box_80133784 *)arg2)->f6 = D_801C8428;
    return 0;
}




s32 func_80133AB0(s16 flag, s16 x, s16 y, s32 arg3)
{
    extern u8 D_801841A0;
    extern u8 D_8018419C;
    extern u8 D_801841A8;
    extern u16 D_801C8428;
    extern s16 D_801C8424;
    extern s32 func_80133CD4();

    Map_80133AB0 *map = (Map_80133AB0 *)arg3;
    u16 *pA = (*(u16 * *)&D_801841A0);
    u16 *pB = (*(u16 * *)&D_8018419C);
    u16 *pC = (*(u16 * *)&D_801841A8);
    register int zr __asm__("$0");
    u32 X, Y, cell, Xc, Yc;
    u16 k, off;
    int cnt;
    u16 *cp, *lst;
    u8 *s0;
    u16 raw;
    u32 hib;
    register int harg __asm__("$4");
    s32 ret;
    void *p0C, *p10;
    u8 *p14, *p18, *p1C;
    u16 *cells;

    pC[0] = pA[0] - pB[0];
    pC[1] = pA[1] - pB[1];
    pC[2] = pA[2] - pB[2];

    X = ((((u16)x + 0x8000) >> 7) & 0x1ff) - map->ox;
    __asm__("addu %0,%1,$zero" : "=r"(Xc) : "r"(X));
    if (!((X & 0xffff) < map->w))
        return 0;
    Y = ((((u16)y + 0x8000) >> 7) & 0x1ff) - map->oy;
    __asm__("addu %0,%1,$zero" : "=r"(Yc) : "r"(Y));
    if (!((Y & 0xffff) < map->h))
        return 0;

    cell = (Yc & 0xffff) * map->w + (Xc & 0xffff);
    cells = map->cells;
    p14 = map->p14;
    p0C = map->p0C;
    p10 = map->p10;
    p18 = map->p18;
    p1C = map->p1C;
    k = cell * 2;
    cp = (u16 *)(k * 2 + (u32)cells);
    off = cp[0];
    cnt = cp[1];
    lst = (u16 *)(p14 + off);

    while (((cnt-- + zr) & 0xffff) != 0) {
        raw = *lst;
        hib = raw & 0x8000;
        harg = hib + zr;
        if (hib == 0) {
            s0 = p18 + raw * 18;
        } else {
            s0 = p1C + (raw & 0x7fff) * 22;
        }
        ret = (s16)func_80133CD4((s16)(harg | flag), s0, p10, p0C);
        if (ret != 0) {
            if (ret > 0)
                D_801C8428 = *(u16 *)s0;
            return 1;
        }
        lst++;
        if (D_801C8424 != 0) {
            D_801C8428 = *(u16 *)s0;
            return 0;
        }
    }
    return 0;
}



s32 func_80133CD4(arg0, cmd, base, arr)
    s16 arg0;
    s16 *cmd;
    s16 *base;
    s32 *arr;
{

    extern u16 *D_801841A0;
    extern u16 *D_8018419C;
    extern s16 *D_801841A8;
    extern s16 *D_801841A4;
    extern s32 *D_801841B0;
    extern s32 *D_801841B4;
    extern u16 D_801C8428;
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

    if (func_80134310(s3, D_801841A0, s6) >= 0)
        return 0;

    s1var = func_80134310(s3, D_8018419C, s6);
    if (s1var < 0)
        return 0;

    s0var = func_80134310(s3, D_801841A8, 0);
    {
        u16 *pac = D_8018419C;
        s16 *pb8 = D_801841A8;
        s16 *pb4 = D_801841A4;
        s32 neg = -s1var;
        pb4[0] = pac[0] + neg * pb8[0] / s0var;
        pb4[1] = pac[1] + neg * pb8[1] / s0var;
        pb4[2] = pac[2] + neg * pb8[2] / s0var;
        if (func_8013435C(((ElemK *)base)[cmd[3]].e, pb4, arr[cmd[4]], s3))
            return 0;
    }
    if (func_8013435C(((ElemK *)base)[cmd[5]].e, D_801841A4, arr[cmd[6]], s3))
        return 0;
    if (func_8013435C(((ElemK *)base)[cmd[7]].e, D_801841A4, arr[cmd[8]], s3))
        return 0;
    if (arg0 < 0) {
        if (func_8013435C(((ElemK *)base)[cmd[9]].e, D_801841A4, arr[cmd[10]], s3))
            return 0;
    }
    if (arg0 & 0x10) {
        if (*(u16 *)cmd & 0x100)
            return 0;
    }
    if (*(u16 *)cmd & 0x200) {
        D_801C8428 = *(u16 *)cmd;
        return 0;
    }

    {
        s32 ret = func_80134310(s3, D_801841A0, s6);
        s32 *pc0;
        s32 *pc4;
        u16 *pb0;
        s32 t, o2;
        s32 q3v;

        {
            s32 *pw = D_801841B0;
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
            : : "r"(D_801841B0) : "$9", "$10", "$11", "memory");
        __asm__ __volatile__(
            "swc2 $25, 0(%0)\n"
            "swc2 $26, 4(%0)\n"
            "swc2 $27, 8(%0)\n"
            : : "r"(D_801841B4) : "memory");

        pc0 = D_801841B0;
        pc4 = D_801841B4;
        s0var = pc4[0] + pc4[1] + pc4[2];
        pb0 = D_801841A0;
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
            s32 *pl = D_801841B0;
            u16 *pb;
            s1var += pl[0];
            s0var += pl[1];
            s2a += pl[2];
            pb = D_801841A0;
            pb[0] = s1var >> 16;
            pb[1] = s0var >> 16;
            pb[2] = s2a >> 16;
            ret = func_80134310(s3, pb, s6);
        } while (ret < ((s3[1] < -0xE00) ? 0x1800 : 0x2F00));
    }

    y = s3[1];
    if (y >= -0xBCB) {
        D_8018419C[3] = y;
        {
            typedef struct { s8 c[8]; } Blk8_80133CD4;
            *(Blk8_80133CD4 *)&D_801152B0 = *(Blk8_80133CD4 *)s3;
        }
        if (*(u8 *)cmd != 0)
            goto ret1;
        return -1;
    }
    {
        u16 *s3u = (u16 *)s3;
        u16 *bp = D_801841A0;
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


DEFINE_func_80134310()  /* dedup: shared engine-core @0x80134310 (src/shared) */


DEFINE_func_8013435C()  /* dedup: shared engine-core @0x8013435c (src/shared) */



// @class: schedule
// @stuck: none — MATCH (83 ins, relocation-masked)



s32 func_801343C4(s32 angle, s32 p1, s32 p2)
{

    extern s32 D_801C8418;
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern s16 * D_8018419C;
    extern s16 * D_801841A0;
    extern u16 D_801C8428;
    extern u16 D_801C8424;

    s16 *pac;
    s16 *pb0;
    s16 *pacs, *pb0s;
    u16 *pb0u;
    int a1v, a2v, d94, b0;
    int sangle = ((s16)angle);

    pac = D_8018419C;
    d94 = D_801C8418;
    pb0 = D_801841A0;
    pac[0] = ((u16 *)p1)[0];
    pac[1] = ((u16 *)p1)[1];
    pac[2] = ((u16 *)p1)[2];
    pb0[0] = ((u16 *)p2)[0];
    pb0[1] = ((u16 *)p2)[1];
    pb0[2] = ((u16 *)p2)[2];

    a1v = pac[0]; a2v = pac[2];
    __asm__ __volatile__("" ::: "memory");
    D_801C8428 = 0;
    D_801C8424 = 0;
    if (func_80133AB0(sangle, a1v, a2v, d94)) {
    setdst:
        pb0u = (u16 *)D_801841A0;
        ((u16 *)p2)[0] = pb0u[0];
        ((u16 *)p2)[1] = pb0u[1];
        ((u16 *)p2)[2] = pb0u[2];
        ((u16 *)p2)[3] = D_801C8428;
        return 1;
    }

    pacs = D_8018419C;
    pb0s = D_801841A0;
    b0 = pb0s[0];
    if ((pacs[0] & 0xFF80) == (b0 & 0xFF80) &&
        (pacs[2] & 0xFF80) == (pb0s[2] & 0xFF80)) {
        return 0;
    }
    if (func_80133AB0(sangle, b0, pb0s[2], D_801C8418)) {
        goto setdst;
    }
    return 0;
}




// @class: schedule


s32 func_80134510(s32 param) {
    extern s32 func_801345F8(s32);
    extern Foo_80134510 * D_8018419C;
    extern Foo_80134510 * D_801841A0;
    extern Foo_80134510 * D_801841A4;
    extern s32 D_801C8418;
    extern u16 D_801C8428;

    s32 ret = 0;
    Foo_80134510 *b0 = D_801841A0;
    Foo_80134510 *ac = D_8018419C;
    u16 t0 = ((Foo_80134510 *)param)->f0;
    u16 t2, t4;

    ((Foo_80134510 *)param)->f6 = 0;
    ac->f0 = t0;
    b0->f0 = t0;
    t2 = ((Foo_80134510 *)param)->f2;
    ac->f2 = t2 - 4;
    b0->f2 = t2 + 0x2FC;
    t4 = ((Foo_80134510 *)param)->f4;
    ac->f4 = t4;
    b0->f4 = t4;

    if (func_801345F8(D_801C8418) != 0) {
        s16 x;
        ((Foo_80134510 *)param)->f2 = D_801841A4->f2 - 2;
        x = D_8018419C->f6;
        if (x >= -3019) {
            if (x < -1400) {
                ret = 0x4000;
            } else {
                ret = 0x8000;
            }
        } else {
            ret = 0x2000;
        }
        D_8018419C->f6 = D_801C8428;
    }
    return ret;
}



// @class: regalloc-order
// @stuck: 26-mismatch near-miss (structure fully matches: while-loop test-first via j-to-bottom-test, s0=puVar7/s1=cnt/s2=scan/s3=iVar8/s4=iVar9/s5=uVar3/s6=uVar10, a1=param/a0=cc/a3=0x8000 pinned, both range-persist copies present, mult+GPU-index+call all byte-correct). Residual = 4 instances of ONE gcc-2.7.2 regalloc/copy-prop tie-break: target computes a preserved-then-masked value in $v0 and reads $v0 for the mask (`subu $v0; addu $persist,$v0; andi $v0,$v0`), gcc here reads the persist reg (`andi $v0,$t0`). (1) range-check-1 andi reads $t0 not $v0; (2) range-check-2 andi reads $a0 not $v0; (3) `hi=uVar1&0x8000` folds into $a0 — target computes in $v0 + copies to $a0 in the branch-delay (same-block copy, gcc coalesces mine); (4) loop-test `cnt&0xffff` folds to direct `andi $v0,$s1` — target copies `addu $v0,$s1` first. Splitting the value into compare-temp + persist-var produces the copy but gcc forward-propagates the copy DEST into the mask; persist-after-compare kills the copy; explicit `register __asm__` pins fold the whole expr chain into the pinned reg; `=r/0` barriers force bad materialization. Also minor: while-loop header-copy adds a `beqz s1` entry guard vs target `j`, and a2/a3 call-arg setup order. Permuter can't run (register __asm__ pins rejected by pycparser). Genuinely compiler-internal — hand-finish or accept as ceiling.


s32 func_801345F8(s32 arg)
{
    extern int func_801347A0(short, u16 *, int, int);
    extern u16 * D_8018419C;
    extern u16 D_801C8428;

    register u16 *param_1 __asm__("$5") = ((u16 *)arg);
    register u16 *cc __asm__("$4") = D_8018419C;
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
        D_801C8428 = *puVar7;
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








s32 func_801347A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    extern u8 D_801152A8[];
    extern s32 func_80134A28(s32 a0, s32 a1, s32 a2);
    extern s16 * D_801841A0;
    extern SVec * D_8018419C;
    extern SVec * D_801841A4;

    Elem *pElem;
    s32 val;
    register s32 iv __asm__("$4");
    s32 q;
    s32 dvsr;

    pElem = &((Elem *)arg2)[((S0 *)arg1)->f2];
    val = ((s32 *)arg3)[((S0 *)arg1)->f4];
    if (func_80134A28((s32)pElem, (s32)D_801841A0, val) >= 0) {
        return 0;
    }
    iv = func_80134A28((s32)pElem, (s32)D_8018419C, val);
    if (iv < 0) {
        return 0;
    }
    iv = -iv;
    dvsr = pElem->f2 * 48;
    q = (iv * 48) / dvsr;
    D_801841A4->f0 = D_8018419C->f0;
    D_801841A4->f2 = D_8018419C->f2 + q;
    D_801841A4->f4 = D_8018419C->f4;
    if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->f6], (s32)D_801841A4, ((s32 *)arg3)[((S0 *)arg1)->f8]) < -0x2F00) {
        return 0;
    }
    if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->fa], (s32)D_801841A4, ((s32 *)arg3)[((S0 *)arg1)->fc]) < -0x2F00) {
        return 0;
    }
    if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->fe], (s32)D_801841A4, ((s32 *)arg3)[((S0 *)arg1)->f10]) < -0x2F00) {
        return 0;
    }
    if ((s16)arg0) {
        if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->f12], (s32)D_801841A4, ((s32 *)arg3)[((S0 *)arg1)->f14]) < -0x2F00) {
            return 0;
        }
    }
    if ((((S0 *)arg1)->f0 & 0x300) != 0) {
        return 0;
    }
    D_801841A4->f0 = D_8018419C->f0;
    D_801841A4->f4 = D_8018419C->f4;
    (*(Elem*)D_801152A8) = *pElem;
    D_8018419C->f6 = pElem->f2;
    return 1;
}


DEFINE_func_80134A28()  /* dedup: shared engine-core @0x80134a28 (src/shared) */



int func_80134A74(int param_1, s16 param_2, s16 param_3, int param_4)
{
    extern u16 D_801C8428;
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
        D_801C8428 = *puVar7;
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


            typedef struct { s8 c[8]; } Blk8_80134C20;

// @class: regalloc-order
// @try: variant B — direct pins m=$s5($21), c=$s6($22)


s32 func_80134C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    extern u8 D_801152A8[];
    extern s32 func_80134FB8(s32 a0, s32 a1, s32 a2);
    extern void * D_8018419C;
    extern void * D_801841A0;
    extern void * D_801841A4;
    extern void * D_801841A8;
    extern u16 D_801C8428;

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
    if (func_80134FB8(temp_s4, (s32) D_801841A0, temp_s1) >= 0) {
        return var_v0;
    }
    temp_v0 = func_80134FB8(temp_s4, (s32) D_8018419C, temp_s1);
    if (temp_v0 < 0) {
        goto block_13;
    }
    temp_v0_2 = func_80134FB8(temp_s4, (s32) D_801841A8, 0);
    temp_a3 = -temp_v0;
    {
        u16 *pB4 = (u16 *)D_801841A4;
        u16 *pAC = (u16 *)D_8018419C;
        s16 *pB8 = (s16 *)D_801841A8;
        pB4[0] = pAC[0] + (temp_a3 * pB8[0]) / temp_v0_2;
        pB4[1] = pAC[1] + (temp_a3 * pB8[1]) / temp_v0_2;
        pB4[2] = pAC[2] + (temp_a3 * pB8[2]) / temp_v0_2;
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 6) * 8), (s32) pB4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 8) * 4))) < -0x2F00) {
            return var_v0;
        }
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xA) * 8), (s32) D_801841A4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0xC) * 4))) < -0x2F00) {
        return var_v0;
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xE) * 8), (s32) D_801841A4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x10) * 4))) < -0x2F00) {
        return var_v0;
    }
    if ((arg0 << 16) < 0) {
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0x12) * 8), (s32) D_801841A4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x14) * 4))) < -0x2F00) {
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
    D_801C8428 = temp_a1;
block_13:
    return 0;
block_14:
    __builtin_memcpy(D_801152A8, (void *)temp_s4, 8);
    VectorNormalSS(D_801841A8, D_801841A8);
    {
        u16 *pB8 = (u16 *)D_801841A8;
        u16 *pB4b = (u16 *)D_801841A4;
        pB4b[0] = pB4b[0] - ((pB8[0] << 0x10) >> 0x1B);
        var_v0 = 1;
        pB4b[1] = pB4b[1] - ((pB8[1] << 0x10) >> 0x1B);
        pB4b[2] = pB4b[2] - ((pB8[2] << 0x10) >> 0x1B);
    }
    return var_v0;
}


DEFINE_func_80134FB8()  /* dedup: shared engine-core @0x80134fb8 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80135004);



// @class: schedule
// @stuck: none — MATCH (62 ins, relocation-masked)



extern int func_80134A74(int, s16, s16, int);

int func_80135168(u16 arg0, u16 *p1, u16 *p2)
{

    extern int D_801C8418;
    extern u16 D_801C8428;
    /* [T48] moved from FILE scope into the two consumers: a file-scope decl of these symbols
       forces every LATER function in this TU to agree with it, which blocks a byte-true
       pointer-typed decl in func_80135260. Declaration-only move; R22 is the arbiter. */
    extern u8 D_801841A0;
    extern u8 D_8018419C;
    extern s16 *D_801841A4;
    extern u8 D_801841A8;
    register s16 *pb0 __asm__("$8");
    register s16 *pac __asm__("$6");
    register s16 *pb8 __asm__("$7");
    u16 *pb4;
    u16 a, b;
    int a1v, a2v, d94;

    pb0 = (*(s16 * *)&D_801841A0);
    __asm__ __volatile__("" : : "r"(pb0));

    a = p2[0]; pac = (*(s16 * *)&D_8018419C); pb0[0] = a; b = p1[0]; pb8 = (*(s16 * *)&D_801841A8); pac[0] = b; pb8[0] = a - b;
    a = p2[1]; pb0[1] = a; b = p1[1]; pac[1] = b; pb8[1] = a - b;
    a = p2[2]; pb0[2] = a; b = p1[2]; pac[2] = b; pb8[2] = a - b;

    a1v = pac[0]; a2v = pac[2]; d94 = D_801C8418;
    __asm__ __volatile__("" ::: "memory");
    D_801C8428 = 0;
    if (func_80134A74(arg0, a1v, a2v, d94)) {
        pb4 = (*(u16 * *)&D_801841A4);
        p2[0] = pb4[0];
        p2[1] = pb4[1];
        p2[2] = pb4[2];
        p2[3] = D_801C8428;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80135260);



/* func_80135480 — cull + coordinate-transform emitter (258 ins, ov_SC01_077 split _a, ×134 family).
 *
 * NOT a §43 s16-param giant. Params are (void*, s32, s16*, s16*); the sole `sll/sra 16` is the s16
 * RETURN narrowing on $s3 (result), not an in-place arg-reg narrow. So §43's K&R-s16-param map does
 * not apply here — no //@EDIT, no ec_edit. func_80135480 has NO ambient prototype/caller anywhere in
 * src/include, so the s16 return type is free (no void->s32 flip, no engine_core.h edit).
 *
 * THE CRACK (residual class = §31 regalloc/schedule, RC-4/RC-2 in gcc-2.7.2-map/regalloc.md):
 * the two output buffers D_8018419C / D_801841A0 are written through a pointer in each of the two
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
 * Zero file-scope footprint (block-scoped typedefs + externs; D_8018419C/B0 read via the ambient
 * `extern u8` + `*(s16**)&` §30 anon-cast, matching neighbor func_80135168) -> ×134-clean for
 * family_sweep --edit-remap with no cc1 crash.
 *
 * VERIFIED: tools/rtu_match.py func_80135480 --split ov_SC01_077_a  ->  MATCH (258 ins), 3x stable.
 */
s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4)
{
    /* [T48] moved from FILE scope into the two consumers: a file-scope decl of these symbols
       forces every LATER function in this TU to agree with it, which blocks a byte-true
       pointer-typed decl in func_80135260. Declaration-only move; R22 is the arbiter. */
    extern u8 D_801841A0;
    extern u8 D_8018419C;
    extern s16 *D_801870B4;
    extern u8 D_801870B8;
        extern void func_80048EAC(void *m0, void *m1);
    extern void func_8004914C(void *m);
    extern void ApplyTransposeMatrixLV(void *m, void *in, void *out);
    extern void ApplyRotMatrixLV(void *in, void *out);
    extern void ApplyRotMatrix(void *in, void *out);
    extern s32 D_801C842C, D_801C8430, D_801C8434, D_801C8438;
    extern s16 D_801C843C;
    extern s32 D_801C844C;
    extern s16 D_801C8450, D_801C8452, D_801C8454, D_801C8456, D_801C8458, D_801C845A;

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
            m = &D_801C842C;
            *m = 0x1000000 / *(s16 *)((s32)param_1 + 0x18);
            q1 = 0x1000000 / *(s16 *)((s32)param_1 + 0x1A);
            q2 = 0x1000000 / *(s16 *)((s32)param_1 + 0x1C);
            D_801C8430 = 0;
            D_801C8438 = 0;
            D_801C8434 = q1;
            D_801C843C = q2;
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
            D_801C8450 = rotout.vx;
            D_801C8454 = rotout.vy;
            D_801C8458 = rotout.vz;
            vecin.vx = *(u16 *)(p + 6);
            vecin.vy = *(u16 *)(p + 0xA);
            vecin.vz = *(u16 *)(p + 0xE);
            ApplyRotMatrix(&vecin, &rotout);
            D_801C844C = 0;
            D_801C8452 = rotout.vx;
            D_801C8456 = rotout.vy;
            D_801C845A = rotout.vz;
            result += 2;
            break;
        case 0x40000000:
            ApplyTransposeMatrixLV((void *)((s32)param_1 + 0x34), &in0, &in0);
            ApplyRotMatrixLV(&in1, &in1);
            result = 2;
            break;
        }
        {
            s16 *p = *(s16 **)&D_8018419C;
            p[0] = in0.vx;
            p[1] = in0.vy;
            p[2] = in0.vz;
        }
        {
            s16 *p = *(s16 **)&D_801841A0;
            p[0] = in1.vx;
            p[1] = in1.vy;
            p[2] = in1.vz;
        }
        return result;
    }
    {
        s16 *p = *(s16 **)&D_8018419C;
        p[0] = in0.vx;
        p[1] = ((u16 *)param_3)[1] - *(s32 *)((s32)param_1 + 0x4C);
        p[2] = in0.vz;
    }
    {
        s16 *p = *(s16 **)&D_801841A0;
        p[0] = ((u16 *)param_4)[0] - *(s32 *)((s32)param_1 + 0x48);
        p[1] = ((u16 *)param_4)[1] - *(s32 *)((s32)param_1 + 0x4C);
        p[2] = ((u16 *)param_4)[2] - *(s32 *)((s32)param_1 + 0x50);
    }
    return 1;
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80135888);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80135A4C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80135D20);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80135EB0);



s32 func_80136334(void *arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern u8 D_8018419C;
    extern u8 D_801841A0;
    extern s16 *D_801841A4;
    extern u8 D_801841A8;
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
        dx = (s16) arg2 - (*(s16 **)&D_8018419C)[2];
        d = dx;
        denom = -(*(s16 **)&D_801841A8)[2];
    } else {
        denom = (*(s16 **)&D_801841A8)[2];
        d = (*(s16 **)&D_8018419C)[2] - (s16) arg2;
        dx = -d;
    }
    n = -d;
    {
        register s16 *b8 __asm__("$6") = *(s16 **)&D_801841A8;
        u16 *ac = *(u16 **)&D_8018419C;
        b4 = D_801841A4;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_801841A0;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_801841A4[2] = a2v + 2;
        __asm__ __volatile__("");
        D_801152AC = 0xFFF;
    } else {
        D_801152AC = -0xFFF;
        D_801841A4[2] = a2v - 2;
    }
    __asm__ __volatile__("" :: "r"(a1v), "r"(a2v));
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}



// @class: regalloc-order — F-band exemplar func_801365B8 (x134). Real-TU reconciled (rtu_match).
// D_8018419C/B0/B8 file-scope `extern u8` holding pointers -> read via *(T**)&sym (§42c-2).
// D_801841A4 file-scope `extern s16*` -> use directly. D_80126720 file-scope `extern u8[]`
// -> single store via *(s16*)D_80126720. D_801152A8/AA/AC, D_80126722/24 block-scope externs
// (siblings use block-scope; gcc-2.7.2 does not cross-conflict block-scope externs).
s32 func_801365B8(void *arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern u8 D_8018419C;
    extern u8 D_801841A0;
    extern s16 *D_801841A4;
    extern u8 D_801841A8;
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
        var_v1 = (s16) arg2 - (*(s16 **)&D_8018419C)[0];
        var_a1 = var_v1;
        var_a3 = -(*(s16 **)&D_801841A8)[0];
    } else {
        var_a3 = (*(s16 **)&D_801841A8)[0];
        var_v1 = (*(s16 **)&D_8018419C)[0] - (s16) arg2;
        var_a1 = -var_v1;
    }
    ac = *(u16 **)&D_8018419C;
    b4 = D_801841A4;
    b8 = *(s16 **)&D_801841A8;
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
        b4[1] = (s16) (*(u16 **)&D_801841A0)[1];
        b4[2] = (s16) (*(u16 **)&D_801841A0)[2];
    }
    D_801152AC = 0;
    D_801152AA = 0;
    if ((a1c & 1) != 0) {
        *(s16 *)D_801152A8 = 0xFFF;
        M2C_FIELD(D_801841A4, s16 *, 0) = a2c + 2;
    } else {
        *(s16 *)D_801152A8 = -0xFFF;
        M2C_FIELD(D_801841A4, s16 *, 0) = a2c - 2;
    }
    *(s16 *)D_80126720 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1);
    var_v0 = 1;
    D_80126724 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1);
    return var_v0;
}



// @class: pointer-type — pointer-vs-array reconcile for func_80136824 (ov_SC01_077_a)
// D_8018419C/B0/B8 are file-scope `extern u8`, D_801841A4 is `extern s32 []`; each HOLDS a
// pointer value that the target loads via lw then derefs. Read as pointer via *(T**)&sym.
// D_801841A4 must be a SCALAR pointer (not s32[]) — as an array it decays and gcc CSEs the
// base address into a held reg (lui;addiu;lw 0(reg)) across the 3 reloads; as a scalar
// pointer it folds %lo (lui;lw %lo). Retype all 3 file-TU occurrences (byte-neutral: the
// siblings read it once via *(u16**)&sym == direct lw either way).

s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {

    extern u8 D_80126720[];
    extern u8 D_8018419C;
    extern u8 D_801841A0;
    extern s16 *D_801841A4;
    extern u8 D_801841A8;
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
        var_t0 = (s16) arg2 - (*(s16 **)&D_8018419C)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_801841A8)[1];
    } else {
        var_a3 = (*(s16 **)&D_801841A8)[1];
        var_v1 = (*(s16 **)&D_8018419C)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    b8 = (*(s16 **)&D_801841A8);
    ac = (*(u16 **)&D_8018419C);
    b4 = D_801841A4;
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
        p = (*(u16 **)&D_801841A0);
        b4[0] = (s16) p[0];
        b4[2] = (s16) p[2];
    }
    D_801152AC = 0;
    (*(s16 *)D_801152A8) = 0;
    if (arg1 & 1) {
        b4b = D_801841A4;
        D_801152AA = 0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos + 2;
    } else {
        b4b = D_801841A4;
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
    extern s16 *D_801841A4;   /* holds a pointer value (*(u16**)&D_801841A4) */
    extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
    extern void ApplyRotMatrix(void *v0, void *v1);
    extern u16 D_80126722;
    extern s16 D_80126724;
    extern s16 D_801152AA;
    extern s16 D_801152AC;

    s32 out[4];
    u16 *pb4;

    if (a0) {
        ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)a3, *(void **)&D_801841A4, *(void **)&D_801841A4);
        ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)a3, (void *)D_80126720, (void *)D_80126720);
        ApplyRotMatrix((void *)D_801152A8, (void *)out);
        *(s16 *)D_801152A8 = out[0];
        D_801152AA = out[1];
        D_801152AC = out[2];
    }

    pb4 = *(u16 **)&D_801841A4;
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
    extern void (*D_801841B8[])(void);
    D_801841B8[D_800B99F0]();
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80136C90);

void func_80136D00(void) {
}

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136d08 (src/shared) */


DEFINE_func_80136DFC()  /* dedup: shared engine-core @0x80136dfc (src/shared) */


void func_80136EC4(void) {
}

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ecc (src/shared) */


DEFINE_func_80136F3C()  /* dedup: shared engine-core @0x80136f3c (src/shared) */


DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */


DEFINE_func_80137178()  /* dedup: shared engine-core @0x80137178 (src/shared) */


DEFINE_func_801372B0()  /* dedup: shared engine-core @0x801372b0 (src/shared) */


DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375ec (src/shared) */


extern void func_801375EC(s32 a0, s16 a1);

// @class: schedule (arg-copy placement) — PIN-FREE
// match_one: MATCH (26 ins).  rtu: MATCH (26 ins) with NO //@EDIT and NO header edit.
//
// ---- RECONCILE 2026-08-01 (uc2 -> uc3) ---------------------------------------------------
// GATE ERROR was:
//   jr_80135D20.c:1412 conflicting types for func_80137614 || :1362 previous declaration
// :1362 is `DEFINE_func_801375EC()`, whose expansion (src/shared/engine_core.h:2819) carries
//   extern void func_80137614(s32 a0, s32 a1, s32 a2);
// and it is instantiated two lines ABOVE this function's INCLUDE_ASM splice point (:1364).
// :1412 is this draft's own definition.  So the conflicting symbol is func_80137614 ITSELF
// and the axis is the §73 RETURN type: the shared header says `void`, the target ends
// `addu $v0, $s0, $zero` and callers in other overlays consume the result
// (ov_SC03_099_jr_80178D40.c already declares it `extern s32 func_80137614(s32,s32,s32)`),
// so the definition MUST stay s32.  Re-voiding the definition is the decay loop: gcc-2.7.2
// silently drops the $v0 set and you get 25/26 ins, class LENGTH-DRIFT/-1.
//
// ESCAPE USED: §37/§124 ASM-LABEL ALIAS (escape #2).  The definition is given a distinct C
// identifier `aF80137614` with __asm__("func_80137614"), so it never collides with the
// header's `extern void func_80137614` while still emitting the canonical symbol.  Zero
// header edits, zero TU edits, blast radius 0 — this replaces uc2's //@EDIT §65b de-macroize
// of DEFINE_func_801375EC, which would have had to be repeated at all 138 sweep sites.
// The TU already uses this exact idiom 60-odd lines below
// (`void *aF801376E8(int a0, int a1) __asm__("func_801376E8");`), so it travels to siblings.
// The in-TU call from func_801375EC still binds to the header's extern declaration and
// resolves to the same symbol at link time; func_801375EC's own 10 instructions are unchanged.
//
// ---- CODEGEN (unchanged from uc2 — do not touch) -----------------------------------------
// Residual before the lever: 4 mismatched, the (sw $sN / addu $sN,$aX) prologue PAIRS mirrored —
// target births $s2<-a2 then $s3<-a1; the naive draft births $s3<-a1 then $s2<-a2 (parm order),
// and drags `sw $s3` above `sw $s2` with it.  Register ASSIGNMENT was already right in both, so
// this is NOT a regalloc problem.  Measured INERT: body statement order, extra plain locals,
// K&R parm-declaration order (incl. declaring a2 before a1 in the K&R decl block).
//
// LEVER — cookbook §67 (arg-copy PLACEMENT).  One zero-instruction launder of the a1 parameter
// pins WHERE its entry copy materialises; a2's copy then takes the earlier slot and the register
// saves fall back into ascending order.  DIRECTION MATTERS and is the opposite of the intuition:
// laundering a2 (the copy that must move EARLIER) is inert — launder the copy that must land
// LATER.  §67 rule 1 respected: the laundered local is NOT pinned.  A pinned variant
// (register s32 __asm__("$18") / __asm__("$19") on a2/a1) also MATCHes, but pins are strictly
// worse for the ×138 family sweep (§42e/§86 pin guard), so the pin-free single launder is banked.
//
// Shape copied from the matched next-door sibling DEFINE_func_8013767C() (engine_core.h),
// which is this function minus the 0xD8 mask and the +0x1C halfword store.

extern s32 func_801399A8(void);
extern void func_801377B4(s32 a0, s32 a1, s32 a2);

s32 aF80137614(s32 a0, s32 a1, s32 a2) __asm__("func_80137614");

s32 aF80137614(s32 a0, s32 a1, s32 a2)
{
    s32 v1, s0;
    __asm__("" : "=r"(v1) : "0"(a1));
    s0 = func_801399A8();
    if (s0 != 0) {
        func_801377B4(a0, a2 & 0xD8, s0);
        *(s16 *)(s0 + 0x1C) = v1;
    }
    return s0;
}


DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767c (src/shared) */


DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376c8 (src/shared) */



/* @class: plumbing (globals-around-two-calls)
 * @stuck: none — MATCH (51 ins).
 *
 * RECONCILE (§37/§124 ASM-LABEL ALIAS) — no TU / header edit required.
 *   Gate error: ov_SC01_077_jr_80135D20.c:1415: conflicting types for `func_801376E8'
 *               || previous declaration at :1368
 *   :1368 is DEFINE_func_801376C8(), the shared engine-core macro that carries
 *   `extern void func_801376E8(int a0, int a1);` — a VOID return. The target's last
 *   pre-epilogue instruction is `addu $v0, $s1, $zero`, i.e. it RETURNS &D_801269F0,
 *   so the definition MUST be non-void; a `void` definition makes gcc-2.7.2 merely warn
 *   and DROP the returned value, killing that instruction (LENGTH-DRIFT/-1, 50 ins).
 *   The conflict is on func_801376E8 ITSELF and is a pure RETURN-type disagreement
 *   (params already agree: int,int), so the §37/§124 alias applies verbatim:
 *   define under the C name aF801376E8 with __asm__("func_801376E8") so the C-level
 *   declaration never collides, while the emitted symbol is still func_801376E8.
 *   Codegen is untouched — an asm label renames the symbol, nothing else.
 *   (The earlier draft's `//@EDIT` widening of the shared extern to `void *` is a
 *   T2 fleet-shared edit; the alias is T0 draft-only. Cookbook §124: fix the reader,
 *   not the source.)
 *
 * Byte levers (unchanged from the passing draft):
 *  - `obj` local holding (s32)&D_801269F0: the address is CSEd ONCE into $s1 and reused
 *    for both jal args and the return (same idiom as the neighbouring func_80137B80).
 *  - D_80126A24 is s16 (`lh`) but D_80126A26 is u16 (`lhu`) with an explicit (s16) cast
 *    at the use site: gcc combines the cast's `sll 16; sra 16` with the `>>1` into
 *    `sll 16; sra 17`, which is exactly what the target emits. A plain s16 D_80126A26
 *    would give `lh; sra 1` instead.
 *  - D_80126A14 as u16[2] (`lhu` loads, `%lo(D_80126A14 + 0x2)` for element 1).
 */


extern void func_801377B4(s32 a0, s32 a1, s32 a2);
extern void func_80139BE0(s32 a0);

void *aF801376E8(int a0, int a1) __asm__("func_801376E8");

void *aF801376E8(int a0, int a1)
{

    extern s32 D_801269F0;
    extern u8 D_801269FD;
    extern u16 D_80126A14[];
    extern s16 D_80126A1C;
    extern s16 D_80126A20;
    extern s16 D_80126A22;
    extern s16 D_80126A24;
    extern u16 D_80126A26;
    u16 *p = (u16 *)a1;
    s32 obj = (s32)&D_801269F0;

    func_801377B4(a0, 0x6200, obj);
    D_80126A1C = 0x1C;
    D_801269FD = 0;
    if (p != 0) {
        D_80126A14[0] = p[0];
        D_80126A14[1] = p[1];
    }
    func_80139BE0(obj);
    D_80126A20 = (D_80126A14[0] + 0x28) - ((D_80126A24 + 0x28) >> 1);
    D_80126A22 = D_80126A14[1] - ((s16)D_80126A26 >> 1);
    return (void *)obj;
}


DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377b4 (src/shared) */


DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */



extern void func_80016714(void *a0, s32 a1);
extern void func_8013A860(void);

void func_801378F0(void) {

    extern u8 D_80127520[];
    extern u8 aD801269F0[] __asm__("D_801269F0"); /* §37 alias: TU canon is `extern int D_801269F0` */
    extern u8 D_80126A28[];
    extern u8 D_801841C0[];
    s32 i;
    s32 si;
    s32 di;
    u8 *p;

    func_80016714(D_80127520, 0xBFC);
    i = 0;
    si = 0;
    p = aD801269F0;
    di = 0;
    do {
        func_80016714(p, 0x4C);
        *(u16 *)&D_80126A28[di]     = *(u16 *)&D_801841C0[si];
        *(u16 *)&D_80126A28[di + 2] = *(u16 *)&D_801841C0[si + 2];
        *(u16 *)&D_80126A28[di + 4] = *(u16 *)&D_801841C0[si + 4];
        *(u16 *)&D_80126A28[di + 6] = *(u16 *)&D_801841C0[si + 6];
        p += 0x4C;
        i += 1;
        si += 8;
        di += 0x4C;
    } while (i < 3);
    func_8013A860();
}


DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379d8 (src/shared) */


DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379ec (src/shared) */


DEFINE_func_801379FC()  /* dedup: shared engine-core @0x801379fc (src/shared) */




// @class: remat
// @stuck: target CSEs &D_801269F0 once for load+call arg; force via local pointer
extern void func_80138BE0(int p);

void func_80137B80(void) {

    extern s32 D_80127548[];
    extern int D_8018420C;
    extern int D_801269F0;
    int *p = &D_801269F0;
    (*(int *)&D_80127548) = 0x24;
    if (*p != 0) {
        ((void (*)(int *))func_80138BE0)(p);
    }
    D_8018420C += 1;
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
    extern int D_8018420C;
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
        if (D_8018420C & 4) {
            ((void (*)(void *, int))func_80139680)(&D_801269F0, arg1);
        }
    }
    return D_800A5E60;
}


DEFINE_func_80137DD4()  /* dedup: shared engine-core @0x80137dd4 (src/shared) */


DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137fd8 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801380E0);

DEFINE_func_801387B8()  /* dedup: shared engine-core @0x801387b8 (src/shared) */


DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */


DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895c (src/shared) */


DEFINE_func_80138AB4()  /* dedup: shared engine-core @0x80138ab4 (src/shared) */


DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138b88 (src/shared) */



// @class: struct
// @stuck: none — MATCH (match_one: MATCH 20 ins)


void func_80138BE0(int p)
{

    extern void (*D_80184210[])(void);
    if (*(unsigned short *)(p + 0xe) != 0) {
        *(unsigned short *)(p + 0xe) -= 1;
    }
    D_80184210[*(short *)(p + 4)]();
}


void func_80138C30(void *a0) {
    if (*(s16 *)((s32)a0 + 4) == 4) {
        *(s16 *)((s32)a0 + 4) = 2;
    } else {
        *(u32 *)((s32)a0 + 8) |= 0x800;
    }
}


extern void func_80139C7C(u8 *a0);
extern s32 func_8013A8FC(s32 arg0);
extern void func_80139BE0(s32 a0);

s32 func_80138C60(s32 arg0)
{
    extern Q_80138C60 D_801841DC[];
    u16 t;
    u8 b;
    s32 f;
    s32 idx;

    if (*(s32 *)(arg0 + 8) & 0x2000) {
        return 1;
    }

    t = *(u8 *)(arg0 + 0x22) & 7;
    *(s16 *)(arg0 + 0x18) = t;
    if (t < 2) {
        *(u8 *)(arg0 + 0x20) = 0;
    }

    f = *(s32 *)(arg0 + 8);
    if (f & 0x40) {
        *(u8 *)(arg0 + 0x22) = (*(u8 *)(arg0 + 0x22) & 0x67) | (f & ~0x67);
    }

    b = *(u8 *)(arg0 + 0x22);
    if (b & 0x80) {
        idx = (b & 0x18) >> 3;
    } else {
        idx = (b & 0x78) >> 3;
        if (b & 0x60) {
            *(s16 *)(arg0 + 0x1C) = 0;
        }
    }

    *(Q_80138C60 *)(arg0 + 0x24) = D_801841DC[idx];

    func_80139BE0(arg0);
    func_80139C7C((u8 *)arg0);
    return func_8013A8FC(arg0);
}


DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138d58 (src/shared) */


DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138db8 (src/shared) */




extern s32 func_80138ED0(u8 *param_1, u32 param_2, u8 *param_3);

s32 func_80138DE0(u8 *arg0, u8 arg1, s32 arg2) {

    extern s32 D_80127548[];
    extern u8 D_800D3AB4[];
    u16 *p;

    if (D_80127548[0] == 0) {
        return 0;
    }
    p = (u16 *)(arg0 + 0x44);
    if ((*(u32 *)(arg0 + 8) & 0x400) == 0) {
        p = (u16 *)(arg0 + 0x10);
        if (*(s16 *)(arg0 + 4) == 8) {
            p = (u16 *)(arg0 + 0x44);
        }
    }
    if (arg1 >= 0xE0) {
        arg2 = func_80138ED0(arg0, 0x1F, D_800D3AB4);
        if (arg2 != 0) {
            return 0;
        }
        *p = *p + 2;
    } else if (arg1 >= 0x20) {
        arg2 = func_80138ED0(arg0, (u16)(arg1 - 0x20), D_800D3AB4);
        if (arg2 != 0) {
            return 0;
        }
        *p = *p + 1;
    }
    if (arg2 != 0) {
        return 0;
    }
    D_80127548[0] = D_80127548[0] - 1;
    return D_80127548[0];
}


DEFINE_func_80138ED0()  /* dedup: shared engine-core @0x80138ed0 (src/shared) */


DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914c (src/shared) */


DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391f0 (src/shared) */


DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */


DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392c8 (src/shared) */


DEFINE_func_801392FC()  /* dedup: shared engine-core @0x801392fc (src/shared) */


DEFINE_func_801395D4()  /* dedup: shared engine-core @0x801395d4 (src/shared) */


DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */


DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */


DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */



extern void GsSortSprite(void *a0, u8 *a1, s32 a2);

void func_801397B0(s32 arg0)
{

    extern short D_800B9A02;
    extern u8 D_800A6518[];
    extern u8 D_80184254;
    extern u8 D_80184298;
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
    b164 = (u8 *)&D_80184254;
    off = ((s32)*(u8 *)(e + 0x20) - 1) << 2;
    b164 = off + b164;

    *(s32 *)((u8 *)buf + 0x00) = 0;

    t2 = *(s16 *)(b164 + 2);
    t0 = *(s16 *)(b164 + 0);
    hi = (t2 & 0x100) >> 4;
    lo = ((t0 & 0x3C0) >> 6) | 0x20;
    *(s16 *)((u8 *)buf + 0x0C) = hi | lo | ((t2 & 0x200) << 2);

    b1A8 = (u8 *)&D_80184298 + off;
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80139BE0);

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


extern void *memcpy(void *, const void *, u32);
extern void func_80015D4C();
extern void func_80015F04();
extern void func_8013AA24(s32 a0, s32 a1);
void func_8013A530(int param_1)
{
    int iVar11;
    u16 uVar2;
    int sVar2;
    register u8 bVar1 __asm__("$8");
    int deadlocal[2];
    iVar11 = *(int *)(param_1 + 4);
    uVar2 = *(u16 *)(iVar11 + 0x18);
    sVar2 = uVar2;
    bVar1 = *(u8 *)(iVar11 + 0x22);
    if (uVar2 != 0 && uVar2 < 7) {
        if (uVar2 != 1) {
            if (sVar2 != 0 && sVar2 < 7) {
                register u32 f34 __asm__("$5");
                u32 uVar2b;
                u32 uVar6;
                short sVar5;
                register int fc __asm__("$5");
                register int zr __asm__("$0");
                int iVar7;
                f34 = *(u16 *)(iVar11 + 0x34);
                uVar6 = f34 + 0x10;
                uVar2b = *(u16 *)(iVar11 + 0x36) + 0x10;
                if (*(u8 *)(iVar11 + 0x20) != 0) {
                    uVar6 = f34 + 0x38;
                }
                sVar5 = (short)((int)((int)*(s16 *)(iVar11 + 0x28) * (uVar6 & 0xffff)) / 0x9a);
                *(s16 *)(param_1 + 8) = sVar5;
                if ((bVar1 & 8) == 0) {
                    *(s16 *)(param_1 + 8) = -sVar5;
                }
                if ((bVar1 & 0x60) == 0 || (bVar1 & 0x80) != 0) {
                    *(s16 *)(param_1 + 8) = -*(s16 *)(param_1 + 8);
                }
                sVar5 = (short)((int)((int)*(s16 *)(iVar11 + 0x2a) * (uVar2b & 0xffff)) / 0x2a);
                *(s16 *)(param_1 + 0xa) = sVar5;
                if ((bVar1 & 0x10) != 0) {
                    *(s16 *)(param_1 + 0xa) = -sVar5;
                }
                __asm__("" :: "r"(bVar1));
                fc = *(s16 *)(param_1 + 0xc);
                iVar7 = fc + zr;
                if (fc < *(s16 *)(param_1 + 0xe)) {
                    int t = iVar7 + 0x400;
                    *(s16 *)(param_1 + 0xc) = (short)t;
                    if (((t << 16) >> 16) > (int)*(s16 *)(param_1 + 0xe)) {
                        *(s16 *)(param_1 + 0xc) = *(s16 *)(param_1 + 0xe);
                    }
                } else if (*(s16 *)(param_1 + 0xe) < fc) {
                    int t = iVar7 - 0x400;
                    __asm__("" :: "r"(iVar7), "r"(t));
                    *(s16 *)(param_1 + 0xc) = (short)t;
                    if (((t << 16) >> 16) < (int)*(s16 *)(param_1 + 0xe)) {
                        *(s16 *)(param_1 + 0xc) = *(s16 *)(param_1 + 0xe);
                    }
                }
                __asm__("" :: "r"(fc));
                func_8013AA24(iVar11, param_1);
            }
        } else {
            int iVar7, iVar8;
            u32 uVar6, uVar4;
            memcpy((void *)(param_1 + 8), (void *)(iVar11 + 0x28), 4);
            uVar6 = ((*(s16 *)(iVar11 + 0x34) + 0x10) * (int)*(s16 *)(param_1 + 8)) >> 0xc;
            uVar4 = ((*(s16 *)(iVar11 + 0x36) + 0x10) * (int)*(s16 *)(param_1 + 0xa)) >> 0xc;
            iVar7 = *(u16 *)(iVar11 + 0x24) - ((uVar6 & 0xffff) >> 1);
            iVar8 = *(u16 *)(iVar11 + 0x26) - ((uVar4 & 0xffff) >> 1);
            func_80015F04((int)(s16)iVar7, (int)(s16)iVar8, (int)(s16)uVar6, (int)(s16)uVar4,
                          0xb3, 0x99, 0x4c, *(u16 *)(iVar11 + 0x1a), 4);
            func_80015F04((int)(s16)(iVar7 + 1), (int)(s16)(iVar8 + 1),
                          (int)(s16)(uVar6 - 2), (int)(s16)(uVar4 - 2),
                          0xe6, 0xcc, 0x73, *(u16 *)(iVar11 + 0x1a), 4);
            func_80015D4C((int)(s16)iVar7, (int)(s16)iVar8, (int)(s16)uVar6, (int)(s16)uVar4,
                          0xff, 0xe6, 0x99, *(u16 *)(iVar11 + 0x1a), 4);
        }
    }
    return;
}


DEFINE_func_8013A860()  /* dedup: shared engine-core @0x8013a860 (src/shared) */


DEFINE_func_8013A8B0()  /* dedup: shared engine-core @0x8013a8b0 (src/shared) */


DEFINE_func_8013A8BC()  /* dedup: shared engine-core @0x8013a8bc (src/shared) */


DEFINE_func_8013A8FC()  /* dedup: shared engine-core @0x8013a8fc (src/shared) */


DEFINE_func_8013A9B4()  /* dedup: shared engine-core @0x8013a9b4 (src/shared) */


DEFINE_func_8013A9F8()  /* dedup: shared engine-core @0x8013a9f8 (src/shared) */


DEFINE_func_8013AA24()  /* dedup: shared engine-core @0x8013aa24 (src/shared) */


DEFINE_func_8013AB54()  /* dedup: shared engine-core @0x8013ab54 (src/shared) */


#define gte_ldv0(r0)  __asm__ __volatile__( \
    "lwc2 $0, 0(%0)\n" \
    "lwc2 $1, 4(%0)\n" \
    : : "r"(r0) : "memory")
#define gte_mvmva0()  __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 0, 0\n" \
    : : : "memory")
#define gte_stlvnl(r0)  __asm__ __volatile__( \
    "swc2 $25, 0(%0)\n" \
    "swc2 $26, 4(%0)\n" \
    "swc2 $27, 8(%0)\n" \
    : : "r"(r0) : "memory")

void func_8013AD38(void *flag, s32 a1, void *out2, void *out3)
{

    extern s16 D_800D45F4[];
    extern u8 D_801842DC[];
    extern s16 D_800D466C[];
    extern u8 D_80184318[];

    u8 *tbl;
    s16 vec[4];
    s32 res[3];
    s32 i;

    tbl = D_80184318;
    if (((s16)a1) < 0xC00) {
        tbl = D_801842DC;
    }

    for (i = 0; i < 30; i++) {
        vec[0] = D_800D45F4[2 * i]     + (((D_800D466C[2 * i]     - D_800D45F4[2 * i])     * ((s16)a1)) >> 12);
        vec[1] = D_800D45F4[2 * i + 1] + (((D_800D466C[2 * i + 1] - D_800D45F4[2 * i + 1]) * ((s16)a1)) >> 12);
        gte_ldv0(vec);
        gte_mvmva0();
        gte_stlvnl(res);
        ((Pair *)out2)[i].x = res[0];
        ((Pair *)out2)[i].y = res[1];
        if (((s16 *)flag)[0] < 0) ((s8 *)out3)[2 * i]     = -tbl[2 * i];     else ((s8 *)out3)[2 * i]     = tbl[2 * i];
        if (((s16 *)flag)[1] < 0) ((s8 *)out3)[2 * i + 1] = -tbl[2 * i + 1]; else ((s8 *)out3)[2 * i + 1] = tbl[2 * i + 1];
    }
    ((Pair *)out2)[i] = ((Pair *)out2)[0];
    if (((s16 *)flag)[0] < 0) ((s8 *)out3)[2 * i]     = -tbl[0]; else ((s8 *)out3)[2 * i]     = tbl[0];
    if (((s16 *)flag)[1] < 0) ((s8 *)out3)[2 * i + 1] = -tbl[1]; else ((s8 *)out3)[2 * i + 1] = tbl[1];
}


DEFINE_func_8013AF20()  /* dedup: shared engine-core @0x8013af20 (src/shared) */


DEFINE_func_8013B204()  /* dedup: shared engine-core @0x8013b204 (src/shared) */




extern void *func_80010A08(s32);

void func_8013B274(s32 a0, s32 a1, void *a2)
{

    extern s16 D_80184354, D_80184356, D_80184358, D_8018435A, D_8018435C, D_8018435E;
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
        if (!(D_80184356 < ang)) goto outer_else;
        if (!(ang < D_8018435C)) goto inner_else;
        if (ang < D_80184358) { *(s16 *)L = D_80184358; goto done; }
        if (D_8018435A < ang) { *(s16 *)L = D_8018435A; goto done; }
        *(s16 *)L = quot;
        goto done;
    outer_else:
        if (ang < D_80184354) { *(s16 *)L = D_80184354; goto done; }
        *(s16 *)L = quot;
        goto done;
    inner_else:
        if (D_8018435E < ang) { *(s16 *)L = D_8018435E; goto done; }
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013B568);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013B598);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013B6A0);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013B7AC);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013B7F4);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013B83C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013BC7C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013BCDC);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013BD34);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013BD74);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013C08C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013C0F8);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013C360);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013C414);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013C938);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013C964);


extern void func_80016714(void *a0, s32 a1);

void func_8013C98C(void) {

    extern s32 D_801C8490;
    extern s32 D_801269D4;
    extern s32 D_801269C8;
    func_80016714(&D_801C8490, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013C9C4);


void func_8013CA14(void)
{

    extern s32 D_801C8490;
    extern s8 D_801C8494;
    extern s8 D_801C8495;
    extern s32 D_801269C8;
    extern s32 D_801269D4;
  int *base = &D_801C8490;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_801C8495;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_801C8494)) * 2) + D_801C8490);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_801C8495 = (unsigned char) p[1];
      D_801C8494 = D_801C8494 + 1;
      if (D_801C8495 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_801C8494 = 0;
        *base = 0;
      }
    }
    else
    {
      D_801C8495 = c - 1;
    }
  }
  return;
}




void func_8013CABC(void) {

    extern s32 D_801C84B4;
    extern s32 D_801C84A8;
    extern s32 D_801C84AC;
    extern s32 D_801C84B8;
    D_801C84B4 = 1;
    D_801C84A8 = 1;
    D_801C84AC = 0;
    D_801C84B8 = 1;
}




void func_8013CAE8(void) {

    extern s32 D_801C84A8;
    extern s32 D_801C84AC;
    extern s32 D_801C84B0;
    extern s32 D_801C84B4;
    extern s32 D_801C84B8;
    D_801C84A8 = 1;
    D_801C84B4 = 0;
    D_801C84AC = 0;
    D_801C84B0 = -1;
    D_801C84B8 = 0;
}




void func_8013CB20(void)
{

    extern s32 D_801C84B4;
    extern s32 D_801C84B8;
    extern s32 D_801C84E0;
    extern s32 D_801C84E4;
    D_801C84E0 = D_801C84B8;
    D_801C84E4 = D_801C84B4;
    D_801C84B8 = 1;
    D_801C84B4 = 0;
}




void func_8013CB5C(void) {

    extern s32 D_801C84E0;
    extern s32 D_801C84E4;
    extern s32 D_801C84B8;
    extern s32 D_801C84B4;
    D_801C84B8 = D_801C84E0;
    D_801C84B4 = D_801C84E4;
}




extern s16 currentLocationId;

extern void func_8013DBE4();
extern void func_8013D9B0();
extern void func_8013D330(void);
extern void func_8013D178(void);
extern void func_8013CF68(void);

void func_8013CB84(void) {

    extern u8 D_80078EAF;
    extern s32 D_801C84B8;
    extern s32 D_801C84B0;
    extern s32 D_801C84B4;
    extern s32 D_801C84A8;
    extern s32 D_801C84AC;
    extern s32 D_801C84BC;
    extern s32 D_801C84C8;
    extern s32 D_801C84D0;
    extern s32 D_801C9A58;
    extern s32 D_801C99D8;
    extern s32 D_801C99CC[];
    extern u8 D_801C9999;
    extern u8 D_801C9AE6;
    extern u8 D_801C9A54;
    extern Rec12 D_80184574[];
    extern Rec9 D_8018453C[];
    extern u8 D_801C9A30;  /* canonical (§8d); Rec9 block-move via cast-at-use */
    s32 loc = currentLocationId;
    s32 s0 = D_80078EAF;
    s32 ta, tb, tc, t;

    D_801C9A58 = 0;
    if (D_801C84B8 == 0 && s0 != D_801C84B0) {
        ta = D_80184574[s0].a;
        tb = D_80184574[s0].b;
        tc = D_80184574[s0].c;
        D_801C84B0 = s0;
        D_801C9999 = tc;
        D_801C9AE6 = ta;
        D_801C9A54 = tb;
        *(Rec9 *)&D_801C9A30 = D_8018453C[s0];
        D_801C84B4 = 1;
        D_801C84A8 = 1;
        if (D_801C84C8 & 2) {
            if (s0 == 4) { D_801C99CC[0] = 0x100; D_801C99D8 = 0x80; }
            if (s0 == 0) { D_801C99CC[0] = 0x100; D_801C99D8 = 0; }
        }
    }
    if (D_801C84B4 != 0) {
        t = D_801C84A8 - 1;
        D_801C84A8 = t;
        if (t == 0) {
            if (D_801C84B8 == 0) {
                if ((D_801C84C8 & 2) && s0 == 4) {
                    if (D_801C84D0 != 0) func_8013DBE4(6);
                    else func_8013D9B0(6);
                } else {
                    if (D_801C84D0 != 0) func_8013DBE4(s0);
                    else func_8013D9B0(s0);
                }
                func_8013D330();
                func_8013D178();
                func_8013CF68();
                D_801C84A8 = 2;
                if (D_801C84B4 != 0) {
                    if (D_801C84C8 & 2) {
                        if (s0 == 4) {
                            s32 *p = &D_801C99D8;
                            t = *p - 8;
                            *p = t;
                            if (t < 0) *p = 0;
                        } else if (s0 == 0) {
                            s32 *p = &D_801C99D8;
                            t = *p + 0x20;
                            *p = t;
                            if (t >= 0x81) *p = 0x80;
                        }
                    }
                } else if (D_801C84C8 & 2) {
                    if (s0 == 4) D_801C99D8 = 0;
                    if (s0 == 0) D_801C99D8 = 0x80;
                }
            } else {
                if (D_801C84D0 != 0) func_8013DBE4(5);
                else func_8013D9B0(5);
                D_801C84A8 = 1;
            }
        }
    }
    D_801C84BC = 0;
    if (loc == 0x1010) {
        if (s0 == 3) {
            if (D_801C84B4 != 0) D_801C84BC = D_801C84AC;
            else D_801C84BC = 0x1F;
        } else if (s0 == 4) {
            if (D_801C84B4 != 0) D_801C84BC = 0x1F - D_801C84AC;
            else D_801C84BC = 0;
        }
    }
}




void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_801C9990;
    extern u8 D_801C9991;
    extern u8 D_801C9992;
    extern u8 D_801C9993;
    extern u8 D_801C9994;
    extern u8 D_801C9995;
    extern u8 D_801C9996;
    extern u8 D_801C9997;
    extern u8 D_801C9998;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801C9990; t1 = D_801C9991; t2 = D_801C9992;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801C9993; t1 = D_801C9994; t2 = D_801C9995;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801C9996; t1 = D_801C9997; t2 = D_801C9998;
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

    extern s32 D_801C84C0;
    extern s32 D_801C84A8;
    extern s32 D_801C84C4;
    extern s32 D_801C84B4;
    if (D_801C84C0 != 0) {
        if (D_801C84C0 != 2) {
            if (((D_801C84C0 < 3) && (D_801C84C0 == 1)) &&
                (D_801C84C4 = D_801C84C4 + 1, 0x23a < D_801C84C4)) {
                D_801C84A8 = D_801C84C0;
                D_801C84C0 = 2;
            }
        } else {
            D_801C84A8 = D_801C84A8 + -1;
            if (D_801C84A8 == 0) {
                D_801C84A8 = D_801C84C0;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_801C84B4 == 0) {
                    D_801C84C0 = D_801C84C0 + 1;
                }
            }
        }
    }
    return;
}



extern void func_8013D9B0();

s32 func_8013D13C(void) {

    extern s32 D_801C84B4;
    func_8013D9B0();
    return D_801C84B4;
}




void func_8013D164(void) {

    extern s32 D_801C84C0;
    D_801C84C0 = 1;
}



void func_8013D178(void) {

    extern unsigned char D_801C9990, D_801C9991, D_801C9992, D_801C9993, D_801C9994, D_801C9995, D_801C9996, D_801C9997, D_801C9998;
    extern unsigned char D_801C9990, D_801C9991, D_801C9992, D_801C9993, D_801C9994, D_801C9995, D_801C9996, D_801C9997, D_801C9998;
    extern unsigned char D_801C9990, D_801C9991, D_801C9992, D_801C9993, D_801C9994, D_801C9995, D_801C9996, D_801C9997, D_801C9998;
    extern unsigned char D_801C9990, D_801C9991, D_801C9992, D_801C9993, D_801C9994, D_801C9995, D_801C9996, D_801C9997, D_801C9998;
    extern unsigned char D_801C9990, D_801C9991, D_801C9992, D_801C9993, D_801C9994, D_801C9995, D_801C9996, D_801C9997, D_801C9998;
    extern unsigned char D_801C9990, D_801C9991, D_801C9992, D_801C9993, D_801C9994, D_801C9995, D_801C9996, D_801C9997, D_801C9998;
    extern unsigned char D_801C9990, D_801C9991, D_801C9992, D_801C9993, D_801C9994, D_801C9995, D_801C9996, D_801C9997, D_801C9998;
    extern unsigned char D_801C9990, D_801C9991, D_801C9992, D_801C9993, D_801C9994, D_801C9995, D_801C9996, D_801C9997, D_801C9998;
    extern unsigned char D_801C9990, D_801C9991, D_801C9992, D_801C9993, D_801C9994, D_801C9995, D_801C9996, D_801C9997, D_801C9998;
    extern u8 D_801C9A30;
    extern unsigned char D_801C9A30, D_801C9A31, D_801C9A32, D_801C9A33, D_801C9A34, D_801C9A35, D_801C9A36, D_801C9A37, D_801C9A38;
    extern unsigned char D_801C9A30, D_801C9A31, D_801C9A32, D_801C9A33, D_801C9A34, D_801C9A35, D_801C9A36, D_801C9A37, D_801C9A38;
    extern unsigned char D_801C9A30, D_801C9A31, D_801C9A32, D_801C9A33, D_801C9A34, D_801C9A35, D_801C9A36, D_801C9A37, D_801C9A38;
    extern unsigned char D_801C9A30, D_801C9A31, D_801C9A32, D_801C9A33, D_801C9A34, D_801C9A35, D_801C9A36, D_801C9A37, D_801C9A38;
    extern unsigned char D_801C9A30, D_801C9A31, D_801C9A32, D_801C9A33, D_801C9A34, D_801C9A35, D_801C9A36, D_801C9A37, D_801C9A38;
    extern unsigned char D_801C9A30, D_801C9A31, D_801C9A32, D_801C9A33, D_801C9A34, D_801C9A35, D_801C9A36, D_801C9A37, D_801C9A38;
    extern unsigned char D_801C9A30, D_801C9A31, D_801C9A32, D_801C9A33, D_801C9A34, D_801C9A35, D_801C9A36, D_801C9A37, D_801C9A38;
    extern unsigned char D_801C9A30, D_801C9A31, D_801C9A32, D_801C9A33, D_801C9A34, D_801C9A35, D_801C9A36, D_801C9A37, D_801C9A38;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_801C9990; v = *p; t = D_801C9A30;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C9991; v = *p; t = D_801C9A31;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C9992; v = *p; t = D_801C9A32;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C9993; v = *p; t = D_801C9A33;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C9994; v = *p; t = D_801C9A34;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C9995; v = *p; t = D_801C9A35;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C9996; v = *p; t = D_801C9A36;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C9997; v = *p; t = D_801C9A37;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801C9998; v = *p; t = D_801C9A38;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}




// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)


void func_8013D330(void) {

    extern u8 D_801C9A72;
    extern u8 D_801C9AE6;
    extern u8 D_801C999A;
    extern u8 D_801C9A54;
    extern u8 D_801C9978;
    extern u8 D_801C9999;
    extern s32 D_801C9A58;
    if ((D_801C9A72 & 0xff) != D_801C9AE6) {
        D_801C9A72 = ((D_801C9A72 & 0xff) < D_801C9AE6) ? (D_801C9A72 + 1) : (D_801C9A72 - 1);
    }
    if ((D_801C999A & 0xff) != D_801C9A54) {
        D_801C999A = ((D_801C999A & 0xff) < D_801C9A54) ? (D_801C999A + 1) : (D_801C999A - 1);
    }
    if ((D_801C9978 & 0xff) != D_801C9999) {
        D_801C9978 = ((D_801C9978 & 0xff) < D_801C9999) ? (D_801C9978 + 1) : (D_801C9978 - 1);
    }
    D_801C9A58 = 1;
}



// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)




extern void func_8013D53C(void *);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{

    extern u8 D_80078E78[];
    extern void *D_801C8498;
    extern void *D_801C849C;
    extern void *D_801C84A0;
    extern s32 D_801C84C8;
    extern s32 D_801C84CC;
    extern s32 D_801C84D0;
    extern s32 D_801C99CC[];
    extern u8 D_8018444C[];
    extern u8 D_801844F4[];
    extern u8 D_801843A4[];
    extern u8 D_801844A0[];
    extern u8 D_80184520[];
    extern u8 D_801843F8[];
    u8 *p = D_80078E78;

    D_801C84C8 = param_2;
    D_801C84CC = (param_2 >> 2) & 3;
    D_801C84D0 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_801C8498 = D_8018444C;
        D_801C849C = D_801844F4;
        D_801C84A0 = D_801843A4;
    } else {
        D_801C8498 = D_801844A0;
        D_801C849C = D_80184520;
        D_801C84A0 = D_801843F8;
    }
    func_8013D53C((void *)param_1);
    if ((param_2 & 1) != 0) {
        if (D_801C84D0 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_801C84C8 & 2) != 0) {
            D_801C99CC[0] = 0x140;
            D_801C99CC[3] = 0x80;
            if (p[0x37] == 4) {
                D_801C99CC[0] = 0x140;
                D_801C99CC[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801C99CC[0] = 0x140;
                D_801C99CC[3] = 0x80;
            }
        }
    }
}



   /* 9-byte, align-1 -> unaligned block copy */








void func_8013D53C(void *arg0v) {

    extern Rec9 D_8018453C[];
    extern Rec12 D_80184574[];
    extern s32 D_801C84C8;
    extern u8 D_80078EAF;
    extern s32 D_801C84B0;
    extern u8 D_801C9A72;
    extern u8 D_801C9AE6;
    extern u8 D_801C999A;
    extern u8 D_801C9A54;
    extern u8 D_801C9978;
    extern u8 D_801C9999;
    extern u8 D_801C9A30;
    extern s32 D_801C9A58;
    extern s32 D_801C84C4;
    extern s32 D_801C84C0;
    extern s32 D_801C84BC;
    extern s32 D_801C84A8;
    extern s32 D_801C84B4;
    extern s32 D_801C84B8;
    extern void *D_801C8498;
    extern s32 D_801C84D0;
    extern void *D_801C84A0;
    Cmd_8013D53C *arg0 = arg0v;

    extern u8 D_80184578[];
    extern u8 D_8018457C[];
    extern unsigned char D_801C9990;
    extern s16 *D_801C84A4;
    extern s32 D_801C84D4;
    extern s32 D_801C84D8;
    extern s32 D_801C84DC;
    s32 s0v;
    s32 t9v;
    s32 t8v;
    u8 b0, b1, b2;
    u8 pad[8];   /* dead BLKmode local: frame 0x10 -> 0x18, zero code */

    if (!(D_801C84C8 & 1)) {
        D_801C84B0 = 1;
    } else {
        D_801C84B0 = D_80078EAF;
    }

    b0 = ((u8 *)D_80184574)[D_801C84B0 * 12];
    D_801C9A72 = b0;
    D_801C9AE6 = b0;
    b1 = D_80184578[D_801C84B0 * 12];
    D_801C999A = b1;
    D_801C9A54 = b1;
    b2 = D_8018457C[D_801C84B0 * 12];
    D_801C9978 = b2;
    D_801C9999 = b2;

    (*(S9 *)&D_801C9990) = ((S9 *)D_8018453C)[D_801C84B0];
    (*(S9 *)&D_801C9A30) = *(S9 *)(&D_801C9978 + 0x18);  /* same addr as (*(S9 *)&D_801C9990); distinct sym defeats cse, keeps %hi/%lo */

    D_801C9A58 = 1;
    D_801C84C4 = -1;
    D_801C84C0 = 0;
    D_801C84BC = -1;
    D_801C84A8 = 0;
    D_801C84B4 = 0;
    D_801C84B8 = 0;

    if ((D_801C84C8 & 2) && (D_801C84B0 == 4)) {
        s0v = (*(s32 * *)&D_801C8498)[18];
        t9v = (*(s32 * *)&D_801C8498)[19];
        t8v = (*(s32 * *)&D_801C8498)[20];
    } else {
        s32 *p = (s32 *)(D_801C84B0 * 12 + (s32) (*(s32 * *)&D_801C8498));  /* block-local: local-alloc ties sum into mul chain */
        s0v = p[0];
        t9v = p[1];
        t8v = p[2];
    }

    (*(Cmd_8013D53C * *)&D_801C84A4) = arg0;
    if (arg0 != 0) {
        if (D_801C84D0 != 0) {
            s32 *p = (s32 *)(D_801C84B0 * 12 + (s32) (*(s32 * *)&D_801C84A0));
            D_801C84D4 = p[0];
            D_801C84D8 = p[1];
            D_801C84DC = p[2];
        } else {
            while ((arg0->cmd & 0xFFFF) != 0xFF) {
                if ((arg0->cmd & 0xFFFF) == 9) {
                    s32 n;
                    s32 i;
                    u16 *src;
                    u16 *dst;
                    n = arg0->w * arg0->h;
                    i = 0;
                    src = arg0->data;
                    __asm__("" :: "r"(src));  /* +2 refs on src (depth-2): keeps src above i, below the mfhi temp */
                    dst = src + n;
                    if (n > 0) {
                        do {
                            u16 px;
                            s32 r, g, b, out;
                            __asm__("" :: "r"(i));  /* +3 refs on i (depth-3): lifts i over dst in the $t2 race */
                            px = *src;
                            r = ((px & 0x1F) * s0v) / 2560;
                            g = (((px & 0x3E0) * t9v) / 2560) & 0x3E0;
                            b = (((px & 0x7C00) * t8v) / 2560) & 0x7C00;
                            out = r | g | b | (px & 0x8000);
                            if (out == 0 && px != 0) {
                                out = 0x8000;
                            }
                            *dst = out;
                            dst++;
                            i++;
                            src++;
                        } while (i < n);
                    }
                }
                arg0++;
            }
        }
    }
}




// @class: schedule
// @stuck: none — MATCH (45 ins, match_one verified)

extern void func_800599B8(u16*);

void func_8013D8FC(void)
{

    extern s16 *D_801C84A4;
    register s16 *psVar3 __asm__("$17");
    register s16 *psVar2 __asm__("$16");
    register s32 c9 __asm__("$19");
    register s32 cff __asm__("$18");
    u16 sVar1;
    s16 buf[4];

    psVar3 = D_801C84A4;
    if (psVar3 != (s16 *)0x0 && (sVar1 = (u16)*psVar3, sVar1 != 0xff)) {
        c9 = 9;
        cff = 0xff;
        psVar2 = psVar3 + 5;
        do {
            if (sVar1 == c9) {
                s32 arg2 = *(s32 *)(psVar2 + 1) + psVar2[-1] * 2;
                buf[0] = psVar2[-3];
                buf[1] = psVar2[-2];
                buf[2] = psVar2[-1];
                buf[3] = *psVar2;
                ((void (*)(s32, s32))func_800599B8)((s32)buf, arg2);
            }
            psVar3 = psVar3 + 8;
            sVar1 = (u16)*psVar3;
            psVar2 = psVar2 + 8;
        } while (sVar1 != cff);
    }
}


extern void func_800599B8(u16*);
#define gte_ldIR0z()   __asm__ __volatile__("mtc2 $0, $8")
#define gte_ldrgb(p)   __asm__ __volatile__("lwc2 $6, 0(%0)"  :: "r"(p) : "memory")
#define gte_ldIRGB(p)  __asm__ __volatile__("lwc2 $28, 0(%0)" :: "r"(p) : "memory")
#define gte_dpcl()     __asm__ __volatile__("nop\n\tnop\n\tdpcl")
#define gte_stORGB(p)  __asm__ __volatile__("swc2 $29, 0(%0)" :: "r"(p) : "memory")

void func_8013D9B0(int param_1)
{

    extern void *D_801C849C;
    extern s16 *D_801C84A4;
    extern s32 D_801C84B4;
    extern s32 D_801C84BC;

    u8 buf[0x20];
    register s32 uVar13 __asm__("$16");
    register u16 *psVar14 __asm__("$17");
    register u16 *psVar15 __asm__("$18");
    register s32 uVar16 __asm__("$19");
    register void *r0 __asm__("$20");
    register u16 *puVar10 __asm__("$11");
    register u16 *puVar9 __asm__("$10");
    register s32 iVar11 __asm__("$13");
    register s32 iVar12 __asm__("$14");
    u16 sVar4;
    register u32 uVar5 __asm__("$3");
    register u32 uVar7 __asm__("$6");
    register u32 uVar1 __asm__("$7");
    register u32 uVar6 __asm__("$4");
    register u32 uVar8 __asm__("$8");
    register u32 uVar3 __asm__("$9");

    psVar15 = (*(u16 * *)&D_801C84A4);
    if (psVar15 != 0) {
        sVar4 = *psVar15;
        *(u32 *)(buf + 8) = (*(u32 * *)&D_801C849C)[param_1];
        D_801C84BC = -1;
        uVar16 = 0;
        if (sVar4 != 0xff) {
            r0 = buf + 8;
            psVar14 = psVar15 + 6;
            do {
                iVar11 = 0;
                if (sVar4 == 9) {
                    *(s16 *)(buf + 0) = psVar14[-4];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 2) = psVar14[-3];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 4) = psVar14[-2];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 6) = psVar14[-1];
                    __asm__ __volatile__("" ::: "memory");
                    {
                        register s32 mw __asm__("$3") = (s32)((s16 *)psVar14)[-2];
                        register s32 mh __asm__("$2") = (s32)((s16 *)psVar14)[-1];
                        iVar12 = mw * mh;
                    }
                    uVar13 = 0;
                    puVar10 = *(u16 **)psVar14;
                    {
                        register s32 boff __asm__("$2") = iVar12 * 2;
                        register u16 *pi __asm__("$5");
                        pi = (u16 *)((s32)puVar10 + boff);
                        __asm__ __volatile__("" : "=r"(pi) : "0"(pi));
                        puVar9 = pi;
                    }
                    if (0 < iVar12) {
                        do {
                            register u32 pix __asm__("$2");
                            register u32 out __asm__("$2");
                            u32 result;
                            *(u32 *)(buf + 0xc) = (u32)*puVar10;
                            pix = (u32)*puVar9;
                            uVar5 = pix & 0x1f;
                            uVar7 = pix & 0x3e0;
                            uVar1 = pix & 0x7c00;
                            {
                                void *p1;
                                register void *pa __asm__("$2");
                                register void *pb __asm__("$12");
                                __asm__ __volatile__("");
                                p1 = buf + 0xc;
                                __asm__ __volatile__("" : "=r"(p1) : "0"(p1));
                                gte_ldIR0z();
                                gte_ldrgb(r0);
                                gte_ldIRGB(p1);
                                gte_dpcl();
                                pa = buf + 0x10;
                                __asm__ __volatile__("" : "=r"(pa) : "0"(pa));
                                pb = pa;
                                gte_stORGB(pb);
                            }
                            out = *(u32 *)(buf + 0x10);
                            uVar6 = out & 0x1f;
                            uVar8 = out & 0x3e0;
                            uVar3 = out & 0x7c00;
                            if (uVar5 != uVar6) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar5 < (s32)uVar6) uVar5 = uVar5 + 1;
                                c = (s32)uVar6 < (s32)uVar5;
                                if (c) uVar5 = uVar5 - 1;
                            }
                            if (uVar7 != uVar8) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar7 < (s32)uVar8) uVar7 = uVar7 + 0x20;
                                c = (s32)uVar8 < (s32)uVar7;
                                if (c) uVar7 = uVar7 - 0x20;
                            }
                            if (uVar1 != uVar3) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar1 < (s32)uVar3) uVar1 = uVar1 + 0x400;
                                c = (s32)uVar3 < (s32)uVar1;
                                if (c) uVar1 = uVar1 - 0x400;
                            }
                            result = uVar5 | uVar7 | uVar1 | (*(u32 *)(buf + 0xc) & 0x8000);
                            if (result == 0 && *(u32 *)(buf + 0xc) != 0) {
                                result = 0x8000;
                            }
                            *puVar9 = (u16)result;
                            puVar9 = puVar9 + 1;
                            iVar11 = iVar11 + 1;
                            puVar10 = puVar10 + 1;
                        } while (iVar11 < iVar12);
                    }
                    if (uVar13 != 0) {
                        ((void (*)(void *))func_800599B8)(buf);
                    }
                    uVar16 = uVar16 | uVar13;
                }
                psVar15 = psVar15 + 8;
                sVar4 = *psVar15;
                psVar14 = psVar14 + 8;
            } while (sVar4 != 0xff);
        }
        D_801C84B4 = uVar16;
    }
    return;
}



// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_801C84A0)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.


extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{

    extern void *D_801C84A0;
    extern s16 *D_801C84A4;
    extern s32 D_801C84B4;
    extern s32 D_801C84D4;
    extern s32 D_801C84D8;
    extern s32 D_801C84DC;
    int *p;
    int x, y, z;
    int flag;

    if (D_801C84A4 != 0) {
        D_801C84B4 = 0;
        p = (int *)(param_1 * 12 + (int)D_801C84A0);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_801C84D4 != x) {
            flag = 1;
            if (D_801C84D4 < x) {
                if (x - D_801C84D4 < 5) {
                    D_801C84D4 = x;
                } else {
                    D_801C84D4 = D_801C84D4 + 4;
                }
            } else {
                if (D_801C84D4 - x < 5) {
                    D_801C84D4 = x;
                } else {
                    D_801C84D4 = D_801C84D4 - 4;
                }
            }
        }
        if (D_801C84D8 != y) {
            flag = 1;
            if (D_801C84D8 < y) {
                if (y - D_801C84D8 < 5) {
                    D_801C84D8 = y;
                } else {
                    D_801C84D8 = D_801C84D8 + 4;
                }
            } else {
                if (D_801C84D8 - y < 5) {
                    D_801C84D8 = y;
                } else {
                    D_801C84D8 = D_801C84D8 - 4;
                }
            }
        }
        if (D_801C84DC != z) {
            flag = 1;
            if (D_801C84DC < z) {
                if (z - D_801C84DC < 5) {
                    D_801C84DC = z;
                } else {
                    D_801C84DC = D_801C84DC + 4;
                }
            } else {
                if (D_801C84DC - z < 5) {
                    D_801C84DC = z;
                } else {
                    D_801C84DC = D_801C84DC - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_801C84B4 = flag;
    }
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013DD68);



s32 func_8013E054(void) {

    extern s32 D_801C84BC;
    return D_801C84BC;
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


DEFINE_func_8013E4B4()  /* dedup: shared engine-core @0x8013e4b4 (src/shared) */


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
    extern void (*D_80184FC0[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_80184FC0[D_80115112];
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
    extern s32 D_80184FAC;
    extern u16 D_80115110;
    extern s32 D_80115188;
    extern s16 D_80184F84;
    extern s16 D_80184F86;
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
        ep = (s32 *)&D_80184FAC;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_80184F84 = 2;
        D_80184F86 = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_80184F86 = 0;
        D_80184F84 = 0;
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
    extern void * D_801C84F0;
    extern void * D_801C84F4;
    extern unsigned char D_80184C24;
    extern unsigned char D_80184C3C;
    extern unsigned char D_80184CB0;
    extern unsigned char D_80184CB8;

    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((func_80029178(0x1c) & 0xFF) == 0) {
        D_801C84F0 = &D_80184C24;
        D_801C84F4 = &D_80184CB0;
    } else {
        D_801C84F0 = &D_80184C3C;
        D_801C84F4 = &D_80184CB8;
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
// three bases (D_80115110/D_80184FAC/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_80184FAC -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

void func_8013E958()
{

    extern u8 D_80078EC0;
    extern u16 D_80115110;
    extern unsigned short D_80115112;
    extern u16 D_80115124;
    extern s32 D_80115188;
    extern s32 D_80184FAC;
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
        v = ((s32 *)&D_80184FAC)[i] >> 6;
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
extern s32 func_8013F350(void);   /* §30#2 widened: def returns live $v0; callers discard */
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
    extern unsigned char D_80184F88;
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
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_80184F88));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_80184F88));
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013EE10);

extern void func_8013FAF8(s16 a0, s16 a1);


// @class: struct
// @stuck: none — MATCH (108 ins, relocation-masked)




s32 func_8013EF88() {

    extern short D_800B9A02;
    extern unsigned short D_80115112;
    extern u16 D_80115124;
    extern s32 D_80115188;
    extern s32 D_801151D0;
    extern s16 D_80184F84;
    extern s16 D_80184F86;
    extern int func_800D0488(int);
    extern void func_800D2624(void);
    extern S115118 D_80115118;
    extern int D_80115168;
    extern unsigned short D_80115114;

    unsigned short v;
    short i;
    register short *p124 __asm__("$16");

    v = D_80115118.field0;
    if (v != 0) {
        v = v - 1;
        D_80115118.field0 = v;
        if (v != 0) {
            (*(int*)&D_801151D0) = D_80115118.arrB0[(*(unsigned short*)&D_800B9A02)];
            ((void(*)(int, int))func_8013FAF8)(0, 5);
            for (i = 0; i < 5; i++) {
                int a = *(int *)((char *)&(*(int*)&D_80115188) + (i << 2));
                int b = *(int *)((char *)&D_80115168 + (i << 2));
                int w = a * 3;
                *(int *)((char *)&(*(int*)&D_80115188) + (i << 2)) = w;
                *(int *)((char *)&D_80115168 + (i << 2)) = b + w;
            }
            if (D_80115118.field0 < 3) {
                unsigned short *p96 = &(*(unsigned short*)&D_80184F86);
                *p96 = *p96 - 1;
            }
            {
                unsigned short *p94 = &(*(unsigned short*)&D_80184F84);
                short t = *p94 - 2;
                *p94 = t;
                if (t < 0) *p94 = 0;
            }
        }
    }
    p124 = &(*(short*)&D_80115124);
    {
        short x124 = *p124;
        if (x124 != 0) {
            if (func_800D0488(x124) == 0) return;
            *p124 = 0;
        }
    }
    if (D_80115118.field0 == 0) {
        if (D_80115114 == ((*(unsigned short*)&D_800B9A02) ^ 1)) {
            func_800D2624();
        } else {
            D_80115112 = D_80115112 + 1;
        }
    }
}




// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {

    extern unsigned short D_80115118;
    extern unsigned short D_80115112;
    extern u16 D_80115110;
    extern unsigned char D_80184F88;
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_80184F88);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013f1bc (src/shared) */


DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013f244 (src/shared) */
