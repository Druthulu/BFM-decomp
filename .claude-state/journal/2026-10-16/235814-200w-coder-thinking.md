---
ts: 2026-10-17T05:58:14.870Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
Given the scale, with roughly 27 names and multiple callers each, I'm realizing the bulk of this work is going to be hand-editing each caller to match its first parameter name, updating the extern declarations in 800.c to the final prototypes for each function.

I need to pin the parameter type as s32, matching how callers pass a0 across varying types like void* or s32 — casting at the call site keeps things consistent even though the body internally treats it as a struct pointer. My plan is to batch the caller edits across all names first, check per binary, then run check-all and commit, before moving to the rung D definition rewrites with their own judge and check-all passes. I'm now looking at the actual caller source for func_8001C9D0, which has 13 call sites I need to edit by adding the parameter to each invocation.

I want a generic script that rewrites both the call sites and the K&R-style declarations, defaulting each call's argument to the enclosing function's corresponding parameter unless verified otherwise — and for function-pointer-cast calls, simplifying them back to direct calls with the correct cast on the argument. Before trusting that callers simply forward their own a0 unchanged, I should write an automated check that scans each caller's instructions from entry to the call site for any write to that register, to robustly confirm the register isn't clobbered first.
