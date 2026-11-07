---
ts: 2026-11-07T00:39:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_syjjgKY9lXOwztjbycyL
---
Both single-lever versions score 6 — so both levers are load-bearing (each alone doesn't fix it). Interesting: w3 (barrier kept, pin dropped) gives REG-caller (a register difference), w2 (pin kept, barrier dropped) gives ORDER.

Hmm wait, that's odd: w2 = pin kept, barrier dropped → ORDER (same as w1: the order diff). w3 = barrier kept, pin dropped → REG-caller (a register difference).

So:
- The barrier fixes the ORDER (load position).
- The pin fixes a REGISTER (v0 vs something).

Let me look at w3's diff to see the register difference.
