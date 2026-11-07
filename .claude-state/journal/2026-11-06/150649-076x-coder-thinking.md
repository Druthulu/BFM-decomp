---
ts: 2026-11-06T22:06:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Wcbs6YzvAZw2QMAl0FAE
---
Confirmed: after cse1, the compare uses reg 77 (iVar2) — cse propagated the copy. So cse is the pass to defeat.

cse's copy propagation: it recorded `iv2c == iVar2` (make_regs_eqv) and replaced the use.

How does cse's make_regs_eqv work? Line 826. Let me look at when cse creates the equivalence: in cse_insn, for `(set (reg) (reg))`, it calls make_regs_eqv(dest, src)? Let me check.

If so, then to prevent it: the copy must not be a plain `(set (reg) (reg))` in cse's view, OR the use must be in a different EBB.

cse's EBB: cse_main processes basic blocks. Does cse propagate across blocks? The copy is in the join block (after code_label 90) and the compare is in the same block. Same block → propagated.

So: different block. The label 90 is the join; the compare is right after. If there were a label between the copy and the compare...

What if the copy is at the END of the *else* arm (in the else block, before the join label) and the compare is in the join block? Then the copy is executed only on the else path — but the then path also needs iv2c.

WAIT. Unless the then path's iv2c value doesn't matter! Let me re-read the target: the then path jumps to the copy (insn 27). So the copy executes on both paths in the target.

Hmm, what if we split the copy into both arms but make the then arm's copy free? The then arm's copy is `iv2c = 1` (li v1,1) — extra.

Hmm, what if the then arm's iv2c assignment is `iv2c = iVar2` where iVar2 = 1 was set by `li a0,1` — and combine folds `move v1,a0` into `li v1,1`. Extra insn either way.

Hmm. What if the then arm's value for iv2c comes from the `one` variable? no.

Let me think about the target's then path once more: `li a0,1` then `j 63c4` where 63c4 = the move. So the then path executes `move v1,a0` after `li a0,1`.

If the source had the copy in each arm, the then arm would be `li a0,1; move v1,a0` = 2 insns — the same as the target's then arm (1) + join (1) = 2! Wait:

Target then path: `li a0,1` (21), `j` (22), delay `move t3,zero` (23), then at the join `move v1,a0` (27). So the then path executes li a0,1 → move v1,a0 (at 27). Total 2 value insns.

If the copy were in the then arm: `li a0,1; move v1,a0; j; move t3,zero` = 3 insns in the arm + no join move. Total 3. The difference: the join move is shared in the target but duplicated in the arm version.

Right, so 57.

Hmm, unless the then arm's copy could go into the jump's delay slot and `move t3,zero` elsewhere... still 3.

OK. What about making the then arm NOT need the copy because iv2c is already 1 from a *previous* iteration? No.

Let me try a different tactic: what if the copy is placed BEFORE the join label but executed on both paths by restructuring the branch so both arms fall through to it? E.g.:

```
if (cond) {
    iVar2 = 1; uVar5 = 0;
} else {
    ...
}
```
The then arm jumps over the else arm to the join. The copy at the join is after the label.

What if we invert: make the then arm the fall-through and the else arm jump?

```
if (!(cond)) {
    ...else...
    goto JOIN;
}
iVar2 = 1; uVar5 = 0;
JOIN:
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
```
Still, the copy is after the label.

The copy is executed by both paths → it must be after the join label. Any insn after the join label is in the join block with the compare.

UNLESS the compare is in a *different* block. To make the compare a separate block, we need a branch between. But the copy itself doesn't branch.

Hmm, hold on: what if the compare is at the top of a *loop* or inside an if-body that's a separate block? E.g.:

```
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
```
What if written as:
```
iv2c = iVar2;
one = 1;
if (iv2c == one) goto DONE;
uVar5 = 0;
DONE: ;
```
The compare is still in the same block as the copy.

What if:
```
iv2c = iVar2;
one = 1;
switch (iv2c != one) { case 0: break; default: uVar5 = 0; }
```
Hmm, a switch might create a jump table — extra.

What about `if (iv2c != one) { ... } else { }` — same.

