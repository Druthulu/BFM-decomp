---
ts: 2026-10-17T16:55:41.031Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm considering whether cse/combine would simplify repeated pointer increments into fixed offsets, and realizing I need straight-line code since GCC 2.7 at -O2 won't unroll loops without -funroll-loops — so I need to figure out what stops cse from folding the pointer arithmetic.

If the base pointer p0 is an opaque register (via asm laundering), each increment p1 = p0+4, p2 = p1+4, etc. stays as a chain of register-relative additions, whereas if p0 itself were a known constant offset like R+45, cse would fold subsequent increments into simple constant offsets like R+49. So the laundering trick works because it hides the constant-offset relationship, forcing cse to keep the increments as separate register values rather than collapsing them.

I'm now wondering whether I need a different approach entirely — maybe making p a struct pointer with a different stride, or finding some other way to force the compiler to preserve a single base register with accumulating offsets, since that matches the target's addiu chain more closely than straightforward constant folding would.

I'm also considering gcc 2.7's cse flags around block/jump boundaries, and whether p0 could instead come from a dereferenced load (p = *abase) rather than a direct address, which would change how the register gets reused across the two assignments.

Tracing through fold_rtx, the chain p0=R, p1=p0+45, p2=p1+4 should still fold into (plus R 49) since cse combines PLUS operands when one operand has a known equivalence of the form (plus reg const). The question is under what condition this folding breaks down—likely tied to how lookup_as_function resolves the register's equivalence.

Using a constant offset still collapses under CSE. The fold seems unavoidable unless the pointer value itself comes from an opaque source like a load or function return rather than a constant arithmetic chain -- which connects back to the sym-class reassignment issue seen in func_8018C2D8 and the pointer reuse pattern in func_801A31CC.
