---
ts: 2026-11-06T05:00:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mXF3jzK47xkVYZJEopGc
---
`RTX_UNCHANGING_P` — a MEM marked unchanging is not recorded (hash_arg_in_memory not set). But that's for the source expression.

Key: a store whose *source* is a MEM sets `hash_arg_in_memory` — and cse's `sets[i].src_in_memory` then prevents recording? Let me check where src_in_memory is used. Search "src_in_memory".
