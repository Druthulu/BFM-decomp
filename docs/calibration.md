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

## The LEGACY h_seq rate — measured, CLASSIFIED (Phase-28 T3b, 2026-07-16)

The roadmap's actual swing number is the *legacy* h_seq rate (the SC07 pool T3-A measured turned out to
be h_exact + unwired, a different question). A bounded `family_sweep --hseq --chunk 1` over **6 legacy
PURE non-jr families** (smallest-nins first; `has_mid_jr` excluded per §53) gated:

| | count |
|---|---|
| **BANKED** (whole-binary) | **9** |
| **PLUMBING** (recoverable class) | 37 |
| **DIFF** (genuine gate byte-mismatch) | **274** |
| skipped (not-stub / pinned-exemplar) | 173 |

**~3% as-tooled (9 of 320 attempted).** *Unlike Phase 26, the failures are CLASSIFIED* — 274 genuine
gate-DIFF, not an unclassified 0%.

**But the DIFF is NOT structural variance, and this is the load-bearing nuance (R14/R35 on my own probe):**
the members are byte-level **PURE** (`classify_member` = PURE, reloc-only, 20/20 sampled), **genuine
h_seq** (all DIFF_BYTES vs the exemplar → `family_sweep` is the correct tool, not `dedup_extend`), and at
the **same vram**. A PURE family should template once its relocs are remapped. That 274 members do NOT
reproduce means the remapped exemplar body **fails to reproduce the member's bytes when recompiled** — i.e.
the residual is **recompilation divergence**, one of:
- **(a) an incomplete remap** — `symbol_map` not covering a symbol class these families use (the recurring
  jtbl/prefix bug: B2's 0/8, T4's 12 DIFFs — *both* turned out to be tooling this phase); or
- **(b) genuine TU-context regalloc divergence** — the same C compiling to different bytes in different
  overlay TUs (a real wall).

**These are the SAME two hypotheses B2 and the SC07 pool presented, and BOTH resolved to (a) tooling this
phase.** So the honest swing number is: **~3% as-tooled, ceiling UNKNOWN** — provisionally consistent with
"legacy h_seq largely doesn't mechanically template", but on a probe whose dominant failure mode is the
exact tooling-vs-wall ambiguity that keeps resolving to tooling. **P29 must run the disambiguating probe
before trusting 3%:** take one PURE DIFF member, diff its `family_sweep`-staged compiled bytes against the
target region-by-region — if the mismatch is at a reloc position, it's (a) incomplete remap (fixable); if
it's regalloc/schedule away from relocs, it's (b) a TU-context wall. Do NOT scale P29's "(cores)×(reach)"
arithmetic on 3% until that probe runs.

## The swing number RESOLVED — (a) TOOLING, an -O0 compile-flag artifact (Phase-29 Task 1, 2026-07-16)

The disambiguating probe RAN. **Verdict: the legacy-PURE-non-jr "~3%" is (a) TOOLING — dominated by an
`-O0` COMPILE-FLAG artifact — NOT a TU-context regalloc wall.** Built `tools/diff_regions.py` (the
deferred roadmap tool): remap the exemplar EXACTLY as `family_sweep --hseq` stages it, compile at the
EXEMPLAR's real optimization level (auto-detected from the Makefile -O0 rules), masked-diff vs the target,
classify each member (`O0-FLAG` / `TEMPLATES` / `PLUMBING-ISO` / `REGALLOC` / `NO-TARGET`).

