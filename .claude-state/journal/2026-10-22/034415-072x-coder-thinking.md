---
ts: 2026-10-22T09:44:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YySAqKI2v6JY5HuK59mX
---
No PLUS case in make_compound_operation. So the swap is elsewhere in combine.c.

Let me search combine.c for the pattern where a PLUS is rebuilt with swapped operands. Perhaps in the main `try_combine` code, in the handling of `(set (reg) (plus ...))` or in `simplify_rtx`'s PLUS handling.

Let me look at simplify_rtx's start (line 2961 onwards) to see the structure.
