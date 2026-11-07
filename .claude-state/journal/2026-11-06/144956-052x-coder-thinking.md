---
ts: 2026-11-06T21:49:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rejVUfETVtM89UI8Qpzm
---
cse's copy propagation for reg-reg copies: In 2.7.2, cse doesn't propagate a simple reg copy into later uses (that's more like `cse_insn`'s handling of SET with src_eqv for comparisons only). Hmm.

Actually the mechanism could be **combine**: combine_instructions merges `iv2c = iVar2` into the following compare since iv2c dies there — combine substitutes the source register into the using insn. Combine is a peephole over up to 3 insns; a reg copy followed by a use of that reg is folded by `subst`. That's a well-known combine behavior: "combine merges a reg copy the target keeps" — wall tag `combine-copy-merge`.

So the enemy might be combine, not cse. If so, the sign-extend trick works because combine folds sign_extend(subreg(x)) into x only under specific conditions... In func_80182ED4, combine did fold it ("the sign extension folds away") — but the copy survived there because it was in a different block (combine works per basic block, over up to 3 insns). Right! combine only looks within a basic block. So the RM1 trick's real mechanism is the block boundary, not the mode.

OK so: to keep the copy, put it in a different basic block from its use, in a way jump1 doesn't merge, and combine can't see across.

Hmm, but the copy must still execute on both paths (target: at the join).

What if we put the copy at the END of each arm? Then the use is in the join block. As computed, that adds a move in both arms → 2 moves. But wait: in the then arm, iVar2 = 1; iv2c = iVar2 → combine folds to `li v1,1`? Or the constant propagates: iv2c = 1 → `li v1,1`. Then at the join, `beq v1,v0`. Target has `li a0,1` in the then arm and `move v1,a0` at the join. Different.

Unless the then arm assigns `iv2c = iVar2` and combine folds `iv2c = iVar2` where iVar2 was just set to 1 → both become... combine could merge `li a0,1` + `move v1,a0` into `li v1,1` and `move a0,v1`? Hmm.

Different idea: keep the copy at the join but make the *join block* start before the copy in a way that combine can't merge the copy with the compare... combine merges consecutive insns in a block; can't prevent.

Unless the copy is separated from the compare by a non-combinable insn. In the target, between `move v1,a0` (27) and `beq v1,v0` (29) there's `li v0,1` (28) — the `one = 1` assignment. So the copy is 2 insns before the compare. combine looks at up to 3 insns, so it CAN still merge through the li? Combine substitutes a register set by insn1 into insn3 only if insn2 doesn't clobber... `li v0,1` sets v0 (a different reg), so combine can propagate iv2c's value into the compare (it does "2 insns into 1" with an intermediate insn that doesn't conflict).

Hmm, in our mine, `li v0,1` at 27 and `beq a0,v0` at 28: the copy was merged.

OK so what if the copy is farther than 3 insns from the use? Then combine can't reach. But the target has it 2 insns away... The target's move survived because it was in a different register from the start (the asm forced it).

Wait — why would combine merge the copy into the compare at all? Combine's `try_combine` looks at i1, i2, i3; here i1 = `iv2c = iVar2`, i2 = `one = 1`, i3 = compare. It tries to combine i1+i2+i3. Substituting iv2c in i3 with iVar2 is allowed if iv2c's death... it requires iv2c dead after i3 — yes (used only there). So combine does it. Unless the register has a REG_DEAD/REG_UNUSED note making it... no, combine merges.

BUT combine has a rule: it won't substitute if the result would be more expensive? No, substitution of a register with another register is always profitable.

Hmm, so how did the sign-extend version survive in func_80182ED4? Because combine couldn't simplify `sign_extend(tmp)` where tmp = subreg(t) unless it knows the sign extension is redundant. It said "the sign extension folds away (t is a sign-extended s16 already)" — combine has REG_EQUAL/sign-extension knowledge from the load `lh`. So combine folded sign_extend into a copy `u = t`, but by then it had consumed i1/i2/i3 differently... The copy then survived because the use was in another block (combine is per-block).

Hmm, in func_80182ED4 the use `t = u - 1` is in the else block, while `u = tmp` was before the if. So block boundary.

So for us: we need the copy in a different block than the compare, with the same code shape. 

Where could a block boundary be? The compare is at the join. If the copy were in the join block and the compare... same block.

What if we introduce a block boundary between them by an `if` that is *always taken the same way* but not provably so? That would add a branch instruction — target has none.

Alternative: make combine unable to substitute by making the copy's destination a register that combine won't touch: e.g., if iv2c's value is used in a way that combine can't fold — like being compared against a hard-reg pinned variable... it already is.

Hmm. What if the copy source is a *pinned* register variable? The existing pins: one=$2. Hmm.

What about using the existing pin `one` ($2) as the copy destination... no.

Let me reconsider. Maybe cse IS the culprit (not combine). Let me test empirically: take w2 and add something that stops cse (do-while) → w1 was do-while around the copy and still 55.

Test: what does the .cse dump show? Let me look at the RTL right after cse for w1 to see if the copy survived cse but died in combine. I have dumps only for w2. Let me check the .cse dump for the copy insn.

Let me find the insn with the compare in w2.i.cse: grep for "reg:SI 1" etc. Hard.

Better: use the dumps' `;;` comments? The .rtl dump might have `;; iv2c` via DECL comments? GCC 2.7.2 print_rtl doesn't print decl names.

Alternative: use the .lreg dump to see the move... 

Let me try a different approach: search cse.c for how a reg-reg copy is handled. Line 3720: "so we can distinguish it from a register-register-copy." Let me read around 3690-3740.
