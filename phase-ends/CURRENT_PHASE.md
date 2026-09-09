# CURRENT_PHASE — Phase 36: levers off — every compiler-forcing construct out of the matched C (v2.1.0 → v2.2.0)

> **Gate 1 approved by Drew on 2026-09-09 (S97; plan mode at Max; Fable 5.1).** The Gen3 order is Drew's: dedup (P35, closed) →
> **pins** → structs → names. Drew widened the phase at gate 1: *"this phase we also want to remove the asm volatiles and the "r"'s
> and all the other compiler hints/hacks"* — so the unit of work is a **lever site** of any class (register pins, asm statements
> incl. every `"r"`-constraint hack, volatile levers, bare `register`), and the phase's product is a tree with **no register pin and
> no asm statement left** (decision 2: grind to zero), the GTE coprocessor asm consolidated under Sony's names, the byte-needed
> `volatile`/`register` kept as ordinary C and counted, and a self-asserting census as a `tools-health` gate. The approved plan is
> reproduced VERBATIM at the end of this file (§"Approved plan"). **Baseline HEAD at open: `e6d98dd1d`** (Drew's P35 close commit,
> v2.1.0). **R22 obligation:** every batch that touches `src/` is followed by the clean fleet run (218/218) before its commit —
> this phase changes no byte, ever. **Rules ratified at gate 1 by the plan approval: R100–R106** (the PhaseEnd_Phase35 candidates
> (a)–(g); Drew may still veto any of them — say so and the DIGEST entry is amended).

## Milestone (gate 2 — what Drew confirms, each with its literal output)

1. `tools/lever_census.py --check --strict` → **0 register pins, 0 asm statements** outside the one GTE header, the byte-needed
   `volatile`/`register` counted and unmarked, the counts published in `docs/progress.json` / the README block with the dated
   snapshot, the coverage assertion green; `tools/verbatim_check.py --strict` unchanged (the five 1998 routines untouched).
2. The ledger names, for every site, the rung and the instrument that judged it (REMOVED / REWRITTEN / NEEDED-kept / the wave that
   reshaped it) — R65-style attribution.
3. `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `check-all: 218 passed, 0 failed of 218` (R22);
   `make tools-health` OK with the new rung; the GTE macros in one header; no per-TU lever macro definitions.
4. The record (T9) written; PhaseEnd_Phase36.md, the DIGEST append, the log archived (T10); v2.2.0.

## Effort / model (R7/R26/R27 — every transition is PROMPTED, never assumed)

- **Max** for T2 (the probe and its pricing), T3's design, T10 (the PhaseEnd); **xHigh** for T0, T1, T3's finish, T4, T5, T6, T8, T9;
  **low** for T0's bookkeeping. Max is session-only (re-apply each session); xHigh is the highest persistent level.
- **Ultracode ONLY for T7** (the reshaping waves — breadth), and only after Drew's actual `/effort ultracode` toggle (R27); the
  coordinator's own judgment (harvest, toolify, the packs) stays at Max — flip back before each harvest.
- **Drew-only (R6):** every `git push`; the gate-2 confirmation; the milestone-close commit + the `v2.2.0` tag.
- Drafter escalation inside T7 (the model-ladder memory): Opus for exemplars ≤ 150 instructions, Fable above or on a new wall class.

## Tasks (plan order; one commit each; ☐ → ☑ with the verify line quoted in the log)

- ☐ **T0** (S97) — Baseline and the phase file: R22 clean fleet at the open; `.gitignore` P36 evidence allowlist; this file; the harness
  task list (R28, 11 tasks); commit. Verify: `check-all: 218 passed, 0 failed of 218`; `git status` clean after the commit.
- ☐ **T1** — `tools/lever_census.py`: the self-asserting census (derived from `share_census.build_forms()` instance records; every
  `asm|__asm|__asm__` spelling; classes A–G per site; the verbatim manifest excluded; coverage assertion vs the raw regex totals; known
  cases `src/800.c func_800226C0` = 45 pins, `src/shared/ov/func_80178004.h` = 26; `--check` marked/UNMARKED) + `progress.py` `levers`
  block + README sentence + dictionary/SETUP rows. Verify: `lever_census: <N> sites in <B> bodies (<D> distinct) + <F> file-scope —
  coverage OK (<N+F> == <raw>)`; `progress.py --json --readme --check` fresh.
- ☐ **T2** (Max) — The probe: the oracle (recipes via `make -n -W`, replayed to a scratch object, `-MF` to scratch), CALIBRATED (sampled
  TUs untouched → 100 % object equality with `build/`; twin == primary; an altered body → DIFFERS), then rung A + B on ~150 stratified
  distinct bodies; the measured table prices T4–T7 (R41). Verify: the probe table in this log with its command.
- ☐ **T3** (Max design) — `tools/delever.py` + `tools/delever_cycle.sh`: rungs A/B/C, group testing per TU with per-symbol attribution
  and the 2 % per-body control, shared headers greedy-on-one/verify-on-all (h_text on all), the in-memory snapshot + `inflight.json` as
  the only restore, the ledger keyed alias+tu+function+address, refusals, progress logs, negative controls, selftest with decoys.
  Verify: selftest; the calibration line; one batch on one overlay end-to-end with R22 green.
- ☐ **T4** — The mechanical campaign over the whole population (headers → multi-copy classes → singletons), batches < 10 min, R22 every
  2 batches, one commit per batch carrying the census line, the log line and the 🛑 headline. Verify per batch: `delever: batch <k> — <n>
  sites removed / <m> needed in <b> bodies; gated <x>/<x> objects identical`; R22 `218 passed`.
- Rules check (P6) after T4.
- ☐ **T5** — GTE consolidation (one header, PsyQ's names; the `"memory"`-clobber variants are levers → residue, not a second spelling) +
  the dead lever-macro sweep (`SHB` cross-file use counted). Verify: `lever_census` 0 per-TU asm macro definitions; R22 green.
- ☐ **T6** — Rung R (mechanical shape recipes, each negative-controlled) and rung D (the permuter on the residue exemplars, time-boxed,
  16 workers; a score-0 applied through `delever --apply-body` and gated). Verify: `recipes: <k> of <r> NEEDED sites removed`;
  `permuter: <k> of <r> exemplars matched lever-free in <t> h`.
- ☐ **T7** (Ultracode, prompted) — The reshaping waves to zero: wave → harvest → toolify (cookbook + rung R) → sweep → next draw; wave 1
  ≈ 40–60 exemplars reported with yield and tokens per bank (R41); stop rule = residue 0. Rules check (P6) after wave 1 and every fourth
  task thereafter.
- ☐ **T8** — The gate: `// !FAKE:` markers from the ledger mid-campaign; `lever_census --check` in `make tools-health` (0 UNMARKED);
  `--strict` at close (0 pins, 0 asm outside the GTE header, manifest unchanged); `progress.py` final split. Verify: `lever_census --check
  --strict: pins 0, asm 0, volatile-needed <v>, register-needed <r> — OK`; tools-health OK.
