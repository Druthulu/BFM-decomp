---
ts: 2026-11-07T02:06:42.225Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ac8891974f3afdd66
model: claude-opus-5-5
effort: medium
turnId: e0c8644d-6ef7-4f4d-ab7b-71dcf29b7e37
---
The verbatim check flagged 12 rows after the T11 cracks, and the documented fix is to run `verbatim_check.py --update`. That changes one row per diff in config/verbatim_manifest.json, which is outside my file list but needed for tools-health to pass, so I'll run it and record it as a deviation. I also want to confirm the stash is from T11's HEAD state, which seems right since I haven't touched src.

Twelve verbatim-manifest rows went GONE, probably from earlier decompile work, and Makefile:304 documents `verbatim_check.py --update` as the fix. I'm applying it even though it's outside my file list, since it blocks tools-health, and will log it as a deviation.
