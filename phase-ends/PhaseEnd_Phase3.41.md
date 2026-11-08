# PhaseEnd — Phase 3.41: Types validated and mirrored (implements Gen 3.41)
Approved: 2026-11-07 | Closed: 2026-11-08 | Planner: claude-opus-5-5/medium | Tasks: 13 done, 0 superseded

## Milestone
Milestone: the type work of 3.38-3.40 is guarded and mirrored: `PY tools/type_census.py --check` (duplicate-layout classes 0, struct definitions outside the canonical type files 0, dead names 0, controls 4/4, lying declarations 0 including return-type lies) runs inside `make tools-health` beside `--check-structs` and `--check-casts --residue`, and tools-health is OK; `PY tools/lever_census.py --check` fails on any lever marker that names no instrument (the P36 `attribution_check`, folded in) and is green; the canonical struct types are authored into the Ghidra database from the C headers by a tool, and `tools/ghidra_rebuild.sh <prog> --proof` prints PROOF PASS for every program in `config/ghidra/` (6 today); `PY tools/doc_links.py --strict` 0/0; clean-tree R22 `make clean && make extract-all JOBS=16 && make check-all JOBS=16` prints `218 passed, 0 failed of 218`, all at one commit.
Confirmed by the developer at the close.

## Tasks
- T1 — phase-start baselines and environment check | Done: baselines recorded at 0bdc4623a5 with make tools-health OK at 9adb323306; all 6 Ghidra --proof legs PASS (145 rows, failed=0) after the developer stopped the MCP. Summary: The phase's starting numbers are recorded: the type, lever and doc-link checks were run once each and their results are below. The health gate first failed because three copies of the 3.40 close documents had not been refreshed in the kit corpus; refreshing them made it pass. Once the developer stopped the live Ghidra server, the six Ghidra mirror rebuilds each reproduced their committed annotation files byte for byte. | commit: 9adb323306 | tasks/T1.md | logs/T1.md
- T2 — census tool bugs from 3.40 T21 | Done: type_census --no-cache runs into a fresh out dir; struct_twins defaults to type_census's census dir; lift_types --fold drops the old def's size tail. Summary: Three small tool bugs left over from 3.40 are fixed, each shown failing before and passing after. A fresh census no longer crashes, the twins tool now points at the right census folder by default, and folding duplicate structs no longer leaves stray size comments behind in the header. | commit: 8713c850bb | tasks/T2.md | logs/T2.md
- T3 — return-type lies in the lying-declaration check | Done: argcheck/type_census report return-type lies (kind/reason `return`) apart from arity; 273 functions / 100,266 decl sites; --check-casts red on them until T4. Summary: The lying-declaration check only compared argument counts, so a function declared `void` everywhere but defined returning a value went unseen. It now also compares return types after resolving typedefs, and the census counts and buckets these lies so T4 can fix them. The count is 273 functions, under the 300 threshold that would have stopped T4 for the developer. | commit: 590e86bbbd | tasks/T3.md | logs/T3.md
- T4 — fix the return-type lies at def, declarations and callers | Done: return lies 0 unledgered: 254 of 273 functions fixed as units (def + decls + callers); 19 kept in config/lying_exceptions.tsv with objdump evidence; --check-casts --residue rc 0; R22 218/218. Summary: Every function whose declared return type disagreed with its definition is now consistent, except 19. Most fixes rewrote the declarations to the definition's type. Where that moved bytes, the definition took the callers' type. The 19 left are width or sign mismatches where either side changes the compiled code, and each is recorded with the instruction that moves. | commit: 9658c8911a | tasks/T4.md | logs/T4.md
- T5 — type_census --check aligned to the done-criteria and wired into tools-health | Done: `type_census --check` asserts the Gen-3 done-criteria and is green; tools-health runs it with --check-structs and --check-casts --residue, lever_census --strict --residue, doc_links --strict. Summary: The type gate used to fail on every one of the ~176k raw cast sites, so it could never pass. It now checks what the generation's done-criteria name: no unlisted duplicate struct definitions, none outside the canonical headers, no dead names, all four controls, and no lying declaration (arity or return type) that is not ledgered. It still prints the raw cast count, which the per-site residue gate covers. The health check now runs this gate, the strict lever gate and the strict doc-link check, which adds about six minutes. | commit: - | tasks/T5.md | logs/T5.md
- T6 — attribution check folded into lever_census --check | Done: `lever_census --check` fails on a counted class A/B site whose `// !FAKE:` text names no instrument; vocabulary `INSTRUMENT_FORMS` (P36, P37, PA3) in the tool; tree 1,853 attributed, 0 unattributed. Summary: The one-off P36 attribution script is now part of the lever gate. Every surviving lever's honesty marker must say which pass or instrument judged it, using one of three named forms, each traced to the phase that wrote it. A census of today's markers found one bare marker from 3.40; its text was fixed from its residue row and the full byte gate stayed green. | commit: - | tasks/T6.md | logs/T6.md
- T7 — canonical types into Ghidra from the headers, proven by rebuild | Done: every canonical type (7,151: 4,131 structs, 3,005 typedefs, 15 unions; no enums present) reaches Ghidra as generated `type` rows. All 6 rebuild proofs PASS with failed=0, and Ghidra's exported layouts equal gcc's. Summary: A new tool reads the two canonical C headers and writes Ghidra type records for each of the six programs, with layouts computed the way the compiler computes them. The headless rebuild imports them and proves that Ghidra reproduces them exactly. A deliberately broken field makes the proof fail, and every type Ghidra exports matches gcc's own offsets and sizes. Ghidra now learns our structures from the text in the repo instead of by hand. | commit: 150cad3292 | tasks/T7.md | logs/T7.md
- T8 — apply the canonical types to the live Ghidra database | Done: live `ghidra/` holds T7's type rows for all 6 tracked programs (failed=0 each, re-export byte-identical); MCP serving on :8080 and answering get_binary_info and a struct lookup. Summary: The canonical C types we keep in the headers are now in the live Ghidra database, so the database shows the same structs the decomp's source uses. Every tracked program got its types with no failures, and reading the saved database back gives exactly the rows we generated. The Ghidra MCP is running again and answers through Claude Code. | commit: 1fc89363ef | tasks/T8.md | logs/T8.md
- T9 — the record: cookbook, wiki type layer, decision log, tool index and kit corpus | Done: the phase's techniques are banked (C0552 new, C0547-C0551 cross-linked, C0553), wiki "The type layer" is in the sidebar, the new gates are named on two wiki pages, decision-log holds the `--check` semantics entry, dictionary rows and kit corpus are fresh. Summary: The public and internal record now explains what this phase built: what a canonical type is and how the census, the cast ledger and the Ghidra mirror keep it honest. The decision log says what `type_census --check` asserts and why raw casts are gated elsewhere. The tool index describes the changed tools, and all doc and health checks are green. | commit: ea1d5696bf | tasks/T9.md | logs/T9.md
- T10 — milestone gate (Phase 3.41) | Done: Phase 3.41 milestone green at f4b1fbad3d: R22 218/218, tools-health OK, the three milestone commands rc 0, six Ghidra --proof PASS; lever and readability close rows recorded; ledgers backed up. Summary: The phase's milestone gate passed on one commit from a clean tree. The byte-identity gate, the tool health check and the type, lever and doc-link checks all pass, and all six Ghidra databases rebuild exactly from the repository. The close snapshots now show the return-type lies (19 functions, 9,302 call sites, all ledgered) that T13's new columns track, and the ledgers are backed up for the archive. | commit: f4b1fbad3d | tasks/T10.md | logs/T10.md
- T11 — phase-close docs: story, retrospective, wiki, README (Phase 3.41) | Done: story §10 has its Phase 41 part and §11 the P3.41-close row; retrospective §7 runs to Phase 41 in all four paragraphs; wiki next-steps rule 4 carries Phase 41; timeline and progress regenerated; the three verify commands rc 0. Summary: The public record now tells the Phase 41 story: the struct gate made to say what the done-criteria say, the return-type lies found and fixed as units (273 functions to 19 ledgered), the lever markers required to name their instrument, and the canonical types carried into Ghidra with byte-for-byte round-trip proofs. The retrospective adds what was believed and was not true, what failed, what it cost and what to do sooner. | commit: - | tasks/T11.md | logs/T11.md
- T12 — phase cleanup | Done: nothing the project needs lives only in .run/P41/ any more; ghidra_types no longer writes into a P41 scratch dir; the T8 MCP client is a tool. Summary: The phase's scratch folders were checked for anything the project still relies on. Almost all of it was already captured in cookbook entries, committed config files or task summaries. Two things were not: the Ghidra type tool wrote its compiler probe into this phase's scratch folder, so it now uses the build folder instead, and the small script that lets an agent talk to the Ghidra server became a proper tool. | commit: - | tasks/T12.md | logs/T12.md
- T13 — return-type lies on the graph and in the day-1 guide | Done: readability series carries return_lie_fns/return_lie_sites (blank on old rows); baseline 273/100266 row at T3's commit; snapshot 19/9302 at HEAD; timeline.py draws the line for T11; guide 03 and 10 carry the day-1 lesson; doc_links --strict 0/0; tools-health OK. Summary: The readability series now counts return-type lies: 273 functions and 100,266 declaration sites when the T3 detector landed, 19 and 9,302 (all ledgered) after T4. The README timeline learns the series so T11's regeneration shows the drop. The how-to guide's bootstrap and integration chapters now teach declaring each function once in a shared header, checking return types as well as arity, and that a void-to-int fix can still move bytes under gcc-2.7.2. | commit: 96e4726f58 | tasks/T13.md | logs/T13.md

