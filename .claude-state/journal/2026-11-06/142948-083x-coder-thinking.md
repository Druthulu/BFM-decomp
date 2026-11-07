---
ts: 2026-11-06T21:29:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cZ6f5xGmevoTtoe0UmQd
---
Tie-break 5: "choose insn with lowest UID". Hmm, in our case the picks at T-3: {60 (uid 60), 55 (uid 55), 63 (uid 63)} → picked 63 (highest UID!). Hmm, but the order is reverse-scheduling, so "first one with the largest potential..." etc.

Anyway: the UID order! The insn UIDs are 55 (move), 58 (li), 60 (store q), 63 (li 1), 65 (store a). The scheduler picks... at T-3 it picked 63 (highest UID among {60,55,63}? no, 63 is the highest).

Hmm, in reverse scheduling the "first in final order" = last scheduled. The final order was 58, 60, 55, 63, 65, 70. The UIDs are in increasing order in the C order: 55 < 58 < 60 < 63 < 65 < 70. The target's order is 55, 58, 60, 63, 65, 70 — exactly UID order! Mine is 58, 60, 55, 63, 65, 70 — 58 and 60 before 55.

So the scheduler moved 55 later. Why? The tie-break at T-3: ready = {60, 55, 63}; picks 63 (highest UID? that's the tie-break "lowest UID" applied in reverse?). Hmm.

Wait, in reverse scheduling, the "first one with the largest potential" — the ready list order in the log is "60 (1) 55 (7f000001) 63 (7f000001)". The picks are 63, then 55, then 60.

The final order is the reverse of the picks: pick order 70, 65, 63, 55, 60, 58 → final 58, 60, 55, 63, 65, 70.

For the target we'd need the picks 70, 65, 63, 60, 58, 55 → final 55, 58, 60, 63, 65, 70.

So 55 must be picked LAST (after 60 and 58). At T-3, the ready list is {60, 55, 63}; 55 is ready. The scheduler picks 63 (tie-break). Then at T-4, {55, 60} → picks 55. To pick 60 instead, 55 must have a lower tie-break rank.

Tie-breaks: (1) lowest conflict cost, (2) longest path to end, (3) kills most registers, (4) conflicts with most ready insns, (5) lowest UID.

"longest path to end of bb": the move's path to the end is... it feeds the store (65) and the call (70), which are at the end. Its path length might be longer than the store-q's.

Hmm, and the log's "(7f000001)" marker vs "(1)": 0x7f000001 might be a priority with the "dead" flag... Actually in sched.c, `INSN_PRIORITY(insn)` for 55 and 63 is 0x7f000001? That's odd. Maybe the dump prints `priority` differently.

Let me look at how the log line is printed: "ready list at T-3: 60 (1) 55 (7f000001) 63 (7f000001)". Hmm, 0x7f000001 = 2130706433. That might be INSN_PRIORITY with the sign bit... Actually INSN_PRIORITY is an int; 0x7f000001 = 2130706433 ≈ INT_MAX/16. Hmm.

Wait, in sched.c, `priority()` sets INSN_PRIORITY; for insns with no dependents (like the call 70), the priority is 0x7fffffa3-ish (the log showed "insn[70]: priority = 2147483555"). For 55 and 63, priority 0x7f000001 — also huge. Hmm, those are the "dead" or "barrier" markers?

Actually, maybe INSN_PRIORITY stores `(priority << 16) | flags`? Let me look at the dump code around line 2680.

This is a deep rabbit hole. The practical question: can I steer it with C? The tie-break uses UID (lowest UID wins) and other properties. The UID order is the RTL generation order: 55 (move) < 58 (li) < 60 (store). The target wants UID order (55 first). The scheduler's picks are reverse-UID for equal priorities... but the final order mine is 58,60,55 — not reverse UID (would be 60,58,55).

Hmm.

Let me try a different tack: make the move's UID *larger* than the store's by moving the `a = arg0` statement *after* the q-store in C. Then the UIDs would be: li 3072, store q, move, li 1, store a, call — i.e., the move after the store. In reverse scheduling, the final order might then be the UID order = li, store q, move, ... — same as mine. Not helpful.

What if the C order is: q-store first, then a = arg0, then a-store, then call? The UIDs: li(3072), store q, move, li 1, store a, call. The scheduler would produce... maybe the same.

Hmm, the target order is 55, 58, 60 — the move BEFORE the li. For the scheduler to emit that, the move must be scheduled last among {55,58,60}.

Since all priorities are equal, the tie-break "longest path to end" matters: the move feeds the store (65) and the call (70). Path length: move → store a (65) → call? Actually 65 and 70 both depend on 55. The "path to end" for 55 = 1 + max(path of dependents) = 1 + max(path(65), path(70)). path(70) = 0 (the call is last), path(65) = 0 (nothing depends on it). So path(55) = 1. For 58 (li): 58 → 60 (store q) → nothing → path(58) = 1. Equal.

Tie-break 3: kills the most registers. The move (55) has REG_DEAD (reg/v:SI 72) — a0 copy kills reg 72 (arg0's pseudo)! Yes: `(insn 55 60 63 (set (reg/v:SI 4 a0) (reg/v:SI 72)) (expr_list:REG_DEAD (reg/v:SI 72) (nil)))`. So 55 kills 1 register. The li (58) kills 0. So the tie-break "choose insn that kills the most registers" would prefer 55... but it picked 58/60 before 55.

Hmm, in reverse scheduling, the tie-break chooses which to schedule *later* (closer to the end)? I'm confusing myself.

OK. Practical approach: try C variants and see. Let me try:
1. Make the move kill fewer registers: e.g., if arg0 (reg 72) is used *after* the move, the move doesn't kill it. In the then-block, after the move, arg0 isn't used (the call uses a). If we use `arg0` in the call instead of `a`, the move wouldn't kill 72 (since arg0 is used later at the call). That's w2-ish (no a variable, call arg0) — score 3, the move at 27.

Hmm, w2's move was at 27 (just before the jal) and the store used s0. Because a didn't exist.

2. Keep `a` but use `arg0` somewhere after the move (e.g., in the store `*(u16*)((u8*)arg0+0xb8)=1` — that's w1! In w1, the store uses `a` and the call uses `a`. Hmm.

Let me try: `a = arg0;` then the store uses `a`, the call uses `a`, but ALSO use arg0 in a dead way? No.

3. What if the move's source is not the same pseudo that dies? E.g., `a = (void *)arg0;` — same.

Hmm, the "kills the most registers" tie-break: in the log, the pick at T-3 was 63 (li 1, kills 0). So killing registers didn't win.

Let me look at the actual tie-break code to understand which one applies. Let me read schedule_insn's ready-list selection (lines 2621-2700).
