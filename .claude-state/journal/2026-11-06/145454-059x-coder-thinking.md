---
ts: 2026-11-06T21:54:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_32WXWh9jdL1PKWzfuvdx
---
Line 1461-1462: `added_sets_1 = i1 && ! (i1_feeds_i3 ? dead_or_set_p (i3, i1dest) : (dead_or_set_p (i3, i1dest) || dead_or_set_p (i2, i1dest)))`.

So `dead_or_set_p(i3, i1dest)` — if iv2c is NOT dead after i3, then `added_sets_1` is true, meaning combine must add back the set of i1dest. That's allowed but then the combination doesn't remove an insn — combine still might do it if `newpat` is simpler? Typically combine rejects when the total insn count doesn't decrease... Actually combine computes `added_sets_1` and then in the cost check.

But crucially: if iv2c is used later, combine must keep the copy (added_sets_1) → the merged compare uses iVar2 and a separate copy remains — that's 2 insns, same as before, and combine's `if (added_sets_1 && ...)` might reject the whole combination.

So: make iv2c used after the compare! We need a *free* second use. Is there one? What if we use iv2c in place of iVar2 in the `r = (iVar2 << 3) | c6b` line? Then iVar2 becomes dead at the copy... but wait, is iVar2 used anywhere else? Let me check: iVar2 is used in `r = (iVar2 << 3) | c6b` only (after being set in the if/else). If we replace it with iv2c, then iVar2 dies at the copy → local_alloc will coalesce iVar2 and iv2c (the source dies at the copy) → no move. Hmm! Unless combine keeps the copy because iv2c is used later, and then local-alloc coalesces them anyway (source dies) → no move.

So that fails.

We need iVar2 to stay live AND iv2c to be used later. Two live variables with the same value. But there's no second use in the code... unless we create one at zero cost.

Hmm, what about `uVar1 = p4s | (param_3 & 0xffff) | uVar5;` — no.

OK. Let me think about the reload/tie mechanism differently: maybe we can create the move via a *struct assignment* that GCC turns into a register copy? No.

What about a conditional expression: `iv2c = (iVar2) ? iVar2 : iVar2;` → folds.

Hmm, what about an `unsigned`/`signed` mismatch in the compare that forces a conversion copy? e.g., iv2c is `unsigned int`, one is `int`, compare `iv2c != one` — comparison of unsigned with signed int → the int is converted to unsigned (no-op). combine still substitutes.

What if iv2c is `unsigned int` and iVar2 is `int`, and the copy `iv2c = iVar2` is a conversion — same mode, plain copy.

What if iv2c is `unsigned short` and compared with `one` (int)? `iv2c != one`: iv2c promotes to int with zero extension (HImode→SImode ZERO_EXTEND). The ZERO_EXTEND is a real RTL op cse can't equate with iVar2! And combine would fold zero_extend(subreg(x)) if it knows the high bits are zero — which it does (iVar2 ∈ [1,16]) → folds to a copy → merges. Hmm.

But wait: would it? The RTL for `unsigned short iv2c; iv2c = iVar2;` is `(set (reg/v:HI 102) (subreg:HI (reg 77) 0))` and the compare `(zero_extend:SI (reg/v:HI 102))`. cse keeps it. combine: can it fold zero_extend(subreg(iVar2))? It needs to know iVar2's high bits are zero. It might, given the andi+addiu. If it folds, we get a copy → merged into the compare.

Test it! It's cheap. Let me batch several candidates:

w4: `s16 iv2c;` declared as s16 at function scope, `iv2c = iVar2;`, compare with one.
w5: `u16 iv2c;` same.
w6: `iv2c = (s16)iVar2;` (w3, done =5).
w7: use `(unsigned short)` cast: `iv2c = (unsigned short)iVar2;`.

Hmm w3 was 5.

Let me think about what happens with a HImode variable: local-alloc would keep iv2c in a HImode hard reg; the compare needs sign/zero extension. If combine doesn't fold, we'd get sll/sra or sll/srl — 2 insns, 57 total.

Another idea: make the value flow through a *different SImode pseudo that combine can't fold* — e.g., an `int` variable assigned via a `union` member? memory.

What about a **volatile-free but opaque** read: a `const` global? no.

Hmm, hold on. Let me reconsider the combine adjacency. In the target, the asm insn sits between the copy... no wait, in the target RTL there's NO copy insn — the asm's tie forces reload to insert the move. So the move is generated at reload time, not by combine.

The tie: asm output reg 100, input reg 77 with constraint "0" → the input must be in the same register as the output. GCC's local-alloc/reload assigns reg 100 a register and then, since reg 77 is in a0 and reg 100 in v1, reload inserts `move v1,a0`.

To get a tie in plain C: a function call argument? No. A *return value*? no.

What about `iv2c` being assigned from a value that the compiler thinks is in a specific register? 

Hmm, what about using the existing pinned variable: `register int one __asm__("$2")`. Suppose we write `one = iVar2;` — no, one must be 1.

What if we make iv2c a pinned variable? forbidden.

OK, maybe there's a different approach entirely: maybe we can get the target's `move v1,a0` by making iVar2 die at the compare and iv2c... 

Let me reconsider: what if the move is produced by local-alloc as a *copy preference* rather than combine? No, combine kills it first.

What if we can make combine not run on that block by making the compare an insn combine can't touch? e.g., a `beq` with a constant? If the compare is against a constant 1 (not the pinned variable), the insn would be `li v0,1; beq v1,v0` anyway... The pinned `one` forces li v0,1.

Hmm, what if the compare is `if (iv2c != one)` where `one` is a hard register (v0) — can_combine_p(i1=copy, i3=jump): "Don't extend the life of a hard register" check is about src/dest being hard. i1's dest is iv2c (pseudo), src is iVar2 (pseudo). OK.

What about `use_crosses_set_p`? all_adjacent is true only if next_active_insn(i1)==i2 && next_active_insn(i2)==i3. If I insert a NOTE between? Notes are skipped by next_active_insn. So notes don't help.

Hmm, what about a non-insn but a *barrier*? no.

Let me look at combine's handling when i1's dest is not dead: `added_sets_1`. Then combine computes `i1_cost`... and later:

```
  if (added_sets_1 && ...) ...
```
Let me read around line 1460-1500 and the final profitability test.
