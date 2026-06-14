# PhaseEnd — Phase 5: splat config + build skeleton (all-asm byte-match)
**Date:** 2026-06-14 · **Project Version:** 1.5.0 · **Phase Status:** Complete

## Build Log

**Files created/changed and complete — do not recreate:**
- `config/splat.us.exe.yaml` — **new.** The splat config for the main EXE. Derived from splat 0.41.0's own
  `create_psx_config` template (platform `psx`, compiler `PSYQ`, `subalign: 2`, `section_order` rodata/text/
  data/bss, `find_file_boundaries: False`, `gp_value: 0x80074750`). `base_path: ..` (the yaml lives in
  `config/`, so paths anchor at the repo root). One `code` segment split into a `[0x800] asm` text
  subsegment + a `[0x531DC] data` subsegment, `align: 4` on the segment (see Deviations). Consumed by
  `make extract`.
- `config/check.us.sha` — **new, committed.** `143dbb89… SLUS_007.26` — the canonical build-check hash
  (validation stage 2). Consumed by `make check`.
- `config/symbols.us.txt` — **modified (now HAND-CURATED).** 15 `2D_*` → `gfx2D_*` renames (a leading digit
  is an illegal as/C identifier — it broke `as`); added the `D_800629D4` data label (boot-code-referenced
  address in the text→data boundary region that splat did not auto-label). Header rewritten to flag that
  ExportSymbols.java overwrites this file → re-apply curations + mirror to Ghidra (G6). Consumed by splat.
- `Makefile` — **modified.** The five Phase-5 stub targets replaced with real implementations: `extract`
  (splat split), `build` (assemble `asm/*.s` → `ld` via the splat linker script + `undefined_*_auto.txt` →
  `objcopy -O binary` → `build/us/SLUS_007.26`), `check` (SHA1 vs `config/check.us.sha`, auto-run by
  `build`), `expected` (snapshot a verified build → `expected/build/`), `clean` (remove all regenerable
  outputs). Added vars `SPLAT/CPP/OUT/ELF/LD_SCRIPT/ASFLAGS/ASPSX_VERSION/OBJS`. `check-env` untouched.
- `.gitignore` — **modified.** Ignore the regenerable splat outputs (`/asm/`, the four generated
  `include/` macros, `undefined_{syms,funcs}_auto.txt`); the earlier "commit asm/" note refined with
  rationale (durable record = `config/symbols.us.txt`). `/build/` + `/expected/` already ignored.
- `docs/SETUP.md` — **modified.** §4.5 binutils **VERDICT: 2.42 byte-clean** (no downgrade); §5.3 + ledger
  #8 **RESOLVED: -G0**; §6.3 **As-built (Phase 5)** target table note; ledger #6 resolved. Original
  deferred-verdict text preserved (additive).
- `docs/memory-map.md` — **modified.** §1 `gp0` row → **-G0 CONFIRMED**; added the **Text→data split**
  block (file/vram boundary, the mixed transition region, `vram = fileoff + 0x8000F800`).
- `phase-ends/PhaseEnd_Phase5.md` — this file.
- `phase-ends/CURRENT_PHASE.md` — **absorbed into this file and deleted** (P8).

**Local artifacts (gitignored / regenerable — do NOT recreate; `make extract` rebuilds them):**
- `asm/{header.s, 800.s, data/531DC.data.s}` — the splat disassembly (header reproduced via splat's
  structured `header` segtype; text + data).
- `include/{include_asm.h, macro.inc, labels.inc, gte_macros.inc}` — splat-generated assembler macros.
- `build/us/SLUS_007.26.ld` — the splat-generated linker script (`_gp=0x80074750`; `ALIGN(.,4)`).
- `undefined_syms_auto.txt` (899) + `undefined_funcs_auto.txt` (8) — splat-generated linker symbol defs.
- `build/` (objects, `.elf`, the 413,696-byte binary) + `expected/build/` (the asm-differ baseline).

**Tools/packages installed:** None — used the existing Phase-4 toolchain (splat64 0.41.0, mipsel-binutils
2.42, the cc1 candidates) entirely. (cc1/maspsx were not invoked — the build is all-assembly.)

**Verification results (literal):**
- **`make extract && make build && make check` → `build/us/SLUS_007.26`, 413,696 B, SHA1
  `143dbb89f34491258bbc27810d0a12ec8b43a8dd` == original (BYTE-IDENTICAL).** Reproduced from a full
  `make clean` cycle.
- **Check is a real gate:** a 1-byte corruption makes `make check` exit non-zero; a rebuild restores `[ OK ]`.
- `make check-env` still exits 0 (no Phase-4 regression).
- **binutils 2.42 byte-clean** with `as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0` — the §4.5
  "≥2.38 regression" risk did not materialise; no 2.35 downgrade.
- **-G0 confirmed:** the disassembly has **0** `($gp)` base accesses and **0** `%gp_rel` relocations.
- `git status`: only `config/`, `Makefile`, `.gitignore`, `docs/` tracked; `asm/ build/ expected/` +
  generated macros + `undefined_*_auto.txt` ignored — **zero generated/ROM bulk staged.**

**Milestone achieved:** `make build` rebuilds `SLUS_007.26` **byte-for-byte (SHA1-identical)** from
disassembly alone at 100% assembly, with the SHA1 check auto-running and provably failing on corruption —
the split, linker script, and as→ld→objcopy tooling proven end-to-end.

