---
ts: 2026-11-06T07:33:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QHxdz6RVL5O7YqhU9z0w
---
Because the local extern decl is removed but... wait, the definition at line 88 is K&R `void func_800CAF84(arg0) void *arg0;` — calling with an argument should be fine. The error says "too many arguments" at line 265. Hmm, maybe there's another declaration at line 134 `extern void func_800CAF84();`? That's an unprototyped declaration, fine. But "too many arguments" means a prototype `(void)` is in scope. The file may have a global `extern void func_800CAF84(void);`? Let me check the top of the file and the header. Actually line 238/253 are local. After removing line 253, maybe there's still a decl. Let me check what's at the top or included headers.

Wait — the error is at line 265 in the scratch TU, which corresponds to our body's line. "too many arguments to function `func_800CAF84'" — the visible declaration must be `(void)`. Maybe the definition at line 88 is after? No, line 88 < 252. But the K&R definition `void func_800CAF84(arg0) void *arg0;` should give a prototype with 1 arg. Hmm, unless the file's function at 88 is inside some `#if`? Let me check line 88 region and line 130-136.
