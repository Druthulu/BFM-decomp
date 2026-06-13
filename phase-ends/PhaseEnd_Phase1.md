# PhaseEnd — Phase 1: Repo governance + WSL RE stack + first import
**Date:** 2026-06-13 · **Project Version:** 1.1.0 · **Phase Status:** Complete

## Build Log

**Files created/changed and complete — do not recreate:**
- `tools/ghidra_scripts/DumpProgramInfo.java` — headless postScript; prints program metadata (language, image base, function count, and every Program-Information property incl. ghidra_psx_ldr's `PsyQ Version`). Consumed by `analyzeHeadless -postScript`.
- `tools/ghidra_scripts/DecompileAt.java` — headless postScript; decompiles a function by address (default `0x80018730`) and prints the C. Used to verify milestone substance without MCP.
- `tools/ghidra_scripts/ImportPsyqGdt.java` — headless `.gdt` "attach"; opens a PsyQ type archive (default `psyq400.gdt`) and `resolve()`s all its types into the program DTM, registering the archive as a SourceArchive. This is the headless replacement for the GUI Data-Type-Manager attach.
- `docs/SETUP.md` — corrections recorded (see Deviations + Rules): PsyQ `4.0.0` confirmed (§2.5 step 3); 41 MCP tools + async `get_code`/SSE notes (§2.6); headless `-loader` auto-detect, extension-install-by-extraction, `.rep` lock note (§2.7); §2.5 step 5 answered (import types into program); ledger #1 moot, #2 & #12 RESOLVED.
- `phase-ends/PhaseEnd_Phase1.md` — this file.
- `phase-ends/CURRENT_PHASE.md` — **absorbed into this file and deleted** (per P8).
- (Section A, earlier this phase, already committed) `PROJECT_CONTEXT.md` env corrections, `.gitignore` H1 relaxation, `.gitattributes`, `.mcp.json`, `docs/SETUP.md` Linux-first, `tools/bfm_extract/` extractor, `docs/history/` archived research files.

**Local artifacts (gitignored / outside the repo — present on this machine, do NOT recreate; a fresh clone elsewhere must redo them):**
- `~/bfm-decomp/ghidra/bfm.{gpr,rep}` — the saved Ghidra project: `SLUS_007.26` imported + analyzed (PSX loader, 1726 functions, PsyQ 4.0.0) **with the 2599 PsyQ 4.0 types imported**. The import does not need redoing on this machine.
- `~/ghidra_12.1_PUBLIC/` — Ghidra install + both extensions in `Ghidra/Extensions/`.
- `extracted/SLUS_007.26` — committed (H1 relaxed); SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd`, 413,696 bytes.

**Tools/packages installed (whole phase):**
- WSL2 Ubuntu 24.04.4 LTS; user `musashi` (passwordless sudo); git identity (`Drew T` / 50529377+Druthulu@users.noreply.github.com); `gh` 2.45.0; `unzip` 6.0; Claude Code 2.1.177 (B0 bootstrap).
- **This session:** JDK 21.0.11 (`openjdk-21-jdk`, apt); Ghidra 12.1 PUBLIC (`ghidra_12.1_PUBLIC_20260513.zip`, 567 MB, central-dir verified); GhidrAssistMCP v2.8.0 (`…20260530…`); ghidra_psx_ldr 2026.06.04 (`…20260604…`). Both extensions load at `version=12.1` (exact-12.1 pin held — no version-lock issue).

**Verification results (literal):**
- `extracted/SLUS_007.26`: SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd`, 413,696 bytes, magic `PS-X EXE`. Track-1 `--verify-disc` PASSED on Windows (== redump `b44f0f0a19936f23b26188b658e13201a6a9c211`); WSL re-run deferred (dump not yet copied — not a milestone blocker).
- Headless import: `Using Loader: PSX Executables Loader`, `PSX:LE:32:default`, ImageBase `80000000`, range `1f800000–801fffff`, **1726 functions**, analysis 177 s, **`PsyQ Version = 4.0.0`** (DetectPsyQ).
- `.gdt` import: 2599 types resolved from `psyq400.gdt` (program DTM 205 → 2609); `psyq400` SourceArchive registered; save succeeded.
- MCP server (headless): "started on port 8080 … with **41 tools**".
- **In-session MCP (Claude Code, the milestone):** `get_binary_info` → SLUS_007.26 / 1726 funcs; `get_code(0x80018730, decompiler)` → LZSS streaming decompressor (scratchpad ring @ `0x1F800000`, 0x3ff window mask, resumable state machine `DAT_800c7d24`, `pos==0` terminator); `types get DRAWENV` → 92-byte struct (`/LIBGPU.H`).

**Milestone achieved:** In a live Claude Code session, `mcp__ghidra__get_code(0x80018730)` returned the documented LZSS streaming decompressor and DetectPsyQ recorded `PsyQ Version = 4.0.0` — both Phase 1 observables, demonstrated end-to-end.

**Next:** Phase 2 — Deterministic disc & .CD extraction pipeline. Start with the full ISO9660 walker (all 27 root files) in `tools/bfm_extract`.

## Deviations
| Item | Plan | Actual | Reason |
|---|---|---|---|
| EXE import method | WSLg GUI (CodeBrowser) | Headless `analyzeHeadless` | Fully autonomous; milestone reachable without GUI |
| `.gdt` attach | "manual GUI step" (known-risk: GUI-only) | Headless `ImportPsyqGdt.java` (resolve types into program) | No GUI needed; resolves ledger #2 — import types into the program, MCP `types`/`struct` tools then see them |
| Headless `-loader` | `-loader "PSX Executables Loader"` (§2.7) | Omit `-loader`; auto-detect | Named loader rejected (`InvalidInputException`); auto-detect correctly selects the PSX loader for a `PS-X EXE` |
| MCP tool count | ~38 | 41 | GhidrAssistMCP v2.8.0 ships 41 tools |
| `get_code` execution | (sync implied) | Async task — returns `task_id`, poll `get_task_status`; SSE wire frames | v2.8.0 runs heavy tools asynchronously |
| `--verify-disc` in WSL | Re-run in WSL | Deferred (ran on Windows, PASS) | Dump not yet copied to `disks/`; EXE already sha1-verified; not a milestone blocker |

## Commit Message
```
chore(phase-1): close Phase 1 — RE stack live, EXE imported, LZSS matched via MCP

- PhaseEnd_Phase1.md written; CURRENT_PHASE.md absorbed + removed (P8)
- milestone: in-session mcp__ghidra__get_code(0x80018730) = LZSS streaming
  decompressor; DetectPsyQ recorded PsyQ Version 4.0.0
- formalizes 6 phase-1 rules (H1-relaxed-while-private, all-in-WSL H2,
  tools-in-tools/, plan-mode-per-phase, no-co-author, WSL-commit/GH-Desktop-push)
- bumps project version 1.0.0 -> 1.1.0
```

## Rules Added This Phase
| Rule | Reason |
|---|---|
| **R1 — H1 relaxed while private.** ROM-derived content (`asm/`, `assets/`, `extracted/`, decompressed `.CD`) MAY be committed while the repo is private; accidental inclusion is not a violation. The raw multi-GB disc dump stays ignored regardless. Compliance before going public = history scrub + a rom→decoder regeneration tool. | Solo private phase; momentum > purity until the public flip, when original H1 is restored. |
| **R2 — All-in-WSL (H2 restatement).** One ext4 clone at `~/bfm-decomp`; no Windows/WSL split, no second clone, no `/mnt` builds; MCP is loopback `127.0.0.1:8080`. | 9P/`/mnt` is 5–20× slower and breaks inotify; one clone removes the sync dance. |
| **R3 — All tooling under `tools/`.** Includes `tools/bin` (compilers), `tools/psyq*` (native PsyQ), `tools/ghidra_scripts` (headless scripts). | Keeps the repo root clean; one predictable home for executables/scripts. |
| **R4 — Plan mode every phase.** Present the task-by-task plan and get approval before executing (the Phase Start gate). | Drew's standing preference; reinforces the two-gate model (P3). |
| **R5 — No `Co-Authored-By` trailer on commits.** Overrides the harness default. | Drew's instruction (2026-06-11). |
| **R6 — Git workflow = WSL-commit / GitHub-Desktop-push.** Claude commits in-phase task work locally in WSL (name/email only, no auth); the user pushes/pulls with GitHub Desktop on Windows over `\\wsl.localhost\…`. **Never `git push` from the WSL CLI** (no credentials by design). `core.filemode=false` in the clone. **Phase-boundary exception:** Claude *writes* `PhaseEnd_PhaseN.md` and removes `CURRENT_PHASE.md` but leaves them **uncommitted**; the **user commits AND pushes** the PhaseEnd, reviewing the milestone-close before it lands. | Avoids git auth in WSL; keeps push (and the milestone-close commit) under human control; the H1 ROM-content safety net stays with the human committing/pushing. |

## PhaseEnd Changelog
**v1.0.0 → v1.1.0** — Phase 1 complete. WSL RE stack live (JDK 21, Ghidra 12.1 + GhidrAssistMCP v2.8.0 + ghidra_psx_ldr 2026.06.04); `SLUS_007.26` imported & analyzed (PSX loader, 1726 functions, **PsyQ 4.0.0**); PsyQ 4.0 types imported (2599); LZSS decompressor at `0x80018730` confirmed via in-session MCP `get_code`. Six rules formalized (R1–R6). Ledger: #1 moot (12.1 pinned), #2 RESOLVED (import .gdt types → MCP resolves them), #12 RESOLVED (PsyQ 4.0.0). Key finding: the entire RE loop runs **headless** (import, `.gdt`, MCP server, decompile, retype) — no WSLg GUI required.

## 🛑 Stop Here
Start a fresh session for the next phase. Keep this file forever.
