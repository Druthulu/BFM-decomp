# CURRENT_PHASE — Phase 34: the flip and the Gen2 exit (v1.32.1 → v2.0.0)

> **Gate 1 approved 2026-09-08 (Drew, plan mode, Max, Fable 5.1; session S93).** Rules **R84–R95 ratified at gate 1** (the Phase-33.5
> candidates (i)–(xii); binding; full text in `phase-ends/DIGEST.md` §3). The approved plan is reproduced VERBATIM at the end of this
> file (§"Approved plan") — its `~/.claude/plans/` copy is not part of the repo. This is the **last Gen2 phase**: it closes at
> **v2.0.0 = Gen2 EXIT**; Gen3 opens at Phase 35 from `docs/gen3-handoff.md` + `docs/gen3-standards.md`. **No build input changes in
> this phase: R22 is not owed**; the fleet's 218/218 is asserted by `make tools-health` (`report BINARY=main` + `audit-digest`).
> **Baseline HEAD at open: `eb342dc9f`** (Drew's Phase-33.5 CLOSE commit; tree clean; `origin/main == main`).
> **The gate is OPEN:** the purge probe printed PASS on 2026-09-07 (`.run/P33.5/probe_github_s91.log`, 33 of 33 old hashes gone,
> control OK); task 0 re-runs it immediately before the flip.

## Milestone (gate 2 — what Drew confirms; the seed's §3 with the measured additions)
1. `gh api repos/Druthulu/BFM-decomp --jq .private` → `false`; `tools/public_rewrite/probe_github.sh --after-flip` exit 0; the three
   unauthenticated URLs (repo page, raw badge JSON, `no-rom` badge.svg) return 200 where they returned 404 on 2026-09-08 while private;
   `no-rom` + `progress` green on the PUBLIC repo; `has_wiki` true and the wiki clonable and rendering; the archive repo
   `Druthulu/BFM-decomp-archive` still private; the `protect-main` ruleset active. B3's fresh-clone proof stands (no build input changed).
2. Every outward action done with its URL, or recorded as pending BY NAME (P9 — never claimed): the decomp.me scratch + preset-request
   issue + manual search (SETUP ledger row 14 closed), the Archipelago issue, decomp.dev, frogress, the wiki push, the xsig topics, the
   fork deletion (already done, S93 evidence), the tools post.
3. C11 done (no other clone of the old history remains — verified; scratch pruned with sizes; docs updated; checks green);
   `PhaseEnd_Phase34.md` v2.0.0 + DIGEST append written; Drew's close commit, the `v2.0.0` tag and the GitHub Release pushed. **Gen2 EXIT.**

## Effort / model (R7/R26/R27 — every transition is PROMPTED, never assumed)
- Per task (the plan's table): **Max** for task 1's decision (Drew) and task 8 (Tier 1 — prompt Drew to confirm Max before starting);
  **xHigh** for tasks 0a, 2, 3, 4, 7; **Low** for tasks 0, 1's checks, 5, 6. Max is set for this session (session-only; re-apply).
  No Ultracode/Workflow anywhere in this phase (nothing is breadth-shaped).
- **Drew-only (R6/R83):** every `git push`; the visibility change; every outward text (in his own words, no AI acknowledgement); the
  frogress key (his shell, never a file); the gate-2 confirmation; the tag + Release; `gh auth logout` (his last command).
- **Claude on Drew's word:** the `gh repo edit` metadata calls (BFM-decomp, xsig), the ruleset `gh api` POST.

## Owner decisions (binding — AskUserQuestion 2026-09-08 + one mid-planning message)
1. The Phase-33.5 candidates (i)–(xii) ratified as **R84–R95**. 2. **Claude runs the `gh` metadata calls** after the flip on Drew's word
(wiki enable, description — Drew edits the proposed wording at task 1 —, homepage = the wiki, topics; xsig topics + homepage at task 6).
3. **No other clone of the old history exists**: the Phase-1 relic clone at `/mnt/z/Storage/git/BFM-decomp` (11 commits, 2026-06-13,
old lineage, `origin` = BFM-decomp) found by S93's preflight was **deleted by Drew during planning; verified gone** (`ls` → No such file).
`/mnt/z/Storage/git/BFM-decomp-archive` is the C4 archive mirror (remote = the private archive repo; the intended surviving copy).
4. **Extras chosen:** a GitHub Release for v2.0.0 (notes in Drew's words) and a `protect-main` ruleset (no force-push, no deletion).
**Not chosen:** the off-machine bundle copy (the archive repo is the surviving copy of the old history — `.run/public_rewrite/`'s
bundle and dictionary are deleted at C11) and a public fresh-clone re-proof (B3's proof stands).

## Tasks (strict order; one commit per task after this file is updated; harness task list = the same rows, R28 — 10 at gate 1)
- [x] **0a** Open the phase: this file, R84–R95 into DIGEST §3 (+ one §0 line), the `.run/P34/` evidence allowlist, TaskCreate ×10, `doc_links --strict` 0/0, commit — xHigh (Claude)
- [x] **0** The probe once more: `tools/public_rewrite/probe_github.sh | tee .run/P34/probe/pre_flip.log` → PASS, control OK, no WARNING — Low (Claude)
- [ ] **1** C10 — the flip (Drew, Max) + post-flip checks, metadata, ruleset, Actions green on the public repo (Claude, Low)
- [ ] **2** E1 — decomp.me: scratch → 100% → preset-request issue → manual search (Drew, xHigh); recorded in SETUP §6.5 + ledger row 14 (Claude)
- [ ] **3** E2 — the Archipelago issue (Drew, xHigh); URL recorded; §5 reply handling pending unless a reply arrives (Claude)
- [ ] **4** D3 — decomp.dev registration + frogress slug/key/push (Drew, xHigh); verified by curl (Claude) → **P6 rules check after this task**
- [ ] **5** F3 — the wiki: dry run (Claude), first page + `wiki_sync.sh --push` (Drew), pages verified — Low
- [ ] **6** Tool discoverability: xsig topics + homepage (Claude on Drew's word); fork deletion already done; tools post (Drew) — Low
- [ ] **7** C11 — aftercare: scratch prune (keep `old-to-new.tsv` + `old_tag_tip.txt`), docs, checks — xHigh (Claude)
- [ ] **8** G2 — tools-health, P7 walk, gate 2, `PhaseEnd_Phase34.md` v2.0.0 + DIGEST + log archive; Drew commits/tags/pushes/releases, then `gh auth logout` — **Max, Tier 1**

## Blockers
- None at open. The Support ticket (#4736982) did its work: the probe PASSED 2026-09-07. If task 0 or task 1's `--after-flip` probe
  shows ANY hash ALIVE → stop (P5e); the fallback (delete + recreate the repository, `delete_repo` scope needed) is Drew's decision.

## Evidence layout (allowlisted under `.run/P34/`, logs only — R74)
`.run/P34/probe/` (pre_flip.log, after_flip.log) · `.run/P34/flip/` (repo JSON before/after, the curl codes, the metadata + ruleset
API outputs, `gh run list`) · `.run/P34/outward/` (the URLs Drew reports, the frogress/decomp.dev curls, the wiki checks, the xsig API
output) · `.run/P34/c11/` (the prune listing with sizes, `git worktree list`, the checks) · `.run/P34/tools_health_close.log`.

## Log (newest last; one entry per task; the 🛑 block at the end is rewritten after every task)

### 2026-09-08 — Task 0a — Open the phase (xHigh; S93)
- Written: this file (milestone, effort, decisions, tasks, evidence layout, the 🛑 block, the approved plan verbatim);
  `phase-ends/DIGEST.md` §3 **R84–R95 in full** (replacing the "proposed candidates" paragraph) + one §0 line ("Phase 34 OPENED
  2026-09-08"); `.gitignore` the dated `.run/P34/` allowlist block (contents-exclude form, `*.log`/`*.json`/`*.txt`/`*.md` only).
- Harness task list: TaskCreate ×10 (0a, 0, 1–8) — R28.
- Verify lines (S93): `tools/doc_links.py --strict` → `58 documents, 451 relative links checked, 0 pending (0 planned targets on the
  list), 0 broken; citations 568 (444 tracked, 124 untracked); docs/ coverage 65 of 65 covered by the Reference index + README; 2
  wiki-first warnings` (the two WARNs — `gen3-handoff.md` / `story.md` citing `verification.md` — pre-date this phase) → `doc_links: OK`,
  rc 0. `git check-ignore -v .run/P34/probe/pre_flip.log` → re-included by `.gitignore:410`; `.run/P34/probe/x.bin` → ignored by
  `:409` (the R84 by-contents form works). `git status --short` before the commit: `M .gitignore`, `M phase-ends/DIGEST.md`,
  `?? phase-ends/CURRENT_PHASE.md` — nothing else (H1 review). Committed as this task's commit.

### 2026-09-08 — Task 0 — The probe once more (Low; S93)
- `tools/public_rewrite/probe_github.sh 2>&1 | tee .run/P34/probe/pre_flip.log` → **`probe: PASS — every sampled old hash is gone from
  Druthulu/BFM-decomp`**, 33 `gone` lines of 33 sampled (every 134th of 4,031 + the pruned commit + the old tag tip), `control: current
  main eb342dc9fe0935b8c9743f9245b08dd16f875b67 resolves (OK)` (the PUSHED tip — local `main` is two commits ahead, unpushed: task 0a
  `c9dffdcfd` + this one), exit 0, **no** "WARNING — the WORKING repo" line, the throwaway `probe_scratch.git` deleted on exit (R81).
  Same 33 hashes as the S91 run (`.run/P33.5/probe_github_s91.log`). **The gate is open at the moment of the flip.** Log committed
  (allowlisted `.run/P34/probe/*.log`).

## 🛑 SESSION CHECKPOINT — PHASE 34 OPEN (S93, 2026-09-08): tasks 0a, 0 ✓; NEXT = task 1 (the flip — DREW's action, then Claude's checks)

### 0. How to use this block
A fresh session reads CLAUDE.md's load order, replays THIS block verbatim, and resumes at the first unchecked task above. Everything
a task needs is in its row, its plan paragraph (§"Approved plan" below), and the "carried context" here. Drew's browser/GitHub steps
pace tasks 1–6: present ONE task, wait for Drew's report (URLs / "done"), verify against the host, log, commit, next. Never claim an
outward action done without its URL or API line (P9). Effort: Max is session-only — ask Drew to re-apply `/effort max` at session
start (tasks 0a–7 run fine at xHigh; task 8 is Tier 1, Max).

### 1. Where things stand
- Baseline HEAD at open `eb342dc9f` = `origin/main` (Drew's 33.5 close, pushed 2026-09-08 15:36Z). Tree clean apart from this task's
  files. 1 pack / 82 MB; the working repo holds none of the sampled old commits (the probe's self-check line is absent from S91's log).
- GitHub (measured S93 15:xx MDT): `Druthulu/BFM-decomp` **private**, `has_wiki` false, description "Brave Fencer Musashi decomp", no
  topics, no homepage, AGPL-3.0, 0 forks, 161 Activity rows; both workflows GREEN on `eb342dc9f` (`no-rom` run 34245832656 1m52s,
  `progress` run 34245832709 22s; artifact `SLUS_007.26_report` 7,921 B). `Druthulu/BFM-decomp-archive` private, not a fork.
  `Druthulu/xsig` public, no topics, no homepage. `Druthulu/decomp-permuter` **does not exist** (API 404; not in `gh repo list`).
- Unauthenticated controls while private (the known-true negatives for task 1): `https://github.com/Druthulu/BFM-decomp` → 404;
  `https://raw.githubusercontent.com/Druthulu/BFM-decomp/main/docs/badges/fleet_instr.json` → 404;
  `https://github.com/Druthulu/BFM-decomp/actions/workflows/no-rom.yml/badge.svg` → 404; `https://github.com/Druthulu/xsig` → 200.
- `gh auth status`: logged in as Druthulu, scopes `gist read:org repo workflow` (enough for everything planned; no `delete_repo`).
- Inputs present: `.run/decompme/drew_bundle/{1_target_asm.s,2_context.c,3_source.c,4_compiler_flags.txt,5_issue_body.md}` (E1);
  `.run/public_rewrite/old-to-new.tsv` (4,033 lines) + `old_tag_tip.txt` (the probe's inputs; `docs/commit-map.tsv` carries the same
  rows); `tools/frogress_upload.py` dry run prints the payload for `eb342dc9f` (363,214 / 13,492,113 / 5,820,205 / 45,150 / 218).
- `.run/` 29 GB, disk 24 GB free of 73 GB; `.run/public_rewrite/` 1.1 GB; `.run/objdiff/` 6.7 MB; no linked worktrees; no tags anywhere.

### 2. Carried context per remaining task (exact invocations; gotchas)
- **Task 0:** `mkdir -p .run/P34/probe && tools/public_rewrite/probe_github.sh 2>&1 | tee .run/P34/probe/pre_flip.log; echo exit=${PIPESTATUS[0]}`.
  Expect "probe: PASS — every sampled old hash is gone", "control: current main <origin/main sha> resolves (OK)", exit 0. The fetch check
  runs in a throwaway bare repo under `.run/public_rewrite/probe_scratch.git` (R81) — it never touches the working repo. Needs `gh` auth
  and network. A "WARNING — the WORKING repo's object store holds N" line means old objects are held locally → the recipe it prints is
  Drew's to run (the auto-mode classifier refuses `gc --prune` from a Claude shell).
- **Task 1 (Drew flips, then Claude):** `gh api repos/Druthulu/BFM-decomp --jq '{private,visibility,has_wiki}'`;
  `tools/public_rewrite/probe_github.sh --after-flip 2>&1 | tee .run/P34/probe/after_flip.log`; the three curls above (expect 200 now);
  `gh api repos/Druthulu/BFM-decomp-archive --jq .private` (expect true). Metadata: `gh repo edit Druthulu/BFM-decomp --enable-wiki
  --description "<Drew-approved>" --homepage https://github.com/Druthulu/BFM-decomp/wiki --add-topic decompilation --add-topic playstation
  --add-topic psx --add-topic mips --add-topic reverse-engineering --add-topic psyq --add-topic brave-fencer-musashi` (proposed
  description: "Matching decompilation of Brave Fencer Musashi (PS1, SLUS-00726): 218 binaries rebuild byte-identical from C").
  Ruleset: `gh api -X POST repos/Druthulu/BFM-decomp/rulesets --input -` with `{"name":"protect-main","target":"branch","enforcement":
  "active","conditions":{"ref_name":{"include":["~DEFAULT_BRANCH"],"exclude":[]}},"rules":[{"type":"deletion"},{"type":"non_fast_forward"}]}`;
  verify `gh api repos/Druthulu/BFM-decomp/rulesets`. Then commit the log, Drew pushes, `gh run list --limit 2` must show both green.
- **Task 2 (Drew):** `docs/decompme-preset.md` §5. Paste `1_target_asm.s` WITHOUT its `.include "macro.inc"` line (the bundle's copy
  starts with a 3-line comment — check whether the `.include` line follows it and drop it). Expect 100% / score 0. If not: STOP and run
  `tools/decompme_replica.sh --upstream` before anything else (a moved decomp.me pin). Record scratch URL, issue URL, the manual search
  result in `docs/SETUP.md` §6.5 (line ~517) and ledger row 14 (line ~1005) and the P33 E1 section (line ~1202).
- **Task 3 (Drew):** `docs/outreach/archipelago.md` §4 (title + body; or the Discord short form). Record the URL in SETUP's P33 E2
  section (line ~1180) + the log. §5 (reply handling: memory-map rows `reported`, names via `config/symbols.us.txt` +
  `tools/ghidra_apply_symbols.sh`) is pending unless a reply arrives in-phase.
- **Task 4 (Drew):** decomp.dev `manage/new` → `Druthulu/BFM-decomp` (reads the `SLUS_007.26_report` artifact of `progress.yml`);
  frogress slug `bfm` + key requested from the maintainers; push = `FROGRESS_API_SECRET=… .venv/bin/python tools/frogress_upload.py
  --push` in DREW's shell. Verify: `curl -s -o /dev/null -w '%{http_code}' <decomp.dev project URL>`; `curl -s
  https://progress.deco.mp/data/bfm/us/ | head -c 600`. Then the P6 rules check (four tasks completed: 0, 1, 2, 3).
- **Task 5:** Claude `tools/wiki_sync.sh` (dry run; expect "not clonable yet … Rendered 32 pages" until Drew creates the first page).
  Drew: Wiki tab → Create the first page → `tools/wiki_sync.sh --push`. Verify: `git -C .run/wiki/BFM-decomp.wiki log -1 --oneline`;
  curls of `https://github.com/Druthulu/BFM-decomp/wiki`, `/wiki/Home`, `/wiki/Reference-index` → 200.
- **Task 6:** `gh repo edit Druthulu/xsig --add-topic decompilation --add-topic mips --add-topic playstation --add-topic psx --add-topic
  psyq --add-topic dedup --add-topic reverse-engineering -h https://github.com/Druthulu/BFM-decomp`; verify `gh api repos/Druthulu/xsig
  --jq '{topics,homepage}'`. Fork: already gone (record, do not redo). Drew posts `docs/outreach/tools-announcement.md` in his words.
- **Task 7 (C11):** `git worktree list` (expect one); `du -sh .run/public_rewrite .run/objdiff`; delete everything in
  `.run/public_rewrite/` EXCEPT `old-to-new.tsv` and `old_tag_tip.txt`; `rm -rf .run/objdiff`; list untracked regenerable `.run/`
  subtrees with sizes (`git ls-files .run` is the keep-set; the allowlisted evidence dirs stay) and prune the regenerable ones, quoting
  before/after `du`. Docs: DIGEST §0 (PUBLIC since <date>) + §1 (the flip executed); `docs/decision-log.md` "## P34 S93 (2026-09-08)
  — the flip" (R31); `docs/SETUP.md` posture section (line ~942: the flip date, the ruleset, the wiki live) + §6.5/row 14/E2/D3
  outcomes; `docs/wiki/Reference-index.md:70` (outreach row → past tense); `docs/wiki/Where-the-project-goes-next.md` §Phase 34 (past
  tense, dated). Checks: `.venv/bin/python tools/doc_links.py --strict`; `.venv/bin/python tools/wiki_render.py --selftest`;
  `make audit-digest`. If wiki pages changed → Drew re-runs `tools/wiki_sync.sh --push` (or list as pending). NOT here: `gh auth logout`.
- **Task 8 (G2, Tier 1):** `nohup make tools-health > .run/P34/tools_health_close.log 2>&1 &` with a foreground waiter loop (the chain
  exceeds the 10-min foreground cap; never a harness background task — the memory `tools-health-foreground-not-background`); read the
  final "tools-health: OK" line. P7 walk of every checkbox + the milestone lines; present; WAIT for gate 2. Then the PhaseEnd
  (`phase-ends/PhaseEnd_Phase34.md`, all sections incl. Plain-English Recap, R84–R95 in the rules table, pending outward items by
  name), `git mv phase-ends/CURRENT_PHASE.md phase-ends/logs/Phase34.md`, DIGEST §0/§2/§3 append — LEFT UNCOMMITTED. The 🛑 block
  hands Drew: `git add -A phase-ends && git commit -m "chore(phase-34): CLOSE — …"`, `git tag -a v2.0.0 -m "Gen2 exit — …"`,
  `git push origin main --tags`, `gh release create v2.0.0 --title "v2.0.0" --notes-file <his notes>`, `gh auth logout`. HARD STOP.

### 3. Environment
WSL2 Ubuntu, `~/bfm-decomp` (ext4). `.venv/bin/python` for every tool. `gh` authenticated as Druthulu (until Drew's logout at the
close). The headless Ghidra MCP is started by the SessionStart hook and is NOT needed in this phase (no RE work; stop it cleanly per
R23 before the close: `tools/ghidra_mcp_stop.sh` if present — check SETUP §2.8). Network needed for every gh/curl step. No `/tmp` (R12):
scratch under `.run/P34/`. Never `git clean -x` (R78). Never `git push` (R6).

## Approved plan (verbatim, 2026-09-08 — the `~/.claude/plans/` copy is not part of the repo)

# Phase 34 plan — the flip and the Gen2 exit (v1.32.1 → v2.0.0)

Planned 2026-09-08 (S93, plan mode, Max) from `docs/phase34-seed.md`, `docs/public-flip-runbook.md` §11–§12, the Phase-33
checkpoint §0b (`phase-ends/logs/Phase33.md:745`), and the live GitHub/tree state measured this session.

## Context

Phase 33 finished everything before the public flip and was re-chartered because the flip waited on GitHub Support purging the
old objects (ticket #4736982). Phase 33.5 made the docs publishable. **The gate opened during 33.5: the probe printed PASS on
2026-09-07** (`.run/P33.5/probe_github_s91.log`, 33 of 33 old hashes gone, control OK). Phase 34 is the last Gen2 phase: the flip,
the outward actions Drew does in his own words, the aftercare, and the v2.0.0 PhaseEnd = Gen2 EXIT. Gen3 opens at Phase 35.

Most tasks are **Drew's browser/GitHub actions**; Claude's job is to run the probes and checks, verify every outward result against
the host (P9: a URL or an API line, never an intent), log each task in `CURRENT_PHASE.md`, commit per task (R42/R8), and write the
PhaseEnd. Nothing in this phase changes a build input: **R22 is not owed**; tools-health runs once before the PhaseEnd (docs rungs).

## Gate-1 decisions (Drew, 2026-09-08, this session)

1. **Rules:** the Phase-33.5 candidates (i)–(xii) are **ratified as R84–R95** (full text appended to `phase-ends/DIGEST.md` §3 in task 0a):
   R84 ignore-file directory-form wall · R85 two DERIVED figures per check · R86 a judge is an instrument (negative-control before a FAIL) ·
   R87 a tool ships with its dictionary row · R88 `doc_links --strict` after ANY untrack/archive move · R89 an unattended installer's
   manifest is a derivable SET · R90 transcripts-in-repo governance needs the firewall's class-7 line · R91 a foreign project's path in
   prose, never a backticked citation · R92 a distillation ships with a coverage check · R93 the worklogs get one final read with an
   "already banked?" grep · R94 never `.strip()` a porcelain listing · R95 types are a banking + width lever: canonical type file from
   the first bank, widths proven by the bytes, no duplicate definition or raw address cast banked (the Gen3 type rule).
2. **Repo metadata:** Claude runs the `gh repo edit` calls after the flip on Drew's word (wiki enable, description, topics, homepage;
   xsig topics + homepage in task 6). Description proposed: *"Matching decompilation of Brave Fencer Musashi (PS1, SLUS-00726): 218
   binaries rebuild byte-identical from C"* — Drew edits the wording at task 1.
3. **Other clones:** none. The one candidate, `/mnt/z/Storage/git/BFM-decomp` (a Phase-1 relic clone: 11 commits, 2026-06-13, old
   lineage, `origin` = BFM-decomp), was found by this session's preflight and **deleted by Drew during planning; verified gone
   (`ls` → No such file)**. C11's clone-reset step is therefore not applicable; recorded with this evidence.
4. **Extras chosen:** a GitHub Release for v2.0.0 (notes in Drew's words) and a ruleset on `main` (no force-push, no deletion).
   Not chosen: the off-machine bundle copy (the archive repo `Druthulu/BFM-decomp-archive`, private, is the surviving copy of the old
   history) and the public fresh-clone re-proof (B3's proof stands, per the seed).

## Preflight facts (measured S93; R14 — re-verify in the task that depends on them)

| Fact | Value |
|---|---|
| `main` / `origin/main` | both `eb342dc9f` (Drew's 33.5 close, pushed 15:36Z); tree clean; 1 pack, 82 MB, no old objects held |
| Repo | `private: true`, `has_wiki: false`, description "Brave Fencer Musashi decomp", topics `[]`, homepage null, license AGPL-3.0, 0 forks, 161 activity rows |
| Workflows | `no-rom` 1m52s and `progress` 22s both **success** on `eb342dc9f`; artifact `SLUS_007.26_report` (7,921 B) present, not expired |
| Unauthenticated controls (today, private) | repo page **404**, raw badge JSON **404**, `no-rom` badge.svg **404**, `Druthulu/xsig` **200** — the known-true negatives for the post-flip checks |
| gh | logged in as Druthulu, scopes `gist read:org repo workflow` (enough for `repo edit`, rulesets, `release create`); no `delete_repo` — not needed |
| Fork `Druthulu/decomp-permuter` | **already gone** (API 404; `gh repo list` shows no fork) — task 6's deletion is DONE, evidence recorded |
| Archive repo | `Druthulu/BFM-decomp-archive` private, not a fork — must STAY private (a milestone check) |
| E1 inputs | `.run/decompme/drew_bundle/` present (33-line target, context, source, flags, issue body); `.run/decompme/target/` absent (regenerable, not needed — the bundle IS the paste) |
| D3 inputs | `frogress_upload.py` dry run prints the payload for `eb342dc9f` (363,214 / 13,492,113 / 5,820,205 / 45,150 / 218) |
| Windows tree | `/mnt/z/Storage/git/BFM-decomp/.git` was a Phase-1 relic (HEAD `f7807d84d` 2026-06-13, 11 commits, old lineage) — **deleted by Drew 2026-09-08 during planning, verified gone**; `/mnt/z/Storage/git/BFM-decomp-archive` is the C4 archive mirror (remote checked, see task 7) |
| `.run/` | 29 GB; disk 24 GB free of 73 GB; `.run/public_rewrite/` 1.1 GB (bundle, dict.json, maps, logs); `.run/objdiff/` 6.7 MB |
| Tags | none, locally or on origin — `v2.0.0` will be the first |
| Maps | `.run/public_rewrite/old-to-new.tsv` 4,033 lines == `docs/commit-map.tsv` rows (+5 comment lines) — the probe's input survives in the tracked file |
| `gh` in the health chain | none — logout is safe for tools-health |

## Tasks (one at a time; each ends with a `CURRENT_PHASE.md` log entry + one commit; effort per R7)

**0a. Open the phase** — Claude · xHigh · *first action after approval.* Write `phase-ends/CURRENT_PHASE.md` (this plan verbatim,
checkboxes, current-task pointer, a 🛑 SESSION CHECKPOINT block), append R84–R95 in full to `phase-ends/DIGEST.md` §3 (the
P33.5 precedent), add the `.run/P34/` evidence allowlist block to `.gitignore` (logs only, R74), build the harness task list (R28),
commit. Verify: `doc_links --strict` still 0/0.

**0. The probe, once more** — Claude · Low. `tools/public_rewrite/probe_github.sh | tee .run/P34/probe/pre_flip.log` → exit 0,
"PASS", control OK, no "WARNING — the WORKING repo holds" line. If anything is ALIVE: stop, P5(e) — the fallback (delete/recreate)
is Drew's decision and needs `delete_repo` scope. Commit the log.

**1. C10 — the flip and the post-flip checks** — Drew (decision, Max) then Claude (checks, Low).
Drew: Settings → General → Danger Zone → Change visibility → Public. Tell Claude. Claude, on that word:
- `gh api repos/Druthulu/BFM-decomp --jq .private` → `false`; `probe_github.sh --after-flip` → exit 0 (adds the unauthenticated
  7-char `/commit/` checks); the four unauthenticated curls flip **404 → 200** (repo page, raw badge JSON, badge.svg; xsig stays 200);
  `gh api …/BFM-decomp-archive --jq .private` → still `true`.
- Metadata (decision 2): `gh repo edit Druthulu/BFM-decomp --enable-wiki --description "<Drew's wording>" --homepage
  https://github.com/Druthulu/BFM-decomp/wiki --add-topic decompilation --add-topic playstation --add-topic psx --add-topic mips
  --add-topic reverse-engineering --add-topic psyq --add-topic brave-fencer-musashi`; verify with `gh api` (`has_wiki` true, topics list).
- The ruleset (decision 4): `gh api -X POST repos/Druthulu/BFM-decomp/rulesets` with `{name:"protect-main", target:"branch",
  enforcement:"active", conditions:{ref_name:{include:["~DEFAULT_BRANCH"],exclude:[]}}, rules:[{type:"deletion"},{type:"non_fast_forward"}]}`;
  verify with `gh api …/rulesets`. (A fast-forward push of the close commit and a tag push are unaffected.)
- Actions: the next push (this task's commit, pushed by Drew) must show both workflows green on the PUBLIC repo — `gh run list --limit 2`
  quoted in the log; never claimed unseen (P9). All outputs → `.run/P34/flip/`.

**2. E1 — the decomp.me preset** — Drew · xHigh. The six steps of `docs/decompme-preset.md` §5 with the bundle in
`.run/decompme/drew_bundle/` (paste `1_target_asm.s` without its `.include "macro.inc"` line; `2_context.c`; `3_source.c`; flags
`4_compiler_flags.txt`; issue body `5_issue_body.md`, edited in Drew's voice, R83). Expect 100% / score 0; if not, STOP and Claude runs
`tools/decompme_replica.sh --upstream` (a moved pin) before anything else. Drew reports: scratch URL, issue URL, the manual-search
result. Claude records them in `docs/SETUP.md` §6.5 + ledger row 14 (closing the greenfield claim's last check) + the log; commits.

**3. E2 — the Archipelago note** — Drew · xHigh. The issue on `AegeusEvander/Brave-Fencer-Musashi-AP-World` from
`docs/outreach/archipelago.md` §4 (or the Discord short form), in Drew's words. Claude records the URL in SETUP's P33 E2 section + the
log; the reply handling (§5: memory-map rows as `reported`, names via `symbols.us.txt` + `ghidra_apply_symbols.sh`) is **recorded as
pending** in the PhaseEnd unless a reply arrives in-phase.

**4. D3 — the progress boards** — Drew · xHigh. decomp.dev: log in → `decomp.dev/manage/new` → add `Druthulu/BFM-decomp` (reads the
`SLUS_007.26_report` artifact). frogress: request slug `bfm` + key from the maintainers; when granted,
`FROGRESS_API_SECRET=… .venv/bin/python tools/frogress_upload.py --push` (Drew's shell — the key never touches a file or Claude's
context). Claude verifies: the decomp.dev project URL resolves (curl 200); `curl https://progress.deco.mp/data/bfm/us/` returns the
entry for the pushed hash. Whatever is not granted in-phase is **recorded as pending** with the request's evidence.
→ **P6 rules check after this task** (four completed: 0, 1, 2, 3 — task 0a is the opening step).

**5. F3 — the wiki** — Drew · Low (Claude dry-runs first). Claude: `tools/wiki_sync.sh` (dry run: render 32 pages, clone refused
until the first page exists). Drew: Wiki tab → "Create the first page" (any content) → `tools/wiki_sync.sh --push`. Claude verifies:
`git -C .run/wiki/BFM-decomp.wiki log -1` shows the sync commit; unauthenticated curl of `…/wiki`, `…/wiki/Home`,
`…/wiki/Reference-index` → 200; the sidebar renders (Drew eyeballs, Claude records). Log + commit.

**6. Tool discoverability** — Claude on Drew's word · Low. `gh repo edit Druthulu/xsig --add-topic decompilation --add-topic mips
--add-topic playstation --add-topic psx --add-topic psyq --add-topic dedup --add-topic reverse-engineering -h
https://github.com/Druthulu/BFM-decomp`; verify via `gh api repos/Druthulu/xsig --jq '{topics,homepage}'`. The fork deletion is
**already done** (measured S93: API 404, no fork in `gh repo list`) — recorded, not redone. Drew posts the tools announcement
(`docs/outreach/tools-announcement.md`, his words) and reports where; recorded as done-with-link or pending.

**7. C11 — aftercare** — Claude · xHigh.
- Other clones: **none remain** — the Windows relic clone was deleted by Drew during planning (verified); the C4 archive mirror at
  `/mnt/z/Storage/git/BFM-decomp-archive` points at the private archive repo, not at BFM-decomp, and is the intended surviving copy of
  the old history (its remote is re-checked read-only and quoted in the log). The runbook's reset recipe is recorded as not applicable.
- Claude: `.run/public_rewrite/` → delete the bundle, `dict.json`, the clone artefacts and logs, **keeping `old-to-new.tsv` +
  `old_tag_tip.txt`** (hashes only, inert; the probe stays runnable — deviation from the seed's "delete the directory", reason: R55,
  keep the instrument); delete `.run/objdiff/`; prune regenerable `.run/` subtrees that are NOT tracked/allowlisted (list first,
  `git ls-files .run` as the keep-set, sizes quoted, R41); `git worktree list` (R77) before any gc — none expected.
- Docs: `phase-ends/DIGEST.md` §0 (PUBLIC since <date>; the Phase-34 state) + §1 (the flip executed; R1/R20 historical stays);
  `docs/decision-log.md` "P34 S93 — the flip" entry (R31: the calendar gate, the relic clone, the ratified rules);
  `docs/SETUP.md` posture section (the flip date, the ruleset, the wiki live, §6.5/row 14/E2/D3 outcomes), `docs/accelerators.md` if
  anything new; the "after the flip" markers in `docs/wiki/Reference-index.md:70` (outreach row) and
  `docs/wiki/Where-the-project-goes-next.md` §Phase 34 (past tense, dated). Then `doc_links --strict`, `wiki_render --selftest`,
  `make audit-digest --check`; if the wiki pages changed, Drew re-runs `tools/wiki_sync.sh --push` (or it is listed as pending).
- **`gh auth logout` moves to the very end** (a deviation from the seed): tasks 8's Release and the tag verification need gh; it is
  the last line of the 🛑 block, Drew's command after the push.

**8. G2 — PhaseEnd_Phase34 v2.0.0 (Gen2 EXIT)** — Claude · **Max, Tier 1** (prompt Drew to confirm Max before starting).
`make tools-health` detached with a waiter (>10 min; the P33.5 precedent), read OK. Verify every checkbox (P7) against the milestone
below, present the proof lines, **wait for gate 2**. On confirmation: `PhaseEnd_Phase34.md` (all sections; the verification lines
quoted from `.run/P34/`; pending outward items listed by name; R84–R95 in the rules table; the plain-English recap; the Gen3 pointer
`docs/gen3-handoff.md` + `docs/gen3-standards.md`), `git mv CURRENT_PHASE.md phase-ends/logs/Phase34.md` (R19), DIGEST §0/§2/§3
appended — left uncommitted for Drew (R6). The 🛑 block gives Drew, verbatim: the close commit; `git tag -a v2.0.0 -m "Gen2 exit …"`;
`git push origin main --tags`; `gh release create v2.0.0 --title "v2.0.0 — Gen2 exit" --notes-file <Drew's notes>` (notes in Drew's
words from the PhaseEnd changelog facts, R83); then `gh auth logout`. HARD STOP.

## Milestone (gate 2 — what Drew confirms; the seed's §3, with the measured additions)

1. `gh api repos/Druthulu/BFM-decomp --jq .private` → `false`; `probe_github.sh --after-flip` exit 0; the three unauthenticated
   URLs 200 (were 404); `no-rom` + `progress` green on the public repo; `has_wiki` true and the wiki clonable/rendering; the archive
   repo still private; the ruleset active. B3's fresh-clone proof stands (no build input changed).
2. Every outward action done with its URL or recorded as pending by name: decomp.me scratch + preset issue + search (row 14
   closed), the Archipelago issue, decomp.dev, frogress, the wiki push, the xsig topics, the fork (done), the tools post.
3. C11 done (no other clone of the old history remains — verified; scratch pruned with sizes; docs updated; checks green); `PhaseEnd_Phase34.md` v2.0.0 + DIGEST append
   written; Drew's close commit, the `v2.0.0` tag and the Release pushed. **Gen2 EXIT.**

## Verification, end to end

- Every check compares a derived figure to a derived figure (R85): API JSON, exit codes, HTTP codes with today's 404 controls, `gh run
  list` lines — all tee'd under `.run/P34/{probe,flip,outward,c11}/` (allowlisted, logs only).
- Instruments: `probe_github.sh` (throwaway scratch, R81), `gh api`, `curl -s -o /dev/null -w '%{http_code}'`, `tools/wiki_sync.sh`,
  `tools/frogress_upload.py`, `tools/doc_links.py --strict`, `tools/wiki_render.py --selftest`, `make audit-digest`, `make tools-health`.
- Stop conditions: any ALIVE hash (task 0/1), a decomp.me diff below 100% (task 2), a red workflow on the public repo (task 1), a
  `doc_links` failure after the C11 edits — each is P5(a)/(e): report with output, no redefinition (P9).

## Deviations from the seed, stated up front
- Task 0a added (the opening commit: plan, R84–R95, allowlist, task list). Task 6's fork deletion is already done. Task 7 keeps the two
  probe input files and moves `gh auth logout` to the end. Task 1 gains metadata + the ruleset (decisions 2, 4); task 8 gains the Release.
- Sessions: 1–2 (Drew's browser steps pace it; frogress/decomp.dev/Archipelago may close as pending).
