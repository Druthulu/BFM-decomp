# TASK_PROGRESS — T11 attempt 12 (paused for developer restart, PA3 update)

## Done so far
- B4 banked (926e7a64b3). Since B4: 0 matches, nothing to bank.
- a12: T11.cG16 on openrouter-deepseek/deepseek: func_8012C2D0 WALL cse-const-addr best 1 (row written); cookbook C0534; log logs/T11.cG16.md.

## In flight
- Nothing. No coder, no shell.

## Hypotheses rejected
- See logs/T11.progress.md and progress10/11.

## Current hypothesis
- DeepSeek works the briefs as written (honoured a mid-run `say`); still in learning mode (1 refusal: `$d/../../bin` path), so 1 lane.

## Next five steps
1. `PY tools/pa_ext.py run openrouter-deepseek/deepseek .run/P40/ext/T11.cG16b.md` (background; G16 remainder: B4B8 from best 19, C750, 72B0).
2. On report: re-score MATCHes (bin/sc.sh), bin/held_add.py for walls, read HEALTH, bank moves/cookbook, df -h.
3. Next shard from .run/P40/T11/mm_queue_a9.txt: G16x G18 G18x ... W50x (briefs in .run/P40/ext/); one lane until a clean run, then up to the developer's 4.
4. Bank every 6-8 finished shards: barrier, in-house pa-coder from bank_brief.txt, K=105, B=5.
5. End: TSV wall causes, strict residue-unused 0, R22 gate, summary.

## Gotchas
- Learning mode refuses a second start (exit 4). Never wrap pa_ext.py run in timeout.
- Bank gate wipes build/: barrier before every bank.
- Briefs should call helpers by project-relative path; `$d/../..` is refused by the judge (added to cG16b brief; consider for later briefs).

## State to carry verbatim
- Next bank K=105, B=5. Queue .run/P40/T11/mm_queue_a9.txt; done: G14b G15b RM1 RM1x RM2 RM2x G16(partial). Next: G16b then G16x.
