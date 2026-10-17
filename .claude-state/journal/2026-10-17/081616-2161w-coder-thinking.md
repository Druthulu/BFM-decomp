---
ts: 2026-10-17T14:16:16.465Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm seeing that CSE folds the memory offsets at +16/+32 into absolute addresses, but the +0 store still uses the plain register form, while calls keep the symbolic plus-16 form. This suggests CSE's address-cost comparison favors symbol-plus-offset over register-plus-offset for nonzero displacements, but prefers the bare register when the offset is zero—likely tied to how MIPS's ADDRESS_COST weighs these address modes.

To avoid the equivalence being folded, I need CSE to lose track that `p` equals the symbol at those store points—maybe by having `p` get reassigned, invalidated across a call, or derived through a memory load, cast, or non-constant computation like an index offset that CSE can't simplify to a known constant.

Maybe different records use separate base pointers that CSE treats as constants anyway. I'm digging into cse.c's find_best_addr logic, which tries to replace an address with the cheapest equivalent from its hash-table class, and wondering whether the equivalence class for (plus p 16) depends on p having a known constant value.

The real question is what the original source pointer was—whether it came from a function call, a volatile load, or some other source that would make CSE treat it as non-constant—and whether different gcc 2.7.2/2.8.1 cost heuristics in Psy-Q's cc1psx explain the address selection.

I'm also wondering whether CSE even sees the stores as pointer-plus-offset memory references, and how MIPS address cost macros in that era's compiler might favor one addressing form over another.

So a register-plus-constant costs less than a symbol-plus-constant by this metric, which contradicts cse picking the absolute form by cost alone—unless fold_rtx is substituting a known constant equivalent for the register directly, turning the register-plus-offset into a symbolic constant expression before cost comparison even happens.

The key seems to be whether p has a known constant equivalent (qty_const) at the point of the store. If p's defining assignment is itself a simple copy of an unresolved value, or if that definition sits in a different extended basic block, cse won't propagate the constant—so placing the pointer assignment in a separate EBB near the use might prevent the folding that produces the absolute address.

But I'm realizing this still requires p's load to end up positioned late, which only happens if cse fails to see across the EBB boundary and nothing else like reg-equiv rewriting moves the load earlier, which seems hard to arrange cleanly since p has multiple uses.

Let me reconsider whether there's actually a label in the late block that would explain this, checking the dispatch call and the s16 return path — neither seems to produce one, and there's no loop unrolling in the original source that could create it. I'm now looking at whether CSE's table gets flushed specifically at a CALL_INSN, since cse_insn invalidates memory and call-clobbered registers whenever it hits a call that isn't a known constant call.

The invalidation logic wouldn't touch pseudo registers, so that's not it either, and I'm also ruling out hard-register locals or static memory variables for p since those would just produce plain loads and stores. This pushes me toward suspecting the original code wasn't pure C at all — it likely used Psy-Q GTE inline assembly macros, where an `la` instruction embedded inside something like a `gte_ReadRotMatrix` macro could explain the unusual register behavior.

I'm fairly confident now that S16 is a dead end on the plain-C hypothesis, and testing an invented identical-arm condition for S20 wouldn't be worth it since it'd just be a fabricated fix. Instead I want to reconsider whether the S20 dead computations stem from something like a subtraction assigned into a narrow u8 field, which could produce similarly unnatural-looking code without needing division or modulo.

I'm also weighing whether loop strength reduction in loop.c is responsible, leaving behind original computations that flow.c's dead-code elimination then strips out, since propagate_block checks insn_dead_p to decide whether to delete an instruction.

Looking closer at the assembly, those sequences computing `su + w - 1` into v0 look like loop-invariant expressions that loop.c hoisted out, after which the in-loop uses were eliminated via biv/giv strength reduction.

But flow's dead-code deletion requires no side effects and a dead destination, so the real explanation may be elsewhere: combine runs after flow and merges insns, meaning it can simplify away a chain's need for an earlier producer without actually deleting that now-dead producing insn itself.

Looking at the loop body more closely, it stores `poly->u2 = su; poly->v2 = sv;` which seems to use the top-left coordinates directly — maybe the original intent was `u3 = su + w - 1` type expressions that end up getting overwritten by later stores to the same memory location before ever being read.

I'm treating S20 as a wall backed by evidence, but since the budget allows extra time beyond the minimum, I'm considering a brief additional pass testing the cross-jump identical-arms diagnostic on S20, even though the lever-free score of 43 may not improve much — the pilot cares about documenting crackability with solid reasoning more than squeezing out a marginal gain.

Notes.md only needs updating for signature changes, which there aren't any, so I'll just write the log and commit. I need to update the end timestamps too — S16's end was set before I did extra dump work afterward, so I should adjust its minutes to roughly 9 and set the correct end time now.

I've confirmed cse propagates `p`'s constant into the store addresses whenever it's set in the same extended block, and plain C can't express the needed ordering to avoid this. I'll document this as a hard wall in the log.
