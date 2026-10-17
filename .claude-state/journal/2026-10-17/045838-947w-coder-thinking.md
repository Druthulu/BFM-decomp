---
ts: 2026-10-17T10:58:38.697Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm examining how the inner loop accesses the sprite array using the index variable, noting that since it's invariant within the inner loop, the sign-extension and multiply-by-4 computation can be hoisted outside.

I'm testing variants that directly index the array by i, k, or m instead of using a separate temp, then checking how loop.c orders the hoisted invariant expressions in the preheader to match the target's sequence of j, k, t3v, pb, m24, mhi.

Then I'm reasoning about whether the mask constants (pb, masks) get hoisted all the way out of the outer loop too, since their cost-savings-lifetime product exceeds the outer loop's instruction count threshold, but that depends on whether they're treated as case 1 or case 2 user variables given they're set in one block and used across others.

If the mask were instead set *inside* the inner loop as a user variable after the conditional branch, maybe_never=1 would normally block hoisting, unless it qualifies under reg_in_basic_block_p since the set and use occur in the same block, which would make it movable after all.

So m24 gets hoisted to the end of the inner preheader. For the outer loop, though, m24's set now lives in the inner preheader while its uses are in the inner loop body — different blocks, so hoisting fails there and it stays put. That gives a hoisting order at the inner preheader following source order: j, k, t3v, pb, m24, mhi, then q at the very end since the strength-reduction giv init gets placed after invariant motion runs.

Actually wait, maybe these masks aren't user vars at all — they could be non-user temps from expression constants, meaning they'd still qualify as hoisting candidates from the outer loop too. But then in the target, the masks get set inside an if-block within the outer loop's inner preheader, so after inner-loop hoisting m24 becomes a non-user temp — fitting case (2) as a candidate, contingent on whether threshold*savings*lifetime clears the outer loop's instruction count.

Working through the numbers: outer insn_count around 500 since it's already been halved from prior inner-loop moves, lifetime spans roughly 70 across the outer loop, and with savings around 2 for a mask used twice, 58*2*70 comfortably exceeds 500 — so the mask would get hoisted out of the outer loop too. That raises the question of loop processing order: scan_loop iterates loops from innermost to outermost based on loop numbering.

So if masks are pure expressions they'd fully hoist out, but the target shows them staying inside, meaning something about these being user-declared variables (rather than compiler-generated temporaries) must block the outer move. Checking the movement conditions: in the inner loop, since the set and both uses sit in the same basic block, condition 1 (single basic block) is satisfied, so it moves out of the inner loop into the inner preheader. But in the outer loop, the set is now in that inner preheader block while the uses are in a different block (the inner loop body), so condition 1 fails; since it's a user variable, condition 2 fails too; and condition 3 (not "maybe never set") likely fails as well — so the variable stays put in the outer loop, matching the target behavior.

That same single-block logic should apply equally to the `size = 8` assignment, which would make it hoist by the same case-1 rule. Checking the cost formula, 58 times savings times lifetime of 2 gives 116, which clears the threshold of 74, so by that logic it would move too — meaning there must be a difference in insn_count or lifetime between the mask case and the size-8 case, perhaps because the masks have a longer live range (spanning further from their set point to their last use) making them more favorable for hoisting, while the size-8 var's shorter lifetime combined with a larger insn_count in the original (pre-hoisting) loop body — which included the mask computations plus other pb/t3v work — could push the threshold past 116 and keep it from moving.

Maybe the asm block spans roughly 90 instructions, and since loop runs before combine, the RTL insn count is still inflated by unmerged address computations like separate lui/addu/load sequences that later get combined away.

So for a constant like size=8 to stay un-hoisted, it must either be set more than once, or fail the movability checks—particularly the case where it's set at the top of the loop body before a conditional jump, where maybe_never is still zero at that point but something about how the loop entry condition is structured keeps it from being treated as always executed.

