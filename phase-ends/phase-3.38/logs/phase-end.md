# Phase 3.38 close — log (closing expert)

- Read: card slice expert; plan header, Context, Rationale, Changes; tasks/T1..T10 (+T5, T5.1); AUDIT.md.
- `PY tools/phaseend_index.py verify --verbose` (run.sh --bg pe_verify) → GREEN 1/1; clause log .run/logs/verify1.log: extract-all 217/0/217, check-all 218/0/218 at 78515137ab.
- `.venv/bin/python tools/type_census.py --check-structs` (run.sh census_cs) → exit 0; gating counts all 0, controls 4/4; non-gating conflicting_types=18 tu_conflict=0 types_floor_lying=229 twins_listed=53 dead_kept=3 block_frames=629. Regenerated tracked outputs: .run/P37/census/{struct_map_top.json,type_census.json,type_census.txt}, docs/struct-map.md (stamp).
- `PY tools/task_log.py gotchas` → 51 tagged lines in 11 summaries.
- generalizable: T1-T6 + T5.1 already promoted by T7 (C0511-C0513; C0512 holds the fold-sdk line). New: T8:20 + T10:24 → cookbook C0514.
- workflow: T4:26 + T6:26 → skill restruct-cycle-watch; T1:34 → retire-doc-consumers; T5.1:33 → commit-task-autostage (HOW_WE_WORK.md ## Skills lines written by skill_add).
- binding: T5.1 tier-2 rule → rules R122; T5/T5.1 contracts → docs/struct-map-decisions.md `## Long-tail rules` (my one edit, 6 lines); others already in their docs (RECAP Decisions).
- H7: misses T2, T3, T5, T6, T10 → RECAP Deviations.
- Carry audit: `~/.claude/pa3/pa_ledger.py audit --phase 3.38 --md` (run.sh carry_audit) → section produced; tables copied to RECAP `## Audit` without cost lines.
- harness: `phaseend_index.py assemble --help` does not say that assemble generates the carry audit and Agent runs; learned from a grep of the module docstring.
- No retrievers, no coders.
