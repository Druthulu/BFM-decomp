---
ts: 2026-11-07T00:44:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_y36dh3UGFzJvPeI9ZDS2
---
"The scheduler is operating in reverse" — sched1 in 2.7.2 runs BACKWARD (schedules from the end of the block to the start). That explains the trace order.

OK. Given the reverse scheduler, the "blocking" of the load means something in reverse.

This is getting deep. Time check: item 2 started 17:36; it's now maybe 17:55? Let me check the time. I've spent a while. Let me get the time and decide.

Practical approach: try a batch of real-C variants targeting the two aspects, especially ones that create a *dependence* between the load and the following stores, or that change the block's start.

Actually — here's a thought experiment: the target's order has the load right after the call, before the stores. In the *reverse* scheduler, insns are scheduled from the end. The stores (58,61,64,67) are at the end-ish; the load (53) is before them.

What if I make the val load's *use* (the addiu / the final store) come earlier in the source? The final store `D_801B7A84 = val + 1;` is last. That's fixed by the target.

Hmm, what about the *p* variable: `*p = 0` uses p (set at 45). 

What if the load and the stores are in a different order in the source AND sched1 preserves it? In w10 (load after stores in source), the result was still ORDER 6 — the load ended up after (same as the target? no, the target has the load before).

Hmm wait, w10 = load after the three stores (before *p=0). The score is 6 ORDER. Which order does w10 produce? Maybe the load is now in a different wrong place. Let me check w10's diff.

Actually, let me reconsider the problem completely. Maybe the answer is that the *real* source uses a different statement order such that the RTL order at sched1 is: load, stores — and the reverse scheduler's blocking works out to the target order. Since mine (load first in source) gives stores-then-load after sched1, the source order that yields the target order might be... the reverse! I.e., the source has the stores BEFORE the load, and sched1 (reverse) hoists the load.

w10 did that (load after the three stores, before *p=0) → score 6. Let me look at w10's diff to see the actual order.
