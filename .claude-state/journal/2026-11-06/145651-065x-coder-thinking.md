---
ts: 2026-11-06T21:56:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_L0l9POGQrDFKPPDQSH5L
---
In w6's cse dump:
- insn 95: `(set (reg/v:SI 100) ...)` — the copy (iv2c = iVar2)
- insn 104: tmp:HI = subreg(iVar2)
- insn 106/107: sign extend into reg 100.

So the copy at 95 is still there, and the sign-extend overwrites 100 at 107. Combine then folds 104/106/107 to a copy and merges into the compare.

The `do { tmp = (s16)iVar2; iv2c = tmp; } while (0);` didn't split at all (no label kept).

Wait — but cse has the copy at 95 AND the sign-extend at 104-107. Why didn't cse propagate `iv2c` (100) in the compare? Because 100 is re-set at 107 (the sign extend) — the copy at 95 is dead!

So the RTL from w6: `iv2c = iVar2; ...; tmp = subreg(iVar2); sll; sra; iv2c = ...`. Combine folds the sign-extend chain to `iv2c = iVar2` and then merges.

So the s16 trick is useless here because the sign-extend folds.

The real problem: combine merges any copy adjacent (within 3) to its use.

Let me now check: in the *successful* cases (func_80182ED4, func_8018302C), the copy's use was in a different basic block. So combine couldn't merge.

For us: the use (compare) is in the same block as the copy. Damn.

Unless... we can get a block boundary between the copy and the compare that jump1 won't remove.

When does jump1 keep a label? When the label has more than one predecessor or is targeted by a branch. So if the compare block is the target of a branch from elsewhere, the label stays.

Idea: make the compare block the target of a branch that already exists! Look at the code: after the compare, there's `uVar5 = 0` then the store block. Hmm.

What about restructuring the if/else so that the *copy* is at the end of the else arm and the *compare* is in the join block, with the then arm jumping to the join label (which stays because it has 2 predecessors: fall-through from else + jump from then)? In that case the join label is a real label, and the copy in the else arm is in a different block from the compare → combine can't merge!

But then the then path doesn't execute the copy... unless the then arm also does the copy (extra insn).

Hmm, unless the then arm jumps to the copy... Let's design:

```
if (cond) {           // then arm
    iVar2 = 1;
    uVar5 = 0;
    goto JOIN;
} else {
    t = ...;
    iVar2 = t + 1;
    param_2 <<= 4;
}
iv2c = iVar2;
JOIN:
one = 1;
if (iv2c != one) uVar5 = 0;
```
Here the then arm jumps to JOIN (after the copy), so it doesn't execute the copy — wrong semantics for the then path (iv2c uninitialized). Unless in the then arm we also assign iv2c = 1.

```
if (cond) { iVar2 = 1; iv2c = 1; uVar5 = 0; goto JOIN; }
else { ...; iVar2 = t+1; param_2 <<= 4; }
iv2c = iVar2;
JOIN:
one = 1;
if (iv2c != one) uVar5 = 0;
```
The then arm: `li a0,1; li v1,1; move t3,zero; j JOIN` — 3 insns vs target 2. Extra.

Hmm.

What if the copy is at the end of the else arm AND in the then arm... same issue.

OK, think about *when* the compare block has a label: if the then arm's `j` targets the copy (the join), the label is AT the copy, and the compare follows in the same block.

Hmm, what if we make the then arm jump to a point *after* the copy but the copy is still executed by the then path? Impossible.

Alternatively: could the compare be in a *different* block than the copy by putting the copy in the block that ends with a conditional branch? E.g.:

```
iv2c = iVar2;
one = 1;
if (iv2c == one) goto SKIP;   // the branch
uVar5 = 0;
SKIP:
```
Here the copy and the compare are still in the same block.

Hmm, the copy's use IS the branch condition.

What if the copy is used in a *later* block instead? The target's compare is the branch.

OK — what about making the copy's source not iVar2 but something that combine can't substitute, e.g., a *memory* value? no.

Let me revisit: maybe combine isn't merging i1 into i3 directly; maybe there's a different sequence. In w6's RTL after cse:

```
95:  iv2c(100) = iVar2(77)
104: tmp(102):HI = subreg(iVar2)
106: 103 = 102 << 16
107: 100 = 103 >> 16 (sign extend)
122: v0 = 1
127: compare 100, v0
```

Combine first folds 104+106+107 → `100 = iVar2` (a copy), then combine merges 95? and the new copy... then the compare.

Now, what if the sign-extend chain is NOT foldable, e.g., because the source's range is unknown? Then we'd get sll/sra (2 insns) but the copy from the *s16 variable* to iv2c... hmm.

Honestly, maybe the answer is: this specific item (launder that must survive adjacent to its use) has no plain-C spelling, and it's a WALL. But wait — the notes say the item was banked PARTIAL:launder after < 30 tries; my job is to try to remove it. If I can't after 30 tries / 20 min, record a WALL.

But hold on. Let me reconsider: maybe there's another way to get `move v1,a0` — via a **tie** created by a real C construct. GCC creates tied operands for:
- function calls (argument passing) — no.
- asm — banned.
- `__builtin_apply`? no.

What about **multiple return values**? no.

What about the **fixed hard registers**: e.g., a value that must be in $2 (v0) for a call, copied from another register. There's no call at that point.

