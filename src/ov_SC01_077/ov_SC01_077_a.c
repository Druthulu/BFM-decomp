#include "common.h"
#include "../shared/engine_core.h"

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

DEFINE_func_80128158()  /* dedup: shared engine-core @0x80128158 (src/shared) */

DEFINE_func_80128178()  /* dedup: shared engine-core @0x80128178 (src/shared) */

DEFINE_func_80128198()  /* dedup: shared engine-core @0x80128198 (src/shared) */

DEFINE_func_801281B8()  /* dedup: shared engine-core @0x801281B8 (src/shared) */

DEFINE_func_801281D8()  /* dedup: shared engine-core @0x801281D8 (src/shared) */

DEFINE_func_801281F8()  /* dedup: shared engine-core @0x801281F8 (src/shared) */

extern s32 D_801D7F90;

s32 func_80128218(void) {
    return D_801D7F90;
}

DEFINE_func_80128228()  /* dedup: shared engine-core @0x80128228 (src/shared) */

DEFINE_func_80128248()  /* dedup: shared engine-core @0x80128248 (src/shared) */

DEFINE_func_80128268()  /* dedup: shared engine-core @0x80128268 (src/shared) */

extern u16 D_800B99F6;
extern void (*D_80186DB4[])(void);

void func_80128288(void) {
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_80186DB4[v1]();
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
DEFINE_func_80128678()  /* dedup: shared engine-core @0x80128678 (src/shared) */

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


DEFINE_func_80128C14()  /* dedup: shared engine-core @0x80128C14 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80128C98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80128CFC);

DEFINE_func_80128D60()  /* dedup: shared engine-core @0x80128D60 (src/shared) */

// @class: struct
// @stuck: none — MATCH
DEFINE_func_80128DB4()  /* dedup: shared engine-core @0x80128DB4 (src/shared) */


DEFINE_func_80128EA8()  /* dedup: shared engine-core @0x80128EA8 (src/shared) */

// LOAD-BEARING register pins (cookbook §17 + §25): the residual here was NOT scheduling but
// gcc-2.7.2 COPY-COALESCING — gcc folded the index-preserve copy (idc) into the multiply operand
// (`sll $v0,$a3,3` on the copy) instead of multiplying $v1 directly. Pinning idc to its target
// reg ($a3) forces the multiply onto $v1 and emits the copy separately AFTER it; routing idc+1
// through the dead $v0-pinned `cnt` lands it in $v0 (target's scratch), not back in $a3.
// Do NOT "simplify" the pins or the cnt reuse — each is byte-load-bearing (byte-gated).
#include "common.h"

s32 func_80128ED8(s32 param_1, s32 *param_2) {
    register s32 iVar4 __asm__("$8");   /* base ptr, lives whole fn in $t0 */
    register s32 cnt   __asm__("$2");   /* decremented count in $v0 */
    register s32 cc    __asm__("$3");   /* preserved count copy in $v1 (forces the bne-delay-slot copy) */
    register s32 idx   __asm__("$3");   /* offset-4 index, loaded into $v1 */
    register s32 idc   __asm__("$7");   /* $a3: preserved idx copy, forced SEPARATE from the multiply */
    u32 uVar3;
    s32 frame_pad[4];                   /* phantom 0x10 frame the target reserves (induce via clobber anchor) */

    __asm__ __volatile__("" : : "r"(&frame_pad) : "memory");
    iVar4 = *param_2;
    cnt = *(s16 *)((s32)param_2 + 6);
    if (cnt == 0) {
        return 1;
    }
    cc = cnt;
    __asm__ __volatile__("" : "=r"(cc) : "0"(cc));   /* force the count-preserve copy ($v1=$v0) */
    cnt = cc - 1;
    *(s16 *)((s32)param_2 + 6) = (s16)cnt;
    if (cnt * 0x10000 < 1) {
        idx = *(s16 *)((s32)param_2 + 4);
        __asm__ __volatile__("" : "=r"(idx) : "0"(idx));   /* pin the index into $v1 */
        uVar3 = *(u32 *)(idx * 8 + iVar4 + 4);
        idc = idx;
        if ((uVar3 & 0xc0) == 0xc0) {
            *(s16 *)((s32)param_2 + 6) = 0;
            return 1;
        }
        if ((uVar3 & 0x80) != 0) {
            *(s16 *)((s32)param_2 + 4) = 0;
        } else {
            cnt = idc + 1;                       /* reuse the dead $v0 pin so idc+1 lands in $v0, not $a3 */
            *(s16 *)((s32)param_2 + 4) = cnt;
        }
        *(u16 *)((s32)param_2 + 6) =
            (u16)(*(u32 *)((s16)param_2[1] * 8 + iVar4 + 4) & 0x3f);
        *(u16 *)(param_1 + 0x28) = *(u16 *)((s16)param_2[1] * 8 + iVar4);
        *(u16 *)(param_1 + 0x2a) = *(u16 *)((s16)param_2[1] * 8 + iVar4 + 2);
    }
    return 0;
}


M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D7F94;

void func_80128FAC(u16 *arg0) {
    func_8001534C(4, &D_801D7F94, 0x80, 0x90, 0, 0);
    func_800153CC(5, *arg0, 0xA8, 0x90, 0x40, 0);
}


DEFINE_func_80129010()  /* dedup: shared engine-core @0x80129010 (src/shared) */

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
DEFINE_func_8012913C()  /* dedup: shared engine-core @0x8012913C (src/shared) */


DEFINE_func_801291C0()  /* dedup: shared engine-core @0x801291C0 (src/shared) */

extern void func_80129258(void);
extern void func_80129248(s16 a0);

void func_80129220(void) {
    func_80129258();
    func_80129248(1);
}

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

// @class: schedule
// @stuck: none — MATCH (72 ins)

DEFINE_func_8012944C()  /* dedup: shared engine-core @0x8012944C (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012956C);


DEFINE_func_801298F4()  /* dedup: shared engine-core @0x801298F4 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801299C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80129C40);

DEFINE_func_80129CF8()  /* dedup: shared engine-core @0x80129CF8 (src/shared) */

DEFINE_func_80129FF4()  /* dedup: shared engine-core @0x80129FF4 (src/shared) */

extern u8 D_80126948[];
void func_8012A048(void *a0, s32 a1, u8 a2);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012A1BC);

DEFINE_func_8012A2F4()  /* dedup: shared engine-core @0x8012A2F4 (src/shared) */

DEFINE_func_8012A304()  /* dedup: shared engine-core @0x8012A304 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012A328);


struct Q16 { s32 a, b, c, d; };

extern s32 D_801151D4;
extern struct BigCopy D_80114EE8;

void func_8012A418(void) {
    struct Q16 *src;
    struct Q16 *dst;
    struct Q16 *end;

    src = (struct Q16 *)D_801151D4;
    dst = &D_80114EE8;
    end = src + 10;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    *(s32 *)dst = *(s32 *)src;
}


typedef struct { s32 w[8]; } Vec8;

extern s32 D_801151D4;
extern Vec8 D_80114F24;

void func_8012A464(void)
{
    D_80114F24 = *(Vec8 *)(*(s32 *)&D_801151D4 + 0x3C);
}

DEFINE_func_8012A4BC()  /* dedup: shared engine-core @0x8012A4BC (src/shared) */

DEFINE_func_8012A568()  /* dedup: shared engine-core @0x8012A568 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012A598);

DEFINE_func_8012A5F8()  /* dedup: shared engine-core @0x8012A5F8 (src/shared) */





DEFINE_func_8012A62C()  /* dedup: shared engine-core @0x8012A62C (src/shared) */


DEFINE_func_8012A68C()  /* dedup: shared engine-core @0x8012A68C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012A6D0);

DEFINE_func_8012A758()  /* dedup: shared engine-core @0x8012A758 (src/shared) */

DEFINE_func_8012A79C()  /* dedup: shared engine-core @0x8012A79C (src/shared) */

DEFINE_func_8012A7D4()  /* dedup: shared engine-core @0x8012A7D4 (src/shared) */


DEFINE_func_8012A828()  /* dedup: shared engine-core @0x8012A828 (src/shared) */

DEFINE_func_8012A860()  /* dedup: shared engine-core @0x8012A860 (src/shared) */

DEFINE_func_8012A8B0()  /* dedup: shared engine-core @0x8012A8B0 (src/shared) */

DEFINE_func_8012A8E8()  /* dedup: shared engine-core @0x8012A8E8 (src/shared) */

DEFINE_func_8012A908()  /* dedup: shared engine-core @0x8012A908 (src/shared) */

DEFINE_func_8012A988()  /* dedup: shared engine-core @0x8012A988 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012AAAC);

extern void func_8012AAAC(void);
extern M2C_UNK D_80186E48;

void func_8012ACA0(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_80186E48;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s16 *, 0x9A) = 0;
    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
    func_8012AAAC();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012ACE0);

DEFINE_func_8012AD44()  /* dedup: shared engine-core @0x8012AD44 (src/shared) */

DEFINE_func_8012AD50()  /* dedup: shared engine-core @0x8012AD50 (src/shared) */


void func_8012AD64(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x34) = a1;
}

DEFINE_func_8012AD6C()  /* dedup: shared engine-core @0x8012AD6C (src/shared) */

DEFINE_func_8012AD80()  /* dedup: shared engine-core @0x8012AD80 (src/shared) */

DEFINE_func_8012ADE4()  /* dedup: shared engine-core @0x8012ADE4 (src/shared) */

DEFINE_func_8012AE00()  /* dedup: shared engine-core @0x8012AE00 (src/shared) */

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_800132BC(s32 a0, s32 a1);

/* LOAD-BEARING: the 8-byte sp+0x18->sp+0x20 copy is an alignment-2 struct copy
   (3 shorts written, then copied) -> gcc emits lwl/lwr/swl/swr.  An aligned-2
   base-type typedef did NOT reproduce it; only a short-only struct (align 2) does. */

DEFINE_func_8012AF0C()  /* dedup: shared engine-core @0x8012AF0C (src/shared) */

DEFINE_func_8012B030()  /* dedup: shared engine-core @0x8012B030 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (38 ins, relocation-masked)

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012B4B8);

DEFINE_func_8012B608()  /* dedup: shared engine-core @0x8012B608 (src/shared) */

DEFINE_func_8012B6D4()  /* dedup: shared engine-core @0x8012B6D4 (src/shared) */

DEFINE_func_8012B70C()  /* dedup: shared engine-core @0x8012B70C (src/shared) */

DEFINE_func_8012B744()  /* dedup: shared engine-core @0x8012B744 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012B77C);

DEFINE_func_8012B864()  /* dedup: shared engine-core @0x8012B864 (src/shared) */

DEFINE_func_8012B8A4()  /* dedup: shared engine-core @0x8012B8A4 (src/shared) */

DEFINE_func_8012B8E4()  /* dedup: shared engine-core @0x8012B8E4 (src/shared) */



/* canonical data externs (per pre-resolved sigs); asm loads them lh -> (s16) cast at use */
extern u16 D_80126B66;
extern u16 D_80126B5E;
/* callee func_8004CFEC, linked as symbol "ratan2" (config/symbols.us.txt: 0x8004CFEC);
 * canonical s32(s32,s32) -- matches the banked sibling func_8012B8E4 in engine_core.h */
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

/* func_8012BF68: lhu 0x5C; andi 0x7FFF; sh 0x5C; jr (sh in delay slot)
 * void form: no return value => no extra andi v0,0xffff truncation past the mask. */
DEFINE_func_8012BF68()  /* dedup: shared engine-core @0x8012BF68 (src/shared) */

DEFINE_func_8012BF7C()  /* dedup: shared engine-core @0x8012BF7C (src/shared) */

// @class: schedule
// @stuck: none — MATCH (39/39 reloc-masked words byte-verified via objdump -s raw .text; match_one's "18 mismatched" is the objdump zero-run-elision artifact dropping the 2 cop2-latency nops, same as sibling DEFINE_func_8013E2C4 @ ov_SC01_077.c:326)
#include "common.h"

DEFINE_func_8012BFA8()  /* dedup: shared engine-core @0x8012BFA8 (src/shared) */


DEFINE_func_8012C044()  /* dedup: shared engine-core @0x8012C044 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected; tail-call passes incoming param through (nop delay slot)

extern void func_8012C218(void *a0);

void func_8012C098(void *param_1)
{
    int iVar1;

    iVar1 = *(int *)((char *)param_1 + 0x68);
    if ((iVar1 != 0) && ((*(short *)((char *)param_1 + 0x72) & 0x8000) != 0)) {
        *(unsigned short *)(iVar1 + 10) = *(unsigned short *)(iVar1 + 10) & 0x7fff;
    }
    func_8012C218(param_1);
    return;
}


// @class: other
// @stuck: none — MATCH (42 ins, relocation-masked); func_8012C044 dispatch idiom, if(fp==0) branch-polarity
extern s32 D_801274D4;
extern s16 D_80126CAC;
extern s32 D_801274E0;
extern s32 func_80013478(s32 a0, s32 a1);
extern void func_8012C218(void *a0);

s32 func_8012C0EC(s32 a0) {
    s32 (*fp)(s32) = (s32 (*)(s32))D_801274D4;
    s32 cond;
    s32 *p;

    if (fp == 0) {
        cond = (func_80013478(a0 + 4, (s32)&D_80126CAC) < D_801274E0) ^ 1;
    } else {
        cond = fp(a0);
    }
    if (cond == 0) {
        return 0;
    }
    p = *(s32 **)(a0 + 0x68);
    if (p != 0) {
        if ((*(s16 *)(a0 + 0x72) & 0x8000) != 0) {
            *(u16 *)((s32)p + 0xA) = *(u16 *)((s32)p + 0xA) & 0x7FFF;
        }
    }
    func_8012C218((void *)a0);
    return 1;
}


DEFINE_func_8012C194()  /* dedup: shared engine-core @0x8012C194 (src/shared) */

