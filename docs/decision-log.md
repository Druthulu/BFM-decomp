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

## 2026-07-12 · Phase 26 — §8 unblocked the HEAVIEST byte-weight lever (switch functions), reframing the endgame priority
- **Context / belief:** built the §8 overlay jtbl-rodata tooling + the ×134 automation (jr-functions can
  now bank as C, proven func_8012ACE0 ×133), then recommended continuing with "the 45 small jr families"
  as the next mechanical lever.
- **Dead-end (the off-plan recommendation, Drew caught it):** that rec optimized for *mechanically easy*
  (small families template cleanly) instead of the endgame's actual objective — **heaviest byte-weight
  first**. Measured: the 45 small jr families = **129,028 templatable ins** (trivial).
- **Pivot:** re-target the heavy tier. The frontier byte-weight (the instr-weighted metric lever):
  **jr (switch) substantial families = 191 fams / 5,534,884 ins**; non-jr substantial = 1,168 / 7,328,348;
  all substantial = 12.86M. And decisively — **9 of the 10 heaviest unmatched family cores are switch
  (jr) functions** (func_80178D40 890×134 = 477K ins alone; func_8017BEBC 952×113; func_8015AE2C 562×134…).
- **Why:** switch functions were UNBANKABLE before §8 (the jtbl-rodata duplicate). §8 didn't just enable a
  small mop-up — it **unlocked the single heaviest chunk of the remaining game** (the byte-weight is
  dominated by big switch cores). The endgame plan (heaviest-byte-weight-first via crack-core → template
  ×134) is intact; §8 was its key enabler, and the correct follow-through is the HEAVY jr cores, not the
  light tail. This needs Task 7 (Fable5) un-paused: Fable5 cracks the giant switch core → §8 + the ×134
  automation bank it fleet-wide → the now-10×-faster R22 verifies.
- **Hindsight / for the wiki:** when a build-mechanism unblocks a whole *class*, re-rank the endgame by
  the class's byte-weight, not by which member is easiest to bank next. "Easy and on-metric" ≠ "easy";
  the plan's objective (heaviest byte-weight) must gate the next-target choice, or you grind the light tail
  of a newly-opened heavy vein. (Drew's steer: "the endgame plan is 1st smartest play to unlock the
  heaviest byte-weighted remainder — does your recommendation follow it?" — it did not; this corrects it.)
- **Sequencing refinement (Drew, same day):** do the 45 SMALL jr families first as a **de-risk
  preamble** (NOT for byte-weight — ~+1% instr), THEN the heavy 191. The decisive reason isn't
  size: `jtbl_carve` only built the single-jtbl carve, but func_8012ACE0 is now matched in all 133
  siblings, so family #2 forces the **multi-jtbl address-ordered carve** — build & prove THAT on
  cheap 30-ins targets before a Fable5-cracked 890-ins core depends on it. Also needs no Fable5
  (progress without burning its limits). **Guardrail:** the small tier is a MEANS (harden the
  pipeline), not the objective — pivot to the heavy 191 once multi-jtbl is proven; don't grind the
  light tail because it "feels productive." Wiki lesson: when a newly-built mechanism has an
  un-built sub-case that the expensive targets will hit, force that sub-case out on the cheap
  targets first — de-risking and building-the-missing-piece are the same move.

### 2026-07-13 — the jr-core ISOLATION wall: mechanical TU-splitting breaks gcc-2.7.2's lenient scoping

- **Context + belief:** Stage 2 of the multi-jtbl campaign (heavy jr cores → template ×134) needs each
  matched jr-function ALONE in its own code subseg so its jtbl carves without a same-subseg collision.
  Drew's steer: build the **scalable "isolate-ALL-jr-per-sibling" upfront resegment** (one-shot multi-cut
  per overlay) so every Stage-2 core bank is a trivial fill during the closing Fable5 window. Belief going
  in: this is mechanical source-splitting — partition the overlay `.c` at jr boundaries, repoint config +
  carves, rebuild byte-identical.
- **What was built + PROVEN:** `tools/overlay_src_split.py` — an overlay-`.c`-aware partition (header =
  includes + Phase-17 canonical-sig layer; each addressed item = its preamble + body; robust
  definition/declaration/K&R/`DEFINE_func`/`SETTER`/`RETCONST` classification). **Fleet-validated 404/404
  overlay `.c`, 341,902 items, round-trip exact / 0 unresolved / 0 non-monotonic.** `tools/jr_isolate_all.py`
  — multi-cut resegment (config split at jr boundaries, source repartition + INCLUDE_ASM path repoint,
  banked-jr carve repoint, -O0-object skip). **SINGLE-cut isolation byte-identical** (isolate func_8013FFD8
  in the simple `main` object → clean `make build` = `d19c9580`, R22).
- **What FAILED (byte-verified):** the FULL 54-jr isolation on ov_SC01_077 hits a **long tail of C-scoping
  edge cases**, culminating in the decisive one: **`func_801734BC` uses `D_80126B3E` with no local decl;
  `D_80126B3E` is declared `extern s16` ONLY inside `DEFINE_func` macros in `engine_core.h`.** The original
  `_after.c` compiles because **gcc-2.7.2 lets a block-scope `extern` (from an earlier `DEFINE_func` macro
  expansion) persist to file scope for the rest of the TU** — splitting `_after` separates the core from the
  earlier macro that declares the symbol → `undeclared`. Earlier tail members (all fixed incrementally, in
  order): block-scope externs must not be hoisted (per-fn type shadows — `D_80115118` is `unsigned short`
  in most funcs but the struct `S115118` in one); file-scope decl ORDERING across a cut (`D_80115110` used
  above its in-region decl); **ambient decl context** (a region needs the file-scope decls that lived in
  earlier regions of the object — solved: prepend, original order, shadow-safe because a file-scope-declared
  symbol can't carry a *different*-typed block shadow or the original wouldn't compile); file-local-typed
  externs (`extern Vec8 D_…;`) can't hoist above their typedef.
- **The why (root):** these overlay TUs are hand-matched against a compiler that treats a block-scope
  `extern` as declaring the symbol for the WHOLE TU. Mechanical splitting into per-jr TUs breaks that
  invisible cross-function dependency, and the dependency is carried through **`DEFINE_func`/`SETTER` macro
  expansions in `engine_core.h`**, not just visible col-0 decls — so no amount of *col-0* ambient-carry
  fixes it.
- **The candidate fix (not yet built):** **declaration-completion** — build a global symbol→type map from
  `engine_core.h`'s macro `extern`s + all overlay col-0 decls, and for each region emit a file-scope
  `extern <type> <sym>;` for every `D_`/`func_` symbol the region USES, EXCLUDING type-inconsistent symbols
  (the `D_80115118` shadow set, kept block-scope in bodies). This makes every region self-contained
  regardless of where the original declared the symbol. Est. ~40–60 LOC on top of the proven parser; the
  whole-binary byte-gate arbitrates. **Owner decision pending (Drew): invest in declaration-completion vs
  a different Stage-2 approach** — surfaced this session before sinking more time (P5a: repeated failures,
  distinct root cause each).
- **Hindsight / for the wiki:** "mechanical source split" of matching-decomp overlay code is NOT mechanical
  — the C is written against a specific compiler's lenient scoping (block-scope-extern TU persistence,
  macro-injected decls, per-function type shadows). Splitting a TU means REBUILDING each fragment's full
  declaration environment from a global symbol map, not relocating text. The parser (structure) was the
  easy 20%; the declaration environment (semantics) is the 80%. Prove the mechanism on the SIMPLE object
  first (it passed) but budget for the dense object's scoping tail before committing to upfront-×134.

---

## 2026-07-13 (session 6) — the §8b scoping wall RESOLVED: rebuild the decl environment, don't map symbols

**Context + belief going in.** Session 5 hit a wall isolating jr cores: the full 54-jr split of `ov_SC01_077`
failed with `D_80126B3E undeclared`, and I logged the cause as **"gcc-2.7.2 block-scope-extern TU-persistence"**
— i.e. a non-conformant compiler quirk where an `extern` inside one function body leaks to file scope for the
rest of the TU. The proposed fix (Drew-approved) was **declaration-completion**: build a global symbol→type map
and emit a file-scope `extern` for every symbol a region *uses*, minus a heuristic "type-shadowed set".

**What was actually wrong (R14 — the hypothesis was incorrect).** There is no gcc quirk. `DEFINE_func_80173460()`
expands **at file scope** to `extern void func_801734BC(...); extern struct S80126B38 D_80126B38; extern s16
D_80126B3E; void func_80173460(...) { … }`. Those externs are *genuinely file-scope* — they are merely
**textually invisible in the `.c`**, because they live in `engine_core.h`. Any col-0 scan of the source can
never see them. The wall was a blind spot in our own tooling, not a compiler eccentricity.

**The pivot — and why the approved design was the wrong one.** Chasing "declare every used symbol from a global
type map" would have been actively harmful. The engine is loosely typed: `func_80173544` is *defined* at file
scope as `s32 f(void *)` while `func_801734BC`'s body declares `extern void f(void);` — contradictory, and legal
only because the block-scope decl never meets the definition. Hoisting "every used symbol" lifts that shadow to
file scope, **creating** a conflict that then needs the heuristic shadow-set to dodge. Instead I **reconstructed
the original TU's file-scope declaration environment and carried it strictly forward**. That is conflict-free
*by construction*: every carried decl already coexisted with every definition in the one original TU, and decl
compatibility is order-symmetric. Shadows stay inside bodies and travel with them. No heuristic, no shadow set.

**What the bytes taught (found by gating, not by reasoning).** Three decl sources were lost, not one — and I only
found #2 and #3 because the byte-gate kept failing with a *new* error class each time:
1. `DEFINE_func_*` macro leading externs (3,929 lines / 1,462 symbols) → `D_80126B3E undeclared`.
2. **A definition is itself a declaration** for everything below it in its TU → `func_8012B2CC undeclared`.
3. File-local typedefs used by a carried prototype → `parse error before '*'` (`Vec3s`).

**Result.** Full 54-jr isolate-all on `ov_SC01_077` → `d19c9580` byte-identical, **R22 clean-fleet 136/136**.
Two latent bugs fell out and were fixed: `func_subseg` derived the owning subseg from the *asm tree*, which
`make extract` never prunes — so after an isolation it returned the STALE owner and silently re-created the
collision the isolation had just removed (now derived from the config); and the sweep's revert **deleted** the
shared `overlays.mk` carve var unconditionally, which would have destroyed a *committed* carve (all 134 overlays
have one) on any failed sibling (now restored to its committed value).

**Upfront vs lazy (new information for the owner).** Drew chose lazy isolation when isolate-all was *failing*,
to avoid ~7,200 region files. Isolate-all is now byte-proven at 136/136, so upfront is available — but lazy is
strictly cheaper (pay only for cores we bank) and is what shipped: `jtbl_family_bank` catches `jtbl_carve`'s
`NON-CONTIGUOUS` fail-loud → isolate that one core → re-carve. Proven on `func_80178D40` (890×134, the heaviest
core): blocked → isolated (byte-neutral) → carve lands in its own subseg. **The heavy-jr harvest is unblocked.**

**Hindsight / for the wiki.** Two lessons. (1) *A wall's stated root cause is a hypothesis until the bytes
confirm it* — I recorded a compiler quirk that did not exist, and the "fix" it implied would have introduced
real conflicts. Re-derive the mechanism before building on it. (2) *Splitting a translation unit is a semantic
operation, not a textual one.* The parser (structure) was the easy 20%; the declaration environment (semantics)
was the 80% — and the correct move is to **reproduce the environment the original had**, never to invent a new
one from a global map. Faithful-forward-carry needs no heuristics; "declare everything used" needs a growing
pile of them.

## 2026-07-13 (session 8) — the ×133 sweep blocker was OUR tool, not the compiler: the R17 triage rule, applied

**Context / prior belief.** Session 7 banked `func_8015AE2C` (562 ins, reach 134) ×1 but its ×133 sibling sweep
failed on `conflicting types for D_801812A4`, and the checkpoint diagnosed it as `reconcile_decls` resolving
against a *fleet-majority* canonical oracle instead of the type the TU can actually see. Drew had just asked the
routing question and we had committed the rule: **"wrong BYTES" → read the gcc source (R17); "won't COMPILE" →
read our Python.** This was the first real test of that rule, and it held — but the diagnosis underneath it was
only half right, and the half that was wrong is the interesting part.

**What the bytes taught.** Reproducing one sibling by hand (rather than trusting the handoff — R14) produced a
much sharper picture than the checkpoint's:

1. The **isolated region compiles and builds `[ OK ]` *without* the body.** So §8b isolation was never implicated.
   The conflict is introduced *entirely* by the templated body.
2. `D_801812A4` was the **only** hard error in the whole build. All 27 carried *function* externs were fine raw —
   `cast_call_sites` was not needed at all. (The checkpoint's "cast_call_sites already fixes the function half"
   was true but irrelevant; it also implied ~4 data symbols needed reconciling. Eight were demoted; none needed
   a type reconcile.)
3. The real mechanism is an **ordering asymmetry**, both halves byte-proven:
   `BLOCK(int) → BLOCK(struct*) → FILE(void*)` builds; `FILE(void*) → BLOCK(int)` is a hard error.
   `family_remap.gather_externs` prepends carried decls at **file scope**. For a per-location symbol the sibling
   declares only at *block* scope inside its own later functions, that carried decl **establishes a global
   declaration the TU never had** — and every later block-scope `extern` of it must now agree. In loosely-typed
   engine code they never do. `D_801812A4` is one fn-ptr dispatch table declared **four incompatible ways** in a
   single region and the TU is perfectly happy — until we add a fifth decl *at the top*.
4. `reconcile_decls` was the wrong instrument **twice**: its oracle answers "what does the fleet call this
   symbol" when the question is "what can *this TU* see" — and its `DATA_DECL_LINE_RE` **cannot parse the
   fn-ptr-array form** `extern void (*D_x[])(void *);` at all, so it silently skipped precisely the symbols that
   were failing. (This is the same "reconcile fn-ptr-extern gap" logged on 2026-07-12; it had been filed as a
   *separate, smaller* lever and was in fact the blocker itself.)

**The pivot.** Don't teach `reconcile_decls` a TU-visible oracle (the checkpoint's plan, and a much bigger,
riskier change to a proven path). Instead **don't change the TU's decl environment in the first place**:
`tools/scope_data_externs.py` demotes a carried `D_` extern to **block scope inside the function body** whenever
the TU has no file-scope decl of it above the insertion point. It then declares no global, nothing below can
conflict, and the environment is preserved exactly. Byte-neutral (an `extern` emits no code; the declared type
and every access opcode are unchanged), and *strictly never worse than raw*, so it needs no type comparator, no
fn-ptr parser, and no oracle. It also **restores fidelity** — the original source declares these symbols at
block scope in exactly this way. Wired as the `scoped` stage (raw → scoped → recovered → reconciled).

**Result.** First sibling byte-identical on the first try; the 133-sibling sweep run to completion.

**Hindsight / for the wiki.** Three lessons. (1) **The R17 triage rule paid for itself immediately.** The
temptation with a `conflicting types` failure on a 1997 compiler is to assume the compiler is being exotic. It
was not — gcc was correctly rejecting plain C89, and every minute spent in `cse.c` would have been wasted. *Ask
which half of the compiler is complaining: the front end (our C is invalid → our bug) or the back end (our C is
valid but the bytes differ → read the source).* (2) **A tool that no-ops on the failing input looks exactly like
a tool that has nothing to fix.** `reconcile_decls` reported success while skipping the only symbol that
mattered, because its regex couldn't see fn-ptr arrays — a silent-skip class we have now been bitten by three
times (`find_site` braces, `overlay_files` splits, this). Prefer transforms that *fail loud on unparsed input*.
(3) **The cheapest fix was to do less, not more.** The instinct was to make our reconciler smarter (a TU-visible
oracle, a fn-ptr type comparator, a cast-at-use taxonomy). The correct move was to stop perturbing something we
had no business perturbing. When a transform breaks a TU, first ask what it is *changing* that it needn't.

## 2026-07-13 (session 8, Fable5 Max) — func_8017BEBC closed: the allocno-tie class is a DIAL, not a wall

**Context / prior belief.** The 952-ins jr core (reach ×113, the largest unmatched function in the game) sat at
close=2 — two transposed preheader `addiu`s. The session-7 Fable5 agent had localized it to `global.c`'s
allocno-priority tie and prescribed a §45-B gdb-on-cc1 read of `allocno_live_length`; the permuter had run 25
minutes without closing it. The residual class: allocation order and emission order are COUPLED (both follow
creation order), but the target needs them to DIFFER — the shipped draft could have either correct, never both.

