---
ts: 2026-10-17T11:13:10.618Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
That cast approach isn't working better either. I'm trying other ways to get a non-folded copy of m that avoids optimization, like masking with zero, taking a pointer copy, or finding another register already holding the same value through an unrelated comparison.

What if `k = i` produces a sign-extended version of i that cse treats as equivalent to m through a jump equivalence class after the bne comparison? That still ends up merging k into the class with m as head, so k gets eliminated — not what I want.

I'm now considering whether making the comparison itself different could prevent cse from linking m and i into the same equivalence class in the first place. Another angle: if m is used again inside the loop body in a separate cse block that doesn't know k≡m, that reference stays as m and keeps it live through the loop — unless loop invariant code motion hoists that use out to the preheader first.

Once hoisted, cse's second pass would just rewrite that use back to k anyway, since it now sits after the k=m copy in the same block — that's exactly the problem that showed up with plain_m. So cse2 passing through the preheader is the real obstacle; I need either a label splitting the preheader from the copy, or a structural reason cse2 wouldn't fold the two together. Alternatively, maybe I can get combine to fold k=f(m) into an actual move if m's defining instruction and the copy are in the same basic block, since combine relies on LOG_LINKS which require the def to be local.

I'm now wondering whether reusing m's nonzero_bits — which combine computes globally across the whole function via set_nonzero_bits_and_sign_copies — could let combine simplify a cast like k=(u16)m even when the def is in a different block, since that bitmask info isn't scoped to LOG_LINKS the same way.

Making m live across the loop doesn't work either, so I'm checking the cse_basic_block_end boundary condition — k's last use beyond the block makes that true, which fails too. Let me try reversing the copy direction instead: set k first from the load, then copy m = k, so the load target becomes k directly.

Actually that still fails since the load target is v1, which belongs to the short-lived pseudo. I'm reconsidering what generates the exact sequence "move a3,v1" followed by "sll t3,v1,2" with m not dying at the copy point — maybe reorg rewrote the shift to read v1 directly because m survives past the copy instruction.

I'm trying to figure out why m and k would be treated as conflicting allocnos in global.c's conflict analysis, since at the copy insn m dies and k is born — which normally shouldn't create a conflict by the standard liveness rule.

So I'm concluding that the target must read m directly in RTL, meaning cse never substituted m with k there. That likely happens because m remained the "head" of its equivalence class — and the head-selection rule in cse depends on which register has the later last-use, so m staying head requires m's last use to be at least as late as k's, which seems to contradict the setup unless m is used again after the loop.

Maybe cse simply never saw the copy as establishing an equivalence in the first place — perhaps the copy between k and m is created later, by combine or loop optimizations rather than being present during cse's pass. I'm also considering whether promoted-mode handling plays a role: if both k and m are promoted unsigned 16-bit values stored in SImode pseudos, a plain copy between them should still register as an equivalence, so that doesn't explain the mismatch either.

I'm checking whether promoted SImode representation of a u16 variable could make the zero-extend disappear at RTL expand time, but that still doesn't match the andi pattern we need — testing k=m with mismatched widths still produces an and instruction, not a plain copy, so this avenue doesn't resolve the discrepancy either.

Now I'm considering whether loop.c's strength-reduction or combine passes might synthesize the extra copy from some trivial arithmetic like adding zero or multiplying by one, but cse would just fold those away before they ever reach that stage, so that's not it either.

I keep coming back to whether LOG_LINKS could expose the connection, but since the load defining m happens in an earlier basic block than its uses, combine can't form that link across blocks. I'm now wondering if reordering the two conditional checks — the mask test and the equality test — changes anything about how the value gets copied.

Still, that reordering wouldn't put the load and the copy in the same basic block, since blocks always end at jumps. So this cast-based route seems to dead-end without combine's help, and I need to think about CSE's jump equivalence mechanism instead — specifically what happens when the branch comparing m and se_i falls through and merges their value number classes.

I'm checking whether cse would actually make k the class head here, which depends on whether the current head is a hard register versus a pseudo, and whether canon_reg would even substitute k for m given mode-matching constraints on register replacement.

It picks the first register of a quantity, falling back to the original if it's a hard register or maps to NO_REGS. Quantities always share the same mode since make_regs_eqv only unifies same-mode registers, so differing modes block equivalence unless something like MIPS's PROMOTE_MODE normalizes integer locals to SImode first.

But looking at the dumps, j shows up as HImode -- so locals aren't being promoted here, meaning k stays HImode too. When k = m happens, since k and m have different modes there's no reg equivalence recorded, so cse treats k as a subreg of m rather than unifying them, which means later uses like t3v = m*4 still read from m directly.

Now I want to trace k's uses: zero-extending k to SI for indexing, and checking whether the a3/a2 register swaps in the ku16_m variant are actually caused by the K3 preference failing since k is HImode and the argument copy involves a sign-extend. I should pull up the full ku16_m diff to see this clearly.

Changing these widths had no effect, and I found that since these locals aren't promoted (j stays `reg/v:HI`), the `u16 k` copy from `s32 m` triggers a mode change that cse doesn't treat as equivalent. I'll now dig into why `ku16_m` scored 11.
