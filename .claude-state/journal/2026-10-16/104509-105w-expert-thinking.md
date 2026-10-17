---
ts: 2026-10-16T16:45:09.088Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae95ad707bdd40ce3
model: claude-opus-5-5[1m]
effort: medium
turnId: f7b8a33c-ceaf-47c8-aacd-9e21fd244f0a
---
These are all tier-2, justified by struct_twins evidence of distinct objects. struct_twins wrote 310 sections but 241 tier-2 classes remain unlisted — because it only lists classes with distinct objects, skipping "SHARED" classes where names share objects, which are the genuine duplicates needing a fold. I need to check why grep for SHARED returned 0 on a second run, since the doc was rewritten and re-run.

This is beyond my call budget — I need to brief a coder: get check-structs passing (dup_classes 0) via the C0512/C0522 mechanism without weakening the predicate, confirm R22 at 218/218, and commit along with the struct-twins.md regen. There's a hypothesis worth flagging too: after the restamp, residue bodies' cause labels changed from TNC to TYPE-NO-MEMBER, so struct_twins loses its evidence and classes become unlisted, even though the underlying entity distinctness hasn't changed — this would mean struct_twins.py should cite residue bodies regardless of cause label, a tools-level fix the coder should verify rather than me assuming. I'll leave the generated struct-twins.md alone and just write up the brief.

I've narrowed check-structs down to one remaining failure: 241 dup_classes at tier 2, likely caused by T5's restamp invalidating the T3-cited evidence rather than an actual folding error. Since fixing this requires either repairing the evidence source or folding real duplicates—both involve loops—I'll hand this off to a coder.