DEFINE_func_8012C1B8()  /* dedup: shared engine-core @0x8012C1B8 (src/shared) */

DEFINE_func_8012C1DC()  /* dedup: shared engine-core @0x8012C1DC (src/shared) */

DEFINE_func_8012C218()  /* dedup: shared engine-core @0x8012C218 (src/shared) */

DEFINE_func_8012C284()  /* dedup: shared engine-core @0x8012C284 (src/shared) */

// @class: schedule
// @stuck: none — MATCH expected (lifted byte-proven loop idiom from sibling func_8012C750 @0x8012C750)
#include "common.h"

DEFINE_func_8012C2D0()  /* dedup: shared engine-core @0x8012C2D0 (src/shared) */


DEFINE_func_8012C31C()  /* dedup: shared engine-core @0x8012C31C (src/shared) */

DEFINE_func_8012C354()  /* dedup: shared engine-core @0x8012C354 (src/shared) */

DEFINE_func_8012C438()  /* dedup: shared engine-core @0x8012C438 (src/shared) */

DEFINE_func_8012C51C()  /* dedup: shared engine-core @0x8012C51C (src/shared) */


DEFINE_func_8012C588()  /* dedup: shared engine-core @0x8012C588 (src/shared) */



extern u8 D_80126720[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);

struct S8012C658 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
};

s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2) {
    struct S8012C658 sp;
    s32 var_v0;
    u16 *var_a1;
    u16 *end;
    u16 *param;

    if ((arg2 != 0) && (*(u16 *)(arg2 + 0x0) != 0)) {
        sp.unk0 = *(u16 *)(arg2 + 0x6);
        sp.unk2 = *(u16 *)(arg2 + 0xA);
        sp.unk4 = *(u16 *)(arg2 + 0xE);
    } else {
        sp.unk4 = 0;
        sp.unk2 = 0;
        sp.unk0 = 0;
    }
    sp.unk6 = (s16)arg0;
    sp.unk8 = (s16)arg1;
    sp.unkA = 0;
    sp.unk10 = 0;
    sp.unkE = 0;
    sp.unkC = 0x7FFF;
    param = &sp.unk0;
    end = (u16 *)D_80126720;
    if (arg2 == 0) {
        var_a1 = (u16 *)((u8 *)end - 0x6480);
    } else {
        var_a1 = (u16 *)(arg2 + 0x10C);
    }
    while (var_a1 != end) {
        if (*var_a1 == 0) {
            goto found;
        }
        var_a1 = (u16 *)((u8 *)var_a1 + 0x10C);
    }
    var_a1 = 0;
found:
    var_v0 = 0;
    if (var_a1 != 0) {
        var_v0 = ((s32 (*)(u16 *, u16 *))func_8012C890)(param, var_a1);
    }
    return var_v0;
}


DEFINE_func_8012C724()  /* dedup: shared engine-core @0x8012C724 (src/shared) */

// @class: iv-combine
// @stuck: none — MATCH (52 ins)
#include "common.h"

extern u8 D_80120194[];
extern u8 D_801202A0[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);

s32 func_8012C750(s32 a0)
{
    s32 p;
    s32 it;
    s32 v0;

    if (*(u16 *)(a0 + 0xA) & 0x800) {
        s32 base = (s32)D_80120194;
        p = base + 0x6480;
        if (p != base) {
            do {
                if (*(u16 *)p == 0) goto found;
                p -= 0x10C;
            } while (p != base);
        }
        p = 0;
        goto found;
    } else {
        it = (s32)D_80120194;
        __asm__ __volatile__("" : "=r"(it) : "0"(it));
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        __asm__ __volatile__("" : "=r"(it) : "0"(it));
        if (it == p) goto zero;
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
    zero:
        p = 0;
    }
found:
    if (p == 0) {
        v0 = 0;
    } else {
        *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) | 0x8000;
        v0 = func_8012C890(a0, p, 0);
    }
    return v0;
}


DEFINE_func_8012C820()  /* dedup: shared engine-core @0x8012C820 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (149 ins). Counter (*(u16 *)&D_801270C4): gcc CSE's the two reads (store to
//   dst+0x36 assumed non-aliasing the global) AND folds %lo per-access — target instead RELOADS
//   and keeps &(*(u16 *)&D_801270C4) in one reg. Fix = pin a `u16*` to $v1 (register asm "$3"), read via
//   `*(volatile u16*)pc` (defeats CSE -> 2 loads) but STORE via plain `*pc` (non-volatile store
//   schedules store-before-sll, no extra `move`). count is s16 so `count==0` -> `sll 16;bnez`.
//   else-block obj must be a BLOCK-LOCAL (gcc then picks $a1, not the shared if-branch $a0).

extern s32   D_8018A32C;
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
    *(s32 *)(dst + 0x78) = (s32)&D_8018A32C;
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


extern void func_8012CC88(s32 a, s32 b, s32 c);
extern u8 D_800D3918[];

void func_8012CBA4(s32 a0) {
    func_8012CC88(a0, 0, (s32)D_800D3918);
}

extern void func_8012CC88(s32 a, s32 b, s32 c);
extern u8 D_800D3918[];

void func_8012CBCC(s32 a0) {
    func_8012CC88(a0, 1, (s32)D_800D3918);
}

DEFINE_func_8012CBF4()  /* dedup: shared engine-core @0x8012CBF4 (src/shared) */

DEFINE_func_8012CC1C()  /* dedup: shared engine-core @0x8012CC1C (src/shared) */

DEFINE_func_8012CC40()  /* dedup: shared engine-core @0x8012CC40 (src/shared) */

DEFINE_func_8012CC64()  /* dedup: shared engine-core @0x8012CC64 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012CC88);

DEFINE_func_8012CE2C()  /* dedup: shared engine-core @0x8012CE2C (src/shared) */

DEFINE_func_8012CEB0()  /* dedup: shared engine-core @0x8012CEB0 (src/shared) */



DEFINE_func_8012CFA8()  /* dedup: shared engine-core @0x8012CFA8 (src/shared) */


/* func_8012D098 — region-a camera 8-corner/frustum builder (189 ins, reach-134).
 * STATUS: MATCH (match_one = 0, relocation-masked byte-identical). ONE-SHOT — the natural
 * Ghidra-faithful C matched with no pins, no zero-byte asm, no permuter, no Fable5 escalation.
 *
 * Why the "hardest tier / all 8 $s0-$s7 live" label did NOT translate to matching difficulty:
 *  - The two callee-saved BASES are the PARAMETERS themselves (param_1->$fp, param_2->$s7), not
 *    hoisted global arrays. §32 idiom #1's whole crux ("a base living in a $s reg across calls can
 *    only come from a source local, never a bare global") is a non-issue: params are already source
 *    locals in registers. No `p = D_xxxx;` hoist, no pins.
 *  - The body is ONE straight-line basic block (calls don't split BBs in gcc-2.7.2), so the 8 output-
 *    buffer address-pseudos are LOCAL-ALLOC territory; param_1/param_2 span BBs -> global-alloc.
 *  - Peak pressure = 10 callee-saved-worthy values (param_1, param_2, &scratch, bufA..bufG) over 9
 *    regs ($fp + $s0-$s7) -> exactly one buffer must rematerialize. local-alloc density-order (all
 *    buffers = 4 refs, equal) + first-fit naturally spills bufA (first-born, longest live range) and
 *    lays the rest out bufB->$s6 .. bufG->$s1, with &scratch->$s0 (dies at call 8) reused for bufH.
 *    That IS the target allocation, produced with zero steering.
 *
 * Loose/intended types (element type from opcode): param_1 = u16* (`*param_1` is `lhu`, unsigned;
 * an s16* would emit `lh` = 1-op miss); param_2 = u32 pointer-base (offsets 4/6/8/a/c/e emit as
 * literal immediates == target's `%lo(D_80000004..)` bytes; `| 0x80000000` -> `lui 0x8000` ==
 * target's `%hi(D_80000004)`); scratch = u16[3] (`sh` stores, `lhu` sources); the 8 output buffers
 * are 8-byte locals never dereferenced here (size only matters) declared bufA..bufH THEN scratch so
 * the ascending in-decl-order slot layout lands bufA@sp+0x10 .. bufH@sp+0x48, scratch@sp+0x50.
 * Callees kept loose (extern void func_...()); reconcile at bank time via cast_call_sites/§33.
 */
DEFINE_func_8012D098()  /* dedup: shared engine-core @0x8012D098 (src/shared) */


DEFINE_func_8012D38C()  /* dedup: shared engine-core @0x8012D38C (src/shared) */

DEFINE_func_8012D3AC()  /* dedup: shared engine-core @0x8012D3AC (src/shared) */

DEFINE_func_8012D3B4()  /* dedup: shared engine-core @0x8012D3B4 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (sibling of func_8012D3B4 + func_8012DEB8 sp10/sp18 prelude)
#include "common.h"

DEFINE_func_8012D4B4()  /* dedup: shared engine-core @0x8012D4B4 (src/shared) */


DEFINE_func_8012D5DC()  /* dedup: shared engine-core @0x8012D5DC (src/shared) */

DEFINE_func_8012D5E4()  /* dedup: shared engine-core @0x8012D5E4 (src/shared) */

DEFINE_func_8012D624()  /* dedup: shared engine-core @0x8012D624 (src/shared) */

// @class: schedule
// @stuck: none — MATCH


struct S8012D664_8012D664 { short a, b, c; };

int func_8012D664(int arg0, int arg1, int arg2) {
    extern int func_8012F568();
    extern int D_80186E58;

    struct S8012D664_8012D664 s;
    int ret;
    int t;

    s.a = (*(unsigned short*)&D_80126B5E);
    s.b = (*(unsigned short*)&D_80126B62) - 0x40;
    s.c = (*(unsigned short*)&D_80126B66);
    ret = ((int(*)())func_800132BC)(arg0, &s);
    t = arg1 + 0x20;
    if (ret < t * t) {
        func_8012F568(1, 1, 0, arg2, arg0, &D_80186E58);
        return 1;
    }
    return 0;
}


// @class: struct
// @stuck: none — MATCH expected; base = (*(u32*)(p+0x58) & 0xFFFFFFF) | 0x80000000 held once, %lo folds via offsets
#include "common.h"

DEFINE_func_8012D714()  /* dedup: shared engine-core @0x8012D714 (src/shared) */


extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);
extern M2C_UNK D_80186E60;
extern M2C_UNK D_80186E68;

s32 func_8012DB84(void)
{
    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, &D_80186E60, &D_80186E68);
}


// @class: regalloc-order
// @stuck: none — MATCH. Pins: args $s2/$s4/$s5/$s3, loop-actor $s0, running-max/square $s1; abs load-temp pinned $v0 ($2) so abs copies $v0->$v1; re-tie barrier on iVar4 kills slt-into-bgez-delay duplication; nested ifs keep the two 0x5c bit-tests from folding to one andi 0xc000.
#include "common.h"

DEFINE_func_8012DBD0()  /* dedup: shared engine-core @0x8012DBD0 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH


typedef struct Entry_8012DDA4 {
    u16 active;
    unsigned char pad[0x10C - 2];
} Entry_8012DDA4;


s32 func_8012DDA4()
{
    extern Entry_8012DDA4 * D_801D94A4;
    extern Entry_8012DDA4 * D_801D94A0;

    Entry_8012DDA4 *p;
    Entry_8012DDA4 *end = ((Entry_8012DDA4 *)D_80126720);

    while (D_801D94A4 != end) {
        p = D_801D94A4;
        if (p->active != 0 && p != D_801D94A0) {
            D_801D94A4 = p + 1;
            return p;
        }
        D_801D94A4++;
    }
    D_801D94A4 = 0;
    return 0;
}


// @class: plumbing
// @stuck: none — MATCH (35/35 ins, relocation-masked)


s32 func_8012DE2C(s32 a0) {
    extern u8 * D_801D94A4;
    extern u8 * D_801D94A0;

    u8 *base;
    u8 *end;
    u8 *p;

    base = D_801202A0;
    end = base + 0x6480;
    D_801D94A4 = base;
    D_801D94A0 = ((u8 *)a0);

    while (D_801D94A4 != end) {
        p = D_801D94A4;
        if (*(u16 *)p != 0 && p != ((u8 *)a0)) {
            D_801D94A4 = p + 0x10C;
            return p;
        }
        D_801D94A4 += 0x10C;
    }
    D_801D94A4 = 0;
    return 0;
}


DEFINE_func_8012DEB8()  /* dedup: shared engine-core @0x8012DEB8 (src/shared) */

DEFINE_func_8012DF34()  /* dedup: shared engine-core @0x8012DF34 (src/shared) */

DEFINE_func_8012DFBC()  /* dedup: shared engine-core @0x8012DFBC (src/shared) */

DEFINE_func_8012DFCC()  /* dedup: shared engine-core @0x8012DFCC (src/shared) */

