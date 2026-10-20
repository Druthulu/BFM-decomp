---
ts: 2026-10-20T01:13:50.029Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a543aec0a7c70e120
model: claude-opus-5-5[1m]
effort: medium
turnId: 279f4a59-e9bd-43fe-b6f4-cb544d688d68
---
I'm realizing many of these are only referenced in historical docs/ops notes rather than live readers, which makes the decision murkier -- I'll apply judgment folder by folder, keeping things if unsure, and deleting only where there's strong evidence they're unused, like the large batch of draft campaign directories in the wave folders.

Beyond those, I'm cataloging more deletion candidates: leaked temp directories, rebuildable hseq folders, untracked bulk inside old phase folders like delever/obj and census/cache, and various permuter/declrepair/regen directories that look safe to clear once outcomes.jsonl and tracked files are preserved. I still need to verify what the engine score folder contains before deciding, and confirm the ledger file matches the live version before keeping it.

For things to keep, I'm listing P40, mod/plans/status/health, the gz archives, frozen census baselines pending confirmation, and most of the git-tracked phase folders — leaving uncertain items like p39-census and the struct_twins default for a follow-up pass. For the deletion script, I'm figuring out how to scope `git clean -fdX` to specific untracked, ignored-file paths like P32/t3 without touching tracked files, noting that nested repos may need the `-ff` flag.

I need to verify every path the script removes stays under .run, so restricting git clean to specific pathspecs should work. Now I want to quickly check the layout of P36/engine/score, P36/regen, and P36/agents before finalizing.
