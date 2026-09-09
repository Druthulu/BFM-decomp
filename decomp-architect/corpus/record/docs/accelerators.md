# Accelerators — what we learned late that a future decomp should know on day one

**Purpose (Drew, 2026-08-07):** we are building a reusable **Claude Code decomp workflow**. The
PhaseEnds record *what happened*; `docs/decision-log.md` (R31) records *why we pivoted*. Neither
answers the question this file exists for: **"what should phase 1 of the NEXT game do differently?"**

**Companion (added P31 S59; re-pointed at Phase 33.5):** the how-to chapters (`docs/how-to-ai-decomp/`, which absorbed the
earlier `portable-decomp-workflow.md`, now archived) hold the part that TRANSFERS —
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
substituted — would have named the real defect (`24bd25993` had adopted a mid-flight substitution;
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

---

## #20 — SET YOUR TU BOUNDARIES AT THE RODATA ISLAND'S JUMP-TABLE SPANS, AT SEGMENTATION TIME (P31 S72)

**What it is.** A compiled object contributes exactly **one contiguous `.rodata` run**. A binary whose
switch jump tables sit in an island of several *separated* spans can therefore carve only one span
per code object — so every switch function outside that one span **cannot ever bank**: gcc emits its
table while the raw copy is still emitted from the data segment, the image grows, and every symbol
above the insertion point shifts. The fix is to make the code subsegment boundaries line up with the
spans, because a contiguous run of tables IS one translation unit's rodata (tables pack tight within
a TU, separated by other data across TUs).

**When we found it.** P31 S72, 2026-09-02.

**When it COULD have been found.** **2026-06-15, Phase 7** — commit `038e7de53` wrote the island's
contents into `config/splat.us.exe.yaml` by hand, naming the game jtbls, `loadDestPtrTable @0x80072C70`
as the divider, and the library tables at `0x800737CC+`. Everything needed to compute the spans and
their owner address ranges was in that comment, 2.5 months before it was used. The signal needs **no
matching progress at all** — it is a property of the retail image, readable the day the binary is
first split.

**What it would have saved, and the number that matters is the COST CURVE, not the delay.** The price
of a TU split is the declarations that cross the new boundary, and that grows monotonically with how
much of the file you have matched:

| moment | `src/800.c` | externs | typedefs | what the split costs |
|---|---|---|---|---|
| Phase 6 (file created) | 4,277 lines, 1,998 stubs | 13 | 0 | a yaml edit |
| Phase 7 (island documented) | 2,712 lines | 101 | 0 | a yaml edit |
| **P31 S72 (actually done)** | **27,126 lines, 94% matched** | **2,378** | **175** | 57 crossing decls, 19 typedefs moved to a new shared header, a compile-error loop, and 4 consumers left stale |

It also cost a full session of wrong conclusions: 11 functions were recorded as *"PROVEN gate-rejects,
§376 in its purest form, do not re-slate"* when 10 of them banked byte-identical the moment the carve
existed.

**PREREQ — and this is the honest part.** At Phase 7 you could have *made* the split but not *known
why*. The binding constraint (one object, one contiguous `.rodata` run) and the carve machinery came
out of the OVERLAY work in Phase 26 §8 / Phase 29 §8e. So this is not "we were careless in Phase 7";
it is knowledge that arrived from a different population two phases later and was never carried back
to `main`. **The transferable advice is therefore for segmentation time on the NEXT project, where
you can carry it in from day one:**

> Before writing the first subsegment list, dump the target's `.rodata`/data island, mark every jump
> table, group them into contiguous spans, and map each span to the address range of the functions
> that reference it. **Put your initial code-subsegment boundaries at those ranges.** At 0% matched
> this is free — there are no declarations to reconcile because there is no C yet — and it removes a
> class of wall you will otherwise hit at 90% completion, on your largest and most valuable functions.

**The general principle, which is worth more than the specific recipe.** Most of this project's
discipline is *probe before investing* — do not build tooling on speculation. **Segmentation is the
exception.** Structural decisions get monotonically more expensive as matched work accumulates, while
the evidence for them is available at t=0 and never improves. For that class, the cheap moment is the
earliest moment, and deferring is what costs. When a decision is (a) evidenced from raw data, (b)
cheap now, and (c) strictly more expensive later, make it early even though its payoff is unproven —
that is the opposite of the default instinct, and the reason to write it down.

