---
ts: 2026-11-06T06:09:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_43XadJhPZn5bgi2sGBiS
---
No change. Hmm, goto loop didn't remove loop notes? In gcc 2.7.2, loop notes are found by scanning for backward jumps (loop_optimize's find_and_verify_loops) — actually NOTE_INSN_LOOP_BEG is emitted by the front end for do/while. With goto, no LOOP notes → loop_depth stays 1 in flow. But maybe flow's loop_depth comes from the CFG (flow.c does its own loop detection?). Let me check flow.c loop_depth.
