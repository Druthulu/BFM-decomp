# TASK_PROGRESS — T11 attempt 13 (PAUSED by developer correction)

## Done so far
- B4 banked (926e7a64b3). Since B4 finished shards: G16, G16b, G16x, G18.
- G16b (DeepSeek, clean): B4B8 WALL reload-hardreg-across-call 2; C750 WALL cse-const-addr 4; 72B0 WALL sched1-birth-order 2.
- G16x: 4 MATCH (80149374, 801495C4, 8014964C, 80177F84). G18: 3 MATCH (8017F898, 8017F7CC, 801876C4), 2 WALL (8017D508 jump2-crossjump-arms, 80180610 sched1-load-delay-fill). All 7 win.c re-scored 0 by the expert (home TU).
- held.tsv: G16 G16x G18 added. Cookbook C0535 (do{}while(0) EBB split). walls.txt +4 tags. Queued briefs G18x..W50x carry PATHS, MOVES+, TRAP lines.

## In flight
- Nothing. No coder, no shell. Paused: no new coder, no bank until the developer resumes.

## Hypotheses rejected
- See logs/T11.progress.md, progress10-12.

## Current hypothesis
- DeepSeek healthy at 2 lanes (G16x/G18 ran together; refusals were judge catches of coder mistakes). Learning mode lifted after G16b.

## Next five steps
1. Bank the 7 unbanked matches (G16x 4, G18 3): barrier, in-house pa-coder from .run/P40/T11/bank_brief.txt, K=105, B=5 (header items: R22 checks all includers).
2. Next shards from .run/P40/T11/mm_queue_a9.txt: G18x G20 G20x G21 ... W50x; up to 4 lanes `PY tools/pa_ext.py run openrouter-deepseek/deepseek .run/P40/ext/T11.c<S>.md`.
3. Retry G16b func_801372B0 (sched1-birth-order) with C0535.
4. Per report: bin/sc.sh re-score MATCHes, bin/held_add.py deepseek <shard>, HEALTH, df -h; bank every 6-8 shards.
5. End: TSV wall causes, strict residue-unused 0, R22 gate, summary.

## Gotchas
- Bank gate wipes build/: barrier before every bank. Never wrap pa_ext.py run in timeout.
- mm_queue_a9.txt is one space-separated line (tr ' ' '\n' before sed).

## State to carry verbatim
- Next bank K=105, B=5. Unbanked: G16x (4 MATCH), G18 (3 MATCH). Queue next: G18x.
