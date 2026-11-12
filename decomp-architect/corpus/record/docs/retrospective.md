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

## 7. After 100 % — what the readability generation has taught so far (Gen3, Phases 35–43; advanced by every phase's closing work, R121)

*From `PhaseEnd_Phase35.md`, `PhaseEnd_Phase36.md` and `PhaseEnd_Phase37.md` (their "what we believed, what failed, what we would do
sooner" sections), decision log "P35", "P36 S99/S101/S104/S105", "P37 S106"; for the migration and Phase 38, the Phase 38 plan's change
lines, task summaries and logs, and git; for Phase 39, its plan's change lines and task summaries (T1–T11, T7.1); for Phase 40, its plan's change lines and task summaries (T1–T13, T15, T17–T21); for Phase 41, its plan and task summaries (T1–T10, T13); for Phase 42, its plan's change lines and task summaries (T1–T10); for Phase 43, its plan's change lines and task summaries (T1–T15). Same four questions as §1–§4, for the work that began when the bytes were done. Where the
record is thin it says so; inferences are marked.*

**What we believed, and what was true.** (P35) That sotn writes duplicate functions explicitly, so ~12,000 duplicate copies were the normal
end state — read from its tree, sotn shares stage code once by an include; the belief rested on one remembered parenthetical (→ R106).
(P36) That the pins would come off mechanically because Phase 32's last four had — the strip took 37 % of the sites and freed 20 % of the
bodies; the rest were 1,803 distinct shapes, each a reading of a compiler pass. That the permuter and a recipe sweep would discover shapes —
they replicate (134/134 on a known shape) and discover nothing (0/300). That "one agent at a time" meant an empty slot between agents — it
meant learning between landings; six of eight hours had no agent running the first night. That every generator's NO-CANDIDATE was a property
of the population — one generator was refusing three ways for two sessions, found only when an agent's close was run back through it. That
the pins were codegen — the biggest single class was a wrong DECLARATION (16,759 repaired free). (P37) That types were a comprehension lever
and struct-ification byte-neutral — the charter carried Phase 17's drafting measurement into a claim about spelling; the compiler map in the
same tree said the opposite, and a 165-body probe measured it: 91 % neutral, the rest a per-access dial. (P37 S107) That the declaration layer
could carry the mapped parameter types "in one pass" — a parameter cannot be typed while its body still adds offsets to it (pointer
arithmetic scales), so widths and arity come first and the typed signature is a per-callee unit after the sites are members. That a new base
symbol wanted a linker fragment — the binary's splat symbol file is the one curated source (R15) and already feeds the link.
(P37 close) That the lying-declaration count measured the work — it went 13,832 → 8,830 → 2,367 → 2,171 → 1,796 through instrument
repairs as much as rewrites. (Migration) That moving to a new working method was a harness change — the product's own tools read four of
the documents it retired, and 36 links pointed at them. (P38) That the milestone's counts were reachable as written — the census defined
a zero duplicate count as one name per layout (293 opaque eight-byte structs would have become one), a zero outside-canon count as moving
1,774 function-local stack frames, and a zero dead count as deleting 114 of 134 names that live types use as members. That equal layout
hashes meant one type — attributes, member-type twins and same-name members at other offsets all break it. That classes with matching
names would fold without respelling members — true only where the names were meaningful, not placeholders. (P39) That spelling every
raw cast dereference (a memory access through a pointer cast where the original wrote a struct field) as a member would take the P and X
forms to about zero apart from non-struct bases — it drew every base that has a canonical type, and about 88 % of what was left sits on
struct-map types with no canonical definition (TYPE-NOT-CANONICAL, 291,819 sites at the close): a definitions problem, not a spelling
problem. That the levers had easy removals left — the oracle judged every one of the 1,868 register pins needed, 0 removed; their floor is
now a ledger of causes, not a backlog. That a planner keyed by real names saw every lying declaration — 17 of 24 callees were
`aF<address>` aliases. (P40) That TNC — TYPE-NOT-CANONICAL, a cast on a struct type with no canonical definition — could reach 0 by
defining types — the last 6,066 types held about 7,000 sites, about one each; a band covering 95 % of the sites, with the tail under a
named cause (TYPE-BELOW-BAND), was the honest finish. That a literal zero of levers was reachable — the pilot showed it was not at any
cap; the real bar was a *wall* for each survivor, the gcc pass that makes it necessary, named with its evidence. That Phase 39 had
oracle-judged all 1,868 pins — 808 had been "left by the author" and 205 "not judged"; re-judged one by one, all were needed after all.
That the pins standing for a missing parameter were parameters — 384 were scratch registers, written before they are read. That defining
a type fixes its casts — the bodies must be re-swept and the ledger rows restamped, and the sweep itself creates new types the frozen band
cannot see. That functions at the same address in different binaries were copies — mostly they were distinct functions. (P41) That a lying count of 0 meant the declarations were honest — it compared only argument counts; return types, compared after typedefs, gave 273 lying functions over 100,266 sites. That a struct gate could assert 0 raw casts — at about 176,000 ledgered sites it was a gate that could never pass; the done-criteria never asked for it, and the per-site residue ledger already gates the casts. That changing a declared `void` to `int` is byte-neutral when the result is dropped — it can move register allocation, so some kept a cast at the call. (P42) That the twenty trampoline families needed the wrapped callee as a parameter — the callee was the same in every copy, and the one varying token was a single data symbol. That "0 left" could mean no rejected class at all — 729 classes stopped the harder batches, the owner chose one repair round and a ledger row for each survivor, and the phrase now means 0 not accounted for. That the 729 rejects were each a real conflict — they were an upper bound, some only collateral of a batch that failed for another class. That an edit to a type header touches only the files that use the type — it puts every binary into a failing batch's bisect set. That `make -n extract` is a dry run — it runs the extractor. (P43) That the names to work on would come with sources — 448 of the 500 had only the code to go on, and two were seen in the running game. That a placeholder names one function — the same `func_` address names different functions in different binaries, so a repository-wide rewrite renames the wrong ones. That the inherited names were all sourced — two rested on cheat-code lore and an outside client and were demoted to guesses. That the 37 functions flipped to `s32` in Phase 41 were the whole problem — at the phase's head 394 names over 9,009 definitions had no `return`; 38 were fixed and the rest parked. That the nine expand-hardreg-var wall tags were right — five were re-tagged.

**What failed, and why it looked right.** A session died at 91 % context with 35 minutes of state only in its transcript, after refreshing
its checkpoint five times — two bank commits inside a task had no log line (→ R101). A tool's restore path was `git checkout`, which wiped
the previous batch's uncommitted shares and returned green (→ R102). Two permuter campaigns scored against a disassembly that was not a
target — 24 wrong words from `move` versus `or` — and every candidate read 28 for a byte-identical body (→ R110). Nine burst agents shared one
scratch object and two scored another agent's function (→ R111). A ledger's "done" was by text hash, so 379 owed bodies passed as done
(→ R114). The harness's low-memory guard killed an unattended batch cycle mid-apply with 22 GB free (→ R115). And, this generation's own
lesson about instruments: the layout audit against cc1 began with 4,498 rejections of 5,295 definitions and ended at 0 — five of the causes
were the probe's own, two were the engine's — the reading order that R40 prescribes, run again. (S107) The linked-mode control read
"identical" for a spelling that differs — because a control the day before had run `make build` with a candidate in place and left its object
in `build/`, and the snapshot refresh copied it in; the fix is a refresh that refuses what it cannot reproduce. A fleet walk's process pool
forked from inside a worker thread deadlocked a batch at 0 % CPU with no message. A selftest's inflight probe used the live path and deleted
a real batch's restore snapshot. And the first audit of the legacy type header read 1,013 violations, 987 of them the audit's own — it paired
a trailing comment with the next field.
(P37 close) A judge stopped with `kill` and restored eight seconds later consumed its own snapshot and left six files with no restore —
it looked stopped; it was finishing its in-flight units. (Migration) The new launcher's PhaseEnd sort crashed on the id `3_5`, filed with
an underscore beside `33.5` and `37.5`: the migration copied the ids without normalising them, and the sort met a number and a string
only when a plan was approved. A bare `.run/` line in the new ignore file overrode the older re-includes, so per-phase evidence under
`.run/` could from then on be committed only by force. And the duty to advance story §10 and this section at every session end lived in
the old method's memory and checkpoint routine, which the migration did not carry; neither document moved between 09-12 and 09-30, and
R121 restored the duty on 09-30. (P38) The phase gate asked for counts its own census defined as impossible, found only at T5, after
the work was planned; it looked right because T2's known-true case passed — the gate failed on the starting tree with exactly the
baseline counts — but that case proved the instrument reads, not that the target is reachable. The census counted a struct's tag and its
typedef as two names, and T5 split nine pairs to satisfy the instrument before T5.1 fixed the instrument. The layout hash ignored
`packed`/`aligned`, so two definitions looked like one type; the byte gate proved packed is not natural twice, 142 and 148 of 218
binaries red, before the hash learned the attributes. Eighteen "conflicting types" rows outlived their fix because the engine writes no
row for a unit with nothing left to do, so the census over-counted from a stale ledger. The reasoning behind the gate-reading decision
was spoken, not written: the plan holds one change line and the discussion record opened that day is an empty template.
(P39) The P38 lesson — test each milestone count against its instrument on the planning tree, both directions — was written at the P38
close and not applied in the P39 plan, and the phase hit it twice: T4's "P and X raw = 0 except non-struct sites" was unreachable as the
census read it (18,526 map types, 1,650 defined), and the owner's *reading A* (a raw site may stay as residue if the ledger records its
cause, per site) replanned the gate; T7's "direct GTE statements = 0" counted the header's own macro calls, so zero meant no GTE at all, and
the critic's T7.1 ruling read the predicate as the census's docstring defines it. Each clause looked right because it described the
intended code, not what the instrument counts. A coverage check keyed on "the function has any ledger row" hid 14,296 uncovered sites
until T10 matched per site. Handoffs lost a coder's hand-back (T3) and orphaned a detached batch cycle (T5); the batch script refreshed the
wrong census directory, so the readability series refused its snapshot for a whole task without a visible error; and one commit took in
about 794,000 lines of census scratch.
(P40) Freezing the band once looked deterministic, but the census regrouped the sites a sweep had left and minted new hash-named types
the band had never seen — *drift*, 8,146 sites on 870 types, which took a task of its own. Walls judged after fewer than 30 tries were
not walls: the shallow pilot failures went 3 of 5 when retried. The struct gate went from passing to failing between the fifth task and
T17, from duplicate definitions that later edits brought in, and nobody saw it because it ran only at the gate; a conversion of assembly
to C left three empty K&R declarations the next tasks did not see for the same reason. A coder was spawned on the wrong belief that its
predecessor had died, and another ran a restamp mode nobody had asked for, undone from the ledger.
(P41) A gate whose verdict could not be green had been read as "red, as expected" for four phases, so the part of it that could catch a real fault was never read. A tool fix applied in place could not be reproduced without its untracked inputs, so the bugs were reproduced on a scratch worktree with those inputs linked in. A commit of about 3,900 paths was split in two by the argument limit, and its first half was never gated alone. New tool files were invisible to the kit corpus until git knew of them, and the layout tool dropped arrays of function pointers and comma-separated bitfields, which only a byte-for-byte comparison with gcc surfaced. The permission system refused the first stop of the Ghidra server; it was not worked around, and the owner stopped it himself. (P42) A planted miss in the test rename passed the byte gate, which is the point of the scanner but also a reminder that a green build says nothing about a stale name in a ledger. The test rename's commit had to be made inside the throwaway worktree, because the main gate checks out files and would have reverted an uncommitted rename. A parallel gate run interleaved its diagnostics, so one batch's rejects went unaccounted and the progress tool double-counted three; serialising the output by target fixed it. The writer for the shared form at first made the argument checker miss the name parameter and report 75 false lies; the cycle script committed with plain `git commit` and an old phase's message; and a lever parser failed on a string macro in the trampoline headers, which only the health suite saw. (P43) The rename scanner hung for eleven hours on one batch: one `git grep` with 96 patterns over 669 MB looks like one cheap pass and is not; chunked, with a time bound, it takes seconds. A class rename did nothing, with exit 0, for most shared classes, because their registry entries used a form the tool did not read, and shared headers were skipped as generated. A census was judged neutral by its counts while it keyed on the `func_`/`D_` spelling the renames removed. The first scan for the return fixes missed 2 of the 38, and the old probe scripts' canonicaliser reported a difference that was not there. A coder cut off by a session restart left a sheet with two false basis claims, read at first as finished.

