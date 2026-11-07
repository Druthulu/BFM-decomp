# TASK_PROGRESS — T11 attempt 9

Task: T11 singleton crack wave · Agent: pa-expert · prior notes: logs/T11.progress1/4/5/7/8.md

## Done so far
- a9 start: archived progress8 (06c711dc89). G07 func_8012EF34/EF70 rows set result HELD-DECL wall decl-change (bank_rows → WALL rows).
- All unstarted shards split to ≤ 5 items by bin/split_shard.py (S keeps chunk 1, S+x/y/z the rest, briefs derived). Queue .run/P40/T11/mm_queue_a9.txt (53 shards).
- No shallow (< 30 tries) MiniMax walls: RM3 not needed. Shallow walls in G01-G04/G09/G17 are haiku/deepseek, on held.tsv.

## In flight
- DONE c103 bank B3 → 1c6bb7445f: 24 banked, 23 rows walled (incl 2 HELD-DECL), dropped residue-unused ov_SC01_077_jr_8015C32C.c func_801627E8 pin; strict residue 2102 unused 0 OK; gate 218/218; BANKING removed. Was: T11.c103 (pa-coder, in-house) bank B3: G05 G06 G07 G08 G08b G10 G11 G14 G15, 24 MATCH. Brief .run/P40/T11/bank_B3.txt. No ext shard may run until it reports (make clean wipes build/).

## Hypotheses rejected
- MiniMax walls shallow: fixed by ≥ 30-tries rule (a7/a8).

## Current hypothesis
MiniMax cracks ~35-40 % when it spends the budget.

## Next 5 steps
1. c103 done (1c6bb7445f); skip.
2. Start 4 MiniMax: G14b G15b RM1 RM1x (`PY tools/pa_ext.py run openrouter-minimax/minimax .run/P40/ext/T11.c<S>.md`, background shells).
3. Ramp +2 per healthy round to ≤ 10; on first 429/rate-limit/stall: stop adding, resume failed (`run --resume T11.c<S>`), settle 1-2 below. Log level + evidence here.
4. After each shard: re-score MATCHes (bin/sc.sh), `bin/held_add.py minimax <S>`, read HEALTH; df -h / > 10 GB.
5. Bank every 6-8 finished shards: barrier (no shard running), in-house pa-coder from bank_brief.txt, K=104.., B=4..

## Gotchas
- harness: restruct `--rung S --residue --only` takes function names, not segment names (segment names match 0 rows; c103). bank_swap.py: orig.c optional now; --restore for no-orig items comes from git.
- Bank gate wipes build/: barrier before every bank.
- MiniMax no compaction: ≤ 5 items per shard.

## State to carry verbatim
- Next bank: K=104, B=4 (after c103). Ramp level: 0 (not started). c103 landed green (1c6bb7445f); start the ramp directly.

## Coder runs so far
- a1-a8: see logs/T11.progress8.md. a9: c103 (bank B3).

## Reports commissioned
- R3.40-013
