---
ts: 2026-10-17T13:36:05.329Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I'm trying to recall how GCC 2.7's local-alloc computes register priority from live length, cross-checking whether the 224 figure for reg_live_length actually matches since the birth point moved didn't seem to change it.

But moving the set 11 insns later should shrink the live range—unless the set in a2 actually landed after the store at insn 40, similar to a1. I need to check whether a1's set of p is placed at the same position, since source order should dictate emission unless some pass reordered it.
