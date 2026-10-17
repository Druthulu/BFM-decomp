---
ts: 2026-10-17T17:07:18.725Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm checking whether the constant OR expression needs to be forced into a register since it's not a valid immediate, and comparing how the original code pinned that value in a hard register versus a pseudo with a short lifetime inside the loop.

Looking at register pressure across the loop variables, I count nine live values competing for s0-s8, which pushes something to spill — and the key insight is that the mask value's hoisting out of the loop is what's stealing the slot the tag constant needs. If I can prevent the mask from being hoisted, the tag constant should get its own register outside the loop instead, matching the original's behavior. I'm now considering making the two masking operations distinct so the compiler treats them separately rather than merging and hoisting them together.

Trying restructuring the load order so the mask lifetime shrinks to just the two adjacent and operations, loading *otp before the mask set and storing after — but that still spans four instructions, so I'm reconsidering whether the savings estimate itself might only be 2.

I'm wondering whether the threshold actually depends on loop_has_call and the number of non-fixed registers, since MIPS reserves several registers (zero, at, k0, k1, gp, sp) leaving roughly 25 usable ones to factor into that formula.

With a loop of ~35 instructions, a hoist threshold using lifetime 2 would clear 35, meaning any constant reused at least twice gets hoisted automatically. That makes the mask constant with two uses an inevitable hoist candidate, unless CSE in this gcc version only merges constant pseudos under specific equivalence conditions when expanding a bitwise-and operation.

I'm trying to figure out how to prevent CSE from merging the two uses — maybe by inserting a basic block boundary between them, since CSE operates per extended basic block, though a label there would feel unnatural. Alternatively, rewriting the second use as a shift-based expression instead of referencing the constant directly might avoid the merge. I'm leaning toward combining loop-constant-hoisting with nonzero-bit tracking for blockSize, and noting a configuration with one pin removed and three others kept as worth recording.
