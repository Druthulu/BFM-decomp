# Accelerators — what we learned late that a future decomp should know on day one

**Purpose (Drew, 2026-08-07):** we are building a reusable **Claude Code decomp workflow**. The
PhaseEnds record *what happened*; `docs/decision-log.md` (R31) records *why we pivoted*. Neither
answers the question this file exists for: **"what should phase 1 of the NEXT game do differently?"**

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
