# PhaseEnd — Phase 3.40: Residue lane (implements Gen 3.40)
Approved: 2026-10-17 | Closed: 2026-11-07 | Planner: claude-opus-5-5[1m]/high | Tasks: 20 done, 1 superseded

## Milestone
Milestone: every residue item from 3.39's ledgers is fixed for real or still marked with its pass, instrument and cause, with TYPE-NOT-CANONICAL gone inside the 95 % band: `PY tools/type_census.py --check-casts --residue` rc 0 and lying 0 (from 11 ledgered), with TYPE-NOT-CANONICAL 0 for every type inside the 95 % band (6,676 types at the post-T2 census, frozen in `config/tnc_band.tsv`) and the tail below the band covered by RESIDUAL rows under one new named cause, TYPE-BELOW-BAND, assigned by a rule the tool applies (not by hand), its count stated (about 7.0k sites, never above the tail frozen with the band), so the by-cause line otherwise carries no TYPE-NOT-CANONICAL (from 291,819); `PY tools/restruct.py --rung S --check-residue` uncovered 0 in ov_*, md_*, main and src/shared/*; `PY tools/type_census.py --check-structs` OK with 0 duplicate defs, 0 dead names, controls 4/4; every lever site either removed or excused by a residue row re-judged this phase with pass, instrument and a named compiler wall as its cause, checked by a rule the tool applies (not by hand): `PY tools/lever_census.py --check --strict --residue config/lever_residue.tsv` OK with residue-unused 0 and no row without a wall cause (unwalled 0, unknown wall tags 0), the before/after stated (from 3,528 sites in 2,433 residue rows); `PY tools/lever_census.py --check` 0 UNMARKED; the legacy-T7 items (func_801A1E94/func_801A5C44, the 5 same-address copies, the 5 return-type lies, func_8016BF50) fixed; R22 218/218.
Confirmed by the developer at the close.

