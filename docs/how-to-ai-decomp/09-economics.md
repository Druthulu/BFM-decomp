# 09 — Economics, as measured

Every number here is BFM's, with its denominator (R41), stated so another project can *calibrate* rather than copy.
The shape transfers; the constants do not. Every number was derived from a log, never hand-transcribed (R33): drafts
from the wave's own verdict file, banked from the whole-binary gate log — the gate is the arbiter, never the agents'
claim — instructions from the corpus census, tokens and wall-clock from the harness's agent timestamps.

## The whole project

| Quantity | Measured |
|---|---|
| Duration | 12 weeks (2026-06-10 → 09-07): 33 phases, ≈87 sessions, ≈4,040 commits, one human, one agent |
| Result | 218 binaries byte-identical; 363,214 functions (360,737 in C, 255,632 of them shared bodies via 2,220 dedup groups; 1,256 vendor-library functions linked; 5 hand-written-assembly bodies kept verbatim); 13.49 M instructions; 5.82 M distinct |
| Knowledge base | some 500 cookbook sections, a four-file codegen map, 80 decision-log entries, 73 numbered rules on top of the constitution's 25 |
| Tooling | ≈236 Python tools, 25 shell tools, 12 Ghidra scripts |

## Drafting yield

| Quantity | Measured |
|---|---|
| drafts → banked, fleet-wide | **34%** (8,885 drafts → 3,027 banked over 37 waves) |
| bank rate by function size | ~57% under 50 instructions · ~30% at 50–80 · ~22% at 80–120 · ~3% at 120–200 · ~6% above — **a fleet-wide curve over 37 waves, most of them before the integration tooling existed**; one late wave banked 16 of 16 with targets up to 397 instructions, another 7 of 16 at a median of 438, a hand pass 8 of 8 including a 579-instruction function. Read the curve with its denominator, or 120-instruction functions look hopeless |
| bank rate by population | the "hard" population banked 27–40% at small sizes — **the gap to the easy population was almost entirely size mix, not difficulty** |
| the prompt as the lever | over five consecutive waves with the models and the gate held constant, the bank rate rose from the mid-70s to 100%; the only variable was a block in the prompt harvested from the previous wave's agents' own "what the index lacked" reports. The targets also trended easier, so the claim that holds is the direction and the mechanism, not the percentage |
| standalone MATCH rate, the mature regime | 98–100% on six consecutive 65–73-card waves — and that variation is noise on a 70-card sample; **never report the 100% as a new floor** |
| claimed vs banked, per wave | the gate's number is below the agents' in every wave (15 claimed → 15, 13 → 10, 16 → 7 across three early waves); the gap is integration, not drafting, and the recovery ladder closes most of it (one wave: 18 of 45 banked on the first slate, and 26 of the 27 rejections were byte-perfect drafts; the reconcile lane's lifetime record 21 of 22) |
| cheap vs. strong drafters, ≤ ~50 instructions (A/B, 100 workers) | the same match rate at ≈4.8× lower cost per match |
| the cheap tier's honesty | 63 claimed matches → 63 real matches |
| a local 7B model | saturated the ≤ 15-instruction population for $0 |

## Throughput and capacity

| Quantity | Measured |
|---|---|
| provider rate ceiling | rejections ~0–3.5% up to ~95 req/min; 6.6–12.7% at 195–227; retries absorb it |
| per-worker request rate | 0.3–0.8 req/min, so ~350–400 concurrent workers sat at the knee |
| unattended throughput (the lane era) | ≈2,000 functions banked per day at a marginal model cost of roughly zero on a free tier |
| one phase's single session (the first harvest under fan-out) | the resident engine 1.4% → 71.7% byte-identical |
| one phase (the dedup engine) | the fleet 3.8% → 54% of functions |

**The single most useful economic fact: card supply, not model capacity, was the binding constraint** for most of the
campaign. The project repeatedly reached for more workers when the answer was more work items; once the excluded
population got its own lane, capacity stopped being the question.

## A wave, priced

The per-wave ledger the campaign kept (one row per wave: agents, tokens, wall-clock, banked), condensed. The early
waves are the orchestrated shape; T–V are the mature 6,500-instruction waves.

| Wave | Agents | Tokens | Wall | Effective parallelism | Banked |
|---|---|---|---|---|---|
| 1 | 25 | 6.87 M | 169 min | 4.8× | 15 heads + 65 free siblings |
| 2 | 19 | 4.51 M | 208 min | 2.7× | 10 + 18 |
| 3 | 14 | 2.73 M | 140 min | 2.1× | all + 21 |
| 4 | 17 | 2.99 M | 136 min | 2.5× | all + 26 |
| 5 | 19 | 2.71 M | 82 min | 3.8× | 16 of 16 + 26 |
| 6 | 24 | 5.20 M | 71 min | 7.4× | 7 of 16 + 25 (the hard knob: median target 438 instructions) |
| T | 87 | 8.71 M | 70 min | — | 70 heads + 49 mechanical siblings (4,954 instructions) |
| U | 86 | 7.42 M | 45 min | — | 73 heads + 34 siblings |
| V | 85 | 8.88 M | 71 min | — | 68 heads + 25 siblings |

The units that came out of that ledger: **170k–300k tokens per banked head** in the stable early regime, **~124k** in
the mature one; a harvest attached to a wave costs about a quarter of the wave again (19 agents, 1.97 M tokens on T);
recovery of gate drops costs ≈0 agent tokens (8 of 8 in one session, +4 in another — "the lane cost nothing and
returned four functions"); putting the banked twin on the card was worth **15% fewer tokens and 64% of the wall-clock**
for two more cards (U against T). Outages are a casualty count, not a rate: twelve agents died to server overload in
one wave without starting, two to rate-limiting in another.

## Instruction weight, not head count

Two waves with the same card count and opposite bank rates:

| | wave 5 | wave 6 |
|---|---|---|
| pool offered (templatable instructions) | 16,884 | 50,596 |
| heads banked | 16 of 16 | 7 of 16 |
| instructions in the banked heads | 2,753 | 2,204 |
| propagated members | 26 | 25 |
| total instructions banked | ≈7,200 (estimate) | 10,616 (exact; `make report` moved by 10,616) |
| pool realised | ≈43% | 21% |

The wave with the worse bank rate banked ~47% more instructions. **Head count flatters small-target waves; instruction
weight is what moves the fleet, and the metric to beat is pool realisation, not bank rate** — a wave banking 16 of 16
of a 17k pool is worth less than one banking 7 of 16 of a 50k pool. Wave T later beat both: 70 heads plus 49 siblings,
11,511 instructions for one wave's tokens. (Record the per-family member breakdown from the first wave; wave 5's total
is an estimate because it was not.)

## The gate's cost is paid in wall-clock

Tokens are one currency; a session that runs waves in series is bounded by the other. Each *gate group* is a
whole-binary rebuild, so the number to watch is groups per wave: **5 → 7 → 9 for the same ~6,500 instructions** across
three waves — the gate's cost per banked instruction rising while the bank rate held — then **3** once the draw
concentrated targets by binary (drafts per rebuild 7.8 → 24.3, roughly an hour back per wave). The concentration is a
*choice* at draw time, not a trend of the frontier: the "thinning" that looked like the frontier running out was a
default flag excluding one lever lane. And the floor under any wave's wall-clock is its slowest single chain (~50
minutes at 200–300 turns; one agent tested 470 statement orderings on a 793-instruction function), so past that point
the lever is target *selection*, not concurrency.

