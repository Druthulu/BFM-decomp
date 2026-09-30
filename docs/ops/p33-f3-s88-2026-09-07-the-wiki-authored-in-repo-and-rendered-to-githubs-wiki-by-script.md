### P33 F3 (S88, 2026-09-07) — the wiki, authored in-repo and rendered to GitHub's wiki by script
- **Why in-repo (decision 8, gate 1).** The project wiki is versioned, link-checked and covered by the history rewrite, so it
  lives in **`docs/wiki/`** (11 pages + `_Sidebar.md`: Home · Build from your own disc · Toolchain setup · Repository
  layout · The matching workflow · The dedup engine · Overlays and modules · Ghidra rebuild from text · Verification and
  progress · Contributing and the no-ROM policy · How-to-AI-decomp) and **`docs/how-to-ai-decomp/`** (the 13 chapters 00–12:
  README · governance · byte gate · bootstrap order · oracles and instruments · cards/lanes/waves · knowledge base ·
  compiler source · models and budgets · economics · integration and propagation · publishing · failure museum), written
  as ordinary Markdown with RELATIVE links. `tools/doc_links.py` checks every file in both directories by default
  (`DEFAULT_GLOBS`, expanded at run time, counted with the rest); `docs/doc_links_pending.txt` carried the not-yet-written
  pages during the task and is EMPTY again (`--strict` PASS).
- **Render + sync:** the two tool rows above. A GitHub wiki addresses pages by NAME (no `.md`, no directories), so the
  renderer rewrites links rather than the authors avoiding them; the sync replaces the wiki's page set wholesale.
  Measured S88: 25 pages rendered, 264 relative links rewritten, 1,896 lines / 163 KB of source; `doc_links --strict`: 40 documents, 290 links, 0 broken; dry run before the wiki exists → "not clonable yet … dry run OK", exit 0.
- **Sources the pages were distilled from** (no new facts were invented; every number is a recorded measurement):
  `docs/portable-decomp-workflow.md` and `docs/hindsight-study.md` (both since archived under `docs/sunset/`, Phase 33.5 — the
  chapters absorbed them), `docs/generic-decomp-package.md`, `docs/accelerators.md`
  (A1–A4, #15), `docs/effort-map.md`, `docs/retrospective.md`, `docs/story.md`, `docs/wave-playbook.md`,
  `docs/public-flip-runbook.md`, `docs/verification.md`, `README.md`, SETUP §4 / P33 B5 / P33 D1–D3, `docs/disc-completeness.md`,
  `docs/memory-map.md` (the load slots), the docstrings of `match_one` / `rtu_match` / `harvest_verify` / `gate_main` /
  `dedup_propagate` / `ghidra_rebuild.sh`, `config/dedup.us.yaml`'s header, the S88 probe defect (R57).
- **After the flip (Drew):** create the first page in the GitHub UI, then `tools/wiki_sync.sh --push` (runbook §11).


