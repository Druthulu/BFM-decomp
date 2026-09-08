# intake.decomp.md — the decomp answers to ProjectArchitect's interview, and the canonical phase ladder

> **What this is.** ProjectArchitect 2.0 generates a project's permanent constitution from a twelve-item intake
> (its methodology document, "Mode 1"). This file pre-answers those twelve items for a **matching decompilation** — a
> project whose definition of done is that every binary of a game rebuilds byte-identical from C — and replaces
> ProjectArchitect's generic "RE / decompilation" starting-point ladder with the ladder a finished project would have
> used from day one. The developer fills the items marked **FILL**; everything else is the distilled default.
>
> **How to use it.** During the ProjectArchitect install, when its interview starts (Path A, the new-project path), say:
> *"My intake answers are in `decomp-architect/intake.decomp.md`; read it, ask me only the FILL items, and generate from
> it."* The generation step then writes the constitution with Part B as the Build Roadmap and Part D as the
> registry's placeholder for §E. **The kit never writes the constitution** — ProjectArchitect freezes it at the end of
> its install, so the decomp content has to be in the constitution's inputs, which is what this file is. The kit's own
> installer runs afterwards, as the project's Phase 0.5, and appends the domain rules, the firewall, the overlays and the
> memory seed (`SETUP.md`).
>
> **Conventions.** Kernels are cited as `DK-n` (`corpus/decomp-kernels.md`); rules as `G-n` (`templates/registry-E.decomp.md`,
> installed into the registry's §E by Step 7 of the kit's SETUP). ProjectArchitect's own rules are cited by their ids
> (P, E, H, X, M groups). Content is generic in structure and complete for the PlayStation / PsyQ generation; other
> platforms carry `TODO(platform)` markers where the answer differs.

---

## Part A — the twelve intake items, pre-answered

### 1. The elevator pitch
A matching decompilation of **{{GAME_TITLE}}** ({{PLATFORM}}, {{GAME_SERIAL}}): C source that, compiled with the original
era's toolchain and linked in the original order, reproduces every shipped binary byte for byte, verified by a hash check
inside every build. *FILL: one sentence on what the game is and why this one.*

### 2. Motivation
**FILL** — why this game; whether prior community work exists ({{COMMUNITY_WORK}}) and what this project adds to it.
**Pre-answered, the one decision that precedes the first commit:** *decomp-first, not recompilation-first.* A matching
decompilation needs no recompiler and a recompiler's output feeds no matching work; the memory map comes from the
loader's own code and the runtime oracle, not from a recompiler. (Failure museum, first exhibit.) Ports, recompilation,
asset repacking and randomizer-grade tooling are a later generation (item 8).

### 3. Who is the developer
**FILL** — experience, domain background, solo or team, working preferences (autonomy posture, recommendation-first
options, whether breadth fan-out is welcome). Feeds ProjectArchitect's `who-is-dev` memory. Pre-answered posture from the
source project: **one human, one agent; the agent carries nearly all of the work between the two gates of each phase, the
human decides direction at the gates** (DK-62). Size phases accordingly.

### 4. Tech stack
Pre-answered shape — the pipeline every matching decompilation of this generation runs:
- **The split:** a splitter/disassembler (splat or equivalent) driven by a per-binary layout config and a curated symbol
  file, emitting per-function assembly and a linker script.
- **The build:** a modern preprocessor → the era's vintage compiler (`{{COMPILER_FAMILY}}`, pinned by evidence in Phase 4)
  → an assembler shim that reproduces the era's assembler behaviour → modern binutils for assemble/link/objcopy → the
  whole-binary hash check inside `make build` (G3). Pinned triple: `{{TOOLCHAIN_TRIPLE}}` (a `TODO` until Phase 4).
- **The oracles (G1):** a disassembler database with an agent-accessible server (the static oracle) and an emulator with a
  scriptable memory interface (the runtime oracle). *TODO(platform): PlayStation projects use a PSX loader for the
  database and a Lua-scriptable emulator; another platform names its own pair.*
- **The extractor:** the project's own deterministic disc/container/compression extractor with a committed manifest of
  hashes, cross-validated against a community reference extractor where one exists (Phase 1).
- **The verification layer** for compressed payloads is the *decompressed* payload, because recompression is rarely
  byte-stable; a rebuilt disc verifies by booting, not by hash.
- **The campaign machinery**, built in the order of Part B: the corpus oracle, signatures and the twin band, dedup and
  propagation, the reconcile ladder, the carve chain, the draw filter, the codegen map, the permuter, cards, lanes and
  the wave procedure.
- **FILL:** the platform, the compiler family the SDK evidence suggests ({{SDK_EVIDENCE}}), and the container layout of
  the medium ({{CONTAINER_LAYOUT}}).

