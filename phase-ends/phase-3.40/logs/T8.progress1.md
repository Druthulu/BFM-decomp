# T8 progress (attempt 1, expert handed back on a harness enforce while T8.c3 still ran)
## Done
- Before (strict, HEAD 2d92eae311): pins 1689, asm 1392, gte-levers 91, per-TU asm macro defs 164 {launder 154, instruction 9, barrier 1}, residue rows 2269 (sites 3336), residue-unused 0. Logs .run/logs/t8_strict_before*, t8_strict_res_before*.
- Plan figures 808/205 are stale: live TSV had left-by-author 543, not-judged 198 (157 asm-macro, 3 gte, 38 other).
- T8.c1 (logs/T8.c1.md; commits 60f9dee83b 28ed26b9e1 b94d9ae080 7bd4b80e5c 82d9a6eefc): all 581 target rows (598 sites: pin 155, launder 280, keepalive 144, barrier 16, instruction 3) re-judged rung A then B, labels t8_rj0..4; 0 removed, all NEEDED/DIFFERS. Spot-checked ledger (t8_rj2 func_80177B5C B RESIDUE launder NEEDED DIFFERS; 440 t8_rj rows). Reconciles the 3.39 T8 claim: the "left by the author" pins were never removal-tested until now; they are all NEEDED.
- T8.c2 (logs/T8.c2.md, commit 30e5e10a23): 12/13 asm-body routines MATCH as lever-free C, drafts .run/P40/T8/asmbody/<fn>.c, targets .run/P40/T8/asmbody/tgt/<bin> (verbatim_target_s.py). func_80020F34 hand-written (no frame, fixed $t0..$t6 roles, loads placed between gpf and mfc2 to fill GTE wait). func_80184440 needs -O0 (--o0). Decl caveats: 800.c K&R `()` for func_80026514/func_80027058; md_MAIN_027 calls func_800CBA44 via 6-arg s32 cast; func_801A3BCC local `g` resembles "LEVER 3" comment md_SC07_003.c:1251.
## In flight
- T8.c3 (agent ab0fc0b10970aee54, log logs/T8.c3.md): SHB -> ENGINE_SHB / ENGINE_SHB_NV in the prelude; 9 one-off macros expanded at uses + delever t8_mac<k>; gte variant respell oracle tests. Check its commits/log when respawned; do not start src edits before confirming it finished (git log, `delever.py --status`).
## Next five steps
1. Read T8.c3's log result line; verify strict line (per-TU macro defs only prelude).
2. Coder T8.c4: land the 12 drafts into src/ (settle decls; func_80184440 -O0 TU handling), remove !FAKE asm-body markers, R22.
3. func_80020F34: no assembly-unit mechanism in tree (no src .s); an .s unit needs build wiring outside T8 files -> keep the asm body, ledger row instrument = hand-written evidence; record as deviation (or question).
4. Rewrite TSV: strip data rows, `lever_census.py --check --strict --write-residue config/lever_residue.tsv -j 16`, set instrument text for gte/asm-macro/asm-body rows from T8 evidence; verify residue-unused 0 and the plan verify line.
5. Summary tasks/T8.md with before/after strict counts per kind; cookbook entries (struct-field vs stack-slot reorder; address-taken scalar slot order; delever marker pass erases author comments -> harness/tools gotcha); task_log finish; commit.
## Gotchas
- commit_task.sh refuses tracked files under ignored .run/ (calibration.json, lever_census.{json,txt} left uncommitted).
- delever marker pass rewrites hand-written `// !FAKE:` comments; restore with .run/P40/T8/rj/keep_author_markers.py.
