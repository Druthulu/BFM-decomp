---
ts: 2026-11-06T05:19:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zTU3Pms9h5inoDJZAvTo
---
This is for operands, not memory clobber. The memory clobber is `(clobber (mem:BLK (scratch)))` built later. No stack allocation.

Let me search for where the memory clobber is added.
