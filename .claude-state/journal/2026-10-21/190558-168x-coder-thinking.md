---
ts: 2026-10-22T01:05:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ESNtOblJNq7kUqM2s1tZ
---
The target:
```
ca4: bne a2,v0,cb4      ; if (sx != 0x10) goto cb4
ca8: sll a2,a2,0x8      ; delay slot: sx <<= 8   (!!!)
cac: li a2,15           ; sx = 0xF
cb0: sll a2,a2,0x8      ; sx <<= 8  (the in-place shift)
cb4: li a0,2533
cb8: ori a1,a1,0x3000
cbc: or a1,a1,a2
cc0: jal func_8019059C
cc4: andi a1,a1,0xffff  ; delay slot: the mask
```
So the target has the `sll a2,a2,0x8` in the delay slot of the *bne* (the speculative shift) AND the real shift at cb0. And the `andi` in the delay slot of the jal.

Mine (castu16 variant): the `bne`'s delay slot has `andi a1,a1,0xffff` and the `sll` is... hmm, the diff said:
```
136  bne a2,v0,cb0 | bne a2,v0,cb4
137  andi a1,a1,0xffff | sll a2,a2,0x8
```
So in mine, the bne's delay slot = `andi` and the target's = `sll`. And the bne's target differs (cb0 vs cb4) — that's just a consequence of the layout.

So the difference: which instruction fills the bne's delay slot. The source comment says: "sx = sx << 8; /* in place, so reorg can steal it into the bne delay slot */" — the *reorg* pass (branch reordering) can hoist the shift into the bne's delay slot (the speculative execution of the shift before the branch). The target does that; mine doesn't (the mask went there instead).

The mask (`andi a1,a1,0xffff`) is computed at the end (for the call argument). In the target it's in the jal's delay slot; in mine it's in the bne's delay slot. So the *scheduler* chose differently — because of the launder's effect (the vol multiply's position).

Hmm. The launder is on `vol`:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
__asm__("" : "=r"(vol) : "0"(vol));   // launder
sx = (sx + 0xA0) / 0x14;
```
The comment: "sched1 otherwise hoists the PAN multiply ahead of this one" — the PAN multiply is the sx computation (the divide by 0x14). So the launder blocks sched1 from hoisting the sx multiply ahead of the vol multiply.

In the target, the vol multiply (the mfhi/sra sequence at c8c-c9c) comes BEFORE the sx divide (at c84-c98? hmm).

Let me look at the earlier part: 136: sra v1,v1,0x1f ... 140: mfhi a2 ... So the vol multiply's result is in a2, and the sx divide's result is in a2 too (they're sequential: sx = (sx+0xA0)/0x14 → the divide; vol = ((0xA0-av)*0x7F)/0xA0 → the multiply+divide).

Hmm, in the target at 138: `subu a1,a0,v1` (a0 = (sx+0xA0)/0x14? and v1 = the sign) and 140: `mfhi a2` (the vol multiply).

So in the target, the *vol* multiply (mfhi) comes AFTER the sx divide (subu) — i.e. the vol multiply was NOT hoisted ahead.

With the launder removed (and the cast), the vol multiply gets hoisted → a different schedule.

So I need to block sched1's hoisting with plain C. The do-while! An empty do-while(0) between the vol computation and the sx computation would create a scheduling barrier. Let me test: the do-while variant (cb001_dow) scored 25 — worse. Hmm.

Hmm, and the castu16 scored 2.

Let me try: do-while + castu16 (the combos didn't include that? the combos had "dowcast" (s16) and "dowcastu" (u16)). Let me check the combo scores for func_80191020: the top was cb021_castu16 (2). The dow+cast ones? The log showed only the top 5: castu16 (2, 4 frame variants) and dow (25). So the dow+castu16 combo is somewhere below 25.

Hmm.

OK, let me try a different approach for this item: the *order* of the statements. The source:
```
sx = (s16)L.sxy[0];
av = sx;
if (sx < 0) { av = -sx; }
vol = ((0xA0 - av) * 0x7F) / 0xA0;
/* launder */
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
sx = sx << 8;
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
What if the *vol* computation were moved after the sx computation? That changes the order of the operations but not the semantics (they're independent). Then sched1 couldn't hoist the vol multiply ahead (it's already after). Hmm! But the target has the vol multiply *after* the sx divide in the instruction stream — hmm, in the target: `subu a1,a0,v1` (the sx divide) then `mfhi a2` (the vol multiply) → so the vol multiply is after ✓. But the *source* order has vol first! So the target's order is the *scheduled* order (sched1 moved the sx divide up, or the vol multiply down).

Hmm, so in the target, sched1 did NOT hoist the vol multiply ahead of the sx divide. In mine (without the launder), sched1 hoisted the vol multiply ahead (the "PAN multiply" comment says the opposite).

So the statement-order move (swapping the vol and sx computations in the source) might make the *scheduled* order match! Let me try:
```
sx = (sx + 0xA0) / 0x14;     (moved up)
if (sx == 0x10) { sx = 0xF; }
sx = sx << 8;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
func_8002D4C8(...);
```
Hmm, but the "sx = sx << 8" before the vol computation changes the *scheduling* opportunities.

Let me just try a few permutations:
p1: swap the vol and sx-divide computations (keeping the rest).
p2: the vol computation moved to just before the call.
p3: the launder replaced by the do-while + the cast.

Let me write these variants and score. Let me also handle func_801813B0's "k sites" generator in the same batch.

Let me write both generators now.
