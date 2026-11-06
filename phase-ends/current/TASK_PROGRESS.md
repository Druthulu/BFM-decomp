# TASK_PROGRESS — T11 attempt 14 (PAUSED by developer correction: Claude Code restart)

## Done so far
- B5..B9 banked: f874a03298 (7), eb321206e5 (23), 2bcf006238 (11), 3ae88a2c3f (25), 606aa305f8 (21). Strict after B9: residue 1913, unused 0. R22 218/218 each bank.
- Since B9 finished (unbanked): O05x (1 MATCH, 3 WALL), W47 (3 MATCH, 1 WALL), W47x (2 MATCH, 1 WALL), W48 (3 MATCH, 1 WALL). 9 MATCH re-scored 0 by the expert. held_add done for all four.
- walls.txt has every tag used so far. bin/chk.sh = expert check (rows, re-score, lever diff orig->win).
- Briefs W48x..W50x carry NOSRC (gcc sources at tools/reference/gcc-2.7.2/), grep-moves.md, PARTIAL-definition lines.

## In flight
- Nothing. No coder, no shell.

## Hypotheses rejected
- See logs/T11.progress.md (a14 section).

## Current hypothesis
- DeepSeek cracks ~55 % per item; learning mode re-arms on any friction (/tmp writes, read-guard on moves.md); runs 1-4 lanes.

## Next five steps
1. Bank B10: shards O05x W47 W47x W48 (9 MATCH, 0 PARTIAL, 6 WALL; W47 func_801888F4 also drops 3 other-kind pin rows). In-house pa-coder from .run/P40/T11/bank_brief.txt, K=110, B=10, NOTE like bank_B9.txt.
2. Remaining shards: W48x W49 W49x W50 W50x (`PY tools/pa_ext.py run openrouter-deepseek/deepseek .run/P40/ext/T11.c<S>.md`, background; up to 4 lanes; exit 4 = learning mode, restart after a clean report).
3. RM3 retry of kept kinds with < 30 tries: G23 func_80183534 func_801919A0 func_80191C50 func_8019059C (pin); G31x func_8017E050 func_8017E6BC (barrier,pin); G31y func_80177EA4 (launder, wall `retry-kept` placeholder in TSV).
4. Per report: bin/chk.sh <S>, held_add.py deepseek <S>, new tags to walls.txt, HEALTH.
5. End: TSV wall causes (no `retry-kept`), parked families recorded, strict residue-unused 0, R22 gate, summary with before/after per kind and cause.

## Gotchas
- Bank gate wipes build/: no ext lane during a bank. Never wrap pa_ext.py run in timeout. Launch ext with Bash run_in_background (not nohup).
- PARTIAL kept-kind rows: instrument `delever_search --try partial keeps <kind> (<n> tries)` (bank_rows.py writes best 0/n: fix).
- `// !FAKE: do-while` fences (incl. empty ones) counted as cracks per the brief (C0535); flag for T19 in the summary.

## State to carry verbatim
- Next bank K=110, B=10. Unbanked: O05x W47 W47x W48 (9 MATCH). Queue next: W48x.
