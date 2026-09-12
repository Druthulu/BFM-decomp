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

### DK-65 — Types are a banking lever and a width lever — and, in gcc 2.7.2, a struct MEMBER is a scheduling lever too
- **Correction (source project, Phase 37 T2, 2026-09-12):** the kernel below was written from Phase 17's measurement, which tested a
  decompiler's drafting with a struct in context — not the spelling of a matched body. On the bytes, `*(T *)(p + k)` and `p->f` are NOT
  the same code in gcc 2.7.2: a member/array access carries `MEM_IN_STRUCT_P` (`expr.c:4568-4577`, `:4888`), a cast on a sum does not, and
  the scheduler's alias escape (`sched.c:837-865`) and cse's kill table read that flag. A struct-spelling probe on 165 matched bodies was
  byte-neutral on 90.6 % and moved instructions on the rest; a per-site minimal kept-cast set closed every one. So: a canonical type
  layer still pays as a banking and width lever from the first bank — and it must be introduced under the byte gate, per access, never by
  a blanket rewrite that assumes neutrality. The name still moves nothing; the SPELLING can.
- **Kernel (as first written):** a type name never moves a byte — the compiler does not care what a field is called — and the source
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

## 8. Added by the coverage and log-mining passes — the record's residue

*The kit's coverage check derives every rule and every hindsight entry of the source project and refuses one that is neither
cited by a provenance line nor dispositioned; the three kernels after it are what that check found in the record and nowhere in
the kit. The twelve after those come from a pass that read every phase worklog of the source project once more (some thirty
thousand lines, one read-only agent per slice) for lessons banked in none of its distilled records — 777 candidates, 634 already
banked, 143 new, clustered here by theme. Each provenance line names the worklog lines the lessons came from.*

### DK-66 — A ledger's tie-break, a checker's widening and a blanket commit are part of the instrument
- **Kernel:** three bookkeeping choices around an oracle that changed its verdicts without anyone reading them as part of it.
  A ledger that keeps the earliest record at equal closeness can never render a re-verdict — the tie-break IS the instrument.
  A link checker that widens its document set must classify a missing *promised* target as pending, never broken (a forward
  link registered with the task that will create it), and the pending list must be empty at a phase close — otherwise every
  new page is a false failure or the check is turned off. A blanket "commit the dirty tree rather than revert it" is right for
  the source tree, where a bank must never be lost, and wrong for configuration, where it adopts a collapsed file and takes a
  binary red with it.
- **When it applies:** any ledger with a best-of ordering; any checker whose input set grows during a phase; any committer
  that stages more than the paths it changed.
- **Cost:** a re-verdict that never appeared; a docs check that would have gone red on every planned page; a config collapse
  committed as a backup.
```calibration
source project: the backlog ledger's earliest-record tie-break hid a re-verdict (one session); the link checker's pending list
carried 10 planned pages mid-phase with 0 false failures; one blanket commit adopted a collapsed overlay config.
```
provenance: BFM R70 (the ledger's tie-break), R80 (PENDING never BROKEN; `doc_links` + its pending list), R52 (a blanket committer must not adopt a collapsed file)

### DK-67 — An ignore file's directory-form rule is a wall no later block can climb
- **Kernel:** git never descends into an excluded directory, so a directory-form rule (`.run/`) defeats every re-include
  written beneath it, however many blocks later. Write the by-contents form (`/.run/*`) and the `!` re-includes under it, and
  write it FIRST — a later block cannot undo a directory rule, and an installer that may not edit above a marker cannot repair
  it. The source project's own governance package wrote the directory form; the kit's installer had to be given one named
  edit above a marker to fix that single line, found by the dry-run's negative probe.
- **When it applies:** the first commit's ignore file, and every ignore block appended by a package.
- **Cost:** one failed dry-run install and a special-cased installer step; on the source project, a tracked scratch tree that
  could only be shaped by narrowing re-excludes.
provenance: BFM accelerators P33.5 S91 (1); the kit's dry-run run 1 (Step 3.7's negative probe); the source project's conventions page

### DK-68 — A summarised signal is a claim, not ground truth
- **Kernel:** a count, a verdict or a "done" that reaches you through a summary — a sub-agent's report, a reconnaissance
  note, a compressed hand-off, a coordinator reading prose results — is a claim about the bytes, not the bytes. Verify it
  against the artefact before anything depends on it: the file on disk, the tool's printed success line, the hash, the diff.
  The source project wrote this rule in its fourth phase and re-learned it in most of the later ones: agents reported matches
  the gate had not proven, a prototype survey's counts did not survive a byte check, a fresh session read a hand-off's summary
  as a conclusion, and "banked" was written from intent twice in one session. The same rule, applied to the project's own
  instruments, is the whole of the instruments group above.
