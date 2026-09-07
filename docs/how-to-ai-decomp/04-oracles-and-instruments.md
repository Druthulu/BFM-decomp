# 04 — Oracles and instruments: a true number about a narrower world

The most damaging defect class in an automated decomp is not a crash. It is **a tool that exits zero reporting a TRUE
number about a scope narrower than the reader believes** — a step that quietly skips, or quietly accepts, work it
cannot handle, so the failure looks ordinary and gets attributed to the worker or the compiler. In one late session of
BFM, ten-plus blockers were counted and every one had that shape. Roughly a third of one phase's recorded "compiler
walls" were the project's own instruments; the retrospective's belief-vs-truth table has a dozen rows that say the same
thing. **Almost every wall was an instrument.** This chapter is the discipline that came out of it.

## The oracle ladder, and what each rung cannot see

| Oracle | Proves | Blind to |
|---|---|---|
| a standalone per-function compile with relocations masked | the instruction **shape** matches | symbol identity (masked), the declarations of the real translation unit, the file's optimization level |
| the real-TU probe (the whole split file with other functions neutralized) | the body matches in its real declaration context | link-time symbol identity |
| the symbol-identity check | the draft names the symbols the target actually references | whether the body is right |
| **the whole-binary rebuild + hash** | **everything** | nothing about *this* draft — but everything about coverage, the wrong contract, a stale output file, an incremental linker script, a body that is pasted assembly ([chapter 02](02-byte-gate.md)) |

**Design rule:** every oracle states what it cannot see, *in its own output*. An oracle that answers confidently outside
its competence is worse than no oracle: BFM had a clean local MATCH that could not link (the mask hid a nonexistent
symbol) and a local mismatch on every instruction because the probe compiled at the wrong optimization level, and
nothing in either diff said why.

## The four instances, and the rules they produced

1. Functions compiled at a different optimization level than their object was drawn as work **79 times across 19
   waves**. None could ever have banked. Every failure looked like a model failure. → **R45 draw-time bankability:**
   never hand out work the pipeline cannot bank; filter at the source and *count what you filtered* in a visible census.
2. The batch gater accepted a binary class it structurally could not gate: **105 cards, 0 banked**, while the same wave's
   other 115 cards banked 94. The whole wave read as a drafting collapse. → **R43 refuse loudly, never mishandle:** a tool
   that cannot process an input says so and names the tool that can.
3. A tool reported "12 banked of 12" because it compared function *names* against a set keyed by *address* — always
   true, therefore always banked. → **R41 assert the denominator:** every rate ships with what it is a fraction of; **R33**
   a metric derived from a proven invariant beats one that re-parses the world.
4. A draw refused the entire wave whenever any binary was mid-gate and silently fell back to pre-drawn waves — every new
   draw-time feature stopped reaching the fleet while the logs showed healthy activity. → **scope a refusal to what is
   actually unsafe:** a blanket guard that fires constantly gets routed around, and the workaround becomes the silent
   failure.

## The rules, as a working set

- **R32 — Assert your coverage.** A scanner compares what it found against an over-approximating candidate set and
  fails on the gap. A silent skip is a defect, and a loud failure nobody counts is exactly as invisible. Seven silent-skip
  defects were found the first time this was applied.
- **R34 — A second, DISAGREEING oracle, not a better assertion,** when an oracle is structurally blind to an error
  class. The byte gate is a null oracle for coverage; BFM keeps two independent function-boundary derivations
  reconciled on a schedule, and both must read zero phantoms and zero truncations.
- **R35 — Fix the instrument before trusting the measurement.** A number from a broken tool and the same number from a
  fixed tool are opposite facts (the 0%-vs-89% families doctrine). Tool integrity is a *precondition* of a measurement.
- **R37 — Probe before costing.** Ground every estimate on ONE instance; diff the artifact to prove an edit actually
  ran before judging the lever it carried. A "0 banked across a class" read as a wall; the raw compiler error on one
  placed candidate showed a declaration conflict.
