---
ts: 2026-10-17T12:45:34.388Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm tracing how the inline function's saved RTL handles a return statement — it gets converted into setting the return register then jumping to the function's own return_label, which is copied along with the body. I'm wondering whether jump optimization would end up eliminating that jump if the label sits right next to it.

Then I pivot to checking whether cse2 actually folds MEM addresses into register-plus-constant forms, since an earlier case (f2) suggested it doesn't fold a known symbolic address even when equivalence was known — this matters because if cse1's extended basic block already resolved the address, sched1 just needs to see a single set on the base register (n_sets 1) to know its value, whereas f2's double-set (n_sets 2) breaks that equivalence.

I also consider whether combine could be the pass that merges a later set into the base register's defining instruction, but that requires the earlier value to come from a register whose source neither cse1 nor cse2 can resolve — which seems to require that register to be set in a separate extended basic block in both cse passes, something cse2 doesn't track since it ignores loop-end boundaries. So that path seems closed off too, and I'm now wondering if there's some non-constant equivalence note that could still let sched1 treat the base as known without actually being a plain constant.

Switching angle: maybe the loads and stores can still be made to conflict even though the base is statically known, if the store address isn't a simple REG+PLUS form that canon_rtx normalizes — like if it involves a variable index register rather than a constant offset, which canon_rtx wouldn't fold into a CONSTANT class address.

I also wonder if reg_known_value for base could itself resolve to another register (via some REG_EQUIV from parameter-passing code), though CSE typically avoids writing such notes for non-constant sources, so that path seems unlikely to produce a real conflict case either.

I'm not finding a clean mechanism that satisfies the sched n_sets≥2 requirement while still being a true double-set, so I'll shift to empirically testing candidate structures from the list — starting with a struct array pointer setup where a Light array's base address is loaded and fields are accessed through it.

Checking a byte-pointer-cast version instead, where the same base address is accessed via a `u8*` and dereferenced with an offset cast back to the struct type, then considering whether forcing char-typed stores or a struct-in-struct do-while variant changes how sched's alias analysis treats the address as varying — but that path seems to eliminate conflicts rather than create the needed double-set scenario.

Reconsidering the loop barrier placement in the LOOP_END case: if the top-level do-while contains only the base assignment versus also including the load/offset computation, the insn immediately following the loop notes becomes the barrier target, so I need to decide exactly what belongs inside that loop to position the barrier correctly.

Working through block 1's source order—computing r0 from base, storing offsets, loading values, and the final call setup—I'm checking whether cse's knowledge of base inside the loop would prematurely fold those addresses to absolute offsets, which would wreck the ordering unless those stores stay strictly after LOOP_END.

Looking at the assignment to r0[0]=0, since the address is a plain register rather than a plus-offset, it wouldn't get folded by the address-finding logic — I'm checking whether cost comparisons (REG vs symbol+offset) under MIPS's address cost rules keep it as a plain register reference. Then combine would merge r0=base-12 into a plus form while base[0]=t0 stays as a straight register reference, matching what I'd expect in the emitted store instructions.

So block 1, with reg-addressed operations, could survive cse1 even with base known, while blocks 2/3 use plus-offset addressing and need cse1 to be blind to the value — meaning they must execute after the loop ends. This suggests structuring it as a do-while(0) wrapping block 1 and the call, followed by blocks 2 and 3, with the barrier placed at the first instruction of block 2.

Trying to pin down what that barrier instruction actually is, since the natural ordering of argument setup (a0/a1 for the call) and the stores doesn't line up cleanly — I may need to reorder the source statements so the store of the constant 7 happens first, making the barrier the load of that constant rather than the zero store.

I'm wondering whether notes stay attached in the instruction stream and get reattached to whatever insn follows after combine deletes the original. Maybe the ordering comes from the call setup itself — computing the pointer argument before the constant argument, which would mean X is the addiu for a1 rather than the li for a0, but that still doesn't match the target ordering where li a0,1 appears first.

I'm now considering whether MIPS argument evaluation order (right-to-left for calls) could explain this, since that would evaluate the second argument before the first and might account for why li a0,1 ends up positioned the way it does.

Then I'm testing a specific pattern: introducing a variable set to 1 right after the loop, so that the register move at the call site could merge with that assignment and place the a0 set exactly at the position needed right after the barrier.

Combine would likely still merge the constant set into the a0 move since n only has one use feeding the call, so that register trick probably doesn't survive — this is getting tangled, and I still need to check scheduler opacity across blocks 1-3 for the stores versus loads interacting with the hoisted load.

The real obstacle seems to be sched1's opacity check requiring exactly one set of the base register with no REG_EQUAL conflict, and loop restructuring alone won't dodge that. I'm now thinking about whether a legitimately multi-set base register, or a dest without REG_EQUAL, could still produce a false conflict via the memory reference comparison logic when the base can't be canonicalized.

I'm also wondering whether the loads go through a register whose value is genuinely unknown to gcc, like a pointer variable, rather than through %hi/%lo immediates—since the raw instruction bytes would look identical either way but the compilation path would differ.

So loads are definitely absolute-addressed, which means it's really the stores that need to be "unknown" somehow, but marking them volatile doesn't fit. I'm also considering whether sched1's view of dependencies is just limited to what it can see before reload assigns hard registers, since the anti-dependence through hard regs like v1/a2/a3 doesn't seem to explain the ordering either.

Checking block 2's target ordering, it looks like loads get hoisted above a store, which confirms the base register's value must be unknown everywhere to sched1 — not just in specific blocks. So I'm narrowing down the possible reasons reg_known_value for the base register ends up being itself: either there's no REG_EQUAL/REG_EQUIV note on its single set, or the number of sets for that register isn't exactly one.

I'm now considering a fourth possibility: the base register's set might not resolve to a clean single_set with a REG destination, perhaps because it's actually a subreg — which points toward investigating how union field assignments get expanded. For a union with a pointer field and an int field, both mapped to SImode, assigning through the pointer field goes through a component reference where the field's bitsize is 32 and position 0, and I'm tracing how store_field handles this case for the register target.

Since bitsize matches the full field mode size with zero offset, the store collapses into a direct move instruction when the modes agree, so the known-value tracking should still catch it — that case checks out. I'm now wondering whether a union mixing a pointer and a float field could end up with a different mode, like SFmode instead of SImode, which could break the known-value assumption.

Tracing through: if the union's mode is SFmode but the pointer field is SImode, storing into it would produce a SUBREG destination rather than a plain REG destination. That's significant because a SUBREG destination means no REG_EQUAL note gets attached, and I need to check whether cse_insn has special handling for SUBREG destinations where the mode size is wide enough to still record the value.

The deeper issue is figuring out how layout_type actually determines a union's mode - whether it's based on the largest field or some size-equivalence rule in stor-layout.
