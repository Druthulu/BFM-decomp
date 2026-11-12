# PhaseEnd — Phase 3.43: Evidence and best-guess names (implements Gen 3.43)
Approved: 2026-11-10 | Closed: 2026-11-12 | Planner: claude-opus-5-5/medium | Tasks: 17 done, 0 superseded

## Milestone
Milestone: every confirmed name carries a citation row (0 uncited) and every `guess_` name a basis row (0 without basis), both checked by the 3.42 scanner (`PY tools/rename_scan.py --ledger --gate-citations` OK: curated without citation 0, `guess_` without basis 0, dead 0, invalid 0); the top 500 of 3.42's ranking named, confirmed or `guess_`, with `no-evidence` only where not even a guess has a basis (the 500 units with `rank43` <= 500 in docs/leverage.tsv as committed at e328006dab, frozen by T1 into a tracked worklist whose dispositions the same scanner checks); R22 218/218 (`make clean && make extract-all JOBS=16 && make check-all JOBS=16` prints `218 passed, 0 failed of 218`); ghidra `--proof` PASS (`tools/ghidra_rebuild.sh <prog> --proof` for all six programs in `config/ghidra/`).
Confirmed by the developer at the close.

## Tasks
- T1 — phase-start baselines, the frozen worklist and the names baseline | Done: 3.43 baselines measured at 5e69f147c5 (R22 218/218, tools-health OK, leverage --check IDENTICAL); config/names_worklist.tsv freezes the 500 units with their dedup targets. Summary: The build and the tool suite are green at the phase's starting commit, and the naming ranking reproduces byte for byte with no drift since 3.42. The 500 names to work on are now frozen in a tracked file, so later renames that renumber the ranking cannot move the target. The join found that most shared function classes use a registry form the rename tool does not read, so a class rename would silently do nothing for 188 of the 196 grouped units: that has to be fixed before the first batch. | commit: 5e69f147c5 | tasks/T1.md | logs/T1.md
- T2 — rename tooling for the campaign: worklist check, ledger row history, generated outputs | Done: rename_scan checks the frozen worklist (`--worklist FILE [--complete]`); rename_sym validates specs before writing, rewrites an existing ledger row with history, expands both registry group forms and rewrites leverage files and share headers as text; rule 1 has the `library symbol` kind. Summary: The two rename tools are now ready for real batches. The scanner can check every disposed row of the 500-name worklist against the symbol files and the names ledger, and in its final form it fails while any row is still open. Renaming a name twice now updates its one ledger row and keeps the name's history, instead of leaving a dead row behind. Bad evidence values are refused before any file is touched. Two silent gaps were closed along the way: class renames on most registry groups did nothing, and share headers were skipped as if they were generated, which would have broken the build. | commit: 4c72a67ad5 | tasks/T2.md | logs/T2.md
- T3 — I4: real returns for the s32 functions with no return statement | Done: the 38 names 3.41 flipped void->s32 (40 defs) each end in a byte-neutral `return <expr>;` (21) or carry a `$v0 at exit` comment with byte evidence (19); R22 218/218; the HEAD scan of 394 names is kept in docs/ops. Summary: In 3.41, 38 functions were changed from `void` to returning a value because their callers read it, but none of them actually returned anything. Now 21 of their 40 definitions return a real value with the compiled bytes unchanged. The other 19 cannot, because any `return` changes an instruction, so each says in a comment what the return register holds and which instruction would move. A full scan found 394 such functions in the code, not 37. The developer chose to fix only the 38 here and park the other 356 for Gen 4. | commit: c837e0d93c | tasks/T3.md | logs/T3.md
- T4 — I3: second look at the 9 expand-hardreg-var wall tags | Done: all 9 `wall:expand-hardreg-var` rows were re-probed with fresh per-pass dumps in .run/3.43/t4/probe/. 4 keep the tag and 5 are re-tagged. The wall gate is OK with unwalled 0, unknown-tag 0 and residue-unused 0. Summary: Each of the nine pins was compiled with and without the pin, and the two compilations were compared pass by pass. In four functions the shape the pin forces at the very first pass is still there after combine, so the old tag stands. In the other five that first difference disappears before combine, and the difference that reaches the code is born later: in cse for three and in the scheduler for two. They now carry those tags. No pin can come off: every pin-free build still differs. | commit: - | tasks/T4.md | logs/T4.md
- T5 — citation rows for the 1,083 curated names, then the citation gate | Done: config/names.tsv holds a row for every curated name (1,083: 1,081 cited, 2 guess_); tools-health runs `rename_scan --ledger --gate-citations`. Summary: Every name the project had inherited now says where it comes from. Sony's library names are cited to the exact SDK object and offset the build links, or, for the 19 library functions we rebuilt from C, to a byte-for-byte comparison with Sony's object. The game's own names are cited to the recorded traces and live observations they were based on. Two names that only rest on cheat-code lore are now marked as guesses. The health check fails from now on if a name without a source appears. | commit: 1d52555fe2 | tasks/T5.md | logs/T5.md
- T6 — naming evidence: outside sources recorded, a dossier per worklist unit | Done: docs/memory-map.md carries the new outside addresses (CodeBreaker NTSC-U, TASVideos; TCRF unreachable) as `reported`; .run/3.43/t6/dossier.py writes 500 dossiers plus evidence counts in about 25 s. Summary: The few public address lists for the game were fetched once and every address not already in the address ledger was added, each marked as reported with its source and date; none is verified, since no live-RAM session was run. A scratch script now writes one evidence page per worklist unit (definition, body, callers and callees by their current names, data touched, strings, ledger hits, owner struct) and reruns in under half a minute, so each naming batch starts from fresh pages. The evidence is thin, as expected: 448 of the 500 units have nothing but their own code, 50 are linked by calls to an already-named function, and 2 are live-verified. | commit: - | tasks/T6.md | logs/T6.md
- T7 — pilot naming batch and the conventions, for the developer's review | Done: 27 worklist units disposed (cited 2, guess 23, no-evidence 2) with names.tsv rows and a 3-line header comment above every definition of each named function; naming conventions written in docs/wiki/Names-and-renames.md; renames are now census-neutral. Summary: The first 25 names landed: two cited from live-RAM measurements (the player's HP and max HP) and 23 marked best guesses, each with the code fact it rests on written in the names ledger and in a comment above the function. Two units were left unnamed on purpose, with the reason recorded. The batch exposed two tool gaps that later batches would have hit: the rename tool rewrites an old name in every file, even where the same placeholder means a different function, and the type census recognised globals only by their placeholder spelling. The second gap was fixed and proved by running the census before and after the batch with the same numbers; the first is avoided for now and needs a tool change before such units can be named. | commit: - | tasks/T7.md | logs/T7.md
- T8 — name the worklist's data units | Done: all 147 worklist data units left after T7 are disposed (guess 99, no-evidence 48), plus the approved cited PsyQ alias D_800AE688 -> GsWSMATRIX; every batch passed the batch procedure; R22 218/218 and make tools-health OK at 948e2daef0; rename_scan --ledger --gate-citations OK. Summary: The game's data placeholders on the worklist now carry names or a recorded reason for staying unnamed. They were named in five batches grouped by address, so the fields of one block (the menu state, the camera records, the HUD, the target-time sprites, the render work block) got one family of names. No name could be cited from an outside record: the only live-verified data were already named in T7, so every new name is a best guess marked `guess_`, with the code fact it rests on in the names ledger. About a third of the units stay unnamed because their code shows only a position inside a record or array, not a role. One extra name is cited: the PsyQ library's GsWSMATRIX, which the code was reaching through a placeholder. | commit: - | tasks/T8.md | logs/T8.md
- T9 — name the worklist's functions, rank43 1 to 177 | Done: all 102 open worklist functions with rank43 <= 177 are disposed (guess 80, no-evidence 22) with header comments; 9 PsyQ aliases cited; two earlier no-evidence units named on new evidence; rename_sym, rename_scan and lint_symbol_refs are now per binary; R22 218/218 and tools-health OK at a2af7fed1c. Summary: Every function in the top 177 of the naming list now has a name or a recorded reason to stay unnamed, and each named function carries a comment saying what it does and why we think so. All new names are marked best guesses, because no outside record names these functions; nine further names are cited from the Sony library the game links. Most of the work went into the tools: one placeholder spelling can mean different functions in different overlays, so the rename, the leftover-name scan and the lint now look at each binary separately. That is what let functions with many copies be named. The leftover-name scan hung for 11 hours on the first batch. The cause was git's search, which slows by orders of magnitude when given many separate patterns. The scan now joins its patterns into one per chunk and stops with an error past a time limit. | commit: - | tasks/T9.md | logs/T9.md
- T10 — name the worklist's functions, rank43 178 to 321 | Done: all 111 open worklist functions with rank43 178-321 are disposed (guess 96, no-evidence 15) with header comments; two earlier no-evidence units named on new evidence; R22 218/218 at 26c6417954, tools-health OK at 754ad3d1d8. Summary: Every function ranked 178 to 321 on the naming list now has a name or a recorded reason to stay unnamed, and each named function carries a comment saying what it does and why we think so. All names are marked best guesses; no outside record names these functions. Two thirds of the batch turned out to be one small routine copied into 66 overlays, which puts the label "ENE" and a number on screen; it is named for what it does, without guessing what "ENE" stands for. T9's tool changes carried the whole task: no tool needed fixing this time. | commit: - | tasks/T10.md | logs/T10.md
- T11 — name the worklist's functions, rank43 322 to 500 | Done: all 113 open worklist functions rank43 322-500 disposed (guess 91, no-evidence 22) with header comments; the frozen worklist is complete (500 of 500); R22 218/218 at 997f76cac6, tools-health OK at c15d04358c. Summary: Every function on the 500-entry naming list now has a name or a recorded reason to stay unnamed, so the list is finished. More than half of this last stretch was the same small "ENE" display routine copied into 62 overlays, named the way the previous task decided. The other 51 were judged one by one: 29 got best-guess names from what their code does and who calls them, and 22 were left unnamed because their code alone does not say what they are for. All names are still marked best guesses; no outside record names these functions. | commit: - | tasks/T11.md | logs/T11.md
- T12 — ledger-to-comment pass: each lever's wall and each guess's ledger pointer beside the code | Done: every residue-excused lever marker names its wall, gated in lever_census --strict --residue; every guess_ datum declaration carries a names-ledger pointer; guess_ function headers already did (0 missing). Summary: A reader of the source now sees, beside each kept compiler lever, the name of the compiler wall that keeps it, and the project's check fails if that comment and the ledger ever disagree. Every declaration of a best-guess global now ends with a pointer to its row in the names ledger, as the best-guess functions' header comments already did. The edits are comments only: the game still rebuilds byte-identical in all 218 binaries and every census reads the same. | commit: - | tasks/T12.md | logs/T12.md
- T13 — the record: cookbook, decision log, wiki, standards, levers prose, tool index, kit corpus | Done: the phase's decisions are in docs/decision-log.md (5 entries), docs/wiki/Names-and-renames.md describes the landed names and the worklist check, rule 1 notes the T7 conventions, levers.md gives I3's outcome, the changed tools' dictionary rows name their new behaviour. Summary: The phase's public record now says what was decided and why. The decision log explains the frozen naming list, the rule that only a recorded source cites a name, how Sony's library names are cited, the header comment above every named function, and the wall tags written beside each kept compiler lever. The names page reports what landed: 500 of 500 list entries settled, 2 cited, 393 best guesses and 105 left unnamed on purpose, with the evidence behind them. All the phase's techniques were already in the cookbook. | commit: - | tasks/T13.md | logs/T13.md
- T14 — Ghidra mirror of the new names into the live project | Done: the live Ghidra project carries every 3.43 name for SLUS_007.26, resident, ov_SC01_077 and ov_SC06_018 (failed=0, saved, 21/21 read back); the five changed type files are verified in it; the MCP Ghidra is stopped for T15. Summary: The new function and data names from this phase are now in the real Ghidra database, not only in the source. Each of the four programs took its full name stack with no failures, and 21 sample names were read back from the saved database. This phase's type changes were only renamed words in field comments; they are confirmed to be in the database exactly as committed. The Ghidra server stays off so the next task can run its proofs. | commit: - | tasks/T14.md | logs/T14.md
- T15 — milestone gate (Phase 3.43) | Done: Phase 3.43's milestone holds at f88462bafc: R22 218/218, tools-health OK, names ledger and worklist complete and gated, leverage --check IDENTICAL, six Ghidra proofs PASS; series rows, timeline and ledger backups recorded. Summary: Every check that defines the end of the naming phase passed on the first run, all at one commit. The game still rebuilds byte-identical in all 218 binaries. Every name in the project now has a source or is marked as a best guess with its reasons. All 500 names on the frozen list are either named or carry a written reason for staying unnamed. The Ghidra database rebuilds with the new names in all six programs. The progress series, the timeline and the public ledger backups now record the close. | commit: f88462bafc | tasks/T15.md | logs/T15.md
- T16 — phase-close docs: story, retrospective, wiki, README (Phase 3.43) | Done: story §10 has its Phase 43 part and §11 the P3.43-close snapshot; retrospective §7 runs to Phase 43 in all four paragraphs; wiki rule 1 carries Phase 43; timeline and progress regenerated; doc_links --strict 0/0. Summary: The public record now tells the names phase in plain words: what a `guess_` name is, why most of the 500 are guesses (448 had only the code to go on), and what a citation row proves (that a name can be traced to its source, not that it is right). The retrospective adds the phase's beliefs, failures, cost and lessons; the wiki's naming rule notes the first names; the timeline chart has the close. | commit: - | tasks/T16.md | logs/T16.md
- T17 — phase cleanup | Done: what 3.43's scratch held that later work reuses is now in the repo: tools/name_dossier.py, tools/map_cite_check.py, tools/wall_probe.py (dictionary rows), and T4's probe evidence in docs/ops; .run/3.43 can be deleted. Summary: The phase left about 16 GB of scratch. Three scripts that later work will reuse became proper project tools. They gather the naming evidence for a unit, check that map-line citations still point at the right line, and probe a compiler wall. The text evidence behind T4's nine wall re-tags is now a docs page. Everything else was either already recorded in tracked files or can be regenerated, so the scratch folder holds nothing the project needs. | commit: f3d88b2a46 | tasks/T17.md | logs/T17.md

