# Log mining — Phase33
Files/ranges: `phase-ends/logs/Phase33.md:1-1372` (whole file: the phase header, the 41-task list, the Log
2026-09-06 S86 → 2026-09-07 S89, the 🛑 checkpoint, and the VERBATIM approved plan at :894-1372)  ·  Lines read: 1372 of 1372
Candidates considered: 37 · NEW: 16 · ALREADY-BANKED: 21

> **Grep set** (used for every candidate; `$DOCS` below):
> ```
> DOCS="docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md \
> docs/retrospective.md docs/wave-playbook.md docs/how-to-ai-decomp/*.md \
> decomp-architect/corpus/decomp-kernels.md decomp-architect/templates/registry-E.decomp.md phase-ends/DIGEST.md"
> ```
> Hit counts below are totals over that whole set (`grep -n -i -c … | awk` sum), and every non-zero hit was read in context
> before the verdict.

## NEW

### C1 — A Ghidra script directory compiles as ONE bundle: a single non-compiling script disables every script in it
- **Evidence:** `phase-ends/logs/Phase33.md:186-190` — "the runs after the import failed with `Failed to get OSGi bundle
  containing script: …/ApplySymbols.java` (same for ExportAnnotations) — Ghidra compiles the script DIRECTORY as one bundle,
  so ONE file that does not compile breaks every script in it"
- **What happened / what it cost:** B5 (the Ghidra text-export + rebuild-proof task) was blocked at 87% context and had to be
  checkpointed as a WIP commit. `ExportAnnotations.java` had already exported 129 programs successfully; adding a *new,
  unrelated* file (`ImportAnnotations.java`, with a bad `LocalVariableImpl` ctor) silently broke `ApplySymbols` and
  `ExportAnnotations` too. The failure names the *working* script, not the broken one, so the error message points away
  from the cause.
- **Not banked — greps:** `grep -n -i 'OSGi' $DOCS` → 0; `grep -n -i 'script directory' $DOCS` → 0;
  `grep -n -i 'bundle containing script' $DOCS` → 0; `grep -n -i 'ExportAnnotations\|ImportAnnotations' $DOCS` → 0;
  `grep -n -i 'ghidra script' $DOCS` → 1 (a tool-count row in `09-economics.md`, not this).
- **Proposed home:** accelerator (a Ghidra-scripting section) + a failure-museum row — the error message misattributes.
- **Portable because:** every decomp that scripts Ghidra keeps its scripts in one directory; the same one-bad-file-breaks-all
  bundling applies to any plugin host that compiles a directory as a unit.

### C2 — Ghidra refuses a project path containing a component that starts with `.` — a scratch project cannot live under `.run/`
- **Evidence:** `phase-ends/logs/Phase33.md:185-186` — "its import step works: the scratch project must live under
  `build/ghidra_rebuild/proj` — Ghidra refuses a path component starting with '.'"
- **What happened / what it cost:** the whole project convention is that scratch lives under `.run/` (a memory-enforced rule
  here). The rebuild-proof harness had to be relocated to `build/` instead, discovered by a failing run rather than by
  reading a doc.
- **Not banked — greps:** `grep -n -i "path component starting with\|starting with '\.'" $DOCS` → 0;
  `grep -n -i 'refuses a path\|dot-director' $DOCS` → 0; `grep -n -i 'ExportAnnotations\|ImportAnnotations' $DOCS` → 0.
- **Proposed home:** accelerator (same Ghidra-scripting section as C1).
- **Portable because:** any project that adopts a dot-prefixed scratch directory will collide with the tools that refuse one;
  the general form is "pick the scratch directory name only after checking what your RE tool will accept".

### C3 — `git check-ignore` is SILENT for tracked paths: an ignore-coverage audit run before the untracking passes vacuously
- **Evidence:** `phase-ends/logs/Phase33.md:236-237` — "ignore coverage proven with `git check-ignore --no-index` on every
  path (the plain form is BLIND to tracked files — it reported nothing)"
- **What happened / what it cost:** in the preparatory purge commit (B9/C3) the audit that proves "every purged path is now
  ignored" is run *while the paths are still tracked*. The plain form printed nothing, which reads as "no path is ignored"
  and is indistinguishable from a run that found nothing to say. `--no-index` was required for the assertion to mean
  anything. A vacuous pass here means a later blanket `git add -A` re-adds ROM bytes to a public history.
- **Not banked — greps:** `grep -n -i 'reports nothing for tracked' $DOCS` → 0; `grep -n -i 'ignore rule.*tracked' $DOCS` → 0;
  `grep -n -i 'check-ignore' $DOCS` → 1 — `docs/decision-log.md:3473` records the *incantation and its timing*
  ("proven with `git check-ignore --no-index` on every path BEFORE the paths became untracked") but not the trap: nothing
  says the plain form is silent for tracked paths, i.e. that the naive audit **passes without checking anything**.
- **Proposed home:** accelerator, or a line appended to the existing publishing chapter's ignore step; it is a silent-false-pass
  instance of the project's dominant defect class.
- **Portable because:** every project that moves files out of git before a rewrite runs exactly this audit at exactly this
  moment, on any host.

### C4 — A coverage instrument that infers its denominator from OPEN work INVERTS at 100% — carry the scanned denominator in the artifact, and test the instrument at both endpoints
- **Evidence:** `phase-ends/logs/Phase33.md:126-129` — "Regenerating `.run/family_hseq.json` made the `audit-binaries` warning
  WORSE (6 → 217 'missing'): at 100% the map's `families` list is empty and CHECK 4 inferred coverage from family members, so
  a complete map read as empty; the P32-close warning had been a stale pre-onboarding file."
- **What happened / what it cost:** the check had been *silently green because the map was stale*; regenerating it turned one
  warning into 217. The fix was to make the artifact carry its own denominator (`"binaries": 217`, `"open_instances": 0`) and
  make the consumer read that, plus a "predates the coverage field" warning for old-format maps. The instrument was correct at
  every intermediate percentage and wrong at both endpoints.
- **Not banked — greps:** `grep -n -i 'infer.*denominator\|denominator.*infer' $DOCS` → 0;
  `grep -n -i 'complete map read as empty\|read as empty' $DOCS` → 0;
  `grep -n -i 'carries its own coverage\|carry the denominator' $DOCS` → 0; `grep -n -i 'family_hseq' $DOCS` → 13 (campaign
  selection and an R32 gap, never this inversion). R32 ("assert your COVERAGE") and R41 ("every number ships with its
  denominator") are the family this belongs to; neither states the endpoint inversion or the "denominator lives in the
  artifact" fix.
- **Proposed home:** DK (a kernel under the oracles/instruments family) + a line in `04-oracles-and-instruments.md`.
- **Portable because:** every decomp builds progress/coverage instruments and runs them for months at 1–99%; the day the
  project finishes is the day the untested endpoint fires, and the same is true of a fresh project at 0%.

### C5 — An annotator that writes into the text it reads must never treat its own output as evidence
- **Evidence:** `phase-ends/logs/Phase33.md:499-503` — "Three instrument defects, found by its own controls/verify before any
  tag was written … (3) after writing, a neighbouring cite's tag read as a `2.8.1` cue — the instrument reading its own
  output — caught by `--verify`."
- **What happened / what it cost:** `gccmap_cites.py` derives each source citation's provenance tag from cues near the cite.
  Once it had written `[2.8.1 pm]` next to one cite, that written tag became a "cue" for the *next* cite, so a second run
  would have drifted the tags. Caught only because the tool shipped a `--verify` that re-derives every written tag from
  scratch and a `--controls` mode over known-true cases; the first two defects (span pairing inside a ±160-char window,
  fenced code blocks inverting the pairing) came from the same controls.
- **Not banked — greps:** `grep -n -i 'reading its own output' $DOCS` → 0;
  `grep -n -i 'its own output as evidence\|own output as input' $DOCS` → 0;
  `grep -n -i 'idempotent.*annotat\|annotator' $DOCS` → 0.
- **Proposed home:** DK (a kernel) — the in-place-annotation corollary to R57 ("an instrument's own write path is part of the
  instrument"): an in-place annotator needs a re-derivation check, not just idempotence.
- **Portable because:** in-place annotation of one's own documents (provenance tags, section ids, cross-refs, cookbook
  indices) is a standard decomp housekeeping tool.

### C6 — Regex-extracted evidence needs a structural marker, or prose becomes data
- **Evidence:** `phase-ends/logs/Phase33.md:503-504` — "Bare ALL-CAPS prose words (`NOT`, `AND`, `DEST`) had also passed as
  evidence: identifiers now need an underscore, as every real gcc macro/function cited has."
- **What happened / what it cost:** the citation tagger's identifier heuristic accepted ordinary emphasised English words as
  gcc identifiers, so prose voted on provenance. The fix was a structural predicate derived from the corpus itself (every
  real cited gcc macro/function contains `_`), not a longer stopword list.
- **Not banked — greps:** `grep -n -i 'ALL-CAPS' $DOCS` → 0 (run as part of the C5 batch);
  `grep -n -i 'idempotent.*annotat\|annotator' $DOCS` → 0; `grep -n -i 'reading its own output' $DOCS` → 0.
- **Proposed home:** accelerator (a line under the instrument-controls material), or folded into C5's kernel.
- **Portable because:** every decomp mines its own prose (cookbooks, logs, decision records) with regexes; the general rule is
  "derive the acceptance predicate from a property the true population provably has".

### C7 — `objdump -dr` interleaves relocation records only for OBJECT files; a linked ELF lists them separately and shifts the address column
- **Evidence:** `phase-ends/logs/Phase33.md:526-529` — "`objdump -dr` interleaves relocation records only for OBJECT files —
  a linked ELF lists them separately (`-r`, section-relative offsets) … and a linked listing puts the address at column 0 (an
  object listing indents it) — the instruction regex is `^\s*`."
- **What happened / what it cost:** two gotchas in building the xsig test fixtures, each of which silently produces an
  *empty or wrong* parse rather than an error: relocation-aware signing over a linked ELF sees no relocations at all, and an
  instruction regex tuned on object listings matches nothing on a linked listing.
- **Not banked — greps:** `grep -n -i 'linked ELF' $DOCS` → 0; `grep -n -i 'relocation records' $DOCS` → 0;
  `grep -n -i 'objdump -dr' $DOCS` → 10 (all about normalised instruction diffing and `masked_diff` on objects, never the
  object-vs-linked difference).
- **Proposed home:** cookbook (the tooling/objdump area) or accelerator.
- **Portable because:** any decomp writing reloc-masked scoring, cross-project signatures, or a differ has to parse both
  object and linked listings, on any binutils target.

### C8 — A derive-then-apply pipeline over a live repository needs a freshness guard, and a stated sequencing law
- **Evidence:** `phase-ends/logs/Phase33.md:285-288` — "One more R43 guard added to `run_filter.py`: it refuses a dictionary
  whose main count/HEAD differ from the clone's (a stale dictionary would drop rows from the public map) … **Sequencing law
  for C4:** the dictionary + ids are rebuilt from the FINAL tree right before the clone (4 s + 3 min) — any commit after that
  invalidates them (the guard enforces it)."
- **What happened / what it cost:** the hash dictionary and the blob-id strip list are derived from the repository, then applied
  to a clone of it; every commit made between derivation and application silently invalidates them, and the failure mode
  (rows missing from the *public* commit map) is invisible at run time. Trial #2 had matched "by construction", i.e. by luck of
  ordering — the guard was added so the property is enforced rather than observed.
- **Not banked — greps:** `grep -n -i 'stale dictionary\|rebuilt from the FINAL tree' $DOCS` → 0;
  `grep -n -i 'invalidates' $DOCS` → 8 (all compiler-pass semantics in the cookbook);
  `grep -n -i 'created EMPTY\|never a fork' $DOCS` → 1 (`11-publishing.md:29`, a different step of the same procedure).
- **Proposed home:** DK (a kernel) or an added step in the publishing chapter's rewrite recipe; it is an R43 instance with a
  named sequencing law.
- **Portable because:** the derive-a-map-then-apply-it-to-a-copy shape recurs far beyond history rewrites (symbol maps, splat
  configs, dedup registries applied to a worktree copy).

### C9 — A content-hash "no ROM bytes" audit collides on zero-length files
- **Evidence:** `phase-ends/logs/Phase33.md:205-207` — "controls: the current tree FAILS with exactly the purge set — 255
  offender rows — a clean subset OK, a renamed EXE copy caught by content; empty-file SHA1 collision with the zero-length
  SC04/SC05 `FILE_029/1.6` payloads found and exempted"
- **What happened / what it cost:** `audit_public.py` flags any tracked file whose SHA1 appears in the extracted-ROM manifest.
  The disc contains zero-length payloads, so the empty-file SHA1 is in the manifest — and every empty tracked file in the
  repository then reads as ROM-derived. Found by running the control, not by reasoning.
- **Not banked — greps:** `grep -n -i 'zero-length\|empty-file\|SHA1 collision' $DOCS` → 0;
  `grep -n -i 'empty blob' $DOCS` → 5 (all the *git* empty-blob strip-list defect, a different mechanism in a different tool).
- **Proposed home:** accelerator, or a line in the publishing chapter's no-ROM-audit description.
- **Portable because:** every project that gates publication on "no tracked file's hash appears in the ROM manifest" inherits
  this collision, since discs and archives routinely contain zero-length entries.

### C10 — `git push --mirror` does not push `refs/stash`
- **Evidence:** `phase-ends/logs/Phase33.md:295-296` — "`git ls-remote archive` == local refs except **`refs/stash`, which
  `--mirror` does not push** (the bundle holds it; Drew may push it as a branch)."
- **What happened / what it cost:** the archive repository was the one snapshot of the pre-rewrite history and was verified
  ref-by-ref against the local repo. The stash — three phase-26 WIP entries — was not in it; only the separately made
  `--all --reflog` bundle held it. Had the bundle not existed, an "identical mirror" check would have passed while losing work.
- **Not banked — greps:** `grep -n -i 'refs/stash' $DOCS` → 0; `grep -n -i 'stash' $DOCS` → 5 (all MIPS register-stashing in
  the cookbook); `grep -n -i 'created EMPTY\|never a fork' $DOCS` → 1 (the neighbouring archive step, silent on this).
- **Proposed home:** accelerator, or a line in the publishing chapter's archive step ("mirror **and** bundle; verify both").
- **Portable because:** it is a property of git, and every project archiving a history before a rewrite does exactly this push.

### C11 — Route a host purge request through the flow that actually exists; the obvious form is a trap
- **Evidence:** `phase-ends/logs/Phase33.md:635-641` — "via the Support portal's **Virtual Agent 'Clear cached views'** flow —
  the route that actually works … The static 'Repositories' form's 'Deletes' sub-option is a trap: it is the
  delete-the-whole-repository flow — never submit it."
- **What happened / what it cost:** the public flip is gated on the host garbage-collecting force-pushed-away objects, which
  only Support can do. The form a reasonable person picks (Repositories → Deletes) would have destroyed the repository. The
  working path is a specific chatbot flow with a specific sequence of answers and a ~500-character reason field, and it is now
  written down in the runbook with the answers.
- **Not banked — greps:** `grep -n -i 'Virtual Agent\|cached views' $DOCS` → 0;
  `grep -n -i 'delete.*whole repository\|delete the repository' $DOCS` → 0;
  `grep -n -i 'Support ticket' $DOCS` → 6 (the ticket is cited as a *cost* in the retrospective and economics chapters, and
  the publishing chapter says "a Support ticket and a daily probe" — none records the route or the trap).
- **Proposed home:** accelerator + the publishing chapter (with an explicit "this is host-specific and dated" caveat).
- **Portable because:** the *shape* transfers to any host — the destructive option and the wanted option live under the same
  menu word; write the working route down the day you find it, because you find it once and need it under time pressure.

### C12 — A host feature can be gated on the very flip it was meant to precede: read the settings page, don't infer
- **Evidence:** `phase-ends/logs/Phase33.md:692-694` — "~~The wiki can be pushed NOW~~ — **WRONG (R14, corrected minutes
  later):** GitHub's settings page reads 'Upgrade or make this repository public to enable Wikis'; on the free plan wikis
  exist only on public repos, so the wiki waits for the flip."
- **What happened / what it cost:** F3 authored 25 wiki pages and a sync script on the assumption they could be published
  during the purge wait; the claim was made and retracted within minutes, and the sync script's message plus the owner's
  checklist item had to be corrected back. Cheap only because it was checked.
- **Not banked — greps:** `grep -n -i 'wikis\? only on public\|enable Wikis\|free plan' $DOCS` → 0;
  `grep -n -i 'Support ticket' $DOCS` → 6 (the wait, not the feature gating); `grep -n -i 'fresh clone\|fresh-clone' $DOCS`
  → 13 (unrelated).
- **Proposed home:** accelerator (one line under the publishing sequencing), or a failure-museum row.
- **Portable because:** the general law — verify a host/service capability against its own settings page before sequencing
  work behind it — applies to badges, pages, discussions, artifact hosting, and any tier-gated feature.

### C13 — A public scratch service's compiler image is NOT your pinned toolchain; rebuild it locally and prove byte-identity before asking for a preset
- **Evidence:** `phase-ends/logs/Phase33.md:645-649` — "the `gcc2.7.2-psx` image is old-gcc **0.13** + maspsx **`86ccd7d8`**
  (not our 0.17 + `874855c5`; SETUP's 'same pinned commit we use' was stale; three rows corrected, R14) … presets: **no create
  button in the UI** … `name`/`platform` immutable, no owner delete (405) → prove before requesting."
- **What happened / what it cost:** the phase plan itself (`:1232-1236`) said presets "are created in-browser by any logged-in
  user (`POST /api/preset/`)" — wrong; the frontend has no create call and maintainers create them from an issue template. And
  the project's own SETUP had asserted the service used our pinned commits, which was false in both components. The response
  was `tools/decompme_replica.sh`: rebuild *their* image locally (tarball sha256-pinned, maspsx at their commit, their `as`
  wrapper verbatim), run their two backend commands, and compare words — BYTE-IDENTICAL on all 26 words of one function, with
  our pipeline as the control and one-component-at-a-time attribution.
- **Not banked — greps:** `grep -n -i 'no create button\|created in-browser\|preset-request\|maintainers create' $DOCS` → 0;
  `grep -n -i 'decomp\.me' $DOCS` → 7 (the preset named as a deliverable, the service's own "do not hook up an LLM" policy,
  a layout probe) ; `grep -n -i 'old-gcc 0\.13\|86ccd7d8' $DOCS` → 1 — `phase-ends/DIGEST.md:141` is the Phase-33 synopsis
  and records the measured FACT plus the local proof ("decomp.me = old-gcc 0.13 + maspsx 86ccd7d8, rebuilt locally, 26/26
  words"). **NEW is the day-one law, not the fact:** nothing records that presets cannot be created from the UI, that
  `name`/`platform` are immutable with no owner delete, or that the project's own SETUP had asserted the service used our
  pins and was wrong — i.e. that the correct move is to rebuild THEIR image and prove byte-identity BEFORE requesting.
- **Proposed home:** DK or accelerator + the publishing chapter — "publishing a preset is a *proof*, not a form".
- **Portable because:** every decomp eventually wants a scratch-service preset, and the service's image drifts from the
  project's pins independently; an unprovable, immutable, undeletable preset is a permanent public error.

### C14 — A miner over your own records finds only what its pattern anticipates: measure the widened pattern's yield
- **Evidence:** `phase-ends/logs/Phase33.md:429-431` — "`tools/mine_hindsight.py` (… the decision-log's `Hindsight` bullets
  AND `### Hindsight` sections — 19 over 79 entries after widening the pattern, the first cut found 11 —, the two 'What we
  believed' sections, 237 deviation rows over 32 PhaseEnds)"
