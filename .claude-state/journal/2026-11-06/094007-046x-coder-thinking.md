---
ts: 2026-11-06T16:40:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mtvKsTySmrr8yur6tT9d
---
Hmm, w1 (no launder) = 11, and w2 (dead reset) = 11 too. So the dead reset didn't work the same. Let me see the diff for w1 and w2.

Note: the launder is `__asm__ __volatile__("" : "=r"(pv));` — an asm with an output. In gcc 2.7.2, an asm with an output but no input... The value pv is defined. The asm is at the very end (after the last call). The dead reset `pv = 0;` placed after func_80016638 — but wait, in w2 I placed it right before the closing `}`. Let me check placement: orig.c's last lines are the ot store, func_80016638, asm, `}`. So w2 has `pv = 0;` after func_80016638. Same position.

But flow deletes the dead store — yet the launder asm is NOT deleted (asm is volatile, kept). So the difference: the asm's 2nd set survives to sched1 (killing the birthing boost), while `pv = 0` is deleted by flow before sched1 — so it doesn't kill the boost. C0414 says flow deletes it BEFORE sched1 and it costs zero bytes — but then how does it break cse? It breaks cse (which runs before flow). Here we need to affect sched1, which runs after flow. So the dead reset is too early.

Hmm. So to kill the sched1 birthing boost, we need a second set that survives flow but emits no bytes. Options:
- Make pv's second set *live*: e.g., use pv after. That would emit code.
- Make the second set a real store to pv that's needed: pv is a local; if we use it in a way that's optimized to zero bytes but survives flow...

What does sched1's birthing boost key on? sched.c: a SET of a register with a single set? "the birthing boost" gives a single-set insn a priority boost. If a value has 2 sets, no boost. The second set must exist at sched1 time.

Real-C: `pv = *(u32*)p;` then later `pv = something;` where the second set is live but costs 0 bytes? If pv is used after the second set, it emits the set (li or move). Unless the second set is the same value and cse folds it... then only one set.

What if the second set is a *copy* that gets coalesced? e.g., `u32 pv2 = pv;`? That's a different pseudo.

Hmm, what about the "dead-reset" placed such that flow keeps it because it's not dead? If pv is read after the reset in a zero-byte way... e.g., `pv = 0;` then the final `}` — dead. 

Alternative: make pv live-out? No.

What if the second set is `pv = pv & 0xFFFFFFFF;`? Folds.

What about making pv `volatile`? Then the first load and the store are volatile — changes code (no scheduling?).

Let me look at what the 11 differences are. Maybe the launder does something else. Let me diff w1.
