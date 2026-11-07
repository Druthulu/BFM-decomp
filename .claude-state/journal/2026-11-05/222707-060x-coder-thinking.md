---
ts: 2026-11-06T05:27:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vyt68fyhrD3bSVcEQ8YE
---
b1 = same as n1 (merged). So declaring iVar2 s16 didn't keep the copy.

Let me think about how to keep the copy while preserving iVar1=v1.

Observation: a1 (`tmp = (s16)iVar2`) kept the copy but the priority flipped. What if we use a copy that doesn't change iVar2's refs/live? E.g., `tmp = iVar2;` then a real 2nd set of *tmp* that cse can't fold, like `tmp = (s16)tmp;` — wait, that's a set of tmp from tmp; cse might delete it (redundant). With a cast, combine may fold.

Hmm. What about using the do-while to split the EBB so cse can't propagate iVar2 into tmp's use? In a3/a4, the do-while was around the copy but it didn't help. Maybe the split needs to be *between* the copy and the first use, and the first use is in a different block already (the if arms).

Wait — actually, why does cse propagate iVar2 into tmp's use? `tmp = iVar2; if (iVar2 < 0) { tmp += 0x80; ... }`. The copy and the `tmp += 0x80` are in the same basic block (the then-arm). cse propagates iVar2 for the read of tmp.

To break it: make the read of tmp not in the same cse "class". If we could insert a NOTE_INSN_BLOCK boundary between the copy and the use... a3 did `do { tmp = iVar2; } while (0);` — the block END is after the copy, so the use is in a different block. But cse still propagated? Maybe cse doesn't respect block notes within an EBB (it uses extended basic blocks, and a do-while(0) is removed by the time cse runs? The loop notes are removed by loop.c? No, cse runs before loop).

Hmm, C0535 says do-while(0) splits cse1's EBB. But a3/a4 didn't keep the copy. Maybe the do-while block boundary didn't survive into the RTL at the right place, or cse's equivalence is per-regno not per-block (it flushes at basic block boundaries but the copy and use are in the same basic block).

Actually the then-arm: `tmp += 0x80` — tmp is read-modify-write. The copy `tmp = iVar2` is in the *parent* block (before the if), and `tmp += 0x80` is in the then-block. Are they different basic blocks? The if statement creates a branch; the copy is before the branch, the use after. So they ARE different basic blocks! cse processes per extended basic block; the branch ends the EBB. So cse shouldn't propagate across... unless cse does global (it does: cse is global across the whole function, using reg_eqv, but it invalidates at labels/jumps? gcc's cse is a global pass but equivalence is invalidated at basic block boundaries where the reg is set... Actually cse uses `reg_eqv` tables and processes insns linearly; at a label/jump it may flush. In 2.7.2 cse, `invalidate_from` etc.

Anyway, empirically cse merged them.

Let me look at the RTL of n1 after cse to see where the copy went. Let me check n1.i.cse around the function.

Actually, let me try a totally different anti-cse mechanism: the dead-reset (C0414). The idea: after `tmp = iVar2`, do something that makes iVar2's value "dead" in cse's table, e.g., reassign iVar2? Can't.

What about making tmp's first use happen *before* the copy? No.

Alternative: make the copy a *real* operation: `tmp = iVar2 + 0x80;` in the then-arm and `tmp = iVar2 - 0x80` in the else? That changes the structure but semantically:
```c
if (iVar2 < 0) { tmp = iVar2 + 0x80; ... } else { tmp = iVar2 - 0x80; ... }
```
No copy instruction then (the addiu computes from iVar2 directly). The target needs a move.

Hmm.

What about making `tmp` and `iVar2` different types where the copy is a real instruction: `tmp = (s32)(s16)iVar2`... same as a1.

Let's look at a1's allocation problem more concretely. a1: iVar1→a0, iVar2→v1, tmp→v0. Target: iVar1→v1, iVar2→a0, tmp→v0. So only iVar1 and iVar2 are swapped!

If I could make iVar1's priority higher than iVar2's... iVar1 is the pointer loaded from a0->unk20 (a global-ish pointer). In n1 (no copy), iVar1 got v1. In a1 (with copy), iVar2 got v1.

The difference: in a1, iVar2 is `lh` into a *separate* pseudo that is copied to tmp; maybe the sign-extend makes iVar2's live range longer.

