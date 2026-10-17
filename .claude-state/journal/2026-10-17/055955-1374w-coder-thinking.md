---
ts: 2026-10-17T11:59:55.107Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm still seeing b2 and b3 load hoisted right after the call, so I need the load to actually depend on the unk5C store rather than float freely. The halfword store to offset 0x5C (writing 0x8000) and the 32-bit load at 0xC4 would need to alias for GCC's scheduler to enforce ordering, so I'm digging into how 2.7.2's true_dependence logic in the scheduler handles this kind of partial overlap.

In GCC's memrefs_conflict_p, two base+offset references with provably different offsets off the same base register won't conflict — so unless the load uses a different pseudo register than the stores (something that can't be disambiguated at scheduling time, before register allocation unifies them to s0), there's no forced dependency. That suggests the source likely accesses memory through a separate pointer variable aliasing the same struct, which would explain why the load gets ordered right after the unk5C store in the target binary.

I'm wondering if the coalescing wouldn't happen across blocks since cse works per extended basic block, so the pointer copy might not unify there. Maybe the real explanation is a different addressing pattern entirely, or some aliasing rule in the dependency checker that treats mismatched memory references as conflicting regardless of base equality — I should look at how true_dependence actually evaluates memrefs_conflict_p.

Right, different base pseudos mean memrefs_conflict_p returns a conflict, otherwise it falls back to comparing offsets with equal bases. So the scheduler needs the load's base to use a distinct pseudo from the store's base during sched1, even though they later map to the same hard register s0. Tracing through, the param a0 gets copied into pseudo S for s0, while the free version kept both pseudos alive (s0 and s1) rather than coalescing them like the target did — so the key difference is whether the copy from the a0 pseudo into the s0 pseudo persists as a separate register through scheduling.

Maybe there's a struct copy or memory-clobbering operation between the store and load, or perhaps this is a bitfield assignment — setting a single bit to 1 would compile to a load, OR, and store sequence that could explain the pattern, with bitfield mems in this era potentially using SImode with MEM_IN_STR flagging.

I'm also wondering if scheduling priority explains why the lw stayed in place rather than being hoisted — it'd need a real dependency to not move. That suggests the original code might have gone through a differently-typed pointer, possibly declared inside the else-block, and I'm checking whether that else-block shares the same extended basic block as the entry point given the branch structure.

Given that, cse's behavior across jump targets matters: with `-fcse-follow-jumps` active, cse may carry equivalences across the jump target, but if the else label starts a fresh block, the pointer assignment there would create a new equivalence locally, replacing later uses with the canonical register. I'm now testing a hypothesis where s0 gets assigned from a0 only within the else-block as a local pointer copy.
