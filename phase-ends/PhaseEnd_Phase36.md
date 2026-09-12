# PhaseEnd — Phase 36: Levers off — every compiler-forcing construct out of the matched C, to its measured floor
**Date:** 2026-09-11 · **Project Version:** 2.2.0 · **Phase Status:** Complete (milestone as AMENDED at S104, confirmed by Drew at gate 2 — 2026-09-11, "confirmed for phaseend") · **Generation:** Gen3 (the second phase; Drew's order dedup → **pins** → structs → names)

> Chartered at gate 1 (S97, 2026-09-09, plan mode, Max) from `docs/gen3-handoff.md` §5–§7 and `docs/gen3-standards.md`, widened by
> Drew at the gate from "pins off" to **every lever class** — register pins, `asm` statements of every kind (barriers, launders,
> keep-alives, hand-placed instructions, the GTE coprocessor idiom), volatile levers, bare `register` — with decision 2 "grind to zero"
> and the marking rule "ban the silence, not the lever". Ran **nine sessions (S97–S105, 2026-09-09 → 2026-09-11)** and **575 commits**
> (`63b886626..db212f167` on the baseline `e6d98dd1d`, Drew's P35 close; 320 of them are single-function banks through the whole-object
> gate). The granular trail — every batch's verify line, every agent landing with its pass and `file:line`, every instrument defect
> with its cause — is at **`phase-ends/logs/Phase36.md`** (R19, on demand; ≈3,300 lines). Owner decisions (Drew): gate 1's three forks
> (scope A–D now, E–G deferred; grind to zero; byte-needed `volatile`/`register` kept unmarked and ledgered) and the verbatim
> confirmation; T1b (the in-function verbatim form, "confirmed per your recommendations"); T7's start rule ("dont start ultra code wave
> for reshaping without my direct approval"); the T7 operating procedure ("always have an agent running … prove the rule, harvest the
> idiom, start a new agent"); the burst of 20; the cap 5 → 2 → 1 → none; the S104 rulings read against sotn-decomp (do-while and dead
> initialisers stay as marked ordinary C; GTE deferred; every site reducible to C, the unclosed ones carried to the structs phase — the
> **milestone amended** from "0 pins, 0 asm" to "every survivor marked, counted, attributed and named for the structs phase"); the
> S105 close ("confirmed per your recommendation. wait for the last agent to finish, then do all the things and no more agents this phase").

## Build Log

**The phase in one line:** the census found **53,234** compiler-forcing sites (37,720 register pins + 15,514 asm statements) in 15,679
matched function bodies; a deterministic ladder — a byte oracle on the build's own recipes, a mechanical strip, the GTE header, shape
recipes, a permuter rung, a guided search — and then one-agent-per-translation-unit readings of the compiler's own source took them to
**4,010** (2,141 pins + 1,869 asm in 1,980 bodies, −92.5 %), every step proven by the 218 hashes from a clean rebuild, every survivor
marked with the compiler pass that needs it and the instrument that judged it, and the remainder bucketed by what it needs (a signature,
a struct, a carve, a GTE macro decision) for the structs phase.

**Files created/changed and complete — do not recreate** (category summaries; the per-commit list is `git log e6d98dd1d..db212f167` and
the archived log):

