---
ts: 2026-11-06T03:40:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JFD4oujdj0lQ2YtzyFzT
---
I now have the full bodies of the four functions except func_8017D7B4 complete (yes, ends at D_801151D4). func_80182560 full. func_801854B8 full. func_801810A4 full.

Now, the task: remove barrier levers and find lever-free C that scores 0. This is a decompilation matching task. The approach: copy each source def to orig.c, strip barrier asm statements, then try to find C variants that score 0.

Let me start with item 1. Approach note first (per X1) before first edit.

Let me set up item dir: copy the function into orig.c. Need to know exact function text range. Let me use sed to extract. For func_8017D7B4: lines 3733-3783ish (ends `D_801151D4 = (s32)D_80126948;` then `}`). Let me get exact line numbers.

Actually the `dt.sh` takes a body file — what does delever_search expect as body? Let me check tools/delever_search.py usage and R3.40-013 helpers. Let me check --help.
