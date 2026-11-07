---
ts: 2026-11-06T07:33:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_C4j1p0xgwbG6GgPHyUXb
---
Conflicting types: the K&R definition's prototype is `void func_800CAF84() void *arg0;`? Actually GCC's K&R definition yields type `void ()` (no prototype) or `void (void*)`? The error "conflicting types" against line 88 suggests the definition is `void func_800CAF84()` (unprototyped). Then `extern void func_800CAF84(void *)` conflicts? In GCC 2.7, an unprototyped decl and a prototyped decl shouldn't conflict... but old GCC might treat the K&R definition's parameter as `void *` prototype. Hmm, "conflicting types" might be because of `(void)` vs the definition. Let me instead use the exact old-style declaration: `extern void func_800CAF84();` (unprototyped, like line 134). That's what the file itself uses at line 134! Then call `func_800CAF84(arg0)`.

Let me try: replace the local extern with `extern void func_800CAF84();` (K&R-style empty parens, which in GCC 2.7 means unspecified args).