## Decisions that still bind
- T5 — `--check` gates the allowlisted counts (struct-twins listed classes, block frames, dead_kept, lying_exceptions.tsv), the same readings --check-structs and --check-casts use; raw counters are printed beside them, never hidden (R42).
- T6 — new `// !FAKE:` markers use the PA3 form `pass: 3.NN T<n>[.k]` (with `; instrument: ...`); a new form goes into INSTRUMENT_FORMS with its phase/commit, never a catch-all (docs/levers.md §7).
- T7 — generated type rows live in config/ghidra/types/, never in the hand-authored config/ghidra/<prog>.jsonl; the rebuild merges them into export order (after the archive rows).
-

## Rules proposed
- (none)

## Cookbook entries added
C0546 | Scratch git worktree for reproducing an in-place tool's edits | worktree,reproducer,lift_types,fold,tools | 2026-11-07 | 3.41/T2 | -
C0547 | Return retype void->int on a decl is not always byte-neutral (dropped result still moves regalloc) | declarations,return-type,lying,bytes,regalloc | 2026-11-07 | 3.41/T4 | P3.41 T4.c1
C0548 | Clearing return-type lies fleet-wide: decls->def, def->decls, else ledger; width/sign lies stay | declarations,return-type,lying,bytes,exceptions | 2026-11-07 | 3.41/T4 | P3.41 T4.c2
C0549 | Fold a scratch text check into a gate: census today's text, one named form per phase | census,lever,gate,vocabulary,regex | 2026-11-07 | 3.41/T6 | 3.41 T6 attribution check
C0550 | New tool files need git add -N before make kit-corpus | kit-corpus,tools-health,tool_census,git | 2026-11-07 | 3.41/T7 | P3.41 T7.c1
C0551 | Ghidra type rows: import order, nested arrays, bitfields, comment alignment | ghidra,types,import,bitfields,layout | 2026-11-07 | 3.41/T7 | P3.41 T7.c1
C0552 | Return-type lies: argcheck norm_ret + canonical typedef map, opt-in returns=True; arity alone misses them | declarations,return-type,lying,argcheck,census | 2026-11-07 | 3.41/T9 | P3.41 T3
C0553 | kit_lint rejects project tokens (BFM*) in tool_dictionary prose mirrored to the kit MANIFEST | kit-corpus,kit-lint,tool_dictionary,tools-health | 2026-11-07 | 3.41/T9 | P3.41 T9.c1
C0554 | Ghidra live-DB type import (program-row guard, export cmp) + MCP over SSE without MCP tools | ghidra,mcp,types,import,live-db | 2026-11-07 | 3.41/T8 | P3.41 T8

