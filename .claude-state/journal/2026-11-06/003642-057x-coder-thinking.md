---
ts: 2026-11-06T07:36:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MhwuLsNCYAj1TSDx62ap
---
Line 35921 and 35936 are the local `(void)` decls in functions at 238 and 253. Those are inside OTHER functions and our function. The `(void)` prototype at line 35921 is inside func_800CB3xx (line 238). Declarations at block scope are local to that block, so they don't affect our function.

But WAIT: our function at 35936 has `extern void func_800CAF84(void);` and the call at 35952. In v30/v33 we replaced the body, so that line should be gone. The scratch TU we inspected confirms.

Hmm, let me reproduce the exact failure with cc1 by compiling the scratch TU (p3) directly. The pipeline includes cpp. Let me run cpp on the scratch TU (with -I its dir) then cc1, and see the error. Actually the tool already did that.

Let me look at the function at line 238 (func_800CB3xx) to understand: maybe its local `(void)` decl is in the SAME block as our function? Let me view lines 230-250.
