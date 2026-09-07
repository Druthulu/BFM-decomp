# PhaseEnd — Phase 31: The Frontier Atlas & Wide-Tolerance Campaign (main to 95%, the fleet to 100.0%, and the last 21)
**Date:** 2026-09-05 · **Project Version:** 1.30.0 · **Phase Status:** Complete (milestone confirmed by Drew, gate 2 — 2026-09-05) · **Generation:** Gen2 (22nd phase of the arc; Phase 14 public-flip deferred to Gen3+)

> Gen2 phase 22 (8→…→30→**31**). Fourth phase off `docs/roadmap-to-100.md` v2 (§3 P31). Ran **30 sessions (S51–S80,
> 2026-08-14 → 2026-09-05)** and **~1,660 commits** — the project's longest phase. The granular trail (every wave's
> velocity row, every 🛑 checkpoint, every instrument defect and its repair) is preserved on-demand at
> **`phase-ends/logs/Phase31.md`** (R19 — NOT auto-loaded; ~8,700 lines; consult only when researching a mechanism).
> **The next session's jumping-off document is `docs/frontier-p32.md`** (the last 21 functions by blocker, the five
> parked payloads, the routes, the proposed Phase-32 shape). Owner decisions (Drew): the re-charter (2026-08-14, gate
> 1, ratifying R37–R39); the wave doctrine (6,000+ ins per wave, 2026-08-15); the autonomous lane architecture with a
> 2-workflow budget; the S61 finish plan; the S78 completion-sprint census and task order; R40–R43 accepted (S58) and
> R61 (S77); close at the ledgered ceiling and open Phase 32 as a short, kill-gated phase for the remainder (S80).

## Build Log

**The phase in one line:** the fleet was driven from **95.3% to 100.0% instruction-weighted** (distinct-code 90.0% →
99.9%, fn-count 96.68% → 99.99%), open stubs **12,059 → 21** (4,554 instructions), **main from 1,041 open functions
to 12** (game-code 0.5% → 95.0%; byte-identical 99.43%), the resident 14 → 2, **213/213 binaries byte-identical at
every banked batch**, and every remaining stub on a named ledger with its mechanism — while roughly a third of the
phase's "compiler walls" turned out to be our own instruments and were repaired instead of matched.

**Files created/changed and complete — do not recreate** (category summaries; `phase-ends/logs/Phase31.md` and
`git log --since=2026-08-14` hold the per-commit list):

- **Source — ~12,000 stub instances replaced by byte-verified C** across main, the resident, the overlays and the
  `md_*` module fleet (`src/**`); `config/dedup.us.yaml` 2,061 → **2,220 groups / 0 failures**; main's SDK regions
  re-linked from real objects (`libgte23–30`, `libgs7–8`, `snd10–12`, `libgpu2`, `libapi1–2`, `libpad1–2`,
  `apicard5–7`; `config/splat.us.exe.yaml` + `Makefile`), 13 + 4 game-code TUs deleted as library tiles.
- **The frontier atlas (T4/T5):** `tools/atlas_features.py` (per-function feature layer, 363k rows) +
  `tools/atlas.py` / `make atlas` (multi-tier similarity groups, lever labels) → `docs/frontier-atlas.md`.
- **The campaign machinery (T10+):** `draw_waves.py` / `wave_args.py` / `claude_wave_packs.py` /
  `journal_notes.py` / `neighbor_ref.py` / `seed_ref.py` (card fuel), `build_wave*.py` / `gate_wave.py` /
  `parallel_gate.py` / `gate_main.py` / `gate_main_parallel.py` / `pregate_check.py` / `reloc_identity.py` /
  `bisect_slate.py` (the pre-gate protocol + gates), `ox_campaign.py` / `gater_lane.py` / `main_lane.py` /
  `campaign_status.py` / `lane_inflight.py` / `launch_check.py` / `work_evidence.py` (the autonomous lanes),
  `twin_rescan.py` / `twin_sweep.py` (the twin oracle), `frontier_classify.py` / `exclude_audit.py` /
  `triage_ladder.py` / `recover_route.py` (the honest census), `agent_verdicts.py` (subagent transcripts).
