---
ts: 2026-10-22T20:55:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NQMBHrBRQKJ2cgRgs437
---
Now I see the structure. The `op` is computed inline in the call: `aGsSortLine(&prim, op, 0)`. In the target, the index chain (sll/addu/sll/addu) is between bx's add and ay's add. In mine, ay's add comes before the chain.

Since `op`'s computation feeds the call's a1 argument, sched1 placed the chain after ay in mine.

Target order within the block:
- loads/prim setup
- by, ax, bx (adds)
- index chain (sll, addu, sll, addu)
- ay
- 4 stores
- call

Mine:
- by/ax swapped
- ay right after bx
- index chain
- stores
- call

Hmm, in the target, ay is scheduled just before the stores (its consumers). In mine, ay is scheduled right after bx.

To push ay later, maybe make ay's value needed only by the store (it is). sched1's "birth" priority: insns whose results are needed soon get scheduled earlier/later?

Try adding a 2nd set `ay = (u16)ay;` — that would create a copy. Or declare ay as u32 (the add would be a 32-bit add; the store sh truncates). In gen_n1, ay was u32 → COUNT 4 (extra andi?) — let me look at gen_n1's diff: `by = (u16)by` added, and ay u32? gen_n1 has u32 ay/bx (from the earlier diff: gen_n1 has u32 ay, u32 bx vs gen_o3's u16 ay, u16 bx). So u32 ay gives an extra andi somewhere.

Let me try:
u1: gen_o3 + `ay = (u16)ay;` before stores.
u2: gen_o3 with ax u16 (s16/u16).
u3: gen_o3 with the by/ax statements swapped in source.
u4: gen_o3 with by = out.vy - 0x5D.
u5: gen_o3 with the `ay = ay + 0x75;` moved *after* `prim.x0 = ay`? impossible.

Also: the target's ay add is in the same position as the stores' first operand; maybe the target's source computes `prim.x0 = ay + 0x75` directly (no ay update):
```
prim.x0 = ay + 0x75;  // ay is the old value
```
Then ay stays as out.vx (used later in the second block's prim.x1 = ay — the original value!). Wait, the second block uses ay: `prim.x1 = ay;` — which ay? After `ay = ay + 0x75`, ay is the updated value. The target's second block stores `sh s1,40(sp)` (prim.x1 = ay) with s1 = the updated ay (0x75 added). Let me verify: in the target's second GsSortLine block (1554+), the stores are sh s1,36 / sh s4,38 / sh s0,40 / sh s2,42 — hmm, at 1574-1580: sh s0,36; sh s4,38; sh s1,40; sh s2,42 → x0=ax(s0), y0=by(s4), x1=ay(s1), y1=bx(s2). So ay is the updated value (s1 = out.vx+0x75). Yes.

So ay is updated in place.

Let me try the batch.
