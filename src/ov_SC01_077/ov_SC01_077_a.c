#include "common.h"
#include "../shared/engine_prelude.h"

/* ==== Phase-17 canonical-sig layer (tools/derive_canonical_sigs.py) ===================
 * ONE byte-neutral canonical signature per undeclared-stub conflict callee, so the parallel
 * hand-matching wave declares each shared callee consistently and the one-big-TU build stops
 * failing on `conflicting types` (hand-matching-process.md §7c). Form: s32 return (void->s32
 * byte-neutral, §3a-1) + s32 params (matched bodies cast int->ptr), arity from Ghidra-C + asm
 * read-before-write $a0-$a3 (agree on all 14 cached; 6 stubs call-site-validated). LOCAL to
 * this TU on purpose (reach-1 names like func_801809BC differ across overlays, so NOT in the
 * shared engine_core.h). Whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9). */
extern s32 func_8016EC0C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012B4B8();                        /* match-first, arity 1 */
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

#include "../shared/ov/func_80128158.h"

#include "../shared/ov/func_80128178.h"

#include "../shared/ov/func_80128198.h"

#include "../shared/ov/func_801281B8.h"

#include "../shared/ov/func_801281D8.h"

#include "../shared/ov/func_801281F8.h"

extern s32 D_801D7F90;

s32 func_80128218(void) {
    return D_801D7F90;
}

#include "../shared/ov/func_80128228.h"

#include "../shared/ov/func_80128248.h"

#include "../shared/ov/func_80128268.h"

extern u16 D_800B99F6;
extern void (*D_80186DB4[])(void);

void func_80128288(void) {
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_80186DB4[v1]();
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

// @class: other
// @stuck: none — MATCH (handwritten inline-asm scratchpad-stack-switch wrapper; manages its own frame, no trailing .set reorder)
/*
 * HANDWRITTEN scratchpad-stack-switch wrapper (same idiom as the byte-proven
 * func_8014ED28 / func_8014F1F4 siblings). Temporarily repoints $sp into the
 * D-cache scratchpad stack based at 0x1F8003FC, calls func_800D18DC (stashing its
 * return through D_801D9484), then func_8014607C, then func_801287B8, restoring $sp
 * around each call; finally reloads D_801D9484 and calls func_80011A3C when nonzero.
 * This variant stores $sp DIRECTLY to 0x1F8003FC (no *(0x1F8003FC) indirection).
 * Manipulating $sp is not expressible in C -> full inline asm (manages its own frame);
 * no trailing ".set reorder" (that would add a stray epilogue nop).
 */
#include "common.h"

extern s32 func_800D18DC(void);
extern void func_8014607C(void);
extern void func_801287B8(void);
extern s32 func_80011A3C(void);
extern s32 D_801D9484;

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
        "lui   $at, %%hi(D_801D9484)\n"
        "sw    $v0, %%lo(D_801D9484)($at)\n"
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
        "lui   $v0, %%hi(D_801D9484)\n"
        "lw    $v0, %%lo(D_801D9484)($v0)\n"
        "nop\n"
        "beqz  $v0, 1f\n"
        "nop\n"
        "jal   func_80011A3C\n"
        "1:\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


/* HANDWRITTEN scratchpad-stack-switch sequencer: stores $sp at the scratchpad slot
 * 0x1F8003FC and repoints $sp into the D-cache scratchpad before each engine call,
 * restoring it after. Manipulating $sp is not expressible in C; full inline asm
 * (manages its own frame). Signature pinned by engine_core.h: void func_80128678(void). */
#include "../shared/ov/func_80128678.h"

// @class: other
// @stuck: none — MATCH (handwritten full inline-asm scratchpad-stack-switch wrapper w/ branch)
/*
 * HANDWRITTEN scratchpad-stack-switch dispatcher (same idiom as func_80128564 /
 * the func_8014ED28 family): repoints $sp into the D-cache scratchpad stack held
 * at *(0x1F8003FC), calls func_800D19F0, stashes its $v0 result through D_801D9484,
 * restores $sp, then dispatches on the stored value:
 *   if (D_801D9484 != 0)  { func_8001903C(); func_80018FC8(); }
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
        "lui   $at, %%hi(D_801D9484)\n"
        "sw    $v0, %%lo(D_801D9484)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9484)\n"
        "lw    $v0, %%lo(D_801D9484)($v0)\n"
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
// @stuck: none — MATCH (62 ins). D_801DAAC0 read needed the address REMATERIALIZED
//   (lui;addiu;lw 0(reg), not the folded lui;lw %lo) AND pinned to $a0. volatile forces the
//   remat; register __asm__("$4") forces the a0 allocation (gcc otherwise picks v0). Both levers
//   required — pin-alone folds, volatile-alone lands in v0.

extern s32 D_80126B58;
extern s32 D_801DAAC0;
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
        /* D_801DAAC0 read: the target materializes &sym into $a0 then lw 0($a0) (not the folded
         * lui;lw %lo). volatile forces the rematerialize; the $4 pin forces the a0 allocation. */
        register volatile s32 *p __asm__("$4") = &D_801DAAC0;
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
extern s32 D_801D7F90;
extern u8 D_800AEFD0;

s32 func_801288B0(void) {
    func_8001ABBC(0, 0, &D_800AEFD0, D_801D7F90, 0);
}

// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x60 store AND arg5; writing D_800C7C60=0x60 directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AF558;
extern int D_801D7F90;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int func_801288E8(int arg0)
{
    int *p = &D_800C7C60;
    *p = 0x60;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AF558, D_801D7F90, p);
}


