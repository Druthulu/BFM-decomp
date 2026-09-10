# func_80135A4C (src/ov_SC04_011/ov_SC04_011_jr_80135A4C.c): T7 agent c10, S103

**Final score 0** (from 40; the mechanical search's best was 24). `mine 181 ins, target 181`. The candidate's
`objdump -drz` of the function (words and relocations) is identical to the tree object's (`scratch/f2.dis` /
`scratch/last.dis` vs `scratch/target.dis`). The whole scratch object also matches the tree object: the md5 of the
full `objdump -drz` and of `.rodata` are equal. It scored 0 on three repeated `--try` runs. The text is `PACK/body.c`. It has
no register pin, no `asm`, no added `volatile`, no zero term and no `__builtin`. The coordinator still has to run the
whole-object gate.

## (a) The residual in one sentence

This was a COUNT residual (171 vs 181), and one of its defects moved the registers. **Nine instructions were missing**
because the second `func_80135EB0` list probe (`move a0,s0; jal; li a1; beqz v0; nop`) and the second copy of the
walk step (`lw s0,0(s0); nop; bnez s0; move a0,s0; j; move v0,zero`) had been merged into the first probe; mine has a
single `j d4` back into it instead. **One more was missing**: `move a0,v0`, the copy of the `z == z` store-flag result into
`eq`. Separately, the callee-saved order of the three long-lived values was wrong: a0's copy, a3's copy and `base`
(the tree's `s7`) sat in `s6/s7/s5` where the target has `s5/s6/s7`.

## (b) The passes and the decisions

1. **The merged probe is the post-reload cross-jump.** It runs in `jump_optimize (insns, 1, 1, 0)` at `toplev.c:3142`.
   Proven by counting `func_80135EB0` call_insns per dump in `scratch/dumps_free/`: there are **2** in every dump
   through `.sched2` and **1** in `.jump2`. So the merge happens after allocation and scheduling, in jump2. The matching
   is `find_cross_jump` (`jump.c:2371`), called from the "other jumps to this label" loop for unconditional jumps
   (`jump.c:1978-1990`, which walks `jump_chain`). The conditional form (`jump.c:1921-1960`) uses `jump_back_p`
   (`jump.c:2635`). In the jump2 dump the second probe's branch is rewritten as `(set (pc) (label_ref 504))` with
   `INSN_CODE -1`, and 504 is a new label in front of the first probe. That is the conditional-cross-jump rewrite
   (`jump.c:1945-1950`).
   **Why the free text merges and the final one does not (proven on the `.sched2` dumps, the input to jump2).** In the
   free text, both exits from the walk are a `return 0` of their own. Each expands to `v0 = 0; j <ret>`, so both walk
   steps enter jump2 as `p = *p; bnez p → loop; v0 = 0; j ret`. jump2 merges each `v0 = 0` into the function's final
   `return 0`, which leaves two identical tails, `p = *p; bnez p → loop; j L`. It merges those, and then the probe in
   front of them. In the final text, the walk **falls out to the function's single final `return 0`** (through the
   `else`). The `for (p = *p; p != 0; p = *p)` exit test is rotated to the bottom (`stmt.c:2253-2330`,
   `expand_end_loop`) and a copy is placed in front of the loop (`jump.c:2131`, `duplicate_loop_exit_test`, which is
   allowed here because the test holds no call). So before jump2 the first exit is already a bare
   `beqz s0 → L_ret` (`dumps_f2`, `.sched2` insn 454), while the loop's exit is `bnez s0 → top; j L_ret` (insns
   149/201). The two tails have different shapes, `find_cross_jump` stops at the first insn (a JUMP_INSN against an
   INSN), and nothing merges. The dumps prove these pre-jump2 shapes. **I did not trace jump2 insn by insn:** in one
   diagnostic (`scratch/v/diag1.c`, the free walk with a short tail borrowed from func_80135888) the free walk did NOT
   merge either. My reading of the order of jump.c's rewrites predicts that it should, so that corner is not
   explained.
