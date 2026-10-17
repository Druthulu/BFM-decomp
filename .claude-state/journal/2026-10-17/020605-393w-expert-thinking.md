---
ts: 2026-10-17T08:06:05.401Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab69a93f9cd77e107
model: claude-opus-5-5[1m]
effort: medium
turnId: 3b612e9d-1673-4d65-90d1-770672d83b37
---
I'm checking whether the macro backing lookup is finding a stale latest-row — since my residue run wrote new rung S rows for three overloaded functions, those could now be the "latest" rows for (tu, fn), and if their verdict isn't in BACKED_S_V that would explain the mismatch.

Looking more closely, the likely culprit is base names shifting: T7 converted a pin into a param, so "local:a0" became "param:a0", which breaks the bclass match even though off stays the same. Given the fix requires re-running restruct's rung S writers on the affected functions rather than hand-editing the ledger, this is really coder work — I should brief a coder to identify the unbacked and uncovered sites and restore coverage through the proper ledger tooling.

Found the issue: T7's register-pins-to-params change broke macro matching since old KEPT/residue rows reference `local:aN` while bases are now `param:aN`. The fix is to re-run restruct's rung-S ledger writers on just the affected functions (no source edits, no manual ledger rows), so I'll hand this off to a coder as a search-and-rerun task.
