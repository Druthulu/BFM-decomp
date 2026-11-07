---
ts: 2026-11-06T06:36:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6h4rLI50DpVY9pJQgk7z
---
Good — only 23:36, I'm doing fine time-wise (started 23:05, 31 min for 2 items).

Let me write notes and the results row for item 2, then move on.

Note: the launder crack for item 2: simply removing the asm works (b2=0). Why? Because with the pins present, the mulc chain and load order are already anchored by the pins. Good.

Let me record: result PARTIAL:pin, best 0, tries: w0(68), p0(40), b2(0), v0..v6 (7), v10..v14 (4, one compile error), v20..v24 (5) = ~18 scored tries. The wall tag: for a PARTIAL, "a tag from walls.txt or a new `<pass>-<what>`". The residual for the pins: w2 s16 fixes the count; the remaining is a v1/a0 swap in local-alloc → tag "lreg-qty-priority" (from moves.md line 87, not in walls.txt; walls.txt has "global-alloc..." etc.). Let me use a new tag `lreg-qty-priority` (lowercase, pass-what). Fine.

Let me write notes and append the row.
