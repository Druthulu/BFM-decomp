# func_80186A8C (ov_SC03_091_jr_8018326C.c) — T7 agent c42 — score 8 -> 0, both `$5` pins gone

## (a) The residual in one sentence
Same 230 instructions; at both `func_8012B178(a0, t - 0x4000)` sites the target emits `addiu a1,v0,-0x4000 / jal / move a0,s0`
(a1 set FIRST, the a0 copy in the delay slot) and the lever-free text emitted `move a0,s0 / jal / addiu a1,v0,-0x4000`.
COUNT: 230 = 230, nothing missing — a pure ORDER residual of two insns, twice.

## (b) The passes and decisions (read, then proven on dumps `scratch/dumps_free`, `scratch/dumps_v1`)
* `calls.c:1860-1881` (gcc-2.7.2): MIPS has no `PUSH_ROUNDING`, so `PUSH_ARGS_REVERSED` is NOT defined (`calls.c:38-44`); the
  hard-register loads are emitted in argument order, `$4 = a0` then `$5 = value` (dumps_free `fn.rtl` insns 163, 165).
* combine (`can_combine_p`, `combine.c:880-930`): the separate `av = t - 0x4000` insn (160) is folded into the `$5 = av`
  arg-move (165), which sits AFTER `$4 = a0` — so the subtract becomes the last insn before the call (dumps_free `fn.combine`).
* sched1 keeps the order: every priority is 1 (`sched.c:1480-1488`, latency-1 insns) and `rank_for_schedule` ties by LUID
  (`sched.c:2428`). reorg then fills the `jal` slot with the LAST insn — the addiu. That is the 8.
* The pin made the subtract a body insn writing `$5` before `$4 = a0` (and the `$5=$5` copy died) — so `move a0` was last.

## (c) The move that closed it (8 -> 0, byte-proven)
Fold the `- 0x4000` into BOTH arms of the sign pick and pass `t` itself (both case 0 and case 1):

    if (ang >= 0) {
        t = -(ang << 4) - 0x4000;
    } else {
        t = (ang << 4) - 0x4000;
    }
    func_8012B178(a0, t);

Why it works (every step read on the dumps of the matching compile, `scratch/dumps_v1`):
1. `t` is now SET in two blocks and read in the join, so it is block-global -> global.c allocates it. The join's copy
   `$5 = t` gives it the copy preference `$5` (`fn.greg`: `;; 120 preferences: 2 5`, conflicts `72 120 4 29` — `$5` free),
   so `t` = `$a1` and the arg copy becomes `$5 = $5` (deleted). Each arm ends `addiu a1,v0,-16384` (greg insns 148, 157).
2. The post-reload jump pass cross-jumps the two identical arm tails (`toplev.c:3142`, `find_cross_jump` `jump.c:2371`):
   `fn.jump2` shows arm A's `jump_insn 150` retargeted to the new `code_label 683` in front of arm B's insn 157, arm A's
   copy of the addiu deleted. The join is now `addiu a1 / move a0,s0 / jal` — the target's order.
3. reorg fills the `jal` delay slot with `move a0,s0` (the last insn); in case 0 it also steals the shared `sll v0,s1,4`
   into the `bltz` slot from both threads, in case 1 that slot already holds the `sh`, exactly as the target.
Score 0 on `--try` (`body.c`). No pin, no asm, no volatile, no invented term, no dead assignment; `av` and its block are gone.

## (d) GENERATOR PROPOSAL
When the residual is "`addiu aN,vX,K / jal / move a0,sM` (target) vs `move a0,sM / jal / addiu aN,vX,K` (mine)" and the
argument is `x - K` / `x + K` where `x` is set on both arms of an if/else (or ternary), distribute the constant into every
arm's assignment and pass the variable bare: the variable becomes block-global, takes the argument register from global.c's
copy preference, and jump2's cross-jump re-merges the per-arm adds into one join insn that precedes the other arg moves.
(Generalises: any "arg-value pin on `$aN` whose value is an arithmetic tail of a join" — move the tail into the arms.)

## (e) What did NOT work (byte evidence)
* `t -= 0x4000;` at the join then `func(a0, t)` (scratch/v3.c): 8 — combine still folds the subtract into the arg-move
  (the tree header's item 3 already recorded that hoisting to a statement does not help).
* `t = -(ang << 4); t -= 0x4000;` inside each arm (scratch/v2.c): 17, COUNT 232 vs 230 (two extra insns; cause not
  dumped — not needed once v1 closed; unproven).
* The mechanical search (history.txt: 894 compiles, R7 block / R8 temp / R10 param-copy / do-while) never reaches this:
  none of its moves distributes an expression into the arms of a preceding if/else.

## (f) Where the method fell short
* Arity check done first as instructed: `func_8012B178` is `void (s32, s32)` (src/shared/ov/func_8012B178.h) and the
  call passes 2; no `jal` reads `$a1` implicitly (`func_8012CBA4` follows, `$a1` is dead after the B178 call). Not this class.
* The METHOD's cross-jump entries (c6/c10) are phrased as "cross-jump merges things the target keeps apart" or "re-merges a
  shared call"; this is a third use — cross-jump as the TOOL that produces the target's join insn from per-arm copies, in
  service of an argument-register order. Worth a line in METHOD.
* The TU header of func_80186A8C (TU:5114-5125, item 3) claims the pin is required; it is refuted by this body and should be
  rewritten when the bank lands (outside this agent's write scope).

Paths: body `.run/P36/agents/ov_SC03_091__func_80186A8C/body.c`; dumps `scratch/dumps_free/`, `scratch/dumps_v1/`.
