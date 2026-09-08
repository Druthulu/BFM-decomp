# PhaseEnd — Phase 33.5: Docs consolidation, the wiki as source of truth, the tracked-`.run/` prune, the memory reconciliation, and the day-one decomp kit (sub-phase before the flip)
**Date:** 2026-09-08 · **Project Version:** 1.32.1 · **Phase Status:** Complete (milestone pre-approved by Drew 2026-09-08 "if everything passes, you have my approval for milestone met and phaseend" — everything passed; gate 2) · **Generation:** Gen2 (a sub-phase between 33 and 34; the flip and the Gen2 exit remain Phase 34)

> Gen2 sub-phase 33.5 (…→33→**33.5**→34). Chartered by Drew on 2026-09-07 while reviewing `docs/` ahead of the flip: the tree was not
> publishable as a *documentation set*, the tracked `.run/` carried 172 files by index inertia and two ROM-derived listings, the
> working knowledge that ran the project lived one-third in `~/.claude`, and nothing packaged the project's own day one for the next
> decompilation. Ran **3 sessions (S90–S92, 2026-09-07 → 2026-09-08)** and **26 commits** (`39d524991..845fd8848`; baseline `80d45b29b`,
> Drew's Phase-33 close). The granular trail — every task's verify lines, the two amendments, the five dry-runs, the mining harvest —
> is at **`phase-ends/logs/Phase33.5.md`** (R19, on demand). Owner decisions (Drew): gate 1 (2026-09-07, plan mode, Max; the nine
> decisions in the plan — kit in-tree now and split later, v1.32.1, sunset by `git mv` + review, the kit opens with "install
> ProjectArchitect 2.0 first", memories stay in `~/.claude`, the two disassembly listings untracked with an audit rule and no second
> rewrite, relative wiki links, only what git tracks under `.run/`, README's `docs/` links stay); **R74–R83 ratified at gate 1**;
> amendment 1 (task 13.5, the tools audit, Drew's retirement criterion); amendment 2 (the two dictionaries in-tree now); the S91-b
> types hindsight into task 14; amendment 3 (task 14.5: "do all three" — the record, the coverage check, the worklog pass); the
> health-chain question (S92); gate 2 pre-approved conditionally.

## Build Log

**The phase in one line:** the wiki became the single source of truth (five new pages + an archive index; 59 documents and 34
tools retired into indexed sunset folders; a link checker that derives its allow-list and refuses the archive), the tracked `.run/`
went from 1,086 files to flip-ready (218 untracked, the two ROM listings out, a content check with both controls), the memory store
was reconciled and seeded, and **the day-one decomp kit `decomp-architect/` was built, dry-run installed five times, and then made to
hold the whole of the project's experience** — three verbatim dictionaries (the tools by need, the cookbook, the record), 80 kernels
and 67 rules with provenance, a coverage check that refuses a silent gap in the distillation, and a final pass over every phase
worklog that recovered 143 lessons banked nowhere else.

**Files created/changed and complete — do not recreate** (category summaries; the per-commit list is `git log 39d524991..845fd8848`
and the archived log):

- **The wiki (source of truth):** `docs/wiki/Docs-and-scratch-conventions.md`, `The-ROM-firewall.md` (with the copyable `.gitignore`
  fence — one source, two copies with the kit's template), `Reference-index.md` (the only sanctioned wiki→`docs/` link site; 47 rows),
  `Where-the-project-goes-next.md`, `Start-a-new-decomp-project.md`, `Archive-index.md`; `Home.md` rewritten; `_Sidebar.md` sections;
  Contributing "AI use — conduct"; the six INTEGRATE documents folded into `The-matching-workflow`, how-to ch.02/03/05/07/09 and
  `wave-playbook.md` §5 (task 5, three read-only diff agents); 11 referrers re-pointed. Wiki 19 pages + 13 chapters; render 32 / 0 unlisted.
- **The archive:** `docs/sunset/` — 59 files by `git mv` (25 root documents, `distill/` 2, `history/` 4, `tool-designs/` 11,
  `generated-snapshots/` 17) + `README.md` (the ☐ review table; deletion is Drew's); `tools/sunset/` — 34 retired tools (28 superseded
  with named successors, 6 one-offs with named products) + `README.md`; `docs/history/README.md` and DIGEST §4 refreshed. `docs/`
  outside wiki/how-to/sunset: 65 files, every one a Reference-index or README target.
- **The checkers:** `tools/doc_links.py` (six checks: links + the pending list; the archive refusal; wiki-first against the index-derived
  allow-list; coverage ⊆; TRACKED/UNTRACKED citations by `git ls-files`, strict only for wiki pages, `--disk` for the R39 control;
  wiki-first warnings), `tools/wiki_render.py --selftest` reachability, `tools/timeline.py` wired into `report BINARY=main` +
  `audit-digest --check`, `tools/gitignore_template_check.py`, `tools/audit_public.py` check 4 (CONTENT: contiguous disassembly-shaped
  runs ≥ 64 lines; both R39 controls recorded) + `tools/public_rewrite/untracked_after_rewrite.txt` (audit-only; `purge_set.txt`
  untouched), `tools/kit_lint.py` (six checks; `--selftest` = the R39 control), `tools/tool_census.py` (two agreeing enumerations,
  the authored `config/tool_dictionary.tsv`, `docs/tool-index.md` generated, the kit's manifest and the three corpora generated —
  `make kit-corpus`, `--check` in tools-health), `tools/kit_coverage.py` (+ `config/kit_coverage_map.tsv`). The 13 dangling cookbook
  cites fixed; `CLAUDE.md` lines 11/61/the effort sentence; five tool docstrings and six document banners corrected (tasks 1–2).
- **Tracked `.run/`:** 1,086 → 868 by `git rm --cached` of exactly what the narrowed `.gitignore` says (172 inertia files, 44 finished
  logs, the two `fable_cd4` listings) → 925 at close with this phase's own evidence allowlisted by dated blocks: `.run/P33.5/kit-dryrun/`
  (answers, expected manifest, `judge.py`, five runs' logs/manifests/verdicts/guardrails), `.run/P33.5/tools_audit/`,
  `.run/P33.5/log-mining/` (BRIEF, 21 slice reports, HARVEST + table, `harvest.py`, `bank.py`).
- **The memory store** (`~/.claude/projects/-home-musashi-bfm-decomp/memory/`, outside git): the off-project file parked, the seven
  stale updated in place with dated blocks, two index defects fixed; 80 files == 80 rows.
- **The kit `decomp-architect/` (436 files):** `README.md` (the three steps; what it installs / does NOT; scope; findings for
  ProjectArchitect), `intake.decomp.md` (PA's twelve items pre-answered; the 11-row ladder with a machine-checkable milestone, tools,
  rules and the kernel that earned each phase; Part C the six inversions; Part D), `SETUP.md` (Step 0 contract … Step 10 verify + hard
  stop; `answers:` for unattended runs; the honesty section; the PA-2.0 pin; Path A only; derived verify lines), `decomp-architect.md`
  (the methodology, 13 sections), `templates/` (19: the firewall pack — `gitignore.decomp`, `firewall.txt`, `audit_public.template.py`,
  the planted fixture, `no-rom.template.yml` —, the READMEs, `ops-setup.decomp.md`, `bootstrap.template.sh`, `CLAUDE.decomp-overlay.md`,
  `pa-overlays.md` (seven blocks), `registry-E.decomp.md` **G1–G67**, the LICENSE/NOTICE/README/CONTRIBUTING skeletons, `.clang-format`
  + `make-format.snippet.mk`, `PLACEHOLDERS.md` (22), `layout-contract.md`), `corpus/decomp-kernels.md` **DK-1–DK-80** + the 37-exhibit
  museum, **`corpus/tools/<phase>/`** (302 verbatim + 28 pointers + INDEX), **`corpus/cookbook/`** (the cookbook, its index, the codegen
  map, a front page on what transfers), **`corpus/record/`** (the how-to, the decision log, the accelerators, the retrospective, the
  story, the playbook, the effort map, the gen3 charter, the digest, every PhaseEnd, `build/tools-health.mk` — 57 files behind a front
  page), `memory-seed/` (18 + index), `tools/MANIFEST.md` (generated).
- **Knowledge base:** `docs/decision-log.md` P33.5 S90 / S91 / S91-b (the types hindsight) / S92; `docs/accelerators.md` P33.5 S91 (four)
  + S92 (two); `docs/SETUP.md` rows for every new tool and for the kit (R21); DIGEST §1/§3/§4; `docs/phase34-seed.md` amended.

**Tools/packages installed:** none external (no apt/pip). Five subagent dry-runs (Opus) under write-scope guardrails; 21 mining agents
(Opus); one review agent; three diff agents.

**Verification results (literal, at close — S92, HEAD `845fd8848`):**
- `make tools-health` (detached; `.run/P33.5/tools_health_t15.log`, 5,917 lines) → **`tools-health: OK — sigs fresh; corpus(+resident) +
  cdecl + binaries + report(lint+dedup) + cookbook-index all green.`** rc 0: audit-binaries 218/218 · audit-digest OK (instr
  13,492,113 / 13,492,113 — `docs/progress.json` unchanged, the fleet's 218/218 stands from the Phase-33 close) · `sdk-dual` OK both legs
  `143dbb89f34491258bbc27810d0a12ec8b43a8dd` · doc_links · gccmap_cites · ghidra_roster 6 · gitignore_template_check 75 · kit_lint
  selftest + run · tool_census --check (358 copies + 28 pointers) · **kit_coverage OK (83 rules: 57 cited + 26 dispositioned; 59
  accelerator entries: 42 + 15 — 0 uncovered)** · work_evidence · split_indicator 218 OK. **No build input changed in this phase; R22 was
  not owed** (the plan's D7) — the digest freshness check asserts the fleet numbers.
- The real render: `wiki_render: 32 pages rendered into .run/P33.5/wiki-render (386 relative links rewritten)`, rc 0. `doc_links
  --strict`: **58 documents, 451 links, 0 pending, 0 broken; citations 564 (439 tracked / 125 untracked, none in a wiki page); coverage
  65 of 65**. `tools/audit_public.py`: **OK — 0 offenders among 6,945 tracked paths** (6,937 text files scanned; longest disassembly-shaped
  runs 14/14/6). `gate_scan.py --all --worktree`: PASS — 0 offenders. `git ls-files -ci --exclude-standard .run` = 0; `git status
  --porcelain .run | grep -c '^??'` = 0; `purge_set.txt` unchanged since `80d45b29b`.
- The archive: `docs/sunset/README.md` ☐ rows 59 == `git ls-files docs/sunset` 59 (`comm -3` empty); every sunset basename has an
  Archive-index row; `tools/sunset` 34 == 34; `git log --follow` on three samples 7 / 2 / 2 commits. Memory 80 == 80; seed 18 == 18.
- **The kit: dry-run 5** (fresh throwaway, fresh Opus agent, the final kit): PA §1–§9 + Steps 0–10, 4 trailer-free commits, `stopped_at`
  null, 0 failed verify lines; **judge PASS 20/20** (manifest 57 == 57; G 67; seeds 34/34; probes 9/9 + 5/5; placeholder audit clean; the
  audit exits 0 in the throwaway; PhaseEnd_Phase0.5 + the archived log; tree clean; every guardrail unchanged). Runs 1–4 in the log.
- Tree: clean at HEAD apart from this close's deliverables; the headless Ghidra MCP stopped ("Save succeeded", R23; never used — no RE
  work; nothing under `ghidra/` is tracked).

**Milestone achieved (gate 2 — pre-approved by Drew 2026-09-08 conditional on every check passing; every check passed):** all six
items of the milestone at the top of the archived log are **MET with literal output** (the task-15 entry): (1) the wiki is the source
of truth (coverage ⊆, strict, the real render); (2) no information lost (the two set equalities, history followed); (3) tracked `.run/`
flip-ready (0 / 0, the audit rule, the content check, the history gate); (4) the kit exists and installs (lint, census, coverage,
dry-run 5 PASS — no `KNOWN-DEFECTS.md`); (5) the memory reconciled and seeded; (6) tools-health OK, this PhaseEnd, the DIGEST append,
the log archived, left for Drew.

**Next:** **Phase 34 — the flip and the Gen2 exit** (v1.32.1 → **v2.0.0**). Open a fresh session in **plan mode, Max** (Tier 1) from
**`docs/phase34-seed.md`**. **Its gate is OPEN:** the purge probe PASSED 2026-09-07 (re-run once immediately before the flip). The kit
is carried WHOLE through the flip; its split into its own repository (and the two items recorded for that split: the installable
health-chain snippet with a `TODO(phase-N)` per rung, and the ProjectArchitect findings) belongs to Gen3's opening phases.

## Roadmap delta (what Phase 33.5 changed about the road ahead)

- **Phase 34 is unchanged in content and now unblocked:** the probe passed during this phase; `docs/phase34-seed.md` records it. The
  wiki it pushes is now the source of truth (32 pages) and every published number is generated.
- **Gen3 gains a seed it did not have:** the S91-b hindsight — *types are a banking lever and a width lever, not a codegen lever* — is
  the kit's DK-65, its Phase-6 milestone (the canonical type layer from the first bank) and G62's bank-time clause; the source project's
  own Gen3 (struct unification, the 143 raw casts) is the proof the kit will later cite.
- **The kit is a deliverable in its own right** (Drew's charter item 4): 436 files, three dictionaries asserted equal to their sources on
  every health check, 80 kernels and 67 rules each with a provenance line into the record, a coverage check on the distillation, five
  dry-runs judged by script. Its split phase inherits two recorded tasks and three upstream findings for ProjectArchitect.
- **Doctrine that outlives the phase:** a distillation ships with a coverage check against the populations it claims to distil (its first
  run found 26 uncited rules and 21 uncited entries, three of them real gaps); the "capture while it hurts" rule captured 82% — the
  worklogs deserve one final read with an "already banked?" grep per candidate (one candidate in five was banked nowhere); every
  verify line compares two DERIVED figures (twice this phase a typed one was wrong); a dry-run's judge is negative-controlled before its
  FAILs are believed (four of its flags across five runs were the instrument's).
- **Scale, honestly (R41):** priced at 2–3 sessions; took 3 (S90–S92) and 26 commits, with two amendments and a third dictionary the
  plan did not have. The agents' cost: five dry-runs ≈ 1.4M tokens, the 21 mining slices ≈ 4.3M, the review + diff agents ≈ 0.5M.

## Deviations

| Item | Plan (gate-1 plan) | Actual | Reason |
|---|---|---|---|
| Task count | 16 | **18** (13.5 the tools audit + the dictionaries; 14.5 the record + the coverage check + the worklog pass) | Drew's two amendments (P5d), each from a question the measured answer to which was "no" |
| The dictionaries | none (the MANIFEST as Phase-1 tasks) | **three**: the tools verbatim by need, the cookbook, the record — `make kit-corpus`, asserted equal in tools-health | amendment 2 and 3; "the kit installs no tools" stays true — it ships the reference shelf |
| The dry-run | one run, fix, re-run to green | **five** (run 1 FAIL at Step 3.7 — PA's directory-form ignore; run 2 resume PASS; run 3 fresh PASS 0 defects; run 4 FAIL on a typed figure → resume PASS; run 5 fresh PASS 20/20) | each kit change that touched an installer step owed a fresh run; the judge itself had two false FAILs (scope; count vs path set) and one snapshot defect (a stripped porcelain line) |
| `family-hseq.md` | FROZEN → SUNSET | **stays KEEP-GEN** (a Reference-index row) | `verify_contract.sh` step 02 regenerates it — the contract's own statement (R14, task 6) |
| Session logs to untrack | "~50" | 44 (39 + 5) | the `gate/` verdict ledger and every rtu/variant log are evidence and stay (R41) |
| tools-health "foreground, ~15-min timeout" | foreground | **detached** with a background waiter | the chain runs longer than the harness's 10-minute foreground cap (task 11's finding); never a harness background task |
| The kit's vocabulary | `§0–§10`, `--answers` | `Step 0 … Step 10`, an `answers:` clause | the kit's own lint bans `§`+digit; a Claude Code prompt has no flags |
| Sunset scope | ~61 docs | 59 docs + **34 tools** (`tools/sunset/`) | the tools audit (13.5) applied Drew's criterion to the 93 no-consumer tools: 55 still needed, 28 superseded, 10 one-offs → 4 overturned to needed |
| Off-project memory | move to the Vantage project's store | **parked** under `~/.claude/memory-parked/` | no such store exists; never delete from a store with no history |
| Rules | (a)–(j) ratified at gate 1 | R74–R83 ratified; **eleven** new candidates + the S91-b doctrine proposed below | the phase generated governance from its own instrument failures |

## What we believed, what failed, and what we would do sooner (for the retrospective; the detail is in `docs/decision-log.md` P33.5 S90–S92)

- **Believed (S91):** the kit held the whole of the project's experience. **Measured from its own provenance lines: 57 of 83 rules cited,
  40 of 53 accelerator entries, no PhaseEnd and no worklog cited anywhere, the record absent verbatim.** The distillation was honest
  about its sources and silent about its coverage. **Sooner:** build the coverage check the day the distillation is designed (task 10),
  not after it ships.
- **Believed (thirty phases):** "capture while it hurts" captured everything worth keeping. **It captured 82%.** The missing fifth was
  fixed-but-never-generalised — a selftest blind by construction, a roster in ignored scratch, a red guard nobody wired, a timeout shorter
  than a tool's budget. **Sooner:** schedule the worklog pass as the project's last harvest by design; its yield (one in five) is far
  above any mid-campaign harvest's.
- **Believed (Phase 17):** types are not a lever, so they could wait until after 100%. **Right for cracking, wrong for banking:** 1,232
  drafter-invented definitions and a whole reconcile ladder later, Drew's question read the record the other way. **Sooner:** a canonical
  type file from the first bank, widths proven by the bytes at bank time, no duplicate definition or raw cast banked (DK-65, G62).
- **Believed:** a typed figure in a verify line is harmless. **Twice wrong in one phase** (the manifest total; the kernel count). **Sooner:**
  every check compares two derived figures — the file states its own total.
- **Believed:** the dry-run judge could be trusted. **Four of its flags across five runs were the instrument's** (an unscoped grep, a
  dirty-tree count instead of a path set, a stripped porcelain line, a crash on an empty value). **Sooner:** negative-control the judge
  against a known-PASS run before believing a FAIL — the same rule the project holds for every other instrument.
- **Cost:** the phase's real expense was the agents (≈6.2M tokens), and it bought 143 lessons, five proven installs and a tools audit of
  327 files. The coordinator's expense was the prose; the mistakes (a dropped log entry from a stale slice index, a stripped snapshot)
  were each caught by a check that read the artifact rather than the intent.

## Commit Message
```
(Phase 33.5 landed as 26 commits 39d524991..845fd8848, 2026-09-07 → 2026-09-08 (S90–S92). This close = the archived log + this
PhaseEnd + the DIGEST update, Drew's milestone-close commit.)

chore(phase-33.5): CLOSE — the wiki as source of truth, 59 docs + 34 tools sunset, tracked .run flip-ready, the memory reconciled,
the day-one decomp kit with three dictionaries / DK-1–80 / G1–67 / a coverage check / five dry-runs (v1.32.1)

- PhaseEnd_Phase33.5.md written; CURRENT_PHASE.md archived to phase-ends/logs/Phase33.5.md (R19); DIGEST §0/§2/§3/§4 appended (step 3b)
- 3 sessions (S90–S92): the six wiki pages + the Archive index; the six documents folded; doc_links rewritten (six checks) +
  render reachability + timeline wired + gitignore_template_check + audit_public check 4; .run 1,086 → 868 (+ this phase's evidence);
  the memory store 80 == 80 + the 18-file seed; the kit (436 files): intake, SETUP, methodology, 19 templates, G1–G67, DK-1–DK-80,
  corpus/tools 302+28, corpus/cookbook, corpus/record 57 files incl. the health chain, memory-seed 18, MANIFEST; tool_census +
  config/tool_dictionary.tsv + docs/tool-index.md; kit_lint; kit_coverage + config/kit_coverage_map.tsv; the worklog mining pass
  (777 candidates / 634 banked / 143 new → DK-69–80); dry-runs 1–5 (judge PASS 20/20 on the final kit)
- close: tools-health OK (5,917 lines; kit_coverage's first run in the chain); real render 32 pages; doc_links --strict 0/0/0;
  audit_public OK over 6,945 paths; gate_scan PASS; every milestone item met with literal output
- rules: R74–R83 ratified at gate 1; candidates (i)–(xi) + the S91-b doctrine proposed for Phase 34 gate 1
- v1.32.0 -> v1.32.1
```

## Rules Added This Phase

**Ratified at gate 1 (2026-09-07):** **R74–R83** (the PhaseEnd_Phase33 candidates (a)–(j)); full text in `phase-ends/DIGEST.md` §3.

**Candidates recorded in the log, for Drew to accept, modify or reject at Phase 34 gate 1 (P10):**

| Rule | Reason |
|---|---|
| **(i) An ignore file's directory-form rule is a wall no later block can climb — write the by-contents form first.** | ProjectArchitect's `.run/` defeated every re-include beneath it; dry-run 1 stopped on it (DK-67, accelerators S91 (1)). |
| **(ii) A check compares two DERIVED figures; a typed figure in a verify line is wrong the day the derived side moves.** | Run 4 stopped on `321 != 293`; the kernel count was typed `= 64` the day it became 65 (S91 (2)). |
| **(iii) A dry-run judge is an instrument — negative-control it against a known-PASS run before believing a FAIL.** | Four of its flags across five runs were its own (scope, count vs set, a stripped porcelain line, an empty value). |
| **(iv) A tool ships with its dictionary row, or the health check fails.** | 91 of 326 tools had no consumer and no way to be found by need; the census + the dictionary made the index and the corpus (S91 (4), G66). |
| **(v) Re-run `doc_links --strict` after ANY untrack or archive move, not only after a docs edit.** | Task 10 found tools-health red on the docs side since task 8's untrack; the claim had been carried from task 7. |
| **(vi) An unattended installer's manifest is specified as a derivable SET.** | Two honest agents produced 57 and 46 entries from the same words (run 3). |
| **(vii) A governance system that keeps transcripts in the repository needs the firewall's class-7 line.** | A decomp's transcripts quote the target's disassembly; the source project purged ~260,000 lines of `.s` from its own archive. |
| **(viii) A foreign project's path is named in prose, never as a backticked `docs/…` citation.** | The checker reads every such citation as this repository's (tasks 7 and 14 both hit it). |
| **(ix) A distillation ships with a coverage check against the populations it claims to distil.** | `kit_coverage`'s first run: 26 uncited rules, 21 uncited entries, three genuine gaps → DK-66/67/68. |
| **(x) The worklogs get one final read at the end of the project, with an "already banked?" grep per candidate.** | 777 candidates, 143 banked nowhere; the missing fifth was fixed-but-never-generalised. |
| **(xi) A snapshot instrument never `.strip()`s a porcelain listing.** | The run-5 false flag: the first line's status space eaten, a deletion under the dry-run's own directory read as foreign. |
| **(xii — doctrine, S91-b) Types are a banking lever and a width lever, not a codegen lever: a canonical type file from the first bank, widths proven by the bytes at bank time, no duplicate definition or raw address cast banked.** | Phase 17 measured the codegen half (0/10/2, identical bytes) and the project underweighted the other: 1,232 definitions, 143 raw casts, a reconcile ladder built to repair what the discipline prevents. |

*(Techniques stay where they belong — the wiki pages and the kit's kernels; strategy in `docs/decision-log.md` (R31) and
`docs/accelerators.md`.)*

## PhaseEnd Changelog
**v1.32.0 → v1.32.1 — Phase 33.5 complete (Gen2 sub-phase before the flip).** Chartered as a documentation consolidation, the phase made
the wiki the single source of truth (six new pages, six documents folded in, a link checker that derives its allow-list and refuses the
archive, 59 documents and 34 tools retired into indexed sunset folders), pruned the tracked scratch tree to flip-ready with a content
check and an audit-only rule for the one recorded residue, reconciled the memory store, and built the day-one decomp kit: a Phase-0.5
overlay on ProjectArchitect 2.0 with the project's phase ladder, its rules with provenance, its kernels, its conduct, its readability
standard at draft time — and, after Drew asked whether it held the whole of the project's experience and the measured answer was no,
three verbatim dictionaries (the tools by need, the cookbook, the record), a coverage check that refuses a silent gap in the
distillation, and a pass over all thirty thousand lines of phase worklogs that recovered 143 lessons and twelve kernels. Five dry-run
installs, judged by script, prove the final kit. R74–R83 ratified; eleven candidates and one doctrine proposed. No build input changed;
the fleet's 218 of 218 stands.

## Plain-English Recap
This short phase tidied the project for its public release and packaged what it learned. The documentation now has one front door,
the wiki, and every other document is either listed there with a note on how to read it or has been retired to an archive folder with a
record of what it was and where its information went. The scratch folder that git was tracking was cut back to what a reader should
see. The working notes the AI kept for itself were reconciled, and the portable ones became a starter set for the next project.

The big deliverable is the kit: a package that sets up a brand-new decompilation project the way this one would have set itself up if it
could start over — the order of work, the rule that keeps game data out of the repository from the first commit, the rules learned from
the failures, the conduct rules for using an AI, and the readability standard applied while matching rather than after. Drew asked
whether the kit really held everything we learned. Measured, it did not: it had been written from our summaries and never from the raw
day-by-day logs, and a third of our rules were not traceable to it. So the kit gained the whole record, verbatim; a check that refuses to
let any rule or lesson go uncited; and a final read of every log by agents that found 143 lessons we had fixed at the time but never
written down as lessons. The kit was installed five times into a throwaway repository by an agent that had never seen it, and judged by
a script each time; the final run passed on every count. The one thing this phase did not do is flip the repository public: that is the
next phase, and its gate opened during this one.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase33.5.md` (R19, via `git mv`); `phase-ends/DIGEST.md` §0/§2/§3/§4
appended (step 3b) — **all left uncommitted for Drew's milestone-close commit** (R6 gate-2 sign-off; the message is above). The Phase-33.5
work is committed across the sessions (`39d524991..845fd8848`); **Drew commits AND pushes** this close. The headless Ghidra MCP was stopped
cleanly ("Save succeeded", R23); nothing under `ghidra/` is tracked; `.run/P33.5/tools_health_t15.log` and `.run/P33.5/wiki-render/` are
untracked scratch. Gen2 continues — do **NOT** start Phase 34 here. Start a **fresh session** (effort **Max**, **plan mode**) for
**Phase 34 — the flip and the Gen2 exit**, opening from `docs/phase34-seed.md`; its gate is open. Keep this file forever.
