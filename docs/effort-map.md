# Effort Map — Claude Code reasoning settings for BFM-decomp

> **Evolvable reference (docs/ layer). Created 2026-06-13.** Update freely as the harness changes — this is not the static constitution.
> Companion to `CLAUDE.md` → "Reasoning & Model Protocol." CLAUDE.md points here; the per-phase guidance, the Max-vs-Ultracode rule, and the verified harness mechanics live here. **Where CLAUDE.md's tier language and this file differ, this file governs.**

---

## How the controls actually work (verified 2026-06-13)

- **Effort ladder:** `low / medium / high / xHigh / Max`, set with `/effort` (slider) or `/effort <level>`. This is *depth* — how hard a single agent reasons. `/effort auto` resets to model default.
- **Persistence:** `low / medium / high / xHigh` persist across sessions (saved as the baseline). **`Max` and `Ultracode` are session-only** — they revert to the persistent baseline (currently xHigh) on a new session. **xHigh is the highest level you can make sticky.** To run Max, re-apply `/effort max` at the start of each session.
- **Ultracode is NOT a deeper effort level.** `/effort ultracode` runs the model at **xHigh** *and* additionally turns on **multi-agent orchestration** (Claude fans out parallel subagents via Workflow). Same as putting the keyword `ultracode` in a prompt. Session-only.
- **Why "Ultracode looks like xHigh":** because it *is* xHigh per agent — the indicator correctly shows xHigh. Ultracode adds **breadth** (parallel agents), not **depth**.
- **Confirm what's active:** the status line next to the spinner (e.g. "with max effort"), `/status`, or `/effort` (slider position).

---

## The two axes (the key mental model)

| | **Depth** — how hard one agent thinks | **Breadth** — how many angles at once |
|---|---|---|
| Control | `/effort` level (… xHigh < **Max**) | **Ultracode**, or Claude-driven **Workflow** fan-out |
| Best for | one hard, irreversible reasoning problem | surveying / auditing / matching many independent items |
| BFM examples | compiler fingerprint, US overlay-address derivation, phase planning, PhaseEnd synthesis | EXE-wide duplicate report, difficulty inventory, bulk matching of independent leaves |

They are **not combinable via `/effort`** (it holds one value). And **global Ultracode caps every task at xHigh depth** — exactly wrong for the fingerprint/address work. So breadth is applied **surgically**: Claude proposes a Workflow fan-out for genuinely breadth-shaped tasks (you opt in) while single-thread depth stays at Max.

---

## Policy for this project

1. **Default working level = `Max`.** Usage is not a constraint (Max20 plan). Max's only cost is mild overthinking / latency on trivial tasks. Re-apply `/effort max` each session (it does not persist).
2. **Drop to `xHigh` only for speed** on purely mechanical Tier-3 stretches (installs, parser boilerplate, report scripts) when slow turns get annoying. Correctness is unaffected.
3. **Do NOT globally enable `Ultracode`.** It would run the deep, crown-jewel tasks at only xHigh depth. Instead, parallelism is surgical: Claude invokes Workflow/subagent fan-out for breadth-shaped tasks (you opt in). You *may* flip Ultracode on for an explicitly breadth-only stretch — accepting xHigh per-agent depth there.

---

## The decision rule — Max vs xHigh vs Ultracode

- **Max** — a wrong answer poisons everything downstream and is hard to reverse, **or** root cause is unclear (non-obvious debugging), **or** it is deep synthesis (phase plan / PhaseEnd). *Depth matters.*
- **xHigh** — the design is already settled in the approved plan and this is execution; single-file, clear-requirements, mechanical. (Also the highest *persistent* baseline.)
- **Ultracode / Workflow fan-out** — the task is "run the same analysis across many independent items" (survey, audit, dedup, bulk match). *Breadth matters more than per-item depth.*

Live heuristic, in order:
1. Is the design already settled in the approved plan, and this is just execution? → **xHigh.**
2. Is this a phase plan, a PhaseEnd, a genuine architectural fork, or non-obvious debugging? → **Max.**
3. Would a wrong answer systematically poison everything downstream *and* be hard to reverse? → **Max** (the "use sparingly" tier).
4. Is it the same analysis across many items? → **Ultracode / Workflow.**

---

## Per-phase map (Gen1)

**Constant for every phase:** the **Phase Start plan** and the **PhaseEnd file** → **Ultracode minimum; Max only for the heavy phases (3, 6) and the Gen1-exit PhaseEnd (7)**. Mechanical-phase PhaseEnds (2, 4, 5) are fine at xHigh/Ultracode — the synthesis is bookkeeping, not novel reasoning. (Confirmed 2026-06-13: Drew called Max unnecessary for the Phase-2 PhaseEnd.)

| Phase | **Max — mandatory (never drop)** | **xHigh — fine (drop for speed)** | **Breadth — Ultracode/Workflow helps** |
|---|---|---|---|
| 1 — RE stack + import ✅ | — | (ran at ~xHigh; correct — headless scripts) | — |
| 2 — Extraction pipeline | none on first pass; escalate **only if** LZSS cross-validation vs CUE fails (non-obvious debugging) | ISO9660 walker, .CD/PAC splitter, LZSS decoder (first pass), SQV awareness, sha1 manifest, format docs | — |
| 3 — File-loader & overlay map | ⭐ **US address derivation** (resident blob + ≥1 overlay) **+ PCSX-Redux RAM-dump proof**; the deep RE call-chain tracing | ledger seeding, blob import *once proven*, map write-up | (optional) surveying many candidate loader functions |
| 4 — Build toolchain | none | **everything** — apt installs, sha-verified compiler fetch, `make check-env`, version recording | — |
| 5 — splat config + byte-match | splat `.yaml` section-boundary authoring/debugging (esp. if the clean link fights back) | Makefile pipeline, `check.us.sha`, `make expected` | — |
| 6 — Compiler fingerprint + first matches | ⭐⭐ **compiler-fingerprint ladder + arbitration** (the single highest-stakes task in Gen1); first matches incl. LZSS (proving loop + pin) | recording the pinned triple, `decompile.py`/asm-differ wiring, INCLUDE_ASM headers | (later) bulk matching of independent leaf functions |
| 7 — Loop at scale + Gen1 close | Gen1-exit synthesis (in the PhaseEnd); first jump-table match; loader-cluster matching (deep) | report scripts (difficulty/dup/progress), README | ⭐ **EXE-wide duplicate report + difficulty inventory + bulk matching** — real Workflow fan-out wins |

**The Max shortlist** (reach for the ceiling only here): (1) Phase 6 fingerprint ladder, (2) Phase 3 address derivation + RAM proof. Conditional escalations: Phase 5 splat config if the link won't go clean; the Phase 7 Gen1-exit PhaseEnd.

---

## Plan-mode (Phase Start) effort

Phase Start planning is deep single-thread synthesis → **Max**. Mandatory-Max for Phases **3** and **6**; xHigh would suffice for the mechanical phases (2, 4, 5, 7) but since Max is the default, just leave it. Use **Ultracode during planning** only when the plan needs broad reconnaissance first (surveying many candidate functions) — realistically only Phase 3 and Phase 7.

---

## The Effort-map check (Rule R7 — formalizes at PhaseEnd_Phase2)

- **Before each Phase Start plan:** state the recommended effort for *planning that phase* (per this file) and confirm the developer has it set.
- **In the phase plan:** annotate every task with its recommended effort level.
- **At every task handoff** and in the Session Start "next task" statement: restate the recommended effort.
- This file is evolvable — correct it as the harness changes or as the per-phase reality is learned.
