---
ts: 2026-11-06T07:33:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HTQTzpbdqtp0GtClQxAz
---
Our extraction of orig.c included the local extern line `extern void func_800CAF84(void);` and my sed removed it. But there might be another issue: the `--try --body` replaces the function definition in the TU. The scratch TU's line 265 corresponds to our body. The error says too many arguments — maybe because the K&R definition `void func_800CAF84(arg0) void *arg0; {` in GCC 2.7 with `-traditional`? Actually K&R definitions give the function a prototype only after the definition. It should be fine.

Wait — maybe the issue: when `--body` replaces the function, the local extern removal isn't the problem; the problem is the call `func_800CAF84(arg0)` where `arg0` is `s32` and the prototype expects `void *`. That's a warning, not an error. "too many arguments" specifically.

Hmm, maybe common.h defines `#define func_800CAF84 ...`? No.

Let me test with the local extern changed to `extern void func_800CAF84(void *);` instead of removing it. Then the local prototype wins. Let me try.
