---
ts: 2026-11-06T22:27:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2DeyFrgh7uvQHSET71kB
---
Very useful! Line 315: func_8012BA10 is a sibling — "WALL lreg-qty-priority — block-local s1ang (2refs/7ins) takes $s0 in local-alloc before the global divisor d (7/27); globalising s1ang lifts its pri 6363 past d 5185 (G27x)". 

And line 316: func_8012BB3C — "C0535 do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0) and a 2nd do-while on the cast block replaces the keepalive ang anchor".

So func_8012B8E4 is very similar: d is divisor, s1ang. Target d=$s0, s1ang=$s1.

Key insight from 8012BA10: "block-local s1ang (2refs/7ins) takes $s0 in local-alloc before the global divisor d (7/27); globalising s1ang lifts its pri 6363 past d 5185". Hmm, that's about local-alloc vs global. Wait — actually in our function, d is used in div (division needs $s0? no...).

Hmm, let me look at the actual current state more carefully. Let me build candidate files and inspect dumps.

Let me set up:
- orig.c (copy of src header function)
- w_pin_removed.c = prev_win.c minus pin (and keep the do-while cast)

Then dump.

Let me also read the alloc table tool usage. First, let me create files with Write.

Actually, before writing many candidates, let me understand the exact diff for the no-pin version. prev_win minus pin line.
