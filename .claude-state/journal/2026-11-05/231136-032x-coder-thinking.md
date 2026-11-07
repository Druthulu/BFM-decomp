---
ts: 2026-11-06T06:11:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DnYgYqfC6OdcKy9CF1v0
---
Ah — this dump's first function (line 31 etc.) is another function in the TU (before func_801804A0). The `16 s0` at line 31 is from a different function. But the alloc_table section is per-function... The ";; Register dispositions" is per function. Fine.

But the conflicts line for r72 includes 16. Hmm, so within func_801804A0's RTL, hard reg 16 is referenced somewhere. Let me look at the function section start (line ~1947 is the order line, function start just before). Let me search within the func_801804A0 section for "16 s0" occurrences after line 1947.

Actually the dump at line 1947+ shows insns of the function. The conflict with 16 might come from the RTL: `(reg/v:SI 16 s0)` — hmm, that's the disposition-era RTL (the dump is printed after allocation, so regs are renumbered).

Hmm wait. Important: the .greg dump is printed AFTER global allocation, so the RTL shown has hard regs substituted. The ";; N conflicts" lines are the recorded conflicts from before allocation, which reference pseudo numbers. So "72 conflicts: ... 16 ..." means pseudo r72 conflicts with hard reg 16. That's real, from before allocation.

Where does the RTL use hard reg $16 before global allocation? Possibly from a hard-reg variable in the body... The original body's pin was $18. Is there any `$16` in the function? grep t.c around the function. Let me search the function region in t.c for "$1" pins.

Let me find the function in t.c and grep the body lines.
