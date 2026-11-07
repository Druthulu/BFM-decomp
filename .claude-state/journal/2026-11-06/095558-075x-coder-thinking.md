---
ts: 2026-11-06T16:55:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GyL52S6qm3USKYJEDXZI
---
30 scored tries now (20 + 10). Best = 2 (w7_r1/r2/w8_b/w8_f/w9_r1).

Time: 09:53 + some. Started item 3 around 09:47? Actually item 3 started after item 2, around 09:44. Now ~10:00. ~16-20 min on item 3. The rule says a WALL needs ≥20 min AND ≥30 tries. I have 30 tries but maybe not 20 min. Let me check the time and continue a couple more minutes with a few more ideas to be safe.

Let me try a couple more targeted ideas:
1. r1 with the inner h4 computed before t (statement order): move the h load before t but keep the r1 expression.
2. r1 with `s2` as the inner addend in a temp computed early.
3. The original expression with a `q` temp for the inner and `t + q` but q declared as a `u32`? changes types.

Actually, let me think about the ORDER issue in r1 more concretely. r1: `(t + (h << 4)) + (s32)s2`. The RTL:
```
sll v1,s0,1      t
lh v0,...        h
sll v0,v0,4      h4
addu v0,v0,v1    h4 + t
addu v0,v0,s2    + s2
```
target:
```
sll v0,s0,1
lh v1,...
sll v1,v1,4
addu v1,v1,s2    h4 + s2
addu v0,v0,v1    t + (h4+s2)
```
So in r1 the inner sum is (h4 + t); in the target it's (h4 + s2).

What if I write `(t + (h << 4))` but compute it as `((h << 4) + t)`? Same tree.

Hmm, what if I make the *outer* sum's second operand the h4 chain, i.e., `(t + s2) + (h << 4)`? That's w7_r2: mine computes t+s2 early (at 11) then +h4. The target computes h4+s2 then +t.

None matches.

What if the target's tree is actually `t + (h4 + s2)` and the register allocation came out right because of a different *scheduling* of the h load? I've assumed the lreg order = a,h,t (mine). If the original's lreg order were different, the priorities could differ.

Let me try to force a different sched1 order by adding a dependency. For example, if the h load's address computation depended on t or a... it doesn't.

What if the h load is written as `*(s16 *)((u8 *)s1 + (t - t) + 0x70)`? gcc folds t-t.

What if the address is `(u8 *)s1 + 0x70` computed before the loop? That would hoist the address (a pointer temp), changing the insns (extra). Hmm, the target has `lh v1,112(s1)` with an immediate offset, so no address temp.

OK. Let me also consider: maybe the original source had `h` as a **s16** and the target's `lh` comes from a HImode load with a sign-extend folded. Let me look at w6_s16's RTL: it scored 6 (same swap). So no.

Given the budget, let me wall item 3 with best 2.

Wall tag: the mechanism is local-alloc qty priority: the h group (3 tied regs, nrefs 12) outranks the t group (2 tied regs, nrefs 8), so h takes $2; the target needs t in $2. The plain-C bodies that flip the tie structure (reassociating the sum) fix the registers but change the addu order. New tag: `lreg-tie-priority-sum`. Or reuse an existing tag? walls.txt has `lreg-qty-priority` ("local-alloc qty priority (refs/live length) gives the hard reg to the other pseudo (G22)"). That fits! The h group has more refs (3 tied regs = 12) so it gets $2; the target needs the t group. I'll use `lreg-qty-priority`.

Best = 2.

Let me record: results row + moves + notes, and win.c = the best body (w7_r1). Hmm, for a WALL the brief says best = lowest score. Should win.c be the best body? The DONE WHEN only requires win.c scoring 0 for MATCH/PARTIAL. For a WALL, I'll copy the best (w7_r1) to win.c as evidence.

Actually, wait. Let me reconsider whether to keep pushing: best 2 is tantalizingly close. Let me try 2-3 more clever variants while I'm here (time permitting).

Idea: the target's order is h4+s2 then +t. What if I write the expression with the h4+s2 inner AND make the t group bigger by tying the outer sum to t AND adding another tie? In the original structure the t group is {77,83}. To make it 3 regs, the outer sum 83 could be used in another tied op. What if the address is computed in two steps: `idx = t + q; ... *(u16 *)(idx + 0)`? The +0 folds. `*(u16 *)(idx)` no tie.

What if the final `+ a` (the addu a1,a1,a0) ties to the address? `86 = 84 + 78` — 84 is the lhu output (memory), no tie with 83.

Hmm.

What if the u16 load is done via a pointer: `p = (u16 *)(t + q); a1 = *p;` — no.

OK, what about making the h group smaller by changing the inner sum to not tie: `(h << 4) + (s32)s2` — if s2 were a *variable that dies*, the tie might go to s2. s2 is live across the loop, doesn't die. If I used a *local copy* of s2 inside the loop, e.g. `s32 s2b; s2b = (s32)s2;` — an extra move. No.

Alright, wall. Let me check the time and record.

Actually, hold on. Let me try ONE more thing: the `t` variable is `s32 t;` and assigned `t = s0 << 1;`. What if I declare `t` as `s32 t` but assign `t = s0 * 2;`? Combine makes sll. Same.

What if `t` is computed AFTER the h load in source (a, h, t)? That's w6_tlast (score 8). Hmm.

What if the h load is INSIDE the expression: `*(s16*)((u8*)s1 + 0x70)` used directly twice? no.

Let me finalize the wall. Time check.
