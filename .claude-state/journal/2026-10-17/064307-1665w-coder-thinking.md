---
ts: 2026-10-17T12:43:07.214Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm working through how address comparisons behave when both are constant integers versus when one is symbolic—checking whether the alias logic correctly falls back to equality checks when only one address is a true constant.

I'm also probing edge cases in how `reg_n_sets` interacts with combine: whether combine actually updates the set count after merging instructions, since the single-set assumption for `REG_EQUAL` notes depends on that count being accurate, and whether a base register reused across different purposes or set in one block then modified elsewhere could violate that assumption.

Then I'm considering whether CSE could inadvertently merge two different pseudo registers holding the same symbolic value, leaving one dead and reducing both to n_sets of 1 even though semantically they're different variables — and whether a do-while loop body that legitimately re-sets or increments the base register could be the real source of the second set needed for this to break.

Actually, since base changes value inside the loop, that leads to an extra addiu that doesn't match the target, so that path fails too. I'm now wondering if the real lever is scheduling — specifically whether sched1 can be made to preserve source order for the block, letting sched2 (which treats everything as hard registers with unknown values) reorder things to match the target, and under what conditions sched1 would keep a store before loads instead of hoisting them.

I'm checking whether the store's priority could be boosted by giving it a dependent later, but the stored value and address have no connection to the loads, so that angle doesn't work. I'm also considering whether an anti-dependence through the loads' destination pseudos could force the ordering, but the store only touches s0 and zero, so there's no link there either — I'm running out of ways to make list scheduling naturally produce this order without altering the source.

Turning back to the REG_EQUAL note, I'm reconsidering whether combine is the real source: if cse1 already propagated base's set as symbolic before combine folds t into base, the REG_EQUAL would get attached regardless of whether the source register is substituted away.

Actually the key may be an EBB boundary — if t's set is in one extended basic block and base's set is in another (split by LOOP_END), cse1 wouldn't know t's value there, leaving base unknown; cse2 ignoring that boundary would still see t ≡ sym and add the note. But that doesn't fully explain why cse2 skipped folding register-based addresses elsewhere even when it already added that REG_EQUAL in the f2 case.

What matters practically is the outcome: cse2 doesn't fold MEM addresses to constants in f2, so maybe the requirement is just that the address isn't already known to cse1. That suggests hiding the symbolic equivalence from cse1 via a loop boundary, but cse2 still attaches REG_EQUAL notes on the base register's set when it recognizes the equivalence, which would leak the information to the scheduler anyway—unless the base register itself gets replaced in a way that avoids this.

I'm now wondering whether flow treats a self-move as a dead set or counts it live, since that affects whether n_sets ends up being 1 or 2 for the relevant pseudo. Maybe there's a natural way to get two live sets of the same value without branching, or perhaps the key lies in how the scheduler tracks known register values rather than in cse2's behavior at all.

I'm also considering that combine could be merging an earlier symbolic-value assignment into the base's set instruction, losing or relocating the REG_EQUAL note in the process, which would change whether sched sees a single qualifying set.

Then I start wondering whether this is actually a sched1 problem specific to block 1 versus other blocks, and want to compare h2's larger mismatch count to see what fails differently when sched has full knowledge. I'm also reconsidering LOOP_END handling and whether function calls in cse could be invalidating call-clobbered registers in a way that breaks the single-set assumption.

Then I think about whether base could be the return value of a jal call, or computed through a parameter addressed differently inside an inline expansion, and whether the inlined function's body ends with a return label that affects how its pseudos get substituted during inline copying.

Argument copies happen before the body during integration, so I wonder if any natural label occurs inside the inline body without an explicit branch -- maybe the function's own return label, or labels from loops and switches, though those typically require jumps anyway. I'm also considering whether a trivial loop like `for(i=0;i<1;i++)` leaves behind a compare/branch that cse could still see, since gcc 2.7.2 doesn't unroll it without -funroll-loops.

Loop rotation in jump.c duplicates the exit test to the top of the loop, so cse1 can fold the top test (0<1) away entirely. But the bottom test after incrementing happens right after the back-edge label at the top of the body -- and since that label is a jump target, it marks an EBB boundary, meaning the value of the loop variable is unknown there, so the bottom test can't be folded even though i should be known to equal 1.

So I'm stuck trying to explain how the loop vanishes through cse alone, and loop unrolling only kicks in with -funroll-loops anyway. Let me shift angle: maybe the `la` instruction's target symbol isn't what I assumed -- the relocation only constrains the final address, so it could resolve to a different symbol plus offset (like an array field) and still produce the same bytes, though that wouldn't actually affect the cse reasoning.

I'm also considering whether the load address is really a raw constant rather than a symbol, checking whether `li` would assemble to `ori` instead of `addiu`, and whether GCC's MIPS backend treats large constant addresses as legitimate for cse to fold directly into a MEM operand.

CONST_INT vs SYMBOL_REF comparisons via rtx_equal_for_memref_p return false, so no conflict registers there either, matching c2's earlier observation about ori vs addiu. I'm also checking whether a constant address compiled through the "la" macro could emit lui+addiu like a symbolic address does, but gcc only uses "la" for symbolic operands and "li" for CONST_INT, so that path doesn't apply, and adding a large offset to a symbol keeps it symbolic too.

Switch jump table labels don't seem relevant either, nor does CONST_CALL_P. I'm circling back to whether reg_n_sets gets recomputed or mutated incorrectly between flow and sched1 — specifically whether combine's try_combine logic ever increments reg_n_sets when splitting an insn into two, which could cause stale assumptions about single-set registers.