- **What happened / what it cost:** the retrospective's entire input is what this miner returns. The first pattern found 11
  hindsight entries; widening it to the second syntactic form found 19 over the same 79 entries — 42% of the corpus was
  invisible to the first cut, and nothing in the output would have said so.
- **Not banked — greps:** `grep -n -i 'widening the pattern\|first cut found' $DOCS` → 0;
  `grep -n -i 'recall' $DOCS` → 5 (a symbol-join recall floor in the cookbook, and card authoring in the decision log — a
  related idea for a different instrument); `grep -n -i 'mine_hindsight' $DOCS` → 2 (`docs/retrospective.md:8` names the tool
  as the retrospective's input and `phase-ends/DIGEST.md:143` lists it as a Phase-33 deliverable; neither records the
  widened-pattern yield or that the first cut saw 11 of 19).
- **Proposed home:** DK (a kernel) or accelerator — the "assert your denominator" law (R32/R41) applied to *text mining of your
  own records*, which is how the retrospective, the cookbook index and this very pass are produced.
- **Portable because:** the record formats drift over a long project (this one had two hindsight syntaxes and two progress
  formats); any future project mining its own logs inherits the same silent under-recall.

### C15 — A harness's low-memory guard silently kills a long BACKGROUND job — and workers from closed phases survive for days
- **Evidence:** `phase-ends/logs/Phase33.md:508-511` — "the first tools-health run was KILLED by the harness's low-memory guard
  during the report step (a transient spike; 29 GB available afterwards) — and the process table held **8 orphaned
  `tools/permuter/run_masked.py` workers from a closed phase, 49 h old (parent PID 18)**, stopped by PID … the foreground
  re-run passed."
