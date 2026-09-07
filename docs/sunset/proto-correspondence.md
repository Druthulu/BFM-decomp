# Prototype Research Spike — Correspondence & Go/No-Go (Phase 3.5)

> **Date:** 2026-06-14 · **Evolvable `docs/` layer.** The go/no-go deliverable for Phase 3.5.
> **Question (Drew's directive):** do the two CRC-verified US prototypes *accelerate Gen1 matching*?
> Bytes are the only truth (P9/G3): proto bytes ≠ retail, so proto matches never transfer as matches.

## TL;DR — Verdict: **SPLIT**

| Claim | Verdict | Why |
|---|---|---|
| Protos accelerate Gen1 matching via **symbols / debug-info / labels / readability** | **NO-GO** | Refuted: *neither* proto carries any symbols, source paths, or labels retail lacks (Finding 1). Both have **fewer** names than retail's 952 — the label flow is retail→proto, not proto→retail. |
| Protos are worth **retaining as project assets** | **GO (modest, targeted)** | Sep-8 is a near-duplicate of retail (99.6%) → a **Phase-6 compiler-determinism corroborant**. Aug-31 is the same engine rebuilt (862 1:1 correspondences, shared dispatch architecture) → a **Gen2 overlay/engine asset** (it covers the SC02 region) + a marginal differential-analysis aid. |

**Actions:** (1) Do **not** build proto-based labeling into the Gen1 matching loop — there is no payoff. (2) Keep the imported Ghidra programs + the correspondence artifacts as committed assets. (3) The bounded lift (T6) is **one-way, retail→proto** (name the proto programs from retail to make them navigable for Phase-6/Gen2); nothing is pushed onto the retail DB (G6). (4) All proto-derived data is provenance/confidence-tagged (R13) so a later full-lift phase can verify/extend it without risk to `config/symbols.us.txt`.

## The prototypes

| Build | Main EXE | Size | Load addr | SHA1 | Funcs | PsyQ | Source |
|---|---|---|---|---|---|---|---|
| Retail (SLUS-00726) | `SLUS_007.26` | 413,696 | 0x80010000 | `143dbb89…` | 1726 | 4.0.0 | redump |
| **Sep-8 "Musashi Master"** | `SLUS_007.26` (root) | 413,696 | 0x80010000 | `43006a31…` | 1726 | 4.0.0 | Hidden Palace, CRC 5C24728E |
| **Aug-31 "Musashi Demo"** | `MUSASHI/USA_DEMO.EXE` | 415,744 | **0x80018000** | `6150b0f8…` | 1737 | 4.0.0 | Hidden Palace, CRC 1369DE07 |

- The Aug-31 demo loads 0x8000 higher; its root `LAUNCH.EXE` (24,576 B) is a bootloader owning the low 32 KB. The demo ships `MAIN.CD` (= retail size) + `SC02.CD` only → it is the **SC02 region** (tutorial/Allucaneet area). The Sep-8 master is structurally retail-identical (27 files, full MAIN+SC01–07).
- **All three share PsyQ 4.0.0** (same compiler family — independent corroboration for the Phase-6 fingerprint).

## Method (reproducible)

1. Extract proto main EXEs: `tools/bfm_extract/extract_proto_exe.py` (reuses the general `iso9660` reader; `--dir` for the demo's `MUSASHI/` subdir; magic-only validation) → `extracted/proto/` (gitignored).
2. Import into the `bfm` Ghidra project: `tools/ghidra_import.sh <exe>` (PSX loader auto-detect → auto-analysis incl. PsyQ signatures + DetectPsyQ → PsyQ-4.0 types → DumpProgramInfo).
3. Fingerprint every function (read-only): `tools/ghidra_scripts/DumpFunctionSignatures.java` → `.run/sig.<prog>.jsonl`. Three tiers so the match count is **bracketed**:
   - `h_exact` — SHA1 of raw instruction bytes (strict).
   - `h_norm` — SHA1 of a MIPS-normalized stream: neutralize `j`/`jal` absolute targets, `lui` high-halves, `%lo`/gp-relative address immediates (detected via Ghidra's analyzed references), branch targets → PC-relative offsets; **keep registers (regalloc) + true constants**. The cross-build "same source, relocated" tier.
   - `h_seq` — SHA1 of the mnemonic-only sequence (loose).
4. Correspondence: `tools/match_protos.py` → per-tier counts + 1:1 unique `h_norm` pairs → `.run/correspondence.<proto>-vs-retail.tsv`.

Normalizer validated by anchors: `LzssDecodeSector` and `CdReadRequest` both `h_norm`-match across the Aug-31 address shift + rebuild (0x80018730→0x80020c20, 0x80019a24→0x80021ed0).

## Finding 1 — No debug symbols in either prototype (T2)

Hidden Palace's "no symbols" is now **verified**, not assumed. Per-file byte comparison (the three main EXEs and the three disc images):

- **Main EXEs are stripped identically.** Each carries only two "debug" strings: `\DEBUG.BIN;1` (the known dead loader path) and `SetGraphDebug:level:%d…` (a stock PsyQ format string, present in retail). No source paths, no symbol tables, no function names in any main EXE.
- **Disc-wide, retail and Sep-8 are debug-string-identical.** `^_dbg_RE1L@55;` is in **retail too** (not Sep-8-only); `C:\TIMPACK\OPDEMO0/1.PAT` is in both (shipped opening-demo data); `DEBUG`-substring counts are retail 63 vs sep8 59 — both pure garbage (coincidental ASCII in compressed data).
- **Correction:** an early reconnaissance pass reported "Sep-8 is less-stripped (11× DEBUG + a `dbg_` linker symbol)" as a strong go-signal. That was a **false positive** from naive disc-wide `strings|grep` counting coincidental `X:\`/`DEBUG` byte sequences. Per-file comparison shows parity. (→ rule candidate R14: verify sub-agent/recon summary *counts* against the bytes before relying on them.)

## Finding 2 — Code correspondence (T3)

Retail real functions (≥1 instruction): 1569; substantial (≥8 ins): 1179.

| Proto vs retail | h_exact (subst.) | h_norm (subst.) | h_seq (subst.) | 1:1 unique norm pairs |
|---|---|---|---|---|
| **Sep-8** | **99.4%** | **99.7%** | 99.7% | 1072 (≥8 ins) |
| **Aug-31** | 16.0% | **65.9%** | 99.0% | 690 (≥8 ins) |

- **Sep-8 is a near-duplicate of retail.** Only **3 substantial functions differ at every tier** — the pre-release diff: `DebugMenuHandler` (0x80011144, 30 ins), `CdReadSectorReadyCB` (0x8001a338, **424 ins** — the inline-LZSS-decode CD-read callback), `SaveLoadRoutine` (0x8002b154, 60 ins) — plus 3 pure-relocation diffs. Everything else is **byte-identical at the same address.** Sep-8 therefore adds essentially no new matching information; its worth is corroboration (below).
- **Aug-31 is the same engine, genuinely recompiled.** Low `h_exact` (address-shifted + rebuilt) but **66% of substantial functions are normalized-identical** and 99% share the opcode sequence — two-thirds of the engine is literally the same source→codegen, the rest minor codegen drift. **862 confident 1:1 correspondences** (`.run/correspondence.aug31_USA_DEMO.EXE-vs-retail.tsv`).

## Finding 3 — Shared dispatch architecture, diverged handlers (T4; resolves Open Q#10)

Anchor-bootstrap from the retail debug-menu anchors:

- The demo's game-mode dispatcher is `FUN_80018b48` (matched by opcode sequence to retail `GameModeDispatch` 0x80010b40; relative offset +0xB48 vs retail +0xB40 — the demo mirrors retail's early-code layout, shifted +0x8000). It decompiles to the same pattern: `(*(code*)(&handlerTable)[gameMode])()`.
- **Both handler tables have exactly 18 entries**, in the same order, **with the same internal duplicate** (index[10] == index[15] in both). retail `gameModeHandlerTable` @0x800629F4 ↔ demo table @0x8006AE8C.
- **Slot [7]** (the menu): retail `DebugMenuHandler` 0x80011144 ↔ demo 0x800194cc — **same slot, but the handler code diverged** (no norm/seq match in the demo *or* in Sep-8).

**Q#10 answer:** the demo's "press-Start scene-select" and retail's "L3 debug menu" are the **same architectural feature** (game mode #7 of an identical 18-mode dispatch table) — but the handler is **reimplemented**, and the demo is **unnamed**, so there are **no labels to lift onto retail.** The shared architecture is real; the "free labels" payoff is not.

## Go/No-Go rationale

The spike's hypotheses, each tested against the bytes:

1. *Protos carry symbols / debug info* → **refuted** (Finding 1).
2. *Protos are more readable / easier to decomp* → **no** — equally stripped; no symbols (Finding 1).
3. *The demo's title menu shares retail's debug-menu code → free labels* → **refuted** — same architecture, diverged + unnamed handler (Finding 3).
4. *A second build helps matching* → **only marginally** — Sep-8 ≈ retail (no new info); Aug-31 gives a same-source-different-address differential that can disambiguate a stubborn function, but it is not a force-multiplier and carries no names (Finding 2).

So for the *stated question* — accelerate Gen1 matching — the answer is **NO-GO**. The protos do not shorten the matching loop.

What they **are** worth (hence retain, don't discard):

- **Sep-8 → Phase 6.** A second build that is 99.6% byte-identical to retail is strong evidence the toolchain is deterministic, and it pins exactly which 3 functions changed pre-release. When the compiler triple is pinned and retail is rebuilt, Sep-8 is a free second cross-check.
- **Aug-31 → Gen2.** A second, navigable build of the engine (once named from retail) covering the **SC02 region**, with 862 mapped functions and a confirmed shared dispatch architecture — a head-start for Gen2 overlay/engine RE. Its overlays (MAIN.CD = retail size; SC02.CD) are a second sample for the Gen2 overlay work.

## Actionable outcomes

- **Keep** the imported Ghidra programs (`sep8_SLUS_007.26`, `aug31_USA_DEMO.EXE`) in the `bfm` project and the committed correspondence artifacts.
- **T6 (bounded lift, one-way retail→proto):** apply retail's names onto the proto programs via the 1:1 `h_norm` correspondences (proto-side only), export `config/symbols.proto-sep8.txt` / `config/symbols.proto-demo.txt`. This makes the protos navigable for Phase-6/Gen2 without touching `config/symbols.us.txt`.
- **Do NOT** push proto-derived names/comments onto the retail DB (the protos have nothing retail lacks; G6).
- **Deferred (Drew):** the exhaustive exact+norm+fuzzy adjudication (Version Tracking + manual near-miss review) is a *later* phase. Every proto-derived datum is tagged `unverified` unless independently confirmed against retail, so that phase can verify/extend safely (R13).

## Provenance & confidence (R13)

| Datum | Region | Confidence |
|---|---|---|
| Proto EXE sizes / SHA1s / load addrs / func counts / PsyQ version | PROTO | **verified** (read from the binaries) |
| Correspondence tier counts; 862/1072 1:1 pairs | PROTO↔US | **verified** (deterministic over the dumps) |
| Sep-8 pre-release diff = {DebugMenuHandler, CdReadSectorReadyCB, SaveLoadRoutine} | PROTO↔US | **verified** |
| Demo dispatch anchors: `GameModeDispatch` 0x80018b48, `gameModeHandlerTable` 0x8006ae8c (18), `gameMode` 0x800c1eb6, slot[7] 0x800194cc | DEMO | **verified** (decompiled + table read from the demo binary) — DEMO addresses, NOT valid for US retail |
| Individual retail↔proto function name assignments (T6 output) | PROTO | **unverified** until confirmed vs retail — quarantined to `config/symbols.proto-*.txt` |
