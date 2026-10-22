---
ts: 2026-10-22T07:24:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hZSibcJe1fAZB3fiViWl
---
Very close! cand14 = score 2, 192 ins.

The diff: at 136-137:
mine:   136 bne a2,v0,cb0 ; 137 andi a1,a1,0xffff
target: 136 bne a2,v0,cb4 ; 137 sll a2,a2,0x8

So the target has the `sll a2,a2,0x8` (the sx << 8) in the branch delay slot, and mine has the `andi a1,a1,0xffff` there. The branch targets differ (cb0 vs cb4) because of the layout shift.

So the difference is which instruction fills the bne's delay slot: the target has `sll a2,a2,0x8` (the sx<<8), mine has `andi a1,a1,0xffff` (the mask).

Note the target's sequence:
```
ca0: li v0,16
ca4: bne a2,v0,cb4
ca8: sll a2,a2,0x8
cac: li a2,15
cb0: sll a2,a2,0x8
cb4: li a0,2533
cb8: ori a1,a1,0x3000
cbc: or a1,a1,a2
cc0: jal
cc4: andi a1,a1,0xffff
```
So the target's delay slot has the `sll a2,a2,0x8` and the `andi` is in the jal's delay slot.

In mine, the `andi` landed in the bne's delay slot and the `sll a2,a2,0x8` elsewhere (the jal's delay slot?). So the two delay-slot fillers swapped.

The C comment in the tree says: "sx = sx << 8; /* in place, so reorg can steal it into the bne delay slot */".

So the target has the sll in the bne's delay slot. Mine has the andi there.

