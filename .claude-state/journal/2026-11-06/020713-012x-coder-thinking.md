---
ts: 2026-11-06T09:07:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5Vd4KGnUURoRNxe2yqTI
---
Interesting: at line 111 `v0 = func_800CD5CC(param_1);` — there is no declaration in this file before? There might be an implicit declaration (C89 allows implicit int return). Actually with GCC 2.7.2 in C mode, implicit declaration returns int. So `v0 = func_800CD5CC(param_1)` works implicitly (and the local extern void decls are inside other functions at 146 etc.).

So the body file could define it as `s32 func_800CD5CC(void *arg0)` and it would still compile, since callers... hmm, line 146 has `extern void func_800CD5CC(void *a0);` inside some function after line 111's use. If the definition at line 471 is s32 but a later function declares extern void, GCC may error "conflicting types". Let's check lines 140-150 and 190-260.
