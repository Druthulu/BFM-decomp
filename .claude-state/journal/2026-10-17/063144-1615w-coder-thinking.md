---
ts: 2026-10-17T12:31:44.925Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm digging into expand_expr to see if there's a check that resets target when it's a hard register before the switch statement, and also considering whether c_expand_return coerces a TRUTH_ANDIF expression to int during return handling.

Tracing through the RTL, I see reg81 gets zeroed at insn 37 right before the jump on v==0, which matches the ANDIF clearing the target — so target must have been swapped out via gen_reg_rtx because safe_from_p returned false. I'm walking through safe_from_p's logic for each piece of the expression (the VAR_DECL, the PARM_DECL's RTL, the INDIRECT_REF cast) to figure out which operand triggered that unsafe result, and I want to look at lines 3880-3950 to pin it down.
