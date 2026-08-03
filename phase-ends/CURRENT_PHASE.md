# CURRENT PHASE — Phase 30: The Recovery & Concentration Campaign (overlays to their ceiling)

**Opened:** 2026-07-30 · **Effort:** Max (Fable 5; saved defaults) · **Generation:** Gen2 (22nd phase of the arc) ·
**Baseline:** PhaseEnd_Phase29 (v1.28.0) · **Roadmap:** `docs/roadmap-to-100.md` **v2** §3 P30
**Plan approved (P3 gate 1):** 2026-07-30, in-session (Drew's explicit waiver of the fresh-session step at 28% context).
Full plan mirror: `~/.claude/plans/continue-dazzling-newt.md` (out-of-repo; this file is the in-repo authority + crash-recovery log).

**Fleet at open:** 87.5% instr-weighted / 78.0% distinct-code / 92.00% fn-count · 140/140
byte-identical · 0 NON_MATCHING · dedup 1886/0 · tools-health RC=0.

**Drew's Phase-Start decisions (2026-07-30):**
- In-session start (fresh-session step waived at 28% context).
- The Ghidra-C prefetch batch pulled forward from P31 → **T0.5** (tail + main's 1,034 stubs; headless, background).
- T2's primary path = the **two-file atomic o0b substitution driver** (the log's costed no-splat route); Arm-A splat research is the fallback only.
- ROI floor for T3: two consecutive sessions each < +0.3pp instr with all lanes exercised (Drew-adjustable).

**⚠️ PRECONDITION (R6):** Drew makes the milestone-close commit + push (`PhaseEnd_Phase29.md` +
`phase-ends/logs/Phase29.md`, both in the tree) **before P30's first commit lands**. P30 work
proceeds; the first P30 commit waits on it.

---

## The numbers this phase must pin FIRST (T0 — do not consume until re-derived, R35/R14)
- family_hseq **29,961** vs progress.py **28,296** remaining instances — an unexplained R32 gap.
- The `-O0` population: "10 families / ~1,287 raw distinct" (checkpoints) vs "123 families /
  121,264 ins / 3,100 distinct" (the log's R14 correction) vs "129 distinct on the table" (the
  costed o0b route) — three numbers, one T0 job.
- The zero-crack family list (map said **61** on 07-29) and the concentration table (top-20/top-100 shares).

## Standing invariants (every task)
- Whole-binary byte-gate is the **sole arbiter** (G3/P9); match_one/closeness/masked = candidates (§52b).
- **R22 clean-fleet per banked batch:** `make clean && make extract-all && make check-all` → 140/140.
- `make tools-health` green + fail-closed before matching (corpus · cdecl · audit-binaries(R36) · report/lint/dedup).
- Blast-radius typing on every integration write (T0 draft-only / T1 binary-local / T2 fleet-shared ⇒ R22 mandatory).
- **Probe before costing** (R37-candidate discipline): probe one member before pricing a job; derive
  attribution from `corpus.stubs` before/after; diff the artifact to prove an edit ran (§120).
- Flywheel: idioms → cookbook + tooling in-session (R16/R30); pivots → decision-log (R31).
- Effort/model transitions **prompted, never assumed** (R26/R27) — STOP + WAIT for the toggle.
- One commit per task/sub-repair after this file's update; Drew pushes (R6/R20). R23 no-op on db.*.gbf churn.

---

## Task checklist (current-task pointer = ▶)

