# func_8015FBE0 (ov_MAIN_012_jr_8015A3C8.c) — T7 agent c37 — CLOSED, score 0

## (a) The residual
Lever-free body, score 3 (COUNT, 57 vs 58): the `move a0,s0` that opens the `else` arm (target 0x5878) sits in MY `bgez`
delay slot (the branch retargeted one insn further, `j 58e8` vs `j 58ec` follows from it); the target leaves that slot a
`nop`. Nothing about registers — one insn stolen into a delay slot.

## (b) The pass and the decision
reorg (dbr), `fill_slots_from_thread` (`reorg.c:3257`): stealing the first insn of the TAKEN thread into a conditional
branch's slot is allowed only when the insn sets nothing live on the OPPOSITE (fall-through) thread —
`mark_target_live_regs (opposite_thread, &opposite_needed)` `reorg.c:3293`, test `! insn_sets_resource_p (trial,
&opposite_needed, 1)` `reorg.c:3375`.

The lever-free body calls the dispatch handler through `((void (**)())D_80180A1C)[*(u16 *)param_1]()` — NO argument —
so on the fall-through path `$a0` is dead until `move a0,s0` for func_80147078, and reorg steals the else arm's
`move a0,s0`. The `__asm__ __volatile__("")` at the head of the else arm stopped the steal (a volatile asm first in the
thread). The real source passes `param_1` to the handler (the table is DECLARED `void (*D_80180A1C[])(void *)` in this very
body, and every sibling in the TU — func_8015FF20, func_8015A3C8 — calls it `D_80180A1C[*(u16 *)p](p)`). With the argument:
- cse/greg keep `(set (reg a0) (reg 72→s0))` (insn 29, `.greg`), and jump2 DELETES it: `find_equiv_reg` sees `$a0` still
  equal to `$s0` from the prologue copy `s0 = a0` (`jump.c:437-462`, the "no-op move from fortuitous allocation" arm) —
  which is why the target's fall-through has NO `move a0,s0` before the `jalr` (proved: `.greg` has insn 29, `.jump2` does
  not);
- but the call_insn keeps `(use (reg:SI 4 a0))` in its CALL_INSN_FUNCTION_USAGE (`.jump2`, call_insn 31), so `$a0` is live
  on the fall-through thread, `reorg.c:3375` refuses the steal, and the slot stays a `nop` — the target's bytes.

Proved on bytes: `--try` score 0, 58/58, and an objdump of the candidate object (with relocations) diffed against
`.run/P36/delever/baseline/src/ov_MAIN_012/ov_MAIN_012_jr_8015A3C8.o` is identical.

## (c) The move that closed it
One line: `((void (**)())D_80180A1C)[*(u16 *)param_1]();` → `D_80180A1C[*(u16 *)param_1](param_1);`, and the barrier deleted.
(The cast was also dropping the body-local declaration's own parameter type.) First `--try`.

## (d) GENERATOR PROPOSAL
When the diff is "an insn that sets `$aN` moved into a conditional branch's delay slot (target: `nop` + the insn at the
branch target)", and the fall-through thread reaches a `jal`/`jalr` whose C call passes fewer than N-3 arguments (a cast
to `()`/`(void)`, or a table call with no arguments), pass the value the target leaves in `$aN` (the parameter copied at
entry) as that call's argument N-4 — at the declared arity — and delete the barrier (a variant of METHOD's "dropped call
argument" and c3/c12, detected by the DELAY-SLOT symptom instead of a missing move).

## (e) What did not work / was not needed
Nothing else tried; the mechanical search (history.txt: blocks, do-whiles, temps, 1,295 compiles) could not reach it
because none of its moves changes a call's argument list.

## (f) Where the method fell short
Not at all — METHOD_S103 §3 bullets 1 and c3/c12 name this exactly. What would have made it instant: the pack's
`related.txt` showed func_8015FF20 calling `D_80180A1C[*(u16 *)param_1](param_1)`; a pack-builder check that diffs the
argument count of the same callee/table between the body and its related siblings would flag it before any agent reads it.
