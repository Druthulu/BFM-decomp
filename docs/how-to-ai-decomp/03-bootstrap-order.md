# 03 — Bootstrap order: front-load what compounds

**The bottleneck is never where you think it is.** BFM optimized *cracking* — making one function match — while the
real bottleneck was, in turn: the tooling that measured the frontier, the integration of correct bodies into their
translation units, and the supply of work items. So the optimal order front-loads the things that *compound*
(structure-mapping and propagation tooling; measurement integrity), builds the integration layer before it is needed,
and treats raw per-function cracking as the last, scarcest resource — because everything else multiplies it.

## The order, in one breath

```
byte-match baseline  →  pin the compiler by evidence  →  honest corpus census (with self-asserting tools)
   →  propagation + reconcile tooling  →  the codegen map + the permuter  →  then crack, leverage-first,
      letting each crack fan out across all its duplicates  →  at every phase close: idioms → tooling widening → free banks
```

## Phase 0 — the two things BFM got right, in this order

1. **Deterministic extraction and a 100%-assembly byte-identical baseline before any C.** A committed sha1 manifest of
   every extracted artifact; a build that reassembles the disassembly to the original hash, with the check in the build.
   ([chapter 02](02-byte-gate.md).) BFM: day 5.
2. **Pin the compiler/assembler/flags by evidence from the binary.** Library version stamps, then idiom-revealing probe
   functions run down a candidate ladder (compiler builds × assembler versions × flags) until one reproduces the
   bytes. Never inherit a sibling project's triple; expect per-module variation (mixed optimization levels, mixed
   compilers within one image). Always pass the assembler version explicitly — the default is not "latest" (G8).
   BFM: day 5, with one flag (`--expand-div`) that turned out to be mandatory.

## Phase 1 — the honest census, with tools that assert their coverage

Before choosing a strategy, measure the *shape* of the corpus with instruments you have verified against a disagreeing
oracle:

- how much is **byte-identical duplication** (the free tier);
- how many **structural families** (the same function recurring, differing only in per-location symbols/immediates);
- the **reach × size** distribution (how many copies each function has, how big each is);
- how large the genuinely **unique tail** is.

And the discipline that must come with it: every scanner compares what it found against an over-approximating candidate
set and fails on the gap (R32); every measurement that is about to steer strategy is checked against a second instrument
(R34); the instrument is fixed before the number is believed (R35). BFM adopted this at Phase 26 — and immediately found
seven silent-skip defects and the collapse of a "families cannot be automated (≈0%)" doctrine that had steered two
phases: the 0% and the real 89% were the same measurement from a broken and a fixed tool. **A wrong shape-measurement
costs phases, not hours.** ([chapter 04](04-oracles-and-instruments.md).)

