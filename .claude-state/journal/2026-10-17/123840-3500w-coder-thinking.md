---
ts: 2026-10-17T18:38:40.224Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm experimenting with ways to give s3 an explicit dependency before the call, trying different statement orderings so the address computation folds into the expected instruction sequence.

Still, I'm not finding a clean explanation — maybe it's a scheduler tie-break issue, where the call and the other instruction (25) have close priorities and luid ordering determines which gets picked first, which could explain why 25 ended up ranked higher.

I'm now considering gcc's sched.c logic around priority adjustment after placing an instruction — specifically how "birthing" instructions (ones that start the life of a register not previously used) get their priority lowered, versus instructions that kill registers getting boosted. This could explain the s3 assignment's scheduling position relative to the call, so I want to try perturbing the birth pattern of the s3 set to see if it changes the ordering.

I'm also considering whether the call could have a dependency forcing it after insn 25 — like if s3 were a call-clobbered hard register creating an anti-dependency, but the target uses $19 for s3 so that doesn't fit. I check whether insn 25 is a memory load (which would create a true dependency with the call), but it's just an address computation, not a load, so that doesn't explain it either.

Looking at the target's prologue sequence more closely, I wonder if s3 is actually used right after the call in an indexed store like `dst[s0-1] = ...`, which would explain the extra instruction count in this scheduling variant.

Rather than keep guessing at source forms, I should actually inspect the scheduler's own ready-list decisions for this block, maybe by dumping the pass with scheduling trace info and grepping for the relevant debug lines.
