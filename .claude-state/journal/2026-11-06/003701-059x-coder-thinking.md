---
ts: 2026-11-06T07:37:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oP3lGqsqlMoMCxtAOWmV
---
Reproduced. So cc1 really rejects it. Why? Let me check the preprocessed declaration at line ~35936 in pre.i. Since the scratch file is v30 (no local extern), the file-scope decls are:
- K&R def
- `extern void func_800CAF84();`

But maybe `func_800CB400`'s local `extern void func_800CAF84(void);` — that's block scope, ends at its closing brace.

Hold on, maybe GCC 2.7's parser, upon seeing a block-scope `(void)` declaration of a function, *updates the function's global type* to `(void)` and it persists! That's a known GCC bug? Actually old GCC might treat a block-scope function declaration as a redeclaration affecting the global type if it's a prototype. That would explain: func_800CB400 (line 238) declares `(void)`, and afterwards (in source order) the global type becomes `(void)`, so our call at 265 fails. And func_800CB158 at line 159 is BEFORE func_800CB400, so it worked. And func_800CB304 at 200? calls func_800CAF84(s0) at 226 with a local `extern void func_800CAF84();` at 200. Before 238. Yes!

So the culprit: the local `(void)` prototype in func_800CB400 (line 238) leaks globally in this old compiler. Our function's own local `(void)` decl is also there. If I change MY local decl to a one-arg prototype `extern void func_800CAF84(void *);` — but that conflicts with the K&R def type? The earlier v31 got "conflicting types" at line 88. Hmm, that was with the local decl `(void *)` at line 253, and it complained about line 88. But maybe the conflict is with the *leaked* `(void)` type from func_800CB400? The error said "line 253 conflicting types / line 88 previous declaration". So a `(void*)` local decl conflicts with the function's type which is... `void ()`? If the function type is unprototyped, `(void*)` should be compatible in C. But GCC 2.7 may consider it a conflict.

Wait, maybe the function's type is actually `(void)` because the K&R definition's parameter... no.

Let me test in my minimal harness: add a block-scope `(void)` declaration before, then a call with arg.