- **When it applies:** every time work crosses a context boundary — agent to coordinator, session to session, summary to plan.
- **Cost:** false banks, false walls, a plan built on a count nobody had checked.
provenance: BFM R14 (verify recon/sub-agent summary counts against the bytes — a summarised signal is a claim), R66 (write "banked" only from the tool's printed line), the S82 coordinator that read prose results, the memory "verify blast radius, not just the defect"

### DK-69 — An instrument's blind spots: the tests that pass by construction
- **Kernel:** a check that cannot fail is not a check, and several common shapes cannot. A round-trip selftest of a
  partition or rewrite tool is a serialisation check, not a coverage check — it passes by construction when a missed item is
  absorbed into its neighbour's span, so every such tool needs an independent detector of items it failed to anchor. A set
  that gates work must be reconstructible from committed artifacts; a roster kept in ignored scratch is an unversioned oracle,
  silently wrong for anything it was not named after and blind after a fresh clone. A guard allowed to sit red and uncalled
  does not exist: its value is zero until it is green on the head commit and invoked by the standing report, and a docstring
  claiming it is wired is not wiring. A verification flag that short-circuits the tool's write path leaves the stale artifact
  in place and still exits zero. A status line a script prints unconditionally is not a measurement — derive every conclusion
  the script emits from the command's own output. A coverage instrument that infers its denominator from *open* work inverts
  at 100% (a complete map read as everything missing): carry the scanned denominator in the artifact and test the instrument
  at both endpoints. A metric that re-parses source is blind to a body banked through an include; trust the metric derived
  from the stub oracle. A name grep is not a "defined here" oracle — a declaration carrying the name reads as a definition.
  An annotator that writes into the text it reads must never treat its own output as evidence, and regex-extracted evidence
  needs a structural marker or prose becomes data.
- **When it applies:** every selftest, health line, coverage figure and "is it banked" query — at the moment it is written.
- **Cost:** a parser defect that survived eight sessions under a green selftest; a rename-drift failure undetected across two
  phases beside a red detector; a decision document nine days stale under a green flag.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase26.md:764 (Phase26 C1); phase-ends/logs/Phase26.md:742 (Phase26 C2); phase-ends/logs/Phase26.md:101 (Phase26 C3); phase-ends/logs/Phase29.md:2762 (Phase29-2of4 C1); phase-ends/logs/Phase29.md:7496 (Phase29-3of4 C5); phase-ends/logs/Phase33.md:126 (Phase33 C4); phase-ends/logs/Phase30.md:2589 (Phase30-1of2 C12); phase-ends/logs/Phase29.md:8080 (Phase29-4of4 C4); phase-ends/logs/Phase33.md:499 (Phase33 C5); phase-ends/logs/Phase33.md:503 (Phase33 C6)

### DK-70 — A verdict has three staleness axes, and the health suite asserts the work was done
- **Kernel:** a stored verdict can be stale because the DRAFT changed, because the BASELINE changed — or because the
  INSTRUMENT changed. When a tool is repaired, every verdict it produced becomes a hypothesis again; re-gate the drafts the
  repair's blast radius plausibly touched, scoped by that radius and never the whole ledger. A ledger row with no draft
  artifact is a rumour, not a result. Count agent completions from the run journal's result records, never from artifact
  existence — an agent writes its deliverable early and then iterates, so the file proves nothing. A clean-looking verdict
  that appears immediately after your own repair transform is a suspect, not a result: re-measure the artifact the transform
  produced before routing the residual. The aggregate check target is proven fail-closed before checks are added to it, and
  every audit oracle has a dependent that would notice its absence. The health suite asserts that a tool DID its work, not
  only that the data is intact: zero inputs, an impossible wall-clock and a missing persistent effect are each a defect. A
  health check that cannot finish is not a check — keep the health target sampled and fast, and put the exhaustive form behind
  its own name. Incremental gates never exercise the extraction step, so regeneration rot is undated and invisible for weeks —
  sweep it on a schedule. A validity stamp must be honoured by every downstream consumer, and a wrong write-side label cannot
  be repaired by a correct read key. Every status claim in an agent's context is expiry-checked against live state, or agents
  report it back as an observation.
- **When it applies:** after any tool repair; in every health target; in every ledger read by a fresh session.
- **Cost:** four byte-correct drafts banked unchanged a month late; a health target that had never completed; three agents
  reporting a red baseline that was a stale note in their pack.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase30.md:4660 (Phase30-2of2 C2); phase-ends/logs/Phase30.md:2481 (Phase30-1of2 C4); phase-ends/logs/Phase30.md:2352 (Phase30-1of2 C5); phase-ends/logs/Phase30.md:4001 (Phase30-2of2 C3); phase-ends/logs/Phase29.md:8207 (Phase29-4of4 C1); phase-ends/logs/Phase27.md:17 (Phase23-27 C6); phase-ends/logs/Phase31.md:5122 (Phase31-2of3 C1); phase-ends/logs/Phase31.md:5175 (Phase31-2of3 C2); phase-ends/logs/Phase31.md:6027 (Phase31-3of3 C6); phase-ends/logs/Phase31.md:2376 (Phase31-1of3 C10); phase-ends/logs/Phase31.md:5437 (Phase31-2of3 C9); phase-ends/logs/Phase31.md:5394 (Phase31-2of3 C8)

### DK-71 — What earns belief: applicability, independence, prediction, and the refusal as a finding
- **Kernel:** an oracle that can always be RUN is not always APPLICABLE — state the applicability precondition beside the
  recipe, or a coarse run returns a large number that reads as a verdict. "Independent" names the instrument, not the input:
  two refusals of two separately-written drafts from one tool is one test repeated. A diagnosis earns belief when it predicts
  its own residual membership, not when it explains the failures already seen. A defect reasoned into a sibling tool is latent
  until a run shows its signature; do not patch on theory right after that tool produced a clean run. A failure that will not
  reproduce earns a negative-control-proven detector, not a speculative fix — and every abort path proves its revert by diffing
  the worktree against a baseline captured at the start of the run. A derived claim outranks a heuristic verdict; when two
  heuristics disagree, take the union and queue the disagreements — under-reporting hides work, over-reporting only costs
  review. An instrument's refusal is a finding, not an obstacle: overriding it means explaining why the instrument is wrong,
  never finding another route. Read the first ten results of a long run before trusting the other hundreds, and
  negative-control any new refusal against everything that already succeeded. A refusal names the branch the caller entered,
  not the subject — make the applier consult the classifier it already has. Classify a harness fix as a logic defect or a
  path-reachability gap and price it accordingly; only the logic defect generalises. Re-verify a task's premise in the code at
  execution time — roadmap lines, audit findings and even an audit's own correction footer go stale, and the document that
  named a defect is usually the first to. A toolchain-version detector's verdict is a hypothesis until a placement count backs
  it; when a version stamp and a byte probe disagree, the probe wins and the refuted stamp is un-banked.
- **When it applies:** every diagnosis, every disagreement between two instruments, every premise inherited from a document.
- **Cost:** a "genuine codegen" verdict that was a size mismatch; a classifier verdict that overrode a hash match and
  understated a whole bucket; a version stamp banked for a phase against the bytes.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase29.md:7359 (Phase29-3of4 C3); phase-ends/logs/Phase31.md:3589 (Phase31-2of3 C3); phase-ends/logs/Phase29.md:3690 (Phase29-2of4 C2); phase-ends/logs/Phase29.md:1191 (Phase29-1of4 C4); phase-ends/logs/Phase30.md:4064 (Phase30-2of2 C5); phase-ends/logs/Phase30.md:4657 (Phase30-2of2 C4); phase-ends/logs/Phase30.md:1369 (Phase30-1of2 C1); phase-ends/logs/Phase30.md:250 (Phase30-1of2 C3); phase-ends/logs/Phase31.md:3346 (Phase31-2of3 C7); phase-ends/logs/Phase29.md:9957 (Phase29-4of4 C2); phase-ends/logs/Phase28.md:143 (Phase28-32 C3); phase-ends/logs/Phase10.md:44 (Phase8-13 C1)

### DK-72 — Denominators, units and labels — the number must say what it counts
- **Kernel:** a number that does not say what it counts will be read as the wrong thing. A stop/continue instrument
  aggregates at exactly the unit the decision is made in; one that averages a finer unit manufactures a false "we are at the
  floor". A reach-weighted gain (size × copies) is not a size — every figure says which of the two it is. Sibling count and
  never-drafted count are different denominators; conflating them overstates free leverage and hides that the remaining mass
  is singletons. A yield estimator that counts "unclaimed at the moment it runs" ranks correctly and over-projects absolutely;
  never plan off its absolute numbers. Do not cross-price two economies: a conversion rate measured on the residue queue does
  not price a fresh wave. When two blockers are orthogonal, a classifier's if-chain order silently becomes the label —
  cross-tabulate, never bucket. Measure what fraction of a cycle a parallelism knob can actually touch before adopting it. A
  milestone counted in matched functions excludes the splitter's auto-generated empty bodies, defined at the moment the bar
  is set. A duplicate census run before the vendor library is linked out is contaminated — the groups are library fragments
  and epilogues. The file a function lives in is not evidence of its class; read the recorded attribute, never the hosting
  split. Keep a glossary line for any term two documents use in opposite senses. Say which currency a wave buys — percentage
  or idioms — before launching it, and judge it in that currency; and a class-distribution assessor only sees the population
  already attempted, so "analyse all remaining work" is a cheap triage pass, not a static analysis.
- **When it applies:** every plan figure, every ledger column, every verdict of "at the floor".
- **Cost:** a phase nearly closed on an artifact of the wrong unit; a leverage estimate three times too high; a thirty-fold
  mis-scope risk from one term meaning two things.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase29.md:1283 (Phase29-1of4 C1); phase-ends/logs/Phase29.md:4775 (Phase29-2of4 C6); phase-ends/logs/Phase31.md:298 (Phase31-1of3 C6); phase-ends/logs/Phase29.md:9350 (Phase29-4of4 C5); phase-ends/logs/Phase30.md:899 (Phase30-1of2 C10); phase-ends/logs/Phase29.md:4958 (Phase29-2of4 C4); phase-ends/logs/Phase29.md:6115 (Phase29-3of4 C6); phase-ends/logs/Phase7.md:12 (Phase7 C2); phase-ends/logs/Phase7.md:26 (Phase7 C3); phase-ends/logs/Phase28.md:182 (Phase28-32 C2); phase-ends/logs/Phase30.md:1343 (Phase30-1of2 C13); phase-ends/logs/Phase21.md:475 (Phase21 C3); phase-ends/logs/Phase21.md:63 (Phase21 C2)

### DK-73 — Leverage is not tractability; scope a campaign by verdicts, invariants and kill criteria
- **Kernel:** the most-duplicated functions are systematically the hardest — leverage and tractability are
  anti-correlated — so a leverage-first queue front-loads hand-tier work, and its early bank rate is not a harness fault.
  Carry a measured closeness read per target and never let reach × size stand in for "crackable"; the reach ranking finds the
  most-DONE work first, so derive the target pool from the build's own invariant. Yield clusters by binary, not across the
  fleet — draw per binary once two independent lanes concentrate in the same place. A cracked idiom transfers within its
  family and not across it: price a lane by families, not by class size. An open-ended grind phase's milestone is invariants
  held plus a clean checkpoint, never a percentage; a research phase is scoped by a per-class verdict (a validated lever or a
  falsifiable wall verdict per class), not by a percentage either. Write numeric kill criteria into the plan before the data
  exists, and let them fire. Measure a pipeline's yield on the residual, not on solved functions: a known-answer ladder (revert
  a match to a stub, make the pipeline re-derive it) sets the ceiling, and the gap to the unmatched tail is the real number.
  Declare a mechanical lever spent only on a positive, three-part measurement — every built lever applied and returning zero,
  the residue split by structure, and the decay curve priced against what remains. Sequence a phase so the cheapest thing that
  can invalidate everything below it runs first; when a foundation task hits a structural wall mid-phase, bank the tractable
  wins and re-scope the wall as its own sub-project. Inside one leverage class, schedule by measured remaining effort and pull
  the payoff-dominating outlier out for an immediate cheap triage. Choose the exemplar for cracking a codegen class by the
  size of its residual: the one-instruction mismatches are the cleanest real-function isolates.
