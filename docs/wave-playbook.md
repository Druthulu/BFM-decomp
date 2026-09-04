# Wave playbook — running a Claude-agent matching wave, start to finish

**Status: CURRENT (P31 S67, 2026-08-31).** This is the pipeline in use today.
`docs/automation-runbook.md` describes the **retired OpenRouter / ox-alpha** campaign — its section 2
is titled "The drafting toolchain (OpenRouter)" and its lanes (`drafter`/`gater`/`maintenance`/
`stallguard`) are all DEAD by choice. Do not follow it for a Claude wave.

Every step below carries **the measured failure that justifies it**. That is the point of the
document: the sequence is easy to guess, the guards are not, and each guard exists because something
specific went wrong and cost tokens or a red binary.

---

## 0. Preconditions

```
git status --porcelain -- src config include     # MUST be empty
make check-all                                   # or trust the last full R22
```

A gate that starts on a dirty tree cannot tell your edits from its own. `ghidra/` churn in
`git status` is MCP noise and is never committed.

---

## 1. Draw — and exclude what cannot bank (R45)

```
python3 tools/draw_waves.py --prefix .run/<name>_ --waves 1 --per-wave <N> \
        --exclude-file config/wave_exclude.txt --ledger .run/<name>_ledger.json
python3 tools/draw_waves.py --only-main --prefix .run/<name>m_ --waves 1 --per-wave <M> \
        --exclude-file config/wave_exclude.txt --ledger .run/<name>_ledger.json
```

* **`--prefix` IS A RELATIVE PATH.** `--prefix s67o` writes `./s67o1/` into the repo root, not
  `.run/`. Always pass `.run/<name>_`.
* **THE EXCLUDE LIST IS AUDITED BEFORE THE DRAW, AND A STALE ONE IS REFUSED (P31 S72).** Pass it as
  `--exclude-file config/wave_exclude.txt`; `draw_waves` classifies every entry against the CURRENT
  tooling and **exits non-zero** if any is stale, naming the count and the regenerate command.
  `--exclude-stale-ok` still draws, but prints what it is ignoring — skipping is possible, never
  silent. Regenerate with `tools/exclude_audit.py <old> --write <new>`.

  > **Measured the day after `.run/S71_exclude.txt` was written: 88 of its 107 entries were stale**
  > — 28 already banked, 14 linked PsyQ symbols that were never targets, and **46 whose blocker had
  > since been fixed**. Those 46 are **12,750 instructions of open, drawable work**, including large main functions that S73 then banked.
  > (Do NOT read `SaveLoadRoutine` as drawable — it is the §434 frame pair, excluded from draws.) A list that filters them out
  > costs more than it saves. Current list: **`config/wave_exclude.txt`** — 26 entries as of S73 (16 CARVE-BLOCKED + 10 WALL); always trust `exclude_audit`, never a number written here.

* **The exclude list is not optional.** It carries two populations that no model can bank:
  * **CARVE-BLOCKED** — a subseg owning raw jtbls in >1 non-adjacent span, so only one can carve
    (cookbook §322/§426). `tools/split_indicator.py` derives this set. **As of P31 S74 it is EMPTY**:
    the four overlays that held it (`ov_SC01_084`, `ov_SC02_005`, `ov_SC02_011`, `ov_SC03_105` — 16
    functions) were split at their span boundaries (§431/§435), the fleet is **213 OK of 213**, and
    `split_indicator` is a HARD gate in `make tools-health`, so a new violation fails the build
    rather than being echoed past. Two of those four needed a THIRD piece the span list did not
    name — read §435 before assuming the cut count.
  * **WALL** — curated toolchain walls, now MERGED into `config/wave_exclude.txt` and pinned
    there with `# WALL:` (the seven `.run/S6*_walls.txt` ledgers are superseded): §188 epilogue functions that `oracle_reorder.py`
    proves byte-correct-but-unemittable, the §332 maspsx `la`-in-delay-slot set, and SDK-object
    addresses that belong to `psyq_integrate.py`. Measured: a main wave spent **4 of 7 slots**
    proving things already proven (§332a).
* Main draws refuse LINKED subsegs automatically — those stubs are dead text and a draft there
  **gates GREEN while wrong**.

### 1a-S76. THREE THINGS THE DRAW GOT WRONG, ALL FIXED — AND WHAT TO CHECK NOW

**`--main` drew ZERO main functions until 2026-09-03.** `bins` came from `glob.glob('src/*')`
DIRECTORIES and main has no `src/main/` (its TUs are top-level `src/*.c`), so `main` was never in
the list — while the tool printed `main: refusing 49 LINKED subseg(s)` and looked like it was doing
the work. `--only-main` worked only because it overwrote the list. Every MIXED draw in the project's
history therefore drew nothing from the binary that IS the frontier. Fixed, and now ASSERTED: a
`--main` draw that yields zero main stubs exits 4 and calls itself a defect. **Read the
`main: N stub(s) reached the pool` line on every mixed draw** — if it is missing, you are running an
old copy.

