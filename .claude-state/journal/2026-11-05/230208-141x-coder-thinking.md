---
ts: 2026-11-06T06:02:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ms5MQ9egvYHfOustbvYy
---
Still 10. Time 23:02.

Let me think about the 96 vs 95: the extra `andi`. Is there any way to make the mask free? What if the masked value is *already* needed? Look at the target's first block:
```
1870 sll v0,v0,0x10
1874 sra s1,v0,0x10
```
The (s16) cast is sll+sra. Then `cc & 0xFFFF` would be an andi. But wait — `(s16)call & 0xFFFF` — since cc = (s16)call is in [-32768,32767], `cc & 0xFFFF` = cc for cc >= 0, else cc + 65536. Hmm, but for the *comparison* `(cc & 0xFFFF) != 1`, the AND is needed.

What if we compute cc differently: `cc = (u16)call;` (zero-extend, sll+srl) and then `cc & 0xFFFF` is free? Then the first test `(cc & 0xFFFF) != one` = `cc != one` → folds the AND, and the second test `cc == one` would be implied → folds. Bad.

Unless the second test uses the sign-extended value... 

Hmm: what if we have TWO variables: `s16 cs = (s16)call; u16 cu = (u16)call;` and the first test uses cu, the second uses cs. gcc knows cu == 1 → (u16)call == 1 → cs == 1 (since (s16)call and (u16)call have the same low 16 bits). Hmm, would gcc know? Possibly not!

Let's think: 
```c
cs = (s16)func(...);      // sll+sra
cu = (u16)func(...);      // sll+srl
one = 1;
if (cu != one) goto second;
func_8012D624(...);
if (cs == one) goto rejoin;
```
gcc: cu == 1 on the fall-through → (u16)raw == 1 → raw & 0xFFFF == 1. cs = (s16)raw. Does gcc derive cs == 1? It would need to know raw's low 16 bits are 1 and cs is the sign-extension of them. gcc's value-range/combine might not connect cu and cs (different pseudos with different conversions). So the second test might survive!

Cost: cu = (u16)raw → sll+srl (2 insns) — an EXTRA 2 insns (we already have sll+sra for cs). Total +2. Worse.

Unless we drop cs and use only cu for the second test? Then no.

Hmm.

What if the second test compares the *raw* value? `if (raw == one)` — gcc knows raw's low bits are 1 but raw could be 0x10001 → doesn't fold! And the asm would compare the raw register (v0) instead of s1. Target compares s1 (cc). Hmm.

Wait, in the target, the second test is `beq s1,s2` where s1 = cc = (s16)raw. Hmm.

OK.

Let me now consider the *time*. 23:02. I need until ~23:11. 9 more minutes. 

Let me do something useful: let me look at the target's *original* (pinned) RTL to see whether the q/u swap and the allocation could be reached with a different declaration structure. But honestly, it's a WALL.

Let me just do a handful more experiments at a slower pace and then write up.

Actually — let me reconsider the problem statement: "For each item in list.tsv: write a lever-free body of func in G22/<dir>/win.c (bare definition) that scores 0." And WALL is allowed.

I've done ~55 tries on item 4. The wall-clock is the only remaining criterion. Let me fill ~9 minutes with a few more genuine experiments.

Let me try:
y1: the second test using `cu` (u16) and the first using `cc` (s16) — 2 conversions.
y2: cc as s32, the first test `if ((cc & 0xFFFF) != one)`, and the second test `if ((cc & 0xFFFF) == one)` — both masked (l3 was the first+second masked? l3 changed only the first). Let me try both masked.
y3: k10 but with `cc` compared using `(cc & 0xFFFF)` in the first test and `cc == one` in the second, with cc declared s16.
y4: k10 + `q`/`u` declaration order variations.
y5: k10 with the `hold` assignment moved after `u -= 0x380` (semantically wrong, skip).

Let me run y2/y3/y4.
