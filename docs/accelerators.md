# Accelerators — what we learned late that a future decomp should know on day one

**Purpose (Drew, 2026-08-07):** we are building a reusable **Claude Code decomp workflow**. The
PhaseEnds record *what happened*; `docs/decision-log.md` (R31) records *why we pivoted*. Neither
answers the question this file exists for: **"what should phase 1 of the NEXT game do differently?"**

**Companion (added P31 S59):** `docs/portable-decomp-workflow.md` holds the part that TRANSFERS —
the system (gate discipline, the oracle ladder, lanes, cards, draw-time refusal, per-population
clocks, model routing, the flywheel, the measured economics) written target- and compiler-agnostic,
for the public "how to AI-decomp" deliverable. This file stays the BFM-specific ledger of *what we
learned late*; that file is *what a new project inherits on day one*. Rule of thumb for which gets an
entry: if it would still be true for a different console and a different compiler, it belongs there.

**How to add an entry** (same session as the discovery — R30 timing): what it is · when we found it ·
when it *could* have been found · what it would have saved · and the honest prerequisite, because some
levers genuinely cannot exist before something else is in place. Mark those `PREREQ` rather than
pretending they were available on day one — the prerequisite is then the real advice.

---

## A1 — Instrument-integrity BEFORE measurement (R35), as a standing habit

**Found:** phase 26 (the tooling-integrity audit), then re-confirmed in 27, 28, and again at S46.
**Could have been found:** phase 1.
**What it cost us:** four separate strategic reversals. A "families bank ≈0%" verdict that steered two
phases was a missing build step. A "~3% h_seq ceiling" was an `-O0` compile-flag artifact. Four hidden
overlays and ~39 code modules were invisible because a glob only looked at one payload layer. A whole
class of "the compiler beat us" walls were our own scanners.

**The rule for a new project:** any number that is about to scope real work — a coverage %, a "wall", a
"cheap win", a 0-hit scan — gets its *instrument* verified before the number is believed. Cheapest
version: every scanner asserts its own coverage against an over-approximating candidate set (R32), and
every oracle that is structurally blind to a class of error gets a **second, disagreeing oracle** (R34).

## A2 — The whole-binary byte-gate + parallel drafting harness

**Found:** phase 12 (of ~30). **Could have been found:** immediately after the first byte-identical
build (phase 5–6).
**What it would have saved:** phases 6–11 matched functions essentially by hand. The pattern — many
cheap agents draft C, and an *incorruptible* whole-binary byte-gate accepts only byte-identical output —
took the resident engine 1.4% → 85.6% in a single session once it existed. It also makes model quality a
*throughput* question instead of a correctness risk, which is what makes cheap models usable at all.

**The rule:** build the gate before the drafting. The gate is what makes everything after it safe.

## A3 — Cross-binary dedup propagation (match once → stamp ×N)

**Found:** phases 11–15. **Could have been found:** as soon as a second binary existed (phase 10).
**PREREQ:** ≥2 binaries onboarded and signed.
**What it would have saved:** this is the project's economic engine — one match banks up to 138
instances. Every match made before it existed was worth ×1.

**The rule:** the moment you have two binaries, ask "how much identical code do they share?" and build
the propagation path before harvesting.

## A4 — Read the compiler's SOURCE once, into a codegen map

**Found:** phase 23. **Could have been found:** phase 6, right after the compiler triple was pinned.
**PREREQ:** the exact compiler identified.
**What it would have saved:** phases 17–22 re-derived the same allocator/scheduler behaviour per
function, and repeatedly concluded "unsteerable" for classes that a map later dissolved. Reading the
passes once and writing a `residual → C-lever | intrinsic→brute-force` catalog converted per-function
reverse-engineering into cheap lookup, usable by *cheap* models.

**The rule:** pin the compiler, then spend one deliberate session reading its allocator, scheduler and
CSE passes into a lookup table. Do it before the first "this one is impossible" verdict, not after the
twentieth.

## A5 — A static scanner must model the compiler's ADDRESSING forms (S46, cookbook §155c)

