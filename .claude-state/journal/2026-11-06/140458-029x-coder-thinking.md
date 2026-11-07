---
ts: 2026-11-06T21:04:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tvySi6SE4gnzu2kDFr8r
---
The lreg dump lists local-alloc candidates. Note register 85 is NOT listed — meaning it was eliminated/coalesced before local-alloc. And `a` (reg/v:SI 4) is also not listed (it's a hard reg user var).

So the merge happened earlier: combine or cse. Let me look at the .combine dump (after combine) — the rtl dump I looked at might be the very first (-dr prints after each pass; first is after expand? Let me identify). The insn numbers 33/35/42 in that first snippet. Let me look at the .combine file around the andi (line 92).

Actually the grep earlier: combine dump line 92 has andsi3 with insn_list 32. Let me view the combine dump around lines 70-110.
