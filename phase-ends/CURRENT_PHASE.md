# CURRENT PHASE — Phase 28: The Endgame Engine

**Started:** 2026-07-15 · **Generation:** Gen2 (20th phase of the arc) · **Plan approved:** gate 1 ✅ (Drew, 2026-07-15)
**Baseline:** v1.26.0 / PhaseEnd_Phase27 · **Roadmap:** `docs/roadmap-to-100.md` §3 P28
**Re-scoped from the roadmap** — reason below. Owner decisions this session: Fable5 = **conditional slot** (only if T3 names a NEW wall class); the **39 type-1 modules = deferred**, documented, owned by a later phase.

---

## Why this phase is re-scoped (the Phase-Start finding — byte-verified, R14)

P28 exists to measure the **member-adapt close-rate** (roadmap §6: "THE swing number"; all P28/P29 yield projections are withheld until it exists). Phase-Start verification found **the evidence behind its presumed value does not survive contact with the bytes** — the exact failure R35 was coined to prevent, by the phase that coined it.

Verified this session against the bytes:

1. **The `0x8017BEBC` refutation is a jump-table artifact, not structural variance.**
   `classify_member(ov_SC01_000→ov_SC01_001)` → **`PURE`, ndiff=2** (words 343/345 only):
   `3c01801a`/`8c224374` vs `3c01801f`/`8c22c44c` = `lui $at,%hi(jtbl_801EC44C)` / `lw $v0,%lo(jtbl_801EC44C)($at)`
   (`asm/ov_SC01_001/nonmatchings/ov_SC01_001_jr_8017A4AC/func_8017BEBC.s:380,382`) — a switch jump table.
   `config/overlays.mk:112` carves `ov_SC01_000_jr_8017BEBC.o` for the exemplar; `:134` has **no** such entry for the member.
   `family_remap.symbol_map` emits only `func_`/`D_` (`family_remap.py:419-422`) — it **structurally cannot generate `jtbl_<ADDR>`**, so the remap no-ops (2 map entries for a 952-ins fn) and the gate books a BYTE failure.
   The file's own comment (`:403-418`) documents this identical bug class for the other two prefixes, calling the result *"indistinguishable from a genuine compiler wall."* **Third instance.** The fix (`tools/jtbl_family_bank.py`, the carve ladder) exists and was never pointed at this family.
2. **That family is the least representative in the population.** Only **3 of 163** matched-exemplar families carry `has_mid_jr` (**120 of 13,232** members). The roadmap generalized n=1, atypical, to the whole frontier.
3. **All three Phase-26 exhaustion probes predate the fix that made such a probe honest.** `_carry_macros` landed in **Phase-27 T5** (`commit:0637`); the probes (tiny-IMM 0/241, PURE 0/134, pinned 0/133) are Phase 26. Phase 27's decision-log calls its own post-fix re-probe *"a **fourth** phantom exhaustion proof"* — implicitly numbering those three as the first three, recognizing the mechanism that would have faked them, and **never re-running them**.
4. **The real population was never probed.** 163 matched-exemplar families / **13,232 unmatched members** / 656,379 templatable ins. Members: **PURE 9,955 (75%) · IMM 3,140 (24%) · STRUCT 137 (1.0%)**. Families: PURE 98 / IMM 35 / MIXED 30. **96 PURE non-jr families / 7,148 members (54%) never honestly probed.** The roadmap sizes its swing number on *register-drift* = **STRUCT = 1.0%** of the input.

**The claim is "unmeasured", not "wrong"** (P9). The pre-fix bug produced CC1-FAIL; if those probes failed with DIFF it does not explain them — their failure classification was never recorded, which is itself the defect. R35: *a 0% from a broken tool and a 0% from a working one are the same number and opposite facts.*

Two further roadmap premises are stale (verified): the **parallel gate farm already exists** (`bulk_harvest.py`, 0.4s/fn @ 8 workers ≈ 75× serial; drafting, not the gate, was the documented bottleneck) — what is missing is the *same-binary* axis; and **both named grinder bugs are already fixed** (`commit:0327`, `commit:0200`) — the real defect is a 22-entry never-retry blacklist built from a broken gate.

