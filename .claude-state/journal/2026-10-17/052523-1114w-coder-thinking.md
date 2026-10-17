---
ts: 2026-10-17T11:25:23.636Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm noting that thread_jumps actually runs before cse1, which means the jump dump happened before that pass, so the threading in a2 was pre-cse1. Then delete_dead_from_cse runs after cse1, and between cse1 and cse2 there's a loop involving jump_optimize with some noop_moves and cross_jump settings I need to pin down.

I'm wondering if loop_optimize differs between cse1 and cse2 passes—maybe loop.c hoists invariant pointer expressions out of the i-loop into the preheader, though that shouldn't touch the head block directly. I'm also questioning whether delete_dead_from_cse's dead-code detection handles self-referential chains correctly, since count_reg_usage excludes a register's own use in its SET_SRC, and whether pe's assignment might be tangled in a REG_RETVAL libcall sequence that complicates the dead-code analysis.

Then it hits me: count_reg_usage also scans REG_NOTES, and there's a comment explaining that things used in a REG_EQUAL note aren't dead since loop may try to use them. So if cse1 attaches a REG_EQUAL note referencing pe somewhere, pe's defining instruction would survive delete_dead_from_cse even though it looks unused—I need to figure out when cse would create such a note mentioning pe.

Right, canon_reg on notes replaces registers with the canonical register of their class, not full expressions, and since pe is the only register in its class, it stays unchanged in the note. Alternatively, pe could survive if a simple copy like `(set (reg x) (reg pe))` gets processed by cse_insn and pe ends up being the cheapest choice to keep as the source.

I'm wondering if pe could instead be reused across multiple sets — maybe the same register gets assigned a new value later in the function, which would affect how cse's dead-code elimination counts its uses.

Actually, that's it: if delete_trivially_dead only checks whether a register has zero uses globally rather than per-definition, a reused variable with later uses would keep the first set alive through cse1. That survival would let the original `(plus pd 4)` equivalence persist into cse2, and then it's a question of whether flow's later life analysis is what finally deletes that first set as dead.

I'm now thinking about which pointer variable could plausibly be reused as pe — candidates like pf, pg, or ps, which already point into D_8011511E or D_8011511A — and whether reassigning one of these to double as pe (e.g. `pf = pd + 2` first, then `pf = &D_8011511E` later) would work out under register allocation.

The concern is whether having two sets of the same pseudo changes how flow/local-alloc treats it: with only one set, update_equiv_regs might substitute a REG_EQUIV constant, but with two sets that equivalence likely won't form, which could change the generated code compared to what we need.

This is a common decomp pattern though — reusing one pointer variable across cases rather than introducing pf/pg/ps separately. I should try naming it consistently as a single reused pointer and test which variant (pf, pg, or ps) matches, since ps is already set later at function scope after the switch.

I traced the bug to `delete_dead_from_cse`/`count_reg_usage` counting uses per register rather than per definition, causing a dead head set to linger in cse2's address class and get folded back in before flow removes it. I'll now test the candidate pointer locals (`pf`, `pg`, `ps`) that get reused for the head.