- ☐ **T9** — The record (cookbook §, decision log P36, accelerators, SETUP rows, wiki, gen3 snapshots, tool-index, kit corpus,
  `doc_links --strict` 0/0, tools-health OK).
- ☐ **T10** (Max) — Close: R22 218/218; tools-health OK; PhaseEnd_Phase36.md + DIGEST §0/§2/§3 + this log archived (R19) + kit corpus;
  left uncommitted for Drew's close commit; v2.2.0.

## Decisions (owner's words, in order)

- **Gate 1 (2026-09-08/09, S97):** *"this phase we also want to remove the asm volatiles and the "r"'s and all the other compiler
  hints/hacks."* → the scope widened from pins to every lever class (the plan's classes A–D).
- **Scope question:** Drew chose *"A–D now, GTE consolidated"* — classes E (asm-label aliases), F (`__builtin_*`), G (`__attribute__`)
  are DEFERRED to the structs/types phase, where the canonical declaration layer (R95) removes their reason to exist.
- **Residue question:** Drew chose *"Grind to zero"* — waves continue until no register pin and no asm statement remains, regardless of
  token cost; the phase does not close with a residue. `// !FAKE:` is the MID-campaign honesty marker only.
- **Marking question:** Drew chose *"Keep unmarked, ledgered"* — a byte-needed `volatile` or bare `register` stays as ordinary C
  (1990s code used both), recorded in the ledger and the published count; `!FAKE` goes only on a surviving pin/asm statement.
- *"just to confirm we aren't including the hand crafted asm code from 1998 right?"* → **confirmed NOT in scope:** the five
  hand-written assembly routines in `config/verbatim_manifest.json` (PERMANENT) are the original's code; the census excludes them by
  the manifest and `verbatim_check --strict` stays green. The 1,256 Sony objects are linked, not source. The GTE coprocessor ops are
  Sony's own inline-asm idiom and are kept under the SDK's names.

## Rules at gate 1 (P10)

**R100–R106 ratified by the plan approval (2026-09-09; the PhaseEnd_Phase35 candidates (a)–(g), operated through P35):**
R100 a shared body has exactly one source; a duplicate copy is a defect the health chain asserts, its count published with its rule ·
R101 every commit that advances a task — an intra-task bank included — carries its log line and the 🛑 headline; a checkpoint older
than HEAD is a dead session's checkpoint · R102 a tool that restores files restores from its own snapshot, never `git checkout` on a
tree it did not commit · R103 a failure-cause extractor is negative-controlled against the compiler's real message forms, not the word
"error" · R104 build the disagreeing oracle before the batch runs, and measure its disagreement before believing either side ·
R105 a registry lists a member only after the gate has spoken for it; a listed member whose site does not share is a defect the check
names · R106 a policy taken on a remembered precedent is a belief — read the target project's tree. **Candidates for Phase 37 gate 1
accumulate here as the phase produces them.**

## Log (append-only; one entry per step, with the literal verify line)

