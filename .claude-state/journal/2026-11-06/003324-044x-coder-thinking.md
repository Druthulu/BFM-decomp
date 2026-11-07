---
ts: 2026-11-06T07:33:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ErBohBx02F5mvQJlsb45
---
The K&R definition at 88 should be visible. But `too many arguments` at line 265 — maybe because the *local* extern in our body was removed, and the nearest visible decl is the K&R definition at 88? That should allow 1 arg. Unless `common.h` declares `func_800CAF84(void)` somewhere? Let me grep headers.
