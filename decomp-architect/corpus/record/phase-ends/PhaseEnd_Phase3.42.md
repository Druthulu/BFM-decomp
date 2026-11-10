# PhaseEnd — Phase 3.42: Rename harness and shared-function form (implements Gen 3.42)
Approved: 2026-11-08 | Closed: 2026-11-10 | Planner: claude-opus-5-5/medium | Tasks: 12 done, 0 superseded

## Milestone
Milestone: a rename scanner (R32) asserts every reference to a renamed symbol rewritten, proven on one known rename and one planted miss; 3,801 cross-address classes in the parameterized `SHARED_FN` form (0 left: `PY tools/share_census.py --check --scope all --strict-macros --strict-text` reports S1 violations 0 and an empty cross-address bucket) and the 20 trampoline families shared (their `config/verbatim_manifest.json` rows show 0 private copies; `PY tools/verbatim_check.py --strict` OK); a leverage ranking of data symbols and functions (xrefs, struct ownership, shared-body fan-out) written with its denominator; R22 218/218 (`make clean && make extract-all JOBS=16 && make check-all JOBS=16` prints `218 passed, 0 failed of 218`); ghidra `--proof` PASS (`tools/ghidra_rebuild.sh <prog> --proof` for all six programs in `config/ghidra/`).
Confirmed by the developer at the close.

