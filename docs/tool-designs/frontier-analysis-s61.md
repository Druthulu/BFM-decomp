# Frontier analysis — S61 (2026-08-26, midday; post-ox)

**What this is.** A read-only analysis of everything that remains between HEAD `commit:3070` and
100%, written for a session that has NO memory of today, as the ground truth for a
Phase-32-shaped FINISH PLAN. Every number carries its denominator and source; Appendix A lists
the exact commands. Nothing in the tree was modified except `make atlas` and
`tools/progress.py --fleet` (both regenerate their own outputs) and scratch under
`.run/frontier_s61/`. All campaign lanes were verified STOPPED (empty `ps`) — these numbers
raced nothing. **Owner directive folded in (Drew, 2026-08-26): the finish is
budget-unconstrained ("no limit — get to 100%"); Ultracode/Claude-subagent waves are
re-authorized on the subagent model ladder (Haiku ≤~50 ins → Sonnet ~50–120 → Opus ≥120); the
paid-model menu is open (DeepSeek continues, anything cheaper-than-Opus-but-capable approved);
and the plan must be EXHAUSTIVE — every crackable function in exactly one class with an engine
and a falsifier.**

**The one-paragraph conclusion.** The remainder is 2,520 open instances (2,517 INCLUDE_ASM
stubs + 3 NON_MATCHING) carrying 191,556 sig-true instructions — 1.6% of the fleet's
instruction mass — and for the first time the whole of it decomposes into named classes with
no unassigned residue: 1,002 instances (73,920 ins) sit behind DETERMINISTIC work (five
red-binary surgeries, two small resolver transforms, carve/-O0 extensions, the A-prop free
lane), while 1,518 instances (117,636 ins) are DRAFTING-shaped — and 61% of those (920 of
1,518) have never been personally attempted by any engine, 652 of them are ≤50 instructions,
and every one now carries warm-start fuel (seeds, prior drafts, or gate feedback) that the
pre-ox Ultracode era never had. The free-model era is over (ox 404s since 07:55) but its
replacement is measured, not hypothetical: DeepSeek v4-flash banked main gen0 at ~$0.25/bank
so far ($3.04 for 12 banks with 74 pre-paid drafts still in the queue), the ox-era conversion
on identical warm-start populations was 39–61%, and the zero-token lanes (resolver 63,
maintenance 35, A-prop 357-in-32-min) keep producing wherever their named blockers are
removed. The plan is therefore: unblock the deterministic mass first (surgeries + two
transforms, ~1 day, zero tokens), run ONE paired model-ladder calibration probe (Haiku/Sonnet/
Opus/DeepSeek on a stratified 20-fn sample), then commit the re-authorized Ultracode ladder to
the never-attempted bulk while the wall track (86 true-DIFF fns) climbs its escalation chain.
This is a path to 100%, not another stall, precisely because every class has an engine that
has already banked its kind — the only genuinely unproven territory is the deep wall tail
(~86 + 5 behemoth-class fns), and it is fenced, named, and last.

---

## 0. Trust ledger — verified against the tree vs taken from records

**Verified against the tree by me today (commands in Appendix A):** the fleet digests
(regenerated: 98.4% instr / 96.7% distinct / 99.31% fn-count / 2,517 stubs); the atlas
(regenerated at HEAD `commit:3070`: 2,520 open / 1,931 skeletons / 1,596 groups / 191,556 ins);
the full stub-counter reconciliation to the last line (3,495 = 2,517 + 959 + 3 + 3 + 13, §1);
the per-bucket `classify()` sums over all 213 binaries; the main weighted-metric divergence
(§1.3 — sig-row join over `corpus.stubs('main')`, both sig files); the exhaustive class
decomposition summing 2,520/2,520 (`.run/frontier_s61/megajoin.py` over the atlas + 4 ledger
families + 293 wave-card files); the red list (5) and per-red-binary open counts; DeepSeek
ds1/ds2 costs summed from per-shard agent logs ($1.9227 / $3.0413) and ds2 bank attribution by
per-commit INCLUDE_ASM diffs; the resolver's converged state (last pass 12:09: 302 items → 85
staged → 0 banked); the grinder's S61 yield (0; its 29-bank file is dated Jul 24); the
main-lane n-pass logs (drafts=0 — its ox half is dead); lane quiescence (`ps` empty);
`decl_from_use.py` exists (commit:3008) and no dup-def-demotion tool exists.

**Repo-recorded measurements I did not independently re-derive:** the S61 session narrative
(resolver 63 banked, maintenance 24+11, wave re-gates fa–ff 17/~5,000, gen0 77+119+10+6 banks,
the ABCD corrected table 8k 6 · 16k 7 · 24k 5 · 32k 3 of 10, the ox-window close at 07:55, the
$60.21 key cap) — all from `phase-ends/CURRENT_PHASE.md` S61 blocks, which were themselves
written against byte evidence; the ox-era wave conversions (dd 217/422 … m74 slate 119/196)
from S60/S61 checkpoints and `.run` ledgers; roadmap/contract text from
`docs/roadmap-to-100.md` (v2, 2026-07-30); token-per-fn model calibration from
`docs/calibration.md` + roadmap §2 (dated 07-24/07-30 — stale-risk flagged where used).

**Taken on trust and NOT reproducible from artifacts:** the S60 A-prop residual split
("169 STRUCT / 121 no-seed-decl / 73 IMM") — I searched `.run/aprop_autodraft_*`,
`aprop_maint_slate`, `aprop_symcheck`: none carries per-member refusal classes; the mechanisms
exist in `aprop_autodraft.py` (:522 no-seed-decl, :592 STRUCT) but the counts must be
re-derived by the next A-prop pass before anything is sized on them. The aprop_cards cls
census I *can* verify is families-level: 424 PURE / 85 IMM / 25 MIXED of 534 (no STRUCT
family cards exist — the STRUCT class lives only in refusal paths).

