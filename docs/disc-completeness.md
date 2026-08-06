# Disc-completeness audit (Phase-27 T7)

> **Generated 2026-07-15.** Reproduce: `tools/disc_code_sweep.py` (committed). The question this
> answers is the one the whole-binary byte-gate is structurally blind to (R34): `make check-all` only
> touches binaries someone ONBOARDED, so a code payload nobody onboarded is invisible to it however
> green the fleet is. This reconciles the ONBOARDED set against every code-bearing payload ON THE DISC.

## What the disc holds (extracted PAC payloads, by type)

`extracted/retail/**` holds **1189** raw PAC payloads across 8 types (`docs/formats.md`):

| type | payloads | code-bearing | onboarded | note |
|---|---|---|---|---|
| 0 | 301 | 0 | 0 | data (graphics/blobs) |
| 1 | 166 | **40** | 1 | **resident-class code modules** — the resident is one; 39 more are NOT onboarded |
| 2 | 201 | 0 | 0 | data (decodes ~100% "valid" but 0% `jr $ra` — the false-positive class) |
| 3 | 201 | 0 | 0 | data |
| 4 | 138 | 138 | **138** | location overlays — **COMPLETE** (134 at PAC entry 0 + 4 SC07 at entry 1) |
| 6 | 29 | 0 | 0 | data |
| 7 | 139 | 0 | 0 | data |
| 8 | 14 | 0 | 0 | data |

**Code detection (`disc_code_sweep.py`):** decode the first 4096 words as MIPS-LE (reusing
`sig_image.make_insn`, GTE-aware) and require BOTH `valid ≥ 0.90` AND `jr $ra` density `≥ 0.01`.
The `jr $ra` gate is decisive: `isValid()` alone is far too permissive (structured type-0/type-2 data
decodes ~100% valid), but real MIPS code carries a `jr $ra` roughly once per function — **2.9–3.4%** of
words across the onboarded overlays + the resident, versus **0.000%** for the data blobs. Validated
against positive controls (`SC01/077/0.4.dec` 3.39%, resident `MAIN/FILE_010/1.1` 2.91%) and negative
controls (type-2 `0.00%`, type-0 `0.00%`).

## The finding

**Type-4 (location overlays) is complete.** All 138 type-4 payloads are onboarded and build
byte-identical. The 4 that were invisible for a month — `ov_SC07_{006,007,010,011}` — put graphics at
PAC entry 0 and the code overlay at entry 1 (`1.4.dec`); `new_overlay.sh` hardcoded `0.4.dec`. They are
now onboarded (byte-verified: `7ca772be`, `b3b95547`, `d7b5875d`, `9885af74`). **Fleet: 136 → 140.**

**Type-1 holds 39 additional, un-onboarded code modules.** These are resident-class code (the resident
`MAIN.CD/FILE_010/1.1` is the one already onboarded), the largest being `MAIN/FILE_027` (1318 w),
`FILE_036` (1229 w), `FILE_028` (1115 w). Full ranked list: `.run/disc_code_sweep.txt` (regenerate with
the tool). They are **NOT location overlays** — they do not load at the shared slot `0x80128158`; each
loads at its own address, the way the resident loads at `0x800CEDF8`. So — unlike the SC07 overlays —
**they cannot be onboarded mechanically:** a build binary needs its load address to byte-verify (P9), and
that address is only knowable by runtime RE (a PCSX-Redux RAM-dump proof, the Phase-3 method). Onboarding
them is a Gen2 RE task, deferred with this evidence — NOT a false "complete" while code sits unbuilt.

## Consequence for the completion contract (roadmap §1)

The contract's binary count is **no longer "136"**. Two corrections:
1. **140 binaries onboarded now** (main + resident + 138 overlays) — the number `check-all` verifies.
2. **⚠️ SUPERSEDED 2026-08-06 by `make audit-disc` — the real backlog is 78 payloads / 3.56 MB, not 39.**
   The "39" below came from `disc_code_sweep`, which reads only the RAW layer through a **4,096-word
   window** and has no notion of a *claim*. The L1+L2 disc audit walks the disc image, classifies
   **whole** payloads at **both** layers, derives `claimed-by` from `config/check.<bin>.sha`, and unions
   two independent oracles: **78 unclaimed code payloads, 3,564,021 bytes**, across MAIN.CD (42),
   SC03 (18), SC05 (7), SC04 (7), SC07 (2), SC02 (2). Verified against the old list: **all 39 are still
   un-onboarded** (0 of 39 claimed), so the new number strictly contains the old one. The audit asserts
   a **residue-0 partition** over all 416,021,760 disc bytes, so this figure is a floor with a proof
   rather than a sample. Live list: `docs/disc-ledger.md`. The paragraph below is kept for provenance.

2. *(superseded)* **A documented backlog of 39 type-1 code modules** pending load-address RE before they can be
   onboarded and counted. Game-code TRUE 100% (the contract's bar) is only honest once these are either
   onboarded-and-matched or explicitly excluded with a reason. They are recorded here so the "100%"
   claim cannot be made while they sit un-onboarded and unexamined (R34 — the byte-gate cannot see them).

**This is a re-baselining event, expected to LOWER the headline %** (the 4 SC07 overlays add ~2.45 MB of
mostly-unmatched code to the denominator; every "×134" family propagation is now "×138"). That is the
honest direction — the prior number was measured over an incomplete disc.

## Reproduce
```
tools/disc_code_sweep.py                 # the table above + the ranked hidden list
tools/disc_code_sweep.py --types 1       # just the type-1 code modules
```
