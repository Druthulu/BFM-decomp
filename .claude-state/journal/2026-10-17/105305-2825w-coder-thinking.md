---
ts: 2026-10-17T16:53:05.991Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'm noticing the target's register allocation reuses v0 across several constant loads where mine spreads them across t2 and v1, and I'm tracing through how the table address load and offset addition sequence differs in ordering from my version.

This is the classic GCC 2.7.2 sched1 heavy-reorder problem that's going to take real iteration to match exactly. I'm trying a more natural libgpu-style rewrite with the pointer and ordinance-table setup, planning to test it against the target and adjust register pinning over a few passes, since the constants seem to get hoisted early and split (lui then a separate OR with 0xFFFF) in a way that plain C without inline asm would just fold via CSE.

Without knowing the exact pins, the allocation will differ in subtle ways, so I'll try several natural variants quickly within the time I have.
