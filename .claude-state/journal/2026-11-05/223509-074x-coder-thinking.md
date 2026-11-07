---
ts: 2026-11-06T05:35:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Pgf8zqVhsCI9T12dXkmL
---
h1: the copy is present in the right place (`move v0,v1` in the delay slot) and the structure is right; only iVar1/iVar2 are swapped (iVar1 in a0, iVar2 in v1). Same as a1.

So the ONLY remaining issue is the priority: iVar1 (5.33) vs iVar2 (12).

I need to make iVar2's priority < iVar1's.

Options:
(a) iVar2 live range longer.
(b) iVar2 fewer refs.
(c) iVar2 smaller qty size (HImode) — but then the copy merges (unless the cast trick).
(d) iVar1 higher priority.

For (c): what if iVar2 is HImode AND the copy uses a cast that creates a cross-mode op that isn't a no-op? With iVar2 s16, `tmp = (s16)iVar2` is a no-op. What if `tmp = (s16)(iVar2 + 0)`? folds.

Hmm, what if we keep iVar2 SI (for the copy trick) but make iVar1's qty higher priority by *increasing its refs* via an extra real use that doesn't add an instruction...

Wait! Here's an idea: what if the *store* in each arm uses iVar1 twice? E.g., write the store as:
`((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;`
What if instead: `*(s16 *)((u8 *)iVar1 + 0x10) = (s16)tmp;` — same.

What if we compute the address as `iVar1 + 0x10` stored in a temp used twice? That'd add instructions.

Hmm, what about the reload line `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;` — could we write it as `iVar1 = iVar1 = ...`? no.

What about (a): lengthen iVar2's live range. What if we use iVar2 in the `skip2` block (after both ifs)? The skip2 block is after the second if. If iVar2 (from the first block) were used there... its live range would span the whole function — but then it'd be global-alloc'd (s-reg), changing everything.

What if we use iVar2 in the *second* block's assignment: `iVar2 = CAST_SIGN(s16, iVar1, 0x12);` — that's a redefinition; the first qty dies before.

Hmm, what if the second block uses a *different* variable (iVar3), so iVar2's first qty... still dies at the last test.

OK, what about (b): reduce iVar2's refs. In a1: 8 refs. What are they? Let me count in a1's cse2 RTL: reg74 occurrences in the first block. Let me grep.

Actually, the n_refs for a pseudo in local-alloc is REG_N_REFS, which counts every mention (each use in each insn, and each set). In the RTL: 
- insn 26: set reg74 (1)
- jump 29: reg74 in the condition (1)
- insn 33: reg74 as source (1)
- jump 38: reg74 in condition (1)
= 4. But the dump says 8. So maybe there are notes or the count is doubled.

Hmm, maybe REG_N_REFS counts the reg in the note (REG_EQUAL) too? Or the `subreg` uses of reg76...

Whatever.

Let me try a different tactic: what if we make the copy `tmp = iVar2;` happen where iVar2 has a *dead* second def? No.

OK, let me consider: maybe the answer is to make iVar1's live range SHORTER by loading it closer to its uses. The target's `lw v1,32(s0)` is at the very start (before the first test). But what if the source loaded iVar1 later? E.g.:

```c
iVar2 = CAST_SIGN(s16, ((Unkstruct_800B5CB8 *)a0)->unk20, 0x10);
iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
```
Then gcc CSEs the two `((Unk*)a0)->unk20` loads into one, but the order of the load vs the CAST_SIGN: the CAST_SIGN needs the pointer, so the load comes first. iVar1's def would be the same load. No change.

Hmm, what if iVar1 is defined *after* iVar2 by loading unk20 twice (gcc CSEs to one load)? The single load is born before the CAST_SIGN. Same.

What if the arms reload iVar1 each time (`iVar1 = ((Unk*)a0)->unk20;` inside each arm)? That adds `lw` instructions. Target has none.

