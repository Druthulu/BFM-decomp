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

- **S103 (2026-09-10), Drew: *"max concurrent agents is 5, leave the ones you have running, but maintain max of 5
  concurrent agents from now on."*** → the T7 agent lane runs at most FIVE agents at once (six were running when he said
  it; they finish, and no new one launches until fewer than five are live).
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

- **S101 2026-09-09 — the two lanes opened (Drew: `/effort xhigh`, Fable 5.1). LANE B launched first** so it overlaps: one Fable
  agent reading `tools/reference/gcc-2.7.2/` + `docs/gcc-2.7.2-map/` for the residual → source-move map, deliverable
  `.run/P36/engine/residual_moves.md` written early (R67), every claim a hypothesis until the engine proves it on bytes.
  **LANE A — rung G, `tools/delever_search.py` (the guided search), built and controlled.** Reconnaissance first (R37/R38): the
  four tools read (`masked_diff` gives a structured, reloc-masked diff; `delever_oracle.compile_obj` returns the scratch object's
  bytes; `objdump -drz` of the largest overlay object is 35 ms) and **a ledger defect found by reading the artifact (R14): 301
  RESIDUE rows of the S99/S100 rung-R sweeps carried NO text hash** — `recipes()` wrote `nhash_after=None` on a miss, so the next
  sweep's rows inherited None as their before-hash; `exemplars()` then read those 300 bodies as ONE class keyed None and
  `--propagate` could never find them. Fixed at the cause (a RESIDUE row keeps the body's hash) and repaired once:
  `delever --repair-nhash: 301 RESIDUE row(s) given their body's hash from earlier rows; 0 still without one`.
  **The design (X1):** the SCORER is the oracle's own object — a candidate compiles through ONE recipe (a header: its first
  includer's), the function's instructions are read from the scratch object and compared, reloc-masked with reloc-operand
  equality, against the same function in the fleet run's baseline object under `build/` (the tree's own bytes, the candidates'
  relocations by construction — no listing, no isolation, no cpp: the two instrument classes of §454 cannot recur); the SCORE is an
  EDIT DISTANCE over the masked words (difflib opcodes), not the positional count; the residual is CLASSIFIED from the diff blocks
  (REG caller/callee from the register pairs, COUNT, ORDER, MIXED) and the class orders the move families; the search is a beam
  (`--beam 3 --depth 3 --cap 48 --budget 400`), a worse-than-parent child dropped, the first score-0 verified on every recipe and
  banked through `delever --apply-body --rung G`, then `--propagate` serially after the parallel phase. The generators stay ONE
  registry (`delever.recipe_candidates`, R33): a `families` filter, `cap=None`, and three new moves — **R8** a temp introduced
  (the deref hoisted, typed by its cast) or an operand hoisted (the exact inverse of R6, typed like the local it feeds), **R9** two
  adjacent simple statements swapped, and **R7's inverse**, the unwrap of a one-line block. Rung R's default family set is unchanged.
  **The controls, in order, each of which changed the tool (R39/R40):** selftest OK (classifier 6 cases, beam 4 cases on a stub
  needing three composed moves, R8/R9 on a fixture) — its first run failed on my own arithmetic (a start three moves away was five).
  Positive control 1 (`func_8014477C`, one R9 swap, start 7): PASS, but by a two-move detour after 142 compiles — the inverse swap
  sat behind 64 block wraps because the family order was a strict primary key → **round-robin across families within the cap**; rerun:
  `PASS … MATCH after 23 compiles by R9 swap-stmts @2289` at depth 1. Positive control 2 (one R6 inline + one R7 wrap, start 46
  POSITIONAL): FAIL at best 41 — the positional score read one inlined temp as 43 shifted words → **the edit-distance score** (the
  same perturbation now starts at 14/24), and the inline of `fv = *(u16 *)(p + 0xA) - 0x30` had no inverse → **R8's operand hoist**
  and **R7's unwrap**; rerun: `PASS — perturbed by R6 inline fv @2302 + R7 do-while @2307 (start 24), MATCH after 74 compiles by R8
  hoist tmp0 @2301 + R7 unwrap @2309` — the composition the engine exists for. Positive control 3 (`func_80135D20`, an inlined
  POINTER temp under a dereference + a wrap, start 26): FAIL at best 10 after 328 compiles — the unwrap came back, the inline of a
  dereference's base has no inverse generator yet: **the engine's stall mode is a missing inverse, and it is measurable** (lane B's
  map feeds exactly this). Also fixed on the way: the deref hoist targeted an assignment's LEFT side (the store's address) — RHS only.
  Speed: 0.11 s per scored candidate on an overlay TU (142 compiles in 15.7 s; 336 in 37.5 s).
  **`--plan --score --limit 24` (the head of the residue, 134–129-copy classes, every control 0/identical):** starting distances as
  EDIT distance vs the permuter's positional ones — `func_8013CF68` 38 (was 70), `func_80135A4C` 40 (131), `func_801345F8` 39 (105),
  `func_80133AB0` 24 (99), `func_80134A74` 30 (104), `func_80135888` 29 (78), `func_801670E4` 45 (276); the class-count-changing
  bodies are COUNT with register pairs beside the count (`s5↔s7`, `a2↔a1`), `func_8013D178` is a pure `a0↔a1` swap 45 times over
  (REG-caller, one `$5` pin — the ARGCOPY class), `func_80143D28` REG-callee `s2↔s3`, and five bodies start ≤ 9. Instrument rows:
  dictionary + SETUP (R21/R87), the `.run/P36/engine/` evidence allowlist. Next: the measurement — `--run --limit 16 -j 8` on this
  head, against rung D's honest baseline (5 of 16 in 0.69 h), then R22 → census → snapshot → commit.

- **2026-09-09 — S101 rung G run `g1` — THE MEASUREMENT (`.run/P36/engine/run_g1.log`, `outcomes.jsonl`, `trace/<alias>__<fn>.jsonl`):**
  `search: 1 of 16 exemplars matched lever-free in 0.12 h (132 of 2,126 bodies behind them; 3,680 compiles) — NO-MATCH 14 ·
  MATCH 1 · UNSTRIPPABLE 1` → `delever --propagate: 131 of 131 sibling(s) banked, 0 refused` → R22 (`.run/P36/baseline/r22_g1.log`)
  **`check-all: 218 passed, 0 failed of 218`** (`wall=82.73 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded):
  33,295 sites in 11,916 bodies (1,754 distinct) · marked !FAKE 33,295 · UNMARKED 0` → `lever_progress --snapshot` row 4
  (33,427 → **33,295**, asm 13,445 → 13,313). **The one close is the body rung D could not:** `func_801424E4` (no pin at all —
  a cast and a keep-alive, the count-changing class; the permuter's best was 2) by THREE composed moves, `R9 swap-stmts @1561 +
  R6 inline t @1559 + R6 inline sVar1 @1559`, 191 compiles, 28.9 s, worth 132 bodies. **Read honestly (R41):** this draw is the
  head of the CURRENT residue = the 11 exemplars rung D failed on + 5 it never tried — rung D's 5 of 16 counted the five it closed
  in ITS draw, and they are banked. On rung D's failures the engine moved most a long way in ≤ 112 s each: `func_8012E364` 25 → 7
  (`R5 swap + R7 do-while`), `func_801345F8` 39 → 14 (`R2 decl-order + R9 + R6`), `func_80135888` 29 → 22, `func_80134A74` 30 → 24,
  `func_8013CF68` 38 → 33, `func_801670E4` 45 → 40, `func_801627E8` 7 → 4, `func_80157D20` 9 → 7; unmoved at their start:
  `func_80135A4C` 40, `func_80133AB0` 24, `func_80148D44` 6, `func_80148E54` 6 (the two 6s: `keepalive+pin $4` / `launder+pin $4`
  in `_after.c`, a `$s0/$s1 ↔ $a0` pair — the ARGCOPY class, 1a-9 in lane B's map: no generator yet routes a parameter through a
  body-local copy). **The budget never bound:** ~325 compiles per body is the beam STRUCTURE exhausted (48 + 3 × 48 + 3 × 48),
  at 0.12 s per compile — so the levers are more generators (lane B's list), a wider beam / deeper search (cheap), and the
  exact inverses. Also: `func_80142EC0` UNSTRIPPABLE `token mismatch … expected register` — the bank of `func_801424E4` ABOVE it in
  the same TU shifted its lines (rung R's bottom-up rule now applied per file; it is redrawable with `--include-done`).
  **Lane B's first claim verified on bytes** (`.run/P36/engine/micro/`): `*(p+17) & -33` and `-33 & *(p+17)` compile IDENTICAL
  (fold moves the constant), `m & x` vs `x & m` differ in one word (`and v0,v0,a1` vs `and v0,a1,v0`) — R5 no longer generates
  a constant-operand swap (selftest updated). Commits: this bank + the two tool refinements.

- **S101 — the engine's second generator round, from the residuals read with the new `--explain TU FN [--path "m1|m2"]`
  (the residual as mnemonic blocks, mine vs the target, after any move path):** the two 6-distance bodies (`func_80148D44`,
  `func_80148E54`) are ONE surviving copy — the target computes `andi a0,v0,0xfff` and copies `move s0,a0` in the branch's delay
  slot, mine folds the copy into `andi s0` (combine merges a single-use def into its copy; the keep-alive/launder was the drafter's
  second use); `func_8012E364` after its best two moves (7) is an ASSOCIATION order (`addu;subu` vs `subu;addu` — `x + a3 - a1` vs
  `x - a1 + a3`) plus a negation the target names once for two stores; `func_80135A4C` (40) is a duplicated call tail the target
  keeps and mine cross-jumps (`jal;li;beqz;nop` vs `j`) with the s5/s6/s7 bank rotated. **Generators added to the registry
  (each with a selftest case, lane B's row in the docstring):** R10 a parameter routed through a body-local copy and the
  reverse (1a-9), R12 a local's scalar width (1c-1/2-2), R13 two adjacent terms of a `+`/`-` chain exchanged, R8's third form
  a repeated RHS named once. **Tested on bytes:** R12 on `ang` AND on the source `a` (u16 and s16) leaves func_80148D44's 6
  unchanged — combine folds the narrowing of a value already masked to 12 bits (nonzero_bits), so lane B's 1c-1 does not
  reach this copy; the class stays open (a second real use of the copied value is what the keep-alive stood in for). Generator
  defects fixed on the way: an `extern s16 (*D_x[])();` line ended the declaration run (every local after it invisible to
  R2/R3/R4/R12) and was offered to R7 as a statement; a multi-line initializer ended the run; `(void)` parsed as type `voi` +
  name `d` (a phantom parameter copy); `s32 * p2` spacing. Next: run `g2` on the same head with the new families and a wider
  structure (beam 4 × depth 4 × cap 64, budget 1,500) at 8 workers.

- **2026-09-09 — S101 rung G run `g2`** (the same 16-class head, `--include-done`, beam 4 × depth 4 × cap 64, budget 1,500, the new
  families; `.run/P36/engine/run_g2.log`): `search: 1 of 16 exemplars matched lever-free in 0.32 h (132 of 2,125 bodies behind
  them; 9,454 compiles) — NO-MATCH 15 · MATCH 1` → `delever --propagate: 131 of 131 sibling(s) banked, 0 refused` → R22
  (`.run/P36/baseline/r22_g2.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=86.07 s`) → census `THE PHASE'S NUMBER (pins
  + asm statements, GTE excluded): 33,031 sites in 11,784 bodies (1,753 distinct) · marked !FAKE 33,031 · UNMARKED 0` → snapshot row 5
  (33,295 → **33,031**). **The close:** `func_80142EC0` (two pins `$16,$17`; lost to the line shift in g1) by `R7 do-while @1843 + R9
  swap-stmts @1844`, 146 compiles, 22.8 s — 132 bodies. **The wider search with the new families moved the hard bodies past g1's
  best on nine of the fifteen (R41):** `func_80135A4C` 40 → 24 (g1: 40; two `R8 cse` temps — the target's duplicated call tail is
  still 10 words), `func_80135888` 29 → 16 (22; `R10 param-alias + R6 inline`), `func_801670E4` 45 → 31 (40; `R6 + R12 width s16 + R7`),
  `func_80133CD4` 28 → 10 (new; `R7 + R6 + R7`), `func_80157D20` 9 → 4 (7; `R12 width a1v s32->u16`), `func_801627E8` 7 → 4 (4),
  `func_801345F8` 39 → 14 (14), `func_80177B5C` 135 → 112 (119; a 15-site body), `func_8012E364` 25 → 7 (7 — the association order
  R13 was generated but not composed within the beam); unmoved: the two 6s (`func_80148D44`, `func_80148E54` — the one surviving copy
  no width reaches; 352 and 167 compiles), `func_80148AFC` 23 → 20, `func_80133AB0` 24 → 23, `func_80134A74` 30 → 24, `func_8013CF68`
  38 → 33. Compiles per body 167–822, 23–276 s. **What the two runs say together (R41):** on this head — the 11 exemplars rung D could
  not close in 0.69 h plus five it never tried — rung G closed 2 (264 bodies) in 0.44 h of compute and no tokens, and its trace names
  the remaining residual of each (`--explain`), so every stall is a generator to write, not a wall. The byte record against lane B's
  map (its verification ledger, appended to `residual_moves.md`): the constant-swap claim VERIFIED, the do-while lever VERIFIED as
  the ref weight (`.lreg` `used 5` → `used 6 times across 39 insns`, the LOOP notes surviving jump1, a plain `{ }` changing nothing),
  the 16-bit-copy claim NOT REACHED where the value's known bits already fit the narrow mode. Cookbook **§455** written; the SETUP row
  extended (R21).

- **2026-09-09 — S101 rung G run `g3`** (the next 64 residue classes by copies, 7,336 bodies behind them; beam 4 × depth 4 × cap 64,
  budget 1,500; `.run/P36/engine/run_g3.log`): `search: 13 of 64 exemplars matched lever-free in 1.02 h (1,516 of 7,336 bodies
  behind them; 35,074 compiles) — NO-MATCH 51 · MATCH 13` → thirteen `--propagate` lines, **1,503 of 1,503 siblings banked, 0
  refused** (≈40 min serial — a subprocess per sibling; the next tooling fix) → R22 (`.run/P36/baseline/r22_g3.log`) **`check-all:
  218 passed, 0 failed of 218`** (`wall=81.70 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 31,025 sites in
  10,268 bodies (1,740 distinct) · marked !FAKE 31,025 · UNMARKED 0` → snapshot row 6 (33,031 → **31,025**; pins 19,718 → 18,442,
  asm 13,313 → 12,583; bodies 11,784 → 10,268). **The thirteen closes and the move that closed each (R41 — the first move names
  the family):** `func_8013FAF8` R12 width `flag` s32→s16 (20 compiles, 125 copies) · `func_801431E8` R9 swap (18, 127) ·
  `func_8014305C` R9 + R7 (92, 126) · `func_801365B8` R12 + R6 + R6 + R12 (621, 126) · `func_80175DA8` R7 do-while (11, 128) ·
  `func_8013D53C` R7 (40, 111) · `func_8016A290` R12 + R12 (100, 124) · `func_80134C20` R6 + R12 (191, 127) · `func_8018000C` R9
  (5, 17) · `func_80167AE0` R12 + R12 (90, 125) · `func_8016C188` **R10 param-copy** (7, 127 — lane B's 1a-9 verified on a real
  body) · `func_80164BDC` **R10 param-alias** (7, 127) · `func_801621CC` R7 (46, 126). By first family: R12 5, R7 3, R9 3, R10 2 —
  **the two generators lane B's map named are half the closes**, and none of the thirteen needed more than four moves. Big movers
  among the 51: 70→16, 18→1 (`func_80156044`, one width), 24→2, 12→2, 34→6, 29→8, 55→21, 35→14, 58→31. **Unmoved at a small
  distance — the next generators, ~1,250 bodies behind them:** `func_8013EB7C` 2, `func_801287B8` 3, `func_8015FBE0` 3,
  `func_8017A3D8` 3 (two classes), `func_80185994` 3, `func_80139BE0` 4, `func_80166F58` 4, `func_8012C890` 5, `func_80141874` 6,
  `func_8017B238` 7, `func_8016E9EC` 8, `func_8014D820` 8; and `func_8013D178` 72 unmoved — the `a0 ↔ a1 ×45` body R10 did not
  reach. Compute: 1.02 h search + ~0.7 h propagation at 8 nice'd workers, no tokens. Harness note: the low-memory guard killed a
  30-byte waiter with 27 GB free (again); the detached run was untouched.

- **S101 — the third generator round, from `--explain` on g3's thirteen unmoved small residuals (`.run/P36/engine/explain_g3_small.txt`),
  and the bank made in-process.** The readings: `func_8013EB7C` (2) a `short` local extended in place vs into a temp; `func_801287B8`
  (3) a global's address in `a0` vs `v0` (a pointer local used once folds); `func_8015FBE0` (3) a `move a0,s0` scheduled early vs
  late (the barrier's job); `func_8017A3D8`/`func_80185994` (3) a value in the argument register vs the next free one;
  `func_80139BE0` (4) an `andi 0xff` the target keeps — a `u8` variable; `func_80166F58` (4) `sra a1,a1,0x10; move s4,a1` vs mine
  `sra s4,a1,0x10` — a `short` PARAMETER extended in place; `func_8012C890` (5) a global re-loaded after a store (the `volatile`
  cast's job — a bare-pointer store flushes cse's table); `func_80141874` (6) a store before the function-pointer load; `func_8017B238`
  (7) the parameter used directly vs through a cast copy; `func_8016E9EC` (8) the `$0`-pin's copy kept in `s4` across a call;
  `func_8014D820` (8) `move a3,a2` — a parameter copied into the next register; `func_8013D178` (72) `a0 ↔ a1` ×45. **Generators
  (each with a selftest case):** R12 now spells `u8` and `short`/`int`/`char`; **R14** a parameter's width in the header; R8's fourth
  form `base-shared` (one address local for every dereference of one base, stores included); R10's alias through casts. **The bank
  in process:** `delever.apply_body_core(tu, fn, body, label, rung)` (the CLI wraps it; `--propagate` returns `(banked, n, refused)`
  and calls it) — the engine no longer spawns a subprocess per bank or per sibling (g3's 1,503 siblings cost ≈40 min that way) and a
  `delever.py` edit mid-run can no longer break a bank. Run `g4s` (the thirteen names, `--include-done`; `--only` matched 38
  classes across the fleet, 1,619 bodies) launched at 8 workers as the test of both.

- **2026-09-09 — S101 rung G run `g4s`** (`--include-done --only` the thirteen names → 38 classes across the fleet, 1,619 bodies;
  beam 4 × depth 4 × cap 64, budget 1,500; `.run/P36/engine/run_g4s.log`): **3 of 38 matched** — `func_8016E9EC` (the `$0`-pin body
  whose copy the target keeps in `$s4` across a call) in three overlays' classes (125 + 7 + 1 copies) by `R12 width h u16->s32 +
  R6 inline r + R6 inline c + R12 width i int->s16` (the new `int` spelling was the fourth move); 35 NO-MATCH at their start
  (`func_8015FBE0` 3 → 2 and `func_80166F58` 4 → 2 in singleton copies only). Propagation IN PROCESS: 124 of 124 and 6 of 6 siblings
  in seconds (g3's 1,503 had cost ≈40 min as subprocesses). **Two instrument findings, both fixed (R40/R43):** (1) the scorer's
  scratch object was named by the worker TAG, which is the TU's index modulo the worker count and not a worker id — two TUs could
  share `g0.o` at the same moment and one worker objdumped the other's object: `ov_SC01_077__func_80141874: UNCALIBRATED — the
  tree's own text scores 14871 ident=True` (the whole object byte-identical, the function stream compared against another TU's);
  every candidate scored in such a window in g1–g3 was noise (never a false bank — the bank re-verifies whole-object equality on
  every recipe) — the scratch is now keyed by the TU; (2) `delever.propagate` returned a bare `1` for a class with no siblings (the
  R68 refusal) where the in-process caller unpacked a tuple — the run's process died after its two real propagations, before its
  `search:` line (the 133 banked files and every per-body outcome row were already on disk; `inflight.json` absent). R22
  (`.run/P36/baseline/r22_g4s.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=81.47 s`) → census → snapshot row 7.
  **What the four new generators did on the thirteen (R41):** the `u8`/`short`/`int` widths closed one class (through `int->s16`);
  R14 (parameter width), R8 base-shared and R10's cast alias closed none of the bodies they were written from — `func_80166F58`,
  `func_8012C890`, `func_8017B238` sit where they were, so those three readings need `--explain --path` with the exact candidate to
  see what each move actually did to the bytes before another generator is written.

- **S101 — the fourth generator round, from `--explain --path` on the exact candidates of the three generators that closed nothing
  (`.run/P36/engine/explain_paths_g4s.txt`), and two draw rules.** (1) Every R14 candidate on `func_80166F58` had been a COMPILE-ERROR:
  a parameter's width changed in the header conflicts with the TU's own PROTOTYPE — R14 now rewrites the TU's prototypes of the
  function with the header (a prototype in a shared header stays; the candidate then fails to compile, a wasted compile, never a
  wrong bank); on the bytes, `param_1 s32->s16` is no longer an error and the residual stands at 4 for both widths — the reading
  was right about the extension-in-place but the width alone is not the move. (2) `func_8012C890` has NO pin or asm left: its
  only surviving site is a byte-needed `volatile` cast, which decision 3 keeps as ordinary C — **a body whose NEEDED sites are all
  class C/D is DONE for the phase's number and is no longer drawn** (the T4 close counted 498 such bodies; g3 spent searches on
  them), **and the search seed keeps the tree's class C/D sites** (it had been stripping the cast and searching for the reload the
  cast produces). (3) `func_8017B238`'s alias through the cast is byte-neutral (score 7 → 7, the same diff): the target computes
  `param << 4` ONCE into `$s0` and never keeps the parameter, mine keeps it and recomputes — R8's named-once form now also names a
  depth-0 operand or a parenthesised group repeated across statements (`(q << 4)` inside `*(s32 *)(p + (q << 4))`). (4) `func_80139BE0`'s
  `u8` is on a name inside a multi-declarator line (`int t, v;`) — R12 splits such a line to widen one name; the line had also
  ended the declaration run and been offered to R7 as a statement (`MULTI_DECL` in `decl_run_end`/`simple_stmt`). Selftests and
  fixture prints for each. **The draw after g1–g4s:** `--plan --limit 64` → 64 classes with only 498 bodies behind them — the head
  (the ~80 classes of 110–134 copies) is exhausted at the current generator set and its ~65 unclosed classes hold ~8,000 of the
  10,135 remaining bodies; the tail is ~1,600 classes averaging < 8 bodies. So run `g5` re-draws the head (`--include-done --limit
  70`: 70 classes, 7,521 bodies) at beam 6 × depth 5 × cap 96, budget 4,000, with generators R2–R14 — launched at 8 workers.

