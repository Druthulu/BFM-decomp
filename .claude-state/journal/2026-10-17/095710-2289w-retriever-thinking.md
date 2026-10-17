---
ts: 2026-10-17T15:57:10.861Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aaa914816ef575a97
model: claude-haiku-5-5[1m]
effort: medium
turnId: 43f50626-97f7-4955-908a-ade8877057ac
---
I'm cross-checking the win/survivor counts against the log data—tallying which function IDs matched (12 wins) versus the surviving ones with their best scores, trying to reconcile the discrepancies in the solo removal cases.

There are some inconsistencies between T10.md and c3 regarding specific "best" values, and I'm noting that tsv.py was used rather than the --write-residue flag for banking, which has its own gotcha around trailing newlines. The commit staging script and exact brief template text aren't present in the available logs, so I'll mark those as NOT FOUND in scope.

The remaining parked items include several specific functions recommended for parking, plus unresolved instruction class and signature lane issues. I also note that match_one's exact flags aren't recorded, though the mo2.sh wrapper script exists at a known path, and I'm recalling the standard scratch directory layout with win.c, notes.md, tu, and dump subdirectories supported by the shared dt.sh/sc.sh/df.sh helper scripts.

I'm also tracking the full set of helper scripts used (dis.sh, dump.sh, rtl.sh, hdump.sh, tryinc.py, batch.sh, perm.py, objfn.sh, db2.sh, sord.sh, c3df.sh), noting T9's dumpbody.sh/mo.sh were referenced but not actually inspected in this scope. For the c5 banking step, I'm confirming swap.py replaces definitions by unique match while tsv.py drops a 12-pair set spanning 20 rows total across multiple entries per function.

I'm also reviewing the cast re-sweep process (restruct with rung/residue/forms flags, logged to t10restructS.log and casts checked in t10casts3.log, with a gitignored ledger), the check-all gate result (218 passed), and the lever_census expert check — plus flagging that stale "LOAD-BEARING" comments and the do-while FAKE marker need updating in the affected files.

Now I'm computing timing stats: total coder-seconds across 20 functions works out to roughly 7.8 coder-minutes per function, with individual coder rates (~8.3 min/fn for one, ~2 min per win for another) and about 45 minutes of wall time at 4x concurrency for the crack phase. From these numbers I'm projecting that scaling to 430 functions would mean roughly 258 cracks, 172 survivors, 14 hours of wall time at capacity, and about 19M tokens consumed.

I'm now preparing to write the final report to the pending research file, keeping the content concise since the answer needs to stay within 60 lines, then will hand it back with the required "REPORT:" prefix pointing to that file.