- **When it applies:** the draw, the phase plan, the campaign's close.
- **Cost:** a phase priced by percentage that could only be closed by verdicts; a mega-leverage "freebie" that was a
  stack-switcher; a lane priced by class that cost forty turns of learning per family.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase17.md:247 (Phase17-18 C1); phase-ends/logs/Phase25.md:473 (Phase25 C1); phase-ends/logs/Phase30.md:1810 (Phase30-1of2 C11); phase-ends/logs/Phase31.md:5040 (Phase31-2of3 C10); phase-ends/logs/Phase31.md:1300 (Phase31-1of3 C5); phase-ends/logs/Phase19.md:24 (Phase19-20-22 C1); phase-ends/logs/Phase18.md:93 (Phase17-18 C6); phase-ends/logs/Phase16.md:24 (Phase15-16 C5); phase-ends/logs/Phase16.md:36 (Phase15-16 C1); phase-ends/logs/Phase29.md:10300 (Phase29-4of4 C6); phase-ends/logs/Phase29.md:4322 (Phase29-2of4 C5); phase-ends/logs/Phase7.md:3 (Phase7 C5); phase-ends/logs/Phase24.md:29 (Phase24 C2); phase-ends/logs/Phase20.md:14 (Phase19-20-22 C2)

### DK-74 — Models and prompts: targeted context, named degenerate outputs, two-sided caps, tiers by what they can learn
- **Kernel:** give a drafting model a targeted slice of the knowledge base, never the whole — full context measurably made
  a model worse. Name the degenerate output in the prompt: an empty body compiles, so "translate every instruction, never an
  empty body" is a required instruction. The output-token cap is a two-sided knob and both failure modes read as "the model is
  bad"; more budget is not more quality — measure it as a paired A/B and treat truncation as recoverable, not as a defect
  signal. When A/B-ing any harness knob, ship a positive control that the knob actually moved. Mine new idioms from fresh
  cracks, never from the failed backlog — the failure pile re-teaches what you already know — while the harvest SELECTOR must
  still be able to see failed attempts, or it learns from the easy half. Escalations to the expensive tier run strictly serial
  with idiom-banking between them; only the tier that cannot learn is run in parallel. The wall-breaker tier is a match tier,
  not a plumbing tier: work a deterministic arbiter can judge does not need the expensive model. Accelerate the stage that is
  the bottleneck — a byte-exact search loop costs a compile plus a whole-binary gate per candidate, so hardware brute force
  buys nothing. Make the drafter run the pre-gate guard and return the NAMED banking prerequisite; a batch of diagnosed
  candidates is worth more than a batch of opaque matches. Before concluding a pipeline is weak, histogram the compiler's
  error text: most failures were one missing declaration, fixed once. Keep prompt and law text in data, never inside the
  launcher's source template.
