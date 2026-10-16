---
ts: 2026-10-16T11:46:14.261Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
role: loop
---

‹pa› T4 stopped: T4 asks a question:
question. The T4 overlay sweep is finished, but 7,128 overlay sites still read TYPE-NOT-CANONICAL, so one done-when clause is not met. Those sites sit on struct names created by the sweep itself, and no rule decides them yet.

What is done: 24 restruct_cycle.sh batches (t4_S1..S24, last 1e4f36bacf), each final 100/100 identical, R22 218/218 and committed. The drawable set shrank every batch, 2,417 → 138 → 38 files, and t4_S25 hit the zero-work exit. No file was written with 0 conversions, and tail-only bodies were skipped by the planner.
- Sweep: 55,583 sites became member accesses. Kept casts are backed CAST_* macros, unbacked 0.
- Raw casts, all segments: P 174,987 → 120,360 and X 12,031 → 10,390.
- Residue chain on ov: `--residue --forms P,X,I,M`, census, `--restamp` (56,625 sites resta…
milestone: `PY tools/plan_edit.py show --section Milestone`
Decide small changes inside the milestone yourself (plan_edit, then release({hold: "question", note})); ask the developer about the milestone or the scope.