- **S97 2026-09-09 — session start.** Session-start protocol at low effort, then Drew: `/effort max` + plan mode. Reconnaissance: two
  Explore agents (pin tooling + the P32 recipes; the gate machinery), one Plan agent (the tool/oracle design, 257k tokens), my own
  census (the numbers in the plan's population table) and two read-only probes: `make -n -W <src> <obj> BINARY=<alias>` prints the
  exact per-object recipe in 0.04–0.06 s (main carries `jtbl_rodata_pads.py --derive main --tu <tu>`; a twin compiles the primary's
  source into its own object); `tools/compile_only.py` omits the pad stage and is NOT a faithful oracle. Three AskUserQuestion forks
  answered (the decisions above). Plan approved (ExitPlanMode); harness tasks #1–#11 created (R28).
- **S97 — T0 baseline.** `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `extract-all: 217 extracted, 0 failed of
  217 (+ main, serial)` · **`check-all: 218 passed, 0 failed of 218`** · `wall=88.46 s user=1384.22 s sys=197.47 s` · `exit=0`
  (`.run/P36/baseline/r22_t0.log`). Tree clean at `e6d98dd1d` before the run. Headless Ghidra MCP running (2 GB; no RE work planned —
  stop it via the sentinel at any checkpoint commit, R23). Memory 31 GB (29 available), disk 32 GB free.
- **S97 — Plan-agent findings carried into T2/T3 (recorded here so a fresh session has them):** (1) a per-candidate `make <obj>` would
  overwrite the baseline object and `.d` in `build/` — extract the recipe once per object (`make -n -W`), replay it with `-o` to scratch
  and `-MF` to scratch; (2) objects embed the source path as an `STT_FILE` symbol (`readelf -s build/src/800_c.o` → `FILE … src/800_c.c`,
  from cpp's first line marker) — compile IN PLACE at the real path (in-memory snapshot restore) or rewrite the marker if a probe file is
  used; (3) ~208 pins use the `asm("$4")` spelling that `PIN_RE` and the gate-1 grep miss (e.g. `src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c:3056`);
  (4) the file-scope `extern volatile` class is ~526 + 3 (the gate-1 8,262 counted the `volatile` token inside GTE macro definitions);
  (5) the agent's census: 15,430 lever bodies, 47,766 sites, 2,557 TUs + 353 shared headers, sites per body median 2 / p99 20 / max 45;
  (6) 330 asm-bearing macro names, mostly PsyQ's `inline_c.h` names already (`gte_ldv0` 839 defs / 9 texts; a 171-definition variant
  carries a byte-relevant `"memory"` clobber) plus address-suffixed private copies; `SHB` 416 defs / 2 texts; `ENGINE_SHB` 8 uses; one
  shared header (`src/shared/ov/func_80166F58__3728db8a.h`) uses the INCLUDER's `SHB`; (7) rung A can be group-tested per TU (strip every
  lever body at once, one compile, attribute per symbol with `masked_diff.insns_from_object`) with a 2 % per-body control (R34); rung B
  batched across a TU's failing bodies; (8) `!FAKE` reason codes: SCHED-ANTIDEP (§373/§3-2), CSE-REMAT (§153/§176-D1), CROSSJUMP-FENCE
  (§336), ARGCOPY-ADDU (§194-E), BLOCKCOPY-EXPAND (§176-D2), UNCLASSIFIED; (9) refuse: file-scope `register`, a pin declarator with a
  function-pointer `(`, a live `#if` inside a body, copies that disagree, a header whose registry and census includers differ, h_text
  includers disagreeing; (10) dotfile probes must be swept before any `make` (the P32 S83 precedent).

## 🛑 SESSION CHECKPOINT — S97 (2026-09-09): gate 1 approved; T0 in progress (R22 green, .gitignore + this file written, commit pending); NEXT = T0's commit, then T1 (`tools/lever_census.py`) at xHigh

### 0. How to use this block
A fresh session reads CLAUDE.md's load order, replays this block verbatim, asks Drew for `/effort xhigh` (T1) — Max only for T2/T3-design/T10 —
and executes §2. The tree is clean at **HEAD `e6d98dd1d`** plus this phase's T0 files until the T0 commit lands. Drew pushes (R6).

### 1. Where things stand
- **Done:** gate 1 (plan approved 2026-09-09, the decisions above); R22 at the open **218/218** (`.run/P36/baseline/r22_t0.log`); `.gitignore`
  P36 block; this file; harness tasks #1–#11.
- **Open:** everything from T1 on. No `src/` edit has been made. No tool exists yet (`tools/lever_census.py`, `tools/delever.py`,
  `tools/delever_cycle.sh` are T1/T3 deliverables).
- **Environment:** WSL2, `~/bfm-decomp`, `.venv`; fleet clean run ≈ 90 s; headless Ghidra MCP up but unused (stop it with the sentinel
  before a checkpoint commit, R23); 16 cores; 31 GB RAM; 32 GB disk free (the WSL disk is capped at 75 GB — `.run/` churn can hit ENOSPC).

### 2. T0's commit, then T1
1. `git add .gitignore phase-ends/CURRENT_PHASE.md .run/P36/baseline/r22_t0.log && git commit -m "phase-36: T0 — baseline (R22 218/218 in 88 s), the P36 evidence allowlist, CURRENT_PHASE.md from the approved plan (levers off: pins + asm statements + volatile + register, GTE consolidated, grind to zero; R100–R106 ratified)"`.
2. T1 (xHigh): build `tools/lever_census.py` per the task text above; its parser must accept `asm|__asm|__asm__` and be comment/string
   aware (`share_census.mask_text`); derive bodies from `share_census.build_forms()` + `classify(keep_instances=True)`; exclude the
   verbatim manifest; assert coverage against the raw regex totals; then wire `progress.py` (`levers` block in `counts`, README
   sentence, a dated `corrections` entry), the `config/tool_dictionary.tsv` row (eight columns; tools-health fails without it) and the
   SETUP row; run `make report BINARY=main` and `progress.py --json --readme --check`; commit with the census line.

### 3. Numbers to re-derive, never trust
The gate-1 population table (grep-derived): pins 40,346 (+~208 `asm(` spellings), asm statements ~20k in bodies, volatile ~3.1k in
bodies + ~529 file-scope, bare register 290, union ~19,500 bodies / ~2,534 distinct; the plan agent's independent 15,430 bodies /
47,766 sites. T1's census is the number the phase publishes.

### 4. Gotchas known before any work
The oracle must not write `build/` (baseline objects); objects embed the source path; `compile_only.py` is not faithful; dotfile
probes are swept before `make`; a shared header's edit reaches up to 136 binaries — verify every includer; h_text headers compile
differently per binary — greedy on all includers; `SHB` may be used by an included header; never `git checkout` to restore (R102).

## Approved plan (verbatim, gate 1 — 2026-09-09)

# Phase 36 — levers off: every compiler-forcing construct out of the matched C (v2.1.0 → v2.2.0) — gate-1 plan

> Gate 1, 2026-09-09, plan mode at Max (Tier 1). Owner decisions recorded below. On approval: T0 writes this plan verbatim into
> `phase-ends/CURRENT_PHASE.md`, builds the harness task list (R28), and execution is one task at a time (P3–P5). The Plan agent's
> stress-test of the tool internals (parsing, includer enumeration, failure modes) lands in T3's design notes when it reports.

## Context

Gen3's order is Drew's: dedup (Phase 35, closed) → **pins** → structs → names. The Gen3 charter (`docs/gen3-standards.md` §2 rule 2,
§4 step 1; `docs/gen3-handoff.md` §2 item 2) says every `register … __asm__("$N")` pin goes, or stays marked `// !FAKE:` with its
reason, and the count is a published metric until it is 0. Drew widened the phase at gate 1 (2026-09-08): *"this phase we also
want to remove the asm volatiles and the "r"'s and all the other compiler hints/hacks."* So the unit of work is a **lever site**
— any construct that exists only to force the compiler's output — of any class, and the phase's product is a tree in which every
such site is either gone (bytes unchanged) or kept with an honest marker, with a self-asserting census as a health-chain gate.

Why now and not later: levers are the community's second gripe with machine decomps ("matches that are bytes without
understanding"); the struct and naming phases are easier on lever-free bodies; and Phase 32 proved the pins were symptoms of
source shape (§501-E/P/R, R73) — every one on the last four functions came off byte-identical once the shape was right. The
project's own §501-E, though, replaced pins with launders (`__asm__("" : "=r"(x) : "0"(x))`): that recipe is now out of bounds —
one lever for another is not removal.

Nothing in this phase changes a byte: the 218 hashes from a clean rebuild gate every batch (R22), exactly as a match was gated.

## The population, measured 2026-09-08 (my grep/scan census at gate 1 — T1 re-derives with a self-asserting tool, R32/R37)

| Class | What | Sites | Bodies | Distinct bodies (addresses normalized) | Notes |
|---|---|---|---|---|---|
| **A** register pins | `register T x __asm__("$N");` | 40,346 (37,493 in bodies) | 13,158 | 1,808 | ~13% carry initializers; `volatile`/pointer qualifiers appear; **1,501 pin `$0`** (a `zr` zero-register variable — a semantic device, not an allocation hint); 13 pin `$29`; 43 bare names (`"a0"`); only function-local (never a parameter, never file scope), sometimes at column 0, sometimes inside a `{}` opened only to host the pin |
| **B** asm statements | `__asm__ [__volatile__](…)` | ~20,000 in bodies | 19,240 (union with A) | 2,415 | B1 barriers `("")`, `("" ::: "memory")` (~4,800); B2 launders `("" : "=r"(x) : "0"(x))` (~4,100, incl. the per-TU `SHB(x)` macro defined 416 times and `ENGINE_SHB` in `engine_prelude.h`); B3 keep-alives `("" : : "r"(x))` (~2,150); **B4 hand-placed instructions** `"addu %0,%1,$zero"` 1,238, `"move"` 407, `"la"` 147, `"lh"` 134, `"addiu"`/`"sll"`/… (~1,950); **B5 GTE coprocessor ops** `lwc2/swc2/mtc2/cfc2/mfc2/rtps…` behind ~90 per-TU macro names (`LDV0_DA34`, `RTPS221A8`, …) — legitimate coprocessor code, to be consolidated, not removed |
| **C** volatile levers | `*(volatile T *)(p+off)`, `volatile T x;` locals, `extern volatile T D_…;` at file scope | 3,131 in bodies + 8,262 file-scope declarations | 1,245 | 240 | none at hardware addresses (0x1F80…/0xBF80…): the game's I/O goes through the SDK; these are reload-forcing levers on RAM |
| **D** bare `register` | `register T x;` (no asm) | 290 | 172 | 119 | at -O2 gcc 2.7.2 should ignore it (`obey_regdecls` = 0) — the oracle decides |
| **Union A–D** | | ~61,000 sites | **19,500** | **2,534** | 491 multi-copy classes hold 17,457 of the 19,500 bodies (identical text modulo `func_/D_` addresses across overlays — the Phase-35 "deferred cross-address classes"); by kind: ov 18,686 · shared headers 412 · md 201 · main 185 · resident 16; **0 pins in `-O0` TUs** |
| E asm-label aliases | `extern u16 aD800B9A02 __asm__("D_800B9A02");` `… __asm__("func_80137030")`, `__asm__("GsSortLine")`, `__asm__("memcpy")` (1,285) | 8,331 (6,196 file-scope) | — | ~100 | declaration-environment dodges (a second typed view of one symbol; a non-builtin name for `memcpy`) — the canonical type layer (R95, the structs phase) removes their reason |
| F builtins | `__builtin_memcpy` 302, `__builtin_abs` 297 | 599 | 428 | 33 | `__builtin_memcpy(&a,&b,N)` is a struct assignment in disguise (needs the struct type); `__builtin_abs` → `abs` is a spelling |
| G attributes | `__attribute__((packed))` 64, `((aligned))` 12 | 76 | — | — | type layer |

Commands (re-derive; the census tool replaces them): `grep -rhoE 'register [^;/]*__asm__\("\$?[a-z0-9]+"\)' src --include=*.c --include=*.h | wc -l`;
`grep -rhoE '\b(__asm__|asm)\s*(__volatile__|volatile)\s*\(' … | wc -l`; the body-level numbers came from a comment-stripped scan
that finds function bodies by a column-0 header + a column-0 `}` and hashes each body with `func_/D_` addresses normalized.

## The oracle and the invariant

- **Inner oracle (per candidate edit, ~0.3–1 s):** compile the ONE affected translation unit in place through the Makefile's own
  rule — `make build/src/<alias>/<tu>.o BINARY=<alias>` (main: `build/src/<tu>.o`; a twin: the primary's source into the twin's own
  object) — and compare the object's bytes with the baseline object from the fleet run. Measured at gate 1: make's parse overhead
  is **0.04–0.06 s** (`make -n -W src/… <obj> BINARY=…`), so the rule is invoked per candidate, faithful by construction (R57): it
  carries the per-object `-O0` overrides, the `jtbl_rodata_pads.py --derive main --tu <tu>` stage for main/module TUs, the reorder
  island, the `-MMD` dependency tracking. `tools/compile_only.py`'s re-typed pipeline is NOT faithful (it omits the pad stage) and is
  not used. Parallelism = many `make <obj>` invocations at once on DIFFERENT objects (workers own whole TUs; the twin's object is
  a second target of the same source). Calibration before any verdict (R39/R56/R57): the tree's `build/` must come from the T0
  fleet run; every sampled TU compiled untouched reproduces its object byte for byte; a deliberately altered body reports DIFFERS.
- **Outer gate (per batch, ≈90 s):** `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `check-all: 218 passed,
  0 failed of 218`, read by exit code with `pipefail` (R22, R97); commit the moment it is green (R42), with the log line and the
  🛑 headline in the same commit (P35 candidate (b)).
- Shared headers (`src/shared/**/*.h`): the greedy search runs on ONE includer TU, the decided edit is verified on EVERY includer
  (registry members via `dedup_integrate.group_members` + the `#include` sites); the twins build the primary's sources into
  their own objects (Makefile twin block) — both objects compared.
- A twin's pair, an `h_text` header (38, byte-variant per binary), a `-O0` TU: each is gated like any other, on its own objects.

## The ladder (deterministic first; tokens last)

| Rung | What | Cost | Who |
|---|---|---|---|
| **A strip-all** | remove every lever in the body (per-class rewrite: pin → plain declaration keeping type/qualifiers/initializer; barrier/launder/keep-alive → statement deleted; `SHB`/`ENGINE_SHB` use → deleted; B4 instruction → its C equivalent (`addu…$zero`/`move` → assignment, `la` → `&sym`, `lh` → the load, else residue); `$0` pin → uses of the zero variable replaced by `0`; `volatile` → qualifier dropped; `register` → keyword dropped; GTE op → the one canonical macro name), compile, compare | 1 compile | tool |
| **B greedy** | if A differs: re-add sites one at a time to find a minimal needed set (order: asm statements, pins, volatile, register), then confirm the set | ≤ sites+1 compiles | tool |
| **C exemplar/replay** | for a multi-copy class the search runs on the exemplar; the decided edit is replayed to each copy by pattern and each copy verified with one compile; a copy that disagrees gets its own greedy pass and is recorded as a disagreement | 1 compile per copy | tool |
| **R recipes** | for each NEEDED site, try the byte-neutral shape recipes the cookbook already holds, mechanically (a fresh single-set temp at the use §501-P; the inline-expression-thrice / `u16` accumulator §501-R; declaration-scope moves §76; branch-polarity flip T4; the explicit temp before a call §17a; `zr` → the `0` constant with the copy-arm rewrite for the `$0` class) — each a few compiles; **the rung grows after every wave (the harvest → toolify step)** | compiles only | tool |
| **D permuter** | the residue (bodies that keep ≥1 pin/asm site): `tools/permuter/run_masked.py` + `permuter_ils.py` on the lever-free body against the target bytes (`permuter_weights.py` REGALLOC/SCHED profiles), time-budgeted, parallel — the randomizer's dials (temps, reorders, types) are exactly what replaces a lever; a score-0 is a candidate, the object oracle and the fleet gate bank it | minutes per body, zero tokens | tool |
| **E agents** | what D leaves: one agent per class exemplar with the P32 brief (§501-P/R, `alloc_table.py` + `cc1_dumps_tu.sh` — read the allocation order first, R73; the 1-second reproducer battery; port a lever-free sibling's spelling first, R71; no lever of any class may remain); deliverables written early (R67); the tool is the judge; copies replayed. **Waves repeat, with the harvest → toolify step between them, until the residue is 0 (Drew's decision 2)** | tokens | agents (Ultracode, prompted R26/R27) |
| **F mark (mid-campaign)** | after every batch, every pin/asm site that survives carries `// !FAKE: <class> — <what it forces: the register/pass, from the ledger>`; the census asserts 0 UNMARKED at every commit and **0 sites of A and B at the close** | 0 | tool |

**Residue classes the record already names (the wave packs cite them; rung R and the permuter profiles are seeded from them):**
a pin that deletes a sched2 anti-dependence (§373 ★★★, §3-2 — "an `asm` can never raise priority"), the caller-saved pin that is a
correctness bug (§175) and the one that cannot schedule around a call (§176-C, a gcc-2.7.2 bug), the chained assignment as a
scheduling dial (§205), the `$0` zero-register variable (a copy-arm device), the launder as a `qty_compare` steer (§501-E — the
recipe now forbidden as a replacement), and the hand-placed `addu/move/la/lh` instructions (B4), whose C spelling must reproduce a
copy, an address materialization or a load the compiler folded away in the draft's shape.

## Tasks (plan order; one commit each; ☐ → ☑ with the verify line quoted in the log)

- **T0 — Baseline and the phase file** (xHigh; low for the bookkeeping). R22 clean fleet at the open (`218 passed, 0 failed of 218`, log
  `.run/P36/baseline/r22_t0.log`); `.gitignore` P36 evidence allowlist (`.run/P36/{baseline,census,probe,delever,permuter,waves}/` text
  only, by-contents form R84); `phase-ends/CURRENT_PHASE.md` from this plan (milestone, effort, tasks, decisions, log, the approved plan
  verbatim); harness task list (R28). Verify: the R22 line; `git status` clean after the commit.
- **T1 — The lever census `tools/lever_census.py`** (xHigh). Derived from `share_census.build_forms()`'s instance records (every function
  instance's TU, span, alias, twin, class — R33), a comment- and string-aware site parser (reuse `p16_permute.hide_asm`'s keyword
  pattern and `share_census`'s masked-text approach), per-site class A–G, register, initializer, block-host, exemplar/copy structure
  (the Phase-35 normalized-text classes), file-scope sites (macro definitions, `extern volatile`, asm-labels) attributed to their TU;
  **coverage assertion (R32):** sites found in bodies + outside == the raw regex totals over the tree, else FAIL; checked against a
  known case (e.g. `src/800.c func_800226C0` = 45 pins; `src/shared/ov/func_80178004.h` = 26); `--check` mode with a `!FAKE`-marked
  vs UNMARKED split; JSON/txt under `.run/P36/census/`. `tools/progress.py` publishes `levers` {by class: sites, bodies, distinct,
  marked, unmarked} + a `corrections`-style dated snapshot + a README sentence (R75). Tool dictionary row (R87) + SETUP row (R21).
  Verify: `lever_census: <N> sites in <B> bodies (<D> distinct) + <F> file-scope — coverage OK (<N+F> == <raw>)`; `progress.py --check` fresh.
- **T2 — The probe (R37)** (Max). The inner oracle built and CALIBRATED first (every TU of two overlays + main compiled untouched → 100%
  object equality with `build/`; an altered body → DIFFERS); then rung A + B on a stratified sample of ~150 distinct bodies (by class mix,
  pins-per-body, kind: shared header / overlay / main / resident / module, the `$0` class, initializer pins, B4 instructions, volatile
  globals). Measured: % identical after strip-all (with `register` dropped vs kept), % after greedy, the residue's class mix, seconds per
  compile, compiles per body. **Prices T4–T7 with denominators (R41)** and fixes the rewrite table. Evidence `.run/P36/probe/`. Verify:
  the probe table in the log with its command.
- **T3 — The tool `tools/delever.py`** (Max for the design; xHigh to finish). Rungs A/B/C, the oracle, `--plan / --apply --class … --only
  <class-hash|tu> --batch N --batches 1 --label`, workers own whole TUs (no two workers touch one TU; shared headers partitioned by
  includer set), the in-memory text snapshot as the ONLY restore (never `git checkout`, P35 candidate (c)), the ledger
  `.run/P36/delever/ledger.jsonl` keyed by alias+tu+function+address (R48) with per-site verdicts REMOVED / REWRITTEN(rule) /
  NEEDED(class, register) / REFUSED(reason), refusals for anything it cannot parse or a body whose copies disagree (R43), progress
  logs (R55), the negative controls run at start (R39). `tools/delever_cycle.sh` = batch → exit code → log entry → commit → R22 every N
  batches (the `share_body_cycle.sh` pattern). Verify: selftest fixture (every class, both verdicts); the calibration line; one batch
  end-to-end on one overlay with R22 green.
- **T4 — The mechanical campaign** (xHigh; unattended cycles). Rungs A–C over the whole population, largest reach first (shared headers,
  then the 491 multi-copy classes by copies, then singletons), batches sized to < 10 min, R22 every 2 batches, one commit per batch with
  the census line in the message and the log; the published count falls with each commit. Rules check (P6) after T4. Verify: per batch
  `delever: batch <k> — <n> sites removed / <m> needed in <b> bodies; gated <x>/<x> objects identical`; R22 `218 passed`.
- **T5 — The GTE consolidation and the dead-macro sweep** (xHigh). One project header (`include/gte_inline.h` or under `src/shared/`)
  carrying the coprocessor macros under PsyQ's standard names (`gte_ldv0`, `gte_rtps`, `gte_stsxy`, …; bodies proven identical to the
  per-TU variants), every per-TU GTE macro definition and the now-unused `SHB`/launder macros deleted; byte-gated like any batch.
  Verify: `lever_census` reports 0 per-TU asm macro definitions; R22 green.
- **T6 — The recipe rung and the permuter rung** (xHigh). (a) `delever`'s rung R: the cookbook's byte-neutral shape recipes as
  mechanical rewrites tried per NEEDED site (the list in the ladder; each recipe negative-controlled on a body it must not change).
  (b) The residue's exemplars through `tools/permuter/run_masked.py` / `permuter_ils.py` seeded with the lever-free body (pins hidden
  no more — the seed has none), the target bytes from the baseline object, `permuter_weights.py`'s class profile, a time budget per
  body, 16 workers; a score-0 is applied through `delever --apply-body` and gated (object oracle, then the fleet). Verify: the two
  yield lines with denominators (`recipes: <k> of <r> NEEDED sites removed`; `permuter: <k> of <r> exemplars matched lever-free in <t> h`).