Comment 48 confirms that a set before the j==0 branch gets hoisted as case 3. But if the value is set in both arms with n_times_set of 2, that's not movable and becomes a global allocno spanning blocks, which could explain why it lands in the wrong register — I'm trying to figure out whether there's some other variant value, modified elsewhere in the loop, that behaves this way in the arm code.

The 8's live range spans both an arm-local set and the common block's set-plus-use, meaning disjoint lifetimes that local-alloc rejects as a multi-death variable, pushing it into a global register and likely explaining the odd placement. For it to stay local-looking yet unhoisted, it'd have to be a user variable set once in the common block with every use confined there, failing all three movability conditions.

I'm now reading through reg_in_basic_block_p to check whether the first mention tracked by regno_first_uid could actually be an earlier use in the same block, before the set — which would explain why the variable's origin appears to precede the loop.

Actually, maybe the two store arms both jump to a common block holding the size=8 assignment right before the stores, making it a global allocation case since it spans the label. Or the dead init path could instead stem from `size` being declared at the function's top and reused across an earlier call that also passes 8 as an argument.

I'm leaning toward treating this as the shared-constant case where 8 is passed consistently, but I still need to settle the ordering of hoisted variables versus explicit preheader statements — placing some as user vars set inside the loop body and others as preheader assignments before the loop starts.

Lifetime is the deciding factor here: masks and `pb` have long lifetimes spanning multiple addPrims calls, so they get hoisted out of the loop, while `t3v`'s short lifetime means its cost calculation doesn't clear the threshold, so it stays as an in-loop shift computation rather than moving to the preheader like the target expects.

This leaves me stuck on why `t3v` appears in the preheader while the `8` constant doesn't, unless the ordering of temps in the explicit source (j, k, t3v, pb, m24, mhi) gets reshuffled by CSE canonicalization favoring `k`-based reads over `t3v`'s dependency on `k`.

I'm now wondering whether CSE's equivalence tracking only kicks in when it recognizes `m` and `k` as the same value, so any expression touching `m`—including loads or shifted multiplications—gets rewritten to use `k` instead, unless the memory access breaks that chain somehow.

I also consider whether a computation based on `i` could trigger the same equivalence: the comparison between `m` and the sign-extended `i` sets up a temp register equivalence class, so a later multiplication using `i` would hash to that same class and canonicalize to `k`, matching the observed score of 10.

Testing `t3v = c3 * 4` instead: if `c3` were linked via a separate `i == c3` jump equivalence, the whole class {c3, temp, m, k} could collapse so the copy targets `c3` rather than `k`, but since the actual compiled output uses `v1` (not `s8`), that equivalence path isn't active here, so prior attempts with c3-based t3v don't match.

Given I've improved from a 35-instruction diff down to 4, I'll keep pushing on the ordering issue rather than stop yet, since I haven't hit 20 tries without gain. The remaining mismatch is about scheduling order — getting `j`'s output to appear with higher priority than `k`'s — and I'm now tracing the exact diff lines around the `callsz` block to see which specific move/insert/delete operations are misplaced.

I'm checking whether making `k`'s live range shorter than `j`'s, by changing where `k = m` is assigned relative to the branch condition, would flip the priority comparison in the scheduler's favor, but the live-range math still favors `k` even with an earlier birth point, so that path doesn't resolve the ordering issue.

Actually combine can fold across insns where cse can't easily: shifting j left 16 then masking with 0xFFFF simplifies to zero, since combine tracks the exact expression rather than just an equivalence class like cse's constant-only substitution.

The combine folding would produce the same `li v0,48` result but tip j's reference count to 14, making j win over k—but that requires a disguised keepalive expression like `q[-7] = 0x30 + ((j << 16) & 0xFFFF)`, which feels like a code smell even though the brief only bans pin/asm/volatile/builtin tricks. I'm wondering if there's a more natural way to get combine to fold a j-expression, maybe through the branch test on `(ashift j 16) != 0` and how record_jump_equiv handles it.

