---
ts: 2026-10-20T01:14:45.269Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a543aec0a7c70e120
model: claude-opus-5-5[1m]
effort: medium
turnId: 279f4a59-e9bd-43fe-b6f4-cb544d688d68
---
That search path is just scratch work, not something to reference directly. I should present the deletion plan with sizes to the developer and only proceed once they confirm, then write the actual deletion script afterward.

I'm breaking the candidates into groups: old campaign wave scratch directories (excluding referenced ones like wave22, wave_ds2, wave_p31r), temp and hseq folders, untracked bulk from old phase folders (P32/t3, P36 engine/score, permuter, declrepair, agent packs, regen subdirs, P37 census cache, P38 t51), the large keep ledger file, and various smaller scratch directories like match, gate_main_fail, gate_lane, and repair folders.

Totaling it all up, I'm estimating roughly 25.8GB of reclaimable space, though I want exact numbers from a dry run before committing. I'm planning to build a candidate path list and use git clean with the ignored-files flag on mixed directories so tracked and whitelisted files stay untouched while everything else gets removed.

I need to watch out for the nested git repo in P33.5/kit-dryrun, which would need special handling or just skipping since it's small. For several directories I need to be careful about selective filtering — keeping outcomes.jsonl in P36/permuter, excluding specific files in P38/t51, and matching wave-pattern JSON files without catching the ones that are actually tracked like wave22_targets.json.
