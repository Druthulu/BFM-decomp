# Fable 5 Strategy Review — 2026-07-01

> **Standpoint:** written by the model line that generated `PROJECT_CONTEXT.md` (2026-06-10), re-reading
> the project after Phases 1–22 + Phase 23-in-progress. Drew's question: *"is there a better way, or
> more resources?"* — a strategy/scope review, NOT a re-audit of the matching mechanics (those are
> byte-gated and were independently proven sound for ~10 straight phases).
>
> **Evidence basis:** the PhaseEnd record (1–22), `CURRENT_PHASE.md` (Phase 23), the Phase-21 5-scout
> collaboration sweep, and the 2026-07-01 T10 measurements. Claims below cite their source; anything
> new is marked as a **hypothesis to probe**, not a finding (R14).

---

## 1. Scorecard — the original scope vs. reality

**What held (better than I had a right to expect):**
- The two "foundational unknowns" I front-loaded — the overlay map and the compiler fingerprint —
  resolved exactly where scoped (Phase 3 byte-proof; Phase 6 pin incl. the `--expand-div` find).
- **The dedup economics bet was the project's single best call.** I scoped Gen2 as "dedup-first
  economics (overlay-heavy game — one match often unlocks many)"; reality: 9,366 h_exact cross-binary
  groups, the ×134 propagation engine, and a fleet that went 3.8% → 64.6% largely on that lever.
- The governance layer (byte-gate as sole arbiter, P9 honesty, R14 verify-vs-bytes) did its exact job:
  **zero false matches banked in the project's life**, several would-be disasters caught (the "42%"
  permuter mirage, the 0/222 harness bugs, recon false positives).
- Repo hygiene / public-ready-from-day-one — intact and cheap to maintain.

**What emerged that I did not scope (the project out-innovated its constitution):**
1. **The swarm-draft + byte-gate harvest pattern** (Phase 12) and its industrialization into the
   **local fine-tuned drafter** (Phase 23: corpus flywheel, $0 LoRA, bulk_harvest factory). My scope
   assumed one agent grinding the matching loop; the actual engine became *many cheap drafters behind
   an incorruptible gate*. This is a genuine methodological contribution beyond the original plan.
2. **PsyQ library LINKING instead of decompiling** (Phase 7) — ~1,000 functions byte-identical from
   real SDK objects. I scoped hand-matching them.
3. **The walls themselves.** I listed "wrong compiler era" as the risk; the real binding constraints
   turned out to be *within* the right compiler: the K&R loose-typing wall (P16) and the
   scheduler/regalloc quirk tail (P17–18, partially cracked by the register-pin toolkit).

**Where reality deviated from my scope and the deviation should now be revisited:**
- **The public flip (Phase 14) has been deferred twice.** I placed "go public" *inside* Gen2
  deliberately — community labor was always the intended scaling resource. See §4/§6: this is my
  strongest recommendation.
- Gen2's "engine systems RE" (naming, semantics, docs) was traded for match-% — rational at the time,
  but the comprehension debt is now real (the overlays/resident are ~all `func_*`; resident symbol
  file still count=1). It gates both the public flip's attractiveness and Gen3.

## 2. Position assessment (honest numbers)

- **64.6% function-count / ~30% byte-weighted** (decomp.dev-comparable), 136/136 binaries
  byte-identical, 0 NON_MATCHING linked. The gap between the two numbers is the deferred giants +
  per-overlay unique code — the *hard* 70% of bytes.
- **The cheap-automation era is over, and that was proven, not assumed:** waves exhausted (P21),
  permuter dry (P22: 0 banks), recovery levers systematically built and tapped (§17–§28), the ≤15
  band now ~92% saturated at $0 (T10.6: 1,297 banks). Each ceiling was byte-proven before moving on —
  this discipline is why the project has never wasted a phase.
- **Asset inventory** (what the next strategy gets for free): the gate/propagation toolchain, the
  2,891-pair verified corpus + LoRA pipeline, the bulk_harvest factory (draft-bound at ~13.5s/fn,
  gate ~free), the §17–§28 cookbook, the ranked near-miss backlog, `xsig`, and a 3080 Ti + 32-thread
  box + Drew's willingness to spend on cloud.

## 3. Adversarial pass on the byte-proven walls

I tried to break three "settled" conclusions. Two hold; one has a genuine gap.

**(a) "No external shortcut" (P21 5-scout sweep) — HOLDS, with one caveat.** The sweep was thorough
(SOTA parity, sister-game dedup clean-negative, no Square symbols). Caveat: it answered "is there a
shortcut *for matching*?" — it did not (and could not) answer the *resource* question, because the
biggest untapped resource isn't a technique. It's **people** (§4).

**(b) The gcc scheduler/regalloc last-mile on giants — HOLDS.** `func_801372B0`-class residuals are
real compiler nondeterminism-from-C; the register-pin toolkit already recovered what it can. The
cost is also already mitigated: INCLUDE_ASM + a banked structural draft is the community-standard
honest state for these. No change recommended.

**(c) The loose-typing wall (P16) — TIMESTAMP GAP; RE-TEST.** The wall was declared **2026-06-19**.
The tools that most directly attack declaration conflicts were built **after** it:
`cast_call_sites` (06-21), the canonical-sig layer (06-20), block-scope extern relocation
(`recover_giant`, 06-26→29 — which *specifically* lets different functions in ONE TU use different
callee declarations, i.e., a direct counter to "no single consistent signature exists"),
`inject_capped_externs` (07-01), and **v3 itself** (which banks classes the Opus-era waves missed).
The P21 waves did run an evolved pipeline over the reach-134 tractable band — but the **>15-ins
struct-core walled inventory has never been swept by v3/v4 through the full current recovery stack**.
**Hypothesis to probe (cheap, bounded):** one systematic re-pass of the P16-walled inventory with
today's pipeline. Even a 5–10% recovery rate on ~900 walled fns is material. Conclusions must not
outlive the capabilities they were tested against.

