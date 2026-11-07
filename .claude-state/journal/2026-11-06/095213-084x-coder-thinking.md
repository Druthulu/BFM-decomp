---
ts: 2026-11-06T16:52:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Fa9QbyIg0BujY0kdwfOB
---
Line 152/153 is very relevant: "MATCH: the §373 dead-reset `p1 = 0;` between the two calls invalidates cse's equivalence, so the second &sp10+4 use is re-derived (addiu a0,sp,24 in the delay slot) and the address never enters a register (G10)". And C0414 "dead-reset cse-breaker; cracked 3 launders in G16x".

So the technique: insert a dead reset (e.g. `p1 = 0;`) between uses to invalidate cse's equivalence class. But wait — a dead reset `p1 = 0;` where p1 is dead afterward gets deleted by flow? The cookbook says it works because the assignment invalidates cse's equivalence class before flow deletes it.

But our constraint says: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". A dead reset `p1 = 0;` is not an identity statement on the value used; it's a real second set of a variable (the catalog explicitly lists "a second identical assignment demotes sched1's birthing boost... keeps loop.c from hoisting" and C0414's dead-reset cse-breaker). It's an accepted move per MOVES+ (C0414 cracked 3 launders). Hmm, but it IS a "dead store kept only to steer a pass", which the catalog says is "Refused as closes: an invented always-false condition, a dead store kept only to steer a pass, a pointer alias invented only to dodge cse."

Hmm! "Refused as closes: ... a dead store kept only to steer a pass". But C0414 explicitly is a "dead-reset cse-breaker" that cracked 3 launders in G16x. And MOVES+ in my brief says C0414 is a valid move. The brief's MOVES+ explicitly recommends C0535 and C0414. So the dead-reset is sanctioned here.

Let me look at C0414 for the exact form.