- **R38 — Read the recorded failure verdicts before designing an experiment.** The answer is frequently already on disk;
  a session's first hours once went to a question the tools had answered the night before.
- **R39 — Negative-control every new refusal-check against the already-succeeded population**; zero false positives
  before it ships. A pre-check's control over 205 banked drafts caught two bugs in the check itself — either would
  have silently discarded good work forever.
- **R40 — Exonerate the instrument before attributing a failure to its subject** (truncation, fences, rate limits,
  tool faults first). Seven false model verdicts in one session.
- **R49 — A soft error inside a success envelope is still that error** (an HTTP 200 carrying code 429; a nonzero
  return code read as "no binary"; an import that printed `failed=2` under a "proof passed").
- **R55 — A lane that runs unattended must leave evidence** (an empty log + no process = never started; a silent
  30-minute gate hid a 31→67-minute regression).
- **R57 — An instrument's own write path is part of the instrument.** A repair tool whose writer corrupted what it
  measured reported the corruption as the subject's failure; and on the day this page was written, the probe that
  guards the published repository against the purged history was found to *fetch that history back into the
  repository* on every run — 5.9 GB of it — because a successful `git fetch <old-sha>` imports the commit's whole
  closure. It now fetches into a throwaway scratch repo and ends with a self-check.
- **R61 — Distinguish "judged and failed" from "not judged"**, and a judging tool must model what the gate does to the
  draft; a loop that reports "unchanged" for N cycles must prove it iterated (the permuter had never run on a class).
- **R63 — A permuter or waypoint score is not a closeness until its diff is read.** A masked "1" had replaced an
  `addiu` with a store.
- **A verdict names its instrument.** Record *which tool* produced a negative verdict, and never re-implement a gate you
  have: eleven "proven gate-rejects" were a missing data carve, judged by a one-off script that skipped the real
  gate's pre-check.
- **Check against a known-true case.** Test every scan, join, census and verdict on one case whose answer you already
  know before reporting it; five of one session's biggest "findings" were artifacts of the instrument, each caught only
  this way.
- **Measure the steady state, not the launch; report every lane, not the loud one.** Launch bursts and startup memory
  both faked hard limits; a lane banking far below the rest meant a harness fault three times out of three.

## The differential-oracle harness — build it at 0%

What caught every one of the ten blockers above was **two independent measurements disagreeing**: the real-TU probe vs.
the whole-binary gate; the standalone probe vs. the real TU; a sweep's zero vs. a member already known; a clean rebuild
vs. an incremental one; an agent's verdict vs. its own scratch directory. The rules above existed and were correct —
and their author wrote one of them into a tool's docstring and rebuilt the exact defect it warns about in a different
file an hour later. Rules are applied by whoever writes the tool; a harness is not.

So: a standing harness that runs the same question down two independent paths on a schedule and fails loudly on
divergence. The pairs exist in any decomp from day one:

| Question | Path A | Path B |
|---|---|---|
| is it matched? | the source scanner | the built binary / the dedup registry |
| does it compile? | the standalone probe | the real translation unit |
| is the fleet green? | incremental build | from `make clean` |
| what does this scanner cover? | its own count | an over-approximating candidate set |
| did the agent produce work? | its returned verdict | its scratch directory |
| is this function bankable? | the draw filter | the toolchain-wall oracle |

It is the only accelerator that works before a single function is matched, and its value grows with every tool added,
because every new tool is a fresh chance to be confidently wrong about scope. Each diagnosis above cost 90k–290k tokens
as a one-off investigation; a nightly disagreement report is minutes of compute. BFM's own estimate: about half of a
typical late session went to harness defects wearing model-failure costumes, and that ratio probably held, invisibly,
for most of the project — **a plausible number never asks to be checked.**

**The scheduling half is not optional.** Tooling was correct when written and went stale as new idioms revealed
populations it could not see. At every session and phase close, review the tooling against the idioms learned and ask
*which scanner's denominator just got wider?* — that is what converts new knowledge into free banks
([chapter 03](03-bootstrap-order.md), [chapter 06](06-knowledge-base.md)).
