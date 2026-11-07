---
ts: 2026-11-06T10:11:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bLVkL9xjv3iRZAXsukbR
---
In b12: r74 = v1, r75 = v0, r76 = a1. These three have refs=2, live=12 (t, tb, u all local qtys in block 2). Priorities all 1666 (tie). Tie-break: lower allocno wins → r74 first → should get v0! But r74 got v1.

Hmm, "TIE (lower allocno wins, global.c:607)". The order should be r74, r75, r76. r74 → first free reg. If v0 is occupied at r74's birth... but local-alloc processes qtys by priority; at r74's birth (52), v0 might be live due to a hard reg (e.g., the previous `sh v0,26(a2)` result or something).

Wait, live=12 for all three — that's suspicious. They all have "2 refs, 12 insns" — the qty live length includes the whole block? Hmm, maybe these aren't t/tb/u. Let me identify. r74 in the b12 lreg RTL.

Actually in b12, the source is:
t = unk4C; unk6 = t;
tb = unk54; unkE = tb;
unk30 = 0;
u = unk50; unkA = u - 8;

t: 1 def, 1 use, life 2. tb: life 2. u: life 2-4. But the table says live=12 for r74/75/76. So maybe r74/75/76 are NOT t/tb/u; they're something else with 2 refs and 12 insns.

Hmm, "used 2 times across 12 insns" — maybe these are the `t`, `tb`, `u` variables but the "12 insns" counts from first to last use including intervening? t at 52, u at 55-59... if t, tb, u were combined into one qty? Local-alloc combines quantities via copies, but there are no copies.

Wait, maybe r74/75/76 are the three values but live=12 because the block's insn range... Let me just find them in the lreg RTL by offset 76/84/80.

Let me grep the b12 lreg for const_int 76.