## 4. The July-2026 landscape — "more resources?"

1. **Frontier models (the T10.7 OpenRouter test) — endorse, with a scope tweak.** Don't aim it at
   small functions (v3 owns that band at $0, now saturated). Aim it at the **reasoning-shaped hard
   band**: the loose-typing reconciliation (finding a consistent declaration strategy across
   contradictory call sites IS a reasoning problem, not a pattern problem), giants' structural
   drafts, and the class-labeled backlog near-misses. Include a **P16-walled sample** in the test set
   (§3c). Measure bank-rate AND $/match against v3-with-recovery as the baseline.
2. **Fable-5-class orchestration (this session).** The change isn't raw capability — it's that
   architect-level judgment is now cheap enough to run *continuously* instead of only at phase
   boundaries. Use it for the strategic calls (this review, the goal fork in §5), keep the cheap
   tiers for drafting (the cheap-tier A/B economics still hold).
3. **THE underused resource: external contributors — re-elevate the public flip.** Every peer
   project (sotn, Xenogears, VS) crossed the hard middle on community hand-matching — exactly the
   labor-shaped work (quirk tail, giants, per-overlay unique) that our automation has byte-proven it
   cannot finish alone. The P21 sweep proved no external *technique* exists; external *labor* does,
   and the project was built public-ready from day one for precisely this moment. Prereqs are known
   and already designed: the R20 clean-mirror plan (no in-place scrub), a rom→decoder regeneration
   path (H1), CI, and a minimum of naming/on-ramp work (§1). The banked near-miss backlog with
   best-drafts is, incidentally, a **perfect contributor menu** — ranked, scoped, with starting code.
4. **Publish the drafter + corpus** (`community-matching-model-plan.md`, parked) — pairs naturally
   with the flip; a decomp.me-adjacent gcc-2.7.2 drafter would attract exactly the contributors we
   want, and the VS (CC0) sibling makes a clean shared corpus (cross-project idiom memory).
5. **ML extras (permuter-guide scorer, etc.)** — the corpus now exists to try, but low expected value
   vs. items 1–4. Keep parked.

## 5. The strategic fork my original scope now needs answered

The constitution says: *"Progress is measured only in matched bytes."* That was the right razor for
Gen1–2. At ~30% byte-weighted with **byte-proven intrinsic walls**, it needs a conscious re-decision,
because the remaining byte-weight has sharply rising marginal cost. Three coherent postures:

- **A. Archival purity** (grind toward 100% match): the community-norm long game; the public flip is
  then *mandatory*, because only community labor finishes it. Timescale: years, like every peer.
- **B. Dual-metric honesty** (my recommendation): keep "matched" sacred (G3 untouched), but formally
  track **coverage** (matched + LINKED + honest NON_MATCHING-drafted) alongside it, and gate Gen3 on
  coverage + specific subsystem completeness rather than match-%. G4's NON_MATCHING discipline was
  designed for exactly this coexistence. Gen3's actual gates (shiftability, asset export, port) need
  *understood and symbolized* code more than they need the last scheduler-quirk bytes.
- **C. Pivot to artifact value** (Gen3-first: asset export, port): premature — but a cheap
  **shiftability probe** (do INCLUDE_ASM-heavy overlays already link at shifted addresses? where does
  data-side symbolization actually break?) would tell us how far Gen3 really is. Hypothesis only.

This is Drew's values call, not mine. My input as the original architect: the scope always intended
the byte-match to be the *foundation*, not the finish line — Gen3 exists in the constitution.

## 6. Ranked recommendations

1. **T10.7 as planned, re-aimed at the hard band** + include a P16-walled sample (§3c, §4.1). Signal
   in days, near-zero build cost.
2. **The walled-inventory re-pass** with the current pipeline (v3 + block-scope externs + cast tool +
   canon/sig_unify) — bounded, deterministic-ish, tests §3c directly. Fold into #1's batch.
3. **Schedule the public flip as a real near-term phase** (not "Gen3+ someday"): R20 clean mirror,
   rom→decoder, CI, naming pass on the major systems, contributor on-ramp from the backlog. This is
   the only lever that scales into the tail our machines have byte-proven they can't finish.
4. **Adopt the dual metric (posture B)** and restate the Gen2 exit / Gen3 entry gates in those terms.
5. **Shiftability probe** (one bounded spike, hypothesis-testing only) to price Gen3 honestly.
6. Keep parked: vLLM/batching (only if bulk drafting returns), ML scorer, 14B-cloud (defer until #1
   says fine-tune-scale beats frontier-reasoning on the hard band — it may not).

## 7. What I would NOT change (explicit endorsements)

The byte-gate-as-sole-arbiter architecture; the honesty rules and their enforcement record; the
phase-gate governance + PhaseEnd record (this review was only possible because the record is
complete and truthful); the measure-before-investing discipline; keeping the raw dump out of git;
the decision to saturate the small band with the $0 local model before spending on cloud.

---

*Review written in-session on the full loaded context (R30). Next concrete action remains T10.7,
modified per §6.1 — awaiting Drew's OpenRouter key + model pick, and his read of §5.*
