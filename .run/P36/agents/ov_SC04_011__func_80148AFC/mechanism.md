# func_80148AFC (src/ov_SC04_011/ov_SC04_011_after.c) — T7 agent c3

**CLOSED: score 0** (`--try ... body.c --body`: "score 0 (OTHER; mine 71 ins, target 71) — MATCH"). All six NEEDED
levers are gone: no pin, no `asm`, no added `volatile`, no zero term. The whole-object gate is still the coordinator's job.
`PACK/body.c` is the text to bank.

## The three source moves (it takes all three)

1. **The 0x41 handler gets the angle as its second argument**: `D_80191F24[...](a0, tmp)`, with the table declared in the
   body as `extern s32 (*D_80191F24[])(void *, s32);` (the TU's `ActorFn` is `s32 (*)(void *)`, one argument too narrow).
2. **The raw angle variable is reused for the second `ratan2` result, and it is the SECOND operand of the final sum**:
   `tmp = ratan2(...); *(u16 *)(iVar5 + 0x12) = (ang + tmp) & 0xFFF;`, with `s32 ang = tmp;` straight after the first
   computation.
3. **The analog-stick test is written the natural way**, early `return 0` first:
   `if (lo == 0x80 && hi == 0x80) return 0; ...; return 1;` in place of `if (lo != c80 || (hi = ...) != 0x80) {...} return 0;`.

What each one does on its own, all measured with `--try`:

| body | score |
|---|---|
| `body_free.c` (the levers just deleted) | 23 (72 vs 71) |
| move 3 only (`scratch/c1.c`) | 6 (70 vs 71): the whole 0x53/0x73 block matches, the `move s1,a1` is still missing |
| moves 3+1, one variable used everywhere (`c3.c`) | 8: the angle sits in `s1` and the 0x41 path gains a `move a1,s1` |
| moves 3+1, `tmp` for the call, `ang = tmp` for the sum, second ratan2 in a new local (`c4.c`, `a3.c`) | 8, same as above |
| moves 3+2, no call argument (`a4.c`) | 6 |
| moves 1+2 with the old `||` / `return 0`-last shape (`a2.c`) | 20 |
| all three, but written `(tmp + ang)` (`a1.c`) | 9: the operand order matters, see (b) |
| **all three (`body.c`)** | **0** |

## (a) The residual in one sentence

Two separate defects. (i) The target computes the angle into `a1` (`andi a1,v0,0xfff`) and copies it into `s1` in the
delay slot of the first switch branch (`move s1,a1`); every lever-free spelling writes `andi s1,v0,0xfff` straight away,
so it comes out one instruction short. That is the same class as the twins func_80148E54 and func_80148D44. (ii) In
the 0x53/0x73 block the target loads `+0xAE` twice, rematerialises 0x80 and compares `hi` against `lo`, while the `||`
spelling shares the load and emits an extra `andi 0xffff` and two `nop`s.

## (b) The mechanism: passes and decisions (proved on bytes and on the RTL dumps in `scratch/dumps_final/`)

**Defect (i) is a missing call argument that the disassembly does not show.** In the target, `a1` is written at `0x3260`
and read only by the `move` at `0x3270`. On the 0x41 path it then reaches `jalr v0` at `0x32c4` without being written.
So the handler receives the angle in `a1` and no instruction is needed to pass it. That is the extra consumer that
keeps the producer alive. The previous agent's census ("the producer has exactly one consumer") counted explicit reads
only. A `jal`/`jalr` reads `$a0-$a3` implicitly.

Giving the call that argument is necessary but not enough (score 8). cse still merges the two variables:

- **cse.c:846-862 (`make_regs_eqv`)**. When the copy `ang = tmp` is processed, `ang` becomes the class's canonical
  register only if its last mention is *later* than `tmp`'s: `uid_cuid[regno_last_uid[new]] > uid_cuid[regno_last_uid[firstr]]`
  (line 856). `regno_last_uid` comes from `reg_scan` (regclass.c:1764) and counts sets as well as uses. With `ang` used
  in the 0x53 block, which comes after the 0x41 block, `ang` wins. Two things follow:
  - the **cse.c:7454-7471 swap** fires (its guard at line 7459 is `qty_first_reg[...] == REGNO(dest)`). The producer is
    rewritten to set `ang` and the copy becomes a dead `tmp = ang`;
  - `canon_reg` rewrites the 0x41 argument `(set (reg a1) tmp)` to `ang`. The 0x41 label has one use and is preceded
    by a barrier, so cse follows the jump into it (cse.c:8106). `tmp` is then dead after the copy. (Dump `dumps_c4`:
    insn 46 sets reg 88 = `ang`, and insn 75 is `(set a1 (reg 88))`.)
- **Move 2 reverses that comparison.** Reusing `tmp` for the second `ratan2` result puts a mention of `tmp` after
  `ang`'s last mention. The sum is stored to a `u16`, so it is narrowed and expanded one operand per insn: insn 143
  `(set (reg:HI 122) (subreg:HI (reg 88 ang)))`, then insn 145 `(set (reg:HI 123) (subreg:HI (reg 75 tmp)))`. `tmp`'s last
  mention (145) is later than `ang`'s (143), so `ang` does not become canonical. The swap does not fire and the 0x41
  argument keeps `tmp`. Dump `dumps_final/cse.fn`: insn 46 `(set (reg/v 75 tmp) (and ...))`, insn 49
  `(set (reg/v 88 ang) (reg/v 75))` kept, insn 75 `(set (reg a1) (reg/v 75))` kept. Written `(tmp + ang)`, the order is
  reversed, `ang` wins and the swap comes back (`dumps_a1`: insn 46 sets 88). That is why `a1.c` scores 9.
- **combine.c:1458.** `tmp` is now live past the copy (read by insn 75 on the 0x41 path), so the copy (insn 49) carries
  no `REG_DEAD` for `tmp`. `added_sets_2 = ! dead_or_set_p (i3, i2dest)` is 1, the merged pattern would be a two-SET
  PARALLEL, it is not recognised, and combine keeps both insns. `dumps_final/comb.fn` insn 49 has no death note. The
  reused `tmp = v0` from the second call is folded into the add (insn 147 reads `v0` directly), so the second live range
  costs nothing.
- **Allocation.** `ang` is live across the second `ratan2` call, so it gets `s1`. `tmp` is copied into the argument
  register `a1`, so it prefers and gets `a1`. That also explains the register in the twins: their `tmp` sits in `a0`,
  the first argument of their argument-less handler calls. After sched, the copy is the only entry-block insn that
  `fill_simple_delay_slots` can move into the first `beq`'s slot.

**Defect (ii) is cse's path following plus reorg.** In `if (A && B) return 0; call...; return 1;` both failing tests
jump to one label, so it has two uses. `cse_end_of_basic_block` (cse.c:8106) only follows a jump whose label has one
use, so the call block starts with an empty table: the `+0xAE` load and the 0x80 are redone (`lhu a1,174(s0)`,
`li v0,128`). On the fall-through of `bne lo,0x80`, `record_jump_equiv` (cse.c:5791) makes `lo` equal to 0x80, and the
second test's 0x80 is canonicalised onto `lo`'s register (`beq v0,a0`). The `return 0` block comes before the call
block in the RTL, so reorg steals `move v0,zero` into the `beq` slot and the call block falls into the epilogue.
Moving the `||` form's early exit to the front repaired all of it at once: that is `c1.c`, 23 to 6.

## (c) Moves that closed it

Listed at the top. One-liners:
- pass the value the target leaves in `$aN` as argument N-4 of the handler call on the other path, and widen the
  callee's declaration;
- reuse the producer variable for the later temporary, as the second operand of the final sum, so its last mention
  comes after the copy destination's;
- `if (lo == 0x80 && hi == 0x80) return 0;` ahead of the work.

## (d) Generator proposals

**R22 "hidden argument"**: when a COUNT residual is missing a reg-reg copy whose source `$aN` has no explicit reader in
the target after the copy, but reaches a `jal`/`jalr` on some path without being written, add that variable as
argument N-4 of that call and widen the callee's (or the table's) declaration to match.

