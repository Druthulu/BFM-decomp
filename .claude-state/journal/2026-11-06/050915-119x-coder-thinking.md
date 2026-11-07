---
ts: 2026-11-06T12:09:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kjnC2eDhyOBYIDU9Me9n
---
Worse. Moving unk14 later breaks the tail order. The target has unk14 first (source order). So the source order matters.

The residual is a sched2 tie-break between li a0 and lui v0,0x20. The target orders li a0 first. Mine orders lui v0 first.

Hmm. This is a sched2 priority issue. The `lui v0,0x20` produces the unk14 value; the `li a0,2432` is the call arg. sched2 picks lui v0 first (more urgent for the sw at 32).

To make li a0 first, I need to make it more urgent or the lui less. 

What if the unk14 store's value comes from a variable (init at decl)? Then the lui might be scheduled differently. Tested v_tail_temps (with the store_dw base) = 2. Let me try v_tail_temps on the both_dw base.

Actually, let me reconsider: maybe the issue is that the do-while around the store creates a boundary that forces the li a0 after it, but the tail's internal order is sched2's. The target's tail order (li a0 before lui v0) comes from the barrier preventing... no, the barrier is before the tail.

Wait — in the target, the barrier is at the END of the middle block (after the store 0x10). The tail follows. So the barrier separates the store from the tail. Within the tail, sched2 orders li a0 (30) before lui v0 (31). 

In mine (both_dw), the do-while around the store separates the store from the tail (like the barrier). But sched2 orders lui v0 (30) before li a0 (31). So sched2's tie-break differs. Why? Maybe because the do-while's structure changes the priorities.

Hmm. The target's sched2 has li a0 before lui v0. Mine has lui v0 before li a0. 

What determines sched2's order? Priorities based on the dependency graph. The li a0 is needed by the jal (later). The lui v0 is needed by the sw unk14 (sooner). sched2 schedules by priority = length of the longest path to the end. The lui v0 has a longer path (to the sw and beyond?) Hmm.

Actually, maybe the target's order is due to the barrier's effect on the RTL order (the barrier is an insn, so the tail's RTL comes after it, and sched2 processes in a certain order). Without the barrier (do-while), the order differs.

This is a deep sched2 tie-break. Let me try a few things:
- v_both_tail_temps: temps for the tail values (init at decl).
- v_both_sw14_first: put the unk14 STORE first but compute the value from a temp.

Let me test v_both_tail_temps.

Actually, I already tested v_tail_temps (on the store_dw base) = 2. Let me test on both_dw.

Let me also try: `CAST_WIDTH(s32, (u8*)a0, 0x14) = 0x200000;` (v_both_cast14 = 2, same).

Hmm.

Let me think about the li a0. It's `li a0,2432`. The a0 register. What if the call's first arg is in a different register? No, a0 is fixed.

What if I make the unk14 value computation use a different register (not v0)? It uses v0 (lui v0,0x20). If it used another reg... the compiler chooses v0.

What if the unk14 store's value is 0x200000 loaded from a variable? `s32 t = 0x200000; ... unk14 = t;` → li/lui into a reg. Same.

Let me try a few more and then accept the wall (score 2).

Actually, wait. Let me reconsider: the target's tail order is:
30 li a0,2432
31 lui v0,0x20
32 sw v0,20(s0)
33 lui v0,0x2
34 move a1,zero
35 sw zero,24(s0)
36 sw v0,72(s0)
37 jal (delay sw zero,28(s0))

Mine (both_dw):
30 lui v0,0x20
31 li a0,2432
32 sw v0,20(s0)
33 lui v0,0x2
...

So only the first two swapped. If I could make the li a0 issue before the lui v0,0x20...

The li a0 is `li a0,2432`. What if I make it a `lui a0,0x0; addiu a0,a0,2432`? No, the target has li (addiu a0,zero,2432).

Hmm. What if the call's first arg is a small constant that fits in li (2432 = 0x980, yes li). 

What if I change the call to `func_8002D4C8(0x980, 0)` but with the 0x980 computed as `0x900 + 0x80`? folds.

Let me try: reorder the tail so the call is FIRST (before the tail stores). But the target has it last.

Actually, what if I put the `li a0` computation in a separate statement before the tail? Like `a0 = 0x980` — but a0 is the parameter name. I could use a variable. Tested v_both_argfirst = 2 (same). Hmm.

Let me look at v_both_argfirst's diff — maybe the li moved but something else.

Actually, all are 2. The swap persists.

Let me accept the wall. But it's SO close (score 2). Let me try a couple more creative things:
- What if I make the unk14 store depend on the call's a0? No.
- What if I reorder so the final call comes before the unk14 store but the unk14 store is after the call? That changes the order (target has call last).

Hmm.

Let me try: split the tail into two do-whiles to change the sched regions.

Or: use the `s8 two` trick on the unk14 value? No, it's 0x200000.

Let me try one more: `v_both_dw2` with the do-while around the store placed differently (e.g., around the whole middle block, which fixed the store in v_mid_dw but left the li v1,2 issue). Combining mid_dw with the two do-while...

Actually, v_s8_both_dw uses do-while around two=2 AND do-while around the store. The store is fixed, li v1,2 is fixed, only li a0/lui swap remains.

What if I add a THIRD do-while around the unk14 store? Let me try:
```
do { unk14 = 0x200000; } while (0);
```
That might change the sched region.

Let me test.

Also: `do { CAST_WIDTH(0x10) = v; } while(0); do { unk14 = ...; } while(0);` etc.

Let me test a batch:
- v_both_dw14: + do-while around unk14 store
- v_both_dwtail: do-while around the whole tail
- v_both_dwcall: do-while around the final call

Let me test.
