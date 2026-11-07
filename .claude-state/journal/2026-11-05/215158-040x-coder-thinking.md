---
ts: 2026-11-06T04:51:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_L2O0zzxCe2P5xZMeWE8U
---
Priority is based on LOG_LINKS (data dependencies) toward... Actually LOG_LINKS points to insns this insn depends on (predecessors). priority(insn) = max over predecessors of (priority(pred) + cost - 1). So priority counts the length of the dependence chain ending at this insn. Insns with long dependency chains have high priority. The store's address chain: lui -> addiu -> store. The store depends on addiu and on the value? The value is the addiu. The store also has a memory dependence maybe on nothing. priority(store) = priority(addiu)+cost-1 = ... So the address chain has priority ~2. The load chain: lui currentLoc -> lh -> and -> sll -> addu -> lw -> ... long chain. So the load chain has higher priority and should be scheduled first. Yet a1 scheduled the store address at 140 before the currentLoc load at 148. Hmm, contradiction.

Unless the store address insns were placed by *local-alloc* or *reorg*, not sched1. Or sched1 isn't run? Let me check the gcc flags: -O2 in gcc 2.7.2 runs -fschedule-insns? Actually in 2.7.2, -O2 includes -fschedule-insns2 but not -fschedule-insns? Let me check the build recipe flags. The moves mention sched1 explicitly, so it runs.

Wait — maybe the order isn't sched1 but the *initial* RTL order influenced by local-alloc's reloads. Hmm.

Let me approach empirically. Maybe there's a much simpler crack: make `D_800C7C64` store use a `s32 *` variable declared as the LAST declaration so birth order changes? Or maybe the target's order can be achieved by making the store address *not* a constant: e.g., `s32 *q = &D_800A2E20; D_800C7C64 = q;` where q is declared with other variables at top. b4 tried a block-scoped q = 17.

Try: declare `s32 *q = &D_800A2E20;` at the top (in declaration order after p) and `D_800C7C64 = q;`. Then the address computation is born at declaration time (early in RTL) and might schedule differently.

Also try making the store address come from `p` arithmetic: `D_800C7C64 = &D_800A2E20;` unchanged.

Let me also consider that maybe the target order comes from *combine* merging `lui/addiu` into the store? No.

Let's test a g-batch with q declared at top and other permutations.