- **When it applies:** the pack builder, the routing table, every model experiment.
- **Cost:** a local model made worse by more context; eight diagnosed matches revealing one lever the opaque batch had
  hidden; a wave killed at launch by a quote character inside a template.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase23.md:24 (Phase23-27 C2); phase-ends/logs/Phase23.md:91 (Phase23-27 C3); phase-ends/logs/Phase23.md:54 (Phase23-27 C4); phase-ends/logs/Phase31.md:2292 (Phase31-1of3 C1); phase-ends/logs/Phase30.md:1541 (Phase30-1of2 C8); phase-ends/logs/Phase23.md:93 (Phase23-27 C1); phase-ends/logs/Phase31.md:3236 (Phase31-2of3 C6); phase-ends/logs/Phase24.md:57 (Phase24 C1); phase-ends/logs/Phase24.md:61 (Phase24 C3); phase-ends/logs/Phase17.md:96 (Phase17-18 C4); phase-ends/logs/Phase29.md:5093 (Phase29-2of4 C3); phase-ends/logs/Phase16.md:40 (Phase15-16 C3); phase-ends/logs/Phase31.md:1702 (Phase31-1of3 C12)

### DK-75 — The unattended run: a crash is a pause, a stop is a file, a limit is an epoch
- **Kernel:** build the unattended campaign so a crash is a pause — probe the dependency at the top of each cycle, commit
  per cycle, persist the tried-set and each confirmed result the moment it is confirmed; a long stateless batch that writes
  only at the end loses everything to a kill. Design it for a human with no agent session: a STOP file honoured at a safe
  boundary, a supervisor that tells a clean exit from a crash, a status one-liner, and crash-resume proven by a deliberate kill
  before the first real run. Never wrap a project tool in a timeout shorter than its own budget — you pre-empt its recovery
  handler and lose its buffered output. Sweep for orphaned worker processes at every session boundary: a dead-pipe compiler
  holds a core forever and nothing reports it, and a harness's low-memory guard silently kills long background jobs. A run
  that looks throttled is usually blocked on an interactive approval prompt — check the pending prompt before diagnosing the
  provider. Batch size is a risk lever, not a token lever: isolated agents cost about N times one agent whether concurrent or
  serial, so size a batch by the unverified spend you are willing to lose before the next measurement. A repair mode whose
  cost is exceptions × population is gated on a measured exception count; for a broadly divergent set, drop rather than
  recover. A free or preview model tier can be withdrawn mid-campaign without notice — a fleet-wide 404 is an epoch event, not
  N model failures — and a metered key's own cap is a separate limit from the account's credit. In a pipelined
  drafter/gater, "still open" is not "not yet attempted": consecutive waves re-drafted the wave still in flight. A fan-out
  script generated by an orchestrator runs sandboxed without the repository: it is self-contained, so target selection
  belongs to the generator, not the workers.
