---
ts: 2026-10-15T03:45:38.493Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7df908b0d85c75d2
model: claude-opus-5-5[1m]
effort: high
turnId: 760fd9fd-9ef6-4183-9220-a4095b678743
---
TNC essentially means these struct-map types lack canonical definitions, since far more map types exist than defined types. To resolve it, I need to define canonical types for the map types, merge the hash-named twins duplicated across overlay families, then rerun rung S over those merged bodies to fix the cast-to-member translation.

Each rung-S batch gets gated by R22 and committed through the restruct cycle script. Looking at the sizing, full TNC elimination spans nearly 292,000 sites across 13,000 types, with 95% coverage needing roughly 4,400 types — the long tail of single-site types is what makes defining canonical headers for all 13,000 such a large undertaking, especially since each canonical definition would need to come from head_types generating struct layouts from field-offset data. I'm trying to pin down whether this generation process is mechanical, and how folding duplicate twin types onto a single canonical type factors into reducing that residue.

Other TNC causes like scalar-extern and width mismatches get bucketed separately — the 3.40 goal is specifically to shrink residue through genuine fixes while leaving everything else properly marked with pass/instrument/cause tags, so I'm narrowing focus to TNC and lever fixes plus any opportunistic NO-FIELD cleanup already decided in 3.38. For the lever strict-zero target, driving it to literal zero means replacing all 1,868 oracle-judged-necessary register pins (1,496 of them asm) with C-level levers that reproduce the same codegen without relying on pinning — essentially substituting cookbook-style levers like allocno class control for what the pins currently enforce.

That's agent-shaped hard work per function given how many pins exist — historically cracking a single function pin-free has taken full agent sessions, so literal strict-zero in one phase is likely unrealistic and I should flag that with sizing data and propose milestone wording instead. I want to check how many functions are actually involved before committing to a number, and I should glance at rules R124/R126 and the GENERATION_PLAN done-criteria to make sure my proposal aligns with existing constraints.
