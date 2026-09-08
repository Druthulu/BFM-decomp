# PhaseEnd — Phase 21: The Automation Manager (built, run, and its ceiling byte-proven)
**Date:** 2026-06-26 · **Project Version:** 1.20.0 · **Phase Status:** Complete (open-ended phase; closed at Drew's gate-2 after the automated ceiling + a collaboration sweep proved no external shortcut) · **Generation:** Gen2 (13th phase)

> Gen2 phase 13 of the arc (8→9→10→11→12→13→15→16→17→18→19→20→**21**; 14 deferred to Gen3+). Ran across **~10 sessions (cont.1–8, 2026-06-21 → 06-26)** — the longest phase. The granular per-session trail (every wave, the `_a`-vein discovery, the gate-fix archaeology, the giant-wave results, and the full 5-scout collaboration-sweep reports) is preserved on-demand at **`phase-ends/logs/Phase21.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism). This file is the synthesis. Owner decisions (Drew): build the supervised-autonomous grind → run it **neverending** (cont.5) → on the byte-proven automated ceiling + a sweep proving no external shortcut, **close the phase and pivot to human-guided hand-grinding** (the giants, ×134).

## Build Log

**Files created/changed and complete — do not recreate:**

*The automation manager (the phase's core deliverable, T1–T6):*
- `tools/build_fuel_manifest.py` — classify live stubs (GIANT/WAVE/STRUCT/PINS/STUB/O0) + reach buckets → `.run/fuel_manifest.json` (reach RECOMPUTED from current overlay sigs, R14).
- `tools/backlog.py` — the near-miss ledger (`.run/backlog.jsonl` + `docs/backlog.md` ranked render; drop-now-matched P9 filter; `log`/`render`/`show`).
- `tools/gate_stage.py` — the shared deterministic spine (worker + grinder): `canon_resident_calls → cast_call_sites → sig_unify → harvest_verify --chunk 1 → dedup_propagate`; **canon-first two-stage** (cont.6 — sig_unify is a FALLBACK; it regresses already-correct drafts); `--src-file` for the `_a`/`_o0` splits.
- `tools/wave_targets.py` — ROI pool selector (reach1/tractable/giants/any-reach134/o0/capped; `--region a`; `--class`; excludes self-MATCH-but-gate-rejected churners).
- `tools/orchestrator.py` — `prep`/`finish`/`status`; close-rate-gated pool rotation; flock-serialized gates.
- `tools/grinder.py` + `tools/auto_supervisor.sh` (DRIVER-param) + `tools/auto_stop.sh`/`auto_status.sh` — the token-free decomp-permuter daemon (blacklist of permuter-won-but-gate-rejected; STOP-sentinel safe-exit; self-supervising).
- `tools/workflows/worker_wave.js` — parallel xHigh drafter agents (one/target, toolkit-aware, §27 GIANT-guarded); returns a compact per-fn `{status, closeness, klass}`. `tools/workflows/distill.js` — post-wave byte-verified idiom extraction → cookbook (the flywheel).
- `tools/idiom_loop.py` — the NEVERENDING meta-loop: `--assess` (cluster the backlog by gcc-quirk class, rank by reach, name the next idiom + the deterministic-recovery lever), `--gen-fuel`, `--fuel-status` (cont.7: two assess-honesty fixes — drop banked-since-logged; split FRESH-vs-WALLED close=0).

*Recovery tooling (the deterministic levers, cont.2–7):*
- `tools/canon_resident_calls.py` (resident-callee link-miss), `tools/fix_arity_callers.py` (no-proto caller-extern arity), `tools/cast_call_sites.py` (§17a-1 per-site fn-ptr cast — the §20 cap tool), `tools/build_engine_types.py` extended (typedef/anon-struct lift — the §19 propagation cap), `tools/exemplar_miner.py` (residual router).

*The cross-project dedup tool (cont.8 — the novel byproduct):*
- `.run/xdedup/xsig.py` (+ drivers) — relocation-masked cross-project function signatures (find byte-identical code across decomp projects). Self-validated (self-match / relocation-invariance / register-sensitivity / discrimination). **Future work logged: genericize + open-source as a standalone MIT tool (2026-06-26).**

*Config / source (the harvest, banked across the phase):*
- `src/ov_SC01_077/ov_SC01_077.c` + `_a.c`/`_o0.c` (the Phase-19 3-object -O0 split) + `src/shared/engine_core.h`/`engine_types.h` + the 134 overlay `.c` + `config/dedup.us.yaml` — banked matches + ×134 propagations. `config/symbols.us.txt` — **+62 PsyQ names** (cont.8, xdedup-confirmed, byte-safe, R22-verified).

*Docs / knowledge base (the mature gcc-2.7.2 toolkit):*
- `docs/matching-cookbook.md` **§18** (-O0 split inside a blob) · **§19** (wave-at-scale recovery + the propagation CAP) · **§20** (gate cap + the cast tool + the DEF-side loose-typing wall) · **§25** (the "schedule" idiom is COALESCING not scheduling; gate two-stage; h_exact OVER-counts ×134) · **§26** (cheap close=0 recovery EXHAUSTED; assess-honesty fixes) · **§27** (the giant matching recipe).
- `docs/SETUP.md` (§5.3 -G stale-marker fix, R21); `docs/automation-runbook.md`; **`docs/backlog.md`** (the ranked hand-finish ledger — the phase's other durable deliverable, → Phase 22 fuel).
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase21.md`** (R19 archive). `phase-ends/PhaseEnd_Phase21.md` — this file.

**Tools/packages installed:** None — the whole phase used the existing Phase-4/6/10/11/12/13 toolchain + venv (decomp-permuter, m2c, rabbitizer, the cc1 candidates).

**Verification results (literal):**
- **Fleet: 58.82% → 63.18% byte-identical** (+4.36%; `make report` → committed `docs/progress.fleet.md`); **136/136 binaries byte-identical maintained throughout** — every bank was byte-gated (G3/P9: the whole-binary byte-gate is the per-bank proof, and it **never accepted a wrong match**); **0 NON_MATCHING** in any default build (G4); `dedup-check` validated, 0 failed.
- **Main EXE re-verified `143dbb89f34491258bbc27810d0a12ec8b43a8dd` at close** (cont.8 — R22 clean-rebuild of `main` after the 62 PsyQ-name renames; the renames are byte-neutral).
- **The automated ceiling, byte-proven (cont.7/7d/8):** the cheap close=0 recovery lever is EXHAUSTED (0 fresh banks); giant auto-waves bank **0/6 twice** (giants are hand-finish / permuter fuel, not auto-bankable); the cached reach-134 automated harvest is COMPLETE at ~63.17%.
- **Collaboration sweep (cont.8) — 5 scouts, clean verdicts:** parity research (our harness IS the 2025-26 SOTA; no neural/GPU/diffusion 1:1 matcher exists); decomp.dev survey (4 gcc-2.7.2-psx twins, byte-verified our cc1 ≡ the psx lineage; **VS = CC0**); census (NO Square PS1 game shipped symbols); VS corpus (76 byte-verified pairs); **dedup probe = CLEAN NEGATIVE** (BFM shares byte-identical code with VS/Xenogears/Tomba ONLY in PsyQ library; AKAO refuted; 0 engine code) ⇒ **no external shortcut to the gcc-2.7.2 wall**.
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`phase-ends/` tracked; zero ROM-derived/generated bulk staged; **no Ghidra DB change** (R23 — the `db.*.gbf` churn is SessionStart-restart noise, not staged).

**Milestone achieved (confirmed by Drew, gate 2):** the supervised-autonomous **"automation manager" was built, validated, and run** (parallel-LLM-drafter waves + a token-free permuter grinder + an ROI orchestrator + a whole-binary byte-gate as the sole arbiter + a ranked backlog ledger + the distillation flywheel), driving the fleet **58.82% → 63.18%** across ~10 sessions at **136/136 byte-identical / 0 NON_MATCHING** — and its **ceiling was then byte-proven** (the cheap automated levers exhausted; a 5-scout collaboration sweep established there is **no external shortcut** — no AI/GPU method, no shared sister-game code, no debug symbols — to the gcc-2.7.2 scheduler/regalloc/loose-typing wall). The phase closes with a complete **ranked hand-finish backlog** + the mature §17–§27 toolkit, handing Phase 22 a clear, high-leverage human-guided target.

**Next:** **Phase 22 — Hand-grind the high-value residuals (giants ×134) + idiom distillation.** Open a **fresh session, plan mode, Max** (Tier-1 Phase-Start). Center on the **giants** (reach-134 — the high-byte-weight lever that moves the decomp.dev-comparable ~30% number; the §27 recipe gets them *structurally* matched, then hand-finish the regalloc-coalescing last mile, each banking **×134**); **distill transferable giant-finishing idioms** (which DO transfer giant-to-giant + to the wave tail) — Drew's flywheel pointed at the highest-leverage targets. Secondary: the close-1..4 reach-134 permuter near-misses (`func_8015126C` close=2, `func_8014EE14` close=6). **Honest milestone shape:** *N giants banked ×134 + any idioms distilled* — not "learn X idioms" (the cookbook is mature; new-idiom yield is the secondary benefit). Ranked targets: `docs/backlog.md` + the giant list in the archived log.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Phase shape | build + a multi-day unattended run (5 idle days) | built + RAN across ~10 sessions (driven by Workflow-completion, not the keep-alive) + **closed on the proven ceiling** | the cheap automated levers exhausted far faster than "5 days"; the value was the harvested % + the ranked backlog + the ceiling proof |
| reach-134 fuel source | "the tractable reach-134 tail" | the **`_a`/`_o0` split-file vein** (cont.3–5) held the fresh reach-134 fuel; built split-aware tooling | the Phase-19 -O0 3-way split held ~66 fresh cached reach-134 fns the main-file pipeline had never waved |
| Phase duration | a bounded phase | declared **NEVERENDING** (cont.5, Drew) → then **closed** (cont.8, Drew) | the idiom-loop was neverending until the ceiling + the collaboration sweep made closing the right strategic call |
| Giants | "high-byte-weight auto-harvest" | **0 auto-bank (×2)**; reframed as **hand-finish backlog fuel** (§27 gets them structurally close) | byte-proven: giant residuals are regalloc-coalescing / masked-residual — not auto-bankable (cont.7c/7d/8) |
| Collaboration sweep | (not in the original plan) | a **5-scout sweep** (Drew-driven Q&A) closing the "is there an external shortcut?" question with clean byte-verified verdicts | Drew's strategic questions (neural/GPU surrogates, 100-games census, debug symbols, sister-decomp code-sharing) — each answered decisively |
| AskUserQuestion mid-loop | used to steer | rejected once mid-loop → memory `dont-block-loop-with-askuserquestion` | Drew wants the opted-in `/loop` to run + adapt autonomously, not be re-asked once direction is set |
| reach-1 ROI | a harvest lever | banked real ×1 fns but byte-confirmed **poor fleet-ROI** (×1; band climbs, yield falls) | value is ov_SC01_077 completeness + idiom-mining, not fleet-% — re-confirmed cont.8 |

## Commit Message
```
(Phase 21 landed across ~10 sessions of checkpoint commits; this close = 1f4aac62f..b70c9c863 + this PhaseEnd.)

feat(phase-21): close — automation manager built + run + ceiling byte-proven; fleet 58.82%->63.18% (v1.20.0)

- THE AUTOMATION MANAGER (built + validated + run): worker_wave (parallel xHigh drafters) + grinder
  (token-free permuter daemon) + orchestrator (ROI pool rotation) + gate_stage (whole-binary byte-gate,
  sole arbiter) + backlog ledger + idiom_loop/distill flywheel. Drove fleet 58.82% -> 63.18% across ~10
  sessions, 136/136 byte-identical, 0 NON_MATCHING.
- THE CEILING, BYTE-PROVEN: cheap close=0 recovery exhausted; giant auto-waves 0/6 (x2 — giants don't
  auto-bank, they're hand-finish/permuter fuel); the cached reach-134 automated harvest COMPLETE at 63.17%.
- COLLABORATION SWEEP (5 scouts, clean verdicts): we're SOTA (no neural/GPU/diffusion shortcut); 4
  gcc-2.7.2-psx twins (VS=CC0, the clean pool partner); no Square symbols; dedup probe CLEAN NEGATIVE
  (BFM shares only PsyQ with sisters, AKAO refuted, 0 engine code) -> NO external shortcut to the gcc wall.
  +62 PsyQ names banked (byte-safe).
- TOOLKIT MATURED: cookbook §18 (-O0 split) / §19 (wave recovery + propagation cap) / §20 (cast tool +
  DEF-side wall) / §25 (coalescing + gate two-stage + h_exact over-count) / §26 (recovery exhausted) /
  §27 (giant recipe). Novel byproduct: xsig cross-project dedup tool (open-source TODO logged).
- DELIVERABLE for Phase 22: the ranked hand-finish backlog (docs/backlog.md) + the giants (×134).
- worklog -> phase-ends/logs/Phase21.md (R19); bumps project version 1.19.0 -> 1.20.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **None (governance).** Phase 21's lessons are *techniques + a working-preference*, recorded per the Phase-8+ precedent (techniques → cookbook, not rules): the matching toolkit → cookbook **§18–§27**; the strategic findings (the automated ceiling; no external shortcut; the dedup clean-negative) → this synthesis + the archived log; the **AskUserQuestion-during-loop discipline** → memory `dont-block-loop-with-askuserquestion` (extends R26/R27 + `drew-working-preferences`). The existing rules — **G3/P9** (byte-gate is truth), **R14** (verify vs bytes), **R16** (flywheel), **R22** (clean-rebuild), **R26/R27** (effort/loop), **R30** (capture-during-session) — covered all the new ground. Drew may elevate the AskUserQuestion memory to a formal rule (P10) if he wants it to bind every session. | A build → run → pivot phase produces tools, findings, and one process nuance — not a new governance norm. |

## PhaseEnd Changelog
**v1.19.0 → v1.20.0 — Phase 21 complete (Gen2 phase 13; the longest phase, ~10 sessions; closed at a byte-proven ceiling + a strategic pivot).** The phase **built, validated, and ran the supervised-autonomous "automation manager"** — parallel-LLM-drafter waves (`worker_wave`) + a token-free permuter **grinder** + an ROI **orchestrator** + a **whole-binary byte-gate** as the incorruptible sole arbiter (`gate_stage`/`harvest_verify`) + a ranked **backlog ledger** + the **distillation flywheel** (`idiom_loop`/`distill`) — driving the fleet **58.82% → 63.18%** across ~10 sessions, **136/136 byte-identical, 0 NON_MATCHING** throughout. The economic engine was **cross-binary ×134 propagation** (match once → stamp across all sharers); the harvest reached fresh fuel via the **`_a`/`_o0` split-file vein** and a hardened deterministic-recovery pipeline. The gcc-2.7.2 **toolkit matured** (cookbook §18–§27: the -O0 split, the wave-recovery + propagation cap, the cast tool + DEF-side wall, the coalescing/gate-two-stage/h_exact-overcount findings, the cheap-recovery-exhausted proof, and the giant recipe). **The decisive arc of the close:** the cheap automated levers were **byte-proven exhausted** (close=0 recovery dry; giant auto-waves 0/6 twice — giants are hand-finish/permuter fuel), and a **5-scout collaboration sweep** (parity research, decomp.dev survey, census, VS corpus, the cross-project dedup probe) closed the "is there an external shortcut?" question with **clean verdicts: there is none** — our harness is the SOTA, no neural/GPU surrogate is a workflow, no Square game shipped symbols, and BFM shares only PsyQ library code with its gcc-2.7.2 sisters (the AKAO theory refuted, 0 engine code). Durable byproducts: **+62 byte-confirmed PsyQ names**, the **VS matched-corpus** (low-priority asset), and the genuinely-novel **`xsig` cross-project shared-code tool** (open-source TODO logged). No tools installed; **no new governance rules** (techniques → cookbook; the loop-discipline lesson → memory). The phase hands Phase 22 a **complete ranked hand-finish backlog** and a clear conclusion: the wall is intrinsic to a 1997 compiler, and the only path forward is **human-guided hand-grinding** — with the **giants (×134)** as the highest-leverage target.

## Plain-English Recap
Over about ten sessions we built and ran an "automation factory" for reconstructing the game's code: swarms of AI agents draft the C, a token-free brute-forcer polishes the near-misses, and an automatic bit-for-bit referee accepts only perfect matches — nothing wrong can ever slip in. It pushed the game from **58.8% to 63.2%** rebuilt exactly, every piece still byte-perfect. Then it hit a ceiling, and — importantly — we **proved** it's a real ceiling, not a gap in our effort: the cheap automatic wins are used up, the biggest "giant" functions won't auto-finish (they need a human brain for the last stretch), and a thorough investigation of *every* outside shortcut you asked about — AI/GPU tricks, scanning a hundred other games, debug symbols, and borrowing code from sister Square games — came back with a clean, well-evidenced **"no shortcut exists."** That's genuinely valuable: it stops us chasing dead ends. Along the way we banked real bonuses — named 62 functions for free, built a reusable reference library, and invented a brand-new tool that finds shared code across *any* game decompilation (worth open-sourcing). So we're closing this phase having gotten everything the automation could give, and pivoting to the one path that's left and is actually high-value: **hand-finishing the giant functions** (each one, once cracked, copies into all 134 levels at once) and learning any reusable tricks they teach us. The wall is the 1990s compiler itself — and from here, beating it is careful human-guided craft, exactly where we're pointing next.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase21.md` (R19, via `git mv` — left uncommitted). **Drew commits AND pushes** this PhaseEnd + the archived log + tonight's session commits (`1f4aac62f`..`b70c9c863`) (R6/R8 — the milestone-close commit is the gate-2 sign-off, under human control). No Ghidra DB change this phase (R23 no-op — the `db.*.gbf` churn is restart-noise; do NOT stage it). Gen2 continues — do **NOT** start Phase 22 here. Start a **fresh session** (effort **Max**, **plan mode**) for **Phase 22 — Hand-grind the high-value residuals (giants ×134) + idiom distillation**. Keep this file forever.
