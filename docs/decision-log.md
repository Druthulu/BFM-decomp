# Decision & Pivot Log — the "why" behind BFM's strategic turns

**Purpose.** An append-only record of the project's STRATEGIC pivots, dead-ends, and reversals — the
*judgment* behind major direction changes, captured WHILE FRESH (R31). This is the perishable layer the
other records don't hold:

| Record | Holds |
|---|---|
| `phase-ends/PhaseEnd_*.md` | per-phase build history + terse **Deviations** tables (WHAT changed, briefly) |
| `docs/matching-cookbook.md` | TECHNICAL idioms (asm↔C compiler quirks, tool recipes) |
| **this file** | STRATEGIC why: what we believed → what we tried that failed → why we turned → the hindsight "better path" |

**Why it exists.** It is the substrate for two future deliverables (see the Phase-25 discussion, 2026-07-08):
1. the project **retrospective** — "with hindsight, the best way to have done this"; and
2. the public **"how to AI-decomp a brand-new project"** wiki at the public flip.

The quantitative curve (fleet % over time) is safe in git + the PhaseEnds forever; the *reasoning* —
"we tried X, it was a dead end because Y, so we turned to Z" — is what evaporates between sessions. So it
is logged here as it happens.

**Discipline (R31 — confirmed by Drew 2026-07-08, Phase 25).** **Forward-only.** Do NOT backfill historical pivots from
compressed summaries — that reproduces exactly the low-quality reconstruction R30 exists to prevent (the
PhaseEnds/cookbook already hold what was captured fresh at the time). Log each NEW strategic pivot during
the session that produced it. Route TECHNICAL idioms to the cookbook; this file is for direction/judgment.

**Entry format:**
```
## [date] · Phase N — <pivot title>
- Context / belief: what we were doing and assumed.
- Dead-end (if any): what we tried that didn't work + the byte/measurement evidence.
- Pivot: what we changed to.
- Why: the grounded reason (bytes, measurement, constraint).
- Hindsight / for the wiki: the transferable lesson — what a from-scratch project should do.
```

---

## 2026-07-08 · Phase 25 — a fresh session nearly closed an OPEN phase (handoff-misread)
- **Context / belief:** resuming Phase 25, the `CURRENT_PHASE.md` handoff header read *"finish T7 → Close;
  do NOT start T4 yet."* I concluded the remaining tasks (T4/T5/T6 + the exemplar-cracking that is the
  phase's actual goal) were being **deferred to Phase 26**, and drove toward writing the PhaseEnd.
- **Dead-end:** I reframed the plan's core work as a "Phase-26 backlog" and presented a milestone-close for
  confirmation.
- **Pivot:** Drew corrected — T7 had been *pulled ahead* opportunistically (only its free/cheap MECHANICAL
  wins); *"not yet"* meant **finish those first**, not **defer to next phase**. The 127-draftable-family
  curriculum (T4→T5→T6→T7-cracking, the 6.7 MB byte-weight prize) remains this phase's substance. No PhaseEnd.
- **Why:** I anchored on the literal *"→ Close"* in a handoff header — a phrase written for one moment
  ("don't start T4 in THIS session") that I read as a permanent scope decision. The approved **plan of
  record** (`plan-mode-…-galaxy.md`) plainly lists T4–T7 as this-phase work with an *open-ended* milestone;
  reconciling the handoff against it first would have prevented the error.
- **Hindsight / for the wiki:** **the #1 failure mode of a long multi-session AI project is a fresh session
  misreading a compressed handoff.** What saved it: (a) an approved plan-of-record that outlives any single
  handoff, and (b) a human who caught it in one message. What to bake in: handoff headers must distinguish
  *"not this session"* from *"not this phase"* in unambiguous words; and **a resuming session must reconcile
  the handoff against the plan-of-record before ever concluding a phase is done** — never close on a handoff
  phrase alone. (This is why the plan-of-record and the two-gate model earn their keep.)

## 2026-07-08 · Phase 25 — the "mechanical" family sweep has a hard ceiling at TU-local type collisions
- **Context / belief (T7.2):** the h_norm structural-family remap is *mechanical* — crack one exemplar,
  lift the local types it references into the shared header, and every sibling overlay compiles + banks.
- **Dead-end:** lifting ALL overlay-split-file types into the fleet-wide `engine_types.h` broke the build —
  `typedef Buf` has a DIFFERENT layout in `_a.c` vs `_after.c` (they never clashed as separate `.o` TUs),
  and `_a.c` locally redefines PsyQ SDK names (`MATRIX`/`VECTOR`) that a fleet-wide lift would shadow.
