---
ts: 2026-10-17T14:09:27.729Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm thinking about register allocation ordering — whether placing the load for const1 late versus val's load affects which value survives scheduling, considering how sched2's forward pass might reorder things depending on which virtual register each value occupies.

Looking at the a3 case, the registers actually match the target exactly, but the ordering of instructions is off — my version puts the load and li after three symbol stores, while the target puts them before. This suggests the register assignment is correct, but sched2 isn't hoisting those two instructions above the stores, so I need to figure out what dependency or priority is blocking that movement given there's no memory aliasing issue between the load and the stores.

Thinking about backward list scheduling here: it fills from the bottom by priority (longest path to end), so the store at the end gets placed first, then addiu, and the load only becomes ready once those are placed. For the load to end up above all the stores, the stores would need higher priority than the load, which seems backwards from what I'd expect given the load's latency requirement.

Tie-breaking in rank_for_schedule falls back to instruction ordering, so whatever order sched1 originally output matters for how sched2 replicates it—if sched1 placed the load early due to some other effect, sched2 just preserves that order rather than recomputing it from scratch.

For local-alloc, it's a question of priority math: comparing the "val" pseudo's priority (refs times log2 refs, divided by its life range) against the constant's priority, and figuring out what life length the value would need to have in order to win out and get allocated before the constant does.

I'm trying to pin down val's lifetime in insn-number terms, thinking through how load placement and n_sets affect scheduling without triggering the birthing boost. I should check the perm2 results more carefully to see whether the score-6 entries are failing on REG or ORDER categories.

I'll check perm2's best results by category to see if any ordering trades the register swap for an order difference instead.
