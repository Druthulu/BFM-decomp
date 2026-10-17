---
ts: 2026-10-17T13:56:55.570Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I'm noticing a register mismatch between the two versions—one copies arg1 into t3 while the other uses t4, and vice versa for arg2. It also looks like the target code operates directly on the original a1 register rather than a copied pseudo-register, which could explain the discrepancy in how the mask is applied.

Thinking through the global register allocator's ordering logic, I suspect arg2's longer live range (spanning through both branch paths and the pos+2/pos-2 computations) should normally give it priority over arg1, yet the target seems to allocate arg1 first—likely because the initial test against the hard a1 register affects tie-breaking in the allocator's priority queue.

If arg1's param pseudo is set directly from hard reg a1 at function entry, and the test instruction reads from and writes back into a1, that pseudo would die right there while a separate pseudo (copied via t3) carries the value forward—explaining why two distinct pseudos exist for the same argument.

I'm now wondering if declaring arg1 as a narrower type (like s16) could trigger the promotion behavior in gcc 2.7 that produces this exact copy pattern.

Changing the signature would also affect the extern declaration at line 676, which could trigger a conflicting-types error in gcc 2.7 since prototypes must match—I could work around this by patching the whole TU rather than just splicing the body, but let me try simpler register-allocation tweaks first, since the real issue might just be whether the andi result lands in a1.

Looking closer, arg1 could stay in a1 the whole time if it weren't conflicting with the temp holding a1 later (used in the negu instruction). The global allocator seems to prefer tying the param to a1 via copy preference unless there's a conflict, so I need to check whether that temp is sitting in v0 in my version instead of a1.

This suggests the C source likely has two distinct variables: one that's only checked once and dies, and a separate long-lived copy — similar to the earlier pattern where a short-lived flag and a persistent flag2 are both derived from the same value via a cast that combine recognizes.

I'm trying to find an identity transformation on arg1 that combine's pattern-matcher would fold into a plain move, but which CSE wouldn't catch earlier, since simple folds like OR-with-self, AND-with-negative-one, or shift-by-zero all get simplified too early to survive.

I'm also considering whether the short-lived use could actually read a different pseudo that combine collapses back into arg1, like a truncate-then-sign-extend-then-mask sequence that simplifies to just `arg1 & 1`, making the test unintentionally reference arg1's pseudo directly again.

But stepping back, maybe the real explanation is register allocation: the param pseudo for arg1 lives in a1 only briefly, while a local copy like `s32 f = arg1` gets the longer-lived pseudo. If so, CSE would treat f as canonical since it outlives arg1, and could legitimately replace the test's reference with f's register instead.

But using (u16)f with multiple uses means combine can't drop the explicit mask instruction, so I'd still get an extra andi — that defeats the trick. The S03 case worked because nonzero_bits(flag)=0xff made the sign-extension collapse into a plain move via combine; I need to figure out whether something analogous applies here where f has multiple uses.

For arg1, the question is whether it's known sign-extended coming in — with PROMOTE_PROTOTYPES and PROMOTE_FUNCTION_ARGS on MIPS, a short parameter would arrive as a SImode pseudo marked with SUBREG_PROMOTED_VAR_P, so uses of arg1 as an int would actually be a sign_extend of a HImode subreg rather than raw bits.

For this to simplify away, combine would need to prove the sign-extend is redundant, but the pseudo's value traces back to an arbitrary incoming hard register, so that knowledge only comes from the promoted-var flag itself rather than from actual bit analysis. I'm considering whether a cast like treating arg1 as a 16-bit value could compile down to identical code, but that's only valid if combine can prove it's a true identity, which seems doubtful here.

Another option is editing the extern declaration itself so the parameter type is s16 — I should check the timing before trying that.
