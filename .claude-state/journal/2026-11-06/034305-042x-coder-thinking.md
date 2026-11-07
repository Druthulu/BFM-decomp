---
ts: 2026-11-06T10:43:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QxgkvMh5SmC7mUXMwcoa
---
Hmm, my naming logic: `"p_" + "_".join(["S2","S3","S4"][[S2,S3,S4].index(x)] ...)` just gives S2_S3_S4 for all permutations — same name! So they overwrite. Only 20 files: p_all, p_or, plus 6 p_, 6 d_, 6 e_ = 20. But the names collide across permutations → only the last permutation of each type survives.

Let me fix the naming to include the permutation order properly (use the actual labels). Simpler: name by the order of statement labels computed from indices. Let me rewrite the loop with labels.
