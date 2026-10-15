---
ts: 2026-10-15T03:38:58.038Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae1bafab81c3094c4
model: claude-haiku-5-5[1m]
effort: medium
turnId: cce2f380-4a93-4035-9f83-e38360d1d36e
---
I notice the architecture doc flags vendor/bfm-decomp as belonging to Druthulu, and the port runs a derivation inventory against that decomp to confirm its own matched C wasn't copied from it — a deliberate check to avoid vendor-derived code. It also keeps decomp symbol names intact, like func_800189A8.

This likely ties to the user's own repo under Druthulu/BFM-decomp, probably linked to Drew T as the git author, though I should treat this as a plausible but unconfirmed identity. I'll check if there's more on known divergences or sibling ports (Parasite Eve, Xenogears) worth noting, but focus next on pulling the provenance/vendor-derivation inventory listing since that's directly tied to the derivation claim.