DEFINE_func_8012DFD4()  /* dedup: shared engine-core @0x8012DFD4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012E014);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012E138);

s32 func_8012E27C(void) {
    return 1;
}

DEFINE_func_8012E284()  /* dedup: shared engine-core @0x8012E284 (src/shared) */

// @class: struct
// @stuck: none — MATCH (modeled on DEFINE_func_8012D3B4 sibling idiom: (s8*)&D_800A651C + (u16)D_800B9A02*0x14)

DEFINE_func_8012E28C()  /* dedup: shared engine-core @0x8012E28C (src/shared) */


DEFINE_func_8012E32C()  /* dedup: shared engine-core @0x8012E32C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012E364);

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


// @class: regalloc-order
// @stuck: none — MATCH (60/60). Pins: $4 defeats &D_800AF648 CSE; $16/$17 force param_2/param_3 saved-reg order vs the guard-branch reversal
#include "common.h"

DEFINE_func_8012E688()  /* dedup: shared engine-core @0x8012E688 (src/shared) */


// @class: other
// @stuck: none — MATCH (69/69 ins, relocation-masked 0 diffs via tools/match_one precise check)
#include "common.h"

/* GTE inline-asm sequences (psyq inline_c.h bodies). rtps uses the project's
 * `rtps` assembler macro (include/gte_macros.inc, pulled in by common.h ->
 * include_asm.h -> labels.inc) which encodes 0x4A180001 — NOT the psyq
 * `.word 0x0000007f`, which assembles to the wrong word for this target. */
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

extern u8 D_800AF648;

s32 func_8012E778(int param_1, int param_2)
{
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


DEFINE_func_8012E88C()  /* dedup: shared engine-core @0x8012E88C (src/shared) */

DEFINE_func_8012E8A8()  /* dedup: shared engine-core @0x8012E8A8 (src/shared) */

DEFINE_func_8012E8C4()  /* dedup: shared engine-core @0x8012E8C4 (src/shared) */

DEFINE_func_8012E8E0()  /* dedup: shared engine-core @0x8012E8E0 (src/shared) */


// @class: other
// @stuck: none — MATCH (branch-polarity invert: `0x78 != 0` puts compute block as fall-through)

extern void func_8016AA50(int, int);
extern void func_8016B428(int);
extern void func_80019064(void *);
extern int D_80186E70;

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
            func_80019064(&D_80186E70);
        }
    }
    return;
}


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


/* func_8012EC04 — region-a giant (T7).
 * Body = sibling func_8012EA90 (proven MATCH, 3-branch select) verbatim;
 * tail = GTE MulRotMatrix(in place)/SetTrans/ldlv0-rt-stlvnl lifted from
 * DEFINE_func_80132784 (engine_core.h), base ptrs remapped:
 *   rot/trans src M = *(param_1+0x20)+0x34 ;  vector matrix = param_3 (in place). */

DEFINE_func_8012EC04()  /* dedup: shared engine-core @0x8012EC04 (src/shared) */


DEFINE_func_8012EECC()  /* dedup: shared engine-core @0x8012EECC (src/shared) */

DEFINE_func_8012EF34()  /* dedup: shared engine-core @0x8012EF34 (src/shared) */

DEFINE_func_8012EF70()  /* dedup: shared engine-core @0x8012EF70 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012EFB8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012F274);

DEFINE_func_8012F2E8()  /* dedup: shared engine-core @0x8012F2E8 (src/shared) */

DEFINE_func_8012F374()  /* dedup: shared engine-core @0x8012F374 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012F40C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012F49C);

// @class: schedule
// @stuck: none — MATCH (35 ins). Two unaligned 8-byte memcpy to globals then sh a1/a2/a3 + lhu/or/sh RMW on D_80126B94. KEY: an `__asm__ __volatile__("":::"memory")` barrier between the 2nd memcpy and the halfword section pins the D_80126B94 RMW *read* AFTER both memcpys (without it gcc hoists the lhu between the two memcpy blocks; volatile globals over-anchors it to the END).

DEFINE_func_8012F568()  /* dedup: shared engine-core @0x8012F568 (src/shared) */


DEFINE_func_8012F5F4()  /* dedup: shared engine-core @0x8012F5F4 (src/shared) */



struct S80131E00;
DEFINE_func_8012F68C()  /* dedup: shared engine-core @0x8012F68C (src/shared) */


extern void func_80131B14(void);
extern void func_80131CA8(int a0, int a1);

void func_8012F75C(s32 a0) {
    *(u8 *)(a0 + 0xC1) = 3;
    if (*(s32 *)(a0 + 0xB4) & 0x4) {
        func_80131B14();
        *(s32 *)(a0 + 0x1C) = 0x10;
        *(s16 *)(a0 + 0x98) = 0;
    }
    func_80131CA8(a0, 6);
}

DEFINE_func_8012F7B4()  /* dedup: shared engine-core @0x8012F7B4 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (pending gate)
extern void func_80131170();
extern void func_80131CA8();
extern unsigned char D_80186E8C[];

void func_8012F828(int param_1)
{
    *(unsigned char *)(param_1 + 0xC1) = 4;
    if (*(unsigned int *)(param_1 + 0xB4) & 8) {
        func_80131170(param_1, D_80186E8C, 0xB);
    }
    func_80131CA8(param_1, 9);
}


DEFINE_func_8012F87C()  /* dedup: shared engine-core @0x8012F87C (src/shared) */

extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern void func_80131CA8(int a0, int a1);
extern u8 D_80186E98[];

void func_8012F8C8(u8* arg0) {
    *(u8*)(arg0 + 0xC1) = 7;
    if (*(u32*)(arg0 + 0xB4) & 0x80) {
        ((void (*)(void*, void*, s32))func_80131170)(arg0, D_80186E98, 0xB);
    }
    ((void (*)(void*, s32))func_80131CA8)(arg0, 0x16);
}


DEFINE_func_8012F91C()  /* dedup: shared engine-core @0x8012F91C (src/shared) */

// @class: struct
// @stuck: none — MATCH (123 ins). Keys: 3 stack out-params as ONE struct (kept all live + word-load),
//         branch-polarity inverts on the two if/else, and the 0x98=0 store moved AFTER the 3rd division.
#include "common.h"

DEFINE_func_8012F968()  /* dedup: shared engine-core @0x8012F968 (src/shared) */


DEFINE_func_8012FB54()  /* dedup: shared engine-core @0x8012FB54 (src/shared) */

DEFINE_func_8012FC30()  /* dedup: shared engine-core @0x8012FC30 (src/shared) */

DEFINE_func_8012FCA4()  /* dedup: shared engine-core @0x8012FCA4 (src/shared) */

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
extern int  D_80186EA4;

void func_8012FCC4(int param_1) {
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
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_80186EA4);
        *(int *)(param_1 + 0x1C) = 0;
        func_80131CA8(param_1, 0x1C);
        return;
    }
    func_80131CA8(param_1, 0x1C);
}

// @class: other
// @stuck: clean control-flow fn; expecting MATCH from direct structural reconstruction

extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8012CBF4(s32 a0);
void func_801319E0(int);
void func_80131C78(int);
void func_80131CA8(int, int);

DEFINE_func_8012FDA8()  /* dedup: shared engine-core @0x8012FDA8 (src/shared) */


struct S80131E00;
DEFINE_func_8012FE70()  /* dedup: shared engine-core @0x8012FE70 (src/shared) */

DEFINE_func_8012FF00()  /* dedup: shared engine-core @0x8012FF00 (src/shared) */

DEFINE_func_8012FF4C()  /* dedup: shared engine-core @0x8012FF4C (src/shared) */

DEFINE_func_8012FF98()  /* dedup: shared engine-core @0x8012FF98 (src/shared) */

DEFINE_func_8013001C()  /* dedup: shared engine-core @0x8013001C (src/shared) */

DEFINE_func_80130088()  /* dedup: shared engine-core @0x80130088 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (61 ins); shared-tail done=1 at the post-if/else merge point fills the shared jal's delay slot
#include "common.h"

DEFINE_func_801300F4()  /* dedup: shared engine-core @0x801300F4 (src/shared) */


DEFINE_func_801301E8()  /* dedup: shared engine-core @0x801301E8 (src/shared) */



struct S80131E00;

DEFINE_func_80130278()  /* dedup: shared engine-core @0x80130278 (src/shared) */


DEFINE_func_80130314()  /* dedup: shared engine-core @0x80130314 (src/shared) */

DEFINE_func_80130360()  /* dedup: shared engine-core @0x80130360 (src/shared) */

DEFINE_func_801303A0()  /* dedup: shared engine-core @0x801303A0 (src/shared) */


DEFINE_func_801303EC()  /* dedup: shared engine-core @0x801303EC (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (55 ins, match_one relocation-masked)

DEFINE_func_80130438()  /* dedup: shared engine-core @0x80130438 (src/shared) */


// @class: schedule
// @stuck: none — MATCH
DEFINE_func_80130514()  /* dedup: shared engine-core @0x80130514 (src/shared) */


DEFINE_func_801305CC()  /* dedup: shared engine-core @0x801305CC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80130650);

DEFINE_func_80130740()  /* dedup: shared engine-core @0x80130740 (src/shared) */

DEFINE_func_801307B0()  /* dedup: shared engine-core @0x801307B0 (src/shared) */

DEFINE_func_80130858()  /* dedup: shared engine-core @0x80130858 (src/shared) */

DEFINE_func_80130898()  /* dedup: shared engine-core @0x80130898 (src/shared) */

DEFINE_func_801308DC()  /* dedup: shared engine-core @0x801308DC (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (41 ins, match_one verified; lh@0x18 / lhu@0x1c, andi 0x8000 on uint field)

DEFINE_func_80130974()  /* dedup: shared engine-core @0x80130974 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80130A18);

DEFINE_func_80130AC4()  /* dedup: shared engine-core @0x80130AC4 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (70 ins). Early-returns (not a shared `mode` var) keep $a0 live on the first path; main-block path reloads $a0 from $s0 at the tail, giving the move+nop delay-slot the target uses.

DEFINE_func_80130AF0()  /* dedup: shared engine-core @0x80130AF0 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80130C08);

extern void (*D_80186EAC[])(void);

void func_80130D0C(void *a0) {
    D_80186EAC[*(u8 *)((s32)a0 + 0xC1)]();
}

// @class: regalloc-order
// @stuck: none — MATCH (266/266). Levers: pin pa=$s2 p=$s3, tbl=$s0 (NOT s1v — leave natural so switch-mask lands in $v1); tight-block pins for the table-addr temps `register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2")` force offset=$v1/base=$v0 (else compute-into-dest $s0); inline offset `TABLE + s1v*2` (late) keeps the 2-sll delay-slot dup; 0x60000 reuses `tbl` (not a fresh `e`) so it stays $s0 and materializes after rand().
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_80186EFC[];
extern s16 D_80186F2C[];
extern s16 D_80186F8C[];
extern s16 D_80186F94[];
extern s16 D_80186FB4[];

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
        { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_80186F2C; tbl = (s16 *)(bp + v1); }

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
            tbl = D_80186F8C;
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
            { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_80186F94; tbl = (s16 *)(bp + v1); }
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
            { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_80186FB4; tbl = (s16 *)(bp + v1); }
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
        tbl = D_80186EFC;
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


// @class: loop-guard
// @stuck: none — MATCH (88 ins). Keys: duplicate the c!=0/c==0 bodies verbatim (gcc cross-jumps
//   the shared "|=4;goto tail" into L240 on its own); tail dispatch as `if (((s32(*)(s32))func_8012BCCC)(p) <= 0x8FFF)`
//   (the <= polarity makes the >0x8FFF/0x33-first block the bnez'd else=L298, fall-through = 0x32-first);
//   both AC8 tails cross-jump-merge into the shared L2AC final call. Externs aligned to the file's
//   existing decls for gate-safety: func_80131B14(void) [file line 1486], func_8012B14C/func_8012BCCC
//   canonical (s32) [DEFINE macros], ((s32(*)())func_80131AC8)() no-proto (compatible w/ later 1-arg DEFINE, 2-arg call).


void func_80131170(s32 p, s32 b, s32 c) {
    extern u8 D_80186E80[];

    func_80131B14();
    *(u8 *)(((u8 *)p) + 0xC2) = 0;
    *(u8 *)(((u8 *)p) + 0xC3) = 0;
    *(s16 *)(((u8 *)p) + 0x98) = 0;
    if (((u8 *)b) == 0) {
        ((u8 *)b) = D_80186E80;
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
    extern M8 D_80186FD4;

    int iVar5;

    iVar5 = func_80131CF4(*(int *)(((int)param_1) + 0xBC), 0x2E);
    if (iVar5 != 0) {
        ((short *)param_2)[2] = 0;
        ((short *)param_2)[0] = 0;
        ((short *)param_2)[1] = (short)iVar5;
    } else {
        *(M8 *)((short *)param_2) = D_80186FD4;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131340);


/* Canonical sigs (consistent with src/ov_SC01_077/ov_SC01_077.c + engine_core.h):
 *  - func_80131CA8: canonical 'extern void func_80131CA8(int, int)' (overlay .c L742,
 *    engine_core.h). Its $v0 return IS used here (asm: jal ...; bnez $v0), so cast at the
 *    call site to read it -- the codebase's own idiom (engine_core.h L17026:
 *    ((s32 (*)(int, int))func_80131CA8)(arg0, 0x2C)). Byte-neutral, no sig conflict.
 *  - func_8012C218: canonical 'void func_8012C218(void *a0)' (DEFINE_func_8012C218).
 *  - func_8002A04C: main-EXE callee (src/800.c), undeclared in this TU -> declare locally,
 *    arity 1 (asm: jal func_8002A04C; delay-slot a0=s0). No conflict.
 */
