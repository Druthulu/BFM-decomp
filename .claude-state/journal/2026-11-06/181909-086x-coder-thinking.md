---
ts: 2026-11-07T01:19:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8mZd6bcxsMrv1O3N9zem
---
In bb, the store's base is still `(reg:SI 4 a0)` — the equivalence fired again despite the do-while block. So cse merged new_var with r75 anyway (the do-while around the assignment didn't stop it).

So the EBB split doesn't prevent the merge.

At this point I'm confident: WALL.

Time 18:19. Item 2 needs until ~18:29. Let me do a few more tries with genuinely different ideas for 5-6 min, then write the log.

Ideas:
1. Make the store's base a pseudo whose live range is only the store (a fresh copy computed right before the store, inside a do-while, AFTER the call-arg copy?). Hmm, the call-arg copy is placed by sched1 right before the call; if the store is BEFORE the call in the RTL, the copy is after it. But sched1 moves the copy up.

What if the store comes AFTER the call in the RTL (source order: call, then store)? Then sched1 can't move the copy above the store (the copy is before the call, and the store after). The store wouldn't be in the delay slot though → the target has it in the delay slot. But maybe dbr (reorg) can still fill the delay slot with the store? Reorg fills the delay slot with the insn after the jump — if the store is right after the call, it can be moved into the delay slot! Then the final code would be `jal; sw` — matching the target's schedule!

So: source order `func_80171990((u8 *) s0); *((s32 *)(new_var + 0x204)) = v0;` — the store AFTER the call. Semantically: the call may read the memory before the store writes it — that's a behavior change! Hmm, the target's source has the store before the call. If func_80171990 reads the 0x204 field, reordering changes behavior.

But wait — is that actually a semantic change? Yes, potentially. However, the game's function might not read it... but I can't assume. The brief says real C moves; reordering a store past a call is not semantics-preserving. Hmm. Actually, could we do it safely? If func_80171990 doesn't touch that memory, it's fine, but we can't prove it.

Hmm, but for a *decomp* the goal is byte-identical output; semantic equivalence to the original source is what matters. The original source (pinned) has the store before the call. Moving it after changes the source semantics. Not allowed as a "real C move"? The catalog C0505 includes "statement order" — but reordering across a call is risky.

Let me try it anyway to see the score; if it scores 0, I'd need to justify. Actually, if it scores 0, the byte-identical output proves the call doesn't observe the store in this codegen... but the source would be semantically different from the original. Hmm, the decomp's goal is matching the target binary; the "source" is reconstructed. If moving the store after the call produces the target binary, then the original source might well have been written that way. But the pinned source (the tree's) has it before. Since the tree's source is our only evidence, changing the order is a semantic guess.

Let me just test it (a try, not a win unless it scores 0 and I can defend it).

2. Another idea: make the second store's value depend on the call? No.

Let me test the reorder + a couple of variants.
