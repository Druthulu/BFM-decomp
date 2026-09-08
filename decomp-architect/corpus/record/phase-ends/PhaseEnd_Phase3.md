# PhaseEnd — Phase 3: File-loader & overlay-map RE (+ PCSX-Redux harness)
**Date:** 2026-06-14 · **Project Version:** 1.3.0 · **Phase Status:** Complete

## Build Log

**Files created/changed and complete — do not recreate:**
- `tools/ghidra_mcp_start.sh` / `ghidra_mcp_stop.sh` / `ghidra_mcp_verify.sh` — oracle lifecycle: start
  detached headless MCP server / clean save+stop (the ONLY way headless MCP writes persist) / read-only
  R9 verify. Used every RE session.
- `tools/ghidra_scripts/BfmMcpServer.java` — headless MCP server + commit-on-clean-shutdown; run by `start.sh`.
- `tools/ghidra_scripts/GetSymbolAt.java` — read-only symbol probe consumed by `verify.sh` (R9).
- `tools/ghidra_scripts/ImportOverlay.java` — headless: loads the proven resident blob (→0x800CEDF8) +
  one location overlay (→0x80128158) into the program (`RAM` block, convertToInitialized+setBytes);
  idempotent. (T7)
- `tools/ghidra_scripts/VerifyOverlay.java` — read-only R9 check that the imported blob bytes persisted. (T7)
- `tools/ghidra_scripts/ExportSymbols.java` + **`config/symbols.us.txt`** — headless export of all 967
  USER_DEFINED symbols (PsyQ-signature names + manual RE) to committed text — the durable, diffable,
  re-importable record of the RE work (the `.rep` is gitignored); Phase-5 splat input. (phase-close)
- **`dumps/INDEX.md`** + `dumps/*.bin` — the 28-dump live RAM corpus, **committed** (H1 relaxed while
  private; static, not regenerable, off-machine backup); INDEX maps each dump → state. (phase-close)
- `.gitignore` — added `/tools/pcsx-redux/` (AppImage), `/.run/` (runtime scratch); dumps committed.
- `.claude/settings.local.json` — SessionStart hook that auto-starts the oracle. (T0)
- **`/tmp` → project-local migration:** `ghidra_mcp_start.sh`/`stop.sh` + `BfmMcpServer.java` now use
  `~/bfm-decomp/.run/{ghidra-mcp.log,mcp-stop.req}` (no `/tmp`); full start/stop/save/R9 cycle re-certified. (R12)
- `docs/memory-map.md` — **the phase's main written deliverable.** Added: the T1 "imported into Ghidra"
  block; the T2 (CdRead chain) / T3 (LIST.CD cache+lookup) / T4 (LZSS staging) / T5 (US load addresses) /
  T6b (MILESTONE proof) blocks; **§4.3 overlay-map table (13 area-states + the loader model)**; §3.4
  player-state promoted to `verified` (gold/HP/BP/day/hour/tiredness-raw) + refutations; §2.3
  `saveHeaderTemplate`; §5 debug-menu dispatch; Open Questions **#1,#3,#4,#5,#6,#8,#9,#12 resolved**;
  SLUS-90029 corrected (FF8 demo, not BFM).
- `docs/SETUP.md` — §3 PCSX-Redux as-built (Windows-native + WSL web-API bridge); ledger #4 RESOLVED
  (web server :8081, dump URL).
- `phase-ends/CURRENT_PHASE.md` — **absorbed into this file and deleted** (P8).
- `phase-ends/PhaseEnd_Phase3.md` — this file.

**Local artifacts (gitignored / outside repo — present on this machine, do NOT recreate; a fresh clone redoes them):**
- `~/bfm-decomp/ghidra/bfm.{gpr,rep}` — the saved Ghidra project. `SLUS_007.26` now carries the T1 seeds
  **plus ~50 Phase-3 symbols**: loader cluster (`LoaderInitFileTable`, `CdReadRequest`,
  `CdReadStateMachine`, `CdReadSectorReadyCB`, `CdQueueBusy`, `cdReq_*` control block), resource loader
  (`ResourceLoadStateMachine`, `ResourceGetCdLoc`, `resourceIdMap`, `resLoad_*`), `cdFileLocTable`,
  `listCdBuffer`, `lzss_sectorStagingBuf`, `StreamLoadStateMachine`, `loadDestPtrTable`,
  `GameModeDispatch`+`gameModeHandlerTable`, `DebugMenuHandler`, `SaveLoadRoutine`, `saveHeaderTemplate`,
  `debugBinPresent`, player-state fields — **plus 2 imported memory blocks** (resident blob @0x800CEDF8,
  tut_forest overlay @0x80128158). R9-verified; DB saved (clean shutdown).
