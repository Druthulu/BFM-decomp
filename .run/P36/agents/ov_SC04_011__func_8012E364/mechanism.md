# func_8012E364 — T7 agent c22 re-draw (IN PROGRESS)

Earlier agent's reading and body are preserved in `scratch/prev_mechanism.md` / `scratch/prev_body.c` (score 4, ORDER).
PACK/body.c is still that score-4 body until this re-draw improves on it.

Working notes (being rewritten as the reading firms up):
- No call of any kind in this function (abs is the `abssi2` insn, not a call), so the S103 implicit-argument
  (`$a0`/`$a1` read by a jalr) shape does not apply: the `$5` pin is on `prev`, a plain local of the tail block.
- Local-alloc constraints read off the target's registers (tail block):
  e2 = `$a0` needs BOTH `$v0` and `$v1` held by LOCAL quantities across e2's life, so `v` (v1) and `d` (v0) are
  both block-local and in different quantities: the untie must come from inside `combine_regs`
  (`local-alloc.c:1722`), not from making `v` or `d` global.
- `prev` = `$a1` needs `$v0` busy during prev's life: in the SCHED1 order the flags `lhu` sits before the `subu`
  that kills `prev` (sched2 later moves it back) — the order the earlier agent's score-4 body gets.