**THE RULE — WHEN TO SPLIT, AND WHEN NOT TO.** The temptation is to split wherever you think the
original developers did. Don't: split where the **BUILD forces a boundary**, which is decidable, and
nowhere else, which is not.

* **SPLIT when the layout proves it is required** — a code subseg owns raw jump tables in two or
  more non-adjacent island spans. Then every switch function outside the one carveable span is
  unbankable at any effort, and no amount of drafting skill changes that. **This is decidable at 0%
  matched, from the raw image, with no attempt needed:** find the tables, group the contiguous runs,
  map each run to its referencing functions' address range, and check whether two runs land in one
  subseg. You never have to try-and-fail to establish it.
* **SPLIT AT THE SPAN-OWNER BOUNDARIES AND NOWHERE ELSE.** The minimum that satisfies the constraint
  is the right answer. Extra splits buy nothing and cost declaration duplication across every new TU.
* **DO NOT split on TU archaeology alone.** "The devs probably had a file boundary here" is not a
  reason. We cannot even establish it: a TU containing no `switch` emits no table and is invisible to
  this signal, so the spans are a LOWER BOUND on the original structure, never a reconstruction. Our
  split is correct because the build requires it, not because we are certain about 1998 — and if the
  real structure was finer, a coarser split is still correct, just coarser.
* **The same reasoning generalises to every forced boundary:** interleaved library objects and
  per-file optimisation levels also force subseg splits. Jump-table spans are simply the one that is
  easiest to miss, because nothing fails loudly — the functions just never bank.

**IT IS A TOOL NOW, NOT A PARAGRAPH.** `tools/split_indicator.py` implements exactly that check and
runs in `make tools-health`; `--self-test` proves it fires on main's pre-S72 island, stays silent on
main today, and does not over-fire on a one-span subseg. **First fleet run: 209 of 213 binaries OK,
and 4 overlays flagged holding 16 open functions / 3,613 instructions** — 18% of the non-main
frontier, all previously sitting in the exclude list as if unmatchable rather than as "needs a
subseg split". Linked-library subsegs are excluded on principle (their code comes from a `.a`, so
cc1 emits no table for them); leaving that filter out made main report NEEDS SPLIT on `libgs6`.

**Companion:** the *method* for doing the split late, if you inherit a project that did not do it
early, is cookbook §431 (cut verbatim, let the compiler enumerate what crosses, MOVE typedefs to a
shared header, and check every consumer that hardcoded the old filename).

---

## S77 — three accelerators, all of the same shape: make the tool state its own denominator

**1. A tool that derives a byte-exact fact from a PRETTY-PRINTER inherits its liberties.**
`psyq_identify` built its match pattern from `objdump -dr` disassembly lines, and objdump collapses
runs of identical words into `...`. It read **520 words for a 526-word object**, misaligned, and
printed "not linked by EXE" for objects that are linked — **25 objects / 3,877 instructions
invisible**. The check that would have caught it on day one is one line: **compare the parsed word
count against the section size.** Generalisation: whenever a tool parses a human-facing rendering
(objdump, nm, a compiler's stderr, a report), assert the parse against the underlying size or count.

**2. A refusal-check must be measured against what the real pipeline does to the input, not against
a model of it.** `gate_main`'s clash pre-check matched *indented* (block-scope) `extern`s and
compared them to file-scope spellings — stricter than cc1, refusing 566 instructions of correct
work. `blocker_probe` reported `local_type` blockers the real gate strips before cc1 ever sees them.
Both would have been caught by running the check over work that ALREADY SUCCEEDED (R39) — which is
cheap, and which is now the standing rule for any new refusal.

**3. An exclusion reason is a claim about the TOOLING on the day it was written.** A Phase-8 comment
said four PsyQ objects were unlinkable for "scattered `.bss` commons — no single NOLOAD base". Every
word true; three of the four are still not blocked by it (two have no `.bss` at all, and `SYS.o`'s
two bases have disjoint offset ranges so the section splits). Same shape as the wave exclude-list
lesson, and the same fix: **when the reason names a mechanism, re-derive the mechanism's PREMISE
from the bytes before accepting its conclusion.** Cost of not doing so: 3,109 instructions of
library code sat as verbatim asm for twenty-odd phases.

**Would-have-sped-up-earlier-work verdict.** None of these needed a new technique or a better model.
All three are self-assertions a tool can make about its own output in under five minutes of code,
and each was worth thousands of instructions the moment it was added.

## S78 — the loader shipped the answer key: per-version SDK signatures name library bands you cannot link

`ghidra_psx_ldr/data/psyq/<ver>/<LIB>.LIB.json` — masked signatures + labels per object, 2.6 → 4.7 —
sat on disk since Phase 1. Regexed over the EXE bytes it names the library, the version and every
function of a band **without the `.LIB`**, and it would have settled main's `800c3` band (LIBPAD
4.2.1: twelve "wall" stubs, four §332 verdicts) in Phase 8, the day the 4.2 stamps were first read.
Accelerator: **before calling a band a compiler wall, score every signature set you have against it;
the version that places the most objects byte-exact is the linked one.** Second, cheaper lesson: the
gates only ever built main WITHOUT the SDK objects (worktrees carry no `.run/obj40`), so the LINKED
path was never gated — `make build BINARY=main` in the real tree is the only check of it; run it
after any change to `psyq_identify`/`psyq_integrate`.