## Research
R3.41-001 | pa-planner, Phase 3.41 Interfaces section (milestone: "attribution_check folded into lever_census") | attribution_check: what it was, and where it would fold into lever_census | lever_census, attribution, tools-health, doc_links, phase-3.41, read-only | retriever-code | 2026-11-07 | 75 lines
R3.41-002 | follow-up for pa-planner, phase 3.41 Interfaces section (canonical types authored as text into the Ghidra DB; ghidra_rebuild.sh --proof) | P3.41 Ghidra type-JSONL contract (ImportAnnotations / ExportAnnotations / delta / committed config) | ghidra, jsonl, types, p33-b5, proof, interfaces | retriever-code | 2026-11-07 | 65 lines
R3.41-003 | 3.41 planning, Interfaces section: wire `type_census --check` into `make tools-health`; maybe add a return-type-lie check | type_census --check wiring and lying-return facts for phase 3.41 | type_census, tools-health, argcheck, lying-declarations, return-type, struct_twins, lift_types, cookbook-C0543 | retriever-code | 2026-11-07 | 36 lines
R3.41-004 | pa-planner input for 3.41 Context/Triage/Risks: legacy P37 T8 (gates + Ghidra mirror) and T9 (record), §396(a), wiki, 3.40 carry-overs, D1 | What does phase 3.41 inherit (legacy T8+T9 carry) | phase-3.41, legacy-carry, type-layer, tools-health, ghidra-mirror, wiki, 396a, D1, tool-bugs | retriever-digest | 2026-11-07 | 65 lines
R3.41-005 | P3.41 T11 phase-close record (docs/story.md Phase 41, §11 numbers row, docs/retrospective.md §7) | Phase 3.41 task-by-task numbers for the public story and retrospective | phase-3.41, story, retrospective, type-census, return-lies, ghidra-types, lever-census | retriever-digest | 2026-11-08 | 62 lines

