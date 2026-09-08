# Start a new decomp project

This project reached 100% and then wrote down, in one place, what it would hand its own day one: the order of work it
would have used from the start, the ROM firewall from the first commit, the rules distilled from its failures, the
knowledge-base flywheel, the model and effort doctrine, the conduct rules for using AI, and the readability standard
applied at draft time instead of after 100%. That package is the **day-one decomp kit**, `decomp-architect/`, at the
repository root. It lives in this tree until the public flip and is split into its own repository afterwards, as xsig was.

It is an overlay, not a system of its own: it installs as **Phase 0.5** of a project governed by
[ProjectArchitect 2.0](https://github.com/Druthulu/ProjectArchitect) (the constitution-and-phase-gates system this project
ran under), and it refuses to run on any other version or on a repository ProjectArchitect has not set up.

## The three steps

From the kit's own README (`decomp-architect/README.md`):

1. **Install ProjectArchitect 2.0.** Copy its `project-architect-2.0/` folder into your new, empty git repository and say, in
   Claude Code, `Read SETUP.md and do it.` When its interview starts, hand it the kit's intake:
   `My intake answers are in decomp-architect/intake.decomp.md; read it, ask me only the FILL items, and generate from it.`
   The intake pre-answers ProjectArchitect's twelve items for a decompilation and carries the phase ladder, so the
   constitution ProjectArchitect generates — and then freezes — already contains the decomp roadmap with a
   machine-checkable milestone per phase. (Copy `decomp-architect/` in first so the file is there to read.)
2. **Copy `decomp-architect/`** into the repository root, beside `project-architect-2.0/`. Only that folder, not the
   repository it ships in.
3. **Run the kit's installer.** In a fresh session: `Read decomp-architect/SETUP.md and do it.` It checks the
   ProjectArchitect version, interviews you about the game (title, platform, serial, where your dump lives, the medium's
   container layout and SDK evidence, prior community work, goals, the license and disclosure decisions), stamps the
   firewall, appends the domain rules and the overlays, seeds the memory and the corpus, verifies every step, commits by
   explicit path, and stops. Then delete the folder, start a fresh session and say `Begin Phase 1`.

For an unattended run, the instruction takes an `answers: <path>` clause naming a `KEY: value` file; a missing key stops
the installer, it never defaults. Every git call is by explicit path; the installer never pushes and never runs `git clean`.

## What it installs — and what it deliberately does not

