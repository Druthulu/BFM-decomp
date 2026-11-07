---
ts: 2026-11-06T05:44:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HBb2V38r3Y12O6tnxID2
---
Item 3: func_80182F3C, kinds launder,pin. Pin: `register s32 v __asm__("$2")`. Three launders on `c` (zero-byte re-ties).

The pin's rationale (from the comment): the two-def return pseudo of the early-out falls to global_alloc and lands in $a0, costing a `move $v0,$a0` in each of the two delay slots. The pin restores the target's $v0 = pointer / $v1 = 0xA2 / $a0 = halfword assignment at zero byte cost.

This looks like a harder case. Let me set up and get the baseline diff.

Let me copy orig.c and score lever-free (remove pin + 3 launders).