## Audit
- seed: median 24k, max 24k, n=14 (phase 3.41)
- previous phase 3.40: median 21k, growth 12.3%
- CLAUDE.md: 1304 bytes (unchanged)
- .claude/skills/commit-task-autostage/SKILL.md: 1024 bytes (unchanged)
- .claude/skills/d1-snapshot/SKILL.md: 932 bytes (unchanged)
- .claude/skills/pa-external-agents/SKILL.md: 11144 bytes (unchanged)
- .claude/skills/pa-planning/SKILL.md: 8277 bytes (+423)
- .claude/skills/project-architect/SKILL.md: 13748 bytes (unchanged)
- .claude/skills/restruct-cycle-watch/SKILL.md: 1119 bytes (unchanged)
- .claude/skills/retire-doc-consumers/SKILL.md: 927 bytes (unchanged)
- .claude/skills/tools-edit-kit-corpus/SKILL.md: 756 bytes (unchanged)
- .claude-state/memory/MEMORY.md: 60 bytes (unchanged)
- HOW_WE_WORK.md: 8777 bytes
- cookbook/INDEX.md: 250887 bytes
- rules/INDEX.md: 15616 bytes
### Carry audit — phase 3.41 (2026-11-07T22:27:52Z → open UTC, 1 sessions, 960 requests)

