# func_80166F58 (src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c): T7 agent c25 (re-draw)

**CLOSED: score 0.** `--try ... body.c --body` printed "score 0 (OTHER; mine 69 ins, target 69) — MATCH" on two runs.
All five NEEDED levers are gone: the two pins ($20, $5) and the three SHB launders. The body has no asm, no pin, no
added volatile, no zero term and no dead assignment. `PACK/body.c` is the text to bank. The whole-object gate is still the
coordinator's job. The earlier agent's files are kept in `scratch/prev_body.c` and `scratch/prev_mechanism.md`.

## The move (one edit, made twice)

```c
    t2 = (short)param_2;
    p2 = (short)t2;          /* was: p2 = t2; */
    t3 = (short)param_3;
    p3 = (short)t3;          /* was: p3 = t3; */
    eq = (t2 == t3);         /* reads the FIRST extension, not p2/p3 */
```

The copy into the loop-lived local is written as a second `(short)` narrowing of a value that is already
short-ranged, and `eq` is computed from the first extension. The value is unchanged. What changes is which passes can
see that the copy is a copy.

Ablations (all `--try`):

| body | score |
|---|---|
| `body_free.c` / earlier best (`p2 = t2`) | 4 (67 vs 69) |
| only `p2 = (short)t2` (`scratch/c/ab1.c`) | 2 (68): one copy back |
| only `p3 = (short)t3` (`ab2.c`) | 11 (68) |
| both, but `eq = (p2 == p3)` (`ab3.c`) | 4 (67): both copies lost again |
| **both, `eq = (t2 == t3)` (`body.c` = `c/B1.c`)** | **0** |

Other spellings that also score 0: `c/B1b.c`/`c/C2.c` (both extensions first, then both copies), `c/C1.c`
(`param_2 = (short)param_2; p2 = (short)param_2; ... eq = (param_2 == param_3);`, with no t2/t3), and `c/C3.c` (the
second narrowing through a declared `short s2 = t2; p2 = s2;`, a width move rather than a cast). `c/C4.c`, the same text
with the init statements after the extensions, scores 19 because sched order changes. `body.c` uses the shortest
spelling.

## (a) The residual

The count was 67 against 69 (I counted first). Two instructions were missing, not two registers wrong. The target
sign-extends each argument IN ITS ARRIVAL REGISTER and then copies it, and its `xor` reads the COPIES:
`sll a1,a1,16; sra a1,a1,16; move s4,a1; sll a2,a2,16; sra a2,a2,16; move s1,a2; xor v0,s4,s1`. Every earlier spelling
gave `sra s4,a1,16` (extension straight into the loop-lived register) and no copy.

## (b) Mechanism (every step checked on the RTL dumps, `scratch/dumps_free/` and `scratch/dumps_B1/`)

Three passes are involved. The earlier agent's reading named only combine, and for `body_free.c` it named the wrong pass.

1. **Why `p2 = t2` loses its copy: cse's `(set REG0 REG1)` swap (cse.c:7440-7474, guard :7454-7459).** `dumps_free`:
   in `.rtl`, insn 23 sets t2 (reg 78) and insn 25 is `p2 = t2`. In `.cse`, insn 23 sets p2 (reg 76) directly and
   insn 25 is gone. `p2` becomes the class's canonical register because it lives past the block and its last mention
   is later (`make_regs_eqv`, cse.c:846-862). The copy sits right after the producer, so cse retargets the producer and
   the reversed copy dies. When the copy is not adjacent, combine is the second defence: `t2`'s only remaining reader is
   the copy, because `canon_reg` rewrote the `xor` to `p2`, so it merges (combine.c:1458 `added_sets_2 == 0`). That is
   the earlier agent's step 2, correct only for its non-adjacent orderings.