**What the bytes taught.** The dumps alone settled it — gdb was never needed. `.lreg` gave the two pseudos'
ground truth: refs 13/13, live lengths 783/782 → `pri = int(390000/L)` = 498/498, an EXACT int-truncation tie
(the agent's remembered "270000/L" had the wrong refs count — reading beats recalling, R14). The quantization
boundary sat one insn away: +1 on both lengths → 497 vs 498. And the split direction is FORCED: the later-created
pseudo always has the shorter live range, so a split always hands it the earlier allocation — precisely the
"allocation ≠ creation" the target requires.

**The pivot.** Rather than hunting an L-shifter that survives cse (the agent's proposed hunt), the map's own
zero-byte-asm toolkit already contained the dial: `__asm__ volatile ("")` placed BETWEEN two existing GTE
volatile asms adds no new cse/sched barrier (one is already there) — it is purely +1 static insn at
global-alloc time, zero bytes emitted. Natural operand order restored (emission correct), one slider inserted →
MATCH 952/952 first try. Whole-binary gate BYTE-IDENTICAL (jr function — the §8a trap respected); one TU-visible
decl reconcile en route (`D_800B9A02`, §8d sub-class b). Banked ×1; the ×113 sweep is IMM-class Task-8 work.

**Hindsight / for the wiki.** (1) *An "irreducible" tie is often a measurable quantization accident* — the
formula is public, the dumps print its inputs, and the fix is one insn of live-range arithmetic. Before
declaring a register-order residual intrinsic, READ THE PRIORITY NUMBERS. (2) *The dumps-first discipline
scales:* .lreg/.greg gave everything gdb would have, at a fraction of the setup. gdb remains the tool for
DYNAMIC questions (which reg find_reg actually grants when hand-modeling stalls), not for static quantities the
dumps already print. (3) *The zero-byte toolkit compounds:* the slider now joins the density dial and the
lifetime-extender as the third allocation dial that emits nothing — and the "adjacent to an existing volatile
asm" placement rule makes it safe in GTE-heavy renderers, which is exactly where the remaining jr cores live.

## 2026-07-14 (session 8) — the silent-skip class: promote the lesson from a rule to a MECHANISM (Drew approved)

**Context / prior belief.** Six silent-skip bugs surfaced in one session (`scope_data_externs`' file-scope
placement; `extract_unit` decl-vs-def; `_body_open_brace`'s own-line brace; `SIG_IN_BODY_RE`'s 10% oracle hole;
`revert()`'s config residue; `jr_isolate_all`'s empty region 0) — and THREE were the same brace-placement class,
the same class as the Phase-15 `find_site` bug and the Phase-24 `overlay_files` bug. Each was written off at the
time as a one-off parser slip.

**What the bytes taught.** They are not one-offs; they are a *structural* blind spot in how this project is
built. Every instance has the identical shape: **a scanner extracts N items from a corpus, the true count is
M > N, and nobody ever compared N to M.** The whole-binary byte-gate (G3/P9) is a perfect guard on
*correctness* — it never once accepted a wrong match — but it is **blind by construction to work that was never
attempted**. A tool that silently no-ops on input it cannot parse is indistinguishable from a tool that had
nothing to do. That is why these survived 26 phases: nothing in the system was looking.

The cost is not hypothetical. `SIG_IN_BODY_RE` hid **186 of 1801 (10%)** of the shared-callee signatures, which
is why nine byte-exact cores from the crack wave would not bank — the draft kept its guessed signature, hit
`conflicting types`, and the recovery pass truthfully reported nothing to fix. It read exactly like an intrinsic
wall. One character class turned it into a zero-hand-edit bank.

**The pivot (Drew, "agreed").** Promote the lesson from a *rule* to a *mechanism*, and do NOT audit by reading
regexes — that is precisely the failure mode that wrote them. Instead **measure coverage**: for each scanner,
build a deliberately OVER-APPROXIMATING candidate detector, run both over the corpus, and report
found-vs-candidates; every gap must be classified as a real skip or a justified exclusion. Going forward, a new
text scanner ships with a coverage assertion or it does not ship. (Rule candidate for PhaseEnd, P10.)

**The bigger prize (the uncomfortable part).** Several verdicts we have treated as settled physics were reached
*on top of* the broken oracle: the **def-side loose-typing wall** (§20/§41, "triple-confirmed" in Phase 23), the
**159 arity/narrow-param conflicts** (Phase-15 "documented dead-end"), the **3,098 type-heavy tail**, the 9
zero-bank type-using families. Each was diagnosed as "no C declaration exists satisfying both the definition and
the call site" — but the tool computing the call site's canonical signature was blind to 10% of them. Phase 16
byte-proved that genuinely contradictory typings DO exist, so the wall is real in part; but **"some of it was our
tooling" is now the prior, not the long shot.** Re-test the cheap ones against the repaired tools.

**Hindsight / for the wiki.** The deepest lesson of the phase, and it generalizes far past decomp: *an
incorruptible correctness gate creates a false sense of completeness.* It tells you everything you banked is
right. It tells you nothing about what you never tried. Pair every correctness oracle with a **coverage** oracle,
or you will spend phases mistaking your own parser's blind spots for properties of the problem.

## 2026-07-14 (session 8) — the coverage audit's biggest finding was REAL, and my reading of it was WRONG. The correction is the lesson.

**Context / prior belief.** Six silent-skip bugs in one session led to the coverage-oracle rule (Drew: "agreed").
The audit's headline came back alarming: *progress.py under-counts by ~243k instructions because classify()
reads a K&R definition as a forward declaration.* I verified the MECHANISM against the bytes (it is real:
`s32 f(arg0)` / `s32 arg0;` / `{` — the `;` precedes the brace, so the scan calls it a declaration and drops the
function into NO bucket), measured 400 banked instances / ~190k instructions in that shape, and told Drew our
headline numbers had been under-reporting our own progress.

**What the bytes taught — I was wrong, and the null result caught me.** After fixing it, old-vs-new on the same
tree moved the headline numbers by **+376 instructions**, not +190,000. A null result where a large effect was
predicted is not noise; it is a refutation. Reading the code: **`weighted_metrics()` never calls `classify()`.**
It determines "matched" as `func not in src_stubs(binary)` — and because the fleet is 136/136 byte-identical,
anything NOT wrapped in `INCLUDE_ASM` is necessarily compiled C emitting the exact original bytes. It never
parses a definition, so it is **structurally immune** to the bug. The published **instr-weighted (65.6%) and
distinct-code (44.9%) were CORRECT ALL ALONG**; only the secondary REAL count and fn-count % were wrong.

I had done the R14 thing (verify the mechanism against the bytes) and still got the conclusion wrong, because I
verified the DEFECT and not its BLAST RADIUS. The auditor conflated "classify() is blind" with "the metrics are
wrong", and I propagated it — to the owner, as fact, in the same breath as lecturing about unverified oracles.

**The pivot.** Both bugs are still worth fixing (they corrupt the REAL/fn-count report, and the phantom-dedup
over-count double-counts 532 stubs) and a coverage assertion now guards classify(). But the strategic conclusion
inverts:

> **A metric DERIVED FROM A PROVEN INVARIANT beats a metric that RE-PARSES THE WORLD.**
> `weighted_metrics()` leans on the byte-gate — "not a stub ⇒ byte-exact, because the build is byte-identical" —
> and *inherits its correctness for free*. `classify()` re-derives the same fact by parsing C, and inherited a
> bug instead. Two tools, one question, and the one that refused to re-derive is the one that was right.

**Hindsight / for the wiki.** Three lessons, and the third is the real one.
(1) *Verify the blast radius, not just the defect.* "This tool is broken" and "this number is wrong" are
different claims needing different evidence. A confirmed mechanism proves nothing about consequence.
(2) *A null result where you predicted a large effect is a refutation — chase it.* The +376 delta was the whole
story, and it would have been trivially easy to wave off as noise or as "the fix worked, the numbers moved".
(3) **The coverage-oracle rule is right but incomplete.** Auditing parsers is treating the symptom. The cure is
to STOP PARSING where an invariant already answers the question. Our byte-gate proves a strong property
(byte-identical build); every fact derivable from it should be *derived*, not re-computed by regex. Before adding
a coverage assertion to a scanner, ask the better question first: **why is this scanner re-deriving something the
build already guarantees?**

## 2026-07-14 (session 8 close) — Drew: the TOOLING-INTEGRITY AUDIT gates further matching work, and gets its own phase

**Context / prior belief.** Session 8 was the most productive of the project: 13 cores cracked (incl. the four
heaviest functions in the game), a 12-agent wave at 11/12 first-pass MATCH, fleet 63.0→65.6% instr-weighted /
39.1→44.9% distinct-code, 136/136 byte-identical throughout. The natural next move was obvious: bank the six
blocked cores (~1.2 MB, all plumbing), then run the next wave.

**Drew's call:** *"I feel like we should do T14 now, before the rest of the work. but not in this phase."*
The tooling-integrity audit **gates** the remaining matching work, and it is substantial enough to deserve its own
phase rather than being squeezed into Phase 26.

**Why this is right (and why I would not have prioritised it as hard).** The session found **seven silent-skip
tool bugs**, and the instinct is to treat them as a tax — annoying, fixable, keep moving. That instinct is wrong,
for a reason that only became clear at the end:

> The byte-gate is a perfect CORRECTNESS oracle and a **null COVERAGE oracle**. It never once accepted a wrong
> match — and it is blind *by construction* to work never attempted. It has been green since Phase 5, when 0% was
> decompiled, because `INCLUDE_ASM` pastes the ORIGINAL assembly: **a green byte-gate is compatible with any
> decomp percentage.** So every silent skip is invisible to the one instrument we trust absolutely.

The cost is not wrong answers. It is **invisible work, and walls that aren't there.** A single 10% hole in the
callee-signature oracle (`SIG_IN_BODY_RE`, a `\s` that could not match a line-continuation backslash) made **nine
byte-exact functions look like an intrinsic compiler wall** — and we would have written them up as such. How many
of the walls we have already "byte-proven" across 26 phases were lookup misses wearing a wall's clothes? The
def-side loose-typing wall, the 159 arity conflicts, the type-heavy tail — all were diagnosed on top of that hole.
**That is the question the audit answers, and it is worth more than the next 1.2 MB.**

Auditing after more matching would compound the problem: every wave run on broken selection tooling produces more
"walls" we would then have to re-litigate.

**Scope discipline (do NOT audit all 82 tools).** 19 were audited (23%), chosen by risk. The filter for the rest
is: **does it PARSE something, and does it GATE or SELECT work?** (~15 tools.) Priority order:
`dedup_integrate.py` (a fail-closed validator that can print a FALSE GREEN — *"1813 validated, 0 failed"*) →
`jtbl_family_bank.py` (3 bugs found by hand this session, never audited) → the SELECTION tools (`family_hseq`,
`wave_targets`, `exemplar_miner` — a hole here makes work invisible to *planning*, the worst kind) →
`masked_diff`/`match_one` (the closeness oracle every agent trusts).

**And apply R33 to each, first:** *why is this tool re-deriving something the build already guarantees?*
`harvest_verify` is the model — it derives from `make build` + SHA1, so a parse hole makes it **conservative, not
wrong**. Tools that lean on the invariant inherit its correctness for free; tools that re-parse inherit bugs.
The best audit outcome is not a fixed regex — it is a **deleted scanner**.

**Hindsight / for the wiki.** The owner saw this faster than I did. I had just spent the session proving that
every wall was our own tooling, had written the coverage-oracle rule, had *corrected myself* about a metric — and
my instinct was still "bank the 1.2 MB first". The lesson: **when your measurement layer is suspect, more
measurements are not progress.** Fix the instrument before taking more readings.

---

## 2026-07-14 (session 9) — The audit runs as an INSERTED HALF-PHASE, not as Phase 27

**Context.** Session 8 closed by gating the tooling-integrity audit ahead of all further matching work (entry
above) and left the phase-boundary shape as an explicit Tier-1 question for the owner: **(a)** close Phase 26
early with a PhaseEnd and open the audit as Phase 27, or **(b)** run it as an inserted half-phase (the Phase-3.5
precedent) and return to Phase 26 afterwards.

**Drew's call:** *"audit as an inserted half-phase in the current phase and then resume phase 26."* (Effort: Max.)

**Why (b) is right.** Option (a) reads as the tidier choice — a clean PhaseEnd, a fresh phase, a fresh context
window. But it would have closed Phase 26 on an **unmet milestone**. Phase 26's milestone is *structural
completion*, and the audit is not a **successor** to that goal — it is a **prerequisite** to reaching it: the
family engine's own numbers are what the audit found broken (93 of 218 "matched" exemplars are phantom; 1,834
clean member templates never attempted; 407 of 811 overlay files invisible to propagation). Closing the phase
would have forced a PhaseEnd that reported the milestone as abandoned, when in fact the tooling that *measures*
the milestone was the thing at fault. The half-phase keeps the goal live and fixes the instrument under it.

The Phase-3.5 precedent is exact: a spike inserted mid-arc, on the owner's directive, to answer a question that
gates the work either side of it. It closed with a go/no-go, not a PhaseEnd, and the roadmap resumed.

**The structural insight this rests on (worth repeating, because it is the whole reason the audit exists).**
A scanner extracts N items from a corpus; the true count is M > N; **nobody ever compared N to M.** The seven
silent-skip bugs were not typos — they are that one blind spot, seven times. And the byte-gate cannot see it:
it is a perfect correctness oracle and a **null coverage oracle** (green since Phase 5 at 0% decompiled, because
`INCLUDE_ASM` pastes the original asm). So the audit's ordering rule is **R33 before R32** — before adding a
coverage assertion to a scanner, ask whether the scanner should exist at all. **The best outcome is a deleted
scanner, not a fixed regex.**

**First finding, immediately (A1).** `dedup_integrate.py` — the fail-closed byte-honesty validator, and the
audit's #1 priority precisely because a silent skip there prints *a false green from a gate* — has **three**
false-green paths, all confirmed within minutes of opening it: the 7 stale registry groups name a `DEFINE_func_*`
macro with **zero hits in `src/`** and still print `[ OK ]`; an **absent** `.run/sig.*.jsonl` yields
*"0 validated, 0 failed"* and **exit 0** (on a fresh clone the gate validates nothing and passes); and it never
checks that a member is **actually banked** rather than still `INCLUDE_ASM` — which is exactly the invariant the
build already proves. The tool that guards byte-honesty was the one least able to prove its own.

**Hindsight / for the wiki.** The owner's framing — *fix it inside the phase, don't ceremonially close the phase
around it* — avoided a subtle honesty trap. Writing a PhaseEnd that says "milestone: not met, closing anyway"
when the real story is "our measuring tape was short" would have been technically true and substantively
misleading. **Phase boundaries should follow the work, not the paperwork.**

---

## 2026-07-14 (session 9, A2) — The audit found the endgame plan was majority-fiction

**What we ran.** 6 auditor agents over the 18 unaudited PARSE+GATE/SELECT tools, each finding handed to an
independent skeptic told to REFUTE it. 38 agents, 2.24M tokens. 32 findings raised → **28 survived**, 4 refuted,
16 downgraded, and **40 scanners measured clean**. The skeptic pass earned its keep: it killed four claims and
corrected magnitudes in both directions.

**The root cause is singular, and it is not a regex.** Almost every finding is the same defect:

> a hand-maintained model of the corpus layout — a file allowlist, a single-`.c` assumption, a `func_`-only
> symbol regex, a `REGION_SUB` dict — sitting on top of a **filesystem that already answers the question**.

An overlay's source is spread over up to 14 `.c` files (`<ov>.c`, `_a`, `_o0`, `_o0b`, `_after`, and the Phase-26
`_jr_<ADDR>` carves). Tools written when there was one file still believe there is one file. **The decay is
measurable:** `.run/fuel_manifest.json` from Jul 8 recorded 130 live stubs; the same tool run today returns **30**.
The Phase-26 splits moved ~100 stubs out from under a dict literal last edited in Phase 22. **Nobody noticed,
because a target that is never nominated produces silence, not an error.**

**Why this is worse than a wrong answer.** 91.6% of all remaining project gain is invisible to the target-selection
layer (994,633 instructions of real work; the manifest sees 83,305). 117 of the 127 reach-134 functions — the
entire high-ROI band — are never nominated by anything. We were about to run Task 7's crack waves against that.

**Three results overturn things we had written down as settled:**

1. **"The permuter's fuel is exhausted" (Phase 22) is unsafe.** The grinder banks through `harvest_verify`, which
   can only see one translation unit — and **1,290 of the grinder's own 1,298 queued functions live in a different
   one**. 99% of its queue could never have banked, however good the permuter's output was. "7 all-time banks, 0
   since Phase 21" is *equally consistent* with "the tool could not bank" as with "there was nothing to bank."
   We concluded the latter and moved on. **Re-test before repeating it.**

2. **The Phase-25/26 endgame plan is majority-fiction.** `docs/family-manifest.md` — the document the whole
   structural-family endgame is planned from — advertises 2,758 multi-member families holding 11.0 MB of hidden
   leverage. **1,071 of them (6.80 MB, 62% of the advertised byte-weight) are already fully matched.** The
   matched-set oracle scans a single overlay. So the byte-weight *ranking*, which is the entire purpose of the
   file, is sorted mostly on dead work, and the real targets are buried under phantoms.