DEFINE_func_801319E0()  /* dedup: shared engine-core @0x801319E0 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131A34);

DEFINE_func_80131AC8()  /* dedup: shared engine-core @0x80131AC8 (src/shared) */

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
    extern u8 D_80186FDC;

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
            ((void(*)(void *))func_80019064)(&D_80186FDC);
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

DEFINE_func_80131C78()  /* dedup: shared engine-core @0x80131C78 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131CA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131CF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131D68);

extern void (*D_80186FEC[])(struct S80131E00 *a0);

void func_80131E00(struct S80131E00 *a0, s32 a1) {
    a0->field_B0 = a1;
    D_80186FEC[a1](a0);
}

DEFINE_func_80131E38()  /* dedup: shared engine-core @0x80131E38 (src/shared) */

struct S80131E00;
DEFINE_func_80131E7C()  /* dedup: shared engine-core @0x80131E7C (src/shared) */

DEFINE_func_80131EE4()  /* dedup: shared engine-core @0x80131EE4 (src/shared) */

extern void (*D_80187044[])(void);

void func_80131EEC(void *a0) {
    D_80187044[*(u16 *)((s32)a0 + 0x2)]();
}

extern void (*D_8018708C[])(void);

void func_80131F28(void *a0) {
    D_8018708C[*(u16 *)((s32)a0 + 0x2)]();
}

extern void (*D_80187094[])(void);

void func_80131F64(s32 *a0) {
    D_80187094[*(u16 *)((s32)a0 + 2)]();
}

extern s32 (*D_8018709C[])();

s32 func_80131FA0(s16 *a0) {
    return D_8018709C[(u16)a0[1]]();
}

extern s32 (*D_801870A4[])();

s32 func_80131FDC(s16 *a0) {
    return D_801870A4[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80132018);

DEFINE_func_801320D0()  /* dedup: shared engine-core @0x801320D0 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int D_8018704C;

void func_801320D8(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018704C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int D_8018705C;

void func_80132144(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018705C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801321B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8013221C);

// @class: regalloc-order
// @stuck: none — MATCH (97 ins, relocation-masked)
DEFINE_func_80132288()  /* dedup: shared engine-core @0x80132288 (src/shared) */


DEFINE_func_8013240C()  /* dedup: shared engine-core @0x8013240C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801325B8);

DEFINE_func_8013277C()  /* dedup: shared engine-core @0x8013277C (src/shared) */


DEFINE_func_80132784()  /* dedup: shared engine-core @0x80132784 (src/shared) */

DEFINE_func_80132DC4()  /* dedup: shared engine-core @0x80132DC4 (src/shared) */

extern void Square0(s32 *a0, s32 *a1);
extern s16 D_80126CAC;
extern s16 D_80126CB0;

s32 func_80132E6C(s16 *a0) {
    s32 in[3];
    s32 out[3];
    in[0] = a0[3] - D_80126CAC;
    in[1] = 0;
    in[2] = a0[7] - D_80126CB0;
    Square0(in, out);
    return out[0] + out[2];
}

DEFINE_func_80132EC4()  /* dedup: shared engine-core @0x80132EC4 (src/shared) */

DEFINE_func_80132EF4()  /* dedup: shared engine-core @0x80132EF4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80132F40);

DEFINE_func_80133060()  /* dedup: shared engine-core @0x80133060 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801330E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80133298);

// @class: schedule
// @stuck: none — MATCH
DEFINE_func_8013339C()  /* dedup: shared engine-core @0x8013339C (src/shared) */


DEFINE_func_8013361C()  /* dedup: shared engine-core @0x8013361C (src/shared) */

// @class: plumbing
// @stuck: none — MATCH

extern s32 D_801D94F0;
extern s32 D_801D94F4[];
extern int D_801D94F8;
extern void func_80136BC4(s32 a0);

void func_801336E8(void *a0, int a1, int a2) {
    if (a0 != 0) {
        (*(void * *)&D_801D94F0) = a0;
        ((void (*)(void))func_80136BC4)();
    }
    (*(int *)&D_801D94F4) = a1;
    D_801D94F8 = a2;
}


extern s32 D_801D94F4[];
extern s32 D_801D94F0;
extern void func_80136BC4(s32);

void func_8013373C(s16 arg0) {
    s32 temp = D_801D94F4[arg0];
    if (temp != 0) {
        D_801D94F0 = temp;
        func_80136BC4(temp);
    }
}


// @class: regalloc-order
#include "common.h"

typedef struct { u16 f0, f2, f4; s16 f6; } Box_80133784;


s32 func_80133784(s32 arg0, void *arg1, s32 arg2) {
    extern s32 func_80047D3C(s32);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern Box_80133784 * D_801870AC;
    extern Box_80133784 * D_801870B0;
    extern s16 D_801D94FC;
    extern u16 D_801D9500;

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
    D_801870AC->f6 = -0x7FFF;
    D_801870B0->f6 = 0x7FFF;
    D_801870AC->f0 = ((Box_80133784 *)arg1)->f0;
    D_801870AC->f4 = ((Box_80133784 *)arg1)->f4;
    D_801870B0->f0 = ((Box_80133784 *)arg2)->f0;
    D_801870B0->f4 = ((Box_80133784 *)arg2)->f4;
    D_801D9500 = 0;
    D_801D94FC = 0;

    if ((s16)a0v == 0) {
        s16 sx = ((Box_80133784 *)arg2)->f0 - ((Box_80133784 *)arg1)->f0;
        s16 sy = ((Box_80133784 *)arg2)->f2 - ((Box_80133784 *)arg1)->f2;
        s16 sz = ((Box_80133784 *)arg2)->f4 - ((Box_80133784 *)arg1)->f4;
        if (sx == 0 && sy == 0) {
            s32 zt = (sz == 0);
            __asm__("addu %0,%1,$zero" : "=r"(s2) : "r"(zt));
        }
        D_801870AC->f2 = ((Box_80133784 *)arg1)->f2 - 4;
        r = func_80047D3C(sx * sx + sz * sz);
        if (r < 3) {
            r = 4;
        } else if (r < 5) {
            r += 1;
        }
        D_801870B0->f2 = ((Box_80133784 *)arg2)->f2 + r + 1;
    } else {
        D_801870AC->f2 = ((Box_80133784 *)arg1)->f2;
        if ((s16)a0v == 2) {
            D_801870B0->f0 = D_801870AC->f0;
            D_801870B0->f2 = D_801870AC->f2 + 6;
            s2 = 1;
            D_801870B0->f4 = D_801870AC->f4;
        } else {
            D_801870B0->f2 = ((Box_80133784 *)arg2)->f2;
        }
    }

    while (1) {
        s32 ret0;
        register s32 retc __asm__("$3");
        __asm__ __volatile__("");
        ret0 = func_80133AB0(arg0s, (s16)D_801870AC->f0, (s16)D_801870AC->f4, (*(s32*)&D_801D94F0));
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

    D_801870B0->f0 = D_801870AC->f0;
    D_801870B0->f2 = D_801870AC->f2;
    s1 = 0x2000;
    D_801870B0->f4 = D_801870AC->f4;
    goto store_out;

after:
    if ((s16)s4 != 0 || D_801D94FC != 0) {
        s16 t;
        __asm__ __volatile__("" :: "r"(s4));
        t = D_801870AC->f6;
        if (t >= -0xBCB) {
            if (t < -0x578) {
                s1 |= 0x4000;
            } else {
                s1 |= 0x8000;
            }
        }
        if ((s16)D_801870B0->f6 < -0xBCB) {
            s1 |= 0x2000;
        }
    store_out:
        ((Box_80133784 *)arg2)->f0 = D_801870B0->f0;
        ((Box_80133784 *)arg2)->f2 = D_801870B0->f2;
        ((Box_80133784 *)arg2)->f4 = D_801870B0->f4;
        ((Box_80133784 *)arg2)->f6 = D_801D9500;
        return s1 & 0xFFFF;
    }
    ((Box_80133784 *)arg2)->f6 = D_801D9500;
    return 0;
}


// @class: regalloc-order/schedule  @status: MATCH (137 ins, real-TU rtu_match byte-identical)
// Cracked from the wave-2 91-off draft. Winning levers (each byte-gated, ~137→0):
//  1. RECONCILE: the TU has TWO conflicting block-scope externs for this fn (s32(s16,s16,s16,s32)
//     @func_80133784 and int(int,s16,s16,int)@func_801343C4); a DEFINITION hard-errors against the
//     mismatched one. Match the first (s16 arg0) + //@EDIT the second to it (byte-neutral for
//     func_801343C4: sangle is already s16-valued in-reg; verified words-identical). arg3 s32→(Map*).
//  2. LOOP FORM (46→20→10): the target is a for-style jump-to-bottom-test with the decrement in the
//     test's delay slot. A plain `while((u16)cnt!=0){cnt--;...}` gets rotated+exit-test-DUPLICATED
//     into a guarded do-while (§ jump.c:duplicate_loop_exit_test). Sibling idiom kills the guard:
//     `while(((cnt-- + zr) & 0xffff) != 0)` — the post-decrement side-effect + `+zr` ($0) forces the
//     `addu v0,s1,$0; andi; ...; addiu s1,-1(delay)` shape and blocks the guard duplication.
//  3. cp REGISTER (10→6): write `&cells[k]` as `k*2 + (u32)cells` (index first, base added LAST) so the
//     running accumulator stays in $v0 (target: `addu v0,v0,v1`), not the cells reg $v1.
//  4. NO pin on pA (6→1): the wave-2 `register u16 *pA __asm__("$7")` pin was UNNEEDED (gcc allocs pA
//     to $a3 naturally) AND poisoned the tail — the dead $7 anti-dep let sched2 hoist `move a3,p0C`
//     out of the jal delay slot. Dropping the pin fixed the whole call-arg schedule. (§42: pins backfire.)
//  5. harg→$4 pin (1→0): `register int harg __asm__("$4")` makes the flag OR in-place `or a0,a0,s7`
//     (harg first) instead of `or a0,s7,a0`; a0 is harg's natural uncontested home (clean pin, §42).
//  hib→a0 copy comes from `harg = hib + zr` (sibling idiom); Xc/Yc live-range splits via the $0-add asm.
#include "common.h"

typedef struct Map_80133AB0 {
    u16 ox;       /* 0x00 */
    u16 oy;       /* 0x02 */
    u16 w;        /* 0x04 */
    u16 h;        /* 0x06 */
    u16 *cells;   /* 0x08 */
    void *p0C;    /* 0x0C */
    void *p10;    /* 0x10 */
    u8  *p14;     /* 0x14 */
    u8  *p18;     /* 0x18 */
    u8  *p1C;     /* 0x1C */
} Map_80133AB0;

s32 func_80133AB0(s16 flag, s16 x, s16 y, s32 arg3)
{
    extern u8 D_801870B0;
    extern u8 D_801870AC;
    extern u8 D_801870B8;
    extern u16 D_801D9500;
    extern s16 D_801D94FC;
    extern s32 func_80133CD4();

    Map_80133AB0 *map = (Map_80133AB0 *)arg3;
    u16 *pA = (*(u16 * *)&D_801870B0);
    u16 *pB = (*(u16 * *)&D_801870AC);
    u16 *pC = (*(u16 * *)&D_801870B8);
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
                D_801D9500 = *(u16 *)s0;
            return 1;
        }
        lst++;
        if (D_801D94FC != 0) {
            D_801D9500 = *(u16 *)s0;
            return 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80133CD4);

typedef struct { s16 x, y, z; } Vec3s;

s32 func_80134310(Vec3s *a0, Vec3s *a1, s32 a2) {
    return a0->x * a1->x + a0->y * a1->y + a0->z * a1->z + a2;
}

DEFINE_func_8013435C()  /* dedup: shared engine-core @0x8013435C (src/shared) */

// @class: schedule
// @stuck: none — MATCH (83 ins, relocation-masked)



s32 func_801343C4(s32 angle, s32 p1, s32 p2)
{
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern s16 * D_801870AC;
    extern s16 * D_801870B0;
    extern u16 D_801D9500;
    extern u16 D_801D94FC;

    s16 *pac;
    s16 *pb0;
    s16 *pacs, *pb0s;
    u16 *pb0u;
    int a1v, a2v, d94, b0;
    int sangle = ((s16)angle);

    pac = D_801870AC;
    d94 = D_801D94F0;
    pb0 = D_801870B0;
    pac[0] = ((u16 *)p1)[0];
    pac[1] = ((u16 *)p1)[1];
    pac[2] = ((u16 *)p1)[2];
    pb0[0] = ((u16 *)p2)[0];
    pb0[1] = ((u16 *)p2)[1];
    pb0[2] = ((u16 *)p2)[2];

    a1v = pac[0]; a2v = pac[2];
    __asm__ __volatile__("" ::: "memory");
    D_801D9500 = 0;
    D_801D94FC = 0;
    if (func_80133AB0(sangle, a1v, a2v, d94)) {
    setdst:
        pb0u = (u16 *)D_801870B0;
        ((u16 *)p2)[0] = pb0u[0];
        ((u16 *)p2)[1] = pb0u[1];
        ((u16 *)p2)[2] = pb0u[2];
        ((u16 *)p2)[3] = D_801D9500;
        return 1;
    }

    pacs = D_801870AC;
    pb0s = D_801870B0;
    b0 = pb0s[0];
    if ((pacs[0] & 0xFF80) == (b0 & 0xFF80) &&
        (pacs[2] & 0xFF80) == (pb0s[2] & 0xFF80)) {
        return 0;
    }
    if (func_80133AB0(sangle, b0, pb0s[2], D_801D94F0)) {
        goto setdst;
    }
    return 0;
}


// @class: schedule
typedef struct {
    u16 f0;   /* 0x0 */
    u16 f2;   /* 0x2 */
    u16 f4;   /* 0x4 */
    s16 f6;   /* 0x6 */
} Foo_80134510;


s32 func_80134510(s32 param) {
    extern s32 func_801345F8(s32);
    extern Foo_80134510 * D_801870AC;
    extern Foo_80134510 * D_801870B0;
    extern Foo_80134510 * D_801870B4;
    extern s32 D_801D94F0;
    extern u16 D_801D9500;

    s32 ret = 0;
    Foo_80134510 *b0 = D_801870B0;
    Foo_80134510 *ac = D_801870AC;
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

    if (func_801345F8(D_801D94F0) != 0) {
        s16 x;
        ((Foo_80134510 *)param)->f2 = D_801870B4->f2 - 2;
        x = D_801870AC->f6;
        if (x >= -3019) {
            if (x < -1400) {
                ret = 0x4000;
            } else {
                ret = 0x8000;
            }
        } else {
            ret = 0x2000;
        }
        D_801870AC->f6 = D_801D9500;
    }
    return ret;
}

// @class: regalloc-order
// @stuck: 26-mismatch near-miss (structure fully matches: while-loop test-first via j-to-bottom-test, s0=puVar7/s1=cnt/s2=scan/s3=iVar8/s4=iVar9/s5=uVar3/s6=uVar10, a1=param/a0=cc/a3=0x8000 pinned, both range-persist copies present, mult+GPU-index+call all byte-correct). Residual = 4 instances of ONE gcc-2.7.2 regalloc/copy-prop tie-break: target computes a preserved-then-masked value in $v0 and reads $v0 for the mask (`subu $v0; addu $persist,$v0; andi $v0,$v0`), gcc here reads the persist reg (`andi $v0,$t0`). (1) range-check-1 andi reads $t0 not $v0; (2) range-check-2 andi reads $a0 not $v0; (3) `hi=uVar1&0x8000` folds into $a0 — target computes in $v0 + copies to $a0 in the branch-delay (same-block copy, gcc coalesces mine); (4) loop-test `cnt&0xffff` folds to direct `andi $v0,$s1` — target copies `addu $v0,$s1` first. Splitting the value into compare-temp + persist-var produces the copy but gcc forward-propagates the copy DEST into the mask; persist-after-compare kills the copy; explicit `register __asm__` pins fold the whole expr chain into the pinned reg; `=r/0` barriers force bad materialization. Also minor: while-loop header-copy adds a `beqz s1` entry guard vs target `j`, and a2/a3 call-arg setup order. Permuter can't run (register __asm__ pins rejected by pycparser). Genuinely compiler-internal — hand-finish or accept as ceiling.


s32 func_801345F8(s32 arg)
{
    extern int func_801347A0(short, u16 *, int, int);
    extern u16 * D_801870AC;
    extern u16 D_801D9500;

    register u16 *param_1 __asm__("$5") = ((u16 *)arg);
    register u16 *cc __asm__("$4") = D_801870AC;
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
        D_801D9500 = *puVar7;
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


// @class: regalloc-order
// @stuck: none — MATCH (162 ins). iv pinned to $4 (a0) forces move+delay-slot negu; divisor-temp forces divisor-first schedule (load-delay nop). Globals declared pointer-typed (SVec*/s16*) so %lo folds per-use instead of &sym address-CSE into callee regs.
#include "common.h"

typedef struct {
    /* 0x00 */ u16 f0;
    /* 0x02 */ s16 f2;
    /* 0x04 */ s16 f4;
    /* 0x06 */ s16 f6;
    /* 0x08 */ s16 f8;
    /* 0x0A */ s16 fa;
    /* 0x0C */ s16 fc;
    /* 0x0E */ s16 fe;
    /* 0x10 */ s16 f10;
    /* 0x12 */ s16 f12;
    /* 0x14 */ s16 f14;
} S0;

typedef struct {
    /* 0x0 */ s16 f0;
    /* 0x2 */ s16 f2;
    /* 0x4 */ s16 f4;
    /* 0x6 */ s16 f6;
} Elem;

typedef struct {
    /* 0x0 */ u16 f0;
    /* 0x2 */ u16 f2;
    /* 0x4 */ u16 f4;
    /* 0x6 */ u16 f6;
} SVec;



s32 func_801347A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_80134A28(s32 a0, s32 a1, s32 a2);
    extern s16 * D_801870B0;
    extern SVec * D_801870AC;
    extern SVec * D_801870B4;

    Elem *pElem;
    s32 val;
    register s32 iv __asm__("$4");
    s32 q;
    s32 dvsr;

    pElem = &((Elem *)arg2)[((S0 *)arg1)->f2];
    val = ((s32 *)arg3)[((S0 *)arg1)->f4];
    if (func_80134A28((s32)pElem, (s32)D_801870B0, val) >= 0) {
        return 0;
    }
    iv = func_80134A28((s32)pElem, (s32)D_801870AC, val);
    if (iv < 0) {
        return 0;
    }
    iv = -iv;
    dvsr = pElem->f2 * 48;
    q = (iv * 48) / dvsr;
    D_801870B4->f0 = D_801870AC->f0;
    D_801870B4->f2 = D_801870AC->f2 + q;
    D_801870B4->f4 = D_801870AC->f4;
    if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->f6], (s32)D_801870B4, ((s32 *)arg3)[((S0 *)arg1)->f8]) < -0x2F00) {
        return 0;
    }
    if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->fa], (s32)D_801870B4, ((s32 *)arg3)[((S0 *)arg1)->fc]) < -0x2F00) {
        return 0;
    }
    if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->fe], (s32)D_801870B4, ((s32 *)arg3)[((S0 *)arg1)->f10]) < -0x2F00) {
        return 0;
    }
    if ((s16)arg0) {
        if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->f12], (s32)D_801870B4, ((s32 *)arg3)[((S0 *)arg1)->f14]) < -0x2F00) {
            return 0;
        }
    }
    if ((((S0 *)arg1)->f0 & 0x300) != 0) {
        return 0;
    }
    D_801870B4->f0 = D_801870AC->f0;
    D_801870B4->f4 = D_801870AC->f4;
    (*(Elem*)D_801152A8) = *pElem;
    D_801870AC->f6 = pElem->f2;
    return 1;
}