| Piece | What it is |
|---|---|
| The intake (`intake.decomp.md`) | ProjectArchitect's twelve items pre-answered; the phase ladder below; the six readability inversions; what to tell the generation step about the rules registry |
| The methodology (`decomp-architect.md`, copied to `docs/`) | thirteen sections: the ladder and why, the byte gate, cards/lanes/waves, the flywheel laws, the instruments, integration, the compiler's source, models and effort, conduct, readability at day one, what stays hard, publishing, the economics' shape |
| The registry seed (`templates/registry-E.decomp.md`) | rules G1–G67 in seven groups — the oracles and the gate, the ROM firewall, the instruments, the campaign, compiler walls, publishing and the record, the use of AI — each with a `provenance:` line naming the failure that earned it |
| The firewall pack | a copyable `.gitignore` (the same block as [The ROM firewall](The-ROM-firewall.md), asserted identical in this project's health check), an audit that derives its forbidden set from a config and fails on a planted fixture before it is trusted, and a CI workflow — no game-derived bytes in git from commit one |
| The layout, the overlays, the skeletons | the `docs/` and `.run/` conventions from [Docs and scratch conventions](Docs-and-scratch-conventions.md); marked-section appends to `CLAUDE.md`, the effort map, the cookbook, the ops reference; the session-start digest, the replayable checkpoint block and the PhaseEnd narrative axis; LICENSE, NOTICE, README and CONTRIBUTING skeletons, a `.clang-format` and a `make format` snippet |
| The kernels (`corpus/decomp-kernels.md`) | DK-1 … DK-68: what this project learned late, each with when it applies and what it cost, plus the failure museum |
| The memory seed (`memory-seed/`) | eighteen working agreements and harness facts, de-specialised, appended to the memory ProjectArchitect configured |

**It installs no tools.** A byte gate, a splitter config, a permuter harness, a decompiler context, a differential
harness — those are the first phases' work, and the kit says so in its installer's honesty section. What it ships instead
is **three dictionaries**, all generated from this tree and asserted equal to it on every health check:

- **The tool corpus** (`decomp-architect/corpus/tools/<phase>/`): this project's 293 live tools, copied verbatim by ladder
  phase, behind an index keyed by the *need* each answers — what it does, what proved it (its consumers), what it
  hard-codes. The live counterpart is the [tool index](../tool-index.md). Superseded tools appear as pointers to their
  successor; one-offs are left behind. A new project builds each tool for its own target from the description, with the
  verbatim copy as the reference implementation and the *adapt* column as the list of what to change — and the kit's rule is
  to look a need up in the dictionary before designing or debugging a tool (G66).
- **The inherited knowledge base** (`decomp-architect/corpus/cookbook/`): the matching cookbook, its symptom-keyed index
  and the gcc 2.7.2 codegen map, verbatim, behind a front page that states what transfers (see *The compiler question*).
- **The inherited record** (`decomp-architect/corpus/record/`): the thirteen how-to chapters, the decision log, the
  accelerators, the retrospective, the story, the wave playbook, the effort doctrine, the readability charter, the digest and
  every PhaseEnd, verbatim, behind a front page that says what each is and how to read it. The kit's rules and kernels were
  distilled from these; a `provenance:` line on any of them leads back here. A coverage check asserts that every one of this
  project's rules and every entry of its accelerators ledger is either cited by such a line or explicitly dispositioned, so
  the distillation has no silent gap. The phase worklogs are not included; a dedicated pass read every one of them for lessons
  banked nowhere else, and those became kernels.

## The phase ladder

The order this project would use if it started again. Each phase ends in something runnable with a machine-checkable
milestone; the last column is the kernel that earned the phase its position — something this project paid to learn late.
The full rows, with the tools built and the rules in force, are the intake's Part B.

| # | Phase | Milestone, in one line | Earned by |
|---|---|---|---|
| 0 | Governance and the firewall | the ROM audit fails on the planted fixture and passes on the tree; CI green on the first push; the constitution carries this ladder | DK-1, DK-53–58 |
| 1 | Deterministic extraction with a committed manifest | one command extracts the whole medium; a second run reproduces the manifest; sampled payloads agree with a reference extractor; nothing ROM-derived staged | DK-2 |
| 2 | The oracles and the load map | the database imported with the era's signatures and exported as text with the rebuild proven; the runtime oracle scripted; load addresses byte-proven against live memory; the forced boundaries recorded | DK-12, DK-13, DK-18 |
| 3 | The all-assembly byte-identical baseline | every onboarded binary rebuilds hash-equal at 100% assembly with the check inside the build; unit boundaries at the forced boundaries | DK-2, DK-12 |
| 4 | The compiler pinned by evidence | three to five probe functions byte-identical under exactly one candidate triple; per-module variation detected; the first functions matched end to end | DK-3 |
| 5 | The honest census and the differential harness, at 0% | every scanner asserts its coverage; a second oracle disagrees on nothing; the census checked against a known-true case; denominators derived from the build | DK-8, 9, 17, 19, 30, 61 |
| 6 | The multipliers | one matched function propagates fleet-wide, gated per member; twins reproduced; a standalone match banked into its real unit without a redraft; the carves build; the draw filter refuses what cannot bank; **the canonical type layer from the first bank** — one definition per shape, widths proven by the bytes, no duplicate definition or raw address cast banked | DK-5, 7, 10, 11, 24, 36, 65 |
| 7 | The codegen map and the permuter | one byte-proven lever per pass group with a symptom-keyed triage table; the compiler's source staged and cited; the permuter proves it iterated; the cookbook seeded and indexed | DK-6, 14, 15, 52 |
| 8 | First cracks, the manual wave, the routing cliff, then the campaign | the bank rate measured on a small manual wave and the routing set from it; every wave closes with the harvest gate; the fleet green from a clean rebuild after every batch; the census reads 0 stubs | DK-16, 31–35, 39–51 |
| 9 | Publish | the contract run recorded; a fresh clone rebuilds from the developer's own dump by the README alone; every published number generated; the flip gated on the host's object store | DK-56–58 |
| 10 | Readability (short if the inversions held) | 0 pins or each marked; 0 shared bodies as macros; 0 raw casts; one definition per structure; every rename with a recorded basis; formatting clean; N of N still byte-identical | DK-64, 65, 47, 12 |

Phases 5–7 look like planning phases and are not: each ends in a running tool, and each is the reason the campaign phase
banks at the rate it does. This project built them reactively, phases later; the bootstrap order is the single largest
lesson of its [retrospective](../retrospective.md) and of the how-to's chapter [03 Bootstrap order](../how-to-ai-decomp/03-bootstrap-order.md).

## The AI-use rules

The five conduct rules from [Contributing](Contributing-and-the-no-ROM-policy.md) are the kit's rules G61–G65, in force
from Phase 0:

1. **The byte gate is the only claim of success.** No match is reported that the gate has not proven; every "done" is
   written from a tool's printed success line.
2. **Names and types are evidence-based, never guessed.** No evidence, no name; a model may propose, it may never assert.
3. **Outward text is written by a person**, the way a developer writes, after reading the target project's own AI policy.
4. **No automated traffic against community infrastructure.**
5. **Agents assist; a person owns.** Every change is justifiable by a person from the record.

## Readability at day one — the six inversions

This project reached 100% and then chartered a whole generation to make the code legible
([Where the project goes next](Where-the-project-goes-next.md)). Each item below is something it had to do *after* the
fact that a new project does at draft or bank time, gated the same way a match is (the intake's Part C, kernel DK-64):

1. **Pins are recorded at draft time, not removed later.** A draft carrying a register pin is a near-miss with its
   allocation-order reading attached, not a bank; a body that cannot be shaped is banked with a `// !FAKE:` line, and the
   count is a published metric from the first bank.
2. **Shared bodies live as C files per system from the first propagation**, not as macro bodies in one header.
3. **Types are canonical at bank time, and no raw address cast is banked.** A canonical type file exists from the first bank
   and grows one proven field at a time; a draft may not invent a structure the file already has, every absolute address it
   touches is a declared, typed symbol, and a width or signedness is proven by the bytes — the one place a type moves bytes
   (DK-65: types are a *banking* lever and a *width* lever, not a codegen lever; this project measured the codegen half
   correctly and underweighted the other).
4. **Names carry evidence, recorded per name**, on the same ladder as addresses.
5. **Formatting is installed with the first C file:** the community style guide's formatter and a `make format` target.
6. **File layout follows the game's systems, with unit boundaries decided at segmentation time** from the build's forced
   boundaries — not by the carving tool, and not by archaeology about the original file layout.

## The compiler question

The inherited cookbook is one project's knowledge base for one compiler family. Its front page
(`decomp-architect/corpus/cookbook/README.md`) says what transfers:

- **Same family (the gcc 2.7.2 era that shipped with the PlayStation SDK):** the idioms apply directly — look the symptom
  up, apply the lever, and still re-prove it on your own bytes before it enters *your* cookbook. An idiom that held on one
  game's functions is a hypothesis until it holds on yours.
- **Another compiler:** the levers do not transfer; the *structure* of every entry does. An idiom is a symptom, a named
  pass, a lever and a byte proof. Find your tell in the index, read which pass this project attributed it to, read the same
  pass in your compiler's source (or probe it), build a five-line reproducer that shows the symptom on your toolchain, find
  your lever, write your own entry in the same shape. The inherited idiom tells your agent what to read; it does not tell it
  the answer (G67: translate through the pass, never copy the lever).

In both cases the compiler-agnostic parts apply unchanged: the integration classes, the instrument findings, the harvest
laws, the verbatim class, the segmentation law, and the type verdict above.

## The accelerators, one line each

Everything in [`docs/accelerators.md`](../accelerators.md) — what was learned late, when it could have been learned, what it
would have saved — in one line per entry. The kernels distil the same material with their costs; this is the index.

| When | Accelerator |
|---|---|
| Phase 26 | **A1** Instrument integrity before measurement, as a standing habit — fix the tool, then trust the number |
| Phase 12 | **A2** The whole-binary byte gate plus a parallel drafting harness, from the first byte-identical build |
| Phases 11–15 | **A3** Cross-binary dedup propagation: match once, stamp every member, gate each |
| Phase 23 | **A4** Read the compiler's source once, into a codegen map — right after the triple is pinned |
| Phase 30 | **A5** A static scanner must model the compiler's addressing forms, or it under-counts references |
| Phases 24–25 | **A6** Regroup the residue by structure before calling any of it unique |
| Phase 30 | **A7** The load map: derive who loads what from the bytes, with control rows |
| Phase 30 | **A8** Parallelism defaults for fleet-wide tools — processes for CPU work, threads for waits, batch what you already know |
| Phase 30 | **A9** Validate the target list, and let an empty tier terminate the pipeline instead of running on nothing |
| Phase 31 | A `#` comment between backslash-continued argument lines silently drops every argument below it; print the effective config on line one |
| Phase 31 | `pgrep -f <pattern>` matches your own shell; anchor the pattern or kill by pid |
| Phase 31 | `cmd \| tail -N` buffers everything until exit — a background job's progress never shows |
| Phase 31 | Telemetry that exists only in a log line is not telemetry; count it where it is read |
| Phase 31 | A running lane script does not read your edit — bash parsed the loop up front; restart it |
| Phase 31 | A 0% gate yield is a statement about the instrument until a no-input control says otherwise |
| Phase 31 | A mechanical-remap lane needs all four verdict layers wired in from day one |
| Phase 31 | **#12** Byte-locate the residual before blaming the draft |
| Phase 31 | **#13** Census what is already drafted before drawing anything |
| Phase 31 | **#14** Make the cheap probe call the real planner, not a copy of it |
| Phase 31 | **#15** The differential-oracle harness: run every question down two paths and fail on disagreement |
| Phase 31 | **#16** A "verified, just bank it" claim must name the compilation it survived |
| Phase 31 | **#17** A similarity join is probably a point when it should be a band |
| Phase 31 | **#18** A claim derived from bytes is not a claim verified by a compiler |
| Phase 31 | **#19** A verdict recorded inside an isolated environment describes the environment |
| Phase 31 | The agent journals were a labelled corpus written for thirty phases and never read back — feed them into the next card |
| Phase 31 | **#20** Set translation-unit boundaries at the data island's jump-table spans, at segmentation time |
| Phase 31 | A tool that derives a byte-exact fact from a pretty-printer inherits its liberties |
| Phase 31 | A refusal check is measured against what the real pipeline does to the input, not against a clean copy |
| Phase 31 | An exclusion reason is a claim about the tooling on the day it was written — re-probe the list after every tool fix |
| Phase 31 | The loader shipped the answer key: per-version SDK signatures name the library bands you cannot link |
| Phase 31 | Check a percentage against a case you already know the answer to |
| Phase 31 | "No single base" means "partition it", along the producer's structure |
| Phase 31 | Provenance → archive → link → compiler, in that order — a "wall" is a provenance question first |
| Phase 31 | A tool that reports "unchanged" for N cycles must prove it iterated |
| Phase 31 | A byte gate is a null oracle for "is this C?" — pasted assembly is a verbatim, not a bank |
| Phase 31 | A pointer-only callee's `extern` is a guess, not a constraint |
| Phase 31 | "banked 1 / merged 0 / refused 0 / exit 0" can be a failure that prints as success |
| Phase 31 | Agent drafters outlive the session that spawned them; harvest a dead session from its transcripts |
| Phase 32 | A coordinator that reads prose results dies mid-wave; agents return one JSON line |
| Phase 32 | A shared scratch directory is a shared blast radius; one work directory per item |
| Phase 32 | A converged multi-agent plateau is not a mechanism proof |
| Phase 32 | The rematerialisation slider is a computation, not a search — read the dump's counts |
| Phase 32 | The build is the batch verdict; a per-draft oracle is blind to cross-draft integration |
| Phase 32 | Read a permuter waypoint's diff before rejecting or accepting it |
| Phase 32 | A tool's live probe in the source tree is part of the build's input |
| Phase 32 | Re-probe a compile-failure wall in a sandbox unit, not by editing the tree |
| Phase 32 | A lever that measures worse may be a cascade |
| Phase 32 | The strongest model on the compiler-internals class banked where every prior tier had 0 — reserve it for that |
| Phase 32 | Attribute the residual to a pass with a dump line before sweeping levers |
| Phase 32 | Enumerate the artefact's producers from the compiler source before probing a single spelling |
| Phase 32 | When a same-family sibling is banked, port its spelling before touching a dial |
| Phase 32 | A similarity score is not a shape oracle — grep the idiom's constants and read the sibling's objdump window |
| Phase 32 | Re-run the producer census with the combiner's bookkeeping in view before writing "proved" |
| Phase 32 | Read the allocation order before the register; pins are symptoms |
| Phase 33.5 | An ignore file's directory-form rule is a wall no later block can climb — write the by-contents form first |
| Phase 33.5 | A check that compares a typed figure against a derived one is wrong the day the derived side moves |
| Phase 33.5 | A dry-run judge is an instrument; negative-control it before believing its FAILs |
| Phase 33.5 | A tool without a dictionary row is invisible to the project that owns it |

## The proof: four dry-run installs

The kit was installed four times into a throwaway repository by an agent that had never seen it, from an answers file,
under write-scope guardrails (nothing outside the throwaway; the real tree's dirty paths, the memory store and the
settings compared before and after), and judged by a script rather than by the agent's own report
(`.run/P33.5/kit-dryrun/judge.py`, with the answers file, the expected manifest, the install logs and the verdicts beside it).

| Run | Outcome | What it found |
|---|---|---|
| 1 | FAIL at the firewall step | ProjectArchitect's own ignore block writes the directory form `.run/`, and git never descends into an excluded directory, so no re-include beneath it can take effect; and its leftover-placeholder audit was not scoped past the installer packages' own template bodies. Two installer steps rewritten. |
| 2 | PASS 10/10 (resumed from the fixed step) | `py_compile` always writes bytecode (an in-memory compile replaced it); prose that quotes a literal placeholder trips the audit (a documented rule); the judge itself had two false FAILs — the same scoping gap it was judging, and a dirty-tree *count* where a path *set* was needed. |
| 3 | PASS 10/10, 0 defects (fresh throwaway, fresh agent, final kit) | Two honest agents produced two honest manifest sizes from the same words: the manifest is now specified as an exact derivable set. |
| 4 | PASS 10/10 after one resume (after the dictionaries were added) | The installer compared a typed figure against a derived one and stopped the day the derived side moved; both sides are now derived. The one guardrail flag was a generated timeline rewritten by a health check running at the time, not a write by the agent. |

The harness is reusable: a kit change is re-verified by resuming on the last throwaway; a fresh full run only when the
installer's steps change.

## Where it lives, and how it is kept honest

- `decomp-architect/` at the repository root, gitignored by the project it is installed into (the folder is deleted after
  Phase 0.5; the methodology survives as a copy in the new project's docs folder).
- `tools/kit_lint.py` keeps it de-specialised: no line outside a calibration fence names this project, its paths, its
  rule numbers or its cookbook sections; the placeholder set equals the documented contract; every script parses; the
  `.gitignore` template equals the wiki page's block.
- `tools/tool_census.py --check` asserts the three dictionaries equal their sources, and `tools/kit_coverage.py` that every rule and
  every accelerator entry of this project is cited or dispositioned; `make kit-corpus` regenerates them
  (any edit to a tool or to the cookbook makes a copy stale until it is run).
- Both run in `make tools-health`. The split into its own repository happens after the flip; the folder lifts unchanged,
  because nothing in it refers to this repository's paths.

Nothing in the kit is derived from any game.
