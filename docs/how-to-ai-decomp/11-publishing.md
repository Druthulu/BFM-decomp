# 11 — Publishing: keep the bytes out from the first commit

## The one decision to make on day one

**Keep ROM-derived bytes out of git from the first commit, even while private.** BFM relaxed that rule while the
repository was private ("accidental inclusion is not a violation; a scrub before going public") and paid for it with a
full-history rewrite: about two sessions of tooling, two rehearsals, an archive repository, a force-push, a GitHub
Support ticket and a daily probe. "ROM-derived" is wider than the executable: the extracted payloads, the disassembly,
memory dumps, the **reverse-engineering database** (a Ghidra project embeds the program's bytes under a page XOR mask),
the vendor SDK, session transcripts that quote disassembly, re-downloadable extension archives, and compiled tool
binaries. Decide the public/private boundary on day one, and **cite commits by date and subject in long-lived documents,
never by hash alone** — a rewrite changes every hash.

## If you must rewrite history anyway

BFM's procedure ([`docs/public-flip-runbook.md`](../public-flip-runbook.md); the tools under `tools/public_rewrite/`)
is the worked example. What made it safe:

1. **One purge set, one file**, read by the rewrite *and* by the public-clean audit, so the two can never disagree.
2. **A scan of every blob reachable from every ref** — by path, by content hash against the derived ROM-hash set
   (the extraction manifest + every per-binary contract), by byte signature, by size — with an **expected-offenders
   fixture as the negative control**: the scan passes only when it fails naming exactly the known set.
3. **Inert tokens in history, real hashes at the tip.** A new hash can never be written into a historical blob (it
   would change every descendant hash), so every old hash cited in history becomes `commit:NNNN` (the commit's
   ordinal), a public ordinal→new-hash map is committed, and one tip commit resolves the tokens in the current
   documents. Prefixes are asserted unambiguous; content-hash collisions are excluded.
4. **The archive is created EMPTY** — never a fork or an import, which share the host's object store — and receives the
   unrewritten history before the rewrite; a local bundle holds it too.
5. **Rehearse on a scratch copy, then prove pair by pair with POSITIVE assertions.** The first trial caught a defect a
   single run would have shipped: the empty blob's id was in the strip list, so every "file emptied" change in 4,000
   commits was silently undone. The second caught that a byte-identical commit keeps its hash and trips an old-hash
   assertion. The pairwise proof checks, for every (old, new) commit: identities, both timestamps, message ==
   scrub(old), parents with the pruned commit spliced out, every changed blob re-derived as hash(scrub(old)), every
   removal justified, *no purge path survives in any new tree*, and the pruned set equals the derived purge-only set.
6. **Adopt, then verify the contract again** — a content-preserving rewrite changes no tracked byte, and the clean
   fleet run on the adopted tree proves it.
7. **Before the gc, audit `git worktree list`.** Twelve forgotten gate worktrees (12 GB, each a full old-history
   checkout) kept 3,729 old commits reachable; a linked worktree's HEAD is a ref.
8. **The host keeps serving force-pushed-away objects until it purges them.** Gate the visibility flip on a probe that
   asks the API and a fetch for sampled old hashes and expects both to fail — and run that fetch in a **throwaway
   scratch repository**: a successful fetch of an old hash imports its whole closure back into whatever repository
   runs it (found the hard way, 5.9 GB; R57).
9. **Afterwards:** the purged paths are ignored-but-present on the maintainer's disk — *never `git clean -x`*; other
   clones reset to the new history and never `git pull` (an 8,000-commit merge of two lineages).

## The contract, recorded

Publish the proof, not the claim: one script that runs the whole verification (toolchain preflight → the clean fleet
rebuild → the with/without-vendor-objects dual → the health check with both boundary oracles → the disc audit → the
report) writing one log per step ending in `EXIT=<rc>` and a timestamp, aborting on the first non-zero, with a summary
table that is pasted into the verification page — never typed. Re-run it after every banked batch and on the published
tree.

## Numbers are generated, never typed

The progress JSON (every metric with numerator and denominator, the counts, a row per binary; no run date, so a
regeneration never churns), the README's progress block rewritten between two markers, the badge endpoints, the
objdiff report for a progress site, the timeline reconstructed from every commit that touched the digests — all
written by tools, all asserted fresh by the health check. A wrong number in a README is a small lie that lasts for
years; a generator cannot tell one.

## The stranger's build

The README's "verify it yourself" criterion is literal: a fresh clone, a bootstrap script (apt presence check that
prints the install line, the venv, the submodules, the checksummed vintage-compiler tarballs), the disc extraction
compared against the committed manifest (a Track-1-only dump gets an explicit PARTIAL verdict, never a silent pass), and
the clean fleet run — proven on a fresh clone **without** the vendor SDK (218/218 in 4 min 18 s). The vendor objects are
optional, user-supplied and checksummed, and a `dual` target proves the executable is byte-identical with and without
them. Absolute include paths were the one thing that would have broken a stranger's build; an audit class now refuses
them.

