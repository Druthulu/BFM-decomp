---
ts: 2026-10-17T12:03:16.630Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I'm realizing the address of D_801D59F0 gets rematerialized after the call rather than staying in s0, likely because free's mp variable is copy-propagated and cse shares that pseudo across the call with later uses of the same symbol — so the natural fix is calling func_800233CC directly on D_801D59F0 instead of through mp.

Normally cse1 would merge the lui/addiu pseudos for repeated uses of the same symbol in one EBB even across calls, since cse doesn't care about calls — so something else is preventing the merge. It's possible the call argument constant is loaded straight into the hard register a0 rather than going through a shared pseudo, which would explain why cse has nothing to propagate back into s0.

The target rebuilds `&D_801D59F0` after the call, keeping it in s0 since that `mp` pseudo is reused for the later store's address. I'll pass the constant directly as the argument so it loads straight into a0.
