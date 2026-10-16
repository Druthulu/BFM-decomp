---
ts: 2026-10-15T21:58:27.349Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 26e5967c-8c53-498a-863d-3266b4d6d04b
---
I need to clarify that the TNC count should reflect the ledger-stamped cause rather than live residue_cause, meaning the census uses stamped TNC values for both sites and bodies. I'm planning to extend residue_census with a small addition that writes tnc_types data (type, sites, bodies) into the JSON output, though I need to check whether type_census.py already handles this.

The cleanest path is adding a `tnc_types` list to residue_census.json via a minor change in type_census.py, then having restruct.py's band-decision mode read that alongside struct_map.json to freeze tnc_band.tsv (only if it doesn't already exist) and emit type_folds rows. For the actual decision logic, I need to trace how T2's 800D3888 fold works mechanically — looking at body_base_type.json and struct_map's merges/evidence fields to understand how sites in bodies get attributed to another canonical type.
