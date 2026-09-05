/* func_8017DF28 (ov_SC06_022, 119 ins) — NEAR/2, SCHEDULE-REORDER.
 *
 * Residual (the only one, byte-measured): the `addiu $s2,$sp,0x10` that
 * materialises &mtx.  The target parks it in the `bnez` delay slot (idx 28);
 * every draft parks it in the `jal func_8012C1B8` delay slot (idx 25).
 *
 * Cause (read out of `cc1 -da`, not inferred — S71 attempts 1-3): the insn is
 * NOT `mptr = &mtx`.  It is the DESTINATION address pseudo that mips.c
 * `expand_block_move` (`copy_addr_to_reg`) mints for the BLKmode copy
 * `mtx = D_800AE620;` — RTL insn 11, at the very top of the function.  cse
 * folds that pseudo back into the movstr's MEMs (giving the sp-relative
 * lw/sw pairs) and then re-uses the *register* for both later `&mtx` call
 * arguments (.cse dump: insn 144/153 `a1/a0 = reg75` + REG_EQUAL
 * `(plus $fp 16)`), deleting mptr's own address insn.  The surviving def
 * therefore lives ABOVE the call; sched1 sinks it only as far as the call
 * (a CALL_INSN blocks it) and reorg then fills the jal's own delay slot with
 * it.  The target's def is BELOW the call, so gas hands it to the `bnez`
 * instead.
 *
 * Levers tried, all byte-measured, none reach it (statement placement is
 * INERT here — the insn is compiler-minted, not source-placed):
 *   mptr before/after the call, after the if, absent entirely (&mtx inline) .. 2
 *   `Blk20 mtx = D_800AE620;` initialiser form ............................. 2
 *   `register ... __asm__("$18")` pin on the pointer (§17) ................. 2
 *   §194-K non-volatile re-tie on the pointer ......................... 120/121
 *   §153 volatile address launder after the call ...................... 120 (+1
 *        `move $s2,$v0`: cse had already substituted, the launder only copies)
 *   §5a `__asm__ __volatile__("")` fence before the call ............... 120 (+1:
 *        reorg is stopped, but the addiu is still ABOVE the jal)
 *   §194-K re-tie on a helper pointer used as the copy destination ..... 119/75
 *        (kills the reuse, but also un-folds the copy to `0($2)` bases)
 *   word-wise copy instead of the struct assign ....................... 124/121
 *        (loses the shared `$a1` base: one lui+lw per word)
 *   copy moved below the call ......................................... 118/114
 *
 * S79 addendum — re-read `docs/gcc-2.7.2-map/cse_expr.md` [A23-2]/§H for the
 * two remedies it names for this exact `expand_block_move` copy_addr_to_reg
 * class, neither of which is in the list above, and tried both:
 *   (a) field-by-field / per-word spelling of `mtx = D_800AE620;` (a `for`
 *       loop over `Blk20.w[8]`, avoiding expand_block_move entirely) —
 *       CONFIRMED REGRESSIVE, closeness 117 (nins 111, LENGTH-DRIFT): gcc
 *       keeps it a genuine loop (strength-reduction never unrolls it back to
 *       the target's straight-line 3-load/3-store groups), destroying the
 *       already-matching block-move sequence itself (cookbook §32 point 4 /
 *       §179-E: any scalar per-element form is the WRONG shape for a
 *       block-move-sized aggregate copy — this is the SAME finding as the
 *       already-tried "word-wise copy" line above, now with the RTL-level
 *       reason nailed down: no legal C rewrite of this 32-byte copy avoids
 *       expand_block_move without also changing the bytes that already
 *       match).
 *   (b) §H's "balanced if/else diamond" cse-reset antidote — wrap the `mptr
 *       = &mtx` statement in `if (obj & 1) { mptr = &mtx; } else { mptr =
 *       &mtx; }` so the merge label is a genuine 2-predecessor join, which
 *       §H reports defeats cse's `follow_jumps`/`skip_blocks` table carry
 *       and forces a fresh definition — MEASURED NO-OP: closeness held at
 *       exactly 2, byte-identical residual (idx 25/28 unchanged). The
 *       identical-body diamond does not survive to reach cse as a genuine
 *       join here (most likely jump.c's cross-jump tail-merge — the same
 *       mechanism documented at §5a — collapses the two identical arms
 *       before the class-reset condition can apply, or the dead `obj & 1`
 *       test is removed first). This function's real control flow (a single
 *       early-return guard, no natural fall-through diamond before the
 *       protected statement) gives no non-destructive way to manufacture the
 *       2-predecessor merge §H's antidote requires.
 *
 * Reaching the target needs the `(plus $fp 16)` equivalence class to be
 * EMPTY after the call, and cse seeds it from the block move that must
 * precede it. Both documented cookbook remedies for this exact mechanism are
 * now byte-tested and inert/regressive on this function — genuine
 * gcc-2.7.2 delay-slot-fill wall, not reachable from C source. Route to
 * permuter (SCHEDULE-REORDER/2) or accept as a wall.
 */

#ifndef BFM_ENGINE_TYPES_H   /* standalone (match_one) only; inert in the TU */
typedef struct { s32 w[8]; } Blk20;
#endif

extern Blk20 D_800AE620;
extern s32 D_801AAD00[];
extern s32 D_801AAD08[];
extern void func_8012C1B8(void);
extern void func_8012C218(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

typedef struct { s16 h0, h1, h2, h3; } Q_8017DF28;   /* 8 bytes, align 2 -> lwl/lwr copy */
typedef struct { s32 x, y, z; } VEC_8017DF28;

void func_8017DF28(s32 param_1)
{
    Blk20 mtx;              /* sp+0x10 */
    VEC_8017DF28 pos;       /* sp+0x30 */
    VEC_8017DF28 *mptr;
    s32 obj;

    mtx = D_800AE620;

    obj = ((s32 (*)(void))func_8012C1B8)();
    mptr = (VEC_8017DF28 *)&mtx;
    if (obj == 0) {
        func_8012C218((void *)param_1);
        return;
    }

    func_8001C214(obj, (s32)D_801AAD08);

    *(Q_8017DF28 *)(obj + 0x08) = *(Q_8017DF28 *)(*(s32 *)(param_1 + 0x20) + 0x08);
    *(Q_8017DF28 *)(obj + 0x10) = *(Q_8017DF28 *)(*(s32 *)(param_1 + 0x20) + 0x10);
    *(Q_8017DF28 *)(obj + 0x18) = *(Q_8017DF28 *)(*(s32 *)(param_1 + 0x20) + 0x18);
    *(s32 *)(obj + 0x04) = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x04);
    *(u16 *)(obj + 0x2C) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C);

    *(s32 *)(param_1 + 0xCC) = obj;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x24) = (s32)D_801AAD00;
    *(s32 *)(param_1 + 0x48) = 0xC000;

    *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0xB0;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0x62);
    func_8012B2CC(param_1);

    *(u16 *)(param_1 + 0xAE) = 0x2000;

    pos.y = -0xC0000;
    pos.x = 0;
    pos.z = -0x80000;

    RotMatrixY(*(s16 *)(param_1 + 0x62), mptr);
    func_800484EC((s32)mptr, (s32)&pos, param_1 + 0x10);

    func_8002D4C8(0x955, 0);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}
