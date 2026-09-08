# Decomp kernels — what a matching decompilation learns late, distilled for day one

> **Growing it (ProjectArchitect's corpus rule, restated):** when a decompilation run under this kit matures, fold its
> genuinely transferable, project-agnostic lessons back into this file — never a project-specific body — and keep the
> id scheme and the coverage line at the bottom current. A kernel that recurs across more projects is stronger evidence
> that it is general. Entries carry no game name, no address, no rule number of the source project outside the
> `provenance:` line; the source project's measurements live only inside ```` ```calibration ```` fences, so a reader
> calibrates rather than copies.
>
> **How to read a kernel.** *Kernel* is the takeaway; *when it applies* names the moment on the phase ladder; *cost* is
> what the source project paid for learning it late, or saved once it existed. The intake document's phase ladder cites
> kernels by id (DK-n) as the reason each phase sits where it does; the registry seed's rules (G-n) are the conduct these
> kernels produced. The test for a kernel, from the source project's own how-to: *if it would still be true for another
> console and another compiler, it belongs here; if it is a fact about one compiler or one game, it does not.*

---

## 1. Order — what to build before the first crack

### DK-1 — Keep the game's bytes out of git from the first commit, private or not
- **Kernel:** decide the public/private boundary on day one and enforce the ROM firewall from commit one. A private
  repository is not an exemption: the bytes end up in every clone, every worktree, every host-side cache, and the only
  way out is a full-history rewrite.
- **When it applies:** Phase 0, before the first extraction.
- **Cost:** a few weeks of convenience against a rewrite of the whole history, two rehearsals, an archive repository, a
  force-push, a host-support ticket and a daily probe of the host's object store.
```calibration
source project: relaxation lasted 2026-06-10 → 2026-09-06; 4,031 commits rewritten, verified pair by pair; the host
still served the old tips after the force-push (157 activity rows).
```
provenance: BFM retrospective §4 item 1; R74; P33 blocks C1–C9

### DK-2 — A committed extraction manifest and an all-assembly byte-identical baseline before any C
- **Kernel:** extract deterministically with a committed manifest of hashes (the manifest is also the audit's source of
  forbidden hashes), then reassemble the disassembly to the original hash with the check inside the build. Only then
  write C. The baseline proves the split, the linker script and the toolchain end to end while there is nothing to
  reconcile.
- **When it applies:** Phases 1 and 3.
- **Cost:** near zero when done first; every later structural change is priced by what has been matched since.
```calibration
source project: baseline on day 5; the link was clean and the assembler was byte-clean at the first try.
```
provenance: BFM PhaseEnd 2 / PhaseEnd 5; how-to chapter 03 Phase 0

### DK-3 — Pin the compiler by evidence from the binary, down a candidate ladder
- **Kernel:** read the library version stamps in the image, pick idiom-revealing probe functions, and run the candidate
  ladder (compiler builds × assembler versions × flags) until one reproduces the bytes. Never inherit a sibling
  project's triple; pass the assembler's compatibility version explicitly; expect per-module variation.
- **When it applies:** Phase 4, the day after the baseline.
- **Cost:** a wrong era produces systematic near-miss diffs on every function; one silent flag default can do the same.
```calibration
source project: the sibling project's compiler was one generation older; one division-expansion flag was mandatory
and found only by the ladder; the assembler's default emulated the wrong version.
```
provenance: BFM G8; PhaseEnd 6; the constitution's "wrong compiler era" risk

### DK-4 — Build the whole-binary byte gate before the drafting harness
- **Kernel:** the pattern that scales is many cheap drafters plus an incorruptible whole-binary gate that accepts only
  byte-identical output. The gate is what makes model quality a throughput question instead of a correctness risk, and
  it is what makes cheap models usable at all. Build it the day the baseline is green.
- **When it applies:** Phase 5 (before any wave).
- **Cost:** every function matched before the gate existed was matched by hand.
```calibration
source project: gate built at phase 12 of 33; the first harness run took one binary 1.4% → 85.6% in a session.
```
provenance: BFM accelerators A2

### DK-5 — Build propagation the moment a second binary exists
- **Kernel:** the moment two binaries are onboarded, ask how much identical code they share and build the
  match-once-stamp-everywhere path (a shared header instantiated at every member site, byte-gated per member, a
  fail-closed registry). Every crack compounds from match #1 with it; without it every match is worth ×1.
- **When it applies:** Phase 6, before harvesting.
- **Cost:** the largest leverage the source project left on the table through ordering alone.
```calibration
source project: ~138 position-locked copies of one shared engine; one match banks up to 138 members; 2,220 dedup
groups / 255,708 instances at the end; the overlay structure was known at phase 3, propagation matured at phase 15.
```
provenance: BFM accelerators A3; how-to chapter 03 Phase 2

### DK-6 — Read the compiler's source once, into a codegen map, right after the pin
- **Kernel:** spend one deliberate session reading the compiler's allocator, scheduler, loop and CSE passes into a
  catalogue of *pass → residual pattern → C-level lever*, with a triage table keyed by the tell in the diff. It converts
  per-function reverse-engineering into cheap lookup usable by mid-tier models. Its highest-value entries need no
  matched function; they can be mined in week one. If the source does not exist, build the same catalogue from
  systematic probes.
- **When it applies:** Phase 7, before the first "unsteerable" verdict.
- **Cost:** phases of re-deriving the same allocator behaviour per function and calling classes unsteerable that the
  map later dissolved.
```calibration
source project: the map arrived at phase 23 and was available from phase 6; a frontier agent reading four files
produced it for what one hand-cracked giant used to cost (375–475k tokens); giants of 400–770 instructions then matched.
```
provenance: BFM accelerators A4; how-to chapter 07; retrospective §4 item 2

### DK-7 — Build the integration layer before the drafting layer
- **Kernel:** once cracking is systematic, every bank failure is translation-unit plumbing: declaration conflicts,
  def-side signatures, symbol spellings, file placement, table carves, vendor objects. Build the reconcile ladder
  (declaration sync, callee casts, canonical signatures, the carve chain, a real-TU probe) before the waves, and budget
  for banking rather than cracking.
- **When it applies:** Phase 6.
- **Cost:** the dominant token spend of the campaign phases went to re-drafting bodies that were already byte-correct.
```calibration
source project: ≈92% of drafts byte-correct, ≈27% banked at one measurement; with the codegen map, 11 of 12 first-pass
drafts matched and every failure was plumbing.
```
provenance: BFM decision-log 2026-07-24 (S15); how-to chapter 10; retrospective §4 item 3

### DK-8 — Census the corpus SHAPE with fixed instruments before choosing a strategy
- **Kernel:** before picking an approach, measure duplication, structural families, the reach × size distribution and
  the unique tail — with scanners that assert their coverage, a second oracle on anything that steers strategy, and a
  known-true case checked first. A wrong shape measurement costs phases, not hours.
- **When it applies:** Phase 5.
- **Cost:** a "families cannot be automated" doctrine that steered two phases was a broken tool's 0% next to a fixed
  tool's high yield on the same measurement.
```calibration
source project: 0% vs 89% on the same family, broken vs fixed probe; seven silent-skip defects found by the first
coverage audit (phase 26).
```
provenance: BFM how-to chapter 03 Phase 1; accelerators A1; R32/R34/R35

### DK-9 — The differential-oracle harness at 0%
- **Kernel:** run the same question down two independent paths on a schedule and fail loudly on disagreement: matched?
  (source scanner vs built binary); compiles? (standalone vs real translation unit); fleet green? (incremental vs
  clean); scanner coverage? (its count vs an over-approximating set); agent produced work? (its verdict vs its scratch
  directory); bankable? (the draw filter vs the wall oracle). It is the only accelerator that works before a single
  function is matched, and its value grows with every tool added.
- **When it applies:** Phase 5, and every close thereafter.
- **Cost:** each one-off diagnosis of a harness defect is a large agent investigation; a nightly disagreement report is
  minutes of compute.
```calibration
source project: ten-plus blockers in one session, every one a true number about a narrower world, every one caught by
a disagreement; 90k–290k tokens per one-off diagnosis; about half of a late session went to harness defects wearing
model-failure costumes.
```
provenance: BFM accelerators #15 (P31 S68); how-to chapter 04

### DK-10 — The similarity join is a band, not a point — and every hash is audited for both error directions
- **Kernel:** dedup wants under-matching (a wrong merge is a visible duplicate bank); a frontier join wants over-matching
  (a missed neighbour is an invisible singleton). One hash cannot serve both. Build the near tier (relocations
  normalised out, a sound prefilter on length and opcode histogram, edit distance on the survivors) at the same time as
  the exact tier; verify it reproduces every exact pair; control against random pairs for the base rate; rank candidates
  by *work* (a deletion is free, a substitution is thought) and filter lookalikes.
- **When it applies:** Phase 6, with the first banks.
- **Cost:** invisible-singleton debt that accumulates from the first bank and looks exactly like "this function is
  unique".
```calibration
source project: exact hash 22 of 352 reachable open stubs; the band 75 of 352 — 3.4× — on a corpus believed fully
mined after 60+ sessions; 31 pure relocation-only twins; base rate 1.17%; lookalike filter at ratio ≥ ~0.3 removed
17 of 30 "cousins".
```
provenance: BFM accelerators #17; generic-decomp-package 2b

### DK-11 — Regroup the residue by structure before calling it unique
- **Kernel:** when the remaining work looks like a wall of unique functions, try a looser fingerprint (an instruction
  skeleton with relocations and immediates masked). Structural families are TEMPLATES, not free dedup: cracking one
  makes the rest fast, not free, and the ceiling is translation-unit type collisions.
- **When it applies:** as soon as a fleet of similar binaries exists.
- **Cost:** an endgame estimate off by an order of magnitude.
```calibration
source project: a "36,000 unique hand-decompiles" frontier regrouped into ~986 families (90% collapse); remaps later
measured at 88% (exact hash) and 80% (normalised) — a "families are SPENT" verdict had been true of one tier only.
```
provenance: BFM accelerators A6; how-to chapter 10

### DK-12 — Set translation-unit boundaries at the build's forced boundaries, at segmentation time
- **Kernel:** a compiled object contributes one contiguous read-only-data run, so a code unit whose switch tables sit in
  two non-adjacent spans can never bank its other switch functions. Before writing the first subsegment list, dump the
  data island, mark every jump table, group the contiguous spans, map each span to the functions that reference it, and
  put the initial unit boundaries there — and at the other forced boundaries (per-file optimisation levels, interleaved
  library objects). Split where the BUILD forces it and nowhere else; never on archaeology about the original file
  layout. The general principle: a structural decision that is evidenced from raw data, cheap now and strictly more
  expensive later is made early even though its payoff is unproven — the opposite of "probe before investing".
- **When it applies:** Phase 2–3, at 0% matched.
- **Cost:** the price of a split grows monotonically with the declarations that will cross the new boundary.
```calibration
source project: the split was free at phase 6 (13 externs) and cost 57 crossing declarations, 19 moved typedefs and a
compile-error loop at 94% matched; eleven functions had been recorded as "proven gate-rejects" that banked the moment
the carve existed; the fleet check then flagged 4 more binaries holding 16 open functions / 3,613 instructions.
```
provenance: BFM accelerators #20 (P31 S72); `split_indicator`

### DK-13 — The load map as a controlled, regenerable table, the day the loader is understood
- **Kernel:** once the per-binary loader wrapper is named, build *payload → owning binary → load address* as a table
  regenerated from the bytes and gated by byte-proven control rows. Onboarding a binary then needs one lookup instead
  of sessions of hand derivation. Absence from the map is not evidence that a payload is dead — several load routes
  exist.
- **When it applies:** Phase 2 (prerequisite: the loader wrapper + at least two proven control rows).
- **Cost:** multiple sessions per binary deriving a load address by hand; five payloads parked for months.
```calibration
source project: the map arrived at phase 30; the five parked payloads onboarded on their first static candidates once
a base-evidence tool existed (controls 7/7).
```
provenance: BFM accelerators A7; PhaseEnd 32 T2a

### DK-14 — Seed the knowledge base before the first match
- **Kernel:** two sources exist before any function is matched: the compiler's own source and sibling projects on the
  same compiler family. Carry a cookbook across as the starting corpus and adapt it rather than rebuild it. Do the first
  distillation by hand — its vocabulary decides whether anyone finds it later — and key the index by *symptom*, because
  that is what the worker has in front of it.
- **When it applies:** Phase 7.
- **Cost:** every idiom re-bought by a later wave that could not find the earlier lesson.
```calibration
source project: the highest-value late idioms came from four files of the compiler's source, none needing a matched
function; the mature harvest found ~85% of agents' "gap reports" already covered — the base knew, the agents could not
find it.
```
provenance: BFM generic-decomp-package 1; how-to chapter 06

### DK-15 — The permuter runs from the first close draft, and its failures are mined
- **Kernel:** an LLM-free, CPU-bound search over a close draft closes register-allocation and scheduling residuals on a
  different budget from everything else; it should be grinding the near-miss backlog from the first close draft. Verify
  it actually runs on your drafts (a loop that reports "unchanged" must prove it iterated). Then mine its *failures*:
  classify each plateau deterministically from the bytes into missing-transform (extend the mutation set — a permanent
  offline win), mis-classified (fix the routing), seed-structural (redraft) or genuine wall.
- **When it applies:** Phase 7; the classifier before the backlog is large.
- **Cost:** a month of "permuter-class plateau" verdicts that measured nothing.
```calibration
source project: the permuter had silently never run on pinned or K&R seeds (436 stored drafts refused for four
phases); 91% of the open backlog carried no class label when the classifier was written.
```
provenance: BFM how-to chapter 03 Phase 2b; accelerators S80 (1)

### DK-16 — The widening review at every close
- **Kernel:** tooling is correct when written and goes stale as new idioms reveal populations it cannot see. At every
  session and phase close ask *which scanner's denominator just got wider?* — new idioms retroactively convert
  already-open functions into free banks, but only if a tool is widened to see them. Harvest → widen → bank the free
  functions → checkpoint, in that order, as a pipeline step and not as hygiene.
- **When it applies:** every close from the first wave on.
- **Cost:** free banks left invisible; an in-flight escalation paid for a class the base already knew.
```calibration
source project: one idiom review reclassified ten functions / 1,027 instructions in an afternoon and stopped one
escalation mid-spend.
```
provenance: BFM generic-decomp-package 4; accelerators #15 (the scheduling half); memory "harvest + toolify before the next wave"

---

## 2. Instruments — a true number about a narrower world

### DK-17 — Instrument integrity before measurement, as a standing habit
- **Kernel:** any number about to scope real work — a coverage percentage, a "wall", a "cheap win", a zero-hit scan —
  gets its instrument verified before the number is believed. Cheapest form: every scanner asserts its coverage against
  an over-approximating candidate set, and every oracle structurally blind to an error class gets a second, disagreeing
  oracle.
- **When it applies:** always; formalised at Phase 5.
- **Cost:** strategic reversals.
```calibration
source project: four reversals — a families-at-0% verdict (a missing build step), a ~3% ceiling (a compile-flag
artifact), four hidden overlays and ~39 modules (a glob at one payload layer), a class of "compiler beat us" walls
(the scanners).
```
provenance: BFM accelerators A1

### DK-18 — A scanner must model the producer's addressing forms; exactly-zero is a decoder gap
- **Kernel:** before trusting a scanner's *negative*, hand-disassemble one known-good case and confirm the scanner sees
  it; keep that control in the tool and fail the tool if it cannot reproduce it. A register-tracked reference scan is
  blind to forms where the address is split across an upper-half load and the memory access with an index add between;
  an exactly-zero result is more often a decoder gap than a discovery.
- **When it applies:** the first time you scan for cross-references.
- **Cost:** an evening lost to a phantom hunt and a written, wrong structural conclusion in the address ledger.
provenance: BFM accelerators A5 (S46)

### DK-19 — Make the tool state its own denominator
- **Kernel:** three shapes of the same defect. (a) A tool that derives a byte-exact fact from a pretty-printer inherits
  its liberties — assert the parsed count against the underlying size. (b) A refusal-check is measured against what
  the real pipeline does to the input, over work that already succeeded, not against a model of it. (c) An exclusion
  reason is a claim about the tooling on the day it was written — re-derive its premise from the bytes before
  accepting its conclusion.
- **When it applies:** every tool that parses a rendering, every refusal, every exclude list.
- **Cost:** invisible library objects, refused correct work, library code sitting as verbatim assembly for twenty phases.
```calibration
source project: 25 objects / 3,877 instructions invisible to a parser that read 520 words of a 526-word object; a clash
pre-check refused 566 instructions of correct work; a Phase-8 "no single base" comment held three objects for
twenty-three phases.
```
provenance: BFM accelerators S77 (1)–(3)

### DK-20 — A claim names the compilation it survived
- **Kernel:** stream or hash containment proves the bytes relate; a standalone compile proves the BODY; the real
  translation unit proves the body in context; the whole-binary gate proves this binary; the clean fleet run proves the
  fleet now. A report that says "verified" without naming its tier invites the reader to assume the strongest one; a
  claim derived from bytes is a prediction, not a bank.
- **When it applies:** every ledger row, every agent report.
- **Cost:** a "free banks waiting" list that gated zero; a "resid 0" that had compiled nothing.
```calibration
source project: 10 of 32 "verified at closeness 0" gated 0 of 28 — every failure a declaration conflict in the real
unit; 8 of the 28 banked the moment the missing integration lever existed, for zero agent tokens.
```
provenance: BFM accelerators #16 and #18 (P31 S69)

### DK-21 — A verdict from an isolated environment describes the environment
- **Kernel:** isolation (worktrees, sandboxes) makes the worker see LESS; every gitignored input, generated file or
  symlink is a difference between "works here" and "works there", and the worker cannot tell a genuine rejection from
  its own missing input. Negative-control the environment with a known-good item; enumerate and assert the worker's
  inputs; report a missing input as MISSING, never as a verdict.
- **When it applies:** the first parallel gate.
- **Cost:** a third of a frontier classified as blocked by an artifact.
```calibration
source project: a gitignored signature registry absent from every worktree turned every table-carve draft into a
"carve refused" verdict; 21 of them had banked twins and banked in ~25 seconds each.
```
provenance: BFM accelerators #19 (P31 S69)

### DK-22 — Prefer positively-affirmative checks; verify from the process, not the file
- **Kernel:** the checks that could not tell "working" from "not running": a comment between backslash-continued
  argument lines silently drops every argument below it (only a startup banner echoing the parsed values catches it);
  a process-name pattern matches the shell that issued it (anchor the pattern or kill by pid); a pipe through a
  tail-style tool buffers everything until exit (write to a file you can tail); telemetry that exists only in a log
  line is not telemetry (append-only ledgers); a running shell has already parsed its loop body, so editing the script
  changes nothing until a fresh shell starts. Know, for your runtime, which of code, arguments and per-invocation
  defaults takes effect when.
- **When it applies:** every long-running driver and lane.
- **Cost:** hours of lanes running on default arguments and old argument lists.
provenance: BFM accelerators "harness self-inflicted wounds" 1–5 (P31 S58/S59)

### DK-23 — Wire the null-input control into the failure path; one writer, one committer per shared file
- **Kernel:** a 0% gate yield is a statement about the instrument until a no-input control says otherwise. On the first
  batch failure, gate an EMPTY slate (build the committed tree with nothing substituted) before judging a single draft,
  and refuse loudly when the baseline itself is red. A shared mutable file needs one writer and one committer; any
  "commit whatever is dirty" adopter over a file another process substitutes into will eventually commit an unverified
  intermediate.
- **When it applies:** every gated pipeline.
- **Cost:** a day's lane output read as a model failure.
```calibration
source project: ~737 drafts, 160 slated, ~50 clean whole-binary rebuilds burned while HEAD itself built red; the
40-second control would have named it.
```
provenance: BFM accelerators harness wound 6 (P31 S59)

### DK-24 — All verdict layers wired before a remap lane ships
- **Kernel:** a lane that mass-produces candidates from a template needs its verdict ladder built FIRST — cheapest
  oracle to most expensive, every verdict consumed, every drop named. "An oracle exists but the lane does not consume
  it" is a defect with a per-pass machine cost.
- **When it applies:** Phase 6, before the first mechanical lane.
- **Cost:** consecutive zero-yield passes on a population that later banked for free.
```calibration
source project: three consecutive 0-of-117 passes at ~25 minutes of gate machine each; after decomposition the same
population banked 64+ in one session at zero tokens.
```
provenance: BFM accelerators harness wound 7 (P31 S59)

### DK-25 — Byte-locate the residual before blaming the draft; a green baseline per binary first
- **Kernel:** a byte comparison of the built and retail images, mapped through the link map, names the first misplaced
  symbol, its delta, section and object in minutes; address-named symbols carry the retail address in the name. And a
  per-draft verdict means nothing until that binary's baseline builds green on its own.
- **When it applies:** the first red gate.
- **Cost:** days of "cause not determined" ledger rows.
```calibration
source project: one derivation turned 15 mystery walls into three named configuration repairs.
```
provenance: BFM accelerators #12 (P31 S61)

### DK-26 — The cheap probe must call the real planner
- **Kernel:** when a lane is scoped by a cheap feasibility probe, check whether the expensive applier's DECISION half is
  separable from its MUTATION half and make the probe call the planner. An optimistic probe does not merely lose
  opportunities; it manufactures work plans, the expensive direction of the error.
- **When it applies:** every "can this be done?" probe.
- **Cost:** work priced as free that was plan-refused.
```calibration
source project: 96 of 159 open table-carve functions were plan-refused; a previous session had priced 32 of them as
free work on the blind probe; the fix was eight lines.
```
provenance: BFM accelerators #14 (P31 S67)

### DK-27 — Validate the target list; an empty tier terminates the pipeline
- **Kernel:** every target passes a validity gate before a wave (a real function boundary, assembly on disk, inside the
  binary's range, not already banked), and in any cascade a tier with nothing to work on ends the chain instead of
  passing its emptiness downstream — otherwise a phantom costs one agent per tier, the last at the most expensive model.
- **When it applies:** the first multi-tier wave.
- **Cost:** most of a wave spent proving phantoms absent.
```calibration
source project: a 47-target wave burned 9.7M tokens for 20 matches; ~29 targets were not real; 87 of 119 agents proved
phantoms absent; the coverage assertion had refused the list and was routed around.
```
provenance: BFM accelerators A9 (S46)

### DK-28 — "Produced but not consumed" gets an assertion
- **Kernel:** every X-produced / Y-consumed pair in a pipeline gets an assertion (produced − adopted − refused = 0), a
  non-zero exit on violation, and per-run evidence files that are not overwritten by the next run.
- **When it applies:** every pipeline hand-off.
- **Cost:** a bank that died with its worktree while the summary printed success.
provenance: BFM accelerators S80 (4)

### DK-29 — A byte gate is a null oracle for "is this C?"
- **Kernel:** a function's assembly spliced in as a file-scope inline-assembly body matches by construction, builds green
  by construction, and is counted by the progress tool. Run a strict verbatim check in the per-bank close, and never let
  a ledger's best draft be an assembly body.
- **When it applies:** from the first bank.
- **Cost:** a fake bank and a census one function off.
provenance: BFM accelerators S80 (2); R62

### DK-30 — A headline percentage ships its remainder
- **Kernel:** every headline % is published with its remainder, and the remainder is reconciled against an independently
  derived list of what is actually open. One subtraction catches a denominator carrying the wrong population.
- **When it applies:** every progress report.
- **Cost:** a wrong headline standing for weeks.
```calibration
source project: "59.8%" stood six weeks with ~32,000 instructions remaining against a frontier that summed to ~4,000 —
the denominator carried 31,000 linked-library instructions.
```
provenance: BFM accelerators S78 (2)

---

## 3. The campaign

### DK-31 — Census what is already drafted before drawing anything
- **Kernel:** join the wave manifests, the filesystem and the corpus oracle to answer "is there already a draft for this
  open function?" for zero tokens, and classify each draft in its real translation unit at the optimisation level the
  target shipped with (a verdict at the wrong level is pure artifact). The classes route themselves: match → gate;
  compile failure → the recovery ladder; near → the permuter; far → redraft.
- **When it applies:** before every draw.
- **Cost:** agents re-deriving work already on disk or already banked.
```calibration
source project: 193 of 530 open functions already had a draft, 37 byte-correct in their real unit; ~109 of 240 agents in
two waves re-derived existing work; wiring the shipped optimisation level turned 8 "near" verdicts into 6 matches.
```
provenance: BFM accelerators #13 (P31 S67)

### DK-32 — Wire the read side of agent journals with the write side
- **Kernel:** if agents produce a per-item report, the next agent on that item must be handed it. An archive of your own
  verified outcomes is training data for your own tooling, and the write side feels complete on its own because the
  notes are being saved.
- **When it applies:** the day agents first write structured notes.
- **Cost:** the hardest functions re-attacked with the same levers wave after wave.
```calibration
source project: 400 journals / 6,658 records / 896 distinct index-gap reports unread for thirty phases; with the notes on
the card, 38 of 39 matched on the hardest frontier and 4 of 39 recovered a body that had already matched.
```
provenance: BFM accelerators "the agent journals" (P31 S71); memory "journal notes are pack fuel"

### DK-33 — Parallelism defaults for fleet-wide tools
- **Kernel:** return every verdict a sweep already computed (not the first failure); processes for CPU-bound work and
  threads only for subprocess waits; longest-first scheduling with results re-sorted into the caller's order; per-item
  search when independence is argued, not assumed; a fixed temp path is a correctness bug the day two workers run; seed
  a pool with one in-process result before fanning out. The acceptance test is a regression — revert, re-run the
  identical command, require the same output and a byte-verified fleet — not a stopwatch.
- **When it applies:** the first tool that iterates the fleet.
- **Cost:** a slow gate is a bug, and a serial one hides over-exclusion.
```calibration
source project: propagation 24 → 11.4 minutes with +62 member instances (the faster path was also more correct);
threads kept 0–4 builds alive at load 3 on 32 cores, processes 14–29 at load 34.75; `-j` on a single build 7.18 → 1.18 s.
```
provenance: BFM accelerators A8; memories "gating speed playbook", "pass -j to every build", "fleet-tool parallelism defaults"

### DK-34 — Agents write deliverables early; one JSON line last; harvest a dead session by tool
- **Kernel:** the draft file first, the verdict last, the final message exactly one JSON line with prose in a report
  file. Agents outlive the session that spawned them; a coordinator that reads prose results dies mid-wave; the
  recovery path is the transcripts, by tool, never memory.
- **When it applies:** the first agent wave.
- **Cost:** verdicts stranded in a dead session; re-drafting functions whose match sat in a transcript.
```calibration
source project: 22 verdicts (two matches worth 724 instructions) unprocessed until a successor replayed the transcripts;
two of eleven harvested agents were matches worth 765 instructions.
```
provenance: BFM R67; accelerators S80 (5), P32 T3 (1)

### DK-35 — Per-item work directories; a deliverable directory no agent cleans
- **Kernel:** each agent works in its own directory keyed by binary and address, may clean only that, and never runs
  find, remove or move outside it; deliverables go to a directory no agent owns.
- **When it applies:** the first parallel wave.
- **Cost:** sibling deliverables swept away by one agent's tidy-up.
provenance: BFM P32 T3 (2); R48

### DK-36 — The build is the batch verdict
- **Kernel:** a per-draft oracle is blind to cross-draft integration (two drafts spelling one global differently, a data
  block only the stub defined, a prototype a sibling bank added between verification and splice). Bank per translation
  unit: verbatim grep → the real-TU probe for every draft in the CURRENT unit → splice all → ONE build → hash → commit
  only on green, leaving the tree for diagnosis on red. Two sentences in the drafter's brief (define any data block your
  stub owns; spell shared symbols exactly as the unit does) make the next agents self-serve it.
- **When it applies:** the first batched bank.
- **Cost:** a batch that failed twice with eleven of twelve drafts individually correct.
provenance: BFM accelerators P32 T3 (5)

### DK-37 — A live probe file in the source tree is build input
- **Kernel:** a tool's temporary file under the source directory is picked up by the build's file discovery; guard at the
  consumer (exclude dotfiles in the build's find) so every probing tool is covered at once, and list any probe that must
  live there.
- **When it applies:** the first concurrent probe.
- **Cost:** a false batch failure and a wasted rebuild.
provenance: BFM accelerators P32 T3 (7)

### DK-38 — A pointer-only callee's declaration is a guess; re-probe in a sandbox unit
- **Kernel:** a declaration that exists only because the unit takes the function's address carries no signature
  information; read the unit's own declaration of the function before touching the body, and treat a block-scope
  declaration of a struct pointer as a block-local tag no file-scope definition can match. Re-probe a compile failure in
  a COPY of the unit under scratch (symlink the headers beside it) rather than by editing the source tree.
- **When it applies:** the first "conflicting types" refusal.
- **Cost:** dozens of drafts against a declaration that constrained nothing.
```calibration
source project: 37 drafts died on a 45-instruction function that was byte-correct on its first try; three of seven
"pinned walls" failed only for declaration reasons, reproduced in a sandbox with zero commits.
```
provenance: BFM accelerators S80 (3), P32 T4 (8)

### DK-39 — The card is fuel, not a ticket
- **Kernel:** the unit of work handed to a model carries everything the project already knows that bears on it,
  assembled deterministically at zero token cost: the target and its destination file; an already-matched sibling with
  the same skeleton (the banked twin, found over the WHOLE world, ahead of the open one); what the destination file
  already declares; the project-wide declaration consensus per callee; the function's own past-attempt history; the
  lever the atlas believes applies plus where to read about it; the same-unit neighbours' declarations of shared
  globals. And the pack must be where the agent is told to read it.
- **When it applies:** the first wave.
- **Cost:** the twin field alone moved a wave from zero banked to fifty-one; a misplaced laws file silently degraded
  every wave's brief for weeks.
```calibration
source project: banked-twin-on-card 4 of 4 on a control draw and 15% fewer tokens at 64% of the wall-clock on the next
wave; one agent spent 102k tokens re-deriving a function banked verbatim in another binary.
```
provenance: BFM how-to chapter 05 "The card"; R44

### DK-40 — Lanes with different clocks; free work before paid work
- **Kernel:** drafter, gater, maintenance, watchdog, distiller and each excluded population run as independent,
  restartable lanes with their own rates; the drafter is the clock-limited resource and is never stopped to ship a
  change. Mechanical zero-token work (twins, remaps, propagation) runs in its own lane whenever the paid lane is idle.
  Collapse same-skeleton members to one card and defer the siblings to the free remap.
- **When it applies:** the first campaign.
- **Cost:** idle time from stopping the wrong lane; an excluded population that got no attention while the fast loop
  starved for work items.
```calibration
source project: 139 of 162 idle minutes from stopping the drafter to ship a change; drawn one-per-skeleton, 71 agent
slots carried 19,266 instructions of potential of which 4,954 sibling instructions banked mechanically the same session.
```
provenance: BFM how-to chapter 05 "Lanes" and "Free work before paid work"; memory "autonomous lane architecture"

### DK-41 — Gate the directory, never the verdict list; reconcile before any rebuild; recover before re-drawing
- **Kernel:** score every draft file the wave produced and assert coverage (banked + failed + no-verdict == drafts)
  before recording a row. After a gate group's drafts land, one deterministic reconcile pass over that group's slate
  precedes the rebuild (two targets sharing a unit create each other's conflicts). After the gate, triage failures into
  body and plumbing, bank the plumbing ones through the ladder, and only then record the wave's yield — the gate number
  is not the close rate.
- **When it applies:** every wave.
- **Cost:** matches reported as nothing; walls hunted that were not there.
```calibration
source project: a byte-identical 579-instruction match reported as nothing by a driver that grepped its child's output;
5 of 8 at the gate became 8 of 8 after deterministic recovery for ≈0 tokens; 26 of 27 rejections on one slate were
byte-perfect drafts.
```
provenance: BFM how-to chapter 05 steps 6, 6b and "Then recover"

### DK-42 — Instruction weight, not head count; concentration is a draw-time choice; card supply binds
- **Kernel:** the metric to beat is pool realisation in instructions, not bank rate in heads — a wave banking every head
  of a small pool is worth less than one banking half the heads of a large one. The number of whole-binary rebuilds a
  wave needs is chosen at draw time by concentrating targets per binary, and it is the wall-clock lever. And for most of
  a campaign the binding constraint is work items, not model capacity: reach for more cards before more workers.
- **When it applies:** every draw.
- **Cost:** waves optimised for a flattering rate; workers added when work items were the shortage.
```calibration
source project: 16 of 16 heads / ≈7,200 instructions against 7 of 16 heads / 10,616 instructions; gate groups 5 → 7 → 9
then 3 once the draw concentrated (drafts per rebuild 7.8 → 24.3); a whole "thinning frontier" was a default flag
excluding one lever lane (607 of 1,179 members).
```
provenance: BFM how-to chapter 09 "Instruction weight" and "The gate's cost"; chapter 08 "Budgets"

### DK-43 — Budget per lane; measure the routing cliff; the strongest model for new wall classes only
- **Kernel:** run a small manual wave first and measure bank rate by instruction count — that is the routing cliff, and
  the first hand-waved boundary will be wrong. Cheap tiers are honest filters (every claimed match was real) but never
  the gate. Escalate sooner: a cheaper tier run into a wall costs the failures and then the escalation. The strongest
  model is for genuinely new wall classes — an unsolved tooling problem, an adversarial review, a residual no documented
  lever reaches — briefed with every measured number, the files to read first and the house rules; it is NOT for
  reviewing a corpus against an existing knowledge base, and its one outright win was reading the compiler's source.
- **When it applies:** Phase 8, the first waves.
- **Cost:** the wrong tier at both ends.
```calibration
source project: the cheap tier's success fell from 86% to 20% across the size range; a 100-worker A/B put cheap
drafters at the same match rate as the strong tier under ~50 instructions at ≈4.8× lower cost per match; 63 claimed
matches were 63 real; a local 7B model saturated the ≤15-instruction population for $0; the most expensive single row
was a 655k-token frontier agent on a function whose answer was a grep.
```
provenance: BFM how-to chapter 08; memories "subagent model ladder", "cheap-tier A/B validated", "fable agents for lane tooling"

---

## 4. Compiler walls

### DK-44 — Attribute the residual to a pass with a dump line before sweeping levers
- **Kernel:** a residual's first artifact is the compiler's own dump line that owns it — the scheduler's ready list, the
  loop optimiser's desirability line, the allocator's priorities and hard-register assignments, the reload pass's
  choices, the hazard walk. Dump from the REAL translation unit (a standalone compile is not faithful on units with many
  declarations). A wall verdict without a pass and a dump line is a hypothesis.
- **When it applies:** every compiler-internal residual.
- **Cost:** thousands of variants sweeping the wrong lever family.
```calibration
source project: six of seven wall citations named the wrong pass; 22 hand spellings and ~4,000 agent sweeps measured
nothing; nine of twelve rows then banked from one dump line each.
```
provenance: BFM accelerators P32 T4b (10)/(11); R65

### DK-45 — A producer census before a spelling sweep; the reproducer battery per ghost species
- **Kernel:** enumerate from the compiler source every site that can produce the artifact (a phantom stack slot, an
  extra callee-saved register), refute each on the bytes or a dump, and only then sweep spellings; "PROVED" is the table
  with every row refuted, and it names its list. Build the one-second battery of five-line reproducers for every species
  of the artifact — including species not yet in the cookbook — before probing the real function.
- **When it applies:** every "proved unmatchable" verdict.
- **Cost:** two sessions of real-function probes against an answer a five-line function gives in seconds.
```calibration
source project: two formal proofs each one producer short; 18 reproducers found the first missing producer (a combine
pass's self-update bookkeeping gap) and an 8-variant sweep the second (the loop optimiser's user-variable rule with the
CSE pass's later-mention canonicalisation); the banks were a three-statement chain and a three-times-read invariant.
```
provenance: BFM accelerators P32 (12), (15); R69, R73

### DK-46 — Port the banked sibling's spelling; grep the idiom's constants; objdump the hit's window
- **Kernel:** when a same-family sibling is banked, port its body with the target's constants before touching a dial —
  a residual-class name is the family's signature, not a lever list. Before any scheduling or allocation dial on a
  packet-building function, grep the source for the idiom's literal constants and objdump each hit's window against the
  target: a same-shape sibling with different base registers scores as a stranger in every similarity metric.
- **When it applies:** every hand pass, step zero.
- **Cost:** the most expensive rows of the endgame.
```calibration
source project: one row matched first try after three agent passes, a 135-variant sweep and a hand pass on a
five-dial draft; another after an Opus pass, a 655k-token frontier pass with 3,360 variants, five pins and a fence —
the answer was a 0.55-scored "weak cousin" found by grepping one constant.
```
provenance: BFM accelerators P32 (13)/(14); R71/R72

### DK-47 — Read the allocation order before any register lever; pins are symptoms
- **Kernel:** the callee-saved bank is the global allocator's priority order (references weighted by live length);
  print the allocation table from the real unit's dumps first. The number of uses the target's register order implies is
  a hard constraint on the C; a register pin only masks it, and every pin comes off once the source shape is right.
- **When it applies:** every callee-saved-register residual.
- **Cost:** forty variants steering a value into a register that its use count forbade.
provenance: BFM accelerators P32 (16); memory "don't conclude unsteerable — try register pins" (superseded by the shape rule); R73

### DK-48 — A lever that measures worse may be a cascade
- **Kernel:** on any regression of a mechanism-grounded lever, diff the pass dumps for a SECOND change before discarding
  it — the lever's saving may have flipped a hoist past a desirability threshold, paid back with a pad. Instruction-count
  pads are a dial re-counted after every in-loop change.
- **When it applies:** every "the right lever made it worse".
provenance: BFM accelerators P32 (9)

### DK-49 — Read a permuter waypoint's diff both ways
- **Kernel:** a waypoint with a semantic mutation (a wrong-width load) may still carry the sound levers that are the
  whole answer: diff it against the seed, drop the unsound hunk, re-measure the remainder; then re-spell any
  uninitialised-read trick as well-defined C that keeps the bytes.
- **When it applies:** every rejected or accepted waypoint.
provenance: BFM accelerators P32 (6); R63

### DK-50 — Provenance → archive → link → compiler; "no single base" means partition
- **Kernel:** before a wall verdict on a band of a mixed binary, score every vendor signature set you hold against it
  (the disassembler's loader often ships per-version signature files that name the library, the version and every
  function without the archive); fetch the archive the signatures name; link it. A vendor object refused for "scattered
  common data, no single base" is a partition problem: cut the section into per-base pieces along the producer's own
  symbol structure in the shared link-prepare path, and confirm every cut against an independent oracle.
- **When it applies:** the first "compiler wall" inside a library band.
- **Cost:** wall verdicts on code you were never going to compile.
```calibration
source project: twelve walls with proofs attached were the vendor's controller library, a 383 KB archive away; the
signature files had sat on disk since phase 1; three objects held for twenty-three phases closed 3/3 in an afternoon
of ELF surgery, including one a probe had certified as a genuine wall.
```
provenance: BFM accelerators S78, S79, S79 (2)

### DK-51 — A converged multi-agent plateau is not a mechanism proof
- **Kernel:** five agents agreeing on a residual with a "proven" mechanism is a claim; two same-unit neighbours may
  document the exact fix. The pack carries the neighbours' DECLARATIONS of the shared globals, not only their bodies, and
  a plateau verdict names the exemplar it was checked against. Route a row to the frontier tier when its blocker is an
  unread compiler pass, and to a mid tier once a sibling's recipe exists.
- **When it applies:** every multi-agent plateau.
```calibration
source project: two functions closed in one pass each after eight agent attempts across two sessions; a frontier pass
banked 9 of 12 completed rows where every prior tier had 0, at ≈325k tokens per row.
```
provenance: BFM accelerators P32 (3), (10)

### DK-52 — The source-version trap
- **Kernel:** the compiler source in community circulation may be a later version than the one that built the game —
  behavioural differences and line-number drift large enough to land inside a different function. Stage the vanilla
  source of the pinned version, and audit every citation line by line, each refutation challenged independently.
- **When it applies:** the day the codegen map starts.
```calibration
source project: the circulating "2.7.2" tree was 2.8.1; the audit of 135 citations: 119 confirmed, 40 line-drift, 7
refuted of 21 raised.
```
provenance: BFM how-to chapter 07 "The source-version trap"; the gcc-map citation audit (P33 E3)

---

## 5. The repository and publishing

### DK-53 — Rehearse every irreversible repository operation; positive assertions, pair by pair
- **Kernel:** a history rewrite is proven on a scratch copy by comparing every rewritten commit with its original:
  purged paths absent AND kept files identical AND the pruned set equal to the derived set. Absences alone pass on
  corrupted output.
- **When it applies:** any rewrite, purge, or mass move.
```calibration
source project: the first rehearsal caught an empty-blob id in the strip list that silently undid every "file emptied"
change across 4,000 commits, and the unchanged-commit case; the real run had 0 failures.
```
provenance: BFM R76; P33 C1

### DK-54 — Linked worktrees pin history
- **Kernel:** every linked worktree's HEAD is a ref that survives a garbage collection; audit and prune them before any
  gc or purge, and never create gate worktrees without a reaper.
```calibration
source project: twelve forgotten gate worktrees (12 GB) pinned 3,729 old commits.
```
provenance: BFM R77; P33 C9

### DK-55 — A "read-only" probe that fetches is a writer
- **Kernel:** a check that fetches, clones or builds does so in a throwaway and ends with a self-check that the guarded
  repository is unchanged.
```calibration
source project: the purge probe re-imported 5.97 GiB of the purged history into the guarded repository on every run.
```
provenance: BFM R81/R57; P33 S89

### DK-56 — The host publishes pre-force-push tips
- **Kernel:** enumerate the HOST's metadata surfaces (activity views, event feeds, pull-request refs, caches) in the
  rewrite design, not only the repository's content; gate a visibility flip on the old objects being gone, or recreate
  the repository.
provenance: BFM R82; P33 S89

### DK-57 — Numbers generated, never typed; commits cited by date and subject
- **Kernel:** every published figure is produced by a tool that asserts the published copy is fresh; a prose number is a
  dated snapshot with its command; long-lived documents cite commits by date and subject because a rewrite changes every
  hash.
```calibration
source project: every hand-typed number in the old README was stale; 1,238 hash citations had to be resolved through a
commit map after the rewrite.
```
provenance: BFM R75; P33 D1/C8

### DK-58 — Outward text is a person's; no automated traffic against community infrastructure
- **Kernel:** filtering AI tells out of model prose makes an upstream contribution worse, not acceptable — the dense
  code-span formatting and exhaustive structure are the giveaway. The maintainer writes every outward word from a facts
  list, short and plain, after reading the target's AI-contribution policy. Community services are used by a person in a
  browser; anything repetitive is replicated locally.
- **When it applies:** every issue, pull request, post and outreach note.
```calibration
source project: a permuter pull request and its issue were closed the same day by a maintainer who read them as
machine-written and said why it cost him; a sibling project forbids autonomous-tool pull requests outright.
```
provenance: BFM R83; gen3-standards conduct; failure museum row 37

---

## 6. Governance and sessions

### DK-59 — The checkpoint is written to be replayed, not summarised
- **Kernel:** the number-one failure mode of a long multi-session agent project is a fresh session misreading a
  compressed hand-off. The in-phase checkpoint carries paths, commands, hashes, tool invocations with their gotchas, a
  file inventory and the exact next step, and the next session replays it verbatim; every perishable artifact is already
  in a file before the block is written; a dead session's checkpoint is reconstructed by its successor from the
  transcripts.
- **When it applies:** every session boundary.
```calibration
source project: the last thirty sessions resumed without a question; one earlier hand-off nearly closed an open phase.
```
provenance: BFM R64; memories "checkpoint CURRENT_PHASE before pausing", "checkpoint = everything already banked"

### DK-60 — Measure the steady state; report every lane; quote the denominator
- **Kernel:** bucket a metric over time before calling it a ceiling; a status check covers every lane with its own
  metrics; every rate, cost and EFFORT estimate ships with what it is a fraction of — a count that is true of an
  unasserted scope nearly defers real work.
```calibration
source project: half the false ceilings of one phase were launch bursts; "2,318 externs to fix" nearly deferred 39% of
the main executable — 57 crossed the line.
```
provenance: BFM R41; memories "measure the steady state", "report every lane", "quote the denominator"

### DK-61 — A known-true case before reading any instrument's output
- **Kernel:** test every scan, join, census and verdict on one case whose answer is already known before reporting it.
```calibration
source project: five of one session's biggest "findings" were artifacts of the instrument, each caught only this way.
```
provenance: BFM memory "check against a known-true case" (P31 S75)

### DK-62 — The human gate
- **Kernel:** automation fills between the gates; it does not replace them. Nearly all of the work was the agent's, and
  every wrong DIRECTION was caught by a person at a plan or milestone gate — a re-charter, a "everything that is not
  vendor code or original hand-assembly must be C" directive, an in-place-flip decision.
provenance: BFM retrospective §5; hindsight principle 7

### DK-63 — Capture the why while it hurts
- **Kernel:** the terse "what changed" record survives a context boundary; the *why* evaporates. The decision log entry
  (context and belief → what failed → the pivot → the measured why → the hindsight path) is written during the session
  that learned it, and the PhaseEnd carries the narrative axis — what was believed, what failed and why it looked right,
  what it cost, what to do sooner — because the transcripts die and the retrospective is rebuilt from the files.
provenance: BFM R31; memory "PhaseEnd verbosity serves the retrospective"; the retrospective's own method

---

## 7. Readability at day one

### DK-64 — Readability is done at draft and bank time, not after 100%
- **Kernel:** the community's bar for a decompilation (a full naming scheme, typedefs, a formatter, decimal for counts
  and hex for masks, a marker on every match-forcing trick, "better unnamed than named wrongly") is met at the moment a
  body is banked, gated exactly like the match was. Six inversions of what the source project did after the fact: pins
  recorded at draft time and marked if kept; shared bodies as C files per system from the first propagation; types
  canonical at bank time; names with recorded evidence; formatting installed with the first C file; file layout by
  system with unit boundaries decided at segmentation time. A matching decomp that is bytes without understanding is the
  community's specific complaint about machine output; the inversions are the answer.
- **When it applies:** from the first bank (Phase 6); the intake's Part C.
- **Cost:** a whole generation of byte-neutral rework after 100%.
```calibration
source project at 100%: 43,925 register-pin declarations; 5,147 shared bodies as macros in one 8.4 MB header; 1,232
struct definitions, many drafter-invented variants of one type; 16,335 address-named functions and 61,898 address-named
data symbols; 3,558 of 4,287 C files carve splits; no formatter configuration; almost no comments.
```
provenance: BFM gen3-standards (2026-09-07) + gen3-handoff §2.2; the sotn-decomp style guide read as data

### DK-65 — Types are a banking lever and a width lever, not a byte lever
- **Kernel:** a type name never moves a byte — the compiler does not care what a field is called — and the source
  project measured exactly that early, correctly, and then drew the wrong second conclusion: that types could wait until
  after 100%. Read the other way, its record says types are the largest *banking* lever it underweighted. Banking, not
  cracking, was the bottleneck, and a large share of gate failures were declaration conflicts — a signed halfword against
  an unsigned one, one arity against another, a structure a drafting agent invented in isolation because there was no
  registry to draft against — so the tree filled with variants of a few shapes and a whole reconcile ladder was built to
  repair what a canonical type file would have prevented. And the one place a type *does* touch bytes is width and
  signedness: a halfword load's sign, a pointer arithmetic scale, a narrower accumulator that stops a value being re-read;
  the permuter cannot change a type, so every width near-miss was dial work until the declaration was right. The
  achievable early form is a discipline, not a census: **a canonical type file from the first bank that grows one proven
  field at a time, the width and signedness fixed by the bytes at bank time, with no draft allowed to bank a duplicate
  definition of an existing shape or a raw address cast, and names only with evidence.** It costs one duplicate-definition
  and raw-cast check per bank; it removes most of the declaration-conflict class before a ladder is needed, lowers the
  width class of near-misses on the first pass, and leaves nothing to unify after 100%. It would not have shortened one
  compiler-pass crack — do not expect it to.
- **When it applies:** from the first bank (Phase 6, the multipliers) — the type layer is part of what makes drafts bank;
  Phase 10 is short when it held.
- **Cost:** a reconcile ladder built reactively; a generation's struct unification and raw-cast removal after 100%.
```calibration
source project: rich decompiler context (the recovered actor structure + the jump tables) scored 0 better / 10 same /
2 worse on a 12-function structural-miss sample, identical bytes (phase 17) — right for cracking; ≈92% of drafts
byte-correct and ≈27% banked at one measurement, declaration conflicts a large share of the gap; 1,232 struct
definitions in the tree at 100%, most of them variants of a few shapes; 143 raw address casts; the width class
(a u16 accumulator as a CSE firewall, an object-table symbol declared u8, the scaffold's ×4 pointer arithmetic) in
the last hand cracks (phase 32).
```
provenance: BFM decision-log "P33.5 S91-b" (the hindsight on types, 2026-09-07); struct-core-pivot.md (2026-06-19); cookbook §501-N/§501-R

---

## 8. The failure museum, condensed — what looked right at the time

The exhibits below are the source project's, stripped of names and numbers; the column that matters is *why it looked
right*. A failure that looks wrong gets fixed the same day; these did not.

| What it looked like | What it was | Why it looked right | Kernel / rule |
|---|---|---|---|
| A recompilation first would force the memory map into the open | A matching decomp needs no recompiler | The one precedent had done it that way | decomp-first (intake item 2) |
| Structural families template at ≈0% | A probe silently omitted a required carve; run correctly the family matched high | The probe exited zero with a number | DK-8, DK-17 |
| The engine holds a bytecode script VM to match | Compiled dispatch tables; no VM | Every game has a script VM | G1 |
| The remaining engine core is blocked by loose typing | The wall was the compiler's own code generation | Types are the usual suspect | DK-6 |
| Residuals that resist every rewrite are unsteerable | Reading the compiler's passes explained them one by one | Dozens of rewrites had failed | DK-6, DK-44 |
| A small "swing number" is a wall class | A compile-flag artifact of the tooling | It was consistent across probes — the probe was consistently wrong | G23 |
| The endgame plan's numbers describe the remaining work | Broken scanners had been measuring the frontier | Nothing had ever checked the scanners | DK-9, G19, G21 |
| A corpus scanner reports the decomp complete | It could not answer and returned an empty set | An empty "remaining" list is what done looks like | G28 |
| Every draft of one binary reads "near" for a month | The shared gate compared it against another binary's hash | The gate was green — for the wrong reason | G42 |
| That binary cannot be gated ("a linker defect") | Incremental builds re-ran a linker-script rewrite | Byte-correct drafts gated red reproducibly | G9 |
| The waves are limited by idioms the drafters lack | Most drafts were byte-correct; integration was the bottleneck | Failures arrived as "no match" verdicts | DK-7 |
| The medium has been fully counted | Dozens more code-bearing payloads | The fleet was 100% green on what it built | G21 |
| A band of the executable is a compiler wall, proofs attached | The vendor's library; the archive was online | Each proof named a real pass behaviour | DK-50 |
| A function is a wall | Its body was byte-identical; the wall was a split boundary | The diff was real | DK-12, DK-25 |
| The permuter has exhausted the near-misses | It had never run on that class | It reported "unchanged" every cycle | G35 |
| A function is finished | Its "C" was the assembly pasted into an inline-assembly body | The byte gate is a null oracle for "is this C?" | DK-29 |
| Two functions are PROVED unmatchable by producer censuses | Each census was one producer short | Every refutation on the list was real | DK-45 |
| The register pins are the levers | Symptoms; every pin came off once the shape was right | Pins moved the diff | DK-47 |
| A low-scored "weak cousin" is unrelated | The exact same-shape sibling | The similarity score was a number | DK-46 |
| The exclude list is current | Most entries stale the day after it was written | Every entry had been true once | G38 |
| The agents have the laws file | It sat one directory below where they were told to read | Two agents said so; the rest never mentioned it | DK-39 |
| "No banked twin — derive from the assembly" | Banked verbatim at the same address in another binary | True of the card, false of the world | G44 |
| A whole wave was a drafting collapse | The gater had accepted a class it could not gate | The rest of the wave banked normally | G28 |
| Several functions failed the gate wave after wave | Drawn at a different optimisation level than their object | Each failure looked like a model failure | G38 |
| "12 banked of 12" | Names compared against a set keyed by address — always true | It printed a fraction | G27, G20 |
| Healthy lane activity in the logs | The draw refused every wave during any gate and fell back to old ones | The logs showed work | scope a refusal to what is actually unsafe |
| The executable's denominator is settled | The disassembler's boundaries under-counted it | It had been stable for a month | G20 |
| The history rewrite is a mechanical filter run | An empty blob in the strip list undid every "file emptied" change | The filter exited zero and the paths were gone | DK-53 |
| The local gc dropped the old history | Forgotten worktrees pinned it | The ref list had been read before the worktrees were | DK-54 |
| The purge probe is read-only | Every fetch imported the purged closure | The probe only reads the host | DK-55 |
| A fresh session read a hand-off as done | The summary said so | A compressed summary looks like a conclusion | DK-59 |
| A wall class's effort estimate | A count that was true of an unasserted scope | The number was real | DK-60 |
| Two ledger messages say "banked" | A helper that did nothing on an empty list; a wrong directory | The intent was there | G28, G37 |
| The permuter plateaued; its logs are quiet | Empty logs: never started | Quiet looks like working | G30 |
| The rate limit is low | A launch burst; the steady state was far higher | The first measurement was a real number | DK-60 |
| An agent's "no draft" after a rate limit | It sat a few instructions from a match with its history on disk | The verdict said no draft | G26 |
| A model-drafted upstream contribution with the tells removed | Read as machine-written anyway, closed | The content was proven and the style pass looked like courtesy | DK-58 |

**The pattern, stated once.** Almost every wall was an instrument: correct when written, stale as the population under it
widened, returning a true number about a narrower world, with nobody comparing what it found to what it should have
found. The cure is not vigilance — the author of one of the rules above rebuilt the exact defect it warns about an hour
later in a different file. The cure is structural: two paths per question on a schedule, a known-true case before any
reading, the denominator on every number, and a decision log that records each of these while it still hurts.

---

## Coverage
- **Order (before the first crack):** DK-1 … DK-16 — 16 kernels.
- **Instruments:** DK-17 … DK-30 — 14 kernels.
- **The campaign:** DK-31 … DK-43 — 13 kernels.
- **Compiler walls:** DK-44 … DK-52 — 9 kernels.
- **The repository and publishing:** DK-53 … DK-58 — 6 kernels.
- **Governance and sessions:** DK-59 … DK-63 — 5 kernels.
- **Readability at day one:** DK-64 … DK-65 — 2 kernels.
- **In all:** DK-1 … DK-65 — 65 kernels (the installer's check compares `grep -c '^### DK-'` against this figure).
- **The failure museum:** 37 exhibits, condensed.
- Conduct rules are not duplicated here; they are the registry seed's E.7 group. The generic engineering kernels of
  ProjectArchitect's own corpus apply unchanged and are not repeated.
