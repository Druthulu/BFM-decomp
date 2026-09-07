# PhaseEnd — Phase 32: The Last 21 + the Parked 5 — the frontier emptied (every game-code function in every binary is byte-identical C)
**Date:** 2026-09-06 · **Project Version:** 1.31.0 · **Phase Status:** Complete (milestone confirmed by Drew, gate 2 — 2026-09-06) · **Generation:** Gen2 (23rd phase of the arc; Phase 14 public-flip deferred to P33)

> Gen2 phase 23 (8→…→31→**32**). Fifth phase off `docs/roadmap-to-100.md` v2 (§3 P32 as written was already consumed by
> P31; this phase was chartered from `docs/frontier-p32.md` as the 21-row census + the 5 parked payloads, short and kill-gated).
> Ran **5 sessions (S81–S85, 2026-09-05 → 2026-09-06)** and **111 commits** (`77df1092e..HEAD`). The granular trail (every
> variant, verdict, instrument defect and its repair, and the session checkpoints) is preserved on-demand at
> **`phase-ends/logs/Phase32.md`** (R19 — NOT auto-loaded). Owner decisions (Drew): gate 1 (2026-09-05, plan mode, Max;
> R44–R63 ratified); the T4b directive (2026-09-05: "anything that isn't the original hand-written asm or the PsyQ libs needs
> to be cracked and banked before we finish" — superseding the kill gate); "no second agent round; hand-crack the remaining
> ones"; the T4c directive (2026-09-06: "do that now, lets crack these before closing the phase"); the R64 session-start
> protocol (the digest, 2026-09-05); the 90%-context pause and "bank/gate/harvest everything" (2026-09-06); gate 2.

## Build Log

**The phase in one line:** the 21 remaining stubs became 54 (five parked disc payloads onboarded, fleet 213 → 218), and
all 54 were banked byte-identical — including one PROVED wall, six candidate walls and two "final verdicts" — so the fleet
reads **100.00% fn-count / 100.0% instruction-weighted / 100.0% distinct-code with 0 INCLUDE_ASM stubs**, main
**2,091 / 2,091 = 100.00% byte-identical**, 218/218 binaries green from a clean rebuild after the last bank, with **zero
register pins, fences or asm bodies in the final two banks**.

**Files created/changed and complete — do not recreate** (category summaries; the per-commit list is `git log
77df1092e..HEAD` and `phase-ends/logs/Phase32.md`):

- **Source — 77 functions banked byte-identical** (`src/**`): T1a `resident:func_800D128C` (`c513e1fbb`, a stored
  closeness-0 draft freed by three instrument fixes), T1b `ov_SC02_017:func_80186C64` (`c7f5b498a`, a RELOC-ONLY twin
  remap), T1c `md_MAIN_034:func_800CB00C` (`059266afc`, a stored S72 body the census had mis-keyed), T2c ×20 (twins,
  constant flips, pass-throughs — 0 drafting tokens), T3 ×39 (the one-agent-per-function pass), T4b ×13 (the Fable first pass
  ×11 incl. the §474 "PROVED" wall `func_80011380` `35fa11674`; the hand pass `md_MAIN_007:func_800CF408` `8fa12bc22` and
  `ov_SC03_105:func_80185810` `cdd9a2cb8`), T4c ×2 (`main:func_80032A74` `f9a90affb`, `main:func_80039308` `ffb1949a1`).
  `config/dedup.us.yaml` 2,220 groups / 0 failures (unchanged count; 255,708 instances).
- **Five binaries onboarded** (T2b, `config/splat.md_*.yaml`, `config/check.md_*.sha`, `config/overlays.mk`, `src/md_*/`):
  `md_MAIN_007` @0x800CEDF8 (`1a696a851`), `md_MAIN_009` @0x800CD348 (`10aaf5c29`), `md_SC03_053` + `md_SC03_054` @0x801EF468
  (`b52d67be0`), `md_SC03_056` @0x801CBB50 (`1e843c607`) — every base static-derived (`tools/payload_base_evidence.py`, controls
  7/7) and byte-proven by the first internal-call C bank; `make audit-disc` residue 0, **UNCLAIMED 0 of 220**;
  `docs/disc-completeness.md` P32 section, `docs/memory-map.md` §S45 p7.
- **Instruments (new/repaired, all under `tools/`, SETUP rows per R21):** `payload_base_evidence.py` (T2a);
  `agent_drafts_restore.py` (transcript replay after a dead coordinator, S82); `ghost_census.py` + the `cc1_dumps.sh` repair
  (frame line, spill lines, census; `-dL` loop dump) (S84/S85); **`cc1_dumps_tu.sh`** (real-TU pass dumps from an `rtu_match
  --work` dir — the standalone compile is NOT faithful on main TUs) + **`alloc_table.py`** (global's allocation order /
  priorities / hard regs from the dumps) (S85); `backlog.py` tie-break repair (a re-verdict could never render); the
  `jr_isolate_all` provided-types fix (§496), `jtbl_carve --pre` + `harvest_verify` extract-rc + `interleave_check --pre`
  fixes (§498); the Makefile `C_SRCS` dotfile guard (`563a21144`); `.run/P32/t3s3/bank.sh` + `splice.py` (the overlay bank
  chain: verbatim grep → rtu → splice → one build → sha → commit-on-green; session trailer from `$CLAUDE_SESSION`);
  `exclude_audit --write` drops banked pins; `frontier_classify` census JSONs for every step (`.run/P32/frontier_*.json`).
- **Knowledge base:** `docs/matching-cookbook.md` **§496–§501-R** (the four T1a instrument classes; §499 module onboarding; §500
  the T3 closers/classes + §500-F/G/H/I; §501–§501-L the twelve S83 dump-read laws; §501-M/§501-O the phantom-slot producer
  censuses; §501-N/§501-P port-the-sibling's-spelling; **§501-Q the combine self-update ghost slot; §501-R the three-times-read
  hoisted invariant: inline temps, `u16` as a cse firewall, the allocation order IS the callee-saved bank**);
  `docs/cookbook-index.md` regenerated; `docs/accelerators.md` (8)–(16); `docs/decision-log.md` P32 S82/S83/S84/S85 entries
  (R31); `docs/wave-playbook.md` §S80 addendum-2 (per-function work dirs, JSON-only final message, the 20-agent cap, the
  recovery tools); `docs/backlog.md` (1 open row — the legacy `func_80062144` "won't compile standalone" entry, NOT a stub);
  `config/wave_exclude.txt` **0 entries**; `config/verbatim_manifest.json` 5 PERMANENT rows (unchanged).
- **Governance:** **`phase-ends/DIGEST.md` created** (R64: every phase's synopsis + every rule in full + the corrections to
  PROJECT_CONTEXT.md + the doc map; the session start reads it instead of all PhaseEnds); `CLAUDE.md` load order + Phase
  Boundary step 3b; `phase-ends/README.md`; SETUP §7; the two memories. `phase-ends/CURRENT_PHASE.md` → **`phase-ends/logs/
  Phase32.md`** (R19). This file.
- `.run/P32/**` allowlisted subtrees (R20 — the drafts, variants, reproducers, verdict logs, bank bodies, slates, notes and
  gate/R22 logs are the only copy of this work): `t3/`, `t3s3/`, `t4/`, `t4b/`, `t4c/`, `t4d/`, `t4e/`, `t5x/`.

**Tools/packages installed:** none external (no apt/pip). No Ghidra DB change (the SessionStart hook's headless MCP was
never written to; the `ghidra/` churn is R23 restart-noise, never staged).

**Verification results (literal, at close):**
- `make clean && make extract-all && make check-all` (after the last bank, `ffb1949a1`) → clean EXIT=0 · **extract-all: 217
  extracted, 0 failed of 217 (+ main, serial)** EXIT=0 · **check-all: 218 passed, 0 failed of 218** EXIT=0 at 16:13:17 MDT
  (`.run/P32/t4e/r22_{clean,extract,check}.log`). R22 was also run after every earlier banked batch of the phase (T1a 213/213;
  T1b+T1c 213/213; T2c 218/218; T3 218/218 ×3; T4b 218/218 ×2; the row-(d) bank 218/218) — no batch closed red.
- `make report` (`.run/P32/t4e/report_close.log`): **FLEET fn-count 363,214 / 363,214 = 100.00% · instr-weighted 13,488,497 /
  13,488,497 = 100.0% · distinct-code 5,816,589 / 5,816,589 = 100.0% (90,984 / 90,984 unique fns) · MAIN game-code 41,534 /
  41,534 = 100.0% · INCLUDE_ASM 0 · NON_MATCHING 0 (G4) · LINKED PsyQ objects 1,256 · REAL substantive 360,737 · dedup 2,220
  groups / 255,708 instances.** The digest's main denominator is 41,534; the corrected one is 41,556 (the 22-instruction Ghidra
  flow-boundary gap on `FUN_80023bf0`, P31 S79) — at 0 stubs both read 100%.