**Instruments exonerated/convicted before use (R40):** the "MAIN game-code weighted 39.4%"
metric is CONVICTED as misleading for planning (§1.3) — mechanism identified, correct number
derived. The `campaign_status` banked-today regex undercount was already fixed in S61 (now
derives from the INCLUDE_ASM invariant). The atlas↔fleet cross-check PASSES exactly:
fleet-weighted open excluding main (13,444,355 − 13,275,028 = 169,327) equals the atlas
non-main open ins (191,556 − 22,229 = 169,327) to the instruction.

---

## 1. The honest denominator (Q1)

### 1.1 The two stub counters, reconciled exactly

`tools/progress.py --fleet` says **2,517 INCLUDE_ASM stubs**. `git grep -c 'INCLUDE_ASM(' HEAD
-- src/` summed says **3,495 lines**. The difference is **exactly 978**, and it is a
*constant*, fully decomposed by running `classify()` over all 213 binaries:

| bucket | count | what it is | work? |
|---|---:|---|---|
| live stubs | 2,517 | the open work; what the fleet counter counts | YES |
| LINKED PsyQ | 959 | INCLUDE_ASM lines in main TUs whose subsegs link real SDK objects, byte-identical (`LINKED_SEGS` in progress.py:475) | NO — done by linking (contract §1 scope decision) |
| NON_MATCHING | 3 | `CdReadStateMachine`, `CdReadSectorReadyCB`, `StreamLoadStateMachine` (all main; each has a C body under the guard AND an INCLUDE_ASM line, e.g. src/800.c:6260) | YES — G4 promotions |
| INCLUDE_ASM data blobs | 3 | `is_data_blob()`-classified (main `func_8005CE38`, `func_80047CAC` + 1) | data conversion, not matching |
| dead/#if-0 lines | 13 | skipped blocks (the resident func_800D00E4 pattern, progress.py:607) | NO |
| **total** | **3,495** | | |

Cross-check on the overnight record: the S61 close quoted "3,896 → 3,518" (git-grep counter)
while the correction quoted "2,540 remaining" (fleet counter) — 3,518 − 2,540 = 978. Same
constant. **The right "done" denominator is the fleet counter (2,517), because the extra 978
lines are 959 already-done-by-linking + 16 non-functions + 3 NM that the fleet counts
separately.** The S60 "961" figure = 959 LINKED + main's 2 INCLUDE_ASM blobs, exactly. Use the
git-grep sum only as a tripwire (it should always exceed the fleet counter by 978 until a
linked seg is decompiled or a blob converted; drift in the offset = a new classification bug).
Separately, 53 `INCLUDE_RODATA` lines are data blobs outside both counters (56 blob entries
total = 53 RODATA + 3 ASM).

### 1.2 The full open decomposition

At HEAD `commit:3070` (all three metrics regenerated today):

- **Fleet:** instr-weighted **98.4%** (13,306,357 / 13,523,865) · distinct-code **96.7%**
  (5,656,025 / 5,851,972; 89,008 / 90,929 unique fns) · fn-count **99.31%** (360,468 /
  362,988). Excluding main: 98.7% (13,275,028 / 13,444,355).
- **Open:** 2,517 stub instances + 3 NM = **2,520 instances / 191,556 sig-true ins** in 1,596
  atlas groups (1,931 distinct skeletons; **1,921 unique open fns** by the distinct-code
  metric — multiplicity is nearly gone: 2,520/1,921 ≈ 1.31, vs 1.6 at the P30 baseline and
  ~9 in the family era). Weighted open = 217,508 (fleet) — the 26k gap vs 191,556 is main's
  sig-provenance artifact (§1.3), not missing work.
- **Duplicate leverage residue:** 480→ now only a minority of groups are multi-instance;
  per-binary-instance duplicates account for 2,520 − 1,921 = **599 instances** that will bank
  by propagation behind 1,921 distinct cracks. The dedup registry already collapses 254,655
  of the fleet's 358,296 REAL fns (2,165 groups / 254,731 instances) — that machine is built
  and running; it is not part of the remaining problem.
- **Not work:** 959 LINKED PsyQ objs (byte-identical), 1,213 empties, 56 data blobs, 13 dead
  lines.

### 1.3 The main metric is wrong for planning — conviction and the correct number

`docs/progress.fleet.md` prints "MAIN game-code weighted 39.4% (31,329 / 79,510)". The join
proves this counts already-done work as open: `corpus.stubs('main')` returns **1,112**
addresses = 148 stubs + 959 LINKED + 3 NM + 2 blobs, and **1,111 of the Ghidra sig's 2,045
rows land on that set (48,181 ins)** — i.e. the metric's denominator includes the 959 LINKED
functions' instructions while its numerator can never contain them (the docstring's claim
that the sig "EXCLUDES the LINKED PsyQ objects" is false of the file as it exists; dated
2026-08-05). Against the splat-true `sig.main.jsonl` (2,000 rows / 83,956 ins), stub-set rows
carry 51,478 ins, of which the atlas says only **22,229 ins across 151 fns are genuinely
open** — the other ~29,249 ins are the LINKED objects, byte-identical since Phase 8. **The
honest main state: 151 open fns / 22,229 ins; main game-code-by-C ≈ 57% and main
by-byte-identity 92.2% (1,784 / 1,935 fn-count).** The roadmap's §1.3 second-oracle contract
item is also the fix for this metric — a fresh LINKED-aware main sig makes the weighted
number honest and foldable. Until then, do not quote 39.4% in any plan.

### 1.4 Three candidate definitions of "100% done" (recommendation: D1)

