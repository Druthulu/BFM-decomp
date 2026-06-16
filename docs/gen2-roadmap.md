# Gen2 Roadmap — Brave Fencer Musashi Decompilation: *Overlays & Engine at Scale*

> **Status:** APPROVED 2026-06-15 (owner-approved plan; Drew). Uncommitted pending Drew's commit/push (R6/R8).
> **Rev 2026-06-15:** Phase 14 changed to the **two-repo model** (private master + curated public mirror, replacing the in-place history scrub); a **Backup & disaster-recovery** policy section added; **R8 commit cadence loosened** for Gen2 (per-session/finer commits+push).
> **Numbering:** Gen2 continues the global phase count — **Phases 8–15** (Gen1 was 1–7).
> **Gen2 EXIT** is declared at **Phase 14 (public flip)**; **Phase 15 (overlay long-tail) is open-ended and does NOT gate exit.**
> **This file is the Gen2 equivalent of PROJECT_CONTEXT's "Build Roadmap — Gen1"** and lives in the evolvable `docs/` layer. It does **not** replace per-phase planning — **every phase still gets its own Phase Start plan + approval gate (P3) and its own `CURRENT_PHASE.md`.** PROJECT_CONTEXT itself is permanent/static (P1) and is never edited.

---

## Context — why this plan, and what it must deliver

Gen1 (Foundation & EXE) is **complete and Gen1-exit confirmed** (PhaseEnd_Phase7, v1.7.0): the main EXE `SLUS_007.26` rebuilds **byte-for-byte from C source**, the compiler triple is pinned by evidence, the matching loop is industrialized, and the file-loader/overlay map is emulator-proven. The project now turns to **Gen2 — Overlays & engine at scale**, whose scope (PROJECT_CONTEXT) is: splat configs for the resident blob + location overlays; engine-systems RE (script VM, entities, render, sound); a dedup pipeline; a progress dashboard; and going public (AGPL-3.0, CI, frogress/decomp.dev).

Almost all of BFM's game code lives **outside** the 404 KiB EXE — in a resident engine blob plus ~134 LZSS-compressed location overlays streamed from the `.CD` files. Gen2's central problem is therefore **scale**: turning a single-binary matching machine into a multi-binary one, and exploiting the fact that an overlay-heavy game shares enormous amounts of code across binaries ("one match unlocks many").

