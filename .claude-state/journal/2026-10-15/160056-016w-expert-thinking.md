---
ts: 2026-10-15T22:00:56.898Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 26e5967c-8c53-498a-863d-3266b4d6d04b
---
I'm checking the check-structs gates around duplicate structs and dead canonical names — any new def needs to either avoid layout twins or be documented with an addressed cause in docs/struct-twins.md, and dead names are only tolerated if explicitly listed under the "Dead kept" section of that doc.

Tooling note: struct_twins.py regenerates the doc from dup_gating.tsv, but it defaults to the wrong census directory (needs --census-dir pointed at the right run), so I need to be careful it doesn't silently regenerate from an empty file. Layout-identical twins without folding evidence are fine per the binding rule, so I'm now checking the size of struct_types.h and how T2 formats its definitions, looking at restruct.py around lines 4398-4445.
