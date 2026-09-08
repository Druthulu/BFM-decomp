# Gen3 handoff — where Gen2 ends, what comes next, and the levers already in hand

> **Written at the Gen2 exit (Phase 33, 2026-09-07).** Gen2's contract is met and published: 218 binaries rebuild
> byte-identical from C ([`docs/verification.md`](verification.md)), every game-code function in every binary is C, the
> repository is public with its full rewritten history. This page is the seed for Gen3's first plan — it names the
> owner's stated next intent, gives the starter census derived from the tree (with the commands, so the next session
> re-derives rather than trusts), states the one invariant that must survive every Gen3 edit, and inventories the
> levers, documents and parked ideas Gen3 inherits. The constitution's Gen3 line ("shiftable build, asset repack, native
> recomp / PC port, randomizer-grade tooling") is unchanged; the order below is a recommendation for plan mode.

## 1. Where Gen2 ends

| | |
|---|---|
| Binaries byte-identical | 218 / 218 — the executable, the resident engine, 141 `ov_*` overlays, 75 `md_*` modules |
| Functions | 363,214 / 363,214; 360,737 in C (255,632 shared bodies via 2,220 dedup groups); 1,256 Sony PsyQ functions linked (or carried as 1,258 `INCLUDE_ASM` tiles without the SDK); 5 hand-written-assembly bodies kept verbatim |
| What is not C | Sony's objects (by design) and the 5 verbatim bodies (`config/verbatim_manifest.json`, PERMANENT) |
| The record | `phase-ends/` (33 PhaseEnds + the digest), `docs/decision-log.md`, `docs/matching-cookbook.md`, `docs/gcc-2.7.2-map/`, `docs/story.md`, `docs/retrospective.md`, the wiki and `docs/how-to-ai-decomp/` |

The matching frontier is empty. Gen3's work is therefore of a different kind: **making the C legible and movable
without changing a byte**, and then the things a legible, movable source enables.

## 2. The owner's next intent: readability and shiftability preparation

Stated at the Phase-33 plan: *casts → structs, pins off, names.* Concretely:

1. **Raw addresses → declared data.** Every `*(type *)0x80xxxxxx` cast becomes a reference to a declared symbol with
   a type; every `D_80xxxxxx` that is a field of a known structure becomes `actor->field`.
2. **Register pins off.** Every `register … __asm__("$N")` that a banked body still carries is removed and the body
   re-gated; Phase 32's finding is that the pins were symptoms — every one on the last four functions came off
   byte-identical once the source *shape* was right (cookbook §501-E/P, R73).
3. **Names.** `func_80xxxxxx` / `D_80xxxxxx` → meaningful names, curated in the symbol files and mirrored into
   Ghidra (G6, R15) — never edited in generated assembly.

### 2.1 External labels versus derived structure (owner Q&A, 2026-09-07, P33 E2)

Asked at the E2 outreach: *do the Archipelago world's "structs" let us turn the unknown casts into structs, and do we need
that repository at all, or can we derive the structures from our own decomp?* Answer, recorded for the Gen3 plan:

- **The AP world carries no structs.** `client.py` (v0.8.1) polls ~342 RAM addresses and attaches gameplay meaning to them
  (HP, BP cap, day of week, chest flags, portal entries). That is *labelling for globals* plus the implied layout of a few
  tables. Against the census in §3 it covers ~342 of 61,898 data symbols, none of the 1,232 struct definitions, none of the
  16,335 function names and none of the 43,925 pins. Most of its player-state block is already imported (memory-map §3.4–§3.6).
- **Structure is derived from our own source, and ours is the better instrument for it.** Shape comes from access patterns
  the compiler locked into the bytes: many functions reading a `u16` at `+0x3C` from one base means a struct with a `u16`
  there; Ghidra's decompiler already propagates these; `docs/actor-struct.md` and the load-slot map are recovered examples.
  Every struct/name edit is byte-neutral, so the 218-binary gate rejects any mistake for free (§4).
