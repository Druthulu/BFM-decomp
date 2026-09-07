# 12 — The failure museum: what looked right at the time

Every exhibit is a real BFM failure, taken from the decision log, the PhaseEnds' "what we believed" sections and the
accelerators ledger (the anchored list is [`docs/retrospective.md`](../retrospective.md)). The column that matters is
the third: **why it looked right**. A failure that looks wrong gets fixed the same day; these did not.

| # | What it looked like | What it was | Why it looked right | What it produced |
|---|---|---|---|---|
| 1 | A recompilation first would force the memory map into the open | A matching decomp needs no recompiler; recomp output feeds no matching work | The one precedent had done it that way | Decided before the first commit: decomp-first |
| 2 | "Structural families template at ≈0% — families cannot be automated" (steered two phases) | A single probe silently omitted a required jump-table carve; run correctly the same family matched 89% | The probe exited 0 with a number | R35: fix the instrument before trusting the measurement |
| 3 | The engine holds a bytecode script VM to reverse-engineer | Compiled MIPS dispatch tables; no VM exists | Every game has a script VM | A written determination replaced a phase of work |
| 4 | The remaining engine core is blocked by loose typing and missing signatures | The wall was the compiler's own code generation | Types are the usual suspect | The compiler-quirk research, then the codegen map |
| 5 | Residuals that resist every rewrite are "unsteerable" | Reading the compiler's passes explained them one by one | Dozens of rewrites had failed | THE BREAKTHROUGH; "unsteerable" means "not yet read" |
| 6 | A "~3% swing number" is a wall class (haunted three phases) | An `-O0` compile-flag artifact of the tooling | It was consistent across probes — because the probe was consistently wrong | R37 probe before costing |
| 7 | The endgame plan's numbers describe the remaining work | Broken scanners had been measuring the frontier — "the plan was majority-fiction" | The scanners had never disagreed with anything, because nothing checked them | R32/R34: assert coverage; a second disagreeing oracle |
| 8 | A corpus scanner reports the decomp complete | It could not answer and returned an empty set; green is what success looks like | An empty "remaining" list *is* what done looks like | R43: refuse loudly, never mishandle |
| 9 | Every draft of the main executable reads "near" for a month | The shared gate compared main against *another binary's* hash | The gate was green — for the wrong reason | Per-binary contracts; R50, R56 |
| 10 | The main executable cannot be gated ("a linker defect") | Incremental builds re-run a linker-script rewrite; a no-draft control produced the same wrong hash | Four byte-correct drafts gated 0/4, reproducibly | Gate main only by a clean rebuild; R22 |
| 11 | The waves are limited by idioms the drafters lack | ≈92% of drafts byte-correct, ≈27% banked: integration was the bottleneck | Failures arrived as "no match" verdicts | The reconcile ladder; "budget for banking" |
| 12 | The disc has been fully counted (136, then 140 binaries) | 73 more code-bearing payloads; 4 overlays put their code at PAC entry 1; a first sweep's 4,096-word window missed half | The fleet was 100% green on what it built — the gate is blind to what it was never asked to build | `make audit-disc`: a residue-0 partition, claimed-by derived from the contracts |
| 13 | A band of the executable is a compiler wall (twelve functions, proofs attached) | Sony's controller library, February 1998; the archive was on the internet | Each proof named a real pass behaviour | Provenance → archive → link → compiler |
| 14 | `SaveLoadRoutine` is a wall | Its body was byte-identical; the "wall" was a splat symbol boundary | The diff was real | Suspect the split before the compiler |
| 15 | The permuter has exhausted the pinned near-misses | It had never run on a pinned seed | It reported "unchanged" every cycle | R61: a loop that reports unchanged must prove it iterated |
| 16 | A function is finished | Its "C" was the original assembly pasted into an `__asm__` body — and 199 such bodies existed | The byte gate is a null oracle for "is this C?" | R62; the verbatim manifest reduced to the 5 genuine hand-written routines |
| 17 | Two functions are PROVED unmatchable by producer censuses | Each census was one producer short (a combine-pass bookkeeping gap; the loop optimizer's user-variable rule) | Every refutation on the list was real | R69: "proved" names its list; R73: reproducers first |
| 18 | The register pins on the last four functions are the levers | Symptoms: every pin came off byte-identical once the source shape was right | Pins moved the diff | R73: read the allocation order before any register lever |
| 19 | A 0.55 "weak cousin" is unrelated | The exact same-shape sibling; the crack was a grep and one port, after ≈1 M tokens of dial work | The similarity score was a number | R72: a similarity score is not a shape oracle |
| 20 | The exclude list is current | 88 of 107 entries stale the day after it was written — 46 of them 12,750 instructions of drawable work | Every entry had been true once | The draw refuses a stale list; a list records what the *tooling* could not do |
| 21 | The agents have the laws file | It sat one directory below where every agent was told to read; the brief silently degraded to "the pack alone" for every wave | Two agents said so; the rest never mentioned it | Pass the wave directory, not the packs directory; check the coverage line |
| 22 | "No banked twin — derive from the .s" (on the card) | Banked verbatim at the same address in another binary; 102k tokens re-deriving it | True of the card, false of the world | The twin scan runs over the world; R44 |
| 23 | A whole wave was a drafting collapse (105 cards, 0 banked) | The gater had accepted a binary class it structurally could not gate | The other 115 cards banked 94 | R43 |
| 24 | Eleven functions failed the gate | 79 draws across 19 waves of functions compiled at a different optimization level than their object — none could ever bank | Each failure looked like a model failure | R45: draw-time bankability |
| 25 | "12 banked of 12" | The tool compared names against a set keyed by address — always true | It printed a fraction | R41/R33: derive from an invariant; assert the denominator |
| 26 | Healthy lane activity in the logs | The draw refused the whole wave whenever any binary was mid-gate and fell back to pre-drawn waves; every new draw feature stopped reaching the fleet | The logs showed work | Scope a refusal to what is actually unsafe |
| 27 | The main executable's game-code denominator is settled | The disassembler's boundaries under-counted it by 3,616 instructions | It had been stable for a month | Derive boundaries from the build's own link map |
| 28 | The history rewrite is a mechanical filter run | The empty blob's id in the strip list silently undid every "file emptied" change; a byte-identical commit keeps its hash | The filter exited 0 and the purged paths were gone | Rehearse; prove pair by pair with positive assertions |
| 29 | The local gc dropped the old history | Twelve forgotten gate worktrees (12 GB) pinned 3,729 old commits | `rev-list --all` had been read before the worktrees were | A linked worktree's HEAD is a ref |
| 30 | The purge probe is read-only | Every successful fetch of an old hash imported its closure — 5.9 GB of the purged history back into the guarded repository | The probe only *reads* GitHub | R57: an instrument's own write path is part of the instrument |
| 31 | A fresh session read a hand-off as "done" and nearly closed an open phase | The summary said so | A compressed summary looks like a conclusion | R64: the checkpoint is replayed verbatim, never summarised |
| 32 | A wall class's estimate ("2,318 externs to fix") | 57 crossed the line | The count was true — of a scope no one had asserted | R41: every effort estimate ships its denominator |
| 33 | Two ledger messages say "banked" | A helper that did nothing on an empty list and exited 0; a wrong draft directory | The intent was there | R66/R68 |
| 34 | The permuter plateaued; the ILS logs are quiet | Empty logs for 20 minutes: never started | Quiet looks like working | R55: an unattended lane leaves evidence |
| 35 | The rate limit is ~95 req/min | A launch burst; the steady state was far higher | The first measurement was a real number | Measure the steady state, bucketed over time |
| 36 | An agent's "no draft" after a rate limit | One sat three instructions from a match with its candidate history on disk | The verdict said no draft | R40: exonerate the instrument; read the scratch directory |

## The pattern, stated once

Almost every wall was an instrument. The instrument was correct when written and went stale as the population under it
widened; it returned a true number about a narrower world; nobody compared what it found to what it should have found.
The cure is not vigilance — the author of one of the rules above rebuilt the exact defect the rule warns about an hour
later in a different file. The cure is structural: two paths per question, on a schedule, failing loudly on
disagreement ([chapter 04](04-oracles-and-instruments.md)); a known-true case before any reading; the denominator on
every number; and a decision log that records each of these while it still hurts.
