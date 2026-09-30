## §6 Daily command crib

### §6.1 Running builds (native, in the WSL clone)

Claude Code runs inside WSL, so builds are plain native commands — no `wsl.exe` wrapper, no cross-shell quoting:

```bash
cd ~/bfm-decomp
make -j$(nproc) build          # exit status is the build result; nonzero = failed
```

- The shell exit code (`$?`) carries the build result directly — no launcher layer to distinguish from a real failure.
- Output is native UTF-8; logs capture/pipe cleanly with no encoding workaround.
- The clone always lives on ext4 under `~/bfm-decomp`, so builds never accidentally touch a `/mnt` drvfs path.

### §6.2 Canonical compile pipeline (one object)

```bash
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef -Wall -fno-builtin \
    -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C src/foo.c \
  | bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker \
  | python3 tools/maspsx/maspsx.py --aspsx-version=2.56 \
  | mipsel-linux-gnu-as -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o build/foo.o
```

Modern cpp preprocesses → **vintage cc1** compiles to asm → **maspsx** emulates ASPSX quirks → modern GNU `as` assembles. Then `mipsel-linux-gnu-ld` with the splat-generated linker script, `objcopy -O binary` to the PS-EXE, SHA1-compare. cc1 path/flags above reflect the §5.4 first candidate — the exact flag set is **pinned only after Phase-6 fingerprinting** (`-funsigned-char`, `-fpeephole`, etc. are decided then; the cpp defines list is the sotn convention, adjust as evidence dictates).

### §6.3 Planned make targets (Phase 5 builds these; names fixed now)

> **As-built at P33 (B8): `make help` is the live list.** Added since this table: `bootstrap`, `disc-extract`, `extract-all`,
> `check-all` (the R22 contract proof: `make clean && make extract-all && make check-all` → `check-all: 218 passed, 0
> failed of 218`), `sdk-dual`, `report`, `tools-health`, the `sig-*` and `audit-*` families, `print-<VAR>`. The public
> recipe with every expected last line is **`docs/verification.md`**.

| Target | Does |
|---|---|
| `make extract` | splat split per `config/splat.us.*.yaml` → `asm/`, linker scripts |
| `make build` | full pipeline → `build/us/SLUS_007.26`, auto-runs the SHA1 check |
| `make check` | standalone SHA1 manifest verification (byte-for-byte = the only "OK") |
| `make expected` | snapshot `build/us` → `expected/build/us` (asm-differ baseline) |
| `make check-env` | toolchain preflight, exit 0 = environment sane (§4.9) |
| `make clean` | mandatory after ANY `config/` change, before re-extract |

**As-built (Phase 5, 2026-06-14):** all five implemented in the root Makefile. The code is **100% assembly** (the phase's "all-asm byte-match"; the cpp→cc1→maspsx→as `c` path is wired-but-dormant until Phase 6). `make extract && make build && make check` → `build/us/SLUS_007.26` **SHA1-identical** to the original. Config `config/splat.us.exe.yaml` (platform psx, compiler PSYQ, subalign 2, gp_value 0x80074750, main segment `align: 4` so the text→data boundary isn't 16-byte-padded); committed checksum `config/check.us.sha`. Build chain = `as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0` → `ld -T <splat .ld> -T undefined_syms_auto.txt -T undefined_funcs_auto.txt --no-check-sections` → `objcopy -O binary`.

