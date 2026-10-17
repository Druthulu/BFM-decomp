---
ts: 2026-10-17T10:33:37.746Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
I notice arg0 lands in a2 rather than a1 in the target, while in the free body it's a1 — that's odd given the tree only pins flags/d to specific registers. This must be because the global pseudo for arg0 is allocated separately across blocks, and the pinning of flags/d somehow shifts which register arg0 gets assigned.

Local allocation runs before global allocation, and locals occupying a1 within a block can force arg0 out of it — in the tail block, `prev` claims a1, pushing arg0 to a2, whereas the free body's tail block doesn't have `prev` competing for a1. I'm also noting that other values like the 4096 literal and mfhi result get their own register slots, and the target does an abs-with-different-destination move plus reuses a0 across two expressions. Since my brief only forbids pins/asm/volatile/builtins (not reuse), I should explore making `d` itself a reused/global variable — similar to how `diff` spans the if-else blocks — to see if that avoids the forced register tie that's been limiting my search results.

If `d` is global rather than local, local-alloc skips it entirely and leaves its placement to global-alloc, which assigns registers based on conflict analysis rather than the `combine_regs` tying that applies to local pseudos. I'm now tracing through how global.c in this gcc version handles instruction-level conflicts — specifically whether input deaths are processed before output births at a single insn — to determine whether `d` and `v` would actually conflict in an abs-expansion insn, since that determines whether `d` could land in v0 while `v` stays in v1 as the target code does.

The abs expands as a single branch-containing instruction, so d's life stays within one block unless I reuse a variable that spans blocks—like reassigning `diff = abs(v)`, since diff is already set earlier in block 2 and used elsewhere, making it a global pseudo that gcc 2.7 would allocate consistently to the same register (v0) across both lives.

Prior search attempts only tried renaming v; reusing diff for d is a new angle worth testing directly, along with checking a's global status too. I'll copy body_free.c into my working directory and write variant scratch files to try this out experimentally.
