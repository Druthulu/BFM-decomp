---
ts: 2026-10-17T10:59:33.315Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
I'm reconsidering making e2 global too, keeping the birth boost tied to a single register-set use, but the tricky part is that the tail needs two distinct blocks, and without emitting extra code the only way to get a block boundary is through a jump target—so maybe the join label itself serves as that boundary, which suggests moving the e2 load earlier so it lands inside the second block instead.

I'm now revisiting the gcc 2.7 global-register rule itself: reg_qty requires reg_basic_block >= 0 and reg_n_deaths == 1, so if e2 dies twice across its two uses it would be forced global automatically, and I'm trying to figure out how a single-set register could rack up two REG_DEAD notes within one flow path—maybe by exploiting REG_UNUSED vs REG_DEAD semantics, or reconsidering whether `d = abs(v)` could rack up two deaths with one set to trigger the same global-boost effect.

Unless d isn't boosted because reg_n_sets isn't 1 — two sets with the first use counting as a death would make d global too, unless that first set only writes a subregister, which wouldn't kill d and would avoid the death. That would require d to be something like a 64-bit or struct value where only part of it is set at a time.

I'm also considering whether the second "set" is actually a clobber, since mark_set_1 may increment reg_n_sets for clobbers too, though abs's pattern doesn't seem to include one. Another angle is whether the abs insn is wrapped in a PARALLEL that birthing_insn_p checks for, or whether bb_live_regs fails to mark d live at scheduling time — but that seems like it should always hold true during backward scheduling once d's users have been scheduled.

Now I'm tracing through the actual scheduling order: with abs, sh28, sh24, X in sched1, v stays live through to X so there's no tie, but d (v0) and e2 overlap v1/v0 giving a0. For sched2, moving X above the flag-setting shifts requires checking whether X's fixed scalar memory reference conflicts with the d stores' varying scalar references — and by the memory conflict rules, a varying in-struct reference against a fixed scalar one shouldn't conflict, but two scalar references (one varying, one fixed) would.

So this suggests the MEM_IN_STRUCT flag could differ between the two schedules, though that seems unlikely since reload wouldn't change flags on existing insns, nor would the address of X change since it's a symbol_ref. The more promising lead is that register dependencies differ: sched1 uses pseudos while sched2 uses hard registers after reload, so a pseudo-register dependency present in sched1 might vanish in sched2 — I'm trying to figure out if X's stored value creates exactly this kind of disappearing dependency.

I'm now checking whether an anti-dependence on a pseudo could explain it, but that would require later sets of the same pseudo, which doesn't quite fit. Instead I'm looking at LUID tie-breaking among equal-priority ready insns at the same cycle, comparing X's priority against other candidates like the D_801ED9DC store to see which one would actually win the tie in sched1.

Tracking through the timeline, X becomes ready at T-2 but gets repeatedly deferred by boosted insns, while abs only becomes ready later at T-6 once its dependencies (sh28, sh24) are scheduled. In between, the picks were all higher-priority d-store insns with priority 4 versus X's priority of 2, so I need to figure out whether bumping X's priority or lowering the d-stores' priority would change the outcome, which means digging into how priority is computed as critical path length to block end.

Sh28 and sh24 get priority 4 because the final load (141) truly depends on them through aliasing with earlier stores, and that load chains further to a priority-5 node. X's priority of 2 comes from an output dependency on its last store rather than a true dependency. To raise X above priority 4, I'd need to establish X as a true predecessor of that final load (141) instead.

If 141 were a scalar-typed load rather than a varying in-struct access, it would truly depend on X's store, giving X a priority of 5 — higher than the sh28/sh24 chain. Simulating this ordering: 145 and 143 fire first, then 141 becomes ready and launches, and only then does X become ready (since it must precede 141) with priority 5, beating 138 and 135 at priority 4 — meaning X would schedule right before 141, placed after the sh instructions rather than before them.

Checking sched2 under the same reload: since 141 is still a scalar vs X's varying type, there's no real dependency, so X can float upward past sh28, sh24, and the e2 load, all of which are in-struct accesses with no conflict against X's fixed scalar. The question becomes whether backward list scheduling, given X's high priority of 5 from the critical path through 141, would actually place X immediately after the addu instruction at the top of the block, ahead of lui/sw/ori and the flag store.

So priority is set by each insn's own predecessor chain depth, meaning X's priority stays lower than sh24's. Working through the ready list at T-4, I pick 138 and 135 first since they have higher priority, then X, and abs becomes ready afterward with its boost applied.

Trying to push X's priority higher by chasing anti-dependency chains (e2 load vs the store), but the numbers keep shifting as I trace through flags-sh and abs priorities, so rather than keep reasoning through this by hand, I think I should just empirically test spelling variants on the free base to see what ordering actually results.

Each memory access in the free tail (e1 load, flags load/store, e2 load, the two d-stores, final load/store) could be written as either a struct access or a scalar cast, combined with 8 possible positions for X — so I'm enumerating that combinatorial search space, building out the access list and checking if the final store at 0x1A has a known struct type before deciding how to spell it.
