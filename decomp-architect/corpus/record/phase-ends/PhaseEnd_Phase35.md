# PhaseEnd — Phase 35: Gen3 opens — the dedup phase, "one source per unique function"
**Date:** 2026-09-08 · **Project Version:** 2.1.0 · **Phase Status:** Complete (milestone: see §Milestone — every item with its literal output; gate 2 = Drew's close commit) · **Generation:** Gen3 (the first phase; Drew's Gen3 order: dedup → pins → structs → names, one phase each, planned one at a time)

> Chartered at gate 1 (S94, 2026-09-08, plan mode, Max) from `docs/gen3-handoff.md` + `docs/gen3-standards.md`, on evidence read from
> sotn-decomp's tree that reversed the 2026-09-02 "leave the dedup backlog" decision. Ran **three sessions (S94–S96, all 2026-09-08)** and
> **48 commits** (`48170fd7f..HEAD`, plus this close). The granular trail — every task's verify lines, the S94 death and the S95
> recovery, every tool defect with its cause — is at **`phase-ends/logs/Phase35.md`** (R19, on demand). Owner decisions (Drew): gate 1's
> four (twins → one source directory; cross-address classes censused and deferred; macro-era tools frozen with a loud refusal; R96–R99
> ratified); no "trivial" exception; the tooling must know there is one source per unique function (→ the S1 gate); the recovery session's
> scope ("capture only"); the effort levels per step (Max for two decisions delegated to Claude, high/xHigh otherwise); T9 run in the same
> session at xHigh.

## Build Log

**The phase in one line:** every shared function body became one plain-C header included at each member's site (sotn's shape), the
five identical-payload overlay twins build from one source directory, the 4,755 already-matched duplicate copies of 1,099 same-address
classes were shared down to 160 copies in 51 ledgered classes, 38 functions whose bytes vary per overlay share one text through a new
registry tier, the invariant "one source per unique function" is a `tools-health` gate with a second, disagreeing oracle, the macro-era
tools are frozen or retired behind a guard, the published numbers were corrected where the old counting was blind — and every step was
proven by the 218 hashes from a clean rebuild.

**Files created/changed and complete — do not recreate** (category summaries; the per-commit list is `git log 48170fd7f..HEAD` and the
archived log):