OK, what about this: make the *first* iVar1 live range end at the CAST_SIGN by using a different variable in the arms — but the arms would need the pointer. Unless the arms use `((Unk*)a0)->unk20` directly and gcc CSEs it... but the store through iVar1 would invalidate the memory cache? Actually, in the target, the arms' store uses v1 (iVar1). If the source wrote `((Unkstruct_800B5CB8 *)((Unkstruct_800B5CB8 *)a0)->unk20)->unk10 = (s16)tmp;`, gcc would need to load unk20 before the store (1 lw), and the store itself doesn't modify a0+0x20 (unknown alias, but gcc's cse might keep the value in a register anyway since it's already loaded). Hmm — if we write the direct expression in BOTH arms, gcc would CSE both into one register = iVar1. So same.

But the *reload* structure: after the arms, the source has `iVar1 = unk20;`. If we used direct expressions, we'd have 3 loads of unk20, CSE'd into... hmm, the store to `unk10` (through the pointer) may alias `a0+0x20`, so gcc must reload after the store. That's why the target reloads at 2aa0.

So the arms: `sh v0,16(v1)` uses the held v1. And after the arms, reload.

I think the target is exactly what the pinned code produces.

Let me try ONE more idea: make iVar1 a *parameter-like* variable with more refs by using it in the CAST_SIGN of the second block too... no, it's reloaded.

Actually, hold on! What about making iVar1's qty SIZE larger? If iVar1 were a `struct` or a wider type... no, it's a pointer.

What about making iVar1's qty *smaller* (HImode)? It's a pointer, no.

Hmm, what if we make iVar2's qty smaller by loading it as `s16` into an HImode variable AND keeping the SI copy via a *separate* SI variable that's not iVar2? Like:

```c
s16 iVar2h;
s32 iVar2;      // SI copy of iVar2h, used in tests?
```
Hmm, the tests must use the SI variable (a0). 

What if:
```c
s16 h;
iVar2 = CAST_SIGN(s16, iVar1, 0x10);   // iVar2 SI (a0)
h = (s16)iVar2;                        // h HImode
tmp = h;                               // tmp SI
```
Then the qty list: iVar2 (SI, 8 refs/10) 9.6; h (HI, short) ; tmp (SI, 20/16) 20.
Allocation: tmp $2, iVar2 $3, iVar1 $4. Same problem.

Unless iVar2's refs drop because the copy now goes through h... but iVar2 is still used by both tests and the copy.

Hmm.

Let me compute what iVar1 would need: pri > iVar2. If iVar2 is 12 (a1), iVar1 needs 8 refs/live < 8 insns: 3*8*4/8 = 12 (tie → regno tiebreak: iVar1 reg73 < iVar2 reg74 → iVar1 wins!). So if iVar1's live range were exactly 8 insns with 8 refs, we'd get a tie and iVar1 wins by regno.

Can iVar1's live range be 8 insns? It spans the first if (from the load to the last arm store). No.

If iVar2's pri were exactly equal to iVar1's 5.33... e.g., iVar2 8 refs/live 18: 3*8*4/18 = 5.33 — tie! Then regno tiebreak → iVar1 (73) wins. So if iVar2's live range were 18 insns (same as iVar1's), iVar1 wins.

How to make iVar2 live 18 insns? Extend its live range by ~8 insns. Hmm.

What if iVar2 is used in the `skip2` block? That would extend it a lot (too much) and make it global.

What if iVar2's last use is moved later, e.g., the second test is placed later? The second test is right after the copy.

Hmm, what if we reorder: `tmp = iVar2; if (iVar2 < 0)` — the test is immediately after.

What if we add the `if (iVar2 < 0)` check *inside* the arms? Like:
```c
if (iVar2 != 0) {
    tmp = iVar2;
    if (iVar2 < 0) {
```
No.

OK, let me try: what if the two tests are merged into one? `if (iVar2 != 0)` and `if (iVar2 < 0)` are separate.

Hmm, let me look at the actual target: both tests use a0 (iVar2), and iVar2's live range is 10 insns. iVar1's is 18. So the target's iVar2 pri (9.6) > iVar1 (5.33) but the pin saved it.

I'm now fairly convinced this is a WALL of the class "lreg-qty-order" (the pin reserved $3; lever-free the s16 test temp outranks the pointer).

