---
ts: 2026-10-15T03:49:22.741Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7df908b0d85c75d2
model: claude-opus-5-5[1m]
effort: high
turnId: 76dfb9f8-086c-49db-b4bc-a2c84ee77998
---
I'm tallying the crack targets across categories — roughly 800 distinct items spanning head-classes, singletons, missing-parameters, gte-clobbers, and asm macros/routines. Many of the 438 singletons will need individual agent cracking, which at historic rates (like the P36 lane's 9 sessions and 15-20M tokens) makes this a costly lane to price out.

Realistically, strict zero within a single phase is unrealistic given this volume, so I need to size it honestly and propose milestone wording instead. I'm also checking whether the TNC data from residue_census.json is current, and want to dig into struct_map.json to understand type layouts — specifically what counts as a definable map type (likely hash-named structs inferred from observed field offsets/widths across overlay copies of shared functions). I plan to check restruct.py and type_census --help to understand the --write-types option and the L rung before proceeding.