**Fail-closed recipes (Phase-27 T2, 2026-07-15).** The Makefile sets **`.SHELLFLAGS := -ec`** — because `.ONESHELL` sends each whole recipe to ONE `bash -c`, so without `-e` a recipe's exit status is its LAST command's only, and every earlier failure is silently swallowed. That had made `make report`'s middle gates (`lint_symbol_refs`, `progress --audit`, `difficulty`, `dup_report`) into non-gates — the 26-A audit's own thesis (a loud failure nobody counts is as invisible as a silent one) biting the audit's infrastructure. Consequences of the flag, now standing:
- **`make report` is genuinely fail-closed** — any of its gates failing exits non-zero (verified by a negative control: the same broken gate exits 0 under the old `-c`, non-zero under `-ec`).
- **`make check-all` / `extract-all` assert COVERAGE (`pass == N`), not the absence of a failure marker** — the old `fail == 0` form was a *vacuous pass* on an empty pipeline. `check-all`'s `pass=$(grep -c …)` carries `|| true` (grep -c exits 1 on zero matches, which `-e` would otherwise treat as fatal — it would fail check-all exactly when nothing failed).
- **`make check-env` opts OUT** (`set +e` at the top of its recipe) — its contract is accumulate-every-failure-and-report, which `-e` would truncate at the first missing tool. It is the **only** intended opt-out; add `set +e` to a recipe only with the same justification.
- **`make tools-health`** (new) = regenerate the byte-derived sigs (`sig-overlays` + `sig-resident`) then run `audit-corpus` + `audit-cdecl` + `audit-binaries` + `report` + `audit-digest`, fail-closed — the deliberate pre-matching ritual the roadmap's standing invariant names. Deliberately NOT a prerequisite of `report`/`build` (audit-cdecl cross-compiles every C declaration through real gcc, ~minutes). `audit-cdecl` ≈ several minutes; `audit-corpus` ≈ 7 s.
- **`make sig-resident`** (Phase-27 T10; **P31 T0 ELF-seeded** — bootstrap's linear partition fused the +0 data word with the first fn and dropped the last, 144→the true 145; S45 nm-seed pattern, bootstrap fresh-clone fallback) signs the resident flat blob with `sig_image` (byte-derived) so `make audit-corpus`'s second boundary oracle (R34) covers the **resident** — probed clean (0 phantom/truncated). `sig-overlays` derives its payload list from `config/overlays.mk` (not a `0.4.dec` glob, which dropped the 4 SC07 index-1 overlays). `progress.py --fleet` reports a separate **MAIN game-code weighted** line (provisional) — the metrics-contract "main in the denominators", honestly un-folded.
- **`make atlas`** (P31 T5) — the Frontier Atlas regen chain: `family_hseq` → `family_cousins` (+both card emitters) → `tools/atlas_features.py` (per-fn feature layer: 363k rows / 93k distinct bodies in ~21 s; §172b tell detectors live here as importable functions — `li_norm_toks`/`extpair_count`/`dupselect_count`/`sign_mix`/`magic_div_count`, one implementation R33) → `tools/atlas.py` (the survey: cousin units + T1.5 h_seqn merges + calibrated warm tier + seed sweep vs the matched-skeleton pool + kNN graph + evidence joins + lever labels → `.run/atlas.json` + committed `docs/frontier-atlas.md`, partition-asserted). `tools/atlas.py --calibrate` freezes THRESH_WARM/KNN_FLOOR from measured recall/false-accept (seeded RNG, regenerable); `--targets N [--lever L] [--cat C]` emits crack slates. Main joins at the ATLAS layer only (family maps stay non-main by design — four enumerated silent-skip hazards in their consumers).
- **`make sig-main` — REWRITTEN P33 A2 (S86, 2026-09-06):** signs ALL of main's game-code functions at **build-true
  lengths**, Ghidra-free and splat-free: `tools/main_seed_ends.py --map build/us/SLUS_007.26.map` reads each game-code
  object's `.text` input section from the link map and slices it at the object's own `nm` function symbols (the rodata
  islands and the LINKED PsyQ blocks sit BETWEEN objects, so every slice is exact — tiling asserted), emits `0xVRAM NINS`
  seeds, and `sig_image --seeds` hashes the ORIGINAL EXE bytes at those boundaries → `.run/sig.main.jsonl` (809 fns /
  45,150 ins). Needs a built main; without the map it leaves the file alone and says so (R51). `progress.py` weighs main
  by this sig (falling back to the legacy Ghidra sig, and EXITING non-zero when neither exists — it used to print
  "217 binaries" and MAIN 0/0 silently, R32); `dup_report.py` reads it for main; `tools-health` and `make report
  BINARY=main` regenerate it first. **Corrected denominator:** the Ghidra sig's flow-derived boundaries left **3,628
  words of real game code owned by no function** (switch tails after unresolved jump tables, 2–4-ins thunks, and
  `SaveLoadRoutine` = the `case 0:` body inside `func_8002b0b4`), so MAIN game-code weighted is **45,150 / 45,150**, not
  41,534 (P31 S79 had caught one instance, +22). Proof (S86): the derived sig tiles the 15 game-code objects' `.text`
  exactly (45,150 words, no overlaps), is never shorter than Ghidra's for any shared function, and Ghidra covers 41,522
  words all inside that text. The fleet totals moved accordingly (instr 13,488,497 → 13,492,113; distinct 5,816,589 →
  5,820,205); the digest's oracle clause is now DERIVED at render time (`progress.main_oracle_line`, was a literal).
  *(Historical P31 T3 text follows.)*
- **`make sig-main`** (P31 T3 — SUPERSEDED above) signed main's 2,002 game-code stubs at **splat-true lengths**: `corpus.py main --seed-ends` emits `0xADDR NINS` per stub (`corpus.s_ins_count`, the same counter audit() uses) and `sig_image --seeds` treats a seeded nins as authoritative (`[addr, addr+4·nins)`, no `func_end` heuristic — which mis-sliced 3/40 main samples). Verified by a full word cross-check (2,002/2,002 EXE slices == `.s` words; note the `.s` word field is byte-order hex, not the LE value). **Deliberately splat-SEEDED** — the atlas needs the boundaries a match must hit; main's *independent* second oracle stays scoped + deferred in `docs/second-oracle.md` (`sig_is_independent("main")` remains False). `family_remap.vram_of/img_path` special-case `"main"` (derived from `splat.us.exe.yaml`: file0-vram = code-seg `vram − start` = 0x8000F800; target_path), so `stream_words("main", …)` works fleet-wide (verified 25/25 vs `.s`).

### §6.4 asm-differ + baseline discipline

```bash
.venv/bin/python3 tools/asm-differ/diff.py -mwo3 <function>     # -m rebuild, -w watch, -o vs object, -3 three-way
```

- Watch mode works **only** with source and build outputs on ext4, modified from inside Linux (§1).
- **Re-snapshot `expected/` only on green:** run `make expected` exclusively after a build whose check passed. A stale `expected/` makes asm-differ silently diff against the wrong baseline — the classic "phantom regression/phantom match".
- Diff score 0 = matched; anything else is not matched, no matter how close.

### §6.5 decomp.me settings for BFM

- Platform: **PlayStation** (`ps1`); Compiler: **`gcc2.7.2-psx`**. **The project's preset — `docs/decompme-preset.md` (P33 E1):**
  flags `-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -Wa,--aspsx-version=2.56,--expand-div`; name
  `Brave Fencer Musashi (SLUS-00726)`; **requested from decomp.me's maintainers via their GitHub issue template** (there is no
  create button in the UI and no owner delete) by Drew after the flip, with a proving scratch attached — proven before it is
  requested (`docs/decompme-preset.md` §5 carries the ready-to-paste issue).
