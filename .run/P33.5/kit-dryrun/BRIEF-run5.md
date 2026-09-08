# BRIEF — dry-run 5 of the decomp-architect kit (P33.5 task 14.5 item 4; the final kit after the record corpus + the mining pass)

You are ONE subagent installing a governance package into a THROWAWAY repository, from an answers file, unattended. Do NOT run the
outer repository's session-start protocol; do NOT read its PROJECT_CONTEXT.md, DIGEST or PhaseEnds. Your whole job is below.

## The throwaway

`R=/home/musashi/bfm-decomp/.run/P33.5/kit-dryrun/repo` — a fresh `git init` that already contains two package folders:
`project-architect-2.0/` (ProjectArchitect 2.0, verbatim) and `decomp-architect/` (the kit under test, verbatim). Nothing else.
You install ProjectArchitect first, then the kit, exactly as their own SETUP files say — `$R/project-architect-2.0/SETUP.md`
(read it, do it, Path A = a new empty repository) and then `$R/decomp-architect/SETUP.md` (read it, do it).

## Hard constraints (write-scope guardrails — the judge diffs the outside world before/after)

- Every write lands INSIDE `$R`, except your three deliverables named below. Nothing under `~/.claude` — when ProjectArchitect's
  §6 (the home-directory step) comes, SKIP IT ENTIRELY as answers.md instructs, and record the deviation in the log.
- Every git command is `git -C "$R" …`. Never `git clean`. Never a relative `rm -rf`. Never `cd` into `$R` and stay there.
- Never push. No attribution trailers in commits. Commit by explicit path as the SETUP files say.
- Every question either installer asks is answered from `/home/musashi/bfm-decomp/.run/P33.5/kit-dryrun/answers.md`; if a needed
  key is MISSING, STOP and say so in the log — never invent, never default.
- A `✓ Verify` line that fails is RECORDED as failed in the log and the run stops at that step — never patched around, never
  "fixed" by editing the kit or the package. (The kit is under test; a failure is the finding.)
- Do not paste a literal double-brace placeholder into any tracked prose (the kit's own rule); name a placeholder in words.

## Deliverables (write them EARLY and keep them current — R67)

1. `/home/musashi/bfm-decomp/.run/P33.5/kit-dryrun/install.log` — append a line per step AS YOU GO (step id, what you did, the
   ✓ Verify result with the literal command output). Start it with the line `run 5 — clean end-to-end run of the final kit (record
   corpus + mining pass + kit_coverage)`.
2. `/home/musashi/bfm-decomp/.run/P33.5/kit-dryrun/manifest.txt` — a copy of the install manifest the kit's Step 10 writes
   (`$R/.run/decomp-architect-install-manifest.txt`), copied when it exists.
3. `/home/musashi/bfm-decomp/.run/P33.5/kit-dryrun/verdict.json` — LAST: `{"run": 5, "pa_steps_done": N, "kit_steps_done": N,
   "stopped_at": null|"Step X.Y", "commits": [subjects], "deviations": [...], "failed_verify_lines": [...]}`.

Your FINAL message is exactly one JSON line: the verdict object above.

## Notes from the earlier runs (so you do not repeat their stops)

- ProjectArchitect's ignore block writes `.run/` in directory form; the kit's Step 3.0 rewrites that one line — that is expected.
- The kit's Step 6 now installs THREE front pages (`docs/tools-manifest.md`, `docs/knowledge-corpus.md`, `docs/inherited-record.md`)
  and its verify lines are DERIVED (the manifest's own stated total; the kernels file's own "In all" figure) — read them as written.
- The kit's Step 10.5 specifies the manifest as an exact derivable set: one line per FILE, sorted, CREATED/APPENDED/SKIPPED, the
  manifest and the PhaseEnd and the archived log included, directories never, a moved file once under its final path.
- Use `command grep` (not a wrapper) for the Step 10.1 leftover-placeholder audit, scoped past both package folders as Step 10.1 says.