3. **A corpus defect the byte-gate cannot see, and never could.** `config/symbols.us.txt:981` declares
   `listCdBuffer = 0x80180000` — a main-EXE **data** symbol — and every overlay's splat config loads that file. In
   overlay space, 0x80180000 is **code**. splat therefore cuts 97 real functions in half and invents 96 phantom
   ones: **193 slices that cannot be matched by anyone**, across 97 of 134 overlays. You cannot write C for a
   function that ends on a `lui` with no return, nor for one that begins by reading the assembler temp `$at`. They
   sit in the harvest queue as ordinary work items, so agents burn on them indefinitely and the failure reads as an
   intrinsic compiler wall. **And the full-binary byte-gate stays green the entire time**, because the `.s` halves
   are pasted back verbatim in original order.

   This is the purest instance of the thesis that motivated the audit: *the byte-gate is a perfect correctness
   oracle and a null coverage oracle.* And note precisely what rescued us — **`sig_image` was right.** Its
   independently-computed function boundaries agree with spimdisasm on 58,524 of 58,621 functions, and on all 97
   disagreements sig_image is demonstrably correct. **A second, independent oracle is the only reason the defect
   was visible at all.** That is a design lesson worth more than the fix: when one oracle is structurally blind to
   a class of error, the answer is not a better assertion inside it — it is a second oracle that can disagree with it.

**The fix follows the root cause: ONE derived corpus oracle, and ~10 deleted scanners.** Not ten fixed regexes.
`tools/corpus.py` answers — from the filesystem and the proven invariant, with coverage assertions baked in —
*which files make up a binary*, *which stubs are live*, *which functions are matched* (sig − stubs, derived, never
re-parsed), and *where a function's asm lives* (globbed, because splat already wrote the truth). Then the allowlists,
the `REGION_SUB` dict, the single-TU regexes, and `census_conflict_callees` in its entirety all get deleted. This is
the "best outcome is a deleted scanner" rule (R33) applied at scale.

**Hindsight / for the wiki.** The strategic error was not writing any one of these tools badly. It was **letting the
corpus layout become a fact that lived in ten places**. Each split was a correct, well-gated change to the *build*;
none of them updated the ten private models of the tree, and nothing existed to notice. **A derived fact has no
maintenance cost and cannot rot; a hand-maintained copy of it is a liability that grows with every structural
change.** And the reason it stayed invisible for four phases is the deepest lesson of the audit: *we had no
instrument that could report absence.* Every gate we owned answered "is this right?" — none answered "is this all?"

---

## 2026-07-14 (session 9, A4) — A corpus defect the byte-gate could never have caught

**The defect.** `config/symbols.us.txt:981` declared `listCdBuffer = 0x80180000`. That is a correct,
Phase-3-derived name for a main-EXE RAM buffer (the LIST.CD cache). But 0x80180000 lies **outside main's
image** (0x80010000–0x80074800) and **inside the overlay slot** (0x80128158–~0x801DAB30) — and every
overlay's splat config stacks `symbols.us.txt`. High RAM is *reused*: an address that is a buffer to
main is live **code** to an overlay.

So splat saw a symbol boundary in the middle of overlay code and, across 97 of the 134 overlays:

* **cut 97 real functions in half** — leaving a head that ends on a `lui` with no return, and
* **invented 96 phantom functions** — a tail that begins by reading the assembler temp `$at`.

**193 slices that nobody can ever match.** Not "hard". Not "a compiler wall". *Unmatchable by
construction* — there is no C you can write for either half. And they sat in the harvest queue as
ordinary work items, so agents would burn on them indefinitely and the failures would be filed as
intrinsic compiler residuals.

**Why no gate caught it, and why that is the important part.** `INCLUDE_ASM` pastes the two `.s` halves
back **verbatim, in original order**, so the image is byte-identical either way. The full-binary
byte-gate — the instrument this project trusts absolutely, and rightly, because it has never once
accepted a wrong match — **was green the entire time and always would have been.** It is a perfect
*correctness* oracle and a **null coverage oracle**. No assertion added *inside* it could ever have
found this.

What found it was a **second, independent oracle**: `tools/sig_image.py` derives function boundaries
from the ORIGINAL bytes without splat, and it *disagreed with the corpus*. It agrees with spimdisasm on
58,524 of 58,621 functions and is demonstrably correct on all 97 disagreements. That is the whole
lesson, and it generalises well past this bug:

> **When one oracle is structurally blind to a class of error, the answer is not a better assertion
> inside it. It is a second oracle that can disagree with it.**

`make audit-corpus` now *is* that second oracle, standing.

**The evidence that makes it concrete.** The phantom `listCdBuffer.s` in ov_SC01_005 begins:
`lw $ra, 0x10($sp)` / `addiu $sp, $sp, 0x18` / `jr $ra`. splat cut a function immediately before its
**epilogue** and called the epilogue a function. You cannot write C for a routine that restores a return
address it never saved.

**And it had already contaminated real work.** In `ov_SC03_031` the cut happened to land where the
epilogue was exactly `jr $ra; nop`, so the Phase-26 ×134 sweep innocently "matched" it as
`void listCdBuffer(void) {}` — byte-correct, gate-green, and completely fictitious — while leaving
`func_8017FFC4` permanently unmatchable. A phantom got *banked*.

**The rule, which nobody had written down.** R13/R15 say overlay-derived symbols are overlay-region only
and must never be merged into `symbols.us.txt`. The mirror is equally true and was never stated:

> **A symbol whose address falls inside ANOTHER binary's vram window must never enter that binary's
> symbol stack.**

Fix: `config/symbols.us.ram.txt` — main-scoped symbols that live outside main's image — stacked **only**
by `config/splat.us.exe.yaml`. Main keeps the name (its asm carries 10 `%hi` / 11 `%lo` references and
rebuilds `143dbb89` byte-identical); the overlays never see it. Exactly one symbol was in scope
fleet-wide, and the resident window was clean.

**Hindsight / for the wiki.** We had *two* oracles all along and never made them argue. The byte-gate and
`sig_image` were both trusted, both correct, and silently disagreeing about the shape of 193 functions
for four phases. The cheapest possible check — *do our two independent views of "where does this function
start and end" agree?* — was never run, because each oracle was individually green and nobody thought to
ask them the same question. **Redundancy is only worth what you spend comparing it.**

---

## 2026-07-14 — `cdecl`: parse the grammar, do not enumerate the shapes

**Context & belief.** The audit's own prescription for the fifteen broken declaration scanners was a
*shape-aware alternation* per tool: add an `(fn-ptr|sized-array|scalar)` branch to `DATA_DECL_RE`, mirror
it in `DATA_DECL_LINE_RE`, add a `fnptr` kind to `parse_data_decl`, add a fn-ptr arm to
`_uniquify_draft_types`, and so on — roughly fifteen coordinated regex edits, each with its own
suggested coverage assertion.

**Why I did not do that.** The audit had *already proved* that fifteen independent hand-maintained models
diverge: two tools in ONE pipeline disagree today about whether `extern s32 D_a, D_b;` is a declaration.
Patching fifteen regexes is fifteen fresh chances to diverge again, and an alternation only ever covers
the shapes somebody remembered — it is the same hand-maintained model, one shape wider. The real problem
was never the character class. It was that **the thing being scanned has a grammar, and nobody was
parsing it.**

C's declarator grammar is small, closed, and **total**. It describes fn-ptr arrays, sized and 2-D arrays,
multi-declarators, fn-ptr parameters, and K&R identifier-lists *without being told they exist*. A
250-line recursive-descent parser is **less** code than the fifteen regexes it deletes, and it is
exhaustive by construction rather than by anyone's memory. That is R33 in its strongest form: the best
outcome is not a fixed regex — it is a deleted model.

**The measurement (not a belief).** Three oracles, whole corpus: coverage (**2,952,246 depth-0 statements
→ 2,731,521 declarators, 0 parser defects**), the real cross-gcc (**50,405 distinct declarations
round-tripped, 0 rejected**), and a differential against the incumbents (0 symbols they see at file scope
that `cdecl` misses; 26 in `engine_core.h` they cannot see; 6 they wrongly promote from *block* scope).

**Two design decisions worth keeping.**
1. **The candidate set is derived, not hand-written.** At file scope C admits nothing but declarations, so
   the over-approximating detector R32 demands is *every depth-0 statement* — supplied by the grammar,
   with no second model to rot. (LAW 4.)
2. **gcc adjudicates my own coverage gap.** When 40 statements would not parse, deciding for myself which
   "don't count" is grading my own homework — the precise habit that wrote the fifteen bugs. gcc decides
   instead: a statement it *also* rejects is not C (my rejection is correct, the input is corrupt); one it
   *accepts* and I do not is my defect. All 33 residual came back NOT-C, all in dead scratch. (LAW 5.)

**Hindsight / for the wiki.** The near-miss is the lesson. Those 33 corrupt drafts were written by a
*recovery tool* that prepended `extern` to an `if` statement, and I was one step from reporting a live
tool bug. Checking the blast radius instead (R14) showed the source defect was fixed back in Phase 19 —
today's oracle emits **0 garbage over 300 signatures**. *Mechanism confirmed, consequence nil.* But note
what it cost while it was live: a draft that cannot compile fails the byte-gate, and the failure reads
downstream as **an intrinsic compiler wall.** That is the audit's whole thesis in one artifact — and the
new parser is what finally makes the guarding assertion expressible: *every canonical signature the
callee oracle emits must PARSE as a C declaration.* Before `cdecl`, nothing in the repo could tell a
signature from garbage.

**Scope discipline (deliberate).** This commit lands the parser and its proof and changes **no consumer**
— so it cannot move a byte, and `check-all` is 136/136 by construction. That is not timidity: the audit
explicitly warns that *making the parser see more ARMS dormant downstream transforms* — the moment
`reconcile_decls` can parse a fn-ptr decl, its `data_access_subs` would happily mangle `D_1[i]()` into
`((u8 *)D_1)[i]()`. Consumer migration is therefore one tool at a time, each byte-gated.

---

## 2026-07-14 — Probe the compiler; and the adjudicator must BE the compiler

**Context.** Building `cdecl.compatible()` — *"will cc1 accept these two declarations of one name?"*, the
question every recovery pass in this repo actually asks and four of them half-implement. I wrote the rules
from the C standard, then validated them against a compiler.

**What happened.** The compiler contradicted me — and then the *right* compiler contradicted the first one.
Validating against modern `mipsel-linux-gnu-gcc` and against the real gcc-2.7.2 `cc1` gives **three
different answers** (with the standard as a third): typedef redefinition is an error in C89, accepted by
C11 gcc, and rejected by cc1; a qualifier mismatch is an error to modern gcc and **accepted** by cc1; the
no-prototype/narrow-param rule is an error to both — and **accepted by cc1 in one direction.**

**The decision.** `--compat` adjudicates with `tools/bin/gcc-2.7.2-psx/cc1`, the front end that actually
arbitrates the build. Now 1,485/1,485 live corpus pairs agree. **Validating a compiler rule against a
compiler that is not the one compiling your code is not a shortcut — it is the same class of error as the
five phases we spent reading `gcc-papermario` believing it was 2.7.2. It was 2.8.1.**

**The prize (→ A10).** Phase 15 closed the "159 arity/narrow-param conflicts" as *"no clean deterministic
fix — it is simply C's default-promotion rule."* **cc1 disagrees.** The rule is order-dependent:
`void X(s16); void X();` compiles; only `void X(); void X(s16);` fails. The wall's stated cause does not
hold. Four three-line probes, 90 seconds, zero tokens.

**Hindsight / for the wiki.** *Probe the compiler for FACTS; read its source only for LEVERS; byte-validate
both.* Reading source is inference and can be wrong (it was, for five phases). Probing is ground truth,
because it IS the compiler — and it is orders of magnitude cheaper. We have the exact binary sitting in the
tree and spent 26 phases reasoning about it instead of asking it.

**And the discipline that saved this from being an over-claim.** Fixing the wrong-TU bug (95.1% of drafts
canonicalized against a TU that would never compile them) took the callee-conflict repair from 8 to 58 of
196 drafts — 7× reach — and banked **exactly zero** functions, because the historical tail fails on codegen,
not plumbing. The real gain is narrower and still worth having: **52 drafts moved from "won't compile" to
"compiles, N instructions off"** — from an invisible failure that reads as a compiler wall into a scored
near-miss the permuter can act on. Three times in one session a confirmed mechanism produced a null
consequence. *"This tool is broken" and "this number will move" are different claims, needing different
evidence.*

## 2026-07-15 (session 13, A10) — the wall re-test verdict: the broken tools WERE the walls, and the payoff was banked by the FIXES

**Context + belief.** The audit set out to answer one question (its own thesis): *how many of the walls we
byte-proved across 26 phases were lookup misses wearing a wall's clothes?* Going in, the honest prior — set by
the `SIG_IN_BODY_RE` finding, where one 10% oracle hole made nine byte-exact functions look like an intrinsic
compiler wall — was *"some of it was our tooling."* A10 was gated ahead of all matching to test that at scale.

**What we found.** The payoff did not come from A10's own re-gating — it came from the **fixes**, and it was
already banked by the time A10 ran: retiring the fleet-majority oracle (A3d → `reconcile_tu`), the all-TU gate
(A3e), the h_seq callee oracle (`SIG_IN_BODY_RE`), the fn-ptr blindness (A9a), and the `build_engine_types`
blocker (A7) collectively moved the fleet **66.5 → 68.6% instr**, with the flagship proof being A9b —
`func_8017A4AC` (536 ins × 134), a "blocked on plumbing" wall since session 8, banking ×134 the moment the
oracle it tripped was fixed. **The walls named in this audit's thesis were, in the parts that moved, our tooling.**

**The pivot inside A10 (measure, then adapt — R14).** The obvious A10 move — brute re-gate the 958
`closeness==0` backlog drafts through the fixed gate — was tested first on one overlay (0/14 bank) and then
settled at fleet scale: **0 of 958 bank across 135 binaries.** `match_one closeness==0` (isolated,
reloc-masked) systematically overstates whole-binary bankability; the fixed gate recovers **none** of them.
So rather than a Workflow fan-out that would have burned agents confirming a null, A10 ran it as a
deterministic parallel job and reported the number. **The closeness-0 residual is genuine codegen — a
re-confirmed wall (P9), which is as valuable as a dissolved one: it tells the endgame where NOT to look.**

**The better path, in hindsight.** The single most load-bearing lesson is upstream of any specific fix:
**a green byte-gate is compatible with any decomp %, so it can never tell you what you failed to attempt.**
Every wall this audit dissolved was invisible to the one instrument we trusted absolutely — not because the
gate was wrong, but because it is a correctness oracle with a null coverage dimension (R34). Had a coverage
oracle (R32) and a *second, disagreeing* oracle (R34) existed from Phase 6, most of these walls would never
have been written down as walls. The audit's real deliverable is not the ~15 fixes — it is the three rules
(R32/R33/R34) and the derived-oracle pattern (`corpus.py`/`cdecl.py`) that make the *next* 26 phases unable
to manufacture a wall out of a lookup miss.

**Handed forward:** #4 the type-heavy harvest (~1,200 members; `build_engine_types` unblocked but not yet
wired into the family path — Phase-26 Task-8 integration, not a re-test). Substrate for the retrospective + the
public "how to AI-decomp" wiki (R31): *audit your instruments before you trust their silence.*

### 2026-07-15 — Phase 26 Task 7 resume: re-baseline corrections + the flagship regalloc wall (single Fable5, likely intrinsic)

**Re-baseline before cracking (R14).** Task 7 resumed at xHigh after the audit. Regenerating the target
frontier from the FIXED tools corrected the handoff twice, both byte-grounded: (1) the "~1,200-member
type-heavy harvest" from the audit ledger was **already banked** by A3h's post-fix h_seq re-run (+2,675) — the
current STRUCT-excluded tail is ~6 substantial members, not 1,200. (2) The real remaining deterministic lever is
bigger and different: **128 matched-sibling families ≈ 2.64M templatable ins**, and **register pins are NOT a
banking blocker** (`func_8017A4AC` banked ×134 with 4 pins/sibling) — so most of that is *un-run ×N sweeps*, not
a wall. Also: all 97 reach-134 tractable cores are already walled, and re-gating the close 1-5 seeds through the
fixed pipeline banked **0/13** — Task 7 is a near-miss CLOSING campaign, not fresh cracking.

