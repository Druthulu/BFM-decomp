---
ts: 2026-11-06T13:40:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iFVZ7leMbmhOY56tMFKy
---
Target (case 1, the `unk1C == 4` block):
```
308c: bne v1,v0,30cc
3090: li v0,2          (delay slot)
3094: sh v0,52(s0)     unk34 = 2
3098: lw v0,32(s0)     unk20 load
309c: nop
30a0: beqz v0,30c4
30a4: li v1,4096      (delay slot) k = 0x1000
30a8: sh v1,24(v0)    unk18 = k
30ac: lw v0,32(s0)
30b0: nop
30b4: sh v1,26(v0)    unk1A = k
30b8: lw v0,32(s0)
30bc: nop
30c0: sh v1,28(v0)    unk1C = k
30c4: jal func_8012E88C
```

Mine (w_b1): 
```
118: bne v1,v0,30c8
119: (delay: ?)
120: lw a0,32(s0)
121: li v0,2
122: beqz a0,30c0
123: sh v0,52(s0)
124: sh v1,24(a0)
```
So mine puts the unk20 load FIRST, then li v0,2, then the beqz, and the store sh v0,52 is in the delay slot of the beqz, and the store to 24(a0) after.

Target has li v0,2; sh v0,52 BEFORE the load.

This is sched1 sinking the `sh v0,52(s0)` (a store) below the load. The barrier prevented it (a memory clobber orders memory ops).

Real-C: make the store non-sinkable. The store is `unk34 = 2`. The load is `unk20` (offset 0x20). They don't alias, so sched1 can reorder freely.

Options:
- do-while around the store (C0535 EBB split) — but sched1 is per basic block; does a do-while create a block boundary for sched1? Earlier in item3, the do-while around `cc = bb+8` DID fix a sched1-ish hoist. Hmm, in item3 it was a cse1 EBB split that changed the RTL (maybe it changed which insns cse merged, not the scheduling). Actually in item3 the do-while split cse's EBB, so the load's *equivalence* wasn't propagated... hmm, the load got hoisted by sched1 though.

Let me just try the do-while variants for B1.

Variants for B1:
1. do { unk34 = 2; } while (0)
2. do { unk34 = 2; k = 0x1000; } while (0)
3. do { unk34 = 2; k = 0x1000; if (unk20 != 0) {...} } while (0)
4. do { k = 0x1000; } while (0) after the store
5. reorder: put `k = 0x1000;` before the store? Target has li v1,4096 in the beqz delay slot (after the load), so k's birth is later. The store unk34=2 is before the load.

Hmm, the key is the STORE before the LOAD. sched1 orders memory ops? On MIPS, sched1 has `true_dependence`/`anti_dependence` using alias info: a store to s0+52 and a load from s0+32 — different offsets, same base. If the base is a pseudo/reg with no alias info, the scheduler may assume they don't conflict (different constant offsets). So it can swap them.

To force the store before the load with real C: make the load depend on the store? No.

What if the store and load are both to `((Unkstruct_800B5CB8 *)param_1)` — they are. The scheduler still reorders.

Hmm, what if we make the load's address depend on the stored value? No.

The do-while (C0535) splits cse1's EBB; maybe that changes the RTL (the load is not CSE'd with the earlier loads?) which then affects scheduling. In item3 it worked. Let me just try.

Also, another idea: swap the source order — put the `if (unk20 != 0)` block BEFORE the `unk34 = 2;` store? Then the store would be after the block; target has it before. No.

Or: assign `unk34 = 2` via a local temp? Same store.

Let me test the do-while variants for B1.
