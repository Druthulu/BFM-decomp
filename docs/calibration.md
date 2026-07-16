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

> ### ⚠️ CORRECTED 2026-07-15 (Phase-28 T1) — the ≈0% row below was measuring a MISSING BUILD STEP.
>
> The Phase-27 row said `h_seq family ≈ 0%`, on the strength of `0x8017BEBC` banking **0 of 8**, and that
> number rewrote the endgame ("P29's arithmetic is (cores cracked) × (reach), NOT (families) × 120",
> `PhaseEnd_Phase27` Roadmap delta). **It is refuted.** The same family, same era, through the carve path
> its own exemplar required: **8 of 8 BANKED** (4 same-address + 4 cross-address; `make clean` +
> extract-all + `check-all` → **140/140 byte-identical**).
>
> **Root cause — the probe used a tool with no carve step.** `0x8017BEBC` is a **jr/switch** core. §47
> banked its exemplar as *"lazy isolation → carve (9-piece interleave) → splice → BYTE-IDENTICAL"* and
> stated the fix is *"×N template-safe"*. `family_sweep.hseq_sweep` stages C and gates — it has **no
> carve step**, so gcc's generated jump table is never placed at the sibling's address. The entire
> residual I byte-verified is **two words**: `lui $at,%hi(jtbl_801EC44C)` / `lw $v0,%lo(jtbl_801EC44C)($at)`
> (`classify_member` → **PURE, ndiff=2**, positions 343/345). `config/overlays.mk:112` carves
> `ov_SC01_000_jr_8017BEBC.o` for the exemplar; `:134` has no such entry for the member. The 0/8 measured
> the omitted carve, not the family. **`tools/jtbl_family_bank.py` exists to do exactly this per sibling
> and had never been run on this family.**
>
> **Compounding:** the family is one of only **3 of 163** with `has_mid_jr` — i.e. the roadmap generalized
> from n=1, on the least representative family in the population, using the wrong tool for its class. And
> the three Phase-26 exhaustion probes it corroborated (tiny-IMM 0/241, PURE 0/134, pinned 0/133) all
> **predate** `_carry_macros` (Phase-27 T5, `commit:0637`) — Phase 27's decision-log itself calls its re-probe
> "a **fourth** phantom exhaustion proof" while never re-running the first three. **R35: a 0% from a broken
> tool and a 0% from a working one are the same number and opposite facts.**

Propagation regimes, byte-measured (the whole-binary gate is the only entry here — G3/P9):

| regime | rate | evidence |
|---|---|---|
| **h_exact reach-N core** (byte-identical across N overlays) | **≈ ×N, near-100%** | §52 (Phase 26): 5 cracked cores → **670 banked instances** = ×134 each, mechanical |
| **h_seq family, jr/switch core, WITH the per-sibling carve** | **8/8 on a bounded probe** (n=1 family) | `0x8017BEBC` via `jtbl_family_bank.py --raw` (P28 T1): 4 same-addr + 4 cross-addr (`to_addr`), 140/140 clean-fleet |
| **h_seq family, jr/switch core, WITHOUT the carve** | 0/8 — **an artifact, not a rate** | the P27 T5 probe (`family_sweep`, no carve step). Do not cite this as templatability evidence. |
| **h_seq family, non-jr (PURE / IMM / MIXED)** | **UNMEASURED** | the three Phase-26 probes are pre-`_carry_macros` and were never re-run → P28 T3 |

**The honest state of the swing number.** The ≈0% doctrine has **no surviving post-fix evidence**. What
T1 establishes is narrow and real: a jr/switch family templates at 8/8 *when the carve its exemplar
required is actually performed*. What it does **not** establish is a general rate — n=1, and jr is by
construction the rarest class (3/163 families). **The general rate is exactly what P28 T3 measures**, over
the population that actually exists (from the T0-fixed map): **1,418 matched-exemplar families / 21,889
unmatched members** — PURE 17,024 (78%) · IMM 4,473 (20%) · **STRUCT 392 (1.8%)**.

**Note the roadmap's swing number is aimed at the wrong class.** It sizes P28/P29 on the *register-drift*
(STRUCT) close-rate — **1.8%** of the input. The mass is PURE+IMM (98%).

**The addressable pool (T0, from the fixed map).** 937,248 ins = **21.7% of all remaining weight** =
**7.16pp of fleet instr if it all banked**, all behind an already-matched exemplar:

| stratum | families | members | ins |
|---|---:|---:|---:|
| **SC07-only** (unmatched ONLY in the 4 P27 overlays; exemplar already byte-proven) | 1,255 | 6,268 | 230,612 |
| legacy PURE non-jr | 95 | 7,993 | 478,379 |
| legacy IMM (incl. `0x8017BEBC`: 115 members × 952 ins ≈ 109,480) | 36 | 6,644 | 212,707 |
| legacy MIXED | 30 | 968 | 10,462 |
| legacy PURE w/ jr | 2 | 16 | 5,088 |

This is a **prediction** (h_seq predicts; the gate decides). T3 gates it before P29 scales.

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
