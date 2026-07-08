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

**Discipline (R31 — proposed Phase 25).** **Forward-only.** Do NOT backfill historical pivots from
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
