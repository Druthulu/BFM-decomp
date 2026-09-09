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

- ☑ **T0** (S97, commit `63b886626`) — Baseline and the phase file: R22 clean fleet at the open `check-all: 218 passed, 0 failed of 218`
  (88 s); `.gitignore` P36 evidence allowlist; this file; the harness task list (R28, 11 tasks); `git status` clean after the commit.
- ☑ **T1** (S97) — `tools/lever_census.py`: `lever_census: 218 binaries · 4,121 TUs + 3,181 headers · coverage OK · unclassified 0 ·
  verbatim excluded 5 fn / 5 sites (manifest 5)`; controls 4/4 exact; **THE PHASE'S NUMBER: 53,221 sites (37,720 register pins +
  15,501 asm statements) in 15,666 bodies (2,214 distinct)**; `progress.py --json --readme --check` fresh (the `levers` block + the
  README sentence); `make report BINARY=main` OK (226 s); dictionary + SETUP rows; kit corpus regenerated. The finding of the task —
  23 whole-body assembly routines inside C shells, outside the manifest — is in the log and the decisions section (Drew's call).
- ☑ **T1b** (S97; added on Drew's confirmation, P5d) — The verbatim manifest learns the in-function form: 23 rows (`binary: "ov_*"`,
  `form: "in-function"`; 22 PERMANENT-VERBATIM trampolines + `func_80184440` DECOMPILE-NOW); `tools/verbatim_check.py` detects the form
  structurally through `lever_census.whole_body_asm_functions` (.c and `src/shared/**/*.h`) with wildcard matching — `--strict` green;
  the census defers the exclusion to the manifest (`asm-body` → `verbatim-body` only when PERMANENT): **the phase's number is 53,222 sites
  in 15,667 bodies (2,215 distinct)** (+1: the DECOMPILE-NOW body is a lever); `progress.py` counts PERMANENT rows (27) with a dated
  `corrections` entry; README prose + wiki Home + Where-next + gen3-standards + gen3-handoff updated as dated snapshots; `progress.py
  --json --readme --check` fresh; `doc_links --strict` green.
- ☑ **T2** (S97) — The probe. `tools/delever_oracle.py`: 4,284 recipes captured in 14 s; `--calibrate ov_SC04_011 ov_SC03_015 ov_SC03_014
  main`: **177/177 objects byte-identical untouched; twin checks 32 (0 mismatch); positive control DIFFERS on build/src/800.o — OK**
  (main 0.079 s per object mean, 0.77 s for `800.o`; overlays ~0.14 s). `tools/delever.py --probe --sample 300 --seed 11 -j 12`: **285
  distinct bodies sampled, 283 judged, 1,660 compiles, 151 s wall; rung A identical 53/283; lever-free after rung B 53/283; sites 1,309
  usable → removed 561 (42.9 %), needed 748 (57.1 %)**; the table is in the log entry below and in `.run/P36/probe/probe_table.md`.
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
- ☑ **T6** — Rung R (mechanical shape recipes, each negative-controlled) and rung D (the permuter on the residue exemplars, time-boxed,
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
- **T1 finding → Drew (2026-09-09): *"confirmed per your recommendations."*** → **T1b added (P5d):** the manifest extended with the
  in-function form; `verbatim_check` taught the form; the README count regenerated (5 → 27 PERMANENT; the 23rd routine,
  `func_80184440`, is `-O0` compiler output — frame-pointer prologue around two global stores — and is listed DECOMPILE-NOW, a Phase-36
  residue counted as a lever). The 20 per-overlay trampoline families (133 private copies each, bytes varying with the wrapped callee)
  are the names phase's parameterized-form inheritance.

- **S98 (2026-09-09), Drew, mid-T3:** *"dont start ultra code wave for reshaping without my direct approval."* → **T7's reshaping waves (Ultracode) start ONLY on Drew's direct approval in the session that would run them** — the R27 toggle is necessary, not sufficient; the T6 recipe/permuter rungs and the mechanical campaign are not waves and proceed under P3.

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

- **S97 — T1 the lever census (`tools/lever_census.py`, 720 lines).** Derived from `share_census.scan_text`'s masked-text defs; a token walk
  in which every `asm|__asm|__asm__` / `register` / `volatile` / `__builtin_*` / `__attribute__` token receives one role; coverage per
  line against the RAW text; asm-bearing macro names harvested from every `#define` first (so `SHB(x)` / `gte_ldv0(...)` uses are classed by
  what they expand to); string-literal tokens roled "string"; the manifest's five bodies matched by every `.globl`/`.ent` name of a
  file-scope block (one block defines a data label THEN the routine — the first name is not enough; and `\t` in C string text is two
  characters, not whitespace). Fixture selftest `OK — 23 sites, 2 defs, 2 asm macros` (decoys: a comment with a pin, `asm(` inside an
  INCLUDE_ASM path string, an `#if 0` pin, a multi-line GTE define, a `!FAKE`-marked pin and barrier). Fleet run 32 s at -j16.
  **Coverage (R32):** asm raw 80,396 = live 66,415 + macro-block 7,189 + comment/dead 6,792 · register 46,408 = 37,806 + 18 + 8,584 ·
  volatile 14,000 = 4,883 + 6,510 + 2,607 · builtin 599 = 445 + 0 + 154 · attribute 76 = 76 + 0 + 0; unclassified 0. **Controls (R39):**
  `src/800.c func_800226C0` 45 pins ✓ · `src/shared/ov/func_80178004.h` 26 ✓ · `ov_SC03_006 func_80184034` 3 bare-name pins ✓ ·
  `engine_prelude.h` 0 asm sites (a macro definition only) ✓ — each counted by hand at gate 1 with an independent grep.
  **The table (2026-09-09; `.run/P36/census/lever_census.{json,txt}`):** A pins 37,720 in 13,279 bodies (1,833 distinct; `$0` 1,337,
  `$sp` 13, with initializer 5,140, volatile-qualified 136, bare-name 76, spelled `asm(` 210) · B asm 25,096 (barrier 5,835 · launder 5,233
  · keepalive 2,576 · instruction 1,857 [addu 1,103, move 407, la 145, lh 134, addiu 24, RTP_SND 22, …] · gte 6,911 · verbatim-body 2,683;
  14 at file scope) · C volatile 3,139 (cast 2,385 · decl-body 235 · decl-file 517 · param 2) · D bare register 86 · E asm-label 7,428 ·
  F builtin 445 · G attribute 76 · **union A–D 19,164 bodies / 2,545 distinct** (488 multi-copy classes hold 17,107 bodies; by kind ov
  18,330 · shared 393 · md 213 · main 212 · resident 16) · **the phase's number 53,221 sites in 15,666 bodies (2,214 distinct), 0 marked,
  53,221 UNMARKED** · asm-bearing macro definitions 9,540 (338 names, 32 with >1 text; gte 9,102 · launder 428 · instruction 9 · barrier 1).
  **Corrections to the gate-1 numbers (R14):** pins 37,720 live, not 40,346 (the grep counted 8,584 `register` tokens in comments and
  dead code); file-scope `extern volatile` 517, not 8,262 (the gate-1 count included the `volatile` token inside 6,510 GTE macro lines);
  bare `register` 86, not 290; asm statements 15,501 once GTE (6,911) and the verbatim bodies (2,683) are set apart.
  **FINDING (R32, P9): 23 whole-body assembly routines live inside C shells** — `void func_801285E4(void) { extern s32 D_801840B4;
  __asm__ __volatile__(".set noreorder\n" "addiu $sp, $sp, -24\n" "lui $v1, 0x1f80\n" "ori $v1, $v1, 0x03fc\n" "sw $ra, 16($sp)\n" "addu
  $t0, $v1, $zero\n" "sw $sp, 0($t0)\n" … : : : "memory"); }` — 2,683 sites: 20 routines with one private copy per overlay (133 each; bytes
  vary per overlay — 134 distinct `h_exact` at 0x801285E4 across 141 sig rows, each copy wrapping its overlay's own callee) + one shared
  header each, and 3 shared-header-only routines (`func_80128678`, `func_80155FF8`, `func_80184440`). They switch `$sp` to the scratchpad
  (0x1F8003FC) around a call — a stack-switch trampoline no compiler emits; 18–37 instructions each, ~448 per overlay. They are the §265
  "verbatim-asm bank lane" in its IN-FUNCTION form, which `tools/verbatim_check.py` (a file-scope `__asm__` detector) and the manifest's
  P31 S75 derivation never saw: the manifest lists 5 file-scope rows, the README says "Five functions across the fleet are hand-written
  assembly", and `progress.py`'s `verbatim_asm_bodies` = 5. The census sets them apart as `verbatim-body` (not levers), publishes them in
  the README sentence, and the decision below is Drew's.
  **Aside for the record:** 0x801285E4 has 141 sig rows and the S1 class at that address 3 instances — the other 138 are per-overlay
  byte variants (singleton classes), not an S1 gap.

- **S97 — T1b the manifest's in-function form.** Drew confirmed the recommendation. Rows built from the census sites + the sig files:
  22 routines carry the trampoline signature (`0x03fc` + `sw $sp`; 20 with 133 private copies each + a shared header, bytes varying per
  overlay — 134 distinct `h_exact` of 141; `func_80128678` and `func_80155FF8` shared-only, byte-identical fleet-wide) → PERMANENT-VERBATIM;
  `func_80184440` (13 ins, 2 binaries) has an `-O0` frame-pointer prologue around two global stores → DECOMPILE-NOW (a carve into an `-O0`
  unit; a lever until then). `tools/verbatim_check.py --strict`: `verbatim bodies in tree: … in-function sites across 23 routines · manifest
  rows: 28 (23 of them fleet-wide "ov_*" in-function rows) · no drift` (the literal line is in `.run/P36/baseline/verbatim_check_t1b.log`).
  The census's `asm-body` kind is structural (the asm statement is the function's only statement; declarations aside) and the manifest
  decides: `verbatim-body` 2,682 sites / 22 routines excluded; `asm-body` 1 site (`func_80184440:DECOMPILE-NOW`) counted — **53,222 sites
  in 15,667 bodies (2,215 distinct)**. README block: `27 hand-written-assembly bodies kept verbatim`; prose + wiki + gen3 docs dated.

- **S97 — T1b, second pass: the structural detector found 21 MORE in-function bodies.** The first census had applied the whole-body
  test only to templates classed `instruction`; `tools/verbatim_check.py`, detecting structurally (the asm statement is the function's
  only statement, declarations aside) through `lever_census.whole_body_asm_functions`, listed 70 NEW — 49 of them false positives of
  the declaration regex (`iVar1 = …` read as type `iVa` + name `r1` with an initializer; fixed with `\b` after every identifier and a
  size pre-filter — the unbounded regex had also made the guard take minutes) and **21 genuine**: 8 Sony libgs `GsTMDfast*` renderers
  in `src/800b2.c` (the cookbook's §176-area bank: libgs code carried as asm where no SDK object of that version matched) and **13 game
  functions carried whole as assembly inside C shells** — main `func_8001E378` (188 ins), `func_80020F34` (53), `func_800249F0` (116),
  `func_80025CBC` (127), `func_80026514` (239), `func_800268D0` (293), `func_80027058` (106), `func_80027200` (125); `md_MAIN_027:
  func_800CBA44` (109), `md_SC07_003:func_801A3BCC` (372); `ov_SC04_016:func_8017E26C` (269), `ov_SC06_032:func_8017D810` (33),
  `ov_SC07_000:func_8017EEC0` (8) — plus the shared `func_80184440` (13, `-O0` shape). None is in the P31 S75 taxonomy (200 rows, all
  file-scope): the lane's in-function form was never censused. **Manifest now 49 rows:** 27 PERMANENT-VERBATIM (5 file-scope + 22
  trampolines) · 8 SDK-VERBATIM (Sony's code, not ours) · 11 DECOMPILE-NOW (compiler-shaped prologue, no hand-asm marker) · 3 UNCERTAIN
  (`$at` present: `func_80026514`, `func_800268D0`, `func_8017E26C` — adjudicate). `verbatim_check --strict`: `verbatim bodies in tree:
  2709 (5 file-scope, 2704 in-function sites across 44 routines) · manifest rows: 49 (23 of them fleet-wide "ov_*" in-function rows) ·
  no drift` (`.run/P36/baseline/verbatim_check_t1b.log`). The census excludes only PERMANENT/SDK dispositions (by name for `ov_*`
  rows, by (binary, addr) for concrete ones — `share_census.verbatim_instances` now skips the wildcard rows); DECOMPILE/UNCERTAIN bodies
  are LEVERS: **the phase's number is 53,234 sites in 15,679 bodies (2,227 distinct)** (pins 37,720 + asm statements 15,514, of which
  14 are whole-body asm functions to decompile). README block: `27 hand-written-assembly bodies kept verbatim · 8 Sony library routines
  carried as assembly where no SDK object matched`. **P9 finding for the record:** the P32 close's "every game-code function in every
  binary is C" was measured by instruments blind to the in-function form (`progress.py`'s verbatim bucket and `verbatim_check` are
  file-scope detectors); 14 game functions (8 in main) were assembly in C shells all along. The README prose is corrected in this commit;
  the decision log carries it at T9; Drew's word on the SDK/DECOMPILE/UNCERTAIN split is asked at the T1b report.

- **S97 — T2 the oracle and the probe (R37).** *The oracle* (`tools/delever_oracle.py`): every object's exact build command captured once
  through `make -n -W <src> <obj> BINARY=<alias>` (4,284 recipes, 14 s at -j16 — the Makefile's own pipeline with the jtbl pad stage of
  main/module objects, the per-object `-O0` overrides, the twin rule); a candidate compiled IN PLACE (objects carry the source path as an
  STT_FILE symbol) with `-o`/`-MF` redirected to scratch, the file restored from the in-memory snapshot after every compile; verdict =
  whole-object byte equality with `build/`'s object of the T0 fleet run. **Calibration:** `177/177 objects byte-identical untouched;
  twin checks 32 (0 mismatch); positive control DIFFERS on build/src/800.o; 2.3 s — OK` (`.run/P36/delever/calibration.json`; two
  instrument findings on the way: a control injected BEFORE the declarations is a C89 parse error, so it goes at the end of the body;
  gcc 2.7.2 reports errors without the word "error" and the assembler floods stderr with `$at` warnings — the error filter keeps
  every non-warning line, R103). *The engine* (`tools/delever.py`): positional rewrites per class at the census's line/col on the raw
  text (a token mismatch REFUSES); rung A strip-all (measured with `register` dropped and kept), rung B greedy; TUs in parallel (one
  worker per file), **shared headers SERIAL after the TU phase** — the dry run's three "compile errors" were two workers' candidates
  crossing inside one includer (a header edit reaches every includer: the campaign tool must never compile a TU while any header it
  includes is being edited). A no-op edit is REFUSED (an identical object would prove nothing, R37).
  **The probe (`--probe --sample 300 --seed 11 -j 12`; `.run/P36/probe/`):** 285 distinct bodies (one exemplar per normalized class,
  stratified by binary kind × site count × class mix, topped up for the `$0`/initializer/instruction/cast/register/launder/keep-alive
  features), 283 judged (2 NOTHING-USABLE), **1,660 compiles, 151 s wall, 0.225 s per compile, 5.87 compiles per body**.

  | kind | bodies | A identical | A (register kept) | lever-free after B | sites | removed | needed | compiles | s/compile |
  |---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
  | main | 40 | 6 | 6 | 6 | 272 | 146 | 126 | 328 | 0.386 |
  | resident | 16 | 4 | 4 | 4 | 31 | 9 | 22 | 53 | 0.06 |
  | md | 29 | 2 | 2 | 2 | 121 | 56 | 65 | 161 | 0.139 |
  | shared | 40 | 7 | 7 | 7 | 164 | 65 | 99 | 216 | 0.211 |
  | ov | 158 | 34 | 34 | 34 | 721 | 285 | 436 | 902 | 0.195 |
  | **all** | **283** | **53** | **53** | **53** | **1,309** | **561 (42.9 %)** | **748 (57.1 %)** | **1,660** | **0.225** |

  Needed by kind: pin 360 of 798 (45 %) · launder 154 of 199 (77 %) · barrier 127 of 154 (82 %) · keep-alive 36 of 44 · instruction 21
  of 24 · cast 26 of 51 · decl-body volatile 16 of 27 · bare register 8 of 12. **Needed pins by register class: v0/v1 126 · a0–a3 112 ·
  s0–s7 71 · t0–t9 36 · $0 13** (removed: s 147 · t 107 · v 90 · a 87). Residue bodies 230 of 283: 75 need only pins, 129 need at least
  one asm statement. Bodies with a launder 4/68 lever-free, a barrier 9/78, a `$0` pin 1/17, a cast 1/22, an initializer pin 7/32.
  `register` dropped vs kept: identical results (53 = 53) — the keyword is byte-neutral at -O2 on this sample. Instrument noise: rung A
  1 COMPILE-ERROR + 1 REFUSED; 6 of 748 needed sites judged by a compile error (0.8 %); 9 rewrites refused (multi-instruction
  templates, `mult`/`mfhi`, a bare `addu $v0,$zero,$zero` with no C operands, `RTP_SND` macro-carried instructions).
  **Pricing (R41; population 16,064 lever bodies / 55,913 removable sites, 2,633 distinct classes by body hash):** T4 (rungs A+B fleet-wide)
  ≈ 94,000 compiles ≈ 5.9 CPU-h ≈ **0.5 h wall at 12 workers** — cheap, and it removes ≈ 24,000 sites (43 %) and frees ≈ 3,000 bodies
  (19 %). **The residue ≈ 13,000 bodies / 32,000 sites ≈ 81 % of bodies — by distinct classes ≈ 1,800 exemplars** whose copies replay:
  that is the campaign grind-to-zero prices (T6 recipes + permuter, then T7 waves). Where the residue sits: launders + barriers +
  keep-alives (317 of 748 needed = 42 %) — the CSE/scheduling steers; v0/v1 + a0–a3 pins (238 = 32 %) — argument/return-register copies
  (the §194-E/§17a ARGCOPY class); callee-saved pins (71 = 9 %) — the allocation-order class (R73, `alloc_table.py`); the rest casts,
  volatile declarations, `$0` variables, instructions. **Design consequences for T3:** per-body compiles at 0.2 s make group testing
  unnecessary (simplicity wins); run T4 first and publish the fall; rung R (T6) targets the three big classes in that order.

- **S98 2026-09-09 — T3 the campaign tool (design at Max; the tools built, the end-to-end batch follows).** Session start at low effort; Drew:
  `/effort max`, "build task list and resume current phase"; the harness task list rebuilt (R28, 12 tasks; T0–T2 completed). Reconnaissance on
  T2's engine and probe before any design (R37/R38): three findings that CHANGE the numbers — (1) **989 of the 4,793 direct launders are
  ASSIGNMENTS** (`__asm__("" : "=r"(p) : "0"(&D_x))` — output ≠ input); the probe deleted them as statements, which left the variable undefined and
  **cc1 2.7.2 ABORTED** (the probe's one "Done" COMPILE-ERROR, `ov_SC03_124 func_80188C68` launder at 3449, reproduced 3/3: rc 134,
  `Aborted (core dumped) | tools/bin/gcc-2.7.2-psx/cc1`; the error filter had kept bash's job-status line and dropped the signal line) — the
  probe's "launder 77 % needed" is partly this; (2) the **macro-carried launders are mostly compound macros** (`XFER`/`DRAW`/`RTP_SND`/`COPY_TO_FAAC`,
  ~60 uses in 8 definitions: real code around the asm — the probe's rewrite deleted the whole USE statement, which is a correctness hazard; only
  `SHB`/`ENGINE_SHB` (416 defs / 2 texts, 399 uses) are pure launder statements and `LAUNDER_8018A180` a launder statement-expression);
  (3) **46 lever bodies live in `-O0` translation units** (boot.c 31 bare `register` + 6 instructions; `md_MAIN_003_o0*` / `md_MAIN_011`) — the
  plan's "none have pins" was about pins; they are judged by their own recipes, not refused (the ledger records `o0`). Also measured: 5 lever
  bodies not named `func_` (addresses from `config/symbols.us.txt`), 1 class whose members disagree on the site sequence (the replay checks it),
  369 header bodies (203 with < 20 includers, 165 with 120–139), 517 file-scope `volatile` declarations in 256 TUs, 2 `volatile` parameters,
  0 multi-declarator pins, nested includes only `engine_prelude.h` → `include/` (the includer scan is transitive anyway).
  **Design (X1, the non-obvious choices):** the verdict unit is the body, the write unit the file, the proof unit the file's FINAL compile
  (every body judged against the original text; all accepted edits + the file-scope volatile edits + the markers spliced once and compiled
  through every recipe — a twin's object, every includer of a header in parallel; DIFFERS → the file-scope edits dropped and retried → the file
  restored and COMBINATION-FAILED, loud); **"done" is a ledger fact keyed by normalized text** (every row carries the body's `nhash` BEFORE and
  AFTER; current nhash ∈ after-hashes → done, ∈ before-hashes → replay in one compile, a disagreement falls through to the full ladder and is
  recorded; markers are comments and do not move the hash; a reshaped body gets a new hash and is drawn again — so T6/T7 need no new bookkeeping);
  the launder-assignment and macro-shape rewrites above; the oracle's **COMPILE-CRASH** verdict (a signal line / rc ≥ 128, R103) distinct from
  COMPILE-ERROR; class C/D survivors judged, ledgered, never marked (decision 3), class A/B survivors marked `// !FAKE: <kind> <detail> — <verdict>
  (P36 <rung> <label>)` at the end of their line (one marker per line, an old one replaced); an asm-body DEFERRED (T7) and marked; the census
  gains `head` + a stat-based `src_stamp` and `--apply` refuses a census that does not describe the tree (it reruns it); the outer gate of EVERY
  batch is the clean fleet run (90 s — cheaper than per-binary checks past ~15 touched binaries, and it refreshes `build/`, the oracle's
  baselines); the calibration is rerun after every commit (2.4 s; its positive control now restores the source's mtime so the census stamp
  survives it); exemplar files run before their copies (a class cover, phase 1) so the replay discount is real; `inflight.json` (every batch
  file's original text, written before the first write) is the only restore (R102). Refusals: a token mismatch, no statement end, a compound
  macro, an instruction with no C spelling, an assigned zero-register variable, two `$0` pins in one body, a no-op edit, an empty includer set,
  a dirty `src/`, a stale calibration or census, an untracked dotfile under `src/` (the cycle).
  **Built:** `tools/delever.py` (1,548 lines: `--plan`, `--apply`, `--restore`, `--status`, `--apply-body`, `--selftest`, `--probe`),
  `tools/delever_oracle.py` (COMPILE-CRASH, `recipes_by_src`, `judge_all`, the mtime restore), `tools/lever_census.py` (`src_stamp`, `head`),
  `tools/delever_cycle.sh`, `.gitignore` (`inflight.json` ignored; the ledger/batch records/logs already allowlisted), SETUP + dictionary rows,
  kit corpus (`tool_census --check: OK`).
  **Verify so far:** `delever --selftest: OK — 15 sites in the exemplar, 1 refused rewrite(s), ladder RESIDUE (15 compiles), replay replay
  (1 compile), markers 5` (the fixture through the census's own parser: every rewrite incl. the assignment launder, the `$0` uses → 0, the
  expression-launder macro → `((s32)(&buf))`, the compound macro REFUSED; the ladder against a stub oracle with two needed sites and one whose
  removal crashes → NEEDED COMPILE-CRASH; 5 marker lines, none on a class C/D site; the replay on a copy in another address environment = 1
  compile with the same verdicts; a disagreeing replay → rung B; the ledger index; the oracle's signal-line regex on the real bash form).
  `lever_census --sites -j 16 --no-cache`: **53,234 / 15,679 / 2,227 unchanged**, `head 89676f096`, `src_stamp` written (32 s).
  `delever_oracle --calibrate main ov_SC03_014 ov_SC03_015 ov_SC04_011: 177/177 objects byte-identical untouched; twin checks 32 (0 mismatch);
  positive control DIFFERS on build/src/800.o; 2.4 s — OK`. `delever --plan --only ov_SC04_011: 18 of 18 drawable files · 176 bodies (109 in
  multi-copy classes) · 540 removable sites`; the campaign order's head: the `*_jr_80140608.c` copies (11 bodies / 30 sites each, classes of
  134); headers: 371 drawable files. **Next in this task:** the end-to-end batch `LABEL_PREFIX=t3_ TASK=T3 tools/delever_cycle.sh 1 1 300 tus
  ov_SC04_011` (apply → R22 → census → log → commit), then the checkpoint refresh.

- **2026-09-09 — T3 batch `t3_tus1`** (`.run/P36/delever/run_t3_tus1.log`, `batch_t3_tus1.json`, `apply_t3_tus1.log`; apply 101 s wall): `delever: batch t3_tus1 — 18 files (TUs; 18 drawable) · 176 bodies: 44 lever-free, 130 residue, 2 refused · sites removed 215 / needed 320 / refused 5 / deferred 0 · replays 0 (0 disagreed) · compiles 657 in 101 s wall · final 18/18 identical · written 18 files` → R22 (`.run/P36/baseline/r22_t3_tus1.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=117.23 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 53,035 sites in 15,638 bodies (2,246 distinct) · marked !FAKE 312 · UNMARKED 52,723` — committed `cd24727dd` (its message and its log entry were written by the cycle with an EMPTY verify line and the coverage line: the script's `^delever:` grep missed the timestamped line and its `final X/X` check passed VACUOUSLY on the empty string (R32/R85) — both fixed in the script, the entry rewritten here from the tool's own logs, R66; the cycle had also inserted its entries AFTER the checkpoint block — it now inserts before it). Needed by the oracle's word: DIFFERS 320, COMPILE-ERROR 0, COMPILE-CRASH 0 (the launder-assignment rewrite ended the probe's crash class); by kind: pin 194 needed / 179 removed, launder 46 / 3, barrier 40 / 9, keepalive 13 / 5, instruction 14 / 3 rewritten, cast 11 / 12, decl-body 1 / 3, decl-file 1 / 1 (a file-scope `volatile` came off byte-identical). The batch's long pole: `ov_SC04_011_jr_8017D494.c` (76 bodies, one worker) — phases now start the longest files first.
- **2026-09-09 — T3 batch `t3_tus2`** (`.run/P36/delever/run_t3_tus2.log`, `batch_t3_tus2.json`): `delever: batch t3_tus2 — 1 files (TUs; 1 drawable) · 2 bodies: 0 lever-free, 1 residue, 1 refused · sites removed 2 / needed 2 / refused 1 / deferred 0 · replays 0 (0 disagreed) · compiles 6 in 3 s wall · final 1/1 identical · written 1 files` → R22 (`.run/P36/baseline/r22_t3_tus2.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=101.55 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 53,033 sites in 15,638 bodies (2,246 distinct) · marked !FAKE 310 · UNMARKED 52,723`.

- **S98 — T3 close: the redraw, the stale-marker finding, the orphan check, the cache-key finding, the scrub.** The refused body
  (`func_8018C14C`: `register s32 ent __asm__("$4") = (s32)a0 + zr;` — the zero-register variable used inside another pin's initializer, two
  overlapping rewrites) → the zero-use edit is now COMPOSED into the enclosing edit's replacement (`s32 ent = (s32)a0 + 0;` when both go;
  moot inside a deleted statement); `--redraw REFUSED NOTHING-USABLE` draws such bodies again after a tool fix; the cycle passes `REDRAW`.
  Redraw batch `t3_tus2` (the cycle, fixed greps): `delever: batch t3_tus2 — 1 files (TUs; 1 drawable) · 2 bodies: 0 lever-free, 1 residue, 1
  refused · sites removed 2 / needed 2 / refused 1 · compiles 6 in 3 s wall · final 1/1 identical · written 1 files` → R22 **`check-all: 218
  passed, 0 failed of 218`** → committed `7ee458dd7`. **Its diff showed the next defect (R14 — read the artifact):** a site that carried an older
  marker and was then REMOVED kept the stale marker text (`s32 ent = …;  // !FAKE: pin $4 — REFUSED …`; a deleted barrier left its marker on
  an otherwise empty line). Fixed at the cause — a removed/rewritten site CONSUMES a trailing marker on its line (`consume_marker`,
  `whole_line_of` on the masked text) — and at the instrument: the census counts **orphan markers** (a `// !FAKE:` line with no pin/asm
  site on it nor on the line below unless that line carries its own) and `--check` fails on them; `delever --scrub [--only …]` removes
  them, each file judged through every recipe. **The census's per-file walk cache then hid the two orphans** (keyed on mtime/size only,
  it served the OLD walker's results: `orphan_markers 0` while a direct walk found `[13634, 13641]`) → the cache key now carries the
  walker's own hash (R35: fix the instrument before trusting its measurement). Rerun: `orphan !FAKE markers … : 2`; `lever_census --check`:
  `2 ORPHAN !FAKE marker(s) … src/ov_SC04_011/ov_SC04_011_jr_8017D494.c:13634, :13641 — FAIL` (the R39 positive control of the new check);
  `delever --scrub --only ov_SC04_011 --label t3_scrub`: `2 orphan marker(s) removed in 1 file(s); 0 file(s) refused` (the object
  identical); R22 (`.run/P36/baseline/r22_t3_scrub.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=142.89 s`); census
  **`53,033 sites in 15,638 bodies (2,246 distinct) · marked !FAKE 310 · UNMARKED 52,723` · `orphan !FAKE markers: 0`**;
  `lever_census --check` now fails ONLY on the 52,723 UNMARKED (the expected mid-campaign state until T4 judges them). Selftests:
  `lever_census --selftest: OK — 23 sites, 2 defs, 2 asm macros` (+ the orphan line), `delever --selftest: OK — 15 sites in the exemplar, 1
  refused rewrite(s), ladder RESIDUE (15 compiles), replay replay (1 compile), markers 5` (+ the composed zero-use, the consumed markers,
  `scrub_edits`). `tool_census --check: OK` (kit corpus regenerated). **T3 ☑** — the tool, the cycle, the selftests, the calibration line
  (177/177), one overlay end-to-end with R22 green (twice, plus the scrub). **The ov_SC04_011 numbers stand as the first real sample of the
  campaign (R41):** 176 bodies → 44 lever-free (25 %), 215 of 540 sites removed (40 %); every NEEDED verdict is DIFFERS.
  **Priced T4 from it:** 2,601 drawable TU files (the census + ledger at this commit) at ~1.3 s per exemplar body (12 workers) and one compile
  per replayed copy → batches of 300 files ≈ 5–8 min + R22 ≈ 2 min + census ≈ 0.5 min; ~9 TU batches + ~2 header batches (371 files, serial
  with parallel includers) ≈ 1.5–2.5 h wall, unattended.

