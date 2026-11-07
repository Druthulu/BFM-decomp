# TASK_PROGRESS — T9 attempt 1

Task: T9 head-class lever cracks with propagation
Attempt: 1   Agent: pa-expert   Commit: 9802994a6e (last green on HEAD)

Why a handoff: the harness forced the report while coder T9.c16 (batch-3 propagation) was still running with uncommitted src edits. Nothing of mine is mid-way; c16 owns its edits and commits them itself when green.

## Done so far
- 38 head classes listed: .run/P40/T9/classes.tsv (1059 rows at start; plan's 1,066 was pre-T8).
- Every class has had at least one crack attempt (crack coders c1-c7, c9-c12, c14, c15, c17; developer cap 4 concurrent respected). Full timeline: phase-ends/current/logs/T9.md.
- Banked + R22 218/218 + committed:
  - T9.c8 f778715179: func_80178970 (6871f73f03cc 127, 95b3e1891574 7) + func_8013F350 (681be4580c7c 130, 5fd67803a96b 3, plus 133 pin rows under other tags): -400 rows, 267 copies.
  - T9.c13 c3675123ba: 5deb6e94a9dc 10, 0b864874586c 6, 7e3ee6323e7b 2, ed9510f54cd6 2, c5888e601970 3, 45b3d1689667 2: -25 rows, 20 copies; 9 names extern void->s32 in 26 files.
  - Residue after c13: 1617 data rows.

## In flight
- T9.c16 (pa-coder, label t9_p3, log phase-ends/current/logs/T9.c16.md when done): banking 69ec29dcfad0 func_8012E364 (133 copies, `s16 d`), 2cf1053e2d37 func_80189AF4, 0de7baa6ab5d func_8018A70C, 24ef6021da45 func_80184238, 09f0668ec77d func_8016A290, 60d5fc98df19 func_80166690, a88fd15989e7 func_80180200 + db4e4996d215 func_8018084C (W4 union struct return; revert that pair only if callers break). At handoff, src/ had many ` M` files (its edits), no commit yet. Check `git log --oneline | grep T9.c16`; if absent and no coder alive, its edits are orphaned: re-run the bank from the win.c files (paths in logs/T9.md), never commit unverified src.

## Hypotheses rejected (no clean crack; rows stay, attempts = instrument)
- 125a1f54cf5d func_80140958 (258 rows): c1+c9 ~1h40, best.c score 1 (insn 143 andi vs move; k=(u16)m cost); no zero-code label survives jump.c:243; no a2-preferring pseudo. Lead c9_K7c1.c score 2.
- 03930f4cac61 func_8013CF68 (134): c2+c17 ~2h40, IRREDUCIBLE-ALIAS: base known to cse (find_best_addr cse.c:2622) and sched (sched.c:418-438); even do-nothing re-set f2 is 6 mism. Clean best h2.c 10.
- 4c2cba101bf4 func_80181D1C (12): c7+c15, best 12 mism (v/h6.c).
- e968e8ba46b1 func_80175AB8 (6): 149 (cse1 folds base-relative loads).
- 39b8abf21cfe 45, 98903885f4ac 45, c1558b7739b7 22, 080c5228b69f 22, 1e4309f46812 21, 0062bb6a8852 4, c25ba3fa99af 27, 475c7780b312 2 (v/k2.c), 413fa955ff17 265, e95409c6da8b 6, eb3ad84974a4 4, 26f44577f418 18.
- Lever-only matches (do-nothing statement; not counted): 0438fbf5646f func_80180324 (always-false flip-bit branches), 9d523cda5f82 func_80145934 (identity address), 26f44577f418 (lever reaches 2 only).
- 7a079af353ad (func_80140958 ov_MAIN_012 variant, 6 rows): follows 125a1f54cf5d, uncracked.

## Open decision (for the developer, via Claude)
- 4a789ceca27f func_80177B5C (133 rows): MATCH via `w = (w >> 16 << 16) | x1;` after `w = c0 | x1;` (.run/P40/T9/func_80177B5C/win.c), a semantic identity combine folds; it plays the launder's role (reg_n_sets 2 -> no birthing boost). Recommendation: do not count it as lever-free (it is a C-spelled launder); if the developer accepts it, bank it like c8 and drop 133 rows.

## Next 5 steps
1. Wait for / verify T9.c16's commit (R22 218/218, lever_census --strict --residue OK, residue-unused 0).
2. If 80177B5C is accepted, one more propagation coder (label t9_p4).
3. Rewrite the summary phase-ends/current/tasks/T9.md from templates/task.template.md: rows cleared per class, agent-hours (sum of coder wall times in logs/T9.md, ~20 h total), cookbook candidates below.
4. Run the full verify line; `PY tools/task_log.py finish T9`; `bash tools/commit_task.sh T9 "<line>"`.
5. Return done (or question on 80177B5C).

## Gotchas
- harness: delever_permute lane 1 dead for every head exemplar (cpp -P draft + match_one prelude -> struct redefinition; UNCALIBRATED). tools/ fix, out of T9 files.
- harness: delever --propagate keys on the chain's first LEVER-FREE ledger row, refuses siblings; workaround .run/P40/T9/c13/remap.py.
- harness: lever_census --write-residue drops line-1 comment; restore it.
- ov_SC03_015 calibration recipe points at missing src/ov_SC03_014/ov_SC03_014_jr_80184440.c (T8.c4 carve).
- commit_task.sh auto-stages logs/ incl. T9.md mid-task.
- match_one on a matched fn needs --asm-subdir (targets via tools/verbatim_target_s.py).

## State to carry verbatim
- generalizable (cookbook candidates): 16-bit result var removes sched1 birthing boost + local-alloc tie (8012E364); reuse a later local as derived pointer keeps head set through cse1 (8013F350); call in && test with constant returns (80178970); short loop counters drop `+ 0` copies and pins (8016A290, 80166690); real s32 return instead of keepalive (80187F4C, 80182000, 80187A50).

## Coder runs so far
- c1 c9 80140958 blocked · c2 c17 8013CF68 blocked · c3 80177B5C lever-match · c4 blocked, c14 MATCH 8012E364 · c5 MATCH 8013F350 · c6 MATCH 80178970 · c7 c10 c11 c12 small groups · c15 near-miss retries · c8 c13 c16 propagators (logs/T9.c8.md, T9.c13.md, T9.c16.md)

## Reports commissioned
- none
