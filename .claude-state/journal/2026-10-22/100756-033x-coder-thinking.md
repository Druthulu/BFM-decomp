---
ts: 2026-10-22T16:07:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TztiNJUaGzJg6C5HY5sm
---
w2/w3 still have the launder asm → they are not lever-free. They score 0 only because they keep the launder. So PARTIAL:launder at best (not a crack).

The lever-free base (gen_base, b1..b5) scores 4 (MIXED, 19 ins = same count). So the residual is a "MIXED" 4 — small differences. Let me see the diff for b1/gen_base.

Note: score 4 MIXED with 19 ins vs 19. Let me get the diff.

Also note the launder is at two places (both assignments of `it`). The lever-free base removes both asm lines (variants.py strips lines with "FAKE: launder"). So b1 is fully lever-free. Score 4.

Let me see the residual.
