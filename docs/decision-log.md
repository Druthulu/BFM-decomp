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
