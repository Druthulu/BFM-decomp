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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013F350);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013FAF8);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8013FFD8);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8014032C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80140608);



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

    extern u8 *D_80184C64;
    extern u8 *D_80184C68;
    extern u8 *D_80184C6C;
    extern u8 *D_80184C70;
    extern u8 *D_80184C74;
    extern u16 *D_80184C78[];
    extern u16 *D_80184C80[];
    extern u16 *D_80184CA0[];
    u8 *puVar1;
    s32 iVar2;
    u16 *puVar3;

    puVar1 = D_80184C64;
    iVar2 = func_80028D58();
    puVar3 = D_80184C78[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    puVar1 = D_80184C68;
    iVar2 = func_80028DE0();
    puVar3 = D_80184C78[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    iVar2 = func_80028FBC();
    *(s16 *)(D_80184C6C + 0x18) = *D_80184C80[iVar2];
    iVar2 = func_80029000();
    *(s16 *)(D_80184C70 + 0x18) = *D_80184C80[iVar2];

    puVar1 = D_80184C74;
    iVar2 = func_80028D9C();
    puVar3 = D_80184CA0[iVar2];
    *(s16 *)(puVar1 + 0x12) = *puVar3++;
    *(s16 *)(puVar1 + 0x14) = *puVar3++;
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;
    *(s16 *)(puVar1 + 0x1c) = *puVar3++;
}





















extern s16 func_8014168C(s16);
extern s32 *func_80140D68(s32 *, Prim4 *, s32, s32, s32);
/* func_80140958 -- MATCH (260 ins), verified by
 *   python3 tools/match_one.py func_80140958 --c .run/near6/wave23/func_80140958.c \
 *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077
 *
 * Three levers took the seed from 6 -> 0 (see the numbered notes in the inner block):
 *   [L1] `m == i` (not `m == 3`)  -- keeps b[0] a RUNTIME value; `m == 3` let gcc
 *        const-fold it and materialise `li a3,3` / `li t3,12` instead of
 *        `addu a3,v1,zero` / `sll t3,v1,2`.
 *   [L2] one dead `__asm__ volatile("" :: "r"(j))` -- +1 weighted REG_N_REFS on j so
 *        global.c:594 allocno_compare ranks j above k (j -> $a2, k -> $a3).
 *   [L3] `t3v = m * 4` as an EXPLICIT preheader statement (instead of letting loop.c
 *        hoist D_8011516A[m]'s index) -- gives it a LUID *below* the three constant
 *        assignments, which is what puts `move a3,v1 / sll t3,v1,2` ahead of them in
 *        sched1's backward LUID tie-break.
 */
s32 *func_80140958(ot, i, n)
s32 *ot;
s16 i;
s16 n;
{

    extern short D_800B9A02;
    extern u16 D_80115110;
    extern u8 D_80115140[];
    extern s16 D_8011514E;
    extern u8 D_80115158[];
    extern Hw4 D_8011516A[];
    extern Prim4 D_80184A7C[];
    extern Prim4 *D_80184B70[];
    extern u8 D_80115143;
    extern Prim4 D_80184A2C[];
    extern s16 D_80184F8C[];
    extern s16 D_80184F9C[];
    extern u16 D_80184AAC;
    extern u16 D_80184AAE;
  extern Env_80140958 D_800AE7BC[];
  Prim4 *p;
  s16 t;
  s32 c3;
register u16 *a __asm__("$20");
register u16 *b __asm__("$21");
register u16 *c __asm__("$23");
register u16 *e __asm__("$22");
register u16 *pb __asm__("$10");
register u32 m24 __asm__("$8");
register u32 mhi __asm__("$9");
register s32 eight __asm__("$2");
  if (i < n)
  {
    c3 = 3;
    a = &D_80115110;
    b = a + 5;
    c = a + 3;
    e = &D_80184AAE;
    do
    {
      if (((a[0] == 0) && (a[1] != c3)) && (a[1] < 6))
      {
        if (i == a[5])
        {
          ot = func_80140D68(ot, &D_80184A2C[i], i, D_80184F8C[a[3] & 7], 0);
        }
      }
      else
      {
        p = D_80184B70[i];
        if (((p != 0) && (i == b[0])) && (i != 6))
        {
          if ((i == 2) && ((*((s16 *) (b + 7))) != 0))
          {
            p = D_80184A7C;
          }
          if (i != c3)
          {
            t = ((s32 (*)(s16)) func_8014168C)(i) * 2;
          }
          else
          {
            t = ((*((u8 *) (&D_8011514E))) - D_80115143) * 2;
          }
          ot = func_80140D68(ot, p, i, D_80184F9C[c[0] & 7], t);
          if (((i == 2) && ((*((s16 *) (c + 9))) == 1)) && ((*((s16 *) (c + 12))) != 0))
          {
            ot = func_80140D68(ot, p, 2, 8, ((*((s16 *) (c + 12))) & 0xF) * 2);
          }
        }
      }
      if (i == c3)
      {
        s32 m = b[0];
        /* [L1] compare against `i`, NOT against the literal 3. */
        if ((m == i) && ((b[-2] & 8) != 0))
        {
          s16 j;
          s32 k;
          s32 t3v;
          u8 *q = ((u8 *) ot) + 0x14;
          s16 y;
          j = 0;
          k = m;
          t3v = m * 4;                  /* [L3] explicit, must sit before the 3 constants */
          pb = (u16 *) (&D_800B9A02);
          m24 = 0xFFFFFF;
          mhi = 0xFF000000;
          for (; j < 2; j++)
          {
            if (j == 0)
            {
              if (D_80115140[k] == 0)
              {
                continue;
              }
              q[-7] = 0x30;
              y = (*e) - 4;
            }
            else
            {
              s32 k2 = k * 2;
              if ((((s8 *) D_80115158)[k2] - ((s8 *) D_80115140)[k]) < 2)
              {
                continue;
              }
              q[-7] = 0x38;
              y = (*e) + 3;
            }
            *((s16 *) (q - 10)) = y;
__asm__("" ::: "memory");
            *((u32 *) ot) = 0x4000000;
            q[-8] = 0x78;
            *((u32 *) (q - 0x10)) = 0x64808080;
            *((s16 *) (q - 6)) = 0x4056;
            *((s16 *) (q - 0xC)) = (D_80184AAC + ((u16) *((u16 *) (((u8 *) D_8011516A) + t3v)))) + 0x4A;
            eight = 8;
            *((s16 *) (q - 2)) = eight;
            *((s16 *) (q - 4)) = eight;
            *((u32 *) ot) = ((*((u32 *) ot)) & mhi) | (D_800AE7BC[*pb].ot[2] & m24);
            {
register u32 *op __asm__("$4");
              op = D_800AE7BC[*pb].ot;
              op[2] = (op[2] & mhi) | (((u32) ot) & m24);
            }
            q += 0x14;
            ot += 5;
            __asm__ volatile("" :: "r"(j));   /* [L2] zero code, +1 ref on j */
          }

        }
      }
      i = i + 1;
    }
    while (i < n);
  }
  return ot;
}





s32 *func_80140D68(out, src, idx, dx, ofs)
    s32 *out;
    Prim4 *src;   /* conformed to the fleet prototype; used only as (s32)src */
    s16  idx;
    s32  dx;
    s16  ofs;
{

    extern Hw4 D_8011516A[];
    extern short D_800B9A02;
    /* §94 TYPE-CARRY: this typedef and its extern MUST be BLOCK-scope. extract_unit carries
       file-scope externs and #defines into each remapped sibling (Phase-27 _carry_macros) but
       NOT file-scope typedefs — so a file-scope Env_800D29F8 is silently dropped from every
       sibling and the family sweeps 0/137. Body-local typedefs DO survive (PTag_80140D68 below
       is the proof), so it lives here. */
         /* 0x14 stride */
    extern Env_800D29F8 D_800AE7BC[];


    register u32 mhi __asm__("$8");
    s16 *q;
    s32  a;

    out[0] = 0x04000000;
    *((u8 *)out + 0xC) = 0x70;
    *((u8 *)out + 0xD) = 0x10;
    mhi = 0x64808080;
    out[1] = mhi;
    *(u16 *)((u8 *)out + 0xE) = 0x4056;

    dx -= 0xD;
    q = (s16 *)(ofs * 2 + (s32)src);
    a = (u16)q[0] + (u16)D_8011516A[idx].x;
    a += dx;
    *(s16 *)((u8 *)out + 0x8) = a;
    *(s16 *)((u8 *)out + 0xA) = q[1] - 4;
    *(s16 *)((u8 *)out + 0x12) = 0x10;
    *(s16 *)((u8 *)out + 0x10) = 0x10;

    ((PTag_80140D68 *)out)->addr = ((PTag_80140D68 *)((D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot) + 2))->addr;
    ((PTag_80140D68 *)((D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot) + 2))->addr = (u32)out;

    return out + 5;
}




// @class: struct
// @stuck: none — MATCH


extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);

void func_80140E6C(void) {

    extern unsigned char D_80078E7F;
    extern unsigned char D_80078E7E;
    extern unsigned char D_80078E7D;
    extern M2C_UNK D_80184BA0;
    void *puVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int uVar4;

    puVar1 = (*(void * *)&D_80184BA0);
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
    extern u8 D_80184BB0;
    extern char *D_80184BD0;
    extern char *D_80184BD4;
    extern char *D_80184BD8;
    extern char *D_80184BDC;
    extern char *D_80184BE0;
    char *p;
    int r;

    if (D_80115128 == 0) {
        p = (*(char * *)&D_80184BB0);
        r = func_800D2CA8(func_80029FE4() + 1, 0x18);
        func_800D2D10(r, 2, p + 4, 1);
        strcpy(p + 0xA, func_8002AAB4());

        p = D_80184BD0;
        r = func_800D2CA8(func_8002A26C() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A2B0(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80184BD4;
        r = func_800D2CA8(func_8002A4B8() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(((int (*)(void))func_8002A4FC)(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80184BD8;
        r = func_800D2CA8(func_8002A998() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A9DC(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80184BDC;
        r = func_800D2CA8(func_8002A728() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A76C(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80184BE0;
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
    extern unsigned short D_80184A6A;
    extern unsigned short D_80184A6E;
    extern unsigned short D_80184A72;
    extern unsigned short D_80184A76;
    short sVar1;
    int iVar7;

    if (D_80115128 == 0) {
        iVar7 = D_80115172 + 0x31;
        sVar1 = D_80184A6A;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A1B4)(), func_8002A28C(), func_8002A27C(), (short)iVar7, (int)sVar1);
        sVar1 = D_80184A6E;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A400)(), func_8002A4D8(), func_8002A4C8(), (short)iVar7, (int)sVar1);
        sVar1 = D_80184A72;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A8E0)(), func_8002A9B8(), func_8002A9A8(), (short)iVar7, (int)sVar1);
        sVar1 = D_80184A76;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A670)(), func_8002A748(), func_8002A738(), (short)iVar7, (int)sVar1);
    }
    return param_1;
}


#define addPrim_1412A8(ot, p) (setaddr_1412A8(p, getaddr_1412A8(ot)), setaddr_1412A8(ot, p))
/* §37/§124 def-side asm-label alias (the S40 class lever). The TU declares
 *   extern int func_801412A8(int, int, int, int, int, int);            (ov_SC01_077.c:2720)
 * and its callers USE the return value (`param_1 = func_801412A8(...)`, :2730-:2736), while the
 * byte-true definition is `Prim_1412A8 *(Prim_1412A8 *, int, int, int, u16, u16)`. The u16 params
 * cannot agree with an `int` prototype (C default argument promotion) and the `()` no-prototype
 * escape is illegal precisely when a param promotes -- so NEITHER side can move. Giving the
 * DEFINITION a private C identifier bound to the emitted symbol by a GNU asm label decouples
 * them: the TU's declaration continues to govern the CALL SITES (their codegen is untouched --
 * which is what match_one could not see, since it only compiles this function), and the
 * definition keeps its byte-true signature. Zero blast radius. */
DEFINE_func_801412A8()  /* dedup: shared engine-core @0x801412A8 (src/shared) */


DEFINE_func_801415C0()  /* dedup: shared engine-core @0x801415c0 (src/shared) */


DEFINE_func_8014168C()  /* dedup: shared engine-core @0x8014168c (src/shared) */


DEFINE_func_801416D4()  /* dedup: shared engine-core @0x801416d4 (src/shared) */




void func_80141788(void)
{

    extern unsigned short D_80115112;
    extern void (*D_80185000[])(void);
    D_80185000[D_80115112]();
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
    extern void (*D_8018500C[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 → store retires early */
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_8018500C[D_80115112];
    fp();
    func_80141C04();
    D_80115116 += 1;
}



// @class: loose-typing
// @stuck: none — MATCH (90 ins). Key levers:
//   (1) D_8011511A must be a DIRECT volatile global (block-scope `extern volatile unsigned short`),
//       NOT `*(volatile u16*)&D_8011511A`. Volatile forces the store-2-then-read-back reload (else
//       gcc folds 2>=4 and drops the branch); direct-global access recomputes %hi/%lo per reference
//       (3 fresh lui) whereas the `&`-cast pointer form CSEs the address into ONE register (2 ins short).
//   (2) Reconcile with the TU/engine_core canonical types: D_80115158 is `u8[]` (decays -> `*(u16*)D_80115158`),
//       D_8011515C is `u8` (halfword store -> `*(u16*)&D_8011515C`), func_80029178 is `s32(s32)`. Do not
//       redeclare these — the shared DEFINE macros already provide them (conflicting-types hard error).

extern void func_800D24A0(int);
extern void func_8002D4C8(int, int);
extern void func_80141C0C(int);

s32 func_801418F8(void) {

    extern u16 D_80115110;
    extern unsigned short D_80115112;
    extern unsigned short D_80115118;
    extern short D_80115128;
    extern s32 D_80115130;
    extern u8 D_80115158[];
    extern u8 D_8011515C;
    extern s16 D_80184F84;
    extern s16 D_80184F86;
    extern u16 D_8011515A;
    extern u16 D_8011515E;
    extern u16 D_80115162;
    extern u16 D_80115166;
    extern u16 D_8011512E;
    extern void *D_801C84F0;
    extern void *D_801C84F4;
    extern u8 D_80184C24;
    extern u8 D_80184C3C;
    extern u8 D_80184CB0;
    extern u8 D_80184CB8;
    extern volatile unsigned short D_8011511A;
    extern s32 func_80029178(s32);
    unsigned short t;

    func_800D24A0(1);
    D_8011511A = 2;
    t = D_8011511A;
    D_80115118 = 0;
    D_80115130 = 0;
    if (t >= 4) {
        D_8011511A = t - 3;
    }
    *(u16*)D_80115158 = 0x106;
    if ((func_80029178(0x1C) & 0xFF) == 0) {
        D_801C84F0 = &D_80184C24;
        D_801C84F4 = &D_80184CB0;
    } else {
        D_801C84F0 = &D_80184C3C;
        D_801C84F4 = &D_80184CB8;
    }
    D_8011515A = 0x104;
    *(u16*)&D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;
    if (D_80115110 == 3) {
        func_8002D4C8(0x46E, 0);
    } else {
        func_80141C0C(0);
    }
    D_80115128 = 1;
    D_80184F84 = 0xE;
    D_80184F86 = 3;
    D_80115112 += 1;
}


extern s32 func_800D0EC4(void);
extern void func_801376E8(int a0, int a1);
extern void func_80137B80(void);
extern void func_80139954(void);
extern s32 func_8013F350(void);
extern void func_8013FAF8(s16 a0, s16 a1);
extern s32 func_8014032C(s32 a0, s32 a1);

// @class: plumbing
// @stuck: TBD — first pass



s32 func_80141A60()
{

    extern short D_800B9A02;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern u16 D_8011511A;
    extern s32 D_80115130;
    extern s16 D_8011514C;
    extern u8 D_8011515C;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern unsigned char D_80184F88;
    int v;
    s32 frame_pad[2];
    (void)&frame_pad;

    D_801151D0 = ((int *)D_801151C8)[(*(unsigned short *)&D_800B9A02)];
    func_8013F350();
    if ((*(unsigned short *)&D_8011511A) >= 4) {
        func_8013FAF8((short)(*(unsigned short *)&D_8011511A), (short)((*(unsigned short *)&D_8011511A) + 1));
    }
    func_8013FAF8(2, 3);
    v = ((int(*)(int, int))func_8014032C)(2, (short)((*(unsigned char *)&D_8011514C) + (*(unsigned char *)&D_8011514D) * (*(unsigned char *)&D_8011515C)));
    if (v != 0 && v != D_80115130) {
        D_80115130 = v;
        func_80139954();
        ((void (*)(int, void *))func_801376E8)(v, &(*(int *)&D_80184F88));
    }
    func_80137B80();
    if (func_800D0EC4() != 0) {
        (*(unsigned short *)&D_80115116) = 0xFFF8;
        (*(unsigned short *)&D_80115112) = (*(unsigned short *)&D_80115112) + 1;
    }
}


DEFINE_func_80141B90()  /* dedup: shared engine-core @0x80141b90 (src/shared) */


void func_80141C04(void) {
}

extern u16 D_80115110;
extern u16 D_80184F60[];

void func_80141C0C(s32 a0)
{
    s32 index = ((a0 << 16) >> 15) + D_80115110;
    u16 value = D_80184F60[index];
    func_8002D4C8(value, 0);
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

    extern void (*D_80185030[])(void);
    short sVar1;
    int iVar2;
    register unsigned short t __asm__("$3");

    (*D_80185030[(unsigned short)param_1[1]])();
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

    extern void (*D_80185040[])(void);
    D_80185040[*(u16 *)((s32)a0 + 0x2)]();
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

    extern s32 D_80185024;
    register s32 iVar1 __asm__("$16");

    if (*(short *)(param_1 + 0x70) != 0) {
        iVar1 = ((s32 (*)(void))func_8012C1B8)();
    } else {
        iVar1 = func_8012C1DC(*(s32 *)(param_1 + 100));
    }
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CA1C(iVar1, (s32)&D_80185024);
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
    extern void (*D_80185054[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80185054[*(u16 *)(param_1 + 2)]();
    }
}


DEFINE_func_80142838()  /* dedup: shared engine-core @0x80142838 (src/shared) */


DEFINE_func_801428CC()  /* dedup: shared engine-core @0x801428cc (src/shared) */



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_8014292C(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_80185070[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80185070[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_80142978(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_80185240[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80185240[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_801429C4(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_801852F8[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_801852F8[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)
// @reconcile: func_80142A80 is DEFINED later in this TU as `void func_80142A80(void)`.
//   The uc2 draft declared it `extern void func_80142A80(int)` -> conflicting types.
//   Escape §17a-1/§20: conform the declaration to the TU's, cast at the use site
//   (codegen-neutral: the argument still lands in $a0).

extern void func_80142A80(void);

void func_80142A10(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_80185308[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80185308[*(u16 *)(param_1 + 2)]();
        if (*(s16 *)(param_1 + 0xFC) != 0) {
            ((void (*)(int))func_80142A80)(param_1);
        }
    }
}




// @class: struct
// @stuck: none — MATCH (packed-word struct -> lwl/lwr unaligned copy; union byte[] -> $sp-direct lbu; branch-polarity invert -> beqz)


void func_80142A80(void)
{

    extern u16 D_800B99D8;
    extern struct packed_word D_801C7B90;
    extern u8 D_801C84F8;
    extern u8 D_801C84F9;
    extern u8 D_801C84FA;
    u16 flags;
    union word_bytes local;
    s32 mul;

    flags = D_800B99D8;
    local.pw = D_801C7B90;

    if (flags & 0x10) {
        mul = (s8)((flags & 0xf) >> 1) + 9;
    } else {
        mul = 0x10 - (s8)((flags & 0xf) >> 1);
    }

    D_801C84F8 = mul * (local.b[0] >> 4);
    D_801C84F9 = mul * (local.b[1] >> 4);
    D_801C84FA = mul * (local.b[2] >> 4);
}


DEFINE_func_80142B2C()  /* dedup: shared engine-core @0x80142B2C (src/shared) */


void func_801439C0(u8 *a0);
void func_8012AD44(s32 *a0, s16 a1);
void func_8012C218(void *a0);
void func_8012C098(void *param_1);

void func_80142BB4(s32* param_1, s32 param_2, s32 param_3)
{
  if (*(short *)((char *)param_1 + 0xfc) == 1) {
    if ((param_2 != 0) || (*(short *)((char *)param_1 + 0x100) == 0)) {
      *(unsigned short *)((char *)param_1 + 0x5c) =
        *(unsigned short *)((char *)param_1 + 0x5c) & 0xfefe;
      *(unsigned int *)(*(int *)((char *)param_1 + 0x20) + 4) =
        *(unsigned int *)(*(int *)((char *)param_1 + 0x20) + 4) | 0x80000000;
      func_801439C0((u8 *)*(int *)((char *)param_1 + 0xcc));
      func_8012AD44((s32 *)param_1, param_3);
    }
  }
  else if ((param_2 != 0) || (*(short *)((char *)param_1 + 0x100) == 0)) {
    func_8012C218(param_1);
  }
  else {
    func_8012C098(param_1);
  }
}


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

    extern int D_80185048;
    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))func_8012C1B8)();
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, s32))func_8001CA1C)(v0, (s32)&D_80185048);
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

    extern unsigned char D_80185064[];
    short sVar1;
    int iVar2;

    *(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))func_8012C1B8)();
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(iVar2, &D_80185064);
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

    extern s32 D_80185230[];
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
        ((void (*)(s32, s32))func_8012A828)(d, D_80185230[*(u16 *)(d + 0x70) & 0xf]);
        ((void (*)(s32))func_80142B2C)(d);
    }
}


DEFINE_func_80142F68()  /* dedup: shared engine-core @0x80142f68 (src/shared) */


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

    extern unsigned char D_80185250[];
    extern unsigned char D_801852B0[];
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
        ((void (*)(int, void *))func_8001CA1C)(s1_copy, D_80185250);
        sVar1 = (*(unsigned short *)(s0_param + 0x70) & 0xf) * 0x600 + 0xc00;
        *(short *)(s1_copy + 0x1a) = sVar1;
        *(short *)(s1_copy + 0x18) = sVar1;
        *(short *)(s0_param + 0xfc) = 0;
        func_8012A828(s0_param, D_801852B0);
        ((void (*)(int))func_80142B2C)(s0_param);
    }
}


DEFINE_func_801430F4()  /* dedup: shared engine-core @0x801430f4 (src/shared) */


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

    extern u8 D_801C7B8C;
    extern u8 D_801C84F8;
    extern u8 D_801C84FC;
    u8 buf[8];
    s32 iVar5;
    u16 uVar2;
    s16 sVar4;

    register s32 d __asm__("$16");
    memcpy(buf, &D_801C7B8C, 4);
    iVar5 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar5;
    d = iVar5;
    if (iVar5 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001CA88)(d, &D_801C84F8);
        uVar2 = *(u16 *)(param_1 + 0x70);
        *(s16 *)(d + 0x76) = -0x10;
        sVar4 = (uVar2 & 0xf) * 0x600 + 0xc00;
        *(s16 *)(d + 0x1a) = sVar4;
        *(s16 *)(d + 0x18) = sVar4;
        *(u32 *)(d + 4) = *(u32 *)(d + 4) | 0x50000000;
        if (func_8012E504(param_1, 0x33) == 0) {
            *(s16 *)(param_1 + 0xfc) = 1;
            func_800233CC(&D_801C84F8, 0x10);
            memcpy(&D_801C84FC, buf, 4);
        } else {
            *(s16 *)(param_1 + 0xfc) = 0;
        }
        ((void (*)(s32))func_80142B2C)(param_1);
    }
}


DEFINE_func_801432FC()  /* dedup: shared engine-core @0x801432fc (src/shared) */


DEFINE_func_80143390()  /* dedup: shared engine-core @0x80143390 (src/shared) */


DEFINE_func_801433F0()  /* dedup: shared engine-core @0x801433f0 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (pending gate)


extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_80143458(s32 param_1)
{

    extern u8 D_800D387C[];
    extern u32 D_80185408[];
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
                  D_80185408[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


DEFINE_func_8014350C()  /* dedup: shared engine-core @0x8014350c (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (pending gate)


extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8014358C(s32 param_1)
{

    extern u8 D_80185418[];
    extern u32 D_80185514[];
    s32 p;
    u16 v;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_80185418;

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
                  D_80185514[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


DEFINE_func_80143640()  /* dedup: shared engine-core @0x80143640 (src/shared) */


DEFINE_func_801437D8()  /* dedup: shared engine-core @0x801437d8 (src/shared) */


DEFINE_func_80143970()  /* dedup: shared engine-core @0x80143970 (src/shared) */


DEFINE_func_80143994()  /* dedup: shared engine-core @0x80143994 (src/shared) */


DEFINE_func_801439C0()  /* dedup: shared engine-core @0x801439c0 (src/shared) */


DEFINE_func_801439FC()  /* dedup: shared engine-core @0x801439fc (src/shared) */




void func_80143B30(void *a0) {

    extern void (*D_80185530[])(void);
    D_80185530[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143B6C()  /* dedup: shared engine-core @0x80143b6c (src/shared) */


DEFINE_func_80143BDC()  /* dedup: shared engine-core @0x80143bdc (src/shared) */




void func_80143C38(void *a0) {

    extern void (*D_8018553C[])(void);
    D_8018553C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143C74()  /* dedup: shared engine-core @0x80143c74 (src/shared) */




void func_80143C98(void *a0) {

    extern void (*D_80185544[])(void);
    D_80185544[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143CD4()  /* dedup: shared engine-core @0x80143cd4 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (80 ins, relocation-masked). iVar2/iVar3 pinned $s1/$s2; sVar4 is an
//   int set BEFORE the call so it naturally takes callee-saved $s3; chained assignment
//   a=b=c=sVar4 materializes the value once (the addu $v0,$s3,$zero move) + delay-slot store.

     /* size 0x0c */

extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80143D28(s32 param_1) {

    extern MatEntry D_80185568[];
    register s32 iVar3 __asm__("$18") = *(s32 *)(param_1 + 0x20); /* $s2 */
    register s32 iVar2 __asm__("$17") = *(s32 *)(param_1 + 0x64); /* $s1 */
    MatEntry *p = &D_80185568[*(s16 *)(param_1 + 0x70)];
    s32 sVar4;
    s32 iVar1;

    *(s16 *)(iVar3 + 0x14) = p->f8;
    *(u16 *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + p->fa;
    sVar4 = 0x1000;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)(*(s32 *)(param_1 + 0x20) + 0x34), p, (void *)(param_1 + 0x50));

    if (*(s16 *)(param_1 + 0xfe) == 0 &&
        (iVar2 == 0 || *(s16 *)(iVar2 + 0x36) != *(s16 *)(param_1 + 0xfc) ||
         *(u8 *)(iVar2 + 0xc1) != 6)) {
        if (0x10 < *(s32 *)(param_1 + 0x1c)) {
            *(s32 *)(param_1 + 0x1c) = 0x10;
        }
        *(s16 *)(param_1 + 0xfe) = 1;
    }

    iVar1 = *(s32 *)(param_1 + 0x1c);
    if (iVar1 < 0x11) {
        sVar4 = iVar1 << 8;
    }
    if (0x73 < iVar1) {
        sVar4 = (0x78 - iVar1) << 10;
    }
    *(s16 *)(iVar3 + 0x18) = *(s16 *)(iVar3 + 0x1a) = *(s16 *)(iVar3 + 0x1c) = sVar4;

    if (func_8012BEE8(param_1)) {
        func_8012C218((void *)param_1);
    }
}




void func_80143E68(void *a0) {

    extern void (*D_8018558C[])(void);
    D_8018558C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80143EA4(void) {
}

void func_80143EAC(void) {
}

void func_80143EB4(void) {
}

DEFINE_func_80143EBC()  /* dedup: shared engine-core @0x80143ebc (src/shared) */




void func_80144054(void *a0) {

    extern void (*D_801855A0[])(void);
    D_801855A0[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: regalloc-order
// @stuck: 154/154 ins structural match (callees/consts/ctrl-flow/stack/GPU-packet all byte-correct); residual 25 = caller-saved temp-reg coalescing in the final ring-vertex block (target reuses dead $s0=iVar3 for iVar3-(iVar4>>6) subu where gcc reuses iVar4>>6's reg; iVar4 mflo -> $a3 vs target $v0) + 2-ins schedule swap of giv-increment vs iVar2*4 -> permuter grinder territory (§27 step-5)

 /* 0x14 stride */

extern void *func_80010A08(s32);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 AddPrim(s32, void *);

void func_80144090(s32 param_1) {

    extern OtBlk aD800A651C_80144090[] __asm__("D_800A651C");
    extern u8 D_800AF648;
    extern short aD800B9A02_80144090 __asm__("D_800B9A02");
    void *iVar1;
    s32 iVar2;
    s32 iVar3;
    s32 iVar4;
    s32 iVar5;
    s32 iVar6;
    struct {
        s16 v10[4];
        u16 sxy[2];
        s32 p;
        s32 flag;
    } L;

    iVar1 = func_80010A08(0x140);
    if (iVar1 != 0) {
        *(s32 *)(param_1 + 4) = *(s32 *)(param_1 + 4) + *(s32 *)(param_1 + 0x10);
        *(s32 *)(param_1 + 8) = *(s32 *)(param_1 + 8) + *(s32 *)(param_1 + 0x14);
        *(s32 *)(param_1 + 0xc) = *(s32 *)(param_1 + 0xc) + *(s32 *)(param_1 + 0x18);
        L.v10[0] = *(u16 *)(param_1 + 6);
        L.v10[1] = *(u16 *)(param_1 + 0xa);
        L.v10[2] = *(u16 *)(param_1 + 0xe);
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648);
        iVar2 = RotTransPers((s32)L.v10, (s32)L.sxy, &L.p, &L.flag);
        iVar2 = iVar2 + 4;
        if (iVar2 < 0) {
            iVar2 = 0;
        }
        iVar6 = 0;
        do {
            *(s32 *)((u8 *)iVar1 + 4) = 0xffffff;
            *(u8 *)((u8 *)iVar1 + 3) = 4;
            *(u8 *)((u8 *)iVar1 + 7) = 0x20;
            if (*(s32 *)(param_1 + 0x1c) - 6 < 1) {
                *(s16 *)((u8 *)iVar1 + 8) = L.sxy[0];
                *(s16 *)((u8 *)iVar1 + 0xa) = L.sxy[1];
            } else {
                iVar5 = func_8004787C(iVar6);
                *(s16 *)((u8 *)iVar1 + 8) = L.sxy[0] + ((iVar5 * ((*(s32 *)(param_1 + 0x1c) - 6) << 4)) >> 0xc);
                iVar5 = func_80047948(iVar6);
                *(s16 *)((u8 *)iVar1 + 0xa) = L.sxy[1] + ((iVar5 * ((*(s32 *)(param_1 + 0x1c) - 6) << 4)) >> 0xc);
            }
            iVar3 = func_8004787C(iVar6) * (*(s32 *)(param_1 + 0x1c) << 4);
            iVar4 = func_80047948(iVar6) * (*(s32 *)(param_1 + 0x1c) << 4);
            iVar6 = iVar6 + 0x100;
            *(s16 *)((u8 *)iVar1 + 0x10) = L.sxy[0] + ((iVar3 + (iVar4 >> 6)) >> 0xc);
            *(s16 *)((u8 *)iVar1 + 0x12) = L.sxy[1] + ((iVar4 + (iVar3 >> 6)) >> 0xc);
            *(s16 *)((u8 *)iVar1 + 0xc) = L.sxy[0] + ((iVar3 - (iVar4 >> 6)) >> 0xc);
            *(s16 *)((u8 *)iVar1 + 0xe) = L.sxy[1] + ((iVar4 - (iVar3 >> 6)) >> 0xc);
            AddPrim(aD800A651C_80144090[(u16)aD800B9A02_80144090].a + (iVar2 * 4), iVar1);
            iVar1 = (u8 *)iVar1 + 0x14;
        } while (iVar6 < 0x1000);
    }
}


extern void func_8012C218(void *a0);

// @class: struct
// @stuck: none — MATCH (relocation-masked match_one); fn-ptr dispatch table + 0x1c counter, sibling idiom (func_801427EC/func_80143B30)


void func_801442F8(int param_1)
{

    extern void (*D_801855A8[])();
    int iVar1;

    D_801855A8[*(u16 *)(param_1 + 2)]();
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

    extern u8 D_80185524;
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
        func_8001CB6C((u8 *)iVar3, (s32)&D_80185524, 0x250, 0x1A0);
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
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_80144458(void *arg0) {

    extern s32 D_80185538;
    s32 temp_s0;
    void *temp_s2;
    void *temp_v0;

    temp_s2 = M2C_FIELD(arg0, void **, 0xCC);
    if (M2C_FIELD(arg0, s16 *, 0x70) == 0) {
        temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x64), void **, 0x20);
        if (temp_v0 != NULL) {
            temp_s0 = (M2C_FIELD(temp_v0, s16 *, 0x12) - 0x400) & 0xFFF;
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (func_80047948(temp_s0) * D_80185538 * 0x10);
            M2C_FIELD(arg0, s32 *, 0x18) = (s32) (func_8004787C(temp_s0) * -D_80185538 * 0x10);
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


DEFINE_func_8014462C()  /* dedup: shared engine-core @0x8014462c (src/shared) */


DEFINE_func_801446A4()  /* dedup: shared engine-core @0x801446a4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (65 ins, match_one). Levers: uVar2/$2 + addr/$3 pins; split (uVar2&0xFFFFFFF) into addr then (addr|0x80000000)+8 deref; %hi/%lo of 0x80000008 via plain 0x80000000+8 (match_one masks the target's D_80000008 reloc, real bytes identical); v1/3 magic-divide; gv+fv reassoc (field-0x30 in own temp) loads field first
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_8014477C(void *param_1) {

    extern u8 D_8018554C;
    extern u8 D_80185558;
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
    ((void (*)(s32, void *))func_8001CA1C)(v0, &D_8018554C);
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
    ((void (*)(void *, void *))func_8012A828)(param_1, &D_80185558);
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

    extern u8 D_80185524;
    extern u8 D_80185594;
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
            func_8001CB6C((u8 *)obj, (s32)&D_80185524, 0x250, 0x1A0);
            b = 0x14;
        } else {
            func_8001CB6C((u8 *)obj, (s32)&D_80185594, 0x300, 0x1D0);
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

    extern void (*D_801855B0[])(void);
    D_801855B0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A04()  /* dedup: shared engine-core @0x80144a04 (src/shared) */




void func_80144A2C(void *a0) {

    extern void (*D_801855B8[])(void);
    D_801855B8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A68()  /* dedup: shared engine-core @0x80144a68 (src/shared) */


void func_80144A90(void) {
}

DEFINE_func_80144A98()  /* dedup: shared engine-core @0x80144a98 (src/shared) */


DEFINE_func_80144AEC()  /* dedup: shared engine-core @0x80144aec (src/shared) */


DEFINE_func_80144B14()  /* dedup: shared engine-core @0x80144B14 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80144B9C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801457A4);

void func_801458E0(void) {
}

DEFINE_func_801458E8()  /* dedup: shared engine-core @0x801458e8 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_80186144 block defeats the tail-merge of the two identical D_80186144 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145934(void) {

    extern u8 D_80186144;
    extern u8 D_801860B4;
    extern u8 D_80186090;
    extern u8 D_8018606C;
    extern u8 D_80186120;
    extern u8 D_801860FC;
    extern u8 D_801860D8;
    extern u8 D_80186048;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_80186144;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_80186144 load from being
         * tail-merged with the v>=0x384 D_80186144 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_801860B4;
    } else if (v >= 0x578) {
        p = &D_80186090;
    } else if (v >= 0x514) {
        p = &D_8018606C;
    } else if (v >= 0x384) {
        p = &D_80186144;
    } else if (v >= 0x258) {
        p = &D_80186120;
    } else if (v >= 0xC8) {
        p = &D_801860FC;
    } else if (v >= 0xA) {
        p = &D_801860D8;
    } else {
        p = &D_80186048;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_801861D4 block defeats the tail-merge of the two identical D_801861D4 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145A2C(void) {

    extern u8 D_801861D4;
    extern u8 D_801860B4;
    extern u8 D_80186090;
    extern u8 D_8018606C;
    extern u8 D_801861B0;
    extern u8 D_8018618C;
    extern u8 D_80186168;
    extern u8 D_80186048;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_801861D4;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_801861D4 load from being
         * tail-merged with the v>=0x384 D_801861D4 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_801860B4;
    } else if (v >= 0x578) {
        p = &D_80186090;
    } else if (v >= 0x514) {
        p = &D_8018606C;
    } else if (v >= 0x384) {
        p = &D_801861D4;
    } else if (v >= 0x258) {
        p = &D_801861B0;
    } else if (v >= 0xC8) {
        p = &D_8018618C;
    } else if (v >= 0xA) {
        p = &D_80186168;
    } else {
        p = &D_80186048;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}


DEFINE_func_80145B24()  /* dedup: shared engine-core @0x80145b24 (src/shared) */


DEFINE_func_80145BF8()  /* dedup: shared engine-core @0x80145bf8 (src/shared) */


DEFINE_func_80145C54()  /* dedup: shared engine-core @0x80145c54 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80145CEC);



// @class: schedule
// @stuck: branch layout — 3-way dispatch on param_1; trying switch form

extern s32 func_80029178(s32 arg);
extern void func_80146014(s32 a0);


void func_80145EE8(s32 param_1)
{

    extern unsigned char D_801855CC[];
    extern unsigned char D_801855FC[];
    extern unsigned char D_8018564C[];
    extern unsigned char D_8018567C[];
    extern unsigned char D_801856AC[];
    switch (param_1) {
    case 0:
        if (((unsigned char (*)(int))func_80029178)(0x1F) != 0) {
            ((void (*)(void *))func_80146014)(D_801855CC);
        }
        if (((unsigned char (*)(int))func_80029178)(0x21) != 0) {
            ((void (*)(void *))func_80146014)(D_801855FC);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1E) != 0) {
            ((void (*)(void *))func_80146014)(D_8018564C);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1D) != 0) {
            ((void (*)(void *))func_80146014)(D_8018567C);
        }
        if (((unsigned char (*)(int))func_80029178)(0x20) == 0) {
            return;
        }
        ((void (*)(void *))func_80146014)(D_801856AC);
        break;
    case 1:
        ((void (*)(void *))func_80146014)(D_801855CC);
        ((void (*)(void *))func_80146014)(D_801855FC);
        ((void (*)(void *))func_80146014)(D_8018564C);
        ((void (*)(void *))func_80146014)(D_8018567C);
        ((void (*)(void *))func_80146014)(D_801856AC);
        break;
    }
}


DEFINE_func_80146014()  /* dedup: shared engine-core @0x80146014 (src/shared) */


void func_80146074(void) {
}


extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();

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
        "lui   $at, %%hi(D_801C8538)\n"
        "sw    $v0, %%lo(D_801C8538)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8538)\n"
        "lw    $v0, %%lo(D_801C8538)($v0)\n"
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


extern void *memcpy(void *dst, const void *src, u32 n);
extern void func_80146FC4(s32 a0);
extern void func_80150A70(s32 a0);
extern void func_80147098(s32 *a0);
extern void func_8014A638(s32 arg0);
extern s32  func_80155458(s32 a0);
extern s32  func_80029104(void);
extern void func_80029344(void);
extern void func_8014ADE0(s32 a0);
extern void func_8014B350(s32 a0);
extern void func_8014B7A4(s16 *param_1);
extern s32 func_80161D58(s32 a0);
extern void func_80161A90(s32 a0);
extern void func_8014B504(u16 *a0);
extern void func_80149BEC(s32 a0);
extern void func_8014B5D0(s32 *a0);
extern void func_8014C99C(u8 *a0);
extern void func_8014B190(s32 s0);
extern void func_80148648(s32 a0, s32 a1);
extern s32 func_80149228(s32 a0);
extern void func_8014A59C(s32 a0);
extern void func_8016F14C(void *a0);
extern void func_80154418(void *a0);
extern void func_80154BE4(s32 a0);
extern void func_80165694(s32 arg0);
extern void func_801654A8(s32 a0);
extern void func_8014A680(s32 a0);
extern void func_8014A6A8(s32 a0);
extern void func_8014A71C(s32 a0);
extern void func_80172588(s32 *a0);
extern void func_801473DC(s32 *a0);
extern void func_80015978(s32 a0, s32 *a1);
s32 func_80146128(void)
{

    extern s32 D_80126B58;
    extern s32 *D_80126B78;
    extern u8 D_80078EC1;
    extern s32 D_80078EC8;
    extern s32 D_80126B9C;
    extern s32 D_8011F730;
    extern u16 D_801152B8;
    extern u16 D_8012693A;
    extern u8 D_80126BE0[];
    extern u8 D_801150F0[];
    register s32 base __asm__("$16");
    register s32 *p   __asm__("$17");
    p = D_80126B78;
    base = (s32)&D_80126B58;
    func_80146FC4(base);
    memcpy((void *)D_801150F0, (void *)D_80126BE0, 8);
    func_80150A70(base);
    ((void (*)(s32))func_80147098)(base);
    func_8014A638(base);
    D_8011F730 = 0;
    D_801152B8 = 0;
    D_8012693A = 0;
    if (D_80078EC1 == 0x10 && D_80078EC8 != 0) {
        *(u16 *)((s32)p + 2) = 6;
        D_80126B9C |= 0x800;
    } else {
        *(u16 *)((s32)p + 2) = 1;
        *(s32 *)(base + 0x44) &= ~0x800;
    }
    if (*(s32 *)(base + 0x1B0) != 0) {
        *(s32 *)(base + 0x1B0) = *(s32 *)(base + 0x1B0) - 1;
    }
    if (func_80155458(base) == 0 && (*(s32 *)(base + 0x44) & 0x4000000) == 0) {
        if ((func_80029104() & 0xFF) != 0) {
            func_8014ADE0(base);
            func_8014B350(base);
            ((void (*)(s32))func_8014B7A4)(base);
            ((void (*)(s32))func_80161D58)(base);
        }
        func_80029344();
        func_80161A90(base);
        ((void (*)(s32))func_8014B504)(base);
        func_80149BEC(base);
        ((void (*)(s32))func_8014B5D0)(base);
        ((void (*)(s32))func_8014C99C)(base);
        func_8014B190(base);
        func_80148648(base, 0);
        ((void (*)(s32))func_80149228)(base);
        func_8014A59C(base);
        ((void (*)(s32))func_8016F14C)(base);
        ((void (*)(s32))func_80154418)(base);
        func_80154BE4(base);
        func_80165694(base);
        func_801654A8(base);
        func_8014A680(base);
        func_8014A6A8(base);
        func_8014A71C(base);
        ((void (*)(s32))func_80172588)(base);
        ((void (*)(s32))func_801473DC)(base);
        ((void (*)(s32, s32))func_80015978)(base + 4, base + 0x98);
        return 1;
    }
    ((void (*)(s32, s32))func_80015978)(base + 4, base + 0x98);
    return 0;
}



// @class: struct
// @stuck: none — MATCH (fnptr-table idiom: D_801856FC[u8 idx](&arg))

void func_80146360(void)
{

    extern void (*D_801856FC[])(void *);
    extern u8 D_80126BA4;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_80126B58;
    D_801856FC[D_80126BA4](&D_80126B58);
}






   /* size 8, align 1 -> unaligned block move */

DEFINE_func_801463A0()  /* dedup: shared engine-core @0x801463A0 (src/shared) */


DEFINE_func_80146534()  /* dedup: shared engine-core @0x80146534 (src/shared) */


DEFINE_func_80146554()  /* dedup: shared engine-core @0x80146554 (src/shared) */


DEFINE_func_80146578()  /* dedup: shared engine-core @0x80146578 (src/shared) */


DEFINE_func_8014659C()  /* dedup: shared engine-core @0x8014659c (src/shared) */


DEFINE_func_801465C0()  /* dedup: shared engine-core @0x801465c0 (src/shared) */


DEFINE_func_801465E4()  /* dedup: shared engine-core @0x801465e4 (src/shared) */


DEFINE_func_80146608()  /* dedup: shared engine-core @0x80146608 (src/shared) */


DEFINE_func_801466B4()  /* dedup: shared engine-core @0x801466b4 (src/shared) */


DEFINE_func_801466F0()  /* dedup: shared engine-core @0x801466f0 (src/shared) */


DEFINE_func_80146750()  /* dedup: shared engine-core @0x80146750 (src/shared) */


DEFINE_func_8014680C()  /* dedup: shared engine-core @0x8014680c (src/shared) */


DEFINE_func_801468C8()  /* dedup: shared engine-core @0x801468c8 (src/shared) */


DEFINE_func_80146924()  /* dedup: shared engine-core @0x80146924 (src/shared) */


DEFINE_func_80146994()  /* dedup: shared engine-core @0x80146994 (src/shared) */


DEFINE_func_801469C8()  /* dedup: shared engine-core @0x801469c8 (src/shared) */



extern void func_80146AFC(void*);
void aF80146A6C(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6) __asm__("func_80146A6C");
void aF80146A6C(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6)
{
    u8 sp[0x18];
    *(s16 *)(sp + 0x0) = a0;
    *(s32 *)(sp + 0x8) = a1;
    *(s16 *)(sp + 0x2) = a2;
    *(s16 *)(sp + 0x4) = a3;
    *(s16 *)(sp + 0x6) = a4;
    *(s32 *)(sp + 0xC) = a5;
    *(s32 *)(sp + 0x10) = a6;
    ((s32 (*)(void *))func_80146AFC)(sp);
}


DEFINE_func_80146AB4()  /* dedup: shared engine-core @0x80146ab4 (src/shared) */


extern s32 func_80146B9C(void * arg0);
  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_80146AFC;

/* func_80146AFC — ASCENDING twin of the byte-proven DEFINE_func_80146B9C()
 * in src/shared/engine_core.h (cookbook §71: find the already-matched sibling first).
 * Same 0x58-stride slot table (base D_8011D030), same 7-store copy body in the same
 * order, same $a2/$a1 giv pair. 80146B9C walks DOWN; this one walks UP, so the guard
 * is `p < end`, end = p + 0xA50 (30 slots x 0x58).
 *
 * DECAY ROOT CAUSE (this redraft): the stored backlog draft had been rewritten to
 * `void func_80146AFC(...)`, which drops BOTH `return 0` paths' `addu $v0,$zero,$zero`
 * and the hit path's `j .L80146B94` => LENGTH-DRIFT -2 (38 vs 40) plus $v0/$v1 regalloc
 * drift on the final lw/sw pair. Restoring the s32 return type (the fleet spelling the
 * banked sibling func_80146B9C already uses) restores MATCH at 40/40.
 *
 * RECONCILE (2026-08-01) — the whole-binary gate failed with
 *   ov_SC01_077_after.c:592: conflicting types for `D_8011D030' (previous decl :564)
 * TWO file-scope collisions were present; both are fixed HERE, with NO edit to
 * src/shared/engine_core.h and NO change to the generated code (re-verified MATCH
 * after each step):
 *
 *   1. D_8011D030 (the reported one). DEFINE_func_801469C8() emits
 *      `extern s32 D_8011D030;` at FILE scope (engine_core.h:10811, above the
 *      `s32 func_801469C8(...) {` line), and this TU expands that macro at :564 —

    extern s32 D_8011D030;
 *      i.e. before the splice point :570. The draft's `extern u16` therefore
 *      redeclared it incompatibly at :592. Conformed to the TU's `extern s32`.
 *      Codegen-neutral: the sole use is `(u8 *)&D_8011D030`, an address-of, so the
 *      declared object type never reaches a load/store width (cookbook §20).
 *
 *   2. func_80146AFC ITSELF (latent, would have surfaced next). DEFINE_func_8014C010()
 *      (:13510) and DEFINE_func_8014AD30() (:13524) each emit a file-scope
 *      `extern void func_80146AFC(void *a0);`, and this TU expands them at :1386 and
 *      :1541 — after the splice — so an `s32 func_80146AFC` definition collides on the
 *      RETURN axis. Fixed with the §37/§124 ASM-LABEL ALIAS: the C identifier is
 *      aF80146AFC, the emitted label is func_80146AFC, so the canonical void decl and
 *      this s32 definition never share a namespace. Callers discard the result, so the
 *      void-typed call sites stay codegen-identical.
 *
 * Both were reproduced and then cleared against the real cpp+cc1-2.7.2 pair using a
 * synthetic copy of this TU's declaration environment (.run/uc2/_recon_probe_80146AFC.c):
 * the pre-reconcile spelling emits exactly the gate's error pair; the spelling below
 * compiles clean.
 *
 * ORACLE: tools/match_one.py func_80146AFC --c .run/uc2/func_80146AFC.c
 *         --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_after  -> MATCH (40 ins)
 */


s32 aF80146AFC(void *arg0) __asm__("func_80146AFC");

s32 aF80146AFC(void *arg0)
{
    register u8 *p __asm__("$6");
    register u8 *q __asm__("$5");
    u8 *end;
    p = (u8 *)&D_8011D030;
    end = p + 0xA50;
    if ((u32)p < (u32)end) {
        q = p + 0x30;
        do {
            if (*(u16 *)p == 0) {
                *(s32 *)(q + 0x4) = *(s32 *)((u8 *)arg0 + 0x8);
                *(s16 *)p = *(u16 *)((u8 *)arg0 + 0x0);
                *(s16 *)(q - 0x2A) = *(u16 *)((u8 *)arg0 + 0x2);
                *(s16 *)(q - 0x26) = *(u16 *)((u8 *)arg0 + 0x4);
                *(s16 *)(q - 0x22) = *(u16 *)((u8 *)arg0 + 0x6);
                *(s32 *)(q - 0x4) = *(s32 *)((u8 *)arg0 + 0xC);
                *(s32 *)(q + 0x0) = *(s32 *)((u8 *)arg0 + 0x10);
                return (s32)p;
            }
            p += 0x58;
            q += 0x58;
        } while ((u32)p < (u32)end);
    }
    return 0;
}


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


extern s16 func_8012A68C(void);
extern s16 func_8012A758(void);
extern void func_8004978C(s16 *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
void func_80146F58(s32 a0, s32 a1) {
    s16 vec[3];
    u8 mat[0x20];
    vec[0] = func_8012A68C();
    vec[1] = func_8012A758();
    vec[2] = 0;
    func_8004978C(vec, mat);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, (void *)a0, (void *)a1);
}


extern void func_80015954(s32 a0, s32 a1);
extern void *memcpy(void *dst, const void *src, u32 n);
void func_80146FC4(s32 a0) {

    extern u8 D_80126DB0[];
    extern u16 D_80126DB6;
    s32 s1 = a0;
    s32 s0;
    if (*(s16 *)(s1 + 0xA) >= 0x401) {
        s0 = (s32)D_80126DB0;
        func_80015954(s0, s1 + 0x4);
        memcpy((void *)(s1 + 0x88), (void *)s0, 8);
        *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = D_80126DB6;
    }
}


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


DEFINE_func_80147364()  /* dedup: shared engine-core @0x80147364 (src/shared) */


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


DEFINE_func_801483E8()  /* dedup: shared engine-core @0x801483e8 (src/shared) */


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
    extern ActorFn D_80185704[];
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
        return D_80185704[*(u16 *)(p + 0xAA) >> 12](a0) & 0xFF;
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
    extern s32 D_80185744[];
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
    return (s32)(s16)((s16 (*)())(D_80185744[D_80126C02 >> 0xc]))();
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80148E54);

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


DEFINE_func_80149350()  /* dedup: shared engine-core @0x80149350 (src/shared) */


DEFINE_func_80149374()  /* dedup: shared engine-core @0x80149374 (src/shared) */


DEFINE_func_801493D0()  /* dedup: shared engine-core @0x801493d0 (src/shared) */


DEFINE_func_8014942C()  /* dedup: shared engine-core @0x8014942c (src/shared) */


void func_8012F038(int param_1, short *param_2, short *param_3);

void func_80149450(int param_1, short *param_2)
{
    short tmp_out[3];
    short tmp_in[3];

    tmp_in[0] = param_2[1];
    tmp_in[1] = param_2[3];
    tmp_in[2] = param_2[5];

    func_8012F038(*(int *)(param_1 + 0x20) + 0x34, tmp_in, tmp_out);

    param_2[1] = tmp_out[0];
    param_2[3] = tmp_out[1];
    param_2[5] = tmp_out[2];
}


extern void func_8012F038(int param_1, short *param_2, short *param_3);

void func_801494CC(int param_1, short *param_2, short *param_3)
{
  short temp_out[3];
  short temp_in[3];

  temp_in[0] = param_2[1];
  temp_in[1] = param_2[3];
  temp_in[2] = param_2[5];

  func_8012F038(*(int *)(param_1 + 0x20) + 0x34, temp_in, temp_out);

  param_3[1] = temp_out[0];
  param_3[3] = temp_out[1];
  param_3[5] = temp_out[2];
}


extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012EF70(s32 a0, s32 a1);

void func_80149544(s32 a0, s32 a1, s32 a2)
{
    s32 buf[2];

    func_8012F14C(*(s32 *)(a0 + 0x20) + 0x34, a1, buf);
    func_8012EF70(buf, a2);
}


void func_8012F14C(s32 a0, s32 a1, s32 a2);
void func_8012EFB8(s32 a0);

void func_80149584(s32 a0, s32 a1, s32 a2)
{
    char local_10[8];

    func_8012F14C(*(s32*)((char*)a0 + 0x20) + 0x34, a1, (s32)local_10);
    ((void (*)(s32, s32))func_8012EFB8)((s32)local_10, a2);
}


extern void func_8014964C(s32 param_1, s32 param_2);

/* func_801495C4  (ov_SC01_077, 34 ins) — clone of the banked sibling func_8014964C.
 *
 * REGISTER-PIN-FREE byte-match (close=0). The sibling's engine_core.h macro pins
 * `register s32 p2 __asm__("$16")` to force a1->$s0; that pin is REMOVED here — once
 * the &buf CSE-hoist is broken, natural density allocation puts a1 in $s0 by itself
 * (a1: 7 refs / 21 insns crosses 2 calls; &buf pseudo out-densities it otherwise).
 *
 * Wall (pure-C, zero-asm): gcc-2.7.2 CSE commons the two identical stack-address
 * computations `&buf` (sp+0x20, passed to both calls) into ONE call-crossing pseudo,
 * which then wins $s0 over a1 (RC-2/K2 density) and spills a1 to $s1 (frame 0x30->0x38).
 * v1 (buf declared first, buf@sp+0x10) rematerializes &buf and matches everything but
 * the in/buf slot offsets; but correct slots REQUIRE `in,result,buf` decl order, which
 * puts buf@sp+0x20 and triggers the hoist. Every zero-asm CSE-break tried (2 pointer
 * vars, single ptr 2-set, struct, (char*)result+8, buf[z-z], a1&0, volatile ptr) is
 * folded/re-commoned by gcc. The two `m1/m2` reg-tie barriers below make the two &buf
 * opaque so each is materialized fresh (as the target does); `pin`/`mtx` barriers fix
 * the call-1 arg-materialization schedule order. These are __asm__ value-barriers, NOT
 * `register __asm__("$N")` pins.
 */
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012EF70(s32, s32);

void func_801495C4(s32 a0, s32 a1) {
    s16 in[4];
    s16 result[4];
    s16 buf[4];
    s16 *pin;
    s16 *m1;
    s16 *m2;
    s32 mtx;

    in[0] = *(u16 *)(a1 + 0x2);
    in[1] = *(u16 *)(a1 + 0x6);
    in[2] = *(u16 *)(a1 + 0xA);
    pin = in;                  __asm__ __volatile__("" : "=r"(pin) : "0"(pin));
    mtx = *(s32 *)(a0 + 0x20); __asm__ __volatile__("" : "=r"(mtx) : "0"(mtx));
    m1 = buf;                  __asm__ __volatile__("" : "=r"(m1) : "0"(m1));
    ((void (*)(s32, void *, void *))func_8012F14C)(mtx + 0x34, pin, m1);
    m2 = buf;                  __asm__ __volatile__("" : "=r"(m2) : "0"(m2));
    ((void (*)(void *, void *))func_8012EF70)(m2, result);
    *(s16 *)(a1 + 0x2) = result[0];
    *(s16 *)(a1 + 0x6) = result[1];
    *(s16 *)(a1 + 0xA) = result[2];
}


DEFINE_func_8014964C()  /* dedup: shared engine-core @0x8014964c (src/shared) */


DEFINE_func_801496D4()  /* dedup: shared engine-core @0x801496d4 (src/shared) */


DEFINE_func_80149704()  /* dedup: shared engine-core @0x80149704 (src/shared) */


DEFINE_func_80149724()  /* dedup: shared engine-core @0x80149724 (src/shared) */


DEFINE_func_80149744()  /* dedup: shared engine-core @0x80149744 (src/shared) */


DEFINE_func_80149788()  /* dedup: shared engine-core @0x80149788 (src/shared) */


DEFINE_func_801497A8()  /* dedup: shared engine-core @0x801497a8 (src/shared) */


DEFINE_func_80149864()  /* dedup: shared engine-core @0x80149864 (src/shared) */


DEFINE_func_80149884()  /* dedup: shared engine-core @0x80149884 (src/shared) */


DEFINE_func_801498C0()  /* dedup: shared engine-core @0x801498c0 (src/shared) */


DEFINE_func_801498E0()  /* dedup: shared engine-core @0x801498e0 (src/shared) */


/* callees (JSON-canonical, verbatim) */
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012E5CC(s32 param_1, u16 param_2, u16 param_3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80147364();
extern s32 func_800CCF28(s32 a0);
extern u16 *func_80146750(u16 *param_1);

/* data (JSON-canonical, verbatim) */
extern u8 D_80126B5C;
extern void *D_8012707C;

/* not in the JSON data list but required by the asm (%hi/%lo currentLocationId);
   type per src/shared/engine_core.h DEFINE_func_80149954() sibling macro (lh => s16) */
extern s16 currentLocationId;

s32 func_80149954(s32 s0)
{
    s32 sp10[2];
    s16 buf[10];

    if (*(s32 *)(s0 + 0x44) & 0x404) {
        return 0;
    }
    if ((*(u16 *)(s0 + 0xAA) & 0x90) == 0) {
        if (currentLocationId == 0x308D) {
            func_80015978((s32)&D_80126B5C, sp10);
            func_8012E5CC((s32)sp10, 0x4, 0x8E0);
            return 0;
        }
        func_8002D4C8(0x4, 0x8E0);
        return 0;
    }
    if (*(u16 *)(s0 + 0xAC) & 0x90) {
        if ((s32)D_8012707C == 0x8E0) {
            D_8012707C = 0;
        } else {
            func_80147364(0x8E0, 0);
        }
    }
    func_800CCF28(s0);
    *(s16 *)((s32)buf + 0x0) = 0x12;
    *(s32 *)((s32)buf + 0x8) = s0;
    *(s16 *)((s32)buf + 0x2) = 0;
    *(s16 *)((s32)buf + 0x4) = -0x1E;
    *(s16 *)((s32)buf + 0x6) = 0;
    *(s32 *)((s32)buf + 0xC) = 0;
    *(s32 *)((s32)buf + 0x10) = 0;
    func_80146750(buf);
    return 1;
}


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


extern void func_80144A04(s32 *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8016EDEC(s32, s32, s32);
s32 func_80149F2C(s32 a0, s32 a1)
{
    void *s1 = a0;
    s32 *s0;
    if (*(u16 *)a1 == 0x83 || *(u16 *)a1 == 0x61) {
        s0 = (s32 *)((s32 (*)())func_80144A04)((s32 *)a1);
        if (s0 != 0) {
            func_801599A4(s1);
            func_80159B3C(s1);
            ((void (*)(s32, s32))func_8016EDEC)((s32)s0, 0x1000000);
            return 1;
        }
    }
    return 0;
}


void func_80149FA8(void) {
}


// @class: regalloc-order
// @stuck: none — MATCH (38 ins)
extern s16 currentLocationId;

s32 func_80149FB0(s32 a0) {

    extern s32 D_801857C4[];
    extern u8 D_80078E78[];
    s32 *p = &D_801857C4[0];
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


extern u8 func_8014BEF8(void);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
extern void func_8014A1B0(s32 a0, s32 a1);
extern u8 D_801202A0[];

typedef struct {
    /* 0x00 */ s16 a30;
    /* 0x02 */ s16 a2e;
    /* 0x04 */ s16 a2c;
    /* 0x06 */ s16 pad06;
    /* 0x08 */ s32 buf[2];
    /* 0x10 */ s16 a20;
    /* 0x12 */ s16 a1e;
    /* 0x14 */ s16 a1c;
} Loc_8014A048;

s32 func_8014A048(s32 param_1) {
    Loc_8014A048 L;
    s32 s0;
    s32 s2;
    u32 s3;

    if ((*(u32 *)(param_1 + 0x44) & 0x400) != 0) {
        return 0;
    }
    if ((*(u16 *)(param_1 + 0xAC) & 0x80) == 0) {
        if ((*(u16 *)(param_1 + 0xAC) & 0x10) == 0) {
            return 0;
        }
        if (((s32 (*)(s32))func_8014BEF8)(param_1) == 0) {
            goto ret0;
        }
    }
    L.a30 = *(s16 *)(param_1 + 6);
    L.a2e = *(s16 *)(param_1 + 0xA);
    L.a2c = *(s16 *)(param_1 + 0xE);
    L.a1e = -0x10;
    L.a20 = 0;
    L.a1c = -0x20;
    func_8012F14C(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&L.a20, (s32)L.buf);
    s3 = 0;
    s2 = 0;
    while (1) {
        s0 = (s32)D_801202A0 + s2;
        __asm__ __volatile__("" : "=r"(s0) : "0"(s0));
        if ((*(u16 *)s0 != 0) &&
            (*(s32 *)(s0 + 0x58) != 0) &&
            (*(s16 *)(s0 + 0xAA) == 0) &&
            (*(s32 *)(param_1 + 0x184) != s0) &&
            ((*(u16 *)(s0 + 0x5C) & 0x200) != 0) &&
            (func_80135260(*(s32 *)(s0 + 0x20), *(s32 *)(s0 + 0x58), &L.a30, (s16 *)L.buf) != 0)) {
            break;
        }
        s3++;
        s2 += 0x10C;
        if (s3 >= 0x60) {
            return 0;
        }
    }
    *(s32 *)(param_1 + 0x178) = s0;
    func_8014A1B0(param_1, s0);
    return 1;
ret0:
    return 0;
}


DEFINE_func_8014A1B0()  /* dedup: shared engine-core @0x8014a1b0 (src/shared) */


DEFINE_func_8014A218()  /* dedup: shared engine-core @0x8014a218 (src/shared) */


DEFINE_func_8014A238()  /* dedup: shared engine-core @0x8014a238 (src/shared) */


DEFINE_func_8014A2E4()  /* dedup: shared engine-core @0x8014a2e4 (src/shared) */


DEFINE_func_8014A380()  /* dedup: shared engine-core @0x8014a380 (src/shared) */


DEFINE_func_8014A3E0()  /* dedup: shared engine-core @0x8014a3e0 (src/shared) */


DEFINE_func_8014A454()  /* dedup: shared engine-core @0x8014a454 (src/shared) */


DEFINE_func_8014A4B4()  /* dedup: shared engine-core @0x8014a4b4 (src/shared) */


DEFINE_func_8014A4FC()  /* dedup: shared engine-core @0x8014a4fc (src/shared) */


DEFINE_func_8014A51C()  /* dedup: shared engine-core @0x8014a51c (src/shared) */


DEFINE_func_8014A59C()  /* dedup: shared engine-core @0x8014a59c (src/shared) */


DEFINE_func_8014A638()  /* dedup: shared engine-core @0x8014a638 (src/shared) */


DEFINE_func_8014A674()  /* dedup: shared engine-core @0x8014a674 (src/shared) */


DEFINE_func_8014A680()  /* dedup: shared engine-core @0x8014a680 (src/shared) */


DEFINE_func_8014A69C()  /* dedup: shared engine-core @0x8014a69c (src/shared) */


DEFINE_func_8014A6A8()  /* dedup: shared engine-core @0x8014a6a8 (src/shared) */


DEFINE_func_8014A6C4()  /* dedup: shared engine-core @0x8014a6c4 (src/shared) */


DEFINE_func_8014A71C()  /* dedup: shared engine-core @0x8014a71c (src/shared) */


  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_8014A738;








extern s32 func_80029178(s32);

s32 func_8014A738(void *arg0) {
    Vec_8014A738 d;
    u32 i;
    Ent_801202A0 *base;

    if ((func_80029178(0x83) & 0xFF) == 0) {
        return 0;
    }
    base = (Ent_801202A0 *)D_801202A0;
    for (i = 0; i < 0x60; i++) {
        if (base[i].state == 7) {
            d.vx = ((Ent_801202A0 *)arg0)->x - base[i].x;
            d.vz = ((Ent_801202A0 *)arg0)->z - base[i].z;
            if (d.vx >= 0) {
                if (d.vx < 0x40) {
                    goto zcheck;
                }
            } else {
                if (-d.vx < 0x40) {
                    goto zcheck;
                }
            }
            continue;
        zcheck:
            if (d.vz >= 0) {
                if (d.vz < 0x40) {
                    goto found;
                }
            } else {
                if (-d.vz < 0x40) {
                    goto found;
                }
            }
            continue;
        found:
            return 1;
        }
    }
    return 0;
}


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


DEFINE_func_8014ADE0()  /* dedup: shared engine-core @0x8014ade0 (src/shared) */


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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8014C1A0);

DEFINE_func_8014C1C8()  /* dedup: shared engine-core @0x8014c1c8 (src/shared) */


DEFINE_func_8014C278()  /* dedup: shared engine-core @0x8014c278 (src/shared) */


DEFINE_func_8014C2B0()  /* dedup: shared engine-core @0x8014c2b0 (src/shared) */


DEFINE_func_8014C308()  /* dedup: shared engine-core @0x8014c308 (src/shared) */


DEFINE_func_8014C3A4()  /* dedup: shared engine-core @0x8014c3a4 (src/shared) */


DEFINE_func_8014C3D0()  /* dedup: shared engine-core @0x8014c3d0 (src/shared) */


DEFINE_func_8014C43C()  /* dedup: shared engine-core @0x8014c43c (src/shared) */



/* §37/§73/§124 asm-label alias: the fleet canon declares this `extern void` (engine_core.h, inside 8
 * DEFINE_func_* macros); the byte-true body must return s32.  Aliasing the C name sidesteps the
 * RETURN-axis conflict with no header edit.  This line MUST travel with the body. */
s32 aF8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4) __asm__("func_8014C4AC");

s32 aF8014C4AC(a0, a1, a2, a3, a4)
s32 a0;
s32 a1;
s32 a2;
s16 *a3;
u16 a4;
{
   /* block-scope: no file-scope conflict (§100) */
    extern s32 D_80126CD0;
    extern u16 D_8012693A;
    extern u16 D_801152B8;
    u16 t;

    if (a0 == 0) {
        return 0;
    }
    if (*(u16 *)a0 == 0) {
        return 0;
    }
    if (a1 == 9 || a1 == 0x11 || a1 == 0x29 || a1 == 0xA || D_80126CD0 != a0) {
        t = *(u16 *)(a0 + 0x5C);
        *(u16 *)(a0 + 0x5E) = a1;
        *(u16 *)(a0 + 0x62) = a4;
        *(u16 *)(a0 + 0x60) = a2;
        *(u16 *)(a0 + 0x5C) = t | 1;
        *(V4U *)(a0 + 0x7C) = *(V4U *)a3;
        *(u8 *)(a0 + 0xC9) = D_8012693A;
        *(u8 *)(a0 + 0xC8) = D_801152B8;
        return a0;
    }
    return 0;
}


DEFINE_func_8014C568()  /* dedup: shared engine-core @0x8014c568 (src/shared) */


DEFINE_func_8014C59C()  /* dedup: shared engine-core @0x8014c59c (src/shared) */



extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);

s16 func_8014C5D0(s32 a0, s32 a1) {

    extern u8 D_80185854;
    return func_8014C5FC(a0, a1, &D_80185854);
}


DEFINE_func_8014C5FC()  /* dedup: shared engine-core @0x8014c5fc (src/shared) */


DEFINE_func_8014C6AC()  /* dedup: shared engine-core @0x8014c6ac (src/shared) */


DEFINE_func_8014C6C0()  /* dedup: shared engine-core @0x8014c6c0 (src/shared) */


DEFINE_func_8014C6D0()  /* dedup: shared engine-core @0x8014c6d0 (src/shared) */


DEFINE_func_8014C6E0()  /* dedup: shared engine-core @0x8014c6e0 (src/shared) */





// @class: schedule
// @stuck: none — MATCH (match_one 91/91)
//
// Levers used (all byte-gated on ov_SC07_006):
//  1. §struct  8-byte alignment-1 struct copy `*(M8_8014C6F4*)(a+0x164) = *(M8_8014C6F4*)(p+0x10)`
//     -> the lwl/lwr,lwl/lwr,swl/swr,swl/swr block (engine_types.h M8_xxx convention).
//  2. §17 base-pointer cache: `u8 *p = D_80078E78;` (NOT a direct D_80078E78[0x49]) so gcc pins
//     the base into callee-saved $s1 and hoists the la into the prologue (live across the jal).
//  3. §17 register pins: the search result `e` MUST be $v0 and the limit `lim` $v1, else
//     local-alloc swaps the loop IV/limit pair ($v1<->$a0) and coalesces `e` into the IV.
//  4. DELAY-SLOT lever (new): writing the compare constant as its own pre-loop statement
//     (`want = 0x22;`) instead of the literal `0x22` inside the loop test. With the literal,
//     loop.c hoists the `li $a1,0x22` into the loop PREHEADER (after the duplicated entry test),
//     so reorg.c's guard branch has nothing local to take and instead COPIES the branch-target
//     insn (`addu $v0,$zero,$zero`) into its delay slot and redirects past it — a +1 shift that
//     also lets the loop-back branch steal the same insn (nop -> move). Materialising the
//     constant in the block BEFORE the entry test makes fill_simple_delay_slots take it from
//     the preceding insns, reproducing `beqz $v0,.L8014C7F4 / addiu $a1,$zero,0x22` and leaving
//     the loop-back delay slot a nop. `want` needs no pin — gcc lands it in $a1 on its own.


DEFINE_func_8014C6F4()  /* dedup: shared engine-core @0x8014C6F4 (src/shared) */


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


extern u16 D_80126CC4;

void func_8014CBE8(void)
{
    (*(s16 *)&D_80126CC4) = 0;
}


DEFINE_func_8014CBF8()  /* dedup: shared engine-core @0x8014cbf8 (src/shared) */


DEFINE_func_8014CC28()  /* dedup: shared engine-core @0x8014cc28 (src/shared) */



extern void func_8014CD0C(u8 *a0);

void func_8014CCB4(void)
{
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
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014CD0C()  /* dedup: shared engine-core @0x8014cd0c (src/shared) */


DEFINE_func_8014CD80()  /* dedup: shared engine-core @0x8014cd80 (src/shared) */


DEFINE_func_8014CF04()  /* dedup: shared engine-core @0x8014CF04 (src/shared) */



extern void func_8014D0A4(s32);

void func_8014D04C(void)
{
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
        "jal   func_8014D0A4\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014D0A4()  /* dedup: shared engine-core @0x8014d0a4 (src/shared) */




DEFINE_func_8014D12C()  /* dedup: shared engine-core @0x8014D12C (src/shared) */



DEFINE_func_8014D2A0()  /* dedup: shared engine-core @0x8014D2A0 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8014D3E0);

DEFINE_func_8014D438()  /* dedup: shared engine-core @0x8014d438 (src/shared) */


DEFINE_func_8014D4C0()  /* dedup: shared engine-core @0x8014d4c0 (src/shared) */


extern u8 D_801202A0[];
extern u8 D_80126720[];

s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
s32 func_8014C918(s32 a0, s32 a1);

s32 func_8014D610(s32 a0, s32 a1, u16* a2)
{
    u8 *s1, *s0;
    s32 result;

    s1 = D_801202A0;

    if (!(s1 < D_801202A0 + 0x6480)) {
        return 0;
    }

    s0 = s1 + 0x75;

    while (1) {
        if (*(u16*)s1 == 0) {
            goto next_iter;
        }

        if ((*(u16*)(s0 - 0x19) & 0x400) == 0) {
            goto next_iter;
        }

        if (*(s32*)(s0 - 0x1D) == 0) {
            goto next_iter;
        }

        if (*(s16*)(s0 - 0x6B) < *(s16*)(a0 + 10)) {
            goto next_iter;
        }

        result = func_80135A4C(*(s32*)(s0 - 0x55), *(s32*)(s0 - 0x1D), a1, (s32)a2);

        if (result == 0) {
            goto next_iter;
        }

        *(u8**)(a0 + 0x174) = s1;
        *(u8*)(s0 - 1) = 1;

        *(u16*)(a0 + 6) = a2[0];
        *(u16*)(a0 + 10) = a2[1];
        *(u16*)(a0 + 14) = a2[2];

        result = func_8014C918((s32)a0, *(u8*)s0);

        *(u16*)(a0 + 0x16E) = result & 0xFF;

        return 1;

    next_iter:
        s1 = s1 + 0x10C;
        s0 = s0 + 0x10C;

        if (!(s1 < D_80126720)) {
            return 0;
        }
    }
}



extern void func_8014D790(s32);

void func_8014D738(void)
{
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
        "jal   func_8014D790\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014D790()  /* dedup: shared engine-core @0x8014d790 (src/shared) */


  typedef struct EntD820_8014D820
  {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 x;
    u16 f8;
    u16 y;
    u16 fC;
    u16 z;
    u8 p10[0x10];
    s32 f20;
    u8 p24[0x34];
    s32 f58;
    u16 f5C;
    u16 f5E;
    u8 p60[0x10C - 0x60];
  } Ent_8014D820;
  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_8014D820;

// @class: schedule
// @stuck: none — MATCH (304/304), symcheck SYMS-OK 12/12, and the whole-TU cc1 stage now compiles CLEAN
//
// ══════════════════════════════════════════════════════════════════════════════
// SESSION-22 RE-DERIVATION + THE ROOT-CAUSE FIX FOR THE "ASSEMBLER-STAGE" FAILURE
// ══════════════════════════════════════════════════════════════════════════════
// The SESSION-21 draft did reach match_one MATCH (re-verified this session, 304/304)
// and symcheck SYMS-OK — but the whole-binary build died with an opaque `Error 33`
// that was logged as "an ASSEMBLER-stage failure I did not finish diagnosing".
//
// IT IS NOT AN ASSEMBLER FAILURE. Stage-by-stage isolation of the real pipeline
// (cpp | cc1 | maspsx | as) over a scratch copy of src/ov_SC01_077/ov_SC01_077_after.c
// with this function spliced in place of its INCLUDE_ASM gives:
//     cpp    rc=0
//     cc1    rc=33   <-- ".../tu.c:1901: conflicting types for `Ent_8014D820'"
//                        "src/shared/engine_types.h:434: previous declaration of `Ent_8014D820'"
//     maspsx rc=0
//     as     rc=0    (only benign "used $at without .set noat" warnings)
// `33` is CC1's exit code, surfaced by the recipe's `set -o pipefail` (Makefile:560).
// Because `as` is the LAST stage in that pipe, make attributes the failure to the
// assembler — the same misread that made func_8012AAAC's "opaque Error 33" look
// assembler-shaped until it was isolated stage by stage.
//
// ROOT CAUSE: the draft declared `typedef struct Ent_8014D820 { ... } Ent_8014D820;` at FILE scope.
// `Ent_8014D820` is already a shared engine type (src/shared/engine_types.h:434,
//   typedef struct { u16 guard; u16 pad; u16 field; u8 rest[14]; } Ent_8014D820;
// a 20-byte struct), pulled into every overlay TU through
// src/ov_SC01_077/../shared/engine_core.h. gcc-2.7.2 rejects the redefinition
// outright (an ERROR, not the "type mismatch with previous external decl"
// WARNING that the rest of this TU is full of), so cc1 aborts.
//
// THE FIX, and why this shape: all three helper types are now declared at BLOCK
// scope inside func_8014D820 itself. That is strictly better than renaming to
// `Ent_8014D820` at file scope, because this function is an h_seq family EXEMPLAR
// with 138 members: a file-scope type name has to stay unique against 138 distinct
// overlay TUs *and* against whatever engine_types.h grows next, while a block-scope
// typedef can never collide with anything, in any TU, ever. It also matches the
// fleet convention — src/shared/engine_core.h contains ZERO `typedef struct`
// (all 0 of them); every DEFINE_ macro body uses engine_types.h types or local ones.
// Typedefs emit no code and create no allocno, so the move is byte-neutral:
// re-verified MATCH (304 ins) after the change, and the local DECLARATION ORDER
// below is untouched (§76 — declaration order is the dominant regalloc lever here).
//
// ══════════════════════════════════════════════════════════════════════════════
// THE BODY (SESSION-21 derivation, each lever re-verified this session)
// ══════════════════════════════════════════════════════════════════════════════
// func_8014D820 (304 ins, ov_SC01_077, h_seq family exemplar, 138 members).
// The whole residual off the SESSION-18 close=9 seed was a sched1 PERMUTATION
// inside ONE basic block (idx 79..101, the pos/desc set-up between the `slti 0x400`
// guard and the `currentLocationId` test): identical multiset of insns, identical
// register assignment, wrong positions. §66d-5 exactly — classed WIDTH [structural]
// at every waypoint and not structural at all.
//
// The lever (reusable): that block is 12 statements over a small dependency poset
// (load x0/y0/z0 -> add -> store pos.* / desc.*), so source ORDER is the only
// control and the space of linear extensions is enumerable. A dependency-respecting
// sweep found MATCH at
//   x0; pos.x; y0; pos.y; z0; tx; pos.z; tz; desc.x; desc.z; ty; desc.y
// i.e. all three loads and both pos stores first, then the two adds, then the desc
// stores, with the y accumulator (`ty`) computed LAST. No pin, no barrier, no
// permuter run. Eleven hand attempts on this window (SESSION-18) were inert or
// worse — hand-reading a 12-statement schedule permutation is the wrong tool;
// brute-forcing the linear extensions is the right one.
//
// Load-bearing levers (each re-verified by removal this session):
//   * the `a0v` launder (`__asm__("" : "=r"(a0v) : "0"(a0))`) — drop => 9 mismatched
//   * the `a2` $7 pin                                         — drop => 5
//   * the `a2x -> a2` launder (vs a plain copy)               — drop => 1
//   * `new_var3` (the s16 stash of dx feeding ratan2)         — drop => 2
//   * `new_var2` (the desc.y + 0x10 accumulator)              — drop => 2
// The `a2` pin's live range ENDS before the first `jal` (last use is
// `desc.z = a2[2] - a1[2]`), so it is §42e-CORRECTION / §74-safe to propagate.
//
// SYMBOLS (§58 rule 1/2): all five data externs use the canonical splat spelling and
// the engine_core.h type — `u8 D_801202A0[]`, `u8 D_801152A8[]`, `s16 D_801152AC`,
// `u8 D_8018585C[]`, `s16 currentLocationId`. symcheck: SYMS-OK, 12 symbols agree.
//
// The one deliberate divergence (§27 step 2 / rule 3): func_80135A4C's canonical
// extern is 4-arg but this call site sets only $a0-$a2, so the canonical decl is
// kept verbatim (it is also the TU's own spelling at ov_SC01_077_after.c:1651/1709)
// and the ARITY is cast at the call site.
//
// BANKING NOTE for the orchestrator (carried forward from SESSION-18, still true):
// 1 `self_decl_hdr` axis remains — DEFINE_func_8014D790's body declares
// func_8014D820, so that macro in engine_core.h needs the §85 return-axis widen
// (already applied). With the `Ent_8014D820` collision gone the TU's cc1 stage is clean.










extern s16 currentLocationId;
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014DCE0(s32 a0, s32 a1, s32 a2);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
s32 func_8014D820(s32 a0, u16 *a1, u16 *a2x)
{

    extern u8 D_801202A0[];
    extern u8 D_8018585C[];
    extern u8 D_801152A8[];
    extern s16 D_801152AC;
  /* BLOCK-SCOPE types — see the header note. `Ent_8014D820` at file scope collides with
     src/shared/engine_types.h:434 and kills the TU's cc1 stage (exit 33). */
  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_8014D820;
  typedef struct EntD820_8014D820
  {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 x;
    u16 f8;
    u16 y;
    u16 fC;
    u16 z;
    u8 p10[0x10];
    s32 f20;
    u8 p24[0x34];
    s32 f58;
    u16 f5C;
    u16 f5E;
    u8 p60[0x10C - 0x60];
  } Ent_8014D820;
  int new_var2;
  s16 new_var3;
register u16 *a2 __asm__("$7");
  V4_8014D820 out[3];
  V4_8014D820 pos;
  Desc desc;
  Ent_8014D820 *ent;
  Ent_8014D820 *p;
  s32 dx;
  s32 dz;
  s32 ex;
  s32 ez;
  s32 r1;
  s32 r2;
  s32 r3;
  s32 ang;
  s32 x0;
  s32 y0;
  s32 z0;
  s32 tx;
  s32 tz;
  s32 ty;
  s32 r;
  s32 t;
  s32 u;
  s32 a0v;
__asm__ __volatile__("" : "=r"(a2) : "0"(a2x));
  t = a2[0];
  u = a1[0];
  dx = t - u;
__asm__ __volatile__("" : "=r"(a0v) : "0"(a0));
  new_var3 = (s16) dx;
  t = a2[2];
  u = a1[2];
  dz = t - u;
  if (((s16) (dx | dz)) == 0)
  {
    goto fail;
  }
  desc.x = dx;
  desc.y = a2[1] - a1[1];
  desc.z = a2[2] - a1[2];
  ent = *((Ent_8014D820 **) (a0v + 0x170));
  if (ent->f0 == 0)
  {
    goto fail;
  }
  if ((ent->f5C & 0x1000) == 0)
  {
    goto fail;
  }
  if (ent->f58 == 0)
  {
    goto fail;
  }
  if (((s32 (*)(s32, s32, s32)) func_80135A4C)(ent->f20, ent->f58, (s32) a1) == 0)
  {
    goto fail;
  }
  ex = ent->x - (*((u16 *) (a0v + 6)));
  ez = ent->z - (*((u16 *) (a0v + 0xE)));
  r1 = (s16) ratan2((s16) dz, new_var3);
  r2 = (s16) ratan2((s16) ez, (s16) ex);
  r3 = (s16) func_80012A60(r1, r2);
  if (0x400 <= r3)
  {
    goto fail;
  }
  desc.f20 = 0;
  desc.f1C = 0;
  desc.f18 = 0;
  x0 = ent->x;
  pos.x = x0;
  y0 = ent->y;
  pos.y = y0;
  z0 = ent->z;
  tx = x0 + desc.x;
  pos.z = z0;
  tz = z0 + desc.z;
  desc.x = tx;
  desc.z = tz;
  ty = (y0 + desc.y) + 8;
  desc.y = ty;
  if (currentLocationId != 0x3008)
  {
    for (p = (Ent_8014D820 *) D_801202A0; p < (Ent_8014D820 *) (D_801202A0 + 0x6480); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->f0 == 0)
      {
        continue;
      }
      if (p->f5C == 0)
      {
        continue;
      }
      if (p->f58 == 0)
      {
        continue;
      }
      func_80135888(p->f20, p->f58, (s32) (&pos), (s32) (&desc));
    }

  }
  else
  {
    ang = ratan2(((s16) x0) - ((s16) tx), ((s16) z0) - ((s16) tz)) & 0xFFF;
    func_800139C8(ang, D_8018585C, &out[0]);
    func_800139C8((s16) (ang - 0x155), D_8018585C, &out[1]);
    func_800139C8((s16) (ang + 0x155), D_8018585C, &out[2]);
    out[0].x += pos.x;
    out[0].y = pos.y;
    out[0].z += pos.z;
    out[1].x += pos.x;
    out[1].y = pos.y;
    out[1].z += pos.z;
    out[2].x += pos.x;
    out[2].y = pos.y;
    out[2].z += pos.z;
    for (p = (Ent_8014D820 *) D_801202A0; p < (Ent_8014D820 *) (D_801202A0 + 0x6480); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->f0 == 0)
      {
        continue;
      }
      if (p->f5C == 0)
      {
        continue;
      }
      if (p->f58 == 0)
      {
        continue;
      }
      if (func_8014DCE0((s32) p, (s32) (&pos), (s32) (&out[0])) != 0)
      {
        __builtin_memcpy((void *) ((s32) (&desc)), (void *) ((s32) (&pos)), 8);
      }
    }

  }
  r = func_80133784(0, &pos, (s32) (&desc));
  if ((r == 0) || ((r == 0x2000) && (((*(u16 *) D_801152A8) | ((u16) D_801152AC)) == 0)))
  {
    ent->x = desc.x - desc.f18;
    ent->y = desc.y;
    ent->z = desc.z - desc.f20;
    desc.x -= pos.x;
    desc.y -= pos.y;
    desc.z -= pos.z;
    *((u16 *) (a0v + 6)) = a1[0] + desc.x;
    new_var2 = desc.y;
    new_var2 = new_var2 + 0x10;
    *((u16 *) (a0v + 0xA)) = a1[1] + new_var2;
    *((u16 *) (a0v + 0xE)) = a1[2] + desc.z;
  }
  else
  {
    *((u16 *) (a0v + 6)) = a1[0];
    *((u16 *) (a0v + 0xA)) = a1[1] + 0x10;
    *((u16 *) (a0v + 0xE)) = a1[2];
  }
  return 1;
  fail:
  *((s32 *) (a0v + 0x170)) = 0;

  return 0;
}


DEFINE_func_8014DCE0()  /* dedup: shared engine-core @0x8014dce0 (src/shared) */


DEFINE_func_8014DD8C()  /* dedup: shared engine-core @0x8014dd8c (src/shared) */



extern void func_8014DF94(s32);

void func_8014DF3C(void)
{
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
        "jal   func_8014DF94\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014DF94()  /* dedup: shared engine-core @0x8014df94 (src/shared) */


DEFINE_func_8014E048()  /* dedup: shared engine-core @0x8014e048 (src/shared) */


DEFINE_func_8014E284()  /* dedup: shared engine-core @0x8014e284 (src/shared) */



extern void func_8014E48C(s32);

void func_8014E434(void)
{
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
        "jal   func_8014E48C\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014E48C()  /* dedup: shared engine-core @0x8014e48c (src/shared) */


DEFINE_func_8014E514()  /* dedup: shared engine-core @0x8014e514 (src/shared) */


extern s32 func_8014CF04(s32 a0, s32 a1, void *a2);
extern s32 func_8014D2A0(s32 arg0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
//
// The return type is LOAD-BEARING here (see DECAY note below), so `void` is not an option.
// Fix = the §37/§124 ASM-LABEL ALIAS, the same lever that banked func_8014C4AC today
// (.run/sweep/*/func_8014C4AC.c): define the body under the C name aF8014E5B4 carrying
// __asm__("func_8014E5B4"). The emitted symbol is unchanged, the C identifier never collides
// with the macro's extern, and NO tracked header edit is needed — the engine_core.h:13392
// §85 return-axis widen described in the old banking note is now UNNECESSARY.
// Byte-checked: match_one MATCH (0 mismatches) before and after the rename.
// The alias line MUST travel with the body to every sibling overlay.
//
// DECAY FIX (2026-08-01, REDRAFT lane) — why the return type cannot be `void`: with `void`,
// gcc-2.7.2 drops the value axis entirely: no `addiu $v0,$zero,0x1`, no `addu $v0,$zero,$zero`
// at .L8014E674, and the `j .L8014E678` merge disappears (the taken path falls straight into
// the shared epilogue), which also frees $v0 so the last `lhu` lands in $v0 instead of the
// target's $v1. `s32` fixes all 23 mismatches at once.
//
// Keys (same D_801202A0 96-entry / stride-0x10C sweep as the func_8014CF04 and func_8014D2A0
// siblings, so most of it is the already-banked idiom):
//
//  (1) LOOP-BOUND DUALITY, register-relative BOTH ends (differs from func_8014CF04!). The
//      target computes `addiu $v1,$s1,0x6480` for the ENTRY guard and then a separate
//      `addu $s5,$v1,$zero` AFTER the guard branch for the loop-carried bound. That extra
//      copy is 1 whole instruction: the plain `e = p + 0x6480; if (p < e)` spelling folds it
//      away and compiles to 58 ins. The spelling that reproduces it is
//        `if (p < p + 0x6480) { e = p + 0x6480; ... }`
//      — the guard makes $v1, CSE turns the in-body `e = p + 0x6480` into a copy of it, and
//      regalloc does not coalesce (gcc-2.7.2 has no coalescing, regalloc.md K8). The back edge
//      then uses the register ($s5), NOT a rematerialised %hi/%lo(D_80126720) as in
//      func_8014CF04 — so do NOT reuse that sibling's absolute-bound half here.
//
//  (2) TWO INDUCTION VARIABLES, secondary base +0xE. `q = p + 0xE` carries every access except
//      the two that use the entry pointer itself (`*(u16 *)p` and `*(u8 **)(a0+0x17C) = p`):
//      offsets -0x8 / 0x0 / 0x12 / 0x4A / 0x4E off q  ==  0x6 / 0xE / 0x20 / 0x58 / 0x5C off p.
//      A single-pointer spelling is NOT equivalent: gcc emits ONE base and the function comes
//      out 56 ins (verified). The negative displacement is the tell that the second pointer is
//      in the source, not a compiler-made giv.
//
//  (3) REGISTER PINS ($16/$17) — the one non-obvious lever, and it is a genuine density
//      knife-edge (regalloc.md K2 / §RC-15). Unpinned, the .lreg reads
//        p:  9 refs / 24 insns -> floor_log2(9)*9/24 = 1.125
//        q:  8 refs / 22 insns -> floor_log2(8)*8/22 = 1.091
//      so p wins $s0 by ~3% and the whole function comes out with p/q SWAPPED (17 mismatches,
//      every one of them a bare $s0<->$s1 rename). The target wants q in $s0. Decl-order swap
//      does nothing (ties are not what decides it — p genuinely out-scores q). Rather than
//      hunt a +1-ref anchor (§RC-11 `#APP` would sit next to three delay slots that maspsx
//      fills: the `beqz $a1` slot, the `jal` slot and the `bnez` slot), pin both:
//        register u8 *p __asm__("$17");  register u8 *q __asm__("$16");
//      Both are callee-saved, so the live-across-`jal` range is §42e/§74-safe by construction
//      (the ov_SC03_099 func_8014D820 caveat only applies to caller-saved pins). Everything
//      else falls out naturally: a0->$s2, a1->$s3, a2->$s4, e->$s5.
//
//  (4) `t = *(s32 *)(q + 0x4A)` is loaded ONCE and reused as arg1 of func_80135888 — that is
//      why `lw $a1, 0x4A($s0)` sits at the zero-test rather than at the call.
//
// The func_80135888 decl below is byte-compatible with the one this TU already carries at
// ov_SC01_077_after.c:2303, so it is not a second conflict axis.

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);

/* §37/§124 asm-label alias: the fleet canon declares this `extern void` (engine_core.h:13392,
 * inside DEFINE_func_8014E48C()); the byte-true body must return s32. Aliasing the C name
 * sidesteps the RETURN-axis conflict with no header edit. This line MUST travel with the body. */
s32 aF8014E5B4(s32 a0, void *a1, void *a2) __asm__("func_8014E5B4");

s32 aF8014E5B4(s32 a0, void *a1, void *a2)
{

    register u8 *p __asm__("$17");
    register u8 *q __asm__("$16");
    u8 *e;
    s32 t;

    p = D_801202A0;
    if (p < p + 0x6480) {
        e = p + 0x6480;
        q = p + 0xE;
    loop:
        if (*(u16 *)p != 0) {
            if ((*(u16 *)(q + 0x4E) & 0x40) != 0) {
                t = *(s32 *)(q + 0x4A);
                if (t != 0) {
                    if (func_80135888(*(s32 *)(q + 0x12), t, (s32)a1, (s32)a2) != 0) {
                        *(u8 **)(a0 + 0x17C) = p;
                        *(u16 *)(a0 + 6) = *(u16 *)(q - 8);
                        *(u16 *)(a0 + 0xE) = *(u16 *)q;
                        return 1;
                    }
                }
            }
        }
        p += 0x10C;
        q += 0x10C;
        if (p < e) {
            goto loop;
        }
    }
    return 0;
}



extern void func_8014E6F8(struct SubE6F8*);

void func_8014E6A0(void)
{
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
        "jal   func_8014E6F8\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014E6F8()  /* dedup: shared engine-core @0x8014e6f8 (src/shared) */


DEFINE_func_8014E790()  /* dedup: shared engine-core @0x8014e790 (src/shared) */


DEFINE_func_8014E83C()  /* dedup: shared engine-core @0x8014e83c (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8014E934);

DEFINE_func_8014E98C()  /* dedup: shared engine-core @0x8014e98c (src/shared) */


DEFINE_func_8014EA4C()  /* dedup: shared engine-core @0x8014ea4c (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8014ED28);

DEFINE_func_8014ED80()  /* dedup: shared engine-core @0x8014ed80 (src/shared) */


DEFINE_func_8014EE14()  /* dedup: shared engine-core @0x8014ee14 (src/shared) */



extern s32 func_8014F24C(struct SubF24C*);

void func_8014F1F4(void)
{
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
        "jal   func_8014F24C\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014F24C()  /* dedup: shared engine-core @0x8014f24c (src/shared) */


DEFINE_func_8014F2E0()  /* dedup: shared engine-core @0x8014f2e0 (src/shared) */


DEFINE_func_8014F3E8()  /* dedup: shared engine-core @0x8014f3e8 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8014F468);

DEFINE_func_8014F4C0()  /* dedup: shared engine-core @0x8014f4c0 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8014F6F4);

DEFINE_func_8014F74C()  /* dedup: shared engine-core @0x8014f74c (src/shared) */



// @class: other
// @stuck: none — MATCH (full inline-asm $sp-switch trampoline w/ 0x40000 guard, jal func_8014FA70, stash D_801C8544; maspsx auto-fills jal delay slot)

extern s32 func_8014FA70(s32 a0);

void func_8014FA04(s32 a0)
{

    extern s32 D_801C8544;
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
        "lui   $at, %%hi(D_801C8544)\n"
        "sw    $v0, %%lo(D_801C8544)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8544)\n"
        "lw    $v0, %%lo(D_801C8544)($v0)\n"
        "1:\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014FA70()  /* dedup: shared engine-core @0x8014fa70 (src/shared) */



extern s32 func_8014FC18(u8*);

void func_8014FBC0(void)
{
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
        "jal   func_8014FC18\n"
        "lui   $at, %%hi(D_801C8544)\n"
        "sw    $v0, %%lo(D_801C8544)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8544)\n"
        "lw    $v0, %%lo(D_801C8544)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014FC18()  /* dedup: shared engine-core @0x8014fc18 (src/shared) */



extern int func_8014FD54(int);

void func_8014FCFC(void)
{
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
        "jal   func_8014FD54\n"
        "lui   $at, %%hi(D_801C8540)\n"
        "sw    $v0, %%lo(D_801C8540)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801C8540)\n"
        "lw    $v0, %%lo(D_801C8540)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014FD54()  /* dedup: shared engine-core @0x8014fd54 (src/shared) */


DEFINE_func_8014FDF4()  /* dedup: shared engine-core @0x8014fdf4 (src/shared) */



DEFINE_func_8014FE60()  /* dedup: shared engine-core @0x8014FE60 (src/shared) */


DEFINE_func_8014FFDC()  /* dedup: shared engine-core @0x8014ffdc (src/shared) */


DEFINE_func_80150150()  /* dedup: shared engine-core @0x80150150 (src/shared) */


DEFINE_func_80150170()  /* dedup: shared engine-core @0x80150170 (src/shared) */


DEFINE_func_801502EC()  /* dedup: shared engine-core @0x801502ec (src/shared) */


DEFINE_func_80150460()  /* dedup: shared engine-core @0x80150460 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80150480);

DEFINE_func_801504D8()  /* dedup: shared engine-core @0x801504d8 (src/shared) */


DEFINE_func_80150528()  /* dedup: shared engine-core @0x80150528 (src/shared) */


DEFINE_func_801505FC()  /* dedup: shared engine-core @0x801505fc (src/shared) */


extern void func_80147324(s32 a0);
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
extern void func_8014ADA8(s32 a0, s32 a1);
extern void func_8014BB24(s32 a0, s32 a1, s32 a2);



s32 func_801506A4(s32 arg0, s32 arg1) {

    extern u16 aD80078EB4 __asm__("D_80078EB4");
    extern void func_80150820(s32, s32);
    extern void func_8015086C(int);
    extern unsigned short D_8018586C[];
    extern unsigned short D_80185874[];
    extern unsigned short D_8018587C[];

    int mode;

    mode = ((struct Ent_801506A4 *)arg1)->unk0;
    ((struct Ent_801506A4 *)arg1)->unk5C |= 1;
    switch (mode) {
    case 0x31:
        ((void(*)(int))func_80147324)(0x452);
        ((void(*)(int, unsigned))func_8014ADA8)(((int)arg0), D_8018586C[((struct Ent_801506A4 *)arg1)->unk70]);
        ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 3, D_8018586C[((struct Ent_801506A4 *)arg1)->unk70]);
        break;
    case 0x32:
        if ((*(unsigned short*)&aD80078EB4) != 0) {
            ((void(*)(int))func_80147324)(0x452);
            ((void(*)(int, unsigned, int))func_8014BB24)(((int)arg0), D_80185874[((struct Ent_801506A4 *)arg1)->unk70], 1);
            ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 2, D_80185874[((struct Ent_801506A4 *)arg1)->unk70]);
        }
        break;
    case 0x33:
        ((void(*)(int))func_80147324)(0x452);
        ((void (*)(int, unsigned))func_80150820)(((int)arg0), D_8018587C[((struct Ent_801506A4 *)arg1)->unk70]);
        break;
    case 0xC5:
    case 0x27B:
        ((void(*)(int))func_80147324)(0x452);
        func_8015086C(((int)arg0));
        break;
    }
}


DEFINE_func_80150820()  /* dedup: shared engine-core @0x80150820 (src/shared) */


DEFINE_func_8015086C()  /* dedup: shared engine-core @0x8015086c (src/shared) */


DEFINE_func_801508B4()  /* dedup: shared engine-core @0x801508b4 (src/shared) */


DEFINE_func_801508F8()  /* dedup: shared engine-core @0x801508f8 (src/shared) */


  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4_8015094C;

extern s32 func_80021174(s32 a0, s32 a1);

s32 func_8015094C(s32 param_1) {

    extern S16 D_801C7B94;
    extern s32 D_80185884;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern u8 D_80126948[];
    struct { s32 x, mid, y; s32 _pad[9]; } arg;   /* 0x30 @ 0x10 */
    S16 local;                                     /* 0x10 @ 0x40 */
    s32 pad1[4];                                    /* 0x10 @ 0x50 */
    register u8 *cam __asm__("$17") = D_80126948;
    s32 ret;

    local = D_801C7B94;
    arg.x = *(short *)(param_1 + 6);
    arg.mid = D_80126994;
    arg.y = *(short *)(param_1 + 0xe);
    ret = func_80021174(D_80185884, (s32)&arg);
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

    extern s32 D_801C8544;
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
        "lui   $at, %%hi(D_801C8544)\n"
        "sw    $v0, %%lo(D_801C8544)($at)\n"
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
    extern void (*D_80185888[])(void);
    u32 idx;
    register u32 sub __asm__("$2");

    if ((D_800AE6B0 & 0x80FFFFFF) == 0) {
        idx = *(u16 *)(param_1 + 0x16C);
        if (idx != 0 && idx < 0x26) {
            sub = idx - 1;
            D_80185888[sub]();
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



/* func_80151664 — INTEGRATE lane.
 * Fleet canon (src/shared/engine_core.h:2924, inside DEFINE_func_8015410C()) declares
 *   extern void func_80151664(void);
 * so a `void func_80151664(s32 a0)` definition is `conflicting types` in every TU that
 * expands that macro (ov_SC01_077_after.c:3910 does).  Cookbook §73 PARAMS axis / §42:
 * keep the canonical (void) signature and read the incoming argument through a $a0 pin.
 * The decl below is reproduced verbatim so this file compiles the real conflict. */
extern void func_80151664(void);

extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801470AC(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80153C18();  /* fleet canon: K&R empty prototype (engine_core.h:75, :1682 defines it (void));
                                 * a prototyped (s32) decl is `conflicting types` in this TU. Arg still
                                 * passes in $a0 under default promotions -> codegen unchanged. */

void func_80151664(void) {
    register s32 a0v __asm__("$4");
    s32 s0;
    s32 v1;

    s0 = a0v;
    func_80154A74(s0, 0x11);
    func_801553C0(s0);
    func_801470AC((s32 *)s0);
    func_801472B4((void *)s0);
    v1 = *(s32 *)(s0 + 0x20);
    *(s16 *)(s0 + 0x3E) = 0;
    *(s16 *)(s0 + 0x40) = 0;
    *(s16 *)(s0 + 0x42) = 0;
    *(s8 *)(s0 + 0xDD) = 0;
    *(s16 *)(s0 + 0x3C) = *(u16 *)(s0 + 0x3C) & 0xFFFE;
    *(s16 *)(v1 + 0x10) = 0;
    *(s16 *)(s0 + 0x60) = 0x1000;
    *(s16 *)(s0 + 0x62) = 0x1000;
    *(s16 *)(s0 + 0x64) = 0x1000;
    func_801477E8((s32 *)s0, 0);
    func_80153C18(s0);
}


DEFINE_func_801516F0()  /* dedup: shared engine-core @0x801516f0 (src/shared) */


DEFINE_func_8015173C()  /* dedup: shared engine-core @0x8015173c (src/shared) */


DEFINE_func_80151780()  /* dedup: shared engine-core @0x80151780 (src/shared) */


void func_80151878(void) {
}

DEFINE_func_80151880()  /* dedup: shared engine-core @0x80151880 (src/shared) */


DEFINE_func_801518D8()  /* dedup: shared engine-core @0x801518d8 (src/shared) */


DEFINE_func_80151924()  /* dedup: shared engine-core @0x80151924 (src/shared) */




void func_80151944(void *a0) {

    extern void (*D_8018591C[])(void);
    D_8018591C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80151980()  /* dedup: shared engine-core @0x80151980 (src/shared) */


DEFINE_func_801519C8()  /* dedup: shared engine-core @0x801519c8 (src/shared) */


DEFINE_func_80151AE4()  /* dedup: shared engine-core @0x80151ae4 (src/shared) */


DEFINE_func_80151B98()  /* dedup: shared engine-core @0x80151b98 (src/shared) */


DEFINE_func_80151C54()  /* dedup: shared engine-core @0x80151c54 (src/shared) */




void func_80151D24(void *a0) {

    extern void (*D_8018592C[])(void);
    D_8018592C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80151D60()  /* dedup: shared engine-core @0x80151d60 (src/shared) */


DEFINE_func_80151DB0()  /* dedup: shared engine-core @0x80151db0 (src/shared) */


DEFINE_func_80151E78()  /* dedup: shared engine-core @0x80151e78 (src/shared) */


DEFINE_func_80151ECC()  /* dedup: shared engine-core @0x80151ecc (src/shared) */


DEFINE_func_80151F38()  /* dedup: shared engine-core @0x80151f38 (src/shared) */


DEFINE_func_80151FB4()  /* dedup: shared engine-core @0x80151fb4 (src/shared) */




void func_80152058(void *a0) {

    extern void (*D_80185950[])(void);
    D_80185950[*(u16 *)((s32)a0 + 0x2)]();
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
    extern M2C_UNK D_80185940;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80185940);
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


DEFINE_func_801522CC()  /* dedup: shared engine-core @0x801522cc (src/shared) */




void func_80152370(void *a0) {

    extern void (*D_80185964[])(void);
    D_80185964[*(u16 *)((s32)a0 + 0x2)]();
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
    extern u8 D_80185970[];
    s32 pad[4];
    s32 buf[4];
    register s32 s0a __asm__("$16");                    /* $s0 = buf */
    register s32 s2a __asm__("$18") = (s32)&D_80185970; /* $s2 = &D_80185970 */

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

    extern void (*D_80185980[])(void);
    D_80185980[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801526D4()  /* dedup: shared engine-core @0x801526d4 (src/shared) */


DEFINE_func_80152714()  /* dedup: shared engine-core @0x80152714 (src/shared) */


DEFINE_func_80152790()  /* dedup: shared engine-core @0x80152790 (src/shared) */




void func_8015282C(void *a0) {

    extern void (*D_80185998[])(void);
    D_80185998[*(u16 *)((s32)a0 + 0x2)]();
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
    extern M2C_UNK D_80185988;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80185988);
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

    extern void (*D_801859AC[])(void);
    D_801859AC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152BA8()  /* dedup: shared engine-core @0x80152ba8 (src/shared) */


DEFINE_func_80152BF0()  /* dedup: shared engine-core @0x80152bf0 (src/shared) */


DEFINE_func_80152C40()  /* dedup: shared engine-core @0x80152c40 (src/shared) */


DEFINE_func_80152C80()  /* dedup: shared engine-core @0x80152c80 (src/shared) */




void func_80152D24(void *a0) {

    extern void (*D_801859C8[])(void);
    D_801859C8[*(u16 *)((s32)a0 + 0x2)]();
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
    extern M2C_UNK D_801859B8;
    func_80019064(&D_80062C14);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    M2C_FIELD(arg0, s8 *, 0xDF) = 8;
    func_80146DB8(arg0, &D_801859B8);
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

    extern void (*D_801859DC[])(void);
    D_801859DC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015309C()  /* dedup: shared engine-core @0x8015309c (src/shared) */


DEFINE_func_801530E4()  /* dedup: shared engine-core @0x801530e4 (src/shared) */


DEFINE_func_80153150()  /* dedup: shared engine-core @0x80153150 (src/shared) */


DEFINE_func_801531BC()  /* dedup: shared engine-core @0x801531bc (src/shared) */


DEFINE_func_80153204()  /* dedup: shared engine-core @0x80153204 (src/shared) */


DEFINE_func_8015327C()  /* dedup: shared engine-core @0x8015327c (src/shared) */




void func_80153320(void *a0) {

    extern void (*D_801859F0[])(void);
    D_801859F0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015335C()  /* dedup: shared engine-core @0x8015335c (src/shared) */


DEFINE_func_801533A4()  /* dedup: shared engine-core @0x801533a4 (src/shared) */


DEFINE_func_80153410()  /* dedup: shared engine-core @0x80153410 (src/shared) */


DEFINE_func_80153490()  /* dedup: shared engine-core @0x80153490 (src/shared) */


DEFINE_func_801534D8()  /* dedup: shared engine-core @0x801534d8 (src/shared) */


DEFINE_func_80153550()  /* dedup: shared engine-core @0x80153550 (src/shared) */


DEFINE_func_801535F4()  /* dedup: shared engine-core @0x801535F4 (src/shared) */


DEFINE_func_8015369C()  /* dedup: shared engine-core @0x8015369c (src/shared) */


DEFINE_func_801536DC()  /* dedup: shared engine-core @0x801536dc (src/shared) */


extern void func_80015954(s32 a0, s32 a1);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80153978(s32 a0, u16 *src);
extern void *memcpy(void *dst, const void *src, u32 n);
s32 func_80153800(s32 a0) {

    extern void (*D_8011DB28)(s32 a0);
    extern u8 D_80126DB0[];
    extern u16 D_80126DB6;
    s32 s1 = a0;
    s32 s0;
    s32 s2;
    u8 bVar1;
    s16 buf1[4];
    s16 buf2[4];
    if (D_8011DB28 != 0) {
        ((void (*)(s32, s32))func_80015978)(s1 + 4, s1 + 0x88);
        memcpy((void *)(s1 + 0x90), (void *)(s1 + 0x88), 8);
ret0:
        return 0;
    }
    bVar1 = *(u8 *)(s1 + 0xDE);
    if (bVar1 >= 0x21) {
        s32 base = (s32)D_80126DB0;
        func_80015954(base, s1 + 4);
        memcpy((void *)(s1 + 0x88), (void *)base, 8);
        memcpy((void *)(s1 + 0x90), (void *)(s1 + 0x88), 8);
        *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = D_80126DB6;
        return 0;
    }
    {
        register s32 m __asm__("$3") = bVar1 * 4;
        s2 = m;
        buf2[1] = *(u16 *)(s1 + 0xA2) - m;
    }
    for (s0 = 0; s0 < 0x80; s0++) {
        s32 ang = s0 * 0x200000;
        buf1[0] = 0;
        buf1[1] = 0;
        buf1[2] = s2;
        func_800139C8(ang >> 0x10, buf1, buf1);
        buf2[0] = *(u16 *)(s1 + 0xA0) + buf1[0];
        buf2[2] = *(u16 *)(s1 + 0xA4) + buf1[2];
        if (((s32 (*)(s32, void *))func_80153978)(s1, buf2) == 0) {
            goto ret0;
        }
    }
    *(u8 *)(s1 + 0xDE) = *(u8 *)(s1 + 0xDE) + 1;
    return 1;
}


DEFINE_func_80153978()  /* dedup: shared engine-core @0x80153978 (src/shared) */


extern s32 func_80133784(s32 arg0, void *arg1, s32 arg2);

typedef struct {
    u16 f0, f2, f4;
    s16 f6;
} Blk801539F8;

s32 func_801539F8(s32 a0, void *a1)
{
    Blk801539F8 buf1;
    Blk801539F8 buf2;
    Blk801539F8 buf3;
    s32 r1, r2, r3;

    buf1 = *(Blk801539F8 *)(a0 + 0xA0);
    buf2 = *(Blk801539F8 *)a1;
    buf1.f2 -= 4;
    r1 = func_80133784(0, &buf1, (s32)&buf2);
    if (r1 != 0x2000) {
        return 1;
    }
    buf1 = buf2;
    buf2.f2 += 8;
    r2 = func_80133784(0, &buf1, (s32)&buf2);
    if (r2 != r1) {
        return 1;
    }
    r3 = func_80133784(2, &buf2, (s32)&buf3);
    if (r3 != r2) {
        return 1;
    }
    *(s16 *)(a0 + 0x88) = buf2.f0;
    *(s16 *)(a0 + 0x8A) = buf2.f2;
    *(s16 *)(a0 + 0x8C) = buf2.f4;
    *(Blk801539F8 *)(a0 + 0x90) = *(Blk801539F8 *)(a0 + 0x88);
    return 0;
}


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

    extern s32 D_80185A04;
    extern void (*D_80185A2C[])(void *a0);
    extern s16 D_8011DB0C;
    extern u16 D_8011F748;
    ((s32 (*)(s32))func_80019064)((s32)&D_80185A04);
    D_80185A2C[a0->idx](a0);
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

    extern u8 D_80185A0C;
    func_80147324(0x451);
    func_80154274((s32 *)param_1, (s32)&D_80185A0C);
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015444C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801549F8);

DEFINE_func_80154A74()  /* dedup: shared engine-core @0x80154a74 (src/shared) */


DEFINE_func_80154AB4()  /* dedup: shared engine-core @0x80154ab4 (src/shared) */


DEFINE_func_80154AE0()  /* dedup: shared engine-core @0x80154ae0 (src/shared) */


DEFINE_func_80154B20()  /* dedup: shared engine-core @0x80154b20 (src/shared) */


DEFINE_func_80154B4C()  /* dedup: shared engine-core @0x80154b4c (src/shared) */


DEFINE_func_80154B7C()  /* dedup: shared engine-core @0x80154b7c (src/shared) */


DEFINE_func_80154B98()  /* dedup: shared engine-core @0x80154b98 (src/shared) */


DEFINE_func_80154BC8()  /* dedup: shared engine-core @0x80154bc8 (src/shared) */


DEFINE_func_80154BE4()  /* dedup: shared engine-core @0x80154be4 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80154C24);

DEFINE_func_80154ED8()  /* dedup: shared engine-core @0x80154ed8 (src/shared) */


DEFINE_func_80154F9C()  /* dedup: shared engine-core @0x80154f9c (src/shared) */



// @class: struct
// @stuck: none — MATCH (array-of-struct stride-8 base materialize + addu, %lo folded into addiu)

extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_800183E0(s32 a0);


void func_801550FC(s32 arg0)
{

    extern ImgRect8 D_80185A38[];
    if (arg0 & 0x40000000) {
        MoveImage(&D_80185A38[arg0 & 0xFF], 0x200, 0x100);
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

    extern int (*D_80185A78[])(void);
    int idx;

    idx = *(unsigned char *)(param_1 + 0x4e);
    if (idx != 0) {
        idx = idx - 1;
        if ((*D_80185A78[idx])() == 0) {
            *(unsigned char *)(param_1 + 0x4e) = 0;
        }
    }
    return *(unsigned char *)(param_1 + 0x4e);
}


DEFINE_func_801554B8()  /* dedup: shared engine-core @0x801554b8 (src/shared) */


DEFINE_func_80155518()  /* dedup: shared engine-core @0x80155518 (src/shared) */


DEFINE_func_8015554C()  /* dedup: shared engine-core @0x8015554c (src/shared) */




void func_80155580(void *a0) {

    extern void (*D_80185A7C[])(void);
    D_80185A7C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801555BC()  /* dedup: shared engine-core @0x801555bc (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801555F4);

DEFINE_func_80155800()  /* dedup: shared engine-core @0x80155800 (src/shared) */


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



void func_80156044(int param_1, int param_2)
{
    extern u32 func_8015616C(s32 a0, u16 a1);
    extern void func_80156670(s32, s32, s32, s32, s32, u16);
    extern void func_801567BC(s32 a0);
    extern void func_80156848(s32, s32);
    extern void func_80156A88(s32 a0, s32 a1);
    extern s32 func_801565C0(void);
    extern u8 D_80185C34;
    extern u8 D_80185C48;
    extern u8 D_80185ACC;

    register s32 puVar2 __asm__("$2");
    register s32 iVar3 __asm__("$3");
    u8 *puVar4;
    s32 uVar1;

    if (((u32)param_2) & 0x10000) {
        iVar3 = (((u32)param_2) & 0xffff) * 0x14;
        puVar2 = (s32)&D_80185C34;
    } else if (((u32)param_2) & 0x20000) {
        iVar3 = (((u32)param_2) & 0xffff) * 0x14;
        puVar2 = (s32)&D_80185C48;
    } else {
        iVar3 = (((u32)param_2) & 0xffff) * 0x14;
        puVar2 = (s32)&D_80185ACC;
    }
    puVar4 = (u8 *)(iVar3 + puVar2);
    uVar1 = func_8015616C(((s32)param_1), *(u16 *)puVar4) & 0xffff;
    if (*(u8 *)(((s32)param_1) + 0x1a8) != 0) {
        ((void (*)(s32, s32, s32, s32, s32, s32))func_80156670)(((s32)param_1), *(s32 *)puVar4, uVar1, *(s32 *)(puVar4 + 4),
                      *(u8 *)(puVar4 + 0xA), *(u16 *)(puVar4 + 0x12));
        if (*(u8 *)(puVar4 + 0x10) != 0) {
            func_801567BC(((s32)param_1));
        }
        ((void (*)(s32, s32, s32))func_80156848)(((s32)param_1), (s32)puVar4, uVar1);
        func_80156A88(((s32)param_1), (s32)puVar4);
        if (((s32 (*)(s32))func_801565C0)(((s32)param_1)) != 0) {
            *(u8 *)(((s32)param_1) + 0x1c0) = 1;
        }
    }
}


DEFINE_func_8015616C()  /* dedup: shared engine-core @0x8015616c (src/shared) */


DEFINE_func_80156370()  /* dedup: shared engine-core @0x80156370 (src/shared) */




S801563EC *func_801563EC(u16 idx) {

    extern S801563EC D_80185C70[];
    return &D_80185C70[idx];
}


DEFINE_func_8015640C()  /* dedup: shared engine-core @0x8015640c (src/shared) */


DEFINE_func_801564B0()  /* dedup: shared engine-core @0x801564b0 (src/shared) */


DEFINE_func_801565C0()  /* dedup: shared engine-core @0x801565c0 (src/shared) */


DEFINE_func_80156600()  /* dedup: shared engine-core @0x80156600 (src/shared) */


DEFINE_func_80156648()  /* dedup: shared engine-core @0x80156648 (src/shared) */



DEFINE_func_80156670()  /* dedup: shared engine-core @0x80156670 (src/shared) */


DEFINE_func_801567BC()  /* dedup: shared engine-core @0x801567bc (src/shared) */


DEFINE_func_80156848()  /* dedup: shared engine-core @0x80156848 (src/shared) */


DEFINE_func_80156A14()  /* dedup: shared engine-core @0x80156a14 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; D_8011520C indexed by param_2 (byte) folds %lo; D_80185EE0 indexed halfword folds %lo
extern void func_80147324(s32 arg0);

void func_80156A1C(s32 param_1, s32 param_2)
{

    extern unsigned char D_8011520C[];
    extern unsigned short D_80185EE0[];
    if (*(unsigned char *)(param_1 + 0xDA) == 0) {
        func_80147324(D_80185EE0[D_8011520C[param_2]]);
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

    extern void (*D_80185EF0[])(void);
    D_80185EF0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80157580()  /* dedup: shared engine-core @0x80157580 (src/shared) */


DEFINE_func_801575E4()  /* dedup: shared engine-core @0x801575e4 (src/shared) */


DEFINE_func_801576A8()  /* dedup: shared engine-core @0x801576a8 (src/shared) */


DEFINE_func_8015771C()  /* dedup: shared engine-core @0x8015771c (src/shared) */


DEFINE_func_8015773C()  /* dedup: shared engine-core @0x8015773c (src/shared) */


void func_80147078(s32 *a0, s16 a1);
void func_801578C0(s32 a0);

void func_80157788(s32 *a0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801C8578;
    D_801C8578 = 0x12C;
    func_80147078(a0, 7);
    func_801578C0((s32)a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_80157808(s32 *a0);

void func_801577C8(s32 *param_1)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801C8578;
    D_801C8578 = 0x12C;
    func_80147078(param_1, 7);
    func_80157808(param_1);
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80157808);

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
    extern u8 D_80185EF8;
    ((void (*)(void))func_80156648)();
    *(u8 *)(param_1 + 0x1AA) = 9;
    func_80154274((s32 *)param_1, (s32)&D_800D5128);
    ((void (*)(s32 *, s32))func_80154A74)((s32 *)param_1, 0x15);
    func_80147324(0xC20);
    ((void (*)(s32 *, s32))func_80146DB8)((s32 *)param_1, (s32)&D_80185EF8);
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
    extern unsigned char D_80185F08;
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
            ((void (*)(int, void *))func_80146DB8)(param_1, &D_80185F08);
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



/* func_80157D20 — 21-ins plumbing shim (×138 overlays).
 *
 * §71 sibling-first: the immediate neighbour func_801578C0 in this very TU
 * (src/ov_SC01_077/ov_SC01_077_jr_80154C24.c L1592) already matches with
 * `((void (*)(void))func_80156648)();` — the zero-argument call form.  The
 * target likewise sets up NO argument registers before `jal func_80156648`
 * ($a0/$a1 still carry this function's own incoming args), so the call is
 * argument-less here too.
 *
 * The `lhu %lo(D_80185F48)($at)` with `sll $s0,$s0,1` => a plain u16 array
 * indexed by the second parameter, NOT hoisted into a pointer (§20: a pointer
 * var would keep one address register live across the call; the target rebuilds
 * the %hi/%lo pair inline after the call returns).
 *
 * §73 PARAMS axis / §42 lever 6 — the fleet canon for this symbol is
 * `extern void func_80157D20(void);` (this TU's carried decl layer, L399, and
 * every sibling overlay's).  A 2-param definition hard-errors with
 * `conflicting types` in the real TU (rtu_match, byte-verified), and the canon
 * cannot be widened from a draft (that is an R22 fleet edit).  So keep the
 * `(void)` signature and capture $a0/$a1 with register pins copied into NORMAL
 * pseudos — the copies are live across `jal func_80156648`, so they get the
 * callee-saved homes the target uses ($s1 = a0, $s0 = a1).  A direct
 * `register` use would leave the values in call-clobbered $a0/$a1.
 */

extern void func_80156648(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80157D74(u16 *a0);

void func_80157D20(void)
{

    extern u16 D_80185F48[];
    register void *a0v __asm__("$4");
    register s32 a1v __asm__("$5");
    void *param_1 = a0v;
    s32 param_2 = a1v;

    ((void (*)(void))func_80156648)();
    ((void (*)(void *, s32))func_80147078)(param_1, D_80185F48[param_2]);
    ((void (*)(void *))func_80157D74)(param_1);
}


DEFINE_func_80157D74()  /* dedup: shared engine-core @0x80157d74 (src/shared) */




void func_80157DC4(void *a0) {

    extern void (*D_80185F58[])(void);
    D_80185F58[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80157E00()  /* dedup: shared engine-core @0x80157e00 (src/shared) */


DEFINE_func_80157E38()  /* dedup: shared engine-core @0x80157e38 (src/shared) */


DEFINE_func_80157EA4()  /* dedup: shared engine-core @0x80157ea4 (src/shared) */


DEFINE_func_80157F64()  /* dedup: shared engine-core @0x80157f64 (src/shared) */




void func_80157FC4(void *a0) {

    extern void (*D_80185F60[])(void);
    D_80185F60[*(u16 *)((s32)a0 + 0x2)]();
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
    extern s32 D_80185F2C;
    *(u8 *)(param + 0x1aa) = 0xe;
    func_80154274((s32 *)param, (s32)&D_800D51E0);
    func_80154A74(param, 0x15);
    func_80146DB8((s32 *)param, &D_80185F2C);
    *(s32 *)(param + 0x234) = 0;
    func_80146994(5, param, 0xc, 0);
    func_80147324(0x455);
    func_80146CA0((void *)param);
}


DEFINE_func_801580B4()  /* dedup: shared engine-core @0x801580b4 (src/shared) */


DEFINE_func_801581AC()  /* dedup: shared engine-core @0x801581ac (src/shared) */




void func_8015824C(void *a0) {

    extern void (*D_80185F6C[])(void);
    D_80185F6C[*(u16 *)((s32)a0 + 0x2)]();
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

    extern u8 D_80185F3C;
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
        ((void (*)(s32, s32))func_80146DB8)(param_1, (s32)&D_80185F3C);
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



// @class: loose-typing
// @stuck: none — MATCH (87 ins, match_one) + symcheck SYMS-OK (17 symbols agree); same file also
//         MATCHes verbatim against ov_SC03_099 and ov_SC06_008 (sibling asm bodies are identical)

/* func_80158638 @ 0x80158638 — ov_SC01_077 / ov_SC01_077_jr_80154C24 (87 ins).
 *
 * TWO decl-ROBUSTNESS choices in the BODY, deliberate — these are the only two things the gate's
 * decl ladder (cast_call_sites/reconcile_tu/sig_unify) CANNOT repair, because they change codegen,
 * not plumbing. Both are load-bearing for templating this exemplar onto its 138 h_seq siblings,
 * where each overlay TU carries its own spelling of these decls:
 *
 *  1) `*(u16 *)&D_80078EB4` — the target loads it with `lhu`. The ov_SC01_077 TU already carries
 *     `extern s16 D_80078EB4;` (line 504), and a plain `D_80078EB4 != 0` read through an s16 decl
 *     compiles to `lh` => WIDTH/lh!=lhu, closeness 1. A `(u16)` cast does NOT fix it (gcc-2.7.2
 *     folds the zero_extend away for a !=0 test and keeps `lh`); the pointer pun does, and it is
 *     correct under EITHER declared signedness.
 *  2) `(s16)func_80159464(...)` with the fleet-canonical `extern s32 func_80159464();` decl.
 *     The target truncates the return to 16 bits at BOTH call sites (`sll 16` + `blez`, then
 *     `sll 16`/`sra 16`/`slti 6`). Declaring the callee `s16` also matches, but the fleet's carried
 *     decl layer spells it `extern s32 func_80159464(void);` in 1600 places — if reconcile_tu wins
 *     that conflict the truncation vanishes and the match dies. The explicit cast makes the body
 *     independent of which decl survives.
 *
 * Symbols verified present in build/ov_SC01_077/undefined_syms_auto.txt:
 *   D_80078EB4=0x80078EB4  D_800B9A17=0x800B9A17  D_800B9A64=0x800B9A64  D_80110EC0=0x80110EC0
 */


DEFINE_func_80158638()  /* dedup: shared engine-core @0x80158638 (src/shared) */


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

    extern s32 D_801C8580;
    extern s32 D_801C858C;
    extern s32 D_801C8590;
    D_801C8580 = 0;
    D_801C858C = 1;
    D_801C8590 = 0;
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

    extern s32 D_801C8580;
    extern s32 D_801C858C;
    extern s32 D_801C8590;
    D_801C8580 = 0;
    D_801C858C = 1;
    D_801C8590 = 0;
    *(s8 *)((s32)arg0 + 0xA8) = 0;
    ((void (*)(void))func_80147084)();
    ((void (*)(void *))func_80147098)(arg0);
    ((void (*)(void *))func_801470AC)(arg0);
    ((void (*)(void *, s32))func_80147078)(arg0, 0x1A);
    ((void (*)(void *))func_80158880)(arg0);
}



extern void func_80149020(s32 *a0);

void func_80158880(s32 *param) {

    extern void (*D_80185FA8[])(s32 *);
    func_80149020(param);
    D_80185FA8[*(u8 *)((s32)param + 0x4F)](param);
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801588CC);

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
    extern s32 D_801C8580;
    if (D_801C8580 == 0) {
        D_801C8580 = 1;
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

    extern s32 D_801C858C;
    extern s32 D_80185F7C[];
    int *self = (int *)param_1;
    struct Actor *act = (struct Actor *)self[0x20 / 4];
    int gate = D_801C858C;

    act->timer = (u16)((act->timer + 0x16) & 0xfff);

    if (gate == 0) {
        s32 r = rand();
        *(s32 *)(param_1 + 0x198) = func_8013767C(D_80185F7C[r % 0xb]);
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

    extern s32 D_801C8590;
    extern u8 D_80110C3C[];
    s32 v0;
    s16 sVar1;

    v0 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v0 + 0x12) = (*(u16 *)(v0 + 0x12) + 0x16) & 0xfff;
    if (((s32 (*)(void))func_80148800)() & 0xf0) {
        D_801C8590 = 1;
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
    extern s32 D_801C8580;
    extern s32 D_801C8588;
    void *temp_v1;

    if (D_801C8580 == 4) {
        D_801C8580 = 5;
    }
    if (D_801C8588 != 0) {
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

    extern Entry D_80185FE4[];
    Entry *e;

    e = D_80185FE4;
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801594E8);



void func_80159698(void *a0) {

    extern void (*D_801861F8[])(void);
    D_801861F8[*(u8 *)((s32)a0 + 0x15)]();
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
    extern char D_80186018[];
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
        func_80028620(0, &(*(u8 *)&D_80186018));
        func_80028620(1, &(*(u8 *)&D_80186018) + 0x10);
        func_80028620(2, &(*(u8 *)&D_80186018) + 0x20);
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

    extern void (*D_8018629C[])(void);
    D_8018629C[*(u8 *)((s32)a0 + 0x4D)]();
}




void func_801599A4(void *a0) {

    extern void (*D_801862A8[])(void);
    D_801862A8[*(u16 *)((s32)a0 + 0x0)]();
}


DEFINE_func_801599E0()  /* dedup: shared engine-core @0x801599e0 (src/shared) */


void func_80159A18(void) {
}

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80159A20);

DEFINE_func_80159B08()  /* dedup: shared engine-core @0x80159b08 (src/shared) */


DEFINE_func_80159B3C()  /* dedup: shared engine-core @0x80159b3c (src/shared) */




void func_80159B70(void *a0) {

    extern void (*D_801863F0[])(void);
    D_801863F0[*(u16 *)((s32)a0 + 0x2)]();
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

    extern unsigned char D_8018620C;
    int v;

    ((void (*)(int, void *))func_80146DB8)(arg0, &D_8018620C);
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80159C84);

DEFINE_func_8015A1C8()  /* dedup: shared engine-core @0x8015a1c8 (src/shared) */


DEFINE_func_8015A1FC()  /* dedup: shared engine-core @0x8015a1fc (src/shared) */


DEFINE_func_8015A230()  /* dedup: shared engine-core @0x8015a230 (src/shared) */




void func_8015A264(void *a0) {

    extern void (*D_801863F8[])(void);
    D_801863F8[*(u16 *)((s32)a0 + 0x2)]();
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

    extern int D_8018621C;
    unsigned char bVar1;

    ((void (*)(int, int *))func_80146DB8)(param_1, &D_8018621C);
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015A3C8);

DEFINE_func_8015AB7C()  /* dedup: shared engine-core @0x8015ab7c (src/shared) */


DEFINE_func_8015ABD4()  /* dedup: shared engine-core @0x8015abd4 (src/shared) */


void func_80154150(s32 a0, s32 a1);
void func_80146DB8(s32 *a0, s32 *a1);
void func_80161CD0(s32 a0, s32 a1);

extern s32 D_8018623C;

void func_8015AC48(s32 a0)
{
    register s32 r __asm__("$16") = a0;
    __asm__("");
    func_80154150(r, 0x9);
    func_80146DB8((s32 *)r, &D_8018623C);
    func_80161CD0(r, *(u16 *)((char *)r + 0x16E));
}


DEFINE_func_8015AC90()  /* dedup: shared engine-core @0x8015ac90 (src/shared) */


DEFINE_func_8015ACC4()  /* dedup: shared engine-core @0x8015acc4 (src/shared) */


DEFINE_func_8015AD08()  /* dedup: shared engine-core @0x8015ad08 (src/shared) */




void func_8015AD3C(void *a0) {

    extern void (*D_80186400[])(void);
    D_80186400[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015AD78()  /* dedup: shared engine-core @0x8015ad78 (src/shared) */


DEFINE_func_8015ADB0()  /* dedup: shared engine-core @0x8015adb0 (src/shared) */



/* func_8015AE2C (ov_SC01_077_after, 562 ins, jtbl_801D8B54) — Phase 26 crack
 * Entity main-update dispatcher: 7-case switch (0/1/2/6 shared, 3/4/5 own, no default
 * block — out-of-range falls to the after-switch join), then movement/clamp/decay tail.
 * PIN-FREE. Offset-pure (s32 arg0 + raw offsets) — ×134 template-safe.
 *
 * match_one: MATCH (562 ins). rtu_match (whole-TU): MATCH (562 ins) — see func_8015AE2C.md
 * for the two TU-side prerequisites (engine_core.h DEFINE_func_8015BEC4 extern must drop its
 * `(void)` prototype, and the def must stay K&R) plus the jtbl_carve trailing-pad-word note.
 *
 * Signature: `s32` return + K&R def are REQUIRED by the TU, byte-neutral vs void/ANSI here
 * (both verified MATCH 562): engine_core.h's thunk DEFINE_func_8015BEC4 does
 * `return func_8015AE2C();` (s32, zero-arg call) — only an unprototyped K&R def coexists
 * with that call. §41d does not bite on this body (it has early `return;`s).
 *
 * jtbl_801D8B54 = 7 entries [0,1,2,6]->0x8015AEE4  [3]->0x8015AFE0  [4]->0x8015AFF0
 * [5]->0x8015B000, bound `sltiu 7`, default(out-of-range) -> 0x8015B044 (after-switch).
 * The raw dlabel's 8th word 0x00000000 is NOT a table entry: it is the original TU's
 * intra-TU `.align 3` pad between consecutive jtbls (B34/B54/B74 chain) — the compiled
 * object emits exactly 28 B; the pad must stay in the raw post-carve data piece.
 */
extern void (*D_801862A8[])(void *);
extern s32 func_80161A60(s32 a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_80149FB0(s32 a0);
extern s32 func_801619A4(s32 *a0);
extern s32 func_80149C08(s32 a0);
extern void func_801577C8();
extern s32 func_8015B6F4(s32 a0);
extern s32 func_8015B7B4(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8015B8F8(s32 *a0);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_801498E0(s32 *a0);
extern s32 func_80149954(s32 s0);
extern s32 func_80149A64(s32 *a0);
extern void func_800CCCC0(s32 a0);
extern int func_80155FF8(int arg, int a1);
extern s32 func_8015B858(u8 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147814(s32 a0, s32 a1);
extern s32 func_800CF8B4(void);
extern s32 func_801491C4(s32 a0);
extern int func_80148AFC(void *a0);
extern s32 func_80149184(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147A30(s32 a0, s32 a1, s32 a2);
extern s32 func_80146E98(s32 a0);
extern void func_80146D90(s32 a0);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32 *a0);
extern s32 func_80172644(u8 *a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801541D8(u8 *a0, s32 a1, s32 a2);
extern s32 func_8014C050(s32 a0, s32 a1);
extern void func_800CCB78(s32 a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_80161488(void *a0);
extern void func_80146CA0(void *a0);
extern s32 func_8014A674(s32 *a0);
extern void func_8014E434(void);
extern void func_8015CC40(s32 *a0);
extern s32 func_8014A69C(s32 *a0);
extern void func_8014E6A0(void);
extern void func_8015CF8C(s32 *a0);
extern s32 func_801725A4(u8 *a0);
extern s16 D_801152A0;
extern u8 D_800D4BE0[];
extern s32 D_800D4E94;
extern s32 D_800D4ED4;
extern u8 D_800D4F8C[];
extern s32 D_800D4A9C;
extern s32 D_800D4B48;

s32 func_8015AE2C(arg0)
s32 arg0;
{
    s32 flag;
    s32 r;
    s32 lim;
    s32 doit;
    s32 t;

    flag = 0;
    if ((func_80161A60(arg0) != 0) && (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) && (*(s32 *)(arg0 + 0x34) >= 0)) {
        flag = 1;
        if (*(s32 *)(arg0 + 0x5C) == 0) {
            *(s32 *)(arg0 + 0x58) = 0;
            *(s32 *)(arg0 + 0x54) = 0;
            *(s32 *)(arg0 + 0x50) = 0;
        }
        *(s32 *)(arg0 + 0x5C) = 1;
    } else {
        *(s32 *)(arg0 + 0x5C) = 0;
    }
    ((void (*)(s32))func_80149FB0)(arg0);
    if (*(s32 *)(arg0 + 0x1B0) == 0) {
        switch (((s32 (*)(s32))func_801619A4)(arg0)) {
        case 0:
        case 1:
        case 2:
        case 6:
            if (*(s32 *)(arg0 + 0xB4) == (s32)&(*(s32 *)&D_800D4BE0)) {
                if (func_80149C08(arg0) != 0) {
                    D_801862A8[*(u16 *)arg0]((void *)arg0);
                    ((void (*)(s32))func_801577C8)(arg0);
                    return;
                }
            }
            if ((*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4E94) &&
                (*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4ED4) &&
                (*(s32 *)(arg0 + 0xB4) != (s32)&(*(s32 *)&D_800D4F8C))) {
                if (func_8015B6F4(arg0) == 0) {
                    ((void (*)(s32))func_8015B7B4)(arg0);
                }
            } else {
                if (*(u16 *)(arg0 + 0xB8) == 0x8000) {
                    func_80154A74(arg0, 0x22);
                    ((void (*)(s32))func_8015B8F8)(arg0);
                    *(u32 *)(arg0 + 0x44) &= ~2;
                    if (flag != 0) {
                        ((void (*)(s32, s32, s32, s32))func_80146994)(0x3B, arg0, 0, 0);
                    }
                }
            }
            break;
        case 3:
            ((void (*)(s32))func_801498E0)(arg0);
            break;
        case 4:
            ((void (*)(s32))func_80149954)(arg0);
            break;
        case 5:
            if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
                D_801862A8[*(u16 *)arg0]((void *)arg0);
                func_800CCCC0(arg0);
                return;
            }
            break;
        }
    }
    if (*(u32 *)(arg0 + 0x44) & 2) {
        ((void (*)(s32, s32))func_80155FF8)(arg0, *(u8 *)(arg0 + 0x1AA));
    } else {
        if ((*(s32 *)(arg0 + 0x240) == 0) && (((s32 (*)(s32))func_8015B858)(arg0) != 0)) {
            *(s32 *)(arg0 + 0x240) += 1;
        }
        if ((*(s32 *)(arg0 + 0xB4) == (s32)&(*(s32 *)&D_800D4BE0)) && (*(u16 *)(arg0 + 0xB8) & 0x8000)) {
            ((void (*)(s32))func_8015B8F8)(arg0);
        } else if ((*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4A9C) ||
                   (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4B48)) {
            if (*(u16 *)(arg0 + 0xB8) & 0x8000) {
                if (*(s32 *)(arg0 + 0x34) >= 0) {
                    *(u16 *)(arg0 + 0xB8) += 1;
                }
            }
        }
    }
    if (*(u8 *)(arg0 + 0x1C6) != 0) {
        if (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) {
            func_80148038(arg0, 0xFFFE6000);
        } else {
            func_80148038(arg0, 0x1A000);
        }
        lim = 0x40000;
        if ((*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4E94) &&
            (*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4ED4) &&
            (*(s32 *)(arg0 + 0xB4) != (s32)&(*(s32 *)&D_800D4F8C))) {
            lim = 0xC0000;
        }
        if (*(s32 *)(arg0 + 0x34) < -lim) {
            *(s32 *)(arg0 + 0x34) = -lim;
        } else if (lim < *(s32 *)(arg0 + 0x34)) {
            *(s32 *)(arg0 + 0x34) = lim;
        }
        func_80147460(arg0);
    } else {
        if (*(s32 *)(arg0 + 0x34) < 0) {
            if (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) {
                func_80147814(arg0, 0xFFFF0000);
            }
            func_80147814(arg0, 0x10000);
        }
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = ((*(u16 *)&D_801152A0) + func_801491C4(arg0)) & 0xFFF;
    }
    if (flag == 0) {
        if ((u8)((s32 (*)(s32))func_80148AFC)(arg0)) {
            (*(u16 *)&D_801152A0) = func_80149184(arg0);
            ((void (*)(s32, s32))func_80146E90)(arg0, 4);
            if (*(s32 *)(arg0 + 0x2C) > -0x80000) {
                *(s32 *)(arg0 + 0x2C) = -0x80000;
                func_80147A30(arg0, -0x10000, 0xBA000);
            } else {
                func_80147A30(arg0, -0x1000, 0xBA000);
            }
        } else {
            if (func_80146E98(arg0) != 0) {
                func_80146D90(arg0);
            }
        }
        func_80147A84(arg0);
        ((void (*)(s32))func_801473EC)(arg0);
        if (*(u8 *)(arg0 + 0x1C6) == 0) {
            func_80148038(arg0, 0x1A000);
            func_80147460(arg0);
        }
    } else {
        ((void (*)(s32))func_80172644)(arg0);
        if ((u8)((s32 (*)(s32))func_80148AFC)(arg0)) {
            (*(u16 *)&D_801152A0) = func_80149184(arg0);
            func_80146D90(arg0);
            func_80147AD4(arg0, 0, 0, 0xFFFF4000);
            *(s32 *)(arg0 + 0x50) += *(s32 *)(arg0 + 0x10);
            *(s32 *)(arg0 + 0x54) += *(s32 *)(arg0 + 0x14);
            *(s32 *)(arg0 + 0x58) += *(s32 *)(arg0 + 0x18);
            if (*(s32 *)(arg0 + 0x50) > 0xBA000) {
                *(s32 *)(arg0 + 0x50) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x50) < -0xBA000) {
                *(s32 *)(arg0 + 0x50) = -0xBA000;
            }
            if (*(s32 *)(arg0 + 0x54) > 0xBA000) {
                *(s32 *)(arg0 + 0x54) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x54) < -0xBA000) {
                *(s32 *)(arg0 + 0x54) = -0xBA000;
            }
            if (*(s32 *)(arg0 + 0x58) > 0xBA000) {
                *(s32 *)(arg0 + 0x58) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x58) < -0xBA000) {
                *(s32 *)(arg0 + 0x58) = -0xBA000;
            }
            *(s32 *)(arg0 + 0x10) = *(s32 *)(arg0 + 0x50);
            *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x54);
            *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x58);
            ((void (*)(s32))func_801473EC)(arg0);
        } else {
            doit = 0;
            if (*(s32 *)(arg0 + 0x50) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x50) >= 0) {
                    *(s32 *)(arg0 + 0x50) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x50) < 0) {
                        *(s32 *)(arg0 + 0x50) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x50) += 0x8000;
                    if (*(s32 *)(arg0 + 0x50) >= 0) {
                        *(s32 *)(arg0 + 0x50) = 0;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x54) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x54) >= 0) {
                    *(s32 *)(arg0 + 0x54) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x54) < 0) {
                        *(s32 *)(arg0 + 0x54) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x54) += 0x8000;
                    if (*(s32 *)(arg0 + 0x54) >= 0) {
                        *(s32 *)(arg0 + 0x54) = 0;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x58) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x58) >= 0) {
                    *(s32 *)(arg0 + 0x58) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x58) < 0) {
                        *(s32 *)(arg0 + 0x58) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x58) += 0x8000;
                    if (*(s32 *)(arg0 + 0x58) >= 0) {
                        *(s32 *)(arg0 + 0x58) = 0;
                    }
                }
            }
            if (doit != 0) {
                *(s32 *)(arg0 + 0x10) = *(s32 *)(arg0 + 0x50);
                *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x54);
                *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x58);
                ((void (*)(s32))func_801473EC)(arg0);
            }
            if (!(*(u32 *)(arg0 + 0x44) & 2)) {
                ((void (*)(s32, s32, s32))func_801541D8)(arg0, 0xF, 0x12);
            }
        }
        t = func_8014C050(arg0, 0x3B);
        if (t != 0) {
            func_800CCB78(t);
        }
        if ((*(u16 *)(arg0 + 0x1C8) & 0x1F) == 0) {
            ((void (*)(s32, s32, s32, s32))func_80146994)(0x3C, arg0, 0, 0);
        }
    }
    if (*(s32 *)(arg0 + 0x1B0) != 0) {
        if (*(s32 *)(arg0 + 0x1B0) == 1) {
            func_80154A74(arg0, 0x22);
            func_80154150(arg0, 0xF);
        } else {
            ((void (*)(s32, s32))func_80154274)(arg0, *(s32 *)(arg0 + 0x1B4));
        }
    }
    r = ((s32 (*)(s32))func_80161488)(arg0);
    if (r & 5) {
        *(u32 *)(arg0 + 0x44) &= ~2;
        if (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4A9C) {
            func_80154150(arg0, 0xE);
        } else {
            func_80154150(arg0, 0x10);
        }
        ((void (*)(s32))func_80146CA0)(arg0);
    }
    if (r == 0) {
        if ((((s32 (*)(s32))func_8014A674)(arg0) != 0) && (((s32 (*)(s32))func_8014E434)(arg0) != 0)) {
            D_801862A8[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8015CC40)(arg0);
        } else if ((((s32 (*)(s32))func_8014A69C)(arg0) != 0) && (((s32 (*)(s32))func_8014E6A0)(arg0) != 0)) {
            D_801862A8[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8015CF8C)(arg0);
        } else {
            ((void (*)(s32))func_801725A4)(arg0);
        }
    }
}

DEFINE_func_8015B6F4()  /* dedup: shared engine-core @0x8015b6f4 (src/shared) */


DEFINE_func_8015B7B4()  /* dedup: shared engine-core @0x8015b7b4 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015B858);

DEFINE_func_8015B8F8()  /* dedup: shared engine-core @0x8015b8f8 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015B950);

DEFINE_func_8015BD8C()  /* dedup: shared engine-core @0x8015bd8c (src/shared) */


DEFINE_func_8015BDD0()  /* dedup: shared engine-core @0x8015bdd0 (src/shared) */


DEFINE_func_8015BE04()  /* dedup: shared engine-core @0x8015be04 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015BE38);

DEFINE_func_8015BE74()  /* dedup: shared engine-core @0x8015be74 (src/shared) */


DEFINE_func_8015BE94()  /* dedup: shared engine-core @0x8015be94 (src/shared) */


DEFINE_func_8015BEC4()  /* dedup: shared engine-core @0x8015bec4 (src/shared) */


DEFINE_func_8015BEE4()  /* dedup: shared engine-core @0x8015bee4 (src/shared) */


DEFINE_func_8015BF04()  /* dedup: shared engine-core @0x8015bf04 (src/shared) */


DEFINE_func_8015BF48()  /* dedup: shared engine-core @0x8015bf48 (src/shared) */


DEFINE_func_8015BF7C()  /* dedup: shared engine-core @0x8015bf7c (src/shared) */


DEFINE_func_8015BFB0()  /* dedup: shared engine-core @0x8015bfb0 (src/shared) */




void func_8015BFF4(void *a0) {

    extern void (*D_80186428[])(void);
    D_80186428[*(u16 *)((s32)a0 + 0x2)]();
}



/* §71 sibling-first: this is DEFINE_func_8015C0C4 (src/shared/engine_core.h L8919)
 * with the two globals replaced by the second parameter and <<6 -> <<7.
 * The explicit temporary `t` keeps the first lh ahead of the 0x238 store.
 *
 * Signature is the fleet canon `(s32 *a0, s32 a1)` declared by
 * DEFINE_func_8015BFB0 (engine_core.h L16218) — a private `(s32, s16 *)`
 * definition also match_one-MATCHes but breaks the real TU with
 * `conflicting types`.  The s16 reads are cast at the use site. */

extern void func_80154150(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern void func_80146CA0(void *a0);

void func_8015C030(s32 *a0, s32 a1)
{
    s32 t = *(s16 *)a1 << 7;
    *(s32 *)((s32)a0 + 0x238) = 0x80000;
    *(s32 *)((s32)a0 + 0x234) = t;
    *(s32 *)((s32)a0 + 0x23C) = *(s16 *)(a1 + 4) << 7;
    func_80154150((s32)a0, 0x11);
    func_801553A8(a0);
    func_80146CA0((void *)a0);
}


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
extern s32 func_8014F3E8(s32 a0);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);



s32 func_8015C128(s32 param_1) {

    extern void (*D_801862A8[])(void *);

    extern u16 D_800B99DA;
    extern void func_8015C6E0(s32*);

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
        D_801862A8[*(u16 *)((int)param_1)](((int)param_1));
        ((void (*)(int))func_8015C6E0)(((int)param_1));
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
        D_801862A8[*(u16 *)((int)param_1)](((int)param_1));
        ((void(*)(int, int))func_80147078)(((int)param_1), 3);
        ((void(*)(int))func_8015BE94)(((int)param_1));
    }
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015C32C);

void func_8015C6A4(void) {
}

DEFINE_func_8015C6AC()  /* dedup: shared engine-core @0x8015c6ac (src/shared) */


DEFINE_func_8015C6E0()  /* dedup: shared engine-core @0x8015c6e0 (src/shared) */




void func_8015C714(void *a0) {

    extern void (*D_80186434[])(void);
    D_80186434[*(u16 *)((s32)a0 + 0x2)]();
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

    extern void (*D_801862A8[])(void*);
    extern int D_8018624C;
    s32 iVar1;
    u32 uVar2;

    iVar1 = ((s32 (*)(u16 *))func_80161B18)(param_1);
    if ((iVar1 == 0) && (iVar1 = ((s32 (*)(u16 *))func_80161B84)(param_1), iVar1 == 0)) {
        iVar1 = ((s32 (*)(u16 *))func_801496D4)(param_1);
        if (iVar1 != 0) {
            ((void (**)(u16*))D_801862A8)[*param_1](param_1);
            ((void (*)(u16 *))func_80149704)(param_1);
        } else {
            uVar2 = ((s32 (*)(u16 *))func_801487F4)(param_1);
            if (((uVar2 & 0x80) == 0) && (iVar1 = ((s32 (*)(u16 *))func_801488A8)(param_1), iVar1 == 0)) {
                ((void (**)(u16*))D_801862A8)[*param_1](param_1);
                ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
                ((void (*)(u16 *))func_80159B70)(param_1);
            } else {
                iVar1 = ((s32 (*)(u16 *))func_80161240)(param_1);
                if (iVar1 == 0) {
                    iVar1 = ((s32 (*)(u16 *))func_80146E98)(param_1);
                    if (iVar1 != 0) {
                        ((void (*)(u16 *))func_80148AAC)(param_1);
                        ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_8018624C);
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

    extern void (*D_801862A8[])();
    func_80149FB0(param_1);
    func_80147AD4(param_1, 0, 0, 0);
    ((void (*)(int))func_801473EC)(param_1);
    ((void (*)(int))func_8014D738)(param_1);
    if (*(int *)(param_1 + 0x170) == 0) {
        (*D_801862A8[*(unsigned short *)param_1])(param_1);
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

    extern void (*D_801862A8[])(void*);
    extern int D_8018624C;
    ((void (*)(void))func_80149FB0)();
    if (((int (*)(u16 *))func_80161B18)(param_1) != 0) return;
    if (((int (*)(u16 *))func_80161B84)(param_1) != 0) return;
    if (((int (*)(u16 *))func_801496D4)(param_1) != 0) {
        ((void (**)(u16*))D_801862A8)[*param_1](param_1);
        ((void (*)(u16 *))func_80149704)(param_1);
        return;
    }
    if ((((u32 (*)(u16 *))func_801487F4)(param_1) & 0x80) != 0 || ((int (*)(u16 *))func_801488A8)(param_1) != 0) {
        if ((((int (*)(u16 *))func_80148AAC)(param_1) & 0xff) != 0) {
            ((void (*)(u16 *, int, int, int))func_80147AD4)(param_1, 0, 0, 0);
            ((void (*)(u16 *))func_801473EC)(param_1);
        }
        if (((int (*)(u16 *))func_8014D738)(param_1) != 0) {
            ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_8018624C);
            ((void (*)(u16 *, int))func_80146E90)(param_1, 0x14);
            ((void (*)(u16 *, int))func_80146C98)(param_1, 2);
        }
        if (*(int *)(param_1 + 0xb8) != 0)
            goto do161240;
    }
    ((void (**)(u16*))D_801862A8)[*param_1](param_1);
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015CC74);

DEFINE_func_8015CCB0()  /* dedup: shared engine-core @0x8015ccb0 (src/shared) */


DEFINE_func_8015CCD0()  /* dedup: shared engine-core @0x8015ccd0 (src/shared) */



extern void func_80146D90(s32 a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_801473EC(s32 *a0);
extern void func_80147A84(s32 arg0);
extern s32 func_8014891C(s32 a0);
extern s32 func_80148980(u8 *a0);
extern s32 func_801489E8(s32 a0);
extern s32 func_80148A48(s32 a0);
extern int func_80148AFC(void *a0);
extern s32 func_801496D4(void *a0);
extern void func_80149724(void);
extern s32 func_80149FB0(s32 a0);
extern void func_8014E434(void);
extern void func_8014FA04(s32 a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80159B70(void *a0);
extern s32 func_801725E0(u8 *a0);





s32 func_8015CD20(s32 arg0) {

    extern void (*D_801862A8[])(void *);
    extern u8 D_8018625C;
    extern u8 D_8018644C;
    extern u8 D_8018645C;

    s32 temp_v0;
    s32 var_v0;
    struct Sub_8015CD20 *sp;

    ((void(*)())func_80149FB0)();
    if (((s32(*)(struct Ent_8015CD20 *))func_801496D4)(((struct Ent_8015CD20 *)arg0)) != 0) {
        D_801862A8[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((struct Ent_8015CD20 *)arg0)->unk1BC = 0xA;
        ((s32(*)(struct Ent_8015CD20 *))func_80149724)(((struct Ent_8015CD20 *)arg0));
        if (((s32(*)(struct Ent_8015CD20 *))func_80148AFC)(((struct Ent_8015CD20 *)arg0)) & 0xFF) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_8018625C);
        } else {
            ((void(*)(struct Ent_8015CD20 *))func_80146D90)(((struct Ent_8015CD20 *)arg0));
        }
        return;
    }
    temp_v0 = ((struct Ent_8015CD20 *)arg0)->unk234;
    if (temp_v0 == 0) {
        if (((s32(*)(struct Ent_8015CD20 *))func_80148980)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_8018644C);
            ((void(*)(struct Ent_8015CD20 *))func_80147A84)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *))func_801473EC)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *, s32))func_80154150)(((struct Ent_8015CD20 *)arg0), 0x15);
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 - 0xAA;
            goto block_13;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_8014891C)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_8018645C);
            ((void(*)(struct Ent_8015CD20 *))func_80147A84)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *))func_801473EC)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *, s32))func_80154150)(((struct Ent_8015CD20 *)arg0), 0x14);
            ((struct Ent_8015CD20 *)arg0)->unkB8 = 1;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_801489E8)(((struct Ent_8015CD20 *)arg0)) != 0) {
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 + 0x71;
            goto block_13;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_80148A48)(((struct Ent_8015CD20 *)arg0)) != 0) {
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 - 0x71;
block_13:
            sp->unk12 = var_v0 & 0xFFF;
        }
    } else {
        ((struct Ent_8015CD20 *)arg0)->unk234 = temp_v0 - 1;
    }
    ((void(*)(struct Ent_8015CD20 *))func_8014FA04)(((struct Ent_8015CD20 *)arg0));
    if (((s32(*)(struct Ent_8015CD20 *))func_8014E434)(((struct Ent_8015CD20 *)arg0)) == 0) {
        D_801862A8[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((void(*)(struct Ent_8015CD20 *, s32))func_80147078)(((struct Ent_8015CD20 *)arg0), 0);
        ((void(*)(struct Ent_8015CD20 *))func_80159B70)(((struct Ent_8015CD20 *)arg0));
    } else {
        ((void(*)(struct Ent_8015CD20 *))func_801725E0)(((struct Ent_8015CD20 *)arg0));
    }
}


DEFINE_func_8015CF24()  /* dedup: shared engine-core @0x8015cf24 (src/shared) */


DEFINE_func_8015CF58()  /* dedup: shared engine-core @0x8015cf58 (src/shared) */


DEFINE_func_8015CF8C()  /* dedup: shared engine-core @0x8015cf8c (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015CFC0);

DEFINE_func_8015CFFC()  /* dedup: shared engine-core @0x8015cffc (src/shared) */


extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80154274(s32 *a0, s32 a1);

// @class: regalloc-order
// @stuck: none — MATCH (uVar1 pinned $s3, uVar5 pinned $s1; param_1->s2, iVar4->s0 fall out)


void func_8015D01C(int param_1) {
    extern s32 func_801725F4(u8 *a0);
    extern int D_800D550C;
    extern int D_8018646C;

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
    *(int *)(param_1 + 0x38) = (int)&D_8018646C | 0x40000000;
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

    extern void (*D_801862A8[])(void *);
    ((void (*)(void))func_80149FB0)();
    ((void (*)(void *))func_8014FA04)(arg0);
    if (((s32 (*)(void *))func_8014E6A0)(arg0) == 0) {
        D_801862A8[*(u16 *)arg0](arg0);
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



extern s32 func_80149FB0(s32);
extern void func_80147324(s32 a0);
extern u16  func_80148800(s32 *a0);
extern void func_80149724(void);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146DB8(s32*, s32*);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_8014FA04(s32);
extern void func_8014E6A0(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void*);
extern void func_8015D380(s32);
extern s32  func_801725F4(u8 *a0);


void func_8015D1B8(s32 *a0)
{

    extern void (*D_801862A8[])(void*);
    extern s32 D_80186488;
    extern s32 D_8018648C;
    extern s32 D_801864D0;
    extern s32 D_800D4C14;
    s32 sum;
    s32 keep;
    s32 obj;
    s16 cur;
    s16 prev;
    s16 d;
    s32 off;
    s32 *p;
    s32 dummy[2]; /* L1: dead, but its stack slot is what makes the frame 0x38 */

    ((void (*)(void))func_80149FB0)();
    obj = *(s32 *)((u8 *)a0 + 0x20);
    sum = *(u16 *)(obj + 0x10) + *(u16 *)((u8 *)a0 + 0x236);
    *(u16 *)(obj + 0x10) = sum & 0xFFF;
    keep = sum; /* L2: AFTER the store — this is what keeps the $s0 copy alive */

    cur = *(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x10);
    prev = *(s16 *)((u8 *)a0 + 0x244);
    if (cur - prev >= 0) {
        d = cur - prev;
    } else {
        d = prev - cur;
    }
    if (d > 0x800) {
        func_80147324(0x5E9);
    }
    *(u16 *)((u8 *)a0 + 0x244) = *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x10);

    if (func_80148800(a0) & 0x40) {
        ((void (**)(s32*))D_801862A8)[*(u16 *)a0](a0);
        ((void (*)(s32 *))func_80149724)(a0);
        func_80154274(a0, (s32)&D_800D4C14);
        func_80146E90(a0, 0x10);
        {
            u32 t = keep & 0xFFF; /* L3: unsigned value, signed guard -> bgez + srl */
            if ((s32)t < 0) {
                t += 0x1FF;
            }
            p = &D_801864D0; /* L4 + scheduling: the `la` must precede the srl/sll pair */
            off = (t >> 9) * 8;
        }
        *p = *(s32 *)((u8 *)&D_80186488 + off);
        ((void (*)(s32 *, s32))func_80146DB8)(a0, (s32)(p - 2)); /* 0x801893D8 == &D_801864D0[-2] (no label there) */
        func_801477E8(a0, *(s32 *)((u8 *)&D_8018648C + off));
        func_80147324(0x5EA);
    } else {
        ((void (*)(s32 *))func_8014FA04)(a0);
        if (((s32 (*)(s32 *))func_8014E6A0)(a0) == 0) {
            ((void (**)(s32*))D_801862A8)[*(u16 *)a0](a0);
            func_80147078(a0, 0);
            ((void (*)(s32 *))func_80159B70)(a0);
        } else {
            ((void (*)(s32 *))func_8015D380)(a0);
            func_801725F4(a0);
        }
    }
}




// @class: regalloc-order
// @stuck: pinning a0->$s1 and buffer-ptr->$s0; body copy already matches
extern void func_80013F3C(s32 a0);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800126C4(s32 a0, s32 a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void *memcpy(void *dst, const void *src, u32 n);


void func_8015D380(s32 a0) {

    extern s32 D_801864D8;
    s16 out[4];
    s32 buf[8];
    register s32 s1 __asm__("$17") = a0;
    register s32 *s0 __asm__("$16") = buf;
    ((void (*)(void *))func_80013F3C)((void *)s0);
    ((void (*)(void *, s32))func_80012558)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12));
    ((void (*)(void *, s32))func_800126C4)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x10));
    ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)s0, (void *)&D_801864D8, (void *)out);
    memcpy((void *)(s1 + 0x138), (void *)out, 8);
}



// @class: plumbing
// @stuck: none — MATCH


extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_8015D414(int param_1)
{

    extern unsigned char D_801855BC[];
    *(unsigned char *)(param_1 + 0x1bd) = 8;
    *(unsigned char **)(param_1 + 0x38) = D_801855BC;
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015D4E8);

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

    extern unsigned char D_801864EC[];
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
                (short)((signed char)D_801864EC[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xc));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 10) =
                (short)((signed char)D_801864EC[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xe));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 0xe) =
                (short)((signed char)D_801864EC[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0x10));
            func_80149374(param_1, iVar1 + 4);
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015D738);

DEFINE_func_8015DA5C()  /* dedup: shared engine-core @0x8015da5c (src/shared) */


DEFINE_func_8015DA90()  /* dedup: shared engine-core @0x8015da90 (src/shared) */


DEFINE_func_8015DAC4()  /* dedup: shared engine-core @0x8015dac4 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015DAF8);

DEFINE_func_8015DB34()  /* dedup: shared engine-core @0x8015db34 (src/shared) */


DEFINE_func_8015DB6C()  /* dedup: shared engine-core @0x8015db6c (src/shared) */



// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015DD74(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015DCB8(s32 a0);

void func_8015DBD4(void *arg0) {

    extern void (*D_801862A8[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015DD74)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_801862A8[*(u16 *)arg0](arg0);
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

    extern s8 D_80186528[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_80186528[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_80186528[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_80186528[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015DD74()  /* dedup: shared engine-core @0x8015dd74 (src/shared) */


DEFINE_func_8015DDF0()  /* dedup: shared engine-core @0x8015ddf0 (src/shared) */


DEFINE_func_8015DE24()  /* dedup: shared engine-core @0x8015de24 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015DE58);

DEFINE_func_8015DE94()  /* dedup: shared engine-core @0x8015de94 (src/shared) */


DEFINE_func_8015DECC()  /* dedup: shared engine-core @0x8015decc (src/shared) */



// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015E0D4(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015E018(s32 a0);

void func_8015DF34(void *arg0) {

    extern void (*D_801862A8[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015E0D4)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_801862A8[*(u16 *)arg0](arg0);
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

    extern s8 D_80186528[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_80186528[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_80186528[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_80186528[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015E0D4()  /* dedup: shared engine-core @0x8015e0d4 (src/shared) */


DEFINE_func_8015E150()  /* dedup: shared engine-core @0x8015e150 (src/shared) */


DEFINE_func_8015E184()  /* dedup: shared engine-core @0x8015e184 (src/shared) */


extern void (*D_80186560[])(void);

s32 func_8015E1B8(s32 a0)
{
    unsigned short idx = *(unsigned short *)(a0 + 2);
    D_80186560[idx]();
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

    extern void (*D_801862A8[])(void*);
    ((s32 (*)(void))func_8015E40C)();
    if (((s32 (*)(u16 *))func_80161B18)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161B84)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161208)(param_1) == 0) {
        if ((param_1[0x5c] & 0x4000) != 0) {
            ((void (*)(u16 *))func_8015E5B0)(param_1);
            *(s32 *)((char *)param_1 + 0x234) = 1;
        }
        if ((param_1[0x5c] & 0x8000) != 0) {
            ((void (**)(u16*))D_801862A8)[param_1[0]](param_1);
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

    extern u16 D_80186570;
    extern u16 D_80186572;
    extern u16 D_80186574;
    extern s32 D_80186578;
    u16 *psVar1;
    s16 v[3];
    s32 local_10;

    psVar1 = *(u16 **)(param_1 + 0x18c);
    if ((psVar1 != (u16 *)0) && (*psVar1 != 0)) {
        v[0] = D_80186570 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0xc);
        v[1] = D_80186572 + *(s16 *)(*(s32 *)(psVar1 + 0x3c) + 0xe) * 2;
        v[2] = D_80186574 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0x10);
        ((s32 (*)(s32, s16 *, s16 *))func_80149350)(param_1, &v[0], &v[0]);
        ((s32 (*)(s32 *, s32 *))func_80013E94)(&D_80186578, &local_10);
        ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x1f, param_1, v[0], v[1], v[2], local_10, 0);
    }
    return;
}


extern s32 func_8013C9C4(s32 *a0);
void func_8015E588(void) {

    extern s32 D_80186580;
    func_8013C9C4(&D_80186580);
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

    extern void (*D_801862A8[])(void*);
    if (func_80161208() == 0 && (param_1[0x5c] & 0x8000) != 0) {
        ((void (**)(u16*))D_801862A8)[param_1[0]](param_1);
        ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
        ((void (*)(u16 *))func_80159BE4)(param_1);
    }
}


DEFINE_func_8015E714()  /* dedup: shared engine-core @0x8015e714 (src/shared) */


DEFINE_func_8015E84C()  /* dedup: shared engine-core @0x8015e84c (src/shared) */


DEFINE_func_8015E880()  /* dedup: shared engine-core @0x8015e880 (src/shared) */


DEFINE_func_8015E8B4()  /* dedup: shared engine-core @0x8015e8b4 (src/shared) */


extern void (*D_80186594[])(void);

void func_8015E8E8(s32* param_1)
{
    unsigned short idx;
    void (*fn)(void);

    idx = *(unsigned short *)((char *)param_1 + 2);
    fn = D_80186594[idx];
    fn();
}


DEFINE_func_8015E924()  /* dedup: shared engine-core @0x8015e924 (src/shared) */


DEFINE_func_8015E95C()  /* dedup: shared engine-core @0x8015e95c (src/shared) */


DEFINE_func_8015E9B8()  /* dedup: shared engine-core @0x8015e9b8 (src/shared) */



extern u16 func_801487F4(s32*);
extern void func_80147078(s32*, s16);
extern void func_80159B70(void *a0);
extern s32 func_80149D10(s32);
extern void func_80175150(s32*);
extern void func_8016EE40(s32, s32, s32);
extern s32 func_80149744(struct S_80149744*);
extern void func_80149788(void);
extern s32 func_80161B84(void *a0);
extern s32 func_8014A4B4(void *a0);
extern void func_8014A4FC(void);
extern s32 func_80149AA8(s32*);
extern void func_80149AD4(s32*);
extern s32 func_80149B54(s32*);
extern void func_80149BAC(s32*);
extern s32 func_800CF8B4(void);
extern s32 func_801491C4(s32);
extern s32 func_80148E54(void *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32*, s32*);
extern void func_80147A84(s32);
extern void func_801473EC(s32*);
extern void func_80154150(s32, s32);
extern void func_8014D738(void);
extern void func_8015C714(void *a0);
extern s32 func_80161208();  /* canonical no-proto (§17a-1) */
extern void func_801483E8(unsigned char*);


void func_8015EA3C(void *arg0) {

    extern void (*D_801862A8[])(void *);
    extern s16 D_801152A0;
    s32 invec[4];
    s32 outbuf[4];
    s32 temp;
    s32 r;

    if (!(((s32 (*)(void))func_801487F4)() & 8)) {
        D_801862A8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
        return;
    }
    r = ((s32 (*)(void *))func_80149D10)(arg0);
    if (r == 1) goto Lcase1;
    if (r < 2) goto Ldefault;
    if (r == 2) goto Lcase2;
    goto Ldefault;
Lcase1:
    D_801862A8[*(u16 *)arg0](arg0);
    ((void (*)(void *))func_80175150)(arg0);
    return;
Lcase2:
    ((void (*)(s32, s32))func_8016EE40)(*(s32 *)((u8 *)arg0 + 0x21C), 0x01000000);
    return;
Ldefault:
    if (((s32 (*)(void *))func_80149744)(arg0) != 0) {
        D_801862A8[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_80149788)(arg0);
        return;
    }
    if (func_80161B84(arg0) != 0) {
        return;
    }
    if (func_8014A4B4(arg0) != 0) {
        D_801862A8[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_8014A4FC)(arg0);
        return;
    }
    if (((s32 (*)(void *))func_80149AA8)(arg0) != 0) {
        D_801862A8[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_80149AD4)(arg0);
        return;
    }
    if (((s32 (*)(void *))func_80149B54)(arg0) != 0) {
        D_801862A8[*(u16 *)arg0](arg0);
        ((void (*)(void *))func_80149BAC)(arg0);
        return;
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12) =
            ((*(u16 *)&D_801152A0) + ((s32 (*)(void *))func_801491C4)(arg0)) & 0xFFF;
    }
    temp = func_80148E54(arg0);
    if ((s16)temp >= 0) {
        s32 d = temp - *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12);
        invec[0] = 0;
        invec[1] = 0;
        invec[2] = 0xFFFC0000;
        func_8001382C((s16)d, invec, outbuf);
        ((void (*)(void *, void *))func_80146DB8)(arg0, outbuf);
        ((void (*)(void *))func_80147A84)(arg0);
        ((void (*)(void *))func_801473EC)(arg0);
        ((void (*)(void *, s32))func_80154150)(arg0, 0x1E);
    } else {
        ((void (*)(void *, s32))func_80154150)(arg0, 0x1D);
    }
    if (((s32 (*)(void *))func_8014D738)(arg0) != 0) {
        D_801862A8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 9);
        func_8015C714(arg0);
        return;
    }
    if (((s32 (*)(s32))func_80161208)(arg0) == 0) {  /* §17a-1 */
        ((void (*)(void *))func_801483E8)(arg0);
    }
}


DEFINE_func_8015ED6C()  /* dedup: shared engine-core @0x8015ed6c (src/shared) */


DEFINE_func_8015EDA0()  /* dedup: shared engine-core @0x8015eda0 (src/shared) */


DEFINE_func_8015EDD4()  /* dedup: shared engine-core @0x8015edd4 (src/shared) */


extern void (*D_8018659C[])(void);

s32 func_8015EE08(s32 a0)
{
    D_8018659C[*(u16 *)((s32)a0 + 0x2)]();
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
    extern int D_8018628C;
    ((int (*)(void))func_8014CBF8)();
    ((int (*)(int))func_801474EC)(param_1);
    ((int (*)(int, void *))func_80154274)(param_1, &D_800D4C48);
    ((int (*)(int, void *))func_80146DB8)(param_1, &D_8018628C);
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

    extern void (*D_801862A8[])(void *);
    ((void (*)(void *, s32))func_80148038)(arg0, 0x10000);
    ((void (*)(void *))func_80147460)(arg0);
    ((void (*)(void *, s32, s32, s32))func_80147AD4)(arg0, 0, 0, 0x1000);
    ((void (*)(void *))func_801473EC)(arg0);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_801862A8[*(u16 *)arg0](arg0);
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015F00C);

DEFINE_func_8015F048()  /* dedup: shared engine-core @0x8015f048 (src/shared) */


DEFINE_func_8015F080()  /* dedup: shared engine-core @0x8015f080 (src/shared) */


extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8014AB5C(void);
extern void func_80159B70(void *a0);
extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern s32 func_80161208();  /* canonical no-proto (§17a-1) */
extern int func_80155FF8(int arg, int a1);

void func_8015F118(void *a0) {

    extern s32 D_80062BE8;
    extern void (*D_801862A8[])(void *);
    u16 flag;

    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        (*D_801862A8[*(u16 *)a0])(a0);
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015F324);

DEFINE_func_8015F360()  /* dedup: shared engine-core @0x8015f360 (src/shared) */


DEFINE_func_8015F380()  /* dedup: shared engine-core @0x8015f380 (src/shared) */




extern s32 func_80149884(void);
extern s32 func_801496D4(void*);
extern void func_80149724(void);
extern void func_801477E8(s32*, s32);
extern u16 func_80148800(s32*);
extern s32 func_80148980(u8*);
extern void func_8014F1F4(void);
extern void func_8014FCFC(void);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32*);
extern void func_80146DB8(s32*, s32*);
extern void func_80146E90(s32*, s32);
extern void func_8014ED28(s32 a0);
extern void func_8014FA04(s32 a0);
extern s32 func_801725B8(u8*);
extern void func_80147324(s32 a0);
extern void func_80019064(void*);
extern void func_801484B0(s32, s32);
extern void func_80148534(s32, s32);

void func_8015F448(s32 arg0) {

    extern void (*D_801862A8[])(void *);

    extern u8 D_80062BD0;
    extern s32 D_801865B4;
    extern s32 D_801865C4;
    extern s32 D_801865D4;
    s32 sp20[2];
    s32 sp28[2];

    if (((*(u32 *)(arg0 + 0x44) & 0x100) && (func_80149884() != 0)) ||
        (((s32 (*)(s32))func_801496D4)(arg0) != 0)) {
        D_801862A8[*(u16 *)arg0]((void *)arg0);
        *(u8 *)(arg0 + 0x1BE) = 0xA;
        ((void (*)(s32))func_80149724)(arg0);
        ((void (*)(s32, s32))func_801477E8)(arg0, 0);
        return;
    }

    if (*(u8 *)(arg0 + 0x245) == 0) {
        if (*(u8 *)(arg0 + 0x244) == 0) {
            if (((s32 (*)(s32))func_80148800)(arg0) & 0x10) {
                *(u8 *)(arg0 + 0x244) = 1;
                *(u8 *)(arg0 + 0x245) = 1;
            }
        } else if (((s32 (*)(s32))func_80148800)(arg0) & 0x80) {
            *(u8 *)(arg0 + 0x244) = 0;
            *(u8 *)(arg0 + 0x245) = 1;
        }
    }

    if (*(u16 *)(arg0 + 0xB8) & 0x3000) {
        if (*(u16 *)(arg0 + 0xB8) & 0x2000) {
            ((void (*)(void *, void *))func_801484B0)(sp20, sp28);
            func_80147324(0x56D);
        } else {
            ((void (*)(void *, void *))func_80148534)(sp20, sp28);
            func_80147324(0x56E);
        }
        ((void (*)(s32 *))func_80019064)(&(*(s32 *)&D_80062BD0));
        ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x25, arg0, *(s16 *)(arg0 + 6),
                      (s16)(*(u16 *)(arg0 + 0xA) - 0x14),
                      *(s16 *)(arg0 + 0xE), 0, 0);
        ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x25, arg0, *(s16 *)(arg0 + 6),
                      (s16)(*(u16 *)(arg0 + 0xA) - 0x14),
                      *(s16 *)(arg0 + 0xE), 1, 0);
    }

    if (*(u16 *)(arg0 + 0xB8) & 0x8000) {
        if (*(u8 *)(arg0 + 0x245) != 0) {
            *(u8 *)(arg0 + 0x245) = 0;
            *(u16 *)(arg0 + 0xB8) = *(u16 *)(arg0 + 0xBA);
            if (((s32 (*)(s32))func_80148980)(arg0) != 0) {
                ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_801865B4);
            } else {
                ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_801865C4);
            }
        }
    } else {
        *(u16 *)(arg0 + 0x246) = *(u16 *)(arg0 + 6);
        *(u16 *)(arg0 + 0x248) = *(u16 *)(arg0 + 0xA);
        *(u16 *)(arg0 + 0x24A) = *(u16 *)(arg0 + 0xE);
        func_80147A84(arg0);
        ((void (*)(s32))func_801473EC)(arg0);
        if (((s32 (*)(s32))func_8014F1F4)(arg0) != 0) {
            *(u16 *)(arg0 + 6) = *(u16 *)(arg0 + 0x246);
            *(u16 *)(arg0 + 0xA) = *(u16 *)(arg0 + 0x248);
            *(u16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0x24A);
        }
    }

    if (((s32 (*)(s32))func_8014FCFC)(arg0) == 0) {
        D_801862A8[*(u16 *)arg0]((void *)arg0);
        *(u8 *)(arg0 + 0x1BE) = 0xA;
        ((void (*)(s32))func_80149724)(arg0);
        ((void (*)(s32, s32))func_801477E8)(arg0, 0xFFE80000);
        ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_801865D4);
        ((void (*)(s32, s32))func_80146E90)(arg0, 0x10);
        return;
    }

    func_8014ED28(arg0);
    func_8014FA04(arg0);
    ((void (*)(s32))func_801725B8)(arg0);
}


DEFINE_func_8015F738()  /* dedup: shared engine-core @0x8015f738 (src/shared) */


DEFINE_func_8015F76C()  /* dedup: shared engine-core @0x8015f76c (src/shared) */


DEFINE_func_8015F7A0()  /* dedup: shared engine-core @0x8015f7a0 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015F7D4);

DEFINE_func_8015F810()  /* dedup: shared engine-core @0x8015f810 (src/shared) */


DEFINE_func_8015F848()  /* dedup: shared engine-core @0x8015f848 (src/shared) */



extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern s32 func_80161208();

void func_8015F89C(void *arg0) {

    extern void (*D_801862A8[])(void *);
    u16 flags = *(u16 *)((u8 *)arg0 + 0xB8);
    if (!(flags & 0x4000)) {
        if (flags & 0x8000) {
            D_801862A8[*(u16 *)arg0](arg0);
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
extern s32 func_80161208();

void func_8015F9A4(void *arg0) {

    extern void (*D_801862A8[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_801862A8[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015FA24()  /* dedup: shared engine-core @0x8015fa24 (src/shared) */


DEFINE_func_8015FA44()  /* dedup: shared engine-core @0x8015fa44 (src/shared) */


DEFINE_func_8015FA78()  /* dedup: shared engine-core @0x8015fa78 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8015FAAC);


extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);
extern void func_8015FBE0(s32 *a0);

void func_8015FAE8(void *arg0) {

    extern void (*D_801862A8[])(void *);
    s32 v;

    v = func_801612B8(arg0, 0);
    if (v == 0 || v == 0x8000) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_801862A8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 3);
        ((void (*)(void *))func_8015BE94)(arg0);
    } else if ((v & 0x4000) != 0) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_801862A8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 4);
        ((void (*)(void *))func_8015C0C4)(arg0);
    } else {
        ((void (*)(void *))func_8015FBE0)(arg0);
    }
}



extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80147324(s32 a0);
extern void func_801553A8(s32 *a0);
extern void func_801553C0(s32 a0);
extern void func_80146CA0(void *a0);


void func_8015FBE0(s32 *param_1)
{

    extern void (*D_801862A8[])(void *);
    extern u8 D_80078EC1;
    extern u16 D_801270C0;
    extern u8 D_800B9A17;
    if (param_1[0x61] < 0) {
        ((void (**)())D_801862A8)[*(u16 *)param_1]();
        ((void (*)(s32 *, s16))func_80147078)(param_1, 0);
        ((void (*)(s32 *))func_80159B70)(param_1);
    } else {
        __asm__ __volatile__("");
        D_80078EC1 = 0;
        ((void (*)(s32 *, s32))func_80154150)(param_1, 0x20);
        ((void (*)(s32 *, s32))func_80154A74)(param_1, 0x18);
        ((void (*)(s32, s32 *, s32, s32, s32, s32, s32))func_80146A6C)(0x16, param_1, 0, 0, 0, 0, 0);
        func_80147324(0x44F);
        ((void (*)(s32 *))func_801553A8)(param_1);
        ((void (*)(s32 *))func_801553C0)(param_1);
        D_801270C0 = 2;
        D_800B9A17 = 0;
        ((void (*)(s32 *))func_80146CA0)(param_1);
    }
}




// @class: struct
// @stuck: none — MATCH (indexed fn-ptr table call + byte-offset struct stores; mirrors sibling func_801599A4 idiom)


extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8015FCC8(void *param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_801862A8[])(void *);
    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_801862A8[*(u16 *)param_1](param_1);
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

    extern unsigned int D_80186604[];
    ((int (*)(int))func_80147324)(0x18);
    *(int *)(param_1 + 0x198) = func_8013767C(D_80186604[*(unsigned char *)(param_1 + 0x1a0)]);
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

    extern void (*D_801862A8[])(void*);
    if ((param_1[0x5c] & 0x8000) != 0) {
        if (param_1[0x5d] == 0) {
            ((void (**)())D_801862A8)[param_1[0]]();
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
    extern void (*D_801862A8[])(void *);
    extern u8 D_80078EC1;
    extern u8 D_80078EC2;
    extern u16 D_801270C0;
    s32 v2;
    u8 cur;

    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_801862A8[*(u16 *)param_1](param_1);
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


extern void (*D_80186680[])(void);

void func_80160138(s32* param_1)
{
    unsigned short idx = *(unsigned short *)((char *)param_1 + 2);
    D_80186680[idx]();
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

    extern void (*D_801862A8[])(void*);
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        ((void (**)())D_801862A8)[*(u16 *)a0]();
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


extern void (*D_80186690[])(void);

void func_8016039C(s32* arg)
{
    unsigned short index = *(unsigned short *)((char *)arg + 2);
    D_80186690[index]();
}


DEFINE_func_801603D8()  /* dedup: shared engine-core @0x801603d8 (src/shared) */


DEFINE_func_80160410()  /* dedup: shared engine-core @0x80160410 (src/shared) */








/* data */

/* callees (engine_core.h canonical sigs) */
extern void func_80149020(s32 *a0);
extern void func_80149034(s32 *a0);
extern u16  func_80148800(s32 *a0);
extern s32  func_80149B54(s32 *a0);
extern void func_80149BAC(s32 *a0);
extern s32  func_80149AA8(s32 *a0);
extern void func_80149AD4(s32 *a0);
extern s32  func_80146E98(s32 a0);
extern u16  func_801487F4(s32 *a0);
extern void func_8015E9B8(s32 *a0);
extern void func_80159B70(void *a0);
extern s32  func_800CF8B4();
extern s32  func_801491C4(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_8015C714(void *a0);
extern s32  func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8015F00C(s32 *a0);

void func_80160534(u8 *p) {

    extern u8  D_80078EC0;
    extern u8  D_80078EBF;
    extern s16 D_801152A0;
    extern void (*D_801862A8[])(void *);
    func_80149020((s32 *)p);
    func_80149034((s32 *)p);
    if ((D_80078EC0 & 0x7F) != 0 && (func_80148800((s32 *)p) & 0x90) != 0) {
        if (D_80078EBF == 0x80) {
            D_801862A8[*(u16 *)p](p);
            func_80147078((s32 *)p, 0x13);
            func_8015F00C((s32 *)p);
            return;
        }
        if (func_80149B54((s32 *)p) != 0) {
            D_801862A8[*(u16 *)p](p);
            func_80149BAC((s32 *)p);
            return;
        }
    }
    if (func_80149AA8((s32 *)p) != 0) {
        D_801862A8[*(u16 *)p](p);
        func_80149AD4((s32 *)p);
        return;
    }
    if (func_80146E98((s32)p) != 0) {
        if ((func_801487F4((s32 *)p) & 8) != 0) {
            D_801862A8[*(u16 *)p](p);
            func_80147078((s32 *)p, 0x11);
            func_8015E9B8((s32 *)p);
        } else {
            D_801862A8[*(u16 *)p](p);
            func_80147078((s32 *)p, 0);
            func_80159B70(p);
        }
        return;
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =
            ((*(u16 *)&D_801152A0) + func_801491C4((s32)p)) & 0xFFF;
    }
    func_80147AD4((s32)p, *(s32 *)(p + 0x234), *(s32 *)(p + 0x238),
                  *(s32 *)(p + 0x23C));
    func_801473EC((s32 *)p);
    if (((s32 (*)(s32 *))func_8014D738)((s32 *)p) != 0) {
        D_801862A8[*(u16 *)p](p);
        func_80147078((s32 *)p, 9);
        func_8015C714(p);
    } else {
        ((s32 (*)(void *))func_80161208)(p);
    }
}


DEFINE_func_801607B8()  /* dedup: shared engine-core @0x801607b8 (src/shared) */


DEFINE_func_801607E4()  /* dedup: shared engine-core @0x801607e4 (src/shared) */


DEFINE_func_80160818()  /* dedup: shared engine-core @0x80160818 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016084C);

DEFINE_func_80160888()  /* dedup: shared engine-core @0x80160888 (src/shared) */


DEFINE_func_801608C0()  /* dedup: shared engine-core @0x801608c0 (src/shared) */



// @class: struct
// @stuck: none — MATCH (function-pointer table folds %lo via extern array indexed by halfword)



extern u16 func_801487F4(s32 *a0);
extern s32 func_80161208();
extern void func_80160A74(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_80160920(unsigned short *param_1)
{

    extern void (*D_801862A8[])(void*);
    if ((((int (*)(void))func_801487F4)() & 8) == 0) {
        ((code *)D_801862A8)[*param_1](param_1);
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

    extern void (*D_801862A8[])(void*);
    if ((((u32 (*)(void))func_801487F4)() & 8) == 0) {
        ((void (**)(u16*))D_801862A8)[*param_1](param_1);
        ((void (*)(u16 *))func_80160A74)(param_1);
    } else {
        ((void (*)(u16 *))func_80161208)(param_1);
    }
}


DEFINE_func_80160A28()  /* dedup: shared engine-core @0x80160a28 (src/shared) */


DEFINE_func_80160A74()  /* dedup: shared engine-core @0x80160a74 (src/shared) */


DEFINE_func_80160ACC()  /* dedup: shared engine-core @0x80160acc (src/shared) */


DEFINE_func_80160B00()  /* dedup: shared engine-core @0x80160b00 (src/shared) */


extern void (*D_801866A4[])(void);

s32 func_80160B34(s32 param)
{
    unsigned short index = *(unsigned short *)((unsigned char *)param + 2);
    D_801866A4[index]();
}


DEFINE_func_80160B70()  /* dedup: shared engine-core @0x80160b70 (src/shared) */


DEFINE_func_80160BB4()  /* dedup: shared engine-core @0x80160bb4 (src/shared) */


DEFINE_func_80160C28()  /* dedup: shared engine-core @0x80160c28 (src/shared) */


DEFINE_func_80160CB4()  /* dedup: shared engine-core @0x80160cb4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015DBD4 in same overlay; dispatch via D_801862A8 + func_80147078/func_80159B70 tail, func_80161208 else)

extern u16 func_80148800(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_80160D10(void *arg0) {

    extern void (*D_801862A8[])(void *);
    if (*(u32 *)((u8 *)arg0 + 0x44) & 0x10) {
        D_801862A8[*(u16 *)arg0](arg0);
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
        D_801862A8[*(u16 *)arg0](arg0);
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

    extern void (*D_801866B4[])(void);
    D_801866B4[*(u16 *)((s32)a0 + 0x2)]();
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

    extern void (*D_801862A8[])(void *);
    func_80149020(a0);
    D_801862A8[*(u16 *)a0](a0);
    func_80147078(a0, 0);
    func_80159B70(a0);
}


DEFINE_func_80161094()  /* dedup: shared engine-core @0x80161094 (src/shared) */


void func_801610FC(void) {
}

DEFINE_func_80161104()  /* dedup: shared engine-core @0x80161104 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80161124);


extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016130C(void*, s32);
void aF80161208(void *a0) __asm__("func_80161208");
void aF80161208(void *a0)
{
    ((s32 (*)(s32, u32))func_8016130C)(a0, func_801612B8(a0, 0));
}


DEFINE_func_80161240()  /* dedup: shared engine-core @0x80161240 (src/shared) */


DEFINE_func_80161278()  /* dedup: shared engine-core @0x80161278 (src/shared) */


DEFINE_func_801612B8()  /* dedup: shared engine-core @0x801612b8 (src/shared) */


extern void func_80161240(void *a0);
extern s32 func_801612B8(void * a0, s32 a1);
#define SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define SHB(x) __asm__("" : "=r"(x) : "0"(x))

extern void func_801599A4(void*);
extern void func_8015BDD0(s32*);
extern void func_8015BF48(s32*);

/* REDRAFT (decay axis: RETURN TYPE). The stored draft had been flipped to
 * `void` to fit the fleet header decl in src/shared/engine_core.h, while the
 * body still `return 1; / return 0;`. gcc-2.7.2 silently drops the $v0 sets in
 * that situation, costing the three `addiu $v0, $zero, 1` / `addu $v0,$zero,$zero`
 * instructions the ASM plainly has. Restored to s32 (§109/§85 — the single call
 * site `func_8016130C(a0, func_801612B8(a0, 1));` discards the result, so the
 * void->s32 widen is caller-neutral and must be fixed on the HEADER side). */

/* RECONCILE (§37/§124 asm-label alias — zero header touch).
 * Gate error: jr_8015C32C.c:3501 conflicting types for `func_8016130C'
 *             :3479 previous declaration.
 * TU line 3479 is `DEFINE_func_80161240()`, whose expansion (engine_core.h:3781)
 * declares `extern void func_8016130C(void *a0, s32 a1);` — a RETURN-TYPE
 * disagreement with this draft's required `s32`.  The third line the gate quoted
 * (:5228 "location of previous definition") is unrelated noise: it is the
 * pre-existing `#define SHB(x)` redefinition *warning* between TU lines 5227 and
 * 5538, present with or without this draft.
 * Fix: the C identifier becomes aF8016130C, so it never collides with the
 * canonical `void func_8016130C` declaration, while the GNU asm label makes the
 * EMITTED symbol `func_8016130C`.  The macro's caller func_80161240 keeps calling
 * the `extern void` spelling and is byte-unaffected (it discards the return).
 * Codegen for this function is untouched — match_one still MATCH.
 * (Alternative, house style, NOT taken here per the no-header-edit rule: widen
 * src/shared/engine_core.h:3781 to `extern s32 func_8016130C(void *a0, s32 a1);`
 * and rename back to the plain name — byte-identical either way.) */

s32 aF8016130C(void *a0, s32 a1) __asm__("func_8016130C");

s32 aF8016130C(void *a0, s32 a1)
{
    if ((a1 == 0) || (a1 == 0x8000)) {
        func_801599A4(a0);
        ((void (*)(void *))func_8015BDD0)(a0);
        return 1;
    }
    if ((a1 & 0x4000) != 0) {
        func_801599A4(a0);
        ((void (*)(void *))func_8015BF48)(a0);
        return 1;
    }
    return 0;
}


extern s32 D_801152BC;

void func_801599A4(void *a0);
void func_8015BDD0(s32 *a0);
void func_8015BF48(s32 *a0);
void func_80015954(s32 a0, s32 a1);

int func_80161374(int a0, unsigned a1)
{
    s32 s0 = (s32)a0;
    s32 v0;

    if (a1 == 0 || a1 == 0x8000) {
        func_801599A4(a0);
        func_8015BDD0((s32 *)a0);
        return 1;
    }

    if ((a1 & 0x4000) == 0) {
        return 0;
    }

    v0 = D_801152BC;
    if (v0 != 0) {
        func_801599A4(a0);
        func_8015BF48((s32 *)a0);
        return 1;
    }

    if (*(s16 *)(s0 + 0xA) < *(s16 *)(s0 + 0x8A)) {
        func_80015954(s0 + 0x88, s0 + 0x4);
        return 0;
    }

    func_801599A4(a0);
    func_8015BF48((s32 *)a0);
    return 1;
}


DEFINE_func_80161418()  /* dedup: shared engine-core @0x80161418 (src/shared) */


DEFINE_func_80161450()  /* dedup: shared engine-core @0x80161450 (src/shared) */


DEFINE_func_80161488()  /* dedup: shared engine-core @0x80161488 (src/shared) */


DEFINE_func_801614E4()  /* dedup: shared engine-core @0x801614e4 (src/shared) */


DEFINE_func_8016151C()  /* dedup: shared engine-core @0x8016151c (src/shared) */


DEFINE_func_80161554()  /* dedup: shared engine-core @0x80161554 (src/shared) */


DEFINE_func_8016158C()  /* dedup: shared engine-core @0x8016158c (src/shared) */


DEFINE_func_801615C4()  /* dedup: shared engine-core @0x801615c4 (src/shared) */


DEFINE_func_8016163C()  /* dedup: shared engine-core @0x8016163C (src/shared) */


DEFINE_func_80161774()  /* dedup: shared engine-core @0x80161774 (src/shared) */


void func_8014C010(s32 a0, s32 a1);
void func_80161D20(s32 a0, s32 a1);

DEFINE_func_80161888()  /* dedup: shared engine-core @0x80161888 (src/shared) */


extern void func_8016151C(void *a0);
extern s32 func_8016163C(s32 a0, u32 a1);
extern s32 func_80161774(int a0, u32 a1);
extern s32 func_80161888(s32 a0, u32 a1);


// @class: sibling-copy (§71) + asm-label alias on the DEFINITION (§37 / §73 return-axis dodge)
// @stuck: none — match_one MATCH (24 ins) AND rtu_match MATCH (24 ins), real TU, zero fleet edits.
//
// DERIVATION (§71 sibling-first, iteration 1):
//   func_80161888 @ src/ov_SC01_077/ov_SC01_077_jr_8015C32C.c:3640 is an already-MATCHED sibling
//   with the identical flag-dispatch skeleton (1 / 0x4000 / 0x2000 -> 1 / 2 / 4, else 0); this
//   target is that function minus the func_80161D20 consumer call.  Body copied verbatim, call
//   dropped.  int/unsigned int spelling kept from the sibling.  MATCH first try.
//
// WHY THE ASM-LABEL ALIAS (this is the only non-obvious part):
//   The fleet canon declares this function inside a shared macro —
//     src/shared/engine_core.h:3567, DEFINE_func_8016151C():
//       extern void func_8016191C(void *a0, s32 a1);
//   but the byte-true body RETURNS s32 ($v0 = 1/2/4/0), so a plain `int func_8016191C(...)`
//   definition dies with `conflicting types for 'func_8016191C'` in the real TU (rtu CC1 FAIL).
//   That is §73's RETURN axis; a `void` def would DCE the $v0 constants outright.
//   §73's prescribed fix is the fleet widen `extern void`->`extern s32` (T2 / R22) — exactly the
//   edit already applied to the three banked siblings in this same macro block
//   (engine_core.h:3546 func_8016163C -> s32, :3553 func_80161774 -> s32, :3560 func_80161888 -> int).
//   The alias reaches the same place at T0 (draft-only, no tracked file touched): the C identifier
//   is aF8016191C so no decl conflicts, while the emitted SYMBOL is func_8016191C.  The macro's
//   caller func_8016151C keeps calling the `extern void` spelling and is byte-unaffected (it
//   discards the return).  Verified by rtu_match, which extracts by symbol name.
//
//   IF the orchestrator prefers house style over zero-touch: widen engine_core.h:3567 to
//     extern s32 func_8016191C(void *a0, s32 a1);
//   (batch it with any other pending §73 widens, one R22) and then the alias line can be deleted
//   and the definition renamed back to `int func_8016191C(int, unsigned int)`.  Byte-identical
//   either way — confirmed: the same body under the plain name is match_one MATCH in isolation.

extern void func_8014C010(int a0, int a1);

int aF8016191C(int param_1, unsigned int param_2) __asm__("func_8016191C");

int aF8016191C(int param_1, unsigned int param_2) {
    if (param_2 & 1) {
        func_8014C010(param_1, 1);
        return 1;
    }
    if (param_2 & 0x4000) {
        func_8014C010(param_1, 1);
        return 2;
    }
    if (param_2 & 0x2000) {
        func_8014C010(param_1, 1);
        return 4;
    }
    return 0;
}


DEFINE_func_8016197C()  /* dedup: shared engine-core @0x8016197c (src/shared) */


DEFINE_func_801619A4()  /* dedup: shared engine-core @0x801619a4 (src/shared) */


DEFINE_func_801619D0()  /* dedup: shared engine-core @0x801619d0 (src/shared) */


DEFINE_func_80161A00()  /* dedup: shared engine-core @0x80161a00 (src/shared) */


DEFINE_func_80161A30()  /* dedup: shared engine-core @0x80161a30 (src/shared) */


DEFINE_func_80161A60()  /* dedup: shared engine-core @0x80161a60 (src/shared) */



extern void func_8014AC10();

void func_80161A90(s32 a0)
{

    extern u8 D_80078E78[];
    extern u8 D_80078EC0;
    u8 *p = D_80078E78;
    s32 t;

    /* INVERTED diamond: the `t = 0` arm must be the THEN arm.
     * (a) the balanced if/else puts `t = 0` AFTER the branch at regalloc time, so t
     *     does not conflict with the entry `lh` temp and both land in $v0 (an
     *     unconditional `s32 t = 0;` before the if costs $v0 -> $a1, 3 mismatches);
     * (b) with the zero-arm as the THEN arm, reorg steals it into the beqz delay slot
     *     and relax_delay_slots drops the `j` -> 34 ins. The other polarity
     *     (`if (x != 0) t = cmp; else t = 0;`) leaves the `j` + an unfilled slot, +2. */
    if (*(s16 *)(a0 + 0x1C8) == 0) {
        t = 0;
    } else {
        t = ((D_80078EC0 & 0x7F) == 6);
    }
    if (t != 0) {
        /* forces the `lhu 0x1C8($a0)` reload: without it cse reuses the entry `lh`
         * value across the join and folds the reload away. */
        __asm__ __volatile__("" ::: "memory");
        *(u16 *)(a0 + 0x1C8) -= 1;
        /* zero-byte 2nd set of p: kills p's qty-const in cse's skipped-block walk, so
         * `p[0x48]` stays `lbu 0x48($v1)` off the hoisted lui/addiu instead of being
         * folded back into a fresh %hi/%lo pair (cse_expr §H find_best_addr). */
        __asm__("" : "=r"(p) : "0"(p));
    }
    if ((p[0x48] & 0x7F) == 6) {
        if (*(s16 *)(a0 + 0x1C8) == 0) {
            func_8014AC10(0x3B);
        }
    }
}


DEFINE_func_80161B18()  /* dedup: shared engine-core @0x80161b18 (src/shared) */


DEFINE_func_80161B84()  /* dedup: shared engine-core @0x80161b84 (src/shared) */


s32 func_801497A8(s32 *a0);
void func_801599A4(void *a0);
void func_80149864(void);

s32 func_80161BE0(s32 *a0)
{
    s32 result = func_801497A8(a0);
    if (result != 0) {
        func_801599A4(a0);
        ((void (*)(void *))func_80149864)(a0);
        return 1;
    }
    return 0;
}



extern void func_80147324();

/* RECONCILE (§17a-1/§20): the TU already declares
 *   extern void func_80161C24(s32, s32);   (jr_8015C32C.c:1474 / :1417)
 * so the definition must use (int, int); the unsigned semantics of param_2
 * are restored by a cast at each use (codegen-neutral: sltiu + index math). */
void func_80161C24(int param_1, int param_2)
{

    extern unsigned short D_801866C4[];
    extern unsigned short D_801866C6[];

    if ((unsigned int)param_2 < 8) {
        if (*(u8 *)(param_1 + 0xDA) != 0) {
            func_80147324(D_801866C4[(unsigned int)param_2 * 2]);
            *(u8 *)(param_1 + 0xDA) = 0;
        } else {
            func_80147324(D_801866C6[(unsigned int)param_2 * 2]);
            *(u8 *)(param_1 + 0xDA) = 1;
        }
    }
}




// @class: struct
// @stuck: none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

extern void func_80147324(s32 arg0);

void func_80161C98(int param_1, u32 param_2)
{

    extern u16 D_801866E4[];
    if (param_2 < 8) {
        func_80147324(D_801866E4[param_2]);
    }
    return;
}



// @class: plumbing
// @stuck: none — MATCH (20 ins)
// DECAY AXIS: return type. The stored draft declared `s32 func_80161CD0(...)` with no
// return statement. That kept $v0 live-out at the epilogue, so gcc-2.7.2's delayed-branch
// pass refused to speculatively fill the second `beqz $v0` delay slot from the fall-through
// with `sll $v0, $s0, 1` — costing one extra nop (21 vs 20 ins) and shifting both branch
// displacements. Declaring the function `void` makes $v0 dead at the return and the fill
// happens. Same return-type axis as the wave, opposite direction (s32 -> void).
// param_2 must be UNSIGNED: the guard assembles as `sltiu $v0, $s0, 0x8`.
//
// RECONCILE (§37/§124 asm-label alias) — the ONLY change vs the uc2 draft; the body is
// byte-identical and untouched.
//   The real TU src/ov_SC01_077/ov_SC01_077_jr_8015C32C.c already carries the m2c canonical
//   declaration
//       :23   extern s32 func_80161CD0(s32 a0, s32 a1);   /* match-first, arity 2 */
//       :1207 extern s32 func_80161CD0(s32 a0, s32 a1);
//   so a plain `void func_80161CD0(int, unsigned int)` definition dies with
//       conflicting types for `func_80161CD0' / previous declaration ... (rtu_match CC1 FAIL).
//   This is the RETURN axis (s32 vs void) plus the param-2 signedness axis, and BOTH spellings
//   are load-bearing for the 20-instruction codegen — conforming the definition to the
//   declaration (escape #1) would perturb bytes, so it is not available here.
//   The alias fixes it at T0: the C identifier is aF80161CD0 (no declaration to collide with)
//   while the EMITTED SYMBOL is func_80161CD0. In-TU callers keep using the `extern s32`
//   spelling and are byte-unaffected (they discard the return). Zero tracked files touched;
//   no header edit is even possible/needed — grep shows func_80161CD0 has NO declaration in
//   include/ or src/shared/, the conflict is purely TU-local m2c boilerplate.
//   Exactly the pattern already banked at src/ov_SC03_099/ov_SC03_099_jr_8015C32C.c:3503
//   for the sibling func_8016191C.
//
//   NOTE on the third gate diagnostic (`:5223 note: location of previous definition`): that is
//   a RED HERRING, unrelated to this function. It is the pre-existing CPP note paired with
//   `:5533 warning: "SHB" redefined` — the TU defines the SHB scheduling-barrier macro twice
//   (post-splice :5222 with __volatile__, :5533 without). It is a warning, present with or
//   without this draft, and it does not fail cc1.

extern int func_800CF8B4();
extern void func_80147324(int arg0);

void aF80161CD0(int param_1, unsigned int param_2) __asm__("func_80161CD0");

void aF80161CD0(int param_1, unsigned int param_2)
{

    extern unsigned short D_801866F4;
    if (param_2 < 8) {
        if (func_800CF8B4() != 0) {
            func_80147324((&D_801866F4)[param_2]);
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80161D20);

DEFINE_func_80161D58()  /* dedup: shared engine-core @0x80161d58 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80161D88);

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
    extern u8 * D_801C8598[];
    extern u8 D_80186714[];
    extern u8 D_80186734[];
    extern u8 D_801C85A4[];
    extern u8 D_801C85CC[];
    extern u8 D_801C85E4[];

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
            D_801C8598[0] = p;
            func_80024054(&D_80186714, &D_801C85A4);
            func_8001CE28(p, &D_801C85A4);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -(s32)(u16)D_800AF7BE / 2 + 0x28;
        }

        if (D_800B5C10 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65E0));
            D_801C8598[1] = p;
            func_80024054(&D_80186734, &D_801C85CC);
            func_8001CE28(p, &D_801C85CC);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -(s32)(u16)D_800AF7BE / 2 + 0x30;
        }

        if (D_800B5C48 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x6618));
            D_801C8598[2] = p;
            func_800242D0((s16)func_801620C4(), &D_801C85E4, 0x84);
            func_8001CE68(p, &D_801C85E4);
            D_800B5C74 = 1;
            D_800B5C50 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -(s32)(u16)D_800AF7BE / 2 + 0x10;
        }

        func_800242D0((s16)func_801620C4(), &D_801C85E4, 0x84);
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

    extern int D_801C8598[];
    int *p;
    int i;

    func_800291C8(8, 0);
    i = 0;
    p = D_801C8598;
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
    extern s32 D_80186748;
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
        return (s32)&D_80186748;
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
                return (s32)&D_80186748;
            }
            i++;
            if ((u32)s1[0x38] < (u32)lo) {
                return (s32)&D_80186748;
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

    extern int D_801C8598[];
    int *p;
    int i;

    ((int (*)(int, int))func_80029124)(0x141, 1);
    ((int (*)(int, int))func_800291C8)(8, 0);
    i = 0;
    p = &D_801C8598;
    do {
        ((int (*)(int, int))func_80016714)(*p, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}




void func_80162330(void *a0) {

    extern void (*D_8018676C[])(void);
    D_8018676C[*(u8 *)((s32)a0 + 0x15)]();
}


DEFINE_func_8016236C()  /* dedup: shared engine-core @0x8016236c (src/shared) */


DEFINE_func_801623B8()  /* dedup: shared engine-core @0x801623b8 (src/shared) */


DEFINE_func_80162414()  /* dedup: shared engine-core @0x80162414 (src/shared) */


extern s32 func_800291DC(s32);








s32 func_80162438(s32 _unused0) {

    extern u8 D_80078EB0;
    extern u8 D_800AF630[];
    extern void func_80024054(void *, void *);
    extern void func_8001CE28(void *, void *);
    extern void func_8001CE68(void *, void *);
    extern void func_800242D0(s32, void *, s32);
    extern s32 func_801626B8(void);
    extern void func_80162760(void);
    extern u8 D_80186778[];
    extern s32 D_80186790;
    extern u8 D_801C85FC[];
    extern u8 D_801C8624[];
    extern u8 D_801C8640[];
    extern int D_801C85F0[];
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
            D_801C85F0[0] = (s32)item;
            func_80024054(D_80186778, D_801C85FC);
            func_8001CE28(item, D_801C85FC);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -D_800AF7BE / 2 + 0x28;
        }
        if (D_800B5C10 == 0) {
            register u8 *t __asm__("$2") = base + 0x65E0;
            item = t;
            D_801C85F0[1] = (s32)item;
            func_80024054(((u8 *)&D_80186790), D_801C8624);
            func_8001CE28(item, D_801C8624);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -D_800AF7BE / 2 + 0x30;
        }
        if (D_800B5C48 == 0) {
            register u8 *t __asm__("$2") = base + 0x6618;
            item = t;
            D_801C85F0[2] = (s32)item;
            func_800242D0((s16)func_801626B8(), D_801C8640, 0x84);
            func_8001CE68(item, D_801C8640);
            D_800B5C74 = 1;
            D_800B5C50 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -D_800AF7BE / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_801C8640, 0x84);
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

    extern int D_801C85F0[];
    int *p;
    int i;

    func_800291C8(18, 0);
    i = 0;
    p = D_801C85F0;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}


DEFINE_func_801627C0()  /* dedup: shared engine-core @0x801627c0 (src/shared) */


extern void func_801627C0(void);

// @class: struct
// @stuck: none — MATCH (19 ins, relocation-masked)
//
// Tiny dispatcher: byte count at D_8011F750 (offset 0 of a 0x58-byte ctl struct;
// cf. func_801627C0 which calls func_80016714(&D_8011F750, 0x58)). If nonzero,
// call D_801867B0[count - 1]() through a word-stride fn-pointer table.
//
// Two idioms combined to match gcc-2.7.2 -O2:
//  1. The target MATERIALIZES &D_8011F750 (lui;addiu %lo) into $a0 before the lbu
//     instead of folding %lo into the load. A direct global byte read always
//     %lo-folds (lui;lbu %lo), so force the full-address materialization with the
//     §21 re-tie barrier __asm__ __volatile__("":"=r"(p):"0"(p)) and pin the
//     pointer to $a0 with register __asm__("$4") to get the exact register.
//  2. Writing `idx = idx - 1;` as its OWN statement (not inline D_801867B0[count-1])
//     keeps the array index/decrement separate so %lo(D_801867B0) folds into the
//     dispatch load (lw %lo(...)($at)) — the inline form instead constant-folds the
//     -1*4 into a -4 load offset and drops the %lo fold (1 ins short, schedule off).


void func_801627E8(void)
{

    extern s32 D_8011F750;               /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
    extern void (*D_801867B0[])(void);   /* word-stride table of dispatch fn pointers */
    register u8 *p __asm__("$4") = (u8 *)&D_8011F750;
    s32 idx;

    __asm__ __volatile__("" : "=r"(p) : "0"(p));   /* materialize &D_8011F750 into $a0 (defeat %lo-fold of the lbu) */
    idx = *p;
    if (idx != 0) {
        idx = idx - 1;
        D_801867B0[idx]();
    }
}




void func_80162834(void *a0) {

    extern void (*D_801867B4[])(void);
    D_801867B4[*(u8 *)((s32)a0 + 0x1)]();
}



// @class: plumbing
// @stuck: none — MATCH (stub: alloc + global init + two calls; $s0 holds param_1 across calls)

extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);


void func_80162870(s32 param_1) {

    extern u8 D_800B5CB8;
    extern s32 D_801867A4;
    extern s32 D_800B5CBC;
    extern u8 D_800B5CDF;
    extern s32 D_800B5CEC;
    *(s32 *)(param_1 + 8) = (s32)&D_800B5CB8;
    func_8001CB6C(&D_800B5CB8, (s32)&D_801867A4, 0x250, 0x1A0);
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

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80162CCC);

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


DEFINE_func_80162FF4()  /* dedup: shared engine-core @0x80162ff4 (src/shared) */


DEFINE_func_801630C4()  /* dedup: shared engine-core @0x801630c4 (src/shared) */


DEFINE_func_80163194()  /* dedup: shared engine-core @0x80163194 (src/shared) */


DEFINE_func_80163234()  /* dedup: shared engine-core @0x80163234 (src/shared) */


DEFINE_func_8016325C()  /* dedup: shared engine-core @0x8016325c (src/shared) */


DEFINE_func_801632E0()  /* dedup: shared engine-core @0x801632e0 (src/shared) */


DEFINE_func_801632F0()  /* dedup: shared engine-core @0x801632f0 (src/shared) */


DEFINE_func_80163328()  /* dedup: shared engine-core @0x80163328 (src/shared) */


DEFINE_func_801633A8()  /* dedup: shared engine-core @0x801633a8 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80163408);

DEFINE_func_8016345C()  /* dedup: shared engine-core @0x8016345c (src/shared) */



// @class: struct
// @stuck: none — MATCH (unaligned 8-byte memcpy from global into stack buffer, then forward to callee)


extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u16 * a5);

void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5)
{

    extern char aD801C7E20_801634D8[8] __asm__("D_801C7E20");
    char buf[8];

    memcpy(buf, aD801C7E20_801634D8, 8);
    ((void (*)(s32, u16, u16, s32, u16, s32))func_80163534)(param_1, param_2, param_3, param_4, param_5, (s32)buf);
}


extern void func_80163664(s32, u16, u16, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32);

void func_80163534(a0, a1, a2, a3, a4, a5)
    s32 a0;
    u16 a1;
    u16 a2;
    s32 a3;
    u16 a4;
    u16 *a5;
{

    extern s32 D_80115100;
    extern s32 D_80115200;
    extern s32 D_80115204;
    extern s32 D_80115208;
    extern u16 D_80126B18[];
    extern u16 D_801270B0[];
    extern u16 D_801270B2;
    extern u16 D_801270B4;
    extern u16 D_80126B1A[];
    extern u16 D_80126B1C;
    extern s32 D_80114EB0;
    extern s32 D_80114EC8;
    extern s32 D_8011DAF0;
    extern s32 D_80115298;
    extern s32 D_80126734;
    s32 *p = &D_80115200;

    *p = 0;
    D_80115204 = 0;
    D_80115208 = 0;

    D_801270B0[0] = *(u16 *)(a0 + 0x44) + a5[0];
    D_801270B2 = *(u16 *)(a0 + 0x46) + a5[1];
    D_801270B4 = *(u16 *)(a0 + 0x48) + a5[2];

    D_80126B18[0] = *(u16 *)(a0 + 0x6) + a5[0];
    D_80126B1A[0] = *(u16 *)(a0 + 0xA) + a5[1];
    D_80126B1C = *(u16 *)(a0 + 0xE) + a5[2];

    *p = ((s32 (*)(s32, u16, u16, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32))func_80163664)(a0, a1, a2, (s32)D_801270B0, (s32)D_80126B18,
                               (s32)&D_80114EB0, (s32)&D_80114EC8, (s32)&D_80115100,
                               (s32)&D_8011DAF0, a3, a4, (s32)&D_80115298,
                               (s32)&D_80126734);
}


DEFINE_func_80163664()  /* dedup: shared engine-core @0x80163664 (src/shared) */


DEFINE_func_801636D0()  /* dedup: shared engine-core @0x801636d0 (src/shared) */


DEFINE_func_80163764()  /* dedup: shared engine-core @0x80163764 (src/shared) */


DEFINE_func_8016380C()  /* dedup: shared engine-core @0x8016380c (src/shared) */


extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern void func_80015954(s32 a0, s32 a1);
extern void *memcpy(void *, const void *, u32);
s32 func_801638A0(u8 *a0, s32 a1) {

    extern s16 D_801152AA;
    u8 buf[8];
    s16 d;
    s32 p;
    __builtin_memcpy(buf, a0 + 0x44, 8);
    p = (s32)(a0 + 4);
    func_80015978(p, (s32 *)a1);
    if (func_80135004(1, buf, a1) != 0) {
        func_80015954(a1, p);
        d = D_801152AA;
        if (d >= -0x578) {
            return 0x8000;
        }
        if (d >= -0xBCB) {
            return 0x4000;
        }
        return 0x2000;
    }
    return 0;
}


DEFINE_func_80163950()  /* dedup: shared engine-core @0x80163950 (src/shared) */




void func_80163A58(void *a0) {

    extern void (*D_801867BC[])(void);
    D_801867BC[*(u16 *)((s32)a0 + 0x2)]();
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
    extern Blk8 D_801C7E28;
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

    in = D_801C7E28;
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

DEFINE_func_80164418()  /* dedup: shared engine-core @0x80164418 (src/shared) */


DEFINE_func_80164530()  /* dedup: shared engine-core @0x80164530 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected (fn-ptr table dispatch via u16 idx, $s0 holds *(s32*)(p+0x20) across the call)

extern void func_80162D28(s32 *a0);

void func_80164744(s32 param_1)
{

    extern void (*D_80186810[])(void);
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x20);
    D_80186810[*(u16 *)(param_1 + 2)]();
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
    extern s32 D_801867D8;
    extern u16 D_8018680C;
    extern s16 D_8018680A;
    extern s16 D_80186808;
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_801867D8;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        D_8018680C = 0x80;
        D_8018680A = 0x80;
        D_80186808 = 0x80;
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


extern void func_80162CCC(void);
extern void func_80164ACC();

// @class: regalloc-order — wave-3 real-TU crack (§42a); cracked at Max.
// Fix: D_8018680C read needs direct-addressed `lhu` (u16). Cannot use `*(u16*)&D_8018680C`
// (forces &sym into a held reg -> drift) NOR a block-scoped `extern u16` (conflicting-types
// ERROR vs the ambient s16, cc1 exit 33). Solution: flip the file-scope decl (5802) to u16 —
// byte-neutral to the only other user (func_801647A4 store-only) — and reference directly.


void func_80164930(s32 param_1) {

    extern s32 D_8011F9D0;
    extern s16 D_80186808;
    extern s16 D_8018680A;
    extern u16 D_8018680C;
    int iVar3 = *(int *)(((int)param_1) + 0x20);
    if (*(int *)(((int)param_1) + 0x50) == 0) {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x100;
        short nv;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + 0x71;
        nv = D_8018680C - 8;
        D_8018680C = nv;
        D_8018680A = nv;
        D_80186808 = nv;
        if (nv < -0x80) {
            int i, lim;
            Ent_80164930 *p;
            for (i = 0, lim = 0x19, p = ((Ent_80164930 *)&D_8011F9D0); i < 0x14; i++) {
                if (p->f0 == lim && p->f50 != 0) {
                    ((void(*)(Ent_80164930 *))func_80162CCC)(p);
                }
                p++;
            }
            ((void(*)(Ent_80164930 *))func_80162CCC)((Ent_80164930 *)((int)param_1));
        } else {
            ((void(*)(int))func_80164ACC)(((int)param_1));
        }
    } else {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x40;
        u16 uVar2;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        uVar2 = *(u16 *)(iVar3 + 0x1a) - 0x200;
        *(u16 *)(iVar3 + 0x1a) = uVar2;
        if ((int)((unsigned)uVar2 << 0x10) < 0) {
            *(short *)(iVar3 + 0x1a) = 0;
        }
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) - 0x71;
    }
}


DEFINE_func_80164A74()  /* dedup: shared engine-core @0x80164a74 (src/shared) */


DEFINE_func_80164ACC()  /* dedup: shared engine-core @0x80164acc (src/shared) */




void func_80164BA0(void *a0) {

    extern void (*D_8018681C[])(void);
    D_8018681C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80146578(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80164DB0(void);


void func_80164BDC(s32 param_1)
{

    extern u8 D_801C8650;
    extern u8 D_801C8651;
    extern u8 D_801C8652;
    extern u8 D_801C8653;
    extern u8 D_801C8654;
    extern u8 D_801C8655;
    extern u8 D_801C8656;
    extern u8 D_801C8657;
    register s32 p1   __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base __asm__("$18");  /* $s2 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_801C8650;
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CD50(iVar1, base);
        ((void (*)(s32, s32))func_800233CC)(base, 0x60);
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        D_801C8651 = 0xf0;
        *(u8 *)base = 0xf0;
        D_801C8652 = 0xc0;
        D_801C8656 = 0;
        D_801C8655 = 0;
        D_801C8654 = 0;
        D_801C8657 = 0;
        D_801C8653 = 0;
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







s32 func_80164E40(void) {

    extern u8 D_801C8650;
    extern u8 D_801C8651;
    extern u8 D_801C8652;
    u8 *p = &D_801C8650;
    if (*p != 0) {
        *p -= 0x10;
    }
    if (D_801C8651 != 0) {
        D_801C8651 -= 0x10;
    }
    if (D_801C8652 != 0) {
        D_801C8652 -= 0x10;
    }
    return *(s32 *)p == 0;
}




void func_80164EA4(void *a0) {

    extern void (*D_8018682C[])(void);
    D_8018682C[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

  /* stride 0x10 */

extern void func_80165124(void *a0);
extern void func_80146CA0(void *a0);

void func_80164EE0(int param_1)
{

    extern DStruct D_801C869C[];
    int i;

    for (i = 7; i >= 0; i--) {
        D_801C869C[i].f0 = 0;
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
// p = &D_801C8690[i] each iteration (NOT p++) so gcc reduces base+i*0x10 into
// a SINGLE pointer IV with immediate offsets 0/8/0xC. Hand-incrementing p makes
// combine_givs split the field offsets into a second pointer IV (+2 ins).




s32 func_80165140(s32 param_1) {
    extern Slot D_801C8690[8];

    int i;
    Slot *p;
    for (i = 0; i < 8; i++) {
        p = &D_801C8690[i];
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

extern void func_80165240(void *param_1, void *param_2, void *param_3);

void func_801651B8(void * param_1)
{

    extern s32 D_801C8690;
    register s32 *puVar1 __asm__("$16"); /* $s0 */
    register s32 iVar2 __asm__("$17");   /* $s1 */
    register s32 p __asm__("$18");        /* $s2 */

    p = param_1;
    ((s32 (*)(s32, s32, s32))func_80165240)(p, p + 0x2c, p + 0x50);
    iVar2 = 0;
    puVar1 = &D_801C8690;
    do {
        if (puVar1[3] != 0) {
            s32 a0v = p;
            __asm__ __volatile__("" : "=r"(a0v) : "0"(a0v));
            ((s32 (*)(s32, s32, s32))func_80165240)(a0v, (s32)puVar1, (s32)(puVar1 + 2));
            puVar1[3] = puVar1[3] + -1;
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 4;
    } while (iVar2 < 8);
}









extern s32  func_80017DC4(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void func_80016ED4(void *a0);



void func_80165240(void *param_1, void *param_2, void *param_3)
{

    extern u8  D_80186840[];
    extern u32 D_80186860, D_80186864, D_80186868, D_8018686C;
    u8 prim[0x40];   /* $sp+0x10 .. 0x50 */
    u8 mat[0x20];    /* $sp+0x50 .. 0x70 */
    u8 *p = prim;

    func_80017DC4(param_2, mat);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_80186840[0x00], p);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_80186840[0x08], prim + 0x08);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_80186840[0x10], prim + 0x10);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mat, &D_80186840[0x18], prim + 0x18);

    *(s16 *)(prim + 0x04) = 3;
    prim[0x38] = 0x2c;
    *(u32 *)(prim + 0x20) = D_80186868;
    *(u32 *)(prim + 0x24) = D_80186860;
    *(u32 *)(prim + 0x28) = D_8018686C;
    *(u32 *)(prim + 0x2c) = D_80186864;
    *(struct W4 *)(prim + 0x30) = *(struct W4 *)param_3;
    *(u32 *)(prim + 0x34) = 0x50000000;

    func_80016ED4(p);
}


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
    extern void (*D_80186870[])(void);
    u8 *s1 = D_80078E78;

    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 != 0x1A) {
        if ((*(s32 *)(arg0 + 0x1F8) & 0x80FFFFFF) == 0) {
            if (func_80165658(arg0, D_80078EC1) & 0x80) {
                ((void (*)(s32))D_80186870[D_80078EC1 & 0x7F])(arg0);
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
    extern void (*D_80186870[])(void);
    if (D_80078EC5 & 0x80) {
        ((void (*)(void))func_80165B28)();
    } else {
        D_80186870[D_80078EC1 & 0x7F]();
    }
}


DEFINE_func_801655E4()  /* dedup: shared engine-core @0x801655e4 (src/shared) */


DEFINE_func_80165624()  /* dedup: shared engine-core @0x80165624 (src/shared) */




u8 func_80165658(s32 a0, s32 a1) {

    extern u8 D_801868EC[];
    return D_801868EC[a1 & 0x7F];
}




void func_80165670(s32 a0, s32 a1) {

    extern s32 D_8018690C[];
    extern s32 D_80078EC8;
    D_80078EC8 = D_8018690C[a1 & 0x7F];
}


DEFINE_func_80165694()  /* dedup: shared engine-core @0x80165694 (src/shared) */




u8 func_801656D0(s32 a0, s32 a1) {

    extern u8 D_80186988[];
    return D_80186988[a1 & 0x7F];
}




u8 func_801656E8(s32 a0, s32 a1) {

    extern u8 D_801869A8[];
    return D_801869A8[a1 & 0x7F];
}




u8 func_80165700(s32 a0, s32 a1) {

    extern u8 D_801869C8[];
    return D_801869C8[a1 & 0x7F];
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801659DC);

void func_80165A18(void) {
}

DEFINE_func_80165A20()  /* dedup: shared engine-core @0x80165a20 (src/shared) */


DEFINE_func_80165A50()  /* dedup: shared engine-core @0x80165a50 (src/shared) */


DEFINE_func_80165A78()  /* dedup: shared engine-core @0x80165a78 (src/shared) */




void func_80165AC8(void) {

    extern u8 D_80078EC1;
    extern void (*D_80186A64[])(void);
    D_80186A64[D_80078EC1 & 0x7F]();
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

    extern void (*D_80186AE0[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_80186AE0[*(u8 *)((s32)a0 + 0x197)]();
}


DEFINE_func_80165B6C()  /* dedup: shared engine-core @0x80165b6c (src/shared) */


DEFINE_func_80165BB4()  /* dedup: shared engine-core @0x80165bb4 (src/shared) */


DEFINE_func_80165BFC()  /* dedup: shared engine-core @0x80165bfc (src/shared) */


DEFINE_func_80165C58()  /* dedup: shared engine-core @0x80165c58 (src/shared) */


DEFINE_func_80165C78()  /* dedup: shared engine-core @0x80165c78 (src/shared) */


DEFINE_func_80165CA0()  /* dedup: shared engine-core @0x80165ca0 (src/shared) */



void func_80165E2C(u16 *arg0) {

    extern M2C_UNK D_801C7E30;
    func_8001534C(0, &D_801C7E30, 0x80, 0x80, 0, 0);
    func_800153CC(1, *arg0, 0xA8, 0x80, 0x40, 0);
}


DEFINE_func_80165E90()  /* dedup: shared engine-core @0x80165e90 (src/shared) */


extern void func_80013F3C(s32 a0);
extern void func_80020F34(s32 a0, s32 a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2)
{
    s32 buf[8];
    func_80013F3C((s32)buf);
    func_80020F34((s32)buf, *(s32 *)((u8 *)arg0 + 0x20) + 0x18);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(buf, arg1, arg1);
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(buf, arg2, arg2);
}




void func_80166018(void *a0) {

    extern void (*D_80186AEC[])(void);
    D_80186AEC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80166054()  /* dedup: shared engine-core @0x80166054 (src/shared) */


s32 func_80128ED8(s32 param_1, s32 *param_2);
void func_80146C3C(u8 *a0);
void func_800D22E4(s32 a0);

void func_801661CC(s32 param_1)
{
  s32 v0;

  v0 = func_80128ED8(*(s32 *)(param_1 + 0x20), (s32 *)(param_1 + 0x24));
  if (v0 != 0) {
    func_80146C3C((u8 *)param_1);
  } else {
    func_800D22E4(param_1);
    *(s32 *)(param_1 + 0x10) = (*(s32 *)(param_1 + 0x10) >> 1) + (*(s32 *)(param_1 + 0x10) >> 2);
    *(s32 *)(param_1 + 0x18) = (*(s32 *)(param_1 + 0x18) >> 1) + (*(s32 *)(param_1 + 0x18) >> 2);
  }
}


DEFINE_func_80166244()  /* dedup: shared engine-core @0x80166244 (src/shared) */


DEFINE_func_8016629C()  /* dedup: shared engine-core @0x8016629c (src/shared) */


DEFINE_func_801662F4()  /* dedup: shared engine-core @0x801662f4 (src/shared) */


DEFINE_func_8016634C()  /* dedup: shared engine-core @0x8016634c (src/shared) */


DEFINE_func_801663A4()  /* dedup: shared engine-core @0x801663a4 (src/shared) */




void func_801663FC(void *a0) {

    extern void (*D_80186AF4[])(void);
    D_80186AF4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80166438()  /* dedup: shared engine-core @0x80166438 (src/shared) */


DEFINE_func_801665B4()  /* dedup: shared engine-core @0x801665b4 (src/shared) */




void func_80166618(void *a0) {

    extern void (*D_80186BBC[])(void);
    D_80186BBC[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80166654(void *a0) {

    extern void (*D_80186BCC[])(void);
    D_80186BCC[*(u16 *)((s32)a0 + 0x2)]();
}



   /* 12-byte sub-table record (stride 0xC) */


extern s32 func_80017758(void *a0, void *a1);

s32 func_80166690(s32 param_1, s32 param_2)
{

    extern Blk20 aD800AE620 __asm__("D_800AE620");
    extern u8 D_801C8710[];
    Frame_80166690 c;
    Blk20 blk;
    Rec_80166690 *sub;
    Rec_80166690 *pv;
    u8 *rec;
    int i6;
    int lt2;
    int p2;
    unsigned int uVar7, uVar8, uVar9;
    int iVar3;
    unsigned int w9, w7, w, t, w3b;
    int w3;
    short sVar10;
    register unsigned int zr __asm__("$0");

    blk = aD800AE620;
    i6 = (short)param_1;
    c.tag = 0x50000000;
    rec = &D_801C8710[i6 * 0xC4];
    sVar10 = 0;
    if (rec[0] == 0) {
        return 0;
    }
    sub = (Rec_80166690 *)(rec + 4);
    uVar9 = rec[1];
    uVar8 = rec[3];
    uVar7 = uVar8 >> 1;
    iVar3 = rec[2];
    w3 = iVar3 - 1;
    iVar3 = w3 + zr;
    if (w3 != -1) {
        lt2 = i6 < 2;
        p2 = (short)param_2;
        do {
            pv = &sub[(short)uVar9];
            c.v0 = pv->h[0];
            c.v1 = pv->h[1];
            c.v2 = pv->h[2];
            c.w0 = pv->h[3];
            c.w1 = pv->h[4];
            c.w2 = pv->h[5];
            sVar10 = sVar10 + 1;

            if (lt2) {
                if (p2 == 0) {
                    t = uVar8 + zr;
                    c.c12 = t; c.c02 = t;
                    t = uVar7 + zr;
                } else {
                    w = ((int)(uVar8 << 16) >> 17) + ((int)(uVar8 << 16) >> 19);
                    uVar7 = w + zr;
                    c.c12 = w; c.c02 = w;
                    t = uVar8 + zr;
                }
                c.c11 = t; c.c01 = t; c.c10 = t; c.c00 = t;
            } else {
                t = uVar8 + zr;
                c.c10 = t; c.c00 = t;
                t = uVar7 + zr;
                c.c12 = t; c.c02 = t; c.c11 = t; c.c01 = t;
            }

            w9 = uVar9 - 1;
            uVar9 = w9 + zr;
            if ((int)(w9 << 16) < 0) {
                uVar9 = 0xF;
            }
            pv = &sub[(short)uVar9];
            c.v3 = pv->h[0];
            c.v4 = pv->h[1];
            c.v5 = pv->h[2];
            c.w3 = pv->h[3];
            c.w4 = pv->h[4];
            uVar8 = uVar8 - 0x10;
            w7 = uVar7 - 0x10;
            uVar7 = w7 + zr;
            c.w5 = pv->h[5];
            if ((int)(w7 << 16) < 0) {
                uVar7 = 0;
            }

            if (lt2) {
                if (p2 == 0) {
                    t = uVar8 + zr;
                    c.c32 = t; c.c22 = t;
                    t = uVar7 + zr;
                } else {
                    t = uVar7 + zr;
                    c.c32 = t; c.c22 = t;
                    t = uVar8 + zr;
                }
                c.c31 = t; c.c21 = t; c.c30 = t; c.c20 = t;
            } else {
                t = uVar8 + zr;
                c.c30 = t; c.c20 = t;
                t = uVar7 + zr;
                c.c32 = t; c.c22 = t; c.c31 = t; c.c21 = t;
            }

            __asm__ __volatile__("" :: "r"(iVar3));
            func_80017758(&c, &blk);
            w3b = iVar3 - 1;
            iVar3 = w3b + zr;
        } while ((short)w3b != -1);
    }
    return (short)sVar10;
}


extern void func_801484B0(s32 a0, s32 a1);
extern void func_80148534(s32 a0, s32 a1);
extern void func_80149350(s32 arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);

/* func_80166994 — trail/afterimage ring recorder (0xC4-stride Trail records at D_801C8710).
 * param_2: 0=init, 1=advance(record), 2=fadeout; param_3: trail index (s16); param_4: divisor (s16).
 *
 * K&R definition: true s16 params => callee-side lazy per-use narrow/extend with raw pseudos
 * (s3/t0/s4 hold raw a1/a2/a3; first-use extension allocates IN PLACE into the arg reg), while
 * the promoted K&R type (int x4) stays compatible with the canon-sig s32 prototype in the TU.
 * Returns s32 (v0=1 when the fadeout completes, else 0) => the //@EDIT above flips the split's
 * canon-sig prototype return type, AND engine_core.h needs the once-global ec_edit (all 5 sites,
 * byte-neutral: every caller discards the result):
 *   ec_edit old: "extern void func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 *   ec_edit new: "extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 * Without the ec_edit, cc1 hard-errors (conflicting types vs the void decls in DEFINE_ macros).
 *
 * Fully block-scoped (typedefs + externs inside the body) so the crack propagates ×134 via
 * family_remap with zero file-scope footprint. No register pins.
 */
s32 func_80166994(param_1, param_2, param_3, param_4)
    s32 param_1;
    s16 param_2;
    s16 param_3;
    s16 param_4;
{
    extern u8 D_801C8710[];
    extern void RotTransSV(s32, s32, void*);
    extern s32 VectorNormalSS(void *a0, void *a1);

    Trail *p = &((Trail *)D_801C8710)[param_3];
    s32 uVar6 = *(s32 *)(param_1 + 0x34);
    s16 v10[4];
    s16 v18[4];
    s16 v20[4];
    s16 v28[4];
    s16 out[4];
    s32 c;

    switch (param_2) {
    case 0:
        p->flag = 1;
        p->count = 0;
        p->idx = 0;
        p->timer = 0xf4;
        break;
    case 1:
        v20[0] = p->e[p->idx].f0;
        v20[1] = p->e[p->idx].f1;
        v20[2] = p->e[p->idx].f2;
        v28[0] = p->e[p->idx].f3;
        v28[1] = p->e[p->idx].f4;
        v28[2] = p->e[p->idx].f5;
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
        break;
    case 2: {
        u8 bVar3 = p->timer - 0x10;
        p->timer = bVar3;
        if (bVar3 < 0x10) {
            p->flag = 0;
            return 1;
        }
        {
            u8 bVar1 = p->count;
            if (bVar1 >= 2 && (bVar3 >> 4) < bVar1) {
                p->count = bVar1 - 1;
            }
        }
        return 0;
    }
    }

    if (param_3 < 2) {
        func_801484B0((s32)v10, (s32)v18);
    } else {
        func_80148534((s32)v10, (s32)v18);
    }
    func_80165FA4(uVar6, (s32)v10, (s32)v18);
    ((void (*)(s32, s32, s32))func_80149350)(uVar6, (s32)v10, (s32)v10);
    ((void (*)(void *, void *, void *))RotTransSV)(v18, v18, out);

    if (param_2 != 0) {
        v20[0] = (v10[0] + v20[0]) >> 1;
        v20[1] = (v10[1] + v20[1]) >> 1;
        v20[2] = (v10[2] + v20[2]) >> 1;
        v28[0] = (v18[0] + v28[0]) >> 1;
        v28[1] = (v18[1] + v28[1]) >> 1;
        v28[2] = (v18[2] + v28[2]) >> 1;
        v20[0] = v20[0] - v28[0];
        v20[1] = v20[1] - v28[1];
        v20[2] = v20[2] - v28[2];
        VectorNormalSS(v20, v20);
        v20[0] = v28[0] + v20[0] / param_4;
        v20[1] = v28[1] + v20[1] / param_4;
        v20[2] = v28[2] + v20[2] / param_4;
        p->e[p->idx].f0 = v20[0];
        p->e[p->idx].f1 = v20[1];
        p->e[p->idx].f2 = v20[2];
        p->e[p->idx].f3 = v28[0];
        p->e[p->idx].f4 = v28[1];
        p->e[p->idx].f5 = v28[2];
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
    }

    p->e[p->idx].f0 = v10[0];
    p->e[p->idx].f1 = v10[1];
    p->e[p->idx].f2 = v10[2];
    p->e[p->idx].f3 = v18[0];
    p->e[p->idx].f4 = v18[1];
    p->e[p->idx].f5 = v18[2];
    return 0;
}


extern void func_80016714(void *a0, s32 a1);
extern void func_80146C3C(u8*);
#define SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define SHB(x) __asm__("" : "=r"(x) : "0"(x))

void func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4)
{

    extern s32 D_8011D030;
    extern unsigned char D_801C8710[];

    register int p2 __asm__("$20");             /* $s4 */
    register int p3 __asm__("$17");             /* $s1 */
    register int t2 __asm__("$5");              /* a1 */
    register int t3 __asm__("$6");              /* a2 */
    unsigned short *puVar1;
    short iVar2;
    int eq;

    iVar2 = 0;
    puVar1 = ((unsigned short *)&D_8011D030);
    t2 = ((short)param_2); SHB(t2); p2 = t2; SHB(p2);
    t3 = ((short)param_3); SHB(t3); p3 = t3;
    eq = (p2 == p3);
    do {
        if ((puVar1 != ((unsigned short *)param_1)) &&
            ((unsigned int)*puVar1 == p2 || (unsigned int)*puVar1 == p3) &&
            (!eq ||
             *(int *)(puVar1 + 0x16) == *(int *)(((unsigned short *)param_1) + 0x16))) {
            ((void(*)(unsigned short *))func_80146C3C)(puVar1);
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x2c;
    } while (iVar2 < 0x1e);
    ((void(*)(void *, int))func_80016714)(&D_801C8710[((short)param_4) * 0xc4], 0xc4);
}




extern void func_80146C3C(u8*);

void func_8016706C(s32 param_1)
{

    extern s32 D_8011D030;
    unsigned short *puVar1;
    short iVar2;

    iVar2 = 0;
    puVar1 = ((unsigned short *)&D_8011D030);
    do {
        if ((unsigned int)*puVar1 == ((short)param_1)) {
            ((void(*)(unsigned short *))func_80146C3C)(puVar1);
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x2c;
    } while (iVar2 < 0x1e);
}




// @class: schedule
// @stuck: 16/279 masked. 3 runs, ONE residual class: gcc's list-scheduler puts `la $s2` (p=DATA) + `addu $s4,$zero,$zero` (i=0) BEFORE the callee-arg address setup (addiu $a1,$sp,0x10 / addu $a2,$a1,$zero); the target emits them AFTER. Inert to ~40 statement-order permutations + pin/barrier combos (sched priority dominates the LUID tie-break, sched.c rank_for_schedule). Runs: 19-24 (blk1), 111-114 (region-B cx-load rotation), 177-182 (blk3). Permuter fuel.




extern void func_80149350(s32);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);


s32 func_801670E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    extern u8  D_80186B10[];
    extern u8  D_80186AFC[];
    extern u8  D_80186B24[];
    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    extern u16 D_80126CE0;
    Fr_801670E4 f;
    register u8 *p   __asm__("$18");   /* $s2 */
    register s32 ent __asm__("$19");   /* $s3 */
    s16 i;
    s32 d;
    s32 node;
    u16 c;
    u8 cv;
    u8 cv2;
    register s32 gA __asm__("$2");
    register s32 cxv __asm__("$4");
    register s32 czv __asm__("$5");
    u8 *vc;
    u8 *ap;
    u8 *mp;
    u8 *va;
    u8 *vb;

    ent = arg0;
    node = *(s32 *)(ent + 0x34);
    f.v[1].z = 0;
    f.v[1].y = 0;
    f.v[1].x = 0;
    f.v[3].z = 0;
    f.v[2].z = 0;
    f.v[0].z = 0;
    f.col[1].b = 0x70;
    cv = *(u8 *)(ent + 0x12);
    f.cx = arg1;
    __asm__ __volatile__("");
    va = (u8 *)&f.cx;
    __asm__ __volatile__("" : "=r"(va) : "0"(va));
    f.cy = arg2;
    vb = va;
    __asm__ __volatile__("" : "=r"(vb) : "0"(vb));
    p = D_80186B10;
    i = 0;
    f.col[0].b = 0;
    f.col[0].g = 0;
    f.col[0].r = 0;
    f.col[2].b = 0;
    f.col[2].g = 0;
    f.col[2].r = 0;
    f.col[3].b = 0;
    f.col[3].g = 0;
    f.col[3].r = 0;
    f.code = 0x50000000;
    f.cz = arg3;
    f.col[1].r = cv;
    f.col[1].g = cv;
    ((void (*)(s32, void *, void *))func_80149350)(node, va, vb);

    c = f.cx;
    *(s16 *)(ent + 0x06) = c;
    *(s32 *)(ent + 0x4C) = (s16)c;
    c = f.cy;
    *(s16 *)(ent + 0x0A) = c;
    *(s32 *)(ent + 0x50) = (s16)c;
    c = f.cz;
    *(s16 *)(ent + 0x0E) = c;
    *(s32 *)(ent + 0x54) = (s16)c;
    func_800D20C0(&f.cx, f.a8, 7);
    func_80017E68(&f.cx, f.m1);
    func_800D23D0(f.a8);
    RotMatrixYXZ(f.a8, f.m1);

    do {
        f.v[0].x = (s8)*p++;
        f.v[0].y = (s8)*p++;
        f.v[2].x = (s8)*p++;
        f.v[2].y = (s8)*p++;
        f.v[3].x = (s8)*p++;
        f.v[3].y = (s8)*p--;
        func_80017758(f.v, f.m1);
    } while ((i = i + 1) < 4);

    p = D_80186AFC;
    gA = 0xA0;
    cxv = (s16)f.cx;
    f.col[1].g = gA;
    gA = D_801269A4;
    czv = (s16)f.cz;
    f.col[1].b = 0x10;
    f.col[1].r = 0x10;
    f.pos[0] = gA - cxv;
    i = 0;
    f.v[3].y = 0;
    f.v[2].y = 0;
    f.v[0].y = 0;
    f.pos[1] = D_801269A8 - (s16)f.cy;
    f.pos[2] = D_801269AC - czv;

    do {
        f.v[0].x = (s8)*p++;
        f.v[0].z = (s8)*p++;
        f.v[2].x = (s8)*p++;
        f.v[2].z = (s8)*p++;
        f.v[3].x = (s8)*p++;
        f.v[3].z = (s8)*p--;
        func_80017758(f.v, (void *)(ent + 0x38));
    } while ((i = i + 1) < 4);

    if (*(s32 *)(ent + 0x30) > 0) {
        vc = (u8 *)&f.cx;
        __asm__ __volatile__("" : "=r"(vc) : "0"(vc));
        mp = f.m1;
        ap = mp;
        __asm__ __volatile__("" : "=r"(ap) : "0"(ap));
        p = D_80186B24;
        i = 0;
        d = (s16)f.a8[0] >> 6;
        f.cx += d;
        f.cy += d;
        f.cz += d;
        func_80017E68(vc, ap);
        f.cx = f.cy = f.cz = ((u32)*(s32 *)(ent + 0x30) >> 1) + D_80126CE0 * 0x20;
        func_80017DC4(&f.cx, f.m2);
        func_80048EAC(f.m2, mp);
        f.v[3].z = 0;
        f.v[2].z = 0;
        f.v[0].z = 0;
        cv2 = *(u8 *)(ent + 0x12);
        f.col[1].b = 0x20;
        f.col[1].r = 0x20;
        f.col[3].b = 0;
        f.col[3].r = 0;
        f.col[2].b = 0;
        f.col[2].r = 0;
        f.col[0].b = 0;
        f.col[0].r = 0;
        f.col[3].g = 0;
        f.col[2].g = 0;
        f.col[0].g = 0;
        f.col[1].g = cv2 + 0x60;
        do {
            f.v[0].x = (s8)*p++;
            f.v[0].y = (s8)*p++;
            f.v[2].x = (s8)*p++;
            f.v[2].y = (s8)*p++;
            f.v[3].x = (s8)*p++;
            f.v[3].y = (s8)*p--;
            func_80017758(f.v, f.m1);
        } while ((i = i + 1) < 8);
    }
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(u8*);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);



 /* 0x20 bytes */






s32 func_80167540(s32 arg0) {
    struct Node_80167540 *node;
    struct Entity_80167540 *ent;
    s32 v;

    node = ((struct Entity_80167540 *)arg0)->unk34;
    if (node->unk0 == 1) {
        if (((struct Entity_80167540 *)arg0)->unk12 > ((struct Entity_80167540 *)arg0)->unk10) {
            if (((struct Entity_80167540 *)arg0)->unk1C > 0) {
                ((struct Entity_80167540 *)arg0)->unk10 = (s16) (((s32(*)())rand)() & 0x30);
                v = -0x30;
                goto shared;
            }
        } else if (((struct Entity_80167540 *)arg0)->unk1C < 0) {
            ((struct Entity_80167540 *)arg0)->unk10 = (s16) ((((s32(*)())rand)() & 0x30) + 0x40);
            v = 0x30;
shared:
            ((struct Entity_80167540 *)arg0)->unk1C = v;
        }
        ((struct Entity_80167540 *)arg0)->unk12 = (s16) (((struct Entity_80167540 *)arg0)->unk12 + ((struct Entity_80167540 *)arg0)->unk1C);
        ((struct Entity_80167540 *)arg0)->mat = node->unk20->mat;
        ((void(*)(struct Entity_80167540 *, s32, s32, s32))func_801670E4)(((struct Entity_80167540 *)arg0), 0, 0, 0);
        ent = ((struct Entity_80167540 *(*)(s32, struct Entity_80167540 *, s16, s16, s32, s32, s32))func_80146A6C)(0xE, ((struct Entity_80167540 *)arg0), node->unk6, node->unkA, node->unkE, 0, 0);
        if (ent != 0) {
            ent->mat = node->unk20->mat;
        }
        if (((struct Entity_80167540 *)arg0)->unk34->unk4C->unk44 & 0x20) {
            ((struct Entity_80167540 *)arg0)->unk30 = 0x600;
            ((struct Entity_80167540 *)arg0)->unk2 = (u16) (((struct Entity_80167540 *)arg0)->unk2 + 1);
        }
    } else {
        ((void(*)(struct Entity_80167540 *))func_80146C3C)(((struct Entity_80167540 *)arg0));
    }
}


DEFINE_func_80167714()  /* dedup: shared engine-core @0x80167714 (src/shared) */




void func_801678B4(void *a0) {

    extern void (*D_80186BDC[])(void);
    D_80186BDC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801678F0()  /* dedup: shared engine-core @0x801678f0 (src/shared) */




void func_80167A9C(void *a0) {

    extern void (*D_80186BE8[])(void);
    D_80186BE8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80167AD8(void) {
}






s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3) {

    extern u16 D_800B99DA;
    extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
    extern s32 func_80017758(void *a0, void *a1);
    extern u8 D_80186CF4;
    extern u8 D_80186D08[];

    struct Fr fr;
    u8 *p;
    s32 i;
    register s32 t __asm__("$2");
    register s32 zr __asm__("$0");
    s32 flags;

    func_80168070(param_1, ((s16 *)param_2), ((s16 *)param_3), fr.matrix);

    fr.v[3].z = 0;
    fr.v[2].z = 0;
    fr.v[0].z = 0;
    fr.v[1].z = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    flags = D_800B99DA;
    if (flags & 1) {
        fr.col[1].r = 0xa0;
    } else if (flags & 2) {
        fr.col[1].r = 0xc0;
    } else {
        fr.col[1].r = 0x80;
    }

    p = ((u8 *)&D_80186CF4);
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.col[1].b = fr.col[1].r >> 2;
    fr.col[1].g = fr.col[1].r >> 2;
    i = 0;
L1:
        fr.v[0].x = (s8)*p++;
        fr.v[0].y = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].y = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].y = (s8)*p--;
        func_80017758(fr.v, fr.matrix);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L1;

    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    fr.v[1].z = -0x20;
    p = D_80186D08;
    i = 0;
L2:
        fr.v[0].x = (s8)*p++;
        fr.v[0].z = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p--;
        func_80017758(fr.v, fr.matrix);
        if ((s16)i == 1) {
            fr.v[1].z = 0x20;
            p += 2;
        }
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L2;

    p += 2;
    fr.v[0].x = 0;
    fr.v[0].z = -0x20;
    fr.col[0].r = fr.col[1].r;
    fr.col[0].b = fr.col[1].g;
    fr.col[0].g = fr.col[1].g;
    i = 0;
L3:
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p++;
        func_80017758(fr.v, fr.matrix);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 2) goto L3;
}


extern s32 func_80017758(void *a0, void *a1);
extern s32 func_80029178(s32 arg);


// @class: schedule
// @stuck: none — MATCH. The between-loops f1/f2 store-swap (0x55/0x56) is fixed by writing f2's assign first, then the chained `buf[0x44] = buf[0x45] = buf[0x45] << 1;` — the chain keeps f1's read first (read order fixed by -0x12 in $v0) while emitting f2's store (0x56) ahead of the f1/f0 pair (0x55,0x54). 173/173.

extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);

s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2) {

    extern u16  D_800B99DA;
    extern u8   D_80186B48[];
    extern u8   D_80186B5C[];
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

    p = D_80186B48;
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

    p = D_80186B5C;
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


extern void func_80149350(s32 arg0);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32 ratan2(s32 a0, s32 a1);
void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4) {

    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    s16 mid[3];
    s16 dir[3];
    s32 pos[3];
    mid[0] = (param_2[0] + param_3[0]) >> 1;
    mid[1] = (param_2[1] + param_3[1]) >> 1;
    mid[2] = (param_2[2] + param_3[2]) >> 1;
    ((void (*)(s32, void *, void *))func_80149350)(param_1, mid, mid);
    func_800D20C0(mid, dir, 8);
    func_80017E68(mid, param_4);
    dir[0] = (u16)param_3[0] - (u16)param_2[0];
    dir[1] = (u16)param_3[1] - (u16)param_2[1];
    dir[2] = (u16)param_3[2] - (u16)param_2[2];
    ((void (*)(void *, void *, void *))ApplyMatrixSV)((void *)(*(s32 *)(param_1 + 0x20) + 0x34), dir, dir);
    func_800D23D0(dir);
    RotMatrixYXZ(dir, param_4);
    pos[0] = D_801269A4 - mid[0];
    pos[1] = D_801269A8 - mid[1];
    pos[2] = D_801269AC - mid[2];
    ApplyTransposeMatrixLV(param_4, pos, pos);
    dir[2] = -ratan2(pos[0], pos[1]);
    RotMatrixYXZ(dir, param_4);
}



extern s32 func_80029178(s32 arg);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_801681FC(s32 param_1) {

    extern u8 D_80186BA0[];
    extern u8 D_80186B70[];
    extern u8 D_80186B71[];
    s32 iVar3;
    s32 a3;

    *(s16 *)(param_1 + 0x28) = func_80029178(0x81) & 0xFF;
    *(s32 *)(param_1 + 0x30) = D_80186BA0[*(s32 *)(param_1 + 0x2C)];
    iVar3 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80186B70[iVar3];
    *(s32 *)(param_1 + 0x1C) = D_80186B71[iVar3];
    a3 = *(s32 *)(param_1 + 0x2C) & 1;
    *(s32 *)(param_1 + 0x2C) = a3;
    func_80166F58(param_1, 4, 4, a3);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016829C);

DEFINE_func_80168328()  /* dedup: shared engine-core @0x80168328 (src/shared) */


DEFINE_func_801683D8()  /* dedup: shared engine-core @0x801683d8 (src/shared) */



extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80168430(s32 param_1) {

    extern u8 D_80186BAC[];
    extern u8 D_80186B84[];
    extern u8 D_80186B85[];
    s32 iVar1;

    *(s32 *)(param_1 + 0x30) = D_80186BAC[*(s32 *)(param_1 + 0x2C)];
    iVar1 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80186B84[iVar1];
    *(s32 *)(param_1 + 0x1C) = D_80186B85[iVar1];
    func_80166F58(param_1, 5, 0x3B, 2);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801684B4);

DEFINE_func_80168540()  /* dedup: shared engine-core @0x80168540 (src/shared) */


DEFINE_func_801685EC()  /* dedup: shared engine-core @0x801685ec (src/shared) */


DEFINE_func_80168640()  /* dedup: shared engine-core @0x80168640 (src/shared) */




extern void func_80048EAC(void *a0, void *a1);
extern s32  func_801670E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void RotMatrixX(int, void*);

void func_80168664(s32 param_1)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Mat32 D_800AE620;
    s32 node;

    node = *(s32 *)(param_1 + 0x34);
    *(s32 *)(param_1 + 0x1c) = 0x20;
    *(u16 *)(param_1 + 0x10) = 0x80;
    *(u16 *)(param_1 + 0x12) = 0;
    *(s32 *)(param_1 + 0x30) = 0x1800;
    *(Blk20 *)(param_1 + 0x38) = (*(Blk20 *)&D_800AE620);
    ((s32 (*)(s32, void *))RotMatrixX)(0x400, (void *)(param_1 + 0x38));
    func_80048EAC((void *)(*(s32 *)(node + 0x20) + 0x34), (void *)(param_1 + 0x38));
    func_801670E4(param_1, -6, -0x44, -0x18);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}




void func_80168744(void *a0) {

    extern void (*D_80186C00[])(void);
    D_80186C00[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168780()  /* dedup: shared engine-core @0x80168780 (src/shared) */


DEFINE_func_801687CC()  /* dedup: shared engine-core @0x801687cc (src/shared) */


extern void func_80017E68(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);



void func_80168828(void)
{
    extern s32 func_80017DC4(void *a0, void *a1);
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_800173BC(void *a0, void *a1);
    extern u16 D_80186BF0[];

    register s32 a0v __asm__("$4");
    s32 param_1 = a0v;
    Thing_80168828 thing;
    s16 matA[16];
    s16 matB[16];
    s16 svec[4];
    u16 *p;
    short i;
    register s32 c40 __asm__("$3");   /* $v1: hold the CSE'd 0x40 (else gcc folds to $v0 immediate) */

    c40 = 0x40;
    thing.f04 = 2;
    thing.f0c = 0x24;
    thing.f14 = 0x28;
    thing.f08 = -3;
    thing.f10 = 3;
    thing.f02 = 0;
    thing.f00 = 0;
    thing.f12 = 0;
    thing.f0a = 0;
    thing.f18 = c40;
    thing.f19 = c40;
    thing.f22 = c40;
    thing.f1e = c40;
    thing.f1a = 0x10;
    thing.f20 = 0xff;
    thing.f1c = 0xff;
    thing.f21 = 0xc0;
    thing.f1d = 0xc0;
    thing.f24 = 0x50000000;

    svec[0] = *(u16 *)(param_1 + 6);
    svec[1] = *(u16 *)(param_1 + 0xA);
    svec[2] = *(u16 *)(param_1 + 0xE);
    func_80017E68(svec, matA);

    svec[0] = svec[1] = svec[2] = (*(s32 *)(param_1 + 0x1C) << 11) + 0x1000;
    ((void (*)(void *, void *))func_80017DC4)(svec, matA);

    svec[0] = *(u16 *)(param_1 + 0x12);
    svec[1] = *(u16 *)(param_1 + 0x16);
    svec[2] = *(u16 *)(param_1 + 0x1A);
    RotMatrixYXZ(svec, matB);

    func_80048EAC(matA, matB);

    svec[1] = 0;
    p = D_80186BF0;
    for (i = 0; i < 4; i++) {
        svec[0] = *p++;
        svec[2] = *p++;
        ((void (*)(void *, void *))func_80049CAC)(svec, matA);
        func_80048EAC(matB, matA);
        func_800173BC(&thing, matA);
    }
}




void func_801689D8(void *a0) {

    extern void (*D_80186C08[])(void);
    D_80186C08[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168A14()  /* dedup: shared engine-core @0x80168a14 (src/shared) */


extern void func_80146C3C(u8*);
void func_80168A88(void) {
    ((void (*)(void))func_80146C3C)();
}




void func_80168AA8(void *a0) {

    extern void (*D_80186C10[])(void);
    D_80186C10[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168AE4()  /* dedup: shared engine-core @0x80168ae4 (src/shared) */


void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
void func_80146C3C(u8 *a0);

DEFINE_func_80168B70()  /* dedup: shared engine-core @0x80168B70 (src/shared) */


extern void func_800D2318(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4)
{
    short mtx[16];
    short vec[4];
    int r;
    register int i __asm__("$17");     /* loop counter, survives the call -> $s1 */
    register int tmp __asm__("$2");    /* increment temp -> $v0 (the split-IV) */
    func_800D2318();
    vec[0] = *(short *)(param_1 + 0x12);
    vec[1] = *(short *)(param_1 + 0x16);
    vec[2] = 0;
    RotMatrixYXZ(vec, mtx);
    vec[0] = 0;
    if (*(int *)(param_1 + 0x2c) < 0) {
        vec[2] = -8;
        vec[1] = -4;
    } else {
        vec[2] = 2;
        vec[1] = -2;
    }
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mtx, vec, vec);
    *(short *)(param_1 + 6) = *(short *)(param_1 + 6) + vec[0];
    *(short *)(param_1 + 0xa) = *(short *)(param_1 + 0xa) + vec[1];
    *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + vec[2];
    i = 0;
    if ((short)param_4 > 0) {
        do {
            r = func_80146A6C((unsigned short)param_2, (void *)param_1,
                              (short)*(short *)(param_1 + 6),
                              (short)*(short *)(param_1 + 0xa),
                              (short)*(short *)(param_1 + 0xe),
                              (short)param_3, 0);
            if (r != 0) {
                *(short *)(r + 0x12) = *(short *)(param_1 + 0x12);
                *(short *)(r + 0x16) = *(short *)(param_1 + 0x16);
                *(short *)(r + 0x1a) = *(short *)(param_1 + 0x1a);
            }
            tmp = i + 1;
            i = tmp;
            __asm__ __volatile__("" : "=r"(i) : "0"(i));
        } while ((short)tmp < (short)param_4);
    }
}




void func_80168D58(void *a0) {

    extern void (*D_80186C18[])(void);
    D_80186C18[*(u16 *)((s32)a0 + 0x2)]();
}


extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern int rand(void);
void func_80168D94(int a0) {
    int s1 = a0;
    short v10[4];   /* sp+0x10 SVECTOR */
    short v18[16];  /* sp+0x18 MATRIX_L48 */
    short v38[16];  /* sp+0x38 MATRIX_L48 */
    register int v1 __asm__("$3");
    register int v0 __asm__("$2");
    v10[0] = *(unsigned short *)(s1 + 0x12);
    v10[1] = *(unsigned short *)(s1 + 0x16);
    v10[2] = *(unsigned short *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v38);
    if (*(int *)(s1 + 0x2C) == 0) {
        v0 = rand();
        v1 = (v0 & 0x7F) << 3;
        v0 = (int)((unsigned int)(v0 & 0x7F00) >> 5);
        __asm__("" : "=r"(v0) : "0"(v0));
        v0 += 0xC00;
    } else {
        v0 = rand();
        v1 = ((v0 & 0x7F) << 3) + 0xE00;
        v0 = (int)((unsigned int)(v0 & 0x7F00) >> 5) + 0xE00;
    }
    v10[0] = v1;
    v10[1] = v0;
    __asm__ __volatile__("" ::: "memory");
    v10[2] = 0;
    RotMatrixYXZ(v10, v18);
    func_80048EAC(v38, v18);
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0x24;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(v18, v10, v10);
    {
        register s32 a __asm__("$4") = *(unsigned short *)(s1 + 0x6);
        register s32 b __asm__("$5") = *(unsigned short *)(s1 + 0xA);
        register s32 c __asm__("$3") = *(unsigned short *)(s1 + 0xE);
        *(unsigned short *)(s1 + 0x12) = v10[0];
        *(unsigned short *)(s1 + 0x16) = v10[1];
        {
            s32 z = (unsigned short)v10[2];
            s32 t = *(unsigned short *)(s1 + 0x2);
            *(unsigned short *)(s1 + 0x10) = a;
            *(unsigned short *)(s1 + 0x14) = b;
            *(unsigned short *)(s1 + 0x18) = c;
            *(int *)(s1 + 0x1C) = 0;
            *(unsigned short *)(s1 + 0x2) = t + 1;
            *(unsigned short *)(s1 + 0x1A) = z;
        }
    }
}


DEFINE_func_80168EC4()  /* dedup: shared engine-core @0x80168ec4 (src/shared) */




typedef struct {
    u16 f00;
    u16 f02;
    u16 f04;
    u16 pad06;
    u16 f08;
    u16 f0A;
    u16 f0C;
    u16 pad0E;
    u8  f10;
    u8  f11;
    u8  f12;
    u8  pad13;
    u8  f14;
    u8  f15;
    u8  f16;
    u8  pad17;
    u32 f18;
} S1_80168F40;

extern s32 func_80016A5C();

void func_80168F40(void *a0)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Mat32 D_800AE620;
    S1_80168F40 s1;
    Blk20 s2;
    s32 pad[2];

    s1.f00 = *(u16 *)((s32)a0 + 0x10);
    s1.f02 = *(u16 *)((s32)a0 + 0x14);
    s1.f04 = *(u16 *)((s32)a0 + 0x18);
    s1.f08 = *(u16 *)((s32)a0 + 0x6);
    s1.f0A = *(u16 *)((s32)a0 + 0xA);
    s1.f0C = *(u16 *)((s32)a0 + 0xE);
    s1.f10 = 8;
    s1.f14 = 0xC0;
    s1.f12 = 0;
    s1.f11 = 0;
    s1.f16 = 0x80;
    s1.f15 = 0x80;
    s2 = (*(Blk20 *)&D_800AE620);
    s1.f18 = 0x50000000;
    func_80016A5C(&s1, &s2);
}




void func_8016901C(void *a0) {

    extern void (*D_80186C20[])(void);
    D_80186C20[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 rand(void);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
void func_80169058(s32 a0) {
    s32 s1 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 v18[4];   /* sp+0x18 SVECTOR */
    s16 v20[16];  /* sp+0x20 MATRIX_L48 */
    s16 v40[16];  /* sp+0x40 MATRIX_L48 */
    register s32 v1 __asm__("$3");
    register s32 v0 __asm__("$2");
    v10[0] = *(u16 *)(s1 + 0x6);
    v10[1] = *(u16 *)(s1 + 0xA);
    v10[2] = *(u16 *)(s1 + 0xE);
    func_800D20C0(v10, v18, 1);
    func_800D23D0(v18);
    RotMatrixYXZ(v18, (void *)(s1 + 0x38));
    v10[0] = *(u16 *)(s1 + 0x12);
    v10[1] = *(u16 *)(s1 + 0x16);
    v10[2] = *(u16 *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v40);
    if ((*(s32 *)(s1 + 0x2C) & 0x2) == 0) {
        v0 = rand();
        v1 = (v0 & 0x7F) << 3;
        v0 = ((u32)(v0 & 0x7F00)) >> 5;
        __asm__ __volatile__("" : "=r"(v0) : "0"(v0));
        v0 = v0 + 0xC00;
    } else {
        v0 = rand();
        v1 = ((v0 & 0x7F) << 3) + 0xE40;
        v0 = (((u32)(v0 & 0x7F00)) >> 5) + 0xE00;
    }
    v10[0] = v1;
    v10[1] = v0;
    __asm__ __volatile__("" : : "r"(v1), "r"(v0));
    v10[2] = 0;
    RotMatrixYXZ(v10, v20);
    func_80048EAC(v40, v20);
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0xA;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(v20, v10, v10);
    *(u16 *)(s1 + 0x12) = v10[0];
    *(u16 *)(s1 + 0x16) = v10[1];
    {
        s32 c = *(u16 *)(s1 + 0x2);
        s32 z = (u16)v10[2];
        *(s32 *)(s1 + 0x1C) = 0;
        *(u16 *)(s1 + 0x2) = c + 1;
        *(u16 *)(s1 + 0x1A) = z;
    }
}


DEFINE_func_801691B8()  /* dedup: shared engine-core @0x801691b8 (src/shared) */


DEFINE_func_80169228()  /* dedup: shared engine-core @0x80169228 (src/shared) */




void func_801693CC(void *a0) {

    extern void (*D_80186C28[])(void);
    D_80186C28[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 rand(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_80169584(s32 param_1);
void func_80169408(s32 a0) {
    register s32 s2 __asm__("$18") = a0;
    register s32 s1 __asm__("$17");
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 out[4];   /* sp+0x18 SVECTOR */
    s16 m[32];    /* sp+0x20 MATRIX_L48 (+ trailing reserve to 0x60 — matches target frame) */
    if (*(s32 *)(s2 + 0x2C) == 0) {
        s32 r = rand();
        s1 = s2 + 0x38;
        v10[0] = (r & 0x7F) << 5;
        v10[1] = ((u32)(r & 0x7F00)) >> 3;
        v10[2] = 0;
        RotMatrixYXZ(v10, m);
        func_80048EAC((void *)s1, m);
        v10[0] = 0;
        v10[1] = 0;
        v10[2] = 2;
        ((void (*)(void *, void *, void *))ApplyMatrixSV)(m, v10, v10);
        *(u16 *)(s2 + 0x12) = v10[0];
        *(u16 *)(s2 + 0x16) = v10[1];
        *(u16 *)(s2 + 0x1A) = v10[2];
        v10[0] = *(u16 *)(s2 + 0x6);
        v10[1] = *(u16 *)(s2 + 0xA);
        v10[2] = *(u16 *)(s2 + 0xE);
        func_800D20C0(v10, out, 1);
        func_800D23D0(out);
        RotMatrixYXZ(out, (void *)s1);
    }
    func_80169584(s2);
    *(u16 *)(s2 + 0x2) = *(u16 *)(s2 + 0x2) + 1;
}


DEFINE_func_8016951C()  /* dedup: shared engine-core @0x8016951c (src/shared) */


DEFINE_func_80169584()  /* dedup: shared engine-core @0x80169584 (src/shared) */


DEFINE_func_801696D8()  /* dedup: shared engine-core @0x801696d8 (src/shared) */




void func_80169830(void *a0) {

    extern void (*D_80186C30[])(void);
    D_80186C30[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 rand(void);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
void func_8016986C(s32 a0) {
    s32 s1 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 v18[4];   /* sp+0x18 SVECTOR */
    s16 v20[16];  /* sp+0x20 MATRIX_L48 */
    s16 v40[16];  /* sp+0x40 MATRIX_L48 */
    s32 v1;
    s32 t;
    v10[0] = *(u16 *)(s1 + 0x6);
    v10[1] = *(u16 *)(s1 + 0xA);
    v10[2] = *(u16 *)(s1 + 0xE);
    func_800D20C0(v10, v18, 1);
    func_800D23D0(v18);
    RotMatrixYXZ(v18, (void *)(s1 + 0x38));
    v10[0] = *(u16 *)(s1 + 0x12);
    v10[1] = *(u16 *)(s1 + 0x16);
    v10[2] = *(u16 *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v40);
    v1 = rand();
    v10[0] = (v1 & 0x1FC) + 0x180;
    if (*(s32 *)(s1 + 0x2C) & 0x2) {
        v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0x200;
    } else {
        v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0xC00;
    }
    v10[2] = 0;
    RotMatrixYXZ(v10, v20);
    func_80048EAC(v40, v20);
    if ((*(s32 *)(s1 + 0x2C) & 0x1) == 0) {
        *(s32 *)(s1 + 0x2C) = 0xE00;
    } else {
        *(s32 *)(s1 + 0x2C) = 0xA00;
    }
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0xA;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(v20, v10, v10);
    *(u16 *)(s1 + 0x12) = v10[0];
    *(u16 *)(s1 + 0x16) = v10[1];
    {
        s32 tmp = *(u16 *)(s1 + 0x2);
        s32 z = (u16)v10[2];
        *(s32 *)(s1 + 0x1C) = 0;
        *(u16 *)(s1 + 0x2) = tmp + 1;
        *(u16 *)(s1 + 0x1A) = z;
    }
}


DEFINE_func_801699D0()  /* dedup: shared engine-core @0x801699d0 (src/shared) */


DEFINE_func_80169A4C()  /* dedup: shared engine-core @0x80169a4c (src/shared) */




void func_80169B80(void *a0) {

    extern void (*D_80186CE4[])(void);
    D_80186CE4[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_800D2318(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void*, Svec_801372B0*, Svec_801372B0*);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_800D222C(void *a0, void *a1, s32 a2);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32 ratan2(s32 a0, s32 a1);
extern void func_80048D9C(void *a0, void *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(u8*);

void func_80169BBC(s32 arg0) {

    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    extern u16 D_80186C38[];
    extern u8 D_80186CA8[];
    extern u8 D_80186CD8[];
    extern u8 D_801C99A0[];
    u16 rot[4];
    s16 vec[4];
    s32 pos[4];
    s16 mtx[16];
    s32 p1;
    s32 s2;

    func_800D2318();
    rot[0] = *(u16 *)(arg0 + 0x12);
    rot[1] = *(u16 *)(arg0 + 0x16);
    rot[2] = 0;
    RotMatrixYXZ(rot, mtx);
    vec[0] = 0;
    vec[1] = -2;
    vec[2] = -0x14;
    ((void (*)(void *, void *, void *))ApplyMatrixSV)(mtx, vec, vec);
    *(u16 *)(arg0 + 6) = *(u16 *)(arg0 + 6) + (u16)vec[0];
    *(u16 *)(arg0 + 0xA) = *(u16 *)(arg0 + 0xA) + (u16)vec[1];
    *(u16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0xE) + (u16)vec[2];
    p1 = func_80146A6C(9, (void *)arg0, *(s16 *)(arg0 + 6), *(s16 *)(arg0 + 0xA),
                       *(s16 *)(arg0 + 0xE), 0, 0);
    if (p1 != 0) {
        *(u16 *)(p1 + 0x12) = rot[0];
        *(u16 *)(p1 + 0x16) = rot[1];
        *(u16 *)(p1 + 0x1A) = rot[2];
    }
    func_80146A6C(0xC, (void *)arg0, *(s16 *)(arg0 + 6), *(s16 *)(arg0 + 0xA),
                  *(s16 *)(arg0 + 0xE), 0, 0);
    s2 = func_800D222C((void *)arg0, D_80186CD8, 0x17);
    if (s2 != 0) {
        *(s32 *)(arg0 + 0x20) = s2;
        rot[0] = rot[0] + D_80186C38[*(s32 *)(arg0 + 0x30)];
        rot[1] = rot[1] - 0x400;
        RotMatrixYXZ(rot, mtx);
        pos[0] = D_801269A4 - *(s16 *)(arg0 + 6);
        pos[1] = D_801269A8 - *(s16 *)(arg0 + 0xA);
        pos[2] = D_801269AC - *(s16 *)(arg0 + 0xE);
        ApplyTransposeMatrixLV(mtx, pos, pos);
        rot[2] = -ratan2(pos[0], pos[1]);
        vec[0] = 0x400;
        vec[1] = -0x400;
        vec[2] = 0;
        RotMatrixYXZ(vec, mtx);
        *(s32 *)(s2 + 0x34) = (s32)D_801C99A0;
        RotMatrixYXZ(rot, D_801C99A0);
        func_80048D9C(D_801C99A0, mtx);
        *(u16 *)(s2 + 0x18) = 0x5000;
        *(u16 *)(s2 + 0x1A) = 0x2000;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0xC000140;
        func_80128EA8(s2, arg0 + 0x24, (s32)D_80186CA8);
        *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}


DEFINE_func_80169E44()  /* dedup: shared engine-core @0x80169e44 (src/shared) */




void func_80169F00(void *a0) {

    extern void (*D_80186CEC[])(void);
    D_80186CEC[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (expected; simple straight-line + single branch, one call-crossing local in $s0)

extern void func_800D1FC8(s32 a0, s32 a1);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(u8*);


void func_80169F3C(int param_1)
{

    extern char D_80186C9C[];
    extern char D_80186C5C[];
    int iVar1;

    ((int (*)(int, int))func_800D1FC8)(param_1, 6);
    iVar1 = func_800D21C4(param_1, D_80186C9C, 0x16);
    if (iVar1 != 0) {
        *(int *)(param_1 + 0x20) = iVar1;
        *(short *)(iVar1 + 0x1a) = 0x2000;
        *(short *)(iVar1 + 0x18) = 0x2000;
        *(char *)(iVar1 + 0x26) = 0x60;
        *(char *)(iVar1 + 0x25) = 0x60;
        *(char *)(iVar1 + 0x24) = 0x60;
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50000000;
        ((void (*)(int, int, void *))func_80128EA8)(iVar1, param_1 + 0x24, D_80186C5C);
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
void func_80169FE0(s32 a0) {
    if (((s32 (*)(void *, void *))func_80128ED8)((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}




void func_8016A020(void *a0) {

    extern void (*D_80186D24[])(void);
    D_80186D24[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016A05C()  /* dedup: shared engine-core @0x8016a05c (src/shared) */


DEFINE_func_8016A08C()  /* dedup: shared engine-core @0x8016a08c (src/shared) */


DEFINE_func_8016A1CC()  /* dedup: shared engine-core @0x8016a1cc (src/shared) */


extern s32 func_80017758(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_80149350(s32 arg0);





void func_8016A290(s32 param_1, void *param_2, void *param_3) {

    extern u16 D_800B99DA;
    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    extern u8 D_80186CF4;
    extern u8 D_80186D08[];

    struct Fr_8016A290 fr;
    u8 *p;
    s32 i;
    register s32 t __asm__("$2");
    register s32 zr __asm__("$0");
    s32 flags;
    s32 iVar3;

    iVar3 = *(s32 *)(param_1 + 0x34);

    fr.center.x = (*((s16 *)param_2) + *((s16 *)param_3)) >> 1;
    fr.center.y = (((s16 *)param_2)[1] + ((s16 *)param_3)[1]) >> 1;
    fr.center.z = (((s16 *)param_2)[2] + ((s16 *)param_3)[2]) >> 1;
    ((void(*)(s32, void *, void *))func_80149350)(iVar3, &fr.center, &fr.center);

    *(u16 *)(param_1 + 0x6) = *(u16 *)&fr.center.x;
    *(u16 *)(param_1 + 0xA) = *(u16 *)&fr.center.y;
    *(u16 *)(param_1 + 0xE) = *(u16 *)&fr.center.z;
    func_800D20C0(&fr.center, &fr.diff, 8);
    func_80017E68(&fr.center, fr.mtx);

    fr.diff.x = *(u16 *)((s16 *)param_3) - *(u16 *)((s16 *)param_2);
    fr.diff.y = *(u16 *)(((s16 *)param_3) + 1) - *(u16 *)(((s16 *)param_2) + 1);
    fr.diff.z = *(u16 *)(((s16 *)param_3) + 2) - *(u16 *)(((s16 *)param_2) + 2);
    ((void(*)(s32, void *, void *))ApplyMatrixSV)(*(s32 *)(iVar3 + 0x20) + 0x34, &fr.diff, &fr.diff);
    func_800D23D0(&fr.diff);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.pos[0] = D_801269A4 - fr.center.x;
    fr.pos[1] = D_801269A8 - fr.center.y;
    fr.pos[2] = D_801269AC - fr.center.z;
    ApplyTransposeMatrixLV(fr.mtx, fr.pos, fr.pos);
    fr.diff.z = -((s32(*)(s32, s32))ratan2)(fr.pos[0], fr.pos[1]);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.v[3].z = 0;
    fr.v[2].z = 0;
    fr.v[0].z = 0;
    fr.v[1].z = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    flags = D_800B99DA;
    if (flags & 1) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x20;
    } else if (flags & 2) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x40;
    } else {
        fr.col[1].r = *(s32 *)(param_1 + 0x30);
    }

    p = ((u8 *)&D_80186CF4);
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.col[1].b = fr.col[1].r >> 3;
    fr.col[1].g = fr.col[1].r >> 3;
    i = 0;
L1:
        fr.v[0].x = (s8)*p++;
        fr.v[0].y = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].y = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].y = (s8)*p--;
        func_80017758(fr.v, fr.mtx);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L1;

    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    fr.v[1].z = -0x20;
    p = D_80186D08;
    i = 0;
L2:
        fr.v[0].x = (s8)*p++;
        fr.v[0].z = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p--;
        func_80017758(fr.v, fr.mtx);
        if ((s16)i == 1) {
            fr.v[1].z = 0x20;
            p += 2;
        }
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L2;

    p += 2;
    fr.v[0].x = 0;
    fr.v[0].z = -0x20;
    fr.col[0].r = fr.col[1].r;
    fr.col[0].b = fr.col[1].g;
    fr.col[0].g = fr.col[1].g;
    i = 0;
L3:
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p++;
        func_80017758(fr.v, fr.mtx);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 2) goto L3;
}




void func_8016A700(void *a0) {

    extern void (*D_80186D30[])(void);
    D_80186D30[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80048EAC(void *a0, void *a1);

// Seed for func_8016A73C (ov_SC01_077 exemplar). Overlay-local struct guessed.





s32 func_8016A73C(s32 arg0) {

    extern Blk20 aD800AE620 __asm__("D_800AE620");
    int sp10[8];
    short v[3];   /* sp30, sp32, sp34 */
    int r;
    short tmp;

    r = rand();
    v[1] = ((r & 0x7F) << 4) + 0x400;
    v[0] = ((unsigned)(r & 0x7F00) >> 5) - 0x300;
    v[2] = 0;
    ((void(*)(short *, void *))RotMatrixYXZ)(v, sp10);
    ((void(*)(int, void *))func_80048EAC)(((Obj_8016A73C *)arg0)->unk34->unk34->unk20 + 0x34, sp10);
    v[0] = 0;
    v[1] = 0;
    v[2] = -0x50;
    ((int(*)(void *, short *, short *))ApplyMatrixSV)(sp10, v, v);

    ((Obj_8016A73C *)arg0)->mat = (*(Mat_8016A73C*)&aD800AE620);

    tmp = ((Obj_8016A73C *)arg0)->unk6 + v[0];
    ((Obj_8016A73C *)arg0)->unk6 = tmp;
    ((Obj_8016A73C *)arg0)->mat.w[5] = tmp;
    tmp = ((Obj_8016A73C *)arg0)->unkA + v[1];
    ((Obj_8016A73C *)arg0)->unkA = tmp;
    ((Obj_8016A73C *)arg0)->mat.w[6] = tmp;
    tmp = ((Obj_8016A73C *)arg0)->unkE + v[2];
    ((Obj_8016A73C *)arg0)->unkE = tmp;
    ((Obj_8016A73C *)arg0)->unk2 = ((Obj_8016A73C *)arg0)->unk2 + 1;
    ((Obj_8016A73C *)arg0)->mat.w[7] = tmp;
}


DEFINE_func_8016A890()  /* dedup: shared engine-core @0x8016a890 (src/shared) */


extern s32 func_80016A5C();
s32 func_8016A8FC(s32 a0)
{

    extern Blk20 aD800AE620 __asm__("D_800AE620");
    Prim p;
    int ptr;
    ptr = *(int *)(a0 + 0x34);
    p.v0 = (short)*(int *)(a0 + 0x4C);
    p.v1 = (short)*(int *)(a0 + 0x50);
    p.v2 = (short)*(int *)(a0 + 0x54);
    p.w0 = *(unsigned short *)(ptr + 6);
    p.w1 = *(unsigned short *)(ptr + 0xA);
    p.w2 = *(unsigned short *)(ptr + 0xE);
    p.v0 = (short)(((int)*(short *)(a0 + 6) + *(int *)(a0 + 0x4C)) >> 1);
    p.v1 = (short)(((int)*(short *)(a0 + 0xA) + *(int *)(a0 + 0x50)) >> 1);
    p.v2 = (short)(((int)*(short *)(a0 + 0xE) + *(int *)(a0 + 0x54)) >> 1);
    *(short *)(a0 + 6) = (short)*(int *)(a0 + 0x4C);
    p.w0 = (short)(((int)*(short *)(a0 + 6) + (int)*(short *)(ptr + 6)) >> 1);
    *(int *)(a0 + 0x4C) = p.w0;
    *(short *)(a0 + 0xA) = (short)*(int *)(a0 + 0x50);
    p.w1 = (short)(((int)*(short *)(a0 + 0xA) + (int)*(short *)(ptr + 0xA)) >> 1);
    *(int *)(a0 + 0x50) = p.w1;
    *(short *)(a0 + 0xE) = (short)*(int *)(a0 + 0x54);
    p.w2 = (short)(((int)*(short *)(a0 + 0xE) + (int)*(short *)(ptr + 0xE)) >> 1);
    *(int *)(a0 + 0x54) = p.w2;
    p.b11 = 0x10;
    p.b15 = 0x80;
    p.b16 = 0x20;
    p.b14 = 0x20;
    p.b12 = 0;
    p.b10 = 0;
    p.w18 = 0x50000000;
    ((s32 (*)(void *, void *))func_80016A5C)(&p, &aD800AE620);
}


DEFINE_func_8016AA50()  /* dedup: shared engine-core @0x8016aa50 (src/shared) */




void func_8016AB30(void *a0) {

    extern void (*D_80186D78[])(void);
    D_80186D78[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016AB6C);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016AE5C);

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016afb0 (src/shared) */


DEFINE_func_8016B114()  /* dedup: shared engine-core @0x8016b114 (src/shared) */




extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80016ED4(void *a0);


void func_8016B234(s32 param_1) {

    extern u8 D_800AF648;
    extern u8 D_80186D70;
    short input[3];
    Prim_B234 prim;
    struct { s16 xy[2]; s32 sp1c; s32 flag; } out;
    void *dp;
    u32 uVar1;
    s16 iVar2;
    s32 X, Y0, Y1, base, ni;
    register s32 sy __asm__("$16");
    register s16 xtmp __asm__("$4");
    register s32 sxy __asm__("$3");

    dp = &D_800AF648;
    func_8004914C(dp);
    func_800491AC(dp);
    input[0] = *(u16 *)(param_1 + 6);
    input[1] = *(u16 *)(param_1 + 0xA);
    input[2] = *(u16 *)(param_1 + 0xE);
    RotTransPers((s32)input, (s32)out.xy, &out.sp1c, &out.flag);
    if ((out.flag & 0xffffefff) == 0) {
        sxy = *(s32 *)out.xy;
        prim.a04 = 0x10;
        X = *(u16 *)(param_1 + 0x2a) + sxy;
        sy = (u16)out.xy[1];
        prim.ax = prim.cx = X;
        prim.bx = prim.dx = X + 8;
        Y0 = sy - *(u16 *)(param_1 + 0x26);
        prim.ay = prim.by = Y0;
        sxy = *(u16 *)(param_1 + 0x26);
        prim.v0 = prim.v1 = 0x1d0;
        prim.v2 = prim.v3 = 0x1d8;
        sxy = sy + sxy;
        prim.cy = prim.dy = sxy;
        __asm__ __volatile__("" : : "r"(sy));
        prim.r = prim.g = prim.b = *(u8 *)(param_1 + 0x24);
        prim.code = (&D_80186D70)[*(s32 *)(param_1 + 0x2c)];
        if (*(s16 *)(param_1 + 0x26) < 5) {
            prim.tag = 0;
        } else {
            prim.tag = 0x50000000;
        }
        uVar1 = *(u16 *)(param_1 + 0x30);
        iVar2 = 0;
        if (0 < *(s16 *)(param_1 + 0x28) + 1) {
            do {
                base = ((uVar1 + 1) & 0xf) << 3;
                prim.u0 = prim.u2 = base + 0x620;
                prim.u1 = prim.u3 = base + 0x628;
                func_80016ED4(&prim);
                uVar1 = (s32)(uVar1 << 0x10) >> 0x14;
                iVar2 = iVar2 + 1;
                __asm__ __volatile__("");
                xtmp = prim.ax;
                prim.cx = prim.ax = xtmp - 8;
                prim.bx = prim.dx = xtmp;
            } while ((s16)iVar2 < *(s16 *)(param_1 + 0x28) + 1);
        }
    }
}


DEFINE_func_8016B3F4()  /* dedup: shared engine-core @0x8016b3f4 (src/shared) */


DEFINE_func_8016B428()  /* dedup: shared engine-core @0x8016b428 (src/shared) */


DEFINE_func_8016B448()  /* dedup: shared engine-core @0x8016b448 (src/shared) */




void func_8016B4BC(void *a0) {

    extern void (*D_80186DF4[])(void);
    D_80186DF4[*(u16 *)((s32)a0 + 0x2)]();
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

    extern int D_801C89B0;
    int iVar1;
    int uVar2;
    volatile int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_801C89B0);
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

    extern s16 D_80186DE8[];
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
    psVar5 = D_80186DE8;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016B6BC;

// @class: schedule
// @stuck: none — MATCH (94/94 ins, match_one relocation-masked)
//
// Exemplar of the 138-member h_seq family. The whole crack was ONE statement-order
// lever in the tail: the target's post-func_80015978 fix-up runs
//   v[2].x += off.x;  v[2].y += off.y;  v[0].c = 3;
// (the `c = 3` store LAST). Writing `c = 3` between the two v[2] RMWs — the order the
// Ghidra-C literally prints, and what every prior draft copied — costs 12 mismatches:
// gcc hoists the `li 3` into the load-delay window, which pushes v[2].x into $v1 and
// the off.x temp into $a0, and then the `addu $a0,$s1,$zero` arg copy can no longer be
// scheduled early enough to become the base register of the v[2]/v[0].c stores.
// With `c = 3` last, the arg copy births at the v[2].x/v[2].y boundary (idx 76) exactly
// as the target does, and the mixed $s1-load / $a0-store addressing falls out for free.
// (§67-adjacent: the copy PLACEMENT was the root cause — but here plain statement order
// reaches it, no `__asm__` launder and no register pin needed. Prior notes calling this a
// regalloc tie-break and pinning $a0 were chasing the consequence, not the cause.)
//
// Everything else follows the Ghidra-C: `Prim *p = &prim` (one alias only — a second
// pointer name splits the pseudo and breaks the $s1 base), the `q++` post-increment
// running pointer over the 8-byte table rows, and the ((param_4 << 16) >> 14) byte-offset
// index into D_80186DD0 (sll 16 / sra 14).


             /* 0x28 */


               /* the 8-byte D_80186DD0[] row */

extern void func_80013CFC(s32 a0, s32 a1, void *a2);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8001739C(void *a0);

/* Def sig is deliberately (s32,s32,s32,s32) — byte-identical to the (int,unsigned,short,int)
 * spelling, and IDENTICAL to this TU's own caller decl `extern void func_8016B6BC(s32,s32,s32,s32);`
 * (ov_SC01_077_jr_8016AB6C.c), so there is no §73/§57 def-side self-decl conflict to reconcile. */
void func_8016B6BC(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {

    extern int D_80186DD0;
    int iVar1;
    M8_8016B6BC *q;
    Prim_8016B6BC prim;
    Prim_8016B6BC *p = &prim;
    DVec_8016B6BC off;
    unsigned int v;
    unsigned int c;

    q = (M8_8016B6BC *)*(int *)((int)&D_80186DD0 + ((param_4 << 0x10) >> 0xe));
    p->color = 0x50000000;
    c = (unsigned int)param_2;
    v = 0x20;
    if (c < 0x20) {
        v = c;
    }
    if (*(int *)(param_1 + 0x2c) == 0) {
        c = c | (v << 0x10 | v << 8);
    } else {
        c = c << 8 | v << 0x10 | v;
    }
    p->combined = c;
    iVar1 = (int)(short)param_3;
    p->z1c = 0;
    p->z20 = 0;
    func_80013CFC(iVar1, (int)q++, &p->v[0]);
    func_80013CFC(iVar1, (int)q++, &p->v[1]);
    func_80013CFC(iVar1, (int)q, &p->v[2]);
    func_80015978(param_1 + 4, (s32 *)&off);
    p->v[0].x += off.x;
    p->v[0].y += off.y;
    p->v[1].x += off.x;
    p->v[1].y += off.y;
    p->v[2].x += off.x;
    p->v[2].y += off.y;
    p->v[0].c = 3;
    func_8001739C(p);
}




// @class: schedule
// @stuck: none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);


int func_8016B834(int param_1, int param_2) {

    extern int *D_80186E2C[];
    extern unsigned short D_80186E34[];
    extern unsigned short D_80186E3C[];
    extern unsigned char D_801C89B8[];
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_801C89B8 + param_2 * 0x40);
    puVar3 = D_80186E2C[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_80186E34[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_80186E3C[param_2];
    }
    return iVar1;
}


DEFINE_func_8016B91C()  /* dedup: shared engine-core @0x8016b91c (src/shared) */


DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016b964 (src/shared) */


DEFINE_func_8016B984()  /* dedup: shared engine-core @0x8016b984 (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016B9F8;

// @class: regalloc-order
// @stuck: none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)

extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{

    extern s32 D_801C89B0;
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_801C89B0, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}


DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016ba48 (src/shared) */


DEFINE_func_8016BA68()  /* dedup: shared engine-core @0x8016ba68 (src/shared) */


DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016badc (src/shared) */




void func_8016BBA4(void *a0) {

    extern void (*D_80186E44[])(void);
    D_80186E44[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_801465C0(void);
extern void func_80146C3C(u8*);

// @class: plumbing
// @stuck: none — MATCH (56 ins, match_one relocation-masked)




s32 func_8016BBE0(s32 param_1) {
    extern void func_8016BF34(void *a0);
    extern void func_8016BF50(s32);
    extern void func_8001CF00(s32);
    extern M2C_UNK D_801C8AEC;
    extern u8 D_801C8AED;
    extern u8 D_801C8AEE;
    extern M2C_UNK D_801C8AF0;
    extern u8 D_801C8AF1;
    extern u8 D_801C8AF2;

    int iVar1;
    int temp;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    *(int *)(((int)param_1) + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32))func_8016BF34)(((int)param_1));
        func_8016BF50(((int)param_1));
        func_8001CF00(iVar1);
        *(s16 *)(iVar1 + 0x10) = 0;
        temp = *(int *)(((int)param_1) + 0x2c);
        *(s16 *)(iVar1 + 0x14) = 0;
        *(s16 *)(iVar1 + 0x1a) = 0;
        *(s16 *)(iVar1 + 0x18) = 0;
        *(s16 *)(iVar1 + 0x12) = temp * 0x555;
        *(s16 *)(((int)param_1) + 0x10) = 0;
        *(s16 *)(((int)param_1) + 0x14) = 0;
        (*(u8 *)&D_801C8AEC) = 0x20;
        D_801C8AED = 0x20;
        D_801C8AEE = 0;
        (*(u8 *)&D_801C8AF0) = 0xc0;
        D_801C8AF1 = 0xc0;
        D_801C8AF2 = 0;
        *(u16 *)(((int)param_1) + 2) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(((int)param_1));
    }
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016BCC0);

extern s32 func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);

// @class: struct
// @stuck: none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{

    extern M2C_UNK D_801C8AEC;
    extern M2C_UNK D_801C8AF0;
    extern u8 D_801C8AED;
    extern u8 D_801C8AEE;
    extern u8 D_801C8AF1;
    extern u8 D_801C8AF2;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    ((void(*)())func_8016BF50)();

    p1 = &(*(u8 *)&D_801C8AEC);
    if (*p1 != 0) *p1 -= 4;
    if (D_801C8AED != 0) D_801C8AED -= 4;
    if (D_801C8AEE != 0) D_801C8AEE -= 4;
    p2 = &(*(u8 *)&D_801C8AF0);
    if (*p2 != 0) *p2 -= 4;
    if (D_801C8AF1 != 0) D_801C8AF1 -= 4;
    if (D_801C8AF2 != 0) D_801C8AF2 -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}


extern void func_80146C3C(u8*);
extern s32 func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);


// @class: plumbing
// @stuck: none — MATCH

s32 func_8016BEA0(s32 param_1)
{

    extern M2C_UNK D_801C8AEC;
    extern M2C_UNK D_801C8AF0;
    int iVar2;
    unsigned short uVar1;

    iVar2 = *(int *)(((int)param_1) + 0x20);
    ((void(*)())func_8016BF50)();
    uVar1 = *(unsigned short *)(((int)param_1) + 0x10) - 0x18;
    *(unsigned short *)(((int)param_1) + 0x10) = uVar1;
    *(unsigned short *)(iVar2 + 0x1a) = *(unsigned short *)(iVar2 + 0x1a) + uVar1;
    *(unsigned short *)(iVar2 + 0x12) = (*(unsigned short *)(iVar2 + 0x12) + 0x22) & 0xfff;
    ((void (*)(int, void *, void *, int))func_8016BFA8)(((int)param_1), &(*(int *)&D_801C8AEC), &(*(int *)&D_801C8AF0), iVar2 + 0x18);
    if (*(short *)(iVar2 + 0x1a) < 0) {
        ((void (*)(int))func_80146C3C)(((int)param_1));
    }
}


DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016bf34 (src/shared) */



/* §71 sibling-first: this is the head of the already-matched func_8016C2C4
 * (src/ov_SC03_099/ov_SC03_099_jr_8016AB6C.c L2707) lifted into its own leaf. */

extern void func_80149350(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016BF50(s32 param)
{
    u16 buf[3];
    s32 arg;

    arg = *(s32 *)(param + 0x34);
    buf[0] = *(u16 *)(param + 0x12);
    buf[1] = *(u16 *)(param + 0x16);
    buf[2] = *(u16 *)(param + 0x1a);
    ((void (*)(s32, void *, void *))func_80149350)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, param + 4);
}




extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_801C8A78;
    func_8016BFD0(a0, a1, a2, a3, &D_801C8A78);
}


extern void func_800123F0(s32 a0, s32 a1);
extern void func_80013F3C(s32 a0);
extern void func_80020F34(s32 a0, s32 a1);
extern void func_8012EFB8(s32 a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

// @class: struct
// @stuck: none — MATCH (95 ins). Keys: (1) 4-byte unaligned copies via `struct{char b[4];}`
//   assignment -> lwl/lwr/swl/swr with reload; (2) 0x40-byte stack buffer `buf` (Mtx padded to
//   0x40, not 0x20) sets the frame to 0x70 and lands v1/v2 at sp+0x50/0x58; (3) func_80017714(a4)
//   takes param_5 as an arg -> gcc materializes `addu $a0,$s0,$zero` and stores the 4 zeros via $a0.




void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4) {
    extern void func_80017714();
    extern s32 D_80186E54;
    extern s32 D_80186E5C;
    extern s32 D_80186E64;
    extern s32 D_80186E6C;

    Mtx buf;
    Vec3_8016BFD0 v1;
    Vec3_8016BFD0 v2;
    s32 iVar5 = *(s32 *)(a0 + 0x20);

    *(u32 *)((s32)a4 + 0x30) = 0x50000000;
    *(W *)((s32)a4 + 0x20) = *(W *)a1;
    *(W *)((s32)a4 + 0x24) = *(W *)a1;
    *(W *)((s32)a4 + 0x28) = *(W *)a2;
    *(W *)((s32)a4 + 0x2c) = *(W *)a2;

    v1.x = *(u16 *)(a0 + 6);
    v1.y = *(u16 *)(a0 + 0xa);
    v1.z = *(u16 *)(a0 + 0xe);
    ((void(*)())func_8012EFB8)(&v1, &v1);
    ((void(*)())func_80013F3C)(&buf);
    ((void(*)())func_800123F0)(&buf, (s32)*(s16 *)(iVar5 + 0x12));

    v2.x = *(u16 *)(a3 + 0);
    v2.y = *(u16 *)(a3 + 2);
    v2.z = *(u16 *)(a3 + 4);
    ((void(*)())func_80020F34)(&buf, &v2);

    buf.t[0] = v1.x;
    buf.t[1] = v1.y;
    buf.t[2] = v1.z;
    ((void(*)())func_8012F14C)(&buf, &D_80186E54, (s32)a4);
    ((void(*)())func_8012F14C)(&buf, &D_80186E5C, (s32)a4 + 8);
    ((void(*)())func_8012F14C)(&buf, &D_80186E64, (s32)a4 + 0x10);
    ((void(*)())func_8012F14C)(&buf, &D_80186E6C, (s32)a4 + 0x18);

    *(s16 *)((s32)a4 + 4) = 0;
    *(s16 *)((s32)a4 + 0xc) = 0;
    *(s16 *)((s32)a4 + 0x14) = 0;
    *(s16 *)((s32)a4 + 0x1c) = 0;
    func_80017714(a4);
}




void func_8016C14C(void *a0) {

    extern void (*D_80186E74[])(void);
    D_80186E74[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_801465C0(void);
extern void func_80149350(s32 arg0);

void func_8016C188(s32 param)
{
    register s32 s1 __asm__("$17");
    register s32 s2 __asm__("$18");
    register u8 *s0 __asm__("$16");
    u16 buf[3];
    s16 *pBCC;
    s16 *pBD4;
    s32 t34;

    extern void func_80015954(s32, s32);
    extern s32 func_8016C374(s32, s32, s32, s32);
    extern void func_80146C3C(u8*);
    extern void func_8001CD9C(s32, void *);
    extern void func_800233CC(void *, unsigned short);
    extern u8 D_801C8AAC[];
    extern s16 D_801C8AF4;
    extern s16 D_801C8AF6;
    extern s16 D_801C8AF8;
    extern s16 D_801C8AFC;
    extern s16 D_801C8AFE;
    extern s16 D_801C8B00;

    s1 = param;
    s2 = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(s1 + 0x20) = s2;
    if (s2 != 0) {
        *(u16 *)(s1 + 0x12) = *(u16 *)(s1 + 0x6);
        *(u16 *)(s1 + 0x16) = *(u16 *)(s1 + 0xA);
        *(u16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0xE);
        t34 = *(s32 *)(s1 + 0x34);
        buf[0] = *(u16 *)(s1 + 0x12);
        buf[1] = *(u16 *)(s1 + 0x16);
        buf[2] = *(u16 *)(s1 + 0x1A);
        ((void (*)(s32, void *, void *))func_80149350)(t34, buf, buf);
        ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
        s0 = D_801C8AAC;
        ((void (*)(s32, void *))func_8001CD9C)(s2, s0);
        *(s16 *)(s2 + 0x1E) = 0xCCC;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0x50000000;
        ((void (*)(void *, s32))func_800233CC)(s0, 0x80);
        *(s16 *)(s2 + 0x1A) = 0;
        *(s16 *)(s2 + 0x18) = 0;
        *(s16 *)(s1 + 0x10) = 0;
        pBCC = &D_801C8AF4;
        pBD4 = &D_801C8AFC;
        *pBCC = 0x20;
        D_801C8AF6 = 0x20;
        D_801C8AF8 = 0;
        *pBD4 = 0xC0;
        D_801C8AFE = 0xC0;
        D_801C8B00 = 0;
        ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, pBCC, pBD4, s0);
        *(u16 *)(s1 + 2) = *(u16 *)(s1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016C2C4;

// @class: schedule
// @stuck: none — MATCH (44 ins; pins $s0/$s1 + hoist call-arg into a temp so its load fills the buf-store delay slot)

extern void func_80149350(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(u8*);


void func_8016C2C4(s32 param)
{

    extern u8 D_801C8AF4[];
    extern u8 D_801C8AFC[];
    extern u8 D_801C8AAC[];
    register s32 s1 __asm__("$17");
    register s32 s0 __asm__("$16");
    u16 buf[3];
    s16 v;
    s32 r;
    s32 arg;

    s1 = param;
    s0 = *(s32 *)(s1 + 0x20);
    arg = *(s32 *)(s1 + 0x34);
    buf[0] = *(u16 *)(s1 + 0x12);
    buf[1] = *(u16 *)(s1 + 0x16);
    buf[2] = *(u16 *)(s1 + 0x1a);
    ((void (*)(s32, void *, void *))func_80149350)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
    v = *(s16 *)(s1 + 0x10) + 0x10;
    *(s16 *)(s1 + 0x10) = v;
    v = *(s16 *)(s0 + 0x1a) + v;
    *(s16 *)(s0 + 0x1a) = v;
    *(s16 *)(s0 + 0x18) = v;
    r = ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, D_801C8AF4, D_801C8AFC, D_801C8AAC);
    if (r == 0) {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}


DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016c374 (src/shared) */


extern void func_80016714(void *a0, s32 a1);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);
extern void func_80048EAC(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void func_801465C0(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(u8*);

// @class: regalloc-order
// @stuck: none — MATCH (172/172, relocation-masked)



s32 func_8016C49C(s32 param_1_arg) {

    extern s32 D_8011D030;
    extern s32 VectorNormalSS(void *, void *);
    extern short func_8016CF04(s32, s32);
    extern u8 D_801C8B08[];
    extern u8 D_801C8BC8;

    register u16 *param_1 __asm__("$17") = ((u16 *)param_1_arg);
    int iVar5;
    int iVar6;
    u16 sv[4];
    s32 mat[8];
    short sVar1;

    iVar5 = *(int *)(param_1 + 0x18);
    iVar6 = *(int *)(param_1 + 0x1a);
    param_1[0x14] = *(u16 *)(iVar5 + 0x36);
    if ((*(u32 *)(param_1 + 0x16) & 0x8000) == 0) {
        short iVar4 = 0;
        u16 *psVar3 = (u16 *)&D_8011D030;
        do {
            if (psVar3 != param_1 && *psVar3 == 0x30) {
                ((void(*)(void *))func_80146C3C)(psVar3);
            }
            iVar4 = iVar4 + 1;
            psVar3 = psVar3 + 0x2c;
        } while (iVar4 < 0x1e);
        D_801C8B08[1] = 0xff;
        D_801C8B08[2] = 0x10;
        D_801C8B08[0] = 0x10;
        D_801C8B08[6] = 0;
        D_801C8B08[5] = 0;
        D_801C8B08[4] = 0;
        ((void(*)(void *, s32))func_800233CC)(D_801C8B08, 10);
        sv[0] = *(u16 *)(iVar5 + 6) - *(u16 *)(iVar6 + 6);
        {
            int t = *(u16 *)(iVar6 + 0xa) + 0x28;
            sv[1] = *(u16 *)(iVar5 + 0xa) - t;
        }
        sv[2] = *(u16 *)(iVar5 + 0xe) - *(u16 *)(iVar6 + 0xe);
        VectorNormalSS(sv, sv);
        param_1[3] = *(u16 *)(iVar5 + 6) + ((s16)sv[0] >> 9);
        param_1[5] = *(u16 *)(iVar5 + 0xa) + (((s16)sv[1] >> 9) - 0x28);
        param_1[7] = *(u16 *)(iVar5 + 0xe) + ((s16)sv[2] >> 9);
        ((void(*)(void *))func_800D23D0)(sv);
        sv[0] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, param_1 + 0x1c);
        ((void(*)(void *, s32))func_80016714)(&D_801C8BC8, 0x620);
        ((s32(*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x32, param_1, 0, 0, 0, 0, *(int *)(param_1 + 0x18));
        sVar1 = 5;
    } else {
        int iVar5b = ((s32(*)())func_801465C0)();
        u32 uVar2;
        if (iVar5b == 0) {
            return;
        }
        ((void(*)(s32, void *))func_8001CD9C)(iVar5b, D_801C8B08);
        *(u32 *)(iVar5b + 4) |= 0x50000000;
        uVar2 = rand();
        sv[0] = (uVar2 & 0x7f) * 8 - 0x80;
        sv[1] = ((uVar2 & 0x7f00) >> 4) - 0x400;
        sv[2] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, mat);
        ((void(*)(void *, void *))func_80048EAC)(param_1 + 0x1c, mat);
        sv[1] = 0;
        sv[0] = 0;
        sv[2] = 0xb;
        ((void(*)(void *, void *, void *))ApplyMatrixSV)(mat, sv, sv);
        param_1[9] = sv[0];
        param_1[0xb] = sv[1];
        param_1[0xd] = sv[2];
        *(int *)(param_1 + 0x10) = iVar5b;
        *(int *)(param_1 + 0xe) = 8;
        func_8016CF04((s32)param_1, 0);
        *(int *)(param_1 + 0x16) = 0;
        sVar1 = param_1[1] + 1;
    }
    param_1[1] = sVar1;
}


DEFINE_func_8016C74C()  /* dedup: shared engine-core @0x8016c74c (src/shared) */


DEFINE_func_8016C83C()  /* dedup: shared engine-core @0x8016c83c (src/shared) */



extern short func_8016CBC0(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);


void func_8016C998(s32 param_1)
{

    extern s32 D_80126B9C;
    extern s16 D_80126CE0;
    u16 *psVar7;
    s32 r;
    short i;
    extern Slot_998 D_801C8BC8[];

    psVar7 = *(u16 **)(param_1 + 0x34);
    if (*psVar7 != 1) {
        *(s16 *)(param_1 + 2) = 6;
    }
    func_8016CBC0();
    if (*(s16 *)(param_1 + 0x28) != *(s16 *)(*(s32 *)(param_1 + 0x30) + 0x36)) {
        return;
    }
    if ((D_80126B9C & 0x20) == 0) {
        return;
    }
    if ((*(s32 *)(param_1 + 0x1c) == 0) ||
        (*(s16 *)(param_1 + 0x12) < D_80126CE0)) {
        *(s16 *)(param_1 + 0x12) = D_80126CE0;
        i = 0;
        do {
            if (D_801C8BC8[i].f0 == 0) {
                goto found;
            }
            i++;
        } while (i < 8);
    found:
        if (i >= 8) {
            return;
        }
        r = func_80146A6C(0x30, psVar7, 0, 0, 0, 0x8000, *(s32 *)(param_1 + 0x30));
        if (r == 0) {
            return;
        }
        D_801C8BC8[i].f0 = 1;
        *(Blk32_998 *)(r + 0x38) = *(Blk32_998 *)(param_1 + 0x38);
        *(s16 *)(r + 0x2a) = i;
        *(s16 *)(r + 6) = *(s16 *)(param_1 + 6);
        *(s16 *)(r + 0xa) = *(s16 *)(param_1 + 0xa);
        *(s16 *)(r + 0xe) = *(s16 *)(param_1 + 0xe);
        *(s32 *)(param_1 + 0x1c) = 0x10;
    } else {
        *(s32 *)(param_1 + 0x1c) = *(s32 *)(param_1 + 0x1c) - 1;
    }
}




void func_8016CB84(void *a0) {

    extern void (*D_80186E7C[])(void);
    D_80186E7C[*(u16 *)((s32)a0 + 0x2)]();
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016CBC0;

extern s32 func_80017758(void *a0, void *a1);
short func_8016CBC0(void)
{

    extern Blk20 aD800AE620 __asm__("D_800AE620");

    extern Blk_8016CBC0 D_801C8BC8[];
  Poly_8016CBC0 p0;
  Poly_8016CBC0 p1;
  Mtx8_8016CBC0 mtx;
  Blk_8016CBC0 *blk;
  Rec_8016CBC0 *sub;
  Rec_8016CBC0 *pv;
  unsigned int uVar9;
  unsigned int w9;
  unsigned int uc;
  unsigned int a2;
  int col;
  int iVar3;
  int w3;
  unsigned int w3b;
  short count;
  short i;
register unsigned int zr __asm__("$0");
  mtx = (*(Mtx8_8016CBC0 *)&aD800AE620);
  count = 0;
  p1.tag = 0x50000000;
  p0.tag = 0x50000000;
  p1.col[3].b = 0;
  p1.col[3].g = 0;
  p1.col[3].r = 0;
  p1.col[1].b = 0;
  p1.col[1].g = 0;
  p1.col[1].r = 0;
  p0.col[2].b = 0;
  p0.col[2].g = 0;
  p0.col[2].r = 0;
  p0.col[0].b = 0;
  p0.col[0].g = 0;
  p0.col[0].r = 0;
  for (i = 0; i < 8; i++)
  {
    blk = &D_801C8BC8[i];
    if (blk->f0 != 0)
    {
      sub = blk->ent;
      uVar9 = blk->f1;
      iVar3 = blk->f2;
      col = blk->f3;
      count = count + 1;
      w3 = iVar3 - 1;
      iVar3 = w3 + zr;
      if (w3 != (-1))
      {
        do
        {
          pv = &sub[(short) uVar9];
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[0].x = a;
            b = pv->h[3];
            p1.v[1].x = b;
            p0.v[1].x = (p1.v[0].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[0].y = a;
            b = pv->h[4];
            uc = ((unsigned) (col & 0xFF)) >> 3;
            p1.v[1].y = b;
            p0.v[1].y = (p1.v[0].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
            w9 = uVar9 - 1;
            uVar9 = w9 + zr;
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[0].z = a;
            b = pv->h[5];
            p1.col[0].g = col;
            p0.col[1].g = col;
            p1.col[0].b = uc;
            p0.col[1].b = uc;
            p1.col[0].r = uc;
            p0.col[1].r = uc;
            p1.v[1].z = b;
            p0.v[1].z = (p1.v[0].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          if (((int) (w9 << 16)) < 0)
          {
            uVar9 = 0xF;
          }
          pv = &sub[(short) uVar9];
          col = col - 0xF;
          a2 = (unsigned) (col & 0xFF);
          a2 = a2 >> 3;
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[2].x = a;
            b = pv->h[3];
            p1.v[3].x = b;
            p0.v[3].x = (p1.v[2].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[2].y = a;
            b = pv->h[4];
            p1.v[3].y = b;
            p0.v[3].y = (p1.v[2].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[2].z = a;
            b = pv->h[5];
            p1.col[2].g = col;
            p0.col[3].g = col;
            p1.col[2].b = a2;
            p0.col[3].b = a2;
            p1.col[2].r = a2;
            p0.col[3].r = a2;
            p1.v[3].z = b;
            p0.v[3].z = (p1.v[2].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          func_80017758(&p0, &mtx);
          func_80017758(&p1, &mtx);
          uc = iVar3 - 1;
          w3b = uc;
          iVar3 = w3b + zr;
        }
        while (((short) w3b) != (-1));
      }
    }
  }

  return count;
}


extern void func_8016D5EC(s32 *a0);
extern void func_800D23D0(void *a0);


/* func_8016CF04 returns short (case 2: 1 if the decremented f2 hit 0, else 0; all other
 * paths return 0 via the addu $v0,$zero,$zero at 0x8016D154). The TU/engine_core.h declare
 * it `void` in 4 DEFINE_ macros + one block-scope decl in func_8016C49C; the real apply is the
 * byte-neutral engine_core.h void->short flip (every caller discards or ptr-casts the return,
 * cf. func_8016D5EC's `(s16)(...)` cast). The //@EDIT lines above are the rtu_match proxy for
 * that flip. Body verified 166/166 in isolation AND in a whole-TU compile w/ the reconciled hdr. */
                /* 4 + 16*12 = 0xC4 stride */

short func_8016CF04(s32 param_1, s32 param_2) {
    extern Blk_8016CF04 D_801C8BC8[];

    Blk_8016CF04 *p = &D_801C8BC8[*(short *)(((int)param_1) + 0x2a)];
    u16 rot[4];
    u16 out[4];
    s32 mtx[8];

    switch (((short)param_2)) {
    case 0:
        p->f2 = 0;
        p->f1 = 0;
        p->f3 = 0xf0;
        break;
    case 1:
        p->f1 = p->f1 + 1;
        if ((u8)p->f1 >= 0x10)
            p->f1 = 0;
        if ((u8)p->f2 < 0xf)
            p->f2 = p->f2 + 1;
        break;
    case 2: {
        u8 c = p->f2 - 1;
        p->f2 = c;
        if (c == 0) {
            p->f0 = 0;
            return 1;
        }
        p->f3 = p->f3 - 0xf;
        return 0;
    }
    }

    rot[0] = *(s32 *)(((int)param_1) + 0x10) >> 12;
    rot[1] = *(s32 *)(((int)param_1) + 0x14) >> 12;
    rot[2] = *(s32 *)(((int)param_1) + 0x18) >> 12;
    func_800D23D0(rot);
    RotMatrixYXZ(rot, mtx);
    rot[0] = 9;
    rot[1] = 0;
    rot[2] = 0;
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].a = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].b = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].c = *(u16 *)(((int)param_1) + 0xe) + out[2];
    rot[0] = -rot[0];
    rot[1] = -rot[1];
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].d = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].e = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].g = *(u16 *)(((int)param_1) + 0xe) + out[2];
    return 0;
}




void func_8016D19C(void *a0) {

    extern void (*D_80186E98[])(void);
    D_80186E98[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016D1D8);



void func_8016D428(void *a0) {

    extern void (*D_80186EA0[])(void);
    D_80186EA0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016D464()  /* dedup: shared engine-core @0x8016d464 (src/shared) */


DEFINE_func_8016D4DC()  /* dedup: shared engine-core @0x8016d4dc (src/shared) */


DEFINE_func_8016D5EC()  /* dedup: shared engine-core @0x8016d5ec (src/shared) */


DEFINE_func_8016D64C()  /* dedup: shared engine-core @0x8016d64c (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016D688);

DEFINE_func_8016D778()  /* dedup: shared engine-core @0x8016d778 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016D848);

INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016D984);

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016da04 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);

void func_8016DA30(int param_1)
{

    extern void (*D_80186F08[])(int);
    ((void (*)(void))func_8016DBD8)();
    D_80186F08[*(unsigned short *)(param_1 + 2)](param_1);
}



// @class: plumbing
// @stuck: none — MATCH (clean if/else, one call-crossing local; bnez polarity = if(iVar1==0) fall-through)

extern void func_801465C0(void);
extern void func_80146C3C(u8*);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);


void func_8016DA7C(s32 param_1)
{

    extern u8 D_80186EAC;
    extern u8 D_80186EB8;
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    if (iVar1 == 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    } else {
        *(s32 *)(param_1 + 0x20) = iVar1;
        ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_80186EAC, 0x250, 0x100);
        *(u8 *)(iVar1 + 0x27) = 0x90;
        *(u16 *)(iVar1 + 0x18) = 0x3000;
        *(u16 *)(iVar1 + 0x1a) = 0x4000;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        func_80128EA8(iVar1, param_1 + 0x24, (s32)&D_80186EB8);
        *(s32 *)(param_1 + 0x10) = 0;
        *(s32 *)(param_1 + 0x14) = 0xfff40000;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
}


s32 func_80128ED8(s32 param_1, s32 *param_2);
void func_80146C3C(u8 *a0);

void func_8016DB34(s32 a0)
{
    register s32 s0 asm("$16") = a0;
    register s32 s1 asm("$17") = *(s32 *)(s0 + 0x20);
    s32 result;
    s32 temp1;
    s32 temp2;

    result = func_80128ED8(s1, (s32 *)(s0 + 0x24));

    if (result != 0) {
        func_80146C3C((u8 *)s0);
    } else {
        *(u8 *)(s1 + 0x27) = *(u8 *)(s0 + 0x28) - 0x70;

        temp1 = *(s32 *)(s0 + 0x10) + (-0x60000);
        *(s32 *)(s0 + 0x10) = temp1;

        temp2 = *(s32 *)(s0 + 0x14) + temp1;
        *(s32 *)(s0 + 0x14) = temp2;

        *(s32 *)(s0 + 0x8) = *(s32 *)(s0 + 0x8) + temp2;

        *(s16 *)(s1 + 0x18) = *(s16 *)(s1 + 0x18) - 0x500;
        *(s16 *)(s1 + 0x1A) = *(s16 *)(s1 + 0x1A) - 0x300;
    }
}


DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016dbd8 (src/shared) */


extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(u8*);
extern void func_80149374(s32 a0, s32 a1);
extern s32 func_801619D0(void *a0);


s32 func_8016DC20(s32 param_1) {

    extern s32  D_8011D030;
    extern s16  D_801C91E8;
    extern s16  D_801C91EC;
    extern s32  D_80186F10;
    extern s32  D_80186F1C;
    u16 *p;
    short i;
    s32 obj;
    s32 r;
    s32 node;
    s32 e;
    Work8016 w;

    i = 0;
    p = (u16 *)&D_8011D030;
    obj = *(s32 *)(param_1 + 0x34);
    do {
        if ((p != (u16 *)param_1) && (*p == 0x34)) goto done;
        i = i + 1;
        p += 0x2c;
    } while (i < 0x1e);

    func_80149374(obj, param_1 + 4);
    r = func_801619D0((void *)obj);
    i = 0;
    if (r != 0) {
        p = (u16 *)&D_8011D030;
        do {
            if (*p == 0x11) goto ddb0;
            i = i + 1;
            p += 0x2c;
        } while (i < 0x1e);

        func_80146A6C(0x11, (void *)param_1, *(s16 *)(param_1 + 6),
                      (s16)(*(u16 *)(param_1 + 0xA) - 8),
                      *(s16 *)(param_1 + 0xE), 0, 0);
        w.x = *(u16 *)(param_1 + 6);
        w.y = *(u16 *)(param_1 + 0xA);
        w.z = *(u16 *)(param_1 + 0xE);
        func_800D20C0(&w.x, &w.vx, 0);
        w.vy = 0;
        func_800D23D0(&w.vx);
        i = 0;
        do {
            e = func_80146A6C(0x12, (void *)param_1, *(s16 *)(obj + 6),
                              *(s16 *)(obj + 0xA), *(s16 *)(obj + 0xE),
                              i, 0);
            if (e != 0) {
                *(s16 *)(e + 0x12) = w.vx;
                *(s16 *)(e + 0x16) = w.vy;
                *(s16 *)(e + 0x1A) = 0;
            }
            i = i + 2;
        } while (i < 3);
        goto done;
    }
ddb0:
    if (((D_801C91E8 != *(s16 *)(obj + 6)) || (D_801C91EC != *(s16 *)(obj + 0xE)))
        && (node = func_800D21C4(param_1, &D_80186F10, 0x18), node != 0)) {
        D_801C91E8 = *(u16 *)(obj + 6);
        D_801C91EC = *(u16 *)(obj + 0xE);
        func_800D1FC8(param_1, 7);
        *(s32 *)(param_1 + 0x20) = node;
        *(u16 *)(node + 0x1A) = 0x3000;
        *(u16 *)(node + 0x18) = 0x3000;
        *(u8 *)(node + 0x26) = 0xFF;
        *(u32 *)(node + 4) = *(u32 *)(node + 4) | 0x50000000;
        func_80128EA8(node, param_1 + 0x24, (s32)&D_80186F1C);
        ((s32 (*)(void *, void *))func_80128ED8)(node, param_1 + 0x24);
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
        return;
    }
done:
    ((void (*)(s32))func_80146C3C)(param_1);
}




void func_8016DEA4(void *a0) {

    extern void (*D_80186F3C[])(void);
    D_80186F3C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
void func_8016DEE0(s32 a0) {
    if (((s32 (*)(void *, void *))func_80128ED8)((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}




void func_8016DF20(void *a0) {

    extern void (*D_80186F44[])(void);
    D_80186F44[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_801465C0(void);
extern void func_80146C3C(u8*);




void func_8016DF5C(s32 param_1)
{

    extern Blk20 aD800AE620 __asm__("D_800AE620");
    extern s32 D_8011D030;
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern void func_8016E3CC(s32);
    extern void RotMatrixY(s32 a0, void *a1);
    extern u8 D_801C91F0;
    extern u8 D_801C91F1;
    extern u8 D_801C91F2;
    extern u8 D_801C91F4;
    extern u8 D_801C91F5;
    extern u8 D_801C91F6;

    s32 iVar8;
    short sVar1;

    iVar8 = *(s32 *)((u8 *)((void *)param_1) + 0x34);
    if ((*(u32 *)((u8 *)((void *)param_1) + 0x2c) & 0x8000) == 0) {
        unsigned short uVar7 = 0;
        u16 *psVar6 = (u16 *)&D_8011D030;
        register s32 iNew __asm__("$17");
        s32 base;
        do {
            if (psVar6 != (u16 *)((void *)param_1) && (*psVar6 == 0x41 || *psVar6 == 0x48)) {
                ((void (*)(void *))func_80146C3C)(psVar6);
            }
            uVar7++;
            psVar6 += 0x2c;
        } while (uVar7 < 0x1e);
        iNew = ((s32(*)())func_801465C0)();
        if (iNew == 0) {
            return;
        }
        base = (s32)&D_801C91F0;
        D_801C91F2 = 0xc0;
        *(u8 *)base = 0xc0;
        D_801C91F1 = 0;
        D_801C91F6 = 0;
        D_801C91F5 = 0;
        D_801C91F4 = 0;
        ((void(*)(void *, unsigned short))func_800233CC)((void *)base, 0x40);
        func_8001CD50(iNew, base);
        *(s32 *)(iNew + 0x34) = (s32)((u8 *)((void *)param_1) + 0x38);
        *(s16 *)(iNew + 0x1a) = 0;
        *(s16 *)(iNew + 0x18) = 0;
        *(u32 *)(iNew + 4) = *(u32 *)(iNew + 4) | 0x50000000;
        ((void (*)(void *))func_8016E3CC)(((void *)param_1));
        {
            register s32 t10 __asm__("$3");
            t10 = 0x10;
            *(s32 *)((u8 *)((void *)param_1) + 0x20) = iNew;
            *(s32 *)((u8 *)((void *)param_1) + 0x1c) = t10;
        }
        sVar1 = *(u16 *)((u8 *)((void *)param_1) + 2) + 1;
    } else {
        short asStack_60[20];
        Blk20_8016DF5C localMatrix;
        s32 uVar2;

        asStack_60[0] = 0;
        asStack_60[1] = 0;
        asStack_60[2] = 0x20;
        localMatrix = (*(Blk20_8016DF5C*)&aD800AE620);
        uVar2 = ((s32(*)())rand)();
        RotMatrixY((uVar2 & 0x7f00) >> 3, &localMatrix);
        ApplyMatrixSV(&localMatrix, asStack_60, asStack_60);
        *(s16 *)((u8 *)((void *)param_1) + 6) = D_80126B5E + asStack_60[0];
        *(s16 *)((u8 *)((void *)param_1) + 0xa) = D_80126B62 - ((u16)uVar2 & 0x3f);
        *(s16 *)((u8 *)((void *)param_1) + 0xe) = D_80126B66 + asStack_60[2];
        *(Blk20_8016DF5C *)((u8 *)((void *)param_1) + 0x38) = *(Blk20_8016DF5C *)((u8 *)iVar8 + 0x38);
        *(s32 *)((u8 *)((void *)param_1) + 0x2c) = 0x1000;
        *(s32 *)((u8 *)((void *)param_1) + 0x30) = 0xff;
        *(s32 *)((u8 *)((void *)param_1) + 0x1c) = 0x10;
        __asm__ __volatile__("" ::: "memory");
        sVar1 = 4;
    }
    *(s16 *)((u8 *)((void *)param_1) + 2) = sVar1;
}


DEFINE_func_8016E1CC()  /* dedup: shared engine-core @0x8016e1cc (src/shared) */


DEFINE_func_8016E26C()  /* dedup: shared engine-core @0x8016e26c (src/shared) */


DEFINE_func_8016E2E8()  /* dedup: shared engine-core @0x8016e2e8 (src/shared) */


DEFINE_func_8016E358()  /* dedup: shared engine-core @0x8016e358 (src/shared) */


DEFINE_func_8016E3CC()  /* dedup: shared engine-core @0x8016e3cc (src/shared) */


DEFINE_func_8016E460()  /* dedup: shared engine-core @0x8016e460 (src/shared) */




void func_8016E5B8(void *a0) {

    extern void (*D_80186F98[])(void);
    D_80186F98[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016E5F4()  /* dedup: shared engine-core @0x8016e5f4 (src/shared) */


DEFINE_func_8016E688()  /* dedup: shared engine-core @0x8016e688 (src/shared) */


DEFINE_func_8016E6E4()  /* dedup: shared engine-core @0x8016e6e4 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016E728);

DEFINE_func_8016E778()  /* dedup: shared engine-core @0x8016e778 (src/shared) */


extern s32 func_80017DC4(void *a0, void *a1);


// @class: regalloc-order
// @stuck: none — MATCH (74 ins); register pin $s2 forces &prim into a saved reg (§17)

                 /* 0x08 */
     /* 0x20 */




void func_8016E7C8(int param_1, short *param_2, unsigned int *param_3)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(s32, s32, void*);
    extern void func_80016ED4(void *a0);
    extern SVECTOR D_80186F58[4];
    extern s32 D_80186F78;
    extern s32 D_80186F80;
    extern s32 D_80186F88;
    extern s32 D_80186F90;

    Prim_8016E7C8_8016E7C8 prim;
    MATRIX_c2 m;
    SVECTOR tmp;
    register Prim_8016E7C8_8016E7C8 *pp __asm__("$18");   /* $s2 — force &prim into a saved reg */

    ((void (*)(void *, void *))func_80017DC4)(param_2, &m);
    m.t[0] = *(short *)(param_1 + 6);
    m.t[1] = *(short *)(param_1 + 10);
    m.t[2] = *(short *)(param_1 + 14);
    func_8004914C(&m);
    func_800491AC(&m);
    pp = &prim;
    ((void (*)(void *, void *, void *))RotTransSV)(&D_80186F58[0], pp, &tmp);
    ((void (*)(void *, void *, void *))RotTransSV)(&D_80186F58[1], &prim.v[1], &tmp);
    ((void (*)(void *, void *, void *))RotTransSV)(&D_80186F58[2], &prim.v[2], &tmp);
    ((void (*)(void *, void *, void *))RotTransSV)(&D_80186F58[3], &prim.v[3], &tmp);
    prim.v[0].vz = 3;
    prim.f5 = 0x50000000;
    prim.f0 = D_80186F78;
    prim.f1 = D_80186F80;
    prim.f2 = D_80186F88;
    prim.f3 = D_80186F90;
    prim.f4 = *param_3;
    prim.f6 = 0x27;
    func_80016ED4(pp);
}


DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016e8f0 (src/shared) */


DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016e918 (src/shared) */



// @class: struct
// @stuck: none — MATCH (36/36 ins, match_one relocation-masked)



typedef void (*Handler)(struct Entry *);


s32 func_8016E95C() {

    extern s32 D_80115218;
    extern Handler D_80186FD8[];

    struct Entry *p;
    for (p = ((struct Entry *)&D_80115218); p < &((struct Entry *)&D_80115218)[4]; p++) {
        if (p->f0 != 0) {
            D_80186FD8[p->f1](p);
        }
    }
}



/* @class: regalloc (non-coalescing delay-slot copy) + sched (load-temp hoist)
 * @stuck: none — MATCH (53/53 ins, match_one AND rtu_match in the real TU).
 *
 * Two levers, both from the cookbook:
 *
 * 1. §52a "non-coalescing delay-slot copy" + §17 zero-reg-copy (the load-bearing one).
 *    The target holds `p[0]-1` in TWO callee-saved regs: $s0 (the array index, later
 *    destroyed in place by `sll $s0,$s0,1`) and $s4 (the value stored to p[3]), created
 *    by `addu $s4,$s0,$zero` sitting in the DELAY SLOT of `jal func_800D2CA8`. A plain
 *    C `c = i;` is destroyed by cse.c canon_reg head-promotion (measured: 50 ins, -3),
 *    and every #APP-asm spelling of the copy is INELIGIBLE for a delay slot (measured:
 *    51 ins, -2 — tried `__asm__("":"=r"(c):"0"(i))`, a real-opcode
 *    `__asm__("addu %0,%1,$0")`, and the §52b RC-7 post-copy second-set barrier
 *    `c=i; __asm__("":"=r"(c):"0"(c))`; all three collapse or lose the slot).
 *    Only the `$0`-add — `register u32 zr __asm__("$0"); c = i + zr;` — emits a bare
 *    `addu` with no asm insn, so reorg can sink it into the call's delay slot.
 *    NOTE for ×138 propagation: this is a ZERO-REGISTER pin, not an allocation pin —
 *    it constrains no real value. family_sweep's §42e "skip pinned exemplar" guard is
 *    documented over-conservative (§86; the SIGABRT was our own extract_unit macro-drop,
 *    fixed in Phase 27), so this exemplar should still sweep.
 *
 * 2. Free-floating load temp for a scheduler hoist (§52a-adjacent, idiom 7).
 *    With the p+6 store written as one statement the sched2 list scheduler hoists
 *    `lbu $v0,1($a0)` ahead of `sb $s4,3($a0)` and sinks the D_80186FC4 lui/addu/lhu
 *    chain (8 mismatched, same 53-ins multiset). Splitting the load into its own
 *    statement `h = D_80186FC4[i];` placed BEFORE `p[2] = 0` (exactly what the Ghidra
 *    seed showed) puts the lhu chain right after `sh $v0,4($a0)` → 0.
 *
 * Data typing: D_80186FA8 is a WORD array (`sll $v0,$s0,2`; its element is dereferenced
 * as a buffer by func_80024054) => u8 *[]. D_80186FC0 is byte-indexed (`lbu`, no shift)
 * => u8[]. D_80186FC4 is halfword-indexed (`sll $s0,$s0,1` + `lhu`) => u16[].
 * `*(s16 *)(p + 4) = -0xD7` emits `addiu $v0,$zero,-0xD7`; 0xFF29 as a u16 would not.
 */


extern s32 func_800D2CA8(s32 a0, s32 a1);
extern void func_800D2D10(s32 a0, s32 a1, void *a2, s32 a3);
extern s32 func_80024054(u8*, u8*);
extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016E9EC(u8 *p)
{

    extern u8 *D_80186FA8[];
    extern u8 D_80186FC0[];
    extern u16 D_80186FC4[];
    register u32 zr __asm__("$0");
    int i;
    int c;
    u8 *buf;
    u8 off;
    u16 h;
    s32 r;

    i = p[0] - 1;
    off = D_80186FC0[i];
    buf = D_80186FA8[i];
    c = i + zr;
    r = func_800D2CA8(p[3], 0x1C);
    func_800D2D10(r, 1, buf + off, 0);
    ((s32 (*)(void *, void *))func_80024054)(buf, p + 8);
    p[3] = c;
    *(s16 *)(p + 4) = -0xD7;
    h = D_80186FC4[i];
    p[2] = 0;
    *(u16 *)(p + 6) = h;
    p[1] = p[1] + 1;
    ((void (*)(u8 *, s32))func_8016EC0C)(p, 0x80);
}




// @class: struct
// @stuck: none — MATCH (31/31 ins, match_one verified)

extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{

    extern u16 D_80186FCC[];
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_80186FCC[param_1->f2];
    ((void (*)(void *, int))func_8016EC0C)(param_1, 0x80);
    bVar1 = param_1->f2 + 1;
    param_1->f2 = bVar1;
    if (5 < bVar1) {
        param_1->f2 = 0x20;
        param_1->f1 = param_1->f1 + 1;
    }
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016EB3C;

// @class: loose-typing
// @stuck: none — MATCH (u8 v + 0xFF emits addiu 0xFF; v-1 would emit -1/0xffff)

extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EB3C(s32 p) {

    extern u8 D_80186FBC[];
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_80186FBC[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}



// @class: struct
// @stuck: none — MATCH (25 ins). %lo-fold via extern u16 D_80186FCC[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.


extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{

    extern u16 D_80186FCC[];
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_80186FCC[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016EC0C;

extern void func_80017B98(void *a0);

void func_8016EC0C(s32 a0, s32 a1)
{

    extern u8 D_80186FB8[];
    /* §100 draft-LOCAL type: a file-scope typedef is an EXEMPLAR-ONLY bank — extract_unit/
       remap_hseq carry only the BODY, so every sibling fails `T8016EC0C undeclared`
       (measured on ov_SC01_000). Block scope travels with the body; byte-neutral. */
 /* 0x1C */
    T8016EC0C s;
    u16 *p;
    s32 x;
    s32 y;
    s32 v;

    s.r = s.g = s.b = a1;
    s.u18 = D_80186FB8[*(u8 *)(a0 + 3)];
    s.u0C = 0x640;
    s.u0E = 0x1C8;
    s.u14 = 0;
    s.u08 = 0x28;
    s.u0A = 8;
    x = *(u16 *)(a0 + 4);
    s.x = x + 0x10;
    y = *(u16 *)(a0 + 6);
    s.u04 = 0x10;
    s.y = y;
    func_80017B98(&s);
    s.u08 = 8;
    y += 0xA;
    p = (u16 *)(a0 + 8);
    while (*p != 0xFFFF) {
        v = *p;
        switch (v) {
        case 0x1850:
        case 0x1858:
            s.x = x + 4;
            s.y = y - 7;
            break;
        case 0x3872:
            x += 2;
            p++;
            continue;
        default:
            s.x = x;
            s.y = y;
            x += 8;
            break;
        }
        s.u0C = *(u8 *)p + 0x500;
        s.u0E = (*p >> 8) + 0x100;
        p++;
        func_80017B98(&s);
    }
}


extern void func_80146C3C(u8*);
void func_8016ED6C(void) {
    ((void (*)(void))func_80146C3C)();
}


DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ed8c (src/shared) */


DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016edbc (src/shared) */


DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016edec (src/shared) */


DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016ee40 (src/shared) */


DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016ee94 (src/shared) */


DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016ef78 (src/shared) */


DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016efa8 (src/shared) */


DEFINE_func_8016EFC8()  /* dedup: shared engine-core @0x8016efc8 (src/shared) */


DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016f094 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8016F0AC);


/* RECONCILE NOTE (uc3) — the body is byte-unchanged from uc2; only the declaration
 * environment moved.  The gate error was
 *     jr_8016AB6C.c:4183 conflicting types for func_8016F0E4 || :4089 previous declaration
 * :4089 was THIS definition; :4183 is the `extern void func_8016F0E4(void);` carried inside
 * DEFINE_func_8016F4C4() (src/shared/engine_core.h:22579), which the host TU instantiates at
 * ov_SC01_077_jr_8016AB6C.c:4136 — i.e. AFTER the definition, so it is a hard error, not the
 * mere warning produced by the earlier block-scope decl in func_8016F0AC (TU:4047).
 * Byte-true signature is `void (u8 *)`; the fleet canon is `void (void)` — a PARAM/ARITY
 * disagreement on func_8016F0E4 ITSELF.
 *
 * ESCAPE TAKEN: §37/§124 ASM-LABEL ALIAS (escape 2, T0 draft-only, zero tracked-file edits).
 * The C identifier is aF8016F0E4 so this TU declares func_8016F0E4 exactly once (the macro's
 * own `extern void`), while the emitted SYMBOL is func_8016F0E4.  Both existing callers already
 * launder through a cast or take no args, so neither is perturbed:
 *   - func_8016F0AC (TU:4047-4049) casts:  ((void (*)(void *))func_8016F0E4)(&D_80126B58);
 *   - DEFINE_func_8016F4C4 calls func_8016F0E4() with 0 args against its own (void) prototype.
 * cc1-proven: preprocess+compile of the real TU with this body spliced in is free of any
 * func_8016F0E4 diagnostic (the pre-existing unrelated warnings in the TU are unchanged).
 *
 * This SUPERSEDES uc2's //@EDIT de-macroize plan (§65b) and its T2 engine_core.h alternative
 * (§75c) — neither is needed; nothing outside this unit changes, so the bank travels to the
 * 137 siblings as a plain unit (carry the alias DECLARATION line with it — §124 trap 2).
 */

extern void func_8017196C(s32 *a0, s8 a1);   /* == DEFINE_func_8017196C's own signature */
extern void func_80147060(u8 *a0);
extern void func_801511A8(u8 *a0);
extern void func_80148634(void *a0);

// @class: plumbing
// @stuck: none — MATCH (26 ins).
//   Levers: (1) §42b read-global &-cast — the TU declares D_80078EB4 as s16 but the target
//   loads it with `lhu`; the bare `D_80078EB4 != 0` gives `lh` (probed: closeness 1, WIDTH
//   lh!=lhu), so read it as *(u16 *)&D_80078EB4.  (2) both 0x1F8/0x1FC stores are s32 `sw`,
//   emitted before the first jal (the 0x1FC one lands in the delay slot by sched2 — free).
//   (3) the param needs no laundering: it is copied to $s0 at entry and the first call's
//   `move $a0,$s0` is deleted because $a0 already holds it — plain `u8 *p` reproduces this.
//   (4) §37/§124 asm-label alias — see the RECONCILE NOTE above; codegen-neutral (symbol only).

void aF8016F0E4(u8 *p) __asm__("func_8016F0E4");

void aF8016F0E4(u8 *p) {

    extern s16 D_80078EB4;                       /* fleet-canonical spelling; see the &-cast below */
    extern u8 D_800B9A17;
    *(s32 *)(p + 0x1F8) = 0;
    *(s32 *)(p + 0x1FC) = 0;
    func_8017196C((s32 *)p, 0);
    func_80147060(p);
    func_801511A8(p);
    if (*(u16 *)&D_80078EB4 != 0) {
        D_800B9A17 = 1;
    }
    func_80148634(p);
}


DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016f14c (src/shared) */


DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016f1ac (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8016F1C4;

// @class: schedule
// @stuck: none — MATCH

extern s16 currentLocationId;

s32 func_8016F1C4(void) {

    extern s32 D_80186FE8;
    extern s32 D_80126B58;
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_80186FE8;
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

    extern void (*D_80187060[])(void);
    D_80187060[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F71C()  /* dedup: shared engine-core @0x8016f71c (src/shared) */


DEFINE_func_8016F764()  /* dedup: shared engine-core @0x8016f764 (src/shared) */




void func_8016F798(void *a0) {

    extern void (*D_80187068[])(void);
    D_80187068[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F7D4()  /* dedup: shared engine-core @0x8016f7d4 (src/shared) */


DEFINE_func_8016F804()  /* dedup: shared engine-core @0x8016f804 (src/shared) */




void func_8016F834(void *a0) {

    extern void (*D_80187070[])(void);
    D_80187070[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F870()  /* dedup: shared engine-core @0x8016f870 (src/shared) */


DEFINE_func_8016F8AC()  /* dedup: shared engine-core @0x8016f8ac (src/shared) */




void func_8016F8E4(void *a0) {

    extern void (*D_80187078[])(void);
    D_80187078[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F920()  /* dedup: shared engine-core @0x8016f920 (src/shared) */


DEFINE_func_8016F95C()  /* dedup: shared engine-core @0x8016f95c (src/shared) */




void func_8016F9C4(void *a0) {

    extern void (*D_80187080[])(void);
    D_80187080[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FA00()  /* dedup: shared engine-core @0x8016fa00 (src/shared) */


DEFINE_func_8016FA44()  /* dedup: shared engine-core @0x8016fa44 (src/shared) */




void func_8016FA84(void *a0) {

    extern void (*D_80187088[])(void);
    D_80187088[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FAC0()  /* dedup: shared engine-core @0x8016fac0 (src/shared) */


DEFINE_func_8016FB10()  /* dedup: shared engine-core @0x8016fb10 (src/shared) */


DEFINE_func_8016FB50()  /* dedup: shared engine-core @0x8016fb50 (src/shared) */




void func_8016FB7C(void *a0) {

    extern void (*D_80187094[])(void);
    D_80187094[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FBB8()  /* dedup: shared engine-core @0x8016fbb8 (src/shared) */


DEFINE_func_8016FC24()  /* dedup: shared engine-core @0x8016fc24 (src/shared) */


DEFINE_func_8016FC64()  /* dedup: shared engine-core @0x8016fc64 (src/shared) */




void func_8016FC90(void *a0) {

    extern void (*D_801870A0[])(void);
    D_801870A0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FCCC()  /* dedup: shared engine-core @0x8016fccc (src/shared) */


DEFINE_func_8016FD08()  /* dedup: shared engine-core @0x8016fd08 (src/shared) */


DEFINE_func_8016FD7C()  /* dedup: shared engine-core @0x8016fd7c (src/shared) */




void func_8016FDB4(void *a0) {

    extern void (*D_801870AC[])(void);
    D_801870AC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FDF0()  /* dedup: shared engine-core @0x8016fdf0 (src/shared) */


DEFINE_func_8016FE2C()  /* dedup: shared engine-core @0x8016fe2c (src/shared) */


DEFINE_func_8016FE78()  /* dedup: shared engine-core @0x8016fe78 (src/shared) */


DEFINE_func_8016FED0()  /* dedup: shared engine-core @0x8016fed0 (src/shared) */




void func_8016FF30(void *a0) {

    extern void (*D_801870BC[])(void);
    D_801870BC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FF6C()  /* dedup: shared engine-core @0x8016ff6c (src/shared) */


DEFINE_func_8016FFA8()  /* dedup: shared engine-core @0x8016ffa8 (src/shared) */




void func_8016FFDC(void *a0) {

    extern void (*D_801870CC[])(void);
    D_801870CC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170018()  /* dedup: shared engine-core @0x80170018 (src/shared) */


DEFINE_func_80170068()  /* dedup: shared engine-core @0x80170068 (src/shared) */


DEFINE_func_801700B8()  /* dedup: shared engine-core @0x801700b8 (src/shared) */


DEFINE_func_80170100()  /* dedup: shared engine-core @0x80170100 (src/shared) */




void func_80170150(void *a0) {

    extern void (*D_801870D4[])(void);
    D_801870D4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017018C()  /* dedup: shared engine-core @0x8017018c (src/shared) */


DEFINE_func_801701C8()  /* dedup: shared engine-core @0x801701c8 (src/shared) */




void func_80170240(void *a0) {

    extern void (*D_801870DC[])(void);
    D_801870DC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017027C()  /* dedup: shared engine-core @0x8017027c (src/shared) */


DEFINE_func_801702B8()  /* dedup: shared engine-core @0x801702b8 (src/shared) */




void func_801702FC(void *a0) {

    extern void (*D_801870E4[])(void);
    D_801870E4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170338()  /* dedup: shared engine-core @0x80170338 (src/shared) */


DEFINE_func_80170374()  /* dedup: shared engine-core @0x80170374 (src/shared) */




void func_801703E0(void *a0) {

    extern void (*D_801870EC[])(void);
    D_801870EC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017041C()  /* dedup: shared engine-core @0x8017041c (src/shared) */


DEFINE_func_8017044C()  /* dedup: shared engine-core @0x8017044c (src/shared) */




void func_801704B0(void *a0) {

    extern void (*D_801870F4[])(void);
    D_801870F4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801704EC()  /* dedup: shared engine-core @0x801704ec (src/shared) */


DEFINE_func_8017051C()  /* dedup: shared engine-core @0x8017051c (src/shared) */




void func_80170548(void *a0) {

    extern void (*D_801870FC[])(void);
    D_801870FC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170584()  /* dedup: shared engine-core @0x80170584 (src/shared) */


DEFINE_func_801705C0()  /* dedup: shared engine-core @0x801705c0 (src/shared) */




void func_801705F8(void *a0) {

    extern void (*D_80187104[])(void);
    D_80187104[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170634()  /* dedup: shared engine-core @0x80170634 (src/shared) */


DEFINE_func_80170670()  /* dedup: shared engine-core @0x80170670 (src/shared) */




void func_801706AC(void *a0) {

    extern void (*D_8018710C[])(void);
    D_8018710C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801706E8()  /* dedup: shared engine-core @0x801706e8 (src/shared) */


DEFINE_func_80170718()  /* dedup: shared engine-core @0x80170718 (src/shared) */




void func_80170748(void *a0) {

    extern void (*D_80187114[])(void);
    D_80187114[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170784()  /* dedup: shared engine-core @0x80170784 (src/shared) */


DEFINE_func_801707D4()  /* dedup: shared engine-core @0x801707d4 (src/shared) */




void func_80170810(void *a0) {

    extern void (*D_8018711C[])(void);
    D_8018711C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017084C()  /* dedup: shared engine-core @0x8017084c (src/shared) */



extern void func_801484B0(s32 a0, s32 a1);
extern void func_80149350(s32 arg0);
extern s32 func_8014C168(s32*, s32);
extern void func_80171928(void *a0);

void func_801708B0(void* a0)
{

    extern void *D_8011F738;
    u16 sp10[4];
    u16 sp18[4];
    short *r;
    func_801484B0((s32)&sp10, (s32)&sp18);
    ((void (*)(s32, void *, void *))func_80149350)((s32)a0, &sp10, &sp10);
    r = (short *)((s32 (*)(s32, s32))func_8014C168)((s32)a0, (*(s32 *)&D_8011F738));
    r[3] = sp10[0];
    r[5] = sp10[1];
    r[7] = sp10[2];
    func_80171928((void *)a0);
}


DEFINE_func_80170928()  /* dedup: shared engine-core @0x80170928 (src/shared) */


DEFINE_func_80170970()  /* dedup: shared engine-core @0x80170970 (src/shared) */


DEFINE_func_801709B8()  /* dedup: shared engine-core @0x801709b8 (src/shared) */


DEFINE_func_80170A00()  /* dedup: shared engine-core @0x80170a00 (src/shared) */


DEFINE_func_80170A48()  /* dedup: shared engine-core @0x80170a48 (src/shared) */


DEFINE_func_80170A90()  /* dedup: shared engine-core @0x80170a90 (src/shared) */




void func_80170AD8(void *a0) {

    extern void (*D_80187124[])(void);
    D_80187124[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170B14()  /* dedup: shared engine-core @0x80170b14 (src/shared) */


DEFINE_func_80170B48()  /* dedup: shared engine-core @0x80170b48 (src/shared) */


DEFINE_func_80170B90()  /* dedup: shared engine-core @0x80170b90 (src/shared) */




void func_80170BD8(void *a0) {

    extern void (*D_8018712C[])(void);
    D_8018712C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170C14()  /* dedup: shared engine-core @0x80170c14 (src/shared) */


DEFINE_func_80170C44()  /* dedup: shared engine-core @0x80170c44 (src/shared) */




void func_80170C74(void *a0) {

    extern void (*D_80187134[])(void);
    D_80187134[*(u8 *)((s32)a0 + 0x215)]();
}


DEFINE_func_80170CB0()  /* dedup: shared engine-core @0x80170cb0 (src/shared) */



extern void func_801718AC(void *a0);

void func_80170CF0(void* a0)
{

    extern void *D_8011F738;
    extern s32 D_8011F73C;
    extern s32 D_8011F740;
    s32 v1;
    void *p;
    ((void (*)(s32))D_8011F738)(a0);
    v1 = *(u8 *)(a0 + 0x217);
    if (v1 == 1) {
        goto case_1;
    }
    if (v1 <= 1) {
        goto done;
    }
    if (v1 == 2) {
        goto case_2;
    }
    goto done;
case_1:
    p = (*(void * *)&D_8011F73C);
    goto call;
case_2:
    p = (*(void * *)&D_8011F740);
call:
    func_801718AC(p);
done:
    ;
}




void func_80170D68(void *a0) {

    extern void (*D_8018713C[])(void);
    D_8018713C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170da4 (src/shared) */


DEFINE_func_80170DE0()  /* dedup: shared engine-core @0x80170de0 (src/shared) */




void func_80170E34(void *a0) {

    extern void (*D_80187144[])(void);
    D_80187144[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170e70 (src/shared) */


DEFINE_func_80170EAC()  /* dedup: shared engine-core @0x80170eac (src/shared) */




void func_80170EFC(void *a0) {

    extern void (*D_8018714C[])(void);
    D_8018714C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170F38()  /* dedup: shared engine-core @0x80170f38 (src/shared) */


DEFINE_func_80170F74()  /* dedup: shared engine-core @0x80170f74 (src/shared) */




void func_80170FB0(void *a0) {

    extern void (*D_80187154[])(void);
    D_80187154[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170FEC()  /* dedup: shared engine-core @0x80170fec (src/shared) */


DEFINE_func_80171028()  /* dedup: shared engine-core @0x80171028 (src/shared) */




void func_80171064(void *a0) {

    extern void (*D_8018715C[])(void);
    D_8018715C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801710A0()  /* dedup: shared engine-core @0x801710a0 (src/shared) */


DEFINE_func_801710DC()  /* dedup: shared engine-core @0x801710dc (src/shared) */




void func_80171120(void *a0) {

    extern void (*D_80187164[])(void);
    D_80187164[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017115C()  /* dedup: shared engine-core @0x8017115c (src/shared) */


DEFINE_func_8017118C()  /* dedup: shared engine-core @0x8017118c (src/shared) */




void func_801711C0(void *a0) {

    extern void (*D_8018716C[])(void);
    D_8018716C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801711FC()  /* dedup: shared engine-core @0x801711fc (src/shared) */


DEFINE_func_80171238()  /* dedup: shared engine-core @0x80171238 (src/shared) */




void func_80171260(void *a0) {

    extern void (*D_80187174[])(void);
    D_80187174[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017129C()  /* dedup: shared engine-core @0x8017129c (src/shared) */


DEFINE_func_80171384()  /* dedup: shared engine-core @0x80171384 (src/shared) */




void func_801714E4(void *a0) {

    extern void (*D_8018717C[])(void);
    D_8018717C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80171520()  /* dedup: shared engine-core @0x80171520 (src/shared) */


DEFINE_func_8017162C()  /* dedup: shared engine-core @0x8017162c (src/shared) */


DEFINE_func_801716AC()  /* dedup: shared engine-core @0x801716ac (src/shared) */


DEFINE_func_801717A0()  /* dedup: shared engine-core @0x801717a0 (src/shared) */


DEFINE_func_801717F4()  /* dedup: shared engine-core @0x801717f4 (src/shared) */


DEFINE_func_80171824()  /* dedup: shared engine-core @0x80171824 (src/shared) */


DEFINE_func_80171854()  /* dedup: shared engine-core @0x80171854 (src/shared) */


DEFINE_func_80171884()  /* dedup: shared engine-core @0x80171884 (src/shared) */


DEFINE_func_801718AC()  /* dedup: shared engine-core @0x801718ac (src/shared) */


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


s32 func_8014C568(s16 *a0, s16 *a1);
s32 func_80012B04(s32 a0, s32 a1, s32 a2);

s16 func_80171AB0(s32 param_1, void* _arg1)
{
    register s32 v0 asm("$2");
    register s32 a0 asm("$4");
    register s32 a1 asm("$5");
    register u32 v1 asm("$3");

    v0 = ((s32 (*)(s16 *))func_8014C568)((s16 *)param_1);
    v0 = (s32)(s16)v0;

    v0 = func_80012B04(
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12),
        v0,
        4
    );

    a0 = v0;
    a1 = *(s32 *)(param_1 + 0x20);
    v0 = (s32)(s16)a0;
    v1 = *(u16 *)(a1 + 0x12);
    v1 = v1 + a0;
    v1 = v1 & 0xFFF;
    *(u16 *)(a1 + 0x12) = v1;

    return v0;
}


DEFINE_func_80171B10()  /* dedup: shared engine-core @0x80171b10 (src/shared) */


DEFINE_func_80171B44()  /* dedup: shared engine-core @0x80171b44 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80171B4C);

DEFINE_func_80171C64()  /* dedup: shared engine-core @0x80171c64 (src/shared) */


DEFINE_func_80171CC4()  /* dedup: shared engine-core @0x80171cc4 (src/shared) */


DEFINE_func_80171D1C()  /* dedup: shared engine-core @0x80171d1c (src/shared) */


DEFINE_func_80171D78()  /* dedup: shared engine-core @0x80171d78 (src/shared) */


DEFINE_func_80171E08()  /* dedup: shared engine-core @0x80171e08 (src/shared) */


DEFINE_func_80171EC8()  /* dedup: shared engine-core @0x80171ec8 (src/shared) */


DEFINE_func_80171FFC()  /* dedup: shared engine-core @0x80171ffc (src/shared) */


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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801727D0);

DEFINE_func_8017280C()  /* dedup: shared engine-core @0x8017280c (src/shared) */


DEFINE_func_80172844()  /* dedup: shared engine-core @0x80172844 (src/shared) */


void func_8017288C(void) {
}

DEFINE_func_80172894()  /* dedup: shared engine-core @0x80172894 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801728E4);

DEFINE_func_80172920()  /* dedup: shared engine-core @0x80172920 (src/shared) */


DEFINE_func_80172958()  /* dedup: shared engine-core @0x80172958 (src/shared) */


void func_801729A8(void) {
}

DEFINE_func_801729B0()  /* dedup: shared engine-core @0x801729b0 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801729F0);

DEFINE_func_80172A2C()  /* dedup: shared engine-core @0x80172a2c (src/shared) */


DEFINE_func_80172A8C()  /* dedup: shared engine-core @0x80172a8c (src/shared) */


DEFINE_func_80172ACC()  /* dedup: shared engine-core @0x80172acc (src/shared) */


void func_80172B0C(void) {
}

DEFINE_func_80172B14()  /* dedup: shared engine-core @0x80172b14 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80172B44);

DEFINE_func_80172B80()  /* dedup: shared engine-core @0x80172b80 (src/shared) */


DEFINE_func_80172BC8()  /* dedup: shared engine-core @0x80172bc8 (src/shared) */


void func_80172C48(void) {
}

extern void func_80174684(void *);
extern void func_80172CA0(void*);
void func_80172C50(void *a0) {

    extern s16 D_80126B30;
    *(struct S8_80172780 *)&D_80126B30 = *(struct S8_80172780 *)a0;
    func_80174684((void *)func_80172CA0);
}




void func_80172CA0(void *a0) {

    extern void (*D_801871C0[])(void);
    D_801871C0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172CDC()  /* dedup: shared engine-core @0x80172cdc (src/shared) */


DEFINE_func_80172D14()  /* dedup: shared engine-core @0x80172d14 (src/shared) */


void func_80172D60(void) {
}

DEFINE_func_80172D68()  /* dedup: shared engine-core @0x80172d68 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80172DAC);

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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80173078);

DEFINE_func_801730B4()  /* dedup: shared engine-core @0x801730b4 (src/shared) */


DEFINE_func_801730FC()  /* dedup: shared engine-core @0x801730fc (src/shared) */


void func_8017316C(void) {
}

DEFINE_func_80173174()  /* dedup: shared engine-core @0x80173174 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8017319C);

DEFINE_func_801731D8()  /* dedup: shared engine-core @0x801731d8 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);

void func_80173220(void * arg0)
{

    extern M2C_UNK D_80187184;
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x4000) {
        func_80147324(0x516);
        func_80019064(&D_80187184);
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


extern struct S80126B38 D_80126B38;
extern s16 D_80126B3E;
extern s16 D_80126B40;
void func_801734BC(s32 a0, s32 a1);

typedef struct { u32 a; u32 b; } __attribute__((packed, aligned(1))) Unaligned8;

void func_801733FC(s32 a0, s32 a1)
{
    func_801734BC(a0, a1);

    *(Unaligned8 *)&D_80126B38 = *(Unaligned8 *)a1;
    D_80126B3E = 1;
    D_80126B40 = 1;
}


DEFINE_func_80173460()  /* dedup: shared engine-core @0x80173460 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801734BC);



void func_80173544(void *a0) {

    extern void (*D_801871F0[])(void);
    D_801871F0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173580()  /* dedup: shared engine-core @0x80173580 (src/shared) */


DEFINE_func_801735B8()  /* dedup: shared engine-core @0x801735b8 (src/shared) */


DEFINE_func_801735EC()  /* dedup: shared engine-core @0x801735ec (src/shared) */


DEFINE_func_80173648()  /* dedup: shared engine-core @0x80173648 (src/shared) */


void func_801736A8(void) {
}

DEFINE_func_801736B0()  /* dedup: shared engine-core @0x801736b0 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801736FC);

DEFINE_func_80173738()  /* dedup: shared engine-core @0x80173738 (src/shared) */


DEFINE_func_80173770()  /* dedup: shared engine-core @0x80173770 (src/shared) */


void func_801737B0(void) {
}

DEFINE_func_801737B8()  /* dedup: shared engine-core @0x801737b8 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801737E8);

DEFINE_func_80173824()  /* dedup: shared engine-core @0x80173824 (src/shared) */


DEFINE_func_8017385C()  /* dedup: shared engine-core @0x8017385c (src/shared) */


void func_801738D4(void) {
}

DEFINE_func_801738DC()  /* dedup: shared engine-core @0x801738dc (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8017390C);

DEFINE_func_80173948()  /* dedup: shared engine-core @0x80173948 (src/shared) */


DEFINE_func_80173980()  /* dedup: shared engine-core @0x80173980 (src/shared) */


DEFINE_func_801739D8()  /* dedup: shared engine-core @0x801739d8 (src/shared) */


void func_80173A20(void) {
}

DEFINE_func_80173A28()  /* dedup: shared engine-core @0x80173a28 (src/shared) */



extern s32 func_8014C118(void*, s32, s32);
extern void func_80174684(void *);
extern void func_80173B4C(void*);

void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5)
{

    extern s32 D_80126B58;
    extern s32 D_80127508;
    extern s16 D_80126B30;
    extern s16 D_80126B3A;
    extern s16 D_80126B3C;
    extern s16 D_8011F9C8;
    extern s16 D_80126938;
    extern s32 D_8012750C;
    s32 *s1 = &D_80126B58;
    s32 v0;

    if (a2 != 0) {
        D_80127508 = ((s32 (*)(s32, s32, s32))func_8014C118)((s32)s1, a2, (s16)a3);
    } else {
        D_80127508 = 0;
    }

    v0 = s1[8];
    __builtin_memcpy(&D_80126B30, arg5, 8);
    (*(s16 *)&D_80126B38) = a0;
    D_80126B3A = a1;
    D_80126B3C = *(u16 *)(v0 + 0x12);
    func_80174684((void *)func_80173B4C);
    D_8011F9C8 = 0;
    D_80126938 = 0;
    D_8012750C = 0;
}




void func_80173B4C(void *a0) {

    extern void (*D_8018722C[])(void);
    D_8018722C[*(u8 *)((s32)a0 + 0x214)]();
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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801742A4);

DEFINE_func_801742E0()  /* dedup: shared engine-core @0x801742e0 (src/shared) */


DEFINE_func_80174318()  /* dedup: shared engine-core @0x80174318 (src/shared) */


void func_80174354(void) {
}

DEFINE_func_8017435C()  /* dedup: shared engine-core @0x8017435c (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80174384);

DEFINE_func_801743C0()  /* dedup: shared engine-core @0x801743c0 (src/shared) */


DEFINE_func_801743F0()  /* dedup: shared engine-core @0x801743f0 (src/shared) */


void func_80174430(void) {
}

DEFINE_func_80174438()  /* dedup: shared engine-core @0x80174438 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80174474);

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


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_801747CC);

DEFINE_func_80174808()  /* dedup: shared engine-core @0x80174808 (src/shared) */


void func_8017481C(void) {
}

DEFINE_func_80174824()  /* dedup: shared engine-core @0x80174824 (src/shared) */


DEFINE_func_8017484C()  /* dedup: shared engine-core @0x8017484c (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80174888);

DEFINE_func_801748C4()  /* dedup: shared engine-core @0x801748c4 (src/shared) */


void func_801748E4(void) {
}

DEFINE_func_801748EC()  /* dedup: shared engine-core @0x801748ec (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_8017496C);

DEFINE_func_801749A8()  /* dedup: shared engine-core @0x801749a8 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (105 ins). Keys: (1) single-buffer struct for the func_80049CAC/func_8012F14C
//   out-params (local_2c..local_14 are fields of ONE stack buffer, not separate scalars — else gcc
//   DCEs the unread ones + overlaps the buffer -> wrong 0x40 frame); (2) $s2/$s1 pins for iVar5/iVar4
//   (call-crossing saved regs); (3) load D_80126B66 as RAW u16 (lhu) with (s16) sext at each USE —
//   this defeats gcc's lhu+sext->lh combine fold so the target's lhu+sll+sra reappears; (4) inline
//   `iVar5 = (s16)D_80126B5E` into the f48 expression so the f28 operand load schedules first.


extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32, s32, s32);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);


s32 func_801749C8(s32 param_1)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    Buf_c1 buf;
    register s32 iVar5 __asm__("$18");
    register u32 iVar4 __asm__("$17");

    *(s32 *)(param_1 + 8) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 8), (s32)*(s16 *)(param_1 + 0xc), 4);
    *(s32 *)(param_1 + 0x10) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1a) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1a), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1c) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1c), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2e), 0x10);
    *(s16 *)(param_1 + 0x2a) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2a), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2c) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2c), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    iVar4 = (u16)D_80126B66;
    *(s32 *)(param_1 + 0x48) = *(s16 *)(param_1 + 0x28) + (iVar5 = (s16)D_80126B5E);
    *(s32 *)(param_1 + 0x4c) = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    *(s32 *)(param_1 + 0x50) = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    func_80049CAC(param_1 + 0x18, (s32)&buf);

    buf.f14 = *(s16 *)(param_1 + 0x28) + iVar5;
    buf.f18 = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    buf.f1c = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    buf.f20 = 0;
    buf.f22 = 0;
    buf.f24 = (s16)*(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&buf, (s32)&buf.f20, (s32)&buf.f28);

    *(s32 *)(param_1 + 0x3c) = buf.f28;
    *(s32 *)(param_1 + 0x40) = buf.f2a;
    *(s32 *)(param_1 + 0x44) = buf.f2c;
}


DEFINE_func_80174B6C()  /* dedup: shared engine-core @0x80174b6c (src/shared) */


DEFINE_func_80174BBC()  /* dedup: shared engine-core @0x80174bbc (src/shared) */



// @class: struct
// @stuck: none — MATCH (27 ins) via func-ptr array fold extern void(*D_80187284[])()


void func_80174BF4(void * arg0)
{

    extern void (*D_80187284[])();
    M2C_FIELD(arg0, s32 *, 0xC) = 0x12C;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x20) = 0x155;
    M2C_FIELD(arg0, s16 *, 0x22) = 0x800;
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0;
    M2C_FIELD(arg0, s16 *, 0x30) = -0x28;
    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    D_80187284[M2C_FIELD(arg0, u8 *, 4)]();
}


DEFINE_func_80174C60()  /* dedup: shared engine-core @0x80174c60 (src/shared) */


DEFINE_func_80174C80()  /* dedup: shared engine-core @0x80174c80 (src/shared) */


DEFINE_func_80174CB0()  /* dedup: shared engine-core @0x80174cb0 (src/shared) */


DEFINE_func_80174E9C()  /* dedup: shared engine-core @0x80174e9c (src/shared) */


DEFINE_func_80174ED4()  /* dedup: shared engine-core @0x80174ed4 (src/shared) */


DEFINE_func_80174EF0()  /* dedup: shared engine-core @0x80174ef0 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_037/nonmatchings/ov_SC02_037", func_80174F28);

DEFINE_func_80174F64()  /* dedup: shared engine-core @0x80174f64 (src/shared) */


DEFINE_func_80174FBC()  /* dedup: shared engine-core @0x80174fbc (src/shared) */


DEFINE_func_80175014()  /* dedup: shared engine-core @0x80175014 (src/shared) */


DEFINE_func_8017509C()  /* dedup: shared engine-core @0x8017509c (src/shared) */


DEFINE_func_80175114()  /* dedup: shared engine-core @0x80175114 (src/shared) */


DEFINE_func_80175150()  /* dedup: shared engine-core @0x80175150 (src/shared) */



extern s32 func_80175268(s32);

void func_80175184(s32* arg0) {

    extern void (*D_80187294[])(void*);
    u16 v1 = *(u16*)((u8*)arg0 + 2);
    if (v1 < 2) {
        D_80187294[v1](arg0);
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
    extern void (*D_8018729C[])(s32);
    s32 i = D_80078EC0 - 1;

    D_8018729C[i](param_1);
    ((void (*)(s32))func_80146CA0)(param_1);
}




s32 func_80175268(s32 param_1)
{

    extern u8 D_80078EC0;
    extern VoidFn D_801872B4[];
    *(u32 *)(param_1 + 0x44) |= 2;
    (*(VoidFn *)((s32)D_801872B4 + ((D_80078EC0 - 1) << 2)))();
}


DEFINE_func_801752BC()  /* dedup: shared engine-core @0x801752bc (src/shared) */


DEFINE_func_80175308()  /* dedup: shared engine-core @0x80175308 (src/shared) */


DEFINE_func_80175414()  /* dedup: shared engine-core @0x80175414 (src/shared) */


DEFINE_func_80175454()  /* dedup: shared engine-core @0x80175454 (src/shared) */


DEFINE_func_80175494()  /* dedup: shared engine-core @0x80175494 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (37 ins, relocation-masked proxy)



extern s32 func_80029504(void);

void func_801754A8(void) {

    extern u8 D_8011F7A8;
    extern unsigned char D_800B9A13;
    extern s32 D_80126B9C;
    extern DispatchFn D_801873F8[];
    u8 *p = &D_8011F7A8;
    s32 r = func_80029504();
    s32 flag = 0;

    if (((D_800B9A13 == 0) && ((D_80126B9C & 0x80) == 0)) ||
        (0x4AF < (u32)(r - 10))) {
        flag = 1;
    }
    p[9] = flag;
    D_801873F8[p[0]]((void *)p);
}



extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_8017553C(s32 *param) {

    extern void (*D_80187404[])();
    D_80187404[*(u8 *)((s32)param + 1)]();
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

    extern void (*D_80187410[])();
    D_80187410[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_801756E4()  /* dedup: shared engine-core @0x801756e4 (src/shared) */


void func_80175798(void) {
}

DEFINE_func_801757A0()  /* dedup: shared engine-core @0x801757a0 (src/shared) */


DEFINE_func_801757E0()  /* dedup: shared engine-core @0x801757e0 (src/shared) */


extern s32 func_801758FC(void);

/* func_80175820 — twin of the byte-matched func_801759D8 / func_801758FC in this same TU
 * (ov_SC01_077_jr_801734BC).  Same three-part body, different slot:
 *   part 1 tag word = ptr[2]        (0x8 vs 0x4 / 0xC)
 *   part 2 head ptr = D_8011F7A8+0x18 (== D_8011F7C0)
 *   part 3 tail ptr = D_8011F7A8+0x20 (== D_8011F7C8)
 * The two __asm__ memory fences are what keep the three parts from CSE-ing their
 * base addresses together (parts 1/2 stay absolute lui/%lo + idx*4; part 3 keeps the
 * shared `la $v1,D_8011F7A8` + 0x18/0x20 displacements).
 */

   /* size 0x14 */
    /* size 0x0C */

s32 func_80175820(void)
{
    extern s16 D_800B9A02;
    extern S_AE7BC_80175820 D_800AE7BC[];
    extern S_AF634_80175820 D_800AF634[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_8011F7A8;
    u8 *p = (u8 *)&D_8011F7A8;
    u16 *q;
    u32 *ptr;
    u32 old;
    u32 *p2;

    q = (u16 *)&(*(u16 *)&D_800B9A02);

    ptr = D_800AE7BC[*q].f0;
    old = ptr[2];
    ptr[2] = (old & 0xff000000) | (*(u32 *)(p + *q * 4 + 0x20) & 0xffffff);
    __asm__("" ::: "memory");

    p2 = *(u32 **)(p + *q * 4 + 0x18);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    __asm__("" ::: "memory");

    {
        s32 acc = D_800AF634[*q].g0;
        s32 t = *(s32 *)(p + *q * 4 + 0x18) - 0x14;
        D_800AF634[*q].g0 = acc + ((*(s32 *)(p + *q * 4 + 0x20) - t) >> 2);
    }
}


DEFINE_func_801758FC()  /* dedup: shared engine-core @0x801758fc (src/shared) */





   /* size 0x14 */
    /* size 0x0C */

s32 func_801759D8(void)
{

    extern u8 D_8011F7B1;
    extern s16 D_800B9A02;
    extern S_AE7BC_801759D8 D_800AE7BC[];
    extern S_AF634_801759D8 D_800AF634[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_8011F7A8;
    u8 *p = (u8 *)&D_8011F7A8;
    u16 *q;
    u32 *ptr;
    u32 old;
    u32 *p2;

    if (D_8011F7B1 != 0) {
        return;
    }

    q = (u16 *)&(*(u16 *)&D_800B9A02);

    ptr = D_800AE7BC[*q].f0;
    old = ptr[1];
    ptr[1] = (old & 0xff000000) | (*(u32 *)(p + *q * 4 + 0x40) & 0xffffff);
    __asm__("" ::: "memory");

    p2 = *(u32 **)(p + *q * 4 + 0x38);
    *p2 = (*p2 & 0xff000000) | (old & 0xffffff);
    __asm__("" ::: "memory");

    {
        s32 acc = D_800AF634[*q].g0;
        s32 t = *(s32 *)(p + *q * 4 + 0x38) - 0x14;
        D_800AF634[*q].g0 = acc + ((*(s32 *)(p + *q * 4 + 0x40) - t) >> 2);
    }
}



void func_80175AB8(param_1)
    s16 param_1;
{
   /* size 0x0C */
    extern S_AF634 D_800AF634[];
    extern S_AF634 D_800AF638[];

    extern u8  D_8011F7F0;
    extern u16 D_8011F7B4;
    extern u16 D_8011F7B6;
    extern s16 D_8011F7BC;
    extern s16 D_8011F7BE;
    extern s32 D_8011F804;
    extern u16 D_8011F80A;
    extern u16 D_8011F824;
    extern u8  D_8011F832;
    extern u8  D_8011F83A;
    extern u8 *D_8018732C[];

    extern u32 *func_80176D94(void *param_1, u32 param_2, s16 param_3_);
    extern u32 *func_801770E0(void *param_1, u32 param_2, s16 param_3_);
    extern u32  func_801783D0(s32 a0, s32 a1);
    extern u32 *func_80177EA4(u32 *param_1, s32 param_2, u32 param_3, s32 param_4);
    extern u32 *func_80177B5C();
    extern void func_80177940(u32 *p, u32 a_, u32 b_, u32 c_);
    extern u32 *func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4);
    extern s32 func_80024054(u8*, u8*);
    extern s32  func_8005A600(s32, s32, s32, s32, s32);

    u8 local[24];
    u8 *base;
    u8 *arr;
    u32 *slot;
    u32 *p;
    register u32 *a0v __asm__("$4");
    u32 uv;
    s32 k;
    s16 q;
    s32 r1;
    s32 a2v;
    register s32 sum __asm__("$5");
    s32 r2;
    s32 idx;
    s16 sv;

    p = (u32 *)(D_800AF638[param_1].g0 + D_800AF634[param_1].g0 * 4);
    __asm__("" : "=r"(base) : "0"(&D_8011F7F0));               /* L1 */
    arr = base - 0x48;
    slot = (u32 *)(param_1 * 4 + (s32)arr);
    *(volatile u32 *)&slot[6] = (u32)p;                        /* L2 */
    p = func_80176D94(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x51));
    p = func_801770E0(p, (s16)(D_8011F7B4 - 0x71), (s16)(D_8011F7B6 + 0x65));
    p = func_80177EA4(p, func_801783D0(D_8011F804, 0),
                      (s16)((*(u16 *)&D_8011F7BC) + 0x39), (s16)((*(u16 *)&D_8011F7BE) + 0x51));
    uv = D_8011F824;
    k = 0x3E7;
    if (uv < 1000) {
        k = uv;
    }
    sv = (s16)func_801783D0(k, 4);
    p = func_80177B5C(p, sv, D_8011F832,
                      (s16)(*(u16 *)(base - 0x34) + 0x39),
                      (s16)(*(u16 *)(base - 0x32) + 0x65));
    q = (s16)D_8011F80A / 15;
    a2v = (q & 3) * 15;
    r1 = func_801783D0((s32)(q << 16) >> 18, 8);
    r2 = func_801783D0(a2v, 0);
    a0v = p;                                                   /* L4 */
    sum = r1 + r2;                                             /* L3 */
    p = ((u32 * (*)(u32 *, s32, s32, s32))func_80177940)(
            a0v, (s16)sum,
            (s16)(*(u16 *)(base - 0x34) + 0x76),
            (s16)(*(u16 *)(base - 0x32) + 0x65));
    idx = D_8011F83A & 0x7F;
    D_8011F83A = idx;
    __asm__ __volatile__("" ::: "memory");
    ((void (*)(s32, u8 *))func_80024054)(((s32 *)D_8018732C)[idx], local);
    p = func_80178298(p, local,
                      (s16)(*(u16 *)(base - 0x34) + 0x39),
                      (s16)(*(u16 *)(base - 0x32) + 0x5B));
    func_8005A600((s32)p, 0, 0, 0x15, 0);
    *p = (((u32)p - 0x14) & 0xFFFFFF) | 0x2000000;
    slot[8] = (u32)p;
    p += 5;
    D_800AF634[param_1].g0 += ((s32)p - (s32)slot[6]) >> 2;
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80175DA8;

   /* size 0x0C */
extern u32 *func_8017742C(u32 *a0, s32 a1, s32 a2);
extern s32 func_8005A600(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_800183E0(s32 a0);

  /* 0x14 */

void func_80175DA8(param_1)
    u16 param_1;
{

    extern u8  D_8011F7F0;
    extern u8  D_800B9A13;
    extern S_AF634 D_800AF634[];
    extern S_AF634 D_800AF638[];
    extern u16 D_801872CC[];
    extern u16 D_8018731C[];
    extern u16 D_80187328;
    extern u8  D_801873A8[];
    extern u8  D_801873BC[];
    extern s32 D_801873D4[];
    extern u8  D_800D43D4;
    extern u8  D_800D4414;
    extern u8  D_800D45D4;

    u8 *base = &D_8011F7F0;
    u8 *s = base - 0x48;
    u16 *src = D_801872CC;
    Sp_80175DA8 *p;
    s16 i;
    s32 arg;
    s32 t;
    s32 fl;
    u16 v;

    p = (Sp_80175DA8 *)(D_800AF638[(s16)param_1].g0 + D_800AF634[(s16)param_1].g0 * 4);
    *(Sp_80175DA8 **)(s + (s16)param_1 * 4 + 0x28) = p;
    i = 0;
    do {
        p->tag = ((u32)(p - 1) & 0xFFFFFF) | 0x4000000;
        p->code = *(u32 *)src;
        src += 2;
        if (i < 2) {
            p->x = *src++ + *(u16 *)(s + 0xC);
            p->y = *src++ + *(u16 *)(s + 0xE);
        } else if (i == 2) {
            p->x = *src++ + *(u16 *)(s + 0x10);
            p->y = *src++ + *(u16 *)(s + 0x12);
        } else {
            p->x = *src++ + *(u16 *)(s + 0x14);
            p->y = *src++ + *(u16 *)(s + 0x16);
        }
        p->uv = *(u32 *)src;
        src += 2;
        p->wh = *(u32 *)src;
        src += 2;
        p++;
        i++;
    } while (i < 5);

    *(u8 *)(s + 7) = D_800B9A13;
    p = (Sp_80175DA8 *)func_8017742C((u32 *)p,
                                     (s16)(*(u16 *)(s + 0x10) - 0x98),
                                     (s16)(*(u16 *)(s + 0x12) + 9));
    func_8005A600((s32)p, 0, 0, 0x16, 0);
    p->tag = ((u32)(p - 1) & 0xFFFFFF) | 0x2000000;
    *(Sp_80175DA8 **)(s + (s16)param_1 * 4 + 0x30) = p;
    p++;
    {
        s32 acc = D_800AF634[(s16)param_1].g0;
        D_800AF634[(s16)param_1].g0 =
            acc + (((s32)p - *(s32 *)(s + (s16)param_1 * 4 + 0x28)) >> 2);
    }

    p = *(Sp_80175DA8 **)(s + (s16)param_1 * 4 + 0x28);
    if (base[0x48] != 0) {
        *((u8 *)p + 0xD) = 0;
    } else {
        *((u8 *)p + 0xD) = 0xA0;
    }

    {
        u8 *q1 = *(u8 **)(s + (s16)param_1 * 4 + 0x28);
        *(u16 *)(q1 + 0x22) = 0x6CD6;
        if (base[0x48] & 0x80) {
            *(u16 *)(q1 + 0x20) = D_80187328;
            arg = (s32)&D_800D45D4;
        } else {
            u16 *tt = D_8018731C;
            s32 k = base[0x48];
            if (k != 0) {
                k--;
                tt += k;
            }
            *(u16 *)(q1 + 0x20) = *tt;
            arg = D_801873D4[base[0x48]];
        }
    }
    func_800183E0(arg);

    {
        u8 *q2 = *(u8 **)(s + (s16)param_1 * 4 + 0x28);
        t = (s32)(*(u16 *)(base + 0x2E) << 16);
        if (t != 0) {
            q2[0x49] = D_801873BC[t >> 20];
        } else {
            q2[0x49] = 0xA0;
        }
    }

    {
        u8 *q3 = *(u8 **)(s + (s16)param_1 * 4 + 0x28);
        v = *(u16 *)(base + 0x40);
        if (v < 100) {
            q3[0x5D] = D_801873A8[v / 5];
        } else {
            q3[0x5D] = 0;
        }
    }

    fl = *(s16 *)(base + 0x1E) & 0x8000;
    /* §5a zero-byte sched fence: without it sched1 hoists the `la D_800D43D4`
       into the lh's load-delay slot, dropping the target's nop (-1 ins). */
    __asm__("");
    arg = (s32)&D_800D43D4;
    if (fl != 0) {
        arg = (s32)&D_800D4414;
    }
    func_800183E0(arg);
}


DEFINE_func_80176144()  /* dedup: shared engine-core @0x80176144 (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80176218;


// @class: regalloc-order
// @stuck: none — MATCH (327/327 ins, match_one MATCH; symcheck SYMS-OK 18 symbols)
//
// STRUCTURE (byte-derived, all verified against the .s):
//   $s3=st=&D_8011F7A8 (int base), $s1=st+0x48 (cach), $s2=st+0xE0 (flag), $s5=&(*(u8 *)D_80078E78) (src), $s4=param.
//   6 HUD fields synced src->cach with a chg-flag at [flag]: pairs 0x3A/0x3C and 0x3E/0x40, then 0x14(s32),
//   0x34(u16)+0x42(u8), 0x1A(s16), 0x4A(u8). Each: `if (cach==src) { if(!chg) goto skip; chg=0; } else {adjust}` + draw.
// KEY FINDINGS (reusable):
//   * Base MUST be `s32`, and the index expr written OFFSET-FIRST (`((p<<16)>>14) + st + 0x18`) — a `u8*` base
//     yields `addu rd,st,off`; the target is `addu rd,off,st`. Matches Ghidra's `(...>>0xe) + -0x7fee0840`.
//   * buf is 24 bytes, NOT Ghidra's 32: MIPS STARTING_FRAME_OFFSET = outgoing_args_size(20), so get_frame_size()
//     counts the 4-byte args-alignment gap. var=MIPS_STACK_ALIGN(4+24)=32 -> 32+24+28 -> 0x58. buf[32] gives 0x60.
//   * Block 1 uses RAW GLOBALS (D_8011F82C...) -> absolute lui/%lo; the ne-block uses `st+0x82`/`st+0x11C`
//     ($s3-relative) — both byte-confirmed; cse blocks end at labels so each region picks its own form.
//   * `ne` pinned to $v0 (+6 aligned).
//
// THE TWO LEVERS THAT CLOSED IT (SESSION-21, both byte-proven here; 18 -> 7 -> 3 -> 1 -> 0):
//   (L1) BLOCK-5 STORE DUPLICATED INTO BOTH ARMS (`if (f&1) *(e+0x32A)=0x200; else *(e+0x32A)=...+0x65;`)
//        instead of computing a phi `sv` and storing once after the merge.  Reason: sched1 is a BACKWARD list
//        scheduler and a store is a memory-unit user, so `potential_hazard` floats it to the FRONT of the
//        backward ready list => it is EMITTED ~8 insns late, which stretches the `sv`/`e` live ranges over
//        $v0/$v1/$a0/$a1 and pushes them out to $a2/$a3.  Writing the store in both arms lets cross_jump
//        merge the common tail, so the store lands first at the merge label, `sv`->$v0 and `e`->$a0, and the
//        `lui $a0` anti-dependence then PINS the schedule.  (18 mismatches -> 7.)
//   (L2) THE COMMUTATIVE-ADD OPERAND SWAP.  Target is `addu $a1,$s0,$v0` = plus(ret1, ret2) into a FRESH
//        non-call-crossing quantity that inherits the $a1 arg copy-suggestion.  Plain `sum = i6 + i4` lets
//        local_alloc TIE the dest to the dying `i6` (which crosses call2) => the whole chain is forced
//        call-saved => `addu $s0,$s0,$v0` (3 mismatched).  Accumulating (`i4 = i6 + i4`) frees $a1 but
//        expand_binop SWAPS a commutative op when target==op1, printing `addu $a1,$v0,$s0` (1 mismatched).
//        Fix: route the second call's value through a copy temp first —
//            sum = i4;  i4 = i6 + sum;
//        target(i4) != op1(sum) at EXPAND time so no swap; cse then folds sum back and deletes the copy.
//        => `addu $a1,$s0,$v0`.  MATCH.

extern void  func_80176FF4(s32);
extern void  func_80177340(s32);
extern u32   func_801783D0(s32, s32);
extern void  func_80177F84(s32, s32);
extern void func_80177DA8(u8 * p, u32 v, s32 idx);
extern void func_80177AD4(int, unsigned int);
extern s32   func_80024054(u8 *, u8 *);
extern u32 *func_80178298(u32*, u8*, short, short);
extern s32   func_8005A600(s32, s32, s32, s32, s32);

void func_80176218(s32 param_1)
{

    extern u16 D_80078EB2;
    extern u16 D_8011F82A;
    extern u16 D_8011F82C;
    extern s16 D_80078EB4;
    extern u16 D_8011F8C4;
    extern u8  D_8011F7A8;   /* st base  ($s3) */
    extern u8 D_80078E78[];   /* cur base ($s5) */
    extern u8  D_801873A8[];
    extern u8 *D_8018732C[];
    s32 st   = (s32)&D_8011F7A8;   /* $s3 */
    s32 cach = st + 0x48;          /* $s1 */
    s32 flag = st + 0xE0;          /* $s2 */
    s32 cur  = (s32)&(*(u8 *)D_80078E78);   /* $s5 */
    u8 buf[24];
    s32 ne;
    s32 t;
    u16 sA;

    /* ---- block 1: raw-global pair 0x3A/0x3C ---- */
    sA = D_80078EB2;
    t = (sA != D_8011F82A);
    if (D_8011F82C == (*(u16 *)&D_80078EB4)) {
        ne = t;
        if (ne == 0 && D_8011F8C4 == 0) goto L340;
    } else {
        s32 d = (s16)(D_8011F82C - (*(u16 *)&D_80078EB4));
        u16 nv;
        if (d < 0) {
            if (d < -10) nv = D_8011F82C + 2;
            else         nv = D_8011F82C + 1;
        } else {
            if (d > 10)  nv = D_8011F82C - 2;
            else         nv = D_8011F82C - 1;
        }
        D_8011F82C = nv;
        *(u16 *)(flag + 0x3C) = 1;
        *(u16 *)(cach + 0x3A) = *(u16 *)(cur + 0x3A);
        goto L328;
    }
    if (ne) {
        *(u16 *)(st + 0x82)  = sA;
        *(u16 *)(st + 0x11C) = 1;
    } else {
        *(u16 *)(st + 0x11C) = 0;
    }
L328:
    func_80176FF4(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18));
L340:

    /* ---- block 2: pair 0x3E/0x40 ---- */
    sA = *(u16 *)(cur + 0x3E);
    t = (sA != *(u16 *)(cach + 0x3E));
    if (*(u16 *)(cach + 0x40) == *(u16 *)(cur + 0x40)) {
        ne = t;
        if (ne == 0 && *(u16 *)(flag + 0x40) == 0) goto L444;
    } else {
        s32 d = (s16)(*(u16 *)(cach + 0x40) - *(u16 *)(cur + 0x40));
        u16 nc;
        if (d < 0) {
            if (d < -10) nc = *(u16 *)(cach + 0x40) + 2;
            else         nc = *(u16 *)(cach + 0x40) + 1;
        } else {
            if (d > 10)  nc = *(u16 *)(cach + 0x40) - 2;
            else         nc = *(u16 *)(cach + 0x40) - 1;
        }
        *(u16 *)(cach + 0x40) = nc;
        *(u16 *)(flag + 0x40) = 1;
        *(u16 *)(cach + 0x3E) = *(u16 *)(cur + 0x3E);
        goto L3E8;
    }
    if (ne) {
        *(u16 *)(cach + 0x3E) = sA;
        *(u16 *)(flag + 0x40) = 1;
    } else {
        *(u16 *)(flag + 0x40) = 0;
    }
L3E8:
    {
        s32 s0b = ((param_1 << 16) >> 14) + st;
        u16 cc;
        s32 pp;
        func_80177340(*(s32 *)(s0b + 0x18) + 0x104);
        cc = *(u16 *)(cach + 0x40);
        pp = *(s32 *)(s0b + 0x28);
        if (cc < 100)
            *(u8 *)(pp + 0x5D) = D_801873A8[cc / 5];
        else
            *(u8 *)(pp + 0x5D) = 0;
    }
L444:

    /* ---- block 3: field 0x14 (s32) ---- */
    if (*(s32 *)(cach + 0x14) == *(s32 *)(cur + 0x14)) {
        if (*(s32 *)(flag + 0x14) == 0) goto L4D0;
        *(s32 *)(flag + 0x14) = 0;
        goto L4A8;
    } else {
        s32 d = *(s32 *)(cur + 0x14) - *(s32 *)(cach + 0x14);
        s32 nd;
        if (d > 0) {
            if (d < 10) nd = *(s32 *)(cach + 0x14) + 1;
            else        nd = *(s32 *)(cach + 0x14) + 10;
        } else {
            if (d < -9) nd = *(s32 *)(cach + 0x14) - 10;
            else        nd = *(s32 *)(cach + 0x14) - 1;
        }
        *(s32 *)(cach + 0x14) = nd;
        *(s32 *)(flag + 0x14) = 1;
    }
L4A8:
    {
        u32 r = func_801783D0(*(s32 *)(cach + 0x14), 0);
        func_80177F84(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 0x208, r);
    }
L4D0:

    /* ---- block 4: field 0x34 (u16) + 0x42 (u8) ---- */
    if (*(u16 *)(cur + 0x34) != *(u16 *)(cach + 0x34)) {
        *(u16 *)(cach + 0x34) = *(u16 *)(cur + 0x34);
        *(u16 *)(flag + 0x34) = 1;
        *(u8 *)(cach + 0x42) = *(u8 *)(cur + 0x42);
    } else {
        if (*(u16 *)(flag + 0x34) == 0) goto L558;
        *(u16 *)(flag + 0x34) = 0;
    }
    {
        u16 e = 999;
        s16 r;
        if (*(u16 *)(cach + 0x34) < 1000) e = *(u16 *)(cach + 0x34);
        r = (s16)func_801783D0((s16)e, 4);
        func_80177DA8(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 0x294,
                      (s32)r, *(u8 *)(cach + 0x42));
    }
L558:

    /* ---- block 5: field 0x1A (s16) ---- */
    if (*(s16 *)(cach + 0x1A) != *(s16 *)(cur + 0x1A)) {
        *(s16 *)(cach + 0x1A) = *(s16 *)(cur + 0x1A);
        *(s16 *)(flag + 0x1A) = 1;
    } else {
        if (*(s16 *)(flag + 0x1A) == 0) goto L63C;
        *(s16 *)(flag + 0x1A) = 0;
    }
    {
        u16 f = *(u16 *)(cach + 0x1A);
        s32 e = *(s32 *)(((param_1 << 16) >> 14) + st + 0x18);
        s32 i6, i4, sum;
        /* L1: the store is written into BOTH arms so cross_jump merges the tail (see header). */
        if (f & 1) *(s16 *)(e + 0x32A) = 0x200;
        else       *(s16 *)(e + 0x32A) = *(u16 *)(st + 0x16) + 0x65;
        {
            s32 t = (((s16)f / 15) & 3) * 15;
            i6 = func_801783D0(((s16)f / 15) * 0x10000 >> 0x12, 8);
            i4 = func_801783D0((t * 0x10000) >> 16, 0);
        }
        /* L2: copy temp defeats expand_binop's commutative swap; cse folds it back (see header). */
        sum = i4;
        i4 = i6 + sum;
        ((void (*)(s32, s32))func_80177AD4)(*(s32 *)(((param_1 << 16) >> 14) + st + 0x18) + 800,
                      i4 * 0x10000 >> 0x10);
    }
L63C:

    /* ---- block 6: field 0x4A (u8) ---- */
    if (*(u8 *)(cur + 0x4A) != *(u8 *)(cach + 0x4A)) {
        *(u8 *)(cach + 0x4A) = *(u8 *)(cur + 0x4A) & 0x7F;
        *(u8 *)(flag + 0x4A) = 1;
    } else {
        if (*(u8 *)(flag + 0x4A) == 0) return;
        *(u8 *)(flag + 0x4A) = 0;
    }
    {
        s32 s0b = ((param_1 << 16) >> 14) + st;
        u8 *arg = D_8018732C[*(u8 *)(cach + 0x4A)];
        u32 *p = (u32 *)(*(s32 *)(s0b + 0x18) + 900);
        func_80024054(arg, buf);
        p = ((u32 * (*)(u32 *, u8 *, s32, s32))func_80178298)(p, buf,
                          (s16)(*(u16 *)(st + 0x14) + 0x39),
                          (s16)(*(u16 *)(st + 0x16) + 0x5B));
        func_8005A600((s32)p, 0, 0, 0x15, 0);
        *p = ((u32)((u8 *)p - 0x14) & 0xffffff) | 0x2000000;
        *(u32 **)(s0b + 0x20) = p;
    }
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80176734;

void func_80176734(s32 param_1)
{
    extern u8  D_8011F7A8;      /* st base  ($s3) */
    extern u8  D_80078E78[];    /* cur base ($s4) */
    extern s16 D_801152BA;
    extern u8  D_8011F7B0;      /* == *(u8 *)(st + 8), read absolutely (mixed addressing) */
    extern u8  D_80115214;
    extern u8  D_801873C8[];
    extern u16 D_8018731A[];
    extern u16 D_80187328;
    extern u8  D_801873BC[];
    extern s32 D_801873D4[];
    extern u8  D_800D43D4;
    extern u8  D_800D4414;
    extern u8  D_800D45D4;
    extern u8  D_800B9A13;
    extern s16 D_80126CE0;
    extern s16 D_80126D20;
    extern s32 D_80126B58;
    extern void func_800183E0(s32 a0);
    extern s32  func_801619D0(void *a0);
    extern s32  func_80161A00(s32 a0);
    extern s32  func_80161A30(s32 a0);
    extern s32  func_80161A60(s32 a0);
    extern void func_801775E0(s32 param_1, s32 param_2);

    s32 st, cach, flag, cur;
    register s32 chg  __asm__("$21");        /* L7 */
    register s32 chg2 __asm__("$16");        /* L7 */
    s32 amp;                                 /* $s0, disjoint from chg2 */
    register u16 tgt __asm__("$5");          /* L7 */
    s32 pv;                                  /* L6: the param copy that owns $s6 */
    s32 ix;                                  /* L6: block A's index, hoisted out of the block */
    u8  dum[8];                              /* L5: dead frame slot (target .frame vars=8) */

    st  = (s32)&D_8011F7A8;
    ix  = ((param_1 << 16) >> 14) + st;
    pv  = param_1;
    cach = st + 0x48;
    flag = st + 0xE0;
    cur  = (s32)&(*(u8 *)D_80078E78);

    /* ---- block A: pulse byte ---- */
    {
        register s32 p __asm__("$5");        /* L7 */
        u8 *q;
        p = *(s32 *)(ix + 0x28);
        q = (u8 *)(p + 0x3C);                /* L2: must live in the entry BB */
        if (D_801152BA != 0) {
            u8 b = D_8011F7B0;               /* L1 */
            u8 v;
            if (b < 0x80) v = b - 0x80;
            else          v = ~b - 0x80;
            q[4] = v;
            *(u8 *)(p + 4) = v;
            *(u8 *)(st + 8) = *(u8 *)(st + 8) + D_80115214;
        } else {
            *(u8 *)(p + 0x40) = 0x80;
            *(u8 *)(p + 4) = 0x80;
        }
    }

    /* ---- block B: 0x48 animation already running ---- */
    if (*(u8 *)(flag + 0x48) != 0) {
        register s32 pp __asm__("$5");       /* L7 */
        pp = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        *(u8 *)(pp + 0xD) = D_801873C8[*(u8 *)(flag + 0x48)];
        if (*(u8 *)(flag + 0x48) < 4) {
            *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
        } else {
            u8 c = *(u8 *)(cach + 0x48);
            s32 q = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
            s32 arg;
            if (c & 0x80) {
                *(u16 *)(q + 0x20) = D_80187328;
                arg = (s32)&D_800D45D4;
            } else if (c != 0) {
                *(u16 *)(q + 0x20) = D_8018731A[c];
                arg = D_801873D4[*(u8 *)(cach + 0x48)];
            } else {
                goto Lskip;
            }
            func_800183E0(arg);
        Lskip:
            if (*(u8 *)(flag + 0x48) == 5) {
                if (*(u8 *)(cach + 0x48) == 0) *(u8 *)(flag + 0x48) = 0;
                else *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
            } else if (*(u8 *)(flag + 0x48) == 10) {
                *(u8 *)(flag + 0x48) = 0;
            } else {
                *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
            }
        }
    /* ---- block C: 0x48 changed -> start the animation ---- */
    } else if (*(u8 *)(cach + 0x48) != *(u8 *)(cur + 0x48)) {
        register s32 pp __asm__("$5");       /* L7 */
        u8 k;                                /* L1: gives the `andi $v1,$v1,0xFF` index mask */
        if (*(u8 *)(cach + 0x48) == 0 && *(u8 *)(cur + 0x48) != 0)
            *(u8 *)(flag + 0x48) = 5;
        else
            *(u8 *)(flag + 0x48) = 0;
        *(u8 *)(cach + 0x48) = *(u8 *)(cur + 0x48);
        pp = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        k = *(u8 *)(flag + 0x48);
        *(u8 *)(flag + 0x48) = k + 1;
        *(u8 *)(pp + 0xD) = D_801873C8[k];
    }

    /* ---- block D: field 0x2E (equality-first: the ne-arm must be out of line) ---- */
    if (*(s16 *)(cach + 0x2E) == *(s16 *)(cur + 0x2E)) {
        if (*(s16 *)(flag + 0x2E) == 0) goto L9C0;
        *(s16 *)(flag + 0x2E) = 0;
    } else {
        *(s16 *)(cach + 0x2E) = *(s16 *)(cur + 0x2E);
        *(s16 *)(flag + 0x2E) = 1;
    }
    {
        s32 pp = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        s32 t = (s32)(*(u16 *)(cach + 0x2E) << 16);
        if (t != 0) *(u8 *)(pp + 0x49) = D_801873BC[t >> 20];
        else        *(u8 *)(pp + 0x49) = 0xA0;
    }
L9C0:

    /* ---- block E: field 0x1E sign flip ---- */
    {
        s32 fa = *(s16 *)(cach + 0x1E) & 0x8000;
        s32 fb = *(s16 *)(cur + 0x1E) & 0x8000;
        if (fa != fb) {
            s32 arg;
            if (fa != 0) {
                *(s16 *)(cach + 0x1E) = 0;
                arg = (s32)&D_800D43D4;
            } else {
                *(s16 *)(cach + 0x1E) = -0x8000;
                arg = (s32)&D_800D4414;
            }
            func_800183E0(arg);
        }
    }

    /* ---- block F: mode byte -> chg ---- */
    {
        u8 m = D_800B9A13;                   /* L1 */
        if (m != 3) {                        /* inverted: `chg = 0` belongs out of line */
            register s32 t __asm__("$2");    /* L3a: pin + 2 uses keeps `chg = t` alive */
            t = (*(u8 *)(st + 7) != m);
            chg = t;
            if (t != 0) *(u8 *)(st + 7) = m;
        } else {
            chg = 0;
        }
    }

    /* ---- block G: switch on cur[0x48] (cases 3/4/5 cross-jump onto one tail) ---- */
    amp = 0;
    switch (*(u8 *)(cur + 0x48)) {
    case 3:
        if (func_801619D0(&D_80126B58) != 0) amp = 0xFF;
        break;
    case 4:
        if (func_80161A00((s32)&D_80126B58) != 0) amp = 0xFF;
        break;
    case 5:
        if (func_80161A30((s32)&D_80126B58) != 0) amp = 0xFF;
        break;
    case 6:
        if (func_80161A60((s32)&D_80126B58) != 0) amp = 0xBA;
        break;
    }

    /* ---- block H: amp != 0 short-circuit ---- */
    {
        s32 av;
        av = amp;
        __asm__("" : "=r"(av) : "0"(av));    /* L3b: keeps the `move $v0,$s0` at the merge */
        if (av != 0) {
            *(u8 *)(flag + 0x47) = 1;
            *(u8 *)(cach + 0x4B) = *(u8 *)(cur + 0x48) | 0xF0;
            *(u8 *)(cach + 0x47) = ((s32)D_80126D20 << 7) / av;
            goto Ltail;
        }
    }

    if (*(u8 *)(cach + 0x4B) >= 0xF0) *(u8 *)(cach + 0x4B) = 0;

    /* ---- block I: target level + change flag.  The lhu is unconditional (target loads
       both the signed and the unsigned view of D_80126CE0 up front). ---- */
    tgt = *(u16 *)&D_80126CE0;
    if (D_80126CE0 != 0) {
        u16 v;                               /* dies at the mask -> destructive `andi $v1,$v1` */
        register s32 t __asm__("$2");
        v = tgt;
        *(u8 *)(cach + 0x4B) = v;
        t = (*(u8 *)(cach + 0x47) != (v & 0xFF));
        __asm__("" : "=r"(t) : "0"(t));      /* L3b */
        chg2 = t;
    } else {
        u32 cv = *(u8 *)(cach + 0x47);       /* L8: one load, two compares, no re-mask */
        tgt = *(u8 *)(cur + 0x47);
        chg2 = 0;
        if (cv != tgt || cv == 0x80) chg2 = 1;
        if (*(u8 *)(cur + 0x47) != 0 && *(u8 *)(cach + 0x4B) != 0) {
            *(u8 *)(cach + 0x4B) = 0;
            *(u8 *)(cach + 0x47) = *(u8 *)(cur + 0x47);
        }
    }

    /* ---- block J: nothing-changed fast path.  The target re-tests chg after the flag load;
       the fence below is what stops cse from folding that second test away. ---- */
    {
    register s32 c __asm__("$3");
    c = chg;
    if (chg2 != 0) goto Lbig;
    if (c != 0) goto Lbig;
    if (*(u8 *)(flag + 0x47) == 0) goto Ltail;
    __asm__("" : "=r"(c) : "0"(c));          /* L3b */
    if (c == 0) goto Lzero;
    }
Lbig:
    /* ---- block K: slew cach[0x47] toward tgt ---- */
    {
        u32 c = *(u8 *)(cach + 0x47);
        s32 sv = (s16)tgt;                   /* L8 */
        if ((s32)c < sv) {
            *(u8 *)(cach + 0x47) = tgt;
        } else {
            if (sv != 0) *(u8 *)(cach + 0x47) = c - 3;   /* L4: store in BOTH arms */
            else         *(u8 *)(cach + 0x47) = c - 8;
            c = *(u8 *)(cach + 0x47);        /* stays a real lbu because of L4 */
            if (c == 0 || c > 0x80) {
                *(u8 *)(cach + 0x47) = 0;
                *(u8 *)(cach + 0x4B) = 0;
            } else if ((s32)c < (s16)tgt) {  /* fresh EBB -> the sll/sra is recomputed */
                *(u8 *)(cach + 0x47) = tgt;
            }
        }
        *(u8 *)(flag + 0x47) = 1;
    }
    goto Ltail;
Lzero:
    *(u8 *)(flag + 0x47) = 0;
Ltail:

    /* ---- block L: tail.  m+5 / m+9 are separate temps: `lhu + (m+5)`, not `(lhu + m) + 5`. ---- */
    {
        s32 b = ((pv << 16) >> 14) + st;
        s32 m = (*(u8 *)(st + 7) != 0) << 8;
        s32 m5 = m + 5;
        s32 m9 = m + 9;
        *(u16 *)(*(s32 *)(b + 0x28) + 0x32) = *(u16 *)(st + 0x12) + m5;
        func_801775E0(*(s32 *)(b + 0x28) + 0x64, (s16)(*(u16 *)(st + 0x12) + m9));
    }
}


DEFINE_func_80176D00()  /* dedup: shared engine-core @0x80176d00 (src/shared) */


DEFINE_func_80176D94()  /* dedup: shared engine-core @0x80176d94 (src/shared) */


DEFINE_func_80176FF4()  /* dedup: shared engine-core @0x80176ff4 (src/shared) */


DEFINE_func_801770E0()  /* dedup: shared engine-core @0x801770e0 (src/shared) */


DEFINE_func_80177340()  /* dedup: shared engine-core @0x80177340 (src/shared) */


DEFINE_func_8017742C()  /* dedup: shared engine-core @0x8017742c (src/shared) */


DEFINE_func_801775E0()  /* dedup: shared engine-core @0x801775e0 (src/shared) */


DEFINE_func_801776EC()  /* dedup: shared engine-core @0x801776ec (src/shared) */


DEFINE_func_80177784()  /* dedup: shared engine-core @0x80177784 (src/shared) */


DEFINE_func_801777BC()  /* dedup: shared engine-core @0x801777bc (src/shared) */





// @class: regalloc-order
// @stuck: none — MATCH
void func_801778A8(int param_1, unsigned int param_2, short param_3, short param_4) {
    register unsigned int uVar1 __asm__("$2");
    register unsigned int nib __asm__("$3");
    int iVar2;
    register int im1 __asm__("$11");
    int p4;
    register char *p __asm__("$7");
    short iVar4;
    unsigned short uVar5;
    register unsigned int mask __asm__("$12");

    uVar5 = 0x100;
    iVar2 = (int)param_3;
    iVar4 = 0;
    if (0 < iVar2) {
        im1 = iVar2 - 1;
        p4 = (int)param_4;
        mask = ~0x100;
        p = (char *)(param_1 + 0xc);
        do {
            uVar1 = (param_2 << 16) >> 28;
            nib = uVar1;
            if (((uVar1 != 0) || ((int)iVar4 == im1)) ||
                ((int)iVar4 == p4)) {
                uVar5 = 0;
            }
            param_2 = param_2 << 4;
            *p = (char)(nib * 8 + 8);
            *(unsigned short *)(p - 2) = uVar5 | (*(unsigned short *)(p - 2) & mask);
            iVar4 = iVar4 + 1;
            p = p + 0x14;
        } while ((int)iVar4 < iVar2);
    }
    return;
}


DEFINE_func_80177940()  /* dedup: shared engine-core @0x80177940 (src/shared) */


DEFINE_func_80177AD4()  /* dedup: shared engine-core @0x80177ad4 (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80177B5C;

/* func_80177B5C - MATCH (147/147 ins), wave23.
 *
 * Seed: .run/near6/func_80177B5C_ils.c (permuter-improved, closeness 7).
 * Two residual clusters remained; both cracked, each by a sourced gcc-2.7.2 mechanism.
 *
 * CLUSTER C (idx 86-89) - the "cl | ((n*8+8) | 0x4000)" re-association.
 *   NOT a cse fold. It happens in the FRONT END: fold-const.c fold(), the `associate:`
 *   arm at :3685. For `A | (X | C)`, split_tree(arg1) (:3759, decomposer at :882) splits
 *   arg1 into var=X / con=C because TREE_CONSTANT(op1) holds, then rebuilds it as
 *   `(A | C) | X` at :3785. Verified in the FIRST RTL dump (t.i.rtl insn 215 already
 *   reads `(ior v1 16384)`), so no RTL-level lever (the cse if/else diamond, tie or
 *   volatile barriers, operand swap, shift-vs-multiply) can ever reach it.
 *   ANTIDOTE: hoist the inner IOR into its own statement. The outer arg1 is then a
 *   VAR_DECL, split_tree returns 0, and the associate arm is skipped. (This function
 *   already proved the shape at `tt = uv | 0x1000; p[3] = cl | tt;`, which matched.)
 *
 *   That exposed a REGALLOC residual: the chain landed in $a3 (`sll a3,a3,3`) instead
 *   of $v0. Cause: `n` was pinned to a HARD reg, and local-alloc.c combine_regs():1798
 *   unconditionally records a dying hard-reg SOURCE in qty_phys_sugg[] for the dest
 *   pseudo, so the shift dest inherited $a3. A *pseudo* source cannot do that - :1763
 *   bails when reg_qty[ureg] < 0 (i.e. not block-local), and the target's `n` crosses
 *   the join, so it is exactly such a pseudo.
 *   ANTIDOTE: move the pin off `n` (which dies into the shift) onto `nn` (the tested
 *   value). `nn` pinned to $2 keeps the two distinct so the `addu $a3,$v0,$zero` copy
 *   survives (combine_regs :1841 refuses to tie when the DEST is non-block-local),
 *   while `n` stays a pseudo and the shift chain gets an ordinary local quantity ->
 *   $v0 - which also restores the target schedule, because the $v0 anti-dependence on
 *   `sw $v0,-0x4($a1)` is what stops sched2 hoisting the chain above the store.
 *   [7 -> 8 -> 3]
 *
 * CLUSTER B (idx 24-27) - `lui $t0,0x300` two slots early.
 *   Pure sched1 LUID tie-break, read straight off the -da trace (t.i.sched, T-36):
 *   ready = { 58 (7f000001), 72 (7f000001), ... } - insn 58 (lui $t0) IS birthing-
 *   boosted (sched.c birthing_insn_p:2469 works on hard regs too; reg_n_sets[$t0]==1),
 *   so 58/71/72 all tie at max_priority and rank_for_schedule:2427 falls through to
 *   DESCENDING LUID. Source order put `ca = 0x3000000;` before the mask, so
 *   LUID(58) < LUID(72) and the lui was placed first.
 *   (The companion mask 0xFFFFFF correctly stays at idx 6-7 because lui+ori is TWO
 *   sets of $t1 -> reg_n_sets==2 -> no boost -> it sinks to the block head. Same
 *   mechanism, opposite sign - the model predicts both.)
 *   ANTIDOTE: split the mask into its own statement (`gg`) and materialise the
 *   constant BETWEEN it and the OR, so expand emits addiu, and, lui, or in that order
 *   and LUID(58) > LUID(72). Sweeping the plain statement position of `ca = ...` was
 *   inert (all 11 slots scored 3) - only interposing the temp moves the LUID past the
 *   AND. [3 -> 0]
 *
 * Dead ends measured, not guessed: pin nv to $2 = 27; reuse tt = 24; reuse uv = 29;
 * two-step |= = 15; unpin n = 84 (146 ins, the copy coalesces away); unpin ca = 139;
 * ca as a bare literal = 139 (145 ins - cse merges it with the loop copy, so the hard
 * pin is what keeps the pre-loop and in-loop constants separate); both literal = 143;
 * `(ca = 0x3000000)` as an assignment-EXPRESSION = 114 (148 ins, extra move); reusing
 * the existing `g` for the mask temp instead of a fresh one = 8 (g has a 2nd set later).
 */
u32 *func_80177B5C(p, bits, tbli, x, y)
u32 *p;
u32 bits;
s32 tbli;
s32 x;
s32 y;
{

    extern u8 D_801873F0[];
register u32 bb __asm__("$14");
  u32 *q;
register u32 v __asm__("$25");
register u32 cl __asm__("$3");
register u32 cs __asm__("$5");
register u32 ca __asm__("$8");
  s16 i;
  u32 mk1;
  u32 cc1;
  u32 flag;
register u32 nn __asm__("$2");
  u32 n;
register u32 t __asm__("$13");
  u32 col;
  u32 uv;
  u32 tt;
  u32 nv;
  u32 x1;
  u32 x2;
  u32 w;
  u32 g;
  u32 gg;
  u32 w3;
register u32 yr __asm__("$16");
register u32 yt __asm__("$4");
register u32 tr __asm__("$21");
register u32 xr __asm__("$17");
register u32 c3 __asm__("$18");
register s32 ff __asm__("$19");
register s32 two __asm__("$20");
  yt = y;
  tr = tbli;
__asm__("" : "=r"(tr) : "0"(tr));
  xr = x;
__asm__("" : "=r"(xr) : "0"(xr));
  mk1 = 0xFFFFFF;
  cc1 = 0x74808080;
  bb = bits;
  t = x + 0xE;
  flag = 0x1000000;
  i = 0;
  two = 2;
  ff = 255;
  ;
  v = D_801873F0[(s16) tbli];
  gg = ((u32) (p - 5)) & mk1;
  ca = 0x3000000;
  p[0] = gg | ca;
  x1 = (x - 3) & 0xFFFF;
  x2 = (x + 5) & 0xFFFF;
  p[1] = cc1;
  yr = yt;
__asm__("" : "=r"(yr) : "0"(yr));
  yt = (s16) yt;
  cs = (yt + 1) << 16;
  w = cs | x1;
__asm__("" : "=r"(w) : "0"(w));
  cl = ((v << 6) | 0x4016) << 16;
  p[2] = w;
  p[3] = cl | 0x1800;
  p += 5;
  p[0] = (((u32) (p - 5)) & mk1) | ca;
  p[1] = cc1;
  p[2] = cs | x2;
  p[3] = cl | 0x1808;
  p += 5;
  q = p;
  yt = yt << 16;
  {
    for (; i < 3; i++)
    {
      nn = ((bb << 16) >> 18) >> 10;
      n = nn;
      if (((nn != 0) || (i == two)) || (i == ff))
      {
        flag = 0;
      }
      q[0] = (((u32) (q - 5)) & 0xFFFFFF) | 0x3000000;
      q[2] = (yt | (t & 0xFFFF)) | flag;
      col = 0x74808080;
      q[1] = col;
      nv = ((n * 8) + 8) | 0x4000;
      q[3] = cl | nv;
      q += 5;
      t += 8;
      bb <<= 4;
    }

  }
  p = q;
__asm__("" : "=r"(v) : "0"(v));
  g = (((u32) (p - 5)) & 0xFFFFFF) | 0x3000000;
__asm__ __volatile__("");
  cs = yr << 16;
  p[0] = g;
  w3 = cs | ((xr + 0x2A) & 0xFFFF);
__asm__ __volatile__("");
  cl = ((v << 6) | 0x4016) << 16;
  uv = ((s16) tr) << 4;
  p[2] = w3;
  tt = uv | 0x1000;
  p[1] = col;
  p[3] = cl | tt;
  p += 5;
  p[0] = (((u32) (p - 5)) & 0xFFFFFF) | 0x3000000;
__asm__ __volatile__("");
  cs = cs | ((xr + 0x32) & 0xFFFF);
  uv = uv | 0x1008;
  cl = cl | uv;
  p[1] = col;
  p[2] = cs;
  p[3] = cl;
  p += 5;
__asm__("" :: "r"(tr), "r"(xr));
  return p;
}


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80177DA8;


void func_80177DA8(p, v, idx)
u8 *p;
u32 v;
s16 idx;
{

    extern u8 D_801873F0[];
    u8 *r;
    u16 c;
    u16 flag;
    u32 n;
    u8 m;
    s16 i;
    u8 t;
    u32 x;
    u32 uv;
    u32 w1;
    u32 w2;

    flag = 0x100;
    i = 0;
    t = D_801873F0[idx];
    c = (t << 6) | 0x4016;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    r = p;
    do {
        n = (v << 16) >> 28;
        m = n;
        if (n != 0 || i == 2 || i == 0xFF) {
            flag = 0;
        }
        v <<= 4;
        i++;
        *(s16 *)(r + 0xA) = flag | (*(s16 *)(r + 0xA) & ~0x100);
        *(u8 *)(r + 0xC) = m * 8 + 8;
        r += 0x14;
    } while (i < 3);
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    *(u16 *)(p + 0xE) = c;
    p += 0x14;
    x = ((t << 6) | 0x4016) << 16;
    uv = idx << 4;
    w1 = uv | 0x1000;
    *(u32 *)(p + 0xC) = x | w1;
    w2 = uv | 0x1008;
    *(u32 *)(p + 0x20) = x | w2;
}


DEFINE_func_80177EA4()  /* dedup: shared engine-core @0x80177ea4 (src/shared) */


DEFINE_func_80177F84()  /* dedup: shared engine-core @0x80177f84 (src/shared) */




DEFINE_func_80178004()  /* dedup: shared engine-core @0x80178004 (src/shared) */


DEFINE_func_80178298()  /* dedup: shared engine-core @0x80178298 (src/shared) */


DEFINE_func_801783D0()  /* dedup: shared engine-core @0x801783d0 (src/shared) */



void func_80178438(u16 *arg0) {

    extern M2C_UNK D_801C8078;
    func_8001534C(2, &D_801C8078, 0x80, 0x88, 0, 0);
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

    extern int D_80187450;
    extern int D_8018745C[];
    register int p __asm__("$16");
    register int s1byte __asm__("$17");
    p = param_1;
    if ((*(unsigned short *)(p + 0x5c) & 1) != 0) {
        s1byte = *(unsigned char *)(p + 0x5e);
        if (s1byte == 0xc) {
            ((void (*)(int))func_80019064)((int)&D_80187450);
        }
        ((void (*)(int, int))func_80131E00)(p, D_8018745C[s1byte]);
    }
}


DEFINE_func_801788B8()  /* dedup: shared engine-core @0x801788b8 (src/shared) */


typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_80178970;

// @class: regalloc-order
// @stuck: none — MATCH (result pinned to $v0 forces call-result copy to $v1 + delay-slot zero)

extern s32 func_801789AC(s32 arg0);

int func_80178970(void)
{

    extern s16 D_801C9A70;
    register int r __asm__("$2");
    int v;

    v = ((s32 (*)(void))func_801789AC)();
    r = 0;
    if (v != 0)
        r = D_801C9A70 == 0;
    return r;
}