## Tasks
- T1 — phase-start health, baselines, instrument checks, ledger hygiene | Done: Start tree 1109994812 is green (tools-health, R22 218/218, oracle calibration, restruct selftest). Census and lever baselines are recorded below. Census dirs are settled, the 5-6 site gap and the 80126B58 anomaly are explained, and the delever ledger is untracked with gz snapshots of both ledgers. Summary: The phase starts from a verified, green tree with every milestone number measured. The apparent disagreement between the two census folders was not a disagreement: the gate deliberately skips six casts written inside `#define` lines, and the progress page shows both counts. The odd type that looked undefined is defined; its ledger rows simply still carry the cause stamped before it was defined. Three of the milestone's checks already pass today, so only the TYPE-NOT-CANONICAL count, the lying count and the literal lever gate actually measure this phase's work. | commit: 1109994812 | tasks/T1.md | logs/T1.md
- T2 — canonical-types pilot and fold policy (top 75 map types) | Done: the top 75 TNC map types each carry a decision in `config/type_folds.tsv` (51 define, 7 fold, 16 residual + 1 already canonical), written in two header batches, swept by rung S, residue rows rewritten; gates green. Blocked only on the plan's own judgment: TNC 0 does not fit the phase. Summary: The 75 struct types that held half of the "type not canonical" cast residue now have one decision each: they become a canonical struct, they fold onto an existing one when the code proves they are the same object, or they stay residual with a named reason. After two header edits and a rung-S re-sweep, non-canonical sites fell from 291,819 to 139,520 and raw pointer casts from 257,470 to 174,987, with every binary still byte-identical. The rest of the problem is a long tail: 12,742 types remain, and the last 6,066 of them hold about 7,000 sites, roughly one each, so driving TNC to zero would mean thousands of one-use canonical structs. The developer should choose the band to cover next; the recommendation is the 95 % set with mechanised decisions. | commit: - | tasks/T2.md | logs/T2.md
- T3 — 95 % band: frozen band, mechanised type decisions, header batches, below-band cause | Done: every TNC map type now has a config/type_folds.tsv decision by rule (band 6,673 rows, tail 6,065 TYPE-BELOW-BAND) and 5,301 band defs sit in include/struct_types.h, R22 218/218 and check-structs OK; by-cause unchanged until T4/T5 sweep and restamp. Summary: The 95 % band was frozen from the post-T2 census and matches T2's projection exactly. A new restruct.py mode decides each band type by the binding policy (fold only on detected evidence, else a residual layout class, else a definition under its owner address) and writes rows and definitions without hand edits; the remaining small types get the below-band cause. The definitions went into the header in three ranked batches, each gated and committed. Nothing in the bodies changed yet: the sweeps that use these types are T4/T5. | commit: - | tasks/T3.md | logs/T3.md
- T4 — rung S re-sweep, overlays, onto the new canonical types | Done: every ov body with a band-type site re-swept (24 green batches, drawable 2,417 → 38 → nothing drawable); residue, restamp and the NO-EDIT variant run on ov; check-residue ov 0; band types TNC 0 and the tail TYPE-BELOW-BAND in ov. The 7,128 ov sites on 652 post-freeze drift types go to the new drift task (done-when amended). Summary: The overlay code was re-swept onto the struct types T3 defined: about 55,600 raw pointer accesses became named member accesses, with every binary still byte-identical after each of the 24 batches. The cast ledger was then re-stamped so each remaining raw site names its real cause, which drops the "type not canonical" count from 139,520 to 23,630 overall. In the overlays, no site of a band type or of a tail type keeps that cause any more. What remains (7,128 overlay sites) sits on struct names that did not exist when the band was frozen: the sweep regrouped the leftover raw sites into new clusters with new hash names, and no rule yet decides them. | commit: - | tasks/T4.md | logs/T4.md
- T5 — rung S re-sweep, md_*, main and shared | Done: md_*, main and src/shared/* re-swept by rung S against the band defs; residue, restamp and NO-EDIT restamp run per segment; band TNC 0, uncovered 0, check-structs OK. Summary: The newly defined band types were drawn into the md, main and shared code (about 3,500 casts became member accesses, every batch byte-identical on all 218 binaries). Unused band definitions were pruned and their types recorded as having no member use. Duplicate definitions that the sweep had bound to the same object were merged, so the struct check passes again. Casts that still point at an undefined type are all on "drift" types the sweep's regrouping created; they are counted here and left for T17. | commit: e033c139c5 | tasks/T5.md | logs/T5.md
- T6 — legacy-T7 declaration items and the ledgered lying decls | Done: lying 0 (ledgered 0), lying_exceptions.tsv header-only; md_SC07_004 pair pin-free with real params; func_8016BF50 one ANSI prototype, TU-CONFLICT row gone; return-type lies fixed at def+callers; R22 218/218. Summary: The old declaration lies from Phase 37 are gone. The two md_SC07_004 functions now take the argument they always used, so their register pins went away, and their wrapper passes it through. func_8016BF50 has one prototype everywhere, so its shared body now covers four more overlays. The lying-declaration count is zero with nothing excused. Functions that pass a callee's result straight through are now declared to return it. | commit: bb99c1cf45 | tasks/T6.md | logs/T6.md
- T7 — missing-parameter pins become declared parameters | Done: every missing-parameter pin whose register carried an incoming value is now a declared parameter in its def and all callers; the 384 survivors carry a residue row naming the refusal. Summary: Functions that read an argument register through a register pin, instead of declaring the parameter, were rewritten so the parameter is declared and every caller passes it, with byte-identical builds after each batch. Most of the remaining rows turned out not to be parameters at all: the register is written before it is read, so there is nothing to declare. The cast gate needed one small matching fix, because a pin that became a parameter changes how the census names its base. | commit: 6a652a9491 | tasks/T7.md | logs/T7.md
- T8 — oracle re-judge and the mechanical lever classes | Done: every residue row is now oracle-judged (0 "left by the author", 0 "not judged"); gte-lever 0, per-TU asm macro defs 164 → 1 (the shared prelude ENGINE_SHB), asm bodies 13 → 1 (func_80020F34, hand-written evidence); TSV rewritten, residue-unused 0. Summary: Every lever the author had left unjudged was removal-tested against the byte oracle. Each one is genuinely needed, so none could be removed, and the older claim that "all pins are needed" now holds with evidence behind it. Twelve hand-copied assembly routines became plain C that compiles to the same bytes, and all GTE calls now go through one spelling in the shared header. The one routine that really was written in assembly keeps its assembly body, and its ledger row records why. | commit: - | tasks/T8.md | logs/T8.md
- T9 — head-class lever cracks with propagation | Done: 18 of 38 head classes cracked pin- and asm-free and propagated to every copy (442 copies); residue -586 rows; each batch R22 218/218; 20 classes keep their rows with attempts recorded. Summary: Every one of the 38 head classes got at least one crack attempt, the six largest first, with up to 4 crack coders in parallel. Eighteen classes now compile byte-identically from plain C with no pins or asm, and that C was copied into every overlay that shares the function, removing 586 ledgered lever rows. The rest stay in the residue ledger with their best near-miss recorded; one class (func_80177B5C, 133 rows) matches only via an identity statement that acts as a launder, so it was not counted and is left for the developer. | commit: 43f073a212 | tasks/T9.md | logs/T9.md
- T10 — singleton crack pilot and wave projection | Done: 12 of a stratified 20 singleton functions are now lever-free and banked (R22 218/218, strict --residue OK, residue 2342 → 2309, −20 rows); the wave is projected. Summary: We tried to remove the compiler-steering levers from 20 one-of-a-kind functions, chosen to cover every lever kind and body size, with four coders working in parallel. Twelve now match the original bytes in plain C. The other eight hit specific compiler behaviours that plain C cannot reproduce. At this rate the remaining 430 functions would take about 14 hours at the four-coder cap and about 19 million tokens, and about 170 functions would still keep their levers. So the literal finish line (zero levers) cannot be reached by the singleton wave, and the milestone needs the developer's ruling. | commit: e984a520d5 | tasks/T10.md | logs/T10.md
- T11 — singleton crack wave | Done: every singleton (file, func) group attempted or parked; 220 functions banked lever-free (or fewer kinds) in 12 R22-green batches; every singleton row in config/lever_residue.tsv names its gcc wall (`singleton(<kind>) wall:<tag>`), unwalled 0, residue-unused 0. Summary: Each function whose hint or register pin stood alone was given to one coder for 20-30 minutes to write plain C that compiles to the same bytes without the hint. About half succeeded; those bodies are now in src and their ledger rows are gone. Every function that did not crack has a row that says which gcc pass blocks it and how close the best try came, so later work can group survivors by wall instead of by guess. Two families stay parked by plan (instructions with no C spelling, and the func_80188C04 unused-result family) and their rows now name that wall too. | commit: 31a30b3eca | tasks/T11.md | logs/T11.md
- T12 — timeline "uncovered" series beside raw casts | Done: readability rows carry an appended `uncovered` column; the timeline draws it beside the four-form raw series with a legend that separates debt left from the gate's measure; row 'P3.40 T12: uncovered series' recorded (uncovered 0). Summary: The readability series now records how many raw cast sites the cast gate actually fails on (those with no ledgered cause), next to the raw counts. The timeline chart draws that number on the same scale as the raw four-form line, so a green gate (0 uncovered) visibly sits on the floor while the raw debt line stays high. Making the tool health check pass also needed three small pieces of upkeep left over from earlier work. | commit: - | tasks/T12.md | logs/T12.md
- T13 — milestone gate and record (Phase 3.40) | Done: every milestone command green at aace727c4c from a clean tree: check-casts rc 0 (lying 0, TNC 0, TYPE-BELOW-BAND 5,871 ≤ frozen tail 6,976), check-residue 0 ×4, check-structs OK, lever strict+residue OK (unused 0, unwalled 0, unknown-tag 0), `--check` 0 UNMARKED, R22 218/218, tools-health OK. Summary: The phase's gate passes in full. Every raw cast is either fixed or recorded with its cause, and no in-band type is left without a canonical definition. Only the small types below the frozen band stay raw, under their own cause. Every remaining compiler lever names the gcc pass that needs it. The close snapshots, the ledger backups and the lever record are written, and two last facts from the phase's work went into the cookbook. | commit: 830167ea3a | tasks/T13.md | logs/T13.md
- T14 — phase-close docs: README graphs, story §10, retrospective §7, wiki (Phase 3.40) | Done: story §10 has its Phase 40 part and §11 a P3.40-close row; retrospective §7, the next-steps wiki page (sentences + gap table) and the conventions page (ledger backup step) run to Phase 40; readability row 'P3.40 T14: phase-close docs' recorded, timeline and progress regenerated. Summary: The public record now tells the Phase 40 story: the 95 % band of struct definitions, the sweeps and the drift types, the declarations made honest, and every surviving compiler lever naming the gcc pass that needs it. The retrospective adds what was believed and what turned out true, what failed, what it cost and what we would do sooner. The charts and progress page carry the close snapshot. | commit: de1d7a80d6 | tasks/T14.md | logs/T14.md
- T15 — ledger backup at phase close: stripped public copy and full archive copy | Done: `tools/ledger_backup.py` writes both ledgers as a stripped public gz in docs/ledgers/ and a full gz committed (unpushed) in ../BFM-decomp-archive/ledgers/P3.40/; wired and documented as a phase-close step. Summary: The two irreplaceable ledgers now have a durable copy at each phase close. The public copy in this repo is stripped of disassembly. The full copy goes to the private archive repo, which the developer pushes. A scan of every field of every record decided what is stripped, and the tool checks its own output (parses, same record count, no disasm, under 50 MB). | commit: 0be078e78e | tasks/T15.md | logs/T15.md
- T17 — drift types: decide the TNC map types the T4/T5 sweeps' census regrouping created, all segments | Done: drift TNC 8,146 sites / 870 types → 0 (two rounds + an approved mini round 3); by-cause has no TYPE-NOT-CANONICAL; check-structs OK (dup 0, dead 0); check-residue 0 ×4; R22 218/218. check-casts rc 1 = T18's 4 items (accepted). Summary: The census had regrouped leftover casts into new, undecided type names after the earlier sweeps. A new drift mode of the band decision tool decided all of them by the same rules as the band, two rounds over, and the sweeps turned about 1,600 more casts into member accesses. A small third round, approved by the developer, decided the last 6 casts, so no undecided type is left. The struct check is green again after repairing duplicates that had built up since T5. | commit: - | tasks/T17.md | logs/T17.md
- T18 — cast-gate leftovers from T8.c4: 3 K&R-empty lying decls, 1 unbacked macro site | Done: `type_census --check-casts --residue` rc 0: lying=0 (ledgered 0), unbacked 0, uncovered 0 in every form; R22 218/218. Summary: The cast gate failed on three functions declared without parameters and one kept-cast macro that no ledger row backed. The three now have full prototypes matching their definitions and their callers make plain calls; the macro site went back to its raw spelling, which the existing residue row already covers. The gate is green again with no exception rows. | commit: ace348ee47 | tasks/T18.md | logs/T18.md
- T19 — lever wall rule: wall vocabulary and the tool check | Done: config/lever_walls.tsv holds 32 walls (tag, pass, what plain C cannot do, evidence). `lever_census --check --strict --residue` now fails on unused, unwalled or unknown-tag rows and prints the walls line. T11's 321 rows are on vocabulary tags. Summary: Each lever left in the code now has to say which compiler pass makes it necessary, using names from one shared list of walls, and the lever check enforces that. T11's roughly 80 ad-hoc wall names were folded into 32 walls, and each row still records its original name. The 861 rows nobody has judged yet (head-class, the T7 scratch pins and the two hand-asm rows) now show up as failures, grouped by cause, instead of passing silently. | commit: - | tasks/T19.md | logs/T19.md
- T20 — walls for the rows no wave re-judges: head classes, T7 scratch pins, asm | Done: every lever residue row names its compiler wall; `lever_census --check --strict --residue config/lever_residue.tsv` rc 0 (rows 1180, unwalled 0, unknown-tag 0, residue-unused 0). Summary: Each of the 861 residue rows that no crack wave had re-judged now names the gcc pass that keeps its lever. The head classes take the wall their exemplar hit in T9's attempts, and two of them were probed fresh. The rows T7 called missing parameters turned out to be scratch registers written before they are read. Each was tagged by the first compiler pass where the pinned and pin-free builds diverge, a rule checked by hand on 26 functions. Three of those probes were outright cracks and are banked with a green full gate. | commit: - | tasks/T20.md | logs/T20.md
- T21 — Bank the waiting cookbook lessons (one time, PA3 3.30) | Done: all 51 `generalizable:` gotchas from 34 task summaries are banked or ruled out; new entries C0530-C0533. Summary: Task summaries had marked lessons for the cookbook that the 3.2 close no longer promoted. Every one was checked against the cookbook: the 3.38 and 3.39 lessons were already banked, five of this phase's were covered by existing entries, four were tool bugs or repo facts and not techniques, and the rest became four new entries. | commit: - | tasks/T21.md | logs/T21.md

## Decisions that still bind
- T1 — census dirs: gate and work = `.run/P37/census` (type_census default, restruct CENSUS, restruct_cycle.sh:66); series = the newest `.run/P<N>/census` (today P39; readability_progress.py:63, progress.py:1181), which restruct_cycle.sh:69-71 refreshes; lever = `.run/P36/census`. Do not create `.run/P40/census` by accident: it would become the series source. Scratch goes in `.run/P40/<task>/`.
- T2 — type identity is decided by object evidence, never by bytes. A map type folds onto an existing canonical type only with evidence that both name the same object: E1-lineage (same union-find cluster, the drift name of a canonical cluster), E2-anchor (both anchored to the same global address, e.g. `&D_8011F7A8 + k`), E3-copy (field-wise copies at equal offsets between the two). Equal layout without a shared object is a coincident twin: kept apart and listed in docs/struct-twins.md `## Twins` (`struct_twins.py --census-dir .run/P37/census --write`).
- T2 — a map type without entity evidence for an existing type is defined under an address name: `Unkstruct_<address of a function or global that owns it>` (suffix `_2` on collision), never under its cluster hash (hash names drift between census runs). Home file: include/struct_types.h for overlay and map types; src/shared/engine_types.h only for engine types already homed there. Each decision is a row of config/type_folds.tsv (`map_type action target evidence note`); restruct.py reads it, no typedef aliases.
- T2 — a map type stays residual (a `residual` row, its cause the target) when no single struct can be written honestly: TYPE-UNION (conflicting widths at one offset; needs a union), TYPE-NO-LAYOUT (no consistent layout, size 0), TYPE-SCALAR (one scalar field; not a struct), TYPE-INTERIOR (base points inside an object, negative offsets), TYPE-NO-MEMBER (a def that rung S drew in 0 bodies; def pruned, would be dead). Sites of drawn canonical bases that still cannot be respelled keep the site causes (NO-FIELD, NO-EDIT, INDEX, GADDR, GLOBAL, TYPE-NOT-VISIBLE, POINTEE, AGGREGATE-FIELD).
- T2 — defining a type does not move by-cause; every decision batch ends with rung S over the touched bodies, then `--residue --forms P,X,I,M` (new rows) AND `--residue --restamp` (rewrites stale TNC stamps) per segment, census before restamp, then `--check-residue`.
- T3 — a TNC map type outside the frozen 95 % band (config/tnc_band.tsv rank > band_n) gets `residual TYPE-BELOW-BAND`, evidence `band:<rank>/<sites>`, written by `restruct.py --decide-band --ranks tail --write`; the band is never re-frozen (later census denominators shrink as folds apply).
- T3 — a band type whose rendered def would form a tier-1 dup class with an existing named canonical def gets `residual TYPE-CANON-TWIN`, evidence `layout-twin:<canonical>` (layout identity is not entity evidence, G62; tier 1 always gates check-structs). Accepted by Claude 2026-10-15.
- T3 — TYPE-UNION = a conflict entry that is `overlap` or holds more than one width at one offset (sign-only mixes are not a union); TYPE-SCALAR = one field at offset 0; checked in order NO-LAYOUT, INTERIOR, UNION, SCALAR, then render refusal.
- T15 — every phase close runs `PY tools/ledger_backup.py` before the PhaseEnd archive (docs/ops/phase-close-ledger-backup.md); the developer pushes the archive clone.
- T19 — a lever residue row passes strict only if its cause ends ` wall:<tag>` and the tag is in config/lever_walls.tsv; a new wall is a new vocabulary row with an evidence pointer, never a free-form tag.
-

## Rules proposed
- T2 — a decision batch is not done until `--residue`, `--restamp` and `--check-residue` have run on every segment it touched.
- T3 — a generated block in a hand-edited header carries a marker pair and a provenance line naming the generator and the commit it ran at.
- T11 — none

## Cookbook entries added
C0529 | git clean -X with a pathspec inside an untracked ignored dir deletes the whole dir | git,cleanup,trap | 2026-10-19 | 3.40/partner | .run cleanup 2026-10-19
C0530 | Lever-removal moves from 3.40 cracks: in-place RMW, % 2^k, derived-pointer reuse, short counters | levers,delever,pins,birthing-boost,sched1,cse | 2026-10-21 | 3.40/T10 | P3.40 T9/T10 summaries
C0531 | Residue refresh: --restamp writes no new rows; after rung D re-run all four forms | residue,restruct,restamp,rung-D,casts,gate | 2026-10-21 | 3.40/T7 | P3.40 T2/T7 summaries
C0532 | A rung-S sweep reshapes map types: hash names drift, frozen bands go stale, twins go SHARED | structs,restruct,rung-S,census,band,twins | 2026-10-21 | 3.40/T4 | P3.40 T2/T4/T5 summaries
C0533 | Census summary JSONs are capped; never rebuild rows from them | census,json,structs,caps,trap | 2026-10-21 | 3.40/T3 | P3.40 T3 summary
C0536 | verbatim_check --update keeps ov_* fleet rows; drop a decompiled one by hand | verbatim,tools-health,manifest | 2026-11-06 | 3.40/T12 | P3.40 T12 tools-health
C0537 | struct_map size_hint can be an address: cap layouts at PSX RAM before rendering | structs,census,restruct,oom,layout | 2026-11-06 | 3.40/T17 | P3.40 T17.c1 OOM
C0538 | Cycle calibration fails after a split rename: stale oracle baseline objects and recipes.json | restruct,rung-S,oracle,recipes,delever,baseline | 2026-11-07 | 3.40/T17 | P3.40 T17.c3 calibration
C0539 | Repair check-structs after prunes: fresh census before struct_twins --write, lift outside_canon, fold tier-1 redeclarations | structs,check-structs,twins,lift_types,prune | 2026-11-07 | 3.40/T17 | P3.40 T17.c5
C0540 | Rung S draws nothing on a MEMBERS-verdict body: REDRAW=MEMBERS per TU:FN; --plan ignores --redraw | restruct,rung-S,redraw,structs,header | 2026-11-07 | 3.40/T17 | P3.40 T17.c6
C0543 | Return-type changes: def+decls+callers as one unit; the return type is a caller byte fact | declarations,return-type,lying,bytes,rung-D | 2026-11-07 | 3.40/T13 | P3.40 T6 summary
C0544 | Lever residue rows key (file, func, kind): one crack re-causes a row, an unused row fails strict | levers,residue,walls,strict,gate | 2026-11-07 | 3.40/T13 | P3.40 T19/T20/T13
C0545 | Strip a JSONL ledger for public: per-path scan of every string, self-verify the gz | ledger,public,audit,gzip,kit-lint | 2026-11-07 | 3.40/T15 | P3.40 T15.c1

## Research
R3.40-001 | 3.40 planner input — drive `lever_census --check --strict` to 0 by real fixes (residue ledger, census gate, wiring) | lever_residue.tsv and lever_census --check --strict: facts for the 3.40 plan | lever-census, residue, R126, phase-3.40, gate | retriever-code | 2026-10-14 | 46 lines
R3.40-002 | pa-planner 3.40 phase plan: canonical-types campaign (TNC residue) and timeline "uncovered" series | TNC residue, canonical types, restruct rungs, timeline series (partial, 20-call cap) | type-census, residue, TYPE-NOT-CANONICAL, restruct, restruct_cycle, readability-timeline, delever-ledger | retriever-code | 2026-10-14 | 54 lines
R3.40-003 | plan phase 3.40 (Residue lane, bfm-decomp) for pa-planner; extract P3.39 milestone, decisions, rules, sizing, T12 close docs; legacy-T7 residue items from P3.37/P3.38 and LEGACY_INDEX | Phase 3.40 (Residue lane) planning inputs from P3.39 close, and legacy-T7 status | phase-3.40, residue, type-not-canonical, lever-residue, reading-A, rules-R123-R126, phase-close-docs, legacy-T7, md_SC07_004, return-type-lies | retriever-digest | 2026-10-14 | 96 lines
R3.40-004 | identify Blizz127/brave-fencer-musashi-decomp-port, its relation to our decomp | Blizz127/brave-fencer-musashi-decomp-port: what it is and how it relates to bfm-decomp | bfm, decomp, pc-port, external-repo, license | retriever-web | 2026-10-14 | 45 lines
R3.40-005 | T2 | T2 state reconstruction (canonical-types pilot) and the rS1..rS21 no-op loop | T2, canonical-types, type_folds, header-batch, restruct-cycle, rung-S, restamp, residue, check-casts, handoff | retriever-digest | 2026-10-15 | 70 lines
R3.40-006 | P3.40 REPLAN drafting; T3 band sweep over the 95% TYPE-NOT-CANONICAL band (6,676 map types) and a new below-band residual cause | Interfaces for mechanising TYPE-NOT-CANONICAL fold decisions (P3.40 T3) | P3.40, restruct, type_folds, residue_cause, restamp, struct_map, type_census, residue_census | retriever-code | 2026-10-15 | 41 lines
R3.40-007 | 3.40 REPLAN facts for tools/ledger_backup.py (T15) and the T3 band sweep gotcha. Not yet written: tools/ledger_backup.py. | Ledger backup tool facts and restruct cycle wiring (P3.40 REPLAN) | ledger, restruct, delever, audit_public, tools-edit-kit-corpus, restruct_cycle, P3.40 | retriever-code | 2026-10-15 | 74 lines
R3.40-008 | 3.40 T5 prep (md_*, main, src/shared/*) | Rung S re-sweep procedure: 3.40 T4 (ov_*) and 3.39 T4 (md/main/shared) | rung-S, restruct, residue, restamp, no-edit, band, tnc, procedure | retriever-digest | 2026-10-16 | 56 lines
R3.40-009 | T6 recipe lookup for T7 (270 `register ... asm("$4-$7")` pins) | T6 rung D recipe and missing-parameter pins | T6, restruct, rung-D, same-address-copies, R22, lever-residue, pins | retriever-digest | 2026-10-16 | 32 lines
R3.40-010 | T10 singleton (20-function) crack pilot design | T9 head-class lever cracks: workflow, moves, costs, singleton-pilot gotchas | lever-residue, head-class, crack-workflow, delever, match_one, propagate, R22, cookbook | retriever-digest | 2026-10-17 | 65 lines
R3.40-011 | planner340 phase-plan redraft; amended close gate `lever_census --check --strict --residue` OK, residue-unused 0, every residue row names a compiler wall in its cause | lever_census residue: parse, strict rc, writer, and where a cause-names-a-wall rule goes | lever-census, residue, strict, phase-40, planner340 | retriever-code | 2026-10-17 | 61 lines
R3.40-012 | phase 3.40 mid-phase plan redraft (milestone amendment + cast-gate fix task) | Phase 3.40 T7-T10 lever residue: survivors, walls, cast leftovers | phase-3.40, lever-residue, T7, T8, T9, T10, walls, lying-decls, cast-gate | retriever-digest | 2026-10-17 | 42 lines
R3.40-013 | T11 singleton crack wave (~430 fns, 4-coder cap) | T10 singleton crack pilot: run, scorer, banking recipe for T11 | T10, singleton, crack, lever, delever_search, banking, tsv, pilot, parked | retriever-digest | 2026-10-17 | 75 lines
R3.40-014 | T11 final wall causes (`singleton(<kind>) wall:<tag>`) for lever_residue.tsv rows T11 did not attempt | Parked func_80188C04 family, T10 wall evidence, and the 8015444C barrier rows | t11, walls, parked, family-80188C04, flow-unused-result, barrier, 8015444C | retriever-digest | 2026-11-06 | 34 lines
R3.40-015 | T17 planning, decide drift TNC map types not in config/tnc_band.tsv or config/type_folds.tsv | restruct.py P3.40 T3 freeze-band / decide-band anatomy (for a `--ranks drift` mode) | restruct, p40, t3, tnc-band, decide-band, type-folds, drift | retriever-code | 2026-11-06 | 36 lines
R3.40-016 | Phase 3.40 T20 (tag lever residue rows with compiler-wall tags), input from T9 logs | T9 uncracked head classes: compiler wall per exemplar | lever-residue, head-class, compiler-walls, T9, T20, delever, cse, sched, global-alloc, reorg | retriever-digest | 2026-11-07 | 64 lines

## Audit
- seed: median 21k, max 24k, n=38 (phase 3.40)
- previous phase 3.39: median 14k, growth 47.1%
- CLAUDE.md: 1304 bytes (+395)
- .claude/skills/commit-task-autostage/SKILL.md: 1024 bytes (unchanged)
- .claude/skills/d1-snapshot/SKILL.md: 932 bytes (unchanged)
- .claude/skills/pa-external-agents/SKILL.md: 11144 bytes (new)
- .claude/skills/pa-planning/SKILL.md: 7854 bytes (new)
- .claude/skills/project-architect/SKILL.md: 13748 bytes (+761)
- .claude/skills/restruct-cycle-watch/SKILL.md: 1119 bytes (unchanged)
- .claude/skills/retire-doc-consumers/SKILL.md: 927 bytes (unchanged)
- .claude/skills/tools-edit-kit-corpus/SKILL.md: 756 bytes (unchanged)
- .claude-state/memory/MEMORY.md: 60 bytes (-16)
- HOW_WE_WORK.md: 8335 bytes
- cookbook/INDEX.md: 249327 bytes
- rules/INDEX.md: 15289 bytes
### Carry audit — phase 3.40 (2026-10-15T03:59:35Z → open UTC, 2 sessions, 8739 requests)
- beside 3.40: session eaf2d6a5 $0.00 (153 turns), not attributed
- beside 3.40: session 295d362f $0.00 (286 turns), not attributed
- beside 3.40: session 87356523 $0.00 (271 turns), not attributed
- beside 3.40: session 90e5ca3a $0.00 (176 turns), not attributed
- beside 3.40: session 0fe6acf4 $0.00 (138 turns), not attributed
- beside 3.40: session b04ccbe8 $0.00 (108 turns), not attributed
- beside 3.40: session ee199aee $0.00 (239 turns), not attributed
- beside 3.40: session 3b346545 $0.00 (198 turns), not attributed
- beside 3.40: session 641cbb66 $0.00 (190 turns), not attributed
- beside 3.40: session 4f42e167 $0.00 (226 turns), not attributed
- beside 3.40: session e9a95da3 $0.00 (318 turns), not attributed
- beside 3.40: session 1746610a $0.00 (104 turns), not attributed
- beside 3.40: session 59b933c8 $0.00 (147 turns), not attributed
- beside 3.40: session 70e05adb $0.00 (130 turns), not attributed
- beside 3.40: session 9608d81c $0.00 (67 turns), not attributed
- beside 3.40: session d33ee273 $0.00 (143 turns), not attributed
- beside 3.40: session f9a53eae $0.00 (89 turns), not attributed
- beside 3.40: session 9539ecde $0.00 (155 turns), not attributed
- beside 3.40: session 0b73af8e $0.00 (208 turns), not attributed
- beside 3.40: session 3f408d86 $0.00 (191 turns), not attributed
- beside 3.40: session 7f7d28c2 $0.00 (112 turns), not attributed
- beside 3.40: session a98eb27f $0.06 (57 turns), not attributed
- beside 3.40: session 20b494d8 $0.10 (144 turns), not attributed
- beside 3.40: session 4d2c2011 $0.06 (111 turns), not attributed
- beside 3.40: session 1eaa1141 $0.12 (174 turns), not attributed
- beside 3.40: session d8e4a260 $0.27 (280 turns), not attributed
- beside 3.40: session ca597773 $0.12 (175 turns), not attributed
- beside 3.40: session 31268faf $0.16 (208 turns), not attributed
- beside 3.40: session 9dcf0c07 $0.06 (118 turns), not attributed
- beside 3.40: session 44a6f67f $0.11 (196 turns), not attributed
- beside 3.40: session cb9c11be $0.20 (220 turns), not attributed
- beside 3.40: session 6bade995 $0.09 (138 turns), not attributed
- beside 3.40: session 7b563ebe $0.10 (164 turns), not attributed
- beside 3.40: session c92ae99e $0.17 (227 turns), not attributed
- beside 3.40: session 4fcba92b $0.09 (126 turns), not attributed
- beside 3.40: session 829f3c15 $0.07 (114 turns), not attributed
- beside 3.40: session 050d7c02 $0.10 (150 turns), not attributed
- beside 3.40: session c965cf09 $0.07 (146 turns), not attributed
- beside 3.40: session a61bec12 $0.15 (193 turns), not attributed
- beside 3.40: session cb8f273d $0.10 (166 turns), not attributed
- beside 3.40: session d0f07e1a $0.06 (80 turns), not attributed
- beside 3.40: session 08dd0cf4 $0.10 (160 turns), not attributed
- beside 3.40: session 8d71ddb1 $0.10 (156 turns), not attributed
- beside 3.40: session 01344495 $0.10 (180 turns), not attributed
- beside 3.40: session a64b7b53 $0.09 (158 turns), not attributed
- beside 3.40: session c6383190 $0.13 (181 turns), not attributed
- beside 3.40: session cb382425 $0.10 (169 turns), not attributed
- beside 3.40: session c603df0a $0.07 (136 turns), not attributed
- beside 3.40: session 242cdd9e $0.06 (98 turns), not attributed
- beside 3.40: session cf0d170d $0.12 (201 turns), not attributed
- beside 3.40: session 08cc300b $0.07 (130 turns), not attributed
- beside 3.40: session 72bc4868 $0.08 (136 turns), not attributed
- beside 3.40: session 8cda9c35 $0.13 (190 turns), not attributed
- beside 3.40: session 89e6dd6e $0.15 (188 turns), not attributed
- beside 3.40: session 0be551f1 $0.04 (92 turns), not attributed
- beside 3.40: session 4cb386e2 $0.06 (117 turns), not attributed
- beside 3.40: session 91d84bcd $0.11 (175 turns), not attributed
- beside 3.40: session 42390626 $0.07 (140 turns), not attributed
- beside 3.40: session 595e323e $0.10 (158 turns), not attributed
- beside 3.40: session 4674e29c $0.13 (194 turns), not attributed
- beside 3.40: session 6b2f6fd4 $0.09 (131 turns), not attributed
- beside 3.40: session ba8aa730 $0.08 (121 turns), not attributed
- beside 3.40: session cabb8d2a $0.24 (308 turns), not attributed
- beside 3.40: session f39e7e2c $0.14 (161 turns), not attributed
- beside 3.40: session d1a77a44 $0.14 (192 turns), not attributed
- beside 3.40: session 942bbe75 $0.09 (136 turns), not attributed
- beside 3.40: session 042600d9 $0.08 (135 turns), not attributed
- beside 3.40: session 087ddae1 $0.12 (183 turns), not attributed
- beside 3.40: session a689f5bd $0.12 (162 turns), not attributed
- beside 3.40: session fbd49785 $0.09 (113 turns), not attributed
- beside 3.40: session 5b2a8e98 $0.10 (133 turns), not attributed
- beside 3.40: session 8495b2a7 $0.11 (138 turns), not attributed
- beside 3.40: session fc9c5d61 $0.08 (147 turns), not attributed
- beside 3.40: session 784efa88 $0.09 (133 turns), not attributed

| file (read) | chars | n |
|---|---|---|
| restruct.py | 122.9k | 37 |
| PHASE_PLAN.md | 86.6k | 5 |
| plan.txt | 83.5k | 8 |
| api_agent.py | 74.1k | 10 |
| TASK_PROGRESS.md | 66.5k | 8 |
| T2.progress1.md | 43.7k | 3 |
| type_census.py | 39.0k | 16 |
| CHANGES.md | 38.5k | 13 |
| lever_census.py | 34.2k | 3 |
| T2.md | 30.7k | 3 |
| file (write) | chars | n |
|---|---|---|
| restruct.py | 55.4k | 31 |
| PHASE_PLAN.draft.md | 27.3k | 18 |
| phase-3.40-replan2.md | 20.0k | 14 |
| TASK_PROGRESS.md | 19.3k | 5 |
| retriever-t9-uncracked-walls.md | 18.1k | 2 |
| T2.md | 10.6k | 14 |
| lane.py | 10.2k | 2 |
| ledger_backup.py | 9.4k | 1 |
| result kind | chars | n |
|---|---|---|
| bash other | 7.0M | 5257 |
| Read | 1.3M | 316 |
| tools/plan_edit.py | 863.3k | 77 |
| Grep | 580.5k | 275 |
| tools/restruct.py | 477.2k | 191 |
| run.sh | 471.8k | 543 |
| tools/type_census.py | 301.7k | 140 |
| tools/delever_search.py | 181.3k | 177 |
| tools/commit_task.sh | 176.4k | 155 |
| tools/pa_ext.py | 139.9k | 178 |
- spilled: 4 results, 781.3k chars on disk, 0 read whole
- whole reads over 20.0k: 0
- seed floor: retriever-code 6,571 (n 13, prev 5,601) · retriever-digest 6,783 (n 10, prev 5,420) · retriever-web 4,630 (n 1, prev —)
- outline credit: 92 outlines · 21 followed by a ranged read · 1.6M chars credited
- warm pings: 203 pings over 27 runs, 52 warmed waits over the TTL, rewrites across warmed waits 0, waits past the cap 2, cost: pings $3.9631 + relay $0.0000 + re-arm $0.0000 = $3.9631 vs rewrites replaced $32.9679, cheaper than one rewrite: yes, undelivered 0
- toasts by cause (waiting): question 3, review 0, replan 0, permission 0, input 66, crash 5, idle 0, stop 0, subagent-stop 0, model 0, other 0
- router turns by cause: loop 5162, relay 0, re-arm 38, other 82, relay cost $0.0000
- retriever re-asks: 4 of 20 retriever briefs repeat a lookup of the same run
- noise: 445 lines 33.1k chars — usage: : 257 lines/17.2k, No such file or directory: 186 lines/15.8k, warning: in the working copy of: 2 lines/80
- price: read $0.20/Mtok · 1h write $7.94/Mtok · output $19.85/Mtok (phase model mix)
- median requests after a read: 3
- carry/request: 1474 chars, 8739 requests (prev 1131 chars, 2525 requests, growth 30.3%)
- flag: carry per request grew 30% vs 3.39
- flag: 5 whole-plan reads by main, pa-claude, pa-planner
- flag: 110 tool-source reads by pa-claude, pa-coder, retriever-code, retriever-digest
  /home/musashi/bfm-decomp/tools/restruct.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  8.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  9.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  5.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  582 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  582 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  5.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  402 chars  retriever-code
  /home/musashi/.claude/pa3/CHANGES.md  1.1k chars  pa-claude
  /home/musashi/bfm-decomp/tools/lever_census.py  21.3k chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  2.3k chars  pa-claude
  /home/musashi/.claude/pa3/CHANGES.md  4.2k chars  pa-claude
  /home/musashi/.claude/pa3/CHANGES.md  4.2k chars  pa-claude
  /home/musashi/bfm-decomp/.claude/skills/tools-edit-kit-corpus/SKILL.md  813 chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  15.2k chars  pa-claude
  /home/musashi/bfm-decomp/tools/pa_ext.py  2.5k chars  pa-claude
  /home/musashi/.claude/pa3/CHANGES.md  749 chars  pa-claude
  /home/musashi/.claude/pa3/CHANGES.md  1.8k chars  pa-claude
  /home/musashi/bfm-decomp/tools/restruct.py  9.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  753 chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  2.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  18.1k chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  1.7k chars  pa-claude
  /home/musashi/bfm-decomp/tools/api_agent.py  8.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_agent.py  13.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_agent.py  8.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_agent.py  13.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_agent.py  8.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_agent.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_agent.py  8.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_agent.py  2.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_agent.py  7.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_agent.py  1.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/api_draft.py  2.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  3.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  3.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  3.7k chars  retriever-digest
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/cse.c  1.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/cse.c  367 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  513 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/.claude/skills/tools-edit-kit-corpus/SKILL.md  813 chars  retriever-code
  /home/musashi/bfm-decomp/tools/delever.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/.claude/skills/tools-edit-kit-corpus/SKILL.md  813 chars  retriever-code
  /home/musashi/bfm-decomp/tools/delever.py  1.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct_cycle.sh  10.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/audit_public.py  2.8k chars  retriever-code
  /home/musashi/bfm-decomp/tools/audit_public.py  2.9k chars  retriever-code
  /home/musashi/.claude/pa3/CHANGES.md  2.3k chars  pa-claude
  /home/musashi/.claude/pa3/CHANGES.md  974 chars  pa-claude
  /home/musashi/.claude/pa3/CHANGES.md  974 chars  pa-claude
  /home/musashi/bfm-decomp/tools/restruct.py  1.5k chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  1.3k chars  pa-claude
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.0k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  865 chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  360 chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  4.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  3.0k chars  pa-coder
  /home/musashi/bfm-decomp/tools/restruct.py  1.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  654 chars  pa-coder
  /home/musashi/bfm-decomp/tools/psyq_integrate.py  799 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.9k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  492 chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  3.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  4.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  4.1k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  6.7k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  2.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/restruct.py  694 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  3.3k chars  retriever-code
  /home/musashi/bfm-decomp/tools/twin_rescan.py  3.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  4.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  2.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/struct_twins.py  3.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  976 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  976 chars  retriever-code
  /home/musashi/bfm-decomp/tools/type_census.py  1.2k chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/cse.c  2.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/sched.c  6.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/sched.c  2.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/local-alloc.c  1.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/local-alloc.c  1.6k chars  pa-coder
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/local-alloc.c  2.8k chars  pa-coder
  /home/musashi/bfm-decomp/tools/lever_census.py  7.6k chars  retriever-code
  /home/musashi/bfm-decomp/tools/lever_census.py  5.4k chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/local-alloc.c  773 chars  retriever-code
  /home/musashi/bfm-decomp/tools/reference/gcc-2.7.2/local-alloc.c  1.5k chars  retriever-code
  /home/musashi/bfm-decomp/tools/delever_oracle.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/cc1_dumps_tu.sh  2.1k chars  pa-coder
  /home/musashi/bfm-decomp/tools/delever_search.py  3.2k chars  pa-coder
  /home/musashi/bfm-decomp/tools/delever_search.py  1.1k chars  pa-coder
  /home/musashi/.claude/pa3/CHANGES.md  1.7k chars  pa-claude
  /home/musashi/bfm-decomp/tools/restruct.py  2.9k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  4.4k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  1.3k chars  pa-coder
  /home/musashi/bfm-decomp/tools/struct_twins.py  2.5k chars  pa-coder
  /home/musashi/bfm-decomp/tools/type_census.py  7.3k chars  pa-coder

## Agent runs
- T4 | pa-claude | partner | claude-opus-5-5 | medium | ctx 134k | $5.067 | saved $13.88 | completed | parent a4742bc1
- T1 | pa-expert | expert | claude-opus-5-5 | medium | ctx 119k | $3.284 | saved $0.20 | completed | parent a4742bc1
- T2 | pa-expert | expert | claude-opus-5-5 | high | ctx 239k | $10.964 | saved $4.14 | completed | parent a4742bc1
- T2 | pa-coder | coder | claude-opus-5-5 | medium | ctx 55k | $0.965 | saved - | completed | parent ad22d983
- T2 | pa-coder | coder | claude-opus-5-5 | medium | ctx 64k | $1.576 | saved - | orphaned | parent ad22d983
- T2 | pa-coder | coder | claude-opus-5-5 | medium | ctx 66k | $1.655 | saved - | completed | parent ad22d983
- T2 | pa-coder | coder | claude-opus-5-5 | medium | ctx 129k | $3.244 | saved $1.27 | completed | parent ad22d983
- T2 | pa-expert | expert | claude-opus-5-5 | high | ctx 62k | $0.936 | saved - | interrupted | parent a4742bc1
- T2 | pa-expert | expert | claude-opus-5-5 | medium | ctx 111k | $2.601 | saved $3.07 | completed | parent a4742bc1
- T2 | retriever-digest | retriever | claude-haiku-5-5 | medium | ctx 67k | $0.021 | saved - | completed | parent a392f0f2
- T2 | pa-planner | planner | claude-opus-5-5 | high | ctx 92k | $2.013 | saved $3.52 | completed | parent a1ce9181
- T2 | retriever-code | retriever | claude-haiku-5-5 | medium | ctx 60k | $0.021 | saved - | completed | parent ab5a3773
- T2 | retriever-code | retriever | claude-haiku-5-5 | medium | ctx 45k | $0.014 | saved - | completed | parent ab5a3773
- T3 | pa-expert | expert | claude-opus-5-5 | medium | ctx 148k | $4.014 | saved $6.98 | completed | parent a4742bc1
- T3 | pa-coder | coder | claude-opus-5-5 | medium | ctx 126k | $3.572 | saved - | completed | parent a6182af3
- T3 | pa-coder | coder | claude-opus-5-5 | medium | ctx 45k | $0.571 | saved - | completed | parent a6182af3
- T3 | pa-coder | coder | claude-opus-5-5 | medium | ctx 119k | $3.092 | saved $0.18 | completed | parent a6182af3
- T4 | pa-expert | expert | claude-opus-5-5 | medium | ctx 102k | $2.823 | saved - | completed | parent a4742bc1
- T4 | pa-claude | partner | claude-opus-5-5 | medium | ctx 67k | $0.919 | saved - | completed | parent a4742bc1
- T5 | pa-claude | partner | claude-opus-5-5 | medium | ctx 83k | $1.706 | saved - | completed | parent a4742bc1
- T5 | retriever-digest | retriever | claude-haiku-5-5 | medium | ctx 40k | $0.013 | saved - | completed | parent a0bf0633
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 86k | $2.381 | saved $8.08 | completed | parent a0bf0633
- T5 | pa-coder | coder | claude-opus-5-5 | medium | ctx 84k | $2.017 | saved $1.00 | completed | parent ae95ad70
- T11 | pa-claude | partner | claude-opus-5-5 | medium | ctx 151k | $4.537 | saved $5.93 | completed | parent a4742bc1
- T5 | pa-expert | expert | claude-opus-5-5 | medium | ctx 67k | $0.878 | saved - | completed | parent a4742bc1
- T6 | pa-expert | expert | claude-opus-5-5 | medium | ctx 74k | $1.172 | saved $5.03 | completed | parent a4742bc1
- T6 | retriever-digest | retriever | claude-haiku-5-5 | medium | ctx 17k | $0.005 | saved - | completed | parent a9545e29
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 108k | $2.186 | saved $4.71 | completed | parent a9545e29
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 72k | $1.339 | saved $0.24 | completed | parent a9545e29
- T6 | pa-coder | coder | claude-opus-5-5 | medium | ctx 107k | $2.104 | saved - | completed | parent a9545e29
- T7 | retriever-digest | retriever | claude-haiku-5-5 | medium | ctx 33k | $0.010 | saved - | completed | parent a53f27fc
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 265k | $10.462 | saved $17.08 | completed | parent a53f27fc
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 36k | $0.477 | saved - | completed | parent ab508551
- T7 | pa-expert | expert | claude-opus-5-5 | medium | ctx 68k | $1.314 | saved $2.69 | completed | parent a4742bc1
- T7 | pa-coder | coder | claude-opus-5-5 | medium | ctx 66k | $0.854 | saved - | completed | parent ab69a93f
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 71k | $1.415 | saved - | completed | parent a5b87281
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 209k | $5.710 | saved - | completed | parent a5b87281
- T8 | pa-coder | coder | claude-opus-5-5 | medium | ctx 111k | $2.606 | saved $0.34 | completed | parent a5b87281
- T8 | pa-expert | expert | claude-opus-5-5 | medium | ctx 77k | $1.292 | saved $13.92 | completed | parent a4742bc1
- … 126 more: PY ~/.claude/pa3/pa_ledger.py report

## Discussions
- D1 | cant push: 100MB+ .run ledger/census blobs in unpushed commits | open
- I2 | -> 3.45 License: developer wants no commercial reuse (free community mods OK, selling not). Recommended CC BY-NC-SA 4.0 | deferred:3.45

## Deferred
- T16 | superseded — ledger backup at phase close: stripped public copy and full archive copy
- from T21: the three tool bugs above (type_census write_parked, struct_twins default dir, lift_types --fold tail) are unfixed candidates for a tools task. (unconsumed)
- from D1: ledger shard/snapshot + pre-commit size/ignored-path guard → 3.40 planner
- I2 (deferred:3.45): -> 3.45 License: developer wants no commercial reuse (free community mods OK, selling not). Recommended CC BY-NC-SA 4.0

## Changes
- 2026-10-14 router: T1 next -> done
- 2026-10-15 partner: T2 next -> done — T2 work complete and green (63fc7e8bf6); blocked only on the judgment clause, answered by the developer 2026-10-15 (95% band, REPLAN.md)
- 2026-10-15 partner: added T16 — ledger backup at phase close: stripped public copy and full archive copy
- 2026-10-15 router: T3 next -> done
- 2026-10-15 partner: T16 queued -> superseded — duplicate of T15: my 2026-10-14 add-task landed late, after the REPLAN already carried it as T15
- 2026-10-16 planner: added T17 — drift types: decide the TNC map types the T4/T5 sweeps' census regrouping created, all segments
- 2026-10-16 router: T4 and T5 done-when amended (T4 question, 2026-10-16): their 'no site keeps TYPE-NOT-CANONICAL' clause covers band and tail types only (band TNC 0, tail under TYPE-BELOW-BAND); TNC sites on drift types (map types in no row of tnc_band.tsv or type_folds.tsv, created by the sweeps' census regrouping) go to the new drift task after T5, which owns the fleet TNC 0 check. T5's verify grep for TYPE-NOT-CANONICAL is therefore met at the drift task; T5 checks it on band types only and states its drift count.
- 2026-10-16 router: T4 next -> done
- 2026-10-16 partner: T14 done-when amended (developer 2026-10-15): also carry retrospective §7's after-100% 'sooner' lessons (Phases 35-40) into docs/how-to-ai-decomp/03-bootstrap-order.md as a from-the-start section on reducing post-100% work (canonical types during matching, declarations before pins, debt chart from phase one), with pointers back to §7; doc_links --strict 0/0
- 2026-10-16 router: T5 next -> done
- 2026-10-16 router: T6 next -> done
- 2026-10-17 partner: T7 question 2026-10-17: T7 may edit tools/restruct.py s_macro_rows (~:1242) so a KEPT entry whose base differs only by local:X vs param:X (same name, same off, same KEPT class) backs the site; follow tools-edit-kit-corpus (kit-corpus, tools-health). Source respelling of the 5 CAST_SIGN sites not taken.
- 2026-10-17 router: T7 next -> done
- 2026-10-17 router: T8 next -> done
- 2026-10-17 router: T9 next -> done
- 2026-10-17 partner: T10 next -> done — pilot done-when met; projection returned blocked as planned; developer chose (a)
- 2026-10-17 partner: T10 ruling 2026-10-17, developer chose (a): T11 runs the full singleton wave at the 4-coder cap, 20-30 min per function, per-coder scratch prefix; instruction rows and the func_80188C04 family (11 fns) parked with cause; every survivor's row names its compiler wall. Milestone amendment (literal strict 0 -> survivors walled) via REPLAN.md.
- 2026-10-21 partner: T11 next -> queued — Developer 2026-10-21: the one-time cookbook banking task runs before T11; T11 paused, back in line
- 2026-10-21 partner: T14 done-when addition 2026-10-17 (developer): docs/how-to-ai-decomp/03-bootstrap-order.md post-100% section also states (1) a lever is allowed at match time only with its compiler wall and moves tried recorded then (as 3.40's survivor rule), (2) names only with evidence (role obvious from code, fields confirmed in more than one function); placeholders otherwise. doc_links --strict 0.
- 2026-10-21 partner: T14 done-when addition 2026-10-17 (developer): docs/wiki/Start-a-new-decomp-project.md, docs/wiki/How-to-AI-decomp.md and docs/how-to-ai-decomp/03-bootstrap-order.md state as rules for new projects on this workflow: (1) structs as you go: agents look up and extend the canonical struct before writing any raw cast; (2) pure C by default: a lever only with its compiler wall and moves tried recorded at match time; (3) best-guess names from the start under a guess prefix with a names ledger row (basis, confidence), promoted to a plain name on evidence and renamed as the picture grows. Each rule cites the 3.35-3.40 cost that motivates it (retrospective section 7). doc_links --strict 0.
- 2026-10-21 partner: T14 addition 2026-10-17: the new-project naming rule uses the guess_ prefix (docs/gen3-standards.md rule 1 as amended, fe8028d960); T14 also aligns decomp-architect/decomp-architect.md:300 and decomp-architect/intake.decomp.md:174 ("unnamed beats wrong") with it.
- 2026-10-21 partner: T14 addition 2026-10-17 (developer): the new-project rules also include (4) comment as you go: at match/crack time the agent writes a short header comment (what the function does, guesses marked as guesses, why any odd spelling or lever exists); comments are overwritten freely as understanding grows, git keeps history.
- 2026-10-21 router: Developer 2026-10-21: every coder (crack shards, banking, all later tasks whatever their coder: field says) runs on openrouter-deepseek/deepseek at max effort until the developer says otherwise; no escalation to Opus or Haiku: a failed run or wall is listed with its evidence and held for the developer's approval. pa.json external: coder openrouter-deepseek/deepseek, escalate none.
- 2026-10-21 router: Developer 2026-10-21, supersedes the line above: function-cracking coders (the bulk per-function crack work, such as T11's crack shards and any later crack wave) run on openrouter-deepseek/deepseek at max effort only; all other coder work (banking and gates, tools, docs, sweeps) stays on the in-house coder named in coder:. No escalation of a crack to Opus or Haiku: a failed run or wall is listed with its evidence and held for the developer's approval. pa.json external: default coder in-house, escalate none.
- 2026-10-21 router: Developer 2026-10-21: DeepSeek crack coders run at the default high effort, never max; this replaces 'max effort' in the line above. pa.json external effort: default.
- 2026-10-21 router: Developer 2026-10-21: function-cracking coders run on openrouter-minimax/minimax (minimax/minimax-m3.1-flash:free) at the default high effort, replacing openrouter-deepseek/deepseek in the lines above; DeepSeek is not used (lane 0). Everything else in those lines stands: banking and other coder work in-house, no Opus/Haiku escalation, walls held for the developer.
- 2026-10-21 planner: added T21 — Bank the waiting cookbook lessons (one time, PA3 3.30)
- 2026-10-21 router: T21 queued -> next — Developer: run the one-time cookbook banking task now, before T11
- 2026-10-21 router: T21 next -> done
- 2026-10-22 router: Cracking coders (T11 and later crack waves) switch from openrouter-minimax/minimax to openrouter-deepseek/deepseek at high effort, one lane until learning mode lifts (free MiniMax retired 2026-10-22; developer).
- 2026-11-06 router: T11 next -> done
- 2026-11-06 router: T12 next -> done
- 2026-11-07 Claude: T17: residue rc-1 clause (1 unbacked CAST_NONSTRUCT func_8012E364__6d96fc6c.h:21, 3 lying decls func_80026514/func_800268D0/func_800CBA44) is T18 scope; T18's fix satisfies it. T17 runs one mini round on the 6 drift sites (Unkstruct_8a49cd6b, Unkstruct_c758f14a).
- 2026-11-07 router: T17 next -> done
- 2026-11-07 router: T18 next -> done
- 2026-11-07 router: T19 next -> done
- 2026-11-07 router: T20 next -> done
- 2026-11-07 router: T13 next -> done
- 2026-11-07 router: T15 next -> done
- 2026-11-07 router: T14 next -> done

## Plain-English Recap
Phase 3.40 gave the struct types left undecided after 3.39 their single agreed definitions, and made every remaining compiler hint justify itself. A compiler hint here means a pin (forcing a value into a specific register) or a piece of inline asm. Undecided struct-type cast sites (TNC) went from 291,819 to 0, counting both the planned band and the "drift" types the sweeps created. The rare tail is recorded under its own cause, TYPE-BELOW-BAND: 5,871 sites, under the frozen cap of 6,976. Disagreeing function declarations went from 11 to 0, and 162 pins became declared parameters. A DeepSeek crack wave freed 220 functions of their hints, and 18 shared head classes cracked and were copied into every overlay that uses them. Hint sites went from 3,364 to 1,853, and ledger rows from 2,433 to 1,180. Every surviving row now names its wall, the gcc pass plain C cannot steer, from the vocabulary in config/lever_walls.tsv, and lever_census enforces it. The milestone gate passed in full at aace727c4c from a clean tree: check-casts --residue rc 0 (lying 0, unbacked 0, uncovered 0), check-structs OK, strict lever census OK (unwalled 0), lever_census --check 0 unmarked, R22 218/218, tools-health OK. Ledger backups (tools/ledger_backup.py), story §10, retrospective §7, the wiki and the graphs are done. Open items: the developer pushes the archive clone (one commit ahead); the census does not detect return-type lies (e.g. func_8016130C has 1,213 void declarations against an s32 definition; C0543); the public delever copy drops the C before/after text (the archive keeps it); three tool bugs from T21 (type_census --no-cache crash, struct_twins' stale default census, lift_types --fold's leftover comment); 9 expand-hardreg-var tags from T20 need a second look; func_80177B5C stays a lever by choice.