- **Integration/plumbing recovery:** `sync_tu_decls.py`, `cast_self_callers.py`, `fix_tu_ret_decls.py`,
  `fix_decl_mirror.py`, `restore_dropped_decls.py`, `decl_from_use.py`, `decl_prior.py`, `reconcile_slate.py`,
  `integration_resolver.py`, `rtu_second_chance.py`, `rtu_shadow.py`, `recover_rejects.py`, `scope_demote_drafts.py`.
- **Carves and splits:** `jtbl_lane.py`, `jtbl_pads_fix.py`, `pads_audit.py`, `interleave_check.py`,
  `split_indicator.py` (a fleet CHECK), `o0_boundary.py` / `o0_detect.py`, `reorder_passthrough.py`,
  `oracle_reorder.py`, `main_diff_locate.py`.
- **Library linking (S78/S79):** `psyq_bss_split.py` (+ `psyq_bss_probe.py`) — the scattered-`.bss` class closed
  (SYS.o, VM_F.o, GS_001.o, cookbook §489); `psyq_integrate --yaml` / `--redefine-sym`; the **PsyQ Runtime Library
  4.2 + J421PD (libpad 4.2.1) archive** banked under `tools/psyq/` (R20; ELF in `.run/obj42/`); `ghidra_apply_symbols.sh`
  + `ghidra_scripts/ApplySymbols.java` (headless symbol mirror — MCP renames do not persist).
- **Verbatim end-state:** `verbatim_check.py` (the drift guard, in tools-health), `verbatim_target_s.py`,
  `verbatim_to_stub.py`, `config/verbatim_manifest.json` (5 PERMANENT rows, ratified S80).
- **Permuter (S79/S80):** `permuter_sweep.py`; `p16_permute.py` + `permuter_ils.py` repaired (pinned + K&R seeds).
- **Knowledge base:** cookbook **§173–§495** (the atlas laws §173–§176, the wave doctrine, the integration classes,
  §332/§434/§474 wall proofs and their later refutations, §487–§490 provenance→archive→link, §491–§495);
  `docs/gcc-2.7.2-map/` extended; `docs/wave-playbook.md` (the procedure), `docs/frontier-atlas.md`,
  `docs/frontier-p32.md`, `docs/disc-completeness.md` + `docs/disc-ledger.md`, `docs/tool-designs/*`,
  `docs/resident-dossier.md`, `docs/backlog.md` (18 open near-misses), `config/wave_exclude.txt` (8 walls),
  `docs/decision-log.md` (S51–S80 entries, R31), `docs/accelerators.md`, `docs/SETUP.md` (every tool row, R21).
- `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/Phase31.md`** (R19). `phase-ends/PhaseEnd_Phase31.md` — this file.

**Tools/packages installed:** none external (no apt/pip). Banked assets: the PsyQ RTL 4.2 archive (383 KB 7z,
sha256-recorded in `tools/psyq/CHECKSUMS.sha256`); the vanilla gcc-2.7.2 reference completed under `tools/reference/`.

**Verification results (literal, at close — S80):**
- `make clean && make extract-all && make check-all` → extract-all **212 extracted, 0 failed of 212 (+ main)**;
  **check-all: 213 passed, 0 failed of 213**, exit codes 0/0 (`.run/S80/r22b_extract.log`, `.run/S80/r22b_check.log`).
  R22 was run after every banked batch of the phase; no batch closed red.
- `make tools-health` → **OK** rc 0: sigs fresh; corpus(+resident) 0 PHANTOM + 0 TRUNCATED; cdecl; audit-binaries
  213/213 citizens (R36); report lint + dedup **2,220 validated / 0 failed**; cookbook-index; split_indicator 213 OK.
