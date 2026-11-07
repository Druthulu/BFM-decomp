---
ts: 2026-11-06T12:09:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R03D1YpBBfTO0MwWu1pA
---
v_both_dwtail = 2 (same). The li/lui swap persists.

Let me look at v_both_dwtail's diff to confirm it's the same swap.

I'm at score 2. The remaining swap is a sched2 tie-break. Let me think if there's any way.

The target: li a0,2432 before lui v0,0x20.
Mine: lui v0,0x20 before li a0,2432.

What if I reorder the source so the call is before the unk14 store? Then the li a0 would be before the lui v0,0x20 in RTL order. But the target has the call LAST (insn 37). If I move the call before unk14 in source, the call would be at ~30 and the stores after — wrong order (the jal would be before the stores). That changes the target match.

Hmm, but wait — what if the call's ARG setup (li a0) is computed early (before the tail stores) but the call itself is last? The compiler might do that if I reference 0x980 early. Tested v_both_argfirst (aa=0x980 before the tail) = 2. Hmm.

Let me look at v_both_argfirst's diff. Maybe the li a0 moved but something else.

Actually, all are 2. Let me check if v_both_argfirst has a different residual.

Let me dump v_both_argfirst's diff.

Actually, I've spent a lot. Let me reconsider: the wall is score 2. The sibling func_801810E4 also got 2. This is a genuine sched2 tie-break wall.

But wait — the sibling's residual was the STORE sink (a different store). Ours now has the store fixed but a li/lui swap. So we're at a DIFFERENT residual than the sibling. Maybe ours is crackable!

Let me focus on the li a0 / lui v0,0x20 swap. 

Idea: make the unk14 value computation NOT be a `lui v0,0x20` scheduled early. What if I compute unk14 from a variable that's set later? 

Idea: what if the unk14 store is a `sw` of a value that's also in a register from earlier? No.

Idea: change the order of the tail's first two statements? The source is unk14 first. If I put 0x18 first, v_both_perm1 = 2 (same). Hmm.

Let me try: what if I compute unk14 LAST in the tail (after unk1C) but keep the call last? v_u14_after1c = 11 (worse). Because the target order has unk14 first.

Hmm. The target's sched order is: li a0, lui v0,0x20, sw unk14, lui v0,0x2, move a1, sw 0x18, sw unk48, jal (delay sw unk1C). 

So li a0 is first in the tail. Mine has lui v0,0x20 first.

What if I make the li a0 depend on the store 0x10 (so it must come after)? It already comes after (both after the do-while). But sched2 puts lui v0 before li a0.

What if I make the lui v0,0x20 depend on something later? 

Idea: use a temp for the unk14 value that's computed from a variable set after the store. E.g.:
```
    s32 t14;
    ...
    do { CAST_WIDTH(0x10) = v; } while(0);
    t14 = 0x200000;
    unk14 = t14;
```
The t14 = 0x200000 is a li/lui into a temp. sched2 might order it differently. Tested v_tail_temps (on store_dw base) = 2. Let me try on both_dw.

Actually, let me look at v_both_argfirst more carefully. Let me dump its diff.

Time: 05:09:32. Item 4 ~13.5 min. Let me continue to ~05:16.

Let me dump v_both_argfirst.
