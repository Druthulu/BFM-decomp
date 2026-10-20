---
ts: 2026-10-20T01:18:25.428Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a543aec0a7c70e120
model: claude-opus-5-5[1m]
effort: medium
turnId: 693094a2-d4ff-421e-b59d-7f82aed5c279
---
Symlinks won't be a problem since git clean removes just the link, not the target, and the shared top-level link stays untouched. I'll only delete the loose wave target JSON files, keeping the cards since tools read them, plus the hseq text files, then write the cleanup script.
