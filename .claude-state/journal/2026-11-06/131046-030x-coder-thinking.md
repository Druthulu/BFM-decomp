---
ts: 2026-11-06T20:10:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZgLjQKh3RFirUlw5ZTKl
---
No change — the dead store was likely deleted before loop.c (by cse1) or the hoist still happened. Let me check whether the dead store survived to loop.c: dump vD and look at insn_count (29?) and whether -1024 still moved.

Actually maybe cse1 deletes it. Let me check quickly with the dump of vD.

Alternatively use a dead store that cse1 cannot delete but flow can. Hmm.

Let me check the .loop dump for vD.
