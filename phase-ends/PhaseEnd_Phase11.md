# PhaseEnd — Phase 11: Cross-binary dedup pipeline
**Date:** 2026-06-16 · **Project Version:** 1.11.0 · **Phase Status:** Complete · **Generation:** Gen2 (4th phase)

> Gen2 phase 4 of the arc (8→9→10→**11**→{12,13}→14). The granular per-task trail (the byte-finding that
> reshaped the milestone, the sig_image boundary/normalization iterations, the overlay-discovery dead-ends)
> is preserved on-demand at **`phase-ends/logs/Phase11.md`** (R19 — NOT auto-loaded; consult only when
> researching a mechanism). Owner decisions (2026-06-16): proving ground = **"report + machinery; defer
> collapse"**; PsyQ 4.7 = **sha-record only** (linking is Phase 12).

## Build Log

**Files created/changed and complete — do not recreate:**

*Cross-binary dedup pipeline (new tooling):*
- `tools/sig_image.py` — **new.** Ghidra-FREE per-function signer for a flat image (overlay `0.4.dec` / resident
  `1.1`), using **rabbitizer** (already in the venv). Emits JSONL field-identical to `DumpFunctionSignatures.java`.
  `h_exact` = SHA1 of raw instruction bytes (format-independent — the cross-tool workhorse). `h_norm`/`h_seq` =
  self-consistent (D2). Boundary detection: seeded (`--seeds`), or `--bootstrap` = linear partition (split code at
  the first `jr $ra`+delay at/after all forward targets) bounded by `detect_code_end` (first run of ≥3 invalid
  instrs = code→data transition). Consumed by `make sig-overlays` + `dup_report --cross`.
- `tools/dedup_integrate.py` — **new.** Byte-honesty VALIDATOR for `config/dedup.us.yaml` (`--check`): fail-closed
  if a registered share's member sig-hash drifts from the recorded `hash`. NOT a `psyq_integrate` fork (D1).
- `config/dedup.us.yaml` — **new, committed.** Cross-binary code-share registry (`group → {id, tier, hash,
  source, func, members:[{binary, vram, name}]}`). Holds the Phase-11 proof group `I0_clearTbl40`.
- `src/shared/clearTbl40.h` — **new, committed.** The shared body (`CLEAR_TBL40` macro) for the byte-identical
  pair `func_80037004`/`func_80037334`, instantiated at both sites in `src/800.c` (one source → two vrams).
- `tools/dup_report.py` — **modified.** Added `--cross`: ingest all `BINARIES` sigs + every `.run/sig.ov_*.jsonl`,
  bucket by `h_exact` then `h_norm` across binaries, split cross-binary (the Phase-12/13 work queue) vs intra,
  rank by collapsible bytes `(count−1)×nins×4`, top-200 capped + totals → `docs/duplicates.cross.md`. Per-binary
  path byte-stable.
