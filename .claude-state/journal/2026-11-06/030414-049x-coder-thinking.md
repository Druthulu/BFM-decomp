---
ts: 2026-11-06T10:04:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R1oyv7stYxb8XRIIOTQW
---
Hmm, only `+= loop_depth`. So how does a non-loop reg get n_refs? Wait — maybe loop_depth is initialized to 1, not 0! Let me check line 1385: `loop_depth = basic_block_loop_depth[bnum];` and basic_block_loop_depth is computed starting from... In flow_loops, depth is 1 for top-level? Let me check around 440-475.