- **T7 — The reshaping waves, to zero** (Ultracode — prompted; the coordinator stays at Max). Rules check (P6) after wave 1 and every
  fourth task thereafter. Each wave: the residue's exemplars family-batched (`draw`-style: largest copy count first, one member per
  class), one agent per exemplar with the pack — the body, the target listing (`verbatim_target_s.py`), the ledger's NEEDED sites (which
  register/pass), `alloc_table.py` on the real TU (`cc1_dumps_tu.sh`), the §501-E/P/R and §17 counter-recipes, `journal_notes` for that
  function, the rule "no lever of any class may remain", deliverable-first (R67); `delever` judges every draft on the bytes and replays
  the copies; then the **harvest → toolify gate before the next wave**: every idiom banked into the cookbook AND, where mechanical, into
  rung R, then a sweep of the residue with the grown rung (free banks), then the next draw. **Wave 1 is ~40–60 exemplars and reports
  yield and tokens per bank with denominators (R41) — Drew's decision 2 sets the stop rule at 0, the report sets the wave shape.**
  Escalation per exemplar: Opus ≤150 instructions, Fable above or on a new wall class (the model ladder memory).
- **T8 — The gate: `!FAKE` mid-campaign, zero at close** (xHigh). From the first batch on, every surviving pin/asm site carries its
  marker from the ledger (`// !FAKE: pin $16 — without it gcc allocates <var> to $17 (global.c order)`; `// !FAKE: barrier — …`) and
  `lever_census --check` asserts 0 UNMARKED in `make tools-health` (before `report`, next to `share_census --check`); at the close the
  same check runs `--strict`: 0 pins, 0 asm statements outside the GTE header, the verbatim manifest unchanged; `progress.py` publishes
  the final split (needed `volatile`/`register` kept, counted, unmarked). Verify: `lever_census --check --strict: pins 0, asm 0,
  volatile-needed <v>, register-needed <r> — OK`; tools-health OK.
