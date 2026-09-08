# BRIEF — the phase-log mining pass (Phase 33.5, task 14.5, item 3)

You are a READ-ONLY subagent on one bounded task. Do NOT run the repository's session-start protocol; do NOT read
PROJECT_CONTEXT.md, phase-ends/DIGEST.md or the PhaseEnd files as a preamble. Your whole job is below.

## The question

The project's day-one kit (`decomp-architect/`) claims to hold the whole of the project's hindsight. Its lessons were taken from
the distilled records — the cookbook, the decision log, the accelerators ledger, the retrospective, the how-to chapters — and
NOT from the raw phase worklogs under `phase-ends/logs/`. Your slice is one of those worklogs (or a line range of one, or a few
small ones). Find every lesson in it that a FUTURE decompilation project should know on day one **and that is banked NOWHERE
in the distilled records**. Only those. A lesson that is already recorded anywhere is a duplicate, not a finding.

## What counts as a lesson

A generalisable "do this sooner / never do this / the instrument was the wall / this is the mechanism" — the kind of thing the
accelerators ledger (`docs/accelerators.md`) and the kernels (`decomp-architect/corpus/decomp-kernels.md`) record. Not: a
function-specific matching idiom (those belong in the cookbook and almost all are there), a status line, a number, a task
ticked, a pivot already in the decision log. Prefer lessons with a COST attached (what it cost to learn late) and a
portable shape (true for another console / another compiler / another agent harness).

## The "already banked?" test — mandatory, recorded per candidate

For every candidate, run 2–3 greps with DISTINCT phrasings of its key terms (case-insensitive, `grep -n -i`) over ALL of:
```
docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md docs/retrospective.md
docs/wave-playbook.md docs/how-to-ai-decomp/*.md decomp-architect/corpus/decomp-kernels.md
decomp-architect/templates/registry-E.decomp.md phase-ends/DIGEST.md
```
(`docs/matching-cookbook.md` is 3.5 MB — grep it, never read it.) Record the exact grep commands and their hit counts. If any
hit records the same lesson (read the hit's surrounding lines to judge), the candidate is ALREADY-BANKED: list it in one line
with `file:line` of where it lives, and move on. If the greps find nothing that records it, it is NEW.

## Reading your slice

Read your file(s) with the Read tool in pages (offset/limit of ~400 lines); very long lines are normal. Read ALL of your
assigned range — your report states the lines read as a denominator. Do not skim; the lessons hide in the middle of task
entries ("what went wrong", "deviation", "finding", "lesson", "sooner", "cost", "wrong", "false", "instrument", "wall").

## The deliverable — write it EARLY, append as you go

Create your output file FIRST (header + empty sections), then append each candidate as you find it. Path and schema:

```
# Log mining — <slice name>
Files/ranges: <file>:<first>-<last> …  ·  Lines read: N of N
Candidates considered: N · NEW: N · ALREADY-BANKED: N

## NEW
### C1 — <one-line lesson, imperative or law form>
- **Evidence:** `<file>:<line-range>` — a quotation of at most 3 lines
- **What happened / what it cost:** <two or three sentences from the log's own facts>
- **Not banked — greps:** `grep -n -i '<phrase 1>' <files>` → 0; `grep -n -i '<phrase 2>' …` → 0; `grep -n -i '<phrase 3>' …` → N (hits are about <something else>)
- **Proposed home:** DK (a kernel) | G (a rule) | accelerator | cookbook | decision-log | NOT-PORTABLE (this project only — say why)
- **Portable because:** <one line>

## ALREADY-BANKED (one line each)
- <lesson> — lives at `<file>:<line>`
```

## Hard constraints

- Read-only except your ONE output file under `.run/P33.5/log-mining/`. No git commands. Nothing under `/tmp` or `~/.claude`.
  Do not edit any repository file. Do not create other files.
- Quote line numbers from the Read tool; a lesson without an evidence line is not a finding.
- Do not invent lessons the log does not contain, and do not "improve" a banked lesson into a new one.
- Your FINAL message is exactly one JSON line: `{"slice": "...", "file": ".run/P33.5/log-mining/<slice>.md", "lines_read": N, "considered": N, "new": N, "banked": N}`
- Budget: finish within your context; if you are running out, write what you have (the file is the deliverable) and end
  with the JSON line marking `"partial": true` and the last line read.
