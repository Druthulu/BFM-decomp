---
ts: 2026-10-15T04:09:02.079Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: b505d23e-a38d-4f89-94d5-31a93a11eba1
---
I'm checking whether RESTRUCT_BBT is referenced in restruct.py, and looking at progress.py and readability_progress for timeline tsv handling and how --check-casts writes the residue census to OUT_DIR. I'm trying to figure out why the P37 and P39 census runs disagree by about 5 P sites, since both should be running type_census on the same tree.

The likely culprit is a stale walk_cache.json from a different snapshot time, or the P39 run missing --sites. I need to rerun both on the same tree now and compare, so let me go back and read the relevant progress.py section.
