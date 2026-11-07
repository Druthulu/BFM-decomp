---
ts: 2026-11-06T21:10:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Z09HedMALmp98J6upRs5
---
All 4. The a0/a1 swap is stubborn. Time spent ~13 min. Let me try to get the global-alloc dump to see allocno priorities. Actually let me use `-dg` with extra verbosity? GCC global.c has a debug flag? There's `-dg` which dumps RTL after global-alloc. Maybe there's a way to print allocno priorities: search global.c for "debug" prints. Let me grep for "allocno_n_refs" prints or `fprintf`.

Alternatively, I can instrument by compiling a small variation and see which one flips. Let me test the actual launder to confirm it flips (score 0 with only the launder kept and barrier removed?). That would confirm e's refs is the mechanism. Let me create a candidate that keeps the launder but drops the barrier: if it scores 0, then the launder is what fixes a0/a1 and barrier removal is fine.