## Decisions that still bind
- T2 — a `class:<id>` spec row writes one names.tsv row with scope `class:<id>`; check_ledger expands it through the registry (name and name_<k> count as live, based, cited).
- T2 — rename_sym rewrites build inputs (src/, include/) as text whatever their generated marker; docs/leverage.md/.tsv are rewritten as text and regenerated once at the close (T15).
- T2 — worklist instances are the .run/sig.*.jsonl rows with the unit's full h_exact; names resolve through the splat yamls' symbol stacks (main us+us.ram, resident us+resident, overlays us+resident+own, md us+own).
- T3 — scope = the 38 names of 112c3e4eb9's flips, at every copy (developer, option A, 2026-11-10); the other 356 go to INBOX for Gen 4, listed in docs/ops/p343-t3-return-less-nonvoid-scan.md.
- T5 — PsyQ citation format `<LIB>.LIB <OBJ>.OBJ <section>+0x<off> (map: build/psyq/<dir>/<OBJ>.o; nm)`; libapi 4.2 and libpad 4.2.1 written `LIBAPI.LIB(4.2)`, `LIBPAD.LIB(4.2.1)`; conflict `object symbol <sym>` when the object names that offset differently.
- T7 — a name is cited only when its meaning comes from a recorded source (library symbol, game string, debug menu, live RAM at G5, a G5-verified community label); every model-worded name is `guess_`, whatever its confidence (wiki conventions).
- T7 — `guess_` is the outermost prefix (`guess_g_X`, `guess_s_X`); stripping it gives the confirmed name; the tools read the tier from it.
- T7 — a rename is census-neutral as well as byte-neutral; the census maps renamed names back to placeholders through names.tsv history (C0572).
- T7 — md_* modules that call a renamed overlay function get a plain md-alias row with the same name (C0571).
- T8 — a resident datum used by main's own C gets its main-side name in config/symbols.us.ram.txt (rename_sym binary `us.ram`), never config/symbols.us.txt (C0574).
- T9 — renames are binary-scoped end to end (rename_sym, rename_scan --spec, lint_symbol_refs); a hit counts as another entity only from a fact on its own line (object id, kind, member binary, residue path, row hash, owner type users), never by a path or line exemption list.
- T9 — a resident caller of an overlay function keeps its placeholder, bound with `__asm__("func_<ADDR>")`; no resident alias rows (every overlay stacks symbols.resident.txt).
- T9 — refresh the series census (d1-snapshot) before tools-health after renames, or progress.py publishes drifted counts.
- T12 — a residue row's wall is shown in its sites' `// !FAKE:` markers; a re-tag or row removal edits the marker in the same change (the gate prints the expected tag).
-

