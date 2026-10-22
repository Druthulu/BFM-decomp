---
ts: 2026-10-22T00:46:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_qgRqHhtYmRGMCdYDY0cD
---
All 11 items are "launder" only. So the pins (in func_8018CDEC) may stay.

Let me fix the generators to only remove *statement* asms (not the register declarations), and regenerate.

Change in gen.py and variants.py: remove lines where "__asm__" appears AND the line is not a `register` declaration. Let me use: a line is a "lever statement" if it contains "__asm__" and does not contain "register ".

Let me update both scripts and regenerate. Also the castframe/framegen scripts.

Let me define a shared helper: I'll just patch each script with the same rule.

Then re-run the scoring for the affected items (func_8018CDEC, func_80191020) and also re-check the others (the removal rule only differs for lines with "register", which only occur in func_8018CDEC and maybe func_80191020).

Let me patch.
