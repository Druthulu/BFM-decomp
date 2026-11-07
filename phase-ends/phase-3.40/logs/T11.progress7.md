# TASK_PROGRESS — T11 attempt 7

Paused at the developer's request (correction 12: Claude Code restart + PA3 update), not a context handoff. No coder running; nothing uncommitted in src/ or config/; no patch. Banks unchanged since B2 492caaa885.

Task: T11 singleton crack wave
Attempt: 7   Agent: pa-expert   Commit: this file (HEAD before it a12835ed76)

## Done so far
- Routing (card + correction 8): crack shards on openrouter-minimax/minimax via `PY tools/pa_ext.py run openrouter-minimax/minimax .run/P40/ext/T11.c<S>.md`, ≤ 4 at once; banking in-house Opus (bank_brief.txt). Brief CODER line opus55 overridden (Deviation).
- Shard state (rows in .run/P40/T11/<S>/results.tsv; every MATCH re-scored 0 by me with bin/sc.sh, no new lever text; pre-existing pins under other causes stay):
  - G05 complete: 2 MATCH (func_8018219C, func_8017E5C4); its 7 shallow walls moved to RM1.
  - G06 complete 9/9: 4 MATCH (func_8017CE7C, func_8017E204, func_80182F44, func_8017EEB0), 5 WALL (48-125 tries, held).
  - G07 complete 10/10: 3 bankable MATCH (func_8012944C header item, G07r says 141/141 includers 0; func_8003DF8C; func_80181E64) + 2 MATCH-NEEDS-DECL (func_8012EF34, func_8012EF70: need shared-header proto void→s32, held, not bankable), 5 WALL held.
  - G08: 2 MATCH (func_801580B4, func_801581AC), 2 WALL held; its 5 shallow walls moved to G08b.
  - G08b (retry) PARTIAL: func_8014C308 WALL cse-const-fold (36 tries, held); func_8014FD54 IN PROGRESS → handoff in G08b/func_8014FD54__func_8014FD54/notes.md + logs/T11.cG08b.md; func_801536DC, func_8017849C, func_8018655C not started.
  - G10 complete: 3 MATCH (func_801627E8, func_80180D54, func_801815D4); 4 shallow walls moved to RM2.
  - G11 complete: 2 MATCH (func_8018AA98, func_80181CF4); 6 shallow walls moved to RM2.
  - G14 10/11: 6 MATCH (func_8018656C, func_8017D73C, func_8017D9D8, func_8017EF0C, func_801813B0, func_8018CDEC), 4 WALL held; func_80191020 IN PROGRESS → handoff in logs/T11.cG14.md (best 2), no row.
  - G15 2/7: 2 MATCH (func_8018A180, func_8017FE9C; §373 dead-reset / dead copy moves); items 3-7 not started (logs/T11.cG15.md).
- Unbanked bankable MATCHes on disk: 24 fns (G05 2, G06 4, G07 3, G08 2, G10 3, G11 2, G14 6, G15 2).
- held.tsv: 54 data rows = haiku 25, deepseek 9, minimax 20 (WALL 17, MATCH-NEEDS-DECL 2, RUN-FAILED 1 = old G06 run).
- MiniMax rate (all attempts, 64 items finished incl. the 17 shallow walls moved to retries): 26 MATCH (24 clean + 2 decl-dependent) = 41 % (38 % clean). Attempt 7 alone: G06r/G07r/G08r/G10r/G11/G14/G15/G08b.

## In flight
- Nothing running. In-progress items with handoffs: G08b func_8014FD54, G14 func_80191020. Not started: G08b items 3-5, G15 items 3-7, RM1, RM2, queue.

## Hypotheses rejected
- MiniMax WALLs are full attempts — rejected: G05/G08/G10/G11 walls had 1-13 scored tries (G08r did 7 items in 46 min); G08b's retry of func_8014C308 lowered best 17→4.

## Current hypothesis
MiniMax cracks ~40 % when it spends the budget; walls cluster on cse copy/const folds and local-alloc order. The added "≥ 20 min and ≥ 30 tries per WALL" rule is what makes a WALL count as attempted.

## Next 5 steps
1. Resume, ≤ 4 at once: G08b (`pa_ext.py run … T11.cG08b.md` again: rows-present items skipped; func_8014FD54 resumes from its notes.md), G14 (re-run T11.cG14.md: only func_80191020 left; point it at its handoff in logs/T11.cG14.md), G15 (T11.cG15.md; items 3-7), RM1, RM2, then queue .run/P40/T11/mm_queue_a7.txt (G16 G18 G20-G31 O01-O05 W47-W50). G14/G15 briefs predate the ≥30-tries line: add it (sed as in log) before re-running.
2. After each shard: verify MATCHes (bin/sc.sh <itemdir> <itemdir>/win.c), `bin/held_add.py minimax <S>`, shallow walls (tries < 30) → `bin/retry_shard.py <new> <S>:<func>…`.
3. Bank B3 now-ish (24 fns waiting) at a barrier (no shard running: scorer reads build/): bank_brief.txt with K=103, B=3, MATCH rows only; NEEDS-DECL excluded; held rows not rewritten.
4. Ask nothing of the developer; held.tsv carries the held list for Claude.
5. End: TSV rewritten, strict residue-unused 0, R22 gate, summary with Opus/Haiku/DeepSeek/MiniMax rows.

## Gotchas
- harness: pa_ext.py nudges on a final message not starting done|question|blocked; briefs demand the bare word.
- harness: MiniMax has no compaction; long shards die "Prompt is too long" (old G06 at 55 turns).
- EXT-HEALTH seen: rm denied to external coders (G15 left .run/P32/t4e/dumps_g15_030, deleted by me; G08b used tools/run_cleanup.py); bash/python3 with .run/ relative or absolute script paths denied 15-26×/shard; bwrap failures re-run.
- Scorer reads build/: no bank gate while a shard runs. Disk 26 GB free at 17:34.
- §373 dead-reset / dead copy moves are accepted cracks (project technique), identity launders are not.

## State to carry verbatim
- Ext briefs: .run/P40/ext/T11.c<S>.md; retry briefs T11.cG08b.md, T11.cRM1.md, T11.cRM2.md (template: G08b brief + "Retry: read notes.md first").
- Queue: .run/P40/T11/mm_queue_a7.txt. Next bank: K=103, B=3.

## Coder runs so far
- attempt 1: c01-c07, cH1, cG01-cG04, cG09, cG17, c101, c102 (logs/T11.progress1.md)
- attempt 5: cG05 cG06 cG07 cG08 cG10 (MiniMax)
- attempt 7: cG06r cG07r cG08r cG10r cG11 cG14 cG15 cG08b (MiniMax) — logs/T11.c<S>.md

## Reports commissioned
- R3.40-013 — T10 cracking recipe and helpers