## Rules proposed
- T3 — a lever removed by a readability edit drops its config/lever_residue.tsv row in the same commit.

## Cookbook entries added
C0565 | join a leverage unit to dedup groups and sig instances (two group forms; rename_sym reads members only) | rename,dedup,leverage,class,join | 2026-11-10 | 3.43/T1 | -
C0566 | Rename batches: generated-marked build inputs, leverage files as text, frozen worklist | rename,symbol,names-ledger,generated,worklist | 2026-11-10 | 3.43/T2 | P3.43 T2.c1
C0567 | Real returns for return-less non-void defs: the neutral-form ladder | return-type,return,bytes,lying,regalloc | 2026-11-10 | 3.43/T3 | P3.43 T3.c1
C0569 | Cite a curated name to its PsyQ library object; byte-compare SDK names compiled from C | names-ledger,psyq,symbol,citation,library | 2026-11-10 | 3.43/T5 | P3.43 T5.c1
C0570 | many-name grep over src: GNU grep -F -f over git ls-files (git grep -f is 100x slower); splat short .asciz is no string | grep,performance,naming,evidence,splat,strings | 2026-11-10 | 3.43/T6 | T6.c1 dossier script
C0571 | Placeholder names are per binary: repo-wide rename rewrite hits unrelated functions; md externs need md rows | rename,symbol,overlay,md,placeholder,hazard | 2026-11-10 | 3.43/T7 | P3.43 T7.c1
C0572 | A data rename breaks tools classifying by D_/func_ spelling (type_census residue, restruct ledger) | rename,type_census,residue,restruct,ledger,names | 2026-11-10 | 3.43/T7 | P3.43 T7.c2
C0573 | data rename: name address-only mentions before rename_scan --spec | rename,names-ledger,rename_scan,data | 2026-11-11 | 3.43/T8 | T8.c1
C0574 | resident data used by main: name it in symbols.us.ram.txt (rename_sym binary us.ram) | rename,symbol,resident,data,rename_sym | 2026-11-11 | 3.43/T8 | T8.c6
C0575 | git grep with many -e patterns stalls; join into one -e per chunk (rename_scan hang) | grep,performance,rename_scan,git,hang | 2026-11-11 | 3.43/T9 | T9.c4
C0576 | md-module renames drop sig instructions unless sig-modules seeds from symbol files | rename,sig,md,makefile,tools-health,timeline | 2026-11-12 | 3.43/T9 | T9.c14
C0577 | Decode resident game text from splat .word data for string naming evidence | naming,evidence,strings,splat,resident,guess | 2026-11-12 | 3.43/T10 | T10.c1
C0578 | Keep a lever's wall tag in its !FAKE marker, gated against the residue row | levers,walls,residue,comments,lever-census | 2026-11-12 | 3.43/T12 | logs/T12.c1.md
C0579 | Append a trailing comment to many C declaration lines, proven comment-only and census-neutral | comments,codemod,census,names-ledger,guess | 2026-11-12 | 3.43/T12 | logs/T12.c2.md
C0580 | Mirror a phase's new names into the live Ghidra project (4 programs) and prove it | ghidra,rename,symbol,live-db,mirror | 2026-11-12 | 3.43/T14 | P3.43 T14

