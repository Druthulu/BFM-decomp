---
ts: 2026-11-06T12:03:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fdWhi6s08O6cbWuH0lX4
---
Item 4: kinds barrier,launder. Levers:
- L1: launder on `base` — `__asm__("" : "=r"(base) : "0"(&D_8011F7F0));`
- barrier memory: `__asm__ __volatile__("" ::: "memory");`
- pins: $4 (a0v), $5 (sum) — pins are a different kind, allowed to stay.

Also L2/L3/L4 comments suggest more levers? L2 is `*(volatile u32 *)&slot[6] = (u32)p;` — a volatile store! L4 `a0v = p;` L3 `sum = r1+r2;`. Those are real C (volatile is a qualifier — hmm, is volatile a lever? It's marked L2 but not !FAKE). The kinds list says barrier,launder. So volatile is not a lever to remove (it's not in the kinds).

Hmm, "no new lever of any kind" — the volatile was already there, so it may stay.

So: remove L1 (launder) and the memory barrier.

Let me set up orig.c and test.
