---
ts: 2026-11-06T07:35:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HAyaOfRRRsJIaeS5wjPx
---
The splice replaces lines from `d_["line"]` to `d_["end"]` (line starts). So it replaces the whole definition, including the local extern. Good.

So why "too many arguments"? Let me check what `sc.scan_text` reports as the function def span — maybe `body_span` for our function starts at the *previous* function or includes the extern at 134? No, name match.

Let me just reproduce the compile manually: copy the TU to my shard, splice my body, and compile with the recipe pipeline? Hard.

Alternative: maybe the compiler is invoked with `-D` something that defines func_800CAF84 as void? Or the K&R definition at line 88 in GCC 2.7.2 gives a type of `void ()` AND GCC 2.7 treats old-style definitions as taking no args for calls? Let me look at the actual error more: "too many arguments to function `func_800CAF84'". In GCC, this happens when the function has a prototype with fewer params. The unprototyped decl should allow. Unless the *call* is being compiled in a context where `func_800CAF84` was declared `(void)` by... our own function's earlier local extern? In the scratch TU, line 253 area: our body now has `extern void func_800CAF84();`. But the compile error at line 266. Hmm.

Let me get the scratch TU. I can make the compile fail but the tool restores the real src. However, the scratch copy `scratch_src` is written in .run/P36/engine/score/.../p<pid>/md_MAIN_016.c and NOT deleted on failure? `score_file` finally deletes the dir unless --keep. With --keep it keeps it! Let me run v33 with --keep and then inspect the scratch_src.
