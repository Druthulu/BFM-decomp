---
ts: 2026-11-06T10:41:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VJKIlGkHMDxgh6K0HfzA
---
dw2: order is right now, but v0/v1 swapped: t in v1, address in v0. Interesting! So in dw2 the store order is fixed but the register assignment swapped.

In v_dw (single load wrapped), the regs were right (no pairs) but the store position wrong.

So the two constraints interact. In dw2 the load t got v1 and the address v0. Why? local-alloc priority: in the same block, the first allocated qty gets v0. Hmm.

Target: load t into v0 (first), address into v1.
Mine dw2: load into v1, address into v0.

Local-alloc assigns hard regs to pseudos in priority order (qty priority = refs * live length). The address pseudo and t both in the same block. Target (barrier-split) has them in different blocks! With the barrier, t is in block B (alone with the store...). Hmm.

Wait, in v_dw (load wrapped alone), no register pairs were reported, so t was v0 and the address v1. Good. In dw2 the load and address are in the same block → local-alloc gives v0 to the address pseudo (higher priority?) and v1 to t.

So we want: block split after the load, keeping t in the load's block and the address in the next block. v_dw does exactly that, but then the store got sunk.

In v_dw, mine order: load (block B); then block C: lui/addiu v1, ori v0, sw v0,196, li, sw v1,88? Let me get the exact full listing to see where sw 88 went.

From the diff: target 31 has sw v1,88; mine has it at 34. So mine block C: lui, addiu, ori, sw 196, [li?], sw 88.

Hmm. sched1 in block C moved the sw 88 later. To keep it early, maybe it must be in the same block as the lui/addiu and before the ori. sched1 reorders by priority: the store's latency... The store to 88 depends on the lui/addiu. The ori/sw to 196 depends on the load (block B). 

Actually, what if we split the block *after* the unk58 store instead: do { t = unkC4; unk58 = ...; } while(0) — that's dw2, which keeps the order right but merges... no wait, dw2 has the load and store in one block, and the RMW outside. The regs swapped because the load and the address are in the same block.

What we want: load in block B, address+store+RMW in block C, and within block C the store before the ori/sw. That's v_dw, where the store sank after the ori/sw.

Hmm, why did the store sink? In block C: instructions are lui v1 (addr), addiu v1, sw v1,88, ori v0,2, sw v0,196. sched1 orders: it lists ready insns by priority. The store sw v1,88 has a dependence on addiu; the ori depends on the load (already done). Both ready at the same time. sched1's priority may favor the ori (higher priority due to... the load is older). So it emits ori/sw first then sw 88.

To force the store earlier, we could give it higher priority: e.g., make the store's value used later? Or use the address variable later? Hmm.

Alternative: put the `sw 88` in block B with the load: do { t = unkC4; unk58 = ...; } while(0) is dw2 (same block → regs swap). Unless we split differently: do { unk58 = ...; } while(0); t = unkC4; ... no, order.

What if we use two do-whiles? do { t = unkC4; } while(0); do { unk58 = ...; } while(0); unkC4 = t|2; That gives block B: load; block C: addr+store; block D: ori/sw. In block C the store is alone with the address → no sink issue; block D has ori/sw. The regs: t in block B, address in block C → separate blocks, good (v0/v1 as target). And the store in its own block right after the address computation.

Let me try that: v_dw4.

Also try wrapping the unkC4 RMW in a do-while too.

Let me generate both variants.
