# BFM-decomp — the wiki

**Brave Fencer Musashi** (Square, PlayStation, 1998; USA release SLUS-00726), decompiled to C that rebuilds every shipped
code binary **byte for byte** with the game's own 1990s toolchain. It is the first public decompilation of the game, and
the whole of its game code is matched: the main executable, the always-resident engine, every location overlay and every
code module streamed from the disc — **218 binaries**, each verified by SHA1 against a redump image of the original disc
on every build. The repository is [github.com/Druthulu/BFM-decomp](../../README.md).

The claim is narrow and machine-checkable: *matching* means byte-identical output, nothing "functionally equivalent"
counts, and what the repository claims is exactly what `make check-all` proves. The live numbers are generated into the
README's progress block and [`docs/progress.json`](../progress.json), never typed by hand; at the Phase-33 close
(September 2026) all three metrics — functions, instructions, distinct code — read 100%, with two things deliberately
not our C and stated as such: Sony's PsyQ library objects linked into the main executable (1,256 functions) and five
hand-written assembly routines kept verbatim.

The project was carried out end to end by an AI coding agent (Claude Code) under a written constitution and a two-gate
phase system, in twelve weeks. How that was done — and what it cost — is the second half of this wiki.

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
| [Contributing and the no-ROM policy](Contributing-and-the-no-ROM-policy.md) | What may never enter the repository, what a useful contribution looks like now that the frontier is empty, the license split |
| [Tools from this project](Tools-from-this-project.md) | xsig, the permuter driver, the codegen map, the decomp.me replica, the drafter write-up — what stands on its own for other projects |

## How to AI-decomp

[How to AI-decomp](How-to-AI-decomp.md) — the transferable part: thirteen chapters on running a byte-exact decompilation
with AI agents, written from this project's records for the next one (any console, any compiler). Governance, the byte
gate, the bootstrap order, oracles and instruments, cards/lanes/waves, the knowledge base, reading the compiler's source,
models and budgets, the economics as measured, integration and propagation, publishing, and a museum of the failures
that looked right at the time.

## The records behind the wiki

Everything here is a summary of files kept *as it happened*; when a page and a record disagree, the record wins.

- [`docs/story.md`](../story.md) — the narrative, first commit to public flip; [`docs/retrospective.md`](../retrospective.md) — what we believed, what failed, what it cost
- [`docs/matching-cookbook.md`](../matching-cookbook.md) (some 500 compiler idioms, each byte-proven; grep it by section — it is 3.5 MB) and its symptom index [`docs/cookbook-index.md`](../cookbook-index.md); [`docs/gcc-2.7.2-map/`](../gcc-2.7.2-map/) — the codegen map of the pinned compiler, by pass
- [`docs/decision-log.md`](../decision-log.md) — every strategic pivot with its measurement and its hindsight; [`docs/accelerators.md`](../accelerators.md) — what would have made earlier phases faster
- [`phase-ends/`](../../phase-ends/) — one PhaseEnd per phase, the digest of every phase and every rule ([`DIGEST.md`](../../phase-ends/DIGEST.md)), the per-phase logs
- [`docs/SETUP.md`](../SETUP.md) — the environment reference, every tool's row; [`docs/verification.md`](../verification.md) — the contract and the last recorded run
- [`docs/memory-map.md`](../memory-map.md) and [`docs/formats.md`](../formats.md) — addresses with provenance; the disc, container, archive and LZSS formats

*Brave Fencer Musashi is © 1998 Square. This project is not affiliated with or endorsed by Square Enix. `src/` asserts no
license ([`src/NOTICE.md`](../../src/NOTICE.md)); the project's own tools and documents are AGPL-3.0 ([`LICENSE`](../../LICENSE)).*
