# decomp-architect — the method for a matching decompilation run with an agent

> **Version:** 0.1 (built in-tree in the source project's Phase 33.5, 2026-09; split into its own repository after that
> project's public flip). **Overlays:** ProjectArchitect 2.0 — this document assumes its governance (a permanent
> constitution, a full-text rules registry recited every session, two human gates per phase with autonomy between them,
> per-task commits after the phase log, a replayable in-phase checkpoint, hard stops at phase ends) and adds the decomp
> content: the order of work, the byte gate, the campaign machinery, the flywheel, the instruments, the models and
> effort, the compiler's source, the conduct, readability at day one, and the shape of the economics.
> **Lineage:** distilled from one finished matching decompilation — every game-code function of every binary on the
> disc byte-identical from C, published with a full history — whose records were written as it happened: a decision
> log of pivots, an accelerator ledger of what was learned late, thirty-three phase syntheses, a cookbook of several
> hundred byte-proven compiler idioms, and a thirteen-chapter how-to. Numbers from that project appear only inside
> ```` ```calibration ```` fences; everything outside them is claimed to transfer to another console and another compiler.
> The kit's installer copies this file to `docs/decomp-architect.md` so it survives the package folder's deletion.

---

## For humans — the one paragraph

Pin the compiler by evidence and make a whole-binary byte gate the only judge. Treat every tool as a suspect before
every function. Build the things that compound — extraction with a manifest, propagation, the twin band, the codegen
map, the reproducer battery, the differential harness — before the things that pay once. Keep the perishable *why* in a
decision log written during the session that learned it. Write hand-offs to be replayed. Keep the game's bytes out of
the repository from the first commit. Then run the campaign in lanes with cards, harvest before every wave, and let a
person decide direction at the two gates of every phase. Everything else follows from those, at a cost that is mostly the
diagnosis of one's own instruments.

## Which harness am I in?

This kit runs **inside** a ProjectArchitect 2.0 project, as its Phase 0.5. The constitution is already generated and
frozen when the kit runs — from the intake this kit ships (`intake.decomp.md`), which carries the phase ladder — so the
kit never writes it; the kit appends marked sections to the entry-point file, the registry (§E), the effort map, the
cookbook and the ops reference, stamps the firewall and the layout READMEs, and seeds the memory. The operative rules
after install are the project's own `RULES_REGISTRY.md` (ProjectArchitect's groups plus the kit's G1–G67); this
document is the reference they point back to, not a second rulebook.

---

## 1. The ladder — why this order

The source project optimised *cracking* — making one function match — while the real bottleneck was, in turn: the
tooling that measured the frontier, the integration of correct bodies into their translation units, and the supply of
work items. The optimal order front-loads what **compounds** and treats raw per-function cracking as the last, scarcest
resource, because everything else multiplies it:

```
extraction + manifest  →  the oracles + the load map (+ segment at the forced boundaries)
  →  the all-assembly byte-identical baseline  →  the compiler pinned by evidence
    →  the honest census + the differential harness at 0%
      →  propagation · families · the twin band · the reconcile ladder · the carve chain · the draw filter
        →  the codegen map + the permuter  →  first cracks, the manual wave, the routing cliff
          →  the campaign, leverage-first, harvest at every close  →  publish  →  readability