**The ledger hid still-open work.** A stub the ledger has seen was filtered forever, so after two
draws the tool reported `population: 0` with 51 stubs open. The ledger records what was ATTEMPTED,
not a property of the function — same shape as the exclude-list lesson in §1. Use `--redraw-open`,
and read the `NOTE: N further open stub(s) were filtered ONLY because the ledger has seen them`
line, which now always prints.

**Cross-check the draw against `corpus.stubs` before believing an empty frontier.** Both defects
above presented as "there is no more work". The corpus oracle and `progress.py` agree exactly
(measured: 59/59 non-linked main stubs), so a draw that disagrees with them is the thing that is
wrong. Building a wave straight from `corpus.stubs` is legitimate when the draw is suspect — S76y's
50 targets were assembled that way — but VERIFY THE LINKED SET YOURSELF first (region must not be in
`progress.LINKED_SEGS`), because a draft written into a linked subseg gates GREEN while wrong.

### 1a-S76b. TWO ORACLE FIXES THE PACKS AND AGENTS DEPEND ON

* **The reorder island.** `REORDER_TUS := 800c2 800c2_2 800c2_3 800c3` build through
  `reorder_passthrough.py + as -O2`, not maspsx + `as -O1`. `match_one` and `rtu_match` modelled the
  wrong path and manufactured a §182/§188 "IMMOVABLE epilogue" wall for every function in those TUs.
  Both now derive the list from the Makefile and print a NOTE when they switch. **If an agent reports
  an epilogue-shaped residual in one of those four TUs, the oracle is the suspect, not the draft.**
* **Verbatim-asm drafts are refused at three points** (`gate_main`, `harvest_verify`,
  `api_agent.prior_draft`). A §265 body is stored as `<fn>.c` like any draft, matches its own source,
  and banks nothing; 1,099 of them sit in the draft store. The pack no longer offers one as a warm
  start. **A deliberate §265 bank goes into `src/` via `asm_verbatim.py`, never through a gate slate.**

### 1b. THE WALLS LEDGER IS ALWAYS INCOMPLETE, AND THAT COSTS A FULL AGENT RUN EACH TIME

`.run/S6*_walls.txt` lists functions the pinned triple **cannot emit at all** — mostly §177/§188's
-O1-vs-O2 epilogue (`jr $ra` with `addiu $sp` in its delay slot), which `oracle_reorder.py` proves
byte-correct-but-unemittable. Excluding them at draw time is in step 1 for a reason.

**But a wall nobody has met yet is invisible to that filter**, so each new one is discovered by
PAYING an agent to hit it. Measured twice in S68, both on `main`:

| function | what it cost | outcome |
|---|---|---|
| `func_8005E228` | a full sonnet run | wall found, then banked the §265 verbatim-asm way |
| `func_8005F0C8` | **289k tokens** | drafted to closeness 36, residual confirmed §188 by the oracle |

Neither was on any list beforehand, and neither is a model failure — an agent handed a wall always
returns a NEAR with an unexplainable tail, which is indistinguishable from a hard function.

**HALF OF THIS IS NOW BUILT — USE IT.** `tools/wall_sweep.py` enumerates the §332 class (a `%lo`
in a delay slot, i.e. the second half of an assembler macro gcc emits as ONE atomic insn, so C can
never put it there):

```
python3 tools/wall_sweep.py                 # report, with the branch/slot pair for each hit
python3 tools/wall_sweep.py --emit-exclude  # binary:fn lines, straight into draw_waves --exclude
```

Current answer: **10 functions, 1,027 instructions** over 1,378 open-stub `.s` files. §332 had said
"6 fleet-wide" and named two — **a count without an enumeration cannot drive a filter**, which is
why the draw kept spending agents on them.

It repaid itself within minutes of existing: `main/func_8005D734` was in the list AND had just been
escalated to Fable at closeness 8; its sweep site was exactly the residual the drafting agent
described, so that escalation could never have succeeded. Filtering the live queue then dropped two
more (`func_8005D9C4` 133 ins, `func_8005F450` 159 ins) before they were ever drafted.

**STILL NOT BUILT:** the same treatment for §188's epilogue shape. The detector exists inside
`oracle_reorder.py` and has never been run as a sweep. Until it is, treat "NEAR with an
epilogue-shaped tail" as a walls candidate and CHECK IT WITH THE ORACLE before escalating — an
escalation cannot beat the toolchain, so that spend is guaranteed waste.

## 2. Cards — and make sure the twin is on them

```
python3 tools/t5_cards.py --wave .run/<wave>
```

Check the printed `seed_ref N/M` line. `seed_ref` is the **already-banked body that matches this
target**, joined on the corpus signature hashes (`tools/seed_ref.py`).

> **The 102k-token lesson.** `t5_cards` used to skip `seed_ref` and the pack then asserted
> *"no banked twin — derive from the .s"*, which its docstring called TRUE. It was true of the CARD
> and false of the WORLD. An opus agent spent **102,193 tokens** re-deriving
> `ov_SC03_107:func_8013DD68`, whose body is banked verbatim at the same address in `ov_MAIN_012`.
> Fleet-wide, **87 open stubs have a banked twin and 41 sit in `twin_sweep`'s refusal ledger**, where
> neither tool could see them. A `mechanical_remap_refused` flag now tells the agent: copy the BODY,
> expect a declaration blocker.

