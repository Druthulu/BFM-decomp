---
ts: 2026-10-15T04:51:04.210Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: 709b2f04-d315-4060-ba93-85c3894dd69d
---
The selftest fixture mixes marked and unmarked pins, so checking it for unmarked sites should fail while a fully-marked fixture should pass—I'll use that as the planted control for the test. Now I'm starting to write milestone_controls.py for coverage.

I'm sketching coverage for check-casts (today's verdict from the log plus planted lying-row and uncovered-site cases), the TNC distinction on canonical vs non-canonical types, check-structs (today OK vs planted dup_classes/dead failures), lever strict failures via planted residue rows, the UNMARKED fixture case, and check-residue grep-based selftest evidence—then I'll write it all out.
