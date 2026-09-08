# PhaseEnd — Phase 33: 100% verification + the publishing surface + the releases — everything before the flip (re-chartered close)
**Date:** 2026-09-07 · **Project Version:** 1.32.0 · **Phase Status:** Complete on the re-chartered milestone (confirmed by Drew, gate 2 — 2026-09-07) · **Generation:** Gen2 (24th phase of the arc; the flip and the Gen2 exit are Phase 34)

> Gen2 phase 24 (8→…→32→**33**). Sixth phase off `docs/roadmap-to-100.md` v2 (§3 P33, all six items — Drew: "everything as written").
> Ran **4 sessions (S86–S89, 2026-09-06 → 2026-09-07)** and **59 commits** (`b5b79b3ac..b46358f27`, plus Drew's close commit). The
> granular trail — every control, every instrument defect and its repair, the four 🛑 checkpoints — is at **`phase-ends/logs/Phase33.md`**
> (R19, on demand). Owner decisions (Drew): gate 1 (2026-09-06, plan mode, Max; the eleven decisions in the plan — in-place flip with the
> full rewritten history, the purge set, AGPL for tools/docs with no license asserted over `src/`, the wiki, R65–R73 ratified); F3 and E5
> "in FULL" (2026-09-07); the outward pushes of xsig and the permuter fork by Claude (R6 waived for those two); **no AI acknowledgement in
> outward text — write it the way a developer writes** (2026-09-07, after the permuter maintainer closed the PR); **the re-charter**
> (2026-09-07): close Phase 33 now on what is done, the flip-gated remainder becomes **Phase 34** (the last Gen2 phase, v2.0.0), **Gen3
> opens at Phase 35**.

## Build Log

**The phase in one line:** the 100% contract was verified as one recorded run on a public-buildable tree; the repository's entire history
was rewritten to remove every game-derived byte and pushed in place with a commit map; the publishing surface, the five releases, the
story, the retrospective, the wiki and the how-to were written; the Gen3 charter was set — and the flip itself waits on GitHub Support
purging the old objects, which is calendar time and is now Phase 34.

**Files created/changed and complete — do not recreate** (category summaries; `phase-ends/logs/Phase33.md` and `git log b5b79b3ac..HEAD`
hold the per-commit list; 45 new tools, 49 new documents):

- **Block A — verification instruments + THE RECORDED RUN.** `make sig-main` rewritten build-derived (`tools/main_seed_ends.py`; the Ghidra
  sig had left **3,628 words of real game code owned by no function** — main game-code is **45,150 / 45,150**, not 41,534); `progress.py`
  fail-loud + derived oracle line; `backlog.py` LINKED-aware; `family_hseq.py` carries its coverage; **`NO_SDK` knob + `make sdk-dual`**;
  `tools/verify_contract.sh` → `.run/P33/verify/` (A5 on `3e0ecfacc`, re-run C8 on the adopted tree `5bc4a5c0ab`: every step EXIT=0,
  **218/218 clean fleet**, `sdk-dual` both legs `143dbb89…`, `0 PHANTOM 0 TRUNCATED 0 PAD-TAIL`, UNCLAIMED 0, report 100.00 / 100.0 /
  100.0, stubs 0, backlog 0); `docs/verification.md`.
- **Block B — the public build path.** `make disc-extract` (`extract.py --expect-manifest / --allow-missing-audio`; the four splat preset
  headers tracked; `.gitignore` re-tightened to H1); 34 absolute includes → `../shared/` (+ the portable-include audit class);
  `tools/bootstrap.sh` / `make bootstrap` + **the fresh-clone proof (218/218 in 4 m 18 s, no SDK objects)**; `tools/fetch_psyq.sh` +
  `tools/psyq_libs_from_disc.py` + `tools/psyq_CHECKSUMS.sha256` (20 LIBs, parser, RTL 4.2); **Ghidra regenerability** —
  `ExportAnnotations.java` / `ImportAnnotations.java` / `tools/ghidra_rebuild.sh --proof`, `config/ghidra/*.jsonl` + `ROSTER.md`, the six
  `ghidra_*.sh` repo-relative, `ExportSymbols` R15 fix (finished at medium, Drew's call); `dumps/CHECKSUMS.sha1` (28/28) + `INDEX.md`;
  **the ROM-free CI** `.github/workflows/no-rom.yml` (`tools/audit_public.py` — the first-push gate reused as CI; `tools/compile_only.py`
  — fleet 4,170/4,170 TUs in 123 s); SETUP rows for every tool (R21).
- **Block C — the history rewrite, pushed in place.** `tools/public_rewrite/` (`purge_set.txt`, `gate_scan.py` + fixture, `hash_dict.py`
  — 4,422 commit objects / 0 ambiguous / 0 collisions, `scrub.py` — 732 tokens == git's own lookup, `run_filter.py`, `verify_rewrite.py`,
  `build_commit_map.py`, `resolve_tokens.py`, `absent_scan.py`, `probe_github.sh`), `git-filter-repo 2.47.0`; two trial rewrites caught
  the empty-blob strip-list defect and the unchanged-commit case before the real run; the prep commit (`git rm --cached` ×251; `audit_public`
  first green); the bundle + Drew's mirror to the private archive `Druthulu/BFM-decomp-archive`; **the rewrite: 4,032 → 4,031 commits, 1
  pruned, 0 old hashes; `verify_rewrite` 4,031 pairs / 0 failures; `absent_scan` 0; `gate_scan` PASS**; adoption; **`docs/commit-map.tsv`**
  + 1,238 tokens resolved to new hashes (residue 8 in 4 tokens, cited commits in no lineage); C8's R22 on the adopted tree; **Drew's
  force-push**; gc with two discoveries (the archive remote and **12 stale linked worktrees, 12 GB, pinning 3,729 old commits**) →
  `.git` 1.5 GB → 93 MB, one pack. `docs/public-flip-runbook.md`.
- **Block D — the publishing surface.** `README.md` rewritten (generated numbers — `docs/progress.json` + `progress.py --readme --check`;
  Special thanks; the ProjectArchitect link; "About the history"; **"Standards, and how the AI was used"; "Tools from this project"**);
  `LICENSE` (AGPL-3.0 verbatim), `src/NOTICE.md` (no license asserted; "clean-room" appears nowhere), `THIRD_PARTY.md` (17 rows, each
  license read at its source), `tools/README.md`; `docs/badges/*.json`, `tools/objdiff_report.py` (validated with objdiff-cli 3.8.1),
  `tools/frogress_upload.py`, `.github/workflows/progress.yml`; SETUP public-clean; `tools/doc_links.py` (+ `doc_links_pending.txt`, EMPTY
  at close); DIGEST §1 corrections; `docs/roadmap-to-100.md` status block; `docs/gen2-roadmap.md` SUPERSEDED banner.
- **Block E — the releases.** `docs/gcc-2.7.2-map/README.md` + `tools/gccmap_cites.py` (135 cites tagged `[2.7.2]` 79 / `[2.8.1 pm]` 55 /
  `[repo]` 1, three instrument defects caught by its own controls); **`tools/xsig/`** (library + CLI + MIT + a game-free two-address
  fixture, 8/8) and the public repo **`github.com/Druthulu/xsig`**; **the permuter upstream PR** (`reloc-masked-scorer`, the tracked patch,
  `docs/permuter-ils.md`; **PR #213 + issue #214 CLOSED unmerged by the maintainer** — see Deviations); `docs/matching-drafter-pipeline.md`;
  **`docs/decompme-preset.md` + `tools/decompme_replica.sh`** (decomp.me's exact toolchain — old-gcc 0.13 + maspsx `86ccd7d8` — rebuilt
  locally; `func_80018F20` 26/26 words BYTE-IDENTICAL; `--upstream` drift check); **`docs/outreach/archipelago.md`** (the note, plus the
  decomp's answers to the AP world's data: the day-of-week byte confirmed and our `dayCounter` row corrected, four patch sites + the
  Time-Sanity hook resolved to shared engine functions, memory-map Q#13 answered); `docs/outreach/tools-announcement.md`.
- **Block F — the writing.** `tools/timeline.py` → `docs/story-timeline.md/.svg` (72 dated rows); `docs/story.md`;
  `tools/mine_hindsight.py` → `docs/retrospective.md`; **`docs/wiki/` (13 pages) + `docs/how-to-ai-decomp/` (13 chapters)** +
  `tools/wiki_render.py` (12/12 selftest) + `tools/wiki_sync.sh`.
- **Block G — Gen3.** `docs/gen3-handoff.md` (the derived census: 143 raw casts · 61,898 `D_` · 16,335 `func_` · 44,243 pins · 1,232
  struct defs · 2,220 dedup groups; the invariant; the levers; §2.1 labels vs derived structure; §2.2 the standard and the measured gap);
  **`docs/gen3-standards.md`** (the charter: accuracy met and stricter than the field; sotn `STYLE.md` adopted + four rules of ours; the
  use-of-AI conduct; the gap; a definition of done); **`docs/phase34-seed.md`** (the re-chartered remainder, every task with actor / effort
  / carrying document, the inventory, the milestone).
- **Governance and memory.** `phase-ends/DIGEST.md` §1/§3 (R65–R73 in full at A1; the H1 and roadmap bullets corrected at D5); `CLAUDE.md`
  fail-safe line "never `git clean -x`" (the hazard begins at the C3 commit); `docs/decision-log.md` P33 S86/S87/S89 entries (R31);
  `docs/accelerators.md`; the memory `decomp-community-ai-standards`; `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase33.md`**.

**Tools/packages installed:** `git-filter-repo==2.47.0` (venv, `requirements-python.txt`); the two cc1 tarballs stay tracked and
sha256-verified; no apt. Downloads under `.run/` (scratch, regenerable): old-gcc 0.13 `gcc-2.7.2-psx.tar.gz` (sha256 `aca64479…`, the
decomp.me replica), the objdiff-cli 3.8.1 validator.

**Verification results (literal, at close — S89, HEAD `b46358f27`):**
- `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → clean EXIT=0 · **`extract-all: 217 extracted, 0 failed of 217 (+
  main, serial)`** EXIT=0 · **`check-all: 218 passed, 0 failed of 218`** EXIT=0, **3 min wall** (`.run/P33/verify/s89_r22_close.log`).
- `make tools-health` (foreground) → **OK** (`.run/P33/verify/s89_tools_health_close.log`): sigs fresh; corpus(+resident) 0 PHANTOM + 0
  TRUNCATED; cdecl; audit-binaries 218/218 (R36); report lint + dedup 2,220 / 0; cookbook-index; `sig-main-oracle` 0 PAD-TAIL; `sdk-dual`;
  `doc_links --strict` 0 broken / 0 pending; `wiki_render --selftest` 12/12; `gccmap_cites --check`; xsig tests 8/8; `split_indicator`
  218 OK.
- The recorded contract run (`docs/verification.md` §2, C8 on `5bc4a5c0ab`): 00–08 every EXIT=0, 218/218, `sdk-dual` both legs
  `143dbb89f34491258bbc27810d0a12ec8b43a8dd`, UNCLAIMED 0, report `363214/363214 · 13492113/13492113 · 5820205/5820205 · main
  45150/45150`, stubs 0, backlog 0. The fresh-clone proof (B3): `check-all: 218 passed` with no SDK objects, 4 m 18 s.
- History: `verify_rewrite` 4,031/4,031 pairs; `absent_scan` PASS (0 offenders over 112,251 blobs / 16.2 GB text + 4,034 commits);
  `gate_scan --all --worktree` PASS; `tools/audit_public.py` OK (0 offenders); `origin/main == main` after Drew's force-push; **both GitHub
  workflows GREEN on every push** (`no-rom` 1 m 34 s; `progress` 17 s; the weekly full-fleet compile 18 m 42 s).
- **Not passed, by design of the re-charter:** `tools/public_rewrite/probe_github.sh` → **31 of 33 old hashes still ALIVE** (S89); the
  repository is still **PRIVATE** (`gh api … --jq .private` → true); GitHub Support ticket **#4736982** filed 2026-09-07. The flip is Phase 34.
- Tree: clean at HEAD (`git status --short` empty apart from nothing — `ghidra/` is untracked since C3). Ghidra MCP stopped cleanly
  ("Save succeeded", R23); no DB in git to commit.

**Milestone achieved (confirmed by Drew, gate 2 — 2026-09-07, on the re-chartered reading):** the phase's original milestone had four
items; **item 1 is met and re-proven today** (the recorded run, `sdk-dual`, the oracles, the disc residue, the three 100% lines, and the
C8 re-run on the adopted tree); **item 3 is met** — every deliverable file exists (`verification.md`, `commit-map.tsv`, `config/ghidra/*.jsonl`
+ `ROSTER.md`, `dumps/CHECKSUMS.sha1`, `decompme-preset.md`, `outreach/archipelago.md`, `gcc-2.7.2-map/README.md`, `tools/xsig/`, the
permuter patch + `permuter-ils.md`, `matching-drafter-pipeline.md`, `story.md` + timeline, `retrospective.md`, `docs/wiki/` +
`how-to-ai-decomp/`, `gen3-handoff.md`, and beyond the plan `gen3-standards.md`, `phase34-seed.md`, `tools-announcement.md`), with every
outward action done (xsig public; the permuter PR/issue submitted and closed) or **explicitly recorded as pending** (P9: the decomp.me
preset request, the Archipelago note, decomp.dev/frogress, the wiki push, the xsig topics, the fork deletion, the tools post); **items 2
and 4 — the public flip and the v2.0.0 tag — are NOT met and are not redefined:** they depend on GitHub Support purging the old objects,
and by the owner's decision they are Phase 34's milestone, word for word. 36 of 41 plan tasks done; C10 and C11 move; G2 is this file.

**Next:** **Phase 34 — the flip and the Gen2 exit** (v1.32.0 → **v2.0.0**). Open a fresh session in **plan mode, Max** (Tier 1) from
**`docs/phase34-seed.md`** — the daily probe until PASS (or the delete-and-recreate fallback past ~a week), C10, the outward halves of
E1/E2/D3/F3 in Drew's own words, tool discoverability, C11, the PhaseEnd. Then **Gen3 at Phase 35** from `docs/gen3-handoff.md` and
`docs/gen3-standards.md`.

## Roadmap delta (roadmap v2 §0 — what Phase 33 changed about the road ahead)

- **P33 as written in v2 (verify + flip + Gen2 exit) is split:** the verification, the rewrite, the publishing surface, the releases and
  the writing are DONE here; **the flip and the exit are Phase 34**, gated on a third party. The version plan follows: 1.32.0 here,
  2.0.0 at the Phase-34 close. The two-repo mirror of `gen2-roadmap.md` Phase 14 stays SUPERSEDED (in-place flip, full history).
- **Gen3 is chartered before Gen2 closes.** Its seed is two documents, not one: `gen3-handoff.md` (where Gen2 ends, the census, the levers)
  and `gen3-standards.md` (the bar: sotn's style guide adopted, names only with evidence, every pin off or `// !FAKE:`, the 5,147 macro
  bodies as C, types from the code and names from observation, a definition of done). Order of work: pins → macro bodies → struct
  unification → names → formatting, each gated by the 218 hashes.
- **Scale, honestly (R41):** the gate-1 plan priced Phase 33 at 17–21 sessions; it took **4** (S86–S89) plus Phase 34's ~1–2. The writing
  blocks were cheap because the record they distil (PhaseEnds, the decision log, the cookbook, the logs) was complete; the one slow item
  is the calendar-gated purge, which no session count buys.
- **Doctrine that outlives the phase:** a repository's own metadata (the Activity view) publishes what its tree no longer contains — gate
  a flip on the objects being gone, never on a clean tree; a "read-only" probe that fetches is a writer (R57); outward text is a person's,
  in a developer's voice (candidate (j)); published numbers are generated, never typed.

## Deviations

| Item | Plan (gate-1 plan) | Actual | Reason |
|---|---|---|---|
| Phase scope at close | one phase through the flip and the v2.0.0 tag | **re-chartered 2026-09-07:** closes at v1.32.0 on everything before the flip; C10/C11 + the outward actions + the tag → Phase 34 | the flip waits on GitHub Support (ticket #4736982; probe 31/33 ALIVE); Drew chose not to idle a phase on a third party (P5d) |
| Sessions | 17–21 | **4** (S86–S89), 59 commits | the writing distilled an already-complete record; F3/E5 "in FULL" still fit |
| C10's gate | "old hashes 404" via the Support purge | the same gate, with a NEW reason measured in S89: GitHub's **Activity view lists every pre-force-push tip** (157 rows to 2026-06-11), and the old tip still served the EXE, the dumps and the archive | the "no one has the old hashes" premise was false — the host publishes them; runbook §11, rule candidate (i) |
| The purge probe | a read-only check | its `git fetch origin <sha>` **imported 5.97 GiB of the purged history** into the working repo (30 packs) | R57 — fixed to a throwaway scratch repo with a self-check; Drew's gc restored one 80 MB pack |
| B5 (Ghidra regenerability) | Max, proof on SLUS + resident | finished at medium (Drew's call): export/import/rebuild shipped, the OSGi one-bad-file lesson recorded | proportionate — the text export is the backup; the proof is regenerable |
| G1 order | after C11 | pulled ahead (S88) | depended on nothing gated |
| E1 mechanics | "presets are created in-browser by a logged-in user"; decomp.me "bundles maspsx at our pin" | **no create-preset UI exists** — maintainers create presets from a GitHub issue template; decomp.me runs old-gcc **0.13** + maspsx **`86ccd7d8`** (not our 0.17 + `874855c5`) | both measured from decomp.me's own repos; the toolchain delta proven text-identical on the probe by `tools/decompme_replica.sh`; three stale SETUP rows corrected (R14) |
| E5 outcome | a PR + an issue upstream | **both CLOSED unmerged the same day**; the maintainer: the wildcard is intentional, rename symbols in the asm, nonzero floors are fine interactively — and the issue text read as LLM-generated ("kinda similar to getting a robocall") | recorded fairly in `permuter-ils.md`, the decision log, failure-museum row 37; Drew's apology was well received; the scorer stays a local tool |
| Outward text | "plain contributor style" | that pass filtered AI tells out of model prose instead of writing like a person — **Drew's decision: no AI acknowledgement; everything outward written the way a developer writes**; both pending messages rewritten | rule candidate (j) |
| E2 | a note asking for their research | the note **plus the decomp's answers to their data** (dow byte confirmed, patch sites → functions, Q#13 answered) and four memory-map corrections | reading their addresses against our source resolved our own open notes |
| Wiki timing | after the flip | briefly "can be done now" (S89) → **wrong**: free-plan GitHub offers wikis only on public repos | corrected within minutes from the settings page text (R14) |
| A2's denominator | "41,534 / 41,534" as the control value | the build-derived sig tiles **45,150** words — the Ghidra sig had left 3,628 words of game code owned by no function | a measured correction to the P31/P32 numbers; all metrics still 100% |

## What we believed, what failed, and what we would do sooner (for the retrospective; detail in `docs/decision-log.md` P33 S86–S89)

- **Believed:** once every document and every commit message cited new hashes, going public early was harmless. **False:** GitHub's
  Activity tab publishes every pre-force-push tip SHA, and each still resolved to the full old tree with the purged binaries one click
  deep. **Sooner:** enumerate the HOST's metadata surfaces (activity, events, PR refs, caches) in the rewrite design, not only the
  repository's content.
- **Believed:** the probe was read-only. **It was a writer** — a successful `git fetch` of an old SHA re-imported the purged history into
  the very repository it guarded (R57). **Sooner:** any check that fetches, clones or builds does so in a throwaway.
- **Believed:** removing AI tells from model prose made an upstream PR acceptable. **It made it worse** — the maintainer recognised it
  anyway and said why it cost him. Drew's diagnosis, shared: the dense code-span formatting and the exhaustive structure were the
  giveaway; the fix is writing the way a person writes, not filtering. **Sooner:** the owner writes every outward word from a facts list,
  and the target project's AI policy is read first (sotn-decomp forbids autonomous-tool PRs outright).
- **Believed:** decomp.me ran our toolchain and let a user create a preset. **Both wrong**, measured from its repositories; the preset is
  requested from maintainers, and their compiler build differs from ours in version — proven equivalent on the probe only by rebuilding
  their exact toolchain locally. **Sooner:** read the service's build recipe before writing the doc that depends on it.
- **Believed:** the phase would take 17–21 sessions. **Four.** The record was complete enough that every writing task was distillation.
  **Cost:** the phase's real expense was the two outward missteps (a maintainer's time and a closed PR; a 6 GB re-import) — both cheap to
  repair, both avoidable by the two rules above.

## Commit Message
```
(Phase 33 landed as 59 commits b5b79b3ac..b46358f27, 2026-09-06 → 2026-09-07 (S86–S89). This close = the archived log +
this PhaseEnd + the DIGEST update + the two close logs, Drew's milestone-close commit.)

chore(phase-33): CLOSE (re-chartered) — verified, rewritten, published-ready: the contract run, the in-place history rewrite,
LICENSE/NOTICE/README, the releases, story/retrospective/wiki/how-to, the Gen3 charter; the flip is Phase 34 (v1.32.0)

- PhaseEnd_Phase33.md written; CURRENT_PHASE.md archived to phase-ends/logs/Phase33.md (R19); DIGEST §0/§2/§3 appended (step 3b)
- 4 sessions (S86–S89): A1–A5 (the recorded run; main game-code 45,150/45,150), B1–B9 (public build path, Ghidra text export, CI),
  C1–C9 (filter-repo rewrite: 4,031 pairs / 0 failures, commit-map.tsv, force-pushed in place, .git 93 MB), D1–D5, E1–E6, F1–F3, G1
- close R22 on b46358f27: extract-all 217/217 (+main), check-all 218 passed / 0 failed (exits 0/0/0); tools-health OK
- re-charter (Drew): the flip-gated remainder (probe → C10 → outward E1/E2/D3/F3 → discoverability → C11 → v2.0.0) is Phase 34
  (docs/phase34-seed.md); Gen3 = Phase 35 from gen3-handoff.md + gen3-standards.md
- rules: R65–R73 ratified at gate 1; candidates (a)–(j) proposed for Phase 34 gate 1
- v1.31.0 -> v1.32.0
```

## Rules Added This Phase

**Ratified at gate 1 (2026-09-06):** **R65–R73** (the PhaseEnd_Phase32 candidates (i)–(ix)); full text in `phase-ends/DIGEST.md` §3.

**Candidates recorded in the log, for Drew to accept, modify or reject at Phase 34 gate 1 (P10):**

| Rule | Reason |
|---|---|
| **(a) No ROM-derived bytes in ANY published artifact** — test fixtures, JSON, badges, reports, wiki pages included. | The xsig fixture was built from our own C at two link addresses for exactly this reason; the regenerated target `.s` stays under the ignored `.run/`. |
| **(b) Published numbers are generated, never typed** (R51 applied to documents). | `docs/progress.json`, the README block, the badges, the timeline: every hand-typed number in the old README was stale. |
| **(c) Rehearse every irreversible repository operation on a scratch copy and prove it pair by pair with POSITIVE assertions.** | Trial rewrite #1 exposed the empty-blob strip-list defect and the unchanged-commit case; the real run had 0 failures. |
| **(d) A linked worktree's HEAD is a ref — audit `git worktree list` before any gc or purge.** | 12 stale worktrees (12 GB) pinned 3,729 old commits through the gc. |
| **(e) R20 amendment: the text export + checksums + the archive repository are the backup; never `git clean -x`.** | The purged paths are ignored-but-present; a `-x` clean deletes the RE database (CLAUDE.md fail-safe since C3). |
| **(f) `pkill -f` never with a literal the calling shell's own command line contains.** | S87 killed its own shell twice (exit 144). |
| **(g) A checker that widens its document set must classify a missing promised page as PENDING, never BROKEN.** | `doc_links` + `doc_links_pending.txt`: 10 planned pages mid-F3, 0 false failures. |
| **(h) A probe or guard must never write into the repository it guards** — a "read-only" check that fetches, clones or builds does so in a throwaway (R57 exemplar). | The purge probe re-imported 5.97 GiB of the purged history on every run. |
| **(i) A rewritten history is not private until the objects are gone from the HOST** — its Activity view publishes every pre-force-push tip; gate a flip on the probe (or recreate the repository), never on a clean tree. | 157 activity rows to 2026-06-11; the old tip still served the EXE, the dumps and the archive. |
| **(j) Outward text to third parties is written by Drew the way a developer writes** — short, plain, few or no code spans, no bullet walls, no evidence scaffolding — rewritten from the facts, never a model draft with the tells removed; **no AI acknowledgement**; the target project's AI-contribution policy is read first. | The permuter maintainer closed #213/#214 and named the LLM-looking text as the reason he minded; sotn-decomp forbids autonomous-tool PRs outright. |

## PhaseEnd Changelog
**v1.31.0 → v1.32.0 — Phase 33 complete on its re-chartered milestone (Gen2 phase 24).** The 100% contract was verified as one recorded
run (218 of 218 from a clean rebuild, both SDK legs, every oracle green, the three metrics at 100% with main's game-code denominator
corrected to 45,150) on a tree a stranger can build from their own disc (the fresh-clone proof, `make disc-extract`, `make bootstrap`,
the optional SDK fetch, the Ghidra database regenerable from text). The repository's entire history was rewritten with `git filter-repo`
to remove every game-derived byte — 4,031 commits verified pair by pair, one pruned, every old hash replaced by an inert token and mapped
in `docs/commit-map.tsv` — force-pushed in place, and shrunk from 1.5 GB to 93 MB. The publishing surface (README with generated numbers,
AGPL for tools and docs with no license asserted over `src/`, NOTICE, THIRD_PARTY, badges, objdiff/frogress publishing, a ROM-free CI), the
five releases (the gcc 2.7.2 codegen map, xsig, the permuter driver, the drafter write-up, the decomp.me preset proven through decomp.me's
own toolchain), the outreach notes, the story, the retrospective, the wiki and the thirteen-chapter how-to were written. The Gen3 charter
was set: accuracy already stricter than the field, readability to sotn's standard with evidence-based names and no match-forcing tricks,
and conduct rules for using AI that keep the project apart from low-effort machine decomps. The flip itself waits on GitHub Support and
is Phase 34, which closes Gen2 at v2.0.0; Gen3 opens at Phase 35.

## Plain-English Recap
This phase took a finished-but-private translation and made it ready to publish. First we proved the whole claim one more time, end to
end, on a computer set up the way a stranger would set it up: every one of the 218 files rebuilds byte for byte from our source and a
copy of the game disc. Then we cleaned the repository's history: the old commits contained the game's executable, memory dumps, Sony's
development kit and our own transcripts, none of which may be published, so we rewrote all four thousand commits to remove them, checked
every rewritten commit against its original, and replaced the repository on GitHub with the clean version. We wrote everything a reader
needs: a README with numbers generated by the tools rather than typed, the licenses, a thirteen-chapter guide to how a project like this
is run with an AI agent, the story of the project and an honest retrospective, and a wiki. We packaged the tools worth sharing, and one
of them was offered to the maintainer of a widely used tool, who declined it and, fairly, objected to the machine-written wording of the
request; that taught us a rule we now hold. Finally we wrote down the standard the next generation must meet: the code matches
perfectly, but it still reads like machine output, and turning it into code a human maintainer would call finished is the work ahead.
The one thing this phase could not do is flip the switch to public: GitHub has to purge the old data first, and that is in their hands,
so it becomes its own short phase.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase33.md` (R19, via `git mv`); `phase-ends/DIGEST.md` §0/§2/§3
appended (step 3b); the two close logs moved into `.run/P33/verify/` — **all left uncommitted for Drew's milestone-close commit** (R6
gate-2 sign-off; the message is above). The Phase-33 work is committed across the sessions (`b5b79b3ac..b46358f27`); **Drew commits AND
pushes** this close. The headless Ghidra MCP was stopped cleanly ("Save succeeded", R23); nothing under `ghidra/` is tracked. Gen2
continues — do **NOT** start Phase 34 here. Start a **fresh session** (effort **Max**, **plan mode**) for **Phase 34 — the flip and the
Gen2 exit**, opening from `docs/phase34-seed.md`. Keep this file forever.
