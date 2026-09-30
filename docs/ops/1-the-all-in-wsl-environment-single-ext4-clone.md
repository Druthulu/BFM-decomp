## §1 The all-in-WSL environment (single ext4 clone)

```
┌─ WSL2 Ubuntu 24.04 (ext4) — everything lives here ──────────────────────────┐
│                                                                             │
│  ~/bfm-decomp          ← THE clone (one git working tree, one remote)        │
│   ├─ Ghidra 12.1 PUBLIC  (JDK 21 Temurin, GUI via WSLg)                      │
│   │   ├─ ghidra_psx_ldr 2026.06.04 (PSX loader, PsyQ signatures,            │
│   │   │   .gdt type archives)                                               │
│   │   └─ GhidrAssistMCP v2.8.0 ── SSE 127.0.0.1:8080 (local to WSL)         │
│   │                                                                         │
│   ├─ Ghidra project .gpr/.rep (under ~/bfm-decomp or ~/.ghidra)             │
│   ├─ PCSX-Redux (Linux build: runtime oracle — debugger, Lua,              │
│   │   web API RAM dumps, GDB server :3333)                                  │
│   ├─ Claude Code ← .mcp.json → 127.0.0.1:8080/sse (same box, no boundary)   │
│   │                                                                         │
│   ├─ .venv/            splat64[mips] etc.                                    │
│   ├─ tools/maspsx, tools/asm-differ, tools/m2c, tools/decomp-permuter (subm.)│
│   ├─ tools/bin/gcc-2.7.2-psx, tools/bin/gcc-2.7.2-cdk                       │
│   │   (old-gcc 0.17, Linux x86-64 binaries)                                 │
│   ├─ disks/             BIN/CUE dump, copied in ONCE (gitignored)           │
│   └─ asm/ build/ expected/  (generated, never committed)                     │
│                                                                             │
│  apt: binutils/gcc-mipsel-linux-gnu, make, ninja, python3.12, JDK 21, ...   │
└───────────────────────────────────┬─────────────────────────────────────────┘
                                    │
                                    └── git remote (push/pull off-box only) ──►
```

One repository clone on ext4 at `~/bfm-decomp` holds everything — RE stack, build toolchain, runtime oracle, docs, and Claude Code's working directory. There is **no Windows/WSL split**: no second clone, no cross-OS working-tree edits, no `/mnt` build path. The git remote is used only to push/pull off the machine (backup, collaboration), never to synchronize two local trees. Rationale for keeping the clone on ext4 (not on a `/mnt/*` drvfs mount):

- **9P filesystem penalty.** File access on `/mnt/*` drvfs mounts goes through the Plan 9 protocol and is the slowest path WSL2 offers — Microsoft's own numbers put ext4 at 2–20× faster, and community benchmarks measured builds up to 375% faster after moving off `/mnt`. Every `make`, `git status`, and splat extract pays the tax if the build tree sits on a mounted Windows drive. Keeping the clone on ext4 sidesteps this entirely.
- **inotify works on ext4.** Linux file-watchers get no events for changes on `/mnt/*` drvfs mounts (microsoft/WSL [#4739](https://github.com/microsoft/WSL/issues/4739), [#5424](https://github.com/microsoft/WSL/issues/5424)). asm-differ watch mode fires reliably only when source *and* build outputs live on ext4 — which, all-in-WSL, they always do.
- **No ghost-file hazard.** anthropics/claude-code [#28015](https://github.com/anthropics/claude-code/issues/28015): Write/Edit on WSL2 drvfs mounts can hit a statx/9P cache-poisoning kernel bug producing "ghost files" (ENOENT for files that exist). Editing only on ext4 avoids the bug; Claude Code runs inside WSL and never touches a drvfs path.

One-shot file copies onto ext4 (e.g. the disc dump into `disks/`) from any source are fine — it is sustained/random IO and watchers on drvfs that break, not correctness. Ghidra project files (`.gpr`/`.rep`) live on ext4 alongside the clone (or under `~/.ghidra`), consistent with Ghidra's local-drive-storage recommendation; their `~lock` files behave correctly on a native Linux filesystem.

Git hygiene: the committed `.gitattributes` (`* text=auto eol=lf` + binary exclusions) keeps line endings consistent. On the Linux clone `core.filemode true` is fine (ext4) and `core.autocrlf` is `false` by default (LF-native), so no line-ending dance is needed.

### §1a Runtime scratch (`.run/`, rule R12)

Project-local scratch directory at `~/bfm-decomp/.run/` — the standing replacement for `/tmp` (rule R12: never write to `/tmp`; all runtime data is project-local). It holds the regenerable transients: the headless MCP server log (`ghidra-mcp.log`), the clean-shutdown sentinel (`mcp-stop.req`, see §2.8), signature dumps (`sig.*.jsonl`, produced by `make sig-refresh`), decomp-permuter scratch (`.run/permuter/`), build/extract logs, per-session work directories (`.run/<session>/…`) and assorted `tmp*` working files — some 29 GB and ~455,000 top-level entries by Phase 33, none of it tracked.

**Ignored by contents, allowlisted by exception (corrected 2026-09-07, Phase 33.5 — the earlier "never committed" wording was false from Phase 25 on).** The `.gitignore` rule is the contents-exclude form `/.run/*` (not `/.run/`), so that `!` re-includes can carve exceptions; each exception is a three-line idiom — re-include the directory, re-exclude its contents, re-include the wanted extensions — under a dated comment naming the phase, session and rule that justified it. The test for an exception is R20's: **commit what a rerun cannot reproduce** (hand or frontier-model analysis, harnesses, ledgers, the recorded contract run); leave everything a script regenerates (RTL dumps, build logs, drafts, compile dirs) ignored. What is tracked at the Phase-33.5 prune: `.run/P33/verify/` (the recorded 218/218 contract run that `docs/verification.md` quotes), the Phase-32 drafts/notes/banks/reproducers under `.run/P32/`, the giant-crack recon under `.run/giants/`, the R20 crack ledgers (`s42`, `s43`, `s45`, `wave22`, `near6`, `fable_80178004`, `probe_jtbl`, `S79w`) and two fleet ledgers (`backlog.jsonl`, `fuel_manifest.json`). A citation of an untracked `.run/` path in a document is a private-tree breadcrumb, not a link — the wiki page *Docs and scratch conventions* states the rules; `tools/doc_links.py` classifies such citations as TRACKED/UNTRACKED and refuses UNTRACKED ones only in wiki pages.

---