But wait — before WALL, let me try one more clever idea: make iVar1 the *same* qty as something that gets $3... 

Hmm, actually, here's a thought: what if we make iVar1's live range longer so it becomes a *global* allocno? Then global-alloc would give it a callee-saved reg ($16+), not $3. No.

What if iVar1 is used in a way that local-alloc sees it as born early in the block with a long life → lower pri. No, we want higher.

OK. Let me also try the "dead reset" trick on iVar2 to see if it changes the qty: e.g., after the second test, `iVar2 = 0;`? That would change the value for... the arms don't use iVar2 after. Actually, after `if (iVar2 < 0)` the arms use tmp, not iVar2. So `iVar2 = 0;` right after the second test would be dead. A dead set can extend the live range! And C0414 says dead resets are deleted by delete_dead_from_cse... but the *qty* might change.

Hmm, but if the dead set is deleted, no effect.

What about a *dead copy* `iVar2 = tmp;` after the second test? That would extend iVar2's live range to include the copy... but it's dead.

Let me just try a few:
k1: after the second test (`if (iVar2 < 0) {`), inside the then-arm, add nothing.
k2: `tmp = iVar2; if (iVar2 < 0) { ... }` + `iVar2 = tmp;` at the end of the if body (dead, same value).
k3: extend iVar2 by using it in the `skip2` condition? no.

Hmm, k2: `iVar2 = tmp;` at the end of the if body — this is a real set (same value), might survive and extend iVar2's live range across the arms! That's exactly "dead copy + 2nd def" from moves.md line 199. Let's try:

```c
if (iVar2 != 0) {
    tmp = iVar2;
    if (iVar2 < 0) { ... } else { ... }
    iVar2 = tmp;    // dead (iVar2 not used after within the block?) 
}
```
But iVar2 IS redefined in the second block later, so this copy is dead. gcc's cse/combine might delete it. But maybe it survives as a real move (extra instruction) — that would break the insn count.

Hmm, risky but worth a try.

Actually, here's a cleaner idea to extend iVar2's live range *without* extra instructions: make the second test's condition use iVar2 AND make the arms use iVar2... no.

Let me just try k2 and a couple more, then WALL.

Actually, WAIT. Let me reconsider (c): iVar2 HImode with the copy surviving. What if iVar2 is s16 and the copy is `tmp = (s16)iVar2` — no-op. But what if iVar2 is s16 and the copy is `tmp = (s32)iVar2` where tmp is s32 — also a no-op cast. Hmm.

What if iVar2 is s16 and tmp is s32, and the copy is written as `tmp = (s16)iVar2;` — the C compiler sees (s16)iVar2 → int (promotion) → same. No.

What if we declare iVar2 as `s16` and tmp as `s16` and then `tmp = iVar2;` — d1 (10, lhu, spill).

Why did d1 use lhu? Let me look at d1's source: `s16 iVar2; s16 tmp;` and the copy `tmp = iVar2;`. The load `iVar2 = CAST_SIGN(s16, iVar1, 0x10);` — that's an lh (signed). But the asm shows lhu. Weird. Maybe gcc decided the value is only used as unsigned because... `if (iVar2 < 0)` — hmm.

Let me look at d1's diff more closely. It showed:
```
10 lhu v0,16(v1) | nop
12 nop | move v0,a0
```
So mine at insn 10 is `lhu` while target at 10 is `nop` (target insn 9 is lh a0, 10 is nop due to load delay). Hmm, mine has lhu at 10 and something at 9. Actually mine's insn 9 might be `lh`? The diff only shows replacements at 10.

Let me dump d1's asm directly. Actually d1's frame is 56 — there's a spill, so it's structurally off.

OK, let me try one more: iVar2 s16, tmp s32, copy `tmp = iVar2;` (b1, merged) — what if I add `do { } while (0)` around the copy to split the EBB and prevent cse from replacing the second test's operand? Then iVar2 HImode (pri 4.8) and the copy might survive. Let me try that (k4).

k5: iVar2 s16, copy `tmp = (s16)iVar2;` with a do-while split.

Let me try k4/k5 and k2.
