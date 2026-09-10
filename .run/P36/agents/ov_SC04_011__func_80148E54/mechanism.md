# func_80148E54 (src/ov_SC04_011/ov_SC04_011_after.c): T7 agent c12

**CLOSED: score 0** (`--try ... body.c --body`: "score 0 (OTHER; mine 67 ins, target 67) — MATCH"). Both NEEDED levers
(the `$4` pin and the launder `asm`) are gone. There is no pin, no `asm`, no added `volatile` and no zero term.
`PACK/body.c` is the text to bank. The whole-object gate is still the coordinator's job.

The earlier agent's reading, which argued this body "unreachable body-only", is kept verbatim at
`scratch/mechanism_prev_agent.md`, and its best body is at `scratch/body_prev_agent.c`. Its two pass readings are
correct: cse.c:7454 for the adjacent copy and combine.c:1458 for the separated one. The unreachability conclusion was
wrong. It rested on the census "the producer's value has exactly one consumer", and that census did not count the
implicit `$a0` read of the `jalr` on the 0x41 path. See (f).

## The two source moves. It takes both.

1. **Give the 0x41 handler the angle as its first argument**: `D_80191FA4[...](tmp)`, with the in-body table declared
   `extern s16 (*D_80191FA4[])(s32);`. It was `(*[])()` before, which passes nothing.
2. **Reuse `tmp` for the second `ratan2` result, and make it the later operand of the sum**:
   `tmp = ratan2(...); return (ang + tmp) & 0xFFF;`, with `s32 ang = tmp;` right after the first computation.

| body (all `--try`, real TU) | score |
|---|---|
| `body_free.c` / the earlier agent's `body.c` | 6 (66 vs 67), the copy is missing |
| move 1 only (`scratch/t1.c`) | 7 (66 vs 67). The copy is still missing and the 0x41 path gains `move a0,s1` |
| move 2 only (`scratch/t3.c`) | 6 (66 vs 67) |
| both, written `(tmp + ang)` (`scratch/t4.c`) | 1 (67 vs 67). The copy is present; only the `addu` operand order differs: `addu v0,v0,s1` vs `addu v0,s1,v0` |
| **both, `(ang + tmp)` (`body.c` = `scratch/t2.c`)** | **0** |

## (a) The residual in one sentence

The target computes the masked angle into `a0` (`andi a0,v0,0xfff` at 0x35b0) and copies it into `s1` in the delay slot of
the first switch branch (`move s1,a0` at 0x35c0). Every earlier spelling wrote `andi s1,v0,0xfff` directly and came out
one instruction short. In the target, `a0` is never written again before the `jalr v0` at 0x3614 on the 0x41 path. The
handler therefore receives the angle as its first argument at no instruction cost. That hidden read is the second
consumer that keeps the producer alive.

## (b) The mechanism: passes and decisions, proved on the RTL dumps