| file (read) | chars | n |
|---|---|---|
| argcheck.py | 64.9k | 8 |
| type_census.py | 51.2k | 9 |
| plan.txt | 27.3k | 2 |
| ExportAnnotations.java | 20.0k | 2 |
| struct_layout.py | 18.4k | 1 |
| ImportAnnotations.java | 17.8k | 2 |
| plansec.txt | 15.3k | 1 |
| readability_progress.py | 13.7k | 1 |
| ghidra_rebuild.sh | 11.8k | 2 |
| story.md | 11.2k | 2 |
| file (write) | chars | n |
|---|---|---|
| ghidra_types.py | 39.2k | 7 |
| retriever-phase-3-41-task-numbers.md | 10.2k | 1 |
| argcheck.py | 10.1k | 5 |
| ImportAnnotations.java | 7.3k | 5 |
| The-type-layer.md | 5.4k | 1 |
| T7.c1.md | 5.1k | 1 |
| T4.c2.md | 4.5k | 1 |
| T8.md | 3.2k | 1 |
| result kind | chars | n |
|---|---|---|
| bash other | 558.0k | 358 |
| Read | 326.0k | 70 |
| tools/plan_edit.py | 196.5k | 32 |
| Grep | 143.8k | 69 |
| tools/type_census.py | 99.4k | 38 |
| tools/ghidra_types.py | 82.3k | 31 |
| tools/argcheck.py | 72.4k | 24 |
| run.sh | 69.8k | 107 |
| tools/timeline.py | 35.8k | 9 |
| tools/ghidra_rebuild.sh | 34.3k | 10 |
- whole reads over 20.0k: 0
- seed floor: retriever-code 6,760 (n 5, prev 6,663) · retriever-digest 6,914 (n 4, prev 6,801)
- outline credit: 11 outlines · 3 followed by a ranged read · 174.8k chars credited
- warm pings: 22 pings over 7 runs, 9 warmed waits over the TTL, rewrites across warmed waits 0, waits past the cap 0, cost: pings $0.3980 + relay $0.0000 + re-arm $0.0000 = $0.3980 vs rewrites replaced $5.3204, cheaper than one rewrite: yes, undelivered 0
- toasts by cause (waiting): question 3, review 0, replan 0, permission 0, input 16, crash 1, idle 0, stop 0, subagent-stop 0, model 0, other 0
- router turns by cause: loop 354, relay 0, re-arm 9, other 12, relay cost $0.0000
- retriever re-asks: 0 of 1 retriever briefs repeat a lookup of the same run
- noise: 60 lines 4.1k chars — usage: : 40 lines/2.6k, No such file or directory: 20 lines/1.6k
- price: read $0.20/Mtok · 1h write $7.95/Mtok · output $19.87/Mtok (phase model mix)
- median requests after a read: 0
- carry/request: 1978 chars, 960 requests (prev 947 chars, 8741 requests, growth 109.0%)
- flag: carry per request grew 109% vs 3.40
- flag: 2 whole-plan reads by pa-expert
- flag: 42 tool-source reads by pa-claude, pa-coder, retriever-code, retriever-digest
  /home/musashi/bfm-decomp/tools/restruct.py  582 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  5.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  11.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  5.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  11.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lift_types.py  4.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lift_types.py  1.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lift_types.py  360 chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  13.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  13.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  8.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  3.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  11.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  8.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  3.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  11.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/readability_progress.py  13.7k chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  4.2k chars  pa-claude
  /home/musashi/bfm-decomp/tools/ghidra_mcp_start.sh  3.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_mcp_stop.sh  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_mcp_verify.sh  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_import.sh  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_apply_symbols.sh  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  882 chars  retriever-code
  /home/musashi/bfm-decomp/tools/lift_types.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_types.py  1.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_types.py  546 chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_types.py  1.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_types.py  546 chars  pa-coder
  /home/musashi/.claude/projects/-home-musashi-bfm-decomp/252d32b5-eb3b-4ca8-9931-8e47bb99cd41/tool-results/toolu_0138znYVwuYUjiHJDdTJMLvG.txt  133 chars  retriever-digest
  /home/musashi/bfm-decomp/tools/ghidra_rebuild.sh  2.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ImportAnnotations.java  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ExportAnnotations.java  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ExportAnnotations.java  18.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_scripts/ImportAnnotations.java  16.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/ghidra_rebuild.sh  9.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/struct_layout.py  18.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  4.1k chars  pa-coder

