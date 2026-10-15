---
ts: 2026-10-15T21:19:51.031Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8db926a6adc5bbd5
model: claude-haiku-5-5[1m]
effort: medium
turnId: 71f49971-3fa1-4ac7-ba61-10ef592c67d9
---
Twin_rescan seems unrelated to struct twins since it's about function twins via seed_ref, so I'll set that aside as a dead end. Now I'm looking at struct_twins and its evidence labels — E1-lineage, E2-anchor, E3-copy — and searching the type census for terms like "lineage" or "anchor" to see what turns up.

The real evidence keys appear to be kinds like param, assign, field, nested, field-canon, ret-of, return. I need to check the struct_map record shape around line 1460-1512 where struct_map is written, plus struct_twins' join logic near line 300-316, and the cause dict construction around 2140-2165. I've done 14 calls so far with a budget of about 20-30; I'll do a few more targeted reads before writing the report.
