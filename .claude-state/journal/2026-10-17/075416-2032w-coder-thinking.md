---
ts: 2026-10-17T13:54:16.173Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm confirming CSE still unifies the expression regardless, so the target needs two separate adds with a call crossing the shared base. If the base pointer were actually a memory load rather than a pure SSA value—say a local whose address gets taken—CSE might not be able to match the two instances across the call.

But I'm realizing that's likely not it: if a0 = mb+24 is computed directly into the hard register before the call, and the call clobbers a0, CSE would need to recompute the expression fresh on the second call rather than reusing a cached pseudo. So the key question becomes whether, at CSE time right after the first call, the earlier pseudo holding mb+24 still lives across the call or gets invalidated.

I'm running through more variations — mb mutated between calls, a function pointer array, implicit pointer conversion, or a derived pointer defined right before the second call — but none quite line up with the target's direct jal pattern. I'll park this line of investigation around try 11 and move on to S13.

Every spelling for S09 has cse folding the second `mb + 0x18` into the first call's pseudo, including c1 where `mb`'s constant is unknown—but the target needs the first add computed directly into `a0`, which no surviving expression can achieve. I'll park S09 and move on to S13.
