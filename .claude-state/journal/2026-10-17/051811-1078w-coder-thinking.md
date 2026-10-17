---
ts: 2026-10-17T11:18:11.460Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm trying to recall whether cse1's jump-threading logic in cse_insn is what redirected jump 21 to 73, since it has code that follows a chain of jumps and rewrites a conditional jump's target when the outcome along the path becomes known.

So the .cse dump confirms threading happened right after cse1, matching my prediction. But I'm puzzled why the store to reg 73 got replaced across a fresh EBB boundary — cse resets its table at new basic blocks, so pe shouldn't have equivalences there unless the block paths being traced (like "2 to 57" or "2 to 73") span multiple basic blocks in a single extended path that I need to work out.

Checking jump 27's branch to label 57 — it has two uses, so it isn't eligible for the "skip around a block" optimization since that requires a single LABEL_NUSES. That rules out one explanation, so I need to reconsider how the dump's "Processing block from 58 to 73" sequence maps to actual insn UIDs and whether an earlier scan already established the equivalence before reaching that block.

I'm checking the cost comparison that keeps the plus expression over a constant, then tracing whether the mem reference to reg 73 could get rewritten in the store block — but reg 73 isn't in the hash table for that block, so nothing changes there. I should look more carefully at the start of the cse1 dump to pin down what insn 58 actually is.
