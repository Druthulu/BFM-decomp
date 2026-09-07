# Phase 34 — the flip and the Gen2 exit (the post-flip half of Phase 33, re-chartered 2026-09-07)

> **Why this phase exists.** Phase 33 planned the contract verification, the history rewrite, the publishing surface, the
> releases, the writing, and the public flip as one phase. Everything that does not depend on GitHub Support is done (see §2).
> The flip is gated on Support purging the old objects (ticket #4736982, filed 2026-09-07; `tools/public_rewrite/probe_github.sh`
> must print PASS first), which is calendar time nobody controls. The owner's decision (2026-09-07): **close Phase 33 now on what
> is done, put the flip-gated remainder into Phase 34 as the last Gen2 phase, and open Gen3 at Phase 35.** Phase 33 therefore
> closes at v1.32.0; Phase 34 closes at **v2.0.0 = Gen2 EXIT**. This file is the seed for Phase 34's plan-mode session (Tier 1,
> Max): it carries every task, every document the task uses, and the milestone, so nothing from Phase 33 is lost.

## 1. Tasks (in order; effort per task; the actor)

| # | Task | Actor | Effort | The document that carries it |
|---|---|---|---|---|
| 0 | **Daily probe** until PASS: `tools/public_rewrite/probe_github.sh` (S89 baseline 31 of 33 old hashes still ALIVE). Fallback if Support stalls past ~a week: delete and recreate the repository under the same name and push the same rewritten history (a new object network and a fresh Activity log; nothing else exists to lose). | Claude runs; Drew decides the fallback | Low | `docs/public-flip-runbook.md` §11 (the Activity-view leak, the ticket route, the fallback) |
| 1 | **C10 the flip:** Settings → General → Danger Zone → Change visibility → Public; then `gh api repos/Druthulu/BFM-decomp --jq .private` → `false`; `probe_github.sh --after-flip`; the Actions tab green; enable Settings → Features → Wikis (free plan: wikis need a public repo). | Drew | Max (decision) | runbook §11; checkpoint §0b |
| 2 | **E1 outward — the decomp.me preset:** the six steps (log in; scratch from `.run/decompme/drew_bundle/` → 100%; the preset-request issue on `decompme/decomp.me` in Drew's words; the manual search closing SETUP ledger row 14; report URLs). Regenerate the bundle with `tools/decompme_replica.sh` if `.run/` was pruned. | Drew | xHigh | `docs/decompme-preset.md` §5 |
| 3 | **E2 outward — the Archipelago note:** the GitHub issue on `AegeusEvander/Brave-Fencer-Musashi-AP-World` (or the Discord short form), in Drew's words; on reply, memory-map rows per its §5. | Drew | xHigh | `docs/outreach/archipelago.md` §4–§5 |
| 4 | **D3 outward — progress boards:** decomp.dev → log in → `decomp.dev/manage/new` → add the repo (reads the `SLUS_007.26_report` artifact `progress.yml` uploads); frogress: request slug `bfm` + key, then `FROGRESS_API_SECRET=… .venv/bin/python tools/frogress_upload.py --push`. | Drew | xHigh | SETUP P33 D1–D3 section; `tools/objdiff_report.py`, `tools/frogress_upload.py` |
| 5 | **F3 outward — the wiki:** Wiki tab → "Create the first page" → `tools/wiki_sync.sh --push` → check the sidebar links render. | Drew | Low | `tools/wiki_sync.sh`; `docs/wiki/`, `docs/how-to-ai-decomp/` |
| 6 | **Tool discoverability:** `gh repo edit Druthulu/xsig --add-topic decompilation --add-topic mips --add-topic playstation --add-topic psx --add-topic psyq --add-topic dedup --add-topic reverse-engineering -h https://github.com/Druthulu/BFM-decomp`; delete the fork `Druthulu/decomp-permuter` (the patch stays tracked in-tree); post the tools announcement in Drew's words. | Drew (or Claude on Drew's word) | Low | `docs/outreach/tools-announcement.md`; README "Tools from this project" |
| 7 | **C11 aftercare:** other clones `git fetch origin && git reset --hard origin/main && git reflog expire --expire=now --all && git gc --prune=now` (never `git pull`); `gh auth logout`; delete `.run/public_rewrite/` and `.run/objdiff/`; prune `.run/`; DIGEST §0/§1 and the decision-log entry for the flip. | Claude | xHigh | runbook §12 |
| 8 | **G2 — PhaseEnd_Phase34 v2.0.0 (Gen2 EXIT):** the PhaseEnd, `CURRENT_PHASE.md` → `phase-ends/logs/Phase34.md`, DIGEST §0/§2/§3 appended, the annotated `v2.0.0` tag; Drew pushes `main --tags`. Rule candidates (a)–(j) of Phase 33 were **ratified as R74–R83 at Phase 33.5 gate 1 (2026-09-07)**; any Phase 34 candidates are added here. | Claude, then Drew (gate 2, push) | Max, Tier 1 | this file; `phase-ends/PhaseEnd_Phase33.md` |