2. **The missing `move a0,v0` is the cse SUBREG gate, the same one S103 c4 read.** With `s16 eq`, the `&&` chain
   stores its last compare (`xor; sltiu` into an SImode temporary, r172) into eq with
   `(set (reg/v:HI 81) (subreg:HI (reg:SI 172) 0))` (`dumps_r3/fn.cse` insn 457). The source is a SUBREG, so the
   `(set REG0 REG1)` fold (`cse.c:7440-7474`, gate `:7455`) does not retarget the `sltiu`, and the copy survives as
   `move a0,v0`. The loop test's `(sign_extend:SI eq)` (cse insns 315/316) comes out of the loop as a copy,
   `(set (reg:SI 132) (subreg:SI (reg/v:HI 81) 0))`, which is combine insn 464, before `NOTE_INSN_LOOP_BEG`, and
   becomes `move s3,a0`. So the target's `sltiu v0; move a0,v0; move s3,a0` is exactly that. I read the hoist as loop.c's
   invariant motion and the loss of `sll/sra` as combine's `nonzero_bits` (eq is 0/1). I did not open loop.c or
   combine.c for this, so that part is inferred from the dumps. In the free text `s32 t = zt` is a same-mode SI copy,
   and cse folds it, which puts `sltiu a0` directly into t.
3. **The register order is `global.c` `allocno_compare` (`:596-610`, priority = `floor_log2(refs)*refs/live*10000`,
   ties to the lower allocno).** With the first two moves in place (`dumps_e8`, score 19), the order line ends
   `... 78 77 72 75`: base r77 has 6 refs over 101 = **1188.1**, a0 r72 has 6/103 = **1165.0**, a3 r75 has
   6/104 = **1153.8**. So base took `s5`, a0 took `s6` and a3 took `s7`. The target needs 72 > 75 > 77.
   **The fix passes the function's own parameters through to `func_80135480`**. The tree's text called it through
   `(s32 (*)(void))`, with no arguments. The call then carries `(set a0 r72) … (set a3 r75)` (visible in `.greg`), so at
   global-alloc time r72 and r75 each gain a reference: a0 has 7/107 = **1308.4**, a3 has 7/108 = **1296.3**, and
   base has 6/105 = **1142.9**. The order line ends `... 78 72 75 77`, giving s4/s5/s6/s7 = flag/a0/a3/base, which is
   the target (`dumps_f2`, `alloc_table.py f2`). **These moves cost zero bytes.** The post-reload jump pass deletes a
   register copy whose destination already holds the value (`jump.c:425-462`, `find_equiv_reg`). `a0` still holds
   the incoming argument that `move s5,a0` just copied, so `move a0,s5` goes away. The `.sched2` dump has 6
   `(set (reg:SI 4 a0)` and `.jump2` has 5. The arguments exist for the allocator and are gone in the bytes. The cast to
   `s32 (*)(void *, s32, s16 *, s16 *)` stays because the declared `s16` return would add `sll/sra` on the switch value
   (`scratch/v/f1.c`, score 9). It is the exact spelling the sibling func_80135888 uses (see (f)).

## (c) The source moves (one line each, from `body_free.c`)

1. **List walk:** `if (EB0(p) != 0) goto docall; for (p = *p; p != 0; p = *p) { if (EB0(p) != 0) { docall: …; return 1; } }`
   ends with no `return 0` of its own. The a1 ≥ 0 path moves into the `else`, and both fall to the function's one final
   `return 0`. (A `p = *p; if (p != 0) do { … } while (p != 0);` spelling also scores 0: `scratch/v/s_do.c`.)
2. **`s16 eq` and `eq = a2->x == a3->x && a2->y == a3->y && a2->z == a3->z;`** replace the `t`/`zt` block.
3. **Pass the parameters to the dispatcher:** `((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)((void *)a0, a1, (s16 *)a2, (s16 *)a3)`.

Readability, each re-proved at 0: `goto out` becomes `break`, and the `old = i; i = i + 1` block becomes
`if (i++ >= 5) return 0;` (`r1`). `acc = 0` moves into the `else` (`r2`). `s7` is renamed `base`, the sibling's name
(`r3` = `body.c`).

Scores for each move (byte-measured, `scratch/v/`): args alone 40 → 21 (`s_args`), walk alone 40 → 27 (`v1f`),
eq alone 40 → 36 (`s_eq`). Walk + eq: 19 (`e8`). Walk + args: 8 (`s_walkargs`). All three: **0**. With move 1
in place, eq variants: `s32 eq` with the `&&` chain scores 54 (`e1`; with an SI destination the chain expands
differently), `s16 t` inside the old block scores 19 (`e4`), `u8 t` scores 20 (`e5`), and `s16/u16 zt` score 27 (`e2/e3`,
because the copy that has to survive is t's, not zt's).

