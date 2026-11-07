---
ts: 2026-11-06T05:12:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ry8uENTBd8SMkbyTslpV
---
w4 (the `+ 0` expression) gives 114 ins! score 15. Interesting — the `+0` changed something (probably prevented cse's equivalence or the load reuse). But `+0` is an identity expression (folded?) — it produced 114 ins, so it did something.

Hmm, but w4's score is 15 vs u3's 0. Let me diff w4.

Actually wait: `(s16)(D_80078EA6 + 0)` — combine folds +0, so the RTL is the same. But the insn count changed to 114. Hmm, maybe the *type* of the expression changed the alias set (the addition might promote to int → SImode → but the comparison is on s16...).

Let me diff w4.