- **decomp.me does NOT run our binaries** (measured 2026-09-07 from `decompme/compilers`): its image is old-gcc **0.13** +
  maspsx **`86ccd7d8`** with `as` = a maspsx `--run-assembler` wrapper (so `-Wa,` args reach maspsx); we run old-gcc 0.17 +
  maspsx `874855c5`. Both deltas measured text-identical on the probe; the maspsx delta is gated on aspsx < 2.30 anyway.
  **`tools/decompme_replica.sh`** rebuilds decomp.me's toolchain under `.run/decompme/` and proves a function through it
  locally (PASS on `func_80018F20`, 26/26 words); `--upstream` reports when decomp.me's pins drift.
- **Do NOT use the SOTN preset** (`Castlevania: Symphony of the Night` / `gcc 2.6.3-psx` / `psyq_263_221`) — wrong era, guaranteed near-miss diffs.
- decomp.me's API is Cloudflare-challenged (403 to scripts) — scratch searches/uploads needing the API must be done manually in a browser
  (the one-time manual BFM search is ledger row 14, closed by the E1 browser session).
- **Outcome (P34 task 2, 2026-09-08 — Drew's browser session):** the proving scratch <https://decomp.me/scratch/mIu4d> (`func_80018F20`,
  target = the `--gas` paste, **100% / score 0** on the first compile after the flags were entered); the preset request
  **<https://github.com/decompme/decomp.me/issues/2106>** ("[PRESET] Create Compiler Preset - Brave Fencer Musashi (SLUS-00726)", opened
  2026-09-08 18:05Z, state open); the manual search (row 14) found no other BFM scratch. **Pending on decomp.me's maintainers:** the
  preset's creation — record its id / URL here when it appears (`https://decomp.me/api/preset`).