## (d) Generator proposals

- **R-args-passthrough:** use this when a register residual swaps callee-saved holders, one of the losing allocnos is
  an incoming parameter, and the function calls a callee whose declared prototype takes (some of) the caller's own
  parameters in the same argument registers, but the text calls it with fewer or none (a `(T (*)(void))` cast).
  Pass the parameters through. Each adds one ref to the parameter's pseudo at global-alloc time, and jump2's
  `find_equiv_reg` deletes the moves (`jump.c:425-462`), so it costs zero bytes. Check it by arithmetic first:
  the new priority is `floor_log2(refs+1)*(refs+1)/live'`.
- **R-shared-return:** use this when a COUNT residual shows the target with a peeled first probe plus a second copy of
  the loop step, and mine has a `j` back into the first probe. Stop giving the loop's exits their own `return K`:
  let them fall out (if/else) to the function's final `return K`, and write the walk as a `for` loop whose step is also
  its init. The first exit then reaches jump2 already as a bare branch to the shared return label, so no tail matches.
  Test: `func_80135EB0`-style call count per dump (2 through sched2 and 1 at jump2 means cross-jump).
- **R20 for `&&` values:** use this when the target keeps `sltiu vX; move aY,vX` for a boolean built from an `&&`/`if`
  chain. Declare the destination `s16` (not `s32`, and not the inner temporary) and assign the whole `&&` expression.

## (e) What did not work (byte evidence, `scratch/v/`)

- `a1.c`: the sibling's walk (`if (EB0) goto docall; p = *p; if (!p) return 0; do {…} while (p); return 0;`) with
  this function's tail scores 40, still merged. The walk's own `return 0` is the defect, not the loop form.
- `diag0.c`: `-0x8000` → `0` (the sibling's argument), still merged. The constant is not the difference.
- `t1.c`: giving the out-path its own `func_80136A94(...); return 1;` scores 60. Both merges still happen.
- `f1.c`: passing the args through the declared `s16` prototype scores 9, from the extra `sll/sra` on the switch value.
- `s_noeq.c`: the final text with `s32 eq` scores 54.

## (f) Where the method fell short

- **neighbours.txt was empty** (this function's own header is a carried-decl marker). The answer was in a
  **different TU file**: `src/ov_SC04_011/ov_SC04_011_jr_80135888.c` func_80135888, closed today. It has the same
  switch, the same `base = p0 + 0x34`, the same list walk with `goto hit` into a do-while, and the pass-through
  `((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)(arg0, arg1, arg2, arg3)` call. The brief says "grep the TU
  for a global your body touches", but here the sibling sits in another file. **Suggest: `neighbours.txt` should
  include lever-free bodies in ANY file of the same overlay that call the same callee** (`grep -l func_80135EB0
  src/<overlay>/*.c`). That grep, not the residual, is what pointed at the args move.
- The pass-through args are invisible in the bytes (jump2 deletes them), so neither the residual nor the target
  disassembly can show them. A sibling's text or the alloc-table arithmetic is the only way in. **The alloc table plus
  "what adds a ref at zero byte cost" (S103 c5/c6 named the loop-depth weighting and cross-jumped duplicates) should
  also list "arguments passed in the register that already holds them".**
- METHOD step 3's cross-jump bullet offers the `extern alias __asm__("SYM")` escape for cross-jump merges. Here the
  real fix was a control-flow spelling (the shared return), and the alias was never needed. I would list "does each
  merged exit return on its own? let it fall to the function's return" before the alias.
- Tooling: my `scratch/dump.sh` needs `-dR` for `.sched2` (without it the pre-jump2 state is not dumped). The first
  version of my `t.sh` resolved a relative candidate path from the repo root, and one diagnostic was mis-scored
  before I noticed. It now takes `realpath`.

## Paths

- `PACK/body.c`: the score-0 text (= `scratch/v/r3.c`).
- `PACK/mechanism.md`: this file.
- `PACK/scratch/`: `t.sh` (score + candidate disassembly), `dump.sh` (cc1 dumps of the last `--try` TU), `v/`
  (every candidate), `dumps_{free,a1,d1,e8,f2,r3,sib}/`, `target.dis`, `free.dis`, `f2.dis`.
