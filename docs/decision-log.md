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
