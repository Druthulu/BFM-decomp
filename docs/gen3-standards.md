# Standards: accuracy, readability, and the use of AI — the bar this project holds itself to

> **Written 2026-09-07 (P33 S89) at the owner's direction, as the charter document for Gen3.** Two things are true at once about
> this repository: it is the largest fully machine-carried matching decompilation on record, and it is not yet code a human
> maintainer would call finished. This page states the standard on both counts — the accuracy bar already met and held, the
> readability bar Gen3 exists to meet — and the conduct rules for using AI that keep the project from being confused with
> low-effort machine output. The measurements are dated; re-derive them before quoting (R37, R41).

## 1. Accuracy — met, held, and stricter than the field

"Matched" here means one thing: the compiled output is instruction-identical to the original, register allocation included,
**and** the whole binary's SHA1 equals the original's (rule G3). Nothing "functionally equivalent" is ever counted (P9). The
enforcement is structural, not procedural:

| Guarantee | How it is enforced | Where the proof lives |
|---|---|---|
| Every shipped binary is byte-identical | `config/check.*.sha` is checked inside every `make build`; there is no third state between "identical" and "failed" | `docs/verification.md` (the recorded contract run: 218 of 218 from a clean rebuild) |
| No unmatched C in a default build | the `NON_MATCHING` guard (G4); the census reads 0 | `make audit-frontier`, `docs/progress.json` |
| A bank is verified from a clean rebuild, never incremental | R22 after every banked batch; main gated only by `gate_main`'s clean rebuild | the phase logs, `.run/P33/verify/` |
| The measuring instruments are themselves audited | corpus/cdecl/sig oracles in `make tools-health`; a second, disagreeing oracle where one is structurally blind (R34) | `docs/SETUP.md` §6, the P26/P27 audits |
| What is *not* our C is stated, not hidden | 1,256 Sony PsyQ objects linked byte-identical; 5 hand-written assembly routines kept verbatim, censused in `config/verbatim_manifest.json` | `README.md`, `docs/verification.md` |

Most projects gate per function with a diff score and check the whole ROM periodically; here the whole-binary hash runs on
every build of every binary, and a clean rebuild follows every batch. Accuracy is therefore not a Gen3 concern. It is the
floor Gen3 stands on: every edit below is byte-neutral by definition and is rejected the moment it is not.

## 2. Readability — the bar Gen3 meets

The community's expectations are written down; the clearest statement is sotn-decomp's `docs/STYLE.md`, and this project
adopts it as the baseline (read 2026-09-07):

- **Naming:** locals `camelCase`, globals `g_PascalCase`, statics `s_PascalCase`, struct members `camelCase`, types and
  functions `PascalCase`, enum values and macros `SCREAMING_SNAKE_CASE`, files `snake_case`. "Ideally names should be both
  short and clear, although it's better to be clear than short."
- **Types:** the project's own `u8 … u32` types; "We always write our enums and structs as typedefs."
- **Formatting:** clang-format — 4 spaces, 80 columns, braces on the same line, pointer on the type; a blank line between
  declarations and code; braces on every conditional and loop body.
- **Numbers:** decimal for counts, timers and indices; hexadecimal for angles, addresses and masks; `bool` for 0/1 returns;
  "It's better to not hardcode array sizes (easier to mod)."
- **Honesty markers:** `// !FAKE:` on code that exists only to force a match; `//! @bug` on original bugs; a comment wherever
  something is strange.
- **The rule this project ranks first:** *"If you are not sure what something does, it is better to leave it unnamed than name
  it wrongly."*
- **Organisation:** functions in the order of the assembly, in a file that belongs to the system they implement.

To that baseline this project adds four rules of its own, because its code was produced by a machine at scale and the
failure modes are different:

1. **Every name carries evidence.** A function or variable is renamed only on a recorded basis — a string it prints, a
   cross-reference chain, the debug menu, a live-RAM datapoint (R10), a community label with provenance (G5). The evidence is
   recorded the way addresses are recorded in `docs/memory-map.md`. No evidence, no name: it stays `func_80xxxxxx` /
   `D_80xxxxxx`, which is honest and greppable. A model may *propose* a name; it may never *assert* one.
2. **Every register pin goes.** `register … __asm__("$N")` was a matching lever; in finished code each one is either removed
   (the body re-shaped so the compiler allocates naturally — P32 showed every pin in the last drafts came off) or, if a body
   genuinely cannot be shaped, kept with a `// !FAKE:` line that names the residual. The count is a published metric until it is 0.
3. **Shared engine functions live as C, not as macros.** The 5,147 `DEFINE_func_…()` macro bodies in `src/shared/engine_core.h`
   were the dedup engine's way of instantiating one body in every location overlay. A reader expects a `.c` file per system,
   shared the way other overlay-heavy projects share it. The restructuring is byte-neutral and is proven so per family.
