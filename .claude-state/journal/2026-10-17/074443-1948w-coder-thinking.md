---
ts: 2026-10-17T13:44:43.144Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I'm recalling that local-alloc in gcc 2.7 only allocates hard registers for pseudos with a single set, while block_alloc handles regs local to one block—so a reg dying in multiple places likely isn't eligible for that allocation path.

Working through the target register assignment: with pv as global, p would get t0 since it conflicts with v0, v1, and a0-a3, but the target shows p in t1, implying t0 must be occupied by a local like mFF, which requires pv to instead be allocated locally in a0. For pv to qualify as local, it needs to be set once and die once within the block—so I'm checking whether the early scheduling placement avoids the birthing boost, either because the load instruction has nonzero death count or because the reg isn't set exactly once, possibly due to an address register dying at that load.

I'm now questioning whether the priority boost even applies if the pv load isn't ready yet in backward scheduling—since its sole consumer (the AND with mFF) must be scheduled first before the load becomes ready, so the boost logic may not trigger the way I assumed. I don't see an obvious way for the load itself to produce register deaths, and alternate forms of the load (different address expressions, pointer arithmetic, struct field access) all reduce to the same dependency structure.

I'm now shifting to recall how local-alloc's block_alloc in GCC 2.7 assigns quantities to registers based on whether they're confined to a single basic block and have recorded death counts, trying to recall the exact conditions in local_alloc() that trigger qty allocation for a register.

For pv, that gives two deaths — once at the masking instruction and once at the final store — but local eligibility needs exactly one recorded death despite having two sets, so I'm working out what register pattern would make the second set occur while the value is still live rather than counting as a fresh death.

Let me try a third variant with three sets of pv and only one death, keeping in mind that gcc 2.7's cse doesn't rename pseudos via SSA, so combine might still fold things—this has three sets, satisfying the REG_N_SETS>1 condition needed to suppress the birth boost.