## Agent runs
- T4 | pa-claude | partner | claude-opus-5-5 | medium | ctx 132k | $3.105 | saved $12.02 | completed | parent 252d32b5
- T1 | pa-expert | expert | claude-opus-5-5 | medium | ctx 70k | $1.162 | saved $0.26 | completed | parent 252d32b5
- T2 | pa-expert | expert | claude-opus-5-5 | medium | ctx 57k | $0.807 | saved $3.36 | completed | parent 252d32b5
- T2 | pa-coder | coder | claude-opus-5-5 | medium | ctx 48k | $0.736 | saved - | completed | parent a73556e2
- T3 | pa-expert | expert | claude-opus-5-5 | medium | ctx 57k | $0.640 | saved $4.14 | completed | parent 252d32b5
- T3 | pa-coder | coder | claude-opus-5-5 | medium | ctx 64k | $1.513 | saved - | completed | parent ab627f19
- T4 | pa-expert | expert | claude-opus-5-5 | medium | ctx 84k | $1.488 | saved $8.81 | completed | parent 252d32b5
- T4 | pa-coder | coder | claude-opus-5-5 | medium | ctx 63k | $2.069 | saved $0.72 | completed | parent a7d120da
- T4 | pa-coder | coder | claude-opus-5-5 | medium | ctx 138k | $4.193 | saved $2.20 | completed | parent a7d120da
- T12 | pa-claude | partner | claude-opus-5-5 | medium | ctx 154k | $3.637 | saved - | completed | parent 252d32b5
- T5 | pa-expert | expert | claude-opus-5-5 | medium | ctx 83k | $1.324 | saved - | completed | parent 252d32b5
- T6 | pa-expert | expert | claude-opus-5-5 | medium | ctx 67k | $0.971 | saved - | completed | parent 252d32b5
- T7 | pa-expert | expert | claude-opus-5-5 | medium | ctx 100k | $1.864 | saved $7.20 | completed | parent 252d32b5
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 184k | $4.976 | saved - | completed | parent a5b793a1
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 58k | $0.791 | saved - | completed | parent a5b793a1
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 48k | $0.622 | saved $1.02 | completed | parent a5b793a1
- T9 | pa-expert | expert | claude-opus-5-5 | medium | ctx 62k | $0.779 | saved $3.01 | completed | parent 252d32b5
- T9 | pa-coder | coder | claude-opus-5-5 | medium | ctx 85k | $1.494 | saved $0.16 | completed | parent acf39ab0
- T8 | pa-expert | expert | claude-opus-5-5 | medium | ctx 70k | $1.142 | saved - | completed | parent 252d32b5
- T10 | pa-expert | expert | claude-opus-5-5 | medium | ctx 59k | $0.843 | saved $0.03 | completed | parent 252d32b5
- T13 | pa-expert | expert | claude-opus-5-5 | medium | ctx 69k | $0.873 | saved $0.39 | completed | parent 252d32b5
- T13 | pa-coder | coder | claude-opus-5-5 | medium | ctx 45k | $0.737 | saved - | completed | parent aafe72b2
- T10 | pa-expert | expert | claude-opus-5-5 | medium | ctx 65k | $0.897 | saved $0.00 | completed | parent 252d32b5
- T11 | pa-expert | expert | claude-opus-5-5 | medium | ctx 75k | $1.046 | saved - | completed | parent 252d32b5
- T11 | retriever-digest | retriever | claude-haiku-5-5 | medium | ctx 53k | $0.024 | saved - | completed | parent a67c4790
- T12 | pa-expert | expert | claude-opus-5-5 | medium | ctx 72k | $1.097 | saved - | completed | parent 252d32b5

