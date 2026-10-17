---
ts: 2026-10-17T12:27:31.794Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm noticing the 76-instruction version uses absolute addressing because CSE folds the constant base into the stores, but the target needs the base to stay unknown—something like a function return value or parameter rather than a compile-time constant.

But since the target has lui/addiu forming a constant, it still looks like an absolute address, not a loaded pointer. Maybe this comes from an inlined function where a constant pointer argument gets substituted directly by integrate.c, or from a struct access where the base is offset by some fixed amount like -12 from a known symbol.

I'm also wondering if this could be a loop-like pattern over multiple records, but the differing immediate values across blocks argue against a true loop, since those would be loaded dynamically rather than via li. I keep circling back to cse/combine semantics—whether a register set to a constant gets recorded as equivalent depends on whether the RTL pattern is a simple set to a constant, versus some non-foldable expression that only later combine passes could simplify, which might explain why the base address stays opaque in this case.

I'm checking whether func_8013CF68 actually takes a parameter by looking at its callers and whether a0 is ever set before the call—but since the target code zeroes a0 first and never references it, that rules out a parameter-based base.

Now I'm considering whether cse's handling of calls could invalidate a constant equivalence—but calls only clobber hard registers and memory, not pseudo equivalences, so that's not it either. I'm also looking at how scheduling's alias analysis computes known register values from REG_EQUIV/REG_EQUAL notes when a register is set exactly once to a constant.

I'm trying to figure out what makes the target's base opaque to both cse and scheduling while o1 resolves it fine, considering possibilities like a static local pointer, a function returning a constant that gets inlined (which integrate would still constant-fold), unusual casts through different-width types, or address arithmetic on an array of structs—none of which seem to explain the opacity, so I'm now wondering if the base is set inside a switch or conditional block instead.

It's odd that block 1 mixes absolute stores for some fields with base-relative stores for others, matching o1's output exactly. Maybe cse only partially recognized base equals a known symbol, leaving some fields absolute and others through s0 — or perhaps the source is fully absolute globals and cse introduced the s0 register itself through some related-value optimization.

I'm trying to figure out what makes s0 equal to D_800A5E94 specifically — maybe a call argument or constant offset from a different base symbol, since o1's opcode-exact match on this pattern is a strong clue I need to track down.

I'm considering how the base pseudo could become opaque to CSE: if it's set in a different extended basic block, split by a code label before its use, that value becomes invisible to optimization. Labels can come from control structures, but I'm wondering whether an unreferenced user label might get deleted during jump optimization in this compiler version, which would change how the alias behaves.

Reviewing the compiler's pass order, I'm thinking the deletion of zero-use labels happens in jump.c before CSE runs, so an unreachable label likely wouldn't survive to create the EBB split I need. I'm now focusing on whether CSE still tracks values across loop boundaries and what register conditions prevent scheduler passes from reordering the instruction, particularly around single-set registers and REG_EQUAL notes.

Actually, does cse even add a REG_EQUAL note when the set already has a constant source? I should check that part of cse.c around where it decides whether to attach the note for constant sets.