2. **`p2 = (short)t2` is not a copy that cse can see.** It expands to `(ashift t2 16)` then `(ashiftrt · 16)`
   (`dumps_B1/.cse` insns 25/26). cse has no fold for a sign-extension of an already sign-extended value, so no
   equivalence is recorded. The swap's guard wants a REG source (cse.c:7456), so nothing is swapped. `eq = (t2 == t3)`
   stays `xor t2,t3` (insn 35 reads regs 76/77, the t's).
3. **combine turns it into a copy AFTER cse, and cannot delete the producer.** `simplify_shift_const`,
   combine.c:7926-7942: for `(ashiftrt (ashift t2 16) 16)`, `num_sign_bit_copies(t2) = 17 > 16`, so the pair reduces to
   `t2`. `.combine` insn 26 is `(set (reg/v 78 p2) (reg/v 76 t2))` with a LOG_LINK to insn 23. The producer insn 23
   cannot be merged into it because `t2` is still read later by the `xor` (REG_DEAD on insn 35, not 26).
   `added_sets_2 = ! dead_or_set_p (i3, i2dest)` (combine.c:1458) is 1, the two-SET PARALLEL is not recognised, and both
   insns survive.
4. **local-alloc then points the `xor` at the copies: `optimize_reg_copy_1` (local-alloc.c:700, called from
   `update_equiv_regs` at :1003-1007, `-fexpensive-optimizations`).** For a reg-reg copy whose source does not die
   there, it scans forward in the block. `t2` dies at the `xor` before either register is re-set, so the pass replaces
   `t2` by `p2` in the `xor` and moves `t2`'s death onto the copy. `.lreg` insn 35 reads regs 78/79 (p2/p3), and insn
   26 carries `REG_DEAD t2`. `t2` is block-local and dies at the copy, so it takes `a1` (tied through the `sll` to the
   incoming `$5`). `p2` is global and gets `s4`. The result is the target's in-place extension, the surviving
   `move s4,a1` and `xor v0,s4,s1`. The sched1 order is unchanged because all the priorities are 1 and ties go by LUID
   (sched.c `rank_for_schedule`). So the source order (copy before `eq`) is the byte order.

Why the loop-hoist route was not the answer: letting `loop.c` hoist `(short)param_2` out of the loop and cse2 turn the
hoisted copy into `copy = X` (`c/A1.c`, the most "natural" no-local spelling; `.combine` insns 126/128) gives 69
instructions with the copies AFTER the `xor`. That is exactly the earlier agent's `h12` shape (score 21). The `xor`
keeps reading `a1,a2`, because optimize_reg_copy_1 only fires when the copy comes before the reader.

## (c) The move that closed it

- `p2 = (short)t2;` / `p3 = (short)t3;` in place of `p2 = t2;` / `p3 = t3;`, with `eq` computed from `t2`/`t3`.

## (d) Generator proposal

**R24 "copy through the narrow type":** when a COUNT residual is missing `move sK,aN` after an in-place `sll/sra aN,aN,16`
(or an `andi 0xffff`) and a later op in the same block reads `sK`, find the plain copy `p = t;` of the extended value
(or the statement that assigns the extension straight into `p`). Rewrite it as `p = (short)t;` (or `(u16)`, matching the
extension), keeping `t` as its own local. Then make the later reader (here `eq = ...`) read `t`, not `p`. cse cannot see
the copy (no cse.c:7454 swap), combine reduces it to a copy but cannot drop the producer (combine.c:1458), and
optimize_reg_copy_1 (local-alloc.c:700) points the reader back at `p`. Test: `.combine` shows `(set p t)` with no
REG_DEAD for `t`. One candidate per copy. The reader move is part of the rule, because either half alone scores worse
(`ab3.c`).

## (e) What did not work (byte evidence)

- The earlier agent's matrix (see `scratch/prev_mechanism.md`): statement orders, declaration orders, K&R/ANSI short
  parameters, `eq` before the copies (`h12`, 69 instructions, score 21).
- No p2/p3 locals, `(short)param_N` used in the loop and in `eq` (`c/A1.c`): 69 instructions, score 21 (copies after
  the `xor`, see above). `eq` moved inside the loop (`A2.c`): 64, score 33. `eq` inside the `if` (`A3.c`): 67, score 14.
  Only `eq` hoisted, casts inline (`A4.c`): 69, score 28.
- `short p2, p3` locals (`B2.c`, `B3.c`): 69, score 21. The loop re-extends them, and loop.c + cse2 put that copy after the
  `xor` again.

## (f) Where the method fell short

- **The inherited mechanism was wrong in its first step, and the brief carried it forward.** `prev_mechanism.md` said
  combine deletes the copy of `body_free.c`. The `.cse` dump shows it is gone one pass earlier, through the cse.c:7454
  swap. METHOD's c4 bullet (the same cse gate) was the better lead. Reading `.rtl` → `.cse` → `.combine` for the ONE
  insn in question took a minute and would have redirected the earlier session.
- **The missing pass was local-alloc's `optimize_reg_copy_1`, which neither the METHOD list nor `residual_moves.md`
  names.** It is the only pass that moves a reader from the source of a copy onto its destination AFTER combine.
  Whenever the target's reader reads a copy that combine "should" have folded, suspect it. It deserves a METHOD bullet
  and a residual_moves row.
- **The hint that fitted was c18's (combine reduces a sign extension to a copy, combine.c:7932-7942).** Combined with
  the question "what could keep the producer alive AND still let the reader end up on the copy?", it gave the answer
  in about 15 compiles. The COUNT-first discipline (METHOD step 2) was what made that question askable.
