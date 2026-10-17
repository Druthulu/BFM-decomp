---
ts: 2026-10-17T15:59:51.309Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac3c2f25cd86a3f15
model: claude-opus-5-5[1m]
effort: medium
turnId: 8d79bbc0-6d30-411b-a4e2-472ff86f0d65
---
Of 11 functions in the family, only 4 show up as singleton rows, so the 7 801833F0 copies are likely head-class rows rather than singletons. I'm also noting that func_80136824 copies in MAIN_012 and SC04_011 weren't cracked the same way the pilot file was, so those still need the cracked body applied.

I'll fold them back into the work list with a note since the pilot attempted a different copy. For survivors, I'm tracking each function's wall cause — cse-const-addr, sched1-birth-boost, sched1-argcopy-hoist, sp-stack-switch — across S01, S09, S11, S15, S16, and S17.

The 27 instruction rows are all parked under the default no-c-spelling wall, and I still need to check which empty-function rows are missing sizes before tallying the full work count.

With 396 functions across 40 shards of ~10 at 4 coders, that's roughly 10 rounds and 30 wall-hours versus the 14h plan — the 13h projection from T10's 8 coder-min/fn assumed the 20-30 min cap as a ceiling, not a target. I'm now worried about coder context limits: 10 functions per shard could hit ~400k tokens, risky if the coder context is only ~200k, so dropping to 8 per shard (50 shards, ~13 rounds) seems safer, and I should think about banking progress instead of strict round barriers.

I'm weighing whether coders could swap/bank results mid-round without waiting for a barrier — since function-level comparison is relocation-masked, it should still work even if candidates for one function are compiled against another's already-swapped source — but keeping barriers is simpler for now, with each banker round handling swap wins, TSV drop, residue resweep, strict checks, and R22 commit in about 25 minutes per round.

Rather than banking every round, I'm considering batching every 2 rounds or every 8 shards to cut idle time, letting coders spawn into freed slots between bank points without needing a barrier each time. I also need to figure out whether the banker role requires a dedicated coder, given it involves roughly six tool calls (swap, tsv, residue sweep, strict, R22, commit).

Having a separate pa-coder banker per batch is cleaner since it keeps tool output out of my own context, even though it costs extra tokens, and it can handle cases where swap fails mid-batch. For survivor tracking, each coder records function-level results in a per-shard TSV with columns for file, func, kind, result, best tries, wall tag, and pass label, which the banker then consolidates and rewrites at the end for survivors.

I'm defining the wall tag vocabulary from the seed list of pass names (cse-const-addr, sched1-argcopy-hoist, etc.), and allowing coders to introduce new tags following a `<pass>-<what>` naming pattern, logged in a dedicated walls.tsv file.

Coders must name the compiler pass responsible and cite evidence, with pass tracking formatted as "T11 <coder shard>" and instrumentation run through delever_search with a best-of-tries flag. I'm also planning to give each coder their own copy of the scorer scripts, adapting dt.sh to take a generic workdir path under the T11 directory instead of hardcoding the T10 location.

Function names might repeat across shards since copies live in different files, so I need a naming scheme like `<Wnn>/<fn>` and should check whether duplicate function names show up within the same shard before finalizing it. Next I want to look at sc.sh, hdump.sh, and the tu file format to generalize things properly.
