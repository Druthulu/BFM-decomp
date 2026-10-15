---
ts: 2026-10-15T04:50:28.373Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: 709b2f04-d315-4060-ba93-85c3894dd69d
---
I'm drafting a controls script that runs the actual verdict functions against today's real data (which fails on TNC and lying counts) and compares that against a planted scenario with clean synthetic inputs that should pass, to confirm the milestone predicate correctly distinguishes real failures from true successes.

For the residue and structs checks, I'm similarly setting up today's real pass/fail baseline alongside planted controls—like a selftest log line that should trigger a failure, and a tampered summary with duplicate classes, dead entries, or insufficient controls that should force a FAIL verdict.

For the lever strict check, today fails but a planted residue should pass, and I need to verify strict_failures with planted data too. For UNMARKED, today passes but marking one site as False should break the predicate—though replicating that cleanly without being too invasive to the real source scan is tricky, so I should check whether lever_census's own selftest already covers the "marked" field. I also need to write a script to pull the summary JSON for check_structs from the type census output.
