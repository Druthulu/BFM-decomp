---
ts: 2026-10-17T16:01:48.944Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 8d79bbc0-6d30-411b-a4e2-472ff86f0d65
---
The round-robin sharding by size gives each shard a mix of one large and one small file, which seems balanced enough—W01 ends up with the biggest file at 559 lines. The dt.sh scoring works fine, and I'll keep .run gitignored. For the bank scripts, I'm planning to have the first banker coder derive generic bank_swap.py and bank_rows.py from T10's c5 scripts, standardizing the row formats for consistency.

For the survivor row format, I'll settle on `singleton(<kind>) wall:<tag>` for the cause column, dropping the agent tag since the pass column already shows provenance via T11 crack. I'll set up a wall tags vocabulary file with seed definitions, letting coders add new tags through their results rather than risking concurrent file appends, then spawn W01-W04 with the crack coder brief enforcing the ≤8 line change constraint and no edits to src/ or config/, no signature changes, and no low-level steering tricks.

I still need to nail down how lever_census verifies a lever-free win, point coders to the reusable tryinc.py and hdump.sh scripts at the T10 path for header scoring, and sort out how partial wins get scored when a coder removes one lever kind from a function but leaves another in place.

For partial results, I'll use a result column tagged `PARTIAL:<kept kinds>` to track what's left, cap each function at a 20-30 minute wall-clock window measurable via `date`, and require that any claimed wall come with a named gcc compiler pass and a one-line mechanism explanation, verifiable through the dump tooling.

I'm mapping coder naming: crack coders map to shard numbers like T11.c<nn>, bankers get T11.b<k> or higher c-numbers like c101+, and their logs land in phase-ends/current/logs/. Crack coders work scratch-only without committing since their .run dirs are gitignored, letting bankers' commits sweep up the logs automatically via commit_task.sh, and I'll just inline the brief template directly into each Agent call rather than writing it to a separate file.

Now I'm deciding to use opus (opus55) as the model and spawn four instances.
