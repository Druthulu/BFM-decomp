---
name: tools-edit-kit-corpus
description: After any tools/ or Makefile edit: make kit-corpus, tool_dictionary row for new files, then make tools-health
---

# Tools Edit Kit Corpus

Captured 2026-11-10 at P3.42 T9 (re-scaffolded with --force).

## When to use
Any edit under tools/, the Makefile, or a new harness tool

## Steps
# tools-edit-kit-corpus
## Steps
1. Edit the tool (or the Makefile: tools-health.mk in the kit corpus mirrors it, so a Makefile edit stales the corpus too).
2. New file: add a `config/tool_dictionary.tsv` row (edit by script; the file is over the read guard). New tool files need `git add -N` before step 3 (C0550).
3. `make kit-corpus` (refreshes the tracked copies under decomp-architect/corpus/).
4. `make tools-health` must say OK (`GAP corpus copy differs` = step 3 skipped).
5. Commit the tool and its corpus copy together; H7 line in docs/ops/ in the same task.
Source: P3.39 tasks/T1.md:35, T2.md:36, T9.md:28; P3.42 tasks/T6.md:29 (Makefile edits).
