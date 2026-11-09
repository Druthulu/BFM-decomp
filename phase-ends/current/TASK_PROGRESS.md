# TASK_PROGRESS — T1 attempt 1

Task: T1 phase-start baselines and environment check
Attempt: 1   Agent: pa-expert   Ctx at handoff: ~45k   Commit: bcd6a3f2a3 (HEAD the measurements belong to)
Reason: developer pause for a Claude Code restart (correction relayed by Claude), not the context threshold.

## Done so far
- HEAD at start d71070a6ad; src/ config/ include/ tools/ Makefile clean.
- R22 at d71070a6ad: 218 passed, 0 failed of 218, 232 s (.run/3.42/logs/t1_r22.log). Superseded by the run at bcd6a3f2a3.
- tools-health at d71070a6ad: FAIL only at tool_census --check, 2 corpus gaps (corpus copy of tools/plan_edit.py stale after the PA3 install; decomp-architect/corpus/record/phase-ends/PhaseEnd_Phase3.41.md missing). Every earlier gate in the run passed (type_census controls 4/4, ghidra_roster OK, ghidra_types OK, doc_links OK, kit_lint OK). Wall time 1099 s (.run/3.42/logs/t1_health.log).
- Fix: `make kit-corpus` (skill tools-edit-kit-corpus), then tool_census --check OK with 0 gaps; committed bcd6a3f2a3 "T1: refresh kit corpus ...".
- R22 at bcd6a3f2a3: 218 passed, 0 failed of 218, run alone, 282 s (.run/3.42/logs/t1_r22b.log).
- Trampolines (config/verbatim_manifest.json rows with `copies`): 22 PERMANENT-VERBATIM in-function rows. 20 have private_tus=133, binaries=141, distinct_h_exact=134, shared_header src/shared/ov/func_<addr>__<h8>.h. 2 (func_80128678, func_80155FF8) have private_tus=0, distinct_h_exact=1, header func_<addr>.h. The 20 + 2 split is confirmed. List: .run/3.42/t1/trampolines.txt (script .run/3.42/t1/scripts/tramp.py).
- Symbols (.run/3.42/t1/symbols.txt, script .run/3.42/t1/scripts/symcount.py; placeholder = name matching (func|D|jtbl|L|sym|jpt|lbl)_<6-8 hex>): 221 config/symbols*.txt files, 144 with entries; total 2,975 entries, 284 placeholders, 2,691 curated, 0 guess_. us.txt 1,082 entries / 2 placeholders / 1,080 curated / 0 guess_ (count header 1082 agrees); us.ram.txt 1/0/1/0.
- Ghidra proofs: proof inputs are unchanged since f4b1fbad3d. `git diff --stat f4b1fbad3d..HEAD -- tools/ghidra_rebuild.sh tools/ghidra_scripts config/ghidra config/symbols*.txt config/splat*.yaml` is empty. The one tools/ghidra_types.py change is SCRATCH (:42), which only gcc_compare (:638-657) uses, not merge (:540) that ghidra_rebuild.sh:118 calls. The other changes are tool_dictionary.tsv, a new tools/ghidra_mcp_call.py (not referenced by the rebuild scripts) and plan_edit.py. So the six proofs carry from f4b1fbad3d.
- Ghidra state (read-only, start of task): :8080 LISTEN on 127.0.0.1; pid 164224 analyzeHeadless .../ghidra bfm -process SLUS_007.26 -noanalysis; ghidra/bfm.lock present. Not touched.

## In flight
- nothing. `make tools-health` at bcd6a3f2a3 finished OK: tool_census --check 0 gaps, `HEALTH_WALL 1117s rc=0` (.run/3.42/logs/t1_health2.log). This also rewrote the same-vram census in .run/P35/census.

## Hypotheses rejected
- "tools-health at HEAD is green as at 3.41's close" — rejected: the PA3 install changed plan_edit.py after the last kit-corpus, and the 3.41 PhaseEnd was archived without its corpus record copy. Fixed in bcd6a3f2a3.

## Current hypothesis
src/ has not changed since f4b1fbad3d, so the cross-address bucket should equal R83 (3,801 / 30,347 / 11,340). If it differs, return `question` (plan note).

## Next 5 steps
1. tools-health is DONE (OK at bcd6a3f2a3, 1117 s). HEAD is now 9bf5b291dc, which adds only this note, so its gates stand.
2. `time .venv/bin/python tools/share_census.py --check --strict-macros --strict-text --scope same-vram` (default out .run/P35/census) via run.sh. Record S1 violations, deferred/pending text counts, unresolved names and the wall time.
3. The same with `--scope all --out-dir .run/3.42/t1/census`. Count the cross-address bucket from .run/3.42/t1/census/classes.jsonl with a scratch script: addrs>1, by verdict and by flag E/F, instances, copies. Check that every same_address_text_duplicates_deferred h is in a cross-address class.
4. `/usr/bin/python3 tools/lint_symbol_refs.py; echo rc=$?`. Time one `make check BINARY=ov_SC02_003 -j16`, `tools/gate_main.py` and `share_body.py --plan` (read the --help first; --plan should write nothing, so check git status after).
5. Write logs/T1.md and tasks/T1.md, run task_log.py finish T1, commit via commit_task.sh T1.

## Gotchas
- tools-health > 285 s: run it as a background Bash shell through run.sh; it worked that way twice here.
- Tracked .run/P35/census and .run/P36/agents files show modified after any tools-health: never pass them to commit_task.sh.
- Never stop the Ghidra process (R49).

## State to carry verbatim
- HEAD bcd6a3f2a3; R22 `check-all: 218 passed, 0 failed of 218` 282 s at it.
- Wall times so far: clean R22 232 s / 282 s; tools-health 1117 s OK (1099 s on the failed run).
- Deviations to log: tools-health red at d71070a6ad (2 corpus gaps), fixed with make kit-corpus in bcd6a3f2a3, then R22 re-run there. Developer pause (relayed by Claude) after R22b: note written, the in-hand tools-health let finish, nothing new started.

## Coder runs so far
- none (coder: none)

## Reports commissioned
- none