- **D1 — The contract 100% (roadmap §1, Drew's 2026-07-15 decisions; RECOMMENDED).** Zero
  INCLUDE_ASM and zero linked NON_MATCHING under src/ across all onboarded code-bearing
  binaries; byte-identical from a genuinely clean tree with AND without SDK objects; both
  audit oracles green including a real main second oracle; PsyQ LINKED = complete; the
  explicit exclusion ledger cited. **Today's exclusion ledger is down to 5 UNCLAIMED payloads
  of 220** (MAIN/7, MAIN/9, SC03/53, SC03/54, SC03/56 — `docs/disc-ledger.md:111`; the S45-era
  "34 parked" has shrunk by onboarding). Distance: 2,517 stubs + 3 NM + the 2-3 blob
  conversions + the oracle item + a decision (onboard-or-exclude-with-evidence) on the 5
  payloads. Fleet reading at D1-done: fn-count 100%, instr-weighted 100%, distinct-code 100%
  *of the onboarded denominator*.
- **D2 — Display 100%.** Instr-weighted 100.0% on decomp.dev semantics (today 98.4% of
  13,523,865). Reached strictly before D1 (it rounds up while stubs remain in small fns);
  it is a milestone marker, not a finish line — G4/P9 forbid declaring on it.
- **D3 — Full-source maximalism.** Decompile the 959 LINKED PsyQ objects too (the sotn
  precedent). Explicitly recorded as far-future stretch, NOT planned (roadmap §1 side note +
  §7). Under D3 the distinct denominator grows by the SDK's fn mass; nothing in this plan
  should be shaped by it.

G4 discipline note for D1: the 3 NON_MATCHING are already 0-in-default-build (G4 green); D1
requires them *promoted to matching*, which is main-lane work counted in class B below.

---

## 2. The exhaustive class decomposition (Q2)

Derived fresh: atlas at HEAD joined to `.run/backlog.jsonl` (2,615 rows) + 179
`.run/auto/bulk/*.backlog.jsonl` + `.run/reloc_rejects.jsonl` (14,071) +
`.run/resolver/verdicts.jsonl` (10,114) + 293 wave-card files + `.run/baseline_red.txt`,
priority-classified so **every open instance appears exactly once; classes sum 2,520/2,520
fns and 191,556/191,556 ins** (script + per-class member lists:
`.run/frontier_s61/megajoin.py`, `classes.json`, `class_members.json`).

| # | class | fns | ins | ≤50 / 51–120 / >120 | fix shape | engine (with escalation) | expectation (measured basis) |
|---|---|---:|---:|---|---|---|---|
| A | RED-HELD (5 binaries) | 241 | 11,417 | 174/50/17 | TOOL/surgery | 5 fresh-eyes surgeries, then classes re-open | binary-level: 6→5 reds already healed by pads auto-repair; each surgery is bounded (named defects, §2.A) |
| B | MAIN (incl. 3 NM) | 151 | 22,229 | 35/64/52 | DRAFTING + lane | main lane clean gate; ds2 refresh + Claude ladder; NM promotions | m74 parked slate banked 119/196 = 61%; ds2 12/86 so far with 74 drafts live |
| D | STRUCT (ledger-klassed) | 5 | 420 | 2/1/2 | DRAFTING | Opus serial (register-layout work) | §270-class; small |
| E | CARVE-TOOL (jtbl-carve lever) | 111 | 20,625 | 2/33/76 | TOOL then free | jtbl_carve island-pads extension; resident's 5 jtbl ride here | carve path measured 8/8 (calibration.md); island-pads shape is the named refusal |
| F | -O0 LANE | 15 | 2,513 | 2/9/4 | TOOL then free | o0_subsplit carves (incl. the ov_SC03_118/119 ten-fn island the ds1 agent mapped) | S60 x3 carve: 48/48 after byte-neutral split |
| G | A-PROP MECH (remap lever) | 555 | 29,456 | 379/133/43 | TOOL (free lane) | aprop_autodraft + symfix + decl_from_use (wire :522) | 357 banked in 32 min (S60); ~50–60%/pass on the reachable slice; residual split needs re-derivation (§0) |
| H | TRUE-DIFF WALL (close≥3 & ≥6 attempts) | 86 | 8,053 | 16/49/21 | DRAFTING (hard) | grinder → serial head-crack → stronger paid model → deep session | bake-off n=1: Opus/GLM-5.3/fueled-DeepSeek matched where ox plateaued; UNPROVEN at scale |
| I | NEAR-MISS (close 1–2) | 37 | 2,114 | 24/8/5 | CPU (free) | grinder (permuter) first; serial lane on stall | grinder S61 yield 0 — falsifier live (§3) |
| J | CLOSENESS-0 RESIDUE | 80 | 9,909 | 32/21/27 | TOOL (named) | resolver named-class transforms + bytes-diff autopsy | resolver re-stage converged 0/pass until dup-def/island tools land |
| K | NEVER-TOUCHED (0 draws, 0 attempts) | 920 | 46,843 | 652/204/64 | DRAFTING | Ultracode ladder waves (warm-start; 157 carry A-prop cards — run G first) | ox gen0 on same shape: 39–61%; ladder probe calibrates (§3.5) |
| L | LOW-TOUCH (draws+attempts ≤2) | 122 | 11,356 | 57/38/27 | DRAFTING | same wave pool as K, second draw | between K and H rates |
| M | DRAFT-REMAINDER (lever-routed) | 197 | 26,621 | 22/81/94 | DRAFTING | extend-tell 94/13,254 + swaprepeat 14/2,113 (tell-carded Sonnet+); UNKNOWN 46/7,553 (autopsy-first); cc1 1/770 (func_80144B9C — cc1_probe kit); head/seeded/len/redraft/etc. per lever | tells are §172b-measured idioms; UNKNOWN needs naming before drafting |
| | **TOTAL** | **2,520** | **191,556** | 1,397/691/432 | | | |

Aggregates: **deterministic-first mass (A+E+F+G+J) = 1,002 fns / 73,920 ins**; **drafting
mass (B+D+H+I+K+L+M) = 1,518 fns / 117,636 ins**, of which the never/low-touch bulk (K+L) =
1,042 fns / 58,199 ins with 709 fns ≤50 ins. (A instance's class is where it *starts*; red
members re-enter their natural class after surgery.)

**2.A The five red binaries** (all gates refuse their drafts pre-build; nothing is billed to
drafts — R56): ov_SC02_005 (50 fns / 3,261 ins; TWO stacked defects — an older
extract/ld_interleave inconsistency of unknown date + the 05:38 bank's +0xAE8 rodata shift;
five snapshot-protected surgical attempts spent; diagnosis in
`.run/resolver/probe/build_ov_SC02_005.log`) · ov_SC04_018 (94 / 3,375; pads 'consumed 3 but
4' AND an rtu-vs-real-pipeline TU divergence, likely per-TU flags) · ov_SC06_022 (33 / 1,707;
'consumed 1 but 2', byte-proof refused) · ov_SC03_024 (32 / 1,576; +4 rodata shift in
jr_8017AE2C.o, no unique winner yet) · ov_SC03_015 (32 / 1,498; emits MORE tables than the
2-entry spec — needs a real carve for a newly-banked switch). Beyond their own 241 fns, the
reds hold **40 of the resolver's 85 live staged drafts** (ov_SC04_018 18 · ov_SC06_022 11 ·
ov_SC03_015 7 · ov_SC03_024 4) — surgery is double-yield.