**Build the differential-oracle harness now, at 0%.** It is the only accelerator that works before a single function is
matched and compounds with every tool added: run the same question down two independent paths on a schedule and fail
loudly on divergence — "is it matched?" (the source scanner vs. the built binary), "does it compile?" (the standalone probe
vs. the real translation unit), "is the fleet green?" (incremental vs. clean), "what does this scanner cover?" (its own
count vs. a candidate set), "did the agent produce work?" (its verdict vs. its scratch directory)
([`docs/accelerators.md`](../accelerators.md) #15).

## Phase 2 — propagation, families, integration: the multipliers

BFM's dominant economic fact: ~138 position-locked copies of one shared engine, so one crack banks up to 138 members.
The overlay structure was known in Phase 3; the propagation tooling matured many phases later, reactively. **Front-load
it, so every crack compounds from match #1** — probably the largest leverage the project left on the table through
ordering alone. What to build the moment you have two binaries ([chapter 10](10-integration-and-propagation.md)):

- the corpus/coverage oracle; the signature layer (exact, relocation-normalized, mnemonic-sequence);
- the twin join — **as a band, not a point**: an edit-distance band found 3.4× more reachable twins than the exact hash
  on a corpus believed fully mined (22 of 352 by exact hash, 75 of 352 by the band — [`docs/generic-decomp-package.md`](../generic-decomp-package.md)
  §2b, which also says to rank the candidates by the *work* each needs, not by distance), and pays from the very first banks;
- propagation (author once, instantiate at each member, byte-gate each, register fail-closed) and the family remap;
- the **reconcile ladder** — declaration sync, callee casts, canonical-signature reconciliation, carve tools — because
  once cracking is systematic, banking a correct body past its translation unit is the bottleneck. This is the part
  everyone under-budgets;
- the opt-level and jump-table carve chain, and the draw filter that refuses work the pipeline cannot bank (R45).

## Phase 2b — read the compiler's source; start the permuter

Two compounding assets BFM built late ([chapter 07](07-compiler-source.md)):

- **The codegen map** — a catalogue of *compiler pass → residual diff pattern → C-level lever*, built by reading the
  actual compiler source (if it exists) or by systematic probes (if not). Before it, cracking was per-function
  guesswork; after it, systematic pattern application. Its highest-value entries required no matched function at all —
  they could have been mined in week 1. BFM: Phase 23 of 33; available from Phase 6.
- **The permuter track** — an LLM-free, CPU-bound search that takes a close draft and randomizes the C to close
  register-allocation and scheduling residuals. It runs on a different budget from everything else and should be
  grinding the near-miss backlog from the first close draft. (And verify that it actually runs on your drafts: BFM's had
  silently never run on a whole class — [chapter 12](12-failure-museum.md).)
- **Mine the permuter's failures, not just its wins.** A flywheel that only distils *successes* into the cookbook and the
  permuter's weights leaves its largest signal unread: every near-miss the search plateaued on. BFM turned that log into
  a corpus (`tools/autopsy.py`) and classified each plateau deterministically from the bytes (`tools/residual_class.py`)
  into *missing transform* (the byte-match is reachable by a local mutation the search never tries — extend the
  mutation set, a permanent offline win), *mis-classified* (fix the routing), *seed-structural* (redraft) or *genuine
  wall*. The first bucket is the one that closes a whole class with no model at all. Build the classifier before the
  backlog is large; 91% of BFM's open backlog carried no class label when the tool was written.

Also seed the knowledge base from **sibling projects on the same compiler** — same-generation idioms transfer.

## Phase 3 onward — crack, leverage-first, and widen at every close

- **Order by leverage, not difficulty.** "Smallest, simplest leaf first" is the lowest-leverage order; fleet progress is
  reach-multiplied, so the schedule is highest (reach × size) first, re-sorted as the frontier shrinks. The right unit
  of work is the family, not the function.
- **Run the small manual wave first, measure bank rate by size** — that is your routing cliff ([chapter 08](08-models-and-budgets.md)).
- **Free work before paid work**, in its own lane, whenever the paid lane is idle ([chapter 05](05-cards-lanes-waves.md)).
- **At every session and phase close, the widening review:** *which scanner's denominator just got wider?* New idioms do
  not only make the next crack easier — they retroactively convert already-open functions into free banks, but only if
  a tool is widened to see them. One idiom review reclassified ten functions and 1,027 instructions in an afternoon.

## The honest caveat

Tooling-first does not remove the hard tail. At one late census BFM's remaining frontier was 418 functions, of which
about 5% was mechanically free; the rest — case-label unstacking, an uncolorable local, an unreferenced aggregate, a
combine-pass bookkeeping gap — needed genuine reasoning and always will. **Tooling-first makes the cheap half nearly free
and stops the waste; it does not shrink the hard half.** Sell it as that and it is true.

## A checklist for a new project

1. Byte-exact build triple by evidence; whole-binary hash check in the build; an all-assembly green baseline.
2. The local per-function oracle, **stating its blind spots in its own output**.
3. The differential-oracle harness (two paths per question, on a schedule) and coverage assertions in every scanner.
4. The census: duplication, families, reach × size, the unique tail — with a known-true case checked first.
5. Propagation, the twin band, families, the reconcile ladder, the carve chain, the draw filter — before the waves.
6. The codegen map (from the compiler's source or from probes) and the permuter — before the first "unsteerable" verdict.
7. The card (destination file, existing declarations, project-wide consensus, any sibling, the lever with where to read it).
8. A small manual wave; bank rate by size; the routing cliff.
9. Harvesting from proven results only; the first distillation by hand — its *vocabulary* decides whether anyone finds it later.
10. Only now scale the worker count; watch rejection rates bucketed over time, not at launch.
11. Every excluded population gets a lane before the main loop gets more workers.
12. At every close: harvest → widen the tooling → bank the free functions → refresh the checkpoint.
