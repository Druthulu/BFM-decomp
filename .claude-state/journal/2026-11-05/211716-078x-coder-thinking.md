---
ts: 2026-11-06T04:17:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yMydiEGqlH4nqXcmnjH5
---
Mine at 4930: `lw a1,32(s1)` — that's the reload of p (a1) for the final store. Target has `lw v1,32(s1)` at 4944, AFTER the sll/addiu. Mine hoisted the load to 4930 (before the sll). That's one scheduling difference. Also mine's `slti v0,v0,17` at 48e4 is in the bnez delay slot (target: nop at 48e4, slti at 4900). And the register pairs a0/a1 vs v0/v1.

So the main issues:
1. The reload `lw a1,32(s1)` is hoisted above the sll chain in mine; target keeps it after (at 4944).
2. The slti for the next arm is in the bnez delay slot in mine; target has nop.
3. Registers a0/a1 vs v0/v1.

These are all sched1/regalloc effects of the removed fences. The fences in the `< 0x11` arm (lines 59, 61) were exactly to keep the multiply above p's load and the +0x600 below it:
- line 54: store 0xC00
- line 58: `v = *(s32*)(obj+0x1C) * 3 * 32;`
- fence (59)
- line 60: `p = ...unk20;`
- fence (61)
- line 62: `v = v + 0x600;`

Target order: lw p (4924); sh (492c); lw obj->1C (4930); sll; addu; sll; lw p (4944); addiu; sh.

Wait, target: the p load for the 0x1A store happens at 4924 BEFORE the 0x1C multiply. Then the multiply chain. Then the reload of p at 4944, then addiu, then sh.

Hmm, the source order: store 0x1A via raw pointer (line 54), then v = multiply, then p = model (line 60), then v += 0x600, then (line 71) `((Unk*)p)->unk18 = v`.

Target: 
- 4924 lw v1,32(s1)  → p for the 0x1A store (from line 54's raw pointer? line 54 uses `*(s32*)(a0+0x20)` directly)
- 492c sh v0,26(v1)   → the 0x1A store
- 4930 lw v1,28(s2)   → obj->1C
- 4938 sll v0,v1,1; addu v0,v0,v1; sll v0,v0,5  → v = obj->1C*3*32
- 4944 lw v1,32(s1)   → p (line 60)
- 4948 addiu v0,v0,1536 → v += 0x600
- 494c sh v0,24(v1)   → line 71 store

So the target's order matches the source order exactly (store, multiply, p load, add, store). Mine: p load for line 60 was hoisted to 4930 (before the multiply), and the multiply chain uses v0 then a0.

The fences forced the multiply to stay before p's load and the +0x600 after. Without them, sched1 hoists the p load (4930) above the multiply.

To reproduce with real C: create a dependency so p's load comes after the multiply. The multiply uses `obj->1C` (a load from obj+0x1C) and `p` is a load from a0+0x20. Independent. The fence ordered them.

Real C ideas:
- Make p's address computation depend on the multiply result? No.
- Reuse a temp: the multiply's result v and p's load... 
- do-while(0) around the pieces to split EBB.

Try wrapping the multiply in do-while(0), or the p load, to keep order. In item 3, do-while around the var computation stopped the hoist. Here, we want the p load to stay after the multiply. Wrapping `p = ...unk20;` in do-while(0) might prevent sched from hoisting it above the loop boundary.

Let me try a series of do-while placements:
- w1: wrap `p = ...unk20;` (line 60) in do-while.
- w2: wrap the multiply `v = ...;` in do-while.
- w3: wrap both the multiply and p load.

Also the first fence (line 50) in the `==0` arm: mine has the p load for the final store at 48f4 `lw a1,32(s1)` which target has at 494c? Target: 48e8 lw v1,32(s1) for the 0x1A store; 48f4 lw v1,32(s1) for the final store (after the sh), then j with li v0,4608. Mine: 48e8 lw v1 (store), 48f4 lw a1 (final), j 4944, li a0,4608. That looks similar except regs (v1 vs a1) and the delay slot li a0 vs v0. Fine, register naming.

The regalloc difference (a0/a1 vs v0/v1) is likely a consequence of the schedule: the p pseudo and v pseudo get different registers because of the hoist. If we fix the schedule, regalloc may follow.

Let me try the do-while variants.

Note: the do-while around `p = ...` — p is used after the block; the loop-shaped range might affect. Let's test.
