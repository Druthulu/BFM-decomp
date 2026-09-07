# 09 — Economics, as measured

Every number here is BFM's, with its denominator (R41), stated so another project can *calibrate* rather than copy.
The shape transfers; the constants do not.

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
| bank rate by function size | ~57% under 50 instructions · ~30% at 50–80 · ~22% at 80–120 · ~3% at 120–200 · ~6% above |
| bank rate by population | the "hard" population banked 27–40% at small sizes — **the gap to the easy population was almost entirely size mix, not difficulty** |
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
**The economics of the project are the ratio between that row and the table above**, and the bootstrap order of
[chapter 03](03-bootstrap-order.md) is about moving work from the second to the first.

## Budget for banking, not cracking

Once cracking was systematic (11 of 12 first-pass MATCH with ordinary agents and the codegen map), every bank failure
was translation-unit plumbing. Budget the integration layer as the main cost centre, not the drafting.

## The cost asymmetry that makes the harness obvious

A one-off diagnosis of a harness defect: 90k–290k tokens. A nightly disagreement report from two independent paths:
minutes of compute. About half of a typical late session went to harness defects wearing model-failure costumes.