// @class: remat
// @stuck: none — MATCH (pointer-var forces single materialization of &D_800C7C60, reused as store base + arg5)

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern u8 D_800AF560;
extern s32 D_801D7F90;

s32 func_80128940(s32 _arg0)
{
    s32 *p = &D_800C7C60;
    *p = 0x5E;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(s32, s32, void *, s32, void *))func_8001ABBC)(0, 0, &D_800AF560, D_801D7F90, p);
}


// @class: remat
// @stuck: none — MATCH. &D_800C7C60 must be CSE'd once (pointer local `p`) so the same reg feeds the *p=13 store AND arg5; writing D_800C7C60=13 directly emits a 2nd address materialization (+1 ins).

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AECB0;
extern s32 D_801D7F90;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_80128998(void)
{
    int *p = &D_800C7C60;
    *p = 13;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AECB0, D_801D7F90, p);
}


extern s32 D_801D7F90;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_801289F0(void) {
    func_8001ABBC(0, 0, &D_800AECB8, D_801D7F90, 0);
}

M2C_UNK func_80010DE0();                            /* extern */
extern void func_80011B7C(int);
extern void func_80011C10(void);
extern u16 D_800B99F6;
extern s16 D_800B9A00;
extern M2C_UNK (*D_80186AF0)();
extern s16 (*D_80186AF4)();

