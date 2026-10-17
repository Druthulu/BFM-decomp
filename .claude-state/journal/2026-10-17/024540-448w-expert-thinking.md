---
ts: 2026-10-17T08:45:40.282Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5b87281e13247865
model: claude-opus-5-5[1m]
effort: medium
turnId: 6f12df8e-268b-4475-9998-393bc5c7470d
---
I need to work through re-judging the 543 rows left by the author plus the ~41 unjudged non-macro rows using the delever apply/rejudge/only flow, which draws bodies, strips levers per site ladder, and keeps the winning text while filtering by function names.

I'm checking that delever_cycle.sh handles the batching, R22 step, and commit, but it may call git commit directly rather than routing through commit_task.sh as the rule requires — the coder should fix that, invoking delever.py with --apply --rejudge --only and a labeled batch, then running R22 and committing properly. I also want to confirm whether delever's per-site ladder tests removal individually and tags each site's oracle verdict, since the census flags "oracle DIFFERS on removal" whenever any site of a kind diverges — meaning after re-judging, rows will either disappear or get marked as DIFFERS, which should let the 3.39 claim about all 1,868 pins being NEEDED reconcile against the actual counts of removed versus DIFFERS rows.

Then there's the tricky case of the 56 gte-lever rows for func_8013AD38 spread across overlay TUs, flagged with a vague "no canonical macro" instrument despite gte_rtv0tr existing — I suspect these were processed by gte_consolidate --rejudge, which might try respelling gte_rtv0tr_m to gte_rtv0tr per file and keep the macro header if it DIFFERS. But since gte_consolidate likely doesn't write to the delever ledger and --write-residue preserves existing rows verbatim, the only way to refresh instruments is to delete all affected rows and regenerate the residue from scratch so the ledger recomputes everything.

Without ledger rows, these gte-lever and macro-def entries will just come back as "not judged," which pushes them into the agent escalation bucket — I could hand-edit the instrument cells afterward since the TSV is allowed to be manually configured, but the done-criteria wants zero unresolved "not judged" rows (or at least evidence for each). Given how large this is, I want to check what gte_consolidate --rejudge actually does before going further, so let me pull up its help text.
