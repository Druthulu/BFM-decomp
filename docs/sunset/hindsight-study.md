# Hindsight Study — the optimal order to run an AI-driven matching decompilation

> **HISTORICAL (marked 2026-09-07, Phase 33.5).** Written 2026-07-20, mid-Phase 29, at ~78% instruction-weighted / ~66%
> distinct-code — four phases and the largest lessons of the project (integration, not idioms, as the bottleneck; the
> instrument-diagnosis campaign; the twin *band*; the differential-oracle harness; the ROM-firewall cost) still ahead of it. Its
> §6 commission — "a study pass that turns this into a general roadmap" — was fulfilled by other documents. Read those; this
> file is kept as the record of what the project believed at 78%. **Superseded part by part:**
>
> | Part | Superseded by |
> |---|---|
> | §0 the thesis and the order | `docs/how-to-ai-decomp/03-bootstrap-order.md` (fuller, later, with the 12-item new-project checklist) |
> | §1–§2 the reordering argument | `docs/generic-decomp-package.md` (adds the twin band and the widening review) + how-to ch.03 |
> | §3 the seven meta-principles | `docs/portable-decomp-workflow.md` and the how-to chapters (written target-agnostically during the campaign) |
> | §4 the tool inventory | `docs/gen3-handoff.md` §5 (the current lever table) + the wiki page *Tools from this project* |
> | §5 what stays hard | `docs/retrospective.md` §5 (which cites this §5 and extends it from the last phases) |
> | §6 the study commission | fulfilled — `docs/retrospective.md`, the how-to, `tools/mine_hindsight.py` |
> | §7 mine the permuter's failures | realised as `tools/autopsy.py` + `tools/residual_class.py`; the live pointer is how-to ch.03, Phase 2b |
>
> **Purpose (as written in July).** This document is a *study substrate*, not a status report. It distills what the Brave
> Fencer Musashi (BFM) decompilation taught us about **how to sequence a matching decomp**, separated
> into (a) BFM-specific facts and (b) platform/compiler-agnostic principles. It is written to be handed
> to a reasoning agent (a "Fable" study pass) that will read the full project history — `PROJECT_CONTEXT.md`,
> every `phase-ends/PhaseEnd_*.md`, `docs/decision-log.md`, `docs/matching-cookbook.md`, the `docs/gcc-2.7.2-map/`
> — and refine this into a **general roadmap for future decomps on any platform and compiler**.
>
> Written 2026-07-20, mid-Phase-29, at ~78% instr-weighted / ~66% distinct-code, from a project that ran
> ~29 phases almost entirely AI-driven under a human-gated phase system. The claims here are grounded in
> the decision-log (R31) and the phase-ends; where a lesson is uncertain or BFM-specific, it says so.
>
> **How to read this for generalization.** Every section is tagged **[UNIVERSAL]** (transfers to any
> matching decomp), **[COMPILER-CLASS]** (transfers to same-compiler-family projects, e.g. other gcc-2.7.2
> PS1 titles), or **[BFM-SPECIFIC]** (an artifact of this game, listed only to show the reasoning). A future
> roadmap should keep the UNIVERSAL spine, adapt the COMPILER-CLASS parts per toolchain, and discard the
> BFM-SPECIFIC details.

---

## 0. The one-sentence thesis

**The bottleneck is never where you think it is** — so the optimal order front-loads the two things that
*compound* (structure-mapping + propagation tooling, and measurement integrity), builds the *integration*
layer before you need it, and treats raw per-function *cracking* as the last, scarcest resource to spend,
because everything else multiplies it.

Ideal order in one breath **[UNIVERSAL]**:
**byte-match baseline → pin the compiler by evidence → honest corpus census (with self-asserting tools) →
build propagation + reconcile tooling → build the codegen-idiom map + start the permuter → then crack,
leverage-first, letting each crack fan out across all its duplicates.**

---

## 1. What our ordering got RIGHT (keep these first, in this order)

**1.1 Deterministic extraction + a 100%-`INCLUDE_ASM` byte-match baseline before writing any C. [UNIVERSAL]**
SHA1 equality of the rebuilt binary is the only definition of "matched" that cannot be gamed (our G3/P9).
Establish it *first*: a build that reassembles the original disassembly to a byte-identical binary, with the
SHA check wired into the build so there is no "third state" between match and fail. Everything downstream —
every claim of progress — is measured against this incorruptible oracle. Getting this first prevented the
documented AI failure mode (stubs/HLE/redefined-success) that has killed other agentic RE attempts.

