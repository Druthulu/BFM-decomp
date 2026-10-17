---
ts: 2026-10-17T16:00:32.360Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 8d79bbc0-6d30-411b-a4e2-472ff86f0d65
---
Rather than chase down those three file-scope barrier instances individually, I'll bundle them as a single work item for the final cleanup shard, labeled "file-scope barrier" for a coder to investigate removal and record results. Now I'm moving on to scope and overall design.

With 396 functions and a shard size of 8, that's roughly 50 shards. I'll regenerate the plan at N=8, pull the two func_80136824 duplicates out of the pilot batch, and fold the blank-func rows into the final cleanup shard too. Each coder handles about 8 functions, with wall-clock time typically around 1.5 hours and worst case under 4.

For banking, I'm considering doing it every 8 shards -- pausing new spawns, waiting for active coders to finish, running the banker, then resuming. The downside is idling slots for up to an hour while waiting on the slowest coder, largely because the R22 clean step can't safely run alongside active crack coders. I'm weighing whether a separate git worktree could isolate the banker's clean build, but that risks missing untracked inputs like the ROM image, so it's probably not worth the complexity -- I'll accept the idle time instead. I'm also considering whether crack coders only need their own build artifacts scored, which might let the banker work around the conflict.

Since the R22 rebuild during make clean creates a window where coders' --try calls could fail with confusing errors, I need a barrier mechanism so coders don't hit that gap. I'm now defining per-coder scratch directories with isolated prefixes, generic helper scripts that take the shard directory as a parameter, a setup script to generate shard folders with the necessary files, and a results.tsv format capturing match status, win.c scoring, and timing for each function.

For the banker component, I need swap.py and tsv.py from the earlier task, generalized for reuse—let me check their current sizes before adapting them.
