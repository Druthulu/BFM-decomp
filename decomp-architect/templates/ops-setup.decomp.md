<!-- decomp-architect: the rows appended to docs/ops-setup.md at Step 8, inside a marked section. The generation-time
     placeholders are written as literal TODO(phase-N) lines when their phase has not happened yet, so the leftover
     placeholder audit stays clean; the phase that produces the value replaces the TODO. -->

## Decomp environment (decomp-architect, Phase 0.5 — installed {{INSTALL_DATE}})

### Version pins (decomp)

| Component | Version | Notes / why pinned |
|---|---|---|
| The pinned toolchain triple (compiler → assembler shim → binutils, with flags) | {{TOOLCHAIN_TRIPLE}} | TODO(phase-4): pinned by fingerprint evidence down the candidate ladder; the assembler's compatibility version is always passed explicitly — a shim's default is not "latest" |
| Candidate compiler family (from the SDK evidence) | {{COMPILER_FAMILY}} | the candidate set the pin phase runs down; never a sibling project's triple |
| The splitter / disassembler and its config | TODO(phase-3) | version pinned in the bootstrap script |
| The disassembler database and its agent server | TODO(phase-2) | the static oracle; the database is tracked as a TEXT export with a rebuild script |
| The emulator and its scripting bridge | TODO(phase-2) | the runtime oracle |

### The game and the medium

- **Title / platform / serial:** {{GAME_TITLE}} · {{PLATFORM}} · {{GAME_SERIAL}}
- **The main executable on the medium:** `{{TARGET_BINARY}}` (its hash is the first per-binary contract, Phase 3)
- **Container layout:** {{CONTAINER_LAYOUT}}
- **SDK / compiler-era evidence:** {{SDK_EVIDENCE}}
- **The dump (machine-local, never committed):** `{{DUMP_PATH}}` — copied once onto a fast local filesystem under `disks/`
  (ignored); the extractor reads it, nothing builds against it.

### Build / extract / verify (decomp)

```
# extract the medium and verify against the committed manifest
{{EXTRACT_CMD}}
# the clean fleet verification — every binary from clean → extract → build, exit code read
{{FLEET_CHECK_CMD}}
```

- **The gate:** a binary is green only when its hash check inside `make build` passes; a match is verified from a CLEAN
  rebuild, never incremental; the executable is gated only by a clean rebuild; a build is verified by its exit code.

### The oracles (decomp)

- **Disassembler MCP:** {{DISASSEMBLER_MCP}} — verify with one cheap call before any reverse-engineering task; after a
  restart or a program switch, pause and ask the developer to reconnect the client.
- **Emulator bridge:** {{EMULATOR_BRIDGE}} — a live-memory finding is verified only with three or more consistent datapoints
  or a controlled before/after diff.

### Git posture (decomp)

- **Visibility at day one:** {{PUBLIC_OR_PRIVATE}} — the ROM firewall applies either way (`config/firewall.txt`,
  `tools/audit_public.py`, the CI workflow). If ever private, a later flip is gated on the host's object store, never on
  a clean tree.
- Never `git clean -x` in this tree (the game-derived data is ignored-but-present); the backup of the reverse-engineering
  work is the text export + the checksum files + a private archive repository, not the ignored directories.

### Tooling inventory (decomp)

| Tool | Location | Purpose |
|---|---|---|
| `tools/audit_public.py` | `tools/` | the ROM audit (purge paths, the derived hash set, the size cap, the pasted-disassembly check); the first-push gate and the CI job; its sources are `config/firewall.txt` |
| `make format` | `Makefile` | clang-format over `src/` with the tracked `.clang-format` (the community style) |
| TODO(phase-1): the extractor, the manifest | `tools/` | — |
