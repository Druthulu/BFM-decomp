---
ts: 2026-11-06T16:52:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_psCVgsJjjUQqGXhCtxrS
---
Very close! Now the registers are right, but the *order* of the `addu s2` differs:
- r1: mine has `addu v0,v0,s2` at 15 (after the t+h sum) but the target has `addu v1,v1,s2` at 14 (before).
- r2: mine has `addu v0,v0,s2` at 11, target has it at 14.

Let me get the full picture. Target:
```
2734: sll v0,s0,0x1     t
2738: lh v1,112(s1)     h
273c: addiu s0,s0,1
2740: sll v1,v1,0x4     h<<4
2744: addu v1,v1,s2     +s2
2748: addu v0,v0,v1     t+h
274c: lhu a1,0(v0)
```
So the target computes (h<<4)+s2 then t+that.

r1 `(t + (h << 4)) + (s32)s2`: mine computes t + (h<<4) first, then +s2. The addu order differs. Score 2 = one insn moved.

r2 `(t + (s32)s2) + (h << 4)`: mine computes t+s2 first. Also differs.

Hmm, both give the correct registers now! Because the reassociation changed the tie structure. Now I need the right instruction order.

The target order is exactly the original C `t + ((h << 4) + (s32)s2)`. But that gave score 6 (wrong regs). The reassociated forms give the right regs but the wrong order.

Can sched1 reorder? The score 2 suggests only the addu position differs. Let me look at r1's full diff: "insert addu v1,v1,s2 at 14, delete addu v0,v0,s2 at 15". So mine:
```
13: sll v1,v1,0x4
14: addu v0,v0,v1   (t+h)
15: addu v0,v0,s2   (+s2)
```
target:
```
13: sll v1,v1,0x4
14: addu v1,v1,s2
15: addu v0,v0,v1
```
So in r1, the sum order is (t + h4) + s2, giving addu v0,v0,v1 then addu v0,v0,s2. The target has (h4 + s2) + t.

So I need the target's order AND the correct registers. The correct registers came from the reassociation (which changed the tie groups). 

Hmm! Wait: maybe I can get the target order with a different reassociation that still changes the ties. The target order corresponds to `t + ((h << 4) + s2)`. That's the ORIGINAL expression (score 6, wrong regs).

So: with the target expression, the regs are swapped; with the reassociated expressions, the regs are right but the order differs.

Interesting. Let me think: can I write `t + ((h << 4) + (s32)s2)` in a way that changes the tie structure but keeps the instruction order? The instruction order comes from the tree: `t + (X + s2)` where X = h<<4. The RTL order: X (sll), then X+s2 (addu), then t+that (addu). 

To change the tie structure without changing the tree order, I could introduce a temporary for the inner sum:
```c
s32 q;
q = (h << 4) + (s32)s2;
... *(u16*)(t + q) ...
```
That's the same tree (maybe with an extra variable). The tie structure: q's reg ties to the h<<4 reg, then the outer sum ties to t or q depending on the tie order.

Hmm, in the original, the outer addu `83 = 77 + 82` has both 77 and 82 dead; the tie loop tries operand 1 (77) first → ties 83 to 77 (t group). That's the target's tie structure. And the h group {76,81,82}. So the target tie structure = the original expression's tie structure. And the priority gives h first → wrong regs.

But the reassociated forms changed the tie structure (the outer sum ties to the h chain instead), giving the right regs but wrong order.

Wait, r1's tie structure: `(t + h4) + s2`: 
- 83 = 77 + 81' (t + h4): both 77 and 81' die → tie 83 to 77 (operand 1).
- 84' = 83 + 75 (s2): 83 dies → tie 84' to 83.
So the t group = {77, 83, 84'} (3 regs). The h group = {76, 81} (2 regs). Priorities: t group nrefs 12, h group 8 → t wins → $2! That's why the regs are right.

And the target has the t group = {77,83} (2 regs) and h group = {76,81,82} (3 regs), yet t got $2. Contradiction with my priority math... unless the qty lives differ.

Hmm wait, maybe in the target, the h group's qty nrefs is lower. Let me recompute with the ACTUAL RTL for the original expression:
- h group {76,81,82}: nrefs = reg_n_refs(76)+reg_n_refs(81)+reg_n_refs(82) = 4+4+4 = 12.
- t group {77,83}: 4+4 = 8.
pri_h = floor_log2(12)*12/18 = 3*12/18 = 2 (life 18: birth 6, death 24? hmm).

Wait, I need the exact birth/death in the 2*insn_number units. Let me recompute with the block insn numbering (including notes? no, notes don't count):

Block 1 insns in order (from the dump): code_label 20 (n=1), 23 (n=2), 30 (n=3), 25 (n=4), 35 (n=5), 37 (n=6), 39 (n=7), 41 (n=8), 33 (n=9), 45 (n=10), 46 (n=11), 49 (n=12), 51 (n=13), 53 (n=14), 55 (n=15), 60 (n=16), 61 (n=17).

Births = 2n: 78→4, 76→6, 77→8, 81→10, 82→12, 83→14, 84→16, 86→20, 88→22, 89→32.
Deaths: wipe_dead_reg sets death = 2*insn_number? Let me check wipe_dead_reg.
