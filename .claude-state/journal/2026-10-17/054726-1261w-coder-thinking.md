---
ts: 2026-10-17T11:47:26.652Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm tracing why register k still shows 13 references even after the x[m] rewrite, trying to figure out how cse2 hoisted t3v into that register and account for its copy and read counts.

Comparing the weighting between k and j: k at 13 refs over 74 uses gives .527 while j needs 14 refs to surpass that at .56, so I'm checking if there's a way to make t3v read m instead of k to shift the balance to .44 vs .4459.

This hinges on cse2's register scan logic that decides which register becomes the class head based on last-use ordering — I'm wondering if m's equivalence class could include a longer-lived register like one from the comparison temp, since several registers (c3, a, b, c, e) stay alive across all four calls.

I'm tracing whether substituting `m == c3` instead of `m == i` would cause cse's canon_reg to replace m with c3 as the class head, since canon_reg picks qty_first_reg when the register is valid and either a pseudo or not NO_REGS — this could produce the wrong instruction emitting a3 instead of reading v1, and I need to check whether cse actually folds this since c3 is a register variable set once to 3.

I'm now following the equivalence chain across the branches: on the fallthrough of `if (i == c3)`, the sign-extended temp 191 becomes equivalent to c3 (register s8), and then I'm tracking what the next branch instruction does with that equivalence.

If class {c3, tmp191, m} forms and c3 should be head as the longer-lived register, then k should resolve to c3, but the generated code uses m instead. I want to check the CSE dump directly to see how that comparison is actually recorded.
