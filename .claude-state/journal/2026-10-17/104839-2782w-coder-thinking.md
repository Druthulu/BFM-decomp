---
ts: 2026-10-17T16:48:39.596Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
Comparing the loop back-edges, I notice mine loops back to after the lui/addiu pair (base hoisted into a3), while the target loops back to the lui itself—meaning the target rematerializes the base address each iteration instead of hoisting it.

I'm wondering whether loop.c's hoisting decision depends on register pressure thresholds—specifically `move_movables` and its `threshold * savings * lifetime` comparison against insn_count. If pinning `w` to a hard register changes the count of non-fixed regs or alters the computed lifetime/savings for the invariant, that could tip the decision away from hoisting the base address.

I'm trying different ways of writing the address computation—inlining the constant symbol reference directly into the addition rather than storing it in a separate base variable—to see if that affects whether loop.c treats it as a movable invariant.

I'm also considering reintroducing extra C statements to bump up the insn count, though that earlier attempt caused a register allocation mismatch. Let me try these variants and check the effect of the pin.
