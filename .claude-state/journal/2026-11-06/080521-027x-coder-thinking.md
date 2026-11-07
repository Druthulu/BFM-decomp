---
ts: 2026-11-06T15:05:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PFIUNfIGN8Pfx5g8t98c
---
Hmm, no label. Maybe the object only holds the function's includer plus the TU's later part; the symbol may be renamed. Let me check the log for the symbol list: `mipsel-linux-gnu-objdump -t`. Actually let me instead find the target object in build/ and compare.

Alternative approach: the delever tool already tells me the single differing slot. Rather than deep RTL, let me try more spellings empirically. That's cheaper.

Actually wait — maybe there's a smarter approach: the diff says mine[217:219] vs target[217:219] with only line 218 differing. So mine at 218 = andi, target = sll; and 219 must be identical in both. So mine at 219 = target at 219. If target 218=sll and 219=X, then mine 218=andi, 219=X. So mine's sll is missing?! But counts are equal... then mine must have the sll somewhere else that target lacks — but no other diff region exists. Contradiction unless the sll in mine is at a position where target has an equal insn. Since target has sll at 218 and mine at some other index... the diff alignment would show it.

Unless: target has BOTH andi and sll and mine also has both, just swapped in adjacent slots — the diff would then show a 2-line region with both lines differing. It shows one differing line only (217 identical bne, 218 differs).

So: mine 218 andi, target 218 sll, and mine 219 == target 219. Both sequences have 237. So mine has one extra andi and lacks one sll compared to target, but they're offset such that... impossible with equal counts unless the missing/extra pair is exactly this swap. Yes! A swap: mine has {andi} where target has {sll}, and elsewhere mine has {sll} where target has {andi}? No, that'd be 2 regions.

OR: target has both `sll` and `andi` in the tail, mine has `andi` at 218 and `sll` at 219; target has `sll` at 218 and `andi` at 219 → then line 218 differs AND 219 differs (andi vs sll) → 2 differing lines. But the diff shows only 218 differing... unless the region printing cut it. It printed lines 217 and 218 only (mine[217:219] = 2 lines: 217,218).

Hmm, then 219 in both must be the same insn. So target's tail has sll at 218 and something at 219; mine has andi at 218 and the same thing at 219. Then where did mine's sll go, and target's andi?

Possibility: target does NOT have an andi at all! Target = orig = launder, and the `& 0xFFFF` might be folded away by gcc since vol | (0x3000|sx) with vol's range unknown... Actually target has the andi probably: 237 insns include it.

Alternatively mine has no sll (folded?) — `sx = sx << 8` can't fold.

I think the diff printer's regions are computed by a sequence aligner that may absorb. Let me not obsess.

Practical: I need the target's exact tail. The target object is the banked build. Where? build/src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.o? Let me check quickly with ls of build/src/ov_SC03_099 (inside project, fine).

Then objdump the target object, find the function (it should have the label since the banked build includes the C def). Compare tails.

Let me do that.
