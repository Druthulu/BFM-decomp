---
ts: 2026-11-06T06:10:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8FZnmeVLDGfeXAhu5I5j
---
The .greg order: 78 77 134 140 72 167 73 80 74 75 76. Hmm, these are the "regs to allocate" in order? The tool says `.greg order` = allocation order. r72 = the param a0 (refs 70, live 219, pri 19178). r73 (refs 9, live 35, pri 7714) = probably the loop pointer s2. So order: r78 (pri 30000), r77 (24000), r134, r140, r72 (param!), r167, r73, r80...

Hmm wait, so the param r72 is allocated before r73 (loop ptr). But the result had the param in $17 (s1), not $16. That's because r78/r77/r134/r140 (all pri ≥ 20000, prefers v0/v1, GR_REGS or none) took caller-saved regs first but that doesn't affect $16. Hmm, then r72 should get the first free callee-saved = $16 (s0). Unless r72 has a conflict with s0 (its conflicts list: v0,v1,a0,a1,s0,sp!). It conflicts with s0!

Ah, that's the key: r72 conflicts with s0 — because the function... hmm, where would a0 conflict with s0? Perhaps there's a hard-reg use of $16 somewhere. Wait, `conflicts v0,v1,a0,a1,s0,sp` — conflict with s0 means some instruction has a hard reg s0. Hmm! Where from? Maybe the pin in the TU? No — this is the candidate TU with my body substituted; no pin. Hmm, but the TU has other functions! alloc_table shows "79 pseudos" — for func_801804A0. Hmm, conflicts with s0 could come from a function call clobber? No, s0 is callee-saved and not clobbered by calls.

Wait, maybe r72 isn't the param. Let me look at the full table for r72/r73/r80/r74 etc. Let me print more of the table and also the order-line explanation.

Also the register assignment: since the .greg dump doesn't give final assignment, the tool prints "-" for global allocnos. The actual final: a0→s1.

Hmm, but why does r72 conflict with s0? Maybe because there's a `move s0, a0` in the prologue... no, conflicts arise from insns where a hard reg is used.

Hold on: maybe r72 IS the loop pointer? refs 70, live 219 — that's a long-lived, heavily-referenced pseudo = a0 (55 uses, but refs counts both def and uses... 70). And live 219 of 281 insns. Yes r72 = a0 param. It crosses 24 calls. And r73 = 9 refs live 35 — the loop pointer? But the loop ptr is inside the loop; live 35 insns.

Hmm, wait: with the goto loop, loop weighting is gone, so the loop pointer has 9 refs.

Now the order 78 77 134 140 72 167 73 ... means r72 is allocated 5th. By then which regs are taken? The first four are GR_REGS-or-none (v0/v1 prefs), so they take caller-saved. Then r72 gets the first free... $16? But the final has a0 in s1.

Unless r72 has a copy preference to s1? Preferences for r72 aren't shown in this line. Let me see the .greg dump directly for the order line and preferences. Let me grep the greg dump around r72.
