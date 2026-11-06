---
ts: 2026-10-22T20:32:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ryV6dx3rbfBMdPye83nj
---
Interesting: even `&m[0]` gives 19 (the base pseudo is created by the movstr and reused). So the identity spelling doesn't even help. Good — that removes a temptation and strengthens the wall evidence.

So the movstr dest pseudo is reused by cse for the call args, period, whenever the calls' address equals m. The only way to get the target's per-call remat is to have the calls' address be a constant *not* materialized in a register — which happens when there's no movstr (score-0). And without a movstr, the source base isn't kept.

But w1 (movstr + calls via the pinned src) gets 2. So there's a third mechanism.

Hmm, in w1 the calls use the pinned hard reg, and gcc emits addiu once. The target emits addiu 3 times. What if the call args use a *fresh non-pinned* pseudo that is single-set and dies at each call... that's not possible with one expression.

What if each call has its own *separate* address variable, each set once right before its call:
```
int *p1, *p2, *p3;
p1 = m; RotMatrixX(..., p1);
p2 = m; RotMatrixZ(..., p2);
p3 = m; RotMatrixY(..., p3);
```
cse would equate p1=p2=p3 (same constant) and probably keep one. But maybe each is a separate pseudo (different registers) → 3 single-set pseudos each dying at its call → local-alloc gives a1 to each → `set a1, fp+16` per call, and cse might not merge them because... it would merge (they're all fp+16). But w8 (3 sets of one mp) gave 19 with an extra reg — meaning cse did NOT merge the sets (multi-set → global → s-reg). With 3 distinct variables p1/p2/p3, cse's constant table would equate them to the constant fp+16 and fold... but the movstr dest pseudo already holds fp+16 in a register, so cse replaces p1/p2/p3 with that pseudo → 19 again.

Unless the copies p1=m happen *before* the movstr. Hmm.

Let me try the 3-variable variant anyway (cheap).

Also another idea: make the call args a *cast of an int variable that is set from m right before each call*, with 3 separate int variables (i1,i2,i3)? Same issue.

Another angle: what if the movstr dest address is *not* fp+16 because we copy into m via an offset: e.g., declare `int m[9]` and copy into `*(Mat32 *)(m + 0)`... same address.

What if the copy is into m but the call args are `m + 0` where the RTL form is `(plus (reg m_base) 0)` vs the movstr's `(reg 80)`? Identity → same.

I think this is the wall: the movstr dest address pseudo is reused by cse for the call args; only a lever (launder/pin) prevents it.

BUT w1 got 2 without a launder! w1 uses the pinned src for the calls. Hmm, so a lever-free body scores 2. The remaining 2 is a reload/flow artifact of the pinned hard reg being reused across calls.

Can I make the pinned src NOT reused across calls? The calls use src (hard $5). GCC thinks a1 survives calls. If instead the calls used a *different* hard register... no.

What if between the calls, src is set to a value that gcc can't keep? e.g. `src = (int *)m;` before X, and for Z/Y... w5 (3 sets) = 19 — because the extra sets made gcc create a *non-hard* value? Let me look at w5's disasm to understand.
