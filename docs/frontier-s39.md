# Frontier snapshot — P30 S39 close (2026-08-05, ~01:00)

Derived fresh from `corpus.stubs` + the sigs (regenerate any time:
`.run/s39/frontier_snapshot.txt` is the raw output). **Reconciled** against every other "what's
left" view by `make audit-frontier` — see that gate's output for disagreements.

## The whole open frontier

**13,312 open stubs / 741,792 instructions across 140 binaries.**

### The single biggest target is now `main`

| binary | open ins | open stubs |
|---|---:|---:|
| **main** | **79,074** | **2,001** |
| ov_SC02_005 | 18,266 | 381 |
| ov_SC04_011 | 15,366 | 285 |
| ov_SC06_033 | 13,302 | 147 |
| ov_SC06_032 | 13,149 | 169 |
| ov_SC03_028 | 13,031 | 203 |
| ov_SC02_011 | 13,017 | 260 |
| ov_SC06_029 | 12,942 | 178 |
| ov_SC06_018 | 12,504 | 169 |
| ov_SC06_024 | 12,243 | 170 |

**`main` is 10.7% of all open instructions** — and it only became *visible* at this size tonight:
its Ghidra sig was 7 weeks stale and covered 1,525 of 2,002 stubs, so 477 of them (19,309 ins) were
invisible to every metric and every target selector. That is the R36/R34 lesson repeating: work a
consumer cannot see does not exist to planning.

`main` is also the least tractable per instruction — it is structurally barren (zero `h_exact`
overlap with the overlays; "main is not free dedup" was checked two ways in S31/32 and both were
negative), so it is the genuine ~490-tok/ins agent tail, not a mechanical harvest.

### Overlay open stubs by size (main excluded)

| band | stubs | ins |
|---|---:|---:|
| ≤20 | 2,003 | 31,413 |
| 21–50 | 5,243 | 173,862 |
| 51–150 | **3,246** | **264,784** |
| 151–400 | 765 | 155,807 |
| >400 | 54 | 36,852 |

The mass is the **51–150 band (264,784 ins)** — too big for the free local ≤15 tier, well inside
what the §17–§45 toolkit handles. The >400 tail is only 54 stubs / 36,852 ins.

## What is measured, and what is still assumed

- **Measured tonight:** the free `h_exact` pool (§142) is now 66 instances / 1,061 ins, all
  macro-backed — the cheap mechanical vein is essentially spent at this address-identical tier.
- **Measured tonight:** stored-draft re-gate rates by population — 4/6 fresh, 1/12 general stored,
  3/17 reverted-overlay, 8/35 draft-exemplar heads (`docs/calibration.md`).
- **Still assumed:** the frontier report's h_norm cluster pool (1,689 clusters / 326,261 ins at a
  claimed 2.7× multiplier). **Its whale claim was 3/4 wrong** (§142), so this number must be
  re-measured before a wave is scoped onto it — that is S5's first step, not its premise.
- **Still open (denominator):** the 39 un-onboarded type-1 modules and main's missing independent
  boundary oracle. Neither is in the 741,792 above, because nothing can see them yet.

---

## Burn-down (T5 prep) — derived from the committed digest history (R33), not a hand-kept series

| day | instr-weighted | Δ |
|---|---:|---:|
| 2026-07-22 | 78.65% | — |
| 2026-07-23 | 79.36% | +0.72 |
| 2026-07-24 | 79.91% | +0.54 |
| 2026-07-25 | 80.57% | +0.66 |
| 2026-07-26 | 81.70% | +1.13 |
| 2026-07-27 | 84.40% | +2.70 |
| 2026-07-28 | 86.56% | +2.16 |
| 2026-07-29 | 87.18% | +0.62 |
| 2026-07-30 | 88.20% | +1.02 |
| 2026-07-31 | 89.16% | +0.96 |
| 2026-08-01 | 92.41% | +3.25 |
| 2026-08-03 | 93.71% | +1.29 |
| 2026-08-04 | 94.50% | +0.79 |
| **2026-08-05** | **94.36%** | **−0.14** |

**⚠️ READ THE LAST ROW CORRECTLY — it is NOT a regression, and T5 must not report it as one.**
The numerator ROSE on 2026-08-05 (12,419,002 → 12,419,169). The percentage fell because the
**denominator** grew 13,141,652 → 13,160,961 (+19,309) when main's stale sig was regenerated and
477 previously-invisible stubs entered the count. Same shape as Phase 27's 68.9% → 67.0% when four
hidden overlays were onboarded: **an honest denominator moves the headline down.**

This is precisely the failure mode S1e caught at the other end of the same session — a percentage
compared across a changed basis, read as a movement in the work. The rule (§140): *a committed
number is a claim about a tree; if it cannot be recomputed from that tree it is not evidence.* Here
both numbers are recomputable and correct; what changed is what they are numbers OF.

For phase-over-phase continuity the digest also prints the main-excluding series
(`fleet EXCLUDING main`), which is the apples-to-apples comparison against pre-2026-07-22 readings.
