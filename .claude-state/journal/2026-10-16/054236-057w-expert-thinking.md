---
ts: 2026-10-16T11:42:36.832Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a877a45df9e0229a1
model: claude-opus-5-5[1m]
effort: medium
turnId: e31cc4d9-ecf8-46bb-9be1-1631c84ed118
---
These 7,128 sites fall under types with no folds row and no band membership, meaning they're new since the freeze—likely because the sweep reshuffled site membership and union-find clusters, generating fresh hash names. I need to decide how to classify them: either treat them as drift and fold them in by checking for E1 evidence of canonical bodies, or try mapping them back to old band/tail names using site overlap with the previous census.

Applying the planner's own rule that "the tail = every TNC map type not in the band" would mechanically classify these as tail by definition. But this feels too convenient—these could actually be drifted band types whose sites split off, and labeling them as below-band could mask sites that deserve band status. The scale is suspicious too: 7,128 sites is close to the entire tail's size, and one type alone (e5341003) has 768 sites, which doesn't look like typical below-band magnitude.

So I'm thinking the honest approach is to treat these as post-freeze drift types and trace their origin rather than mislabel them. I want to inspect struct_map.json for e5341003's merge history, evidence, and bodies to see if it traces back to a band type that got renamed or split—if so, the fold policy should apply. I'll write a scratch script to pull a few fields from the top new types and check whether their sites' bodies reference canonical types from the latest rung.
