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

## 🛑 SESSION CHECKPOINT — S98 (2026-09-09): T0 ☑ T1 ☑ T1b ☑ T2 ☑ T3 ☑ — all committed (T3 = `39e3e1851` tools, `cd24727dd` + `7ee458dd7` the ov_SC04_011 batches, this close); NEXT = T4 the mechanical campaign: `tools/delever_cycle.sh` over the whole population (TUs then headers), unattended, one commit per batch, R22 every batch | the number: 53,033 sites in 15,638 bodies (2,246 distinct), 310 marked, 0 orphans | last batch `tus7` on 3e60fdf41: THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 36,764 sites in 13,224 bodies (2,199 distinct) · marked !FAKE 29,045 · UNMARKED 7,719

### 0. How to use this block
A fresh session reads CLAUDE.md's load order, replays this block verbatim, confirms the effort (T4/T5/T6/T8/T9 are xHigh per the plan, Max is
what S98 ran at — Drew toggles, R27) and executes §2. The tree is clean at HEAD = this close commit (`git log --oneline -4` shows it above
`7ee458dd7`, `cd24727dd`, `39e3e1851`). The headless Ghidra MCP is unused this phase (the SessionStart hook starts it; stop it with the sentinel
before a checkpoint commit, R23). Drew pushes (R6). **T7 (the Ultracode reshaping waves) starts ONLY on Drew's direct approval in the session
that would run them** — his words, 2026-09-09, in the decisions section; the R27 toggle is necessary, not sufficient.

### 1. Where things stand
- **Done, committed:** gate 1 (2026-09-09, the decisions above); T0 (`63b886626`, R22 218/218); T1 (`357f8a1ed`, `tools/lever_census.py`); T1b
  (`a1407bdfc`, the manifest's in-function form, 49 rows); T2 (`617f29e30`, `tools/delever_oracle.py` + the probe); **T3** (`39e3e1851` the campaign
  tool + cycle; `cd24727dd` batch `t3_tus1` = ov_SC04_011's 18 TUs, 176 bodies, 215 sites removed, R22 green; `7ee458dd7` batch `t3_tus2` = the
  redraw of the one refused body; this close = the scrub of 2 orphan markers + the tool fixes + the docs, R22 green).
- **The number:** `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 53,033 sites in 15,638 bodies (2,246 distinct) · marked !FAKE 310 ·
  UNMARKED 52,723` · `orphan !FAKE markers: 0` (was 53,234 / 15,679 / 2,227 at T1b; the census's `distinct` RISES while copies of an edited
  class are still unjudged — expected). Re-derive: `.venv/bin/python tools/lever_census.py --sites -j 16` (30–35 s; the JSON carries `head`,
  `src_stamp`, `orphan_markers`; the walk cache is keyed on the tool's own hash). `lever_census --check` FAILS until T4 has judged everything
  (0 UNMARKED is the T8 gate) — it must NOT fail on orphans at any commit.
- **The first real sample (ov_SC04_011, R41):** 25 % of bodies lever-free after rungs A+B, 40 % of sites removed, 100 % of NEEDED verdicts
  DIFFERS (0 compile errors, 0 crashes since the launder-assignment rewrite); needed by kind: pin 194/373, launder 46/49, barrier 40/49,
  keepalive 13/18, instruction 14/18, cast 11/23. The T2 probe's numbers (43 % / 19 %) were measured with the assignment-launders deleted.
- **The ledger** `.run/P36/delever/ledger.jsonl` (tracked): 176 + 2 body rows + 1 scrub row; `tools/delever.py --status` prints the totals.
  "Done" = the body's current nhash is some row's `nhash_after`; a body whose nhash is a row's `nhash_before` REPLAYS that row (1 compile);
  `--redraw REFUSED NOTHING-USABLE` draws refused bodies again after a tool fix; `--rejudge` draws everything.
- **Instruments (all with SETUP rows + dictionary rows, kit corpus regenerated, `tool_census --check: OK`):** `tools/delever.py` (`--plan`,
  `--apply --batch N --label L [--headers] [--only …] [--redraw …] [-j 12]`, `--restore`, `--scrub`, `--status`, `--apply-body`, `--selftest`,
  `--probe`), `tools/delever_cycle.sh` (`[LABEL_PREFIX=…] [TASK=T4] [REDRAW=…] START END [BATCH=300] [tus|headers] [ONLY=…]`),
  `tools/delever_oracle.py` (`--calibrate ov_SC04_011 ov_SC03_015 ov_SC03_014 main -j 16` 2.4–3.9 s; keyed to HEAD — EVERY commit stales it; the
  cycle recalibrates itself), `tools/lever_census.py` (`--sites`, `--check [--strict]`, `--selftest`). Selftests: `delever --selftest: OK — 15 sites
  in the exemplar, 1 refused rewrite(s), ladder RESIDUE (15 compiles), replay replay (1 compile), markers 5`; `lever_census --selftest: OK — 23
  sites, 2 defs, 2 asm macros`.
- **No src/ is dirty at this commit;** `.run/P36/delever/inflight.json` (ignored) may exist from the last batch — `--apply` deletes it on a clean
  tree; a crash mid-batch leaves files modified → `tools/delever.py --restore` (never git checkout, R102).
- **Environment:** WSL2, `~/bfm-decomp`, `.venv`; R22 clean fleet run 90–145 s; the census 30–35 s; `make kit-corpus` ≈ 25 s (a NEW tool must be
  `git add`ed first); 16 cores; 31 GB RAM; ~32 GB disk free; the harness's foreground cap is 10 min — run the cycle in the BACKGROUND with its log.

### 2. T4 — the mechanical campaign (xHigh; unattended cycles; P3 — no permission stops between batches)
1. Preflight: `git status --short` empty; `.venv/bin/python tools/delever.py --plan --batch 300` (prints `N of M drawable files …`; the census is
   rerun by the tool when its src stamp is stale); `--plan --headers --batch 200` for the header count.
2. The TU campaign, in the background with its log: `TASK=T4 tools/delever_cycle.sh 1 10 300 tus > .run/P36/delever/cycle_t4_tus.log 2>&1`
   (labels `tus1..tus10`; each batch: apply ≈ 3–8 min → R22 ≈ 2 min → census ≈ 0.5 min → log entry + headline → commit). It stops cleanly
   with `nothing drawable` when the TUs are exhausted, or on the first red (`cycle: …` names it; the files stay in place → inspect the apply
   log, fix the tool, `delever --restore`, recommit nothing, rerun). Expect ~9 batches ≈ 1–1.5 h.
3. The header campaign: `TASK=T4 tools/delever_cycle.sh 1 3 200 headers > .run/P36/delever/cycle_t4_hdr.log 2>&1` (labels `headers1..`; serial
   per header, includers in parallel; a header's greedy runs on ONE includer and the final on ALL — an `h_text` header (38, byte-variant per
   binary) that disagrees reruns the greedy on all includers, logged `does not hold on every includer`).
