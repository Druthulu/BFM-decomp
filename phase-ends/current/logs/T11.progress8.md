# TASK_PROGRESS — T11 attempt 8

Paused at the developer's request (correction 13: restart/update), not a context handoff. No coder running; nothing uncommitted in src/ or config/; no patch. Banks unchanged since B2 492caaa885.

Task: T11 singleton crack wave
Attempt: 8   Agent: pa-expert   Commit: this file

## Done so far
- Attempt 8 learning-mode test: one MiniMax coder (T11.cG08c, G08b's 4 left) ran clean: judge allowed 75 / refused 0, 7 rules learned, 1 denial. 0 MATCH, 4 full WALLs (44-135 tries). G08b complete 5/5, 0 MATCH. Review in logs/T11.md "Attempt 8".
- Shard state (rows in .run/P40/T11/<S>/results.tsv; every MATCH re-scored 0 by an expert with bin/sc.sh):
  - complete: G05 (2 MATCH), G06 (4), G07 (3 bankable + 2 MATCH-NEEDS-DECL held), G08 (2), G08b (0), G10 (3), G11 (2).
  - G14 10/11: 6 MATCH; func_80191020 in progress (best 2, handoff logs/T11.cG14.md) → brief T11.cG14b.md.
  - G15 2/7: 2 MATCH; items 3-7 → brief T11.cG15b.md.
- Unbanked bankable MATCHes on disk: 24 fns (G05 2, G06 4, G07 3, G08 2, G10 3, G11 2, G14 6, G15 2). NEEDS-DECL (func_8012EF34, func_8012EF70) held, not bankable.
- held.tsv: 58 data rows = haiku 25, deepseek 9, minimax 24 (WALL 21, MATCH-NEEDS-DECL 2, RUN-FAILED 1).
- MiniMax rate: 68 items finished, 26 MATCH (24 clean + 2 decl-dependent) = 38 % (35 % clean).

## In flight
- Nothing running.

## Remaining batches (≈ 219 fns)
G14b 1 · G15b 5 · RM1 7 · RM2 10 · then queue .run/P40/T11/mm_queue_a7.txt: G16 8, G18 10, G20 7, G21 10, G22 9, G23 9, G24 7, G25 6, G26 9, G27 8, G28 12, G29 4, G30 8, G31 12, O01-O04 10 each, O05 9, W47-W50 7 each. Plus RM3 (G07 shallow walls) if any tries < 30 there (check G07 rows).

## Hypotheses rejected
- MiniMax WALLs are full attempts (rejected attempt 7; fixed by the ≥ 30-tries rule — G08c obeyed it, all 4 walls 44-135 tries).

## Current hypothesis
MiniMax cracks ~35-40 % when it spends the budget; walls cluster on global/local-alloc register choice and cse const folds.

## Scale-up plan (next 5 steps)
1. At resume, barrier (no shard running: the scorer reads build/): bank B3 = the 24 MATCHes via an in-house Opus coder (.run/P40/T11/bank_brief.txt, K=103, B=3, MATCH rows only, NEEDS-DECL excluded, held rows untouched); R22-green commit.
2. Then 4 MiniMax lanes (`PY tools/pa_ext.py run openrouter-minimax/minimax .run/P40/ext/T11.c<S>.md`): G14b, G15b, RM1, RM2 first; next from the queue as each reports. All 27 remaining briefs carry FRESH (regenerate stale orig.c), PERMISSIONS (judge; log refused under Friction), REMINDER (bare first word). Learning mode is clean, so 4 at once is allowed.
3. Shards of 10-12 items: MiniMax has no compaction (G08c used 136 turns for 4 items; old G06 died "Prompt is too long"). Consider splitting ≥ 10-item shards into halves with bin/retry_shard.py before starting.
4. After each shard: re-score MATCHes (bin/sc.sh <itemdir> <itemdir>/win.c), `bin/held_add.py minimax <S>`, tries < 30 walls → retry shard; review HEALTH; bank every 6-8 finished batches.
5. End: TSV rewritten with wall causes (walls.txt tags), strict residue-unused 0, R22 gate, summary with Opus/Haiku/DeepSeek/MiniMax rows; held list for the developer.

## Gotchas
- harness: pa_ext.py nudges on a final message not starting done|question|blocked; briefs demand the bare word.
- harness: MiniMax has no compaction; long shards may die "Prompt is too long".
- Scratch orig.c goes stale once a bank moves src: FRESH line in every brief (G08c finding).
- Scorer reads build/: no bank gate while a shard runs. Disk 26 GB free (attempt 8 start).
- §373 dead-reset / dead copy moves are accepted cracks; identity launders are not.

## State to carry verbatim
- Ext briefs: .run/P40/ext/T11.c<S>.md (resume labels T11.cG14b.md, T11.cG15b.md). Queue .run/P40/T11/mm_queue_a7.txt. Next bank: K=103, B=3.
- Judge-learned rules (G08c): dt.sh, sc.sh, objdump, mipsel-linux-gnu-objdump, alloc_table.py, diff, delever_search.py.

## Coder runs so far
- attempt 1: c01-c07, cH1, cG01-cG04, cG09, cG17, c101, c102 (logs/T11.progress1.md)
- attempt 5: cG05 cG06 cG07 cG08 cG10 (MiniMax)
- attempt 7: cG06r cG07r cG08r cG10r cG11 cG14 cG15 cG08b (MiniMax)
- attempt 8: cG08c (MiniMax, learning mode) — logs/T11.cG08c.md

## Reports commissioned
- R3.40-013 — T10 cracking recipe and helpers