### 5. Hard constraints
Pre-answered:
- **The ROM firewall from commit one, no private exemption** (G12, DK-1). The repository ships no byte of the game.
- **The byte gate is the only definition of done** (G3, G61); no unmatched C in a default build (G4).
- **The AI-conduct rules** (G61–G65): names only with evidence, outward text by a person, no automated traffic against
  community infrastructure, every change justifiable by a person from the record.
- **Everything runs on a fast local filesystem in one clone**; scratch lives under the repository (`.run/`), never in
  system temp (ProjectArchitect H4).
- **FILL:** the license decision for tools and documents and the statement over the decompiled source
  ({{LICENSE_CHOICE}}); the project-level AI-use disclosure sentence ({{AI_DISCLOSURE}}); whether the repository starts
  public or private ({{PUBLIC_OR_PRIVATE}}) — the firewall applies either way; platform legalities (a legally owned
  dump at `{{DUMP_PATH}}`, never committed).

### 6. Core features (the non-negotiable heart)
The milestone chain of Part B: deterministic extraction with a manifest → the oracles and the load map → an
all-assembly byte-identical baseline → the compiler pinned by evidence → the honest census and the differential harness
→ propagation, families and the reconcile ladder → the codegen map and the permuter → the campaign to every game-code
function in every binary → publication with the contract run → readability to the community's standard.

### 7. Stretch features
A public preset for the community's online matching tool (requested from its maintainers, by a person); the codegen
map, the signature tooling and the drafter pipeline released as standalone tools; support for additional versions
(regions, prototypes) as extra split configs; a text-export policy that makes the reverse-engineering database
regenerable from tracked text.

### 8. Dream features (the Parking Lot — a later generation)
A shiftable build; asset export and repacking; native recompilation or a port; randomizer-grade tooling; a
community-trained matching model. Each is sequenced after readability (Part C), because every one depends on symbolic,
legible source.

### 9. Known risks and pain points
Pre-answered from the source project's failure museum (`corpus/decomp-kernels.md` part 9):
- **Almost every recorded wall was one of the project's own instruments** (DK-9, DK-17) — plan the differential
  harness and the coverage assertions at 0%.
- **Integration, not idioms, is the bottleneck once cracking is systematic** (DK-7) — budget for banking.
- **A wrong compiler era or a silent assembler default produces systematic near-misses everywhere** (DK-3).
- **ROM-derived bytes committed "while private" cost a full-history rewrite** (DK-1, DK-53–56).
- **Model-drafted outward text costs goodwill** (DK-58); **names guessed by a model damage a decompilation without any
  test catching it** (G62).
- **Structural decisions get more expensive as matched work accumulates** (DK-12) — segment at the forced boundaries
  before any C exists.
- **A fresh session misreads a compressed hand-off** (DK-59) — the checkpoint is replayed, never summarised.
- **FILL:** what worries the developer; what failed before.

### 10. Definition of success
Pre-answered, and machine-checkable per phase (ProjectArchitect M1): every binary on the medium — **N of N** — rebuilds
byte-identical from C from a clean rebuild, with the check inside the build; every game-code function is C (what is not
C — the vendor's linked objects, the original's genuine hand-written assembly — is stated, censused and published, never
hidden); a stranger with their own dump can extract, build and verify from the README alone; the published numbers are
generated. The per-phase milestones are Part B's.

### 11. Multi-user / deployment reality
**FILL.** Typical: one developer on one machine; CI that proves everything that does not need the game (the ROM audit,
a compile of every translation unit with the pinned toolchain) while byte-identity is verified locally with the dump and
recorded; contributors bring their own dump.

### 12. Resource management
**FILL:** disk for the dump, the extraction and the scratch tree (the source project's scratch reached tens of gigabytes;
`make clean` never touches it and pruning is a hand decision); model budget per lane; local model capacity if any.
Pre-answered shapes: scratch under `.run/` with dated tracked exceptions (the conventions README the kit installs);
per-worker git worktrees for parallel gates, reaped; budgets that are part of the harness (G39); free work before paid
work (DK-40).

---

## Part B — the canonical phase ladder (the Build Roadmap; adapt, don't copy)