- `make report BINARY=main` (`report_main_close.log`): **REAL 789 · LINKED 1,256 · VERBATIM 3 · INCLUDE_ASM 0 · matchable 2,091 ·
  byte-identical 2,091 / 2,091 = 100.00% · build SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd`** (the WITH/WITHOUT-SDK-object-dirs
  dual invariant was proven in P31 S79 and re-exercised by every `gate_main` clean rebuild this phase).
- `make tools-health` → OK at the T4b close (`.run/P32/t4d/tools_health.log`: sigs fresh; corpus(+resident) 0 PHANTOM + 0
  TRUNCATED; cdecl; audit-binaries 218/218 citizens (R36); report lint + dedup 2,220 validated / 0 failed; cookbook-index OK;
  split_indicator 218 OK); the post-T4c run is `.run/P32/t4e/tools_health.log` (read by the next session's preflight if it had
  not finished when this file was written — the only tree changes since the T4b-close run are the two main banks, both gated
  by `gate_main`'s clean rebuild).
- Census `tools/frontier_classify.py` → `.run/P32/frontier_t4c_final.json`: **0 stubs / 0 instructions** (the phase's arc: open
  21 → T2c 54 → T3 15 → T4b 4 → S84 3 → S85 2 → 0). `verbatim_check --strict`: **5 bodies == 5 manifest rows, all PERMANENT**.
  `exclude_audit --assert-fresh config/wave_exclude.txt`: 0 entries. `twin_rescan`: 0 open. `make audit-disc`: residue 0,
  UNCLAIMED 0 of 220 (T4b close).
- Tree: non-ghidra clean at HEAD; `git status` shows only the R23 `ghidra/` churn.

**Milestone achieved (confirmed by Drew, gate 2 — 2026-09-06):** the chartered milestone — *every census row BANKED or
carrying a FINAL verdict; every parked payload onboarded byte-identical at a byte-proven base or excluded with evidence; the
fleet byte-identical at every banked batch; the PhaseEnd carrying the final wall ledger, the corrected denominators, all
three metrics and the roadmap delta* — is met on its **strongest** reading: **every row is BANKED (the "FINAL verdict"
clause was never needed — the one PROVED wall, the six candidate walls and the two S84 verdicts all fell), all five payloads
are onboarded (UNCLAIMED 0 of 220), 218/218 byte-identical from a clean rebuild after the last bank, and the wall ledger is
EMPTY.** What is not C, stated plainly (P9): main's **1,256 LINKED functions are Sony's PsyQ objects** (byte-identical by
link, not our source — the Phase-31 decision; libs-from-source is a parked Gen3 stretch) and the **5 PERMANENT verbatim
`__asm__` bodies** (hand-written assembly in the original, censused from the archive tables in P31).

**Next:** **Phase 33 — 100% verification + the public flip + Gen2 exit** (roadmap v2 §3 P33, ≈2–4 sessions). Open a fresh
session in **plan mode, Max** (Tier 1); plan from roadmap v2 §3 P33 + `docs/gen2-roadmap.md`'s Phase-14 checklist + this
file's Roadmap delta. First task: the contract verification (R22 fleet + the with/without-SDK dual + both audit oracles +
the three-metric dashboard) as one recorded run, then the public-flip checklist.

## Roadmap delta (roadmap v2 §0 — what Phase 32 changed about the road ahead)

- **The frontier is empty.** Roadmap v2's P32 ("behemoths + the wall endgame") and P31's stricter "main + resident at 100%
  game-code" are now BOTH met literally: 0 stubs, main 2,091 / 2,091. The "Drew-reviewed wall ledger with a re-attack
  cadence" alternative is moot — there is no ledger. The metrics contract's three numbers read 100.00 / 100.0 / 100.0.
- **Scope is final:** 218 binaries (main + resident + 138 location overlays + 78 code modules), all disc code onboarded or
  explicitly excluded (UNCLAIMED 0 of 220), 2,220 dedup groups.
- **Doctrine that outlives the phase:** (1) *a wall is a census against a LIST* — two "final verdicts" written by producer
  censuses (§501-M/O) fell to producers missing from the list (§501-Q combine's self-update bookkeeping gap; §501-R loop.c's
  user-variable rule + cse's later-mention canonicalization); (2) *reproducers before probes* — 1-second compiles of 5-line
  functions settled in minutes what hours of real-function variants could not (accelerators (15)); (3) *read the allocation
  ORDER before any register lever* — the callee-saved bank is global's priority order, and every pin the S79–S84 drafts
  carried came off byte-identical once the source shape was right (accelerators (16)); (4) *port a banked sibling's spelling
  before any dial, and grep the idiom's constants — the atlas's similarity score is not a shape oracle* (§501-N/P,
  accelerators (13)/(14)); (5) *the session-start digest* (R64) — the protocol now costs ≈100k tokens instead of ≈150k+.
- **P33 remains as written in v2** (contract verification; the two-repo mirror, the rom→decoder tool, AGPL-3.0, no-ROM CI,
  frogress/decomp.dev, README/docs refresh, the first-push gate, the one-way sync script, the Ghidra `ExportSymbols`
  text-export; the parking-lot sweep; the releases: the gcc-2.7.2 codegen map, `xsig`, the permuter-ILS/masked-scorer PR, the
  drafter write-up; Drew's endgame deliverables; v2.0.0 Gen2 EXIT) — plus one P32 addition for the verification task: **the
  post-T4c `make tools-health` run must be read and recorded** (it was still running at this file's writing), and the
  `docs/backlog.md` legacy row `func_80062144` should be pruned as "not a stub" rather than carried.

## Deviations

| Item | Plan (gate-1 plan / `frontier-p32.md` §4) | Actual | Reason |
|---|---|---|---|
| Kill gate / scope | "a session that banks nothing and produces no new verdict ends the crack work"; 8 walls get NO drafting (final verdicts only) | **superseded by Drew's T4b directive**: all 15 remaining rows cracked (11 by a Fable pass, 4 by hand) and then **T4c** (added 2026-09-06) for the last two | Drew: "anything that isn't the original hand-written asm or the PsyQ libs needs to be cracked and banked before we finish" |
| T3 expectation | 1–4 banks from a bounded Opus pass (S79: 3/11) | **47 drafted, 39 banked, 0 FAIL, 0 new walls** | the census had become 54 rows after T2c (36 never-drafted ≤50-ins bodies in the five new modules); a Haiku tier banked 17/17 |
| Models | Opus for T3; "Fable only if an agent names a wall class the map lacks — STOP and prompt Drew first" | Fable used for the T4b first pass (15 agents, 11 MATCH) — **with Drew's explicit permission**; the hand passes (S84/S85) used no agents | the T4 walls were compiler-internals rows; Drew called the Fable round a permission, not a requirement, then "no second agent round" |
| T2d | one bounded static-RE pass if MAIN/7 or MAIN/9 refused every candidate | **NOT NEEDED** — all five payloads onboarded on their first candidate | T2a's static alignment (self-calls / fn-ptr-table entries on the module's own function starts) gave every base; the all-INCLUDE_ASM first build is a NULL oracle for fine base errors (R34) — the bases were proven by the first C bank |
| The wall ledger | the PhaseEnd carries the final wall table with proofs | **the table is EMPTY** — the §474 PROVED wall (`func_80011380`), the six CANDIDATE walls and the S84 PROVED/PLATEAU rows all banked | every citation named a real mechanism and the wrong pass, or a census with a missing producer (§501, §501-Q, §501-R) |
| Session count | 3–5 | 5 (S81–S85), 111 commits | T4b/T4c extended the phase by two sessions |
| Coordinator death | (not planned) | the T3 coordinator hit "Prompt is too long" (S82) with 22 agent completions landing in a dead session; recovered via `agent_verdicts.py` + a new `agent_drafts_restore.py`; one agent's tidy-up swept 11 sibling deliverables (R48 class) — restored, byte-verified | the S80 one-agent-per-function shape + the 20-agent harness cap; the per-function work-dir rule went into the playbook |
| "Banked" bookkeeping | (n/a) | two S83 ledger messages claimed a bank that had not happened (a helper no-op on an empty list; a wrong draft dir) — corrected in the next commits; `bank.sh` hardened (R43) | the origin of candidate (ii)/(iv) below |
| R64 | (not in the plan) | the session-start digest written mid-phase at Drew's direction | the protocol's cost had reached ~150k tokens |

## What we believed, what failed, and what we would do sooner (for the retrospective; the detail is in `docs/decision-log.md` P32 S82–S85)

- **Believed (S80/S83):** eight functions were compiler walls with proofs or citations; two more were "PROVED" and "PLATEAU"
  by producer censuses that refuted every known producer. **All ten banked.** The proofs were correct about the mechanism and
  wrong about the list: combine's `i2dest_in_i2src` bookkeeping gap (§501-Q) and loop.c's user-variable rule with cse's
  later-mention canonicalization (§501-R) were not in any census. **Sooner:** treat "PROVED" as "proved against this list",
  name the list, and build the 1-second reproducer battery for every species before probing the 500-instruction function.
- **Believed:** the pins were levers. **They were symptoms** — every `register … __asm__` pin in the S79–S84 drafts of the
  last four functions came off byte-identical once the source SHAPE was right (a sibling's spelling, three inline temps, a
  `u16` accumulator). **Sooner:** remove every pin and re-measure after any structural change (§501-E/P), and read
  `alloc_table.py`'s order before the first pin.
- **Believed:** the atlas's similarity score would name a function's family. **A 0.55 "weak cousin" was the exact
  same-shape sibling** (§501-P). **Sooner:** step 0 of every hand pass greps `src/` for the idiom's literal constants.
- **Cost:** the phase's token spend went overwhelmingly to the last four functions (a 655k-token Fable agent, 3,360-variant
  sweeps, ~100 hand variants) against rows whose answers were a grep (row (d)), one three-statement chain (`func_80032A74`)
  and a shape the reproducer found in eight tries (`func_80039308`). The lesson is the same as P31's: the instrument and the
  census before the subject.

## Commit Message
```
(Phase 32 landed as 111 commits 77df1092e..HEAD, 2026-09-05 → 2026-09-06 (S81–S85). This close = the archived log +
this PhaseEnd + the DIGEST update, Drew's milestone-close commit.)

chore(phase-32): CLOSE — the frontier is empty: 0 stubs across 218 binaries, fleet 100.00 / 100.0 / 100.0, main 2,091/2,091 (v1.31.0)

- PhaseEnd_Phase32.md written; CURRENT_PHASE.md archived to phase-ends/logs/Phase32.md (R19); DIGEST.md §0/§2/§3 appended (step 3b)
- 5 sessions (S81–S85): the parked 5 onboarded (fleet 213 -> 218, UNCLAIMED 0 of 220); 77 functions banked (T1 3, T2c 20,
  T3 39, T4b 13, T4c 2) incl. the §474 PROVED wall, six candidate walls and the two S84 verdicts; every final bank pin-free
- fleet R22 after the last bank: 218 passed / 0 failed (exits 0/0/0); make report 363,214/363,214 · 13,488,497/13,488,497 ·
  5,816,589/5,816,589; main REAL 789 · LINKED 1,256 · VERBATIM 3 · stubs 0 · 143dbb89; verbatim 5==5; wave_exclude 0
- cookbook §496–§501-R (§501-Q the combine self-update ghost slot; §501-R the three-times-read hoisted invariant);
  accelerators (8)–(16); tools payload_base_evidence / ghost_census / agent_drafts_restore / cc1_dumps_tu / alloc_table
- rules: R64 ratified (the session-start digest); candidates (i)–(ix) recorded for Drew
- Roadmap delta: P32 consumed; P33 = verify + public flip + Gen2 exit
- v1.30.0 -> v1.31.0
```

## Rules Added This Phase

**Ratified at gate 1 (2026-09-05):** R44–R63 (the P31 candidates — binding since gate 1; their one-liners are in
`phase-ends/DIGEST.md` §3).

**Ratify at this close (Drew-directed 2026-09-05, operated all phase):**

| Rule | Reason |
|---|---|
| **R64 — The session-start digest.** Session start reads `PROJECT_CONTEXT.md` → `phase-ends/DIGEST.md` → the three most recent `PhaseEnd_*.md` → `CURRENT_PHASE.md`, then replays the 🛑 SESSION CHECKPOINT block VERBATIM into the chat; the protocol costs ≈100k tokens + the checkpoint. Every PhaseEnd appends its synopsis and rules to the digest (P7, step 3b). A checkpoint is written to be replayed: self-sufficient, verbose, every path/command/hash explicit. | The protocol had grown to ~150k tokens (32 PhaseEnds); three S84/S85 sessions started from the digest + the checkpoint alone and resumed without a single question. |

**Candidates recorded in the log, for Drew to accept, modify or reject (P10):**

| Rule | Reason |
|---|---|
| (i) A wall verdict must be PASS-attributed with a dump line (R40 → "exonerate the instrument, then name the pass"). | Six of the seven T4 citations named the wrong pass; the cracks each came from one dump line (§501). |
| (ii) Write "banked" only from the tool's printed success line. | Two S83 ledger messages claimed banks that had not happened (a helper no-op, a wrong draft dir). |
| (iii) Agents write deliverables early. | Every agent lost to a usage limit had to be resumed; the one that had written its draft first banked from the dead run. |
| (iv) A helper must refuse an empty work list (R43 restated). | `bank.sh` built the unchanged tree and exited 0 on an empty function list. |
| (v) A residual gets a PRODUCER CENSUS from the compiler source before a spelling sweep, and "PROVED" means every producer on a NAMED list refuted on the bytes. | §501-M/O were right about their lists; §501-Q/R were the producers missing from them — a verdict must say what it was proved against. |
| (vi) A ledger's tie-break is part of the instrument. | `backlog.py` kept the earliest record at equal closeness — a re-verdict could never render (S84). |
| (vii) When a same-family sibling is banked, port its SPELLING before touching a dial on the draft. | §501-N (`func_800CF408`, first try) and §501-P (`func_80185810`, first try after 3,360 sweep variants). |
| (viii) A similarity score is not a shape oracle — a hand pass opens with a grep for the idiom's literal constants across `src/` and an objdump of each hit's window against the target. | The atlas scored the exact sibling 0.55 (§501-P). |
| (ix) Build the 1-second reproducer battery for a mechanism BEFORE probing the real function, and read the allocation ORDER before any register lever. | §501-Q was found by 18 five-line reproducers after two sessions of real-function probes; §501-R's shape came from an 8-variant reproducer sweep after 40 real-function variants; every pin then came off (accelerators (15)/(16)). |

*(Techniques stay in the cookbook — §496–§501-R — per the Phase-8+ precedent; strategy in `docs/decision-log.md` (R31) and
`docs/accelerators.md`.)*

## PhaseEnd Changelog
**v1.30.0 → v1.31.0 — Phase 32 complete (Gen2 phase 23; the phase that emptied the frontier).** Chartered as a short,
kill-gated close-out of 21 stubs and 5 parked payloads, the phase onboarded the five payloads on their first static-derived
candidates (fleet 213 → 218, disc UNCLAIMED 0 of 220), ran a 47-target one-agent-per-function pass that banked 39, and then
— on Drew's directive that everything short of Sony's objects and the original hand-asm must be C — cracked the remaining
fifteen: eleven by a Fable pass that read pass dumps against the gcc-2.7.2 source, four by hand. The four hand cracks each
overturned a written verdict: a "PROVED" wall (§501-M's census was missing combine's self-update bookkeeping gap, §501-Q), a
PLATEAU (loop.c's user-variable rule and cse's later-mention canonicalization, §501-R), and two rows whose banked siblings'
spellings matched first try (§501-N/P). Every register pin the earlier drafts carried came off byte-identical. The census is
**0 stubs**; the fleet reads **100.00% / 100.0% / 100.0%**; main **2,091 / 2,091** with 1,256 linked PsyQ objects and 3
verbatim bodies (5 fleet-wide); **218 / 218 byte-identical from a clean rebuild after the last bank.** Governance: R44–R63
ratified at gate 1, R64 ratified here, nine candidates recorded; the session-start digest is the new load order.

## Plain-English Recap
This short phase finished the translation. It started with twenty-one functions left and five small disc files nobody had
seen the game load. The five files turned out to be real code modules; we worked out where each one sits in memory from its
own bytes, added them to the checklist (fifty-four functions to go instead of twenty-one), and then cleared the list: first a
batch of AI agents translating one function each with an automatic bit-for-bit referee, then — at Drew's instruction that
nothing but Sony's library code and the original's five hand-written assembly routines may remain untranslated — a final
push on the "impossible" ones. Two of those had formal proofs that they could not be matched. Both proofs were wrong in the
same way: they listed every way the 1995 compiler could produce the odd byte or the odd stack slot, and the list was one item
short. Five-line test programs found the missing behaviours in minutes, and the last two functions then matched with no
tricks at all. Every one of the game's 218 code files rebuilds byte-for-byte from our C source from a clean rebuild; the
project's three progress numbers all read 100%. What remains for the next phase is bookkeeping and the public release:
verifying the whole thing once more end to end, cleaning the repository's history of anything ROM-derived, and opening it.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase32.md` (R19, via `git mv`); `phase-ends/DIGEST.md`
appended (step 3b) — **all three left uncommitted for Drew's milestone-close commit** (R6 gate-2 sign-off). The Phase-32 work
is committed across the sessions (`77df1092e..HEAD`); **Drew commits AND pushes** this PhaseEnd + the archived log + the
digest. The Ghidra MCP (the SessionStart hook's headless server) was stopped cleanly (R23); no DB change to commit — the
`db.*.gbf` churn is restart-noise, do NOT stage it. Gen2 continues — do **NOT** start Phase 33 here. Start a **fresh session**
(effort **Max**, **plan mode**) for **Phase 33 — 100% verification + the public flip + Gen2 exit**, planning from roadmap v2
§3 P33 + `docs/gen2-roadmap.md`'s Phase-14 checklist + this file's Roadmap delta. Keep this file forever.
