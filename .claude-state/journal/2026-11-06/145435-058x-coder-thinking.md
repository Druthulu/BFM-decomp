---
ts: 2026-11-06T21:54:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8NOMVRHk8tGSZNx2M6ax
---
In the matching body (q1), the RTL is:

```
(insn 97 (set (reg 100) (asm_operands "" "=r" [ (reg 77) ] [ ("0") ])))   ; the launder itself
(insn 100 (set (reg 2 v0) (const_int 1)))
(jump_insn 103 (if_then_else (eq (reg 100) (reg 2 v0)) ...))
```

And reg 100 is the asm output. The `move v1,a0` in the asm is the *tied input operand copy*: the asm has an input operand `(reg 77)` with constraint "0" (tied to output), so the allocator must put the input in the same register as the output → it emits `move v1,a0` (copy reg 77 → reg 100's register). Wait, but the RTL shows the input as `(reg 77)` and output reg 100 — the tie means they must be in the same register. If reg 77 is in a0 and reg 100 in v1, that's a contradiction... unless reload inserts a copy.

Hmm, actually with "0" constraint, GCC's expand_asm_operands creates the output as a new pseudo (100) and the input as the tied pseudo (77) with matching constraint; the register allocator assigns them the same register? No — reload inserts a move if they're in different registers.

The `move v1,a0` comes from reload/regalloc realizing the tie.

Interesting: in the matching RTL, there's NO explicit `iv2c = iVar2` copy insn — the earlier `(insn 95 ...)` was deleted (NOTE_INSN_DELETED at 95). The asm's input is reg 77 (iVar2) directly.

So the target's `move v1,a0` is created by *reload* satisfying the "0" constraint: the input value in a0 must be moved to v1 where the output pseudo lives.

So to reproduce: we need a construct that creates a *tied* operand pair with the value in one register and a new pseudo in another. In plain C, that's a copy that the allocator can't coalesce.

Hmm! What about a function call with the value as an argument? no.

What about `iv2c` being the destination of a copy that must live in a specific register... no.

What if we use the *address* of a variable? no.

OK, alternative: make the allocator unable to coalesce the copy. Coalescing (local_alloc) merges quantities when the source dies at the copy. If iVar2 does NOT die at the copy, they conflict and a move is emitted — but combine removes the copy first.

So we need combine to not merge. Combine merges because the copy's dest dies at the compare and the insns are adjacent.

What if the copy's destination is used in the compare AND the copy is separated from the compare by a CODE_LABEL? Combine can't cross labels. In the target RTL above, the asm is between.

So: can I get a CODE_LABEL between `iv2c = iVar2` and `if (iv2c != one)` with no runtime cost? 

A code label is emitted for a jump target. If some branch targets a point between the two statements, we'd need a branch that jumps there. But maybe an *unreachable* branch that flow doesn't delete? e.g., `if (0) goto L;` is folded.

Hmm, what about `switch` on a variable with only one case? That emits a jump table...

What about the loop: `do { ... } while (0)` — the body's end is a label (loop end), and the compare after is a new block! Wait: `do { iv2c = iVar2; } while (0); one = 1; if (iv2c != one)`. jump1 deletes the jump-to-next and merges blocks (removing the label). That's why w1 didn't work.

Unless the loop body contains a branch that makes jump1 keep the label. Hmm.

What about a `while` loop that always exits: `while (0) {...}` — folded.

What about a backward goto?

Hmm, what if the label is the target of a *later* branch, e.g.:

```
iv2c = iVar2;
if (iv2c != one) goto SKIP;   // hmm
```

Let me think about the target's actual code: the compare is `beq v1,v0,63d8` — a forward branch to skip `move t3,zero`. Standard.

What if I restructure the tail as:

```
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
```
→
```
iv2c = iVar2;
one = 1;
if (iv2c == one) goto L;
uVar5 = 0;
L:;
```
Same code, but now there's a label L after the if — doesn't help.

What about:
```
iv2c = iVar2;
L:
one = 1;
if (iv2c != one) uVar5 = 0;
```
with `goto L` from somewhere before? A goto that's the only path... jump1 threads it.

Hmm, what about placing the label so that it's a jump target from the THEN arm? That's the join label itself, which is BEFORE the copy (at 27 = the copy insn's address; the label is at the copy).

Hmm, wait! What if we put the copy at the join label and the compare in a separate block by making the join label *between* them? Like:

then arm: `iVar2 = 1; uVar5 = 0; goto JOIN;`
else arm: `iVar2 = t+1; param_2 <<= 4;`
JOIN: `iv2c = iVar2;`  ← label here
...

The label is before the copy. For the label to be between the copy and the compare, the copy must be before the label and executed by both paths — impossible unless duplicated.

OK, what about a completely different mechanism to get a move: **make the copy needed because the source and destination must differ due to a hard-register constraint from an existing pin**. The existing pins: `one` ($2). Hmm, what if we assign `iv2c` from `one`? no.

What if we use the pinned `one` variable as the copy source: `one = 1; ...` no.

New idea: **make iVar2 and iv2c different MODES that reload must handle**. E.g., iv2c is a `float`? no.

Let me look at the problem from the score side: mine is 55 ins vs target 56, with `beq a0,v0` vs `move v1,a0; beq v1,v0`. If I can't create the move, could I instead get 56 ins some other way? No — the target is fixed.

Let me look for other bodies in this project that cracked a similar "copy before compare" with plain C. Search moves.md for "move v1" or similar. Let me grep for MATCH entries mentioning "copy" and "compare".

Actually, a thought: what if the copy is `iv2c = iVar2` where iVar2 is *not* used after? Then the allocator coalesces... 

What if we make the copy's destination a variable that is live ACROSS the compare? E.g., use iv2c after the compare in a way that costs nothing... The code after: `uVar1 = p4s | (param_3 & 0xffff) | uVar5;` then the store, then `r = (iVar2 << 3) | c6b`.

What if we write `r = (uint)(iv2c << 3) | c6b;` — using iv2c instead of iVar2 (same value!). Then:
- iv2c is used at the compare AND later at r.
- combine's can_combine_p for i1 (copy) into i3 (compare): the check "Make sure that DEST is not used after SUCC but before I3" — no. But there's another check in try_combine: if the destination of i1 is used after i3, combine can still combine but must keep the copy? Let me check: combine has `i1dest` and `undobuf`... In try_combine, there's:

```
  /* If I1 feeds into I2 and I1DEST is not used in I3, we can't ... */
```

Let me actually read the part of try_combine that decides whether the combination is valid when i1's dest is used elsewhere. Search for "i1dest" usage.

Actually — maybe simpler: if iv2c is used later, cse might still propagate it (cse does copy propagation? we saw in w2 the copy at insn 95 SURVIVED cse!). Indeed: in w2's cse dump, insn 95 `(set (reg/v:SI 100) (reg/v:SI 77))` survived cse, and the compare used reg 100. So cse did NOT propagate the copy. It was combine that merged it (the compare at insn 108 used reg 100; after combine, reg 100 was gone).

So if iv2c is used later (after the compare), combine cannot delete the copy — it would have to keep it, so it won't combine (not profitable / invalid). Let me check combine's rule.

In try_combine, there's a variable `i1dest` and code:

```
  /* If I1 or I2 is a register copy and the destination is used later, ... */
```

Let me grep for "dead" around i1 in try_combine.

Let me read the relevant section of try_combine: after can_combine_p calls, it computes `i1dest`, `i1src`, then:

```
  /* If I1 contains any REG_UNUSED notes ... */
  /* If the source of I1 is a register that is set in I2 ... */
```

Then later:
```
  /* If I2 is setting a pseudo to a constant ... */
```

I recall combine checks `dead` for i2dest: "If I2DEST is not dead after I3, we can't combine I1 into I3" — hmm, actually the check is: `if (! dead) { ... }` where dead = find_reg_note (i3, REG_DEAD, i2dest) or i2dest not used after.

Let me look at the actual code.
