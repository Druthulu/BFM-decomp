---
ts: 2026-11-06T08:50:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ymnIg96pDI38LYarEOV1
---
So the scratch has only the launder asm at 4316 (a different function). The `(use reg78)` in func_80187988's RTL must come from something else.

Let me look at the .rtl dump (initial RTL) for func_80187988's else block. If the use is there from the start, it's from the C. If it appears first in combine, combine made it.

Actually, wait. I realize: the use insn could be from `val = -val;` where val is **volatile**? No.

Let me look at the .rtl dump.
