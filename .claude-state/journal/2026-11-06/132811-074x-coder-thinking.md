---
ts: 2026-11-06T20:28:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gfBu0WsFL8KZYrzLR9OB
---
rank_for_schedule: highest priority; then class relative to last_scheduled_insn; then INSN_LUID (original order). Scheduling backwards, `last_scheduled_insn` is the insn scheduled most recently (i.e., the one at T-(k-1), later in the final order). Class 3 (independent or latency 1) is preferred over 1 (data dependent) and 2.

So the tie-break at T-4 in nolau: after scheduling the call (110) at T-3, `last_scheduled_insn` = 110. Candidates: 103 (sh), 95 (move a0), 108 (const).
- 108 (const): is it in LOG_LINKS of 110 (the call)? Yes, data dependence (the call uses a1) → class 1.
- 103 (sh): independent of 110? no link → class 3.
- 95 (move a0): class 3? The call uses a0 (from 95) → data dependence → class 1.
So classes: 103 → 3, 95 → 1, 108 → 1. The scheduler picks the highest class = 103. Hmm, but the dump shows it picked 108 at T-4. Wait, the dump order: "ready list at T-4: 103 (1) 95 (1) 108 (1), now 108 103 95". Hmm, if it picked 103, the remaining list would be 95 108. The "now 108 103 95" includes 108 and 103 both — maybe the printout is before/after differently.

Let me reinterpret: maybe the line "ready list at T-N: <list>" is the list *after* the pick and additions, and the pick at T-N was made from the previous list. Then at T-3 the list is "110" (picked at T-3?).

Ugh. Let me instead check the final order from the .dbr RTL: 95(move a0), 101(li), 103(sh), 108(const), 110(call). So the const is last before the call. So the scheduler picked: T-1: 116(jump), T-2: 113(v=0x20), T-3: 110(call), T-4: 108(const), T-5: 103(sh), T-6: 101(li), T-7: 95(move a0). Forward: 95,101,103,108,110,113,116. Yes.

At T-4, after the call (110) was scheduled at T-3, candidates were {95, 101?, 103, 108}. The dump "ready list at T-4: 103 (1) 95 (1) 108 (1), now 108 103 95" — this suggests the list before the pick was "103 95 108" and the pick was... the first element 103? Then "now" would be "95 108". But it says "now 108 103 95" which contains 108 and 103. So maybe "now" is the list *after* adding the newly-ready 108? Hmm.

Let me read the dump code.
