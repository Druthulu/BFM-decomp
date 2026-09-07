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
3. **All three Phase-26 exhaustion probes predate the fix that made such a probe honest.** `_carry_macros` landed in **Phase-27 T5** (`ee4b3a02e`); the probes (tiny-IMM 0/241, PURE 0/134, pinned 0/133) are Phase 26. Phase 27's decision-log calls its own post-fix re-probe *"a **fourth** phantom exhaustion proof"* — implicitly numbering those three as the first three, recognizing the mechanism that would have faked them, and **never re-running them**.
4. **The real population was never probed.** 163 matched-exemplar families / **13,232 unmatched members** / 656,379 templatable ins. Members: **PURE 9,955 (75%) · IMM 3,140 (24%) · STRUCT 137 (1.0%)**. Families: PURE 98 / IMM 35 / MIXED 30. **96 PURE non-jr families / 7,148 members (54%) never honestly probed.** The roadmap sizes its swing number on *register-drift* = **STRUCT = 1.0%** of the input.

**The claim is "unmeasured", not "wrong"** (P9). The pre-fix bug produced CC1-FAIL; if those probes failed with DIFF it does not explain them — their failure classification was never recorded, which is itself the defect. R35: *a 0% from a broken tool and a 0% from a working one are the same number and opposite facts.*

Two further roadmap premises are stale (verified): the **parallel gate farm already exists** (`bulk_harvest.py`, 0.4s/fn @ 8 workers ≈ 75× serial; drafting, not the gate, was the documented bottleneck) — what is missing is the *same-binary* axis; and **both named grinder bugs are already fixed** (`e91859fb4`, `4927f38c4`) — the real defect is a 22-entry never-retry blacklist built from a broken gate.

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
- [x] **T2 — Purge the poisoned grinder blacklist** · xHigh · ✅ purged (8 of 22 had MATCHED anyway)
  - 22 permanent never-retry entries built from a known-broken gate (`tooling-audit.md:927-931`: 16/22 never compiled, 5 absent); `worklist.md:50,56` marks two of them **"none — MATCH"**. Purge; fix `harvest_verify`'s `--src`/`--asm-subdir` split coupling that poisoned it; re-derive only from the fixed gate.
