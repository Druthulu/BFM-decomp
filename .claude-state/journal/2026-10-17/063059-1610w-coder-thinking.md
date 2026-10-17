---
ts: 2026-10-17T12:30:59.349Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
With branch cost 1, I'm checking whether this if/else assigning 0 and 1 to x can collapse into a direct set-condition-code instruction, since the earlier assignment is found to be constant zero and reversible, letting v0 become scc(c) directly.

For a multi-operand ANDIF chain with several jumps before the final clear/set, I need to trace how reg_set_last walks backward through the instruction stream, since it stops at labels and (for hard registers) calls but otherwise passes through jump instructions — which matters here since there's a call between the jumps and the final clear instruction in the ANDIF expansion.

So I'm checking whether the target in my RTL trace is actually the function's return value pseudo rather than v0, which would mean expand_return/expand_assignment routed through DECL_RESULT instead of reusing the ANDIF's own temp — that would explain why the target shape I expected (v0 reused directly) doesn't match what I'm seeing in the h7 RTL with pseudo register 81.

I'm not fully certain about the hard register check, so I should look more carefully at how store_expr in expr.c handles targets that are hard registers, since reg81 ends up holding v0 at the end of the RTL sequence.
