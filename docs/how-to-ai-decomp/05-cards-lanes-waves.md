# 05 — Cards, lanes, waves

## The card: fuel, not a ticket

The unit of work handed to a model is not "function X, go". It is a **card**: everything the project already knows that
bears on this function, assembled deterministically at zero token cost. What earned its place on BFM's, each measured:

- the target's disassembly path and its destination source file;
- **an already-matched sibling with the same skeleton**, when one exists — this single field moved a wave from 0
  banked to 51 banked;
- **what the destination file already declares** — a drafter that invents a signature the file contradicts produces a
  body that compiles alone and not in place;
- **the project-wide declaration consensus** for each callee — the assembly frequently cannot tell you a function's
  arity, and the corpus can;
- **the function's own past-attempt history** (journal notes from every earlier agent that touched it) — measured 38 of
  39 MATCH on the hardest frontier with it, and 4 of those 39 recovered a body that had already matched once;
- **the lever** the atlas believes applies — *plus what that lever means and where to read about it.*

**The lever lesson generalizes hard.** Cards were once labelled with lever names that appeared nowhere in the project's
own knowledge base. 108 transcripts show the agent dutifully searching for the exact word on its card and finding
nothing. A label a worker cannot look up is a dead end that costs a search and buys nothing. **If you put a name on a
card, that name must resolve in your knowledge base by the words on the card** (R44).

Two more card laws, both bought with tokens: the pack must actually be where the agent is told to read it (one
misplaced laws file silently degraded every wave's brief to "the pack alone" for weeks — two agents said so verbatim,
the rest never mentioned it); and never assert "no banked twin" on a card unless the twin scan ran on the *world*, not
on the card — an agent spent 102k tokens re-deriving a function banked verbatim at the same address in another binary.

## Lanes: separate what has different clocks

The naive design — pick, draft, verify, repeat — fails at scale because the steps have different natural rates and
different failure modes. Split them into independent, restartable lanes:

| Lane | Rate | May it stop? |
|---|---|---|
| **drafter** | bounded by model capacity and by how many work items you can produce | **never stop it to ship a change** — it is usually the clock-limited resource |
| **gater** | bounded by build time | freely restartable; nothing is lost but a pause |
| **maintenance** | opportunistic zero-cost mechanical work (twins, remaps, propagation) | freely |
| **watchdog** | a fixed short interval | freely |
| **distiller** | slow, human-paced (harvest → cookbook) | freely |
| **second population** (the expensive binary) | its own clock | freely |

The single most expensive mistake in this area: stopping the drafting lane to ship a code change — 139 of 162 idle
minutes in one session. Ship changes at a wave boundary, or to a lane that is not the clock-limited one. And an
invisible trap: a shell parses a `while … done` body in full before running it, so editing the lane script does not
change the running loop, and restarting only the inner process re-runs the *old* arguments. Verify from the process,
not the file.

**An excluded population needs its own lane, not an exclusion.** BFM's main executable was left out of the main loop
because its gate was expensive, and the consequence was that it got no attention at all while the fast loop ran at a
quarter of the available capacity for lack of work items. Give each population a cadence matched to its own gate cost
and let the lanes share the capacity ([chapter 02](02-byte-gate.md)).

## Free work before paid work

Every project has mechanical work that costs no model tokens: the same function in several binaries, a proven body
remappable to a sibling, a deterministic transformation of an already-banked result. Run it in its own lane whenever
the paid lane is idle. Corollary for the draw: if two work items are the *same* item, draft one and derive the other —
collapse same-skeleton members to one card and defer the siblings to a free remap. Rescan the twin graph after every
bank; it changes with every bank ([chapter 10](10-integration-and-propagation.md)).

## The wave, step by step

BFM's procedure is [`docs/wave-playbook.md`](../wave-playbook.md); its value is not the command list but **the pairing of
each guard with the measurement that produced it**. The spine:

0. **Preconditions.** Tree clean (a gate on a dirty tree cannot tell your edits from its own); the last full clean-fleet
   run green.
1. **Draw — and exclude what cannot bank.** The exclude list is audited before every draw and a stale one is refused:
   measured the day after one was written, 88 of its 107 entries were stale — 28 already banked, 14 never targets, and
   46 whose blocker had since been fixed: 12,750 instructions of drawable work a list would have hidden. An exclude list
   records what the *tooling* could not do at the time, not a property of the functions.
2. **Cards — and make sure the twin is on them** (the twin scan over the world; the near band, not the exact hash).
3. **Packs.** One per target plus the shared laws file, at the paths the drafting prompt reads.
4. **Validate — never hand-type a target;** the launch asserts every target is still open at draw time (payloads go
   stale). Hand the near-misses to the permuter first — it costs no tokens.
5. **Draft.** One agent per target, model by size ([chapter 08](08-models-and-budgets.md)). Streaming (refill each slot
   on completion) beats batch (a batch cannot gate until its slowest agent lands: 18 of 20 drafts idle behind 2
   stragglers). Wave size: BFM's doctrine became **6,000+ instructions per wave** after a 40-card wave drafted its
   "unknown lever" cards at 96% — "unknown" had meant "the atlas could not name a lever", not difficulty, and size was
   nearly free mass.
6. **Gate — everything in parallel.** Overlays in worktrees; the executable by a clean rebuild of the whole batch; read
   the verdicts (a "banked 1 / merged 0" is a failure and the tool now says so with exit 2).
7. **After ANY bank:** the twin sweep, then commit (R42).
8. **Harvest — before the next wave, a hard gate.** Every new idiom into the cookbook and its index; then ask of each
   idiom *is this mechanical?* — if yes, build the sweep and bank the free functions before drafting again. This is the
   project thesis, not hygiene ([chapter 06](06-knowledge-base.md)).
9. **Verify the fleet, not the binary.** A clean rebuild of everything; read the exit code.
10. **Checkpoint.** Refresh the replayable block; stale is worse than absent.

Then **recover** before re-drawing: a gate's failures are triaged (body vs. plumbing) and most plumbing rejects bank
without a new draft ([chapter 10](10-integration-and-propagation.md)).

## The one-agent-per-function shape

When the open census fits on one page, the wave machinery is the wrong shape: build packs, launch one subagent per
function with its own work directory (never keyed by bare function name — R48: one agent's tidy-up once swept eleven
sibling deliverables), and process results one at a time: a verbatim grep (`.ent`/`.word` in a "C" body = not a match)
→ the real-TU probe → the gate → commit per bank → the twin rescan. Agents outlive the session that spawned them —
their final verdicts are recoverable from the harness's subagent transcripts, and a tool harvests them; **agents write
their deliverables early** (the draft file first, the verdict last — R67), because every agent lost to a usage limit
had to be resumed, and the one that had written its draft first banked from the dead run. The coordinator can die too
("prompt too long" with 22 completions landing in a dead session); the recovery path is the transcripts, not memory.

## Budgets are part of the harness

A turn/cost cap that fits a small function starves a large one (98 of 270 attempts on the hardest population ended *at
the cap* rather than at a wall — R46). The cap on concurrent workflows is a budget, not a concurrency count, and a
harvest workflow counts against it. The owner retunes these often and unprompted; obey the latest, apply from the next
draw.