- **What happened / what it cost:** the project's full health check reads as a failure when it is actually a harness kill, and
  the memory pressure that triggers the kill was manufactured by the project's own abandoned workers from a *previous phase*.
  Two independent instrument errors compounding: run long checks in the foreground, and audit the process table across phase
  boundaries.
- **Not banked — greps:** `grep -n -i 'low-memory guard\|memory guard' $DOCS` → 0;
  `grep -n -i 'background.*killed\|killed.*background' $DOCS` → 0; `grep -n -i 'orphan.*worker\|orphaned' $DOCS` → 14 (an
  orphaned dedup reconcile, orphaned per-binary reports — never a live process).
- **Proposed home:** accelerator (an ops/lane-hygiene line) + a failure-museum row (an R40 instance: exonerate the harness).
- **Portable because:** any agent harness that supervises long jobs has a resource guard, and any project that runs unattended
  worker fleets leaks them across phases.

### C16 — A `cd` in one agent shell call persists into the next
- **Evidence:** `phase-ends/logs/Phase33.md:660-661` — "Gotcha, recorded: a `cd` in one Bash call persists into the next — the
  first download landed inside `tools/maspsx/` (moved out; submodule clean)."
- **What happened / what it cost:** a downloaded tarball was written into a git *submodule*, which dirties a pinned dependency
  rather than the project's own tree — the kind of pollution a `git status` in the superproject reports only as "modified
  content". Cleaned by hand; the correction cost a step, not a session.
