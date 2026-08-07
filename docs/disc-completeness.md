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

> **⚠️ 2026-08-06 (S44): the "only knowable by runtime RE" sentence above is REFUTED.** The load
> addresses are **static** for 46 of the 78 unclaimed payloads: the EXE's `loadDestPtrTable`
> (0x80072C70) + the boot loaders' literal `&cdFileLocTable[k]` operands + two index tables INSIDE the
> resident (`D_800D3764` → slot A 0x800CAE08 for MAIN/13…41; `D_800D384C` → slot B 0x800CCB1C for
> MAIN/42…47) + `src/resident/resident.c:641` (MAIN/12 → the standard overlay slot 0x80128158) + the
> SC07 pair's own headers (→ 0x801A00D8). Full routing table with provenance:
> **`docs/memory-map.md` §"Phase 30 S44"**. Independently corroborated by h_exact base voting (~500:1)
> and jal-alignment voting. The genuinely runtime-only remainder is the 28 SC0x script modules +
> MAIN/7, MAIN/9, SC02/9 — parked for L3 with evidence. Additional corrections from the same pass:
> the three biggest "modules" (MAIN/12, SC02/37, SC03/107) are **ordinary overlays stored uncompressed**
> (PAC type 1 = raw overlay, type 4 = LZSS overlay); the 78 ledger rows sum **3,406,325 B** (the
> bucket's 3,564,021 additionally counts PAC headers); `MAIN/7` is a raw file (`FILE_007`, not
> PAC-wrapped); `MAIN/0 ≡ MAIN/1` byte-identical; payload word0 is a global module id (resident=0x36).

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

## S45 (2026-08-06): the module campaign landed — the residue IS the parked-for-L3 ledger

**43 of the 78 unclaimed payloads now build byte-identical** (P30 S44/S45): the 3 uncompressed
overlays (`ov_MAIN_012`, `ov_SC02_037`, `ov_SC03_107`) + the 38 MAIN modules (slot A
`md_MAIN_013…041` @0x800CAE08 · slot B `md_MAIN_042…047` @0x800CCB1C · boot trio `md_MAIN_001`
[≡MAIN/0, stored twice] / `md_MAIN_008` / `md_MAIN_011` @0x800CEDF8) + the SC07 pair
(`md_SC07_003/004` @0x801A00D8) — every address static-derived (§S44 loader table,
`docs/memory-map.md`) and byte-corroborated by a first-build byte-identity. Fleet = **183
binaries**, `make audit-disc` residue 0.

**The remaining UNCLAIMED = 34 payloads = the parked-for-L3 exclusion list** (the 100% claim
cites exactly this list, roadmap §1.1):
- the **28 SC0x script modules** (SC03/73–79, SC03/132–138, SC04/24–30, SC05/23–29 = 7 modules ×
  4 per-disc builds) — bases loader-determined per-disc via the resourceIdMap/DESTPTR path;
- **SC02/9** (70,784 B), **MAIN/7** (raw file, not PAC), **MAIN/9**;
- **SC03/53, SC03/54, SC03/56** (6,616 / 8,220 / 3,680 B) — *added S45:* three SC-disc type-1
  rows the S44 exploration never tiered; same per-disc runtime-routing class as SC02/9. Their
  jal-vote bases are low-confidence; onboarding on a guess would be P9 theater.

Resolution path: the **L3 emulator tour** (P31 bucket T) logs every load (payload → RAM addr →
len), delivering the 34 bases + R34-verification of the static addresses + evidence for any
never-loaded payload's out-of-scope call.

## S45 addendum (2026-08-07): the L3 tour ran — 29 of the 34 onboarded; parked = 6

The debug-menu tour (`docs/memory-map.md` §S45; menu list `docs/debug-menu-list.txt`) delivered:
- **All 28 script modules captured live and onboarded byte-identical** (`md_SC03_073…079`,
  `md_SC03_132…138`, `md_SC04_024…030`, `md_SC05_023…029` at the four byte-verified per-chapter
  slots). The interior↔module routing law is in memory-map §S45.
- **MAIN/3 DISCOVERED and onboarded** (`md_MAIN_003` — the main-menu module, id 0x39, live
  byte-proven at 0x800CEDF8). It had been mis-bucketed `classified-data` by BOTH oracles — the
  low-jr module class evades the L1 heuristic AND L2's carve. The **module-id census** (word0 ∈
  id-range + early prologue, run disc-wide) found **77 id-law code payloads, 72 claimed + 5
  parked, zero further misses** — that census is the third oracle for this class.
- **SC03/55 verdict: DATA, confirmed** (id-like word0 0x42 but zero prologues and zero `jr $ra`
  in 7,988 B; it is the data companion of modules 0x40/0x41/0x43).
- **Fleet: 183 → 212 binaries.** `make audit-disc`: **UNCLAIMED = 6, residue 0.**

**The parked-for-L3 ledger is now 6 payloads**, each with byte-checked negative evidence from the
tour (never present in RAM across boot/title/attract/menus/load/opening/endings/game-over and ~15
scene loads): **MAIN/7, MAIN/9, SC02/9, SC03/53, SC03/54, SC03/56.** Next tier: the CD-read
tracer (log `cdFileLocTable` index per read during play), not further scene-guessing.

## Reproduce
> **⚠️ S45: `tools/disc_code_sweep.py` is RETIRED (R33)** — superseded by `make audit-disc`
> (`tools/disc_audit.py`): whole-payload classification at BOTH the raw and LZSS layers, a
> residue-0 partition over the disc, and `claimed-by` derived from `config/check.<bin>.sha`.
> The commands below are kept for provenance of the 2026-07-15 findings; they no longer run.
```
tools/disc_code_sweep.py                 # (retired) the table above + the ranked hidden list
tools/disc_code_sweep.py --types 1       # (retired) just the type-1 code modules
```
