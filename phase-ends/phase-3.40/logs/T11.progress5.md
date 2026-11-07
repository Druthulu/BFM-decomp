# TASK_PROGRESS — T11 attempt 5

Paused at the developer's request (correction 9: Claude Code restart for an external-coder update), not a context handoff. No coder running; nothing uncommitted in src/ or config/; no patch.

Task: T11 singleton crack wave
Attempt: 5   Agent: pa-expert   Commit: this file (banks unchanged since B2 492caaa885)

## Done so far
- Pause note 1a0eea2f4b read; attempt-4 digest archived → logs/T11.progress4.md (3b195bc1c4).
- Routing per correction 8 (2026-10-21): crack shards on external openrouter-minimax/minimax (`PY tools/pa_ext.py run openrouter-minimax/minimax .run/P40/ext/T11.c<S>.md`), ≤ 4 at once; no Haiku/Opus crack coders, no escalation; banking in-house Opus via bank_brief.txt every 6-8 shards.
- Old ext lane retired (process gone); `.run/P40/T11/BANKING` removed; its 9 DeepSeek rows kept (ext/lane.tsv) and listed in held.tsv.
- `.run/P40/T11/held.tsv` (header + 48 rows): haiku 25 (B2 18 + WH1 5 WALL 2 PARTIAL), deepseek 9, minimax 14 (WALL 11, MATCH-NEEDS-DECL 2, RUN-FAILED 1). Helpers `bin/held_seed.py`, `bin/held_add.py <model> <shard>…` (skips rows already present).
- MiniMax shards this attempt (started 14:11, last back 16:38), every MATCH re-scored 0 by me with no `__asm__`/`register`:
  - G05 complete 9/9: 2 MATCH (func_8018219C, func_8017E5C4), 7 WALL (cse-copy-merge 5, lreg-v0-local-first 2). 203 turns, 26.4M tok, 44 min.
  - G06 4/9 then RUN-FAILED (exit 3 "Prompt is too long", unrecognized_model, 55 turns 46.6M tok): 3 MATCH (func_8017CE7C, func_8017E204, func_80182F44), 1 WALL cse2-pre-fold best 1.
  - G07 3/10 (paused): func_8012EF34 + func_8012EF70 MATCH only with the shared-header prototype void→s32 (1294 TUs declare void, 5 s32) — forbidden by the brief's no-decl-change rule → held as MATCH-NEEDS-DECL, not bankable until the developer rules; func_800D02D0 WALL lreg-qty-order best 8. func_801415C0 started after the pause by mistake (launcher nudge), scratch deleted, no row.
  - G08 2/9 (paused): func_80145C54 WALL cse-copy-merge best 6; func_801468C8 WALL sched1-order best 2.
  - G10 1/7 (paused): func_801627E8 MATCH.
- MiniMax rate so far: 19 items finished, 7 clean MATCH (37 %), +2 decl-dependent (47 % if the developer allows them). $0 (free tier). Tokens 175M over 641 turns.

## In flight
- Nothing. Unbanked wins on disk (G05 2, G06 3, G10 1 = 6 fns) wait for the next bank.

## Hypotheses rejected
- (none new)

## Current hypothesis
MiniMax cracks about a third of items; its walls cluster on cse-copy-merge and local-alloc ties, like Haiku's. Long shards overflow its context (G06): shorter shards (≤ 5 items) or one resume per shard may avoid RUN-FAILED.

## Next 5 steps
1. Resume shards G06 G07 G08 G10 (items without a results row are skipped by the brief), then the queue `.run/P40/T11/mm_queue.txt` from G11 on (G05 done), ≤ 4 at once; after each, `held_add.py minimax <S>`, re-score MATCHes, append to coder_usage.tsv and the log.
2. Every external brief must end with: final message starts with the bare word done|question|blocked (launcher nudge gotcha).
3. Bank after 6-8 finished shards (barrier: no crack shard running): bank_brief.txt with K=103, B=3, shards' MATCH rows only; MATCH-NEEDS-DECL rows excluded; held rows are not rewritten as survivors.
4. Ask nothing of the developer; held.tsv carries the held list for Claude to present.
5. At the end: TSV rewritten, strict residue-unused 0, R22 gate, summary with Opus / Haiku / DeepSeek / MiniMax rows.

## Gotchas
- harness: `tools/pa_ext.py:789` nudges "Go on with the task" when a coder's final message does not begin with done/question/blocked; a paused coder reads it as a go (G07).
- harness: MiniMax via pa_ext has no compaction ("unrecognized_model"); a long shard dies with "Prompt is too long" (G06 at 55 turns).
- Scorer reads build/: no bank gate (make clean) while any crack shard runs.
- Disk: 26 GB free at start; keep the disk rule in briefs.

## State to carry verbatim
- Ext briefs: `.run/P40/ext/T11.c<S>.md` (31: 27 shards + W47-W50 cloned from brief_G05; MiniMax attempts all 28 W47-W50 items incl. the 9 DeepSeek walls, for the comparison).
- Labels T11.cG05..; resume of a cut run: `PY tools/pa_ext.py run --resume T11.c<S>`.
- Shards done/partial: G05 full; G06 4/9, G07 3/10, G08 2/9, G10 1/7. Not started: G11 G14 G15 G16 G18 G20 G21 G22 G23 G24 G25 G26 G27 G28 G29 G30 G31 O01-O05 W47-W50.
- Next bank: K=103, B=3.

## Coder runs so far
- attempt 1: c01-c07, cH1, cG01-cG04, cG09, cG17, c101, c102 (see logs/T11.progress1.md)
- attempt 5: cG05 cG06 cG07 cG08 cG10 (MiniMax, external) — logs/T11.cG<nn>.md

## Reports commissioned
- R3.40-013 — T10 cracking recipe and helpers
