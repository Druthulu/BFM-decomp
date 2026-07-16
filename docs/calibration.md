# Endgame calibration — measured rates for P28/P29 sizing (Phase-27 T9)

> The roadmap (§6 risk register) makes the **member-adapt close-rate** THE swing number and holds
> P28/P29 yield projections until it's measured. This records what Phase-27 could measure directly and
> names honestly the one number that needs P28's `member_adapt` tool to pin down. All rates are
> byte-gate-grounded (G3/P9) — a "match" here means the whole-binary gate accepted it.

## Velocity (the flip-timing checkpoint input)

| | value | note |
|---|---|---|
| instr-weighted, Phase-26 close | 68.9% | committed baseline |
| instr-weighted, Phase-27 close | **67.0%** | a re-baselining DOWN, not a regression |
| game-code matches banked this phase | **~0** | Phase 27 was an INFRASTRUCTURE + FINDINGS phase |

The headline **dropped** because T7's disc-completeness audit added 4 SC07 overlays (~2.45 MB of mostly-
unmatched code) to the denominator — the prior 68.9% was measured over an incomplete disc. Raw match
velocity this phase was ~0 (no harvest ran), but the phase's product is leverage on FUTURE velocity: the
tool fixes (T2/T4/T6) and the pin-crash-wall dissolution (T5) unblock work the prior tooling hid. **For
the flip decision: do not read Phase-27 as ~0 progress/session — it is a denominator correction plus a
set of unblocking findings; the next harvest phase (P29) is where velocity resumes and should be
re-measured there.**

## The templatability swing (the number that decides P28/P29 yield)

Two propagation regimes, both byte-measured this phase:

| regime | rate | evidence |
|---|---|---|
| **h_exact reach-N core** (byte-identical across N overlays) | **≈ ×N, near-100%** | §52 (Phase 26): 5 cracked cores → **670 banked instances** = ×134 each, mechanical |
| **h_seq / h_norm structural family** (same skeleton, per-overlay byte-variants) | **≈ 0%** | `0x8017BEBC` (T5): 106/112 members STAGE cleanly (macro-carry fixed), but **0 of 8 bank** — all genuine byte-DIFF |

**This is the decisive P28/P29 input.** The roadmap's B1/B2 hoped the large `h_seq` families were a
cheap mechanical harvest; the byte-gate says they are **not templatable** — the structural (h_seq) match
is necessary, not sufficient. So the remaining yield is NOT "template ×120 the 986 families"; it is
**per-member cracking** for the structural families and **mechanical ×N only for the h_exact reach-N
cores**. The current 223-live-stub frontier: **101 reach-134** (h_exact — ×134-able IF the core cracks),
119 reach-1 (×1), 3 mid. So the P29 arithmetic is: (cores cracked) × (their reach), NOT (families) × 120.

## Cost / yield per tier (this session)

| tier | cost/fn | direct banks | durable yield |
|---|---|---|---|
| **Fable5** (discovery) | **~230k tok/fn** (238k/257k/270k/199k measured) | **0 / 5** | 3 oracle reclassifications + 2 cracked roots + **the pin-crash wall dissolved** + 4 new pin-free levers (cookbook §H) |
| cheap-Opus (apply idioms) | ~40–140k tok/fn (Phase-23/26 data) | the §52 wave: 5 cores | applies Fable5's idioms; the productive banking tier |
| permuter | CPU-only ($0) | regalloc/schedule drift | 7 all-time (all Phase-21); tail exhausted |
| local v3 | $0 | the ≤15-ins band | ~1,300 (Phase-23); off the hard tail |

**Fable5's ROI is NOT banks — it is idioms + wall-dissolutions** (the doctrine held perfectly this phase:
0 banks, but a propagation wall down and the codegen map extended). Budget Fable5 for *discovery*, then
harvest cheap-Opus against the distilled idioms. The perishable Fable5 window (~7/19) is spent on the
hard un-drafted cores + wall characterization, never on functions cheap-Opus can apply a known idiom to.

## The one number that needs P28 (honest gap)

**Member-adapt close-rate on REGISTER-DRIFT members** — the roadmap's headline swing — was NOT directly
measurable this phase: it needs P28's `member_adapt` tool (the exemplar→member delta engine) to try each
drift member and gate it. The bounding data: the refusal taxonomy's register-drift class is the *only*
adaptable one (§52 levers, ~⅓ pin-free crack rate per walled cluster), collision members filter out, and
pin-crash members are now UNBLOCKED (T5) rather than ×1-capped. **P28 opens by measuring this on a
byte-gated sample before P29 scales — exactly as the roadmap's risk register prescribes.**

## New lever this phase (not in the roadmap's projections)

The **pin-crash wall is dissolved** (T5 + `.run/giants/pin_crash_sigabrt.md`): the ~20 PINS-class stubs
in the manifest (and the 4 characterized pin families) were routed to the ×1 backlog as "cc1-crash /
intrinsic"; they now stage clean and are mechanically harvestable (byte-identity per sibling is the
gate's question, but the crash barrier is gone). This is un-projected P29 fuel — a whole reach-N class
the roadmap wrote off, back on the table.