OK: the compare's block is the same as the copy's, always.

THEREFORE: the only way is to make the copy's RTL not a plain reg-reg copy (so cse doesn't equate), and then have combine fold it into a move without merging.

The sign-extend approach does exactly that at cse time — and in w2, cse did NOT propagate (the compare used reg 100). The failure was combine folding the sign-extend AND merging into the compare.

So: can I make the sign-extend fold into a move but NOT merge into the compare? Combine merges i1(copy) + i2(li) + i3(compare) if adjacent. What if the sign-extend's fold happens at a point where combine then can't merge because the resulting copy is not adjacent?

In w2 the RTL after cse:
```
95:  iv2c(100) = iVar2(77)
104: tmp(102):HI = subreg(iVar2)
106: 103 = 102 << 16
107: 100 = 103 >> 16
122: v0 = 1
127: compare 100, v0
```
Combine first combines 104+106+107 into `100 = iVar2` (a copy). Then combine processes... the insns are now 95 (dead copy), the new copy, 122 (li), 127 (compare). The new copy is 3 insns before the compare (with the li in between) → combine merges it. 

What if there were 2 insns between the folded copy and the compare? Then combine's window (i1,i2,i3 = 3 insns) — the copy would be i1, and i3 = compare needs i2 = the insn right before. With 2 insns between, the copy is too far.

So: add an insn between the copy and the compare that the target ALSO has... The target has `li v0,1` only.

Hmm. What if `one = 1` is moved BEFORE the copy? Then the order is: li v0,1; copy; compare — the copy is adjacent to the compare (1 insn). Combine merges.

What if we have TWO statements between: e.g., `one = 1; six = 6;`? six is a pinned variable already assigned earlier in the block... adding a second `six = 6;` would be an extra insn (li v0,6) — but maybe it's a no-op because six is already 6? No, it'd be an insn.

Hmm, what if we reuse an existing assignment that's already between? There isn't one.

OK. What if the sign-extend chain itself is longer so that after folding, the copy is further from the compare? No — folding collapses it.

What if the sign-extend chain is NOT folded by combine (because the range is unknown) and stays as 2 insns? Then the compare uses iv2c and the total is 57. Unless one of the two insns replaces the copy... In w2, we had BOTH the copy (95) and the sign-extend (104-107). If the sign-extend didn't fold, the copy at 95 would be dead (iv2c overwritten at 107) → deleted by flow → total: 2 insns (sll+sra) instead of the target's 1 move. 57 insns.

Unless we write ONLY `iv2c = (s16)iVar2` (w3): the RTL would be just the sign-extend (2 insns if unfolded) = 57.

Hmm, 57 ≠ 56.

Unless the sign-extend folds to ONE insn (a move) but combine can't merge it into the compare because the fold happens late (in combine's own processing, after the merge attempts?). In w2 it merged.

OK, what if the value is a HImode *variable* that's stored/loaded... no.

Let me try the "two insns between" idea with a real second use: what if we write
```
iv2c = iVar2;
one = 1;
six = 6;          // extra li v0,6 — costs 1 insn
if (iv2c != one) uVar5 = 0;
```
57. No.

I'm now confident: WALL.

Actually, hold on, hold on. One more idea: what if the *compare* is not in the same EBB because the copy is at the end of a block that ends with a *conditional branch*, and the compare is in the successor? For instance:

```
iv2c = iVar2;
one = 1;
if (iv2c != one) goto ZERO;   // the compare
...
```
The copy is right before the compare. Same block.

What if the compare is at the START of a block reached by a jump from the copy's block? That requires a jump.

Hmm, what if we exploit the LOOP: the compare is inside the loop body; the loop body starts at label X (jump target of the back edge). The copy is in the middle.

No.

OK, final: WALL. But wait — maybe I should reconsider the "existing pin reuse" idea after all, since it might be considered legitimate... No. The task explicitly says no new lever of any kind; reusing a pin to steer a register is a lever. I'll not do it.