## Research
R3.43-001 | 3.43 pa-planner: can comments be added beside functions, data and lever sites without moving any gate; where they go | Lever-site comments, parser comment handling, and the 9 expand-hardreg-var rows | lever-census, residue, walls, comments, share-census, cdecl, restruct, argcheck, type-census, verbatim-check, lint-symbol-refs | retriever-code | 2026-11-10 | 79 lines
R3.43-002 | pa-planner phase 3.43 `## Interfaces` (names campaign: ~500 renames, citation rows for 1,083 curated names, rank43 <= 500 worklist) | Rename machinery interfaces for the P3.43 names campaign | rename_sym, rename_scan, names.tsv, rename_known, leverage_rank, leverage.tsv, lint_symbol_refs, dedup.us.yaml, classes.jsonl | retriever-code | 2026-11-10 | 169 lines
R3.43-003 | pa-planner phase 3.43 plan, deferred items I3 and I4 | I3/I4 worklists and method notes (3.41 T4 void->s32 defs; 3.40 T20 expand-hardreg-var rows) | deferred, return-type, void-s32, expand-hardreg-var, levers, walls, probe, C0541, C0542, C0547, C0548 | retriever-digest | 2026-11-10 | 63 lines
R3.43-004 | What naming evidence /home/musashi/bfm-decomp already holds, and where the 1,080 curated main names came from (phase 3.43 planner input) | Naming evidence on disk and provenance of config/symbols.us.txt's curated names | naming, evidence-ladder, symbols.us.txt, memory-map, live-ram, tcrf, archipelago, provenance | retriever-digest | 2026-11-10 | 74 lines
R3.43-005 | Survey public web sources for named symbols, debug menu entries, and RAM addresses for the USA PS1 release, to size a naming phase. | Public sources naming functions, variables, or RAM addresses in Brave Fencer Musashi (SLUS-00726) | bfm, research, ram-map, symbols, cheats, tcrf, datacrystal, archipelago, tasvideos, decomp | retriever-web | 2026-11-10 | 52 lines
R3.43-006 | phase 3.43 T6, rule G5 outside-address ledger | Brave Fencer Musashi (USA, SLUS-00726) outside address list: CodeBreaker, TASVideos, TCRF | bfm, usa, SLUS-00726, cheats, ram-address, codebreaker, tasvideos, tcrf, G5 | retriever-web | 2026-11-10 | 93 lines
R3.43-007 | T16 phase-close docs (docs/story.md §10, docs/retrospective.md §7) | Phase 3.43 names campaign: story and retrospective facts (T2 to T14) | phase-3.43, names, bfm-decomp, retrospective, story | retriever-digest | 2026-11-12 | 72 lines

