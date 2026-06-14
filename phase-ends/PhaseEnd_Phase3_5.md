# PhaseEnd — Phase 3.5: Prototype Research Spike
**Date:** 2026-06-14 · **Project Version:** 1.3.1 · **Phase Status:** Complete

> Inserted half-phase (Drew's directive at Phase-3 close): assess whether the two CRC-verified US
> prototypes accelerate Gen1 matching, **before** the build toolchain (which resumes as Phase 4).
> Filename uses an underscore (`Phase3_5`) so the glob load order sorts Phase3 → Phase3_5 → Phase4.

## Build Log

**Files created/changed and complete — do not recreate:**
- `tools/bfm_extract/extract_proto_exe.py` — extract a main EXE from a prototype disc; reuses the general
  `iso9660` reader, `--dir` for subdirectories (the demo's real EXE is in `MUSASHI/`), magic-only
  validation (proto sizes/SHA1s differ from retail). Companion to the retail-locked `extract_exe.py`.
- `tools/ghidra_import.sh` — reusable headless import of any PS-X EXE into the `bfm` project (PSX-loader
  auto-detect → auto-analysis incl. PsyQ signatures + DetectPsyQ → PsyQ-4.0 types via `ImportPsyqGdt.java`
  → `DumpProgramInfo.java`). Precondition: MCP server stopped (exclusive project lock).
- `tools/ghidra_scripts/DumpFunctionSignatures.java` — **read-only** per-function 3-tier fingerprint
  (`h_exact` raw bytes / `h_norm` MIPS-normalized / `h_seq` mnemonic-only) + ordered call targets →
  `.run/sig.<prog>.jsonl`. Consumed by `match_protos.py`.
- `tools/match_protos.py` — cross-binary correspondence: per-tier counts, 1:1 unique `h_norm` pairs,
  anchor sanity check; emits `config/symbols.proto-*.txt`. Consumes the `.run/sig.*.jsonl` dumps.
- `docs/proto-correspondence.md` — **the deliverable**: the evidence-backed go/no-go report.
- `config/symbols.proto-sep8.txt` (953) / `config/symbols.proto-demo.txt` (682) — retail names mapped onto
  the protos via 1:1 `h_norm` correspondence. **R13-tagged: proto-side, UNVERIFIED, never merge into
  `config/symbols.us.txt`.** Phase-6/Gen2 navigation aid.
- `docs/memory-map.md` — added the **Phase-3.5 block** (proto correspondence summary + DEMO dispatch
  anchors), resolved **Open Q#10**, upgraded §5 proto notes ("no symbols") to **VERIFIED**.
- `.gitignore` — nested allowlist for `extracted/retail/` (3 committed files re-included); `extracted/proto/`
  fully ignored.
- `tools/bfm_extract/extract.py` · `extract_exe.py` · `crosscheck.py` — DEFAULT output/extracted paths
  → `extracted/retail` (per-ROM subfolders).
- `tools/ghidra_mcp_start.sh` — `PROG` now `${1:-SLUS_007.26}` (serve a prototype by passing its name).
- **Renamed (git mv, history preserved):** `extracted/{SLUS_007.26,manifest.jsonl,manifest.sha1}` →
  `extracted/retail/` (the extracted/ reorg; the 34 gitignored bulk items moved alongside).

**Local artifacts (gitignored / outside the repo — present on this machine; a fresh clone redoes them):**
- `extracted/proto/sep8_SLUS_007.26` (413,696 B, sha1 `43006a314513d962528ddc90ee496c781867366a`) +
  `extracted/proto/aug31_USA_DEMO.EXE` (415,744 B, base 0x80018000, sha1
  `6150b0f839972ac52214e3510e7d7f0e2c194624`) — extracted proto main EXEs.
- Ghidra `bfm` project now holds **3 programs**: `SLUS_007.26` (retail) + `sep8_SLUS_007.26` (1726 funcs)
  + `aug31_USA_DEMO.EXE` (1737 funcs); all PsyQ 4.0.0; R9-verified. (The retail DB was NOT modified.)
- `extracted/retail/` bulk (the Phase-2 disc extraction, moved here); `.run/sig.*.jsonl` ×3,
  `.run/correspondence.*.tsv` ×2, `.run/proto-import.log` — scratch.

**Tools/packages installed:** None (used the existing Ghidra 12.1 + Python stack).

**Verification results (literal):**
- **Proto extraction:** sep8 `SLUS_007.26` 413,696 B, sha1 `43006a31…`; aug31 `USA_DEMO.EXE` 415,744 B,
  base 0x80018000, sha1 `6150b0f8…`; both `PS-X EXE` magic verified. `extracted/` reorg: `extract.py
  --verify --out extracted/retail` **PASS** (manifest paths are out_root-relative → move transparent);
  git shows 3 renames; **zero ROM bulk staged**.
- **Ghidra import:** sep8 **1726 funcs / PsyQ 4.0.0**, aug31 **1737 funcs / PsyQ 4.0.0**; both
  `Import succeeded` + **R9-verified** by read-only re-open.
- **T2 (debug-info):** main EXEs string-identical (retail=sep8=351, aug31=331; only `\DEBUG.BIN;1` +
  `SetGraphDebug`); disc-wide retail/sep8 debug-string-identical (`_dbg_RE1L@55`, `C:\TIMPACK\` in **both**;
  `DEBUG`-substrings retail 63 / sep8 59 = garbage). **No symbols in any proto — Hidden Palace claim
  VERIFIED; the recon "Sep-8 less-stripped" signal REFUTED.**
- **T3 (correspondence, substantial ≥8 ins):** sep8 h_exact **99.4%** / h_norm **99.7%** / h_seq 99.7%,
  1072 1:1 pairs; aug31 h_exact 16.0% / h_norm **65.9%** / h_seq 99.0%, 690 1:1 (862 all sizes). Normalizer
  validated by anchors (`LzssDecodeSector`, `CdReadRequest` matched across the demo's shift+rebuild).
  Sep-8→retail pre-release diff = exactly **3 substantial funcs** (`DebugMenuHandler`,
  `CdReadSectorReadyCB` 424 ins, `SaveLoadRoutine`).
- **T4 (anchor):** demo dispatch table @0x8006AE8C = **18 entries** (= retail's 18, same idx[10]==idx[15]
  duplicate); demo `GameModeDispatch` 0x80018b48, `gameMode` 0x800c1eb6; slot **[7]** 0x800194cc (= retail
  `DebugMenuHandler` slot, **code diverged**). **Q#10 resolved.**
- **T6:** `config/symbols.proto-sep8.txt` 953 names, `config/symbols.proto-demo.txt` 682 names, R13-tagged.

**Milestone achieved:** `docs/proto-correspondence.md` states an evidence-backed go/no-go — **SPLIT:
NO-GO** as a Gen1 label/symbol accelerator (no symbols in either proto, *verified* by byte compare; the
free-label lead refuted), **GO** to retain Sep-8 (Phase-6 compiler-determinism corroborant; 99.6%
byte-identical, 3-function pre-release diff) and both (Gen2 assets) — backed by a per-proto debug-info
inventory, quantified retail↔proto correspondence (Sep-8 99.6% / Aug-31 66% norm, 862 1:1), and the
Aug-31 anchor alignment (18-entry dispatch table located, slot[7] mapped) resolving Q#10; proto-side
labels imported (`config/symbols.proto-*.txt`).

**Next:** Phase 4 — Matching-build toolchain (WSL). Start with: apt toolchain + Python 3.12 venv +
splat64 installed; submodules (asm-differ, m2c, maspsx, decomp-permuter) added and pinned.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| Spike outcome | open (free-label lead hypothesized "GO") | NO-GO for Gen1 accel; GO only as asset | Bytes refuted the symbol/label hypothesis (T2); protos have FEWER names than retail's 952 |
| `extracted/` layout | single `extracted/` root | reorganized → `extracted/retail/` + `extracted/proto/` | Drew directive mid-phase (multiple ROMs now); inserted cleanup task |
| T6 lift direction | name protos **and** annotate retail w/ proto provenance | one-way retail→proto only; **retail untouched** | verdict: protos add nothing retail lacks → nothing to annotate; preserves crown-jewel DB (G6) |
| T6 application | apply names in the Ghidra proto programs + export | `config/symbols.proto-*.txt` only; **Ghidra-side naming deferred** | premature given NO-GO (protos are future assets); the text file is the durable record |
| T2 xref step | map debug strings → functions via MCP | moot — no new debug strings exist in any main EXE | negative finding; nothing to map |
| Recon debug signal | (4th explore agent: "Sep-8 = GO, strong") | refuted | naive disc-wide grep counted coincidental `X:\`/`DEBUG` byte sequences (→ R14) |
| `BfmVtExactMatch.java` (Version Tracking) | available for T6 on GO | not created/needed | correspondence computed in Python; the bounded lift needs no Ghidra writes |
| MCP for the spike | live MCP for xref/anchor | mostly standalone read-only `analyzeHeadless` | lock-serialized + avoids `/mcp` re-attach churn; only one decompile needed |

## Commit Message
```
feat(phase-3.5): prototype research spike — go/no-go (protos don't accelerate Gen1 matching)

- extract_proto_exe.py: subdir-aware proto main-EXE extraction (reuses iso9660); extracted
  sep8 SLUS_007.26 (413,696 B) + aug31 MUSASHI/USA_DEMO.EXE (415,744 B, base 0x80018000)
- ghidra_import.sh: reusable headless import; both protos imported into the bfm project
  (sep8 1726 funcs, aug31 1737 funcs, both PsyQ 4.0.0), R9-verified
- DumpFunctionSignatures.java + match_protos.py: 3-tier (exact/norm/seq) cross-binary
  correspondence; MIPS normalizer validated by anchors
- FINDINGS: (T2) no debug symbols in either proto — Hidden Palace "no symbols" VERIFIED;
  recon "Sep-8 less-stripped" REFUTED by per-file byte compare. (T3) Sep-8 99.6% byte-identical
  to retail (only 3 funcs differ: DebugMenuHandler, CdReadSectorReadyCB, SaveLoadRoutine);
  Aug-31 66% norm-identical, 862 1:1 correspondences. (T4) demo shares retail's 18-entry
  game-mode dispatch architecture but the handler code diverged — Q#10 resolved
- VERDICT (docs/proto-correspondence.md): NO-GO as a Gen1 label/symbol accelerator; GO to retain
  Sep-8 (Phase-6 compiler corroborant) + both (Gen2 assets); proto-side labels in
  config/symbols.proto-{sep8,demo}.txt (R13-tagged, never feed symbols.us.txt)
- reorg extracted/ into per-ROM subfolders (extracted/retail/, extracted/proto/); nested
  gitignore allowlist; extractor defaults updated; manifest --verify PASS
- memory-map.md: Phase-3.5 block + demo dispatch anchors; Q#10 RESOLVED; §5 proto notes VERIFIED
- ghidra_mcp_start.sh: PROG arg to serve a prototype
- rules R13 (proto-provenance/confidence tagging), R14 (verify recon counts vs bytes)
- bumps project version 1.3.0 -> 1.3.1
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R13 — Proto-provenance & confidence tagging.** Every prototype/cross-build-derived datum carries source build (`sep8`/`demo`/…), match tier (`exact`/`norm`/`fuzzy`), and verification status (`verified-retail` only if independently confirmed in retail; else `unverified`). `config/symbols.us.txt` and the curated retail Ghidra DB receive ONLY `verified-retail` data; unverified proto-derived names live exclusively in `config/symbols.proto-*.txt` + reports (never merged into `symbols.us.txt`); retail comments carrying proto info are prefixed `[PROTO:… UNVERIFIED]`. | Drew directive 2026-06-14: keep the deferred full-lift safe and never corrupt the crown-jewel symbol list with uncertain cross-build data. Extends G5/G6. |
| **R14 — Verify recon/sub-agent summary counts against the bytes.** A sub-agent's or reconnaissance pass's summarized counts/signals are claims, not ground truth; confirm against the actual bytes before relying on them. | A recon "Sep-8 is less-stripped (strong GO signal)" was a false positive — coincidental `X:\`/`DEBUG` byte sequences in compressed data — refuted by per-file byte comparison. Extends G1/X2. |

## PhaseEnd Changelog
**v1.3.0 → v1.3.1** — Phase 3.5 (inserted prototype research spike) complete. Both US prototypes extracted,
imported (PsyQ 4.0.0), and diffed against retail via a new read-only 3-tier signature pipeline. **Go/no-go:
the prototypes do NOT accelerate Gen1 matching** — neither carries symbols/debug-info/labels retail lacks
(*verified*; the demo's scene-select shares retail's 18-mode dispatch *architecture* but its handler code
diverged and is unnamed, so the "free labels" lead is refuted). They are **retained** as a Phase-6
compiler-determinism corroborant (Sep-8 = 99.6% byte-identical to retail; the entire pre-release delta is 3
functions) and Gen2 assets (Aug-31 = the same engine rebuilt, SC02 region, 862 1:1 correspondences). Open
Q#10 resolved. `extracted/` reorganized into per-ROM subfolders. New reusable tooling (proto extractor,
headless importer, signature dumper + matcher). Rules R13 (proto-provenance tagging) and R14 (verify recon
vs bytes). **Deferred (Drew):** the exhaustive Version-Tracking + manual near-miss full-lift to a later phase.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` absorbed and removed. **Drew commits AND pushes** this PhaseEnd
(R6/R8). Start a fresh session for **Phase 4 — Matching-build toolchain**. Keep this file forever.
