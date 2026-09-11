# func_801852E4 (ov_SC06_022, 5 copies): closed lever-free — `goto out` + a result variable (agent c32, S103)

**Result: score 0, no pin, `--body` only. Whole object byte-identical to the baseline** (`objdump -drs` diff empty,
symbols identical apart from the scratch FILE path).

## (a) The residual
Lever-free: 52 vs 52, one branch target wrong. After `r = func_80187460(...)`, mine has `beqz v0,<ret0 block>`
(`j epi; move v0,zero`), the target has `beqz v0,<epilogue>`. The target sets nothing in `$v0` on that path, because
the call already left 0 there. So the path's return value is the call result itself: a `$2 = r` copy that reload
turns into a self-copy and deletes. Mine returns the constant 0 instead, and cross-jump merges that into the ret0
block.

## (b) The pass and the decision (proved on bytes and dumps)
- **cse1, not cse2** (the tree header says cse2; `.cse` already shows it): `if (r == 0) return r;` compiles to
  "jump if r != 0", and the fall-through records `r == 0` — `record_jump_equiv (insn, 0)`, cse.c:7508-7511.
  `return r` sits in that same extended block, so its `(set (reg 2) (reg 73))` folds to
  `(set (reg 2) (const_int 0))` — the lever-free `.cse` insn 101 has `REG_EQUAL 0`. That becomes `$2=0; j epi`, which
  cross-jump merges with ret0's identical block.
- The fix makes the r==0 edge a TAKEN jump to a label that cse won't follow. `cse_end_of_basic_block` follows a
  conditional jump only when the label has `LABEL_NUSES == 1` AND a BARRIER before it (cse.c:8106-8116), and only a
  followed path gets `record_jump_equiv (insn, 1)` (cse.c:8448). The label `out:` has two users — the jump, plus the
  fall-through from the store block — and no barrier, so cse starts a fresh block there and `$2 = r` survives
  (`scratch/dumps_f1/f1.i.cse`: `(insn 159 (set (reg/i:SI 2 v0) (reg/v:SI 73)))` right after `code_label "out"`).
  `r` dies straight into `$2` on both paths, so it's allocated `$v0`, the copy becomes a self-copy, and jump sends
  the `beqz` straight to the epilogue.

## (c) The move (JOINT — neither half alone)
```c
    r = func_80187460(p, 0x380);
    if (r == 0) {
        goto out;
    }
    ...
ret0:
    return 0;
store:
    *(u16 *)(p + 2) = 0xC;
    r = 1;
out:
    return r;
```
i.e. `return r` becomes `goto out`, and the store arm's `return 1` becomes `r = 1;` falling into the shared `out: return r;`.
`r = 1` is the function's return value, not a dead or do-nothing assignment. It gives `out` its second user,
which is what stops cse following the jump. `goto out` alone, with `return 1` kept in the store arm, scores 8
(`scratch/f1n.c`): `out` then has one user and a barrier, cse follows it, the fold comes back, and the layout
shifts too. The structured `if (r != 0) { ...; r = 1; } return r;` scores 7 (`scratch/f2.c`) — ret0 ends up after
the store and the branch polarity flips. The tree's own label order (ret0 BEFORE store) still has to hold.

Transfer checked on a sibling: the same textual edit on `ov_SC06_024` `func_801877BC` (symbols remapped)
scores 0 (`scratch/sib024.c`). The other copies are in ov_SC06_018/020/032/033, found by grepping the header's
`/* $v0 — see note 2 above */` pin comment. The tree's header notes 2 and 1 should be rewritten to match this reading.

## (d) GENERATOR PROPOSAL
When the target branches on a call result straight to the epilogue with no `$v0` set in the delay slot, and the
lever-free `return r` inside `if (r == 0)` jumps to a shared `return 0` block instead: turn the arm into
`goto out;`, and route one other return path whose value is not a constant-equal-to-the-test (here `return 1`) into
`r = <value>; out: return r;`. The label needs two users so cse (cse.c:8106) won't follow the jump and
record_jump_equiv can't fold `r` to the tested constant. General form: **a pinned-`$2` "return r" whose value the
branch just tested = give the return point a second predecessor.**

## (e) Tried and rejected (bytes)
- `goto out` with `return 1` kept in the store arm: score 8 (above).
- Structured `if (r != 0) {...}`: score 7 (above).
- The mechanical search (history.txt): decl moves, blocks, do-while — all stayed at 1. None of them touches the
  label's use count, and that's the actual variable.

## (f) Where the method fell short
- The header note was right about the symptom and wrong about the pass (cse2 vs cse1). METHOD's "a `@stuck:`
  note is a CLAIM" applies to the mechanism lines inside `/* */` headers too.
- `residual_moves.md` has no row for "a return value folded to the tested constant by record_jump_equiv". It
  should: the lever that fakes it is always a `$2` pin on a call result that gets tested against 0 and returned.
  Grepping the tree for `register s32 \w+ __asm__("$2")` next to `if (\w+ == 0) {\s*return \w+;` would size the
  family.
