# 07 — The compiler's source: "unsteerable" means "not yet read"

For six phases BFM called a class of residuals *unsteerable*: diffs that resisted every source rewrite — a phantom
callee-saved register, a load stuck below a store, a spill slot in the wrong place. Phase 23 is the one the record
calls **THE BREAKTHROUGH**: agents reading the gcc 2.7.2 passes directly explained them one by one — which pass emits
the odd instruction, why, and what C-level change moves it. The map could have been built in Phase 6, the day the
compiler was pinned. **Read the compiler's source before the first "unsteerable" verdict** (accelerators A4;
[`docs/retrospective.md`](../retrospective.md) §4 item 2).

## The codegen map

[`docs/gcc-2.7.2-map/`](../gcc-2.7.2-map/) is organised by pass group — scheduling, register allocation and reload, the
loop optimizer, common-subexpression elimination and expression generation — and each file is a catalogue of
*residual pattern → mechanism in the source → byte-proven C lever*, with the experiment that proved it. The cookbook's
§31 carries the **triage table**: read the *tell* in the diff (a temporary in a spill slot = a reload artifact; "every
small edit moves 20+ instructions" = a pressure lock, hand it to the permuter; a load stuck below a `x = 0` store while
offset loads float = the aliasing flag; a phantom seventh callee-saved register = cross-call value caching), look up
the class's lever, apply, gate. This is the artifact that lets a mid-tier agent — or a local model — apply
compiler-internal levers without reading 80,000 lines of source.

Whole classes long "confirmed unsteerable" fell to it: hoist-vs-rematerialize across calls, store-vs-load ordering, the
delay-slot filler's choice, the spill-slot order (which is the *declaration* order, not first-assignment order).

**The source-version trap.** The "gcc 2.7.2" tree in community circulation is gcc **2.8.1** — a behavioural difference
(a biv-elimination path disabled in 2.8.1 is live in the real 2.7.2 `cc1`) and a line-number drift large enough to land
inside a different function. The map's citations were audited line by line against the vanilla 2.7.2 source by parallel
agents, each refutation then challenged by an independent agent: 119 confirmed, 40 line-drift, 7 refuted of 21 raised.
Know which source you are reading; stage the vanilla one.

## Dumps, not guesses

The compiler will tell you what it did. BFM's instruments:

- **RTL dumps per pass** (`-da`) from the *real translation unit*, not a standalone compile — the standalone compile is
  not faithful on the executable's units ([`tools/cc1_dumps_tu.sh`](../../tools/cc1_dumps_tu.sh)); the loop dump (`-dL`)
  for the loop optimizer's decisions.
- **The allocation table** ([`tools/alloc_table.py`](../../tools/alloc_table.py)): the global allocator's *order* —
  priorities and hard registers per pseudo, read from the dumps. **Read the allocation ORDER before any register lever
  (R73).** The callee-saved bank is the allocator's priority order; every `register … __asm__` pin the last four
  functions' drafts carried came off byte-identical once the source *shape* was right. Pins looked like levers because
  they moved the diff; they were symptoms.
- **A ghost census** of stack slots and frame lines from the dumps, for the "phantom slot" class.

## Reproducers before probes

**Build the one-second reproducer battery for a mechanism before probing the 500-instruction function** (R73). Two of
BFM's last functions carried formal proofs of unmatchability, each written as a *producer census*: every way the
compiler could emit the odd byte, refuted on the bytes one by one. Both proofs were right about the mechanism and wrong
about the list — each was one producer short. Eighteen five-line reproducers found the first missing producer (a
bookkeeping gap in the combine pass's self-update) in minutes after two sessions of real-function probes; an
eight-variant reproducer sweep found the second (the loop optimizer's user-variable rule with the CSE pass's
later-mention canonicalization) after forty real-function variants. The last two functions then matched with no tricks
at all.

Hence **R69 — a residual gets a producer census from the compiler source before any spelling sweep, and "PROVED" means
every producer on a NAMED list was refuted on the bytes.** A verdict says what it was proved against.

## A wall verdict names the pass and quotes the dump line

**R65** — a wall verdict must be pass-attributed with a dump line: exonerate the instrument (R40), then name the compiler
pass, quoting the dump line that shows it. Six of the seven late wall citations named the wrong pass; each crack came
from one dump line. Before that, ask the cheaper question: **whose object is this?** Twelve "compiler walls" in the
executable were the vendor's controller library — the exact February-1998 archive was on the internet and linked
byte-identical. Provenance → archive → link → compiler, in that order.

## When there is no source

The method survives: build the catalogue from **systematic probes** — small functions that isolate one construct,
compiled and diffed against the target's idioms — and from sibling projects on the same compiler family. The reproducer
battery is the same instrument either way; the compiler's own dumps (if any) or its emitted patterns are the evidence.
What does not survive is the *content*: the catalogue is per-compiler, and a new target starts it empty.

## The economics of reading

A frontier-class agent reading four files of the compiler's source produced the map in one phase for what a single
hand-cracked giant used to cost (375–475k tokens per giant before the map). After the map, giants of 400–770
instructions matched across all overlays, and the last twenty-one functions of the project were mostly one dump line
each. The reading is a "do it up front" investment: it pays on every crack that follows.