Hmm what if we make the copy from a *different* temp so iVar2's range stays short: e.g.
```c
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
if (iVar2 != 0) {
    tmp = (s16)iVar2;   // a1
```
In a1 the copy is `tmp = (s16)iVar2`, so iVar2 is read once (for the copy) plus the branch test.

Alternatively:
```c
if (iVar2 != 0) {
    tmp = iVar2;
    tmp = (s16)tmp;   // real 2nd set? 
```
Hmm.

What if we swap which variable gets the copy: `iVar2` stays, and we copy to `tmp` via a *different* route that doesn't extend iVar2's life: e.g., copy from the *memory* again? `tmp = CAST_SIGN(s16, iVar1, 0x10);` — that's a second lh (extra instruction). No.

What about copying from the *parent* variable? There is none.

Hmm, what if the copy is placed in a different block to change priorities? E.g., inside each arm:
```c
if (iVar2 < 0) {
    tmp = iVar2;
    tmp += 0x80;
```
Then the copy is in the arm block. cse would propagate again.

Let me look at this from the target's perspective: the target's `move v0,a0` is in the beqz delay slot — that's the *parent* block, right after the test. So the copy is in the parent block.

I wonder: maybe the answer is a *dead copy* that changes priorities? Hmm.

Let me look at the actual qty priorities by dumping a1 and n1 and finding the assignment. The .lreg dump doesn't show assignments, but the .s does. Actually, the .lreg dump DOES show the "Register N used ..." lines with ref counts; the allocation order is by priority.

n1: 72 (a0, 12 refs/46 insns), 73 (8/18), 74 (6/6), 75 (20/16).
Wait, these are local qtys. The priority formula in gcc 2.7.2 local-alloc: `priority = (n_refs * 1000) / (live_length)`. Hmm, but then 74 (6/6=1000) > 73 (8/18=444) > 75 (20/16=1250)... 75 is highest.

Hmm, but 75 got v0 (highest), then 73 got v1, then 74 got... also v0? In n1 they merged, so 74 and 75 might be the same pseudo split.

Let me look at the actual .s of n1 to see which regs.

I think I'm spending too long. Let me try a different, more promising approach: since the pin is redundant (n1 already has iVar1 in v1), the only issue is keeping the copy `tmp = iVar2` without disturbing priorities. 

What if I keep the copy by making `tmp` used *before* being set? No.

What if `tmp = iVar2;` is replaced by `tmp = iVar2, iVar2 = tmp;`? no.

Hmm, here's an idea: make the copy *dead* but present in the RTL, like the "dead copy vol2=vol" trick from moves.md line 199: "MATCH — dead copy vol2=vol + a 2nd def vol=vol|0x3000 (both dead in the RTL) give vol 2 defs". Interesting: a dead copy can change scheduling/priority.

What if we add `tmp2 = iVar2;` (unused)? That's a dead copy — gcc deletes it.

OK, alternative idea: use `&&`/`||` folds? No.

Let me reconsider: maybe the target isn't `tmp = iVar2` but `iVar2` being copied to `tmp` via the *comparison*. Hmm.

Actually — WAIT. What if the source has `tmp = iVar2;` and the arms use `tmp`, and the *launder* is what keeps it, but the lever-free equivalent is to make `tmp` **unsigned** while iVar2 is signed (or vice versa)? b4 (u16 tmp) scored 8 = merged.

Hmm.

Let me look at a1's RTL to see why iVar2's priority rose. Actually, let me try a1 but with the copy in the form `tmp = iVar2; tmp = (s16)tmp;`? 

Or: what if the copy uses a **u8** intermediate: `u8 t8 = iVar2; tmp = t8;` — two copies. Too many.

Let me try the reverse: make iVar1's priority higher by adding a *use* of iVar1 (a dead use that folds). E.g., in the first block, `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;` — already there. The reload at the end of the block: `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;` — present.

What if we use iVar1 in the `if` test: `if (iVar2 != 0)` → no.

Hmm, let me look at the a1 dump and the n1 dump priorities, to understand. Let me grep the .lreg for "Register 7x" in a1.

Actually, I realize there might be a much simpler answer: maybe with the copy present, the *ordering* of local qtys is determined by `qty_compare` which compares n_refs first:
```
static int qty_compare_1 (q1, q2) {
  if (q1->n_refs != q2->n_refs) return q1->n_refs > q2->n_refs ? 1 : -1;
  ...
}
```
Let me read tools/reference/gcc-2.7.2/local-alloc.c.