- **When it applies:** every lane that runs while nobody watches.
- **Cost:** a thirteen-hour orphaned compiler; three gates with no verdict and half-applied propagations from one timeout;
  a six-hour "throttle" that was a permission prompt.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase23.md:92 (Phase23-27 C5); phase-ends/logs/Phase16.md:89 (Phase15-16 C6); phase-ends/logs/Phase31.md:7121 (Phase31-3of3 C4); phase-ends/logs/Phase31.md:7024 (Phase31-3of3 C1); phase-ends/logs/Phase29.md:1029 (Phase29-1of4 C5); phase-ends/logs/Phase33.md:508 (Phase33 C15); phase-ends/logs/Phase21.md:731 (Phase21 C1); phase-ends/logs/Phase29.md:2387 (Phase29-1of4 C2); phase-ends/logs/Phase29.md:1635 (Phase29-1of4 C3); phase-ends/logs/Phase31.md:2319 (Phase31-1of3 C8); phase-ends/logs/Phase31.md:2380 (Phase31-1of3 C9); phase-ends/logs/Phase31.md:258 (Phase31-1of3 C2); phase-ends/logs/Phase25.md:487 (Phase25 C2)

### DK-76 — Agents and the tree: write-isolation is architecture, never a sentence in a prompt
- **Kernel:** drafting agents must never be ABLE to write the build tree; every agent artifact lands in a scratch directory,
  so a killed or racing campaign costs build cycles and zero paid work. "Never modify the source tree" in a prompt is a
  request, not an enforcement — snapshot the tree status around every agent and name the offender. Never adopt a subagent's
  worktree wholesale: it is a snapshot of an older tree and may predate a bank; re-gate its artifacts against the head. The
  generated disassembly tree is shared mutable state — a fleet verify/clean chain and the per-function instruments cannot run
  at the same time. A probe that splices the tree in order to measure it must restore it, or the progress oracle counts the
  splices as banks. Snapshot every target's disassembly before gating: a successful bank prunes it, and harvest and recovery
  need both sides. Never let model-authored prose reach the shell inside double quotes — a backticked command in a commit
  message executed; use a quoted heredoc. Keep the wave harness in the repository with its contracts; a harness rebuilt from
  memory each run silently goes stale. A `cd` in one agent shell call persists into the next. Never test a helper by importing
  its module: a tool with no main guard runs its whole pipeline on import.
