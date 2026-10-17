---
ts: 2026-10-17T11:15:21.461Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm trying to trace how v0=0 ends up in the branch's delay slot — maybe the RTL before reorganization sets v0 to zero and jumps to the return point when the condition is false, which would explain the ordering I'm seeing.

Actually, I think mine merges multiple return-0 paths into a shared block via cross-jumping, while the target keeps each return's "move v0,zero" separate before its own jump since they don't all match the same later value. I should check whether cross-jump optimization is actually enabled by default in toplev.c to confirm this theory.