- [~] **T3 — The stratified templatability re-probe: THE swing number** · Max · 🚩 **stratum A done — 0 DIFF; the pool is h_exact + UNWIRED.** Strata B/C (legacy) carried → T3b
  - Strata: **PURE non-jr** (96 fam / 7,148 members) · **IMM** (35 fam, `imm_map_tier1`) · **MIXED** (30 fam). ~8–12 members/class, byte-gated, R22-clean.
  - **Classify every failure** (`harvest_verify.classify_fail` → DIFF/PLUMBING/CC1-FAIL/SKIP) — the distinction Phase 26 never recorded.
  - **Do not score with `masked_diff`** — `mask_for` drops HI16/LO16 (`:92-124`), blind to this delta class (would score all 112 `0x8017BEBC` members a perfect 0). The gate decides.
  - **Deliverable:** honest per-class close-rate + taxonomy → rewrite `calibration.md`'s decisive table; decision-log (R31); Roadmap delta.
  - **Decision point (P5d):** high → T4 + a bounded first harvest (the gate's "measured engine throughput"); ~0 → thesis retired on evidence that holds, pivot to T5/T6.
- [ ] **T4 — `member_adapt.py`, scoped to what T3 measured** · xHigh · CONDITIONAL on T3
  - Reuse: `classify_member` (per-delta + index attribution), `imm_map_tier1`, `remap`'s `imm_map` hook, `jtbl_family_bank`'s ladder — the "delta engine" is largely written. The **novel** part is the post-flight diff (exemplar compiled **in the member's own TU** vs member target); pre- and post-flight can disagree for reasons outside the C body. On failure emit the per-member **delta brief**.
- [x] **T5 — Resident flag-plant** · ✅ **21 → 14 stubs (7 banked, 85.52% → 90.34%)** — NOT 100%; honest dossier written (`docs/resident-dossier.md`)
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

*(none)*

## ⏭️ RESUME POINT (fresh session) — PhaseEnd at Max. All 11 tasks done; 1 sub-item carried.

**PhaseEnd_Phase28 is the only remaining work** (Tier-1 Max synthesis — write it in a fresh session with headroom; it re-reads the committed state cold, which is the discipline that caught tonight's stale-map/stale-.md traps). Everything it needs is in this file + the commits `76db32455`..(T3b). **Carried to P29:** the burn-down velocity tracker (T7c — a genuine new tool, no history to track until built) and the T3b disambiguating probe (below). Ratify **R36** at PhaseEnd.

**Roadmap delta to write:** B1/B2 numbers re-derived (B2 LIVES, 102/115); the "structural families ≈0%" doctrine has NO surviving post-fix evidence (calibration.md rewritten); the legacy h_seq swing number is **~3% as-tooled, ceiling unknown** (T3b — P29 must run the disambiguating probe first); binary count 138 overlays + main + resident = 140, disc-complete (the fixed disc_code_sweep confirms 0 further hidden type-4; 39 type-1 modules still pending load-address RE); R36 added.

---

### (historical) The pre-T7 resume note — T7 and T3b are now DONE (kept for the trail):

**9 of 11 tasks committed** (`76db32455` T0 → `1dbf5477d` T6). Gate items already met (swing number measured; resident resolved). Fleet **67.0% → 68.9% instr / 47.8% → 49.5% distinct**, 140/140 byte-identical throughout, 0 NON_MATCHING. **Two tasks remain; neither needs this session's accumulated context.**

### T7 — Coverage gate + the blind disc sweep + stale labels (EXPANDED, Drew-approved)
Was "burn-down + stale labels"; **promoted** after the SC07 evidence showed 4 consumers silently ignoring onboarded binaries. Three parts:
1. **`make audit-binaries` — the R32/R36 citizenship gate (the real deliverable).** Assert every onboarded binary is a full citizen of every consumer that enumerates binaries: present in the sig set, the family map, the dedup registry (or an explicit exemption), the shared-header include, and the reports/labels. A binary a consumer silently ignores is invisible work (R34). This is what would have made tonight's SC07 pool *not exist as a hidden bug*.
2. **Fix `tools/disc_code_sweep.py` — it is STRUCTURALLY BLIND to compressed code.** `:87` `if … p.endswith(".dec"): continue` excludes the `.dec` universe, and it never decompresses raw payloads — so it cannot see where all 138 type-4 overlays live (its "type 4: code 0, onboarded 0" row is vacuous). It found the 39 type-1 modules only because those are uncompressed; **it could NOT have found the 4 SC07 overlays** (those were caught by hand-reconciling 138-vs-134). Fix = decompress each payload (`lzss.decompress`, NOT the nonexistent `.decode`) + cross-reference the onboarded set + assert coverage. Tonight's ad-hoc exhaustive sweep (1190/1190, coverage-asserted) found NO further hidden overlays — 138 type-4 all onboarded, 1 type-0 hit is a false positive (469KB→578B decoder bail), types 2/3/6/7/8 = 0 code — but that must become a reproducible tool, not a one-off script (`.run/t7_lzss_full_sweep.log`).
3. **Burn-down tracker** over `progress --weighted` (roadmap §1 velocity = a standing obligation with no instrument) + **the stale `134`→138 labels** (`fuel_manifest.reach_buckets`, `progress.fleet.md:7`, `second-oracle.md:60`, `backlog.py:22`, `worklist.py:14`, `roadmap:161-165`) + **`worklist.py:194`** (reads `source`; key is `source_overlay` → R32 assertion rides a hardcoded default).

Also fold into T7: the **`func_800CEDFC` / `func_800D33E0` sig_image boundary question** (defined in `resident.c`, absent from the 2nd oracle, while `audit-corpus` = 0 PHANTOM/TRUNCATED; `progress.py`=145 vs both oracles=144). That is exactly an `audit-binaries` finding.

### T3b — The LEGACY h_seq templatability rate (still genuinely unmeasured)
T3-A answered a *cheaper* question (the SC07 pool = h_exact + unwired). The roadmap's actual swing number — the *legacy* h_seq rate — is unmeasured. Strata from the fixed map (`.run/t3_strata.json`): **B legacy PURE non-jr** (95 fam / 7,993 members) · **C legacy IMM** (36 fam / 6,644). `family_sweep --hseq --only <exemplar addrs> --chunk 1`, EXCLUDE `has_mid_jr` (§53), classify every failure (DIFF/PLUMBING/CC1-FAIL), do NOT score with `masked_diff`. Known datapoints to fold in: B2 = 102/115 (88.7%, jr+carve), stratum A = 0 DIFF (giants, h_exact), the resident wave = 7/16 gate (64% of match_one MATCH, all blocks = loose-typing). Deliverable: the honest legacy per-class rate → `calibration.md` + the Roadmap delta.

### New rule to ratify at PhaseEnd
**R36** — *A newly-discovered binary is not real until every consumer knows it.* Onboarding a code-bearing payload produces a byte-clean binary that is NOT yet a citizen; the same change must wire it into every consumer that enumerates binaries (sig set, family map, dedup registry or explicit exemption, shared include, reports/labels), asserted by a gate (R32), not remembered. Justification: P27 onboarded 4 SC07 overlays byte-clean; P28 found FOUR consumers silently ignoring them (`img_path`, the family map, the dedup registry, the overlays' own `.c`), hiding ~6,400 already-matched bodies. Every failure was silent. `make audit-binaries` (T7) is its enforcement.

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
  - **Three compounding failures made the doctrine:** (1) wrong tool for the class; (2) **n=1 on the least representative family** — `has_mid_jr` = **3 of 163** matched-exemplar families; (3) its corroborating Phase-26 probes (0/241, 0/134, 0/133) are **all pre-`_carry_macros`** (P27 T5 `ee4b3a02e`) — P27's decision-log calls its own re-probe *"a **fourth** phantom exhaustion proof"*, naming the mechanism that would have faked the first three, and never re-ran them.
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

- **2026-07-15 — T2 ✅ blacklist purged; the tool fix was already in, the audit's own premise was stale.**
  - **R14 on the premise first (twice):** (1) the roadmap's two named grinder bugs are **already fixed** (`e91859fb4`, `4927f38c4`) — stale line. (2) `docs/tooling-audit.md:933-937` **downgraded its own finding** with three corrections: *the prescribed fix is a NO-OP* (deleting the scanner banks zero fns; harvest_verify was single-TU **by construction**, the defect was mislocalized), *nothing is being discarded now* (grinder STOPPED since 2026-07-02 — confirmed, `.run/auto/STOP`), and *the queue magnitude was inflated* (1252, not 1298). So T2's only real content was the **realized-and-persisted** artifact.
  - **And the audit's snapshot is itself now stale (verified in code):** `harvest_verify` is **fully multi-TU** today — `_stubs` derives every stub across every TU from the `corpus` oracle (`:122`), `render()` splices "each draft into the TU that actually holds its stub", `_write()` writes multiple paths, un-stubbed drafts are "REPORTED, never silently dropped (R32)". **The gate that manufactured the blacklist no longer exists.**
  - **The proof the verdict was manufactured, not observed:** of the 22 entries — recorded as "permuter won, gate rejected ⇒ plumbing-bound, never re-permute" — **8 have since MATCHED anyway** (`func_80131D68/80149374/8014FE60/80150528/8016BBE0/80171C64/80174684/8017F290`); the other **14 are still stubs** and would have been skipped **forever** on a verdict from a gate that no longer exists. (The audit predicted 5 such; it is 8.)
  - **Done:** blacklist → `[]` (poisoned copy kept at `.run/auto/grinder_blacklist.json.poisoned-pre-T2`); `grinder.py` carries the **rule** (R35): *a blacklist entry is a verdict from a specific gate and EXPIRES when that gate changes — purge and re-derive; never inherit.* No `harvest_verify` change was needed or made.

- **2026-07-15 — T3 stratum A 🚩 — ZERO DIFF. The SC07 pool is the EASY (h_exact) class, and it is simply UNWIRED.**
  - **The probe (cleanest available):** the 4 SC07-only families of highest byte-weight are **the giants** — `0x80144B9C` (770, the whale), `0x80141CA4` (476), `0x80132784` (400, "irreducible for 22 phases"), `0x80133CD4` (399, the §45 Fable5 crack). Exemplars already byte-proven, members PURE, non-jr → **every confound removed; a failure here is pure mechanism.** `family_sweep --hseq --band substantial --chunk 1`.
  - **Result: 4 banked / 8 failed / 4 skipped of 16 — and the classification is the finding:**

    | verdict | fns | n |
    |---|---|---|
    | **BANKED** | `func_80133CD4` — a 399-ins Fable5 giant → **4/4 overlays, free** | 4 |
    | **PLUMBING** `parse error before ')'` | `func_80144B9C`, `func_80132784` | 8 |
    | skipped `pinned-exemplar` (the §42e guard — P27's T5 dissolved the wall behind it; `--allow-pins` bypasses) | `func_80141CA4` | 4 |
    | **DIFF (real codegen)** | — | **0** |

    **Not one failure is a byte mismatch.** Of the members that reached the gate as valid C: **4/4 = 100%**. The 8 never compiled. *This is the DIFF-vs-CC1-FAIL distinction Phase 26 never recorded — and precisely why its 0% could not be trusted.*
  - **🔑 ROOT CAUSE (byte-verified, and far bigger than the parse error): the 4 new overlays were onboarded but NEVER WIRED INTO THE SHARED-BODY ECOSYSTEM.**

    | | established (`ov_SC01_001`) | the 4 new SC07 |
    |---|---|---|
    | includes | `common.h` + **`../shared/engine_core.h`** | `common.h` **only** |
    | body | `DEFINE_func_*()` instantiations | **~2,400 raw `INCLUDE_ASM` stubs** |
    | matched | ~2,150 | ~80 |
    | refs in `config/dedup.us.yaml` | member of 1,689 groups | **0** |

    The parse error is a *symptom*: the drafts reference types (`P10/P14/P18/P1C/HDR/ENT`) that live in `src/shared/func_80144B9C.h` — a header the SC07 TU doesn't include. **1,689 registry groups say "134 binaries", never 138.**
  - **📐 SCALE (measured against the registry): 6,513 live stubs across the 4 new overlays are byte-identical to an ALREADY-REGISTERED h_exact group** (1,625 / 1,628 / 1,627 / 1,633). That is the **h_exact** class — which `calibration.md` itself rates **≈×N, near-100%** — not the h_seq class, and **not** a `member_adapt` problem.
  - **✅ MECHANISM PROVEN BY HAND (probe-before-investing):** added `#include "../shared/engine_core.h"` + swapped ONE stub → `DEFINE_func_80128158()` in `ov_SC07_006.c` → `make build BINARY=ov_SC07_006` → **`7ca772be…` BYTE-IDENTICAL**. Probe reverted; let the tool do it uniformly.
  - **The gap in the tooling:** `dedup_propagate --auto-from` only plans **11** fns here — it authors macros from ov_SC01_077's *inline defs*; the ~1,600 shared bodies are **already** `DEFINE_func_*` macros in `engine_core.h`, and `--addr` errors *"no source overlay has it matched"* because no overlay holds an inline def. **There is no mode for "extend an existing macro-backed group to a newly-onboarded binary."** → T4.
  - **R22: `make clean` + extract-all + `check-all` → 140/140**, 0 FAIL (stratum A's 4 banks).
  - **Carried → T3b:** strata **B** (legacy PURE non-jr, 95 fam / 7,993 members) and **C** (legacy IMM, 36 fam / 6,644) — the *legacy* h_seq rate, still genuinely unmeasured. The SC07 pool answered a different (and cheaper) question than the one T3 set out to ask.

- **2026-07-16 — T4 ✅ `dedup_extend`: 6,174 / 6,457 (95.6%) wired across the 4 new overlays — and TWO self-inflicted defects, both mine.**
  - **New `tools/dedup_extend.py`** — the missing mode. `dedup_propagate` is CRACK→AUTHOR MACRO→INSTANTIATE: `--auto-from` scans *inline defs* (planned only **11** here — the ~1,600 shared bodies are ALREADY `DEFINE_func_*` macros in `engine_core.h`), and `--addr` dies *"no source overlay has it matched"* because no overlay holds an inline def. **Extending an existing macro-backed group to a newly-onboarded binary had no implementation.**
  - **Safety (explicit — it feeds the byte-gate):** `h_exact` = SHA1 of RAW instruction bytes ⇒ identical h_exact means identical bytes **including** `jal`/`lui`/`%lo` reloc immediates ⇒ same C, no remap. A bug can only FAIL TO BANK, never falsely bank. **Reuse (R33):** owns only the set computation + registry edit; the splice and gate are `harvest_verify` verbatim → ~1 build/binary, not 1/function.
  - **Results:** 006 **1543/1614** · 007 **1544/1615** · 010 **1544/1614** · 011 **1543/1614** = **6,174/6,457 = 95.6%**, ~0 agent tokens. Stubs/overlay ~2,400 → 831/984/898/825. **R22 140/140** after each stage; **dedup-check 1840 validated / 0 failed**, groups now read **"138 members [138 binaries]"** (was 134); **C1 coverage 227,211 → 233,385 = exactly +6,174**. Fleet **instr 67.7 → 68.0%** on the first overlay alone.
  - **The 283 non-banks: 271 PLUMBING + 12 DIFF, ZERO unexplained-at-scale.** Plumbing = the loose-typing conflict class (`conflicting types for D_800A5E60 / func_8012C750`) + the whale (`undefined reference` — its body is in `src/shared/func_80144B9C.h`, the -O0 header, so no `DEFINE` macro exists to expand). Existing tools cover both (`cast_call_sites` / `canon_sig_reconcile` / `reconcile_tu`).
  - **❌ SELF-INFLICTED #1 — I DESTROYED the registry's documentation (H5), and every gate called it green.** My first cut wrote the registry with `yaml.safe_dump`, which round-tripped the whole file: **47 comment lines → 0** (including the curated Phase-11 header explaining *why* the share is source-level) and **1,832 `vram: 0x80162FF4` → `vram: 2148937716`** (PyYAML parses YAML-1.1 hex to int, dumps int as decimal). 25,948 lines rewritten. **It passed dedup-check 1840/0 AND check-all 140/140** — because `_addr()` accepts both forms: *the data was correct and the document was ruined*. Landed in `c0486fe5f`; **fixed forward** (R6 — no history rewrite): registry restored from `c0486fe5f~1`, memberships re-applied by a **surgical text edit** (`add_members_surgical`), verified **1545 insertions / 1545 deletions, 0 non-`binaries:` lines changed, 47 comments + 1908 hex fields intact**. *The lesson is the sharpest of the phase: every oracle we own measures BYTES, so a formatting-destructive write is invisible to all of them.*
  - **❌ SELF-INFLICTED #2 — I mis-reported the DIFFs, twice (R14).** (a) I claimed ov_SC07_006's 71 non-banks were *"ALL PLUMBING, ZERO DIFF"* — from reading `head -6` of the classified file and generalizing. It has the same 4 DIFFs; the claim is **false and is in commit `c0486fe5f`**. (b) I then built a jr guard on the assumption those 4 were the §53 jr class *because ov_SC01_077 hosts them in `_jr_8017A4AC.c`* — **`has_mid_jr` is False for all four** (33-52 ins, no jump table). They merely live in a carved jr-**region** split (the carve sweeps in every fn in its address range). **Hosting file ≠ function class.** The guard is kept (preventive, §53-correct, currently skips 0) with its docstring corrected; **the 12 DIFFs (0.19%) are UNDIAGNOSED and logged** — correctly left as stubs by the gate.

- **2026-07-16 — T5 ✅ resident 21 → 14 stubs (7 banked, 90.34%). NOT 100% — honest dossier instead.**
  - **Instrument first (R35):** `progress.py` `#if 0`-blindness + the `len()`-sum fixed BEFORE the flag-plant (`2c4e2344d`) — resident 123/146 → 122/145; fleet provably unaffected. **Both oracles then agreed exactly at 144** (corpus 21+123 · sig_image 144, empty set-difference both ways).
  - **Prefetch:** MCP stopped (R23, `Save succeeded`) → one headless `DecompileFunctions` run → **21 ok / 0 fail**; MCP restarted. The wave needed **no live MCP** (it drafts from the cache — the point of the prefetch).
  - **Ultracode wave** (Drew toggled, R27 — *the toggle, not the verbal yes*): 16 isolated drafters, 0 errors, ~2.4M tokens, drafts-only into `.run/drafts-t5/` (never `src/`). **The gate arbitrated: 7/16 banked.** R22 `make clean` + extract-all + `check-all` → **140/140** (the first R22 was **killed by a terminal crash and RE-RUN**, not assumed).
  - **Result:** REAL 122 → **129**, stubs **21 → 14**, byte-ident **124/145 (85.52%) → 131/145 (90.34%)**; fleet instr **9,017,152 → 9,017,606** (+454). 14 agrees 3 ways (source grep · splat stub `.s` count · progress.py).
  - **§52b's law, independently re-measured:** agents self-reported **11 match_one MATCH** → gate banked **7 (64%)**. All 4 blocked MATCHes died on **`conflicting types`** (loose-typing def-side wall), **not codegen**; `gate_stage` recovery banked **0/5**.
  - **🔧 FIX — `match_one`'s isolation was FAKE, and its own docstring was the false spec.** It promises *"Fully isolated (own temp dir) so many run in PARALLEL"* while `--work` defaulted to the **shared** `.run/match` — every concurrent caller compiling into one `t.c`. **Found by an agent mid-wave** (the only way it can be found): it read another agent's function out of its own scratch and reported it. Every other agent steered by a loop that could hand it someone else's compile — a **confident wrong verdict**, worse than a crash. Default is now a private `.run/match/<fn>.<pid>`; the default IS the promise. The byte-gate was never at risk (sole arbiter); the agents' iteration loop was.
  - **The 14 remaining** (`docs/resident-dossier.md`, raw verdicts preserved at `.run/resident_wave_verdicts.json`, R20): **5 PLUMBING** (loose-typing, byte-correct C the TU can't hold) · **4 DIFF** (`func_800D2650` close=4 · `func_800CFAD0` close=5 · `func_800D0E30` close=12 · `func_800D27DC` close=48 — each with a named allocno/sched verdict) · **5 jtbl deferred** (§53 — the rodata-island carve; deliberately NOT forced, since forcing a jr sweep without its carve is exactly how the ≈0% doctrine was manufactured).

- **2026-07-16 — T3b ✅ the LEGACY h_seq rate: ~3% AS-TOOLED, classified, ceiling UNKNOWN.**
  - `family_sweep --hseq` over 6 legacy PURE non-jr families (smallest-nins, `has_mid_jr` excluded per §53): **9 BANKED / 37 PLUMBING / 274 DIFF** (173 skipped not-stub/pinned). **~3% (9/320).** *Unlike Phase 26, the failures are CLASSIFIED.*
  - **The DIFF is NOT structural variance (R14/R35 on my own probe):** the members are byte-level **PURE** (`classify_member` 20/20 PURE, reloc-only), **genuine h_seq** (all DIFF_BYTES vs exemplar → `family_sweep` is the *right* tool, not `dedup_extend`), at the **same vram**. A PURE family should template once relocs are remapped → the 274 failures are **recompilation divergence**: either **(a)** an incomplete `symbol_map` (the recurring jtbl/prefix bug — B2 0/8 and T4's 12 DIFFs BOTH resolved to tooling this phase) or **(b)** genuine TU-context regalloc divergence (a real wall).
  - **Honest verdict:** ~3% as-tooled, **ceiling unknown** — provisionally consistent with "legacy h_seq doesn't mechanically template" but on a probe whose dominant failure mode is the exact ambiguity that keeps resolving to *tooling*. **P29 must run the disambiguating probe** (diff one PURE DIFF member's staged bytes region-by-region: reloc-position mismatch = fixable remap; regalloc-away-from-relocs = TU wall) **before scaling "(cores)×(reach)" on 3%.** → `calibration.md`, R31.
  - 9 real banks (R22 pending). This is the roadmap's swing number, measured and classified — the single most important open input to P29, handed forward honestly rather than rush-resolved on tight context.

  - **T3 strata (honest, from the fixed map):** SC07-only **1,255 fam / 6,268 mem / 230,612 ins** · legacy PURE non-jr **95 / 7,993 / 478,379** · legacy IMM **36 / 6,644 / 212,707** · legacy MIXED **30 / 968 / 10,462** · legacy PURE w/ jr **2 / 16 / 5,088** (T1's jtbl territory — note B2's family is far smaller here than the roadmap's "×112 ≈ 106k ins"; T1 re-derives it). **Total addressable = 937,248 ins = 21.7% of all remaining weight = 7.16pp of fleet instr if it all banked.** This is the prize the roadmap declared dead. It stays a prediction until T3's gate.
</content>