- **T9 — The record** (xHigh). Cookbook § (the ladder, the measured "a bare `register` is byte-neutral at -O2: N/N", every new idiom the
  waves produced), decision log P36 (R31), accelerators, SETUP rows, the wiki (`Where-the-project-goes-next`, `Verification-and-progress`,
  `The-matching-workflow` or a new "Levers off" page), `gen3-standards.md` §4 + `gen3-handoff.md` dated snapshots, `docs/tool-index.md`
  and the kit corpus regenerated, `doc_links --strict` 0/0, `make tools-health` OK.
- **T10 — Close** (Max; fresh session or Drew's call). R22 218/218 from clean; tools-health OK; PhaseEnd_Phase36.md + DIGEST §0/§2/§3 +
  the log archived (R19) + kit corpus; left uncommitted for Drew's close commit (R6); v2.2.0.

## Milestone (gate 2 — what Drew confirms, each with its literal output)

1. `tools/lever_census.py --check --strict` → **0 register pins, 0 asm statements** outside the one GTE header (Drew's decision 2:
   no residue), the byte-needed `volatile`/`register` counted and unmarked (decision 3), the counts published in `docs/progress.json` /
   the README block with the dated snapshot, and the census's coverage assertion green; `verbatim_check --strict` unchanged (the five
   1998 routines untouched).
