---
ts: 2026-11-06T12:11:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QX3eqfum44RaH3JOh79L
---
v_both_u18_first = 2 (same). The li/lui swap persists.

OK, this is a genuine sched tie-break wall. Score 2. The sibling func_801810E4 also got 2.

Time: 05:10:57. Item 4 ~15 min. I need ~20 → 05:16. Let me do a few more genuine tries, then write up. 

Let me think about the li a0 one final time. The target has li a0 BEFORE lui v0,0x20. Mine after. 

What if I reorder the source so the unk14 store is LAST among the tail stores but the call is after it? v_u14_before_call = 11. Hmm, worse.

What if I reorder so the unk14 store comes right after the store 0x10 (it does) but the call's arg setup is explicitly before it in source? v_both_argfirst (aa=0x980 before unk14) = 2. Let me check if its li moved.

Actually, all give li at 31. So sched2 always puts lui v0 first.

Hmm. What determines sched2's order? Let me look at sched.c's priority. The `li a0,2432` has no dependents until the jal (far). The `lui v0,0x20` has a dependent sw (soon). sched2 prioritizes insns with more dependents / longer critical path. The lui v0 has a shorter path to a use (the sw). So it's scheduled first. The target schedules li a0 first — maybe because the barrier changes the DFA/scheduling state.

This is really a sched2 artifact. Without the barrier, it's very hard to flip.

Let me accept the wall. Score 2.

Actually, wait — maybe I can make the li a0 have a dependent sooner. If the call's a0 were used earlier... no.

Or make the lui v0's dependent later. If the unk14 store were later (but then the order breaks).

Hmm.

Let me try: what if the unk14 value is 0x200000 but I express it as a subtraction that needs 2 insns (e.g., 0x200000 = something)? That would change the value computation. The target has a single `lui v0,0x20`. So no.

OK. Let me finalize item 4 as WALL, best 2, wall=sched1-birth-order (or sched2). Let me reconsider the tag: the residual is the li a0 / lui v0 order. walls.txt has `sched1-load-order sched1 orders an addiu/lw pair opposite to the target (G20)` and `sched1-birth-order sched1 orders two independent insn births opposite to source (T11 G16b)`. The li/lui are two independent constant loads; the target orders them opposite to source (li a0 for the call comes before lui v0 for unk14, but unk14 is earlier in source). So `sched1-birth-order` fits.

Hmm, but actually, is it sched1 or sched2? The do-while affects cse1/loop notes (early passes), so the difference might propagate to sched1/sched2. The wall tag should describe the mechanism. Let me use `sched1-birth-order` — "sched1 orders two independent insn births opposite to source". But I'm not 100% sure it's sched1. Let me check by dumping the cc1 passes? That's expensive. Let me just use `sched1-birth-order` as the closest tag, or `sched-store-sink` (since the root cause is the missing barrier / store scheduling).

Actually, the ORIGINAL residual (without do-whiles) was the store sink (sched-store-sink, matching the sibling). The do-whiles moved the residual to a li/lui swap. The honest tag: the mechanism is still "sched reorders the tail relative to the barrier", which is sched-store-sink-adjacent. But the specific residual is now a birth-order swap.

Let me use `sched1-birth-order` since the store is fixed and the residual is the li/lui birth order. I'll note in the evidence.

Hmm, but the brief says "wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". `sched1-birth-order` is in walls.txt. Good.

Let me finalize. First, let me update the notes (the best body changed to v_s8_both_dw with score 2, residual li/lui). Actually v_s8_both_dw is the best (score 2, store fixed, li/lui swap). Let me update notes.

Wait — v_s8_both_dw = 2, and v_s8_dw_two = 2. Both score 2. Which is "best"? Both 2. The difference: v_s8_dw_two has the store sink; v_s8_both_dw has the li/lui swap. Both score 2. I'll report best 2.

Let me update the notes to reflect v_s8_both_dw (store fixed, li/lui residual) as the best, since it's a different residual. Actually, let me keep the notes accurate: best = 2, achieved by v_s8_both_dw (store fixed, li a0/lui v0 swap) and v_s8_dw_two (li order fixed, store sink).

Let me rewrite the notes section about the barrier.

Then results row, moves append, and the final log.

Let me update notes.md.
