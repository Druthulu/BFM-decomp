---
ts: 2026-11-06T21:47:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_J1RtJ4WswotPbF5ADdCY
---
Now I see the target:

```
20 sra v0,a1,0x10      ; t = param_2 >> 16 (arith)
21 li a0,1
22 j 63c4
23 move t3,zero         ; delay slot (uVar5=0)
24 andi v0,v0,0xf
25 addiu a0,v0,1        ; iVar2 = t+1 in a0
26 sll a1,a1,0x4
27 move v1,a0           ; iv2c = iVar2
28 li v0,1              ; one = 1
29 beq v1,v0,63d8
30 nop
31 move t3,zero         ; uVar5 = 0
```

So the then-arm (iVar4 == 6): li a0,1; j; move t3,zero. Then at the join: `move v1,a0` — this is the copy iv2c = iVar2 executed on BOTH paths (the then path has a0=1, the else path a0=t+1). So the copy is after the join, unconditional: exactly our structure. Good — so the copy is in the join block, and its use `beq v1,v0` is in the same block. Hmm, so cse propagation is the enemy.

So how to stop cse from propagating `iv2c == iVar2` in the same block? The launder did it via a hard reg.

Real-C possibilities:
(a) Make the copy a mode conversion that cse doesn't equate: e.g., assign through an s16. In func_80182ED4 the copy and its use were in different blocks. Here they're in the same block.

(b) Make the copy not a pure copy in RTL: `iv2c = iVar2 + 0` folds. What about `iv2c = iVar2 | 0`? folds. `iv2c = iVar2 * 1`? folds.

(c) Make iVar2's value not provably equal to iv2c's due to a *type difference*: e.g., iv2c is `unsigned int` and iVar2 `int` — same mode; cse equates.

(d) A struct/union copy? memory.

(e) What about making iv2c the result of a *subreg* extraction that combine turns into a move: e.g., `iv2c = (int)((unsigned)iVar2 & 0xffffffff)`? folds.

Hmm — what about `(short)` where GCC can't prove the range? Then the sign-extend emits sll/sra (2 insns) — but wait: combine might then fold the sign_extend with the compare! `if ((s16)iVar2 != one)` — the compare of a sign-extended value with 1... hmm.

Actually, what if we change the *compare* instead: the target is `beq v1,v0` where v0 = one (li v0,1). If we make iv2c a genuinely different value...

Alternative approach: what if the copy comes from `iVar2` being assigned from a temp and then iv2c from that temp... same cse.

Let's think about cse's actual algorithm in GCC 2.7.2: cse records (reg1, reg2) equivalences in the table; a use of reg2 is rewritten to reg1. To prevent it, the copy must be something cse doesn't recognize as a copy: a sign_extend is NOT a copy (cse treats SET_DEST = SIGN_EXTEND(src) as a computation, not an equivalence). Then later, if the sign-extend is folded by combine into a plain reg copy, that happens AFTER cse1 (combine runs after cse1). And cse2 runs after combine? In GCC 2.7.2 the pass order: jump, cse1, loop, cse2, ... combine after cse2? Let me recall: toplev passes: jump_optimize, cse (cse1), loop_optimize, cse (cse2), ... then combine runs in the same cse pass? In 2.7.2, `rest_of_compilation`: ... cse_insn ... then `if (optimize > 0) { cse2 }` ... Actually combine is part of cse pass 2: `combine_instructions` is called from `rest_of_compilation` after cse2? Hmm.

The RM1 note says "The HImode copy `u = tmp` escapes cse2's equivalence class". So the sign-extend rtx survives cse, and later combine folds the sign_extend into a copy → the move survives.

So `tmp = (s16)iVar2; iv2c = tmp;` — here `iv2c = tmp` is a plain copy that cse WOULD equate with tmp, then propagate iv2c→tmp, leaving `tmp = (s16)iVar2` (a sign extend). Then combine folds sign_extend(iVar2) into a copy `tmp = iVar2`, and the move survives because cse already passed!

