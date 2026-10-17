---
ts: 2026-10-17T08:09:17.312Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aee27218559a6cb07
model: claude-opus-5-5[1m]
effort: medium
turnId: 924c6b58-d828-4a45-885e-7f9083635c03
---
The key mismatch between the pin's local naming and the param's current naming suggests the pin won't resolve this directly. I'm realizing the ledger rows were keyed with the old base names, while the source macros themselves never actually changed, so I need to check which tool is responsible for writing the merged rows—likely the one handling the residue output.

The residue copy plus the residual mechanism for uncovered P sites should fix those 3 cases, but for the 7 K sites, the merged copy still retains old entries under the local naming. I need to check whether the residue writer actually rekeys these entries by inspecting the residue_rows data.
