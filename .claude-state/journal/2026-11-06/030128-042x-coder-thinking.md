---
ts: 2026-11-06T10:01:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UVn9t9Z7Tzj4ZfLKpeLY
---
The alloc table shows the globals (live across calls) order: 78 80 79 77 76 74.

- r78: pri 30000 refs 10 live 10 — conflicts v0,sp prefers v1,a1
- r80: pri 20000 refs 4 live 4 — prefers v0
- r79: pri 17500 refs 7 live 8 — prefers v1,a1
- r77: pri 10000 refs 5 live 10 — TIE, prefers s0
- r76: pri 8333 refs 5 live 12
- r74: pri 5185 refs 7 live 27 — crosses 1 call

Hmm, which are d and s1ang? r74 (refs 7 live 27) crosses 1 call → that's probably d (live long across call). r76 (refs 5 live 12) conflicts v0,s0 — hmm. r75 is s0 with pri 2857.

Wait, the .greg order line lists allocnos: 78 80 79 77 76 74. These are the allocnos that survive to global allocation? Actually 6 allocnos. The table says r74 crosses 1 call, r75 crosses 1 call too. But r75 (s0) is already assigned s0? "r75 s0 2857 2 7 0 crosses 1 call" — it has a hard reg already (s0), maybe from a preference or it's an arg?

Hmm, this is the *nopin* body. Let me figure out which pseudo is d and which is s1ang. 

The globals that need callee-saved: those live across the call. r74 (refs 7, live 27, crosses 1 call) and r75 (s0, refs 2, live 7, crosses 1 call). r75 already has s0 — that's odd.

Hmm wait, maybe r75 is s1ang and it got s0 because... "r75 s0" hard=s0. That means it was assigned s0. And r74 is d (live 27, crosses call) got... the order is 78 80 79 77 76 74, so r74 is LAST — it gets the remaining callee-saved reg, which would be s1. That matches: d→s1, s1ang→s0.

So s1ang = r75 with pri 2857, refs 2, live 7, and it already got s0. d = r74, pri 5185, refs 7, live 27, got s1.

Wait, why is r75 already s0? Because in the alloc table, "hard" column shows the assigned register. Hmm, maybe r75 is not an allocno but a pseudo that got s0 in local-alloc (live range doesn't cross the call?). But the note says "crosses 1 call". Hmm.

Actually the alloc_table might list pre-assigned. Let me not over-interpret. The key: d (r74) has pri 5185, s1ang (r75) has 2857. So d already has HIGHER priority than s1ang! Yet d got s1 and s1ang got s0. That contradicts "higher priority gets s0 first".

Unless the .greg order 78 80 79 77 76 74 means r74 is considered last, and registers are assigned in that order. But if d has higher pri (5185 > 2857), it should be earlier in the order... unless the order line isn't sorted by pri. The order 78(30000) 80(20000) 79(17500) 77(10000) 76(8333) 74(5185) IS descending by pri. So r74 (d, pri 5185) is last among the globals.

And r75 (s1ang, pri 2857) is NOT in the .greg order line — it's below r74? It's listed after r92 and before r104. Hmm, the table seems sorted by pri descending: 30000, 20000, 17500, 13333, 10000..., 8333, 6666..., 5185, 5000, 2857, 0. So r75 pri 2857 comes after r74 5185.

But the .greg order line says "78 80 79 77 76 74" — only 6 allocnos. r75 isn't there. Yet r75 has hard=s0. Hmm, maybe r75 is a *local* pseudo (allocated by local-alloc) that the table also shows? The "hard" column might be the final assignment from both local and global.

Wait, s1ang crosses a call, so it can't be local-alloc'd... unless the "crosses 1 call" note means its live range crosses a call and thus must be callee-saved, and local-alloc refuses, sending it to global. Hmm.

Let me look at the .lreg table (19 pseudos) and .greg to identify. The alloc_table output says "19 pseudo(s) in the .lreg table; .greg order: 78 80 79 77 76 74".

So the .lreg table has 19 pseudos, and .greg order has 6. r75 must be in the .lreg table (local) — but it crosses a call? Confusing.

Maybe r75 is a hard-reg copy created in local-alloc. Whatever.

Key insight: d (r74) has pri 5185 but gets s1; s1ang gets s0. Why? Because s0/s1 assignment happens in global-alloc in the .greg order. r74 is last in the order (lowest pri) so it gets the last remaining callee-saved register. But s1ang (r75) isn't in the order — so how did it get s0?

Maybe s1ang is actually r76 (refs 5, live 12, pri 8333, conflicts v0,s0). r76 is in the order at position 5 (after 77). Hmm.

Let me identify by reading the .lreg/.greg dumps. Let me grep for the register names or look at the .greg file. The alloc table gives pseudo numbers; I need to map to variables. Let me look at the .lreg file which has the pseudo definitions with line numbers.

Actually, easier: the .greg order 78 80 79 77 76 74 — these 6 are the global allocnos. Two of them must be d and s1ang (the ones live across the call). r74 (crosses 1 call) is clearly d or s1ang. Which of the others crosses a call? The table shows only r74 and r75 with "crosses 1 call". r75 has hard s0 already.

Hmm, so maybe only ONE of d/s1ang is in the global set, and the other is... Wait, both are live across the jal. Both must be callee-saved.

Unless s1ang's live range does NOT cross the call in the RTL! Look at the target: `lh s1,18(v0)` at 38f0 (right before jal at 38f4) and `andi s1,s1,0xfff` at 3908 (after). So s1ang IS live across the call. Unless the load was moved before the call by sched1 and in the RTL (pre-sched) the load is AFTER the call. Yes! In the source, `s1ang = *(...)` is before the u5 = ratan2(...) line, so at RTL generation the load is before the call. So live across.

Hmm, but the alloc dump is from the *nopin* body. Maybe the load order differs. Let me look at the .lreg dump to see the actual RTL for the function, and identify pseudos.

Let me grep the .lreg for "reg 75" or look at its structure. Actually alloc_table.py might print pseudo→line mapping. Let me look at alloc_table.py briefly.