**The single-Fable5 test ("can we crack not on Max?" — Drew).** One Fable5 (xHigh orchestration, 477k tokens,
93 min) on `func_80178004` (165 ins ×134, the regalloc-order class exemplar shared by 12 siblings). Result: an
**honest wall** (P9). A pin-free draft driven to structure-exact (163/165); residual = pure register identity,
reduced by a gdb-on-cc1 oracle to **three compiler-internal integers**, each ruled unreachable under every legal
C construct with file:line evidence. Byte-verified: `match_one` 126/165, the 126 dominated by one `$s0`↔`$s2`
swap. **R14 ledger correction:** the historic "pinned MATCH / close=0" was a myth — the seed was never a match
(best historic permuter score 5, pinned). Likely intrinsic to gcc-2.7.2; ONE untested lever remains
(`qty_n_refs` tie-shape, local-alloc.c:1869). The parallel permuter could not crack `func_801325B8` either (best 25).

**Payoff despite the wall (R16 flywheel).** The pass produced 6 byte-proven "walker-family" levers + the
skeleton idiom (cookbook §52) that transfer to the 11 regalloc-order siblings: **Fable5 DISCOVERS the skeleton,
cheap-Opus APPLIES it.** So a walled exemplar still fed the flywheel.

**Pivot (pending Drew's Max call, R27).** Per Drew's instruction the failed single-Fable5 → prompt for Max.
Recommendation to be logged on decision: Max-grinding `func_80178004` itself is low-EV (Fable5 already went to
depth; one untested lever); the higher-ROI use of the perishable window is the §52 sibling-idiom wave
(cheap-Opus) + the deterministic matched-sib harvest (2.6M-ins ceiling, pins OK) — both higher-certainty than
grinding an intrinsic wall.

### 2026-07-15 — Phase 26 close: the mechanical-harvest thesis is byte-proven exhausted → close + Phase-27 fresh scans

**The §52 flywheel worked — and then the byte-gate closed the phase.** The single-Fable5 failure on `func_80178004`
still distilled the walker-family idiom (§52), and two cheap-Opus waves applied it to bank **5 pin-free regalloc
cores ×134 = 670 instances** (68.6→68.9% instr), confirming *Fable5 DISCOVERS, cheap-Opus APPLIES* and the
crack-then-template loop for CLEAN families.

**The correction (P9/R14 — walking back my own prior entry).** The entry above recommended "the deterministic
matched-sib harvest (2.6M-ins ceiling, pins OK)" as *higher-certainty*. **That was wrong.** Three byte-gate
probes returned 0% — tiny-IMM 0/241, PURE reach-134 0/134, and pinned-PURE-templated-WITH-pins 0/133 (so the
`func_8017A4AC` pinned-×134 precedent does NOT generalize). The manifest's ~13,075 "templatable" member-slots
are an h_seq *prediction* the whole-binary gate refuses (collision / register-drift / pin-crash). A3h + the wave
propagations already banked everything cleanly templatable. The mechanical/templating thesis is spent at
68.9% instr / 49.2% distinct.

**The pivot (Drew, 2026-07-15).** Close Phase 26; open Phase 27 with a byte-gate-honest re-scan. Why it matters:
the 26-A audit fixed the TOOLS, but the megaplan's frontier was scoped by the PRE-audit (buggy) scans, and even
the post-audit manifests over-predict templatability (h_seq ≠ bankable). The remaining work is a different shape
— hard-wall cracks + hand-decomp of the genuine unique residue — and deserves a plan built on a gate-validated
frontier, not a manifest that over-promises phantom members.

**Hindsight better-path — the phase's most transferable lesson:** *a scan is a hypothesis; the byte-gate is the
truth. Validate a "templatable"/"matchable" count against the gate with one small probe BEFORE scoping a whole
phase around it.* The megaplan's "986 families / 2.6M ins" set an expectation the gate then had to walk back
twice this session; a probe up front would have sized the real yield. This is R14 applied at planning scale, and
it is exactly why Phase 27 opens with a gate-validated re-scan.

### 2026-07-15 — The Road-to-100 roadmap adopted (Phase 27+); the megaplan superseded

**Context.** Phase 26 closed on the honest pivot (mechanical harvest byte-proven exhausted; instruments made
trustworthy by the 26-A audit). Drew directed a plan-mode session (Fable5, Max): not a Phase-27 plan but a
**full roadmap from 68.9% instr / 49.2% distinct to game-code 100%**, grounded in the audit. Method: all 26
PhaseEnds + 3 scout distillations (audit / frontier / strategy) + a 16-defect red-team pass. Deliverable:
**`docs/roadmap-to-100.md`** (P27 farewell-sprint+honest-frontier → P28 engine → P29 families → P30 mass+main
→ P31 behemoths+walls → P32 verify+flip+Gen2-exit).

**Drew's four contract decisions (the values calls, 2026-07-15):** (1) **game-code TRUE 100%** — no completion
declaration while any game-code stub remains; walls re-attacked each phase boundary / model generation until
they fall (the §45/§52 model-relativity history). (2) **PsyQ LINKED = complete**; libs-from-source (sotn
precedent) recorded as a far-future side note only. (3) **Public flip AT 100%** — over the 2026-07-01 strategy
review's near-term recommendation ("community labor is how every peer crossed the hard middle"). The tension is
resolved by a **standing velocity checkpoint**: every phase close reports instr-%/session; if the trajectory
stretches beyond what solo+agents can credibly finish, the flip-timing question is re-surfaced with the numbers
— the decision stays falsifiable, not assumed. (4) **Fable5 window ~7/19**: the discovery sprint is P27's FIRST
task (recon-done seeds, 1–2 fresh top cores, the qty_n_refs lever, the pin-crash SIGABRT characterization).

**What the red-team caught (the why behind the roadmap's shape).** My own draft carried numbers past their
invalidation events — reconcile_tu "needs wiring" (already wired, PhaseEnd26), a "~300k free plumbing win"
(really ≈123k across 3 cores; func_8017A4AC already banked; func_8013F350 is a real class), "top-20 = 52%"
(34% post-audit), worklist "needs regen" (already regenerated) — exactly the R14-at-planning-scale failure the
Phase-26 close named. Fixes: every number in the roadmap traces to a committed post-audit artifact; §0 mandates
that every PhaseEnd re-baseline the roadmap via a standing **"Roadmap delta"** line; and P27 re-derives whatever
it consumes. The red-team also surfaced two real finds the plan now owns: **the `0x8017BEBC` family (952×~112,
~106k ins, exemplar MATCHED) was never covered by the exhaustion probes** — the IMM-scattered class gets a P27
gate-probe as possibly the largest cheap win left — and **the R34 second oracle covers only the overlays**, so
main/resident (exactly where the 100% flags plant) get the oracle extension before any 100% claim.

**Supersession.** `docs/family-endgame-megaplan.md` is superseded by `docs/roadmap-to-100.md` (banner added,
content preserved). Its h_seq reframe survives — it produced Phase 26 — but its scan-derived numbers and the
"crack ~986 exemplars → template ×120" thesis are byte-proven spent.

**Hindsight better-path.** A roadmap "grounded in the audit" nearly shipped with pre-audit numbers in it. The
transferable rule: when authoring any forward plan, red-team it against the committed artifacts *of the same
day*, and make the plan self-expiring (the Roadmap-delta line) rather than self-perpetuating.

## 2026-07-15 (Phase 27) — three strategic findings: the disc is bigger, a "wall" was our tool (again), and a "cheap win" is dead

**Context + belief.** Phase 27 opened to build the endgame on measured reality (the roadmap adopted the day before, red-teamed against same-day artifacts). Three beliefs going in, all now revised by the byte-gate:

**(1) The binary count is 136 — REVISED to 140 + a 39-module backlog.** The disc-completeness audit (T7) found 4 code-bearing SC07 overlays invisible for a month (code at PAC entry 1, not 0; `new_overlay.sh` hardcoded `0.4.dec`), onboarded byte-clean → 140. Then the type-sweep found **39 more un-onboarded type-1 code modules** (resident-class, in MAIN.CD), byte-confirmed code (jr $ra density ~3%, vs 0% for the data types that decode as valid-looking noise). They load at unknown addresses, so they are NOT mechanically onboardable — game-code TRUE 100% now spans 140 binaries PLUS ~39 modules pending runtime load-address RE. **Why it matters:** the completion contract's denominator was wrong, and the honest re-baselining LOWERED the headline (68.9→67.0% instr) because the SC07 overlays added mostly-unmatched code. The prior number was measured over an incomplete disc. Hindsight better-path: a disc-completeness sweep belongs at Gen2 *start*, not Phase 27 — the byte-gate is blind to un-onboarded code (R34), so "what did nobody onboard" must be asked explicitly and early.

**(2) The §42e "pin-crash wall" is intrinsic — REFUTED; it was `extract_unit` dropping macros.** For phases the project recorded that register-pin-heavy families "SIGABRT the sibling TU… ov077-TU-context-specific… fixed-size allocator tables… NOT ×134-recoverable." The wave-2 Fable5 characterization (`.run/giants/pin_crash_sigabrt.md`) located the abort exactly (`sched.c:2725 create_reg_dead_note`, a sched1 REG_DEAD-note conservation bug) and proved the trigger is `family_remap.extract_unit` dropping the body's file-scope `#define` macros (the T5 bug): the dropped gte_* macros became implicit-declaration CALLS, pushing caller-saved pins into the one fatal shape. Only 1 of 4 families genuinely crashed; the other 3 were exit-33 plumbing folded into one crash bucket by a shared gate-TU (R14, recursed). **Fixed (T5 `_carry_macros`), all four stage 133/133 clean.** Why it matters: **P31's pin-propagation route is OPEN** — a whole class of high-reach pinned cracks the roadmap wrote off as ×1 can now propagate ×133. This is the 26-A audit thesis a third time: the instrument, not the compiler, was the wall. Hindsight: every "intrinsic" verdict tied to a *tool's* behavior (a crash, a compile fail) deserves the R34 second look before it's recorded as a compiler limit.

**(3) The `0x8017BEBC` family is "possibly the largest cheap win left" (roadmap B2) — REFUTED, and the refutation is only trustworthy because the tool was fixed first.** Pre-T5, the probe would have read a fake 0% (112/112 CC1-FAIL on dropped macros) — a fourth phantom exhaustion proof. Post-fix: 106/112 stage, and the byte-gate says 0/8 (all genuine DIFF). The family is genuinely not byte-templatable; the h_seq structural match is necessary, not sufficient. **Why it matters:** it confirms Phase-26's mechanical-harvest-exhausted thesis extends to the families the roadmap hoped were cheap — and it is the cleanest demonstration of the phase's meta-lesson: **fix the measuring tool before you trust a measurement; a 0% from a broken tool and a 0% from a working one are the same number and opposite facts.**

**The through-line (the phase's transferable rule).** Every one of these was a case where an instrument — a scanner (`make report` swallowing gates, T2), a strip regex (six of them, T4), a boundary oracle blind to main/resident (T10), a staging step dropping macros (T5), an onboarding glob (T7) — silently mis-reported reality, and the fix changed the answer. The roadmap's own numbers were red-teamed; the *tools under them* were not, until this phase. R32/R33/R34 exist for exactly this, and Phase 27 is their first full application to the frontier the endgame plans against.

## 2026-07-15 (Phase 28 T0/T1) — the "families don't template" doctrine was a missing build step; B2 lives

**Context + belief.** P28 exists to measure the member-adapt close-rate — the roadmap's §6 "THE swing
number", with all P28/P29 yield projections deliberately withheld until it existed. Going in, the settled
belief (PhaseEnd_Phase26 + PhaseEnd_Phase27 + `calibration.md`'s "decisive P28/P29 input") was: **the
mechanical templating harvest is dead** — h_seq/h_norm structural families bank at **≈0%**, so P29's
arithmetic is "(cores cracked) × (reach)", not "(families) × 120", and B2 (`0x8017BEBC`, "possibly the
largest cheap win left") is byte-refuted.

**What failed.** All of it, and the failures compound:

1. **The ≈0% was measured with the wrong tool for the class.** `0x8017BEBC` is a **jr/switch** core. §47
   banked its exemplar as *"lazy isolation → carve (9-piece interleave) → splice → BYTE-IDENTICAL"* and
   called the fix *"×N template-safe."* The P27 T5 probe swept it with `family_sweep`, which stages C and
   gates and **has no carve step** — so gcc's jump table was never placed. The whole residual is **two
   words** (`classify_member` → **PURE, ndiff=2**, idx 343/345 = `lui/lw %hi/%lo(jtbl_801EC44C)`);
   `overlays.mk:112` carves the table for the exemplar, `:134` does not for the member. **Re-run through
   `jtbl_family_bank.py --raw` (which carves per sibling): 8 of 8 BANKED**, 4 same-address + 4
   cross-address, `make clean` + extract-all + `check-all` → **140/140**.
2. **n=1, on the least representative family in the population.** `has_mid_jr` is **3 of 163**
   matched-exemplar families (120 of 13,232 members). The rarest class was generalized to the whole frontier.
3. **Its corroborating evidence was pre-fix.** The three Phase-26 exhaustion probes (tiny-IMM 0/241,
   PURE 0/134, pinned 0/133) all predate `_carry_macros` (P27 T5, `commit:0637`). P27's decision-log calls its
   own re-probe *"a **fourth** phantom exhaustion proof"* — it named the mechanism that would have faked the
   first three and never re-ran them. **The ≈0% doctrine now has no surviving post-fix evidence.**
4. **A second instrument was lying underneath.** `family_remap.img_path` hardcoded `0.4.dec`, so the 4 SC07
   overlays P27 onboarded returned `None` → `stream_words` → `None` → `classify_member` → `("LEN", [])` —
   **silently** classified "not templatable" AND poisoning their family's `diff_class` to MIXED. Fixed by
   deriving from `config/splat.<bin>.yaml`'s `target_path` (R33 — what the BUILD reads) + raising (R32).
   Negative control: `ov_SC07_006` **None → `1.4.dec`**; all **233** shared substantial fns between
   ov_SC07_006 and ov_SC01_001 classify **PURE**, every one of which the old tool called LEN.

**The pivot.** The mechanical-templating thesis is **un-refuted, not vindicated** — and re-opened as the
phase's central question rather than its retired premise. P28 T3 now measures the rate over the population
that actually exists (from the fixed map): **1,418 matched-exemplar families / 21,889 unmatched members**,
PURE 17,024 (78%) · IMM 4,473 (20%) · **STRUCT 392 (1.8%)**. Note the roadmap sizes its swing number on
*register-drift* = **STRUCT = 1.8%** of the input; the mass is PURE+IMM.

**Why it matters (the number).** Regenerating the map exposed a **doubly-hidden** pool: **1,255 families /
6,268 members / 230,612 ins whose ONLY unmatched members are the 4 new SC07 overlays** (0 elsewhere), each
behind an already-matched, byte-proven exemplar — hidden once because P27 never regenerated the map after
onboarding them, and again because `img_path` would have called them all LEN. Total addressable behind a
matched exemplar: **937,248 ins = 21.7% of all remaining weight = 7.16pp of fleet instr**. `0x8017BEBC`
alone is 115 members × 952 ins ≈ **109,480 ins**. All of this is a **prediction** until T3's gate — h_seq
predicts, the whole-binary gate decides (G3/P9).

**The better path, in hindsight.** Three of the four failures above are one habit: **a probe inherits the
authority of the tool that ran it, and nobody re-runs a probe after fixing the tool under it.** P27 coined
R35 for exactly this and then, in the same phase, generalized a 0% from a carve-less sweeper on the rarest
family class in the population. The transferable rule is sharper than R35 as written:

> **Before a 0% retires a lever:** (a) did the probe run every build step the *exemplar's own bank*
> required? (b) is the probe family *representative* of the class being generalized to? (c) was the
> corroborating evidence taken through the same tool you just fixed? A negative result is a claim about a
> tool until each is answered.

Two further R14 corrections this session, both mine: the approved plan's own population figures (163
families / 13,232 members) came from the **stale** map; and "add `jtbl_` to `symbol_map`" was a **wrong fix
derived from a true diagnosis** — a compiler-generated switch table is never named in C, so there is no
token to substitute; the fix is placement, not substitution. Recorded in cookbook **§53**.

**Handed forward:** the remaining 107 members of `0x8017BEBC`; T3's stratified probe (SC07-only pool first —
its exemplars are already byte-proven, so a failure isolates the templating mechanism with no drafting
variable); and the roadmap's B1/B2/§2 numbers + the "(cores) × (reach)" arithmetic all need re-deriving at
the P28 close (Roadmap delta).

## 2026-07-16 (Phase 28 T3b) — the legacy h_seq swing number: ~3% as-tooled, but the failure mode is the tooling-vs-wall ambiguity that keeps resolving to tooling

**Context + belief.** T3-A measured the SC07 pool (h_exact + unwired, banked 95.6% via dedup_extend) but
that answered a *different* question than the roadmap's swing number, which is the LEGACY h_seq
templatability rate. Going in, the roadmap's belief (from Phase 26 + the pre-T1 calibration) was that
structural families bank at ≈0% — a belief this phase already refuted for B2 (jr+carve, 88.7%) by proving
the 0/8 was a missing build step.

**What T3b measured.** `family_sweep --hseq --chunk 1` over 6 legacy PURE non-jr families: **9 BANKED /
37 PLUMBING / 274 DIFF** = ~3% as-tooled. **Classified, unlike Phase 26's 0%.**

**The load-bearing nuance (R14/R35 on my own probe).** The 274 DIFF is NOT proof the families don't
template. The members are byte-level PURE (`classify_member` = reloc-only, 20/20 sampled), genuine h_seq
(all DIFF_BYTES vs the exemplar, so `family_sweep` is the correct tool, not `dedup_extend`), at the same
vram. A PURE family should reproduce once its relocs are remapped — so 274 non-reproducing members means
the **remapped exemplar body fails to recompile to the member's bytes**, which is one of: (a) an
incomplete `symbol_map` (the recurring jtbl/prefix bug — B2's 0/8 and T4's 12 DIFFs BOTH resolved to
tooling THIS phase), or (b) genuine TU-context regalloc divergence (a real wall).

**Why I did not resolve it.** Distinguishing (a) from (b) needs a region-by-region byte-diff of one PURE
DIFF member's staged output against the target — a Max-effort diagnostic, and I was at ~40% context after
a very long session. Rushing it is exactly how Phase 26 manufactured a wrong ≈0%. So the honest deliverable
is the CLASSIFIED measurement + the named next probe, not a verdict.

**The better path / handoff.** P29 opens by running the disambiguating probe BEFORE scaling its
"(cores)×(reach)" arithmetic on 3%: diff one PURE DIFF member's `family_sweep`-staged bytes vs the target
— mismatch AT a reloc position ⇒ (a) incomplete remap, fixable, and the legacy h_seq ceiling is far above
3%; mismatch in regalloc/schedule AWAY from relocs ⇒ (b) a TU-context wall and 3% is real. Given this
phase's scoreboard — every "structural wall" probed (B2, SC07, the pin-crash wall in P27) has resolved to
tooling — the prior should lean toward (a), but that is a prior, not a measurement. **The swing number is
~3% as-tooled, ceiling unknown; do not treat 3% as the ceiling until the probe runs.**

## 2026-07-16 (Phase 29 Task 1) — the swing number RESOLVED: the "~3%" was an -O0 compile-flag artifact, not a wall (the third structural wall to resolve to tooling)

**Context + belief.** P29 opened, as the Phase-28 handoff mandated, by running the disambiguating probe on
the legacy-PURE-non-jr "~3% as-tooled" swing number BEFORE scaling any "(cores)×(reach)" arithmetic on it.
The prior (from the phase scoreboard — B2, SC07, pin-crash all resolved to tooling) leaned (a) incomplete
remap; but that was a prior, not a measurement, and the honest state was "ceiling unknown."

**What the probe found (byte-proven).** Built `tools/diff_regions.py` (the deferred roadmap tool): it
remaps the exemplar EXACTLY as `family_sweep --hseq` stages it and compiles at the EXEMPLAR's real
optimization level. The two families supplying **~272 of the 274 DIFF** (`0x8013c964`, `0x8013c938`) are
**-O0 functions** (their exemplar is in `ov_SC01_077_o0.c`, the Phase-19 -O0 cluster), and `family_sweep
--hseq` stages the draft into the member's -O2 stub file — so it compiled an -O0 target at -O2, which can
NEVER match. Compiled at -O0 the remapped C masked-MATCHes (`func_8013C964`→MATCH(10),
`func_8013C938`→MATCH(11)). A 106-member sample across all size bands (nins 2..133): **O0-FLAG 45 ·
already-banked 29 · TEMPLATES 17 · type-lift-plumbing 15 · REGALLOC 0**. Zero codegen walls.

**Why the T3b measurement was neither wrong nor a lie — it was a measurement of a broken build step.** The
Phase-28 T3b probe honestly classified the 274 as "genuine gate-DIFF" and honestly refused to call 3% a
ceiling. What it could not see (at ~40% context, end of a long session) was that its own tool
(`family_sweep --hseq`) had no per-member opt-level awareness — the SAME shape as the §53 carve-law finding
(a family swept with the wrong build step reads exactly like an intrinsic wall). R35 again: a 0/near-0 from
a tool missing a build step, and a real wall, are the same number and opposite facts. The `has_mid_jr`
carve gap (§53) and this -O0 opt-level gap are two instances of one class: **`family_sweep` must reproduce
every build step the exemplar's own bank required — the carve AND the optimization level.**

**The pivot.** The swing is (a) tooling. P29's member track is NOT a low-ceiling per-member grind and does
NOT need `member_adapt.py` (the (b)-wall delta engine) for this pool. It is the mechanical **-O0 split
rollout** (the deferred "-O0 ×134", the whale `_o0b` precedent) + the type-lift sweep — Task 2a. The
~478k-ins legacy-PURE pool is back on the table.

**Honest caveat (not yet a bank).** The verdict is masked-MATCH — a candidate (§52b). The -O0-split
mechanism is independently byte-proven (the whale banks ×134; `ov_SC01_077_o0.c` banks byte-identical), so
confidence is high, but Task 2a whole-binary-gates it (and byte-gates EACH cluster member — `func_8013B7AC`
in this cluster was called "overlay-local" in Phase 20, so no blanket assumption).

**Better path, in hindsight.** The generalizable lever `family_sweep` is still missing: it should DERIVE
each member's required build steps (carve for `has_mid_jr`, -O0 for an -O0-cluster exemplar) from the
exemplar's own bank, and refuse to gate at the wrong build step rather than book a phantom DIFF. Task 2a
builds the -O0 arm of that; the carve arm (§53/`jtbl_family_bank`) already exists — they should converge
into one build-step-faithful sweep. That would have made both the Phase-26 "≈0%" and the Phase-28 "~3%"
impossible to manufacture.

### 2026-07-16 — P29 Task 2 Arm A: the swing verdict is now a BANKED FACT, but the fleet-scale -O0 carve hits a splat-integration wall (deferred, not a compiler wall)

**Context + belief.** Task 1 proved the swing pool is -O0-flag tooling (masked-MATCH at -O0), a *candidate*
(§52b). Arm A was to build the -O0-cluster split rollout (`tools/rollout_o0_cluster.py`, adapting the whale
`rollout_whale_o0.py`) and **whole-binary-gate one overlay to convert the candidate to a fact**, then roll
the ~478k-ins -O0 pool out fleet-wide.

**What was proven (byte-gated).** The tool carves the -O0 cluster (16 fns, vram 0x8013B568..0x8013C98C,
file 0x13410..0x14834) into a per-overlay `<ov>_o0.c` compiled -O0 (new Makefile `O0_CLUSTER_OBJS`
wildcard). On **`ov_SC07_010` the carve is byte-neutral and `family_sweep --hseq` banked 9/9 of the -O0
exemplar families' members whole-binary** (`func_8013B568/B7AC/B7F4/BC7C/BCDC/BD34/C360/C938/C964`), R22
clean-fleet 140/140. **So the swing verdict is confirmed as a FACT — these -O0 cluster members DO bank when
compiled at -O0, not just masked-MATCH.** (Phase 20's "`func_8013B7AC` is overlay-local" blanket claim is
also refuted at the member level — it banks in 010.)

**The wall (byte-proven, and it is TOOLING not the compiler).** Carving the SAME cluster in the other 3
sampled tail overlays (006/007/011) **byte-shifts the whole image** — a +0x20 data-symbol-address shift
(`lw v0,%lo(D_..3b6c)` → `..3b8c`), 34% of bytes differ — from a genuinely-clean `make clean &&
extract-all`. The boundary offsets are verified real fn-starts in every overlay's sig (identical 14-fn
layout), so this is **not** a wrong-boundary bug: it is a splat *re-disassembly* sensitivity — 3-way
splitting a code subseg makes splat resolve some `%lo` data references to a different auto-symbol. The
whale carve avoids it (single fn, a shared-header `_o0b` body, no INCLUDE_ASM in the split); the multi-stub
cluster carve triggers it on most overlays. This is the same "-O0 cluster split infra" that **Phase 20
built + reverted** — now characterized precisely (splat data-symbol resolution, not the compiler).

**The pivot (ROI-gated, honest).** The full -O0 fleet rollout (~1,233 members / ~0.6pp) is **deferred**: (1)
the splat-data-shift wall blocks 3/4 sampled overlays and debugging splat's `%lo` resolution is deep
splat-internals work; (2) the 134 whale-swept overlays have the cluster embedded INSIDE the
`jr_801380E0` carve (a carve-within-a-carve, even harder); (3) the remaining P29 levers are bigger and
cleaner — Task 6's tiny-IMM mega-pools (`0x80131eec` 2887×15 + `0x80130d0c` 2679×15 ≈ 5,566 members via
`imm_map`) and Task 3's core-cracks. The swing verdict's *strategic* claim (the ~478k-ins pool is real
matchable work, ceiling ≫ 3%) stands, banked-confirmed; only its *mechanical fleet harvest* is blocked on
the splat-carve integration, logged for a future session. The tool + the byte-neutral 010 carve are kept.

**Better path, in hindsight.** The whale's `_o0b` shape (a thin split whose body is a shared header
`#include`, no INCLUDE_ASM in the -O0 object) is splat-safe; the cluster rollout should likely mirror it —
route each overlay's -O0 members through a shared-per-member header rather than leaving INCLUDE_ASM stubs
in the split that splat re-disassembles. Testing that hypothesis is the cheap first move if/when the -O0
pool is revisited; it may dissolve the +0x20 shift the same way the whale never hit it.