### §6.6 Matching a function (INCLUDE_ASM → C; the NON_MATCHING guard) — As-built Phase 6

Phase 6 flipped the text segment to splat's `c` type: `src/800.c` is one
`INCLUDE_ASM("asm/nonmatchings/800", <fn>);` stub per function (file-scope `__asm__`, pulls
the per-function `asm/nonmatchings/800/<fn>.s` in at assembly time). The build is **byte-identical
at 100% INCLUDE_ASM**; matching replaces stubs with C one function at a time. Harness as-built:
`include/common.h` (committed prelude), `diff_settings.py` (asm-differ, arch `mipsel`, object mode
vs `expected/`), `tools/decompile.py` (m2c wrapper), `-Map build/us/SLUS_007.26.map` for symbol lookup.

📓 **Consult `docs/matching-cookbook.md` before/while matching** — the evolvable catalog of reusable
compiler idioms (asm↔C) and "what makes gcc emit X" techniques. These recur across nearly every
function; shaping the C toward them up front saves asm-differ rounds. **Add to it as you learn.**

Cross-refs (HOW-TO lives in the cookbook / PhaseEnds, not duplicated here): per-module **-O0**
overrides — cookbook §6; the **rodata island** — cookbook §8; PsyQ **library linking** — cookbook
§9.1–§9.5; **symbol curation** (rename in Ghidra + `config/symbols.us.txt`, re-extract) — rule R15.

**The loop (per function):**
1. Scaffold: `tools/decompile.py <fn>` (m2c) — or Ghidra `get_code` via MCP for complex ones.
2. Replace the `INCLUDE_ASM(... <fn>);` line with the C function body — **in the TU that owns
   the function's address** (P31 S72; main's game code is THREE TUs, not one):

   | vram | TU | asm path | owns `.rodata` span |
   |---|---|---|---|
   | `0x800123F0-0x8002B0B4` | `src/800.c`   | `asm/nonmatchings/800`   | A `0x80072A38-0x80072C70` |
   | `0x8002B0B4-0x80035270` | `src/800_b.c` | `asm/nonmatchings/800_b` | B `0x80072E44-0x80073140` |
   | `0x80035270-0x8003A444` | `src/800_c.c` | `asm/nonmatchings/800_c` | C `0x800732A0-0x8007344C` |

   **This is load-bearing for any function with a `switch`:** one code object contributes
   exactly ONE contiguous `.rodata` run, so the TU decides which jump-table span the body's
   table lands in. Put a span-B function in `src/800.c` and you re-create the double-emit
   that cookbook §426 exists to describe. Declarations shared across the three TUs live in
   `src/800_shared.h` (§431).
3. Iterate: `.venv/bin/python tools/asm-differ/diff.py -mo <fn>` until **score 0** (`-m` rebuilds;
   `-w` watch, `-3` three-way). decomp-permuter for stubborn near-misses.
