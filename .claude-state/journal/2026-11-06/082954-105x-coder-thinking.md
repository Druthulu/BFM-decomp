---
ts: 2026-11-06T15:29:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vzjWn2AJHsbGtWgC2iri
---
Target tail:
```
5124: bne a2,v0,5134
5128: sll a2,a2,0x8        (delay)
512c: li a2,15
5130: sll a2,a2,0x8
5134: li a0,2715
5138: ori a1,a1,0x3000
513c: or a1,a1,a2
5140: jal
5144: andi a1,a1,0xffff    (delay slot of jal)
```
So the target has the final `andi a1,a1,0xffff` in the jal delay slot at 5144. And the `ori a1,a1,0x3000` at 5138.

In a2 (mine), the andi a1,a1,0xffff is in the *bne* delay slot at 5128 (mine[218]) and the sll a2,a2,0x8 is... somewhere. So my extra `vol & 0xFFFF` andi got scheduled into the bne delay slot, and the target's andi (the call's `& 0xFFFF`) is at the jal delay slot.

Hmm, so the counts match because the target's final andi moved? No — the target has an andi at 5144 too. If mine has an extra andi at 5128, mine should have 238. But it says 237. So maybe mine's `vol & 0xFFFF` *replaced* the final andi (folded into it): `(vol & 0xFFFF) | ...` then `& 0xFFFF` → gcc might merge the two masks into one andi. Then mine has one andi (at the bne delay slot) instead of the target's one andi (at the jal delay slot). And the `sll a2,a2,0x8` that was in the bne delay slot got displaced.

So the diff: mine moved the andi from the jal delay slot to the bne delay slot, displacing the sll.

Interesting. So a2 is close but the mask got scheduled differently.

Let me try other 2nd-set values that don't add a mask:
- `vol = vol | 0;` folds.
- `vol = vol + 0;` folds.
- `vol = vol ^ 0;` folds.
- `vol = vol * 1;` folds.
- `vol = (s16)vol;` — hmm, a sign-extend of vol. vol = ((0xA0-av)*0x7F)/0xA0. The final value is masked with 0xFFFF, so (s16)vol is safe? The call arg is `(vol | (0x3000|sx)) & 0xFFFF`. If vol is negative, (s16)vol preserves the low 16 bits → same after masking. So `vol = (s16)vol;` is safe. It would emit sll+sra (2 insns) unless folded... probably folds to nothing? Let me test.
- `vol = (u16)vol;` — zero-extend, emits andi (like a2).

Hmm.

What about giving vol a 2nd set via the *call arg expression* itself, e.g. `vol = vol | (0x3000 | sx);` then call with `vol & 0xFFFF`? That's a1-like (8).

Let me think about the sched1 birth boost: the launder's 2nd set kills the boost. A "real 2nd set" needs a set of vol. The value can be anything since the final mask... no, the value matters.

Option: `vol = vol & 0xFFFF;` → andi (a2, score 2).
Option: `vol = (s16)vol;` → sll/sra (2 insns) — probably worse.
Option: `vol = vol | 0x3000;` → ori (a1, score 8).

Hmm, a2's issue is the andi's *position*. The scheduler moved it into the bne delay slot. The target has the andi at the jal delay slot (it's the call's mask).

Wait — maybe the problem is that a2's extra andi is redundant and gcc merged it with the final mask, changing the LUID/scheduling. What if we make the 2nd set a *different* operation that folds into something already there? E.g., `vol = vol + 0x3000;`? Then the value changes by 0x3000 — but the final mask is 0xFFFF and the OR 0x3000... no, adding 0x3000 ≠ oring.

What about `vol = vol | 0x3000;` and call `(vol | sx) & 0xFFFF` — a1 scored 8 (236 ins). Let me see a1's diff; maybe it's close.

Let me check a1's diff.
