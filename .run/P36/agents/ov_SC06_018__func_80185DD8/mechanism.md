# func_80185DD8 (ov_SC06_018_jr_8017C24C.c) — CLOSED, score 0, no lever (agent c40, S103)

## (a) The residual
Lever-free text: 91 ins vs 96 (counted: 5 missing). The |vecB[1]| < 0xC9 test is one value-converged abs in mine
(`bgez; negu; slti 201; bnez <ret>`, the same shape as the x test above it); the target keeps TWO compare arms:
`bltz <else>; slti 201; beqz <call>; j <ret>` and `<else>: negu; slti 201; bnez <ret>` falling into the call.

## (b) The pass and the decision (read in `tools/reference/gcc-2.7.2/jump.c`, proven in the `.rtl`/`.greg`/`.jump2` dumps)
- Source `if (z >= 0) { if (z < 0xC9) return; } else { if (-z < 0xC9) return; }` expands arm 1 as
  `beq <end-of-then>; j <ret>; <end-of-then>: j <call>`. jump.c's "jump to a jump" (jump.c:1790-1798) and
  "conditional jump over an unconditional jump" (jump.c:1737-1782) leave it as `slt 201; bne <ret>; j <call>`
  (the `.greg` dump: insns 200/201/209). Arm 2 is `neg; slt 201; bne <ret>` falling into `<call>`.
- Both arms are now `slt v0,v0,201; bne v0,<ret>` followed by reaching `<call>`. The post-reload jump pass
  (`jump_optimize (insns, 1, 1, 0)`, toplev.c:3142) cross-jumps arm 1's `j <call>` (jump.c:1969-1998,
  `find_cross_jump` jump.c:2371 compares the insns before the `j` with the insns before its label — arm 2's tail):
  arm 1's `slt; bne` are deleted and it jumps into arm 2's `slt` (the `.jump2` dump: new `code_label 251`, the
  `bge` now skipping only the `neg`). = the 91-ins text.
- The tree's `__asm__ __volatile__("" ::: "memory")` before arm 1's `return` put an insn between the `beq` and the
  `j <ret>`, so jump.c's inversion never fired (`prev_active_insn (reallabelprev) == insn` fails) and arm 1 stayed
  `beq <call>; asm; j <ret>`, which no longer equals arm 2's tail.
- **The plain-C close**: write the test in the CALL's polarity with the per-sign test as a `?:` in the jump
  context. `do_jump` of a COND_EXPR (expr.c:9124, in `do_jump` expr.c:8865) expands each arm as its own
  compare with BOTH labels: arm 1 = `slt 201; beq <call>; j <end>` directly (the `.rtl` dump: insns 200/201,
  branch to `code_label 215` = the call, jump to 223 = past it). Arm 2's `beq <call>; j <end>; <call>:` is the one
  that jump.c inverts into `bne <end>`; arm 1's branch target is no longer adjacent to its `j`, so it keeps
  `beq <call>; j <ret>`, which differs from arm 2's tail, so jump2 has nothing to cross-jump. Proven on bytes
  (score 0) and in `scratch/dumps_final/final.i.{rtl,jump2}`.

## (c) The move
Replace the nested if/else-with-returns by one condition guarding the call:
`if (x >= 0x105 || (vecB[1] >= 0 ? vecB[1] >= 0xC9 : -vecB[1] >= 0xC9)) func_8012C098((void *)a0);`
(the local `z` is no longer needed and was removed). Other byte-proven closes (score 0), for the record:
- `scratch/b3.c`: the same with `((z = vecB[1]) >= 0 ? z >= 0xC9 : -z >= 0xC9)`;
- `scratch/a1.c`: keep the nested if but write arm 1 as `if (z >= 0xC9) goto call; return;` with `call:` before the call;
- `scratch/b4.c`: `if (x < 0x105) { ...; if (?: >= 0xC9) call(); return; } call();` (two calls, cross-jump re-merges them).

## (d) Generator proposal
When the diff shows a value-converged `bgez; negu; slt K; bnez <ret>` where the target has two per-sign compare arms
(`bltz; slti K; beqz <call>; j <ret>` / `negu; slti K; bnez <ret>`), rewrite the `if (z >= 0) { if (z < K) return; }
else { if (-z < K) return; }` block as `if (... || (z >= 0 ? z >= K : -z >= K)) call();` — a `?:` in a
branch condition, in the polarity whose true label is the fall-through code, keeps each arm's compare distinct.

## (e) What did not work (byte evidence, `scratch/`)
- `b1.c` `if (z >= 0 ? z < 0xC9 : -z < 0xC9) return;` (return polarity): 7 — arm 1 becomes
  `bcc <drop-through>; j <call>`, the drop-through is `j <ret>`, jump threading gives `bne <ret>; j <call>` and
  cross-jump merges again. `b5.c` (`!(?: >= 0xC9)`) and `b7.c` (`x < 0x105 && ((z = ...) ?: <) return`): 7, same reason.
- `b2.c` (`z = vecB[1];` hoisted above the `||`): 9 — the `lh` is scheduled before the x test.
- `a2.c` (`else if` instead of else { if }): 7, identical RTL.
- The tree's comment ("9 probe variants … ternary-condition … ALL merged") is refuted for the call-polarity ternary.

## (f) Where the method fell short
The lever's comment named a "scheduling/combine barrier"; the real pass was jump.c (first-pass inversion, then the
post-reload cross-jump), visible only by diffing `.greg` against `.jump2`. METHOD_S103's cross-jump bullet (c6/c10,
"make their SHAPES differ") was the right family; the missing piece is that `do_jump`'s COND_EXPR case is a
source-level way to produce the un-inverted `beq <other>; j <ret>` shape.
