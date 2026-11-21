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
| What is *not* our C is stated, not hidden | 1,256 Sony PsyQ objects linked byte-identical; the hand-written assembly routines kept verbatim, censused in `config/verbatim_manifest.json` (5 at the Phase-33 close; 27 since the Phase-36 census of 2026-09-09, which found the in-function form of the lane) | `README.md`, `docs/verification.md` |

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
   **Amended 2026-10-17 (developer): best guesses are named, marked.** A name without that evidence is allowed as a
   best guess under the `guess_` prefix (`guess_MutateHp`, `guess_PlayerState`, field `guess_hp`), each with a names-ledger
   row: basis, confidence (low/medium/high), evidence kind (code inference, string, xref chain, debug menu, live RAM,
   community label), a conflict flag naming any contradicting evidence, and the name's history. Confidence lives in the
   ledger, never in extra name prefixes. `guess_` always means "our best guess so far"; `unk`/`Unkstruct_`/`func_` keep
   meaning "nothing known". A guess loses the prefix only when evidence above is recorded, and is renamed freely as the
   picture grows. This keeps the baseline rule: a marked guess does not claim to be sure.
   **Amended 2026-11-10 (developer, at the 3.43 plan approval): "Add the seventh evidence kind 'library symbol' to
   docs/gen3-standards.md rule 1 and the scanner's closed list."** A name defined by a linked PsyQ library object (the
   build links Sony's objects byte for byte; evidence: the linker map and the object's symbol table) has evidence kind
   `library symbol`, so Sony's own names are cited, never marked as guesses. The evidence kinds are now seven.
   **Adopted 2026-11-10 (developer, at the 3.43 T7 review): the naming conventions in
   [`docs/wiki/Names-and-renames.md`](wiki/Names-and-renames.md) bind every naming batch.** A name is cited only when its
   meaning comes from a recorded source (library symbol, game string, debug menu, live RAM at G5, a G5-verified community
   label); every name a model words from reading the code is `guess_`, whatever its confidence; `guess_` is the outermost
   prefix (`guess_g_X`), so stripping it gives the confirmed name; a basis quotes code facts with their lines.
2. **Every register pin goes.** `register … __asm__("$N")` was a matching lever; in finished code each one is either removed
   (the body re-shaped so the compiler allocates naturally — P32 showed every pin in the last drafts came off) or, if a body
   genuinely cannot be shaped, kept with a `// !FAKE:` line that names the residual. The count is a published metric until it is 0.
3. **Shared engine functions live as C, not as macros.** The 5,147 `DEFINE_func_…()` macro bodies in `src/shared/engine_core.h`
   were the dedup engine's way of instantiating one body in every location overlay. A reader expects a `.c` file per system,
   shared the way other overlay-heavy projects share it. The restructuring is byte-neutral and is proven so per family.
