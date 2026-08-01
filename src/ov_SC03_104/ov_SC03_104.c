#include "common.h"
#include "../shared/engine_core.h"

DEFINE_func_80128158()  /* dedup: shared engine-core @0x80128158 (src/shared) */

DEFINE_func_80128178()  /* dedup: shared engine-core @0x80128178 (src/shared) */

DEFINE_func_80128198()  /* dedup: shared engine-core @0x80128198 (src/shared) */

DEFINE_func_801281B8()  /* dedup: shared engine-core @0x801281B8 (src/shared) */

DEFINE_func_801281D8()  /* dedup: shared engine-core @0x801281D8 (src/shared) */

DEFINE_func_801281F8()  /* dedup: shared engine-core @0x801281F8 (src/shared) */


extern s32 D_801BDB90;

s32 func_80128218(void) {
    return D_801BDB90;
}


DEFINE_func_80128228()  /* dedup: shared engine-core @0x80128228 (src/shared) */

DEFINE_func_80128248()  /* dedup: shared engine-core @0x80128248 (src/shared) */

DEFINE_func_80128268()  /* dedup: shared engine-core @0x80128268 (src/shared) */


extern u16 D_800B99F6;
extern void (*D_8018AF58[])(void);

void func_80128288(void) {
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_8018AF58[v1]();
    }
}


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
extern s32 D_801BED74;

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
        "lui   $at, %%hi(D_801BED74)\n"
        "sw    $v0, %%lo(D_801BED74)($at)\n"
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
        "lui   $v0, %%hi(D_801BED74)\n"
        "lw    $v0, %%lo(D_801BED74)($v0)\n"
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
 * at *(0x1F8003FC), calls func_800D19F0, stashes its $v0 result through D_801BED74,
 * restores $sp, then dispatches on the stored value:
 *   if (D_801BED74 != 0)  { func_8001903C(); func_80018FC8(); }
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
        "lui   $at, %%hi(D_801BED74)\n"
        "sw    $v0, %%lo(D_801BED74)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801BED74)\n"
        "lw    $v0, %%lo(D_801BED74)($v0)\n"
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
// @stuck: none — MATCH (62 ins). D_801C0428 read needed the address REMATERIALIZED
//   (lui;addiu;lw 0(reg), not the folded lui;lw %lo) AND pinned to $a0. volatile forces the
//   remat; register __asm__("$4") forces the a0 allocation (gcc otherwise picks v0). Both levers
//   required — pin-alone folds, volatile-alone lands in v0.

extern s32 D_80126B58;
extern s32 D_801C0428;
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
        /* D_801C0428 read: the target materializes &sym into $a0 then lw 0($a0) (not the folded
         * lui;lw %lo). volatile forces the rematerialize; the $4 pin forces the a0 allocation. */
        register volatile s32 *p __asm__("$4") = &D_801C0428;
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
extern s32 D_801BDB90;
extern u8 D_800AEFD0;

s32 func_801288B0(void) {
    func_8001ABBC(0, 0, &D_800AEFD0, D_801BDB90, 0);
}



// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x60 store AND arg5; writing D_800C7C60=0x60 directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AF558;
extern int D_801BDB90;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int func_801288E8(int arg0)
{
    int *p = &D_800C7C60;
    *p = 0x60;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AF558, D_801BDB90, p);
}




// @class: remat
// @stuck: none — MATCH (pointer-var forces single materialization of &D_800C7C60, reused as store base + arg5)

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern u8 D_800AF560;
extern s32 D_801BDB90;

s32 func_80128940(s32 _arg0)
{
    s32 *p = &D_800C7C60;
    *p = 0x5E;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(s32, s32, void *, s32, void *))func_8001ABBC)(0, 0, &D_800AF560, D_801BDB90, p);
}




// @class: remat
// @stuck: none — MATCH. &D_800C7C60 must be CSE'd once (pointer local `p`) so the same reg feeds the *p=13 store AND arg5; writing D_800C7C60=13 directly emits a 2nd address materialization (+1 ins).

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AECB0;
extern s32 D_801BDB90;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_80128998(void)
{
    int *p = &D_800C7C60;
    *p = 13;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AECB0, D_801BDB90, p);
}