---

## Tasks

- [ ] **T0 — Tool-health + the 2 instrument fixes that gate an honest probe** · xHigh · ⏳ IN PROGRESS
  - `make tools-health` green (audit-corpus + audit-cdecl + report, fail-closed).
  - `family_remap.img_path` (`:32-35`) hardcodes `0.4.dec` → `None` for the 4 SC07 overlays → `stream_words`→`None` → `classify_member` → `("LEN",[])` → **member silently dropped as not-templatable**. Twin of the P27 T7 `new_overlay.sh` bug, left in a second tool. Fix + **assert coverage (R32)**: a missing image fails loud.
  - Regenerate `.run/family_hseq.json` (covers **134** overlays; 138 sig files exist; carries pre-T7 `68.9` vs the honest `67.0`).
  - **Verify:** 138 overlays in the map; SC07 members classify to a real class, not `LEN`.
- [x] **T1 — the honest `0x8017BEBC` re-probe (roadmap B2)** · Max · ✅ **8/8 BANKED — B2 LIVES**
  - Add `jtbl_<ADDR>` to `symbol_map`'s keys, belt-and-braces, on the file's own documented rationale.
  - Re-probe via `tools/jtbl_family_bank.py` (carve ladder `raw→scoped→recovered→reconciled`, `:116-193`) — **not** `family_sweep` (no carve step). `--raw` first (a reconciled body is TU-specific and poisons the template).
  - Bounded ~8 members, byte-gated, R22-clean. **Either outcome is the deliverable.** Correct `calibration.md` + `decision-log.md` (R31) in-session (R30).
- [ ] **T2 — Purge the poisoned grinder blacklist** · xHigh (small)
  - 22 permanent never-retry entries built from a known-broken gate (`tooling-audit.md:927-931`: 16/22 never compiled, 5 absent); `worklist.md:50,56` marks two of them **"none — MATCH"**. Purge; fix `harvest_verify`'s `--src`/`--asm-subdir` split coupling that poisoned it; re-derive only from the fixed gate.
