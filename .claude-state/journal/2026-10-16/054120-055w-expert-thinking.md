---
ts: 2026-10-16T11:41:20.198Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a877a45df9e0229a1
model: claude-opus-5-5[1m]
effort: medium
turnId: e31cc4d9-ecf8-46bb-9be1-1631c84ed118
---
The census check seems quick since it's likely reading cached site data. The bigger issue is the 23,630 TYPE-NOT-CANONICAL count overall -- I need to know how many of those fall within ov specifically, since the census json only breaks things down by covered/uncovered rather than by ov. I should check if there's a sites file, like residue_census.json, that would let me compute the ov-specific TNC breakdown.

I'm also noticing NO-EDIT grew substantially to 53,763, and TYPE-NO-MEMBER sits at 7,542, lower than the expected ~9.6k -- some sites were probably redrawn. The band-def-with-zero-bodies case belongs to a later pruning task, not something I need to resolve now. To find the ov-specific TNC count, I should check how residue_census computes by_cause, likely from per-site ledger entries, so I'll look at the relevant section of type_census.py.
