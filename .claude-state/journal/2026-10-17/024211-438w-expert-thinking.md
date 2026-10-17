---
ts: 2026-10-17T08:42:11.488Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
I'm realizing these are sites left behind by an --apply-body run that were never individually removal-tested, so they lack an oracle verdict. To re-judge them I'd rerun delever with --rejudge --only on those specific functions, drawing their bodies and testing lever removal one at a time—I need to confirm the ladder actually removal-tests each site when applying.

I should check the delever_cycle.sh lane and look for a runbook in docs/ops, maybe grepping the cookbook index for delever references.
