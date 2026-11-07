---
ts: 2026-11-06T18:32:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8S56xzrl6KrWCqQvlrDv
---
The scheduling trace shows the block 3 insns scheduled in reverse-ish order (T-1 first is the last insn). The final order is: 45,47,49,52,58,61,64,67,70,72,75,77,86,89,94,96,98,100,104,105 — wait, where is 55?

The trace's insn list at the top of block 3 (from the earlier output) was:
45,47,49,52,58,61,64,67,70,72,75,77,86,89,94,96,98,100,104,105.
No 55! But the initial RTL has insn 55. So insn 55 must have been changed before sched1: combine or cse merged it? Or maybe insn 55 was *replaced* by a different number. Hmm, the RTL I dumped is the .rtl (initial). Let me check the .combine or .cse dump for insn 55.

Actually, wait: maybe insn 55 is not in block 3's list because sched1's dump only lists insns that... hmm.

Let me grep the .sched dump for "55" in the function's RTL (the final RTL printed after scheduling).
