---
ts: 2026-10-17T12:27:39.942Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm tracing how `return expr` gets expanded with the hard register v0 as the target, and specifically how expr.c handles a TRUTH_ANDIF chain of comparisons when a target register is already supplied in a value context.

What stands out is that preset of v0=0 before the comparisons even run -- that matches the "right shape, wrong reg" mismatch I noted, suggesting a pseudo gets created instead of writing directly into the hard register. I want to dig into expr.c to see why a pseudo would be substituted when the target is a hard reg.
