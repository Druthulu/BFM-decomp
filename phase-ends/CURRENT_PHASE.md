# CURRENT PHASE — Phase 31: The Frontier Atlas & Wide-Tolerance Campaign

**Started:** 2026-08-14 · **Plan approved:** 2026-08-14 (gate 1; Drew) · **Effort doctrine:** xHigh default / Max deep (T5, T7, synthesis) / Ultracode waves (R26/R27 prompts) / Fable-tier only for new wall classes.
**Approved plan:** `/home/musashi/.claude/plans/fable-5-set-max-goofy-seahorse.md` (the full design; this file is the crash-recovery log).
**Approval also ratified R37 (probe before costing), R38 (read recorded failure verdicts first), R39 (negative-control new refusal-checks) — now binding.**

## The re-charter (one paragraph)

Instead of roadmap-v2 P31's per-function grind, Phase 31 organizes the 12,059 remaining stubs (main 1,041 · resident 14 · ov 9,832 · md 1,179) into **crack groups**: a deterministic per-function feature layer + multi-tier similarity atlas (li-normalized exact tier, seed sweep vs the 2,719 matched skeletons, calibrated warm tier for the 3,238-unit cold tail + main, kNN neighborhood graph), evidence-joined to a lever label per group; plus **widened mechanical lanes** (LEN-tolerant aligned remap with a fully-mechanical LI class, §172b EXTPAIR/SELECT detectors + routing, PLUMBING campaign, permuter cluster warm-start, weak-seed cards); then a **campaign loop to ceiling** — deterministic $0 lanes first, agents only for exemplars, velocity-ledgered, closed on measured decay. Milestone shape = P30 (campaign to ceiling; every remaining stub on a named ledger at close). Main fully included from day one.

## Task checklist

- [x] **T0 — Pivot log + freshness + hygiene** — DONE 2026-08-14. (xHigh)
- [x] **T1 — Integration quick-bank sweep** — DONE 2026-08-14 (pending final R22 log line). **8 banked, 0 agent tokens.** (xHigh)
- [x] **T2 — References** — DONE 2026-08-14. (xHigh)
- [x] **T3 — Main enablement** — DONE 2026-08-14. (xHigh)
- [x] **T4 — atlas_features.py** — DONE 2026-08-14. (xHigh)
- [x] **T5 — atlas.py** — DONE 2026-08-14. **THE ATLAS EXISTS.** (Max)
- [x] **T6 — PLUMBING campaign** — DONE 2026-08-14. **+9 banked (probe 64%); recipe + 3 laws distilled (§173); sweep proved the no-draft majority routes to family lanes.** (xHigh)
- [x] **T7 — family_align.py built + NC'd; the mechanical-cousin premise REFUTED by its probe (0/26)** — engine re-scoped to T8's LEN+N same-function pile; no driver built (correctly). (Max)
- [x] **T8 — LEN+N lane** — DONE 2026-08-14. **Pile routed 587/587; 345 wrong-drafts reclassified; 49 permuter + 192 card fuel staged; mechanical lane = honest null.** (xHigh)
- [x] **T9 — Warmstart + weak-cards** — DONE 2026-08-14. **Grinder queue armed (49 lenmiss + 10 seeded drafts, 120 refused by the stream filter); 954 weak-cards emitted, cheap-tier-dominated. No grinder patch needed.** (xHigh)
- [ ] **T10+ — Campaign loop to ceiling** (repeating sessions; velocity ledger; close on measured decay). (Ultracode waves / xHigh orchestration / Fable new-walls)
- [ ] **Tclose — PhaseEnd** (gate 2). (Max)

## Standing verification (every task)
R22 clean-fleet **213/213** after every banked batch · tools-health green · 0 NON_MATCHING (G4) · dedup-check 0 failed · R32 coverage assertions on every new scanner · R39 negative controls on every refusal check · R37 probes before pricing · R38 ledgers before experiments · commit per task (task + this log in the same commit; Drew pushes).

## Progress log

