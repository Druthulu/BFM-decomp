---
ts: 2026-11-07T01:19:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eexfIRKMsbq9FFwSyDXt
---
Now append the two moves.md lines. Then final verification.

Time now ~18:21. Item 2 needs until 18:29 — I'll do a few more tries after the moves append.

moves.md line format: `kind | func | MATCH: move / WALL tag — mechanism (P1x)`.

Line 1: `launder | func_80177940 | WALL callee-saved-order — global-alloc pri p=r72 14refs/34live 12352 first of s-bank -> $s0; target p=$s3 pin-forced ($16/$17/$18 hold s0,s1,s2); 132 lever-free bodies, best 41 (P1x)`

Line 2: `pin | func_8017E98C | WALL sched1-argcopy-hoist — sched1 hoists a0=r72 above the 0x204 store, local-alloc equivalence rewrites the pseudo base to a0; pinned base is hard $16; 70 lever-free bodies, best 1 (P1x)`

Use printf >> with tabs? The format shows " | " separators. Let me match the existing lines' style (they use " | " with spaces). Let me append with printf.
