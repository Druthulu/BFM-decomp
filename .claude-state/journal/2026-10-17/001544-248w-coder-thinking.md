---
ts: 2026-10-17T06:15:44.182Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
The calibration passed, confirming the cascade head change was already part of the caller commit. Now I'm moving on to process the remaining batch-1 names, starting with 8017D254, which needs its TU plus the two shared header definitions from other overlays' variants.

Since func_8017D254 shows 11 reference files without --all-defs, I'll need to specify --tu for the overlay source explicitly, and the same approach applies to other overlay names going forward. For 80168828, I'll use --all-defs with --map-data, then run --tu twice for the headers. I'm setting this up as a background sequence script to run through everything.