**1.2 Pin the compiler/assembler triple by *evidence*, before bulk matching. [UNIVERSAL, method] / [COMPILER-CLASS, the answer]**
The single highest-stakes early decision. Copying a sibling project's toolchain (we were tempted by sotn's
gcc-2.6.3) would have produced systematic near-miss diffs on *every* function — an invisible poison. We pinned
gcc-2.7.2 + the ASPSX assembler version by *fingerprint evidence* (library stamps in the binary + idiom-revealing
probe functions), not by assumption. **Universal rule:** identify the exact compiler, version, optimization
default, and assembler by evidence from the binary itself, and expect per-module variation (mixed -O levels,
mixed compilers within one image). Never inherit another project's triple without re-proving it.

*These two were correctly first. Everything below is what we'd RE-ORDER.*

---

## 2. The four things to re-order (each learned the hard way)

### 2.1 Characterize the corpus SHAPE before choosing a strategy — and never build strategy on an unverified measurement. [UNIVERSAL]

Our most expensive mistakes were not bad matches — they were **strategic misdirections built on broken-tool
readings.** The worst: a "structural families template at ≈0%, so families can't be automated" doctrine that
**steered two entire phases** of strategy. Its evidence was a single probe that silently omitted a required
jump-table carve; run correctly, that same family matched **89%**. The 0% and the 89% were the same number
produced by a broken vs a fixed tool — *opposite facts.*

**The re-order:** the first move after the byte baseline is an **honest census of the corpus**:
- How much is **byte-identical duplication** (the free tier)?
- How many **structural families** (the same function recurring, differing only in per-location symbols/immediates)?
- What is the **reach × size distribution** (how many copies does each function have; how big is each)?
- How large is the genuinely-**unique tail**?

And — the meta-discipline that must accompany it — **every scanner asserts its own coverage** (compare what it
found against an over-approximating candidate set and fail on the gap), and **every measurement is checked
against a second, disagreeing oracle before any strategy is built on it.** (Our rules R32/R34/R35.) We adopted
this at Phase 26 and immediately found *seven* silent-skip bugs and the collapse of the ≈0% doctrine. **It
belongs at the foundation, not as a late audit.** A perfect correctness oracle (the byte-gate) is a *null*
oracle for coverage — it is green at 0% decomp — so it cannot tell you what you *failed to attempt*. You need
a second instrument that can.

> Generalization: on any platform, before sequencing the work, measure the shape of the problem with tools
> you have *verified against a disagreeing oracle*. The cost of a wrong shape-measurement is phases of
> mis-directed effort, not hours.

### 2.2 Build the propagation / dedup infrastructure IMMEDIATELY after the first match — not incrementally over 15 phases. [UNIVERSAL where duplication exists; magnitude BFM-SPECIFIC]

The dominant economic fact of BFM: it is **~137 position-locked copies of one shared engine** streamed as
overlays, so **one crack banks ~137 members for free.** We *knew* the overlay structure early (Phase 3) but
did not have the propagation tooling (`dedup_propagate`, `family_sweep`, `jtbl_family_bank`) mature until many
phases later; we built it reactively. **Front-loading it means every crack compounds from match #1.** This is
probably the largest leverage we left on the table through ordering alone.

Mechanics worth generalizing:
- **h_exact** duplicates (byte-identical, same address) → author once as a shared macro/body, propagate to all
  members, byte-gate each. Zero-crack.
- **structural families** (same skeleton, per-location relocations/immediates) → crack one exemplar, then
  *mechanically remap* the per-member symbols and byte-gate each. Near-zero-crack after the first.
- The right unit of work is **the family, not the function.** Rank and schedule by family leverage.

> Generalization: any target with repeated/loaded code (overlays, statically-linked shared libs, templated
> code, copied engine across levels) has this multiplier. Detect the duplication structure and build the
> propagate-and-gate pipeline *before* bulk matching, so cracking is never the thing you repeat.

### 2.3 Order the matching by LEVERAGE, not by DIFFICULTY. [UNIVERSAL]

The intuitive ramp is "smallest, simplest leaf functions first." That is *lowest-leverage*. Fleet progress is
function-weighted and reach-multiplied, so the correct schedule is **highest (reach × size) first**: crack the
exemplar that unlocks the most members and the most instructions. We eventually built a leverage-ranked family
manifest and it changed everything; doing it from the start would have front-loaded the percentage gains and
surfaced the *shape of the hard tail* far earlier.

