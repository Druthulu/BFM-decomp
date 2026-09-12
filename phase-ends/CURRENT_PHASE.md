# CURRENT_PHASE — Phase 37: the structs phase — the original's types back into the matched C (v2.2.0 → v2.3.0)

> **Gate 1 approved by Drew on 2026-09-11 (S106; plan mode at Max; Opus 5).** The Gen3 order is Drew's: dedup (P35, closed) → pins
> (P36, closed) → **structs** → names. The phase's product: one canonical struct definition per layout, every raw pointer cast a member
> of a typed base, one canonical prototype per definition, the 4,010 Phase-36 lever survivors closed by the shape that was missing — with
> Drew's stop rule **grind to zero** on all three volume counters (raw casts, lying declarations, levers), each "zero" defined honestly in
> the plan's §"What zero means". Names are placeholders + cited evidence (`Unkstruct_<addr>`, `unk<HEX>`); meaning-naming is Phase 38.
> The approved plan is reproduced VERBATIM at the end of this file (§"Approved plan"). **Baseline HEAD at open: `79b2f6f15`** (the
> Phase-36 close commit — made by Claude on Drew's word "you commit the last phase end" and pushed on his word "just push the last
> phaseend as a normal commit", two one-off R6 waivers; **no tag, no release** at phase closes — Drew, S106; the PhaseEnd blocks'
> `git tag` lines are retired from T10 on).
> **R22 obligation:** every batch that touches `src/` is followed by the clean fleet run (218/218) before its commit — this phase changes
> no byte, ever. **Rules ratified at gate 1 by the plan approval: R107–R117** (the PhaseEnd_Phase36 candidates (a)–(k); Drew may still
> veto any of them — say so and the DIGEST entry is amended).

## Milestone (gate 2 — what Drew confirms, each with its literal output)

1. **Definitions:** `type_census --check` → **0 duplicate struct definitions fleet-wide** (one canonical definition per layout, in the
   canonical type files, hex offset comments, VARIANT camps named apart), 0 dead names, 0 definitions outside the canonical files, every
   converted site a field of its type, controls green.
2. **Casts:** `type_census --check` → **0 raw cast sites** in all four forms (`*(T *)(…)`, `*(T *)ident`, `((T *)e)[i]`, `M2C_FIELD(`);
   reinterpret sites counted apart by macro; the player block and the first-parameter entity type are structs in `src/`; the counts
   published in the readability series with the dated snapshot (R75).
3. **Declarations:** **0 lying declarations**; K&R sites counted apart, each marked with its bytes' cause; one canonical prototype per
   definition; the 51 TU-CONFLICT rows resolved (the ledger rows deleted with the bytes that resolved them); the 24 parked P36 classes
   landed; classes E/F/G at 0.
4. **Levers:** `lever_census --check --strict` → **0 pins, 0 asm statements outside the GTE header, 0 per-TU asm macro definitions**; every
   removal attributed `(P37 …)` in the ledger; `verbatim_check --strict` unchanged (the 1998 routines untouched).
