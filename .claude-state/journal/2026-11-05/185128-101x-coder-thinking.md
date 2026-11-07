---
ts: 2026-11-06T01:51:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4HSFwqt9DpgJDCqprPg7
---
Wait — v1's sched dump shows the asm_input barrier?! v1 was derived from orig by removing the BAR line... let me check: v1 = base.replace(SH+STORE, STORE+SH) where base=orig.replace(BAR,''). But the dump shows `(asm_input (""))` at insn 368 — that's the barrier! So the scratch TU wasn't v1 — it's stale again! The p3 dir wasn't overwritten by the --try v1 run? Hmm, the dump shows the barrier.

Wait, the --keep scratch: maybe delever_search caches by text hash and the p3 dir holds the previous? Let me check the p3 TU content now.
