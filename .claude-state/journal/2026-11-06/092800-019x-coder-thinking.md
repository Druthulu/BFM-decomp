---
ts: 2026-11-06T16:28:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SPsIi6geUKA8DPYVMQte
---
So --body splices my definition over the existing definition. If I use `s32 func_800D1E9C(void *arg0)`, the earlier `extern void func_800D1E9C(void *arg0);` at line 87 conflicts → compile error. Unless the extern decl is inside a function scope? Line 87 is file scope presumably. Let me check around line 80-95.

Actually wait — what if the extern decl at line 87 is inside a function? Let me look.
