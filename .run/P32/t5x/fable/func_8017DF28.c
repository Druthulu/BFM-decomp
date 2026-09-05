/* func_8017DF28 (ov_SC06_022, 119 ins) — MATCH (match_one + rtu_match, S83 Fable, 2026-09-05).
 *
 * The 2-insn residual of every prior draft (`addiu $s2,$sp,0x10` in the jal's
 * delay slot vs the target's `bnez` slot) was NOT a cse / expand_block_move /
 * reorg wall.  It was sched1's REGISTER-BIRTH priority boost applied to the
 * call insn, and the trigger was the number of $v0 SETS in the function:
 *
 *   * sched.c:2469 birthing_insn_p — a SET of a live register with
 *     reg_n_sets[reg] == 1 is "birthing"; adjust_priority (sched.c:2507) then
 *     lifts its priority to max_priority (the 0x7f000001 entries in the
 *     `-dS` ready lists).  regclass.c:1791 reg_scan counts reg_n_sets for HARD
 *     regs too, so a function whose ONLY value-returning call is
 *     `obj = func_8012C1B8()` has reg_n_sets[$v0] == 1 and that call_insn's
 *     `(set (reg v0) (call ...))` is birthing.
 *   * The block-move destination pseudo P = fp+16 (mips.c:2350 copy_addr_to_reg;
 *     cse later re-uses it for both `&mtx` args — that part of the prior
 *     analysis was right, and is NOT the lever) is also birthing.  sched1 is a
 *     BACKWARD list scheduler; at T-3 the ready list is {P-def, call}: both at
 *     max priority → rank_for_schedule falls to the LUID tie-break
 *     (sched.c:2428) → the LATER insn (the call) is scheduled first = placed
 *     later → P-def lands ABOVE the jal.  reorg's backward search for the jal
 *     (set/needed built with include_delayed_effects=0) then takes it.
 *   * With ANY second $v0 set in the function the call's priority is the plain
 *     1 (as in the banked same-TU twin func_80180700, which has 3 $v0 sets and
 *     whose addiu sits in its beqz slot for exactly this reason): P-def wins
 *     the ready list, is placed right AFTER the call, and reorg's FORWARD search
 *     for the jal rejects it because mark_set_resources (reorg.c:542) marks
 *     every call_used reg — $sp INCLUDED (no `!fixed_regs` filter) — as set by
 *     the call, so an insn reading $sp cannot be pulled up into the call's
 *     slot.  The bnez's backward search takes it instead → target bytes.
 *
 * The lever is therefore: one more value-returning call.  libgte's real
 * prototype is `MATRIX *RotMatrixY(long, MATRIX *)`, so calling it through
 * its pointer-returning type is the faithful spelling; the TU's `void`
 * declaration is kept (cast at the use, §500-F).  Any of the six callees
 * cast to a value-returning type gives the same 119/119 (all measured).
 *
 * Measured inert before this (S71/S79, do not repeat): statement placement of
 * mptr, initialiser form, $18 pin, §194-K re-tie, §153 launder, §5a fence,
 * word-wise / per-field copy, copy below the call, §H diamond.
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

    /* libgte RotMatrixY returns MATRIX*: the value-returning call is the
     * second $v0 set that keeps sched1 from boosting the func_8012C1B8 call
     * (see header).  The TU declares it void, so cast at the use. */
    ((void *(*)(s32, void *))RotMatrixY)(*(s16 *)(param_1 + 0x62), mptr);
    func_800484EC((s32)mptr, (s32)&pos, param_1 + 0x10);

    func_8002D4C8(0x955, 0);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}