- **The shape (T3, T4, T5, T5b).** `src/shared/engine_prelude.h` (what every overlay/module TU includes at line 2), `src/shared/{ov,main,
  slot_800CAE08,slot_801E25E8,slot_801EF468}/func_<VRAM>[__<h8>|__t<h8>].h` — **3,175 headers**, one per shared body (2,215 converted from
  the macro header at T4, 914 + 1 + 38 written by the share tool); `src/shared/engine_core.h`, `ov_setters.h`, `clearTbl40.h` deleted;
  the whale `func_80144B9C.h` moved under `ov/`; **3,173 registry groups** in `config/dedup.us.yaml` (2,220 at the open; 38 of them
  `tier: h_text` in the verbose member form with per-member `h_exact`); `config/dedup_exceptions.tsv` (the S1 ledger: 51 rows, each with
  the compiler's diagnostic and a reason code); `config/overlays.mk` `<twin>_TWIN_OF/_SRC_DIR` for SC01_006, SC03_119, SC02_003, SC04_019,
  SC03_015 (their `src/` directories deleted, 166 files; the twins' yamls = the primaries' carves with `create_c_files: False`, their
  `JTBL_PADS` lines regenerated); the Makefile's twin block.
- **The tools (T1, T2, T4, T5, T5b, T6, T7).** `tools/share_census.py` (the S1 census + gate: every sig instance resolves to one source form;
  verdicts A/B/C/D/M, flags E/F/TWIN/PINS/ALIAS; `--selftest` fixture; `--check --strict-macros --strict-text`; `text_classes`; the second,
  sig-blind oracle keyed by (text, address)), `tools/macro_to_header.py` (the T4 converter, kept as `share_body`'s library), **`tools/
  share_body.py`** (the permanent share tool: `--plan / --apply --bucket extend|new|text / --reexemplar / --repair-registry`, the
  per-binary gate with object comparison and a snapshot-based bisect, the ledger, `--batches 1`), `tools/share_body_cycle.sh` (the
  unattended batch cycle: batch → exit code → phase-log entry → commit → periodic clean fleet run), `tools/frozen.py` (the one refusal
  14 FROZEN tools print from `main()`), `tool_census.py` (status FROZEN; the `ast` macro-form guard with `--guard-root` for the negative
  control), `dedup_integrate.py` (C2c/C2d; the `h_text` tier with C1 per member), `progress.py` (the include form as a definition, the
  source-dir oracle, the empty-shared fold, `unique_function_bodies`, `duplicate_source_copies/_classes`, `text_tier_*`,
  `deferred_same_address_*`, a dated `corrections` list, the README sentence), `corpus.py` (`src_dir/twin_of`, the one source-dir oracle),
  16 health-chain tools taught the include + twin forms (T2), 12 tools' dead macro branches dropped (T6); `tools/sunset/`: `dedup_propagate`,
  `dedup_extend` (their library surface moved verbatim into `share_body`), `macro_draft`, `test_reconcile_ledger`; the Makefile's
  `tools-health` gained `share_census --selftest` and the strict check before `report`.
- **The record (T8).** `docs/wiki/The-dedup-engine.md` rewritten for the shared-source model; `Repository-layout.md`,
  `Where-the-project-goes-next.md`, `Verification-and-progress.md`, how-to ch.10, README prose and the generated block (with the
  "One source per unique function" sentence), `docs/gen3-standards.md` (§4 row struck, the DoD's "0 macro bodies" met), `docs/gen3-
  handoff.md` (dated snapshots), cookbook **§453** + a retirement banner on §14, `docs/decision-log.md` P35 (R31), `docs/accelerators.md`
  P35 (five), DIGEST §0/§2/§3/§4, `docs/SETUP.md` P35 sections (T1, T3–T5, T6, T7/T5b, the context guard), `docs/tool-index.md` and the
  kit corpus regenerated, the memory `dedup-backlog-leave-it` rewritten as REVERSED.
- **Evidence (`.run/P35/`, allowlisted text):** `baseline/` (every R22 and tools-health log, the kit-corpus logs), `census/` (the census
  json/txt, `check_t5.txt`), `share/` (every batch record `batch_<label>.json`, every run log, the 146 per-binary gate logs, the registry
  repair record, the old header of the re-exemplar), `convert/` (T4's batch scripts, ledger and apply logs), `probe/` (T0's object A/B).
- **Outside the repository:** `~/.claude/statusline.sh` writes the context percentage; `~/.claude/ctx_guard.sh` (a user-settings
  `PostToolUse` hook) injects "90% context. decide on the best place to checkpoint for a fresh session" once per session — built after
  S94 died at 91 % without a checkpoint; it fired in S96 exactly at the right moment.

**Tools/packages installed:** none (no apt/pip). Agents: three at gate 1 (two Explore, one Plan; ~680k tokens); none during execution —
every task was the coordinator's own work and deterministic gates.

**Verification results (literal, at close — S96, HEAD `c1a901373` + this close):**
- T9 R22 from clean: `extract-all: 217 extracted, 0 failed of 217 (+ main, serial)` · **`check-all: 218 passed, 0 failed of 218`** · `wall=87.62 s` · exit 0` (`.run/P35/baseline/r22_t9.log`).
- T9 `make tools-health` (foreground): `tools-health: OK — sigs fresh; corpus(+resident) + cdecl + binaries + report(lint+dedup) + cookbook-index all green.` (run 2, 431 s, exit 0; run 1 was red only at the kit corpus, which had not yet copied this file and the DIGEST edit — regenerated, re-run) (`.run/P35/baseline/tools_health_t9.log`) carrying `S1: one source per unique function — 10,180 classes, 10,180 satisfied (3,507 twin-covered, 51 excepted, 3,801 deferred cross-address), 0 VIOLATION(S) — OK`, `dedup-check: 3173 validated, 0 failed | C1 coverage 262573/262573 members signed`,
  `macro-form guard: 0 LIVE tools reference the retired form (217 scanned, 14 frozen, 6 whitelisted detectors, 38 retired)`.
- `git grep -c '^#define DEFINE_func_' -- src` → empty; `tools/macro_to_header.py --verify` → `OK — 0 macro sites, no macro header, the
  prelude present`; the census `macro sites 0` (two block-comment lines in prose still mention the token — comments are the record);
  `src/shared/engine_core.h` absent.
- `tools/share_census.py --selftest` → `7/7 verdicts correct`; the strict check's second oracle: `0 same-address definition texts
  duplicated across TUs`, `381 … inside the deferred cross-address classes (1,668 sites)`.
- `tools/progress.py --json --readme --check` → fresh; `timeline --check: fresh (74 rows)`; `doc_links` strict `0 pending, 0 broken`;
  `wiki_render --selftest: 12 cases, 0 failed; 32 pages, 0 unlisted`; `cookbook-index OK (1170 sections)`; `kit_coverage: OK`;
  `tool_census --check: OK` (the guard: 217 scanned, 14 frozen, 6 whitelisted detectors, 38 retired).
- The negative controls on record (R39): the guard against a worktree of the pre-T4 tree flags exactly the 15 tools with macro-form code
  (`--guard-root`); one member's include reverted in place → `S1 … 1 VIOLATION(S) — FAIL` naming the class, C2d naming the member, restored → OK.

**Milestone achieved (gate 2 — Drew's close commit is the confirmation; each item with its literal output):**
1. `git grep -c '^#define DEFINE_func_' -- src` empty; no `DEFINE_func_X()` site (`macro_to_header --verify` 0; the census 0);
   `src/shared/engine_core.h` absent; every registered body a plain-C header under `src/shared/<space>/` (`dedup-check` C2c, 3,173 groups).
2. `tools/share_census.py --check --strict-macros --strict-text` exit 0: `S1: one source per unique function — 10,180 classes, 10,180
   satisfied (3,507 twin-covered, 51 excepted, 3,801 deferred cross-address), 0 VIOLATION(S) — OK` — same-vram duplicate copies 160, each
   in a ledgered class with its reason; the five twins built from one source directory each (`audit-binaries` CHECK 3b); the cross-vram
   classes published as a deferred count (3,801; plus the 381 tiny-body texts / 1,668 copies inside them).
3. `make tools-health` OK with S1 strict and the macro-form guard; every consumer updated (16 + 12), frozen (14) or retired (4) per its
   dictionary row.
4. `make clean && make extract-all && make check-all` → `check-all: 218 passed, 0 failed of 218` (R22, T9 and after every batch).
5. README/wiki/kit regenerated (R75), decision log (R31), SETUP rows (R21), this PhaseEnd + the DIGEST; v2.1.0.

**Next:** **Phase 36 — pins off** (Drew's Gen3 order). Open a fresh session in **plan mode, Max** (Tier 1) from `docs/gen3-handoff.md`
§5–§7 and `docs/gen3-standards.md`: the 44,243 `register … __asm__` pins (most come off byte-identical once the source shape is right —
Phase 32's finding), family-batched, byte-gated per binary, R22 per batch; the S1 gate stays in the chain (a pin removed inside a shared
header reaches every member — one edit, one gate). Inherited by name: the 51 ledgered declaration conflicts (the types phase), the 3,801
cross-address classes and the 381 tiny-body texts (the names phase's parameterized form), the kit split, xsig v2.

## Roadmap delta (what Phase 35 changed about the road ahead)

- **The Gen3 charter's first item is met and measured:** "shared engine functions live as C, not as macros" — 0 macro bodies; the
  charter's "5,147" counted define lines (3,516 distinct macros; R14/R41 correction published in the log and the wiki).
- **A new registry tier exists (`h_text`)** for the shape the byte tier cannot hold: identical C whose bytes vary per binary through
  the translation unit's declaration environment. The types phase must treat those 38 headers as compiling per unit by design.
- **The names phase inherits a precise list:** 3,801 cross-address classes (E flag), 381 same-address tiny-body texts inside them, and
  the parameterized `SHARED_FN` form as the intended shape (one worked example, `clearTbl40`).
- **The types phase inherits the ledger:** 50 declaration conflicts in the late-onboarded overlays (`config/dedup_exceptions.tsv`,
  each with its diagnostic) and one byte-variant body — exactly where a canonical declaration layer (R95) pays.
- **Scale, honestly (R41):** the plan priced the phase at 7–8 sessions; it took three (one of them a recovery), because the tooling was
  built to gate itself and the batches ran unattended. The cost that was real: one dead session's 35 minutes rebuilt from its transcript,
  four tool defects found from their artifacts, and nine red health-chain runs across T6–T7, every one an instrument finding.

## Deviations

| Item | Plan (gate-1 plan) | Actual | Reason |
|---|---|---|---|
| Sessions | 7–8 | 3 (S94–S96) + this close | the gates were the tool's; batches ran unattended (`share_body_cycle.sh`) |
| S94 | a checkpoint at every pause | died at 91 % context waiting on a background run, no checkpoint for T5; S95 rebuilt the state from the transcript with no runs (Drew's scope) | two bank commits carried no log line; rule candidate (b); the context guard built |
| `share_body` | designed at T5 | four defects found from S94's artifacts and fixed at S96: the cause extractor (no "error" token in gcc 2.7.2), `git checkout` as restore, a twin's duplicate edit, wholesale registry extension | each caught by a gate or a known-true control; cookbook §453 |
| Bucket 0's residue | ledgered with a message class | 48 late-overlay declaration conflicts ledgered TU-CONFLICT for the types phase; `E_func_80168B70` re-exemplared from the majority text (Claude's delegated decision at Max) | the header carried a 7-overlay minority spelling; the cast form compiles under both environments (141/141) |
| The second oracle | "a second, disagreeing oracle" | it disagreed: 38 same-address texts / 2,030 copies byte-variant per binary → **T5b added** (the `h_text` tier; Claude's delegated decision at Max); 381 tiny-body texts inside the deferred classes stay deferred | no later phase would remove the copies; one header per address for the empties would be undone by the names phase's form |
| T6's counts | freeze 7, retire 3 | freeze **14**, retire **4**; the guard's census measured 30 hits, not 22; `family_cousins` stays LIVE (`make atlas` runs it) with its dead branch dropped | the plan's counts came from a partial census |
| `progress.py` | "the +219 correction" | +459 (SC03_015's 219 + SC03_118's 3 + the never-extended members of five groups) and REAL −10,211 → EMPTY (the fold); both dated in `progress.json` `corrections` | the include form made invisible sites visible; the macro-era fold had counted empty shared bodies as REAL |
| T9 | Max, fresh session | run in S96 at xHigh (Drew) | owner's call; the checkpoint carried the brief |

## What we believed, what failed, and what we would do sooner (for the retrospective; detail in `docs/decision-log.md` P35)

- **Believed (2026-09-02):** sotn writes duplicate functions explicitly, so ~12,000 duplicate copies are the normal end state. **False:**
  read from its tree, sotn shares stage code once and instantiates it by an include. **Sooner:** read the target project's tree, never a
  memory of it, before setting a policy on its precedent.
- **Believed:** refreshing the checkpoint at every task close was enough. **S94 refreshed it five times and still died with 35 minutes
  of state only in its transcript** — two bank commits inside a task carried no log line, and a background wait consumed the rest.
  **Sooner:** every commit that advances a task carries its log line and the headline; past ~85 % context, checkpoint before any long wait.
- **Believed:** a green per-binary gate meant the tool's edits were what it reported. **Its restore was `git checkout`,** which wiped the
  previous batch's uncommitted shares and returned green; its cause lines read "Error 33" for 254 of 303 rejections. **Sooner:** a tool's
  restore path is part of the tool (R57); read a compiler's diagnostics by their form.
- **Believed:** the byte join sees every duplicate. **The text oracle found 38 functions in 2,030 copies it could never class.** **Sooner:**
  build the disagreeing oracle before the batch runs, and measure the disagreement before believing either side (R34).
- **Cost:** no model tokens beyond the coordinator and gate 1's three agents; the phase's expense was wall-clock in gates (≈2.5 h of
  `make check` and fleet runs) and the recovery (≈1 h reading a 6 MB transcript).

## Commit Message
``
(Phase 35 landed as 48 commits 48170fd7f..c1a901373, 2026-09-08 (S94–S96). This close = the archived log + this PhaseEnd + the DIGEST
update + the kit's record copies, Drew's milestone-close commit.)

chore(phase-35): CLOSE — Gen3's dedup phase: one source per unique function (3,175 shared headers, 3,173 registry groups incl. the
h_text tier, the macro header gone, the five twins from one directory, S1 a tools-health gate with a second oracle, 14 macro-era tools
frozen and 4 retired behind a guard, the published counts corrected) — v2.1.0

- PhaseEnd_Phase35.md written; CURRENT_PHASE.md archived to phase-ends/logs/Phase35.md (R19); DIGEST §0/§2 appended (step 3b)
- T0–T8 + T5b across S94–S96 (S94 died at 91 % without a checkpoint; S95 recovered it from the transcript; S96 finished)
- close: R22 clean fleet 218/218; tools-health OK (S1 10,180/10,180, 0 violations; dedup-check 3173/0; the guard 0)
- rules: R96–R99 ratified at gate 1; candidates (a)–(g) proposed for Phase 36 gate 1
- v2.0.0 -> v2.1.0
``

## Rules Added This Phase

**Ratified at gate 1 (2026-09-08):** **R96–R99** (the PhaseEnd_Phase34 candidates (a)–(d)); full text in `phase-ends/DIGEST.md` §3.

**Candidates recorded in the log, for Drew to accept, modify or reject at Phase 36 gate 1 (P10):**

| Rule | Reason |
|---|---|
| **(a) A shared body has exactly one source; a duplicate copy is a defect the health chain asserts, and its count is published with its rule.** | The phase's invariant (S1), a `tools-health` gate; 1,099 classes / 4,755 copies → 51 / 160, every remainder ledgered with its diagnostic. |
| **(b) Every commit that advances a task — an intra-task bank included — carries its log line and the 🛑 headline; a checkpoint older than HEAD is a dead session's checkpoint.** | S94 refreshed the block at every task close, made two T5 bank commits with no log line, then died at 91 % context; S95 rebuilt 35 minutes of state from the transcript. |
| **(c) A tool that restores files restores from its own snapshot, never `git checkout` on a tree it did not commit.** | `share_body`'s first bisect wiped the previous batch's uncommitted shares (~50 sites) and returned green. |
| **(d) A failure-cause extractor is negative-controlled against the compiler's real message forms, not against the word "error".** | gcc 2.7.2 prints errors without it and exits 33; 254 of 303 rejection lines read "Error 33". |
| **(e) Build the disagreeing oracle before the batch runs, and measure its disagreement before believing either side (R34 operated).** | The text oracle's 4,312 hits decomposed into twin false positives, the gate-1 deferral, and 38 genuine byte-variant functions — three different actions. |
| **(f) A registry lists a member only after the gate has spoken for it; a listed member whose site does not share is a defect the check names.** | The first pass extended 788 members wholesale; 317 were private after the run (C2d exists now). |
| **(g) A policy taken on a remembered precedent is a belief — read the target project's tree.** | The 2026-09-02 deferral rested on one parenthetical about a cross-jump idiom. |

## PhaseEnd Changelog
**v2.0.0 → v2.1.0 — Phase 35 complete (Gen3's first phase).** Every shared function body in the fleet is one plain-C header included at
each member's site, sotn's shape, verified from its tree; the 8.8 MB macro header and its 5,147 define lines are gone; the five overlay
twins build from one source directory each; the same-address duplicate backlog fell from 1,099 classes and 4,755 private copies to 51
ledgered classes and 160 copies, each with the compiler's own reason; 38 functions whose bytes vary per overlay share one text through a
new registry tier; the invariant "one source per unique function" is asserted on every health-chain run by a census with a self-test and
a second, sig-blind oracle, and by four registry checks; fourteen macro-era tools are frozen and four retired behind a guard that scans
every live tool; the published numbers were corrected where the macro-era counting had been blind, dated and explained. Every batch was
proven by the 218 hashes from a clean rebuild, which now takes 84–90 seconds instead of 157. R96–R99 ratified; seven candidates proposed.

## Plain-English Recap
This phase made the code say each thing once. Before it, when the same function appeared in many of the game's 141 level files, our source
held it as a macro in one enormous header, or as a private copy pasted into each level, thousands of times over. Now every shared function
is one small ordinary C file, included wherever it is used, exactly the way the best-known PlayStation decompilation does it, and a check that
runs with every health check proves that no function has two sources. Along the way the tool that does the sharing was caught making four
kinds of mistake by its own gates and fixed; one session ran out of memory in the middle and the next rebuilt its state from the transcript;
a second, independent check found 38 functions the first could never have seen, and they got their own way of being shared. Fifty-one
functions could not be shared yet because their surrounding declarations disagree between level files, and they are listed with the
compiler's own reason for the next phase to settle. The numbers on the public page were corrected where the old counting had been blind.
All 218 game files still rebuild byte for byte, and faster than before.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase35.md` (R19, via `git mv`); `phase-ends/DIGEST.md` §0/§2 appended
(step 3b); the kit's record corpus regenerated (`make kit-corpus`) — **all left uncommitted for Drew's milestone-close commit** (R6 gate-2
sign-off; the message is above). The Phase-35 work is committed across the sessions (`48170fd7f..c1a901373`; nothing pushed). The headless
Ghidra MCP was stopped via the sentinel (R23); nothing under `ghidra/` is tracked. **Drew, from the repository root:**

``
git add -A phase-ends decomp-architect docs .run/P35/baseline .run/P35/census
git commit -m "chore(phase-35): CLOSE — Gen3's dedup phase: one source per unique function (3,175 shared headers, 3,173 registry groups incl. the h_text tier, the macro header gone, the five twins from one directory, S1 a tools-health gate with a second oracle, 14 macro-era tools frozen and 4 retired behind a guard, the published counts corrected) — v2.1.0"
git tag -a v2.1.0 -m "v2.1.0 — Phase 35: one source per unique function; 218 binaries byte-identical"
git push origin main --tags
``

Gen3 continues — do **NOT** start Phase 36 here. Start a **fresh session** (effort **Max**, **plan mode**) for **Phase 36 — pins off**,
planning from `docs/gen3-handoff.md` and `docs/gen3-standards.md`. Keep this file forever.
