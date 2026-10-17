---
ts: 2026-10-17T12:32:18.989Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm tracing how the return value gets expanded, suspecting the retval_rhs is wrapped in a NOP_EXPR conversion around a TRUTH_ANDIF expression, and working through how that gets handled during expand_expr with the target.

I'm checking safe_from_p for the variables involved, following how VAR_DECL and INDIRECT_REF cases are handled, but I'm having trouble pinning down exactly where the problem originates in this expansion path.

Let me try a simpler experiment instead: compile a small test function like `int f(int a, int b){ return a && b; }` with a standalone cc1 and dump its RTL to see directly whether the ANDIF expansion ever targets v0.