DEFINE_func_80134A28()  /* dedup: shared engine-core @0x80134A28 (src/shared) */

int func_80134A74(int param_1, s16 param_2, s16 param_3, int param_4)
{
    extern u16 D_801D9500;
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
        D_801D9500 = *puVar7;
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
    extern s32 func_80134FB8(s32 a0, s32 a1, s32 a2);
    extern void * D_801870AC;
    extern void * D_801870B0;
    extern void * D_801870B4;
    extern void * D_801870B8;
    extern u16 D_801D9500;

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
    if (func_80134FB8(temp_s4, (s32) D_801870B0, temp_s1) >= 0) {
        return var_v0;
    }
    temp_v0 = func_80134FB8(temp_s4, (s32) D_801870AC, temp_s1);
    if (temp_v0 < 0) {
        goto block_13;
    }
    temp_v0_2 = func_80134FB8(temp_s4, (s32) D_801870B8, 0);
    temp_a3 = -temp_v0;
    {
        u16 *pB4 = (u16 *)D_801870B4;
        u16 *pAC = (u16 *)D_801870AC;
        s16 *pB8 = (s16 *)D_801870B8;
        pB4[0] = pAC[0] + (temp_a3 * pB8[0]) / temp_v0_2;
        pB4[1] = pAC[1] + (temp_a3 * pB8[1]) / temp_v0_2;
        pB4[2] = pAC[2] + (temp_a3 * pB8[2]) / temp_v0_2;
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 6) * 8), (s32) pB4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 8) * 4))) < -0x2F00) {
            return var_v0;
        }
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xA) * 8), (s32) D_801870B4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0xC) * 4))) < -0x2F00) {
        return var_v0;
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xE) * 8), (s32) D_801870B4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x10) * 4))) < -0x2F00) {
        return var_v0;
    }
    if ((arg0 << 16) < 0) {
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0x12) * 8), (s32) D_801870B4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x14) * 4))) < -0x2F00) {
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
    D_801D9500 = temp_a1;
block_13:
    return 0;
block_14:
    __builtin_memcpy(D_801152A8, (void *)temp_s4, 8);
    VectorNormalSS(D_801870B8, D_801870B8);
    {
        u16 *pB8 = (u16 *)D_801870B8;
        u16 *pB4b = (u16 *)D_801870B4;
        pB4b[0] = pB4b[0] - ((pB8[0] << 0x10) >> 0x1B);
        var_v0 = 1;
        pB4b[1] = pB4b[1] - ((pB8[1] << 0x10) >> 0x1B);
        pB4b[2] = pB4b[2] - ((pB8[2] << 0x10) >> 0x1B);
    }
    return var_v0;
}


DEFINE_func_80134FB8()  /* dedup: shared engine-core @0x80134FB8 (src/shared) */

// @class: plumbing
// @stuck: MATCH (89 ins). To BANK: retype D_801870B0 + D_801870AC (u8 -> s16*) in sibling func_80135168's externs (src/ov_SC01_077/ov_SC01_077_a.c ~L1879); they hold pointers double-referenced across a call, so only a 4-byte/pointer decl folds %lo (u8 &-cast CSE's the address into a saved reg). Retype is byte-NEUTRAL for the sibling (verified: identical objdump bytes u8 vs s16*).




s32 func_80135004(s32 arg0, s32 p1, s32 p2)
{
    extern int func_80134A74(int, s16, s16, int);
    extern s16 * D_801870B0;
    extern s16 * D_801870AC;
    extern u8 D_801870B8;
    extern s16 *D_801870B4;
    extern u16 D_801D9500;

    register s16 *pb0 __asm__("$9");   /* D_801870B0 -> $t1 */
    register s16 *pac __asm__("$6");   /* D_801870AC -> $a2 */
    register s16 *pb8 __asm__("$8");   /* D_801870B8 -> $t0 */
    u16 *pb4;
    u16 a, b;
    int id;
    int a1v, a2v, d94;

    pb0 = D_801870B0;
    __asm__ __volatile__("" : : "r"(pb0));

    a = ((u16 *)p2)[0]; pac = D_801870AC; pb0[0] = a; b = ((u16 *)p1)[0]; pb8 = (*(s16 * *)&D_801870B8); pac[0] = b; pb8[0] = a - b;
    a = ((u16 *)p2)[1]; pb0[1] = a; b = ((u16 *)p1)[1]; pac[1] = b; pb8[1] = a - b;
    a = ((u16 *)p2)[2]; pb0[2] = a; b = ((u16 *)p1)[2]; pac[2] = b; pb8[2] = a - b;

    id = ((int)arg0) & 0xFFFF;
    a1v = pac[0]; a2v = pac[2]; d94 = D_801D94F0;
    __asm__ __volatile__("" ::: "memory");
    D_801D9500 = 0;

    if (func_80134A74(id, a1v, a2v, d94)) {
    found:
        pb4 = (*(u16 * *)&D_801870B4);
        ((u16 *)p2)[0] = pb4[0];
        ((u16 *)p2)[1] = pb4[1];
        ((u16 *)p2)[2] = pb4[2];
        ((u16 *)p2)[3] = D_801D9500;
        return 1;
    }
    {
        register u16 *qb __asm__("$4");   /* D_801870AC -> $a0 (reloaded) */
        register int qa0 __asm__("$5");   /* D_801870B0[0], kept in $a1 for the 2nd-call arg */
        register u16 *qa __asm__("$6");   /* D_801870B0 -> $a2 (reloaded) */
        qb = (u16 *)D_801870AC;
        qa = (u16 *)D_801870B0;
        qa0 = qa[0];
        if (((qb[0] & 0xFF80) == (qa0 & 0xFF80)) &&
            ((qb[2] & 0xFF80) == (qa[2] & 0xFF80)))
            return 0;
        if (func_80134A74(id, (s16)qa0, (s16)qa[2], D_801D94F0))
            goto found;
        return 0;
    }
}


// @class: schedule
// @stuck: none — MATCH (62 ins, relocation-masked)


extern u8 D_801870B0;
extern u8 D_801870AC;
extern s16 *D_801870B4;
extern u8 D_801870B8;
extern int D_801D94F0;
extern u16 D_801D9500;

extern int func_80134A74(int, s16, s16, int);

