---
ts: 2026-10-17T11:39:26.490Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm realizing that reg_renumber treats local-alloc'd pseudos as hard regs too, so a local pseudo given a2 would pass that preference along through copies. I need to check whether any local pseudos appear in the inner loop that could be interfering with this preference logic.

Tracing through j++'s compiled form, I see a local temp v0 holding j+1, which only gives j a preference for v0, not a2 — so that's not the source. The real issue seems to be m's merged preference with k; preventing that merge requires m and k to conflict, or for m to not die right at the copy instruction, but optimize_reg_copy_1 and its various blockers (labels, jumps, intervening sets) make that tricky. I'm now examining whether m's death note could actually be occurring inside the t3v instruction itself rather than after it.

Reordering the copy and the shift instruction doesn't help either, since optimize_reg_copy_2 would likely fail without k dying in the block, and expand_preferences would just merge them again absent a real conflict. So I'm considering whether m and k could be made to naturally conflict — perhaps by extending k's liveness into the region where m is loaded — though that risks altering the actual code semantics. I'm also looking at m's concrete lifetime in the target, tracing where it's loaded via the `lhu` instruction.

I'm tracing why k survives after the loop while m doesn't get merged in: in best.c the cast makes t3v read m directly without a reg-copy rewrite, so m stays live past the point where k is set, creating a conflict that blocks merging. The real question is what construct produces a plain move surviving past cse2 without either the copy-propagation or cse rewriting it away first.

Combine runs between cse2 and local-alloc, so if combine can prove k's zero-extend is redundant (because m's nonzero bits are already known to fit within 16 bits from its lhu definition), it could simplify the extension into a plain `k = m` move, which is exactly the kind of move that would still conflict if m is used again afterward.

But combine only acts on pairs of insns linked by LOG_LINKS within a block — it won't simplify the `andi` in isolation unless it has a link to a producer or consumer in the same block. So I need to check whether k's definition is actually linked to a later user that lets combine substitute it, since that's the only path by which combine would touch this instruction at all.

Separately, if m itself is declared as a u16-typed register, then `(u16)m` is already a no-op truncation on a value that's already zero-extended, making the whole operation a trivial copy — which matches that lower score I saw earlier for the equivalent test case.

I'm also tracing cse's class-head logic: it picks k as head only when k's last use extends beyond the block and later than m's last use. That makes me look at where m gets used after the inner loop, since m and i appear to coincide in this branch — the increment `i = i + 1` seems to compute into v1 speculatively in a delay slot before the branch, which suggests the scheduler filled that slot from the branch target.

Looking more closely at CSE's basic-block extension logic: the condition hinges on whether k's last use occurs after m's, comparing their uid positions relative to the loop's cuid range. I need to check whether m gets used again after k's last reference inside the loop to see if the head register choice flips.

So k's last use moves back into the loop, making k the head and causing t3v to be rewritten to k — which seems wrong. I'm checking whether cse2 even runs here: rerun_cse_after_loop is enabled by default at -O2, so it should. Maybe plain_m's coalescing came from optimize_reg_copy_1 instead, and I need to check whether v1 gets clobbered inside the loop at instruction 191, which would change which register m's last use actually points to.

I'm now considering whether loop.c itself hoists the `k = m` copy out of the loop, since loop.c only requires a register be set once within the loop and not used before that set — k being set elsewhere outside the loop could still qualify. Testing the in-loop copy variants gives scores of 17 and 8, and the score-8 case coalesces again.

I'm also wondering where a label could naturally appear between `k=m` and the later use — maybe from the for-loop expansion structure in gcc 2.7, which lays out init, loop-begin, condition test, body, loop-continue, step, and loop-end markers in a specific order.

With loop rotation duplicating the exit test ahead of the loop body, and j=0 being a known constant that gets folded during CSE1, the preheader would end up containing something like j=0, k=m, then a folded copy of the exit test that becomes trivial since j<2 is already decidable.

If that duplicated test isn't foldable, though, a conditional jump sits right between k=m and LOOP_BEG, with hoisted insns placed after it. CSE still treats this as one extended basic block since it follows through conditional jumps, so it should still catch the equivalence -- but optimize_reg_copy_1 halts at the JUMP_INSN, which matters for whether the copy gets eliminated.

For the final code to work, that jump has to disappear before local-alloc runs, and cse2 would rewrite t3v back to k within the same extended block regardless, making m die right at the copy -- so expand_preferences would merge them without regard to the jump. So really I need m to be used afterward in a way that cse doesn't canonicalize into k, since cse normally rewrites any register reference to the quantity's first register.

There's a condition checking whether k's first use precedes the block start or its last use falls outside it, which decides whether k counts as live past this point -- and if K3 sets k earlier, that check becomes true automatically. So the real question is whether m's last use occurs after k's last use, and where k is actually referenced inside the loop body for that comparison to hold.

Actually k is used in the loop body for a separate array access since that address computation isn't hoisted, so k stays live there too. That makes me reconsider whether cse2 would even see the copy and the hoisted register in the same block — it depends on where the loop's label sits relative to the preheader code, which ties back to how `expand_start_loop_continue_elsewhere` emits its notes.

I'm trying to figure out whether a label from an earlier `if` statement could sit between `k = m` and the loop start, which would block the hoisting — though that would require the if's body to vanish entirely, which isn't typically allowed. I'm also wondering if the ordering of the `(b[-2] & 8) != 0` test relative to `k = m` could explain the discrepancy instead.

Looking at the actual MIPS sequence now: the target places `move a3,v1` after the `beqz` branch, which scheduling shouldn't be able to move past. But reorg's delay-slot filling could potentially pull that move earlier if it's independent of the branch — I'm checking whether `fill_simple_delay_slots` would slot `move a3,v1` into the nop slot of either the `bne` or `beqz` branch.

I'm also wondering whether the k=m copy arises differently entirely — maybe `k` gets its value from a reloaded memory read of `b[0]` that CSE treats as equivalent to `m`, provided no intervening store could alias and invalidate that equivalence.

Actually the k=r copy makes k the cse class head since it outlives the temp. So maybe t3v traces back to i rather than m or k — if cse records equality from the branch condition `m == i`, then on the fall-through path i could substitute for m, and the sign-extended i shifted by 2 would produce v1, explaining the sll into t3.

Let me try a batch of variants on best.c with different combinations of k=i, k=m, and indexing via [m], [i], [k]. I should look at how cse's jump equivalence merging determines which register becomes the class head, but it's probably faster to test empirically — I'll write a spec script with these variants and run it.
