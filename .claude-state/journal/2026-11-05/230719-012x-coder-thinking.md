---
ts: 2026-11-06T06:07:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_R81OTVdiCOAPFWABJvjX
---
Baseline confirmed. Now the lever-free version: remove pin `register u16 *s2 __asm__("$18");` → `u16 *s2;`, and the launder in case 2 → plain `func_8012A828(a0, &D_801C00D0);`.

Let me create win.c with those two changes.
