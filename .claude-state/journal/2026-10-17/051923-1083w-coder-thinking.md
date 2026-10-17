---
ts: 2026-10-17T11:19:23.848Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm tracing through the register allocation across the second test on v1, figuring out where r=0 gets placed relative to the compare and branch so the live value stays correct between v0 and v1.

Target shows "move v1,v0" copying the call result into pseudo v, which lands in v1 because r prefers v0 as its return value—so r=0 must be set before v's test for that conflict to force the split. I'm testing whether making r more heavily referenced, or splitting v's live range between local and global allocation, could explain why v ties to v0 in one block but not the other.

Checking func_80178970: the pattern seems to be a call used directly in an && condition, like `if (func() && cond) return expr; return 0;`, which matches b4's 34-instruction form, and variants like `if (!func() || a < t) return 0;` look close to b5.
