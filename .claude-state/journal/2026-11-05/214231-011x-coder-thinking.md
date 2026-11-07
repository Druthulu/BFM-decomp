---
ts: 2026-11-06T04:42:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_et5kkkyoCoYThbE9bUDN
---
Without barrier, gcc keeps v1 as the result register across statements and reorders stores after each subu? Actually mine: 20 ins; target 22. Mine uses v1 for the subtraction result and delays stores (stores after all computations?). Target uses v0 and stores immediately after each if.

Wait actually the difference: target stores sb v0,0(a0) right after the if (at insn 7), while mine computes all three and stores later? Let's look at the mine full listing. Let me get the target/mine asm dumps. delever_search might have a --keep or dump option. Let me check delever_search.py usage.
