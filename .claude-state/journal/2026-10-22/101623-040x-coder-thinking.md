---
ts: 2026-10-22T16:16:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pxd12yxMyYlotbU3HVyg
---
In the greg dump: `(eq:SI (reg/v:SI 4 a0) ...)` — so at the compare, the first operand is a0. Which pseudo is a0? Let me see more context. In cse2: `(eq:SI (reg:SI 75) ...)`. Let me print those regions.

Let me look at cse2 lines around the function start +40..+80.