5. `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `check-all: 218 passed, 0 failed of 218` (R22); `make tools-health`
   OK with the new rung; `ghidra_rebuild --proof` PASS with the types; the record (T9), the PhaseEnd, the DIGEST append, the log archived;
   v2.3.0.

## Effort / model (R7/R26/R27 — every transition is PROMPTED, never assumed)

- **Max** for T2 (the probe and its pricing), T3's design, T5's head-type layouts, T10 (the PhaseEnd); **xHigh** for T0, T1, T3's finish,
  T4, T6, T8, T9; **low** for T0's bookkeeping. Max is session-only (re-apply each session); xHigh is the highest persistent level.
- **T7 = the P36 lane:** the Agent tool, one agent per TU batch, at Drew's concurrency cap (he sets and retunes it); it STARTS only on his
  word in the session that runs it (the S98 rule); **never an Ultracode wave without his direct approval** (R27). The coordinator's own
  judgment (harvest, toolify, the packs) stays at Max.
- **Drew-only (R6):** every `git push`; the gate-2 confirmation; the milestone-close commit + the `v2.3.0` tag.
- No harness task-list tool exists in this build (no TaskCreate/TodoWrite — checked 2026-09-11) — R28's list is THIS file's ☐/☑ checklist.

## Tasks (plan order; one commit each; ☐ → ☑ with the verify line quoted in the log)

- ☑ **T0** (S106; the commit carrying this line) — Precondition, baseline and the phase file: the P36 close commit `79b2f6f15` (done and pushed this
  session, on Drew's word; the `v2.2.0` tag created then DELETED — no tags/releases at closes, Drew); R22 clean fleet at the open `extract-all: 217 extracted, 0 failed of 217 (+ main, serial)` · `check-all: 218
  passed, 0 failed of 218` · `real 1m25.976s` · exit 0 (`.run/P37/baseline/r22_t0.log`, HEAD `db212f167` — the close commit adds no
  build input); `delever_oracle --recipes` `4284 recipes captured in 14.6 s at -j16; errors 0` · `--snapshot-baseline` `7428 object(s)
  under .run/P36/delever/baseline at db212f167` · `--calibrate main md_SC07_004 ov_SC02_005 ov_SC04_011: 147/147 objects byte-identical
  untouched; twin checks 0 (0 mismatch); positive control DIFFERS on build/src/800.o; 2.3 s — OK` (main 0.108 s/object, ov 0.15–0.16,
  md_SC07_004 0.504) (`.run/P37/baseline/oracle_t0.log`); `.gitignore` P37 allowlist (by-contents, R84; `git check-ignore` verified: logs
  and `.tsv` tracked, `.o` ignored); this file. Verify at the commit: `git status` clean.
- ☐ **T1** (xHigh; the layout/cluster model reviewed at Max) — `tools/type_census.py` + **the struct map** (added at gate 1 on Drew's
  question, P5d — his "Yes — T1 delivers the map"): definitions with o32 layouts + duplicate classes +
  VARIANT camps + dead names; cast sites in all four forms + `M2C_FIELD` with base class/offset/width/sign/load-store; the declaration
  layer (definitions K&R-read, in-scope declarations per TU, the lying set, multi-spelled callees, aliases, builtins, attributes); the P36
  inheritance in ONE file (`.run/P37/census/parked.tsv`) and the func_8013D9B0 `gte-unsigned` inconsistency resolved; coverage (R32) vs
  the raw regex totals; controls (the player block's live-verified fields, MATRIX vs MATRIX_L48, one TU-CONFLICT diagnostic); `progress.py`
  `types` block + README sentence; `readability_progress` learns the uncounted forms; dictionary + SETUP rows; `lever_census`'s stale
  controls re-keyed. **The struct map** (`.run/P37/census/struct_map.json` + the rendered `docs/struct-map.md`, generated — R75): every
  function analysed, every cast site assigned to a base, bases clustered into the types the fleet needs — membership (which functions,
  which parameter/global), the evidence class per merge (same `D_` base · call-graph argument flow · dedup-registry identity · allocator
  return · signature-only, which never merges alone), each type's layout from the union of its sites' (offset, width, sign), its site
  coverage (how many of the 412k it explains — the campaign's leverage order), and every conflict (two incompatible layouts on one base →
  two types or a union); consumed by T2's sampling, T4's typed prototypes and T5/T6. Verify: `type_census: <D> definitions (<L> layouts, <C> duplicate classes, <V> variant camps) · <S> cast sites in <B>
  bodies over <K> bases (<F> forms, coverage OK) · <Y> lying declarations / <Q> callees · controls 4/4` and `struct_map: <T> types over <K> bases explain <S'>/<S> sites (<p> %); <U>
  unassigned bases; <C> conflicts`.
- ☐ **T2** (Max) — The probe: (i) struct spelling on ~150 bodies over the top bases (identical / differing / closing under S+A / residual
  by pass); (ii) the canonical prototype per TU on ~300 TUs (free / byte-changing / refused, causes) + the 24 parked patches as the known-true
  set; (iii) the definition fold on 20 TUs; seconds per object, objects per header edit. Prices T4–T7 with denominators (R41). Verify: the
  probe table in the log with its commands.
- ☐ **T3** (Max design; xHigh finish) — `tools/restruct.py` (rungs L/D/S/S+A/X/R, the delever pattern, the ledger, inflight restore,
  selftest + known-true no-op + negative controls), `tools/struct_layout.py`, the canonical type files' writer (final style; one file per
  symbol space), the reinterpret macros in `include/common.h`, `tools/restruct_cycle.sh` (detached, R115). The Plan agent's stress-test
  lands here as design notes. Verify: selftest; the calibration line; one batch on one overlay end-to-end with R22 green.
- ☐ **T4** (xHigh; unattended cycles) — The declaration layer over the fleet by symbol space (rung D): canonical prototypes where free — carrying the struct map's
  parameter types (`Unkstruct_X *a0`, not `s32 a0`) in the same pass —, the
  free repairs, the 24 parked signature changes with their callers, the 51 TU-CONFLICT rows, class E aliases, `__builtin_abs`, K&R sites
  marked and counted apart, the "carried decl layer" banners deleted. R22 every 2 batches; one commit per batch. **Rules check (P6) after T4.**
- ☐ **T5** (Max for the head types; xHigh to run) — Struct unification (rung L): one canonical definition per layout in the final style,
  VARIANT camps uniquified, dead names deleted, PsyQ layouts under Sony's names, the entity type and the player block authored, main + `md_*`
  onboarded. Verify: `type_census: 0 duplicate definitions …; 0 dead names; controls 4/4`; R22.
- ☐ **T6** (xHigh; unattended cycles) — The cast campaign (rungs S/S+A/X/R), largest leverage first; the 138 absolute casts; `M2C_FIELD`;
  `__builtin_memcpy`; carved word runs (R60 audits). R22 every 2 batches; the readability and lever series fall per commit. **Rules check
  (P6) every 4 batches' worth of tasks.**
- ☐ **T7** (agents at Drew's cap; starts on his word) — The residue lane to zero (rung E), harvest → toolify → regen between draws, the
  residue re-bucketed at every landing (R117).
- ☐ **T8** (xHigh) — The gates: `type_census --check` in `make tools-health`; `attribution_check` folded into `lever_census --check`; the
  close snapshots published; the canonical types into the Ghidra programs (`ExportAnnotations` type rows) with `ghidra_rebuild --proof` PASS.
- ☐ **T9** (xHigh) — The record: cookbook § (incl. the §396(a) correction with its bytes), decision log P37, accelerators, SETUP rows, the
  wiki, the Gen3 pages, the series rendered, tool-index + kit corpus, `doc_links --strict`, tools-health OK.
- ☐ **T10** (Max) — Close: R22 218/218; tools-health OK; PhaseEnd_Phase37.md + DIGEST §0/§2/§3 + this log archived (R19) + kit corpus;
  left uncommitted for Drew's close commit; v2.3.0.

## Decisions (owner's words, in order)

- **Gate 1 (2026-09-11, S106), the four forks (AskUserQuestion):** stop rule → **"Grind to zero"** (the phase does not close while any raw
  cast, lying declaration or lever remains; the agent lane runs until the counters are 0 regardless of token cost); naming → **"Placeholders
  + cited evidence"**; T7 → **"P36 pattern at your cap"**; the declaration layer → **"Full canonical layer"**. The plan's §"What zero means"
  gives each counter its honest, reachable definition (reinterpret macros and unions for the genuine reinterpretations; byte-proven K&R sites
  counted apart; legitimate GTE sequences as project-local macros in the one header, clobber-only steers closed by the shape).
- **Gate 1, Drew's question mid-plan:** *"did we do this project wrong from the start? should we have focused on building structs and not
  letting compiler hints/register pins add up?"* → answered from the record (levers.md §5, DK-65, the S91-b hindsight, P36's `/s` finding):
  the levers' error was the SILENCE, not the lever (38 % never load-bearing; the rest needed knowledge that did not exist until P23–P32);
  types were the larger error — Phase 17 measured correctly that types did not move match-% for m2c and wrongly concluded they could wait:
  they were the banking lever (§236), the width lever, and — P36's finding — a codegen lever through `MEM_IN_STRUCT_P`. A canonical type
  layer growing from the first bank (sotn's shape) was achievable and is the kit's day-one rule. The T2 probe puts the number on it (how much
  of the 4,010 the struct hypothesis closes) → the decision log (R31).
- **Gate 1, after the plan approval:** *"you commit the last phase end"* → Claude made the Phase-36 close commit `79b2f6f15` (a one-off R6
  waiver). Then: *"there is no tag and release, just push the last phaseend as a normal commit"* → the local `v2.2.0` tag deleted (no tags or
  releases at phase closes — the PhaseEnd 🛑 blocks drop their `git tag` lines from T10 on) and `git push origin 79b2f6f15:main` run on his
  word (a second one-off waiver; R6 unchanged for everything else — Drew pushes).
- **Gate 1, after T0 (Drew):** *"insted of our phase plan, should we analyze every single func, and group together all the funcs that need a
  struct that share, so we can build a final struct map of all needed structs?"* → not instead of the plan — it is T1's clustering made a
  first-class deliverable, and it lets T4's canonical prototypes carry the mapped parameter types in one pass (order: census → **map** →
  probe → tools → declarations-with-types → unification → casts). AskUserQuestion: **"Yes — T1 delivers the map"** (P5d, a deliverable added
  to T1; the task order unchanged).

## Rules at gate 1 (P10)

**R107–R117 ratified by the plan approval (2026-09-11; the PhaseEnd_Phase36 candidates (a)–(k), operated through P36):**
R107 ban the silence, not the lever — a compiler-forcing construct is allowed in a banked body only marked, ledgered and published from the
first bank, with a one-compile bank-time trial of the body without it · R108 a generator ships with a negative-control corpus of real bodies
where it must fire, and a regen pass reports its refusal reasons as a histogram · R109 at every landing, run every registered family on the
agent's START text before banking · R110 a scorer's target is the tree's own bytes compiled by the build's own tail, never a disassembly — a
known-true case (the tree's body scores 0) before any campaign · R111 scratch is keyed by the unit of work, never by a worker tag or a file
(R48 extended) · R112 a gate's baseline is a snapshot, not the build directory — a clean rebuild never runs where a live scorer reads `build/`
· R113 a lever's marker names its PASS and its INSTRUMENT (R65 for markers), asserted by an attribution check at the close · R114 a ledger's
"done" is per body (unit, function, after-hash), never by text alone · R115 a long unattended run is DETACHED with a progress log, never a
harness background task (R55 operated) · R116 a marked ordinary-C fake (do-while, dead initialiser) is counted apart from levers and never an
orphan; an invented condition, a dead store or a dummy reassignment is never banked · R117 a "stalling?" question is answered with the residue
bucketed by what each bucket needs before any plan is proposed. **Candidates for Phase 38 gate 1 accumulate here as the phase produces them.**

## Log (append-only; one entry per step, with the literal verify line)

- **S106 2026-09-11 — session start.** Session-start protocol at low effort (the P36 close artifacts still uncommitted in the tree), then
  Drew: `/effort max` + plan mode. Reconnaissance: three Explore agents (the type layer as it stands — 196k tokens; the P36 residue and its
  artifacts — 243k; sotn-decomp's type layer + our types doctrine — 207k) and one Plan agent (the tool/oracle design stress-test, still
  running at the T0 commit — its report lands in T3's design notes). Four AskUserQuestion forks answered (the decisions above). Plan approved
  (ExitPlanMode). Facts the plan rests on, verified this session: `PROMOTE_PROTOTYPES` at `tools/reference/gcc-2.7.2/config/mips/mips.h:1153`
  and the caller-side conversion at `c-typeck.c:1740` (convert to the parameter type, THEN default-promote); the `/s` model in
  `docs/gcc-2.7.2-map/cse_expr.md` §4; `ExportAnnotations.java` carries `type` rows (0 tracked today); `delever_oracle.py` is object-scoped
  and header-capable through `delever.includers()`.
- **S106 — the P36 close commit.** Drew: *"you commit the last phase end"* → `git add -A phase-ends decomp-architect config/kit_coverage_map.tsv
  docs/story-timeline.md docs/story-timeline.svg` (8 files, 632 insertions; nothing ROM-derived) → `79b2f6f15` with the PhaseEnd's message;
  `git tag -a v2.2.0` created locally. **Not pushed (R6) — Drew: `git push origin main --tags`.**
- **S106 — T0 baseline.** `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `extract-all: 217 extracted, 0 failed of 217
  (+ main, serial)` · **`check-all: 218 passed, 0 failed of 218`** · `real 1m25.976s` · `exit=0` (`.run/P37/baseline/r22_t0.log`; run at HEAD
  `db212f167` 04:42 UTC, before the close commit — which adds no build input). `delever_oracle --recipes -j 16` → `4284 recipes captured in
  14.6 s at -j16; errors 0`; `--snapshot-baseline` → `7428 object(s) under .run/P36/delever/baseline at db212f167` (the oracle's baseline path
  is still P36's — T3 decides whether `restruct` shares it or takes `.run/P37/`); `--calibrate main md_SC07_004 ov_SC02_005 ov_SC04_011 -j 16`
  → `147/147 objects byte-identical untouched; twin checks 0 (0 mismatch); positive control DIFFERS on build/src/800.o; 2.3 s — OK` · `main
  85/85 identical, mean 0.108 s per object` · `md_SC07_004 1/1, 0.504 s` · `ov_SC02_005 33/33, 0.152 s` · `ov_SC04_011 28/28, 0.163 s`
  (`.run/P37/baseline/oracle_t0.log`). `.gitignore` P37 block inserted before the outreach block (by-contents form); `git check-ignore -v`:
  `r22_t0.log`/`oracle_t0.log` → `!/.run/P37/baseline/*.log`, `census/parked.tsv` → `!/.run/P37/census/*.tsv`, a `.o` → ignored.

- **S106 — T0 committed `0a55cb0fd`** (this file, `.gitignore`, the two baseline logs, the recalibrated `calibration.json`); tree clean.
- **S106 — the close pushed.** Drew: *"there is no tag and release, just push the last phaseend as a normal commit"* → `git tag -d v2.2.0`
  (0 `v2*` tags remain — none ever existed for v2.0.0/v2.1.0 either); `git push origin 79b2f6f15:main` → `db212f167..79b2f6f15 main`;
  `origin/main` = the close commit; local main 1 ahead (T0).
- **S106 — gate-1 adjustment (P5d): T1 delivers the struct map.** Drew's question + "Yes — T1 delivers the map"; the T1 task line, T4's
  typed prototypes and the decisions above updated; committed as the next log commit.

## 🛑 SESSION CHECKPOINT — S106 (2026-09-11/12, LIVE — refreshed at every task close): gate 1 APPROVED, **T0 ☑** (baseline + oracle + allowlist + this file, committed) — 🛑 **T1 NEXT (the type census, xHigh; its layout/cluster model at Max)** | R22 `check-all: 218 passed, 0 failed of 218` at `db212f167` | the P36 close `79b2f6f15` is committed AND PUSHED (`origin/main`); no tag (Drew: no tags/releases at closes); T0 `0a55cb0fd` local

**Replay this block into the chat at the next session start (R64); it is the ONLY in-phase context the next session inherits.**

1. **Where we are.** Phase 37 (the structs phase) opened 2026-09-11 in S106 at Max. Gate 1 approved with Drew's four decisions: **grind to
   zero** (raw casts, lying declarations, levers — the plan's §"What zero means" defines each honestly); **placeholders + cited evidence**
   for every type/field name; **T7 = the P36 agent lane at Drew's cap, started only on his word**; **the full canonical declaration layer**.
   R107–R117 ratified. T0's baseline and oracle calibration are done (the log entry above has every verify line). T0 is committed (this file, `.gitignore`, `.run/P37/baseline/*.log`, the recalibrated `.run/P36/delever/calibration.json`).
   NEXT = **T1 — the type census `tools/type_census.py` + THE STRUCT MAP** (`.run/P37/census/struct_map.json` + `docs/struct-map.md`)
   at xHigh (its layout/cluster model at Max) — added to T1 on Drew's word after T0 (P5d); T4's prototypes carry the map's parameter types.
2. **What the next session must know before T1.** (a) The population table in the approved plan below is a gate-1 grep census — T1
   re-derives every number with a self-asserting tool (R32/R37) and its verify line is the plan's. (b) The four cast forms: `*(T *)(…)`
   (411,850, the readability regex `tools/readability_progress.py:31`), `*(T *)ident` (26,279), `((T *)e)[i]` (14,491), `M2C_FIELD(`
   (19,542) — the last three are UNCOUNTED by the series today (R32 gap; T1 adds them with a dated `corrections` entry). (c) The 24 parked
   P36 classes have NO list with reasons anywhere — the reasons are split across `phase-ends/logs/Phase36.md:2261-2267` and `:2197-2199`,
   the bank lists' MSG column (`.run/P36/s105/banks_*.txt`), and each pack's `mechanism.md` headline; `.run/P36/s105/pick.py`'s PARK set (44
   names) mixes parked classes with minimum-lever banks; patch files exist for 6 (`main__func_800385C0/scratch/signature.patch`,
   `main__func_80029D3C/scratch/patch_signature.c`, `ov_SC07_007__func_80180FA4/scratch/signature_3args.patch`,
   `ov_SC02_027__func_80180A54/scratch/signature.patch`, `md_SC07_004__func_801A1E94/signature.diff`, `…__func_801A5C44/signature.diff`),
   whole-TU scratch copies for 8 more; `func_80180200` has no pack (it lives in `ov_SC03_115__func_8017FC5C/`). (d) `func_8013D9B0`'s 268
   markers are kind `gte-unsigned` (NON_LEVER) — OUTSIDE the 4,010 headline though the PhaseEnd lists it among the residue heads; T1 resolves
   this on the bytes. (e) `lever_census`'s known-true controls: three of four return N-A (their T1 body hashes are stale) — re-key them (R85).
   (f) The 4,010 reconcile exactly against the ledger: 1,637 drawable RESIDUE + 1,080 minimum-lever banks in PARK + 593 parked RESIDUE +
   450 GTE clobber variants (`gte-lever`; 64 per-TU `_m` macro definitions, `gte_rt_m` 55) + 94 arg-only pins (83 classes) + 83 whose latest
   ledger row is a failed attempt (invisible to `pick.py`; `delever.py --redraw`) + 24 + 18 + 13 asm-body + 10 drawn + 8 file-scope.
   (g) The §396(a) refuting body IS recorded: `.run/P36/agents/ov_SC03_110__func_801800F0/mechanism.md:64-70` (d11) — T9 writes the correction.
   (h) The type tools' reach: `lift_types.py` scans only `src/ov_*/*.c` (line 49); `engine_types.h` is included by 3,818 TUs via
   `engine_prelude.h` but by 0 of the 85 root `.c` and 12 of 87 `md_*`; `decl_repair.py` compares `.text/.rodata/.data` sections (the scratch
   path lands in the object) while `delever_oracle` compares whole objects compiled in place.
3. **Environment.** `~/bfm-decomp` on ext4; `.venv/bin/python`; every build with `JOBS=16`/`-j`; the headless Ghidra MCP was started by
   the SessionStart hook (pid in `.run/ghidra-mcp.log`) and is NOT needed until T8 — stop it via the sentinel before any commit that touches
   `ghidra/` (nothing does until T8; R23). The oracle's snapshot baseline: `.run/P36/delever/baseline/` (7,428 objects at `db212f167`, taken
   after the green R22 — R112). The Plan agent (tool design stress-test) may still be running or have reported: its report goes into T3's
   design notes; if it is lost, T3's design at Max re-derives it from the plan's §B questions.
