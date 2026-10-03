---
name: tools-edit-kit-corpus
description: After any tools/ edit: make kit-corpus, tool_dictionary row for new files, then make tools-health
---

# Tools Edit Kit Corpus

Captured 2026-10-02 from /home/musashi/bfm-decomp/.run/p339_close/skill_tools-edit-kit-corpus.md.

## When to use
Any edit under tools/ or a new harness tool

## Steps
# tools-edit-kit-corpus
## Steps
1. Edit the tool.
2. New file: add a `config/tool_dictionary.tsv` row.
3. `make kit-corpus` (refreshes the tracked copy under decomp-architect/corpus/tools/P10/).
4. `make tools-health` must say OK (`GAP corpus copy differs` = step 3 skipped).
5. Commit the tool and its corpus copy together; H7 line in docs/ops/ in the same task.
Source: P3.39 tasks/T1.md:35, T2.md:36, T9.md:28.