int func_80135168(u16 arg0, u16 *p1, u16 *p2)
{
    register s16 *pb0 __asm__("$8");
    register s16 *pac __asm__("$6");
    register s16 *pb8 __asm__("$7");
    u16 *pb4;
    u16 a, b;
    int a1v, a2v, d94;

    pb0 = (*(s16 * *)&D_801870B0);
    __asm__ __volatile__("" : : "r"(pb0));

    a = p2[0]; pac = (*(s16 * *)&D_801870AC); pb0[0] = a; b = p1[0]; pb8 = (*(s16 * *)&D_801870B8); pac[0] = b; pb8[0] = a - b;
    a = p2[1]; pb0[1] = a; b = p1[1]; pac[1] = b; pb8[1] = a - b;
    a = p2[2]; pb0[2] = a; b = p1[2]; pac[2] = b; pb8[2] = a - b;

    a1v = pac[0]; a2v = pac[2]; d94 = D_801D94F0;
    __asm__ __volatile__("" ::: "memory");
    D_801D9500 = 0;
    if (func_80134A74(arg0, a1v, a2v, d94)) {
        pb4 = (*(u16 * *)&D_801870B4);
        p2[0] = pb4[0];
        p2[1] = pb4[1];
        p2[2] = pb4[2];
        p2[3] = D_801D9500;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135260);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135480);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135888);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135A4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135D20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135EB0);

s32 func_80136334(void *arg0, s32 arg1, s32 arg2) {
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
        dx = (s16) arg2 - (*(s16 **)&D_801870AC)[2];
        d = dx;
        denom = -(*(s16 **)&D_801870B8)[2];
    } else {
        denom = (*(s16 **)&D_801870B8)[2];
        d = (*(s16 **)&D_801870AC)[2] - (s16) arg2;
        dx = -d;
    }
    n = -d;
    {
        register s16 *b8 __asm__("$6") = *(s16 **)&D_801870B8;
        u16 *ac = *(u16 **)&D_801870AC;
        b4 = D_801870B4;
        b4[0] = ac[0] + n * b8[0] / denom;
        b4[1] = ac[1] + n * b8[1] / denom;
        b4[2] = ac[2] + dx;
    }

    if (b4[0] < M2C_FIELD(arg0, s16 *, 4)) return 0;
    if (M2C_FIELD(arg0, s16 *, 6) < b4[0]) return 0;
    if (b4[1] < M2C_FIELD(arg0, s16 *, 8)) return 0;
    if (M2C_FIELD(arg0, s16 *, 0xA) < b4[1]) return 0;
    if (a1v & 0x8000) {
        u16 *b0 = *(u16 **)&D_801870B0;
        b4[0] = b0[0];
        b4[1] = b0[1];
    }
    D_801152AA = 0;
    (*(s16 *)D_801152A8) = 0;
    if (a1v & 1) {
        D_801870B4[2] = a2v + 2;
        __asm__ __volatile__("");
        D_801152AC = 0xFFF;
    } else {
        D_801152AC = -0xFFF;
        D_801870B4[2] = a2v - 2;
    }
    __asm__ __volatile__("" :: "r"(a1v), "r"(a2v));
    (*(s16 *)D_80126720) = (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1;
    D_80126722 = (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1;
    result = 1;
    D_80126724 = (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1;
    return result;
}

// @class: regalloc-order — F-band exemplar func_801365B8 (x134). Real-TU reconciled (rtu_match).
// D_801870AC/B0/B8 file-scope `extern u8` holding pointers -> read via *(T**)&sym (§42c-2).
// D_801870B4 file-scope `extern s16*` -> use directly. D_80126720 file-scope `extern u8[]`
// -> single store via *(s16*)D_80126720. D_801152A8/AA/AC, D_80126722/24 block-scope externs
// (siblings use block-scope; gcc-2.7.2 does not cross-conflict block-scope externs).
s32 func_801365B8(void *arg0, s32 arg1, s32 arg2) {
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
        var_v1 = (s16) arg2 - (*(s16 **)&D_801870AC)[0];
        var_a1 = var_v1;
        var_a3 = -(*(s16 **)&D_801870B8)[0];
    } else {
        var_a3 = (*(s16 **)&D_801870B8)[0];
        var_v1 = (*(s16 **)&D_801870AC)[0] - (s16) arg2;
        var_a1 = -var_v1;
    }
    ac = *(u16 **)&D_801870AC;
    b4 = D_801870B4;
    b8 = *(s16 **)&D_801870B8;
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
        b4[1] = (s16) (*(u16 **)&D_801870B0)[1];
        b4[2] = (s16) (*(u16 **)&D_801870B0)[2];
    }
    D_801152AC = 0;
    D_801152AA = 0;
    if ((a1c & 1) != 0) {
        *(s16 *)D_801152A8 = 0xFFF;
        M2C_FIELD(D_801870B4, s16 *, 0) = a2c + 2;
    } else {
        *(s16 *)D_801152A8 = -0xFFF;
        M2C_FIELD(D_801870B4, s16 *, 0) = a2c - 2;
    }
    *(s16 *)D_80126720 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 4) + M2C_FIELD(arg0, s16 *, 6)) >> 1);
    D_80126722 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 8) + M2C_FIELD(arg0, s16 *, 0xA)) >> 1);
    var_v0 = 1;
    D_80126724 = (s16) ((s32) (M2C_FIELD(arg0, s16 *, 0xC) + M2C_FIELD(arg0, s16 *, 0xE)) >> 1);
    return var_v0;
}

// @class: pointer-type — pointer-vs-array reconcile for func_80136824 (ov_SC01_077_a)
// D_801870AC/B0/B8 are file-scope `extern u8`, D_801870B4 is `extern s32 []`; each HOLDS a
// pointer value that the target loads via lw then derefs. Read as pointer via *(T**)&sym.
// D_801870B4 must be a SCALAR pointer (not s32[]) — as an array it decays and gcc CSEs the
// base address into a held reg (lui;addiu;lw 0(reg)) across the 3 reloads; as a scalar
// pointer it folds %lo (lui;lw %lo). Retype all 3 file-TU occurrences (byte-neutral: the
// siblings read it once via *(u16**)&sym == direct lw either way).

s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {
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
        var_t0 = (s16) arg2 - (*(s16 **)&D_801870AC)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_801870B8)[1];
    } else {
        var_a3 = (*(s16 **)&D_801870B8)[1];
        var_v1 = (*(s16 **)&D_801870AC)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    b8 = (*(s16 **)&D_801870B8);
    ac = (*(u16 **)&D_801870AC);
    b4 = D_801870B4;
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
        p = (*(u16 **)&D_801870B0);
        b4[0] = (s16) p[0];
        b4[2] = (s16) p[2];
    }
    D_801152AC = 0;
    (*(s16 *)D_801152A8) = 0;
    if (arg1 & 1) {
        b4b = D_801870B4;
        D_801152AA = 0xFFF;
        __asm__ __volatile__("");
        var_v0_3 = pos + 2;
    } else {
        b4b = D_801870B4;
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


extern s16 *D_801870B4;   /* holds a pointer value (*(u16**)&D_801870B4) */

s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3) {
    extern void ApplyMatrixSV(void *m, void *v0, void *v1);
    extern void ApplyRotMatrix(void *v0, void *v1);
    extern u16 D_80126722;
    extern s16 D_80126724;
    extern s16 D_801152AA;
    extern s16 D_801152AC;

    s32 out[4];
    u16 *pb4;

    if (a0) {
        ApplyMatrixSV((void *)a3, *(void **)&D_801870B4, *(void **)&D_801870B4);
        ApplyMatrixSV((void *)a3, (void *)D_80126720, (void *)D_80126720);
        ApplyRotMatrix((void *)D_801152A8, (void *)out);
        *(s16 *)D_801152A8 = out[0];
        D_801152AA = out[1];
        D_801152AC = out[2];
    }

    pb4 = *(u16 **)&D_801870B4;
    *(s16 *)(a2)     = pb4[0] + *(s32 *)(a1 + 0x48);
    *(s16 *)(a2 + 2) = pb4[1] + *(s32 *)(a1 + 0x4C);
    *(s16 *)(a2 + 4) = pb4[2] + *(s32 *)(a1 + 0x50);

    *(u16 *)D_80126720 = *(u16 *)D_80126720 + *(s32 *)(a1 + 0x48);
    D_80126722 = D_80126722 + *(s32 *)(a1 + 0x4C);
    D_80126724 = D_80126724 + *(s32 *)(a1 + 0x50);
}


DEFINE_func_80136BC4()  /* dedup: shared engine-core @0x80136BC4 (src/shared) */

DEFINE_func_80136C1C()  /* dedup: shared engine-core @0x80136C1C (src/shared) */

DEFINE_func_80136C3C()  /* dedup: shared engine-core @0x80136C3C (src/shared) */

DEFINE_func_80136C44()  /* dedup: shared engine-core @0x80136C44 (src/shared) */

DEFINE_func_80136C4C()  /* dedup: shared engine-core @0x80136C4C (src/shared) */

extern unsigned short D_800B99F0;
extern void (*D_801870C8[])(void);

void func_80136C54(void)
{
    D_801870C8[D_800B99F0]();
}

// @class: struct
// @stuck: none — MATCH (28 ins). 10-byte 1-aligned struct copy (S10{char s[10]}) from global D_801D81E4 into a stack buffer, then ((void(*)(int, void *, int, int, int, int))func_8001534C)(0,&buf,0x78,0x10,0,0). gcc emits the block move as 2 unaligned words (lwl/lwr+swl/swr) + 2 bytes (lb/sb).

typedef struct { char s[10]; } S10;

s32 func_80136C90()
{
    extern S10 D_801D81E4;

    S10 buf = D_801D81E4;
    ((void(*)(int, void *, int, int, int, int))func_8001534C)(0, &buf, 0x78, 0x10, 0, 0);
}


DEFINE_func_80136D00()  /* dedup: shared engine-core @0x80136D00 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (61 ins). Modeled on byte-proven sibling func_8012D3B4. Key: precompute ((v0+v0_2)>>3)*4 into a separate statement before AddPrim so the D_800B9A02*0x14 array-index chain regallocs to $v1/$v0 (computing the index inline left lhu in $a0 / product in $v1 → 6-off).

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136D08 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80136DFC);

DEFINE_func_80136EC4()  /* dedup: shared engine-core @0x80136EC4 (src/shared) */

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ECC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80136F3C);

// @class: schedule
// @stuck: none — MATCH
DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80137178);

/* func_801372B0 — MATCH (207 ins), match_one relocation-masked byte-exact (2026-07-07, Fable5)
 * ov_SC01_077 region-a (asm/ov_SC01_077/nonmatchings/ov_SC01_077_a). Debug 3D-axis overlay:
 * draws the +X/+Y/+Z axis lines (white) + a red cross at +X+6 + sibling markers at +Y+6/+Z+6.
 *
 * Prior state: CLOSE=8 (count-exact, all regs + global hoists solved; see LEVERS_HARVEST).
 * The 8 residual = TWO independent sched1 S2 (birthing-boost) artifacts, both cracked zero-byte:
 *
 * LEVER A — idx 73-78 (corner-1 by/ax/bx/[a1-chain]/ay order): S2-KILL ON PINNED SINGLE-SET VARS.
 *   birthing_insn_p (sched.c:2469) boosts ANY live single-set REG dest — including register-asm
 *   HARD regs (reg_n_sets[] is indexed by hard regno too). The single-set pins ax($16)/by($20)
 *   were boosted -> adjust_priority (sched.c:2507) fires the instant their anti-dep partner
 *   (ay/bx in-place update) schedules -> glued adjacent, collapsing out.vx's use span. The
 *   multi-set pins (bx, ay: 2 sets each) were never boosted and sat at source order. Fix: one
 *   re-tie asm per var AFTER its call-1 use = a 2nd set -> reg_n_sets==2 -> no boost -> all four
 *   adds revert to pure source/LUID order (rank_for_schedule sched.c:2429 ties). 8 -> 2.
 *
 * LEVER B — idx 31/32 (li $s3,0xFF vs li $t0,0x78 order): S2 FIRE-TICK DIAL VIA CONSUMER STORE
 *   ORDER. A boosted const is placed directly ABOVE its LAST-backward-picked consumer; among
 *   equal-priority independent stores the backward scheduler picks highest-LUID first. With
 *   corner-0 written [x0, attr, r,g,b, y0], the r/g/b sb's (white's consumers) out-LUID the x0
 *   store -> picked BEFORE it -> white's boost fires too early -> li 0xFF lands BELOW the
 *   x0-cluster. Writing corner-0 [attr, r,g,b, x0, y0] (colors FIRST) drops the sb's LUIDs below
 *   the x0 store's -> backward cascade picks them AFTER it -> white's boost-fire slips to the
 *   exact tick above the x0-li (dump: fire T-157 -> T-161). sched2's own hazard cascade
 *   re-normalizes the FINAL store layout identically for both source orders (x0@33 ... attr@41,
 *   rgb@42-44, y0@45), so the reorder's only byte effect is the boosted li's slot. 2 -> 0.
 *   (Found by the directed permuter at iter 291 after 12 hand variants byte-validated the
 *   fire-tick model; corners 2/3 keep [x0, attr, r,g,b, y0] — no li $s3 in their blocks.)
 *
 * Kept from the CLOSE=8 draft (LEVERS_HARVEST 173->8): $s7 cross-BB base-offset split (mat+=0x18),
 * post-jal out.vx/vy scratch pins ($a3/$v1/$v0), x1v/y1v boost-defeat re-ties, corner-1 op fence.
 */
/* Svec_801372B0 (8B vertex) + Gline_801372B0 (16B GsLine) lifted to src/shared/engine_types.h
 * for ×134 propagation (a different same-named SVEC lives in _after.c). */