> Generalization: build a difficulty/leverage inventory early, but sort execution by **leverage**, and
> re-sort as the frontier shrinks. "Easy first" optimizes for a feeling of progress; "leverage first"
> optimizes for actual progress.

### 2.4 Read the compiler SOURCE and build the codegen-idiom map early; run the permuter continuously from the first near-miss. [COMPILER-CLASS map / UNIVERSAL permuter]

Two compounding assets we built late:
- **The codegen map** (our `docs/gcc-2.7.2-map/` + cookbook §31): a catalog of *compiler pass → residual diff
  pattern → C-level lever that fixes it*, built by **reading the actual compiler source**. Before it, cracking
  was per-function guesswork; after it, cracking became systematic pattern-application and every subsequent
  match got cheaper. A frontier model reading the compiler source broke wall-classes that trial-and-error
  could not. **This is a "do it up front" investment**: the map pays back on every crack that follows.
- **The permuter track** (decomp-permuter, automated by our `grinder`): **LLM-free**, CPU-bound, it takes a
  *close* draft (within a few instructions) and randomizes the C to close regalloc/scheduling residuals. It
  runs **in parallel** with everything else on a *different budget* (CPU, not tokens/reasoning). It should be
  grinding the near-miss backlog continuously from the first close draft. We ran it late; running it from the
  start is free background yield.

> Generalization: whatever the compiler, invest early in a *residual→lever* map derived from its actual
> behavior (source if available, else systematic probes), and run a search-based closer (permuter or
> equivalent) continuously on near-misses. The map makes cracking systematic; the permuter harvests the tail
> for free.

---

## 3. The meta-principles (the transferable spine)

1. **The bottleneck is never where you think.** We optimized *cracking* (making a function match) while the
   real bottleneck was *integration* — banking a proven match past translation-unit / declaration / symbol
   conflicts (our §58/§59 reconcile classes). "Matching is solved; integration is the bottleneck" became true
   once cracking was systematic. **Build the integration/reconcile layer before you need it, and budget for
   banking, not drafting.** [UNIVERSAL — the *specific* conflict classes are COMPILER-CLASS]

2. **Incorruptible oracles or nothing.** The byte-gate (SHA1) is the only arbiter; intermediate metrics
   (closeness scores, standalone match, "looks right") are *candidates*, never matches. Every automated actor —
   AI agent or deterministic tool — reports to the byte-gate, so a wrong answer cannot land. This is what makes
   heavy automation *safe*: a weak model or a buggy tool is a throughput risk, never a correctness risk. [UNIVERSAL]

3. **A correctness oracle is blind to coverage.** The byte-gate is green at 0% decomp because the fallback
   pastes the original bytes. So it can prove *what landed* is correct, but never *what you failed to attempt*.
   You need a **second, disagreeing oracle** for coverage, and **every scanner must assert it did not silently
   skip**. Most of our worst multi-phase errors were invisible *because nobody compared what a tool found to
   what it should have found.* [UNIVERSAL]

4. **Fix the instrument before trusting the measurement.** A number from a broken tool and a number from a
   fixed tool are the same number and opposite facts. Tool-integrity is a *precondition* of a measurement, not
   a parallel concern. [UNIVERSAL]

5. **Leverage compounds; effort doesn't.** Prefer the move that makes the *next* move cheaper — the codegen
   map, the propagation pipeline, the reconcile tooling, the permuter — over the move that banks one more
   function. The whole project is a flywheel: each match should lower the cost of the average future match. [UNIVERSAL]

6. **Capture the perishable reasoning while it's fresh.** The terse "what changed" record survives; the *why*
   (the judgment behind a pivot, the byte-evidence behind a near-miss crack) evaporates across a context
   boundary. We keep a decision-log (R31) and a cookbook (R16/R30) written *during* the producing session.
   For an AI-driven project this is load-bearing: a fresh session inherits only compressed summaries. [UNIVERSAL for AI-driven]

7. **Humans gate direction; automation fills between the gates.** The phase system (two human gates per phase —
   plan approval and milestone confirmation — with autonomous execution between) is what let ~99% of the work
   be AI-driven without drifting. The gates are where a wrong *direction* gets caught; the byte-oracle is where
   a wrong *result* gets caught. Both are needed. [UNIVERSAL for AI-driven]

---

## 4. The tool inventory worth porting (what we built) [COMPILER-CLASS / re-implementable]