- **When it applies:** the day the first agent is launched, as architecture; then every wave.
- **Cost:** two tree corruptions recovered with one checkout only because the drafts lived outside the tree; a real extract
  run by a commit message; a download landing inside a submodule.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase30.md:4017 (Phase30-2of2 C1); phase-ends/logs/Phase31.md:2879 (Phase31-1of3 C7); phase-ends/logs/Phase31.md:2879 (Phase31-2of3 C4); phase-ends/logs/Phase30.md:449 (Phase30-1of2 C2); phase-ends/logs/Phase31.md:6808 (Phase31-3of3 C7); phase-ends/logs/Phase32.md:255 (Phase28-32 C6); phase-ends/logs/Phase31.md:2598 (Phase31-1of3 C11); phase-ends/logs/Phase31.md:1612 (Phase31-1of3 C3); phase-ends/logs/Phase30.md:2893 (Phase30-2of2 C6); phase-ends/logs/Phase30.md:688 (Phase30-1of2 C9); phase-ends/logs/Phase33.md:660 (Phase33 C16); phase-ends/logs/Phase30.md:2163 (Phase30-1of2 C7)

### DK-77 — Edits that keep their proofs: repair the caller, land changes separately, draft before you carve
- **Kernel:** when a byte-proven body will not integrate, the repair moves the CALLER's declaration to the definition's
  signature — never the definition to the caller's — and only where the change is width-compatible. A repair ladder probes
  whether each stage is needed before applying it, or it silently escalates a binary-local bank into a fleet-shared edit. Land
  a pure rename and a semantic or layout change as separate gated edits, so a gate failure attributes itself. Draft first,
  then carve: a build-unit split is safe only when the new unit is immediately populated with proven bodies. A proven
  transform that is not a rung of the ladder the drafts actually pass through does not exist for those drafts. Re-run the
  deterministic declaration canonicaliser over old quarantined drafts after every large bank — recovery odds rise as the
  banked corpus grows and the pile costs nothing to keep. An idempotency guard keyed on presence freezes every record created
  before the system matured; key it on completeness, and make regenerated artifacts idempotent by replacement, never by
  skipping. A hard-coded assumption fixed in one tool survives in its siblings: grep the tree for the literal and fix every
  twin in the same change. Before a fleet-wide mechanical edit, census the whole population for the exact preconditions the
  edit assumes — uniformity is the licence, non-uniformity the design input. A batch gate that bisects on failure re-runs the
  singleton against an unchanged baseline: special-case one, or pay a duplicate build on the hot path. A byte-identical
  baseline is proven only when the whole gate is green from clean across several independent sessions. A build-system
  conditional that expands at parse time makes its own negative control vacuous. Never round-trip a curated configuration
  through a serializer: every oracle you own measures bytes, so a formatting-destructive write is invisible to all of them.