**Owner decisions locked for this plan (2026-06-15):**
1. **Finish the EXE first** — link the remaining PsyQ SDK libraries byte-identical and harvest remaining easy EXE matches *with the already-proven single-binary tools*, before any overlay work.
2. **Public flip is the LATE capstone, via a separate curated public repo** — AGPL-3.0, no-ROM CI, the rom→decoder regeneration tool, and frogress/decomp.dev all happen as the **final** substantive Gen2 phase, after substantial matching. **This private repo stays the untouched master/backup;** the public version is a freshly-created, allowlisted mirror (no destructive in-place history scrub). *(Refined 2026-06-15 — two-repo model.)*
3. **Substantial exit, not exhaustive** — Gen2 exits when the resident engine blob + key engine systems (script VM, save/Q#5, sound) are matched, cross-binary dedup is live, a *representative* set of location overlays is matched end-to-end, and the project is public with a dashboard. The ~134-overlay long-tail is a **defined, open-ended ongoing phase — not a gate.**

**Intended outcome:** a public, multi-binary, dashboard-tracked decomp where the EXE + resident engine + key systems + a representative overlay set are byte-matched, cross-binary dedup makes each new overlay cheap, and the long-tail can be ground down (by maintainer or contributors) without ever stranding the project.

---

## Verified starting state (checked against the bytes during planning — R14)

- **EXE byte-identical from source**, reproducibly: `make clean && make extract && make build && make check` → SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd`. **43 REAL matches + 7 NON_MATCHING drafts.** Compiler PINNED: `gcc-2.7.2-psx -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker` + `maspsx --aspsx-version=2.56 --expand-div`; per-module **-O0** mechanism proven (`src/boot.c`, `21F0A003` frame-pointer signature).
- **PsyQ libraries linked byte-identical** from real PsyQ 4.0 USA objects: **libcd (18 objs) + libgs (31 objs / 6 blocks)**, byte-identical with *and* without the SDK objects (fresh-clone stub fallback). Pipeline proven: `psyq_lib_split → psyq_build_libs → psyq_identify → psyq_link[_lib] → psyq_link_region → psyq_integrate` (+ `ld_interleave.py`, `make_libgs.sh`). `psyq_integrate` already accepts a placement-window arg (GS_106 precedent).
- **Overlays are position-locked** (live-proven, Phase 3 T6b): **resident engine blob @ `0x800CEDF8`** (`MAIN.CD/FILE_010/1.1`, **type-1 uncompressed**, 365,404 B; 18,788-byte exact prefix sha1-EQUAL, 92.98% identical) and **every location overlay loads to the same slot `0x80128158`** (`SC01/FILE_077/0.4.dec`, type-4 LZSS, 731,607 B; 389,400-byte exact prefix sha1-EQUAL, 98.59% identical; first divergence is a loader-filled pointer, not relocation). A **per-location data/entity block sits *below* `0x80128158`** — separate from the code blob (note for overlay splat config).
- **~134 location-overlay payloads on disk** (`extracted/retail/SCxx.CD.dir/FILE_nnn.dir/0.4.dec`; 138 type-4 `.dec` total). Verification happens at the **decompressed layer** (repack/recompression is a Gen3 problem — standing decision).
- **All tooling is single-binary today** — `Makefile` (`EXE`, `OUT_DIR := build/us`), `tools/{progress,difficulty,dup_report}.py`, and `tools/psyq_*.py` hardcode the EXE path / `0x8000F800` file-base. `dup_report.py` is **intra-binary only** — cross-binary dedup is brand-new work.
- **Cross-binary substrate already exists**: `tools/match_protos.py` + `tools/ghidra_scripts/DumpFunctionSignatures.java` emit a 3-tier (`h_exact`/`h_norm`/`h_seq`) cross-program fingerprint (used in the Phase-3.5 proto spike) — never yet pointed at overlays.
- **Engine RE maturity:** loader cluster fully mapped (6 matched + 5 NON_MATCHING; `SaveLoadRoutine`/Q#5 deferred). Game-mode dispatch matched. Script VM / entity / sound (SQV) / save-format are **mostly greenfield and live in the resident blob**.
- **Public-flip prerequisites unbuilt:** no LICENSE, no CI, no history scrub; committed ROM-derived content includes `extracted/retail/SLUS_007.26` and `dumps/*.bin` (H1 relaxed-while-private; compliance = scrub + rom→decoder tool before public).

> **R14 caveat on approximate figures:** the per-`.CD` type-4 distribution, the exact remaining-PsyQ-library symbol counts, and the boss-HP addresses surfaced by reconnaissance are *directional* (sub-agent claims, not all in the durable record). They do not gate any phase; exact denominators are produced by the Phase-11 cross-binary report and the Phase-13/15 overlay worklist. Load-bearing facts above are byte-verified.

---

## Design principles

1. **Never let an unproven tool meet an unproven target.** Each new pipeline is proven against an already-byte-verified artifact before it touches greenfield: the multi-binary refactor (Phase 9) is validated by the EXE rebuilding *byte-identical*; cross-binary dedup (Phase 11) is proven on the byte-verified EXE↔resident pair; the overlay recipe (Phase 13) is proven on the already-byte-proven `SC01/077`. This invariant is the spine of the ordering.
2. **Leverage-first within the de-risk constraint.** Because every overlay shares slot `0x80128158` and chains into the *same* resident engine, code is shared across binaries at the function/sub-block level. So: stand up the resident engine (most-shared code) early, build dedup *before* the matching waves, and match engine systems *before* individual overlays — so each engine match is auto-credited across the overlay fleet.
3. **Bytes are the only truth (G3/P9).** Every phase ends at a single **observable, machine-checkable** milestone (a byte-identical SHA1, an asm-differ score 0, a passing report, a clean-history scan). Honest NON_MATCHING/stub deferral beats a wrong guess (the `SaveLoadRoutine` precedent). The default build never links non-matching C (G4).
4. **Bank, don't strand.** Each phase is decomposed so the smallest committed unit (one library, one tool, one engine system, one overlay) is independently byte-verified — a stalled budget never strands an unverifiable half-task.

---

## Phase overview

| Phase | Name | Effort | Gate milestone (byte-checkable) |
|---|---|---|---|
| **8** | Finish the EXE — remaining PsyQ libs + final harvest | xHigh (Max if externals fight) | EXE SHA1 `143dbb89…` byte-identical with **and** without the new SDK objects; `make report` shows higher REAL count / fewer stubs; 0 NON_MATCHING in default build |
| **9** | Binary-agnostic toolchain refactor | xHigh | EXE rebuilds SHA1 `143dbb89…` through the **parameterized** path (refactor proven a no-op); reports reproduce exactly |
| **10** | Resident engine blob — splat config + all-asm byte-match | xHigh (Max if link fights) | resident blob image SHA1 == extracted `MAIN.CD/FILE_010/1.1`, at 100% INCLUDE_ASM |
| **11** | Cross-binary dedup pipeline | **Max** (design) | `docs/duplicates.cross.md` groups funcs across binaries; one shared C body → **both** EXE and resident blob byte-identical from a single source |
| **12** | Key engine systems — script VM, save/Q#5, sound (SQV) | **Max** | defined resident-blob systems matched at score 0 (script-VM core + `SaveLoadRoutine`/save path + SQV cluster); save format documented; both binaries green |
| **13** | Representative location overlays — end-to-end + fleet runbook | **Max** (template) | a location overlay (`SC01/077`) byte-identical from source; a duplicate pair collapsed to one source (both green); `make build-all`/`check-all` + one-command onboarding |
| **14** | **Public flip via a curated public repo (LATE CAPSTONE) — Gen2 EXIT** | **Max** | fresh **public repo** (private master untouched): only allowlisted paths, zero ROM bytes; `rom→decoder` + `make build && check` reproduces the EXE from a user's dump; no-ROM CI green; dashboard live |
| **15** | Overlay long-tail (ONGOING — **not a gate**) | xHigh + breadth | per-overlay `make check` byte-identical; fleet matched-% rises monotonically, zero regressions |

---

## Phase detail

### Phase 8 — Finish the EXE: remaining PsyQ libraries + final harvest
- **Goal:** Drive the EXE to its practical matching ceiling — link the remaining PsyQ SDK libraries byte-identical (libsnd, libgte, libapi/libgpu, libmcrd, libc/libc2, libetc, libspu — whichever `psyq_identify` confirms the EXE actually links) and harvest remaining easy single-binary matches — using only the proven Gen1 tools.
- **Why here:** Owner constraint #1, and the lowest-risk work in Gen2 — a known-good pipeline (`psyq_build_libs → psyq_identify → psyq_link_region → psyq_integrate`, twice-proven on libcd/libgs) against a known-good binary on a documented problem class (cookbook §9.1–§9.5). Banks matched bytes, shrinks the stub count, and keeps the EXE as the fully-understood reference every later pipeline is validated against. No new tooling.
- **Key tasks:**
  1. Run `psyq_build_libs.sh` for the remaining BFM-footprint libraries; gate each on `psyq_identify.py` placements before integrating (skip libraries with zero placements).
  2. Per present library, ascending difficulty: resegment `config/splat.us.exe.yaml` into per-block subsegs (derive blocks empirically from `psyq_identify`, cookbook §9.5 — don't trust notes), add a conditional `psyq_integrate.py` call in the Makefile `$(OUT)` recipe (gated on the SDK ELF dir → fresh-clone-safe), resolve externals, confirm byte-identical.
  3. Handle scattered-`.bss`/short-object hard cases per §9.1/§9.4 (`--weaken-symbol` + `--defsym`; placement window for short objects, GS_106 precedent).
  4. `make sig-refresh` → regenerate `docs/difficulty.md` → harvest cheap non-jtbl game-code leaves (cookbook §1–§5 idioms). Bank, don't exhaust.
  5. Update `include/psyq/*.h` from the Ghidra `.gdt` (cookbook §7) for any SDK function that must be hand-matched rather than linked.
- **Milestone:** `make clean && make extract && make build && make check` → SHA1 `143dbb89…` (byte-identical) **with the new libraries linked from real PsyQ objects AND with them absent** (stub fallback) — both green. `make report` shows the increased REAL count and reduced INCLUDE_ASM stubs; 0 NON_MATCHING in the default build (G4).
- **Dependencies:** Gen1 complete. No new tooling.
- **Primary risk + mitigation:** A library has scattered-`.bss` commons or byte-identical `.text` object aliases (the GS_131≡RVWUNIT class). → Documented in §9.1/§9.4; gate each library on `psyq_link_region.py --verify` (per-object byte-identical) *before* wiring it in, so a problem library is isolated to its own block and the EXE never leaves green. An intractable library stays as asm stubs (still byte-identical) — does not block the phase.
- **Effort tier:** **Tier-2 (xHigh)** bulk integration + harvest; **Tier-3** for regen/report steps; **Tier-1 (Max)** only if a library's external resolution fights the trial link beyond §9's coverage.

### Phase 9 — Binary-agnostic toolchain refactor
- **Goal:** Parameterize every single-binary tool by `--binary` / `--text-vram` / target paths so one toolchain builds any binary, and prove the refactor is a pure no-op by rebuilding the EXE byte-identically through the new path.
- **Why here:** The prerequisite enabler for all overlay/blob work, and the textbook "prove the new mechanism on the byte-locked binary." Confirmed scope: `psyq_integrate.py:33`, `psyq_identify.py:16` hardcode the EXE; `dup_report.py:14`/`progress.py`/`difficulty.py` hardcode it; the `Makefile` is `build/us`-only. The refactor's correctness oracle is "the EXE still produces SHA1 `143dbb89…`."
- **Key tasks:**
  1. Refactor `tools/psyq_*.py`: replace module-level `EXE` + the hardcoded text window with **required** `--binary` / `--text-vram-lo/hi`; the `VRAM_BASE = fileoff + 0x8000F800` relation becomes per-binary (overlays are *not* `0x8000F800`-based). Borrow the multi-binary list idiom from `match_protos.py`. One commit per tool (P4), each gated by the byte-identical EXE rebuild.
  2. Generalize the Makefile to a data-driven `BINARIES` list with per-binary `{config/splat.<bin>.yaml, build/<bin>/, config/check.<bin>.sha}`; `SLUS_007.26` is the first instance; the libcd/libgs `psyq_integrate` calls become per-binary.
  3. Generalize `progress.py`/`difficulty.py`/`dup_report.py` to a binary selector + per-binary sig file (`.run/sig.<bin>.jsonl`), defaulting to the EXE.
- **Milestone:** After the refactor, `make build` + `make check` reproduces SHA1 `143dbb89…` (proving a behavior-preserving no-op) and `make report` reproduces the Phase-8 counts exactly. A parameterized invocation that explicitly names the EXE confirms the parameter is actually threaded (not an ignored default).
- **Dependencies:** Phase 8 (validate against the fullest EXE build).
- **Primary risk + mitigation:** A hidden EXE-specific assumption (`0x8000F800` base, text-window default, the `ld_interleave.py` sandwich) silently bakes into the "generalized" path and only surfaces as a wrong address on the first overlay. → Make every binary-specific value a **required** parameter (no EXE default an overlay could inherit); the byte-identical EXE rebuild is the regression gate after each tool is touched (one-tool revert).
- **Effort tier:** **Tier-2 (xHigh)** (mechanical, hard SHA1 oracle); **Tier-3** for report-script parameterization.

### Phase 10 — Resident engine blob: splat config + all-asm byte-match
- **Goal:** Stand up the second binary — the always-resident engine blob (`MAIN.CD/FILE_010/1.1` @ `0x800CEDF8`) — as its own splat config that rebuilds byte-identical from disassembly alone (100% INCLUDE_ASM, no C yet).
- **Why here:** Mirrors Gen1 Phase 5 (all-asm byte-match before any matching) and proves the parameterized toolchain on a real second target whose load address + bytes are emulator-proven. Lowest-risk new target: **type-1 uncompressed** (no LZSS in the verify path), always-resident (no swap complexity), and partly imported into Ghidra already (Phase 3 T6b). It must precede engine matching and overlays because the script VM + actor system live here and every overlay references engine symbols defined here.
- **Key tasks:**
  1. Author `config/splat.<resident>.yaml`: `target_path` = extracted `1.1`; a single `code` segment at `vram: 0x800CEDF8`, **no header segment** (flat image); stacked `symbol_addrs_path: [config/symbols.us.txt, config/symbols.<resident>.txt]`. Iterate the text/data/rodata split against the byte check (as Phase 5 did for the EXE).
  2. Properly analyze the blob in Ghidra (decision at execution: a region in the existing program vs a second program in the `bfm` project — the latter is cleaner for per-binary symbols); apply PsyQ signatures; seed `config/symbols.<resident>.txt` (provenance-tagged, blob region only — never merged into `symbols.us.txt`). Optionally re-derive the EXE→resident pointer table (open Q#2) to map the blob's subsections.
  3. Wire its build target + `config/check.<resident>.sha` into the generalized Makefile; establish `make expected` baseline.
- **Milestone:** `make build BINARY=<resident> && make check` produces an image whose SHA1 equals the extracted `MAIN.CD/FILE_010/1.1` payload, at 100% INCLUDE_ASM (no C linked) — split + linker script + parameterized tooling proven end-to-end on the engine binary.
- **Dependencies:** Phase 9 (parameterized toolchain). Phase 3 T6b (done) supplies the proven load address + payload identity.
- **Primary risk + mitigation:** The blob mixes code/data so clean section detection is hard (rodata islands, data-in-text) or contains constructs the EXE lacked. → Byte-identity is robust to boundary placement as long as the disasm round-trips; reuse `ld_interleave.py` (the `.data→.rodata→.data` sandwich, cookbook §8) + the data-in-text carve. It's a fixed-address resident blob (no relocation) — the simplest realistic second target.
- **Effort tier:** **Tier-2 (xHigh)**; **Tier-1 (Max)** for section-boundary authoring if the clean link fights back (Gen1 Phase-5 conditional-Max precedent).

### Phase 11 — Cross-binary dedup pipeline
- **Goal:** Build the brand-new cross-binary duplicate-detection + share pipeline ("one match unlocks many") and prove it by collapsing functions shared between the EXE and the resident blob — match-once, link byte-identical in both.
- **Why here:** The key Gen2 economics, and it must precede the matching waves because it changes *what* you match (highest collapsible-bytes first) and *how* each match is spent. It is itself a new tool, so per the de-risk invariant it is validated on two already-byte-verified binaries (EXE from Phase 8, resident from Phase 10) before ever touching overlays.
- **Cross-binary dedup design (the deliverable):**
  - **(a) Gather signatures.** *Ghidra-rich:* generalize `make sig-refresh` to loop every imported program → `.run/sig.<prog>.jsonl` (`h_exact`/`h_norm`/`h_seq` + `nins`/`ncalls`/ordered `calls`). *Ghidra-free (scales to 134 without importing each):* new `tools/sig_image.py` linearly disassembles each flat `0.4.dec`/`1.1` at its known vram and computes the same `h_exact` + relocation-insensitive `h_norm` (neutralize `j`/`jal` 26-bit targets, `lui` highs, address-immediate low-16s — mirroring `DumpFunctionSignatures.normToken`), bootstrapping function boundaries from internal jump targets + known-function `h_norm` hits (the `match_protos.py` anchor model). Ghidra import is reserved for overlays actually matched (Phase 13).
  - **(b) Group.** Generalize `dup_report.py` to ingest all sig sources, tag each row with its `binary`, bucket by `h_exact` then `h_norm` across all binaries → `docs/duplicates.cross.md`, ranked by collapsible bytes `(count−1)×nins`. The ranked report **is** the Phase-12/13 work queue.
  - **(c) One C source → N binaries.** Symbol *stacking* (sotn pattern): shared names in `config/symbols.us.txt`; per-binary addresses in `config/symbols.<binary>.txt`; a shared C body `#include`s a common header and each binary's link supplies that binary's addresses, so an `h_norm` member relocates per binary from the SAME source. A `config/dedup.us.yaml` maps `group → {source, members:[{binary, vram}]}`.
  - **(d) Build links each binary to the right object.** `tools/dedup_integrate.py` — **forked from the proven `tools/psyq_integrate.py`** (swap stub → real object at a known vram, recover externals from the binary's resolved relocations R_MIPS_26/HI16+LO16, byte-gated, stub fallback) — runs in each binary's recipe. **Every redirect is byte-gated:** collapse only if the rebuilt image stays byte-identical, else keep the INCLUDE_ASM stub. `h_exact` is risk-free; `h_norm` is candidate-only, link-confirmed.
- **Key tasks:** (1) generalize `sig-refresh` + add `sig_image.py`; (2) cross-binary `dup_report.py` → `docs/duplicates.cross.md`; (3) `config/dedup.us.yaml` schema + `dedup_integrate.py`; (4) prove EXE↔resident, then the confirmed pair `SC01/005 ≡ 006` once overlays exist; (5) document the share workflow in a new cookbook §11.
- **Milestone:** `make report` emits cross-binary duplicate groups spanning ≥2 binaries; then a single shared C body, referenced from `config/symbols.SLUS_007.26.txt` **and** `config/symbols.<resident>.txt`, yields **both** `make check BINARY=SLUS_007.26` and `make check BINARY=<resident>` green — one match, two binaries, zero source duplication.
- **Dependencies:** Phase 9 (per-binary sigs + parameterized reports), Phase 10 (a verified second binary to dedup against).
- **Primary risk + mitigation:** `h_norm` over-grouping (false positive) or `sig_image` mis-segmentation makes a "shared" object non-identical at a member site, contaminating multiple binaries. → Byte-gate is the sole acceptance (P9/G3): a share is accepted only when `make check` is green in **every** claiming binary; lead with `h_exact` (guaranteed byte-match), treat `h_norm` as byte-confirmation-required candidates; validate `sig_image` boundaries against the imported blob before trusting them on overlays.
- **Effort tier:** **Tier-1 (Max)** for the dedup-semantics design (a wrong grouping model poisons all downstream overlay economics — the effort-map's "poisons everything downstream" criterion); **Tier-2** for report/share mechanics; **breadth (Workflow/Ultracode)** for the actual cross-binary scan (same analysis over many functions).

### Phase 12 — Key engine systems: script VM, save/Q#5, sound (SQV)
- **Goal:** Match the engine's core systems in the resident blob — the script/bytecode VM core, the save-data format + memcard path (Q#5 / `SaveLoadRoutine` @ `0x8002B154`), and the sound driver (SQV) — each match auto-credited to overlays via Phase-11 dedup.
- **Why here:** These are the owner's named exit-criteria systems and are mostly greenfield. They depend on the blob building (10) and dedup existing (11) so shared engine/SDK helpers aren't re-matched; EXE-side anchors are in hand (`SaveLoadRoutine` + `saveHeaderTemplate` @ `0x80072DF0`; the 28-dump RAM corpus incl. `ram_savescreen.bin` for Q#5). The unproven element is the *code*; the toolchain + dedup are now fully proven.
- **Key tasks:**
  1. **Save/Q#5:** resolve `SaveLoadRoutine` (Gen1-deferred 1139-ins multi-entry blob) + the save-block format/checksum using `ram_savescreen.bin` + libmcrd/`write` xrefs (libmcrd linked in Phase 8 as anchors); document the format in `docs/formats.md`.
  2. **Script VM:** locate the bytecode dispatcher/opcode jump-table in the blob (cookbook §8 rodata workflow), prototype the VM state in Ghidra, match the interpreter core + first handlers.
  3. **Sound (SQV):** RE the SQV (MIDI+VAB, semi-custom) driver; link wrapped libsnd/libspu PsyQ objects byte-identical (§9 pipeline); match the custom sequencer glue.
  4. Feed every hard residual back into the cookbook (R16 flywheel); use the §3a/R17 web-research tier + decomp-permuter for compiler-quirk/scheduling tails.
- **Milestone:** A defined set of resident-blob engine functions at asm-differ **score 0** with `make check BINARY=<resident>` byte-identical — specifically (a) the save/load path matched + save-data layout documented; (b) the script-VM interpreter core matched; (c) the SQV driver entry cluster matched (hand-match or byte-identical PsyQ link). `make report BINARY=<resident>` crosses the agreed "key systems matched" bar; 0 NON_MATCHING in the default build.
  - **⟶ AMENDED at Phase-12 close (2026-06-16, Drew-approved gate 2 — the bytes reshaped the premises; "substantial + honest deferral"):** (1) the resident has **no PsyQ library footprint** (T1, byte-verified) — it is all custom engine code, so progress is **REAL** (hand-matched C), not LINKED; (2) there is **no bytecode VM** (T4) — the "script VM" is **resolved** as compiled-MIPS state/mode dispatch via function-pointer tables (byte-backed by the matched dispatchers), a *written determination* (not a matched interpreter); (3) the **save/Q#5 path is documented** (`saveHeaderTemplate` header + the `0x8002Bxxx` handler table + the `bu00:BASLUS-00726MUSASHI` libmcrd path, runtime-confirmed) with the deep save-data serialization + `SaveLoadRoutine`'s 1139-ins code-match **honestly deferred** (Gen3-repack / Gen1-precedent, not needed for the byte-match, P9); (4) the **SQV** cluster matched in the harvest + format documented (semi-custom). **Achieved:** resident **REAL 1 → 123/146 = 85.62% byte-identical**, both binaries byte-identical, 0 NON_MATCHING in either default build.
- **Dependencies:** Phases 10, 11; Phase 8 (libsnd/libspu/libmcrd as call anchors).
- **Primary risk + mitigation:** A system (esp. the script VM or `SaveLoadRoutine`) is too large/entangled for clean Ghidra decompilation, tempting a fake-success stub (the psxrecomp failure mode). → G3 byte-match + G4 NON_MATCHING + P9 honesty: an unmatchable system is left an honest NON_MATCHING draft or documented stub (the Gen1 `SaveLoadRoutine` precedent); milestone counts only score-0 matches; size each system as its own sub-task so a stall strands one system, never a half-binary.
- **Effort tier:** **Tier-1 (Max)** — deep, novel greenfield RE where wrong structural understanding is expensive. Breadth helps only for surveying candidate functions.

### Phase 13 — Representative location overlays: end-to-end + fleet runbook
- **Goal:** Take a *representative* set of overlays from "identified" to byte-identical-from-source end-to-end (splat at `0x80128158` → import → dedup-credit shared engine code → match the unique remainder → byte-check), and produce the repeatable per-overlay runbook + a one-command fleet build.
- **Why here:** The exit-criterion "representative set matched end-to-end." Deliberately after the resident engine (overlays call engine symbols), after dedup (overlays share code), and after the toolchain is binary-agnostic + proven on two binaries. Every *component* is now proven; a representative set bounds risk before the long-tail.
- **Key tasks:**
  1. Reusable `config/splat.us.overlay.template.yaml` parameterized on the `0.4.dec` path; all overlays share `vram: 0x80128158` (position-locked, confirmed) and stack `symbol_addrs_path: [symbols.us.txt, symbols.<resident>.txt, symbols.ov<NN>.txt]`. Account for the per-location data/entity block *below* `0x80128158` (separate subseg).
  2. Stand up the milestone overlay `SC01/077` (load byte-proven): all-asm byte-match → dedup-credit against resident+EXE → harvest its unique matches.
  3. Add a confirmed duplicate pair (`SC01/005 ≡ 006` or `SC02/000 ≡ 003`) to prove cross-overlay collapse; add a large free-roam overlay (e.g. `SC03/001`) to prove the recipe scales.
  4. Produce `tools/new_overlay.sh` (instantiate yaml, register binary, snapshot check.sha, auto-run dedup-credit) + `make build-all`/`check-all` (whole-fleet single PASS/FAIL); document the canonical "add an overlay" runbook (cookbook).
- **Milestone:** For each overlay in the set, `make build BINARY=<ovNN> && make check` → SHA1 == the extracted `0.4.dec` payload (at least at 100% INCLUDE_ASM, with harvested score-0 matches linked). The duplicate pair shares a matched body across both members (both green from one source). `make build-all`/`check-all` green; `tools/new_overlay.sh` onboards a fresh overlay to a byte-identical all-asm build + dedup credit in one command.
- **Dependencies:** Phases 9, 11, 12. Phase 3 overlay map + RAM dumps (done).
- **Primary risk + mitigation:** An overlay isn't as cleanly position-locked as the sample (internal relocation / a loader-patched pointer like `SC01/077`'s `+0x5F118` field). → Verify at the decompressed layer against the on-disk `0.4.dec` (the pre-load payload, before runtime patches); the proven model is that divergences are runtime data init, not relocation. Pick the set to span the distinct shapes so any anomaly surfaces here (3–5 overlays), not in the long-tail; an anomalous overlay becomes a documented special case.
- **Effort tier:** **Tier-1 (Max)** for the overlay template + first overlay (the pattern inherited by ~134 overlays); **Tier-2 (xHigh)** for subsequent ones; **breadth (Workflow)** for per-overlay harvest.

### Phase 14 — Public flip via a curated public repo (LATE CAPSTONE — Gen2 EXIT)
- **Goal:** Publish the project as a **separate, freshly-created public repo** — AGPL-3.0 LICENSE, the `rom→decoder` regeneration tool, no-ROM CI, frogress/decomp.dev — while **this private repo remains the untouched master/backup**. (Replaces the earlier in-place history-scrub approach — owner decision 2026-06-15: the two-repo model is safer and cleaner.)
- **Why here:** Owner constraint #2 (late capstone), after substantial matching. The two-repo model avoids any destructive history rewrite of the master: the public repo is built by **copying an allowlisted subset into a fresh repo with new history**, so there is nothing to scrub and no force-push, and the master's full ROM-relaxed working history + backup value is preserved. It also cleanly separates "my private storage/backup" from "what I share." It touches governance/infra, not matching, so it can't regress any byte-identical result.
- **What goes public (allowlist) vs stays private:**
  - **Public:** `src/`, `config/`, `tools/` (decomp-relevant), `include/`, README, LICENSE, the `rom→decoder` tool, and the *technical* docs — `docs/matching-cookbook.md`, `docs/formats.md`, `docs/memory-map.md`, `docs/SETUP.md`. **NO ROM-derived bytes** (no `extracted/`, no `dumps/`, no disc dump, no EXE).
  - **Private (master only):** the *process scaffolding* — `CLAUDE.md`, the AI-collaboration rules, `docs/effort-map.md`, `docs/gen2-roadmap.md`, the `phase-ends/` worklogs, MEMORY. `PROJECT_CONTEXT.md` is mixed → publish a *derived* technical overview, not the file itself. (Optional: one cleaned-up methodology writeup.)
- **Key tasks:**
  1. **rom→decoder regeneration tool:** promote `tools/bfm_extract` into the public `make extract` so a contributor with their own legally-owned dump regenerates every ROM-derived artifact (`extracted/`, the `0.4.dec` payloads, the EXE) deterministically, sha1-manifest-verified — the public repo ships only configs/symbols/source + this tool (sotn precedent).
  2. **Build the public repo:** create a fresh repo; copy the **allowlisted** paths in (copy-in, never copy-all-then-delete); author the public README (the "stranger with their own dump can `make extract && build && check`" criterion); add **AGPL-3.0 LICENSE** (sotn model; `tools/brave-CUE/` keeps its own GPL). A committed allowlist + a ROM-SHA1/oversized-blob scan gate the FIRST public push.
  3. **No-ROM CI** (GitHub Actions on the public repo): with a secret/self-hosted dump, run `make extract && build-all && check-all` + report determinism; the image carries the toolchain, never the ROM. CI verifies what's verifiable ROM-free, never fakes a byte-check (P9).
  4. **frogress / decomp.dev:** publish per-binary matched-byte progress, fed by the parameterized `progress.py`.
  5. **One-way sync:** a documented script to push future updates from the private master's allowlisted paths → the public repo, so ongoing Gen2/long-tail work flows out without re-deciding the split each time.
- **Milestone (Gen2 EXIT, all true):** (a) the **public repo's working tree + its entire (fresh) history** pass a ROM-SHA1 / oversized-blob scan → **zero** found, and a diff confirms only allowlisted paths are present (no scaffolding, no ROM); (b) on a fresh clone of the public repo with **no ROM present**, `<rom→decoder> <user-dump>` + `make build && make check` reproduces the EXE SHA1 `143dbb89…`; (c) no-ROM CI green; (d) the dashboard renders live per-binary percentages; (e) **the private master is unchanged** (no history rewrite).
- **Dependencies:** Phases 8–13 substantially complete; owner gate before the first public push (P5c-class — making content public is irreversible/outward-facing).
- **Primary risk + mitigation:** The public repo accidentally includes a ROM byte or a scaffolding file. → Build by **explicit allowlist** (copy-in, not delete-from-a-copy); gate the first push on a working-tree+history ROM-SHA1/oversized scan AND an "only-allowlisted-paths" diff; owner reviews before pushing. Because the master is never rewritten, a public-repo mistake is fixable by re-curating — no irreversible damage to the master or its backup history.
- **Effort tier:** **Tier-1 (Max)** — irreversible, outward-facing, security-sensitive (publishing); **Tier-3** for the LICENSE file + dashboard wiring once the allowlist + rom→decoder are proven.

### Phase 15 — Overlay long-tail (ONGOING — explicitly NOT a Gen2 gate)
- **Goal:** Match the remaining ~130 location overlays by repeated application of the Phase-13 runbook + Phase-11 dedup economics — open-ended, never an exit gate.
- **Why here / open-ended:** Owner constraint #3. By now the per-overlay recipe is proven and dedup makes each new overlay cheap (match-once-share-many). Runs against the public repo with the dashboard live, so external contributors can participate. Captures and tracks the tail without holding Gen2 (or Gen3) hostage to exhaustive completion.
- **Key tasks:** generate the full overlay worklist (all 134 `0.4.dec` payloads, ranked by collapsible-bytes from `docs/duplicates.cross.md` + RAM-dump coverage); per overlay: instantiate config, dedup-credit against the live corpus, harvest the unique remainder, confirm byte-identical at the decompressed layer; continuously feed the dashboard; capture new overlay shapes back into the runbook.
- **Milestone (recurring, not a gate):** each overlay closes when `make check BINARY=<ovNN>` is byte-identical against its `0.4.dec` SHA1; the cumulative overlay matched-% rises monotonically with zero checksum regressions. **No single completion bar gates the phase.**
- **Dependencies:** Phases 11, 13, 14. Does **not** block Gen2 exit (declared at Phase 14).
- **Primary risk + mitigation:** Long-tail fatigue / budget exhaustion mid-overlay; or a rare overlay shape breaks the template. → Each overlay is independently byte-checkable and committed on completion (P4) — a stall strands nothing; open-ended-by-design means no all-or-nothing gate; rare shapes become documented special cases.
- **Effort tier:** **Tier-2 (xHigh)** per overlay + **breadth (Ultracode/Workflow fan-out)** for parallel harvest; **Tier-1 (Max)** only when a genuinely new shape appears.

---

## Dependency graph / critical path

```
Phase 8  Finish EXE (proven single-binary tools)            [xHigh]  ── constraint #1
   │
   ▼
Phase 9  Binary-agnostic refactor (proven: EXE byte-identical) [xHigh]
   │
   ▼
Phase 10 Resident engine blob — all-asm byte-match           [xHigh/Max]
   │
   ▼
Phase 11 Cross-binary dedup (proven: EXE ↔ resident)         [Max]
   │
   ├──────────────────────────────┐
   ▼                              ▼
Phase 12 Engine systems        Phase 13 Representative overlays
 (VM/save/sound)  [Max]         (end-to-end + fleet runbook)  [Max]
   │                              │   (needs 9, 11, 12)
   └──────────────┬───────────────┘
                  ▼
            Phase 14  PUBLIC FLIP — Gen2 EXIT (late capstone)  [Max]
                  │   (needs substantial matching: 8–13)
                  ▼
            Phase 15  Overlay long-tail — OPEN-ENDED, NOT A GATE  [xHigh + breadth]
```

- **Critical path:** 8 → 9 → 10 → 11 → {12, 13} → 14.
- **Permitted overlap:** Phases 12 and 13 can run concurrently once 11 is done — an overlay can reach *all-asm byte-match* (needs symbols/addresses, not matched C) before every engine system is matched; 12's engine matches then incrementally credit 13's overlays via dedup.
- **The invariant:** each new pipeline meets a *known-good* binary before a *greenfield* one — Phase 9 on the byte-locked EXE, Phase 11 on the byte-verified EXE↔resident pair, Phase 13 on the byte-proven `SC01/077`. No unproven-tool-meets-unproven-target crossing exists on the critical path.

---

## Gen2 EXIT criteria (the "substantial, not exhaustive" decision)

Gen2 exits — and Gen3 may be considered — when **all** are machine-verified:
1. **EXE at its matching ceiling** (constraint #1): all linkable PsyQ libraries linked byte-identical; the easy difficulty-queue tail harvested; EXE byte-identical with and without SDK objects. *(Phase 8)*
2. **Resident engine blob matched substantively** — the **script/event system resolved** (Phase 12: *no bytecode VM*; it is compiled-MIPS state/mode dispatch via fn-pointer tables — a byte-backed written determination, not a matched interpreter), the **save/Q#5 path documented** (`saveHeaderTemplate` + handler table + libmcrd path; deep save-data serialization + the `SaveLoadRoutine` code-match honestly deferred as Gen3/Gen1-precedent, P9), and the **sound/SQV cluster** matched + documented — all byte-checked, none NON_MATCHING in the default build; `make check BINARY=<resident>` green. **Met Phase 12 at REAL 123/146 = 85.6% byte-identical** ("substantial, not exhaustive"; the ~21 remaining stubs are documented permuter/§3a residuals). *(Phases 10, 12 — milestone amended at the Phase-12 close, Drew-approved)*
3. **Cross-binary dedup live and proven:** `make report` emits cross-binary groups, and ≥1 shared body is byte-identical across ≥2 binaries from a single source. *(Phase 11)*
4. **A representative set of location overlays matched end-to-end** (≥3 spanning the archetypes: a single overlay, a collapsed duplicate pair, a large free-roam overlay), each `make check` byte-identical against its `0.4.dec`. *(Phase 13)*
5. **Public with a dashboard (via the curated public repo; private master untouched):** AGPL-3.0 present; the public repo's tree + history scan clean of ROM bytes and contain only allowlisted paths; rom→decoder reproduces the byte-identical EXE on a fresh clone from a user's dump; no-ROM CI green; frogress/decomp.dev live. *(Phase 14)*
6. **Fleet build self-sustaining:** `make build-all`/`check-all` green; onboarding a new overlay is one command. *(Phase 13)*

**Explicitly NOT required for exit:** completing the ~134-overlay long-tail (Phase 15 is open-ended), matching every engine function, or any Gen3 work (shiftability, repack, native recomp, randomizer tooling).

---

## Inherited open-questions (assigned to phases)

| # / topic | Where documented | What's known | Gen2 phase that picks it up |
|---|---|---|---|
| **Q#5 save / memcard format** | memory-map §2.3 / §5; PhaseEnd_Phase7 (deferred) | `saveHeaderTemplate` @ `0x80072DF0` verified; `SaveLoadRoutine` @ `0x8002B154` (1139-ins, multi-entry) deferred | **Phase 12** (with `ram_savescreen.bin`, libmcrd anchors) |
| **EXE→resident pointer table** (Q#2; JP ~0x62620, re-derive US) | memory-map §4.1/§4.2 | resident base proven (`0x800CEDF8`); the *table* that maps sub-files → load dests is JP-only documented | **Phase 10** (informs resident-blob subsection layout) |
| **Full location-ID ↔ SCxx.CD FILE map** | memory-map §4.3 (~11/35 live-verified) | 134 `0.4.dec` payloads exist; ~11 locations RAM-verified | **Phase 13/15** (overlay worklist; may need another PCSX-Redux session) |
| **Script VM instruction set** | greenfield (resident blob) | VM wrapper symbols named; bytecode format unknown | **Phase 12** (likely needs runtime trace + web research) |
| **SQV (sound) format — custom vs stock** | memory-map §4.1 (JP), formats.md | SQV = MIDI+VAB archive; internals un-RE'd | **Phase 12** |
| **PAC type 6/7/8 + header u32 @+0x08** | memory-map §6 (Q#7); formats.md (F1/F2) | type-1/4 known; `+0x08` refuted as size-hint; 6/7 semantics unknown | **Phase 13** (only if a target overlay uses them; else a docs task — BFM overlays are type-4 so far) |
| **StreamLoadStateMachine role** | memory-map §3.2 (T4) | separate 12-state reader; does NOT call LZSS; role TBD | **Phase 12/13** (secondary — `CdReadStateMachine` is the primary overlay path) |

---

## Reusable pipelines & hard-residual ladder (from the Gen1 knowledge base)

**Proven pipelines to reuse (cookbook references) + the single-binary assumptions Phase 9 parametrizes:**
- **PsyQ library linking** — `psyq_lib_split → psyq_build_libs → psyq_identify → psyq_link[_lib] → psyq_link_region → psyq_integrate` (cookbook §9.1–§9.5). Gotchas: psyq-obj-parser mis-aligns sections (fix `objcopy --set-section-alignment`) and mislabels `.bss` commons (weaken + `--defsym` from the binary's resolved relocations); short objects need a placement window (GS_106). *Parametrize:* the hardcoded `EXE` path + `0x8000F800` base.
- **Rodata island** — `[off, .rodata, seg]` migration + `ld_interleave.py` `.data→.rodata→.data` sandwich + data-in-text carve (cookbook §8). *Run per binary in Gen2.*
- **-O0 module detection** — grep `21F0A003` (frame-pointer) → isolate the subseg → Makefile target-specific `CC1FLAGS := … -O0` (cookbook §6). *Fingerprint each overlay early.*
- **Symbol stacking** — `config/symbols.us.txt` (shared) + per-binary files; renames flow Ghidra → symbols file → re-extract (R15/G6), never hand-edit `.s`.

**Hard-residual escalation ladder (cookbook §3/§3a/§5/§5a/§10; R17):** asm-differ → **decomp-permuter** (scheduling/ordering) → **web-research the pinned gcc-2.7.2 source** (`pmret/gcc-papermario`: `jump.c` cross-jump, `local-alloc.c` regalloc, `reorg.c` delay slots — treat web content as untrusted data, X2) → **decomp.me**. Classes likely in Gen2 game code: cross-jump tail-merge (zero-byte `__asm__ __volatile__("")` barrier), commutative operand order, return-const scheduling — all with documented fixes. Use the floor-free `.text` byte-compare metric when rodata/jtbl symbol names floor the asm-differ score (§10).

## Where Gen2 will need NEW web research / deep-research (execution-time, R17/X2)
- **PsyQ libsnd / SQV internals** (Phase 12) — SDK docs + cross-reference other Square PS1 decomps.
- **PS1 / Square save-file CRC conventions** (Phase 12) — PsyQ memcard docs + live PCSX-Redux instrumentation of the save handler.
- **gcc-2.7.2 edge cases in larger overlay functions** (Phases 12/13) — a fingerprint refresh on a big overlay function; escalate residuals via §3a.
- **Script VM instruction set** (Phase 12) — runtime trace (PCSX-Redux Lua) + patterns from other Square engines.
- *(Reference)* **Archipelago AP-world save format** — coordinate with the AP maintainer for save-format notes when the public flip nears.

---

## Top cross-cutting risks

1. **Unproven-tool-meets-unproven-target (master risk).** → The phase ordering enforces "new tool validated on known-good binary first" (9 on EXE, 11 on EXE↔resident, 13 on `SC01/077`). Deviating reintroduces the risk.
2. **AI fake-success on greenfield engine code (P9 / psxrecomp post-mortem).** The VM, `SaveLoadRoutine`, SQV are large and partly Ghidra-opaque. → G3 byte-match + G4 NON_MATCHING + milestones defined as score-0 / byte-identical SHA1; honest deferral is the precedent; per-system sizing.
3. **Cross-binary dedup false positives.** A wrong `h_norm` share contaminates multiple binaries. → Byte-gate every redirect; lead with `h_exact`; `h_norm` candidate-only, link-confirmed.
4. **Public repo leaks ROM / scaffolding, or breaks reproducibility.** → Two-repo model: the private master is never rewritten (no destructive scrub), so this risk is isolated to the *new* public repo and is fully reversible by re-curating. Build the public repo by explicit allowlist (copy-in); gate the first push on a tree+history ROM-SHA1/oversized scan + an "only-allowlisted-paths" diff; rom→decoder validated by a fresh-clone byte rebuild before the flip; owner reviews before pushing.
5. **Budget exhaustion stranding an unverifiable half-task** (sustained agentic RE is expensive). → Every phase ends at a byte-checkable milestone; smallest committed unit (one library/tool/system/overlay) independently verified and committed (P4); the open-ended Phase 15 has no gate, so the tail can never strand the project; the two heaviest tasks (11 dedup-semantics, 12 engine systems) are flagged Tier-1 Max so they aren't attempted under a rushed budget.

---

## Process notes
- **Per-phase gates still apply.** This roadmap is the Gen2 *map*; each phase, when started, runs the **Phase Start Protocol** (analyze checklist → present task-by-task plan → owner approval → write `CURRENT_PHASE.md` → autonomous execution), and ends with the **Phase Boundary Protocol** (verify every checkbox → demonstrate the observable milestone → owner confirms → PhaseEnd file → worklog archived per R19). Two gates per phase, autonomy between (P3).
- **Effort & breadth.** Planning each phase = Max (Tier-1). Execution drops to xHigh where the design is settled. **Breadth (Workflow fan-out, opt-in Ultracode) is surgical** — for the cross-binary scan (Phase 11) and overlay harvest (Phases 13/15), never for the deep synthesis (which Ultracode would cap at xHigh). The planning session used parallel Explore/Plan subagents for breadth while the synthesis stayed at Max — no global Ultracode needed.
- **Provenance of this plan.** Designed 2026-06-15 (Gen1→Gen2 boundary session) at effort Max, via parallel reconnaissance (overlay/loader landscape, engine-systems maturity, tooling/build/public-flip inventory) + a knowledge-base mine of the cookbook, the Phase-7 worklog, and `docs/`, then a two-lens Plan panel (de-risk vs leverage) synthesized at Max. Load-bearing facts byte-verified (R14).
- **Approximate figures (R14).** The ~134 overlay count is byte-verified; per-`.CD` distribution and remaining-library symbol counts are directional and get pinned by the Phase-11 report / Phase-13 worklist — they gate nothing.

---

## Backup & disaster recovery (project policy — Drew, 2026-06-15: "private backup is essential; I won't want to regenerate anything if a HDD [death] occurs; this is a very long project")

**Already safe (tracked + pushed to the private `origin`):** all decomp *work* — PROJECT_CONTEXT, CLAUDE.md, `phase-ends/`, all `docs/`, `config/` (incl. `symbols.us.txt`), `src/` (the matched C), `tools/`, `include/`, and the 29 `dumps/*.bin`. A fresh `git clone` restores all of it.

**Decisions (Drew, 2026-06-15):**
1. **Ghidra project → COMMITTED to the private repo** (this session). `ghidra/` (~36 MB; no file >100 MB) is the annotated RE database (comments, types, structs beyond `symbols.us.txt`) — the one valuable, *laborious-to-redo-by-hand* artifact. `.gitignore` now **tracks** `ghidra/` and excludes only live-session transients (`*.lock`, `tmp*.ps`) so a running MCP server doesn't dirty the tree. Re-commit after significant RE (the data buffers change only on a Ghidra *save*, so read-only sessions cause no churn). Ghidra is pinned at 12.1, so the committed `.rep` restores directly. *(Optional future hardening: also commit a per-program `.gzf` export for cross-version portability.)*
   - **Operational note (how a Ghidra commit actually works):** the MCP server holds an open transaction while serving → **no mid-session save**, and **closing the CC session does NOT save** (SessionStart hook auto-starts the server; no SessionEnd hook; a SIGKILL loses the work). The lock never blocks `git` (gitignored; ext4 reads open `.rep` files) — the real requirement is a *save* before commit. So at a checkpoint/phase-end **with RE work**: Claude runs `tools/ghidra_mcp_stop.sh` (clean save+close → "Save succeeded", lock released) + `tools/ghidra_mcp_verify.sh` (R9), then Drew commits+pushes `ghidra/`; the next session's SessionStart hook restarts the server from the saved DB. Don't push `ghidra/` mid-RE (stale snapshot). Planning-only sessions need no stop. *(Optional: a SessionEnd hook running stop.sh would make "close session → Ghidra saved" literally true, for clean exits.)*
2. **Disc dump → NOT backed up** (deliberate). `disks/` (Track-1 `.bin` = 364 MB, >100 MB → GitHub rejects it anyway) stays ignored. Re-ripping the legally-owned physical disc is easy (Drew), and `make extract` regenerates everything downstream from it. Not decomp work.
3. **`extracted/` bulk → NOT committed** (deliberate, recommended). 760 MB of decompressed ROM data; every file *is* under 100 MB so committing is *possible*, but it regenerates in one `make extract` from the (easily re-ripped) dump and is **not decomp work** — committing it would add 760 MB of repo bloat for zero protection of actual work. Status quo kept: only the 3 retail files (EXE + 2 manifests) committed. Same for `asm/`, `build/`, `expected/`, `.venv/`, compiler downloads — all regenerable; stay ignored. *(Reversible if Drew later wants a literal zero-`make` clone.)*

**Net:** after this session's Ghidra commit + push, **a dead HDD costs nothing but a one-command `make extract` + a quick disc re-rip** — zero hand-redone decomp work.

**Commit cadence (loosens R8 — Drew-approved):** commit + push at **per-session (or finer) checkpoints**, not just at phase end; push irreplaceable work the moment it lands. (Phase 7 already ran this way.)

**→ Proposed rule R20 (active now per Drew 2026-06-15; formalize at the next PhaseEnd):** *Every piece of irreplaceable RE/decomp work — including the Ghidra project — is committed AND pushed to the private remote at per-session checkpoints (loosening R8). The disc dump (re-rippable, >100 MB) and regenerable build/`extracted/` bulk are the deliberate, documented exceptions. Never let hand-produced work live only on the local HDD between phase boundaries.*
