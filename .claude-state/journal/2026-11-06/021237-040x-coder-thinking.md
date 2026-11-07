---
ts: 2026-11-06T09:12:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5QX27CVAP15M2U4A3ldk
---
expand_value_return emits the move to return_reg (v0) unconditionally, even for void functions? It's called when there's a return statement with a value. But for a void function, `return expr;` — does GCC call expand_value_return with the value? Let's check expand_return in stmt.c.
