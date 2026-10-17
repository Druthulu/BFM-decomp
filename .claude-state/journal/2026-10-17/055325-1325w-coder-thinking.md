---
ts: 2026-10-17T11:53:25.486Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm counting only real instructions, which means an extra RTL insn before flow analysis gets removed or emits nothing later. Global alloc runs after local-alloc using live-length data from flow, but I need to check whether local-alloc's equivalence updates or combine's later deletions actually touch reg_live_length—combine likely leaves it unmodified.

I'm trying to pin down which merged or copy insn combine eliminates while flow still counts it, exploring candidates like sign-extension pairs or ternary-vs-branch rewrites of the min computation, though those tend to produce different RTL rather than equivalent counts. I'm also considering whether bumping reg_n_refs via an extra use in a later block could push r323's priority threshold to the needed length of 609.

Looking at how g.sz1 and related pseudos get referenced across the stsz3/stsz4 cases, I'm trying to figure out which of the seven uses push r321's priority above 230, but suspect many of these references are frame-address loads that CSE treats cheaply rather than real pseudo uses, and asm operands likely force register allocation regardless—making it hard to find a change that doesn't alter generated code elsewhere. I'm starting to think the real answer lies in how the original PsyQ gte macros were written.

Comparing live lengths (609 vs 608), I suspect the original source had one extra insn somewhere in the loop body that both explains problem B's scheduling priority shift and extends the live range of r321/r323 across the loop head—possibly an extra wz copy that combine later eliminates. My earlier attempts at inserting s16 copies to replicate this made things worse rather than better.

I'm going to test a set of variant tweaks on the free body base (without the barrier or levers), trying small changes to the wz handling to see if any produces exactly the extra insn needed to match the target without disturbing other counts.
