# Contributing, and the no-ROM policy

## What may never enter the repository

Nothing derived from the game: no executable, no disassembly, no assets, no memory image, no extracted payload, no
vendor SDK. Symbol names, addresses, hashes and configuration are fine (the sotn-decomp precedent). The rule is enforced
three ways:

1. **The ignore firewall** — `disks/`, `extracted/` (except the manifest), `asm/`, `assets/`, `build/`, `expected/`,
   `ghidra/`, `dumps/*.bin`, `tools/psyq/` are ignored, and the tracked preset headers are the only files `make clean`
   leaves behind.
2. **The audit** — [`tools/audit_public.py`](../../tools/audit_public.py) refuses any tracked file whose SHA1 appears in
   the 1,801-row extraction manifest or in any binary's contract, any file under a purged path, and anything over 50 MiB.
   It runs in CI on every push and pull request, and as the first-push gate before the repository went public. (One
   subtlety it had to learn: two zero-length disc payloads share the empty file's SHA1, so empty files are exempt by
   content, not by name.)
3. **The history** — the repository was private for its first three months and carried game-derived files then; before
   publication every revision was rewritten to remove them, proven pair by pair, and force-pushed. The procedure and its
   controls are in [`docs/public-flip-runbook.md`](../public-flip-runbook.md). Do not reintroduce what it removed.

The policy in full — the nine classes of ROM-derived content (the executable is the obvious one; the reverse-engineering
database, transcripts that quote disassembly and a pasted instruction listing are the ones people miss), the copyable
`.gitignore`, the audit's design and its content check, and what a history rewrite costs — is
[The ROM firewall](The-ROM-firewall.md). If you are unsure whether something is ROM-derived, open an issue first.

## What a useful contribution looks like

The matching frontier is empty, so new matches are not the need. The work that helps most:

- **Readability** — structs in place of raw `(*(s16 *)0x800A4ED4)` casts, names in place of `func_80144B9C`, types in
  place of `s32` everywhere. The starter census at the Phase-33 close: about 143 raw address casts, 61,898 distinct
  `D_80xxxxxx` data symbols, 16,335 distinct `func_80xxxxxx` names, 1,092 curated names. The levers that already exist
  are the type-lift, call-site cast and canonical-signature tools under `tools/`; the constraint is below.
- **Shiftability** — a build whose addresses can move; the LZSS repack (recompression is not byte-stable, so this is a
  Gen3 problem) and asset tooling.
- **Tooling and documentation** — every tool has a row in [`docs/SETUP.md`](../SETUP.md)'s inventory; a tool change
  ships with its siblings wired to use it and its docs in the same change.

## AI use — conduct

The project was carried out by an AI coding agent and says so once, at the project level; that is the disclosure. What
keeps it from being a liability is a short set of conduct rules, which apply to any contribution made with an agent's
help (the charter is [`docs/gen3-standards.md`](../gen3-standards.md) §3; the direction they serve is
[Where the project goes next](Where-the-project-goes-next.md)):

1. **The byte gate is the only claim of success.** No match is reported that the gate has not proven; "the compiler ran"
   and "looks equivalent" are not results, and every "done" is written from a tool's printed success line.
2. **Names and types are evidence-based, never guessed.** A function or variable is renamed only on a recorded basis — a
   string it prints, a cross-reference chain, the debug menu, a live-RAM datapoint, a community label with provenance. No
   evidence, no name: `func_80xxxxxx` is honest and greppable. A model may propose; it may never assert.
3. **Outward text is written by a person.** Issues, pull requests, posts and notes to other projects are written by the
   maintainer the way a developer writes — short and plain — never a model draft with the tells removed; and the target
   project's own AI policy is read first (sotn-decomp, for one, requires pull requests made without autonomous tooling).
4. **No automated traffic against community infrastructure.** decomp.me asks that nobody scrape it or hook an LLM to it;
   the project's use of it is a person in a browser, and its local replica of that toolchain exists so proofs run at home.
5. **Agents assist; a person owns.** Every change is justifiable by a person from the record — the phase logs, the
   decision log, the cookbook's byte proofs.

## The one invariant

Every change to `src/`, `config/` or `include/` is held to the byte gate: `make check BINARY=<alias>` stays green for
every binary the change touches, and the clean fleet run stays **218 passed, 0 failed of 218**. A rename is a symbol-file
change mirrored into Ghidra, never a hand edit of generated assembly (rule G6); a shared body edited in `src/shared/`
changes every member, so the fleet run follows. The gate is what makes readability work safe: a wrong edit cannot land.

Two conventions from the project's own rules that apply to any pull request:

- **Read the exit code, not the output file** (R53) — a failed build leaves the previous binary in place.
- **A clean rebuild is the verdict** (R22) — incremental builds have reported false results on the main executable, whose
  extract step rewrites its linker script.

## The pull-request flow

1. Branch; make the change; run the affected binaries' `make extract BINARY=… && make check BINARY=…` and, for anything
   touching shared code or the main executable, the clean fleet run.
2. Push. CI runs the public-clean audits and compiles every eligible translation unit with the pinned toolchain (four
   representative binaries per PR, about a minute). CI cannot verify bytes; say in the PR which binaries you verified
   locally and quote the `check-all` line.
3. If the change adds or renames a tool, add its SETUP row; if it changes a governing document, keep
   [`tools/doc_links.py`](../../tools/doc_links.py) green (it is in `make tools-health`).

## Licenses

`tools/` and `docs/` — the project's own work — are AGPL-3.0 ([`LICENSE`](../../LICENSE)). `src/` is a reimplementation
of copyrighted game code provided for study and preservation; **no license is asserted** over it
([`src/NOTICE.md`](../../src/NOTICE.md)), and distributing compiled output is distributing the game's code — don't.
Third-party components keep their own licenses ([`THIRD_PARTY.md`](../../THIRD_PARTY.md)); the Sony SDK is never
distributed.

## For maintainers with the local-only directories

The purged paths (the Ghidra project, the dumps, the SDK, the disc) are ignored-but-present on a maintainer's disk.
**Never `git clean -x` or `git clean -fdx` in this tree** — it deletes the reverse-engineering database. `make clean` is
the only clean; the Ghidra text export plus [`tools/ghidra_rebuild.sh`](../../tools/ghidra_rebuild.sh) `--proof` is the
backup. The private archive of the pre-rewrite history exists for the owner's recovery only and is never re-added as a
remote of the working repository.

## Running the AI workflow yourself

The project was carried out by an AI coding agent under a written constitution ([`PROJECT_CONTEXT.md`](../../PROJECT_CONTEXT.md)),
a session protocol ([`CLAUDE.md`](../../CLAUDE.md)) and a rule set that grew to 83 numbered rules. All of it is public
and the framework is published separately as [ProjectArchitect](https://github.com/Druthulu/ProjectArchitect). The
transferable part — how to run a byte-exact decompilation with agents — is [How to AI-decomp](How-to-AI-decomp.md).