Hmm. So my extra `vol = vol & 0xFFFF;` created an extra andi that competes for the delay slot. Wait — the target ALSO has an andi (at cc4, in the jal's delay slot). So both have an andi; the difference is which one goes where.

Hmm, in mine the `andi a1,a1,0xffff` — is it the one from my `vol = vol & 0xFFFF` or from the call arg's `& 0xFFFF`? If mine has TWO andis (one from `vol & 0xFFFF` and one from the call arg's `& 0xFFFF`), the count would be 193. It's 192 = the target. So gcc folded them: `vol = vol & 0xFFFF;` then `(vol | (0x3000|sx)) & 0xFFFF` → gcc's combine folded the double mask ✓ (so the value's mask is applied once).

So the emitted andi is the combined mask, and it's placed in the bne's delay slot instead of the jal's.

So my extra statement changed the scheduling slightly: the andi is now available earlier (right after the vol division) so the delay-slot filler picks it.

Hmm! So the fix: make vol's 2nd set happen LATER (after the sx<<8) or make the andi not available for the bne's delay slot.

Options:
(a) Move the `vol = vol & 0xFFFF;` statement to AFTER the sx computation and the sx<<8 — i.e., just before the call:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
sx = sx << 8;
vol = vol & 0xFFFF;         /* the 2nd set, placed last */
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
Hmm, but the tree's asm is BEFORE the sx computation (right after the vol assignment). The asm's position matters for the RTL/UIDs. Hmm, but the asm's 2nd set is what we want; its position affects the scheduling.

Hmm, but wait: in the tree, the asm is right after the vol assignment and before `sx = (sx + 0xA0) / 0x14;`. In cand14, my `vol = vol & 0xFFFF;` is also right there ✓ — the same position. The difference is that the asm is a zero-byte insn whereas my statement is a real andi insn (which competes for the delay slot).

So the problem: my 2nd set emits an instruction (the andi) that can be stolen into a delay slot.

Hmm! But the target ALSO has an andi (the combined mask). The target's andi is in the jal's delay slot. So in the target, the andi is scheduled LATE (after the sll). In mine, the andi is scheduled EARLY (right after the vol division) → available for the bne's delay slot.

Why? Because in the target, the mask is applied to the COMBINED value (vol|0x3000|sx) which is only available after the sx computation → so the andi is late ✓. In mine, the mask `vol & 0xFFFF` is on vol (available early) and the combined `& 0xFFFF` was folded into it → so the andi is early ✗.

So I need the 2nd set to be a real instruction that does NOT emit an andi... or the andi to be late.

Hmm! What if the 2nd set is a compound assign that emits an instruction which is NOT the andi? E.g. `vol = vol + 0;` → folded.

What if the 2nd set's instruction is something that lands late? Hmm.

What if I put the 2nd set AFTER the sx<<8 but keep the andi on the combined value? I.e.:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
sx = sx << 8;
vol = vol & 0xFFFF;      /* 2nd set — but then the andi is on vol (early value) */
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
Hmm, the andi would still be folded into the combined mask (gcc combines `(vol & 0xFFFF) | ...` & 0xFFFF → the mask is redundant → the final andi on the combined value) → the andi is late ✓ and vol's 2nd set exists ✓ (the compound assign on vol creates a SET of vol even if the value is folded?).

Hmm! Careful: if gcc folds `vol & 0xFFFF` into the final mask, then vol's assignment might be eliminated → vol has 1 set again ✗.

Hmm. But in cand14 the fold DID happen (192 ins = target) and yet the score was 2 — so the 2nd set survived enough to fix the multiply order ✓. So the SET survived (the andi was applied to vol and then the combined mask was folded away? or the other way).

Hmm, let me think: in cand14, is the andi in the output applied to vol (early) or to the combined value? The diff shows mine has `andi a1,a1,0xffff` in the bne's delay slot and the target has `sll a2,a2,0x8` there. So in mine the andi is EARLY. Since the target's andi (on the combined value) is late, mine's andi must be a different one (on vol) — but then there would be 2 andis in mine (192 total though...). Hmm, let me count: maybe the target has an andi and mine has 2 andis but one fewer something else? No, both 192.

Let me just look at mine's assembly around there. Let me disassemble cand14.

Actually, let me think about it more cleverly: the goal is a real 2nd SET of vol that emits no instruction (or emits an instruction that lands in the right place).

Since `vol = vol & 0xFFFF;` seems to work for the boost (score 2 vs 39), let me try variants:
(a) `vol = vol & 0xFFFF;` placed at various positions (after sx<<8).
(b) `vol = vol & 0x7F;` (a different mask).
(c) `vol = vol | 0;` → folded (score 39 ✗).
(d) `vol = vol ^ 0;` → folded ✗.
(e) `vol = vol & -1;` → hmm, might be folded.

So the AND with a real mask works. Let me try (a): move the statement after the sx<<8, and also try keeping the call's mask.

Hmm, but semantically: `vol = vol & 0xFFFF` — the value is unchanged for vol ≤ 0x7F ✓ (the target's vol is (160-|sx|)*127/160 ∈ [0,127]).

But hold on: is the C-level change acceptable? "real C moves only" — yes, this is a plain C statement. But it CHANGES the semantics of the source slightly (vol is masked) — for the actual runtime values it's identical (vol ≤ 0x7F). Hmm, is that acceptable? The lever-free body must be semantically equivalent to the target. Since vol = ((160-av)*127)/160 with av = |sx| ≤ ... hmm, av could be large if sx is large. sx = L.sxy[0] (a u16 cast to s16) → |sx| ≤ 32768 → (160 - av) could be negative → vol = negative*127/160 → negative! Then `vol & 0xFFFF` changes the value (e.g. -1 → 0xFFFF) → the call arg (vol | 0x3000 | sx) & 0xFFFF would differ!

Hmm: with the original C, the arg = (vol | 0x3000 | sx) & 0xFFFF — the mask is applied to the whole thing, so the result is the same whether or not vol is pre-masked ✓✓ (masking vol first then ORing then masking again = the same final value, since the final mask kills the high bits anyway).

So `vol = vol & 0xFFFF;` before the call is SEMANTICALLY IDENTICAL ✓ (the final & 0xFFFF makes it moot).

So cand14 is semantically fine.

Now, the remaining issue: the delay-slot filler picks the andi instead of the sll.

Let me look at where mine's andi is and what the target's is. Let me disassemble cand14 and look at the region 130-150.

Then try moving the `vol = vol & 0xFFFF;` later (after `sx = sx << 8;`).

Let me do both: disassemble cand14 and try cand17 (the statement movedafter sx<<8).