Checking: since cse only knows that t (the shifted value) equals 0 in arm A, not j itself, a direct expression like `j * 8` wouldn't fold there—combine can't exploit that. But since target values follow `0x30 + j*8` exactly for j=0,1, maybe the natural original code computes v from j this way outside the arms entirely, in common code rather than inside the branch arms.

I'm tracing how CSE could fold `j*8` to a constant in arm A where j is known to be 0, since both the comparison and the multiplication re-derive the same sign-extension expression, letting it collapse to 0x30. But in arm B, j isn't known to be a fixed nonzero value, so the multiplication can't fold the same way—unless that branch simply writes the literal 0x38 directly instead.

Now I'm thinking about expressions that combine (not CSE) could fold using sign/zero-bit knowledge, like masking or shifting a promoted 16-bit value by its full width to get zero, and whether CSE's simplification would catch that during expansion.

Then I shift focus to reducing j's live range instead: since j is referenced at both the loop test and the increment, it stays live across the body unless the increment were rewritten to depend on something else, which would let j die earlier.

I also check the target assembly for the shift and branch instructions in the arms, trying to see if swapping k to u16/s16 changes anything meaningful — but comparing ks16 and ku16 results, the instruction mnemonic differences don't seem to lead anywhere promising.

Now I want to concretely work through the "everything hoisted into the loop" idea, focusing on ordering: if loop.c hoists t3v, pb, m24, and mhi to the end of the preheader in sequence, with j and k set first, the output order would be j, k, then the hoisted values, then q. The risk is that t3v might not actually get hoisted since its lifetime is only 1. I also need to account for the callsz value of 8, and consider that masks and pb behave as user variables inside the loop body, which get moved under case 1, while t3v is a non-user expression tied to the array indexing computation, which falls under case 2 and is potentially movable depending on its lifetime and how CSE might canonicalize it later.

But then I realize that regardless of hoisting, the allocation problem persists: t3v still reads k, so j must be born after k by some other means, yet the target order has j born first. The only arrangement where allocation works is when j is born last, not first, which contradicts the target. I'm now looking closely at the actual loop structure to figure out whether j is really initialized where I thought, and whether the real loop top is somewhere else than I assumed.

I'm checking whether reorg would rewrite the sll instruction, and tracing through the case where v0 is set by the next instruction — confirming no replacement happens there. Then I'm considering whether the increment is instead expressed directly as a register-plus-one assignment rather than through a temp.

Now I'm working through how MIPS lacks a native HImode add, so the increment must expand via SImode with a temp register t, then truncate back into j. The real question is whether CSE recognizes j as equivalent to the lowpart of t and substitutes t into the later test — if it doesn't make that substitution, the generated code differs since the test would read j directly, producing a different `sll` instruction with no reorg rewrite possible, which would explain a byte-level mismatch against the target.

I'm now trying to pin down the exact live-range numbers for j and k that would make the target match — checking ratios like 11/75 versus 11/74, and considering that the discrepancy could come from differing instruction orderings between sched1 (pseudo-register) and sched2 (post-reload) streams, where k and j might swap relative positions due to changed dependencies after reload.

With both insns at priority 1 in sched1, there's no priority boost to break ties, so ordering falls back to luid — meaning it comes down to the original instruction order established after combine. I'm wondering whether the k-copy actually originates somewhere other than where I assumed, since loop.c typically doesn't synthesize such copies on its own.

I'm also reconsidering strength reduction's role — it generates new pseudos for givs placed at the end of the preheader, so maybe the address computation involving the symbol plus register offset isn't hoisted at all but instead expanded by the assembler macro for the load instruction, meaning the whole thing collapses into a single memory reference RTL insn with the register directly in the address. That still leaves me uncertain whether the register I'm calling v1 truly corresponds to m from the array load.

Confirming that yes, v1 loads from s5 and compares against v0, which matches the b[0] value check. I should check how much time I've spent on this.