4. `make check` must stay SHA1-green (the whole-binary gate); commit-accumulate (R8).
5. If the symbol name changes, rename in Ghidra + `config/symbols.us.txt` and re-extract (R15/G6/R9).

**Matched** → the C replaces INCLUDE_ASM directly (byte-identical, no guard).

**Correct-but-not-yet-matched C** → keep it OUT of the default build behind the guard (G4):
```c
#ifdef NON_MATCHING
    /* correct-but-unmatched C */
#else
INCLUDE_ASM("asm/nonmatchings/800", <fn>);
#endif
```
The default build (no `-DNON_MATCHING`) links the asm, so `make check` never goes red on
non-matching C (G4). `M2CTX`/`PERMUTER` builds are already handled in `include/include_asm.h`.
`expected/` is the asm-differ baseline (a green-build snapshot = original bytes) — re-`make expected`
**only after a green build** (§6.4), never mid-match.

---

### §6.7 Binary-agnostic toolchain (Phase 9) — `make build BINARY=<alias>`

The toolchain builds any binary, not just the EXE. The Makefile holds a data-driven `BINARIES`
list of **alias keys**; each alias has a namespaced `<alias>_*` variable set, and
`make build [BINARY=<alias>]` selects one (default `main`). `main` = the retail EXE `SLUS_007.26`;
**its artifact paths are preserved verbatim** (`build/us/`, `config/splat.us.exe.yaml`,
`config/check.us.sha`, `config/symbols.us.txt`, `.run/sig.SLUS_007.26.jsonl`) so its rebuild is a
byte-exact no-op. `make report`/`asm-differ` are binary-selectable too (see below).

**Adding a second binary (Phase 10+):** append the alias to `BINARIES` and define its `<alias>_*`
block. New binaries use the clean convention — `config/splat.<bin>.yaml`, `build/<bin>/`,
`config/check.<bin>.sha`, `config/symbols.<bin>.txt`, `.run/sig.<bin>.jsonl` — plus per-binary
`<bin>_VRAM_BASE` (the fileoff→vram delta; overlays are **not** `0x8000F800`-based) and
`<bin>_TEXT_LO/HI`. The EXE-only steps (the 9 PsyQ `psyq_integrate` calls, `ld_interleave`) are
gated under `ifeq ($(BINARY),main)`; a second binary supplies its own.