- **The instruments (T1–T3, extended through T7).** `tools/lever_census.py` (the self-asserting census: every `asm`/`register`/
  `volatile`/`__builtin_*`/`__attribute__` token roled once, per-line coverage against the raw text, four known-true controls keyed on
  their T1 hashes, the `// !FAKE:` split, orphan-marker detection, cross-file macro names, the src stamp, `--check` / `--check --strict`,
  `--sites`, `--selftest`; a `make tools-health` rung since T8); `tools/delever_oracle.py` (every object's exact build command captured
  once by `make -n -W`, candidates compiled IN PLACE with the output redirected, whole-object byte equality against the fleet run's
  object; `--calibrate` 177/177 + a positive control; COMPILE-CRASH apart from COMPILE-ERROR, R103; `--snapshot-baseline` — the baseline
  under `.run/P36/delever/baseline/`, so a clean fleet rebuild can run beside scoring agents); `tools/delever.py` (the engine: positional
  rewrites per lever class with a token-mismatch REFUSAL, rung A strip-all, rung B greedy, the file as the write unit and its final
  compile as the proof, the ledger keyed by body hash before/after, `inflight.json` as the only restore (R102), `--scrub`, `--apply-body`,
  `--propagate` (class remap by address, the allowance derived from the exemplar's surviving markers), `--port-scan`, `--recipes` (rung
  R, TU-parallel), `--repair-nhash`, `--selftest`; **the generator registry R2–R46** — every family with a selftest fixture and a
  known-true run on the body it came from); `tools/delever_cycle.sh` (the unattended batch cycle with FINISH and REDRAW modes, the stale
  `.git/index.lock` wait); `tools/gte_consolidate.py` (T5: the signature engine on the build's own tail, one canonical text per
  signature, Sony's names, lever variants `_m`/`_v`, `--sweep`, `--remark`); `tools/delever_permute.py` (rung D: the permuter on a
  lever-free draft with the tree's own body as `target.o` and a positive control); `tools/delever_search.py` (rung G: the object-scored
  beam search with a reloc-masked edit distance, the residual classifier, `--explain`, `--try` — the agents' scorer, per-function scratch,
  parallel-safe); `tools/delever_regen.py` (the read-only regen of newly harvested families over the whole residue, forked worker
  processes, `--bank`); `tools/delever_pack.py` (the agent packs: `neighbours.txt`, `related.txt`, `best_body.c`, `ORDER.tsv`);
  `tools/argcheck.py` + `tools/decl_repair.py` (S102: the lying call declarations — 16,759 repaired byte-identically across 3,439 units;
  K&R definitions read since S103); `tools/localalloc_sim.py` (c26's local-alloc simulator, promoted after 0 mismatches over 150 blocks;
  the three-quantity switch modelled at S104); `tools/alloc_table.py` (gcc's truncated integer priority, TIE flags); `tools/cc1_dumps_tu.sh`
  (`-dt -dJ -dd`, `-Isrc/shared`, takes a `.c`); `tools/lever_progress.py` + `docs/levers.md` + `docs/lever-progress.tsv` (the series, 78
  milestone rows, rendered as state transitions); `tools/readability_progress.py` + `docs/readability.md` + `docs/readability-progress.tsv`
  (the second Gen3 series); `tools/verbatim_check.py` (the in-function form, `--update` keeping order and UTF-8, `--strict` in tools-health).
- **The tree.** `include/gte_inline.h` (50 GTE macros under Sony's names for what were 9,102 per-TU definitions; 8,951 deleted, 629 of
  699 `"memory"`-clobber variants proven byte-neutral and dropped, 70 kept as marked `_m` levers; 575 direct GTE statements as
  canonical calls); `config/verbatim_manifest.json` (49 rows: 27 PERMANENT-VERBATIM incl. the 22 per-overlay scratchpad stack-switch
  trampolines the file-scope detector never saw, 8 SDK-VERBATIM libgs renderers, 11 DECOMPILE-NOW, 3 UNCERTAIN — T1b's finding that "every
  game-code function is C" had been measured by file-scope instruments); **`src/`: 53,234 → 4,010 lever sites** — the survivors marked
  `// !FAKE: <kind> <detail> — <pass, file:line> (P36 <rung|agent>)`, 2,693 files' stale `@stuck:` header notes retagged `@unstuck(P36):`
  (30,138 notes, comment-only), 16,759 call declarations made honest, four `do { } while (0)` and dead-initialiser fakes marked per sotn's
  rule; the ledger `.run/P36/delever/ledger.jsonl` (one row per judgement, the rung, the calibration id, every site's verdict).
- **The record.** Cookbook **§454** (rungs D/R: the instrument lessons — a disassembly is not a target), **§455** (rung G, the object-scored
  search), **§456** (S104's move catalog under ~205 levers), **§457** (S105's catalog: the loop family, cse's address fold, sched1's
  birthing boost in both directions, combine's narrow-load split, local-alloc arithmetic, the parameter shapes), §197-A superseded;
  `docs/decision-log.md` P36 S99 / S101 / S104 / S105; `docs/accelerators.md` P36 S99 / S101 / S105; `.run/P36/agents/METHOD_S103.md`
  (the agents' method, steps 1–25, every emitter and register-order move with its `file:line`); `docs/SETUP.md` P36 rows for every tool;
  the wiki (`Where-the-project-goes-next` item 2 + the table row) and the Gen3 charter pages date-stamped; `docs/tool-index.md` + the kit
  corpus regenerated; `config/kit_coverage_map.tsv` (the P36 accelerator entries dispositioned); 333 agent packs with `mechanism.md`.
- **Evidence (`.run/P36/`, allowlisted text):** `baseline/` (every R22 log), `census/`, `probe/`, `delever/` (batch records, apply logs,
  the calibration), `permuter/`, `engine/` (run logs, outcomes, traces, `residual_moves.md` — lane B's 58-row residual → source-move map
  with its verification ledger), `regen/`, `s103/` `s104/` `s105/` (per-session R22 logs, bank lists, known-true candidates, the picker,
  the briefs, `attribution_check.py`, `unstrippable.json`, the tools-health logs), `agents/` (the packs).

**Tools/packages installed:** none external (no apt/pip). `tools/reference/sotn-decomp` shallow-cloned (ignored; X2 — data) at S104 to
read Drew's four questions against its tree (R106).

**Verification results (literal, at close — S105, HEAD `db212f167`, tree clean):**
- R22 from clean after the last `src/` change (`fe4a62420`, the comment-only retag): `extract-all: 217 extracted, 0 failed of 217 (+ main,
  serial)` · **`check-all: 218 passed, 0 failed of 218`** · `real 1m27.146s` · `exit=0` (`.run/P36/s105/r22_l.log`); every batch of the phase
  — 15 T4 batches, 3 T5 batches, every rung-D/R/G run, every agent bank — carried the same line.
- **`lever_census --check: 4,010 pin/asm sites, 4,010 marked !FAKE, 0 UNMARKED — OK`** (exit 0; orphans 0; GTE levers 450 inside the
  number; `--strict` NOT claimed — by the S104 amendment "0 pins, 0 asm" is the structs phase's finish line). `verbatim_check --strict`:
  no drift (49 rows).
- **`make tools-health: OK — sigs fresh; corpus(+resident) + cdecl + binaries + report(lint+dedup) + cookbook-index all green.`** (run 4,
  `.run/P36/s105/tools_health_t8d.log`; the new rung inside it; S1 10,180 / 10,180, 0 violations; sdk-dual OK; kit_coverage OK; runs 1–3
  were red on the day's own record — three Reference-index rows, one kit_lint LEAK, two undispositioned accelerator entries — each fixed).
- **Attribution (milestone item 2):** `.run/P36/s105/attribution_check.py` → `4026 counted lever sites, 4026 attributed {rung B 2,620 ·
  S103 933 · T5 450 · S105 22 · S104 1}, 0 without an instrument` (measured at 4,026, before f11's last 16 rung-B sites came off).
- Published (R75): README line 30 `Levers off (Phase 36, snapshot 2026-09-11): 2,141 register pins and 1,869 asm statements remain in
  1,980 functions (674 distinct bodies), 4,010 of them marked …`; `docs/progress.json` `counts.levers`; `docs/levers.md` (78 rows,
  `lever_progress --check: OK`); `docs/readability.md` (33 lying declarations left in 25 pinned bodies, from 461 in 314 at S102).
- `delever --selftest: OK` · `lever_census --selftest: OK — 24 sites, 2 defs, 2 asm macros` · `share_census --selftest 7/7` · `doc_links
  --strict: OK` · `kit_lint: OK` · `kit_coverage: OK` · `tool_census --check: OK` · `cookbook-index OK (1,175 sections)`.
- The headless Ghidra MCP was never used (no RE work) and was stopped cleanly at the S105 close ("Save succeeded", R23).

**Milestone achieved (gate 2 — Drew, 2026-09-11; each item with its literal output above):** (1) as AMENDED at S104 — every surviving
register pin and asm statement outside the GTE header is marked, counted and named for the structs phase: `lever_census --check` 4,010 /
4,010 / 0 UNMARKED, the counts published with the dated snapshot, the manifest unchanged; (2) the ledger names, for every site, the rung
and the instrument that judged it — 4,026 of 4,026 attributed; (3) `check-all: 218 passed, 0 failed of 218` from clean, `make tools-health`
OK with the new rung, the GTE macros in one header (314 per-TU asm macro definitions remain, each tied to a surviving marked lever or an
`h_text` homonym — stated at T5's close, not zero); (4) the record written, this PhaseEnd, the DIGEST append, the log archived; v2.2.0.

**Next:** **Phase 37 — the structs phase** (Drew's Gen3 order; R95's canonical type layer is its core). Open a fresh session in **plan
mode, Max** (Tier 1) from `docs/gen3-handoff.md` (item 4, the types doctrine) + `docs/gen3-standards.md`, with this phase's residue as its
acceptance test: 4,010 sites = 1,548 drawable singletons (472 classes) + 691 in 24 parked classes (six signature changes with ready
patches — func_800385C0, func_80029D3C, func_80180FA4, func_80180A54, func_80188DF4, func_80183CC4, func_801A1E94/func_801A5C44, func_80035210,
func_800384A8, func_80188A30, func_8017FC5C/func_80180200, func_80185578, func_80157D20, func_80168828; the carve change func_80186CE0; the
proven-irreducible heads func_8013CF68 ×134, func_80178970 ×127 + four same-shape families, func_8013F350's head) + ~1,150 minimum-lever
survivors in five head classes (func_8013D9B0 ×125 — the `gte_stORGB` respelling question of T5; func_80177B5C, func_80140958, func_8012E364,
func_8013F350) + 450 GTE clobber variants + 94 `$4`–`$7`-only pins (the missing-parameter shape, ~158 estimated across `src/`). d10's
register-union proof (func_8017EF88), a18's `extern u16 X[]` close, f10's three type closes and f3's `s16[3]` finding are the phase's
evidence FOR the struct hypothesis; `tools/argcheck.py` (98,648 lying declarations over 1,609 callees) and the raw-cast census
(411,850 against 177,902 struct member reads) are its starting instruments. Inherited by name: the kit split, xsig v2, the §396(a)
correction owed since S104 (the refuting body was not identified — R14), the 15 remaining UNSTRIPPABLE packs (one-off instructions,
macro-carried and multi-output launders), a refusal-reason histogram for `delever_regen`, a "local vs global" column for `alloc_table`.

## Roadmap delta (what Phase 36 changed about the road ahead)

- **Gen3 item 2 is at its measured floor, and the floor has a shape.** The phase did not reach zero and says so: the last third of the
  residue is not a codegen problem the pin lane can read its way out of — it is wrong signatures (a `(void)` function that reads `$a0`, a
  `void` one that returns `$v0`), missing struct types (the compiler's own alias tests, `sched.c:837-863`, `expr.c:4568-4577`, decide by
  `MEM_IN_STRUCT_P`), carved data that a struct copy would address in one relocation, and one GTE macro spelling. Each is the structs phase's
  by construction, and the phase leaves it a list with patches, readings and byte proofs rather than a number.
- **The doctrine is written where the next project starts:** `docs/levers.md` §5 — "ban the silence, not the lever": a lever is allowed only
  marked, ledgered and published from the first bank, with a one-compile bank-time trial ("does it still match without this?") that would
  have refused 37 % of this population while the context was hot; blanket prevention would have stalled Phase 18. The kit's DK entries and
  the wiki carry it.
- **The compiler map grew by a catalog of moves with their passes** (§454–§457, METHOD steps 1–25): the loop family's biv law, cse's address
  fold and its inverse, sched1's birthing boost in both directions, combine's narrow-load split, local-alloc's arithmetic (`find_free_reg`'s
  lowest-free rule, `update_equiv_regs` doubling a constant's life, the three-quantity birth order), the call-signature class (a truncated
  declaration DELETES an instruction). Every entry names its `file:line` in gcc 2.7.2 and its byte witness.
- **What the readability series now measures for the structs phase:** the struct debt (411,850 raw cast dereferences vs 177,902 struct
  member reads) and the declaration debt (98,648 lying declarations, 33 of them still in pinned bodies).
- **Scale, honestly (R41):** the plan priced the mechanical floor at 3 sessions and called T7 "open-ended, to zero"; the phase took 9 sessions,
  575 commits, ~200 agent draws (S102 22, S103 56, S104 ~105, S105 11 TU batches of 4–7 classes) and roughly 15–20 M agent tokens across
  the three agent sessions (S105 measured ≈3.5 M for 56 classes). The mechanical rungs took 37 % of the sites for ~20 CPU-hours and no
  tokens; the search engine took another 6 % for ~5 CPU-hours and no tokens; the agents took the rest — and the closes per agent rose from
  1 (S102) to 4–7 (S104–S105) as the TU batch and the method file matured.

## Deviations

| Item | Plan (gate-1 plan) | Actual | Reason |
|---|---|---|---|
| The milestone | 0 register pins, 0 asm statements outside the GTE header (decision 2, "grind to zero") | **amended at S104 by Drew:** every surviving site marked, counted, attributed and named for the structs phase; 4,010 remain | S103/S104 read the head classes to proven irreducibility in plain C, and Drew's (c)/(d) rulings — read against sotn-decomp, which keeps `INCLUDE_ASM` stubs rather than pins — moved the unclosed sites to the structs phase |
| T7's shape | Ultracode waves (Workflow fan-out), prompted | the Agent tool, one agent per residue class, then one per TU with 4–7 classes; caps 5 → 2 → 1 → none | Drew's rule "one agent at a time so the methodology is honed at each landing" (S101), then his cap retunes; a Workflow was never the right unit for a reading |
| T6's permuter rung | the residue exemplars through the permuter, time-boxed | 5 of 16 closed (0.69 h); its two prior campaigns were the instrument (a disassembly is not a target, §454); rung R closed 134/134 of the class it found, then 0 of 300 on the residue | the permuter is a replication engine after a shape is known, not a discovery engine; the guided search (rung G) replaced it |
| Sessions | mechanical floor 3; T7 open-ended | 9 (S97–S105) | T7 was 5 of the 9 |
| The call-signature turn | not planned | `argcheck` + `decl_repair`: 16,759 lying declarations repaired byte-identically in 3,439 units (S102); R19/R25 generators | six independent agent cracks in one burst were the same class — a truncated declaration deletes an instruction the pin then faked |
| The minimum-lever bank | not planned | the S103 pivot: the best honest plain-C body plus only the marked lever(s) it cannot do without, `allow_residue`, propagation deriving the allowance from the exemplar's markers | four 130-copy classes at 4–34 levers per copy became 1–2 |
| The in-function verbatim form (T1b) | 5 PERMANENT file-scope rows | 49 manifest rows; 22 per-overlay trampolines + 8 SDK renderers + 11 DECOMPILE-NOW + 3 UNCERTAIN | the census's structural detector found what the file-scope detector never had (P9: the P32 "every game-code function is C" was blind to it) |
| Rules | R100–R106 ratified at gate 1 | R100–R106 ratified; **eleven** candidates proposed below | the phase generated governance from its instrument failures, as every phase has |
| The §396(a) correction | owed at T9 (S104) | **not written** — carried by name | the refuting body was not identified from the record; a correction needs its bytes (R14) |

## What we believed, what failed, and what we would do sooner (for the retrospective; the detail is in `docs/decision-log.md` P36)

- **Believed (gate 1):** the pins would come off mechanically, family-batched, because Phase 32's last four functions had. **The strip took
  37 % of the sites and freed 20 % of the bodies; the rest was 1,803 distinct shapes**, each a reading of a compiler pass. **Sooner:** the
  probe (T2) said exactly this on day one — price the residue by distinct SHAPES, never by bodies.
- **Believed (S99–S100):** the permuter and a recipe sweep would discover shapes. **They replicate, they do not discover** (134/134 on a
  known shape, 0/300 on unknown ones); and two permuter campaigns had scored against a disassembly that was not a target (24 wrong words
  from `move` vs `or`). **Sooner:** a known-true case — the tree's own body must score 0 — before any campaign; the guided search with the
  object as the scorer.
- **Believed (S101):** a wider search would close the head. **112,216 compiles bought 62 bodies**; the head needed readings. **Sooner:** the
  lane B map (the gcc source read for residual → move) before the wide search, and agents on the head from the first day of T7.
- **Believed (S102, the night of three agents):** one agent at a time meant one agent, then a sweep, then the next. **It meant learning
  between landings, not an empty slot** — six of eight hours had no agent running. **Sooner:** Drew's rule as written at S102: the slot is
  refilled in seconds; sweeps never stand between two agents; one writer.
- **Believed (S102–S104):** every `NO-CANDIDATE` was a property of the population. **R22 was refusing for three unrelated regex reasons for
  two sessions**, found only when agents closed by its own move and the generator was run on their start text. **Sooner:** a negative-
  control corpus per generator; refusal reasons as a histogram; the known-true run at every landing.
- **Believed (S102):** the pins were codegen. **The biggest single class was a wrong DECLARATION** — a truncated `(void)` deletes an
  instruction the pin was hired to fake; 16,759 of them were repaired in an afternoon for zero bytes. **Sooner:** `argcheck` at Phase 17
  (the canonical type layer, R95) — the same lesson the S91-b hindsight recorded, now with a number.
- **Believed (S104):** the residue could be ground to zero by more agents. **The residue's last third is signatures, structs, carves and one
  GTE spelling** — the structs phase's material; the drawable rest is singletons at ~3 sites each. **Sooner:** the bucketing that S105 did
  on Drew's "stalling?" question, done at every wave close as the stop-rule's input.
- **Cost:** the phase's real expense was the agent sessions (S102–S105, ~15–20 M tokens for ~200 draws) and the coordinator's landing
  loop; the instruments were cheap and paid every day — a calibration line after every commit, a positive control in every scorer, a
  selftest with a known-true run in every generator. The mistakes that cost the most were each a scorer that read the wrong thing (a
  disassembly, another agent's object, a stale baseline) and each was caught by a check that read the artifact rather than the intent.

## Commit Message
```
(Phase 36 landed as 575 commits 63b886626..db212f167, 2026-09-09 → 2026-09-11 (S97–S105). This close = the archived log + this
PhaseEnd + the DIGEST update + the kit's record copies, Drew's milestone-close commit, then the v2.2.0 tag.)

chore(phase-36): CLOSE — levers off to the measured floor: 53,234 → 4,010 register pins + asm statements (−92.5 %), every survivor
marked with its pass and its instrument and named for the structs phase; the GTE idiom in one header; 16,759 lying call declarations
repaired; the lever series and the readability series published; 218/218 at every step (v2.2.0)

- PhaseEnd_Phase36.md written; CURRENT_PHASE.md archived to phase-ends/logs/Phase36.md (R19); DIGEST §0/§2/§3 appended (step 3b)
- T0–T10 across S97–S105: the census (T1/T1b, 49 verbatim rows), the oracle + probe (T2), the engine + cycle (T3), the mechanical
  campaign (T4, 15 batches, −36.8 %), the GTE header (T5), rungs R/D (T6), rung G + the agent lane at caps 5→2→1 (T7, ~200 draws,
  generators R15–R46, the call-signature turn, the minimum-lever pivot), the gate rung + attribution (T8), the record (T9)
- close: check-all 218/218 from clean; lever_census --check 4,010 / 0 UNMARKED (exit 0); make tools-health OK (run 4); attribution
  4,026/4,026; tools-health, doc_links, kit_lint, kit_coverage, tool_census all OK
- rules: R100–R106 ratified at gate 1; candidates (a)–(k) proposed for Phase 37 gate 1
- v2.1.0 -> v2.2.0
```

## Rules Added This Phase

**Ratified at gate 1 (2026-09-09):** **R100–R106** (the PhaseEnd_Phase35 candidates (a)–(g)); full text in `phase-ends/DIGEST.md` §3.

**Candidates recorded in the log, for Drew to accept, modify or reject at Phase 37 gate 1 (P10):**

| Rule | Reason |
|---|---|
| **(a) Ban the silence, not the lever:** a compiler-forcing construct is allowed in a banked body only marked, ledgered and published from the first bank, with a one-compile bank-time trial of the body without it. | `docs/levers.md` §5: 37 % of 53,234 sites came off with no understanding at all once tried; the levers propagated with every family remap (1,758 distinct bodies became 12,578) because nothing ever asked. |
| **(b) A generator ships with a negative-control corpus of real bodies where it must fire, and a regen pass reports its refusal reasons as a histogram.** | R22 refused three ways for two sessions (`&&` as `&p`, the literal base, a cast store as a set); every `NO-CANDIDATE` had been read as a property of the population (accelerators P36 S105). |
| **(c) At every landing, run every registered family on the agent's START text before banking** — a close by a move the registry claims is the cheapest instrument check in the loop. | It found all three R22 defects and banked shared headers IDENTICAL on 141 objects each. |
| **(d) A scorer's target is the tree's own bytes compiled by the build's own tail, never a disassembly** — a known-true case (the tree's body scores 0) before any campaign. | Two permuter campaigns scored 28 for a byte-identical body: `objdump`'s `move` assembled as `or`, resolved `%hi/%lo` pairs (§454). |
| **(e) Scratch is keyed by the unit of work, never by a worker tag or a file** (R48 extended). | Nine burst agents shared one scratch object and two scored candidates against another agent's function; the search's `g0.o` was keyed by a worker index. |
| **(f) A gate's baseline is a snapshot, not the build directory** — a clean rebuild never runs where a live scorer reads `build/`. | `--try` scored against half-written objects during a fleet gate until `--snapshot-baseline` (S102). |
| **(g) A lever's marker names its PASS and its INSTRUMENT** (R65 for markers), asserted by an attribution check at the close. | 4,026 of 4,026 sites attributed; the S103 minimum-lever markers and the T5 remark were the only way a later reader knows which compiler decision each survivor stands for. |
| **(h) A ledger's "done" is per body (unit, function, after-hash), never by text alone.** | The T4 preflight drew 2,204 files where 2,583 were owed: every fleet-wide copy of an all-NEEDED exemplar passed as done by its text hash. |
| **(i) A long unattended run is DETACHED with a progress log, never a harness background task** (R55 operated). | The harness's low-memory guard killed the batch cycle mid-apply and two 30-byte waiters with 22–27 GB free; a SIGKILL skips a restore. |
| **(j) A marked ordinary-C fake (do-while, dead initialiser) is counted apart from levers and never an orphan; an invented condition, a dead store or a dummy reassignment is never banked.** | Drew's S104 ruling (a), read against sotn's `docs/STYLE.md`; a14/d20/c9/c13 refused on exactly this line. |
| **(k) A "stalling?" question is answered with the residue bucketed by what each bucket needs before any plan is proposed.** | S105: 1,548 drawable singletons / 691 parked / ~1,150 proven / 450 GTE / 94 missing-parameter — the close decision took one message. |

*(Techniques stay in the cookbook §454–§457 and METHOD steps 1–25; strategy in `docs/decision-log.md` (R31) and `docs/accelerators.md`;
the portable form is for the kit at its split.)*

## PhaseEnd Changelog
**v2.1.0 → v2.2.0 — Phase 36 complete (Gen3's second phase).** The compiler-forcing constructs in the matched C — register pins, asm
barriers, launders, keep-alives, hand-placed instructions, the GTE coprocessor idiom — were censused with a self-asserting instrument
(53,234 sites in 15,679 bodies; 44 whole-body assembly routines inside C shells found on the way and put in the verbatim manifest), then
taken off in a ladder that never changed a byte: a byte oracle on the build's own recipes, a mechanical strip (−37 %), one GTE header for
9,102 per-TU macro definitions, recipes, a permuter rung, an object-scored guided search (−6 %, no tokens), and ~200 agent readings of gcc
2.7.2's own source (one agent per class, then per translation unit) that closed 56 of 56 in the last session. 4,010 remain (−92.5 %), each
marked with the pass that needs it and the instrument that judged it, and bucketed for the structs phase: wrong signatures with ready
patches, missing struct types, a carve, one GTE spelling, and 1,548 singleton sites. On the way: 16,759 lying call declarations repaired
byte-identically, the lever series and the readability series published, the generator registry R2–R46 with a known-true run for each, and
the doctrine "ban the silence, not the lever" written for the next project's day one. R100–R106 ratified; eleven candidates proposed.

## Plain-English Recap
When this decompilation reached 100 %, thousands of its functions still carried little hacks — instructions to the compiler that forced
a particular register or ordering so the bytes would match — that a real programmer in 1998 never wrote. This phase counted them
honestly (fifty-three thousand), then removed them in stages while re-checking every one of the 218 game files byte for byte after every
step. A third came off just by asking the compiler "do you still produce the same bytes without this?". The rest needed understanding:
first a search program that scores each candidate rewrite against the real object, then agents reading the compiler's own source code to
find WHY the original bytes came out the way they did — a wrong function signature, a missing struct type, a loop written a different way
— and spelling the C the way the original author plausibly had. About four thousand hacks remain, each now labelled with the exact
compiler decision that needs it, and sorted by what would remove it. Most of those need the next phase's work — real struct types and
correct function signatures — which is why the phase stops here rather than grinding on. The count over time is published as a chart, and
the lesson for the next project is written down: allow such hacks only when they are marked and counted from the first day.

## 🛑 Stop Here
PhaseEnd written; `CURRENT_PHASE.md` archived → `phase-ends/logs/Phase36.md` (R19, via `git mv`); `phase-ends/DIGEST.md` §0/§2/§3
appended (step 3b); R100–R106 dispositioned in `config/kit_coverage_map.tsv` (kit_coverage OK); the timeline regenerated (76 rows, the
P36 row); the kit's record corpus regenerated (`make kit-corpus`, `tool_census --check: OK`) — **all left uncommitted for Drew's milestone-close commit**
(R6 gate-2 sign-off; the message is above). The Phase-36 work is committed across the sessions (`63b886626..db212f167`; not pushed). The
headless Ghidra MCP is stopped (R23); nothing under `ghidra/` is tracked. **Drew, from the repository root:**

```
git add -A phase-ends decomp-architect config/kit_coverage_map.tsv docs/story-timeline.md docs/story-timeline.svg
git commit -m "chore(phase-36): CLOSE — levers off to the measured floor: 53,234 → 4,010 register pins + asm statements (−92.5 %), every survivor marked with its pass and its instrument and named for the structs phase; the GTE idiom in one header; 16,759 lying call declarations repaired; the lever and readability series published; 218/218 at every step (v2.2.0)"
git tag -a v2.2.0 -m "v2.2.0 — Phase 36: levers off to the measured floor (53,234 → 4,010); 218 binaries byte-identical"
git push origin main --tags
```

Gen3 continues — do **NOT** start Phase 37 here. Start a **fresh session** (effort **Max**, **plan mode**) for **Phase 37 — the structs
phase**, planning from `docs/gen3-handoff.md` and `docs/gen3-standards.md` with this PhaseEnd's residue list as the acceptance test. Keep
this file forever.