**What it cost.** P35: three sessions (one a recovery) and ~2.5 h of gates; no model tokens beyond the coordinator and three gate-1 agents.
P36: nine sessions, 575 commits, ~200 agent draws, roughly 15–20 M agent tokens — the mechanical rungs took 37 % of the sites for ~20
CPU-hours and no tokens, the search another 6 % for ~5 CPU-hours, the agents the rest, at 1 close per agent rising to 4–7 as the TU batch and
the method file matured. P37 so far: two sessions; four reconnaissance agents (~1 M tokens), a fleet census that runs in 3.5 minutes, and an
engine of ~2,300 new lines built in one session with no agents — three clean fleet runs and two byte-gated batches on the way.
P37 in all: three sessions and 115 commits; the kill/restore race was its one real incident. The migration: one commit, then a day of
repairs inside the next phase's first task. P38: planned, worked and gated in about a day and a half (09-29 → 09-30); T5 stopped once on
the gate question and was reopened as T5.1, which took two expert attempts and ten coder runs (one red and reverted); every batch passed
the 218-binary gate before its commit. Start to end: struct definitions 7,255 → 1,650; duplicate classes 206 → 53, all listed twins;
file-scope definitions in `.c` files 4,085 → 0; variant camps 40 → 0; dead canonical names 141 → 0 (3 kept with cause); padding names
26 → 0; hidden-type declarations ~1,106 → 0; lying declarations 1,796 / 76 callees → 229 / 24 (the census's `decls.lying`, printed by the
gate as `types_floor_lying` — not the 98,648-based Phase 37 series, nor the plan's 1,537 "types floor"); levers 3,730, flat.
P39: 2026-10-01 → 10-03, nine planned tasks and four added mid-phase (T10 from the replan, T11 and T12 from the owner, T7.1 from the
critic); T3 alone took three expert attempts, two handoffs, about eight coder runs and 61 sweep batches; 218 of 218 binaries identical on
every batch. Start to end: raw casts 503,016 → 336,219 (P 409,007 → 257,470, I 60,666 → 49,831, X 13,800 → 13,790, M 19,543 → 15,128),
0 uncovered; 20,963 kept casts, all backed; lying declarations 229 / 24 callees → 11 / 3, all ledgered; levers 3,730 → 3,364, the rest
in a 2,433-row cause ledger; struct definitions 1,650, flat. The I/M recipe ladder was the cheapest-looking and lowest-yield rung, about
1,676 sites drawn against about 48,000 left.
P40: 2026-10-14 → 11-07, about 410 commits, two replans (both stops planned in advance, on 10-15 and 10-17). The head-class crack campaign
took about 21 coder-hours; the singleton pilot cost about 796,000 tokens, and the wave it priced was projected at about 14 hours and 19
million tokens with four coders at once. Each edit of the 2 MB `include/struct_types.h` fans out to 51 seconds of rebuilds, and the
clean gate grew from 5 minutes 38 seconds to about 9 minutes; a tools-health run takes 10 to 15 minutes. 218 of 218 binaries identical on
every batch. Start to end: TNC 291,819 → 0 (5,871 sites below the band); raw casts 336,219 → 176,439 (P 257,470 → 115,647, I 49,831 →
46,563, X 13,790 → 10,312, M 15,128 → 3,917), 0 uncovered; lying declarations 11 → 0; levers 3,364 → 1,853, the residue ledger 2,433 →
1,180 rows, all walled; struct definitions 1,650 → 4,762 (4,128 canonical).
P41: 2026-11-07 → 11-08, about eleven hours and 88 commits; nine coder runs in all (three for the Ghidra type tool, two for the return-type fixes), the rest done by the task experts themselves; the close was paused twice for the owner's word. Each Ghidra proof leg takes 77 to 208 seconds headless; the type tool's check runs in about 6 seconds. 218 of 218 binaries identical on every batch. Start to end: return-type lies 273 functions / 100,266 sites → 19 / 9,302, all ledgered; raw casts, levers and struct definitions unchanged (176,445 covered; 1,853, all attributed and walled; 4,762); 7,151 canonical types mirrored into Ghidra.
P42: 2026-11-08 → 11-10, about 35 hours and 111 commits; thirteen coder runs, four of them on the harder share batches; paused for a Claude Code restart, for the owner's decision on the rejects, and once to stop the Ghidra server. A clean gate takes about 4 minutes 42 seconds and a tools-health run about 19 minutes; a batch of 120 groups takes 9 to 12 minutes, gating 85 to 194 binaries. 218 of 218 binaries identical on every batch. Start to end: cross-address groups 3,801 (30,347 instances, 11,340 private copies) → 0 unaccounted (3,214 shared, 12 twin-covered, 575 ledgered: 282 file conflicts, 206 return-type lies, 87 undefined types); trampoline private copies 20 × 133 → 0; levers 1,853 → 1,850 and raw casts 176,445 → 172,942, both from sites collapsing into one header, not new work; struct definitions 4,762 → 4,748; names landed 0, by design.
P43: 2026-11-10 → 11-12, about 47 hours and 127 commits; 38 coder runs (14 in the function batches T9 alone), three lost to session restarts and one blocked; paused for the owner's review of the pilot batch and his three planning decisions, for a Windows restart to stop the hung scan, and to stop the Ghidra server for the mirror. A data batch cost about 6.5 minutes of census, 7 of regeneration, 5 of gate and 20 to 30 of reference scan before the scan was fixed (about 7 seconds for 48 renames after). 218 of 218 binaries identical on every batch. Start to end: names ledger 0 → 2,171 rows; curated names without a citation 1,083 → 0; worklist 500 → 2 cited, 393 guesses, 105 unnamed with a reason; lever sites with a wall named on the line 0 → 1,850; guessed-data declarations with a ledger pointer 0 → 160,465.

**What we would do sooner.** Read the target project's TREE before setting a policy on its precedent. Make every commit that advances a task
carry its log line, and checkpoint before any long wait past ~85 % context. Price a residue by distinct SHAPES, never by bodies. Put a
known-true case — the tree's own body scoring 0 — in front of every scorer before any campaign. Run every generator on an agent's start text
at every landing. Bucket the residue by what it needs at every wave close, as the stop-rule's input. And for a types phase: probe the
spelling on the bytes on the first day (six minutes for 165 bodies) before designing the engine — it corrected the charter, fixed the rewrite
table five times, and proved the oracle needs a linked-relocation mode before a single global block was rewritten. When a byte question
has a linker in it, ask the linker (the build's own tail), never re-derive its arithmetic; snapshot an oracle's baseline only from a clean run
and make the snapshot refuse what it cannot reproduce; compute every process pool before the first thread. Read a census's rows against the
DEFINITIONS' names before pricing a campaign on them — a function defined under another name is a hole in the denominator, and a planner
should count only the rows its engine can act on. S108 added the sharpest version of the lesson: a census can be wrong about its own denominator in five independent ways at once (an index
that skips a sibling's includes, a name where an identity was needed, an anchored regex, a counter that never read included bodies, a
snapshot that stamps an empty build), and every repair moved the count by thousands while no rung got smarter — so a "stalling" number is
first a question about the instrument, then about the population, and only then about the method; and the stop rule for a mechanical
campaign is the remainder bucketed by its recorded cause, never the yield of the last two batches. In one line, the
generation's rule so far: *the byte gate is still the only judge, and after 100 % it judges spelling.* From the migration and
Phase 38: in the migration itself, grep the tools and the build for every path it retires, and normalise every id it inherits; keep a
published narrative's duty in a rule a task executes, not in a session habit. Test each milestone count against its instrument on the
planning tree before approval — both directions: the starting tree fails it, and the target the plan describes can pass it — and write
the gate's reading into the plan rather than discovering it at the fifth task. Put every attribute the compiler reads into a layout
hash before the first fold, and let the byte gate, not a hash, say two types are one. (P39) Make that test a step of plan approval,
not a paragraph here: the same failure twice in a row says a written lesson is not applied unless something runs it — put every
milestone clause through its instrument on both trees before the plan is approved. Size a residue by its recorded cause before planning
a sweep: T10's concentration table (half of the TYPE-NOT-CANONICAL sites on 81 types) would have predicted T4's wall. Check coverage
per site from the first residue row, and key a planner by the definitions' names, aliases included. (P40) Measure the tail's
distribution — sites per type — before choosing a zero target. Re-run the census after every sweep before freezing anything on it.
Require a wall vocabulary from the first crack wave, not after it. Run the struct and cast gates after every task that edits bodies, not
only at the milestone. Back up irreplaceable ledgers outside the repository from the start, which the phase did only at its end. (P41) Compare a declaration's return type with the definition's from the first day, in one shared prototype header every file includes, and keep a cast at the call where a void-to-int change moves bytes. Make a gate's verdict reachable the day it is written, or split it: a gate that is red by construction teaches its readers to ignore it. Census the text a scratch check reads, with its old pattern, before folding it into a gate. Mirror the types into the oracle as soon as the headers are canonical, not four phases later. (P42) Split a deferred bucket out of the census the phase itself uses before counting it, since the wider scope rewrites the flag that defines it. Run a pilot batch before the fleet: it found ledger rows keyed to the moved bodies that the plan had not listed. Fix the commit path of a batch script before its first batch. Settle with the owner, before the work, what a stop rule's "0" means for classes the bytes refuse. Look at what actually varies across copies before choosing a parameter. Build the rename scanner before any rename, as here, and plant a miss to prove it. (P43) Make the rename tool binary-scoped before the first rename, not as a batch's first step. Bound every scan's wall-clock time and join its patterns from the start. Count how many names have outside evidence before planning a naming phase, so the plan expects guesses. Treat a coder's sheet cut off by a restart as a draft. Refresh the series census before tools-health, and remove a lever's residue row in the same commit as the lever.
