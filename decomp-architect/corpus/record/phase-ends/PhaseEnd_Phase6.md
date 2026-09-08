# PhaseEnd — Phase 6: Compiler fingerprint + first matched functions
**Date:** 2026-06-14 · **Project Version:** 1.6.0 · **Phase Status:** Complete (substantively; the LZSS milestone gate is carried to Phase 7 per Drew — it uniquely needs the jump-table-in-rodata workflow)

## Build Log

**Files created/changed and complete — do not recreate:**
- `config/splat.us.exe.yaml` — text subsegment flipped `[0x800, asm, 800]` → `[0x800, c, 800]`. splat now emits `src/800.c` (file-scope `INCLUDE_ASM` stubs) + per-function `asm/nonmatchings/800/*.s`. Consumed by `make extract`.
- `include/common.h` — **new, committed** prelude (`#include "include_asm.h"` + `u8..f32` typedefs). Every `src/*.c` includes it; splat references but does NOT generate it.
- `Makefile` — added: `MAPFILE` + `-Map` on the `ld` line (asm-differ symbol lookup); `C_SRCS`; `OBJS` excludes `asm/nonmatchings/*` (those are textually `.include`d by the .c); the **`build/src/%.o: src/%.c` c-rule** (cpp→cc1→maspsx→as); `CPPFLAGS`/`CC1FLAGS` (pinned §5.4 flags); **`MASPSX_FLAGS := --expand-div`** (pinned). `check-env` untouched.
- `diff_settings.py` — **new**, repo root. asm-differ config: arch `mipsel` (R3000), object mode vs `expected/`, gnu map, `mipsel-linux-gnu-objdump`.
- `tools/decompile.py` — **new**, m2c wrapper (fn → `asm/nonmatchings/**/<fn>.s` → m2c `mipsel-gcc-c` scaffold).
- `tools/permuter/compile.sh` + `tools/permuter/bin/mips-linux-gnu-objdump` — **new, committed** decomp-permuter harness (build-faithful compile command + the objdump shim the permuter's hardcoded `mips-` name needs). Per-function setup recipe in cookbook §3.
- `docs/matching-cookbook.md` — **new**, the evolvable idiom catalog (I1–I4 idioms, T1–T3 techniques, §3 permuter recipe + `-j` sweet-spot, §4 flag gotchas, §5 hard-residual classes). The compounding knowledge base.
- `requirements-python.txt` — **new, committed** venv freeze (the Phase-4-deferred freeze). Notably **`pycparser` held <3.0** (3.0 removed `plyparser`, breaking the pinned permuter — hard-won). `pip install -r` reproduces the venv.
- `docs/SETUP.md` — **§6.6** (the matching loop + NON_MATCHING guard convention) and **§5.4 PINNED** block (the compiler triple, G8).
- `CLAUDE.md` — **step 5** in the Session Start Protocol: matching phases read the cookbook + §5.4, and *evolve* the cookbook + tooling (the flywheel).
- `src/800.c` — **the matched-C record (committed):** 14 real functions in C (`func_80018F20` byte-clamp + 13 accessors), 2 `#ifdef NON_MATCHING`-guarded near-misses (`func_80015A74`, `func_80016714`), and 14 splat-auto empty no-ops (`void f(void){}`).
- `phase-ends/PhaseEnd_Phase6.md` — this file. `phase-ends/CURRENT_PHASE.md` — **absorbed into this file and deleted** (P8).

**Local artifacts (gitignored / regenerable — do NOT recreate):**
- `asm/nonmatchings/800/*.s` (2054 per-function disasm) + `include/*.inc` + `undefined_*_auto.txt` + `build/` + `expected/` — `make extract`/`make build`/`make expected` regenerate them.
- `.run/permuter/func_80015A74/` — permuter scratch (recipe in cookbook §3; the C also lives guarded in `src/800.c`).
- `.venv/` — now reproducible from `requirements-python.txt`.
- **Memory (outside repo):** `matching-cookbook` (the flywheel pointer) + MEMORY.md index line.

**Tools/packages installed (this phase):** venv pip — asm-differ runtime (`watchdog 6.0.0`, `Levenshtein 0.27.3`+`RapidFuzz`, `cxxfilt 0.3.0`; `colorama` already present) and decomp-permuter (`pycparser 2.23` **(<3.0 pin)**, `toml 0.10.2`, `PyNaCl 1.6.2`+`cffi`). All pinned in `requirements-python.txt`.

**Verification results (literal):**
- **`make clean && make extract && make build && make check` → `build/us/SLUS_007.26`, SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd` == original (BYTE-IDENTICAL)** — through the cpp→cc1→maspsx→as c-path, both at 100% INCLUDE_ASM (the flip) and with 14 real C functions linked.
- **Compiler triple PINNED + confirmed (G8):** `func_80018F20` byte-exact (asm-differ **score 0** — the `sltiu` range-check probe); `func_80015A74` division idioms exact (the `--expand-div` find — `divu`+`break` + `multu 0xCCCCCCCD`); `func_80016714` every instruction identical (phantom-frame residual). psx≈cdk and 2.56≈2.67 are byte-equivalent on non-discriminating functions.
- **14 real functions matched (asm-differ score 0):** `func_80018F20` + 13 accessors (`func_80019198/378/388/398/3A8`, `func_8001AA78/AA88`, `func_800168B4`, `func_80019018`, `func_8001B22C/B374/B384/B85C`). **+14 splat-auto empty no-ops** = 28 byte-matched total.
- **decomp-permuter harness validated:** `base score = 60` on `func_80015A74` (== asm-differ); `-j 8` ≈ 6600 candidates/30 s (parallel works); `-j 30` oversubscribes → exit 144 (sweet spot ~8–16).
- **2 instruction-identical near-misses** guarded NON_MATCHING (`func_80015A74` hoisted-invariant scheduling; `func_80016714` phantom empty stack frame) — decomp-permuter candidates (cookbook §5).
- **LZSS spike (read-only recon):** `LzssDecodeSector` needs gcc's switch jump table placed byte-exact at 0x80072A38, inside a **mixed blob of 102 jump tables + 161 other data labels** → the jump-table-in-rodata workflow → **Phase 7 opener** (unlocks ~102 switch-functions).
- `git status`: only `config/`, `Makefile`, `src/`, `include/common.h`, `diff_settings.py`, `tools/decompile.py`, `tools/permuter/`, `docs/`, `requirements-python.txt`, `CLAUDE.md` tracked; **zero ROM-derived/generated bulk staged**; all tooling committable; deps frozen.

**Milestone achieved:** The matching loop is **proven and industrialized** — the asm→c flip rebuilds byte-identically, the compiler triple is **pinned by evidence**, and **14 real functions (+14 splat-auto empties) compile to byte-identical machine code** (asm-differ score 0; `make check` BYTE-IDENTICAL). The roadmap's LZSS gate is deferred to Phase 7 (Drew's framing — LZSS uniquely needs the jump-table-in-rodata workflow).

**Next:** Phase 7 — **open in plan mode with a fresh context window.** Start with the **jump-table-in-rodata workflow → LZSS** (first table) → the other ~101 switch-functions; then matching-loop-at-scale (difficulty/duplicate/progress reports, the auto-match harvester) + the Gen1 close-out (≥25 matched, overlay map emulator-proven).

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| LZSS milestone gate | match in Phase 6 | **deferred to Phase 7** | needs the jump-table-in-rodata workflow (roadmap-scoped Phase 7); Drew's milestone-framing decision |
| Task D "≥3 score-0 probes" | 3 score-0 probes | 1 score-0 probe + 2 instruction-identical near-misses + 13 tiny-leaf score-0 matches | the medium idiom-rich probes hit gcc byte-exactness quirks (scheduling, phantom frame); the pin is established by instruction-level identity across 3 idiom classes |
| Task F approach | match probes + LZSS | **pivot to tiny trivial leaves** (185 available) | medium probes quirk-prone; tiny leaves one-shot from a pattern (the harvester triage, live) |
| Empty functions | (n/a) | splat auto-emitted empty C for 14 no-ops → free byte-matches | splat c-mode behavior (discovered) |
| Execution order | A→B→C→D… (checklist) | harness (C) **before** the ladder (D) | the ladder is *scored by* asm-differ — the harness is a prerequisite (per the approved plan) |
| `--expand-div` | (not anticipated) | **pinned globally** | the division idiom requires it (bare `divu` never matches); key fingerprint find |
| Tooling (Task T / #9) | not in the original plan | **added mid-phase (Drew-directed):** permuter harness built+validated; **m2c `--context` seed deferred to Phase 7** | Drew directive; the flywheel's tier-2 |
| venv requirements freeze | Phase-4-deferred | **done at Phase-6 close** (`requirements-python.txt`) | Drew flagged the dep-loss risk; the planned time |

## Commit Message
```
feat(phase-6): compiler pinned + matching loop proven (14 matches) — LZSS to Phase 7

- splat.us.exe.yaml: text subseg asm->c (INCLUDE_ASM scaffold); include/common.h
  (committed prelude); Makefile c-rule cpp->cc1->maspsx->as + -Map
- PIN (G8): gcc-2.7.2-psx -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker
  + maspsx --aspsx-version=2.56 --expand-div; byte-exact on func_80018F20 +
  instruction-identical across 3 idiom classes; --expand-div REQUIRED for div/rem
  (SETUP.md §5.4 PINNED, Makefile MASPSX_FLAGS)
- harness: diff_settings.py (asm-differ mipsel object mode), tools/decompile.py
  (m2c wrapper), tools/permuter/ (decomp-permuter harness + objdump shim), expected/
- 14 real functions matched (asm-differ score 0): func_80018F20 + 13 accessors;
  +14 splat-auto empty no-ops; make check BYTE-IDENTICAL throughout
- 2 instruction-identical near-misses guarded NON_MATCHING (func_80015A74 scheduling,
  func_80016714 phantom frame) -> decomp-permuter candidates
- flywheel: docs/matching-cookbook.md, memory + CLAUDE.md step 5 (consult+evolve), R16
- requirements-python.txt: venv freeze (pycparser<3.0 pinned — permuter needs plyparser)
- LZSS spike: needs jump-table-in-rodata workflow (102 tables, mixed blob) -> Phase 7
- venv: asm-differ + permuter deps installed
- bumps project version 1.5.0 -> 1.6.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R16 — The matching automation flywheel.** Consult the knowledge base (`docs/matching-cookbook.md` + the pinned triple §5.4 + the decomp-permuter harness + the m2c `--context`) **before** each match, and **after** each match — especially a hard-won near-miss ground to byte-perfect — feed the GENERALIZABLE lesson back into **both** the cookbook (the idiom/technique) **and** the tooling (a permuter `PERM_*` recipe / weight, an m2c context entry). Don't over-encode one-offs; the target is the *average* function trending to one-shot + a shrinking hard tail, not literal zero-intervention. Wired into the `matching-cookbook` memory + CLAUDE.md step 5. | Drew-directed (2026-06-14). The ~99.9%-autonomous matching model only scales if each match makes the next one cheaper; this makes "consult + evolve" a standing obligation, not a one-off. |

## PhaseEnd Changelog
**v1.5.0 → v1.6.0** — Phase 6 complete (substantively; the **LZSS gate is carried to Phase 7**, which it fits better — it uniquely needs the jump-table-in-rodata workflow). The **matching loop is proven and industrialized**: the asm→c flip rebuilds byte-identically; the **compiler triple is PINNED by evidence** (`gcc-2.7.2-psx -O2 -G0 …` + `maspsx --aspsx-version=2.56 --expand-div`), with `--expand-div` the key discovery; the full harness is wired (asm-differ object mode + `tools/decompile.py` + the decomp-permuter harness + the `expected/` baseline); **14 real functions match at asm-differ score 0** (a byte-clamp + 13 accessors) plus 14 splat-auto empties, `make check` BYTE-IDENTICAL throughout. The **tiny-leaf harvest validated the harvester triage** (easy=auto, medium=permuter, hard=defer) — there are 185 tiny leaves and ~102 switch-functions waiting. A **knowledge flywheel** is now standing (cookbook + memory + CLAUDE.md step 5 + R16), and the venv is reproducible (`requirements-python.txt`, with the hard-won `pycparser<3.0` pin). Two instruction-identical near-misses are guarded as permuter candidates. The LZSS recon scoped Phase 7's opener.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` absorbed and removed. **Drew commits AND pushes** this PhaseEnd plus the whole Phase-6 change set (R6/R8 — one commit lands: `config/`, `Makefile`, `src/800.c`, `include/common.h`, `diff_settings.py`, `tools/decompile.py`, `tools/permuter/`, `docs/` (SETUP §5.4/§6.6 + matching-cookbook.md), `requirements-python.txt`, `CLAUDE.md`, `PhaseEnd_Phase6.md`). Start a **fresh session, in plan mode, for Phase 7 — opening with the jump-table-in-rodata workflow → LZSS**. Keep this file forever.
