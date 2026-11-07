---
ts: 2026-11-06T09:56:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UZ0QBKWl530C8KIfSr1J
---
Callers declare void at file scope. So changing the definition to s32 would conflict. Unless the definition is later... Hmm.

But wait — maybe the callers' declarations are in the same TU, and GCC would error. Let me test empirically. First, let's try the simplest lever-free body without pin/keepalive and see the score and whether flow deletes.

Let me write win.c candidate 1.
