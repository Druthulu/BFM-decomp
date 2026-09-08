# BFM-decomp — the wiki

**Brave Fencer Musashi** (Square, PlayStation, 1998; USA release SLUS-00726), decompiled to C that rebuilds every shipped
code binary **byte for byte** with the game's own 1990s toolchain. It is the first public decompilation of the game, and
the whole of its game code is matched: the main executable, the always-resident engine, every location overlay and every
code module streamed from the disc — **218 binaries**, each verified by SHA1 against a redump image of the original disc
on every build. The repository is [github.com/Druthulu/BFM-decomp](../../README.md).

The claim is narrow and machine-checkable: *matching* means byte-identical output, nothing "functionally equivalent"
counts, and what the repository claims is exactly what `make check-all` proves. The live numbers are generated into the
README's progress block and `docs/progress.json`, never typed by hand; at the Phase-33 close (September 2026) all three
metrics — functions, instructions, distinct code — read 100%, with two things deliberately not our C and stated as such:
Sony's PsyQ library objects linked into the main executable (1,256 functions) and five hand-written assembly routines
kept verbatim.

The project was carried out end to end by an AI coding agent (Claude Code) under a written constitution and a two-gate
phase system, in twelve weeks. How that was done — and what it cost — is the second half of this wiki.

**This wiki is the source of truth for the project's documentation.** The records behind it (the cookbook, the decision
log, the memory map, the environment reference) live under `docs/` and are listed, with how to read each one, in the
[Reference index](Reference-index.md); when a page and a record disagree, the record wins and the page gets fixed.

## Using the project

| Page | What it answers |
|---|---|
| [Build from your own disc](Build-from-your-own-disc.md) | The six-command recipe, what each step proves, the expected last lines, what to do when one fails |
| [Toolchain setup](Toolchain-setup.md) | The pinned compiler/assembler triple and why it is pinned; every tool version; the optional Sony SDK; Ghidra and the emulator |
| [Repository layout](Repository-layout.md) | What every top-level directory holds, and what is deliberately *not* in the repository |
| [The matching workflow](The-matching-workflow.md) | Draft → gate → bank: the oracle ladder from a masked standalone compile to the whole-binary hash, and how a change is kept honest |
| [The dedup engine](The-dedup-engine.md) | Why one matched function banks up to 138 copies: position-locked overlays, signatures, propagation, the registry that fail-closes |
| [Overlays and modules](Overlays-and-modules.md) | The disc, the 218 binaries, where each loads and how every load address was proven |
| [Ghidra rebuild from text](Ghidra-rebuild-from-text.md) | The reverse-engineering database is not in git; here is how it regenerates from text + the disc, and the proof that it does |
| [Verification and progress](Verification-and-progress.md) | The contract run, the three metrics and how they are computed, what CI proves without a disc, the published numbers |
| [Contributing and the no-ROM policy](Contributing-and-the-no-ROM-policy.md) | What may never enter the repository, what a useful contribution looks like now that the frontier is empty, the AI-use conduct rules, the license split |
| [Tools from this project](Tools-from-this-project.md) | xsig, the permuter driver, the codegen map, the decomp.me replica, the drafter write-up — what stands on its own for other projects |
| [Start a new decomp project](Start-a-new-decomp-project.md) | The day-one kit for the next decompilation: the three install steps, what it installs and does not (the two dictionaries), the phase ladder, the conduct rules, the six inversions, every accelerator in one line, the four dry-runs that prove it |

## Working conventions

| Page | What it answers |
|---|---|
| [Docs and scratch conventions](Docs-and-scratch-conventions.md) | Where each kind of knowledge goes, which files are generated, how links are checked, what the archive is, what may be tracked under `.run/` |
| [The ROM firewall](The-ROM-firewall.md) | The rule with no private exemption, the nine classes of ROM-derived content, a copyable `.gitignore`, the audit and CI, what a history rewrite costs |

## Reference

The [Reference index](Reference-index.md): every live reference and generated file under `docs/` — the environment
reference, the formats and the memory map, the cookbook and the codegen map, the progress files, the releases, the record,
the Gen3 inputs — with what each is, how to read it and who writes it.

## How to AI-decomp

[How to AI-decomp](How-to-AI-decomp.md) — the transferable part: thirteen chapters on running a byte-exact decompilation
with AI agents, written from this project's records for the next one (any console, any compiler). Governance, the byte
gate, the bootstrap order, oracles and instruments, cards/lanes/waves, the knowledge base, reading the compiler's source,
models and budgets, the economics as measured, integration and propagation, publishing, and a museum of the failures
that looked right at the time.

## Where the project goes next

[Where the project goes next](Where-the-project-goes-next.md): the flip and the Gen2 exit (Phase 34), then Gen3 —
readability on a byte-exact floor: the style bar, the measured gap, the one invariant, the order of work, the levers.

## History

The narrative and the retrospective are in the Reference index (`docs/story.md`, `docs/story-timeline.md`,
`docs/retrospective.md`); the phase-by-phase record is `phase-ends/` ([Repository layout](Repository-layout.md)); the
documents that served one phase and were then retired are in the [Archive index](Archive-index.md), each with what came
of it and where its information lives now.

*Brave Fencer Musashi is © 1998 Square. This project is not affiliated with or endorsed by Square Enix. `src/` asserts no
license ([`src/NOTICE.md`](../../src/NOTICE.md)); the project's own tools and documents are AGPL-3.0 ([`LICENSE`](../../LICENSE)).*
