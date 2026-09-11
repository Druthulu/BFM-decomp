# func_8017F694 (ov_SC06_016, src/ov_SC06_016/ov_SC06_016_jr_8017C8D0.c) — e24, P36 S104

**Final: score 0, ZERO levers** — the tree's `__asm__ __volatile__("")` barrier AND its un-marked frame-pad lever
(`SVec8_8017F694 unused; (void)&unused;`, "frame-pad induction") are both gone. `body.c` = scratch/p_and2.c.
ONE move: the sign test `if (*(s32 *)(*(s32 *)(arg0 + 0x20) + 0x4) < 0)` spelled as the bit test it is —
`if (*(u32 *)(*(s32 *)(arg0 + 0x20) + 0x4) & 0x80000000)` — plus deleting the pad (which the move makes redundant).

(a) Residual (body_free, score 12, COUNT 59 vs 60): the `bgez` delay slot holds the ELSE arm's `lui v1,0x7fff` in mine,
the fall-through arm's `lui v1,0x8000` in the target, and the fall arm then needs a load-delay `nop` (the missing insn).

(b) Mechanism (proved on the .cse/.combine/.sched2/.dbr/.greg dumps, scratch/dumps_base vs dumps_and2):
- body_free: `bgez` = `(ge x 0)`; `mostly_true_jump` (`reorg.c:1335`, the GE-against-0 case) predicts it TAKEN, so
  `fill_eager_delay_slots` tries the target thread first and `fill_slots_from_thread` (`reorg.c:3257`) steals the
  else arm's `lui 0x7fff`. The tree's asm at the head of the else arm stopped that search (`stop_search_p`).
- with the bit test: cse gives `0x80000000` ONE pseudo (r77) shared by the test's `and` and the fall arm's `|=`
  (`.cse`: insn 20 `(set r77 -2147483648)`, used by insn 21 `and` and the later `ior`). combine then folds
  `and`+`beqz` into the sign test `(ge r75 0)` (`.combine` jump 23), but r77's load STAYS in the test block, before
  the branch, because the fall arm still reads it. reorg's `fill_simple_delay_slots` backward scan (`reorg.c:2887ff`,
  "scan backwards from the insn") moves that `lui v1,0x8000` into the slot — the target's bytes; the fall arm is left
  `lw; nop; or`.
- the FRAME: the folded `and`'s result pseudo r76 loses its insn but combine's `distribute_notes` leaves a
  `(use (reg 76))` carrying its REG_DEAD note (`combine.c:10831-10845`). r76 keeps refs, gets no hard register
  (`.lreg`: "ST_REGS or none"; absent from `.greg`'s dispositions) and reload gives it a stack slot (the `.sched2`
  `(use (mem:SI (plus sp 16)))`, `reload1.c:2327-2352`) → frame 0x20, `$ra` at 0x18. That is the exact slot the
  "frame-pad induction" lever was faking. With the pad kept, the frame is 0x28 (score 4, scratch/p_and.c).

(c) See the move above. Both the delay-slot fill and the frame come from the one spelling.

(d) GENERATOR PROPOSAL: when a function tests a value's sign (`x < 0` / `x >= 0`) AND also ORs/ANDs the constant
0x80000000 elsewhere, try the test as `(u32)x & 0x80000000` (and for a frame-only residual of +8 bytes with a dead
pad local in the tree, try the same for any sign test) — cse shares the constant, combine orphans the `and`'s pseudo
into a slot.

(e) Tried and failed (bytes): `!(x > -1)` (12 — normalised to GE 0 before reorg), `(u32)x >> 31` (12), the arms swapped
with `x >= 0` (13). The history's 149 mechanical candidates reached 5 (ORDER) — no generator rewrites a comparison's
operator.

(f) Method note: the residual looked like a reorg/scheduling puzzle (the tree comment blamed reorg's eager steal); the
decisive evidence was the COUNT (60 vs 59) plus the tree's frame pad — two symptoms of one missing pseudo. A pad lever
in `body_free.c` is a hint that some real pseudo is missing. The 263 other "frame-pad induction" sites in `src/`
(func_80141A60 / func_8013BC7C families, already matched) might be read the same way — only this function had the
sign-bit + 0x80000000 shape, so none was tried.

(g) Structs: no. The decision is cse/combine's handling of a constant and a dead comparison pseudo; the field widths
are already right. A struct for `D_8019F9FC` (fields at 4/0x8/0x10/0x12/0x14/0x18) would only rename the accesses.
