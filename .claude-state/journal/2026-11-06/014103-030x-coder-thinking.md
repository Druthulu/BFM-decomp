---
ts: 2026-11-06T08:41:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CuqKXtkoHddD3bGSWuX2
---
Item 1 done in ~10 min. Now item 2: func_80187988 (ov_SC02_000), keepalive at line 5878: `__asm__ __volatile__("" : : "r"(val));` in the else branch:

```c
    r = rand();
    nudge = r << 4;
    if (hi == 0) {
        nudge = r << 5;
    }
    if (rand() & 1) {
        val = nudge;
    } else {
        val = nudge;
        __asm__ __volatile__("" : : "r"(val));  // keepalive
        val = -val;
    }
```
The asm keeps `val` live/forces the copy before negation. Without it, `val = nudge; val = -val;` folds to `val = -nudge` (combine-copy-merge). The asm forces the move.

Lever-free: need a real C use. Perhaps in the else branch, `val = nudge;` then `val = -val;` — gcc merges. What real C could keep the move? Maybe use the value in a real expression before negating: `val = nudge; ... val = -val;` with something in between that reads val. E.g. the target probably has `move vX, nudge; negu vX`? Let's see the diff.

Also could restructure: `if (rand() & 1) { val = nudge; } else { val = -nudge; }` — would lose the move.

Let's score the asm-deleted candidate and see the residual.

FRESH: copy src to orig.c, extract body.

Also, item 2's kinds: keepalive only.

Let me do it.