void func_80128A28(void) {
    s16 temp_v0;

    switch (D_800B99F6) {                           /* irregular */
    case 1:
        D_80186AF0();
        /* fallthrough */
    case 0:
        func_80011C10();
        return;
    case 2:
        temp_v0 = D_80186AF4();
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


M2C_UNK func_80010DE0();                            /* extern */
extern void func_80011B7C(int);
extern void func_80011C10(void);
extern void func_8002AEF8(void);
s32 func_8002AF08();                                /* extern */
extern void func_800CFBBC(void);
s32 func_800CFBE8();                                /* extern */
extern u16 D_800B99F6;
extern M2C_UNK (*D_80186AFC)();
extern s32 (*D_80186B00)();
extern s32 D_801D9480;

void func_80128AF4(void) {
    switch (D_800B99F6) {                           /* irregular */
    case 0:
        D_801D9480 = func_8002AF08();
        func_80011C10();
        return;
    case 1:
        D_80186AFC();
        func_80011C10();
        return;
    case 2:
        if ((D_80186B00() << 0x10) != 0) {
            if (D_801D9480 == 1) {
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

#include "common.h"


extern s16 D_80186DCC[];
extern CdFileLoc cdFileLocTable[];
extern s32 D_801D7F90;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_80128C98(s32 arg0) {
    s16 idx = D_80186DCC[arg0];

    if (idx >= 0) {
        func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[idx], D_801D7F90, 0);
    } else {
        return 1;
    }
}




extern CdFileLoc cdFileLocTable[];
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_80128CFC(s32 arg0) {

    extern s16 D_80186DDC[];
    s16 idx = D_80186DDC[arg0];

    if (idx >= 0) {
        func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[idx], D_801D7F90, 0);
    } else {
        return 1;
    }
}


#include "../shared/ov/func_80128D60.h"

// @class: struct
// @stuck: none — MATCH
#include "../shared/ov/func_80128DB4.h"


#include "../shared/ov/func_80128EA8.h"

// LOAD-BEARING register pins (cookbook §17 + §25): the residual here was NOT scheduling but
// gcc-2.7.2 COPY-COALESCING — gcc folded the index-preserve copy (idc) into the multiply operand
// (`sll $v0,$a3,3` on the copy) instead of multiplying $v1 directly. Pinning idc to its target
// reg ($a3) forces the multiply onto $v1 and emits the copy separately AFTER it; routing idc+1
// through the dead $v0-pinned `cnt` lands it in $v0 (target's scratch), not back in $a3.
// Do NOT "simplify" the pins or the cnt reuse — each is byte-load-bearing (byte-gated).
#include "common.h"

#include "../shared/ov/func_80128ED8.h"


M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D7F94;

void func_80128FAC(u16 *arg0) {
    func_8001534C(4, &D_801D7F94, 0x80, 0x90, 0, 0);
    func_800153CC(5, *arg0, 0xA8, 0x90, 0x40, 0);
}


#include "../shared/ov/func_80129010.h"

extern u8 *func_8012913C(s32 a0);

u8 *func_801290DC(s32 a0, u8 *a1) {
    u8 *v1 = func_8012913C(a0 & 0xFFFF);

    if (v1 != 0) {
        *(u16 *)(v1 + 0x6) = *(u16 *)(a1 + 0x0);
        *(u16 *)(v1 + 0xA) = *(u16 *)(a1 + 0x2);
        *(u16 *)(v1 + 0xE) = *(u16 *)(a1 + 0x4);
    }
    return v1;
}


/* Callees — canonical-consistent sigs.
 * func_8001D074: canonical `void func_8001D074(s32, s32)`; widened return to s32
 *   (byte-neutral, §3a-1) because this fn uses the result.
 * func_801291C0: canonical `u8 *func_801291C0(void)` (engine_core.h DEFINE_func_801291C0).
 * func_8001CC3C: arity-4 from m2c/asm read-before-write $a0-$a3; void->s32 byte-neutral.
 */
#include "../shared/ov/func_8012913C.h"


#include "../shared/ov/func_801291C0.h"

extern void func_80129258(void);
extern void func_80129248(s16 a0);

void func_80129220(void) {
    func_80129258();
    func_80129248(1);
}

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

// @class: schedule
// @stuck: none — MATCH (72 ins)

#include "../shared/ov/func_8012944C.h"


#include "common.h"



extern s32 D_801D9484;

extern void func_801299C8();
extern void func_80015B6C(s32, s16, s32, s16, s32, s32, s32, s32, s32, s32);
extern void GsSortBg(s32 *, void *, u16, s32 *);
extern void GsSortFastBg(s32 *, void *, u16, s32 *);

void func_8012956C(void) {

    extern s16 D_80114EE0;
    extern u8 D_800B9A78;
    extern u8 D_801D9485[];
    extern u8 D_801D9486[];
    extern u8 D_801D9488[];
    extern u8 D_801D9489[];
    extern u8 D_801D948A[];
    extern u8 D_801DAAA0;
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
            func_801299C8(D_801DAAA0, 1, base);
        }
        func_80015B6C(-0xA0, -0x74, 0x140, 0x8C,
                      D_801D9488[0], D_801D9488[1], D_801D9488[2],
                      D_801D9488[4], D_801D9488[5], D_801D9488[6]);
        func_80015B6C(-0xA0, 0x18, 0x140, 0x3C,
                      D_801D9488[4], D_801D9488[5], D_801D9488[6],
                      D_801D9488[8], D_801D9488[9], D_801D9488[0xA]);
        func_80015B6C(-0xA0, 0x54, 0x140, 0x28,
                      D_801D9488[8], D_801D9488[9], D_801D9488[0xA],
                      D_801D9488[0xC], D_801D9488[0xD], D_801D9488[0xE]);
        goto next;
    case_7FFE:
        func_801299C8(D_801DAAA0, (s16)(i * 2), base);
        func_80015B6C(-0xA0, *(s16 *)&base->f3A, 0x140, base->f3E,
                      ((u8 *)&D_801D9484)[idx], D_801D9485[idx], D_801D9486[idx],
                      D_801D9488[idx], D_801D9489[idx], D_801D948A[idx]);
        goto next;
    do_default:
        __asm__("");
        arg0 = D_801DAAA0;
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
//  2. §18 array-of-struct %lo-fold: three sibling extern arrays D_801D9488/1/2[] (a 4-row x 3-comp
//     RGB gradient table, stride 4) give `lui $at,%hi(sym); addu $at,$at,idx4; sb $v0,%lo(sym)($at)`
//     for the indexed case and plain `lui/sb %lo(sym+k)` for the constant-index case.
//  3. Switch CASE-ORDER = source order: the jump table dispatches case 1 to the FIRST emitted block,
//     so `case 1:` must be written before `case 0/2:` and `case 3/4:`.
//  4. THE residual (56 -> 0): the case-1 body must be written ROW-MAJOR (BE0[0],BE1[0],BE2[0],
//     BE0[4],BE1[4],BE2[4],...), i.e. the natural table fill. gcc-2.7.2's sched pass then REORDERS
//     the stores itself (BE0,BE1,BE5,BE8,BE4,BEC,BE9,BED,BE2,BE6,BEA,BEE) because the three arrays
//     are distinct declarations => provably non-aliasing. Writing the source in the target's STORE
//     order is the trap: it pins the b*255 / r*143 CSEs at their late store sites instead of letting
//     them hoist into $a0/$v1 at rows 0/1, and mis-schedules the D_801DA998 load.
//  5. Shift signedness: `u32` component locals give `srl` for r*5>>3 and g*25>>1; an explicit
//     `(s32)(x * 255) >> 4` gives `sra` for the *255 / *143 / *45 terms (mixed within one block).

extern u8 D_801DAABA;
extern u8 D_801DA9C2;
extern u8 D_801DA998;
extern u8 D_801D9488[];
extern u8 D_801D9489[];
extern u8 D_801D948A[];

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
            r = D_801DAABA;
            g = D_801DA9C2;
            b = D_801DA998;
            D_801D9488[0] = r * 5 >> 3;
            D_801D9489[0] = g << 3;
            D_801D948A[0] = (s32)(b * 255) >> 4;
            D_801D9488[4] = (s32)(r * 143) >> 4;
            D_801D9489[4] = g * 25 >> 1;
            D_801D948A[4] = (s32)(b * 255) >> 4;
            D_801D9488[8] = (s32)(r * 255) >> 4;
            D_801D9489[8] = (s32)(g * 255) >> 4;
            D_801D948A[8] = (s32)(b * 255) >> 4;
            D_801D9488[12] = (s32)(r * 143) >> 4;
            D_801D9489[12] = (s32)(g * 255) >> 4;
            D_801D948A[12] = (s32)(b * 45) >> 2;
            break;
        case 0:
        case 2:
            i = arg1 * 4;
            D_801D9488[i] = arg2[0x44] * D_801DAABA >> 4;
            D_801D9489[i] = arg2[0x45] * D_801DA9C2 >> 4;
            D_801D948A[i] = arg2[0x46] * D_801DA998 >> 4;
            i = (arg1 + 1) * 4;
            D_801D9488[i] = arg2[0x47] * D_801DAABA >> 4;
            D_801D9489[i] = arg2[0x48] * D_801DA9C2 >> 4;
            D_801D948A[i] = arg2[0x49] * D_801DA998 >> 4;
            break;
        case 3:
        case 4:
            arg2[0x20] = D_801DAABA << 3;
            arg2[0x21] = D_801DA9C2 << 3;
            arg2[0x22] = D_801DA998 << 3;
            break;
        }
    }
}

#include "../shared/ov/func_80129C40.h"


#include "../shared/ov/func_80129CF8.h"

#include "../shared/ov/func_80129FF4.h"

extern u8 D_80126948[];
void func_8012A048(void *a0, s32 a1, u8 a2);

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

#include "../shared/ov/func_8012A568.h"

#include "common.h"

/* §71 sibling-first: this is DEFINE_func_8012A4BC (src/shared/engine_core.h L15896)
 * minus the write-back line, i.e. DEFINE_func_8012A62C (L23877) with the tail
 * constant folded to 0x30.  164-byte struct assignment => gcc-2.7.2 -O2 emits the
 * 16-byte-unrolled block-move loop (10 iters, 0xA0) + a 4-byte remainder.
 *
 * §37 asm-label alias: the canonical `struct BigCopy` lives in src/shared/engine_types.h
 * (L312, `{ s32 words[41]; }`), which match_one's `-Iinclude` cannot see.  Declaring a
 * private tag + an asm-label alias keeps the draft self-contained AND avoids redefining
 * `struct BigCopy` when this body is spliced into the real TU (which already includes
 * engine_core.h -> engine_types.h and declares `extern struct BigCopy D_80126DB8;`). */

/* S11: was a draft-local `struct BigCopy164` tag + an asm-label alias, which made this body
 * UNEXTRACTABLE (dedup_propagate refuses any body declaring an inline named struct, since two
 * macros defining the same tag would redefine it in one TU). The SHARED `struct BigCopy`
 * (src/shared/engine_types.h L312) is the identical layout and is already used this exact way at
 * engine_core.h:16158, so using it is byte-neutral and lets the fn propagate x137. */
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


// @class: schedule
// @stuck: none — MATCH (125 ins). Round-3 re-verification 2026-07-27: relocs resolved
//         mechanically (7/7 jal, 8/8 j, 2/2 hi-lo) and the 50-word jtbl diffed 50/50 against
//         tail2.data.s; all 3 levers refuted-as-variants. The only residual is the §81 jr/jtbl
//         BANKING floor (symcheck MISSING jtbl_801D7FB0 is a jr false positive — gcc emits its own
//         table with a section-relative HI16/LO16, so the splat name can never appear in the draft
//         object's relocs). Not a body defect. See "BANKING" below.
/*
 * ── RE-VERIFICATION (rounds 2 AND 3, independent re-derivations from the .s; §88e discipline) ───
 *   match_one : MATCH (125 ins).  .text = 0x1F4 = 500 B = 125 ins — the exact target size, so this
 *               is NOT a §83a length-drift masking a bad count.
 *   relocs    : ROUND 3 resolved them MECHANICALLY (objcopy the sections, decode the implicit
 *               MIPS-REL addends — the §84 trap / §88f gate). 7× R_MIPS_26 -> func_8012AAAC, all
 *               addend 0, at .text +B4/C4/100/124/158/1AC/178 — the target's 7 `jal func_8012AAAC`
 *               offsets EXACTLY. 8× R_MIPS_26 -> .text, every one resolving to 0x8012AC84, at
 *               +88/BC/D8/108/12C/164/18C/1B4 — the target's 8 `j .L8012AC84` offsets EXACTLY.
 *               1× HI16 +1× LO16 -> .rodata at +60/+68 (target's lui/lw), combined addend 0.
 *   jump tbl  : gcc's own .rodata is 0xC8 = 200 B = 50 words; ROUND 3 decoded all 50 and diffed
 *               them against asm/ov_SC01_077/data/tail2.data.s word for word —
 *               [0]=8012AC18, [1..44]=8012AC84 (default ×44), [45]=8012AC40, [46]=8012AB8C,
 *               [47]=8012ABBC, [48]=8012AB24, [49]=8012AB3C. 50/50 identical.
 *   ROUND 3 re-tested BOTH inherited levers as live variants (not assumed) and added a THIRD
 *   refutation, V3 below — the one a naive re-derivation actually lands on.
 *
 * Script/animation-command interpreter (recursive). ptr = arg0->0x90 + arg0->0x94*8, an 8-byte
 * command record; the s16 at +4 is the opcode. opcode >= 0 -> emit (arg0->0x20)->0x20 = ptr->w0
 * and latch arg0->0x98; opcode < 0 -> a 6-way switch on the negative opcode. Source case ORDER
 * (-2, -1, -4, -3, -50, -5) is fixed by the target's block layout: gcc-2.7.2 lays switch case
 * bodies in SOURCE order, and the target's blocks run 0x8012AB24, AB3C, AB8C, ABBC, AC18, AC40.
 *
 * TWO BYTE-PROVEN CODEGEN LEVERS (both needed; 16 -> 2 -> 0 mismatches):
 *  1. case -1 must be spelled `if (link != 0) { <pop-block>; break; } <else-code>` with the shared
 *     `pop:` label INSIDE the if-body (case -2 jumps into it). The inverse spelling
 *     (`if (link == 0) { ... break; } pop: ...`) inverts the branch polarity and lays the 0x4000
 *     tail inline instead of out-of-line.
 *     RE-TESTED 2026-07-27: the inverse spelling gives DIFF 14 mismatched, OPCODE-MIXED
 *     (branch,width) — idx 32/38 flip bnez/beqz and the whole pop-block shifts. CONFIRMED.
 *     (Note the shared `pop:` tail contains a CALL, so per §88a `cross_jump` will NOT factor it for
 *     you — the explicit `goto` is load-bearing, not cosmetic.)
 *  2. cookbook §49-variant / sched.md:38 (birthing_insn_p, REG_N_SETS==1 -> max_priority ->
 *     sunk late by the BACKWARD sched1). The `ptr->w0` load in case -3 must be a *distinct* local
 *     from the one in case -4: sharing one variable makes REG_N_SETS==2, kills its boost, and the
 *     two loads `lw $s0,0x90($s1)` / `lw $v1,0x0($a0)` come out transposed. With BOTH single-set,
 *     they tie at max_priority and the LUID (source-order) tie-break -- `saved` declared/assigned
 *     FIRST, `next` second -- puts them in target order at zero byte cost.
 *     RE-TESTED 2026-07-27: folding `next` into `head` gives DIFF 2 mismatched, SCHEDULE-REORDER,
 *     idx 77/78 exactly the predicted transposition. CONFIRMED — and this is the trap an
 *     independent re-derivation falls into, since one temp is the obvious spelling.
 *
 *  3. NEW, round 3 — the `goto pop` is REQUIRED; do NOT write case -2's tail longhand.
 *     V3 test: delete the `goto pop` and duplicate the 6-statement pop-block into case -2 (the
 *     obvious, goto-free spelling any independent re-derivation writes first) => DIFF **126 ins**
 *     vs 125, LENGTH-DRIFT/1, 81 mismatched. gcc-2.7.2 leaves the duplicate standing because the
 *     common suffix contains a `jal` — this is §88a reproduced from a second, independent function
 *     (the §88a evidence was all func_8017D2DC before). ⇒ For this 138-member family the explicit
 *     `goto` into a call-bearing shared tail is a TEMPLATE INVARIANT, not a stylistic choice.
 *
 * ── BANKING (§81 carve chain) — symcheck reports MISSING jtbl_801D7FB0; that is the EXPECTED jr
 *    floor, not an invented/dropped symbol: gcc emits its own table into .rodata addressed by a
 *    section-relative HI16/LO16, so the splat name is never referenced. Table content verified
 *    50/50 above. Banking still needs jr_isolate_all --only + jtbl_carve + harvest_verify.
 *
 *    ⚠ MEASURED HAZARD for whoever runs the carve — `jtbl_carve.jtbl_range()` will TRUNCATE this
 *    table. It computes `end = the next data dlabel` over `all_data_labels()`, which collects BOTH
 *    `jtbl_` and `D_` labels. splat split this ONE 50-word table across two dlabels in
 *    asm/ov_SC01_077/data/tail2.data.s:
 *        dlabel jtbl_801D7FB0   0x801D7FB0..0x801D8020   28 words
 *        dlabel D_801D8020      0x801D8020..0x801D8078   22 words   (zero xrefs anywhere in tree)
 *    so jtbl_range() returns end = 0x801D8020 => a 28-word (112 B) carve for an object that supplies
 *    200 B of .rodata. The trailing-zero trim cannot rescue it (word[27] = 0x8012AC84, non-zero).
 *
 *    THE TRUE RANGE is the WHOLE `tail2` data piece: vram 0x801D7FB0..0x801D8078 = file
 *    0xAFE58..0xAFF20 = 200 B = 50 words, confirmed three independent ways: the function's own
 *    `sltiu $v0, $v1, 0x32` = 50 entries; gcc's emitted .rodata = 0xC8 = 50 words; and the splat
 *    config, where `- [0xafe58, data, tail2]` runs exactly up to the already-carved
 *    `- [0xaff20, .rodata, ov_SC01_077_jr_8012ACE0]`. i.e. tail2 IS this table and nothing else.
 *
 *    CONSEQUENCE, and it is the good kind: func_8012AAAC lives in subseg ov_SC01_077_a, which
 *    ALREADY holds a .rodata carve at `- [0xafe44, .rodata, ov_SC01_077_a]` ending exactly at
 *    0xafe58. Carved correctly, the two are ADJACENT and same-subseg, so §8a case (a) MERGE applies
 *    and ov_SC01_077_a keeps ONE contiguous .rodata run 0xAFE44..0xAFF20 — no §81 NON-CONTIGUOUS
 *    refusal, no jr_isolate_all needed for contiguity. Base 0x801D7FB0 is 8-aligned, so gcc's
 *    `.rdata .align 3` lands with no pad (JTBL_PADS stays 0).
 *
 *    ⇒ Either drop the spurious `D_801D8020` dlabel before running jtbl_carve, or teach
 *    jtbl_range() to skip a `D_` label that has no xref and whose predecessor jtbl's entry count is
 *    still short of the function's `sltiu` limit. This is a §84-class blind spot: `match_one` is
 *    structurally incapable of seeing it, and the symptom would surface as a whole-binary DIFF.
 */
#include "common.h"

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
extern M2C_UNK D_80186E48;

void func_8012ACA0(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_80186E48;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s16 *, 0x9A) = 0;
    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
    ((void (*)(void))func_8012AAAC)();
}
