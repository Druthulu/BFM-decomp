---
ts: 2026-10-17T11:03:46.017Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm noticing that j lands correctly in a2, but the increment now uses a direct addiu without the temp-register move pattern — the target code's for-loop style increments through v0 as a temp before copying back to a2, which differs from how an explicit `j++;` statement would compile.

The key issue seems to be block placement: when the increment is in the same block as the exit test (as in a for-step), cse can fold the sign-extension into a temp before the test reads it; but when increments happen at separate continue sites that jump to a shared test block, the test reads j directly and local register allocation collapses the temp-then-copy into a plain addiu. So preserving the target's temp-move form requires the increment and test to live in the same duplicated block — meaning I'd need the loop duplication to carry over the test tail too, not just re-merge via a cross jump. I'm considering whether using normal `continue` statements in each arm could achieve this instead.

Cross-jump merges insns before an unconditional jump with ones after a label, so I'm checking if the y-store merge at that point accounts for one of the j-arm tails. I'm also wondering whether the first-iteration entry, where j=0 is already known, got folded by jump threading or cse so the preheader jumps straight into arm A — need to check what the preheader actually falls into in the target.

Shifting focus to k, worth 13 insns from a set, a hoisted use, and three triples, I want to check whether optimize_reg_copy_1 rewrote a copy `k = m` into something that doesn't get attributed to k's set — this pass scans forward from a non-dead copy until the source register dies, substituting it in between.

Actually it's the reverse: it replaces src with dest going forward, so later uses of m become k, m dying at the copy, effectively shifting refs from m to k — that would explain k's inflated count. But optimize_reg_copy_2 does the opposite when m is dead at the copy, hunting for a later `m = k` to merge backward. I'm also considering whether the long-lived variable is actually m rather than k, with the loop reading m directly from a3 after the load, and the copy `k = m` only feeding t3v, in which case there'd be no copy inside the loop region at all.

Actually, the live range length depends on insn count between definition and last use. If sched1 inserts one extra instruction between the increment computation and the move that assigns it back to j, that stretches j's dead range by one, making its live length tie with k's — and since j's register number is lower, it would win the tie-break. So I need to check what's actually scheduled in that loop-bottom block between the increment and the subsequent shift/compare/branch sequence.

But the loop-bottom block only contains the increment and the loop test, with nothing else available to interleave — so that approach doesn't work. I'm now considering whether reordering the register copies (k vs j vs t3v) before the loop test could change the live-length ratio enough to flip which allocno wins, since the tie-break depends on relative reference counts as well as live length.

This still doesn't match the target ordering of j then k though. Maybe the real explanation is that j's birth point is actually scheduled later in the first pass but reorg's delay-slot filling physically moves instructions around, changing the apparent order independent of the tie-break rule I'm assuming.

I'm wondering whether reorg actually reordered instructions into delay slots rather than the source order being different, but that doesn't match how reorg works—it only fills slots, it doesn't reorder freely. So I'm trying to figure out why `move a2,zero` didn't get pulled into the beqz's delay slot if a2 was dead there, which points me toward examining fill_eager_delay_slots and its fall-through thread logic.

I'm considering whether a2's liveness at that label is actually conservative—since j's pseudo got assigned hard register a2, maybe some other pseudo also assigned a2 is live at that point, which would block the fill even though j itself isn't live there.

Checking my own version, I see the delay slot after beqz is also a nop since the residual diff only shows ordering differences, so reorg failed to fill it in both versions too. Given that, I want to look instead at whether a cross-jump merge after reload could have produced duplicate j-referencing code in both branch arms.

Tracing the cross-jump merge: arm A loads from s6, jumps past its own addition to land at the shared store, while arm B falls straight through its own addition into the same store — so both arms compute `y = *e ± k` and the final store got unified via cross-jump since the store instructions matched exactly in registers.

I'm considering whether a shared jump-target reference elsewhere could also merge, but the common tail block has no jump reference to match against, so that path doesn't apply. I'm now thinking about whether combine could eliminate a jump reference entirely, for instance by having CSE know `j == 0` is true along one branch and simplifying a conditional store value accordingly.

Then I'm chasing whether combine understands nonzero bit ranges that CSE wouldn't fold—like masking a sign-extended value against 0x10000 producing zero only for the zero-extended case—and whether CSE's binary-operation simplifier is smart enough to catch that distinction in this version.

But crafting such an artificial expression would look fake and wouldn't survive readability scrutiny. I'm reconsidering whether the original decompiled logic might use j more naturally, maybe with different array indices being compared across the two branches to decide between 0x30 and 0x38.

The natural original likely loops over j from 0 to 1, checking count conditions in each branch and setting a value and y-offset before calling the sprite UV/position setup. But the target assembly stores the value register directly inside each arm rather than through a shared variable, so it might actually just be duplicated per-branch stores rather than a merged common path.

I'm now considering that the source could have used a sprite pointer struct directly, where the stores like s->v0 and s->y0 happen per-branch and the compiler resolved these as offsets relative to a1, matching the ot+16 addressing scheme.

I'm also reconsidering whether `k` might be a signed or unsigned 16-bit type, since that could affect how many references turn up when comparing against the baseline count of 13, and I want to check how ks16/ku16 variants behave on the same test case.

Allocation flipped so j uses `a2`, and the explicit `j++` compiles to a direct `addiu` that cross-jump doesn't merge, giving 16. Next I'll check k's width and declaration variants on the order-correct `allin_k` body.