- **2026-09-09 — T4 batch `tus1`** (`.run/P36/delever/run_tus1.log`, `batch_tus1.json`): `delever: batch tus1 — 300 files (TUs; 2204 drawable) · 1392 bodies: 299 lever-free, 1093 residue, 0 refused · sites removed 3342 / needed 4177 / refused 0 / deferred 0 · replays 1364 (0 disagreed) · compiles 1794 in 59 s wall · final 300/300 identical · written 300 files` → R22 (`.run/P36/baseline/r22_tus1.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=157.17 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 49,787 sites in 15,243 bodies (2,244 distinct) · marked !FAKE 4,391 · UNMARKED 45,396`.

- **2026-09-09 — T4 batch `tus2`** (`.run/P36/delever/run_tus2.log`, `batch_tus2.json`): `delever: batch tus2 — 300 files (TUs; 2483 drawable) · 2752 bodies: 495 lever-free, 2257 residue, 0 refused · sites removed 3505 / needed 5262 / refused 0 / deferred 0 · replays 1350 (0 disagreed) · compiles 5616 in 251 s wall · final 300/300 identical · written 297 files` → R22 (`.run/P36/baseline/r22_tus2.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=148.11 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 46,424 sites in 14,758 bodies (2,258 distinct) · marked !FAKE 9,393 · UNMARKED 37,031`.

- **S98 — T4 in progress: the campaign launched; three tool fixes between batches (each picked up by the next batch — the cycle re-reads
  the tool per batch; committed once the cycle was idle, R59).** (1) **"Done" is per body:** the T4 preflight drew `2204 of 2204` TU files
  where ~2,583 were expected — the ledger's done set was keyed by normalized text alone, so every fleet-wide copy of an all-NEEDED exemplar
  (after-hash == before-hash, e.g. the 133 copies of a residue body) passed as done, never drawn, never marked; now done = (tu, fn,
  after-hash), the text hash is the REPLAY key only (selftest: a copy with a judged text but no row of its own is drawn) — batch tus2 drew
  `2483 drawable`. (2) **The includer map is cached** per file on (mtime, size) in the ignored `includers_cache.json`: 29 s → 1.3 s per
  batch, proven equal to the uncached map (R39). (3) **A stale `.git/index.lock`** (created 03:24:19 during batch tus2's fleet run, no
  holder — the Makefile runs no git; a harness hook is the likely source) cost tus2 its commit: the batch was complete and gated (apply
  `final 300/300 identical`, R22 `218 passed`, the census, the log entry) and was committed by hand from its own lines (`85905840c`); the
  cycle now waits out a transient lock (6 × 10 s) and clears a stale one (no git process alive), logging it. **Batches so far:** `tus1`
  (`a605e1dba`): 300 files · 1,392 bodies: 299 lever-free, 1,093 residue · sites removed 3,342 / needed 4,177 · replays 1,364 (0 disagreed) ·
  1,794 compiles in 59 s · R22 218/218 → 49,787 sites; `tus2` (`85905840c`): 300 files · 2,752 bodies: 495 lever-free, 2,257 residue · removed
  3,505 / needed 5,262 · replays 1,350 (0 disagreed) · 5,616 compiles in 251 s · R22 218/218 → **46,424 sites in 14,758 bodies (2,258
  distinct) · marked 9,393 · UNMARKED 37,031**. The replay discount is real (≈ half the bodies, 1 compile each, 0 disagreements so far).

- **S98 — T4: the harness's low-memory guard killed the background cycle mid-apply of batch `tus3`** ("stopped because the system is
  running low on memory" — the box had 22 GB free of 31; the guard's own heuristic, the failure mode the S88 memory records for long
  background tasks). State found: 50 batch files holding final or candidate texts (a SIGKILL skips the restore `finally`), `inflight.json`
  present, no fleet run for the batch, 641 ledger rows appended by the batch's completed files, no surviving worker. **Recovery:** the
  641 `tus3` rows dropped from the ledger (backup `ledger.jsonl.killed_tus3`, ignored scratch) — a body judged all-NEEDED in a killed batch
  would otherwise count as done while its markers were restored away — then `delever --restore: 50 of 300 files restored … src clean`.
  **Now built in:** `inflight.json` carries the batch label and `--restore` drops that label's rows itself; the cycle's usage says to run
  it DETACHED (`setsid nohup …`) with a tiny waiter, never as a harness background task. The campaign continues from batch 3 detached.

- **2026-09-09 — T4 batch `tus3`** (`.run/P36/delever/run_tus3.log`, `batch_tus3.json`): `delever: batch tus3 — 300 files (TUs; 2183 drawable) · 2513 bodies: 194 lever-free, 2319 residue, 0 refused · sites removed 2925 / needed 6699 / refused 0 / deferred 0 · replays 1251 (0 disagreed) · compiles 5347 in 194 s wall · final 300/300 identical · written 300 files` → R22 (`.run/P36/baseline/r22_tus3.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=112.47 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 43,517 sites in 14,550 bodies (2,250 distinct) · marked !FAKE 16,077 · UNMARKED 27,440`.

- **2026-09-09 — T4 batch `tus4`** (`.run/P36/delever/run_tus4.log`, `batch_tus4.json`): `delever: batch tus4 — 300 files (TUs; 1883 drawable) · 2224 bodies: 673 lever-free, 1551 residue, 0 refused · sites removed 2143 / needed 3936 / refused 0 / deferred 0 · replays 1328 (0 disagreed) · compiles 4095 in 158 s wall · final 300/300 identical · written 300 files` → R22 (`.run/P36/baseline/r22_tus4.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=114.75 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 41,414 sites in 13,872 bodies (2,225 distinct) · marked !FAKE 19,995 · UNMARKED 21,419`.

- **2026-09-09 — T4 batch `tus5`** (`.run/P36/delever/run_tus5.log`, `batch_tus5.json`): `delever: batch tus5 — 300 files (TUs; 1583 drawable) · 1225 bodies: 63 lever-free, 1162 residue, 0 refused · sites removed 1821 / needed 5783 / refused 0 / deferred 0 · replays 624 (0 disagreed) · compiles 3110 in 73 s wall · final 300/300 identical · written 300 files` → R22 (`.run/P36/baseline/r22_tus5.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=115.39 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 39,918 sites in 13,820 bodies (2,224 distinct) · marked !FAKE 25,081 · UNMARKED 14,837`.

- **2026-09-09 — T4 batch `tus6`** (`.run/P36/delever/run_tus6.log`, `batch_tus6.json`): `delever: batch tus6 — 300 files (TUs; 1283 drawable) · 1409 bodies: 301 lever-free, 1108 residue, 0 refused · sites removed 1667 / needed 2377 / refused 0 / deferred 0 · replays 897 (0 disagreed) · compiles 2505 in 63 s wall · final 300/300 identical · written 300 files` → R22 (`.run/P36/baseline/r22_tus6.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=114.08 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 38,580 sites in 13,622 bodies (2,225 distinct) · marked !FAKE 27,018 · UNMARKED 11,562`.

- **2026-09-09 — T4 batch `tus7`** (`.run/P36/delever/run_tus7.log`, `batch_tus7.json`): `delever: batch tus7 — 300 files (TUs; 983 drawable) · 1407 bodies: 432 lever-free, 973 residue, 2 refused · sites removed 1855 / needed 2032 / refused 6 / deferred 0 · replays 589 (0 disagreed) · compiles 3211 in 101 s wall · final 300/300 identical · written 300 files` → R22 (`.run/P36/baseline/r22_tus7.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=116.04 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 36,764 sites in 13,224 bodies (2,199 distinct) · marked !FAKE 29,045 · UNMARKED 7,719`.

- **S98 — T4: the census's known-true control went stale on a correct tree (batch `tus7`).** The detached cycle (batches `tus3`–`tus6`
  committed `ce8737066`, `5e10b19e8`, `ca761c4f6`, `3e60fdf41`, each R22 218/218) stopped after `tus7`'s green apply (`final 300/300
  identical`) and green fleet run (`218 passed`) at the census: `ov_SC03_006 func_80184034 bare-name pins got 0 expected 3 MISMATCH` — the
  batch had removed those three pins byte-identically; the control's hand count from T1 could only be right while the body's text was the
  one it was counted on (R39's control is a property of the INSTRUMENT, and this one had a hidden precondition). Fix: each control carries
  the body's T1 normalized hash (`CONTROL_NHASH`, from commit `357f8a1ed`) and reports **N-A** once the text differs — never a failure on
  a correct tree, never a silent pass on a wrong walker. The batch was finished from its own logs with the cycle's new `FINISH=<label>`
  mode (census → log entry → commit, no work redone): `34f03003d`. Also learned: the harness's low-memory guard kills its background
  tasks (the cycle, then a 30-byte waiter) while the box has 22 GB free — the cycle runs DETACHED (`setsid nohup`) and a `Monitor` on
  its log reports each commit.

- **2026-09-09 — T4 batch `tus8`** (`.run/P36/delever/run_tus8.log`, `batch_tus8.json`): `delever: batch tus8 — 300 files (TUs; 683 drawable) · 602 bodies: 208 lever-free, 394 residue, 0 refused · sites removed 432 / needed 601 / refused 1 / deferred 0 · replays 206 (0 disagreed) · compiles 1458 in 48 s wall · final 300/300 identical · written 300 files` → R22 (`.run/P36/baseline/r22_tus8.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=112.84 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 36,419 sites in 13,044 bodies (2,173 distinct) · marked !FAKE 29,642 · UNMARKED 6,777`.

- **2026-09-09 — T4 batch `tus9`** (`.run/P36/delever/run_tus9.log`, `batch_tus9.json`): `delever: batch tus9 — 300 files (TUs; 383 drawable) · 1901 bodies: 454 lever-free, 1430 residue, 8 refused · sites removed 2244 / needed 2937 / refused 42 / deferred 9 · replays 522 (0 disagreed) · compiles 5262 in 294 s wall · final 300/300 identical · written 297 files` → R22 (`.run/P36/baseline/r22_tus9.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=113.94 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 34,459 sites in 12,656 bodies (1,909 distinct) · marked !FAKE 32,473 · UNMARKED 1,986`.

- **2026-09-09 — T4 batch `tus10`** (`.run/P36/delever/run_tus10.log`, `batch_tus10.json`): `delever: batch tus10 — 83 files (TUs; 83 drawable) · 362 bodies: 99 lever-free, 258 residue, 2 refused · sites removed 411 / needed 483 / refused 37 / deferred 3 · replays 4 (0 disagreed) · compiles 1171 in 25 s wall · final 83/83 identical · written 83 files` → R22 (`.run/P36/baseline/r22_tus10.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=112.89 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 34,100 sites in 12,570 bodies (1,823 distinct) · marked !FAKE 32,973 · UNMARKED 1,127`.

- **2026-09-09 — T4 batch `headers1`** (`.run/P36/delever/run_headers1.log`, `batch_headers1.json`): `delever: batch headers1 — 200 files (headers; 371 drawable) · 200 bodies: 42 lever-free, 158 residue, 0 refused · sites removed 302 / needed 340 / refused 1 / deferred 0 · replays 18 (1 disagreed) · compiles 40597 in 1460 s wall · final 200/200 identical · written 196 files` → R22 (`.run/P36/baseline/r22_headers1.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=109.12 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 33,812 sites in 12,538 bodies (1,787 distinct) · marked !FAKE 33,301 · UNMARKED 511`.

- **2026-09-09 — T4 batch `headers2`** (`.run/P36/delever/run_headers2.log`, `batch_headers2.json`): `delever: batch headers2 — 171 files (headers; 171 drawable) · 171 bodies: 37 lever-free, 133 residue, 0 refused · sites removed 199 / needed 332 / refused 0 / deferred 1 · replays 86 (0 disagreed) · compiles 967 in 146 s wall · final 171/171 identical · written 170 files` → R22 (`.run/P36/baseline/r22_headers2.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=113.78 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 33,625 sites in 12,501 bodies (1,728 distinct) · marked !FAKE 33,612 · UNMARKED 13`.

- **2026-09-09 — T4 batch `tus11`** (`.run/P36/delever/run_tus11.log`, `batch_tus11.json`): `delever: batch tus11 — 5 files (TUs; 5 drawable) · 5 bodies: 0 lever-free, 5 residue, 0 refused · sites removed 0 / needed 10 / refused 7 / deferred 0 · replays 0 (0 disagreed) · compiles 20 in 2 s wall · final 5/5 identical · written 5 files` → R22 (`.run/P36/baseline/r22_tus11.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=119.43 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 33,625 sites in 12,501 bodies (1,728 distinct) · marked !FAKE 33,625 · UNMARKED 0`.

- **S98 — T4 CLOSE: the mechanical campaign over the whole population (rungs A/B + replay), 15 batches, every one gated by the clean
  fleet run.** TU batches `tus1`–`tus10` (`a605e1dba`, `85905840c`, `ce8737066`, `5e10b19e8`, `ca761c4f6`, `3e60fdf41`, `34f03003d`,
  `d9e01a398`, `aa70308cf`, `cb2fb5e6d`), header batches `headers1`–`headers2` (`9184678f1`, `0cb78a6a7`), the file-scope stragglers
  `tus11` (`f087282a3`: the 6 file-scope `__asm__("")` barriers in the three `*_jr_8015444C.c` copies all NEEDED; the 7 file-scope
  `.section .rodata` blocks are DATA carried as assembly — refused as `asm-data`, marked, T7's) — each `check-all: 218 passed, 0 failed of
  218`. **Totals (the ledger, latest row per body; R41):** 16,334 bodies judged — **3,341 lever-free (20.5 %)**, 12,967 residue (79.4 %),
  13 nothing-usable, 13 deferred asm-bodies; sites 56,445 — **removed 20,780 + rewritten 283 = 21,063 (37.3 %)**, needed 35,281
  (62.5 %; the oracle's word: DIFFERS 35,273, COMPILE-ERROR 8), refused 88, deferred 13. By kind (needed % of the kind's sites): pin 20,643
  needed / 17,074 removed (55 % of 37,720) · barrier 4,570 / 1,257 (78 % of 5,829) · launder 4,631 / 419 + 138 rewritten as assignments
  (88 % of 5,233) · keep-alive 2,000 / 576 (78 %) · instruction 1,667 / 145 rewritten (90 % of 1,850) · cast 1,509 / 876 (63 %) ·
  decl-file 152 / 365 (29 % — most file-scope `volatile` came off) · decl-body 57 / 177 (24 %) · bare register 50 / 36 (58 %). Needed
  pins by register: $2 3,834 · $4 2,718 · $5 2,475 · $3 2,445 · $16 1,764 · $17 1,492 · $0 1,318 · $7 721 · $19 588 · $6 520 (the v/a
  argument-return class dominates, as the probe said). Refused: the macro-carried sites (RTP_SND 22, XFER 12, DRAW 9, XFERLAST 9,
  XFER_1919A0 6 — the lever is in the `#define`, T5), launders with 2 inputs 5, `addu`/`lui` with no C spelling 7, asm-data 7.
  Compiles 49,487 (16,577 s CPU); replays 8,239 of 16,334 bodies (50 %), **1 disagreement** (a header). **THE NUMBER: 53,234 → 33,625
  sites (−36.8 %) in 12,501 bodies (1,728 distinct) · marked 33,625 · UNMARKED 0 · orphans 0** — `lever_census --check: 33,625 pin/asm
  sites, 33,625 marked !FAKE, 0 UNMARKED — OK` (the mid-campaign gate is met; T8 wires it into tools-health). The residue for T5–T7:
  12,967 bodies in **1,803 distinct classes**; mix: pins-only 6,018 bodies, pins + asm 4,310, asm-only 2,141, C/D-only 498 (no A/B
  survivor — done for the phase's number, kept unmarked by decision 3); by kind ov 12,359 · shared 291 · md 163 · main 142 · resident 12.
  The T2 probe priced 43 % of sites / 19 % of bodies / ~1,800 exemplars; measured 37 % / 20.5 % / 1,803 — its pricing held. Published
  (R75): `make report BINARY=main` (285 s) → README line 30 `Levers off (Phase 36, snapshot 2026-09-09): 20,646 register pins and 12,979
  asm statements remain in 12,501 functions (1,728 distinct bodies), 33,625 of them marked …`, `docs/progress.json` `counts.levers`
  (`sites 33625 · marked_fake 33625 · unmarked 0`), the timeline regenerated. Instruments changed in this task (each with its log entry
  above): "done" per body; the includer cache; the stale-lock wait; `--restore` drops a killed batch's rows; the controls keyed on their
  T1 hashes; the cycle's FINISH mode; the file-scope pseudo-body now holds file-scope asm statements. **T4 ☑.** Rules check (P6) done
  after T4 (re-read complete).

- **S98 — T5 opened: the GTE consolidation — design, the signature engine, the header step (gated).** Reconnaissance (R37): 327 GTE macro
  names (215 `gte_*`, 112 address-suffixed private copies), 9,102 definitions, 1,140 direct GTE statements, 5,751 macro-carried uses;
  `mipsel-linux-gnu-as` and the maspsx tail both reject `rtps`/`mvmva` — the mnemonics are GAS macros in `include/gte_macros.inc` reached
  through `include_asm.h`; Sony's converted `inline_c.h` is unreliable for opcode words (`gte_rtps` = `.word 0x0000007f`, which assembles to a
  bare 0x7f) and serves for names, operand counts and clobber lists only; 3,269 macro uses and 968 direct statements carry a `"memory"`
  clobber, of which Sony's own STORE macros account for most — the steers are the clobbers on loads and compute ops. **Design (X1):** a
  SIGNATURE = (the bytes the build's own maspsx→as tail makes of the template with %k bound to $4–$7/$2–$3, #outputs, #inputs) — `nop;nop;rtps`,
  `.word 0x4a180001` and `cop2 0x0180001` are one; one canonical text per signature (the majority body, byte-proven in the fleet — the header
  ships nothing new), Sony's name when the operand counts agree, Sony's clobber set canonical EVEN when every definition carries the steer
  (the body synthesized: `gte_rtv0`'s six definitions all added `"memory"`); a definition with the canonical bytes and other clobbers is a
  lever variant `<name>_m` / `_v<hash>` — the apply TRIES it as canonical first and keeps it only when the object differs; direct statements
  rewritten into canonical calls when bytes and clobbers agree (a concatenation of two canonical macros included), marked as levers when
  their clobbers exceed the canonical's, counted when they match nothing. **Built:** `tools/gte_consolidate.py` (`--inventory`, `--header`,
  `--apply`, `--sweep`, `--status`, `--selftest`: `OK — signatures rtps=0100184a ldv0=000080c8040081c8; table 1 canonical / 1 variant; fixture
  edits 8`), the cycle's `MODE=gte`, the census's `gte-lever` class (a variant's uses; a direct statement whose clobbers exceed its canonical's,
  by a read-only lookup of the tool's signature cache) + `per_tu_asm_macro_definitions` + the strict gate on both (selftest OK), the dictionary
  + SETUP rows, kit corpus. **The inventory:** `9540 asm-bearing macro definitions (9102 GTE, 9101 signed), 1140 direct GTE statements (1137
  signed)` → **`canonical table — 50 signatures (41 with Sony's name), 8402 canonical definitions; 10 lever variants holding 699 definitions;
  1 unsigned`** (variants: `gte_rtv0tr_m` 307 defs / 293 files, `gte_ldv0_m` 179 / 163, `gte_ldrgb_m` 137, `gte_SetRotMatrix_m` 30,
  `gte_SetTransMatrix_m` 25, `gte_rtv0_m` 6, `gte_rtir_m` 3, `gte_rt_m` 1; three store macros MISSING Sony's `"memory"`: `gte_stsz4_vda39` 10,
  `gte_stsxy_vda39` 1, `gte_stclmv_v41be` 1; `gte_ldlvl_v02f2` with extra register clobbers 1; the unsigned one is a two-statement macro in
  `md_MAIN_019`); direct statements: 713 → canonical calls, 226 lever, 201 matching no canonical signature. **The header step:**
  `include/gte_inline.h` (50 macros; 9 project names beside Sony's 41: `gte_ldIR0z`, `gte_ldIRGB`, `gte_stORGB`, `gte_SetRotTransMatrix`,
  `gte_mulcol`, `gte_multrans`, `gte_ldlvl_alt`, `gte_ldv3_alt`, `gte_rt_alt`), included from `include/common.h` → every TU sees it, the local
  definitions still win as later definitions → **R22 `check-all: 218 passed, 0 failed of 218` (`wall=112.72 s`,
  `.run/P36/baseline/r22_t5_header.log`)**. Census after the header step (before any apply): GTE levers (clobbers beyond the canonical macro's): 49 sites (0 via a variant macro, 49 direct) · marked 0 · UNMARKED 49 · unsigned GTE statements 3 · per-TU asm macro definitions outside the GTE header: 9,540 {'gte': 9102, 'launder': 428, 'instruction': 9, 'barrier': 1} (GTE variants 0). Next: the apply batches
  (`tools/delever_cycle.sh 1 4 400 gte`, detached), then `--sweep`, then the T5 verify line.

- **2026-09-09 — T5 batch `gte1`** (`.run/P36/delever/run_gte1.log`, `batch_gte1.json`): `gte_consolidate: batch gte1 — 400 files: 400 consolidated, 0 defs-only, 0 unchanged, 0 refused, 0 no-recipe · definitions deleted 8056 / renamed as lever variants 5 (variant trials: 416 freed, 5 kept) · header-bound definitions kept 80 · use renames 930 · direct statements → calls 460 / lever 252 / unmatched 185 · markers 276 · compiles 1146 · final 400/400 identical` → R22 (`.run/P36/baseline/r22_gte1.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=117.27 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 33,901 sites in 12,601 bodies (1,756 distinct) · marked !FAKE 33,665 · UNMARKED 236`.

- **2026-09-09 — T5 batch `gte2`** (`.run/P36/delever/run_gte2.log`, `batch_gte2.json`): `gte_consolidate: batch gte2 — 244 files: 237 consolidated, 0 defs-only, 6 unchanged, 1 refused, 0 no-recipe · definitions deleted 895 / renamed as lever variants 60 (variant trials: 213 freed, 65 kept) · header-bound definitions kept 5 · use renames 105 · direct statements → calls 115 / lever 108 / unmatched 17 · markers 184 · compiles 1240 · final 237/237 written files identical · refused 1 (restored, ledgered)` → R22 (`.run/P36/baseline/r22_gte2.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=114.34 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 34,085 sites in 12,710 bodies (1,757 distinct) · marked !FAKE 33,741 · UNMARKED 344`.

- **S98 — T5: the consolidation applied fleet-wide (two batches, `145ab7719` + `666d4b5ae`), then the marker repair; four instrument
  findings on the way, each fixed at its cause.** Batch `gte1` (400 files, `final 400/400`): definitions deleted 8,056, header-bound
  homonyms kept 80, variant trials 416 freed / 5 kept, use renames 930, direct statements → calls 460 / lever 252 / unmatched 185; batch
  `gte2` (244 files): deleted 895, kept 5, trials 213 freed / 65 kept, renames 105, direct → calls 115 / lever 108 / unmatched 17, 1 file
  refused — R22 218/218 each. **Totals (R41): 644 files; 8,951 of 9,102 per-TU GTE definitions gone; 629 of 699 clobber variants came off
  BYTE-IDENTICAL in their trials (the `"memory"` was no steer there) and 70 stayed as marked `_m` levers; 575 of 1,137 direct GTE
  statements became canonical calls, 360 are levers (clobbers beyond Sony's), 202 match no canonical sequence; 85 definitions kept
  as header-bound homonyms.** The findings: (1) the first run refused 81 files "all DIFFERS" — a macro NAME is redefined between
  functions in one unit (~2 definitions per name per file) and a use must follow the definition ABOVE it, not the file's last: renames
  are scoped to the governing definition (selftest: a redefinition case); (2) still 80 refused — a HOMONYM across files: the unit's
  `gte_stsxy3_f4` had f3's bytes and was used only by an included `h_text` header (`func_8017BEBC__t67f11bf2.h`), which binds to the
  includer's definition — that is why those 20 headers are byte-variant per includer; such a definition is KEPT (the names phase's
  parameterized form), a header-bound variant whose trial differs stays under its own name; (3) `md_MAIN_026`: an OBJECT-like macro
  (`#define MVMVA __asm__ …`, used as `MVMVA;`) — the use-scan required parentheses; bare uses of a deleted object-like definition now
  become calls (`gte_rt();`); (4) after the batches the census reported 408 ORPHAN markers and only 3 direct GTE levers: the tool had put
  a direct statement's marker at the end of its LAST line (the census reads the first line or the one above), the variant note above
  a `#define` carried the marker token, and — the real one — the canonical table was REGENERATED at each batch from the consolidated
  units, so a signature whose definitions had all moved into the header dropped out and its direct statements silently stopped
  classifying; the census's walk cache then served those stale walks (keyed on the file and the walker, not on the tables). Fixed:
  the header's own definitions are part of the inventory with name authority (the table is stable: 50 signatures, 48 with no per-TU
  definition left), the marker goes on the statement's first line, the note carries no marker token, the census's cache key carries
  the tables' stamp, `--remark` re-marks unmarked GTE levers. Repair: `delever --scrub` (344 misplaced markers) + `gte_consolidate
  --remark` (349 markers on the right lines, 64 notes rewritten), R22 `check-all: 218 passed, 0 failed of 218`
  (`.run/P36/baseline/r22_t5_remark3.log`, 118 s). **Census now:** `34,090 sites in 12,712 bodies (1,759 distinct) · marked 34,090 · UNMARKED 0`
  (= 33,625 + the 465 GTE levers, INSIDE the number since T5) · `orphan 0` · `GTE levers 465 (103 via a variant macro, 362 direct) · marked 465`
  · `per-TU asm macro definitions outside the GTE header: 591 {gte 153 (variants 64, header-bound homonyms 80+, the unsigned two-statement
  macro 1), launder 428, instruction 9, barrier 1}` · `lever_census --check: 34,090 pin/asm sites, 34,090 marked !FAKE, 0 UNMARKED — OK`.
  The batch commits' census lines undercounted the GTE levers (the shrunk table) — this entry is the corrected reading (R66). Next: the
  refused unit rejudged, the dead-macro sweep, the T5 verify line.

- **S98 — T5 batch `gte3`: the refused unit rejudged with the object-like fix.** `md_MAIN_026.c: CONSOLIDATED — deleted 3 defs, use renames 9`
  (`MVMVA;` → `gte_rt();`; variant trials 2 freed) → R22 **`check-all: 218 passed, 0 failed of 218`** (`.run/P36/baseline/r22_gte3.log`) → census
  `34,087 sites … marked 34,087 · UNMARKED 0` · `GTE levers 462` · `per-TU asm macro definitions 588 {gte 150, launder 428, instruction 9, barrier 1}`.
  Every unit with GTE work is now consolidated (`gte_consolidate --status`: 645 consolidated, 6 unchanged, 0 refused).

- **S98 — T5 the dead lever-macro sweep (`gte_consolidate --sweep`, label `sweep3`).** Two false starts: the dead test counted a name's
  sibling definition as a mention (SHB is defined twice per unit → nothing was ever dead), then counted uses per name per file (a used
  sibling kept a dead definition alive) — now uses are counted per GOVERNING definition (a use, or an `#include` of a header that uses
  the name, belongs to the last definition above it). Result: **274 dead asm-bearing macro definitions deleted in 133 files** (all SHB
  definitions with no governed use), 0 compound macros' inner asm droppable (XFER/DRAW/RTP_SND/COPY_TO_FAAC/XFERLAST/LAUNDER_8018A180:
  15 refused "all DIFFERS" — their launder/barrier is a real steer, their uses stay marked, T7's), 19 refused in all. R22
  **`check-all: 218 passed, 0 failed of 218`** (`.run/P36/baseline/r22_sweep3.log`, 113 s). Census: `34,087 sites · marked 34,087 · UNMARKED 0`
  · `orphan 0` · `GTE levers 462 (100 via a variant macro, 362 direct) · marked 462` · **`per-TU asm macro definitions outside the GTE header:
  314 {launder 154 (SHB 142 + the compound ones), gte 150 (variants 64, header-bound homonyms 80+5, the unsigned two-statement macro 1),
  instruction 9 (RTP_SND), barrier 1 (COPY_TO_FAAC)}`** (was 9,540 at T1) · `lever_census --check: … 0 UNMARKED — OK`. Two of the
  refusals are a CENSUS BLIND SPOT, fixed next: a use of a macro defined in ANOTHER file is invisible to the census (it only knows a file's
  own `#define`s) — the prelude's `ENGINE_SHB` is used 7 times by `src/shared/ov/func_80165CA0.h` (7 launder levers uncounted; deleting the
  prelude's definition DIFFERED), and a unit's `SHB` used by an included header looked dead (the oracle refused the deletion — the
  instrument's blind spot never reached the bytes). Also found on the way: the tool's selftest wrote its two-signature fixture table over the
  real `canonical.json` (the census then classified every direct GTE statement against a fixture — 362 levers vanished twice); a selftest
  never writes an instrument's real state (`write=False`).

- **S98 — T5 CLOSE.** The census's cross-file blind spot fixed (a name defined in another file is classed by the majority definition's kind;
  selftest 24 sites): 10 launder sites appeared in two shared headers → `delever --apply --headers --rejudge`: `func_80165CA0.h A=DIFFERS
  B: removed 6 needed 2` (6 of the prelude's 7 `ENGINE_SHB` launders came off), `func_80166F58__3728db8a.h … needed 2 / refused 3` (its
  three `SHB` uses bind to each includer's own definition — header-bound, marked); R22 **`check-all: 218 passed, 0 failed of 218`**
  (`.run/P36/baseline/r22_t5_xfile.log`). **T5's verify line:** `lever_census`: **per-TU asm macro definitions outside the GTE header:
  9,540 → 314** {gte 150 = 64 lever variants (`_m`/`_v`, their uses marked) + 85 header-bound homonyms (an includer's name with another
  signature's bytes, used by an `h_text` header — the names phase's parameterized form) + 1 unsigned two-statement macro; launder 154 = 142
  `SHB` definitions each governing a marked NEEDED use + the 12 compound/private launders whose inner asm is a real steer; instruction 9
  (`RTP_SND`); barrier 1 (`COPY_TO_FAAC`)} — **0 canonical duplicates remain**; every remaining definition is tied to a surviving marked
  lever or to a homonym, and dies with it (T6/T7/names). `include/gte_inline.h`: 50 macros for what were 9,102 definitions; 575 direct
  statements now Sony-named calls; the GTE levers (462: 100 via a variant macro, 362 direct) are inside the number. **THE NUMBER: 34,091
  sites in 12,712 bodies (1,759 distinct) · marked 34,091 · UNMARKED 0 · orphans 0** — `lever_census --check: … 0 UNMARKED — OK`. T5's
  instrument findings for the record (nine, each fixed at its cause and selftested): the signature engine must be the build's own tail;
  Sony's header is names-only; scoped renames; header-bound homonyms; object-like macros; the marker on the first line; the stable
  canonical table (the header in the inventory); the census cache keyed on the tables; the selftest that wrote the real table; the
  cross-file names; the sweep's per-definition uses. Commits: `0bd784c64` (header), `145ab7719`/`666d4b5ae`/`02810debd` (batches),
  `5b6e1a2fe` (repair), `3b2c5178b`, `4bc987426` (sweep), this close. **T5 ☑.**

- **S98 — T6 opened: reconnaissance and the two feasibility probes (the design is in the 🛑 block §2; the build is the next session's).**
  The residue from the ledger (latest row per body): **12,970 bodies in 1,804 distinct after-hash classes** — 1,450 singletons, 80 classes
  of 134 copies (the overlay-wide functions), 75 pairs, 60 triples; the median exemplar needs ONE site (p90 4, max 25); 904 exemplars need
  only pins, 48 only `$0` pins; needed sites × copies: pin 20,643 · launder 4,635 · barrier 4,576 · keep-alive 2,000 · instruction 1,667 ·
  cast 1,509. The cookbook on the classes: the `$0` pin is the "$0-ADD OPAQUE COPY" (§34/§17 RC-12: `y = x + zr` emits a `move` CSE
  cannot see through — no plain-C spelling; T7's); §137 says a clean register swap is a TWO-COMPILE ARITHMETIC PROBLEM (read R and L from
  `cc1 -dl -dg`, `tools/alloc_table.py`), not a permuter job; §76 the allocno class through declaration scope. The permuter harness as
  built: `tools/permuter/run_masked.py` (the masked scorer rebound over decomp-permuter's Scorer: target.o and cand.o each hold ONE
  function, whole-.text compared), `tools/p16_permute.py` (`make_base_c` = comments → cpp WITHOUT includes → M2C_FIELD → `hide_asm` (asm
  statements and pins carried as decomp-permuter's own `#pragma _permuter b64literal`, decoded by its serializer, so cc1 sees the real
  asm) → typedefs; `setup(fn, draft, asm_subdir, klass)` builds base.c + target.o from `<asm_subdir>/<fn>.s` + settings.toml;
  `run_permuter(pd, secs, j)`; `winner_to_draft`), `tools/permuter_ils.py` (warm restarts from the best waypoint), `tools/permuter_weights.py`
  (profiles regalloc / schedule / cse / length via `render_settings_toml(fn, klass=…)`), `tools/permuter/compile.sh` (the faithful
  cpp→cc1→maspsx→as tail, no pad stage — .text only, fine). Per-function `.s` targets do NOT exist on disk for matched functions;
  `tools/verbatim_target_s.py --binary <alias> --fn <fn>` regenerates one from the extracted ROM image (`.run/verbatim_targets/<alias>/<fn>.s`,
  splat format — the independent oracle). **Probe 1:** `verbatim_target_s.py --binary ov_SC04_011 --fn func_80135D20` → `100 ins @
  0x80135D20 -> .run/verbatim_targets/ov_SC04_011/func_80135D20.s`. **Probe 2 (the base):** the TU text with the exemplar's body lever-free
  (delever's rung-A edits for that body: 1 site, the `$17` pin), every OTHER definition replaced by its prototype (`sc.scan_text` defs →
  the signature up to `{` + `;`), every `#include "../shared/…/func_*.h"` replaced by the prototypes of the definitions that header holds,
  `INCLUDE_ASM`/`INCLUDE_RODATA` lines dropped, then `mipsel-linux-gnu-cpp -P -lang-c -Iinclude -I<tu dir> -undef -Dmips -D__GNUC__=2
  -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C` (the real include paths — common.h, the prelude, engine_types.h, the GTE header
  expand; make_base_c's own cpp runs without includes and would lose them) → `p16_permute.make_base_c(expanded)` → `base.c` 5,218 lines,
  `defines_fn` True, 0 other bodies → `tools/permuter/compile.sh base.c -o base.o` rc 0 → `nm`: `T func_80135D20` alone (the callees `U`).
  The pipeline is proven; scratch under `.run/P36/permuter/probe/` (ignored).

- **S99 — T6 rung D BUILT and CALIBRATED: `tools/delever_permute.py` (the driver), the GTE-lever rewrite, four harness defects.**
  `tools/delever_permute.py` (`--plan`, `--prepare TU FN`, `--calibrate`, `--run`, `--bank`, `--status`, `--selftest`) drives the
  checkpoint's §2 pipeline per exemplar: delever's own rung-A rewrite of every REMOVABLE site of the body -> the TU isolated (every
  other definition to a prototype, every shared-header include to the prototypes it defines, `INCLUDE_ASM`/file-scope asm dropped) ->
  the build's own CPPFLAGS through `cpp -P` -> `draft.c`; the target regenerated from the ROM image in BOTH forms (`--gas` for
  `p16_permute.setup`'s `target.o`, the splat listing for `match_one`); `permuter_ils.py` with the weight profile from the NEEDED
  kinds; a winner banked through `delever --apply-body` + the GTE re-fold. Scratch and winners are keyed **alias+fn** (R48;
  `p16_permute.setup(outdir=)` and `permuter_ils --pd` added, defaults unchanged). **THE CONTROL, and it is new (R39/R56):** every
  attempt first compiles the body AS THE TREE HAS IT and requires `match_one` MATCH against the regenerated target — the harness must
  agree with the tree before it may judge a candidate — and then records the LEVER-FREE body's distance as the search's starting point.
  `--calibrate --limit 12`: **12 of 12 levered bodies MATCH** (ov_SC04_011, 37-279 ins) · lever-free distance **min 8 / median 78 /
  max 276** (`.run/P36/permuter/calibration.json`). The distance splits the population: where the lever was a pin the count is
  unchanged (8, 12, 19, 25); where it was a hand-placed `instruction` the C spelling changes the instruction COUNT (mine=103 vs
  target=106) and everything after it shifts (99-276) — `--max-start N` triages those as FAR with their number rather than spending a
  search on them. **The GTE levers are now on the ladder:** `("B", "gte-lever")` joined `delever.REMOVABLE` with a rewrite that resets a
  direct statement's clobbers to its canonical set, and points a variant-macro use (`gte_rt_m`) at its canonical macro — the target name
  derived from the variant definition's SIGNATURE, never its spelling (T5 named `gte_rt_m` after Sony's `gte_rt` while that signature's
  canonical name is `gte_rt_alt`). `gte_consolidate.canonical_match()` is now the one reader of the canonical table (R33), with
  `direct_rewrite` refactored onto it, selftest green. Offered to the ladder: **462 of 462** gte-lever sites (0 before, all refused).
  **Four harness defects, each found by running the thing and each a finding for the record:** (1) the splat listing is the WORD oracle
  and `mipsel-as` refuses its bare `addiu sp,sp,-152` exactly as decomp.me did in P34 — the permuter needs `verbatim_target_s --gas`
  (R98 in a second place); (2) pycparser rejects `__attribute__((packed, aligned(1)))` and decomp-permuter then REFUSES base.c and
  permutes nothing, so the draft's cpp defines the keyword away (a fidelity loss, recorded, never a correctness one — the bank gate is
  the object oracle); (3) `include/include_asm.h` injects `__asm__(".include \"include/labels.inc\"")` at file scope into every draft,
  and the permuter's own `compile.sh` already prepends `macro.inc` -> `Macro 'glabel' was already defined`; (4) an asm-LABEL clause
  (`extern void func_8005C324(…) __asm__("memcpy");`, 6,423 of them) is not an asm statement — a bare `__asm__(` scan ate one and left a
  headless K&R body whose next 60 declarations became parameters, so file-scope asm is taken from the CENSUS in the TU and, after cpp,
  only where the previous non-space character is `;` or `}`. A fifth was mine and is the reason the rule exists: the first "ASSEMBLED
  OK" was an empty file (the `.s` had not been written) — a known-true case, checked, and it lied until it was read.

- **S99 — T6 MEASURED: the rung-D campaign (5 of 16 exemplars) and rung R's first bank (134 of 134 bodies, R22 green).**
  **The two campaigns before this one were the instrument** (§454, accelerators P36 S99): the permuter's `target.o` had been
  assembled from `verbatim_target_s --gas`, and assembling a disassembly is a second toolchain — objdump prints the pseudo-instruction
  `move` for `addu rX,rY,$zero` and gas assembles it as `or` (24 wrong words in one 234-instruction function), and a listing's %hi/%lo
  pairs come back RESOLVED, with no relocation, against candidates that all carry one. **The scorer read 28 for a body that is
  byte-identical**, so score 0 was unreachable and every NO-MATCH was its own (`.run/P36/permuter/outcomes_broken_target.jsonl`, the two
  `campaign_d*_broken_target_*.log`). The control that names it in ~30 s is now `--positive-control`; the base score of the tree's own
  body is **0** since the target became the tree's OWN body compiled by the build's tail (the candidates' relocations by construction,
  with `match_one` against the ROM listing as the independent oracle that proves it, R34/R56). `verbatim_target_s --gas` now assembles,
  disassembles and compares itself word by word, `.word`-patches what does not reproduce (24 in that function) and REFUSES what still
  disagrees — it is the file pasted into decomp.me and it was wrong for every function containing a `move` (R98 in a second place).
  **Arm C, the first campaign with a trustworthy instrument** (16 exemplars, all ov_SC04_011 132-134-copy classes, 3 cycles x 240 s,
  4 at a time, `campaign_d3.log`): **`permuter: 5 of 16 exemplars matched lever-free in 0.69 h (665 of 2,131 bodies behind them)`**.
  The split is the STARTING DISTANCE, not the site count — closed: 8, 12, 19, 8, 29 mismatched instructions (5.9 s, 24.4 s, 314 s,
  651 s, 8.6 s); not closed: 25, 37, 50, 52, 70, 78, 99, 104, 105, 131, 276, every one improved a long way (78->9, 52->3, 50->3, 37->2)
  and none a wall. The far ones are all bodies where removing a hand-placed `instruction` changed the instruction COUNT
  (`mine=103 ins, target=106`). **The profile now follows the REGISTER a needed pin names** (callee-saved -> regalloc, caller-saved ->
  cse): the residual on func_80163EC8's `$2` pin is the operand order of one `&`, and regalloc weights `perm_commutative` 2.0 where cse
  weights it 40.0 — 8 of the 16 changed profile.
  **Every rung-D win is a small nameable shape, and each became a rung-R recipe the same session** (the flywheel; the permuter's own
  winner is pycparser-reprinted, and banking that would trade a lever for a readability regression in a phase whose purpose is
  readability): `flag = 0;` -> `do { flag = 0; } while (0);` (RC-5 scope) became **R7**, and a single-set temp inlined at its use
  (§501-R's S2 kill) became **R6**; **R5** (the operand order of one commutative operator) came from reading the `$2` residual.
  With R2/R3/R4 that is seven generators, each with selftest cases on a fixture whose answers are known by hand.
  **RUNG R's FIRST RUN BANKED THE CLASS THE PERMUTER HAD JUST CRACKED, MECHANICALLY:** `delever --recipes --label r1 --only
  func_80135D20 --cap 200` -> **`recipes: 134 of 134 bodies closed lever-free (134 NEEDED sites in the 134 drawn), 3243 compiles in
  6.0 min`**, every one `R7 do-while @<line>` — a ONE-LINE source change per body instead of a reprinted body, each judged on its own
  objects. **R22: `check-all: 218 passed, 0 failed of 218`.** The number: **34,091 -> 33,957 sites**, 33,957 marked, 0 UNMARKED.
  Also built: `delever --propagate TU FN` (a reshaped body's class re-banked by address remap — one crack, up to 134 bodies; a ledger
  REPLAY cannot do it, it replays a SITE SET) and `--apply-body` now records the before/after body text, which the remap needs and which
  exists nowhere else after the write.

- **S99 — THE LEVER SERIES IS NOW A TRACKED DELIVERABLE (Drew's directive, mid-T6): `docs/levers.md` + `tools/lever_progress.py`.**
  Drew: the pin/hint removal is not only work to finish — *"this will be a post 100% chart where we graph it and for the story,
  and for the decomp-architect deployable package and for the wiki … as well as what we should have done from the start to
  prevent this issue from creeping up on us post-100%, if that is optimal, or if it's optimal to leave them till post-100%
  cleanup"*, kept up to date **after each task**. Built: `docs/levers.md` (the taxonomy A–G; a GENERATED §2; how the levers got
  in, phase by phase; the ladder with each rung's measured yield; §5 the prevent-vs-defer argument; §6 what the wiki and the kit
  take from it) and `tools/lever_progress.py` (`--snapshot "<task>"` appends a milestone row with the census's totals and the
  tree's HEAD to `docs/lever-progress.tsv` — a census is a MOMENT and cannot be recovered later — and re-renders the document;
  the campaign half is derived from the ledger on every render, scored as state TRANSITIONS so the rung that FINISHES a body
  gets the credit and not only the rung that first judged it; `--check` refuses a series that is not this tree's). Reference-index
  row, SETUP row, dictionary row, and the memory `lever-removal-is-a-tracked-series`.
  **The story's numbers so far, all generated:** 21,061 sites removed or rewritten across 17,119 bodies by the mechanical rungs
  against 33,957 still standing — **38% of the class A/B population came off with no understanding at all** — plus rung R's first
  134. **The argument §5 makes from that:** blanket prevention would have stalled Phase 18 (the pin toolkit is why its waves went
  33% → 56% → 90%, and the knowledge to replace a pin did not exist until P23–P32), but *deferring silently* was the mistake —
  the rule worth carrying to day one is **"ban the silence, not the lever"**: a lever is allowed and is a marked, ledgered,
  published debt from the first bank, with a one-compile bank-time trial ("does it still match without this?") that would have
  refused more than a third of the population while the context was hot, and harvest→toolify applied to lever classes so a shape
  sweeps the banked population instead of the lever propagating with every family remap (1,758 distinct bodies became 12,578).

- **S99 — T6 CLOSE: both yield lines measured, 664 lever sites gone, R22 green at every step. T6 ☑.**
  **The two lines the plan asks for (R41):** `permuter: 5 of 16 exemplars matched lever-free in 0.69 h (665 of 2,131 bodies
  behind them)` and `recipes: 134 of 134 bodies closed lever-free (134 NEEDED sites in the 134 drawn), 3243 compiles in 6.0 min`.
  **Banked this session:** rung R's batch `r1` (134 bodies, every one `R7 do-while @<line>`, a ONE-LINE source change each) ·
  rung D's four remaining exemplars (`d1`, tidied and judged) · the propagation `p1`/`p1b` (132 + 130 + 131 + 132 = **525
  siblings**, 0 refused, each judged on its own objects). **34,091 → 33,427 sites** (19,982 pins + 13,445 asm) in 12,048 bodies,
  33,427 marked, 0 UNMARKED, 0 orphans; `check-all: 218 passed, 0 failed of 218` after every batch.
  **What T6 leaves for T7, stated rather than smoothed over:** rung R's recipe set does NOT reproduce the shape rung D found on
  func_80163EC8 — R6 was generalised from "assigned once, read once" to "dead after one read" (the lever was one of two
  assignments to `uVar5`) and still does not close it (154 candidates, 1.3 min, 0 hits), so that class was banked from the
  permuter's own winner instead. The 11 exemplars rung D did not close are seeds, not walls: every one improved (78→9, 52→3,
  50→3, 37→2, 131→35) and the ones that stayed far all removed a hand-placed `instruction` whose C spelling changed the
  instruction COUNT. A fleet-wide rung-R sweep is priced but not run: one body costs ~150 compiles / ~1.3 min at `--cap 200`
  when nothing hits, so the 12,000-body residue needs the run parallelised across TUs before it is affordable.
  **Instrument work banked with it:** `--recipes` is killable (its judge snapshots to inflight.json first — a killed run had
  left a candidate in `src/`); `--bank` skips a body another rung already closed (it had re-applied a permuter body over rung
  R's cleaner one-line version, restored through the oracle as `d1fix`); `--propagate` keys the class on the FIRST bank in a
  body's chain (the later row's before-hash describes a text only that body ever had — func_80163EC8 found 0 siblings until
  this was fixed, then 132); the permuter's winner is TIDIED before it is offered (pycparser's two-space indent and the corpse
  `;` where a statement was inlined away), with the tidy judged like any other candidate.

- **S100 — the free-bank sweep MEASURED, and it is spent at the current recipe set (zero tokens; cookbook §454a).**
  Rung R made TU-PARALLEL first (a worker owns a whole translation unit — the oracle writes each candidate to the real source
  path and names its scratch object after the object it builds; shared headers stay serial because two headers can share an
  includer's object; a file's bodies are judged BOTTOM-UP so a bank never shifts a body still to come; the in-flight map is
  per-file under the lock; ledger rows are appended per body, not at the end, so an interrupted sweep cannot leave a banked
  body whose row never landed). Candidates are also ordered by distance to the NEEDED site — the lever says where to look.
  **The measurement, same 300-body draw both times:** `recipes: 0 of 300 bodies closed lever-free … 12,110 compiles in 4.6 min`
  at `--cap 40`, and `0 of 300 … 17,140 compiles in 6.0 min` at `--cap 400`. **The cap was never the binding constraint** —
  17,140 compiles over 300 bodies is ~57 candidates each, so ten times the depth bought 42 % more candidates and closed
  nothing — and the instrument was cleared by hand on one body (`src/800.c CdReadSectorReadyCB`, one `$18` pin): every
  candidate COMPILES and returns DIFFERS, none errors out silently (R40).
  **What that establishes for T7's shape:** rung R is a REPLICATION engine (134 of 134 on a class whose shape rung D had just
  found, 6.0 min) and not a DISCOVERY engine (0 of 300 where no shape is known). So T7's real question is not "how many bodies"
  but **"how many distinct SHAPES are left"** — every shape discovered makes its whole class free, and the 134-copy classes at
  the head of the draw are worth 130 bodies per discovery. Throughput for planning: 82 bodies/min at 10 workers, 123 at 20
  (nice'd; Drew measured ~20-40 % CPU at 10 and asked twice for more), so a full-residue pass is ~2 h — affordable, but it buys
  nothing until the recipe set grows.

## 🛑 SESSION CHECKPOINT — S100 (2026-09-09): T0–T6 ☑ — all committed (this close on top of `72a9ab112`); NEXT = **the exemplar TRIAGE (Drew approved: hours of compute, zero tokens) and then a COMPUTE-ONLY guided search engine (§2/§3)**; **NO WAVES — T7's agents start only on Drew's direct approval in the session that runs them** | the number: **33,427 sites** (19,982 pins + 13,445 asm) in 12,048 bodies · marked 33,427 · UNMARKED 0 · orphans 0 · GTE levers 462 — `lever_census --check` OK · `lever_progress --check` OK (3 milestones)

### 0. How to use this block
A fresh session reads CLAUDE.md's load order, replays this block verbatim, confirms the effort (**Drew set `high` and prefers it for
this work — an explicit Workflow at high over Ultracode**, his words 2026-09-09) and executes §2. The tree is CLEAN at HEAD = this
close commit; nothing is in flight. **Resource etiquette, learned the hard way this session:** 24 nice'd workers made Drew's desktop
lag and he asked twice to stop; at 10 workers he measured ~20–40 % CPU and asked twice for more, and 20 ran fine at load 8/32. **Start
a long run at 10–20 workers with `nice`, tell him the number, and let him call it up or down.** Never a harness background task (the
low-memory guard kills them; the harness also backgrounds any foreground command over 120 s — fine for `make`, not for a campaign):
`setsid nohup nice -n 10 … &` + a `Monitor`. **`pkill -f` with a literal your own command line contains kills your shell (exit 144 —
it happened again this session); bracket a character.** The calibration is keyed to HEAD: EVERY commit stales it — recalibrate the
FULL set (`tools/delever_oracle.py --calibrate ov_SC04_011 ov_SC03_015 ov_SC03_014 main -j 16`, ~3 s; a single-alias calibration
fails its own completeness check). A killed batch: `tools/delever.py --restore`.

### 1. Where things stand — and the one measurement that reframes the phase
- **T0–T6 done.** T6's two yield lines: `permuter: 5 of 16 exemplars matched lever-free in 0.69 h (665 of 2,131 bodies behind them)`
  and `recipes: 134 of 134 bodies closed lever-free … 3243 compiles in 6.0 min`. Banked: rung R `r1` (134) · rung D `d1` (4) ·
  propagation `p1`/`p1b` (525 siblings, 0 refused). **34,091 → 33,427 sites**, R22 `218 passed, 0 failed of 218` after every batch.
- **THE S100 MEASUREMENT (cookbook §454a): the free-bank sweep is SPENT at the current recipe set.** Same 300-body draw:
  `0 of 300 … 12,110 compiles in 4.6 min` at `--cap 40`, and `0 of 300 … 17,140 compiles in 6.0 min` at `--cap 400`. **The cap was
  never binding** — 17,140 / 300 ≈ 57 candidates per body, so 10× the depth bought 42 % more candidates and closed nothing. The
  instrument was cleared by hand (`src/800.c CdReadSectorReadyCB`, one `$18` pin: every candidate COMPILES and returns DIFFERS,
  none errors out silently) and the locality ordering changed nothing. **Rung R is a REPLICATION engine (134/134 on a class whose
  shape rung D had just found) and NOT a discovery engine (0/300 where no shape is known).** So the number that prices T7 is not
  12,048 bodies but **how many distinct SHAPES remain** — each discovery makes its whole class free, and the head of the draw is
  80 classes of 134 copies. Throughput for planning: 82 bodies/min at 10 workers, 123 at 20; a full-residue rung-R pass ≈ 2 h.
- **THE INSTRUMENT LESSON THAT COST TWO CAMPAIGNS** (cookbook §454): the permuter's target had been ASSEMBLED FROM A DISASSEMBLY
  LISTING and scored **28 for a byte-identical body**, so score 0 was unreachable and two campaigns reported "0 of 16" about a
  healthy population. Run `tools/delever_permute.py --positive-control TU FN` (base score must be 0) before believing ANY yield.

### 2. NEXT, and Drew approved the compute for it: the exemplar TRIAGE (zero tokens)
Rung D's evidence is sharp: everything that closed started **≤ 29 mismatched instructions** from the target, everything **≥ 37** did
not (25, 37, 50, 52, 70, 78, 99, 104, 105, 131, 276 — all improved, none a wall). So measure that number for the WHOLE residue and
work the close tail first.
1. Parallelise `delever_permute.cmd_calibrate` over exemplars (a `ThreadPoolExecutor`; `prepare()` writes only inside its own
   `alias__fn` scratch dir and `match_one` runs in its own temp dir, so exemplars are independent — unlike rung R, which needs TU
   ownership because the oracle writes into the tree).
2. Run it over all ~1,795 residue classes (`exemplars()` with no limit): prepare + two `closeness()` calls each ≈ 10–20 s, so
   **~30 min at 20 workers**. Record the distribution into `.run/P36/permuter/triage.json` and a `lever_progress`-style table.
3. That distribution IS T7's price: how many classes sit in the tractable band, and how many bodies stand behind them.
Then run rung D (`delever_permute --run`) on the close band, ordered by distance (`--max-start 35` triages the rest as FAR with
their number), 4–6 exemplars at a time — zero tokens, and **every shape it finds becomes a rung-R recipe that then sweeps its class
for free** (that is how R5/R6/R7 were born, and it is the only thing that moves rung R's 0/300).

### 3. The compute-only engine Drew asked for ("a fancier permuter, focused on pin pulling and C shape matching")
**The one design flaw the S100 measurement exposes: rung R is BLIND.** It generates ~57 candidates, asks the oracle "IDENTICAL?" and
throws away everything else. The oracle also knows the DISTANCE (`masked_diff` gives a mismatch count, which is what `match_one` and
the permuter's scorer both use) — so the same compute could hill-climb instead of guessing. The engine to build:
1. **Score, don't test.** Every candidate scored by masked mismatch count; keep the best; re-expand from it. One-move candidates that
   individually fail may compose — 0/300 on singles says nothing about pairs.
2. **Classify the residual, then choose the moves.** `masked_diff` already distinguishes: same opcodes with swapped registers
   (REG-SWAP → declaration order, commutative swap, temp introduce/inline), different instruction COUNT (→ add/remove a temp, split
   or merge an expression — this is the class where removing a hand-placed `instruction` lever shifted everything), same multiset in
   a different order (SCHED → block wrap, statement reorder, chained assignment). Today's profile choice is a crude version of this
   (it follows the pinned REGISTER: callee-saved → regalloc, caller-saved → cse).
3. **Search near the diff.** Candidates are already ordered by distance to the NEEDED site; order them by distance to the DIFFERING
   INSTRUCTION instead once the residual is classified.
4. **Two- and three-move combinations**, guided by (2), budgeted by (1)'s gradient. ~57 singles → ~1,600 pairs ≈ 7 min/body at
   0.25 s a compile: affordable for a close-band class worth 130 bodies, not for the whole residue.
**Drew's question — a Fable agent, or a fresh Fable session, to design this?** My recommendation, recorded for the next session:
**build the engine here** (it is engineering on top of measurements that live in this phase's log and would have to be re-established
from scratch — and this session showed how easily a wrong conclusion follows from a mis-measured instrument), and **give a Fable agent
the compiler-internals question only**: *for each residual class, which SOURCE-level moves can possibly fix it in gcc 2.7.2* — read
from the compiler source and `docs/gcc-2.7.2-map/`, briefed with the measured facts above, with **every claim verified against the
bytes by the engine itself** (the `fable-agents-for-lane-tooling` memory: brief with measured facts + a doc path, then verify).
That is exactly how P23's §31 codegen map was produced, and it is the highest-value thing a model can do here that compute cannot.

### 4. Gotchas known before any work
Everything in the T3/T4/T5 lists, plus: a disassembly listing is not a target (§454); `--only <fn>` in `--recipes` draws EVERY body of
that name across the fleet (that is why `r1` banked a whole class in one run); `--propagate` keys the class on the FIRST bank in a
body's chain; rung R needs TU ownership and serial headers, judges a file's bodies BOTTOM-UP, and appends its ledger rows per body;
`lever_progress --check` fails when the series is not this tree's; **`docs/levers.md` + `tools/lever_progress.py --snapshot "<task>"`
are updated after EVERY task that changes the count** (Drew's directive: the post-100 % chart, the story, the wiki, and the kit's
day-one rule "ban the silence, not the lever"); the LoRA idea is PARKED by Drew for the endgame — a gcc-2.7.2 LoRA trained on the
final clean asm/C pairs, released for other projects to use when cracking.


## (superseded) SESSION CHECKPOINT — S99 (2026-09-09): T0–T5 ☑ **T6 ☑** — all committed (this close on top of `1c2355054`); NEXT = **T7, the reshaping waves — and T7 STARTS ONLY ON DREW'S DIRECT APPROVAL IN THE SESSION THAT RUNS IT** (his words, twice: the `/effort ultracode` toggle is NOT approval); until he gives it, the drawable work is a PARALLELISED rung-R sweep (§2) | the number: **33,427 sites** (19,982 pins + 13,445 asm) in 12,048 bodies · marked 33,427 · UNMARKED 0 · orphans 0 · GTE levers 462 — `lever_census --check` OK · `lever_progress --check` OK (3 milestones)

### 0. How to use this block
A fresh session reads CLAUDE.md's load order, replays this block verbatim, confirms the effort (T7's coordinator at Max, the waves at
Ultracode — Drew toggles, R27) and executes §2. The tree is clean at HEAD = this close commit. **Never run a long job as a harness
background task** (the low-memory guard kills them; the harness also backgrounds any foreground command over 120 s, which is fine for
`make` but not for a campaign) — run campaigns DETACHED with `setsid nohup … &` and a `Monitor` on the log. **The calibration is keyed to
HEAD: EVERY commit stales it** — `tools/delever_oracle.py --calibrate ov_SC04_011 ov_SC03_015 ov_SC03_014 main -j 16` (3 s) before any
judging, and calibrate the FULL set: a single-alias calibration fails its own completeness check. A killed batch: `tools/delever.py
--restore`.

### 1. Where things stand
- **Done: T0–T6.** T6 delivered both yield lines the plan asks for: `permuter: 5 of 16 exemplars matched lever-free in 0.69 h (665 of
  2,131 bodies behind them)` and `recipes: 134 of 134 bodies closed lever-free (134 NEEDED sites in the 134 drawn), 3243 compiles in
  6.0 min`. Banked: rung R `r1` (134 bodies) · rung D `d1` (4 exemplars) · propagation `p1`/`p1b` (525 siblings, 0 refused).
  **34,091 → 33,427 sites**; `check-all: 218 passed, 0 failed of 218` after every batch.
- **THE INSTRUMENT LESSON THAT COST TWO CAMPAIGNS** (cookbook §454, accelerators P36 S99): the permuter's target had been ASSEMBLED
  FROM A DISASSEMBLY LISTING and scored **28 for a byte-identical body**, so score 0 was unreachable and two campaigns reported "0 of
  16" about a healthy population. The target is now the tree's OWN body compiled by the build's tail (`--positive-control` reads base
  score 0). **Run `tools/delever_permute.py --positive-control TU FN` before believing any future yield.**
- **Instruments (SETUP + dictionary rows, kit corpus regenerated, `tool_census --check: OK`):** `tools/delever.py` (+ `--recipes`
  rung R with R2/R3/R4/R5/R6/R7, `--propagate TU FN`, `--cap`, `--control`), `tools/delever_permute.py` (`--plan`, `--prepare`,
  `--positive-control`, `--calibrate`, `--run`, `--bank`, `--status`, `--selftest`), `tools/lever_progress.py` (the series behind
  `docs/levers.md`), `tools/delever_oracle.py`, `tools/lever_census.py`, `tools/gte_consolidate.py`, `tools/delever_cycle.sh`.
- **Drew's directive, mid-session:** the lever count over time is a DELIVERABLE — `docs/levers.md` + `docs/lever-progress.tsv` +
  `tools/lever_progress.py --snapshot "<task>"` **after every task that changes the count** (the post-100% chart, the story, a wiki
  page, and the kit's day-one rule). §5 of that document is the prevent-vs-defer argument, written from the generated numbers:
  **38% of the class A/B population came off with no understanding at all**, so the rule is *ban the silence, not the lever*.
- **Environment:** WSL2, `~/bfm-decomp`, `.venv`; R22 clean fleet ≈ 115 s; the census ≈ 35 s; `make kit-corpus` ≈ 25 s; 16 cores.

### 2. What is drawable WITHOUT Drew's wave approval — the parallelised rung-R sweep
Rung R is serial today: one body costs ~150 compiles / ~1.3 min at `--cap 200` when nothing hits, so the ~12,000-body residue is
unaffordable as written. Make `recipes()` run TU-parallel the way `apply_batch` already does (a `ThreadPoolExecutor` over files, one
worker owning a whole TU — two workers must never share a TU, and the oracle writes the candidate into the tree to compile it), then:
1. `--cap 40` first over the whole residue (the targeted recipes R5/R6 and a few R7s) to measure the cheap yield with a denominator;
2. `--cap 200` on what the cheap pass leaves, drawn by class size so a hit is worth 130 bodies;
3. after each batch: R22 → `lever_census --sites --check` → `lever_progress --snapshot "<label>"` → commit (R42, R101).
Also drawable: more rung-D exemplars (`delever_permute --run --limit N --workers 4 --secs 240 --cycles 3`), ordered by the STARTING
DISTANCE the calibration prints — everything that closed started ≤ 29 mismatched instructions, everything ≥ 37 did not; `--max-start 35`
triages the rest as FAR with their number.

### 3. T7, when Drew approves it
One agent per residue exemplar with the pack (the body, the target listing, the ledger's NEEDED sites with the register each names,
`alloc_table.py` on the real TU, §501-E/P/R + §17 + **§454**, `journal_notes`, "no lever of any class may remain", deliverable-first
R67); `delever --apply-body` judges every draft on the bytes and `--propagate` spreads it to the class. The harvest → toolify gate
between waves is not optional: every shape an agent finds becomes a rung-R recipe (R5/R6/R7 all came from rung D this way) and then
sweeps the population for free.

### 4. Gotchas known before any work
Everything in the T3/T4/T5 lists, plus: a disassembly listing is not a target (§454); `--only <fn>` in `--recipes` draws EVERY body of
that name across the fleet, which is why `r1` banked a whole class in one run; the class key for `--propagate` is the FIRST bank in a
body's chain; `pgrep -cf` matching your own command line counts itself (R79's cousin); the harness backgrounds any command over 120 s;
`lever_progress --check` fails when the series is not this tree's.


## (superseded) SESSION CHECKPOINT — S98 (2026-09-09): T0 ☑ T1 ☑ T1b ☑ T2 ☑ T3 ☑ T4 ☑ T5 ☑ — all committed (this close on top of `4bc987426`); NEXT = T6 BUILD: `tools/delever_permute.py` per §2 (the design is settled and its pipeline proven by two probes — the T6 log entry); S98 ended here at 90 % context | the number: 34,091 sites in 12,712 bodies (1,759 distinct) · marked 34,091 · UNMARKED 0 · orphans 0 · GTE levers 462 · per-TU asm macro definitions 314 (0 canonical duplicates) — `lever_census --check` OK

### 0. How to use this block
A fresh session reads CLAUDE.md's load order, replays this block verbatim, confirms the effort (T6/T8/T9 xHigh per the plan; S98 ran at Max —
Drew toggles, R27) and executes §2. The tree is clean at HEAD = this close commit. **T7 (the Ultracode reshaping waves) starts ONLY on
Drew's direct approval in the session that would run them** (his words, 2026-09-09, decisions). **Never run a long job as a harness
background task** (its low-memory guard kills them with 22 GB free; it also killed a 10-minute foreground chain that was moved to the
background — keep foreground chains under ~8 min, run cycles DETACHED with `setsid nohup … &` and a `Monitor` on the log). A killed
batch: `tools/delever.py --restore` (drops its ledger rows). The calibration is keyed to HEAD: EVERY commit stales it — recalibrate
(`tools/delever_oracle.py --calibrate ov_SC04_011 ov_SC03_015 ov_SC03_014 main -j 16`, 3 s) before any judging.

### 1. Where things stand
- **Done:** T0–T5. T4's campaign judged every body (16,334; 3,341 lever-free; 21,063 of 56,445 sites removed; the T4 close entry has the
  tables). T5 consolidated the GTE coprocessor asm: `include/gte_inline.h` (50 canonical macros, Sony's names for 41, included from
  `include/common.h`), 8,951 per-TU definitions deleted, 629 clobber variants byte-identical without the clobber, 575 direct statements
  turned into calls, 274 dead launder macros swept; the census gained the `gte-lever` class (INSIDE the number), per-TU definition
  counts, cross-file macro names, orphan markers, the controls keyed on their T1 hashes.
- **THE NUMBER: 34,091 sites (33,625 pins/asm + 462 GTE levers + 4 launders the cross-file fix surfaced) in 12,712 bodies (1,759
  distinct); 34,091 marked; 0 UNMARKED; 0 orphans.** The residue for T6/T7 = every marked site: pins ≈ 20,600, barriers ≈ 4,570,
  launders ≈ 4,640, keep-alives 2,000, instructions ≈ 1,670, refused/deferred ≈ 100, GTE levers 462. Re-derive: `.venv/bin/python
  tools/lever_census.py --check -j 16` (must print `… 0 UNMARKED — OK`, no ORPHAN line); `tools/delever.py --status`;
  `tools/gte_consolidate.py --status` (645 consolidated, 6 unchanged, 0 refused).
- **Instruments (SETUP + dictionary rows, kit corpus, `tool_census --check: OK`):** `tools/delever.py` (`--plan`, `--apply`, `--restore`,
  `--scrub [--dirty-ok]`, `--status`, `--apply-body TU FN FILE --label L --rung D|E`, `--redraw`, `--rejudge`, `--selftest`, `--probe`);
  `tools/delever_cycle.sh` (`[TASK] [FINISH=label] [REDRAW] START END [BATCH] [tus|headers|gte] [ONLY]`); `tools/delever_oracle.py`;
  `tools/lever_census.py`; `tools/gte_consolidate.py` (`--inventory`, `--header`, `--apply`, `--sweep`, `--remark`, `--status`,
  `--selftest`). The ledger `.run/P36/delever/ledger.jsonl` (tracked): body rows (rung A/B/replay), gte rows, sweep/scrub/remark rows.
- **Environment:** WSL2, `~/bfm-decomp`, `.venv`; R22 clean fleet run ≈ 115 s; the census ≈ 35 s (a full rewalk when a tool or a table
  changes); `make report BINARY=main` ≈ 285 s; `make kit-corpus` ≈ 25 s; 16 cores; 31 GB RAM; ~30 GB disk free.

### 2. T6 — rung R (mechanical shape recipes) + rung D (the permuter on the residue exemplars) (xHigh) — DESIGN SETTLED, BUILD NEXT
The two yield lines to report (R41): `recipes: <k> of <r> NEEDED sites removed` · `permuter: <k> of <r> exemplars matched lever-free in <t> h`.
**Rung D first (the bigger lever; its pipeline is proven by the two probes in the T6 log entry).** Build `tools/delever_permute.py`:
1. `--plan`: the exemplars from the ledger (`dl.load_ledger()`, latest row per (tu, fn), verdict RESIDUE, grouped by `nhash_after`, one
   exemplar per class = the first (tu, fn); order: copies desc, then needed sites asc; skip classes in `.run/P36/permuter/outcomes.jsonl`);
   `--only`, `--limit`.
2. Per exemplar `prepare(tu, fn)` EXACTLY as probe 2: (a) the lever-free TU text = `dl.site_edits` for every REMOVABLE site of the body
   (a site that REFUSES → the exemplar is `UNSTRIPPABLE`, skipped and recorded); a `gte-lever` site (kind not in `dl.REMOVABLE` yet) should
   get a rewrite too: `gte_consolidate.set_clobbers(statement, canonical clobbers)` — add ("B", "gte-lever") to delever's rewrite table
   (the canonical from `.run/P36/gte/canonical.json` by the statement's signature) so rung A/B in delever can judge direct GTE levers as
   well (T5 tried only the definitions); (b) every other definition → prototype; (c) every `#include "…/shared/…/func_*.h"` → the
   prototypes of that header's definitions (a static function's prototype keeps `static`); (d) `INCLUDE_ASM`/`INCLUDE_RODATA` lines and
   file-scope `__asm__` blocks dropped; (e) cpp with `-Iinclude -I<tu dir>` and the build's -D flags, `-P`; (f) write the expanded text
   as the DRAFT `.run/P36/permuter/<alias>__<fn>/draft.c`; (g) the target: `tools/verbatim_target_s.py --binary <alias> --fn <fn>` →
   copy `.run/verbatim_targets/<alias>/<fn>.s` into the scratch dir (p16's `setup(fn, draft_c, asm_subdir=<scratch dir>)` reads
   `<asm_subdir>/<fn>.s`); the alias = the body's first alias (`aliases[0]`; a shared header's body → its first includer's alias);
   (h) klass from the needed-site mix for `permuter_weights`: pins only → "REGALLOC-PERM"; barriers/launders/keep-alives → "SCHEDULE-REORDER";
   mixed → "REGALLOC-PERM"; (i) `permuter_ils.py <fn> --draft draft.c --asm-subdir <scratch> --klass <k> --cycles 3 --secs 240 --j <J>`
   (its `setup` runs `make_base_c` on the draft — already expanded, so its include-less cpp changes nothing — and asserts `defines_fn`;
   the winner lands in `.run/permuter-winners/<fn>.c` — KEY BY alias+fn (R48): copy it to the scratch dir at once).
3. A winner → `p16_permute.winner_to_draft` → extract the function's definition span → write `<scratch>/body.c` → `tools/delever.py
   --apply-body <tu> <fn> <scratch>/body.c --label d<k> --rung D --dirty-ok` (refused if a class A/B lever remains; the copies replay
   through the ledger when their class is drawn again: `delever --apply --redraw RESIDUE --only …` or the exemplar's copies by nhash) →
   then `tools/gte_consolidate.py --apply --only <tu> --rejudge --label d<k>g` re-folds the cpp-expanded GTE asm in that function into
   canonical calls (the winner is macro-expanded: readability regained by the re-fold; `#define`d constants stay expanded — the names
   phase) → the batch's R22 → commit (the cycle's FINISH mode or by hand with the log line + headline, R101).
4. The campaign: DETACHED (`setsid nohup … &` + a `Monitor`), K exemplars concurrently with `-j 16/K` each, `--secs 240 --cycles 3` per
   exemplar as the first measurement on ~16 exemplars (the 134-copy classes first: one match banks 134 bodies), then price the rest
   from the measured yield (the P29 sweep's honest prior: ~3 in 8 for small residuals). `outcomes.jsonl` = exemplar, class copies, needed
   sites, klass, secs, cycles, best score, winner path, banked commit.
**Rung R second (cheap, measured on samples, R37):** in `tools/delever.py --recipes --only …`: per RESIDUE body, candidates from
(R2) the declaration-ORDER permutations of the pinned callee-saved variables (§76/§501-R: the allocation order is the bank; ≤ 4 pins →
all 24 orders, else 24 random) applied to the lever-free text; (R3) a pin with an initializer split into declaration + assignment, or the
declaration moved next to its first use (§17a); each candidate judged by the oracle; the first IDENTICAL replaces the body (its ledger row
updated, its markers consumed); negative-control each recipe on a LEVER-FREE body first (must stay identical, R39). Report `recipes: k of r`.
Then the T6 log entry (both lines with denominators), `make report BINARY=main`, the checkpoint refresh, commit.

### 3. Numbers to re-derive, never trust
The T2 probe's rates → T4's measured rates → T5 changed the population (the number went UP by the 462 GTE levers and 4 surfaced
launders, DOWN by 6). Published numbers: `make report BINARY=main` (R75) — last run at the T4 close; run it at the T6 close.

### 4. Gotchas known before any work
Everything in the T3/T4 lists, plus T5's: a macro name is redefined between functions (scope every use to the definition above it); a
shared header's macro use binds to the INCLUDER's definition (the 20 `h_text` headers; a homonym is kept, not deleted); an object-like
macro's uses carry no parentheses; a marker goes at the end of a statement's FIRST line; a tool's selftest must never write the tool's
real tables; a census cache is keyed on every table it classifies with; never two `make`s at once; never edit a running bash script.

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