- **The two sources answer different questions.** The decomp gives the shape (`u16` at 0x80078EB6, written by the
  14-instruction `func_8014BCEC` as `+= a1`, clamped at 0x662); an observer gives the meaning (that is the BP cap). Meaning
  comes from the AP world, our live-RAM harness (R10), string references, the debug menu and community cheat tables. Plan:
  **types and structure from the decomp; names from observation wherever someone already made one, cited (G5).**
- **Ordering caution (census-derived):** most of the 61,898 data symbols are per-overlay script data that may never earn a
  human name; the 1,232 struct definitions include many drafter-invented duplicates of one type — **unify before naming**
  (`tools/lift_types.py` knows the collision classes); pins-off is mechanical and family-batchable; struct unification is
  semi-mechanical (access-pattern clustering, then a person or model names fields); function naming is judgment plus
  evidence (xrefs, strings, the AP names, TCRF/debug-menu strings). Plan Gen3 in that order, and measure each class's
  size before pricing it (R37/R41).

### 2.2 The standard to meet, and where the tree stands against it (measured 2026-09-07, P33 S89)

The owner's aim for Gen3 is stated plainly: *turn a machine-produced matching decomp into a decomp the human community would
accept as proper, at the level of sotn-decomp or the Vagrant Story project.* What those projects actually require, read from
their documents on 2026-09-07 (as data):

- **sotn-decomp `docs/STYLE.md`:** a full naming scheme (locals `camelCase`, globals `g_PascalCase`, statics `s_PascalCase`,
  struct members `camelCase`, types/functions `PascalCase`, enum values and macros `SCREAMING_SNAKE_CASE`, files `snake_case`);
  "We always write our enums and structs as typedefs"; the custom `u8…u32` types; clang-format (4 spaces, 80 columns, pointer
  on the type); decimal for counts and timers, hex for angles, addresses and masks; `bool` for 0/1 returns; braces on every
  block; "It's better to not hardcode array sizes (easier to mod)"; comments for anything strange, `//! @bug`, `// !FAKE:` on
  code that exists only to force a match; **"If you are not sure what something does, it is better to leave it unnamed than
  name it wrongly"**; "All functions should go in the main C file in the same order as the assembly".
- **sotn-decomp `CONTRIBUTING.md`:** `func_`/`D_`/`Unk` placeholders are the to-be-improved state, renaming is a first-class
  contribution; and, verbatim: **"We require commit messages and Pull Requests to be submitted without autonomous tooling such
  as an LLM or coding agent. Assistance from coding agents is allowed, but changes must be justifiable and manually operable."**
- **decomp.me FAQ:** "Please do not attempt to scrape the site, hook up an LLM, or otherwise make repeated, automated,
  requests to decomp.me"; contributions accepted "from people who use the site or are actively involved in the wider
  decompilation community".
