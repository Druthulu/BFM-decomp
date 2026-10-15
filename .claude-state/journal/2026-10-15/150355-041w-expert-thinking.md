---
ts: 2026-10-15T21:03:55.325Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a392f0f264a320d35
model: claude-opus-5-5[1m]
effort: high
turnId: fbd02241-c212-4c6f-9662-f763aed1dbdc
---
I'm wondering if the hash-named struct map entries are actually cluster hashes that could shift after a census refresh, which would explain why those sites aren't resolving to TYPE-NO-MEMBER in the restamp.

Actually, the top_types list still shows Unkstruct_a2c8734a stable with 2,646 sites across 126 bodies, so the name itself hasn't drifted. That means those sites must be stamped with some other cause entirely, and I should just grep the ledger directly for a2c8734a to confirm what cause they're actually tagged with rather than reasoning further in the abstract.