A future decomp on a similar stack could lift these directly; on a different stack, re-implement the *roles*:
- **Corpus census & family map** — cluster the frontier by byte-identity (h_exact), reloc-only skeleton
  (h_norm), and mnemonic skeleton (h_seq); rank families by leverage. (`family_hseq.py`, `family_manifest.py`)
- **Propagation** — author-once-share-many for duplicates and structural families, each member byte-gated.
  (`dedup_propagate.py`, `family_sweep.py`, `jtbl_family_bank.py`)
- **Per-function gate** — compile one function standalone, relocation-mask, compare to target; a fast local
  loop an agent iterates against. (`match_one.py`) + **whole-binary gate** (`harvest_verify.py`).
- **The reconcile ladder** — the *integration* layer that banks a proven match past TU-local conflicts:
  callee-decl casts, data-decl conformance, self-decl normalization, def-side canonical-sig reconciliation,
  symbol-name normalization (decompiler names → linker names), opt-level relocation. (`cast_call_sites.py`,
  `reconcile_tu.py`, `normalize_self_decls.py`, `canon_sig_reconcile.py`, …) — **this is the part everyone
  under-budgets.**
- **The codegen map** — compiler-pass → residual → C-lever catalog, from reading the compiler source.
- **The permuter track** — automated search-based near-miss closer, running on CPU budget in parallel. (`grinder.py`)
- **The burn-down tracker** — per-session velocity + remaining frontier + a *yield-floor* signal, so the
  ROI-gated close is data-driven, not a guess. (`burndown.py`)
- **Self-asserting audits** — every scanner compares found-vs-should-have-found and fails on the gap.

---

## 5. What is genuinely hard and stays hard (be honest in the roadmap)

- **The novel unique tail.** Functions with no duplicate, no structural sibling, and an m2c/decompiler scaffold
  too far from byte-exact for the permuter. These need reasoning (an LLM or a human) to produce the close seed.
  No deterministic normalizer we found covers all the context-dependent codegen idioms. Plan for this tail to
  be the *last and most expensive* fraction. [UNIVERSAL]
- **Compiler-internal residuals** (scheduling ties, register-allocation drift, boosted-load/delay-slot
  knife-edges): steerable only by zero-byte tricks, register pins, or the permuter — and a subset are genuine
  walls at a given model tier. Characterize them honestly; don't force a non-match. [COMPILER-CLASS]
- **Build-integration walls** (split/relocation infrastructure, jump-table carves, mixed opt-levels): these
  masquerade as "compiler walls" but are *our tooling*. Every single "wall" we deeply probed on BFM resolved
  to tooling, not the compiler. Suspect the instrument first. [UNIVERSAL lesson, BFM-SPECIFIC specifics]

---

## 6. For the future Fable study pass — how to turn this into a general roadmap

