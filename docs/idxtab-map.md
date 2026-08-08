# The master IDXTAB / DESTPTR load map (S46)

**Tool:** `tools/idxtab_map.py` (regenerate: `tools/idxtab_map.py` → `.run/idxtab_map.json`;
`--controls-only` runs just the validation). **Depends on:** `tools/find_addr_refs.py` (the one
register-tracker, R33).

Repeats the §S45-p6 `ov_SC03_001` decode for **every onboarded binary**: which payloads a binary's
index tables request, and where its wrapper loads them.

---

## What was actually blocking this (the S45 "one idea still needed")

The plan was "find `-1`-terminated s16 index runs, then require a register-verified code reference to
the run's address." Run as specified it returns **nothing**: `0x8018D7BC` (the byte-proved
`ov_SC03_001` table) has **zero** register-verified references and is **not stored as a data word
anywhere in the fleet**. The table looked unreachable.

It was not. **Our register-tracker was blind to gcc's indexed global-array read:**

```
80128CA4: 3C018019   lui  $at, 0x8019
80128CA8: 00240821   addu $at, $at, $a0        <- index add; the tracker killed $at here
80128CAC: 8422D7BC   lh   $v0, -0x2844($at)    -> 0x8019<<16 + (-0x2844) = 0x8018D7BC
```

The address is split across the `lui` and **the load**, with the index added in between. `find_addr_refs`
invalidated the `lui` register at the `addu` (it *is* written), so the pair was never reconstructed and
the load looked like an offset off an unknown register. Carrying the hi half through the add — still
strictly register-tracked, never window-paired (§155) — recovers it. Loads reached this way are labelled
`-indexed` so the two shapes stay distinguishable.

This is the third time a "structural wall" in this project was our own instrument (R35).

## Controls (R32/R35 — the tool refuses to emit a map if these fail)

| binary | IDXTAB | DESTPTR |
|---|---|---|
| `ov_SC01_000` | `0x8017EEC8`, 37 entries ✓ | `*0x801A3234 = 0x801A58E8` ✓ |
| `ov_SC03_001` | `0x8018D7BC`, 5 entries ✓ | `*0x801EBC68 = 0x801EF468` ✓ |

Both byte-proved rows from `docs/memory-map.md` reproduce **from the images alone**. The global index
space is derived from the extracted tree, not hardcoded, and independently reproduces §S44's table
(`MAIN@0, SC01@49, SC02@135, SC03@178, SC04@318, SC05@349, SC06@379, SC07@418`, total 447).

## Is it 100% correct? No — here is exactly what it is

**Validated, not proven complete.** Precision is high and measured; recall is unmeasured beyond two
controls. Use it as a lookup with that caveat, never as proof of absence (see MAIN/7+9 below).

| claim | status |
|---|---|
| the two byte-proved rows reproduce from the images alone | **PROVEN** (controls, tool refuses to emit otherwise) |
| the read mechanism (`lui`/`addu`/`lh`) | **OBSERVED** in the disassembly at named addresses |
| the global index space (`MAIN@0 … SC07@418`, 447 total) | **DERIVED** from the extracted tree; independently reproduces §S44 |
| DESTPTR values | **141/141 read from each binary's OWN image** (no cross-image guessing) |
| the 283 fleet-wide-class tables (5-entry ×142, 37-entry ×141) | **HIGH** — identical content across 141 binaries; coincidence is not a plausible explanation for that |
| the 3 rare-class rows | **LOW** — listed by name below; treat as candidates |
| **completeness (recall)** | **UNMEASURED.** A table reached by a form the tracker does not model is invisible, and no independent oracle for "all tables" exists. Two controls is what we have. |

The three low-confidence rows, named so nobody inherits them as fact:
`md_SC07_004 @0x801B0020` (2 entries), `ov_SC03_028 @0x8018F9FC` (7), `main @0x80063138` (18).

## The fleet result

213 binaries scanned → **143 carry a referenced index table (294 tables), 141 carry a DESTPTR**,
**61 distinct payloads** requested. (A first pass reported 452 tables: 106 were runs of ZEROS ending in
`0xFFFF`, and another ~26 were majority-zero data — both filtered in the tool, not in the write-up.)

**The two dominant tables are fleet-wide CONSTANTS — identical content in all 141 overlays (283 of the
294 tables):**

| table | ×141 content |
|---|---|
| 5-entry | `SC03/46, SC03/53, SC03/54, SC03/56, SC03/55` |
| 37-entry | `SC03/62-65, SC02/32-33, SC02/12-14, SC02/18-20, SC03/128-131, SC01/53-73` |

The per-binary variable is the **DESTPTR**: 141 binaries, **134 distinct destinations** (the repeats are
the known duplicate-overlay pairs). So the shape is *constant list + per-binary destination + a runtime
index* — which is exactly what the `addu` index in the read above is for.

### ⚠️ This CORRECTS `memory-map.md` §S45 p6 (R14)

§S45 p6 concluded the SC03 trio are "LIVE script modules **owned by `ov_SC03_001`**" and that "only the
scene(s) backed by `ov_SC03_001` request them." **The fleet scan refutes the ownership half:** the
5-entry table containing `SC03/53/54/56` is present, with identical content, in **all 141 overlays** —
`ov_SC03_001` is not special. What remains true is everything that was byte-observed: the trio are live
script modules, reached through `func_80128CFC`, and `ov_SC03_001`'s own destination is `0x801EF468`.

## ⚠️ What this does NOT settle: MAIN/7 and MAIN/9

They are absent from all 294 tables. That was hoped to be "the strongest dead-code evidence obtainable."
**It is not, and the map itself proves why.** The MAIN payloads any IDXTAB references are:

```
referenced: 0 1 4 6 8 17 33
absent:     2 3 5 7 9 10 11 12 13 14 15 16 18 19 20 21 22 23 24 25 … (42 of the 49)
```

`MAIN/13`, `MAIN/20`, `MAIN/34`, `MAIN/42`, `MAIN/44` are **byte-proved to load** (they are the
onboarding controls in `.run/s45p5/derive_base.py`) and they are absent from every index table too. So
absence from the IDXTAB route says only that a payload is not loaded *by that route* — the descriptor
path (`StreamLoadStateMachine`) and the `resourceIdMap` path are separate. **MAIN/7 and MAIN/9 remain
unresolved, and this route cannot close them.** Recording that here so a later session does not
re-derive the same false conclusion from the same table.

## What the ledger IS good for

- **payload → requesting binaries** for the 61 payloads on this route (`.run/idxtab_map.json`).
- **binary → destination** for 141 binaries (the DESTPTR half), which is the "where does it land"
  question for anything loaded through `func_80128CFC`.
- A reusable, controlled instrument: any future "who loads X?" question on this route is now a lookup,
  and any answer it gives is gated by two byte-proved controls.
