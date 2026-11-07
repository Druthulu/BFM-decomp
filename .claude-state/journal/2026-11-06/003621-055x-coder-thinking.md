---
ts: 2026-11-06T07:36:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_87K2PNNzTpWeckZKmR79
---
So with no local decl, the visible declarations are:
- line 88 K&R definition: `void func_800CAF84(arg0) void *arg0; {`
- line 134: `extern void func_800CAF84();`

And GCC still says too many args. But func_800CB158 at line 137 calls `func_800CAF84(arg0)` and compiles! Wait, does the whole file compile? The baseline object exists, so yes. So why does the same call fail at line 265?

Difference: maybe in func_800CB158 the call is `func_800CAF84(arg0);` at line 159 — yes.

Hmm, unless the baseline was built from a different version of the file? No, the tree builds.

Let me test compiling a trivial candidate that calls with arg0 but in the ORIGINAL body position (e.g., keep everything else identical but change only the call). That's what v30 does.

Wait... maybe the issue is that `func_800CAF84` at line 88 is defined with a K&R parameter `void *arg0`, so its prototype is `void (void *)`. Then `extern void func_800CAF84();` (unprototyped) is a compatible redeclaration. Calling with an `s32` arg: with a prototype `void*`, passing s32 is a warning (int to pointer). With no prototype, fine.

"too many arguments" is weird. Let me look at the cc1 error semantics. Maybe it's not about func_800CAF84's own decl but about the *call* being parsed as `func_800CAF84(arg0)` where func_800CAF84 is a macro? `-undef` removes predefined macros. No.

Let me try a direct compile test: create a scratch C file in my shard with a K&R def and a call, compile with the same cc1? The toolchain path is tools/bin/gcc-2.7.2-psx/cc1. Let me test:

```
void f(a) void *a; {}
void g(s32 x) { f(x); }
```
compile with cc1 flags. Let me try.