**Found:** S46 (phase 30). **Could have been found:** the first time we scanned for cross-references
(phase 3).
**What it cost us:** a register-tracked scan for "who references address X" was blind to gcc's indexed
global-array read (`lui` … `addu` index … `lh lo(base)`), where the address lives in the `lui` **and the
load** with the index add between. It returned **zero** — and zero was read as a fact about the game. It
produced an evening lost to a phantom hunt (S45 p4), four failed static scans (S45 p5/p6), and a
*written, wrong* structural conclusion in `memory-map.md` ("the index never appears in CODE at all —
invisible to any fleet-wide code scan"). It appears in code; we couldn't see it.

**The rule:** before trusting a scanner's *negative*, hand-disassemble one known-good case and confirm
the scanner sees it. An **exactly-zero** result is more often a decoder gap than a discovery (§155b).
Keep a control the scanner must reproduce, and fail the tool if it can't (`tools/idxtab_map.py` does).

## A6 — Regroup the residue by STRUCTURE before calling it unique

**Found:** phases 24–25. **Could have been found:** as soon as a fleet of similar binaries existed.
**What it would have saved:** a "36,000 unique hand-decompiles" frontier was a *grouping artifact*;
regrouped by instruction skeleton, 90% collapsed into ~986 families. The endgame arithmetic changed
completely. (Caveat, byte-proven later: structural families are TEMPLATES, not free dedup — cracking one
makes the rest *fast*, not free.)

**The rule:** when the remaining work looks like a wall of unique functions, try a looser fingerprint
before accepting the estimate.

## A7 — The load map (`tools/idxtab_map.py`, `docs/idxtab-map.md`)

**Found:** S46 (phase 30). **Could it have helped earlier? Partly — and the honest answer matters.**
**PREREQ:** the per-binary loader wrapper identified + the fleet onboarded + ≥2 byte-proved control rows.
Those did not exist before ~phase 27, so the map itself could not have.

**But the thing that blocked it (A5) existed from day one**, and the map's *shape* is worth copying
early: once you can name the loader wrapper, build **payload → owning binary → load address** as a
controlled, regenerable table. Onboarding a new binary needs exactly one fact — its load address — and
this project spent multiple sessions per binary deriving that by hand (a TLO-law oracle, a runtime
tracer, four failed value scans, "the parked five"). A map that answers it as a lookup, gated by
controls, is worth building the day the wrapper is understood.

**And its limit, recorded so it isn't over-trusted:** absence from the map is NOT evidence a payload is
dead — byte-proved loaders are absent from that route too, because several load routes exist.

## A8 — Parallelism defaults for fleet-wide tools (processes vs threads; batch what you already know)

**Found:** S46 (phase 30). **Could have been found:** the first time a tool iterated the fleet —
phase 13, when `check-all` first existed.
**Measured:** `dedup_propagate` 24 min → **11.4 min**, same 29 functions, **+62 more member instances**,
R22 213/213 both ways.

Four rules, each learned from a specific failure:

1. **Return every verdict a sweep already computed.** The byte-gate built all 141 overlays and returned
   only the *first* failure; the recovery loop then paid a full sweep to rediscover each of the next
   137. Convergence went ~138 rounds → 1–3 rounds with no extra builds. A previous session's run died
   92 minutes in looking like it was nearly done — it had barely started.
2. **PROCESSES for CPU-bound work, threads only for subprocess waits.** 138 "independent parallel"
   searches on a `ThreadPoolExecutor` kept **0–4 builds alive at load 3** on a 32-core box: the work was
   regex over 15k-line files and every thread queued on the GIL. The identical logic in a
   `ProcessPoolExecutor`: **14–29 builds, load 34.75.** Threads remain correct for the byte-gate itself
   (each is a `subprocess.run` that releases the GIL).
3. **Longest-first scheduling.** `ex.map` starts in list order, so the giant items landing last left 31
   cores watching one build for ~25 s of every 56 s sweep. Sort by cost descending; re-sort the results
   into the caller's order so the verdict is bit-identical to the serial one.
4. **Per-item search beats lock-step sweeps when items are independent** — and the independence must be
   *argued*, not assumed. Here the shared header carries every macro regardless of which sites are
   instantiated, so writing it once leaves each overlay owning only its own files and build dir.

**Two traps it exposed:** a fixed temp path (`.run/dpcc/t.c`) is a correctness bug the day anything runs
concurrently (the same fake-isolation class as a shared `--work` dir); and a pool submitted all at once
shares no learning between workers — seed with one item in-process, then fan out with the result, or
every worker repeats the same expensive search.

**The acceptance test is the transferable part:** not a stopwatch — a **regression**. Revert to the
pre-run state, re-run the identical command, require the same output plus a byte-verified fleet. That is
what surfaced the *over-exclusion* in the old path: the faster run was also strictly more correct, and a
timing comparison would never have shown it.

## A9 — Validate the target list, and let an empty tier TERMINATE the pipeline

**Found:** S46 (phase 30), the hard way. **Could have been found:** the first multi-tier wave.
**Measured cost:** a 47-target wave burned **9.7M tokens for 20 matches**; ~29 targets were not real,
and **87 of 119 agents** were spent proving phantoms absent.

Two independent defects that multiplied:

1. **No validity gate on the target list.** It was derived by joining sig data against `corpus.stubs`
   with no check that each address was a real function boundary with an actual `.s` on disk. Four
   defect classes, every one diagnosed by the agents *after* the money was spent: NO-ASM, **MID-BODY**
   (an address ~545 instructions inside another function's carve, on a load-delay nop), OUT-OF-RANGE
   (before the binary's vram start), and ALREADY-DONE (banked in an earlier phase).
   → `tools/validate_targets.py` now names each class and exits non-zero.
2. **The pipeline short-circuited on MATCH but not on SKIPPED.** `done = r.status === 'MATCH'` meant a
   non-existent target was not "done": it fell through tier 1 → tier 2 → tier 3, and three agents each
   re-investigated the same phantom — **the third at the most expensive model in the stack.** One
   invalid target cost 3× instead of 1×.
   → `done = (status === 'MATCH' || status === 'SKIPPED')`. **A tier with nothing to work on must
   terminate the pipeline, not pass its emptiness downstream.**

**And the part that stings:** `wave_snapshot`'s R32 coverage assertion **refused this exact list**,
reporting 24 of 57 files found. That was the instrument saying the list was wrong. It was read as a
path-convention problem and routed around via a different resolver. Same session, fifth instrument
warning — and the only one that was *correct and overridden*.

**The rule:** before a wave, every target passes a validity gate; and in any cascade, a tier that
cannot act ends the chain. Cheap targets must fail cheaply, or the cheapest thing in the pool becomes
the most expensive.

---

## Harness self-inflicted wounds (P31 S58) — the checks that were vacuous

Four defects in one session where the *tooling around the work* failed, not the work. Each cost real
throughput, and each was invisible to the check I was relying on. These generalize to any
Claude-Code-driven pipeline, not just decomp.

**1. A `#` comment between backslash-continued argument lines silently drops every argument.**
```bash
$PY tools/ox_campaign.py \
    # this comment eats everything below it
    --waves 40 --workers 128 ...          # never reaches the program
```
The run falls back to argparse DEFAULTS and looks completely normal. `bash -n` does **not** catch it
— the construct is syntactically valid — and grepping the file finds the arguments even though they
are unreachable. **The only reliable check is a startup banner that prints the values the program
actually received.** Every long-running driver should print its effective config on line one.

**2. `pgrep -f <pattern>` matches your own shell.** A command containing the pattern string has that
string in its own `/proc/<pid>/cmdline`, so `pkill -f 'tools/foo.py'` kills the shell issuing it
(observed three times, twice fatally mid-edit). It also matches the harness's `bash -c "... eval
'...'"` wrapper, which **outlives** the process it launched — so a `while pgrep -f X; do sleep; done`
wait never ends. Anchor at the start of the cmdline (`'^\.venv/bin/python tools/foo'`), or collect
PIDs in one call and `kill` them in a separate one.

**3. `cmd | tail -N` buffers everything until exit.** A background job piped through `tail` writes a
0-byte log for its entire run, so "no errors yet" and "no output yet" are indistinguishable. Same for
any unflushed `print()` in a redirected Python process — use `python -u`, and redirect to a file you
can `tail` yourself rather than piping through one.

**4. Telemetry that only exists in a log line is not telemetry.** `429` handling printed with
`flush=True` into a block-buffered shard log; the rate-limit question ("are we being throttled?") was
unanswerable until every request appended to a JSONL (`tools/api_rate.py`). **If a number will decide
something, write it to a file a separate process can read at any moment.**

**The pattern behind all four:** the check I trusted (`bash -n`, `grep`, an empty log, a silent
console) could not distinguish "working" from "not running". Prefer checks that are *positively
affirmative* — a banner echoing real values, an append-only ledger, a counter that must move.

**5. A running lane script does not read your edit — bash parses `while … done` up front.** Editing
`.run/drafter.sh` and bouncing only its python re-runs the OLD command line: bash parses a compound
command in full before executing it, so the loop body — python invocation and all — is fixed in
memory for the life of that shell. Measured P31 S59: the file changed at 10:44, the python was
bounced at 11:02, and it came back on the pre-change lane list (it logged `lane tells, band
(5, 2000)`, which only the old list produces at that rotation index). The distinction to keep
straight:

| change | how it takes effect |
|---|---|
| lane **code** (`tools/*.py`) | next python start — a bounce is enough, since the arg list is unchanged |
| lane **args** (the `.sh` invocation) | needs a fresh **shell** (`tools/lanes/relaunch_drafter_shell.sh` waits for a wave to queue first, so no drafts are lost) |
| wave-draw **defaults** (`build_wave_atlas.py`) | next wave draw — it is a fresh subprocess per draw, no restart at all |

Same family as #1–#4: the check that "the change is live" was reading the file on disk, which cannot
distinguish *edited* from *in effect*. Verify from the process — its `/proc/<pid>/cmdline`, or the
startup banner echoing the values it actually parsed.

**6. A 0% gate yield is a statement about the INSTRUMENT until a no-input control says otherwise.**
The main lane drafted at 84–98% completion all day and banked ZERO for 3h46m — and every log line
blamed the drafts (`reject func_…`, `COMPILE conflict … drafts declaring it: []`, tries burned,
bisects to MAX_STEPS). One `try_batch([])` control — build the committed tree with NOTHING
substituted — would have named the real defect (`commit:2693` had adopted a mid-flight substitution;
HEAD itself built RED) in ~40 seconds. Measured cost of not having it: ~737 drafts drafted, 160
slated, ~50 clean whole-EXE rebuilds burned, and a day's lane output read as a model failure
(P31 S59, `docs/tool-designs/main-lane-fix-s59.md`). The generalization for ANY gated pipeline:
**wire the null-input control into the failure path itself** — on the first batch failure, gate an
empty slate before judging a single draft, and refuse loudly (exit ≠ 0, sentinel file) when the
baseline is the thing that is broken. Corollary from the same incident: a shared mutable file needs
ONE writer and ONE committer — any "commit whatever is dirty" adopter over a file another process
substitutes into will eventually commit an unverified intermediate, no matter what pre-check it
runs, because the check and the add are two separate reads of a file someone else is writing.

**7. A mechanical-remap lane needs ALL FOUR verdict layers wired in from day one — instructions,
symbols, TU coexistence, whole-binary bytes.** The A-prop lane shipped with two of the four
(match_one shape inside reloc_identity, whole-binary gate at the end), consumed only ONE bit of one
of them (`status==AGREE`, ignoring `shape`), and had NO TU-level oracle at all — so it staged 82
already-refuted drafts per pass while dropping 27 standalone COMPILE-FAILs of which 7 were
byte-perfect in their real TU, and its byte-correct near-0 drafts died forever on TU decl walls
the pipeline had a tool for (fix_arity_callers) but no wiring to. Measured cost: three consecutive
0/117 passes at ~25 min of gate machine each, plus every diagnosis run being a re-derivation.
When it was finally decomposed (P31 S59), the fixes were all one-day work — K&R definitions,
candidate-adjudicated IMM pairing, decl scope/name/direction corrections, rtu_second_chance,
fix_tu_ret_decls — and the same population banked 64+ in one session at zero tokens. The
accelerator: for ANY lane that mass-produces candidates from a template, build the verdict ladder
FIRST (cheapest oracle to most expensive, every verdict consumed, every drop named), and treat "an
oracle exists but the lane doesn't consume it" as a defect with a per-pass machine cost, not a
nice-to-have (`docs/tool-designs/aprop-lane-s59.md`, cookbook §270–§273).

## #12 — Byte-locate the residual before blaming the draft (P31 S61)
`cmp -l built retail | map through <bin>.map` names the first misplaced symbol, its delta, section
and OBJECT in ~2 minutes; name-encoded symbols (D_/func_/jtbl_<addr>) mean the retail address is
already in the name. One derivation replaced days of "CAUSE NOT DETERMINED" backlog rows and
turned 15 mystery walls into three named config repairs. Corollary: gate verdicts need a green
baseline — audit `make build BINARY=<b>` per binary BEFORE trusting any per-draft verdict
(gate_stage now refuses red-listed binaries' drafts as BASELINE-RED).

## #13 — Census what is ALREADY DRAFTED before drawing anything (P31 S67)
`tools/strand_census.py` joins the wave manifests × the filesystem × `corpus.stubs` and answers
"is there already a draft for this open function?" in seconds, for zero tokens. First run:
**193 of the 530 open functions already had a draft** — 37 of them byte-correct in their real TU.
S66 measured the same shape from the other side: ~56 of its 416 banks came from ZERO drafting
agents, and ~109 of 240 agents in two waves re-derived work already on disk or already banked.
The census is worth running *before every draw*, and its verdict classifier (`--classify`, one
`rtu_match` per draft in its real TU) is what turns the pile into lanes: MATCH → gate,
CC1-FAIL → the recovery ladder, NEAR≤3 → register pins, NEAR 8-20 → permuter, NEAR>20 → redraft.
Corollary that paid immediately: the classifier must compile each target the way the game SHIPPED
it — wiring the -O0 prologue tell in turned one binary's verdicts from 8 NEAR (seven >20 mismatches)
into 6 MATCH. A verdict produced at the wrong optimization level is 100% artefact.

## #14 — Make the cheap probe call the real planner (P31 S67)
If a lane is scoped by a cheap feasibility probe, check whether the expensive applier's DECISION
half is separable from its MUTATION half. `jtbl_carve`'s `build_carve` is a pure planner (reads
config + payload, writes nothing, refuses via `sys.exit`), while `--probe` called only
`island_probe` — which answers *where does this table live*, not *can it be carved*. Every blocked
function probed "carveable". Re-probed with the planner: **96 of 159 open jtbl functions are
plan-refused**, and a previous session had priced 32 of them as free work on the blind reading.
Cost of the fix: eight lines. An optimistic probe does not merely lose opportunities — it
manufactures work plans, which is the expensive direction of the error.

## #15 — THE DIFFERENTIAL-ORACLE HARNESS: run every question down TWO paths and fail on disagreement (P31 S68)

**The pattern, counted in ONE session.** Ten-plus blockers, every one the same shape: *a tool
computed a TRUE number about a NARROWER WORLD than the one we believed it covered.* Not bugs —
correctly-scoped tools whose population widened underneath them as new idioms landed.

* `gate_stage` compared `main` against **another binary's SHA** (`build/main/main` and
  `config/check.main.sha` do not exist, so `DEF_SHA` = ov_SC01_077 took over). Every main draft read
  "near" — for weeks.
* `psyq_integrate` dropped `firstfile` on every INCREMENTAL relink, so main was 2 bytes red before
  any draft was spliced. This is the true identity of the long-standing "main link defect".
* `match_one`'s standalone probe called 39 of 43 drafts `cc1-fail` for symbols that ARE in their
  real TU.
* `seed_ref` offered 43 `main` LINKED-subseg stubs as bankable twins — dead text where a draft gates
  GREEN while wrong.
* `wall_sweep` (written that same day) returned a confident **0 across 1,378 files**: the `.s` lines
  carry a `/* … */` prefix and the regex anchored at line start.
* `corpus.stubs` passed while **106 of 213** binaries had no `.s` on disk after a restore that
  printed `212 extracted, 0 failed`.
* Four agents returned `NO-DRAFT` after a rate limit while one sat **3 instructions** from a match,
  its full candidate history on disk.
* §332 stated "6 functions fleet-wide" and named TWO. **A count without an enumeration cannot drive
  a filter**, so the draw kept paying agents to rediscover the class (92k and 289k tokens, twice).

**What caught every single one: two independent measurements disagreeing.** `rtu_match` vs the
whole-binary gate. The standalone probe vs the real TU. A sweep's zero vs a member already known. A
clean rebuild vs an incremental one. An agent's verdict vs its own scratch dir.

**Why the RULES were not enough.** R32 (assert your coverage), R34 (a second DISAGREEING oracle) and
R40 (exonerate the instrument) all existed and are correct. They are *rules applied by whoever
writes the tool* — and in S68 the author wrote R34's warning into one tool's docstring and then
**rebuilt the exact defect it warns about, in a different file, an hour later** (an mtime liveness
heuristic, after documenting that "a quiet file mtime is not a completion signal").

**THE TOOL: a standing harness that runs the same question down two independent paths on a schedule
and fails loudly on divergence.** The pairs exist in any decomp from day one:

| question | path A | path B |
|---|---|---|
| is it matched? | `corpus.stubs` | the built binary / dedup registry |
| does it compile? | standalone probe | the real TU |
| is the fleet green? | incremental build | from `make clean` |
| what does this scanner cover? | its own count | an over-approximating candidate set |
| did the agent produce work? | its returned verdict | its scratch dir |
| is this function bankable? | the draw filter | the toolchain-wall oracle |

**Why build it FIRST, before the cookbook has a single entry.** It is the only accelerator on this
list that works at 0% and compounds. Retrieval needs a matched corpus; triage needs drafts; the
cookbook needs matches. But *two ways to measure the same thing* exist from the first function — and
the value grows with every tool added, because every new tool is a fresh chance to be confidently
wrong about scope.

**Cost asymmetry that makes it obvious in hindsight.** Each of the diagnoses above cost 90k–290k
tokens as a one-off agent investigation. A nightly disagreement report is minutes of compute. Rough
estimate for S68: **about half the session went to harness defects wearing model-failure costumes**,
and that ratio has probably held, invisibly, for most of the project — because a plausible number
never asks to be checked.

**The scheduling half, and it is not optional (Drew, S68):** the widening is PERIODIC, not one-off.
Tooling was correct when written and went stale as new idioms revealed populations it could not see.
So at every session/phase close, review the tooling against the idioms learned that phase and ask
*which scanner's denominator just got wider?* — the answer converts new knowledge into free banks.
S68's own §332 sweep is the worked example: one idiom review, ten functions / 1,027 instructions
reclassified from "hard" to "not bankable at all", and one in-flight escalation stopped mid-spend.

## #16 — A "VERIFIED, JUST BANK IT" CLAIM MUST NAME THE COMPILATION IT SURVIVED (P31 S69)

**What happened.** A session closed with "32 FREE BANKS ARE WAITING", 10 of them personally verified
with `match_one` at closeness 0. The next session gated them: **0 of 28**. Not one failure was a
codegen miss — every one was a declaration conflict inside the real translation unit.

**Why the claim looked true.** `match_one` compiles the draft ALONE, with its own externs. The TU the
function must actually live in already carries a forward declaration written for a call site, and the
draft's real signature conflicts with it. **Closeness 0 is a statement about the BODY. Banking is a
statement about the TU.** They are different oracles and only one of them was consulted.

**Why this belongs in a NEW decomp's day-one kit.** The trap is structural, not local to this project:
any per-function matching oracle compiles in isolation, and every real bank compiles in context. So:

* every "already matches" claim ships with **which compilation it survived** (isolated / whole-TU /
  whole-binary), the way every rate ships with its denominator (R41);
* the isolated oracle's output is a **GATE-FIRST candidate**, never a bank;
* budget for the integration lever, because it is the one that actually pays: 8 of those 28 banked the
  moment the missing lever existed (the self-caller cast, cookbook §378), including one in `main` —
  the project's most expensive binary — for **zero agent tokens**.

**The corollary that cost the most time.** Fixing the first declaration error only REVEALS the second:
no-proto the conflicting decl and the draft's own definition becomes the prototype in scope, so the
same call site now fails with `too few arguments`. A class can look dead after one fix and be three
mechanical steps from banking. Drive the chain to a byte verdict before writing anything off.

## #17 — YOUR SIMILARITY JOIN IS PROBABLY A POINT WHEN IT SHOULD BE A BAND (P31 S69)

**What happened.** This project's twin oracle keyed on an exact signature hash for sixty-plus
sessions. It found **22 of 352** reachable open stubs with a banked twin — 6% — and everything else
read as a singleton. One agent-run added an edit-distance tier over reloc-normalized streams and the
number went to **75 of 352 — 21%, a 3.4x widening on a corpus we believed was fully mined.** Thirty-one
of the new rows were PURE twins of already-banked bodies differing only in relocation slots; ten were
clean, and **eight banked the same day for ~0 agent tokens**. One 94-instruction exemplar served five
open copies.

**Why the hash missed them.** The normalizer under-matched by design: it dropped a pending `lui`-hi
whenever an R-type intervened, so the indexed-global triad kept its `%lo` in the hash (§389). Two
per-overlay copies of one function differing only in a data symbol's ADDRESS hashed differently.

**The generalisable law — and it is about ERROR DIRECTION, not accuracy.**

| the question | wants | a wrong answer costs |
|---|---|---|
| **dedup**: "are these certainly the same?" | under-matching | a duplicated bank; cheap, visible |
| **frontier join**: "is anything close to this?" | over-matching | free work becomes an invisible singleton; expensive, silent |

**One hash cannot serve both.** If you built your similarity layer for dedup — almost everyone does,
because dedup is the first use — then your frontier join is silently lossy, and the loss looks exactly
like "this function is unique", which nobody ever investigates.

**What to do, in any decomp:** build the near tier at the SAME time as the exact tier, not later.
Normalize relocations out of the stream; prefilter soundly on length and opcode histogram so no true
pair can be lost; edit-distance the survivors. Then verify it three ways: assert the population it
scanned (R32), require the band to reproduce every exact-hash pair on every run (R34), and control
against random pairs to get the base rate (1.17% here, so the signal is real). Do NOT retrofit the
normalizer itself — every stored map, ledger and calibration keys on it; read *through* the hole with
a new tier instead.

**Why it matters more for a NEW project than it did for us.** The band pays from the very first bank:
every function you crack becomes an exemplar for everything within a few instructions of it,
immediately. Build it late and you accumulate invisible-singleton debt that costs a whole session to
recover — and you will never know how much you left on the floor, because the tool reports a
confident, true, useless number.

## #18 — A CLAIM DERIVED FROM BYTES IS NOT A CLAIM VERIFIED BY A COMPILER (P31 S69)

**What happened.** A tooling agent reported an open function as "= banked twin minus its final
statement — **resid 0**", listed under "mechanically bankable". Read naturally, `resid 0` means *it
compiles to the target*. It did not: the agent had aligned the two BYTE STREAMS, observed one
contiguous 6-instruction block absent and zero other token differences, and **had compiled nothing**.
Challenged, it said so immediately and cleanly: *"my 'resid 0' was a byte-stream containment fact, not
a compiled draft."* It then produced the draft and the real verification — `{"status": "match",
"closeness": 0, "nins": 98}`. The prediction was correct. **The claim's TYPE was not.**

**Why this is its own accelerator and not just a wording nit.** Every decomp pipeline mixes claim
types that read identically in a report:

| claim type | what it proves | what it does not |
|---|---|---|
| stream/hash containment | the bytes relate | that any C produces them |
| compiled standalone (`match_one`) | the BODY is right | that the TU accepts the signature (§376) |
| whole-binary gate green | this binary is byte-identical | anything about the other 212 |
| clean-fleet R22 | the fleet is green NOW | that a config change was re-extracted (§384) |

A report that says "resid 0" or "verified" without naming which tier it reached invites the reader to
assume the strongest one. Downstream that becomes a bank attempt against a draft that does not exist,
or — worse — a "free win" ledger entry nobody re-checks.

**The standing rule: every similarity or correctness claim names the tier it reached.** "Contained at
d=6 (bytes, uncompiled)" and "MATCH closeness 0 (compiled standalone)" are different sentences and
should look different. Ask any agent that reports a match: *what command produced that number?* If the
answer is a stream comparison, the work is a PREDICTION — valuable, rankable, not bankable.

**The corollary that saved this one:** the reader could not reproduce the number, said so plainly
rather than passing it along, and asked for the file and the literal command. The agent then
self-corrected AND diagnosed the reader's failed repro to the instruction (an invented byte-aligned
type, §391). Non-reproduction is a finding; treat it as one instead of assuming your own setup is at
fault.

## #19 — A VERDICT RECORDED INSIDE AN ISOLATED ENVIRONMENT DESCRIBES THE ENVIRONMENT (P31 S69)

**What happened.** Gating runs in per-worker `git worktree`s for parallelism. One input the carve
step needs — a signature registry — is **gitignored**, so it exists in the main tree and in no
worktree. Every jtbl draft gated in a worker therefore failed its isolation step and was recorded as
**`CARVE-REFUSED`**, a per-function verdict that got written into ledgers, quoted in a census, and
used to classify ~a third of a project's remaining frontier as blocked. It described the worktree.

**Why isolation makes this the DEFAULT failure, not a freak one.** Isolation is introduced for
correctness (no shared mutable state) and its whole point is that the worker sees LESS. Every
gitignored input, every generated file, every symlink you forgot is a difference between "works here"
and "works there" — and the worker cannot tell a genuine rejection from its own missing input. Left
alone, the environment's shortcomings are silently attributed to the SUBJECT, one per function, in
writing.

**The rule: a verdict produced in an isolated environment is provisional until that environment is
proven complete for the class of work it judged.** Concretely, three cheap habits:
1. **Negative-control the environment itself.** Run one KNOWN-GOOD item through the isolated path.
   If it fails there and passes in the main tree, the environment is the defect — this is R40 applied
   to a place, not a model.
2. **Enumerate what the worker needs and ASSERT it**, don't discover it by failure. This project's
   worktree setup already listed five non-obvious pieces (asm/, .venv/, generated headers, submodule
   contents, extract outputs); the registry was the sixth and cost a whole verdict class.
3. **Report a missing input as MISSING, never as a verdict.** The fix here adds the registry to a
   `missing_generated` field that already existed for exactly this purpose — and which, in an earlier
   incident, was populated correctly and *read by nobody* (R32's corrected form: a loud failure nobody
   counts is as invisible as a silent one).

**Cost when skipped:** here, a class recorded as structurally blocked was mostly free work — 21
functions with already-banked twins, ~25 seconds each, zero tokens. The census that said otherwise
was arithmetic on artifacts.

## The agent journals were a labelled corpus we wrote for 30 phases and never read (P31 S71)

**What we did for ~30 phases.** Every drafting agent ends its run with a note: what it tried, what it
measured INERT, which lever moved the residual, where its draft sits on disk. Those notes were written
to `subagents/workflows/wf_*/journal.jsonl` and never read back. When a function refused a wave it went
back in the pool, and the NEXT wave's agent started from the pack — with no idea that three agents had
already burned through the same four levers, or that one of them had left a MATCHing body on disk.

**What it cost.** By S71 the unread corpus was **400 journals / 6,658 result records / 4,853
substantive notes (5.4 MB)**, of which 707 explicitly claim something new/undocumented/refuting, plus
**896 distinct `index_gap` reports** — each one an agent telling us a symptom the cookbook index does
not cover. The functions still open at that point were, almost by definition, the ones that had
generated the most of these notes.

**What it took to fix: one afternoon's tool.** `tools/journal_notes.py` mines the journals per
(binary, fn) and appends a `PAST ATTEMPTS ON THIS EXACT FUNCTION` section to that function's pack;
`claude_wave_packs.py` now calls it automatically, so it is the default rather than a step to remember.

**The measured effect** (S71 wave 1: 50 one-agent workflows over the 210-function real frontier, every
target having already refused at least one earlier wave):

| | with journal notes (S71) | without (S70) |
|---|---|---|
| MATCH at closeness 0 | **38 / 39 (97.4%)** | 124 / 131 (94.7%) |
| pool | the hardest residue | strictly easier |
| agents citing a prior attempt | **29 / 39 (74%)** | n/a |
| banked by RECOVERING an existing MATCH body | **4 / 39 (10%)** | 0 |

**Do this sooner on the next project.** The moment agents write structured notes, wire the read side
in the same change. The rule generalises past decomp: **if your agents produce a per-item report, the
next agent on that item must be handed it.** An archive of your own verified outcomes is training data
for your own tooling (see also `docs/decision-log.md` on the banked-corpus pivot) — and the specific
trap here is that the write side felt complete on its own, because the notes were being *saved*.