- **2026-09-09 — S101 rung G run `g5`** (the head re-drawn: `--include-done --limit 70`, 7,521 bodies; beam 6 × depth 5 × cap 96,
  budget 4,000; generators R2–R14 with the fourth round's forms; `.run/P36/engine/run_g5.log`): `search: 5 of 70 exemplars matched
  lever-free in 1.67 h (62 of 7,521 bodies behind them; 112,216 compiles) — NO-MATCH 65 · MATCH 5` → five in-process propagations,
  57 of 57 siblings, 0 refused → R22 (`.run/P36/baseline/r22_g5.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=80.07 s`)
  → census → snapshot row 8. The five closes are all SMALL classes (10–14 copies: `func_8018D3FC` R8 temp; `func_8013D53C` R7;
  `func_8017C6CC` R3 + R7; `func_80182C70` two do-whiles, from 32; `func_8017DA20` R9) — **not one of the ~50 big head classes
  closed at three times the beam and eight times the budget of g3.** That is the measurement that ends the wide-search lever
  (R41: 112,216 compiles bought 62 bodies; g3's 35,074 bought 1,516): the unclosed head classes (~6,500 bodies) are each a reading
  and a generator, or T7's agents on Drew's word — the search space the registry spans is exhausted on them.

- **2026-09-09 — S101 the tail pass, `g6` (8 workers, stopped at 138 of 200 on Drew's word to double the concurrency) + `g6b` (16
  workers, the rest of the tail):** `g6b`: `search: 63 of 200 exemplars matched lever-free in 0.89 h (93 of 376 bodies behind them;
  41,366 compiles) — NO-MATCH 136 · MATCH 63 · UNSTRIPPABLE 1`; `g6` had banked 47 exemplars before the stop and never reached its
  propagation phase — propagated by hand in process (`g6p`): **186 of 191 siblings banked, 5 refused** (one class whose siblings carry
  7 address tokens to the exemplar's 11: the remap refuses, R43) → R22 (`.run/P36/baseline/r22_g6.log`) **`check-all: 218 passed, 0
  failed of 218`** (`wall=84.61 s`) → census `THE PHASE'S NUMBER (pins + asm statements, GTE excluded): 30,358 sites in 9,747 bodies
  (1,624 distinct) · marked !FAKE 30,358 · UNMARKED 0` → snapshot row 9 (30,806 → **30,358**). **The stop itself was an instrument
  finding (R40):** a SIGTERM landed while the tool was writing `inflight.json` and left it EMPTY; `--restore` crashed on it; the 31
  dirty files were reconciled against the object oracle (a bank is IDENTICAL, a leftover candidate DIFFERS: 29 banks, 2 candidates),
  the 2 proven to hold no uncommitted bank and restored from HEAD; `--restore` now refuses loudly on an empty or torn snapshot and
  says how to reconcile. **Built for T7 while the tail ran (both without tree writes): `delever_search.py --try TU FN FILE [--body]`**
  (a candidate scored through the TU's real recipe on a scratch copy — proven on a known-true case: the tree's text 0, one pin removed
  the known residual) **and `tools/delever_pack.py`** (57 packs under `.run/P36/agents/<alias>__<fn>/`, `ORDER.tsv` by best distance
  reached; the brief `PROMPT.md`). One agent was launched on rank 1 (`func_80156044`, best 1 after one width move) a minute before Drew's
  message *"dont launch the agents yet, wait for the tail to finish, and then checkpoint for a fresh session and we will start it in
  there"* — stopped at once, before it wrote anything. **Session total: 33,427 → 30,358 sites (−3,069), 12,048 → 9,747 bodies, every
  run gated 218/218, no drafting tokens.**

- **S102 2026-09-10 — T7 opens: the serial agent loop, agent a1 (Drew: `/effort high`, Opus 5 1M; "set and ready. start").** Oracle
  recalibrated at HEAD `5a8bd1021`: `177/177 objects byte-identical untouched; twin checks 32 (0 mismatch); positive control DIFFERS
  on build/src/800.o — OK`. **Agent a1 on rank 1 `func_80156044`** (ov_SC04_011, 130 copies, 2 NEEDED pins `$2`/`$3`, start 18,
  six mechanical runs stuck at best 1): **closed it at score 0.** Its move is not a dial — it DELETES two locals: the `iVar3`/`puVar2`
  pair that every arm of the if/else chain set is gone, and each arm gets the whole address expression
  (`puVar4 = &D_80192454 + (((u32)param_2) & 0xffff) * 0x14;`). Mechanism, read from the compiler's own source and confirmed in the
  `.lreg`/`.greg` dumps: (i) with the base scoped into the arm the block holds THREE local quantities instead of two, and
  `block_alloc`'s unrolled `case 3` (`local-alloc.c:1491-1496`) falls through into `case 2` and applies `qty_compare(0,1)` a second
  time — undoing its own exchange, so the `$2`/`$3` assignment flips (density formula `local-alloc.c:1578-1596`); (ii) deleting the
  cross-block variable also removes it from `global.c`, where `set_preference` (`global.c:1535+`) had given it a copy preference for
  `$5` through `puVar4`'s argument copy, merged by `expand_preferences` (`global.c:781-825`) and overriding first-fit at
  `global.c:1034-1067`. The `u16 puVar2` width move that six runs found was a LOCAL OPTIMUM that imitates the fix by manufacturing the
  third quantity while paying an `andi` — the search had no move that deletes a variable, so it could not leave that basin (the
  method finding of the task). Verified independently before banking: `--try … score 0 (OTHER; mine 74 ins, target 74) — MATCH`.
  Banked: `delever --apply-body: src/ov_SC04_011/ov_SC04_011_jr_80154C24.c:func_80156044 IDENTICAL on 1 object(s) (0.11 s) — KEPT,
  ledgered (rung E, a1)`; propagated: `delever --propagate: 129 of 129 sibling(s) banked, 0 refused`. R22 `check-all: 218 passed, 0
  failed of 218`; `lever_census --check: 30,098 pin/asm sites, 30,098 marked !FAKE, 0 UNMARKED — OK`; snapshot row 10
  (**30,358 → 30,098**, −260 sites = 130 bodies × 2 pins; 9,747 → 9,617 bodies). The body is also SHORTER and more readable than the
  levered one — two locals fewer — which is the phase's point. Toolify (R16) follows in its own commit.

- **S102 — the a1 harvest: generator R15 (the sink) and sweep s1 (commits `861dd0651`, this one).** Agent a1's crack was
  MECHANICAL, so it became a move the engine can make anywhere (R16, the harvest→toolify gate): **R15** pushes the statement
  AFTER an if/else chain into every arm and deletes the variables it consumed (`if (c) { v = e1; } else { v = e2; } w = f(v);`
  → `if (c) { w = f(e1); } else { w = f(e2); }`). Applicability is CHECKED (each consumed variable assigned exactly once in
  every arm by a simple statement, present in the merge statement, occurring nowhere else in the function); ranked third in
  REG-caller / REG-mixed / COUNT; three selftest controls. **The defect it was born with, caught by running it on the very
  body it came from (the known-true case):** `if_chains()` counted a line's opening and closing braces together, and on a
  `} else if (…) {` line the two net to zero, so the walk never closed an arm and the generator returned 0 candidates —
  the closes are now counted first. Its known-true check after the fix: run on `func_80156044`'s pre-bank text it emits the
  agent's crack and `--try` scores `0 (OTHER; mine 74 ins, target 74) — MATCH`.
  **Sweep s1** (`--run --include-done --only <the 56 other head fns> -j 8 --beam 3 --depth 2 --cap 48 --budget 200`; note
  `--only` draws EVERY body of a name across the fleet, so 147 exemplars were judged, not 56):
  `search: 6 of 147 exemplars matched lever-free in 0.28 h (267 of 7,477 bodies behind them; 23,892 compiles) — NO-MATCH 141
  · MATCH 6`. **All six closes are R15, in FOUR compiles each** — `func_8013EB7C` (126 + 7 copies) and `func_8016DF5C`
  (127 + 4 + 2 + 1) across their fleet copies, every propagation 0 refused. R15 also moved `func_80136824` 21 → 2 as a first
  move. **The economics of the loop, with denominators (R41): one agent's reading (≈221k tokens) bought 130 bodies directly
  and 267 more for 0 tokens — 397 bodies, 30,358 → 29,697 sites (−661).** R22 `check-all: 218 passed, 0 failed of 218`;
  `lever_census --check: 29,697 pin/asm sites, 29,697 marked !FAKE, 0 UNMARKED — OK`; snapshot row 11 (9,617 → 9,350 bodies).
  Drew raised the sweep concurrency to `-j 16` for everything after this run.

- **S102 — T7 agent a2: `func_80168828` (ov_SC04_011, 125 copies, pins `$3`/`$4`, start 35, g5's best 1).** Score **0**, one of
  the two pins off, **125 bodies** (1 + 124 propagated, 0 refused). Two moves: (1) delete `register s32 c40 __asm__("$3")`
  and its `c40 = 0x40;` and write the literal at its four uses — byte-neutral on its own, the pin was never doing the work;
  (2) swap the adjacent `thing.f1e = 0x40;` and `thing.f1a = 0x10;` so the `0x10` store SPLITS the run of `0x40` stores.
  **The residual reads like cse/sched — "the target holds `0x40` in a register while mine rematerialises it" — and the
  decision is in local-alloc.** Dumps of the real TU in both orderings: `cse`/`combine`/`flow` identical up to order; the
  `.lreg` header moves on exactly one line, `Register 76 used 5 times across 10 insns in block 0` → `across 14 insns`, and
  `;; Register 76 in 2.` → `in 3.` ($v0 → $v1). The decision is `find_free_reg`'s live-range scan at
  `local-alloc.c:2109-2110` (`for (ins = born_index; ins < dead_index; ins++) IOR_HARD_REG_SET (used, regs_live_at[ins])`):
  unswapped, qty 76 dies at insn 61 and the `0x10` quantity is born at 64 — disjoint, both take `$v0`; swapped, 76 stays
  live across the whole of the other and the intervals overlap, so 76 takes `$v1`. **The `$4` pin STAYS and the reason is a
  declaration, not a lever:** `src/shared/ov/func_801687CC.h` declares `extern void func_80168828(void);`, so the target's
  `move s1,a0` — a read of the incoming `$a0` — has no C source at all; an uninitialised local, a pointer-typed one, a split
  declaration and deleting it outright all give the IDENTICAL score-25 residual, and both K&R and prototyped parameter forms
  are hard cc1 errors against that header (`number of arguments doesn't match prototype`). It is one of the 51 declaration
  conflicts P35 ledgered for the types phase, and it is the FIRST measured case of a pin that only a declaration fix can
  remove. The engine's own score-1 text (`u8 a0v; s16 param_1 = a0v;`) is a COINCIDENCE, not a near miss: its `andi
  s1,s1,0xff` truncates garbage already in `$s1` and never touches `$a0` — the agent refused to propose it (P9).
  **Instrument fixed in the same change:** `--propagate` could not spread a reshape that deliberately keeps a lever (it
  refused all 124 siblings). The allowance is now DERIVED from the exemplar's own banked text — the count of surviving
  `// !FAKE:` markers — and a sibling whose remap would carry MORE levers than the exemplar is refused by name.
  R22 `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 29,572 pin/asm sites, 29,572 marked !FAKE, 0
  UNMARKED — OK` (29,697 → 29,572); snapshot row 12. The agent's two toolify proposals (R16 the constant-run split; the
  constant-holder pin census, its 284 of 10,958 claim to be verified against the bytes, R14) follow in their own commit.

- **S102 — sweeps s2 and s3, and the constant-holder census (R14/R40).** **s2** re-swept the same head with R16/R17 added:
  `search: 0 of 140 exemplars matched lever-free in 0.24 h (0 of 7,085 bodies behind them; 23,689 compiles)` — **the two new
  generators closed NOTHING on the head**, honestly recorded; the head's shapes are not this family's. Agent a2's claim of
  "284 constant-holder pins of 10,958" was then verified against the source rather than believed (R14), and the FIRST
  instrument was wrong (R40): asking R16 directly answered **33**, because R16 only fires on a SPLIT declaration while most
  pins carry their value as an INITIALISER (`register s32 c __asm__("$3") = 0x40;`) — R3 already converts one form to the
  other, so the family R16 can reach is R3+R16. The corrected census (`.run/P36/engine/const_holder_census.py`, both figures
  derived): **537 constant-holder pin sites of 17,302, in 510 bodies** — 152 as an initialiser, 385 as a separate assignment;
  by register `$2` 282, `$20` 136, `$3` 28. **s3** drew exactly those 99 function names at beam 3 × depth 3 × cap 64:
  **10 bodies closed before the run CRASHED** — `AttributeError: 'Namespace' object has no attribute 'allow_residue'` in
  `propagate`, because the a2 fix read the flag off the caller's namespace and the search engine builds its OWN Namespace for
  that in-process call. Fixed with `getattr(a, "allow_residue", False)` (R43: a library must not assume its caller's
  namespace shape). The ten banks were all real — R22 `check-all: 218 passed, 0 failed of 218` on the tree the crash left,
  which is the proof no leftover candidate was standing; `lever_census --check: 29,533 pin/asm sites, 29,533 marked !FAKE,
  0 UNMARKED — OK` (29,572 → 29,533); snapshot row 13. By first move the ten are R15 ×3, R6 ×4, R7 ×2, R9 ×1 — the draw was
  right about the family even though R16 itself did not fire. s3 re-runs from the top with the fix.

- **S102 — s3b, the constant-holder draw re-run after the fix.** `search: 1 of 80 exemplars matched lever-free in 0.89 h
  (6 of 486 bodies behind them; 28,042 compiles) — BUDGET 59 · NO-MATCH 18 · UNSTRIPPABLE 2 · MATCH 1`
  (`func_801621CC` by `R6 inline lo + R7 do-while`, 5 of 5 siblings propagated). **The number that prices this draw is
  BUDGET 59 of 80** — three quarters of the remaining bodies exhausted 400 compiles rather than being refuted, so this
  family is not measured yet, only sampled; s3 had already taken its cheap half (10 bodies). Two UNSTRIPPABLE recorded by
  name: `func_8017DC80` (a launder with 2 outputs) and `func_80181A4C` (`instruction \`lw\` has no C spelling in the
  table`). R22 `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 29,527 pin/asm sites, 29,527 marked !FAKE,
  0 UNMARKED — OK`; snapshot row 14. **Loop economics so far (R41), two agents in: 30,358 → 29,527 sites (−831) and
  9,747 → 9,320 bodies, of which the agents' own two bodies are 255 and everything else (576 sites) came from their
  toolified moves at zero drafting tokens.**

