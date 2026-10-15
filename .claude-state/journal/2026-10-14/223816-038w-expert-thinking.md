---
ts: 2026-10-15T04:38:16.649Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: 709b2f04-d315-4060-ba93-85c3894dd69d
---
I'm noting that the default forms are P,X, so I/M remain untested unless the milestone specifies otherwise, and I need to verify whether --only accepts a path glob for src/shared/*. Sites data was just refreshed from CENSUS, so that should be fine moving into checking structs next.

For lever_census, strict failures are excused by residue keys only when --residue is passed, so testing with the planted residue file should let the strict gate pass as a control, confirming the predicate behaves correctly when failures are excused. The UNMARKED check is already passing today, so that's more of a regression guard than a real target, and I need to find a cheap way to construct a planted control for the type_census check-casts predicate around TNC in by-cause.

I'm thinking through writing a scratch script that evaluates each milestone predicate against both the real output and a planted fixture designed to satisfy it, since causes are stamped at write time and the real finding may just be a stale stamp rather than an actual fix.

I'm weighing whether existing selftests already contain these planted controls (restruct and check-structs seem to), versus needing to build new ones for type_census and lever_census's UNMARKED check. I want to keep this proportional and avoid blowing past a reasonable tool-call budget since I can run the scratch script myself.

Let me check the actual outputs on the start tree while the nocache census is running, and in the meantime read through the strict and UNMARKED code sections of lever_census.