```

Three phases in the middle (the census, the multipliers, the map) look like preparation and are the reason the campaign
banks at the rate it does. The intake's Part B gives each phase its machine-checkable milestone, the tools it builds,
the rules in force from it, and the kernel that earned its position (`corpus/decomp-kernels.md`, DK-1 … DK-16).

**Two structural decisions are made at t=0 even though their payoff is unproven** — the opposite of "probe before
investing", and worth stating because the instinct is wrong: (1) the ROM firewall, private or not (DK-1); (2) the
translation-unit boundaries at the build's forced boundaries — jump-table spans in the data island, per-file
optimisation levels, interleaved library objects — read from the raw image before any C exists (DK-12). Both are
evidenced from raw data, cheap now, and strictly more expensive later.

**The honest caveat.** Tooling-first does not remove the hard tail. The novel unique functions and the compiler-internal
residuals need genuine reasoning and always will. Tooling-first makes the cheap half nearly free and stops the waste; it
does not shrink the hard half. Sell it as that and it is true.

```calibration
source project: the whole-binary gate arrived at phase 12 of 33 and took one binary 1.4% → 85.6% in a session;
propagation matured at phase 15 with the overlay structure known since phase 3; the codegen map arrived at phase 23 and
was available from phase 6; at one late census ~5% of the remaining frontier was mechanically free and the rest needed
reasoning.
```

## 2. The byte gate — the only claim

A function is done when the whole binary still hashes with it compiled from source and linked in place. Everything
else — a per-function diff score, a masked standalone compile, a real-translation-unit probe, an agent's "match" — is a
**filter**, useful for triage, never the arbiter (G3, G10). The hash check lives inside every build, so there is no third
state between "identical" and "failed"; the census of open functions reads from the source, and a default build never
links unmatched C (G4).

**The oracle ladder, with what each rung cannot see** — every oracle states its blind spots in its own output:

| Oracle | Proves | Blind to |
|---|---|---|
| standalone compile, relocations masked | the instruction shape | symbol identity, the real unit's declarations, the file's optimisation level |
| the real-unit probe | the body in its declaration context | link-time symbol identity |
| the symbol-identity check | the draft names the symbols the target references | whether the body is right |
| **the whole-binary rebuild + hash** | everything about this binary | coverage of the other binaries; a stale output file; an incremental linker script; a body that is pasted assembly |

Hence the rules that follow from the ladder: decisive verification is a clean rebuild with the exit code read (G9); a
standalone match is not a bank and every claim names the compilation it survived (G10); pasted assembly is a verbatim,
not a bank, and a strict verbatim check runs in the per-bank close (G11); the whole fleet is rebuilt on a schedule
because a gate is silent about every binary it did not build (G42).

## 3. Cards, lanes, waves — the campaign machinery

**The card is fuel, not a ticket** (DK-39). The unit of work handed to a model carries everything the project already
knows that bears on the function, assembled deterministically for zero tokens: the target and its destination file; the
banked twin found over the whole world (ahead of any open sibling); what the destination file already declares; the
project-wide declaration consensus per callee; the function's own past-attempt history from every earlier agent; the
lever the atlas believes applies *and where to read about it* — a name on a card must resolve in the knowledge base by
the words on the card (G44); the same-unit neighbours' declarations of shared globals.

**Lanes have different clocks** (DK-40): drafter (bounded by model capacity and by work items — never stopped to ship a
change), gater (bounded by build time, freely restartable), maintenance (zero-token mechanical work: twins, remaps,
propagation), watchdog, distiller (human-paced), and one lane per excluded population with a cadence matched to its gate
cost (G48). Free work runs before paid work whenever the paid lane is idle; same-skeleton members collapse to one card
and the siblings go to the free remap.

**The wave, as a spine** (the source project's playbook pairs every guard with the measurement that earned it):
preconditions (tree clean, the last clean fleet run green) → draw, refusing what cannot bank and auditing the exclude
list (G38) → cards with the twin on them → packs where the agent is told to read them → validate every target (G49) →
draft, one agent per target, model by measured size, streaming not batched → gate everything in parallel — the
directory, never the verdict list, with coverage asserted (G50) → reconcile before any rebuild → after ANY bank, the twin
rescan and a commit (G37, G46) → **harvest before the next wave, a hard gate** (G45) → verify the fleet, not the binary →
refresh the replayable checkpoint. Then recover before re-drawing: triage the gate's failures into body and plumbing, and
bank the plumbing ones through the reconcile ladder without a redraft — the gate number is not the close rate until
recovery has run.

**Draw by instruction weight, not head count** (DK-42): the metric is pool realisation in instructions; gate-group
concentration (how many whole-binary rebuilds the wave needs) is chosen at draw time and is the wall-clock lever; card
supply, not model capacity, is the binding constraint for most of a campaign.

**The one-agent-per-function shape.** When the open census fits on one page, the wave machinery is the wrong shape:
build packs, launch one agent per function in its own work directory (G41), and process results one at a time through
the per-unit bank chain — verbatim grep → the real-unit probe for every draft in the CURRENT unit → splice → one build →
hash → commit only on green (DK-36). Agents write their deliverables early and end with one JSON line (G47); a dead
session's verdicts are harvested by tool from the transcripts.

```calibration
source project: the twin field alone moved a wave from 0 banked to 51; a barrier-free pipeline ran 16 targets in 82 min
at 3.8× against two batched halves at 136 min and 2.5×; mature waves drew 6,500+ instructions on 65–73 cards; the mature
harvest found ~85% of agents' gap reports already covered by the base; 139 of 162 idle minutes in one session came from
stopping the drafter to ship a change.
```

## 4. The flywheel and its laws

The knowledge base is the project's compounding asset and it is **per-compiler**: the machine that builds it is what
transfers. Its layers: the cookbook (one section per idiom, each byte-proven on a named function with the diff before and
after), the symptom index (derived by a tool that asserts every section is indexed and every entry resolves), the codegen
map (pass → residual pattern → lever), the pinned triple and the permuter recipes (the executable form of the same
knowledge), the per-function journal (what every earlier agent tried on *this* function), and the meta layer (the
decision log, the accelerator ledger, the rules).

The loop: the gate accepts a function → harvest the worker's note, only for byte-proven results → distil into the base
(a person plus a mid-tier reviewer) → the next workers grep it from their next card. Its laws, each bought with tokens:

1. **Harvest only from proven results.** A note on an unverified draft is a lesson about a function you did not reproduce.
2. **Extraction is not distillation.** Only what reaches the base changes behaviour; an archive of unread notes is ore.
3. **Expect most harvested claims to be already covered** — a fast, correct "already known" is most of the value.
4. **The inert-rider law.** Workers stack edits; when the match closes the last edit gets the credit, and byte-inert riders
   survive into the accepted result *precisely because they are inert*, which then reads as proof. Strip a credited lever
   from the accepted body and recompile before it enters the base (G45).
5. **Vocabulary decides findability.** The first distillation is done by hand; the index is keyed by symptom — what the
   diff looks like — because that is what the worker has in front of it.
6. **Accept the one-wave lag.** Wave N's lessons land while N+1 is in flight; N+2 is the first that can use them. Pausing
   production to think costs more than the lag.
7. **Harvest is a pipeline step, not hygiene** — and periodic, not per bank: the highest-value entry of one session was
   visible only because four independent instances appeared in one wave.
8. **Seed it before the first match** — from the compiler's own source and from sibling projects on the same compiler
   family; carry a cookbook across and adapt it rather than rebuild it (DK-14). The kit ships three dictionaries for exactly
   this: the source project's tools verbatim, keyed by the need each answers (consult it before designing or debugging a tool —
   G66), its cookbook, symptom index and codegen map behind a front page that says what transfers (translate an inherited
   idiom through its named pass, never copy the lever — G67), and its record — the how-to, the decision log, the accelerators,
   the retrospective, the playbook and every phase-end, verbatim — so that a rule's or kernel's provenance line leads to its evidence.
9. **Capture while it is fresh** (ProjectArchitect X5): the *why* evaporates at a context boundary.

```calibration
source project: one in three credited levers was inert — 4 of 8, then 6 of 19; the journals were a labelled corpus
written for thirty phases and read in the thirty-first, and with the notes on the card 38 of 39 matched on the hardest
frontier.
```

## 5. Instruments — a true number about a narrower world

The most damaging defect class is not a crash. It is **a tool that exits zero reporting a true number about a scope
narrower than the reader believes**, so the failure looks ordinary and gets attributed to the worker or the compiler.
Almost every wall the source project recorded was one of its own instruments (the corpus's failure museum). The
discipline (G19–G36): assert coverage against an over-approximating set; derive from invariants instead of re-parsing; a
second, disagreeing oracle on a schedule; fix the instrument before believing its number; probe one instance before
costing; read the recorded verdicts first; negative-control every refusal against the population that already
succeeded; exonerate the instrument before blaming the subject; every number with its denominator; refuse unsupported
input; a soft error is an error; a known-true case before any reading; a verdict names its instrument; measure the
steady state and report every lane; distinguish judged from not-judged; a score is not a closeness until its diff is read.

**The differential-oracle harness is built at 0%** (DK-9): the same question down two independent paths on a schedule,
failing loudly on disagreement — matched? compiles? fleet green? scanner coverage? agent produced work? bankable? It is
the one accelerator that works before a single function is matched, and every new tool is a fresh chance to be
confidently wrong about scope. Rules are applied by whoever writes the tool; a harness is not — the author of one of the
rules above rebuilt the exact defect it warns about an hour later in a different file.

**The widening review at every close** (DK-16): tooling is correct when written and goes stale as new idioms reveal
populations it cannot see; at every session and phase close, ask *which scanner's denominator just got wider?* — that
is what converts new knowledge into free banks.

## 6. Integration is the bottleneck

Once cracking is systematic, a byte-correct body fails to bank because of the *file* it must live in, never because of
its own bytes: declaration conflicts (arity, widths, `void` vs pointer; two drafts in one file disagreeing with each
other), def-side loose typing, symbol spellings, file placement (the wrong optimisation level, a boundary the split drew
wrongly), jump-table carves, vendor objects, missing data carves. The reconcile ladder — declaration sync to the file's
consensus, callee casts at the use site, a canonical-signature layer, self-declaration normalisation, the carve chain,
the real-unit probe — is built before the waves (DK-7) and every bank failure is triaged into body vs plumbing before a
redraft is paid for. **Budget for banking, not cracking.**

**Propagation turns the ladder into leverage** (DK-5, DK-10, DK-11): dedup (a body authored once, instantiated at every
member, byte-gated per member, registered fail-closed — and, per the readability inversions, living in a C file a reader
would open); structural families (crack one exemplar, remap the siblings mechanically, gate each; templates, not free
dedup); twins as a band (rank by work, filter lookalikes, rescan after every bank — G46); constant flips and
pass-throughs as remaps with an edit. A gate verifies one binary and propagation writes N others, so the clean fleet run
follows every propagating gate; carve state belongs to its binary (G43); a newly discovered binary is not real until every
consumer knows it (G7).

**Types — the two-sided verdict.** As a codegen lever, types are inert: the source project measured rich structure context
against a structural-miss sample early and got identical bytes, and every wall after that was a compiler pass — so a type is
never the reason a body will not match. As a banking lever they are the largest one it underweighted: agents drafting in
isolation invent their types, so gate failures arrive as declaration conflicts and the tree fills with variants of one shape;
and width and signedness are the one place a type *does* move bytes, which the permuter cannot reach. Hence the canonical type
file from the first bank, growing one proven field at a time — one definition per shape, widths fixed by the bytes at bank
time, a draft refused for a duplicate definition or a raw address cast (DK-65, G62). It removes most of the declaration-conflict
class before the ladder is needed and leaves nothing to unify after 100%; it shortens no crack.

```calibration
source project: ≈92% of drafts byte-correct and ≈27% banked at one measurement; with the map, 11 of 12 first-pass
drafts matched and every failure was plumbing; one 299-instruction head became 4,485 instructions across 15 siblings
for ≈0 tokens; the exact-hash twin join found 22 of 352 reachable stubs, the band 75. Types: rich decompiler context
scored 0 better / 10 same / 2 worse on a 12-function structural-miss sample, identical bytes (phase 17); 1,232 struct
definitions and 143 raw address casts in the tree at 100%.
```

## 7. The compiler's source — "unsteerable" means "not yet read"

Residuals that resist every source rewrite — a phantom callee-saved register, a load stuck below a store, a spill slot
in the wrong place — are explained pass by pass by the compiler's own source: which pass emits the odd instruction, why,
and what C-level change moves it. Build the **codegen map** right after the pin (DK-6): a catalogue of *pass → residual
pattern → byte-proven lever* with a triage table keyed by the *tell* in the diff, so a mid-tier agent applies
compiler-internal levers without reading the source. If the source does not exist, build the same catalogue from
systematic probes; the reproducer battery is the same instrument either way. Know which source you are reading — the
tree in community circulation may be a later version (DK-52).

**Dumps, not guesses** (DK-44, DK-47): the compiler's per-pass dumps from the REAL translation unit; the allocation table
(the global allocator's order — the callee-saved bank *is* its priority order); a ghost census of stack slots. Read the
allocation order before any register lever; a pin is a symptom, and every pin comes off once the source shape is right.

**Reproducers before probes; a census before a sweep** (DK-45, G53, G55): a one-second battery of five-line functions per
mechanism before the real function; a producer census from the source before any spelling sweep; "PROVED" names its list.
A wall verdict names the pass and quotes the dump line (G52). And before any of it, the cheaper question — **whose object
is this?** — provenance → archive → link → compiler (G56).

```calibration
source project: a frontier agent reading four files of the compiler's source produced the map for what one hand-cracked
giant used to cost (375–475k tokens); two formal proofs of unmatchability were each one producer short and fell to 18
and 8 five-line reproducers; every pin on the last four functions came off; twelve "walls" were the vendor's controller
library, a 383 KB archive away.
```

## 8. Models and effort — as method, not as a price list

Two different agents run the project: the **drafters** (many, disposable, one function each) and the **orchestrator**
(one, long-lived, under the governance). They are budgeted differently.

**Drafters: route by a difficulty cliff you measured on your own corpus** (DK-43, G39). Run a small manual wave first and
measure bank rate by instruction count; the first hand-waved boundary will be wrong. Cheap tiers are honest filters
(every claimed match was real) and never the gate. Escalate sooner: a cheaper tier run into a wall costs the failures and
then the escalation. The strongest model is for genuinely new wall classes — an unsolved tooling problem, an adversarial
review of a design, a residual no documented lever reaches — briefed with every number already measured, the files to
read first, the house rules as hard constraints and an explicit deliverable path; its claims are verified against the
bytes by the orchestrator. It is not for reviewing a corpus against an existing knowledge base. Budgets are part of the
harness: caps sized to the card; the workflow cap is a budget; usage limits are a wall class; a truncated transcript is
an instrument failure, not a verdict.

**The orchestrator: depth vs breadth** (ProjectArchitect's effort doctrine). Depth is how hard one agent thinks; breadth
is how many angles at once. Maximum depth for the compiler fingerprint, an address derivation, the segmentation decision,
a wall verdict, a phase plan, a PhaseEnd, non-obvious debugging; breadth (isolated parallel agents) for a fleet-wide
audit, a duplicate report, bulk drafting — never global breadth mode for the crown-jewel decisions, and every transition
prompted and waited for. Isolated agents beat the serial main loop on breadth because the main loop's context accumulates
roughly quadratically; hand-by-main-loop wins only for a handful. Writing a document from the session's own context is
not breadth.

```calibration
source project: the cheap tier's success fell from 86% to 20% across ~50–120 instructions; a 100-worker A/B put cheap
drafters at the strong tier's match rate under ~50 instructions at ≈4.8× lower cost per match, 63 claimed = 63 real; a
local 7B model saturated the ≤15-instruction population for $0; 80 functions drafted under breadth mode vs maximum depth
banked 13 and 14 — noise; the most expensive row was a 655k-token frontier agent on a function whose answer was a grep.
```

## 9. The use of AI — conduct

The project is openly machine-carried and says so once, at the project level. The conduct rules (G61–G65) are what keep
that from being a liability: **the byte gate is the only claim of success**; **names and types are evidence-based, never
guessed** — hallucinated meaning is the specific way a model damages a decompilation without any test catching it, and
unnamed beats wrong; **outward text is written by a person** the way a developer writes, from the facts, never a model
draft with the tells removed, after reading the target project's AI policy; **no automated traffic against community
infrastructure**; **agents assist, a person owns** — every change justifiable from the record.

```calibration
source project: an upstream pull request drafted by the model and given a "plain contributor-style" pass was closed the
same day by a maintainer who read it as machine-written and said why it cost him; a sibling project forbids
autonomous-tool pull requests outright.
```

## 10. Readability at day one — the six inversions

The source project reached 100% and then chartered a generation to make the code legible; the community's bar
(a full naming scheme, typedefs, a formatter, decimal for counts and hex for masks, a marker on every match-forcing
trick, "better unnamed than named wrongly") was read afterwards. A new project inverts six things at draft or bank time,
gated the same way a match is (`intake.decomp.md` Part C): pins recorded at draft time and marked if kept; shared bodies
as C files per system from the first propagation; types canonical at bank time; names with recorded evidence; formatting
installed with the first C file; file layout by system with unit boundaries decided at segmentation time. Every step is
checked the only way the project checks anything: N of N binaries rebuild identical.

## 11. What stays hard

Not everything is tooling. The novel unique tail (no duplicate, no structural sibling, a scaffold too far for the
permuter); compiler-internal residuals (steerable in the end, but only by understanding the pass — knowledge won from
the source once and written down); build-integration walls that masquerade as compiler walls (table carves, mixed
optimisation levels, scattered common data in vendor objects) — ours to fix, and they never announce themselves; and
the human gate: nearly all of the work is the agent's, and every wrong *direction* is caught by a person at a plan or
milestone gate (DK-62).

## 12. Publishing

The firewall was day one (G12–G18), so publishing is a contract run, not a rewrite: a recorded clean rebuild of the whole
fleet with and without the vendor SDK, every oracle green, the disc residue zero; a fresh-clone proof from the
developer's own dump; every published number generated with a freshness check (G58); a no-ROM CI that proves everything
that does not need the game; releases and outreach written by a person (G63); and, if the repository was ever private,
the visibility flip gated on the host's object store, never on a clean tree (G17).

## 13. The economics' shape

The shape transfers; the constants do not. **Two rows, and the project is the ratio between them:** the paid row — drafts
that are re-drafted because they failed on plumbing, functions re-drafted whose banked twin sat two words away, frontier
agents on rows whose answer was a grep, sessions lost to instrument diagnosis, the private-era convenience of committing
game-derived files; and the free row — the mechanical banks that cost ≈0 tokens each once a tool existed for their class
(twins, families, siblings, carves, propagation, stranded boundaries). The bootstrap order is about moving work from the
first row to the second. Card supply, not model capacity, binds; head count flatters small-target waves and instruction
weight moves the fleet; the gate's cost is paid in wall-clock and gate-group concentration is a draw-time choice; budget
recovery against gate drops and treat near-misses as permuter fuel; and a one-off diagnosis of a harness defect costs
orders of magnitude more than a nightly disagreement report.

```calibration
source project: 12 weeks, 33 phases, ≈87 sessions, ≈4,040 commits, one human and one agent; 218 binaries, 363,214
functions (255,632 shared bodies via 2,220 dedup groups; 1,256 vendor functions linked; 5 hand-written bodies kept
verbatim); drafts → banked fleet-wide 34% (8,885 → 3,027 over 37 waves, most before the integration tooling); bank
rate by size ~57% under 50 instructions falling to ~3% at 120–200 on that fleet-wide curve, while one late wave banked
16 of 16 up to 397 instructions; 170k–300k tokens per banked head early, ~124k mature; the zero-token pipeline of one
phase banked ~256 members against an estimated ≈20M tokens as waves; about half of a typical late session went to
harness defects wearing model-failure costumes.
```

---

## Coverage
Thirteen sections; every claim outside a calibration fence is stated to transfer. The rules are the registry seed
(`templates/registry-E.decomp.md`, G1–G67); the kernels with their costs are `corpus/decomp-kernels.md` (DK-1 … DK-68 and
the failure museum); the ladder with its milestones is `intake.decomp.md` Part B; the day-one inversions are its Part C.
