---
ts: 2026-11-06T06:37:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JNoMZQnfBMZHjpKXmfDV
---
Hmm wait, the second extraction (func_80191C50 from ov_SC06_018_jr_8019059C.c) gives lines 2843-3150 — but that's inside func_8019059C's range (2787-3095)? No wait: func_8019059C is at 2787-3095 in ov_SC06_018_jr_8019059C.c, and func_80191C50 is at 2843-3150 in ov_SC06_018_jr_80191C50.c (a different file). Right, the second item's tu is ov_SC06_018_jr_80191C50.c. Let me verify: the list.tsv says item 2 file is src/ov_SC06_018/ov_SC06_018_jr_80191C50.c. Yes.

Good. Now let me score the origs of all three to confirm baselines. That's 3 scores; let me do them in one sc.sh call? sc.sh takes one dir and multiple files. Different dirs → 3 calls. Let me use dt.sh? Simpler: run each with sc.sh.

Actually, let me write a small loop using bin/sc.sh per dir in one command. That's fine.

Let me score origs.
