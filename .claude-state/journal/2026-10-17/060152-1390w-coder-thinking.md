---
ts: 2026-10-17T12:01:52.027Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
That still seems off. Maybe the redundancy comes from v1=3 being shared across both compares in the delay slot, so CSE only folds `t != 3` if it knows t is constant 5, which depends on how the equivalence is recorded.

I'm spending many tries on this class without progress. Perhaps the real cause is the merge label also being reachable from an unthreadable path — like another jump landing inside the branch target that blocks the optimization.

Maybe the original source used `a1 == 5` directly rather than the truncated `t == 5`, since a1's upper bits are unknown and would prevent the compiler from treating both comparisons as equivalent, unlike the target which clearly reuses `s0` for both tests.

Right, so record_jump_equiv only records the fallthrough (not-taken) condition's equivalences when the jump is a simple conditional. That means when folding the next comparison `t != 3`, fold_rtx would pull in the known equivalence class for t (where it equals the constant 5) via find_comparison_args, substituting const_arg0/const_arg1 accordingly.

I'm now wondering whether t, being declared as a 16-bit type, gets promoted to SI mode on MIPS via PROMOTE_MODE, and whether the jump actually compares a sign-extended value — I should check how t is actually declared in the source to confirm this.
