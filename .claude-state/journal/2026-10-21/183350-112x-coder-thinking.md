---
ts: 2026-10-22T00:33:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_CE6BadV75C5WheFFDXn3
---
w7 = 33 (like E1). So the reorder doesn't help.

Time is running out. Let me settle item 1: the best lever-free score = 14 (w1/w4/w6) — the compound-assignment split of the vol computation. That's a big improvement over 30 but not 0.

So item 1 = WALL, best = 14, tries = 8ish. Wall tag: the launder is a scheduling barrier between two magic-multiply chains; the compound-assignment split gets the chain order right (30 → 14) but the shared magic constant's materialization stays sunk next to its mult instead of at the top of the tail. New tag: `sched1-const-sink`? Hmm, or use the existing "sched1-birth-boost" (the magic constant's birth boost). I'll use "sched1-birth-boost" with the mechanism.

Hmm, wait. Before giving up on item 1, let me try ONE more thing for the magic's position: what if the vol numerator is computed so that the magic gets a 2nd set? Hmm.

Alternatively: what if I split the vol division the other way — put the *division* first and the numerator... no.

What if the vol statement is written as:
```
vol = (0xA0 - av) * 0x7F;
vol /= 0xA0;
```
(w1) and the PAN as:
```
sx = sx + 0xA0;
sx = sx / 0x14;
```
(w2 = exploded).

Hmm, what about the pan as a compound on a different variable? no.

What if the pan's dividend is split but with a temp (not a compound)? e.g. `pd = sx + 0xA0; sx = pd / 0x14;` — I tried that (v2 in item 1 = 30).

Hmm, what if the ORDER of the two divisions' *expansion* changes if the pan uses a compound assignment on a temp? Ugh.

Let me now also quickly check item 2 (func_8018389C) — the same TU, the same launder pattern (on vol at line 7252). If the mechanism is identical, the compound split might get it to 14 as well, or maybe it cracks. Let me check what item 2's function looks like — maybe it's simpler.

Let me look at lines 7230-7270 of the TU.
