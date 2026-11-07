---
ts: 2026-11-06T15:28:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F96HJHywmHirUcIKV3np
---
Item 3's launder-free body has a significant residual around the vol/pan magic-multiply region (indices 204-224). This is exactly the "§21 ZERO-BYTE RE-TIE on vol" / "sched1 hoists the PAN multiply first" lever 3 from the comment.

The launder at line 6630 is `__asm__("" : "=r"(vol) : "0"(vol));` after `vol = ((0xA0 - av) * 0x7F) / 0xA0;`. The comment says: "lever 3: sched1 otherwise hoists the PAN multiply ahead of this one" and "§21 ZERO-BYTE RE-TIE on vol. Both magic-multiplies write the same match_scratch, so sched1 ... is free to swap them and always hoisted the PAN multiply first... only the re-tie does."

So the launder is needed to keep the vol multiply before the pan multiply. The comment says "Source statement order does NOT move it (9 spellings swept, all identical); only the re-tie does."

Hmm. So this is a known wall-ish situation. But we need a lever-free crack.

The moves catalog has several "real 2nd set" tricks that kill sched1's birth boost:
- line 169: "pv &= 0xFF000000 (compound assign) = a REAL 2nd SET of the pinned pv, kills the sched1 birth boost of the pv load; plain pv = pv & mask (a new temp) does NOT"
- line 212: "the re-tie gives vol a 2nd SET (kills sched1 birth boost on the quotient...); plain C: `vol = vol | 0x3000;` right before the call — value preserved because the arg ORs 0x3000 and masks 0xFFFF, and the ori folds into the target ori"

So the trick: give `vol` a real 2nd set that kills sched1's birth boost, with the value preserved and the extra operation folded.

In our function: 
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
__asm__("" : "=r"(vol) : "0"(vol));  // launder
sx = (sx + 0xA0) / 0x14;
...
sx = sx << 8;
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
The launder gives vol a 2nd set. A plain-C equivalent: `vol = vol | 0x3000;` right before the call? In our case, the call is `func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF)`. We could do:
```
vol = vol | 0x3000;
func_8002D4C8(0xA9B, (vol | sx) & 0xFFFF);
```
Wait, the original is `(vol | (0x3000 | sx)) & 0xFFFF`. If vol = vol|0x3000, then `(vol | sx) & 0xFFFF` = `((vol|0x3000) | sx) & 0xFFFF` = same. And the ori would fold: `ori vol,vol,0x3000` then `or vol,vol,sx` — hmm, the target's instruction sequence is `ori ...,0x3000` on VOL and `or` with pan. The comment says: "the OR must be spelled `vol | (0x3000 | sx)`. fold's `associate:` rewrites `(VAR|CON)|ARG1` to `(CON|ARG1)|VAR`, which is what puts `ori ...,0x3000` on VOL and the plain `or` on the pan field".

So the exact spelling matters. If we do `vol = vol | 0x3000;` as a separate statement, then the call arg is `(vol | sx) & 0xFFFF` — the fold might produce the same `ori` + `or`. Let me test.

But the launder's position is right after the vol computation, BEFORE the pan computation. A 2nd set of vol at that position: `vol = vol | 0x3000;` right there. Then `sx = (sx + 0xA0) / 0x14;` etc. Then the call with `(vol | sx) & 0xFFFF`.

That gives vol a 2nd set at the right place (killing the birth boost of the vol quotient) and folds the ori into the call arg. Let me test.

Also note there are register pins ($a1 av pin) still present — allowed.

Let me write candidates:
A1: insert `vol = vol | 0x3000;` after the vol computation, and change the call arg to `(vol | sx) & 0xFFFF`.
A2: keep the call arg as `(vol | (0x3000 | sx)) & 0xFFFF` but add `vol = vol | 0;` (folds, no).
A3: `vol = vol & 0xFFFF;`? changes nothing but the mask... value preserved only if vol < 0x10000. vol = ((0xA0-av)*0x7F)/0xA0 where av is |sx| and sx is s16; vol could be negative? (0xA0 - av) could be negative if av > 0xA0 → vol negative. Then & 0xFFFF would change the value, but the final `& 0xFFFF` masks it anyway! The call arg is `(...) & 0xFFFF`, so vol's upper bits don't matter. So `vol = vol & 0xFFFF;` is safe. But that's a 2nd set with an andi → might add an instruction (or the andi folds into the final mask?). Hmm.

Let me start with A1 (the catalog's proven trick).

Let me look at the exact body region first (lines 6620-6640).