extern s32 D_801BDB90;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_801289F0(void) {
    func_8001ABBC(0, 0, &D_800AECB8, D_801BDB90, 0);
}


extern void func_80011B7C(int);
extern void func_80011C10(void);
extern u16 D_800B99F6;
extern s16 D_800B9A00;
extern M2C_UNK (*D_8018AC94)();
extern s16 (*D_8018AC98)();

void func_80128A28(void) {
    s16 temp_v0;

    switch (D_800B99F6) {                           /* irregular */
    case 1:
        D_8018AC94();
        /* fallthrough */
    case 0:
        func_80011C10();
        return;
    case 2:
        temp_v0 = D_8018AC98();
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
extern M2C_UNK (*D_8018ACA0)();
extern s32 (*D_8018ACA4)();
extern s32 D_801BED70;

void func_80128AF4(void) {
    switch (D_800B99F6) {                           /* irregular */
    case 0:
        D_801BED70 = func_8002AF08();
        func_80011C10();
        return;
    case 1:
        D_8018ACA0();
        func_80011C10();
        return;
    case 2:
        if ((D_8018ACA4() << 0x10) != 0) {
            if (D_801BED70 == 1) {
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


typedef struct {
    s32 word0;
    s32 word4;
} CdFileLoc_80128C98;

extern CdFileLoc_80128C98 cdFileLocTable[];
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_80128C98(s32 arg0) {

    extern s16 D_8018AF70[];
    s16 idx = D_8018AF70[arg0];

    if (idx >= 0) {
        func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[idx], D_801BDB90, 0);
    } else {
        return 1;
    }
}


INCLUDE_ASM("asm/ov_SC03_104/nonmatchings/ov_SC03_104", func_80128CFC);

DEFINE_func_80128D60()  /* dedup: shared engine-core @0x80128D60 (src/shared) */

DEFINE_func_80128DB4()  /* dedup: shared engine-core @0x80128DB4 (src/shared) */

DEFINE_func_80128EA8()  /* dedup: shared engine-core @0x80128EA8 (src/shared) */

DEFINE_func_80128ED8()  /* dedup: shared engine-core @0x80128ED8 (src/shared) */

extern M2C_UNK D_801BDB94;

void func_80128FAC(u16 *arg0) {
    func_8001534C(4, &D_801BDB94, 0x80, 0x90, 0, 0);
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




extern s32 D_801BED74;

extern void func_801299C8();
extern void func_80015B6C(s32, s16, s32, s16, s32, s32, s32, s32, s32, s32);
extern void GsSortBg(s32 *, void *, u16, s32 *);
extern void GsSortFastBg(s32 *, void *, u16, s32 *);

void func_8012956C(void) {

    extern s16 D_80114EE0;
    extern u8 D_800B9A78;
    extern u8 D_801BED75[];
    extern u8 D_801BED76[];
    extern u8 D_801BED78[];
    extern u8 D_801BED79[];
    extern u8 D_801BED7A[];
    extern u8 D_801C0408;
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
            func_801299C8(D_801C0408, 1, base);
        }
        func_80015B6C(-0xA0, -0x74, 0x140, 0x8C,
                      D_801BED78[0], D_801BED78[1], D_801BED78[2],
                      D_801BED78[4], D_801BED78[5], D_801BED78[6]);
        func_80015B6C(-0xA0, 0x18, 0x140, 0x3C,
                      D_801BED78[4], D_801BED78[5], D_801BED78[6],
                      D_801BED78[8], D_801BED78[9], D_801BED78[0xA]);
        func_80015B6C(-0xA0, 0x54, 0x140, 0x28,
                      D_801BED78[8], D_801BED78[9], D_801BED78[0xA],
                      D_801BED78[0xC], D_801BED78[0xD], D_801BED78[0xE]);
        goto next;
    case_7FFE:
        func_801299C8(D_801C0408, (s16)(i * 2), base);
        func_80015B6C(-0xA0, *(s16 *)&base->f3A, 0x140, base->f3E,
                      ((u8 *)&D_801BED74)[idx], D_801BED75[idx], D_801BED76[idx],
                      D_801BED78[idx], D_801BED79[idx], D_801BED7A[idx]);
        goto next;
    do_default:
        __asm__("");
        arg0 = D_801C0408;
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


DEFINE_func_801298F4()  /* dedup: shared engine-core @0x801298F4 (src/shared) */


// @class: schedule
// @stuck: none — MATCH (158 ins, match_one relocation-masked)
//
// Levers that landed it (2 iterations, 56 mismatched -> MATCH):
//  1. §43 K&R s16-param definition: `void f(a0,a1,a2) s16 a0; s16 a1; u8 *a2;` reproduces the
//     in-place `sll $a0,$a0,16` zero-test on the arg reg + the raw-$a1 copy (`addu $a3,$a1,$zero`)
//     stashed in the jtbl branch delay slot and RE-extended per use in the case body.
//  2. §18 array-of-struct %lo-fold: three sibling extern arrays D_801BED78/1/2[] (a 4-row x 3-comp
//     RGB gradient table, stride 4) give `lui $at,%hi(sym); addu $at,$at,idx4; sb $v0,%lo(sym)($at)`
//     for the indexed case and plain `lui/sb %lo(sym+k)` for the constant-index case.
//  3. Switch CASE-ORDER = source order: the jump table dispatches case 1 to the FIRST emitted block,
//     so `case 1:` must be written before `case 0/2:` and `case 3/4:`.
//  4. THE residual (56 -> 0): the case-1 body must be written ROW-MAJOR (BE0[0],BE1[0],BE2[0],
//     BE0[4],BE1[4],BE2[4],...), i.e. the natural table fill. gcc-2.7.2's sched pass then REORDERS
//     the stores itself (BE0,BE1,BE5,BE8,BE4,BEC,BE9,BED,BE2,BE6,BEA,BEE) because the three arrays
//     are distinct declarations => provably non-aliasing. Writing the source in the target's STORE
//     order is the trap: it pins the b*255 / r*143 CSEs at their late store sites instead of letting
//     them hoist into $a0/$v1 at rows 0/1, and mis-schedules the D_801C0328 load.
//  5. Shift signedness: `u32` component locals give `srl` for r*5>>3 and g*25>>1; an explicit
//     `(s32)(x * 255) >> 4` gives `sra` for the *255 / *143 / *45 terms (mixed within one block).

extern u8 D_801C0422;
extern u8 D_801C034A;
extern u8 D_801C0328;
extern u8 D_801BED78[];
extern u8 D_801BED79[];
extern u8 D_801BED7A[];

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
            r = D_801C0422;
            g = D_801C034A;
            b = D_801C0328;
            D_801BED78[0] = r * 5 >> 3;
            D_801BED79[0] = g << 3;
            D_801BED7A[0] = (s32)(b * 255) >> 4;
            D_801BED78[4] = (s32)(r * 143) >> 4;
            D_801BED79[4] = g * 25 >> 1;
            D_801BED7A[4] = (s32)(b * 255) >> 4;
            D_801BED78[8] = (s32)(r * 255) >> 4;
            D_801BED79[8] = (s32)(g * 255) >> 4;
            D_801BED7A[8] = (s32)(b * 255) >> 4;
            D_801BED78[12] = (s32)(r * 143) >> 4;
            D_801BED79[12] = (s32)(g * 255) >> 4;
            D_801BED7A[12] = (s32)(b * 45) >> 2;
            break;
        case 0:
        case 2:
            i = arg1 * 4;
            D_801BED78[i] = arg2[0x44] * D_801C0422 >> 4;
            D_801BED79[i] = arg2[0x45] * D_801C034A >> 4;
            D_801BED7A[i] = arg2[0x46] * D_801C0328 >> 4;
            i = (arg1 + 1) * 4;
            D_801BED78[i] = arg2[0x47] * D_801C0422 >> 4;
            D_801BED79[i] = arg2[0x48] * D_801C034A >> 4;
            D_801BED7A[i] = arg2[0x49] * D_801C0328 >> 4;
            break;
        case 3:
        case 4:
            arg2[0x20] = D_801C0422 << 3;
            arg2[0x21] = D_801C034A << 3;
            arg2[0x22] = D_801C0328 << 3;
            break;
        }
    }
}

DEFINE_func_80129C40()  /* dedup: shared engine-core @0x80129C40 (src/shared) */

DEFINE_func_80129CF8()  /* dedup: shared engine-core @0x80129CF8 (src/shared) */

DEFINE_func_80129FF4()  /* dedup: shared engine-core @0x80129FF4 (src/shared) */

extern void func_8012A048(void *a0, s32 a1, u8 a2);

void func_8012A018(s32 a0, s32 a1)
{
    extern u8 D_80126948[];

    func_8012A048(D_80126948, a0, a1);
}


DEFINE_func_8012A048()  /* dedup: shared engine-core @0x8012A048 (src/shared) */

DEFINE_func_8012A094()  /* dedup: shared engine-core @0x8012A094 (src/shared) */

DEFINE_func_8012A0E0()  /* dedup: shared engine-core @0x8012A0E0 (src/shared) */

DEFINE_func_8012A100()  /* dedup: shared engine-core @0x8012A100 (src/shared) */

DEFINE_func_8012A110()  /* dedup: shared engine-core @0x8012A110 (src/shared) */



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


DEFINE_func_8012A2F4()  /* dedup: shared engine-core @0x8012A2F4 (src/shared) */

DEFINE_func_8012A304()  /* dedup: shared engine-core @0x8012A304 (src/shared) */









extern s32 func_80012F74(s32, s32, s32, s32);

void func_8012A328(void)
{

    extern s8 D_801152C0;
    extern s16 D_801152C2;
    extern s16 D_80126940;
    extern s16 D_80126942;
    extern s16 D_80126944;
    extern s16 D_80127080;
    extern s16 D_80126CAE;
    typedef struct {
        u8 pad[0x154];
        u16 f154;
        s16 f156;
        u16 f158;
    } Obj_80126B58;
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


DEFINE_func_8012A418()  /* dedup: shared engine-core @0x8012A418 (src/shared) */





DEFINE_func_8012A464()  /* dedup: shared engine-core @0x8012A464 (src/shared) */


DEFINE_func_8012A4BC()  /* dedup: shared engine-core @0x8012A4BC (src/shared) */

extern void func_8012A598(void *a0);
void func_8012A568(void (*a0)(void)) {
    func_8012A598(a0);
    a0();
}


INCLUDE_ASM("asm/ov_SC03_104/nonmatchings/ov_SC03_104", func_8012A598);

DEFINE_func_8012A5F8()  /* dedup: shared engine-core @0x8012A5F8 (src/shared) */

DEFINE_func_8012A62C()  /* dedup: shared engine-core @0x8012A62C (src/shared) */

DEFINE_func_8012A68C()  /* dedup: shared engine-core @0x8012A68C (src/shared) */

DEFINE_func_8012A6D0()  /* dedup: shared engine-core @0x8012A6D0 (src/shared) */

DEFINE_func_8012A758()  /* dedup: shared engine-core @0x8012A758 (src/shared) */

DEFINE_func_8012A79C()  /* dedup: shared engine-core @0x8012A79C (src/shared) */

DEFINE_func_8012A7D4()  /* dedup: shared engine-core @0x8012A7D4 (src/shared) */

DEFINE_func_8012A828()  /* dedup: shared engine-core @0x8012A828 (src/shared) */

DEFINE_func_8012A860()  /* dedup: shared engine-core @0x8012A860 (src/shared) */

DEFINE_func_8012A8B0()  /* dedup: shared engine-core @0x8012A8B0 (src/shared) */

DEFINE_func_8012A8E8()  /* dedup: shared engine-core @0x8012A8E8 (src/shared) */

DEFINE_func_8012A908()  /* dedup: shared engine-core @0x8012A908 (src/shared) */

DEFINE_func_8012A988()  /* dedup: shared engine-core @0x8012A988 (src/shared) */


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
extern M2C_UNK D_8018AFEC;

void func_8012ACA0(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_8018AFEC;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s16 *, 0x9A) = 0;
    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
    ((void (*)(void))func_8012AAAC)();
}
