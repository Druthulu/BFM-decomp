---
ts: 2026-10-22T20:54:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QZCXeEm18ql1I7eozmsu
---
Mine: ax(1520), by(1524), bx(1528), ay(152c), index chain, stores.
Target: by(1520), ax(1524), bx(1528), index chain, ay(153c), stores.

Differences:
1. by vs ax order swapped.
2. ay's add is before the index chain in mine, after in target.

Both are sched1 decisions. The target's sched1 put ay late (after the index chain) and by before ax.

In the target, the `ay += 0x75` insn is right before the stores (it feeds prim.x0 = ay, the first store). In mine, it's early. Why? The target's ay add was scheduled late, probably because of its priority (low) vs the index chain (high). In mine, ay's add was scheduled early.

The difference could be due to the *types*: in mine ay is u16; the add is `addiu s1,s1,117` and the store `sh s1` (needs a truncation? u16 store of an int). Hmm.

The prior coder's variants: gen_n1 (u32 ay/bx + by=(u16)by) had COUNT 4 with an extra andi. gen_o3 (u16 ay/bx) has ORDER 4.

Ideas to change the schedule:
- Make `ay` u32 and `bx` u16 (mixed).
- Make ax u16 as well.
- Add `ay = (u16)ay;` (a 2nd set) to delay it.
- Move the `prim.x0 = ay;` store order.

Since the residual is only scheduling, the prior coder's many variants likely explored this. Let me check which variants got 4 and what they are:
gen_n1,n2,n3 (4), gen_o2 (4), gen_o3 (ORDER 4), gen_q3 (4), gen_r2/r3 (4), gen_g1/g2/g4/g5 (6), etc.

Let me diff a few of the 4s to see the variety tried. gen_n1 vs gen_n2 vs gen_n3, gen_o2, gen_q3, gen_r2, gen_r3.