- **When it applies:** every integration repair, every carve, every fleet-wide edit.
- **Cost:** a registry's forty-seven comment lines destroyed under green gates; a fleet edit taken by a bank that needed a
  local one; a duplicate build on every single-draft gate.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase24.md:119 (Phase24 C4); phase-ends/logs/Phase29.md:3377 (Phase29-2of4 C7); phase-ends/logs/Phase29.md:1959 (Phase29-1of4 C6); phase-ends/logs/Phase31.md:922 (Phase31-1of3 C4); phase-ends/logs/Phase31.md:3810 (Phase31-2of3 C5); phase-ends/logs/Phase15.md:57 (Phase15-16 C4); phase-ends/logs/Phase15.md:51 (Phase15-16 C8); phase-ends/logs/Phase31.md:6171 (Phase31-3of3 C5); phase-ends/logs/Phase28.md:36 (Phase28-32 C4); phase-ends/logs/Phase29.md:7520 (Phase29-3of4 C4); phase-ends/logs/Phase28.md:58 (Phase28-32 C5); phase-ends/logs/Phase7.md:75 (Phase7 C4); phase-ends/logs/Phase31.md:5155 (Phase31-2of3 C11); phase-ends/logs/Phase28.md:181 (Phase28-32 C1)

### DK-78 — The search harness and the compiler as evidence: same context, own corpus, a sibling's silence proves nothing
- **Kernel:** a search harness must compile in the SAME declaration context as the real build; an isolated context does not
  merely fail to verify, it makes the search converge on the wrong answer. The search unit is the C expression — it cannot
  freeze the instructions already right, because register allocation couples them. A decompiler's "unaffected register"
  output means it decompiled one entry path of a multi-entry function and handed you a fragment: an instrument limit, never
  evidence the function is hard. Check group identity from the signature files before probing a family — if the members are
  structurally identical, a zero result is a compile-error certainty, not evidence about codegen. Vendor compiler sources
  carry form-feed page separators, which a scripting language's line splitter honours and grep does not, so a line-number
  checker over the source drifts and blames the wrong line. Your own corpus of byte matches is an experiment already run on
  the toolchain: settle "is my rebuilt compiler faithful?" from it before installing the original vendor tools. Another
  project's unmatched stubs are a record of what they did not crack, never proof that a class is uncrackable —
  cross-project corroboration multiplies confidence in a wrong verdict as readily as a right one. Histogram a secondary
  binary's call targets by address range before assuming it carries its own copy of anything; a raw blob's load address is a
  hypothesis whose free confirmation is arithmetic against the next known segment's base. A relocation-interleaved
  disassembly is produced only for object files; a linked image lists relocations separately with a shifted address column.
- **When it applies:** the permuter's base file, the first probe of any family, every cross-project citation.
- **Cost:** an overnight run that "closed" forty per cent of its near-misses and gated zero; a class written off on a
  neighbour's silence.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase16.md:71 (Phase15-16 C2); phase-ends/logs/Phase16.md:43 (Phase15-16 C7); phase-ends/logs/Phase7.md:109 (Phase7 C1); phase-ends/logs/Phase30.md:168 (Phase30-1of2 C6); phase-ends/logs/Phase29.md:6915 (Phase29-3of4 C1); phase-ends/logs/Phase18.md:64 (Phase17-18 C3); phase-ends/logs/Phase18.md:52 (Phase17-18 C2); phase-ends/logs/Phase12.md:45 (Phase8-13 C2); phase-ends/logs/Phase10.md:13 (Phase8-13 C3); phase-ends/logs/Phase33.md:526 (Phase33 C7)

### DK-79 — Maintaining the knowledge base and the record: contradictions are work items, edits are verified by section
- **Kernel:** a contradiction between two entries of your own knowledge base is a work item, not noise — replay the levers
  already written down, under the correct oracle, before commissioning new research. A wrong prescription left in the base is
  worse than no entry: when evidence refutes an entry, correct that entry in place, in the same session, carrying the
  refutation. A document that cites a repository path is an untested claim about the repository — lint it. A programmatic
  edit to a long-lived knowledge document silently truncates or duplicates it; verify the sections, never the commit. The
  live hand-off block is strictly appended at the end of its file — file order is the only recency signal a fresh session
  has. Never restructure a proven tool with blind string replaces at the end of a long session; specify it as the next
  session's first task. A miner over your own records finds only what its pattern anticipates — measure the widened pattern's
  yield. Assert that the work ledger partitions the live work, and treat a row the invariant refutes as a lie a fresh session
  will act on. Write the phase synthesis in a fresh session that re-reads the committed state cold; the cold read is what
  catches stale artifacts. A derive-then-apply pipeline over a live repository needs a freshness guard and a stated sequencing
  law.
