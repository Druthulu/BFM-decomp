---
ts: 2026-11-06T17:05:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_StcY1aQxdyTaB4DeqDEa
---
At .cse (first cse pass), cse swapped: `78 = v0` and `77 = 78`, and the branch tests 78. So cse canonicalized the copy: q(77) and n(78) were merged with n as the canonical, and the branch now tests n. In the target (pinned), cse couldn't merge because n is a hard register.

So the fix: prevent cse from merging q and n. cse merges a copy `n = q` and rewrites uses. To stop it, the copy must be "non-canonical": e.g., if q is used before the copy or n has other uses... cse's `make_regs_eqv` chooses a canonical register based on uses/live range. Here it chose n (78) as canonical and rewrote q's uses to n.

Why? `make_regs_eqv(reg1, reg2)` — it picks the one with more uses or a hard reg. Both pseudos have similar uses. Hmm.

Cse.c:840 make_regs_eqv. Let me read it — maybe there's a rule we can exploit (e.g. the register that's live longer wins).