## Audit
- seed: median 26k, max 27k, n=17 (phase 3.43)
- previous phase 3.42: median 25k, growth 7.6%
- CLAUDE.md: 1304 bytes (unchanged)
- .claude/skills/commit-task-autostage/SKILL.md: 1024 bytes (unchanged)
- .claude/skills/d1-snapshot/SKILL.md: 1396 bytes (unchanged)
- .claude/skills/pa-external-agents/SKILL.md: 11144 bytes (unchanged)
- .claude/skills/pa-planning/SKILL.md: 8277 bytes (unchanged)
- .claude/skills/project-architect/SKILL.md: 13748 bytes (unchanged)
- .claude/skills/restruct-cycle-watch/SKILL.md: 1119 bytes (unchanged)
- .claude/skills/retire-doc-consumers/SKILL.md: 927 bytes (unchanged)
- .claude/skills/tools-edit-kit-corpus/SKILL.md: 990 bytes (unchanged)
- .claude-state/memory/MEMORY.md: 60 bytes (unchanged)
- HOW_WE_WORK.md: 9541 bytes
- cookbook/INDEX.md: 255329 bytes
- rules/INDEX.md: 15616 bytes
### Carry audit — phase 3.43 (2026-11-10T17:26:49Z → open UTC, 1 sessions, 4141 requests)

