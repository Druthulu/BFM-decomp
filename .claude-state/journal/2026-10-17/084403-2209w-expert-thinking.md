---
ts: 2026-10-17T14:44:03.159Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a13c1de15ca946b2d
model: claude-opus-5-5[1m]
effort: medium
turnId: 20c9a92e-234c-4d50-839b-9be9e48a2849
---
I'm tallying costs: the crack token spend works out to roughly 39.8k per function, banking adds about 7.5k per win, bringing the total near 886k plus expert time, or about 44k all-in per function. On wall-clock, cracking the coder wall took 156 minutes, which is 7.8 minutes per function, dropping to roughly 2 minutes per function with 4 concurrent runs.

For the remaining 430 functions (572 rows, plus 5 blank-function asm-data rows that can't be levered since they're file-scope data), I'm projecting at a 60% success rate with a 95% CI of 39-78%, giving roughly 258 cracks and 172 survivors, leaving around 230 rows outstanding. That maps to about 17.1M crack tokens plus 1.9M for banking, near 19M tokens total, with wall time around 14 hours of cracking plus a few hours for banking batches, landing near 14-15 hours elapsed overall. I'm also noting the strict-mode residue counts against the singleton wave's limits.

Even hitting the cap of 4 concurrent crack coders doesn't bound this in a resource sense since it's unbounded in time — the real blocker is that roughly 40% of the singleton tail survives due to hard compiler walls (cse/flow/sched1) that plain C can't express, meaning literal strict zero is fundamentally unreachable. So the finish line as originally defined can't be met, and I need to flag this as blocked with supporting numbers and recommend a fallback milestone per the plan.

I'll report back as blocked, recommending the fallback: run T11 at the cap of 4 (~14 hours, ~19M tokens), expecting roughly 258 cracks, with the milestone amended from "literal strict 0" to "every survivor row re-judged with pass, instrument and named wall cause," mirroring the earlier TNC band amendment. I should also note the option to skip the zero-instruction-class cases and park certain multi-function families sharing the same seven levers, plus flag three cross-cutting issues: the header scorer only considering the first includer, dumpbody mishandling headers, and coders clashing in a shared scratch directory that needs per-function isolation.

I also need to note some format quirks accepted by the checker: K&R-style function definitions and do-while(0) blocks with markers are fine, and func_80177940's best candidate (score 37) requires a `u32*` return type across its 144 declarations, which is really a signature-lane issue.

There's also a cast gate concern: type_census returned rc 1 because of lying=3 and an unbacked CAST_NONSTRUCT flagged from T8.c4 — this looks pre-existing and not something I caused, but I should verify the coder's claim rather than just trust it, maybe by quickly grepping the t10casts3 log instead of rerunning the full type_census, since that would take too long.
