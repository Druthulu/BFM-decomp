---
ts: 2026-11-06T11:32:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xFingU0lqJENgcXQkwBU
---
Wait — the func_80182334 def in src/ov_SC05_008 file? The grep showed only usages `extern s32 func_80182334(s32 a0v);` at 4866, 4929, etc. Let me find the actual definition. The item says func_80182334 is in src/ov_SC05_008/ov_SC05_008_jr_8017AE2C.c. grep -n gave usages. Let me search for `^s32 func_80182334` or `void func_80182334` or `func_80182334(` definition (not extern). The definition line probably has a comment header. Let me grep more precisely.

Actually grep output only had 6 lines with `extern` or call, head cut it. Let me grep all and look for a line that starts with a type. Use grep -n "func_80182334" with more lines.