| file (read) | chars | n |
|---|---|---|
| rename_scan.py | 287.5k | 61 |
| rename_sym.py | 111.0k | 15 |
| share_body.py | 89.1k | 8 |
| type_census.py | 62.2k | 22 |
| lever_census.py | 56.2k | 13 |
| argcheck.py | 46.8k | 10 |
| 800.c | 38.3k | 32 |
| share_census.py | 37.9k | 14 |
| HEAD | 29.0k | 1 |
| plan.txt | 27.3k | 2 |
| file (write) | chars | n |
|---|---|---|
| rename_scan.py | 50.9k | 49 |
| dossier.py | 31.0k | 4 |
| mk_b3.py | 27.2k | 4 |
| mk_b1.py | 27.1k | 7 |
| rename_sym.py | 26.3k | 21 |
| mk_b2.py | 26.0k | 10 |
| mk_b4.py | 22.9k | 1 |
| mk_b4.py | 21.5k | 4 |
| result kind | chars | n |
|---|---|---|
| bash other | 4.5M | 2300 |
| Read | 1.4M | 389 |
| tools/plan_edit.py | 573.2k | 40 |
| Grep | 559.9k | 261 |
| run.sh | 334.1k | 506 |
| tools/rename_scan.py | 244.3k | 136 |
| tools/rename_sym.py | 137.2k | 67 |
| tools/type_census.py | 74.4k | 57 |
| tools/outline.py | 61.4k | 11 |
| tools/lever_census.py | 54.4k | 22 |
- spilled: 6 results, 811.8k chars on disk, 0 read whole
- whole reads over 20.0k: 0
- seed floor: retriever-code 7,021 (n 17, prev 7,021) · retriever-digest 6,914 (n 12, prev 6,914) · retriever-web 5,367 (n 2, prev 5,367)
- outline credit: 45 outlines · 22 followed by a ranged read · 1.6M chars credited
- warm pings: 244 pings over 26 runs, 68 warmed waits over the TTL, rewrites across warmed waits 0, waits past the cap 1, cost: pings $6.8373 + relay $0.0000 + re-arm $0.0000 = $6.8373 vs rewrites replaced $45.3634, cheaper than one rewrite: yes, undelivered 0
- toasts by cause (waiting): question 1, review 0, replan 0, permission 0, input 7, crash 0, idle 0, stop 0, subagent-stop 0, model 0, other 0
- router turns by cause: loop 1019, relay 0, re-arm 0, other 11, relay cost $0.0000
- retriever re-asks: 0 of 3 retriever briefs repeat a lookup of the same run
- noise: 152 lines 10.6k chars — usage: : 111 lines/7.6k, No such file or directory: 41 lines/3.0k
- price: read $0.20/Mtok · 1h write $7.99/Mtok · output $19.98/Mtok (phase model mix)
- median requests after a read: 0
- carry/request: 2052 chars, 4141 requests (prev 7121 chars, 1676 requests, growth -71.2%)
- flag: 189 tool-source reads by pa-claude, pa-coder, pa-expert, retriever-code, retriever-digest
  /home/musashi/bfm-decomp/tools/restruct.py  582 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  5.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  11.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ram_probe.py  1.2k chars  retriever-digest
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  14.9k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_sym.py  14.9k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.9k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  8.2k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  5.7k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.9k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  8.2k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  5.7k chars  pa-expert
  /home/musashi/bfm-decomp/tools/lever_census.py  3.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  1.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  10.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  10.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  56 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  56 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  224 chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  13.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  8.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  3.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  11.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  9.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  9.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  14.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  14.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  7.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  22.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  6.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  17.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  471 chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  17.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  471 chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  1.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  1.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  710 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  19.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  19.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  11.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  674 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  312 chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  4.2k chars  pa-claude
  /home/musashi/bfm-decomp/tools/progress.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/progress.py  2.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/progress.py  2.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  803 chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  673 chars  pa-coder
  /home/musashi/bfm-decomp/tools/delever.py  1.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/delever.py  1.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/delever.py  1.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  5.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/corpus.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  849 chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.1k chars  pa-coder
  /home/musashi/bfm-decomp/.claude/skills/d1-snapshot/SKILL.md  989 chars  retriever-code
  /home/musashi/bfm-decomp/tools/timeline.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/leverage_rank.py  292 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  3.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  4.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  7.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  4.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  7.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  12.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  14.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_mcp_start.sh  3.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_mcp_stop.sh  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_mcp_verify.sh  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_import.sh  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_apply_symbols.sh  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  2.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  2.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  3.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  3.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/DumpFunctionSignatures.java  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/DumpFunctionSignatures.java  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/decl_from_use.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/decl_from_use.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  513 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  513 chars  retriever-code
  /home/musashi/bfm-decomp/tools/lint_symbol_refs.py  8.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lint_symbol_refs.py  8.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  4.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  4.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  15.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  17.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  26.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  882 chars  retriever-code
  /home/musashi/bfm-decomp/tools/lift_types.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  6.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  6.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  725 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  525 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  6.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  6.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  6.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  1.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  8.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  8.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_types.py  1.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_types.py  546 chars  pa-coder
  /home/musashi/bfm-decomp/tools/lint_symbol_refs.py  3.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_apply_symbols.sh  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_rebuild.sh  10.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_mcp_call.py  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_export_annotations.sh  968 chars  retriever-code
  /home/musashi/bfm-decomp/tools/lint_symbol_refs.py  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/DumpFunctionSignatures.java  797 chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_rebuild.sh  2.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ImportAnnotations.java  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ExportAnnotations.java  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  2.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  3.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  2.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ExportAnnotations.java  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ExportAnnotations.java  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  4.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body_cycle.sh  5.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body.py  806 chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body.py  214 chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  4.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  3.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body_cycle.sh  2.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/dedup_integrate.py  833 chars  retriever-code
  /home/musashi/bfm-decomp/tools/shared_lock.py  736 chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body.py  19.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body_cycle.sh  5.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  5.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_sym.py  3.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_body.py  3.1k chars  retriever-code

