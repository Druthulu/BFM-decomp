# 10 — Integration and propagation: matching is solved; banking is the bottleneck

> *The source project's tools for this chapter's steps, keyed by the need each answers: [the tool index](../tool-index.md).*

The efficiency audit that became BFM's thesis for the rest of the project (decision log, 2026-07-24): **the bottleneck
is integration, not idioms.** At one measurement about 92% of drafts were byte-correct and about 27% banked; with the
codegen map in hand, 11 of 12 first-pass drafts from ordinary agents matched — and every bank failure was
translation-unit plumbing. Build the integration layer *before* the drafting layer, and budget for banking, not cracking.

## The integration classes

A byte-correct body fails to bank because of the *file* it must live in, never because of its own bytes:

| Class | What it looks like | The lever |
|---|---|---|
| **Declaration conflicts** | the draft's `extern` for a callee or a global disagrees with the file's (arity, `s16` vs `u16`, `void` vs `void *`); or two drafts batched into one file disagree with *each other* | a declaration-sync tool that reconciles a draft to the file's consensus; callee casts at the use site; a canonical-signature layer that all files declare against; when batching, greedy in-order resolution that reports the dropped set (they are usually correct and recoverable with a cast). Compare **type signatures only** — a checker that compared parameter names discarded good work (an R39 catch) |
| **Def-side loose typing** | the body matches standalone and not in place because the *definition's* own signature in the file differs from what the bytes were compiled with | def-side canonical-signature reconciliation; self-declaration normalization |
| **Symbol spellings** | the decompiler's names vs. the linker's names; a curated rename the draft did not know about | normalize to linker names; a lint for stale renamed references; never key a draft by bare function name (R48) |
| **File placement** | the function belongs to a translation unit whose optimization level differs, or whose boundaries the split drew wrongly | the opt-level detect/carve chain; set translation-unit boundaries at the rodata island's jump-table spans at segmentation time (accelerator #20) — a function whose jump table sits in an island between two others needs its own file |
| **Jump-table carves** | the splitter cannot place a switch's table; a subsegment owns raw tables in more than one non-adjacent span | the carve tool; a fleet check that refuses a carve that cannot build; carve state (the yaml + registry lines) belongs to the binary that owns it — a gate commit carries only its own binary's lines (R60) |
| **Vendor objects** | a band of "compiler walls" that are the vendor's library; scattered `.bss` in those objects | provenance → archive → link; a link-time `.bss` splitter |
| **Missing data carves** | eleven "proven gate-rejects" | one missing rodata carve, judged by a one-off script that had skipped the real gate's pre-check — a verdict names its instrument |

The rule of thumb from a class that was called dead too early: **a standalone match is not a bank** — before calling a
class dead, run the whole chain (arity fix → self-caller cast → declaration sync → the real-TU probe → the gate).

## Recover before you re-draw

After every gate, triage its failures into **body** rejects and **plumbing** rejects; the plumbing ones bank without a
new draft through the ladder above. BFM's recovery tools — declaration restore, declaration-from-use, a prior over
declarations, a slate reconciler, a second-chance real-TU pass, a shadow compile, a reject recoverer — exist because
the alternative was paying an agent to redraft a body that was already right. The wave procedure's step is *gate →
recover → gate → siblings → verify → harvest → checkpoint*, in that order, every time.

## Propagation: one crack, many banks

- **Dedup** — a body matched in one binary is authored once (as a macro in Gen2; as a plain-C header included at each site since Phase 35, sotn's shape) and instantiated at every member
  site, byte-gated per member, and registered in a fail-closed registry validated on every health check. Source-level,
  because interior functions cannot be excised by the linker. (BFM: 2,220 groups, 255,708 instances.)
- **Structural families** — same skeleton, per-location relocations and immediates: crack one exemplar, remap the
  siblings mechanically, gate each. Measured at 88% of exact-hash and 80% of normalized families; the ceiling is
  translation-unit type collisions, not bytes. Enumerate banked twins *before* drawing any wave — cards once omitted
  the join and agents redrafted functions whose answer was already banked. And measure per tier: a "families are
  SPENT" verdict that steered two phases was true of the mnemonic-sequence tier only.
- **Twins as a band** — an edit-distance band (d ≤ 25) reached 3.4× more open stubs than the exact hash; rank
  candidates by *work* (substitutions + regions, coverage), not distance — a deletion is free, a substitution is
  thought; filter lookalikes (two different functions sharing boilerplate: a wrong twin is worse than none, because the
  agent believes it). **Rescan after every bank** — the graph changes with each; never draft two members of one open
  cluster.
- **Constant flips, pass-throughs, reloc-only twins** — remaps with an edit; zero drafting tokens.

Propagation is what turns the bootstrap order of [chapter 03](03-bootstrap-order.md) into leverage: with it, every
crack compounds from match #1; without it, every match is worth ×1.

## The honesty rules

- **A gate verifies the source binary; propagation writes N others.** The clean fleet run follows every propagating
  gate; one propagated overlay once sat red behind a green fleet.
- **Commit the moment a bank exists** (R42) — a gate is a command that can touch the source.
- **Key by integer address, never by name** (R48); a carve's state belongs to its binary (R60); a blanket commit of
  another lane's mid-gate tree is a race, not a backup (R59).
- **A newly-discovered binary is not real until every consumer knows it** — signature set, family map, dedup registry,
  shared-header include, reports — asserted by a gate, not remembered (R36).
- **The dedup backlog is orthogonal to completion — and it is the readability phase's first job**: Gen2 left thousands of already-matched duplicate copies (right for completion %, gates ran with `--no-propagate`); Gen3's first phase gave every unique function one source, with the invariant asserted by a gate. The old rule (leave it) applied while matching was the goal;
  propagate deliberately, gate with propagation off by default.
