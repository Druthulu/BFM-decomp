---
ts: 2026-10-17T12:37:46.037Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm thinking about rtx_unchanging semantics -- an unchanging read shouldn't conflict with a non-unchanging store, but here I actually want the scheduler to detect a conflict. If the base symbol is known, adding a constant offset should canonicalize to a CONST matching the symbolic load address, letting the dependency logic treat them as the same location.

But what if the known base value isn't a plain constant but something like a register plus offset from a REG_EQUAL note, or if cse's view of the store address pseudo doesn't match reality? Loads through a known pointer would also canonicalize to a constant, so that's not it either. The QImode exemption in the struct condition is about suppressing conflicts, not creating them, so that's a different mechanism.

I'm trying to enumerate how a pseudo ends up with an "unknown" value for scheduling and cse purposes while still assembling to a load-address instruction -- either because flow counts multiple sets and cse loses track at the use site, or because the destination isn't a plain REG but a SUBREG, such as when a pointer is stored into a union/struct pseudo through a subreg of that pseudo.

I'm considering whether a union with pointer and array fields would actually end up in BLKmode and thus in memory rather than as a pseudo, which rules that out, and similarly a DImode long long doesn't fit. For the "two sets" idea, cse tracks values across the whole extended basic block, so an incrementing base pointer would still resolve to a constant at each use unless there's an EBB break. I'm now considering whether a user-written goto-to-next-label construct, which gets deleted by an early jump optimization pass before cse runs, could create exactly that kind of EBB-breaking effect while leaving no trace in the final code.

Switch statements with a non-constant selector leave real branches behind, so that's not it either. I'm instead thinking about labels whose address is taken (the GNU `&&label` extension), since those survive indefinitely and genuinely split basic blocks in the flow graph, which would block scheduling from moving code across that boundary — unlike calls, which don't end basic blocks on this target. This makes me wonder whether placing such a label right after a call instruction, so it starts a new block before the call's result is used, would actually prevent the following block's instructions from being scheduled above the call.

Looking at the delay slot and reorg filling, the label after the call stops cross-block motion, but the call itself was never a scheduling barrier here anyway. Turning to CSE, I realize the extended basic block ends at that label, so if the base address is set in the block before it, CSE in the later block won't know that base — but within the block where it's set, the store addresses could still fold to absolute addresses unless the label sits right before that set happens.

I'm now checking whether `la` could move past `sw ra` across the label boundary and concluding it can't unless `la` actually appears after the label itself. A REG_EQUAL note on the single set of the base register still lets the scheduler treat the base as known, removing the apparent conflict between stores through that base and loads in the next block, which lets those loads hoist — so both pieces are needed together.

I'm pivoting to consider whether the missing REG_EQUAL is really about a REG destination set, since src_const would be null only if cse fails to resolve a constant equivalent — but a symbol_ref source should always be constant unless the insn wasn't processed by cse1 at all, meaning it was created later, perhaps by combine building `(set base sym)` out of an intermediate temp-to-base assignment.

I'm also weighing whether this could stem from combine simplifying a non-constant expression into a symbolic constant beyond what cse would catch, though no loop invariant hoisting applies here since there's no loop. Another angle is integrate's inlining of a function's return value or constant parameter substitution, but those cases should still be visible to cse as straightforward copies.

Setjmp/nonlocal gotos don't seem relevant either. I'm now looking at canon_rtx's bounds check on reg_known_value_size for pseudos created late, and at who strips REG_EQUAL notes — candidates include combine's note redistribution during insn merging, or cse_insn itself dropping the note when src_eqv_elt doesn't apply.

I'm also wondering if combine could fold a chain like `t = sym; base = t;` into a single set on base, which would make cse propagate sym directly and leave the intermediate dead — worth checking if that's the mechanism the brief is hinting at with "a value cse cannot know."

And another possibility: if base is initialized from a `static const` pointer variable with a constant initializer, the C front end's `decl_constant_value` substitutes the initializer directly at the read site when optimizing, since the address constant is TREE_CONSTANT — this could explain the folding without cse or combine being involved at all.

Thinking from the CSE side: the (plus base k) folding depends on cse's hash table recording an equivalence between base and a symbolic constant, then equiv_constant checking the quantity's const slot. I'm now considering under what conditions that const slot fails to get set even though the defining set assigns a constant.

I'm checking whether `do_not_record` gets triggered by volatile sources, or whether a CONST expression could be rejected as non-constant—like a difference of two symbol_refs—but none of those quite fit, so I'm circling back to EBB boundaries: the only way a label present at cse1 time vanishes afterward without leaving a branch is if cse1 itself folds away a conditional branch, eliminating the label through its own constant propagation.

I'm trying to construct a concrete scenario where cse1 knows a branch condition that jump1 wouldn't—like storing a known value then branching on it—but these examples all feel too contrived to match naturally occurring code, so I'm still hunting for a more plausible trigger case.

I'm trying to pin down whether cse2 would fold `(plus base k)` once base has a constant equivalence — same fold logic runs in both passes, so if base's value is known in cse2's EBB it should collapse. But in f2, base's defining set may carry a different n_sets or an address form cse1 already rewrote, which could explain why cse2 leaves it as reg+k rather than folding to a constant.