## S78 (2) — check a percentage against a case you already know the answer to

`MAIN game-code weighted 59.8%` stood for six weeks. Its remainder (~32,000 ins) never matched the
frontier's own stub sum (~4,000 ins), and nobody subtracted the two. One subtraction would have shown
the denominator was carrying the 31,000 linked-SDK instructions. Accelerator: **every headline % ships
with its remainder, and the remainder is reconciled against an independently-derived list of what is
actually open.**

## S79 — "no single base" means "partition it", and partition along the producer's structure

Three SDK objects sat excluded for twenty-three phases as "scattered `.bss`, no single NOLOAD base".
The general fix (cut the section into per-base NOBITS pieces at link-prepare, ~400 lines of ELF
surgery, `tools/psyq_bss_split.py`) took one afternoon and closed the class 3/3 — including the object
the previous session's probe had certified as a genuine wall, because that probe grouped by base while
the original linker had scattered SYMBOLS. Accelerators: **(1)** a "no single X" verdict is a
partition problem, not a wall — build the partition the day the exclusion is written; **(2)** partition
along the structure the original producer used (the symbol table), and confirm every cut against an
independent oracle (here the other objects' by-name recoveries agreed on all seven cuts); **(3)** put
the transformation in the shared prepare path, not in a curated artifact, so it is re-derived from the
bytes on every build and negative-controlled over the whole placed population for free.

## S79 (2) — provenance → archive → link → compiler, in that order

Twelve stubs in one band carried compiler-wall verdicts from three sessions of wall-sweeping. The band was
Sony's controller library; the exact library was a 383 KB archive.org download away; every object linked
byte-identical on the first try. Accelerator: **before any wall verdict on a function in a mixed binary,
ask whose code it is and whether the shipped object exists** — the loader's signature sets name the
library and version for free (§487), and the SDK archives are indexed on archive.org by version. A wall
verdict on code you were never going to compile is correct and worthless.


## S80 — five accelerators from a two-task session, all "the instrument was the wall"

**(1) A tool that reports "unchanged" for N cycles must prove it iterated.** `permuter_ils` re-copied the permuter's
DECODED waypoint (raw register pins) into `base.c`, so every cycle after the first on a pinned seed was a parser refusal
printed as "(unchanged)"; `hide_asm` knew only the `__asm__` spelling; `defines_fn` could not see a K&R definition and
had refused **436 stored backlog drafts for four phases**. Every permuter verdict on a pinned or K&R seed before S80 was
one cold cycle. Accelerator: an R61a "not judged" state in every loop tool, and an R39 control over the WHOLE stored
population when a parser/regex changes (the control caught the fix's own false positive — the bare word `asm` inside
`INCLUDE_ASM("asm/…")` path strings). Cost of not having it: a month of "permuter-class plateau" verdicts that measured
nothing. (`7fbdb8fd6`, cookbook §493 S80 correction.)

**(2) A byte gate is a null oracle for "is this C?".** S79 #7 spliced a function's ASSEMBLY as a file-scope `__asm__`
body and counted it banked — `rtu_match` MATCHes it by construction, the build is green by construction, `progress.py`
counts it. `verbatim_check --strict` caught it one session later. Accelerator: run the strict verbatim check in the
per-bank close (not only in tools-health), and never let a ledger's `best_draft` be an `__asm__` body (R62 candidate;
§495). Cost: one fake bank and a census one function off for a session.

