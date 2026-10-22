---
ts: 2026-10-22T06:29:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_BmjQUboV5JKeYQxs7psL
---
Now the results.tsv row. Format: `dir file func kinds result best tries wall evidence` (tabs).

dir = func_80191020__ov_SC06_018_jr_8019059C
file = src/ov_SC06_018/ov_SC06_018_jr_8019059C.c
func = func_80191020
kinds = launder
result = WALL
best = 2
tries = 531
wall = dbr-delay-fill-2ndset
evidence = "gcc: the vol 2nd set (u16 cast = 1 andi) is ready before the bne, so the delay slot takes it, not the sll copy the target speculates; 192 ins = 192, 2 differ"

Let me count the evidence chars: roughly 140. Let me make it ≤140.

"gcc: the vol 2nd set (u16 cast) is ready before the bne, so the delay slot takes its andi, not the sll copy the target speculates; 192 ins = 192, 2 differ" — let me count: roughly 149. Trim:

"gcc: the vol 2nd set (u16 cast = 1 andi) is ready before the bne, so the delay slot takes the andi, not the target's sll copy; 192 ins = 192, 2 differ" ≈ 143. Hmm.

"gcc: the vol 2nd set (u16 cast, 1 andi) is ready before the bne, so the delay slot takes the andi, not the target's sll copy; 192=192 ins, 2 differ" ≈ 140. Let me just write something ~135 chars:

"gcc: the vol 2nd set (u16 cast = 1 andi) is ready before the bne, so the delay slot takes the andi, not the sll copy the target has; 192 ins, 2 differ"

Count: let me count in python when writing.

Let me append the row with a small python script (to control the tabs).

Also the moves.md line:
"launder | func_80191020 | WALL dbr-delay-fill-2ndset — the vol 2nd set that restores the multiply order is ready before the bne, so the final pass parks its andi in the delay slot where the target speculates the sll copy (G14)"

Let me write both with python.
