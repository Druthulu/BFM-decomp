## Backup & repository posture (rules R20/R21) — PUBLIC since 2026-09-08 (Phase 34)

The repository is **public** (`https://github.com/Druthulu/BFM-decomp`, AGPL-3.0 for `tools/`+`docs/`, `src/NOTICE.md`
for the game sources, `THIRD_PARTY.md`) — **flipped 2026-09-08** (Phase 34 task 1) after `tools/public_rewrite/probe_github.sh`
passed immediately before (33/33 sampled old hashes gone) and again after (`--after-flip`, incl. the unauthenticated commit pages);
the **`protect-main` ruleset** (id 22564862: no deletion, no force-push of `main`, no bypass actors — edit the ruleset first if a
rewrite is ever needed) guards the published history; the wiki (`docs/wiki/` + the how-to, 32 pages) is live and synced by
`tools/wiki_sync.sh`; the progress card is `https://decomp.dev/Druthulu/BFM-decomp`. **H1 is in force:** no ROM-derived or proprietary bytes are in git or in its
history — the retail EXE, the RAM dumps, the Ghidra project, the Sony SDK, the session archive, the extension zips and
`brave.exe` were purged from every commit before the flip (`docs/public-flip-runbook.md`), and `tools/audit_public.py` +
CI (`.github/workflows/no-rom.yml`) keep it that way. The disc dump (`disks/`), `extracted/`, `build/`, `asm/`, `expected/`
and `.venv/` are regenerable or user-supplied and are never committed (`.venv/` from `requirements-python.txt`).

*Historical note (2026-06-15 → 2026-09-06, the private era):* while the repository was private, rule R1 relaxed H1 and the
Ghidra project, the PsyQ working artifacts (minus the >100 MB raw archives), the cc1 tarballs and the extension installers
were committed as the R20 backup. That state is preserved, unrewritten, in the private archive repository
`Druthulu/BFM-decomp-archive` and in the local bundle made at C4 — it is not the public history.

**P33 update (B5/B8, 2026-09-06) — R20's new home after the public flip.** The Ghidra project, the RAM dumps, the PsyQ
SDK, the session archive and the extension zips leave git at C3 (`tools/public_rewrite/purge_set.txt`). What R20 backs up
INSTEAD: the RE work as text — **`config/ghidra/<program>.jsonl` + `ROSTER.md`**, proven regenerable by
`tools/ghidra_rebuild.sh <program> --proof` (all six PASS); the dumps' identity in `dumps/CHECKSUMS.sha1`; the SDK's
identity in `tools/psyq_CHECKSUMS.sha256` (+ `tools/fetch_psyq.sh`); the zips' sha256s (§2.3/§2.4). The one-time snapshot
of the binaries is the private archive repo `Druthulu/BFM-decomp-archive` (C4). **Never `git clean -x` in this tree** —
the purged paths become ignored files and a `-x` clean deletes the RE database (R20 amendment proposed at PhaseEnd_Phase33).

**Rules:**

- **R20** — back up all irreplaceable RE/decomp work plus gathered hard-to-re-source tooling at per-session checkpoints. This **loosens R8** (which mandated a single commit at phase end): checkpoint commits are now expected within a phase.
- **R21** — keep **THIS file** (`docs/SETUP.md`) current whenever tooling, the MCP setup, the session hooks, or the environment changes.

Sony's **PsyQ libraries are never distributed** (user-supplied, `tools/fetch_psyq.sh`, checksums only); the gcc-2.7.2 **cc1 tarballs ARE tracked** (GCC, GPL; sha256-verified). The two-repo "curated public mirror" plan of `docs/gen2-roadmap.md` was SUPERSEDED by the in-place flip with the full rewritten history (decision log, P33 S86). The four submodules (asm-differ / m2c / maspsx / decomp-permuter) stay **gitlinks** on GitHub (the deliberate no-bloat choice over vendoring); residual risk = upstream deletion of a pinned commit.

---

