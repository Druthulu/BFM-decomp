# The retrospective — what we believed, what failed and why it looked right, what it cost, what we would do sooner

> **What this is.** The analytical companion to [`docs/story.md`](story.md), written at the public flip (Phase 33) for
> the next project — ours or anyone's. It is assembled from three records the project kept *as it happened*, never from
> memory: the decision log's hindsight entries (`docs/decision-log.md`, cited by dated heading and line), the two
> PhaseEnds that carry a "What we believed, what failed, and what we would do sooner" section (`PhaseEnd_Phase31.md`,
> `PhaseEnd_Phase32.md`), and the Deviations table of every PhaseEnd (237 rows across 32 phases — what was planned
> against what happened). `tools/mine_hindsight.py` gathers all three with `file:line` anchors; nothing here is
> backfilled into the log (R31). Two earlier syntheses are folded in by reference rather than rewritten: the July
> hindsight study (the optimal ORDER for an AI-driven matching decompilation, with its seven meta-principles — written
> at 78%, superseded by the how-to chapters and archived as `docs/sunset/hindsight-study.md` at the Phase-33.5
> consolidation) and [`docs/generic-decomp-package.md`](generic-decomp-package.md) (what the next project should
> inherit on day one). Every cost carries its denominator (R41).

## 1. What we believed, turn by turn — and what was actually true

| When | What we believed | What was true | Record |
|---|---|---|---|
| June (the brief) | A recompilation first would force the memory map into the open and bootstrap the decomp | A matching decomp needs no recompiler; recomp output feeds no matching work. Decided before the first commit | `docs/history/claude-bfm-starting-point.md` (banner), `PROJECT_CONTEXT.md` "Key Decisions" |
| Phase 5 | The link would be a fight; a 2.35 binutils downgrade might be needed | The link was clean; binutils 2.42 was byte-clean; the only fights were 15 leading-digit symbol names | `PhaseEnd_Phase5.md` Deviations |
| Phase 7 | ~350 PsyQ SDK functions would have to be hand-decompiled | The real Sony objects link byte-identical; hand-decompiling library code was never necessary | `PhaseEnd_Phase7.md` Deviations ("Library code") |
| Phase 12 | The resident engine holds a bytecode script VM to match | There is no VM — the "script VM" is compiled-MIPS dispatch tables; a written determination replaced a phase of work | `PhaseEnd_Phase12.md` Deviations |
| Phases 16–17 | The remaining engine core was blocked by loose typing and missing signatures | The wall was the compiler's own code generation; types and signatures were a red herring | `PhaseEnd_Phase16.md`, `PhaseEnd_Phase17.md` |
| Phases 18–22 | Residuals that resisted every source rewrite were "unsteerable" | Reading the gcc 2.7.2 source explained them pass by pass (the codegen map); "unsteerable" meant "not yet read" | `PhaseEnd_Phase23.md`, `docs/gcc-2.7.2-map/` |
| Phase 25 | A "mechanical" family sweep would remap whole families for free | The sweep had a hard ceiling at translation-unit type collisions; the mechanical tier was a third over-counted by its probe | `decision-log.md:58`, `:167` ("the mechanical tier was ⅓ probe-over-counted") |
| Phase 25 | The GIANT def-side wall was a matching wall | 71% of it was tool-shaped: a declaration conflict hidden behind "0 banked" | `decision-log.md:102`, `:134` |
| Phase 26 | The endgame plan's numbers described the remaining work | "The audit found the endgame plan was majority-fiction": broken scanners had been measuring the frontier | `decision-log.md:780` (2026-07-14, A2) |
| Phases 26–28 | The "~3% swing number" was a wall class | It was an `-O0` compile-flag artifact of the tooling | `decision-log.md:1241` (2026-07-16, Phase 29 Task 1) |
| Phase 29 | The waves were limited by idioms the drafters lacked | The bottleneck was INTEGRATION — banking a byte-correct draft past declarations, placement and symbol spellings (~92% of drafts byte-correct, ~27% banked at one measurement) | `decision-log.md:1932` (2026-07-24, SESSION-15); `PhaseEnd_Phase31.md` "Cost" |
| Phase 30 | The disc had been fully counted | It held 73 more code-bearing payloads; the denominator grew 140 → 213 while the percentage still rose | `decision-log.md:2151`, `:2208`, `:2243`; `PhaseEnd_Phase30.md` |
| Phase 31 | A band of the main executable was a compiler wall | It was Sony's libpad 4.2.1; the exact February-1998 archive was on the internet and linked in — twelve "walls" at once | `decision-log.md:3067` (S78); `PhaseEnd_Phase31.md` |
| Phase 31 | The permuter had exhausted the pinned near-misses | It had never run on one | `PhaseEnd_Phase31.md` "What we believed" |
| Phase 32 | Two functions were PROVED unmatchable by producer censuses | Each census was one producer short; five-line reproducers found the missing behaviours in minutes | `decision-log.md:3404`, `:3424` (S85); cookbook §501-Q/§501-R |
| Phase 33 | Main's game-code denominator was settled | Ghidra's boundaries under-counted it by 3,616 instructions; the build-derived sig replaced it | `decision-log.md:3451` (P33 S86) |
| Phase 33 | The history rewrite was a mechanical filter run | Two defects only a rehearsal could show: an empty blob in the strip list silently undid every "file emptied" change in history, and a byte-identical commit keeps its hash | `phase-ends/CURRENT_PHASE.md` (P33 C1), `docs/public-flip-runbook.md` §5 |