- 2026-08-14 — Phase planned and approved (3 Explore + 2 Plan agents; full design in the plan file). Task list built (harness tasks #1–#12). T0 started.
- 2026-08-14 — **T0 COMPLETE.** (1) R31 decision-log entry (the re-charter WHY + R37–R39 ratification). (2) `harvest_verify.py` import guard: a bare import now RAISES instead of running a gate (verified both directions; CLI behavior unchanged). (3) **Resident ±1 RESOLVED + FIXED**: `--bootstrap`'s linear partition had fused the +0 data word with `func_800CEDFC` (row `0x800CEDF8` nins=18) and dropped `func_800D33E0` past a glued tail — the true denominator is **145** (progress was right, the sig wrong). `sig-resident` now ELF-seeds (S45 pattern: unique 4-aligned T-symbol addrs inside the `resident_TEXT_START/END` markers → exactly 145; bootstrap fresh-clone fallback). All three oracles now agree (sig 145 · corpus matched 131 · progress byte-ident 131); `audit-corpus` 0 PHANTOM + 0 TRUNCATED. (4) Family maps regenerated at HEAD `commit:2161`: **11,025 open non-main members = 12,059 − main's 1,034 EXACT** (the stale map's 102 phantoms cleared); cousins totals now A-prop 1,125 / seeded 1,293 / cousin-multi 5,373 / cold 3,234 inst; adapt cards 704, aprop cards **204 (full emission)**. (5) **Main fuel gap is DEAD**: 2,001/2,002 main stubs have cached Ghidra-C (only `func_80049600` missing) — the roadmap's "0/2,096" note was stale. (6) `make tools-health` → OK (dedup 2,063/0; C1 254,521/254,521; audit-digest confirms the fleet digest; resident fix moved instr num+denom by the same +9).

- 2026-08-14 — **T1 COMPLETE: 8 banked for 0 agent tokens.** R38-first: partitioned the MATCH-108 pile against current stubs (75 still open) and against the S50 gate history (62 gated-and-failed with verdicts · 13 never-gated). The lanes and their measured outcomes:
  - **Never-gated 13** → gate_lane: 0/13, but the verdicts decomposed to 11× `undefined reference to D_*` = the §171 stale-seed-symbol class. **Extended `aprop_symfix` with STALE-DELTA** (n:n uniform-delta rebase; R39 synthetic + snapshot NCs, zero false positives; the delta test even refused a pair my hand-check wrongly accepted) → 4 rebased, **4/4 banked** (`func_8016BCC0`, `func_8017F1C8`, `func_80186BD8`, `func_80186BF8`). Cookbook **§171-D** written in-session.
  - **SELF-decl PLUMBING 7** → `recover_integration --stages demacroize --max-tier binary`: **4/7 banked** (`func_80139BE0`, `func_8014ED28`, `func_80161D88`, `func_801659DC`); 3 stay near.
  - **Stored-draft re-gates** (no-verdict 7 + close=0 8 + diff 1 + 9 STALE→clean world-motion drafts): **0/23-ish banked** — the ~8% A10 stored-verdict law held again; all re-verdicted fresh.
  - **Handed forward with fresh classifications**: CALLEE-decl 15 + CC1-FAIL 14 → T6 (cast-callees/tu-scope stages); UNDEF-DATA/OTHER 9 → the §171b-1 data-definition carry (T7/T8); md CARVE-REFUSED 8 → campaign side-quest ledger. immfix pile: fully consumed (0 open). fix20: 19/20 consumed in S50.
  - Tool fixes landed: `gate_lane` propagate-commit tag now derives from GATE_PHASE (was hardcoded phase-30 S49).
  - Rate lesson for the velocity ledger: fresh-fix lanes (STALE-DELTA 4/4, demacroize 4/7) vastly outperform blind stored re-gates (0/23) — the campaign loop's L2 ordering is confirmed by measurement.

- 2026-08-14 — **T2 COMPLETE (references).** (1) **PsyQ dev-CD extracted**: walked the on-disk Track-1 image (MODE2/2352) with the frozen `tools/bfm_extract/iso9660.py` (R33 — no new extractor; walker = iter_directory/read_extent with out-of-range extents skipped) → `tools/reference/psyq-sdk/` (gitignored): 2,374 files / 231.6 MB, **400 C sources (373 in PSX/SAMPLE/** across CD/GRAPHICS/SOUND/MODULE/CMPLR/…); only 7 out-of-track `.DA` audio skipped. (2) **Provenance find**: `GNU/SNGNUVER.TXT` = SN Systems' gcc build history (`2.7.2.SN32.3.7.0002`, 14.5.97) with per-build changelog of SN's patches vs vanilla — only `UNROLL.C` (parameterised max unroll insns) is codegen-relevant; recorded in the idiom notes as the first-look suspect if a loop-unroll residual ever defies the vanilla model. (3) **gcc-2.7.2 reference completed**: +6 files from GNU ftp (`calls.c` + `caller-save.c` — both cited by §172's producer model, previously missing — + integrate/optabs/varasm/recog), tarball sha256 `7cd8bce5…` recorded. (4) `docs/psyq-sample-idioms.md` seeded (inventory, provenance, first style conventions, the lane hook); SETUP §5.6 rows added (R21).

- 2026-08-14 — **T3 COMPLETE (main enablement).** (1) `sig_image` seed-ends extension: `--seeds` now accepts `0xADDR NINS` lines (and jsonl `nins`); a seeded nins is authoritative — the slice is exactly `[addr, addr+4·nins)`, bypassing `func_end` (whose heuristic mis-sliced 3/40 main samples). (2) `corpus.s_ins_count()` factored from audit() (R33, one counter) + `corpus.py <bin> --seed-ends` CLI. (3) **`make sig-main`**: 2,002 main stubs signed at splat-true lengths → `.run/sig.main.jsonl` (deliberately splat-SEEDED — the atlas needs the boundaries a match must hit; NOT the independent second oracle, which stays deferred per `docs/second-oracle.md`). (4) **Full word cross-check: 2,002/2,002 slices byte-faithful** (EXE bytes vs `.s` comment-column words; 0 SLICE-SUSPECT; note the `.s` word field is byte-order hex, not the LE-decoded value — first checker draft compared wrong and read 1,999 false suspects). (5) `family_remap` main special-cases: `vram_of('main')` = code-segment `vram − start` from `splat.us.exe.yaml` = 0x8000F800; `img_path('main')` from the same yaml's target_path (R33). `stream_words('main')` == `.s` words on **25/25** samples. (6) Regression: `sig-resident` re-run **byte-identical** after the shared `read_seeds` change.

- 2026-08-14 — **T4 COMPLETE (`tools/atlas_features.py`).** Per-function features memoized per distinct `h_exact` (`.run/feat_memo.json`) and fanned out 1:1 with sigs to `.run/feat.<bin>.jsonl` ×213 (main reads the splat-true `sig.main.jsonl`; registry untouched). **363,525 rows / 92,855 distinct bodies in 21 s** (vs the 3–6 min estimate). Features: nins/band · o0 prologue tell · frame/callee-saved set+order/fp · CFG skeleton (nblk/ncond/nback/ret_n via branch-target scan; jal = call, never an edge — position-independence proof in the docstring) · mid_jr/jalr · stable-call-sequence hash (fixed main+resident ranges) · reloc-kind sequence hash · 16-bucket ophist · **§172b tells as importable shared functions (extpair/dupselect/sign_mix/magic_div — T8's len_tells imports these, R33)** · **li-normalized skeleton `h_seqn`** (non-anchor lui dropped, ori→addiu class). Verifies: R32 join asserted per binary at write; determinism 0 mismatches on 200 re-derived bodies; **mid_jr cross-check vs family_hseq's independent oracle: 6,444/6,444 exemplars agree** (first verifier draft compared ZERO rows — a string-vs-int addr type mismatch, the R32 silent-no-op class caught in my own verifier; now indexed + fails loud if compared==0). o0-tell vs `corpus.is_o0` on 13,019 open fns: 41 both / **94 tell-only = candidate undiscovered -O0 fns in -O2 TUs (§116 — o0_subsplit carve fuel for the campaign)** / 14 src-only outliers.

- 2026-08-14 — **T5 COMPLETE (`tools/atlas.py` + `make atlas`) — THE FRONTIER ATLAS EXISTS.** Survey in 92 s, all assertions green: **5,139 groups cover ALL 12,058 open instances / 613,710 ins** (12,058 = progress's 12,051 stubs + 7 NON_MATCHING exactly — the +1-blob and +8-banked discrepancies were both chased and resolved: data blobs excluded, T1 banks confirmed absent; main open reconciles to classify()'s stubs+NM with a hard assert). Tiers: **calibration measured** (positives = cousin ≥0.85-raw merges, negatives = size-matched cross-unit pairs; the li-normalized metric is so discriminative that recall ~99% holds down to 0.55; rule = smallest t with neg-accept ≤0.2% ∧ recall ≥95% → **THRESH_WARM=0.70** at 99.1%/0.18% — chosen because a false warm-merge wastes an exemplar crack, a miss only routes cheaper) · T1.5 h_seqn 2 merges · **warm tier 1,019 merges** · **seed sweep: 4,702/7,247 open skeletons (65%) carry a ≥0.55 matched seed** from the 2.7k-skeleton pool · kNN graph (top-8 open + matched neighbors) · tiny-direct. **Lever table (the strategic map):** head-crack 1,283g/186.9k ins · UNKNOWN 1,964g/138.6k (honest) · **extend-tell 575g/76.7k** · redraft 46.8k · **jtbl-carve 190g/45.7k** · integration 575 inst/23.4k · seeded-crack 23.4k · len-vein 778 inst/16.8k · swaprepeat 9.2k · plumbing 161 inst/8.1k · o0-lane 6.6k · cc1 6.4k. Top group: 268 drifted single-member skeletons unified (per-location ~23-ins family, 0.72 seed). Evidence joins accounted (audit/backlog/ledgers/cards; residuals EXCLUDED-STALE until regenerated); `--targets` resolves 12/12 `.s`. `make atlas` = the full regen chain. docs/frontier-atlas.md committed.

- 2026-08-14 — **T6 IN PROGRESS (PLUMBING campaign) — probe converged after two R14 corrections.** `plumbing_groups.py` derived the honest pool: **237 still-open** PLUMBING rows (the "1,217" was ledger-vintage inflation): SELF 109 (3 concentrated binaries) · CALLEE 48 · OTHER 48 · DATA 32. Probe (ov_SC03_107 SELF-21 → 14 with drafts): first run **0/14 with a PHANTOM shared error** — root-caused to **cross-group TU-edit poisoning** (a demacroize edit in TU-A persists while TU-B's drafts gate; every whole-binary build compiles ALL TUs) → fixed `recover_integration` with per-group isolation (git-checkout binary TUs between groups, gate_lane's proven pattern; engine_core.h untouched so fleet-tier arity persists) + added the **`macro-externs` draft stage** (§121: one draft's guessed `extern int f()` vs the TU's `DEFINE_`-macro definition — lifted from family_sweep, R33) + **`tu-scope` stage** (§103 STU, the sweep-only lever). Isolated re-run exposed the TRUE class: `undefined reference to D_*` = **the §171 stale-seed-symbol class** (rtu_match MATCHes these drafts — it is blind to relocation names; the R34 two-oracle disagreement exactly as documented) → **symfix-first**: 11/11 rebased (mixed 1:1 + n:n deltas incl. the S49 Δ0x4128) → **9/14 banked (64%)** where the raw path scored 0. The standing recipe: `aprop_symfix --fix → recover_integration --stages macro-externs,demacroize,tu-scope` (per-group isolated). Full sweep over the remaining ~200 rows now running.

- 2026-08-14 — **T6 COMPLETE.** Sweep over the remaining ~200 rows: **the decisive finding is Law 3 (§173)** — the biggest groups (ov_SC02_037 44 rows, most of ov_MAIN_012's 42) have **zero stored drafts**: their PLUMBING verdicts came from transient family-sweep remaps never persisted to the backlog. A recovery lane can only recover what was stored — verdict-only rows are family-lane fuel (already atlas-labeled), not recovery fuel; the true stored-draft class was largely consumed by the probe (**9 banked, 64%**). Singleton tail with drafts: 0/~20 (fresh per-fn verdicts recorded). Cookbook **§173** (symfix-first · per-group isolation · verdicts-without-drafts) + index regenerated (518). **R22 clean fleet: 213/213** with all T6 banks. Phase total so far: **17 banked, 0 agent tokens** (stubs 12,059 → 12,042).

- 2026-08-14 — **T7 COMPLETE (honest refutation).** `tools/family_align.py` built: aligned classifier (SequenceMatcher over FC.tok; LEN-LI/LEN-NOP/LEN-JTBL/LEN-STRUCT/STRUCT-ALIGNED/PURE/IMM verdicts) + li-cluster reconstructor (with the split-cluster absorb for the rs-changed addiu partner) + the aligned imm engine. **NC-1: 157/157 verdict-equivalence** with classify_member on banked pairs — the NC itself caught two real classifier gaps (R-type non-shift sa = STRUCT; registers tested BEFORE the reloc skip — a reloc-slot word with a different register is STRUCT). NC-2 parity 21/21. **The R37 probe then killed the planned driver before it was built: 0/26 LI-ONLY cards classify mechanically** (regfields drift ×19) — cousins are 0.85-similar DIFFERENT functions; §168 law 1 ("a cousin is a seeded crack, never a remap") re-derived by measurement. The engine's true consumer is **T8's LEN+N pile** (draft vs its own target = same function). Parked for T8: the reloc-vs-constant range discriminator for lui-bearing clusters. Decision-log entry written (R31).

- 2026-08-14 — **T8 COMPLETE (LEN+N lane).** Built: `match_one --emit-streams` (additive, stdout-identity NC'd) · `family_align.addr_true_rel` (the reloc-vs-constant range discriminator — full conservative set kept for pair semantics/NC-1 [157/157 regression], address-true subset for indel eligibility; synthetic probes: lui-bearing constant cluster now LEN-LI, address-anchored indel still refuses) · `tools/len_tells.py` (per-draft aligned classification + §172b tell tagging on target-side indels, detectors imported from atlas_features R33, cookbook text embedded in cards) · `tools/lenmiss_route.py` (pool-parallel per A8: **587 audit LEN rows re-verified live and routed in 24 s**). **Routing:** redraft **345** (frac>0.35 — the draft is not the function; reclassified APPEND-ONLY in the backlog, so near-miss metrics stop lying) · permuter-length **49** (|Δ|≤2 clean drift — grinder fuel) · cards **192** incl. **14 EXTPAIR/SELECT/NOP-tagged** (the audit's own detectors had emitted zero — these are new signal) · **mechanical 0 — an honest null**: stored drafts rarely get CONSTANTS wrong (agents copy them from asm); LEN drift is shape, so the LI-cluster swap lane has no fuel in this pile and family_align's value here is the classifier/detector. R32 accounting 587/587.

- 2026-08-14 — **T9 COMPLETE.** `tools/warmstart.py` (the permuter/grinder FEEDER): `--from-banked` walks a banked exemplar's h_seq family's still-open members, builds remapped proven-body drafts (`symbol_map` + `aprop_autodraft.build_draft`, refusing on reloc-count mismatch), **stream-classifies member-vs-seed with ZERO compiles** (masked_diff-shaped dicts from ground-truth bytes → `residual_class.classify_streams`), enqueues ONLY permuter-shaped (bucket==permuter or LENGTH-DRIFT |Δ|≤2) as backlog near-records; `--lenmiss` ingests T8's 49-route. **Grinder patch NOT needed** (its candidates() deliberately keeps unclassified records — "unknown is not a reason to skip" — so pre-filtered enqueues flow as-is; documented in the feeder's docstring). Armed live: **49 + 10 enqueued, 120 refused** by the stream filter (the anti-92%-wasted-CPU discipline working). `family_cousins --weak-cards`: **954 units** (the 0.70–0.85 annotate-only band, never before consumed) as seeded-crack cards, ins-ranked, §168 laws embedded, model-routed **haiku 804 / v3 43 / sonnet 86 / opus 21** (cheap tiers dominate — the token-efficiency shape), 0 unresolved `.s`.

## 🛑 SESSION CHECKPOINT — S60 FINAL (2026-08-25 19:30). Phase 31 CONTINUES. **NINE LANES RUNNING.**

**SESSION CLOSE 22:50: 2,238 banked (regex count; the stub invariant is higher) · open crackable
2,981 · fleet 98.2% instr-weighted, 96.4% distinct-code · cookbook 888 sections · registry 5,085
lines healthy.** Fleet moved 97.4% -> 98.2% instruction-weighted and 94.6% -> 96.4% distinct today.
Lanes: drafter · gater · maintenance · stallguard · distill · main · **elastic (new)** ·
**grinder/permuter (new)** · re-gate runner. A Fable analyst is auditing the whole strategy and
writes `docs/tool-designs/frontier-analysis-s60.md` — **READ THAT FIRST NEXT SESSION.**

### THE SESSION'S LESSON, MEASURED REPEATEDLY
**Every throughput ceiling was a harness defect, and the guards only count when they are RUNNING.**
1. **The straggler tail blocked the fleet** — collect_drafts() waited out the full 700s grace before
   queueing, 11m40s of every ~44-min wave at 4-13 agents, four waves for four. Fixed with a finisher
   thread; trough went 11m41s -> 0s.
2. **The draw set the request rate, not the API** — `--max-bins 24` handed 196 of 699 available cards
   to a 2,000-agent fleet. The endpoint's real envelope, from 170k logged requests: 2,755 req/min
   peak minute, 764/min sustained 15 min at 8% 429s. The "knee at 150-250" I reported earlier was
   ramp-burst confounding — **corrected**.
3. **Every second wave re-drafted the wave still in flight** — `--retry-unbanked` returns still-open
   cards and the pre-draw runs WHILE a wave drafts, so ck->cl were 239/239 identical, co->cp 238/238.
   Yield alternated 47.6% / 3.8% / 35.3% / 3.6%. Fixed by deriving finished-ness from BOTH gate logs.
4. **The "parallel" gate was serial** — gate_stage takes the fleet-shared lock EXCLUSIVE unless
   GATE_NO_ARITY is set; sweep_parallel never set it, so 24 workers queued on one lock. Two-phase
   split (parallel readers, serial arity only for COMPILE-failures): wave dd banked **217 in 39 min**.
5. **config/overlays.mk was wiped THREE TIMES** — the 5,077-line registry committed as a ZERO-LINE
   file. Root cause found: four `open(mk,"w").write(txt)` truncating writes (jr_isolate_all:593,
   jtbl_carve:1077/1118/1165) that zero the file before writing, racing the carve automation that runs
   AT THE GATE. All four now go through **tools/mk_write.py** (atomic tmp+fsync+replace, refuses a
   rewrite below 80% of current lines, refuses to write over an already-broken registry, flock).
   Blast radius each time: no overlay builds -> main's glob sweeps overlay .s into MAIN's OBJS -> main
   RED -> main lane correctly refuses -> EVERY gate rejects EVERY draft. Waves dn/do/ei/ej/ek/el
   banked 0 with 675 backlog rows reading "match_one MATCH but the whole-binary gate rejected".
6. **A guard that is not running is not a guard** — config_sane() was added at 13:0x but the gater
   process had run since Mon 19:32; Python loads a module once. It wiped the registry again AFTER the
   guard existed. Restarting a long-running lane is part of shipping a fix to it.

### WHAT LANDED (all committed)
* **Throughput**: tail overlap · MAX_BINS 24->160->250 · queue-depth 4 · levers remap/needs-autopsy/
  plumbing added · gate two-phase · --gate-jobs 32 · gate now LOGS sweep_parallel output (it was a
  30-minute silent block). Rate went 65 -> **554 req/min peak**, 1,363 agents at peak.
* **ONE_PER_GID=0** — draft every instance, siblings included: 627 cards vs 334 skeletons, and the gate
  got MORE efficient per build (2.9 drafts/rebuild vs 2.6). Wave `eh` banked **129/380 (34%)**.
* **Generational top-off** — generation is the primary ordering at both assembly levels; never-drafted
  work goes first, no tier is filtered out, wave size unchanged.
* **-O0 U2/U3**: whale object resolved BY CONTENT (NC 134/134) -> 4 SC07 banked; the x3 carve at
  [0x8013B568,0x8013C98C) byte-neutral on all three, then **48/48 banked**. 52 fns, zero tokens.
* **Cookbook §274-§292** from three distill batches (18 waves, cf, and 36 waves / 1,216 candidates
  reviewed by five agents). Index **888 sections**.
* **New tools**: mk_write.py · jtbl_pads_fix.py (byte-proven pad-spec repair) · elastic.sh · grinder lane.
* **Fixed**: idiom_serial (dead at turn 0 — a FAMILY-card file fed to a per-function consumer, KeyError
  before its first turn, which is why tells had "never been run") · match_one warns when --asm-subdir
  is defaulted (it targets resident; names are address-derived so the same name is a different function
  in another binary) · tell counts on the card + rendered as a checklist in the prompt.

### THE STRATEGIC PICTURE (this is what next session must act on)
* **3,062 open crackable.** main is **313** crackable, not 1,274 — 961 of its stubs are LINKED PsyQ
  segments and data blobs, linked byte-exact, never decompiled.
* **CORRECTED 19:45 by the Fable audit, and I had this wrong all session.** The atlas at commit:2911
  measures: 3,106 open instances · 2,245 open skeletons · 1,772 groups, of which **480 are
  multi-member holding 1,334 siblings** and **1,292 are SINGLETONS carrying 57% of the open
  instruction mass**. My "~3,900 siblings behind ~334 skeletons" conflated two different
  populations — the never-drafted stub count with the sibling count — and overstated remap leverage
  by ~3x. Most remaining work is singletons that each need their own crack. The "~334 drawable,
  308 gen6+" figure describes only the COLLAPSED wave-eligible view; whole-pool generation is 53%
  gen0/1 and 25% gen6+, and only **292 functions are 6+ GATE-refused**.
* **Wide waves now convert at 1-5%.** The drafting side is solved; the gate is the bottleneck (30-67
  min per gate at 1-3 concurrent builds, load 2.6 of 32 cores) and the drafter parks when its queue
  fills. **Optimise banks per GATE MINUTE, not cards per wave.**
* **The reasoning budget is NOT the cause of the decline** (checked): truncated-turn rate is INVERSELY
  correlated with bank rate — the best waves had the MOST truncation (cx 8.7% trunc / 43.9% bank,
  dd 8.3% / 51.4%) and the dead waves the least (dl 1.3% / 0.5%, ej 0.6% / 0%). The zeros are the
  registry outages; the slide from 51% to 20% is population generation, not agent budget.
* **The wall is an INTEGRATION wall, not a codegen wall** (Fable's headline, and the highest-value
  finding of the day): of the 292 functions the gate has refused 6+ times, **178 (61%) already
  produced a closeness-0 draft** — match_one byte-equality, whole-binary gate rejection. The blocker
  is symbols/decls/TU plumbing, and the fleet keeps re-drafting them (10,049 reject rows over 574
  distinct functions). Its top recommendation is a ZERO-TOKEN integration-resolver lane
  (rtu_match -> reconcile/cast/arity -> reloc_identity -> symfix -> stage to the maintenance gate).
* **5,388 backlog rows at closeness <= 2** de-duplicate to **~543 open functions** (470 at 0, 73 at
  1-2) — the grinder (tools/grinder.py, Phase 21, LLM-free, decomp-permuter) had NEVER been run this
  campaign and is now on them. My own re-measure at 19:40 found 290 still-open closeness-0 functions,
  down from Fable's 470: the re-gate and grinder are draining exactly this pool.
* **Gate cost is proportional to FAILURES, not drafts** (measured mechanics): chunk=1 plus the 3-stage
  ladder means ~3 whole-binary builds per FAILING draft, serial per binary — dd (51% conversion) ran
  1.8 s/draft, eo (1.4%) 8.6 s/draft, and banks-per-gate-minute fell 17.5 -> 0.10. My "30-67 min
  gates at 8% CPU" conflated wall_min (which includes drafting and queue time) with gate wall
  (12-31 min healthy). tools/rtu_match.py inverted into the gate's stage 0 would make builds
  proportional to BANKS (~20x fewer at current conversion) — shadow-run it over 2-3 gates first.

### OPEN THREADS (ranked)
1. **Read `docs/tool-designs/frontier-analysis-s60.md`** — the Fable analyst was told we are NOT married
   to the ox-wave model and asked for the smartest path to 100% given the measured state.
2. **The gate.** 30-67 min at ~8% CPU with -j 32. The new sweep logging will show where the wall-clock
   goes. A 3x gate speedup outvalues any drafting change.
3. **Re-gate: DONE 21:42, and the result is instructive.** ei 34 · ej 0 · ek 4 · el 6 · em 3 · en 8
   = **55 recovered** from 2,814 pre-paid drafts, zero model tokens. Only ei paid well (34/184 = 18%);
   the rest returned 0-4% because by the time they were re-judged the live lanes had already banked
   those functions — they come back NOT-A-STUB, not as banks. **This does NOT confirm the uncollapsed
   thesis**: eh's 129/380 (34%) remains an outlier, and ei's 18% is the only corroboration. Do not
   plan on sibling-drafting reproducing eh without more evidence.
4. **The fleet R22 never actually runs** — guarded to skip while any gate is in flight, and one always
   is. Last real sweep 12:54. Give it a lock-aware window.
5. **A-prop residual**: 169 STRUCT · 121 no-seed-decl (wants type INFERENCE from use sites, a tractable
   deterministic tool nobody has built) · ~73 IMM-unresolved · 12 void-returning near-0s.
6. **The unwritten law**: 8 cards across 4 waves independently re-derived that the whole-object gate
   needs every sibling matched. Recorded in §283; never written as its own section.

### THE 8k-vs-16k QUESTION — UNRESOLVED, AND THE A/B THAT WOULD SETTLE IT
Drew asked whether waves cracked better BEFORE the output budget was raised (MAXTOK 8000 -> 16000
in S59). The record holds one clean measurement and one confound, and they point opposite ways.

**Clean (measured, S59's own ledger).** Raising MAXTOK to 16k DID cause a real regression — overlay
draft completion fell from **84-89% (8k) to 41% on wave bt and 69% on bu**. The cause was a harness
interaction, not the model: at ~30 tok/s a 16k generation runs ~530 s while STRAGGLER_GRACE was
still 120 s, so agents were guillotined mid-thought with NO draft at all. Raising the grace to 700 s
fixed it; completion has run 97-99% since.

**Confounded (cannot be resolved from existing data).** On BANKS PER DRAFT the 8k era looks better:
S59 records the default lane at **1,335 banked of 2,996 drafts = 44.6%**, while today's best 16k
waves ran dd **217/625 = 34.7%** and de **192/647 = 29.7%**. But the two eras drew from different
populations — 8k waves still had never-drafted work, today's draw from skeletons that have refused
six times each. Token budget and population exhaustion moved TOGETHER, so neither number isolates
the other. Do not cite either as evidence about the budget.

**Separately measured today, and it rules out the simple story**: truncated-turn rate is INVERSELY
correlated with bank rate — the best waves had the MOST truncation (cx 8.7% trunc / 43.9% bank;
dd 8.3% / 51.4%) and the dead ones the least (dl 1.3% / 0.5%; ej 0.6% / 0%). If budget exhaustion
were driving the decline that relationship would run the other way.

**THE A/B THAT SETTLES IT (do this next session — it is cheap):** draw ONE card pool and split it
within a SINGLE wave — half the shards at MAXTOK 8000, half at 16000, everything else identical
(same generation mix, same binaries, same gate, same tree state). Compare banks per DRAFT and per
GATE MINUTE, not completion. Holding the population constant is the entire point; every historical
comparison fails precisely because it does not. Keep STRAGGLER_GRACE at 700 s for both arms, or the
8k arm wins on an artefact. If 8k matches or beats 16k on banks per draft, the cheaper budget also
buys more agents per unit time, which compounds.

### SESSION STOPPED 22:55 — ALL LANES DOWN, TREE CLEAN
Every campaign process was stopped deliberately at session end (0 alive, verified twice after
settling). Stop sentinels `.run/ox_campaign.stop` and `.run/auto/STOP` are SET — **delete both
before relaunching anything**, or every lane exits immediately. Tree clean; registry 5,085 lines.
One dirty overlay TU (`ov_SC04_019_jr_80186570.c`) left by a killed gate was BUILD-VERIFIED as an
abandoned substitution (its binary failed to build with it) and reverted, not committed — R42's
distinction between a proven bank and mid-gate residue, decided by the bytes rather than by the
file merely being dirty.

Two shutdown hazards for whoever restarts: `pkill` on a lane's SHELL leaves its python running
(it happened to the drafter, the gater AND the main lane tonight — kill by PID and verify with
`ps -o lstart`), and a bash `case "$f" in src/[a-z0-9_]*.c)` pattern MATCHES ACROSS SLASHES, so it
silently classified an overlay TU as a main TU and nearly reverted the wrong file.

### HOW TO RESUME
`tools/campaign_status.py` first, then `git status --porcelain -- src/ config/` — if dirty, **COMMIT,
never revert** (R42). **Check `wc -l config/overlays.mk` is ~5,083** before trusting any gate verdict:
a wiped registry makes every draft look wrong. Three stale `.git/index.lock` files blocked all lanes
today; if one exists with no `git` process and `.git/index` newer, it is residue. **Verify lanes from
`ps -o lstart`, never from `pgrep`** — pgrep matches your own shell, and `pkill` killed the gater's
shell while its python survived, twice.

### RULE CANDIDATES FOR PHASEEND (P10)
* **R51 — A DERIVED PROPERTY STORED AS CONFIG WILL GO STALE AND TAKE A BINARY WITH IT.** JTBL_PADS
  records how many jump tables an object emits; every bank carrying a `switch` can change it. Three
  REDs in one day. Derive it, or give it a byte-proven self-repair.
* **R52 — A BLANKET COMMITTER MUST NOT ADOPT A COLLAPSED FILE.** "Commit the dirty tree rather than
  revert" is right for src/ and wrong for config.
* **R53 — VERIFY A BUILD FROM ITS EXIT CODE, NOT ITS OUTPUT FILE.** A failed build leaves the previous
  binary in place, so `make build; sha1sum build/<bin>/<bin>` is a FALSE GREEN. It fooled me twice.
* **R54 — A GUARD DOWNSTREAM OF THE FAILURE IS NOT A GUARD, AND A GUARD THAT IS NOT RUNNING IS NOT A
  GUARD.** api_agent's "wrong card file?" warning sat one line below the KeyError that killed every
  serial-lane run; config_sane() could not stop a wipe because its process predated it.
* **R55 — A LANE THAT RUNS UNATTENDED MUST LEAVE EVIDENCE.** The gate was a 30-minute silent block, so
  a 31->67 min regression had nothing to diagnose from; an elastic-lane cap silently stopped existing
  because a two-line integer made its test error and bash read the failure as false.

---

## 🛑 SESSION CHECKPOINT — S60 (2026-08-25 15:35). Phase 31 CONTINUES. **ALL LANES RUNNING.**

**1,947 banked today · 4,819 -> ~3,652 open crackable · fleet 97.4% instr-weighted.**
Seven lanes alive: drafter · gater · maintenance · stallguard · distill · main · **serial (new)**.

### THE SESSION'S ONE LESSON
**Every throughput ceiling was a harness defect, and the last one nearly cost the fleet.** In order:
1. **The tail blocked the fleet.** `collect_drafts` waited out the full 700s straggler grace before
   queueing, so 11m40s of every ~44-min wave ran at 4-13 agents — four waves for four. Fixed by
   handing the tail to a finisher thread (`wait_for_tail` + `finish_wave_async`); measured 11m41s →
   **0s**.
2. **The draw set the request rate, not the API.** `--max-bins 24` handed 196 cards of 699 available
   to a 2,000-agent fleet. Raised to 160: **644 cards / 46,590 ins**. The endpoint's real envelope,
   from 170k logged requests: 2,755 req/min peak minute, 764/min sustained 15 min at 8% 429s. My
   earlier "knee at 150-250" was confounded by ramp bursts — **corrected**.
3. **Every second wave re-drafted the wave still in flight.** `--retry-unbanked` returns
   "waved but still open" cards, and the pre-draw runs WHILE a wave drafts, when none of its cards
   have gated. ck→cl 239/239 identical, co→cp 238/238, cv→cw 222/222. Yield alternated 47.6% / 3.8%
   / 35.3% / 3.6%. Fixed by deriving finished-ness from BOTH gate logs.
4. **The parallel gate was serial.** `gate_stage` takes the fleet-shared lock EXCLUSIVE unless
   `GATE_NO_ARITY` is set; `sweep_parallel` never set it, so 24 workers queued on one lock — 0-2
   builds at load 2.2 of 32 cores. Two-phase split (parallel readers, then serial arity for
   COMPILE-failures only): gate dd banked **217 in 39 min** vs 50 in 63 min before.
5. **`config/overlays.mk` was committed EMPTY** by wave dk's gate — the 5,077-line registry for all
   141 overlays. main could not build (its glob prunes siblings via `$(<bin>_ASM_DIR)`, so every
   overlay's nonmatchings fell into MAIN's OBJS), the main lane correctly refused against a RED
   baseline for 1,288 stubs, and gates collapsed (dn 0/224, do 0/236). Restored; `config_sane()` now
   refuses to commit any config below 80% of HEAD's lines at all three commit sites.

### WHAT LANDED (all committed)
* **Throughput**: tail overlap (TAIL_DONE_FRAC 0.75) · MAX_BINS 160→50 (see below) · queue-depth 4 ·
  levers remap/needs-autopsy/plumbing added · gate two-phase. Rate 65 → **341 req/min peak**, 452 agents.
* **-O0 U2/U3**: whale object resolved BY CONTENT (NC 134/134) → 4 SC07 banked; the ×3 carve at
  [0x8013B568,0x8013C98C) byte-neutral on all three, then **48/48 banked**. 52 fns / ~6,730 ins, zero tokens.
* **Cookbook §274-§282** from two distill batches (18 waves + cf); index **824 sections**.
* **jtbl_pads_fix.py** — repairs a stale JTBL_PADS spec by ENUMERATING candidates and keeping one only
  if it is the UNIQUE byte-identical spec. Three of five REDs today were that one stored-derived-state class.
* **Generational draw**: `--generational` (opt-in) + **top-off** (generation is the primary ordering at
  both assembly levels, so every wave fills lowest-first without shrinking).
* **Serial lane fixed and RUNNING for the first time**: it passed a FAMILY-card file to a per-function
  consumer, so `api_agent` died with KeyError at turn 0 on every target since the line was written —
  which is why its ledger held 8 rows and tells had "never been run".

### THE STRATEGIC FINDING (this changes the endgame)
Two populations, 10x apart, and both are true:
* **open crackable functions: 3,652** — 2,873 never drafted (78.7%)
* **DRAWABLE skeletons: 334** — gen0 **5**, gen1 2, gen2 4, gen3 6, gen4 4, gen5 5, **gen6+ 308**

683 candidates collapse to 334 skeletons (349 same-gid siblings). The ~2,900 untouched functions sit
BEHIND those skeletons and bank by mechanical remap once an exemplar cracks — they are not waiting for
a draft. So wide drafting is done: it now converts at **5%** (dq: 8 banked of 167 gated, 98 min of gate)
because the drawable pool is 92% gen6+ walls. **"Everything out of gen2" is 11 cards away.**
Also corrected: **main is 327 crackable, not 1,288** — 961 of its stubs are LINKED PsyQ segments and
data blobs, which are linked byte-exact and never decompiled.

### RUNNING RIGHT NOW
drafter (waves ea/eb) · gater (4-deep queue draining) · main (m41) · serial lane on
`func_8017D1C0 @ ov_SC06_027` (118 ins, 60 turns) · maintenance · stallguard · distill.
Re-gate of the false-verdict waves: dk 15 · dl 12 · dm 3 banked; dn/do NOT re-gated (stopped
deliberately to give the gater its capacity back — their drafts are intact in `.run/wave_d[no]/`).

### OPEN THREADS (ranked)
1. **The fleet R22 never actually runs.** It is guarded to skip while any gate is in flight, and the
   campaign always has one — last real sweep 12:54, and `.run/fleet_red.txt` still names main RED
   (stale; main is green). Give it a lock-aware window instead of a skip.
2. **5,388 near-records at closeness <=2 have NO consumer.** No permuter/grinder lane exists. tells 6.5,
   the A-prop IMM tier-2 slice (7 IMM-VALUE + 4 IMM-OFFSET) and the general tail all terminate here.
3. **Run several serial lanes in parallel, one per lever** — the only shape that both uses API capacity
   and compounds. One lane = one agent; the free-ox window cannot otherwise be spent.
4. **A-prop residual, named and sized**: 169 STRUCT · 121 no-seed-decl (needs type inference from usage,
   not lookup) · ~73 IMM-unresolved · 12 void-returning near-0s (gate_stage-internals candidates).
5. **`func_8017F39C` suspects a binary-registration mixup** with a same-named function in ov_SC01_009
   (from the cf distill) — a GATE-side question, worth checking after today's registry incident.

### HOW TO RESUME
`tools/campaign_status.py` first. Then `git status --porcelain -- src/ config/` — if dirty, **COMMIT,
never revert** (R42). Two stale `.git/index.lock` files blocked every lane today (8 min and 21 min);
if one is present with no `git` process and `.git/index` newer than it, it is residue — verify, then
remove. Lane changes take effect on three clocks: draw defaults next draw, tool code next invocation,
lane args/env only on a fresh SHELL (`tools/lanes/relaunch_drafter_shell.sh`). **Verify from the
process (`/proc/<pid>/cmdline`), never from the file you edited** — `pgrep` matches your own shell.

### RULE CANDIDATES FOR PHASEEND (P10)
* **R51 — A DERIVED PROPERTY STORED AS CONFIG WILL GO STALE AND TAKE A BINARY WITH IT.** JTBL_PADS
  records how many jump tables an object emits; every bank carrying a `switch` can change it. Three
  REDs in one day. Either derive it, or give it a byte-proven self-repair (jtbl_pads_fix).
* **R52 — A BLANKET COMMITTER MUST NOT ADOPT A COLLAPSED FILE.** "Commit the dirty tree rather than
  revert" is right for src/ and wrong for config: config holds no proven state that exists only in the
  worktree, and an empty registry is never intended.
* **R53 — VERIFY A BUILD FROM ITS EXIT CODE, NOT ITS OUTPUT FILE.** A failed build leaves the previous
  binary in place, so `make build; sha1sum build/<bin>/<bin>` reports a FALSE GREEN over a build that
  never linked. It convinced me twice today.
* **R54 — A GUARD DOWNSTREAM OF THE FAILURE IS NOT A GUARD.** api_agent's "ZERO matched — wrong card
  file?" warning sat one line below the KeyError that killed every serial-lane run.

---

## SESSION S54 (2026-08-17, ultracode) — wave T + the pre-gate ladder learns to see overlays

- 2026-08-17 — **Session opened with the §180 leftover sweep, before drafting anything new.**
  `scan_leftovers.py` over 644 stored drafts in 5 binaries: **29 byte-perfect, still-stubbed drafts =
  2,478 instructions** (main 3/217 · ov_SC04_011 15/1,392 · ov_SC02_005 5/261 · ov_SC06_029 5/521 ·
  ov_SC03_028 1/87), plus 39 honest NEAR. Zero agent tokens. `reloc_identity --batch`: **29/29 AGREE**.
  `fragment_check`: 1 FAIL — `gfx2D_BG0_OBJ_4D8` owns `.L80050D5C`, which `gfx2D_BG0_OBJ_1B4` branches
  into (the §181 mirror class; it is also a `GsSortBg` fragment-merge target, so it routes there).

- 2026-08-17 — **Wave T built and launched (71 cards / 6,557 ins / 5 gate groups / 14.2 drafts per
  rebuild), and the selector learned two new principles.** `make atlas` first (it predated 161 banks):
  4,836 groups / 11,183 open instances / 563,916 ins. Then two additions to `build_wave_atlas.py`:
  * **`--one-per-gid`** — a fleet-wide draw over SIBLING overlays fills half a wave with the SAME
    skeleton at two addresses (the naive draw put 22 of 44 groups in twice), paying an agent for work
    `family_sweep --hseq` does free behind the banked exemplar. Collapse to one card per atlas group,
    defer the siblings to `<out>.siblings.json`, assert reps + siblings == candidates (R32).
  * **`--rank total`** — rank gate groups by the mass a card DELIVERS (its own instructions plus its
    deferred siblings'), not by face mass. Measured on this draw: face 6,509 ins with 9,985 sibling ins
    behind 57 gids under `--rank mass`, versus **6,557 ins with 12,709 sibling ins behind 69 of 71
    gids** under `--rank total`. **Wave T's potential is 19,266 instructions for 71 agents.**
    R39 negative control: on a pool with unique gids, `--one-per-gid` output is byte-identical.
  The wave prompt carries the S53 harvest as laws 8-20 (§183.1/§183.3, §186, §186b, §186c, §189-A..E,
  §190-A..C), STEP 0 (the cross-overlay magic-literal grep), a per-card sibling note, and a new
  **Reconcile phase**: one agent per gate group runs the deterministic ladder over its own slate and
  resolves the refusals with the §183 playbook — reconciliation moved INSIDE the wave (§176h.C2).

- 2026-08-17 — **§192: the pre-gate ladder was main-only and said "clean" about it.** Running
  `pregate_check` on an overlay slate printed `checking 0 substituted file(s) ... clean`. Three
  defects, all fixed with controls: (1) `resolve_conflicts`/`substitute` hardcoded
  `corpus.stubs('main')` → per-binary `_stubs_for()` (main path byte-identical); (2) `sym_of` returned
  `void` for every `extern void (*D_x[])(...)` → 192 phantom CONFLICTING-EXTERNs; project symbols now
  matched by name, keywords excluded, declarator read explicitly — **NC over 5,526,100 declarations:
  189,301 changed verdicts, 0 regressions**; (3) `void f()` vs `void f(void)` were collapsed together →
  40 more phantoms; C89's unspecified-parameter rule is now `gate_main.sig_conflict` (7 synthetic
  controls). Same slate now reports **2 failures, both real**. Plus **§192b**: the tool REFUSES when it
  substituted 0 files, and prints one `[DROP]` line per rejected draft — the drop reasons were being
  computed and discarded while the tool printed "worth a rebuild".

- 2026-08-17 — **Leftover-recovery lane launched** (5 agents, one per binary): each gets its slate, its
  TU, and the deterministic `[DROP]`/refusal evidence, and applies the §183 playbook draft-side only.

- 2026-08-17 — **WAVE T: 71 cards -> 70 MATCH -> 70 BANKED, zero drops in five gate groups.** 87 agents,
  8.71M tokens, 0 errors, ~70 min. The only structural change from wave S was the **Reconcile phase**:
  one agent per gate group runs `reconcile_slate --apply` -> §183 playbook -> `pregate_check` over its
  OWN slate, re-verifying every edit with match_one, BEFORE the first rebuild (§176h.C2 says
  reconciliation belongs inside the wave; this is that, automated). Wave R banked 18 of 45 on its first
  slate; wave T dropped nothing. Selector changes that made the pool worth more per agent:
  **`--one-per-gid`** (the naive draw duplicated 22 of 44 skeletons across sibling overlays) and
  **`--rank total`** (rank gate groups by card + deferred-sibling mass). Potential 19,266 ins for 71
  agent-slots; **49 siblings (4,954 ins) then banked mechanically** via `family_sweep --hseq`.

- 2026-08-17 — **The §180 leftover pile: 24 banked for ~0 drafting tokens.** 644 stored drafts
  re-verified -> 29 byte-perfect and still stubbed; `reloc_identity` 29/29 AGREE; `fragment_check` 1 FAIL
  (`gfx2D_BG0_OBJ_4D8`, the §181 mirror class, routed to the fragment-merge lane). A 5-agent §183 lane
  reconciled them draft-side; gates: ov_SC04_011 14/15 · ov_SC06_029 4/4 · ov_SC03_028 1/1 ·
  ov_SC02_005 4/5 (after a 3-typedef hoist in its TU, **null-control-built byte-identical first**) ·
  main 1 (the second is `func_80031A98`, the known `D_800C5328` wall).

- 2026-08-17 — **§192 + four over-refusals: the pre-gate ladder was main-only and said "clean" about it.**
  `pregate_check` on an overlay slate printed `checking 0 substituted file(s) ... clean`. Fixed, each
  with controls: per-binary `_stubs_for()` (main path byte-identical); `sym_of` no longer returns the
  keyword `void` for `extern void (*D_x[])(...)` (**NC: 5,526,100 declarations, 189,301 changed
  verdicts, 0 regressions**); C89's unspecified-parameter rule as `gate_main.sig_conflict`; the overlay
  DRIVER's typedef transform modelled (harvest_verify strips TU-provided typedefs, gate_main hoists);
  block-scope typedefs skipped; `M2C_UNK` and friends derived from include/common.h as scalar aliases
  (R33). A cc1 probe settled the builtin case: two conflicting `memcpy` decls are a WARNING (exit 0),
  the same pair on a non-builtin is an error. §192b: the tool now REFUSES when it substituted 0 files
  and prints the per-draft `[DROP]` reasons it used to compute and discard.

- 2026-08-17 — **Harvest: 71 index_gaps -> 9 CONFIRMED laws (§193-A..I), 5 REJECTED, 61 ALREADY COVERED.**
  19 agents (5 cluster readers + one adversarial verifier per candidate, defaulting to REJECT). The 61
  is the actionable number: the cookbook knew and the agents did not find it. **§193-A is the cause and
  the fix** — a card's `exemplar`/`sibs` come from the atlas's OPEN set by construction (`atlas.py:96`
  load_open, `:657` max over open members) = 0/34 banked measured, 0% at any maturity, while
  `atlas.py:505-536` already computes a MATCHED-pool twin whose identity `build_wave_atlas` discarded.
  Cards now carry `seed_ref` + `matched_n` (control draw: seed_ref banked **4/4**, exemplar **0/12**).
  §193-B byte-refutes §43's cast absolute (the decider is `combine.c:929`'s cross-call guard);
  §193-G refutes §164-54's ">=4 arms" bound (`balance_case_nodes` splits at `i > 2`); §193-C bounds
  §8/§48-A1's cross-jump refund to TAILS (gcc-2.7.2 has no prefix merge).

- 2026-08-17 — **R22 clean-fleet: `make clean` + extract-all (212/212 + main) + `check-all` = 213 passed
  / 0 failed of 213**, EXE `143dbb89` unchanged. Fleet **95.7% instr-weighted · 91.0% distinct-code ·
  96.96% fn-count**; MAIN 20.5%. Session total: **143 functions banked** (70 wave + 49 mechanical +
  24 leftovers), of which only 70 cost an agent.

## SESSION S53 (2026-08-16, ultracode) — wave R + the leftover-draft harvest

- 2026-08-16 — **S53-1 PREFLIGHT + ATLAS REGEN.** Tree clean at `commit:2416`, no gate in flight. `make atlas`
  regenerated at HEAD (the S52 atlas predated waves P+Q, whose banks grew main's matched seed pool 175→293):
  **4,985 groups / 11,352 open instances / 579,571 ins**, warm merges 880, seeded 4,714/6,911 skeletons, all
  assertions green. (Watch-for confirmed live: my own `pgrep -f atlas` waiter self-matched its shell wrapper —
  the bracket trick is mandatory.)
- 2026-08-16 — **S53-2 LEFTOVER-DRAFT HARVEST (R38: read the recorded verdicts before designing anything).**
  `.run/s53_scan_leftovers.py` re-verified every wave-P/Q main draft on disk with `match_one` rather than
  trusting the journals (R14). Of 141 drafts: **72 are already banked** (their `.s` is gone — the honest
  signal that splat stops emitting a matched function), **34 still verify MATCH and are still stubs**
  (3,075 ins of finished work nobody had banked), **35 are NEAR**. Oracle cross-check: all 34 MATCH and all
  35 NEAR are in `corpus.stubs('main')`; all 72 ERROR are not. Zero agent tokens.
- 2026-08-16 — **S53-3 PRE-GATE LADDER ON THE FREE SLATE (the S52 protocol, applied cold).** `reloc_identity
  --batch`: **33 AGREE / 1 MISMATCH** (`func_80034C24` names `D_80078F20` where the target references
  `cdReq_sectorHdrBuf+0xE0`; its `--dry-fix` rename to `D_80078F10` is unverified, so it was dropped, not
  guessed). `fragment_check`: **1 FAIL** — `MoveImage` DEFINES `SYS_OBJ_8F4`, a stub that still has its own
  `.s` (exactly the enclosing-function trap that cost wave Q a 3-hour bisect; caught in milliseconds).
  `reconcile_slate --apply` on the pruned 32: **11 compatible, 21 refused as human decisions** (7 TYPE,
  5 SIGNATURE, 3 DIFFERENT-STRUCT, 3 BROKE-MATCH, 1 DEF-SIDE-RETURN, 1 resourceIdMap TYPE, 1 alias).
  **The 11 were NOT gated on their own** — §176h.C2 says banking a subset hardens the rest's conflicts
  (last session: 1 of 18 parked drafts survived that), so all 32 ride one slate after repair.
- 2026-08-16 — **S53-4 WAVE R BUILT — and the main mass band is measurably SPENT.** `build_wave_atlas
  --only-bins main --min-ins 60 --max-ins 200 --rank mass` returned **917 ins / 10 cards** against a 6,500
  target: waves O/P/Q consumed main's mass band. Probes (R37 before costing): main widened to 30–400 yields
  44 cards / 4,600 ins in 10 gate groups; **fleet-wide 60–200 yields 63 cards / 6,525 ins in exactly 2 gate
  groups = 31.5 drafts per rebuild**, from a 1,546-candidate well. Wave R therefore = the fleet-wide draw
  (`ov_SC06_029` ×41, `ov_SC02_005` ×22) + main's last 10 mass cards, **7,442 ins across 73 fresh cards**.
- 2026-08-16 — **S53-5 WAVE R LAUNCHED (110 agents, 3 lanes, run `wf_c070b4fa-53b`).** Lane 1 = 73 fresh
  mass cracks. Lane 2 = the 21 declaration-blocked drafts (already byte-MATCH; the agent's job is to make the
  DRAFT agree with the TU, never the reverse, then re-verify — a declaration change is a codegen change).
  Lane 3 = 16 near-miss repairs, whose residuals were classified deterministically first: **10 of 16 are the
  §177 epilogue signature** (`addiu $sp / jr $ra / nop` vs `jr $ra / addiu $sp`, all in `800c3`), 4
  SCHEDULE-REORDER, 1 BRANCH-POLARITY, 1 OPCODE-MIXED. The prompt carries §177 as law 4 and §178's
  "REGALLOC-PERM is the most over-diagnosed class" as law 5.

- 2026-08-16 — **S53-6 WAVE R DRAFTED: 92/110 MATCH (84%), 0 agent errors, 134 agents.** Per lane:
  **mass 68/73 (93%)** · **plumbing 20/21 (95%)** · **near-miss 4/16 (25%)**. 5 IMMOVABLE, 13 NEAR.
  Two of the IMMOVABLEs are real structural findings, not failures: `gfx2D_BG1_OBJ_648` is the shared
  tail of `GsSortFastBg` (no prologue; branched into three times by raw `bnez`/`j`), and `vmNoiseOn`
  is one compiled function the splitter cut into **seven** glabels (one prologue at `0x800403A4`, its
  only matching epilogue in `VM_NO1_OBJ_4A4`, plain `j` at every hop). Both need a TU-level merge, not
  a draft.
- 2026-08-16 — **S53-7 BANKED 75 FUNCTIONS / 7,400 INSTRUCTIONS.** main **18** (stubs 1,763 → 1,745,
  EXE `143dbb89` byte-identical) · `ov_SC06_029` **36 of 41** · `ov_SC02_005` **21 of 26**.
  **R22 clean-fleet after: `check-all` 213 passed, 0 failed of 213.**
- 2026-08-16 — **S53-8 THE GATE'S REJECTION CENSUS (cookbook §181) — 26 of 27 blocked main drafts are
  byte-correct.** Five classes, four of which the whole C-level ladder is blind to: **MIRROR-FRAGMENT**
  ×2 (a sibling branches to a `.L` label *inside* the function; only the linker knows) · duplicate
  typedef with the TU's copy BELOW the insertion point ×7 (`gate_main` reuses only definitions ABOVE,
  so it keeps the draft's and C89 rejects the pair) · draft-vs-draft data-symbol type clash ×1
  (`ClearOTag` says `u32 D_80072784`, `SetGraphQueue` says function pointer) · draft-vs-file signature
  conflict ×4 · **genuinely byte-wrong ×1** (`SYS_OBJ_1DC0`). `bisect_slate` found that one in
  **5 steps / 90 s** at 13 s per build — against `gate_main`'s built-in bisect's 3 hours and no answer.
- 2026-08-16 — **S53-9 TOOLS: the mirror test now exists.** `fragment_check.branched_into()` refuses a
  draft that owns a label a still-stubbed sibling branches to; negative-controlled on both known-bad
  drafts, then measured: **99 of 1,745 main stubs (5.7%)** carry this hazard, **0 of 229** in
  `ov_SC04_011` and **0 of 194** in `ov_SC03_028` — a main-specific trap at ~1 in 18. Also fixed
  `pregate_check` to scan comment-MASKED text (`_typedefs(text)` counted a typedef quoted in a bank
  note as a definition; negative-controlled three ways). Cookbook **§180/§180d/§181/§182** banked.

- 2026-08-16 — **S53-10 THE RECOVERY BACKLOG WORKED: 15 of the 27 blocked drafts banked, and the
  blockers turned into TOOLING.** A 20-agent lane reconciled 18/20 while keeping the match; the gate
  then took them in three rounds as each fix exposed the next layer. Banked: 3 (typedef hoist) + 10
  (declaration reconciliation) + 2 (byte-neutral TU edits) + 2 (forward-typedef fix) = **17 more main
  functions this session** (stubs 1,763 → 1,728). Every gate green at `143dbb89`.
- 2026-08-16 — **S53-11 FOUR TOOL DEFECTS FIXED, ALL FOUND BY THE WORK ITSELF (§184/§185).**
  (a) **Comment-blindness in THREE tools** — `pregate_check._typedefs` scanned raw text (a typedef
  quoted in a bank note counted as a definition), `reconcile_slate._same_struct` and
  `gate_main.strip_dup_typedefs` compared body TEXT (so `Slot16B` vs `Slot16` — same seven fields —
  read as DIFFERENT-STRUCT, and an identical struct got renamed into a conflict). Agents annotate
  every field with its address; the TU does not. All three now mask comments; negative-controlled.
  (b) **The forward typedef** — `typedef struct X X;` is not a competing definition; renaming it
  manufactured the very extern conflict it was meant to avoid. Recognized and stripped now.
  (c) **`gate_main` hoists TU typedefs** above the include block (with a dependency closure) so a
  draft above the TU's definition can reuse it — **proven byte-neutral by the SHA**, 5–10 typedefs
  moved per gate.
  (d) **`pregate_check` recalibrated**: ANY return-type disagreement now FAILs (`G4P *` under a
  `G3P *` declaration was rejected by gcc after the tool WARNed), and it now sees brace-bodied
  externs (`extern struct { ... } *D_x;` vs `void *` — the clash that cost a rebuild).
- 2026-08-16 — **S53-12 THREE TU RETYPES PROVEN BYTE-NEUTRAL, ONE REFUTED (§185).** `func_8001ABBC`
  `void`→`s32`; `W16 D_80076240`→`Slot16A[]`; `W32 D_8007622C`→`s32[]` — each verified by a clean
  rebuild at `143dbb89`. **REFUTED:** `s16 D_800C5328[]`→`[][2]` compiles at the declaration and then
  breaks **four banked assignments** in two other functions. The rule that fell out: a TU retype is
  byte-neutral only if every existing USE SITE still compiles unchanged — and prefer editing the
  draft, which verifies in seconds, over the TU, which costs a rebuild and risks the whole file.

- 2026-08-18 — **WAVE W: 71/71 drafted, 68 banked in THREE gate groups — and the draw exposed that the
  SELECTOR had been overriding the DOCTRINE.** The first draw came up short (63 cards / 5,647 ins /
  10 groups, continuing 5 -> 7 -> 9), so I probed the atlas instead of accepting it: **UNKNOWN held
  607 of the 1,179 in-band members — more than every other lane COMBINED — and
  `build_wave_atlas`'s default `--levers` excluded it**, while the wave PROMPT tells every agent
  "UNKNOWN does NOT mean hard — it means the atlas could not name a lever ... UNKNOWN cards draft
  like any other lane (measured across waves O-S)". Redrawn with UNKNOWN in: **73 cards / 6,500 ins
  in 3 GATE GROUPS = 24.3 drafts per rebuild** (T 14.2 · U 10.4 · V 7.8). Result: **71/71 of the
  agents that ran matched** (2 died on server rate-limiting and are released back to the pool),
  **68 banked** (ov_SC03_105 26/26 · md_SC07_004 34/36 · ov_SC06_006 8/8 — the first MODULE binary
  drafted this session). UNKNOWN is now a DEFAULT lane (§198). **Recorded cost: zero siblings** —
  UNKNOWN groups are mostly singletons, so the free remap that gave T/U/V 49/34/25 gave W nothing.
  Concentration and sibling mass trade against each other; pick per wave.

- 2026-08-18 — **§196 `decl_prior`: the card now carries the fleet's declaration consensus.** Chosen
  by measurement, not intuition: wave V's tokens are **88.3% drafting / 8.4% repair / 3.2% reconcile**
  at **9.3 match_one compiles per agent**, so the lever is what a drafter must GUESS before its first
  compile. Two such guesses are answered in the tree — callee arity/return type (§195-A: the asm has
  NO tell either way, the procedure is a two-arity A/B) and global type (every CONFLICTING-EXTERN
  drop). `tools/decl_prior.py` indexes 4,162 files -> **67,094 symbols** (9,739 with a banked
  DEFINITION); cards carry the rows for their own target's symbols, ranked DEF > TU (authoritative,
  law 2) > FLEET modal + rivals with counts. I did NOT build the offset-width prior I first sketched:
  the `.s` already gives access width unambiguously (`lh`/`lhu`/`lw`), so it would have been
  redundant. Structs deferred to the readability pass per Drew.

- 2026-08-18 — **§197 harvest (4 confirmed / 3 rejected / 41 already-covered), and one entry is banked
  CONTESTED.** Two verifiers confirmed the same phenomenon (`lhu ; sll 16 ; sra 16+K` where the
  target has `lh ; sra K`) and attributed it to DIFFERENT passes — cse's `fold_rtx` associative block
  (with `-da` dumps showing the middle insn already gone in `x.i.cse`) vs combine preferring the
  count-merge. R34 forbids reading agreement between disagreeing oracles as corroboration, so the
  tell and the cure (a zero-byte asm re-tie; a FRESH TEMP works with no second SET at all) are banked
  and the pass question is recorded open. Both verifiers independently **byte-refuted §136 type-form
  rule 9's cure**: `u16 v[4]` and `SVECTOR v` compile byte-identically in rule 9's own context.

- 2026-08-18 — **WAVE X: 64/65 drafted, 62 banked in 4 gate groups; UNKNOWN confirmed as a lane on its
  second wave.** md_SC07_003 24/24 · ov_SC06_016 18/18 · ov_SC06_025 19/20 · ov_SC03_001 1/1. A SECOND
  module binary went clean. Sibling remap 1 (UNKNOWN groups are singletons — the recorded cost of the
  lane). R22 **213/213** from a clean tree. **Fleet crossed 96.0% instr-weighted** (91.6% distinct,
  97.05% fn-count). The one near-miss, `func_8017F9D8`, sits at **closeness 1** — 93 of 94 words
  byte-identical, a branch landing one instruction early — and its agent got there from 21 by reading
  each delay slot as a PROVENANCE fact (§194-M) rather than as scheduling noise: a `bgtz` + filler
  that moved BACKWARD proves the statement DOMINATES the branch, so it belongs above the test, not
  inside the arm. The session's own harvest being used mid-wave.

- 2026-08-18 — **§199 harvest (7 confirmed / 2 rejected / 56 already-covered) — and it BYTE-REFUTES
  §189-A, banked this morning.** §189-A claimed an interloper between a split constant's `lui`/`ori`
  PROVES two source steps. Four independent refutations: the banked one-statement slice
  `prim.col[1] = 0x101010;` compiles with SEVEN insns in the gap; the prescribed two-step spelling is
  BYTE-IDENTICAL (the fix is inert); moving an unrelated statement moves a third constant in and out
  of the gap; and one separated pair is `0x88888889` — gcc's own reciprocal magic for `/ 0x3C`, a
  constant with NO source spelling, so the inference is unsatisfiable there. Mechanism corrected off
  cc1's `-dS`: `rank_for_schedule` tests INSN_PRIORITY FIRST (`sched.c:2395`), the LUID tie-break is
  last (`:2428`), and the separator is the BIRTHING BOOST (`birthing_insn_p`, gate `reg_n_sets == 1`)
  which the split pair can never have because `try_split` gives its pseudo two sets. The dump also
  corrected the READER: sched1 is a BACKWARD scheduler, so the LUI sinks, not the ORI. §189-A's
  split-TIMING half survives and carries a banner. **Two of the seven laws correct laws from earlier
  the same day — that is the adversarial verifier paying for itself.**

- 2026-08-18 — **Usage-limit recovery, third use, reliable.** The wave-X harvest died mid-flight with
  3 verifiers outstanding. `Workflow({scriptPath, resumeFromRunId, args})` replayed 10 finished agents
  from cache and re-ran only the 3: **398k tokens against the original run's 1.31M**.

- 2026-08-18 — **WAVE Y: 69/70 drafted, 72 banked (64 gate + 4 recovery + 4 siblings).** Groups:
  ov_SC03_007 20/21 · ov_SC03_121 14/14 · ov_SC02_017 15/19 · ov_SC03_001 12/12 · ov_SC05_018 3/3.
  R22 **213/213** twice (before and after the recovery lane). Fleet **96.0% instr-weighted · 91.7%
  distinct · 97.07% fn-count**. One reconcile agent died on a server error, so I built that group's
  slate from the drafts on disk and ran the ladder by hand — which is exactly why the Reconcile
  phase's product is a FILE, not an agent return value.

- 2026-08-18 — **§200 — THE ALIAS IS THE UNIVERSAL DECLARATION ESCAPE, and it was found because the
  API went down.** Wave Y's recovery lane lost 12 agents to two rounds of 529 Overloaded (0 tokens),
  so the five gate drops were fixed BY HAND — and five different refusal classes turned out to need
  ONE move. §183's playbook negotiates with the TU's spelling; §200 declines to share the C
  identifier at all: only the LINK name has to agree, so bind a private identifier to the symbol with
  gcc's asm label (§37/§124). `extern u8 aD8018A800[] __asm__("D_8018A800");`. Classes recovered:
  array-vs-scalar where `reconcile_slate`'s own array fix had BROKEN the match · a slate-mate's
  private struct · `void *` vs `s32` · and TWO DEF-side return conflicts (one of them a function
  whose only in-TU use takes its ADDRESS as a callback) — the case §183.3 says has no cast escape.
  All five still MATCH; 4 re-gated and banked. **Ordering recorded so it stays an escape hatch:**
  adopt the TU's spelling → cast at the use site → alias. Every alias in the tree carries a comment
  naming the spelling it could not use.

- 2026-08-18 — **THIRD INSTANCE OF THE §192 CLASS, on our own idiom.** `sym_of` returned `__asm__` as
  the symbol for every asm-label alias (an identifier followed by `(`, matched before the real one),
  so aliased declarations all collided under that name — 1 byte-verified draft DROPPED and 2 phantom
  CONFLICTING-EXTERNs **on the very slate the recovery lane was fixing**. NC over the tree: **1,210
  changed verdicts, 0 regressions**, 899 of them one symbol — the idiom is fleet-wide, so the
  miscount was too. *A project idiom the tools cannot parse is an idiom that silently costs work.*

- 2026-08-18 — **WAVE Z IS BUILT AND STAGED, DELIBERATELY NOT LAUNCHED** (Drew's instruction).
  75 cards / 6,517 ins / **8 gate groups** (9.4 drafts per rebuild) · seed_ref 46 · tu_ref 50 ·
  decl_prior 70 · 43 siblings staged. Binaries: ov_SC02_005 20 · ov_SC01_084 16 · ov_SC05_001 11 ·
  ov_SC03_011 10 · ov_SC03_094 8 · md_MAIN_034 7 · md_SC03_075 2 · ov_SC06_018 1.
  **To fire it:**
      Workflow({scriptPath: ".run/wave_p31z_workflow.js", args: <the object in .run/wave_z_args.json>})
  Cards `.run/wave_z_cards.json`, siblings `.run/wave_z_cards.siblings.json`, wavedir `.run/wave_p31z`.

- 2026-08-18 — **⚠ WAVE Y'S HARVEST IS OUTSTANDING — the API is 529-Overloaded for subagents.** Three
  separate launches lost every agent at spawn (12 recovery + 5 readers), all at zero tokens. The gap
  reports are captured at `.run/wave_y_gaps.json` (67 of them) and the targets are snapshotted at
  `.run/waveY_asm_snapshot/`, so nothing is lost. **Resume with:**
      Workflow({scriptPath: ".run/wave_y_harvest_workflow.js", resumeFromRunId: "wf_ef996308-610",
                args: <the object in .run/wave_y_harvest_args.json>})
  This is the ONLY step of the seven-step wave-closing sequence left undone for wave Y.

- 2026-08-18 — **WAVE Z FIRED AND CLOSED (S56). 127 banked; R22 213/213; fleet 96.1 / 91.8 / 97.11.**
  Wave Z (`wf_3a3c6273-f82`, 75 cards / 6,517 ins / 8 gate groups, 93 agents, 0 errors, 81 min):
  **74/75 standalone MATCH, 0 immovable**, 73 reconciled onto slates, **72 banked on the first gate**.
  - **Recovery, 2 for 2, zero agent tokens.** `func_800CC310` (md_MAIN_034) — `match_one` MATCH but the
    whole-binary gate refused. `reloc_identity` AGREE (13 relocs); a disassembly of the built `.elf`
    read 69/69 identical **and was an artifact** — the draft never compiled, so the `.elf` still held
    the original `INCLUDE_ASM` bytes. **The verdict was already on disk** in
    `.run/harvest_failed.md_MAIN_034.classified.txt`: `PLUMBING: parse error before 'D_800CCAD0'`
    (R38 — reading it first would have cost one command instead of three oracles). Cause: slate-mate
    `func_800CC4E8` banked a `Quad4_800CCB14` typedef, `strip_provided_typedefs` correctly dropped
    `func_800CC310`'s duplicate, and `func_800CC310` splices EARLIER in address order — survivor below
    its uses. First fix (rename to dodge the stripper) was WRONG and the gate caught it: one symbol,
    two types. Hoisting the typedef to the top of the TU banked it (`commit:2558`). Cookbook **§203**.
    **Correction (same session):** the text that banked is the RENAMED variant — `gate_stage`'s
    `backlog.save_draft()` overwrote the original draft on the failed attempt, so "copying the
    original back" copied the rename. Bytes are correct (R22 213/213); the TU carries two names for
    one shape and a transform mangled a COMMENT. A backlog draft path is not a stable original.
    `func_8018280C` (ov_SC05_001) — the reconciler's IMMOVABLE §183.3 DEF-SIDE-RETURN wall (asm proves
    `s32`, TU declares `void` at three sites with live callers). The **§200 alias applied to a
    DEFINITION** — `s32 aF8018280C(s32) __asm__("func_8018280C")` — banked first try (`commit:2559`),
    body untouched. Cookbook **§202**; the idiom existed in-tree only on declarations.
  - **Sibling sweep: 3, then 50 — the difference was MY scoping error, not the tree.** The first
    `family_sweep --hseq` passed the ATLAS gid-exemplar addresses to `--only`, which filters on
    `family_hseq`'s OWN exemplar addr; with the default `--band substantial` that left 2 families / 4
    candidates. Recomputed from the manifest: **59 families contain a wave-Z function, 21 with a
    matched exemplar and 196 open members**. Re-swept `--band all`: **50 banked / 91 failed / 60
    skipped** (45 STRUCT-class, 12 unresolved-immediates, 3 not-stub). §53's "a 0% from the wrong tool
    is not evidence", one level up: **a small yield from a mis-scoped sweep is not evidence either.**
  - **R22 `make check-all` = 213 passed / 0 failed of 213** from a clean tree. dedup-check 2,165/0;
    C1 254,731/254,731; 0 NON_MATCHING in any default build (G4). **Fleet 96.1% instr-weighted /
    91.8% distinct-code / 97.11% fn-count / MAIN 20.5%** (session start 96.0 / 91.7 / 97.07), 10,501
    stubs open. Honest ratio: 74 agent-drafted fns moved instr-weighted ~0.1pt; the 53 mechanical
    siblings cost ~0 tokens. **Draw exemplars that carry siblings.**
  - **Harvest (`wf_5508f6b2-fae`, 16 agents): 82 gap reports -> 30 already-covered, 31 confirmations,
    5 laws, 16 rejected.** The adversarial verifier killed **7 of 12** law claims — two on byte-false
    mechanisms it reproduced itself, five as re-derivations of existing §§. The synthesizer corrected
    three wrong line citations, narrowed §204-A's instruction delta from a claimed +4 to a measured
    +1 by re-running the A/B, and flagged a miscite. **§204 written, 510 lines** (§204-A..E +
    CONFIRMED + REJECTED).
  - **Tooling (all negative-controlled).** (1) **The S46 validity gate was OFF the path for waves T-Z**
    — it lives in `wave_snapshot.py`, which hardcodes `asm/<bin>/nonmatchings/<bin>/` and so found 9 of
    75 split-TU targets; its R32 assertion fired correctly, the snapshot step got hand-rolled, and the
    phantom-target gate went with it. Wired `validate_targets` into **`build_wave_atlas`** where cards
    are BORN (`--allow-invalid` escape), widened `_key` to the card spelling `fn`, and documented the
    PRE-DRAFT-ONLY constraint in the tool: every verdict reads live sig/stub/.s state, so the same
    check after a wave condemns exactly the targets that BANKED (an R39 refusal-check run at the wrong
    moment). (2) `wave_snapshot` now honors the card's `sub` (NC: 9/9 legacy targets byte-identical,
    66/66 split-TU targets recovered). (3) **§204-E fixed**: `decl_prior._ASM_SYM`'s leading `\b`
    bound to the whole alternation, demanding a word boundary before `%` — impossible in a .s — so the
    `%hi/%lo` arm had NEVER fired (0 of 1,210 over four waves). NC over the 75 wave-Z targets: **jal
    306 -> 306, zero regressions; data 0 -> 299 symbols recovered.**
  - **Flow hardening after Drew asked whether the findings were actually wired in (S56).** The audit
    found three gaps beyond the four fixes already committed: (a) **R21 violation — `docs/SETUP.md`
    was not updated**; now carries a "Crack-wave toolchain — the four flow traps" table naming each
    trap, its measured cost and where it is caught. (b) **`family_sweep --only` had no coverage
    assertion**, so my 3-vs-50 mis-scope could recur silently; it now resolves member addrs to their
    family, ALWAYS prints `--only: N addr(s) -> M family(ies) (... K unresolved)`, and REFUSES on zero
    (replaying the exact wave-Z call now prints `15 -> 3, 12 unresolved` instead of quietly sweeping
    nothing). (c) **`pregate_check` modelled the driver's typedef strip but never checked the
    consequence**; it now reports `[DROP-RISK] §203 USE-BEFORE-TYPEDEF` — R39 bidirectional NC: flags
    the known-bad pre-hoist splice, 0 false positives on the post-hoist file and on all 7 other
    wave-Z TUs (its first draft read a typedef named in its own COMMENT as a use, so it searches a
    comment-blanked copy with offsets preserved). Memories: `crack-wave-sweep-map-regen` rewritten
    with the exemplar-vs-member keying, and a new `silently-narrowed-tool-scope` recording all four
    instances as one defect class.
  - Outstanding: `func_8018675C` (ov_SC02_005, closeness 6) — its agent ran ~35 variants and attributed
    the residual to cse.c:5278's unconditional constant-second swap for symbol-valued pointer bases
    (retires "reorder the addends" as a lever). **Permuter fuel, not a hand lever.**

## 🛑 SESSION CHECKPOINT — S59 FINAL (2026-08-24 → 08-25 00:20). Phase 31 CONTINUES. **LANES RUNNING; NOTHING BLOCKED.**

**1,342 banked this session · 140 commits · open stubs 6,575 (main 1,493 · overlay/md 5,082).**
Six lanes alive and self-restarting: drafter · gater · maintenance · stallguard · **distill** (new)
· **main** (new). `tools/campaign_status.py` prints all six with their own metrics — **use it for
every status check**; reporting only the loud lanes is how two of this session's bugs hid for hours.

### THE SESSION'S ONE LESSON, MEASURED SIX TIMES
**Every lane that looked like "the models can't crack these" was a HARNESS defect.** In order found:
1. `match_one --o0` existed for a year and **nothing ever passed it** — agents were shown an -O2
   compile of their own C. Fixed → an agent then banked a 131-ins -O0 function on the FIRST compile.
2. The **tells** lane was retired on a lane verdict that was really a card-SIZE verdict.
3. The **jtbl** carve machinery had existed since Phase 29; nothing handed it a draft.
4. The **main** lane's 737 drafts banked zero because the committed BASELINE was red — with no draft
   substituted, main built the wrong hash. Every rejection was a false verdict.
5. **44-72% of shards per wave died at turn 1 on a SOFT 429** — HTTP 200 whose body carried
   `{"code": 429}`. The retry path keyed on the envelope. One wave logged **202 retries** the moment
   it could see them. It had read as "poor draft completion", and I wrongly blamed the straggler grace.
6. The **A-prop** lane staged 82 hopeless drafts of 117 because it read one bit of one verdict
   (reloc `status==AGREE`, ignoring `shape`).

### WHAT LANDED (all byte-proven; commits named in the docs)
* **jtbl**: the §154-A island split works — ONE config line + `jr_isolate_all --only`, with the
  object-level `sh_size` control a green SHA cannot give (§260). The lane is automated at the gate
  and byte-proven ×3, one per class; 181 members / 26,445 ins reachable unattended.
* **-O0**: census corrected (167 real, not 311 `$fp` mentions); `md_MAIN_011` compiles -O0 via ONE
  Makefile line (21 fns / 4,321 ins unlocked); `corpus.o0_subseg()` derives -O0-ness from the
  Makefile, never a name (§261, §261a).
* **main lane** (new): its own draft→gate→commit cadence, baseline-asserted every cycle, bisecting
  compile conflicts. **Open main stubs 1,713 → 1,493.**
* **distill lane** (new): the flywheel's second half beside drafting; §265-§269 landed from two
  batches. Reviewer tier is **Opus/Sonnet, never Fable**.
* **Fleet hygiene**: two RED binaries found and fixed (`ov_SC07_010` never-built commit;
  `ov_SC07_002` stale 2-table jtbl pad spec), and the maintenance lane now runs a **periodic fleet
  R22** every 4th pass — it reports and FIXES NOTHING.
* **Throughput**: MAXTOK 16k + HTTP_TIMEOUT 700 (one setting, probed: ox is 1M context / 131,072 max
  completion at ~30 tok/s); tells and jtbl are QUOTAS inside ordinary waves; the draw excludes
  mid-gate binaries instead of refusing; the drafter never blocks on the draw lock.
* **Docs**: `docs/portable-decomp-workflow.md` (NEW — the part that transfers, for the public
  deliverable), the automation runbook rewritten from two months stale, accelerators #5/#6.

### RULE CANDIDATES FOR PHASEEND (P10 — Drew accepts, modifies or rejects)
* **R44 — a card may not name a lever the knowledge base does not contain.** 108 transcripts grepped
  `extend-tell` against a cookbook containing that string zero times.
* **R45 — draw-time bankability: never draw a card the pipeline cannot bank.** 11 -O0 functions drawn
  79 times across 19 waves; none could ever have banked.
* **R46 — a budget is part of the harness, not a constant.** One turn/cost cap across card sizes that
  differ 2.4× starved the large ones.
* **R47 — CONSUME EVERY VERDICT LAYER.** A stage that reads one bit of one oracle stages garbage
  forever: 82 of 117 A-prop drafts were shape-DIFF and rebuilt every 45 minutes.
* **R48 — NEVER KEY BY BARE FUNCTION NAME.** Three fn-keyed collision defects in one session,
  including a scratch dir one concurrent run `rm -rf`'d out from under another.
* **R49 — A SOFT ERROR INSIDE A SUCCESS ENVELOPE IS STILL THAT ERROR.** The soft 429 (200 + code 429)
  and `gate_main`'s `clean_build` reading rc≠0 as "no binary" are the same defect.
* **R50 — PERIODIC WHOLE-FLEET VERIFICATION.** A byte gate is silent about every binary it did not
  build; two sat RED for hours.

### OPEN THREADS (ranked)
1. **`cf` is the first wave drafted with the soft-429 fix** — its completion and bank rate are the
   honest read on every throughput change today. Everything before it is contaminated.
2. **A-prop residual, named and sized** (`docs/tool-designs/aprop-lane-s59.md`): 169 STRUCT real
   cracks · 121 no-decl-anywhere · ~73 IMM tier-2 · 8 wrong-family · 12 stubborn near-0s.
3. **-O0 U2/U3** — `rollout_o0.py` SC07 fix (4 fns), the ×3 `jr_801380E0` carve+remap (54 fns /
   6,414 ins, zero drafting). **Draft-first ordering is what makes carves safe: populated-at-carve
   is 137/137; stubs-in-new-object was 1/4 and 2/2.**
4. **tells 6.3/6.5/6.6** — tell COUNTS on the card, the post-wave permuter/§173 recovery pass, and
   routing extend-tell ≥80 ins to `idiom_serial` (never once run on tells).
5. **The distill batch `axbm.json`** is still parked for review.

### HOW TO RESUME
`tools/campaign_status.py` first. Then: `git status --porcelain -- src/ config/` — if dirty,
**COMMIT it, never revert** (R42). Lane changes take effect on three different clocks — draw
defaults next draw, tool code next invocation, lane args/env only on a fresh SHELL — see
`docs/automation-runbook.md` §3 and the restart helpers in `tools/lanes/`. **Verify from the
process (`/proc/<pid>/cmdline`, `/proc/<pid>/environ`), never from the file you edited.**

---

## 🛑 SESSION CHECKPOINT — S59 (2026-08-24 ~12:50). Phase 31 CONTINUES. **AGENTS RETURNED; EVERY FIX LANDED.**

**All three Fable agents completed and every claim was re-verified against the bytes by the main
loop (each binary rebuilt under its own gate lock).** 4 functions banked by the agents; the
campaign banked 145 more (waves bk 110, bl 35) while they worked, undisturbed.

### THE ANSWER TO "CAN THE WAVES DRAW AND BANK EACH TYPE NOW"
| type | drawn by waves? | banks? | mechanism |
|---|---|---|---|
| **default** | yes | yes | unchanged |
| **cc1** | **yes (new)** | yes | never a structural blocker — it recorded a past compile failure |
| **tells** | yes, band 5-80 | yes | + the LEVER_CRIB on the card, the §172b grep aliases, 40 turns / $0.40 |
| **jtbl** | **yes (new)** — 6/wave via `--jtbl-quota` | yes, gate-time carve | probe-filtered to reachable members, ONE per binary (§61c), main excluded |
| **-O0, in an -O0 object** | **yes** (50, incl. md_MAIN_011's 21) | yes | `match_one` auto-selects -O0; the Makefile is now the oracle, not the name |
| **-O0, stranded in -O2** | **deliberately refused** | no | unbankable by construction until U2/U3/U5 land — the draw says `o0-in-an-O2-object` |

### WHAT LANDED AFTER THE AGENTS RETURNED
* **tells** (`commit:2667`): `LEVER_CRIB` in `api_agent._fuel` (what each tell MEANS, the § to grep,
  the byte-proven C spellings) · a **LANE ALIASES grep-bait block at §172b** — the card named a word
  the 750-section cookbook contained **zero times**, and 108 failure transcripts grepped it for
  nothing · `LANE_BUDGET` = 40 turns / $0.40 for tells (98 of 270 attempts had ended AT the 24-turn
  cap on cards 2.4x the default size) · two new SYS laws (grep the crib's §; stop when the class
  says `[permuter]`) · cookbook **§264** = the four recipes the agent drove to MATCH, including two
  NEW laws (save-order = a bb0 anti-dependence; an opaque bound must be a LATE-assigned local).
* **-O0** (`commit:2669`): **md_MAIN_011 now compiles -O0** — whole-object override, the boot
  precedent, no carve, no §18-P29 risk. Byte-proven by a CLEAN per-binary rebuild:
  `sha1 80731bac0ddd6b3e354f43b2c179582b12590752`. Landed with its coupling fix: three tools decided
  -O0-ness from the subseg NAME, and this object keeps its plain name, so `corpus.o0_subseg()` now
  derives it from the Makefile (R33). Verified end to end — match_one compiles those targets -O0
  with the cannot-bank warning correctly gone, and the draw emits cards for them.
* **jtbl** (`commit:2670`): the lever alone was **inert** — jtbl cards are one-per-binary by
  construction, so they are maximally un-concentrated and the gate-group ranking (which exists to
  pack drafts behind one rebuild) selected **0 of 71** candidates. `--jtbl-quota 6` seeds them
  before the ranked fill. Measured: 6 jtbl cards in a 200-card wave, 13,470 ins across 7 gate groups
  (was 11,451 in 1).
* **§263** (`commit:2666`): the `func_801F218C` residual I could not close was an **ARITY error**, not
  a schedule — I had given a no-argument callee a parameter, so the copy had to dominate the call
  and the delay-slot filler took it. `func_801EF6E4(a0)` → `func_801EF6E4()` = MATCH (83 ins). The
  §5a fence (both placements), if/else inversion, an early-break form and a 1,200 s permuter at -j12
  had all failed, because **the permuter cannot change call arity**.

### RULE CANDIDATES FOR PHASEEND (P10 — Drew accepts, modifies or rejects)
* **R44 — A CARD MAY NOT NAME A LEVER THE KNOWLEDGE BASE DOES NOT CONTAIN.** Fuel a drafter cannot
  look up is a dead end that costs a grep and buys nothing; 108 transcripts proved it. Any label put
  on a card must resolve to a cookbook § by the words on the card itself.
* **R45 — DRAW-TIME BANKABILITY: never draw a card the pipeline cannot bank.** R43 for the wave
  draw. Measured: 11 -O0 functions drawn 79 times across 19 waves, none bankable; and jtbl members
  whose table the gate cannot reach. Each failure then looks ordinary and is attributed to the model.
* **R46 — A BUDGET IS PART OF THE HARNESS, NOT A CONSTANT.** One turn/cost cap across card sizes
  that differ 2.4x starves the large ones: 36% of tells failures ended at a cap, not at a wall.

### STILL OPEN (ranked, from the agents' docs)
1. **-O0 U2** — `rollout_o0.py` SC07 fix (~15 lines, 4 fns / 316 ins, zero drafting).
2. **-O0 U3** — the ×3 `jr_801380E0`/`jr_8013F350` carve+remap (54 fns / 6,414 ins, zero drafting;
   ov_SC01_077 already has all 16 exemplars matched). **Draft-first ordering is what makes carves
   safe: stubs-in-new-object scored 1/4 and 2/2 historically; populated-at-carve is 137/137.**
3. **tells 6.3/6.5/6.6** — tell COUNTS on the card; the post-wave permuter + §173 recovery pass
   (16 permuter candidates and 34 shape-MATCH strays are waiting); route extend-tell ≥80 ins to
   `idiom_serial` (never once run on tells) instead of drafting the band wide.
4. **jtbl** — the 10 island-blocked members convert as the island stack peels; the 6 island-pads
   members need §8e pads wired for modules.mk.

---

## 🛑 SESSION CHECKPOINT — S59 LIVE (2026-08-24 ~11:45). Phase 31 CONTINUES. **THREE FABLE AGENTS IN FLIGHT.**

**HEAD `commit:2656` · autonomous lanes RUNNING (drafter · gater · maintenance · stallguard, ~130
agents) · `src/`+`config/` carry live campaign work — COMMIT IT, NEVER REVERT (R42).**

### WHAT S59 DID — the S58 handoff's three tooling lanes, worked to a verdict each

**LANE 4 (jtbl) — the §154-A island split is BYTE-PROVEN.** `md_SC03_076` / `func_801F218C`, exactly
as the adversarial review prescribed: one inserted `- [0x268, .rodata, md_SC03_076_jr_801F218C]`
plus `jr_isolate_all.py --only`. No `_pre` piece, no `ld_interleave` change, island piece untouched.
Clean rebuild (build dirs deleted → re-extract → rebuild): `sha1 9a165e36…` BYTE-IDENTICAL, and the
object-level control that a green SHA alone cannot give — `md_SC03_076.o` `.rodata` 0x27c→**0x268**,
new jr object **0x14**. Four md_*-blindness fixes made it possible:
* `jtbl_carve.parse_config` implements its documented contract at last (it took the FIRST
  data/.rodata piece; on the 42 md_* configs that is the leading island, so `apply()` DELETED the
  `c` line and corrupted the yaml on disk). `tools/test_jtbl_parse_config.py`: 171/171 non-md
  unchanged, 42/42 md_* now keep their `c` line. **main was never in that corruption class** — its
  defects were the config path (`splat.us.exe.yaml`), the file base (0x8000F800, not 0x80010000) and
  the asm tree (`asm/nonmatchings/800/`, not `asm/main/`). All three fixed; main now reaches the real
  analysis and refuses correctly (`func_8001A114`: subseg `800` would host non-contiguous carves).
* `jr_isolate_all.rodata_carves` no longer reads the leading island as a carve (it aborted
  `UNOWNED 0x801ef468`; discriminator verified over all 213 configs).
* Cookbook **§260** carries the recipe + the island-is-a-stack census (only the END-adjacent table
  carves cheaply; each isolation exposes the next).
* **Open:** `func_801F218C` is ONE instruction from banking — gcc schedules `addu $a0,$s0,$zero`
  into a `jal` delay slot the target leaves as `nop`. §5a fence both sides, if/else inversion,
  early-break form and a 1200s permuter at -j12 all failed. Logged to the backlog (closeness 1,
  DELAY-SLOT) with the lever list, so the grinder keeps at it.

**LANE 3 (o0/cc1) — answered with a census.** 167 of 14,400 `.s` files carry the real -O0 prologue;
the handoff's "311 `$fp` files" over-counts (`$fp` is `$s8`, allocatable at -O2). 51 sit in -O0
objects; **116 / 14,148 ins are stranded in -O2 subsegs and cannot bank at all** — more than double
the atlas estimate, with x2/x3/x4 sibling replication. **The handoff's refutation of md_MAIN_003/011
is itself WRONG** (16 and 21 -O0 functions, byte-verified) and is now marked so in the design doc.
Two fixes landed: `match_one` derives the opt level from the target (prologue tell OR -O0 subseg) —
`--o0` existed and NOTHING ever passed it, so every agent handed an -O0 target saw an -O2 compile of
its own C, a mismatch on every instruction and no way to converge; and `build_wave_atlas` now
refuses to DRAW a stranded -O0 function (measured: 11 of them drawn **79 times across 19 waves**,
~6 per wave, under head-crack/UNKNOWN/tells/len-vein/redraft labels, none of which could ever bank —
a live draw now reports `o0-in-an-O2-object: 54`). `cc1` joined the default lever list: it records a
past compile failure, not a structural blocker. Cookbook **§261**.

**LANE 1 (tells) — the removal measured the population, not the lever.** All four waves S58 cited
ran at band 120-2000. Bank rate by size, from each wave's cards joined to the functions its own
commit banked: 0-50 default 57% / tells 40% · 50-80 30%/27% · 80-120 22%/10% · 120-200 3%/1% ·
200+ 6%/0%. Tells cards are median 89-95 ins vs default's 37-39 (2.4x). Tells is restored and pinned
to band **5-80**; the large band always goes to `default`. **§235 (phantom symbol) is REFUTED** as
the tells cause — among MISMATCH? rows the shape-already-matched fraction is 6/66, 4/81, 5/47 on
tells vs 25/87, 16/79, 17/66, 13/57 on default: tells drafts fail on the BODY. Wave `bi` confirmed
the band diagnosis live: tells @120-2000, **0 banked of 50 drafts**. Cookbook **§262**.

### IN FLIGHT — THREE FABLE AGENTS (launched ~11:45; results NOT yet on disk)
| agent | asked for | deliverable |
|---|---|---|
| tells | residual taxonomy from the drafts on disk, the idioms drafters lack, card/prompt changes, honest 75% verdict | `docs/tool-designs/tells-lane-s59.md` (proposes diffs only) |
| o0 | per-sub-population bankability, whether we can write -O0-matching C at all (byte-proven crack), serial-vs-wave, worth-it verdict | `docs/tool-designs/o0-path-s59.md` (proposes diffs only) |
| jtbl | AUTOMATE carve→draft→bank, prove on two targets, name the campaign hook | `docs/tool-designs/jtbl-automation-s59.md` + implementation + commits |

**If this session died before they returned:** their docs may or may not exist — check
`docs/tool-designs/*-s59.md` and `git log`. Re-spawning is cheap; the briefs are in the S59
transcript and every fact they were given is in this checkpoint.

### OPS LAW LEARNED (docs/accelerators.md #5)
**A running lane script does not read your edit.** bash parses `while … done` in full before
executing, so a lane-ARG change is invisible to the running shell and a python bounce re-runs the
OLD command line (measured: an 18-minute-old edit was invisible until the shell restarted). Code
changes (`tools/*.py`) → a bounce suffices. Arg changes (`.sh`) → fresh shell, via
`tools/lanes/relaunch_drafter_shell.sh`, which waits for a wave to queue so no drafts are lost.
Wave-draw defaults (`build_wave_atlas.py`) → next draw, no restart at all.

### STANDING VERIFICATION
`md_SC03_076` re-verified byte-identical from a CLEAN per-binary rebuild (R22 scoped to the binary I
touched — a fleet `make clean` is unsafe while gates are building). No fleet R22 run this session;
the campaign's own gates carry it.

---

## 🛑 CRASH-RECOVERY CHECKPOINT — S58 LIVE (2026-08-24 00:2x). Phase 31 CONTINUES. **WORK IS IN FLIGHT.**

**This is NOT a fresh-session handoff — it is a crash-recovery snapshot.** Autonomous lanes are
RUNNING right now. If you are reading this after a crash, the first question is not "what next"
but "what is still alive" — see RESTART below.

**HEAD `commit:2600` · 1,790 functions banked today across 36 commits · 7,581 open overlay/md/resident
stubs · tree clean · R22 last verified GREEN 213/213 at `commit:2587` (re-verify before trusting).**

### WHAT IS RUNNING (all `setsid`-detached, all self-restarting)
| lane | script | role |
|---|---|---|
| drafter | `.run/drafter.sh` | draw → shard → draft → queue a ready marker, forever. **NEVER stop this to ship a code change** (that cost 139 of 162 idle minutes on 2026-08-23) |
| gater | `.run/gater.sh` | reloc pre-filter → gate → commit → harvest → ledger. Safe to kill/restart |
| maintenance | `.run/maintenance.sh` | the FREE A-prop sibling lane whenever the gater is idle; zero model tokens |
| stallguard | `.run/stallguard.sh` | 60s cycle: revive a dead lane shell, kill agents silent >20min, kill a gate >90min, bounce an idle drafter |
| toolwork | `.run/toolwork.sh` | 2 ox agents designing the jtbl island-split and the o0/cc1 lanes (read-only) |

Stop everything cleanly: `touch .run/ox_campaign.stop`. A 5-minute cron (`271eadf8`) checks the lanes.

### RESTART AFTER A CRASH, IN THIS ORDER
1. `git status --porcelain -- src/ config/` — if dirty, **COMMIT it, never revert** (R42). A dirty
   `src/` after a crash is usually banked work a gate had not committed yet. The one safe revert is
   `src/800.c`/`src/800c.c` alone when a `gate_main` was interrupted mid-substitution.
2. Salvage drafts: `find .run/wave_* -name '*.c' | wc -l` — drafts survive crashes and are worth
   re-gating via `ox_campaign.py --gate-only <tag>` before drafting anything new.
3. Relaunch: `setsid nohup .run/drafter.sh >> .run/drafter.log 2>&1 </dev/null &` then the same for
   `gater.sh`, `maintenance.sh`, `stallguard.sh`. Verify from the STARTUP BANNER, not the config file
   (a `#` between backslash-continued args silently drops them all — see `docs/accelerators.md`).
4. Drafting is the clock-limited resource (ox is free for ~3 more days) — start it FIRST, do
   bookkeeping while it runs.

### FLEET / SCALING, AS MEASURED
* **1,720 ox + 280 deepseek**, 3,000-card waves. Shard count tracks CARDS, not the config: a
  818-card wave runs 818 shards however many are configured. **Card supply is the binding constraint.**
* ox 429s are **launch burst only** — 961 of 964 landed in the first 5-minute bucket when 818 shards
  fired at once; every later bucket 0.0%. Startup is now staggered. **Not a capacity ceiling.**
* Agent RSS ~10 MB steady (the 39 MB figure was a startup snapshot). WSL raised 32→48 GB via
  `/mnt/c/Users/user/.wslconfig`; 45 GB available carries thousands, not hundreds.
* deepseek's pool has never returned a 429. Zero PLATFORM 429s ever — OpenRouter has not once
  refused this account. Credit ~$16.
* Telemetry: every request and 429 appends to `.run/api_rate.jsonl`; read with `tools/api_rate.py`.

### TOOLS BUILT THIS SESSION
`tools/ox_campaign.py` (drafter/gater split, lane+band rotation, pipelining, main parking,
smallest-ratio model lanes, launch stagger, per-wave harvest) · `tools/idiom_harvest.py` ·
`tools/api_rate.py` · `tools/idiom_serial.py` (serial compounding lane, ov_* jtbl only) ·
`.run/{drafter,gater,maintenance,stallguard,toolwork,sibling_lane}.sh`

### FIXES THAT MUST NOT REGRESS
* `atlas.py` `_CONF_RANK` needs `aprop-pure` — without it atlas.py cannot run AT ALL, and the
  `remap` lever (235 groups / 46,240 ins) is invisible.
* `validate_targets` prefers the card's own `addr` — name-slicing made every NAMED symbol MALFORMED
  and discarded whole 220-card waves.
* `sweep_parallel` REFUSES main (R43). `gate_main` holds `.run/auto/gate.main.lock` (R42 companion).
* `api_agent`: 5xx retried like 429; `HTTP_TIMEOUT` 420s not 1800; `EXTRA_READABLE` widens the
  read surface for tooling briefs; bare-directory paths no longer refused.
* `ox_campaign.gate()` COMMITS a dirty tree, never reverts (R42).

### THE WORK QUEUE (ordered, and why)
1. **jtbl/o0/cc1 tooling** — the two ox study agents return DESIGNS; a Fable agent validates each
   design before implementation; then WE write the tool and verify on **2 examples per tool** before
   it joins the toolset; then cards that exercise it, end-to-end, before autonomy resumes.
   Population: jtbl 177 groups / 36,685 ins (169 of 245 members are ov_*, where the carve works;
   150 of 177 groups are SINGLETONS so there is little family leverage) · o0 6,564 ins · cc1 6,511.
2. **main** — 157 drafts parked in `.run/main_queue/`, ~1,041 open stubs. Its gate is a clean whole-EXE
   rebuild that bisects on failure: 39 min unfinished on 29 drafts, 25 min on 8, 65+ min on 8.
   Needs a cheaper gate, not more agents. **~54 h of gate time at current rates = the schedule risk.**
3. **The tells lane** — 86,602 ins, never drawn until now (a rotation counter reset to 0 on every
   restart, so index 1 was never reached). Draws at rotation index 16.
4. **Sibling remap** — use `aprop_autodraft` (synthesizes a minimal preamble), NOT
   `family_sweep --hseq` (carries the seed's decl layer: 0/14 banked on a PURE probe, all PLUMBING).
   527 templatable families / 1,334 members is the tool-verified number; the 5,042 card-file count
   was optimistic.

### HONEST FRONTIER (atlas, before today's ~1,790 banks)
SOLVED lanes 8,607 inst / 352,649 ins · TELLS 1,132 / 86,602 · NEEDS TOOLING 452 / 53,853 ·
other 287 / 6,130. Clean-run pace ~400 banked/hour; today's actual was 1,790 in ~24 h at 53% idle.

---

## 🛑 S58 HANDOFF — THE THREE OPEN TOOLING LANES (jtbl · o0/cc1 · tells)

Written 2026-08-24 with full session context. Each lane below has a STUDY on disk, a VERDICT, and
a named next action. **Read the linked doc before touching the tool** — both studies contain claims
that were checked and refuted, and re-deriving them costs hours.

---

### LANE 4 — jtbl island split · `docs/tool-designs/jtbl-island-split{,-review}.md`

**Population** (atlas): 177 groups / 245 instances / **36,685 ins**. By binary class:
ov 169 · main 47 · md 24 · resident 5. **150 of 177 groups are SINGLETONS** — only 26
multi-member non-md groups exist (6,294 ins), so there is very little family leverage to amortise
the tooling. Judge the investment against that, not against 36,685.

**Verdict: GO-WITH-CHANGES.** Fable's adversarial review = 14 CONFIRMED / 8 WRONG / 1 UNVERIFIABLE.
**The correct implementation is SMALLER than the ox design proposed:**

* **DO NOT create a `_pre` piece.** A dotted `.rodata` named `md_SC03_076_pre` has no sibling `.c`,
  so splat points the ld at a never-built "implied C file" object; the rename also unbinds the
  island from `md_SC03_076.c`, breaking the other five stub tables' migration and both
  INCLUDE_RODATA blobs.
* **DO NOT touch `ld_interleave`.** Verified against the real generated
  `build/md_SC03_076/md_SC03_076.ld` + splat's `LinkerWriter`: the native script is **already
  rodata-first in yaml order**. No leading mode, no make variable.
* **KEEP** `- [0x0, .rodata, md_SC03_076]` untouched. The whole "split" is **ONE INSERTED LINE**:
  `- [0x268, .rodata, md_SC03_076_jr_801F218C]`.
* **Isolate with `jr_isolate_all.py --only`, NOT `jr_isolate.py`.** The latter's backend
  (`split_src_region.py:109-111`) provably `sys.exit`s on `md_SC03_076.c`'s top-level extern
  block. `jtbl_family_bank.py:183` already uses the right one.

**BEFORE any of that — harden `parse_config`.** On md_*/main it does not implement its own
documented contract and can **DELETE the `c` config line, corrupting the yaml on disk** before it
errors out. `tools/jtbl_carve.py::cfg_path` now HARD-REFUSES md_*/main for this reason (S58); lift
that refusal only once parse_config is fixed and proven on two examples.

**main additionally needs:** a file-base of 0x8000F800 (not the yaml's 0x80010000 — `payload_word`
silently reads 0x800 early), and there is no `config/splat.main.yaml` at all (it is
`splat.us.exe.yaml`), which was the original FileNotFoundError.

**Known real defects in the existing tools** (from the study, worth fixing while in there): the
`migrated_tables` "same address by construction" premise is refuted by `apply()`'s own measurement;
the hardcoded 0x80100000–0x801D0000 vram window is vacuous for md_* text at 0x801EF468+ AND for
main, and for md the clamp's safety guard inverts into silent entry-dropping; the `--order`
docstring overstates what that branch does.

**NEGATIVE CONTROL — do not trust the one in the ox study.** It cites func_801F218C @ md_SC03_076
going 43,760 → 43,760 vs a diseased 43,768 (+8, first diff 0x144). Fable found that +8/0x144
baseline was **measured on func_801F0F28 and misattributed**. Build a fresh control. The
object-level `.rodata sh_size 0x14` discriminator is sound; the whole-binary SHA gate is the arbiter.

**Also missed by the design:** a per-target migration-re-homing precheck (func_801F218C is safe by
census), and the **pre-object contiguity wall** — only island-end-adjacent tables carve cheaply;
func_801F0F28 itself needs cascading isolation. Pipeline integration goes through
`jtbl_family_bank`.

---

### LANE 3 — the -O0 and cc1 lanes · `docs/tool-designs/o0-cc1-lanes.md`

**Populations** (atlas): o0-lane 31 groups / 69 instances / **6,564 ins** · cc1 14 groups / 105
instances / **6,511 ins**. Small. A defensible outcome is "not worth building" — say so with
evidence rather than building a lane that cannot bank.

**Status: the study is HALF REFUTED and the header of that doc records which half.**

| claim | verdict |
|---|---|
| `func_801F0A9C` @ md_SC03_076 has no frame pointer, so the atlas `o0-lane` tag is WRONG for it | **CONFIRMED** — zero `$fp` under `asm/md_SC03_076/` |
| md_MAIN_003 (~16 fns) and md_MAIN_011 (~20 fns) are the un-routed -O0 population | **WRONG** — zero `$fp` in *either* module |

**`$fp` occurs in 311 files across `asm/`** — that is the population an -O0 lane would really
target, and nobody has looked at it. Start there.

**Detection law (byte-proven, cookbook §6/§18):** gcc-2.7.2 at -O0 keeps a frame pointer;
`addu $fp,$sp,$zero` = bytes `21F0A003`. -O2 omits it.

**Already-routed -O0 machinery — do not rebuild it:** `boot` is handled at `Makefile:697`
(`build/src/boot.o: CC1FLAGS := …-O0`); overlay clusters are covered by the Makefile globs
`WHALE_O0B_OBJS` (`src/ov_*/ov_*_o0?.c`) and `O0_CLUSTER_OBJS` (`*_o0.c`); `tools/rollout_o0.py`
and `tools/o0_subsplit.py` exist.

**THE LOAD-BEARING QUESTION FOR BOTH, STILL UNANSWERED:** *can the existing gate path bank these
functions unchanged?* A lane that drafts functions the gate cannot accept produces verified drafts
that never bank — that trap has already cost this project two sessions (S57's jtbl pair; wave ab's
105 main cards banking 0/105). Answer this BEFORE drafting a single card.

---

### LANE 1 (half done) — tells: REMOVED from drafting, destination UNKNOWN

`extend-tell` / `swaprepeat-tell` / `s16-div-tell` = 1,040 member functions / **86,602 ins**.
Removed from the drafting rotation in `tools/lanes/drafter.sh` on measured evidence — four waves:
`as` 5/9 gated of 57 drafts · `aw` 6/12 of 60 · `az` 4/10 of 55 · `bd` 3/9 of 56, because **~80% of
tells drafts name symbols the target `.s` never references** (vs the default lane's 74-84% clean).

**DO NOT assume `aprop_autodraft` is the answer.** I asserted that three times from the failure
signature alone; checked, its input population overlaps the 1,040 tells members by **44 (4.2%)**.

**The one live hypothesis, untested:** cookbook **§235 (the phantom symbol)** — `match_one` masks
relocations, so a draft naming a nonexistent symbol scores a clean MATCH with **no instruction diff
at all**; the cure is the `extern u16 SYM[]; SYM[1]` spelling for `%hi(SYM+K)`. That is exactly the
tells failure signature. **Cheap test:** draw one tells wave with §235 in the brief and compare the
`MISMATCH?` rate against the 80% baseline before writing the lane off.

---

## RULES ADDED IN S58 — **ACCEPTED BY DREW 2026-08-23, BINDING FROM NOW**

| Rule | Reason |
|---|---|
| **R42 — COMMIT BANKED WORK THE MOMENT IT EXISTS; NEVER BLIND-REVERT A DIRTY `src/`.** A gate that banks with `commit=False` (`sweep_parallel`, `gate_stage --no-propagate`) leaves REAL, byte-proven functions uncommitted in the tree, and **no tool can distinguish them from residue**. Two obligations follow. (a) A lane that banks **commits before handing control to any other lane, tool, or step** — not at the end of the wave, not "after main", immediately. (b) A tool that finds a dirty tree **COMMITS it or REFUSES**; `git checkout -- src/ config/` as a tidy-up is forbidden. The byte-gate is the arbiter of whether work is correct; git is the only thing that makes it durable, and the window between the two is where work dies. | **Three instances in one session, one of which fired.** `ox_campaign.gate()` and `idiom_serial` both opened with `git checkout -- src/ config/` to clear "residue" — caught before they ran. `gate_main.py` then did it for real: it substitutes into `src/` and reverts on a failing batch, could not tell its own substitution from the 61 overlay functions `sweep_parallel` had just banked with `commit=False`, and reverted **all 61 back to `INCLUDE_ASM` stubs** (verified against `corpus.stubs`) after 95 minutes of bisecting. The drafts survived in `.run/`, the gate cycle did not. |
| **R43 — A TOOL MUST REFUSE AN INPUT IT CANNOT HANDLE, NEVER PROCESS IT WRONGLY.** Silently accepting work a tool will mishandle is worse than skipping it, because the output is a plausible FAILURE that gets attributed to the subject instead of the harness. Where a tool has a known-unsupported input class, it fails loud and names the tool that does handle it. | `sweep_parallel` contained an explicit `"us.exe" if b == "main"` branch — written to LET main IN — while `gate_main.py`'s own docstring documents that main cannot be gated incrementally (its extract rewrites the linker script). Measured: wave `ab` drew **105 main cards and banked 0 of 105**, while its 115 non-main cards banked 94 (82%). The drafts were competent; the harness could not accept them, and the wave read as a drafting failure for a whole session. Extends **R32** (assert your coverage) from *silently skipping* work to *silently accepting work it will mishandle*, and is the same family as **R40** (exonerate the instrument). |

---

## 🛑 SESSION CHECKPOINT — S57 FINAL (2026-08-19/23). Phase 31 CONTINUES. NOTHING IN FLIGHT.

**HEAD `commit:2565` · R22 `make check-all` 213/213 from a clean tree still VALID (no src/ change since
S56; this session banked NOTHING) · EXE `143dbb89` · 0 NON_MATCHING · fleet unchanged at 96.1 /
91.8 / 97.11.** No process running, no wave launched, no cron armed.

### WHAT THIS SESSION WAS
An **external-model bake-off**, not a banking session. Drew's goal: replace ultracode wave agents
with cheap/free API models to stop burning weekly Claude usage. Answer: **yes, decisively** — but
NOTHING WAS BANKED, and that is the top of the next session's list.

### THE FOUR RESULTS THAT MATTER
1. **CARD FUEL IS THE BIGGEST LEVER — bigger than model choice.** Injecting the wave card's
   `seed_ref`/`tu_ref`/`decl_prior` into an API model took the SAME 10 cards from **4/10 to 9/10**
   (DeepSeek) and 4/5 (ox). `func_80181E70` (122 ins) went from *no compiling draft* to MATCH in
   **2 oracle calls**. The "60-instruction ceiling" I inferred earlier was an artifact of withholding
   fuel, not a capability limit. **Always `--cards` before drafting; it is free and deterministic.**
2. **Sub-50 is nearly free money: 19/19 verified MATCH at $0.007/function**, blind (no fuel). The
   pool is **7,724 sub-50 open functions = 73.5% of all open**, in 2,710 groups (1,457 multi-member
   holding 6,471; 5,014 are siblings). All 2,710 exemplars ≈ **$19**; every sub-50 directly ≈ **$54**.
3. **A free model cracked a 611-ins function AND wrote a publishable idiom.** All four autopsy arms
   (Opus/Sonnet/ox/DeepSeek) matched `func_801898E4` + 3 siblings = **2,444 instructions**, every one
   `reloc_identity` AGREE at 80 relocs. ox also cracked the jtbl exemplar (83 ins) and distilled
   **§206** — whose two negative results I independently byte-confirmed (51 and 66 mismatches).
4. **§206 transfers WITHIN a family, NOT across.** exemplar 40 turns/5 oracle -> within-family
   **11 turns/3 oracle MATCH** -> cross-family **56 turns/0 compiles, FAILED**. So jtbl costs ~40
   turns of learning **per family** (191 families), not per class. The jtbl quest is a project, not
   a lane — defer it.

### ⚠ THE BIG UNBANKED PILE (do this FIRST next session)
Everything below is `reloc_identity`-verified and sitting in `.run/bakeoff/`, banked nowhere:
| work | ins | where | note |
|---|--:|---|---|
| **611 family ×4** | **2,444** | `.run/bakeoff/ap-opus/`, `ap-sonnet/`, `ap-ds/`, `ap-ox/` | TWO independent drafts each; both blocking tool bugs FIXED |
| sub-50 probe | 19 fns | `.run/bakeoff/sub50A/`, `sub50B/` | 19/19 verified |
| fueled batch-10 | ~9 fns | `.run/bakeoff/ds-fuelA/`, `ds-fuelB/`, `ox-fuelA/` | vs 4/10 blind |
| jtbl exemplar + sibling | 170 | `.run/bakeoff/jtbl-ox2/`, `jtbl-xfer/` | **needs the §8a CARVE first — a verified match_one is NOT bankable until the table is carved** |
**Matching is solved; integration is the bottleneck** — this session proved the first half four times
over and never touched the second.

### TOOL FIXES SHIPPED (all negative-controlled)
* **`family_remap.gather_externs`** — scanned every `.c` in the source overlay and took the FIRST
  alphabetical match, so it carried `D_8011514C`/`D_8011515C` **type-swapped** (`sh/lh` vs `lbu/sb`,
  LENGTH-DRIFT 610 vs 611 at insn 448). Now prefers the extracted unit's own file. NC: reproduces the
  correct `u8`/`s16` pair.
* **`atlas.py::member_lever`** — `aprop_card` was loaded and **never read** while a bare `DIFF` token
  promoted members to `needs-autopsy`. `PURE` now outranks the ledger; provenance recorded in the
  confidence string. **Rescues 32 members / 11 families / 3,810 ins.**
* **`decl_prior._ASM_SYM`** — `\b` bound to the whole alternation, so the `%hi/%lo` arm had NEVER
  fired (0 of 1,210 across four waves). NC: jal 306->306 zero regressions, data **0->299**.
* **`api_agent.py` (NEW, untracked)** — the API-model harness. Gained this session: `--cards` (fuel),
  `--brief` (analysis tasks), `--max-cost`/`--max-cost-per-fn` (OpenRouter Agent-SDK style), nudge
  loop, 429 backoff with PLATFORM-vs-PROVIDER attribution + Retry-After, transport retry, directory
  reads, non-fatal tool faults, error-body surfacing, and a **repeated-call guard** (identical call
  x4 breaks the loop — ox burned 56 turns on 46 identical greps with 0 compiles).
* **`api_draft.py`** — FRESH_RETRY, reasoning controls, unterminated-fence extraction.

### MODEL LEDGER (OpenRouter, ~$21 spent of $26.83; all costs MEASURED)
| model | verdict |
|---|---|
| **stealth/ox-alpha** | **$0.00**, cracked 611 + jtbl + wrote §206; 4/5 fueled. BURSTY — `upstream_provider_shared_pool` 429s; NOT a `:free` variant so no 20/min-1000/day cap. **Rumoured 5-day window.** |
| **deepseek/deepseek-v4-flash-0731** | $0.46 total; the DEPENDABLE lane. `effort=high`. 9/10 fueled |
| z-ai/glm-5.3 | $6.31 — 3/4 rungs but $1.10 on ONE failure. **`effort=max` REGRESSED it** (0 compiles on a card it had matched); wants `REASON_CAP=16000` |
| RETIRED | Kimi K3 ($2.71, surrendered), Qwen 3.8 Max ($5.98) + 2.4t ($3.20) — read exhaustively, compile rarely |
| free tier | `glm-5.2:free` unreachable (Decart shared pool, 11h+); laguna/dots never compiled; nemotron-ultra works at `effort` (NOT `reasoning.max_tokens` — that 502s) |
**REQUESTS PER FUNCTION = 12-25** (each turn is one POST). `:free` caps = 20/min, 1000/day -> only
40-80 functions/day. ox escapes that cap but not its provider's pool.

### RECOMMENDED NEXT SESSION, IN ORDER
1. **BANK THE 2,444** (611 family ×4) — highest value, drafts verified twice, blockers fixed.
2. Bank the sub-50 19 + the fueled batch-10.
3. Then the sub-50 wave with `--cards` (~$19 for all 2,710 exemplars; gate by TU density — the
   top-40 TUs hold 52% of the pool in 40 rebuilds).
4. **Worktrees** are the untested accelerator: `gate_lane` refuses to run concurrently, so parallel
   drafting queues behind one serial gate. Worktrees would fix it.
5. DEFER: the 245-member jtbl quest (per-family learning cost), more model comparisons.

### RULES ADDED THIS SESSION — **ACCEPTED BY DREW 2026-08-23, BINDING FROM NOW**

| Rule | Reason |
|---|---|
| **R40 (ACCEPTED) — EXONERATE THE INSTRUMENT BEFORE YOU ATTRIBUTE A FAILURE TO ITS SUBJECT.** When a measured subject (a model, a binary, a family, a lane) appears to fail, the harness that produced the reading is a suspect until cleared. Before writing "X failed", check the run for: a truncated reply (`finish=length`), a transport error, a rate limit, an unhandled tool fault, a parameter the provider rejected, a missing input the subject was entitled to, and a loop the harness never bounded. Report the failure only once those are excluded — and when one of them WAS the cause, say so as a correction, not as a footnote. | **Seven instances in one session, every one reported to Drew as a model result first**: a 568k-token prompt read as "GLM returns empty"; an unstripped code fence read as "Qwen writes broken C"; uncapped reasoning read as three separate models "failing"; break-on-`finish=length` read as "DeepSeek gave up with 24 turns unspent"; a `reasoning.max_tokens` that 502s one provider read as "nemotron-ultra can't run"; an `IncompleteRead` read as "near 17 is its ceiling"; a directory read that killed the jtbl run at turn 2 of 50. The models were fine; the instrument was not. Extends **R35** (fix the instrument before trusting the measurement) to the ATTRIBUTION step, which R35 does not cover. |
| **R41 (ACCEPTED) — A COST, RATE OR YIELD NUMBER SHIPS WITH ITS DENOMINATOR.** Never quote a marginal figure where a total is implied, or a success rate without the attempts it excludes. Say which one it is in the same sentence: "$0.09 per solved function, $6.31 spent total", "19/19 on a seeded stratified sample of 19", "12–25 requests per function, so 1,000/day = 40–80 functions". | I reported GLM-5.3 as costing **$0.30** for eight messages. Drew's bill said **$5**. Both were true: $0.30 was the marginal cost of the two runs that matched, $6.31 was the spend, and 95% of the difference was experiments and my own configuration failures. The flattering number was the one I kept repeating. This is the session's own dominant defect class — *a true number about a narrower scope than the reader believes* (memory `silently-narrowed-tool-scope`) — turned on my own reporting, and it extends **P9** (milestone honesty) from outcomes to metrics. |

**Not elevated to rules** (Phase-8+ precedent — techniques to the cookbook, findings to the checkpoint):
the card-fuel result (**§206** + the fuel A/B) is a *procedure* already enforced by `--cards`; the
jtbl idiom is **§206**; the `gather_externs` / `atlas` / `decl_prior` defects are R32/R33/R36 cases
the existing rules already govern; "a verified `match_one` is not a bankable jtbl card" is a
watch-for below.

### WATCH-FORS
* A verified `match_one` is **NOT** a bankable card for jtbl functions — the §8a carve
  (`jtbl_carve` -> `make extract`) must happen first; `api_agent` cannot do it (read-only, no config).
* `reloc_identity`'s summary line prints `shape=MATCH` even when it means "streams not aligned,
  verdict advisory" — read the line BELOW it.
* Don't run card tooling during a gate (`corpus.stubs()` misreports substituted drafts).
* `.env` holds the OpenRouter key as `open_router_key=` (no export, no prefix).

## 🛑 (superseded by S57) SESSION CHECKPOINT — S56 FINAL (2026-08-18). Phase 31 CONTINUES. NOTHING IN FLIGHT.

**HEAD `commit:2563` · tree clean except Ghidra `db.*.gbf` restart-noise (R23: do NOT stage) and
`.run/` scratch · R22 `make check-all` = 213 passed / 0 failed of 213 from a CLEAN tree · EXE
`143dbb89` · 0 NON_MATCHING in any default build (G4) · dedup-check 2,165 validated / 0 failed · C1
254,731/254,731.** No process running, no cron armed, no workflow in flight. Drew pushes.

### Banked this session: 127 functions
| lane | banked | notes |
|---|--:|---|
| wave Z drafts, first gate | 72 of 73 | 74/75 drafted MATCH, 0 immovable, 73 reconciled onto slates |
| recovery — `func_800CC310` | 1 | §203 address-order typedef hoist; **0 agent tokens** |
| recovery — `func_8018280C` | 1 | §202 alias on a DEFINITION (the §183.3 DEF-side wall); **0 agent tokens** |
| mechanical siblings — first sweep | 3 | **mis-scoped, see below** |
| mechanical siblings — corrected sweep | 50 | 22 families, `--band all`, ~0 tokens |

**Fleet 96.1% instr-weighted · 91.8% distinct-code · 97.11% fn-count · MAIN 20.5%.**
(Session start: 96.0 / 91.7 / 97.07.) **10,501 stubs open.**

### THE ONE-LINE VERSION OF WHAT THIS SESSION LEARNED
**Four tools were silently answering a narrower question than they were asked, and every one exited
zero reporting a TRUE number.** `wave_snapshot` found 9 of 75 targets (and took the S46 validity gate
off the path with it for six waves) · `family_sweep --only` selected 2 families instead of 21
(**3 banked vs 50**, same tree, same day) · `decl_prior`'s `%hi/%lo` arm had **never fired in 1,210
opportunities** across four waves · `pregate_check` modelled the banking driver faithfully and never
checked the consequence, so it said "clean" about the batch it broke. **The byte-gate cannot see any
of this** — it is a perfect CORRECTNESS oracle and a null COVERAGE oracle (R34). When a step reports
a count, ask what denominator it is a fraction of, and make the tool print it.

### RESULTS THAT OUTLIVE THE COUNT
1. **§202 — THE ALIAS CARRIES A DEFINITION.** `s32 aF8018280C(s32) __asm__("func_8018280C");` banks a
   DEF-side return-type wall with the TU's three `void` decls left untouched. §183.3's "report
   IMMOVABLE with a TU edit" is no longer the end of that road. In-tree the idiom existed only on
   declarations. **Reach for it the moment a wall is DEF-side.**
2. **§203 — A DEDUPED TYPEDEF MUST PRECEDE EVERY SPLICE POINT.** Two slate-mates sharing a type:
   `strip_provided_typedefs` drops the earlier-addressed one's copy and the survivor lands below its
   uses (`parse error before '<symbol>'`, which reads like a codegen residual). **Hoist to the top of
   the TU; never rename in one draft** — that gives one symbol two types and the failure just moves.
   `pregate_check` now reports `[DROP-RISK] §203 USE-BEFORE-TYPEDEF` before the gate cycle.
3. **R38 PAID FOR ITSELF, AFTER I IGNORED IT.** The verdict was on disk in
   `.run/harvest_failed.<binary>.classified.txt` before I ran a single oracle. I ran `reloc_identity`
   (AGREE, correct, irrelevant) and then a disassembly that read **69/69 identical** — an artifact,
   because the draft never compiled and the `.elf` still held the original `INCLUDE_ASM` bytes.
   **A byte-diff against a build that failed to include your draft always reads MATCH.**
4. **THE HARVEST'S ADVERSARIAL VERIFIER KILLED 7 OF 12 LAW CLAIMS** — two by reproducing the claimed
   mechanism and finding it BYTE-FALSE, five as re-derivations of existing §§. The synthesizer then
   corrected three wrong line citations and re-measured a law's claimed +4 instruction cost as an
   actual **+1**. 82 reports -> 30 already-covered, 31 confirmations, 5 laws, 16 rejected (**§204**).
5. **A BACKLOG DRAFT PATH IS NOT A STABLE ORIGINAL.** `gate_stage` calls `backlog.save_draft()` on
   failure, so a failed attempt OVERWRITES it; "copying the original back" copied my rename. The
   bytes banked correctly, but §203's first write-up claimed "draft byte-unchanged" and was wrong —
   corrected in place. **Snapshot text you intend to re-gate.** A symbol-rewriting transform also
   mangled prose INSIDE A COMMENT (`(*(Quad4_800CCAD0 *)&D_800CCB14)`) — transforms must skip comments (H5).

### Tooling shipped (all negative-controlled, both directions)
`build_wave_atlas`: **the S46 validity gate now runs where cards are BORN** (`--allow-invalid` escape)
— NC: wave AA 69/69 OK pre-draft, poisoned card refused OUT-OF-RANGE ·
`validate_targets`: accepts the card spelling `fn`; **PRE-DRAFT-ONLY constraint documented in the tool**
(every verdict reads live sig/stub/.s state, so the same check after a wave condemns exactly the
targets that BANKED — an R39 refusal-check at the wrong moment) ·
`wave_snapshot`: honors the card's `sub` (NC 9/9 legacy byte-identical, 66/66 split-TU recovered;
wave AA snapshotted **69/69** by the call that found 9 of 75 this morning) ·
`family_sweep --only`: resolves MEMBER addrs to their family, **always prints
`--only: N addr(s) -> M family(ies) (... K unresolved)`**, refuses on zero ·
`pregate_check`: `[DROP-RISK] §203 USE-BEFORE-TYPEDEF` (searches a comment-blanked copy — its first
draft read a typedef named in its own comment as a use) ·
`decl_prior`: **§204-E** — the leading `\b` bound to the whole alternation, demanding a word boundary
before `%`, impossible in a `.s` (NC: `jal` 306→306 zero regressions, data **0→299**); uncopyable
pointer-to-function spellings are now MARKED `fleet_note`, not dropped.
Docs: **SETUP.md "Crack-wave toolchain — the four flow traps"**; memories `crack-wave-sweep-map-regen`
(rewritten) + new `silently-narrowed-tool-scope`.

### WAVE AA IS BUILT AND STAGED — DELIBERATELY NOT LAUNCHED (Drew's instruction)
**69 cards / 6,539 ins / 8 GATE GROUPS** (8.6 drafts per rebuild) · models opus 19 / sonnet 50 ·
seed_ref 34 · tu_ref 46 · decl_prior rows **471, of which 165 are DATA rows — 0 on every prior wave**
(the §204-E fix; 49 marked `fleet_note` as uncopyable fn-pointer spellings) · 33 siblings behind 25
gids staged · nins 60-197 (avg 95) · levers UNKNOWN 36 / head-crack 12 / family-sweep 10 / redraft 6 /
seeded-crack 3 / len-vein 1 / integration 1.
Binaries: ov_SC07_000 14 · ov_SC01_080 13 · ov_SC07_006 9 · ov_SC02_021 9 · ov_SC04_004 8 ·
ov_SC06_032 7 · ov_SC02_000 5 · ov_SC02_016 4. **All 69 passed the validity gate pre-draft.**
**To fire it:**
```
Workflow({scriptPath: ".run/wave_p31aa_workflow.js", args: <the object in .run/wave_aa_args.json>})
```
Cards `.run/wave_aa_cards.json` · siblings `.run/wave_aa_cards.siblings.json` · wavedir
`.run/wave_p31aa` · snapshot `.run/waveAA_asm_snapshot/` (69/69 + MANIFEST.sha1).
**Gate-group count is 8, same as wave Z** — the recipe's re-open-the-band trigger is ~12, not yet hit.

### THE WAVE-CLOSING SEQUENCE (memory `wave-harvest-is-a-pipeline-step`)
snapshot+verify+**gate** -> **RECOVER** the failures (near-miss / gate-drop / errored; read
`.run/harvest_failed.<bin>.classified.txt` FIRST) -> gate the recovery -> **regen** (`make
sig-overlays` + `family_hseq.py`) -> `family_sweep --hseq --band all` **with families selected by
MEMBERSHIP, not by handing it your banked addrs** -> **R22 once** -> **harvest+bank idioms** (run
`gap_triage` first) -> **build the next wave's cards** -> **CHECKPOINT, always, refreshed if any work
lands after it.**

### Known-open items
* `func_8018675C` (ov_SC02_005, closeness 6) — ~35 variants ground; residual attributed to
  **cse.c:5278's unconditional constant-second swap for symbol-valued pointer bases**, which retires
  "reorder the addends" as a lever. **Permuter fuel, not a hand lever.**
* `func_80184F18` (wave V, closeness 9) · `func_80184500` (wave W, 4) · `func_8017F9D8` (wave X, 1).
* `func_80031A98` — the `D_800C5328` wall. The 6 §188 SDK objects -> `psyq_integrate`.
  `GsSortBg`/`GsSortFastBg` fragment merges. `gfx2D_BG0_OBJ_4D8` (§181 mirror class).
* Two wave-W cards still released to the pool: `func_80185480`, `func_8017EC98`.
* **`gate_main.typesig` renders pointer-to-function unusably** (`('void (*', ('* void',))`). NOT
  fixed: `typesig`/`norm_sig` is the BANKING DRIVER's conflict oracle (`sig_conflict`), so changing
  its output changes signature equality classes fleet-wide. The safe fix is a DISPLAY-only
  pretty-printer in `decl_prior` — **no index rebuild needed, the tuple is what's stored**. Rows are
  marked meanwhile so no agent pastes one.
* The **typing/naming debt** remains the largest non-matching liability (S54 note): 9.5 casts per 100
  lines, 749 per-function invented typedefs vs 220 shared. Byte-checkable by the same gate.

### Watch-fors
* **Transient API failures are normal at this scale**: resume with
  `Workflow({scriptPath, resumeFromRunId, args})` — cached agents replay, only dead ones re-run. Never
  rebuild a wave by hand.
* A wave script's LAWS block is a JS template literal: **backticks inside law text terminate it.**
* `gate_lane` aborts on a dirty `src/`/`config/`; it commits per function, so **do not run your own
  `git commit` while it runs** (index.lock race).
* Do NOT run card tooling (`build_wave*`, `validate_targets`) DURING a gate — `corpus.stubs()`
  misreports substituted drafts and every verdict reads ALREADY-DONE.
* **md_* MODULE binaries gate through `gate_lane` like overlays. Only `main` (the EXE) needs
  `gate_main --apply`** — its extract rewrites the `.ld` and an incremental build gives a false diff.
* `pregate_check` models two drivers (main -> `gate_main` hoist/strip, overlay/module ->
  `harvest_verify.strip_provided_typedefs`). **A third driver would need teaching.**

## 🛑 (superseded by S56) SESSION CHECKPOINT — S54/S55 FINAL (2026-08-17/18). Phase 31 CONTINUES. NOTHING IN FLIGHT.

**HEAD `commit:2546` · tree clean except `.run/backlog.jsonl` churn + Ghidra `db.*.gbf` restart-noise
(R23: do NOT stage) · R22 `make check-all` = 213 passed / 0 failed of 213 from a CLEAN tree, run
SEVEN times this session (after every wave and after wave Y's recovery) · EXE `143dbb89` ·
0 NON_MATCHING.** No process running, no cron armed, no workflow in flight. Drew pushes.

### Banked this session: 547 functions
| lane | banked | notes |
|---|--:|---|
| wave T — 5 groups | 70 of 70 | **zero drops** — first wave ever to bank every byte-verified draft |
| wave U — 7 groups | 73 of 73 | **100% drafted AND banked**; 15% fewer tokens, 64% of the wall-clock |
| wave V — 9 groups | 68 of 69 | |
| wave W — 3 groups, UNKNOWN lane | 68 of 70 | 24.3 drafts/rebuild; first MODULE binary |
| wave X — 4 groups | 62 of 63 | second module binary clean |
| wave Y — 5 groups | 72 | 64 gate + **4 recovery (§200, 0 agent tokens)** + 4 siblings |
| mechanical siblings (all waves) | 113 | `family_sweep --hseq`, ~0 tokens |
| §180 leftover sweep | 24 | byte-perfect drafts already on disk from waves M/O/P/R/S |

**Fleet 96.0% instr-weighted · 91.7% distinct-code · 97.07% fn-count · MAIN 20.5%.**
(Session start: 95.6 / 90.8 / 96.92.)

### THE ONE-LINE VERSION OF WHAT THIS SESSION LEARNED
**Every single lever that moved the numbers was already computed and simply not carried anywhere.**
§193-A (the atlas's banked twin, discarded by the card builder) · §194-E (`tu_ref`, the banked
neighbour in the destination TU) · §196 (`decl_prior`, the fleet's declaration consensus) · §198
(the UNKNOWN lever lane, excluded by a default flag while the PROMPT told agents to draft it) ·
§200 (the asm-label alias, an idiom the project already used and the tools could not parse) ·
`gap_triage` (the harvest's majority verdict is a text search). **Before adding an agent, an
attempt, or a prompt paragraph, ask what the tree already knows.**

### THE SEVEN RESULTS THAT OUTLIVE THE COUNT
1. **RECONCILIATION BELONGS INSIDE THE WAVE.** One agent per gate group runs the deterministic
   ladder over its OWN slate before the first rebuild. Wave R banked 18 of 45 and needed a recovery
   lane; waves T-Y banked 70/70, 73/73, 68/69, 68/70, 62/63, 64/69. Costs one agent per group.
2. **THE CARD IS THE CHEAPEST PLACE IN THE PIPELINE TO PUT A FACT.** `seed_ref` (banked 51/51 on
   wave U's draw vs `exemplar` 0/73) took wave U to 100% drafted at 15% fewer tokens and 64% of the
   wall-clock. `tu_ref` reaches 48-64 cards per wave. `decl_prior` answers the arity guess §195-A
   proved the asm cannot answer. Every field costs zero tokens per wave, forever.
3. **§198 — THE SELECTOR WAS OVERRIDING THE DOCTRINE.** `UNKNOWN` held 607 of 1,179 in-band members,
   more than every other lane combined, and `--levers` excluded it while the prompt told agents it
   drafts like any other lane. Promoted (measured 71/71 drafted, 68 banked, 24.3 drafts/rebuild).
   **Recorded cost: zero siblings** — UNKNOWN groups are singletons.
4. **§200 — THE ALIAS IS THE UNIVERSAL DECLARATION ESCAPE.** Only the LINK name has to agree:
   `extern u8 aD8018A800[] __asm__("D_8018A800");`. Five refusal classes, one move, five still
   MATCH, four re-gated — during a total API outage, by hand, at zero agent cost. Ordering: adopt
   the TU's spelling -> cast at the use site -> alias.
5. **FOUR SELF-CORRECTIONS IN ONE SESSION.** §194-E corrected §193-A · §199-A byte-refuted §189-A ·
   §197-A refuted §136-9's cure · §201-A caught `decl_prior`'s address-keyed DEF row **before wave Z
   launched**. A law from one wave is a first draft; the next wave is its review. This is the
   adversarial verifier paying for itself, and it is why the harvest is a pipeline step.
6. **THE §192 DEFECT CLASS, THREE MORE INSTANCES.** The pre-gate ladder was main-only and said
   "clean" about it; `sym_of` returned the keyword `void` for pointer-to-function decls (189,301
   verdicts corrected) and `__asm__` for the project's own alias idiom (1,210 more); `masked_diff`
   dropped every internal `j` so a `break`-vs-`return` error read as MATCH. **A tool written against
   one binary — or blind to one idiom — silently narrows its own domain and reports success over
   what is left.**
7. **THE HARVEST CONVERGES, AND THAT IS THE POINT.** already-covered by wave: 61/71 (T), 44/64 (U),
   76/67 (V), 41/68 (W), 56/63 (X), 53/67 (Y); confirmations 9, 14, 14, 4, 7, 5; wave Y's 8
   rejections are the session high. Readers seeded with all prior passes cannot re-derive them.

### Tooling shipped (all negative-controlled)
`build_wave_atlas`: `--one-per-gid` · `--rank total` · `seed_ref`/`matched_n` (§193-A) · `tu_ref` +
null self-exemplars (§194-E) · `decl_prior` rows (§196), now per-binary (§201-A) · UNKNOWN in the
default lane (§198) ·
**NEW** `tools/decl_prior.py` (67,558 symbols; DEF keyed by binary) ·
**NEW** `tools/gap_triage.py` (harvest pre-filter; wired as step 0 of the harvest prompt, SETUP.md
row, named in the wave-closing memory) ·
`gate_main`: `_stubs_for` · `sym_of` x2 · `norm_sig`/`sig_conflict` · `substitute(transform=)` ·
common.h-derived aliases · `pregate_check`: overlay driver transform, builtin->WARN, block-scope
typedefs, `[DROP]` reporting, refuse-on-zero-files · `masked_diff`: internal `j` compared.

### WAVE Z IS BUILT AND STAGED — DELIBERATELY NOT LAUNCHED (Drew's instruction)
**75 cards / 6,517 ins / 8 GATE GROUPS** (9.4 drafts per rebuild) · seed_ref 46 · tu_ref 50 ·
decl_prior 70 · 43 siblings staged. Binaries: ov_SC02_005 20 · ov_SC01_084 16 · ov_SC05_001 11 ·
ov_SC03_011 10 · ov_SC03_094 8 · md_MAIN_034 7 · md_SC03_075 2 · ov_SC06_018 1.
**Cards were REDRAWN after the §201-A fix** — the first staging carried 24 poisoned DEF rows of 292;
the current file has 0 poisoned and 24 withheld with a stated reason.
**To fire it:**
```
Workflow({scriptPath: ".run/wave_p31z_workflow.js", args: <the object in .run/wave_z_args.json>})
```
Cards `.run/wave_z_cards.json` · siblings `.run/wave_z_cards.siblings.json` · wavedir `.run/wave_p31z`.

### THE WAVE-CLOSING SEQUENCE (eight steps, memory `wave-harvest-is-a-pipeline-step`)
snapshot+verify+**gate** -> **RECOVER** the failures (near-miss / gate-drop / errored) -> gate the
recovery -> `family_sweep --hseq` siblings -> **R22 once** -> **harvest+bank idioms** (run
`gap_triage` first) -> **build the next wave's cards** -> **CHECKPOINT, always, written for a fresh
session — and refresh it if any work lands after it.**

### Known-open items
* `func_8017FCFC` (ov_SC02_017, closeness 3) — the ONE wave-Y near-miss not recovered. Its agent
  attributed the last 3 instructions to sched1 by elimination (`oracle_reorder` bypass+`as -O2` = 9
  diffs so NOT an assembler artifact; `-fno-schedule-insns2` alone does not fix it;
  `-fno-schedule-insns` alone fixes idx 25-27 and breaks 50-52). Permuter fuel, not a hand lever.
* `func_80184F18` (wave V, closeness 9) · `func_80184500` (wave W, closeness 4) · `func_8017F9D8`
  (wave X, closeness 1 — 93 of 94 words identical, a branch landing one instruction early).
* `func_80031A98` — the `D_800C5328` wall, unchanged. The 6 §188 SDK objects -> `psyq_integrate`.
  `GsSortBg`/`GsSortFastBg` fragment merges. `gfx2D_BG0_OBJ_4D8` (§181 mirror class).
* Two wave-W cards released back to the pool (agents died on rate limits, no draft):
  `func_80185480`, `func_8017EC98`.

### Watch-fors
* **Transient API failures are normal at this scale and the recovery is always the same.** Session
  limit (wave X harvest) and 529 Overloaded (wave Y recovery + harvest, four rounds, ~17 agents, 0
  tokens) both resolved with `Workflow({scriptPath, resumeFromRunId, args})` — cached agents replay,
  only the dead ones re-run (measured 398k vs the original 1.31M). Do not rebuild a wave by hand.
* A wave script's LAWS block is a JS template literal: **backticks inside law text terminate it.**
* `gate_lane` needs `binary` + `name` per slate record; `scan_leftovers` slates carry `fn` + `draft`.
* If a Reconcile agent dies, its group has NO slate — build it from the drafts on disk and run the
  ladder by hand (that is why the phase's product is a FILE, not an agent return value).
* `pregate_check` models the banking DRIVER: main goes through gate_main's hoist/strip, overlays
  through harvest_verify's `strip_provided_typedefs`. A third driver would need teaching.
* Snapshot every target's `.s` BEFORE gating — banking prunes it and recovery/harvest need both sides.

## 🛑 (superseded by S54/S55) SESSION CHECKPOINT — S54 FINAL (2026-08-17). Phase 31 CONTINUES. NOTHING IN FLIGHT.

**HEAD `commit:2541`+ · tree clean except Ghidra `db.*.gbf` restart-noise (R23: do NOT stage) ·
R22 `make check-all` = 213 passed / 0 failed of 213 from a CLEAN tree (run 3x this session, after
each wave) · EXE `143dbb89` · 0 NON_MATCHING.** No process running, no cron armed, no workflow in
flight. Drew pushes.

### Banked this session: 547 functions (433 gated heads + 113 mechanical siblings + 1 main)
| lane | banked | notes |
|---|--:|---|
| wave T — mass band, 5 groups | 70 of 70 | **zero drops** — first wave ever to bank every byte-verified draft |
| wave U — mass band, 7 groups | 73 of 73 | **100% drafted AND 100% banked**; 15% fewer tokens, 64% of the wall-clock |
| wave V — mass band, 9 groups | 68 of 69 | 8 of 9 groups clean |
| mechanical siblings (`family_sweep --hseq`) | 49 + 34 + 25 = **108** | ~0 tokens; 9 failed of 112 attempts |
| wave W — UNKNOWN lane, 3 groups | 68 of 70 | 71/71 drafted; 0 siblings (UNKNOWN groups are singletons) |
| wave X — UNKNOWN lane, 4 groups | 62 of 63 | 2nd module binary clean; 1 sibling |
| wave Y — UNKNOWN lane, 5 groups | 72 | 64 gate + 4 recovery (§200, 0 agent tokens) + 4 siblings |
| §180 leftover sweep | 24 | byte-perfect drafts already on disk from waves M/O/P/R/S |

**Fleet 96.0% instr-weighted · 91.7% distinct-code · 97.07% fn-count · MAIN 20.5%.**
(Session start: 95.6 / 90.8 / 96.92.)

### THE FIVE RESULTS THAT OUTLIVE THE COUNT
1. **RECONCILIATION BELONGS INSIDE THE WAVE.** The only structural change from wave S was a
   **Reconcile phase**: one agent per gate group runs `reconcile_slate --apply` -> the §183 playbook
   -> `pregate_check` over its OWN slate, re-verifying every edit with match_one, BEFORE the first
   rebuild. Wave R banked 18 of 45 on its first slate and needed a recovery lane afterwards (§181:
   26 of 27 rejections were byte-perfect drafts). Waves T/U/V banked **70/70, 73/73, 68/69**. This is
   the single highest-leverage change of the session and it costs one agent per gate group.
2. **§192 — THE PRE-GATE LADDER WAS MAIN-ONLY AND SAID "clean" ABOUT IT.** `pregate_check` on an
   overlay slate printed `checking 0 substituted file(s) ... clean`. Four fixes, each controlled:
   per-binary `_stubs_for()`; `sym_of` no longer returns the keyword `void` for
   `extern void (*D_x[])(...)` (**NC: 5,526,100 declarations, 189,301 changed verdicts, 0
   regressions**); C89's unspecified-parameter rule as `gate_main.sig_conflict`; the overlay DRIVER's
   typedef transform modelled. Plus §192b: the tool REFUSES when it substituted 0 files.
3. **§193-A -> §194-E — THE CARD WAS HANDING AGENTS A DEAD POINTER.** `exemplar`/`sibs` come from the
   atlas's OPEN set by construction, so they are stubs 0/34 measured — and on ~half the cards
   `exemplar` IS the card's own target. Meanwhile `atlas.py:505-536` already computed a MATCHED-pool
   twin whose identity the card builder discarded. Cards now carry **`seed_ref`** (banked 51/51 on
   wave U's draw, 37/37 on wave V's) and **`tu_ref`** — banked functions in the card's OWN .c ranked
   by symbols shared with the target's `.s` relocations (48/70 cards on wave V; 62% of wave-T targets
   have such a neighbour vs 19% for the cross-overlay literal grep).
4. **§195-D — AN INTERNAL `j` WAS INVISIBLE TO THE FAST ORACLE.** `masked_diff.mask_for`
   short-circuited on the OPCODE ahead of the reloc dispatch, so every `j .L…` was dropped from the
   comparison. For a loop/switch arm that is the difference between `break` (execute the shared
   tail's calls) and `return` (skip them): byte-proven on `ov_SC03_118:func_801825EC`, where the two
   objects differ in ONE word (`0800003e` vs `08000041`) and both reported MATCH. It blinded
   match_one, the permuter's scorer, `family_cousins.tok` and the atlas tiers at once. Fixed (mask
   only when `reloc_kind == "26"`); R39 control 35/35 banked drafts still MATCH. **The similarity
   TOKENIZERS are deliberately left blind** — everything they feed is byte-gated, and the raw field
   is position-dependent so including it naively would break sibling grouping.
5. **THE HARVEST IS THE PRODUCT, AND ITS BIGGEST NUMBER IS "ALREADY COVERED".** Three harvests:
   **9 CONFIRMED / 5 rejected / 61 already-covered** (T), **14 / 5 / 44** (U), **14 / 9 / 76** (V) —
   37 verified laws banked as §193-A..I, §194-A..N, §195-A..N. Two of §194 correct §193 entries
   written the SAME DAY (both cross-bannered). The already-covered majority is a RETRIEVAL problem,
   which is what `tu_ref` and the prompt's STEP 0b cookbook-search exist to fix.

### Tooling shipped (all negative-controlled)
`build_wave_atlas`: **`--one-per-gid`** (collapse same-skeleton siblings to one card, defer the rest
to the mechanical remap; R32 accounting asserted) · **`--rank total`** (rank gate groups by DELIVERED
mass = card + deferred siblings) · **`seed_ref`/`matched_n`** (§193-A) · **`tu_ref`** + null
self-exemplars (§194-E; operand-only `.s` symbol extraction — a naive uppercase regex read the
comment column's hex words as symbols) · `gate_main`: `_stubs_for`, `sym_of`, `norm_sig`/`sig_conflict`,
`substitute(transform=)`, common.h-derived scalar aliases · `pregate_check`: driver-accurate overlay
transform, builtin conflicts -> WARN (cc1-probed), block-scope typedefs skipped, `[DROP]` reporting,
refuse-on-zero-files · `masked_diff.mask_for`: internal `j` compared.

### NEXT SESSION — in order
1. **`make atlas` FIRST**, then wave W: `build_wave_atlas --target-ins 6500 --min-ins 60 --max-ins 200
   --rank total --one-per-gid --max-bins 10`. **Watch the gate-group count**: waves T/U/V needed
   5 -> 7 -> 9 groups for the same ~6,500 instructions. When it reaches ~12, the fleet-wide 60-200
   mass band is thinning and the honest move is to re-open the band question with the velocity
   ledger, not to keep drawing.
2. **Close the wave the same way every time** (memory `wave-harvest-is-a-pipeline-step`):
   gate -> `family_sweep --hseq --only <exemplar addrs>` (after `make sig-overlays` +
   `family_hseq.py`) -> R22 clean-fleet -> **harvest the index_gaps**. Snapshot each target's `.s`
   BEFORE gating (`.run/wave*_asm_snapshot/`) — banking prunes it and the verifiers need both sides.
3. **The typing/naming debt is now the largest non-matching liability** (see the S54 note below):
   9.5 casts per 100 lines, 749 distinct per-function invented typedefs vs 220 shared, parameters
   typed `s32` that are really pointers. Not a matching problem; it is THE readability problem, and
   every retype is byte-checkable by the same gate (§185: grep and COUNT the use sites first).
4. **Carry-overs**: `func_80184F18` (wave V, closeness 9, ~12 permutations pinned — permuter fuel);
   `func_80031A98` (the `D_800C5328` wall, unchanged); the 6 §188 SDK objects -> `psyq_integrate`;
   the `GsSortBg`/`GsSortFastBg` fragment merges; `gfx2D_BG0_OBJ_4D8` (§181 mirror class).

### Watch-fors
* `gate_lane` needs `binary` + `name` in its slate records; the leftover slates from
  `scan_leftovers.py` carry `fn` + `draft` only — add `binary` before gating.
* A wave script's LAWS block is a JS template literal: **backticks inside the law text terminate it**.
  Wave U's first launch died on exactly that; write law text with single quotes.
* `pregate_check` models the DRIVER: main goes through gate_main's hoist/strip, overlays through
  harvest_verify's `strip_provided_typedefs`. If you add a third banking driver, teach it the tool.
* A TU typedef defined BELOW the stubs that need it breaks the overlay path (the draft's copy is
  stripped, the survivor sits below). Hoisting is byte-neutral — null-control-build it first, as
  `ov_SC02_005` was.

## 🛑 (superseded by S54) SESSION CHECKPOINT — S53 FINAL (2026-08-16/17). Phase 31 CONTINUES. NOTHING IN FLIGHT.

**HEAD `commit:2453`+ · tree clean except Ghidra `db.*.gbf` restart-noise (R23: do NOT stage) ·
R22 `make check-all` = 213 passed / 0 failed of 213 from a clean tree · EXE `143dbb89` · 0 NON_MATCHING.**
No process running, no cron armed, no workflow in flight. 39 commits this session; Drew pushes.

### Banked this session: 161 functions
| lane | banked | notes |
|---|--:|---|
| wave R — mass band | 75 | ov_SC06_029 36 · ov_SC02_005 21 · main 18 |
| wave S — mass band | 63 | ov_SC04_011 30 of 45 · ov_SC03_028 33 of 34 |
| the 27-draft recovery backlog | 23 | incl. 2 real fragment merges |

**main stubs 1,763 → 1,714** · **MAIN game-code weighted 17.4% → 20.4%** · fleet instr-weighted
**95.6%**, distinct-code **90.8%** (was 90.7%), fn-count 96.92%.
Remaining stubs in the four worked overlays: ov_SC02_005 315 · ov_SC04_011 199 · ov_SC03_028 161 ·
ov_SC06_029 134.

### THE FOUR RESULTS THAT OUTLIVE THE COUNT
1. **DRAFTING IS SOLVED AT THIS SCALE; INTEGRATION IS THE ENTIRE COST.** Wave R drafted 84%, **wave S
   70/71 = 99%** (82 agents, 0 errors). Of 27 gate-rejected main drafts, **26 were byte-correct** and
   rejected purely on declaration plumbing (§181 census). Three independent measurements now agree
   (§180b's cold pile 11/32, wave P's 97%→68%, this census). **Budget for banking, not cracking; an
   hour spent making the integration layer COMPUTE a refusal outranks an hour of drafting.**
2. **§188 — THE `jr $ra` + `addiu $sp` EPILOGUE TAIL IS AN ASSEMBLER ARTIFACT, NOT CODEGEN.** GNU
   `as -O2` fills the return delay slot; cc1 CANNOT emit that shape for any `$s`-saving frame
   (`mips.c:5081/5174/5204`). This **corrects §177's row 2 in place** (banner added), **answers §182's
   open question**, and explains why that lane converted 4 of 16. `tools/oracle_reorder.py` now
   separates a C defect from an assembler artifact in one 2×2 — a 0 in the bypass+`as -O2` cell means
   the draft is already right and grinding is futile. **Six functions in that band are prebuilt SDK
   objects** (libpad `pdent3/4/5`, `pdmain1`, `pdmaiini`, libapi `first.o`) → `psyq_integrate`.
3. **§187 — THE libgs SHORTCUT IS REFUTED, AND THE LESSON IS ABOUT THE ORACLE.** `src/800b_7.c` really
   is `GsSortBg`/`GsSortFastBg` = `2D_BG0.o`/`2D_BG1.o`, but the game's build carries **six extra GTE
   hazard nops**: 520 object instructions vs a 526-instruction region. Two checks (the agent's and my
   own) called it a match because both excused a whole word whenever it carried a relocation. **A mask
   coarser than the linker's is not weak evidence, it is no evidence**, and agreement between two loose
   checks is not corroboration (R34). Reverted; those 8 symbols stay decomp work.
4. **COMMENT-BLINDNESS WAS A DEFECT CLASS, NOT A BUG (§184).** Three tools were comparing C text
   without masking comments, so identical layouts read as DIFFERENT-STRUCT because agents annotate
   fields and the TU does not — each silently refusing byte-verified work. Related: `scan_leftovers.py`
   found **37 byte-perfect, still-stubbed drafts (3,240 ins) on its first run** — a wave targets ~6,500
   ins, so sweep `.run/` before spending a token on new cards (§180).

### Tooling shipped this session (all negative-controlled)
**NEW** `scan_leftovers.py` (re-verify unbanked drafts; the `.s`-existence oracle) ·
**NEW** `fragment_check.branched_into` (the MIRROR trap: a sibling branches INTO your range; 5.7% of
main stubs, 0% in the wave-S overlays) · **NEW** `tools/oracle_reorder.py` (§188's diagnostic) ·
`gate_main`: typedef **HOIST** above the include block (byte-neutral, SHA-proven) + comment-blind
comparison fixed + FORWARD typedef stripped instead of renamed · `pregate_check`: masked-text scan +
ANY return-type disagreement now FAILs + brace-bodied externs visible · `reconcile_slate`:
comment-blind struct comparison fixed.

### Cookbook: §180–§191 (24 entries) — see the section list in the S53 progress-log entries above
The **S53 journal harvest is DONE — do not redo it**: 10 readers over 247 wave-R/S verdicts, one
adversarial verifier per candidate defaulting to REJECT → **10 CONFIRMED / 4 WEAK / 4 REJECTED**
(`.run/s53_harvest.json`; §191 records the rejects). Verifiers rebuilt targets from the ROM where the
`.s` was pruned on bank, re-ran their own A/B sweeps, and caught a wrong mechanism comment at
`src/800.c:5430`.

### NEXT SESSION — in order
1. **Wave T.** `make atlas` FIRST (it predates 161 banks), then
   `build_wave_atlas --target-ins 6500 --min-ins 60 --max-ins 200 --rank mass` **fleet-wide** — NOT
   `--only-bins main`, whose mass band is spent (§180c). Then the pre-gate ladder BEFORE the first
   rebuild: `reconcile_slate --apply` → `fragment_check` → `pregate_check` → `gate_main` dry-run until
   `N -> N compatible, 0 dropped`. Gate with `bisect_slate.py`, never `gate_main --apply` without
   `--no-bisect`. Overlays: convert slates to `gate_lane` shape first (it needs `binary` + `name`).
2. **The 6 SDK objects from §188 Law 3** → `psyq_integrate`. Cheapest instructions on the board, and
   the identification came FROM the strict oracle (unlike §187's refuted claim). Verify with
   `psyq_identify` + a clean rebuild.
3. **The 15 wave-S rejects in `ov_SC04_011`.** That overlay's declaration landscape is the known
   hostile one (6/10 also failed there in wave O). Run the §183 playbook lane; wave R's equivalent
   converted 20 of 21.
4. **`GsSortBg` / `GsSortFastBg` fragment merges** (6 symbols / 526 ins; 2 symbols / 496 ins). §187
   removed the link shortcut, so this is the honest route. A merged draft exists at
   `.run/final10/main/gfx2D_BG0_OBJ_4D8.c` (526/526 ins, 260 mismatched) with the full boundary map in
   the final-10 verdicts. **Merge recipe that worked twice this session:** build a synthetic merged `.s`
   (fragments concatenated in address order, interior `j <symbol>` rewritten to `j .L<addr>`), verify
   with `match_one` against THAT, then hand-substitute the body at the entry symbol's INCLUDE_ASM line
   and delete the other fragments' lines — the whole-binary rebuild is the real oracle.
5. **Do NOT re-run the §177 epilogue lane** (§182/§188). Use `oracle_reorder.py` to file the
   assembler-artifact cases IMMOVABLE instead of drafting them.

### Known-open items
* `func_80031A98` — the one honest wall. An agent PROVED with a minimal cc1 repro that the block-scope
  `extern s16 D_800C5328[][2];` is a hard error against the file-scope flat decl, and all three escapes
  (local 2-D pointer, inline cast, TU retype) fail. Unblock cost: retype 7 declarations + 4 banked
  assignments in `func_80030A14`/`func_8003750C`, then re-verify THEIR bytes.
* `func_80186020` (closeness 5) — grinder/permuter fuel, NOT a hand-lever target: survived ~900 compiles
  across 11 sweeps of a fully-understood `global.c:allocno_compare` tie-break (§186c).
* The AGREE re-gate lane stays CLOSED (measured 5%, S52). Do not reopen.

### Watch-fors
* The `pgrep` bracket trick protects only the PATTERN — a waiter whose command line names the file
  elsewhere (e.g. in a `tail`) never exits (§180d). Cost this session: a 46-min loop on a finished job.
* `gate_main --apply` prints BANKED — **verify `corpus.stubs()` actually dropped before committing.**
* `corpus.stubs()` refuses (correctly) when a binary's `.s` files are missing: after `make clean`, only
  the binaries you re-extracted can be queried. `make extract-all` restores the fleet.
* `tools/make_libgs.sh` is not executable — run it as `bash tools/make_libgs.sh`.
* `psyq_link_region.py --verify` inside `make_libgs.sh` is STALE (missing the Phase-9-required
  `--vram-base`/`--exe`) and reports only the objects it could PLACE — a silently smaller set.
* A workflow killed by the session usage limit resumes cleanly: `Workflow({scriptPath, resumeFromRunId,
  args})` replays completed agents from cache and re-runs only the interrupted ones (proven twice).

## SESSION S52 TASK LIST (2026-08-15, ultracode) — the monitorable view (no TaskCreate tool in this harness build)

- [x] **S52-1 — Preflight + wave-selector repair.** Tree clean @ `commit:2390`, no gate/grinder in flight. Fixed `build_wave_atlas.py`: (a) the already-waved set was a hardcoded `'abcdefghijkl'` wave-letter literal → now a `glob('.run/wave_*_cards.json')` derivation (R33); **NC: old 634 → new 726 taken, strict superset, +92 previously-missable cards from waves m/n**; (b) `--exclude-bins` defaulted to `main` carrying the REFUTED link-defect rationale → default now empty, help corrected to the real (gate-path) reason; (c) new `--only-bins` allow-list (main waves need it — `gate_main` rebuilds once per SLATE, so main has no per-TU gate cost).
- [x] **S52-2 — Atlas regen** (`make atlas`, $0) — the selector was stale by ~448 banks (last regen predates waves J–N).
- [x] **S52-8 — `gate_lane` crash-vs-empty fixed.** A non-zero rc or a missing JSON line is now labelled `‼ CRASH`, prints the stderr tail, records `{'CRASH':True,…}` in the results JSON, lists the never-gated groups in the summary, and exits non-zero. R39 NC both ways: crash→CRASH, honest-empty→not-CRASH.
- [~] **S52-3 — Wave O: MAIN + the UNKNOWN probe** — LAUNCHED (`wf_278b05de-bae`, 49 cards / **6,266 ins**, 2 gate groups). **The selection finding that reshaped this wave: main's agent-lane pool at ≥20 ins is nearly SPENT (21 left after 113 already waved) — main's remaining 52,714 ins are overwhelmingly UNKNOWN-lever, as are 138k fleet-wide.** So wave O is deliberately three arms: 21 main head-crack (avg 145 ins, opus) + 18 main UNKNOWN (avg 122) + 10 overlay UNKNOWN (`ov_SC04_011`, avg 103, sonnet). The UNKNOWN arms are an R37 probe of the biggest unclaimed block on the atlas — 1,239 candidates at 60–120 ins alone. Wave prompt gained §175/§176A–C (statement-order-around-a-call first; pin the interloper; **a pin cannot schedule across a call and can silently DELETE an instruction**).
- [ ] **S52-4 — Independent re-verify (R14) + `gate_main.py --apply`** (one clean rebuild per slate).
- [ ] **S52-5 — R22 clean fleet 213/213 + commit** (task + this log together).
- [ ] **S52-6 — Wave P: overlay TU-packed**, drafted concurrently with the main gate (drafting is tree-free).
- [x] **S52-7 — 11 conflict-dropped main drafts recovered** (waves J/K/L). All 11 re-verified MATCH standalone; the TU-aware `gate_main` then named **7 real TU conflicts the old check missed entirely**, all repaired by adopting the TU's declaration verbatim + casting at the use site — including a NEW variant, casting the CALLEE through a function pointer when the TU prototypes it `(void)` and your call must pass an argument (`((void (*)(s32))func_8001C9D0)(a0)`). All 11 re-verified MATCH after repair; slate now 11/11 compatible, staged for the next main rebuild. **None needed a codegen change — every one was plumbing.** Cookbook **§176d**.
- [x] **S52-10 — `tools/reloc_identity.py` (NEW): the oracle that DISAGREES with `match_one` about symbol identity** (R34). match_one masks relocations, so it cannot see a wrong callee or a wrong global (§174 law 1c). But the target `.s` comment column is the FINAL LINKED WORD, so the true address behind each masked field is recoverable arithmetically and `symbols*.txt` maps it back to a name — $0, no rebuild, and it names the fix. **Three of its own bugs were caught by its negative controls before any verdict was believed:** splat-derived `func_`/`D_` names aren't in the symbol files (first run checked ZERO relocs while reporting clean — R32); a 0x4000 nearest-symbol window mislabelled `func_8001C9D0` as `SsGetMute+0xC50`; and **MIPS o32 REL relocations keep the addend IN THE INSTRUCTION**, so reading it off the operand string fabricated a mismatch for every struct-field/array access (the `+1/+2/+3` signature on `func_801F0734` was a byte-array walk, not three symbol errors). Also refuses to answer when streams aren't index-aligned.
- [~] **S52-11 — The 88-draft "MATCH but gate-rejected" pile, triaged deterministically for $0.** Result: **68 AGREE · 12 MISMATCH · 8 COMPILE-FAIL**. The 12 split into two named, actionable classes: **uniform-delta stale seed symbols** (§171 — `func_80130D48` all 5 relocs off by exactly `0xD1EC`, `func_8016D688` all 5 by `0x65450` → `aprop_symfix` STALE-DELTA rebase) and **wrong field offsets** (`func_80185D6C` +0x10, `func_8017F060` +0x4, `func_80188720` +0xC). `--fix` then mechanically repaired **10 of the 12** (2 correctly REFUSED as **SYMBOL-COLLAPSE** — one draft `extern` standing in for two distinct globals, which a rename cannot fix). MISMATCH 12 → 2, AGREE 68 → 77.
- [x] **S52-12 — LANE KILLED BY MEASUREMENT (R37).** Re-gating 20 of the AGREE drafts (5 groups) banked **1 — 5%**, statistically identical to the project's existing **A10 stored-verdict law** (~0–8%; T1 measured 0/23 on the same kind of pile earlier this phase). **The null is the finding: symbol verification does NOT improve stored-draft re-gate conversion** — a stored draft's rejection is almost never identity, it is TU plumbing or staleness. So `reloc_identity`'s real home is as a **pre-gate check on FRESH drafts** (seconds, removes a whole failure class before the rebuild), NOT as a backlog resurrection tool. The remaining 30 groups are NOT worth 30 rebuilds; lane closed. Banked `func_80186C44` + propagation. **R38 self-note: the 0/23 prior was already in this very log — I should have started from ~8%, not from optimism.**
- [ ] **S52-8 — Tooling debt: `gate_lane` swallows `gate_stage` stderr** (reports a crash as `0/0/0`).
- [ ] **S52-9 — Bank idioms into the cookbook + refresh this checkpoint** BEFORE any pause (memory `bank-idioms-before-checkpoint`).

## 📐 THE WAVE DOCTRINE (adopted 2026-08-15 by Drew, after wave O) — 6,000+ INSTRUCTIONS PER WAVE

**A wave is sized by INSTRUCTION MASS, not by card count.** The public metric is instruction-
weighted, so a wave is worth what its instructions are worth. The card lanes (12–42-ins cousins)
carried ~1,400 ins/wave ≈ 0.011pp of fleet ⇒ ~440 waves to finish. Wave O carried **6,266 ins for
the same gate cost and the same draft rate (47/49)**. That is the shape from here on.

**The recipe** (`--target-ins` implements it; the tool now refuses to under-fill silently):
```
.venv/bin/python tools/build_wave_atlas.py .run/wave_<id>_cards.json 80 \
    --target-ins 6500 --min-ins 60 --max-ins 200 --max-bins 4 \
    --levers head-crack,seeded-crack,redraft,len-vein,integration,family-sweep,UNKNOWN
```
- **`--target-ins 6500`** — draw cards until the instruction budget is met (capped by `n`).
- **`--min-ins 60 --max-ins 200`** — the mass band. Draft rate barely decays with size (wave M 98%
  at avg 51, wave N 92% at avg 65, **wave O 96% at avg 128**), so size is nearly free mass.
- **`--max-bins 4`** — gate cost scales with (binary, TU) GROUPS, not drafts.
- **UNKNOWN is now a first-class lane** (see below). `main` needs `--only-bins main` + `gate_main`.

**THE UNKNOWN UNLOCK (wave O's strategic result).** UNKNOWN is not a difficulty label — it is
"the atlas could not name a lever". Wave O ran 22 UNKNOWN cards as an R37 probe and they drafted
like any other lane. That moves ~138k ins into reach and re-scopes the whole endgame:

| pool (agent-draftable, incl. UNKNOWN) | fns | ins | waves @6k |
|---|--:|--:|--:|
| **mass band 60–200 ins** | 1,762 | **164,357** | **27** |
| 40–59 ins | 1,752 | 84,009 | 14 |
| <40 ins (the old card lanes) | 5,585 | 132,466 | 22 |
| >200 ins | 125 | 36,493 | 6 |
| **total agent-draftable** | **9,224** | **417,325 = 70% of all open ins** | **69** |

Non-agent levers hold the remaining ~175k ins (extend-tell, jtbl-carve, cc1, o0-lane, swaprepeat,
needs-autopsy, plumbing, frame-172) and still need their own lanes.
**Order of work: the mass band first** — 27 waves covering 164k ins, and it is where the
instruction-weighted metric moves fastest per agent spent.

**THE PRE-GATE PROTOCOL (do all five, in order — wave O proved each one earns its place):**
1. **Independently re-verify every claimed MATCH with `match_one`** (R14). Agent self-reports run
   optimistic; wave O happened to agree exactly (47/49), earlier waves did not (wave C claimed
   35/35 → 32 banked; the main probe claimed 6/6 → 4).
2. **`tools/reloc_identity.py --batch`** — the symbol-identity check `match_one` structurally
   cannot do. Seconds, $0, and it removes a whole failure class before a rebuild is spent.
   (Wave O: 46 AGREE / 0 MISMATCH — the first wave of the campaign with zero symbol errors.)
3. **`gate_main.py <slate>` DRY RUN, and iterate until `N -> N compatible, 0 dropped`.** Conflicts
   surface one layer at a time; each fix reveals the next.
4. **Reconcile declarations toward the form the MATCH needs, never arbitrarily** (§176f) — then
   re-verify every converted draft, because a declaration change is a codegen change.
5. **Gate.** main → `gate_main.py --apply` (one clean rebuild per slate). Overlays → `gate_lane`.

## Campaign velocity ledger (T10+)

| wave | lane | cards | standalone MATCH | banked | tokens | tok/bank | lesson banked |
|---|---|--:|--:|--:|--:|--:|---|
| **O** | **mass — main head-crack + main UNKNOWN + overlay UNKNOWN (49 cards / 6,266 ins)** | 49 | **47/49 = 96%** / **6,040 ins** (my independent re-verify agreed exactly) | **50** — 46 main in ONE clean rebuild (`143dbb89` byte-identical) + 4 overlay | ~12.8M | ~256k | **THE 6k-INS WAVE SHAPE + THE UNKNOWN UNLOCK.** 4.4× the card lanes' mass at the same gate cost; UNKNOWN drafts like any lane (⇒ 138k ins re-scoped into reach). First wave with **0 symbol errors** (`reloc_identity` pre-gate). Declaration reconciliation took the slate 5-dropped → **0 dropped**, and 3 of 4 conflicts were load-bearing CODEGEN (§176f). Gate cost 8 attempts: 2 my errors, 3 real tool defects now fixed (typedef ordering, silent bisect-on-build-failure, `short`≠`s16` over-refusal), 3 reconciliation rounds |
| A | adapt SMALL-EDIT | 24 | 18 (75%) | **12** (+1 prop) | ~1.40M | **~117k** | zero stale seed-symbols (the §171 prompt-law works); 6 gate-fails all INTEGRATION shapes (3× decl-type vs TU, 1 arity, 2 TU-context DIFF) → wave-B prompt adds match-the-TU's-existing-decl |
| grinder-1 | permuter | 10 | — | 0 | $0 | — | func_800CB4CC parked at best-1 (warmstart seed); queue enriched +59+6 records since |
| C-probe | tell (3) | 3 | 1 (33%) | **1** | ~300k | ~300k | §174 **Law 4**: the TU's decl of YOUR OWN fn constrains the def sig — standalone MATCH gated 0/1 until canonical-sig + cast-at-use; tell attribution unreliable (2/3 residuals were a different class) |
| C | tell 11 + weak 24 | 35 | **35 (100%)** | **32** (8 propagated ×2) | ~2.39M | ~75k | Law 4 in-prompt → 0 symbol fails, 91% gate; **weak lane 24/24 on haiku — the 890-card vein is live**; 3 NEAR → grinder |
| E-probe | mass/main (6) | 6 | 4 (67%) | **0** | ~474k | — | **main is agent-draftable but LINK-BLOCKED**: 1 byte-correct fn ⇒ 2-byte whole-EXE diff, a `jal` retargeted game-code→PsyQ-archive symbol. Not a matching wall. `gate_lane` main-blindness fixed en route |
| D | adapt (48) | 48 | **47 (98%)** | **45** (40 main gate + 5 late-repair, 2 gates) | ~4.48M | **~100k** | repair stage rescued 5/6 first-pass DIFFs → gate them in a SECOND slate (the first slate is built before the repair stage lands); 23 gate groups for 42 drafts = the throughput ceiling → `build_wave_atlas.py` now packs by **(binary,TU)** = the real gate-group key; 1 NEAR at **close=1 DELAY-SLOT** → grinder |
| **MAIN** | **mass/atlas main probe (4 drafts, re-gated CLEAN)** | 4 | 4 | **4 BANKED — the first main-EXE functions of the campaign** | $0 (re-used the wave-E probe drafts) | — | `func_80013228`/`func_8001CB00`/`func_800142C8` (src/800.c) + `func_8001099C` (src/boot.c, -O0). `make clean && make extract BINARY=main && make build BINARY=main` → **143dbb89 BYTE-IDENTICAL**. These are the SAME drafts the incremental gate rejected 0/4 — the drafts were right, the gate path was wrong |
| **M** | mass/atlas — overlay, LARGER band (44) | 44 | **43/44** shape-verified / 2,212 of 2,249 ins | **40 banked**, ONE gate group; R22 213/213 | ~4.41M | ~110k | **The band test.** Cards avg 51 ins (up to 112) vs the 12–42-ins cousins the night opened with, and the draft rate HELD at 98%. Since the public metric is **instruction-weighted**, this is the band that moves it — and it is reachable by haiku/sonnet, not only the frontier tier. 1 NEAR (close=9, beqz+delay-slot reorder) → grinder |
| **L** | mass/atlas — MAIN (44) | 44 | **44/44 = 100%** | **42 banked** (2 dropped: dup `SVECTOR` typedef + `u8[]`-vs-`char[]`) — main 133 → **175** | ~1.96M | ~47k | First wave carrying **law 1c**. The compile-error shortcut named `SVECTOR at src/800.c:94` + the exact draft in SECONDS where the old bisect burned 28 min. Drove the `gate_main` typedef-stripper fix |
| **K** | **mass/atlas — MAIN (44)** | 44 | **44/44 = 100%** / 674 ins | re-gating (41 compatible / 3 conflict-dropped) — **an earlier "43 banked" report of mine was WRONG, see below** | ~2.36M | — | Third perfect sweep, all haiku. **`tools/gate_main.py` (NEW) drove it**: substitute batch → `make extract BINARY=main` → `make build` → SHA, with bisection. **MY TOOL BUG, caught by R22 not by the tool:** `gate_main` said BYTE-IDENTICAL, then the clean fleet check failed `[FAIL] main`. Cause: my `typesig()` split on the symbol name and kept only the PREFIX, so **`u8 D_x` and `u8 D_x[]` compared EQUAL** — three drafts declared `D_80078D98` inconsistently (1 scalar, 2 array) and the conflict reached the build. Fixed to keep the declarator suffix; NC'd both ways (wave-K conflict now caught; wave-J answer unchanged). **Both failure modes are now on record in the tool: v1 too STRICT (compared parameter names → discarded 2 good drafts), v2 too COARSE (ignored `[]` → passed a real conflict).** |
| **J** | **mass/atlas — MAIN (40)** | 40 | **39/40 = 98%** / 917 of 940 ins | **34 BANKED** (5 dropped for in-TU decl conflicts, 1 DIFF) — main now **38 matched** | ~2.65M | ~78k | **First full wave against the main EXE, and it drafts like any overlay (98%, all haiku).** Gated by the clean-rebuild batch path: substitute → `make extract BINARY=main` → `make build BINARY=main` → **143dbb89 BYTE-IDENTICAL**. **NEW CLASS — in-TU cross-draft decl conflicts:** batching N drafts into ONE `.c` means their `extern`s must agree with EACH OTHER, not just with the file (`D_800A4ED4` s16-vs-u16; `func_8001C9D0` void/void*/s32). Resolved greedily (keep-in-order, drop incompatible): cost 5. Dropped set is recoverable next session via cast-at-use — the same lever that fixed `func_80037368` (`extern u8 D_80076251;` verbatim from `src/shared/clearTbl40.h` + `(&D_80076251)[i]`) |
| I | mass/atlas (44) | 44 | **44/44 = 100%** / 1,602 ins, symfix clean ×44 | **44 BANKED**, ONE gate group | ~4.27M | ~97k | Second perfect sweep; 41 of 44 drawn by **haiku**. Gate reported `0/0/0` twice — an unreported `gate_stage` CRASH (`corpus.CorpusError`: 16 missing `.s`, fallout from MY `make clean`), not a result. Binary then built byte-identical with all 44 substituted; R22 213/213 confirmed (batch included a fleet-shared `engine_core.h` arity fix) |
| H | mass/atlas (40) | 40 | **38 (95%)** / 1,820 of 1,902 ins | **34** of 38, ONE gate group | ~5.05M | ~149k | 2 NEARs banked as permuter fuel with strong diagnoses. **SAFETY FINDING: a `register __asm__("$2")` PIN CAN BE A CORRECTNESS BUG, not just a scheduling choice** — on `func_80182EB0` a value was written before a call and read after it; the hard-reg pin made gcc treat the pre-call store as dead across the call and **silently DROP** `addiu v0,zero,-1` (49 vs 50 ins), then read garbage. Dropping the pin + storing the constant directly before the call recovered it and closed 19/25. Pins are our most-used lever — this failure mode needs a cookbook note |
| G | mass/atlas (36) | 36 | **36/36 = 100%** (independently re-verified) / 2,554 ins | **32** of 33 gated **in ONE gate group**; fleet 95.3→**95.4%** | ~3.16M | ~99k | **Best draft rate of the campaign, on FRESH CRACKS.** 3 held by the symfix audit for inventing symbol names where the target calls **PsyQ `RotTransSV`/`RotMatrixY`** — the just-fixed non-hex handling earned its keep immediately (pre-fix, one such name crashed the whole audit). Pattern: agents reconstruct the CODE reliably and guess PsyQ SYMBOL NAMES unreliably; the deterministic audit is what catches it |
| F | **mass/atlas (60)** — the TU-packed experiment | 60 | **55 (91%)** pre-repair → **59/60** post-repair / 3,508 ins | **56** total (50 + 6 stragglers) of 60, **1 rebuild each** | ~7.16M | ~143k | **THE WAVE SHAPE FOR THE REST OF THE CAMPAIGN.** Fresh-crack lane (no proven body to edit) converts like the seeded lanes; ~3× mass/card (avg 48 ins vs 12–42); **1 rebuild for 50 banks** vs wave D's 23 rebuilds for 45. 2 genuine STALE (agents invented `S80131E00`/`Mat32_…` where the target calls **PsyQ `Square0`/`RotMatrixY`**) held back; 5 "local-only" flags are just local type names (harmless). Straggler batch pending: the repair stage rescued ~6 more AFTER the slate was built (same lesson as wave D — **build the slate after the repair stage lands**) |

- 2026-08-14 — **CAMPAIGN OPEN (T10+, Ultracode).** Wave A: 24 adapt cards → 18/24 standalone (75%) → symfix-first (0 stale — the prompt-law worked) → gate **12 banked + 1 propagation** (~117k tok/bank e2e; stubs → 12,030). 6 NEARs (3 at close ≤3) enqueued to the grinder. Wave B (48 cards, all haiku, 29 binaries) launched with the decl-matching lesson. Grinder pass 1: 0/10 but func_800CB4CC at best-1.

- 2026-08-14 (resume session) — **Checkpoint resume steps 1–2 DONE.** (1) **R22 owed proof banked: `make clean && make extract-all && make check-all` → 213 passed, 0 failed of 213** (`.run/r22_p31_resume.log` EXIT=0) — wave B's banks verified fleet-clean. (2) **`make atlas` regenerated at HEAD `commit:2234`**: 363,525 feature rows / 92,855 distinct bodies (0 newly computed — memo hit); **5,144 groups / 11,994 open instances / 612,325 ins**; warm merges 1,014; seeded 4,710/7,247 skeletons; all assertions green. Open count 12,058→11,994 reconciles with the session's 65 banks. (3) Wave C fuel verified: `.run/wave_p31c_cards.json` = 38 cards (14 tell/sonnet + 24 weak/haiku); grinder idle (heartbeat `done`); gate free. Drew's re-extraction question answered (disc/splat layers gain nothing — deterministic + continuously regenerated; sig/atlas layer regenerated by this step; Ghidra-C re-analysis = targeted-probe candidate only, R37). NOTE: this harness build has no TaskCreate tool — this checklist + log is the monitorable task view (R28 noted plainly).

- 2026-08-14 (resume session, cont.) — **WAVE C COMPLETE: 32 banked, R22 213/213.** Probe→wave cadence (§174 law 3) paid: the 3-card probe cost ~300k tok and returned Law 4, which the 35-card wave then converted at 91% gate with zero symbol failures. Independent re-verify of all 35 drafts by me (R14) before gating: 35/35 MATCH held. **Reach measured honestly: 32 exemplars, only 8 had any sharer, each ×2 → ~1.25× effective.** The ×134 era is over (P25/29/30 harvested the shared cores); fleet-% now moves ~1:1 with exemplars banked, so THROUGHPUT is the lever, not leverage.
  - **THREE instrument defects found+fixed in my own new tooling this cycle** (the R32/R35/R39 class, and the reason R39 exists): (1) `build_wave.py`'s gate-guard used `pgrep -f` via `shell=True` — the wrapping `sh -c` carries the pattern in its own cmdline so it self-matched and refused forever; fixed by invoking pgrep without a shell. (2) The open-stub predicate did `fn in corpus.stubs(binary)` — but `stubs()` returns **addr→Stub**, so every card looked "already-banked" and BOTH pools reported ~0 candidates (I nearly concluded the 622-card adapt pile and 954-card weak pile were spent). Fixed to `{st.symbol for st in ...values()}` and **negative-controlled against the known population** (35 wave-C cards, 32 banked → exactly 3 still open: PASS). (3) I fired wave D once with hand-typed placeholder card names instead of the generated file — caught and stopped within a minute, relaunched from `.run/wave_p31d_args.json`. Recorded, not buried (P9).
  - **Pools are NOT spent (post-fix, honest): adapt 569 candidates, weak 890 candidates.**
  - **STRATEGIC (Drew's question "why are our waves so weak?" — he is right):** the card lanes I have been drawing from are the *mechanical leftovers* (12–42-ins cousins), ≈1,400 ins/wave against 612,325 open ins ≈ **0.23%/wave**. The Atlas already maps where the mass actually is: **head-crack 1,276 groups / 4,248 inst / 186,291 ins** (≈3.3 inst per group — a group head crack banks its members), **UNKNOWN 1,964 / 138,597**, extend-tell 575 / 76,730, redraft 280 / 46,769, jtbl-carve 190 / 45,673. And high-reach groups DO remain: gid `96f8b78ec8d3` = **265 instances / 6,084 ins** (integration lever, 31-ins exemplar), `75cec648ba15` = 116 inst / 3,002 ins, `152d63c1086d` = 64 inst / 1,559 ins. **Next: build the wave generator off `.run/atlas.json` groups (top instruction-mass first, routed by the group's measured lever) instead of the leftover card piles.**

- 2026-08-14 (resume session, cont. 2) — **THE TARGETING CORRECTION (Drew's "why are our waves so weak?" — he was right).** Measured the arithmetic: **635,744 ins open (4.7pp of fleet) across 11,994 fns**; the adapt/weak card piles I had been drawing are the 12–42-ins best-seeded tail ⇒ ~1,440 ins/wave = **0.011pp/wave ≈ 440 waves to finish**. The mass is elsewhere: cousin-multi 294k ins (avg 44), **cold 183k (avg 82, no seed)**, main-only 38k (avg 87). TWO fixes:
  1. **`tools/build_wave_atlas.py` (NEW)** — wave selection off `.run/atlas.json`, on two measured principles: **(a) gate cost scales with (binary,TU) GROUPS, not drafts** — each group is a whole-binary rebuild, and wave C was 35 drafts over 27 groups = 1.3 drafts/rebuild (~50 min of gate for 32 banks); the atlas selector concentrates a wave into few binaries (**96 drafts → 1 group**, ~70× the gate efficiency); **(b) mass beats count** for the instr-weighted metric. 7,430 draftable candidates available in the agent-lever bands.
  2. **`gate_lane` was STRUCTURALLY BLIND TO `main`** (R36/R33): it located a stub's home .c by `glob('src/<binary>/*.c')`, but main's sources live at `src/*.c` → every main draft grouped under `src=None`. Latent because **main has never been wave-gated** (main = 79,510 weighted ins at 0.5%, the largest coherent mass left). Fixed to derive from `corpus.stubs()[..].path`; NC'd 3 ways (still-open wave-C drafts 3/3 agree · overlay sample 96/96 agree · main now resolves `None`→`src/800.c`).
  - **MAIN PROBE (6 cards, R37 — never spend 96 agents on an unproven path): 4/6 standalone MATCH (67%)**, including the `-O0` boot-module fn `func_8001099C` (the main-specific trap: `asm/nonmatchings/boot` → `src/boot.c` is **-O0** per §6, so match_one needs `--o0`; flagged in the mass-lane prompt). **Main is agent-draftable.** Gate result pending.
  - **RULE VIOLATION CAUGHT (P9, recorded):** a wave-E agent wrote its body directly into `src/boot.c` instead of its draft dir — caught by `git status`, reverted, gate re-run clean. A dirty tree ABORTS the shared gate for the whole wave, so the wave prompt's HARD RULES were hardened (explicit "never write into the tree, not even to test; no state-changing git commands").
  - Wave D (48 adapt cards) drafted 47/48 concurrently — drafting and gating overlap safely (drafts land in `.run/`, the gate writes `src/`).

- 2026-08-14 (resume session, cont. 3) — **MAIN'S BLOCKER DIAGNOSED — it is LINK-LEVEL, not matching.** Main probe: 4/6 standalone MATCH (my independent re-verify; the workflow's own repair stage claimed 6/6 — the gate and my check disagree with the agents, R14), then **gate 0/4 banked, 4 near**. Reproduced one (`func_80013228`, a clean 27-ins `Square0` wrapper) through `harvest_verify` and byte-diffed the built EXE against the original: **exactly 2 bytes differ in 413,696**, and NOT inside the drafted function — a `jal` at **vaddr 0x80060E74** retargeted from **`func_80061FA8`** (game code, `build/src/800c2.o`) to **`firstfile`/`firstfile2`** (**PsyQ libapi object `build/psyq/apicard/A66.o`**, symbols.us.txt line: `firstfile2 = 0x80062248`). So adding ONE byte-correct C function to `src/800.c` perturbs **symbol resolution between game code and the LINKED PsyQ library objects** — the C is right; the link binds a call to a different definition. This is main-specific (main is the only binary with `psyq_integrate` archive objects, per the `ifeq ($(BINARY),main)` blocks) and explains why main has sat at 0.5%: it is an INTEGRATION wall, not a matching wall. **Main is NOT ready for bulk waves; it needs a named link-resolution investigation lane** (candidate leads: duplicate `.NON_MATCHING` symbol definitions visible in the map at both `Square0` and `func_80061FA8`; archive-member selection order when a new undefined ref appears in `src/800.o`). Recorded here + decision-log (R31). The 4 main drafts are preserved in `.run/wave_p31e/main/` as fuel for that lane.
- 2026-08-14 — **Campaign returned to the lanes that bank.** Wave D (48 adapt cards) drafted; independent re-verify **42/48 MATCH (87.5%)**; 6 DIFF handed to the near/grinder path. Gating now.

- 2026-08-15 — **Wave D closed: 45/48 banked. R22 clean fleet 213/213. Stubs 12,059 → 11,876** (183 banked this phase; ~118 tonight). Committed `commit:2324`. **Wave F LAUNCHED — the first TU-packed wave**: `build_wave_atlas.py` now packs by **(binary, home .c)** — the real `gate_lane` group key — giving **60 drafts / 3,508 ins in ONE gate group** (vs wave D's 42 drafts / 23 groups). Target `ov_SC02_011` `jr_8017AE2C`, avg 48 ins (vs the card lanes' 12–42), 70 head-crack + 17 redraft + 4 seeded + 2 integration + 2 len-vein + 1 family-sweep; 32 sonnet / 28 haiku. **This is the throughput experiment**: same gate cost as ~2 wave-D groups for 60 functions of larger mass. 6,981 candidates remain in the atlas's agent-draftable levers (`main` excluded).

- 2026-08-15 — **WAVE F RESULT: the TU-packing thesis is CONFIRMED, and the fresh-crack lane works.** 60 atlas `mass` cards (no proven seed to edit — agents decompile from the .s) → **55/60 = 91% standalone**, **3,203 of 3,508 instructions**, in **ONE gate group**. Wave D needed 23 whole-binary rebuilds for 42 drafts; wave F needs 1 for 60. Per-card mass is ~3× the card lanes'. **This is the wave shape for the rest of the campaign** — `build_wave_atlas.py --max-bins 1..6`, 60–96 cards.
  - **NEW TOOL DEFECT (logged, not yet fixed): `aprop_symfix` CRASHES on non-hex symbol names.** `deltas[int(new[-8:],16) - int(old[-8:],16)]` assumes every symbol is `func_XXXXXXXX`/`D_XXXXXXXX`; a draft calling **PsyQ `Square0`** raises `ValueError: invalid literal for int() with base 16: 'Square0'` and takes the whole audit down. This will recur on every PsyQ-calling draft. **Fix wanted:** treat a stale pair whose names are not hex-suffixed as a direct 1:1 rename (no delta), and never let one unparseable pair abort the batch (R32: a crash is not a coverage answer). Workaround used: gate the 53 clean drafts, hold the 2 genuine STALE for a hand rename.
  - **Grinder ran concurrently with drafting** (free CPU, no tree writes during permute) on the close≤6 seeds: 3 ILS cycles each on the md_MAIN_* band, **0 banked, all parked at best-1** — plus it re-surfaced the Phase-22 split-file blindness (`func_800CB270: no .s under md_MAIN_027 — skip`). Stopped via the STOP sentinel to hand the tree to the wave-F gate (single-writer discipline; the gate is chained to start on grinder release).

- 2026-08-15 — **Wave G: 36/36 drafted (100%), 32 banked, fleet 95.3→95.4%.** Two TU-packed waves now confirm the shape. **`aprop_symfix` non-hex fix landed** (`commit:2330`): a curated PsyQ name (`Square0`) made `int(name[-8:],16)` raise and abort a 55-draft audit *after* the renames had already succeeded; now counted as a `named-1:1` rename and the batch survives. Verified on the literal incident values (old aborts, new completes + still buckets the hex pair by its `0x484c` delta); honest caveat — the live slates could not re-trigger the path because those drafts are banked, so the changed expression was exercised directly.
  - **Standing pattern worth keeping in the prompt:** agents reconstruct CODE reliably (91–100% standalone) but guess **PsyQ symbol NAMES** unreliably (wave F: `S80131E00`→`Square0`, `Mat32_…`→`RotMatrixY`; wave G: `SRM_…`/`STM_…`→`RotTransSV`, `Blk20_…`→`RotMatrixY`). The deterministic symfix audit — not the model, and not `match_one` (which masks relocations and is BLIND to a wrong callee name) — is what catches this every time. Consider adding "if the target's .s calls a PsyQ symbol, use that exact name" to the wave LAWS.

- 2026-08-15 — **`aprop_symfix` FALSE-POSITIVE class found (R39), and it cost real banks — my error, not the tool's alone.** I withheld 3 wave-G drafts from the gate because symfix reported them `STALE`/`AMBIGUOUS`. On inspection **all 3 already used the correct PsyQ names** (`RotMatrixY`, `RotTransSV`); what symfix flagged as "draft-only symbols" were **local identifiers** — a typedef (`Mtx8_8017DE10_8017E710`), inline-asm macro names (`SRM_80186334`/`STM_80186334`), and local struct typedefs (`Blk20_…`/`Vec32_…`). Gated unchanged: **3/3 banked** (wave G → 35/36). Two defects behind it: (a) the classifier counts local typedef/macro names as symbol references; (b) its draft-symbol extraction misses some `extern` declaration forms, so a name the draft *does* declare (`RotMatrixY`, line 8) still shows as `asm-only`.
  - **OPERATING RULE (adopt now): symfix flags are ADVISORY; the whole-binary gate is the arbiter.** Never withhold a standalone-MATCH draft from the gate on a symfix flag alone — gate it and let the bytes decide. R39's own wording applies to *me* here: a refusal check that silently discards good work is worse than one that lets a few failures through. (Law 1b in the wave prompt remains correct as *prevention* — the wave-F cases were genuinely wrong names.)

## Blockers
- 🔴 **CORRECTION (2026-08-15, R14/R35/P9 — I got this WRONG earlier tonight and reported it with confidence).** The "main is blocked on a LINK-RESOLUTION defect" conclusion below is **REFUTED**. It is a **stale-artifact / missing-extract** condition in the GATE'S BUILD PATH — the R22 corollary this project already documented at Phase 20 — not a linker bug and not anything to do with the drafts.
  - **The control that killed it:** with `src/` fully reverted and **NO draft at all**, `make build BINARY=main` still produced the "broken" `c4546248` and the identical 2-byte diff. A defect that reproduces with zero drafts is not caused by drafts.
  - **The fix, byte-proven both ways:** `make extract BINARY=main && make build BINARY=main` → **`143dbb89…` BYTE-IDENTICAL**, reproduced twice. `make build` alone → `c4546248` + the 2-byte `jal` diff, deterministically.
  - **Why main and not overlays:** main's `extract` runs the EXE-only `psyq_integrate` + `ld_interleave` steps (the `ifeq ($(BINARY),main)` Makefile blocks) which **rewrite the linker script**. `gate_stage`/`harvest_verify` build **without** re-extracting, so main gates against a stale `.ld` — exactly the "a reverted config needs a re-extract, not just a rebuild" corollary. Overlays have no such step, so they are unaffected (and every overlay bank tonight is R22-verified from a genuinely clean tree).
  - **What this means: main is very likely NOT blocked at all.** Its 79,510 weighted ins @ 0.5% are gated behind a TOOLING gap in the main gate path, not a compiler or linker wall. **Next step (do this first):** teach the main path to re-extract (or re-run `psyq_integrate`) before the gate build — then re-gate the 4 preserved drafts in `.run/wave_p31e/main/` (2 of which reference no PsyQ symbol at all). The earlier "archive-member selection" evidence (the broken map gaining ~20 PsyQ symbols + `firstfile` at `0x80062248`) is a **downstream symptom of the stale `.ld`**, not the cause.
  - **The false-lead ledger, kept honestly:** I built a 3-hypothesis theory on a measurement whose instrument I had not controlled, and only the null-draft control exposed it. Same lesson as the `corpus.stubs()` misread and the symfix withholding earlier tonight — three instrument errors in one session, all mine.
- *(superseded, kept for the trail)* ~~main is blocked on a LINK-RESOLUTION defect~~ — see the 2-byte `jal` retarget above. Needs its own lane before any main wave is worth running. Overlay/md lanes are unaffected and continue to bank.
  - **NARROWED 2026-08-15 (a specific, testable lead).** The call site is `asm/nonmatchings/libmcrd1/func_80060D9C.s` +0xD8, and it references the callee **BY NAME**: `jal func_80061FA8`. Original encodes `0x80061FA8`; our build with one extra C function encodes `0x80062248`. **The delta is exactly `0x2A0`, which the map shows is precisely the `.text` SIZE of `build/src/800c2.o`** — the object whose `.text` *starts* at `0x80061FA8` (map line 3712: `.text 0x80061fa8 0x2a0 build/src/800c2.o`, with `func_80061FA8` and `func_80061FA8.NON_MATCHING` both bound there, and `func_80062144` inside it). So the name `func_80061FA8` resolved to the **END** of that object instead of its start — i.e. one object's length later, landing on the next section's first symbol (`firstfile`, `build/psyq/apicard/A66.o`). **Hypotheses to test, in order:** (1) the duplicate `func_80061FA8` / `func_80061FA8.NON_MATCHING` pair — a second definition winning under a changed link order; (2) `800c2.o` being dropped/reordered when a new undefined ref appears in `src/800.o`, so the name binds to the following object; (3) an `undefined_syms_auto.txt` / `symbols.us.txt` absolute (`firstfile2 = 0x80062248`) shadowing the object-provided symbol. Everything needed to test is in `build/us/SLUS_007.26.map` + `.run/wave_p31e/main/*.c` (4 preserved main drafts).



## 🛑 (superseded by S53) SESSION CHECKPOINT — S52 FINAL (2026-08-15/16)

**Tree CLEAN at `commit:2415`. No process running. R22 verified 213/213 from a clean tree after the last bank.**

### Banked this session: 131
Wave O 46 main + 4 ov · re-gate probe 1 · wave P 32 main + 8 md · wave Q 40 main.
**main 175 → 293 matched · stubs 1,881 → 1,763.** Fleet 213/213 byte-identical, 0 NON_MATCHING.

### Measured wave economics — the numbers to plan with
| wave | carded | drafted | BANKED | yield |
|---|--:|--:|--:|--:|
| O | 6,266 ins | 96% | 5,166 | **82%** |
| P | 6,589 ins | 97% | 4,501 | **68%** |
| Q | 6,249 ins | 58% (stopped early) + repair | ~3,000 | ~48% |

**~4,800 banked ins/wave when a wave runs to completion (≈75% of carded mass)** — NOT 6,000. I
quoted the *draft* rate for most of the session and that overstated it. Still ~5× the old card
lanes; ~87 waves for the 417k-ins agent-draftable pool.

### THE FOUR RESULTS THAT OUTLIVE THE COUNT
1. **UNKNOWN is not a difficulty label** — it means the atlas could not name a lever. A 22-card R37
   probe drafted it like any other lane ⇒ ~138k ins (a quarter of all open instructions)
   reclassified as ordinary wave fuel. Agent-draftable pool: **9,224 fns / 417,325 ins = 70%**.
2. **Matching is solved at this scale; INTEGRATION is the entire cost.** 96–97% draft rates with
   zero symbol errors, then ~14 clean rebuilds to bank them. Every failure was declaration plumbing.
3. **Reconcile BEFORE the first gate (§176h.C2).** Of 18 parked drafts still verifying MATCH, only
   **1** survived the conflict check after their wave banked, versus 5 before. Post-bank recovery
   banked **0**. Budget reconciliation into the wave.
4. **§177 — the epilogue return-delay slot is decided by the SAVED-REGISTER SET**, not scheduling
   (`mips.c:5376 mips_epilogue_delay_slots`). Eleven functions sat 1–3 instructions from banked,
   filed by every agent as an intrinsic wall. ~600 ins unblocked by forty lines of compiler source.

### Tooling built this session (all committed, all NC'd)
**NEW** `reloc_identity.py` (symbol identity — the oracle `match_one` structurally cannot be) ·
**NEW** `pregate_check.py` (validates a slate in 0.7s vs a 5-min rebuild) ·
**NEW** `reconcile_slate.py` (drives a slate to 0-dropped; auto-reverts any repair that moves a byte) ·
**NEW** `fragment_check.py` (the enclosing-function trap: a draft that SUBSUMES another symbol, or
that REDEFINES another stub's symbol in asm — the second cost a 3-hour bisect) ·
**NEW** `bisect_slate.py` (**null control FIRST**, per-step logging, true binary search — found the
culprit in 7 steps / 176s where `gate_main`'s built-in bisect ran 3 hours and named nothing) ·
`build_wave_atlas` `--target-ins`/`--only-bins`/`--rank mass` + 2 selector bugs · `gate_lane`
CRASH≠empty · **`gate_main` ×8 defects**.

### Cookbook banked: 543 → 564 sections
§176d–k (TU-seeded conflicts · symbol identity computable offline + its 5% null · declaration FORM
as a matching lever · the 6k-ins doctrine + 5-step pre-gate protocol · the batch-substitution hazard
map incl. **C2 reconcile-before-gating** · what a static pre-gate can/cannot prove · the cost of
stopping a wave + the measured repair-pass yield · two selector bugs) ·
**§177** epilogue delay slot ← saved-register set ·
**§178** six levers from the wave-P journals (the $0-add opaque copy vs `make_regs_eqv`;
return-const as a priority-1 hard-reg set; `birthing_insn_p` single-set rule; narrow-type copy
elision; the zero-offset alias hole; `MEM_IN_STRUCT_P` asymmetry) — leads with **"REGALLOC-PERM is
this project's most over-diagnosed class"** ·
**§179** eight more, harvested by 12 readers over 172 journal findings (loop-walked pointer
parameter → giv; the maspsx transcription checklist; no-epilogue functions; `gte_stflg` clobber;
struct-assignment block copy; pinning disables strength reduction; a pin creating a combine
LOG_LINK; mid-body `.global` fragment slicing).

### NEXT SESSION — in order
1. **Wave R the new way.** `build_wave_atlas --target-ins 6500 --min-ins 60 --max-ins 200
   --rank mass`, then **iterate `reconcile_slate --apply` → `fragment_check` → `pregate_check` →
   `gate_main` dry-run until `N -> N compatible, 0 dropped` BEFORE the first rebuild.** That
   sequence is the whole difference between 68% and ~95% yield, and every tool in it now exists.
   Use `bisect_slate.py`, never `gate_main --apply` without `--no-bisect`.
2. **Apply §177 to the eleven epilogue near-misses** (`800c`/`800c3`, closeness 1–3, ~600 ins).
   Pure lever application, no drafting: change what is live across the call, re-verify, gate.
3. **4 immovable-TU-declaration drafts** (`func_8002D034`, `func_8001ABBC`, …) need their own pass:
   edit the declaration in `src/800.c`, ONE clean rebuild, R22. They cannot ride a slate because
   `gate_main` reverts `src/` before every build.
4. Grinder fuel: `func_80015F04` at closeness 2 with a fully-derived sched1/sched2 LUID model and
   three seeds in `.run/p31p_15F04/`; plus wave-Q leftovers in `.run/wave_p31q/main/`.

### Watch-fors (all bit this session)
`gate_main`'s built-in bisect is near-linear and silent — use `bisect_slate.py`. · A wave stopped
mid-flight loses its in-flight tail; a repair-only pass recovers ~⅓ of it (12/39, 579 ins), but
resuming the workflow re-runs unfinished agents from scratch at full cost. · `pgrep -f` self-matches
its own shell wrapper — use the `[g]ate_main` bracket trick. · Closeness must be COUNTED, not read
off the first differing index. · A clean `pregate_check` is a licence to build, not a prediction of
success: link errors and byte mismatches are outside what any text check can see.

## 🛑 (superseded) SESSION CHECKPOINT — S52 mid-day

**Tree CLEAN at `commit:2407`. R22 verified 213/213 from a fully clean tree after the last bank. Nothing owed, nothing in flight.**

### Banked: 91 functions
46 main + 4 ov (wave O) · 1 (re-gate probe) · 32 main + 8 md (wave P). **main 175 → 253 matched · stubs 1,881 → 1,803.** Fleet 213/213 byte-identical, 0 NON_MATCHING.

### The two waves, measured honestly
| wave | cards / ins | drafted (my re-verify) | symbol errors | BANKED ins | yield |
|---|---|---|--:|--:|--:|
| O | 49 / 6,266 | 47/49 (96%) | 0 | 5,166 | 82% |
| P | 60 / 6,589 | 58/60 (97%) | 0 | 4,501 | 68% |

**The number to plan with is ~4,800 BANKED ins/wave (75% of carded mass), not 6,000** — I quoted the draft rate for most of the session and that overstated it. Still ~5× the card lanes' ~1,400. Revised projection: **~87 waves** for the 417k agent-draftable pool, not 69.

### THE THREE RESULTS THAT OUTLIVE THE COUNT
1. **UNKNOWN is not a difficulty label** — it means the atlas could not name a lever. A 22-card R37 probe drafted it like any other lane ⇒ ~138k ins (a quarter of everything open) reclassified as ordinary wave fuel. Agent-draftable pool is now **9,224 fns / 417,325 ins = 70% of all open instructions**.
2. **Matching is solved at this scale; INTEGRATION is the whole cost.** 96–97% draft rates and zero symbol errors across two waves, then ~14 clean rebuilds to bank them. Every failure was declaration plumbing — N standalone drafts having to agree with each other and with a TU none of them can see.
3. **Reconcile BEFORE the first gate (§176h.C2).** Measured: 18 parked drafts still MATCH, but only **1** survived the conflict check after their wave banked (vs 5 before). A banked draft's declarations become the TU's, so a sibling clash becomes a file clash, which is stricter. The post-bank recovery pass banked **0** — this law cost real work to learn.

### Tooling built/fixed (all committed, all NC'd)
**NEW** `tools/reloc_identity.py` (symbol identity, the oracle `match_one` structurally cannot be) · **NEW** `tools/pregate_check.py` (validates a slate in **0.7s** instead of a 5-min rebuild) · `build_wave_atlas --target-ins/--only-bins` + glob-derived taken-set · `gate_lane` CRASH≠empty · **`gate_main` ×8**: TU-seeded + per-file conflicts, definition-aware, trailing-comment-blind regexes (×2), typedef alias normalization, address-order walk, build errors surfaced instead of bisected, body+position-aware typedef handling.

### Cookbook banked
**§176d** TU-seeded conflicts + callee function-pointer cast · **§176e** symbol identity is computable offline (+ its honest 5% null) · **§176f** declaration FORM is a matching lever · **§176g** the 6k-ins doctrine + 5-step pre-gate protocol · **§176h** the batch-substitution hazard map (7 under-reporting holes, the 3 wrong typedef strategies, the spelled-name limit, **C2 reconcile-before-gating**).

### NEXT SESSION — in order
1. **Wave Q the NEW way**: build with `--target-ins 6500 --min-ins 60 --max-ins 200 --max-bins 4`, then **iterate `pregate_check` + `gate_main` dry-run to `N -> N compatible, 0 dropped` BEFORE the first rebuild.** That is the whole difference between 68% and ~95% yield.
2. The 4 **immovable-TU-declaration** drafts (`func_8002D034`, `func_8001ABBC`, …) need their own pass: edit the declarations in `src/800.c`, ONE clean rebuild, R22.
3. 5 genuine NEARs → grinder. `func_80015F04` is at **closeness 2** with a fully-derived sched1/sched2 LUID model (9/9 probes predicted) and three seed candidates in `.run/p31p_15F04/`.
4. Latent, unfixed: conflict detection compares spelled type NAMES; comparing struct **bodies** (the auto-reconciler already does this) is the real fix.

## 🛑 (superseded) checkpoint — S52 mid-session

**State at checkpoint:** tree CLEAN at `commit:2402` + wave-O bank commit. **R22 verified 213/213 from a fully clean tree** after wave O. Nothing owed.

### What S52 banked
**51 functions** — 46 main (ONE clean rebuild, `143dbb89` byte-identical) + 4 overlay (`ov_SC04_011`) + 1 from the re-gate probe. **main 175 → 221 matched, stubs 1,881 → 1,835.**

### THE TWO RESULTS THAT MATTER MORE THAN THE COUNT
1. **UNKNOWN IS NOT A DIFFICULTY LABEL.** It means "the atlas could not name a lever", and it had been routed as needing its own bespoke lane. Wave O's 22-card R37 probe drafted it like any other lane ⇒ **~138k ins (a quarter of everything open) reclassified as ordinary wave fuel.** With UNKNOWN in, **9,224 fns / 417,325 ins = 70% of all open instructions** are agent-draftable.
2. **THE 6k-INS WAVE DOCTRINE (adopted by Drew).** A wave is sized by INSTRUCTION MASS, not cards — see the doctrine section above for the recipe and the pre-gate protocol. Draft rate barely decays with size (M 98% @51 ins · N 92% @65 · **O 96% @128**), so mass is nearly free. Projection: **~69 waves**, mass band first (27 waves / 164k ins), vs ~440 under the card lanes.

### IN FLIGHT AT CHECKPOINT
**Wave P** (`wf_faa2b5e5-a80`, 60 cards / 6,589 ins, 2 gate groups: main ×51 + md_SC07_004 ×9) — hit the **weekly limit** at 18/60 drafted, then RESUMED (`w8xrn5y3i`). Cached agents replay; the 42 failures re-run. On completion: run the 5-step pre-gate protocol, then `gate_main --apply` for the main half and `gate_lane` for md_SC07_004.
- The 18 already-drafted are all MATCH-claimed; **my independent re-verify is still OWED** (the classifier rate-limited Bash mid-check). Do it before gating.

### Tooling fixed this session (all committed, all NC'd)
`reloc_identity.py` (**NEW** — the symbol-identity oracle `match_one` structurally cannot be, §176e) · `build_wave_atlas` (`--target-ins`, `--only-bins`, glob-derived taken-set, refuted main-exclusion default) · `gate_lane` (CRASH ≠ empty result) · `gate_main` ×4 (TU-seeded + per-file conflict table · typedef walk in ADDRESS order · build errors surfaced instead of silently bisected · `short`≡`s16` alias normalization).

### Cookbook banked this session
**§176d** TU-seeded conflicts + the callee function-pointer cast · **§176e** symbol identity is computable offline (+ the honest null: it does NOT rescue stored drafts, 5%) · **§176f** the declaration FORM is a matching lever · **§176g** the 6k-ins doctrine + the 5-step pre-gate protocol.

### Known-open items
1. `func_8002D034` — verified MATCH but needs `src/800.c`'s `D_800A4E74` decl changed u16→s16; `gate_main` reverts `src/` before building, so it cannot ride a slate. Recover as its own commit + verifying rebuild.
2. `func_80016224` — verified MATCH but requires `volatile D_800B9A02`, which is fatal to two other drafts. Near-fuel until the TU's form settles.
3. 6 of the 10 `ov_SC04_011` wave-O drafts failed the gate on TU plumbing (that overlay's own decl landscape).
4. The AGREE re-gate lane is CLOSED (measured 5% ≈ the A10 law). Do not reopen it.

## 🛑 (superseded) CHECKPOINT — OVERNIGHT CAMPAIGN CLOSED 2026-08-15 (morning)

**Cron `be8fb48c` (23-min overnight heartbeat) is CANCELLED.** No wave will fire on its own. Nothing is in flight at handoff.

### What this session did (waves C–N)
**~448+ banked** · stubs **12,059 → 11,549** · fleet **95.4% instr** · **213/213 byte-identical after every single batch** · 0 NON_MATCHING · **main 0 → 175 matched**.
Draft rates 91–100% across twelve waves, overwhelmingly **haiku/sonnet writing byte-exact C from raw MIPS with no reference body**. Four perfect sweeps (36/36, 44/44, 44/44, 44/44).

### The three things that actually changed the campaign
1. **MAIN IS OPEN — and was never hard.** It sat at 0.5% for the whole project, written up as the largest/hardest remaining mass. The blocker was that `gate_lane`/`gate_stage` build INCREMENTALLY while main's `make extract` runs the EXE-only `psyq_integrate`/`ld_interleave` steps that REWRITE the `.ld` → false diff (R22's own rationale). Four byte-correct drafts were rejected; I diagnosed a "linker defect" and built 3 hypotheses on it. **A null-draft control killed it** (the defect reproduced with ZERO drafts substituted). Use **`tools/gate_main.py <slate> --apply`**: substitute batch → extract → build → SHA; ONE clean rebuild verifies a WHOLE batch (40+ per rebuild). ~913 main stubs remain and they draft at 98%.
2. **GATE-GROUP PACKING is the throughput lever.** Gate cost scales with **(binary, TU) groups**, not drafts — each group is a whole-binary rebuild. Wave D: 42 drafts / 23 groups. Waves F–N: 40–56 drafts / **1 group**. `tools/build_wave_atlas.py` packs by TU and ranks by instruction mass; `--min-ins 40` targets the band the public instr-weighted metric tracks (wave M held 98% at avg 51 ins; wave N 92% at avg 65).
3. **`match_one` VERIFIES SHAPE, NOT SYMBOL IDENTITY.** It masks jal/HI16/LO16, so a draft calling the wrong function or storing to the wrong global reports a clean MATCH (wave K: `func_8002A234` had two globals swapped — 5 gate attempts). Only the whole-binary gate catches it. Now law 1c in the wave prompt.

### Tooling built/fixed this session (all committed, all NC'd)
`tools/gate_main.py` (NEW — batch clean-rebuild gate for main; in-TU decl-conflict resolution on TYPE SIGNATURES ONLY; duplicate-typedef stripping; compile-error culprit naming instead of bisection; **rm-output+returncode check after it once reported a FALSE PASS off a stale binary**) · `tools/build_wave_atlas.py` (NEW — TU-packed, mass-ranked selection; `main` excluded by default) · `tools/build_wave.py` (NEW — adapt/weak pools) · `gate_lane` home-TU resolution derived from `corpus` (was blind to main) · `aprop_symfix` survives curated PsyQ names · cookbook **§174 law 1b/1c**, **§175** (caller-saved pins can DELETE an instruction across a call).

### Idioms banked before this checkpoint (Drew's rule, 2026-08-15 — memory `bank-idioms-before-checkpoint`)
**Everything learned this session is in `docs/matching-cookbook.md`, not just in commit text.**
- **§174 Law 1b/1c, Law 4** — PsyQ symbol names; `match_one` verifies SHAPE not SYMBOL IDENTITY; the DEF-side prototype constraint.
- **§175** — a pin to a CALLER-SAVED register can silently DELETE an instruction when the value's live range crosses a `jal`.
- **§176a/b/c** (mine, process-level) — the verification-layer laws (what each check can and cannot prove); batch-gating mechanics (gate cost scales with (binary,TU) groups; batched drafts must agree with each other; compile errors name their own culprit); main cannot be gated incrementally.
- **§176 A–F** (agent-discovered, mined from all 14 wave journals by a 15-agent workflow; 26 novel of 81, each cross-checked against the existing cookbook first):
  - **A — statement order around a call** is the FIRST check for any schedule/delay-slot/±1 residual. Two functions that first-pass agents filed as "irreducible tie-break / permuter fuel" went to MATCH by moving ONE statement above a call.
  - **B — a small REGALLOC-PERM is usually not allocation** (narrow-symbol aliasing; pin the interloper, not the contested value).
  - **C — 🔴 WALL REFUTATION, source-verified by me:** `gcc-2.7.2 sched.c:1704` tests `call_used_regs[i]` where every neighbouring line uses `regno + i`, so for a 1-word register it always tests `$zero` (call-used on MIPS) ⇒ **every hard-reg SET in a block gets a REG_DEP_ANTI on the last call**, while the pseudo arm is guarded by `reg_n_calls_crossed`. **A PIN CANNOT SCHEDULE AROUND A CALL — sometimes the fix is to UNPIN.** Refutes the universality of `sched.md` S11 step 1 and the "always try pins" reflex.
  - D/E/F — CSE levers in reverse, two cc1-probed spellings, and four residual verdicts that were lying.
  - The section ends with an explicit **"What is NOT banked here"** listing 7 mined items judged too thin — including two whose functions are still `INCLUDE_ASM` (so the lever is unverifiable) and one whose narrative **contradicts** the banked C. Nothing was silently dropped.

### Open work, in priority order
1. **Run main waves** — highest value, ~913 stubs, 98% draft, `gate_main` handles it.
2. **`gate_lane` swallows `gate_stage` stderr** — reports an unhandled crash as `0 banked / 0 near / 0 failed`, indistinguishable from an honest empty result (cost 2 cycles). Make it surface stderr / distinguish CRASH from NOTHING-BANKED.
3. **Recover ~10 conflict-dropped main drafts** (waves J/K/L) — verified-correct, need cast-at-use.
4. Grinder queue has fresh seeds incl. **close=1 DELAY-SLOT** (`func_80183578`) and count-exact `func_8017DAEC`.

### The methodological lesson (worth more than the count)
Every serious stall traced to **an instrument trusted without a control**, never to gcc: the main "linker defect"; `corpus.stubs()` read as names when it returns addr→Stub; 3 good drafts withheld on an ADVISORY symfix flag; `gate_lane` crash-as-zero; my conflict checker too strict then too coarse; my verifier passing without building. **Before believing a measurement, run the control that would make it fail** — a null input, a known-answer population, or an independent oracle. The counterweight: the safety architecture held every time. R22 caught the false pass, `corpus` refused to guess, and the byte-gate never accepted a wrong match.

## (superseded) mid-flight checkpoint

**Phase 31 CONTINUES.** Overnight campaign running under Drew's "waves and banking all night long" directive (Opus 5, ultracode, 23-min cron heartbeat `be8fb48c` as the loop's safety net).

**This session's arc:** resume R22 213/213 → atlas regen (5,144 groups / 11,994 open) → wave-C probe (3 tell) → wave C (35: 11 tell + 24 weak) **32 banked** → main probe (6) **0 banked, blocker diagnosed** → wave D (48 adapt) **47/48 standalone, gating now**. Session banked ≈ **59+** (18 mechanical/probe + 32 wave C + wave D in flight).

**THE TWO STRATEGIC FINDINGS (read these first on resume):**
1. **Reach is spent: ~1.25×.** 32 wave-C exemplars → only 8 had a sharer, ×2 each. The ×134 era ended in P25/29/30. Fleet-% now moves ~1:1 with functions banked ⇒ **throughput is the lever**, and the throughput bottleneck is the GATE, whose cost scales with **(binary,TU) groups, not drafts** (wave C: 35 drafts/27 groups; wave D: 42/23). `tools/build_wave_atlas.py` (NEW) concentrates a wave into few binaries (96 drafts → 1 group) and weights by instruction mass — **use it for every future wave**; the adapt/weak card piles are the 12–42-ins tail (~0.011pp fleet per 48-card wave ≈ 440 waves to finish).
2. **main is BLOCKED on a LINK defect, not on matching** (see Blockers). `--exclude-bins main` is the default in `build_wave_atlas.py`.

**🔑 THE NIGHT'S HEADLINE — MAIN IS OPEN (2026-08-15).** main (79,510 weighted ins, was 0.5%) was NOT blocked by a linker defect; that was my misdiagnosis off an uncontrolled measurement. It needs a **CLEAN REBUILD** to gate (`make clean && make extract BINARY=main && make build BINARY=main`), because main's extract runs the EXE-only `psyq_integrate`/`ld_interleave` steps that rewrite the `.ld` — exactly the trap **R22's own rationale** describes. **4 main functions are banked** (byte-identical, full clean build), drafted by the ordinary mass lane. **NEXT SESSION'S HIGHEST-VALUE TASK: give the main gate path a clean-rebuild mode** (one clean build verifies a whole BATCH — that is how 4 banked at once), then run main waves as ordinary campaign fuel. main has ~1,030 open stubs.

**📐 THE ONE METHODOLOGICAL LESSON OF THE NIGHT (worth more than the function count).** Every serious stall traced to *an instrument I trusted without controlling*, never to gcc:
- "main is link-blocked" → **refuted by a null-draft control** (the defect reproduced with ZERO drafts substituted). I had already written a 3-hypothesis linker theory on top of it.
- `corpus.stubs()` read as names when it returns **addr→Stub** → nearly reported both card pools exhausted.
- 3 good drafts withheld on an **advisory** symfix flag → all 3 banked unchanged when gated.
- `gate_lane` reporting an unhandled crash as **"0 banked / 0 near / 0 failed"** → indistinguishable from an honest empty result; cost 2 cycles.
- `gate_main.typesig()` **too strict** (parameter names) then **too coarse** (dropped `[]`) → discarded good work, then passed a real conflict that R22 caught.
**The rule that would have prevented all five: before believing a measurement, run the control that would make it fail.** A null input, a known-answer population, or an independent oracle. R35 says fix the instrument first; the sharper form is *confirm the instrument can even answer, and that it answers correctly on a case whose answer you already know.*

**⚠️ TOOLING DEBT FOUND TONIGHT (fix before the next long run):**
1. **`gate_lane` swallows `gate_stage`'s stderr** — it reported `banked 0, near 0, failed 0` twice while `gate_stage` was actually raising `corpus.CorpusError`. An unreported crash is indistinguishable from an honest empty result. It must surface stderr and distinguish CRASH from NOTHING-BANKED. (Running `gate_stage` directly gave the precise cause instantly.)
2. **`aprop_symfix` false-positives on LOCAL identifiers** (typedefs, inline-asm macro names) and its draft-symbol extraction misses some `extern` forms → it reported `STALE`/`AMBIGUOUS` for 3 drafts that were already correct. **Symfix is ADVISORY; the gate is the arbiter** — never withhold a standalone-MATCH draft on a flag alone.
3. **Never `make clean` mid-campaign** without immediately re-running `make extract-all` — it wipes every binary's `asm/` and every downstream tool then fails in confusing ways (cost 2 gate cycles tonight).

**📊 OVERNIGHT RESULT (2026-08-15, waves C–M).** ~408 banked · stubs 12,059 → **11,589** · fleet **95.4% instr** · **213/213 byte-identical after every batch** · **main 0 → 175 matched** (913 stubs left). Wave draft rates 91–100% across ten waves, mostly **haiku**, writing byte-exact C from raw MIPS with no reference body. Four perfect sweeps (36/36, 44/44, 44/44, 44/44).

**🔧 THE MAIN LANE — HOW TO RUN IT (this is the night's unlock).** main was 0.5% and written up as the hardest remaining mass; it was never hard, it was never *gated correctly*. Use **`tools/gate_main.py <slate.json> --apply`**: substitute the batch → `make extract BINARY=main` → `make build` → SHA. ONE clean rebuild verifies the WHOLE batch (42–43 banked per rebuild). It reports in-TU declaration conflicts and, on a compile error, names the culprit instead of bisecting. **Do NOT gate main through `gate_lane`/`gate_stage`** — they build incrementally and main's extract rewrites the `.ld`, producing a false diff (R22's own rationale).
- **Known next improvement (mechanical, recurring):** `gate_main` should strip DUPLICATE TYPEDEFS on substitution the way `harvest_verify` already does. `src/800.c` now carries local typedefs (e.g. `SVECTOR`) from previously banked functions, so any later draft defining its own collides and costs a draft per wave.
- The 5+3+2 conflict-dropped main drafts across waves J/K/L are **verified-correct and recoverable** with cast-at-use (adopt the other declaration verbatim, adapt at the use site).

**RESUME STEPS:**
1. `pgrep -f tools/gate_lane` — never run two gates, and never run `build_wave*.py` during one (R35 guard: `corpus.stubs()` misreports substituted drafts).
2. Gate the late-repaired wave-D drafts: `.run/wave_p31d_late_slate.json` (5 verified MATCH, rescued by the repair stage after the main slate was built).
3. R22 (`make clean && make extract-all && make check-all` → 213/213), then commit (task + this log together).
4. Next wave: `.venv/bin/python tools/build_wave_atlas.py .run/wave_p31f_cards.json 96 --max-bins 8` → convert to args (`{wavedir,cards_file,cards}`) → Workflow `scratchpad/p31_wave.js`. Lanes: `mass` (atlas), `adapt`/`weak` (`tools/build_wave.py <pool>`; adapt 569 + weak 890 candidates remain, both verified live after the predicate fix).
5. Grinder queue has 3 fresh high-value seeds incl. **`func_80183578` close=1 DELAY-SLOT** (§60a precedent: a close=1 delay-slot banked in ~6 min) and `func_8017DAEC` count-exact 113=113.

**Watch-fors (all bit tonight):** agent self-reports run OPTIMISTIC — always re-verify with `match_one` yourself, then the gate (wave C claimed 35/35→32 banked; main probe claimed 6/6→I measured 4/6→0 banked). An agent once wrote its body straight into `src/boot.c` (reverted; prompt hardened) — a dirty tree ABORTS the shared gate. `pgrep -f` self-matches its own shell wrapper (invoke without `shell=True`). `corpus.stubs()` is **addr→Stub**, not names.

## (superseded) checkpoint — 2026-08-14 pre-overnight

**Phase 31 CONTINUES (campaign-to-ceiling; do NOT close).** Session totals: **65 banked** (17 mechanical @$0 + wave A 12+1prop @~117k tok/bank + wave B **35/37 gated, 95% conversion** @~88k tok/bank — the decl-matching lesson nearly eliminated integration failures). Stubs ≈ **11,995** (from 12,059). All banks byte-gated + committed; wave banks propagated where sharers existed.

**RESUME STEPS (fresh session, after the standard load order):**
1. `git log --oneline -20` to see the wave-B bank commits; run **R22** (`make clean && make extract-all && make check-all` → expect 213/213) — it was NOT run after wave B (context ran out; the per-bank gates each verified their own binary, but the standing clean-fleet proof is owed FIRST).
2. `make atlas` (regenerates maps + atlas post-banks, ~15 min, $0).
3. **Wave C is STAGED, not launched**: `.run/wave_p31c_cards.json` (14 §172b tell-cards [sonnet] + 24 weak-seed haiku cards — measures the two untested agent lanes). Launch via the persisted workflow script `workflows/scripts/p31-adapt-wave-a-wf_2fbef223-859.js` pattern (args = the cards; NOTE the tell/weak cards have different fields than adapt cards — adapt the prompt per lane or write a v2 script). Needs `/effort ultracode` (R27).
4. Adapt pile remains ~630 SMALL-EDIT cards — the proven 73-95% lane; wave D+ = next 48 by the same selection (exclude banked; see `.run/wave_p31{a,b}_cards.json` for taken).
5. Grinder queue armed: 59 warmstart + 6 wave-A NEARs + 8 wave-B NEARs (4 at close ≤3). Relaunch: `GATE_PHASE=phase-31 .venv/bin/python tools/grinder.py --once --batch 15 …` (single-writer: never while a gate runs).
6. Ledger discipline: velocity row per wave (the table above); distill lessons per R16/R30; close the phase ONLY on measured multi-session yield decay (plan file §Leg-C).

**Watch-fors:** gate_lane aborts on dirty src/config (clean first); symfix-first before every gate (§173); the safety-classifier can rate-limit under 48-agent bursts (harmless — retry).

## (superseded) previous checkpoint (end of build arc)
**T0–T9 ALL COMPLETE AND COMMITTED** (through `commit:2181`). Phase totals: **17 banked, 0 agent tokens**; stubs 12,059 → 12,042; R22 213/213 verified twice (post-T1, post-T6). The machine: the Atlas (5,139 groups, `make atlas`), the widened lanes (symfix STALE-DELTA, recover_integration isolation + macro-externs/tu-scope, family_align + len_tells + lenmiss routing), the armed queues (grinder: 59 warmstart records; cards: 954 weak + 192 len + 704 adapt; permuter-49). NEXT = **T10+ the campaign loop**: L3 grinder running in background (launched at checkpoint time); **card/crack WAVES need Drew's `/effort ultracode` toggle first (R27)** — prompt and WAIT. Campaign cadence + close criterion: the plan file §Leg-C. If resuming fresh: read the approved plan + this log; check `.run/auto/grinder_heartbeat.json`; run `make atlas` to refresh; continue the loop.

---

## 🛑 SESSION CHECKPOINT — S61 INTERIM (2026-08-26 00:5x). Phase 31 T10+ CONTINUES. Lanes: gater + maintenance + resolver_lane UP (drafter deliberately DOWN).

**The session so far, in one paragraph.** Read `frontier-analysis-s60.md` and executed its sequence:
built the INTEGRATION-RESOLVER (tools/integration_resolver.py + lanes/resolver_lane.sh) — first pass
1,352 nominated → 424 judged in 41 s → 245 staged (57.8%) → **63 banked, zero tokens, ~10 min**
(commit:2991; subject says 72 = gross incl. 9 carve moves). Probing why 182 doubly-verified drafts
still refused exposed the night's real story: **15 of 214 binaries were baseline-RED at HEAD**
(stale JTBL_PADS / missing interleave entries / half-committed carves from S60's evening), refusing
174 of those 182 regardless of draft quality; the fleet R22 sweep had been guard-skipped since
12:54. Repairs so far (each byte-proven, committed): ov_SC01_006 (pad spec 0,0→0), ov_MAIN_012 +
ov_SC02_037 (missing jr_8016AB6C.o interleave entry; +0x20, 1,671/2,176 misplaced symbols). A
background batch (`.run/resolver/probe/repair3.sh`) is running jtbl_pads_fix over 9 more +
insertions-only interleave regeneration for 3. Casualties fixed en route: jtbl_pads_fix was broken
three ways (stale OBJ_ERR bracket regex; only one drift phrasing; write_pads' colon-split poisoning
the registry into a make parse error that failed EVERY build for ~9 min and was adopted by a blanket
commit — R52 #2); mk_write now REFUSES parse-poisoned lines; gate_stage now refuses red-listed
binaries' drafts as BASELINE-RED pre-build (negative-controlled both ways).

**Measurement/tooling shipped:** campaign_status derives banked-today from the INCLUDE_ASM
invariant (+ anchored pgrep alive()); gater ledger carries gate_min beside wall_min; maintenance
fleet sweep is draw.lock-aware (it actually runs now); rtu_shadow.py (prospective ledgers for
fa–fd EXIST at .run/rtu_shadow/<w>.jsonl; join handles 0-bank waves + excludes REDs);
build_wave_atlas holds resolver-owned (binary,fn) from draws; resolver ledger re-opened 146
refusals on RED binaries as BASELINE-RED (auto re-judged next pass). Cookbook §293 (the sibling
law decomposed — the load-bearing part is THE BASELINE, NOT THE SIBLINGS), two decision-log
entries, accelerators #12.

**In flight right now:** gater re-gating fb honestly (third attempt — attempts 1–2 were voided by
a NameError guard then the poisoned registry), queue fc/fd/fe/ff behind it; repair3 batch;
a Fable agent building tools/decl_from_use.py (negative-control-first; its scratch may appear as
src/*/.cdecl_*.c dotfiles — untracked noise, sweep after it reports). Resolver lane wakes every
45 min and will re-judge the re-opened items against repaired binaries.

**Next after the notifications:** (1) repair3 results → update .run/baseline_red.txt → commit →
trigger a resolver pass early; (2) fb..ff gates → `tools/rtu_shadow.py --join fb --join fc ...` →
the INVERSION decision (§3: false-negative <~2% flips the gate to rtu-first); (3) decl_from_use
slate → resolver intake; (4) then S61-5 re-aim (gen0/main/3–8 band) + the 8k-vs-16k A/B on the
first relaunched wave; (5) escalation tier only after the resolver stock drains.

**Hazards for whoever resumes:** kill lane PYTHONS by PID and verify with `ps -o lstart` (pgrep -f
self-matches your own wrapper — it killed two restart helpers AND the gater tonight); never let a
script's own text contain the pattern it pkills; the gater blanket-commits src/ config/ at gate
entry — probes that splice into src/ must hold the per-binary lock AND finish before gate entry, or
ride into a chore commit (the ov_MAIN_012 repair did — commit commit:2998 — harmless but
mis-attributed). Stop sentinels are CLEAR; `.run/baseline_red.txt` is live gate input — keep it
current as repairs land.

**Rule candidates added tonight (P10):** R56 — A GATE VERDICT IS A MEASUREMENT OF THE DRAFT ONLY
WHILE THE BINARY'S BASELINE IS GREEN; check the baseline before billing the subject (extends
R35/R40 to the subject's environment; enforcement shipped as the BASELINE-RED skip + the fleet
audit). R57 — AN INSTRUMENT'S OWN WRITE PATH IS PART OF THE INSTRUMENT: a repair tool whose writer
corrupts what it measures voids its own search and reports the corruption as the subject's failure
(write_pads; extends R40/R43). R58 — A SESSION-CLOSE "CLEAN" MUST QUOTE THE FLEET'S GREEN COUNT:
tree-clean and fleet-green are different invariants (S60 closed "clean" with 15 binaries red).

## 🛑 SESSION CHECKPOINT — S61 FINAL (2026-08-26 01:10). Phase 31 T10+ CONTINUES. Lanes UP: gater (idle, empty queue) · maintenance · resolver_lane. Drafter DELIBERATELY DOWN pending the S61-5 re-aim. Stop sentinels CLEAR. Tree clean; registry 5,085 lines; red list 4.

**Bottom line.** The frontier analysis was right and is now measured: the wide-wave machine on this
population is FINISHED — the five pre-paid waves plus fa, honestly gated against a repaired fleet,
banked fa 0/211 · fc 9 · fd 5 · fe 2 · ff 1 · fb 0 ≈ **17 banks from ~5,000 pre-paid drafts** —
while the zero-token lanes produced the night's real yield: resolver 63, maintenance 24 (+11
fix_tu_ret earlier), and the fleet repairs that un-blocked everything else. Fleet: 3,896 → 3,854
committed stubs since midnight-of-25th's close (net, INCLUDE_ASM invariant).

**The inversion question (S61-3) is CLOSED: NO.** fb — the one wave with a PROSPECTIVE rtu shadow
(taken 23:50) gated on the stable fleet — shows P(bank | rtu-MATCH) = 0/92; fc (partial confound)
11/58 = 19%; fd is void for this purpose (its "refusals" cluster 21/22, 9/10 in binaries that were
skip-listed mid-gate and repaired mid-flight — the join used today's red list, not gate-time's).
The falsifier fired exactly as §3 designed: rtu-MATCH does not predict whole-binary banking on this
population; the residual for byte-correct-at-the-TU drafts lives at LINK/LAYOUT level. The gate
architecture stays; the shadow ledgers (.run/rtu_shadow/) remain for any future re-test.

**What the 0-yield re-judge taught (176 re-staged, 0 banked).** The remaining stock's refusals are
now NAMED per class, none mysterious: (a) CARVE-REFUSED — the md_ island-pads shape jtbl_carve
declines ("is 'island-pads', not 'island-end'"); (b) assembler DUPLICATE SYMBOLS — the draft
DEFINES data a still-stubbed sibling's .s also emits (live-probed: md_MAIN_003/func_800D3204,
"symbol 'D_800D3200' is already defined") — wants a deterministic data-def→extern demotion;
(c) TU decl conflicts (the ov_SC04_018 broken-TU family). Each is a small tool, not a wall.

**The four still-RED binaries and their named mysteries:** ov_SC03_015 (emits MORE tables than the
2-entry spec; +1/+2 candidate search found no byte-identical winner — needs the real carve for a
newly-banked switch), ov_SC03_024 (+4 rodata shift in jr_8017AE2C.o; value search found no unique
winner), ov_SC04_018 (pads drift 'consumed 3 but 4' AND a TU whose rtu-view diverges from the real
pipeline — likely per-TU flags; two src attempts reverted), ov_SC06_022 ('consumed 1 but 2',
byte-proof refused). All four are skip-listed so no draft is billed for them.

**Record corrections (honesty over tidiness; do NOT rebuild history):** commit commit:3004
("ox wave fc banks recovered") actually captured 10 of fd's MID-GATE splices — 6 were later
reverted by their own judgments (verified; HEAD correct throughout). Commit commit:3006's message
describes a repair; its content actually REVERTS commit:3005 (the TU stands at its pre-S61 state).
Commit commit:2998 (gater chore) carries the ov_MAIN_012 interleave repair. Lesson for the rulebook:
NEVER blanket-commit another lane's mid-gate tree — R42's "commit, don't revert" is for trees AT
REST.

**Next session (in order):** (1) wire `decl_from_use.infer()` into aprop_autodraft:522 and the
resolver's `undeclared` classification behind `tu_compiles()` (the 39-cases-were-one-TU lesson);
(2) the data-def→extern demotion transform for the duplicate-symbol class, then one more resolver
pass; (3) S61-5 re-aim per the frontier doc §5.6 with tonight's measured wave ceiling (gen0
pockets · MAIN (313 crackable, its own lane) · the 3–8 band via the grinder) and relaunch the
drafter WITH the S61-6 8k-vs-16k A/B split on the first wave; (4) the md_ island-pads carve
extension (jtbl_carve); (5) S61-7 escalation tier only after (1)–(2) drain. Rule candidates
R56–R58 (interim block above) stand for the PhaseEnd P10 table; add R59 candidate: A BLANKET
COMMIT OF ANOTHER LANE'S MID-GATE TREE IS A RACE, NOT A BACKUP.

**How to resume:** campaign_status → `git status --porcelain -- src/ config/` (dirty ⇒ commit,
never revert) → `wc -l config/overlays.mk` ≈ 5,085 → `cat .run/baseline_red.txt` (4) → lanes via
`ps -o lstart` with patterns assembled at runtime (pgrep -f self-matches its own wrapper — it
killed three helpers tonight). The gater idles on an empty ready queue; feed it by re-queueing
`.run/ready/<tag>.json` markers or relaunching the drafter (S61-5 first).

### S61-6 VERDICT (2026-08-26 03:2x) — MAXTOK ABCD, paired, byte-judged
Same 10 gen0 functions (22–55 ins), four budgets, identical warm-start inputs verified per arm
(10 ghidra_c seeds + 6 old backlog drafts, same files every arm; an earlier arm-to-arm
contamination — big arms resuming from the small arms' fresh drafts — was caught in the shard
logs, killed, quarantined, and relaunched cold). Judge: splice → build → whole-binary SHA →
snapshot-restore per draft under per-binary locks. **BANKABLE: 8k 10/10 · 16k 10/10 · 24k 8/10 ·
32k 8/10** (big arms: two budget-never-converged NO-DRAFTs plus the 55-ins fn BYTE-DIFF in both).
Truncated turns 6/1/0/0 — truncation recovers across the turn loop and does not cost banks (the
S60 inverse-correlation, now paired-confirmed). **Decision: overlay drafting at MAXTOK=8000**
(fastest turns, most shots/hour); the main lane keeps its own tuned 16000 (also a 10/10 arm).
Caveat (R41): n=10 at 22–55 ins; the gen0 tail (p90 246 ins) is extrapolation. The 10 winners
were staged and banked for real (commit:3023; 6 first-pass, remainder accounted in the ledger).
Gen0 sweep launched at 8000/700: 196 sweepable non-main fns in waves g0a–g0d (size-ascending,
<=60 agents), each wave queued to the gater as its drafts land; main's 231 gen0 run through the
main lane. Rule-candidate data point for the effort doctrine: MORE OUTPUT BUDGET IS NOT MORE
QUALITY on this model/population — budget bought nothing the turn loop didn't already provide.

### CORRECTION to the S61-6 verdict (03:4x) — the judge had an R53 false-green hole; corrected table flips the winner to 16k by one function
The paired judge checked the built binary's SHA without checking the BUILD'S EXIT CODE: a draft
that failed to compile left the previous (green) binary in place and scored BANKABLE — R53's third
strike this campaign, caught because the production gate refused exactly the four "winners" whose
rtu verdict was CC1 (correlation 4/4; every genuinely banked winner was rtu MATCH; fleet_red.txt
also turned out stale-S60 and was skip-listing repaired binaries — reconciled). CORRECTED TABLE
(true raw banks / 10): **8k 6 · 16k 7 · 24k 5 · 32k 3.** The ordering conclusion stands — bigger
budgets are WORSE — but 16k edges 8k by ONE function (8017DBA0: 16k's draft rtu-MATCHed, 8k's
CC1'd). At n=10 that is noise-range; the gen0 sweep ALREADY RUNS at 8000 and is NOT being churned
for a one-function margin (coverage before the window closes outranks a marginal budget delta;
misses get 16k re-shots via the feedback-armed redraft pass). The four false-green functions'
drafts fail the real TU (engine_core.h DEFINE conflicts) and return to the pool as gen1 with gate
feedback. Judge lesson for the PhaseEnd: R53 candidate is now byte-proven three times — VERIFY A
BUILD FROM ITS EXIT CODE, NOT ITS OUTPUT FILE.

### THE OX WINDOW CLOSED — 2026-08-26 07:55 (probed: HTTP 404 on stealth/ox-alpha; stealth/* gone from the model list)
The free-drafting era ended mid-m0b (its 29 agents all 404'd at turn 0 — a harness-epoch event, not
29 model failures, R40). THE GOAL BEAT THE DOOR: overlays 196/196 gen0 drafted (waves g0a–g0e, 60
banked at the gate so far + 6 ABCD), main 196/225 drafted and PARKED for the main lane's clean gate
(the 29 stragglers were attempted twice, no submission — final). Still converting, all pre-paid or
zero-token: wave g0f (103 feedback-armed redrafts) mid-gate; the 196-draft parked slate (40/pass);
resolver/grinder/maintenance/pads-repair lanes. Drafting anything NEW now requires a PAID model —
S61-7's escalation question is now the only drafting question left, and it is Drew's call.

## 🛑 OVERNIGHT CLOSE — S61 (2026-08-26 09:1x). Drew slept 02:00–morning; the session ran autonomously on 30-min ticks.

**The night, in numbers (INCLUDE_ASM invariant, denominators attached).** Since midnight:
**378+ net stubs removed** (3,896 → 3,518 committed, 60 commits). The gen0 campaign Drew ordered
("all gen0 touched before the ox era ends") BEAT THE CLOSING DOOR: overlays **196/196 drafted,
77 banked**; main **196/225 drafted (29 no-draft after two attempts), 119 banked** — 196 gen0
banks total. The ABCD MAXTOK test ran as a paired four-arm byte-judged experiment (corrected
verdict after its own R53 false-green was caught: 8k 6 · 16k 7 · 24k 5 · 32k 3 of 10 — bigger
budgets are worse; the one-fn 8k/16k gap is noise). The feedback-armed redraft wave (g0f) banked
10 more of the previously-refused. **The ox window closed at 07:55** (stealth/ox-alpha 404,
delisted) — m0b's 29 retries lost the race by a minute. Fleet now: instr-weighted = 98.2% ·
distinct-code = 96.4% (regenerated this morning).

**What runs on, all zero-token:** gater (idle unless fed), maintenance (fleet sweep + A-prop +
pads auto-repair), resolver lane (converging ledger stock), grinder (permuter band), main lane
(its parked-gate half is alive; its DRAFT half 404s harmlessly each pass — quiet it or feed it
paid models, Drew's call). Red list steady at 4 named mysteries (ov_SC03_015, ov_SC03_024,
ov_SC04_018, ov_SC06_022).

**The one drafting question left is S61-7's: paid models or not.** Everything free is either
consumed or self-running. Candidates for a paid escalation pack: the residual true-DIFF wall,
the 106 undrafted-or-unbanked main gen0, the g0f leftovers — all carry per-fn gate feedback now.

**Overnight incident log (all diagnosed to the byte, all corrected in-line):** the ABCD warm-start
cross-contamination (caught in shard logs; big arms relaunched cold behind a quarantine); the
judge's R53 false-green (caught by the production gate's disagreement — R34 working as designed);
the stale fleet_red.txt skip-listing repaired binaries (reconciled); one hung agent killed by the
silence rule; an R12 slip (a log aimed at scratch instead of .run/) — caught and rerun.

**CORRECTION to the overnight close (R40):** the "fleet regenerated" line above quoted the STALE
file — bare `progress.py` reports one binary; the fleet aggregation needs `--fleet` (its rc=0 with
no rewrite was the tell, caught by the unchanged numerator + mtime). The TRUE morning numbers:
**instr-weighted 98.4% (13,304,903 / 13,523,865) · distinct-code 96.6% (89,005 / 90,929) ·
2,540 INCLUDE_ASM stubs remaining** — up from 98.2% / 96.4% at the S60 close.
