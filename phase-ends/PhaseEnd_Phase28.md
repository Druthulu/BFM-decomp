# PhaseEnd — Phase 28: The Endgame Engine → the instrument-repair phase (every "wall" was our tooling)
**Date:** 2026-07-16 · **Project Version:** 1.27.0 · **Phase Status:** Complete (milestone confirmed by Drew, gate 2) · **Generation:** Gen2 (20th phase of the arc; Phase 14 public-flip deferred to Gen3+)

> Gen2 phase 20 (8→…→27→**28**). Second phase off `docs/roadmap-to-100.md` (§3 P28). Ran across **one long session + a resume after a terminal crash**. The granular per-task crash-recovery trail (every probe, the wave verdicts, the two self-inflicted defects and their repair, the classified failure taxonomies) is preserved on-demand at **`phase-ends/logs/Phase28.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism). This file is the synthesis. Owner decisions (Drew): re-scope on the Phase-Start finding; Fable5 = conditional slot (unused); the 39 type-1 modules = deferred/documented; expand T7 to the citizenship gate + fix the blind disc sweep; add R36; continue T6→T7→T3b to completion; close at Max.

## Build Log

**Files created/changed and complete — do not recreate** (the durable Phase-28 output; the archived log has the exhaustive per-commit list):

*New tooling (committed):*
- **`tools/dedup_extend.py`** — the missing mode: EXTEND an existing macro-backed dedup group to a newly-onboarded binary (`dedup_propagate` only authors macros from *inline defs*; the ~1,600 shared bodies are already `DEFINE_func_*` macros). Owns only the set computation + a **surgical text** registry edit (never `yaml.safe_dump` — see Deviations); the splice + gate are `harvest_verify` verbatim. Carries the §53 jr-guard (with an R14 note on what it is *not*).
- **`tools/audit_binaries.py`** + **`make audit-binaries`** — the **R36 citizenship gate** (R32 enforcement): every onboarded binary (derived from `config/splat.*.yaml`, R33) is asserted present in `dup_report.BINARIES`, has a sig, and (overlays) includes `../shared/engine_core.h`. Negative-control-proven to catch the exact SC07 bug; wired into `tools-health`.

*Fixed tools (the phase's real substance — each fix CHANGED an answer the old tool gave):*
- `tools/family_remap.py` — `img_path` **derives** the payload from the splat config's `target_path` (R33) and **raises** on absence (R32); was a hardcoded `0.4.dec` that returned silent `None` for the 4 SC07 overlays → phantom `LEN`. Un-hid a 230,612-ins pool.
- `tools/progress.py` — `#if 0`-blindness (a dead body counted as REAL *and* stub) + the `matchable = len()`-sum (a fn in two buckets counted twice) → both fixed; added the OVER-coverage assertion (R32, both directions). Resident 123/146 → 122/145.
- `tools/match_one.py` — `--work` defaulted to a **shared** scratch dir while the docstring promised isolation; now a private `<fn>.<pid>` dir. Found by an agent mid-wave reading another agent's function out of its own `t.c`.
- `tools/harvest_verify.py` — `--chunk 1` no longer double-builds every failing draft (~26% fewer builds on the gate's hot path).
- `tools/disc_code_sweep.py` — was **structurally blind to compressed code** (decoded only raw bytes → the type-4 row was vacuous for 138 known binaries); now decodes both the raw and the LZSS-decompressed layer. Could not have found a hidden type-4 overlay before; can now.
- `tools/worklist.py` — `--assert-partition` read `source` where the manifest key is `source_overlay` → the R32 assertion silently rode a hardcoded default; now reads the right key and fails loud if absent.
- `tools/grinder.py` — the poisoned 22-entry blacklist purged (8 had matched anyway; built from a gate that no longer exists); carries the R35 rule that a blacklist entry expires when its gate changes.

*Config / source (the harvest — fleet 67.0% → 68.9% instr):*
- The **4 SC07 overlays wired in** (`src/ov_SC07_{006,007,010,011}/*.c` + `config/dedup.us.yaml`): **6,174 h_exact members banked** (95.6%), C1 coverage 227,211 → 233,385, groups 134 → 138 binaries.
- **B2 family** (`func_8017BEBC`, 952 ins): **102/115 banked** ×134-class via the jtbl carve path (`src/ov_*/*_jr_8017BEBC.c` + `config/overlays.mk`).
- **Resident** (`src/resident/resident.c`): **21 → 14 stubs** (7 banked via the Ultracode wave); `.run/resident_wave_verdicts.json` preserved (R20).
- **T3b** + **T3-A giants**: 9 + 4 legacy/giant banks.

*Docs / knowledge base (R16/R30/R31):*
- `docs/matching-cookbook.md` **§53** — sweep a family with the tool its exemplar needed (the carve law + the `--raw` rule + the `symbol_map`-jtbl trap + the "before a 0% retires a lever" test).
- `docs/calibration.md` — the "structural families ≈0%" table **rewritten** (the ≈0% row marked an artifact); the addressable pool tabulated; the **legacy h_seq swing number** recorded (~3% as-tooled, classified, ceiling-unknown).
- `docs/decision-log.md` (R31) — the B2 refutation; the T3b swing-number measurement + the named P29 disambiguating probe.
- `docs/resident-dossier.md` — **new**: the 14 remaining resident stubs, classed (5 PLUMBING / 4 DIFF / 5 jtbl-deferred) with each agent's byte-grounded residual analysis.
- `docs/second-oracle.md` (context), `docs/SETUP.md` (implicit via tool inventory), `docs/disc-completeness.md` (the fixed-sweep confirmation).
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase28.md`** (R19). `phase-ends/PhaseEnd_Phase28.md` — this file.

**Local artifacts (gitignored / regenerable):** `.run/family_hseq.json` (regenerated 138-overlay), `.run/drafts-t5/*`, `.run/t5_verdicts.json`, `.run/t3b_*`, `.run/t7_*`, `build/`, `expected/`, `asm/`, `assets/`. The resident Ghidra-C prefetch (`.run/ghidra_c/func_800D*.c`) is script-reproducible.

**Tools/packages installed:** None — the whole phase used the existing toolchain + venv. Fable5/Opus agents via the Agent tool; one Ultracode wave (`worker_wave`-style) via the Workflow tool. No Ghidra DB change (R23 no-op — the resident prefetch was read-only headless decompile; the `db.*.gbf` churn is restart-noise, not staged).

**Verification results (literal) — the milestone proof:**
- **`make clean && make extract-all && make check-all` → 140 passed, 0 failed of 140** BYTE-IDENTICAL from a genuinely-clean tree (R22), reproduced after every banked batch.
- **`make tools-health` → OK (exit 0):** corpus(+resident) **0 PHANTOM + 0 TRUNCATED**; **`audit-binaries`: 140 onboarded, every one a full citizen**; `audit-cdecl` green; **dedup-check 1840 validated / 0 failed, C1 coverage 233,385/233,385**; report(lint+dedup) green. All fail-closed.
- **`make report`:** FLEET **instr-weighted 67.0% → 68.9%** (9,017,678 / 13,081,451) · **distinct-code 47.8% → 49.5%** (2,757,556 / 5,574,674) · **fn-count 82.16% → 83.94%** · **0 NON_MATCHING** in any default build (G4). **Velocity: +1.9pp instr this phase.**
- **The disc is complete** (fixed `disc_code_sweep`, coverage-asserted 1189/1189): 138 type-4 overlays all onboarded, 0 further hidden type-4; the 39 type-1 modules remain pending load-address RE (documented, deferred).
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`.run/`(allowlisted)/`phase-ends/` tracked; the `db.*.gbf` churn is R23 restart-noise (not staged).

**Milestone achieved (confirmed by Drew, gate 2):** Phase 28 rebuilt the endgame plan on **measured reality** and, in doing so, banked a large harvest almost entirely by **fixing instruments rather than out-muscling the compiler**. The swing number was **measured and classified** (T3-A: the SC07 pool = h_exact, 95.6%; T3b: the legacy h_seq class = ~3% as-tooled, ceiling-unknown, 274 DIFF / 37 PLUMBING); the **resident was resolved** (90.34% + an honest classed dossier); the fleet rose **67.0% → 68.9% instr** at 140/140 byte-identical / 0 NON_MATCHING; and the **R36 citizenship gate** now enforces that a newly-onboarded binary cannot hide from the tools again. The phase's decisive through-line: **roadmap item B2 LIVES** (the "structural families ≈0%" doctrine that reshaped two phases of strategy had *no surviving post-fix evidence* — its 0/8 was a missing carve), and **every "compiler wall" probed this phase resolved to our own tooling.**

**Next:** **Phase 29 — The Family Campaign (roadmap §3 P29)**, opening with the **T3b disambiguating probe** (diff one PURE DIFF member's staged bytes region-by-region: reloc-position mismatch ⇒ fixable remap and the legacy h_seq ceiling is far above 3%; regalloc-away-from-relocs ⇒ a genuine TU wall) **before** scaling any "(cores)×(reach)" arithmetic on 3%. Carried tools: the burn-down velocity tracker (T7c), `diff_regions.py`, the grinder family-warm-start, and the same-binary shard farm (all deferred, none lost). Fresh session, **plan mode, Max** (Tier-1 Phase-Start).

## Deviations

| Item | Plan (roadmap P28) | Actual | Reason |
|---|---|---|---|
| **The whole phase** | build `member_adapt.py` + the delta engine around the swing number | **RE-SCOPED at plan time** — the swing number's evidence was untrustworthy (R35); the phase became instrument-repair + honest measurement | Phase-Start verification found the ≈0% doctrine rested on a broken-tool probe (B2's 0/8 was a missing carve); building on it would have been building on sand |
| `member_adapt.py` | THE deliverable | **NOT built** — the number said build nothing like it | T3-A: the SC07 pool is h_exact + unwired (95.6% via `dedup_extend`, the *right* tool), not the h_seq drift-adaptation `member_adapt` targets; the STRUCT/register-drift class it was scoped for is 1.8% of the population |
| The parallel gate farm | build it (throughput bottleneck) | **only the free `--chunk 1` fix** (T6); the distinct-binary farm already exists in `bulk_harvest`; the same-binary shard farm deferred (conditional on P29 volume) | the premise was stale — the gate stopped being the bottleneck in Phase 23 (drafting is) |
| Fleet-wide Ghidra-C prefetch | import all 138 overlay programs + cache every stub | **only the resident's 21** (the flag-plant needed them) | the SC07 harvest was h_exact (no drafting → no Ghidra-C needed); full-fleet prefetch is P29 fuel when the family campaign needs it |
| Grinder warm-start / `diff_regions.py` / burn-down tracker | build them | **deferred/carried to P29** (T7c) | not load-bearing for this phase's actual work; genuine new tools better built with the campaign that uses them |
| The swing number | a measured close-rate | **measured but CEILING-UNKNOWN** (~3% as-tooled; the 274 DIFF is the tooling-vs-wall ambiguity, un-disambiguated) | refused to rush a clean number on tight context — that is how Phase 26 manufactured a wrong 0% (P9); a classified measurement + a named probe is the honest deliverable |
| Resident flag-plant | 100% | **90.34% (21→14)** + an honest classed dossier | the "OR an honest wall dossier" branch; the 5 jtbl need the carve, the 5 PLUMBING need a def-side lever, the 4 DIFF are genuine residuals — none forced (forcing is how the ≈0% doctrine was made) |
| T7 scope | burn-down + stale labels | **EXPANDED (Drew)** to the `audit-binaries` R36 gate + fixing the blind `disc_code_sweep` | the SC07 evidence showed 4 consumers silently ignoring onboarded binaries — a gate, not a label sweep, is the fix |
| Fable5 slot | conditional | **UNUSED** | no new wall class appeared that cheap-Opus/known idioms couldn't handle; spending a discoverer on already-discovered idioms is the one thing the doctrine forbids |
| **Three self-inflicted defects** | (n/a) | **the registry `yaml.safe_dump` (H5), two DIFF mis-reports (R14), the `match_one` shared-scratch** — each caught + fixed forward | the phase's own thesis (instruments lie) applied to *me*; each is recorded honestly, not buried under the 95.6% headline |

## Commit Message

```
(Phase 28 landed as 16 commits commit:0644..commit:0659 + this PhaseEnd. Fleet 67.0 -> 68.9% instr,
140/140 byte-identical, 0 NON_MATCHING throughout. The granular trail -> logs/Phase28.md.)

feat(phase-28): the endgame engine -> the instrument-repair phase; B2 lives, SC07 wired, R36 (v1.27.0)

- RE-SCOPED at plan time (R35): the roadmap's swing number rested on a broken-tool probe. B2's
  "structural families bank ~0%" (0/8, which reshaped 2 phases of strategy) was a MISSING CARVE ->
  8/8, then 102/115 (88.7%). The ~0% doctrine has NO surviving post-fix evidence.
- T0 img_path derive-not-guess -> un-hid a 230,612-ins SC07 pool doubly hidden (P27 onboarded 4
  overlays, never regenerated the map; the hardcode would have called every member "LEN").
- T3-A: the SC07 pool is h_exact + UNWIRED, not h_seq. T4 dedup_extend (NEW) wired 6174/6457 (95.6%)
  -> groups 134->138 binaries, C1 coverage +6174. NOT member_adapt (the number said build nothing).
- T5: resident 21->14 (90.34%, 7 banked via an Ultracode wave) + honest dossier for the 14; fixed
  progress.py (#if 0 + len()-sum) and match_one's FAKE isolation (found by an agent mid-wave).
- T2 purged the poisoned grinder blacklist (8/22 matched anyway). T6 killed the --chunk 1 double-build.
- T7: make audit-binaries (the R36 citizenship gate, negative-control-proven) + fixed disc_code_sweep's
  BLINDNESS to compressed code (the type-4 row was vacuous for 138 known binaries) + the worklist key-bug.
- T3b: the legacy h_seq swing number = ~3% AS-TOOLED, CLASSIFIED (274 DIFF / 37 PLUMBING), ceiling
  UNKNOWN -- the 274 DIFF is byte-PURE members whose remapped bodies don't reproduce (the same
  tooling-vs-wall ambiguity that resolved to TOOLING twice this phase). P29 disambiguates before scaling.
- THREE SELF-INFLICTED DEFECTS fixed forward: the registry yaml.safe_dump (H5, destroyed 47 comments +
  1832 hex fields, invisible to every byte-gate), two DIFF mis-reports (R14), the match_one shared scratch.
- rule R36 (a newly-discovered binary is not real until every consumer knows it; enforced by
  audit-binaries). cookbook §53. R22 140/140 throughout; tools-health OK; dedup 1840/0.
```

## Rules Added This Phase

| Rule | Reason |
|---|---|
| **R36 — A newly-discovered binary is not real until every consumer knows it.** Onboarding a code-bearing payload produces a *byte-clean* binary that is not yet a *citizen*: the same change must wire it into every consumer that enumerates binaries — the sig set, the family map, the dedup registry (or an explicit exemption), the shared-header include, and the reports/labels — and that must be **asserted by a gate (R32), not remembered.** A binary a consumer silently ignores is invisible work, and the byte-gate is structurally blind to it (R34). Enforcement shipped: **`make audit-binaries`** (negative-control-proven, in `tools-health`). | P27 onboarded 4 SC07 overlays byte-clean; P28 found **four** consumers silently ignoring them (`family_remap.img_path`, `.run/family_hseq.json`, `config/dedup.us.yaml`, the overlays' own `.c`), hiding ~6,400 already-matched bodies. Every failure was silent. Drew-approved 2026-07-16. |

*(No OTHER new governance rules — per the Phase-8+ precedent, the phase's other lessons are techniques (→ cookbook **§53**) + findings (→ `decision-log.md`, `calibration.md`). The **three self-inflicted defects** reinforce existing rules rather than needing new ones: the registry-destroying `yaml.safe_dump` is **H5** ("never silently drop comments on a rewrite") + the R34 corollary that a byte-gate is a null *document* oracle; the two DIFF mis-reports are **R14** (verify counts against the bytes — I read `head -6` and generalized); the `match_one` fake isolation is the docstring-vs-default gap R35 governs. The **carve-law** ("sweep a family with the tool its exemplar needed; a 0% from the wrong tool is not evidence") is cookbook §53, a direct application of R35/G3.)*

## PhaseEnd Changelog

**v1.26.0 → v1.27.0 — Phase 28 complete (Gen2 phase 20; the instrument-repair phase).** Chartered to measure "the swing number" and build a delta engine around it, the phase found in **planning** that the number's evidence was untrustworthy — the "structural families bank ≈0%" doctrine that had reshaped two phases of strategy rested on a **broken-tool probe** (B2's 0/8 was a missing jump-table carve, not a wall). Re-scoped on that finding, the phase became **instrument-repair + honest measurement**, and delivered: **B2 LIVES** (8/8 → 102/115, and the ≈0% doctrine has no surviving post-fix evidence); a **doubly-hidden SC07 pool un-hid and wired** (`img_path` derive-not-guess + the new `dedup_extend` → **6,174 h_exact members banked, 95.6%**, groups 134→138 binaries); the **resident resolved** (21→14, 90.34%, + a classed dossier); and the **R36 citizenship gate** (`make audit-binaries`) that makes a newly-onboarded binary unable to hide from the tools again. The **legacy h_seq swing number** was measured and **classified** (~3% as-tooled, 274 DIFF / 37 PLUMBING) but honestly left **ceiling-unknown** — the 274 DIFFs are byte-PURE members whose remapped bodies don't reproduce, the same tooling-vs-wall ambiguity that resolved to *tooling* twice this phase, and the disambiguating probe is handed to P29 rather than rushed. Fleet **67.0% → 68.9% instr / 47.8% → 49.5% distinct** at **140/140 byte-identical, 0 NON_MATCHING** throughout; `disc_code_sweep` fixed (it was blind to compressed code, so it could not have found a hidden overlay — now it can). The phase's honesty ledger includes **three self-inflicted defects, caught and fixed forward** — a registry-destroying `yaml.safe_dump` (H5; invisible to every byte-gate because they measure bytes, not documents), two DIFF mis-reports (R14), and a `match_one` that faked the isolation its docstring promised (caught by an AI agent mid-wave). One rule (**R36**); techniques → cookbook §53; findings → decision-log/calibration. The decisive lesson, five times over: **every "compiler wall" this phase probed was our own tooling** — and the byte-gate, a perfect correctness oracle, is a null oracle for coverage (R34), for documents (H5), and for the iteration loops agents steer by.

## Roadmap delta (roadmap §0 — what Phase 28 changed about the road ahead)

- **B2 LIVES; the "structural families ≈0%" doctrine is RETIRED on no surviving evidence.** The doctrine's one post-fix probe (B2) refuted it (0/8 was a missing carve → 102/115); its three Phase-26 corroborating probes all predate the `_carry_macros` fix that made such a probe honest. `calibration.md`'s "decisive P28/P29 input" table is rewritten. **P29's arithmetic is NOT settled** — see the swing number.
- **The swing number is ~3% AS-TOOLED, ceiling UNKNOWN** (legacy h_seq; classified 274 DIFF / 37 PLUMBING). **P29 MUST run the disambiguating probe first** (reloc-position mismatch ⇒ fixable remap, ceiling far above 3%; regalloc-away-from-relocs ⇒ TU wall). Do not scale "(cores)×(reach)" on 3% until then.
- **A doubly-hidden pool is now VISIBLE and WIRED:** the SC07 harvest banked 6,174 h_exact members. The lesson generalizes — any future onboarding (the 39 type-1 modules) must be wired into every consumer, now enforced by **R36 / `make audit-binaries`**.
- **`member_adapt.py` is VACATED for the h_exact case** (`dedup_extend` is the right tool) and **deferred for the h_seq case** (pending the T3b disambiguation — if the residual is TU-context, a delta engine is the P29 tool; if it's incomplete remap, `symbol_map` is the fix).
- **Binary count firm at 140** (main + resident + 138 overlays); the disc is byte-verified complete for type-4 (0 further hidden), 39 type-1 modules pending load-address RE. The completion contract's denominator is stable.
- **Carried tools (none lost):** the burn-down velocity tracker (T7c), `diff_regions.py`, the grinder family-warm-start, the same-binary shard farm. `make audit-binaries` is new and standing.

## Plain-English Recap

This phase was supposed to measure one number — how often the "same function, slightly different per level" pattern can be rebuilt automatically — and build a tool around it. Instead, before writing a line, we found that **the number the whole plan rested on was wrong**, measured months ago with a broken tool: a "families can't be automated, ~0% success" verdict that had steered the project's strategy for two phases. Run correctly, that same family succeeded **89%** of the time — the earlier failure was a missing build step, not a real wall. That set the tone for everything: **almost every "the 1990s compiler beat us here" turned out to be our own tools lying.**

Chasing it, we found four game levels that had been added last phase but **never introduced to any of our tools** — so about 6,400 functions already solved elsewhere were sitting unrecognized. One new command wired them in: **95.6% rebuilt, for essentially no cost.** We drove the game's permanent engine chunk from 85% to **90%** with a swarm of AI agents, and wrote an honest map of the 14 pieces left and exactly why each is hard. And we built a **safety gate** — the thing you asked for — that now refuses to let a newly-found level hide from our tools ever again; we proved it by deliberately breaking one level and watching the gate catch it.

The game went from **67% to 68.9%** rebuilt bit-for-bit — but the real story is *how*: almost none of it came from beating the compiler, and a lot came from **fixing our own instruments**, including three mistakes that were mine — a tool that quietly destroyed a documentation file (caught and repaired), two miscounts I reported before checking, and a match-checker that faked the isolation it advertised (caught by one of the AI agents mid-run). On the headline question, we were deliberately honest: the leftover "harder" families rebuild at only ~3% *with today's tools* — but we did **not** call that a ceiling, because the way they fail is the exact same "is it the tool or the compiler?" ambiguity that kept turning out to be the *tool* this phase. So we wrote down precisely the one experiment that settles it, for next phase, rather than guess. Nothing broke; all 140 pieces of the game still rebuild perfectly. The lasting win isn't the percentage — it's that our instruments lie to us a lot less than they did, and there's now a gate that keeps it that way.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase28.md` (R19, via `git mv` — left uncommitted for Drew's milestone-close commit). The Phase-28 work is committed across the session (`commit:0644`..`commit:0659`); **Drew commits AND pushes** this PhaseEnd + the archived log + the two regenerated digests (`docs/progress.fleet.md`, `.run/backlog.jsonl`) (R6/R20 — the milestone-close is the human-controlled gate-2 sign-off). No Ghidra DB change this phase (R23 no-op — the `db.*.gbf` churn is restart-noise; do NOT stage). Gen2 continues — do **NOT** start Phase 29 here. Start a **fresh session** (effort **Max**, **plan mode**) for **Phase 29 — The Family Campaign**, opening with the T3b disambiguating probe before scaling any yield arithmetic. Keep this file forever.