The pattern is not subtle. **Almost every wall the project recorded was one of its own instruments** — a scanner that
skipped, a gate that compared the wrong hash, a probe that sized what it should only have filtered, a census one
producer short, a boundary from the wrong tool. The Phase-31 close says it in one line: roughly a third of that phase's
"compiler walls" were tooling. Phase 26 made it a doctrine (R35: fix the instrument before trusting its measurement;
R32: assert your coverage; R34: a second, disagreeing oracle) and Phase 32 sharpened it to R65: a wall verdict must name
the compiler pass and quote the dump line.

## 2. What failed, and why it looked right at the time

- **The silent skip.** A corpus scanner that could not answer returned an empty set, and an empty set read as "nothing
  left" — the tool reported a 100%-complete decomp from a swallowed error (`tools/progress.py`, the comment block in
  `weighted_metrics`). It looked right because green is what success looks like. Seven of these were found in Phase 26
  (`decision-log.md:608`, "the silent-skip class"). Fix: R32/R43 — a tool refuses rather than guesses, and every scanner
  compares what it found against an over-approximating candidate set.
- **The wrong-hash gate.** For a month the shared byte gate compared one binary against *another binary's* hash
  (`decision-log.md:1499`). It looked right because the gate was green — for the wrong reason. Fix: per-binary contracts
  (`config/check.*.sha`), R50 periodic whole-fleet verification, R56 (a gate verdict measures the draft only while the
  baseline is green).
- **The proof that was a census.** "PROVED unmatchable" meant "every producer on my list is refuted on the bytes"; the
  list was the assumption (`decision-log.md:3424`). It looked right because each refutation was real. Fix: R69 — a
  verdict names the list it was proved against; R73 — build the one-second reproducer battery before probing the real
  function.
- **The summary that hid a compile error.** "0 banked" across a whole class read as an intractable wall; the raw
  compiler error on ONE placed candidate showed a declaration conflict (`decision-log.md:124`). Fix: R37 — probe before
  costing; ground every estimate on one instance.
- **The register pins.** Every pin on the last four functions came off byte-identical once the source *shape* was right
  (`PhaseEnd_Phase32.md` "What we believed"). Pins looked like levers because they moved the diff; they were symptoms.
  Fix: R73 — read the allocation order before any register lever; remove every pin after a structural change.
