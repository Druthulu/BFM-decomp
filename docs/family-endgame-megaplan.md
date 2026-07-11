# BFM Family-Endgame Megaplan — draft for the Fable5 plan-mode session (2026-07-11)

> **Purpose.** Input package for a fresh **plan-mode, Fable5Max** session to build the "finish the decomp this
> weekend" plan. This file holds every byte-verified finding from the 2026-07-11 session. **The headline: the
> "87% unique tail" was a measurement artifact — most of the remaining code is templatable per-location
> families we can crack once and stamp ×~120.** Read this end-to-end, then analyze the data yourself and build
> the finish-plan. Ordering everywhere = **most byte-weight value → least.**
>
> **Effort/model discipline (R26/R27):** plan-mode = Max/Fable5 for the plan itself. Execution is mixed:
> Ultracode for breadth waves, Fable5 ONLY for hard family *cores* (discovery), cheap-Opus for applying banked
> idioms, mechanical/permuter for the rest. **STOP + prompt Drew for every effort/model toggle — Claude cannot
> set them itself.** Fable5 is GONE after ~2026-07-13 — spend it only on what nothing else can crack.

---

## 1. THE HEADLINE FINDING (byte-verified this session) — the tail is families, not unique code

We measure progress three ways (`tools/progress.py --weighted`): fn-count ~74.6% (×134-inflated), **instr-weighted
58.2%** (decomp.dev-display, shipped .text), **distinct-code 30.3%** (each unique fn once — the honest RE truth).

The distinct-code "70% remaining" *looked* like a 36,190-function unique-shape long grind when grouped by our
strict **`h_norm`** fingerprint (87.3% of remaining distinct-ins were reach-1). **That was an artifact of `h_norm`
being too strict** (it keeps normalized immediates, so per-location constant differences fragment one function
into 121 "unique" functions).

Re-clustered by the looser **`h_seq`** (mnemonic-skeleton only — same instruction sequence, ignoring
registers/operands/immediates):

