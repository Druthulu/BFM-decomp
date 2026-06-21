#include "common.h"

/* Phase-19 T1: the -O0 cluster (16 contiguous fns vram 0x8013B568..0x8013C98C, prologue sig
 * 21F0A003 = -O0 frame pointer). Split into its own .c so the Makefile forces CC1FLAGS=-O0 on
 * ov_SC01_077_o0.o (src/boot.c precedent). A single object's .text can't be split around a middle
 * object, so the overlay code is 3 objects: ov_SC01_077_a (before) / ov_SC01_077_o0 (this, -O0) /
 * ov_SC01_077 (after). Data externs hoisted + deconflicted; intra-cluster callees forward-declared.
 *
 * 6/16 matched here (reach-134, but the ×134 fleet rollout is DEFERRED to Phase 20: -O0 functions
 * can't propagate via engine_core.h — that header compiles -O2 in other overlays — so each overlay
 * needs its own -O0 split).
 *
 * 10 stubs DEFERRED to Phase 20: they hit an -O0 codegen quirk — for indexed global access
 * `arr[i]=x`, our cc1 materializes the address (lui;addiu;addu;sw 0(reg)) while the original folds
 * %lo (lui;addu idx;sw %lo(sym)(reg), 1 ins shorter). That's gcc address-splitting behavior our cc1
 * reproduces differently at -O0; cracking it is gcc-source research (Phase-18 §17 / R17 territory),
 * not a C-form fix. The 6 matched below are scalar-store / pointer-loop / simple-call (no index). */
extern s32 D_80187270;
extern s32 D_801DAB24;
extern s32 D_801DAAC0;

void func_8013B83C(s32 a0, s32 a1, s32 a2);
void func_8013BD74(void *a0, s32 a1);

void func_8013B568(s32 arg0) {
    D_80187270 = arg0;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0", func_8013B598);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0", func_8013B6A0);

#include "common.h"
typedef struct { s32 f0; u8 pad[0x18]; } E_3B7AC;   /* sizeof 0x1C stride */
extern E_3B7AC D_801DAA08[];
void func_8013B7AC(int a0) { D_801DAA08[a0].f0 = 0; }


void func_8013B7F4(s32 a0, s32 a1) {
    func_8013B83C(a0, a1, D_801DAB24);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0", func_8013B83C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0", func_8013BC7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0", func_8013BCDC);

void func_8013BD34(s32 a0) {
    func_8013BD74(&D_801DAAC0, a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0", func_8013BD74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0", func_8013C08C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0", func_8013C0F8);

void func_8013C360(s32 a0) {
    s32 *p;
    u32 i;
    p = (s32 *)(a0 + 0x10);
    for (i = 0; i < *(u32 *)(a0 + 8); i++) {
        *(s32 *)(*(s32 *)p) = *(s32 *)((s32)p + 4);
        p = (s32 *)((s32)p + 0xC);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_o0", func_8013C414);

void func_8013C938(void) {
    D_801DAAC0 = 1;
}

void func_8013C964(void) {
    D_801DAAC0 = 0;
}
