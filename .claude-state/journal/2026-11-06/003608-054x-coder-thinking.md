---
ts: 2026-11-06T07:36:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_P9wiGKJQIlP9TiBZXi2x
---
The recipe uses cpp with `-undef -Wall -fno-builtin`. No forced `(void)`.

Hmm, maybe the issue: `void func_800CAF84(arg0) void *arg0; {` is a K&R definition. In GCC 2.7, when a function is *defined* old-style, its type is `void ()` — unprototyped. A subsequent block-scope declaration `extern void f();` is fine. Calling with 1 arg is fine.

Unless the call `func_800CAF84(arg0)` where arg0 is `s32` — no.

Let me test the compiler directly on a minimal case? I could compile the scratch TU manually using the pipeline, but that's what failed.

Wait, maybe the error line 266 is not our call. Let me count: our function starts at line 252. Lines:
252 void ...
253 extern void func_800CAF84();
254 extern s32 func_80146A6C(...);
255 s32 s0...
256 s32 s1;
257 s32 v0;
258 s32 id;
259 blank
260 s1 = ...
261 v0 = ...
262 blank
263 copy1
264 copy2
265 blank
266 func_800CAF84(arg0);
Yes, line 266 is the call. So the compiler has a `(void)` prototype for func_800CAF84. Where from? 

OH WAIT. Maybe it's the maspsx or cpp: `-Dmips -D__GNUC__=2 ...` no.

Could `func_800CAF84` be declared in `include/common.h` indirectly via a function *definition*? We grepped `.h` and found none.

Hmm, maybe the local `extern void func_800CAF84();` at block scope, followed by the *definition* at file scope earlier — in GCC 2.7, a block-scope declaration with `()` might default to `(void)`? Actually there's a known old GCC behavior: in C, `f()` in a *definition* means no args; in a *declaration*, `f()` means unspecified. But GCC 2.7 may have treated `()` as `(void)` when `-fno-...`? No.

Let me look at how other functions in the same file call it successfully: line 159 `func_800CAF84(arg0);` inside func_800CB158, which has file-scope `extern void func_800CAF84();` at line 134. That compiles (the file builds). So an unprototyped decl works there! The difference: our decl is *block scope* inside the function. Maybe GCC 2.7 gives a block-scope `()` declaration a `(void)` prototype? That seems plausible as a bug/behavior: block-scope declarations without a prototype... Hmm.

Simple fix: remove the block-scope declaration entirely (rely on the file-scope K&R definition at line 88 and/or the file-scope extern at 134). v30 did that and still errored. Wait, v30 removed the line and still got "too many arguments". Hmm! So even without the local decl it fails. But then func_800CB158 works with the same file-scope decl. The difference: v30's body still has `extern s32 func_80146A6C(...)` — irrelevant.

Wait, in v30 I removed the local extern and called with arg0. The error was at line 265. Let me recheck v30's scratch with --keep. Maybe the body_span splice left the original `(void)` line? Let me inspect.