**Next:** Phase 6 — Compiler fingerprint + first matched functions. Start with selecting 3–5 medium leaf
functions as fingerprint probes (⭐⭐ **Max** — the highest-stakes task in Gen1 per `docs/effort-map.md`).
Phase 6 also introduces the `c`/INCLUDE_ASM scaffold (flip the code subsegment to `c`, wire `decompile.py`
+ asm-differ, establish INCLUDE_ASM/NON_MATCHING headers) — the Makefile already has the dormant
cpp→cc1→maspsx path and the §5.4 candidate ladder is queued.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Code segment type | `c`/INCLUDE_ASM primary; `asm` as fallback | **`asm` (all-asm)** | The plan's documented fallback, and the better fit: the phase title is "all-asm byte-match" and the roadmap puts INCLUDE_ASM/NON_MATCHING setup in Phase 6. Keeps the unpinned compiler out of Phase 5. Drew-ratified. |
| Execution order | T1 split → T2 Makefile → T3 byte-match | Byte-identity proven by a **manual round-trip during T1**, before the Makefile | Isolated and cleared the High-risk binutils-2.42 variable first (as→ld→objcopy only); the Makefile then just transcribed the working chain. |
| binutils 2.42 verdict | possibly downgrade to 2.35 (§4.5) | **No downgrade — 2.42 is byte-clean** | The build is SHA1-identical with 2.42; the regression warning didn't bite our flags. |
| `asm/` git policy | gitignore (my plan) vs the repo's existing "commit asm/" note | **gitignored** (regenerable via `make extract`) | `make extract` deterministically regenerates it from committed yaml+symbols → build scaffolding, not durable work. `.gitignore` note refined; Drew-ratified. |
| Section-boundary effort | feared a fighting link (T3 Max-escalation) | The link was clean; the only real fights were **15 leading-digit symbol names** + **one un-labelled boundary address** + an **`align: 4`** tweak | splat round-trips bytes, so byte-identity was robust to the imperfect text/data split (as predicted). |
| `config/symbols.us.txt` role | seeded Ghidra export | became the **hand-curated** build input | Build validity (identifiers) + a boot-referenced label had to be fixed in the splat input; ExportSymbols now a careful re-merge, not a blind overwrite (→ R15). |

## Commit Message
```
feat(phase-5): splat config + all-asm byte-identical build of SLUS_007.26

- config/splat.us.exe.yaml: splat PSX config (platform psx, compiler PSYQ,
  subalign 2, gp_value 0x80074750, base_path .., main segment align 4); one
  asm text seg [0x800] + data seg [0x531DC], header via splat's header segtype
- Makefile: implement extract (splat split) / build (as -> ld(splat .ld +
  undefined_*_auto) -> objcopy) / check (SHA1 vs config/check.us.sha, auto-run)
  / expected (asm-differ baseline) / clean; check-env untouched
- config/check.us.sha: committed build-check hash (validation stage 2)
- config/symbols.us.txt: now hand-curated — 15 2D_* -> gfx2D_* (illegal leading
  digit broke as), +D_800629D4 label; header flags re-merge + Ghidra-mirror (G6)
- .gitignore: ignore regenerable splat outputs (asm/, include macros,
  undefined_*_auto.txt); refine the earlier commit-asm/ note
- docs: SETUP.md §4.5 binutils 2.42 = byte-clean (no 2.35 downgrade), §5.3 +
  ledger #8 RESOLVED -G0, §6.3 as-built; memory-map.md gp0 -> -G0 + text/data split
- MILESTONE: make extract && make build && make check -> build/us/SLUS_007.26
  SHA1 143dbb89... == original (BYTE-IDENTICAL), 100% asm, check fails on corruption
- rule R15 (symbol file = curated, valid-identifier build input, Ghidra-mirrored)
- bumps project version 1.4.0 -> 1.5.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R15 — `config/symbols.us.txt` is the curated, build-valid symbol source.** It is hand-curated (seeded from `ExportSymbols.java`, then refined for the build); re-exporting is a **careful re-merge, never a blind overwrite**. Every name must be a valid as/C identifier (no leading digit, etc.). All curations — renames and added labels — are **mirrored back into Ghidra** so a future re-export stays valid and consistent (extends G5/G6). | Phase 5: `2D_*` names broke `as` (leading digit illegal); the fix lives only in this file, which `ExportSymbols` would silently overwrite, and Ghidra must carry the change to stay the static oracle. This recurs at scale in Gen2. |

## PhaseEnd Changelog
**v1.4.0 → v1.5.0** — Phase 5 complete. The repo now **rebuilds `SLUS_007.26` byte-for-byte (SHA1-identical)
from disassembly alone** via `make extract && make build && make check` — splat split → mipsel-`as` → `ld`
(splat linker script) → `objcopy`, at 100% assembly (no C). The build is **compiler-independent** (no
cc1/maspsx invoked), so it is solid before the Phase-6 fingerprint. Two roadmap unknowns fell out for free:
**binutils 2.42 is byte-clean** (the §4.5 ≥2.38 regression risk cleared — no 2.35 downgrade) and **ledger #8
= -G0** (zero `$gp`-relative addressing in the disassembly). The splat config uses splat's own PSX template
(PSYQ, subalign 2, gp 0x80074750) with a single `align: 4` tweak (the word- but not 16-aligned text→data
boundary at vram 0x800629DC). `config/symbols.us.txt` became the hand-curated build input (15 `2D_*`→`gfx2D_*`
for illegal identifiers, +`D_800629D4` label) → **R15**. Decisions (Drew-ratified): the code segment stays
**all-`asm`** (Phase 6 owns the INCLUDE_ASM/.c scaffold per the roadmap), and the regenerable splat outputs
(`asm/`, generated macros, `undefined_*_auto.txt`) are **gitignored**. No tools installed. One rule (R15).

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` absorbed and removed. **Drew commits AND pushes** this PhaseEnd plus the
whole Phase-5 change set (R6/R8). Start a **fresh session for Phase 6 — Compiler fingerprint + first matched
functions**. Keep this file forever.