*Each phase produces something runnable and ends with an observable, machine-checkable milestone (M1). Size to the
developer (ProjectArchitect's skill-level handling): a beginner merges phases 1–3 and 5–6; an advanced developer may
split 8 into waves. The `earned by` column is the reason the phase sits where it does — a kernel the source project paid
to learn late, or its retrospective's "do sooner" list. Rules are ratified at each phase's close (P10); the ids are the
registry seed's, installed at Phase 0.5.*

| # | Phase | Machine-checkable milestone | Tools built | Rules in force from here | Earned by |
|---|---|---|---|---|---|
| 0 | **Governance and the firewall** (ProjectArchitect's Phase 0 + this kit's Phase 0.5) | The ROM audit FAILS on the planted fixture and PASSES on the tree; the no-ROM CI workflow is green on the first push; the constitution carries this ladder; the registry holds G1–G67 | the audit with its config, the fixture, CI, the layout READMEs, `make format` | G12–G18, G58, G61–G65 | DK-1, DK-53–DK-58 |
| 1 | **Deterministic extraction with a committed manifest** | One command extracts the whole medium; the manifest of hashes is reproduced identically by a second run; sampled payloads agree byte-for-byte with a reference extractor where one exists; `git status` shows nothing ROM-derived staged; the audit now reads the manifest as a required hash source | the extractor (game-semantics decompression with a length cross-check), the manifest, the format notes | G13 (the manifest becomes `required:` in the firewall config) | DK-2 |
| 2 | **The oracles and the load map** | The database imported with the era's signatures and the detected SDK version recorded; the database's annotations exported as text and the rebuild round-trip proven; the runtime oracle scripted; the load address of the resident code and of at least one overlay byte-proven against a live memory image (three datapoints or a before/after diff — M3); the load map regenerated from the bytes with control rows; the data island's jump-table spans and the other forced boundaries recorded for Phase 3's segmentation | the MCP server wiring, the text export + rebuild script, the emulator bridge, the load-map tool, a span/boundary indicator | G1, G2, G5, G6 | DK-13, DK-12, DK-18 |
| 3 | **The all-assembly byte-identical baseline** | `make build` produces every onboarded binary with a hash equal to the original at 100% assembly, with the check inside the build; translation-unit boundaries sit at the forced boundaries found in Phase 2; `make expected` baseline set | the Makefile pipeline, the per-binary contracts, the split configs, the boundary check in the health target | G9 | DK-2, DK-12 |
| 4 | **The compiler pinned by evidence** | Three to five probe functions byte-identical under exactly one candidate triple; the triple recorded with its fingerprint evidence and the assembler version passed explicitly; per-module variation (optimisation levels, mixed compilers) detected and recorded; the first functions matched end to end through the whole workflow | the decompile scaffold wrapper, the differ invocation, the standalone probe, the stub/non-matching headers | G8, G10 | DK-3 |
| 5 | **The honest census and the differential harness — at 0%** | Every scanner asserts its coverage; a second oracle disagrees with the first on nothing (0 phantoms, 0 truncations); the harness runs at least five question pairs on a schedule with 0 disagreements; the census reports duplication, structural families, reach × size and the unique tail, each checked against a known-true case; the progress report derives its denominators from the build | the corpus oracle, the coverage assertions, the second boundary oracle, the differential harness, the census, the progress/difficulty/duplicate reports, the health chain that runs every one of these on a schedule (the source project's ordered recipe, a comment per rung naming its incident, ships in the record: `build/tools-health.mk`) | G19–G36 | DK-8, DK-9, DK-17, DK-19, DK-30, DK-61 |
| 6 | **The multipliers: propagation, families, twins, the reconcile ladder, the carve chain, the draw filter** | One hand-matched function propagates to every member across the fleet, byte-gated per member, registered fail-closed; the twin band reproduces every exact pair and finds more; a standalone match is banked into its real translation unit by the ladder without a redraft; the opt-level and jump-table carves build; the draw filter refuses what cannot bank and counts what it filtered; all four verdict layers are consumed; **the canonical type layer** exists from the first bank — one definition per shape, widths and signedness proven by the bytes at bank time, a bank refused for a duplicate definition of an existing shape or a raw address cast | signatures (exact, normalised, sequence) + the band, dedup propagation and the registry, the family remap, declaration sync / callee casts / canonical signatures, the canonical type file with its bank-time duplicate-definition and raw-cast check (the type lifter and the signature reconciler start here, not at Phase 10), the carve tools, the wall oracle, the draw filter, the twin rescan | G7, G37, G40–G43, G46, G62 (its bank-time clause) | DK-5, DK-7, DK-10, DK-11, DK-24, DK-36, DK-65 |
| 7 | **The codegen map and the permuter** | The map holds at least one byte-proven lever per pass group with a symptom-keyed triage table; the compiler's source staged at the pinned version with citations audited; the permuter runs on a stored draft and proves it iterated; the plateau classifier labels a plateau; the cookbook seeded from the source and any sibling project, indexed by symptom with its own coverage assertion | the map, the dump scripts (from the real unit), the allocation-table reader, the reproducer battery harness, the permuter with a masked scorer, the plateau classifier, the cookbook index tool | G51, G52, G55, G57, G60, G66, G67 | DK-6, DK-14, DK-15, DK-52 |
| 8 | **First cracks, the manual wave, the routing cliff — then the campaign, leverage-first** | Bank rate by instruction count measured on a small manual wave and the routing set from it; every wave closes with the harvest gate (idioms in the base, mechanical ones toolified, free banks swept, the widening review asked); the fleet green from a clean rebuild after every banked batch; every remaining function on a named ledger with a class, a closeness, a best draft and a named blocker; the census reads 0 stubs | cards and packs (with the banked twin, past attempts, the lever with where to read it), the lanes, the wave procedure with each guard's measurement, the journal read side, the target validator, the exclude-list audit, the gates in worktrees, the recovery ladder, the harvest tools, the verbatim check | G38, G39, G44, G45, G47–G50, G53, G54, G56 | DK-16, DK-31–DK-35, DK-39–DK-43, DK-44–DK-51 |
| 9 | **Publish** | The contract run recorded (clean rebuild, both with and without the vendor SDK, every oracle green, N of N); a fresh clone rebuilds from the developer's own dump by the README alone; every published number generated with a freshness check; the no-ROM CI green; the releases and outreach written by a person; if the repository was private, the visibility flip gated on the host's object store | the contract script, the bootstrap script, the progress publisher, the badges, the release write-ups | G17, G58, G63, G64 | DK-56, DK-57, DK-58 |
| 10 | **Readability** (short if Part C and Phase 6's type layer held — with one definition per shape and no raw cast banked from the first bank, this phase is names, pins and formatting) | 0 register pins, or each one marked as forced with its reason; 0 shared bodies as macros; 0 raw address casts (every one a declared, typed symbol; a field of a known structure accessed as a field); one definition per structure; every renamed symbol with a recorded basis; formatting clean; and, unchanged, N of N byte-identical from a clean rebuild | the allocation-order reader on the real unit, the type lifter, the symbol mirror into the database, the rename-coverage scanner | G11, G62 | DK-64, DK-65, DK-47, DK-12; Part C |

**Two notes on the order.** Phases 5–7 look like "planning-only" phases and are not: each ends in a running tool with a
verifiable output (M1), and each is the reason the campaign phase banks at the rate it does — the source project built
them reactively, phases later, and the how-to's bootstrap order is the single largest lesson of the retrospective.
Tooling-first does not remove the hard tail: the novel unique functions and the compiler-internal residuals still need
genuine reasoning; it makes the cheap half nearly free and stops the waste (DK-43, the honest caveat).

---

## Part C — readability at day one: the six inversions

The source project reached 100% and then chartered a whole generation to make the code legible. Each item below is
something it had to do *after* the fact that a new project does *at draft or bank time*, gated the same way a match is:

1. **Pins are recorded at draft time, not removed later.** A draft carrying a register pin is a near-miss with its
   allocation-order reading attached, not a bank; a body that genuinely cannot be shaped is banked with a `// !FAKE:`
   line naming the residual, and the count is a published metric from the first bank (G55, DK-47).
2. **Shared bodies live as C files per system from the first propagation**, not as macro bodies in one header; the dedup
   registry points at a function in a file a reader would open (G7, DK-5).
3. **Types are canonical at bank time, and no raw address cast is banked.** A draft may not invent a structure the shared
   header already has, and every absolute address it touches is a declared, typed symbol from the first bank (a field of a
   known structure is accessed as a field); one definition per shape, unified before any field is named; a duplicate type is a
   defect (G62).
4. **Names carry evidence, recorded per name**, on the same ladder as addresses: a string it prints, a cross-reference
   chain, a debug menu, a live-memory datapoint, a community label with provenance. Unnamed beats wrong; a model proposes,
   a person with evidence asserts (G62).
5. **Formatting is installed with the first C file:** the community style guide's formatter configuration and a
   `make format` target ship with the kit; a bank is formatted before it is committed.
6. **File layout follows the game's systems, with unit boundaries decided at segmentation time from the build's forced
   boundaries** (jump-table spans, optimisation levels, library objects) — not by the carving tool, and not by
   archaeology about the original file layout (DK-12).

---

## Part D — what to tell ProjectArchitect's generation step about the registry

Registry **§E** is left **empty except one line** — *"the decomp kit's Phase-0.5 install appends the domain rules here
(G1–G67)"* — so the kit's seed installs with its numbering intact; any corpus-derived rule ProjectArchitect would add that
is *not* decomp-specific goes after the kit's block at Phase 0.5, not before it. The CLAUDE.md fail-safes
(`{{DOMAIN_FAILSAFES}}`) are the four the kit's overlay states: never commit game-derived bytes; a match is byte-for-byte
and the whole-binary hash; never `git clean -x` here; the byte gate is the only claim. The effort map's per-phase rows
are the ladder above with Max on the plan, the PhaseEnd, the compiler pin, the segmentation decision and any wall verdict.
