<!-- decomp-architect: the registry §E seed for a matching decompilation.
     The kit's installer (SETUP.md, Step 7) appends this file's body VERBATIM under the project's RULES_REGISTRY.md §E,
     inside a marked section, numbered G1…G67 by construction: the intake document asks ProjectArchitect's generation
     step to leave §E empty except a one-line pointer, and Step 7 asserts that before appending (if §E already holds
     rules, Step 7's fallback renumbers this block by the offset and records the offset in the section header).
     Every rule below is distilled from a finished, byte-identical decompilation; the `provenance:` line names the
     source rule and the incident that earned it. Rules here are NORMS OF CONDUCT; techniques go to the cookbook. -->

## §E — Project-specific rules (a matching decompilation) — installed by decomp-architect, Phase 0.5

*The domain ground-truth rules for a matching decompilation: the two oracles, the byte gate that is the only definition of
done (the concrete instance of M1 and P9), the ROM firewall, the discipline that keeps the project's own instruments
honest, the campaign rules, the compiler-wall rules, the publishing rules, and the conduct rules for using AI. Each entry
carries a `provenance:` line naming the source project's rule and the failure that earned it. Recited in full every
session with the rest of this registry.*

### E.1 — The oracles and the gate

### G1 — Two oracles; guess neither
The disassembler database is the static oracle and the emulator is the runtime oracle. Every claim about code behaviour, an
address, a calling convention or a data layout is validated against one of them — never speculated from general knowledge
of the hardware or the game. The two answer different questions: the database gives shape, the running game gives meaning.
provenance: BFM G1 (constitution 2026-06-10); the "script VM" that did not exist (PhaseEnd 12)

### G2 — Oracle precondition
Before any reverse-engineering task, verify the disassembler's server with one cheap call. If it is down, stop and ask the
developer to start it; never proceed on cached assumptions. After a restart or a program switch, pause and ask the developer
to reconnect the client — the agent cannot.
provenance: BFM G2 + R29

### G3 — A match is byte-for-byte, and the whole binary still hashes
A function is matched only when its compiled output is instruction-identical to the original, register allocation included,
AND the whole-binary hash check stays green with it linked. "Functionally equivalent" is never done. The hash check runs
inside every build; there is no third state between "identical" and "failed".
provenance: BFM G3 + the per-build SHA1 contract (Phase 5)

### G4 — No unmatched C in a default build
Logically-correct-but-unmatched C lives under a NON_MATCHING guard with the assembly stub remaining in the default build.
The census of open functions reads from the source, and a default build never links non-matching C.
provenance: BFM G4

### G5 — Address provenance and region tags
Every symbol or address imported from outside the project's own oracles (community research, cheat tables, wikis, forums)
is recorded in the address ledger with its source, its region or version, and its verification status. An address valid
for one version is never assumed valid for another; an overlay-region address is never treated as a static symbol until
the load map says so. A live-memory finding is verified only with three or more consistent datapoints or a controlled
before/after diff; two-datapoint matches stay candidates.
provenance: BFM G5 + R10 + R13

### G6 — Never rename blind
A symbol is renamed only after checking every cross-reference and every configuration or symbol file that mentions it.
Renames happen in the curated symbol file and in the disassembler database (mirrored by script, never trusted to a
client-side rename) — never by hand-editing generated assembly. The curated symbol file is re-merged carefully, never
blindly overwritten; every name in it is a valid assembler and C identifier.
provenance: BFM G6 + R15 + the MCP renames that did not persist (S78)

### G7 — Duplicates first
Before matching a function, check the duplicate report. A duplicate is matched once and shared through a header and
per-binary symbol addresses. A newly discovered binary is not real until every consumer knows it (the signature set, the
family map, the dedup registry, the shared header, the reports) — asserted by a gate, not remembered.
provenance: BFM G7 + R36

### G8 — Compiler honesty
The compiler, assembler and flags are pinned by fingerprint evidence from the binary itself and recorded with that evidence.
The assembler's version or compatibility flag is always passed explicitly — a tool's default is not "latest". Never import
another project's toolchain settings without evidence; expect per-module variation (mixed optimisation levels, mixed
compilers within one image). Each binary's toolchain provenance is recorded separately.
provenance: BFM G8 + R24 + the mandatory division-expansion flag found only by the probe ladder (Phase 6)

