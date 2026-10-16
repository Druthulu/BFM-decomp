---
ts: 2026-10-15T22:06:32.542Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a355e5f4e671b32e5
model: claude-opus-5-5[1m]
effort: medium
turnId: e98fac13-aa90-492f-ab26-6b8eacc10264
---
I realize extern_data only captures declarations, not actual global definitions, which in a decomp are often defined in separate data files. I'll pull extern_data from the walk cache after the census, and supplement it with a light regex scan to catch file-scope definitions that follow typical variable declaration patterns.

I need to handle the pointer-prefix case and allow struct/union keywords in the type regex. For determinism when a global has conflicting canonical types across files, I'll pick the most common one, breaking ties alphabetically, and otherwise just follow the order in globals_at. For the owner of a definition, I should use the lowest dl.fn_addr across the type's bodies, falling back to the lowest globals_at address, and name it like "Unkstruct_<hex addr>" matching dl.fn_addr's format—I need to verify that format. Finally, collisions should be checked by collecting all existing identifiers from src/ and include/ via regex.

I'm noting that a map type's own name might coincide with its define target when the owner address matches the map name's address, but that's fine since it only matters if that identifier collides with something already in src/include. I'll treat existing type_folds define targets, including earlier batches, as part of the reserved identifier set too, since that's safe even if unnecessary. Now I'm checking the struct_map record fields and layout entries.
