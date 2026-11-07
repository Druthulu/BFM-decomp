---
ts: 2026-11-06T11:39:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oaguPSNKF2728IPA59OI
---
The sched1 dump shows: insn 9,11,13,15 = group A loads; then insn 37 = store D_80126950; then 57 = load A2 (r2), 39 = store D_80126954, 62 = load A2 (r3), 41 = store D_80126958, 67 = load A2 (r4), 51 = parallel (Blk8 copy #1!), 43 = store D_8012695C, 72 = load A2 (r5)...

So sched1 interleaved: loads A, store 1, load A2, store 2, load A2, store3, load A2, Blk8 copy, store4, load A2, then group B loads, ...

So sched1 scattered. The target order is very different.

Interesting: the sched1 output shows insn 51 (parallel = the Blk8 move) placed mid-way. So yes sched1.

For the pinned orig, sched1 would place things differently. Fine.

Now, the key: it's sched1's ordering. The wall tag "global-hardreg-reserve" is about global-alloc though. Here the schedule itself differs, which then affects allocation. Hmm, but the mechanism is: pins create hard-reg dependencies that constrain sched1. So the tag could be `sched1-birth-order` or a new tag. Let me think: `sched1-birth-order` = "sched1 orders two independent insn births opposite to source; reorder moves the other" — not quite.

A new tag `<pass>-<what>`: `sched1-hardreg-pin-dep` — "the pin's hard-reg WAR dependency orders the Blk8 copy after the scalar stores; lever-free sched1 hoists it (priority 4 vs 2)". That's a new tag allowed ("or a new `<pass>-<what>`").

But maybe existing `global-hardreg-reserve` is closer: "the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it". That's about allocation. Here the schedule differs first. Hmm.

Let me check whether the sched1 order difference is caused by the hard-reg pins. In the pinned version, r2 is a hard reg v0; the Blk8 copy (parallel, BLKmode) writes v0/v1? In orig, the copy's operands are hard regs? Let me dump orig's sched1 to confirm.

Let me run hdump for orig.c.

Actually, this evidence is good enough. But let me check the orig sched1 to name the mechanism precisely.