- **Pivot:** lift only the collision-free subset (base + `_after` minus `Buf`); defer the conflicting
  families to per-type reconciliation (Phase 26). Banked 1,729 of the ~3,857 targeted — the rest is genuine
  work, not mechanical.
- **Why:** the overlay split files are independent translation units with independent local type
  namespaces; "share everything" is unsound across that boundary. (Technical detail → cookbook §40a.)
- **Hindsight / for the wiki:** **know the mechanical ceiling before launching a mass pass.** A cheap
  detect-collisions-first probe would have scoped the safe subset up front instead of discovering it via a
  failed build. General lesson: an automated bulk transform needs an explicit *soundness boundary*, and the
  byte-gate (not optimism) is what stops a partial success from masquerading as a full one.

## 2026-07-08 · Phase 25 — the local-7B tier is capacity-bound and off the endgame critical path (T4)
- **Context / belief:** the fine-tuned local drafter (`bfm-match-7b-v3`) was a core cheap tier; retraining **v4**
  on the much larger post-giant-campaign corpus (2,891→3,574 pairs, +994 medium + 597 large functions v3 never
  saw) should extend its band upward and make it a stronger drafter for the T5 wave.
- **Dead-end:** v4 **did not beat v3** — it was marginally WORSE. Gate-true head-to-head on identical held-out
  functions: easy 6-14 ins both 5/5; **medium 18-40 ins** v3's near-misses closer (one at `near-1`, permuter fuel)
  with 1 compile-fail vs v4's 4 — v3 closer on 9/12; **hard 45-85 ins** both 0/10. Crucially v4 scored 0/5 even on
  the 76-83 ins functions it TRAINED on (verified ~1.4-1.7k tok, well inside maxlen 2048 → NOT truncation → genuine
  capacity). (Note: a real corpus-prep flaw exists — functions >85 ins WERE truncated at maxlen 2048 → training on
  cut-off completions, likely the source of v4's slight medium regression — but it doesn't touch the decisive band.)
- **Pivot:** discard v4, **keep v3 (the frozen ceiling)**, and stop investing in the local-7B tier. Not retired
  (still a $0 mop-up for the ≤~15-ins setter/leaf tail), just no longer load-bearing and no more retrains.
- **Why:** the byte-gate A/B settled it directly (G3/P9). "**Corpus quality > size**" landed empirically: v2→v3
  gained from *better* data (the extern-capture fix); v3→v4 was just *more/harder* data and it didn't lift a
  capacity ceiling. Byte-matching's hard part is compiler-codegen REASONING (scales UP with model size), not
  language breadth (which a smaller model could shed) — so neither "more data" nor "a smaller RE-specialist" is the
  lever; the reasoning has to come from a large pretrained base or a frontier model, and the RE-smartness that IS
  small+deterministic already exists as **m2c** (rules, not weights).
- **Hindsight / for the wiki:** **the endgame engine is `frontier-crack → deterministic-propagate → byte-gate`,
  with the permuter softening near-misses — the local small model is a convenience on the small tail, not a
  load-bearing part.** For a *matching* decomp you already own the ground-truth compiler + a perfect verifier, so
  the ML task is candidate-PROPOSAL + search (proposal quality scales with reasoning/size; the check is free). A
  bespoke small "RE model" founders on data scarcity (the asm↔C-under-a-specific-compiler corpus only exists, tiny,
  in decomp git histories). The honest tiering: **m2c** for structure, a **frontier reasoner** for the byte-exact
  precision on the hard/byte-weighty band, the **permuter** for regalloc/schedule search, a **frozen small LoRA**
  only for the cheap ≤15-ins tail. Don't spend GPU-hours chasing band-extension on a 7B; rent a bigger GPU or use
  the frontier tier when the hard band is the target.

## 2026-07-09 · Phase 25 — the GIANT def-side wall is mechanically crackable → build the lever, don't just measure (T5b batch-2)
- **Context / belief:** T5b batch-2 (the 29 giants) was scoped as a pure *measure* wave — draft, `match_one`, map the
  frontier; the plan filed the def-side loose-typing wall as a T7 (post-curriculum) problem, expecting ~0 giant banks.
  Belief going in: giants would mostly near-miss and feed Fable5/permuter; any that isolation-MATCHed would bank via
  the gate's existing `sig_unify`/`cast` transforms.
