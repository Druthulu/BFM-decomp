---
ts: 2026-11-06T07:36:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8W03r0TlnG049COY2oPP
---
OK so func_800CB400 has its own `(void)` decl and calls with no args.

Now let me compile the scratch TU directly to reproduce and inspect. Actually, maybe the error is that in v33 the local `extern void func_800CAF84();` at block scope in GCC 2.7 means `(void)` (because block-scope declarations might be parsed differently), and in v30 without any local decl, the call resolves to the file-scope `extern void func_800CAF84();` at line 134... but wait, line 134's decl is at file scope. Hmm.

Actually, v30 error line 265. Let me reproduce v30's compile manually using the scratch p3 dir (it currently holds v30? no, last --keep was v30? The last --keep run was v30, then I inspected. Let me check the scratch content now: it showed v30 (no local extern). Let me run cpp+cc1 on it exactly as the pipeline.
