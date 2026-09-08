# Contributing to {{PROJECT_NAME}}

## Bring your own copy of the game

Every contributor extracts from their own legally obtained copy. Nothing derived from it is committed — no executable,
payloads, disassembly, assets, build output, memory images, database, vendor SDK, or notes that paste the target's
instructions. The `.gitignore` firewall stops the ordinary case; `tools/audit_public.py` refuses the rest and runs in CI
on every push; review `git status` before every commit.

## What "done" means

A function is matched when its compiled output is instruction-identical to the original, register allocation included,
**and** the whole binary's hash check still passes with it linked. "Functionally equivalent" is never done. Unmatched C
lives under the non-matching guard with the assembly stub in the default build. A match is verified from a clean rebuild,
never an incremental one; a pull request states which compilation each claim survived (standalone / the real translation
unit / the whole binary).

## Names, types and formatting

A symbol is renamed only on recorded evidence — a string it prints, a cross-reference chain, a debug menu, a live-memory
datapoint, a community label with provenance. **If you are not sure what something does, leave it unnamed rather than
name it wrongly**; the address-named placeholder is honest and greppable. One definition per structure; a duplicate type
is a defect. Run `make format` before committing (`.clang-format` is the community's style); mark anything that exists
only to force a match with `// !FAKE:` and its reason; mark an original bug with `//! @bug`.

## AI use — conduct

{{AI_DISCLOSURE}}

The rules that keep that honest, for every contributor and every agent:

1. **The byte gate is the only claim of success.** Never report a match the gate has not proven; "it compiled" and "looks
   equivalent" are not results. "Banked" is written from a tool's printed success line.
2. **Names and types are evidence-based, never guessed.** A model may propose a name; a person with recorded evidence asserts
   one. Hallucinated meaning is the specific way a model damages a decompilation without any test catching it.
3. **Outward text is written by a person.** Issues, pull requests, forum posts and outreach to other projects are written
   by their author the way a developer writes — short, plain, from the facts — never a model draft with the tells removed.
   Before contributing to another project, read and follow its own AI-contribution policy.
4. **No automated traffic against community infrastructure.** Shared services are used by a person in a browser; anything
   repetitive is replicated locally.
5. **Agents assist; a person owns.** Every change is justifiable by a person from the record (the phase logs, the decision
   log, the cookbook's byte proofs).

## Submitting

Small, per-function or per-family pull requests; the hash check green on every binary the change touches; the clean
fleet verification for anything that touches a shared body, a shared header or the executable; a commit message that
names what was matched and how it was verified; no AI-attribution trailers.
