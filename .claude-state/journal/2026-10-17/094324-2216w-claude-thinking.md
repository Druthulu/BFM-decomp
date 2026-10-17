---
ts: 2026-10-17T15:43:24.778Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: b08ad1f5-2856-43f4-9a29-899bea47b0fc
---
I'm wondering whether this milestone change counts as a replan, since T11's done-when condition already covers the re-judging case, but T13's verify step references a literal `--check --strict` flag that would fail as written. I also need to change T13's verify/done-when and amend the milestone, but plan_edit's subcommands only allow set-status, append-change, reopen, and add-task — there's no direct way to edit milestone text.

Following the precedent from the 2026-10-15 amendment, I should write a REPLAN.md and spawn a fresh planner to redraft the milestone and T13, folding in the cast-gate loose end as a task too. Meanwhile T10 looks done since its done-when covers returning blocked on cap-exceeded projections, so I can mark it complete and release the question hold with a note; T11 can proceed in parallel since its done-when already permits survivors being re-judged. Now I just need to check the right template and set-status syntax.
