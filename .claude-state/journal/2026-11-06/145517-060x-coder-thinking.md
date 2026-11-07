---
ts: 2026-11-06T21:55:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BeIeLJZpt3lavyL4cjQ0
---
Note `i1_feeds_i3 = i1 && ! reg_overlap_mentioned_p (i1dest, i2src)`. Our i2 is `one = 1` (li v0) whose src is const 1 → doesn't mention iv2c → i1_feeds_i3 = TRUE (meaning i1 and i2 independently feed i3). Then added_sets_1 = ! dead_or_set_p(i3, i1dest). If iv2c is not dead at i3 (used later), added_sets_1 = true → the set must be kept, so combine would produce i3 using iVar2 plus a re-added copy — no gain. Combine would reject (it checks `added_sets_1 && added_sets_2 && ...` cost).

So: making iv2c used after i3 blocks the merge. But then the copy must survive local-alloc coalescing: iVar2 must not die at the copy.

So we need: iv2c used after the compare, AND iVar2 still used after. Both holding the same value. Where can iv2c get a second use for free?

Look at the code after: 
```
uVar1 = p4s | (param_3 & 0xffff) | uVar5;      (in each arm)
do { puVar3[-1] = uVar1; } while (0);
r = (uint)(iVar2 << 3) | c6b;
*puVar3 = r;
```
iVar2 is used in `r`. If iv2c is used there instead, iVar2 dies at the copy. Unless iVar2 is used elsewhere too.

What if we keep `r = (iVar2 << 3) | c6b` and ALSO use iv2c somewhere free... there's nowhere.

Alternatively: make the copy `iv2c = iVar2` where the compare uses iVar2 (not iv2c)! Then the copy's dest is dead (unused) → flow deletes it. No.

Hmm. What about making iVar2 not die but iv2c used later... 

Wait, actually maybe I have this backwards. Let me reconsider: what if we introduce a *second variable* that is compared and also used later, while iVar2 remains the source?

Actually — the real question: what does the target do later with iv2c? Nothing. The target's move is reload-generated from the tie.

Let me try yet another approach: since the move is reload-generated, maybe I can force a reload-generated move with plain C via a **register conflict**: if the compare's operand register is already occupied... no, that's the allocator's choice, and there's no copy insn at all.

Alternatively — maybe I can find a different way to make 56 instructions that matches. But the target is fixed; no.

Let me reconsider the problem from the "which pass" angle once more, but empirically: test a body where iv2c is used after the compare (using it in `r`), and iVar2 is also kept alive by some other use... 

Idea: use iv2c in `r = (uint)(iv2c << 3) | c6b;` AND keep iVar2 alive by using it in the earlier `uVar1` line? uVar1 = p4s | (param_3 & 0xffff) | uVar5 — adding iVar2 there would change the value. No.

Hmm, what about using iv2c in place of iVar2 in the `r` computation and keeping iVar2 alive via the `else` arm's `param_2 << 4`? No.

OK, radical: maybe the copy doesn't have to be `iv2c = iVar2`. What if the move is between two other variables that happen to have the same value? E.g., the target's `move v1,a0`: v1 gets a0's value. If we could get a *real* copy elsewhere that combines to the same instruction... The instruction is at a specific position.

Let me try the HImode variable (u16/s16 iv2c) experiments — cheap, and maybe combine's zero_extend folding produces something interesting. Also try the "used later" variants to see the behavior.

Let me create:
w4: `s16 iv2c;` function-scope, `iv2c = iVar2;`, compare `if (iv2c != one) uVar5 = 0;`
w5: `u16 iv2c;`
w6: `iv2c = iVar2; one = 1; if (iv2c != one) uVar5 = 0;` but with the copy moved before the `if` join... 

Let me do w4 and w5 first.

Actually, wait. Let me reconsider something: the `do { } while (0)` empty statement trick — how does it work for the barrier cases? It creates a block boundary that jump1 keeps? In C0535 it split the cse1 EBB. If it creates a CODE_LABEL that jump1 doesn't remove, combine would also be blocked! In w1 I put `do { iv2c = iVar2; } while (0);` — the copy inside the do-while. The block boundary is after the copy (between the copy and `one = 1`). jump1 removed it (jump to next insn deleted + blocks merged). But if the boundary were kept, combine would be blocked.

Hmm, in the barrier cases, the do-while splits the EBB — meaning jump1 does NOT always merge. When does jump1 not merge? When the label is a jump target from elsewhere, or when the jump-to-next is not deleted (e.g., when the block has other predecessors).

So: if the do-while's end label is also a jump target from another block, the label stays. In our case, could we arrange for a branch to target the end of a do-while? That's a `goto` into... hmm.

Actually the simplest: what if the copy is inside a block that is jumped into from elsewhere, i.e., a label? A `goto L; ... L:` where the goto comes from an earlier conditional.

For example, restructure the if/else to jump to the copy:

```
if ((short)iVar4 == six) {
    iVar2 = 1; uVar5 = 0;
    goto JOIN;
} else {
    t = ...; iVar2 = t + 1; param_2 <<= 4;
}
JOIN:
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
```
That's the same as the natural code (the join label is there anyway). Combine operates on the join block; the copy is at the block start. Combine still merges within the block.

The label must be BETWEEN the copy and the compare.

What if:
```
JOIN:
one = 1;
iv2c = iVar2;
if (iv2c != one) ...
```
same block.

Hmm.

What if the compare is in a block that is a jump target:
```
iv2c = iVar2;
if (0) goto CMP;   // deleted
CMP:
one = 1;
if (iv2c != one) uVar5 = 0;
```
The `if (0) goto` is deleted at tree level.

What about `if (uVar5) goto CMP;`? uVar5 is 0 in the then arm... not provable in general. That adds a branch.

Hmm.

Let me reconsider the sign-extend route with a value whose sign bit is unknown at combine time. What if the value is stored in a *HImode variable assigned in the else arm* and combine can't see across? e.g.:

```
if (...) { iVar2 = 1; uVar5 = 0; }
else { t = ...; iVar2 = t + 1; param_2 <<= 4; }
iv2c = (s16)iVar2;
```
The sign-extend source is iVar2, whose last set is in the else block (andi). Combine at the join computes nonzero_bits for iVar2 — in combine, `reg_last_set` is recorded as it walks the function (`record_dead_and_set_regs`), so at the join insn, reg_last_set[iVar2] = the addiu insn in the else block. And `subst`/`simplify_rtx` would use `reg_nonzero_bits`... Actually, `nonzero_bits` in combine uses the insn's REG_EQUAL notes and reg_last_set only via `reg_last_set_value`? There's a mechanism `record_value_for_reg` that tracks known values across blocks (used for REG_EQUAL). Hmm, combine's `subst` calls `simplify_rtx` which uses `nonzero_bits (x, mode)` from rtlanal, which for a REG uses `REG_NONZERO_BITS`... hmm, in 2.7.2 `nonzero_bits` for a register returns `reg_nonzero_bits[REGNO]` if known — a global array updated by combine's record_value_for_reg.

This is getting deep. Empirically, w2's sign extend got folded. So combine knew.

New idea: **hide the range by making the value come from a memory load in the else arm**. Not possible without changing the code.

New idea: **use a float/double conversion**? no.

Let me try a totally different C shape that might naturally produce a move: what if the compare is done on a *pointer*? no.

Hmm, let me look at other cracked items with a similar "move vX,vY before compare" pattern and see what real-C moves were used. Let me grep moves.md for "tie" or "copy" in MATCH lines.
