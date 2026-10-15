---
ts: 2026-10-15T03:35:44.540Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a1ce918197a39b8ec
model: claude-opus-5-5[1m]
effort: medium
turnId: 80012580-34a8-4c0b-8701-0fce1ef170b6
usage: {input: 12, cacheRead: 180801, cacheWrite: 8650, output: 1458}
---

Phase 3.40 needs your decision before I brief the planner: whether it runs, and how big it is.

The generation plan left this open until 3.39's leftovers (the "residue") were counted. Phase 3.39 closed by recording about 292,000 cast sites as residue instead of fixing them. These are places in the C code that read struct fields through raw pointer arithmetic, and they stay that way because their structs have no single agreed definition yet. That is roughly 13,000 struct types, and the top 81 cover half the sites. The lever residue file also lists 2,433 rows covering 3,528 sites. A "lever" here is a pin or inline asm we use to steer the compiler, and 70 of those rows are tagged as needing an agent.

My recommendation is to run it in full. Giving those structs canonical definitions and getting the lever check to a true zero is the real goal of this generation. Phase 3.39 only covered these sites with records, and the naming phases (3.42–3.43) work much better on real struct members. Starting with the top 81 types keeps it manageable.

The smaller option does the named items plus the 70 agent-tagged rows and leaves the canonical-types campaign for later. Skipping goes straight to 3.41 and leaves the residue as it is.

Whatever you pick, the plan will also get its usual phase-close docs task: the README graphs, story section 10, retrospective section 7 and the wiki. The "uncovered" chart series you asked for in 3.39 is still queued for this phase too.