## Discussions
- I3 | -> 3.43 Second look at the 9 expand-hardreg-var wall tags from 3.40 T20 (sub-tag heuristic checked on only 26 hand reads | deferred:3.43
- I4 | -> 3.43 37 `void` defs became `s32` in 3.41 T4 (callers read $v0) but their bodies have no `return`; give each a real re | deferred:3.43

## Deferred
- from T13: T10: run --check-casts --residue against the series census before the close snapshot so `uncovered` is not blank. T11: regenerate the timeline; both rows share a date and draw as a short step. (unconsumed)
- I3 (deferred:3.43): -> 3.43 Second look at the 9 expand-hardreg-var wall tags from 3.40 T20 (sub-tag heuristic checked on only 26 hand reads
- I4 (deferred:3.43): -> 3.43 37 `void` defs became `s32` in 3.41 T4 (callers read $v0) but their bodies have no `return`; give each a real re

## Changes
- 2026-11-07 router: T1 next -> done
- 2026-11-07 router: T2 next -> done
- 2026-11-07 router: 2026-11-07 partner: T8's wait-for is answered (developer): the headless Ghidra is the session-start MCP server and was meant to run. It stays stopped after T1's proofs until a task needs the live database; T7's proofs need :8080 free.
- 2026-11-07 router: T3 next -> done
- 2026-11-07 router: T4 next -> done
- 2026-11-07 planner: added T13 — return-type lies on the graph and in the day-1 guide
- 2026-11-07 router: T5 next -> done
- 2026-11-07 router: T6 next -> done
- 2026-11-07 router: T7 next -> done
- 2026-11-07 partner: T8 next -> blocked — wait-for is free text the loop cannot evaluate (R32 already answered); plan_edit has no way to clear the field; T9 and T13 run meanwhile
- 2026-11-07 router: T9 next -> done
- 2026-11-07 partner: T8 wait-for cleared to '-' by hand with the developer's OK (commit 024ca0ad03): the free text could not be evaluated, plan_edit cannot clear the field, and R32 was answered
- 2026-11-07 partner: T8 blocked -> next — wait-for cleared; R32 answered; MCP stopped and ready for the live import
- 2026-11-07 partner: T8 next -> done — developer confirmed COORD2_8001EFE0 is right in the live Ghidra; keep .run/P41/T8/ghidra.bak for now
- 2026-11-07 partner: T10 next -> queued — R56: T13's return-lie columns must land before T10's close snapshot; T13 runs first
- 2026-11-07 partner: T13 queued -> next — runs before T10 per R56
- 2026-11-08 router: T13 next -> done
- 2026-11-08 partner: T10: the developer approved (2026-11-07) stopping the MCP Ghidra with tools/ghidra_mcp_stop.sh (clean save and stop, never a kill) for the six --proof legs. Leave it stopped after the proofs; it is restarted after the close, then the developer runs /mcp (R49)
- 2026-11-08 router: T10 next -> done
- 2026-11-08 router: T11 next -> done
- 2026-11-08 router: T12 next -> done

## Plain-English Recap
Phase 3.41 made the type checks meaningful and mirrored the canonical types into Ghidra. `type_census --check` used to fail on all ~176k raw casts, so it could never pass. It now asserts the done-criteria: no unlisted duplicate struct layouts, no definitions outside the canonical headers, no dead names, controls 4/4, and no unledgered lying declaration. Raw casts are still printed and stay gated by `--check-casts --residue`, and the check runs inside `make tools-health`. Return-type lies, where a declaration's return type disagrees with the definition, are now detected. They went from 273 functions over 100,266 declaration lines to 19 functions over 9,302 lines. Each of the 19 is a width or sign mismatch kept in config/lying_exceptions.tsv with the instruction that moves. `lever_census --check` now requires every `// !FAKE:` marker to name its instrument (1,853 attributed, 0 bare). A new tool, tools/ghidra_types.py, writes 7,151 canonical types (structs, typedefs, unions) from the headers into per-program Ghidra rows. Their field offsets and sizes equal gcc's, a staleness `--check` sits in tools-health, and all six rebuild proofs pass. The live Ghidra database holds the types, and the developer confirmed COORD2_8001EFE0 is right. Three 3.40 tool bugs were fixed. The readability series and README graph now show return lies, and the day-1 guide teaches one shared prototype header. Story §10, retrospective §7 and the wiki run to Phase 41.

Milestone gate at f4b1fbad3d, from a clean tree: R22 218/218 run alone; tools-health OK; type_census --check --check-structs --check-casts --residue rc 0; lever_census --check --strict --residue rc 0; doc_links --strict 0; ghidra_rebuild --proof PROOF PASS for all six programs.

Open items:
- The developer pushes the archive clone (b9534ed) and the repo.
- The MCP Ghidra is stopped; restart it with tools/ghidra_mcp_start.sh, then the developer runs /mcp.
- .run/P41 holds ~2.4 GB of scratch plus the 1 GB ghidra.bak, which the developer keeps for now.
- For 3.43: 37 s32 definitions with no return statement, and the 9 expand-hardreg-var wall tags.
- The PA3 wait-for bug report is the developer's to file.