**2.B Main detail** (151 = 148 stubs + 3 NM): 74 are ds2-drafted-with-feedback awaiting
redraft/regate, 64 attempted-open (includes the 29 two-attempt no-drafts), 10 queued with
older drafts, 3 NM promotions. The main queue file is 94% stale (156 of 166 entries no longer
open) — the lane needs a queue rebuild before its next gate pass.

**2.J/2.C The resolver's converged stock, by named cause** (last pass 12:09:43: 302 tracked →
85 staged → **0 banked**; verdict census over open instances: SKIP-UNCHANGED 160 ·
GATE-REJECTED 85 · TU-DECL 23 · DIFF 23 · CC1 9 · SYM-MM 2): all 85 GATE-REJECTED notes read
"MATCH (N ins)" — byte-correct at the real TU, refused at link/layout. Sub-causes are
probe-identified (S61): (a) md_ island-pads CARVE-REFUSED; (b) assembler DUPLICATE SYMBOLS
(draft defines data a still-stubbed sibling's .s also emits — the deterministic
data-def→extern demotion, NOT YET BUILT); (c) TU decl conflicts (23 TU-DECL, scattered 1–2
per binary); (d) 40/85 red-held. `decl_from_use.py` is BUILT but UNWIRED
(aprop_autodraft:522 + the resolver's `undeclared` path).

**2.K honesty caveat:** "never-touched" is instance-level. 275 of the 920 sit in groups where
a sibling WAS tried; **645 fns / 33,146 ins are in fully-virgin groups** (297 cold /
154 seeded / 99 A-prop / 95 cousin-multi). The gen0 sweep's "196/196 overlays drafted" was
its own eligibility slice (sweepable = carded band), not this population — most of K was
never card-eligible under the old draw filters. That is the re-aim: make it eligible.

**Attempt/closeness censuses over all 2,520** (for calibrating "survivor bias"): recorded
gate-attempt rows — 0 for 1,937 fns · 1–2 for 156 · ≥6 for 402; best closeness — none for
2,008 · 0 for 245 · 1–2 for 42 · 3–8 for 53 · ≥9 for 172 (of the ≥9s, 167 have no klass —
mis-scoring suspected per the S59 lesson; only 74 also have ≥6 attempts and count toward H).

---

## 3. Post-ox drafting economics (Q3) — measured only

Cost ceased to be a gate (owner directive) but still routes engines. Basis prices: DeepSeek
v4-flash-0731 $0.06/M prompt · $0.12/M completion (OpenRouter). The OpenRouter key carries a
$60 LIFETIME cap, hit at $60.21 mid-ds2 (~$10.6 account credit stranded); resume = raise the
key limit or a new key, then `.run/resolver/probe/ds2_resume.sh`.

| engine | measured record (with denominators) | unit economics | population fit |
|---|---|---|---|
| **DeepSeek v4-flash** | ds1: $1.9227 / 60 agents / 59 drafts / **1 bank** (once-refused overlays — the hardest population). ds2: $3.0413 / 106 agents / 86 drafts / **12 banks so far**, 74 drafted-still-open (63 slated-and-refused-or-pending with gate feedback, 10 never slated) | $1.92/bank on wall-adjacent; **$0.25/bank so far on main gen0, falling as the 74 gate** (m74-slate analogue converted 61%) | cheap parallel arm for ≤50-ins fresh/warm populations; NOT the wall |
| **ox (gone)** | window closed 07:55 (404, delisted). Final gen0 record: overlays 77/196 + ABCD 6 + g0f 10/103; main parked slate 119/196 at the clean gate | $0 while it lasted | the conversion benchmarks above are the bar any paid ladder must meet |
| **Claude Ultracode waves (re-authorized)** | pre-ox record: resident 1.4%→71.7% in one session (harvest pattern); P30 "~256 members ≈ 20M tokens as waves" ≈ 78k tok/bank; cheap-tier A/B (2026-06-29): Haiku ≈ Opus on ≤50-ins at ~4.8× lower $/match; roadmap doctrine: Haiku ≤50 / GLM $0.03–0.08/fn / cheap-Opus 40–140k tok/fn / Opus 90+ tail / frontier ~230k tok/fn discovery-only | tokens/bank known; $ depends on current API prices — price at launch, not from memory | the K+L bulk (1,042 fns; 709 ≤50-ins) and M's tell classes; **today's edge over the pre-ox era: warm starts + per-fn gate feedback exist for everything** |
| **Claude serial idiom lane** | 5 head-cracks, 5/5 banked (S60 era): 65–138-ins exemplars unlocking group worth 2,785 ins total | ~1 crack/session-turn, subscription-cost | H-wall mid-tier and M head-crack levers; the proven "head-crack → family_remap" pattern |
| **LLM-free grinder** | S61 yield **0 banks**; stock exhausted ("no untried candidates"; skips 509–514 non-permuter: unclassified 182 · redraft 150 · already-tried 89 · structural 78 · integration 15); its 29-bank file is dated Jul 24 (prior era) | $0, CPU only | class I (37 fns) only; falsifier already half-fired — see plan step 6 |
| **Integration resolver (free)** | S61: 63 banked in ~10 min from first pass (1,352 nominated → 424 judged → 245 staged); now CONVERGED at 0/pass (85 staged re-refused) pending the named tools | $0 | class J + the 40 red-held after surgery; restart yield arrives with dup-def demotion + decl_from_use wiring |
| **Maintenance/A-prop (free)** | S60: 357 banks in one 32-min sweep; S61: 24 + 11 fix_tu_ret; currently self-throttled ("only 3–17 banked since last pass, need 50 — skipping") | $0 | class G (555 fns); the throttle rule needs loosening once wave inflow resumes |
| **Stronger paid tier (unpriced)** | one documented bake-off row (func_80181714, 121 ins): ox plateaued at closeness 4 over 20 oracle calls; Opus, GLM-5.3, and fueled DeepSeek each reached reloc-verified MATCH | UNKNOWN at scale — probe before committing (below) | class H after the free chain stalls |

**3.5 The calibration probe the plan requires (owner asked "can Sonnet crack everything —
maybe even Haiku?"):** one PAIRED wave, stratified 20 fns (10 from K ≤50 ins, 5 from K/L
51–120, 5 from M extend-tell), each fn drafted by all four arms — Haiku, Sonnet, Opus,
DeepSeek-v4-flash — at MAXTOK 8000 (the ABCD-winning budget class; 16k edged it by one fn at
n=10, noise), identical warm-start packs, judged by the production gate with **exit-code
checks** (the ABCD judge's R53 false-green is three-times-proven). Decision rule: route each
size band to the cheapest arm within ~5pp of the best arm's banks-per-draft. Falsifiers: all
arms <10% on the stratum → the population needs autopsy-first, not more drafting; Haiku ≥
Sonnet on ≤50 → Drew's belief confirmed, fleet goes cheap; arms disagree wildly by class →
split routing stands. Cost bound: 80 drafts ≈ one ox-era wave's gate time; token cost is
whatever the arms bill — accepted per directive.

---

## 4. The sequenced finish plan (Q4)

Ordered from tomorrow morning; each step names its falsifier. Steps 1–3 are zero-token and
independent of every model decision.

0. **Resume ritual** (5 min): `tools/campaign_status.py` → `git status --porcelain -- src/
   config/` (dirty ⇒ commit, never revert) → `wc -l config/overlays.mk` = 5,086 →
   `cat .run/baseline_red.txt` (5) → verify lanes via `ps -o lstart` with runtime-assembled
   patterns. Delete no sentinel without reading its owner.
1. **Ship the two resolver transforms, then one resolver pass** (~half day, $0): (a) the
   data-def→extern demotion (probe case: md_MAIN_003/func_800D3204, "symbol 'D_800D3200'
   already defined"); (b) wire `decl_from_use.infer()` into aprop_autodraft:522 and the
   resolver `undeclared` path behind `tu_compiles()`. Negative-control both (R39). Expected:
   10–30 of the 45 non-red staged (85−40) + fresh A-prop reach. Falsifier: <5 banks → the
   named-cause analysis was wrong; autopsy two refusals to bytes before building anything else.
2. **The five red-binary surgeries** (fresh-eyes day sessions, hardest first is WRONG — do
   SC03_015/SC03_024/SC06_022 first, they are single-defect; then SC04_018; SC02_005 last with
   its dossier): each ends in R22 green for that binary + `make extract` (the §61c lesson:
   incrementally-green hides extract rot — add a weekly per-binary extract sweep while any
   surgery is open). Unblocks 241 held fns + 40 staged banks. Falsifier per binary: a surgery
   that cannot produce byte-identity in a day goes back on the ledger with its new evidence —
   never force-banked (P9).
3. **Carve + -O0 extensions** (classes E+F = 126 fns / 23,138 ins, $0): extend jtbl_carve for
   the md_ island-pads shape (the "is 'island-pads', not 'island-end'" refusal); run
   o0_subsplit over the mapped islands (SC03_118/119 pair first — the ds1 agent's note names
   the exact range 0x80183178–0x80183830 and both twins). Probe 3 carves before sweeping
   (R37). Falsifier: byte-neutral-split proof fails → that island goes to the wall ledger.
4. **Run the model-ladder calibration probe (§3.5)** — one day, parallel with 1–3.
5. **Relaunch the drafter as Ultracode ladder waves over K+L+M** (~1,239 fns / 84,820 ins;
   the probe fixes the per-band model): warm-start packs + gate feedback on every card;
   sibling-inclusive draws (ONE_PER_GID=0); the A-prop-carded 157 of K go through lane G
   first (free) with the wave as their fallback. DeepSeek runs as the parallel cheap arm on
   the ≤50 band once the key is re-funded; main lane gets its queue rebuilt (2.B) and the
   74 ds2 feedback-armed redrafts. Cadence: gate per wave, R22 per banked batch,
   atlas regen + `family_remap` behind every crack (the 599-instance propagation residue
   banks itself here). Expected: at ox-gen0's measured 39–61% on warm fresh populations,
   K+L's 1,042 fns yield ~400–630 banks before decay; falsifier: first two waves <15%
   banks-per-draft with the probe-chosen models → stop, autopsy 10 refusals to bytes, re-aim
   (do NOT tune wave knobs — S58–S60 proved that lever moves single digits).
6. **The wall track, escalation in order** (classes H+I+D+M-UNKNOWN, continuous alongside 5):
   grinder on I (37 fns) for two more weeks MAX — its S61 yield is 0; falsifier: still 0 →
   grinder retires to pure warm-start feeder duty. Serial idiom lane (proven 5/5) takes
   H's mid-tier and M's head-crack levers at ~1/session. The stronger-paid-model probe
   (bake-off pattern: same fn, 3 models, full §31-context pack) runs on H's top 20 by
   group-worth; kill the tier if 10 attempts bank 0. M-UNKNOWN's 46 fns get the bytes-diff
   autopsy FIRST (the decision-log's "second instrument that says where") — never drafted
   blind. The behemoth list (SaveLoadRoutine 1,139 ins riding jtbl-carve; func_800226C0 670;
   the §172 frame-172 16-instance family; func_80144B9C 770 cc1-class) stays P32 fare unless
   a probe shows otherwise.
7. **Main to zero + the contract items**: NM promotions (3), the main second oracle
   (roadmap §1.3 — also fixes §1.3's metric), gsgap/libapi residue asserted empty, then
   resident's last 6 (5 ride the E-carve, 1 direct) → **the first 100% binary flag-plant,
   then main**.
8. **Scope closure**: decide the 5 UNCLAIMED payloads (onboard via the L3 emulator tour or
   exclude-with-evidence — the contract permits either; do it deliberately at a phase
   boundary, not implicitly).
9. **PhaseEnd discipline**: P31 closes when main+resident are at 100% (or main's residue is
   named-wall-only), the red list is empty, and every remaining stub sits in exactly one
   ledgered class — quote the fleet GREEN count (213/213) next to "tree clean" (R58). P32 =
   the wall endgame (H residue + behemoths) per roadmap v2; P33 = verification + flip. The
   PhaseEnd carries R56–R59 candidates + the R53 three-strike verdict for ratification.

**What should NOT be done:** no wave-parameter tuning before step 5's falsifier fires (band/
mix/size knobs moved single digits across S58–S60 while the real causes were harness/baseline
defects); no rtu-gate inversion revisit (S61-3 CLOSED: P(bank | rtu-MATCH) = 0/92 on fb — the
residual is at link/layout, rtu cannot see it); no chunked gating (1.35 builds/draft measured,
mis-attributes neighbours); no re-drafting of anything in J/resolver stock (drafting is
finished there — it wastes a gate slot per re-draft); no bulk header edits ever (G-rule); no
blanket-committing another lane's mid-gate tree (R59 candidate — the fc/fd mis-capture); no
global Ultracode for the deep/surgical tasks (it caps reasoning at xHigh — surgeries and wall
sessions run Max, solo); no trusting a build's output file over its exit code (R53, three
strikes); and no new $60-lifetime-capped keys — set the cap above the expected burn or
uncapped, since the cap masqueraded as a model failure for two hours.

**Where this plan's knowledge ends (honesty):** (1) K's conversion under paid models is
extrapolated from ox-era warm-start records — the §3.5 probe exists precisely because that
number is unmeasured; (2) the H wall's crackability by ANY current model is n=1 evidence
(func_80181714) — the escalation chain is designed so its failure is cheap and visible;
(3) ov_SC02_005's defect (a) has an unknown introduction date (nothing ran full extract for
weeks — the fix's shape is known, the archaeology is not); (4) the ≥9-closeness stratum
(172 fns) is suspected mis-scored (167 have no klass) and is deliberately NOT summed into H
until re-scored at intake; (5) the A-prop residual split (STRUCT/no-seed-decl/IMM) is
unverified from artifacts (§0) — the first post-wiring pass re-derives it; (6) whether Haiku
really "cracks everything now" is exactly what step 4 measures — plan commits to the probe,
not the belief.

---

## 5. Dead ends declared (so nobody re-walks them)

- **"Re-gate the pre-paid ox waves harder"** — done to exhaustion: fa 0/211 · fb 0 · fc 9 ·
  fd 5 · fe 2 · ff 1 ≈ 17 banks from ~5,000 pre-paid drafts on a REPAIRED fleet. The stock is
  spent; the residue is in J/H by construction.
- **The rtu-first gate inversion** — falsified prospectively (fb shadow: 0/92). Keep
  `.run/rtu_shadow/` for any future re-test; do not rebuild the idea from memory.
- **"The gen6+ wall is a codegen wall"** — 61% of it had closeness-0 drafts (S60); after the
  resolver drained what a green fleet allows, the TRUE codegen wall is H = 86 fns / 8,053
  ins, and the rest of the old "wall" was baselines (15 red binaries), integration classes,
  and mis-scoring.
- **"More output budget = more quality"** — ABCD paired, corrected: 8k 6 · 16k 7 · 24k 5 ·
  32k 3 of 10; bigger budgets are WORSE on this model class; truncation recovers across the
  turn loop. Overlay drafting stays at 8k; main at its tuned 16k; misses get 16k re-shots.
- **"The A-prop 0-bank means the lane is broken"** — S59 decomposed it into four separate
  causes; the lane then banked 357 in 32 minutes. The current 0s are the self-throttle
  ("need 50 banks since last pass"), not exhaustion.
- **The grinder as a yield engine** — 0 banks in S61 against 37-fn stock; its July record (29)
  was a different, richer population. Two more weeks or retirement to feeder duty.
- **The main queue as a work list** — 156 of its 166 entries are stale (already banked);
  rebuild it from the atlas main set before the next main gate pass, or the lane gates
  nothing while looking busy (the R32 silently-narrowed-scope class).

## Appendix A — how every number was derived (all read-only)

- Fleet: `.venv/bin/python tools/progress.py --fleet` → `docs/progress.fleet.md` (also the
  per-binary table used for red-binary open counts). Atlas: `make atlas` →
  `.run/atlas.json` + `docs/frontier-atlas.md` (HEAD `commit:3070`; scope/totals blocks).
- Counter reconciliation: `git grep -c 'INCLUDE_ASM(' HEAD -- src/ | awk -F: '{s+=$NF}
  END{print s}'` = 3,495; per-binary split with the n==2 path test (main = src/*.c
  top-level, 1,125); bucket sums via `.run/frontier_s61/recon2.py` (imports
  tools/progress.py, runs `set_binary()`+`classify()` over all `BINARIES`: stubs 2,517 ·
  linked 959 · nm 3 · blobs 56 [53 INCLUDE_RODATA + 3 INCLUDE_ASM] · real 103,643 · empty
  1,213); NM names + main buckets via `.run/frontier_s61/buckets.py`; the 978 constant =
  959+3+3+13; overnight cross-check 3,518−2,540=978 from CURRENT_PHASE.
- Main metric conviction: `.run/frontier_s61/mainsig.py` — `corpus.stubs('main')` = 1,112
  addrs; `.run/sig.SLUS_007.26.jsonl` (2,045 rows / 79,510 ins; stub-addr rows 1,111 /
  48,181 ins) vs `.run/sig.main.jsonl` (2,000 / 83,956; 1,110 / 51,478); mechanism read from
  `weighted_metrics()` (tools/progress.py:781); atlas main_open 151 / 22,229.
- Class decomposition: `.run/frontier_s61/megajoin.py` (priority classifier; outputs
  `classes.json` + `class_members.json`; TOTAL asserted 2,520/2,520) with refinements in
  `refine.py` (resolver sub-causes via note regex + per-binary clusters; K composition;
  E/J binary concentration; red per-binary ins; ds2 slate coverage; ≥9-closeness census;
  draft-shaped band aggregate) and `ksib.py` (virgin-group split 645/275).
- Ledgers: `.run/backlog.jsonl` 2,615 + 179 bulk files (25,280 rows at resolver intake) +
  `.run/reloc_rejects.jsonl` 14,071 + `.run/resolver/verdicts.jsonl` 10,114 +
  `last_summary.json` (run 20260826-120943) + `gate.log` (12:10 gate of 85 → 0).
- DeepSeek: cost lines `grep 'api_agent done. cost \$'` summed over
  `.run/wave_ds1/shard*.log` (60 agents, $1.9227) and `.run/wave_ds2/shard*.log` (106,
  $3.0413); drafted = distinct `shard*/func_*.c` (59 / 86); ds2 banks = INCLUDE_ASM removals
  per main-lane commit since 2026-08-25 22:00 intersected with the ds2 fn set (12; script
  `ds_econ.py`); slate coverage from `.run/main_slate_*.json` (75/86 ever slated).
- Lanes: `.run/grinder_lane.log` (idle censuses; 0 bank lines; `grinder_banked.txt` mtime
  Jul 24), `.run/maintenance.log` (throttle lines; pads repair 6→5 at 09:20),
  `.run/main_lane.log` + `main_lane_ledger.jsonl` (n-passes: drafts=0; parked-slate gates),
  `.run/main_queue_live.json` (166 entries; 156 stale). Serial lane:
  `git log --grep 'serial idiom lane —'` (5 commits, worths 138/337/1066/563/681).
- Records: `phase-ends/CURRENT_PHASE.md` (S60 FINAL block lines 60–235; S61 blocks
  1997–2206), `docs/decision-log.md` last three entries, `phase-ends/PhaseEnd_Phase30.md`,
  `docs/roadmap-to-100.md` v2, `docs/disc-ledger.md:111` (5 UNCLAIMED of 220),
  `docs/calibration.md`, `.run/baseline_red.txt` = `.run/fleet_red.txt` (5). Tools:
  `ls tools/decl_from_use.py` (exists; commit:3008); no dup-def-demotion tool matches
  `demot|dupsym|dup_def` in tools/.

---

## Addendum — 2026-08-26, after the S61 idiom distill landed (§294–§300)

*Append-only; the body above is unmodified. The distill (15 byte-verified additions from 99
candidates; 3+1 refuted) landed after this document was written. Two sections were checked
against the open pool; both were verified against the tree before any number below was moved.*

**§295 (kernel-trap stubs) — moves 4 fns from drafting to deterministic.** src/800c3.c still
carries 24 INCLUDE_ASM lines; 23 are in class B-MAIN (the 24th, func_8005CE38, is one of
main's 2 data blobs, outside matchable). By atlas nins, only **4 of the 23 are ≤6-ins
kernel-trap-template members — ResetEntryInt, HookEntryInt, read, SysEnqIntRP (4 ins each,
16 ins total)** — bankable by the §295 verbatim-asm template (pad-nop and addiu-spelling rules
included) as a deterministic sweep; fold into plan step 1's zero-token batch. The other **19
(1,660 ins, 21–223 ins each) are real libapi functions** — ordinary B-MAIN drafting work, NOT
template food; do not let the "~22 stubs" phrasing of `docs/psyq-worklist.md:72` route them to
the blob lane. Headline effect if all 4 bank: deterministic-first mass 1,002 → 1,006 fns
(73,920 → 73,936 ins); drafting mass 1,518 → 1,514 (117,636 → 117,620). Class-table totals
are otherwise unchanged.

**§296 (frame check outranks the lever) — quantified over the whole open pool: the
contamination is 11 fns / 913 ins, ALL in main; the overlay classes are clean.** A regex scan
of every open member's target `.s` for the §296 tell (`\bjr\s+\$?ra\b` absent ⇒
fragment-suspect) flags **11 of 2,520**: the 4 kernel traps above (they end `jr $t2` — §295
owns them), the 4 `SYS_OBJ_*` cousins of the cards §296 already banked (SYS_OBJ_1034 /
202C / 2264 / 2CDC), GsSortFastBg, func_8002B0B4, func_8005A870. **0 of the 2,369 non-main
open members fire the tell** — M-DRAFT-extend-tell's 94, K's 920, H's 86 are measured clean,
so §296 does NOT shrink the overlay drafting pool; the m0a fragment cards it describes are
already banked and were never in this document's open set. Caveats: this grep is one of
§296's several signals (a fallthrough-TAIL fragment that ends in `jr $ra` — the SYS_OBJ_1AF0
boundary case — is invisible to it, and §296 says that shape is legitimately C anyway); and
the 7 non-§295 suspects still need the per-fn frame read before routing (blob lane vs pinned
C). Plan amendments: step 5's draw filter gains the §296 frame check as card metadata
(seconds per card, prevents the +2..+7 phantom-teardown plateau class); step 7's main sweep
routes the 7 suspects through the frame read FIRST. Instrument note for re-derivers (R40):
the first scan false-flagged 2,520/2,520 because a literal `'jr $ra'` match never hits the
padded column format (`jr         $ra`) — use the regex
(`.run/frontier_s61/fragscan2.py`, suspects in `fragment_suspects.json`).

Nothing else in §294–§300 moves a number or step here: §297–§299 are drafting idioms (they
raise wave quality, priced in via the warm-start assumption), and the refuted §300-R2
("maspsx rejects hex in `__asm__`") corrects a rule this document never relied on.

## Addendum 2 — 2026-08-26 (S62), plan step 1 executed: the falsifier FIRED; premises corrected

*Append-only. Every number below was measured on the tree at `commit:3078` → `commit:3080`.*

**Premise corrections (R35/R40, checked before building anything).** (a) The dup-def→extern
demotion was NOT "not yet built": `integration_resolver.dup_def_demote()` landed at `commit:3012`
(01:14, an ancestor of this document's HEAD) and had already BANKED its own probe case
(md_MAIN_003/func_800D3204, ledger run 011436: `dupfix:backlog … BANKED`). (b) `decl_from_use` was
already wired into A-prop (`aprop_autodraft.py` :522 branch, same commit); only the resolver's CC1
`undeclared` path was unwired — now wired as `integration_resolver.declfix()` (stages only on rtu
MATCH + stageable reloc; refusal class appended to the CC1 note). Its population measured by
`decl_from_use --cases` over the 42 recorded cases: **TU-BROKEN 39/42** (all ov_SC04_018 — the
split TU fails cc1 with NO draft; T2d's defect), NOT-A-STUB 1, UNKNOWN-SYMBOL 1, STRUCT 1 →
**0 bankable today**; the wiring pays after the SC04_018 surgery. (c) The "resolver converged at
0/pass" reading of §2.J was partly an instrument artifact: the resolver writes its `=== gate ===`
header through a buffered handle, so each header lands AFTER the gate output it labels; the 12:10
gate had run (34 binaries, all 0/N).

**The fresh pass (13:40, `--fresh`, live gate):** 1,419 nominated → 302 judged → **98 staged → 0
banked**. Of the 58 non-red staged: **54 CARVE-REFUSED** (the md_ island-pads shape — T3's carver,
not a resolver transform), **2 DIFF**, **1 PLUMBING** (`D_800CEE3C` = an unlabeled string inside the
rodata island that `func_800CFDB4.s` carries at `D_800CEE30` — a symbol-split, deterministic,
queued with T3). Step 1's falsifier (<5 banks from the transforms) fired exactly as written → no
further resolver transforms were built.

**The 2 DIFF refusals, autopsied to bytes (`tools/diff_autopsy.sh`):** each differed from the good
binary by ONE byte, inside the function, at a `j` word — a wrong internal jump target that
rtu/match_one could not see because `R_MIPS_26 .text` (which the assembler DOES emit for an
in-section `j`) was masked. Both drafts had a genuine control-flow error (goto-to-recheck vs the
cross-jumped call; a shared post-join negation vs an else-arm `negu`); one-line fixes, gated
through `sweep_parallel`, **banked 2/2** (`commit:3080`). The comparer is fixed (`masked_diff` `jrel`;
`rtu_match` now shares `structured_diff`), positive-controlled (originals → DIFF 1, fixes → MATCH)
and negative-controlled over all 3,475 stubs (`tools/stub_invariant_audit.py`: 1,097 stubs / 4,043
internal `j` exercised, 0 new mismatches). Cookbook §301. **Consequence for this document:** every
"byte-correct at rtu / closeness 0" claim (§2.J's 85, class J, the 54 carve-refused) was blind to
`j` targets; re-judge under the new comparer before spending builds.

**§295 sweep:** ResetEntryInt, HookEntryInt, read, SysEnqIntRP → `gate_main` clean rebuild, main
SHA `143dbb89…` byte-identical, **banked 4/4** (`commit:3079`).

**Net T1: +6 banks (2,517 → 2,511 stubs; fleet 98.4% instr / 96.7% distinct), 1 instrument defect
closed, 2 tools promoted.** The deterministic-first mass is unchanged in shape: the resolver's
stock is now carver-gated (T3) and red-gated (T2); nothing in class J is a drafting problem.
