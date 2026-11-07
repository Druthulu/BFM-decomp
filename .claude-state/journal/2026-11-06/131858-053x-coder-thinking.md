---
ts: 2026-11-06T20:18:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9EGcOJdsTxUYC8kIEZ8A
---
vB scores 0! The W47 move works: split `pv &= 0xFF000000` into its own statement.

Interesting that vC (pv = 0) scored 11 with 177 insns — the `li $3,0` must have been deleted or combined. Anyway.

vB = MATCH. Let me set win.c and verify no levers: the launder asm removed; pins ang/pv kept (allowed, they're other-kind levers already in the def). Check: `grep asm win.c` should show only the two `register ... __asm__("$N")` pins.

Let me copy and verify.