### 2026-07-16 — P29 Task 6: the tiny-IMM mega-pools CRACKED (+4,801) — a def-signature conflict, after THREE byte-gate-corrected mis-diagnoses (R14/R35)

**Context.** The two tiny-IMM mega-pools (`0x80131eec` 2887 + `0x80130d0c` 2679 members, ~15-ins jump-table
dispatchers repeated per location) were the biggest unbanked pool (~5,116). `family_sweep --hseq` banked
**1/4966 (0.0%)** — a total block.

**Three wrong diagnoses, each refuted by the byte-gate/build (the R35 lesson, live, three times).** (1) I
first read `diff_regions`'s `O2:MATCH(0)` as "just a symbol-definition gap" and committed that finding
(`commit:0665`) — WRONG: masked_diff masks `%hi/%lo`, so a masked-MATCH cannot prove the reloc target resolves.
(2) I traced it to a "splat-local undefined symbol" — WRONG: the symbol (`D_801815EC`) is a defined `dlabel`
in the data tail. (3) The failure is a **compile** error, not a link/symbol issue: substituting one member
draft gave `conflicting types for func_8015FAAC` (cc1 exit 33), and the `family_sweep --reconcile`
(canon_sig_reconcile) path also banked **0/2470**. Only reading the *actual cc1 error* (not the masked
metric) got the truth.

