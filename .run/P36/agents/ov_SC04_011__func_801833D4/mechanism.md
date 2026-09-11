# func_801833D4 (impl_801833D4, ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e11)

**Result: score 0 in plain C.** No pin, no asm, no added volatile. Levers go from 1 to 0 (the `$19` pin on `r1`).
Signature unchanged. No copy of this class in another TU (the 0xFFD80000 / `obj + 0x20) + 0x12), s0)` greps find
unrelated bodies).

## (a) The residual in one sentence
Same count, same registers. Two moves of the first block are swapped. The target does `sw s4; move s4,zero` early
and fills the `beqz` delay slot with `move s3,a1`. Mine does `sw s3; move s3,a1` early and puts `move s4,zero` in
the slot.

## (b) The pass and the decision (proven on dumps and bytes)
- **The initialiser `s32 r1 = a1;` sits directly after the parameter copy** `(set 74 $5)`. cse's
  `(set REG0 REG1)` swap (`cse.c:7454-7480`: `NEXT_INSN (PREV_INSN (insn)) == insn`, the previous insn sets REG1,
  REG0 is the canonical reg) retargets the parameter copy to set `r1` directly. The `.cse` dump of
  `scratch/v_first.c` shows `(insn 6 (set (reg/v 74) (reg 5 a1)))`.
- **sched1 never moves a parameter copy.** Before reload, block 0's leading SETs before `NOTE_INSN_FUNCTION_BEG`
  are removed from scheduling (`sched.c:3188-3205`: "don't delay getting parameters from hard registers into
  pseudo registers"), so the copy keeps the lowest LUID. In sched2 all first-block insns have priority 1, and
  `rank_for_schedule`'s last tie-break is `INSN_LUID` (`sched.c:2425-2428`). The `s4 = 0` insn (higher LUID) is
  therefore scheduled closer to the branch, and reorg's backward scan puts it in the delay slot.
- **Written as a statement after a real insn** (`s0 = D_801EFD20;` first), the copy `r1 = <param pseudo>` stays a
  separate insn at its own position. Combine then folds the dying parameter pseudo into it: in the `.lreg` of
  `scratch/v_before_s4.c`, reg 73 is gone and `(insn 16 (set (reg/v 74) (reg 5 a1)) REG_DEAD a1)` sits after the
  `D_801EFD20` load. sched1 now schedules it with `LAUNCH_PRIORITY` (`sched.c:187`, the 0x7f000001 in the trace),
  ahead of `s4 = 0` (priority 1). That places it after `s4 = 0`, sched2's LUID tie-break keeps the order, and reorg
  takes `move s3,a1` into the delay slot, which is the target.

## (c) The move that closed it
`s32 r1 = a1;` becomes `s32 r1;` plus the statement `r1 = a1;` after `s4 = 0;`. Every position after the first
real insn scores 0: after `s0 = …` (`v_before_s4`), after `s4 = 0` (`body.c`), after `obj = …` (`v_after_obj`),
and as the declaration list `u16 s0 = D_801EFD20; s32 r1 = a1;` (`v_declinit`). The body comment that explained
the pin now explains this.

## (d) Generator proposal
When a register residual is two first-block moves swapped, and one of them is a parameter copy (`move sN,aK`, which
the target has later or in a delay slot), turn `T x = aK;` at the top of the body into a plain `x = aK;` statement
placed after the first real statement (and try each later position). This takes the copy out of cse's
adjacent-producer swap and sched1's parameter-copy exclusion.

## (e) What did NOT work (byte evidence)
- `r1 = a1;` as the FIRST statement (`v_first.c`): score 5, the same residual. It is still adjacent to the
  parameter copy, so cse still swaps it.
- Deleting `r1` and using `a1` directly (`v_noR1.c`): score 5. The parameter copy is the only copy and stays
  unscheduled.
- `s4 = 0;` moved first (`v_s4_first.c`): score 5.
- `r1 = a1;` inside the `if` (`v_in_if.c`): score 8. The copy lands in block 1, which is too late.
- The sweep's R6 (inline r1) and R9 (swap statements) stayed at 5. No generator splits an initialiser off its
  declaration.

## (f) Where the method fell short
The residual's "register pairs zero->a1, s4->s3" line reads like an allocation defect, but it was purely order
(ORDER class, same registers). The sched1 trace (the 0x7f000001 LAUNCH_PRIORITY on the copy) and sched.c:3188 gave
the reason. The allocation table would have been a detour.

## (g) Structs question
No. The lever was about where a register copy sits (cse adjacency, sched1's parameter-copy exclusion), not about
memory. A struct for `obj`/`a0` would not change it. The `v[5]` padding array could plausibly become a real struct
local (2 leading words + an x/y/z vector) in the structs phase, but it is not part of this lever.

Files: `body.c` (score 0), `scratch/v_*.c` (variants above), `scratch/dumps_{free,first,before_s4}/`,
`scratch/splice.py`.
