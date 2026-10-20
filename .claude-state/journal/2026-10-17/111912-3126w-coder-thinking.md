---
ts: 2026-10-17T17:19:12.425Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm noticing the target keeps recomputing the address of blk each time rather than holding it in a register across calls, even though it's a cheap frame-relative address that CSE might otherwise cache as a pseudo.

I'm recalling that gcc 2.7's cse.c may specifically avoid replacing fixed frame-pointer-plus-constant addresses with a register since recomputing them is treated as cheaper. I need to check the actual cse dump to see how s1 and s4 are assigned across the relevant blocks to confirm this.
