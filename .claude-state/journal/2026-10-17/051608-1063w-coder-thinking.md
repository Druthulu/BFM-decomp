---
ts: 2026-10-17T11:16:08.897Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm tracing where update_equiv_regs gets called, within local_alloc after sched1, and checking how optimize_reg_copy_1 scans forward through the post-sched1 instruction stream to find where a register dies before stopping at a label or jump.

If optimize_reg_copy_1 rewrites the copy and shifts the death note for m to the copy point, that would cause expand_preferences during global allocation to share m and the copy target, leading to coalescing -- unless the death note lookup fails because the mode comparison between the note and the source register doesn't match. I'm checking whether update_equiv_regs's optimize calls are actually active under -O2 (since flag_expensive_optimizations is set), and confirming that in the u_m case (score 1), the AND operation isn't a plain reg copy, so optimize_reg_copy_1 never triggers and m stays live into v1 -- whereas with a plain copy and a later read of m, the death note would move and global's conflict computation (which relies on REG_DEAD notes) wouldn't see a conflict between m and the copy target.

I'm now reconsidering whether the target's register k actually inherits a3's preference at all, or whether the allocation order depends purely on priority. I'm also exploring other ways to produce a `move a3,v1` with m in v1 -- specifically whether it could come from a same-mode copy, a mode-changing copy combined within the same block, or a truncating subreg assignment where a 16-bit register k is set from a signed 32-bit m via a HImode subreg.

Since k's value is just a truncation of m, sign-extension is needed in principle — let me dig into the ks16_m diff more closely to see what's actually happening.

Since a plain copy would just get coalesced away, the remaining candidate is a truncating subreg move (s16 k), and `ks16_m` scored 11—so I'll check whether that cost comes solely from allocation.