**(3) A pointer-only callee's `extern` is a guess, not a constraint.** `extern void func_8017D878(void)` existed only
because the TU takes `(s32)func_8017D878`; the function returns an address or 0. Thirty-seven drafts died on
"conflicting types" against a declaration that carried no information. The same session: a block-scope `extern … (struct
S *)` declares a BLOCK-LOCAL tag no file-scope definition can match. Accelerator: when a real-TU compile refuses a
standalone MATCH, read the TU's own declaration of the FUNCTION before touching the body — and treat a pointer-only
callee's decl as unconstrained. Cost: 37 drafts on a 45-instruction function that was byte-correct on its first try.

**(4) "banked 1 / merged 0 / REFUSED 0 / exit 0" is a failure that prints as success.** `parallel_gate` banked a function
in its worktree and adopted nothing; the bank died with the worktree and the fixed-path results JSON was overwritten by
the next run before anyone looked. Accelerator: every "X produced but Y consumed" pair in a pipeline gets an assertion
(X − adopted − refused = 0), a non-zero exit, and per-run evidence files. Cost: one lost bank, re-done by hand.

**(5) Agent-tool drafters outlive the session that spawned them.** Their final JSON verdict sits in the transcript
(`~/.claude/projects/<proj>/<session>/subagents/agent-*.jsonl`); `tools/agent_verdicts.py` extracts it without loading a
transcript. Accelerator: when a session must end mid-wave, let the agents finish and harvest by tool; two of eleven
were MATCHes worth 765 instructions. Cost avoided: re-drafting eleven functions.

## P32 T3 (2026-09-05) — 31 concurrent one-agent-per-function drafters (cookbook §500, playbook §S80 addendum-2)

**(1) A coordinator that reads prose results dies mid-wave.** The producing session overflowed four minutes after its
ninth bank; 22 verdicts (two MATCHes worth 724 ins among them) sat unprocessed until a successor session replayed the
transcripts. Accelerator: the agent's final message is exactly one JSON line; prose goes to a report file. Cost: one
session boundary and ~45 minutes of recovery.

**(2) A shared scratch directory is a shared blast radius.** One agent's `find … ! -name <mine> -exec mv {} _scratch/`
swept eleven sibling deliverables out of the contract path (R48 class: bare-name files in one dir). Accelerator:
per-function work dirs and a deliverable dir no agent cleans; recovery = `tools/agent_drafts_restore.py` (transcript
replay) — but check the `_scratch/`-style dir first, the files were moved, not deleted. Cost: a new tool and an hour.

**(3) A converged multi-agent plateau is not a mechanism proof.** `func_8001BC6C`: five agents converged on 28 with an
"RTL-proven sched1 unreachability" — the real blockers were two source-idiom errors (a hand-written mask pair that is
the libgpu P_TAG bitfield; a `fold`-reassociated or-tree). `func_8002FDE8`: four attempts called 35 a "regalloc-priority
wall" while two same-TU neighbours (`src/800_b_2.c:2866`, `:3000`) documented the exact fix (block-scope scalar extern vs
the TU's array spelling). Accelerator: the pack must carry the same-TU neighbours' DECLARATIONS of the shared globals
(not only their bodies), and a plateau verdict must name the exemplar it was checked against (R38/R40). Cost: eight
agent attempts across two sessions on two functions that closed in one pass each.

**(4) The §47 slider is a computation, not a search.** `-dl -dg` prints `n_refs`/`live_length`; `floor_log2(n)·n/L`
says exactly how many static instructions a fence must add and where. 118 fence-position variants had plateaued at 4
before the arithmetic was read (`func_8002FDE8`). Accelerator: read the `.lreg` numbers before sweeping fence positions.

