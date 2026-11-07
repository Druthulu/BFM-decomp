---
ts: 2026-11-06T07:35:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rKlO2xeCglxTixm9ghlI
---
The scratch TU looks correct. Yet GCC says too many arguments. This must be because GCC 2.7.2 treats `extern void func_800CAF84();` in a *block scope* as `(void)`? No... Actually, in GCC 2.7.2, an empty parameter list in a function *declaration* means "no prototype" (old C). Calling with args is allowed.

Wait — maybe the compile pipeline uses `-fstrict-prototypes`? Let me check the recipe. Or maybe the call is in the context of a *definition* of func_800CAF84 seen at line 88 as K&R: `void func_800CAF84(arg0) void *arg0; {`. GCC 2.7 might give this function a prototype of `(void*)` and then `extern void f();` at block scope... should still be compatible.

Hmm, "too many arguments" is emitted by the compiler when the function type is a prototype with 0 args. The only 0-arg prototype would be `extern void func_800CAF84(void);`. Did the tool perhaps re-extract the body span incorrectly such that the ORIGINAL extern `(void)` line remained? Look at the scratch: line 253 is `extern void func_800CAF84();` — unprototyped. So no.

Unless... `common.h` or the pipeline defines `func_800CAF84` as `(void)` via an included header? We grepped .h files: none.

Let me look at the recipe pipeline to see if there's a forced include or `-D`. Let me get the recipe for this TU.