4. **Commands that work.** R22: `make clean && make extract-all JOBS=16 && make check-all JOBS=16` (≈86 s; read the exit code with
   `pipefail`). Oracle: `.venv/bin/python tools/delever_oracle.py --calibrate <aliases> -j 16` (147/147 in 2.3 s). Census (P36's, for the
   lever side): `.venv/bin/python tools/lever_census.py --check -j 16`. Series: `tools/readability_progress.py --snapshot <label>`,
   `tools/lever_progress.py --check`. Tools-health (foreground, ~8–15 min): `make tools-health`.

## Approved plan (verbatim, gate 1 — 2026-09-11)

# Phase 37 — the structs phase: the original's types back into the matched C (v2.2.0 → v2.3.0) — gate-1 plan

> Gate 1, 2026-09-11, plan mode at Max (Tier 1). Drew's Gen3 order: dedup (P35) → pins (P36) → **structs** → names. Owner decisions
> recorded at the end. On approval: T0 writes this plan verbatim into `phase-ends/CURRENT_PHASE.md`, builds the harness task list (R28),
> and execution is one task at a time (P3–P5). **Precondition:** Drew's Phase-36 close commit + the `v2.2.0` tag (the block in
> `PhaseEnd_Phase36.md` §🛑) — the close artifacts are still staged/uncommitted in the tree (`git status`: `R CURRENT_PHASE.md ->
> logs/Phase36.md`, `?? PhaseEnd_Phase36.md`, `M DIGEST.md` …); T0 refuses to start on a tree that still carries them.

