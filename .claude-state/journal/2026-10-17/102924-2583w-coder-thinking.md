---
ts: 2026-10-17T16:29:24.901Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm noticing register r74 gets reused across early and late points in b1, pointing to a global variable with separate copies, while in a4 both argument copies happen late. The target seems to need t's move scheduled earlier, right after the second jal, but since the gte assembly macros are volatile inline asm, the scheduler can't move code across them -- so t's copy has to sit textually before the gte call, whereas u's copy, being coalesced, behaves differently.

In the target, arg2's pseudo register is tied directly to s2, and s7 holds t copied from s2, while d gets s1 -- so I need to figure out why a4's allocation flips t's copy timing relative to b1's. I'm checking the allocation tables for both a4 and b1 to see which pseudo-register ties account for this difference.
