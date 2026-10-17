---
ts: 2026-10-17T16:19:53.231Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm comparing register allocation details against the target binary—my version swapped which registers hold flags, t, rb, and m compared to the original's assignment, plus differences in how D_801E9B9C gets hoisted.

Trying to understand why mine hoists that symbol into s4 while the target doesn't: it likely comes down to loop.c's register pressure heuristics deciding whether an invariant is worth moving out, based on threshold calculations involving non-fixed register counts and whether the loop contains a call. The hard-coded register pins in my version may be skewing that pressure estimate differently than in the original, causing the hoisting decision to diverge.

Given time constraints, I'm going to test simple variations directly: removing the local `sc` and using the slot inline in the call, and declaring `rb` as a `u8` so the masking behaves differently. The target's retained `andi` instruction suggests combine couldn't prove the upper bits were zero, which would happen if the pin forces `rb` into a hard register before combine can track its nonzero-bits info from the `lbu` load.
