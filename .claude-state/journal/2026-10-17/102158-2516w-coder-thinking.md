---
ts: 2026-10-17T16:21:58.215Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm comparing register allocations between my version and the target, and noticing the target schedules the move/addiu instructions differently right after the branch, so I need to match that placement to align the two sequences.

The deeper conflict is that rb and m have different register assignments across versions, which shifts the live ranges—so in my version rb landing in a0 clashes with where the move needs to happen, which likely explains why the scheduling diverges.

I'm realizing these four pseudos (t, flags, rb, m) all cross basic blocks, making them global allocations rather than local ones, so their register assignment depends on priority ordering by reference count and live range length rather than simple linear scanning.

I'm trying to work out why the target assigns flags to a0 and t to a1, while mine does the reverse — it comes down to allocation order determined by that priority formula, roughly the log2 of reference count times reference count divided by live range length.

t has three refs from its set and two loads; flags also has three refs but a different live span, so maybe boosting flags' priority or shortening its live range would flip the order. I should check the actual allocation table by running tud.sh with f1 to see the computed priorities directly rather than guessing.
