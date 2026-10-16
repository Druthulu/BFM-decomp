---
ts: 2026-10-15T22:02:50.693Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 26e5967c-8c53-498a-863d-3266b4d6d04b
---
I'm confirming struct_map sites cover all sites, not just TNC ones, then sketching the census addition: a tnc_types list per type with site/body counts, sorted by sites then bodies descending and name ascending, where bodies are distinct (tu,fn) pairs holding TNC sites of that type.

Rather than touching type_census.py, I realize decide mode could just load sites.jsonl and the latest ledger directly and run residue_split itself to get per-type TNC sites, since the census run already writes sites.jsonl with the `--sites` flag. This would let the freeze-band calculation happen in restruct.py using the same data, then cross-check against residue_census.json's totals -- I just need to verify sites.jsonl's mtime lines up with the same census run.

To be safe I'll start by running a fresh full census on HEAD -- first with `--sites`, then `--check-casts --residue` -- so there's a clean baseline before freezing anything. I'm not sure if the residue check rereads sites.jsonl or recomputes it, so I'll run these myself in the background via run.sh and check timing and `type_census --help` to confirm behavior.
