---
ts: 2026-11-06T06:43:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OmX38jqraTS46QF2jea2
---
Item 4: 127 lines. Levers: 4 pins ($3, $20, $18, $19) and 4 launders (on k40, k50, kF0, k100).

Lever-free: remove the `register ... __asm__("$N")` and the 4 asm launders.

Let me copy and score the baseline. The function spans 3195-3329? Let me find the end: the `}` after func_8012C218(arg); — line 3328 or so. From the sed output, after `func_8012C218(arg);` there's `    }` and `}` then blank lines and `extern void (*D_80184C34[])(void);`.

Let me compute: the sed printed 3195..3330. Counting... easier: find the line of `extern void (*D_80184C34[])(void);`.
