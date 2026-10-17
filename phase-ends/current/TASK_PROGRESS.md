# TASK_PROGRESS — T11 attempt 1

Paused at the developer's request (correction 7, relayed by Claude), not a context handoff. Everything below is committed and green; no patch.

Task: T11 crack wave (lever-free rewrites of residue singletons, banked in batches)
Attempt: 1   Agent: pa-expert   Commit: 492caaa885 (B2) + this file

## Done so far
- 14 shards finished: W01-W07, WH1, G01, G02 (bank B1, T11.c101, 8408af290c: 54 fns) and G03, G04, G09, G17 (bank B2, T11.c102, 492caaa885: 24 fns). Total 78 fns banked, residue rows rewritten for every WALL.
- B2 gate: `check-all: 218 passed, 0 failed of 218` (.run/logs/t11_bank2_gate.log). Strict: `pins 1046, asm 1100, gte-levers 0, residue 2147, residue-unused 0 — OK`. Casts uncovered P=I=X=M=0 (rc 1 only from pre-existing lying=3 + CAST_NONSTRUCT unbacked 1, T18's).
- B2 per shard: G03 7 MATCH/4 WALL, G04 8/2, G09 6/4, G17 3/8.
- Disk incident (~12:26, ENOSPC): cleaned cc1 dumps + my 878 MB backup; every brief now carries the disk rule (dumps deleted after reading, shard < 200 MB, skip items with a results row). Free now ~6 GB of 73 GB.

## In flight
- Nothing from coders: no coder is running.
- Ext lane, not killed: pids 217970 (run_lane.sh) / 217971 (lane.py, deepseek/deepseek-v4.1-flash-1017 pass). Held by `.run/P40/T11/BANKING` (lane.py:58 sleeps while it exists); log unchanged since the hold. Done 9 of 28 targets, all WALL, spend $0.2078 of $12.40 for this model (smoke ~$0.13 earlier). After deepseek, run_lane.sh runs z-ai/glm-5.3-flash with another $12.40 cap ($25 total).

## Not started (27 shards, 246 items; briefs written, all with the disk rule)
- Haiku-first (single-kind, items ≤ 100 lines): G05 9, G06 9, G07 10, G08 9, G10 7, G11 8, G14 11, G15 7, G16 8, G18 10, G20 7, G21 10, G24 7, G25 6.
- Opus (multi-kind): G22 9, G23 9, G26 9, G27 8, G28 12, G29 4, G30 8, G31 12. Opus (items > 100 lines or unknown size): O01-O05 (10, 10, 10, 10, 9).
- Opus retry shards (R<nn>) for Haiku WALL/PARTIAL items: none created yet. Pending: WH1's 5 WALL + 2 PARTIAL and B2's 18 WALL (G03 4, G04 2, G09 4, G17 8). Per the rule they count as survivors only after an Opus retry.

## Routing state
- Haiku-first ON: WH1 rate (3 MATCH + 0.5·2 PARTIAL)/10 = 40 % ≥ 40 % threshold (correction 6). Haiku retries since: G03 7/11, G04 8/10, G09 6/10, G17 3/11 = 24/42 MATCH (57 %).
- Haiku model haiku, effort medium; Opus pa-coder default.

## Current hypothesis
The remaining walls cluster on a few compiler-pass shapes (sched1-birth-boost, dbr-delay-fill, cse-copy-merge, lreg-* register ties). Further Haiku shards should keep a rate near 50 %; walls in those tags are good candidates for the Opus retry, not for more Haiku attempts.

## Next 5 steps (on resume)
1. Read this file and `git mv` it to logs/T11.progress1.md; commit.
2. Decide on the ext lane: `rm .run/P40/T11/BANKING` resumes it (deepseek 19 targets left, then glm). It must be re-touched before any bank gate, and banks must rm it afterwards (bank_brief.txt rule; B2's brief said leave it).
3. Spawn the Haiku-first G shards (brief_G<nn>.txt, prompt as for the G03 retry), at most 4 concurrent, watch `df -h /`.
4. Spawn the Opus shards (G22/G23/G26-G31, O01-O05), then Opus retry shards for the Haiku walls listed above.
5. Bank each finished set with bank_brief.txt (K=103+, next B=3), as B1/B2; at the end write the T11 summary from the logs.

## Gotchas
- Disk: cc1 dumps fill the 75 GB WSL disk fast; never `cp -r` scratch for a backup.
- `restruct --residue` reads the census site list: run type_census before the cast sweep after swapping bodies (B2 banker).
- Shard dump helpers must copy TU-dir headers (ov_SC02_011_shared.h) or cpp fails (G03).
- commit_task.sh stages all of logs/, so shard logs ride along in the bank commit (B1, B2).
- SDK gte_* macros (hardcoded $12-$14) pass strict as lever-free (G04 func_8017FB04, banked); flag for the developer if that should count as a lever.
- New wall tags from B2: lreg-slt-tie, dbr-redundant-move, sched2-unit-hazard, sched2-load-delay-fill.

## State to carry verbatim
- Scratch: .run/P40/T11/ (work.tsv 396 items, parked.tsv, moves.md 131 lines, append-only shared moves log, walls.txt, coder_usage.tsv, bank_brief.txt template, bank_B1.txt, bank_B2.txt, crack_brief.txt, brief_<shard>.txt).
- Ext lane: .run/P40/T11/ext/ (lane.py, run_lane.sh, lane.tsv 9 rows, targets.json 28, run_deepseek-v4.1-flash-1017.log).
- Hold file: .run/P40/T11/BANKING (present now).

## Coder runs so far
- c01-c07 opus W01-W07 — done — logs/T11.c0<k>.md
- cH1 haiku WH1 — 3 MATCH 2 PARTIAL 5 WALL — logs/T11.cH1.md
- cG01, cG02 opus — 6/5, 6/5 — logs/T11.cG0<k>.md
- cG03, cG04, cG09, cG17 haiku (first runs ENOSPC-blocked, retries done) — logs/T11.cG<nn>.md
- c101 banker B1, c102 banker B2 — done — logs/T11.c101.md, T11.c102.md

## Reports commissioned
- R3.40-013 — T10 cracking recipe and helpers (also read: R3.40-010, R3.40-001)
