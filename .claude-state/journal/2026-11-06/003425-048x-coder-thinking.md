---
ts: 2026-11-06T07:34:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7VK2oMSy7bFPg0tN24qH
---
Odd. Let me get the actual compile command and see. The oracle compiles the TU. "too many arguments to function `func_800CAF84'" — the compiler thinks the function takes 0 args. Perhaps GCC 2.7's K&R definition `void func_800CAF84(arg0) void *arg0;` actually defines it with NO prototype args in the type because of an old-style quirk? Let me test directly: write a tiny C file? That requires the toolchain. Alternatively, look at how other functions in this file call it: line 159 `func_800CAF84(arg0);` and line 195 `func_800CAF84(ent);` and 226 `func_800CAF84(s0);` — these compile fine in the current TU! So calling with an arg IS fine normally. But those functions have their own local extern? Line 134 has `extern void func_800CAF84();` at file scope before func_800CB158. Then line 200 has `extern void func_800CAF84();` inside func_800CB228? and line 226 calls with s0.

Our function at 252 has a local `extern void func_800CAF84(void);` which shadows with a `(void)` prototype. In my v32 I changed it to `extern void func_800CAF84();`. Yet "too many arguments". Maybe my sed didn't match because the orig/base has the line but with different spacing? base.c line: `    extern void func_800CAF84(void);` — sed pattern `s/extern void func_800CAF84(void);/.../` should match. Let me verify v32 content.