DEFINE_func_801372B0()  /* dedup: shared engine-core @0x801372B0 (src/shared) */


DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375EC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80137614);

DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767C (src/shared) */

DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376C8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801376E8);

DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377B4 (src/shared) */

DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801378F0);

DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379D8 (src/shared) */

DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379EC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801379FC);

// @class: remat
// @stuck: target CSEs &D_801269F0 once for load+call arg; force via local pointer
extern s32 D_80127548[];
extern int D_8018711C;
extern int D_801269F0;
extern void func_80138BE0(int p);

void func_80137B80(void) {
    int *p = &D_801269F0;
    (*(int *)&D_80127548) = 0x24;
    if (*p != 0) {
        ((void (*)(int *))func_80138BE0)(p);
    }
    D_8018711C += 1;
}


DEFINE_func_80137BD8()  /* dedup: shared engine-core @0x80137BD8 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (51 ins). Three globals stored/loaded around 3 calls; &D_801269F0 held in $s1, arg1 in $s0 across calls; return reloads global D_800A5E60.

extern unsigned char D_80126A0E;
extern short D_80126A0A;
extern s16 D_801269F4;
extern int D_800A5E60;
extern int D_8018711C;
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
        if (D_8018711C & 4) {
            ((void (*)(void *, int))func_80139680)(&D_801269F0, arg1);
        }
    }
    return D_800A5E60;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80137DD4);

DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137FD8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801380E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801387B8);

/* func_80138948: sh 7 @0x4; sb 0 @0x1F; sb 0 @0xD (store order = source order). */
DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */

DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895C (src/shared) */

DEFINE_func_80138AB4()  /* dedup: shared engine-core @0x80138AB4 (src/shared) */

DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138B88 (src/shared) */

// @class: struct
// @stuck: none — MATCH (match_one: MATCH 20 ins)

extern void (*D_80187120[])(void);

void func_80138BE0(int p)
{
    if (*(unsigned short *)(p + 0xe) != 0) {
        *(unsigned short *)(p + 0xe) -= 1;
    }
    D_80187120[*(short *)(p + 4)]();
}


DEFINE_func_80138C30()  /* dedup: shared engine-core @0x80138C30 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80138C60);

DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138D58 (src/shared) */

DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138DB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80138DE0);

/* func_80138ED0 — region-a bit-unpacking / tilemap builder (159 ins, reach-134).
 * STATUS: MATCH (match_one = 0, relocation-masked byte-identical), cracked from close=21.
 *
 * Levers applied (all gcc-2.7.2-source-cited; -> cookbook §31/§32):
 *  [C1 prologue/sched]  `pb = param_3;` as the FIRST statement. sched.c:3191-3215 pins the leading
 *      run of SET(reg, hard-reg-src) parm copies at block-0 head in sched1 ("don't delay getting
 *      parameters"). combine folds the pinned `s3<-a2` parm copy into the statement-positioned
 *      pb-init, so the a2 read escapes the pin, gets a late LUID, and sched2 (backward list sched,
 *      ties broken by LUID after the class-of-last-scheduled rule) reproduces the target prologue:
 *      addiu a1,sp,16 hoisted, saves ra/s4/s3/s0 batched by the schedule_select hazard rule
 *      (sched.c:2686), and move s3,a2 landing in the lbu load-delay gap.
 *  [C2 preheader order]  Per-branch `u32 pv = uVar1;` BEFORE `p = base;` replaces loop.c's
 *      move_movables hoist of the in-loop zero-extend (loop.c:1652/1810 emits at loop_start, which
 *      lands AFTER the p=base statement -> wrong order). Explicit statement = target order
 *      [andi t1,s4][move a1,t2].
 *  [C2b copy-loop body order]  `iVar2++` moved to the END of the do-body (LUID order drives the
 *      final [lhu][addiu src][addiu t0] arrangement).
 *  [C3 tail regalloc]  The crux. Target assignment {dcount=v1, c36+df=v0, chain=v1, ba=a1, dst=a0,
 *      src=a2} is reached by:
 *      - dp pinned $4: kills the &D local qty entirely (lui a0/addiu a0/addiu a0,4 all in hard a0),
 *        and hard-blocks a0 for src.
 *      - ba pinned $5 (+ dst pinned $4, disjoint inner scope): the two sides of the surviving
 *        giv-init-style move `addu a0,a1,zero`. The $5 pin also raises reg_n_sets[$a1] so sched1's
 *        birthing boost (sched.c:2507 adjust_priority, reload_completed==0 only) does not fire on
 *        the call-arg insn a1<-sp+16 — that boost would scramble the prologue (class 1).
 *      - `tmp` (the bit-loop sll temp, global allocno already in v1) REUSED for the mult chain:
 *        a multi-block pseudo has reg_qty < 0, so local-alloc combine_regs (local-alloc.c:1667)
 *        refuses to tie ba to the chain, and set_preference's operand-strip (global.c:1545,
 *        format[0]=='e') poisoning is neutralized by conflict pruning.
 *      - mult split `tmp = (df << 1) + df; tmp = tmp << 4;` so the addu lands directly in tmp's
 *        pseudo: only ONE fresh local (q1 = df<<1) remains, whose density loses v0 to {c36,df}.
 *      - THE 3-QTY SORT BUG: local-alloc.c:1441-1463/:1494-1516 sorts <=3 local qtys with an
 *        unrolled switch that COMPARES fixed qty numbers (qty_compare(0,1),(1,2),(0,1)) but
 *        EXCHANGES order-slots; when pri(q1)>pri(q0),pri(q2) the third compare re-fires and undoes
 *        the first swap -> allocation in CREATION order, not density order. With >=4 qtys it uses
 *        qsort (correct density order). The zero-instruction DECOY qty (asm-def anchored on ba +
 *        asm-use) pushes the tail-preheader block back to 4 qtys => density order => {c36,df}
 *        (tied via combine_regs since c36 dies at the subu) takes v0 first, dcount falls to v1,
 *        q1 to v1, and first-fit (global.c:904 find_reg; regs_used_so_far pre-seeded with all
 *        call-used regs, global.c:352) gives src=a2.
 *      - The dual dummy `asm("" :: "r"(c36), "r"(dcount))` releases the li-36 and the lw together
 *        in sched1's backward pass; the class rule (sched.c:2385 rank_for_schedule: cost-1 dep =
 *        class 3 beats cost-2 load dep = class 1) then emits [lw v1][li v0] in target order.
 *      All asm()s are empty templates: zero bytes, input-only or write-then-read pairs — the
 *      byte-gate certifies the allocation they induce.
 */
DEFINE_func_80138ED0()  /* dedup: shared engine-core @0x80138ED0 (src/shared) */


DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914C (src/shared) */

DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391F0 (src/shared) */

DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */

DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392C8 (src/shared) */

/* func_801392FC (T7, 182 ins, reach-134, HARDEST tier — all 8 $s0-$s7)  —  MATCH (182 ins).
 * GsSPRITE-drawing loop; LOOP form of the banked twin func_80139680 (engine_core.h DEFINE_).
 * $s map: $s0=arg0, $s1=i, $s2=rem, $s3=arg1, $s4=acc(+=0xC), $s5=arg2(natural, NO pin), $s6=0xC,
 * $s7=0xC-arg1.  Solved by Fable5 from the Opus close=2 seed; every lever below byte-verified.
 *
 * LEVER 1 (R1, the wall — count-load software-pipeline):  carry the raw count across the backedge:
 *   u16 cnt loaded VOLATILE in the preheader and re-loaded VOLATILE at the loop tail (after the
 *   call); divisor = (s16)cnt + 1 at the loop top.  Mechanics (gcc-2.7.2 source):
 *   - flow.c:2087: LOG_LINKS only created when BLOCK_NUM(use)==BLOCK_NUM(def) — combine can never
 *     fold the tail/preheader lhu (def BB) into the top-BB sll/sra sign-extend, so the "split and
 *     schedulable" sequence the target shows is simply a cross-BB dataflow, unreachable from any
 *     single-BB expression (that was the seed's dead end).
 *   - reorg.c fill_slots_from_thread then steals the top-BB-leading sll into the loop-back bnez
 *     delay slot and redirects the label to the sra (the sll appears twice: preheader fall-in +
 *     delay slot).
 *   - WHY VOLATILE (frame parity, not semantics): a non-volatile cnt load gets cse-commoned with
 *     the same-address *(s16*) condition read (the LOOP_CONT label between them is deleted as
 *     unused before cse2), and combine then does the KEEP-LOAD fold (newi2pat): combine.c:2089
 *     sets elim_i2=0 when newi2pat!=0, so the dead ashift-temp's REG_DEAD is NOT dropped
 *     (distribute_notes:10741), walks back, hits a CODE_LABEL and plants a (use reg) insn
 *     (combine.c:10835-10847); the stale-ref allocno then gets an 8-byte reload stack slot
 *     (frame 0x88/0x90 instead of 0x80).  The volatile mem is never hashed by cse (do_not_record),
 *     the condition folds CLEAN (temps fully elided, no slot), and sched2 still hoists the lh
 *     above the volatile lhu because sched.c:811 read_dependence requires BOTH mems volatile.
 *     Target frame keeps exactly ONE such slot: the w keep-load fold at +0x34 (lh/addu/slti shape).
 * LEVER 2 (prologue): NO $21 register pin (the seed needed one; with this body shape arg2 lands
 *   in $s5 naturally).  The natural param copy is batched sw s5/addu s5,a2 ahead of a0=0/a1=1.
 * LEVER 3 (buf+0x0F byte stores): route each `rem*12 + *(u8*)(arg0+0x3A) [+ arg1]` sum through an
 *   s32 temp — defeats the C-frontend QI-shorten, whose canonical QImode (plus (lbu) (prod)) has
 *   the operands swapped vs the target's SI-mode (plus (prod) (lbu)) — [addu v0,v0,v1 not
 *   addu v1,v1,v0].  (The s16 store at buf+0x06 IS shortened: mem-first there is correct.)
 * LEVER 4 (pre-call schedule / jal delay = i++): `acc += 0xC; i++;` AFTER the call statement.
 *   sched2 is the 2.7.2 BACKWARD list scheduler; rank_for_schedule ties break on INSN_LUID
 *   (original order), so statement position steers the a0/a1 arg setups early and leaves i++
 *   adjacent for reorg's slot fill.
 * LEVER 5 (post-loop block): statement order buf+0x04, buf+0x06, buf+0x0A, buf+0x0E, buf+0x0F —
 *   the LOOP BODY's own order (x,y,h,0E,0F), NOT the emission order.  This keeps sched1 from
 *   sinking the buf4 store into the s3-2 chain (which would stretch the 0x30-tmp's live range and
 *   flip the local-alloc v0/v1 assignment cascade: qty priority = log2(refs)*refs*size/length,
 *   local-alloc.c qty_compare).  The lone load-delay nop after lhu 0x30 is the target's own stall.
 * LEVER 6 (>=0xFD tail): the final call is WRITTEN IN BOTH ARMS (duplicated).  Post-reload
 *   cross-jumping (jump2 runs between sched2 and dbr) merges only the identical [jal] suffix
 *   (arm tails diverge one insn earlier), creating .L8013959C at the else's jal; dbr then fills
 *   the arm's j-slot with the a0 copy and the shared jal's slot stays nop (label blocks the
 *   backward scan).  The buf+0x04 += old buf+0x08 read is INLINE (no u16 t local) — expansion
 *   order lhu30-then-lhu(buf8) puts the loaded old-w in $a0 and lets sched pull the 0x20/0x0E
 *   stores into the load latency, matching 145-152 exactly.
 * LEVER 7 (the one pin): register s32 a1c __asm__("$5") used ONLY to re-arm a1 before the arm's
 *   SECOND call (`a1c = (s32)arg2; func(..., a1c, ...)`), producing the mid-block addu a1,s5 and
 *   suppressing call#2's own a1 copy (which is what limits the cross-jump depth to [jal] and
 *   frees the j delay slot for a0).  Call#1 and the else call pass plain (s32)arg2 — call#1's own
 *   a1 copy becomes its jal-delay fill.
 */
DEFINE_func_801392FC()  /* dedup: shared engine-core @0x801392FC (src/shared) */


extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
} Stk801395D4;

void func_801395D4(void * a0)
{
    Stk801395D4 sp10;
    u16 mul;
    u16 base;
    sp10.f0 = *(u16 *)(a0 + 0x38);
    mul = *(u16 *)(a0 + 0x12);
    base = *(u16 *)(a0 + 0x3A);
    sp10.f4 = 0x38;
    sp10.f6 = 0xC;
    sp10.f2 = base + mul * 12;
    func_80059888(&sp10, 0, 0, 0);
}

DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */


DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */


DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */

// @class: struct
// @stuck: none — MATCH (89 ins). GsSPRITE build (twin func_80139680). Levers: (1) two loads per
// D_80187164 addr — signed *(s16*) for tpage, unsigned *(u16*) for u/v — placed at their natural
// program points (buf stores interposed) so gcc can't CSE-merge them; (2) s32 temps t2/t0 force lh
// (defeat mask-driven lh->lhu narrow that would srl-reassociate the shift); (3) hi/lo temps pin the
// tpage OR structure so `|0x20` binds the middle term (else fold hoists it onto the first term);
// (4) pins: e=$a3, off=$a0 (index reuses the freed arg reg); (5) b164 base materialized into its OWN
// reg via `b164=&sym; b164=off+b164` (two-stmt) so base+ptr share $a2 (a separate base local/pin
// lands base in $v0 or ripples the tail).

