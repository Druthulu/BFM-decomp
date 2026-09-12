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
- ☑ **T1** (S106; the commit carrying this line) — `tools/type_census.py` + **the struct map** (added after T0 — Drew asked, Claude recommended,
  Drew approved "Yes — T1 delivers the map"; P5d): definitions with o32 layouts + duplicate classes +
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
- ☑ **T2** (S106; the commit carrying this line) — The probe: (i) struct spelling on ~150 bodies over the top bases (identical / differing / closing under S+A / residual
  by pass); (ii) the canonical prototype per TU on ~300 TUs (free / byte-changing / refused, causes) + the 24 parked patches as the known-true
  set; (iii) the definition fold on 20 TUs; seconds per object, objects per header edit. Prices T4–T7 with denominators (R41). Verify: the
  probe table in the log with its commands.
- ☑ **T3** (S107, Max; the commits `21d2ccc14`, `42a57f576` and the close commit carrying this line) — `tools/restruct.py` (rungs S/S2/S+A/X/R/D/L, the
  delever pattern, the ledger, inflight restore, selftest 48 + `--real` 53 incl. the known-true no-op and the negative controls), `tools/struct_layout.py`
  (the layout engine + the writer + the naming invariant), `delever_oracle`'s LINKED mode (+ the snapshot guard), the reinterpret macros in
  `include/common.h` (proven equal on cc1's assembly), `tools/restruct_cycle.sh` (detached, R115); the Plan agent's stress-test landed as the
  design (the S106 "T1 design" entry + the S107 design statement). **Verify:** `restruct --selftest: 48/48 OK` · `--selftest --real: 53/53 OK` ·
  `delever_oracle --calibrate main md_SC07_004 ov_SC04_011: 114/114 objects byte-identical untouched … positive control DIFFERS … OK` ·
  `--linked-control: OK` · **the batch on one overlay:** `restruct: batch t3d1 rung D — 27 files … 258 declaration units: 242 canonical / 0
  promoted / 6 K&R marked / 16 kept … final 27/27 identical · written 27 files` + the redraw `t3d2 … 8 K&R marked / 16 kept … final 26/26
  identical · written 5 files`, each followed by R22 **`check-all: 218 passed, 0 failed of 218`** (`r22_t3d1.log`, `r22_t3d2.log`; and
  `r22_t3c.log` after the `common.h` macros). Deviations from the brief, recorded in the log: a new base symbol goes into the binary's splat
  symbol file (R15), not a `-T` fragment; T4 canonicalises widths/arity — the typed signature is T6's per-callee S → T → D unit (pointer
  arithmetic scales).
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
  wiki, the Gen3 pages, the series rendered, tool-index + kit corpus, `doc_links --strict`, tools-health OK; **the post-100 % story** —
  `docs/story.md` §10 ("After 100 %") and `docs/retrospective.md` §7 brought to the phase's close, `tools/timeline.py`'s lower panel (the lever
  and readability series) regenerated (added 2026-09-12 on Drew's word; the per-session step is in the checkpoint procedure).
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
- **S106, after the checkpoint (Drew):** *"we are documenting our story about this post 100% work correct?"* → the record showed the story and the
  retrospective ended at Phase 33 and the timeline's axes read 100 % forever; recommended and approved (*"agreed. do it now and update checkpoint
  memory to do this at the end of each session"*): `docs/story.md` §10 "After 100 %" + `docs/retrospective.md` §7 written from the record (P35–P37
  so far), `tools/timeline.py` extended with the lever and readability series as a lower panel + two columns, the rule in the wiki conventions page,
  T9 amended, and **the checkpoint procedure gains a step: advance §10/§7 + regenerate the timeline at the end of EVERY session** (the memory
  `checkpoint-current-phase-before-pause` updated).
- **Gate 1, after T0 (Drew):** *"insted of our phase plan, should we analyze every single func, and group together all the funcs that need a
  struct that share, so we can build a final struct map of all needed structs?"* → Drew asked, he did not propose (*"i wasn't suggesting we do it. im not the expert you are. I was asking you"*); Claude's answer and
  recommendation: yes — not instead of the plan, it is T1's clustering made a first-class deliverable, and it lets T4's canonical prototypes carry the mapped parameter types in one pass (order: census → **map** →
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

- **S106 — T1 design (X1).** One walker per file in worker processes (the masking and the function spans from `share_census`, the
  cache/coverage pattern from `lever_census`) → definitions with o32 layouts (`Resolver`), six cast-site forms with base/offset/width/
  sign/access, the declaration records, the flow edges; the parent computes duplicate tiers, coverage, controls, global blocks and the
  struct map (union-find over evidence only). **The Plan agent's stress-test landed** (322k tokens; its design goes into T3's notes) and
  corrected four premises before the fleet run: (1) a whole-object oracle says DIFFERS on a correct global-block edit because the
  RELOCATION SPELLING changes (`D_80078EB4` → `g.hp`) while the linked bytes are identical — T3 needs a resolved-relocation mode
  (control: `md_SC07_004`'s `D_801F8870[1]`) and a committed linker fragment for every new base symbol; (2) function identity is never
  the bare name (6,415 names carry >1 body text) — the map keys a function by its body hash; (3) a sixth site form exists, `((T *)p)->f`
  (36,681 sites: a COMPONENT_REF already, the readability MEMBER regex counts it as a member — it is the rewrite's rung 1, not a finished
  member); (4) "one definition per layout" is too strong — `{s16 ×4}` carries 177 names, some genuinely different types (`Rect` vs
  `SVECTOR`): a duplicate is same layout AND (identical meaningful member names | an opaque copy block | flow evidence); layout twins
  without evidence are reported, not merged — **milestone item 1's "per layout" reads "per type" from here (a clarification for Drew,
  not a scope change)**. Also from the agent: caller bytes DO depend on a narrow prototype's widths in both directions (the return axis
  too: `extern u8 f(void)` makes the caller mask eagerly), and rung 1 (body-local `((Unk *)a0)->f`, no signature change, the same `/s`)
  decouples the byte question from the declaration question — rung 2 (the typed signature) follows the declaration solver.