### 2a-0. THE SAME-ADDRESS LEAD IS SIZE-FILTERED NOW — READ THE `⚠ IGNORE` LINE (S74)

The card's `⭐ IS BANKED AT THIS ADDRESS` lead used to be name+address keyed with no size check, and
**about a dozen of ~60 S74 cards carried a wrong twin** — one advertising a 72-instruction namesake
to a 241-instruction target, *with journal history claiming "already MATCH closeness 0"*. `api_agent`
now keeps a lead only at a MATCHING instruction count (marking it strong when `h_seq` matches too)
and prints an explicit `⚠ IGNORE …` naming the binaries where that address holds a different
function, with both sizes. Nothing to run — but if a pack still shows a bare address lead, it was
built before S74; regenerate it rather than trusting it (cookbook §438/§238).

### 2a. RUN `seed_ref --near` BEFORE BELIEVING ANY "NO TWIN" VERDICT (S69)

```
.venv/bin/python tools/seed_ref.py --near --max-d 25 --json .run/<wave>/near.json
```

The exact-hash tier finds 22 of 352 reachable open stubs; the near band finds **75 of 352 (21%)** —
3.4x. `h_norm` is blind to indexed-global relocs (§389), so true reloc-only twins of ALREADY-BANKED
bodies hash differently and read as singletons. A `RELOC-ONLY` row is mechanical: `family_remap` the
banked exemplar onto the open address, then gate — **8 of 10 banked at ~0 agent tokens on first use**,
one 94-ins exemplar serving five open copies. Never send a RELOC-ONLY row to a drafting agent.

### 2a-2. THE TWIN LADDER — take the CHEAPEST tier available, never the closest number (S69)

Distance is a FILTER, not the ranking key: a deletion is free and a substitution is thought (§390).
Work down this ladder and stop at the first tier that has a row; only widen when the tier above is
empty. We never "go straight to d25" — widening only lets tiers 2-3 SEE candidates that a d=0-only
tool called singletons.

| tier | detector | cost | measured S69 |
|---|---|---|---|
| 1 exact twin (d=0) | `seed_ref` hash | free — copy the body verbatim | 22 rows |
| 2 RELOC-ONLY (any d) | `seed_ref --near` + `family_remap.classify_member` | mechanical — remap, gate | 31 rows, **8 banked, ~0 tokens** |
| 3 CONTAINED (± whole block) | `seed_ref --contained` | near-mechanical — delete/add statements | 9 usable, **1 banked** |
| 4 true cousin (few substitutions) | `--near`, ratio `r = d/min(nins) <= 0.27` | seeded crack — a cheap agent holding the twin's C | 13 rows |
| 5 no match | — | cold draft, full price | 277 of 352 |

**Filter lookalikes before handing anything to an agent.** At `r >= ~0.37` the "twin" is two
different functions sharing boilerplate — 17 of 30 NEAR-COUSIN rows were exactly that. A wrong twin
is worse than no twin, because the agent believes it.

**And do not build more scanners.** Three fleet-wide probes past RELOC-ONLY returned 0 new / 9 / 2
(§390). The scanner well is dry; the integration levers (§376/§378) out-earned it by an order of
magnitude in the same session.

### 2a-3. AFTER EVERY EXEMPLAR BANK, RE-RUN THE TWIN SCAN BEFORE DRAFTING ITS SIBLINGS (S69)

