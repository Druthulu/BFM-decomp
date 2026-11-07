---
ts: 2026-11-06T05:05:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_02203JbOPMFkg1pbWNrK
---
`reg_n_refs[regno] += loop_depth` — a register used in an insn inside a loop gets +loop_depth refs. So each a1 use inside a do-while block gets +1 (loop_depth=1). t2 has 3 a1 uses inside loops → +3. ✓

For r1: the do-whiles wrap the ifs; a1 is not used inside them, but the +1 came from somewhere. Maybe a1 is *referenced* by a USE/CLOBBER at the loop boundary? Line 2067/2315 etc. — these are in mark_used_regs for various insn types. Hmm.

Anyway: to keep a1's refs at 7, no a1 use may be inside a loop.

Can I place the do-while *after* the a1 use? The store `D_80078EA4 += a1;` is the a1 use, and the load to be kept after it is in the following if. So I need the boundary between the store and the if. If I wrap the *if* (r1), the a1 use is outside — good, but the +1 still appeared.

Hmm, why? Let me look at flow.c:2501/2711 — maybe at the loop end, registers live across the loop get +loop_depth? Let me read around 2067 and 2501.

Actually, maybe the +1 in r1 is from a different mechanism: the if body contains a use of... `D_80078EA4` (a symbol → memory, not a register). Hmm.

Let me check r1's alloc more carefully: a1 refs 8. Which insn adds the extra ref? Maybe the do-while around the third block's outer if (line 18) contains the store `D_80078EA4 += a1` inside it! Yes! Look at the source:

```
if ((s16)D_80078EA6 < 0x80) {     // line 18
    D_80078EA4 += a1;             // line 19  <- a1 use INSIDE this if!
    if ((s16)D_80078EA6 >= 0x81) {
```
So wrapping the outer if at line 18 puts the store (a1 use) inside the loop → +1 ref. That explains r1's +1.

So: wrap only the ifs that do NOT contain an a1 use: lines 7 and 14 (blocks 1,2), and for block 3, wrap the inner if (line 21) instead of the outer. Then no a1 use is inside a loop → refs stay 7!

Let me construct: do-while around ifs at lines 7, 14, and 21 (the inner one), plus the t1/t2 fix for the reload.

Wait, but block 3's ordering issue: the first load (for < 0x80) is before the store (correct), and the reload after the store needs to happen. The inner if wrap gives the boundary for the reload (t1/t2 fix already forced the reload via the pointer/cast). Hmm, actually t2 already forced the reload with `*q` and got 114 ins. So the reload issue is solved by t2's pointer trick. The remaining issue is just the register swap, caused by the do-while refs.

So: use t2's body (with the *q inner load) and replace the do-while placement: instead of wrapping all 3 stores, wrap only the ifs at lines 7,14 and the inner if at 21 (no a1 inside), or wrap the stores... the stores ARE the a1 uses.

Wait, but the ordering fix needs a boundary between the store and the following load. If I wrap the if (lines 7,14) — the load is inside the if → boundary between the store (outside) and the load (inside) → fixed. For block 3, the outer if contains the store and the inner if; the inner load (>= 0x81) is inside the inner if. So wrapping the inner if at line 21 gives the boundary between the store (outside the inner if) and the inner load. 

So: wrap ifs at lines 7, 14, 21 (0-based 6, 13, 20). That's r1 minus line 17 plus 20. Let me build that with t2's *q change.

Let me also keep the t2 reload trick (the inner load through a pointer/cast) — actually, with the inner if wrapped in a do-while, cse might not reuse the load anyway (block boundary), so the pointer trick might be unnecessary. Let me test both:
u1: t2 (with *q) + do-while on ifs {6,13,20}.
u2: v1 (direct loads) + do-while on ifs {6,13,20}.

Let me generate.
