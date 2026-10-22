---
ts: 2026-10-22T04:31:03.632Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: afdda1e6f94a02c83
model: claude-opus-5-5[1m]
effort: medium
turnId: 93d96e30-d64f-4169-8a8e-7bff7f29eac8
usage: {input: 6, cacheRead: 192414, cacheWrite: 824, output: 748}
---

Partly. The batches are grouped by lever type, but cracking one function doesn't mean the coder can crack the others the same way.

**Why one crack doesn't carry over.** These are singletons: each function's lever appears nowhere else. The functions that shared the exact same lever were already handled in T9, where cracking one example fixed every copy. So in T11 there's no exact fix to copy from one function to the next.

**Why grouping still helps.** On the 17th, at your suggestion, we re-dealt the batches that hadn't started. Each batch now holds functions with the same lever type, from the same source file where possible. That pays off in three ways:
- **Similar moves.** Functions with the same lever type tend to fall to the same few moves. In T10, about half the wins came from two tricks: reusing a variable to steer the compiler's choices, and putting a store in each branch of an if instead of using a barrier. A coder that has just cracked a barrier with one of those tricks tries it first on the next barrier.
- **Already-read context.** Functions from the same file share types and headers the coder has already read. Re-reading cached context costs about a tenth of fresh reading, so the coder doesn't pay again to understand the file.
- **Shared notes.** Every coder adds the move that cracked each function, or the wall it hit, to `.run/P40/T11/moves.md`. Every new coder reads that file first, so what one coder learns reaches the others too.

Batches stay at about 5 to 10 functions. Much longer than that, and the coder's old notes start crowding out the function in front of it. For MiniMax we're keeping batches to 5 or fewer, since one of its earlier runs ran out of room.