4. **Types come from the code, names from observation.** Structure is recovered from access patterns the compiler locked into
   the bytes (many functions reading a `u16` at one offset from one base); meaning comes from observation. The 1,232 struct
   definitions are unified before any field is named; a duplicate type is a defect, a wrong name is a worse one.
   **Amended 2026-11-13 (developer, the Phase 3.45 replan, R182/R184): the bar is the SOTN decomp — organized structs.** His
   words: "i want our code base up to the standards of sotn, human readable and modder useful, organized structs, no
   unnecessary casts if we dont need it." So: **one real struct per real object** the game owns (a global or static, an
   array element, an allocation every use of which is that type, a member of another real type, a value handed to the SDK);
   **variant data lives inside its parent** as an overlay or union (SOTN's `Entity.ext.<variant>`), never as a separate
   fragment struct viewed through a cast; fields may stay `unkNN` inside a real struct, fragment structs may not. Every
   placeholder type ends in exactly one disposition (`config/struct_dispositions.tsv`, gated by
   `tools/struct_twins.py --dispositions --check`): **fold** into a target (class `link`: a shared global, pointer or routine
   copy, the 3.45 T2 evidence; `twin`: an exact layout twin of 3+ fields, G62 as amended; `value`: a small dense value shape,
   onto its PsyQ type where one fits), **absorb** into its real parent (at its offset, or in the parent's variant overlay or
   union; per pointer source when a type's sources point to different parents), **survivor** (a real root type, its object
   cited; a type seen only through views of another type's objects is never a survivor), **scalar** ("not a struct", class
   `text`|`scalar`: the object is shown not to be a record, so its sources are retyped to the true scalar type and the
   placeholder deleted, the data object and retyped sources cited; never a way to finish a hard struct) or **wall** (a fold, absorption or
   retype the byte gate refused after its second attempt up the lever ladder, with object, offset, residual class and both
   attempts). `apart`, `no-evidence` and `undisposed` are pending, not finishes. Why: 3.40 gave each union-find cluster of
   raw-cast bases its own definition, so one real type split into many wherever no edge joined its uses (4,112
   placeholders at 3.45 T1, against SOTN's ~1,280 types for a larger game); a reader and a modder need the one object.
   **Worked example: the actor (3.45 T16, the parent model for variant data).** The game keeps its objects in typed pools:
   each slot holds its type at +0x0 (`u16`, the index into the overlay's handler table: the pool walker
   src/shared/ov/func_8017849C.h:15-35 calls `D_8011DB08[slot->unk0] (slot)`) and a per-type state at +0x2. The actor
   slot is `Unkstruct_801202A0` (0x10C; `guess_g_ObjectTable` 0x801202A0 x 96; spawn scan src/shared/ov/func_8012C658.h:8-48).
   Its **common fields are flat**: what the spawn init (src/shared/ov/func_8012C890__1bddfa15.h) and the shared helpers
   (func_8012A828.h, func_8012B23C.h, func_8012C354.h) write: type, state, s32 position (a fixed-point union, `.val` and
   `.i.hi`, because the shipped code reads the word and its integer half), velocity, the render pointer at +0x20, parent at
   +0x64, flags, sequence. The **per-kind data does not form one tail** (unlike SOTN's `Entity.ext`): it sits in four gaps
   between common fields (0x24-0x34, 0xA0-0xD4, 0xE0-0xF8, 0x100-0x10A), so each gap is a **named union of per-kind variant
   structs** (`extA`..`extD`; cc1 has no anonymous unions), one variant per kind, named by its owning handler
   (`kSC05_007_8017E7D0`), a copied body in several overlays sharing one variant; a view reading common fields only absorbs
   at +0x0 with no variant. Access: `a0->extC.kSC02_005_80181BE8.unkE8`. A width or sign the kinds disagree on at a
   common offset is a named union there (`unk2.u`/`.s`). Other pools follow the same shape (sprite record
   `Unkstruct_800B5BD8` 0x38 at RenderWork+0x65A8, model record `Unkstruct_8001C9D0` 0x84, fx `Unkstruct_8011DB30`, small
   object `Unkstruct_8011D030`); the player (`Unkstruct_80126B58`, 0x254 at 0x80126B58) is its own root object sharing only
   the 0x0-0x24 prefix layout. A placeholder named after an address is checked against the pools first: `Unkstruct_800B5CB8`
   was named after sprite record #4 and merged the actor, sprite and model records (C0624); it is split per source.
5. **Every raw cast goes, or names its cause.** (Phase 39 T2, 2026-10-01.) A `*(T *)(p + k)` is a member access the drafter
   could not spell; finished code spells it as the member. Where the byte gate refuses the member (cookbook §458: `/s` moves
   the scheduler), the cast is kept through ONE of the kept-cast macros in `include/common.h`, each expanding to the identical
   cast and naming one cause class — `CAST_ALIAS` SCHED-ALIAS, `CAST_SIGN` SIGN, `CAST_WIDTH` WIDTH (overlap loser),
   `CAST_MISALIGNED` MISALIGNED, `CAST_NONSTRUCT` NON-STRUCT base, and `LOBU/LOH/HIH/LOHU/HIHU/LOW/LOWU` REINTERP (an lvalue
   read at another width or sign). A macro site is honest only with its restruct ledger row (rung S, site verdict
   `KEPT(<class>)`, keyed tu + function per R99); `tools/type_census.py --check-casts` counts raw sites by form, macro sites
   by name against the ledger, and lying declarations against `config/lying_exceptions.tsv`, and fails on any raw site, any
   unbacked macro site or any unledgered lie; with `--residue` (the form `make tools-health` runs, 3.41 T5) a raw site
   passes when a ledger entry `RESIDUAL(<cause>)` covers it. `M2C_FIELD` is a raw form, never a kept spelling. Each macro's byte proof (one
   kept site respelled, `make check` BYTE-IDENTICAL) is recorded in the Phase 39 T2 summary. Levers follow the same reading:
   `tools/lever_census.py --strict --residue config/lever_residue.tsv` is the gate, the residue file the ledger of what stays.
   **Amended 2026-11-13 (developer, the Phase 3.45 replan, R182/R184): no cast the shipped game does not need.** Pointers
   are typed at their source (the parameter, global, local or return), so a struct-view cast `((T *)p)->f` becomes `p->f`
   and a raw pointer-arithmetic cast becomes a field access. A cast stays only as one of: a kept-cast macro with its restruct
   `KEPT` row (the bytes refuse the member), a reinterpretation row (the shipped game reads one pointer as two types and no
   overlay or union inside the parent reproduces the bytes; both views cited), or a wall (refused after the second attempt up
   the ladder, G57). The `RESIDUAL` causes the census stamps (FILE-SCOPE, NO-TYPE-IN-MAP, TYPE-NOT-CANONICAL,
   TYPE-NOT-VISIBLE, ABS-ADDR, GADDR, GLOBAL) are tooling states, not reasons the game needs a cast: under this bar each such
   site is pending. And the habit the developer named ("doing some work, then giving up and accepting not finishing the
   work… a bad habit and I want to fix it"): **a ledger row is a finish only for a byte-proven wall.** SOTN, for scale:
   about 7,783 struct-pointer casts and 5 raw pointer-arithmetic casts across 3,362 files; its entity code takes
   `Entity *self` and reads `self->ext.<variant>.field`. The gate (3.45 T8) is `tools/struct_twins.py --gate` in
   `make tools-health`: it fails on a broken disposition row (a fold or absorption whose member is still defined, a survivor
   without its root object cite, a wall without both attempts and its DIFF, a cite that no longer holds) and on any count
   above or below its committed ratchet `config/consolidation_ratchet.tsv` (pending types; unledgered casts by form;
   pending DECL-PARAM rows); each batch lowers the ratchet in its own commit (`--write-ratchet`); `--gate --final` (T30,
   T11) fails on any pending type or unledgered cast. Kept casts outside the macros are rows of `config/cast_views.tsv`.
6. **Every prototype agrees with the bytes.** **Adopted 2026-11-10 (developer, at the 3.44 plan; R115).** Every function
   declaration and definition agrees with its contract as measured from the original machine code by the asm census
   (`tools/sig_evidence.py`: whether callers read the return, how many arguments the body reads and callers set, width and
   sign), or carries an exception whose cited instructions the tool re-verifies against the bytes. One prototype per
   function (the definition's); where the shipped game called a function inconsistently, a marked cast at that call
   (`RET_AS`, `KR_AS`) with its ledger row. The gate is `tools/sig_evidence.py --check` in `make tools-health` (3.44 T9): 0
   unledgered disagreements, 0 failed cites, 0 unused exceptions. Since 3.45 T8 (R179) that includes parameter types
   (DECL-PARAM): a declaration's struct parameter names its definition's type, and a word against a struct pointer is a
   disagreement. Rules, unknown reasons and the ledger format:
   [`docs/ops/sig-evidence.md`](ops/sig-evidence.md).

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
| No match-forcing tricks | **43,925** register-pin declarations (snapshot 2026-09-07: `grep -rhoE 'register [^;/]*__asm__\("\$?[a-z0-9]+"\)' src --include=*.c --include=*.h \| wc -l` — 43,857 in the `"$reg"` form + 68 in the bare `"reg"` form; 42,985 in `.c`, 940 in `.h`; the same command and number as `gen3-handoff.md` §3 — re-derive, do not trust) |
| Readable organisation | ~~**5,147** shared bodies as macros in one 8.4 MB, 227,730-line header~~ → **0** at Phase 35 (2026-09-08, `git grep -c "^#define DEFINE_func_" -- src` empty; 3,173 per-function headers under `src/shared/`, S1 asserted by `tools/share_census.py --check`); **3,558** of 4,287 C files are `_jr_` carve splits |
| Formatting, comments | no `.clang-format`, no `make format`; almost no code comments |

The order, each step gated by the 218 hashes and each sized by a probe before it is priced (R37):

1. **Pins off** — mechanical, batched by function family (`tools/alloc_table.py` + `tools/cc1_dumps_tu.sh` name the
   allocation order; the P32 recipes in cookbook §501 show the reshaping); publish the count as it falls.
   *Phase 36 (2026-09-09 → 2026-09-11): 53,234 → 4,010 sites (−92.5 %), 218/218 at every step; the rungs and their yields are in
   `docs/levers.md`, the moves in cookbook §454–§457; the 4,010 survivors are marked with their pass and named for the structs phase.*
2. **Macro bodies → shared C files** — one family first, measured, then the rest; the carve-split file layout regrouped by
   system where the linker script permits.
3. **Struct unification** — cluster the 1,232 definitions by access pattern (`tools/lift_types.py` knows the collision classes),
   one canonical type per shape, then field names only with evidence.
4. **Names with evidence** — the evidence ladder (strings → debug menu → xrefs → live RAM → community labels), recorded per name.
5. **Formatting and comments** — adopt clang-format with sotn's settings; a file-level description per system; `// !FAKE:` on
   every residual.

**Definition of done for Gen3 (proposed; the Gen3 plan ratifies):** 0 pins or each one `// !FAKE:`-marked with its reason; 0
macro bodies (**met at Phase 35**); one definition per structure; 0 raw casts, every kept cast a `CAST_*`/`REINTERP` macro
site with its ledger row (`type_census --check-casts` green, Phase 39 T2); every renamed symbol with a recorded basis; clang-format clean; and, unchanged,
218 of 218 byte-identical from a clean rebuild.

## 5. Related

`docs/gen3-handoff.md` (the census, the levers, the sequencing against Phase 33) · `docs/verification.md` (the accuracy record)
· `docs/decision-log.md` P33 S89 (the closed pull request and what it taught) · `docs/how-to-ai-decomp/` (the method) ·
`docs/retrospective.md` · sotn-decomp `docs/STYLE.md` and `CONTRIBUTING.md`; decomp.me FAQ; `ser-pounce/rood-reverse` — all
read 2026-09-07 as data (X2).
