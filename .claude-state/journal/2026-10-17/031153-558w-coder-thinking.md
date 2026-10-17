---
ts: 2026-10-17T09:11:53.255Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ad689c37ea88bcff0
model: claude-opus-5-5[1m]
effort: medium
turnId: f24e09ce-98d5-45d3-8db8-69a0d3469b71
---
I notice the stack argument loads happen late in the target, right before use, while mine loads them at the start — suggesting the target references incoming stack args directly as memory operands rather than copying them into pseudos at entry, unlike how I'm approaching it.

The sp adjustment appearing mid-function in the target rather than at the top is also odd. That could point to either prologue RTL being scheduled later by the compiler, or the function expanding its prologue through a different mechanism than I assumed, which would explain both the delayed stack pointer update and the late memory loads for the stack arguments.

Maybe it's a memory aliasing issue — the stores into the output array could be seen as potentially conflicting with the stack argument slots, preventing the scheduler from hoisting those argument loads above the stores. That would explain why in the target they get pushed down near their use while in my version they load early into different temporary registers.

I'm wondering if the difference traces to how gcc 2.7.2 handles stack parameter assignment — whether a pseudo gets a REG_EQUIV to its stack slot and only gets replaced by direct memory loads at each use if it never receives a hard register during allocation, rather than being copied once at entry.

Here a1/a0 are each loaded a single time and held live across the whole range, which implies they were assigned hard registers rather than left as reload-per-use equiv pseudos. That late-starting live range suggests local-alloc's equivalence-handling pass relocated the initial load from the stack slot to later in the block rather than leaving it where it originally appeared in the parameter setup.

Maybe the loads aren't moved at all but rather placed later because the stack param loads depend on aliasing with the stores. I'm wondering if gcc 2.x's assign_parms, when a parameter isn't addressable, emits the move at a point relative to where it's actually used rather than strictly at function entry, which would explain the ordering difference.

The alias analysis matters here: whether a load conflicts with a store depends on whether the memory reference is a struct member versus a scalar fixed-address access. If the pointer indexing isn't treated as "in struct," the alias checker assumes a possible conflict and keeps the load before the store, whereas a struct-field store against a fixed-address scalar load is deemed non-conflicting, letting the scheduler move the load later.

So this suggests `out` is a struct-pointer array (like SVECTOR entries with vx/vy fields), with each struct spanning several shorts, and `in` similarly composed of paired fields rather than plain scalars.