- [ ] **T3 — The stratified templatability re-probe: THE swing number** · Max · 🚩 **milestone report to Drew** · blocked by T0,T1
  - Strata: **PURE non-jr** (96 fam / 7,148 members) · **IMM** (35 fam, `imm_map_tier1`) · **MIXED** (30 fam). ~8–12 members/class, byte-gated, R22-clean.
  - **Classify every failure** (`harvest_verify.classify_fail` → DIFF/PLUMBING/CC1-FAIL/SKIP) — the distinction Phase 26 never recorded.
  - **Do not score with `masked_diff`** — `mask_for` drops HI16/LO16 (`:92-124`), blind to this delta class (would score all 112 `0x8017BEBC` members a perfect 0). The gate decides.
  - **Deliverable:** honest per-class close-rate + taxonomy → rewrite `calibration.md`'s decisive table; decision-log (R31); Roadmap delta.
  - **Decision point (P5d):** high → T4 + a bounded first harvest (the gate's "measured engine throughput"); ~0 → thesis retired on evidence that holds, pivot to T5/T6.
- [ ] **T4 — `member_adapt.py`, scoped to what T3 measured** · xHigh · CONDITIONAL on T3
  - Reuse: `classify_member` (per-delta + index attribution), `imm_map_tier1`, `remap`'s `imm_map` hook, `jtbl_family_bank`'s ladder — the "delta engine" is largely written. The **novel** part is the post-flight diff (exemplar compiled **in the member's own TU** vs member target); pre- and post-flight can disagree for reasons outside the C body. On failure emit the per-member **delta brief**.
- [ ] **T5 — Resident flag-plant → 100% or an honest wall dossier** · xHigh→Max · independent
  - **Fix `progress.py` first** (R35): `#if 0`-blind (`:418-485`) → `resident.c:868-925` double-counts `func_800D00E4` as REAL *and* stub; `:512` sums `len()`s instead of unioning sets. Reported 123/146=85.62%; honest **122/145=85.5%**; third opinion `sig-resident`=144. Reconcile before planting a flag on the denominator.
  - Prefetch: resident already imported (`~index.dat` id 3) → **one** headless `DecompileFunctions` run over the 21 addrs (R23 stop-MCP; R29 `/mcp` prompt). None of the 21 cached (`.run/ghidra_c/`=861, all ov_SC01_077).
  - Targets (`difficulty.resident.md`): 7 non-jtbl leaves · 9 other · 5 jtbl. Ledger is ov_SC01_077-hardcoded (`backlog.py:37,94`) → scope to `--binary`.
- [ ] **T6 — Gate throughput: the free win, then the missing axis** · xHigh
  - **Unconditional:** the `--chunk 1` double-build (`harvest_verify.py:199-213`) — the bisect re-runs `attempt()` on the same single element vs an unchanged baseline = a duplicate build. 1.35→1.0 builds/draft = **~26% fewer builds on the hot path**, one line.
  - **Conditional (T3 volume):** the same-binary shard farm — shard by **directory** (the build is CWD-relative → no Makefile change); a shard must own its `build/`; `cp -al` hardlink `asm/`(815M)+`extracted/`(760M); 8–16 shards (15 GB RAM / WSL2 bound, not cores).
- [ ] **T7 — Burn-down tracker + the stale-label sweep** · xHigh (cheap)
  - Burn-down over `progress --weighted` (roadmap §1 velocity = a standing obligation with no instrument today).
  - `worklist.py:194` reads `source`; the key is `source_overlay` → the R32 assertion rides a hardcoded default.
  - Stale `134`→138 labels: `fuel_manifest.reach_buckets`, `progress.fleet.md:7`, `second-oracle.md:60`, `backlog.py:22`, `worklist.py:14`, `roadmap:161-165`.

**Conditional — Fable5 slot** (window ~7/19, `Agent(model: fable)`, parallel-isolated): only if T3's taxonomy names a **new wall class** cheap-Opus has no idiom for. Distill same-session (R30). Fable5 **discovers**, cheap-Opus **applies**. Never behemoths.

---

## Milestone (gate 2)

1. The swing number **measured through working instruments** — stratified, every failure classified, `calibration.md` rewritten on it, Roadmap delta stated. *(A byte-grounded ~0% is as valid as a high rate — P9.)*
2. **Resident at 100%** or an honest wall dossier — on a denominator `progress.py` and `sig-resident` agree on.
3. **140/140 byte-identical from a genuinely clean tree** (R22), 0 NON_MATCHING (G4), all three gates green + fail-closed.
4. All three metrics + velocity reported (roadmap §1).

## Standing invariants (roadmap §5)

Whole-binary byte-gate = sole arbiter (G3/P9) · R22 clean-fleet per banked batch · tool-health green before matching · **one commit per task after this file is updated** (Drew pushes, R6/R20) · idioms → cookbook in the producing session (R16/R30) · pivots → `decision-log.md` (R31) · effort/model toggles prompted, never assumed (R26/R27) · every tool fix carries a **negative control** (it must change an answer the old tool gave).

## Blockers

*(none yet)*

## Progress log

- **2026-07-15 — Phase Start.** Load order read (PROJECT_CONTEXT + 27 PhaseEnds); no CURRENT_PHASE (P27 closed clean). Plan-mode + Max confirmed. 3 Explore agents surveyed the member_adapt substrate / the gate substrate / the frontier+resident. **Phase-Start finding (above) byte-verified by me, not taken on an agent's word (R14).** Plan approved (gate 1). Task list built (R28). Starting T0.

- **2026-07-15 — T0 (in progress).** `family_remap.img_path` fixed: derives the payload from `config/splat.<bin>.yaml`'s `target_path` (R33 — the file the BUILD reads, so it cannot drift from the bytes) and **raises** on a missing payload (R32 — a silent `None` was the defect).
  - **Negative control (the fix must change an answer the old tool gave):** `ov_SC01_001` → `0.4.dec` *unchanged* (no regression) · `ov_SC07_006` **`None` → `…/1.4.dec`** · `resident` → `…/FILE_010.dir/1.1` (works for free — useful for T5) · `ov_SC99_999` → **raises** (was a silent `None`).
  - **Downstream:** all **233** shared substantial fns between `ov_SC07_006` and `ov_SC01_001` classify **`PURE`** (reloc-only — the most templatable class). Under the old tool every one returned `LEN` = "not templatable" *and* poisoned its family's `diff_class` to `MIXED` (`family_hseq.py:141-143`). Fourth instance of the project's dominant defect class, and it sat directly under the number P28 was chartered to measure.
  - **`.run/family_hseq.json` regenerated** (pre-image kept at `.run/family_hseq.json.pre-T0`): **134 → 138 overlays**, newly visible = the 4 P27 SC07 overlays; metrics re-baselined **68.9 → 67.0% instr** (now agreeing with the committed `docs/progress.fleet.md`); **LEN across the whole frontier = 0** (a phantom-LEN from a missing image is now structurally impossible).

  - **🔑 T0 FINDING — a large, doubly-hidden target pool.** Regenerating exposed **1,255 families / 6,268 members / 230,612 ins whose ONLY unmatched members are in the 4 new SC07 overlays** (0 elsewhere — a perfectly clean partition), each behind an **already-matched, byte-proven ov_SC01_077 exemplar**. Classes **PURE 5,575 (89%) / IMM 633 (10%) / STRUCT 60 (1%)**. It was hidden twice over: P27's disc audit *created* it by onboarding the overlays but never regenerated the map — and had it, the `img_path` hardcode would have classified every member `LEN` and it would have looked like nothing. **Prediction, not a bank** (h_seq predicts; the gate decides — Phase 26 predicted PURE too and the gate refused). → T3's headline stratum, and a *better* probe than planned: the exemplar is already byte-proven, so a failure isolates the templating mechanism with no drafting variable.

  - **↺ SELF-CORRECTION (R14).** The plan's own population figures (163 families / 13,232 members) came from the **stale** map — my own numbers were an instance of the defect this phase is about. Honest, from the fixed map: **1,418 matched-exemplar families / 21,889 unmatched members** (PURE 17,024 = 78% · IMM 4,473 = 20% · **STRUCT 392 = 1.8%** — the roadmap's "register-drift" swing class remains ~2% of the input, so that framing is unchanged). The legacy pool is *unchanged* at 163 families (a clean consistency check: the fix and the 4 overlays are purely additive); it grew 13,232 → 15,621 members because legacy families also gained SC07 members.

- **2026-07-15 — T1 ✅ `8/8 BANKED` — roadmap B2 LIVES; the ≈0% doctrine has no surviving evidence.**
  - **The probe:** `jtbl_family_bank.py func_8017BEBC ov_SC01_000 0x8017bebc --raw .run/phase26-cracks/func_8017BEBC.c` over 8 of 115 members (4 same-address + **4 cross-address**, exercising `to_addr`) → **`{'BANKED': 8}`**. **R22: `make clean` + extract-all + `check-all` → 140 passed, 0 failed of 140**, exit 0, zero FAIL lines.
  - **Root cause of the P27 0/8 — a missing build step, byte-verified:** `0x8017BEBC` is a **jr/switch** core. §47 banked its exemplar as *"lazy isolation → carve (9-piece interleave) → splice → BYTE-IDENTICAL"* and called the fix *"×N template-safe"*. `family_sweep.hseq_sweep` stages C and gates — **no carve step** — so gcc's jump table is never placed. Residual = **two words**: `classify_member` → **PURE, ndiff=2** @ idx 343/345 = `lui/lw %hi/%lo(jtbl_801EC44C)`; `overlays.mk:112` carves it for the exemplar, `:134` does not for the member. **`jtbl_family_bank.py` exists to do exactly this and had never been run on this family.**
  - **Three compounding failures made the doctrine:** (1) wrong tool for the class; (2) **n=1 on the least representative family** — `has_mid_jr` = **3 of 163** matched-exemplar families; (3) its corroborating Phase-26 probes (0/241, 0/134, 0/133) are **all pre-`_carry_macros`** (P27 T5 `commit:0637`) — P27's decision-log calls its own re-probe *"a **fourth** phantom exhaustion proof"*, naming the mechanism that would have faked the first three, and never re-ran them.
  - **↺ TWO SELF-CORRECTIONS (R14), both mine:** (a) the plan's bullet *"add `jtbl_` to `symbol_map`"* was a **wrong fix from a true diagnosis** — a compiler-generated switch table is never named in C (`grep jtbl` on the exemplar → nothing), so there is no token to substitute; the fix is **placement**, not substitution. T1 became a *run*, not a code change; **no `symbol_map` change was made**. (b) `func_8017BEBC.md`'s header still says *"close=2 of 952"* — the state BEFORE §47's slider; the `.c` was updated, the `.md` was not. Templating from the header's body would have produced zeros I'd have misread as a wall.
  - **Scope honesty (P9):** this refutes the **evidence** for ≈0%; it does **not** establish a general rate. n=1, and jr is the rarest class by construction (3/163). **T3 measures the rate.**
  - **Distilled in-session (R30):** cookbook **§53** (the carve law + the `--raw` rule + the `symbol_map`-jtbl trap + the "before a 0% retires a lever" test) · `calibration.md` (the decisive table **rewritten**; the ≈0% row marked an artifact) · `decision-log.md` (R31).
  - **Carried:** the remaining **107** members of the family (≈101,864 ins, ~0 tokens) → T1b.

- **2026-07-15 — T1b ✅ the B2 family swept: `102 of 115` banked (88.7%), ~0 agent tokens.**
  - **Sweep:** 107 remaining members → **`{'BANKED': 94, 'gate-fail': 7, 'remap-refuse': 6}`**. Family total **8 + 94 = 102 / 115**. **R22: `make clean` + extract-all + `check-all` → 140 passed, 0 failed of 140**, 0 FAIL lines.
  - **📈 FLEET (measured, `make report`): instr-weighted 67.0% → 67.7% (+0.7pp, +97,104 ins) · distinct-code 47.8% → 49.4% (+1.6pp) · fn-count 82.16% → 82.19%.** 102 × 952 = **97,104** = the exact measured delta (the arithmetic reconciles to the byte).
  - **The 13-member tail is the predicted shape, and both halves are data:**
    - **6 remap-refuse** = *exactly* the family's 6 IMM members (`cls_counts` PURE 109 / IMM 6). `imm_map_tier1` **refused rather than guessed** — `unresolved immediates: [(512, 'asm-ambiguous')]` (512 also occurs at a non-differing position, so a blind swap could corrupt it). This is the concrete shape of T3's IMM stratum.
    - **7 gate-fail** = genuine byte-DIFFs, correctly rejected; **verified to leave no config/source residue** (all 7: `split_file=none cfg_refs=0` — no false-bank risk).
  - **Hygiene:** the 7 `git checkout … did not match any file` errors are benign (revert of a never-tracked path). Verified **0** untracked splits belong to a non-banked member; 91 new splits + 3 banked into existing splits = 94 ✓.
  - **The comparison that matters:** this is the family recorded as **0/8 → "≈0%, structural families do not template"** — the number that rewrote P29's arithmetic. Run with the carve its own exemplar required: **88.7%**.
  - **Scope (P9, unchanged):** still **n=1 family**, and jr is the rarest class (3/163). This demonstrates the mechanism at family scale; it does **not** give a rate for the PURE/IMM mass (98% of the population). **T3 is the swing number.**

  - **T3 strata (honest, from the fixed map):** SC07-only **1,255 fam / 6,268 mem / 230,612 ins** · legacy PURE non-jr **95 / 7,993 / 478,379** · legacy IMM **36 / 6,644 / 212,707** · legacy MIXED **30 / 968 / 10,462** · legacy PURE w/ jr **2 / 16 / 5,088** (T1's jtbl territory — note B2's family is far smaller here than the roadmap's "×112 ≈ 106k ins"; T1 re-derives it). **Total addressable = 937,248 ins = 21.7% of all remaining weight = 7.16pp of fleet instr if it all banked.** This is the prize the roadmap declared dead. It stays a prediction until T3's gate.
</content>
