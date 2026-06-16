# PhaseEnd — Phase 12: Key engine systems (resident harvest, script/event, save, SQV)
**Date:** 2026-06-16 · **Project Version:** 1.12.0 · **Phase Status:** Complete (milestone confirmed by Drew, gate 2) · **Generation:** Gen2 (5th phase)

> Gen2 phase 5 of the arc (8→9→10→11→**12**→{13}→14). The granular per-task trail (the 5 workflow passes,
> the gate logs, the extern-conflict diagnostics, the save trace) is preserved on-demand at
> **`phase-ends/logs/Phase12.md`** (R19 — NOT auto-loaded; consult only when researching a mechanism).
> Owner decisions (2026-06-16): milestone = **"substantial + honest deferral"** (criterion #2 amended); planned
> guided save trace; **full substantial resident harvest** (after T1 found no library to link); save deep-data =
> defer (Gen3); Ultracode used for the harvest (Drew enabled it).

## Build Log

**Files created/changed and complete — do not recreate:**

*New reusable tooling (committed — feeds Phase 13 directly):*
- `tools/harvest_verify.py` — **the byte-gate.** Substitutes each drafted `.c` for its `INCLUDE_ASM` stub,
  `make build BINARY=<bin>`, keeps it ONLY if the image stays byte-identical, else reverts (chunk + bisection).
  The build is the sole arbiter (G3/P9) — a wrong match cannot be accepted. Strips inline scalar-typedef
  redefinitions (C89 dup-error ≠ byte miss). Binary-parameterized (`--binary/--src/--asm-subdir/--good-sha`).
- `tools/match_one.py` — **per-function isolated compile + relocation-masked diff** vs the target `.s` (jal/HI16/
  LO16 mask, the `psyq_identify` logic). Own temp dir → parallel-safe → gives agents a real asm-differ loop
  without a shared build. gcc-2.7.2 -O2 compiles each global fn independently, so a standalone match == the
  whole-binary byte-gate for that fn (modulo TU-level extern conflicts — see Deviations).

*Config / source (the harvest):*
- `src/resident/resident.c` — **REAL 1 → 123** matched engine functions (was 100% INCLUDE_ASM at Phase-10 close).
  All hand-written C, each byte-gated. `func_800D00E4` is an honest `INCLUDE_ASM` stub (needs the external
  `jtbl_80113ED8` relocation; its analysis preserved under `#if 0`). 22 stubs remain (documented residuals).
- `config/symbols.resident.txt` — unchanged (count=1, `DsMix`): the harvest matched bytes; meaningful per-fn
  naming beyond `func_*` is a future refinement (the C bodies + the dispatch-table determination document behavior).

*Docs / knowledge base (the determinations + the flywheel):*
- `docs/matching-cookbook.md` **§12** — "Ultracode harvest — parallel-draft + byte-gate at scale" (the full reusable
  pipeline + the retry-wave resilience + the two TU gotchas + the idioms the swarm surfaced). R16 flywheel.
- `docs/memory-map.md` — **script/event system RESOLVED** (compiled-MIPS state/mode dispatch via fn-pointer tables;
  NO bytecode VM — byte-backed by the matched `D_800D3430[D_800B99F0]()`-class dispatchers mirroring the EXE's
  `GameModeDispatch`). Resolves the roadmap's "Script VM instruction set" open question.
- `docs/formats.md` — **§5 SQV driver = semi-custom** (Square wrappers/glue over stock PsyQ libsnd; `DsMix` is a
  custom 2-line wrapper, the 4.7 sig was coincidental) + **§6 Save/memcard format** (`saveHeaderTemplate` layout:
  filename `BASLUS-00726MUSASHI`, SJIS title, the `0x8002Bxxx` handler dispatch table; the `bu00:BASLUS…` libmcrd
  path; deep save-data + the `SaveLoadRoutine` code-match honestly deferred).
- `docs/psyq-worklist.md` — the resident-has-NO-PsyQ-footprint correction (T1, byte-evidence + regen command).
- `docs/effort-map.md` — **§ "Proactively prompt for Ultracode on breadth-heavy stretches"** (R26).
- `docs/gen2-roadmap.md` — **Phase-12 milestone + EXIT criterion #2 AMENDED** (script/event *resolved*, not a
  matched VM; save documented + deferred; 85.6% "substantial").
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase12.md`** (R19 archive). `phase-ends/PhaseEnd_Phase12.md` — this file.

**Local artifacts (gitignored / regenerable):** `.run/drafts{,2,3,4}/*.c` (the workflow drafts), `.run/match/*`
(match_one scratch), `.run/harvest_*.log`, `.run/ram_save*.bin` (the save trace), `build/`, `expected/`, `asm/`.

**Tools/packages installed:** None — the whole phase used the existing Phase-4/6 toolchain + the venv (rabbitizer).

**Verification results (literal) — the milestone proof (clean dual-binary rebuild, all green):**
- **`make clean && make extract BINARY=resident && make build BINARY=resident`** → `build/resident/resident` SHA1
  `8e17e02ff8954d07c979449198f7e1645046b353` (BYTE-IDENTICAL) — **with 123 hand-matched engine functions linked**.
- **`make extract BINARY=main && make build BINARY=main`** → `143dbb89f34491258bbc27810d0a12ec8b43a8dd`
  (BYTE-IDENTICAL) — no regression from any of the phase's work.
- **`make report BINARY=resident`** → **REAL 123 / 0 NON_MATCHING / 146 matchable = 85.62% byte-identical**
  (was 0 REAL / 1.4% at Phase-10 close). `make report BINARY=main` unchanged (54 REAL / 959 LINKED / 50.33%).
- **T1 (byte-survey + Ghidra):** the resident embeds **no PsyQ library object of either version** (4.7 libsnd 1/226
  / libgte 0/509 / libspu 0/134; 4.0 likewise ~0; the few hits are ≤8-ins coincidences); tool sanity 4.0 libsnd
  vs the EXE = 35/163. Ghidra-confirmed (DsMix = custom wrapper; 61 distinct EXE-range `jal` calls).
- **T2 (fingerprint):** resident game-code triple == the EXE's (`gcc-2.7.2-psx -O2 -G0 …` + `maspsx 2.56 --expand-div`),
  opt level -O2 (0 frame-ptr sigs), proven by 2 byte-exact matches across idiom classes.
- **G4 preserved:** 0 NON_MATCHING in either default build. `git status`: only `config/`/`tools/`/`src/`/`docs/`/
  `phase-ends/` tracked; zero ROM-derived/generated bulk staged. **No Ghidra DB change** (the harvest is in committed
  C/asm; pass-4 agents used read-only `get_code`) — R23 no-op (the `db.*.gbf` rename churn is not committed).

**Milestone achieved (confirmed by Drew, gate 2):** the always-resident engine blob is **matched substantively from
C source — REAL 1 → 123/146 (85.62% byte-identical)** with 0 NON_MATCHING and the EXE still `143dbb89…`; the
**script/event system is resolved** (compiled-MIPS dispatch, no bytecode VM — byte-backed), and the **SQV + save
formats are documented**. The amended "substantial + honest deferral" bar (criterion #2) is crushed.

**Next:** **Phase 13 — Representative location overlays (end-to-end + fleet runbook).** Start a fresh session
(effort **Max**, plan mode). The two tools built this phase (`harvest_verify.py` + `match_one.py`) + the cross-binary
dedup report (the 134-overlay queue, all sharing slot `0x80128158` + the now-mostly-matched resident engine they
call) feed directly into the overlay harvest — and **that 134-overlay harvest is the canonical Ultracode breadth
task** (R26): prompt to enable it.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Opener (Phase-11 close + R24) | "link the resident's PsyQ **4.7** libs first" | **VACATED** — T1 byte-survey found **nil** library footprint | The resident is all custom engine code calling the EXE's resident SDK; nothing to link (verified by psyq_identify on 4.0 AND 4.7, + Ghidra). The DetectPsyQ 4.7 was one coincidental DsMix signature. |
| Library-integration tasks (T3/T4/T5 of the plan) | one byte-gated task per resident library | **removed** (P5d, Drew-confirmed) | No footprint → nothing to integrate; progress became REAL (hand-matched), not LINKED. |
| Script VM | "match the interpreter core + first handlers" | **resolved as a written determination — NO bytecode VM** | The `VM_*` symbols are PsyQ libsnd (T1); the matched dispatchers prove "scripting" is compiled-MIPS fn-ptr-table dispatch. P9-honest; criterion #2 amended (Drew-approved). |
| Save/Q#5 | "resolve `SaveLoadRoutine` + match" | **format documented; deep data + the 1139-ins code-match honestly deferred** | The save-data serialization is Gen3-repack territory (not needed for the byte-match); `SaveLoadRoutine` stays the Gen1-precedent hard-defer (P9). The guided save trace confirmed the libmcrd path + directory but the running game churns the data-buffer diff. |
| Harvest method | hand-match / decomp-permuter | **Ultracode: 5 parallel-draft + byte-gate workflow passes** (62+8+9+2+13) + a 20-fn extern-conflict recovery | Drew enabled Ultracode; the swarm + the incorruptible byte-gate produced 79 matches blind + 13 via the match_one iteration loop; the recovery unified ~25 shared-symbol extern types. Far faster than serial. → cookbook §12, R26. |
| Dedup collapse (T3 plan item) | collapse the 6 h_exact / 9 h_norm intra-resident groups | **reassessed → deferred** | All group members got individually matched byte-identical during the harvest → collapse has no recovery/count value (only source-DRY elegance); the §11 share mechanism is already proven; real leverage is Phase-13 overlays. |
| Effort | Max throughout | Max → **Ultracode** (harvest) → Max (the rest) | Breadth-shaped harvest under Ultracode; deep single-thread work (T1 pivot, T2 fingerprint, T4/T5 determinations, this PhaseEnd) at Max. Codified as R26. |

## Commit Message
```
(Phase 12 landed as ~17 per-task/per-batch checkpoint commits commit:0068..commit:0082 + this PhaseEnd.)

feat(phase-12): key engine systems — resident harvest 1.4%->85.6% + script/save/SQV resolved (v1.12.0)

- T1 (byte-survey + Ghidra): the resident has NO PsyQ library footprint -> all custom engine
  code; library-link tasks vacated, progress is REAL not LINKED (R24 premise mooted)
- T2: resident game-code triple == the EXE's (gcc-2.7.2 -O2 + maspsx 2.56), 2 byte-exact proofs
- T3: ULTRACODE harvest -> REAL 1->123/146 (85.62% byte-identical). 5 parallel-draft + byte-gate
  workflow passes (tools/harvest_verify.py) + a match_one.py iteration loop + a 20-fn extern-
  conflict recovery. New reusable tools: harvest_verify.py, match_one.py (-> Phase 13)
- T4: script/event system RESOLVED (compiled-MIPS fn-ptr-table dispatch, NO bytecode VM -
  byte-backed by the matched dispatchers); SQV driver = semi-custom (memory-map + formats.md)
- T5: save/memcard format documented (saveHeaderTemplate + handler table + bu00:BASLUS libmcrd
  path, runtime-confirmed); deep save-data + SaveLoadRoutine code-match honestly deferred (P9)
- both binaries byte-identical (resident 8e17e02f, main 143dbb89); 0 NON_MATCHING linked (G4)
- cookbook §12 (the ultracode harvest pattern), effort-map + R26 (prompt for ultracode on
  breadth), gen2-roadmap milestone/criterion-#2 amended (Drew-approved gate 2)
- rule R26 (ultracode-on-breadth prompting); bumps 1.11.0 -> 1.12.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R26 — Prompt for Ultracode on breadth-heavy stretches during a Max session.** When a breadth-shaped, parallelizable sub-task appears (the *same analysis across many independent items* — bulk function matching / a whole-binary harvest, an EXE- or overlay-fleet-wide audit / survey / dedup), **proactively prompt Drew to enable `/effort ultracode`** rather than grinding it serially or settling for one one-off Workflow. Keep the deep single-thread tasks at **Max** (Ultracode caps depth at xHigh): phase planning, the compiler fingerprint, US-address derivation, non-obvious debugging, PhaseEnd synthesis. The "is this actually breadth, or mine-to-author-with-full-context?" call is itself a Max judgment. Governing doc: `docs/effort-map.md`; memory `effort-prompt-ultracode-on-breadth`. | Drew (2026-06-16): Ultracode + the parallel-draft/byte-gate harvest took the resident **1.4%→85.6% in one session** — Max-serial would have been ~10× slower, and the compounding across passes only happens if Ultracode is actually enabled. (The harvest *pattern* itself is captured as cookbook §12, per the Phase-8/11 precedent that techniques live in the cookbook, not as rules.) |

## PhaseEnd Changelog
**v1.11.0 → v1.12.0 — Phase 12 complete (Gen2 phase 5).** The always-resident engine blob is driven from 100%
INCLUDE_ASM to **REAL 123/146 = 85.62% byte-identical** — all hand-matched engine C, both binaries byte-identical,
0 NON_MATCHING. The phase opened with a byte-finding that reshaped it (Drew-approved): the resident embeds **no PsyQ
library** (T1) and uses **the EXE's compiler** (T2), so the planned 4.7-library-link tasks were vacated and the work
became a pure **REAL harvest**. That harvest was done under **Ultracode** as a reusable pattern (cookbook §12): a
swarm of agents drafts matching C and an **incorruptible byte-gate** (`tools/harvest_verify.py`) accepts only
byte-perfect output — 5 passes (62+8+9+2+13) plus a `tools/match_one.py` per-function iteration loop and a 20-function
extern-conflict recovery. Two long-standing questions were **resolved by the bytes**: there is **no bytecode script
VM** (it is compiled-MIPS state/mode dispatch via function-pointer tables, byte-backed by the matched dispatchers),
and the **save/memcard format** is documented (header + handler table + libmcrd path), with the deep save-data
serialization and `SaveLoadRoutine`'s 1139-ins code-match **honestly deferred** (Gen3 / Gen1-precedent, P9). The
milestone + EXIT criterion #2 were **amended** to "script/event system *resolved*; save documented + deferred"
(Drew-approved). One rule (**R26**, prompt-for-Ultracode-on-breadth); the harvest pattern + two reusable tools feed
directly into Phase 13's 134-overlay harvest.

## Plain-English Recap
The game's permanent "engine" went from essentially nothing decompiled to **86% rebuilt, bit-for-bit, from our own
source code** — in a single session. Two early checks (which Drew approved) saved a lot of wasted effort: the engine
contains none of Sony's prebuilt code, and it's built with the exact same compiler as the main program. With those
settled, we ran a swarm of AI agents that *draft* C, paired with an automatic bit-for-bit referee that rejects
anything wrong — so nothing incorrect can slip in — and looped it five times, each pass smarter than the last (the
final one let each agent test-compile and self-correct). Along the way we settled two long-standing mysteries with
hard evidence: the game has **no script "virtual machine"** — its scripting is ordinary compiled code steered by
lookup tables, which we proved by rebuilding the steering functions themselves; and we mapped the **save-file
header** (the memory-card name, the on-screen "BRAVE FENCER MUSASHI" title, and the table of save/load handlers).
The handful of functions left are the genuinely compiler-stubborn cases, documented exactly how to finish. The
biggest lasting win is the *method* — swarm-of-agents-with-a-bit-for-bit-referee — which we wrote down as a permanent
recipe and two reusable tools, because the next phase (the game's 134 levels) is the same shape and will benefit
enormously. Both the engine and the main program still rebuild perfectly.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase12.md` (R19). The Phase-12 work is committed
(~17 checkpoints `commit:0068`..`commit:0082` + this PhaseEnd commit, which also lands the gen2-roadmap amendment); **Drew
pushes** (R6). Gen2 continues — do **NOT** start Phase 13 here. Start a **fresh session** (effort **Max**, plan mode)
for **Phase 13 — Representative location overlays**; the 134-overlay harvest is the canonical Ultracode breadth task
(R26 — prompt to enable it). Keep this file forever.
