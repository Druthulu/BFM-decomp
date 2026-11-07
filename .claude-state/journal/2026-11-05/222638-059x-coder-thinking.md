---
ts: 2026-11-06T05:26:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_quUZtX7gz33swm6Fx3w7
---
The dump doesn't show the actual hard-reg assignment clearly (that's in the .s or greg). Let me instead look at the .s file directly to see n1's asm and compare with a1. Actually I already have the diffs.

Let me think about local-alloc priority. In local-alloc (gcc 2.7.2), for each basic block it allocates the qtys that die within the block; qtys live across block boundaries go to global-alloc. The priority is based on `floor_log2(n_refs) * ... ` roughly `((n_refs * 1000) / live_length)`. Registers allocated in order of priority: $2 (v0), $3 (v1), $4 (a0), ...

Hmm wait, actually local-alloc's `reg_alloc_order` for MIPS is probably $2,$3,$4,...,$15? Let me check the target assignment: iVar1→v1, iVar2→a0, tmp→v0. That means priority order: tmp > iVar1 > iVar2. tmp gets v0, iVar1 v1, iVar2 a0.

In n1 (merged), the merged pseudo got v0 and iVar1 got v1. Consistent.

In a1 (HImode copy), the order became: tmp? Let's see a1's asm: iVar1→a0, iVar2→v1, tmp→v0. So priority order: tmp > iVar2 > iVar1. Hmm.

So a1 changed iVar2's priority above iVar1. Why? Because in a1 the copy is `tmp = (s16)iVar2` which is a sign-extend — maybe that made iVar2 live longer or increased refs.

OK so the key is to get iVar1's priority above iVar2. In the target, iVar1 (8 refs/18 insns in n1's numbering = reg 73) vs iVar2 (6/6 = reg74) vs tmp (20/16 = reg75). Priority ≈ refs*1000/live: tmp = 20*1000/16 = 1250; iVar1 = 8*1000/18 = 444; iVar2 = 6*1000/6 = 1000. So iVar2 (1000) > iVar1 (444) → iVar2 should get v1 and iVar1 a0. But in n1, iVar1 got v1!

Hmm, so local-alloc's priority formula may differ. Let me check gcc 2.7.2 local-alloc.c. Actually the priority is computed in `local_alloc` via `qty_compare`/`qty_compare_1`: 
```
qty_compare_1: 
  tem = qty1->n_refs - qty2->n_refs ... 
```
Let me look at the source: tools/reference/gcc-2.7.2/local-alloc.c.

Actually, in n1, maybe iVar2 and tmp WERE merged (cse), so reg 74 might be something else. Let me check: reg 74 used 6 times across 6 insns; reg 75 used 20 across 16. tmp is used a lot (in both arms). iVar2 used in the branch tests. Hmm.

Let me just look at the n1 .s and the pseudo mapping... hard.

Different approach: empirically, in n1 the allocation is iVar1=v1, merged=v0, and everything else matches except iVar2/tmp. If I can find ANY spelling that keeps the copy without changing iVar1's register, I win.

a1 changed it. Let me look at other anti-cse mechanisms:
- `tmp = iVar2;` + do-while — a3/a4 didn't keep the copy.
- HImode cast — kept copy but changed priority.
- What about `tmp = (s16)iVar2;` where iVar2 is *declared* s16? b1: score 8 — maybe it merged again? Let me check b1's diff.

Let me also try: `tmp = iVar2;` but declare `tmp` as s16 (b3: 8, probably merged/extra).

Let me check b1's diff quickly.