> **Phase 33.5 runs before this phase** (opened 2026-09-07; `phase-ends/CURRENT_PHASE.md`): docs consolidation into the wiki, the
> tracked-`.run/` prune, the memory reconciliation and the day-one decomp kit — v1.32.1. It changes no build input and no flip step;
> task 0's daily probe continues in parallel. Phase 34 opens from this file once 33.5 closes.

Every outward action is done by Drew or **explicitly recorded as pending** in the PhaseEnd (P9 — never claimed). Every outward
text is written by Drew the way a developer writes it (rule candidate (j); `docs/gen3-standards.md` §3).

## 2. What Phase 33 delivered (the record Phase 34 inherits — nothing here is redone)

Verification and instruments: `docs/verification.md` (the recorded contract run, 218 of 218), `tools/verify_contract.sh`, `make
sdk-dual`, `make disc-extract`, `tools/bootstrap.sh`, `tools/fetch_psyq.sh`, the ROM-free CI (`.github/workflows/no-rom.yml`,
`tools/audit_public.py`, `tools/compile_only.py`), `dumps/CHECKSUMS.sha1`, `config/ghidra/*.jsonl` + `ROSTER.md`
(`tools/ghidra_rebuild.sh --proof`). The history rewrite: `tools/public_rewrite/`, `docs/commit-map.tsv`,
`docs/public-flip-runbook.md`, the private archive `Druthulu/BFM-decomp-archive`, the force-pushed rewritten `main`. The
publishing surface: `README.md` (generated numbers, Special thanks, "Standards, and how the AI was used", "Tools from this
project"), `LICENSE`, `src/NOTICE.md`, `THIRD_PARTY.md`, `docs/progress.json` + `docs/badges/`, `tools/objdiff_report.py`,
`tools/frogress_upload.py`, `.github/workflows/progress.yml`, `tools/doc_links.py`. The releases: `docs/gcc-2.7.2-map/README.md`
+ `tools/gccmap_cites.py`; `tools/xsig/` + `github.com/Druthulu/xsig`; `docs/permuter-ils.md` + the tracked patch (offered
upstream, declined); `docs/matching-drafter-pipeline.md`; `docs/decompme-preset.md` + `tools/decompme_replica.sh`;
`docs/outreach/archipelago.md`; `docs/outreach/tools-announcement.md`. The writing: `docs/story.md` + `docs/story-timeline.md/.svg`
(`tools/timeline.py`), `docs/retrospective.md` (`tools/mine_hindsight.py`), `docs/wiki/` (13 pages) + `docs/how-to-ai-decomp/`
(13 chapters) + `tools/wiki_render.py` / `tools/wiki_sync.sh`. Gen3: `docs/gen3-handoff.md`, `docs/gen3-standards.md`. Memory
map: the S89 corrections (day-of-week, the patch-site functions, Q#13). Rules: R65–R73 ratified at gate 1; candidates (a)–(j)
recorded in the Phase 33 checkpoint and proposed at its close.

## 3. Milestone (gate 2 of Phase 34 — what Drew confirms; these are Phase 33's original items 2–4)

1. `gh api repos/Druthulu/BFM-decomp --jq .private` → `false`; `probe_github.sh` exit 0 (old hashes 404); `.github/workflows/
   no-rom.yml` green on the public repo; the wiki live; the fresh-clone criterion met with the disc (B3's proof stands).
2. Every outward action done or recorded as pending: the decomp.me preset request, the Archipelago note, decomp.dev and
   frogress, the wiki push, the xsig topics, the fork deletion, the tools post.
3. C11 done; `PhaseEnd_Phase34.md` v2.0.0 + DIGEST append + the `v2.0.0` tag pushed. **Gen2 EXIT.**

## 4. What comes after (not this phase)

Gen3 opens at Phase 35 in a fresh plan-mode session from `docs/gen3-handoff.md` and `docs/gen3-standards.md`: pins off, the
macro-body header into shared C files, struct unification, names with evidence, formatting — every step gated by the 218 hashes.
