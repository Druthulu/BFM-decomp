# How to AI-decomp

The transferable part of this project: thirteen chapters on running a byte-exact decompilation with AI agents, written
at the close of BFM-decomp for whoever runs the next one — any console, any compiler, any game. They are distilled from
records kept *as it happened* (the decision log, the PhaseEnds, the accelerators ledger, the wave playbook, the
retrospective), and every number is a BFM measurement given with its denominator, so you can calibrate rather than copy.
Start with [chapter 00](../how-to-ai-decomp/00-README.md).

| | Chapter | One line |
|---|---|---|
| 00 | [Read me first](../how-to-ai-decomp/00-README.md) | Who this is for, the four prerequisites, the thesis in a paragraph, what transfers and what does not |
| 01 | [Governance](../how-to-ai-decomp/01-governance.md) | A static constitution, two human gates per phase, autonomy between them, rules that accumulate, a digest, and a checkpoint written to be replayed |
| 02 | [The byte gate](../how-to-ai-decomp/02-byte-gate.md) | A function is done when the whole binary still hashes with it compiled from source; everything else is a filter, and each filter's blind spot has a rule |
| 03 | [Bootstrap order](../how-to-ai-decomp/03-bootstrap-order.md) | Baseline → pin by evidence → honest census → propagation and integration tooling → the codegen map and the permuter → then crack, leverage-first; a 12-point checklist |
| 04 | [Oracles and instruments](../how-to-ai-decomp/04-oracles-and-instruments.md) | A true number about a narrower world; the rules R32–R63 as a working set; the differential-oracle harness to build at 0% |
| 05 | [Cards, lanes, waves](../how-to-ai-decomp/05-cards-lanes-waves.md) | The card as fuel, lanes with different clocks, free work before paid, the wave step by step with each guard's measurement |
| 06 | [The knowledge base](../how-to-ai-decomp/06-knowledge-base.md) | The cookbook, the symptom index, the harvest→distil→next-card flywheel and its four laws, siblings' spellings before dials |
| 07 | [The compiler's source](../how-to-ai-decomp/07-compiler-source.md) | "Unsteerable" means "not yet read": the codegen map, dumps not guesses, reproducers before probes, a wall verdict names the pass |
| 08 | [Models and budgets](../how-to-ai-decomp/08-models-and-budgets.md) | Routing drafters by measured difficulty, budgets per lane, the orchestrator's depth-vs-breadth doctrine, delegation shapes that worked |
| 09 | [Economics](../how-to-ai-decomp/09-economics.md) | Yield by size and population, throughput and capacity, where the tokens went, what did not cost much |
| 10 | [Integration and propagation](../how-to-ai-decomp/10-integration-and-propagation.md) | The integration classes and the reconcile ladder; dedup, families and twins; the honesty rules |
| 11 | [Publishing](../how-to-ai-decomp/11-publishing.md) | Keep the bytes out from day one — or the rewrite, done safely; the recorded contract; generated numbers; no-ROM CI; licenses |
| 12 | [The failure museum](../how-to-ai-decomp/12-failure-museum.md) | Thirty-six failures that looked right at the time, each with why, and the rule it produced |

**What transfers:** the gate discipline, the oracle ladder, lanes and cards, draw-time refusal, free-before-paid,
per-population clocks, model routing, the flywheel and its inert-lever law, the governance cadence, the publishing
discipline, and the *shape* of the economics. **What does not:** the compiler idioms — the knowledge base is
per-compiler; the machine that builds it is universal.

The framework the governance chapter describes is published separately as
[ProjectArchitect](https://github.com/Druthulu/ProjectArchitect); this repository is its largest worked example. The
project-side pages of this wiki — [the matching workflow](The-matching-workflow.md), [the dedup engine](The-dedup-engine.md),
[verification and progress](Verification-and-progress.md) — are the same machinery seen from inside one project.