**Root cause (byte-proven).** The two families supplying **~272 of the 274 DIFF** (`0x8013c964`,
`0x8013c938`) are **-O0 functions** — their exemplar lives in `ov_SC01_077_o0.c` (the Phase-19 -O0 cluster,
vram 0x8013B568..0x8013C98C, `21F0A003` frame-pointer prologue). `family_sweep --hseq` stages the remapped
draft into the member's CURRENT stub file, which compiles **-O2** (the Makefile -O0 rule covers ONLY
`ov_SC01_077_o0.o` / `boot.o` / the whale `_o0b` wildcard). An -O2 compile of an -O0 target can NEVER match
(a frameless ~4-ins leaf vs the 10-ins -O0 frame — `match_one`'s own `--o0` flag exists for exactly this).
Compiled at **-O0** the remapped C masked-MATCHes: `func_8013C964`@ov_SC01_000 → MATCH(10),
`func_8013C938` → MATCH(11); the -O2 compile the sweep used DIFFs(10/11).

**Distribution (106-member sample, 11 matched PURE-non-jr families, nins 2..133):**
`O0-FLAG 45 · NO-TARGET(already-banked) 29 · TEMPLATES(at exemplar opt) 17 · PLUMBING-ISO(type-lift) 15 ·
REGALLOC 0`. **ZERO genuine codegen walls.** Every failure mode is recoverable tooling: the -O0
compile-flag, already-banked, template-clean, or the §40a/§8d type-lift plumbing (a `match_one`-isolation
blind spot the real TU carries via `engine_types.h`; `family_sweep --no-preclassify` resolves it).

**Honest scope (§52b, R14/R35).** These are masked-MATCHes — a CANDIDATE, not a whole-binary bank. But the
fix is an INDEPENDENTLY byte-proven mechanism: the -O0 split (the whale banks ×134 via exactly this;
`ov_SC01_077_o0.c` banks byte-identical for THIS cluster in ov_SC01_077) + the §8d/§40a recovery (~20k
members banked so in Phase 25/26). **Whole-binary banking + the TRUE ceiling (larger families) are P29
Task 2a's gate — a prediction, gate-validated there.** Caveat carried: one cluster fn (`func_8013B7AC`,
%lo-fold) was called "overlay-local" in Phase 20 — Task 2a byte-gates EACH cluster member, never assumes
all 16 template.

**Consequence.** The "~3% as-tooled ceiling" is RETIRED (a tooling artifact — the THIRD "structural wall"
this endgame resolved to tooling, after B2 and SC07). P29's member track is NOT a low-ceiling per-member
grind; it is a **mechanical -O0 split rollout** (the deferred "-O0 ×134") + the type-lift sweep. The
~478k-ins legacy-PURE pool is back on the table. `member_adapt.py` (the (b)-wall delta engine) is NOT
needed for this pool. (Full run: `.run/probe29/`; tool: `tools/diff_regions.py`.)

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

---

## Stranded-draft integration recovery — measured 2026-07-24 (Phase 29 SESSION-16)

Population: the 36 stranded drafts of waves s14+s15 (`ov_SC07_006`, all reach-138), i.e. the drafts a
wave produced and the whole-binary gate rejected.

| question | measured |
|---|---|
| of the STRANDED residue, how many are byte-correct? | **24/36 MATCH, 11 near, 1 ERR (67%)** — the "~92%" is a whole-wave figure |
| blockers (they stack; cc1 shows only the first) | `self_decl_hdr` 21 · `callee_decl` 19 · `data_decl` 16 · `self_decl_tu` 5 · `local_type` 5 |
| per function, by MAX tier | T0 = 6 · T1 = 26 · not-an-integration-problem = 4 |
| yield of the EXISTING draft-side ladder | clears its own classes (callee 19→3, data 16→0) but converts **1/36** to compiling, which then DIFFs |
| yield of the per-overlay de-macroize (§65b) | 13/14 clean candidates rtu-MATCH; **14/14 attempted banks succeeded** |
| **total recovered** | **14 of 36 = 39%** (vs a pre-session projection of "all 22") |
| implied wave multiple | ~6/24 → ~20/24 = **~2.3×**, NOT the projected 3.7× |
| metric shape | distinct-code **+14 unique fns**; instr-weighted / fn-count ~flat (de-macroized banks are ×1) |
| R22 after each batch | **140/140**, three times — the T1 blast-radius claim holds |

Remaining, named (not silently dropped): 10 `match_one`-MATCH drafts still blocked by stacked classes
(3 `self_decl_tu` → `normalize_self_decls`; 3 `local_type`+`self_decl_hdr` → draft type uniquify then
de-macroize; 1 struct-tag redefinition; 1 callee-decl that rtu over-claimed; 2 with no static blocker
whose real cc1 error needs reading). 11 `near` drafts are NOT recovery fuel — they are unfinished
drafts and belong to the permuter/redraft track.