4. Stragglers: `--redraw REFUSED NOTHING-USABLE` after any tool fix (`REDRAW="REFUSED NOTHING-USABLE" tools/delever_cycle.sh …`); a
   COMBINATION-FAILED file (the cycle stops on it: `final X/Y`) is a tool defect to fix, never a body to skip.
5. After the last batch: `tools/delever.py --status`; `lever_census --check` (0 orphans; UNMARKED = the sites of bodies never drawn — should be
   0 once every file is judged, else find them with `--plan`); the T4 log entry = the totals with denominators (bodies lever-free / residue,
   sites removed / needed / refused by kind, replays and disagreements, compiles and wall) and the residue's class mix for T5/T6; the P6
   rules check after T4 (S98 did one after T3); then the checkpoint refresh.
Gotchas already paid for: the cycle greps `delever: batch …` WITHOUT a `^` anchor (the log line is timestamped) and refuses an EMPTY verify
line; the census line is `THE PHASE'S NUMBER…`; a body whose zero-register variable is used inside another site's statement composes; a
removed site consumes its trailing marker (an orphan marker is a `--check` failure and a `--scrub` job); the census cache is keyed on the
tool's hash; a compound macro use is REFUSED (its marker says `T5`) — T5 edits the `#define`; the 13 asm-bodies are DEFERRED with a `T7`
marker; class C/D survivors are never marked (decision 3) — the ledger is their record; `-O0` TUs are judged like any other (`o0` in the row).

### 3. Numbers to re-derive, never trust
`docs/progress.json` `counts.levers` and the README sentence are generated from `.run/P36/census/lever_census.json` — rerun the census, then
`make report BINARY=main` (≈ 226 s; rewrites `docs/story-timeline.md` too — commit it with the rest) before any commit that quotes a number
in a published document (R75); the batch commits quote the census line only. The gate-1 population table is superseded by T1; the T2 probe's
percentages by the ov_SC04_011 sample (§1).

### 4. Gotchas known before any work
The oracle must not write `build/`; objects embed the source path (compile in place, restore from the in-memory snapshot); the calibration is
keyed to HEAD + the Makefile/config stamp; `compile_only.py` is not faithful (no pad stage); a dotfile probe under `src/` refuses the cycle;
a shared header's edit reaches up to 136 binaries — the final verifies every includer; `SHB` may be used by an included header
(`src/shared/ov/func_80166F58__3728db8a.h`); never `git checkout` to restore (R102); `tool_census --check` refuses an UNTRACKED tool — `git
add` a new tool before `make kit-corpus`; two concurrent `make` invocations in one tree are a race — never run `make kit-corpus` (or a report)
while a cycle's R22 runs.

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