An open-open cluster reports "no banked twin" for ALL members — correctly, because none is banked.
**Bank one and every sibling may become a remap job.** Measured S69: a reach-6 cluster's exemplar
cost 203k tokens to crack, then four siblings were drafted at ~60k each when `seed_ref` would have
returned the freshly-banked exemplar as their twin and `family_remap` would have banked them for ~0
(the agents' own diffs read "label-stripped .s diff is EMPTY" and "an EXACT clone"). One of them had
already burned 257k plateauing at permuter-class NEAR before the remap closed it.

```
crack ONE exemplar -> gate -> BANK -> re-run seed_ref/--near for the rest of the cluster
                                   -> remap what now has a twin; draft only what does not
```

**And never draft two members of the same cluster in parallel** — if either cracks, the other is
free, so the second agent is pure waste (§397).

### 2b. WORKED-EXAMPLE NEIGHBOURS — **AUTOMATIC SINCE S77**; read the coverage line

```
worked-example neighbours: 30/30 target(s) have a matched neighbour; appended to 30 pack(s)
```

`claude_wave_packs.py` now calls `neighbor_ref.neighbors()` for every target and appends an
**ALREADY-MATCHED NEIGHBOURS — READ THESE FIRST** block to its pack, exactly like the past-attempt
notes in §3b. Additive and never fails a wave.

> **Why this changed (P31 S77).** From S68 to S77 this step was documented as a MANUAL per-card
> command and wired into nothing — so on a 30-card wave it ran for approximately zero cards, while
> the playbook called it the biggest measured cost lever in the wave. A lever the pack does not
> carry is a lever nobody pulls. First automatic run: **30/30 targets had a matched neighbour.**
>
> **And it shipped with a name bug that would have silently un-done it.** `neighbor_ref` reports the
> SYMBOL-TABLE name, which for an unnamed function is Ghidra's `FUN_8003a0e4` — a string that
> appears NOWHERE in `src/*.c`, where that function is `func_8003A0E4`. An agent told to read
> `FUN_8003a0e4` greps, finds nothing, and concludes there is no neighbour. The pack renderer now
> resolves every name against the destination TU's own text and falls back to the address; the
> symbol-table spelling is shown in parentheses. Measured on the first wave: **150 of 150 neighbour
> names needed resolving.**

Run it by hand only when you want the ranking outside a wave:

```
python3 tools/neighbor_ref.py --binary <bin> --fn <fn> --top 5
```

`seed_ref` (step 2) answers *"is there a byte-identical twin?"*. This answers the weaker and far
more common question: **"which already-MATCHED function should this agent READ first?"**

**The measurement, S68.** Every one of the cheapest large matches came from an agent finding a
matched neighbour; the expensive ones had none:

| function | ins | tokens | what unlocked it |
|---|---|---|---|
| `func_800D1254` | 555 | **72k** | an `-O0` sibling in the same binary |
| `func_800D12D0` | 657 | **122k** | the `-O0` sibling, FIRST COMPILE |
| `func_8018AD9C` | 397 | **87k** | a banked twin, §193-A one-shot |
| `func_8017BEBC` | 753 | **177k** | a near-twin IN THE SAME FILE |
| `main` fns with no neighbour | ~80 | **200–350k** | — |

That is a ~20× swing on the one variable the card controls.

**The failure it exists to prevent:** `func_8017BEBC`'s card asserted **"no banked twin"** while a
matched 755-instruction near-twin sat 3,700 lines up in its own destination file, its header comment
listing the four levers the target needed. `seed_ref` joins on signature hashes and could not see it.
Three other S68 agents found their unlock the same way, unprompted — so this is a supplied habit now,
not an accidental one.

**Read the ranking honestly:** SAME-TU beats everything (same decl environment, same carve, and its
header usually records the levers). An opt-level mismatch is PENALISED, not ranked low — an `-O2`
example actively misleads an `-O0` target (§116). And a neighbour is a **worked example to read**,
never a body to copy: §168 law 1 measured cousin-remap at 0/26.

## 3. Packs

```
python3 tools/claude_wave_packs.py .run/<wave>/targets.json .run/<wave> \
        --cards .run/<wave>/cards.json
```

Positional args, not flags. **The second arg is the WAVE dir, not `<wave>/packs`** — the tool writes
`out_dir/SYS.md` + `out_dir/packs/<fn>.md`, which is exactly the layout the drafting prompt reads.

> **CORRECTED P31 S70 — the old form silently cost every agent its laws file.** This step used to be
> documented as `... .run/<wave>/packs` followed by
> `mv .run/<wave>/packs/packs/*.md .run/<wave>/packs/`. That put the packs one level too deep (hence
> the mv) and **SYS.md at `<wave>/packs/SYS.md`, while `claude_wave_draft.js` tells every agent to
> read `<wave>/SYS.md`**. So SYS.md did not exist where any agent looked, in every wave, and the
> drafting brief silently degraded to "the pack alone". Two S70 agents reported it verbatim
> ("NOTE: .run/S70y_1/SYS.md does not exist — worked from the pack alone"); the rest never mentioned
> it. Pass the wave dir and the mv disappears with the bug.

### 3b. PAST-ATTEMPT FUEL — automatic since S71, but CHECK ITS COVERAGE LINE

`claude_wave_packs.py` now ends by calling `tools/journal_notes.py`, which mines every agent journal
for notes about each target and appends `PAST ATTEMPTS ON THIS EXACT FUNCTION` to its pack. Read the
line it prints:

```
past-attempt notes: 16/27 target(s) have journal history; appended to 16 pack(s)
```

A **0/N** on a wave drawn from the frontier is a DEFECT, not a fact — those functions have refused
waves before, so they have history. Check the journal glob in `journal_notes.JOURNALS` resolves
(`~/.claude/projects/-home-musashi-bfm-decomp/*/subagents/workflows/*/journal.jsonl`) before believing
it. Back-fill a wave built another way with `tools/journal_notes.py --wave <dir>` (idempotent).

**Why it is worth a step of its own (§411).** S71 wave 1, over the hardest 210-function frontier where
every target had already refused a wave: **38/39 MATCH (97.4%)** vs S70's 124/131 (94.7%) on an easier
pool, **29/39 agents citing a prior attempt**, and **4/39 banking by recovering a MATCHing body the
notes told them was already on disk**. The two costs it removes are re-testing a measured-inert lever
and re-deriving a body that exists.

## 4. Validate — never hand-type a target

```
python3 tools/wave_args.py .run/<wave>          # writes wf_args.json
```

Asserts the `.s` exists, `sub` matches its parent directory, the pack exists, and the target is
still open **at draw time**.

> **EVERY payload you launch comes from `wf_args.json`. Never type one.** In S67 I hand-wrote a
> single streaming refill and invented `func_80184F60` — the *second instruction* of an
> already-matched function, and a `D_` data label in sibling overlays. 58k tokens to prove my typo
> wrong. `wave_args.py` exists because of an earlier instance of exactly this.

### 4b. THE TRIAGE LADDER RUNS HERE (S69) — and again before any escalation

`wave_args` now calls `triage_ladder.pre_classify` and DROPS every target that is walled or parked,
printing each one (never a silent cap). Nothing extra to run at draw time; read what it dropped.

Before escalating a stuck draft to a better model, run the check that S68 did not have:

```
python3 tools/triage_ladder.py --escalate <binary>:<fn>     # exit 2 = do not escalate
```

S68 escalated `main/func_8005D734` to Fable at closeness 8. It is a §332 delay-slot wall — no model
can emit it under the pinned triple. `escalate_fable.js` now REFUSES any target that does not carry
`triage:'DRAFT'`, so the check is structural rather than remembered.

**The ladder never runs on a moving tree.** It refuses while a gate or drafting lane is live, because
a merging gate makes the stub oracle wrong in both directions (§377). If it refuses, wait — do not
`--force` to save a minute.

**And do not treat its `INTEG-STANDALONE-MATCH` / `NOCOMPILE-UNDECLARED-*` output as banks.** That is
the §376 correction: standalone closeness 0 proves the BODY, not that the TU accepts the SIGNATURE.
Measured S69: **0 of 28** of that class banked raw — then **8 banked** once the missing lever
existed. Run the full §378 chain, IN ORDER; each step only reveals the next, and stopping at step 1
is how the class read as dead for half a session:

```
tools/fix_arity_callers.py --binary B --funcs FN --any-proto --apply --journal J1   # `conflicting types'
tools/cast_self_callers.py --binary B --funcs FN --drafts D --apply --journal J2    # `too few arguments'
tools/cast_self_callers.py … --sync-decls        # narrow-param: C89 forbids no-proto vs `void f(s16)'
<gate>                                            # the byte-gate is the sole arbiter
tools/cast_self_callers.py --undo-journal J2 --keep <banked>    # MANDATORY — see below
```

Or in one driver: `recover_integration.py --binary B --stages arity,self-cast --max-tier fleet --r22`.

> **THE UNDO IS NOT OPTIONAL.** The casts go in BEFORE the gate, in preparation. A cast left behind
> for a draft that did not bank made `ov_SC07_000` fail to COMPILE at HEAD, so every later gate
> verdict on that binary measured a broken baseline rather than a draft (found only because two
> drafting agents reported BASELINE-RED and I checked their claim). Run `--undo-journal --keep
> <banked>` after EVERY gate.

**CORRECTED S69 — the callee variant is NOT the same chain.** If the diagnostic names a DIFFERENT
symbol (`conflicting types for func_8012AD44`), that is a CALLEE and §378 does **not** transfer:
`cast_self_callers` cannot cast it (it reads the return type off the draft), so `--any-proto` runs
UNPROTECTED and changes argument conversion at every call site. Measured: 60 decls no-protoed,
binary RED, reverted. It banked `main:func_80021D38` only because that callee had ONE decl.
**Count the sites first; never no-proto a symbol whose call sites you are not also casting.**

See §378b for the full decision table — there are FOUR variants and two of them break the chain.
Notably variant 3 (`conflicting types`, RETURN type only, decl already `()`, symbol ADDRESS-TAKEN)
is fixed by `--sync-decls` ALONE: both other levers no-op, and the sync is safe precisely because an
address-taken site has no arguments to convert.

### 4c. LAUNCH-TIME OPEN CHECK — `wave_args` asserts at DRAW time, and payloads go stale

```
python3 tools/launch_check.py --payload .run/<wave>/wf_args.json   # filters in place
python3 tools/launch_check.py <binary> <fn>                        # exit 2 = already banked
```

A wave's payload sits on disk while gates run, so by launch time some of its targets are banked. An
agent handed one burns a full run to report "STALE CARD — already banked today", with no `.s` left to
score against. Measured S71: `ov_SC01_006/func_8017F9F8` did exactly that, and filtering the wave-2
payload found **3 of 27** already banked. Also skip any target that already has a FRESH draft from
this session — it needs a gate, not another agent.

## 5. Draft

`tools/workflows/claude_wave_draft.js`, `args = {wave, targets}`. One agent per target,
`model = target.arm`.

**Two shapes, and streaming is preferred:**
* **Batch** — N targets in one workflow. Simple, but it **cannot gate until its slowest agent
  lands**: measured 18 of 20 drafts idle while 2 stragglers ran.
* **Streaming** — one target per workflow, refill each slot on completion. Same concurrency, but
  banking starts immediately. `claude_wave_draft.js` with a single target IS a one-agent workflow;
  no new script needed.

Streaming **burns the 5-hour window faster** (it removes the idle gaps), so slots are the budget
dial. Model routing (P31 S73): **≤120 ins Sonnet · >120 Opus**; Fable is the tier above Opus for >~340 ins BUT WAS EXHAUSTED account-wide in S73 (three agents died on "You've reached your Fable limit" after ~10 min / ~133k tokens each) — check `/usage-credits` before routing to it. Opus handled 424/459/464/663-ins targets fine; 1165 is beyond its measured band. Never Haiku→Opus directly.

### 1c. MAIN'S SWITCH FUNCTIONS ARE DRAWABLE ONLY INSIDE A CARVED SPAN (P31 S72, cookbook §426)

At S72 25 of main's 59 frontier functions had a gcc jump table; after S72+S73 it is **2 of 36**, and both are the §434 frame pair. The mechanism below is why they mattered. A drafted switch emits its table into
`.rodata` while the raw copy is still emitted from the tail data object **unless that table's span is
carved** — the image grows and 238 symbols shift, which reads as a codegen reject and is not one.
`config/splat.us.exe.yaml` currently carves ONE span:

```
0x80072A38-0x80072C70   span A — LZSS + 11 game tables   -> src/800.c     CARVED, drawable
0x80072E44-0x80073140   span B — 14 tables               -> src/800_b.c   CARVED, drawable
0x800732A0-0x8007344C   span C —  8 tables               -> src/800_c.c   CARVED, drawable
0x80073494-0x80073514   span D —  4 tables               -> snd2, not game code
```

**All three game spans are carved as of S72** — `src/800.c` was split into three TUs at
`0x8002B0B4` / `0x80035270` so each span gets its own code object (one object contributes exactly
ONE contiguous `.rodata` run). 7 of the 14 main functions banked in S72 were span B/C, i.e.
impossible the day before, and S73 banked 9 more. **main's jtbl frontier is 25 -> 2**; the two
survivors are the §434 frame pair (excluded from DRAWS, route = §265 pair transcription); the R45 refusal that used to
apply here is gone. Census the class with the `jr $rN` (N != `ra`) detector — never `jr $ra`, which
ends every function (§401). If a FOURTH span ever appears (a newly-matched switch whose table sits
outside A/B/C), it needs its own object too: split again at that span's owner range (§431).

### 5b. GATE THE DIRECTORY, NEVER THE VERDICT LIST (P31 S72)

A wave's reported verdicts are a claim about what the AGENTS returned, not about what is **on disk**.
`claude_wave_draft.js` cannot read the filesystem, so its `.catch()` reports `NO-DRAFT` for any agent
that dies — including one that already wrote a finished body.

**Measured, S72.** A Fable agent on `main/func_80024448` spent 133k tokens / 17 tool calls / 10 min,
wrote `.run/S72m_1/fable/func_80024448.c`, and was then killed by
`You've reached your Fable limit`. The workflow returned:

```
{"fn":"func_80024448","status":"NO-DRAFT","closeness":null,"compiles":false,"draft_path":""}
```

`match_one` on that same file: **`{"status":"match","closeness":0,"nins":362}`** — a complete,
byte-perfect body reported as no work at all. Believing the verdict discards it; scanning the
directory finds it. This is §404 seen from the other side, and R40: a provider rate limit is a
HARNESS event, and attributing it to the target ("Fable failed on this function") is a false model
verdict — the same class as S71's seven.

**Apply:** after every wave, `find <wave> -name '*.c'` and score everything, whatever the verdicts
said; a sibling `scratch_<fn>/` with candidates but no final draft is worth scoring too. And when a
tier is exhausted, re-run its targets on the next tier ALONGSIDE the dying agents — never kill a
running workflow to relaunch it differently.

### 6-S76. WHAT TO DO WHEN A GATE BANKS FAR LESS THAN IT STAGED

Measured S76: the overlay gate banked **1 of 38** and main's first pass **0 of 49** — and none of it
was drafting quality. Classify before re-drafting anything:

1. **Run `recover_integration --probe-only --no-propagate`.** It compiles each stranded draft in its
   ACTUAL TU and splits them three ways. On main's 40: **CC1-FAIL 16 / DIFF 18 / MATCH 6**. Only the
   CC1-FAIL group is plumbing; the DIFF group is real residual and no declaration work will save it.
   **A `CC1-FAIL` says the declaration blocked COMPILATION — never that the body underneath is right.**
2. **For a CC1-FAIL, run `tools/sync_tu_decls.py --binary main --fn F --draft D --apply`.** It copies
   the TU's own `extern` for whichever symbol the gate names, re-gates, repeats. Banked
   `func_8005EB28` in one round and `func_8005EC00` in two.
3. **If it refuses with `self_decl_tu`**, the TU declares the function being banked, so the call
   SITES must change too — that is `cast_self_callers --sync-decls`, and the `--undo-journal --keep`
   afterwards is mandatory.
4. **Expect a CASCADE.** Every bank gives its TU a real definition, which then contradicts the stale
   `extern` that every later draft in that TU still carries. A draft that was compatible before a
   bank can be incompatible after it — re-run the sync rather than concluding the draft went bad.

## 6. Gate — EVERYTHING PARALLEL. There is no serial lane.

> **P31 S74 — after a gate that CARVED, the binary's `asm/` is stale until a re-extract.** The
> isolation's new TU references `.s` files that do not exist yet, so `corpus.stubs` refuses and the
> NEXT gate on that binary dies with `corpus refused` before doing any work. `parallel_gate` now
> re-extracts any binary whose carve created a new source file, and a refusal carries corpus's own
> message instead of a bare "refused" — but if you gate by hand, run `make extract BINARY=<b>`
> yourself and confirm `corpus.stubs` is satisfiable before trusting the next verdict.

```
python3 tools/parallel_gate.py --plan plan.json --workers 12 --commit
      # plan.json: [{"binary": "...", "drafts": "/abs/path"}, ...]
```

> **`main` IS NOT IN THAT LANE.** `parallel_gate` REFUSES `binary == 'main'` (§414) — its worker is
> `gate_stage`, which builds incrementally, and main's extract rewrites the linker script. Use
> `tools/gate_main.py <slate> --apply`: baseline assert → one clean rebuild per slate (~15 s with
> `-j`) → bisect on failure. Since S72 a red batch **preserves the failing image + map** under
> `.run/gate_main_fail/<tag>/` and prints the attribution — FOUR verdicts: **BODY REJECT**
> (divergence confined to the drafted function) · **TABLE REJECT** (§405-A — `.text` is
> byte-identical and ALL divergence is in `.rodata`, i.e. its own jump table: fix the case
> VALUES/ORDER, do NOT respell the body and do NOT run the §376 chain; on main's switch
> functions this is the DOMINANT residual, §433) · **PLUMBING REJECT** (byte-identical, differs
> elsewhere IN CODE -> the §376/§378 chain) · **MIXED**. Read that line before recording any main verdict; a bare hash cannot tell
> those apart, and mistaking the second for the first parked 11 functions for a session (§426/§427).
> A single-entry slate gets the sharpest verdict; drops go to `.run/gate_main_dropped.json` with the
> §376/§378 recovery chain spelled out.

**MEASURED S67, and this is the bar:**

| lane | result |
|---|---|
| non-jtbl | **13 banked / 13 binaries / 139 s** (12 workers) |
| jtbl | **19 banked / 14 binaries / 188 s** (8 workers), 0 refusals |
| the same jtbl work, serially, earlier that day | **58 minutes for ONE binary** |

**jtbl used to be serial-only** because `harvest_verify`'s carve runs `make extract` and a worktree's
`asm/` is a symlink to the main tree — a carving worker would rewrite shared asm. `isolate_asm()`
fixes it: `asm/` is 448 MB but ONE binary's subtree is **3.6-5.0 MB**, so a carving job gets
per-binary symlinks plus a real copy of the single binary it carves (~5 MB/worker). It is applied
PER JOB because worker slots are reused, and gated by the same jtbl predicate `harvest_verify`
carves on.

**A CARVE WRITES THREE THINGS AND THE MERGE MUST CARRY ALL THREE** — `src/<bin>/*.c`,
`config/splat.<bin>.yaml`, and this binary's BLOCK of the shared `config/overlays.mk`. Carrying only
the first gives a green worker and a red fleet: measured S67, 13 of 213 red, every one a jtbl binary
from that run (reverted, then fixed with `ovl_block()`/`splice_ovl_block()`). Never blanket-adopt
`overlays.mk` — splice the one block, with the same pinned-baseline refusal as a file adopt.

**RUN A jtbl GATE WITH `--r22`.** It aborts on a non-green fleet and leaves the files in the tree for
inspection instead of committing red binaries — the guard that would have caught the above at once.

**If you are writing `for b in binaries: gate_stage ...`, STOP.** That loop is the hour-long mistake
this section exists to prevent.

### 6b. (historical) split on jtbl, run both lanes at once

```
python3 tools/gate_wave.py --drafts <dir> --workers 8 --commit [--r22]
      # <dir>/<binary>/<fn>.c
```

* **Parallel is the DEFAULT.** `parallel_gate`'s worktrees measured **4 binaries in 103 s** against
  ~6 min serial.
* **Only jtbl-bearing drafts go serial**, because `harvest_verify`'s carve runs `make extract` and a
  worktree's `asm/` is a symlink to the main tree. All four `make extract` sites are inside the
  carve path, so a non-jtbl draft never triggers one.
* **The split PRECEDES the run.** A jtbl draft in a worker does not fail cleanly — it re-extracts
  through the symlink and writes the MAIN tree while other workers read it. "Run everything parallel
  and re-run the failures" can poison the whole batch.
* Measured cost of getting this wrong: I gated **16 binaries serially to protect ONE jtbl draft** —
  about an hour for what should have taken minutes. **`gate_wave.py`'s split is now an optimisation
  (same-binary drafts share a build), NOT a safety requirement.**

### 6b. READ THE VERDICTS — `tools/gate_triage.py`

```
python3 tools/gate_triage.py --plan <gate_plan.json>
```

Routes every verdict to the lane it names and asserts the staged denominator: CARVE (probe it —
`jr_isolate_all` was the usual unblock; as of S73 it and `split_src_region` run to completion but the resulting object still fails to ASSEMBLE, so no overlay has been split with them — prefer cookbook §431, cut the file verbatim and let the compiler enumerate what crosses) · UNDEF-D (§171 `aprop_symfix`) · CONFLICT/ARITY (§376/§378)
· PARSE · NO-DIAG · DIFF (real codegen). S71's census over 37 verdicts: DIFF 18 · CARVE 7 · PARSE 3 ·
NO-DIAG 3 · CONFLICT 2 · ARITY 2 · UNDEF 2 — which corrected an impression that carve dominated.

## 7. After ANY bank

```
python3 tools/twin_sweep.py --tier both --workers 10 --commit
```

The twin pool **refills after every bank** — a sweep returning 0 is not the end. It delegates its
gate to `parallel_gate` already.

> **Known holes, do not trust its "pool is dry":** it reads `family_sweep.load_sigs()`, which covers
> **141 of 213 binaries** (`main`, `resident`, every `md_MAIN_*` are absent), and it builds its
> open-set with `int(s.symbol[5:],16)` inside a bare `except Exception: pass`, so ONE curated symbol
> name silently disables an ENTIRE binary (measured: `main`, 765 of 1048 stubs). Use
> `tools/seed_ref.py --all` for the fleet-wide answer.

## 8. Harvest — BEFORE the next wave (hard gate)

Write every new idiom into `docs/matching-cookbook.md`, then regenerate
`python3 tools/cookbook_index.py`.

**This is the project thesis, not hygiene:** new idioms make the next exemplar easier and turn
mechanical classes into free banks. Then ask of each idiom *"is this MECHANICAL?"* — if yes, build
the sweep and bank the free functions **before** drafting again.

Harvest **periodically, not per-bank**: §330 (the neighbour-shape lever, the highest-value entry of
S67) was only visible because four independent instances appeared in one wave. One function at a
time cannot see it.

## 9. Verify the FLEET, not the binary

```
make clean && make extract-all && make check-all      # expect "213 passed, 0 failed of 213"
```

* **A bare `make check-all` is INCREMENTAL and will lie.** It once reported a false 211/213.
* **Read the EXIT CODE, not the output file** (R53). A failed build leaves the PREVIOUS binary on
  disk and `sha1sum` reads GREEN. This happened twice in one hour in S67 and would have certified a
  non-compiling resegmentation as byte-neutral.
* **Propagation is NOT byte-gated.** `gate_stage` verifies the SOURCE binary, then `dedup_propagate`
  writes N others and nothing re-checks them. That produced a RED `ov_SC04_018` (fleet 212/213) whose
  cause was a deleted declaration layer the surviving bodies still needed. **Run R22 after any
  propagating gate**, not just at session end.

## 10. Checkpoint

Refresh the `🛑 SESSION CHECKPOINT` block at the END of `phase-ends/CURRENT_PHASE.md` and commit.
Stale is worse than absent. Write it for a session that has none of your context.

---

## Waiting on background work — one trap that costs 40 minutes

`pgrep -f` matches against **every process's full command line, including the waiter's own.**

```
until ! pgrep -f "parallel_gate.py"   >/dev/null; do sleep 20; done   # WRONG — matches itself
until ! pgrep -f "parallel_[g]ate.py" >/dev/null; do sleep 20; done   # better, but NOT sufficient
```

**THE BRACKET IS NOT ENOUGH IF YOU LAUNCH AND WAIT IN ONE SHELL.** Measured twice in S67:

1. A waiter using the bare pattern matched its own shell and spun **40 minutes** while
   `parallel_gate` never started.
2. A waiter using the *bracketed* pattern ALSO spun — for **1 h 35 m** — because the same shell
   command had launched the job, so its command line contained the UNBRACKETED text too:
   `nohup … tools/gate_stage.py --binary ov_SC07_007 … ; until ! pgrep -f "gate_[s]tage.py --binary ov_SC07_007"`
   The regex `gate_[s]tage.py` does not match the literal `gate_[s]tage.py`, but it matches the
   `gate_stage.py` sitting in the launch half of the very same line.

**LAUNCH DETACHED:** `setsid nohup <cmd> > log 2>&1 < /dev/null & disown`. A plain `nohup` child
shares the launching shell's PROCESS GROUP, so the harness killing that shell on its timeout kills
the job too — measured S67: a `sleep 120` in the launching call discarded **8 completed jtbl carves**.

**THE RULE: launch and wait in SEPARATE shell invocations.** Launch in one call, return, then wait
in another whose command line never names the target unbracketed. Better still, wait on a
CONDITION the job itself produces — a completion marker in its log — rather than on process
liveness:

```
until grep -q "R22 rc=" .run/<job>.log 2>/dev/null; do sleep 30; done
```

**The tell for both failures: an empty log plus zero `ps` hits means NEVER STARTED, not "buffered".**
Same hazard, from the other side, killed two lane helpers in S60.

Any long-running tool you write must **stream** its progress (R55). `gate_wave.py` initially captured
both lanes and printed at the end, leaving a zero-byte log for the whole run — indistinguishable from
a hang.

---

## For the future-decomp template

The reusable content here is **not the command list** — it is the pairing of each guard with the
measurement that produced it. A generic decomp guide can tell you to verify your build; only a
project log can tell you that a failed build leaves a stale binary whose hash reads green.

Feeder documents for that template: `docs/decision-log.md` (R31 — the WHY behind every strategic
pivot), `docs/accelerators.md` (discoveries that would have sped up earlier work),
`docs/hindsight-study.md`, `docs/matching-cookbook.md` (the compiler-idiom knowledge base), and the
`phase-ends/` series (the build history).
