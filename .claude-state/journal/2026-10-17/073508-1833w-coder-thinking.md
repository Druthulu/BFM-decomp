---
ts: 2026-10-17T13:35:08.634Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm trying to trace why the store ends up using register a0 instead of s0 — it looks like the move instruction gets emitted before the store, so by the time the store is generated during RTL scheduling or CSE, the value has already been copied into a0 and that's the register reference used for the offset store.

Since the original code pins s0 as a hard register, there's no such propagation, so the question becomes whether reordering the stores or changing how the final call argument is derived (maybe deriving it from a pointer offset rather than the raw variable) could force the compiler to keep using s0 instead of substituting a0.

Maybe I should just try permuting the store order directly — storing at 516 before 512, matching the target's sequencing with the delay slot, or precomputing a pointer for the 0x204 store before the call instead of relying on cse ordering.
