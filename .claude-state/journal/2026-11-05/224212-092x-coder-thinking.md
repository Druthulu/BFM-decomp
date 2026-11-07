---
ts: 2026-11-06T05:42:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tkrGKkuDcNaPJumpXEji
---
Interesting! z1/z2 = 14 (REG-caller), same insn count. So the expression folded away (68 ins) but changed something. Score 14 — likely the same iVar1/iVar2 swap (14 = h1's score).

Hmm. So the reference boost didn't materialize (folded) but something else changed slightly.

Time 22:41:44. Started 22:24 → ~17.5 min. Let me do 2-3 more minutes.

Let me check z1's diff to see if the swap is still the issue.

Actually, let me think about *buying references* in plain C without extra instructions. The asm trick adds refs to a pseudo. Plain C: any expression that mentions the variable and is not folded. GCC's fold is quite good but not perfect. Some ideas:
- `iVar1 + 0` folds.
- `iVar1 * 1` folds.
- `iVar1 & -1` folds.
- `iVar1 | 0` folds.
- `iVar1 ? iVar1 : iVar1`? fold may simplify.
- `iVar1 == iVar1` → 1.
- `(iVar1, iVar1)` comma → same.
- Casting: `(void *)iVar1` → no extra ref in RTL (same reg).

Hmm, what about `(s32)iVar1 + (s32)iVar1 - (s32)iVar1`? fold: (2*iVar1 - iVar1) → iVar1? Maybe not.

Actually, the reference must survive to the RTL as a mention of the pseudo in an insn. An expression that's folded at the tree level never reaches the RTL.

What survives? A subexpression used in an instruction that's already there. For example, if the store's address computation involved iVar1 twice: `*(s16 *)(iVar1 + (iVar1 - iVar1) + 0x10)` — if not folded, emits extra arithmetic.

Hmm.

What about a *comparison* whose result is used in a branch that's already needed? No.

OK, what about the live-length dial: we need iVar1's live range shorter than iVar2's. Currently 18 vs 8-10.

Hmm, wait — actually, what if we make iVar2's live range LONGER by making its *definition* earlier and its *use* later in a way that's free? The definition is the sign-extend after the load. The load is right before.

What if the sign-extend is moved earlier (before the unk20 load)? Impossible (depends on iVar1).

What if the *copy* `tmp = iVar2` is moved to the end of the if body (after the arms)? Then iVar2's live range would extend to there — but tmp is used in the arms before.

Hmm.

What if the second test `if (iVar2 < 0)` is moved AFTER the copy... it is.

What if we add a THIRD use of iVar2 at the end of the if body, in a way that's free: e.g., `if (iVar2 < 0) {...}` is the second test; what if the arms end with `tmp = (s16)iVar2;`? no, that changes the value.

Hmm, what about using iVar2 in the *inner* if condition instead of tmp: `if (0 < tmp * 0x10000)` — no iVar2.

Let me try: replace the inner conditions with expressions that use iVar2 but are equivalent: `if (0 < (tmp * 0x10000) + (iVar2 & 0))`. The `iVar2 & 0` folds.

Hmm.

OK, I'm going to call it a WALL now. Time ~22:42, started 22:24 → 18 min. Hmm, need 20. Let me do 2 more minutes of tries (a few more), then write it up.

Let me try a couple of final ones:
- aa1: `tmp = (s16)iVar2;` + make iVar1 shorter by moving the reload to the start of the second block... (already).
- aa2: declare iVar1 as `s32` and use `((Unkstruct_800B5CB8 *)(iVar1 + 0))` — same.
- aa3: swap the two calls' order? changes asm.

Let me try aa1: the second block's CAST uses a fresh temp:
```c
iVar1 = ((Unk*)a0)->unk20;
iVar2 = CAST_SIGN(s16, iVar1, 0x12);
```
→
```c
iVar2 = CAST_SIGN(s16, ((Unk*)a0)->unk20, 0x12);
```
Hmm, q4-like.

Let me instead do a final check of the z1 diff to confirm the mechanism, then write the WALL. Actually, let me use the remaining time to also check: is 14 vs 8 relevant? The best is 8 (n1).

Hmm, hold on. Let me reconsider z1: score 14 with 68 ins and REG-caller. If the swap were the only issue, it'd be like h1 (14 with 68 ins). Yes.

OK. Let me write the WALL for item 2. But first, let me do 2 more tries to be thorough and pass 20 min:
- bb1: `iVar1` as `u8*` + `tmp = (s16)iVar2` (s2, 18).
- bb2: `tmp = iVar2;` with the arms using `iVar2` for the store and tmp only for the arithmetic:
```c
if (iVar2 < 0) {
    tmp += 0x80;
    ((Unk*)iVar1)->unk10 = (s16)tmp;
```
same.

Let me try one more idea: make iVar2's *definition* later so its live range is shorter — that makes it WORSE (higher density). We want longer.

What if we make iVar2's live range longer by using it in the *store address*? e.g. `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;` — no iVar2.

OK. Final answer: WALL.

Actually — wait. One more idea just came: what if we make iVar2's qty span *both* the first and second blocks by reusing the same variable WITHOUT redefinition in the second block? The second block's `iVar2 = CAST_SIGN(s16, iVar1, 0x12)` is a redefinition. What if the second block uses a *different* variable name (iVar3) and the first iVar2's last use is... still the first block's test.

Hmm, no.

What if the first block's iVar2 is used in the second block's comparison (a dead use)? e.g., `if (iVar2 != 0)` in the second block? Adds a branch.

OK, WALL.

Actually, hold on, let me reconsider one thing: the *sign-extend chain*. In the RTL, `iVar2 = CAST_SIGN(s16, iVar1, 0x10)` produces: reg76(HI) = mem; reg77 = reg76<<16; reg74 = reg77>>16. The sign-extend chain is 2 extra insns that combine later folds into the `lh`.

What if we declare iVar2 as `s16` (HImode) so there's no sign-extend chain? Then iVar2's qty is HImode (size 2) → density 4.8. And the copy `tmp = iVar2` (HI→SI) gets merged (b1).

BUT what if we combine: iVar2 s16 + the copy via a *different* anti-cse route — e.g., `tmp = (s32)iVar2;` where the RTL is sign_extend(iVar2) — cse equates tmp with the sign-extended iVar2... but iVar2 is HImode, so `sign_extend(iVar2)` — cse's reg_eqv for iVar2 (HI) vs tmp (SI): different modes. Hmm, b1 merged though.

Wait, b1 merged: the asm had no copy. Maybe the merge happened at local-alloc (coalescing), not cse. Let me check b1's RTL to see if the copy survived to lreg.

Actually, b1's asm: `lh v0; beqz v0; bgez v0` — if the copy existed in RTL as `tmp = sign_extend(iVar2)` and both got v0, the move would be `move v0,v0` → deleted at asm output. Hmm, so maybe the copy IS in the RTL but coalesced.

Then to prevent coalescing, we need iVar2 and tmp in different registers → the priority. iVar2 HImode (4.8) < iVar1 (5.33) → iVar1 wins $3; tmp (20) $2; iVar2 $4! That's the target! But if they coalesce (same reg), the move disappears.

Hmm, if iVar2 gets $4 and tmp $2, they can't coalesce (different regs) → the move survives! So b1 might work IF iVar2's density is low enough. But b1 merged, meaning iVar2 and tmp got the same register. Why? Because local-alloc coalesced them via copy preference *before* considering density? Or because iVar2's density was high.

Wait, b1: iVar2 s16. Let me check b1's lreg dump for the qtys. Let me dump b1.

Actually, let me reason: b1's asm shows `lh v0` and no copy. If iVar2 were in v0 and tmp also v0, the copy is coalesced. Local-alloc's `combine_regs` coalesces a copy `tmp = iVar2` by making tmp prefer iVar2's register — but only if it can. It would allocate iVar2 first (higher priority?) then tmp copies its reg.

Hmm, if tmp (density 20) is allocated first → $2. Then iVar2 (density 4.8) → the next free reg, but `combine_regs` gives it a copy preference for tmp's reg ($2) — if iVar2 is not live when tmp is... they overlap (iVar2 is used in the test after tmp is born). So iVar2 can't take $2 → $3 or $4.

Hmm, but b1 merged. Let me look at b1's lreg.

Let me dump b1 (I already have the TU? no). Let me do it quickly.
