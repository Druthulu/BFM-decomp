// func_80143D28 @ 0x80143d28 (ov_SC01_000) -- shared engine fn, 80 ins.
// STATUS: characterized NEAR (15 masked mismatches; instrs 0..62 = 63/80 byte-exact).
//
// The whole body logic, types, splat symbol (D_80180564), and canonical callee sigs are
// PROVEN correct: with iVar3->$s2 / iVar2->$s1 pinned (their true allocation) and sVar4's
// $s3 home forced, the first 63 instructions match byte-for-byte through the sll s3 result.
//
// SOLE BLOCKER (1 real instruction, then a positional shift): the target materializes the
// callee-saved store value into $v0 before the three sh stores --
//     /* 80143E24 21106002 */ addu $v0, $s3, $zero   ; v0 = sVar4
//     sh $v0, 0x1C($s2) ; sh $v0, 0x1A($s2) ; jal func_8012BEE8 ; sh $v0, 0x18($s2)(delay)
// gcc here instead stores `sh $s3` directly (no copy). This copy is an allocator/reload
// artifact: every source-level `tmp = sVar4; sh tmp` is removed by copy-propagation/coalescing,
// and the direct-from-$s3 store is what natural allocation emits. Not source-steerable via
// match_one; this is a textbook PERMUTER candidate (split/rematerialize the store value).
//
// ALLOCATION NOTES (how the register map was reproduced):
//  - iVar3(*(param+0x20))->$s2, iVar2(*(param+0x64))->$s1 pinned to their target homes; without
//    pins, once sVar4 becomes callee-saved it out-prioritizes both and steals $s1 (-> iVars
//    bump to s2/s3, wrong map).
//  - sVar4 = 0x1000 is placed BEFORE ApplyMatrixSV so sVar4 crosses that call at allocation
//    time -> callee-saved. gcc rematerializes the 0x1000 constant load to AFTER the call
//    (matches `addiu $s3,$zero,0x1000` in the delay slot), and with s1/s2 pinned the only free
//    callee-saved reg is $s3 -> sVar4 lands in $s3 (target's home). Semantically neutral: sVar4
//    is a local ApplyMatrixSV never reads.

typedef struct {
    u8 pad[8];
    u16 f8;   /* +8  */
    u16 fA;   /* +0xA */
} Entry12;   /* 12-byte stride; index = *(s16*)(param_1+0x70) */

extern Entry12 D_80180564[];
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80143D28(s32 param_1) {
    register s32 iVar3 __asm__("$18") = *(s32 *)(param_1 + 0x20);  /* $s2 */
    register s32 iVar2 __asm__("$17") = *(s32 *)(param_1 + 0x64);  /* $s1 */
    Entry12 *e = &D_80180564[*(s16 *)(param_1 + 0x70)];
    s16 sVar4;
    s32 iVar1;

    *(u16 *)(iVar3 + 0x14) = e->f8;
    *(u16 *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + e->fA;
    sVar4 = 0x1000;   /* placed pre-call to force sVar4's callee-saved ($s3) home */
    ApplyMatrixSV((void *)(*(s32 *)(param_1 + 0x20) + 0x34), (void *)e, (void *)(param_1 + 0x50));

    if (*(s16 *)(param_1 + 0xfe) == 0 &&
        (iVar2 == 0 || *(s16 *)(iVar2 + 0x36) != *(s16 *)(param_1 + 0xfc) ||
         *(u8 *)(iVar2 + 0xc1) != 6)) {
        if (0x10 < *(s32 *)(param_1 + 0x1c)) {
            *(s32 *)(param_1 + 0x1c) = 0x10;
        }
        *(s16 *)(param_1 + 0xfe) = 1;
    }
    iVar1 = *(s32 *)(param_1 + 0x1c);
    if (iVar1 < 0x11) sVar4 = iVar1 << 8;
    if (0x73 < iVar1) sVar4 = (0x78 - iVar1) * 0x400;
    *(s16 *)(iVar3 + 0x1c) = sVar4;
    *(s16 *)(iVar3 + 0x1a) = sVar4;
    *(s16 *)(iVar3 + 0x18) = sVar4;
    if (func_8012BEE8(param_1) != 0) func_8012C218((void *)param_1);
}
