---
ts: 2026-10-17T16:53:21.139Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm comparing scheduling priorities between the la instruction and the lhu load — tracing their dependency chains to see which has the longer path to the end, since that determines ordering in gcc 2.7.2's backward instruction scheduler.

Let me try declaring obase once and reusing it for both load sites, so cse can fold the address computation consistently rather than rebuilding the symbol reference twice. I'm also wondering if the birthing-boost logic in sched.c—where instructions that birth a register get priority adjustments—explains why a second identical assignment demotes that boost, since la effectively "births" reg 78 and that interacts with how backward scheduling orders things.
