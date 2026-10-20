---
ts: 2026-10-17T17:29:11.200Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm working through the local-allocation puzzle, mapping which constants and temporaries should land in which registers based on their lifetimes and reference priority.

Realizing the complication: scheduling passes run before and after register allocation, so the final instruction order won't match the order local-alloc actually saw, making this much harder to reverse-engineer than a simple priority sort.

Given the time pressure, I should fall back to checking the actual dumps for a dropped case like c7840 to see what priorities the allocator really assigned, rather than continuing to guess.
