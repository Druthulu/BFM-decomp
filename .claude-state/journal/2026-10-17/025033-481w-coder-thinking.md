---
ts: 2026-10-17T08:50:33.330Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad48947f967e77fd9
model: claude-opus-5-5[1m]
effort: medium
turnId: 5652b206-5bd1-470d-af6a-d1e28be458c3
---
I'm noticing func_8012E364 has 133 TU copies but the real target is the header file, so those bodies have already been judged separately and I should exclude this function from TU runs, using the header path instead.

For TU mode: run --only with the 26 names excluding func_8012E364 (and func_8017E98C lacks a TU), covering roughly 432 bodies across ~418 files. For header mode: run --headers --only with the 8 header paths.

Before the full run, I want to prove it works on 2-3 singleton bodies like func_80148AFC, func_80148D44, func_801ADF5C. I also need to verify the tree is clean since --apply likely requires it, and check what the calibration refresh step in delever_cycle actually does.
