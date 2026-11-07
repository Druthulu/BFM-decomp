---
ts: 2026-11-07T00:21:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_O8mCkz73SeOkaG3jBZBM
---
Now I see. Mine (nolau):
```
5aec: bgez v1, 5afc      ; if (iVar4 >= 0) skip
5af0: slt v0,s1,v1       ; DELAY SLOT: compare (with un-negated v1!)
5af4: negu v1,v1         ; iVar4 = -iVar4
5af8: slt v0,s1,v1       ; compare again (with negated v1)
5afc: beqz v0, 5b08
```
So mine emits the slt TWICE: once in the delay slot (using the un-negated value, but it's harmless because the branch skips to 5afc where the second slt's result is used... wait, no).

Hmm, actually: bgez v1, 5afc — if v1 >= 0, jump to 5afc, where `beqz v0` uses the delay-slot slt's result (computed with the un-negated v1, which equals v1 since v1>=0). Correct.
If v1 < 0: fall through, negu v1, then slt at 5af8, then beqz. Correct.

So mine has a duplicate slt (the delay-slot one and the real one) — that's 2 slt insns. Target has 1 slt + 1 nop.

Target:
```
5aec: bgez v1, 5af8
5af0: nop
5af4: negu v1,v1
5af8: slt v0,s1,v1
5afc: beqz v0,5b08
```
So the target fills the delay slot with a nop (no duplicate slt).

Mine's reorg duplicated the slt into the delay slot. Why? Because in mine, the insn after the branch (in the fall-through) is the negu, and the branch target has the slt. Reorg "steals" the slt from the target into the delay slot when the branch is taken... Actually reorg fills the delay slot from the *target* insn if it's safe. Here the slt at 5af8 (the target) is copied into the delay slot? No, it's MOVED... but mine has both.

Hmm, actually reorg's `fill_slots_from_thread` can move an insn from the fall-through or the target into the delay slot. If it moves the target's slt into the delay slot, the branch target changes to 5afc (after the slt). That's what mine did: bgez v1, 5afc and the slt in the delay slot. But then there's ALSO a slt at 5af8 in the fall-through — that's the original slt, which is still needed for the v1<0 path.

Wait: the slt at 5af8 is the original (needed when v1<0). The delay-slot slt (5af0) is a *copy* for the v1>=0 path. Hmm, that's reorg duplicating.

Hmm, actually reorg's delay-slot filling from the target: it copies the insn at the branch target into the delay slot only if the target insn is on the path. Here the branch target is 5af8 (slt). Filling the delay slot with the slt and changing the branch to 5afc is a valid optimization (the slt is needed on both paths).

In the target, reorg did NOT do this. Why? Because in the target's RTL, there's an extra insn (the launder asm) between the negu and the slt, so the slt is not the immediate branch target — the asm is. Then the branch target is the asm... hmm.

Wait, in the target (with the launder), the RTL is: bgez, negu, [asm insn], slt. The branch (bgez) targets the insn after the negu = the asm. reorg might fill the delay slot with the asm? No, asm can't go in a delay slot. So it emits a nop.

Then the asm is deleted later (it's an empty asm with a tied output; after reload it becomes nothing), leaving the nop.

So the launder's asm blocks the delay-slot fill, leaving a nop.

Lever-free: I need an insn between the negu and the slt that (a) is not schedulable into the delay slot and (b) disappears or becomes the nop.

Hmm, the target's nop is the delay slot. So the target's structure has a nop there. 

What if the C has a statement that generates a no-op-ish insn? E.g., `iVar4 = iVar4;`? flow deletes it.

Hmm. What if the order of the two ifs is swapped? Let me think: the C is
```
if (iVar4 < 0) iVar4 = -iVar4;
[launder]
if (iVar5 < iVar4) iVar5 = iVar4;
```
If instead:
```
if (iVar4 < 0) { iVar4 = -iVar4; }
iVar5 = (iVar5 < iVar4) ? iVar4 : iVar5;
```
Hmm.

What if I reorder to compute the abs differently, e.g.:
```
iVar4 = (iVar4 < 0) ? -iVar4 : iVar4;
if (iVar5 < iVar4) iVar5 = iVar4;
```
Then the RTL: compare, branch, negu, ... The slt might be placed differently.

Hmm. This is a 1-insn scheduling/reorg issue. Let me try a handful of variants on nolau (pins kept):
1. `if (iVar4 > -1) ... else ...` 
2. `iVar4 = (iVar4 < 0) ? -iVar4 : iVar4;`
3. Reorder the two ifs.
4. Use a temp for the comparison.
5. `iVar5 = (iVar5 < iVar4) ? iVar4 : iVar5;` (ternary)
6. Add a statement between.

Let me look at the C:
```
        iVar5 = t;
        if (t < 0) {
            iVar5 = -iVar5;
        }
        if (iVar4 < 0) {
            iVar4 = -iVar4;
        }
        __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4));  // launder
        if (iVar5 < iVar4) {
            iVar5 = iVar4;
        }
```
In nolau, the launder is removed.

Target structure (from the assembly):
- bgez v0 (t<0) → move s1,v0; negu s1
- bgez v1 (iVar4<0) → nop; negu v1
- slt v0,s1,v1 (iVar5 < iVar4)
- beqz v0 → move s1,v1

So the C order is: t abs, iVar4 abs, max.

Lever-free, the max's slt is duplicated into the delay slot.

Idea: make the max a ternary or a different form so the RTL differs:
```
iVar5 = (iVar5 < iVar4) ? iVar4 : iVar5;
```
That's an if/else (set iVar5 in both arms). The target has `beqz v0, 5b08; nop; move s1,v1` — i.e., `if (iVar5 < iVar4) iVar5 = iVar4;` (conditional move). A ternary would produce the same.

Hmm.

Idea: swap the operands: `if (iVar4 > iVar5) iVar5 = iVar4;` → the slt becomes slt v0, iVar4, iVar5? The target has `slt v0,s1,v1` = slt(iVar5, iVar4). So the C is `iVar5 < iVar4`. Keep.

Idea: reorder the abs and max: do the max for iVar4 before its abs? No.

Hmm, what if the launder's position matters: the target's nop comes from the launder's asm being between the abs and the max. Lever-free, I need an insn there.

What if I move the `iVar4` abs AFTER the max? No.

Hmm, what if the C uses `iVar4` in the max via a temporary:
```
iVar5 = (iVar5 < iVar4) ? iVar4 : iVar5;
```
same.

What about:
```
{
    s32 m = iVar4;
    if (iVar5 < m) iVar5 = m;
}
```
An extra copy → extra insn.

Hmm. The target has 117 insns and mine (nolau) also 117 — but mine has a duplicate slt and target has a nop. So the target's nop is "free" (the delay slot must be filled with something). So I need the slt NOT to be stolen into the delay slot.

What if I put a statement between the abs and the max that survives? That would add an insn → 118. Unless it replaces the nop. Hmm! The target's delay slot is a nop. If I add a real statement that generates an insn which reorg puts in the delay slot... but the target's delay slot is nop, so any insn there would differ.

Hmm.

OK, what if the difference is the ORDER of the two abs blocks? Target: t abs first, then iVar4 abs, then max. Mine: same.

What if the max is computed BEFORE the iVar4 abs? No.

Hmm. Let me try the variants empirically. It's cheap.

Actually, let me reconsider: maybe the launder's role is to prevent reorg from stealing the slt into the delay slot, and lever-free we can't. This is a `sched1-*` or `reorg-*` wall.

But it's worth a few tries. Let me generate variants of the block.

Let me do it.