## Agent runs
- T7 | pa-claude | partner | claude-opus-5-5 | medium | ctx 193k | $5.061 | saved $20.08 | completed | parent 252d32b5
- T1 | pa-expert | expert | claude-opus-5-5 | medium | ctx 83k | $1.516 | saved $4.19 | completed | parent 252d32b5
- T1 | pa-coder | coder | claude-opus-5-5 | medium | ctx 86k | $1.273 | saved $0.87 | completed | parent a0198e68
- T2 | pa-expert | expert | claude-opus-5-5 | medium | ctx 116k | $2.038 | saved $3.46 | completed | parent 252d32b5
- T2 | pa-coder | coder | claude-opus-5-5 | medium | ctx 139k | $3.458 | saved - | completed | parent a1dbd289
- T3 | pa-expert | expert | claude-opus-5-5 | medium | ctx 88k | $1.763 | saved $1.25 | completed | parent 252d32b5
- T3 | pa-coder | coder | claude-opus-5-5 | medium | ctx 81k | $1.553 | saved - | completed | parent aa04d9e4
- T3 | retriever-code | retriever | claude-haiku-5-5 | medium | ctx 38k | $0.012 | saved - | completed | parent a5d2780f
- T4 | pa-expert | expert | claude-opus-5-5 | medium | ctx 121k | $2.172 | saved $1.31 | completed | parent 252d32b5
- T5 | pa-expert | expert | claude-opus-5-5 | medium | ctx 148k | $3.436 | saved $10.21 | completed | parent 252d32b5
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 79k | $1.432 | saved - | completed | parent ac13270e
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 51k | $0.626 | saved $0.97 | completed | parent ac13270e
- T6 | pa-expert | expert | claude-opus-5-5 | medium | ctx 106k | $1.770 | saved $7.70 | completed | parent 252d32b5
- T6 | retriever-web | retriever | claude-haiku-5-5 | medium | ctx 13k | $0.006 | saved - | completed | parent a8ae4549
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 116k | $2.856 | saved - | completed | parent a8ae4549
- T7 | pa-expert | expert | claude-opus-5-5 | medium | ctx 221k | $6.644 | saved $25.84 | completed | parent 252d32b5
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 78k | $1.631 | saved - | completed | parent a5cfafac
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 188k | $7.371 | saved $0.40 | completed | parent a5cfafac
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 140k | $3.545 | saved $3.13 | completed | parent a5cfafac
- T9 | pa-claude | partner | claude-opus-5-5 | medium | ctx 79k | $1.164 | saved - | completed | parent 252d32b5
- T8 | pa-expert | expert | claude-opus-5-5 | medium | ctx 117k | $2.476 | saved $49.35 | completed | parent 252d32b5
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 182k | $6.126 | saved $0.08 | completed | parent ab19356a
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 191k | $5.289 | saved - | completed | parent ab19356a
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 157k | $3.690 | saved $0.86 | completed | parent ab19356a
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 147k | $2.589 | saved - | completed | parent ab19356a
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 114k | $2.544 | saved $0.48 | completed | parent ab19356a
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 186k | $6.331 | saved - | completed | parent ab19356a
- T9 | pa-expert | expert | claude-opus-5-5 | medium | ctx 182k | $5.296 | saved $113.38 | completed | parent 252d32b5
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 102k | $1.946 | saved - | completed | parent a38415d0
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 228k | $9.117 | saved $3.61 | completed | parent a38415d0
- T17 | pa-claude | partner | claude-opus-5-5 | medium | ctx 128k | $2.004 | saved - | completed | parent 252d32b5
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 40k | $0.403 | saved - | completed | parent a38415d0
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 85k | $1.568 | saved $0.55 | completed | parent a38415d0
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 43k | $0.431 | saved - | completed | parent a38415d0
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 36k | $0.357 | saved - | completed | parent a38415d0
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 291k | $10.722 | saved $3.42 | completed | parent a38415d0
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 123k | $2.584 | saved $1.30 | completed | parent a38415d0
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 96k | $1.517 | saved $0.82 | completed | parent a38415d0
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 53k | $0.650 | saved - | completed | parent a38415d0
- … 24 more: PY ~/.claude/pa3/pa_ledger.py report

## Discussions
- I5 | -> 3.44 The 356 older non-void functions with no `return` (or only a bare `return;`) left after 3.43 T3, which did only | deferred:3.44
- I6 | -> 3.45 Developer 2026-11-10, the modder's view: src/ should read like a modern project, with code in folders and files | deferred:3.45

