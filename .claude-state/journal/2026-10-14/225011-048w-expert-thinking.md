---
ts: 2026-10-15T04:50:11.036Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: 709b2f04-d315-4060-ba93-85c3894dd69d
---
I'm checking which planted controls fail versus pass against today's data: the TNC/lying-count conjuncts correctly fail, but the residue check passes with zero across all segments, meaning it's acting as a regression guard rather than a progress measure — a coverage predicate, not a causal one.

The selftest harness includes a planted scenario confirming that uncovered bodies/sites are flagged when residue rows are missing, and running the full selftest suite (114/114) confirms this control works. I'm also considering how to plant fail controls for check-structs (dup_classes=1 should trigger rc 1), the lever strict-literal check (already failing today, passes with excusing residue), and the unmarked-site check for lever, where I need to trace how the "un" variable gets computed to simulate a marked=False scenario. For legacy-T7 items, there's no instrument yet since the predicate is just "fixed" with no existing check for lying.

Looking at R22, it passes today as the arbiter, and the positive control from oracle calibration shows it correctly detects byte-level changes — so that's a solid fail/pass demonstration. This raises a framing issue: several instruments (check-residue, check-structs, UNMARKED, R22) already pass today as guards, so the "show it fails today" requirement doesn't literally apply to them since they're designed to always hold. I think the honest approach is to report both a pass state and a fail state for every instrument, and flag this as a finding rather than force a contradiction — noting that guard-type instruments inherently can't fail today by their nature, and that some milestone conjuncts are already satisfied by prior work (Reading A).
