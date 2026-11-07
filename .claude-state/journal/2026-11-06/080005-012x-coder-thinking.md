---
ts: 2026-11-06T15:00:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GMjNhhrGZlBz8QAfYu8c
---
Key: "Set counts steer three passes: a second identical assignment demotes sched1's birthing boost (sched.c:2469-2545)". So the launder `__asm__("" : "=r"(vol) : "0"(vol));` is a re-tie — the equivalent is a second identical assignment to vol.

Actually the launder ties vol as both input and output — it's a second set of vol with the same value. In plain C: `vol = vol;`? That would be deleted. But `vol = (vol);`? Hmm.

From moves: func_8018AA98: `pv &= 0xFF000000` (compound assign) = a REAL 2nd SET. Plain `pv = pv & mask` (new temp) does NOT.

Here vol is int, values 0..0x7F. What second set could be zero-byte? Options:
- `vol |= 0;` — fold removes it? `vol | 0` folds to vol in fold, and then `vol = vol` is a copy... would it remain? A self-copy `vol = vol` is deleted by cse/flow probably.
- `vol &= 0xFFFF` — would produce andi (a real insn), not zero-byte, unless combine knows the range. Actually vol = ((0xA0 - av) * 0x7F)/0xA0. Division by 0xA0... compiler can't prove < 0x10000? Actually ((0xA0 - av)*0x7F) can be at most 0xA0*0x7F = 0x4F60 < 0x8000, and /0xA0 gives at most 0x7F. But gcc doesn't do range analysis like that. So andi would appear → +1 insn → score nonzero unless the target had... no, target is 237 ins exactly. So can't add an insn.

Wait — what does "second identical assignment" mean concretely? "a second identical assignment demotes sched1's birthing boost". The launder `__asm__("" : "=r"(vol) : "0"(vol))` is a second set of the same value. Plain C equivalent: `vol = vol;` — is that deleted? Let's check gcc 2.7.2: `vol = vol` where vol is a local — the assignment would be a simple set of a reg from itself. In gcc's RTL, that's `(set (reg) (reg))`. cse might eliminate it... Actually cse does eliminate self-sets? Hmm, in gcc, `insn = reg` where same reg — cse would replace the source with the dest and then it's a no-op set; jump/flow may delete. Let me just test.

Actually a known trick: use a second assignment of the same value through a variable that isn't obviously the same, e.g. `vol = ((0xA0 - av) * 0x7F) / 0xA0;` repeated? That's a duplicate computation — cse merges them, so no.

Hmm. What about restructuring: compute vol via two statements:
```
vol = (0xA0 - av) * 0x7F;
vol = vol / 0xA0;
```
That's a real second set of vol! Two sets: vol = product, then vol = vol/0xA0. And in the original, `((0xA0-av)*0x7F)/0xA0` is one expression → one set (div of product). Splitting into two statements gives vol two sets: the multiply's dest is vol, then the divide's dest is vol. That's exactly "second identical assignment demotes sched1's birthing boost" — well, it's a real second set, zero extra instructions (the multiply and divide are both there). 

But careful: does it change codegen? In the original, the multiply computes into a scratch then div. With `vol = (0xA0-av)*0x7F; vol = vol / 0xA0;` the multiply's result goes into vol's hard reg, then division. In MIPS, div uses hi/lo, mult uses hi/lo. `((0xA0 - av) * 0x7F) / 0xA0`: multiply then divide. Assignment target doesn't matter for mult/div (results in hi/lo, then mflo). So the register allocation might be the same. Actually the original target likely was: `subu`, `mult`, `mflo`... wait 0x7F multiply could be shift-sub. Let me not speculate; test.

Actually, the launder exists because sched1 hoists the PAN multiply (`(sx + 0xA0)/0x14`? no, that's division) — hmm, "the PAN multiply" refers to `(0xA0 - av) * 0x7F` (vol computation) vs... the note says "Both magic-multiplies write the same match_scratch, so sched1 ... always hoisted the PAN multiply first". Two multiplies: vol = (0xA0-av)*0x7F and sx = (sx+0xA0)/0x14 (division, but signed division by constant becomes multiply by magic). Right! `(sx+0xA0)/0x14` is a magic multiply. Both use hi/lo scratch, so sched1 can swap them. The launder gives vol a second set (the asm), demoting its birth boost so vol's multiply stays first.

So a real second set of vol at that point: split the vol computation so that the final `vol` set happens right there. But the launder is AFTER vol is fully computed and BEFORE sx's division. The second set needs to be at that position. Options:
- `vol = vol & 0x7F;` — real andi, +1 ins. Not ok.
- Split: `vol = (0xA0 - av) * 0x7F;` before, then after... no, the second set would need to be the division: `vol = vol / 0xA0;` placed where the launder is. That means:
```
vol = (0xA0 - av) * 0x7F;
vol = vol / 0xA0;      /* second set at the launder's position */
sx = (sx + 0xA0) / 0x14;
```
Wait but the launder is between `vol = ...` and `sx = ...`. So this split puts the division after the multiply, both before sx. That's exactly the same statement order as the original single expression. And vol has 2 sets. 

But is the multiply's result in a register before division? mult writes hi/lo; mflo needed. In original, `((0xA0-av)*0x7F)/0xA0`: gcc computes `(0xA0-av)`, multiply by 0x7F (likely sll-sub or mult), then divides that by 0xA0 (magic multiply). With the split, same. The only difference is set counts (2 vs 1) on vol pseudo.

Hmm, but will gcc's CSE merge? `vol = (0xA0-av)*0x7F; vol = vol / 0xA0;` — the second uses vol, so no merge. Good.

Alternatively, a simpler approach: from moves G11, `pv &= 0xFF000000` compound assign = real 2nd set. Here `vol &= 0xFFFF` would add an andi. But what about `vol %= 0x10000`? worse.

Another: `vol = vol * 1;`? fold removes.

Let me think about what preserves the exact instruction stream. The target has 237 insns. The split approach should be zero-byte if allocation unchanged.

But hold on — does the second set actually change scheduling priority? sched1's birth boost: an insn that sets a value which is live... The boost is for the insn that "births" a pseudo at the start of a basic block? Let me recall sched.c:2469-2545. Actually it's `priority()` computing: `if (INSN_DEP_COUNT... )` Hmm. Let me look at the source.

Let me first just test the straightforward candidates using dt.sh. Let me set up item 1.

First, copy src def to orig.c. But the brief says "copy to <dir>/orig.c" — a bare definition body? Let me look at how dt.sh works and what the body file should be.