## Deferred
- from T17: the close: R108's MCP restart; .run/3.43 may be deleted whole (nothing left that the project needs). Cookbook entries still citing other .run/3.43 scripts label them "(scratch)"; their method text stands alone. (unconsumed)
- I5 (deferred:3.44): -> 3.44 The 356 older non-void functions with no `return` (or only a bare `return;`) left after 3.43 T3, which did only
- I6 (deferred:3.45): -> 3.45 Developer 2026-11-10, the modder's view: src/ should read like a modern project, with code in folders and files

## Changes
- 2026-11-10 router: T1 next -> done
- 2026-11-10 developer: Developer decides answered 2026-11-10: yes to all three. (1) T14 may stop the MCP Ghidra once with tools/ghidra_mcp_stop.sh (clean save+stop, never a kill) for the live name mirror and the six --proof legs; it stays stopped to the close, then tools/ghidra_mcp_start.sh and Claude asks for /mcp. Until T14 it keeps running for the developer's use. (2) Add the seventh evidence kind 'library symbol' to docs/gen3-standards.md rule 1 and the scanner's closed list (T2, T5). (3) 3.43 names functions and data only; struct types and fields are deferred, recorded in the PhaseEnd.
- 2026-11-10 router: T2 next -> done
- 2026-11-10 developer: T3 scope (developer 2026-11-10, option A): T3 fixes only the 38 functions that 3.41's 112c3e4eb9 flipped from void (the HEAD scan found 394 names / 9,009 defs; 3.41 said 37). The other 356 are parked in INBOX -> Gen 4. T3 keeps the full scan list (names, def counts, kinds, last-statement bucket) in docs/ops/ so it outlives .run/3.43/.
- 2026-11-10 router: T3 next -> done
- 2026-11-10 router: T4 next -> done
- 2026-11-10 router: T5 next -> done
- 2026-11-10 router: T6 next -> done
- 2026-11-10 router: T7 next -> done
- 2026-11-10 router: T7 review approved (all 7 as recommended): conventions page binds T8-T11; func_80014554 stays unnamed; g_PlayerHpMax stays cited; low player guesses kept; binary-scoped rename_sym rewrite added to T9's scope before the function batches (C0571); PsyQ alias renames cited in T8/T9 after checking the symbol file can carry the object's name; c2/c3 tool fixes accepted
- 2026-11-11 router: T8 next -> done
- 2026-11-12 router: T9 next -> done
- 2026-11-12 router: T10 next -> done
- 2026-11-12 router: T11 next -> done
- 2026-11-12 router: T12 next -> done
- 2026-11-12 router: T13 next -> done
- 2026-11-12 router: T14 next -> done
- 2026-11-12 router: T15 next -> done
- 2026-11-12 router: T16 next -> done
- 2026-11-12 router: T17 next -> done

## Plain-English Recap
Phase 3.43 named the code for the first time. All 500 worklist units are settled: 2 cited (g_PlayerHp and g_PlayerHpMax, live-RAM proven), 393 best guesses marked `guess_` with ledgered basis, confidence and evidence kind, and 105 left unnamed with a recorded reason. Most are guesses because the game has no public symbol map and 448 of the 500 had only their own code as evidence. All 1,083 inherited curated names now carry citations, most as `library symbol` checked against the PsyQ objects; 2 were demoted to guess_. tools-health now fails on any uncited name. Every named function has a three-line header comment, every guess_ datum declaration points to its ledger row, and every `// !FAKE:` marker shows its wall tag, kept in step by lever_census. Carry-overs: of 3.41's 38 return-less functions, 21 now have real returns and 19 have explanatory comments (the other 356 go to 3.44). Of the 9 expand-hardreg-var walls, 4 were kept and 5 re-tagged. Tooling: rename_sym, rename_scan and lint_symbol_refs work per binary. rename_scan's 11-hour git grep stall (many -e patterns) is fixed with joined chunked patterns and a 30-minute bound (C0575). name_dossier, map_cite_check and wall_probe were promoted to tools. The names are mirrored into the live Ghidra project, and the story, retrospective, wiki and decision log run to Phase 43.

Milestone gate at f88462bafc, from a clean tree: R22 218/218 run alone; tools-health OK; rename_scan --ledger --gate-citations OK (2,171 rows, 0 uncited); --worklist --complete OK (0 undisposed); leverage_rank --check IDENTICAL; lint_symbol_refs rc 0; lever_census --check --strict --residue OK (unwalled 0); ghidra_rebuild --proof PROOF PASS for all six programs; doc_links and audit_public clean; ledger_backup done (archive commit 0a63007, unpushed).

Open items: the developer pushes the archive clone and the repo; after the close Claude runs tools/ghidra_mcp_start.sh and asks the developer for /mcp; .run/3.43 (about 16 GB, including the 994 MB t14/ghidra.bak) can be deleted, with about 8 GB of disk free; type_census's struct_map counts vary between runs on an unchanged tree and need a fixed tie-break; the text-slot helpers (func_8001534C, func_800153CC, func_80015498) and func_80133784 are worth naming later; the targeted ram_probe session list (R128) is still owed to the developer.