- `make report BINARY=main` → SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd` byte-identical, WITH the SDK object
  dirs and WITHOUT them (fresh-extract fallback, S79); REAL **777** · LINKED **1,256** (268 objects / 70 blocks) ·
  VERBATIM 3 · INCLUDE_ASM stubs **12** · matchable 2,091 · byte-identical **2,079 / 2,091 = 99.43%**; MAIN game-code
  weighted **39,479 / 41,556 = 95.0%** (the digest prints 41,534: Ghidra's flow-derived body for `FUN_80023bf0` omits
  its last 22 instructions — splat's 281 is right, the S79 draft is 281/281 exact-length).
- Fleet (`docs/progress.fleet.md`): **instr-weighted 13,481,386 / 13,485,889 = 100.0%** · distinct-code 5,809,493 /
  5,813,996 = **99.9%** (90,920 / 90,929 unique fns) · fn-count 363,136 / 363,157 = **99.99%** · INCLUDE_ASM stubs
  **21** · NON_MATCHING **0** in any default build (G4).
- Census (`.run/frontier_s80.json`, `tools/frontier_classify.py`): **21 stubs / 4,554 ins** — main 12 (2,077),
  resident 2, md_MAIN_003 1, md_MAIN_034 1, ov_SC02_017 1, ov_SC03_105 2, ov_SC06_022 1, ov_SC07_002 1; classes
  B-CARVE 4 / D-NEAR 10 / F-FAR 7; every row with class, closeness, best draft and named blocker (`docs/frontier-p32.md`).
- `verbatim_check --strict`: **5 bodies in tree == 5 manifest rows, all PERMANENT**, no drift. `make audit-disc`
  residue 0, UNCLAIMED = 5 (MAIN/7, MAIN/9, SC03/53/54/56 — the explicit exclusion, `docs/disc-completeness.md`).
- `git status`: only `config/`/`tools/`/`src/`/`docs/`/`.run/`(allowlisted)/`phase-ends/` tracked; the `ghidra/`
  `db.*.gbf`/`~index` churn is R23 restart-noise (never staged). Ghidra DB: the S78 symbol mirror was applied via
  `ApplySymbols.java` and R9-verified; the DB is text-derived and re-applicable, deliberately not committed.

**Milestone achieved (confirmed by Drew, gate 2):** the chartered milestone — *P30-shaped: the campaign run to its
measured ceiling, every remaining stub on a named ledger at close, main fully included* — is **met**: fleet
**100.0% instr-weighted / 99.9% distinct / 213/213 byte-identical**, main **99.43% byte-identical (95.0% game-code)**,
and the 21 remaining functions each carry a class, a closeness, a best draft and a named blocker or a cited wall
mechanism. **Roadmap v2's stricter wording for P31 ("main + resident at 100% game-code") is NOT literally met** —
main has 12 open functions and the resident 2 — and the phase says so rather than redefining it (P9); those, with
seven others, are the Phase-32 frontier. Its other two clauses are met: all disc code is onboarded (213 binaries) or
explicitly excluded with evidence (5 payloads), and the contract denominators are final.

**Next:** **Phase 32 — the last 21 + the parked 5** (short, kill-gated). Open a fresh session in **plan mode, Max**
(Tier 1); read **`docs/frontier-p32.md` first**, then roadmap v2 §3 P32/P33 and this file's Roadmap delta. Proposed
shape (Drew's steer 2026-09-05: "plan mode will use it as a jumping-off point to build a full plan to 100%"):
tooling first (the two NON-CONTIGUOUS jtbl splits + the leading-island case — 2–3 free banks), one bounded Opus pass
over the 10 near/far bodies, no drafting on the 8 pinned walls (final verdicts only), a static-RE pass over the 5 parked
payloads, close with the final ledger; then P33 = verify + flip.

## Roadmap delta (roadmap v2 §0 — what Phase 31 changed about the road ahead)

- **P31's charter was re-cut at gate 1** from roadmap v2's per-function grind (T1 type-1 onboarding · T2 the
  main campaign · T3 resident 14 → 0) into the **frontier atlas + wide-tolerance campaign**; the v2 T1/T2 content
  was absorbed and finished (the md_* fleet is onboarded — 213 binaries; main's SDK regions are LINKED from real
  objects incl. the libpad 4.2.1 archive; `SaveLoadRoutine` banked; main's independent second oracle exists —
  `make sig-main-oracle` + `audit-corpus`). T3 stopped at **2** (resident `func_800D06E8` F-FAR, `func_800D128C`
  carve-blocked with a closeness-0 draft).
- **P32 as written in v2 ("behemoths + the wall endgame") is largely consumed:** no behemoth is on the frontier
  (the largest open function is 518 ins), the §172 mechanism-complete wall class, the GIANT exemplar walls and the
  §332 band "walls" (twelve of them were Sony's libpad 4.2.1, linked in S79) are all off the ledger. **What P32 is
  now: the 21-row census + the 5 parked payloads**, with a kill gate — `docs/frontier-p32.md` §4.
- **Metrics re-baselined and honest:** the fleet number the contract cites is now **100.0% instr-weighted** with the
  21-stub / 4,554-ins remainder stated; main's game-code denominator carries the 22-ins Ghidra-boundary correction;
  the S79 close was one bank overstated (an assembly "bank", corrected S80) — P32 counts banks from the SOURCE.
- **Doctrine changes that outlive the phase:** every "compiler wall" is a provenance question first (§487–§490:
  provenance → archive → link → compiler — twelve walls and a 383 KB download); the instrument is a suspect before
  the subject (R40; ~a third of this phase's walls were tooling); a masked score is not a closeness until the diff is
  read; a ledger's best draft may never be an `__asm__` body.
- **Scale estimate:** P32 ≈ 3–5 sessions (kill-gated); P33 ≈ 2–4 (unchanged from v2).

## Deviations

| Item | Plan (gate-1 plan / roadmap v2 P31) | Actual | Reason |
|---|---|---|---|
| Phase length | "a campaign to ceiling; close on measured decay" (~10–18 sessions) | **30 sessions, ~1,660 commits** | the ceiling kept moving: each instrument repair (R35/R40) re-opened a class the previous session had called a wall — closing early would have banked those walls as permanent |
| T7 mechanical-cousin engine | a driver over the cousin lanes | **refuted by its own probe (0/26)** — no driver built | cousins are 0.85-similar DIFFERENT functions (§168 law 1 re-derived); the classifier became T8's LEN+N lane instead |
| T8 LEN+N mechanical lane | a free lane | **honest null** (0 mechanical; 587 routed: 345 redraft / 49 permuter / 192 cards) | stored drafts rarely get constants wrong; LEN drift is shape |
| Wave size | 40–50-card waves | **the 6,000+-instruction wave doctrine** (Drew, 2026-08-15) after wave O drafted UNKNOWN cards at 96% | UNKNOWN was "the atlas could not name a lever", not difficulty; size was nearly free mass |
| Execution shape | orchestrated waves | **autonomous lanes** (drafter / gater / maintenance / stallguard) under a 2-workflow budget, then a completion sprint (S78–S80) once the census fit on one page | the lanes banked while I slept; the sprint's task order was Drew's census-based call |
| main | band-tiered waves | main was **link-blocked** for weeks (S52 E-probe: 1 byte-correct fn ⇒ a 2-byte whole-EXE diff), then gated only by `gate_main` (clean rebuild; S71–S73 debugged its false-pass/blind-revert) | main's extract rewrites the linker script (R22's own rationale); incremental gates give false verdicts on it (R43) |
| Walls | a wall ledger with proofs | **most recorded walls were not walls**: §332's twelve were Sony objects (S79), `SaveLoadRoutine`'s §434 wall was a splat symbol boundary (S75), the §42e pin-crash (P27), the S68 `func_800CB00C` pin labels a wrong draft, the permuter "plateaus" on pinned seeds were one cycle (S80); one is PROVED (§474) and seven carry citations | R40, five times over: exonerate the instrument first |
| Verbatim `__asm__` bodies | not in scope | **the assembly-posing-as-C class discovered (S75: 199 bodies), censused from the archive tables (24 game), reduced to the 5 PERMANENT rows (S80)** — and one S79 "bank" found to be exactly this class | a byte gate is a null oracle for "is this C?" |
| Resident 14 → 0 | 0 | **2** | one F-FAR body, one carve refusal — both routed in `frontier-p32.md` |
| Rules | (P10 at close) | R37–R39 ratified at gate 1; R40–R43 (S58) and R61 (S77) accepted mid-phase; R44–R60 recorded as candidates | the phase generated governance faster than its close could hold |

## What we believed, what failed, and what we would do sooner (for the retrospective; the detail is in `docs/decision-log.md` S51–S80)

- **Believed:** the remaining 12k stubs were a drafting problem the atlas would route. **True for ~11.6k of them.**
  The last few hundred were integration (declarations, file placement, symbol spellings), carve state, or Sony's own
  objects — and the tools that measured them were the walls' co-authors. **Sooner:** run `verbatim_check --strict`,
  `exclude_audit --assert-fresh`, the provenance question (§487) and an R39 control on every new refusal-check from
  the first wave, not at S75/S79/S80.
- **Believed:** the permuter had exhausted the pinned near-misses. **False** — it had never run on one (S80).
  **Sooner:** any tool that reports "unchanged" for N cycles must prove it iterated (R61a); we wrote that rule in S77
  and still shipped a tool that violated it.
- **Believed (S52):** main was un-gateable. **True for incremental gates, false for a clean rebuild** — the
  night lost to a "linker defect" was R22's own rationale. **Sooner:** a null-draft control before any diagnosis.
- **Cost:** the campaign's token spend went overwhelmingly to drafting that was already byte-correct and failed on
  plumbing (~92% byte-correct, ~27% banked at the S29 measurement; the recovery tooling of this phase is what closed
  that gap), and to re-drafting functions whose banked twin was two words away (§397, ~250k tokens before
  `twin_rescan` existed).

## Commit Message
```
(Phase 31 landed as ~1,660 commits 2026-08-14 → 2026-09-05; the last in-phase commit is 3c292ef09 (docs/frontier-p32.md).
This close = the archived log + this PhaseEnd, Drew's milestone-close commit.)

chore(phase-31): CLOSE — the frontier atlas & wide-tolerance campaign; fleet 95.3% -> 100.0% instr (213/213), main 1,041 -> 12 open, the last 21 ledgered (v1.30.0)

- PhaseEnd_Phase31.md written; CURRENT_PHASE.md archived to phase-ends/logs/Phase31.md (R19)
- 30 sessions (S51–S80): the atlas (T4/T5), the 6k-ins wave doctrine, the autonomous lanes, the
  completion sprint; stubs 12,059 -> 21 (4,554 ins); dedup 2,061 -> 2,220 / 0 failed
- main: SDK regions LINKED from real objects incl. the PsyQ RTL 4.2 + libpad 4.2.1 archive (S79),
  the scattered-.bss class closed (psyq_bss_split), SaveLoadRoutine banked, main's second oracle;
  REAL 777 / LINKED 1,256 / stubs 12 / 99.43% byte-identical / 95.0% game-code
- the verbatim class discovered, censused from the archive tables, reduced to the 5 PERMANENT rows
- rules: R37–R39 ratified (gate 1), R40–R43 + R61 accepted in-phase; R44–R60 + two S80 candidates
  proposed below for Drew
- Roadmap delta: P32 = the 21-row census + the 5 parked payloads, kill-gated (docs/frontier-p32.md)
- milestone: 213/213 byte-identical, fleet 100.0% instr, every remaining stub on a named ledger;
  roadmap v2's "main + resident at 100%" NOT literally met (12 + 2 open) — stated, not redefined
- v1.29.0 -> v1.30.0
```

## Rules Added This Phase

Ratified at gate 1 (2026-08-14, previously proposed at PhaseEnd_Phase29/30): **R37** (probe before costing),
**R38** (read the recorded failure verdicts before designing an experiment), **R39** (negative-control every new
refusal-check against the already-succeeded population). Accepted in-phase by Drew (2026-08-23): **R40** (exonerate the
instrument before attributing a failure to its subject), **R41** (a cost/rate/yield number ships with its
denominator), **R42** (commit banked work the moment it exists; never blind-revert a dirty `src/`), **R43** (a tool
must refuse an input it cannot handle, never process it wrongly). Accepted 2026-09-03: **R61** (a tool must
distinguish "judged and failed" from "not judged", and a judging tool must model what the gate does to the draft).

**Candidates recorded in the log, for Drew to accept, modify or reject (P10):**

| Rule | Reason |
|---|---|
| **R44 — A card may not name a lever the knowledge base does not contain.** | 108 transcripts grepped `extend-tell` against a cookbook containing that string zero times (S59). |
| **R45 — Draw-time bankability: never draw a card the pipeline cannot bank.** | 11 -O0 functions drawn 79 times across 19 waves; none could ever have banked (S59). |
| **R46 — A budget is part of the harness, not a constant.** | One turn/cost cap across card sizes differing 2.4× starved the large ones (S59). |
| **R47 — Consume every verdict layer.** | A stage reading one bit of one oracle staged garbage forever: 82 of 117 A-prop drafts rebuilt every 45 minutes (S59). |
| **R48 — Never key by bare function name.** | Three fn-keyed collision defects in one session, incl. a scratch dir one run `rm -rf`'d under another (S59); the same-name phantom drafts of S79 #7. |
| **R49 — A soft error inside a success envelope is still that error.** | The soft 429 (200 + code 429) and `gate_main`'s `rc≠0` read as "no binary" (S59). |
| **R50 — Periodic whole-fleet verification.** | A byte gate is silent about every binary it did not build; two sat RED for hours (S59). |
| **R51 — A derived property stored as config will go stale and take a binary with it.** | `JTBL_PADS`: three REDs in one day; derive it or give it a byte-proven self-repair (S60). Also `frontier_classify`'s hard-coded LINKED set (S79). |
| **R52 — A blanket committer must not adopt a collapsed file.** | "Commit the dirty tree rather than revert" is right for `src/` and wrong for config (S60). |
| **R53 — Verify a build from its exit code, not its output file.** | A failed build leaves the previous binary in place; `make build; sha1sum` is a FALSE GREEN (S60, twice). |
| **R54 — A guard downstream of the failure is not a guard, and a guard that is not running is not a guard.** | `api_agent`'s warning sat one line below the KeyError that killed every run; `config_sane()` predated the process it should have stopped (S60). |
| **R55 — A lane that runs unattended must leave evidence.** | A 30-minute silent gate hid a 31→67 min regression; a cap silently stopped existing (S60); the S80 ILS logs were empty for 20 minutes. |
| **R56 — A gate verdict is a measurement of the draft only while the binary's baseline is green.** | Check the baseline before billing the subject (S61; enforcement = the BASELINE-RED skip + the fleet audit). |
| **R57 — An instrument's own write path is part of the instrument.** | A repair tool whose writer corrupts what it measures voids its own search and reports the corruption as the subject's failure (`write_pads`, S61). |
| **R58 — A session-close "clean" must quote the fleet's green count.** | Tree-clean and fleet-green are different invariants (S60 closed "clean" with 15 binaries red). |
| **R59 — A blanket commit of another lane's mid-gate tree is a race, not a backup.** | S61. |
| **R60 — `config/overlays.mk` and the splat yamls are CARVE STATE.** | A gate/lane commit may only carry its own binary's lines; any blanket restore/commit is followed by `interleave_check` + `pads_audit` on every touched binary (S61). |
| **R62 (S80) — A ledger's best draft may never be an `__asm__` body, and a bank whose body is `__asm__` is a verbatim, not a bank.** | S79 #7 spliced the function's assembly and counted it banked; the byte gate is a null oracle for "is this C?"; `verbatim_check --strict` belongs in the per-bank close (§495). |
| **R63 (S80) — A permuter/waypoint score is not a closeness until its diff is read.** | A masked "1" had replaced an `addiu` with a store; R14 applied to the instrument's own output (§493/§494). |

*(Techniques stay in the cookbook — §173–§495 — per the Phase-8+ precedent; the strategic findings are in
`docs/decision-log.md` (R31) and `docs/accelerators.md`.)*

## PhaseEnd Changelog
**v1.29.0 → v1.30.0 — Phase 31 complete (Gen2 phase 22; the longest phase; the campaign that took the fleet to
100.0% instr-weighted).** Chartered as the frontier atlas + a wide-tolerance campaign to ceiling, the phase built the
atlas (a per-function feature layer + multi-tier similarity groups + lever labels over all 12,059 open stubs), then ran
the campaign in three shapes — orchestrated waves, autonomous lanes (drafter/gater/maintenance under a 2-workflow
budget), and a final census-driven completion sprint — driving stubs **12,059 → 21**, the fleet **95.3% → 100.0%
instr-weighted** (distinct 90.0% → 99.9%), and main **1,041 → 12 open** (game-code 0.5% → 95.0%, byte-identical
99.43%), at **213/213 byte-identical after every banked batch**. Its defining discovery was that the wall was mostly
ours: the §332 band walls were Sony's libpad 4.2.1 (found on archive.org, linked byte-identical), the scattered-`.bss`
exclusion class fell to a link-time splitter, `SaveLoadRoutine`'s wall was a splat symbol boundary, the permuter had
never run on a pinned seed, and one "bank" was the assembly itself — each repaired, controlled (R39), and written into
the cookbook (§173–§495) and the decision log. The verbatim-`__asm__` class was discovered, censused from the archive
symbol tables, and reduced to the five PERMANENT hand-asm rows. Governance: R37–R39 ratified, R40–R43 and R61
accepted, R44–R63 proposed. The chartered milestone is met and the roadmap's stricter "main + resident at 100%" is
honestly not: **the last 21 functions and the 5 parked payloads are Phase 32**, documented for plan mode in
`docs/frontier-p32.md`.

## Plain-English Recap
This phase started with about twelve thousand functions of the game still un-translated and ended with twenty-one.
The way we got there changed three times: first a "map" that grouped every remaining function by what trick it would
need, then big batches of AI agents translating hundreds of functions at a time with an automatic bit-for-bit referee,
then unattended "lanes" that kept banking while nobody watched, and finally a hand-run sprint once the leftover list
fit on one page. Every single one of the game's 213 files still rebuilds exactly, and the shipped code is now 100.0%
rebuilt by instruction count. The surprise of the phase was how many "impossible" functions were our own mistakes: a
whole stretch of the main program we had labelled compiler walls turned out to be Sony's controller library — we found
the exact February-1998 version on the internet and linked it in; a "wall" was a mislabelled boundary; our brute-force
polisher had silently never worked on a whole class of drafts; and one "finished" function was the original assembly
pasted back in. Each time, the fix was to repair the instrument, prove the repair, and write the lesson down. What
remains is small and specific: twenty-one functions, each with its cause recorded (three need a build-tool change and
should then be free, eight are genuine compiler walls with proofs or citations, ten are near-misses that need one more
careful attempt), plus five small disc files we have never seen the game load. That is the next, short phase.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase31.md` (R19, via `git mv` — **left uncommitted
with this file for Drew's milestone-close commit**, R6 gate-2 sign-off). The Phase-31 work is committed across the
sessions (through `3c292ef09`); **Drew commits AND pushes** this PhaseEnd + the archived log. The Ghidra MCP was
stopped cleanly (R23); no DB change to commit (the `db.*.gbf` churn is restart-noise — do NOT stage it). Gen2
continues — do **NOT** start Phase 32 here. Start a **fresh session** (effort **Max**, **plan mode**) for
**Phase 32 — the last 21 + the parked 5**, opening from `docs/frontier-p32.md`. Keep this file forever.
