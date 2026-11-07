---
ts: 2026-11-06T15:15:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dW7vZj5Pl8TEa1zVZWpp
---
e1 moved sx to $s0 (callee-saved) because vol's extended live range forced a different allocation. Bad.

OK. Let me now think about whether there's a completely different second set that's zero-cost and placed such that sched2/reorg don't steal it.

Observation from b4: the andi is scheduled right after the branch by sched2 (I hypothesized). Let me verify by checking the .sched2 dump's final order. If sched2 puts the andi there, then any pre-branch andi that's independent will be sunk there.

What if the second set is *dependent on sx after the shift* so sched2 can't move it before the sll? E.g., `vol = vol & (0xFFFF & ~(sx ^ sx))` — fold removes. 

What if the second set uses sx in an identity way that fold can't remove: e.g. `vol = vol & 0xFFFF | (sx & 0xFFFF0000)`? That's not identity (sx<<8 has bits above 16? sx <= 15, sx<<8 <= 0xF00, so sx & 0xFFFF0000 = 0, but the compiler doesn't know). That would add an and+or. No.

Hmm. What about `vol = vol & 0xFFFF;` placed after the sll and relying on combine to merge it with the final andi *if I write the final expression without the outer mask*? 

```
sx = sx << 8;
vol = vol & 0xFFFF;
func_8002D4C8(0xA9B, vol | (0x3000 | sx));
```
Semantics: vol is masked; sx<<8 with sx<=15 → 0xF00; 0x3000|sx<<8... wait, `0x3000 | sx` where sx is already <<8 → 0x3000|0xF00 = 0x3F00. All within 16 bits. So the OR is within 16 bits. But the original has `& 0xFFFF` after the OR — which the compiler emits as andi at 5a8. If I drop it, the andi disappears (1 fewer insn) — but the target HAS it. Unless the vol mask takes its place... The target's andi at 5a8 masks the OR result. Mine would have `andi vol` before the or. Different instruction position/operand → not byte-identical. So no.

OK, think about the delay-slot filler differently: what if I can make reorg's thread-copy of the sll happen *in addition* to having the andi? The target has 237 insns: it includes the duplicated sll. b4 has 237: the andi + one sll. To get 237 with both the andi and two slls, we'd need to remove one insn elsewhere — impossible.

Therefore: the andi must NOT be in the function. So the second set must be a zero-cost set that isn't a separate insn.

Zero-cost sets that aren't separate insns: a set that is part of a *multi-set insn* (a PARALLEL) or a set of a pseudo that's coalesced into an existing insn. Hmm — e.g., a value that's set by a `move` that gets coalesced away by the register allocator! If I write `vol = vol;`... deleted.

What about making the second set a *copy that gets coalesced*: e.g. `s32 v2 = vol;` and then use v2? The copy `v2 = vol` might be coalesced into the same register (zero-cost), but that's a set of v2, not vol.

What if I write `vol = ((0xA0 - av) * 0x7F) / 0xA0;` and then later `vol = vol + (sx & 0)`? fold removes sx&0.

Hmm what about a second set that's a *no-op cast assignment* that survives as a SUBREG? E.g., `*(s32 *)&vol = vol;`? That's a store/load — extra.

What about `vol = (s32)(u32)vol;`? fold removes.

OK, different tack: maybe the birth-boost target is NOT vol. Let me determine which insn gets boosted. Let me diff the sched1 priorities between a0 (no launder) and b4 (mask). The b4 log showed all priorities small (1 and 12) in block 15 — no huge boost. Let me look at a0's block 15 log.

Actually both had priority 1/12. So the birth boost isn't in block 15? Hmm, birthing_insn_p requires the dest reg live at block start. In block 15 (459-492), which regs are live at entry? From the RTL, insn 459 is the block head. Let me look at what insn 459 is and what regs are live. 

Wait, maybe the difference between a0 and b4 is not sched1 at all. Let me diff the two dumps' sched2 sections. Actually, let me directly compare the final RTL order (pre-reorg) between a0 and b4. The .dbr dump's beginning lists insns. Let me find the bne and its neighbors in the .dbr of both.

Hmm, this is a deep rabbit hole. Time check needed. Let me check the clock and decide.

Alternative pragmatic approach: since b4 is 1 insn away and the issue is the delay slot, maybe a *different* zero-cost second set that sched2 won't move after the branch. What if the second set is on a DIFFERENT pseudo that is live at block start? Recall birthing_insn_p: dest live at block start AND set once. Which pseudo in block 15 is live at block start and set once? Look at the RTL: insn 481 `(set (reg:SI 209) (plus (reg/v:SI 194) 160))` — reg 194 is sx, live at block start (read before written in this block). reg_n_sets[194]: sx is set multiple times (in this block at 488, and earlier). So not birthing.

Hmm, what about reg 196 (vol)? vol is NOT live at block start (it's born in this block). So not birthing either. So neither is boosted. Then what changes between a0 and b4?

Maybe the difference is in `local-alloc`/`global-alloc` because vol's set count changed the priority/ref counts! The C0505 catalog says: "Set counts steer three passes: a second identical assignment demotes sched1's birthing boost (sched.c:2469-2545), keeps a constant off REG_EQUIV's doubled live length (local-alloc.c:1016-1064), and keeps loop.c from hoisting (loop.c:705)."

"keeps a constant off REG_EQUIV's doubled live length" — hmm. vol isn't a constant.

Wait — maybe the relevant effect is on the *magic constant* pseudo (reg 206 = 0x66666667)! insn 537/538 set reg 206 (lui+ori). In b4's block 15 log: insn 537 priority 1, 538 priority 1. In a0? Let me compare.

Actually, the launder's 2nd set of vol changes vol's REG_N_REFS / live length, which affects allocation priorities, which changes which pseudo gets $a0 (the magic constant) vs $a1 etc. In the no-launder version, the diff showed the magic constant in a2 and pan in a0; with the mask (b4), the constant is in a0 (target). So it's an allocation effect, not scheduling!

Hmm, b4's final code has the constant in a0 (`lui a0,0x6666`), matching target. And a0 (no launder) had `lui a2,0x6666`. So the mask changes the allocation of the constant.

This is getting too deep. Let me consider a different lever entirely: maybe restructure so vol's live length changes naturally, e.g., declare vol inside the `if` block or reuse another variable. C0505: "One value per temp: a local that dies in several places is refused by local-alloc... substitute in place, split, or declare per block."

Actually! Idea: what if vol is declared INSIDE the `if` block (block-scoped) rather than at the top? It's already declared inside the `if (flag >= 0 && ...)` block (line: `s32 vol;` is inside). Yes it is.

Hmm.

Let me try yet another simple thing: the launder is an asm re-tie. What if we replace it with a *volatile* read/write of a local? E.g., `*(volatile s32 *)&vol = vol;` — that's a memory store+load, costs insns.

What about making vol `volatile`? `volatile s32 vol;` — then every access goes through memory. Bad.

OK. Let me reconsider: maybe there's a *natural* C body that gets this right without any second set — the dev swept 9 spellings, but let me try a few structural things:
1. Compute vol as `(0xA0 - av) * 0x7F / 0xA0` in different association: `(0xA0 - av) * 0x7F / 0xA0` is the same.
2. Use a different intermediate: `vol = (0xA0 - av); vol = vol * 0x7F; vol = vol / 0xA0;` — 3 sets, and the target's code is exactly `subu; sll; subu; mult` — the same instructions! The multiply by 0x7F is `sll v1,v0,7; subu v1,v1,v0` — that's combine's strength reduction. With separate statements, combine may still do it. And vol would be set 3 times (subu, sll-subu, div). Hmm, but the intermediate regs change (vol would hold the intermediate). Let me try it: it's like t1 but with the mult split too.

Actually t1 (`vol = (0xA0-av)*0x7F; vol = vol/0xA0;`) scored 14. The problem there: the multiply result goes into vol's register (a1) instead of v1. In the target, the multiply chain uses v1/v0 and the div result goes to a1. So vol holding the intermediate changes allocation.

Hmm.

Let me reconsider the e-variants' failure: 245 ins because sx went to s0. That's because vol's live range extended past the call? No... e1's `vol = vol | ...` at the call — vol's live range is the same. Hmm, but the diff shows sx in s0 and a new s2. So the allocation shifted a lot.

Let me try: `vol = vol & 0xFFFF;` placed at the launder position but make it *not* sinkable by sched2. sched2 (post-reload scheduler) schedules within basic blocks. It moved the andi after the branch? Insns can't move across the branch insn within a block... unless the branch splits the block. The andi is before the branch in the RTL; sched2 can't move it after the branch (different block). So the andi in the delay slot must have been placed there by REORG (moving it from before the branch into the slot). So my earlier reorg analysis (resource conflict) was wrong somewhere.

Let me look at reorg's `eligible_for_delay` and `stop_search_p` / `insn_sets_resource_p` semantics. Maybe `set` doesn't accumulate a1 because `subu a1,a0,v1` was itself moved into... no.

Wait, maybe the andi was moved by `fill_slots_from_thread` from the *fall-through thread* — i.e., the andi IS in the fall-through after the branch in the RTL. That would mean sched2 moved it there, which requires it to be in the same basic block as the branch... The branch is a jump_insn; sched2's `schedule_block` treats a block ending with a jump. Insns before the jump can be reordered among themselves but not past the jump. So the andi can't be after the branch.

Unless the basic block structure is different: the `if (sx == 0x10)` might compile to a branch whose fall-through is the `li a2,15`, and the block boundary... the andi is in the block that ENDS at the bne. So reorg moved it backwards-scan.

So `insn_sets_resource_p(trial, &set)` must be false for the andi. Let me check `set` contents: `mark_set_resources (insn, &set, 0, 0)` for the branch itself — the bne sets nothing (pc). Then for each skipped trial: `mark_set_resources (trial, &set, 0, 1)`. Hmm — the last arg `1` = include_delayed? Let me look at the signature: `mark_set_resources (x, res, include_delayed_effects, include_calls)`. The call `mark_set_resources (trial, &set, 0, 1)` means include_calls=1, include_delayed=0. So it marks the sets of trial.

The skipped trials from the branch backwards: `li v0,16` sets v0. `subu a2,v1,v0` sets a2. `sra v1,a2,3` sets v1. `mfhi a2` sets a2. `sra v0,v0,0x1f` sets v0. `subu a1,a0,v1` sets a1. So a1 ∈ set. Then the andi `(set (reg a1) (and (reg a1) 0xFFFF))` — `insn_sets_resource_p(trial, &set, 1)` → a1 ∈ set → TRUE → conflict → not eligible.

But the andi's destination at the RTL stage might not be a1 (hard reg). Post-reload, yes hard regs. Hmm, but the andi is at 58c in the final code — after reload, so a1.

Unless the andi is NOT the vol mask but a *different* andi... Let me verify: in b4's final disassembly, is the `andi a1,a1,0xffff` at 58c the vol mask, or could it be something else? a1 = vol. Yes.

Hmm, wait: maybe the andi is in the delay slot via `fill_slots_from_thread` because the andi was moved to the *end of the block before the branch* and reorg's backward scan found it, but the resource check passed because... `insn_references_resource_p (trial, &set, 1)` where `set` = resources set by the branch. Hold on, re-read:

```
CLEAR_RESOURCE (&needed);
CLEAR_RESOURCE (&set);
mark_set_resources (insn, &set, 0, 0);
mark_referenced_resources (insn, &needed, 0);
```
For the branch insn: `mark_set_resources(branch, &set, ...)` — a branch sets the PC. `mark_referenced_resources(branch, &needed, 0)` — references a2, v0.

Then the scan checks:
```
if (! insn_references_resource_p (trial, &set, 1)
    && ! insn_sets_resource_p (trial, &set, 1)
    && ! insn_sets_resource_p (trial, &needed, 1))
```
The andi: references a1; does it reference `set` (=pc)? no. Does it set `set` (pc)? no. Does it set `needed` (a2,v0)? no. → ELIGIBLE! The `set` is NOT accumulated across trials before this check... Actually it IS accumulated at the bottom of the loop:
```
mark_set_resources (trial, &set, 0, 1);
mark_referenced_resources (trial, &needed, 1);
```
So after each skipped trial, `set` and `needed` grow. But the check happens BEFORE accumulating the current trial. Let's re-trace:
- trial = `li v0,16`: references none, sets v0. Check: references set(pc)? no. sets set(pc)? no. sets needed({a2,v0})? YES (v0) → conflict. Accumulate: set={pc,v0}, needed={a2,v0}.
- trial = `subu a2,v1,v0`: references v1,v0. Check: references set={pc,v0}? YES (v0) → conflict. Accumulate: set={pc,v0,a2}, needed={a2,v0,v1}.
- trial = `sra v1,a2,3`: references a2. set contains a2 → conflict.
- ... 
- trial = `subu a1,a0,v1`: references a0,v1; sets a1. Check: references set (which includes v1, a0?) — a0 was set by `sra a0,t1,6` and `mfhi t1`... yes, v1 ∈ set → conflict.
- trial = `sra a0,t1,6`: references t1 ∈ set (mfhi t1) → conflict.
- trial = `mfhi t1`: references hi; sets t1. hi ∈ set? The mult insns set hi/lo. Are hi/lo in `set`? `mark_set_resources` on the mult parallel — the mult pattern sets (reg:SI hi) and (reg:SI lo)? For smulsi3_highpart, it sets a pseudo (205) and clobbers scratches; the actual mult writes hi/lo implicitly (clobber scratch is match_scratch). Hmm.
- Eventually the scan reaches the mults, the magic constant, etc., all conflicting, then the andi at the top.

For the andi: does it reference/set anything in the accumulated `set`/`needed`? By then, set includes many regs including a1 (from `subu a1,a0,v1`) → `insn_sets_resource_p(trial, &set, 1)` → sets a1 ∈ set → conflict → NOT eligible.

So the andi should not be stolen by the backward scan. Therefore it must be from the thread.

Hmm! Unless the scan stops before reaching the andi due to a label. But then the andi wouldn't be stolen either.

So the andi must be in the fall-through thread (after the branch). Which means sched2 moved it after the branch... impossible... UNLESS the branch's basic block is split differently: the `if (sx == 0x10)` — the bne is the branch, and the andi is before the `sx = (sx + 0xA0)/0x14` statement, which is before the branch. So it's in the branch's block.

Wait, maybe reorg's `fill_slots_from_thread` for the fall-through thread can move insns from *before* the branch into the slot if they're "owned" by the thread? No.

Let me just look at the .dbr dump around the bne to see the actual decision. Let me find the bne insn in the .dbr and the andi.

Actually — maybe I should check the .sched2 dump, which is the state *before* reorg. If the andi is after the branch there, then sched2 moved it. Let me grep the .sched2 RTL for the andi and bne order. The .sched2 file contains the final RTL (all insns in order). Let me find insn numbers for the andi (478) and the branch.