1. **Read the primary sources**, not just this summary: `PROJECT_CONTEXT.md` (the constitution + rules),
   every `phase-ends/PhaseEnd_*.md` in order (the true build history + each phase's "Rules Added"),
   `docs/decision-log.md` (the R31 pivots with byte-evidence), `docs/matching-cookbook.md` (the idiom/technique
   flywheel), `docs/gcc-2.7.2-map/` (the codegen map), and `docs/calibration.md` (the measured close-rates).
2. **Keep the UNIVERSAL spine** (§0–§3, §5–§6). Re-derive the COMPILER-CLASS parts (§2.4 map, §4 tools, §5
   walls) for the target's toolchain. Discard BFM-SPECIFIC facts (the overlay count, the exact idioms).
3. **Produce a platform-parameterized roadmap**: for a new target, the roadmap should first ask —
   *what's the incorruptible build oracle? what's the exact toolchain (by evidence)? what's the duplication
   structure? what's the reach×size distribution? is the compiler source available for a codegen map? what's
   the search-closer for near-misses?* — and then sequence per the UNIVERSAL order, adapting magnitudes.
4. **Stress-test the thesis against counter-examples**: platforms with little/no code duplication (where §2.2's
   multiplier is weak), closed-source or unknown compilers (where §2.4's map must come from probes not source),
   and hand-written assembly (where "matching a compiler" is the wrong frame entirely). The roadmap should say
   where the BFM playbook *doesn't* apply and what replaces it.

> The deliverable is not "do what BFM did." It is: **measure the shape, verify your instruments, build the
> multipliers before the grind, and spend reasoning last** — parameterized by the target's oracle, toolchain,
> duplication structure, and available compiler knowledge.

---

---

## 7. The offline-automatic endgame — mine the permuter's FAILURES, not just its wins [UNIVERSAL]

> Post-project goal (Drew, 2026-07-20): drive the offline tooling toward *near-full automation*, calling the
> LLM only to get over a genuine hump. The lever we are currently **not** pulling: systematically learning from
> what the search-closer (permuter/ILS) *fails* on.

**The gap, stated precisely.** Our flywheel (R16) evolves the permuter recipes/weights **reactively from
successes** — when a human or LLM cracks a function, we distill the idiom back into the cookbook + the permuter
weights. But the permuter's **failures** — every near-miss it plateaued on — are a richer, unused signal.
Today the grinder re-logs a failure with only `closeness` + a coarse `where_stuck` label ("N mismatch") and,
for the "won-standalone-but-gate-rejected" case, a blacklist entry. Nobody asks *why the ILS plateaued* or
*what would have bridged it.* So the offline tool's coverage grows only as fast as we hand-feed it idioms.

**The loop that closes the gap — the "permuter-failure autopsy":**

1. **Enrich the failure telemetry (the cheap prerequisite — start capturing this NOW so the corpus exists).**
   On every plateau, log the **structured residual**, not a scalar: the exact mismatching instructions
   (post-mask), the register/schedule delta, the seed C used, the plateau closeness over the ILS run, and the
   mutation classes the permuter *did* try. Without this, no diagnosis is possible later; with it, the autopsy
   is a pure offline read.
2. **LLM triage over the failure corpus (batched, not per-function) → a 3-way classification:**
   - **missing-transform** — the byte-match *is* reachable by local mutation, but the permuter's mutation set /
     weights don't include the needed move (e.g., a specific commutative-operand swap, a delay-slot fill choice,
     a spill-slot sizing). **→ the LLM proposes a new permuter recipe/weight; add it to `permuter_weights.py` /
     `permuter_ils.py`; re-run the backlog. This is a PERMANENT offline win — that whole class now cracks with
     no LLM.** This is the highest-value bucket and the whole point.
   - **seed-structural** — the C *structure* is wrong (wrong loop shape, wrong aggregate layout, a missing
     idiom the permuter can't introduce because it only does *local* edits). **→ the LLM does a one-shot seed
     rewrite (the "hump"), then hands it back to the permuter to finish.** LLM used once, minimally.
   - **genuine-wall** — compiler-internal, unsteerable at this model tier (intrinsic scheduler knife-edge,
     global regalloc shift). **→ blacklist WITH A REASON + a tier tag** (R35: the verdict expires when the gate
     or the model tier changes), and revisit only on a tier upgrade. Never silently give up; record why.
3. **Track the offline-automatic fraction over time** (extend `burndown.py`): what % of the frontier the
   permuter+wrapper close with zero LLM, and how that % moves as each autopsy adds transforms. The success
   metric of this whole endeavor is *that number rising toward 1*, with the LLM's role shrinking to the
   seed-structural humps + the wall-tier escalations.

**Why this is the right shape.** It makes the flywheel **failure-driven and data-driven** instead of
success-driven and anecdotal. Each autopsy either (a) permanently widens the offline tool's reach (missing-
transform → a new weight), (b) spends the LLM once on a real hump (seed-structural), or (c) honestly files a
wall with an expiry condition. Over enough passes the offline pipeline (m2c/decompiler → corpus-NN seed →
permuter+evolved-wrapper → reconcile-ladder bank → propagate) handles the bulk unattended, and the LLM is the
scarce reserve it was always meant to be — pulled only for the genuine humps. This is the concrete mechanism
behind the "finish a sibling game (e.g. Vagrant Story) mostly offline" ambition: the more failure-autopsy
passes we run, the larger the offline fraction, on *any* same-compiler target.

**Generalization [UNIVERSAL].** For any search-based match-closer (permuter or otherwise): treat its failure
log as a first-class training corpus. Capture structured residuals, batch-diagnose with the strongest available
model, and route each failure to *extend the tool* (permanent), *spend one LLM seed* (hump), or *file a walled
verdict with an expiry* (honest). Measure the LLM-free fraction and make raising it the objective. The tool
should get stronger every time it loses.

---

*This document is evolvable (docs/ layer). It is the R31/R30 substrate for the project's "public how-to-AI-decomp"
endgame deliverable. Corrections and extensions welcome; keep the UNIVERSAL/COMPILER-CLASS/BFM-SPECIFIC tagging so
the general roadmap stays separable from the case study.*