## Context — why this phase, and what it is really about

The Gen3 charter (`docs/gen3-standards.md` §2 rule 4, §4 step 3; `docs/gen3-handoff.md` §2 item 1, §2.1) says: *types come from the code,
names from observation* — unify the drafter-invented struct definitions into one per shape, turn raw address casts into declared, typed
data, and do it before any field is named. R95 (the S91-b doctrine) is the binding rule: **types are a banking lever and a width lever;
a canonical type file; widths proven by the bytes; no duplicate definition or raw address cast.**

Phase 36 changed what this phase is. It took the compiler-forcing levers from 53,234 to 4,010 and found that the last third of the residue
is not codegen the pin lane can read its way out of — it is **wrong signatures** (a `(void)` function that reads `$a0`; a `void` one that
returns `$v0`; an `s16` parameter the bytes use as `s32`), **missing struct types** (the compiler's own alias tests decide by
`MEM_IN_STRUCT_P`), **carved data** a struct copy would address in one relocation, and one GTE spelling. Its evidence is byte-proven:
d10's register union (`ov_SC05_001__func_8017EF88`: three pins + two keep-alives → 0 with a `union { struct { s16 x, y; } v; s32 sxy; }`),
a18's `extern u16 X[]` (the MEM_IN_STRUCT alias escape, `sched.c:837-839`), f10's body-local structs (`ov_SC06_006__func_80180AE8/FE8`:
"the aggregate-vs-scalar MEM flag is the whole lever"), f3's `s16[3]` arrays (identical after linking), func_80186CE0's 20-byte struct
copy over five carved word symbols.

**The fact the plan is built on: struct spelling is not byte-neutral in gcc 2.7.2.** `*(T*)(p+k)` gets no `/s`; `p->f`, `q[k]`, `*(Blk*)p`
get it; the scheduler's alias escape (`sched.c:830-865`) and cse's kill table read that flag (`docs/gcc-2.7.2-map/cse_expr.md` §4;
cookbook §30/§351/§379/§456/§469). So this campaign is gated exactly like a match — object oracle per TU, R22 per batch — and its
residue is informative: a site where the member spelling moves bytes is a site where the original's shape was different, and the
marked lever that survives beside it is the P36 residue this phase is meant to close. Phase 17's "types are byte-neutral" (0/10/2 on a
structural-miss sample) measured m2c drafting, not member-vs-cast spelling in a matched body (`docs/struct-core-pivot.md`, its caveats).

Nothing in this phase invents a name. Struct and field names are placeholders (owner decision 2) or citations of recorded evidence
(`docs/memory-map.md` §3.4, `docs/actor-struct.md`); meaning-naming is Phase 38.

## The population, measured at gate 1 (grep/scan census, 2026-09-11 — T1 re-derives it with a self-asserting tool, R32/R37)