## Where the tokens went

| Sink | Cost | Of |
|---|---|---|
| Re-drafting functions that were already byte-correct and failed on plumbing | the dominant spend of the campaign phases: **≈92% of drafts byte-correct, ≈27% banked** at one measurement | the recovery tooling of the following phase is what closed the gap ([chapter 10](10-integration-and-propagation.md)) |
| Re-drafting functions whose banked twin sat two words away | ≈250k tokens before the twin rescan existed | one session |
| The last four functions | a 655k-token frontier agent on one row; 3,360-variant sweeps; ≈100 hand variants; ≈1 M tokens of dial work on a row whose answer was a grep and a sibling's spelling | Phase 32 |
| One wave of 31 drafters | ≈16 strong + 4 mid + 11 cheap agents, 30–70 min each on the strong tier, for 20 MATCH (2,111 instructions) + 9 exact-length seeds; plus ≈1 hour of the orchestrator's session to recover from the coordinator's death | one wave |
| Sessions lost to instrument diagnosis | "the cost was the diagnosis": three zero-token banks and five onboardings whose only expense was finding which tool lied; each one-off diagnosis 90k–290k tokens | recurring ([chapter 04](04-oracles-and-instruments.md)) |
| The private-era convenience of committing ROM-derived files | a full-history rewrite: ≈2 sessions of tooling, two rehearsals, 311 s of filter time, a Support ticket | Phase 33 ([chapter 11](11-publishing.md)) |
| Stale scratch | 12 GB of forgotten gate worktrees, each a full old-history checkout, found only when they pinned the old lineage against a gc | Phase 33 |
| Phase length vs. plan | the longest phase: 30 sessions against "10–18" — the ceiling kept moving because every instrument repair re-opened a class that had been called a wall | Phase 31 |

## What did not cost much

The mechanical banks. Once a tool existed for a class — twins, families, siblings, opt-level carves, propagation,
stranded boundaries — its members cost ≈0 tokens each. The zero-token pipeline of one phase (auto-drafts → symbol fixes
→ pre-checks → a lane gate) banked about 256 members for about no agent tokens, against an estimated ≈20 M as waves.
Per wave, the free siblings that followed the drafted heads ran 65 · 18 · 21 · 26 · 26 · 25 in the early waves and
49 · 34 · 25 · 0 · 1 · 4 in the mature ones — the zeros are the waves whose draw filled up on single-member functions.
The best single case: one 299-instruction head became 4,485 instructions across 15 siblings for ≈0 agent tokens. The
sweep yield is a property of the *family*, not the wave, and it is **bimodal, not average** — one wave swept 21 of 21,
the next 18 of 165, because the second wave's big families were per-location variants that do not template (settled by
probe: a remapped member that builds and is byte-different is genuine per-member codegen).
**The economics of the project are the ratio between that row and the table above**, and the bootstrap order of
[chapter 03](03-bootstrap-order.md) is about moving work from the second to the first.

## Budget for banking, not cracking

Once cracking was systematic (11 of 12 first-pass MATCH with ordinary agents and the codegen map), every bank failure
was translation-unit plumbing. Budget the integration layer as the main cost centre, not the drafting. Read the
"recovery is free" rows above carefully before generalising them: recovery was cheap because the drops were
declaration refusals on already-byte-verified drafts — the work was done and only the plumbing failed, and five
refusal classes collapsed into one move (bind a private C identifier to the link symbol instead of negotiating over the
shared one). A recovery lane over genuine near-misses is a different economy. **Budget recovery against gate drops;
treat near-misses as permuter fuel** unless a specific new law applies.

## The cost asymmetry that makes the harness obvious

A one-off diagnosis of a harness defect: 90k–290k tokens. A nightly disagreement report from two independent paths:
minutes of compute. About half of a typical late session went to harness defects wearing model-failure costumes.
