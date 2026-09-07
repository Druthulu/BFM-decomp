# 08 — Models and budgets

Two different agents run a decomp like this: the **drafters** (many, disposable, one function each) and the
**orchestrator** (one, long-lived, the one under the governance of [chapter 01](01-governance.md)). They are budgeted
differently.

## Routing drafters by measured difficulty

- **Route by difficulty, and measure the cliff.** BFM's ladder, as measured: the cheapest tier up to ~50 instructions,
  a mid tier to ~120, the strongest above, and the frontier class only for a *new* wall class. The cheap tier's success
  drops from 86% to 20% across that range, and the first hand-waved boundary was wrong by a factor of two. Never route
  cheap→strongest directly; the mid tier exists for a reason.
- **A controlled A/B (100 workers):** cheap drafters under a strong orchestrator matched the strong tier on functions
  ≤ ~50 instructions at about 4.8× lower cost per match. Reserve the strong tier for the 90+-instruction
  register-allocation and scheduling tail.
- **A local 7B model saturated the ≤ 15-instruction population for $0.** The bottom of the ladder can be free.
- **Cheap tiers are honest.** Across 100 workers, 63 claimed matches were 63 real matches. Treat their verdicts as a
  reliable *filter* and never as the gate ([chapter 02](02-byte-gate.md)).
- **Reserve the strongest model for genuinely new walls** — an unsolved tooling problem, an adversarial review of a
  design, a residual no documented lever reaches. Reviewing a pile of artifacts against an existing knowledge base is
  mid-tier work. BFM's most expensive single row: a 655k-token frontier agent on a function whose answer was a grep
  and a sibling's spelling ([chapter 06](06-knowledge-base.md), R71/R72).
- **Frontier reading beats frontier cracking.** The one place the frontier class paid outright was reading the
  compiler's source into the codegen map ([chapter 07](07-compiler-source.md)) — knowledge every later, cheaper agent
  applied.

## Budgets

- **Budget per lane, not per project.** A turn/cost cap that fits a small function starves a large one: 98 of 270
  attempts on the hardest population ended *at the cap* rather than at a wall. Size the cap to the card (R46).
- **Concurrency is a budget.** The provider's rejection rate stays ~0–3.5% up to ~95 requests/min and reaches
  6.6–12.7% at 195–227; retries absorb it. Each worker makes 0.3–0.8 req/min, so ~350–400 concurrent workers sat at
  the knee. Streaming (refill each slot on completion) burns a rate window faster than batching, so slots are the dial.
- **Measure the steady state, not the launch.** Bucket rejections over time before calling a number a ceiling; launch
  bursts and startup memory both faked hard limits in one session.
- **Card supply, not model capacity, was the binding constraint** for most of the campaign. The project repeatedly
  reached for more workers when the answer was more work items — and once a second population got its own lane,
  capacity stopped being the question ([chapter 09](09-economics.md)).
- **The harness has limits of its own.** A hard cap on concurrent subagents (20 in BFM's harness); a coordinator whose
  context fills ("prompt too long") with completions landing in a dead session — recoverable only because agents wrote
  their drafts first and their verdicts are in the transcripts (R67, [chapter 05](05-cards-lanes-waves.md)).
- **Usage limits are a wall class.** Three frontier agents died ten minutes in on an account-wide limit; check the
  quota before routing to that tier, and treat a truncated transcript as an instrument failure, not a model verdict
  (R40).

## The orchestrator's effort — depth vs. breadth

The orchestrating agent's reasoning depth is a human-controlled setting, and it maps onto two axes
([`docs/effort-map.md`](../effort-map.md)):

| | Depth — how hard one agent thinks | Breadth — how many angles at once |
|---|---|---|
| Control | the effort level (… xHigh < Max) | multi-agent fan-out (Ultracode / a workflow of subagents) |
| Best for | one hard, irreversible reasoning problem: the compiler fingerprint, an address derivation, a phase plan, a PhaseEnd, non-obvious debugging | the same analysis across many independent items: a fleet-wide audit, a duplicate report, bulk drafting |

They are not combinable in one setting, and global breadth mode caps every task at the shallower depth — exactly wrong
for the crown-jewel decisions. So breadth is applied surgically: the agent *prompts* for the toggle when a
breadth-shaped stretch appears ("would ten agents each doing one item beat me doing them in sequence?") and prompts
again to switch back when the deep single-thread work resumes. The controlled experiment that settled the doctrine:
80 fixed functions drafted by the identical workflow under the shallower-per-agent breadth mode and under maximum
depth banked 13 and 14 — noise. Per-agent depth does not change blind-draft yield; breadth changes throughput.

**The doctrine as run:** xHigh (the highest *persistent* level) for execution whose design is already settled; Max for
phase plans, PhaseEnds, architectural forks and non-obvious debugging; breadth mode for surveys, audits and bulk
matching; plan mode always at Max; **every transition prompted and waited for** (R27). Writing a document from the
session's own context is *not* breadth — subagents would have less context than the author.

## Delegation shapes that worked

- **Isolated agents for breadth, never serial in the main loop**: the main loop's context accumulates and its cost is
  quadratic; compile-and-gate is free and local; a local-only drafting tier without agents sat at ~3% of the work.
- **One frontier agent per stuck lane**, briefed with measured facts, the house rules and a document path; its claims
  verified against the bytes by the orchestrator.
- **Read-only exploration agents** for surveys during planning; design agents for tool designs; never an agent that
  reports a number the orchestrator does not check against a known-true case.
- **"Resume" means resume:** replay a failed run from its run id so it finishes itself; never rebuild targets or re-route
  models on the orchestrator's own inference.