### G9 — Decisive verification is a clean rebuild
A byte-match is verified from a clean rebuild (`clean → extract → build`), never from an incremental build; a reverted
configuration needs a re-extract, not just a re-check. A binary whose extraction rewrites the linker script is gated only by
a clean rebuild. A build is verified by its exit code, never by its output file — a failed build leaves the previous binary in
place.
provenance: BFM R22 + R53 + the "linker defect" that was an incremental gate (P31 S52/S71)

### G10 — A standalone match is not a bank
Every "it matches" claim names the compilation it survived: standalone with relocations masked (proves the body's shape),
the real translation unit (proves the body in its declaration context), or the whole-binary rebuild (proves everything).
An isolated oracle's output is a gate-first candidate, never a bank; before calling a class dead, drive the integration
chain (declaration sync, callee casts, the real-TU probe, the gate) to a byte verdict.
provenance: BFM accelerators #16/#18 (P31 S69); "32 free banks waiting" that gated 0 of 28

### G11 — Pasted assembly is a verbatim, not a bank
A "C" body that is the original assembly inside an inline-assembly block is a verbatim, not a match; a ledger's best draft
may never be one; the manifest of genuinely hand-written routines is censused from evidence (the vendor's symbol tables,
the original's own hand-assembly), and a strict verbatim check runs in every per-bank close. The byte gate is a null oracle
for "is this C?".
provenance: BFM R62 (S79 #7, one fake bank; 199 such bodies found, reduced to 5)

### E.2 — The ROM firewall

### G12 — No game-derived bytes in any tracked or published artifact, from the first commit
Nothing derived from the game enters git — the dump, extracted payloads, generated disassembly, assets, build output,
memory images, the reverse-engineering database, the vendor SDK, transcripts that quote disassembly, training data derived
from the target, and any text file that pastes the target's instructions. Symbol names, addresses, hashes, configuration
and the decompiled C are what a decompilation publishes. There is no private-repository exemption: the source project
relaxed this rule while private and paid for it with a full-history rewrite of four thousand commits.
provenance: BFM H1 + R74; the R1 relaxation and its bill (P33 C1–C9)

### G13 — The audit derives its forbidden set and asserts its own coverage
The repository audit refuses any tracked file under a purged path; any tracked file whose hash appears in the forbidden set
— derived from the extraction manifest, the per-binary contracts and the medium's own hash, never a typed list; anything
over the host's size threshold; and any text file with a long contiguous run of disassembly-shaped lines. It fails on a
missing required source rather than passing vacuously, refuses a rule it cannot interpret, prints every count with its
denominator, has a planted-fixture negative control it must fail on before it is trusted, and runs in CI on every push.
provenance: BFM `audit_public.py` (P33 B9, P33.5 task 8); the two disassembly listings a path-and-hash audit could not see

### G14 — Rehearse every irreversible repository operation
A history rewrite, a purge, a force-push or a mass move is rehearsed on a scratch copy first and proven pair by pair with
POSITIVE assertions (every purged path absent AND every kept file identical AND the pruned set equal to the derived set),
never with absences alone.
provenance: BFM R76; trial rewrite #1's empty-blob strip-list defect

### G15 — A linked worktree's HEAD is a ref
Audit `git worktree list` before any garbage collection or purge; forgotten worktrees pin the history they were created from.
provenance: BFM R77; twelve stale worktrees pinned 3,729 old commits through a gc

### G16 — A probe or guard never writes into the repository it guards
A "read-only" check that fetches, clones or builds does so in a throwaway; a successful fetch of an old object imports its
whole closure. An instrument's own write path is part of the instrument.
provenance: BFM R81 + R57; the purge probe that re-imported the purged history on every run

### G17 — A rewritten history is not private until the host has purged the objects
The host's own metadata (an activity view, event feeds, pull-request refs) publishes every pre-force-push tip, and each
still serves the old tree. A visibility flip is gated on a probe of the old object ids — or on recreating the repository —
never on a clean working tree.
provenance: BFM R82; 157 activity rows still serving the executable after the force-push

### G18 — Never `git clean -x` where irreplaceable data is ignored-but-present
The dump, the memory images, the reverse-engineering database and the SDK live on the maintainer's disk under ignored
paths; a `-x` clean deletes them. The backup is the text export of the database, the checksum files and a private archive
repository — not the ignored directories.
provenance: BFM R78 (the CLAUDE.md fail-safe since the rewrite)

### E.3 — Instruments

### G19 — Assert your coverage
A scanner compares what it found against an over-approximating candidate set and fails on the gap. A silent skip is a
defect, and a loud failure nobody counts is exactly as invisible. A tool that cannot answer refuses; it never returns an
empty set that reads as "nothing left".
provenance: BFM R32 + R43; seven silent-skip defects in one audit (Phase 26); a scanner that reported the decomp complete

### G20 — Derive, don't re-derive
Where a proven invariant answers a question, derive the answer from it rather than re-parsing the world; a metric derived
from the build's own link map beats one that re-scans the source. The best outcome of a tooling review is a deleted scanner.
provenance: BFM R33; the main-executable denominator that was 3,616 words short until derived from the link map

### G21 — A second, DISAGREEING oracle — on a schedule
When an oracle is structurally blind to an error class, the fix is a second independent oracle that must agree, not a
better assertion in the first. From day one a standing harness runs the same question down two independent paths (matched?
compiles? fleet green? scanner coverage? agent produced work? bankable?) on a schedule and fails loudly on disagreement.
provenance: BFM R34 + accelerator #15; ten blockers in one session, every one caught only by a disagreement

### G22 — Fix the instrument before trusting its measurement
A number from a broken tool and the same number from a fixed tool are opposite facts. Tool integrity is a precondition of a
measurement, not a parallel concern; a probe from a broken tool is not evidence.
provenance: BFM R35; "families bank at 0%" (a missing build step) that steered two phases, then measured 89%

### G23 — Probe before costing
Ground every estimate or attribution on ONE instance; derive counts from the corpus oracle; diff the artifact to prove an
edit actually ran before judging the lever it carried. A "0 banked across a class" is read on one placed candidate's raw
compiler output before it is called a wall.
provenance: BFM R37; the def-side "wall" that was one declaration conflict

### G24 — Read the recorded verdicts before designing an experiment
Failure classifications, gate results and agent journals already on disk are read before any new probe; the answer is
frequently already recorded, and the next agent on an item is handed every earlier attempt on it.
provenance: BFM R38; the journals written for thirty phases and read in the thirty-first

### G25 — Negative-control every new refusal-check
Every new refusal, filter or pre-check is run over the population that ALREADY SUCCEEDED before it ships; zero false
positives is the bar. A refusal-check is measured against what the real pipeline does to the input, not against a model
of it.
provenance: BFM R39; a pre-check's control over 205 banked drafts caught two bugs in the check itself

### G26 — Exonerate the instrument before blaming the subject
Truncation, fences, rate limits, tool faults and environment gaps are ruled out before a failure is attributed to a draft, a
model or the compiler. A verdict produced in an isolated environment (a worktree, a sandbox) describes the environment
until that environment is proven complete for the class of work it judged.
provenance: BFM R40 + accelerator #19; seven false model verdicts in one session; a whole verdict class that was a missing gitignored input

### G27 — Every number ships with its denominator
Every cost, rate, yield and effort estimate states what it is a fraction of; a headline percentage ships its remainder,
reconciled against an independently derived list of what is actually open; a claim's TYPE (byte-stream containment,
compiled standalone, whole-binary) is stated with the number.
provenance: BFM R41 + accelerator S78 (2); a 59.8% that carried 31,000 linked-library instructions in its denominator for six weeks

### G28 — Refuse unsupported input; a helper refuses an empty work list
A tool must refuse an input it cannot handle, loudly, naming the tool that can — never process it wrongly. A helper given an
empty list refuses rather than building the unchanged tree and exiting zero.
provenance: BFM R43 + R68; a gater that accepted a binary class it could not gate (105 cards, 0 banked); the no-op bank helper

### G29 — A soft error inside a success envelope is that error
An HTTP 200 carrying an error code, a non-zero return read as "no binary", an import that prints failures under a "proof
passed" banner — each is the error it carries. Verify a build from its exit code.
provenance: BFM R49 + R53

### G30 — A guard that is downstream, or not running, is not a guard; unattended lanes leave evidence
A check that sits below the failure it should stop is not a guard; a guard that predates the process it should stop is not
running. A lane that runs unattended leaves progress evidence (an empty log and no process means it never started); a
number that will decide something is written to a file another process can read at any moment.
provenance: BFM R54 + R55; the harness wounds of P31 S58

### G31 — A derived property stored as configuration goes stale
A value that can be derived from the artifacts (a pad, a boundary, a linked set) is derived on every run or given a
byte-proven self-repair; stored, it goes stale and takes a binary with it.
provenance: BFM R51; three red binaries in one day from a cached pad table

### G32 — Check against a known-true case first
Every scan, join, census, similarity band and verdict is tested on one case whose answer is already known before its
output is reported. An exactly-zero result is a decoder gap until the scanner reproduces a hand-checked positive.
provenance: BFM memory "check against a known-true case" + accelerator A5; five of one session's biggest findings were artifacts of the instrument

### G33 — A verdict names its instrument; never re-implement a gate you have
A negative verdict records which tool produced it; a one-off script never stands in for the real gate (it skips the real
gate's pre-checks and mints false walls).
provenance: BFM memory "a verdict names its instrument"; eleven "proven gate-rejects" that were one missing data carve

### G34 — Measure the steady state; report every lane
A metric is bucketed over time before it is called a ceiling — launch bursts and startup memory both fake hard limits. A
status check covers every lane with its own metrics, and a lane banking far below the rest is a harness fault until proven
otherwise.
provenance: BFM memories "measure the steady state" + "report every lane" + "lane blockers are harness"; three for three

### G35 — Distinguish "judged and failed" from "not judged"
Every loop or judging tool has a distinct not-judged state; a tool that reports "unchanged" for N cycles proves it iterated;
a judging tool models what the gate will do to the draft before it judges.
provenance: BFM R61; a permuter that had never run on a whole class while printing "unchanged"

### G36 — A score is not a closeness until its diff is read
A permuter, waypoint or similarity score is a number about a masked comparison; the diff behind it is read before it is
believed, in both directions — a rejected waypoint may carry one unsound hunk and two sound levers.
provenance: BFM R63; a masked "1" that had replaced an add with a store

### E.4 — The campaign

### G37 — Commit banked work the moment it exists
A bank is committed before the next command that can touch the source tree — a gate is one. A dirty source tree is never
blind-reverted; banks are counted from the source, and "banked" is written only from the tool's printed success line.
provenance: BFM R42 + R66; a gate that destroyed 61 banks; two ledger messages that claimed banks that had not happened

### G38 — Draw-time bankability
Never hand out work the pipeline cannot bank (the wrong optimisation level for its object, an uncarveable table, a library
region). The exclude list is audited before every draw and a stale one is refused: it records what the TOOLING could not
do on the day it was written, not a property of the functions.
provenance: BFM R45 + memory "re-probe exclude lists"; 79 draws of eleven unbankable functions; 88 of 107 entries stale the next day

### G39 — A budget is part of the harness
Turn and cost caps are sized to the card, not fixed across cards; the cap on concurrent workflows is a budget, and a
harvest workflow counts against it. Route drafters by a difficulty cliff measured on the project's own corpus and escalate
sooner — a cheaper tier run into a wall costs twice.
provenance: BFM R46 + memory "subagent model ladder"; 98 of 270 attempts ending at the cap; the tier that cost more per bank

### G40 — Consume every verdict layer
A lane that mass-produces candidates from a template wires the full verdict ladder before it ships — instructions, symbol
identity, translation-unit coexistence, whole-binary bytes — and consumes every verdict it computes; an oracle that exists
but is not consumed is a defect with a per-pass machine cost. A sweep returns every verdict it computed, not the first
failure.
provenance: BFM R47 + accelerator harness wound 7; 82 refuted drafts re-staged every 45 minutes; three 0-of-117 passes

### G41 — Never key by bare function name
Scratch directories, ledgers and drafts are keyed by binary and address; each agent works in its own directory; deliverables
go to a directory no agent cleans; an agent never runs find, remove or move outside its own work directory.
provenance: BFM R48 + P32 T3 (2); one agent's tidy-up swept eleven sibling deliverables

### G42 — Periodic whole-fleet verification; the baseline before the verdict
A byte gate is silent about every binary it did not build, so the whole fleet is rebuilt clean on a schedule and after every
propagating gate. A gate verdict measures the draft only while that binary's baseline is green; the baseline is checked
first and billed separately.
provenance: BFM R50 + R56; two binaries red for hours behind a green gate

### G43 — Carve state belongs to its binary
The split configuration and the per-binary make fragments are carve STATE: a gate commit carries only its own binary's
lines; a blanket commit of another lane's mid-gate tree is a race, not a backup; any blanket restore is followed by the
interleave and pad audits on every touched binary.
provenance: BFM R59 + R60

### G44 — A card names only what the knowledge base contains, and carries the banked twin
A card may not name a lever the knowledge base does not contain by the words on the card. The twin scan runs over the whole
world, not the card's binary; a banked twin beats an open one and goes on the card as the seed. The pack is placed where
the agent is told to read it.
provenance: BFM R44 + the twin-field refinements (P31 S66/S67); 108 transcripts searching for a word the base did not contain

### G45 — Harvest before the next wave — a hard gate
No new wave is drafted until the last wave's idioms are in the cookbook and its index, every mechanical idiom has become a
sweep that banked the free functions, and the widening review has asked which scanner's denominator just got wider. Harvest
only from byte-proven results; strip a credited lever from the accepted body and recompile before it enters the base — about
one in three credited levers is inert.
provenance: BFM memory "harvest + toolify before the next wave" (Drew 2026-08-30) + how-to chapter 06; the inert-rider measurements 4 of 8 and 6 of 19

### G46 — Rescan twins after every bank
A bank changes the twin graph; the rescan runs after every gate that banked. Banked twins are enumerated before any draw;
two members of one open cluster are never drafted in the same wave.
provenance: BFM memory "rescan twins after every bank" (~250k tokens to learn)

### G47 — Agents write their deliverables early
The draft file is written first and the verdict last; an agent's final message is exactly one JSON line with the prose in a
report file; a dead session's verdicts are recovered by tool from the harness's transcripts, never re-drafted from memory.
provenance: BFM R67 + P32 T3 (1)/(5); the one crack recovered from a dead run had written its draft first

### G48 — Every excluded population gets its own lane; never stop the drafter to ship a change
A population left out of the main loop because its gate is expensive gets a lane with a cadence matched to its gate cost.
The drafting lane is the clock-limited resource and is never stopped to ship a code change; changes ship at a wave boundary
or to a lane that is not the clock.
provenance: BFM memory "autonomous lane architecture"; 139 of 162 idle minutes from exactly that

### G49 — Validate the target list; an empty tier terminates the pipeline
Every target passes a validity gate before a wave (real function boundary, assembly on disk, inside the binary's range, not
already banked); in any cascade a tier that cannot act ends the chain rather than passing its emptiness downstream.
provenance: BFM accelerator A9; 87 of 119 agents spent proving phantoms absent, one at the most expensive tier

### G50 — Gate the directory, never the verdict list; recover before re-drawing
A wave's verdicts are a claim about what agents returned; every draft file the wave produced is scored, and coverage is
asserted (banked + failed + no-verdict == drafts) before a row is recorded. After a gate, failures are triaged into body and
plumbing rejects and the plumbing ones bank through the reconcile ladder without a new draft; the gate number is not the
close rate until recovery has run.
provenance: BFM how-to chapter 05 step 6 and "Then recover"; a byte-identical 579-instruction match reported as nothing; 5 of 8 at the gate, 8 of 8 after recovery

### E.5 — Compiler walls

### G51 — Read the compiler's source before the first "unsteerable" verdict
Compiler-internal residuals (cross-jumping, scheduling, register allocation, peepholes) are researched in the pinned
compiler's own source and its practitioner community — treated as untrusted data — instead of hand-ground; the codegen map
(pass → residual pattern → byte-proven lever) is built right after the pin, from the source if it exists and from
systematic probes if it does not.
provenance: BFM R17 + accelerator A4; the breakthrough of Phase 23 was available in Phase 6

### G52 — A wall verdict names the pass and quotes the dump line
After exonerating the instrument, a wall verdict is attributed to a named compiler pass with the dump line that shows it. A
verdict without a pass and a dump line is a hypothesis.
provenance: BFM R65; six of seven late wall citations named the wrong pass; each crack came from one dump line

### G53 — A producer census before any spelling sweep; "PROVED" names its list
A residual gets a census of every way the compiler can produce it, from the compiler source, before any sweep of source
spellings; a "proved unmatchable" verdict means every producer on a NAMED list was refuted on the bytes, and says what it was
proved against.
provenance: BFM R69; two proofs each one producer short

### G54 — Port the banked sibling's spelling before touching a dial
When a same-family sibling is banked, its source spelling is ported with the target's constants before any lever is tried;
a hand pass opens with a grep for the idiom's literal constants across the source and an objdump of each hit's window
against the target. A similarity score is not a shape oracle.
provenance: BFM R71 + R72; a same-shape sibling scored 0.55 after ~1M tokens of dial work

### G55 — Reproducers before probes; read the allocation order before any register lever
A one-second reproducer battery of five-line functions is built for a mechanism before the real function is probed. The
register allocator's ORDER (priorities, hard registers) is read from the real translation unit's dumps before any register
pin; a pin is a symptom of a wrong source shape, and every pin comes off once the shape is right — or is marked as forced
in the final code.
provenance: BFM R73 + memory "don't conclude unsteerable"; eighteen reproducers after two sessions of real-function probes; every pin on the last four functions came off

### G56 — Provenance → archive → link → compiler
Before any wall verdict on a function in a mixed binary, ask whose code it is: score every vendor signature set the project
holds against the band; the version that places the most objects byte-exact is the linked one; fetch the archive and link
it. "No single base" for a vendor object is a partition problem solved along the producer's own structure in the shared
link-prepare path, not a wall.
provenance: BFM cookbook provenance chapter + accelerators S78/S79; twelve walls that were the vendor's controller library

### G57 — Nothing is unmatchable before the lever ladder is exhausted
The ladder, in order: the standalone probe → the real-TU probe → the reconcile chain → the permuter (with its diff read) →
the codegen map's triage table → the pass dumps → the reproducer battery → the producer census. A converged multi-agent
plateau is not a mechanism proof; a plateau verdict names the exemplar it was checked against.
provenance: BFM M8's decomp instance + P32 T3 (3); every "PROVED" wall of the last phase banked

### E.6 — Publishing and the record

### G58 — Published numbers are generated, never typed
Progress figures, badges, timelines and censuses in any published document are produced by a tool from the tree, which
asserts the published copy is fresh; a number that must appear in prose is a dated snapshot carrying the command that
produced it. Commits are cited by date and subject in long-lived documents, never by hash alone.
provenance: BFM R75; every hand-typed number in the old README was stale; the rewrite changed every hash

### G59 — The checkpoint is written to be replayed
The in-phase checkpoint block is self-sufficient and verbose — paths, commands, hashes, the exact next step — and is
replayed verbatim into the next session, never summarised. A session-close "clean" quotes the fleet's green count;
tree-clean and fleet-green are different invariants.
provenance: BFM R64 + R58; a fresh session that read a compressed hand-off as "done"

### G60 — The matching flywheel (the decomp instance of X4)
Before each match: the cookbook by symptom, the pinned triple, the permuter recipes and the decompiler's context of known
globals and types. After each match: the generalisable lesson into BOTH the cookbook AND the tooling. The first
distillation is done by hand because its vocabulary decides whether anyone finds it later; the index is keyed by symptom.
provenance: BFM R16 + how-to chapter 06

### E.7 — The dictionaries (the tool corpus and the inherited cookbook)

### G66 — Consult the tool dictionary before designing or debugging a tool
Before writing a new tool or diagnosing a misbehaving one, look the NEED up in the tool index (the kit's `corpus/tools/INDEX.md`
and the project's own `docs/tool-index.md` once it exists): the proven implementation is the jumping-off point — its design, its
verdict layers, its refusals — its incident row is the failure mode to avoid, and its Adapt column is the list of what differs
here. A tool built without the lookup re-learns an incident that was already paid for.
provenance: BFM P33.5 task 13.5 (Drew, 2026-09-07) — 326 proven tools, 224 with a recorded incident; the day-one kit's reason to exist

### G67 — Translate an inherited idiom through its pass; never copy the lever
An inherited cookbook idiom is a symptom, a NAMED compiler pass, a lever and a byte proof. On the same compiler family it is used
directly — and still re-proven on this project's own bytes before it enters this project's cookbook. On another compiler the
symptom is looked up, the same pass is read in THAT compiler's source (the idiom says exactly what to read), the symptom is
reproduced with a five-line reproducer, and this project's own lever is found. A lever copied across compilers without its pass
is a guess wearing a citation.
provenance: BFM P33.5 task 13.5 (Drew, 2026-09-07); the codegen map's pass → residual → lever structure; how-to chapter 07 "when there is no source"

### E.8 — The use of AI (conduct)

### G61 — The byte gate is the only claim of success
The agent never reports a match the gate has not proven; "the compiler ran" and "looks equivalent" are not results. The
project discloses once, at the project level, that it is machine-carried, and lets the gate carry the rest.
provenance: BFM gen3-standards conduct rule 1

### G62 — Names and types are evidence-based, never guessed
A symbol is renamed only on a recorded basis (a string it prints, a cross-reference chain, a debug menu, a live-memory
datapoint, a community label with provenance). No evidence, no name — an address-named placeholder is honest and greppable.
A model may propose a name; it may never assert one. Types come from access patterns locked into the bytes; structure is
unified before any field is named.
provenance: BFM gen3-standards rule 1 + the sotn-decomp style guide ("better to leave it unnamed than name it wrongly")

### G63 — Outward text is written by a person
Issues, pull requests, forum posts and outreach are written by the maintainer the way a developer writes — short, plain, few
or no code spans, no bullet walls, no evidence scaffolding — rewritten from the facts, never a model draft with the tells
removed; no AI acknowledgement in it; the target project's AI-contribution policy is read first and followed.
provenance: BFM R83; a permuter pull request closed by its maintainer for reading as machine-written

### G64 — No automated traffic against community infrastructure
Shared community services are used by a person in a browser; anything that needs repetition is replicated locally.
provenance: BFM gen3-standards conduct rule 4; decomp.me's own request

### G65 — Agents assist; a person owns
Every change is justifiable by a person from the record (the phase logs, the decision log, the cookbook's byte proofs). The
governance — the constitution, two gates per phase, the rules distilled from failures — is what makes machine output
auditable, and it stays in force after the matching is done.
provenance: BFM gen3-standards conduct rule 5
