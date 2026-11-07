---
ts: 2026-11-06T05:41:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6vHA48ZsKgG95ISJ2Kt0
---
This confirms the density mechanism. But the lever used there is a zero-byte asm — which is a lever (asm). We can't use asm.

But the law: "reference count is a dial, live length is a dial". We need iVar1's density > iVar2's. Reference count via zero-byte asm is forbidden. Live length is a dial via placement.

We need iVar1 (8 refs) to beat iVar2 (8 refs). Since refs are equal, live length must be shorter: iVar1's live < iVar2's live. iVar1 live 18, iVar2 live 8-10. Can't.

Hmm, unless we can shorten iVar1's live range. iVar1 is live across the arms.

Actually, wait — what if we make iVar1's *first* live range end at the CAST_SIGN and have a separate variable for the arms? But the arms need the pointer. What if the arms use a *second* load of unk20 that gcc CSEs... the store in the then-arm would invalidate the memory, forcing a reload in the else arm. Hmm.

Actually, hold on: the arms are mutually exclusive. If the source is:
```c
if (iVar2 < 0) {
    ((Unk*)iVar1)->unk10 = (s16)tmp;
    ...
} else {
    ((Unk*)((Unk*)a0)->unk20)->unk10 = (s16)tmp;   // reload
    ...
}
```
Then in the else arm there'd be an `lw` (extra instruction) — target doesn't have it.

So iVar1 must span.

Alternatively, we can make iVar2's live range LONGER (lower density). iVar2's live range is 8-10. If we extend it to 18+, its density drops below iVar1's. How to extend without extra instructions?

The live range is from the def (sign-extend) to the last use (second test). The second test is right after the copy. What if we move the second test LATER? The second test guards the arms; it must come before them.

What if the copy `tmp = iVar2` is moved to after the second test? It must be before the arms use tmp.

Hmm, what if the second test is moved into the arms? Like:
```c
if (iVar2 != 0) {
    tmp = iVar2;
    if (iVar2 < 0) {
```
No.

What if we add a *third* test of iVar2 at the end of the if body (dead but not eliminable)? For example, `if (iVar2 == 0x7FFF) ...` — adds a branch.

Hmm. What about a *use* of iVar2 in the arms that folds into an existing instruction? E.g., the store `((Unk*)iVar1)->unk10 = (s16)tmp;` — the cast `(s16)tmp` is a subreg. Could we write `(s16)(tmp | (iVar2 & 0xFFFF0000 & 0))`? folds.

What about `(s16)(tmp + iVar2 - iVar2)`? gcc's fold might not cancel because of overflow? In C, signed overflow is UB but gcc 2.7.2 may not exploit it. fold-const's `associate_trees`/`fold` does handle `(x + c1) + c2` but `x - x` → 0? Let me check: fold-const has `if (code == MINUS_EXPR && operand_equal_p (arg0, arg1, 0)) return integer_zero_node;`. Yes, `tmp + iVar2 - iVar2` — the tree is ((tmp + iVar2) - iVar2). fold would simplify? `(a + b) - b` → a? fold-const does handle `(a + b) - b = a` via `associate_trees`? There's code for PLUS/MINUS reassociation in fold(). Might simplify to tmp. If not simplified, it would emit an extra addiu/subu.

Hmm, risky but let me try: `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)(tmp + iVar2 - iVar2);` — if it doesn't fold, +2 instructions.

What about a use of iVar2 in the *inner condition*: `if (tmp * 0x10000 < 0)` → `if ((tmp + iVar2 - iVar2) * 0x10000 < 0)`. Same issue.

Alternatively, use a *shift by zero*: `tmp >> (iVar2 - iVar2)`? If not folded, a variable shift. Ugly.

Hmm. Actually, what about making iVar2's live range longer by using it in the SECOND block's computation in a foldable way? The second block reassigns iVar2.

OK, what about the live-length dial in the other direction: make iVar1's live range SHORTER by moving its *birth* later. iVar1 is born at the unk20 load (insn 21), needed by the CAST_SIGN (insn 24). If the load happened at 23 instead of 21... the source order is: `iVar1 = unk20; iVar2 = CAST_SIGN(s16, iVar1, 0x10);`. The load must precede.

What if we write `iVar2 = CAST_SIGN(s16, ((Unk*)a0)->unk20, 0x10);` and `iVar1 = ((Unk*)a0)->unk20;` AFTER (q4, 17). q4 gave 69 ins (extra). Hmm.

What if iVar1 is born later but still used in the arms:
```c
iVar2 = CAST_SIGN(s16, ((Unk*)a0)->unk20, 0x10);
iVar1 = ((Unk*)a0)->unk20;
```
gcc CSEs the two loads into one (born early). 69 ins in q4 — hmm, why 69? Maybe gcc didn't CSE and emitted 2 loads.

OK. I think the density contest is unwinnable here without an asm reference booster (forbidden).

Actually, WAIT. What about *buying references* without asm? C0467 says "Reference count is a dial (zero-byte asm inputs)". But there might be plain-C ways to add references that don't add instructions: e.g., using a variable in an expression that folds. Hmm, folding removes the reference.

What about a *dead but kept* reference? For example, a comparison result used in a way that's optimized away... 

Hmm, what about `iVar1 = iVar1;`? cse deletes it.

What about making the *arms* use iVar1 twice in one instruction? E.g., `((Unk*)iVar1)->unk10 = (s16)(tmp + (s32)iVar1 - (s32)iVar1);` — if fold doesn't cancel, +2 insns.

Hmm. Let me try `tmp + iVar2 - iVar2` and see if it folds (score tells).

Actually, there's a classic: `x | 0` folds. `x + 0` folds. But `(x + y) - y` may not fold in 2.7.2.

Let me test: add `(s16)(tmp + iVar2 - iVar2)` in the store of the then-arm only? That would extend iVar2's live range to the then-arm's store (~+4 insns). Hmm, and if it folds, no change.

Let me test both arms.

Actually, a cleaner idea: `(s16)(tmp ^ (iVar2 & 0))`? folds.

Let me try the `+iVar2 -iVar2` form.

Also: what about `iVar2 * 1`? folds.

Let me run one test.