4. **Types come from the code, names from observation.** Structure is recovered from access patterns the compiler locked into
   the bytes (many functions reading a `u16` at one offset from one base); meaning comes from observation. The 1,232 struct
   definitions are unified before any field is named; a duplicate type is a defect, a wrong name is a worse one.

Every step is checked the only way this project checks anything: 218 binaries rebuild identical.

## 3. The use of AI — conduct

The project is openly machine-carried and says so in its README; that is the disclosure, made once, at the project level.
The conduct rules below are what keep that fact from being a liability:

- **The byte gate is the only claim of success.** The agent never reports a match the gate has not proven; "the compiler ran"
  and "looks equivalent" are not results (P9). Every "banked" is written from a tool's printed success line (R66).
- **Names and types are evidence-based, never guessed** (§2 rule 1). Hallucinated meaning is the specific way a model would
  damage a decompilation without any test catching it.
- **Outward text is written by a person.** Issues, pull requests, forum posts and outreach to other projects are written by the
  maintainer, the way a developer writes — short, plain, no dense inline-code formatting, no bullet walls, no evidence
  scaffolding — and never a model draft with the tells removed. The model supplies facts. (Rule candidate (j); the lesson cost a
  closed pull request.) Before any submission, the target project's own AI policy is read and followed: sotn-decomp, for one,
  requires that "commit messages and Pull Requests [be] submitted without autonomous tooling such as an LLM or coding agent."
- **No automated traffic against community infrastructure.** decomp.me asks that nobody "scrape the site, hook up an LLM, or
  otherwise make repeated, automated, requests"; the project's decomp.me use is a person in a browser, and its local replica
  (`tools/decompme_replica.sh`) exists so that proofs are run at home.
- **Agents assist; a person owns.** Every change is justifiable by a person from the record (the phase logs, the decision log,
  the cookbook's byte proofs). Governance — the constitution, the two gates per phase, the rule set distilled from failures — is
  what made the machine's output auditable; it stays in force in Gen3.

## 4. The gap, measured (2026-09-07), and the order of work

| Bar (§2) | This tree today |
|---|---|
| Named functions | 1,094 named in the symbol files vs **16,335** `func_80xxxxxx` |
| Named data | **61,898** `D_80xxxxxx` (most are per-overlay script data; many will honestly stay unnamed) |
| Typed structures | **1,232** struct definitions, many drafter-invented variants of one type; **143** raw address casts |
| No match-forcing tricks | **43,857** register pins (`grep -rhoE 'register [^;]*__asm__\("\$[0-9a-z]+"\)' src \| wc -l`) |
| Readable organisation | **5,147** shared bodies as macros in one 8.4 MB, 227,730-line header; **3,558** of 4,287 C files are `_jr_` carve splits |
| Formatting, comments | no `.clang-format`, no `make format`; almost no code comments |

The order, each step gated by the 218 hashes and each sized by a probe before it is priced (R37):

1. **Pins off** — mechanical, batched by function family (`tools/alloc_table.py` + `tools/cc1_dumps_tu.sh` name the
   allocation order; the P32 recipes in cookbook §501 show the reshaping); publish the count as it falls.
2. **Macro bodies → shared C files** — one family first, measured, then the rest; the carve-split file layout regrouped by
   system where the linker script permits.
3. **Struct unification** — cluster the 1,232 definitions by access pattern (`tools/lift_types.py` knows the collision classes),
   one canonical type per shape, then field names only with evidence.
4. **Names with evidence** — the evidence ladder (strings → debug menu → xrefs → live RAM → community labels), recorded per name.
5. **Formatting and comments** — adopt clang-format with sotn's settings; a file-level description per system; `// !FAKE:` on
   every residual.

**Definition of done for Gen3 (proposed; the Gen3 plan ratifies):** 0 pins or each one `// !FAKE:`-marked with its reason; 0
macro bodies; one definition per structure; every renamed symbol with a recorded basis; clang-format clean; and, unchanged,
218 of 218 byte-identical from a clean rebuild.

## 5. Related

`docs/gen3-handoff.md` (the census, the levers, the sequencing against Phase 33) · `docs/verification.md` (the accuracy record)
· `docs/decision-log.md` P33 S89 (the closed pull request and what it taught) · `docs/how-to-ai-decomp/` (the method) ·
`docs/retrospective.md` · sotn-decomp `docs/STYLE.md` and `CONTRIBUTING.md`; decomp.me FAQ; `ser-pounce/rood-reverse` — all
read 2026-09-07 as data (X2).
