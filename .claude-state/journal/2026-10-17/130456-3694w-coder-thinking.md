---
ts: 2026-10-17T19:04:56.572Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm thinking about how the compiler's dead branch removal pass eliminates the redundant move since it sees a0 already equals s0, but to defeat the reorg's backward redundancy check I need something between the move and the call that breaks its ability to track that a0 and s0 remain equal.

I'm wondering if the real difference is that s0 isn't a plain copy of a0 but depends on something reorg can't prove equal — like s0 being set through an asm block or a different load path, so reorg's redundant_insn backward scan for an identical pattern simply fails to find a match and the move survives in the target version.

I tried variations but got the same result each time. I'm settling on this as the likely explanation: the dbr/reorg pass deletes the first call's `move a0,s0` as redundant since a0 already holds the argument and s0 was set equal to it at entry, with the assembly only obscuring that equality.