Dumps are in `scratch/dumps_{t1,t2,t4}/` (made by `scratch/dump.py`: the real TU with the body spliced in, then the
recipe's cpp and cc1 with `-dr -ds -dj -dc -dl -dg -dS`). Pseudo 73 is `tmp` and pseudo 86 is `ang`.
In `.jump` the producer is insn 40 `(set 73 (and 85 4095))`, the copy is insn 43 `(set 86 73)` and the argument is
insn 67 `(set a0 73)`.

- **cse.c:846-862 (`make_regs_eqv`)**. When insn 43 makes 86 equivalent to 73, 86 becomes the class's canonical register
  only if `uid_cuid[regno_last_uid[86]] > uid_cuid[regno_last_uid[73]]` (line 856). `regno_last_uid` is set by `reg_scan`
  at regclass.c:1764 and counts sets as well as uses.
  - Move 1 only (t1): 73's last mention is insn 67, in the 0x41 block. 86's last mention is insn 135, the sum in the 0x53
    block, which comes after the 0x41 block. So 86 wins. The **cse.c:7454-7471 swap** then fires. `.cse` shows insn 40
    rewritten to `(set 86 (and ...))`, the copy gone, and insn 67 re-canonicalised to `(set a0 86)`. The angle lives in
    `s1` and the call path pays a `move a0,s1`. That is the 7.
  - Both moves (t2): the reuse adds insn 133 `(set 73 v0)` and puts 73 in the sum insn 136 `(plus 86 73)`. The last
    mentions of 73 and 86 are now the same insn, 136. The test at line 856 is a strict `>`, so 86 does not become
    canonical and the swap does not fire. `.cse` keeps insn 40 setting 73, insn 43 `(set 86 73)` and insn 67 `(set a0 73)`.
  - `(tmp + ang)` (t4): the cse result is identical to t2, because the tie holds whichever operand comes first. The
    SImode sum is one `addsi3` insn that mentions both. The operand order only reaches the final `addu`, which is the
    score 1. This differs from sibling func_80148AFC. There the sum is narrowed to HImode one operand per insn, so the
    order decided the cse tie itself (c3's `a1.c` scored 9).
- **combine.c:1458**. In t2, 73 stays live past the copy because insn 67 reads it on the 0x41 path. So the copy carries no
  `REG_DEAD` for 73 (`.combine`: insn 43 `(set 86 73)` with an empty note list). `added_sets_2 = ! dead_or_set_p (i3,
  i2dest)` is 1, the merged two-SET PARALLEL is not recognised, and combine keeps both insns.
- **Allocation and slot**. 86 is live across the second `ratan2` call, so it gets `s1`. 73 is copied into `a0` for the
  call, so it prefers and gets `a0`. The copy is then the only entry-block insn `fill_simple_delay_slots` can move
  into the first `beq`'s slot, which is the target's layout. This last step was not dump-verified; the bytes show it.

## (c) The moves, one line each

- Pass the value the target leaves unwritten in `$a0` as the first argument of the handler call on the other switch path,
  and widen the in-body table declaration to `(*[])(s32)`.
- Reuse the producer variable for the second `ratan2` result, as the later operand of the final sum, so that its last
  mention is not earlier than the copy destination's.

## (d) GENERATOR PROPOSAL

This is the same pair c3 named for func_80148AFC, and these two bodies are its second and third instances.
**R22 "hidden argument"**: when a COUNT residual is missing `move sK,$aN` and `$aN` reaches a `jal`/`jalr` on some path
without being written, pass the copy's source variable as argument N-4 of that call and widen the callee or table
declaration.
**R23 "stay canonical"**: when R22 alone gets worse (the call path gains `move $aN,sK`), reuse the source variable for the
next temporary after the copy destination's last use. In an SImode sum, put it as the later operand so that the tie at
cse.c:856 holds. That position is also what the `addu` operand order wants.
Neither move improves the score alone (7 and 6 from 6), so a beam that drops non-improving children cannot find the
pair. The generator has to emit them together.

## (e) What did not work (byte evidence)

The single moves and the operand order are in the table above. The earlier agent's ~90 spellings (listed in
`scratch/mechanism_prev_agent.md` §e) all lacked move 1, so each one met the cse.c:7454 or combine.c:1458 killer.

## (f) Where the method fell short

- **A consumer census has to count implicit argument-register reads.** The earlier agent's unreachability argument was
  valid given its premise. The premise ("`a0` is read only at 0x35c0") was measured with an instrument that treats a
  `jalr` as reading nothing. Any census must treat a `jal`/`jalr` as reading every `$a0-$a3` that reaches it unwritten.
  That check is a straight-line scan per path.
- **The register was the clue.** A value placed in `a0` right after a call's result lands in `v0`, with no visible
  reader, is not what first-fit gives. It is asking "which call reads it?"
- **The TU header above func_80148E54 is now wrong.** It says "then jalr with no args" (the TU at line 749). The
  handler takes the angle. The coordinator should correct it when banking.
- With c3's sibling reading in hand, this closed on the second `--try`. The cross-function prediction was the method's
  strongest step this time.