- `tools/pcsx-redux/PCSX-Redux-HEAD-x86_64.AppImage` — Linux AppImage (downloaded; **NOT used** — WSLg
  display + WSL controller failed; the Windows-native build is the actual oracle). Gitignored.
- `disks/` — 2 CRC-verified US prototypes (**Aug-31-1998 "Musashi Demo" 1369DE07**, **Sep-8-1998 "Musashi
  Master" 5C24728E**) + a "Squaresoft on PlayStation Vol.2 (FF8 Demo)" disc. Gitignored.

**Tools/packages installed:**
- **PCSX-Redux** (runtime oracle). The Linux AppImage was fetched to `tools/pcsx-redux/` but is unused;
  the **Windows-native build** (`distrib.app/.../dev-win-x64`) is what runs — web server on :8081, reached
  from WSL at **172.17.208.1:8081** (NAT gateway). Ships OpenBIOS (no BIOS dump needed).
- **usbipd-win** (Windows, installed by Drew) — attempted DualSense→WSL passthrough; abandoned (WSL2 kernel
  has no `CONFIG_HID_PLAYSTATION`/`joydev`) in favour of the Windows-native emulator.

**Verification results (literal):**
- **MILESTONE byte-proof (live PCSX-Redux RAM):** resident `MAIN.CD/FILE_010/1.1` @0x800CEDF8 = **18,788-byte
  contiguous exact prefix, sha1 `dbc55765593d3c157965a22af5808990714dbae9`** (RAM slice == extracted, EQUAL);
  overlay `SC01/FILE_077/0.4.dec` @0x80128158 = **389,400-byte contiguous exact prefix, sha1
  `8e40afab29200f00752573bfc28f9a8676000f85`** EQUAL. EXE resident: RAM[0x10000:] == extracted
  `SLUS_007.26`[0x800:] (8192/8192).
- **R9 persistence verifies — all PASS:** T1 (`CdPathTable`, db.5); checkpoint#1 (`StreamLoadStateMachine`);
  #2 (`loadDestPtrTable`); T7 (`VerifyOverlay` — both blobs init=true, bytes correct); #3 (`DebugMenuHandler`).
- PCSX-Redux web API `GET :8081/api/v1/cpu/ram/raw` → exactly **2,097,152 B**.
- **Overlay map:** 13 area-states identified by RAM-vs-extracted byte-match across **SC01/SC02/SC03**;
  2 duplicate-overlay pairs (`SC02/000≡003`, `SC01/005≡006`).
- **Player/time state live-verified** (multi-datapoint / controlled diff): `gold` 0x80078E8C (÷10),
  `hp_max/cur` 0x80078EB2/EB4, `bp_max/cur` 0x80078EB6/EB8, `dayCounter` 0x80078EAC, `hour` 0x80078EB1,
  `tiredness_raw` 0x80078EA4, `bossHp_SteamKnight` 0x801E4398. **Four 2-datapoint false positives caught
  and refuted** (clock 0x8007CE82, two tiredness guesses, a dow byte) → see R10.
- `git status`: only docs + tooling/scripts tracked; all ROM-derived (`ghidra/`, `disks/`, extracted bulk,
  the PCSX AppImage) gitignored.

**Milestone achieved:** `docs/memory-map.md §4.3` holds a loader/overlay table where the resident blob
(0x800CEDF8) and a location overlay (0x80128158) have US load addresses **proven byte-identical** (sha1-equal
contiguous prefixes) against a **live PCSX-Redux RAM dump** — the project's central "what loads where"
unknown, resolved.

**Next:** **Phase 4 = PROTOTYPE RESEARCH SPIKE** (Drew's directive — supersedes the roadmap's "build
toolchain" as the *next* phase; toolchain follows). Start with a symbol/debug-info hunt in the Aug-31
"Musashi Demo". See "Notes for Future Phases" below for the full brief.

## Deviations

| Item | Plan | Actual | Reason |
|---|---|---|---|
| Runtime-oracle location | PCSX-Redux under WSLg (all-in-WSL) | **Windows-native** PCSX-Redux; WSL fetches RAM via 172.17.208.1:8081 | WSLg wouldn't paint the window; WSL2 kernel can't do the DualSense. Hybrid bridged by the web API (→ R11) |
| Overlay-mapping scope | ≥1 overlay (milestone) | 13 area-states across SC01/02/03 + full loader model | Drew-driven live tour; high value for Gen2 overlay configs |
| Player-state RE | not in plan | gold/HP/BP/day/hour/tiredness/boss-HP verified; save-header found | Opportunistic live triangulation (Drew fed ground truth) |
| Prototypes | parking lot | 2 US protos acquired + CRC-verified; FF8 demo disc | Drew acquired them; seed the Phase-4 spike |
| Next phase | Phase 4 = build toolchain (roadmap) | Phase 4 = prototype research spike | Drew's directive — assess proto value before matching |
| T6b proof form | "sha1 of dump slice == sha1 of extracted blob" (whole blob) | sha1-equal large **contiguous prefix** (runtime data diverges past the code) | Runtime writes mutate the blob's data after load; the code prefix is byte-identical at the exact vaddr — conclusive for the load address (P9) |
| `.DA`/proto context | — | SLUS-90029 corrected to FF8 demo (not a BFM demo); no playable US BFM demo exists | Drew correction + web research |

## Commit Message
```
feat(phase-3): file-loader & overlay-map RE + PCSX-Redux runtime oracle

- RE'd the full file-loader/overlay subsystem in Ghidra via MCP: CdReadRequest ->
  CdReadStateMachine (hand-rolled CdControl SeekL/ReadN reader, NOT PsyQ CdRead);
  LIST.CD RAM cache cdFileLocTable + ResourceGetCdLoc/resourceIdMap lookup; LZSS
  staging buffer 0x80079A70; loadDestPtrTable; ~50 symbols named (T1-T5,T8)
- T6b MILESTONE: resident blob @0x800CEDF8 + location overlay @0x80128158 proven
  byte-identical (sha1-equal contiguous prefixes) vs live PCSX-Redux RAM; blobs
  imported into Ghidra (ImportOverlay.java); overlay-map table -> memory-map.md §4.3
- PCSX-Redux runtime oracle: Windows-native build, WSL reads RAM via the web API
  at 172.17.208.1:8081; ledger #4 resolved
- live-verified player/time state: gold(/10) HP BP day hour tiredness boss-HP;
  save-header template (Q#5) + debug-menu dispatch (Q#9: DEBUG.BIN path is dead)
- overlay map: 13 area-states across SC01/02/03, 2 duplicate pairs, location x
  chapter keying, free-roam vs menu-hub granularity
- resolves Open Q#1/#3/#4/#5/#6/#8/#9/#12; corrects SLUS-90029 (FF8 demo, not BFM)
- 2 US prototypes acquired + CRC-verified (Aug-31 1369DE07, Sep-8 5C24728E)
- rules R9 (verify persistence), R10 (>=3-datapoint live verification),
  R11 (runtime oracle Windows-native, bridged to WSL)
- bumps project version 1.2.0 -> 1.3.0
```

## Rules Added This Phase

| Rule | Reason |
|---|---|
| **R9 — Verify Ghidra persistence after every save-shutdown.** Read-only re-open (`tools/ghidra_mcp_verify.sh <addr> <name>`) and confirm a recent edit survived — never trust "Save succeeded" alone. Mandatory at phase end; recommended at each checkpoint. | Headless MCP writes persist only on clean shutdown; the live server holds an open transaction. Catches a lost save before it strands work. (Candidate since this phase; formalized.) |
| **R10 — Multi-datapoint live-RAM verification.** A RAM-address finding from PCSX-Redux is `verified` only with **≥3 consistent datapoints** OR a **controlled before/after diff** (e.g. paused snapshots, sleep reset). Two-datapoint matches stay `candidate` (coincidence-prone). | Four 2-datapoint false positives this phase (clock 0x8007CE82, two tiredness guesses, a day-of-week byte) were each disproven by a 3rd datapoint. Aligns G1/P9 (bytes are truth). |
| **R11 — Runtime oracle is Windows-native, bridged to WSL via the web API** (`http://172.17.208.1:8081`). Build, Ghidra, splat, asm-differ, analysis all stay in WSL (R2/H2 unchanged for those); only the emulator GUI + controller live on Windows — the explicit all-in-WSL exception. | WSLg can't render PCSX-Redux and the WSL2 kernel can't expose a DualSense; the web API is a clean, low-friction WSL↔Windows boundary that preserves the rest of the architecture. |
| **R12 — No `/tmp`; project-local data only.** All project data — including transient runtime scratch (logs, sentinels, temp outputs) — lives under `~/bfm-decomp` (runtime scratch → `.run/`, gitignored). Never `/tmp`. | Drew directive 2026-06-14: `/tmp` is volatile (28 non-regenerable RAM dumps nearly lost on a reboot). Keeps the clone self-contained and durable. |

## PhaseEnd Changelog
**v1.2.0 → v1.3.0** — Phase 3 complete. The file-loader/overlay subsystem is fully reverse-engineered in
Ghidra and the central "what loads where" unknown is **byte-proven against live hardware behavior**: the
resident blob (0x800CEDF8) and location overlays (0x80128158) load position-locked and verbatim; the loader
is a hand-rolled `CdControl` async reader (not PsyQ `CdRead`) driven by `cdFileLocTable` (the parsed LIST.CD
TOC) + a two-level resource-ID map. A live overlay map of 13 area-states across SC01/SC02/SC03 was captured
(duplicate overlays, location×chapter keying, free-roam-vs-menu-hub granularity). PCSX-Redux stood up as the
runtime oracle (Windows-native, WSL web-API bridge). Bonus live-verified the player/time state block
(gold÷10, HP/BP, day, hour, tiredness) and the save-header (Q#5) + debug-menu dispatch (Q#9: DEBUG.BIN dead).
Open Questions #1/#3/#4/#5/#6/#8/#9/#12 resolved. Three rules added (R9 persistence, R10 multi-datapoint
verification, R11 Windows-native oracle). Two US prototypes acquired + CRC-verified, seeding the Phase-4 spike.

## Notes for Future Phases — Phase 4 RESEARCH SPIKE brief (Drew's directive)

Analyze the two CRC-verified US prototypes (`disks/`) **before** the build/matching phases:
1. **Debug info?** Hunt the Aug-31 "Musashi Demo" + Sep-8 "Musashi Master" for `.SYM`/symbol tables, debug
   strings, assertion/source-path text, less-stripped data. (Hidden Palace said "no symbols" — UNVERIFIED.)
2. **Is the demo easier to decomp, and does it help the full game?** Assess optimization level vs retail.
   **Caveat:** demo ≠ retail bytes → demo *matches don't transfer* to SLUS-00726; value is **labels + a
   readable reference + shared tables**, not matched bytes.
3. **Free-label lead (already identified):** the Aug-31 demo's title scene/area-select very likely shares
   code/tables with the retail debug menu mapped in T8 — `GameModeDispatch` (0x80010B40),
   `gameModeHandlerTable` (0x800629F4), `DebugMenuHandler` (0x80011144). Binary-diff to lift labels in.
4. **Deliverable:** a go/no-go on whether the protos accelerate Gen1 matching, plus any labels imported.
This is a **roadmap insertion** before Phase 4 (build toolchain), which then follows. Also outstanding for
later: the save-data block format (trace `SaveLoadRoutine` 0x8002B154, Q#5); the exact tiredness-% / minute /
day-vs-dow encoding; importing more overlays as Ghidra overlay address spaces (Gen2).

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` absorbed. **Drew commits AND pushes** this PhaseEnd (R6/R8). Start a
fresh session for the next phase. Keep this file forever.