- `tools/progress.py` — **modified.** Counts dedup-shared members (from `dedup.us.yaml`) as REAL (the macro form
  isn't a parseable function def) — honest measurement (P9).
- `Makefile` — **modified.** `make report` (gated `BINARY=main`) runs `dup_report --cross` + `dedup_integrate
  --check` (the byte-honesty gate, last line → fail-closed). New `make sig-overlays` (sign all 134 overlays).
- `src/800.c` — **modified.** The two `INCLUDE_ASM` stubs → `CLEAR_TBL40(...)` + the `#include "shared/clearTbl40.h"`.

*Reports / docs (committed):*
- `docs/duplicates.cross.md` — **new, committed.** The cross-binary work queue: 9366 h_exact + 8957 h_norm
  cross-binary groups (28.5 MB / 38.3 MB collapsible), ranked by leverage.
- `docs/progress.md` / `docs/difficulty.md` — regenerated (REAL 52→54; the 2 dedup-shared fns left the queue).
- `tools/psyq/CHECKSUMS.sha256` — **new, committed.** Integrity record for `psyq-4.7-converted.zip` (R20) +
  Phase-12 provenance (the resident is 4.7 → link from `conv47/`).
- `docs/matching-cookbook.md` — **§11** (the cross-binary dedup & code-share workflow; R16 flywheel).
- `docs/SETUP.md` — **§6.8** (dedup command crib) + tooling-inventory rows (R21).
- `docs/psyq-worklist.md` — resident-is-4.7 Phase-12 linking note (R24).
- `README.md` — Gen2 status (resident = 2nd byte-identical binary; cross-binary dedup live).
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase11.md`** (R19 archive). `phase-ends/PhaseEnd_Phase11.md` — this file.

**Local artifacts (gitignored / regenerable — a fresh clone redoes them):** `.run/sig.ov_*.jsonl` (134 overlay
sigs — `make sig-overlays`, ~27 s), `.run/sig.resident_image.jsonl` (the T4/T5 validation sig), `build/`,
`expected/`, `asm/`, generated `include/` macros.

**Tools/packages installed:** None — rabbitizer (1.16.2) and PyYAML (6.0.3) were already in the venv as
splat64 dependencies (Phase 4); the whole phase used the existing Phase-4/6 toolchain.

**Verification results (literal) — the milestone proof (clean dual-binary rebuild, all green):**
- **(1) `make clean && make extract BINARY=main && make build BINARY=main`** → `build/us/SLUS_007.26` SHA1
  `143dbb89f34491258bbc27810d0a12ec8b43a8dd` (BYTE-IDENTICAL) — WITH the `I0` shared-C body linked.
- **(2) `make extract BINARY=resident && make build BINARY=resident`** → `build/resident/resident` SHA1
  `8e17e02ff8954d07c979449198f7e1645046b353` (BYTE-IDENTICAL) — no regression.
- **(3) T3 dual invariant:** the EXE is `143dbb89…` WITH the shared-C match AND WITH the two sites reverted to
  `INCLUDE_ASM` stubs (both clean rebuilds) — the share is byte-honest and degrades gracefully.
- **(4) `make report`** → `docs/duplicates.cross.md`: **h_exact 9366 cross-binary groups / 28,577,800 collapsible
  bytes**; h_norm 8957 / 38,288,368; top group = a 770-instruction fn byte-identical in **all 134** overlays.
  `dedup-check`: 1 validated, **0 failed**; negative tests (corrupt hash / wrong vram) fail-closed (exit 1).
- **(5) sig_image validated vs the resident Ghidra oracle:** `h_exact` 140/140 = **100% on the contiguous/non-GTE
  subset, zero UNEXPLAINED** (98.6% overall; 2 misses = non-contiguous bodies, D5). `h_exact` equivalence classes
  6/6 == Ghidra; `h_norm` reproduces 7/9 Ghidra structural groups (disagreements benign — masked-field only).
- **(6)** `SC01/005 ≡ 006` (byte-identical overlays) sign identically (same function set, all `h_exact` equal).
- **(7) REAL 52→54** (2 dedup-shared); **7 NON_MATCHING**, all `#ifdef`-guarded (0 linked in the default build, G4).
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`phase-ends/` tracked; **zero ROM-derived/generated bulk
  staged** (`.run/`, `build/`, `asm/` gitignored). No Ghidra DB change this phase (pure tooling — R23 no-op).

**Milestone achieved:** `make report` emits cross-binary duplicate groups spanning ≥2 binaries (9366 h_exact
groups across 136 binaries, up to all 134 overlays per group), AND a single shared C body fills two addresses
byte-gated with the EXE (`143dbb89…`) byte-identical with and without it — the cross-binary dedup pipeline is
built and proven on the byte-verified EXE↔resident pair, with the 134-overlay fleet signed and ranked as the
Phase-12/13 work queue. Confirmed by Drew (gate 2).

**Next:** **Phase 12 — Key engine systems (script VM, save/Q#5, sound SQV).** Start by **linking the resident's
PsyQ 4.7 library code** (libsnd/libgte/libspu from `tools/psyq/conv47/`, sha-recorded; R24) via the proven
`psyq_identify → psyq_link_region → psyq_integrate` pipeline pointed at the resident (the Phase-9 `--vram-base`/
`--exe` params make it binary-agnostic), then RE + match the script-VM core, the save/Q#5 path (`SaveLoadRoutine`),
and the SQV driver — each engine match auto-credited across the 134 overlays via `docs/duplicates.cross.md`.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Milestone shape | roadmap: "one C body → both EXE and resident green" | **report + machinery; defer collapse** (owner decision, plan time) | The bytes showed EXE↔resident share NOTHING collapsible (h_exact=0; 4.0 vs 4.7 SDK + loader-vs-engine roles). Real cross-binary sharing is overlay↔overlay (proven: 9366 groups). The literal EXE↔resident collapse is infeasible; first true cross-binary collapse → Phase 13 (built overlay). |
| **D1** dedup mechanism | "fork `psyq_integrate.py` — .ld interpose" | **source-level macro share + per-binary `make check` gate** | `psyq_integrate`'s object-swap works only for separate library SUBSEGMENT stubs; game-code fns are interior to one object per binary → the linker can't excise them. Source-level share (macro in `src/shared/`) is the byte-correct mechanism. `dedup_integrate.py` is a byte-honesty validator, not an interpose engine. Simpler. (cookbook §11) |
| **D2** sig_image `h_norm` | "Ghidra-byte-exact normToken replica, ≥98% match" | **self-consistent normalization** (scope-guard, pre-approved) | Byte-reality made byte-exact low-value (EXE↔resident share nothing; overlays share via `h_exact` at the same vram, and CALL not embed the resident). `h_exact` is the format-independent cross-tool workhorse; every `h_norm` candidate is byte-gated. Full replica = documented future refinement. |
| Overlay function discovery | (not specified) | **linear partition + validity-based `detect_code_end`** (call-graph BFS dead-ended) | Overlays dispatch most code via function-pointer tables, not `jal`, so BFS found ~2 fns; linear partition recovers the whole contiguous-code prefix. Jump-table-only fns + non-contiguous bodies (D5) are a documented coverage gap until splat configs (Phase 13). |
| 4.7 `.LIB` fetch | "fetch + sha-verify from archive.org" (Phase-10 carried) | **already present + git-tracked** → reduced to a sha-record + provenance note | The converted 4.7 SDK (`conv47/` 55 objs + the zip) was already committed (R20 backup satisfied). Fetch was moot; integrity recorded in `tools/psyq/CHECKSUMS.sha256`. |
| `progress.py` accounting | (not anticipated) | taught to count dedup-shared members as REAL (registry source) | The `CLEAR_TBL40(name)` macro form isn't a parseable function def → the 2 matched fns would have vanished from the count; the registry restores honest measurement (P9). |

## Commit Message
```
(Phase 11 landed as 7 per-task checkpoint commits commit:0060..commit:0066 + this PhaseEnd.)

feat(phase-11): cross-binary dedup pipeline — one match unlocks many (v1.11.0)

- T1 (commit:0060): dup_report --cross -> docs/duplicates.cross.md (multi-binary bucketing,
  cross/intra split, collapsible-bytes ranking); per-binary reports byte-stable
- T2 (commit:0061): config/dedup.us.yaml registry + tools/dedup_integrate.py byte-honesty
  validator (fail-closed on sig-hash drift); make report gate. DEVIATION D1: game-code
  dedup is SOURCE-LEVEL (shared macro body), not a psyq_integrate object-swap (fns are
  interior to one object/binary); the byte-gate is per-binary make check
- T3 (commit:0062): intra-binary collapse PROOF — src/shared/clearTbl40.h CLEAR_TBL40 fills
  func_80037004 + func_80037334 from one body; EXE 143dbb89 WITH the share AND WITHOUT
  (stub fallback); negative gate tests fail-closed; REAL 52->54
- T4 (commit:0063): tools/sig_image.py Ghidra-free h_exact signer (raw-byte SHA1) + boundary
  detection; validated 100% on the resident contiguous/non-GTE set, 0 UNEXPLAINED
- T5 (commit:0064): sig_image self-consistent h_norm + h_seq (DEVIATION D2 — scope-guard, not
  a Ghidra-byte-exact normToken replica; byte-gate is the truth)
- T6 (commit:0065): make sig-overlays signs all 134 overlays (linear partition + code-end
  detection; BFS dead-ends on function-pointer dispatch). Cross-report spans 136 binaries:
  9366 h_exact groups / 28.5 MB collapsible; one 770-ins fn byte-identical in all 134
- T7 (commit:0066): tools/psyq/CHECKSUMS.sha256 (4.7, R20/R24); cookbook §11; SETUP §6.8 +
  inventory; psyq-worklist + README
- MILESTONE: clean dual-binary rebuild green (main 143dbb89, resident 8e17e02f);
  cross-report spans >=2 binaries; one shared body byte-gated in both states; 0 NON_MATCHING
  linked (G4). No new rules (deviations captured as cookbook §11 techniques)
- worklog archived -> phase-ends/logs/Phase11.md (R19); bumps 1.10.0 -> 1.11.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **None** | Phase 11's findings are *techniques*, captured in `docs/matching-cookbook.md` §11 (the source-level share mechanism / byte-gate / sig_image notes — D1, D2) — the Phase-8 §9.6 precedent of recording techniques in the cookbook, not as governance rules. The existing **G3/P9** byte-gate discipline (h_exact risk-free, h_norm candidate-only / link-confirmed) and **R24** per-binary toolchain provenance already cover the new ground. |

## PhaseEnd Changelog
**v1.10.0 → v1.11.0 — Phase 11 complete (Gen2 phase 4).** The **cross-binary deduplication + code-share
pipeline** is built and proven. New Ghidra-free tooling — **`sig_image.py`** (rabbitizer signer; `h_exact`
byte-matches the Ghidra dumper, validated 100% on the resident contiguous set), **`dup_report --cross`**
(`docs/duplicates.cross.md`), **`dedup_integrate.py`** (the byte-honesty validator), **`config/dedup.us.yaml`** +
**`src/shared/`** (the source-level share registry + bodies), **`make sig-overlays`**. A byte-finding reshaped
the milestone (owner-approved): the EXE (4.0) and resident (4.7) share **no** collapsible code, so the machinery
was proven on a real **intra-binary** `h_exact` collapse (`func_80037004`≡`func_80037334`, one body → two
addresses, byte-gated, dual invariant) while the cross-binary **report** was proven by signing all **134
overlays** — which share an enormous amount of code: **9366 h_exact cross-binary groups / 28.5 MB collapsible**,
one 770-instruction engine function byte-identical in **all 134** overlays. This is the Phase-12/13 work queue
("one match unlocks many", quantified). Two deviations (D1 source-level share not an object-swap; D2
self-consistent `h_norm` not a Ghidra-byte-exact replica), both byte-correct and captured as cookbook §11
techniques — **no new rules**. The resident's PsyQ **4.7** provenance is sha-recorded (R24) for Phase 12. Both
binaries rebuild byte-identical; 0 NON_MATCHING linked (G4).

## Plain-English Recap
We taught our build system a new trick: spotting when the *same* piece of game code shows up in more than one
part of the game, so we only have to figure it out once and reuse it everywhere. We proved the idea by rebuilding
two copies of one function from a single shared source — and both the main program and the engine still rebuild
perfectly, bit-for-bit. Then we fingerprinted all **134 location "levels"** (without needing the slow analysis
tool) and discovered they share a huge amount of identical code — about **28 megabytes**, with one core engine
function appearing **byte-for-byte in all 134 levels**. That means most functions we reverse-engineer from here
on will complete dozens of levels at once — exactly the leverage the next phases need. One surprise the bytes
settled early: the main program and the engine chunk share essentially *nothing* (they were built with different
toolkits for different jobs), so the real payoff is in how much the levels share with *each other*. Nothing we
already had broke, and we now have a ranked to-do list of the highest-value functions to match next.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase11.md` (R19). The Phase-11 work is
committed (7 checkpoints `commit:0060`..`commit:0066` + this PhaseEnd commit); **Drew pushes** (R6). Gen2 continues — do
**NOT** start Phase 12 here. Start a **fresh session** (effort **Max**, plan mode) for **Phase 12 — Key engine
systems**, opening with the resident's PsyQ 4.7 library linking. Keep this file forever.