Hmm, but hmm. Let me reconsider: is there any chance the intended solution is the `c3`/`c74` reuse? The task says "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". "pointer reuse" and "variable reuse" are listed! E.g., W02's "reuse m for next ptr". Reusing an existing variable (even a pinned one) for another purpose is a listed real-C move... 

Hmm, "pointer reuse" means reusing a pointer variable, not a pinned register variable. Reusing `c3` (a uint pinned to $3) as iv2c would be steering via the pin.

But here's the thing: the variable c3 IS already pinned and its pin exists "under another cause" (the store constant). If I reuse c3 for the compare, the pin's $3 constraint does the steering — that's a new lever use.

I'll not do it. The WALL is honest.

Hmm, but wait. What about using a NON-pinned variable that happens to be allocated to v1 naturally? That's what we want; the allocator gives iv2c v0 because v0 is free (since iv2c dies at the compare after the propagation). If iv2c were live after, it couldn't take v0 (one's reg)... but then the compare's operand is rewritten anyway.

Hmm, hold on! What if iv2c is live after the compare AND cse's propagation is blocked by the sign-extend trick? Let's think:
```
{ s16 t2; t2 = (s16)iVar2; iv2c = t2; }   // iv2c = sign_extend -> cse can't equate
one = 1;
if (iv2c != one) uVar5 = 0;
...
r = (uint)(iv2c << 3) | c6b;   // iv2c live after
```
But iVar2 would be dead after the copy (only used in the sll, which we changed) → coalescing... no wait, the copy is `iv2c = t2` where t2 = sign_extend(iVar2). iVar2 dies at the sign-extend → local-alloc might coalesce iVar2 with t2? They're different modes (SI vs HI) — coalescing across modes? local_alloc can coalesce only same-mode qtys I think.

Hmm, and then iv2c (SI) = t2 (HI, sign-extended). The sign-extend folds at combine into a copy → iVar2 (a0) → iv2c. If iv2c is live after the compare, combine keeps the copy but still rewrites the compare... 

ARGH, the compare rewrite happens because cse/combine know iv2c == iVar2.

But WAIT: in w2, cse did NOT rewrite the compare (it used reg 100). Then combine folded the sign-extend and merged. If iv2c were live after the compare, combine would keep the copy — but would it still rewrite the compare to iVar2? Yes, combine substitutes into i3.

Hmm, unless combine can't substitute because after folding, the copy is... 

Let me just test it: w20 = s16 temp + iv2c used later in r.

```
                {
                    int iv2c;  (function scope)
                    ...
                }
                {
                    s16 t2;
                    t2 = (s16)iVar2;
                    iv2c = t2;
                }
                one = 1;
                if (iv2c != one) uVar5 = 0;
...
r = (uint)(iv2c << 3) | c6b;
```
Let me test this. If the compare keeps iv2c (v1) and the copy `move v1,a0` appears... but wait, with iVar2 dead at the copy, local-alloc might coalesce. Let's see.

Actually, since iVar2 is dead after the copy, and iv2c is live long, the copy `iv2c = iVar2` would be coalesced (copy preference) if they don't conflict. They conflict? iVar2 dies at the copy → coalescing possible → the copy disappears.

Hmm, but then we'd have iv2c = the sign-extend of iVar2 in the same register — no move.

Ugh.

Let me test anyway — cheap. And also test keeping iVar2 alive by using it in the r line too... 

Hmm, actually: what if `r = (uint)(iVar2 << 3) | c6b;` stays (iVar2 used later) AND iv2c is used later somewhere free... there's no free use.

OK, one test: the s16-temp copy with iv2c used later in r. Let me do it, plus a couple more, then finalize.

Actually, let me think about the time: 15:06. Item started 14:43 = 23 min. The budget says 20-30 min. I've done 30+ tries. Recording a WALL is justified. But let me do this one last test since it's the most promising variant (it combines the sign-extend cse block with the live-after combine block).

Let me construct it:
- base = prev_win
- move `int iv2c;` to function scope (after `int cont;`)
- replace the launder line with: `{ s16 t2; t2 = (s16)iVar2; iv2c = t2; }`
- change `r = (uint)(iVar2 << 3) | c6b;` to `r = (uint)(iv2c << 3) | c6b;`

Test.
