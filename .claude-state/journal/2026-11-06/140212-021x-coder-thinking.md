---
ts: 2026-11-06T21:02:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_toTOBK8ZAIxP6SZO9MG6
---
I need a TU for this function to dump. The function is in src/ov_SC01_009/ov_SC01_009_jr_8017E590.c. I can copy the TU? It's 4278 lines with many functions. cc1_dumps_tu.sh can take the actual src file and dump it. But the pass dumps would include all functions. That's fine — I can grep for func_8017E590 in the .lreg/.greg dumps.

But the src file uses INCLUDE_ASM for other functions maybe. The dump helper handles that. Let me use tools/cc1_dumps_tu.sh on src/ov_SC01_009/ov_SC01_009_jr_8017E590.c with DUMP_ROOT under my item dir.

However, the src currently contains the lever body (asm). To dump the candidate I need a TU with the candidate body. I can create a scratch TU: copy the src file and replace the function body? That's big. Alternatively, delever_search likely creates a scratch TU under .run/P36/engine/score/... Let me check its --try internals / --keep.

Let me check delever_search.py options.