- **What was tried that failed:** all **16** R14-verified isolation-MATCH giants banked **0/16** through `gate_stage`
  AND through raw `harvest_verify`. Root cause (dug out by placing one and reading the cc1 error, not trusting the
  gate's summary): `conflicting types for func_X` — the drafters wrote Ghidra-*typed* sigs (`void f(u32*, s16*)`) that
  clash with the TU's **canonical** sig, which lives *inside a `DEFINE_func_*` macro* in `engine_core.h` where
  `sig_unify` (a file-scope-extern rewriter) can't see it. First reconcile attempt ALSO failed twice: an `s32/s32-args`
  form conflicted with the engine_core.h `void/void*` canonical; then intermediate cast-locals (`u32 *a0 = (u32*)arg0`)
  *compiled* but produced the WRONG bytes (`70ff4748`) — a fresh pseudo shifted regalloc.
- **Pivot:** stop treating the def-side wall as a future-T7 abstraction and **build the lever now**
  (`tools/canon_sig_reconcile.py`): strip ambient-dup typedefs/externs, rewrite the def to the engine_core.h canonical,
  and **cast each changed param AT ITS USES, never via a local**. That banked `func_8013B274` byte-identical, then
  **5/16** giants total; 3 swept ×134. Batch-2 turned from "measure + backlog" into "prove + partly-automate the
  phase's #1 lever," pulling a chunk of T7 forward on real data.
- **Why (byte/measurement-grounded):** the cast-local vs at-use difference is a *measured* byte fact (`70ff4748` wrong
  vs `d19c9580` right), not a style call — an intermediate local is a new pseudo gcc-2.7.2 may color differently; an
  at-use cast is free. The whole-binary byte-gate stayed the sole arbiter throughout (G3/P9): every one of the 5 banks
  is byte-identical, and R22 clean-fleet is the backstop — it caught my *own* buggy R22 harness (an unexpanded
  `$(OVERLAY_BINARIES)` that only extracted 2 of 136 binaries) before any false "136/136" could be reported.
- **Hindsight / for the wiki:** when a whole *class* of candidates fails the gate identically, **read the raw compiler
  error on ONE placed candidate before concluding "hard / defer"** — the summary ("0 banked") hid a *mechanical*
  declaration conflict behind what looked like an intractable matching wall. The giant tier was never a matching
  problem; it was a **plumbing** problem (the body was already right in isolation). General lesson for
  frontier-crack→propagate→byte-gate: distinguish *codegen* residuals (permuter/Fable5) from *TU-integration* residuals
  (a deterministic reconcile) early — they look identical at the gate ("0 banked") but have completely different levers,
  and the integration ones are cheap ×134 wins hiding as "hard giants." Residual: non-identical ambient types and
  macro-local data symbols are the genuinely-hard remainder (real `reconcile_decls`/rename work), and a reconciled body
  doesn't `family_sweep` cleanly to siblings (per-sibling re-reconcile needed) — both logged for T7.

## 2026-07-09 · Phase 25 — T6: the def-side wall was ~71% tool-shaped; the endgame's frontier shrank from 95 to 33 (Fable5 curriculum session)

- **Context + belief going in (the T5 handoff):** the 95 still-stub family exemplars decomposed as
  "~19 clean-canonical mechanical via canon_sig_reconcile; ~32 harder implicit-int fallback; 31 genuine
  near-misses; 11 hard walls (non-identical types / macro-local data); the 3 `_o0` giants need a special
  -O0 reconcile; the frontier 'match' statuses carry un-verified agent claims (spot-check 3/5); reconciled
  bodies don't sweep (func_8016DC20 = 133 sibling failures)." T6's job was to author the crack curriculum
  from that map, with the expectation that most of the 95 needed per-fn Fable5/permuter work.
- **What was tried that failed / surprised:** (1) R14 re-verification of ALL 95 (not 5) flipped the
  caution — 62/95 genuinely isolation-MATCH; the spot-check pessimism didn't generalize. (2) Probing all
  62 through the REAL TU (splice + full pipeline + masked in-TU byte-compare) showed v1
  canon_sig_reconcile itself was the wall for most: six probe iterations (v1→v3.1) flipped 10→20→37→44
  fns to BANKABLE as five tool defects fell (scalar-typedef strip; preprocessed-TU canonical; block-scope-
  move-not-strip; collision RENAME; decl-line cast protection). (3) Two of my own v2/v2.1 policies
  (ambient-type rewrite of data externs; canonical-text re-emission + blanket casts) BYTE-DRIFTED or
  parse-broke dozens — caught only because every iteration re-probed all 62 (the probe program, not the
  first diagnosis, was the method). (4) A byte-perfect gate run reported MISMATCH because I hand-typed
  `--good-sha` from memory — the check file is the only source of a hash.
- **The pivot:** T7 is now mostly DETERMINISTIC EXECUTION, not discovery: tiers M1 (44 reconcile-banks,
  4,254 ins, 13 giants) → M2 (sweep ×134 via remap + PER-SIBLING re-reconcile — proven 6/6, dissolving
  §41's "sweep fragility") → M3 (6 fns: no-proto rewrite of engine_core.h macro externs — arity conflicts
  with a visible typed prototype are the one thing no draft transform can fix) → M4 (8 fns: §33 TU
  stale-decl retypes) ≈ **+2.2% fleet for ~0 agent tokens**; the true Fable5/permuter frontier is 33 fns
  (31 verified nears + 4 perturbs, minus overlaps) + 2 trivial drafts. The "-O0-specific reconcile" need
  was refuted outright. Deliverables: `docs/phase25-t6-curriculum.md`, `.run/t6_worklist.json`,
  cookbook §41a, canon_sig_reconcile v3.1.
- **Hindsight / better path:** a "wall" verdict is only as good as the TOOL REVISION it was measured
  against — re-derive wall taxonomies after every tool change (three iterations moved 34 fns from
  "wall" to "mechanical"). And validate the gate-proxy against the real gate before trusting either
  direction (the probe caught real walls the drafts hid; the gate caught my SHA typo). The general
  law: when a residual class's members share an error SHAPE (`conflicting types`, `undeclared`,
  parse-at-decl), suspect the pipeline before the compiler.

