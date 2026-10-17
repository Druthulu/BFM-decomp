---
ts: 2026-10-17T12:31:28.139Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm recalling how expand_function_start in GCC 2.7.2's function.c sets DECL_RTL for the result decl, assigning the hard function value register and marking it with REG_FUNCTION_VALUE_P when the result is returned in a register.

Now I'm tracing through the actual RTL for reg81, which starts at zero and gets used as the target, and checking whether expand_expr picked a pseudo for the TRUTH_ANDIF case before store_expr handles assignment -- I want to look at the condition around line 2825 checking if the register number is below FIRST_PSEUDO_REGISTER.
