# func_80180E24 (ov_SC06_016, src/ov_SC06_016/ov_SC06_016_jr_8017C8D0.c) — e24, P36 S104

**Final: score 0, ZERO levers** (the tree's `__asm__ __volatile__("")` fence after the `sh` pair removed). `body.c` =
scratch/q_B.c. ONE move: the `+0x1A`/`+0x18` store pair that followed the `if (t < 4) … else …` is written INSIDE
EACH ARM (`= v0` in the ramp arm, `= 0x2800` literally in the other); the join block starts at the call.
(scratch/q_A.c, keeping `v0 = 0x2800;` in the else arm, also scores 0; writing the else arm without `p`, q_C.c, is 12.)

NOTE: `body_free.c` in the pack does not compile (the lever strip removed the `__asm__` line that opened the
multi-line `/* §194-A … */` comment and left its continuation lines) — the pack's residual is a COMPILE-ERROR and
history's search is UNSCORED. scratch/base.c is the corrected lever-free text: score 6 (ORDER, 81 vs 81 ins).

(a) Residual (base.c): in the block after the if/else, mine schedules the call's argument setup
(`move a0,s2; lui/addiu a1; addiu a2,sp,16`) ABOVE the `sh v0,26(v1)`, and reorg fills the `jal` slot with the second
`sh`; the target emits the two `sh` FIRST, then the arguments, with `addiu a2` in the slot.

(b) Mechanism (pass order `toplev.c:3033` sched1 → `:3117` sched2 → `:3142` jump2 with cross-jump → `:3167` dbr):
- with the pair in the join block, sched1/sched2 see one block `sh; sh; <arg setup>; call` and the list scheduler
  (`rank_for_schedule`, sched.c) ranks the call-feeding argument insns higher (the tree's own §190-C note), so they are
  placed above the stores. The `__asm__` fence split that block.
- the original had the pair in each arm, so during both scheduling passes the stores sit in the ARM blocks and the
  join block holds only the call sequence. After sched2, `find_cross_jump` (`jump.c:2371`) matches the two arms'
  identical tails backward — `sh v0,26(v1); sh v0,24(v1)` — (it stops at `sll v0,v0,9` vs `li v0,10240`) and moves the
  join label above the else arm's pair, deleting the ramp arm's copy: the target's single pair at the head of the
  join block, followed by the unscheduled-across call setup.
- Proved on bytes (0) and on the dumps (scratch/dumps_qB): the `.sched2` dump still has the HImode `+0x1A/+0x18`
  store pair in BOTH arms; `.jump2` has one pair fewer (the ramp arm's copy deleted by cross-jump).

(c) The move above.

(d) GENERATOR PROPOSAL (new family, also closes func_8017E54C in this TU and two siblings, see below): when a
residual is ORDER/COUNT on statements that IMMEDIATELY FOLLOW an if/else join (a barrier/`do-while` lever sits right
after them in the tree), duplicate those statements into the end of BOTH arms (substituting each arm's value for the
temp) — cross-jump re-merges the identical tails after scheduling/cse, so the bytes keep one copy but the passes saw
two blocks.

(e) Other attempts: none needed beyond q_A/q_B/q_C. The history is UNSCORED (the broken body_free.c).

(f) Method note: the pack's starting text was invalid C — the lever stripper should delete a whole multi-line comment
that begins on the lever's line. The broken pack meant the sweep never ran on this function.

(g) Structs: no. The decision is block structure against the scheduler (which block the stores live in during sched),
not an aliasing decision; the `p` object type would not move the argument setup.

## Copies closed with the same text (scratch/copies_closed.txt) — both --try 0 with the lever removed
1. func_80181998 — src/ov_SC06_016/ov_SC06_016_jr_801816DC.c:3082 (marked `// !FAKE: do-while` LOOP-note barrier):
   scratch/sib_80181998.c (pair inside each arm, `v` / `0x3800`).
2. func_80185B70 — src/ov_SC04_005/ov_SC04_005_jr_8017BEBC.c:9284 (an UNMARKED `do { … } while (0)` — the lever the
   §190-C comment above its call describes): scratch/sib2_a.c (the `+0x1A`/`+0x18` stores inside each arm).