#include "common.h"

extern short D_800B9A02;
extern u8 D_800A6518[];
extern u8 D_80187164;
extern u8 D_801871A8;
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
    b164 = (u8 *)&D_80187164;
    off = ((s32)*(u8 *)(e + 0x20) - 1) << 2;
    b164 = off + b164;

    *(s32 *)((u8 *)buf + 0x00) = 0;

    t2 = *(s16 *)(b164 + 2);
    t0 = *(s16 *)(b164 + 0);
    hi = (t2 & 0x100) >> 4;
    lo = ((t0 & 0x3C0) >> 6) | 0x20;
    *(s16 *)((u8 *)buf + 0x0C) = hi | lo | ((t2 & 0x200) << 2);

    b1A8 = (u8 *)&D_801871A8 + off;
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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80139BE0);

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

// @class: regalloc-order
// @stuck: none — MATCH; p=&D_80127524 pointer idiom + memory barrier forces *p reload for call arg
DEFINE_func_8013A2BC()  /* dedup: shared engine-core @0x8013A2BC (src/shared) */


DEFINE_func_8013A378()  /* dedup: shared engine-core @0x8013A378 (src/shared) */


struct S8013A4C4;

DEFINE_func_8013A380()  /* dedup: shared engine-core @0x8013A380 (src/shared) */


DEFINE_func_8013A448()  /* dedup: shared engine-core @0x8013A448 (src/shared) */

DEFINE_func_8013A4C4()  /* dedup: shared engine-core @0x8013A4C4 (src/shared) */

/* func_8013A530 — region-a giant (204 ins, reach-134, HARDEST tier: ALL 8 $s0-$s7 + $fp).
 * Camera/entity transform dispatch on mode = *(u16*)(ent+0x18) (ent = *(param_1+4), held in $fp).
 * STATUS: match_one MATCH (204 ins), Fable5 Phase-24 T7. LOOSE/intended types.
 *
 * The whole function is byte-exact: the CASE1 block (all 8 $s regs live across three calls
 * func_80015F04/F04/5D4C), the sltiu/slti dispatch, both magic divisions (/0x9a,/0x2a), the
 * unaligned 4-byte copy, the frame, AND the clamp's double register-split (the last 10).
 *
 * LEVERS (all cookbook-cited):
 *  [dispatch]  outer `uVar2<7` on the u16 -> sltiu (gcc folds u16<C to unsigned); the redundant inner
 *      guard uses a SIGNED copy `sVar2=uVar2` -> a FRESH slti (a single signed cmp emits slt; only
 *      CSE-reuse canonicalises signed->unsigned). Branch polarity read off the target `beq ==1`:
 *      `if(uVar2!=1){DEFAULT}else{CASE1}` makes DEFAULT the fall-through, CASE1 the branched-to/last.
 *  [§17a] unaligned 4-byte mem->mem copy -> memcpy((void*)dst,(void*)src,4) -> lwl/lwr/swl/swr.
 *  [§32-5] frame is +8 over args+saves -> a dead 8-byte local (int deadlocal[2]).
 *  [§17]  bVar1 pinned $t0 (fixes its reg + pushes the 0x99/4 consts to $t1); a zero-byte
 *      __asm__("":: "r"(bVar1)) extends its range past the div2 `&0x10` so the andi lands in $v0
 *      (not in-place $t0) -> div1+div2 byte-exact.
 *  [§17]  f34 pinned $a1 (field34) so uVar6 takes $a0 (density-tie the target resolves the other way).
 *
 *  CLAMP (the former close=10 residual — RC-6 verdict OVERTURNED, no $v1 pin needed; cookbook §36):
 *  [pin]   fc stays pinned $a1: canon_reg NEVER rewrites hard-reg uses (cse.c:2545 "Never replace a
 *      hard reg") -> both compares keep reading fc even while iVar7 holds an equivalent value.
 *  [$0-add] `register int zr __asm__("$0"); iVar7 = fc + zr;` — the copy as (plus $a1 $0), NOT
 *      (set reg reg): cse forms no fc<->iVar7 equivalence (make_regs_eqv never runs -> no canon
 *      poisoning either direction) and combine cannot absorb the fc load into iVar7 (no extend+plus
 *      pattern) — a plain `int iVar7 = fc;` gets REVERSED (load->pseudo, pin<-copy, 1 insn short).
 *      (plus $a1 $0) assembles to the byte-identical `addu $v1,$a1,$zero`; maspsx/ASPSX-2.56 hops it
 *      over the slt into the beqz delay slot (cc1 emits [lh;lh;addu;slt;beqz]).
 *      iVar7 as a PSEUDO (not a $v1 pin) un-poisons reload's retry pool: with $2/$3 pins,
 *      regs_explicitly_used -> bad_spill_regs (reload1.c:3900-15) forced CASE1's 2nd-product
 *      retry_global_alloc to $t2; unpinned it lands $v1 (".greg: Register 177 now in 3").
 *  [flip]  then-arm inner compare spelled `((t<<16)>>16) > (int)mem` (canonically the SAME slt as
 *      `mem < t-ext`): mirrors the else-arm's expansion-uid order so sched1's BACKWARD list
 *      scheduler (mem-unit hazard blocks the lh next to the sh; boosted-group ties break by uid)
 *      keeps the fe-reload lh BELOW the addiu that kills iVar7 -> the reload (local-alloc, first
 *      pick) and iVar7 (global) are live-DISJOINT and can both hold $v1. Unflipped, sched1 hoists
 *      the lh to the block top ("blocking insn 185 for 1 cycles") -> hard-3 conflict -> iVar7=$a0.
 *  [dens]  two-input dummy `__asm__("" :: "r"(iVar7), "r"(t));` in the ELSE arm (anchors at t's def,
 *      §34 toolkit): +1 ref lifts iVar7's allocno priority (global.c:594 floor_log2(refs)*refs/len:
 *      3/10 -> 8/11) past the fe-load's 3/5, so iVar7 allocates FIRST -> $v1, fe -> $a0. Must NOT
 *      sit in block1: its #APP markers land between the addu-copy and the slt and block maspsx's
 *      delay-slot hop (that was v4's last diff).
 *  [keep]  `__asm__("" :: "r"(fc));` after the clamp: fc/$a1 no longer DIES at the else-compare slt,
 *      so the slt-result temp gets no qty_phys_sugg $a1 suggestion (local-alloc.c suggested-first
 *      path) and falls to plain first-fit $v0, matching the target.
 *  [nat]   the 2nd split (lh $v1 / addu $a0,$v1 / slt on $v1 / sh $a0) is NATURAL: `(int)mem`
 *      expands as HI-load + sll/sra; the body re-load cse-folds onto the HI pseudo; combine merges
 *      the extend into one lh and re-emits the HI pseudo as a subreg copy (the store temp).
 */
DEFINE_func_8013A530()  /* dedup: shared engine-core @0x8013A530 (src/shared) */


DEFINE_func_8013A860()  /* dedup: shared engine-core @0x8013A860 (src/shared) */

DEFINE_func_8013A8B0()  /* dedup: shared engine-core @0x8013A8B0 (src/shared) */

DEFINE_func_8013A8BC()  /* dedup: shared engine-core @0x8013A8BC (src/shared) */


DEFINE_func_8013A8FC()  /* dedup: shared engine-core @0x8013A8FC (src/shared) */


DEFINE_func_8013A9B4()  /* dedup: shared engine-core @0x8013A9B4 (src/shared) */

DEFINE_func_8013A9F8()  /* dedup: shared engine-core @0x8013A9F8 (src/shared) */

DEFINE_func_8013AA24()  /* dedup: shared engine-core @0x8013AA24 (src/shared) */

DEFINE_func_8013AB54()  /* dedup: shared engine-core @0x8013AB54 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (122 ins). GTE lerp+mvmva loop. Two levers: (1) flat `extern s16`
//   source arrays indexed [2*i]/[2*i+1] force 4 separate walking IVs (t2/t3/t4/t5) instead of
//   one shared offset-IV + symbol(reg) addressing; (2) INVERTED-arm if/else
//   `if (flag<0) out3=-tbl; else out3=tbl;` gives the target's bgez polarity + reload-per-arm
//   sign-flip block (a plain ?: hoists the common lbu; the inverted if/else does not, and gcc
//   still merges the sb). out2[i]=out2[0] tail-copy of the align-2 Pair emits lwl/lwr/swl/swr.
#include "common.h"

typedef struct { s16 x, y; } Pair;

extern s16 D_800D45F4[];   /* src0 (flat: [2*i]=x, [2*i+1]=y) */
extern u8  D_801871EC[];   /* sign table, alt (when a1 < 0xC00) */

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
    extern s16 D_800D466C[];
    extern u8 D_80187228[];

    u8 *tbl;
    s16 vec[4];
    s32 res[3];
    s32 i;

    tbl = D_80187228;
    if (((s16)a1) < 0xC00) {
        tbl = D_801871EC;
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


/* func_8013AF20 — MATCH (185 ins) — Phase 24 T7 Fable5 batch, giant 3/3.
 *
 * 3 GPU-primitive-builder loops (2× LINE_F2 len=3 code=0x40, 1× POLY_F4 len=5
 * code=0x28), each ending in the PS1 libgpu addPrim(ot, prim) idiom.
 *
 * THE CRACK (was: Opus close=15, permuter-stuck 40k iters — "loop-invariant
 * const-materialization order coupled to AND order"):
 *
 * 1) addPrim is a P_TAG BITFIELD store, not user masks. setaddr writes the
 *    24-bit `addr` field; gcc's store_fixed_bit_field (expmed.c:556) expands
 *    it as: value & 0x00ffffff FIRST (must_and :667, mask emitted :679-681),
 *    THEN *dest & 0xff000000 (:694-696), THEN or(destmasked, value) (:706 —
 *    dest chain stays op0 of the OR). So the 0x00ffffff movable is FOUND (and
 *    preheader-emitted by move_movables) BEFORE 0xff000000, while the body
 *    still computes the dest-AND first — the decoupling no user-mask C reorder
 *    can express (any `&`-operand swap flips the AND/OR shape with it).
 *
 * 2) NO scheduling barrier. The old do{}while(0) around the 0x3d stores added
 *    a NOTE_INSN_LOOP nest: flow.c weights refs by loop_depth (flow.c:2067/
 *    2315/2501/2711), inflating the 0x3d const's refs 7→10 and flipping the
 *    loop-1 $a2/$a3 contest (pri 4166 > 4000). With the bitfield form the
 *    barrier's original purpose (puVar5→$t1) holds without it.
 *
 * 3) Why the mask WINS $a2 (gdb-on-cc1 verified): sched1 pre-reload-splits
 *    every insn (sched.c:4830 try_split) → mips.md:3208 large_int define_split
 *    turns li 0xffffff into lui+ori → reg_n_sets=2 → FAILS the single-set gate
 *    (local-alloc.c:1021) → ESCAPES update_equiv_regs' live-length doubling
 *    (local-alloc.c:1064). One-instruction consts (61, 0x40, 3, 0xff000000)
 *    get doubled. Priorities (allocno_compare, global.c): mask fl2(7)*7/35 =
 *    4000 vs 0x3d fl2(7)*7/72 = 1944 → mask allocates first → first-fit $a2.
 *    (n_sets 61=1 mask=2 ff000000=1; LL 36/35/33 → post-equiv 72/35/66.)
 *
 * Cookbook §36 (this entry) + gcc-2.7.2-map/loop.md L4 / regalloc.md RC-7.
 */
DEFINE_func_8013AF20()  /* dedup: shared engine-core @0x8013AF20 (src/shared) */


DEFINE_func_8013B204()  /* dedup: shared engine-core @0x8013B204 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (189/189). Levers: (1) POLY_FT4 UV stores in per-vertex source order
//   (u0,v0),(u1,v1),(u2,v2),(u3,v3) -> exact const-materialize schedule + 0xEF held in $v1 across
//   the angle branch, u3 store fills the bnez delay slot. (2) vertex reads *(volatile s32*) force
//   the target's reload-each-vertex (defeats CSE). (3) addPrim via P_TAG 24-bit bitfield store
//   (value-mask-first order, cookbook §36). (4) raw lwc2/mvmva/swc2 inline-asm + memory clobbers.
#include "common.h"


extern void *func_80010A08(s32);
extern s16 D_80187264, D_80187266, D_80187268, D_8018726A, D_8018726C, D_8018726E;
extern u16 D_800D45F6;

void func_8013B274(s32 a0, s32 a1, void *a2)
{
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
        if (!(D_80187266 < ang)) goto outer_else;
        if (!(ang < D_8018726C)) goto inner_else;
        if (ang < D_80187268) { *(s16 *)L = D_80187268; goto done; }
        if (D_8018726A < ang) { *(s16 *)L = D_8018726A; goto done; }
        *(s16 *)L = quot;
        goto done;
    outer_else:
        if (ang < D_80187264) { *(s16 *)L = D_80187264; goto done; }
        *(s16 *)L = quot;
        goto done;
    inner_else:
        if (D_8018726E < ang) { *(s16 *)L = D_8018726E; goto done; }
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


/* func_8013B568..func_8013C964 (16 contiguous fns) moved to ov_SC01_077_o0.c — built -O0 (Phase-19 T1). */
