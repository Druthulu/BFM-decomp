# The portable decomp workflow — a system anyone can run on any target

**Started 2026-08-24 (P31 S59). Living document.** This is the seed of the public deliverable: the
**system**, extracted from BFM and written so it applies to any byte-exact decompilation — any
console, any compiler, any language — by someone driving it solo.

Three sibling documents already exist and this one does not replace them:
`docs/accelerators.md` (what we learned late that day one should know), `docs/decision-log.md` (why
we pivoted), `docs/automation-runbook.md` (how *this* project's lanes are driven). Those are BFM's
history. **This file is the part that transfers.**

The rule for what belongs here: *if it would still be true for a PS2 game built with a different
compiler, it goes here. If it is a fact about gcc-2.7.2 or about Brave Fencer Musashi, it does not.*

---

## 0. What the system assumes

1. **A byte-exact target exists** — an original binary you must reproduce exactly.
2. **A build you control** that can, in principle, reproduce it (right compiler, right flags, right
   linker order). Establishing that triple is prerequisite work, not part of this system.
3. **A splitter/disassembler** that emits per-function assembly and a config describing the layout
   (splat, or an equivalent). The system needs to address one function at a time.
4. **Cheap parallel model capacity.** Not necessarily frontier models — see §7.

Everything below is about what you do *after* those four exist, which is where the years go.

---

## 1. The one non-negotiable: the byte gate

**A function is done when the whole binary still hashes correctly with that function compiled from
source. Nothing else counts.** Not "looks equivalent", not a passing test, not a local diff of zero.

Every other signal in the system is a *filter* feeding this gate, and each one is blind to something:

| oracle | what it proves | what it is blind to |
|---|---|---|
| local per-function compile + masked diff | instruction SHAPE matches | symbol identity (relocations are masked), declarations in the real TU, optimization level |
| symbol-identity check | the draft names the symbols the target actually references | whether the body is right |
| **whole-binary rebuild + hash** | **everything** | nothing — this is the arbiter |

Two failure modes this table exists to prevent, both observed:

* **A clean local MATCH that cannot link**, because the draft named a symbol that does not exist.
  The local oracle masked the relocation, so it scored zero diff.
* **A local mismatch on every instruction** because the local oracle compiled at the wrong
  optimization level. The feedback could never converge, and nothing in the diff said why.

**Design rule:** every oracle must state what it cannot see, in its own output. An oracle that
answers confidently outside its competence is worse than no oracle.

---

## 2. Lanes: separate what has different clocks

The naive design is one loop: pick a function, draft it, verify it, repeat. It fails at scale because
the steps have *different natural rates and different failure modes*. Split them into independent,
restartable lanes:

| lane | rate | may it stop? |
|---|---|---|
| **drafter** | bounded by model capacity and by how many work items you can produce | **never stop it to ship a change** — it is usually the clock-limited resource |
| **gater** | bounded by build time | freely restartable; nothing is lost but a pause |
| **maintenance** | opportunistic, zero-cost mechanical work (see §5) | freely |
| **watchdog** | fixed short interval | freely |
| **distiller** | slow, human-paced | freely |
| **second population** | its own clock (see §6) | freely |

**The single most expensive mistake we made in this area:** stopping the drafting lane to ship a code
change. It cost 139 of 162 idle minutes in one session. Ship changes at a wave boundary, or to a lane
that is not the clock-limited one.

**An implementation trap worth stating because it is invisible:** a shell parses a `while … done`
body *in full* before running it, so editing the lane script does not change the running loop, and
restarting only the inner process re-runs the *old* arguments. Know, for your runtime, which of
{code, arguments, per-invocation defaults} takes effect when. Verify from the process, not the file.

---

## 3. The card: fuel, not a ticket

The unit of work handed to a model is not "function X, go". It is a **card**: everything the project
already knows that bears on this function, assembled deterministically at zero token cost.

What earned its place on ours, each measured:

* the target's disassembly path and its destination source file;
* **an already-matched sibling** with the same skeleton, when one exists (this single field moved a
  wave from 0 banked to 51 banked);
* **what the destination file already declares** — a drafter that invents a signature the file
  contradicts produces a body that compiles alone and not in place;
* **the project-wide declaration consensus** for each callee, because the assembly frequently cannot
  tell you a function's arity and the corpus can;
* **the lever**: which known pattern this function is believed to exhibit — *plus what that lever
  means and where to read about it.*

**The lever lesson generalizes hard.** We labelled cards with lever names that appeared **nowhere in
our own knowledge base**. 108 model transcripts show the agent dutifully searching for the exact
word on its card and finding nothing. A label a worker cannot look up is not fuel; it is a dead end
that costs a search and buys nothing. **If you put a name on a card, that name must resolve in your
knowledge base by the words on the card.**

---

## 4. Refuse work the pipeline cannot bank

The most damaging bug class in this system is not a crash. It is **a true number about a narrower
scope than the reader assumes** — a step that quietly skips, or quietly accepts, work it cannot
handle, so the failure looks ordinary and gets attributed to the worker.

Four instances, all real, all costly:

1. Functions compiled at a different optimization level than their object was drawn as cards **79
   times across 19 waves**. None could ever have banked. Every failure looked like a model failure.
2. The batch gater accepted a binary class it structurally could not gate: **105 cards, 0 banked**,
   while the same wave's other 115 cards banked 94. The whole wave read as a drafting collapse.
3. A tool reported "12 banked of 12" because it compared function *names* against a set keyed by
   *address* — always true, therefore always "banked".
4. A draw refused **the entire wave** whenever any binary was mid-gate, silently falling back to
   pre-drawn waves — so every new draw-time feature stopped reaching the fleet while the logs showed
   healthy activity.

**The rules that fall out of these, stated portably:**

* **Draw-time bankability.** Never hand out work the pipeline cannot bank. Filter at the source, and
  *count what you filtered* in a visible census.
* **Refuse loudly, never mishandle.** A tool that cannot process an input must say so and name the
  tool that can — silently producing a plausible failure is worse than skipping.
* **Assert the denominator.** Every rate ships with what it is a fraction of. A metric derived from
  an invariant beats one that re-parses the world.
* **Scope a refusal to what is actually unsafe.** A blanket guard that fires constantly gets routed
  around, and the workaround becomes the silent failure.

---

## 5. Free work before paid work

Every project has mechanical work that costs no model tokens: the same function appearing in several
binaries, a proven body remappable to a sibling, a deterministic transformation of an already-banked
result. **Run it in its own lane, opportunistically, whenever the paid lane is idle.**

Corollary for the card draw: if two work items are the *same* item, draft one and derive the other.
Ours collapses same-skeleton members to one card and defers the siblings to a free remap — drafting
both pays twice for something a script gives away.

---

## 6. Populations have different clocks — give each its own lane

Not all of the target is the same kind of work. Ours splits into: many small independent overlay
binaries (fast gate, cheap), and one large executable (slow gate, must rebuild wholly, bisects on
failure).

The large one had been excluded from the main loop for a good reason — its gate is expensive and
stalled everything behind it — and the consequence was that **it got no attention at all**, while
the fast loop ran at a quarter of the available model capacity because it could not produce work
items fast enough. Two populations, one idle half of a rate limit.

**Rule: an excluded population needs its own lane, not an exclusion.** Give it a cadence matched to
its own gate cost, and let the two lanes share the capacity.

Batching is what makes an expensive gate affordable: one rebuild verifies N drafts. Two conditions
make batching work — a *pre-filter* strong enough that most of the batch is right, and a *bisect*
when it is not. And measure the gate before you fear it: ours was believed to cost 40-60 minutes and
actually costs ~15 seconds when the batch is clean. The stalls were bisects, not rebuilds.

---

## 7. Model routing and budgets

* **Route by difficulty, and measure the cliff.** Ours: cheapest tier ≤30 instructions, mid tier to
  ~120, strongest above. Measured, not assumed — the cheap tier's success drops from 86% to 20%
  across that range, and the earlier hand-waved boundary was wrong by a factor of two.
* **Budget per lane, not per project.** A turn/cost cap that fits a small function starves a large
  one: 98 of 270 attempts on our hardest population ended *at* the cap rather than at a wall.
* **Reserve the strongest model for genuinely new walls** — an unsolved tooling problem, an
  adversarial review of a design, a residual no documented lever reaches. Reviewing a pile of
  artifacts against an existing knowledge base is mid-tier work, not frontier work.
* **Cheap tiers are honest.** Across 100 workers, 63 claimed matches were 63 real matches. Treat
  their verdicts as a reliable *filter* and never as the gate.

---

## 8. The flywheel: harvest, distil, and the one-wave lag

Workers discover things. If discoveries do not reach the *next* workers, you re-buy the same lesson
forever.

```
gate accepts a function → harvest the worker's note (only for BYTE-PROVEN results)
   → distil into the knowledge base (human + a mid-tier reviewer)
      → the next workers grep it on their next card
```

Four things we learned the hard way:

1. **Harvest only from proven results.** A note attached to an unverified draft is a lesson about a
   function you did not reproduce.
2. **Extraction is not distillation.** Ours harvested automatically and correctly for weeks while the
   ore piled up unread; only what reaches the knowledge base changes behaviour.
3. **Expect ~85% of harvested claims to be already covered.** That is not waste — a fast correct
   "already known, see §N" is most of the value, and it stops the base bloating with duplicates.
4. **One in three credited levers is inert.** Workers stack edits; when the match closes, the
   last-added edit gets the credit, and byte-inert riders *survive into the accepted result precisely
   because they are inert*, which then reads as proof. **Before a lever enters the knowledge base,
   strip it from the accepted body and recompile.** Measured twice: 4 of 8, then 6 of 19.

**Accept the one-wave lag.** Wave N's lessons land while wave N+1 is already in flight, so wave N+2
is the first that can use them. The alternative — pausing production to think — costs more than the
lag does.

---

## 9. The economics, as measured

Numbers from BFM, stated so another project can calibrate rather than copy:

| quantity | measured |
|---|---|
| drafts → banked, fleet-wide | **34%** (8,885 drafts → 3,027 banked over 37 waves) |
| bank rate by function size | ~57% under 50 instructions · ~30% at 50-80 · ~22% at 80-120 · ~3% at 120-200 · ~6% above |
| bank rate by population | the "hard" population banks 27-40% at small sizes — **the gap to the easy population was almost entirely SIZE MIX, not difficulty** |
| provider rate ceiling | rejections stay ~0-3.5% up to ~95 req/min; 6.6-12.7% at 195-227; retries absorb it |
| per-worker request rate | 0.3-0.8 req/min, so ~350-400 concurrent workers sits at the knee |
| throughput | ~2,000 functions banked per day, unattended, at a marginal model cost of roughly zero on a free tier |

**The single most useful economic fact:** *card supply*, not model capacity, was the binding
constraint for most of the campaign. We repeatedly reached for more workers when the answer was more
work items — and once a second population got its own lane, capacity stopped being the question.

---

## 10. What transfers, and what does not

**Transfers:** everything above — the gate discipline, the oracle ladder, lanes, cards, draw-time
refusal, free-before-paid, per-population clocks, model routing, the flywheel and its inert-rider
law, and the economics *shape* (not the constants).

**Does not transfer:** the compiler idioms themselves. Our knowledge base is ~780 sections of
gcc-2.7.2 behaviour; another target needs its own, built the same way. **The knowledge base is
per-compiler; the machine that builds it is universal.** That is the whole thesis of this document:
a new project inherits the *system* on day one and spends its effort discovering its own compiler's
idioms rather than rediscovering how to run a decomp.

---

## 11. Bootstrapping order for a new project

1. Establish the byte-exact build triple and a whole-binary hash check. Nothing else matters until
   the hash can go green on an all-assembly build.
2. Stand up the local per-function oracle **and make it state its blind spots** (§1).
3. Build the card: destination file, existing declarations, project-wide consensus, any sibling.
4. Run a *small* manual wave. Measure bank rate by size. You now have your routing cliff (§7).
5. Add the byte gate as a lane, with a per-binary lock so gates can run in parallel.
6. Turn on harvesting from proven results only. Distil the first batch by hand — you are writing the
   seed of your knowledge base, and its *vocabulary* decides whether anyone finds it later (§3).
7. Only now scale the worker count, and watch the rejection rate bucketed over time rather than at
   launch (launch bursts fake a ceiling).
8. Give every excluded population a lane before you give the main loop more workers (§6).
