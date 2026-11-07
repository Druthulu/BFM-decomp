---
ts: 2026-11-06T05:30:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EdQSbAohfqM8gCCDifSX
---
In the orig: jump 38 tests reg74 (iVar2), the copy insn 33 sets reg75 = reg74, then the asm re-sets reg75. Both jumps test reg74. reg74's live range: from insn 26 to jump 38 → 10 insns, 8 refs (pri 9.6). But with $3 pinned, iVar2 gets $4.

So in the target, iVar2's RTL is exactly like a1's! a1's asm:
- `lh v1,16(a0)` — wait, a1 has iVar1 in a0 and iVar2 in v1. So a1's RTL is like the target's but with the allocation swapped.

So the only difference between a1 and the target is the priority: iVar1 (5.33) vs iVar2 (9.6).

To fix: iVar1 must have priority > iVar2. 

Now, iVar1 in a1: 8 refs/18 insns. Its live range in the RTL: from insn 21 (load) to the last use in the arms. In the orig, iVar1 is a hard reg so its qty isn't counted, but its ref count is the same.

Hmm, what if we could make iVar1's live range SHORTER, e.g., 8 refs/12 insns → 8. Still < 9.6.

What if we split iVar1: the source already has a reload after the first if. The first iVar1's live range spans the arms. Hmm.

What if iVar1 is declared as a `u8*`/pointer and used with pointer arithmetic? Same.

What about making iVar1's qty size bigger? Size is 4 for SI.

What if iVar1 gets MORE refs through a foldable use? For instance, in the then-arm the store `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;` — what if we write the address as `iVar1 + 0x10` and the store via a cast? Same ref count.

Hmm, what if the source uses `((Unkstruct_800B5CB8 *)iVar1)` twice in one statement, e.g., `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;` — one ref.

What about the reload: `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;` — one def.

Hmm. To add refs without adding instructions, use a CSE-able expression that gcc folds: e.g., in the condition `if (iVar2 != 0)` — could we write `if (iVar2 != 0 && ...)`? Adds a branch.

What about `(s32)iVar1` casts? Casts don't add refs in RTL (same reg).

Hmm. What if we declare iVar1 as `s32` instead of a pointer? Then `((Unkstruct_800B5CB8 *)iVar1)` casts. Same.

What about making iVar2's live range longer? If iVar2's live range were longer (e.g., 20 insns), its priority would drop to 4.8 < 5.33. How? Use iVar2 after the arms... but it's dead.

Wait — the *second* block: `iVar2 = CAST_SIGN(s16, iVar1, 0x12);`. If we reuse the same variable iVar2 (which we do), its qty in the first block ends at the last use. The second def starts a new qty.

Hmm. What if we move the second block's `iVar2 = ...` load BEFORE the first if? No, it must be after (iVar1 is reloaded).

Hmm, what if iVar2's first-block live range extends because we use iVar2 in the `skip2` code? No.

OK, alternative: what if we make tmp's priority lower so it doesn't take $2, letting iVar2 take $2? Then iVar2=$2, tmp=$3? No, target has tmp=$2.

Alternatively: what if iVar2 and tmp are the same register (merged) but there's still a move? Impossible.

Hmm, let me reconsider the problem. Maybe there's a completely different source shape that yields the target. What if the copy `move v0,a0` is NOT `tmp = iVar2` but rather the result of `tmp` being assigned the *sign-extended* value from a variable that is stored in a0 for the tests?

Look at the target: a0 is used for BOTH tests (`beqz a0` and `bgez a0`) and as the source of `move v0,a0`. tmp (v0) is used in the arms.

What if the source is:
```c
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
if (iVar2 != 0) {
    tmp = (s16)iVar2;   // a1
```
a1 gave iVar2=v1, iVar1=a0. Swapped.

What if we make iVar1 more "attractive"? Let's look at the formula: pri = floor_log2(nrefs) * nrefs * size / (death-birth).