**Required parameters — no EXE default an overlay could inherit** (the phase's #1-risk mitigation;
a miss fails loud, never a silent wrong-address-later):
- `psyq_link.py` / `psyq_identify.py` / `psyq_link_lib.py` / `psyq_link_region.py`: `--vram-base <hex> --exe <path>`
- `psyq_integrate.py`: `--vram-base --exe --symbols <file>` (flags go BEFORE the positionals)
- `gen_lib_subsegs.py` / `make_snd_used.py` / `make_apicard_used.py`: `--vram-base --exe` (EXE-curation tools — these CLI flags *default* to the EXE's values for convenience, but thread explicit values down to the now-required pipeline)
- `ld_interleave.py`: `--order <address-ordered leaf list>` for **main** since P31 S72 — its island is a 7-piece sandwich that `--front/--tail` cannot express (a `*.data.o` leaf contributes its `(.data)`, a code-object leaf its `(.rodata)` carve). Overlays keep `--front <obj> --tail <obj>` (the sandwich `.data` objects) + `--section .<binary>` (Phase 26: default `.main` = the EXE; overlays with a §8 jtbl-rodata carve pass their own section — derives the `<binary>_TEXT/DATA/RODATA/DATA2/BSS` symbol prefix)
- `split_src_region.py`: `--symbols <file>`
- report scripts (`progress.py` / `difficulty.py` / `dup_report.py`): `--binary <alias>` (default `main`)
- asm-differ: select via the **`BFM_BINARY`** env var (default `main`); `diff_settings.py` maps alias → `{baseimg, myimg, mapfile}`

**Proof it's a no-op:** the EXE rebuilds SHA1 `143dbb89…` through the parameterized path **with AND
without** the SDK objects, `make report` reproduces the counts, and a deliberately wrong
`--vram-base` (e.g. `make build main_VRAM_BASE=0x8000F804`) diverges to a non-`143dbb89` hash
(the negative control — proves the param is load-bearing, not accepted-and-ignored).

**First instantiation — `resident` (Phase 10):** the always-resident engine blob
(`extracted/retail/MAIN.CD.dir/FILE_010.dir/1.1`, 365,404 B, vram `0x800CEDF8`, type-1 uncompressed)
is the project's second binary — `make build BINARY=resident` → `8e17e02f…` at 100% INCLUDE_ASM.
The reusable **flat-blob recipe** (every Gen2 overlay follows it):
- **Per-binary source roots + OBJS prune** — main lives at the repo-level `asm/`+`src/`; a second
  binary nests at `asm/<bin>/`+`src/<bin>/` (`<bin>_ASM_DIR`/`<bin>_SRC_DIR`). The `OBJS` glob is
  scoped to the active root with a `$(BINARIES)`-derived prune (`-not -path 'asm/<sibling>/*'`,
  guarded by `$(if $(filter $(ASM_DIR)/%,…))`) so main's root doesn't sweep in nested siblings.
- **`build_path: build`** in the `<bin>` yaml (NOT `build/<bin>`) — splat writes the `.ld`'s object
  paths under `$(build_path)`, and the Makefile pattern rules build them at `build/asm/**`+`build/src/**`;
  only `elf_path`/`ld_script_path`/output live under `build/<bin>/`. Per-binary `undefined_*_auto_path`
  under `build/<bin>/` (splat options) + `<bin>_UNDEF_SYMS/FUNCS` aliases keep main's at the root verbatim.
- **Flat-image splat config** — NO `header` segment (overlays carry no PS-X EXE header), NO `gp_value`
  (-G0; verify zero `($gp)` in the disasm), single `code` segment at `vram: <base>`, stacked
  `symbol_addrs_path: [config/symbols.us.txt, config/symbols.<bin>.txt]` (the shared EXE globals the
  blob references + blob-local names). Iterate text/data boundaries against `make check` (Phase-5 method).
- **A leading data word *before* the code** (e.g. the resident's 1-word header `0x00000036` at the very
  base, code at +0x04) fights `section_order: [.rodata,.text,.data,.bss]` (which puts `.data` after
  `.text`). Emit it as **`rodata`** (no-dot type → asm rodata, placed FIRST) — a 1-word analogue of
  main's rodata-island, **no `ld_interleave` needed**.
- **§8 jtbl-rodata carve (Phase 26 — only when a jr-function is matched):** an overlay's gcc switch jump
  tables sit in a contiguous `.rodata` island at the TAIL of the blob. Matching a jr-function makes its C
  emit that jtbl into `.rodata` (floated to the front by `section_order`) while the raw copy stays in the
  data tail → duplicate. Fix = carve the fn's jtbl into a dotted `[.rodata, <code-subseg>]` subseg + set
  `<bin>_JTBL_INTERLEAVE := --front <pre>.data.o --tail <post>.data.o …` in `config/overlays.mk` (a
  `$(strip)`-guarded `make extract` branch then runs `ld_interleave --section .<bin>`). The C body needs
  `canon_sig_reconcile` first. Full recipe + gotchas: cookbook **§8a**. (No carve ⇒ this is a no-op.)
- Per-binary `<bin>_GHIDRA_PROG` → `make sig-refresh BINARY=<bin>`; `diff_settings.py` + the three
  report scripts gain a `<bin>` entry; `make expected` is per-binary-safe (merge-copy, no sibling clobber).

**Module-class binaries — `md_*` (P30 S44/S45; the §S44 loader table, `docs/memory-map.md`):**
the small type-1 payloads (per-actor modules, the SC07 endgame pair) load at their OWN statically
derived slots (A `0x800CAE08` · B `0x800CCB1C` · boot/resident `0x800CEDF8` · SC07 `0x801A00D8`),
not the shared overlay slot. Onboard with **`tools/new_binary.sh <alias> <payload> <VRAM>
[TEXT_LO]`** (the generalized `new_overlay.sh`; registry `config/modules.mk` / `MODULE_BINARIES`).
Module-specific facts the recipe encodes:
- **TEXT_LO ≠ 0** (the §154 module-id law: payload word0 is a global module id, sometimes followed
  by a fn-ptr table and/or data): derive per payload from the first-prologue scan (`27BDxxxx`) and
  the min fn-ptr-table target — NOT min-table alone (functions can precede the lowest table entry:
  the SC07 pair's real code start is 0xFC/0x158, their min table targets 0x930/0x370).
- **The header carve is a dot-typed `.rodata` PAIRED with the c segment** (same name), never a
  standalone `rodata, hdr` object and never `bin`: a module header can hold a function's JUMP
  TABLE, whose `.L` labels only resolve when jtbl and function assemble in the SAME object (the
  EXE `[0x63238,.rodata,800]` precedent); `bin` assets link in the data block (wrong placement).
- **A4 symbol-window law:** a module whose window lies INSIDE another binary's symbol region must
  NOT stack that binary's symbol file — the boot trio (`0x800CEDF8`) omits `symbols.resident.txt`
  (DsMix @0x800D1BD8 minted a phantom fn boundary in md_MAIN_011 before this).
- **`make sig-modules`** signs every module at its own vram/TEXT_LO, seeding from the built ELF's
  `func_*` symbols when a build exists (bootstrap's linear partition glues adjacent functions
  around jtbl dispatch); fresh-clone fallback is `--bootstrap`, self-healing on the next run.

### §6.8 Cross-binary dedup & code-sharing (Phase 11) — "one match unlocks many"
Full how-to in `docs/matching-cookbook.md` §11. Command crib:
- **`make sig-overlays`** — Ghidra-FREE sign all 134 location overlays (`SCxx 0.4.dec`) at the shared overlay
  vram `0x80128158` via `tools/sig_image.py` → `.run/sig.ov_<SCxx>_<nnn>.jsonl` (gitignored; ~27 s). Re-run when
  overlays change. (`make sig-refresh` still does the Ghidra-imported EXE/resident sigs.)
- **`make report`** (gated `BINARY=main`) runs **`tools/dup_report.py --cross`** → `docs/duplicates.cross.md`:
  cross-binary duplicate groups across main + resident + all overlay sigs, ranked by collapsible bytes (the
  Phase-12/13 work queue), + **`tools/dedup_integrate.py --check`** (the byte-honesty gate — fail-closed if a
  registered share's sig hash drifts).
- **Share a matched fn across binaries**: author the body ONCE as a macro in `src/shared/<fn>.h`, instantiate at
  each site in each binary's `.c`, register the group in **`config/dedup.us.yaml`** (`{id, tier, hash, source,
  func, members:[{binary, vram, name}]}`). Byte-gate = per-binary `make check`. `h_exact` = risk-free; `h_norm`
  = candidate (accept only if every claiming binary stays byte-identical). NOT an object swap — game-code fns are
  interior to one object per binary (cookbook §11 / deviation D1).
- `tools/sig_image.py`: `h_exact` byte-matches the Ghidra dumper (validated 100% on the resident contiguous set);
  `h_norm` is self-consistent within the overlay fleet (not Ghidra-byte-exact — D2); overlay boundaries via linear
  partition + `detect_code_end` (BFS fails — overlays dispatch via function-pointer tables, not `jal`).
- **PsyQ provenance (R24)**: the resident is PsyQ **4.7** (`tools/psyq/conv47/`, sha-recorded in
  `tools/psyq_CHECKSUMS.sha256`) — Phase 12 links its embedded SDK code from 4.7, not the EXE's 4.0 libs.

