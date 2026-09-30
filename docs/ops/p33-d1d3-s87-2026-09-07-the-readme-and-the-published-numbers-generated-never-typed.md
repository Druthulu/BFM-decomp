### P33 D1–D3 (S87, 2026-09-07) — the README and the published numbers, generated never typed
- **D1 README:** rewritten from the Phase-19 text (every number was stale). Its numbers block is generated: `tools/progress.py
  --json` writes `docs/progress.json` (every metric with its denominator, R41; no run date so `make report` never churns it)
  and `--readme` rewrites the block between `<!-- progress:begin -->` / `<!-- progress:end -->`; `--check` asserts both (and the
  badges) are fresh and sits in `make audit-digest`; `make report BINARY=main` regenerates all of it after the fleet digest.
- **D2:** `LICENSE` (AGPL-3.0 verbatim from gnu.org, 661 lines), `src/NOTICE.md` (no license asserted over `src/`; never the
  phrase "clean-room"), `THIRD_PARTY.md` (every license from the upstream LICENSE file or the GitHub API's license metadata:
  old-gcc and ghidra_psx_ldr publish NONE — download-only rows), `tools/README.md` (the one AGPL statement).
- **D3:** badges (shields endpoint JSON, colour by percentage), `tools/objdiff_report.py` (validated: `objdiff-cli report
  changes report.json report.json` parses and diffs it; a mutated unit shows as a change), `tools/frogress_upload.py`
  (dry-run default), `.github/workflows/progress.yml` (artifact `SLUS_007.26_report`). CI never rebuilds the game: the report
  is the committed `docs/progress.json` from a local clean rebuild. Outward actions after the flip (Drew): decomp.dev
  registration, the frogress slug + key. The `objdiff-cli` binary used for validation lives in scratch (`.run/objdiff/`).
- **Outcome (P34 task 4, 2026-09-08):** **decomp.dev — DONE.** Drew registered the repo at `decomp.dev/manage/new` (game name
  "Brave Fencer Musashi", platform PlayStation); the project page **<https://decomp.dev/Druthulu/BFM-decomp>** renders unauthenticated
  (200) as "Brave Fencer Musashi • Progress Report — 100.00% decompiled | 100.00% fully linked (53.97 MB)", read from the
  `SLUS_007.26_report` artifact of the public repo's latest `progress` run (53,968,452 bytes = 13,492,113 instructions × 4). Drew set a
  hero image on the manage page (decomp.dev hosts it; nothing enters this tree). A unit's page says "No function information
  available" **by design**: `tools/objdiff_report.py` writes per-binary measures with an empty `functions` list (363,214 rows of
  `func_XXXXXXXX` names would add bulk, not information) — a Gen3 item once functions carry names. **frogress — SKIPPED this phase
  (Drew, 2026-09-08), pending by name:** the service is alive (`/projects/` lists 38 projects; a project's data endpoint answers 200;
  the API has no root page, hence `/` → 404; the code repo last pushed 2023-12), projects are admin-created on request (the decomp
  community Discord), and at 100% with generated README badges and decomp.dev live it would add only a row in that list. When wanted:
  request slug `bfm` / version `us` + a key, then `FROGRESS_API_SECRET=… .venv/bin/python tools/frogress_upload.py --push` from
  Drew's shell; verify `https://progress.deco.mp/data/bfm/us/` (404 today — the control).

