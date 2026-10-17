---
ts: 2026-10-17T13:53:28.340Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm wondering if the original code accessed the matrix through a separately named symbol rather than an offset from the base pointer, which would explain why the register holds base+24 instead of a direct reference.

I'm also considering whether mb was assigned once at the top of the function, before the loops, making the two calls' pointer expressions hash identically under CSE even though they're in different blocks — which would still predict unification, not the divergence actually seen in the target.

Maybe the discrepancy comes from the call arguments having different effective types or indirection in the original source, rather than purely from CSE behavior.

Looking more carefully at cse_insn's lookup logic: within a block, if mb's constant equivalence isn't known at the second call, the hashed expression itself should still match P's entry in the same expression class, which would force unification. So the only way they'd diverge is if something breaks that hash equivalence between the two blocks, not within a single one.

Maybe the two calls are actually separated into different cse scopes—perhaps by a loop body executing once, or some conditional structure that the disassembly doesn't make obvious. Or perhaps the original source had two separate array index expressions, like `D_800AF630[0x18]`, passed to two different function calls, and gcc's optimizer treated them differently for some other reason.

Another thought: maybe the pointer offset calculation was wrapped in an inline helper function, which GCC could expand only under certain optimization settings, producing distinct instruction patterns for each call site rather than a shared cse result.

I'm also wondering whether the argument expression being a literal constant could change how expand_call handles register loading, bypassing the usual pseudo-register precomputation entirely and loading the value directly for one of the calls.

I'm trying to figure out how s0 ends up holding the base address with the +24 offset — maybe mb is a reused variable, first set to D and later reassigned to pkt, which would explain why s0 gets repurposed as p0 right after the two calls.

All eight variations fold to the same result. I'll try two more structural approaches: assigning `mb` once at the top of the function, and merging `mb` with the later `p0` local.