That's the mechanism, and it doesn't depend on block boundaries. In our w2 test I wrote `{ s16 tmp; tmp = (s16)iVar2; iv2c = tmp; }` and got 55 ins, no move. Why? Maybe because the sign-extend folded earlier (combine before cse? or the value's known range made expand emit a plain copy). GCC knows iVar2 in 1..16 → the sign extend is provably a no-op at RTL expansion? expand_expr for (s16)x does a convert, and if the value's range is known (nonzero_bits from the andi) it might elide.

Hmm. Maybe use a value whose range isn't known: the copy source could be a variable GCC can't bound, e.g., `param_2`? Not the same value.

Wait — what if we make the temp s16 but *store the value through a variable GCC can't prove*: e.g., `s16 tmp; tmp = iVar2; iv2c = tmp;` — the conversion to s16 happens on assignment; same.

Alternatively use a *u16* temp: `u16 tmp = iVar2;` → zero-extend; GCC knows 1..16 → folds.

Hmm. What if we widen the range by making iVar2 not provably small? iVar2 = t+1 where t = (param_2 >> 16) & 0xf — GCC's nonzero_bits tracks that t ≤ 15 (after andi). If instead we compute t differently, e.g. `t = (short)param_2 >> 12 & 0xf`? Still bounded.

But wait, does the target's `addiu a0,v0,1` mean a0 = t+1 where t is in v0 after andi 0xf. Yes.

What if the sign-extend is applied to a *larger* variable... Hmm.

Another angle: maybe the launder's real role isn't the sign-extend trick. Since the item's kind is `launder`, and the notes say "The launder was anti-coalescing: without it `iv2c = iVar2` folds into iVar2 (no move v1,a0)".

Options to break cse's copy equivalence without asm:
- A hard-register operand (pin) — forbidden to add.
- A mode conversion cse doesn't see through.
- A block boundary.

Block boundary idea: the copy is at the join, and its use is immediately after. What if we split the use into a separate block by an if:
```
iv2c = iVar2;
if (1) { one = 1; if (iv2c != one) uVar5 = 0; }
```
`if (1)` is folded.

What about `if (one) {...}`? one is pinned $2 = 1... that's a real branch.

Hmm, what if we put the copy inside the previous if/else join differently: move the `iv2c = iVar2;` INTO each arm (last statement of each arm). Then the join block contains only the use. The copy in each arm is in a different block from the use → cse can't propagate across. Then:
- else arm: `iv2c = iVar2` after iVar2 = t+1 (same block) → cse sees the copy but the use is elsewhere; it keeps the copy? Actually cse only deletes/rewrites uses; a copy with no uses in the block stays. Then at the join, iv2c is live-in, so local-alloc assigns it a reg, and a move is emitted (unless coalesced with iVar2 — iVar2 is live after the join too (used in `sll v0,a0,0x3`), so they conflict? No — iv2c = iVar2 copy: if iv2c and iVar2 don't interfere... they'd interfere because both are live simultaneously after the copy. So no coalesce → move.
- then arm: `iVar2 = 1; iv2c = iVar2;` → cse equates iv2c with iVar2 in that block, then the constant 1 propagates: iv2c = 1? In the target, the then arm has `li a0,1` and then the join has `move v1,a0`. If we write the copy in the then arm too, we'd get `li v1,1` maybe (if the copy folds to a constant). Target expects a0 = 1 then move v1,a0. Hmm.

Alternatively: keep `iv2c = iVar2` in the else arm only, and in the then arm set iv2c = 1? Let's see what the target does in the then arm: `li a0,1` (iVar2=1), `j 63c4` with delay `move t3,zero` (uVar5=0). Then at the join `move v1,a0`. So both arms flow to the join where the copy executes — unconditional.

If I put the copy in both arms: then arm would be `li a0,1; ...; move v1,a0` (one extra insn in the then path) and else `addiu a0,v0,1; ...; move v1,a0`, and the join wouldn't have the move. Total insns might be 57 (two moves) vs target 56. Not matching.

Alternative: restructure so the copy is in a block of its own *before* the join... no.

Hmm, what about making the then arm's copy disappear? If in the then arm we don't assign iv2c but the code still works... we need iv2c for the compare on both paths.

Wait — actually can we restructure the whole thing semantically? The compare is `if (iv2c != 1) uVar5 = 0;`. In the then arm, iVar2 = 1 and uVar5 = 0 already. So the compare result in the then arm: iv2c = 1, so the condition is false, uVar5 stays 0. So we could move the entire compare into the else arm only:
```
if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; }
else { t=...; iVar2 = t+1; param_2 <<= 4; { int iv2c = iVar2; one = 1; if (iv2c != one) uVar5 = 0; } }
```
But that changes the target code (the compare is in the join block, shared). We'd produce different code.

OK, different approach: what if the copy comes from a *different expression* that cse can't equate to iVar2 but still compiles to a move? For example, assign iv2c from a variable that holds the same value in a different register — like `t + 1` computed again but cse would CSE it... cse does CSE of expressions: `t+1` computed twice → the second becomes a copy of the first result → then copy propagation. Same.

What if the expression is different but provably equal only to the register allocator? e.g., `iv2c = (int)(unsigned char)(iVar2)`? emits andi. No.

Hmm, let me reconsider the do-while: w1 (do-while around the copy) gave 55. Why didn't the EBB split help? Because the do-while block merges with the following block via jump1 (no real jump). But C0535 says do{}while(0) splits cse1 EBB — maybe it does when the body contains something that prevents merging.

Let me check whether cse is even the pass doing the propagation. Could be combine (which does copy propagation within a block? combine does substitution of a register that was set by a single copy? Actually combine only combines insns; but `reg_dead` etc.). Or local_alloc coalescing: if iv2c and iVar2 are coalesced (qty merged), no move is needed. In w1, the compare `beq a0,v0` uses a0=iVar2 → so iv2c was replaced entirely.

Let me test a variant: make iv2c live longer / used later so coalescing is impossible. E.g., use iv2c again after the compare: `if (iv2c != one) uVar5 = 0;` then later `...`? Adding uses changes code.

Alternatively: make iVar2 die at the copy and be re-loaded... no.

Hmm, what about a *volatile-free* but opaque operation: a call? no.

Let me look at the actual instruction: target `move v1,a0`. The register v1 is a caller-saved temp. Note that in the target, after the copy, v1 is used only in the compare; iVar2 (a0) is used later. This is exactly a copy whose source is still live.

What if we make iv2c used *before* it's defined in some other block? no.

Idea: **use a function-scope (static?) no.**

Idea: **different variable types where the copy is a no-op but cse sees a conversion**: e.g., iv2c as `unsigned` and iVar2 as `signed` with the copy `iv2c = (unsigned)iVar2` — same mode.

What about `iv2c = iVar2; ` where iv2c is `long`? same mode on 32-bit.

What about a bit-field extraction: `struct { int f:16; }` — extracts with sll/sra.

Hmm, what about making the copy go through a *pointer dereference of a local*? memory.

What if we use the pinned `one` trick differently? `one` is a $2 pin already in the body (allowed to stay). Could we make iv2c = one... no.

Wait — maybe we can exploit an *existing* pin: `one` is `register int one __asm__("$2")`. The launder forces iv2c into a register. What if iv2c is assigned *through* the pinned variable's register? e.g., `one = 1; iv2c = iVar2; if (iv2c != one)`. No.

New idea: **make the copy a 64-bit or float conversion?** no.

Let me look at how other items in moves.md cracked "launder" kinds. grep "^launder" in moves.md.
