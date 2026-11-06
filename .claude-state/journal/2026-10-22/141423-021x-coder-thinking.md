---
ts: 2026-10-22T20:14:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iauC7V306CAKuvVFyfxU
---
Hmm, this alloc table is from the .lreg dump (local-alloc stage) — "22 pseudo(s) in the .lreg table". The table shows r72 pri 5625 refs 9 live 48 crosses 3 calls — that's likely self. r77 a0 pri 11739 refs 9 live 23 blk 1 — obj? Hmm.

Where's the addr pseudo? Maybe it's a hard-reg-eliminated thing not in the table, or it's one of r78/r79/r80? Those are 6 refs each, conflicting a1,s0,sp — the movstr dest address? Hmm.

Actually the .greg order line shows only 4 allocnos: 78 79 80 72. So global-alloc's allocation order is r78, r79, r80, r72! That means the three "TIE" pseudos with pri 10909 come first. These must be... the movstr source address? and dest? Hmm, 6 refs each, live 11, 3 deaths.

Wait — the .greg order line gives the order of allocation: 78 79 80 72. r78, r79, r80 have pri 10909, 10909, 10000. r72 (self?) 5625. But the object shows s2=self, s1=addr, s0=obj — three callee-saved.

Hmm, r78/r79/r80 conflict a1,s0,sp. And they "die in 3 places". These could be the movstr temporaries? No...

Let me dump the target's alloc? We can't — we don't have target source. But we have the score-0 body (orig.c) which is identical to target! Dump that and compare tables. That's the direct comparison. Let me do it.