- **The atlas score.** A 0.55 "weak cousin" was the exact same-shape sibling; the whole crack was one grep and one port
  after ~1M tokens of dial work (`decision-log.md:3399`). A similarity score looked like a shape oracle. Fix: R72 — a
  hand pass opens with a grep for the idiom's literal constants.
- **The fresh session that nearly closed an open phase.** A compressed hand-off was misread as "done"
  (`decision-log.md:51`). It looked right because the summary said so. Fix: the replayable 🛑 checkpoint (R64) that
  distinguishes *not this session* from *not this phase*, and a plan of record that outlives any hand-off.
- **The rewrite that would have corrupted history.** `--strip-blobs-with-ids` with the empty blob's id in the list
  dropped every "file emptied" change across 4,000 commits; the pairwise proof caught it, the trial caught the pairwise
  proof's own gap (P33 C1). It looked right because the filter exited 0 and the purged paths were gone. Fix: rehearse an
  irreversible operation on a scratch copy and verify pair by pair, with positive assertions (no purge path survives,
  the pruned set equals the derived set), not only absences.

## 3. What it cost — with denominators

| Item | Cost | Of |
|---|---|---|
| Duration | 12 weeks (2026-06-10 → 09-07), ≈87 sessions, ≈4,040 commits | the whole project |
| Re-drafting functions that were already byte-correct and failed on plumbing | the dominant token spend of the campaign phases; ≈92% of drafts byte-correct, ≈27% banked at one measurement | `PhaseEnd_Phase31.md` "Cost"; the recovery tooling of P31 closed the gap |
| Re-drafting functions whose banked twin was two words away | ≈250k tokens before `tools/twin_rescan.py` existed | `PhaseEnd_Phase31.md` (§397) |
| The last four functions of Phase 32 | a 655k-token Fable agent on one row, 3,360-variant sweeps, ≈100 hand variants, ≈1M tokens of dial work on a row whose answer was a grep | `PhaseEnd_Phase32.md` "Cost"; `decision-log.md:3399` |
| One wave of 31 drafters (P32 T3) | ≈16 Opus + 4 Sonnet + 11 Haiku agents, 30–70 min each on Opus, for 20 MATCH (2,111 instructions) + 9 exact-length seeds; ≈1 hour of a Max session to recover from the coordinator's death | `decision-log.md:3291` (S82) |
| Sessions lost to instrument diagnosis | "the cost was the diagnosis" — three zero-token banks and five onboardings whose only expense was finding which tool lied | `decision-log.md:3245` (S81) |
| The private-era convenience (R1) | a full-history rewrite: ≈2 sessions of tooling, two rehearsals, 311 s of filter time, and a Support ticket | `decision-log.md:3447`; `docs/public-flip-runbook.md` |
| Stale scratch | 12 GB of forgotten gate worktrees, each a full old-history checkout, discovered only when they pinned the old lineage against the gc | `phase-ends/CURRENT_PHASE.md` (P33 C9) |
| Phase length vs. plan | P31: 30 sessions against "10–18" — the ceiling kept moving because every instrument repair re-opened a class that had been called a wall | `PhaseEnd_Phase31.md` Deviations |

