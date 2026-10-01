---
name: retire-doc-consumers
description: Grep and repoint tools, Makefile and docs that read a doc being retired, in the same task
---

# Retiring a doc without breaking its consumers

Captured 2026-09-30 from .run/P38/phaseend/sk_retire.md#Workflow.

## When to use
moving a doc to docs/retired or deleting it

## Steps
- For every doc a migration or cleanup moves to `docs/retired/` (or deletes), grep its path in `tools/`, `Makefile`
  and `docs/` in the same task: `grep -rn '<path>' tools Makefile docs`.
- Repoint each consumer to the successor (or to the retired copy when none exists) and record the mapping.
- Then run `make tools-health` (needs a complete build/: R22 first) and `make kit-corpus`; both read docs.
- P38 T1: the PA3 migration retired SETUP.md, matching-cookbook.md, cookbook-index.md and effort-map.md; four
  tools-health reds and 36 broken links came from that one cause.
Origin: P38 T1 summary.