2. The ledger names, for every site, the rung and the instrument that judged it (REMOVED / REWRITTEN / NEEDED-kept / the wave that
   reshaped it) — R65-style attribution, so a reader can see why each survivor of classes C–D stayed.
3. `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `check-all: 218 passed, 0 failed of 218` (R22), `make tools-health`
   OK with the new rung; the GTE macros in one header; no per-TU lever macro definitions.
4. The record (T9) written; this PhaseEnd, the DIGEST append, the log archived (T10); v2.2.0.

## Rules at gate 1 (P10) — Drew accepts, modifies or rejects

PhaseEnd_Phase35's candidates (a)–(g), operated through P35, proposed for ratification as **R100–R106**: (a) one source per shared
body, a duplicate is a defect the health chain asserts; (b) every task-advancing commit carries its log line and the 🛑 headline; (c) a
tool restores from its own snapshot, never `git checkout`; (d) a failure-cause extractor is negative-controlled against the compiler's
real message forms; (e) build the disagreeing oracle before the batch runs; (f) a registry lists a member only after the gate spoke; (g) a
policy on a remembered precedent is a belief — read the tree.

## Effort / sessions / budget (R41)

Effort per task above (R7): Max for T2, T3's design, T10; xHigh for the rest; Ultracode only for T7 and only after the `/effort`
toggle (R27). Sessions: T0–T3 one; T4–T5 one (compute-bound, unattended cycles: ~80k compiles ≈ 1 h on 16 cores is the ceiling
before exemplar/replay savings); T6 background hours; T8–T10 one. **T7 is open-ended by decision 2 (to zero):** its length is the
residue after T6 divided by the per-wave yield, neither known until T2 and wave 1 measure them — the T2 report prices it with
denominators (distinct residue exemplars × measured tokens per bank), and every wave's close re-prices. Mechanical floor 3 sessions;
the campaign is the unknown. P35 was priced 7–8 sessions and took 3.

## Evidence and docs

`.run/P36/baseline/` (R22 + tools-health logs) · `census/` (json/txt) · `probe/` (calibration + the sample table) · `delever/`
(ledger.jsonl, batch logs) · `permuter/` (per-body outcome) · `waves/` (packs, verdicts). Text only, nothing ROM-derived (R74).

## Deferred by name (recorded, not owed this phase)

Class E asm-label aliases, `__builtin_memcpy` (struct assignment), `__attribute__((packed/aligned))` → the structs/types phase (R95);
stale prose comments that describe a removed lever → the formatting/comments phase (the tool lists them); the 3,801 cross-address
classes' parameterized form → the names phase; the kit split, xsig v2 (unchanged).

## Owner decisions at gate 1 (Drew, 2026-09-09, in order)

1. **Scope: classes A–D now; GTE consolidated, not removed; E/F/G deferred to the structs/types phase.**
2. **Residue: grind to zero.** Waves continue until no register pin and no asm statement remains, regardless of token cost; the
   phase does not close with a residue. `// !FAKE:` is therefore the MID-campaign honesty marker (every commit leaves the tree honest),
   not an end state for classes A and B.
3. **A byte-needed `volatile` or bare `register` stays as ordinary C, unmarked, ledgered and counted** (the original plausibly had it);
   `!FAKE` goes only on a surviving pin or asm statement while the campaign runs.
4. **Not in scope, confirmed:** the five hand-written 1998 assembly routines (`config/verbatim_manifest.json`, PERMANENT) are the
   original's code, not levers — the census excludes them by the manifest and `verbatim_check --strict` stays green; the 1,256 Sony
   objects are linked, not source; the GTE coprocessor ops are Sony's own inline-asm idiom and are kept under the SDK's names.
