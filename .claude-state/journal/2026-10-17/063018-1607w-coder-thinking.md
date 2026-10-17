---
ts: 2026-10-17T12:30:18.828Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
It seems only addresses that double as call arguments get registers assigned, since CSE reuses a register for repeated stores at the same offset. So the target design likely has s0 bound to D_800A5E94 and all offset stores use s0+k, while absolute stores elsewhere remain untouched.

For CSE to not fold the base into a constant, the base pseudo must not be visibly set from the symbol in a way CSE can track — perhaps it's set across separate basic blocks, loaded from memory rather than via la, returned from a function call, passed in as a parameter, or computed from a more complex expression that obscures the constant origin.

I'm considering whether a struct with a single pointer field might live in a register and still be visible to cse, then checking a union assignment where the integer path emits li/ori rather than addiu, and finally wondering if routing the value through a hard register call result could hide it from cse — none of these seem to produce the right divergence.

Another possibility: a label surviving because jump optimization runs after cse2, and only gets deleted if cse2 actually folds a conditional branch. That would require cse2 to simplify the jump using a comparison whose operands were set up in a prior EBB, which gets complicated since the base-register assignment and the branch live in different extended basic blocks.

Maybe the original symbol just wasn't present at all, since this looks like PS1 game code (Brave Fencer Musashi, PsyQ gcc 2.7.2 toolchain), and the function could have originally been hand-written assembly pinned verbatim. I'm now considering whether the `-12` offset and the call argument relate to a GTE light structure, imagining an extern array of Light structs with position and color fields, and a pointer being derived by subtracting 0xC from that base address.

I notice the offset math doesn't quite line up with a simple struct pointer -- s0 would need to equal 5E94, which points toward the color byte field within the struct array rather than the struct base itself, maybe via something like a `u8*` pointing at the color component. Since the stores in the first block are absolute rather than relative to a struct base, that suggests the source code wasn't using a unified struct pointer for all the fields at all.

Maybe the original source had a struct array accessed through address labels, with the sibling function using separate symbols too, suggesting both compiled from constant pointer casts. I wonder if there's a macro casting an integer literal to a pointer, which would explain the absolute addressing pattern, though that raises questions about whether li or addiu instruction encoding matches what's expected.

Let me check whether func_8013CF68 is called with any arguments by grepping for its callers.
