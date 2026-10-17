---
ts: 2026-10-17T08:07:49.834Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aee27218559a6cb07
model: claude-opus-5-5[1m]
effort: medium
turnId: 924c6b58-d828-4a45-885e-7f9083635c03
---
I'm checking whether the --residue path actually covers the K macro sites: the merged copy still carries stale KEPT(SIGN) local:a0 entries, so residue alone resolves the 3 P cases but not the 7 K cases unless the residue writer also normalizes the bases.

But I'm now questioning why the 3 P sites end up uncovered in the first place — their row is MEMBERS with MEMBER entries keyed by local, so maybe residue_match itself normalizes bases differently there. I need to trace through residue_match and _residue_key in restruct.py to see exactly how the key normalization works.
