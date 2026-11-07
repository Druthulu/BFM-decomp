---
ts: 2026-11-06T16:44:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_egpPwPIgO7v39uXTReY9
---
Item 2: launder kind. The orig has:
- pins a0 $4, a1 $5 (these are "pins under other causes"? The row kind is launder only; pins $4/$5 are not the row kind, so they may stay — the brief says "levers of other kinds the def already had (pins under other causes) may stay, never added").

Wait: the kinds file says "launder" only. The orig.c has two register pins ($4, $5) and one launder asm. So I must remove the launder (the `__asm__ __volatile__("" : "=r"(s0) : "0"(s0))`) but may keep the $4/$5 pins.

Hmm, but wait: the pins are `register s32 a0 __asm__("$4")` etc. Those are "pin" kind levers, but the row kinds say launder only — meaning the expert determined the row's lever is only the launder; the pins are needed for other causes and may stay. Actually, re-reading the PARTIAL definition: "PARTIAL:<kept> means every row kind not in <kept> is gone from win.c". So for a MATCH, all row kinds (launder) must be gone. Pins under other causes may stay.

Hmm, but hold on: the two `register __asm__("$4")` / `"$5"` are pins — the brief says "levers of other kinds the def already had (pins under other causes) may stay, never added". So yes, keep them.

Wait, but that seems odd: a0 and a1 pins are pins, which is a different kind than the row's "launder". So keeping them is allowed. But the item is called "launder" — so the task is to remove the launder asm while keeping the pins.

Let me check the fresh diff: orig.c vs src lines 3030-3060.

Let me read the src def.