- [x] **T0 — Frontier regen + instrument repair [Max]** ✅ (all six letters; see per-task log; frontier
      report = `docs/frontier-p30.md`, report point #1):
      (a) `gate_stage.py` snapshot/restore (the ladder destroys good drafts) ·
      (b) `rtu_match.py` surface the real cc1 error in the verdict ·
      (c) reconcile the family_hseq↔progress instance gap (R32) ·
      (d) purge since-banked rows from the backlog ledger + still-a-stub filter from `corpus.stubs` (R33) ·
      (e) refresh `.run/autopsy/residuals.jsonl` + fix the 21-file absolute-include defect ·
      (f) regenerate the frontier (report / family_hseq / worklist / fuel manifest) + **pin the three
      contested populations** → the one-page frontier report (**report point #1**).
      Verify: tools-health green; digests committed; velocity derives from digest git history (R33).
- [x] **T0.5 — Fleet Ghidra-C prefetch batch [background]** ✅ (SESSION-27: 124/124 programs, 7,716
      files, 335 min unattended; 95.2% of crack-needing families seeded, main 2,001/2,002, resident
      14/14. *Was left unticked through S27 — corrected S28.*) — `ImportOverlay.java` (~130 missing
      programs) + `DecompileFunctions.java` over every remaining distinct stub (overlay tail + main's
      1,034; skip LINKED) → `.run/ghidra_c/`. **R23 lock discipline** (stop the hook-launched MCP
      server first or route through it). Verify via `build_fuel_manifest.py` counters + 5 spot-reads.
- [x] **T1 — Integration-recovery sweep** ✅ **DELIVERED as T1a (report point #2), then CLOSED both
      ways.** 108 fresh autopsy-MATCH strandeds / 50 binaries through the tiered driver → **+18
      banked** (derived: fn-count +18 / distinct +12; the commit-message sum of 19 was a gate-report
      double-list — the metric wins), R22 140/140. **The measured verdict:** the S16 "39%" prior did
      NOT generalize (it was measured on FRESH same-wave drafts); on this stored-backlog population —
      the class decision-log **A10** had already byte-proved non-bankable by plain re-gate (0/958) —
      the driver's reconcile/de-macroize lifted **18 of ~111 ≈ 16%**, a real but bounded delta. The
      ~90 that did not bank stay `match_one`-MATCH but are integration-DECAYED: they route to T3's
      REDRAFT lanes, not another recovery pass. No Ultracode was needed (the lever was deterministic).
- [x] **T2 — The `-O0` cluster [Max, deep]** ✅ **ROUTE PROVEN, TOOLED, AND SWEPT FLEET-WIDE (S28).**
      **Report point #3 = this entry.**
      DEVIATION from the phase-start plan, byte-justified — **BOTH named routes were refuted:**
      the PRIMARY "two-file atomic o0b substitution driver" mis-places by construction unless the
      target abuts the o0b object's END (the ×1 probe), and the FALLBACK premise was also wrong —
      the Arm-A splat `%lo +0x20` **does not bite** (a pure `-O2` sub-split of a jr object is
      byte-neutral, probe 1). The real constraint is **§126**: *an address range is not an
      optimization region* — it contains already-matched `-O2` bodies, so the bound is
      (range MINUS matched) and K islands ⇒ K+1 regions (probes 3–4).
      **Shipped:** `tools/o0_subsplit.py` · Makefile `-O0` glob `_o0b`→`_o0?` · cookbook §126/§126a.
      **Swept:** 135/135 overlays, 0 refusals; 140 new `-O0` region files; `o0_sources()` 137→277;
      0 invisible to the oracle; **2,200 open stubs now in a genuinely `-O0` TU**. 6 fns banked
      (ov_SC03_014/015). R22 140/140; tools-health OK.
      **Population correction (R14):** my "275 stubs / 18 overlays" was an 8× under-count from a
      bare `except` swallowing R32 during a rebuild; truth **2,184 / 138**, which **vindicates the
      T0(f) "2,192" pin** I had wrongly called stale (§126a).
      **Handoff → T3:** drafting the 2,200 is crack-wave work; seeds cached; `match_one --o0`.
- [x] **T3 — The standing crack-wave loop** ✅ **RAN across S26–S29, all four lanes exercised, with a
      measured per-lane verdict** (the ROI floor is a LANE property, not a phase property):
      · **Lane B (top-mass fresh families) PAYS and is not exhausted** — S27 waves 1–4 (8/14 · 15/19 ·
        48/48 · 69/70) + 7 confirmed behemoths at 700–970 ins; S28 the jtbl OVER-SPAN fix + the 710-ins
        `func_80191C50`; S29 the jr-pair = frontier families #3 and #4 by templatable weight, banked
        ×138 each for ~0 agent tokens after the instrument repair.
      · **Lane C (tail mass, ×2-reach cached band) is AT the floor** — S28 measured 1.33M tokens →
        12 banks → **+0.00pp headline**. That, not the phase, is what the ROI floor names.
      · Lane A (zero-crack propagation) + Lane D (PINS/W4/permuter) exercised; 29 zero-crack families
        remain as propagation-only fuel behind matched exemplars.
      *(Original text:)* — lanes interleaved,
      propagate behind every crack same-session:
      A zero-crack (~61, propagation-only) · B top-mass fresh families (no size cap; jr via
      `jtbl_family_bank`; `gate_stage` call-site-casts, never bulk header edits) · C tail mass on
      prefetched seeds (local v3 ≤15 → GLM/Haiku ≤~50 → cheap-Opus mid) · D PINS (19) + W4 bounded
      diagnoses + permuter backlog via the T4-fixed grinder.
      Per-session checkpoint + velocity + 3 metrics. **ROI floor: 2 consecutive sessions < +0.3pp
      instr each with all lanes exercised.**
- [x] **T4 — Carried-tool resolution [xHigh]** ✅ (S28, `commit:1279`). The 2 "Phase-22 grinder bugs"
      were struck as STALE in S27 (already fixed). This session: **`--fix-def-sig` posture audited
      clean** (defaults False, one consumer, no caller passes it) — and the audit found the live
      hazard the earlier pass missed: `docs/decision-log.md` still recommended making it
      **default-on**, which T84/§119 byte-refuted; struck in place with a superseding note (R31).
      **Grinder ILS warm-restart WIRED** — `permuter_ils.py` had sat unused beside `grinder.py`
      since Phase 24, so every grind was a COLD search; now `--cycles` (default 4) warm-restarts
      from the best byte-waypoint, `--cycles 1` = old behaviour. Justified by measurement before
      building (the lane looked dead: 0 banks since Phase 21) — **665 open near-misses in the
      permuter-tractable band, 157 at close 1–4, incl. `func_8016BA68` close=1 reach=134**.
      ⚠️ **Yield UNPROVEN on this backlog** — wiring only; the ILS evidence is one Phase-24 fn.
- [ ] **T6 — The measured-frontier continuation [approved by Drew 2026-08-01, in-phase re-plan
      (P5d)]** — P30 stays OPEN. Order derived from the S29 frontier regen, ranked by the family
      map's TEMPLATABLE weight (see the pricing finding below), NOT by `worklist.md`:
      **S1** zero-crack propagation sweep — 29 families / **67,470 ins**, ~0 agent tokens
        (head `0x8014032C` 183×137 = 25,071 jr · `0x8017BEBC` 12,376 · ~8 ×4-straggler families) ·
      **S2** the LAST two reach-138 fresh cracks — `func_80176734` (371×138 = **51,198**, no jr,
        cached) + `func_8016EC0C` (88×138 = 12,144) ·
      **S3** the close=0 stored drafts as a **diagnostic** pass (§132 ladder per draft), not a
        blind re-sweep (T1a's ladder measured 16%; S29 resolved 2 of 2 "gate refuses" to tooling) ·
      **S4** PINS bounded wave (14 fns / 44,279 ins; the pin-crash wall dissolved in P27) ·
      **S5** the ×10-133 mid-multiplicity families (142,527 ins).
      **Deliberately excluded:** the 2 GIANT walls (close=110/91 — P32's track), the ×2-9 mass
      (339,742 ins, worst multiplier), the singleton/non-substantial residue (635,805 ins, ×1).
      **⚠ THE PRICING FINDING (R14/R35):** `worklist.md` ranks by **h_exact** reach, so a
      per-location PURE family is priced ×1 — it under-prices the frontier head by up to **138×**.
      Byte-proof: S29's pair was priced 272 and 198 ins and delivered **37,536 + 27,324**.
      `func_80176734` sits at rank ~50 in `worklist.md` and is the single largest item on the board.
      **Rank by `.run/family_hseq.json` templatable weight for family work; the worklist is correct
      only for genuinely h_exact-reach functions.**
      **⚠ THE STRUCTURAL SIGNAL:** after S2 the **×138 era ENDS** — those are the last two crackable
      fleet-wide families; everything after is ≤133 members and mostly ≤9. That rise in
      cost-per-point, not a session count, is P30's honest ROI floor and the trigger for T5.
- [ ] **T5 — Phase close [Max]** — burn-down from digest history; P7 milestone walk; Roadmap delta
      (**including the v2 gap this analysis exposed: bucket W3's remainder has NO owner phase after
      P30 — P31 is T/M/R, P32 is walls/behemoths**); gate 2; PhaseEnd_Phase30.

**Milestone:** overlays at their measured ceiling — **≥95% instr fleet, or every remaining overlay
stub on a named wall/behemoth/queue ledger** — 140/140 byte-identical throughout.

## Blockers
- (none) — the precondition (Drew's milestone-close commit) landed at `commit:1213`.

---

# 🛑 SESSION-31 CHECKPOINT (2026-08-03) — wave 4a + S6c + wave 4b b1/b2 + reconcile + redraft
> Supersedes SESSION-30 below. Effort: **ultracode** (Drew enabled at session start; re-enabled
> after a mid-session usage-limit stop that Drew cleared). `make tools-health` **RC=0 at session
> open**. **R22 clean-fleet run FIVE times this session, 140/140 every time.** HEAD `commit:1365`.
> ⚠️ **Wave 4b BATCH 3 was in flight at this write** (37 targets, `.run/s7_wave4b_b3.js`, run
> `wf_c7555629-640`) — if the session ended mid-flight, its drafts are in `.run/s7/<ov>/` and are
> UNGATED. Gate with `.venv/bin/python .run/s6f_gate.py '.run/s7/*/func_*.c'` (it skips already-
> banked automatically), then propagate → R22 → commit. Nothing else is running.

## FLEET — R22 clean-fleet **140 passed / 0 failed of 140** (`make clean` + extract-all + check-all)
**95.77% fn-count · 92.9% instr-weighted · 86.4% distinct-code** (76,824 / 87,459 unique fns) ·
dedup **1905/0** · C1 240496/240496 · **0 NON_MATCHING** in any default build (G4).
Phase opened 92.00 / 87.5 / 78.0 ⇒ **+3.77pp fn, +5.4pp instr, +8.4pp distinct this phase.**
*(`.run/family_hseq.json`'s metrics read ~0.3–1.0pp higher — that is the OVERLAY-ONLY denominator,
not a disagreement. `make report` is the authoritative fleet number.)*

## WHAT S7 DID — ~1,238 function-instances; **103 of 107 drafts banked (96%)**
| round | heads | members | commit |
|---|---|---|---|
| wave 4a draft (33 targets, 46 agents, 4.44M tok) | 23 | 251 | `commit:1355` |
| S6c jr families (deterministic, ~0 tokens) | — | 12 | 5 per-family commits |
| wave 4a reconcile (7 PLUMBING) | 7 | 76 | `commit:1363` |
| wave 4b batch 1 (37 targets, 50 agents, 4.35M tok) | 32 | 365 | `commit:1364` |
| batch 2 + reconcile ×3 + **redraft ×4** | 41 | 431 | `commit:1365` |

**Per-lane economics, measured:** drafting banks 70–86% at ~4M tokens/wave · the **reconcile lane is
10/10 lifetime at ~13× lower cost** (329K for 7 fixes) · the **redraft lane is 4/4** · deterministic
sweeps banked 443 members for ~0 tokens. *The cheap lanes keep out-earning the expensive one.*

*(wave 4a detail, retained:)* 29 claimed `match_one` MATCH → gate **23/33 (70%)** → 251 members
across 69 overlays (13 failed, 4 STRUCT skipped by design).

**Bank rate by the tier that produced the FINAL draft** (derived per-function; the workflow's
`by_tier` counts CLAIMED matches and sums to 29, not 23 — do not read it as banks):
| tier | banked / attempted |
|---|---|
| Opus direct (≥90 ins) | 10 / 14 |
| Haiku direct (≤89 ins) | **3 / 8** |
| Opus escalation after a Haiku miss | **10 / 11** |
⇒ on the 60–120-ins band the cheap tier is **triage, not a substitute** (it is ≡ Opus only at
≤~50 ins). The two-lane shape still pays *because the escalation almost never fails.*

## S6c — the 9 jr zero-crack families: 12 banked, 6 families ledgered, ALL banks in the SC07 quartet
Probe-one-sibling-per-family first (R37) — it spared ~20 builds each on six families:
| family | ins | slots | outcome |
|---|---|---|---|
| `func_80178D40` | 890 | 4 | **4/4 BANKED** |
| `func_801734BC` | 34 | 4 | **4/4 BANKED** |
| `func_8012ACE0` | 25 | 4 | **4/4 BANKED** |
| `func_801380E0` · `func_80191C50` · `func_8019059C` · `func_8013FFD8` · `func_8016AE5C` | 438/710/673/213/85 | 10 | **gate-fail — genuine byte DIFF** |
| `func_8016AB6C` | 188 | 4 | **carve-fail** — span table starts do not fit the span |

**Every one of the 12 banks landed in `ov_SC07_006/007/010/011`** — the four overlays P27 discovered
and P28 made citizens (R36). P28 drained their **h_exact** backlog via `dedup_extend`; the **jr/h_seq
propagation lane was still owed**, and this was it. ⚠️ **But do NOT over-read that:** the SC07 quartet
are the top four overlays by remaining zero-crack residue (2,190–2,355 ins each vs 500–870 typical,
~3–4×) yet hold only **7% of the 2,114 remaining slots**. It is a per-overlay priority signal, NOT a
bulk lever — the non-jr zero-crack residue is genuinely fleet-wide (120 families / 65,946 ins).

## 🎯 THE 10 WAVE-4a GATE FAILURES ARE CAPTURED AND CLASSIFIED → `.run/s7_blockers.json`
**7 PLUMBING / 3 genuine byte-DIFF** — i.e. **70% of "the gate refused" is declaration paperwork.**
- **PLUMBING (→ reconcile lane, feed each agent its line VERBATIM):** `func_80185254`(SC02_026,
  `conflicting types for func_8012C1B8`) · `func_8018362C`(SC02_035, `func_8012B200`) ·
  `func_80183A14` + `func_80183B20`(SC02_035, both `func_80183E68` — ONE shared TU, so **forbid agent
  builds**, §135) · `func_8017E654`(SC02_041, `func_8012BF4C`) · `func_8017BF50`(SC03_001,
  `func_8012913C`) · `func_8017CDB0`(SC03_002, `func_801439C0`).
- **DIFF (→ redraft, the C is wrong, not the declarations):** `func_8017E978`(SC01_005) ·
  `func_80184494`(SC02_026) · `func_80184960`(SC04_018). *(`func_8017E978`'s original agent died on
  the session limit, so it is effectively undrafted.)*
- Tool: **`.run/s7_capture.py`** — any overlay, any draft dir (the ov_SC01_077-only
  `.run/uc_capture.py` is its ancestor); reverts the TU in a `finally:`.

## 📓 COOKBOOK §136 + §136a — the phase's largest single-wave idiom yield (R30, written in-session)
19 byte-verified idioms from 25 banked functions' `index_gap` reports. The finding:
**in the 60–120-ins band most "regalloc residuals" are decided by HOW MANY C LOCALS YOU DECLARE AND
AT WHAT SCOPE, not by register pins** — `local-alloc.c:472` refuses a local allocno with
`REG_N_DEATHS > 1`, promoting it to a global allocno that loses the low register. One case
explicitly **refutes the pin** as the lever for a redundant copy (source position is the lever).
**§136a** adds the capture law: **classify on the build's OUTPUT, never its exit status** —
`make build` runs `check`, so a draft that compiles perfectly and merely differs in bytes ALSO exits
non-zero; an `rc == 0 ⇒ DIFF` branch is unreachable and files every real byte-DIFF under "unknown"
(my own defect this session, caught and fixed). Index regenerated **364 → 371** sections, green.
⚠️ Agents self-reported `index_hit` **13 true / 18 false** — *discoverability of our own knowledge,
not the compiler, is the drafting bottleneck.* The 31 gap reports are worth more than the matches.

## ⚠️ THREE THINGS A FRESH SESSION MUST NOT INHERIT UNCHECKED
1. **The T6 ROI-floor trigger stays REFUTED** (S30's finding, re-confirmed): the ×138-era-ends
   trigger was wrong. Re-derive from a freshly regenerated `family_hseq` before any close.
2. **My S6c probe first reported 1/9 — it was 1 bank + 8 CORRECT REFUSALS, not 8 failures.**
   `jtbl_family_bank` refuses on a dirty `config/`+`src/` (its per-sibling revert restores from
   HEAD, so an uncommitted prior bank would be destroyed). My driver did not commit between
   families. **A uniform failure across N different functions is a statement about the mechanism,
   not the functions** (§134). Fixed: `.run/s7_s6c.py` now commits between families.
3. **The session hit the agent limit mid-wave** (3 agents died on it; resets 4:20am America/Denver).
   Agent capacity is NOT assumable — and the measured economics favour the deterministic lanes
   anyway (S30: sweeps ≈0 tokens for +0.5pp; wave-3 ≈4.1M for +0.3pp).

## 📊 THE LIVE QUEUE — re-derived at HEAD from the regenerated map (overlay-only ins)
| lever | families | templ ins | note |
|---|---|---|---|
| B-shape ≥20 memb, ≤60 ins | **0** | 0 | exhausted (was 36 at S30 open) |
| B-shape ≥10 memb, **61-120 ins** | **10** | **10,003** | wave 4a consumed 23 of the 33 |
| B-shape 10-19 memb, ≤60 ins | **111** | **33,554** | **wave 4b, staged in 3 batches of 37** |
| zero-crack `has_mid_jr` (S6c) | 6 | ~5,600 | **DONE** — 12 banked; the 6 left are gate/carve-fail, ledger material |
| zero-crack non-jr residue | 120 | 65,946 | fleet-wide (2,114 slots); SC07 quartet = top 4 but only 7% |
| fresh ×2-9 | 1,872 | 362,591 | worst multiplier — deprioritised |
| fresh ×1 singletons | 3,800 | 231,284 | ×1 — deprioritised |
Unmatched fleet-wide: **14,887 instances / 912,037 ins**.

## 🔑 THE FOUR FINDINGS THIS SESSION PRODUCED (cookbook §136 · §136a · §136b · §136c · §136d)
1. **§136 — the LOCAL-VARIABLE lever.** In the 60–120-ins band most "regalloc residuals" are decided
   by **how many C locals you declare and at what scope**, not by register pins (`local-alloc.c:472`
   promotes any pseudo with `REG_N_DEATHS > 1` to a global allocno, which loses the low register).
   One case explicitly REFUTES the pin as the lever for a redundant copy.
2. **§136b — a "genuine byte-DIFF" verdict is a fact about ONE DRAFT, closed at 8/8.** Every
   DIFF-ledgered function banked on redraft: wave 3's four, the **three I classified myself**, and
   one from batch 1. **Never retire a target on a DIFF verdict; route it to REDRAFT.** And
   re-GATING an unchanged draft is not a retry (that is why wave 4a's 3 DIFFs survived one gate).
3. **§136a CORRECTED, by an agent, against the bytes.** I wrote "70% of gate refusals are paperwork,
   not codegen." **Wrong** — a declaration conflict ABORTS the compile, so a PLUMBING verdict says
   NOTHING about the body. 2 of 3 second-round PLUMBING drafts had a real codegen residual behind
   the conflict. Also: classify on the build's OUTPUT, never its exit status (`make build` runs
   `check`, so a clean-compiling byte-DIFF also exits non-zero).
4. **§136c — SIBLING-FIRST is a DERIVATION shortcut**, not just a conflict fix. Search order:
   `engine_core.h DEFINE_* near-twin` → same-TU banked sibling → the `.s` → **the Ghidra seed LAST**
   (byte-proven an entirely different body twice this session). Produced first-draft matches.
   §136d adds four new levers, each with its **refuted axis** recorded.

## ▶ RESUME HERE
1. **Gate batch 3** if it was in flight (see the header) → propagate → R22 → commit.
2. **The 4 remaining stubs of 107**: `func_8017C120`(SC02_026 — classified **UNKNOWN**, neither a
   compiler error nor a SHA mismatch; **owes a direct look at its build output**, not a guess) ·
   `func_8017CD9C`(SC04_003) · `func_801848DC` + `func_80185904`(SC04_018). Capture then route —
   **and per §136b none of these is a wall on one attempt.**
3. **The wave-4b remainder**: batch 3 was the last of the 111-family volume lane. After it, the
   B-shape lanes are spent — re-derive the queue from a freshly regenerated `family_hseq` before
   scoping anything new (the ×138 era already ended; the next tiers are ×10-99 and the zero-crack
   non-jr residue at 120 families / 65,946 ins).
4. **T5 close** — only after re-deriving; the checklist's ROI-floor trigger is REFUTED and must not
   be used to close the phase.

---

# 🛑 (superseded) SESSION-30 CHECKPOINT (2026-08-01, S6 complete through wave 3)
> **Nothing is running. Tree lock FREE. Tree CLEAN** (0 non-ghidra entries; the `db.*.gbf` churn is
> R23 restart-noise — never stage). **HEAD `commit:1352`.** Effort: xHigh → **ultracode** (Drew enabled
> mid-session for the waves). `make tools-health` green at session open; frontier REGENERATED at HEAD
> after the last bank, so every number below is current (not carried forward).

## FLEET — R22 clean-fleet **140 passed / 0 failed** (run 9× this session, 140/140 every time)
**95.42% fn-count · 92.4% instr-weighted · 85.5% distinct-code** (75,926 unique fns) · dedup 1905/0 ·
0 NON_MATCHING. Phase opened 92.00 / 87.5 / 78.0 ⇒ **+3.42pp fn, +4.9pp instr, +7.5pp distinct.**

## WHAT S6 DID — ~3,500 member-matches in 11 commits
`commit:1343` S6a 842 · `commit:1344` S6b +740 · `commit:1345` S6e fix · `commit:1346` B +268 ·
`commit:1347` S6f calib +65 · `commit:1348` S6f wave-1 +544 · `commit:1349` S6g wave-2 +342 ·
`commit:1351` S6h wave-3 +673 · `commit:1352` cookbook §135 (+ 2 checkpoint/doc commits).

**Two distinct engines ran, and BOTH paid:**
1. **Tooling repair (deterministic, ~0 agent tokens).** The pre-fix tools scored the zero-crack
   population at 842 members; with three scanner fixes the SAME population scored 1,582. Six defects
   found, five fixed — all one root cause: **a multi-line C construct read one line at a time**, or a
   guard firing on a condition it never verified. → **cookbook §134**.
2. **Agent waves (two-lane: cheap drafts + Opus reconciles).** Bank rate **83% → 93% → 89%**;
   the **reconcile lane is 12/12**. → **cookbook §135** (6 codegen idioms + 4 integration rules).

## ⚠️ TWO THINGS A FRESH SESSION MUST NOT INHERIT UNCHECKED
1. **The T6 ROI-floor trigger is REFUTED. Do not close P30 on it.** The checklist says T5 fires when
   "the ×138 era ENDS after S2". That was wrong twice today: two ≥126-member families were open
   (33 ins of C → 266 members), and a 36-family / 28,829-ins pool of the same shape sat unexamined
   behind them. **Three §133-class misses now share one mechanism — a conclusion drawn from a view
   that silently excluded the thing being looked for.** Re-derive from a freshly regenerated
   `family_hseq` before any close.
2. **Token economics, measured today (re-check before scaling wave 4):** deterministic sweeps ≈ **0
   tokens for +0.5pp instr**; wave-1 ≈ 2.0M for +0.1pp; wave-3 ≈ 4.1M for +0.3pp. The agent lane is
   still paying, but the **tooling lane paid better** — the same finding Phase 15 recorded. Probe the
   cheap lever before funding the expensive one.

## 📊 THE LIVE QUEUE — re-derived at HEAD after the final bank
| lever | families | templ ins | note |
|---|---|---|---|
| B-shape ≥20 memb, ≤60 ins | **0** | 0 | **EXHAUSTED** (was 36 / 28,829) |
| B-shape ≥10 memb, **61-120 ins** | **33** | **34,895** | best per-target value; Opus ≥90 ins |
| B-shape 10-19 memb, ≤60 ins | **111** | **33,554** | volume lane, Haiku |
| zero-crack non-jr residue | 116 | 61,230 | S6-diagnosed; bimodal residue |
| zero-crack `has_mid_jr` (**S6c, untouched**) | 9 | 9,364 | needs `jtbl_family_bank`, 26 slots, ~0 tokens |
| fresh ×2-9 | 1,877 | 363,873 | worst multiplier — deprioritised |
| fresh ×1 singletons | 3,642 | 207,945 | ×1 — deprioritised |
Unmatched fleet-wide: **15,161 instances / 935,927 ins**.

## 🔁 THE WAVE RECIPE (cookbook §135 has the full version)
Manifest **derived** from `corpus.stubs` + `family_hseq`, paths verified on disk, **pasted from the
file — never typed** (a hand-transcribed list cost wave 1 three agents' time). Draft lane: Haiku ≤89
ins (≡ Opus at ≤~50, ~4.8× cheaper), Opus direct ≥90, Opus escalation between. Then: gate whole-binary
via `.run/s6f_gate.py '<glob>'` (derives every TU/split; agents' `match_one` MATCH is NOT a bank) →
**capture each failure's compiler error** → Opus reconcile lane → gate → `family_sweep --hseq
--band all --only <addrs>` → R22 → commit. **If N reconcile targets share ONE TU, forbid agent builds.**

## ▶ RESUME HERE
1. **Wave 4** over the two B-shape slices (144 families / 68,449 ins) — recipe above, §135 in prompt.
2. **S6c** — the 9 jr zero-crack families (9,364 ins, ~0 agent tokens) via `jtbl_family_bank`,
   probing ONE sibling first (the S29 discipline: 1 build, not 137).
3. **The 4 carried failures:** `func_80184A94` (reconciled to `match_one` MATCH, still gate-refused)
   + 3 genuine byte-DIFFs `func_801845B0`, `func_8017BEBC`@ov_SC02_026, `func_8018480C`.
4. **T5 close** — only after re-deriving; see the refuted trigger above.

---

# 🛑 (superseded) SESSION-29 CHECKPOINT (2026-08-01, refreshed ~11:2x)
> Supersedes the earlier S29 block below (which said "AT GATE 2"; Drew then directed **P30 stays
> OPEN** and approved the T6 continuation). **Nothing is running. Tree lock FREE. Tree clean** but
> for the R23 `db.*.gbf` churn (never stage). **HEAD `commit:1335`.** Effort: Max → **xHigh** (Drew).

## FLEET — R22 clean-fleet **140 passed / 0 failed** (run 7× this session, 140/140 every time)
**94.43% fn-count · 91.4% instr-weighted · 84.0% distinct-code** (73,787 unique fns) · dedup 1905/0 ·
0 NON_MATCHING. Phase opened 92.00 / 87.5 / 78.0 ⇒ **+2.43pp fn, +3.9pp instr, +6.0pp distinct.**
Session start (S28 close) was 93.25 / 89.2 / 80.5 ⇒ **+1.18 / +2.2 / +3.5pp today.**

## THE UC WAVES (Drew opted in mid-session) — 33 heads banked, ~3,560 members propagated
- **Wave 1** (14 agents, 2 lanes): 14/14 `match_one` MATCH → **8 heads banked** by three mechanisms
  (plain gate · a NEW targeted decl reconcile that edits ONLY the line the compiler names · the
  `gate_stage` ladder) → **1,370 members** propagated, 0 failed.
- **Wave 2 + 3** (19 + 11 agents): **19/19 heads banked** — the best conversion of the phase →
  **2,192 members** / 411 stage-but-DIFF residue.
- **THE RECONCILE LANE IS THE RESULT WORTH KEEPING.** 17 of 19 wave-2 heads needed a declaration fix
  and **not one needed a header edit**. Two escapes did all of it: the **§37/§124 asm-label alias**
  (`<ret> aF<ADDR>(...) __asm__("func_<ADDR>")`) when the conflict is on the function ITSELF
  (return-type or arity), and **conform-the-decl + cast-at-use** when it is on a DIFFERENT symbol the
  draft declares (`func_80142A80`, `RotTransSV`, `func_80146C3C`, `D_8011D030`, `D_800AF634`).
  This is the direct answer to the morning's failure: the documented fix for that class was a
  fleet-wide decl widen, which touched **2,046 files and still did not build**. The alias sidesteps
  the collision at ZERO blast radius.
- **Agents cannot run the gate**, so a blocker-capture pass (splice→build→revert) had to precede each
  reconcile fan-out and embed the exact compiler error per agent. Without it they are blind on the one
  axis that matters. *(R14 on my own capture: the `note:` lines I passed through were pre-existing SHB
  macro-redefinition NOISE — four agents independently called it and worked the real error.)*

## WHAT S29 DID
1. **`JR-PAIR-IN-ONE-O0-OBJECT` RETIRED** — two instrument defects (§132), not a compiler wall:
   `jtbl_carve` blind to a merged-double span + no `.DELETE_ON_ERROR` (a truncated `.o` outlived its
   own loud compile error and the NEXT build linked it). Pair banked ×138 = 276 instances.
2. **S1 zero-crack tier — 186 members** (head `func_8014032C` 137/137 = 25,071 ins via the new
   `--span-rel`, §132b; `func_8017BEBC` 13/13; + jr tier). My routing error recorded: 13 of 28
   families are not jr and carve-failed by construction (§123's own law).
3. **S2 — both remaining reach-138 heads cracked.** `func_8016EC0C` (void-return delay-slot idiom)
   ×138; **`func_80176734` (371 ins — the largest single item in the frontier) banked first try** and
   propagated. TWO agents reached byte-identical solutions independently via different lever sets.
4. **S3 measured, not scaled** — 77% of stored drafts have DECAYED (7/30 still verify); the survivors
   are def-side-walled. A fleet `sed` over decls touched 2,046 files and failed ⇒ reverted (§29 law).
5. **UC wave 1 (14 agents): 14/14 match_one MATCH → 8 banked heads** by three different mechanisms
   (plain gate · a NEW targeted decl reconcile that edits only the line the compiler names · the
   `gate_stage` ladder). **1,370 member instances propagated, 0 failed.**
6. **Cookbook §132 · §132a · §133** (the DEFAULT-FILTER class — three times in one session a tool
   silently answered a narrower question than the one asked).

## 📊 THE POST-WAVE FRONTIER (re-derived at HEAD after the 2,192-member propagation — R35)
Overlays: **94.7% fn / 91.8% instr / 85.0% distinct**; unmatched **18,635 instances / 1,069,466 ins /
13,658 distinct classes** → 2,378 families + 3,767 singletons.

| lever | scale | cost | verdict |
|---|---|---|---|
| **Zero-crack propagation (source-agnostic)** | **190 families / 129,997 ins** | **~0 agent tokens** | **DO FIRST (S6)** |
| ×10-99 fresh-crack band | 243 families / 239,058 ins | agent waves | next (S5) |
| STRUCT class (ov077 surface) | 29 fns / 39,892 ins | agent waves | after S5 |
| GIANT | 4 fns / 100,188 ins | 2 are the known walls (close=110/91) | P32's track |
| ×2-9 fresh-crack | 1,941 families / 410,671 ins | biggest mass, worst multiplier | deprioritised |
| ×1 singletons | 3,767 / 230,367 ins | ×1 | deprioritised |
| ~~S4 PINS~~ | **101 ins** (not 44,279) | — | **RETIRED, see below** |

**TWO PRICING CORRECTIONS (both §133, in OPPOSITE directions — this is why the table is re-derived):**
1. **S4 PINS is retired on measurement.** The plan priced it at **44,279 ins** from `worklist.md`,
   which prices by **h_exact reach** (×138/fn). Re-priced against the family map after the waves, the
   PINS functions' families are almost all already matched/propagated: **24 fns / 101 templatable ins**.
   Running the planned wave would have bought ~0.001pp. The same mis-pricing that once *under*-valued
   the frontier head by 138× *over*-valued this by ~440×.
2. **106 of the 190 zero-crack families have exemplars OUTSIDE `ov_SC01_077`** (ov_SC03_014 17,
   ov_SC06_018 10, ov_SC01_084 9, ov_SC02_027 7, ov_SC02_011 7, …). **Every sweep this project has run
   passed `--source ov_SC01_077`**, so those families were structurally unreachable — not hard, not
   walled, just never addressed. Probe-confirmed: `func_8012B77C` is DEFINED in ov_SC07_006 and still
   an `INCLUDE_ASM` stub in ov_SC01_000.

## ▶ RESUME HERE (T6: S1–S3 done, both UC waves done; nothing blocked, nothing running)
- **The ×138 redraft band is now CONSUMED.** All 33 fresh-crack ≥100-member families are banked
  except the 2 GIANT walls (`func_801412A8` close=110, `func_80178004` close=91 — P32's track).
- **S6 (NEW, highest ROI): source-agnostic zero-crack propagation** — 190 families / 129,997 ins,
  ~0 agent tokens. Drive each family from ITS OWN exemplar overlay, not always ov_SC01_077; route by
  tier (§123) and pass **`--band all`** (the S1 trap). Probe one sibling per family first.
- **S5: the ×10-99 band** — 243 families / 239,058 ins, the proven 3-lane workflow. Expect the ROI
  floor here: the multiplier is 10-99, not 138.
- ~~S4 PINS~~ **RETIRED on measurement** (101 ins, not 44,279 — see the pricing corrections above).
- **The 411 stage-but-DIFF propagation residue** — per-overlay variants whose remapped bodies do not
  reproduce; individually gate-rejected, ledger material not a lever.
- **Reusable machinery from today** (all committed): the 3-lane workflow scripts under
  `.claude/…/workflows/scripts/p30-uc-wave{1,2,3}-*.js` · `.run/uc_capture.py` (blocker capture, the
  precondition for any reconcile fan-out) · `.run/uc_reconcile.py` (compiler-named decl edits only) ·
  `tools/jtbl_family_bank.py --span-rel` (§132b) and its `like_arg` guard (§132a).
- **T5 close** fires on the measured ROI floor. The ×138 lever is spent; S4/S5 are the remaining
  in-phase levers, and their multiplier is materially lower — that is the honest floor signal.

---

# 🛑 (superseded) SESSION-29 CHECKPOINT (2026-08-01 ~00:40) — AT GATE 2
> Supersedes SESSION-28 below. **Nothing is running. Tree lock FREE. Tree clean** but for the R23
> `db.*.gbf` churn (never stage). **HEAD `commit:1303`.** Effort: **Max** all session.
> `make tools-health` **RC=0** at close; **R22 clean-fleet run TWICE this session, 140/140 both times.**

## FLEET — R22 clean-fleet **140 passed / 0 failed**
**93.33% fn-count · 89.6% instr-weighted · 81.6% distinct-code** (72,416 unique fns) · dedup 1905/0 ·
C1 240496/240496 · 0 NON_MATCHING. Overlays-only: 93.6% fn / **90.1% instr** / 82.5% distinct.
Phase opened 92.00 / 87.5 / 78.0 ⇒ **+1.33pp fn-count, +2.1pp instr, +3.6pp distinct this phase.**

## WHAT S29 DID (all committed, all R22-verified)
1. **`JR-PAIR-IN-ONE-O0-OBJECT` RETIRED** — the S28 class and its §81-isolate escape are BOTH refuted.
   Two instrument defects: `jtbl_carve`'s merged-double blindness + no `.DELETE_ON_ERROR` (a truncated
   `.o` outliving its own loud compile error). Both fixed; cookbook **§132**.
2. **The jr pair banked ×138 each — 276 function-instances.** Frontier families **#3 and #4** by
   templatable weight (37,536 + 27,324 ins). The `-O0` cluster is now COMPLETE fleet-wide.
3. **§132a** — the `--like` role-name over-transfer (`ov_SC07_010`), guard shipped.
4. **§100 type-locality** — a file-scope typedef in a draft is an *exemplar-only bank*: it passes the
   gate and silently cannot travel. Caught by probing ONE sibling before 137 builds (R37).
5. **T1/T3 closed with measured per-lane verdicts** (see the checklist), tools-health + fresh frontier.

## ▶ RESUME HERE — **P30 STAYS OPEN; T6 approved (Drew, 2026-08-01)**
Gate 2 was reached and **deliberately not taken**: the ≥95% branch is out of reach (89.6%) and the
ledger branch IS met, but closing now would strand roadmap-v2 bucket **W3** (the overlay family mass)
with **no owner phase** — P31 is scope-complete/main/resident, P32 is walls/behemoths. So P30
continues on the **T6** order in the checklist above (S1 → S2 → S3 → S4 → S5), and T5 fires on the
measured ROI floor (the end of the ×138 era after S2), not on a session count.

**Start here:** S1's head — `0x8014032C` (183 ins ×137, jr, per-location, exemplar matched in
ov_SC01_077) via `jtbl_family_bank`, **probing ONE sibling first** (the S29 discipline: 1 build
instead of 137). Then `0x8017BEBC`, then the ×4-straggler families.
Frontier data: `.run/family_hseq.json` (regenerated at HEAD `commit:1303`, same-tree as the digests).

---

# 🛑 (superseded) SESSION-28 CHECKPOINT (2026-07-31 08:1x)
> Supersedes SESSION-27 below. **Nothing is running. Tree lock FREE. Tree clean** but for the R23
> `db.*.gbf` churn (never stage). **HEAD `commit:1293`** (+ this doc commit).
> Effort: opened **xHigh** → **Max** for the jr re-measurement and the T2 probe ladder → back to
> **xHigh** for the driver + sweep. `make tools-health` RC=0 at session open.
> **R22 clean-fleet run THIRTEEN times this session, 140/140 every time** (one 139/140 and one
> 137-file false-pass, both MINE, both caught and reverted — see the honesty ledger).

## FLEET — R22 clean-fleet **140 passed / 0 failed** (verified THIRTEEN times this session)
**93.25% fn-count · 89.2% instr-weighted · 80.5% distinct-code** (72,154 / 87,459 unique fns) ·
dedup 1905/0 · C1 240496/240496 · 0 NON_MATCHING. Phase opened 92.00 / 87.5 / 78.0
⇒ **+1.25pp fn-count, +1.7pp instr, +2.5pp distinct this phase.**

## 🎯 THE THREE REACH-138 TARGETS + THE SWEEP RESIDUE — 270 members banked, 1 wall
**✅ `func_8013C08C` 0/137 → 137/137** (`commit:1286`) — §94 type-carry; `E_13C08C` was a MULTI-LINE
typedef at FILE scope and `extract_unit`'s backscan cannot carry one (it presents its CLOSING line
first). Fix = §100 draft-local. Byte-neutral.
**✅ `0x8013BC7C` 133/133** (`commit:1291`) — the sweep residue. My hypothesis (split tracks the `-O0`
file) was REFUTED (SC07_006/007/011 were sub-split today and banked anyway), so I staged one member
and READ the error: (1) a typedef textually identical to `engine_types.h`'s, which C89 still rejects
— already handled by `harvest_verify`'s `cdecl.strip_provided_typedefs`; (2) §57 self-decl divergence
⇒ **`--normalize-self-decls`**. One flag, 133/133.
**⛔ `func_8013B83C` + `func_8013BD74` — NOT BANKED, class `JR-PAIR-IN-ONE-O0-OBJECT`.** Both bodies
byte-correct (`--o0` MATCH, 272/198 ins). Two jr fns sharing one `-O0` object: carving both gives a
valid span (pads `[0,4,4]`) and an INCREMENTAL build says BYTE-IDENTICAL, but the CLEAN build **cannot
link** — `undefined reference to $L105` (local label from the C-emitted jtbl) + `undefined reference
to func_8013C938` (a previously-MATCHED fn). **Untested escape: §81 step 1 — isolate one into its own
code subseg so each object owns exactly one table.** Drafts preserved at `.run/s28w/`.

## ▶ RESUME HERE — FRESH SESSION SAFE. Nothing running, tree clean, lock FREE.
**Drew's directive at the S28 close:** items 1–3 done; **item 6 wants Max** (prompted, not started);
**items 4–5 are for a FRESH SESSION** (this checkpoint is that handoff).

1. **[T1, Ultracode] Integration-recovery sweep** — the ~90 stored drafts that are `match_one`-MATCH
   but integration-decayed, + the 10 named SESSION-16 blockers. Prior measured recovery 39%.
   **Report point #2.** Prompt for `/effort ultracode` and WAIT (R26/R27).
2. **[T3, Ultracode] More crack waves** — 3,873 fresh cached cores across 119 binaries
   (`.run/p30w4_pool.json`). ⚠️ **S28 ROI evidence: a 15-target wave cost 1.33M tokens for 12 banks
   and +0.00pp headline.** Only worth resuming against HIGH-REACH targets; ×2-reach drafting is not
   where the leverage is. Deal ACROSS binaries so the gate fans out.
3. ~~**[Max] #9 — `jtbl_carve` diverges on ov_SC06_018**~~ ✅ **SOLVED + BANKED (S28, `commit:1293`).**
   Root cause: a jtbl **OVER-SPAN**. `sltiu 0xC` names 12 entries, the object emits 12 words, the carve
   reserved 13 — the 13th being ordinary NON-ZERO data spimdisasm ran into the dlabel, which the
   zero-word trim cannot see. The piece under-filled ⇒ every later symbol slid −4 ⇒ 812 `%lo`
   immediates changed. Fixed with an `sltiu`-authorized clamp (refuses loudly if a surplus word looks
   like a real entry). **`func_80191C50` (710 ins) BANKED**, R22 140/140. Cookbook **§131**.
   ⇒ the `JTBL-CARVE-BREAKS-BYTES` class is RETIRED — it was a real bug, now fixed.
4. ~~**[Max, xHigh-able] `JR-PAIR-IN-ONE-O0-OBJECT`** — try §81 step 1~~ ✅ **SOLVED + BANKED (S29).**
   The class is RETIRED and the §81-isolate escape was never needed: it was TWO instrument defects
   (a merged-double span `jtbl_carve` could not see + no `.DELETE_ON_ERROR`, so a truncated `.o`
   survived its own loud compile error and the NEXT build linked it). Both fns banked, R22 140/140.
   Cookbook **§132**. Sibling sweep (2 × 137) unblocked — see the S29 log entry.
5. **[T5, Max] Phase close.** ⚠️ **Milestone reality: 89.2% instr vs a ≥95% bar.** The remaining
   overlay volume is small; the bulk is main's 1,034 stubs + the 39 type-1 modules, both **P31 scope**.
   P30 realistically closes on the milestone's **ledger branch** ("every remaining overlay stub on a
   named wall/behemoth/queue ledger"), which is an explicit either/or in the approved milestone —
   **Drew's call, to be made deliberately at T5, not discovered.**

## ⚠️ S28 HONESTY LEDGER (read before trusting any S28 conclusion)
Five wrong calls, every one caught by an oracle, none committed:
1. **Two of three jr "wall" verdicts RETRACTED** — a grep-of-the-build-log gate in a driver with no
   revert-on-abort contaminated its own measurements (§125).
2. **An 8× population under-count** (275 vs 2,184) — a bare `except: continue` swallowed R32's
   coverage assertion during a rebuild; it also made me wrongly call a good T0 pin "stale" (§126a).
3. **"15 contiguous -O0 fns"** — an under-count from scanning `asm/**/*.s`, which cannot see matched
   functions (§126).
4. **Broke the fleet gate to 139/140** — a negative control that corrupted the REAL tracked file and
   restored it with tangled escaping (§128a). *A negative control must mutate a scratch copy.*
5. **Reported "BOTH BANKED — BYTE-IDENTICAL" from an INCREMENTAL build** that the clean build cannot
   even LINK (§130). **The sharpest lesson of the session: an incremental byte-gate result can be
   actively FALSE, in the most convincing direction.**
Standing consequence: **only `make clean && make extract-all && make check-all` counts**, and a
tool's exit status is never the oracle — read the output.

## 📌 THE 4th `-O0` REGION — verified, sized, and correctly BLOCKED (do not re-litigate)
My own byte scan (not the agent's claim — R14/R37) over all 156 fns of `ov_SC03_014_jr_8017EB7C`:
the `-O0` frame-pointer prologue covers **exactly** the contiguous run `0x80183CF0..0x80184868`
(15 fns), with `-O2` neighbours `0x80183A54` below and `0x80184920` above — a clean cut.
**Prize: 30 fn-instances / 1,504 ins** — the region is h_exact-identical in **ov_SC03_014 +
ov_SC03_015 ONLY**; the 3 other overlays holding a `func_801846E4` (SC03_090, SC04_005, SC05_018)
are DIFFERENT code at the same VA (overlays share VAs — the §-index warning, live).
**Blocked structurally:** all 15 live in an `-O2` split (`corpus.o0_sources` confirms), and the
append-to-`_o0b` route fails BY CONSTRUCTION (the existing `_o0b` covers the whale at file
`0x1CA44..0x1D64C`; this region is far above it, so appended bytes land at the wrong VA — the same
reasoning that killed the T2 ×1 append probe). ⇒ needs the re-carve; it IS T2.

## ⚠️ TWO CORRECTIONS TO THE SESSION-27 CHECKPOINT (mine, R14)
1. **The 137 were SKIPS, not failures.** S27 folded them into the 401 gate-failures;
   `137+22+10 = 169 ≠ 401`. They are a separate `skipped{}` bucket.
2. **The cause was NOT "the exemplar banked in a different binary."** It is banked in
   `ov_SC01_077` under the §37/§73 **asm-label alias** (`int aF8016191C(...) __asm__("func_8016191C")`),
   and `extract_unit` only matched a head literally named `func_<ADDR>`. One exemplar × 137
   same-address members — a tool lookup miss, the 4th consecutive "structural" residual to resolve
   to our own tooling (R35). Fixed T0-only; the alternative (widen `engine_core.h`, drop the alias)
   was REJECTED — it fixes only §73's RETURN axis while the decl/body also disagree on PARAMS, and
   it is a T2 fleet-shared edit. §124.

## 🧪 A METHOD NOTE WORTH KEEPING (cost me one probe this session)
I ran a `corpus.stubs` probe **while `make extract-all` was mid-flight** and got 4 binaries' worth of
garbage. `corpus.py`'s R32 coverage assertion caught it and refused to answer instead of returning a
wrong stub set — the assertion earning its keep. *A measurement taken during a rebuild is not a
measurement* (SESSION-27's law, re-earned). Re-derive after the campaign exits.

---

# 🛑 (superseded) SESSION-27 CHECKPOINT (2026-07-31 01:25)
> Supersedes SESSION-26 below. **Nothing is running. Tree lock FREE. Tree clean** but for the R23
> `db.*.gbf` churn (never stage). **HEAD `commit:1258`.**

## FLEET — R22 clean-fleet **140 passed / 0 failed** (verified at HEAD)
**92.67% fn-count · 88.3% instr-weighted · 78.7% distinct-code** (70,590 / 87,459 unique fns).
Phase opened at 87.5 / 78.0 / 92.00 → **+0.8pp instr, +0.7pp distinct, +0.67pp fn-count** so far.

## WHAT LANDED THIS SESSION (all committed, all R22-verified)
- **T0 instrument repair (a–f)**, 6 commits — incl. `gate_stage` stage-0 (§122) and the
  `fix_arity_callers` per-edit journal undo.
- **T0.5 fleet Ghidra-C prefetch COMPLETE** — 124/124 programs, **7,716 files**, 335 min unattended.
  **95.2% of the 6,070 crack-needing families are seeded; main 2,001/2,002; resident 14/14.**
- **T3 waves 1–4 + behemoths:** wave1 8/14 · wave2 15/19 · wave3 **48/48** · wave4 **69/70 banked**
  (70/70 drafted) · **7 behemoths CONFIRMED** at 700–970 ins (4 banked; 3 jr deferred).
- **Propagation:** 548 + 911 members via `family_sweep --hseq`; h_exact leg 14 propagated / 42
  benign skips / 0 failures.
- **New instruments:** `tools/treelock.sh` · `tools/prefetch_fleet.py` · `tools/cookbook_index.py`
  + **`docs/cookbook-index.md` (324 sections, symptom-keyed, in `tools-health`)**.
- **Cookbook §122, §123.**

## ▶ RESUME HERE (nothing blocked, nothing in flight)
1. **`func_801846E4`** (ov_SC03_014) — the 1 of 10 resumed drafts that did NOT bank (agent reported
   MATCH; gate refused). Draft at `.run/drafts-p30w4/ov_SC03_014/func_801846E4.c`. Its agent flagged
   it as the **-O0** class (SIZE-MISMATCH/short + frame-pointer prologue) — likely needs `--o0`.
2. **The 137 "no matched unit for func"** sweep-routing gap — `family_sweep` looks for the exemplar's
   banked unit in the wrong binary. Cheap, worth ~137 members.
3. **3 jr behemoths** (`func_80191C50`, `func_8018057C`, `func_80181CDC`; staged in
   `.run/beh-gate/<binary>/`) **+ group B's carve** (13-member IMM/jr @952, 103 already matched →
   `jtbl_family_bank.py`). **Both run `make extract` — run ALONE under `tools/treelock.sh`.**
4. **T2 `-O0` carve-within-a-carve** (13 families / 1,746 members). Newly cheaper: wave-4 agents
   documented the `match_one --o0` flag AND found a **4th -O0 region** beyond the 3 known ones.
5. **Next wave:** 3,873 fresh cached cores across 119 binaries remain (`.run/p30w4_pool.json`);
   deal them ACROSS binaries so the gate fans out.

## 🔁 THE LOOP THAT WORKS (proven 4 waves running)
draft (agents, `.run/` only) → **`--no-propagate` gate, per-binary IN PARALLEL** → sig+map regen →
**propagate per-function, routed by tier (§123)** → **one R22** → commit. Wrap every tree-writing
campaign in `tools/treelock.sh`.

## ⚠️ THE THREE LAWS THIS SESSION COST US (all mine, all now mechanised)
1. **Guard the CAMPAIGN, not the process** — a `pgrep` poll cannot see a campaign made of sequential
   processes; mine started in a gap → 63/140 broke. → `treelock.sh`.
2. **A killed process performs no undo** — a fixed 3600s propagation timeout killed the driver
   mid-fleet-write. → timeout scales with bank count AND is caught.
3. **A measurement taken during corruption is not a measurement** — I reported a "per-binary bank-rate
   cliff" and theorised a cause; re-gated clean it was 6/6 everywhere.
*Both incidents cost build cycles and ZERO work, because agents only ever write `.run/`.*

## 📊 THE MEASURED FINDING WORTH KEEPING
Bank rate by wave: **57% (no index) → 79% → 100% → 99%** (index-first). Same models, same gate. The
bottleneck was **discoverability of our own knowledge**, not the compiler. Agents also self-report
`index_hit`/`index_gap`, and their gap reports are now curated symptom lines — the flywheel is
closing on itself.

---

# 🛑 (superseded) SESSION-26 CHECKPOINT (2026-07-30 23:05)
> Supersedes the in-flight block below. Paused for the 5h usage limit; **a one-shot cron is set for
> 00:47 (2026-07-31)** to resume — but cron is SESSION-ONLY and dies with this session, so if the
> session ended, just follow "RESUME HERE" manually.

**HEAD `commit:1254`.** Fleet at last verified point: **92.59% fn-count · 88.2% instr · 78.7%
distinct · R22 140/140** (commit `commit:1252`).

## ⏳ RUNNING AT PAUSE (check these FIRST)
- **`w4-gate`** under `tools/treelock.sh` (pid at pause 1313761): gating wave-4's **68 drafts across
  14 binaries** in parallel, then sig+map regen, then R22. Log: `.run/w4gate_run.log` +
  `.run/w4gate/<binary>.log`. If it did not finish: `tools/treelock.sh w4-gate bash .run/p30w4_gate.sh`.
  **Nothing from it is committed yet** — commit only after R22 shows 140/140.
- Tree carries **Lane A's 15 banks** (sweep finished: 15 banked / 712 failed / 910 already-not-stub —
  the population was largely consumed by the earlier sweep, so Lane A is now nearly spent).

## ▶ RESUME HERE (in order)
1. Finish/verify the w4-gate → R22 140/140 → commit.
2. **RESUME THE 12 UNFINISHED AGENTS** (`.run/p30w4_remaining.json`) — Drew's explicit instruction,
   cron `799f00d8` set for **00:49 on 2026-07-31**. Wave 4 launched 70, **58 returned (ALL 58
   match_one MATCH)**, 12 were killed mid-run:
   `func_8017EA1C`(SC02_041) · `func_8018A150`(SC02_027) · `func_80185680`(SC02_017) ·
   `func_8017D900`,`func_801846E4`(SC03_014) · `func_80187940`,`func_80185B5C`,`func_801885C0`(SC04_011) ·
   `func_801832D4`,`func_80183CBC`,`func_80183258`,`func_8017D7A4`(SC02_035).
   Workflow scriptPath
   `/tmp/claude-1000/-home-musashi-bfm-decomp/f1a9b030-5924-4b17-b102-3de2ca684a6f/scratchpad/p30w4.js`,
   args = the 12 targets **as an ARRAY** (a JSON string breaks `pipeline()`).
   ⚠️ 10 of the 12 have a **PARTIAL draft** on disk from the killed run — a starting point, NOT a
   verified result; re-verify with `match_one` before any MATCH claim.
   *(Counting note, R14: my first count said "2 remaining" because I measured draft-FILE existence.
   An agent writes its draft early and then iterates, so a file proves nothing about completion —
   the journal's `result` records are the truth. Drew's "12" was right and my measure was wrong.)*
3. The **h_exact propagation leg** that halted at `0x801466F0` (rc=1, stopped by design).
4. The **137 "no matched unit for func"** sweep-routing gap — the exemplar banked in a DIFFERENT
   binary than `family_sweep` looks in. Likely cheap and worth ~137 members.
5. **3 jr behemoths** (`func_80191C50`, `func_8018057C`, `func_80181CDC`, staged in
   `.run/beh-gate/<binary>/`) + **group B's carve** (13-member IMM/jr family @952, 103 already
   matched → `jtbl_family_bank`). Both run `make extract` — run them ALONE under the lock.
6. **T2's `-O0` carve-within-a-carve** (13 families / 1,746 members walled) — the deep arc.

## ⚠️ THE TWO LAWS THIS SESSION COST US (both self-inflicted, both now mechanised)
- **Guard the CAMPAIGN, not the process** (`tools/treelock.sh`). A `pgrep` poll cannot see a campaign
  made of sequential processes; mine started in a gap and 63/140 binaries broke.
- **Gate with `--no-propagate`, then propagate PER FUNCTION, routed by tier (§123).** A fixed 3600s
  propagation timeout killed the driver mid-fleet-write; a killed process performs no undo.
- Corollary proven twice: **agents must only ever write `.run/`** — that is why both incidents cost
  build cycles and zero work.

## 📓 NEW THIS SESSION
Cookbook **§122** (gate raw before transforming; undo belongs to the writer as a per-edit journal),
**§123** (propagate a family with the tool its TIER needs + routing table), **`docs/cookbook-index.md`**
(226→324 sections, symptom-keyed, in `tools-health`), `tools/treelock.sh`, `tools/prefetch_fleet.py`,
`tools/cookbook_index.py`.

---

# 🛑 (superseded) SESSION CHECKPOINT (2026-07-30, in-flight)
> Written while two background campaigns run; REFRESH before any pause (the stale-checkpoint trap).

**Running in background:** (1) **T0.5 full prefetch batch** (`prefetch_fleet.py`, 126 programs —
imports ~3 min each + define+decompile; cache was 3,680 at launch; task `baw61zyz6`; resumable —
re-run the same command if interrupted). (2) **T1a recovery sweep** (`.run/recover/t1a_runner.py`
→ `.run/recover/t1a.log`; 108 autopsy-MATCH fns / 50 binaries; driver commits banks per binary via
gate_stage's scoped add; **OWED AFTER IT LANDS:** a config sweep-up commit — jr-bank preps edit
`config/overlays.mk` + splat yamls which `gate_stage --commit` does NOT stage — then R22 clean-fleet
+ report point #2).

**HEAD at checkpoint:** `commit:1223`. **Fleet:** 87.5 / 78.0 / 92.00 (pre-T1a-banks). Tree: T1a's
in-flight src/config edits (theirs); `.run/` artifacts.

**T0 ✅ (6 commits) · T0.5 ▶ (batch running; main+3 overlays done: +2,241 cached) · T1a ▶ ·
T2 ▶ (two probes done, arc re-scoped — see log; NEXT session opener: sub-split carve + shift-diff
+ symbol-pin probe on ov_SC07_007) · T3/T4/T5 pending.**

**If resuming fresh:** read `docs/frontier-p30.md` (report point #1, with the T2 R14 correction) +
the T2 log entries; check both background tasks' outcomes first (`git log` for t6-recover commits;
`ls .run/ghidra_c | wc -l`); the Ultracode prompt for T3's first wave is still OWED to Drew
(R26/R27) — T1b agent-residue wave folds into it.

## Per-task log

### ▶ S6a — the source-agnostic zero-crack sweep: 842 banked, and the residue is OUR TOOLING again (2026-08-01)
**Setup, measured before running anything (R37 — probe before costing).** The 190 zero-crack families
(129,997 templatable ins) were decomposed with **zero builds** by remapping each family's exemplar onto one
member and type-checking the resulting draft statically:
· **117 families / 92,368 ins / 2,735 member-slots** — draft self-contained ⇒ sweepable now.
· **17 / 24,332 ins** — the §94/§100 class: the body uses a **file-scope MULTI-LINE typedef**, which
  `extract_unit` cannot carry (it carries single-line ones only). Head prizes `0x8012b77c` (ov_SC07_006,
  139 members, `Ang2_8012B77C`) and `0x80128c98` (ov_SC01_077_a, **275 members**, `CdFileLoc`) = 14,937 ins.
· **9 / 9,364 ins** — `has_mid_jr` ⇒ the §53 carve path, not this sweep.
· **47 / 3,933 ins** — `remap_hseq` REFUSES (mostly unresolved immediates). Genuine, small.

**⚠ PREMISE CORRECTION (R14) — the checkpoint's stated mechanism was wrong.** The post-wave frontier says
these families were unreachable because "every sweep this project has run passed `--source ov_SC01_077`".
It is not the mechanism: `--source ov_SC01_077` is the **default**, and `hseq_sweep`'s override block only
fires when `source != EX_OV`, so the manifest's own non-ov077 exemplar was already being used. The real gate
is **`--band substantial`** (the default): of the 181 non-jr zero-crack families only **13 are substantial**
— 114 `mid`, 54 `tiny`. **`--band all` is the unlock**, exactly as the S1 trap note warned. (The 106
non-ov077 exemplars are real and interesting; they were not what blocked the sweep.)

**Result:** `family_sweep --hseq --band all -j12 --only <117 addrs>` staged **2,735 drafts / 1,239 groups,
0 skips** → **BANKED 842 / 1,893 failed**. **R22 clean-fleet `make clean` + extract-all + check-all → 140
passed, 0 failed of 140.** Fleet **94.43→94.67% fn-count · 91.4→91.6% instr · 84.0→84.5% distinct**.

**The residue is bimodal, and that is the finding: 57 families banked ALL members, 52 banked ZERO, 8
partial.** A per-member compiler wall does not produce that shape; one per-family blocker does. Eight
zero-banked families were probed with a new generic blocker-capture (`.run/s6_diag.py` — the any-overlay
sibling of S29's ov077-only `.run/uc_capture.py`: remap → splice → build THAT overlay → read the compiler's
own error → revert; **one build per family, not 137**). **Seven of eight are declaration/carry plumbing;
one is a genuine byte DIFF.** Two are proven defects in `tools/family_remap.py`, both located at source:
- **D1 — the preamble backscan's `{`-guard does not exempt comment lines.** The guard is a real T65 fix
  (`extern void f(int); int g(){…}` on one line), but it fires on any *documentation* line that merely
  mentions a brace, so the carry stops mid-comment and the sibling receives a dangling ` * …` fragment →
  `parse error before 'the'` (`0x80176144`, `0x80146afc`).
- **D2 — `_def_head_at` returns `True` on "param list continues past this line ⇒ ANSI definition".** False
  for a **wrapped multi-line DECLARATION** (`extern void func_801466F0(s32 a0, …,\n  s32 sp8);`), so
  `extract_unit` accepts line 457 of `ov_SC01_077_after.c` as a definition head and returns a **16-line
  fragment that contains no function body at all** (`DEFINE_func_801466B4()` + `#include "common.h"` + a
  comment), terminated by a brace pair *inside* that comment. Verified directly:
  `_def_head_at('extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,', idx) -> True`.
  This is the §110/R35 class again — a silent 0/137 wearing a compiler wall's clothes.

**S6b — the fix belongs in the TOOL, not in 17 exemplars (R33).** The plan was to hand-move each
MISSING-TYPE exemplar's typedef into its function body (§100, byte-neutral, 17 edits + 17 verifications).
Probing the class first showed it is the SAME root cause as D1/D2 — a multi-line construct read one line
at a time — so it was fixed once, in `family_remap`, for every future family instead:
- **D5 — `_typedef_block_start()`**: on a `} T;` closing line, walk up to the matching `typedef` (both
  the `typedef struct {` and brace-on-its-own-line forms) and carry the WHOLE block. Only blocks that
  literally begin with `typedef` are carried (a struct VARIABLE closes identically but would be a
  duplicate global in the sibling); safe because `harvest_verify` already strips a typedef the sibling
  TU provides. The old code comment claimed these functions "route through the engine_types.h lift" —
  measured, they routed **nowhere**: 17 families / 24,332 ins were simply dropped.
- **D4 — the wrapped asm-label alias** (`_alias_decl_for` is a single-line `rx.match`) was MEASURED
  (1 exemplar, `0x801466f0`, 137 members / 3,288 ins, with a second blocker behind it) and deliberately
  **left unfixed**. It now returns `None`, so the sweep reports `skipped {'no matched unit for func'}`
  instead of failing 137 times. **A known gap that announces itself is not the same defect as a silent
  one** (R32).
- Also hardened: the forward body scan now counts braces in `cdecl._mask`ed text (R33 — one masking
  oracle), so a brace inside a comment or string can never close a function body.

**Blast radius verified, not assumed (R14):** `extract_unit` output diffed against the pre-S6 tool over
all 181 zero-crack exemplars — **157 byte-IDENTICAL**, 24 changed, every change in the intended
direction (more preamble carried; one → `None`, the D4 case that previously produced garbage).

**Measured payoff of the repairs, one sweep each:**
· D1+D2 → **+323 members** recovered from families that had banked **zero**.
· D5 → **+417 members**, including `func_8012B77C` **139/139** (8,062 ins — the head prize) and
  `func_80128C98` 137/275; `func_80146AFC` 135/137, `func_80176144` 99/137.
· **S6 total: 1,582 member-matches.** The pre-fix tool scored this same population at 842.
**R22 clean-fleet `make clean` + extract-all + check-all → 140 passed, 0 failed of 140.**
Fleet **94.43→94.88% fn-count · 91.4→91.9% instr · 84.0→84.6% distinct**; phase arc from open
(92.00 / 87.5 / 78.0) = **+2.88pp fn · +4.4pp instr · +6.6pp distinct**.

**Family state now: 70 ALL-banked · 17 partial · 94 zero-banked; 64,050 templatable ins still open.**
Distilled to **cookbook §134** (the MULTI-LINE BLINDNESS class + the bimodality tell: 57/52/8 is a
tooling signature, not a codegen one — read ONE compiler error before believing the compiler).

### ✅ S6h — wave 3 (38 targets, size-routed) + an 8/8 reconcile lane (2026-08-01)
38 targets / 44,297 templatable ins — the 11 high-multiplier families at 61-120 ins plus the top 26 of
the 10-19-member band, model-routed (Haiku ≤89 with Opus escalation, **Opus direct ≥90**).
**52 agents, ~4.1M tokens, 30 min → gate banked 27/38 (71%).** All 11 failures were captured and
classified: **8 declaration/link plumbing · 3 genuine byte-DIFF**. An 8-agent Opus reconcile wave then
fixed **8/8** (7 banked; 1 re-failed) → **wave-3 total 34/38 = 89%**, propagation **+639 members /
1 failed / 83 overlays**. **R22 clean-fleet 140/140.** Fleet **95.23 → 95.42% fn · 92.1 → 92.4% instr ·
85.0 → 85.5% distinct**.

**The reconcile lane is now 12/12 across two waves** and is the most reliable stage in the pipeline.
**Design note (S27 law, applied BEFORE it bit):** six of the eight reconcile targets share ONE TU, so
this wave **forbade agents any build** — six concurrent splice-builds would have clobbered a tracked
file. Wave 2's reconciles were allowed one build each because they were spread across TUs.

**The agents out-diagnosed the blockers I handed them — three findings worth keeping:**
· **`func_801848B0`: an agent REJECTED MY PREMISE.** I told it the draft was byte-correct and only
  declaration-blocked; it ran `match_one` first, found a real 1-instruction DIFF, and fixed both.
  R14 coming back at me from a subagent, correctly.
· **`func_8017C5F0`: the "invented symbol" was an INTERIOR ADDRESS.** `D_801DA0F0` has no symbol
  because it is offset `0x6C` into `D_801DA084` (which spans `0x801DA084..0x801DA103`,
  `asm/ov_SC02_027/data/tail18.data.s`). The lui/addiu pair builds an interior pointer — a class the
  drafters will hit again.
· **`func_8018A860`: the TU declares `memcpy` THREE times** with incompatible signatures (L81, L1518
  builtin-compatible, L1524), and a latent byte bug sat behind it. A TU that declares one symbol three
  ways is a defect waiting for the next draft that touches it.

**Carried (4):** `func_80184A94` (reconciled to `match_one` MATCH, still gate-refused) + the 3 genuine
byte-DIFFs `func_801845B0`, `func_8017BEBC`(ov_SC02_026), `func_8018480C` — real codegen residuals,
ledger material.

### ✅ S6g — wave 2: 83% → 93% bank rate from ONE batch of learning (2026-08-01)
15 targets (11 fresh Haiku + **4 gate-failed reconciles on Opus**), 15 agents, ~0.74M tokens.
**Gate banked 14/15 (93%)** — up from wave 1's 20/24 (83%) — **and all 4 reconciles banked**.
Propagation **+328 members / 0 failed / 76 overlays**. **R22 clean-fleet 140/140.** Fleet
**95.13 → 95.23% fn · 92.0 → 92.1% instr · 84.9 → 85.0% distinct**.

**Three changes between the waves, each fixing a wave-1 failure — this is the S27 finding reproducing
(57→79→100% there, 83→93% here):**
1. **Args pasted from the DERIVED manifest, not typed.** All 30 paths verified present on disk before
   launch (`asm 15/15, tu 15/15`).
2. **Blocker-capture before the reconcile fan-out** (the S29 law: agents cannot run the gate, so a
   `match_one`-MATCH draft that dies on `conflicting types for D_800A5E88` looks like a codegen
   problem to them). Each reconcile agent got the exact symbol + line, plus the two byte-neutral
   levers (conform-and-cast-at-use; the §37/§124 asm-label alias).
3. **Wave-1's Opus DISCOVERIES became wave-2's Haiku INSTRUCTIONS** (the `ori`-vs-`addiu` unsigned
   destination rule; the store-sinking scheduler rule). The flywheel closing on itself.

**The reconciles produced better root causes than my captured blocker did** — worth keeping:
· `func_80189B78`: my capture named ONE conflicting symbol; the agent found the draft had invented
  prototypes for **six** the TU already declares, **two of them AFTER the splice point** where cc1
  had not yet reached. Fixed by copying all six from the TU verbatim and pushing every type
  disagreement to a **cast at the call site** — zero bytes changed.
· `func_8018584C`: lever (A) was *blocked in both directions* — the draft cannot use the TU's tag
  (it must also compile standalone for `match_one`) and cannot redefine it. Closed with the **data**
  form of the asm-label alias: `extern struct B16_8018584C aD800A5E88 __asm__("D_800A5E88");`
  (in-tree precedent at ov_SC06_008_jr_80135D20.c:1434).
· `func_80180A4C`: the draft declared `extern s32 D_801A9DA0[]`, the TU says `extern u8 D_801A9DA0[]`
  eleven lines *after* the splice point — conform to `u8`, the use site already casts. One character
  class, byte-neutral.

### ✅ S6f — the B-shaped wave: Haiku drafts, Opus closes, the gate arbitrates (2026-08-01)
**The pool.** Derived from the regenerated map: **36 families / 28,829 templatable ins** that are
`kind=modal` (no member matched ANYWHERE, so no sweep could reach them), ≥20 members, ≤60 ins, non-jr,
and **not one exemplar in `ov_SC01_077`**. Calibrated by hand first (Phase-15/18 discipline): **3/3
one-shot** — `func_8017CDD8` (17 ins ×142), `func_8017CE7C` (16 ins ×126), `func_8017E934` (29 ins ×65)
= **330 members from 62 instructions of C, ~0 agent tokens.**

**The wave (Drew enabled Ultracode; Haiku drafters + Opus escalation, 24 targets).** Haiku was the
right tier by the `cheap-tier-ab-validated` measurement (≡ Opus at ≤~50 ins, ~4.8× cheaper); this pool
is 16-53 ins. **31 agents, 0 errors, ~2.0M tokens, 12.5 min.**
· agents claimed **24/24 MATCH** · whole-binary gate banked **20/24 (83%)** · propagation
**+524 members / 0 failed / 91 overlays**. **17 of the 20 banks were Haiku, 3 Opus.**
**R22 clean-fleet 140/140.** Fleet **94.97 → 95.13% fn · 91.9 → 92.0% instr · 84.7 → 84.9% distinct**.

**What Opus actually bought** (it earned its slot on exactly the cases the A/B predicted):
· a `sh` of a constant whose stored-width top bit is set needs a **u16 destination** — through `s16`
  gcc-2.7.2 folds it sign-extended and `li` emits `addiu`; through `u16`, `force_fit_type` keeps it
  positive and `li` emits `ori` (`func_8018A0F4`).
· a **schedule-reorder closed by STATEMENT ORDER, not the permuter**: gcc's list scheduler preserves
  relative order of disambiguable stores, so two field-zero stores had to be written ABOVE a
  three-halfword copy to sink correctly — 9 mismatches → 0 (`func_8017CAB4`).
· three separate **loose-typing fn-ptr casts** (`((void(*)(s32))func_80178D18)(a0)`) where the TU
  declares `(void)` but the asm passes `$a0` — a cheap drafter had misread all three as delay-slot /
  permuter-class residuals (`func_8017EAAC`, `func_8017CBD4`, `func_8017D5C4`).

**⚠ MY ERROR, recorded (R37/R14).** I generated the wave manifest to `.run/s6f_wave_targets.json` and
then **hand-transcribed the args into the Workflow call instead of pasting the generated file**,
pattern-filling `_jr_8017BEBC` across overlays where no such split exists (`ov_SC02_027`,
`ov_SC04_018`, `ov_SC03_002` — `corpus.stubs` says `_jr_8017AE2C`). Three agents lost time
rediscovering the real paths and reported SPEC ERRATA. Cost: tokens, not correctness. The gate driver
written afterwards (`.run/s6f_gate.py`) **derives** every TU/split from `corpus.stubs` per draft and
asserts nothing — which is what the manifest should have done. *Assert nothing you can derive.*

**The 24→20 gap is the known `match_one`→gate gap, not new:** `match_one` compiles standalone and
cannot see a TU-level declaration conflict (Phase-19 measured 88-92% match_one → 60-71% banking).
4 carried: `func_8018584C`, `func_80180A4C` (ov_SC02_026), `func_8017CC80` (ov_SC02_027),
`func_80189B78` (ov_SC03_014).

### ✅ A + B — the ×138 era was NOT over: two 16-ins cracks bought 266 members (2026-08-01)
**A (frontier regen at HEAD, R35).** Sigs + `family_hseq` regenerated after S6's banks — required before
pricing anything, and doubly so because `.run/hseq_verified.*.txt` has accumulated **22,841 files across
every sweep ever run**, so any per-family analysis that globs them over-counts. The regenerated map
derives state from sigs + `corpus.stubs` (R33), which is the authority. Overlay-only frontier at HEAD:
**95.2% fn / 92.3% instr / 85.5% distinct**; zero-crack residue **106 families / 58,657 ins** (was
181 / 120,633 at S6 open).

**B — and the finding that matters.** The S29 checkpoint's structural signal said *"after S2 the ×138 era
ENDS — those are the last two crackable fleet-wide families"*, and made that the trigger for T5/phase
close. **It is wrong, and this is the THIRD §133-class miss in a row.** Re-derived from the family map,
two fresh-crack families with ≥126 members were open the whole time:
· `0x8017cdd8` ov_SC02_039 — **17 ins × 142 members** = 2,414 templatable ins, PURE
· `0x8017ce7c` ov_SC03_114 — **16 ins × 126 members** = 2,016 templatable ins, IMM
Both are `kind=modal` — **no member matched anywhere**, so no sweep could reach them, and neither
exemplar is in `ov_SC01_077`. They are invisible to exactly the two habits this phase already corrected.

**Both hand-drafted off the `.s`, `match_one` MATCH on the FIRST try, ~0 agent tokens.** Then:
- **First gate attempt FAILED, class PLUMBING (not DIFF)** — my draft declared `extern void
  func_8017CFCC(s32 a0);` while the TU **defines** `void func_8017CFCC(void)`. The target passes `$a0`
  anyway (the caller's incoming argument simply still sits in the register — loose typing, §16), so the
  byte-true C calls it with **no argument** and declares it exactly as the TU defines it. Re-verified
  MATCH, then gated byte-identical in both overlays.
- **Propagated: 266 member-matches / 0 failed across 118 overlays** — from 33 instructions of C.
- **R14 on the seed:** the cached Ghidra-C for `func_8017CE7C` decompiled an entirely DIFFERENT body
  (three calls that do not exist in the asm). Reading the `.s` is what made it one-shot; a drafter
  trusting the seed would have burned the target and possibly ledgered it as hard.

### ✅ S6e — `--normalize-self-decls` measured to ZERO, but only after fixing the guard that made the measurement impossible (2026-08-01)
The S6a blocker probe found `conflicting types for func_X` on the SELF axis, which is exactly what
`family_sweep --normalize-self-decls` targets (drop the sibling's divergent decl of the function being
defined, cast its in-scope calls). It is OFF by default, so it was the obvious next zero-token lever.

**Run 1: 0 banked / 1,622 failed — and 909 of 909 groups reported `⚠ self-decl edit NON-NEUTRAL`.**
A 100% rate is a statement about the mechanism, not about 1,622 different functions (the §134 tell,
one day old). The three earlier sweeps over the SAME population reported **0** NON-NEUTRAL.

**The defect (D6, `family_sweep.hseq_sweep`):** the TU snapshot was taken **unconditionally**, one line
before the `if nfix:` that decides whether to edit at all — so a TU that NSD merely INSPECTED still
landed in `tu_snapshots`, and the phase-2 MISMATCH backstop then attributed ANY group failure to a
"self-decl edit" that was never made, reverting the TU and reporting `0/N banked`. Measured directly:
**NSD fires on ~25% of members (3 of 12 probed)**, so ~75% of those reverts were attributing a failure
to an edit that did not exist. The §103 tu-scope path immediately below has always snapshotted inside
its own `if _rep["moved"]:`; NSD was the odd one out. Fixed to match.

**Run 2 (fixed): NON-NEUTRAL 909 → 303** (~33%, consistent with the measured fire rate) — the fix is
confirmed — **and still 0 banked**. The 606 groups that now took the NORMAL path banked nothing, so
**the verdict is real: this residue is not self-decl-conflict-bound.** Lever measured, closed, zero.

**One open item, deliberately not chased (it is no longer decision-relevant).** I byte-measured a
firing case myself rather than trusting the backstop (R14): `func_80162CCC` in `ov_SC01_000` builds to
`9052dc0e…` **with and without** the NSD edit — i.e. **byte-NEUTRAL**, so the surviving 303 verdicts are
wrong too. Most likely the sweep applies NSD to several members of the SAME TU and the backstop
attributes an accumulated-state mismatch to "the edit". Left as a named open item because the lever
yields 0 either way; it would matter only if a future population makes NSD worth re-testing.

### ✅ S3 — the close=0 stored-draft DIAGNOSTIC pass: measured, classified, and correctly NOT scaled (2026-08-01)
Chartered as "classify, and only build a fix if ≥3 share a named class". Ran exactly that; the answer
is that no cheap shared class exists, so nothing was scaled. **The population is bigger than the plan
thought and worth less than it looks:**
- **30 ×138 family heads carry a stored draft = 182,850 templatable ins** (the plan said ~12 drafts).
- **Only 7 of 30 still verify** (`match_one` MATCH). **23 have DECAYED** — mostly `LENGTH-DRIFT`, a few
  `SIZE-MISMATCH`/`WIDTH`/`ADDRESSING`. ⇒ **a stored draft's recorded closeness is not a current fact:
  77% of this backlog no longer matches.** Re-verify before valuing a draft (extends A10/T1a).
- Of the 7 survivors: **1 banked clean** (`func_801754A8`, 37 ins ×138 = 5,106). The other 6 failed
  `conflicting types` — and `gate_stage`'s ladder recovered **0/6**.
- Those 6 split into: **1 §30#2 return-widen** (`func_8014C4AC`) and **5 PARAMETER-signature
  conflicts** (the Phase-16 def-side loose-typing wall, unchanged).

**The §30#2 attempt, and why it was reverted (R14 + the anti-bulk-header law).** `func_8014C4AC`'s
draft documents its own fix (`extern void`→`s32` in `engine_core.h`, measured byte-neutral there) —
but the note's claim that no split `.c` carries its own decl is **wrong**: the gate named
`_jr_80154C24.c`, then `_jr_80182268.c`. A `sed` over every matching decl touched **2,046 files** and
STILL did not go green. That is precisely the "bulk header edits BREAK builds" pattern (§29 doctrine:
call-site casts are the integration spine). **Reverted; exemplar re-verified `d19c9580`.** A fleet-wide
decl reconcile needs a gated TOOL, not a sed — logged, not attempted.

**Ledger:** 23 decayed drafts → redraft lanes (they are not "nearly done"); 5 param-conflict → the
def-side wall; 1 widen → needs the gated decl-reconcile tool. S3 is CLOSED as a measurement.

### ✅ S29 — `JR-PAIR-IN-ONE-O0-OBJECT` RETIRED: two instrument defects, both fixed; the pair banked (2026-07-31)
The S28 ledger class and its recorded escape (§81 step 1, isolate one fn into its own code subseg)
are **both refuted**. Neither function needed isolation; neither is on a compiler wall.

**Root cause 1 — `jtbl_carve` could not see a 4th table.** `ov_SC01_077_o0`'s carve at `0xb01a4`
predates the §8e `tables=` persistence and is a **merged double** (`func_8013C0F8` `$L75` +
`func_8013C414` `$L105`); the second owner is MATCHED, so `make extract` pruned the stub `.s` that
named its table. The tool's "single-table predecessor" inference therefore derived 3 starts where the
object emits **4 tables**, wrote `JTBL_PADS := 0,4,4`, and `jtbl_rodata_pads` refused mid-stream —
correctly, with the exact message.
**Root cause 2 — the refusal left a corpse.** `as` reads a pipeline, so it had already written a
TRUNCATED `.o` (12 of 16 `T func_`; undefined `$L57/$L59/$L63/$L75/$L76`). `make` reported Error 1 and
**left the object on disk, newer than its `.c`** — no `.DELETE_ON_ERROR`. The next build linked the
corpse: that IS S28's `undefined reference to $L105` + `func_8013C938`, one build downstream of a
loud, correct compile error.

**Fixes (both byte-gated).** (a) `Makefile`: **`.DELETE_ON_ERROR:`** — negative-control-proven
(`make: *** Deleting file …`), scratch invocation, tracked files untouched. (b)
`tools/jtbl_carve.py` `spec_from_starts`: a **R32 coverage assertion + payload recovery** at the
single choke point — every zero word inside a span is an original `.align 3` pad (the tool's own
axiom), so the word after it starts a table; recovered starts are logged. No-op where the structure is
already known (the 134 sibling `_o0c` spans DO carry `tables=+0x0,+0x70`), so committed-green spans are
untouched. Honest limit: only pad-separated boundaries are recoverable; a tight boundary still fails
LOUD (short spec → filter refusal), never silently.

**Byte proof.** 4 tables at `0x801D8254 / 0x801D828C / 0x801D82FC / 0x801D836C` (13/27/27/27 entries,
each preceded by a zero pad); span `0xb00fc..0xb0280` = 388 B = 52+4+108+4+108+4+108 — closes exactly;
derived spec `0,4,4,4  tables=+0x0,+0x38,+0xa8,+0x118`. **`func_8013B83C` (272 ins) + `func_8013BD74`
(198 ins) banked**, ov_SC01_077 `d19c9580`, **R22 clean-fleet 140/140** (`make clean` + extract-all +
check-all — the incremental result was NOT trusted, §130). Fleet **93.25% fn-count / 89.2% instr /
80.5% distinct**; dedup 1905/0; 0 NON_MATCHING. Cookbook **§132** (incl. the reusable ladder: compile
the ONE TU standalone and let `.section .rodata` + the nearest preceding `.ent` name every table owner
— it found the 4th owner and attributed `$L105` in one command, before any build or carve).

**Sweep prep — the §94/§100 type-carry class, caught by probing ONE sibling (R37).** The first
sibling gate-failed. The §132 ladder named it in one command: the sibling object emitted only
`func_8013C0F8` + `func_8013C414` tables — BD74's body never compiled (`E_13BD74' undeclared`).
Cause: BD74's draft declared `E_13BD74`/`P_13BD74` at **FILE scope**, and `extract_unit`/`remap_hseq`
carry only the BODY — the exact class that held `func_8013C08C` at 0/137 earlier this phase. Fix =
**§100 draft-local types** (moved both typedefs inside the function body; byte-neutral, exemplar
re-gated `d19c9580`). B83C's draft was already draft-local, hence unaffected. *A file-scope type in a
draft is an exemplar-only bank: it passes the gate and silently cannot travel.*

**THE SWEEP — 137/137 both, i.e. 2 × 138 = 276 function-instances banked.** `jtbl_family_bank`,
BD74 first then B83C (order is load-bearing: B83C's table sits BELOW BD74's, so carving it while
BD74 is still raw leaves an unmatched table inside the span — `NON-CONTIGUOUS`, byte-observed on the
exemplar). ~8.5 s/sibling, zero-token. Both sweeps failed on the SAME single overlay, `ov_SC07_010`
— **which is a property of that sibling, not noise, so I probed it instead of ledgering it** and it
returned 2 banks plus a real tool defect (**§132a**): `jtbl_carve --like` matches donor→recipient by
the subseg's ROLE NAME; `ov_SC07_010`'s `-O0` region is named `_o0`, the same role as the exemplar's
and the ONLY other overlay so named (the other 136 are `_o0c`, whose role never matched — **the only
reason the sweep worked at all**). The exemplar had just banked 2 more owners than the sibling has,
so the transfer derived SIX starts for THREE emitted tables. Guard shipped
(`jtbl_family_bank.like_arg`: a sibling's own committed `tables=` is authoritative; `--like` is for a
span with NO record — inert for all 136 already-banked siblings, fixes exactly the broken one).

**Fleet after the sweep (R22 clean-fleet 140/140, `make clean` + extract-all + check-all):**
**93.33% fn-count · 89.6% instr-weighted · 81.6% distinct-code** (72,416 unique fns, **+260**);
dedup 1905/0; 0 NON_MATCHING. Phase arc so far: 92.00→93.33 fn / 87.5→89.6 instr / 78.0→81.6 distinct.
That `-O0` cluster is now COMPLETE across the fleet — the two functions were the last open stubs in
every overlay's `_o0*` region.

### ✅ T0.5 COMPLETE — the fleet Ghidra-C prefetch: 124/124 programs, 7,716 files, 335 min, unattended
Zero-token, headless, resumable; imported ~120 overlay programs on demand and ran the
`DefineFunctions` completion pass per program (raw-blob auto-analysis only finds the reachable
subset — the Phase-10 finding, now automated). **Coverage measured, not assumed:**
- **5,777 of 6,070 families needing a fresh crack (95.2%) have a cached seed**
- **main 2,001/2,002 (100%)** · **resident 14/14 (100%)** · 1 residue (one main addr with no fn)

**What this changes:** the drafting surface is now fully fueled with NO MCP dependency, so waves can
run unattended against any part of the fleet — the precondition Drew asked about. It also un-blocks
P31's main-EXE campaign early (its 1,034 game-code stubs are all cached), though that stays P31
scope. `tools/prefetch_fleet.py` is committed and re-runnable; the Ghidra programs are
script-reproducible, so only the tool is tracked, not the DB bulk.

### ✅ REDO UNDER LOCK — 52 cores + 911 members banked; R22 140/140; the "cliff" was an artifact
Re-ran the whole banking sequence serially under `treelock.sh`: parallel 8-binary gate → non-jr
behemoth gate → **sig+map regen** (a bank invalidates the map) → tier-routed propagation (§123) →
one R22 over everything.
- **Wave 3: 48/48 banked** through 8 PARALLEL per-binary gates (the throughput unlock, proven).
- **Wave 2: 15/19.  Behemoths: 4 non-jr confirmed** (incl. `func_8017E120` 884 ins ×14).
- **`family_sweep --hseq`: 911 members banked / 401 failed across 137 overlays**, 49 families.
- **Fleet: 92.59% fn-count · 88.2% instr · 78.7% distinct (70,506 unique fns) · R22 140/140.**

**R14 CORRECTION, on my own earlier claim.** I reported a "per-binary bank-rate cliff" (SC03_014
1/6, SC04_018 1/6, SC06_018 2/6) and theorised a cause — canonical-decl maturity per binary. It was
an **artifact**: those gates ran against a tree that propagation was concurrently rewriting. Re-gated
clean, every binary banked **6/6**. *A measurement taken during corruption is not a measurement*,
and I theorised before re-running. Same failure shape as the phantom 91.4% in the same incident.

**Carried, honestly:** the h_seq sweep's 401 failures split as 137 "no matched unit for func"
(the exemplar banked in a DIFFERENT binary than the sweep expects — a routing gap, likely cheap),
22 unresolved-immediates, 10 STRUCT (refused by design). One `dedup_propagate` run stopped the
h_exact leg early (`0x801466F0` rc=1) — the loop halted as designed rather than risking a partial
write; the h_exact leg is unfinished and owed.

### ⚠️ INCIDENT 2 (mine) — a POLL is not a MUTEX: concurrent tree writers broke 63/140; reverted clean
**What I did.** Wave-3 gated 8 binaries in parallel (correct — the byte-gate IS per-binary) while
wave-2's propagation loop was still running, then I ran `make clean` (deleting `asm/`) on top of
both. `check-all` → **77/140**, and the corpus denominator itself moved (353,720 → 353,691), so the
apparent "91.4% instr" was an artifact of a half-written tree, not a gain.

**Root cause — the guard was structurally unsound, not merely unlucky.** My gate waited on
`while pgrep -f dedup_propagate; do sleep; done`. But a CAMPAIGN is a **loop of short-lived
processes** — 15 sequential `dedup_propagate` invocations — so between every pair there is a window
with no matching process. The poll sampled one of those gaps, read "clear", and started. Presence-
of-a-process is a sampling test on a gappy signal; it cannot express "a campaign owns the tree."

**Recovery (clean, nothing lost that mattered).** Killed the writers; `git checkout -- src/ config/`
back to `commit:1245` (the last R22-verified 140/140 commit); all 58 drafts survive untouched in
`.run/` because agents never write the tree — the discipline that made this cheap. Re-verifying
baseline, then re-gating and re-propagating serially under the lock.

**Fix shipped: `tools/treelock.sh`** — an flock(1) mutex held for the WHOLE campaign, released by
the kernel on exit or kill, with `--status`. Both drivers now refuse to run unlocked.
**The general law (worth a rule at close): guard the CAMPAIGN, not the process.**
Corollary, the second time this session a killed writer hurt: **a killed process performs no undo**,
so a fleet-tier write needs a lock ABOVE it, not cleanup inside it.

### T3 BEHEMOTH WAVE (10 agents, 3.23M tok) — **7/10 CONFIRMED byte-matches at 700–970 ins**, 0 disputed
Drew asked for up to 10 agents on the behemoths; grouping analysis first showed the ≥700-ins band is
**structured, not 29 singletons**: one 16-member family @947, one 14-member @884, a 5-member @793, a
3-member @710, a 2-member @728, 5 true singletons — plus two groups that are TOOL jobs, not agent
jobs (the 13-member IMM/jr @952 with **103 already matched** → `jtbl_family_bank` carve; two
134-matched families with 4 stragglers each → sweep). All 10 agents therefore went to genuinely
uncracked families/singletons, and each MATCH claim was adversarially re-verified by a second agent.

**CONFIRMED (7):** `func_8017E120` 884×**14** · `func_80191C50` 710×3 · `func_8017FA5C` 728×2 ·
`func_8018057C` 897 · `func_80181CDC` 769 · `func_8017CAD4` 755 · `func_8017E35C` 719.
**NEAR (3), all with byte-grounded residuals:** `func_8017EF68` 969 ins at **closeness 2** — two
transposed instructions, sched2 `rank_for_schedule` LUID tie-break, everything else (frame 0x228,
spill map, every register) byte-exact · `func_8017D174` 793 at 82 (allocno tie + pin damage, length
EXACT) · `func_8017C974` 947×16 at 812 (a pure regalloc cascade from ONE extra reserved reload reg;
598/957 regions already exact, no shape errors) — the last is the biggest family left and now has a
full structural map + the exact gcc mechanism written down.

**MY ERROR (recorded):** I hand-typed the `asm` paths into the workflow args instead of passing the
ones I had already DERIVED from `corpus.asm_path` in the same session — so several task cards named
a split that does not exist (`_jr_8017AE2C` where the truth was `_jr_8017C8D0` / `_jr_8017C294`).
The agents located the real paths themselves and reported the discrepancy. Deriving then discarding
the derivation is worse than never deriving it: it looks authoritative. Pass the artifact, never a
retyped copy of it.

**Gating plan (the jr/non-jr split matters):** 4 confirmed are non-jr → gate freely. 3 are jr →
their jtbl carve runs `make extract`, which rewrites `asm/` under the 48 running wave-3 agents, so
they are DEFERRED until wave 3 lands. Staged per-binary in `.run/beh-gate/<binary>/` for parallel
gating (7 distinct binaries).

### T4 (partial) ✅ — the two "Phase-22 grinder bugs" are STALE carry items; the real fixes were elsewhere
Verified against the code, not the list (R14 on our own defect ledger):
- **"split-file-blind lookup" — ALREADY FIXED.** `asm_subdir_for` globs `nonmatchings/*/` which
  matches every split; verified on a `_jr_` fn, an `_o0` fn, and an absent fn. Struck.
- **"churn-without-blacklist" — ALREADY FIXED.** The blind `tried.clear()` was replaced by
  input-signature gating in the T5 targeting work (re-open only fns whose draft mtime/closeness
  changed), and the blacklist exists. Struck.
- **Real fix taken instead (R33):** `asm_subdir_for` was a PARALLEL implementation of
  `corpus.asm_path` that silently took `g[0]` on multiple matches — now derived from the oracle.
- **`--fix-def-sig` posture:** flag correctly defaults OFF, but its help still advertised
  "Byte-neutral; gate arbitrates" — the exact claim T84 refuted (it imposed a signedness-wrong
  header decl over a byte-correct draft, `slti`/`sltiu`, and held 137 members at 0 until DROPPED).
  Help now carries the §119 warning. **The posture was right; the documentation was the defect.**
**Lesson for the phase close:** the carried-defect list had 2 of its entries already fixed. A
defect ledger nobody re-verifies decays into busywork — verify before scheduling (R35's sequencing
applied to the backlog of *our own* bugs).

### T3 wave 1 (Ultracode, 14 agents, 1.20M tok) — 14/14 match_one MATCH → **8/14 BANKED**; the gate's propagation TIMEOUT left the fleet half-written (caught, reverted, tool fixed)
**The wave:** 14 fresh reach-138 cores in ov_SC01_077 (117,162 gain-ins in play), one agent each,
drafting against the §31 map + cookbook with `match_one`/`rtu_match` self-verification. **All 14
returned closeness 0**, most cross-verified in the real TU. **Whole-binary gate (the arbiter,
§52b): 8 banked** — `func_80175820` (×276!) · `func_8012E014` · `func_80133298` · `func_8015FBE0` ·
`func_8016E9EC` · `func_80151C54` · `func_8012F49C` · `func_80151B98`. Bank truth derived from
source (INCLUDE_ASM presence), never the gate report (§55b trap 4). 57% conversion = the §52b law
holding exactly; the 6 rejects are all declaration/integration work their agents had already named.

**THE INCIDENT (recorded, not buried).** `gate_stage` hardcoded `timeout=3600` on
`dedup_propagate`. Ample for one bank; with EIGHT (each rewriting ~138 overlays) it blew, and
`TimeoutExpired` propagated out and **killed the driver mid-write**: 313 files modified
(alphabetically ov_SC01_000..ov_SC03_013 — it died partway through the fleet),
`config/dedup.us.yaml` never updated, `engine_core.h` half-edited. **`check-all` 124/140.**
Caught by running the oracle before trusting the state; **`git checkout -- src/` reverted all of
it** (§61 — and note a KILLED process performs no undo at all, so the driver's own restore logic
was never reached). Nothing was committed at any point; zero contamination.
**Fix shipped:** timeout now SCALES with bank count (`1800 + 1800×banks`, capped 6h) AND is
CAUGHT — on expiry the driver reports `TREE DIRTY, REVERT REQUIRED` and returns cleanly instead of
dying with the fleet open. **Recovery path (also the new standing practice for multi-bank waves):
re-gate `--no-propagate`, then propagate PER FUNCTION via `dedup_propagate --addr` — bounded,
resumable, verifiable between steps — rather than one monolithic fleet write.**

**Three byte-grounded idioms to distill (R16/R30, owed):** (1) **`void`→`s32` return is NOT
byte-neutral** — an s32 return keeps `$v0` live-out and stops dbr stealing an `addiu` into the
loop-back delay slot; this CORRECTS cookbook §3a-1's neutrality claim (`func_8016EC0C`).
(2) **The asm-label alias** `extern s32 SYM_w __asm__("SYM")` — reads a `u8`-declared shared global
as a word WITHOUT `*(s32*)&SYM`, which force_regs the address and drags 3 extra `la` pseudos across
calls; found independently by two agents; a general unblock for the u8-vs-s32 loose-typing
collisions (`func_8012E014`, `func_80133298`). (3) **Zero-byte `__asm__("")` as a delay-slot
fence** — `reorg.c stop_search_p` halts the eager filler on an asm insn (`func_8015FBE0`).

### T1a ✅ — the deterministic recovery sweep: +18 banked; the stored-draft question CLOSED (report point #2)
Population: the 108 fresh autopsy-MATCH strandeds (+ the 012 abort re-run, 0/3) across 50 binaries,
47 min, 17 driver commits. **Metric truth (R14, derived): fn-count +18 instances / distinct +12
unique fns** (commit messages summed 19 — gate-report double-list; the metric wins). **R22
clean-fleet 140/140** after the sweep + residue revert. Fleet: 87.5 / 78.0 / 92.00 (+384 w-ins).
**The honest read:** the S16 "39%" prior did NOT generalize — it was measured on FRESH same-wave
drafts; this stored-backlog population is the class decision-log **A10** already byte-proved
non-bankable by plain re-gate (0/958). The driver's reconcile/demacroize lifted **18 of ~111
(≈16%)** over A10's 0% — a real but bounded delta. **The stored-draft recovery question is now
CLOSED both ways:** cheap wins taken; the ~90 not-banked stay match_one-MATCH but their drafts are
integration-decayed — they route to T3's REDRAFT lanes (A10's "fresh re-drafts only"), not another
recovery pass. §61 residue class found + reverted (2 orphan carve .c + overlays.mk/yaml edits from
FAILED jr attempts). **Two live gaps for T3 pre-work:** (1) `gate_stage --commit` add-scope cannot
stage NEW carve files / overlays.mk / yaml — moot at 0 jr banks here, live the moment a T3 wave
banks a jr fn through it; (2) my own checkpoint edit mid-sweep tripped the driver's blast-radius
assert (012's abort) — tracked-file writes and a tree-writing campaign cannot share a repo; queue
docs until the campaign exits.

### T2 finding 2 — the Arm-A reproduction target has MOVED: the fleet is jr-carved now (2026-07-30)
`rollout_o0_cluster.py ov_SC07_007` → SKIP ("cluster fns not in base .c"): since Arm A (07-16),
the P29 jr campaign carved every overlay (007 now: 16 `_jr_*.c` splits) and **the -O0 range
(0x8013B568..) sits INSIDE `<ov>_jr_80135D20.c`** (23 stubs there in 007). The Arm-A tool's
single-file premise is stale fleet-wide — the rollout is now the predicted **carve-within-a-carve**:
sub-split `_jr_80135D20.c` (pre / o0 / post) per overlay + the Makefile -O0 wildcard for the new
class + the +0x20 shift-diff at the NEW seam. Next concrete steps (deep arc, next session's opener):
(1) extend the carve tool to sub-split jr files; (2) probe on **ov_SC07_007** (zero T1a collision;
baseline `%lo/%hi` inventory saved: `.run/t2_007_baseline_syms.txt`, 951 operands); (3) on shift:
diff the generated asm symbol inventory → **pin the drifted `D_` symbols at pre-carve addresses in
the overlay symbol file** → re-extract → per-binary sha (the config-only fix hypothesis); (4) the
R31 whale-shape hypothesis (no INCLUDE_ASM in the -O0 split) as fallback. ov_SC07_010's carve is
still in-tree + byte-neutral (the Arm-A keeper) — the 010-vs-007 asm diff is a free shift oracle.

### T2 ▶ driver generalized; ×1 probe REFUTED the append route for the remaining cluster (2026-07-30)
`tools/rollout_o0.py` (generalizes T85's `rollout_801457a4_o0.py`): map-derived members
(cross-address-safe), stub located in any non-`_o0` split, jr+o0 composites routed out loudly,
atomic two-file + per-binary SHA gate + restore-both. **×1 probe (`0x8013b6a0`@ov_SC01_000):
gate-reject — and the diagnosis corrects the frontier report (R14 on my own doc):** T85's family
banked by APPEND because `0x801457A4` abuts the o0b object's END; the remaining 18 families
(`0x8013Bxxx–0x8013Cxxx`, below the whale) mis-place on append by construction, and per-fn
isolation IS the Arm-A re-carve. o0b-*bearing* ≠ o0b-*adjacent* — my "the wall never has to fall"
inference was wrong; caught at 1 build instead of 2,131. **T2's real substance = the Arm-A `+0x20`
defect.** First probe: identify WHICH symbol shifts on a failing overlay's re-carve; hypothesis:
splat re-GUESSES a data-symbol boundary the carve moves → pin it in config symbols and re-probe.

### T0.5 ▶ launched + probed (2026-07-30)
`tools/prefetch_fleet.py` (committed `commit:1220`): 126 programs / 7,966 uncached representatives.
**Probe 1 (main):** +1,525/2,002 cached in <1 min — the decompile leg is CHEAP; **477 main addrs
have no defined function in the program** (main's 06-14 auto-analysis gap) → follow-up: a
`DefineFunctions.java` completion pass over main from splat entries (the Phase-10 mechanism), then
re-run (resumable). **Probe 2 (import leg): FAILED then FIXED** — my missing-program matcher
checked "not exist"/"NOT_FOUND"; Ghidra's actual phrase is "Requested project program file(s)
**not found**" → the self-healing import never fired (+0/371, +0/315). One-line trigger broadening;
re-probe running. T1a (deterministic recovery sweep, 108 fns / 50 binaries, driver-committed banks,
no-propagate — reach≥2 winners ride T3 Lane A) launched concurrently; commit-scope interaction
VERIFIED safe (driver delegates to gate_stage's scoped `git add -u src/` — ghidra/ churn cannot
leak into bank commits).

### T0(e2)+(f) ✅ — autopsy refreshed; frontier regenerated + the three populations PINNED (2026-07-30)
- **Autopsy** (`collect -j12` + `report`): 1,349 rows — **1,178 near / 63 nobuild / 108
  match_one-MATCH** (T1's stranded-draft fuel, 3× the S16 sample), 0 classifier errors,
  second-oracle agree. `docs/autopsy.md` regenerated.
- **Worklist/manifest regen:** 101 live stubs / 261,789 gain-ins (stale 160/583k gone); R14 checks
  inside the manifest: 28/28 giants verified reach-138.
- **THE `-O0` PIN (headline):** 18 families / **2,192 open members — 2,131 o0b-route-eligible /
  61 SC07-no-o0b**; **15/18 exemplar-matched**. The "WALLED ~1,287" framing dissolves: the bulk
  never needs the Arm-A splat fix — T2 = generalize the proven `rollout_801457a4_o0.py` (130/130).
  Composites flagged: `0x8013c414`/`0x8013c0f8` are jr+o0 (carve inside the o0b TU — probe ×1 first).
- **Zero-crack roster:** 114 families / 3,166 open members / ~204k weighted ins (28 substantial);
  its head IS the -O0 set (T2 and Lane A open together).
- **Concentration:** top-20 = 24.0% / top-100 = 44.8% of open family weight (head consumed vs S13's
  53% — expected post-campaign flattening).
- **Report point #1: `docs/frontier-p30.md`** (all numbers same-tree at one HEAD, post-repair — R35).

### T0(e) — part 1 ✅: the 21-file absolute-include defect fixed (2026-07-30)
All 21 carriers were jr-carve split files including `engine_types.h` by absolute path
(`/home/musashi/bfm-decomp/...`, some twice); swapped to the house-relative
`#include "../shared/engine_types.h"`. `grep -rln /home/musashi src/ include/` → **0**.
**R22 clean-fleet from a genuinely clean tree: 140 passed, 0 failed of 140.** Part 2 (autopsy
refresh) next.

### T0(d) ✅ — backlog ledger: already clean; the scanner deleted (R33) (2026-07-30)
Findings, byte-verified: (1) the still-a-stub filter **already existed** (`load_best` drop +
`prune`, built 07-24) and the tracked jsonl was **already compacted** — the tree's pre-existing
uncommitted `.run/backlog.jsonl` edit was late-S25's un-committed prune output; `prune` today:
1350 → 1350, dropped 0. (2) The stale rows I'd flagged (`func_80151944` etc.) live in **worklist.md**
(regen at T0(f)), not backlog. (3) `_open_stubs` (private regex) vs `corpus.stubs` (the oracle):
**0 divergence across all 131 ledger binaries** — after fixing MY probe, which compared names
against int vram addrs (R35 pointed at my own instrument). Hardening: `_open_stubs` now **derives
from corpus.stubs** (STUB_RE deleted — R33's "best outcome is a deleted scanner"); hex-case
canonicalized on both sides of the membership test (a lower-hex record can't silently drop, R32);
count parity proven post-change (load_best 1350 == 1350). §83's doctrinal caveat (backlog ≠ work
queue; worklist is the queue) STANDS — that's classification quality, not staleness.

### T0(c) ✅ — family_hseq↔progress gap: ZERO definitional gap; stamped against recurrence (2026-07-30)
Same-tree regeneration of BOTH digests: family_hseq (overlays) **27,248 instances** == progress fleet
stubs 28,296 − main 1,034 − resident 14 = **27,248 — EXACT**. The carried "29,961 vs 28,296" was a
**cross-date, cross-scope misread**: the 07-29 map snapshot was SESSION-25's *open* state, and
29,961 − 27,248 = **2,713 = exactly the session's banked total**. The tools were never in
disagreement — both already derive from `corpus.stubs` (the Phase 26-A conversion, family_hseq:42).
Hardening: the family-hseq digest header now **stamps scope ("138 OVERLAYS only") + generation
HEAD + the shared-oracle note** ("compare digests only at the same HEAD") — a stale or
scope-mismatched comparison is now self-announcing. Roadmap v2 D-bucket corrected.
**Fresh frontier readings from the regen** (full pinning still at T0(f)): 478 substantial families /
678,404 templatable ins · **28 zero-crack** (was 61 on 07-29 — S25 consumed 33) · 3,626 PURE / 40
IMM / 6 STRUCT · overlays 27,248 instances / 17,629 distinct / 1,587,311 ins.

### T0(b) ✅ — rtu_match surfaces the real cc1 error in the verdict (2026-07-30)
`_diagnostics()` filter (the SESSION-25 recipe, in-tool): drop `warning:`/`In function`/`At top
level`/`###`/blank lines from the failing stage's stderr and print the FIRST 15 survivors — gcc-2.7.2
hard errors carry no `error:` prefix and the old `[-2000:]` tail was all warnings. Raw-tail fallback
if the filter empties (ICE/signal formats) — never prints less than before. Applied to all four
stages (CPP/CC1/MASPSX/AS). Verified on a real deliberate CC1 failure: the verdict now leads with
`t.c:3116: 'nonexistent_var' undeclared` instead of a 2 KB warning tail. `--stderr-out` unchanged
(full dump). Docstring updated.

### T0(a) ✅ — gate_stage stage-0 + fix_arity_callers journal undo (2026-07-30)
The carried defect pair closed structurally, not by root-causing:
- **`gate_stage.py`**: **stage 0 gates the RAW drafts before any transform** (`GATE_NO_STAGE0` to
  disable) — the destroyed-good-draft mode (SESSION-22 reproduction: `_o0` pair + `func_80138C60`,
  ladder-FAILED / bare-VERIFIED) is now impossible by construction; the canon/cast/rc ladder + arity
  pre-pass run only on stage-0 failures. Root-cause hypothesis recorded in-code (transforms are
  batch-`--src-file` TU-blind where the gate is per-draft TU-aware) — open, now harmless.
- **`fix_arity_callers.py`**: `--journal` (per-edit literal before/after) + `--undo-journal
  [--keep <banked>]` — the exact undo now lives in the WRITER, shared by ladder AND bare workflows
  (the 17-TU residue class). Replaces gate_stage's two-special-case file snapshot; undo moved to
  after stage 2 (closes the latent stage-2 parity gap: a stage-2 bank used to lose its arity edit
  before its own gate attempt). Stale-journal guard (`_arity_rc is not None`).
- **Verification:** negative control apply→undo → byte-identical tree; `--keep` retains exactly the
  kept edit; in-process flow test `.run/t0a_flowtest/driver.py` **7/7 PASS** (stage-0-first, s1in =
  failures-only, accumulation, undo-guard, src/ untouched). Real-tree at-scale proof lands with
  T1's first sweep (R22-bracketed there). Cookbook **§122**.
