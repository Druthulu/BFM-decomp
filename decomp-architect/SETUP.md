# SETUP.md — decomp-architect installer (Phase 0.5 of a ProjectArchitect 2.0 project)

> **For the human:** install ProjectArchitect 2.0 first, handing its interview `decomp-architect/intake.decomp.md` (the kit's
> `README.md`, step 1). Then, with this folder at your project root and a **fresh** Claude Code session, say:
> **"Read decomp-architect/SETUP.md and do it."** For an unattended run say instead **"Read decomp-architect/SETUP.md and do
> it; answers: <path>"** (Step 2 describes the file). Expect file-write permission prompts; nothing here writes outside the
> repository. Everything below is for the agent.

## Honesty — what this installs, and what it does not

This installer stamps **documents, configuration and one script**: the ROM firewall (the ignore file, the audit with its config
and its negative control, the CI workflow), the layout and its READMEs, the decomp rules into the registry, the overlays on the
entry-point file, the digest, the phase templates, the effort map, the cookbook and the ops reference, the methodology and the
kernels into `docs/`, the tools manifest as a task list, the memory seed, and the license/notice/README/contributing skeletons.
It does **not** install a byte gate, a splitter configuration, a compiler, a disassembler, an emulator, a permuter harness, a
decompiler context or a differential harness — those are the first phases' work, listed in `docs/tools-manifest.md` as tasks
with the source project's tool named beside each. The generation-time values (the toolchain triple, the extract and fleet-check
commands, the oracle endpoints) are written as `TODO(phase-N)` lines that the named phase replaces. The one decision it cannot
make is whether the repository starts public or private; the firewall applies either way.

---

## Step 0 — Execution contract (agent: read this first, follow it exactly)

1. **You are Claude Code, running from the project's root**, with this package at `./decomp-architect/`. Resolve two
   variables once and use them throughout: `KIT="./decomp-architect"` (if the folder is elsewhere, resolve its path) and
   `ROOT="$(git rev-parse --show-toplevel)"`. Every git command is `git -C "$ROOT" …`. Quote every path.
2. **If you are in plan mode:** your plan is exactly *"execute SETUP.md Steps 1–10 in order."* Present that, get approval,
   execute. Do not redesign, reorder or "improve" these steps.
3. **Copy templates verbatim.** Files are materialised with `cp`, then placeholders are filled with the Edit tool. **Never
   retype a template's body from memory.** Placeholders come in two classes (`templates/PLACEHOLDERS.md` is the contract):
   **copy-time** — answered once at Step 2 and filled wherever a template is copied in; **generation-time** — written as a
   literal `TODO(phase-N)` line at Step 8 (`{{TOOLCHAIN_TRIPLE}}` → `TODO(phase-4)`, `{{EXTRACT_CMD}}` → `TODO(phase-1)`,
   `{{FLEET_CHECK_CMD}}` → `TODO(phase-3)`, `{{DISASSEMBLER_MCP}}` and `{{EMULATOR_BRIDGE}}` → `TODO(phase-2)`). Step 10's
   audit catches any leftover.
4. **Marked sections, never edits.** Every append lands under the block's own heading — its **marker** — at the END of the
   target, or at the one insertion point a step names. A target that already contains the marker is SKIPPED. Nothing above
   a marker is ever edited — with ONE named exception, Step 3.0: ProjectArchitect's bare `.run/` ignore line is rewritten to
   `/.run/*` (the two forms ignore the same files; without it no re-include under `.run/` can ever work). Everything else
   ProjectArchitect stamped stays byte-identical.
5. **Every step self-verifies** (the ✓ line). If a verification fails: STOP, report exactly what failed, and wait — do not
   improvise around it.
6. **Idempotent:** every step begins with an existence or marker check and a SKIP branch. Re-running this file after a crash
   resumes at the first unticked checkbox of the Phase-0.5 `CURRENT_PHASE.md` (Step 1 creates it).