**R23 "stay canonical"**, the partner that makes R22 stick: when a surviving copy `dst = src` is folded because cse
made `dst` canonical, move `src`'s last mention after `dst`'s. Reuse `src` for the next temporary whose use comes
after `dst`'s last use, and put it as the later operand. The test to evaluate is cse.c:856.

Both are cheap to compute from the target and the C text. The "reaches a call without being written" check is a
straight-line scan per path. Neither changes the score alone on this body (R22 alone: 6 to 8, worse; R23 alone: 6),
which is the METHOD §5 "joint edit" shape. A beam that drops non-improving children cannot find them.

## (e) What did not work (byte evidence)

See the table in "The three source moves". Also: `ang = tmp` placed inside `case 0x53` (`c2.c`) reaches 71
instructions with the copy present, but in the case block after the `lhu`, with `tmp` in `v1` and the subject in `a0`,
scoring 13. The copy really is in the entry block in the target. `fill_eager_delay_slots` would have preferred the
fall-through `slti` for an EQ branch (`mostly_true_jump` returns 0), so the slot can only have been filled by
`fill_simple_delay_slots` from an insn before the branch.

## (f) Where the method fell short

- **The census of consumers missed implicit reads.** The twin's mechanism.md concluded "unreachable body-only" from
  "the producer has exactly one consumer". A call reads `$a0-$a3` with no instruction. METHOD item 3's first bullet
  ("a dropped call argument") was the answer, but it was hidden because the call is on a different switch path from
  the copy. Any consumer census should count a `jal`/`jalr` as reading every argument register that is live, unwritten,
  at that point.
- **The register the target picked was the clue.** `a1` (and `a0` in the twins) is not what first-fit gives after
  `v0`/`v1`. A value in the second argument register with no visible reader asks "which call reads it?". An
  alloc-table pass should flag argument-register placements that have no visible reader.
- **A neighbour's `@stuck`/"unreachable" claim was wrong again**, as METHOD item 0 warns. It was well argued inside its
  premises, and one premise (the consumer count) was measured with a blind instrument.

## Twins, prediction only (not worked, per the brief)

func_80148E54 and func_80148D44 have the same entry block with `tmp` in `a0`, and their 0x41 handler calls pass
nothing. Prediction: pass the angle as the handler's **first** argument (`D_80191FA4[...](tmp)`,
`D_80191F64[...](a)`), plus R23 if cse still merges: `tmp = ratan2(...); return (ang + tmp) & 0xFFF;` (the sum there is
SImode, so check which operand is mentioned last in `.jump`). This has not been checked on bytes.
