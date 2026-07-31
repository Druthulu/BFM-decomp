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
- [ ] **T0.5 — Fleet Ghidra-C prefetch batch [background]** — `ImportOverlay.java` (~130 missing
      programs) + `DecompileFunctions.java` over every remaining distinct stub (overlay tail + main's
      1,034; skip LINKED) → `.run/ghidra_c/`. **R23 lock discipline** (stop the hook-launched MCP
      server first or route through it). Verify via `build_fuel_manifest.py` counters + 5 spot-reads.
- [ ] **T1 — Integration-recovery sweep [Ultracode — prompt at launch]** — all close=0 stranded
      drafts through `recover_integration.py` tiers + §65b de-macroize + the snapshot-safe ladder;
      the 10 named SESSION-16 blocked drafts. Prior: 39% recovery. **Report point #2.** R22 per batch.
- [ ] **T2 — The `-O0` cluster [Max, deep]** — PRIMARY: build the two-file atomic substitution
      driver (stage remapped body into `<ov>_o0b.c` AND drop the stub's INCLUDE_ASM from
      `<ov>_after.c` in one edit, gate) and sweep the T0-pinned families. FALLBACK: R17 research on
      the Arm-A splat `%lo +0x20`. Resistant residue → wall ledger with evidence. **Report point #3.**
- [ ] **T3 — The standing crack-wave loop [Ultracode waves; Max between]** — lanes interleaved,
      propagate behind every crack same-session:
      A zero-crack (~61, propagation-only) · B top-mass fresh families (no size cap; jr via
      `jtbl_family_bank`; `gate_stage` call-site-casts, never bulk header edits) · C tail mass on
      prefetched seeds (local v3 ≤15 → GLM/Haiku ≤~50 → cheap-Opus mid) · D PINS (19) + W4 bounded
      diagnoses + permuter backlog via the T4-fixed grinder.
      Per-session checkpoint + velocity + 3 metrics. **ROI floor: 2 consecutive sessions < +0.3pp
      instr each with all lanes exercised.**
- [ ] **T4 — Carried-tool resolution [xHigh]** — grinder warm-start + the 2 Phase-22 grinder bugs;
      verify `--fix-def-sig` is nowhere a default (§119).
- [ ] **T5 — Phase close [Max]** — burn-down from digest history; P7 milestone walk; Roadmap delta;
      gate 2; PhaseEnd_Phase30.

**Milestone:** overlays at their measured ceiling — **≥95% instr fleet, or every remaining overlay
stub on a named wall/behemoth/queue ledger** — 140/140 byte-identical throughout.

## Blockers
- (none) — the precondition (Drew's milestone-close commit) landed at `commit:1213`.

---

# 🛑 SESSION-28 CHECKPOINT (2026-07-31 08:1x) — FRESH SESSION SAFE HERE
> Supersedes SESSION-27 below. **Nothing is running. Tree lock FREE. Tree clean** but for the R23
> `db.*.gbf` churn (never stage). **HEAD `commit:1261`** (+ this doc commit).
> Effort **xHigh** (Drew, session start). `make tools-health` RC=0 at session open.

## FLEET — R22 clean-fleet **140 passed / 0 failed** (verified this session, genuinely clean tree)
**92.70% fn-count · 88.3% instr-weighted · 78.7% distinct-code** (70,590 / 87,459 unique fns) ·
dedup 1904/0 · 0 NON_MATCHING linked. Phase opened at 92.00 / 87.5 / 78.0.

## WHAT LANDED THIS SESSION
- **Resume item 2 CLOSED — the "137 no matched unit" class: 137/137 banked, 0 failed** (`commit:1261`),
  behind a one-line-class tool fix (`commit:1260`). R22 140/140. Cookbook **§124/§124a**.
- **Resume item 1 RE-SCOPED (not banked)** — see below; it is T2 work, and now T2's best ×1 probe.

## ▶ RESUME HERE (nothing blocked except where noted)
1. **The 3 jr behemoths + group B's carve** (staged `.run/beh-gate/<binary>/`; member list
   `.run/jtbl_members_0x80191c50.json`). **Both run `make extract` — run ALONE under
   `tools/treelock.sh`.** ⚠️ Re-derive which of the 7 staged fns are still stubs FIRST — 4 were
   banked in SESSION-27 and the staging dir still holds all 7.
2. **T2 `-O0` carve-within-a-carve.** Open with the **×1 probe on the 4th region** (below) — smaller
   blast radius than the planned `ov_SC07_007` and it is the Arm-A `%lo +0x20` shift oracle.
3. **Next wave**: 3,873 fresh cached cores across 119 binaries (`.run/p30w4_pool.json`), dealt ACROSS
   binaries so the gate fans out. **Breadth ⇒ prompt Drew for `/effort ultracode` and WAIT** (R26/R27).
4. T1 remainder (10 named S16 drafts + route the ~90 to REDRAFT lanes), T4, T5.

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
