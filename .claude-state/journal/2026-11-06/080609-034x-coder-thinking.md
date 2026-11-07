---
ts: 2026-11-06T15:06:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pB25rkQWy7GZ5iea9TTF
---
Self-assign and |0 and -0 are deleted (236 ins, pan-first = no effect). Masks all give 237 ins score 2 (andi steals delay slot).

So the only way to get 237 is a real andi. The andi is +1 ins but the target is 237 while the no-launder body is 236. Interesting: the launder itself is zero-byte yet orig is 237. Why is no-launder 236? Because the launder changes scheduling which changes... the `nop` after `mult` at 560? In the orig there's `addiu v0,a2,160; nop; mult v0,a0`. The nop is a hazard filler? Without the launder, maybe that nop disappears and code is 1 ins shorter. Actually the no-launder body has 236 insns; the launder adds no code but changes the schedule such that an extra nop/hazard insn appears (the `nop` at 560 between addiu and mult — a load-delay/hazard slot). So the launder's "cost" is a scheduling artifact.

So with the mask (b4), we get 237 ins but the andi occupies the delay slot and the sll stays out. The count matches but the schedule differs at that point: target has TWO sll (one stolen, one real); mine has one sll + one andi (stolen). So mine is effectively +1 andi, -1 sll compared to target — meaning mine is MISSING an sll somewhere? No: target 58c sll (steal), 590 li a2,15, 594 sll (real). Mine: 58c andi, 590 li a2,15, 594 sll (real). So mine has only ONE sll, target has TWO. Where did target's second sll come from? `sx = sx << 8;` is one statement → one sll. The second sll is the "in place, so reorg can steal it" — reorg duplicates the insn: it copies the sll into the delay slot while keeping the original? Let me check reorg: it "steals" by moving, but for a `sll a2,a2,8` where the fall-through overwrites a2, the delay-slot copy is the one that matters for the branch-taken path, and the original remains for the fall-through path. Actually reorg's `fill_slots_from_thread` can copy an insn into the delay slot while leaving the original if the insn is needed on the fall-through too (it duplicates). Yes — reorg duplicates "simple" insns into delay slots.

So the target's 237 includes a duplicated sll. Mine's 237 includes an andi in the slot instead. To match, the andi must not be chosen for the slot, so reorg picks the sll and duplicates it. The andi is chosen because it's earlier in the block and eligible.

How does reorg choose? It scans insns from the branch backwards (fill_slots_from_thread). It picks the first eligible insn before the branch. The insn right before the bne is `sll` (from `sx = sx << 8`). But the andi (vol mask) is placed before `sll` in source (launder position is before `sx = (sx+0xA0)/0x14`, and the sll is after). So order: vol mask (launder pos), sx div, if, sll. Reorg scans backwards from bne: first candidates are insns between the test and the branch. The sll is right before the bne — it should be picked first! Unless reorg scans forward from the branch target backwards differently.

Hmm, reorg's `fill_slots_from_thread`: it looks at insns after the branch (the fall-through) and tries to move them into the delay slot, or looks before. For a conditional branch, delay slot fill looks at insns BEFORE the branch (from the previous insn backwards) and also the target thread. The sll is the immediately preceding insn. But wait — the sll's result is used by the fall-through (after the if), so moving it into the delay slot would still work (delay slots execute). Reorg moves it and then, since the fall-through also needs it, duplicates.

But the andi is also before the branch, just earlier. If reorg scans backwards from the branch and picks the FIRST eligible, it'd pick the sll (nearest). Unless the sll is not eligible for another reason: `sll a2,a2,8` where a2 is set in BOTH paths before it? In target, the sll uses a2 which was set by `li a2,15` in the fall-through... no wait. Let's re-read the target order:

```
584 li v0,16
588 bne a2,v0,598     ; if sx != 16 goto 598
58c sll a2,a2,0x8     ; delay slot: sx <<= 8
590 li a2,15          ; fall-through: sx = 15
594 sll a2,a2,0x8     ; sx <<= 8
598 li a0,2715
```
Hmm, that's odd: if sx==16, delay slot does `16<<8 = 0x1000`, then li a2,15, then sll → 15<<8. So the delay slot sll is dead on the fall-through (a2 overwritten). Reorg moved the sll from after `li a2,15` to the delay slot? No — the source is:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
sx = sx << 8;
```
Compiled: bne; li a2,15; sll. Reorg sees the `sll` after `li 15` (in the fall-through thread) and moves a COPY into the delay slot (thread copy), keeping the original for the fall-through. That's "fill_slots_from_thread" — it copies the insn from the fall-through (thread) into the delay slot when the thread is likely... So the delay-slot copy comes from the insn AFTER the branch, not before.

In mine (b4), the delay slot contains `andi a1,a1,0xffff` — which is BEFORE the branch. So reorg preferred an insn from before the branch (the andi) over copying the sll from the thread. Why? Because the andi is a "simple" insn before the branch and reorg's `fill_simple_delay_slots` runs first and finds it. Hmm, in target there is no eligible insn before the branch, so the thread copy wins.

So to match: the vol mask must NOT be an eligible pre-branch insn. Options: place the andi AFTER the branch (in the fall-through), i.e. after the sll statement, but then it merges/duplicates.

Alternatively make the second set be an insn that reorg won't steal (e.g., a branch, a load?). A `lw` before a branch could be stolen too. A `jal`? no.

Or: place the second set so it lands in a *different* basic block. If the second set of vol is in a block that's not the one containing the bne, reg_n_sets still counts it globally! birthing_insn_p uses `reg_n_sets[i]` which is function-wide. So I can put a second set of vol ANYWHERE else in the function — e.g., in the earlier `if (sx < 0)` block or at the very beginning — as long as it's not dead-deleted by flow (it must survive: either used or a real set that flow keeps).

But a second set that's dead gets deleted by flow (dead store elimination runs before scheduling? flow does DCE). If the set is used somewhere, it stays but costs an insn.

Idea: reuse vol for an existing computation elsewhere! E.g., use vol as the temp in the earlier part of the function, so it's genuinely set twice with real code and no extra insn. Look at the function for a temp I can replace with vol: e.g. `s32 t` is used for func_8004787C results. If I reuse `vol` instead of `t`... but that changes the variable's live range and might change allocation of the whole function.

Hmm. But actually there's a cleaner idea: the second set could be at the point where vol's value is consumed — i.e., write `vol = vol | (0x3000|sx)` and pass that? No, that's a third set and would use vol as the arg temp.

Wait: actually we want vol to have 2 sets, and the second set must be zero-cost. What if the second set IS the existing `andi a1,a1,0xffff` at 5a8 (the outer mask)? That insn sets a1 (vol's reg) — in the source, `(vol | (0x3000 | sx)) & 0xFFFF` is passed as an argument; the result lands in a1. That's not a set of the vol pseudo (it's the argument temp). If I write it as `vol = (vol | (0x3000|sx)) & 0xFFFF; func_8002D4C8(0xA9B, vol);` — then vol is set twice: once by the division, once by the mask-or. The second set is the SAME insn sequence (andi at 5a8 → a1), just named vol instead of an anonymous temp. Zero cost! And reg_n_sets[vol]=2 → no birth boost.

But careful: with vol set a second time at the end, the vol pseudo's live range extends to the call — that's already the case (vol is used in the call expression). The register allocation: vol was a1, and the argument temp also a1. Identical.

But: does the second set happen before the bne? No — it's after (in the block after the if, before the jal). And the birth boost is decided per insn; the vol division insn (554) is in the same basic block? The function-wide reg_n_sets is 2 → no boost. 

This seems very promising. Let me try:

```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
sx = sx << 8;
vol = (vol | (0x3000 | sx)) & 0xFFFF;
func_8002D4C8(0xA9B, vol);
```

Wait but there's a subtlety: `vol | (0x3000|sx)` — the order of operations in the original was `func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);`. Same expression. Just assign to vol first. Should be zero-cost.

Also, does flow/cse keep vol's second set? Yes, it's live into the call.

Let me test (c1).