- **Not banked — greps:** `grep -n -i 'cd in one\|cd persists\|persists into the next' $DOCS` → 0;
  `grep -n -i 'working directory persists' $DOCS` → 0.
- **Proposed home:** accelerator (one line) — minor, but it belongs with the other harness-shell gotchas (R79's `pkill`).
- **Portable because:** it is a property of agent harnesses that keep a persistent shell; the durable form is "absolute paths
  in every tool invocation, and never rely on the working directory across calls".

## ALREADY-BANKED (one line each)
- A linked worktree's HEAD is a ref — audit `git worktree list` before any gc/purge (12 stale worktrees pinned 3,729 commits) — lives at `decomp-architect/corpus/decomp-kernels.md:692` (DK-54), `phase-ends/DIGEST.md:291` (R77), `docs/how-to-ai-decomp/11-publishing.md:116`, `docs/how-to-ai-decomp/12-failure-museum.md:37`, `decomp-architect/templates/registry-E.decomp.md:115` (G15)
- A probe or guard must never write into the repository it guards (the purge probe re-imported 5.97 GiB) — lives at `phase-ends/DIGEST.md:298` (R81), `decomp-architect/templates/registry-E.decomp.md:119` (G16), `docs/how-to-ai-decomp/04-oracles-and-instruments.md:74`
- A rewritten history is not private until the objects are gone from the HOST; the Activity view publishes every pre-force-push tip — lives at `phase-ends/DIGEST.md:300` (R82), `decomp-architect/corpus/decomp-kernels.md:708` (DK-56), `decomp-architect/templates/registry-E.decomp.md:125`
- Outward text is rewritten the way a developer writes, never a model draft with the tells removed; read the target's AI policy first — lives at `phase-ends/DIGEST.md:303` (R83), `docs/decision-log.md:3500`, `docs/how-to-ai-decomp/12-failure-museum.md:45`, `decomp-architect/corpus/decomp-kernels.md:727`, `decomp-architect/templates/registry-E.decomp.md:421`
- `--strip-blobs-with-ids` with the shared EMPTY blob's id silently undid every "file emptied" change in history — lives at `docs/retrospective.md:71`, `docs/how-to-ai-decomp/11-publishing.md:32`, `docs/how-to-ai-decomp/12-failure-museum.md:36`, `decomp-architect/corpus/decomp-kernels.md:916`
- A byte-identical commit keeps its hash across a rewrite and trips old-hash assertions — lives at `docs/retrospective.md:35`, `docs/how-to-ai-decomp/12-failure-museum.md:36`
- Rehearse every irreversible repository operation on a scratch copy and prove it pair by pair with positive assertions — lives at `docs/how-to-ai-decomp/11-publishing.md:114`
- A metric's denominator comes from the artifact you control (the build), not the analysis tool — Ghidra left 3,628 words owned by no function — lives at `docs/decision-log.md:3450-3461`
- When two instruments disagree by a systematic offset, the one corrected instance is usually a class — lives at `docs/decision-log.md:3459-3461`
- No ROM-derived bytes in ANY published artifact — test fixtures, JSON, badges, reports included — lives at `docs/how-to-ai-decomp/11-publishing.md:112`, `phase-ends/DIGEST.md:284`
- Published numbers are generated, never typed (R51 applied to documents; the README's numbers were Phase-19 stale) — lives at `docs/how-to-ai-decomp/11-publishing.md:113`
- A link checker that widens its document set must classify a missing *promised* page as PENDING, never BROKEN — lives at `docs/how-to-ai-decomp/11-publishing.md:116`, `:100-102`
- Build the test fixture from your own C at two link addresses so a ROM-facing tool ships publishable tests — lives at `phase-ends/DIGEST.md:284`, `docs/how-to-ai-decomp/11-publishing.md:106`
- The archive repository is created EMPTY — never a fork or import, which share the host's object store — lives at `docs/how-to-ai-decomp/11-publishing.md:29`
- Other clones reset to the new history and never `git pull` (an 8,000-commit merge of two lineages) — lives at `docs/how-to-ai-decomp/11-publishing.md:46`
- Every third-party licence read from its own source of truth; two upstreams publish none and the table says so; never the phrase "clean-room" — lives at `docs/how-to-ai-decomp/11-publishing.md:90-94`
- An upstream interactive tool's author does not want an unattended tool's objective function — ask what the maintainer's workflow needs before offering — lives at `docs/decision-log.md:3504`, `:3496`
- `pkill -f` never with a literal the calling shell's own command line contains (exit 144) — lives at `phase-ends/DIGEST.md:295` (R79), `docs/accelerators.md:197`, `docs/wave-playbook.md:730`
- To prove an RE database regenerable from text, subtract a baseline exported from the freshly rebuilt program (analysis-origin rows) — lives at `docs/how-to-ai-decomp/11-publishing.md:83-85`
- A fresh-clone reproducibility proof only proves independence from what is actually absent — B3's clone still contained the vendor SDK, so the no-SDK path needed its own control — lives at `docs/decision-log.md:3475`, and the corrected claim at `docs/how-to-ai-decomp/11-publishing.md:69`
- A verification harness that writes its evidence logs into the tree it checks fails its own cleanliness step (`00_tree.log`; the tracked A5 logs) — covered by the same class at `phase-ends/DIGEST.md:298` (R81) and `:242` (R57 — an instrument's own write path is part of the instrument)
