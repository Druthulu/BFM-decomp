---
ts: 2026-11-06T03:21:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BZ2fBldog8SqCzqB83U2
---
Still 56. Hmm. So the struct store didn't force the reload. Let me check mine's asm and where the reload is missing.

Maybe the issue is different: mine caches D_80126B78 in a2 across the store; the target reloads. With the struct store, cse should invalidate... but maybe cse doesn't because the *global* D_80126B78 is a fixed address and the store is a varying struct — the `fixed_scalar_and_varying_struct_p` says a varying struct store MAY clobber a fixed scalar? Let me check cse.c's invalidation.

Actually, let me look at where the barrier sits relative to the store and the second load. Source:
```
obj = unk20;
obj[0x14] = obj[0x14] + (unk2A - D_80126B78[0x12]);   // uses D_80126B78
[barrier]
unk2A = D_80126B78[0x12];                              // uses D_80126B78 again
```
The barrier is after the store. For cse, the store to obj+0x14 may clobber D_80126B78 (the global variable holding a pointer), so the second load must be re-done. But cse's memory table for D_80126B78 (a SYMBOL_REF-based address) vs the store's address (a varying reg+const): if cse thinks they may alias, it invalidates. Without the barrier, cse did NOT invalidate (mine reused the value). 

Hmm, maybe the issue is not cse but the *register allocator*: the compiler loaded D_80126B78 once and kept it in a register (a2) because the two uses are close. The barrier insn forces a reload because the asm clobbers memory.

Real-C to force the reload: make the store's address *possibly* alias D_80126B78 in a way cse recognizes. cse's memory invalidation: `cse_insn` calls `invalidate_memory` for a store using `rtx_addr_can_trap_p`? Let me look at cse.c 2.7.2 for how stores invalidate the table.

Actually, maybe the relevant pass is `flow`/`combine` (which might CSE the two global loads). Let me dump the passes for nopin and see where the second load disappears. Let me dump and check .cse/.cse2/.combine.
