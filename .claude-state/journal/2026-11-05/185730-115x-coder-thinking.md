---
ts: 2026-11-06T01:57:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6Yx75yWgem2HSgvWvuju
---
g.out has 3674 lines but no uid=368. Maybe insn numbering differs across the TU's functions (UIDs are per-function? UIDs are global per function compilation; each function restarts UIDs at 0? In gcc, INSN_UIDs are assigned per function starting at 1? Actually get_max_uid per function... The dumps show UIDs restarting per function (note 2, 5, etc.), so yes per function. Our function's jump 368 exists only when compiling that function. The gdb run compiles all functions; the DEL lines print uid but not the function. Let me look at the g.out for DEL lines and their counts, and find one with uid=368 near a jump code.

Let me check what codes appear. JUMP_INSN's code value: let me get it from rtl.def order. Let me just grep the DEL lines with code values and count.
