# How to AI-decomp — read me first

**What this is.** Thirteen chapters on running a byte-exact decompilation with AI agents, written at the close of the
Brave Fencer Musashi project (218 binaries byte-identical from C, 100% of the game code, twelve weeks, one human and
one agent) for whoever runs the next one — a different console, a different compiler, a different game. They are
distilled from records the project kept *as it happened*, not from memory: the decision log's hindsight entries, the
PhaseEnds' "what we believed" sections, the accelerators ledger, the wave playbook, and the retrospective. Where a
chapter states a number, it is a BFM measurement, given with its denominator so you can calibrate rather than copy.

**Who it is for.** Someone who has (or can get) the four prerequisites and wants to spend their effort discovering
their compiler's idioms instead of rediscovering how to run a decomp:

1. a byte-exact target — an original binary you must reproduce exactly;
2. a build you control that can in principle reproduce it (the right compiler, flags and link order — establishing that
   triple is prerequisite work, and [chapter 03](03-bootstrap-order.md) says how to do it by evidence);
3. a splitter/disassembler that emits per-function assembly and a layout config (splat or equivalent), so work can be
   addressed one function at a time;
4. cheap parallel model capacity — not necessarily frontier models ([chapter 08](08-models-and-budgets.md)).

## The thesis in one paragraph

Pin the compiler by evidence and make a whole-binary byte gate the only judge; treat every tool as a suspect before
every function; build the things that compound — dedup, propagation, the codegen map, the reproducer battery — before
the things that pay once; keep the perishable *why* in a decision log written during the session that learned it;
write hand-offs to be replayed; and keep the game's bytes out of the repository from the first commit. Everything else
follows from those, at a cost that is mostly the diagnosis of one's own instruments. Almost every "wall" the project
recorded — a third of one phase's compiler walls, two formal proofs of unmatchability, a month of a gate comparing
against the wrong hash — was one of its own instruments.

## The chapters

| | Chapter | One line |
|---|---|---|
| 01 | [Governance](01-governance.md) | A static constitution, two human gates per phase, autonomy between them, rules that accumulate, a digest, and a checkpoint written to be replayed — what let ~99% of the work be the agent's without drifting |
| 02 | [The byte gate](02-byte-gate.md) | The one non-negotiable: a function is done when the whole binary still hashes with it compiled from source; everything else is a filter |
| 03 | [Bootstrap order](03-bootstrap-order.md) | The order that front-loads what compounds: baseline → pin by evidence → honest census → propagation and integration tooling → the codegen map and the permuter → then crack, leverage-first |
| 04 | [Oracles and instruments](04-oracles-and-instruments.md) | A correctness oracle is blind to coverage; every scanner asserts its own denominator; a second disagreeing oracle; fix the instrument before trusting the measurement |
| 05 | [Cards, lanes, waves](05-cards-lanes-waves.md) | The unit of work handed to a model, the lanes with different clocks, draw-time refusal of work that cannot bank, and the wave procedure with each guard's measurement |
| 06 | [The knowledge base](06-knowledge-base.md) | The cookbook, its symptom index, the harvest→distil→next-card flywheel, the inert-lever law, and why a name on a card must resolve in the base |
| 07 | [The compiler's source](07-compiler-source.md) | Reading the actual passes turns "unsteerable" into a catalogue of pass → residual → lever; reproducers before probes; a wall verdict names the pass and the dump line |
| 08 | [Models and budgets](08-models-and-budgets.md) | Route by measured difficulty, budget per lane, keep the strongest model for new wall classes, treat cheap verdicts as filters; the effort doctrine for the orchestrating agent |
| 09 | [Economics](09-economics.md) | What it cost, with denominators: drafts→banked by size, the token sinks, the free tiers, card supply as the binding constraint |
| 10 | [Integration and propagation](10-integration-and-propagation.md) | Matching is solved; banking a correct body past its translation unit is the bottleneck — the reconcile ladder, dedup and families, and "commit the moment it exists" |
| 11 | [Publishing](11-publishing.md) | Keeping ROM bytes out from day one, or paying for a full-history rewrite; the contract run; generated numbers; no-ROM CI; what to release |
| 12 | [The failure museum](12-failure-museum.md) | The failures that looked right at the time, each with why it looked right and the rule it produced |

## What transfers, and what does not

**Transfers:** the gate discipline, the oracle ladder, lanes and cards, draw-time refusal, free-before-paid, per-population
clocks, model routing, the flywheel and its inert-rider law, the governance cadence, the publishing discipline, and the
*shape* of the economics (not its constants).

**Does not transfer:** the compiler idioms themselves. BFM's knowledge base is some 500 sections of gcc 2.7.2 behaviour
and a codegen map of its passes; another target needs its own, built the same way. **The knowledge base is per-compiler;
the machine that builds it is universal.** That is the whole point of these chapters.

## The records these chapters are distilled from

- [`docs/portable-decomp-workflow.md`](../portable-decomp-workflow.md) — the system, written target-agnostic during the campaign
- [`docs/hindsight-study.md`](../hindsight-study.md) — the optimal *order*, with seven meta-principles, tagged UNIVERSAL / COMPILER-CLASS / BFM-SPECIFIC
- [`docs/generic-decomp-package.md`](../generic-decomp-package.md) — what the next project should inherit on day one
- [`docs/accelerators.md`](../accelerators.md) — what was learned late that day one should know, each entry dated with when it *could* have been found
- [`docs/retrospective.md`](../retrospective.md) and [`docs/story.md`](../story.md) — what we believed, what failed, what it cost; and the narrative
- [`docs/wave-playbook.md`](../wave-playbook.md) — the running procedure, each guard paired with the measurement that earned it
- [`docs/decision-log.md`](../decision-log.md) — every pivot with its measurement and hindsight; [`docs/effort-map.md`](../effort-map.md) — the reasoning-effort doctrine
- [`phase-ends/DIGEST.md`](../../phase-ends/DIGEST.md) — every phase's synopsis and the full text of every rule cited here as `R<n>`

The framework the governance chapter describes is published separately as
[ProjectArchitect](https://github.com/Druthulu/ProjectArchitect); the BFM repository is its largest worked example.