- **Vagrant Story (`ser-pounce/rood-reverse`, 62.66% on decomp.dev):** readability refactors called out as goals ("Much of the
  menu code has been refactored and is readable"), `make format` before a PR, the decomp.me claim-and-PR workflow.

**What the community's gripe with "AI decomp" actually is** (the record: our own `docs/history/` psxrecomp post-mortem; the
2026 Macabeus 60-function study; today's permuter episode; the policies above): (1) unsound claims — matches asserted that
are not, the model "wrongly assuming there is a perfect match when there isn't"; (2) matches that are bytes without
understanding — register pins, raw casts, magic numbers, macro bodies, anything that forces the compiler without saying what
the code does; (3) maintainers' time spent on machine-written PRs and issues; (4) automated load on shared infrastructure;
(5) names invented rather than evidenced — the sotn rule "leave it unnamed rather than name it wrongly" is the one Gen3 must
honour most, because a model will happily guess. Item (1) this project answers with the byte gate over 218 whole binaries;
items (2) and (5) are exactly the Gen3 work; (3) and (4) are conduct, governed by rule candidate (j) and the decomp.me rule.

**Where the tree stands, measured today:**

| Bar | This tree (2026-09-07) |
|---|---|
| Byte-identical build, splat, permuter/asm-differ, CI, no-ROM policy, progress publishing | met, and stricter than most: whole-binary SHA1 on every build, 218/218 |
| Named functions | 1,094 named in the symbol files vs **16,335** `func_80xxxxxx` |
| Named data | **61,898** `D_80xxxxxx`; most are per-overlay script data |
| Typed structures | **1,232** struct definitions, many drafter-invented variants of one type; 143 raw address casts remain |
| No match-forcing tricks | **43,925** `register … __asm__("…")` pin declarations (the §3 command, snapshot 2026-09-07; two earlier figures — 43,857 and 44,243 — came from a stricter and a looser grep, the looser one counting 290 comment lines) — sotn would want each either gone or marked `// !FAKE:` |
| Readable organisation | **5,147** shared engine functions live as `DEFINE_func_…()` macro bodies in one 8.4 MB, 227,730-line header (`src/shared/engine_core.h`), instantiated per overlay; 3,558 of the 4,287 C files are `_jr_` carve splits — the layout follows the carving tool, not the game's systems |
| Formatting | no `.clang-format` in the tree and no `make format` target |
| Documentation | the method, the cookbook, the decision log and the wiki are unusually complete; the CODE carries almost no comments |

The gap is therefore not matching and not process; it is the five rows in the middle. In Gen3 planning order they are:
pins off (mechanical, family-batched, byte-gated), the macro-body architecture → shared `.c` files a human can read (a
byte-neutral restructuring; measure it on one family first), struct unification then naming (types from access patterns,
names only with evidence — xrefs, strings, the debug menu, live RAM, the AP world's labels — else stay `func_`/`D_`),
formatting, then comments. Each step is checked the only way this project checks anything: 218 binaries rebuild identical.

**Sequencing against Phase 33 (owner's question, 2026-09-07):** Gen3 execution — any edit to `src/` — starts after the
v2.0.0 close in a fresh plan-mode session (P8; the Gen3 plan is Tier 1). While the flip waits on GitHub Support, Gen3
*preparation* that is measurement-only is legitimate Phase-33 work under G1 and lands in this file: the struct-duplicate
census, a pins-off dry run on ONE family in a scratch worktree (measured yield and cost, nothing committed to `src/`), a
naming pilot's evidence ladder. If Support stalls beyond about a week, the runbook's delete-and-recreate route flips the
repository the same day and the close follows.

## 3. The starter census (derived 2026-09-07 — re-derive, do not trust)

```bash
grep -rhoE '\*\)\s*0x80[0-9A-Fa-f]{6}' src --include=*.c --include=*.h | wc -l          # raw address casts
grep -rhoE '\bD_80[0-9A-Fa-f]{6}\b'   src --include=*.c --include=*.h | sort -u | wc -l # distinct data symbols
grep -rhoE '\bfunc_80[0-9A-Fa-f]{6}\b' src --include=*.c --include=*.h | sort -u | wc -l # distinct function names
grep -rhoE 'register [^;/]*__asm__\("\$?[a-z0-9]+"\)' src --include=*.c --include=*.h | wc -l  # register pins (declarations only; excludes comment text)
grep -rhoE '^\s*INCLUDE_ASM\(' src --include=*.c | wc -l                                  # assembly tiles
cat config/symbols.us*.txt | grep -cE '^[A-Za-z_]'                                        # symbol-file entries
```

| Quantity | Value | Note |
|---|---|---|
| Raw address casts `*(T *)0x80…` | **143** | the low-hanging fruit; each becomes a declared symbol |
| Distinct `D_80xxxxxx` data symbols | **61,898** | most are fields of a handful of structures the engine indexes; `docs/actor-struct.md` recovered one of them (base `0x80078E00`, ~154 fields, live-verified) |
| Distinct `func_80xxxxxx` names | **16,335** | across 4,287 C files; the overlays' shared engine functions have one name each fleet-wide (position-locked) |
| Register-pin declarations | **43,925** (43,857 `"$reg"` + 68 bare `"reg"`; 42,985 in `.c`, 940 in `.h`; snapshot 2026-09-07 — the earlier 44,243 counted 290 comment lines, the earlier 43,857 missed the bare form) | a campaign, not a chore — but batched by family, since a shared body's pins come off once for every member |
| `INCLUDE_ASM` tiles | 1,258 | all inside the executable's linked Sony regions; not Gen3 work |
| Symbol-file entries | 1,083 (1,081 curated names, 2 address-named) | `config/symbols.us*.txt` — the names the build already knows |
| Struct definitions in `src/shared/engine_types.h` | 1,232 | many are drafter-invented variants of the same type (`tools/lift_types.py` knows the collision landscape) |
| Dedup groups | 2,220 (255,708 instances) | a rename or a type change inside a shared body reaches every member |
| Verbatim `__asm__` bodies | 5 | PERMANENT; the manifest audits drift |

## 4. The one invariant

**Every Gen3 edit is gated exactly like a match was.** `make check BINARY=<alias>` for every binary a change touches,
and the clean fleet run (`make clean && make extract-all && make check-all` → `218 passed, 0 failed of 218`) after
anything that touches a shared body, a shared header or the executable — never an incremental check on the executable
(R22). Read the exit code (R53). Commit the moment a batch is green (R42). A rename is a symbol-file change mirrored
into Ghidra by the headless script, never a hand edit of assembly (G6, R15). Readability work is *safe* for precisely
the reason drafting was: a wrong edit cannot land — but it is also *slow* for the same reason, so batch by family and
gate in parallel worktrees ([the matching workflow](wiki/The-matching-workflow.md)).

Two subtleties the census hides:

- **A shared body is one source, many binaries.** Removing a pin or renaming a field inside a `DEFINE_func_…()` macro in
  `src/shared/engine_core.h` changes up to 138 binaries at once; the gate must run on all of them, and a member whose
  bytes happen to depend on that pin (they should not, but the gate decides) has to be split out of the group first.
- **Types are a comprehension lever, not a byte lever.** Phase 17 proved that recovering the actor structure and giving
  it to the decompiler produced identical bytes (`docs/struct-core-pivot.md`): the compiler does not care what you call
  a field. That is good news for Gen3 — struct-ification is byte-neutral by construction *as long as the layout and
  the access widths are right* — and it is why every such edit still goes through the gate.

## 5. Levers Gen3 inherits

| Lever | What it does | Where |
|---|---|---|
| `tools/lift_types.py` | Lifts a named list of types fleet-wide into the shared header, picking the canonical (majority) definition among the drafter-invented variants and stripping the local copies; reports the variant users so the reconcile is targeted; dry-run by default | the struct-ification workhorse |
| `tools/cast_call_sites.py` | Per-site function-pointer / callee casts (cookbook §17a-1) so a call keeps its byte-exact argument codegen while the declaration becomes canonical | when a name/type change alters a call's conversions |
| `tools/canon_sig_reconcile.py` | Reconciles a definition to its canonical signature byte-neutrally (typedef strip, positional param types, casts at the uses — never through a fresh local, which shifts register allocation) | signature clean-ups |
| `tools/sync_tu_decls.py`, `fix_arity_callers.py`, `cast_self_callers.py`, `restore_dropped_decls.py`, `decl_from_use.py` | the declaration layer of the reconcile ladder ([chapter 10](how-to-ai-decomp/10-integration-and-propagation.md)) | any edit that touches declarations |
| `tools/alloc_table.py`, `tools/cc1_dumps_tu.sh` | the allocation order and the per-pass RTL dumps from the real translation unit — read before touching a pin (R73) | the pin-removal campaign |
| `tools/dedup_propagate.py`, `family_sweep.py`, `twin_rescan.py`, `config/dedup.us.yaml` | the propagation and registry machinery; `dedup_integrate --check` refuses a drifted share | keeping 2,220 groups consistent through renames |
| `tools/ghidra_apply_symbols.sh`, `tools/ghidra_scripts/ApplySymbols.java`, `config/ghidra/` + `tools/ghidra_rebuild.sh --proof` | names reach the Ghidra database only this way; the database is regenerable from text | the naming campaign |
| `tools/atlas.py` / `atlas_features.py` | per-function feature layer and similarity groups over the whole fleet | grouping candidates for a rename or a struct |
| `docs/actor-struct.md`, `docs/idxtab-map.md`, `docs/memory-map.md` | the recovered actor structure; the load/index-table map of the 218 payloads; every address with provenance | the ground truth for naming and typing |
| `docs/struct-core-pivot.md`, `docs/wall-taxonomy.md` | what struct recovery can and cannot do; the residual classes | expectations |

## 6. Shiftability, honestly scoped

A *shiftable* build is one whose addresses can move. Three facts frame it:

1. **Overlays are position-locked** at one slot (`0x80128158`) by the loader, the resident at `0x800CEDF8`, the modules
   at their slots (`docs/memory-map.md` §S44/§S45). Shifting code *within* a slot (a function grows) needs only that
   every cross-reference be symbolic — which is what §2's cast → symbol work delivers — plus the data-side references
   the splitter still emits as literal addresses in rodata/jump tables.
2. **LZSS recompression is not byte-stable** (`docs/formats.md` §4.6): a rebuilt overlay cannot be re-encoded to the
   original compressed bytes. The verification layer is therefore the *decompressed* payload (as today); a rebuilt disc
   is a Gen3 deliverable that verifies by booting, not by hash (the constitution's stage 5).
3. **The executable's Sony regions are linked objects**; shifting them means relinking with the real SDK (or the tiles).

Recommended order: symbolic references first (byte-neutral, gated), then a `-Ttext`-shifted overlay that boots in
PCSX-Redux, then the disc rebuild with recompressed payloads.

## 7. The parked Gen3 ideas, with their state

- **Asset export / native rebuild** (`docs/gen3-parking-lot.md`, read-only survey 2026-07-01): rendering is stock
  libgpu; model data goes through libgs `GsMapModelingData` (a documented TMD path — verified by real call sites);
  animation is custom; textures are a VRAM rip away. Difficulty read and the decisive probes are in that file.
- **Native recompilation / PC port** — the original brief's ambition, properly sequenced after readability.
- **Randomizer-grade tooling** — the Archipelago world's RAM map is already cited in `docs/memory-map.md`; E2's
  outreach note is the first contact.
- **The community matching model** — pipeline published ([`docs/matching-drafter-pipeline.md`](matching-drafter-pipeline.md));
  the dataset and weights wait on a licensing decision.
- **JP (SLPS-01490) and the prototypes as extra versions** — the two prototype executables are already imported
  programs with tracked annotations (`config/ghidra/ROSTER.md`).
- **The decomp.me preset** (E1) and **libs-from-source for the Sony regions** — small and large stretches respectively.

## 8. Governance for Gen3

The framework carries over unchanged: the constitution, the session protocol, the digest, the two gates, one task at
a time, the rules R1–R83 (the Phase-33 candidates were ratified as R74–R83 at the Phase-33.5 gate). A new generation starts with a fresh
plan in plan mode at Max. Three things the record says to do first:

1. **Measure the shape before choosing** (the "characterize the corpus SHAPE first" principle — `docs/how-to-ai-decomp/03-bootstrap-order.md`, Phase 1): which structures own most of the 61,898
   data symbols, and which families own most of the 43,925 pins — a census with a self-asserting scanner, checked
   against a case whose answer is known.
2. **Build the differential harness for the new question** before the campaign: "is this rename/type change
   byte-neutral?" has two paths — the per-binary gate and the fleet run — and a scanner that asserts every reference
   to a renamed symbol was rewritten (R32).
3. **Batch by leverage**: a pin in a shared body comes off for 138 binaries at once; a struct that explains a thousand
   `D_` symbols is worth more than a hundred one-off names. Rank, then start.
