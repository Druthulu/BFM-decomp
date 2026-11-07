---
ts: 2026-11-06T13:00:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BGyWVnjqzfJLqiHLdUhA
---
Item 3: func_801E8DF4 (131 lines? the list says 131). One barrier at line 857: `__asm__ __volatile__("");` between `if (D_8011512C == 4) return;` and `if (D_8011512C == 0xA) return;`.

That's the "two consecutive tests on the same global" — the barrier prevents cse/flow from folding the two loads into one (the second `D_8011512C` load). Target keeps two loads.

Real-C fix: make the second test read a *fresh* value. Ideas:
- `if (*(volatile s16 *)&D_8011512C == 0xA) return;` — volatile (lever?).
- Split with a function call? no.
- Use a different expression: `if (D_8011512C == 0xA)` after `if (D_8011512C == 4)`.

cse would fold the second load into the first. To prevent: a store between? None.

Hmm, what about reordering the tests: `if (D_8011512C == 0xA) return; if (D_8011512C == 4) return;` — cse would still fold.

What about combining: `if (D_8011512C == 4 || D_8011512C == 0xA) return;` — folds to one load and two compares. The target has 2 loads? Let me check the target's asm. Let me set up and get the baseline + removal diff.

Let me extract orig.c and score.
