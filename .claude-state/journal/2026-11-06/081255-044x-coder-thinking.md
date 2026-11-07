---
ts: 2026-11-06T15:12:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XOTITTBOkpjM4WSJzKf5
---
c_i2: 237 ins, score 4 — order improved slightly? c_i3 failed (a1.c has no '/* lever 3:').

Let me check c_i2's diff. Score 4 vs 2. Hmm, worse.

Let me think about flipping li a0 vs ori. 

In target, the li a0,2715 comes first. In mine (i1), the ori comes first.

What if I give the li an earlier birth by making the call's first arg a variable computed earlier? No, that changes insns.

What if the `vol = vol | 0x3000;` uses a different form so fold moves it: e.g. `vol |= 0x3000;` (compound) — same insn.

What if the 2nd set is `vol = (vol | 0x3000) & 0xFFFF;`? Then the ori is computed as part of a bigger expression... and the call arg becomes `(vol | sx)` — no wait, then the arg's `& 0xFFFF` would be redundant.

Hmm, alternatively: put the ori in the call arg as target does, and put the 2nd SET of vol somewhere else entirely — e.g. `vol = (u16)vol;` — but that gave the delay-slot problem. Unless we combine `vol = (u16)vol` with... 

WAIT. What about combining c_u16 (cast at the division, score 2, delay-slot issue) with something that removes the andi from the delay slot? 

Hmm, what if the cast is on the vol at the *call arg* and the 2nd set is `vol = vol | 0x3000` — no, that's i1.

Let me try to flip the li/ori order by making the ori depend on something later. What if I write:
```
sx = sx << 8;
func_8002D4C8(0xA9B, (vol | 0x3000 | sx) & 0xFFFF);
vol = vol | 0x3000;   -- can't, after the call
```

What about:
```
vol = vol | 0x3000;
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
Redundant ori 0x3000 in the arg — fold would simplify (vol|0x3000|0x3000) = vol|0x3000. Value same. The arg would be `(vol | sx)` after simplification. But the extra `| 0x3000` in the expression might make fold reorder. Try it.

Alternatively, flip by moving the shift before the ori:
```
vol = vol | 0x3000;
sx = sx << 8;
```
vs
```
sx = sx << 8;
vol = vol | 0x3000;
```
c_i1 had ori after the shift → ori first in the block. i2 had ori before the shift → score 4 (let me see its diff).

Let me look at i2's diff to see what changed.
