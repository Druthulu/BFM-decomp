---
ts: 2026-10-17T10:09:52.246Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed9b349dc2455822
model: claude-opus-5-5[1m]
effort: medium
turnId: dfd29141-6312-4a35-8baa-9537d6cb55c6
---
These lines aren't in rejudge_targets.tsv, which makes me wonder how that file was built — maybe the residue rows were added later, after the tsv was generated. Since lever_residue.tsv is modified in the working tree, I want to check whether these specific lines existed at the time the tsv was created versus now, so I'll dig into git history with a pickaxe search.
