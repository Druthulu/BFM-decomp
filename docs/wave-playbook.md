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

## 3. Packs

```
python3 tools/claude_wave_packs.py .run/<wave>/targets.json .run/<wave>/packs \
        --cards .run/<wave>/cards.json
mv .run/<wave>/packs/packs/*.md .run/<wave>/packs/ ; rmdir .run/<wave>/packs/packs
```

Positional args, not flags. It nests `packs/packs/` — flatten it or `wave_args` reports every
target as "no pack".

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

## 6. Gate — split on jtbl, run both lanes at once

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
  about an hour for what should have taken minutes.

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

```
until ! pgrep -f "parallel_[g]ate.py" >/dev/null; do sleep 20; done     # RIGHT
until ! pgrep -f "parallel_gate.py"   >/dev/null; do sleep 20; done     # WRONG — matches itself
```

`pgrep -f` matches the waiter's OWN command line. In S67 a waiter spun for 40 minutes waiting for
itself and the gate never started. **The tell: an empty log plus zero `ps` hits means NEVER STARTED,
not "buffered".** The bracket makes the pattern match the target but not the literal text in the
waiter. Same hazard, from the other side, killed two lane helpers in S60.

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
