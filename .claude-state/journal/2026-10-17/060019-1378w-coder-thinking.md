---
ts: 2026-10-17T12:00:19.631Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I'm puzzling over why gcc 2.7.2 left a redundant comparison in the compiled output instead of folding it away — the target binary still checks `t != 3` even though `t==5` should make that always true, suggesting the original source had some construct like a switch statement that defeated the compiler's constant propagation.

Maybe the comparison involves a different variable type—like checking a (u16) cast of a1 versus t directly—which wouldn't fold the same way. Or the ordering comes from jump threading under -fcse-follow-jumps, which only works within fallthrough paths, so the redundant compare genuinely reflects source code checking something like `t == 3 || t == 5` followed by a nested `t != 3` condition guarding another call.

I realize the inner t!=3 test becomes a merge point for both the t==3 and t==5 paths, since t==3 jumps directly into that body, so CSE can't exploit the t==5 equivalence there without jump threading. But later jump optimization could thread the t==3 branch directly to the sel_054 target, bypassing the inner test entirely.

Mapping that back to C, this reconstructs to an outer `t==3 || t==5` check with a nested `t!=3` test that calls func_800291B4 and either jumps to a call site or sets sel_094, falling through to sel_054 otherwise. I'm now tracing the memory layout to confirm which address corresponds to sel_054 versus sel_094.

This confirms the redundant `t != 3` check stems from an `if (t == 3 || t == 5)` pattern, where the `||` creates a merge point that CSE can't fold, letting jump threading route the `t == 3` path directly to `sel_054`.