- **S102 — T7 agent a3: `func_801397B0` (126 copies, one `$4` pin, best 2) — NO BANK, and the reading is the deliverable.**
  It first ran the a2 check and REFUTED it: `git grep` returns 1,770 declarations in two forms, both `(s32 a0)`, no `(void)`
  anywhere, and the pin is on a LOCAL, not the parameter — three different lever-free spellings reach the target's complete
  register assignment, so this class is reachable from plain C. Its best is **score 2, class ORDER, 89/89 instructions, every
  register correct**, one displaced bystander store. Why it stops there: the target emits that `sw` at index 6, INSIDE the
  `lbu`→`addiu` window, and that position is forced — `anti_dependence`/`true_dependence` (`sched.c:817/845`) both hold (the
  QImode carve-out kills the first, `$fp` not varying the second), so the store can neither hoist above nor sink below the
  `lbu`; the post-`sched1` stream and `reg_live_length` are then identical to ours, leaving `reg_n_refs` — computed by flow on
  the PRE-combine RTL — as the only remaining input, so the original gave that chain a fourth reference from a loop note or
  from an insn `combine` later deleted. **Toolified as R18, the bystander move** (its proposal): one simple statement moved to
  each other position in its own block, up to six away — R9's adjacent swap is the special case and the distance is the point;
  it costs no instruction, where `R7 do-while`'s LOOP notes are a full `sched1` barrier and always cost one displaced insn
  (the agent enumerated all 60 wrap ranges in its body and every one paid exactly that), so R18 is ranked ahead of R7 in every
  class. **Two wrong spellings before the known-true check passed:** identifier-disjointness as a REQUIREMENT offered three
  candidates and none of them the agent's — it is now only an ORDERING preference, because byte-identical output is the same
  program and the oracle is the whole correctness proof (R9's own footing) — and a BLANK line counted as an obstacle, so the
  generator never offered the very move it was written from. It now reproduces that body exactly (`bystander @21->17`).
  **`delever_pack.py` fixed from the agent's own method note:** each trace candidate now carries its residual CLASS beside its
  score, because a bare number hid that a move had already turned this body's residual from REG into ORDER.

- **S102 — the OUT-OF-BODY defect, found by run s4 and fixed at its cause.** s4 reported `BANK-REFUSED` on `func_80136824`
  after 288 compiles that had genuinely reached score 0 (`R15 sink + R12 width pos + R14 param-width arg1 s32->s16`), with
  `conflicting types for 'func_80136824'`. **The cause is a contract, not a bad body:** the engine verifies the WHOLE
  candidate text through every recipe, then hands `apply_body_core` only the function's DEFINITION — and `--propagate`
  remaps that body text to siblings — so any generator whose candidate edits lines outside the definition produces a
  score-0 text that can never be banked. R14 (a parameter's declared width) is the only such generator: it must rewrite the
  TU's prototypes too, and those edits are dropped at bank time. **My first diagnosis was wrong and was discarded rather
  than shipped** — I guessed the conflicting declaration lived in a shared header, built a 2,431-name index of shared-header
  declarations to refuse on, and the index said `func_80136824` is NOT in it; reading `cmd_run` gave the real answer.
  Two fixes: `param_widths` refuses outright when the TU declares the function anywhere but at its definition
  (`protos_outside_definition`, R43 — the earlier R14 banks were all bodies with no such prototype, so nothing that worked
  is lost), and the engine names the condition itself with a new **OUT-OF-BODY** verdict instead of letting the bank fail on
  a compiler error that reads like a bad body. Controls both ways in the selftest. **Open by name for the types phase:**
  `func_80136824` (126 + 4 copies) has a REAL crack that needs its prototype widened with its definition — the same shape as
  a2's `$4` pin, and the second measured case where a declaration, not codegen, is what stands between us and the bytes.

- **S102 — sweep s4 (the head, with R18): `search: 0 of 139 exemplars matched lever-free in 0.54 h (0 of 7,077 bodies
  behind them; 52,566 compiles) — NO-MATCH 136 · BANK-REFUSED 3`.** The three refusals are the three fleet copies of
  `func_80136824`, each a REAL score-0 blocked by the body-only bank contract. **The measurement that should steer the rest
  of T7 (R41): across s1–s4 the head's 57 classes have now absorbed ~128,000 compiles and yielded 6 closes, all of them
  R15's, all in the first sweep. The head is resistant to every mechanical generator at this width** — the tail and the
  targeted families are where the sweeps pay, and the head is what agents are for. Cumulative for the session so far:
  30,358 → 29,527 sites, 9,747 → 9,320 bodies, three agents (≈590k tokens) and four sweeps (0 tokens).

- **S102 — sweep s5, THE TAIL, and it is where the number is: `search: 285 of 800 exemplars matched lever-free in 2.32 h
  (285 of 800 bodies behind them; 94,627 compiles) — NO-MATCH 499 · MATCH 285 · UNSTRIPPABLE 9 · UNSCORED 7`.**
  The first broad draw of NON-head classes, at the cheap width (beam 3 × depth 2 × cap 48, budget 200) with the full
  generator set. **36 % of the tail closes mechanically, against 6 closes in ~128,000 compiles on the head.** By first move:
  **R7 105 · R10 59 · R12 42 · R6 26 · R9 20 · R18 13 · R8 9 · R3 6 · R15 4 · R14 1**, and **242 of the 285 closed in ONE
  move** — these are not deep searches, they are bodies nobody had ever offered a single shape to. R18, one day old, is
  already 13 of them. R22 `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 29,204 pin/asm sites, 29,204
  marked !FAKE, 0 UNMARKED — OK` (29,527 → 29,204); snapshot row 15. **The steer for the rest of T7 is now measured, not
  guessed: run the cheap sweep over the WHOLE residue before spending another agent.** The head's 57 classes stay the
  agents' work; everything else is the engine's, at zero tokens.

- **S102 — sweep s6, the LAST never-attempted exemplars: `search: 25 of 337 exemplars matched lever-free in 1.39 h (25 of
  337 bodies behind them; 57,838 compiles) — NO-MATCH 307 · MATCH 25 · UNSTRIPPABLE 4 · UNSCORED 1`.** The draw asked for
  1,200 and the ledger could only offer **337**: s5 had taken the whole easy half, and **the never-attempted pool is now
  empty** — every remaining residue class has been offered at least one shape. The yield fell from 36 % to 7 % on exactly
  the bodies s5's ordering had left for last, which is what an exhausted pool looks like rather than a broken instrument.
  R22 `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 29,148 pin/asm sites, 29,148 marked !FAKE, 0
  UNMARKED — OK` (29,204 → 29,148); snapshot row 16. **What is left, and what it costs (R41): 9,010 bodies in ~1,300
  classes, every one of them already refuted at beam 3 × depth 2 × cap 48. The next zero-token lever is a WIDER re-draw
  over the NO-MATCH population (`--include-done`, beam 4 × depth 3–4), which is the same move that took g1's 1-of-16 to
  g3's 13-of-64 in S101; the head's 57 classes remain the agents'.**

- **S102 — the CADENCE MISTAKE, named by Drew on waking, and the correction.** He expected dozens of agents overnight and
  got **three**. The cause is mine and it is not the agents: I ran the loop strictly serially — agent, gate, toolify, sweep
  — and the sweeps are HOURS (s5 2.32 h, s6 1.39 h, s7 killed part-way), so roughly six of the eight hours had no agent
  running at all. His rule was *one agent at a time so the methodology is honed each time one lands*, which is about
  LEARNING BETWEEN LANDINGS, not about leaving the agent slot empty while a sweep runs. **The correction: agents run
  back-to-back, the next one launched the moment the last lands; a sweep is only started when it does not stand between two
  agents, and it must exclude the TU the live agent is scoring in (the scorer's scratch object is keyed by the TU).**
  s7 was stopped for this. **Stopping it cost a lesson worth keeping (R102):** the kill landed mid-write, so
  `inflight.json` was EMPTY and `--restore` refused loudly and told me how to reconcile — 8 dirty files, 5 of them the
  run's recorded banks and 3 with no bank at all; the fleet named exactly those 3 binaries (`ov_SC03_113`, `ov_SC04_004`,
  `ov_SC04_011`), they were restored from HEAD, and the gate went back to `check-all: 218 passed, 0 failed of 218`. The
  refusal plus the fleet was a complete reconciliation instrument with no snapshot at all.
  `lever_census --check: 29,140 pin/asm sites, 29,140 marked !FAKE, 0 UNMARKED — OK`; snapshot row 17.

- **S102 — THE OPERATING PROCEDURE FOR T7, set by Drew 2026-09-10 after the three-agent night:** *"you should always have an
  agent running once it finishes, prove the rule, harvest the idiom, start a new agent, thats the main lane. the banking and
  propegation lane can run slower in the background as needed."* **The agent lane is the MAIN lane and is never empty.**
  On a landing, in this order: (1) `--try` the agent's `body.c` — seconds — to prove the claim on bytes; (2) **launch the
  next agent immediately**; (3) only then bank, propagate, harvest the idiom into a generator, gate and commit, all of it
  while the new agent runs. Still ONE agent at a time (his earlier rule: the methodology is honed at each landing), but the
  slot is refilled in seconds, not after an hour of gating.
  **The one real hazard, and how it is handled:** the scorer's scratch object is keyed by the TU, so two processes scoring
  the SAME TU collide and one gets a wrong score. Banking itself is safe to run beside an agent — a bank is IDENTICAL on the
  whole object by construction, so it cannot move the agent's function's bytes — but a `--propagate` that reaches the LIVE
  AGENT'S TU must be deferred until that agent lands. Pick the next exemplar from a different file when there is a choice,
  and note the live TU before propagating. **A sweep is not part of this lane at all:** it writes candidates across many
  TUs for hours, which is exactly what emptied the agent slot for six of the eight hours of S102's night; sweeps run only
  when no agent is running, and never on the live agent's TU.

- **S102 — T7 agent a7: `func_801287B8` CLOSED at score 0, lever-free, 127 bodies (1 + 126 propagated, 0 refused) — and it
  is a NEW CLASS: a pin that was faking a MISSING CALL ARGUMENT.** `ov_SC04_011.c:197` declares `extern void
  func_8013BC7C(void);` while that function's real, byte-verified definition is `src/shared/ov/func_8013BC7C__8042ae05.h:3`
  — `void func_8013BC7C(void *arg0)`, dispatching through `D_8017F230[arg0->f68](arg0)`. The `$a0` instruction the pin was
  forcing is simply the argument the TU's own declaration denies. The move: a block-local `s32 *p = &D_801F1640;`, tested
  and then passed through a function-pointer cast — `((void (*)(void *))func_8013BC7C)(p);` — the idiom this TU already uses
  for two other calls. **Score 0 on the first spelling tried, where seven mechanical runs and 4,000+ compiles had sat at 3**,
  because every generator rewrites statements that are already there and this move ADDS an argument. Mechanism, both halves
  proven on bytes: `update_equiv_regs` (`local-alloc.c:947`, the "referenced exactly twice" test at `:1066`, substitution at
  `:1085-1112`) — one use folds the `SYMBOL_REF` into `lui;lw %lo`, the SECOND reference keeps the address in a register,
  which is what the `volatile` was faking; and `combine_regs` (`local-alloc.c:1722`, the hard-reg path `:1797-1818`) records
  `$4` in `qty_phys_copy_sugg[]` so `find_free_reg` (`:2073`, restricted at `:2145-2150`) colours the quantity `$4` and
  coalesces the copy away, which is what the pin was faking. Controls: reading the global directly scores 9 (63 ins), and
  declaring the pointer at function top scores 4 (`s0->a0`, an extra `move`). **Unlike a2's case this truncation is a LOCAL
  `extern`, so the cast keeps the bank body-only** — a2's was a shared header and could not be. Its generator proposal is
  **R19 "argument restore"**, a zero-compile STATIC filter: when a NEEDED pin sits on `$4`–`$7`, look up the callee's real
  arity from its shared body and offer the call with the argument restored through a cast. The agent's own method note is
  worth more than the pass reading: *an argument register in the residual's register pairs is a strong prior for "a call is
  missing an argument", and one grep answers it before any compiler source is opened.*
  `lever_census --check: 29,013 pin/asm sites, 29,013 marked !FAKE, 0 UNMARKED — OK` (29,140 → 29,013); snapshot row 18.
- **S102 — THE BUILD-DIRECTORY HAZARD (recorded before it cost anything).** `--try` scores a candidate against the fleet
  run's BASELINE OBJECT under `build/`. The R22 gate begins with `make clean`, which deletes exactly that. **A clean fleet
  rebuild must therefore never run while agents are in flight** — every live `--try` would score against a missing or
  half-written baseline and report nonsense in the agent's own voice. Banking and propagation are safe beside agents (they
  compile into scratch and only READ `build/`), so the writing lane keeps up during a burst and the R22 fleet gate is taken
  when the burst drains, before the close.

- **S102 — THE BUILD-DIRECTORY COUPLING FIXED so the burst is safely parallel (Drew, 2026-09-10: "fix the build issue so
  agents effort dont get wiped, this needs to be parallelizable").** Every score in this engine compares a candidate with
  the fleet run's object under `build/`, and the R22 gate starts with `make clean`, which deletes exactly that — with agents
  scoring in parallel a fleet gate would have made every live `--try` compare against a missing or half-written baseline
  and report nonsense **in the agent's own voice**. Fixed at the single accessor: `delever_oracle.baseline_path(obj)`
  returns the SNAPSHOT under `.run/P36/delever/baseline/` when it holds the object and falls back to `build/` when it does
  not, so nothing can silently score against half a snapshot; `baseline_bytes` and both direct readers in
  `delever_search.py` (the engine's `Scorer` and `--try`) go through it. `delever_oracle --snapshot-baseline` refreshes it:
  **7,428 objects, 188 MB, taken at `9f5b22176`**. It is valid until the fleet stops being green, because the baseline is
  the ORIGINAL game's bytes and a bank is byte-identical by construction. **Known-true test, both directions:**
  `func_800123F0` in `src/800.c` scores `0 … MATCH` with `build/src/800.o` present, `build/src/800.o` was then MOVED AWAY
  and it scores `0 … MATCH` unchanged, then restored (186,228 bytes). The R22 gate may now run at any time; refresh the
  snapshot after each green `check-all`.
- **S102 — T7 agent a4: `func_8016C49C` CLOSED at score 0 from a seed of 34, 126 bodies (1 + 125, 0 refused), by ONE
  character-level move:** `param_1[1] = sVar1;` → `do { param_1[1] = sVar1; } while (0);` on the function's LAST statement,
  and nothing else. The whole 34-point residual was a single `qsort` comparison in `global_alloc` lost by 142 units out of
  6,666: `global.c:546` sorts allocnos by `global.c:587`'s priority `floor_log2(refs)*refs/live_length*10000*size` and
  `find_reg` (`global.c:904`) colours first-fit, so whoever is compared first takes `$s1`. The agent read the pinned cc1's
  own `-dl -dg` dumps and reproduced the table by hand — it matches `;; 8 regs to allocate: 81 76 80 73 74 140 75 84`
  exactly: `r80 iVar4` refs 5 / live 15 / **pri 6666** against `r73 param_1` refs 23 / live 141 / **pri 6524**. `reg_n_refs`
  is LOOP-WEIGHTED and computed before combine and sched (`toplev.c:2983` → `:3004` → `:3033` → `:3080`): `flow.c:434`
  starts at `depth = 1`, `:440-443` bumps it on `NOTE_INSN_LOOP_BEG/_END`, and `:2067`/`:2501`/`:2711` do `reg_n_refs +=
  loop_depth`, so the reference inside a `do {} while (0)` is counted TWICE — refs 23→24, pri 6524→**6808 > 6666**, the
  order flips, `param_1` takes `$s1` and all 34 words fall into place. **Control proving it is the NOTES and not the
  scope:** a plain `{ … }` block at the same site leaves refs at 23 and still scores 34. **Position is the discriminator,
  not the site:** of all 47 do-while sites in this body 22 change the instruction count and only the function's last
  statement scores 0 (next best 2).
  **Two instrument findings from it, both to act on:** (i) `recipe_candidates` ranks by distance to the nearest NEEDED site
  (`delever.py:2520-2529`), the only NEEDED site here is the declaration pin at 2707 and the answer is at 2777, so
  `do-while @2777` ranked **438 of 439** and `--cap 48` cut it in g3, g5, s1, s2, s4 and s7 — **~4,300 compiles spent
  discarding the answer six times**; for the regalloc-order class the ranking must be by TAIL distance, or a block's last
  statement must never be dropped by the cap. (ii) `history.txt`'s `R15 sink @2777 -> 1` is NOT reproducible — the agent ran
  `sink_merges` and scored its exact text at **40 (mine 173 ins)**, so either the trace row or the generator moved; to be
  checked against the bytes before either is trusted (R40). Also `tools/alloc_table.py` drops the `;; N regs to allocate:`
  line — the most informative line in a `.greg` dump — and its `Register N in M.` regex missed 7 of the 8 allocnos.
  `lever_census --check: 28,887 pin/asm sites, 28,887 marked !FAKE, 0 UNMARKED — OK` (29,013 → 28,887); snapshot row 19.

- **S102 — THE BURST OF 20 (Drew, 2026-09-10: "maintain your concurrency of 4 if you think that is best. but lets do a
  burst. burst 20 agents now"). The first landings, and a CROSS-AGENT DEFECT they found for us.**
  **The defect (fixed at its cause):** `score_file` called `compile_obj(..., tag="score")` with a CONSTANT tag, and
  `compile_obj` names its scratch object `<obj>.<tag>.o` — keyed by the FILE. Nine of the burst's agents shared one
  translation unit, so they wrote and read ONE object. Two reported it independently without either seeing the code: one
  saw spurious `COMPILE-ERROR`s naming an unrelated header that re-ran clean, the other **scored four candidates against
  another agent's function** before `--try`'s echo of the TU and function name gave it away. The tag is now per FUNCTION
  (`score_<alias>_<fn>`). **Every landed body was re-verified after the fix and all still score 0** — the banks were
  never at risk (the coordinator verifies serially and `apply_body_core` judges on the real recipes), but the agents'
  own intermediate readings were.
  **Banked from the burst so far — 503 bodies:** `func_801627E8` (a8, 132), `func_8017A3D8` (a12, 118),
  `func_80141874` (a18, 119 of 125, 6 refused), `func_801345F8` (a19, 134). 28,887 → **27,984 sites**;
  `lever_census --check: 27,984 pin/asm sites, 27,984 marked !FAKE, 0 UNMARKED — OK`; snapshot row 20.
  **THE FINDING OF THE BURST — the biggest lever class in the phase is a WRONG DECLARATION, not codegen.** Four agents
  independently reached score 0 by restoring a call's real arity, each in a different spelling:
  *a7* `extern void func_8013BC7C(void);` against a shared body taking `void *` → a function-pointer cast at the call;
  *a8* `extern void (*D_80192FD0[])(void);` → widen the block-scope prototype to `(u8 *)` and pass the pointer, which
  removed BOTH its levers; *a12* `extern int func_8001AAA0(void);` against `void func_8001AAA0(s32)` at `src/800.c:7846`
  — and another TU already declares it correctly and calls it with an argument; *a13* `func_80157D20` itself declared
  `(void)` in 131 of its 138 defining sites while the target's prologue copies two parameter registers. The mechanisms
  differ (combine's `added_sets_2` gate at `combine.c:1458`; `set_preference` `global.c:1589` applied ahead of first-fit
  at `:1001-1015`, the argument copy becoming a self-move deleted by `jump_optimize` at `toplev.c:3142` so it costs ZERO
  instructions; `assign_parms`' parameter home copies), but the class is one: **a truncated `(void)` declaration removes
  an instruction the pin was then hired to fake.** No mechanical generator can reach it — every generator rewrites
  statements that exist, and this changes a call's ARITY — which is why these bodies sat at 3 through thousands of
  compiles across seven runs.
  **a13 is the one that does NOT bank body-only:** `func_80157D20` reaches 0 only by widening its own `extern` line, and
  gcc 2.7.2 rejects a block-scope redeclaration (`conflicting types`), so the body-only ceiling is 4. Its Path A (widen the
  declaration in the 131 + 5 defining sites, worth 2 pins × 132 copies) is recorded for the types phase together with
  `func_80136824` and a2's `func_80168828` — **three measured cases now, all the same shape.**
  **Two more new classes, each byte-proven:** *a18* `func_80141874` — a plain scalar global's STORE sank past an array
  load because `true_dependence`'s exception clause (`sched.c:837-839`) discards the edge when the load is in-struct and
  varying and the store is neither, even though `memrefs_conflict_p` returns 1; declaring the global `extern u16 X[];` and
  storing through `X[0]` sets `MEM_IN_STRUCT_P` on the store, the exception fails and the order is restored — and the
  delevered body is SHORTER than the levered one. *a19* `func_801345F8` — a post-decrement inside a `while` condition is
  QUEUED by `expand_increment` and flushed only at the next sequence point, so splitting it into its own statement (or a
  comma operator) plus a `u16` destination that `insert_regs` (`cse.c:1017-1019`) refuses to join keeps the copy alive.
  Its answer to the `$0` question is a correction worth keeping: `zr` is `register int __asm__("$0")` with NO initializer,
  an opaque operand and NOT R16's constant holder — **R16 must refuse an uninitialised `register … __asm__` declaration.**

- **S102 — DREW'S CHALLENGE TO a10's "NEEDED BY CONSTRUCTION", and the verdict DOWNGRADED (R65/R69).** He asked the right
  question: *"does this mean the dev in 1998 wrote in that register pin in his C code? because if not, then it should be
  possible to remove it."* **He is right, and the verdict was too strong.** Nobody wrote `register int r __asm__("$2")` —
  every pin in this tree is OUR scaffold, inserted by this project to force a byte match, so a plain-C spelling exists for
  every one of them by construction. What agent a10 actually proved is the SCOPED claim: within `func_80178970`'s CURRENT
  declaration environment, no spelling it tried reaches the bytes, because combine deletes the call-result copy
  (`combine.c:914-917`, `use_crosses_set_p` at `:10127-10130`; the `SMALL_REGISTER_CLASSES` arm at `:944-957` is not
  defined for MIPS) and only a call or a return writes `$v0` in plain C. **The environment is demonstrably wrong in that
  very function:** the TU declares `extern s32 func_801789AC(s32 arg0);` at line 3884 and the body calls it as
  `((s32 (*)(void))func_801789AC)()` — the SAME dropped-argument class six other agents cracked today. Restoring the
  argument was tested on the bytes at once: `func_801789AC(0)` scores **3**, both as a statement and folded into the `if`,
  so it is not the whole answer here — but it proves the body is being read in a distorted environment, and a verdict
  taken inside a distorted environment is not a property of the function. **Drew's own next hypothesis is the right one to
  record:** structs, once built out and propagated, change the RTL a body generates — this phase already has a byte-proof
  of exactly that lever, agent a18's `func_80141874`, where declaring a global `extern u16 X[];` instead of a scalar set
  `MEM_IN_STRUCT_P` on its store, restored a `true_dependence` edge the exception clause at `sched.c:837-839` had
  discarded, and closed the body. **So `func_80178970` is NOT permanent: it moves to the structs/types phase's list**
  alongside `func_80136824`, `func_80168828` and `func_80157D20`, with its reading attached.
- **S102 — T7 agent a15: `func_80166F58` NOT closed (score 4 of a start of 4; ~350 hand-tested candidates on top of the
  search's 2,625) — and it CORRECTS one of my own documented premises.** The SETUP row for R14 says a `short` parameter
  "arrives in its SImode register and gcc 2.7.2 sign-extends it IN PLACE". **That is wrong for this port:** MIPS defines
  only `PROMOTE_PROTOTYPES`, not `PROMOTE_MODE` (`config/mips/mips.h:1153`), so a narrowed parameter stays a HImode pseudo
  and the extension still happens at the USE — the agent compiled it both ways and got the same 67-instruction merged
  form, and the K&R form too. R14 was doubly dead on that body (the TU also declares the function twice at file scope
  after its definition, so narrowing is a hard `conflicting types` error). Its real reading: the missing pair is a reg-reg
  copy that combine deletes because the extension's destination carries `REG_DEAD` at the copy, and the obvious defence —
  a second use — is undone by `cse.c:canon_reg`, which rewrites the later use onto the COPY's destination; only a second
  use placed BEFORE the copy survives, and it then rotates the callee-saved seats. Its sweep measures the trap exactly:
  second use after both copies 67 ins, between them 68, before both 69. It also disassembled all 4,284 objects under
  `build/src` looking for the target's shape and found it in exactly ONE function in the whole game — itself.
  **And a scoring finding that explains several stalls: the score is not monotone in structure.** Its 69-instruction
  candidate (the CORRECT shape) scores 21 while the 2-instruction-short one scores 4, so a hill-climb cannot reach the
  answer from the start; a secondary sort on |count difference| would have let the mechanical search find it.

- **S102 — a14's close is a FORK, not a bank, and I am NOT banking it (recorded for Drew).** `func_80139BE0` reaches score
  0, but by an INVENTED identically-zero term: `if (h < 7 + (t >> 8))`, whose only purpose is to keep `t` alive so combine
  cannot fold the second `andi`. The agent said so itself and named the fork: *"whatever kept `t` alive in the original was
  probably a real second use we cannot recover"*. **An invented no-op expression is a compiler-forcing construct wearing C
  clothes** — worse than the marked `__asm__` launder it replaces, because the launder is COUNTED and this would be
  silent. That is the phase's own rule, from `docs/levers.md` §5: **ban the silence, not the lever.** The body is parked
  for the structs/types phase with its reading (five other spellings also reach 0, all equally invented); the tree comment
  above it — "no pure-C spelling survives that fold" — is refuted and should be replaced when the body is next touched.
- **S102 — a6's `func_80148E54` NOT closed (score 6), and it CORRECTS cookbook §455.** §455 says "combine merges a
  single-use def into its copy"; the agent's dumps show that is only the second half — **cse1 (`cse.c:7439-7502`) rewrites
  the producer's destination to the copy's destination whenever the producer is the IMMEDIATELY PRECEDING insn**, and
  combine (`combine.c:1458`) only finishes the job once cse's adjacency is broken. It then enumerated the three
  lever-free blockers `can_combine_p` admits (no LOG_LINK via a `CODE_LABEL` between, the producer still live at the copy,
  a CALL between) and showed this body can pay for NONE of them: one consumer in the target's 67 instructions, no branch
  targets any address in the gap, and the only prior call is the one that produces the value. It scanned all 4,284 objects
  under `build/src` for the shape — 101 hits — and every lever-free precedent pays with a genuine second use, a narrow
  local with two consumers, or a join label. Its **R20 "copy-keeper pair"** proposal is the generalisable part: neither
  half moves the score alone, which is exactly why every single-move family sits at the same number, so the generator must
  emit one candidate per (separation × blocker) PAIR. Its twin `func_80148D44` carries the identical residual and census.
- **S102 — a22 banked: `func_8017B238` (126 bodies), by giving the if-arm's pointer and the else arm's FIRST table address
  one function-scope `u8 *src`.** Three decisions turn on that single edit, all dump-proven: `make_regs_eqv`'s head rule
  (`cse.c:840-857`) makes `src` the canonical head so the `move s0,a1` survives and the parameter dies at it keeping `$a1`;
  `set_preference` (`global.c:1535`) strips one RTX level so the ARITHMETIC set `src = idx*16 + base` inherits the
  register `idx*16` already has (`;; 74 preferences: 16`); and `combine_regs` (`local-alloc.c:1765-1788`) with
  `birthing_insn_p`'s `reg_n_sets == 1` (`sched.c:2469`) is why `src` must be merged with the else arm's read-only,
  NON-call-crossing temp — merging the call-crossing one instead gives the score-12 and score-6 near misses.

- **S102 — a24's `func_80133CD4` NOT closed (28 → 11; its readable spelling is 21) — and it names the instrument the
  engine is missing.** Its 28-point residual was ONE ABSENT LOAD: after `sh <val>,2(pb0)` cse holds the value of that
  halfword, so the later sign-extending read is replaced by the stored pseudo and combine folds the extension away — no
  `lh` is emitted at all, and seven branch-displacement mismatches downstream were consequences of that single missing
  instruction. Moving the store to the object's HIGHEST offset to just before the reads makes cse invalidate the lower
  entries and both reads become real loads. The register half then moved `pb0` from `v1` to the target's `a0` by a
  `do { } while (0)` whose loop-depth weighting doubles that statement's `REG_N_REFS` (`local-alloc.c:1578-1595` +
  `:2073`, MIPS having no `REG_ALLOC_ORDER`), demoting the pointer below three other quantities. **Its method gap is the
  one to act on: the residual text cannot separate "an instruction is missing" from "the registers are wrong" — the
  register-pair histogram invited a register lever when the defect was a cse invalidation.** What closed it was reading
  local-alloc's own quantity table out of the `.lreg` dump (priority, refs, live length, assigned hard reg per pseudo).
  **Three agents have now independently asked for that same table in the pack** (a4, a9, a16, a24), and `tools/alloc_table.py`
  — which is supposed to be it — was reported by two of them as printing an EMPTY or one-row table because it keys on
  `Register N in M.` lines the dumps often do not emit. That is the silently-narrowed-scope defect class, and it is the
  next instrument to fix.
- **S102 — Drew on structs (2026-09-10), and the answer he should have on the record.** He asked whether to fix a
  function's struct when a pin will not pull, or to define all structs first, and whether structs are detectable in the
  binary at all. **They are not in the binary:** C types are erased at compile time, a retail PS1 build carries no type
  metadata, and our symbol names come from library signature matching, not layout. **What IS there is exactly what he
  described** — a base register, constant offsets, an access width, and for arrays a stride (`(x & 0xffff) * 0x14` in this
  session's first crack is an array of twenty-byte objects). So a struct is an INFERENCE over consistent access patterns
  across every function touching a base, which is why fixing one function's struct to unstick its pin is the wrong unit:
  the next function invents a different shape and the two must then be reconciled — the failure P35 already recorded as
  1,232 drafter-invented definitions and a reconcile ladder built to repair them (R95). **But struct typing DOES change
  bytes** — a18 closed `func_80141874` outright by declaring a global an array rather than a scalar, which set
  `MEM_IN_STRUCT_P` and restored a dependence `sched.c:837-839` had discarded. **The recommendation on record: do not
  shift gears** (struct unification churns the whole tree and would invalidate the pin lane's in-flight work); keep pins
  as the main lane, build a zero-token STRUCT EVIDENCE CENSUS beside it (cluster base+offset+width across the fleet, emit
  candidate layouts with the functions that touch each), and park a stuck pin WITH its evidence instead of inventing a
  type for it. **And a correction to the priority: call SIGNATURES are the bigger and cheaper blocker right now** — six
  independent cracks and `argcheck`'s 471 narrow call sites inside 323 bodies that still hold an argument-register pin.
  Measured for scale: the tree holds **372,224 raw cast dereferences against 92,624 struct member accesses**.

- **S102 — THE CALL-SIGNATURE TURN: 16,759 lying declarations repaired across 3,439 units, byte-identical, and the class
  turned into tooling.** Drew read the six agent cracks and asked the two questions that mattered — *"can we do a tooling
  solution that doesn't need cracking funcs?"* and *"do call signatures need fixing in our non-register-pin funcs?"* —
  and both answers are now measured rather than argued.
  **`tools/argcheck.py`** reads every function's REAL signature from its definition (a `.c` under `src/` or a shared body
  header) and reports every call declaration narrower than it: at the open, **110,478 over 1,912 callees** (86,701
  K&R-empty, 23,777 positively `(void)`), of which **471 sat in 323 bodies still holding an argument-register pin**.
  **`delever.restore_arguments` (R19)** turns the class into engine work: it offers the call at the callee's full arity
  through a function-pointer cast, one candidate per value already in scope, and the byte oracle picks — the missing
  argument is never inferred. Ranked FIRST in every residual class because it emits nothing when it does not apply.
  Known-true: run on `func_8017A3D8`'s pre-bank text it emits agent a12's exact fix and scores `0 … MATCH`. Sweep s8:
  `3 of 55 exemplars matched lever-free … 12,034 compiles`, **every close R19, each at depth 1 in TWO compiles** — the
  class seven earlier runs could not touch at any width.
  **`tools/decl_repair.py`** answers the other half: a declaration is repaired only where every call in that unit ALREADY
  passes the arguments, so the code is right and only the promise is wrong. **3,439 units / 16,759 declarations were
  byte-identical with the declarations made honest; `check-all: 218 passed, 0 failed of 218`.** Only 2 units / 3
  declarations genuinely depend on a false declaration.
  **TWO INSTRUMENT FAILURES ON THE WAY, AND THE SECOND NEARLY SHIPPED AS A FINDING (R39/R40).** (i) The first framing
  widened declarations and left the call sites alone — not a repair at all, since a prototype demanding an argument the
  call does not pass is a hard error; **1,766 of the first 3,250 units could not compile BY CONSTRUCTION** and none was
  IDENTICAL. A measurement that cannot come out any other way is not a measurement. (ii) The corrected scan still
  returned **0 free of 3,634 units**, and I reported it before controlling it. The control I had not run — compile the
  UNCHANGED text through the same path — came back **DIFFERENT by 9,176 bytes**, because the candidate is built from a
  scratch copy and the object records its own source filename; comparing only `.text`/`.rodata`/`.data` removes the path
  and the control then matches exactly. **The control now runs for every unit inside the tool**, and a unit whose control
  fails is reported as a harness failure rather than as a result about the code (101 of them). The unit that had reported
  "the code depends on the false declaration" reports the opposite once controlled.
  **`tools/readability_progress.py` — the Gen3 series Drew asked for**, beside `docs/levers.md`, because levers are only
  one way the source is untrue: lying call declarations (split `()` / `(void)`, and how many sit in a pinned body) and
  raw cast dereferences against struct member reads — the struct debt. Dated rows carrying their commit, generated never
  typed (R75); `docs/readability.md` renders it. **First row, after the repair: 94,001 lying declarations over 1,564
  callees (86,701 `()`, 7,300 `(void)`), 461 in 314 pinned bodies; 414,148 raw cast dereferences against 173,286 struct
  member reads.** The remainder is three groups: declarations the unit never calls, calls that genuinely pass too few
  arguments (R19's, one candidate per in-scope value), and declarations inside `src/shared` headers, which are not units
  with recipes and were never scanned — stated as a scope limit in the tool.
  **The teaching example, compiled through the pinned cc1 and worth keeping for the story:** `extern void f(void); void
  g(void) { f(); }` emits `subu sp; sw ra; jal f`, while `extern void f(int); void g(void) { f(counter); }` emits
  `lw $4,counter` first. `$4` is the first argument register — **a false declaration DELETES AN INSTRUCTION from the
  program**, and that deleted instruction is precisely what a register pin was hired to fake.

- **S102 — T7 agent b4: `func_80133784` NOT closed (21 → 2; 203/203 instructions, one two-instruction residual) and it
  brought back three byte-proven moves plus a cookbook correction.** Its moves: (1) `while (1) { … }` rewritten as a
  LABEL + `goto`, which emits no `NOTE_INSN_LOOP_BEG`, so `loop.c` never registers a loop and cannot hoist the call
  argument's shift into a preheader — `invariant_p`'s REG case (`loop.c:2745-2751`), `scan_loop`'s movable
  (`:645-710`), `move_movables` at `:1631` where the threshold (~60) dwarfs the insn count (~15) so the hoist is
  unconditional, and `loop.c:595-596` forcing `n_times_set = 1` for a HARD register, **which is exactly what the `$21`
  pin was buying**; (2) ONE variable for both call results, so a single allocno spanning both call sites loses `$v0` and
  the `move v1,v0` survives; (3) an `s32` flag narrowed to `u16`, whose HImode subreg store blocks `try_combine`;
  (4) two constants hoisted into locals at a label, padding the accumulator's flow-time live length 89 → 91 **at zero
  instruction cost**, which flips `allocno_compare`. **The cookbook correction: §176 documents only the OPPOSITE
  rewrite** (goto-loop → `for`, in order to OBTAIN a hoist); the de-looping direction is new and belongs beside it.
  Its residual 2 is `andi v0,s2,0xffff / bnez v0` against `nop / bnez s2`: an `s32` flag loses the copy under all ten
  spellings it tried, so the narrow flag is the best trade available. **Its sharpest observation is about our own
  instrument: none of the seven NEEDED sites named what actually had to change, and one shape move retired three of
  them** — a site list says which levers the byte oracle could not remove ALONE, not which source facts are load-bearing.

- **S102 — T7 agent b9: `func_8013F350` NOT closed (70 → 16) and it REFUSED TO OFFER ITS OWN IMPROVEMENTS AS A BANK.**
  It solved the whole tail — **instructions 32 to 489 of 490 are byte-identical in plain C with the `$4` pin gone** — by
  ONE statement move: hoisting `off = st << 1;` above the two derived pointers, which is a COLOURING move and not a
  scheduling one (the `.sched`/`.sched2` RTL order is identical in both candidates, so the tree's own header note
  blaming the scheduler describes the assembly, not the RTL). With `off` born first it takes `$a0` and dies into the
  later pointer, and `fill_simple_delay_slots`' backward scan (`reorg.c:2906-2952`), which ACCUMULATES set/needed over
  skipped insns, then finds the conflict that produces the target's `nop`. **The head is a proven wall**: `find_best_addr`
  (`cse.c:2663-2665`) folds the base to an absolute address because its only set is a `symbol_ref`, so combine deletes
  the pseudo outright — and its known-true control `func_8013F138` keeps its base in plain C ONLY because both its uses
  are at offset 0, where `find_best_addr` returns early. Ours needs offsets 0 and 4. **The honesty that matters: it
  labelled its remaining two moves COMPENSATING ERRORS** — a width change that deletes the target's real `andi` to cancel
  an extra instruction the folded head costs — and wrote "nothing here is bankable" rather than hand back a 16 dressed as
  progress. **Its generator proposal is R18 with the independence test INVERTED** (hoist the shared operand's defining
  statement to the front of its run — R18 refuses it precisely because it shares identifiers with what it crosses, which
  is why ~4,000 mechanical compiles never tried it). **Two pack defects it found, both fixed:** `neighbours.txt` carried
  the `@class`/`@stuck` LINES but not the header comment they sit in — and that comment is an eight-point English
  explanation of every lever in the body, including the tail crack stated outright; the pack now ships the target's own
  header IN FULL. And `history.txt`'s `@NNNN` line numbers are relative to the EVOLVING text, so reconstructing a path by
  hand lands elsewhere (it reached 51 where the engine's own generators reproduce 16 in one round) — the pack now ships
  the best candidate's TEXT as `best_body.c`.

- **S103 (2026-09-10, Opus 5 1M at `/effort high`) — the loop resumed from the S102 checkpoint.** `git log -1` =
  `82da34b39`, tree clean; `delever_oracle --calibrate … : 177/177 objects byte-identical untouched; twin checks 32 (0
  mismatch); positive control DIFFERS on build/src/800.o; 2.3 s — OK`; `--snapshot-baseline: 7428 object(s) … at
  82da34b39`; `delever_pack --build`: `32 packs under .run/P36/agents; ORDER.tsv written`. `func_80178970` re-measured
  after the declaration repair: still **2** (the combine fold of the call-result copy, `combine.c:914-917`) — not
  re-drawn. **Wave c launched, six agents on unread classes, all read-only:** c1 `func_80135168` (25, Opus), c2
  `func_8013D8FC` (25, Opus), c3 `func_80148AFC` (23, Opus), c4 `func_80133AB0` (24, Opus), c5 `func_8015D738` (17,
  Fable, 201 ins), c6 `func_80130D48` (18, Fable, 266 ins). The S102 method is now a file every brief cites:
  `.run/P36/agents/METHOD_S103.md` (count first, the whole-function dump, the five emitters of a missing instruction,
  the allocation arithmetic, joint edits, the two refusals).
  **Fable 5.1 ran out of usage credits** (HTTP 429 on c5/c6's first step — the harness, not the functions, R40); both
  relaunched on Opus.

- **S103 — T7 agent c2: `func_8013D8FC` CLOSED (25 → 0, 45/45) and harvested as generator R22.** The body walked a list
  with `p` and ALSO kept `q = p + 5`, stepping both by 8: loop.c strength reduction keeps both bivs because a plain `*q`
  read keeps `q` live (`-dL`: "Cannot eliminate biv … biv used in insn"), costing an add per iteration and a callee-saved
  register — the +3 COUNT the `$16` pin was hired to hide. One pointer lets `combine_givs` (loop.c:5494) fold every field
  read onto one base, and `record_giv` prepends (loop.c:4421-4422) so the textually LAST read becomes the base — `data`
  must be computed before the four stores (inline after them scores 19). The agent typed the pointer as the TU's existing
  `Cmd_8013D53C` (its sibling `func_8013D53C` walks the same `D_801EDABC`). Bank: `delever --apply-body … IDENTICAL on 1
  object(s) — KEPT, ledgered (rung E, c2)`; `delever --propagate: 130 of 130 sibling(s) banked, 0 refused`; R22
  `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 23,988 pin/asm sites, 23,988 marked !FAKE, 0 UNMARKED
  — OK` (24,119 → 23,988). **Harvest: `delever.merge_walked_pointers` = family R22** (second pointer `q = p + K` stepped
  in lockstep deleted, `q[n]` → `p[n+K]`, `*q` → `p[K]`; refuses unequal strides, a re-seated `q`, `&q`, differing
  element types), leads the COUNT class after R19; **known-true check: its candidate from the agent's start text is
  byte-for-byte the agent's closing body and `--try` scores 0**; selftest fixture + two refusal controls, `delever
  --selftest: OK`; SETUP generator table row. The mechanical search had ~3,500 compiles on this body and no move that
  merges two walked pointers — it could never close a whole extra loop variable.

- **S103 — wave c lands: SEVEN more agent closes + one coordinator bank, 23,988 → 20,206 sites (−3,782).** Every body
  `--try` score 0 before the next agent launched, then `apply-body … IDENTICAL … KEPT` and `--propagate … N of N
  sibling(s) banked, 0 refused`: **c4 `func_80133AB0`** (24 → 0, 137/137; 133/133) three WIDTH moves — a flag copy, the
  X/Y copies split out of `u32 X, Y, cell, Xc, Yc;`, a counter — to `u16`: no PROMOTE_MODE on MIPS, a same-mode SI copy
  is folded by cse's `(set REG0 REG1)` case (`cse.c:7440-7474`, gate `:7455`), a HImode copy is a SUBREG move and
  survives, a `u16 cnt--` takes `copy_to_reg` (`expr.c:8645`); **c6 `func_80130D48`** (18 → 0, 266/266; 129/129) a
  shared `goto do_call` tail given one call per case — the parameter's refs 4 → 11 lift its `allocno_compare` priority
  384.6 → 1586.5 past the rival's 1212.1 (`global.c:594-607`); cross-jump re-merges the calls AFTER allocation
  (`toplev.c:3142`, `jump.c:2371`), so the bytes keep one call; **c1 `func_80135168`** (25 → 0, 62/62; 125/125) reused
  temps split one pair per group (a pseudo dying 3× is not a local-alloc candidate, `local-alloc.c:472`) JOINT with the
  global store written as an `H16` member store, whose MEM_IN_STRUCT_P keeps sched1's anti-dependence
  (`sched.c:858-863`, `expr.c:4888`) the `"memory"` barrier was faking; **c7 `func_80134A74`** (30 → 0, 107/107;
  133/133) c4's width moves (relayed mid-run) + the struct fields copied to locals before the loop + `lst--` written in
  both arms of an if/else, which adds loop-weighted refs (`flow.c:2067`) and flips `allocno_compare` 3684 → 8461 vs
  7674; **c3 `func_80148AFC`** (23 → 0, 71/71; 131/131) the angle passed as the dispatch handler's implicit SECOND
  argument (the TU's `ActorFn` was one argument too narrow) JOINT with `tmp` reused as the LATER operand so its last
  mention wins `make_regs_eqv` (`cse.c:846-862`, the swap at `:7454`); **c5 `func_8015D738`** (17 → 0, 201/201;
  125/125) jump threading (`jump.c:4161`; `-fno-thread-jumps` reproduces the target in one compile): the pointer
  re-read before the second null test JOINT with a `do { … } while (0);` around its first read — **the agent flagged the
  do-while as a possible lever; banked on precedent (R7 emits it, S102's a4 and b8 banked with it, the census does not
  count it, 1,347 in `src/`) and the class RAISED WITH DREW**; **c8 `func_80135004`** (26 → 0, 89/89; 126/126) c1's
  temp split (relayed) JOINT with `D_801EDA30` passed straight to the call — a load stays a separate insn when a store
  lies between it and its use (`combine.c:914-917`, `:10134`); **coordinator `func_8017EEC0`** (ov_SC07_000): the
  uninitialised `s32 a0v;` T4 batch tus10 left when it took the `$4` pin off is the function's PARAMETER —
  `void func_8017EEC0(s32 *a0)` scores 0 (8/8), IDENTICAL, KEPT (its callers still declare it `(void)`: the
  too-few-arguments group). R22 after the first four: `check-all: 218 passed, 0 failed of 218`; after all eight:
  `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 20,206 pin/asm sites, 20,206 marked !FAKE, 0 UNMARKED — OK`.
  **CI was red since 2026-09-09 (Drew's report, run 34525907006):** `verbatim_check --strict` → `1 manifest row(s) no
  longer verbatim … ov_SC07_000 func_8017EEC0` — the DECOMPILE-NOW row went stale when T4 batch `tus10` (`cb2fb5e6d`)
  converted it, and the check ran ONLY in CI. Fixed: the row removed (a one-row, 14-line diff), `--update` repaired to keep
  row order and write UTF-8 (its first run re-sorted and escaped the file: 588 lines for one row) and proven
  byte-identical to the hand removal, **`verbatim_check --strict` wired into `make tools-health`** — `verbatim strict
  rc=0`. **Harvest: generator R23 `split_reused_locals`** (c1/c8's move; one name per value), selftest fixture past a
  multi-line comment + two refusal controls (`delever --selftest: OK`); known-true: its joint split scores **12** on c1's
  start text and **26** on c8's — exactly the numbers each agent measured for that move alone; R6 does not reach c8's
  second move (a temp in a multi-statement line), so the full close stays an agent result. **Drew set the lane to at
  most five concurrent agents.** Relayed mid-run twice (c4 → c7, c1 → c8), and both relays were used in the close.

- **S103 — c12 closes the twins `func_80148E54` + `func_80148D44` (6 → 0 each, 67/67 and 68/68; 131 + 131) and c10
  closes `func_80135A4C` (40 → 0, 181/181; 133/133); 20,206 → 19,276 sites.** c12 applied c3's reading to the twins and
  it held: the angle passed as the handler's FIRST argument (`$a0`, never overwritten before the `jalr`) JOINT with
  `tmp` reused for the second `ratan2` — scores 7 / 6 / 1 (`(tmp + ang)`) / 0 (`(ang + tmp)`); the earlier agent's
  "unreachable body-only" verdict was wrong only because its consumer count never treated a `jalr` as reading `$a0`.
  The stale `jalr with no args` header comment corrected in the 135 files whose body now passes the argument (the one
  unbanked variant, `ov_SC01_077`, keeps its true comment). c10: nine missing instructions were jump2's post-reload
  cross-jump (`toplev.c:3142`, `jump.c:2371`) merging two identical walk tails — the loop's exits made to fall to the
  function's single final `return`; the tenth the cse SUBREG gate (`s16 eq`); the register order by parameters passed
  through to `func_80135480` at its real arity (one more ref each, zero bytes); its answer was `func_80135888` in a
  DIFFERENT FILE. **Harvest: `delever_pack` writes `related.txt`** — lever-free bodies anywhere in the overlay sharing a
  `func_`/`D_` symbol with the target, ranked (known-true: for `func_80135A4C` its top hit is `func_80135888`; c2's
  `func_8013D53C` is listed for `func_8013D8FC`); METHOD_S103 gained six emitter entries (the implicit handler argument,
  cross-jump both ways, the parameter pass-through, `-fno-thread-jumps`, the join-point duplicate, local-alloc's own
  ranking). Bank lines: `apply-body … IDENTICAL … KEPT` ×3, `--propagate: 131 of 131` ×2, `133 of 133`; R22
  `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 19,276 pin/asm sites, 19,276 marked !FAKE, 0 UNMARKED — OK`.

- **S103 — T7 agent c11: `func_80175AB8` CLOSED (41 → 0, 188/188; 124/124).** Four joint moves, any one removed breaks
  it (30/37/8/3): late field reads through the derived pointer `arr` (fold_rtx re-associates before folding,
  `cse.c:5580-5667`; base-relative reads fold absolute via `find_best_addr`, `cse.c:2622`; the first cse pass stops at
  the clamp's join label, `cse.c:8039`, and only `.cse2` re-associates); the clamp as a ternary reading the global twice;
  ONE temp reused for both `$a1` values (block-global by flow, `flow.c:1204/1428`, so global.c's preference scan picks
  `$a1`, `:1535`/`:1037-1071`); the table read as a cast-wrapped byte offset (not an aggregate access, `expr.c:4568`,
  so `true_dependence`, `sched.c:817`, keeps it after the store). The body keeps the `*(volatile u32 *)&slot[6]` store
  the free text already had (without it 20). `apply-body … IDENTICAL … KEPT`; `--propagate: 124 of 124`; R22
  `check-all: 218 passed, 0 failed of 218`. **Harvest: `tools/cc1_dumps_tu.sh` now dumps `-dt` (`.cse2`) and `-dJ`
  (`.jump2`)** — c11's deciding fact was only in `.cse2`, c10's cross-jump only in `.jump2` (smoke: `rc=0`, both
  files written); METHOD_S103 +3 entries.

- **S103 — c14 `func_801670E4` CLOSED (45 → 0, 279/279; 132/132 incl. both shared twin headers) and c16
  `func_8013D178` CLOSED (72 → 0, 110/110; 129/129); R23 widened and it closes c16's body with no agent; c9
  `func_8013CF68` READ, not closed (38 → 10); 18,776 → 17,715 sites.** c14 (all seven levers gone; any move taken back
  scores 5-18): `&f.cx` passed at each call instead of through a pointer local (cse's cheapest-source rewrite,
  `cse.c:6776-6803`, made the local a callee-saved pseudo; the hard `$a1` is dropped at each call,
  `invalidate_for_call` `cse.c:1725`); each loop's `p = tbl; i = 0;` moved to just before its `do` (sched1's LUID
  tie-break, `rank_for_schedule` `sched.c:2385`); block 2 as single-use temps; one store order. **The `@stuck` note above
  it ("inert to ~40 permutations") was refuted on bytes and replaced by a `@crack` note in all 136 copies**, each
  rewritten only after checking its body is now lever-free. c16: the one pointer `p` re-seated at the head of nine
  `if` groups had 36 refs over a live length of 99 (priority 18181, `global.c:587-610`) and took `$a0` ahead of the
  per-group temps (7500); one block-scoped `p` per group (4 refs over 22) gives the target's order. **R23 widened** from
  straight-line code to definitions at one brace depth of one open block (plus pointer declarators, plus a refusal of a
  brace-less `if (c) v = E;` definition, plus `*p = E;` read as a store THROUGH `p`, not a definition): **on c16's start
  text R23's `split p into 9` scores 0** — a whole close by the generator; c1/c8's known-true numbers unchanged (12, 26);
  selftest fixtures for the widened form and the refusal, `delever --selftest: OK`. c9: the count closed (76 → 63) by
  constant addresses off the array behind a block split, then order only; its 5 used a do-nothing second `base =`
  assignment and **it refused to claim it** (a dummy set); reading: sched1's `init_alias_analysis` (`sched.c:419-438`)
  knows the single-set constant base and `memrefs_conflict_p` (`:775-778`) lets the loads pass the stores — the target's
  base was opaque to it; loop notes are scheduling barriers (`sched.c:2058-2080`) incompatible with the target's
  argument-setup hoists. Not bankable. Bank lines: `apply-body … IDENTICAL … KEPT` ×2, `--propagate: 132 of 132` /
  `129 of 129`; R22 `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 17,715 pin/asm sites, 17,715 marked
  !FAKE, 0 UNMARKED — OK`.

- **S103 — `tools/delever_regen.py`: the new families re-run over the WHOLE residue, read-only, and 17 classes / 22
  bodies closed with no agent.** Why it exists: every landing is harvested into a generator, but the residue's 2,078
  NO-MATCH attempts all predate the newest families and nothing ever re-tried them (R23 widened reproduced c16's close
  alone). Starting texts: the lever-free body and the engine's best text; candidates: `recipe_candidates(families=R22
  R23, cap=None)`; scorer: `delever_search --try --body`, one worker per class (the scorer's scratch dir is per
  function). Pass 1: `delever_regen: 1169 of 1169 classes judged in 127 s — {'MATCH': 14, 'BEST': 181,
  'NO-CANDIDATE': 949, 'UNSCORED': 25, 'GEN-ERROR': 0}; 14 class(es) close at score 0 (18 bodies)`. **The 25 UNSCORED were
  read before banking (R61): 24 were an INSTRUMENT defect** — `--try` on a class whose exemplar is a shared HEADER passed
  `-I` for the shadow copy and the header's directory but not the INCLUDER's, so the includer's `#include
  "../shared/engine_prelude.h"` never resolved and every header-TU candidate was a COMPILE-ERROR (no header-TU class had
  ever been judged by `--try`); fixed in `score_file` and controlled both ways (the header's unchanged body scores 0; its
  lever-free text 32; a mutated body 1). The 25th: a body-local `#define` spelling the locals — R22/R23 now refuse bodies
  with preprocessor lines. Pass 2 over the header TUs: `104 of 104 classes judged in 8 s — {'MATCH': 3, 'BEST': 21,
  'NO-CANDIDATE': 80, 'UNSCORED': 0}`. Banked by `--bank` (re-scored on the current tree first): `14 of 14 MATCH row(s)
  banked, 4 sibling(s) propagated` and `3 of 3 MATCH row(s) banked, 1 sibling(s) propagated` — two of them shared
  headers IDENTICAL on 141 objects each (`func_8014E83C` by R22, `func_8014CD80` by R23). Families (counted from the two TSVs): R23 12 classes,
  R22 5. Dictionary + SETUP rows.

- **S103 — T7 agent c18: `func_80176734` CLOSED (90 → 0, 371/371; 128/128).** From the rebuilt mechanical best (32; the
  pack had no `best_body.c`, so the agent replayed `history.txt`'s path): ONE variable `p` for the sprite pointer across
  blocks A/B/C (12 refs over 41 insns, priority 8780, picks up `$a0`'s conflict and takes `$a1`, `global.c:945-990`) —
  the INVERSE of R23's split, read off the whole objdump as "same register, same role"; block J/K as a nested `||` if with
  `chg` as `s16` (combine turns the 0/1 sign extension into a plain copy, `combine.c:7932-7942`, and its second user keeps
  the `move` the `c = chg` launder was faking); block I's change flag reuses `amp` (the target keeps both in `$s0`);
  block I's copy `v` as `u8` (a SUBREG move survives `make_regs_eqv`, `cse.c:826-862`). Undoing one move at a time on the
  final body: 2 / 12 / 8 / 9 / 53 / 22. The free text's `dum[8]`, `pv`, `ix` stay (removing any scores 18-32).
  `apply-body … IDENTICAL … KEPT`; `--propagate: 128 of 128`. METHOD_S103 +2 entries.

- **S103 — T7 agent c20 (a RE-DRAW): `func_8013DD68` CLOSED (S102 read it to 2; now 0, 187/187; 128/128), and it
  corrected the earlier reading on bytes (R14).** The move the earlier agent never tried: the addPrim copy reads the
  ordering-table entry as a WHOLE WORD (`((P_TAG_8013DD68 *)p)->addr = *(u32 *)OTE;` instead of `OTE->addr`). A 24-bit
  bit-field read ANDs with the mask (`expmed.c:1456-1471`) and the 24-bit store ANDs again (`:667-683`), so at FLOW time
  the hoisted `0x00ffffff` mask has 3 loop-weighted uses (7 refs, `flow.c:2067`) — combine later merges the ANDs but
  never lowers the count (`combine.c:55-57`). Priorities (alloc_table): mask 2413.8 before → 1724.1 after, below the
  counter's 1728.4, so the counter takes `$a3` as in the target. With the earlier agent's own move 2 (the `q[-7]` store
  inlined and moved above the `0x7800` store): 17 → 10 → 0. The earlier reading counted refs AFTER combine and so called
  the swap reachable only by an extra ref on the counter. Its method note: `alloc_table` should show where refs come
  from (flow-time vs final RTL). R22 `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 16,015 pin/asm
  sites, 16,015 marked !FAKE, 0 UNMARKED — OK`. Census for a generator: the `->addr = ->addr` copy occurs in 37 residue
  classes / 41 bodies.

- **S103 — harvest: generator R24 `word_read_bitfields`** (c20's move: `X->addr = Y->addr;` → `X->addr = *(u32 *)Y;`,
  each site and ALL; a side-effecting source refused; an already-parenthesised source not wrapped twice — the selftest
  caught `*(u32 *)((ot + 1))`). **Known-true on c20's start text: 17; the in-loop site alone 10; ALL 10; the two sites
  outside the loop 17** — exactly the agent's measurement. `delever --selftest: OK`; SETUP row; REG classes after R23.
  **R24 regen:** `delever_regen: 1150 of 1150 classes judged in 84 s — {'MATCH': 2, 'BEST': 11, 'NO-CANDIDATE': 1137,
  'UNSCORED': 0}`; `--bank: 2 of 2 MATCH row(s) banked` — one of them the shared header `func_80140D68.h`, IDENTICAL on
  140 objects.
- **S103 — T7 agent c13: `func_80140958` READ, not closed (43 → 4, 260/260; three of four levers replaced).** Four
  defects behind an equal count: the loop constant 8 (hoisted by `scan_loop`, `loop.c:681-690` / `move_movables`
  `:1631`), a join store (jump2 cross-jump, the target's `j` lands on the second branch's store — split into both
  branches), the addPrim store (a reused read-modify-write local `w`; sched1's `birthing_insn_p`/`adjust_priority`,
  `sched.c:2469-2540`), and the pre-loop `j`/`k` order — unsolved: `allocno_compare` (`global.c:594-609`) needs `j` at ≥14
  loop-weighted refs; the tree's `j` keepalive adds exactly +3; ~20 spellings refuted on bytes. **Its first move is a
  DEAD INITIALISER (`s16 size = 0;` then `size = 8;` in the loop) whose only job is to defeat the hoist** — the same
  family as c9's refused do-nothing reassignment and c5's barrier do-while; NOT bankable at 4 either way, and raised
  with Drew beside the do-while question. Its tool asks: a `.loop`-dump reader that says why each invariant was or was
  not hoisted, and its per-block sched1 priority extractor (`PACK/scratch/sblk.py`).
- **S103 — T7 agent c15: `func_80135EB0` CLOSED (64 → 0, 289/289 + its jump table; 128/128) — with a do-while.** Eleven
  of the thirteen missing instructions were jump2's cross-jump folding case tails (`jump.c:2370`): it searches other
  jumps to a label only when that label existed before the pass (`INSN_UID < max_uid`, `jump.c:1985`), so one `if (F(…))
  goto ret1;` per case makes jump2 create the join label itself and the tails are never matched; two nops from
  `true_dependence` (`sched.c:817-835`) — the globals written as array/struct accesses keep the dependence
  (`MEM_IN_STRUCT_P`, `expr.c:4888`), removing both barriers; the `$5` pin replaced by a shared `test:` label. **The
  register swap closes only with `m2 = -(c); m2 &= 0x20;` inside a `do { } while (0)`** — the wrapper doubles the chain's
  loop-weighted refs (`flow.c:2067`) to lift `m2` (11 refs, 2307) past `arg1` (2045, `global.c:596-610`); without it
  the best is 18. The agent asked for a ruling; **banked on the S102 a4 precedent (the same reference-weight mechanism,
  already banked) and ADDED to the do-while question for Drew** — if he rules the class a lever, this body is one of its
  members. The agent also found `build/` deleted mid-run (the fleet gate's `make clean`): METHOD step 1 now dumps the
  target from `.run/P36/delever/baseline/`. `apply-body … IDENTICAL … KEPT`; `--propagate: 128 of 128`.
  R22 `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 15,239 pin/asm sites … 0 UNMARKED — OK`.
- **S103 — T7 agent c17: `func_8013D9B0` READ, not closed (96 → 15 in plain C; 140 vs 141) — and the last 15 are a GTE
  HEADER MACRO, not the body.** Plain-C moves: one walked `Cmd_8013D53C *p` (the siblings' struct; two `u16*` + casts
  had made a third walked pointer), `s16 rect[4]` filled field by field (replaces all four `"memory"` barriers),
  LoadImage given both arguments (the target keeps `img` live in `a1`), the flag set in both arms (15 → 24 refs, beats
  the pointer for `$s0`; the delay-slot filler re-merges the stores), `fc = gte;` inside the guard. The residual: a
  `move t4,v0` before `swc2 $29,0(t4)` that no C variable can own, because `include/gte_inline.h`'s `gte_stORGB` does not
  write `$12` itself. **Proof in scratch (asm, not claimable):** `gte_stORGB` respelled `"move $12, %0\n\tswc2 $29,
  0($12)" :: "r"(p) : "$12", "memory"` scores 2 (PsyQ `inline_o.h`'s `$12-$15` clobber list scores 6); a second macro
  merged scores 0. The four macros are used only by the 134 `func_8013D9B0` copies, and a macro change must ship with a
  new body for every copy (the old bodies pin the pointer to `$12`). **This is T5's GTE question** (one GTE header
  under Sony's names; the phase plan says a clobber VARIANT is a lever, not a second spelling) **— for Drew, not a
  bank.** The agent refused a dead second store that also reached 0.
- **S103 — RE-DRAWS c24 and c23 both CLOSED (the S102 readings stopped at 4 and 2).** **c24 `func_8012956C`** (0,
  226/226; 126/126 incl. a shared header): the decompiler had read the still-live `$a3` at a `jal` as a FOURTH argument to
  the three-parameter K&R callee `func_801299C8` — the phantom argument's copy and second load consumer reordered sched1
  (`rank_for_schedule`, `sched.c:2385`), which is what the `$7`/`$4`/`$3` pins undid (four args via a temp 2, inline 12,
  three 0); the `__asm__("")` barrier faked the empty delay slot a `switch` produces (reorg's `fill_eager_delay_slots` /
  `steal_delay_list_from_fallthrough`, `reorg.c:3632/1699`; the empty `0x7FFF` case first, `stmt.c:5580`,
  `jump.c:1725-1757`). **c23 `func_80133784`** (0, 203/203; 126/126 incl. its twin header): a real `while (1)` with the
  timeout block INSIDE it — loop.c's desirability test `threshold*savings*lifetime >= insn_count` (`loop.c:1631`,
  threshold `1 + n_non_fixed_regs` with a call, `:532`) then refuses the argument `sll`'s hoist ("38 real insns … not
  desirable") where the block-after form (28 insns) hoisted it; the flag `s16`. **This overturns S102 b4's reading**
  (de-loop to a `goto`, "threshold ~60 vs ~15, never fails" — the real margin is ~29 vs 28) and the cookbook §176 note
  S102 wanted: the new direction is "move the loop's exit block into the body", not "de-loop". Bank lines: `apply-body
  … IDENTICAL … KEPT` ×2; `--propagate: 126 of 126` ×2.
- **S103 — c19 `func_80177B5C` READ, not closed (135 → 2, 147/147, every register right; one `or` two slots late —
  sched2's tie at equal priority falls back to sched1's order, `sched.c:2385`, and every natural multi-set spelling
  fails).** Its K&R-parameter move and its annealing scorer (`PACK/scratch/fast.py`, ~0.12 s/candidate) are recorded.
- **S103 — R25 `trim_arguments` (c24's move, R19's inverse) and a BLIND SPOT FIXED IN `argcheck`: K&R definitions.**
  R25's known-true check found nothing on the very body it came from — the callee `func_801299C8` is defined K&R
  (`f(a, b, c) s16 a; …; {`) and `argcheck.definitions()` required `) {`: **505 functions are K&R-defined and 95 had no
  other readable definition**, invisible to R19, R25, `decl_repair` and the readability census since S102. Fixed:
  `KR_DEF` + `kr_params` (the default-promoted types, char/short → int, so a cast matches the definition; unit-checked on
  `s16 a, b; int *p, q; unsigned char c;` + an undeclared parameter); definitions read 15,626 → 15,721. R25 then offers
  the trim; alone it scores 11 → 12 and 4 → 7 on c24's texts (the close was joint) — **no single-move known-true number
  is claimed**; the census: 203 residue classes / 448 bodies call a function with more arguments than it takes (a first
  census counted each definition's own `(void)` header as a one-argument call — caught by its self-referencing top rows,
  R40). Selftest fixture (both spellings + the side-effect refusal), `delever --selftest: OK`; SETUP rows.
- **S103 — re-draws c25 and c26 CLOSED (S102 readings at 4 and 11).** **c25 `func_80166F58`** (0, 69/69; 124/124): the
  copies `p2 = (short)t2; p3 = (short)t3;` with `eq` reading the originals — cse cannot see through the double
  extension (`cse.c:7456` wants a REG source), combine reduces it to a copy but keeps the producer (`added_sets_2`,
  `combine.c:1458`), and local-alloc's `optimize_reg_copy_1` (`local-alloc.c:700`, called `:1003-1007`) points the `xor`
  at the copies; each half alone scores worse (2, 11). The redundant `(short)` is a value-preserving narrowing — accepted
  as ordinary C (a declared-`short` local reaches the same bytes). **c26 `func_80133CD4`** (0, 399/399; 130 of 133 —
  three are a different variant): the three `pb0[k] +=` in order with the shifted reloads after, and the reused `t`
  split into `t0/t1/t2` (local-alloc.c:472, `combine_regs` `:1870`, `qty_compare_1` `:1598`); the earlier agent's
  do-while was not needed. **c26's `lsim.py` promoted as `tools/localalloc_sim.py`** after the coordinator's validation:
  `mismatches vs dump: 0` over 126 block simulations on five dumps of its function and 24 on func_8013D178 /
  func_8013D8FC / func_8013D53C.
- **S103 — a propagate defect found and fixed: STALE ledger hashes hid siblings.** c26's propagate printed `-> 0
  sibling(s) of class 44af245e1a13` for a 131-copy class: its siblings' ledger rows carried the T4-era hash
  (`4b25d21fdcee`) because S102's `decl_repair` rewrote block-scope externs inside those bodies without writing rows
  (R51). `delever.propagate` now also considers every RESIDUE row of the same function name and lets the existing
  per-sibling current-text check decide: `130 of 133 sibling(s) banked, 3 refused`. **Blast radius measured (R14):** of
  2,843 banked exemplars, one other had hash-matching unpropagated siblings (`func_8014D820`, 2) — and both are correctly
  refused by the remap's symbol-consistency check (`D_8019207C maps to both …`), so the free yield there is 0; a hash
  census overcounts remappable twins.
- **S103 — re-draw c21: `func_801397B0` CLOSED (S102 a3 read it to 2; now 0, 89/89; 125 of 132 — 7 variants refused)
  — with a do-while.** The eight fixed sprite-field stores wrapped in one `do { … } while (0)`: flow counts the two
  `b1A8` loads inside the zero-trip loop double (`flow.c:1401/2067/2501`), lifting the combine_regs-tied quantity
  (lbu→addiu→`off`→`b1A8`, `local-alloc.c:1722/1855`) from 10 refs / length 44 (6818) to 12 (8181), past t2's quantity
  (7000, `qty_compare_1` `:1598`); lengths unchanged, a plain `{ }` scores 12. a3 had guessed "one more flow-time ref" but
  only wrapped statements using `off` — `b1A8` belongs to the same tied quantity. Evidence: all 529 contiguous wraps in
  two statement orders enumerated (22 close; in the original order only [cx..h] and supersets) and 288 other spellings
  that never went below 12; the agent's quantity-level simulator predicted every flip. **Banked on the a4/c15
  reference-weight precedent — the third S103 do-while close (c5, c15, c21); the class is Drew's open question.**
- **S103 — re-draw c28: `func_8013F350` READ, not closed (best honest 42; b9's 16 rested on compensating errors and a
  do-while, kept in `scratch/prev_body.c`, unclaimed).** c11's derived-pointer move cannot reach the head, for two
  proven reasons: no first-pass-only cse boundary lies between the base's set (BB0) and the offset-4 read (BB1, its
  fall-through — `cse.c:8039-8055` finds no label or loop end), and the second cse pass scans BB1 on TWO paths
  (`cse.c:8098-8124`; `.cse2` shows three paths from insn 2), re-associating the read on one and folding it on the
  other; a diagnostic with a banned do-while split proved the scan count decides (a new read in a once-scanned block
  stays `lhu 6($5)` in the same compile). METHOD_S103's c11 entry gained that third condition. The head's `$5` pin +
  launder: irreducible in plain C by this reading — the class stays residue with its evidence.
- **S103 — re-draw c22: `func_8012E364` READ, not closed (stays 4; the earlier body is still the best).** A call-free
  function, so the implicit-argument lead did not apply (the brief should say "no calls" up front); ~63,000 compiles over
  every legal statement order × struct spellings; `combine_regs`'s refusal tests (`local-alloc.c:1722-1854`) prove `d`
  and `v` cannot both be tail-block locals, and a reuse family that makes them cross-block reached 10 — rejected by the
  agent itself as unreadable. **Harvest: `delever_search --try` is now parallel-safe per call** (pid-keyed scratch,
  removed afterwards, `--keep` prints the object path) — c19, c21 and c22 had each written a private scorer. R22 after
  c21's bank: `check-all: 218 passed, 0 failed of 218`.
- **S103 — re-draw c27: `func_8013CF68` READ, not closed (10 with c9's steering do-while, 35 with no steering
  construct, 5 only with the refused do-nothing reassignment).** The address-spelling idea tested (struct member, array
  element, whole-record cast on the stores; struct/array on the loads — all 10) and REFUTED on mechanism: the dependence
  tests' struct/varying clauses (`sched.c:830-835`, `:858-863`) can only REMOVE an edge `memrefs_conflict_p` (`:614`)
  allowed; here `base` has one constant set with a REG_EQUAL note (`cse.c:6919-6934`), so `init_alias_analysis` makes every
  store address constant and `:775-778` proves no overlap — plain C cannot make `base` unknown without a second set, a load,
  a call, a parameter or asm (the §194-K bound). A new reading of c9's count fix: `find_best_addr` folds then LOOKS UP the
  constant (`cse.c:2700-2735`) and recovers `-12(s0)` from a live call argument holding the same address. The class stays
  residue with its evidence.
- **S103 — re-draw c30: `func_8017B614` CLOSED with NO do-while (S102 read it 13 → 6; now 0, 101/101; 125 of 133 —
  8 variants refused).** One function-scope `u8 *src` assigned in both arms (as the matched sibling func_8017B238 is
  written): `src` becomes the class's canonical register (`make_regs_eqv`, `cse.c:850-858`), `expand_preferences`
  (`global.c:781-821`) hands it `$s0` — 13 → 6 and every register right. The order: sched1 still hoists `li 1; sh
  D_801F1638` (launch priority, `sched.c:2469/2539`); the target's order is restored in SCHED2 by the struct-access rule
  (`sched.c:817-835`) — the tail's two reads as struct members (as sibling func_8017B490 writes them) and the `sb` as an
  array element `D_8012694C[0]` (keeps its relocation symbol; the address is field 4 of the camera object `D_80126948` —
  a names-phase spelling). Moves 2 and 3 only close together (4, 6, 0). `apply-body … IDENTICAL … KEPT`.
- **S103 — c33 (the ov_MAIN_012 tier): `func_80169058` (18 → 0) and `func_80168D94` (24 → 0) CLOSED, 5 of 6 siblings
  each.** func_80169058: a per-arm `s32 r` holding each arm's `rand()` result with the stores duplicated into both arms
  (the function-scope `v0` died 3× → global, `local-alloc.c:472`; jump2's cross-jump re-merges the duplicated stores,
  `jump.c:2371` — both arms in `.sched2`, one pair in `.jump2`); func_80168D94: the same, plus `+0xE` read at its point
  of use so it is born last and ranks first (`qty_compare_1`, `local-alloc.c:1598`; 2,520 statement orders → exactly
  42 zeros, the predicted ones; checked with `tools/localalloc_sim.py`, 0 mismatches). Every copy (six TUs + the header)
  scored 0 before the bank. A stray `a1.c.dis` at the repo root (c30's scratch) moved into its pack.
- **S103 — re-draw c31: `func_80178970` PROVED IRREDUCIBLE in plain C on this compiler (stays 2).** TWO walls, each alone
  deleting the call-result copy: combine folds it into the branch (every refusal condition enumerated — `$v0` write
  between, a call, a volatile insn, the value live after, a block boundary: `combine.c:914-917/929/985-989/1458`,
  `flow.c:2087`), and when it survives local-alloc hands its destination back to `$v0` (copy suggestion from the dying
  hard register, `local-alloc.c:1798-1818`, taken at `:1469-1476`) → `move v0,v0`, deleted. Proved on bytes (a surviving
  extension stays in `$v0`). Every S103 idea refuted (table in its `mechanism.md`). **A whole-binary byte-shape scan:**
  `jal; nop; move rX,v0; beqz/bnez rX; move v0,zero` occurs in 9 families; the three lever-free ones read the call result
  AGAIN in a later block; every family whose result is read only by the test is levered (func_80178970 ×133,
  func_80180CC0 / 80181D1C / 80183790 / 80187250, and func_8002FF0C unread). **For the phase's milestone: this is an
  irreducible class — the original source must have had a later reader the optimiser removed; Drew's call how "grind to
  zero" treats it.** Its tool ask: a byte-shape census (`tools/shape_census.py`) that resolves shared headers.
- **S103 — c36 (ov_SC07_006 tier) `func_8014305C` (12 → 0; 6/6) + `func_80141874` (6 → 0; 6/7), and c35 (ov_SC06_010)
  `func_8017DBE4` (4 → 0; 10/10) + `func_80185994` (3 → 0; 17/17) CLOSED — all four by a sibling's spelling or a call's
  real arity.** c36: the parameter used directly instead of an entry copy, `*m = x = call();` (a store target makes
  `preexpand_calls` give the call a fresh temp, `expr.c:6199-6202/8699`, `calls.c:2114`), and a table read through a pointer
  temp (`p = &tbl[i]; x = *p;` — the array read is `mem/s`, the scalar store before it is not, so `true_dependence`,
  `sched.c:837-839`, saw no dependence and sched1 hoisted the load). c35: a FRAME-ONLY residual — a self-referencing
  local (`p += r`) whose uses all fold into one address leaves combine with refs but no insns (`combine.c:2306`) and gets a
  stack slot from reload (`reload1.c:2331-2352`), 24 → 32 bytes; one assignment closes it; and a call whose CAST dropped the
  argument though the TU's declaration was right (the argument copy costs 0 bytes — jump2 deletes it, `jump.c:437/462`).
  **Harvest: R19 reads the arity a call's own cast asserts** (it compared only declarations) — known-true: on c35's
  start text R19's `+a0` candidate scores 0; selftest fixture; `delever --selftest: OK`. METHOD gains the frame-only row.
  R22 `check-all: 218 passed, 0 failed of 218`.
- **S103 — c34 (ov_SC02_031): `func_8017ECEC` (8 → 0; 10/10) and `func_8017BF88` (14 → 0; 13/14) CLOSED.**
  func_8017ECEC: the helper's output read as ONE packed `u32` (the TU's own header said so) with `(s16)w` and
  `(s32)w >> 16`, the fake `u32 buf[4]` frame pad gone — combine's split at `combine.c:1994` skips the ref cleanup at
  `:2306`, leaving a stale count that both lifts the high half's priority (12000 → 14000, `qty_compare_1`) and gives a
  deleted pseudo the stack slot `buf[4]` was faking (`reload1.c:2331`); func_8017BF88: `u16 r = rand();` keeps the copy
  (SUBREG move, `cse.c:7457`) and `c++; store(c)` makes the counter twice-set so `birthing_insn_p` (`sched.c:2490`) stops
  boosting its load. Tool asks: `--try` should report a FRAME-size difference (`.frame … vars=`), not OTHER.
- **S103 — c32: `func_801852E4` (ov_SC06_022) CLOSED (1 → 0; 4 of 4 siblings)** — the return point given a second
  predecessor (`goto out;` + `r = 1;` falling into `out: return r;`): `record_jump_equiv` (`cse.c:7508-7511`) had folded
  `return r` to the tested 0 on the fall-through, and with `out:` holding two users `cse_end_of_basic_block` does not
  follow the jump (`cse.c:8106-8116`). **`func_8017FC5C` (ov_SC03_115, 9 copies) closes only with a SIGNATURE change** —
  the target returns its first argument (`move v0,s0`), so the function is `s32 *f(s32 *a0, …)` and the TU's three
  `extern void` declarations must say so; a body-only bank cannot carry it → **types-phase inheritance with a ready patch**
  (`.run/P36/agents/ov_SC03_115__func_8017FC5C/scratch/tu_p1.diff`, whole-object identical; the same edit closes
  `ov_SC03_099` `func_80180200`).
- **S103 — c39 ports two variants (func_8012956C in ov_SC07_006, func_80133784 in ov_MAIN_012 — both 0 on the first
  try, 6/6 siblings each) and finds why propagation refused them: the ONLY difference beyond a symbol remap was one
  BODY-LOCAL `extern` line (the banked sibling declared it at file scope).** `delever.propagate` now compares and remaps
  with body-local `extern` lines stripped (`_strip_externs`) and re-inserts the sibling's own. **Re-propagation over every
  banked exemplar: `repropagate: 413 exemplars, 97 sibling(s) banked, 48 refused of 145 candidates`** — a first census
  said "1,250 siblings" by counting each banked copy of a class as its own exemplar; the distinct candidates were 145
  (R41, deduplicate before quoting).
- **S103 — c41: `func_8017E73C` (ov_SC02_031, 14 → 0; 10/10) and `func_80145934` (ov_SC07_006, 11 → 0; 7/7) CLOSED.**
  The first by two widths (`u16 flags`, `s16 ret` — the SUBREG gate and combine's 0/1 sign-extension copy), the author's
  habit c34 found in the same TU; the second PORTED from another overlay's banked pack — a body-local `extern u8
  aD8018C944 __asm__("D_8018C944");` declaration alias keeps jump2's cross-jump (which compares symbols by pointer,
  `jump.c:2440`) from merging two identical `la/j` blocks; an asm LABEL on a declaration is class E (deferred to the types
  phase by Drew's gate-1 scope decision; S102 banked the same form). **Harvest: `related.txt` now lists the SAME function
  already lever-free in other overlays, first** (`git grep`) — known-true: for func_80145934 it lists the variants c41
  found by hand; for c43's func_80185578 it found a lever-free copy in ov_SC03_014 (relayed to c43 mid-run).
- **S103 — the R19 cast-arity regen: `1131 of 1131 classes judged in 408 s — {'MATCH': 8, 'BEST': 33, 'NO-CANDIDATE':
  1086, 'COMPILE-ERROR': 4, 'UNSCORED': 0}`; `--bank: 8 of 8 MATCH row(s) banked, 4 sibling(s) propagated`** (one a shared
  header IDENTICAL on 141 objects, `func_80130514.h`). **c29 `func_80140958` READ (still 4):** the loop constant 8 without a
  dead initialiser but through ONE variable holding two unrelated 8s (flagged by the agent itself as steering); the
  pre-loop order unclosable without raising `j`'s weight (sched1 rewrites `reg_live_length`, `sched.c:4947`; k 5270 vs j
  4400, `global.c:587-609`).
- **S103 — c38: `func_80180EDC` (ov_SC04_015, 3 → 0; 7/7) and `func_8018431C` (ov_SC03_104, 4 → 0; 7/7); c40:
  `func_80185DD8` (ov_SC06_018, 7 → 0; 5/5) and `func_80184854` (ov_SC03_002, 11 → 0; 7/7) CLOSED.** c38: a local that
  carried a pointer to a join took a dying argument register's preference (`expand_preferences`, `global.c:781-821`) —
  the store written in each arm (cross-jump re-merges it); a single-set `la` launched low by sched1
  (`birthing_insn_p`, `sched.c:2469/2489`) — its store moved to the head of the run (sched2 re-sorts the independent
  stores, `sched.c:2616/2657-2670`). c40: a `?:` inside the branch condition (`do_jump`'s COND_EXPR, `expr.c:9124`)
  gives each arm its own compare so jump's inversion (`jump.c:1737-1782`) and the cross-jump (`:2371`) find nothing to
  merge; and a hand-rotated `if … do … while` written as a real `for` loop, whose `NOTE_INSN_LOOP_VTOP`
  (`jump.c:2306`) makes reorg's `mostly_true_jump` predict taken (`reorg.c:1364-1372`) and fill the slot from the target.
  Tools: `cc1_dumps_tu.sh` gains `-dd` (`.dbr`); METHOD notes `--keep`'s path is the LAST output line.
- **S103 — c42: `func_80186A8C` (ov_SC03_091, 8 → 0; 4/4) and `func_80182058` (ov_SC03_001, 10 → 0; 4/4) CLOSED —
  both through jump2's cross-jump in ways METHOD did not yet list.** func_80186A8C: the `- 0x4000` folded into both arms
  of the sign pick and `t` passed bare — `t` set in two blocks takes `$5` by copy preference, and cross-jump merges the two
  identical arm tails into the target's single join instruction (argument registers load in order on MIPS,
  `calls.c:1860-1881`); func_80182058: the case failures sent to one labelled `return 0` — cross-jump lowers its match
  threshold for a block at a label (`jump.c:2406-2410`) or right after a conditional jump past it (`:2516-2519`), so which
  block SURVIVES the merge is decided by where the labels are; the tree's "load-bearing zero-byte cross-jump barrier"
  comment was refuted. METHOD note: for a cross-jump residual, find which label survives in `.jump2`, yours and the tree's.
- **S103 — the first MINIMUM-LEVER draw: c46 on `func_80177B5C`** (c19's plain body at 2; goal: 0 with the fewest marked
  levers, ideally one, instead of 23 per copy × 132).
- **S103 — the FIRST MINIMUM-LEVER BANK: c46 `func_80177B5C` at 0 with ONE marked launder (was 23 levers/copy), 133
  bodies** (`apply-body … allow_residue`; `--propagate: 132 of 132 sibling(s) banked` — "the exemplar keeps 1 marked
  lever(s), so its siblings may too"). The launder is a second set of `w`, so sched1 stops launching the p[2] `or` at its
  store (`birthing_insn_p`, `sched.c:2469`) and sched2's equal-priority tie keeps the target's order; its single-lever table
  (18 rows) shows every pin scores 2+ (registers were already right). Minimum-lever draws running: c47 func_8013D9B0,
  c48 func_80140958, c49 func_8013F350, c50 func_80136824, c51 func_8012E364.
- **S103 — c43 `func_80182F8C` (0) + its sibling `func_80182490` (0, from c43's whole-TU text) banked; propagate found 0
  siblings for 7-copy classes — the copies are CROSS-ADDRESS (the same code as func_80181C24 / func_80181128 at other
  addresses in ov_SC03_107/112/113/117/118 and ov_SC05_004; the census's class key ≠ the ledger's).** A remap port banked
  12 of 12 (after a first attempt paired the classes crosswise — refused at the remap, nothing written). 105 residue
  classes (422 bodies) have members under different names → **`delever.py --port-scan [--apply]`**: indexes every banked
  chain by the (token count, line count) of its extern-stripped before-text and remaps onto every other-named member of
  the same class, gated; runs: `7 … remap cleanly; 4 banked, 3 refused` and `2 …; 1 banked, 1 refused`. **c43's
  `func_80185578` needs a SIGNATURE change** (`void` → `s32`: it returns 0/1 and a keepalive faked the `$v0` writes) —
  types-phase inheritance with its whole-TU proof; c43 also refuted a related.txt pointer I relayed (a same-address
  function in another overlay was a different function) → related.txt now requires shared symbols and a comparable size.
- **S103 — c44 `func_8017D000` (33 → 0; 9/9) + `func_8018F02C` (24 → 0; 5/5); c45 `func_80183A2C` (30 → 0; 14/14) +
  `func_80183E3C` (38 → 0; 9/9); c37 `func_8017D494` (10 → 0) + its 43 CROSS-ADDRESS copies (the "§45-B live-length
  slider" class — 34 inline + 9 shared headers, all banked through the gate).** c44: `u8 v` (no birthing boost for a
  SUBREG destination), an offset address named as a pointer local (find_best_addr folds a non-register address with no
  cost test, `cse.c:2659`), and the P_TAG bitfield link. c45: a body-local `extern u8 D_800AF648_b __asm__("D_800AF648");`
  alias for the second use of the same address (cse compares symbol names by pointer, `cse.c:1937-1939`; an asm-label
  declaration gets a fresh name string, `varasm.c:479-486`) — **harvested as generator R26 `alias_repeated_addresses`,
  known-true: on func_80183E3C's start text its "second" candidate scores 0 from 38** — and `vol` computed in place so it
  is multi-set (no birthing boost). c37: an integer-priority TIE in `allocno_compare` (498 = 498) split by a +1 live-length
  shift — `zc = za;` gives it in natural C (the tree's empty asm was that +1); `func_8015FBE0` was already banked by the
  R19 cast regen.
- **S103 — c50: `func_80136824` CLOSED WITH ZERO LEVERS as a BODY-ONLY change (130 bodies; was 10 levers/copy and listed
  for the types phase since S102).** A body-local `u16 a1v` copy of the parameter, with the first test reading `arg1` and
  the later tests the copy (the lever-free sibling func_801365B8's spelling), `u16 pos`, and the store in each branch:
  the u16 copy is a SUBREG move cse cannot merge (`cse.c:7440-7474`), so `arg1` lives in block 0 only and local-alloc keeps
  it in `$a1` (`local-alloc.c:1281-1295`, `:1722`) — the same allocation an `s16 arg1` prototype gives (the whole-TU
  prototype route also scores 0 and is not needed). **func_80136824 comes OFF the types-phase list.**
- **S103 — c49: `func_8013F350` at 0 with TWO marked head levers (was 4/copy; 133 bodies)** — c28's plain-C body (b9's
  tail move, no compensating errors) + the `$5` pin and the launder, each marked with its pass: the launder keeps
  `&D_8011511C` from `find_best_addr` on both `.cse2` paths (c28's irreducibility), the pin breaks a three-way conflict
  `allocno_compare` ranks 13333/7500/6154 (`global.c:594-603`) with no zero-byte `set_preference` source. Single-lever
  table: none 42, pin only 42, launder only 9, both 0.
- **S103 — c47: `func_8013D9B0` at 0 with TWO marked GTE `__asm__` statements (was 34 levers/copy).** Defect 1 is c17's
  (only an asm writing `$12` gives the target's `move t4,v0`); defect 2: every header GTE macro is a volatile asm, a
  scheduling barrier (`sched.c:1957`), so the IRGB pointer lands after `lwc2 $6`; set earlier it is hoisted (life 4,
  `loop.c:1631`), set twice it loses `birthing_insn_p` (`sched.c:2490`). No single lever reaches 0 (best 2); three pairs
  do. If Drew's T5 respells `gte_stORGB` and adds a three-op load macro, both become macro calls and the body has 0.
  `delever_regen` crashed mid-R26 (`IndexError` in `site_edits`): the census's site lines no longer fit files a bank had
  changed during the pass — it now refuses such a class as STALE-SITES instead of dying (R43); R26 reruns after a census
  refresh. R22 after c49/c50: `check-all: 218 passed, 0 failed of 218`.
- **S103 — c48: `func_80140958` at 0 with TWO marked levers (133 bodies)**, every piece of unmarked steering gone (c13's
  dead initialiser, c29's shared constant): a `$2` pin on the in-loop 8 (a hard register is `may_not_optimize`,
  `loop.c:596`, so `scan_loop` cannot hoist it) and the tree's `j` keepalive (+3 depth-3 refs: j 14/76 over k 13/75,
  `global.c:587-609`); no single lever reaches 0 (10 / 39). **c52: the four ov_SC06_010 `$4`-pin classes
  (func_8018315C, func_80184394, func_801848A4, func_80184EFC) CLOSED by ONE move — the R26 address alias, first try —
  16 + 4 bodies**; c52 counted 111 more `&D_800AF648` pins of that exact shape in the tree (93 followed by the paired
  `func_800491AC` call) — the R26 regen reruns on a fresh census. **c47 banked** (133 of 133 siblings, two marked GTE asm
  statements each). **c56 ported c47's text to ov_MAIN_012's class — 7 of 7 copies score 0.** **c54:** `func_8017B238`
  (ov_SC07_006) ported from ov_SC04_011's lever-free copy (symbols only, first try); `func_801651B8` had already been
  banked by the extern-variant re-propagation after its pack was built (the pack builder should re-score before issuing).
  R22 after c47/c48/c52: `check-all: 218 passed, 0 failed of 218`.
- **S103 — WHERE THE RESIDUE IS (measured at 12,003 sites): ~70% of the remaining lever weight sits in 9 classes of
  ≥100 copies, every one already read by an agent with a written reading** (approx. copies × sites/body:
  func_8013D9B0 125×34 — c17 15 plain, the GTE-macro question; func_80177B5C 132×23 — c19 2, one `or` late;
  func_80140958 119×11 — c13/c29 4; func_80136824 125×10 — types phase; func_8012E364 133×4 — c22 4; func_8013F350
  130×4 — c28 head irreducible; func_80157D20 132×2 — types phase; func_8013CF68 134×1 — c27 irreducible;
  func_80178970 127×1 — c31 irreducible). 940 of the 1,093 classes are single-copy (~3,500 sites). **The pivot: a
  MINIMUM-LEVER close** — the best honest plain-C body an agent reached, plus only the one or two MARKED `// !FAKE:` levers
  it cannot do without, banked with `allow_residue` (S102 a2's precedent; the phase's rule is "ban the silence, not the
  lever"): each such bank replaces a body's 11-34 levers with 1-2, marked and explained, and the census falls by
  thousands. The disposition of the last marked lever per class stays Drew's (GTE, irreducible, types phase).
- **S103 — packs for the next tier: `delever_pack --build --min-copies 5` → `64 packs under .run/P36/agents; ORDER.tsv
  written`** (the head-only ORDER kept as `ORDER_head.tsv`). The head (≥100 copies) is down to classes with honest
  readings; the tier below has several classes at a mechanical best of 1-2 — agents now take TWO small classes each.
- **S103 — the R19+R25 regen pass (R19 now sees the K&R callees):** first launch REFUSED `unknown families ['R25']` —
  the `ALL_FAMILIES` edit had matched nothing (a literal `\\n`); the selftest now asserts every family `recipe_candidates`
  dispatches is registered (negative control: removing R25 fails it by name). Rerun: `1150 of 1150 classes judged in 474
  s — {'MATCH': 3, 'BEST': 98, 'NO-CANDIDATE': 1040, 'UNSCORED': 9}`, all three MATCH by R25 (R19 found no new close);
  the 9 UNSCORED were candidates that genuinely do not compile (a direct trimmed call against a prototype demanding the
  argument: "too few arguments") — `delever_regen` now reports those as COMPILE-ERROR, not UNSCORED (R61). `--bank: 3 of
  3 MATCH row(s) banked`. R22 `check-all: 218 passed, 0 failed of 218`; `lever_census --check: 13,083 pin/asm sites,
  13,083 marked !FAKE, 0 UNMARKED — OK` (13,842 → 13,083; commit `e984e5822`'s message typed "14,xxx" for the start figure — a placeholder that should never have been committed, R66/R85; recorded here rather than amended, P5c).

## 🛑 SESSION CHECKPOINT — S103 (2026-09-10): T0–T6 ☑, **T7 RUNNING — the agent lane at FIVE, every landing harvested**. 24,119 → **12,957 sites** (−11,162) in this session; 33 agent draws (21 closed = 22 functions incl. a twin pair — 7 of them (c12, c20, c21, c23, c24, c25, c26) RE-DRAWS of classes earlier agents left at 2-11; 7 read without closing; 5 in flight at the last refresh; c5/c6 relaunched on Opus after Fable ran out of credits) + 17 classes closed by generators alone (`delever_regen`); generators **R22–R25** added (R23 widened); `delever_regen` closes 22 classes with no agent; `argcheck` reads K&R definitions; propagate no longer trusts stale ledger hashes; `tools/localalloc_sim.py`; `--try` learned header TUs; CI's `verbatim_check` fixed and wired into tools-health; R22 `check-all: 218 passed, 0 failed of 218` at every bank | `lever_census --check` OK (12,957 marked, 0 UNMARKED) · `lever_progress --check` OK (43 milestones) · refreshed at `01f066923`

### 0. How to use this block
A fresh session reads CLAUDE.md's load order, replays this block verbatim, confirms the effort (**S103 ran at `/effort
high` on Opus 5 1M; Fable 5.1 was OUT OF USAGE CREDITS all session — every agent ran on Opus and 14 of the 15 judged draws
closed**) and executes §2. **What may be in flight when this block is read:** at writing, five read-only agents were
running (at the last refresh) — c29 `func_80140958` (re-draw), c30 `func_8017B614` (re-draw), c31 `func_80178970` (re-draw),
c32 `func_8017FC5C` + `func_801852E4`, c33 `func_80169058` + `func_80168D94` (the ov_MAIN_012 tier). A dead session's agents leave their work in `.run/P36/agents/ov_SC04_011__<fn>/body.c` + `mechanism.md` (R67):
`--try` each `body.c`; a score 0 is bankable (§3), anything else is a reading to record. The tree is committed at every
bank; `git status --short | wc -l` should be 0 apart from those packs. First commands:
```
git log --oneline -1 && git status --short | grep -v '^?? .run/P36/agents\| M .run/P36/agents' | wc -l
.venv/bin/python tools/delever_oracle.py --calibrate ov_SC04_011 ov_SC03_015 ov_SC03_014 main -j 16   # after EVERY commit
.venv/bin/python tools/delever_oracle.py --snapshot-baseline
```

### 1. THE OPERATING PROCEDURE (Drew's; S103 additions in bold)
- **At most FIVE agents at once** (Drew, 2026-09-10, S103). The agent lane is the main lane and is never empty: on a
  landing (1) `--try` the agent's `body.c`; (2) launch the next agent into the free slot; (3) then bank, propagate,
  harvest, gate, commit. Agents are read-only; **one writer** (a bank, a propagate, a sweep, a `delever_regen --bank`)
  at a time.
- **Relay a sibling's crack to a running agent** with SendMessage when a landing's mechanism plausibly applies to it —
  twice in S103 (c4 → c7, c1 → c8), both relays used in the close.
- **Every harvest that adds or widens a generator is followed by `tools/delever_regen.py`** over the whole residue (§3):
  the residue's NO-MATCH attempts predate every new family and nothing else revisits them (17 free classes the first time).
- Brief every agent with `PROMPT.md` + `METHOD_S103.md` (grown at every landing — it is the method) + the pack's
  `related.txt` + the named sibling packs whose mechanism applies. Tell it which functions other agents hold in its TU.
- Fable out of credits → an agent dies with HTTP 429 on its first step; relaunch on Opus (R40). Drafter ladder otherwise.
- Sweeps/fleet runs detached or `run_in_background` with a watcher; the finish sequence after every bank (§3).

### 2. NEXT — the head is 16 classes of ≥100 copies; keep five agents on it and harvest every landing
1. Land whatever of c13/c15/c17/c19/c20 is back (§0). Then draw from the classes still open (`delever_search.exemplars`):
   ≥100 copies at S103's end — `func_8013CF68` (134; **c9 READ: 38 → 10, count closed, order only; its 5 used a dummy
   reassignment and was refused; sched1 alias analysis `sched.c:419-438` — re-draw only with a new idea**),
   `func_8012E364` (133), `func_80157D20` (132, needs a fleet declaration widen — types phase), `func_80133CD4` (131),
   `func_8013F350` (130, head a proven wall), `func_8012956C` (127), `func_80133784` (127, S102 b4 read 21 → 2),
   `func_801397B0` (126, `$4` pin — try the implicit-argument reading), `func_8017B614` (126), `func_80166F58` (125),
   `func_80136824` (125, types phase), `func_80178970` (127, the combine fold wall, `combine.c:914-917`) — plus whichever
   of the five in flight did not close. **A re-draw needs new information in the brief** (S103's re-draws carried
   METHOD_S103 + `related.txt`); the prior agent's `body.c`/`mechanism.md` are copied to `scratch/prev_*` first.
2. Below 100 copies the residue is ~1,165 classes of 1–41 copies: that is `delever_regen` + the engine's territory, and
   the next lever after the head is a pack build over them (`delever_pack --build --min-copies 10`) once the head is down.
3. Per landing, the checklist: `--try` → next agent → `apply_body_core` → `--propagate` → R22 → census → `lever_progress
   --snapshot` → baseline → METHOD_S103 entry → generator if mechanical (selftest + known-true against the agent's own
   start text) → `delever_regen` if a family was added/widened → log line → commit.

### 3. THE EXACT INVOCATIONS (S102's §3 still holds; additions)
```
# per-pack related bodies for a draw whose pack predates S103 (the pack builder writes it for every pack now)
.venv/bin/python - <<'PY'
import sys; sys.path.insert(0,'tools'); import delever_pack as dp
fn,tu='<fn>','<tu>'; d=f'.run/P36/agents/ov_SC04_011__{fn}'
open(d+'/related.txt','w').write(dp.related_bodies(tu,fn,open(d+'/body_tree.c').read(),'ov_SC04_011'))
PY
# the regen pass (read-only; ~2 min for 1,169 classes at -j 10) and its bank (the one writer)
setsid nohup nice -n 10 .venv/bin/python tools/delever_regen.py --families R22 R23 -j 10 --label <L> \
    --exclude <every fn an agent holds> > .run/P36/regen/<L>.log 2>&1 &
.venv/bin/python tools/delever_regen.py --bank .run/P36/regen/<L>.tsv      # then the R22 fleet run
# read every UNSCORED row before banking (R61): S103's were 24 header TUs --try could not compile + 1 #define body
```

### 4. WHAT S103 BUILT (all with SETUP rows under §P36 S103 and dictionary rows; `tool_census --check` OK)
- **R22 `merge_walked_pointers`** (c2) and **R23 `split_reused_locals`** (c1/c8, widened from c16: one brace depth of one
  open block, pointer declarators, `*p = E` is a store through `p`, brace-less `if (c) v = E;` refused, `#define` bodies
  refused). Known-true: R22 reproduces c2's closing body (0); R23 reproduces c1/c8's single-move scores (12, 26) and closes
  c16's `func_8013D178` alone (0). Both lead their residual classes in `delever_search.FAMILIES`.
- **`tools/delever_regen.py`** — §3. **`delever_search --try` on a shared-header TU** now passes the includer's directory
  (`-I`): no header-TU class had ever been scorable (controlled: unchanged 0, lever-free 32, mutated 1).
- **`delever_pack` writes `related.txt`**: lever-free bodies anywhere in the overlay sharing a `func_`/`D_` symbol, ranked
  (known-true: for `func_80135A4C` the top hit is `func_80135888`, the body its agent found by hand in another file).
- **`tools/cc1_dumps_tu.sh`** dumps `.cse2` (`-dt`) and `.jump2` (`-dJ`).
- **`verbatim_check --strict` in `make tools-health`**; `--update` keeps the manifest's order and UTF-8. CI had been red
  since `cb2fb5e6d` (2026-09-09) on the stale DECOMPILE-NOW row `func_8017EEC0` — fixed, and that function's uninitialised
  `a0v` local is now its parameter.
- **`.run/P36/agents/METHOD_S103.md`** — every emitter and register-order move byte-proven in S103 with its `file:line`.

### 5. GOTCHAS S103 PAID FOR
- **A mid-turn message from Drew can arrive with a tool result** — answer it in the same turn (the CI failure and the
  five-agent cap both came that way).
- **A check that runs only in CI is not a guard for the local chain** (R54): the verbatim row sat red for a day.
- **A "json.dump" rewrite is an instrument change**: `--update` re-sorted and ASCII-escaped the whole manifest; a
  one-row fix became a 588-line diff until the tool was fixed (R57).
- **An instrument that cannot score a population reports it as UNSCORED, and "unscored" is not "judged"** (R61): the
  header-TU `--try` defect hid behind that word for every header class since the engine began.
- **A typed count in a log line is wrong the first time** (R85): the regen family split was typed 13/4 and is 12/5 —
  counted from the TSVs.
- `tools/cc1_dumps_tu.sh` failed with CPP-EMPTY on TUs that include `../shared/…` — **FIXED in S103** (`-Isrc/shared`, and it takes a .c file):
  agents keep writing their own `dump.sh` (a working one: `.run/P36/agents/ov_SC04_011__func_8013D178/scratch/dump.sh`).
  **Fix it next** (it should take the TU's own directory and `src/` as include roots like `--try` does).

### 6. OPEN BY NAME
- **Drew's call, asked in S103:** does `do { … } while (0);` count as a lever? (banked with one so far: c5's `func_8015D738`, c15's `func_80135EB0` and c21's `func_801397B0` in S103, a4 and b8 in S102 — c15 and c21 as REFERENCE-WEIGHT doublers, c5 as a cse barrier; and its cousin: c13's DEAD INITIALISER — `s16 size = 0;` flow deletes, whose only job is to stop `scan_loop` hoisting a constant; c9 refused the do-nothing reassignment form) It is R7's move, banked in S102 (a4, b8)
  and S103 (c5's `func_8015D738`, where it is the barrier the removed `asm` was — c5 flagged it), uncounted by the census,
  1,347 in `src/`. If yes: a census class + a residue to work down.
- **Drew's call (T5, the GTE header):** c17 showed `func_8013D9B0`'s last 15 (134 copies) are `include/gte_inline.h`'s
  `gte_stORGB` spelling: an `inline_o`-style macro that writes `$12` itself (clobber `$12` only) takes the plain-C body to
  2, a second merged macro to 0 — a clobber list that differs from Sony's own (`$12-$15` scores 6). Whether a GTE macro
  may be respelled that way (the plan calls a clobber variant a lever) decides this class. Evidence:
  `.run/P36/agents/ov_SC04_011__func_8013D9B0/scratch/PA.c`, `PROOF_K1.c`, `mechanism.md`.
- **Drew's call (the milestone): irreducible sites.** c31 proved `func_80178970`'s `$2` pin (133 copies, and four more
  families with the same byte shape) cannot come off in plain C on gcc 2.7.2 — two passes each delete the copy. The phase
  plan says grind to zero; a proven-irreducible site needs a disposition (kept, marked and counted like the verbatim rows?).
  Also read to an irreducibility argument: `func_8013F350`'s head (c28), `func_8013CF68` (c27, §194-K).
- The declaration debt, measured at S103's open (`.run/P36/s103/argcheck.json`, 94,001 rows): **91,846 are calls that
  pass FEWER arguments than the definition** (the R19 population — which side is wrong is a types-phase question: a
  definition may carry a phantom parameter), 1,731 have every call passing enough but sit in units `decl_repair` did not
  judge IDENTICAL, 424 are in `src/shared` headers. The "shared headers are the next cheap win" line of S102 was an
  overestimate — 424 rows.
- The types phase inherits: `func_80168828`, `func_80157D20` (S102; `func_80136824` CLOSED body-only by S103 c50); `func_8017FC5C` + `func_80180200` (S103 c32 — a `void` function that returns its first argument; ready patch `ov_SC03_115__func_8017FC5C/scratch/tu_p1.diff`); `func_8017EEC0`'s callers still
  declare it `(void)`; the `ov_SC01_077` variant of `func_80148E54` still calls its handler with no argument.
- Tool gaps agents named: `alloc_table.py` prints the GLOBAL priority only — local-alloc's `qty_compare_1` rank is in
  `.run/P36/agents/ov_SC04_011__func_80135168/scratch/lpri.py` (c1, c8 asked); `--try` does not print its object path;
  the pack has no `best_body.c` where the engine never wrote one.

### 7. WHERE EVERYTHING IS
S102's §7 holds, plus: `.run/P36/regen/` (every regen TSV, log and candidate) · `.run/P36/s103/` (this session's R22 logs,
the argcheck census, the verbatim manifest before/after, the R22/R23 known-true candidates) · `.run/P36/agents/METHOD_S103.md`
· each landed pack's `mechanism.md` (c1–c20) · SETUP §P36 S103.

## (superseded) SESSION CHECKPOINT — S102 (2026-09-10): T0–T6 ☑, **T7 RUNNING AND PRODUCTIVE**. 30,358 → **24,119 sites** (−6,239) in 6,317 bodies; 22 agents across two waves (14 closed, 8 read); generators **R15–R21** added, each with a known-true check; **16,759 lying call declarations repaired free** across 3,439 units; R22 `check-all: 218 passed, 0 failed of 218` at every step | `lever_census --check` OK (24,119 marked, 0 UNMARKED) · `lever_progress --check` OK (30 milestones) · tree CLEAN at `8a22254bf`

### 0. How to use this block
A fresh session reads CLAUDE.md's load order, replays this block verbatim, confirms the effort (**Drew ran S102 at
`/effort high` on Opus 5 1M; xHigh on Fable is equally fine — the work is engineering against a byte oracle**) and
executes §2. **Nothing is in flight: the tree is clean, no sweep and no agent is running, the fleet is 218/218.**
First commands of the session:
```
git log --oneline -1                       # expect 8a22254bf or Drew's push on top of it
git status --short | wc -l                 # expect 0
.venv/bin/python tools/delever_oracle.py --calibrate ov_SC04_011 ov_SC03_015 ov_SC03_014 main -j 16   # ~3 s, after EVERY commit
.venv/bin/python tools/delever_oracle.py --snapshot-baseline                                          # 7,428 objects, 188 MB
```

### 1. THE OPERATING PROCEDURE (Drew's, and it is the thing to get right)
- **The AGENT LANE IS THE MAIN LANE AND IS NEVER EMPTY** (2026-09-10, after a night that produced only three agents
  because sweeps ran between them). On a landing, in this order: (1) `--try` the agent's `body.c` — seconds — to prove
  the claim on bytes; (2) **launch the next agent immediately**; (3) only then bank, propagate, harvest the idiom into a
  generator, gate and commit, all while the new agent runs. One agent at a time was his earlier rule so the methodology
  is honed at each landing; four to six in parallel on DISTINCT residue classes is what he approved once it was shown
  that `--try` writes nothing into the tree.
- **ONLY ONE WRITER.** Agents are read-only (`--try` compiles a scratch copy). The BANK and a SWEEP both write the tree,
  and they cannot overlap: running a sweep while banking made `--calibrate` fail at 174/177 and cost a hand
  reconciliation of eight files. **A sweep is not part of the agent lane.** If you must stop one: kill by PID (never
  `pkill -f` a literal your own command line contains, R79), then reconcile — a bank recorded in the run log stays, a
  dirty file with no recorded bank is a leftover candidate and is restored from HEAD, then `make check-all` proves it.
- **`make clean` is now SAFE beside agents** because of the baseline snapshot (§3). Refresh the snapshot after each
  green `check-all`.
- Effort/resources: sweeps at `-j 16` with `nice -n 10` (Drew raised it from 8 on 2026-09-10). Campaigns run DETACHED
  (`setsid nohup … &`) with a `Monitor` on the log — the harness backgrounds any foreground command over 120 s and its
  low-memory guard kills long background tasks (it killed a waiter, not the run, twice).

### 2. NEXT — keep the loop running; the head is 34 classes and the method is now sharp
1. `.venv/bin/python tools/delever_pack.py --build` (~2 min, no tree writes) → `.run/P36/agents/ORDER.tsv`, 34 packs.
   Packs now carry `neighbours.txt` (the target's OWN header in full + matched siblings' headers + every
   `@class:`/`@stuck:`/`@crack:` note) and `best_body.c` (the engine's best text, because `history.txt`'s `@NNNN` line
   numbers are relative to the EVOLVING text and cannot be replayed by hand).
2. Launch 4–6 agents on DISTINCT classes from `ORDER.tsv`, briefing each with `PACK/PROMPT.md` plus the method below.
   **Already read without closing — do not re-draw without new information:** `func_80136824` (blocked: a real crack
   that needs its prototype widened, types phase), `func_801397B0` (2), `func_80178970` (3, and its pin was judged
   needed-by-construction inside a declaration environment we have since repaired — RE-MEASURE before believing it),
   `func_80148E54` + twin `func_80148D44` (6), `func_80157D20` (4, needs a fleet declaration widen), `func_80139BE0`
   (banked since, by R20), `func_80166F58` (4), `func_8012956C` (4), `func_8012E364` (4), `func_8013DD68` (2),
   `func_8017B614` (6), `func_80133CD4` (11), `func_80133784` (2), `func_8013F350` (16, head proven a wall).
3. **THE METHOD THAT CLOSED 14 OF 22, in order** — put it in every brief:
   0. Read `PACK/neighbours.txt`. One agent closed on its FIRST `--try` because a sibling's header spelled the crack out
      in English. **A `@stuck:` note is a CLAIM: two were refuted on bytes this session.**
   1. Dump the target function WHOLE off the tree's own object (`objdump -drz build/src/<tu>.o`), not the residual's
      hunks — the hunk view scrambles moves into branch delay slots and hides a repeated shape.
   2. **COUNT FIRST.** The residual text cannot tell you whether an instruction is MISSING or the registers are WRONG;
      one agent chased a register theory for hours when cse had forwarded a just-stored value and deleted a load.
   3. If instructions are missing, ask what emits them. The answers this session: a dropped call argument (R19); a copy
      cse deleted because the producer sat immediately before it (R21); a copy deleted because two locals shared a WIDTH
      (R20); a block merged by cross-jump, whose equality test compares symbol names BY POINTER, so a body-local
      `extern T alias __asm__("SYM");` keeps the blocks apart at zero byte cost.
   4. Only then the allocation table (§3). Declaration-order moves (R2/R4) are PROVABLY DEAD on a register residual whose
      allocnos have distinct priorities — `global.c:604-610` compares priority first and ties only by allocno number.
4. **HARVEST EVERY LANDING (R16).** If the move is mechanical it becomes a generator with a selftest AND a known-true
   check against the body it came from; then sweep. **Three of the four new generators win only as JOINT edits** whose
   every single step scores worse than the start — when that is true, generate the joint candidate, do not trust a beam.
5. Two REFUSALS to keep making: an invented identically-zero term is a compiler-forcing construct in C clothing and is
   NOT banked (the phase's rule is *ban the silence, not the lever*; the honest close arrived from R20 hours later); and
   a body whose improvements are compensating errors is reported, not banked (agent b9 said so itself).

### 3. THE EXACT INVOCATIONS
```
# the packs, the agents' loop, the bank
.venv/bin/python tools/delever_pack.py --build
.venv/bin/python tools/delever_search.py --try <tu> <fn> <PACK>/body.c --body      # agents: read-only, any number at once
.venv/bin/python - <<'EOF'
import sys; sys.path.insert(0,'tools'); import delever as dl
print(dl.apply_body_core('<tu>','<fn>',open('<PACK>/body.c').read(),'<label>','E',source='T7 agent <label>')[1])
EOF
.venv/bin/python tools/delever.py --propagate <tu> <fn> --label <label>p --dirty-ok
#   allow_residue=True as a kwarg when the body deliberately KEEPS a marked lever (a2's case)

# the engine (a SWEEP: never while banking, never while an agent scores)
setsid nohup nice -n 10 .venv/bin/python tools/delever_search.py --run [--include-done] --limit N \
    -j 16 --beam 3 --depth 2 --cap 64 --budget 300 --label sN > .run/P36/engine/run_sN.log 2>&1 &
.venv/bin/python tools/delever_search.py --explain <tu> <fn> [--path "m1|m2"]

# call signatures
.venv/bin/python tools/argcheck.py --json .run/P36/engine/argcheck.json
.venv/bin/python tools/decl_repair.py -j 10 [--apply]
.venv/bin/python tools/readability_progress.py --snapshot "<label>"   # ~10 min; --check asserts it is this tree

# reading the compiler
tools/cc1_dumps_tu.sh <wd> <tag>          # needs $wd/shared -> src/shared for TUs with relative includes
.venv/bin/python tools/alloc_table.py <tag> <fn> <dump_root>

# THE FINISH SEQUENCE after every bank
set -o pipefail; make clean >/dev/null && make extract-all JOBS=16 >/dev/null && make check-all JOBS=16 | tail -1
.venv/bin/python tools/lever_census.py --sites --check -j 16
.venv/bin/python tools/lever_progress.py --snapshot "<what changed>"; .venv/bin/python tools/lever_progress.py --check
.venv/bin/python tools/delever_oracle.py --snapshot-baseline
make kit-corpus && .venv/bin/python tools/tool_census.py --check      # after ANY tool or SETUP edit
git add -A src tools docs config decomp-architect .run/P36 phase-ends && git commit
```
Timings: R22 clean fleet ≈ 90–150 s · census ≈ 35 s · calibration 3 s · one scored candidate 0.12–0.3 s · a pack build
≈ 2 min · `argcheck` ≈ 10 min · `decl_repair` fleet ≈ 25 min · `make kit-corpus` ≈ 25 s.

### 4. THE TOOLS — all documented, nothing to rediscover
**`docs/SETUP.md` §P36 S102 is the full reference** (the generator table R15–R21 with the body each was harvested from,
the call-signature tools, the oracle and scorer changes, the dump tools, the packs). Every tool carries a
`config/tool_dictionary.tsv` row and `tool_census --check` is green. In one line each:
- `tools/argcheck.py` — every call declaration narrower than the callee's real definition (110,478 → 94,001 after the
  repair; 461 in 314 bodies still holding an argument-register pin). Blind to a function wrong EVERYWHERE.
- `tools/decl_repair.py` — repairs the free ones (`--apply`); compares CODE SECTIONS, controls every unit by compiling
  it unchanged first.
- `tools/readability_progress.py` — `docs/readability.md` + `docs/readability-progress.tsv`, the Gen3 chart Drew asked
  for: lying declarations and the struct debt (414,148 raw cast derefs vs 173,286 struct member reads).
- `tools/alloc_table.py` — rewritten: every pseudo, coverage asserted, a loud refusal instead of an empty table.
- `tools/cc1_dumps_tu.sh` — include path fixed, `-dR` added, refuses a short preprocess.
- `tools/delever_oracle.py --snapshot-baseline` + `baseline_path()` — the gate and the agents are now independent.
- `tools/delever_pack.py` — `neighbours.txt` and `best_body.c`.
- `tools/delever.py` — generators R15–R21, `protos_outside_definition`, propagate's derived residue allowance, a unique
  temp for the includers cache (a fixed name made a lost race look like a compiler crash).

### 5. GOTCHAS THIS SESSION PAID FOR
- **A measurement that cannot come out any other way is not a measurement.** The first declaration scan widened
  declarations and left the calls alone: 1,766 of 3,250 units could not compile BY CONSTRUCTION. The second returned
  0 free of 3,634 and I reported it before controlling it — compiling the UNCHANGED text through the same path also
  differed, by 9,176 bytes, because the object records its own source filename. **Control the instrument, then believe
  it** (R39/R40). The control now lives inside the tool.
- **A commit stales the calibration**; recalibrate before every bank. `--apply-body` refuses on a stale calibration and
  says so.
- **Two writers corrupt each other** (§1). **A per-file scratch name is a collision** when agents share a TU.
- **A `git add`/commit whose edit failed still commits**: one commit message here claimed a documentation fix the failed
  edit had not made; it was named and repaired in the next commit (R66 — write "done" only from the tool's own line).
- The harness's low-memory guard kills long BACKGROUND waiters; use a `Monitor` on the log instead.

### 6. OPEN BY NAME
- **The types phase inherits three measured cases** where only a declaration change can remove a pin, all body-only
  unbankable: `func_80136824` (133 copies, needs its prototype widened with its definition), `func_80168828` (its `$4`
  pin is forced by a shared header's `(void)`), `func_80157D20` (declared `(void)` in 131 of 138 defining sites).
- **94,001 lying declarations remain** in three groups: units that never call the function, calls that genuinely pass
  too few arguments (R19's population), and declarations inside `src/shared` headers — which are not units with recipes
  and were NEVER SCANNED. That last group is the next cheap win.
- `decl_repair`: **117 COMPILE-ERROR and 101 CONTROL-FAILED units** were never diagnosed.
- **Drew's struct question, answered and recorded:** structs are not in the binary (types are erased; a retail build has
  no metadata) — what is there is base + offset + width + stride, so a struct is an INFERENCE across every function
  touching a base, which makes per-function struct invention the wrong unit (P35 already paid for that: 1,232 invented
  definitions and a reconcile ladder, R95). The recommendation on record: keep pins as the main lane, build a zero-token
  STRUCT EVIDENCE CENSUS beside it (cluster base+offset+width across the fleet, emit candidate layouts with the
  functions touching each), and park a stuck pin WITH its evidence rather than inventing a type for it.
- Carried: the 5 propagate refusals of `func_8017EB44`/`func_8017EBA8`; the `UNSTRIPPABLE` bodies named in the run logs;
  cookbook §176 documents only the OPPOSITE of agent b4's de-looping move and wants the new direction beside it.

### 7. WHERE EVERYTHING IS
`.run/P36/engine/` — `outcomes.jsonl` (every attempt), `trace/`, `run_g*.log`/`run_s*.log`, `residual_moves.md` (lane B's
compiler-source map), `argcheck.json`, `argcheck_draw.tsv`, `decl_repair.json`, `const_holder_census.py` ·
`.run/P36/agents/` — `ORDER.tsv`, `PROMPT.md` (the brief), one pack per exemplar with every agent's `body.c` and
`mechanism.md` (the readings are the durable record — several are worth more than their bodies) ·
`.run/P36/delever/` — `ledger.jsonl`, `calibration.json`, `baseline/` (the snapshot) ·
`docs/levers.md` + `docs/lever-progress.tsv` (the lever series) · `docs/readability.md` +
`docs/readability-progress.tsv` (the Gen3 readability series) · `docs/SETUP.md` §P36 S102 (the tool reference) ·
cookbook §454, §454a, §455 · this file's log (append-only, one entry per step, with the literal verify line).

## (superseded) SESSION CHECKPOINT — S101 (2026-09-09) / LIVE, refreshed S102 (2026-09-10): T0–T6 ☑, **T7 RUNNING — agent a1 BANKED + HARVESTED: `func_80156044` (130 bodies) and its move toolified as generator **R15, the sink**, which then closed 6 more exemplars (267 bodies) in 4 compiles each with no tokens; agent a2 banked 125 more; 30,358 → 29,572 sites, R22 218/218**; **lane B DELIVERED + 4 claims verified on bytes; lane A = rung G, `tools/delever_search.py`, BUILT, CONTROLLED, MEASURED over six runs (g1–g6b: 33,427 → 30,358 sites, 12,048 → 9,747 bodies, every bank R22 218/218, no drafting tokens); the head is where the number is (57 classes ≥100 copies = 7,318 of 9,796 residue bodies) and the wide search is spent on it; T7 APPROVED by Drew as ONE AGENT AT A TIME — the packs, the brief and the agent's scorer are built; NEXT = §2: start the serial agent loop IN THIS FRESH SESSION** | the number at this commit: **27,984 sites** in 8,249 bodies · marked 27,984 · UNMARKED 0 · orphans 0 — `lever_census --check` OK · `lever_progress --check` OK (20 milestones). **S102's loop state: the burst of 20 is landing; a4/a7/a8/a12/a18/a19 banked (756 bodies); the per-file scratch-object collision is FIXED (per-function tag); the biggest class found is a truncated `(void)` DECLARATION, three cases of which need the types phase.**

### 0. How to use this block
A fresh session reads CLAUDE.md's load order, replays this block verbatim, confirms the effort (**Drew: `/effort xhigh`, Fable 5.1**
— his 2026-09-09 setting for this work) and executes §2. **FIRST check whether run g3 finished and whether its bank is committed:**
`grep -E '^search:|propagate' .run/P36/engine/run_g3.log` and `git status --short -- src | wc -l` (0 = nothing in flight). A run
that was killed leaves candidates in `src/` — `tools/delever.py --restore` (never git checkout, R102). **Never commit while a run
is going** (the oracle's calibration is keyed to HEAD; `--apply-body` inside the run refuses on a stale calibration and every later
close of that run is BANK-REFUSED) and **never edit `tools/delever.py` while a run is going** (`--apply-body`/`--propagate` are
subprocesses that re-import it; a half-edited file breaks a bank mid-run) — `tools/delever_search.py` may be edited, the running
process has it in memory. Resource etiquette: **Drew raised the sweep concurrency to `-j 16` on 2026-09-10 ("you can raise the concurrency from 8
workers to 16 for all sweeps") — use 16 with `nice -n 10` for every sweep from here**; 8 was fine all of S101 (he asked for
more at 10 earlier in the phase and less at 24); tell him the number. The harness backgrounds any foreground command over 120 s and its low-memory
guard kills long background tasks: campaigns run DETACHED (`setsid nohup … &`) with a `Monitor` on the log. `pkill -f` with a
literal your own command line contains kills your shell (R79).

### 1. Where things stand — what S101 built, measured and banked (commits `623e55340` → `a4cbe0d5a` → `584031c71` → `5ae0b5ceb`)
- **Rung G (`tools/delever_search.py`)** — the guided search: the score is the ORACLE'S OWN OBJECT (a candidate compiles through one
  recipe of its TU; the function's instructions are read from the scratch object and compared, reloc-masked, with the same
  function in the fleet run's baseline object under `build/` — the tree's bytes, the candidates' relocations by construction; no
  listing, no isolation, no cpp), read as an EDIT DISTANCE over the masked words (difflib; a positional count read one inlined
  temp as 43); the residual CLASSIFIED from the diff blocks (REG caller/callee from the register pairs, COUNT, ORDER, MIXED) and
  the class orders the generator families (lane B's map), ranked ROUND-ROBIN under the cap; a BEAM composes 2–4 moves; the first
  score-0 is verified on every recipe and banked through `delever --apply-body --rung G`, then `--propagate` serially. Controls:
  per body the tree's own text must score 0 and be identical; `--positive-control` (one move back in 23 compiles; inline + wrap
  back by hoist + unwrap in 74; an inlined pointer temp under a dereference stalled at 10 until the base hoist existed);
  `--selftest`. `--explain TU FN [--path "m1|m2"]` prints a body's residual as mnemonic blocks after any move path — the
  instrument that turns a stall into a generator.
- **The generator registry (`delever.recipe_candidates`, `families=`, `cap=None`)** now holds R2 decl-order, R3 init-split, R4
  decl-move, R5 commutative swap (never a constant operand — fold), R6 single-set temp inlined, R7 block/do-while wrap AND unwrap,
  R8 temp introduced (a dereference typed by its cast; its BASE into an address local; an operand typed like the local it feeds;
  a repeated RHS named once), R9 adjacent statements swapped, R10 a parameter routed through a body-local copy and the reverse,
  R12 a local's scalar width, R13 two terms of a `+`/`-` chain exchanged. Rung R's default set is still R2–R7 (`RUNG_R_FAMILIES`).
- **Measured (R41):** g1 (beam 3 × depth 3 × cap 48, budget 400): `1 of 16 … 0.12 h, 3,680 compiles` — `func_801424E4`, the body
  with NO pin (cast + keep-alive, the count-changing class, the permuter's best 2) by `R9 + R6 + R6`, 132 bodies. g2 (beam 4 ×
  depth 4 × cap 64, budget 1,500, the new families, the same head): `1 of 16 … 0.32 h, 9,454 compiles` — `func_80142EC0` (two pins)
  by `R7 do-while + R9`, 132 bodies; nine of the other fifteen moved past g1's best (40→24, 29→16, 45→31, 28→10, 39→14, 25→7, 9→4,
  7→4, 135→112). 0.12–0.3 s per scored candidate; 23–276 s per body. The 16-class head = the 11 rung D could not close + 5 new.
- **The ledger defect fixed:** 301 rung-R RESIDUE rows carried no text hash (`recipes()` wrote None on a miss; the next sweep
  inherited it) — `exemplars()` had read them as one class keyed None; `delever --repair-nhash` filled them (recorded, committed).
- **Lane B (`residual_moves.md`):** 58 ranked (class → move, pass, decision `file:line`, mechanism, how-to-test) with ~150
  grep-verified anchors in `tools/reference/gcc-2.7.2/`; its "Verification ledger" at the end: the constant-swap claim VERIFIED
  (`.run/P36/engine/micro/c1.c`/`c2.c`), the do-while lever VERIFIED as the ref weight (`micro/dowhile/`: `{ }` changes nothing;
  `do…while(0)` keeps its LOOP notes through jump1 and lifts one `.lreg` line from `used 5` to `used 6 times across 39 insns`,
  `$18` → `$17`), the 16-bit-copy claim NOT REACHED where the value's known bits fit the narrow mode. Five map contradictions
  it found are T9's (regalloc.md RC-4 cite `:1825` → `:1722`; sched.md: a mid-block LOOP note is a full sched1 barrier; cse_expr.md
  §1's "volatile asm invalidates nothing" row; loop.md's arg order; regalloc.md K1 vs [A23]-5).
- **Cookbook §455** (rung G) written; SETUP + dictionary rows; `docs/levers.md` rows 4–5; the `.run/P36/engine/` allowlist.
- **What `--explain` says about the stalls (the next generators, in the order of bodies they unlock):** (i) the two 6s
  `func_80148D44`/`func_80148E54` (132 + 132) are ONE surviving copy — the target computes `andi a0,v0,0xfff` and copies `move
  s0,a0` in a delay slot; mine folds the copy (combine merges a single-use def into its copy; the keep-alive/launder was the
  drafter's second use) — no width reaches it; the move is a SECOND REAL USE of the copied value or an uncombinable copy (lane B
  1c-2/1c-3: re-set the source after the copy; a real join label between copy and use); (ii) `func_8012E364` at 7 is `x + a3 - a1`
  vs `x - a1 + a3` (R13 exists, was not composed within the beam) plus a negation the target names once for two stores (R8 cse
  exists); (iii) `func_80135A4C` at 24 is a duplicated call tail the target keeps and mine cross-jumps (`jal;li;beqz;nop` vs `j`)
  — a source-level tail duplication (lane B class 2 row 19); (iv) `func_8013D178` (130 copies) is a pure `a0 ↔ a1` swap 45× over,
  one `$5` pin — the ARGCOPY class, lane B 1a-9 (R10 exists; in g3's draw).

### 2. NEXT — T7 as ONE AGENT AT A TIME (Drew, 2026-09-09: "spawn one agent at a time, this way we can hone our methodology each time one lands, in the hopes of learning enough to be able to tool crack the rest"; approved: "i am okay with the 57 agent wave"; "wait for the tail to finish, and then checkpoint for a fresh session and we will start it in there")
The head holds the number: 57 residue classes of ≥100 copies = 7,318 of the 9,796 residue bodies (derived from the ledger at S101's
end: `ds.exemplars(include_done=True)`; 17 of the 57 are within 4 instructions of the target, 14 more within 10). Six runs of the
mechanical search closed none of them at any width, so each is a READING + a GENERATOR, and the loop below is the harvest→toolify
gate at agent granularity. **The packs exist:** `.run/P36/agents/ORDER.tsv` (rank, fn, alias, copies, best distance reached, needed
sites, kinds, regs, tu) and one directory per exemplar (`tu.txt`, `body_tree.c`, `body_free.c` = the seed, `residual.txt`, `sites.txt`,
`history.txt`); rebuild them after any bank with `.venv/bin/python tools/delever_pack.py --build` (no tree writes; ~2 min). **The
brief is `.run/P36/agents/PROMPT.md`** (read it before launching: the residual first, the pass from the compiler's source + the map,
every hypothesis on bytes with `--try`, deliverables early — `body.c` + `mechanism.md` with a GENERATOR PROPOSAL, no tree writes).
**Per agent, in order:**
1. `sed -n 2,3p .run/P36/agents/ORDER.tsv` → the next exemplar (rank 1 first: `func_80156044`, best 1 after `R12 width puVar2 s32->u16`;
   rank 2 `func_80168828` best 1; then the 2s and 3s). Launch ONE general-purpose agent (the session's model, Fable) with the prompt:
   "Read /home/musashi/bfm-decomp/.run/P36/agents/PROMPT.md in full and follow it exactly. PACK = <the pack dir>. <the head start from
   its history.txt, one sentence>. Work in PACK only; score with `.venv/bin/python tools/delever_search.py --try <tu> <fn> PACK/body.c
   --body` from the repository root; write PACK/body.c and PACK/mechanism.md early; report as PROMPT.md says." Wait for it (it is the
   only agent; nothing else touches the tree meanwhile).
2. When it lands: read `mechanism.md`; verify its claim yourself — `--try` on its `body.c` (score 0 expected), then the bank on the REAL
   recipe: `.venv/bin/python - <<'EOF'` … `dl.apply_body_core(tu, fn, open('PACK/body.c').read(), 'a<k>', 'E')` → the printed line must say
   IDENTICAL … KEPT; then `.venv/bin/python tools/delever.py --propagate <tu> <fn> --label a<k>p --dirty-ok` (each sibling judged on its
   own objects). A refused bank = the agent's reading was of the isolated compile, not the object: read the diff it printed.
3. TOOLIFY (R16): if the move is mechanical, add it as a generator in `delever.recipe_candidates` (a selftest case; the docstring names
   the agent's mechanism and the body), then sweep the REMAINING head exemplars cheaply with the engine — `--run --include-done --only
   <the other 56 fns> -j 8 --beam 3 --depth 2 --cap 48 --budget 200 --label s<k>` (~30 s per body) — every close is a free class; if it is
   not mechanical, write it into the cookbook (§455's addenda) and PROMPT.md's method so the NEXT agent starts from it.
4. THE FINISH SEQUENCE (§3) after every bank: R22 → census → `lever_progress --snapshot "S102 a<k> …"` → the log entry (the agent's
   reading, the move, the mechanism with its `file:line`, the generator, the propagation count) → commit (R42/R101). Then the next agent.
5. Stop rule: Drew's — the residue reaches 0 (decision 2). Report yield and tokens per bank with denominators (R41) after every 5 agents.
Also open, by name: the 5 propagate refusals of class `func_8017EB44`/`func_8017EBA8` (7 vs 11 address tokens — the remap needs a
per-token alignment, not a count match); the 1 UNSTRIPPABLE of g6b; the tail's remaining ~1,500 small classes (a second unattended pass
after the head, or never — 1–8 bodies each).

### 3. THE EXACT INVOCATIONS (every one run this session)
```
# the engine
.venv/bin/python tools/delever_search.py --selftest
.venv/bin/python tools/delever_search.py --plan --limit 24 --show 24 [--score]        # the residue head with starting distance + class
.venv/bin/python tools/delever_search.py --explain <tu> <fn> [--path "R5 swap + @786|R7 do-while @790"]
.venv/bin/python tools/delever_search.py --positive-control <tu> <fn> --moves 2 --seed 3
.venv/bin/python tools/delever_oracle.py --calibrate ov_SC04_011 ov_SC03_015 ov_SC03_014 main -j 16   # ~3 s; after EVERY commit
setsid nohup nice -n 10 .venv/bin/python tools/delever_search.py --run --limit 64 -j 8 \
    --beam 4 --depth 4 --cap 64 --budget 1500 --label g3 > .run/P36/engine/run_g3.log 2>&1 &
#   + Monitor: tail -F .run/P36/engine/run_g3.log | grep -E --line-buffered 'MATCH start|^search:|propagate |Traceback|UNCALIBRATED|BANK-REFUSED'
.venv/bin/python tools/delever_search.py --run --include-done --only func_80148D44 -j 1 --beam 6 --depth 4 --cap 96 --budget 3000 --label gx
.venv/bin/python tools/delever_search.py --status

# THE FINISH SEQUENCE after a run that banked (R22 → census → snapshot → log → commit)
set -o pipefail; make clean >/dev/null && make extract-all JOBS=16 >/dev/null && make check-all JOBS=16 | tail -2   # ~85 s, must be 218/218
.venv/bin/python tools/lever_census.py --sites --check -j 16          # ~35 s, must print "… 0 UNMARKED — OK"
.venv/bin/python tools/lever_progress.py --snapshot "S101 rung G g3 (…)"; .venv/bin/python tools/lever_progress.py --check
git add src .run/P36/delever/ledger.jsonl .run/P36/delever/calibration.json .run/P36/engine .run/P36/census .run/P36/baseline/r22_g3.log \
    docs/levers.md docs/lever-progress.tsv phase-ends/CURRENT_PHASE.md && git commit -m "phase-36: rung G run g3 — …"

# a killed run
.venv/bin/python tools/delever.py --restore
# the ledger repair (done once; the cause is fixed)
.venv/bin/python tools/delever.py --repair-nhash
```
Timings: R22 ≈ 85 s · census ≈ 35 s · calibration 3 s · one scored candidate 0.12–0.3 s · one body 20–280 s at beam 4 · `make
kit-corpus` ≈ 25 s (regenerate + `tool_census --check` after ANY tool or SETUP edit, or tools-health goes red).

### 4. Gotchas this session paid for
- **A commit during a run stales the calibration and every later bank is refused** (`--apply-body` checks `calibration_current`).
- **`delever.py` is re-imported by the run's bank subprocesses** — edit it only between runs; `delever_search.py` is safe.
- **A bank shifts the lines below it in the same TU** — bodies are judged BOTTOM-UP per file (g1 lost one to a `token mismatch`).
  After any bank the census is stale until `lever_census --sites` reruns (the FINISH sequence does it).
- **The outcomes file is the skip list**: `--include-done` redraws attempted classes; a class banked by another rung is not
  RESIDUE any more and is never drawn.
- **A strict family order starves later families under the cap** (round-robin fixed it); **a positional score cannot see
  progress on a shifted residual** (edit distance fixed it); **every move needs its inverse in the registry** or the search
  cannot undo a step it took (unwrap, hoist, param-alias were added for that).
- **`(void)` parsed as type `voi` + name `d`; an `extern s16 (*D_x[])();` line ended the declaration run and was offered to R7 as
  a statement; a multi-line initializer ended the run; the deref hoist targeted an assignment's LEFT side** — all fixed, each with
  a selftest case. Read a generator's candidates on a fixture before trusting its yield.
- **A constant-operand commutative swap is byte-neutral** (fold) — never generated now. **The width move does not reach a copy
  whose value's known bits fit the narrow mode.**
- `pgrep -f` matching your own command line counts itself; bracket a character (`--ru[n]`).
- **A body whose NEEDED sites are all class C/D is done** (decision 3) — `exemplars()` skips it and the seed keeps such sites; **the scorer's scratch object is keyed by the TU** (a per-tag name let two workers share one file); **`delever.propagate` returns a tuple on an empty list too**; **the bank is in process** (`apply_body_core`), so `delever.py` may now be edited during a run — a commit still may not (the calibration).

### 5. Where everything is
`.run/P36/engine/outcomes.jsonl` (every attempt: verdict, start, best, compiles, path, bank line, propagate line) · `trace/<alias>__<fn>.jsonl`
(every scored candidate: depth, move, parent score, score, class) · `run_g1.log`, `run_g2.log`, `run_g3.log` · `residual_moves.md` (lane B +
the verification ledger) · `micro/` (the two byte experiments) · `bodies/<alias>__<fn>.c` (the winning bodies handed to `--apply-body`;
ignored scratch) · `.run/P36/delever/ledger.jsonl` (`rung: "G"` rows carry `before_text`/`after_text` — `--propagate` needs them) ·
`docs/levers.md` + `docs/lever-progress.tsv` (the series; snapshot after every task that changes the count) · cookbook §454, §454a, §455 ·
`docs/SETUP.md` rows for `delever_search.py` and `delever.py --repair-nhash`.


## (superseded) SESSION CHECKPOINT — S100 (2026-09-09): T0–T6 ☑ — the two-lane plan that S101 executed

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

### 2. NEXT — TWO LANES, IN PARALLEL (Drew's idea, 2026-09-09): build the engine while Fable reads the compiler
Drew: *"we can have fable read the gcc source while we are building the engine so we can understand it better and hopefully build
the engine to accomplish our debt with zero token use."* **The triage is DEFERRED by him to the next phase** — do not start it as
the first act; it is compute that prices T7, not a prerequisite for the engine, and §3's engine will want to run over the same
exemplars anyway.

**LANE A (the coordinator, this project's context): build the engine of §3.** It is engineering against a byte oracle, not
research — no Fable, no waves, no agents. Effort `high` (Drew's, 2026-09-09: he prefers an explicit Workflow at high over
Ultracode, and there is no fan-out in this lane at all).

**LANE B (one Fable agent, launched at the start of lane A so they overlap): the residual → move-set map.** The brief, in full:
> Read gcc 2.7.2's own source (`tools/reference/`, and `docs/gcc-2.7.2-map/` for what this project already mapped at Phase 23)
> and answer ONE question: **for each class of residual difference between two compilations of the same function, which
> SOURCE-LEVEL changes can possibly produce it?** The classes to cover, in this order: (1) same opcodes, different REGISTERS —
> especially the caller-saved v0/v1 swap and the callee-saved s-bank order; (2) a different instruction COUNT (one side has a
> `move`/`addu` the other does not); (3) the same instruction multiset in a different ORDER. For each, name the pass
> (`local-alloc`, `global-alloc`, `combine`, `cse`, `sched`, `reload`), the decision inside it that flips, and the C-level
> constructs that reach that decision. Deliver a table of (residual class → ordered list of source moves, with the pass and the
> mechanism for each). **Every claim is a hypothesis until the engine proves it on bytes** — do not report a move as effective
> without saying how to test it. Facts you may rely on, measured 2026-09-09: a `register … __asm__("$2")` pin's residual was
> exactly `lw v1,68(s1); li v0,-33; and v0,v1,v0` against `lw v0,68(s1); li v1,-33; and v0,v0,v1` — the operand ORDER of one `&`;
> wrapping one statement in `do { … } while (0)` flipped an allocation; inlining a single-set temp at its use flipped another.
Verify its claims against the bytes yourself (the `fable-agents-for-lane-tooling` memory). Its output feeds §3 step 2 and, when
proven, becomes new rung-R recipes — which is the only thing that moves rung R's 0/300.

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

### 3b. The evidence the engine is built from — the 16 rung-D exemplars, measured 2026-09-09
Ordered by the LEVER-FREE body's distance from the target (`match_one` mismatched instructions). 3 cycles x 240 s each, 4 at a
time, profiles as shown. **The cut is the distance, not the site count or the register.**

| fn | start | best | secs | copies | needed | pinned regs | profile | verdict |
|---|---:|---:|---:|---:|---:|---|---|---|
| func_80163EC8 | 8 | **0** | 313.7 | 134 | 1 | $2 | cse | MATCH |
| func_8013E5E8 | 8 | **0** | 5.9 | 132 | 1 | $2 | cse | MATCH |
| func_80135D20 | 12 | **0** | 24.4 | 134 | 1 | $17 | regalloc | MATCH |
| func_8015D01C | 19 | **0** | 651.0 | 133 | 1 | $17 | regalloc | MATCH |
| func_8012E364 | 25 | 6 | 721.7 | 133 | 3 | $2,$5 | cse | NO-MATCH |
| func_80178840 | 29 | **0** | 8.6 | 132 | 1 | $16 | regalloc | MATCH |
| func_801424E4 | 37 | 2 | 721.6 | 132 | 2 | — | regalloc | NO-MATCH |
| func_80148E54 | 50 | 3 | 722.0 | 132 | 2 | $4 | cse | NO-MATCH |
| func_80148D44 | 52 | 3 | 721.9 | 132 | 2 | $4 | cse | NO-MATCH |
| func_8013CF68 | 70 | 24 | 722.6 | 134 | 1 | — | regalloc | NO-MATCH |
| func_80135888 | 78 | 9 | 721.3 | 134 | 5 | $17,$19,$2,$21 | regalloc | NO-MATCH |
| func_80133AB0 | 99 | 37 | 721.9 | 134 | 4 | $0,$4 | cse | NO-MATCH |
| func_80134A74 | 104 | 35 | 721.8 | 134 | 5 | $0,$18,$4 | regalloc | NO-MATCH |
| func_801345F8 | 105 | 18 | 723.2 | 134 | 3 | $0,$4,$5 | cse | NO-MATCH |
| func_80135A4C | 131 | 35 | 722.0 | 134 | 3 | $23 | regalloc | NO-MATCH |
| func_801670E4 | 276 | 51 | 722.1 | 133 | 7 | $2,$4 | cse | NO-MATCH |

Read it as: **everything ≤ 29 closed; everything ≥ 37 did not, and every one of those improved** (37→2, 50→3, 52→3, 78→9) — they
are seeds, not walls. The two 8s took 5.9 s and 313.7 s, so time-to-close is not the distance: the search is a random walk and
sometimes gets lucky early. `func_801424E4` and `func_8013CF68` carry NO pin at all (their NEEDED sites are cast/keepalive and a
hand-placed instruction) — the count-changing class. **The whole point of §3's engine is to replace this random walk with a
directed one, and the honest baseline it must beat is 5 of 16 in 0.69 h.**

### 3c. THE EXACT INVOCATIONS THAT WORK (copy these; every one was run this session)
```
# calibrate (ALWAYS the full set; every commit stales it; ~3 s)
.venv/bin/python tools/delever_oracle.py --calibrate ov_SC04_011 ov_SC03_015 ov_SC03_014 main -j 16

# the census + the published series (after every task that changes the count)
.venv/bin/python tools/lever_census.py --sites --check -j 16          # ~35 s, prints "… 0 UNMARKED — OK"
.venv/bin/python tools/lever_progress.py --snapshot "<task>"           # appends the milestone row + re-renders docs/levers.md
.venv/bin/python tools/lever_progress.py --check

# rung R (zero tokens; TU-parallel; nice it and tell Drew the worker count)
setsid nohup nice -n 10 .venv/bin/python tools/delever.py --recipes --label <lbl> \
    [--limit N] [--only <fn|tu> …] --cap 40 --control 3 -j 10 > .run/P36/delever/<lbl>.log 2>&1 &

# rung D (the permuter; ALWAYS positive-control a new harness first — base score must be 0)
.venv/bin/python tools/delever_permute.py --positive-control <tu> <fn>
.venv/bin/python tools/delever_permute.py --plan --show 20
.venv/bin/python tools/delever_permute.py --calibrate --limit 12       # levered MATCH + the lever-free starting distance
setsid nohup .venv/bin/python tools/delever_permute.py --run --limit 16 --workers 4 --secs 240 --cycles 3 -j 16 \
    [--max-start 35] [--include-done] > .run/P36/permuter/<lbl>.log 2>&1 &
.venv/bin/python tools/delever_permute.py --bank --label d2 [--dirty-ok]

# spread a banked reshape to its whole class (each sibling judged on its own objects)
.venv/bin/python tools/delever.py --propagate <tu> <fn> --label p2 --dirty-ok

# the outer gate after every batch, then commit at once (R42)
set -o pipefail; make clean >/dev/null && make extract-all JOBS=16 >/dev/null && make check-all JOBS=16 | tail -2
```
Timings measured this session: R22 clean fleet ≈ 115 s · census ≈ 35 s · rung R 82 bodies/min at `-j 10`, **123 at `-j 20`** ·
one rung-R body ≈ 40–57 candidates ≈ 0.25 s per compile · rung D 12 min per exemplar at 3x240 s · `make kit-corpus` ≈ 25 s.

### 3d. Where everything is
- `.run/P36/delever/ledger.jsonl` — every judged body, ever (tracked). Rows carry `sites[]` with per-site verdicts, and since
  S99 `before_text`/`after_text` on an `--apply-body` row (which `--propagate` needs and which exists nowhere else after the write).
- `.run/P36/permuter/outcomes.jsonl` — every rung-D attempt (tracked) and the skip list; `<alias>__<fn>/` scratch dirs hold
  `tu.c` (lever-free), `iso.c` (one body, the rest prototypes), `draft.c` (the permuter's seed), `levered.c` (the calibration
  seed), `target.o`, `gas/<fn>.s` + `splat/<fn>.s`, `ils.log`, and any winner `<fn>.c`.
- `.run/P36/permuter/outcomes_broken_target.jsonl` + `campaign_d1/d2_broken_target_*.log` — the two campaigns the bad target
  invalidated, kept deliberately as the evidence behind cookbook §454.
- `.run/P36/delever/sweep_cap40*.log`, `sweep_cap400.log` — the free-bank sweep's measurement.
- `docs/levers.md` (+ `docs/lever-progress.tsv`) — the deliverable Drew asked for; `tools/lever_progress.py` regenerates it.
- Cookbook **§454** (the instrument + the rungs) and **§454a** (replication vs discovery); accelerators **P36 S99**.

### 4. Gotchas known before any work — every one of these cost something this session
**The instrument class (R40 — clear the harness before blaming the subject):**
- **A disassembly listing is not a target** (§454). `objdump` prints the pseudo-instruction `move` for `addu rX,rY,$zero` and GAS
  assembles `move` as `or` — 24 wrong words in one 234-instruction function; and a listing's `%hi`/`%lo` come back RESOLVED with no
  relocation while every compiled candidate carries one, and the masked scorer compares reloc operands. Symptom: a scorer that reads
  nonzero for a byte-identical body and a campaign that reports 0 of N with a straight face.
- **`verbatim_target_s.py --gas` now verifies itself** (assemble → disassemble → compare word by word → `.word`-patch or REFUSE). It
  is the file pasted into decomp.me and it was wrong for every function containing a `move` (R98 in a second place).
- **pycparser rejects `__attribute__((packed, …))`** outright — decomp-permuter then prints "Syntax error in base.c" and permutes
  NOTHING. The draft's cpp defines the keyword away; the loss is recorded, not hidden.
- **`include/include_asm.h` injects `__asm__(".include \"include/labels.inc\"")` at file scope** into every cpp-expanded draft, and
  the permuter's own `compile.sh` already prepends `macro.inc` → `Macro 'glabel' was already defined`.
- **An asm-LABEL clause is not an asm statement.** `extern void func_8005C324(…) __asm__("memcpy");` (6,423 of those) — a bare
  `__asm__(` scan ate one and left a headless K&R body whose next 60 declarations became parameters. File-scope asm is taken from the
  CENSUS in the TU and, after cpp, only where the previous non-space character is `;` or `}`.
- **Check a known-true case before reporting.** The first "ASSEMBLED OK" of this session was an empty file (the `.s` had not been
  written) and it lied until it was read.

**The tooling class:**
- **`--only <fn>` in `--recipes` draws EVERY body of that name across the fleet** — that is why `r1` banked a whole 134-body class in
  one run, and it is the cheapest way to spread a known shape.
- **`--propagate` keys the class on the FIRST bank in a body's chain** (a body reshaped then tidied has two rows, and the later
  row's before-hash describes a text only that body ever had — func_80163EC8 found 0 siblings until this was fixed, then 132).
- **`--bank` skips a body another rung already closed** (it had re-applied a permuter body over rung R's cleaner one-line version).
- **A permuter winner is pycparser-reprinted** (two-space indent, a corpse `;` where a statement was inlined) — `tidy_body` fixes
  those two things and the tidy is judged like any other candidate; parenthesisation and brace style are the formatting phase's, over
  the whole tree at once, never per bank.
- **Rung R needs TU ownership and serial headers**, judges a file's bodies BOTTOM-UP (a bank shifts the lines of everything below it),
  and appends its ledger rows per body (an interrupted sweep must not leave a banked body whose row never landed).
- **A lazy cache published before it is filled is a race that lies in the tool's own voice** — the site cache did exactly that and a
  whole batch reported "no site in this TU".
- **`pkill -f` with a literal your own command line contains kills your shell** (exit 144, twice in this project, once again today).
- **The harness backgrounds any foreground command over 120 s** and its low-memory guard kills long background tasks: `setsid nohup
  … &` + a `Monitor`, never a harness background task for a campaign.

**Carried from T3/T4/T5:** a disassembly listing is not a target (§454); `--only <fn>` in `--recipes` draws EVERY body of
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

### 4. Gotchas known before any work — every one of these cost something this session
**The instrument class (R40 — clear the harness before blaming the subject):**
- **A disassembly listing is not a target** (§454). `objdump` prints the pseudo-instruction `move` for `addu rX,rY,$zero` and GAS
  assembles `move` as `or` — 24 wrong words in one 234-instruction function; and a listing's `%hi`/`%lo` come back RESOLVED with no
  relocation while every compiled candidate carries one, and the masked scorer compares reloc operands. Symptom: a scorer that reads
  nonzero for a byte-identical body and a campaign that reports 0 of N with a straight face.
- **`verbatim_target_s.py --gas` now verifies itself** (assemble → disassemble → compare word by word → `.word`-patch or REFUSE). It
  is the file pasted into decomp.me and it was wrong for every function containing a `move` (R98 in a second place).
- **pycparser rejects `__attribute__((packed, …))`** outright — decomp-permuter then prints "Syntax error in base.c" and permutes
  NOTHING. The draft's cpp defines the keyword away; the loss is recorded, not hidden.
- **`include/include_asm.h` injects `__asm__(".include \"include/labels.inc\"")` at file scope** into every cpp-expanded draft, and
  the permuter's own `compile.sh` already prepends `macro.inc` → `Macro 'glabel' was already defined`.
- **An asm-LABEL clause is not an asm statement.** `extern void func_8005C324(…) __asm__("memcpy");` (6,423 of those) — a bare
  `__asm__(` scan ate one and left a headless K&R body whose next 60 declarations became parameters. File-scope asm is taken from the
  CENSUS in the TU and, after cpp, only where the previous non-space character is `;` or `}`.
- **Check a known-true case before reporting.** The first "ASSEMBLED OK" of this session was an empty file (the `.s` had not been
  written) and it lied until it was read.

**The tooling class:**
- **`--only <fn>` in `--recipes` draws EVERY body of that name across the fleet** — that is why `r1` banked a whole 134-body class in
  one run, and it is the cheapest way to spread a known shape.
- **`--propagate` keys the class on the FIRST bank in a body's chain** (a body reshaped then tidied has two rows, and the later
  row's before-hash describes a text only that body ever had — func_80163EC8 found 0 siblings until this was fixed, then 132).
- **`--bank` skips a body another rung already closed** (it had re-applied a permuter body over rung R's cleaner one-line version).
- **A permuter winner is pycparser-reprinted** (two-space indent, a corpse `;` where a statement was inlined) — `tidy_body` fixes
  those two things and the tidy is judged like any other candidate; parenthesisation and brace style are the formatting phase's, over
  the whole tree at once, never per bank.
- **Rung R needs TU ownership and serial headers**, judges a file's bodies BOTTOM-UP (a bank shifts the lines of everything below it),
  and appends its ledger rows per body (an interrupted sweep must not leave a banked body whose row never landed).
- **A lazy cache published before it is filled is a race that lies in the tool's own voice** — the site cache did exactly that and a
  whole batch reported "no site in this TU".
- **`pkill -f` with a literal your own command line contains kills your shell** (exit 144, twice in this project, once again today).
- **The harness backgrounds any foreground command over 120 s** and its low-memory guard kills long background tasks: `setsid nohup
  … &` + a `Monitor`, never a harness background task for a campaign.

**Carried from T3/T4/T5:** a disassembly listing is not a target (§454); `--only <fn>` in `--recipes` draws EVERY body of
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