7. **Git and write scope:** commits add only the files this installer created or appended, **by explicit path** (never
   `git add -A`); no attribution trailers; **never push**; never `git clean` (in a decomp the game-derived data is
   ignored-but-present); never remove a directory with a relative `rm -rf` — the one deletion below is one explicit file;
   **never write under the home directory** (`~/.claude` is ProjectArchitect's; the project's memory lives at the
   repository's `.claude-state/memory/`).
8. **Interaction:** the developer answers once, at Step 2 — or the `answers:` file answers for them. An unanswered question
   STOPs; nothing is defaulted silently.

## Step 1 — Prerequisites: the version pin, the path, the registry precondition, the phase file

1. `git -C "$ROOT" rev-parse --show-toplevel` succeeds (ProjectArchitect requires a git repository too).
2. **The version pin.** All of these must hold, else STOP with *"Install ProjectArchitect 2.0 first (its Path A), handing its
   interview decomp-architect/intake.decomp.md; this kit overlays version 2.0 exactly"*:
   `grep -q '^> \*\*Version:\*\* 2\.0' docs/project-architect.md` · `test -f RULES_REGISTRY.md` · `test -d phase-ends` ·
   `test -f PROJECT_CONTEXT.md` · `test -f CLAUDE.md` · `test -f phase-ends/PhaseEnd_Phase0.md` (the ProjectArchitect install
   phase is closed) · `test -f phase-ends/CURRENT_PHASE.template.md` · `test -f phase-ends/PhaseEnd.template.md` ·
   `test -f docs/effort-map.md` · `test -f docs/ops-setup.md` · `ls docs/*cookbook*.md` lists exactly one file ·
   `test -d .claude-state/memory`.
3. **The ladder is in the constitution.** `grep -q 'Governance and the firewall' PROJECT_CONTEXT.md` (the Phase-0 name from
   the intake's ladder). If it fails, the intake was not handed to the generation step. STOP and give the developer the two
   options: re-run ProjectArchitect's install on a fresh repository with the intake, or proceed and record, in this phase's
   PhaseEnd, the constitution correction that the roadmap of record is the intake's Part B (copied to `docs/decomp-ladder.md`
   at Step 6 in that case) — the constitution itself is never edited (ProjectArchitect P1). Record the choice in the log.
4. **The registry precondition.** Between the `## §E` heading and the `## §E′` heading of `RULES_REGISTRY.md` there must be no
   `### G` heading (the intake's Part D asked the generation step to leave only a one-line pointer). If rules G1…Gk already
   exist there, Step 7 uses its renumber-by-offset fallback; note k now in the log.
5. **Path A only.** A repository that already holds a decompilation — any `src/*.c`, a splitter configuration under
   `config/`, a `Makefile` with a build target — is an explicit STOP: *"an existing decompilation repository is out of this
   version's scope; the kit installs into a fresh ProjectArchitect 2.0 project only."*
6. **The phase file.** If `phase-ends/CURRENT_PHASE.md` exists and names Phase 0.5 → resume from its first unticked step.
   Else `cp phase-ends/CURRENT_PHASE.template.md phase-ends/CURRENT_PHASE.md` and fill it: *"Phase 0.5 — decomp-architect:
   the decomp overlay"*, started today, the milestone = Step 10's verify list, the checklist = Steps 2–10 as checkboxes.

✓ *Verify:* every test in 2 passes; 3 and 5 hold; the §E state is recorded; `CURRENT_PHASE.md` names Phase 0.5 and lists
Steps 2–10.

## Step 2 — The game interview (the copy-time answers; `answers:` for unattended runs)

1. **Read back from ProjectArchitect** (never re-ask): `{{PROJECT_NAME}}` = the title on `CLAUDE.md`'s first line (after the
   dash); `{{COOKBOOK_NAME}}` = the file name of the one `docs/*cookbook*.md`; `{{INSTALL_DATE}}` = today in the format
   ProjectArchitect used (an `answers:` file may pin it).
2. **Ask the developer, in ONE compact round**, offering a default where one is sane, the thirteen copy-time values:
   `{{GAME_TITLE}}`, `{{PLATFORM}}`, `{{GAME_SERIAL}}`, `{{TARGET_BINARY}}` (the main executable's file name on the medium),
   `{{DUMP_PATH}}` (an ABSOLUTE path to the developer's own dump; it must lie OUTSIDE the repository, and it is never copied
   by this installer), `{{CONTAINER_LAYOUT}}`, `{{SDK_EVIDENCE}}`, `{{COMPILER_FAMILY}}` (a candidate set, not the pin),
   `{{COMMUNITY_WORK}}` ("none found on <date>" is an answer), `{{PROJECT_GOALS}}`, `{{LICENSE_CHOICE}}` (for the project's own
   work; no license is asserted over the decompiled source), `{{AI_DISCLOSURE}}` (one project-level sentence),
   `{{PUBLIC_OR_PRIVATE}}` (the day-one visibility; the firewall applies either way).
3. **Unattended mode.** If the developer's instruction carried `answers: <path>`, read that file: one `KEY: value` line per
   key (the placeholder name without braces; `#` starts a comment), the thirteen keys above plus the optional
   `INSTALL_DATE`. Every question is answered from the file; **a missing or empty key STOPs, naming the key** — it is never
   defaulted.
4. Record every answer in the Phase-0.5 log (`CURRENT_PHASE.md`), so the PhaseEnd can carry them.

✓ *Verify:* all sixteen values are non-empty; `{{DUMP_PATH}}` is absolute and not under `$ROOT`; `{{COOKBOOK_NAME}}` resolves
to an existing file; in unattended mode, the file supplied every key.

## Step 3 — The ROM firewall, in force from this commit

0. **The one edit above a marker.** ProjectArchitect's own ignore block writes the directory form `.run/`. Git does not
   descend into an excluded directory, so beneath that line no `!` re-include under `.run/` — the README of Step 4, the
   dated-exception convention for tracking irreplaceable scratch evidence — could ever take effect. If `.gitignore` contains a
   line that is exactly `.run/`, rewrite THAT ONE LINE to `/.run/*` (same files ignored; the by-contents form). SKIP if no such
   line exists (idempotent; runs even when Step 3.1's marker is already present). This is the single edit this installer makes
   above a marker (Step 0.4).
   ✓ `git -C "$ROOT" check-ignore -v .run/x` names a `/.run/*` line; `grep -cx '\.run/' .gitignore` prints 0.
1. **The ignore file.** If `.gitignore` does not contain the marker line `# ROM firewall — in force from the FIRST commit`:
   append one dated comment line `# ---- decomp-architect Phase 0.5, installed {{INSTALL_DATE}} ----` and then the whole of
   `$KIT/templates/gitignore.decomp`. Never remove or reorder ProjectArchitect's block above it.
2. `cp "$KIT/templates/firewall.txt" config/firewall.txt`; fill `{{TARGET_BINARY}}`.
3. `cp "$KIT/templates/firewall-fixture/blob.sha1" config/firewall-fixture.sha1` (the hash only — the blob itself is never
   tracked; `templates/firewall-fixture/README.md` says why).
4. `cp "$KIT/templates/audit_public.template.py" tools/audit_public.py && chmod +x tools/audit_public.py`.
5. `mkdir -p .github/workflows && cp "$KIT/templates/no-rom.template.yml" .github/workflows/no-rom.yml`.
6. **The negative control — an audit that has not failed on its fixture is not trusted to pass:**
   `mkdir -p .run/firewall-control && cp "$KIT/templates/firewall-fixture/blob.bin" .run/firewall-control/planted.bin`, then
   `python3 tools/audit_public.py --paths .run/firewall-control/planted.bin` **must exit 1** and print
   `OFFENDER .run/firewall-control/planted.bin`. Then `rm -f .run/firewall-control/planted.bin` (the one deletion in this
   installer: an explicit file), and `python3 tools/audit_public.py` (the tracked tree) **must exit 0**. If the control passes
   the planted blob, STOP: the fixture hash or the config is wrong; never proceed with an audit that cannot fail.
7. **The ignore probes.** Positive — each must succeed: `git -C "$ROOT" check-ignore -q disks/x.bin`, `… asm/x.s`,
   `… extracted/x`, `… dumps/x.bin`, `… ghidra/x`, `… tools/psyq/x`, `… .claude-state/transcripts/x`, `… .run/scratch/x`.
   Negative — each must FAIL (exit 1): `git -C "$ROOT" check-ignore -q src/main.c`, `… config/x.yaml`,
   `… extracted/retail/manifest.jsonl`, `… .run/README.md`, `… .claude-state/memory/MEMORY.md`.

✓ *Verify:* the marker is in `.gitignore` exactly once; the five files exist; the control failed then passed; every probe
behaved as listed.

## Step 4 — The layout and its two READMEs

1. `mkdir -p src config tools docs .run disks extracted/retail dumps` (the ignored ones exist so the probes above are real
   directories; nothing is put in them).
2. `cp "$KIT/templates/docs-README.md" docs/README.md`; fill `{{PROJECT_NAME}}`, `{{INSTALL_DATE}}`, `{{CONTAINER_LAYOUT}}`.
3. `cp "$KIT/templates/run-README.md" .run/README.md`; fill `{{PROJECT_NAME}}`, `{{INSTALL_DATE}}` (the ignore file re-includes
   exactly this one file under `.run/`).

✓ *Verify:* the directories exist; both READMEs exist and contain no `{{`; `git -C "$ROOT" check-ignore -q .run/README.md`
FAILS (the README is trackable).

## Step 5 — The bootstrap skeleton, and the checkpoint commit

1. `cp "$KIT/templates/bootstrap.template.sh" tools/bootstrap.sh && chmod +x tools/bootstrap.sh && bash -n tools/bootstrap.sh`.
2. Tick Steps 2–5 in `CURRENT_PHASE.md`; write the Step-2 answers into its log if not yet done.
3. **Checkpoint commit, by explicit path:** `.gitignore config/firewall.txt config/firewall-fixture.sha1 tools/audit_public.py
   .github/workflows/no-rom.yml docs/README.md .run/README.md tools/bootstrap.sh phase-ends/CURRENT_PHASE.md` — message
   `chore: decomp-architect Phase 0.5 — firewall, layout, bootstrap` (no trailer). Do not push.

✓ *Verify:* `bash -n` clean; the commit exists; `git -C "$ROOT" status --porcelain` lists none of those paths;
`git -C "$ROOT" log -1 --format=%B` contains no attribution trailer.

## Step 6 — The flywheel skeleton (documents that outlive the package)

1. `docs/wave-playbook.md` — CREATE from `pa-overlays.md` **Block 6** (the fenced body under that heading, copied verbatim);
   fill `{{INSTALL_DATE}}`. SKIP if the file exists.
2. `docs/tools-manifest.md` — `cp "$KIT/tools/MANIFEST.md"` and prepend one line: *"Installed by decomp-architect on
   {{INSTALL_DATE}}; every row is a task for its phase; the verbatim reference implementation of each is in the kit's
   `corpus/tools/<phase>/` (the kit master copy — see the ops reference's corpus row)."*
2b. `docs/knowledge-corpus.md` — `cp "$KIT/corpus/cookbook/README.md"` (the front page that says what transfers from the inherited
   cookbook, its symptom index and its codegen map — the files themselves stay in the kit master copy beside it).
2c. `docs/inherited-record.md` — `cp "$KIT/corpus/record/README.md"` (the front page of the inherited record: the source project's
   how-to, decision log, accelerators, retrospective, playbook, effort doctrine, readability charter and every phase-end — the files
   stay in the kit master copy beside it; a rule's or kernel's `provenance:` line is followed there).
3. `docs/decomp-kernels.md` — `cp "$KIT/corpus/decomp-kernels.md"` (the constitution's ladder cites kernels by id; they must
   survive the package's deletion).
4. If Step 1.3 chose "proceed": `docs/decomp-ladder.md` — `cp "$KIT/intake.decomp.md"` with a banner naming it the roadmap of
   record for this project.

✓ *Verify:* the files exist; `grep -c '^| [0-9]' docs/wave-playbook.md` ≥ 11 (the step table); `grep -c '^### DK-'
docs/decomp-kernels.md` equals the "In all" figure of that file's own Coverage section (both derived, never typed here); the manifest's row count equals the total its own header states (`grep -c '^| \`'
docs/tools-manifest.md` == the "Table rows in all: N" figure in its Coverage line — the live rows plus the superseded pointer
rows, both derived, never typed here); `docs/knowledge-corpus.md` and `docs/inherited-record.md` exist.

## Step 7 — The registry: the decomp rules into §E

1. Marker: the seed's own heading line `## §E — Project-specific rules (a matching decompilation)`. If `RULES_REGISTRY.md`
   contains it → SKIP.
2. Re-assert the precondition of Step 1.4 (no `### G` heading between `## §E` and `## §E′`).
3. Take the seed body: from the line of `$KIT/templates/registry-E.decomp.md` that starts `## §E —` to its end (the leading
   HTML comment is dropped). **Insert it immediately BEFORE the `## §E′` heading line** (ProjectArchitect's own `## §E`
   heading, its italic paragraph and the pointer line stay above; the registry then reads: the §E heading, the pointer, the
   installed block G1–G67, then §E′ and §F).
4. **Fallback** (only if Step 1.4 found rules G1…Gk in §E): renumber the seed body — every `G<number>` token inside the body,
   headings and cross-references alike — by `+k` with one scripted pass, change its heading to end `— installed as
   G<k+1>–G<k+67>`, then insert as in 3. Record the offset in the log and the PhaseEnd.

✓ *Verify:* `grep -c '^### G' RULES_REGISTRY.md` = 67 (or 67 + k); the marker appears exactly once; `## §E′` still follows the
block; the session-start recitation in `CLAUDE.md` already covers "every §E project rule" — nothing to change there.

## Step 8 — The overlays and the skeletons

*For each append: grep the target for the marker first; SKIP if present. Fill copy-time placeholders; write generation-time
ones as the `TODO(phase-N)` literals of Step 0.3.*

1. **`CLAUDE.md`** ← `$KIT/templates/CLAUDE.decomp-overlay.md` from its `## Decomp fail-safes` line to the end (the leading HTML
   comment dropped), APPENDED. Marker `## Decomp fail-safes`. Fill `{{INSTALL_DATE}}`, `{{COOKBOOK_NAME}}`; `{{FLEET_CHECK_CMD}}`
   → `TODO(phase-3)`.
2. **`phase-ends/DIGEST.md`** ← `pa-overlays.md` **Block 1**, CREATE if absent. Fill `{{INSTALL_DATE}}`. Then write its part 2's
   first synopsis line for Phase 0 (ProjectArchitect's install, from `PhaseEnd_Phase0.md`'s recap) — one sentence.
3. **`phase-ends/CURRENT_PHASE.template.md`** ← **Block 2** APPENDED at the end. Marker `## 🛑 SESSION CHECKPOINT`. (Every phase
   from 1 on inherits the replayable block; the Phase-0.5 file, already created, keeps ProjectArchitect's shape.)
4. **`phase-ends/PhaseEnd.template.md`** ← **Block 3** INSERTED immediately before the `## PhaseEnd Changelog` line. Marker =
   the block's heading.
5. **`docs/effort-map.md`** ← **Block 4** APPENDED. Marker `## Per-phase effort map (decomp ladder`. Fill `{{INSTALL_DATE}}`.
6. **`docs/{{COOKBOOK_NAME}}`** ← **Block 5** APPENDED. Marker `## The decomp entry shape`. Fill `{{INSTALL_DATE}}`,
   `{{SDK_EVIDENCE}}`; `{{TOOLCHAIN_TRIPLE}}` → `TODO(phase-4)`.
7. **`docs/ops-setup.md`** ← `$KIT/templates/ops-setup.decomp.md` from its `## Decomp environment` line (the HTML comment
   dropped), APPENDED. Marker `## Decomp environment`. Fill every copy-time placeholder it names; the five generation-time
   ones as their `TODO(phase-N)` literals.
8. **`config/decomp-hooks.snippet.json`** and **`config/mcp.json.template`** ← **Block 7**'s two JSON bodies, CREATE each if
   absent; `{{DISASSEMBLER_MCP}}` → `TODO(phase-2)`. `.claude/settings.json` and `.mcp.json` are NOT touched (Phase 2 merges and
   copies them when the server exists). Validate both files parse as JSON.
9. **`docs/decomp-architect.md`** ← `cp "$KIT/decomp-architect.md"` (the methodology survives the package's deletion).
10. **The skeletons.** `LICENSE`: if absent, `cp "$KIT/templates/LICENSE.skeleton.md" LICENSE` and fill `{{LICENSE_CHOICE}}`,
    and flag in the final message that it must be replaced by the license's verbatim text before the first push; if present,
    leave it and note it. `src/NOTICE.md` ← `templates/NOTICE.src.md` (fill `{{GAME_TITLE}}`, `{{PLATFORM}}`, `{{GAME_SERIAL}}`,
    `{{LICENSE_CHOICE}}`). `README.md` and `CONTRIBUTING.md`: if absent, create from the skeletons (fill `{{PROJECT_NAME}}`,
    `{{GAME_TITLE}}`, `{{PLATFORM}}`, `{{GAME_SERIAL}}`, `{{PROJECT_GOALS}}`, `{{AI_DISCLOSURE}}`, `{{PUBLIC_OR_PRIVATE}}`,
    `{{COMMUNITY_WORK}}`, `{{LICENSE_CHOICE}}`); if present, write the filled skeleton beside it as `README.decomp-skeleton.md` /
    `CONTRIBUTING.decomp-skeleton.md` and tell the developer to merge by hand. `.clang-format`: `cp` if absent, else SKIP with
    a note. `Makefile`: if absent, create it with the content of `templates/make-format.snippet.mk`; if present, APPEND the
    snippet under its marker `.PHONY: format format-check`.

✓ *Verify:* each marker appears exactly once in its target; `grep -c '{{' CLAUDE.md docs/ops-setup.md docs/effort-map.md
docs/{{COOKBOOK_NAME}} phase-ends/DIGEST.md src/NOTICE.md` = 0 for each; `grep -c 'TODO(phase-' docs/ops-setup.md` ≥ 5; both
JSON files parse; `docs/decomp-architect.md` exists.

## Step 9 — The memory seed

1. Assert the memory directory is the one ProjectArchitect configured: the `autoMemoryDirectory` value in
   `.claude/settings.local.json` ends with `/.claude-state/memory`; the directory exists. **Nothing is written under the home
   directory.**
2. `cp "$KIT/memory-seed/"*.md .claude-state/memory/` — every file EXCEPT `MEMORY.md`.
3. APPEND the kit's index rows to `.claude-state/memory/MEMORY.md`: a heading `## decomp-architect seed` (the marker; SKIP if
   present), then every `- [` line of `$KIT/memory-seed/MEMORY.md` in order.
4. State plainly: **seeded memories activate from the NEXT session.**

✓ *Verify:* `ls .claude-state/memory/*.md | grep -vc MEMORY.md` = 34 (ProjectArchitect's 16 + the kit's 18); every link in
the appended rows resolves to a file; the marker appears once.

## Step 10 — Verify, the manifest, gitignore the package, close Phase 0.5, hard stop

1. **The leftover-placeholder audit:** `command grep -rln '{{' --include='*.md' --include='*.txt' --include='*.sh'
   --include='*.py' --include='*.yml' --include='*.json' --include='*.mk' --include='Makefile' . | grep -vE
   '^\./(decomp-architect|project-architect-2\.0)/'` — with a grep that does NOT honour ignore files (plain GNU grep via
   `command grep`; a wrapper that honours `.gitignore` silently narrows the result — if in doubt, `find . -type f | xargs grep -l
   '{{'` and filter the same way); both package folders are dropped by the filter, never by ignore rules. The result may list
   ONLY `./docs/project-architect.md`, `./phase-ends/CURRENT_PHASE.template.md` and `./phase-ends/PhaseEnd.template.md`
   (ProjectArchitect's own reference spec and templates). Anything else = an unfilled placeholder → fill it, then re-run.
   The audit cannot tell an unfilled placeholder from prose that QUOTES the token, so the rule that keeps it a true signal is:
   **a tracked document never pastes a literal double-brace token — it names the placeholder in prose** (this installer's own
   phase file and PhaseEnd included; the dry-run tripped on both).
2. `python3 tools/audit_public.py` → exit 0. `bash -n tools/bootstrap.sh`. Syntax-check the audit WITHOUT writing bytecode:
   `python3 -c "compile(open('tools/audit_public.py').read(), 'tools/audit_public.py', 'exec')"` (the `py_compile` module always
   writes a `__pycache__`, whatever the environment says; a `__pycache__` left in a fresh install is untracked litter).
3. `grep -c '^### G' RULES_REGISTRY.md` = 67 (+ the offset, if any).
4. **Gitignore the package:** append to `.gitignore` under the comment `# decomp-architect (the day-one kit's package folder —
   safe to delete after install)` the line `decomp-architect/` (SKIP if present).
5. **The install manifest:** write `.run/decomp-architect-install-manifest.txt`, sorted, one line per FILE, and print it.
   Exactly these lines and no others: `CREATED <path>` for every file this installer created (Steps 1–9, plus this step's own
   manifest file, the PhaseEnd and the archived phase log of step 6 — write the manifest after step 6 so they are in it; a file
   created and then moved is listed once, under its final path, so the phase file appears only as `phase-ends/logs/PhaseLog_0.5.md`);
   `APPENDED <path> (<marker>)` for every file it appended a marked section to (`.gitignore` once, with both markers named);
   `SKIPPED <path> (<reason>)` for every OPTIONAL artifact this run did not write — the two `*.decomp-skeleton.md` beside an
   existing README/CONTRIBUTING, `docs/decomp-ladder.md`, `.claude/settings.json` and `.mcp.json` (never touched at Phase 0.5) —
   so the reader sees the decision, not an absence. Directories are never listed. (An unattended run diffs the manifest against
   an expected one, so the set of lines must be derivable from this rule alone.)
6. **Close the phase.** Tick Steps 6–10. Write `phase-ends/PhaseEnd_Phase0.5.md` from `phase-ends/PhaseEnd.template.md` (which
   now carries the narrative axis): the Build Log = the manifest; Deviations (an existing README/LICENSE left beside a
   skeleton, a registry offset, the Step-1.3 choice); Rules Added = *"G1–G67 installed into §E — the kit's seed; the origin
   of each is its provenance line"*; the narrative axis filled honestly (what the install assumed, what it found); the
   Plain-English Recap last. Append the Phase-0.5 synopsis (one paragraph) to `phase-ends/DIGEST.md` part 2 — the digest's own
   maintenance rule. Run `bash tools/backup-claude-state.sh` (ProjectArchitect's state sweep; the transcripts it
   copies are ignored by the class-7 line, the memory files are tracked). Then `git -C "$ROOT" mv phase-ends/CURRENT_PHASE.md
   phase-ends/logs/PhaseLog_0.5.md`.
7. **The close commit, by explicit path:** every path in the manifest that this step or Steps 6–9 created or appended, plus
   `.gitignore`, `phase-ends/PhaseEnd_Phase0.5.md`, `phase-ends/logs/PhaseLog_0.5.md`, `.claude-state/memory/…`. Message
   `chore: decomp-architect Phase 0.5 — the decomp overlay installed` (no trailer). Do not push — tell the developer to review
   and push.
8. **Final message, in order:** (a) the install manifest; (b) *"You may delete `decomp-architect/` from this repository (it is
   gitignored; keep the master copy elsewhere) — `docs/decomp-architect.md`, `docs/decomp-kernels.md`, `docs/tools-manifest.md`
   and the registry carry what matters"*; (c) if `LICENSE` was written from the skeleton: *"Replace `LICENSE` with the license's
   verbatim text before the first push"*; (d) *"Start a **fresh session** (the seeded memories activate at startup) and say
   **'Begin Phase 1'**"*; (e) the plain-English recap, last. Then **🛑 HARD STOP** — no previewing Phase 1, no continuing.

✓ *Verify (before the final message):* the PhaseEnd exists; `CURRENT_PHASE.md` is archived, not deleted; both commits are
present and trailer-free; `git -C "$ROOT" status --porcelain` is empty apart from intentionally uncommitted items (none).

---

## Install manifest (what exists after a completed install)

```
.gitignore (+ the firewall block, + decomp-architect/)     config/firewall.txt         config/firewall-fixture.sha1
tools/audit_public.py       .github/workflows/no-rom.yml    tools/bootstrap.sh          docs/README.md      .run/README.md
docs/wave-playbook.md       docs/tools-manifest.md          docs/decomp-kernels.md      docs/decomp-architect.md
RULES_REGISTRY.md (+ §E G1–G67)                              CLAUDE.md (+ Decomp fail-safes, Session-start extras)
phase-ends/DIGEST.md        phase-ends/CURRENT_PHASE.template.md (+ the checkpoint block)
phase-ends/PhaseEnd.template.md (+ the narrative axis)      docs/effort-map.md (+ the decomp rows)
docs/<cookbook> (+ the entry shape and the triage table)   docs/ops-setup.md (+ Decomp environment)
config/decomp-hooks.snippet.json   config/mcp.json.template LICENSE (skeleton, or untouched)   src/NOTICE.md
README.md, CONTRIBUTING.md (created, or *.decomp-skeleton.md beside the existing ones)   .clang-format   Makefile (+ format)
.claude-state/memory/ (+ 16 seeds, + the index rows)        phase-ends/PhaseEnd_Phase0.5.md   phase-ends/logs/PhaseLog_0.5.md
```

## Troubleshooting

- **The version line is not found** → the project is not a ProjectArchitect 2.0 install; install it first (its Path A) with the
  intake, then re-run this file.
- **§E already holds rules** → Step 7's renumber-by-offset fallback; the offset goes in the log and the PhaseEnd.
- **A README, LICENSE, CONTRIBUTING or `.clang-format` already exists** → the skeleton is written beside it (or skipped) and
  named in the final message; merging is the developer's.
- **The negative probe for `.run/README.md` fails (the path is ignored)** → ProjectArchitect's bare `.run/` line is still in
  `.gitignore`; Step 3.0 did not run. Re-run Step 3.
- **The control passes the planted blob** → STOP; `config/firewall-fixture.sha1` or `config/firewall.txt` is wrong. An audit
  that cannot fail proves nothing.
- **The `answers:` file lacks a key** → STOP, naming the key; unattended runs never default.
- **Interrupted mid-install** → say "Read decomp-architect/SETUP.md and do it" again; Step 1.6 resumes at the first unticked
  checkbox of the Phase-0.5 `CURRENT_PHASE.md`.
- **The disassembler or emulator is not reachable** → not an install concern; Phase 2 sets them up, and `docs/ops-setup.md`
  carries their `TODO(phase-2)` rows until then.