iVar1: nrefs=8 → floor_log2(8)=3, 3*8*4=96, /18 = 5.33.
iVar2: nrefs=8 → 96/10 = 9.6 (orig) or /8 = 12 (a1).

If iVar1's live range were 10 instead of 18: 96/10 = 9.6, tie → qty number tiebreak (lower regno wins). iVar1 is reg73 < reg74, so iVar1 wins! 

So: shorten iVar1's live range from 18 to ≤ 10 insns, or increase its refs.

How? iVar1's live range spans the whole first if because it's used in both arms and reloaded after. In the target, the reload `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;` is at 2aa0, right before the second block. The first iVar1 is live from 2a44 to 2a9c.

What if we use a *separate variable* for the reload (iVar1b)? Then the first iVar1's live range still spans the arms (2a44-2a9c ≈ 22 insns). No change.

What if the arms don't use iVar1 but reload it each time? That adds instructions.

Hmm, what if the store in each arm uses `iVar1` but the first iVar1's *death* is earlier? It's used in the last arm.

OK, different approach: maybe reduce iVar2's refs. In a1, iVar2 has 8 refs. Where do they come from? The sign-extend chain: lh reg76, sll reg77, sra reg74. Then jump 29, copy, jump 36. Hmm, 8 refs seems high. Maybe each jump counts as multiple refs (the branch insn uses reg74 once, but n_refs counts per occurrence in the insn).

Let me look at the .lreg dump's ref counting... it counts `REG_N_REFS`.

What if iVar2 is loaded as an SI directly (no HI/sign-extend chain)? The target asm has `lh a0,16(v1)` — combine folds the sll/sra into the lh. But in the RTL before combine, there's the HI reg + sll + sra.

What if we declare iVar2 as s16? Then the load is `lh` into an HImode reg, and the test `iVar2 != 0` on HImode would need sll/sra at the test... The qty size would be 2 (HImode) → pri halves! Let's compute: iVar2 HImode with 8 refs/10 insns, size 2: 3*8*2/10 = 4.8 < 5.33 → iVar1 wins! 

But b1 (s16 iVar2) scored 8 with the copy merged. Hmm, because the copy `tmp = iVar2` merges? Let me check b1's lreg.

Actually b1's asm was identical to n1 (merged, `lh v0; beqz v0; bgez v0` — no copy). So the copy was merged by cse/alloc.

But if I combine s16 iVar2 with the (s16) cast copy (a1's trick), maybe the copy survives AND iVar2 is HImode with low priority.

Let me try: `s16 iVar2;` + `tmp = (s16)iVar2;`. Hmm, if iVar2 is already s16, `(s16)iVar2` is a no-op → merged. Instead `tmp = iVar2;` where tmp is s32 → sign-extend, cse... b1 tried that (merged).

Hmm, what if `s16 iVar2` + `tmp = (s32)iVar2`? Same as tmp = iVar2.

Let me try a different width for tmp: `s16 tmp;` + `tmp = iVar2;`? b3 (tmp s16, iVar2 s32) scored 8.

Let me test the combination: iVar2 s16 AND tmp s16. And iVar2 s16 + `tmp = (s16)iVar2;` etc.

Actually, let me think about why b1 merged. In b1, iVar2 is s16 and the copy `tmp = iVar2` (tmp s32) is a sign-extend. cse equates tmp with sign_extend(iVar2)... and replaces uses of iVar2 with tmp? Hmm.

Let me just try a batch of width combos:
d1: iVar2 s16, tmp s16
d2: iVar2 s16, tmp s32, copy `tmp = (s32)iVar2;`
d3: iVar2 u16, tmp s32
d4: iVar2 s16, tmp u16
d5: iVar2 s16 + copy `tmp = (s16)iVar2;`
d6: iVar2 s32, tmp s16, copy `tmp = (s16)iVar2;`

Let me generate from n1 (the merged baseline) with sed.