**(5) The BUILD is the batch verdict; a per-draft oracle is blind to cross-draft integration (P32 T3 S83).** Eleven of
twelve same-TU drafts were `rtu_match` MATCH alone and the batch failed twice — a `s16`/`u16` spelling of one global across
two drafts, a §304 rodata block only the stub `.s` had defined (undefined at LINK, invisible to a compile-only oracle), and
a prototype a sibling bank added between an agent's verification and the splice. Accelerator: (a) a per-TU bank chain —
verbatim grep → rtu ×N in the CURRENT TU → splice ×N → ONE build → sha → commit only on green, tree left for diagnosis on
red (`.run/P32/t3s3/bank.sh`; the shape `rtu_match --batch` should take); (b) two sentences in the drafter brief (define
any `dlabel` block your `.s` owns; spell shared symbols exactly as the TU does) made the next agents self-serve it.
Measured: 17/17 Haiku MATCH on the ≤25-ins module band at ~50k tokens each; the coordinator's whole cost was the plumbing.

**(6) Read a permuter waypoint's diff before rejecting OR accepting it (R63 both ways).** `func_8001BC6C`'s masked "1"
carried a wrong-width load (`lhu`→`lbu`) — but subtracting that one mutation left two sound levers that were the entire
answer (6 → 0). Accelerator: on a waypoint with a semantic mutation, diff it against the seed, drop the unsound hunk,
re-measure the remainder; then re-spell any uninitialised-read trick well-defined (`k = 0; tag = (a1 << 8) | k;` kept the
bytes; five "cleaner" spellings did not — the lever was the pseudo's BIRTH point, the §47 slider again).

**(7) A tool's live probe in `src/` is part of the build's input.** `make` parsed `find src -name '*.c'` while another
agent's `src/.masked_diff_probe.<pid>.c` existed and compiled after it was deleted — gate_main reported a false batch
FAIL and spent a rebuild. Accelerator: guard at the consumer (`-not -name '.*'` in the Makefile's find) so every probing
tool is covered at once; a probe tool that must live in `src/` should also be listed in the cookbook §500-E3.

**(8) Re-probe a CC1-FAIL wall in a SANDBOX TU, not by editing `src/` (P32 T4 S83).** Three of seven pinned walls failed to
compile in their TU for declaration reasons only (header typedefs a draft duplicated; a narrow-typed prototype vs a K&R
definition; a load-bearing `[][1]` extern vs the TU's `[]`). Copying the TU under `.run/`, symlinking `src/*.h` +
`src/shared` beside it, editing the declaration THERE and passing `--tu <copy>` to `rtu_match` reproduced every residual
(1/2/3) with zero commits to `src/` — the byte-neutral TU edit is deferred to the day a row reaches closeness 0.
Accelerator: `rtu_match --tu` accepts any path; a sandbox costs one `mkdir` + two symlinks.

**(9) A lever that measures worse may be a cascade (P32 T4b, `func_800391D4`, §501).** The hand pass measured the right
lever (explicit promotion before `off = 0`) at 18 and moved on; the agent's `.loop` dump showed the 18 was ONE hoist that the
lever's -2 in-loop instructions had flipped past loop.c's desirability threshold, paid back with two more `__asm__("")` pads →
MATCH. Accelerator: on any regression of a mechanism-grounded lever, diff the pass dumps for a second change before discarding
the lever; treat `insn_count` pads as a dial that must be re-counted after every in-loop instruction change.

**(10) Fable on the compiler-internals class: 9 of 12 completed rows banked where every prior tier had 0 (P32 T4b S83).** The
twelve rows were the residue of Sonnet/Opus waves, an Opus second look, ~16k permuter compiles and a bounded hand pass; one Fable
agent per row (~2 h, ≈325k tokens each, 123k–655k) banked nine — six of them pinned "walls" whose citations named the wrong
pass. The common move was reading the pass dumps (`-dS` ready lists, `.loop` desirability, `-dl` priorities, `.greg`, `-dR`)
against the 2.7.2 source before the first probe. Accelerator: route a row to Fable when its blocker is an unread compiler pass;
route it to Opus once a sibling's recipe exists (§501-H for the md_MAIN_007 pair). Budget for three usage-limit outages per
batch and resume with SendMessage; make agents write the draft and report EARLY (the one crack recovered from a dead run had).

**(11) Attribute the residual to a PASS before sweeping levers (P32 T4b, all nine cracks).** Every T4 wall citation named a
mechanism; six of seven named the wrong pass, and 22 hand-pass spellings plus ~4,000 agent sweeps of the wrong lever family
measured nothing. The cracks came from one dump each: the `7f000001` birthing boost in `-dS` (§501-C/D/G/H), the `.loop`
"not desirable" line (§501), the `-dl` quantity priorities (§501-B/E), the `.greg` "Register N in M" (§501-B/E), the `-dR`
hazard walk (§501-G). Accelerator: a residual's first artefact is the dump line that owns it — `tools/cc1_dumps.sh` gives all of
them in one run; a wall verdict without a pass and a dump line is a hypothesis, not a proof (extends (9) and R40).

**(12) Enumerate the artefact's PRODUCERS from the compiler source before probing a single spelling (P32 T4b hand pass,
`func_80032A74`, S84).** Two sessions (S79 ~200 byte-probes + a 100-variant sweep, S83 22 spellings, a 402k-token Fable agent)
had chased the 8 phantom frame bytes as a spelling problem. Reading every stack-slot allocation site in reload1.c /
caller-save.c / combine.c / local-alloc.c gave a four-row producer census, and each row died on a fact already in the bytes
or a dump — the site's `lhu`, the call blocks' contents, the spill register's identity (`lw $t0` ⇒ no pseudo lived in `$t0`),
the mult results' alternate class — without compiling a variant of the draft (18 isolated reproducers, 0 draft variants).
It also found a new ghost producer (`optimize_reg_copy_2`, §501-M) and measured why it cannot slot. Accelerator: a frame
residual gets a producer table first (`tools/cc1_dumps.sh` + `tools/ghost_census.py`), a spelling sweep last — and a
"PROVED" verdict is the table with every row refuted, not a sweep that came back empty (extends (9), (11), R40).

**(13) When a same-family sibling is banked, port its SPELLING with the row's constants before touching a dial on the draft
(P32 T4b hand pass, `md_MAIN_007:func_800CF408`, S84).** The row had consumed three agent passes, a 135-variant sweep and a hand
pass on a draft that carried five dials (named mask, base pointer, two temps, a dead parameter kill); its residual class had
been named correctly (§501-H/L) and every cure oscillated. The banked sibling `func_800CD92C` (§501-H, same four-prim family)
had matched with the plain libgpu shape; porting that body with this function's constants matched first try — the only work
was the TU's `u8` declaration of the OT symbol, solved by the fleet's asm-label alias (§501-N). Accelerator: a wave card for a
row whose family has a banked exemplar must carry that exemplar's SOURCE as the seed (family_cousins/seed_ref), and a hand pass
must open with `grep -l` for the family's banked bodies; a residual-class name is the family's signature, not a lever list.

**(14) The atlas's similarity score is not a shape oracle — grep the idiom's CONSTANTS and read the sibling's OBJDUMP window
(P32 T4b hand pass, `ov_SC03_105:func_80185810`, S85).** The row had consumed an Opus pass, a 655k-token Fable pass with a
3,360-variant sweep, five pins and a fence, and sat at DIFF 13 with its mechanism correctly read and its cure judged blocked. The
atlas had listed the answer all along as a 0.55 "weak cousin" (`ov_SC02_027:func_80180B3C`): a grep for the getTPage chain's
constant (`'0x200) << 2'`) across `src/` surfaced it as the same billboard drawer, and its compiled window was the target's rows
362–386 verbatim. Porting the spelling matched in one draft, then with every pin removed (§501-P). Accelerator: before ANY
scheduling/allocation dial on a packet-building function, grep `src/` for the idiom's literal constants (tpage chain, prim codes,
`+ 0x100) << 6` cluts, `0xE1000000` tags) and objdump each hit's window against the target; a same-shape sibling with different
base registers scores as a stranger in every similarity metric we have, and its spelling is worth more than the diff's
mechanism (extends (13); the twin oracle, family maps and atlas knn all reported nothing for this row).

**(15) Re-run the producer census with combine's bookkeeping in view before writing "PROVED" (P32 T4c, `func_80032A74`, S85).**
Two sessions and a Fable agent had proved the 8-byte orphan unreachable; the proof's census enumerated reload's slot
producers but not combine's `i2dest_in_i2src` gap (combine.c:2306), which leaves a pseudo with references and no insns.
Eighteen 1-second reproducers found it (§501-Q); the bank was one three-statement chain. Accelerator: a "PROVED" frame
verdict needs the reproducer battery (`tools/cc1_dumps.sh` on 5-line functions) for every ghost SPECIES, not only the ones
already in the cookbook — and the S84 statement "only combine mints those" was right; the list of combine paths was short.

**(16) Read the allocation ORDER before the register (P32 T4c, `func_80039308`, S85).** Forty variants tried to steer one
hoisted value into $s2 with pins, dead mentions and sliders; the dumps' "regs to allocate" line + `tools/alloc_table.py`
showed in one read that the callee-saved bank is global's priority order (refs/live length) and that the value needed
exactly 7 weighted refs = three body reads — which forced the source shape (three inline expressions + `u16 vol`, §501-R).
Accelerator: for any callee-saved-register residual, dump the REAL TU (`tools/cc1_dumps_tu.sh`) and print the allocation
table first; the number of uses the target's register order implies is a hard constraint on the C, and pins only mask it.

## P33.5 S91 (2026-09-07) — four accelerators from the kit's dry-run and the tools audit

**(1) An ignore file's directory-form rule is a wall no later block can climb.** ProjectArchitect writes `.run/`; git never descends into
an excluded directory, so the kit's `/.run/*` + `!/.run/README.md` beneath it could never re-include anything, and the kit's own
"never edit above a marker" rule forbade the one-line fix. The source project's conventions page had documented exactly this since
Phase 33 — the knowledge existed and the kit had not carried it. Accelerator: the by-contents form (`/.run/*`) must be the FIRST rule
under a scratch directory in any ignore file a governance system stamps, and a kit that overlays another system needs a named
exception for the one line it must rewrite. Cost: one dry-run stop (~200k tokens) and a resume.

**(2) A check that compares a typed figure against a derived one is wrong the day the derived side moves.** Run 4 stopped on
`321 != 293`: the installer's manifest check compared a whole-file row count against the header's LIVE figure, which excludes the
superseded-pointer table the census had just added. The file was right; the check was a number I had typed. Accelerator: when a
tool derives a figure, make the checker read the SAME tool's stated total (the header now prints live, pointers and total), never a
sibling figure with a different scope — the same rule as the published-numbers rule, applied to a verify line. Cost: one stop and a
resume (~100k tokens).

**(3) A dry-run judge is an instrument; negative-control it before believing its FAILs.** Two of the judge's failures across four runs
were the judge's own scope: its placeholder grep did not exclude the still-present installer package, and its dirty-tree count caught
the coordinator's own edits (and once the timeline regenerated by a detached health run). Accelerator: compare dirty PATH SETS with an
explicit allow-list of the coordinator's own paths, scope every audit past the packages it is auditing, and attribute each foreign path
before calling it a write by the subject — the retrospective's "exonerate the instrument" for the harness that judges the harness.

**(4) A tool without a dictionary row is invisible to the project that owns it.** 326 tools, 224 SETUP rows written over thirty phases,
and still 91 with no runtime consumer and no way to find them by the need they answer. The census + a hand-kept dictionary with
coverage asserted both ways turned that into a need-keyed index in one task, and the retirement review found 28 superseded tools
whose successors had existed for phases. Accelerator: from the first phase that has ten tools, adding a tool means adding its
dictionary row (need · phase · what it hard-codes) or the health check fails; the index is generated, and the kit's corpus is
generated from the same row.

## P33.5 S92 (2026-09-07) — the log-mining pass: the distillation had never read the worklogs, and a coverage check found what the kit lacked

Drew asked whether the kit held "the whole of our experience". Measured from the kit's own provenance lines: the tools and the cookbook
were in verbatim; the rules were a distillation citing 57 of 83; the kernels cited 40 of 53 accelerator entries; **no PhaseEnd and no
phase worklog was cited anywhere** — the kit had been written from the summaries (this ledger, the decision log, the retrospective, the
how-to), never from the 30,510 lines of `phase-ends/logs/`. Three things followed in one task. **(1) A coverage check for a
distillation** (`tools/kit_coverage.py`): derive both source populations (every rule from the digest, every entry of this ledger at
numbered-item granularity) and refuse one that no kit provenance line cites unless an authored map says where it went. Its first run
found 26 uncited rules and 21 uncited entries; three were genuine gaps and became kernels (a ledger's tie-break, a checker's widening and
a blanket commit are part of the instrument; the ignore file's directory-form wall; a summarised signal is a claim, not ground truth).
**Accelerator: a distillation ships with a coverage check against the populations it claims to distil, or it silently drops the lessons
nobody remembered to cite.** **(2) The record as a verbatim dictionary** (`decomp-architect/corpus/record/`): the how-to, this ledger, the
decision log, the retrospective, the story, the playbook, the effort doctrine, the readability charter, the digest and every PhaseEnd,
asserted equal on every health check, so that a rule's or kernel's provenance line leads to its evidence. **(3) The worklogs, read once
more:** 21 read-only agent slices over the 26 logs (the three giants split by line range), each briefed to extract only lessons that a
grep over every distilled record could not find, with the greps recorded — **777 candidates, 634 already banked, 143 new**, every cited
log line verified to exist and to say what the candidate claims, clustered into twelve kernels (DK-69–DK-80: instrument blind spots;
verdict staleness and the health suite; what earns belief; denominators and units; leverage versus tractability; models and prompts;
the unattended run; agents and the tree; edits that keep their proofs; the search harness and the compiler as evidence; maintaining the
knowledge base; hosts and services), each provenance line naming the worklog lines. **Accelerator: the "capture while it hurts" rule
does not capture everything — an end-of-project pass over the raw worklogs, with an "already banked?" grep per candidate, recovers the
lessons that were fixed but never generalised; on this project one in five candidates was such a lesson.** Cost (R41): 21 Opus agents,
~4.3M tokens, ~13 min wall each in two batches; the coordinator's cost was the brief, the harvest script, the clustering and the
provenance generation.

## P34 S93 (2026-09-08) — the flip day: a third-party step proven through the third party's toolchain, and the public-tree decisions

The one failure of the flip day was a browser step nobody could have exercised while the repository was private: `docs/decompme-preset.md`
told the owner to paste the regenerated target listing into decomp.me, and decomp.me's assembler refused it (`invalid operands 'li a2,2'`).
The listing is the project's word oracle — nothing on our side assembles it; its bare register names resolve only through `macro.inc` and
its branch targets are absolute addresses — and the replica that had "proven the preset" compared words from the listing's comments,
never the listing itself. **Accelerator: a step that hands a file to a third party is proven through that party's own toolchain, on the
file itself, before the owner's browser session — and the tool that proves it writes the paste** (`verbatim_target_s.py --gas`;
`decompme_replica.sh` steps D and E; the retry matched 100% first time). Two smaller ones from the same day. **A calendar gate is read
the morning after the ticket, not "daily for a week":** the Support purge took one day; the probe passed during the previous sub-phase and
the flip could have opened a day earlier. **Decide what a public tree carries before the flip:** the sent outreach drafts and the
document archive were always going to leave (the owner removed both within hours of going public), and deciding at the consolidation
sub-phase would have spared two untrack commits on a public history; the Archive-index rule that made the removal harmless — name
archived files as paths, never links — held.

**P35 S94–S96 (2026-09-08) — the dedup phase.** (1) **A read-only replay of the artifacts beats a re-run:** the dead session's scratchpad
still held the `cc1.err` of its last replay; reading its non-warning lines gave the real cause (`too many arguments to function`) that
303 rejection lines had hidden behind "Error 33". (2) **Measure a disagreement between two oracles before believing either:** the text
oracle's 4,312 hits decomposed into twin false positives (3,495), the gate-1 deferral (380), and 38 genuine byte-variant functions —
each a different action. (3) **A known-true control per join:** the registry repair's first cut removed 9,269 members; one control
(`ov_SC01_004` includes `func_80146E90`) exposed the name-only match. (4) **One batch per invocation on a committed tree** turns a
multi-batch tool's hardest bug (stale line numbers + a restore that wipes the previous batch) into a non-event; the driver commits
between batches. (5) **The census's per-instance forms are the registry check's C2d for free** (one cached scan, 36 s) — derive, don't
re-parse (R33).
