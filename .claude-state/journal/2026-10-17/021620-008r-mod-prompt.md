---
ts: 2026-10-17T08:16:20.331Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
role: loop
---

‹pa› T7 stopped: T7 asks a question:
question

T7's pin work is done, but its cast gate can't reach rc 0 inside T7's file scope. Fixing it takes a small tools/ edit, and tools/ is not among T7's files.

Done so far:
- The pins became declared parameters (T7.c1 and T7.c2, each R22 218/218).
- The residue TSV was rewritten and committed (8ca59342a5). Missing-parameter rows went from 546 to 384.
  - 383 survivors are scratch registers (the pin is written before it is read, so there is no incoming value).
  - 1 is refused: func_8017EC90, where dropping the pin changes the bytes.
  - Each survivor's instrument field names its refusal.
- `lever_census --check --strict --residue` passes with residue-unused 0.
- The per-segment cast residue was re-run for all four segments.

Still failing: T7.c3 found the 10 sites the cast gate flagg…
milestone: `PY tools/plan_edit.py show --section Milestone`
Decide small changes inside the milestone yourself (plan_edit, then release({hold: "question", note})); ask the developer about the milestone or the scope.
