---
ts: 2026-11-06T16:53:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6IvZMUEUtvfHfGrFdAsV
---
u16 gives `lhu` — wrong instruction (target uses `lh`).

I've spent ~27 min on item 3. Tries: win0 + 7 (w6) + 5 (w7) = 13. Plus the w7_r1/r2 diffs. To declare a wall I need ≥30 tries and ≥20 min. I'm at 20 min, 13 tries. Let me push a bit more with targeted variants around r1/r2 (which are at 2).

The gap in r1: mine has the t+h4 addu before the +s2 addu. The target has +s2 first.

Idea: change the order of the *statements* so the inner sum is computed first. In r1 the tree is (t + h4) + s2. The RTL order follows. To get (h4 + s2) then +t while keeping r1's tie structure... 

What if I write:
```c
s32 q;
q = t + (h << 4);
q = q + (s32)s2;   // same as r1
```
Same.

What if I introduce the reassociation differently:
```c
q = (h << 4) + (s32)s2;   // inner first (target order)
r = t + q;                // then +t
```
This is the original tree order. The ties: q ties to 81 (h group), r ties to t (t group). Same as the original → score 6.

Hmm, so the tie structure follows from the tree.

Unless... the tie at the outer addu depends on which operand dies first in the RTL. In the original, `83 = 77 + 82` ties to 77 (operand 1). If I write `q + t` (swapping), the RTL might be `(plus q t)` → tie to q. Let me check if gcc canonicalizes: for commutative ops, gcc's RTL usually keeps the source order (or canonicalizes constants last). So `q + t` would give (plus q t). Then the outer ties to q (h group). Wrong direction.

What about `t + q` (current) → ties to t. Right structure, wrong regs.

Hmm, so the original tree gives the right tie structure but the wrong priority outcome; r1 gives the right outcome but the wrong order.

Wait, maybe I mis-analyzed. Let me just try a few more r1-like forms and check if any gives score 0:
1. `(t + (h << 4)) + (s32)s2` → r1 (2).
2. `((h << 4) + t) + (s32)s2` → same tree as r1 (commutative) probably (2).
3. `(s32)s2 + (t + (h << 4))` → (plus s2 (t+h4)): order s2+t? then +h4? Hmm.
4. `t + ((h << 4) + (s32)s2)` with a temp for t? 
5. Use a temp `idx` for the final address and index it.

Let me look at r1's actual full .s to see the order and think.

Actually — here's a thought: r1's order is t+h4 then +s2. The target is h4+s2 then +t. What if I write the C as `(h << 4) + ((s32)s2 + t)`? That's h4 + (s2+t): order sll h4, addu s2+t, addu h4+that. Hmm, the tie structure: the inner (s2+t) ties to t, then the outer ties to h4. Different.

What about `((h << 4) + (s32)s2) + t` — original order (h4+s2 then +t) and the tie: outer ties to... operand 1 = the inner sum's reg (82, dies) → h group! So the outer joins the h group. That's the original expression's behavior? Wait, in the original C `t + ((h<<4)+s2)`, the outer plus is (t, inner). Operand 1 = t. If I write `((h<<4)+s2) + t`, the outer plus is (inner, t) — operand 1 = inner (82). The tie loop would tie to 82 (h group) instead of t!

So `((h << 4) + (s32)s2) + t` might give the target ORDER (h4+s2, then +t) AND a different tie structure (h group grows, t alone). Hmm, that would make the h group bigger → h gets $2. Wrong.

Ugh.

OK, let me try a different approach: maybe the t group's priority can be raised via nrefs by tying the address pseudo. Let me try the r1 form but with the addu order nudged by a temp:

```c
s32 q;
q = (h << 4) + (s32)s2;
q = t + q;      // r1 order? no...
```

Hmm.

Let me just try a bunch of algebraic orderings and see if any hits 0:
a) `((h << 4) + (s32)s2) + t`
b) `(s32)s2 + (t + (h << 4))`
c) `(h << 4) + (t + (s32)s2)`
d) `(s32)s2 + ((h << 4) + t)`
e) with temps: `q = (h<<4)+(s32)s2; r = t+q;` (original)
f) `q = t+(h<<4); r = q+(s32)s2;` (r1 with temps)

Let me batch a-f.

Also, maybe I should reconsider the *other* direction: keep the original expression (right order) and fix the regs by making the h group smaller. The h group {76,81,82} — if 82 didn't tie to 81, the h group is {76,81} nrefs 8. The tie 82→81 happens because 81 dies at the `+s2`. If 81 were used later, no tie. What if the expression is `(h << 4) + (s32)s2` where s2 is added to the shifted value — 81 dies. Can't avoid.

What if h<<4 is computed via a different op, e.g., `h * 16`? `sll` still. What about `(h << 4) + (s32)s2` → `h * 16 + s2`? combine turns it into sll.

What if I write the inner sum as `s2 + (h << 4)`? Then 82 = 75 + 81, operand 1 = 75 (s2, not dead) → no tie! The tie loop: i=1: r1 = 75 (s2), doesn't die → combine_regs returns 0 (source not dead) → continue i=2: r1 = 81 (dies) → tie 82 to 81. Same.

Hmm, the tie loop tries all operands. So 82 ties to 81 regardless.

What if h's shift result (81) is used twice? no.

OK let me just run the algebraic batch. Time-box: 10 more minutes.