- **90% of the "unique tail" collapses:** 32,432 of 36,190 "unique" fns (2.36M of 2.59M ins) share an `h_seq`
  skeleton with siblings → **754 families**; **30,117 fns / 2.2M ins (85% of the tail's byte-weight)** are
  per-location-family-shaped (many members, few addresses, ~120 overlays).
- **Substantial families (nins≥80): 986 families / 1.88M ins; the top-20 = 52% of that byte-weight; 20/20 are
  per-location-shaped** (1 distinct address across ~120 overlays).
- **Templatability CONFIRMED (sig spot-check):** top families are the SAME function per location — identical
  `nbytes`, `ncalls`, and call sequence across all members — differing only in per-location immediates/data:
  - `0x80178d40` — 890 ins × **121** members, `#addr=1`, nbytes 3560, ncalls 75 (identical across all).
  - `0x8015ae2c` — 562 ins × 121, `#addr=1`, identical structure.
  - `0x8017ca80` — 952 ins × 100, identical structure but **varying address per overlay** (cross-address variant).

**Conclusion:** the endgame is **~986 substantial families → crack ONE exemplar each → template ×~120** (plus the
tiny/low-value families and the genuine unique residue). This is the SAME leverage as the reach-134 shared engine
we already templated — `h_norm` just hid it. **This is what makes "finish this weekend" credible.**

### Caveats to carry into the plan (be rigorous — R14)
1. **`h_seq` families differ in immediates**, so they are NOT free dedup (unlike reach-134 h_exact). They are
   **templates**: one C body + per-member immediate+symbol substitution + byte-gate. Needs a `family_remap`
   extension (see §3, task T2).
2. **The two biggest families by *count* are tiny (15 ins × 6,385 and × 5,309)** — low byte-weight, and a
   15-mnemonic skeleton risks *coincidental* `h_seq` collisions. **Filter by size; the value is in the
   substantial (nins≥80) families.** Fable5 should sanity-check whether the mega-tiny-families are one real
   pattern or lumped noise (probably the cheap-tier's ≤15-ins domain already — Phase 23 saturated ≤15 for $0).
3. **Per-family crack difficulty is UNKNOWN until drafted.** An 890-ins exemplar may be cheap-Opus (clean
   structure) or a hard Fable5 class. Triage cheap-first; only walls → Fable5.
4. **`h_seq` still fragments families that differ by a few INSTRUCTIONS** (an extra branch, an inlined helper) —
   those need a fuzzy pass (MinHash/edit-distance) or Ghidra-C clustering (§5). The `h_seq` pass is the first,
   biggest, cheapest cut; the fuzzy pass is the follow-on.

### Reproduce / extend the survey (committed-reproducible)
- Sigs: `.run/sig.ov_*.jsonl` (134) + `.run/sig.resident_image.jsonl` — regen `make sig-overlays`. Each record:
  `{addr,name,src,nins,nbytes,ncalls,h_exact,h_norm,h_seq,calls}`. **`h_seq` is the family key here.**
- The survey logic (ran this session; fold into a committed `tools/family_hseq.py`): group tail (`h_norm`
  reach-1) by `h_seq`; rank families by `members × nins`; per-family `#distinct addr`/`#overlays` (per-location
  test); templatability = identical `nbytes`/`ncalls`/call-sequence across members.

---

## 2. THE PLAN SHAPE (most-value → least; validate before scaling — Phase 15/16 lesson)

**Step A (cheap/mechanical, NO Fable5) — build the real leverageable-family map + Fable5-necessary list.** This
is the measured foundation the finish-plan is built on. Do FIRST.
1. `tools/family_hseq.py` — commit the survey: `h_seq` re-cluster the whole remaining frontier (not just the
   `h_norm`-reach-1 tail — also the reach 2–10 and any `h_norm` families), rank by byte-weight, tag per-location
   (same-addr) vs cross-address vs scattered, filter tiny/coincidental. Output the ranked family map + per-family
   exemplar (prefer an ov_SC01_077 member for drafting; else the lowest-addr member).
2. **Templatability validation** on the top ~30 substantial families: confirm members are mechanically
   substitutable (identical structure, diffs = immediates+symbols). The 3 spot-checked pass; validate the rest.
3. **Cheap-Opus triage** of each top family's EXEMPLAR (draft via the existing pipeline + `match_one`/`rtu_match`
   closeness + residual class). Output: which exemplars cheap-Opus/permuter can crack vs which are **Fable5-
   necessary** (the hard cores). THIS is the "know immediately what's Fable-necessary" list, over the whole tail.

**Step B (Fable5, the 2-day window; parallel-isolated, distill-between) — crack the hard family CORES.**
- Highest leverage = the hardest EXEMPLAR of the biggest families (crack once → template ×~120). The 890/952/562
  cores are the real "monsters worth Fable5" — NOT the unique behemoths (§4).
- Also the carried Fable5 queue from this session (§6): the 2 permanent walls + the 3 walled reach-134 giants.
- Each crack → distill the idiom into cookbook §31/§45 (R30) → cheap-Opus applies it to sibling family cores.

**Step C (cheap-Opus + mechanical, PARALLEL with B and continues AFTER Fable5 is gone) — the harvest.**
- Extend `family_remap` to substitute **immediates** (task T2) + a **cross-address** variant.
- Per validated family: crack exemplar (Step A/B) → template ×~120 → whole-binary byte-gate → batched R22 → commit.
- The `≤180-ins draftable` frontier + the **5.9 MB matched-free propagation** (exemplars already matched, just
  propagate) run here too. Most of the *headline %* comes from this mechanical harvest.

**Step D (deferred / lowest ROI) — the genuine unique residue + the behemoths.** After the families collapse,
whatever's left that's truly reach-1-by-`h_seq` (and the 5 unique ≥1000-ins behemoths, §4) is the real long
grind — cheap-Opus/hand/decomp.me, post-Fable5, or never. Do LAST.

---

## 3. TOOLING TO BUILD (execution tasks — these are IN the plan, not prerequisites)

- **T1 `tools/family_hseq.py`** — the committed `h_seq` family survey + ranked map (§2 Step A).
- **T2 `family_remap` immediate-substitution extension** — the current `family_remap.py` substitutes SYMBOLS
  positionally (reloc-masked). `h_seq` families ALSO differ in immediates, so extend it to substitute per-member
  immediates too (positionally paired from the two disassemblies, like the reloc pairing). Plus a **cross-address
  variant** for families at different vram per overlay (`0x8017ca80` class). Whole-binary byte-gate is the sole
  arbiter (a wrong substitution fails+reverts).
- **T3 family-aware `family_sweep`** — feed it the `h_seq` grouping (not just `h_norm`) so one exemplar templates
  the whole `h_seq` family. Reuse the proven two-phase stage-then-gate structure.
- Existing tools that carry over: `family_remap.py`, `family_sweep.py` (`--only`, `--edit-remap`, `--reconcile`),
  `harvest_verify.py` (the gate), `canon_sig_reconcile.py`, `rtu_match.py` (real-TU-faithful closeness),
  `masked_diff.py`/`masked_scorer.py` (permuter scorer), `permuter_ils.py`, `dedup_propagate.py`.

---

## 4. FABLE5 TARGETING — the corrected doctrine (data-backed this session)

**Fable5's deliverable is PERMANENT IDIOMS, not matched functions.** Everything it discovers (e.g. this
session's §45 levers) is banked into the codegen map and cheap-Opus wields it forever, including after Fable5 is
gone. So the 2 days should MAXIMIZE hard-class DISCOVERY on high-leverage targets.

**RIGHT Fable5 targets (highest leverage):**
- **Hard EXEMPLARS of the biggest per-location families** (890/952/562… ins cores) — crack once → template ×~120
  AND bank the idiom. This is the top of the queue now.
- **The 2 permanent walls** (each a class-defining idiom): `func_801412A8` (198×134, S11 LUID×alloc permutation),
  `func_80178004` (165×134, currently matched only WITH pins → needs a pin-free lever for ×134).
- **The 3 walled reach-134 giants** (recon done this session — pin-free seeds + gdb-oracle specs, §6).

**WRONG Fable5 targets (worst ROI — do NOT burn the window here):**
- **The 5 unique ≥1000-ins behemoths** (`0x8017bf14` 4763, `0x8017d2dc` 1586, `0x8017c954` 1194, `0x8017c730`
  1061 ×2): all **reach-1 unique** — ×1, non-transferable idiom, enormous token cost, might not even close.
  Cracking all 5 ≈ 0.3% of distinct-code. **Explicitly deferred to Step D / post-Fable5.**

**HOW to run Fable5 (proven this session):** **parallel-isolated agents, NEVER one batched agent** — a giant
crack is a long tool-heavy grind (the flagship: 125 tool-calls / 506k tokens) and context accumulation makes one
shared-context agent ~N× more expensive; the §31 map already amortizes the compiler-source read, so isolation is
cheaper AND higher-quality. Crack one exemplar per distinct class → **distill to §45** → cheap-Opus mops up
transfers (the flywheel). `Agent(model: fable)`; ~375k tok/giant.

---

## 5. THE FUZZY / GHIDRA-C FOLLOW-ON (for families `h_seq` still misses)

`h_seq` requires an EXACT mnemonic sequence, so it fragments families that differ by a few instructions. To catch
those (Drew's "convert to C to find groups" idea, done right):
- **Fuzzy asm clustering (cheaper, do first):** MinHash / edit-distance / longest-common-subsequence on the
  normalized instruction stream → cluster near-duplicates that differ by a few instructions. Extends `h_seq`.
- **Ghidra-C structural clustering (heavier, complementary):** batch-decompile remaining fns (headless
  `DecompileFunctions.java` — already exists) to READABLE (not compiling) C, cluster by C-AST shape → catch
  *semantic* families with divergent asm (different scheduling/inlining). Also good for humans naming/understanding
  families (Gen2 quality).
- **DO NOT chase a "compiling C draft tool for all remaining funcs"** — that's the **Phase-16 struct wall** (m2c/
  Ghidra emit `actor->unkXXX` that won't compile without per-function struct types), and it is NOT needed:
  family detection runs on asm, and byte-matching reads access widths off the asm opcode, not a struct def.

---

## 6. CARRIED CONTEXT — this session's other findings (fold into the plan, most-value-first)

### Committed this session (`commit:0515`)
- **🎯 FLAGSHIP `func_80133CD4` (399 ins) CRACKED ×134** (Fable5 gdb-on-cc1) — the ~22-phase "unsteerable
  whole-function register permutation" retired. Fleet instr-weighted 57.7→58.2%, distinct-code 29.3→30.3%.
  **Idiom → cookbook §45** (READ IT — it's the template for the family-core cracks): (a) **merged-accumulator
  variables** break a "whole-function permutation" (K8 no-coalescing → one reused C var); (b) the **1-death
  local-alloc in-out-asm** (`flow.c:2511`, pin-free/×134-safe); (c) offset-0 `/s` store; (d) goto-shared-return.
  Draft `.run/giants/func_80133CD4.fable.c`, report `.fable.md`, gdb oracle/dumps `.run/giants/fable_cd4/`.

### Deferred → Fable5 queue (recon DONE — pin-free seeds + gdb-oracle escalation specs)
- `func_8014D820` (304×134): flywheel → LCS 226 pin-free; RC-6 sched1 delay-slot (`sched.c:3199` param-pin +
  ratan2-delay-slot tie-break). `.run/giants/func_8014D820.opus.{c,md}`.
- `func_8016CBC0` (209×134): flywheel → close=153 pin-free (beat the 155-pinned ×1); qty-birth/allocno-priority
  lock. `.run/giants/func_8016CBC0.opus.{c,md}`.
- `func_801670E4` (279×134): flywheel → **close=23** pin-free (block0 fence-lock 6 + block2 S3-priority 17);
  permuter re-tried this session, **stuck at masked-22** (intrinsic). `.run/giants/func_801670E4.opus.{c,md}`.
- **2 permanent walls:** `func_801412A8` (198×134, S11), `func_80178004` (165×134, pin-free needed).
- **Flywheel reusable sub-findings to fold into §45 when these crack:** merge-lever has a **mirror split-law for
  scalars**; a new **input-only-anchor** load-early+tie dial; **§44-Lever-5 "i=0/p-hoist" DOWNGRADED** (cracked
  42→0, R14 — was mis-tagged intrinsic). Detail in the `.opus.md` files.

### F-band permuter batch (this session — all WALLED, no banks; → Fable5 or fuzzy tail)
- `func_801670E4` masked-22, `func_8012E364` masked-31 (backlog "c=4" is stale — needs a fresh draft),
  `func_801549F8` masked-2 (**2 diffs from done**, but a jump-table so a `.text`-0 still needs the rodata `jtbl`
  verified via §8 workflow). The free permuter tier is exhausted on these; they're Fable5 or fuzzy-tail work.

### Strategic doctrine settled this session (Drew + data)
- **Metrics:** report all three; distinct-code (30.3%) is the honest RE truth; instr-weighted (58.2%) is the
  decomp.dev-display; fn-count (74.6%) is ×134-inflated.
- **Fable5 = permanent idioms; parallel-isolated agents (never batched); distill-between; cheap-Opus mops up.**
- **Reach distribution (this session):** reach-134 shared engine 2.1% (mostly done), reach 2–133 10.6%, reach-1
  **87.3%** by strict h_norm — but **90% of that reach-1 is `h_seq` families** (the whole point of this plan).

---

## 7. FABLE5-EXAMINE-FURTHER LIST (put your compiler-internals + planning edge here, plan-mode session)

1. **Analyze the ranked `h_seq` family map** (build it via T1 first) — pick the crack curriculum: which family
   cores first/second/third by (byte-weight × crackability). Ground it on Step-A cheap-Opus triage data, NOT
   predictions (Phase-25 lesson: an ungrounded Fable5 plan is speculation).
2. **Are the two tiny mega-families (15-ins × 6,385 / × 5,309) one real pattern or coincidental `h_seq` collision?**
   Decide if they're worth a template or just cheap-tier fodder.
3. **The immediate-substitution + cross-address `family_remap` extension (T2)** — design it; it's the mechanical
   lever that converts every family crack into ×~120.
4. **The hard family cores** — the 890/952/562-ins exemplars: are they §45-class (merged-vars/1-death) or new
   classes? Each new class banked into §45 = cheap-Opus cracks the rest.
5. **The 2 permanent walls** (`func_801412A8` S11, `func_80178004` pin-free) — the flagship proved "permanent"
   verdicts fall; these are class-defining.
6. **The fuzzy/Ghidra-C follow-on (§5)** — scope how much extra byte-weight it recovers beyond `h_seq`.
7. **Honest finish math:** with ~986 families × ~120 templating, what distinct-code % is reachable this weekend,
   and what's the genuine unique residue (Step D) that is NOT weekend-finishable? Set a realistic target.

---

## 8. GATE / DISCIPLINE (unchanged, non-negotiable)
- **Whole-binary byte-gate (`harvest_verify`) is the SOLE arbiter (G3/P9)** — `match_one`/`rtu_match`/permuter
  scores are indicators, never banks. Re-verify every agent "MATCH" against the bytes (R14).
- **R22 clean-fleet every batch before commit:** `make clean` + re-extract ALL 136 + `make check-all` → 136/136.
  (`make clean` wipes `asm/`, so re-extract all before check-all; don't run R22 while agents need `asm/`.)
- **×134 pin-free rule (§42e):** `register __asm__("$N")` pins SIGABRT sibling TUs → ×1 only. Family templating
  needs pin-free bodies (generic-constraint asm + GTE blocks are fine).
- **Commits:** Claude commits locally, **Drew pushes (R6)**; never stage the `ghidra/ db.*.gbf` churn (R23); no
  `Co-Authored-By` (R5). Update `CURRENT_PHASE.md` + capture findings during the session (R30/R31).