- **When it applies:** every harvest, every close, every programmatic edit of a document that outlives the session.
- **Cost:** a cookbook section silently deleted for a session; a day-older hand-off read as the live one; a class re-researched
  because two entries disagreed and nobody replayed either.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase18.md:26 (Phase17-18 C5); phase-ends/logs/Phase29.md:9029 (Phase29-4of4 C3); phase-ends/logs/Phase27.md:71 (Phase23-27 C7); phase-ends/logs/Phase31.md:6529 (Phase31-3of3 C2); phase-ends/logs/Phase31.md:6126 (Phase31-3of3 C3); phase-ends/logs/Phase29.md:6134 (Phase29-3of4 C2); phase-ends/logs/Phase33.md:429 (Phase33 C14); phase-ends/logs/Phase27.md:45 (Phase23-27 C8); phase-ends/logs/Phase28.md:86 (Phase28-32 C7); phase-ends/logs/Phase33.md:285 (Phase33 C8)

### DK-80 — Hosts and services: the small facts that each cost an hour
- **Kernel:** small facts about hosts and services, each learned at the cost of an hour. `git check-ignore` is silent for
  tracked paths, so an ignore-coverage audit run before the untracking passes vacuously — use its no-index form. A
  content-hash "no forbidden bytes" audit collides on zero-length files. A mirror push does not push the stash ref. Route a
  host purge request through the flow that actually exists; the obvious form is a trap. A host feature can be gated on the
  very flip it was meant to precede — read the settings page, do not infer. A public scratch service's compiler image is not
  your pinned toolchain; rebuild it locally and prove byte-identity before asking for a preset. A disassembler's script
  directory compiles as one bundle, so a single non-compiling script disables every script in it and the error names a
  working one. The same tool refuses a project path containing a component that starts with a dot, so a scratch project
  cannot live under a dot-directory. Run reference-compiler dump passes from a scratch working directory, or the dumps land
  in the repository root and later read as committed artifacts.
- **When it applies:** the first time each host or service is touched.
- **Cost:** an hour each, and one flip-gate misread.
provenance: BFM phase-log mining pass (P33.5 task 14.5, S92; the accelerators entry "P33.5 S92"): phase-ends/logs/Phase33.md:236 (Phase33 C3); phase-ends/logs/Phase33.md:205 (Phase33 C9); phase-ends/logs/Phase33.md:295 (Phase33 C10); phase-ends/logs/Phase33.md:635 (Phase33 C11); phase-ends/logs/Phase33.md:692 (Phase33 C12); phase-ends/logs/Phase33.md:645 (Phase33 C13); phase-ends/logs/Phase33.md:186 (Phase33 C1); phase-ends/logs/Phase33.md:185 (Phase33 C2); phase-ends/logs/Phase25.md:337 (Phase25 C3)

### DK-81 — The flip day: a third-party step is proven through the third party's toolchain, and the public tree is decided before the flip
- **Kernel:** four small facts from the day a private decomp went public. (1) A step that hands a file to a third party — a
  scratch on a public diff service, a preset request — is proven through that party's OWN toolchain, on the file itself, before
  the owner's browser session, and the proving tool writes the paste: a listing that exists only as a comparison oracle (bare
  register names resolved by a local include, absolute branch targets) will not assemble anywhere else. (2) Decide what a
  public tree carries before the flip: sent outreach drafts and a reviewed document archive were always going to leave, and
  deciding after cost two untrack commits on a public history; an archive index that names files as paths, never links, is what
  made the removal harmless. (3) A calendar gate — a host's purge ticket — is read the morning after it is filed, not "daily for
  a week"; it passed in one day. (4) A scratch prune is an instrument change: every tool that writes under a pruned tree is re-run
  before the prune is called done — one audit's probe directory went with the prune and its bare `except` turned a refusal into a
  verdict, which read as four parser defects.
- **When it applies:** the flip and the outward actions around it; any prune of scratch a health check writes under.
- **Cost:** one failed browser step, two extra commits on a public history, one red health chain diagnosed twice.
provenance: BFM Phase 34 (S93, 2026-09-08; the accelerators entry "P34 S93"): docs/decision-log.md "P34 S93 — the flip";
the Phase-34 worklog (phase-ends/logs/Phase34.md after the close: task 2 part 1, task 7 parts 1–2, task 8 part 1).

---

## 9. The failure museum, condensed — what looked right at the time

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
- **Added by the coverage pass:** DK-66 … DK-68 — 3 kernels.
- **Added by the log-mining pass:** DK-69 … DK-80 — 12 kernels (143 worklog lessons, clustered).
- **In all:** DK-1 … DK-80 — 80 kernels (the installer's check compares `grep -c '^### DK-'` against this figure).
- **The failure museum:** 37 exhibits, condensed.
- Conduct rules are not duplicated here; they are the registry seed's E.7 group. The generic engineering kernels of
  ProjectArchitect's own corpus apply unchanged and are not repeated.
