---
ts: 2026-10-16T11:42:14.323Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a877a45df9e0229a1
model: claude-opus-5-5[1m]
effort: medium
turnId: e31cc4d9-ecf8-46bb-9be1-1631c84ed118
---
I'm finding 7,128 TNC sites remaining in ov, all tied to map types absent from the frozen band file—these are new cluster hashes that emerged after the census sweep, not genuine canonical mismatches. That means the done condition needs to account for these drifted types rather than treating them as leftover non-canonical cases.

I'm wondering whether these are drift renames of band types—since cluster hashes shift when bodies get respelled—or truly novel types never captured in the band. T3's re-resolve step might be the key: it mapped band names forward to current names, so I should check if T3's doc explains how it handled this, and whether struct_map.json has merge/lineage evidence linking something like Unkstruct_e5341003 back to an old band name.

Band types now show 0 TNC sites in ov, with the ov tail at TYPE-BELOW-BAND (5,009 sites), but 7,128 ov sites still carry TNC—all tied to map type names missing from the frozen band file, likely cluster-hash drift since the freeze. I'll check how T3 re-resolved those names.
