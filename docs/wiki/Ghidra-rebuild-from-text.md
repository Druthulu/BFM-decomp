# Ghidra rebuild from text

## Why the database is not in git

The Ghidra project (`ghidra/`) was the static oracle for the whole project — every claim about code behaviour, calling
conventions and data layout was validated against it (rule G1). Its database embeds the program's bytes (verified under
Ghidra's page XOR mask), so it is ROM-derived and left the repository before publication. What is tracked instead is
the **hand-authored part as text**, plus the proof that the program regenerates from the disc, the symbol files and that
text. This replaced the earlier private-era backup of the binary database (rule R20).

## The delta model

`tools/ghidra_scripts/ExportAnnotations.java` dumps *everything* a program holds — container facts, local types,
every function signature (parameters, locals, storage), defined data, the five comment kinds, bookmarks, equates, labels
not already in the symbol files — as byte-stable JSON Lines (fixed key order, sorted, `0x%08x` addresses). The
hand-authored part is what a **fresh rebuild does not reproduce**: export a baseline from a freshly rebuilt program,
subtract it from the live export, and drop three measured classes of analysis drift (`Error`/`Analysis` bookmarks;
auto-named functions with default signatures that only exist because the function set drifted; name-only differences
where the database lagged the curated symbol file). What remains is committed as `config/ghidra/<program>.jsonl`.

The census was humbling: the resident and the overlays reduced to container rows only (every name comes from the
symbol files), the retail executable to **38 hand-authored rows** (13 annotated functions, 22 comments, 3 labels), and
no program held a single hand-authored type. Most of the reverse-engineering knowledge had already migrated into the
symbol files and the C.

## Rebuild and prove

```bash
tools/ghidra_mcp_stop.sh                          # the headless server holds the project lock
tools/ghidra_rebuild.sh resident --proof           # -> "PROOF PASS"  (≈65 s; the executables ≈200 s)
```

[`tools/ghidra_rebuild.sh`](../../tools/ghidra_rebuild.sh) works in a scratch project under `build/` (Ghidra refuses a
path component starting with `.`): import the program (the PSX loader for the executables, a raw blob at the binary's
registered load address otherwise — the address comes from the build's own registry, never retyped) → auto-analysis and
the PsyQ 4.0 type archive → `DefineFunctions` from the built ELF's text symbols (splat's validated boundaries) →
`ApplySymbols` with the binary's splat symbol files → baseline export → `ImportAnnotations` of the committed file →
export → delta. `--proof` compares the delta with the committed file byte for byte. Controls the proof was gated on: a
mutated block row in the committed file → `PROOF FAIL`; a synthetic comment, bookmark, label and retyped signature →
imported, re-exported, `PROOF PASS`, and idempotent on the second run.

[`config/ghidra/ROSTER.md`](../../config/ghidra/ROSTER.md) (generated, checked in `make tools-health`) lists the tracked
programs — the retail executable, the resident, two overlays, the two prototype executables — with their kind, payload,
load address and hand-authored census. The other 123 programs the project had on disk carry no hand-authored rows and
regenerate on demand.

## Gotchas that cost a session

- Ghidra compiles `tools/ghidra_scripts/` as **one OSGi bundle**: a compile error in any script disables every script
  in the directory, and the headless log names the script, never the error. Compile by hand with `javac` first.
- `/undefined` is `DataType.DEFAULT` and lives in neither type manager; a first "passing" proof had silently failed to
  import 13 of 13 function rows. The rebuild now refuses unless the import printed `failed=0` (a soft error inside a
  success envelope is still that error — R49).
- MCP renames do not persist. Symbols reach the database only through the headless `ApplySymbols` script, and every
  save-shutdown is followed by a read-only re-open that checks the write landed (R9).

## The oracle in daily use

The agent queried Ghidra over an MCP server run **headless** by [`tools/ghidra_mcp_start.sh`](../../tools/ghidra_mcp_start.sh)
(started by a session hook; a silent no-op when Ghidra is not installed, so a contributor's session never tries to
launch it) and stopped cleanly by [`tools/ghidra_mcp_stop.sh`](../../tools/ghidra_mcp_stop.sh) — the only event at
which the database is saved. Before any reverse-engineering task the server is pinged with one cheap call (rule G2);
after any restart the session pauses for a reconnect (R29). The decompiler's C for every function was also cached as
text by [`tools/prefetch_fleet.py`](../../tools/prefetch_fleet.py) so that drafting agents never needed a live Ghidra.

The runtime oracle is separate: PCSX-Redux, bridged over its web API, whose RAM snapshots proved every load address
([Overlays and modules](Overlays-and-modules.md#how-the-load-addresses-were-proven)). The 28 snapshots are local-only;
[`dumps/CHECKSUMS.sha1`](../../dumps/CHECKSUMS.sha1) records their identity and a re-capture
([`tools/ram_probe.py`](../../tools/ram_probe.py)) is a new state, never byte-identical to the original.
