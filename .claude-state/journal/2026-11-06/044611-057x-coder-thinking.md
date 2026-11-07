---
ts: 2026-11-06T11:46:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dtYQQKAw6rqTlVdXi9JH
---
Ah — d000 was from gen2 with `g2w` = G2 (a string) and my emit did `s += wrap(g2w) if g2w else g2w` — a bug: it always wrapped! `wrap(g2w)` — yes, in gen2 emit: `s += wrap(g2w) if g2w else g2w`. g2w is a non-empty string so it always wraps. So all gen2 candidates had the middle group wrapped (and g1w controlled only the first). So d000 = middle-group do-while + const before → 28.

And c001 (gen1, masks "2") also = 28. Consistent.

So wrapping the middle group in do-while gives 28 vs 30. Interesting.

Now the decl-order sweep without any wrap gives 30. Let me redo the decl-order sweep WITH the middle do-while (the 28 base) — maybe a decl order + middle wrap gets lower.

Let me update gen3 to wrap the middle group and re-run. Also note that the do-while wrap of the middle group introduced the s2/s0 swap residual (score 28 had s2->s0 x10).

Let me regenerate gen3 with the wrap and score.