Hmm, but there IS the pinned `one` ($2). What if we assign `one = 1` and then compare... no.

What if iv2c is assigned *from* a variable pinned to a hard register? Like `iv2c = one;` — no, one = 1.

Hmm, what if we exploit the existing pin `nx` ($2)? The pins are `register int nx __asm__("$2")` and `iVar4 = nx;`. Hmm.

What if iv2c were pinned to $3 (v1)? That's a new pin — forbidden.

Let me reconsider the rules: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

So no new pin. Right.

Hmm, but wait: is the *existing* pin `one` ($2) usable as a lever to force the copy? E.g., if iv2c is assigned from a variable that must be in $2... 

What if we write the compare as `if (iv2c != one)` where `one` is assigned AFTER the copy, and iv2c is assigned from... no.

Let me think about `local_alloc` coalescing: it merges two quantities when the source dies at the copy (copy preference). If iVar2 does NOT die at the copy, no merge, and a `move` is emitted — IF the copy survives combine.

So: make iVar2 die... no wait, we need it NOT to die.

So the only blocker is combine. And combine is blocked by a block boundary or by the dest being live after i3.

**Dest live after i3** — let me test this empirically! I need iv2c used after the compare. What if I write the store of uVar5 differently... 

Hmm, what about this: the compare is `if (iv2c != one) uVar5 = 0;`. What if we instead write:

```
uVar5 = (iv2c != one) ? 0 : uVar5;
```
no.

What about using iv2c in the `r` computation (replacing iVar2) AND keeping iVar2 alive by ALSO using it in `r`? Like `r = (uint)((iVar2 | iv2c) << 3) | c6b;` — that's an extra or. No.

What if `uVar1 = p4s | (param_3 & 0xffff) | uVar5;` uses iVar2? no.

Hmm, hold on: what if the copy's dest is used later *in a branch that is the compare itself*... no.

Let me look at the target's register allocation again: the compare uses v1, and v1 is dead after the compare. So the target's copy is merged-adjacent and only survived because of the asm.

Let me consider: maybe there's a way to make combine's window miss by inserting a non-combinable insn that the target ALSO has. The target has `li v0,1` between. If instead the order were `move; beq` adjacent, combine would merge too.

What if I could make combine see i1=copy, i2=li, i3=beq but *reject* because `i2` (li) modifies something? E.g., if `one = 1` were written so that its insn also sets/clobbers iVar2? no.

What if the copy's source is `one`? no.

OK — different idea: **make the compare use the value through a memory operand or a different form**... 

Let me look at whether there's any C construct producing an insn between the copy and the compare that the target also has. The target has: move(27), li(28), beq(29). No.

Alright, let me consider the possibility that the move can be produced by **local_alloc's copy preference with a HImode variable**, where the copy is a HImode move that combine can't merge because the modes differ. E.g., iv2c is `s16`, iVar2 is int. `iv2c = iVar2` → `(set (reg:HI 102) (subreg:HI (reg 77) 0))` — a HImode copy. The compare `if (iv2c != one)`: iv2c promotes to int → sign_extend(102) vs one.

Combine: i1 = HImode copy, i3 = compare using sign_extend(102). Substituting 102 with subreg(iVar2) gives sign_extend(subreg(iVar2)) — foldable (known range) → merges.

If not foldable, we'd get sll/sra — 2 insns.

Hmm. What if the compare is done in HImode? `if (iv2c != (s16)one)`? Then the compare is between two HImode regs; the pinned `one` is int ($2)...

Hmm.

Let me step back and consider the time budget: 20-30 min per item. I've spent ~20 min on this item. I have 3 items total; items 1-2 are done (5 min). So I have budget.

Let me try a couple more promising things:

(A) Make iv2c used after the compare (to block combine), even at the cost of changing the later code — then see what score comes out. If it's e.g. 2, maybe a further move fixes it.

Concretely: `r = (uint)(iv2c << 3) | c6b;` instead of iVar2. iVar2 would then be dead after the copy → coalescing risk, but let's see.

(B) Move the `one = 1` assignment *before* the copy, so combine's i1=li, i2=copy, i3=beq: then can_combine_p(i1=li) and i2=copy... combine would merge the copy into the beq (i2 into i3). Same.

(C) Try putting the copy in the *then* and *else* arms with `iv2c = iVar2` in both and see the count (maybe 56?).

Let me do (A) and (C) and score.

For (C):
```
if ((short)iVar4 == six) { iVar2 = 1; iv2c = iVar2; uVar5 = 0; }
else { t = ...; iVar2 = t + 1; param_2 <<= 4; iv2c = iVar2; }
one = 1;
if (iv2c != one) uVar5 = 0;
```
Hmm, in the else arm the copy is last; then the join. In the then arm the copy is followed by uVar5=0.

Let me write these variants. I need to restructure lines. Let me write a python script that takes prev_win.c and produces variants by replacing the block:

Current block (lines 38-44 of prev_win):
```
            {
                int iv2c;
                register int one __asm__("$2");  // ...
                iv2c = iVar2;
                __asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c));  // !FAKE: launder ...
                one = 1;
                if (iv2c != one) uVar5 = 0;
            }
```
Let me view prev_win around there to get exact text.
