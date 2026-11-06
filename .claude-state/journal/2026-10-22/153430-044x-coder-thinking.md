---
ts: 2026-10-22T21:34:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xo8vNWZIy5KqAriFNO7c
---
Item 4 (func_80177F84): kinds = launder, but the def has many pins (register asm) too. The kinds row says `launder`, so only the launder is the row kind; pins under other causes may stay ("levers of other kinds the def already had (pins under other causes) may stay, never added").

So I only need to remove the launder (`__asm__ __volatile__("" : "=r"(byteval) : "0"(byteval));`). The pins stay.

That's a single-line drop. Let's test: orig (lines 3-36 of header) → drop the launder line.

Careful: `byteval` has `register u32 byteval __asm__("$3")` pin and the launder. Removing the launder: `byteval = src;` then used in `pcVar2[0] = (u8)(byteval * 8 + 8);`.

Let me copy lines 3-36 (the whole def) and drop the launder.
