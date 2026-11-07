---
ts: 2026-11-06T02:27:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wnJfxFuIfmpEZKLUGKqz
---
Line 78-80: it requires `! insn_references_resource_p (trial, &set, 1) && ! insn_sets_resource_p (trial, &set, 1) && ! insn_sets_resource_p (trial, &needed, 1)`. Where `set` is the set of resources set between the branch and the trial, and `needed` is the resources needed at the branch. So an insn is not eligible if it sets a resource in `needed` (resources needed by the branch's condition!). The branch `bnez v0` needs v0. The addiu SETS v0 → `insn_sets_resource_p(trial, &needed)` should be TRUE → not eligible! But reorg DID move it in mine. Hmm.

Wait — maybe `needed` is computed as the resources needed at the branch *after* the condition is evaluated? Let me read the start of the function.
