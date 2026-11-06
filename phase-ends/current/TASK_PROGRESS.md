# TASK_PROGRESS — T11 attempt 15 (PAUSED by developer correction: Claude Code restart)

## Done so far
- B5..B10 banked: f874a03298 (7), eb321206e5 (23), 2bcf006238 (11), 3ae88a2c3f (25), 606aa305f8 (21), 5b1a50b1e4 (9). Strict after B10: residue 1892, unused 0. R22 218/218 each bank.
- Since B10: W48x 3/3 WALL (held_add done; new tag global-expand-pref in walls.txt). Unbanked MATCH: 0.
- W49 refused exit 4: learning mode (O05x friction; W48x had 1 denial + 1 read-guard, so it stays armed).

## In flight
- Nothing. No coder, no shell.

## Hypotheses rejected
- See logs/T11.progress.md (a14, a15 sections).

## Current hypothesis
- DeepSeek cracks ~55 % per item; learning mode re-arms on any friction; runs 1-4 lanes.

## Next five steps
1. Queue: W49 W49x W50 W50x (`PY tools/pa_ext.py run openrouter-deepseek/deepseek .run/P40/ext/T11.c<S>.md > .run/P40/T11/ext/run_<S>.out 2>&1`, Bash run_in_background). One lane until a clean report, then up to 4.
2. Per report: bin/chk.sh <S>, held_add.py deepseek <S>, new tags to walls.txt, HEALTH.
3. Bank B11 (K=111) on an in-house pa-coder from bank_B10.txt (sed shards/ids, new NOTE), no ext lane during it.
4. RM3 retry of kept kinds < 30 tries: G23 func_80183534 func_801919A0 func_80191C50 func_8019059C (pin); G31x func_8017E050 func_8017E6BC (barrier,pin); G31y func_80177EA4 (launder, TSV wall `retry-kept` placeholder).
5. End: TSV wall causes (no `retry-kept`), parked families recorded, strict residue-unused 0, R22 gate, summary with before/after per kind and cause.

## Gotchas
- Bank gate wipes build/: no ext lane during a bank. Never wrap pa_ext.py run in timeout. Launch ext with Bash run_in_background.
- Check each NOTE claim about extra dropped rows against the TSV (B10: func_801888F4 kept its pin row).
- `// !FAKE: do-while` fences counted as cracks (C0535); flag for T19 in the summary.

## State to carry verbatim
- Next bank K=111, B=11. Unbanked: none. Queue next: W49 (one lane, learning mode).
