---
ts: 2026-11-06T17:11:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2QCvsNcgcu38ucCKAu9Q
---
In the orig (pinned) cse: line 321 `(if_then_else (ge:SI (reg/v:SI 77)...)` — the branch tests the pseudo 77 (q), NOT the temp. So even with the pin, the branch tests q. Let me check what pseudo 86 is at line 131 (probably an earlier branch).

So in the pinned version, cse keeps the branch on q(77) because the temp is a hard reg ($16).

Confirmed: the mechanism is cse's make_regs_eqv canonicalization. With a pseudo temp, cse makes the temp canonical (pseudo preferred over hard v0), rewriting the branch to the temp; the target needs the temp to be a hard register (the pin).

Let me now wait until 20 min and record the WALL. Actually, let me try 3 more creative variants while waiting:
- b43: make the temp's last use within the EBB by using the temp only for the shift and a different var for the subtraction: `n = q; if (q<0) n = q+3; m = n >> 2; m = m << 2; m = (q - m) << 16;`
- b44: `n = q; if (q<0) n=q+3; n = (n>>2)<<2; m = (q-n)<<16;` (one expression) — b12 tried similar.
- b45: put the two velocities in a `switch(0)`? no.

Let me do b43 and b44 and then record.