- **S106 — T1 built.** `tools/type_census.py` (selftest 21/21 on a fixture with every form); five fleet runs to converge the map: run 1
  a mega-cluster of 297,668 sites (Steensgaard's classic over-merge through untyped conduit parameters) and A/C sites counted against a
  deref denominator (105 %); run 2 typed-use parameters + a width-conflict veto + nested bases → 173,025; run 3 the single-source rule
  for locals + declared-type seeding of `AT:` nodes → 166,789 (the entity type: max offset 0x24C = `actor-struct.md`'s record size);
  run 4 positive shared evidence required on inter-function edges (the callee's map structured ≥2 offsets, ≥1 offset in common) →
  two large types (107,598 sites / 0x10C spanning 9,753 pointer globals — the cross-address copies of per-overlay globals, still partly
  fused at low offsets; 65,397 sites / 0x24C with one instance global `D_80126B58`), their conflicts mostly same-width sign mixes (a
  store's signedness leaves no byte), now counted apart from width conflicts; run 5 = the final numbers. **The map is a model with
  stated rules and reported conflicts; T2 tests it on bytes, T5 refines it.**
- **S106 — T1 verify lines (HEAD `23fc5d215`, 3 m 20 s at -j16).** `type_census: 7261 definitions (525 layouts, 206 duplicate classes,
  39 variant camps) · 503016 cast sites in 69497 bodies over 8 base classes (4 forms + A, coverage OK) · 98648 lying declarations / 1609
  callees · controls 4/4` · `struct_map: 18760 types over 18760 clusters explain 498896/503016 sites (99.2 %); 4120 unassigned sites; 729
  types with conflicts`. DEFINITIONS: canonical header 1,179 · `.c` file-scope 4,091 · `.c` block-scope 1,904 · per-function shared headers
  63 · other headers 24; 3,109 distinct names; duplicate tiers: 122 same-named + 84 opaque classes (2,789 names), 46 layout-twin classes /
  1,844 names kept apart; 588 exact-text classes / 4,469 copies; 39 VARIANT names; 141 dead canonical names; 75 canonical names redefined
  in `.c`. CAST SITES: **deref 503,016 = P 409,007 + I 60,666 + X 13,800 + M 19,543** (+ A 18,912 address-of; + C 36,681 typed cast-member)
  in 69,497 bodies; coverage OK on all six forms; refused 0; the readability regex over raw text 411,850 (the 2,843 difference = casts
  inside comments/strings/macro blocks); by base: param 276,860 · local 149,915 · gaddr 40,122 · nested 24,076 · global 8,860 · other 1,678;
  by width: s4 145,167 · u2 142,775 · s2 131,818 · u1 43,174 · agg 13,472 · p4 12,016 · u4 11,165 · s1 3,429; top bases a0 92,255 ·
  param_1 81,595 · arg0 67,704 (the first parameter 241,554 = 48 %). DECLARATIONS: 99,130 definitions (1,889 K&R) · 4,279,365 extern
  function declarations over 12,139 names (3,870 spelled >1 way) · 6,415 names with >1 body text · 1,078,837 data externs over 55,569
  symbols (18,442 typed >1 way) · asm-label aliases 5,749 (225 names) · builtins memcpy 301 / abs 144 · attributes packed 64 / aligned 12 ·
  lying 98,648 / 1,609 callees (K&R-empty 91,357, narrow 7,291). GLOBAL BLOCKS: 2,123 runs of ≥4 adjacent scalar `D_` symbols (14,251
  symbols). PARKED (P36): **24 classes / 453 bodies / 691 needed sites → `.run/P37/census/parked.tsv`**, needs {signature 13, struct 7,
  ? 4}; 22 PARK names are minimum-lever banks. CONTROLS 4/4 (the doc dispute reported: `D_80078F08/0C` code 4 vs `actor-struct.md` 2 —
  a T9 correction; the bytes side with the code). `lever_census`: controls re-keyed (14 / 8 / `func_801896EC` 2, each counted
  independently) → 4/4 OK; `--check: 4,010 … 0 UNMARKED — OK`; **`--check --strict: pins 2141, asm 1419, gte-levers 450, direct GTE
  statements in bodies 6717, per-TU asm macro definitions 314 … FAIL`** — `--strict` now reads its own words: a direct GTE coprocessor
  statement in a body is an asm statement outside the GTE header (the P36 close excluded 6,447 `gte` + 270 `gte-unsigned` as Sony's
  idiom; under decision 1 they are work — macro calls from the one header; `func_8013D9B0`'s 268 are among them, resolved this way).
  Published (R75): `progress.py --json --readme` → `counts.types` + the README "Types (Phase 37, snapshot 2026-09-12)" sentence + two
  dated `corrections` (the four-form count; `--strict`'s direct GTE statements); `progress.py --check` fresh; `readability_progress
  --snapshot` (the TSV now read by column NAME; 16 census columns appended) → `503016 by the census's four forms (+36681 typed
  cast-member, +18912 address-of) … 7261 struct definitions over 525 layouts (206 duplicate classes / 2789 names); the map: 18760 types
  (99.2 % of sites)`; `lever_progress --snapshot` (79 milestones, 4,010 unchanged) → `--check OK`; `docs/struct-map.md` generated (200
  types) + its Reference-index row; dictionary row + SETUP §P37 S106 (R87/R21); `make kit-corpus` → `tool_census --check: OK`;
  `doc_links --strict: OK`; `kit_lint: OK`; `kit_coverage: OK`. Files: `.run/P37/census/{type_census.json,type_census.txt,struct_map_top.json,
  parked.tsv}` tracked; `struct_map.json` (6.4 MB) and `sites.jsonl` (213 MB) regenerable, ignored.

- **S106 — T2 the probe (Max).** Harness: `tools/restruct.py` — the rewrite engine's first form (`--try` rung 1 on one body, `--probe`,
  `--probe-decls`, `--probe-defs`, `--audit-layouts`, `--fanout-cost`; SETUP §P37 S106, dictionary row). Every judgement through
  `delever_oracle` in place and restored (R102); header bodies on every includer; the residual classified by `delever_search.classify`.
  **Five probes, every number with its denominator (R41):**
  1. **Struct spelling (rung 1) — 165 bodies, stratified (A entity/0x24C 40, B pointer-globals 25, C matrix/vector-shaped 25, D record
     tables 25, E shared headers 20, F other multi-body 20, G single-body 10; half lever-bearing where available), seed 37, 385 s wall at
     -j12, `.run/P37/probe/probe_table.md` + `probe_rows.jsonl`:** 139 judged (23 had no convertible site on the base, 3 compile errors —
     one shape: a pointer field typed `void *` because the sites' pointees disagree, then indexed; the rewrite now skips those sites) →
     **IDENTICAL 126 (90.6 %), DIFFERS 13; 716 sites moved**. The DIFFERS were all COUNT/ORDER residuals = the `/s` alias asymmetry:
     after rung 1 the struct stores carry MEM_IN_STRUCT_P and the body's bare fixed globals do not, so `sched.c:837`'s escape hoists a
     fixed load over a struct store the original kept below it — read on the bytes of `func_801814AC` (ov_SC05_010): every `D_801C7E30`
     site a member except the store at +0x34 → IDENTICAL; that one store a member → the pointer reload hoists; the pointer global itself
     spelled as a struct member fixes that store and moves a constant elsewhere (§351: the `/s` flag is a dial per ACCESS). **Rung S2** (the
     minimal set of sites kept as casts — leave-one-out, then cumulative revert with minimisation, delever's rung-B shape) **closes 13/13
     DIFFERS keeping 27 casts → 139/139 judged bodies byte-identical with members everywhere but 27 of 716 sites (3.8 %)**; C (matrix/
     vector) keeps the most (20 casts over 7 bodies). Skipped by the rewrite, counted: 226 of 942 candidate sites (24 %): no-field 133
     (the cluster layout has no field at that offset — overlaps/misalignment), sign 44 (a load whose sign differs from the field's), width
     33 (a union/LOH shape), index 13, negative offset 3 — T5's type-authoring residue. S+A (struct + levers off) closed 0 of the 5 DIFFERS
     bodies with levers — the struct hypothesis is unmeasured at this sample size; T6's S+A rung on all 1,980 lever-bearing bodies measures
     it. Cost: mean 2.0 s per body judgement (max 45 s: a header on 141 includers); S2 ≤ 2n+1 compiles on ~10 % of bodies.
  2. **Declarations — 4,828 (TU, callee) judgements (ov 4,666, md 80, main 41, shared headers 41) over the argcheck rows of 300 TUs,
     941 s wall, `decl_table.md` + `decl_rows.jsonl`:** the definition's ANSI signature written into the callee's lying declarations →
     **IDENTICAL 4,473 (92.6 %), DIFFERS 0, COMPILE-ERROR 355**: arity contradictions 136 (`too few/many arguments` — the byte-proven
     K&R sites), conflicting declarations elsewhere in the TU 121 (the repair must replace EVERY declaration of the callee in the TU, not
     only the lying ones), 98 whose message the cause reader did not classify (main's `At top level:` 22, a `#define NULL` context line 14
     — T3's solver reads the full message, R103). Zero DIFFERS: the caller-side width conversion the Plan agent warned of did not appear
     in this sample — either the narrow parameters already carry the right widths or their callers pass narrow values.
  3. **Definitions — 20 overlay TUs (the 60 with the most file-scope definitions, shuffled), 365 folds, `defs_rows.jsonl`:** a duplicate
     of a canonical type (same layout, tier 1/2) replaced by `typedef <Canon> <Local>;` → **IDENTICAL 12 TUs, COMPILE-ERROR 8** (`structure
     has no member named a/f0/v`: an opaque-tier fold changes the member NAMES, so the TU's accesses must be renamed with it — T5's engine
     rewrites members, not only the definition; the tier-1 folds are free).
  4. **The layout engine vs cc1 — 5,283 file-scope definitions / 29,248 named fields asserted (`sizeof` + every named field's offset by
     the negative-array-size idiom, the TU's real include environment in source order): rejected 0, unresolved 0** (`layout_audit.json`).
     Reached through three probe defects (R40: the environment lacked the canonical header; typedefs emitted out of order; block-scope
     typedefs hoisted) and two REAL engine gaps it found: `__attribute__((aligned(4)))`'s nested parens broke the attribute regex and
     dropped the field (`MZ` in md_MAIN_027), and per-field `aligned(N)` was ignored — both fixed in `type_census.py`; plus a census
     over-count: 27 `#ifndef BFM_ENGINE_TYPES_H` standalone blocks in 21 TUs (inert in a TU that includes the canonical header) now
     blanked — definitions 7,261 → 7,255, layouts 525 → 527, variants 39 → 40 after the re-run.
  5. **The oracle — the relocation-spelling control (f3's `D_801F8870[3]` array walked through a pointer, md_SC07_004 `func_801A4258`):
     whole-object DIFFERS, `make build BINARY=md_SC07_004` with the candidate in place → `sha1 87ac0de3… == config/check.md_SC07_004.sha
     (BYTE-IDENTICAL)`** — T3's linked-relocation mode is required for the global-block class. **Fan-out cost: `engine_types.h` reaches
     3,818 TUs / 3,975 objects; one typedef appended → 3,949 IDENTICAL in 35 s wall at -j16 (0.141 s/object)**, 26 transient
     COMPILE-ERRORs that vanished on re-run (a fan-out judgement retries a failure once before believing it, R40).
  **Pricing (R41):** T4 declarations ≈ 94k (TU, callee) pairs × 0.15–0.8 s ≈ 1 session unattended (≈93 % mechanical; ~6.6k pairs to the
  solver: ~2.9 % K&R sites, ~2.5 % multi-spelling, ~2 % unread causes). T5 unification: 5,995 in-`.c` definitions, ~60 % by alias alone,
  the rest with member renames; canonical-header batches of dozens per 35-s fan-out ≈ 1 session. T6 casts: 69,497 bodies × 2 s ≈ 2.4 h
  compute for rung 1 + S2 on ~10 % (≈3 h) + R22 per batch → 1–2 sessions unattended; expected floor after S2 ≈ 4 % of converted sites
  kept as casts (≈20k sites) plus the 24 % the current types cannot hold (≈120k sites) — T5's types decide most of those. T7: the
  per-access `/s` residue (the kept casts) and the lever bodies — open-ended by decision 1; the S+A measurement comes with T6's first
  batches. **Rewrite table fixed by the probe:** misaligned layout entries skipped; pointer fields need the site's pointee; sign-mismatch
  loads stay casts; the typedef inserted at file scope before the function; S2 before any agent.
- **S106 — T2 verify.** `restruct --audit-layouts: 5283 file-scope definitions (29248 named fields) asserted against cc1; rejected 0;
  unresolved layouts 0` · `restruct --fanout-cost: … 3818 TUs / 3975 objects … wall 35 s at -j16 (cpu 560 s, 0.141 s/object)` · the
  probe tables above · the census re-run `type_census: 7255 definitions (527 layouts, 206 duplicate classes, 40 variant camps) · 503016
  cast sites … coverage OK … controls 4/4`; `readability_progress --snapshot` (a T2 row) + `progress.py --check` fresh.

- **S107 2026-09-12 — T3 in progress (Max design, the first bank).** Design stated (X1) and built: **`tools/struct_layout.py`** (the o32 layout
  engine factored out of `type_census.py` — `Resolver`, `parse_struct_body`, `layout_hash`, `field_offsets`; new: `field_map`, `leaf_at`, the WRITER
  `render_struct`/`entries_from_layout` in the final style — `/* 0xNN */` comments, `unk<HEX>` for accessed-unknown, `u8 pad<HEX>[n]` for
  never-touched gaps, `// size = 0x..` — and the INVARIANT `audit_definition`: every `unk/pad<HEX>` at offset HEX, every comment = the computed
  offset, the trailer = sizeof; selftest 9/9; `type_census.py` imports it — its selftest 21/21 unchanged; `walk_all()` factored out of
  `run_census` for the engine). **`tools/delever_oracle.py`** gained the LINKED MODE: `link_vars` (the Makefile's own link variables per binary,
  asked of make), `snapshot_links` (every binary's `.ld` + `undefined_*_auto.txt` + main's 11 `build/psyq/*_externals.ld` into the snapshot's
  `_link/`, `links.json`), **`judge_linked`** (the candidate object linked by the build's own `ld/objcopy/trim` against the snapshot's other objects,
  SHA1 vs `config/check.<alias>.sha` — ~10 ms), `reloc_only_diff` (the cheap pre-check: `.text` words equal under the mask, only relocation operands
  differ), `--linked-control` (the f3 body `func_801A4258`: **`p[1]/p[2]` whole-object DIFFERS · reloc-only True · linked IDENTICAL ✓; the negative
  `p[2]/p[3]` linked DIFFERS ✓**) — and a GUARD on `--snapshot-baseline`: a changed object must reproduce from an untouched compile or the refresh is
  REFUSED. **The guard was needed the same hour:** the first control read `whole-object IDENTICAL` for the `p[1]` spelling because
  `build/src/md_SC07_004/md_SC07_004.o` was NOT the tree's object — T2's relocation control had run `make build BINARY=md_SC07_004` with the
  candidate in place (linked-identical, differently spelled relocs) and my refresh copied it into the snapshot (R56/R112). Fixed by the clean fleet
  run (`.run/P37/baseline/r22_t3a.log`: `check-all: 218 passed, 0 failed of 218`, exit 0), a re-snapshot (`1 changed since the previous snapshot`) and
  `--calibrate main md_SC07_004 ov_SC02_005 ov_SC04_011` → `147/147 … positive control DIFFERS … OK`. **`tools/restruct.py`** (2,900 lines; the T2
  functions kept verbatim): the judge on a multi-file job (`judge_files`: whole-object, then linked when reloc-flagged or reloc-only), the ledger
  `.run/P37/restruct/ledger.jsonl` keyed (rung, tu, unit, hash) with `--restore` from `inflight.json`, the shared ladder (all units at once, else
  cumulative greedy — delever's rung-B shape), **rung S** on every typed base with the declared-type-aware spelling (`a1->unk4` / `D_x.unk4` / the cast
  form), **S2** (greedy kept casts), **S+A** (delever's ladder on the struct-spelled text, `(P37 S+A …)` markers via `delever.marker_edits(phase=)`, stale
  `_m` markers scrubbed), **X** (`pass_hint`: SCHED-ALIAS / CSE-KILL / WIDTH / ADDRESS-FOLD / ALIGNMENT / REGALLOC / OTHER), **R** (the registry: R1 the
  pointer global as a struct member (§458), R2 `extern T X[]` (a18), R3 the walked pointer (f3, reloc-flagged)), **D** (every declaration of a callee →
  the definition's ANSI signature > the width-promoted form > all-`()` + `// K&R: n of m args (P37 rung D <label>)`; the definitions index keyed by the
  TU's visible files — own TU, its binary's dir, its headers, then main/resident — REFUSING when two definitions disagree; `--callee/--signature` for a
  definition-side change judged on every declaring TU), **L** (folds with member renames by the offset map, REFUSED on an ambiguous member name),
  `--write-types` (the writer's preview from the struct map), `--audit-types`, `--check-ledger`, `--try-file` (a real-oracle dry run, nothing written),
  `--redraw`. **Selftest 48/48 (a stub oracle; every form, the no-op, S2's two paths, D's three verdicts, L, the three recipes, the ledger, the
  inflight parser, negative controls) · `--real` 51/51** (calibration current; the tree's own text IDENTICAL; a nop DIFFERS; the linked control).
  **Known-true on the bytes:** `--try … func_801814AC --base global:D_801C7E30 --recipes` → `DIFFERS · S2 IDENTICAL kept 1 (+0x34, 1 compile) ·
  R1-ptr-global-member IDENTICAL (adopt)` — §458's body closes mechanically; `--try-file … func_8017E830` → **S IDENTICAL (2 members) · S+A LEVER-FREE:
  6 `gte_rtv0tr_m` levers off, markers scrubbed, re-judged IDENTICAL, nothing written** (the T2 row says levers-off-alone was IDENTICAL too — a P36
  `_m` leftover, not the struct hypothesis; the path is proven either way). **The end-to-end batch — rung D on ov_SC04_011 (`--apply --rung D
  --batch 27 --only ov_SC04_011 --label t3d1 -j 12`):** `restruct: batch t3d1 rung D — 27 files (TUs; 27 drawable) · 258 declaration units: 242
  canonical / 0 promoted / 6 K&R marked / 16 kept · compiles 223 in 31 s wall · final 27/27 identical · written 27 files` → R22
  (`.run/P37/baseline/r22_t3d1.log`) **`check-all: 218 passed, 0 failed of 218`** (108 s, exit 0). The kept causes, read: `func_800D20C0` ×7 = the
  prototype names `Pos800D20C0`, a type the overlay TU cannot see (T5's canonical file closes it); `too few arguments` = the K&R sites (marked);
  `func_8016BF50` = a mix of `()` and truncated ANSI declarations (the all-`()` candidate added after this run). Three instrument findings on the
  way, each fixed at its cause: the fleet walk (a process pool) forked from inside the worker threads and deadlocked the first run at 0 % CPU
  (now computed before any thread exists); 1,889 K&R definitions re-masked per TU (now one mask per file); the selftest's inflight probe used the
  LIVE `inflight.json` and deleted batch t3d1's snapshot (now a scratch path — the batch's files were already proven by R22, so nothing was lost).
  `.gitignore`: the argcheck cache excluded. This commit = the bank (R42): the 27 TUs, the tools, the evidence.

- **S107 — T3 batch `t3d2` (the redraw of the 16 kept units, `--redraw DECL-KEPT`, after the cause reader learned cpp's context lines and
  the all-`()` arity candidate):** `restruct: batch t3d2 rung D — 26 files … 16 declaration units: 0 canonical / 0 promoted / 8 K&R marked / 16
  kept · compiles 27 in 5 s wall · final 26/26 identical · written 5 files` (two more K&R sites closed by the all-`()` form; the causes now read
  `conflicting types for func_800D2318 … prev: shared/ov/func_80168BDC.h:3` — a per-function shared header carries the lying spelling, rung D's
  `--headers` mode — and `parse error before '*'` = the prototype names a type the TU cannot see, T5's). R22 (`.run/P37/baseline/r22_t3d2.log`)
  **`check-all: 218 passed, 0 failed of 218`** (110 s, exit 0). Fixed after the run: a K&R-marked unit (every declaration `()` + the marker) is
  settled and no longer drawn by a redraw (t3d2 re-labelled three already-marked units — comment churn only, byte-neutral).

- **S107 — T3 closed.** After the two D batches: **`tools/restruct_cycle.sh`** (the detached cycle: clean tree → guarded snapshot refresh +
  calibration when stale → `--apply` read by exit code and `final X/X identical` → R22 → `type_census --sites` + the readability snapshot →
  the log entry + 🛑 headline → one commit; `bash -n` OK); **`include/common.h`**: `LOBU/LOH/HIH/LOHU/HIHU/LOW/LOWU` (sotn's shape) + the
  `M2C_FIELD` note corrected (the "identical codegen" claim owed at T9 — done now, same edit); the macro proof `restruct.macro_probe` (cc1's
  assembly for the macros == the bare casts, 7 loads) in `--selftest --real`; R22 after the header edit (`r22_t3c.log`) `check-all: 218 passed,
  0 failed of 218` (104 s, exit 0). **The writer's preview** (`--write-types --top 6` → `.run/P37/restruct/types_preview/ov.h`):
  `Unkstruct_800B5CB8: 90 fields, size 0x10c · skipped {'overlap': 44}` · `Unkstruct_80126B58: 146 fields, size 0x24c · skipped {'overlap': 28,
  'misaligned': 1}` · four more clean — the overlaps are the map's width conflicts (T5 decides union vs split). **`--audit-types` on the legacy
  header: 26 violations, every one a legacy `pad<SIZE>` name** (T5's rename list) — after two instrument corrections (a TRAILING legacy comment
  was paired with the next field: 1,013 false flags; a multi-declarator line's comment names its FIRST declarator). `--check-ledger: 0 MEMBER
  sites … 0 violation(s)` (no S bank yet). Rows: `config/tool_dictionary.tsv` (restruct updated; struct_layout, restruct_cycle added), SETUP
  **§P37 S107**, `make kit-corpus` → `tool_census --check: OK`, `doc_links --strict: OK`, `cookbook-index OK`; the record: decision log
  **P37 S107** (R31), accelerators **P37 S107** (five), cookbook **§458 addendum** (the engine reproduces and closes the exemplar: S2 keeps 1,
  R1 IDENTICAL). **Found on the way, for Drew:** `tools/audit_public.py` is RED on HEAD — `.run/P36/delever/ledger.jsonl` is tracked at
  78,396,681 bytes (> 50 MiB, GitHub's warning cap), since the P36 S105 commit `31cf8695f`; the public CI's no-rom job has been red since
  that push. Not touched (P36's evidence; a decision): recommendation below the checkpoint. Also: 19,343 stale scratch files under
  `.run/P36/delever/obj/` (ignored; hygiene, not correctness).

- **S107 — Drew's decision on the red `no-rom` CI (the P36 ledger's size):** *"did we accidentally push rom info? or is that just a file >50
  failing our test? if so, just relax the size gate to 100MB per github limit"* → evidence shown: `audit_public`'s checks 1 (purge paths), 2
  (1,422 ROM-derived SHA1s vs 15,203 tracked files) and 4 (disassembly-shaped runs; longest 14 lines, cap 64) all CLEAN — only check 3 (SIZE)
  fired; the ledger is 29,649 rows of our own tool's verdicts on our own C (0 eight-hex-digit words outside the hash fields). **No ROM content
  was pushed.** The gate raised to GitHub's HARD limit: `tools/audit_public.py` `SIZE_CAP = 100 MiB` (+ a `WARN` above 80 MiB, so a file
  approaching the limit is announced before a push can be rejected — R54), the docstring, `.github/workflows/no-rom.yml`, SETUP's row,
  `docs/wiki/The-ROM-firewall.md` and `docs/wiki/Verification-and-progress.md` (the wiki's live copy needs Drew's sync). `audit_public: OK — 0
  offenders among 15219 tracked paths`. (The ledger is 74.8 MiB today; P36's rows are frozen — only P37's S+A rows are appended to it.)

- **2026-09-12 — T4 batch `t4_D1`** (`.run/P37/restruct/run_t4_D1.log`, `batch_t4_D1.json`): `restruct: batch t4_D1 rung D — 40 files (TUs; 3878 drawable) · 1441 declaration units: 1261 canonical / 0 promoted / 29 K&R marked / 60 aliases typed / 0 __builtin_abs → abs / 120 kept · compiles 1554 in 70 s wall · final 40/40 identical · written 40 files` → R22 (`.run/P37/baseline/r22_t4_D1.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=80.19 s`) → census `(census skipped)`.

- **2026-09-12 — T4 batch `t4_D2`** (`.run/P37/restruct/run_t4_D2.log`, `batch_t4_D2.json`): `restruct: batch t4_D2 rung D — 300 files (TUs; 3878 drawable) · 4995 declaration units: 4354 canonical / 1 promoted / 85 K&R marked / 84 aliases typed / 7 __builtin_abs → abs / 469 kept · compiles 5836 in 196 s wall · final 300/300 identical · written 264 files` → R22 (`.run/P37/baseline/r22_t4_D2.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=80.17 s`) → census `(census skipped)`.

- **2026-09-12 — T4 batch `t4_D3`** (`.run/P37/restruct/run_t4_D3.log`, `batch_t4_D3.json`): `restruct: batch t4_D3 rung D — 300 files (TUs; 3878 drawable) · 3441 declaration units: 2948 canonical / 0 promoted / 24 K&R marked / 61 aliases typed / 3 __builtin_abs → abs / 261 kept · compiles 3981 in 100 s wall · final 300/300 identical · written 220 files` → R22 (`.run/P37/baseline/r22_t4_D3.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=80.46 s`) → census `(census skipped)`.

- **2026-09-12 — T4 batch `t4_D4`** (`.run/P37/restruct/run_t4_D4.log`, `batch_t4_D4.json`): `restruct: batch t4_D4 rung D — 300 files (TUs; 3878 drawable) · 2941 declaration units: 2549 canonical / 0 promoted / 0 K&R marked / 0 aliases typed / 0 __builtin_abs → abs / 213 kept · compiles 3277 in 92 s wall · final 300/300 identical · written 214 files` → R22 (`.run/P37/baseline/r22_t4_D4.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=82.75 s`) → census `(census skipped)`.

- **2026-09-12 — T4 batch `t4_D5`** (`.run/P37/restruct/run_t4_D5.log`, `batch_t4_D5.json`): `restruct: batch t4_D5 rung D — 300 files (TUs; 3878 drawable) · 2618 declaration units: 2213 canonical / 0 promoted / 2 K&R marked / 0 aliases typed / 0 __builtin_abs → abs / 189 kept · compiles 2851 in 76 s wall · final 300/300 identical · written 187 files` → R22 (`.run/P37/baseline/r22_t4_D5.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=80.94 s`) → census `(census skipped)`.

- **2026-09-12 — T4 batch `t4_D6`** (`.run/P37/restruct/run_t4_D6.log`, `batch_t4_D6.json`): `restruct: batch t4_D6 rung D — 300 files (TUs; 3878 drawable) · 2086 declaration units: 1670 canonical / 0 promoted / 2 K&R marked / 0 aliases typed / 0 __builtin_abs → abs / 159 kept · compiles 2215 in 73 s wall · final 300/300 identical · written 152 files` → R22 (`.run/P37/baseline/r22_t4_D6.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=83.38 s`) → census `(census skipped)`.

- **2026-09-12 — T4 batch `t4_D7`** (`.run/P37/restruct/run_t4_D7.log`, `batch_t4_D7.json`): `restruct: batch t4_D7 rung D — 300 files (TUs; 3878 drawable) · 1566 declaration units: 1084 canonical / 0 promoted / 108 K&R marked / 0 aliases typed / 0 __builtin_abs → abs / 160 kept · compiles 1564 in 76 s wall · final 300/300 identical · written 103 files` → R22 (`.run/P37/baseline/r22_t4_D7.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=92.91 s`) → census `(census skipped)`.

- **2026-09-12 — T4 batch `t4_D8`** (`.run/P37/restruct/run_t4_D8.log`, `batch_t4_D8.json`): `restruct: batch t4_D8 rung D — 300 files (TUs; 3878 drawable) · 1268 declaration units: 767 canonical / 0 promoted / 140 K&R marked / 0 aliases typed / 0 __builtin_abs → abs / 140 kept · compiles 1149 in 66 s wall · final 300/300 identical · written 70 files` → R22 (`.run/P37/baseline/r22_t4_D8.log`) **`check-all: 218 passed, 0 failed of 218`** (`wall=83.95 s`) → census `(census skipped)`.

## 🛑 SESSION CHECKPOINT — S107 (2026-09-12, FINAL — written for a FRESH session; the session's last commit follows this): gate 1 APPROVED, **T0 ☑ T1 ☑ T2 ☑ T3 ☑** (baseline · the census + map · the probe · THE ENGINE) — 🛑 **T4 NEXT (the declaration layer over the fleet by symbol space — rung D in unattended cycles; xHigh) — and FIRST the P6 rules check (four tasks complete)** | R22 `check-all: 218 passed, 0 failed of 218` at `42a57f576`+`common.h` (`r22_t3c.log`; the close commit adds no build input) | HEAD after this commit is the checkpoint's commit; tree clean; nothing pushed after `79b2f6f15` (6 commits ahead: `0a55cb0fd` … this one — Drew pushes, R6) | last batch `t4_D8` on 4eeb4412f: 300 files (TUs; 3878 drawable) · 1268 declaration units: 767 canonical / 0 promoted / 140 K&R marked / 0 aliases typed / 0 __builtin_abs → abs / 140 kept · comp

**Replay this block into the chat at the next session start (R64); it is the ONLY in-phase context the next session inherits. Everything below
is what S107 knew and the next session must not re-derive.** **The checkpoint procedure (every session end, Drew 2026-09-12):** bank the
record (cookbook / decision log / accelerators / SETUP / stale assertions), **advance the post-100 % story — `docs/story.md` §10 and
`docs/retrospective.md` §7 from the session's decision-log entry — and regenerate `tools/timeline.py`** (its lower panel draws the lever and
readability series), then rewrite this block, commit, recap (R18).

1. **Where we are.** Phase 37 (the structs phase) opened 2026-09-11 (S106, plan mode, Max). Drew's four gate-1 decisions: **grind to zero** on raw
   casts, lying declarations and levers (each "zero" defined in the plan's §"What zero means"); **placeholders + cited evidence** (`Unkstruct_<addr>`,
   `unk<HEX>`, `/* 0xNN */`, `// size = 0x..`); **T7 = the P36 agent lane** at his cap, started only on his word, never an Ultracode wave without direct
   approval; **the full canonical declaration layer**. The struct map is T1's deliverable; no tags/releases at closes. R107–R117 ratified. S107
   (this session, Max) built **T3 — the engine** in one session with no agents: `tools/struct_layout.py`, `tools/restruct.py`'s full form,
   `delever_oracle`'s LINKED mode + the snapshot guard, `include/common.h`'s reinterpret macros, `tools/restruct_cycle.sh`; two rung-D batches on
   ov_SC04_011 banked (258 declaration units: 242 canonical, 8 K&R sites marked, 16 kept with legible causes), R22 218/218 three times. **Two
   deviations from the T3 brief, recorded:** a new base symbol goes into the binary's splat symbol file (R15: one curated source; splat feeds the
   link), not a `-T` fragment; and T4 canonicalises WIDTHS/ARITY only — the typed signature (`Unkstruct_X *a0`) is T6's per-callee unit S → T → D,
   because a parameter cannot be typed while its body still adds offsets to it (pointer arithmetic scales). **A session-start owed check: the P6
   rules check** (T0–T3 = four tasks) — re-read CLAUDE.md's rules and PROJECT_CONTEXT.md's, state "Rules check — re-read complete. Continuing with
   T4." Commits this session: `21d2ccc14` (T3 bank 1: the tools + batch t3d1), `42a57f576` (batch t3d2), then this checkpoint's commit (the T3
   close: cycle script, macros, the record). **Resolved S107 (Drew):** the red `no-rom` CI was the SIZE check alone — `.run/P36/delever/ledger.jsonl` (74.8 MiB, our own tool's rows, no ROM content; checks 1/2/4 clean) — and the gate is now GitHub's 100 MiB hard limit (`SIZE_CAP`, a WARN above 80 MiB); `audit_public: OK`. The two edited wiki pages await Drew's wiki sync. Also 19,343 stale scratch files under the ignored `.run/P36/delever/obj/` (hygiene).

2. **The counters (T1, `tools/type_census.py`, coverage OK, controls 4/4; every verify line in the T1/T2 log entries).**
   Raw dereferences **503,016** = P `*(T *)(…)` 409,007 + I `*(T *)ident|&D_|0x80…` 60,666 + X `((T *)e)[i]` 13,800 + M `M2C_FIELD` 19,543,
   in 69,497 bodies (+18,912 A address-of casts and +36,681 C `((T *)p)->f` typed cast-member accesses, counted apart — C is rung 1's own
   form, already a COMPONENT_REF); by base: param 276,860 · local 149,915 · `&D_` 40,122 · nested 24,076 · `D_` by value 8,860 · other 1,678;
   the first parameter (`a0`/`param_1`/`arg0`) 241,554 = 48 %. Definitions **7,255** (canonical header 1,179 · `.c` file-scope 4,085 ·
   `.c` block-scope 1,904 · per-function shared headers 63 · other headers 24) over **527 layouts**; 206 duplicate classes / 2,789 names
   (tier 1 same-named 122, tier 2 opaque 84; **46 layout-twin classes / 1,844 names are NOT duplicates without flow evidence** — milestone
   item 1 reads "one definition per TYPE"); 40 VARIANT names; 141 dead canonical names; 75 canonical names redefined in `.c`.
   Declarations: 99,130 definitions (1,889 K&R); 4,279,365 extern function declarations over 12,139 names (3,870 spelled >1 way);
   **6,415 names carry >1 body text** (identity = body hash `F:<nhash>` / shared header `H:<path>` / external `X:<space>:<name>`, never the
   name); 1,078,837 data externs over 55,569 symbols (18,442 typed >1 way); asm-label aliases 5,749 (225 names); builtins memcpy 301 / abs
   144; attributes packed 64 / aligned 12; **lying declarations 98,648 over 1,609 callees** (K&R-empty 91,357, narrow 7,291).
   **Levers (`lever_census --check --strict`, made literal at T1): 4,010 marked (2,141 pins + 1,869 asm) + 6,717 direct GTE asm statements
   in bodies (kinds `gte`/`gte-unsigned`, incl. func_8013D9B0's 268) + 314 per-TU asm macro definitions** — the `--check` headline (4,010)
   keeps the P36 definition for the series. Global blocks: 2,123 runs of ≥4 adjacent scalar `D_` symbols (14,251 symbols). The 24 parked
   P36 classes with reasons: `.run/P37/census/parked.tsv` (453 bodies / 691 sites; needs: signature 13, struct 7, ? 4).
   **The struct map** (`.run/P37/census/struct_map_top.json` tracked; `struct_map.json` 6.4 MB and `body_base_type.json` 11 MB ignored,
   regenerable): 18,760 types explain 99.2 % of the deref sites; the two largest are `Unkstruct_800B5CB8` (107,598 sites / 0x10C over 9,753
   pointer globals — partly fused at low offsets) and `Unkstruct_80126B58` (65,397 sites / 0x24C, one instance global — the actor record of
   `docs/actor-struct.md`); merge rules in SETUP §P37 S106 (typed-use parameters; positive shared evidence ≥1 offset with the callee's map
   ≥2 offsets; single-source locals; a width-conflict veto; `AT:`/`PTR:` global nodes seeded by the declared type; FLD nodes for pointer
   fields). It is a MODEL: T2 tested it on bytes (below); T5 authors from it after T3's engine can judge every type per body.

3. **What T2 proved on the bytes (the design inputs for T3; the full tables are the T2 log entry and `.run/P37/probe/*.md`).**
   (a) **Rung 1** (body-local `((P37S_<hash> *)base)->unk<HEX>` with the type from the cluster layout; misaligned layout entries skipped;
   pointer fields only where the site's pointee equals the field's; sign-mismatch loads stay casts; the typedef inserted at file scope before
   the function) is byte-neutral on **126/139 judged bodies (90.6 %), 716 sites moved**; 226 of 942 candidate sites (24 %) were skipped
   because the cluster layout cannot hold them (no-field 133, sign 44, width 33, index 13, negative 3) — T5's type-authoring residue.
   (b) **The 13 DIFFERS are the `/s` asymmetry** (COUNT/ORDER residuals, never REG): a converted store carries `MEM_IN_STRUCT_P`, the body's
   bare fixed globals do not, `sched.c:837`'s escape hoists a fixed load over it. Byte-read on `func_801814AC` (ov_SC05_010 :3030): five
   `D_801C7E30` sites as members + the `+0x34` store as a cast → IDENTICAL; the pointer global itself as a member fixes that store and moves a
   `li v0,10` elsewhere. **The `/s` flag is a per-ACCESS dial** (cookbook §458, §351). (c) **Rung S2** (leave-one-out, then cumulative
   revert in source order, then minimise) **closes 13/13 keeping 27 of 716 sites as casts** — ≤2n+1 compiles, no agent. (d) S+A (levers
   stripped too) closed 0/5 lever bodies — unmeasured at this size; T6 measures it on all 1,980 lever bodies. (e) **Declarations:** the
   definition's ANSI signature written into a callee's lying declarations is IDENTICAL for **4,473/4,828 (TU, callee) pairs (92.6 %), 0
   DIFFERS**; 355 compile refusals = 136 arity contradictions (`too few/many arguments` → the K&R sites), 121 conflicting declarations
   elsewhere in the TU (a repair must replace EVERY declaration of the callee in the TU), 98 unread causes (main's `At top level:` 22; a
   `#define NULL` context line 14) — T3's solver reads full messages (R103). (f) **Definition fold** (`typedef <Canon> <Local>;` for a
   same-layout tier-1/2 duplicate): 12/20 TUs IDENTICAL, 8 COMPILE-ERROR `structure has no member named a/f0/v` — an opaque-tier fold
   renames members, so the fold must rewrite the TU's member accesses too. (g) **The layout engine agrees with cc1 on 5,283 file-scope
   definitions / 29,248 named fields (0 rejected, 0 unresolved)** — `restruct --audit-layouts`; on the way two engine gaps were fixed
   (nested-paren `__attribute__((aligned(4)))`, per-field `aligned(N)`) and 27 dead `#ifndef BFM_ENGINE_TYPES_H` standalone blocks (21 TUs)
   are now blanked by the census. (h) **The oracle:** the f3 control (`func_801A4258` in md_SC07_004 with `s16 *p = &D_801F8870; p[1]…`)
   is **whole-object DIFFERS and `make build BINARY=md_SC07_004` BYTE-IDENTICAL** (`87ac0de3…`) — relocation SPELLING differs, linked bytes
   do not → T3's linked-relocation mode is required for global blocks/arrays; `engine_types.h` fan-out = 3,818 TUs / 3,975 objects in **35 s
   wall at -j16** (0.141 s/object), with 26 TRANSIENT compile errors at 16 threads (0 on re-run: retry a fan-out failure once). Oracle
   tags must contain no spaces (the scratch object path lands in the pipeline). `judge_text` writes the file IN PLACE and restores it —
   two workers must never own one file; header judgements compile other workers' TUs, so headers run serially after the `.c` bodies.
   (i) **Pricing (R41):** T4 ≈ 1 unattended session (94k pairs, ~93 % mechanical, ~6.6k to the solver); T5 ≈ 1 session (5,995 in-`.c`
   definitions, ~60 % by alias, the rest with member renames; header batches of dozens per 35-s fan-out); T6 ≈ 1–2 sessions (69,497 bodies ×
   2 s + S2 on ~10 %; expected floor after S2 ≈ 4 % of converted sites kept + the 24 % the types cannot hold yet); T7 open-ended by
   decision 1.

4. **T3's engine — what exists and how it is used (the reference is `tools/restruct.py`'s docstring + SETUP §P37 S107).**
   - **Rungs:** S (every typed base of a body → `((Unkstruct_X *)base)->unkK`, or `base->unkK` / `D_x.unkK` when the base is already declared with
     the type; CANONICAL types only under `--apply`, T2's local `P37S_` type under `--try`/`--try-file`; a site the type cannot hold is SKIPPED and
     counted: no-field / width / sign / index / negative / pointee / overlap / aggregate-field), S2 (the minimal kept-cast set: leave-one-out →
     cumulative revert → minimise), S+A (delever's ladder — rung A strip-all, rung B greedy — on the struct-spelled text; survivors' markers
     `(P37 S+A <label>)`; a removed `_m` GTE lever's stale marker scrubbed; the lever row also appended to delever's ledger), X (`pass_hint`:
     SCHED-ALIAS / SCHED-ORDER / CSE-KILL / WIDTH / ADDRESS-FOLD / ALIGNMENT / REGALLOC / COUNT-OTHER / OTHER — a hint, never a verdict), R (the
     registry `RECIPES`: R1 the pointer global read as a struct member (§458), R2 `extern T X[]` (a18), R3 the walked pointer (f3; reloc-flagged);
     each returns candidates the oracle judges; a hit is adopted), D (every declaration of a callee in the TU → the definition's ANSI signature >
     the width-promoted form (`s16 a` → `s32 a`, what a K&R call passes) > every declaration `()` + `// K&R: <n> of <m> args (P37 rung D <label>)`
     when the TU's calls pass another count and the all-`()` form is IDENTICAL; ladder per TU = all callees at once then cumulative greedy; the
     definitions index = the TU's own file, its binary's dir, its headers, then main/resident (REFUSES when two definitions disagree); a
     K&R-marked unit is settled; `--callee F --signature "ret F(params)"` = a definition-side change judged on the definition's TU + every
     declaring TU as ONE unit), L (a file-scope duplicate of a canonical type → deleted when same-named identical text, else `typedef <Canon>
     <Local>;` + member renames by the offset map; REFUSED when a renamed member name is also a field of another type visible in the TU).
   - **The oracle:** `judge_files({rel: text}, tag, reloc=)` — every recipe of every file (a header's includers) compiled in place, whole-object
     equality against the snapshot; a DIFFERS falls to **`judge_linked`** when the job is reloc-flagged or `reloc_only_diff` says the `.text` words
     agree modulo relocation operands (the linked mode = the build's own `ld/objcopy/trim` on the candidate object against the snapshot's other
     objects, SHA1 vs `config/check.<alias>.sha`; ~10 ms); a fan-out COMPILE-ERROR retried once. **The snapshot (`--snapshot-baseline`) REFUSES an
     object that does not reproduce from an untouched compile** — run it only after a green clean fleet run; it also carries every binary's link
     inputs (`_link/<alias>/`, `links.json`). `--linked-control` (md_SC07_004 `func_801A4258`) is the known-true + negative.
   - **The ledger** `.run/P37/restruct/ledger.jsonl`: one row per unit (rung, tu, unit = fn | `decl:<callee>` | `def:<callee>` | `fold:<name>@<line>`,
     `nhash_before/after`, verdict, per-site rows MEMBER / KEPT(hint) / REFUSED / SKIPPED, `bases`, `skips`, `residual`, `hint`, `levers`, `recipes`,
     `cause`, `needs_types`); "done" = (rung, tu, unit, current hash) ∈ the latest rows' DONE verdicts; `--redraw VERDICT…` draws settled units
     again (e.g. `DECL-KEPT` after T5's types exist); `inflight.json` is the only restore (`--restore` drops the killed batch's rows).
   - **The measured causes of a kept declaration (t3d1/t3d2, 16 of 258):** 7× `func_800D20C0` — its prototype names `Pos800D20C0`, a type local to
     the resident TU the overlay cannot see (`needs_types`; T5 makes it canonical, then `--redraw DECL-KEPT`); 1× `conflicting types for
     func_800D2318 … prev: shared/ov/func_80168BDC.h:3` — a per-function SHARED HEADER carries the lying spelling (rung D `--headers` mode judges
     the header on every includer); 8× K&R sites marked (`too few arguments`: the original's calling convention). T4's plan: rung D over the
     fleet by symbol space in cycles (`tools/restruct_cycle.sh 1 N 50 D`, detached), `--headers` batches for the shared headers (serial, ~35 s per
     judgement on 141 includers), then the definition-side changes (`--callee/--signature`) from `.run/P37/census/parked.tsv`'s 13 signature
     patches (e.g. `func_800385C0`: `s16 a0` → `s32 a0`, the patch text in `.run/P36/agents/main__func_800385C0/scratch/signature.patch`) with R22
     per change; the 51 TU-CONFLICT rows of `config/dedup_exceptions.tsv`; class E aliases (`extern u16 aD_x __asm__("D_x")` → one typed
     declaration) and `__builtin_abs` → `abs` are NOT yet generators in the engine — T4 adds them as rung-D sub-rewrites (the census records
     them: 5,749 aliases / 225 names; 144 `__builtin_abs`). **Pricing (T2, R41):** ≈94k (TU, callee) pairs × 0.15–0.8 s ≈ 1 unattended session,
     ~93 % mechanical; the t3d1 batch measured 27 TUs / 258 units / 223 compiles in 31 s wall at -j12.
   - **Known-true controls to re-run after any engine change:** `restruct --selftest` (48) · `--selftest --real` (53: + calibration, the tree's
     own text IDENTICAL, a nop DIFFERS, the linked control, the macro proof) · `--try src/ov_SC05_010/ov_SC05_010_jr_80180F84.c func_801814AC
     --base global:D_801C7E30 --recipes` → DIFFERS · S2 kept 1 (+0x34) · R1 IDENTICAL · `--try-file src/ov_SC06_008/ov_SC06_008_jr_8017C294.c
     func_8017E830` → S IDENTICAL (2 members) · S+A 6 levers off (nothing written).
   - **For T6 (noted S107):** the 6 `gte_rtv0tr_m` levers of func_8017E830 come off with or without the struct today — a P36 T5 leftover class;
     a targeted regen over the 450 GTE `_m` variants (delever's rung A per body, or `gte_consolidate --sweep` on the current tree) is cheaper than
     meeting them one S+A body at a time. `--write-types --top 6` previews the two big types: `Unkstruct_800B5CB8` 90 fields / 44 overlaps,
     `Unkstruct_80126B58` 146 fields / 28 overlaps + 1 misaligned — the overlaps are the map's width conflicts (T5: union vs split per offset).
     `--audit-types` on the legacy header: 26 violations, all legacy `pad<SIZE>` names → T5's rename list.

5. **Files and artifacts.** Tools: `tools/struct_layout.py` (new; selftest 9), `tools/restruct.py` (2,900+ lines; the T2 functions verbatim inside),
   `tools/restruct_cycle.sh` (new), `tools/delever_oracle.py` (+ `link_vars`, `snapshot_links`, `judge_linked`, `reloc_only_diff`, `linked_control`, the
   snapshot guard, the error filter), `tools/delever.py` (`marker_edits(phase=)`), `tools/type_census.py` (imports `struct_layout`; `walk_all`),
   `include/common.h` (the macros; the `M2C_FIELD` note corrected — one of the three T9-owed corrections, done). Evidence (tracked):
   `.run/P37/restruct/{ledger.jsonl,batch_t3d1.json,batch_t3d2.json,apply_t3d1.log,apply_t3d2.log}`, `.run/P37/baseline/{r22_t3a,r22_t3d1,r22_t3d2,
   r22_t3c}.log`; ignored: `.run/P37/restruct/{argcheck_cache.json,selftest/,macro_probe/,types_preview/}`, `.run/P36/delever/baseline/` (the snapshot:
   7,428 objects + `_link/` + `links.json`, at `42a57f576`). Docs: SETUP **§P37 S107**, dictionary rows (restruct updated; struct_layout,
   restruct_cycle added), cookbook **§458 addendum**, decision log **P37 S107**, accelerators **P37 S107**, story §10 + retrospective §7
   advanced, the timeline regenerated (78 rows). **Still owed at T9:** `docs/actor-struct.md` (+0x108/+0x10C are 4-byte in the code), the §396(a)
   correction (`.run/P36/agents/ov_SC03_110__func_801800F0/mechanism.md:64-70`).

6. **Environment and commands.** `~/bfm-decomp` on ext4; `.venv/bin/python`; every build `JOBS=16`/`-j`. The headless Ghidra MCP is started by the
   SessionStart hook and stopped by the SessionEnd hook — not needed until T8. R22: `make clean && make extract-all JOBS=16 && make check-all
   JOBS=16` (≈90–110 s; read the exit code, `pipefail`). Oracle: `tools/delever_oracle.py --snapshot-baseline` (ONLY after a green R22; refuses
   otherwise) then `--calibrate ov_SC04_011 md_SC07_004 main -j 16` (keyed to HEAD — every commit stales it; `--apply` refuses on a stale one).
   Engine: `tools/restruct.py --plan --rung D --batch 50 [--only <alias>]` (the argcheck rows are cached on the src stamp — 2.4 min to rebuild after
   any `src/` change) · `--apply --rung D --batch 50 --label <l> -j 12` · `--headers` for the shared headers · `--callee F --signature "…"` ·
   `--restore` · `--status` · `--check-ledger` · `--audit-types` · `--try-file TU FN` (dry, nothing written). The cycle, DETACHED: `setsid nohup
   bash -c 'TASK=T4 tools/restruct_cycle.sh 1 8 50 D; echo "cycle exit=$?"' > .run/P37/restruct/cycle_t4a.log 2>&1 &` (per batch: guarded
   snapshot + calibration when stale → apply → R22 → `type_census --sites` (3.5 min; `CENSUS=0` skips) + readability snapshot → log + commit).
   Census: `tools/type_census.py -j 16 --sites`. Series: `tools/readability_progress.py --snapshot <label>`, `tools/lever_progress.py --snapshot
   <label>`, `tools/progress.py --json --readme [--check]`. Health: `make tools-health` (foreground, 8–15 min — **currently RED at audit_public
   on the P36 ledger size, see 1.**); `tools/doc_links.py --strict`, `tools/tool_census.py --check`, `make kit-corpus`, `tools/cookbook_index.py
   --check` — all OK at this checkpoint. No harness task-list tool exists in this build (R28 = this file's ☐/☑).

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