## What CI can prove without the ROM

Audits (the public-clean scan on every tracked file; every source text with portable includes; the verbatim-assembly
manifest without drift; derived indexes fresh; the decoder's unit tests; no stale symbol references) and
**compile-only** (every eligible translation unit through the pinned compiler with the build's exact flags — a PR
scope of a few representative binaries in a minute, the whole fleet weekly). CI cannot compare bytes to the originals;
say so in the workflow header and the README.

## Regenerable reverse-engineering artifacts

The RE database's hand-authored part as text (a baseline-subtracted export), with a rebuild script that regenerates
the program from the disc + the symbol files + that text and *proves* it equal (a mutated row must FAIL; a synthetic
row must round-trip). The memory dumps stay local with a checksum file recording their identity. What is tracked is
what a stranger can regenerate; what is not is what only a disc can produce.

## Licenses and words

The project's own work (tools, docs) under a copyleft license; the reimplemented game code under a NOTICE that asserts
**no license** and acknowledges the copyright; every third-party component's license read from *its* source of truth
(its LICENSE file or the host's license metadata — two upstreams published none, and the table says so); the vendor SDK
never distributed. One phrase never used: "clean-room" — the source was derived from the binary.

## The documentation set, and its checker

A README whose numbers are generated; a verification page; the story and the retrospective assembled from the records
with `file:line` anchors; a wiki **authored in the repository** (link-checked, covered by the rewrite) and pushed by a
script that rewrites relative links into page names and refuses a dead one; a relative-link checker in the health check
with a *pending list* — a document may promise a page a later task of the same phase writes, but the promise is
tracked, and the phase cannot close while any entry remains.

## Releases worth separating

The codegen map with its citation audit; a cross-project signature tool with a fixture that contains no game bytes; the
masked-scorer improvement offered upstream to the permuter (declined: the maintainer keeps the wildcard rule and prefers symbol renames in the asm, and he read the model-drafted text as LLM-written — write outward text the way a developer writes an issue, short and plain, rewritten from the facts rather than a model draft with the tells removed; failure museum row 37); the drafter-pipeline write-up (the paired dataset of
disassembly and matched C is ROM-derived and stays private); a decomp.me preset for the pinned compiler; a note to the
neighbouring community project whose RAM map cited yours.

## Rules this chapter proposes (recorded for the PhaseEnd)

- No ROM-derived bytes in **any** published artifact — test fixtures, JSON, badges and reports included.
- Published numbers are generated, never typed (R51 applied to documents).
- Rehearse every irreversible repository operation on a scratch copy and prove it pair by pair with positive assertions.
- A linked worktree's HEAD is a ref — audit `git worktree list` before any gc or purge.
- A checker that widens its document set must classify a missing *promised* page as pending, never broken.
