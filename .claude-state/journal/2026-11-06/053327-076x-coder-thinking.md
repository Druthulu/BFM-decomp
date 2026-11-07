---
ts: 2026-11-06T12:33:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nejgI5y3h3lH1XkPRMrV
---
f2 = 56. Improvement continues. Tries: 28 + 6 (well, 4 successful) = 32+.

Time is ~07:10, item 3 at ~20 min. Let me try a couple more on top of f2 (56) — the pattern is that swapping the if/else arms of the min/max tests helps. Let me apply the same swap to the x2 and x3 tests on top of f2.

Actually e4 (c2+X2+X3+Y3) was 90 — worse. But that was on c2. Hmm.

Let me try:
g1: f2 + x2 swap
g2: f2 + x3 swap
g3: f2 + both
g4: f2 + the `if (my >= -0x6E && mny < 0x6F)` ... can't swap.

Let me do 3-4 more and then record. Also let me record the diff of f2 to describe the mechanism.

Actually, time check: I still have item 4 (87 ins) which is the best MATCH candidate. Item 3 is at 56 with a huge residual (733 ins, 56 = lots of register pairs). It's a WALL.

Let me do 2 more tries and record.