**The byte-proven root cause + fix.** `src/shared/engine_core.h` forward-declares the member
(`extern void func_8015FAAC(s32 *a0);` — a shared engine fn CALLS it), while `family_remap` copies the
EXEMPLAR's signature (`void *a0`) onto the member's def → `conflicting types` → the member TU never
compiles. (The exemplar `func_80131EEC` has NO engine_core.h decl, so it banks cleanly — that asymmetry is
why the family templates in ov_SC01_077 but not its members.) Fix = **reconcile the member draft's DEF
signature to the shared-header canonical** (`s32 *a0` not `void *a0`) — byte-NEUTRAL (a pointer-type param
diff doesn't change codegen; `(s32)a0` is identical), and the whole-binary gate arbitrates anything else
(G3/P9). Implemented as `family_sweep --fix-def-sig` (`header_sig_map` + `reconcile_def_sig`, 1005 mapped
fns). Result: pool 1 **2331/2470 (94%)**, pool 2 **2470/2496 (99%)** = **4,801 members banked**, one member
hand-verified byte-identical first.

**The generalizable lesson (this is the FOURTH instance of one class).** `family_sweep` must reproduce every
build step the member's own bank requires — the §53 carve, the -O0 flag (Task 1), AND now the member's
CANONICAL DECLARATION when a shared header forward-declares it. The plain sweep's premise ("remapped drafts
are self-contained") is false whenever `engine_core.h` already declares the member with a caller-derived
signature. `--fix-def-sig` should likely be default-on for the h_seq path. And the meta-lesson, hammered
three times in one task: **a masked/intermediate MATCH is a candidate, never a diagnosis — reproduce the
real build and read the real error before naming the cause (R35).**

### 2026-07-18 — P29 jtbl 8-align wall: the half-pin was INVERTED (vacuous probes), the fix is a pad-spec filter (§8e)

**Context.** The 4 jtbl giants (`func_80131340`/`80159C84`/`8013C414`/`8013F350`, all match_one MATCH,
~2.6M agent-tokens of preserved drafts) were blocked on ONE tooling gap: banking `func_80131340` into the
shared `_jr_8012ACE0` TU produced a +4 pad at rodata 0xCC → image-wide %lo shift → SHA1 fail. The session-2
checkpoint recorded a half-pin — "cc1 AND maspsx both emit the jtbl `.align 2`; the +4 is a downstream
`as`/`ld_interleave` artifact" — and told the next session to start from there.

**What the evidence actually said (R35, again).** Both preserved probes were VACUOUS: an empty `j $31`
function with NO jump table — the `.align 2` they "showed" was the function-entry `.text` align. The honest
stage-walk (real draft spliced into the real TU, `.run/probe_jtbl/`) inverted every clause: cc1 emits
**`.align 3` before every table**; **maspsx passes it through verbatim** (the famous `maspsx.py:435` "drops
`.align`" is an inventory-only pass — the §8a-pad cookbook claim was false too); `as` bakes the pad
section-relative; and the LINK side was never guilty (`SUBALIGN(2)` + `ALIGN(.,4)` place even 4-mod-8 carve
starts tight — the banked `0xb07dc` carve proves it). Two Explore subagents produced OPPOSITE readings of
maspsx (one read the inventory pass as the output path); the tie was broken by reading the code path myself
plus one byte observable — the clean object's `.rodata` sh_addralign=8, which only a surviving `.align 3`
explains (R34: make oracles argue; R14: settle on bytes).

**The design fork and why the filter won.** The obvious fixes all fail a generality test: blanket align-demote
breaks the main EXE's island (its intra-TU pads are load-bearing); pure isolation fails multi-table functions
whose first table sits at vram ≡4 mod 8 (`.align` is section-relative, so the section-start parity flips every
internal pad); sed/as/ld have no per-occurrence mechanism. The winning shape: **replace each rodata `.align 3`
with the ORIGINAL's exact pad bytes** — derived per span by interval arithmetic from the carve config
(`pad[K] = start[K] − end[K−1]` ∈ {0,4}), emitted as a per-object `JTBL_PADS` make var, applied by a ~50-line
post-maspsx filter with fail-loud drift guards. Parity-independent, per-sibling self-adapting (each overlay's
own addresses), and structurally fleet-neutral (every pre-existing carve is single-table → no var → pipeline
byte-identical). A red-team subagent pre-verified the transform empirically (verbatim 0xE4/pad-at-0xCC vs
filtered 0xE0/tight) and surfaced 7 hardening items, including the LATENT bug that produced the original
failure (tight abutment silently merged into a bytes-impossible span) and a byte-witnessed wrong-TU splice
(`stub_file` first-match returned a stale duplicate stub — the "conflicting types" cascade was never the
draft's fault).

**Hindsight better-path.** The checkpoint's half-pin cost nothing this time because R35 forced re-derivation —
but only because the vacuous probes were LOOKED AT. The transferable rule: **a probe whose output contains no
instance of the probed thing pins nothing** — check that first, before trusting any recorded verdict. And when
a wall involves a multi-stage pipeline, walk it stage-by-stage with one byte observable per stage before
designing anything; the whole design fell out of five observables in under an hour.

---

## 2026-07-21 — Phase 29 Task-13A: the permuter's problem was TARGETING, not a missing transform

**Context + belief going in.** `docs/hindsight-study.md` §7 framed the offline endgame as *mine the
permuter's failures*: capture structured residuals, batch-diagnose them with an LLM, and route each plateau
to **missing-transform** (extend `permuter_weights` — "the highest-value bucket and the whole point"),
**seed-structural** (one LLM seed), or **genuine-wall** (file with an expiry). The implicit premise was that
the permuter is pointed at reachable work and is losing for want of the right mutation. Task 12 had plumbed
the telemetry; Task 13 was to build the classifier and the LLM autopsy on top.

**What the measurement said instead.** Before writing the LLM tier I materialised the corpus the classifier
was supposed to read — and it did not exist: 1 of 6,169 backlog records carried a `residual`, 0 carried
`passes_tried`, because Task-12's telemetry only fills records written after it landed. But 1,752 open
near-misses had their draft and their target .s on disk, so the residual was ~1 s of CPU away per function.
Recomputing all of them (21 s at -j12, through the existing `match_one` path) and classifying deterministically
gave the real distribution: **699 `redraft` · 578 `structural` · 306 `integration` · 75 `permuter` · 2 unknown.**

Of the 972 records the grinder's OWN filter admits, **75 (7.7%) are permuter-shaped.** The daemon has been
spending ~92% of its CPU on residuals a search-closer provably cannot close — 547 structural (a different
load width, an extra instruction, a flipped branch) and 348 drafts that are not the function at all. That is
the byte-grounded explanation of the Phase-22 audit's "7 banks all-time, all in Phase 21, and 0 since," and it
is a *targeting* defect, not a missing transform. Fixed for free: `grinder.candidates()` filters on the
measured bucket (1,303 → 78) and takes its directed profile from the measured class rather than the logged
label — 91% of records have no label, so the directed search had been silently running on gcc defaults.

**The pivot.** §7's ordering is now inverted for the rest of the phase: **do not run an LLM batch autopsy over
the backlog.** The deterministic classifier resolves 96% of it into three non-LLM routes, and the remaining 75
have not yet been permuted *under correct targeting* — so calling any of them a "plateau" today would be
diagnosing a search that never properly ran (the R35 failure mode: a probe from a mis-aimed instrument is not
evidence). Correct order: run the directed permuter over the 75 → collect genuine plateaus with real
`passes_tried` → only then spend the LLM, on what survives.

**Two findings that change other numbers.** (1) `closeness` conflates "one instruction off" with "this draft
is a different function"; 699 records rank as near-misses at closeness up to 278 purely from a length
artefact. They are un-attempted work misfiled as a backlog of hard functions — fresh crack fuel, and a reason
`docs/backlog.md`'s closeness ranking overstates how nearly-done the frontier is. (2) A 12-draft gate probe of
the `integration` bucket banked **1 of 12** (11 PLUMBING), so the 306 prices Task 14's reconcile ladder rather
than promising 306 free banks — stated as a measured conversion, not a projection, precisely because this
phase already over-projected once from a staged count (§57a).

**Hindsight better-path.** The corpus was one command away for months; the reason nobody ran it is that the
backlog's scalar `closeness` *looked* like a diagnosis. The transferable rule: **when a queue is ranked by a
scalar, check what the scalar is measuring on a sample before building anything that consumes the ranking** —
here, 40 % of the queue's "closeness" was a length artefact, and the tool built to consume it (the grinder)
had been quietly wasting 92 % of its work for two phases. Also: fixing the instrument surfaced a genuine
concurrency defect (`masked_diff`'s shared probe file) that had been silently dropping 0.8 % of drafts in
every parallel wave — a crashed self-check is indistinguishable from a failed draft, so it never got reported.

## 2026-07-22 (Phase 29, §61c) — the "clean-invalid jtbl bank" blocker does not exist: two reads of one polluted tree are not a replication

**Context + belief.** Phase 29's session-7 checkpoint named a single blocking finding and gated the entire
jtbl track behind it (cookbook §61c): the carve+isolation path produces a bank that is *incrementally valid
and clean-invalid*. `func_80135A4C` gated BYTE-IDENTICAL through `harvest_verify` every time, and
`make clean && extract-all && check-all` came back **139/140, `[FAIL] ov_SC06_018`, twice, identically.**
The stated implication was that the whole-binary byte-gate — the project's sole arbiter since Phase 12 —
cannot see this class of defect, *because the gate IS the incremental build* (§42b in its worst form). On
that reading, no jtbl core could be banked by anyone, and the 9 preserved cracks were frozen. It was written
up as the single next task with a precise diagnostic recipe: diff the incremental vs clean object set.

**What happened when the diagnosis ran.** It never reached the object diff, because the failure does not
reproduce. Re-applying the bank through the single-function automated path and then measuring:
per-binary clean rebuild BYTE-IDENTICAL; `make clean && extract-all && check-all` **140/140**; an
independent second full-fleet run **140/140**. The path is reproducible from committed config + source.
There is no extraction-order effect and no mid-flow asm.

**Why the original measurement said otherwise.** The failing R22 runs were taken on the tree left by the
*batch* `_jtbl_prep` — the run that ended `6 table-bearing → 1 carved, 4 isolate-FAILED, 1 stale-asm carve
fail`, i.e. a tree carrying the residue of five failed preps (stranded carves, half-applied isolations).
The per-function snapshot-restore that removes exactly that residue landed **after** those runs, in the very
commit that named the blocker (`commit:0803`). The measurement was real; the attribution was to the mechanism
rather than to the tree it ran on. The failing tree is gone, so that stays the best-supported explanation
rather than a byte-proof — but the load-bearing claim (the path is clean-invalid) is byte-refuted twice.

**The pivot.** §61c is retired; jtbl cores bank again, one draft per `harvest_verify` invocation (fault 2 —
isolation repartitions shared source, so a per-function undo is unsound in a batch — is real and stands).
`func_80135A4C` (181 ins) is banked and clean-fleet-verified; its family is 138 members / 24,978 ins ≈ 0.19pp
and the 9 remaining preserved cracks are unfrozen.

**Hindsight better-path.** "Twice, identically" felt like replication and was not: it was two reads of the
*same* contaminated state, which is one observation. A replication has to re-create the state, not re-run the
check — especially when the session that took the reading had, in the same hour, documented the tree as
polluted and then shipped the fix for the pollution. This is R35 turned on ourselves: we are disciplined
about not trusting a *tool* until it is verified, and much less disciplined about not trusting a *tree*.
The cheap guard is procedural and costs one command: **before writing a fault down as a property of a
mechanism, re-apply it from a known-clean tree.** Had that run before the checkpoint was written, the phase
would not have spent its single named next task on a blocker that was already fixed. That makes six
"structural walls" in this project that resolved to our own state or tooling (B2, SC07, pin-crash, the ~3%
-O0 artifact, the grinder targeting, and now this) — the base rate is now high enough that *the first
hypothesis for any new wall should be our own tree or instrument*, not the 1997 compiler.

## 2026-07-22 (Phase 29) — the shared byte-gate compared one binary against another binary's hash, for a month, because a default was truthy

**Context + belief.** `gate_stage` is the project's shared banking spine — the ladder every wave, the grinder,
and every manual harvest run through. Phase 29 had spent two sessions treating its verdicts as measurements:
"the ladder converts 0/10" was used to price Task 14 stages 2-3, and the Task-5 wave's "11/12 match_one MATCH,
the gate banked ZERO" was written up as three named integration walls (§61a).

**What the bytes said.** `main()` did `good_sha=a.good_sha or DEF_SHA`, where `DEF_SHA` is **ov_SC01_077's**
locked hash. Being truthy it beat `run_gate`'s per-binary `good_sha or _check_sha(binary)`, making that lookup
dead code on every CLI invocation. So the gate BUILT `ov_SC06_018` and compared it to `ov_SC01_077`'s SHA.
It cannot match. Every draft came back `"near"` — built, wrong bytes — which is *exactly* what a genuine
codegen residual looks like. **Nothing could ever bank outside ov_SC01_077 from the CLI, since 2026-06-21.**

**Why it survived a month.** The programmatic callers take a different path and were all correct:
grinder/idiom_hunt pass `None` (per-binary lookup); lora_grind/bulk_harvest pass an explicit per-binary sha;
orchestrator only ever gates 077, where DEF_SHA happens to be right. So the tool banked fine for daemons and
never for a human — and the two paths were never compared. This is R34 experienced from the inside: we had
two oracles all along (the CLI verdict and the direct `harvest_verify` verdict) and never made them argue.
The tell was visible and ignored: Task 13B's grinder banked `func_80181F78` in **ov_SC03_014** in the same
week my CLI ladder banked **0/10** on the same tree.

**Blast radius, measured not assumed.** 0 of 6,708 backlog records come from the affected path (worker 2724 /
bulk-harvest 2275 / lora-grind 766 / grinder 522 — all correct). The backlog needs no re-run. The void
verdicts are exactly the manually CLI-gated non-077 functions: the 12 preserved t5wave cracks. Re-run after
the fix, **7 of 12 now bank**, including two giants (478, 673 ins) and `func_801299C8`, which had been filed
as "PLUMBING: prototype declaration".

**The pivot.** Three "findings" are withdrawn: §61a's three integration walls, the 0/10 ladder pricing, and
the "9 compile / 0 bank ⇒ image-level effect" reading. Task 14 stages 2-3 remain unpriced — but now against
a gate that can actually bank.

**Hindsight better-path.** The defect is one truthy default, and the fix is one line — but the *detectable*
signal was a **disagreement between two paths to the same answer**, which existed for weeks. The transferable
rule: **when a tool has both a library entry point and a CLI, gate them against each other, because a
divergence there is invisible to every downstream check** — the byte-gate is a perfect correctness oracle and
a null oracle for "was the right question asked". Concretely: a gate must ASSERT that the SHA it is comparing
against belongs to the binary it just built (R32-style — assert the premise, not just the result). That
assertion would have failed loudly on the first non-077 CLI run in June. This is the fourth wall in one
session, and the fifth this phase, to resolve to our own tooling rather than gcc-2.7.2.

---

## 2026-07-22 (Phase 29, SESSION-11) — the fresh-exemplar sweep is FAMILY-SPECIFIC, not a blanket mechanical ×137

**Context + belief.** SESSION-10 closed on a strong claim: "sweeps only pay when they RIDE a fresh ×1 crack;
the discriminator is the exemplar's PROVENANCE — every success templated from a core freshly banked ×1 today,
every refusal from an ov_SC01_077 exemplar." The plan was to crack ov_SC06_018 exemplars fresh and sweep their
h_seq families (Task-5 measured ~1.59pp of fresh families for this one overlay).

**The experiment.** Two families SESSION-10 had swept 0/137 from an ov077 exemplar — `func_801365B8` (0/133)
and `func_80133AB0` (0/137) — were cracked FRESH in ov_SC06_018 (agent drafts, whole-binary byte-gated ×1),
then swept via `family_sweep --hseq --source ov_SC06_018 --allow-pins` from the fresh exemplar.

**The result (byte-gated, R22 140/140).** SPLIT: `func_801365B8` → **132/132 siblings banked** (thesis
confirmed — a fresh non-ov077 exemplar unlocked the whole family ov077 could not). `func_80133AB0` → **0/136,
reverted clean** (thesis refuted for this family — the members diverge in more than reloc symbols; no fresh
exemplar remaps into them).

**The refined finding.** A fresh ×1 crack is **necessary but not sufficient**. The fresh-exemplar sweep is
**family-specific** — the whole-binary byte-gate arbitrates each family, and on this 2-family thesis sample
the sweep rate was ~50%. The SESSION-10 provenance claim holds DIRECTIONALLY (func_801365B8 swept where ov077
refused) but overstated it as a mechanical ×137. **Consequence:** the ~1.5pp "fresh families" campaign
estimate must be discounted — cracking generates sweep fuel for SOME families, not all, and only the gate
says which. The honest yield model is (families that crack) × (per-family sweep probability), not
(families) × (reach).

**Why the difference (hypothesis, not yet exhaustively byte-proven).** func_801365B8's members differ only in
per-overlay reloc symbols over a uniform pinned regalloc → the fresh pinned exemplar templates cleanly.
func_80133AB0's members carry per-location immediate/codegen divergence the single exemplar does not share.

**Tooling caught in the act (R33 — fix the instrument).** The `family_sweep --source` override only searched
`members`, but a freshly-banked source member moves to `matched_members` after a sig-regen, so the override
silently missed it and would have templated from ov077 (a false refutation). Fixed to search both lists —
without it the thesis test would have "confirmed" SESSION-10's refusal for the wrong reason. Second fix:
`cdecl._depth0_spans` now consumes `\`-continuations, so a raw-draft `#define` macro no longer trips
audit-cdecl (the committed, cpp-expanded source was never affected — the gate was reading scratch).

**Hindsight better-path.** Test the sweep-from-fresh mechanism on ONE family before scoping a 95-target
campaign around it. The calibration cost ~1 wave and delivered a load-bearing correction to the yield model —
exactly the probe-before-scaling discipline (Phase-15/R35). Carry it forward: every fresh core crack this
phase must be followed by a gate-arbitrated sweep attempt, and the sweep's 0/N is data (per-member wall),
not a tooling artifact — provided the tools (`--source`, cdecl) are themselves verified first.

**Addendum (same session, 3rd data point).** `func_8017D648` — a MODAL/cross-address family (reach 82, a
structurally different case than the two per-location families) — cracked fresh in ov_SC06_018 and swept
**70/82 (85%)** (+3 gate-fail, +8 remap-refused "unresolved immediates"). So across three thesis families the
fresh-exemplar sweep rate is **100% · 0% · 85%** — 2 of 3 sweep, and the two that sweep do so at high rates.
The refined model: the fresh-exemplar sweep works for the MAJORITY of families at high per-family rates, with
a genuine per-member-wall minority (func_80133AB0). So the ~1.5pp campaign estimate should be discounted by
the wall-family fraction (~1/3 here) and the per-family remap-refusals, not treated as a flat 50% haircut —
and the only way to know a given family's rate is to crack it fresh and let the gate sweep it. Cracking
remains the generator; the sweep is high-yield but not universal.

---

## 2026-07-22 (Phase 29, SESSION-11) — the jtbl families are near-misses/walls, not plumbing wins; the post-carve reconcile makes the gate honest

**Context + belief.** SESSION-11's calibration wave drafted 4 jtbl families to match_one MATCH; the plan
(SESSION-11 checkpoint) billed the 3 reach-138 ones (`func_80135EB0`/`func_80135260`/`func_8012AAAC`) as
"≈+0.58pp, drafts done, just bank via the §8e carve." Banking them all failed with `conflicting types` —
looked like a jtbl tooling wall. Drew set /effort max to "fix the tooling once."

**Root cause (diagnosed, not assumed).** The jtbl carve's §8b carried-decl layer (jr_isolate_all's ambient
file-scope decls) conflicts with each draft's own externs. The reconcile chain that fixes this
(`cast_call_sites` + `reconcile_tu`, both `--src-file`-aware) already exists but runs PRE-carve against the
wrong TU — a jtbl fn's real TU is the split file, which doesn't exist until harvest_verify carves. gate_stage
had even deleted its batch jtbl stage noting "harvest_verify owns the splice." So the fix is one hook:
`harvest_verify._jtbl_reconcile` runs the same chain POST-carve against the carved TU (cookbook §62).

**The fix works — and that is exactly how it delivered a NEGATIVE result.** Validated on two functions
(`func_80135260` callee, `func_80191C50` data): both went `conflicting types` → a genuine codegen DIFF. The
plumbing was real and is now dissolved. But dissolving it revealed that all four jtbl drafts have a DEEPER
issue the plumbing hid: `func_80135260`/`func_80191C50` a real `%hi`-sharing regalloc residual (the agents'
reloc-masked match_one MATCH over-claimed it — R14); `func_8012AAAC` a def-side-arity conflict that is ALSO
fleet-shared (engine_core.h) and ALSO still DIFFs after the arity fix (a def-side register-threading wall);
`func_80135EB0` a carve `isolate FAILED`. **So the "+0.58pp from 3 reach-138 jtbl families" is REFUTED** —
they are genuine near-misses/walls needing per-function matching (re-draft/permuter), not cheap plumbing wins.

**Why this is a good outcome, not a wasted phase.** (1) The post-carve reconcile is the durable fix Drew
approved — it BANKS any jtbl family that is plumbing-only-blocked with a true MATCH, and it makes the jtbl
gate HONEST: it now attributes the blocker (plumbing vs codegen) instead of reporting every loose-typed jtbl
fn as an unbankable wall (the §26/§53-class error that manufactured two phases of wrong doctrine). (2) It
corrected an optimistic read: a reloc-masked match_one MATCH is NOT a whole-binary MATCH for a jtbl fn that
references shared symbols — the mask hides both the reloc-resolved codegen AND the carried-decl plumbing
(§58, extended).

**Hindsight better-path.** The calibration wave's jtbl drafts should have been whole-binary-gated (not just
match_one) before the checkpoint billed them as "drafts done, +0.58pp." A match_one MATCH on a jtbl fn is the
weakest MATCH signal we have (two masked layers). For the remaining ov_SC06_018 harvest: gate jtbl drafts
whole-binary early, and expect the reach-138 shared-region jtbl families to be walls (they are the most
loose-typed code in the engine). The cheaper yield is the ~83 non-jtbl targets (no carve, no §8b layer).

**Two §61-class traps re-confirmed** (both in cookbook §62): gate jtbl functions ONE AT A TIME (a mid-batch
isolate-FAIL corrupts the whole batch, `final SHA None`); and `fix_arity` on a fn in engine_core.h edits
fleet-shared state — a `git checkout src/<ov>/` restore misses `src/shared/`, and the per-overlay build stays
byte-identical so nothing flags the leak (caught here by a full `git status` + R22 clean-fleet).

## 2026-07-23 (Phase 29, SESSION-13) — the reach-138 wave on a P27-onboarded overlay is LOW-ROI; the true lever is LIVE-siblings, and the fresh families are per-member walls / def-side plumbing (R14/R35)

**Context + belief.** The SESSION-12 checkpoint's option (b): a fresh-exemplar crack-wave on a *higher-reach*
overlay (Task-5 greedy cover, ov_SC03_015/ov_SC07_006 "each ~+0.3–0.6pp of FRESH families"), billed as a
cleaner path than the drained ov_SC06_018 non-jtbl tail. Belief: ov_SC07_006's **122 draft-now reach-138 WAVE
families** (all cached, zero prefetch) are untouched fresh fuel — one crack + sweep banks ×138 (the SESSION-11
`func_801365B8 ×138` precedent).

**What happened.** `tools/build_wave_args.py` (new) emitted the top-24 reach-138 families **ranked by the fuel
manifest's `nins*reach` leverage**. Wave (`wave_binary.js`, 24 xHigh): 16 self-assessed MATCH, 8 killed by the
Anthropic session usage limit. Byte-gate: **2 via plain harvest_verify + 4 via `gate_stage` reconcile = 6 ×1
banked**; 17 failed as PLUMBING (`conflicting types for func_XXXX/D_XXXX`), 2 CC1-FAIL, 2 DIFF. Propagation:
`dedup_propagate --addr` banked **func_801325B8 → +3 onboarded-tail siblings**; func_8014A048/func_801678F0
**byte-diverge** in the SC07 cluster (kept ×1); func_8014FE60/func_80167540 **local-type-blocked** (§20 cap);
**func_80165CA0 consolidated its h_exact subgroup (+0 new)** and then **swept 0/135** via `family_sweep --hseq`
— a per-member wall like func_80133AB0 (0/136). **Net batch-1 yield ≈ 9 newly-matched functions**; ov_SC07_006
84.6% → 84.8%; fleet +0.1pp instr, ~0 distinct. R22 clean-fleet 140/140 twice (the engine_core.h arity edit
was fleet-safe); tools-health green.

**The finding (R14/R35 — verify the leverage assumption against the bytes BEFORE scaling).** The fuel
manifest's `nins*reach` leverage **badly over-counts**: a reach-138 family already matched in ~135 overlays
yields **+(live siblings)** on a fresh crack, not +138. Re-scoping the 122-fn pool by **actual live-sibling
count** (grep INCLUDE_ASM): **76 "fresh" (≥100 live) vs 44 onboarded-tail (<5 live)**. And the two classes have
OPPOSITE difficulty: the **onboarded-tail** families bank *easily* (they have a matched sibling in ~135
overlays to port verbatim — 5 of the 6 banks) but yield only +few; the **genuine fresh** families are the HARD
tail — batch-1's fresh-138 attempts FAILED as **def-side plumbing** (`conflicting types for func_XXXX`, needs
§54 `--fix-def-sig`, which `gate_stage`'s caller-arity pre-pass does NOT clear), **genuine DIFF** (permuter
fuel), or **per-member walls** (func_80165CA0). A fresh crack does **not** reliably unlock its family.

**Why this is a good outcome, not a wasted batch.** (1) The corrected lever is durable: `build_wave_args.py`
now ranks by `--rank live` and reports the fresh/tail split, so future scoping targets the true fuel and never
again mistakes an onboarded-tail family's inflated `nins*reach` for leverage. (2) It confirms — from a fresh
overlay ov077/ov_SC06_018 never sourced from — that the reach-138 *family well is largely SPENT via wave+gate*
(the Phase-26 "h_seq templatable-families thesis is byte-proven SPENT" finding, now re-confirmed on the SC07
cluster). The remaining reach-138 residual is per-function (permuter + §54), not breadth.

**Hindsight better-path.** (a) Rank by live-count AND *require a matched-sibling-to-adapt* — that combination
is what banks (the tail wins had siblings; the sibling-less fresh families didn't). (b) The onboarded SC07
overlays (006/007/010/011) are a **distinct less-shared ~84% cluster** (1549 vs 1702 distinct-code base), not
merely un-integrated — so a "sweep every matched family into them" pass will hit the same per-member
divergence batch-1 saw (func_8014A048/func_801678F0 diverge; two more local-type-blocked). (c) The genuinely
higher-ROI next move is NOT more ov_SC07_006 wave batches — it is either the per-function grind (permuter on
the DIFFs, §54 `--fix-def-sig` on the def-side-plumbing failures) or a different lever entirely (Task 7's
ROI-gated close arithmetic now has a third low-yield data point: ov_SC06_018 non-jtbl tail ≈0.1pp, this ≈9
functions). **Do NOT close P29 on ROI — the burn-down floor is still undetermined (needs 3 session-close
deltas).**

**UPDATE (same session, R35 — the probe REVERSED this verdict).** Rather than defer the header-decl reconcile
as future work, I ran the bounded probe on `func_8014CD80` (138 live, 0 matched, NO DEFINE macro; a clean MATCH
draft with a **universal body** — only universal callees + param offsets, zero overlay-local `D_*` refs). The
def-side blocker was engine_core.h `DEFINE_func_8014CD0C()` forward-declaring it `void func_8014CD80(s32,void*,
void*)` while the byte-true def is `int func_8014CD80(s32,u16*,u16*)`. **One byte-neutral header edit**
(`void`→`int`, `void*`→`u16*`; the call site passes `u16[3]` arrays and ignores the return, so codegen is
unchanged) → `harvest_verify` banked ×1 BYTE-IDENTICAL → **`dedup_propagate --addr` propagated 138/138 overlays
byte-identical (live 138→0)** → R22 clean-fleet **140/140**. **So the fresh-138 families ARE recoverable ×138 —
the blocker was purely the def-side header decl, NOT a wall.** (func_80165CA0's 0/135 was a non-universal
*body*, a different failure mode; h_exact=1 does not distinguish them — the BODY's universality does.)
**Quantified market:** of the 75 fresh (≥100-live) families, **46 carry an engine_core.h caller forward-decl,
38 SIMPLIFIED (`void`/`void*`) = the func_8014CD80 pattern** — each a candidate ×138 (≈+1.5–2.8pp instr if
half-to-most bank, gated by whether each draft's body is universal + byte-correct). **DECISION: build a
`fix_header_decl` tool** — parse the byte-true def sig (from the banked def or a MATCH draft), rewrite every
engine_core.h forward-decl of that fn to match, then hand off to the existing bank→dedup_propagate→R22 chain.
It edits fleet-shared engine_core.h → INHERITS the §61 snapshot-undo constraint (undo = restore, never an
inverse; validate FLEET-WIDE via R22). Pair it with a fresh-family wave (`--rank live --min-live 100`): the tool
is the INTEGRATION half, the wave supplies the byte-true draft. **This reopens option (b) as the campaign's best
lever — the "low-ROI, spent" read above was measured on the WRONG 24 (leverage-ranked → onboarded-tail) and is
superseded for the FRESH pool. The onboarded-tail read stands.**

## 2026-07-23 (Phase 29, SESSION-13) — the full remaining-work re-derivation + two roadmap-bucket corrections (R31, roadmap delta)

**Context.** While a crack wave ran, re-derived the ENTIRE remaining-work map from `family_hseq.json` +
`asm/nonmatchings/` (main) to answer "largest families, largest unique fns, what's MCP-automatable." This is
the re-derivation the roadmap §0 mandates (numbers rot; consume §2 only through one). It does NOT supersede the
roadmap's PHASE SEQUENCE (families P29 → main+tail P30 → behemoths P31 → flip P32 — CONFIRMED), but it
re-baselines the numbers and corrects two buckets.

**The re-derived baseline (2026-07-23).** Fleet 78.8% instr · 67.6% distinct · 88.26% fn-count. Remaining:
**overlays 40,395 stubs / 2,738,677 ins / 6,472 families** (159 reach-138 · 2,510 reach-2..133 · 3,803
singletons) **+ main EXE 2,002 fns / ~84k ins (~1,048 game-code, 0.7% done).** **CONCENTRATION: top-20
families = 23% of remaining instr, top-100 = 53%** — half the entire remaining project is 100 shared cores,
each ×N. Largest cores: `0x80176734` 371×138=51k · `0x80176218` 327×138 · `0x8013c414` 329×137 (jr) ·
`0x8014d820` 304×138 · `0x80135eb0` 289×138 (jr); ~half the top-20 are jr (jtbl-carve path).

**CORRECTION 1 — B1 pessimism partially REVERSED (cross-ref the SESSION-13 fix_header_decl entry).** B1 =
"substantial h_seq families, mechanical templating byte-proven dead, per-member cracking only." FALSE for the
def-side-blocked slice: `fix_header_decl` recovers them ×138 (func_8014CD80 proved; ~38+ candidates). The
templating-dead verdict holds for the h_seq-adapt path; it does NOT hold once the shared-header decl is fixed.

**CORRECTION 2 — B7 behemoth list is STALE/INCOMPLETE.** B7 lists 5 behemoths topping at `0x8017bf14` (4,763).
It MISSES **`0x80183814` (5,122 ins, ov_SC07_006) — now the largest single function in the game** — and
`0x8017dc1c` (1,518, ov_SC07_006). Cause: the 4 SC07 overlays were P27-onboarded AFTER the roadmap's
2026-07-15 baseline, so their singletons never entered B7's count. **P31 must rebuild B7 from
`family_hseq.json` singletons, not the roadmap's list.** (R14 caveat: verify `0x80183814` is one function, not
a mis-split, before scoping it.)

**MCP-automation finding — the prefetch gap is in the TAIL, not the top.** reach-138 families are **146/159
already cached** (draft-now, no MCP); the 6,027 tail families + main (0/2,002) are uncached. So the roadmap's
P28 "fleet Ghidra-C prefetch" is a **P30 fuel-generator for the tail+main**, NOT a P29 blocker — the top-100
(half the project) is already fuel-ready. The only MCP-dependent link left in the pipeline
(prefetch → wave → fix_header_decl → dedup_propagate) is that tail prefetch.

**Path forward (abiding by the roadmap, refined by concentration).** Stay in P29; order by ×138 byte-weight
top-down; **STOP capping the wave at 150 ins — the GIANT fresh families (150–371 ins) are the biggest single
wins and were being skipped.** Non-jr via wave→fix_header_decl→dedup_propagate; jr-half via the carve path.
Defer main+tail to P30 (the MCP prefetch pays off there); behemoths (incl. 0x80183814) to P31.

## 2026-07-23 (Phase 29, SESSION-13) — CORRECTION: fix_header_decl is fragile for SHARED multi-caller decls; gate_stage's call-site-cast is the right tool (R14/R31)

**The over-claim.** The earlier SESSION-13 entry billed ~38 fresh-138 families as a `fix_header_decl` ×138
market. On the actual crack wave (24 fresh families, 20 MATCH drafts), bulk-applying `fix_header_decl`
(v1 self-def AND v2 --reconcile-externs) **BROKE the build** (`SHA None`, CC1-FAIL across the batch).

**Root cause (byte-proven).** `fix_header_decl` rewrites a decl in `src/shared/engine_core.h`. But that decl
is SHARED by MANY caller macros, each using the fn differently. Changing the return (e.g. `s32`→`void`) breaks
a caller that USES the return (`void value not ignored`); changing a callee's params to match one draft's
loose extern is an ABI change the tool correctly REFUSES — but a bulk pass still corrupts the header.
`func_8014CD80` (the ×138 proof) worked only because it was a LUCKY single-caller / ignored-return case. The
header-rewrite lever is therefore NARROW: it is byte-neutral only when the decl change is compatible with
EVERY caller — a minority of the 38, not all. **Also:** most of these fresh families' def-side conflict is a
PER-OVERLAY-LOCAL forward-decl in the split `.c` (emitted by a matched sibling), which `fix_header_decl`
(src/shared only) never touches.

**The right tool — `gate_stage`'s reconcile ladder.** It casts the CALL SITES in the draft's OWN TU
(`cast_call_sites`) instead of rewriting the shared decl, so it never breaks other callers. On the same wave
it banked **5** (func_80175308/8012E138/80130C08/8012A1BC/80137178) where `fix_header_decl` broke the build;
plain harvest_verify banked 2 self-contained (func_8012B4B8 §52b-wall + func_80169228). **7 of 20 MATCH banked
cleanly; R22 140/140.** The other ~13 are near / deeper-plumbing, staged for a member-adapt/gate_stage pass.

**Doctrine (supersedes the "build fix_header_decl v3" next-step).** Keep `fix_header_decl` for the narrow
single-caller/ignored-return self-def case (it's cheap + proven there). For the fresh-138 integration in
general, the SPINE is `gate_stage` (call-site casts + arity pre-pass, byte-gated), NOT header-decl rewriting.
"Matching is solved; integration is the bottleneck" holds hard here — the 20 bodies matched; the plumbing is
the wall, and the call-site-cast ladder is the way through it, per-family, not a bulk header edit.

## 2026-07-23 (Phase 29, SESSION-13) — the §20 type-lift is a FLEET-WIDE collision-resolution op, not a tool-run (R32/R35; do NOT improvise it)

**Goal.** Unblock the 4 §20-capped fresh-138 cores (func_8012B4B8/80175308/8012E138/8012A1BC — "not
self-contained (local types)") via `build_engine_types` so they propagate ×138 (+552 stubs; roadmap B4).

**Diagnosis (correctly measured, after fixing a broken instrument twice — R35).** The cores reference
fleet-local struct types (`Vec8`, `Mat32`, `Buf`, `MATRIX`) that live at overlay file scope, NOT in
`src/shared/engine_types.h`. `dedup_propagate` conservatively skips any body referencing a non-shared type.
`build_engine_types` lifts such types to the shared header (byte-neutral: `--strip` removes the defs, type
decls emit no code) — the proven §19 Phase-20 lever.

**The blocker — MULTI-DEF COLLISION across the fleet.** Robust scan (`}[ ]*<T>[ ]*;`, NOT the `[^;]*` regex
that silently under-counts multi-field structs — that bug read "Mat32 = 1 copy/SAFE" when it is 138+1, and I
nearly trusted it: R35, twice): **`Mat32`/`Vec8`/`Buf` each have 2 distinct defs across 138 overlays, `MATRIX`
has 3.** The extra defs are drafter-invented simplified variants (`Mat32 = {int w[8]}` from THIS session's
wave vs the canonical `{s32 w0,w4,w8,wC; s16 h10,hpad; s32 t0,t1,t2}`). So a naive `build_engine_types
--source ov_SC07_006 --strip` would push a NON-CANONICAL def into the fleet-shared header and break the 138
overlays holding the canonical local copy. The safe scoped lift (ov07-UNIQUE types only, e.g. the named
`Cam8012E138`) unblocks ~1 core — not worth an R22.

**Why this is not a tail-of-session improvisation (the responsible call).** It is a genuine fleet-wide op: (1)
pick the canonical def PER type (resolve the 2–3-way collisions); (2) reconcile every non-canonical draft
(this session's simplified Mat32/Vec8/Buf + historical variants) to the canonical — byte-checking each (a
32-byte struct COPY is byte-neutral across layouts, but any FIELD access is not); (3) lift canonical →
engine_types.h; (4) `--strip` FLEET-WIDE (138 overlays, no make target exists — Phase-20 did it manually); (5)
R22. Rushing a fleet-shared header edit with colliding type defs is exactly the SESSION-12 corruption class.

**Bounded payoff (cookbook §20).** The lift only helps type-blocked-BUT-otherwise-clean bodies. The DOMINANT
§20 fraction is the DEF-conflict loose-typing wall — byte-proven unrecoverable by text transform, only path is
RE-DRAFTING under the caller-canonical sig. So the type-lift is real but not a fleet-% silver bullet.

**RECOMMENDATION.** Do the type-lift as a DEDICATED operation with: a correct multi-field type-scanner (the
`[^;]*` one is retired), a per-type canonical-def picker + a draft-reconcile pass, fleet-wide strip
orchestration (build the missing `make lift-types` that loops all overlays + `--exclude` the irreconcilable),
and R22. It is high-value (roadmap B4) but must be planned, not improvised. The 4 cores stay ×1 until then.

## 2026-07-23 (Phase 29, SESSION-13) — UPDATE: the §20 type-lift IS safely executable when SCOPED to clean types (lift_types.py works)

Refines the "do NOT improvise it" entry above. The fleet type-lift is NOT all-or-nothing: `tools/lift_types.py`
(built this session — reuses build_engine_types' brace-aware parser, picks each type's CANONICAL/majority def
fleet-wide, strips all local copies, R22 arbitrates) lets you lift the CLEAN subset safely while deferring the
variant-heavy types. Applied to Mat32 (138 canonical + 1 copy-only variant) + Cam8012E138 (unique): R22
**140/140**, unblocked **func_8012B4B8 + func_8012E138** for ×138 propagation. **The doctrine:** classify each
type first (`lift_types --types … ` dry-run reports distinct-def counts + variant overlays); lift the 1-def and
copy-only-variant types NOW (byte-neutral, R22-verified); DEFER the genuinely fleet-split types (MATRIX 3-def,
Vec8 180/139, Buf 3-def, M8 2-def) to a per-camp reconcile pass — they need field-access reconciliation, not a
blind strip. So: not a monolith, an incremental clean-first lift. The variant reconcile is the remaining hard
part of roadmap B4.

## 2026-07-23 (Phase 29, SESSION-13) — the BROAD 100+-type lift needs collision-vetting + precise strip; the CLEAN 2-type lift stands

Attempted #2 (broaden the clean §20 lift): discovered 102 single-def fleet-local types + added a topological
sort to `lift_types.py` (dependency ordering — a type with a value member of another lifted type must follow
it). Two edge cases blocked the broad lift, both caught by R22 (as designed — nothing committed):
1. **Name collisions.** `actor4c` (struct) vs `Actor4C` (typedef) are the SAME logical type declared under
   case-variant names across overlays — lifting both → `redefinition`/`redeclared as different kind`. A
   case-insensitive name-collision exclude dropped it (100/102), taking R22 138-fail → 1-fail.
2. **-O0 strip precision.** The last straggler (ov_SC01_077's `_o0.c`) hit a link `multiple definition of
   D_801DAA08` — stripping a type def indirectly perturbed a nearby declaration in the -O0 file format (the
   diff showed nothing removed AT D_801DAA08, so it is an indirect/format edge case in the strip span logic).

**Verdict:** the broad lift is 139/140-close but needs (a) full name-collision vetting (case-variant + struct-
tag/typedef aliasing), and (b) a strip that is exact against the -O0 file format. Both are real tool work, not
a tail-of-session push. **The CLEAN 2-type lift (Mat32+Cam8012E138, +276) stands committed** and proved the
lever; the broad lift is a follow-up with the harder strip/vet. `lift_types.py`'s topo-sort is kept (correct +
needed for any future multi-type lift). Doctrine unchanged: classify-first, lift the truly-conflict-free
types, and let R22 arbitrate — it did.

## 2026-07-23 (Phase 29, SESSION-14) — the broad §20 lift LANDS (154 types, R22 140/140); all three carried "blockers" were misdiagnosed

**Context + belief.** SESSION-13 closed the broad lift at "139/140-close, needs (a) full name-collision
vetting (case-variant + struct-tag/typedef aliasing) and (b) a strip that is exact against the -O0 file
format — both real tool work." I opened by treating that as the spec.

**What actually failed.** Fixing the instrument before trusting its readings (R35) changed all three answers:
1. **(a) is not a naming problem.** `actor4c`/`Actor4C` is a single TAGGED TYPEDEF counted twice with
   OVERLAPPING spans — 13 such pairs / 6,142 occurrences fleet-wide, 0 with a standalone tag. The
   case-insensitive exclude that appeared to fix it was a heuristic over a structural fact, and would have
   wrongly dropped the legitimate `Obj`/`obj` and `Vec`/`vec` pairs. `build_engine_types` had solved this
   correctly since Phase 26-A; `lift_types` simply carried its own copy of the model (the R33 failure mode).
2. **(b) is not strip precision.** `ov_SC01_077_o0.c` is the 1 TU of 3,226 that deliberately omits
   `engine_core.h`. Stripping its types deleted them; `multiple definition of D_801DAA08` was three steps
   downstream (undeclared type → parse error → implicit int → tentative definition → link collision). The
   link error named a data symbol that no diff ever touched, which is why the strip-span theory survived.
3. **A third blocker, introduced by me this session.** `--candidates` classifies per ENTITY but emits per
   NAME; passing `Prim` dragged in the deferred VARIANT `typedef Prim`, repointing 103 overlays at the
   header's different layout. Compiled clean; per-binary pre-filter green; **R22 37/140**, and the 103
   failures were exactly the 103 Prim-stripped overlays (set equality).

**The pivot.** Three guards, each at the point of mutation rather than in the selector: one shared
containment model (R33), a pairwise-disjointness assertion (R32), a header-visibility check, and the strip
invariant *"remove a local def only if what becomes visible is textually identical to it."* A selector bug
can no longer reach the source. Byte-grounded: R22 **140/140**, `engine_types.h` +510 lines, 2,958 files.

**Hindsight — the better path.** Two of my own measurements lied before the tools did: an `__attribute__`
regex artifact invented a "defs that also declare an object" class (zero real instances — I nearly built a
`cdecl` vetter for it), and a `while read` loop counted the literal string `check-all:` as an overlay. R14
applies to the three-line script I just wrote, not only to sub-agents. And the pre-filter lesson generalises
§61 one level down: **a pre-filter is evidence only about what it filtered** — `ov_SC01_077` passed the
Prim-broken run too. Pre-filter on a binary that FAILED.

**Deferred, named, not dropped:** 8 VARIANT entities (MATRIX 3-def, Buf 3-def, Vec8, Prim, Handler, Blk8,
V8, Prim_8016E7C8) for the per-camp field-access reconcile — still the remaining hard part of roadmap B4;
14 carried tags; 5 types kept local in the -O0 TU.

## 2026-07-23 (Phase 29, SESSION-14) — "should a fresh decomp do types FIRST?" — no for matching; yes for one cheap naming convention

**Context.** Drew asked whether doing the type work up front would help a lot — e.g. for Vagrant Story or a
fresh game decomp. Worth recording because the intuitive answer ("of course, types make code readable and
matchable") is **byte-refuted by this project three separate times**.

**(a) Types are byte-NEUTRAL for matching.** Phases 16, 17 and 18 each re-confirmed it: gcc's output is
determined by access WIDTH and OFFSET, which we read directly off the MIPS opcode; a struct definition is a
spelling convenience for `*(s16*)(p+0x24)`. Phase 16 spent an entire phase on "recover the actor struct →
matching gets easier" and the byte-gate refused it. SESSION-14 closes the loop from the other direction:
lifting 154 types fleet-wide banked **zero** new matched functions.

**(b) What types gate is SHARING, and that is architecture-specific.** BFM's economics are "match once →
stamp ×138 overlays"; a matched body naming a file-local type cannot enter the shared header, so it cannot
be stamped (§20 cap). That lever exists because 138 overlays run the same engine. A decomp without that
duplication gets far less from types-first. **For VS specifically: unmeasured.** Same compiler and CC0, so
the gcc idioms transfer; whether its structure supports propagation is an open question, not a claim.

**(c) The cheap exception is a NAMING convention, not type recovery.** Seed documented SDK types on day one
(we found THREE contradictory `MATRIX` layouts, and the 578-file majority — `{s32 m[3][3]; s32 t[3]}`, 48B —
is almost certainly WRONG versus the documented PsyQ `{short m[3][3]; long t[3]}`, 32B, which sits in only 71
files; it spread precisely because it never mattered for bytes). Then forbid bare generic type names at
DRAFT time: measured, **7 of the 8 collided names are bare** (MATRIX, Buf, Vec8, Handler, Blk8, V8, Prim),
and the one address-suffixed collision (`Prim_8016E7C8`) differs only in a member's type spelling.

**The transferable lesson** (→ the public "how to AI-decomp" wiki): the type camps were **self-inflicted by
parallel agents** each inventing a local name and layout for the same memory. Enforcing an address-suffixed
naming convention at draft time costs nothing; cleaning it up afterwards cost a session. **Types-first would
not have made one function match sooner; a naming convention would have saved most of SESSION-14.**

## 2026-07-23 (Phase 29, SESSION-14 close) — the §20 propagation cap was gating DE-DUPLICATION, not coverage

**Belief going in** (carried from Phase 19/20 and restated in the SESSION-13 checkpoint): the §20
local-type cap is "the single biggest propagation unlock" — free the capped cores and the fleet %
follows. This session tested it end to end and the bytes say otherwise.

**Measured.** The broad type-lift freed 17 propagatable cores (13 banked ×138) = **−831 stubs**. Then the
uniquify campaign (Buf → MATRIX → Vec8; 3 camps, 223 files renamed, ~1,559 local copies stripped, 5
propagations, 4 full R22 cycles) freed 6 more cores and moved the fleet by: **+6 functions, +558
instructions, −6 stubs, 0.00pp on all three headline metrics.**

**Why.** A core capped by a local type was still MATCHED in every overlay that has it — each overlay's copy
had been banked individually. Propagation replaces those N individual definitions with one shared
`DEFINE_func_*()` macro. That is a source-DRY win (and it shrinks the registry/gate surface), but it banks
no new bytes, because nothing was unmatched. **"Unblocked" and "unmatched" were being conflated.**

**Consequence for the roadmap.** Roadmap B4 ("close the propagation cap") should be re-labelled as a
maintainability item, not a coverage lever. The remaining camps (Handler, Blk8, V8, Prim, Prim_8016E7C8)
are small AND now known low-yield — do them opportunistically, never as the session's main bet. **The only
lever that moved distinct-code today was nothing: it sat at exactly 3,811,442/5,634,875 = 67.6% at open and
at close.** Fresh cracks are the sole mover of the distinct-RE number, and that is where the next session
should point.

**What the campaign IS worth keeping for:** the uniquify recipe + `tools/uniquify_type.py` (the correct
operation for same-name-different-type camps, §64a), the blocked-queue drop 13 → 7, and the R32 fix that
makes `dedup_propagate` name what it skips. Cheap to re-apply later; just not a yield play.

## 2026-07-24 (Phase 29, SESSION-15) — crack-wave efficiency audit: the bottleneck is INTEGRATION, not idioms

**Question (Drew):** waves cost millions of tokens each — how many succeed, and are we missing a new idiom?

**Measured (2 LLM waves, byte-verified):**
- s14: 24 drafted / 20 match_one MATCH / **6 whole-binary banked** / 2.52M tok.
- s15: 24 drafted / 22 match_one MATCH / **6 whole-binary banked** / 2.77M tok.
- Draft success ~**92%**; bank success ~**27%**.

**Are we missing an idiom? NO — verified against the bytes.** Re-ran match_one on 6 s15 NON-banks:
all 6 are MATCH (byte-correct bodies). The drafters find the right idioms (92% byte-correct C). The
functions that don't bank are **byte-correct-but-unintegrated** — the whole-binary build rejects a
declaration/type conflict (def-side sig, data-extern type, unshared struct), NOT a wrong instruction.
The only recurring genuine codegen residual is the phantom-frame schedule class (~2/wave) — minor.

**The waste:** each wave produces ~22 byte-correct functions and banks 6, **stranding ~16 paid-for
correct functions**. 461K tok/bank now; if integration recovered all 22, ~126K tok/bank — a **3.7×
efficiency gain for ZERO additional drafting tokens.** We already bought the correct code; we throw
away 73% of it at the gate.

**Conclusion / next investment:** the bottleneck is INTEGRATION AUTOMATION, not drafting and not idioms.
Pointing more tokens at drafting strands more correct functions. Build a **fleet-safe integration-recovery
pass** (def-side sig reconcile + data-extern reconcile + auto struct-def lift, R22-validated) that runs
after the gate — NOT fix_header_decl (fleet-blind, §63). It ~3.7×'s the yield of every wave, past and
future. Stop waves; invest in integration tooling first, then resume at ~3× efficiency. (Drew stopped the
waves on this instinct — the data confirms it.)

## 2026-07-24 (Phase 29, SESSION-16) — the integration-recovery pass: measured, and the §20 DEF-conflict wall refuted per-overlay

**Belief going in (SESSION-15 audit).** Waves bank ~27% of drafts; the ~73% stranded are "byte-correct
bodies stranded by plumbing", so a fleet-safe integration-recovery pass would **~3.7×** every wave's
yield for zero new drafting tokens. Drew stopped the waves on that finding and this session was
chartered to build the pass.

**What measuring first changed (before any recovery tooling existed).**
1. **The premise was ~2/3 true, not true.** Among the 36 STRANDED drafts, `match_one` says **24 MATCH,
   11 near, 1 ERR**. The "~92% byte-correct" was a whole-wave figure; the residue is **67%**. The 11
   `near` are unfinished drafts — and they are precisely the ones that compile in their real TU and
   DIFF. So the recoverable fuel was ~24, not ~36, and the 3.7× was over-stated at the source.
2. **The blocker was not the class the existing ladder targets.** Running `cast_call_sites` +
   `reconcile_tu` over all 36 clears `callee_decl` 19→3 and `data_decl` 16→**0**, and converts **1 of
   36** to compiling — which then DIFFs. §61d verbatim. The dominant blocker is the **shared-header
   self-decl (21 of 36)**, which no draft-side transform can reach.

**The move that worked, and why it was available.** `fix_header_decl` is off-limits (fleet-blind: 3/3
per-binary then R22 139/140). §20 had concluded the DEF-conflict class is "byte-proven unrecoverable by
text transform" because the shared macro's `extern` is the only declaration in the 137 stub overlays and
"can't be edited per-overlay — it's in the shared header". **The missed move: you do not have to edit
the header to change what ONE overlay sees — you expand the macro there.** The conflicting `extern`
lives INSIDE the `DEFINE_func_*` body, so it exists only at instantiation sites; replacing those in the
overlay's own TU with the expansion, correcting only the conflicting decl to the draft's byte-true sig,
is a **T1 (binary-local)** edit that cannot reach another binary. `tools/demacroize.py`.

**Measured result.** 13/14 clean candidates MATCH in their real TU; **14 banked whole-binary
BYTE-IDENTICAL**, R22 clean-fleet **140/140** (three times). Distinct-code **64,860 → 64,874 unique
fns**. The one rtu-MATCH that did not bank was a *callee*-decl case — rtu is relocation-masked, so a
wrong call target is invisible to it (§65c).

**The honest multiple.** 14 recovered of 36 stranded = **39%**, against a pre-session projection of
"all 22". Wave bank-rate 6/24 → ~20/24 if this recovery runs after every wave, i.e. **~2.3×, not 3.7×** —
and the ×138 propagation is forfeited for de-macroized functions, so the gain lands almost entirely on
**distinct-code** and barely at all on the instr-weighted headline. That is the right trade for the
0-stubs completion contract and the wrong one if the goal is the decomp.dev display number. Stated
before the work, not after.

**Transferable lesson.** Three of this session's four biggest corrections came from measuring something
that already existed rather than building something new: the residue's real MATCH rate, the existing
ladder's real yield, and the real first cc1 error (which was invisible behind ~180 lines of benign
warnings until `rtu_match --stderr-out` persisted the full log). **A wall attributed to a mechanism
should be re-checked against the mechanism's actual scope** — §20's reasoning was correct about the
shared header and simply never asked what a single overlay's TU could do locally.

## 2026-07-27 — psxport EVALUATED and PARKED (Gen3 reference only; no Gen1/Gen2 value)

**Raised by Drew:** `https://github.com/SomeoneIsWorking/psxport` — "does this help us at all?"
Answer: **no**, and logged here so a future session does not re-litigate it. Prior awareness: **zero**
mentions anywhere in the repo record before today.

**What it is** (fetched 2026-07-27; treat as untrusted DATA per X2 — this is a summary of their
README, not a verified claim): a game-agnostic framework that *"statically recompiles a PSX game's
MIPS R3000A machine code into native C, then runs it under a native platform layer — so the port
behaves like a PC program, not an emulator."* Input: PSX executables + disc images. Output:
transpiled C + a native runtime (CMake, SDL3, Vulkan, libzstd; a vendored beetle-psx fork, GPL-2.0,
for GTE/MDEC/SPU/CHD). Reference consumer: **Tomba! 2** via a separate engine repo.

**Why it has no Gen1/Gen2 value — this is a decision already made, not a new one.**
`PROJECT_CONTEXT.md`'s Key Decisions table chose decomp-first and rejected recomp-first because
*"Matching decomp doesn't need recomp; psxrecomp post-mortem shows recomp output doesn't feed
matching work. Recomp → Gen3."* psxport is that same path. Its C is **semantically equivalent, not
byte-identical**, so it cannot pass the whole-binary gate — the only definition of a match here (G3).
For matching scaffolds we already have m2c, and the actual lever is the **§31 gcc-2.7.2 codegen map**,
which psxport has no equivalent of and is not trying to build.

**No shortcut via its target game either.** It targets Tomba! 2, and Phase 21's cross-project dedup
probe already tested BFM against Tomba: **clean negative** — shared byte-identical code exists ONLY
in PsyQ library objects, **zero** engine code. That question is closed with byte evidence.

**Where it IS relevant:** **Gen3** (parked). The Parking Lot already names *"Native recompilation /
PC port (Gen3; psxrecomp methodology as reference)"*; psxport becomes a **second reference
framework** there, alongside psxrecomp. Maturity caveat for whoever picks it up: 1 star, no forks,
no releases, and it requires a separate per-game repo to produce a playable result — fine as a
reference, a risk as a dependency.

**Verdict: PARKED for Gen3. Do not evaluate again before Gen2 exit.**