## Tasks
- T1 — phase-start baselines and environment check | Done: 3.42 baselines measured: R22 218/218 and tools-health OK at bcd6a3f2a3; cross-address bucket 3,801 / 30,347 / 11,340 equals R83; six Ghidra proofs carry. Summary: The task re-measured every number the phase starts from before anything changes. The build is byte-identical for all 218 binaries and the health suite passes after one corpus refresh. The deferred cross-address work matches the milestone exactly, so the tree has not moved. The Ghidra proofs from 3.41 still hold because none of their inputs changed. | commit: bcd6a3f2a3 | tasks/T1.md | logs/T1.md
- T2 — names ledger with the guess_ tier, and the rename scanner (R32) | Done: config/names.tsv (rule 1's 11 fields, header only) and tools/rename_scan.py (--selftest, --ledger, --spec/--range scan) exist; both ledger checks run in tools-health, OK. Summary: The project now has a place to record the evidence behind every name, and a scanner that proves a rename left no stale mention behind. The scanner looks for every spelling of the old name and its address across all tracked files and makes each hit account for itself as rewritten, history or stale; anything it cannot classify fails. The ledger check fails on a guess name with no recorded basis and on a row for a name that no longer exists. Today 1,083 curated names have no citation row; that is printed, and a flag turns it into a gate for 3.43. | commit: 656798c20a | tasks/T2.md | logs/T2.md
- T3 — rename tool and the scanner's two controls (known rename, planted miss) | Done: tools/rename_sym.py applies a rename spec end to end; the known rename func_80037004 -> guess_ClearTbl40 passes the positive control and a planted miss fails the scanner, both in a scratch worktree; no rename landed. Summary: The project now has one tool that performs a rename: it writes the symbol line, rewrites every live mention, records the evidence row and says which binaries and Ghidra programs need follow-up. It was proven on a real function in a throwaway copy of the repo: the build stayed byte-identical, the scanner found nothing stale, and an independent search agreed line for line. Leaving one mention the build cannot see unrewritten kept the build green and made the scanner fail on exactly that line, which is the proof the scanner catches what the byte gate misses. | commit: 7ceaea748f | tasks/T3.md | logs/T3.md
- T4 — the parameterized SHARED_FN writer, ledger re-keying, and a pilot batch | Done: share_body.py --bucket cross writes one SHARED_FN header per cross-address class and re-keys every ledger in the batch; 122 C classes converted, tools-health OK, R22 218/218. Summary: Functions whose identical bytes sit at several addresses can now be given one source: a header written once per class, and at each old copy a three-line include that names the function. The tool also moves the copies' bookkeeping (residue, cast and lying ledgers) onto the header in the same batch, which the first full pilot showed is needed in more places than the plan listed. A pilot of 122 classes is converted with every gate green, and the shared-source violations fell by exactly 122. | commit: d05ea62517 | tasks/T4.md | logs/T4.md
- T5 — convert the C-verdict cross-address classes | Done: every verdict-C cross-address class (2,026 after T4's pilot) is in the SHARED_FN param-include form; 0 rejected, 0 excepted; tools-health OK, R22 218/218 at 02d5ac206b. Summary: The remaining functions whose identical bytes sat at several addresses, each with a single text, now have one source each: a class header included at every old copy under its own name. The work ran unattended in 17 gated batches, every one green on the first try, so no class needed the developer's stop rule. The shared-source violation count fell from 3,667 to 1,641, exactly by the 2,026 classes converted. | commit: acddc5eaa0 | tasks/T5.md | logs/T5.md
- T6 — convert the D- and B-verdict cross-address classes, then gate S1 over the full scope | Done: 1,066 of 1,641 cross-address classes share one text; the other 575 are ledgered one row each; S1 gates --scope all with 0 violations. Summary: The task turned cross-address duplicate functions into one shared text included at every address, each choice gated byte-identically on every binary. After the first sweep 729 classes resisted; under R92 the developer chose a repair round (option A), which converted 154 more by carrying missing data externs into the shared header and retrying misparsed or collateral rejects. The 575 still rejected are ledgered with their measured reason, and the S1 gate in tools-health now checks the full scope, where it reports 0 violations ("0 left" = 0 un-ledgered). | commit: ab62f2f6a4 | tasks/T6.md | logs/T6.md
- T7 — share the 20 scratchpad trampoline families | Done: each of the 20 trampoline families has one source src/shared/ov/<F>.h (params SHARED_FN, SHARED_SLOT) included at all 141 copies; manifest rows private_tus 0, --strict OK, tools-health OK, R22 218/218. Summary: The twenty hand-written stack-switch routines that every overlay carried its own copy of now each have one source file, included at every former copy. Their copies turned out to differ only in one per-overlay data address, not in the function they wrap, so the shared file takes that address as its parameter. Two checking tools had to learn the new spelling, and every gate is green. | commit: 13c6f9ab64 | tasks/T7.md | logs/T7.md
- T8 — leverage ranking of data symbols and functions, with its denominator | Done: `tools/leverage_rank.py` writes docs/leverage.md and the full ranked docs/leverage.tsv (190,849 units) from our own build's relocations, struct ownership and share-class fan-out; unattributed 0, controls 3/3, `--check` byte-identical. Summary: The project now has a measured answer to "which names buy the most readability": every function body (one per share class) and every data address is ranked by how many places in the deduplicated source its name would appear, plus credit for struct types it anchors and a damped bonus for bodies shared across many binaries. Counting is per unique body, so the ranking stays put while bodies move into shared headers. Every one of the 3.36 million relocations in the build is accounted for, either to a unit or to a named exclusion, and three independent checks agree. 3.43's naming list is the top 500 of the units not yet named; those 500 cover about 35% of all references. | commit: - | tasks/T8.md | logs/T8.md
- T9 — the record: cookbook, decision log, levers prose, wiki, tool index, kit corpus, snapshot skill | Done: four decision-log entries, levers §7 de-dup prose, dedup wiki param-include section, new wiki page Names-and-renames linked from the sidebar, card Tools rows, d1-snapshot skill runs --check-casts --residue, C0563; kit-corpus, doc_links --strict, tools-health all green. Summary: The phase's work is now on the public and internal record. The decision log explains why cross-address duplicates got one class-named header, what the names ledger and its guess_ tier require, how the rename scanner proves its coverage, and how names are ranked. The levers page explains that the 3-site drop this phase (1,853 to 1,850) comes from one two-copy class now counted once in its header, not from a removed lever. The readability snapshot skill now writes the residue census with the type census, so the series' uncovered column is never blank. | commit: - | tasks/T9.md | logs/T9.md
- T10 — milestone gate (Phase 3.42) | Done: every 3.42 milestone leg is green at 2cb3493055; series snapshots, timeline and P3.42 ledger backups written. Summary: The phase's milestone checks all pass on one clean commit. The build is byte-identical for all 218 binaries and the health suite passes. Every cross-address duplicate is now either shared or ledgered with a reason, and the twenty trampoline families have no private copies left. The rename machinery passes its own tests, and the test rename was mirrored into a throwaway Ghidra project and read back without touching the real database. All six Ghidra rebuild proofs pass, and the readability and lever series have their 3.42 rows. | commit: - | tasks/T10.md | logs/T10.md
- T11 — phase-close docs: story, retrospective, wiki, README (Phase 3.42) | Done: story §10 has its Phase 42 part and §11 the P3.42-close row; retrospective §7 runs to Phase 42 in all four paragraphs; wiki next-steps rules 1 and 3 carry Phase 42; timeline and progress regenerated; doc_links --strict 0 pending / 0 broken. Summary: The public record now tells the story of Phase 42: the deferred cross-address duplicates became one source each or a ledgered row with its reason, the trampoline families lost their private copies, and the rename machinery was built and tested without landing a name. The retrospective adds what the phase believed wrongly, what failed, what it cost and what it would do sooner. The small drops in lever and raw-cast counts are explained as copies collapsing into shared headers, not as new work. | commit: - | tasks/T11.md | logs/T11.md
- T12 — phase cleanup (Phase 3.42) | Done: everything the repo still needed from .run/3.42/ now lives in docs/ops/; the rest of the scratch (4.2 GB) is deleted, logs/ kept for the close; R22 218/218 and tools-health OK. Summary: Twenty shared trampoline headers named a scratch script as their generator. That script is now archived in an operations note, and the headers point to it. The share batch cycle tool no longer writes into this phase's scratch folder, so later phases get their own. Everything else in the phase's scratch area was temporary working material whose lessons are already in the cookbook, so it was deleted. | commit: - | tasks/T12.md | logs/T12.md

## Decisions that still bind
- T2 — a rename lands only with `rename_scan.py --range HEAD..` (or `--spec`) at 0 stale and 0 unclassified, and every guess_ name with a names.tsv row carrying a basis (gated by `--ledger` in tools-health).
- T3 — share headers src/shared/<space>/func_<VRAM>(__h8).h are address keys and are never renamed by a function rename; the scanner classes header-file tokens address-key.
- T3 — address-only mentions pass only in the closed ADDRESS_KEYED list; generator-made func_<ADDR> names pass only in NAMES_FROM_VRAM (docs/duplicates.md); a curated old name there is still stale. Extending either list is a reviewed edit, never a rename-time convenience.
- T4 — cross-address headers are named by class, src/shared/<space>/cls_<h[:12]>.h (multi/ when flag F), registry id X_<h[:12]>; a rename touches only `#define SHARED_FN` lines and member names.
- T4 — a gate-red cross class is undone at every site and listed in batch_<label>.json, never ledgered in dedup_exceptions.tsv, so violations fall exactly by converted classes and R92's bucketing stays with T5/T6.
- T6 — "0 left" for the shared form = 0 un-ledgered (developer, option A; plan ## Changes).
- T7 — an asm-body family varying in one symbol is shared with SHARED_SLOT stringified in the template; header named src/shared/ov/func_<VRAM>.h (same address fleet-wide); tools key a SHARED_FN header def by its file stem.
- T8 — references = relocations of our own built objects, parsed in Python (REL addends); objdump -r is the independent raw-count control, never the parser.
- T8 — units are one per share class (h_exact) for functions, `raw:<space>:<addr>` for a call target with no sig row that starts an ELF FUNC/global symbol, and (space, addr) for data; space = vram base of the image holding the address (main, resident, the slot base; `abs` outside every image).
- T8 — score = (refs + own) x (1 + log10(fan)); refs = unique-body non-HI16 references; own = sum over held struct types of reach/holders; fan = instances (func) or referencing binaries (data). Reasons are in docs/leverage.md ## Weights.
-

## Rules proposed
- (none)

## Cookbook entries added
C0555 | Prove a rename complete with rename_scan (R32 coverage) | rename,symbol,names-ledger,guess,r32 | 2026-11-08 | 3.42/T2 | P3.42 T2.c1
C0556 | Apply and prove a rename in a scratch worktree (rename_sym + controls) | rename,symbol,worktree,gate_main,r32 | 2026-11-08 | 3.42/T3 | P3.42 T3.c1
C0557 | Cross-address share: the SHARED_FN class header and its traps | share,dedup,shared_fn,cross-address,residue | 2026-11-08 | 3.42/T4 | T4.c1 d3f940420a
C0558 | One-text sharing of differing cross copies: dead types, lies, alias names | share,dedup,shared_fn,cross-address,type_census,lying | 2026-11-09 | 3.42/T6 | T6.c1 92473260c4
C0559 | Asm-body family varying in one symbol: SHARED_SLOT stringify header | share,dedup,shared_fn,trampoline,verbatim,asm | 2026-11-09 | 3.42/T7 | T7.c1 13c6f9ab64
C0560 | sys.exit in a multiprocessing.Pool worker hangs Pool.map; raise instead | python,multiprocessing,tools,harness | 2026-11-10 | 3.42/T8 | -
C0561 | Independent reloc-count controls: a fleet-unique control symbol; objdump -r lacks REL addends | reloc,objdump,controls,leverage,symbol | 2026-11-10 | 3.42/T8 | -
C0562 | Generated doc with byte-for-byte --check: no volatile provenance; new docs need a Reference-index row | docs,generated,check,doc_links,tools-health | 2026-11-10 | 3.42/T8 | -
C0563 | A share batch lowers lever/cast site counts by counting a header once, not by removing sites | share,dedup,lever,census,metrics | 2026-11-10 | 3.42/T9 | P3.42 T9 levers prose
C0564 | Prove a rename's Ghidra mirror in a scratch project, live DB untouched | ghidra,rename,symbol,proof,worktree | 2026-11-10 | 3.42/T10 | P3.42 T10

## Research
R3.42-001 | phase 3.42 plan, `## Interfaces` for the milestone-gate task (deferred P3.41-1: `uncovered` blank in readability series) | Milestone-gate series interfaces (readability, timeline, levers, ghidra, tools-health, ledger backup) | readability, timeline, lever, ghidra, tools-health, ledger-backup, census, interfaces | retriever-code | 2026-11-08 | 94 lines
R3.42-002 | 3.42 plan ## Interfaces: rename scanner, symbol-file renames mirrored to Ghidra, leverage ranking with denominator | Rename / symbol machinery interfaces (for 3.42 plan ## Interfaces) | rename, symbols, ghidra, xref, type_census, lint, interfaces | retriever-code | 2026-11-08 | 65 lines
R3.42-003 | pa-planner phase 3.42 ## Interfaces (R32 rename scanner candidate set, guess_ ledger, leverage ranking denominator) | Rename machinery follow-up: downstream reach, C spellings, xref sources, denominators, struct inputs | rename, symbols, splat, lint_symbol_refs, ghidra, reloc, type_census, denominator | retriever-code | 2026-11-08 | 99 lines
R3.42-004 | phase 3.42 plan, ## Interfaces and ## Risks for the shared-function conversion batches (pa-planner) | Body move from src/<bin>/<file>.c to a shared header: what the per-site ledgers and gates do | lever-census, type-census, restruct, verbatim-check, residue, lying-exceptions, tools-health, shared-header | retriever-code | 2026-11-08 | 77 lines
R3.42-005 | 3.42 plan ## Interfaces: exact file:line interfaces for the shared-function conversion (registry, ledger, manifest trampoline rows, census/share/cycle tools, src/shared layout, cookbook C0502) | Share registry, exceptions ledger, trampoline rows, and share tooling (3.42 interfaces) | share-registry, dedup, exceptions, verbatim-manifest, trampoline, share_census, share_body, phase-3.42 | retriever-code | 2026-11-08 | 57 lines
R3.42-006 | pa-planner, phase 3.42 plan ## Context, ## Risks and task sizing | Phase 3.42 plan inputs: cross-address deferral, trampolines, gate timings, names ledger, P3.41-1 | phase-3.42, names-phase, shared-function, cross-address, trampoline, gate-timing, names-ledger, guess-tier, readability-snapshot | retriever-digest | 2026-11-08 | 32 lines
R3.42-007 | digest Phase 3.42 task summaries, PHASE_PLAN Changes, and git reflog for the public phase-close record | Phase 3.42 close record digest (for story §10/§11, retrospective §7) | phase-3.42, phase-close, cross-address, trampolines, rename, leverage, retrospective | retriever-digest | 2026-11-10 | 116 lines

## Audit
- seed: median 25k, max 27k, n=13 (phase 3.42)
- previous phase 3.41: median 24k, growth 3.3%
- CLAUDE.md: 1304 bytes (unchanged)
- .claude/skills/commit-task-autostage/SKILL.md: 1024 bytes (unchanged)
- .claude/skills/d1-snapshot/SKILL.md: 1396 bytes (+464)
- .claude/skills/pa-external-agents/SKILL.md: 11144 bytes (unchanged)
- .claude/skills/pa-planning/SKILL.md: 8277 bytes (unchanged)
- .claude/skills/project-architect/SKILL.md: 13748 bytes (unchanged)
- .claude/skills/restruct-cycle-watch/SKILL.md: 1119 bytes (unchanged)
- .claude/skills/retire-doc-consumers/SKILL.md: 927 bytes (unchanged)
- .claude/skills/tools-edit-kit-corpus/SKILL.md: 990 bytes (+234)
- .claude-state/memory/MEMORY.md: 60 bytes (unchanged)
- HOW_WE_WORK.md: 9394 bytes
- cookbook/INDEX.md: 252521 bytes
- rules/INDEX.md: 15616 bytes
### Carry audit — phase 3.42 (2026-11-09T00:12:17Z → open UTC, 1 sessions, 1676 requests)

| file (read) | chars | n |
|---|---|---|
| share_body.py | 194.3k | 17 |
| rename_scan.py | 58.7k | 10 |
| HEAD | 58.0k | 2 |
| leverage_rank.py | 55.9k | 7 |
| share_census.py | 52.4k | 22 |
| TASK_PROGRESS.md | 45.8k | 3 |
| argcheck.py | 39.2k | 6 |
| type_census.py | 35.6k | 10 |
| plan.txt | 27.3k | 2 |
| share_body_cycle.sh | 18.2k | 4 |
| file (write) | chars | n |
|---|---|---|
| share_body.py | 40.1k | 38 |
| leverage_rank.py | 24.0k | 2 |
| rename_scan.py | 18.2k | 8 |
| rename_sym.py | 13.9k | 2 |
| retriever-phase-342-close-record.md | 12.6k | 1 |
| T6.c3.md | 7.5k | 1 |
| convert.py | 7.1k | 1 |
| T6.c1.md | 6.5k | 1 |
| result kind | chars | n |
|---|---|---|
| bash other | 915.5k | 511 |
| Read | 857.3k | 197 |
| Grep | 420.9k | 197 |
| tools/plan_edit.py | 284.0k | 23 |
| tools/share_body.py | 237.7k | 78 |
| run.sh | 158.0k | 189 |
| tools/share_body_cycle.sh | 99.3k | 24 |
| tools/share_census.py | 91.3k | 32 |
| tools/type_census.py | 77.9k | 53 |
| tools/outline.py | 63.4k | 8 |
- spilled: 3 results, 464.5k chars on disk, 0 read whole
- whole reads over 20.0k: 0
- seed floor: retriever-code 6,927 (n 13, prev 6,927) · retriever-digest 6,893 (n 9, prev 6,893)
- outline credit: 24 outlines · 12 followed by a ranged read · 566.5k chars credited
- warm pings: 244 pings over 20 runs, 42 warmed waits over the TTL, rewrites across warmed waits 0, waits past the cap 2, cost: pings $4.3412 + relay $0.0000 + re-arm $0.0000 = $4.3412 vs rewrites replaced $20.0361, cheaper than one rewrite: yes, undelivered 0
- toasts by cause (waiting): question 1, review 0, replan 0, permission 0, input 9, crash 0, idle 0, stop 0, subagent-stop 0, model 0, other 0
- router turns by cause: loop 718, relay 0, re-arm 20, other 4, relay cost $0.0000
- retriever re-asks: 0 of 2 retriever briefs repeat a lookup of the same run
- noise: 75 lines 5.6k chars — usage: : 57 lines/4.1k, No such file or directory: 18 lines/1.4k
- price: read $0.20/Mtok · 1h write $7.96/Mtok · output $19.89/Mtok (phase model mix)
- median requests after a read: 0
- carry/request: 2202 chars, 1676 requests (prev 8402 chars, 960 requests, growth -73.8%)
- flag: 1 whole-plan reads by pa-expert
- flag: 107 tool-source reads by pa-claude, pa-coder, pa-expert, retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  2.9k chars  pa-expert
  /home/musashi/bfm-decomp/tools/lever_census.py  824 chars  pa-expert
  /home/musashi/bfm-decomp/tools/restruct.py  582 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  19.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  307 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  799 chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  1.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  2.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  5.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  11.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/rename_scan.py  8.1k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  4.2k chars  pa-expert
  /home/musashi/bfm-decomp/tools/argcheck.py  13.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  8.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  3.7k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  11.1k chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  4.2k chars  pa-claude
  /home/musashi/bfm-decomp/tools/share_census.py  5.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/corpus.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  5.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/corpus.py  2.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  849 chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  849 chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  344 chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  636 chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  134 chars  retriever-code
  /home/musashi/bfm-decomp/tools/share_census.py  281 chars  retriever-code
  /home/musashi/bfm-decomp/.claude/skills/d1-snapshot/SKILL.md  989 chars  retriever-code
  /home/musashi/bfm-decomp/tools/timeline.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/leverage_rank.py  292 chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  292 chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/argcheck.py  4.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  1.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  648 chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  12.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  14.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  12.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  14.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/leverage_rank.py  2.3k chars  pa-coder
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
  /home/musashi/bfm-decomp/tools/share_body.py  15.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  17.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  26.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  15.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  17.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  26.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  3.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  882 chars  retriever-code
  /home/musashi/bfm-decomp/tools/lift_types.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/argcheck.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/rename_scan.py  10.0k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  5.5k chars  pa-expert
  /home/musashi/bfm-decomp/tools/rename_scan.py  5.7k chars  pa-expert
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
  /home/musashi/bfm-decomp/tools/share_body.py  19.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body_cycle.sh  5.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  13.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  5.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  5.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_census.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/share_body.py  3.1k chars  retriever-code

## Agent runs
- T5 | pa-claude | partner | claude-opus-5-5 | medium | ctx 108k | $2.144 | saved $22.17 | completed | parent 252d32b5
- T1 | pa-expert | expert | claude-opus-5-5 | medium | ctx 62k | $1.115 | saved $0.61 | completed | parent 252d32b5
- T1 | pa-expert | expert | claude-opus-5-5 | medium | ctx 62k | $0.980 | saved - | completed | parent 252d32b5
- T2 | pa-expert | expert | claude-opus-5-5 | medium | ctx 79k | $1.178 | saved $2.13 | completed | parent 252d32b5
- T2 | pa-coder | coder | claude-opus-5-5 | medium | ctx 64k | $1.168 | saved - | completed | parent a21bfe61
- T3 | pa-expert | expert | claude-opus-5-5 | medium | ctx 89k | $1.504 | saved $2.69 | completed | parent 252d32b5
- T3 | pa-coder | coder | claude-opus-5-5 | medium | ctx 147k | $3.983 | saved - | completed | parent a8a829ad
- T4 | pa-expert | expert | claude-opus-5-5 | medium | ctx 100k | $1.742 | saved $32.64 | completed | parent 252d32b5
- T4 | pa-coder | coder | claude-opus-5-5 | medium | ctx 132k | $2.805 | saved - | completed | parent a2243a12
- T4 | pa-coder | coder | claude-opus-5-5 | medium | ctx 99k | $2.083 | saved $10.96 | completed | parent a2243a12
- T4 | pa-coder | coder | claude-opus-5-5 | medium | ctx 75k | $1.247 | saved $0.36 | completed | parent a2243a12
- T5 | pa-expert | expert | claude-opus-5-5 | medium | ctx 62k | $0.838 | saved $4.80 | completed | parent 252d32b5
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 76k | $1.809 | saved $0.42 | completed | parent a2929a04
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 220k | $11.141 | saved $1.72 | completed | parent a1fe4aac
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 118k | $2.895 | saved - | completed | parent a1fe4aac
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 173k | $10.869 | saved $1.16 | completed | parent a1fe4aac
- T12 | pa-claude | partner | claude-opus-5-5 | medium | ctx 116k | $1.984 | saved - | completed | parent 252d32b5
- T6 | pa-expert | expert | claude-opus-5-5 | medium | ctx 73k | $1.190 | saved $4.79 | completed | parent 252d32b5
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 98k | $2.722 | saved $1.93 | completed | parent a114b585
- T7 | pa-expert | expert | claude-opus-5-5 | medium | ctx 107k | $2.015 | saved $5.61 | completed | parent 252d32b5
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 138k | $3.458 | saved $0.33 | completed | parent a05b95d5
- T8 | pa-expert | expert | claude-opus-5-5 | medium | ctx 161k | $3.831 | saved $5.78 | completed | parent 252d32b5
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 103k | $2.273 | saved - | completed | parent a605cbfb
- T8 | retriever-code | retriever | claude-haiku-5-5 | medium | ctx 42k | $0.014 | saved - | completed | parent a605cbfb
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 138k | $3.118 | saved - | completed | parent a605cbfb
- T9 | pa-expert | expert | claude-opus-5-5 | medium | ctx 111k | $2.117 | saved - | completed | parent 252d32b5
- T10 | pa-expert | expert | claude-opus-5-5 | medium | ctx 84k | $1.431 | saved - | completed | parent 252d32b5
- T11 | pa-expert | expert | claude-opus-5-5 | medium | ctx 76k | $1.048 | saved $0.01 | completed | parent 252d32b5
- T11 | retriever-digest | retriever | claude-haiku-5-5 | medium | ctx 79k | $0.032 | saved - | completed | parent a70dcdbe
- T12 | pa-expert | expert | claude-opus-5-5 | medium | ctx 75k | $1.127 | saved - | completed | parent 252d32b5

## Discussions
- (none)

## Deferred
- from T12: none; MCP Ghidra restart and /mcp after the close (T10). (unconsumed)

## Changes
- 2026-11-08 developer: Developer decides answered 2026-11-08: yes to both. (1) T10 may stop the MCP Ghidra once with tools/ghidra_mcp_stop.sh (clean save+stop, never a kill) for its Ghidra steps; it stays stopped until the close, then ghidra_mcp_start.sh and Claude asks for /mcp. (2) Shared-form stop rule is 0 left: classes still rejected after repair stop T5/T6 after bucketing by reason; Claude brings the buckets to the developer.
- 2026-11-08 router: T1 next -> done
- 2026-11-08 router: T2 next -> done
- 2026-11-08 router: T3 next -> done
- 2026-11-08 router: T4 next -> done
- 2026-11-09 router: T5 next -> done
- 2026-11-09 developer: R92 amended at T6's stop (developer picked option A): T6 runs one repair round on the cheap buckets (undeclared data 160: extern in the shared header; unparsed diagnostic 28 with the parser fixed; one-batch-skip collateral retried), then ledgers every class still rejected in config/dedup_exceptions.tsv, one row per class with its measured reason and evidence, and widens Makefile:301 tools-health S1 to --scope all with those exceptions. The milestone's and T10's '0 left' now read: S1 violations 0 and the cross-address bucket empty except ledgered dedup_exceptions rows, counted by reason in the T6 summary.
- 2026-11-09 router: T6 next -> done
- 2026-11-09 router: T7 next -> done
- 2026-11-10 router: T8 next -> done
- 2026-11-10 router: T9 next -> done
- 2026-11-10 router: T10 next -> done
- 2026-11-10 router: T11 next -> done
- 2026-11-10 router: T12 next -> done

## Plain-English Recap
Phase 3.42 built the groundwork for naming; no real name landed (that is 3.43). Cross-address families (functions whose identical bytes sit at several addresses) went from 3,801 to 0 unaccounted. 3,214 now have one shared SHARED_FN source included at every address, 12 are twin-covered, and 575 are ledgered in config/dedup_exceptions.tsv with a measured reason (TU-CONFLICT 282, RETURN-LIE 206, DEAD-TYPE 87). This follows the developer's option A at T6's R92 stop: one repair round, then ledgering. Private copies fell from 11,340 to 2,169, and tools-health's S1 check now runs over every address. The 20 scratchpad trampoline families have one source each (133 private copies each down to 0), parameterized by a per-overlay data symbol rather than the callee. The rename machinery is in place: config/names.tsv (with the guess_ tier), tools/rename_sym.py, and tools/rename_scan.py (R32), which passed a clean known rename and caught a planted miss the byte gate could not see. The rename was also mirrored into a scratch Ghidra project, with the live project untouched. tools/leverage_rank.py writes docs/leverage.md/.tsv, which ranks 190,849 units with every relocation attributed; 3.43's top 500 cover 35.5% of references. The d1-snapshot skill now runs the cast check first (P3.41-1).

Milestone gate at 2cb3493055, from a clean tree: R22 218/218 run alone; tools-health OK; share_census --check --scope all --strict-macros --strict-text 0 violations (575 ledgered); verbatim_check --strict OK; rename_scan --selftest and --ledger OK; leverage_rank --check IDENTICAL; audit_public 0; ghidra_rebuild --proof PROOF PASS for all six programs.

Open items:
- The developer pushes the archive clone (34a3181), then the repo.
- The MCP Ghidra is stopped. After the close, Claude runs tools/ghidra_mcp_start.sh and asks the developer for /mcp.
- For 3.43: rerun leverage_rank after real renames, and decide whether the wiki's Names-and-renames example keeps func_80037004's old name.
- The 575 ledgered families need struct and declaration cleanup before they can share a text.
