# Verification and progress

## The contract

218 binaries rebuild byte-for-byte from the C in `src/`, compared by SHA1 against the originals extracted from a
redump-verified disc. That is the whole claim. It is proven by one recorded sequence,
[`tools/verify_contract.sh`](../../tools/verify_contract.sh), whose every step writes a log ending in `EXIT=<rc>` and a
timestamp under `.run/P33/verify/` (tracked) and whose summary is pasted into [`docs/verification.md`](../verification.md):

| # | Step | Contract line |
|---|---|---|
| 01 | `make check-env` | `check-env: OK` |
| 02 | the family map | `217 binaries scanned, 0 open instances` |
| 03 | **`make clean && make extract-all && make check-all`** | `check-all: 218 passed, 0 failed of 218` |
| 04 | `make sdk-dual` | main byte-identical WITH and WITHOUT the PsyQ objects |
| 05 | `make tools-health` | both boundary oracles: `0 PHANTOM, 0 TRUNCATED, 0 PAD-TAIL`; the S1 invariant (`share_census --check`, strict: 0 violations) and the registry (dedup-check, C1–C2d: 3,173 groups / 0 failed at Phase 35); every audit fresh |
| 06 | `make audit-frontier` | every remaining `INCLUDE_ASM` is inside main's linked Sony regions; 0 game-code stubs |
| 07 | `make audit-disc` | `UNCLAIMED code payloads: 0` |
| 08 | `make report` | the three 100% lines, `INCLUDE_ASM stubs : 0`, `Open near-misses: 0` |

The run is repeated after every banked batch (218/218 at every one since Phase 30) and was repeated on the rewritten
history before publication — a content-preserving rewrite changes no tracked byte, and that run proves it.

## The three metrics, and why there are three

| Metric | Numerator / denominator | Why it exists |
|---|---|---|
| **Functions byte-identical** | matched functions / all functions in all 218 binaries | the natural count — but the shared engine is counted once per overlay (×138), so it flatters the work |
| **Instruction-weighted** | matched instructions / all instructions | the honest effort measure; a 700-instruction giant is not one function |
| **Distinct code** | each unique body once / all unique bodies | the reverse-engineering measure: how much *different* code is understood |
| **Main game-code** | main's instructions outside Sony's linked objects | the executable reported separately until 2026-07-22, when it entered the fleet denominators (the owner's decision — it lowered nothing, the same day's banks absorbed it) |

All four are computed from the sources by [`tools/progress.py`](../../tools/progress.py): what a function *is* comes
from the per-binary signature files (`make sig-*`), what is *matched* from the C and the dedup registry, never from a
hand-maintained list. Main's function boundaries are derived from the build itself (the link map's sections × each
object's symbols, asserted to tile the text exactly) — the Ghidra-derived boundaries under-counted the game code by
3,616 instructions, discovered at the very end. Every number ships with its denominator (R41).

**What is not our C, stated with the numbers:** 1,256 functions of the main executable are Sony's PsyQ objects (linked
byte-identical when the SDK is present, carried as assembly tiles from the disc when it is not) and 5 functions
fleet-wide are hand-written assembly in the original, kept verbatim and audited by
[`tools/verbatim_check.py`](../../tools/verbatim_check.py) `--strict` against [`config/verbatim_manifest.json`](../../config/verbatim_manifest.json).
Every other function in every binary is C.

## The second oracle

A correctness oracle is blind to coverage: the byte gate is green at 0% decompiled, because the fallback pastes the
original bytes. So the project keeps a second, disagreeing oracle for *what exists*: two independent function-boundary
derivations (Ghidra's flow analysis vs. the built ELF's symbols) reconciled in `make tools-health` — a function one sees
and the other does not is a **phantom** or a **truncation**, and both must read 0. Seven silent-skip defects were found
the first time this was done (Phase 26); the rule that came out of it, *assert your coverage* (R32), is the reason
every scanner in the repository prints its denominator.

## What CI proves, and what it cannot

[`.github/workflows/no-rom.yml`](../../.github/workflows/no-rom.yml) runs on every push and pull request without the
disc: the tracked tree is public-clean ([`tools/audit_public.py`](../../tools/audit_public.py): no tracked file's hash
appears in the ROM manifest or the contracts, no purge path, nothing over 50 MiB), every source is text with portable
includes, the verbatim manifest has no drift, the derived indexes are fresh, the LZSS decoder's unit tests pass, and
every eligible translation unit compiles with the pinned `cc1` → maspsx → `as` and the Makefile's exact flags
([`tools/compile_only.py`](../../tools/compile_only.py): four representative binaries per PR, the whole fleet weekly).
CI cannot compare bytes to the originals — that is [your step](Build-from-your-own-disc.md). The two together are the
full claim.

## The published numbers

- [`docs/progress.json`](../progress.json) — the metrics with numerators and denominators, the counts, and a row per
  binary; written by `tools/progress.py --json`, asserted fresh by `make audit-digest`.
- The README's progress block — rewritten by `--readme` between two markers; never edited by hand.
- [`docs/badges/`](../badges/) — shields.io endpoint JSON, colour by percentage.
- `SLUS_007.26_report` — an objdiff report (categories *game-code* and *linked-sony-objects*) converted from the JSON
  by [`tools/objdiff_report.py`](../../tools/objdiff_report.py) and uploaded as a workflow artifact for decomp.dev;
  [`tools/frogress_upload.py`](../../tools/frogress_upload.py) pushes the same measures to frogress. CI never rebuilds
  the game — the report is the committed JSON from a local clean rebuild.
- [`docs/story-timeline.md`](../story-timeline.md) and its chart — the metrics by date across the whole project,
  reconstructed from every commit that touched the progress digests.