What did *not* cost much: the mechanical banks. Once a tool existed for a class — twins, families, siblings, `-O0`
carves, propagation, stranded boundaries — its members cost ≈0 tokens each (`docs/generic-decomp-package.md`, "The
claim"). The economics of the project are the ratio between those two rows.

## 4. What we would do sooner

*In the order the July hindsight study first argued for and `docs/how-to-ai-decomp/03-bootstrap-order.md` now carries — byte-match baseline → pin the compiler by evidence → honest corpus
census with self-asserting tools → propagation and reconcile tooling → the codegen map and the permuter → then crack,
leverage-first — and with the specific lessons this project paid for:*

1. **Keep ROM-derived bytes out of git from the first commit, even while private.** R1's relaxation bought a few weeks
   of convenience and cost a full-history rewrite, a rehearsal harness and a Support ticket (`decision-log.md:3447`).
   Decide the public/private boundary on day one; cite commits by date and subject in long-lived documents, never by
   hash alone.
2. **Read the compiler's source before the first "unsteerable" verdict.** Phase 23's breakthrough was available in
   Phase 16 — the source was public all along (`PhaseEnd_Phase23.md`; `docs/gcc-2.7.2-map/`).
3. **Build the integration layer before the drafting layer.** Banking, not cracking, was the bottleneck from the day
   cracking became systematic (`decision-log.md:1932`); the reconcile/propagation/declaration tools of P19–P31 should
   have preceded the waves.
4. **Assert coverage in every scanner from its first version, and control every refusal against the population that
   already passed** (R32, R39). Seven silent-skip defects and several "walls" were nothing but tools that could not
   answer and said "none" (`decision-log.md:608`, `:647`).
5. **Ask "whose object is this?" before "which pass emitted this?"** Twelve walls were Sony's library; provenance →
   archive → link → compiler is the order (`PhaseEnd_Phase31.md` "Doctrine changes"; cookbook §487–§490).
6. **Build the one-second reproducer battery for a mechanism before probing the 500-instruction function**, and read
   the register allocation ORDER before any register lever (R73; `decision-log.md:3424`).
7. **Rehearse anything irreversible on a scratch copy, and make the proof assert presences, not only absences** (P33 C1:
   two rehearsals, two defects that a single run would have shipped).
8. **Write the checkpoint to be replayed, not summarised** (R64). The number-one failure mode of a long multi-session AI
   project is a fresh session misreading a compressed hand-off (`decision-log.md:51`); the 🛑 block that carries paths,
   commands, hashes and the exact next step is what made the last thirty sessions resume without a question.
9. **Measure the steady state, not the launch; report every lane, not the loud one; quote the denominator** (R41,
   the `measure-the-steady-state` and `report-every-lane` lessons of the autonomous-lane phase). Half the false ceilings
   of P31 were launch bursts read as limits.
10. **Give every scanner and every gate a known-true case to check against before reading its output** — five of one
    session's biggest "findings" were artifacts of the instrument that produced them, each caught only that way
    (`decision-log.md:2938`, S75).

## 5. What stayed genuinely hard

Not everything was tooling. The July hindsight study's §5 (archived as `docs/sunset/hindsight-study.md`) named the
classes that remain hard for any matching decompilation of this compiler, and this project's last phases confirm them:

- **The novel unique tail** — functions with no duplicate, no structural sibling and a scaffold too far from byte-exact
  for the permuter. They need reasoning; they were the last and most expensive fraction (the 21 of Phase 32).
- **Compiler-internal residuals** — scheduling ties, register-allocation drift, the delay-slot knife-edges. They were
  steerable in the end (every pin came off), but only by understanding the pass (§501-Q's combine bookkeeping gap,
  §501-R's user-variable rule) — knowledge that had to be won from the source, once, and written down.
- **Build-integration walls** that masquerade as compiler walls — jump-table carves, mixed optimization levels,
  scattered `.bss` in Sony's objects (cookbook §489). They are ours to fix, and they never announce themselves.
- **The human gate.** ~99% of the work was the agent's, but every wrong *direction* was caught at a plan or milestone
  gate by a person — the re-charter of P31, the "everything short of Sony's objects and the original hand-asm must be C"
  directive of P32, the in-place-flip decision of P33. Automation filled between the gates; it did not replace them
  (the July hindsight study's principle 7; the chapters carry it as governance — `docs/how-to-ai-decomp/01-governance.md`).

## 6. For the wiki, in one paragraph

Pin the compiler by evidence and make a whole-binary byte gate the only judge; treat every tool as a suspect before
every function; build the things that compound (dedup, propagation, the codegen map, the reproducer battery) before the
things that pay once; keep the perishable *why* in a decision log written during the session that learned it; write
hand-offs to be replayed; and keep the game's bytes out of the repository from the first commit. The rest — the 218
binaries, the 363,214 functions, the 4,000 commits — follows from those, at a cost that is mostly the diagnosis of
one's own instruments.
