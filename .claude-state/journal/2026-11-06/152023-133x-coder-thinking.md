---
ts: 2026-11-06T22:20:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3HlckQmX3PuXFjxfhwGI
---
Only 4 blocks matched (regex didn't match all 6 because the 0xD4 blocks have a different src line? The pattern requires `src + 0x20`; for the 0xD4 blocks, src is set from arg0+0xD0 or 0xD4 — still `src + 0x20`. Hmm, maybe the regex's non-greedy matching consumed across blocks. Anyway, no change: 135.

The do-while doesn't affect the twins' dst allocation. The dst problem is different (long-lived pointer vs short temps).

Let me try wrapping the dst block *differently*: the issue is that dst is long-lived. A do-while doesn't shorten its life.

OK. Let me reconsider the twins' dst allocation with the insight from item 1: the do-while fixed the *EBB split* so local-alloc allocated separately. For the twins, the dst block is already in its own basic block (the case). So no change.

The twins' dst gets a2 because the temps in the block take v0,v1. To give dst v1, we'd need the temps to not take it.

Hmm, in item 1 the do-while worked because it split the tail into two blocks so the packet chain and oidx were allocated separately. For the twins, dst and the temps are in the same block and genuinely conflict.

What if we split the dst block so the temps are in a different block from dst? E.g., wrap the *sum* statements in a do-while:
```
do {
    *(u16 *)(*(s32 *)(dst + 0x20) + 0x10) = ...;
    *(u16 *)(*(s32 *)(dst + 0x20) + 0x12) = ...;
} while (0);
```
Then the sums' temps are in a separate EBB, and dst is used in both blocks (live across) → global-ish? No, dst would be live across the boundary; local-alloc handles each block; dst's qty in block 2 would be born... Actually dst is used in block 1 (the sh stores) and block 2 (the sums); local-alloc allocates per block with dst re-materialized? No, dst is a pseudo live across; if the block splits, dst becomes a global allocno (live across blocks) → global-alloc assigns it a callee-saved reg (s-registers), not v1. That would mismatch.

Hmm.

Let me try wrapping the sh stores separately from the sums:
```
do { dst = load; 3 sh; } while(0);
do { 2 sums; } while(0);
```
dst is live across → global. Mismatch likely.

Alternatively, wrap the *whole* case block? no.

Let me try a few anyway (cheap):
- v1: do-while around the 3 sh stores only.
- v2: do-while around the 2 sums only.
- v3: do-while around the dst load + sh stores.

Let me test on the twin.
