---
ts: 2026-11-06T16:46:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n07i9svlumvC122i3vtH
---
The `size` passed comes from `REG_SIZE`? Let me look at reg_is_born / reg_is_set. But likely `size = REG_SIZE (reg)` = GET_MODE_SIZE in words? For HImode, REG_SIZE might be 1 (in words). Let me check where alloc_qty is called.