## 2026-07-10 · Phase 25 — T7 executed the curriculum; the "mechanical tier" was ⅓ probe-over-counted (Opus-Max)

- **Context + belief going in:** the T6 Fable5 curriculum projected 58 fns / ~2.5 MB as MECHANICAL (M1 44
  reconcile-banks, M3 6 no-proto, M4 8 reconcile_decls-retypes), sized from an in-TU OBJECT probe (compile the
  fn in the real TU, mask jal/%hi/%lo, byte-compare). Drew: "run T7."
- **What was tried / surprised:** executing against the WHOLE-BINARY gate (`harvest_verify`) revealed the object
  probe systematically OVER-counts, because it is blind to three things it cannot see: (1) **rodata** — 4 "M1"
  jump-table fns have byte-perfect `.text` but a switch table in rodata diverges (this also REFUTED the T6 "Q3
  -O0 REFUTED" claim — the `_o0` giants are jump-table fns); (2) **link** — 3 "M1" fns are the only asm referencer
  of a scratch data symbol, so C-ifying them drops splat's auto-symbol → `ld undefined`; (3) **in-TU codegen
  perturbation** — all 8 "M4" fns are byte-correct in ISOLATION but drift 8–69 in the real TU (scheduling order,
  `volatile`-loss), and `reconcile_decls` banks 0/8 (4 have no data-decl conflict at all). Plus 4 M3 residue
  (arity/loose-typing). Net: 19 of the 58 "mechanical" were per-fn F-band work.
- **The pivot:** bank the TRULY-mechanical core and re-tier the rest honestly. M1 37 + M3-clean 2 = 39 exemplars,
  reconciled (`canon_sig_reconcile` v3.2 — a type-name-uniquify fix unblocked the struct-collision giants) and
  swept ×134 via `family_sweep --reconcile` (the Q5 per-sibling re-reconcile law: plain remap banks 0, per-sibling
  reconcile banks 94%). **~4,694 fleet fns, fleet 72.29 → 73.66% (+1.37%), R22 136/136, ~0 agent tokens.** The 19
  over-counts → F-band (permuter/§31/Fable5) or specialist workflows (jump-table-in-rodata, manual undefined-syms).
- **Hindsight / better path:** an in-TU OBJECT probe is a necessary FILTER but must never SIZE a "mechanical"
  tier — gate a full sample on the whole binary first, and budget ~⅓ of any object-probe "drift/fail" bucket as
  genuine per-fn work. The mechanical ×134 sweep is the real economic engine (4,655 members from 39 cracks); the
  curriculum's value was concentrating the crack effort onto the 39 exemplars, not the tier-size projection.
  Reinforces R14 (verify vs bytes) at the tier-classification level and cookbook §41b/§41b-addendum.

## 2026-07-10c — Propagation-recovery (task b) is NOT a simple --edit-remap gap; it's a family_remap LIMITATION on lever-heavy F-band cracks

**Context+belief:** After waves 3/4 banked exemplars but dropped ~1,200 siblings, I projected task (b) as a cheap
`family_sweep --edit-remap` enhancement (carry the exemplar's //@EDIT file-scope edits per sibling) — a ~0-token bulk win.

**What failed / the diagnosis:** Probing the 7 dropper families showed the drops are HETEROGENEOUS and dominated by
**`family_remap` symbol-pairing FAILURE ("133 remap-fail")**, NOT the decl/byte layer an --edit-remap would fix.
`family_remap` was built for MECHANICAL (reloc-only, T3) families; the F-band cracks carry heavy levers (register
`__asm__` pins, density dead-reads, phantom-frame `frame_pad`, pointer casts, //@EDIT flips), whose disassembly
doesn't positionally pair to the sibling image cleanly → remap aborts. func_8014FE60 (engine_core void→s32) also
remap-fails even after the correct global flip. The families that DID sweep (func_80166690/8017B238/80131B14/
8016CF04/8014FBC0) have remap-clean bodies; the droppers don't.

**The pivot:** recovering the ~1,200 dropped siblings needs EITHER (a) a `family_remap` upgrade that pairs
lever-heavy bodies (structure-aware, not positional-reloc-only), OR (b) a per-sibling re-crack (m2c+reconcile+rtu_match
fan-out ×133/family — expensive). Both are a focused follow-up, not a quick enhancement. Backlogged.

**Hindsight better-path:** the ×134 economics assumed family_remap propagates any crack; it only propagates
remap-clean ones. Future crack-then-sweep waves should CHECK remap-ability of the exemplar body BEFORE counting the
×134 (a cheap `family_remap --dry` per exemplar), so the frontier map's leverage estimate reflects propagate-able
families, not all same-address families.

## 2026-07-10c (CORRECTION, same day) — the "family_remap limitation" was a MISDIAGNOSIS; the real bug was canon_sig_reconcile's def-finder (R14)

**Correcting the entry above.** I concluded the propagation drops were a `family_remap` limitation because `family_sweep`
reported "133 remap-fail". **That label was misleading.** Running `family_remap` directly on all 7 droppers SUCCEEDED
(it paired 4–6 symbols each). The None that `reconcile_remap` returns — which `family_sweep` counts as "remap-fail" —
actually came from **`canon_sig_reconcile.reconcile` raising "no definition of func_X found in draft"**: its def-finder
regex required a leading `\n` (`r'\n(<type> fn(...)){'`), but stripping the `//@EDIT` lines left the fn definition on
LINE 1 of the raw draft (no leading newline) → not found. The swept-clean families happened to have a leading `// @class`
comment, so their def had a `\n` before it.

**FIX (1 char, low-risk):** def-finder regex `\n` → `(?:^|\n)` (also match a def at the draft start; only ADDS matches).
**Result:** func_8014FE60 fully recovered — 133/133 siblings banked (fix + its engine_core.h void→s32 global flip).

**Residual (the GENUINE --edit-remap work):** 4 families (func_8016DF5C/80136334/8013D9B0/80156044) now RECONCILE but
BYTE-DRIFT per sibling — their crack levers (s32↔void return flip, array-decay pointer `//@EDIT`, no-proto `//@EDIT`)
aren't carried/re-derived per sibling. Recovery = carry the exemplar's `//@EDIT` per sibling (symbol-remapped) + apply
the return-type flip to the shared engine_core.h decl once. Still a focused follow-up, but SMALL and well-understood
now — NOT a family_remap rewrite.

**LESSON (R14):** a tool's failure LABEL can misattribute the failing STAGE. "remap-fail" was actually a
reconcile-def-finder throw. Trace the real exception (`reconcile_remap` swallows it) before concluding a limitation.

## 2026-07-11 · Phase 25 — task B: `--edit-remap` BUILT, but 4/6 byte-drift families are cc1-crash-walled (~266, not ~800)

**Context + belief (from the 2026-07-10c handoff):** the 6 byte-drift `//@EDIT` families were framed as "SMALL and
well-understood — recover ~800 fns by carrying the exemplar's `//@EDIT` per sibling + a once-global engine_core.h
flip." Drew locked B first on that basis (scoped, mechanical). I built `family_sweep --edit-remap MANIFEST` to do
exactly that.

**What the byte-gate revealed (probe-before-invest, R14):** the families are NOT one bucket. Only the **2 array-decay
pointer-flip** families (`extern s32 D_x[];`→`extern s16 *D_x;`) recover — `func_80136824` + `func_80136334` banked
**266/266 siblings byte-identical (0 failed), full ×134**. The other **4 are register-pin-heavy** (`func_80133AB0`'s
exotic `register int zr __asm__("$0")`; `func_8016DF5C`/`func_8013D9B0`'s GTE 20-pin bodies; `func_80156044`'s
inline-asm trampoline) and **cc1-2.7.2 SIGABRTs (`make` Error 134) compiling the SIBLING TU** — the identical body
compiles fine in ov077. Universal (func_80133AB0 crashed 3/3 siblings tested). The hand pins are ov077-TU-context-
specific: cc1's fixed-table 1996 register allocator aborts on the pin pattern in a different overlay's surrounding
function set. func_80156044's engine_core.h `int`→`void` flip IS byte-neutral (verified) — the wall is its body, not
the edit.

**The pivot:** ship the 2 tractable families (266 ×134, R22 136/136 green, fleet 74.40→74.48%), backlog the 4 crashers
as exemplar-only (×1) / per-sibling permuter-Fable5 fuel, and move to A (the 7 giants — all remap-clean 133/133, ~938
fns high-byte-weight, the real ROI). The `--edit-remap` tool is reusable for future array-decay-class cracks; its yield
must be sized by that subset, never by "family has an //@EDIT."

**Better path (hindsight):** the "~800" estimate counted `sibs × families` without asking "does the CRACK compile in a
sibling TU?". A hand crack that banked in ov077 by exotic register pins does not generalize — a 30-second single-sibling
`make build` probe per family would have sized B honestly up front. **LESSON (R14):** an exemplar match proves the crack
in ITS TU only; the ×134 claim needs a sibling-TU compile probe, because pins are TU-context-specific and cc1 *crashes*
(not just drifts) on the ones that don't transfer. Corollary: rtu_match/match_one are blind here — their neutralized/
isolation compiles crash too (harness artifact); only the real `make build` is the arbiter.

## 2026-07-11 · Phase 26 — the "reach-1 tail" is largely a reloc-tracker blind spot, not unique code (Task 1)

**Context + belief (from the Phase-25 close):** the h_seq reframe had already shown the "36k unique tail" collapses
~90% into per-location families. The open question entering Phase 26 was HOW the families differ — the megaplan framed
immediate-substitution as the central new problem (families "differ in immediates, so are NOT free dedup").

**What the design pressure-test found (byte-verified before any scaling — R14):** the dominant difference is NOT
immediates — it is a **tracker blind spot**. `norm_stream`/`reloc_targets` dropped the lui-hi on every R-type write,
but gcc-2.7.2's indexed-global idiom `lui;addu $idx;lw %lo($at)` preserves it. So `D[i]`-indexing functions were
*mis-normalized per overlay* → they inflated the "h_norm reach-1 tail," and `family_remap` silently dropped their
indexed `D_` symbols → those families couldn't bank even though they are pure per-location templates. On the
substantial tail the classification is **PURE-same-addr 62 fams / 1.55M ins · PURE-cross-addr 103 / 0.10M · genuine
IMM only 8 / 0.10M** — i.e. ~95% of the byte-weight is reloc-only, fixable by a ≤15-LOC tracker change, and the
immediate engine shrinks to an escalation tier for ~8 families. A second latent bug surfaced alongside: `remap`'s
sequential substitution corrupts chained/permuted maps (harmless on h_norm, breaks the imm engine).

**The pivot:** front-load the tracker fix (Task 1) as the load-bearing change, demote the immediate engine to a
diff-driven 3-tier escalation (Task 3), and add a **free validation corpus** — 63 families / 0.31M ins already have a
MATCHED exemplar and only failed earlier sweeps from this bug → they bank with zero cracking the moment the fix lands
(Task 5 V2), simultaneously measuring the real template success rate before any Fable5 spend.

**Better path (hindsight):** the tracker's own design note already said "conservative: can miss a match, never forge
one" — but a *missed* reloc in a REMAP tool isn't harmless the way a missed h_norm match is; it silently produces a
wrong-but-compiling sibling body that only the byte-gate catches. When a normalization/remap tool is REUSED for code
generation (not just clustering), its conservative-miss becomes a correctness bug. **LESSON (R14):** before treating a
"unique/unmatchable" population as intrinsic, re-run the *grouping and the remap* under a corrected fingerprint —
here the "reach-1 tail" and the "unremappable family" were the SAME artifact of one dropped register-tracking case.

## 2026-07-11 · Phase 26 — Task 5 GO/NO-GO: the h_seq engine is 100% correct on clean families; the substantial matched band is type-dominated (a reconcile follow-on, not a machinery gap)

**Context + belief:** Task 5 was the validate-before-scaling gate — run the whole-binary byte-gate on the
matched-exemplar families and MEASURE the real template success rate before any Fable5 spend. Expectation:
a high mechanical bank rate on the "free-win" tracker-miss corpus.

**What the byte-gate revealed (R14):** the substantial matched-exemplar band banked **532/1507 non-pinned
members (~35%)** — but that aggregate is misleading, and the per-family breakdown is the real signal:
- **3 families banked 100% ×133** = 399 byte-perfect members — exactly the 3 tracker-miss PURE families
  (`0x8015d5e8`/`0x8015f118`/`0x801407f4`) the design pass named. The addu-hi tracker fix + the extern-carry
  fix (below) make these template flawlessly. **The machinery is 100% correct on clean families.**
- **9 of 13 clean families ZERO-banked** — all reference overlay-local custom struct types (`Work8016`,
  `Work8017`, `SV4_8017B368`, `Prim`, `E4`) → the templated body is `undeclared-type` in the sibling TU =
  the §41 def-side / type-lift RECONCILE class, which the existing `family_sweep --reconcile` /
  `build_engine_types` path already handles. NOT a machinery failure — a known follow-on (Task 8).
- 16 of 29 substantial matched families were pinned-exemplar (×1-only hard-reg cracks) → skipped by the
  new static pin guard → Task-7 pin-free re-crack.

**The load-bearing tooling fix (Task-5's "measure then fix", R16):** the first gate run banked only ~34%
because `extract_unit` grabs only *immediately-preceding* externs — a per-location body that indexes a
global (`(*D_x[i])()`) references symbols declared once at file scope elsewhere in the exemplar TU; templated
into a sibling TU that never declared them, they are `undeclared` at the gate. Added `remap_hseq.gather_externs`
(carry the file-scope externs for every body-referenced symbol, remapped). `func_8015F118` went from gate-fail
to BYTE-IDENTICAL; the 3 clean families then banked 133/133 each.

**The pivot / verdict: GO.** The zero-crack h_seq machinery (tracker + imm + cross-address + extern-carry) is
byte-proven correct. Scale it (Task 8: the mid/tiny bands + the reconcile pass for the type families). The
Fable5 window (Task 6/7) goes to the big PURE cores that have NO matched exemplar (890/562/536… — they need a
crack before they can template).

**Better path (hindsight):** the raw aggregate rate (35%) nearly read as "the engine is weak"; the per-FAMILY
breakdown showed it is "the engine is perfect on the families it targets; the rest are a different, already-
solved problem." **LESSON:** when measuring a mechanical harvest, stratify by family/class before judging the
rate — an aggregate mixes 100%-clean, 0%-type-blocked, and skipped-pinned populations that demand different
follow-ons.

## 2026-07-11 · Phase 26 — Task-8 pipeline-validation slice (pre-Fable5-window de-risk): reconcile→bank works; templating reconcile-class cracks needs per-sibling re-reconcile in --hseq

**Context + decision (Drew):** before spending the closing Fable5 window (Task 7), validate that the
reconcile→gate→template pipeline actually banks an isolation-crack end-to-end — else the window's output
(same isolation-crack format) could pile up un-bankable. Ran optimal-order step 1 only ("bank the wins,
pause before Task 8").

**What the byte-gate revealed (R14), in two halves:**
1. **Reconcile→bank WORKS.** The 23 triage closeness-0 cracks gate **0/23 raw** (they carry standalone
   `struct Obj`/scalar typedefs + Ghidra sigs → §41 def-side wall). Run through `canon_sig_reconcile` v3.2
   (strip ambient dups, canonicalize the sig, cast callees at use) they bank **4/15** into ov077
   (`func_801506A4`/`func_8016A73C`/`func_80167540`/`func_80155800`, byte-identical). The 11 residual fails
   are a data-extern-typing gap (e.g. `conflicting types for D_801891B8`, a fn-ptr array the seed types
   differently than the TU) the reconcile's pt-9 data-extern handling doesn't fully cover for these seeds.
2. **Templating a RECONCILED body ×133 FAILS (0/4).** The reconciled ov077 body is TU-SPECIFIC — its
   canonical-sig casts + `Name_<addr>` collision-renames fit ov077, not the sibling TUs (each has its own
   ambient types/sigs). Plain `remap_hseq` copies the ov077-reconciled body → re-hits the def-side wall in
   every sibling. This is the decision-log 2026-07-11 lesson again: an exemplar match proves the crack in
   ITS TU only; ×134 needs per-sibling work.

**The implication (the point of validating first):** the PURE tracker-miss families template cleanly via
plain `--hseq` (Task 5: 399 banked). But the **type-using families — the triage cracks AND the 61 Fable5
cores — are reconcile-class**: their cracks bank as ov077 exemplars but need **per-sibling re-reconcile**
to template ×134. That machinery EXISTS for h_norm (`family_sweep --reconcile` / `reconcile_remap`, the
Phase-25 M2 4,389-bank path) — it just needs porting into the `--hseq` path (over `remap_hseq`, i.e. with
cross-address + imm). **So the Task-8 prerequisite before the Fable5 window is productive: wire per-sibling
reconcile into `hseq_sweep`.** Otherwise Fable5 output stalls at ×1 (ov077-only).

**Outcome:** kept the 4 real ov077 exemplar banks (byte-verified). Paused before building the per-sibling
reconcile wiring (that IS Task 8, per Drew). **LESSON:** the validation slice paid for itself — it converted
"the pipeline works, go spend the window" into "reconcile→bank works, but templating reconcile-class needs
one more wiring step first," a decision that would have been very expensive to learn after the window closed.

## 2026-07-12 · Phase 26 — the crack-harvest has TWO tooling gaps + the rtu_match-vs-whole-binary lesson (Fable5 batch-1 processing)

**Context:** processing the Fable5 batch-1 cracks + the 23 triage isolation-cracks through the whole-binary
gate revealed the "closeness-0 / rtu_match-MATCH" counts were optimistic. Whole-binary reality (G3/P9):

**1. The rtu_match blind spot on jump-table functions.** Both Fable5 cracks (`func_80159C84`, `func_8015444C`)
rtu_match-MATCH but FAIL the whole-binary gate. rtu_match neutralizes `INCLUDE_ASM` (excluding the §8
jump-table rodata `.s`) and compares only the masked INSTRUCTION stream — it never verifies the jtbl rodata
data bytes. The code is right; the jtbl rodata isn't confirmed. **rtu_match is NOT a sufficient sole arbiter
for jr-functions** — the whole-binary gate is (as always, G3). Pattern is clean: all 6 whole-binary-banked
cracks are no-jtbl; every jtbl crack (2 Fable5 + the 2 jtbl triage cracks) fails.

**2. Two distinct harvest gaps, both fixable Task-8 tooling:**
   - **§8 jtbl-rodata gap:** replacing an `INCLUDE_ASM` jr-function with C needs the compiler-generated jtbl to
     byte-match + land in the right rodata slot (the §8 dotted-`.rodata`-subseg + ld_interleave). The overlay
     splits don't have this per-cracked-jr-function setup → every jtbl crack fails the binary. **This blocks the
     jtbl-heavy Fable5 window** (most top cores are jr giants).
   - **reconcile data-extern gap:** ~15 of the 21 no-jtbl triage cracks fail canon_sig_reconcile on a
     `conflicting types for D_x` (fn-ptr-array / typed-global the seed declares differently than the TU) — pt-9
     data-extern handling is incomplete for these. Only 6 no-jtbl reconcile-clean cracks bank (729 members:
     463 committed + 266).

**The implication for the Fable5 window:** cracking a jtbl giant with an rtu_match-only agent produces an
UNVERIFIED result — the §8 rodata must be handled + the whole-binary gate must be the arbiter. So the window
is only productive on jtbl cores AFTER the §8-overlay-jtbl tooling exists (or with serial whole-binary
verification). **Better path (hindsight):** the Fable5 crack prompt should have required the whole-binary gate
(or an rtu_match variant that includes the jtbl rodata) as the bar, not plain rtu_match — for jr-functions the
two diverge. LESSON: an indicator that MASKS a byte-region (rtu_match masks relocs + excludes neutralized
INCLUDE_ASM rodata) cannot arbitrate a match whose difference lives in that region.
