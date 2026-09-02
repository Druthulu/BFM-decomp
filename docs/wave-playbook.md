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
        --exclude "$(cat .run/S67_exclude2.txt)"
python3 tools/draw_waves.py --only-main --prefix .run/<name>m_ --waves 1 --per-wave <M> --exclude ...
```

* **`--prefix` IS A RELATIVE PATH.** `--prefix s67o` writes `./s67o1/` into the repo root, not
  `.run/`. Always pass `.run/<name>_`.
* **The exclude list is not optional.** It carries two populations that no model can bank:
  * **96 jtbl functions whose carve plan `build_carve` REFUSES** (non-contiguous same-subseg
    `.rodata`). Cookbook §322. Before the S67 probe fix these all read "carveable".
  * **the toolchain walls** (`.run/S67_walls.txt`): §188 epilogue functions that `oracle_reorder.py`
    proves byte-correct-but-unemittable, the §332 maspsx `la`-in-delay-slot set, and SDK-object
    addresses that belong to `psyq_integrate.py`. Measured: a main wave spent **4 of 7 slots**
    proving things already proven (§332a).
* Main draws refuse LINKED subsegs automatically — those stubs are dead text and a draft there
  **gates GREEN while wrong**.

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

### 2b. RUN `neighbor_ref` FOR EVERY CARD — the biggest measured cost lever in the wave

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
dial. Model routing: ≤50 ins Sonnet · 51–120 Sonnet · >120 Opus. Never Haiku→Opus directly.

## 6. Gate — EVERYTHING PARALLEL. There is no serial lane.

```
python3 tools/parallel_gate.py --plan plan.json --workers 12 --commit
      # plan.json: [{"binary": "...", "drafts": "/abs/path"}, ...]
```

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