| Unit | What | Count | Where / command | Notes |
|---|---|---|---|---|
| **U1 definitions** | struct/union bodies in `src/shared/engine_types.h` | ~1,180 (1,089 `typedef struct` + 90 tags + 1 union; the charter's 1,232 counts 53 forward decls) | `grep -cE '^typedef struct' src/shared/engine_types.h` | **103 exact-duplicate groups cover 919 of 1,162 names; 91 layout groups cover 946** (`s32 w[8]` ×68 names, `u16 x,y,z,w` ×99, `s16 v[4]` ×56, SVECTOR ×50); 467 double-suffixed `Name_ADDR_ADDR`; 123 dead names |
| | struct/union bodies inside `.c` files | **5,547** (3,990 file-scope, 1,557 block-scope) in 1,725 of 4,121 TUs | `grep -rhoE '^\s*(typedef\s+)?(struct\|union)\s*\w*\s*\{' --include='*.c' src \| wc -l` | 1,900 distinct names; `Prim_8016E7C8` defined in **1,192** files, `Ent` 394, `Blk8` 314 (the "carried decl layer" banner in 3,546 TUs); 32 names with >1 body; `lift_types.py` scans only `src/ov_*/*.c` |
| | in per-function shared headers / `*_shared.h` / `include/` | 52 / 24 / 2 | | |
| **U2 cast sites** | `*(T *)(…)` (the readability regex) | **411,850** | `tools/readability_progress.py` | + **26,279** `*(T *)ident`, **14,491** `((T *)e)[i]`, **19,542** `M2C_FIELD(` — uncounted today (R32 gap); struct member reads 177,902 |
| | by base | first parameter `a0`/`param_1`/`arg0` **188,844 (46 %)** on 289 offsets (`+0x20` pointer 18,215; `+0x2`, `+0x1C`, `+0x2C`, `+0xE`, `+0xA`, `+0x6`, `+0x34`, `+0x234` …); `(s32)matrix + k` 53,797; `D_`/`&D_` bases 47,178 over 6,040 symbols; nested 18,282 | | one entity type owns half the debt; the player block is **64 bare `D_80078Exx` globals** (`D_80078E78` 6,792 mentions) with a documented field table and no struct in `src/` |
| | absolute-address casts `*(T *)0x80…` | **138** | `grep -rhoE '\*\)\s*0x80[0-9A-Fa-f]{6}' src \| wc -l` | the charter's low-hanging fruit |
| **U3 declarations** | extern function declarations | **4.28 M** (4.24 M file-scope) per-function blocks; 12,120 declared names; **3,894 callees with >1 parameter-list spelling** | python line scan | no canonical header exists; the Phase-16 global header broke matches (`struct-core-pivot.md`) |
| | lying call declarations | **98,648** over 1,609 callees (91,357 `()`, 7,291 `(void)`/narrow; 33 in pinned bodies) | `tools/argcheck.py` | `decl_repair.py` repaired 16,759 free (S102); `PROMOTE_PROTOTYPES` (mips.h:1153): callee bytes depend on the DEFINITION's widths, caller bytes on arity |
| | ledgered TU-CONFLICT classes | **51** (16 int-from-pointer, 19 conflicting types for a function, 3 for a `D_`, 4 undeclared, 4 too few args, 1 redefinition) | `config/dedup_exceptions.tsv` | the S1 ledger's types-phase inheritance |
| | `h_text` groups (bytes vary per binary through the TU's declarations) | 38 | `config/dedup.us.yaml` | gate every member |
| **U4 P36 residue** | marked pin/asm sites | **4,010** = 1,637 drawable RESIDUE + 1,080 minimum-lever banks in PARK + 593 parked RESIDUE + 450 GTE clobber variants + 94 arg-only pins + 83 whose latest ledger row is a failed attempt + 24 minimum-lever not in PARK + 18 + 13 asm-body + 10 drawn + 8 file-scope | `tools/lever_census.py --check`; the ledger `.run/P36/delever/ledger.jsonl` | **24 parked classes / 453 bodies** (6 with patch files, 8 more with whole-TU scratch copies, `func_80180200` inside `ov_SC03_115__func_8017FC5C/`); heads func_8013CF68 ×134 (`la`), func_80178970 ×134 (`$2`); the five S103 head classes 933 sites; **func_8013D9B0's 268 markers are `gte-unsigned`, OUTSIDE the 4,010** (a census inconsistency T1 resolves); the `gte_stORGB` respelling (`include/gte_inline.h:237`; sotn's header adds 7 project-local GTE macros) |
| **U5 P36-deferred classes** | E asm-label aliases `extern u16 aD800B9A02 __asm__("D_800B9A02");` / F `__builtin_memcpy` 302 + `__builtin_abs` 297 / G `__attribute__((packed/aligned))` 76 | 8,331 (6,196 file-scope) / 599 / 76 | the P36 gate-1 table | E = a second typed view of one symbol (a union/array/struct in truth — a18, f3); F memcpy = a struct assignment (`expand_block_move`, §391 alignment); G = a wrong layout |
| **U6 instruments** | `delever_oracle.py` (object oracle, header-capable via `delever.includers()`; `engine_types.h` reaches 3,818 TUs ≈ 3,900 objects at 0.08–0.14 s each), `delever.py`'s engine pattern, `cdecl.py`, pycparser 2.23, `argcheck`/`decl_repair`, `lift_types`/`uniquify_type`/`build_engine_types`, `canon_sig_reconcile`, `conform_decls`, `decl_prior`, `ram_probe.py`, `ExportAnnotations.java` (type rows supported: struct/union/enum/typedef/fndef with fields — **0 tracked today**) | | | nothing exists that infers a layout from base+offset+width evidence, rewrites a cast to a member, or merges same-layout names |

The reference read (R106, X2 — data): sotn-decomp holds **479** typedef structs for a whole game, **26** raw scalar casts and 2,335
`LOH/LOW`-style reinterpret macros, one `Entity` (0xBC) + a 367-arm `Ext` union, `/* 0xNN */` offset comments, `unk<HEX>` fields,
anonymous bit-field padding, `Unkstruct_<addr>` for the unknown, `SYNC_FIELD` offset asserts; its declarations are per-overlay headers
(`src/dra/dra.h`: 194 prototypes + 152 externs, placeholders typed), no per-TU extern lists.

## The oracle and the invariant

- **Inner oracle (per candidate, 0.1–1 s):** `tools/delever_oracle.py` — the TU compiled IN PLACE through the build's own rule against
  the snapshot baseline (`--snapshot-baseline` at T0; whole-object equality; calibration 100 % untouched + a positive control before any
  verdict, R39/R56/R57). A header edit is judged on EVERY includer (`delever.includers()`), serialized; twins on both objects; the 38
  h_text bodies on every member; `-O0` TUs and main's pad stage through the same recipes.
- **Outer gate (per batch, ≈90 s):** `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `check-all: 218 passed, 0 failed
  of 218`, read by exit code with `pipefail` (R22, R97); commit the moment it is green with the log line and the 🛑 headline (R42, R101).
- **The type invariant (new, asserted from T1 on):** every struct definition in the canonical type files has a computed layout; no two
  definitions share a layout under different names (VARIANT camps are DIFFERENT types under different names, §64a); every converted site's
  `(base type, offset, width, signedness)` is a field of its type (the `SYNC_FIELD` equivalent, run by the census, not by the PC build);
  every raw cast that remains is counted and, in a lever-bearing body, ledgered with its pass.
- **The declaration invariant:** a function has one canonical prototype, derived from its DEFINITION; a TU's in-scope declaration equals
  it wherever the object is unchanged; where the bytes refuse, the site keeps its local declaration with its cause named in the ledger and
  the count published — never a silent lie (the P36 doctrine: ban the silence, not the lever).

## The ladder (deterministic first; tokens last)

| Rung | What | Cost | Who |
|---|---|---|---|
| **L layout** | parse every definition (canonical header + every `.c`), compute o32 layouts, hash; fold exact/layout duplicates onto one canonical name (majority body; address-suffixed placeholder where the purpose is unknown); strip local copies where what becomes visible is layout-identical (lift_types' three laws, extended to `.c` file-scope and block-scope, main and `md_*`) | compiles only | tool |
| **D declarations** | per TU: the canonical prototype (K&R-read from the definition) replaces each per-function extern where the object is unchanged; the free `decl_repair` set; asm-label aliases replaced by one typed declaration; `__builtin_abs` → `abs`; the 24 parked signature patches (definition-side fixes: `s16`→`s32`, `(void)`→`(s32)`, `void`→`void *`) with their callers | compiles only | tool |
| **S struct spelling** | per body, per base with a type: `*(T*)(base + k)` → `base->unkK` (nested, address-of, strides); `M2C_FIELD` → members; `((T*)x)->f` → typed base; `__builtin_memcpy(&a,&b,N)` → `a = b`; carved word runs → one record table (`func_80186CE0`, f3); the 138 absolute casts → declared symbols; oracle per object | 1 compile per body | tool |
| **S+A the struct hypothesis** | for a lever-bearing body: rung S with the body's marked levers stripped, then greedy (P36's rung B) — the levers come off where the struct was the missing piece | ≤ sites+1 compiles | tool |
| **X classify** | a body whose member spelling moves bytes: the residual classified by pass (sched alias escape / cse kill / width / other — `delever_search.py`'s classifier) and ledgered; the plain cast kept MID-CAMPAIGN, counted, and queued for R then E — decision 1 says it does not stay | 0 | tool |
| **R recipes** | the shapes the record already names (`u16 X[]` vs scalar, the `s16[3]` array, the register union, the cast-at-the-shift, `p = &tbl[i]` to drop `/s`, the one-struct-pointer rule §357) tried mechanically per X site; **the rung grows after every agent landing (harvest → toolify)** | compiles only | tool |
| **E agents** | what R leaves, if owner decision 3 allows: one agent per TU batch with the pack (body, target listing, the ledger's X sites, `alloc_table`/`cc1_dumps_tu`, the `/s` model, METHOD_S103 steps 1–25, §454–§457, a known-true run on the start text at every landing — P36 candidate (c)); deliverables early (R67); the tool judges; harvest → toolify → regen before the next draw | tokens | agents (Agent tool; Drew's cap; his word to start) |
| **M mark/ledger** | every remaining raw cast in a lever-bearing body and every kept local declaration carries its ledger row; the census asserts 0 UNLEDGERED; `lever_census --check` keeps 0 UNMARKED, and `--strict` is asserted the day it passes | 0 | tool |

## Tasks (plan order; one commit each; ☐ → ☑ with the verify line quoted in the log)

- **T0 — Precondition, baseline and the phase file** (xHigh; low for bookkeeping). Refuse to start until the P36 close commit and `v2.2.0`
  are in `git log`/`git tag`; R22 clean fleet at the open (`.run/P37/baseline/r22_t0.log`); `delever_oracle --snapshot-baseline` re-taken
  on that tree + `--calibrate` on two overlays + main + one module; `.gitignore` P37 evidence allowlist (`.run/P37/{baseline,census,probe,
  restruct,decls,agents}/`, text only, by-contents form R84); `phase-ends/CURRENT_PHASE.md` from this plan; harness task list (R28).
  Verify: the R22 line; the calibration line; `git status` clean after the commit.
- **T1 — The type census `tools/type_census.py`** (xHigh; its layout/cluster model reviewed at Max). Derived from `share_census`'s instance
  records (R33); a comment/string-aware site parser (the `lever_census` approach; pycparser where a whole declaration must be understood,
  `cdecl.py` for declarators); **(a) definitions:** every struct/union/typedef fleet-wide with its o32 layout hash, duplicate classes, VARIANT
  camps, dead names, shadowing (`.c` names that also exist in the header); **(b) cast sites:** all four forms + `M2C_FIELD`, base class
  (parameter / local / `D_` / `&D_` / absolute / nested / member), offset, width, signedness, load/store, address-of; per-base offset maps
  across functions (the clustering input); **(c) declarations:** every function's definition signature (K&R-read), the in-scope declaration
  per TU, the lying set (`argcheck` as a library), the 3,894 multi-spelled callees, the asm-label aliases, builtins, attributes; **(d) the
  P36 inheritance:** the 24 parked classes with their reasons in ONE file (`.run/P37/census/parked.tsv`: fn, alias, copies, sites, what
  it needs, the patch path) — the record has no such list; the func_8013D9B0 `gte-unsigned` inconsistency resolved (counted or the markers
  dropped, on the bytes); **coverage (R32):** sites found == the raw regex totals for each form, else FAIL; **controls:** the player block's
  live-verified fields (`+0x8C s32`, `+0xB2/+0xB4/+0xB6/+0xB8 u16`, `+0x108/+0x10C s16`) recovered from the `D_80078Exx` accesses; `MATRIX`
  (32) vs `MATRIX_L48` (48) as two layouts; one TU-CONFLICT row's diagnostic reproduced. Output `.run/P37/census/*.json/.txt`; `progress.py`
  publishes a `types` block (definitions, distinct layouts, duplicate classes, cast sites by form, lying declarations, aliases) + the README
  sentence (R75); `readability_progress.py` gains the uncounted forms (a dated `corrections` entry). Dictionary + SETUP rows (R87, R21);
  `lever_census`'s three stale controls re-keyed (R85). Verify: `type_census: <D> definitions (<L> layouts, <C> duplicate classes, <V>
  variant camps) · <S> cast sites in <B> bodies over <K> bases (<F> forms, coverage OK) · <Y> lying declarations / <Q> callees · controls 4/4`.
- **T2 — The probe (R37)** (Max). Three stratified probes on the calibrated oracle, each with denominators: **(i) struct spelling** — ~150
  bodies over the top bases (the first-parameter entity type, the player block, `(s32)matrix` MATRIX/SVECTOR bases, three `D_` record
  tables, the shared headers): % identical after rung S, % differing, of the differing how many close under S+A (levers off), the residual
  classes by pass; **(ii) declarations** — `decl_repair`-style judgement of the canonical prototype per TU on ~300 TUs across spaces: free /
  byte-changing / refused, causes histogram (`(void)` truncation, width, arity, K&R); the 24 parked patches applied and gated as the
  probe's known-true set; **(iii) definitions** — the fold of the 103 exact + 91 layout duplicate groups and the `.c` file-scope copies on
  20 TUs: textual fold / layout fold / VARIANT; seconds per object; objects per header edit. Prices T4–T7 with denominators (R41) and fixes
  the rewrite table. Evidence `.run/P37/probe/`. Verify: the probe table in the log with its commands.
- **T3 — The tools** (Max design; xHigh finish). `tools/restruct.py` (rungs L/D/S/S+A/X/R; the `delever.py` pattern: positional token-exact
  rewrites with REFUSAL on mismatch (R43), the file as the write unit, `--plan/--apply/--class/--only <base|tu|type>/--batch/--batches 1/--label`,
  workers own whole TUs, header edits serialized and judged on every includer, `inflight.json` the only restore (R102), the ledger
  `.run/P37/restruct/ledger.jsonl` keyed alias+tu+function+body-hash (R48) with per-site verdicts MEMBER / KEPT(pass) / REFUSED(reason) /
  DECL-CANON / DECL-KEPT(cause), progress logs (R55), selftest fixtures for every form + a known-true no-op run (a body already spelled
  with members), negative controls (R39)); `tools/struct_layout.py` (the o32 layout computer + the field assertion, shared with the census);
  the canonical type files' writer (offset comments in hex, `unk<HEX>` fields, `// size = 0x..`, the PsyQ ground-truth block preserved,
  one file per symbol space — `src/shared/engine_types.h` stays the `ov`/resident file; `src/shared/main/types.h`, `src/shared/<slot>/types.h`
  added; main's and the modules' TUs gain the include); the named reinterpret macros in `include/common.h` (sotn's `LOH/LOW/…` form, each
  proven byte-identical to the cast it replaces); `tools/restruct_cycle.sh` (batch → exit code → log entry → commit → R22 every N batches;
  DETACHED with a progress log, never a harness background task — R115). The Plan agent's stress-test lands here as design notes. Verify:
  selftest; the calibration line; one batch on one overlay end-to-end with R22 green.
- **T4 — The declaration layer** (xHigh; unattended cycles). Rung D over the fleet by symbol space: the canonical prototype per TU where
  free; the 16,759-style free repairs; the 24 parked signature changes landed with their callers (definition-side fixes, then the fleet's
  declarations, gated — their levers come off: the first P36 residue bucket falls); the 51 TU-CONFLICT rows resolved (a shared header
  re-exemplared or a declaration conformed) or re-ledgered with the byte cause; class E aliases → one typed declaration where free (a symbol
  needing two widths is an aggregate → T6); `__builtin_abs` → `abs`; the byte-proven K&R sites marked and counted apart; the byte-changing
  remainder ledgered with its cause (definition-side fixes queued for T6/T7) and published; the 3,546 TUs' "carried decl layer" banner blocks
  deleted as their contents become canonical. Batches < 10 min; R22 every 2 batches; one commit per batch with the census line. **Rules check
  (P6) after T4.** Verify per batch:
  `restruct D: batch <k> — <n> declarations canonical / <m> kept (<causes>) in <t> TUs; gated <x>/<x> identical`; R22 `218 passed`.
- **T5 — Struct unification** (Max for the head types' layouts and the naming of the canonical files; xHigh to run). Rung L: the 103 exact
  + 91 layout duplicate groups in the header and the 5,547 in-`.c` definitions folded to one canonical definition per layout, written in the
  final style (owner decision 2), the VARIANT camps uniquified (§64a), the 123 dead names deleted, the PsyQ-identical layouts under Sony's
  names (MATRIX/SVECTOR/VECTOR/POLY_*), `MATRIX_L48` kept as documented; the entity type behind the first parameter and the player block's
  struct authored from the census's evidence (fields typed by width, named `unk<HEX>` or by the cited record); main and `md_*` TUs onboarded
  to their canonical file. Every step oracle-gated; R22 per batch. Verify: `type_census: 0 duplicate definitions (<L> layouts = <D>
  definitions, <V> variant camps named apart); 0 dead names; controls 4/4`; R22 `218 passed`.
- **T6 — The cast campaign** (xHigh; unattended cycles; largest leverage first: shared headers → the first-parameter entity type → the player
  block and the top `D_` record tables → MATRIX/SVECTOR bases → the rest). Rungs S / S+A / X / R over the population; the 138 absolute casts
  → declared symbols; `M2C_FIELD` → members; `__builtin_memcpy` → struct assignment; carved word runs → record tables (carve-state edits under
  R60: `interleave_check` + `pads_audit`); the lever count falls with the struct hypothesis and is attributed per site (`(P37 rung S+A)`).
  Batches < 10 min; R22 every 2 batches; the readability series and the lever series fall per commit. **Rules check (P6) every 4 batches'
  worth of tasks.** Verify per batch: `restruct S: batch <k> — <n> sites → members / <m> kept (<pass histogram>) in <b> bodies; levers −<l>;
  gated <x>/<x> identical`; R22.
- **T7 — The residue lane** (owner decision 3; the coordinator at Max, agents at Drew's cap, NO Ultracode wave without his direct approval —
  the S98 rule). Rung E over the X residue and the P36 heads, TU-batched cheapest-residual-first; the harvest → toolify → `regen` gate
  between draws (the recipe rung R grows; a mechanical shape sweeps the residue for free); the residue re-bucketed by what it needs at every
  landing (P36 candidate (k)); the stop rule per owner decision 1. Verify per landing: the agent's verdict on the bytes, the known-true run
  of every registered recipe on the start text, `lever_census --check` 0 UNMARKED, R22 per bank.
- **T8 — The gates and the Ghidra mirror** (xHigh). `type_census --check` in `make tools-health` next to `lever_census` (0 duplicate
  definitions; every converted site a field of its type; 0 UNLEDGERED kept casts in lever-bearing bodies; the parked list empty or
  re-ledgered) + P36's `attribution_check` folded into `lever_census --check` (every marker names its instrument — candidate (g));
  `progress.py`/`readability_progress`/`lever_progress` publish the close snapshot (R75); **the canonical types into Ghidra**: a headless
  step that authors the canonical struct definitions into the tracked programs (from the C headers via `cdecl`/`struct_layout` → the
  `ExportAnnotations` `type` row form), exported to `config/ghidra/*.jsonl`, `tools/ghidra_rebuild.sh --proof` PASS (R9; MCP stopped, R23).
  Verify: `tools-health: OK` with the new rung; `--proof` PASS for the programs that gained types.
- **T9 — The record** (xHigh). Cookbook § (the `/s` campaign's byte findings by pass; the declaration causes; the shapes the lane produced;
  **the §396(a) correction with its bytes** — the refuting body is recorded in `ov_SC03_110__func_801800F0/mechanism.md:64-70`, owed since
  S104); decision log P37 (R31); accelerators; SETUP rows for every tool (R21); the wiki (a "The type layer" page; `Where-the-project-goes-next`
  item 3 + the table row; `Verification-and-progress`; the how-to's integration chapter); `gen3-standards.md` §4 step 3 + `gen3-handoff.md`
  dated snapshots; `docs/levers.md` and `docs/readability.md` rendered; `docs/tool-index.md` + the kit corpus regenerated (`tool_census
  --check`, `kit_lint`, `kit_coverage` with the R107–R117 dispositions); `doc_links --strict` 0/0; `make tools-health` OK.
- **T10 — Close** (Max; fresh session or Drew's call). R22 218/218 from clean; tools-health OK; PhaseEnd_Phase37.md + DIGEST §0/§2/§3 + the
  log archived (R19) + kit corpus; left uncommitted for Drew's close commit (R6); v2.3.0.

## What "zero" means, counter by counter (owner decision 1 = grind to zero; each definition is honest AND reachable)

- **Raw casts → 0.** No `*(T *)(…)`, `*(T *)ident`, `((T *)e)[i]` or `M2C_FIELD(` in `src/` (all four forms the census counts). Every
  base+offset access is a member of a typed base; every genuine REINTERPRETATION (the original reading a word as two halves, a struct as bytes)
  is a union field or one of a small set of named macros (sotn's `LOH/LOW/LOHU/…` form, defined once in `include/common.h`), which the census
  counts apart as "reinterpret sites" and lists per macro — never a bare pointer cast on a sum.
- **Lying declarations → 0.** Every call site's in-scope declaration is the callee's canonical prototype. A byte-proven K&R call (the matched
  caller passes fewer arguments than the definition takes and every spelling of a prototype moves its bytes) is not a lie about the callee — it
  is the original's calling convention: it keeps a `()` declaration carrying `// K&R: <n> of <m> args (P37 rung D, <TU>)`, is counted apart
  ("K&R sites") and published. A definition proven wrong by its own bytes (a `(void)` that reads `$a0`, a `void` that returns `$v0`, an `s16`
  the bytes treat as `s32`) is FIXED at the definition (the P36 parking signals, §456). Width rule (verified in `tools/reference/gcc-2.7.2/
  c-typeck.c:1740` and `function.c:3664-3676`): under `PROMOTE_PROTOTYPES` a prototyped narrow parameter is converted in the CALLER (a
  possible `andi`/`sll-sra`) and narrowed again at the callee's ENTRY — so the callee's entry code is the oracle for the definition's width
  (no entry narrowing ⇒ the parameter is `s32`, fix the definition), and a caller whose bytes lack the prototype's conversion while the callee
  narrows is a K&R site, not a lie.
- **Levers → 0.** `lever_census --check --strict`: 0 register pins, 0 asm statements outside `include/gte_inline.h`, 0 per-TU asm macro
  definitions. A GTE variant that is a legitimate coprocessor sequence (a three-op load, a respelled store — `gte_stORGB`) becomes a
  project-local macro in the one GTE header under a Sony-style name (Drew's S104 ruling (b); sotn's `libgte.h` adds seven such); a
  clobber-only `_m` steer is a lever and is closed by the shape (the struct hypothesis) — it may not be re-homed as a macro.
- **A function is identified by its DEFINITION, not its address.** Same-address different-body overlay functions are different functions with
  their own prototypes (the 38 h_text bodies prove the original overlays' declaration environments differed); the canonical prototype is keyed
  by (symbol space or binary, address, body) and the fleet-wide form applies only to shared/resident/main definitions.
- The phase does not close while any counter is above zero (Drew, gate 1). T7 is therefore open-ended; every landing re-prices it with
  denominators, the residue is re-bucketed by what it needs (R117), and Drew may amend the rule as he did at P36 S104 — the plan follows his
  latest word and records it.

## Milestone (gate 2 — what Drew confirms, each with its literal output)

1. **Definitions:** `type_census --check` → **0 duplicate struct definitions fleet-wide** (one canonical definition per layout, in the canonical
   type files, hex offset comments, VARIANT camps named apart), 0 dead names, 0 definitions outside the canonical files, every converted site a
   field of its type, controls green.
2. **Casts:** `type_census --check` → **0 raw cast sites** in all four forms; reinterpret sites counted apart by macro; the player block and the
   first-parameter entity type are structs in `src/`; the counts published in the readability series with the dated snapshot (R75).
3. **Declarations:** **0 lying declarations**; K&R sites counted apart, each marked with its bytes' cause; one canonical prototype per
   definition; the 51 TU-CONFLICT rows resolved (the ledger rows deleted with the bytes that resolved them); the 24 parked P36 classes landed;
   classes E/F/G at 0.
4. **Levers:** `lever_census --check --strict` → **0 pins, 0 asm statements outside the GTE header, 0 per-TU asm macro definitions**; every
   removal attributed `(P37 …)` in the ledger; `verbatim_check --strict` unchanged (the 1998 routines untouched).
5. `make clean && make extract-all JOBS=16 && make check-all JOBS=16` → `check-all: 218 passed, 0 failed of 218` (R22); `make tools-health`
   OK with the new rung; `ghidra_rebuild --proof` PASS with the types; the record (T9), this PhaseEnd, the DIGEST append, the log archived; v2.3.0.

## Rules at gate 1 (P10) — Drew accepts, modifies or rejects (ratified by the plan approval unless vetoed)

PhaseEnd_Phase36's candidates (a)–(k), operated through P36, proposed as **R107–R117**: (a) ban the silence, not the lever — a lever is
allowed only marked, ledgered and published from the first bank, with a one-compile bank-time trial without it; (b) a generator ships with
a negative-control corpus and a regen pass reports its refusal reasons as a histogram; (c) at every landing run every registered family on
the agent's START text before banking; (d) a scorer's target is the tree's own bytes compiled by the build's own tail, never a disassembly —
a known-true case before any campaign; (e) scratch is keyed by the unit of work, never by a worker tag or a file; (f) a gate's baseline is a
snapshot, not the build directory; (g) a lever's marker names its PASS and its INSTRUMENT, asserted by an attribution check at the close;
(h) a ledger's "done" is per body (unit, function, after-hash), never by text alone; (i) a long unattended run is DETACHED with a progress
log, never a harness background task; (j) a marked ordinary-C fake is counted apart from levers and never an orphan; an invented condition,
dead store or dummy reassignment is never banked; (k) a "stalling?" question is answered with the residue bucketed by what each bucket needs
before any plan is proposed.

## Effort / sessions / budget (R41)

Effort per task (R7): **Max** for T2, T3's design, T5's head-type layouts, T10; **xHigh** for T0, T1, T3's finish, T4, T6, T8, T9; T7 per
owner decision 3 (agents at Drew's cap; the coordinator at Max; Ultracode never without his direct approval, R27 + the S98 rule). Max is
session-only — re-apply each session. Sessions: T0–T2 one; T3 one; T4 one (compute-bound cycles); T5 one; T6 one to two (a 400k-site
campaign at ~0.1 s per object is compute, not tokens — the header fan-out is the cost: ~3,900 objects ≈ 6 min per `engine_types.h` edit at
`-j16`, so header edits are batched); T8–T10 one. **Mechanical floor 6–7 sessions; T7 is open-ended by decision 1 (to zero)** — priced by T2
(X residue × measured tokens per close; P36 measured ≈3.5 M tokens per 56 classes at S105) and re-priced at every landing with denominators.
P36 was priced 3 + open-ended and took 9 sessions / 575 commits / ~15–20 M agent tokens; this population is larger (412k casts vs 53k
levers) but the mechanical fraction is expected higher (member spelling on a base with no fixed-symbol interplay is byte-neutral) — T2
measures it before T4 starts.

## Evidence and docs

`.run/P37/baseline/` (R22 + tools-health + calibration logs) · `census/` (json/txt, `parked.tsv`) · `probe/` (the three probe tables) ·
`restruct/` (ledger.jsonl, batch records, apply logs) · `decls/` (the per-TU declaration judgements) · `agents/` (packs, mechanism.md). Text
only, nothing ROM-derived (R74).

## Deferred by name (recorded, not owed this phase)

Meaning-names for functions, data, structs and fields (Phase 38 — names with evidence); the `_jr_` carve-split file layout regrouped by
system and clang-format (the formatting phase); the 3,801 cross-address classes' parameterized form and the 20 trampoline families (names
phase); the kit split; xsig v2; the 11 still-RESIDUE UNSTRIPPABLE packs (one-off instructions, multi-output/macro-carried launders) unless
the struct hypothesis closes them; a refusal-reason histogram for `delever_regen` and a "local vs global" column for `alloc_table` (built
only if T7 draws).

## Owner decisions at gate 1 (Drew, 2026-09-11, in order)

1. **Stop rule: grind to zero.** The phase does not close while any raw cast, lying declaration or lever remains; the agent lane runs until
   the counters are 0 regardless of token cost. (The three "zero" definitions above make it honest and reachable; Drew may amend, as at P36
   S104 — the plan follows his latest word.)
2. **Naming: placeholders + cited evidence.** Unknown-purpose types `Unkstruct_<addr>` (the address of a canonical instance where one exists —
   the player block `Unkstruct_80078E00`; else the exemplar function's address, sotn's `ET_<addr>` precedent), the SDK's name where the layout
   equals a PsyQ type; fields `unk<HEX>` with `/* 0xNN */` hex offset comments and `// size = 0x..`; a field is NAMED only where the record
   already cites evidence (`docs/memory-map.md` §3.4, `docs/actor-struct.md`), with the citation in the header comment. Every other name is
   Phase 38's.
3. **T7 runs as the P36 lane:** the Agent tool, one agent per TU batch, cheapest-residual-first, at a concurrency cap Drew sets and retunes; the
   harvest → toolify → `regen` gate between draws; it STARTS only on Drew's word in the session that runs it (the S98 rule); never an Ultracode
   wave without his direct approval (R27).
4. **The declaration layer is the full canonical layer:** one canonical prototype per definition, applied per TU where the object is unchanged
   (per-TU and byte-arbitrated — not the Phase-16 header forced on every TU); the 24 parked patches; the 51 TU-CONFLICT rows; classes E/F/G;
   the byte-proven K&R sites counted apart and marked.
