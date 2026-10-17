---
ts: 2026-10-17T17:08:00.604Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm puzzled why register r73, allocated first, ends up assigned a1 instead of v0 — maybe a conflict with the constant in v0 or with hard register a0 forces this choice, suggesting local-alloc's first pass prioritizes quantities with suggested registers.

I'm also looking at why r73's address computation shows a lui/lw macro sequence using the same destination register, likely from gcc's split of symbol references rather than the assembler's own $at expansion, and trying to trace why r74's liveness extends further — possibly due to the do-while loop structure adding extra label/note insns that affect the register allocation order for v0, v1, a0-a3.
