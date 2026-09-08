# decomp-architect

A day-one kit for running a **matching decompilation** with Claude Code: the order of work that a finished project would
have used from the start, the ROM firewall from the first commit, the rules distilled from that project's failures, the
knowledge-base flywheel, the model and effort doctrine, the conduct rules for using AI, and the readability standard
applied at draft time instead of after 100%. It installs as **Phase 0.5** of a project governed by **ProjectArchitect
2.0** — it does not replace that system, it fills in the decomp-specific half of it.

It comes from one project that took a console game from a disc image to every binary rebuilding byte-identical from C,
with an agent doing nearly all of the work and a person deciding at the gates, and that kept its records as it went. The
kit is what that project would hand its own day one.

## Requirements

- [ProjectArchitect 2.0](#step-1--install-projectarchitect-20) — your master copy of its package folder. The kit refuses
  to run on any other version or on a repository ProjectArchitect has not set up (see *Scope*).
- Claude Code and git, as ProjectArchitect requires.
- For the decompilation itself, none of these is an install blocker — they are the first phases' work — but you will
  need them: a legally owned dump of the game, a splitter/disassembler that emits per-function assembly (splat or
  equivalent), candidate compilers of the game's era, a disassembler database with an agent-accessible server, and an
  emulator with a scriptable memory interface.

## Install

### Step 1 — install ProjectArchitect 2.0

Copy ProjectArchitect's `project-architect-2.0/` folder into your new, empty git repository and say, in Claude Code:

```
Read SETUP.md and do it.
```

When its interview starts (the new-project path), hand it this kit's intake:

```
My intake answers are in decomp-architect/intake.decomp.md; read it, ask me only the FILL items, and generate from it.
```

That file pre-answers ProjectArchitect's twelve intake items for a decompilation and carries the phase ladder, so the
constitution ProjectArchitect generates — and then freezes — already contains the decomp roadmap with a
machine-checkable milestone per phase. (Copy `decomp-architect/` in before this step so the file is there to read; the
kit's installer itself runs in step 3.)

### Step 2 — copy this folder

Copy `decomp-architect/` into the repository root, beside `project-architect-2.0/`. Copy only this folder — not the
repository it ships in.

### Step 3 — run the kit's installer

In a fresh Claude Code session (ProjectArchitect's install ends with a hard stop and asks for one), say:

```
Read decomp-architect/SETUP.md and do it.
```

The installer runs as the project's Phase 0.5: it checks the ProjectArchitect version, interviews you about the game
(title, platform, serial, where your dump lives, what the medium's container layout and SDK evidence look like, prior
community work, your goals, the license and disclosure decisions), stamps the firewall, appends the domain rules and the
overlays, seeds the memory and the corpus, verifies every step, commits by explicit path, and stops. Then delete the
`decomp-architect/` folder (it is gitignored; the methodology survives as `docs/decomp-architect.md`), start a fresh
session and say `Begin Phase 1`.

## What it installs

| Piece | What it is |
|---|---|
| **The intake** (`intake.decomp.md`) | ProjectArchitect's twelve items pre-answered; the canonical phase ladder with a machine-checkable milestone, the tools built, the rules in force and the kernel that earned each phase's position; the six readability inversions; what to tell the generation step about the registry |
| **The methodology** (`decomp-architect.md` → `docs/decomp-architect.md`) | the ladder and why, the byte gate, cards/lanes/waves, the flywheel laws, the instruments, integration, the compiler's source, models and effort, conduct, readability at day one, what stays hard, publishing, the economics' shape |
| **The registry seed** (`templates/registry-E.decomp.md` → `RULES_REGISTRY.md` §E) | G1–G67: the oracles and the gate, the ROM firewall, the instruments, the campaign, compiler walls, publishing, the use of AI — each with a `provenance:` line naming the failure that earned it |
| **The firewall pack** (`templates/gitignore.decomp`, the audit template and its config, a planted fixture, the CI workflow) | no game-derived bytes in git from commit one; an audit that derives its forbidden set, asserts its coverage and fails on the fixture before it is trusted; CI on every push |
| **The layout and its READMEs** (`docs/`, `.run/`, the ops-setup overlay) | where each kind of knowledge goes; scratch under the repository with dated tracked exceptions; the ops reference a fresh machine rebuilds from |
| **The overlays** (`templates/pa-overlays.md`, `templates/CLAUDE.decomp-overlay.md`) | marked-section appends to `CLAUDE.md` (the decomp fail-safes and session-start extras), the effort map (Max on the plan, the PhaseEnd, the compiler pin, the segmentation decision, any wall verdict), the cookbook (the idiom entry shape, the triage table), ops-setup; the digest, the replayable checkpoint block and the PhaseEnd narrative axis |
| **The corpus** (`corpus/decomp-kernels.md`) | DK-1 … DK-80 — what the source project learned late, each with when it applies and what it cost, and the failure museum |
| **The three dictionaries** (`corpus/tools/`, `corpus/cookbook/`, `corpus/record/`) | the source project's tools, verbatim, by ladder phase, behind an index keyed by the NEED each answers (what it does, what proved it, what to adapt); its knowledge base — the cookbook, its symptom index and the codegen map — verbatim, behind a front page that says what transfers to another compiler; and its record — the how-to, the decision log, the accelerators, the retrospective, the story, the playbook, the effort doctrine, the readability charter and every phase-end — verbatim, behind a front page that says what each is, so that every rule's and kernel's `provenance:` line can be followed to its evidence. All three are regenerated from the source project and asserted equal to it; a new project installs the index and the front pages and keeps the folder as its reference shelf |
| **The memory seed** (`memory-seed/`) | working agreements and harness facts learned on the source project, appended to the memory ProjectArchitect configured |
| **The skeletons** | LICENSE, `src/NOTICE.md`, README, CONTRIBUTING (with the AI-conduct section), `.clang-format` and a `make format` snippet |
| **The tools manifest** (`tools/MANIFEST.md`) | the portable tools of the source project by phase — what each does and what it hard-codes — as Phase-1 tasks (see below) |

## What it does NOT install — read this before you expect it to

- **No tools.** The kit installs documents, configuration and the firewall's audit script. It does not install a byte
  gate, a splitter config, a permuter harness, a decompiler context or a differential harness — those are the first
  phases' work, listed in `tools/MANIFEST.md` as tasks with the source project's tool named beside each, until the
  tools are de-specialised and split out of the source project. The installer's SETUP says so in its honesty section.
- **No compiler, no disassembler, no emulator, no dump.** Phase 1–4 work; the ops reference carries `TODO(phase-N)`
  markers where their values will go.
- **Not the private/public decision.** The firewall applies either way; the decision is yours, made at the interview.

## Scope

- **Generic in structure, complete in content for the PlayStation / PsyQ generation.** Where another platform's answer
  differs, the text carries a `TODO(platform)` marker rather than a guess; the kit's lint counts them.
- **Version pin.** The kit overlays **ProjectArchitect 2.0** exactly (its SETUP asserts the version line of the installed
  methodology reference and the presence of the registry and the phase-ends folder) and STOPS otherwise, sending you to
  ProjectArchitect first.
- **New projects only, for now.** An existing decompilation repository (ProjectArchitect's paths B and C) is an explicit
  STOP in this version — the moves it would need are the source project's own consolidation, not yet packaged.
- **Numbers.** The source project's measurements appear only inside ```` ```calibration ```` fences, with "source project"
  as their attribution; everything outside a fence is claimed to transfer to another console and another compiler. A
  lint keeps the kit free of the source project's names, paths and rule numbers.

## Findings for ProjectArchitect (from the kit's dry-run; carried upstream at the split)

- ProjectArchitect's ignore block writes the directory form `.run/`; git never descends into an excluded directory, so no later
  `!` re-include under `.run/` can take effect beneath it. The kit's installer rewrites that one line to the by-contents form
  `/.run/*` as its single named edit above a marker (SETUP Step 3.0); at source the fix is to write `/.run/*` and
  `!/.run/README.md` in the first place.
- ProjectArchitect's leftover-placeholder audit is not scoped past the installer packages' own template bodies, and a
  `.gitignore`-aware `grep` wrapper hides that; the kit's Step 10.1 scopes the audit and says to use a plain grep.
- On a host whose global git ignore hides `.claude/settings.local.json`, ProjectArchitect's checkpoint commit silently leaves it
  out; neither installer names it as intentionally uncommitted.

- ProjectArchitect's close step runs `git mv` on the phase file before the last checkbox edits are staged, so the close commit
  leaves the tree dirty unless the agent notices; its step could say "tick the remaining tasks before the move" (the kit's own
  Step 10 ticks first).

## Package contents

```
decomp-architect/
  README.md                  this file
  intake.decomp.md           ProjectArchitect's intake, pre-answered; the phase ladder; the six inversions
  SETUP.md                   the installer (Step 0 contract … Step 10 verify + hard stop); --answers for unattended runs
  decomp-architect.md        the methodology reference (copied to docs/)
  templates/                 the firewall pack, the READMEs, the overlays, the registry seed, the skeletons, PLACEHOLDERS.md
  corpus/decomp-kernels.md   the kernels and the failure museum
  corpus/tools/<phase>/      the source project's tools, verbatim, with INDEX.md (the need-keyed dictionary)
  corpus/cookbook/           the source project's cookbook, symptom index and codegen map, verbatim, with a front page
  corpus/record/             the source project's how-to, decision log, accelerators, retrospective, playbook, phase-ends…, verbatim, with a front page
  memory-seed/               the memory files and their index rows
  templates/layout-contract.md  a draft of the layout assumptions the portable tools share (for the split)
  tools/MANIFEST.md          the portable tools by phase, as tasks and as a dictionary
```

## License

Part of the repository it ships in until it is split into its own repository after that project's public release; the
split will carry its own license file. Nothing in the kit is derived from any game.
