# Levers — the register pins and compiler hints, what they cost, and what to do about them

> **What this is.** The living record of every compiler-forcing construct in this decompilation: how many there are, how they
> got in, how they come out, and — the part that outlives the project — whether a decomp should refuse them from its first
> bank or clean them up at the end. The numbers below are **generated** (R75); the argument is written from them.
>
> **Maintained:** updated at the close of every Phase-36 task (`tools/lever_progress.py --snapshot "<task>"`, which also
> re-renders the tables here). Sources: `tools/lever_census.py` for the counts, `.run/P36/delever/ledger.jsonl` for the
> campaign, `docs/lever-progress.tsv` for the series a chart is drawn from.
>
> **Audiences:** the post-100% chart and the project story · the wiki (a "Levers" page) · `decomp-architect/` (the day-one
> kit: the rule a new project should adopt at its first bank, §"What we would do from day one").

---

## 1. What a lever is

A **lever** is a construct that exists only to force the compiler's output — it says nothing about what the program does.
This project's C is full of them because bytes were the only thing being optimised:

| class | what it looks like | why a drafter reached for it |
|---|---|---|
| **A** register pin | `register s32 x __asm__("$16");` | name the register the allocator must use |
| **B1** barrier | `__asm__ __volatile__("" ::: "memory");` | stop the scheduler moving code across a point |
| **B2** launder | `__asm__("" : "=r"(x) : "0"(x));` | break a value's history so cse/combine cannot see through it |
| **B3** keep-alive | `__asm__("" : : "r"(x));` | keep a dead value live |
| **B4** hand-placed instruction | `__asm__("addu %0,%1,$zero" …)` | emit exactly this instruction |
| **B5** GTE op | `__asm__("lwc2 …")` behind a per-TU macro | *not a lever* — Sony's coprocessor idiom; consolidated, not removed |
| **C** volatile | `*(volatile s32 *)(p + 4)` | force a reload |
| **D** bare `register` | `register int i;` | a hint gcc 2.7.2 at `-O2` ignores |
| **E** asm-label alias | `extern u16 aD800B9A02 __asm__("D_800B9A02");` | a second typed view of one symbol |
| **F** builtin | `__builtin_memcpy(&a, &b, N)` | a struct assignment in disguise |
| **G** attribute | `__attribute__((packed))` | a layout the type layer should carry |

Classes **A and B are the ones this phase drives to zero.** C and D stay if the bytes need them (ordinary C, ledgered and
counted, not marked). E, F and G belong to the canonical type layer and are the **types phase's** work (R95).

---

## 2. The numbers

<!-- BEGIN GENERATED: lever_progress.py -->

### Milestones — the count, at each moment a census ran

| date | milestone | pins | asm | **class A+B sites** | bodies | distinct | GTE levers | per-TU asm macros | C | D | E | F | G | HEAD |
|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|
| 2026-09-09 | T6 r1 (rung R's first class) | 20512 | 13445 | **33957** | 12578 | 1758 | 462 | 314 | 1722 | 50 | 7428 | 445 | 76 | `1761a3125` |
| 2026-09-09 | T6 d1 (rung D's four exemplars) | 20508 | 13445 | **33953** | 12574 | 1758 | 462 | 314 | 1722 | 50 | 7428 | 445 | 76 | `8fac96651` |
| 2026-09-09 | T6 p1 (four classes propagated) | 19982 | 13445 | **33427** | 12048 | 1755 | 462 | 314 | 1722 | 50 | 7428 | 445 | 76 | `a2da99b13` |
| 2026-09-09 | S101 rung G g1 (the guided search's first run: 1 of 16 exemplars, 132 bodies) | 19982 | 13313 | **33295** | 11916 | 1754 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `623e55340` |
| 2026-09-09 | S101 rung G g2 (wider beam + R10/R12/R13/R8-cse: 1 of 16, 132 bodies) | 19718 | 13313 | **33031** | 11784 | 1753 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `584031c71` |
| 2026-09-09 | S101 rung G g3 (the next 64 classes: 13 of 64, 1,516 bodies) | 18442 | 12583 | **31025** | 10268 | 1740 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `5ae0b5ceb` |
| 2026-09-09 | S101 rung G g4s (the 13 explained names, 38 classes: 3 of 38, 133 bodies) | 18309 | 12583 | **30892** | 10135 | 1737 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `068781ae0` |
| 2026-09-09 | S101 rung G g5 (the head re-drawn wide: 5 of 70, 62 bodies) | 18261 | 12545 | **30806** | 10073 | 1732 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `1ec67f667` |
| 2026-09-09 | S101 rung G g6 + g6b (the tail: 47 + 63 of 400 small classes, 93 + 186 + 47 bodies) | 17954 | 12404 | **30358** | 9747 | 1624 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `2f3ce92a1` |
| 2026-09-10 | S102 T7 a1 — func_80156044 closed by an agent (merge-point expression sunk into the if/else arms, both $2/$3 pins gone); 130 bodies banked (1 + 129 propagated) | 17694 | 12404 | **30098** | 9617 | 1623 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `5a8bd1021` |
| 2026-09-10 | S102 T7 s1 — the R15 sweep of the head: 6 exemplars closed by the sink alone (267 bodies), no drafting tokens | 17427 | 12270 | **29697** | 9350 | 1617 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `861dd0651` |
| 2026-09-10 | S102 T7 a2 — func_80168828: the constant-holder pin deleted and one adjacent swap closes it (125 bodies, 1 of 2 pins off; the $4 pin is forced by the header's (void) declaration) | 17302 | 12270 | **29572** | 9350 | 1617 | 462 | 314 | 1590 | 50 | 7428 | 445 | 76 | `c00ffe5d4` |

### The campaign — every batch, from the ledger (derived on every render)

| batch | date | rungs | bodies first judged | sites removed | rewritten | sites closed later | bodies made lever-free |
|---|---|---|---:|---:|---:|---:|---:|
| `t3_tus1` | 2026-09-09 | A,B | 176 | 211 | 4 | 0 | 0 |
| `t3_scrub` | 2026-09-09 | scrub | 1 | 0 | 0 | 0 | 0 |
| `tus1` | 2026-09-09 | A,B,replay | 1,392 | 3,241 | 101 | 0 | 0 |
| `tus2` | 2026-09-09 | A,B,replay | 2,752 | 3,501 | 4 | 0 | 0 |
| `tus3` | 2026-09-09 | A,B,replay | 2,513 | 2,910 | 15 | 0 | 0 |
| `tus4` | 2026-09-09 | A,B,replay | 2,224 | 2,012 | 131 | 0 | 0 |
| `tus5` | 2026-09-09 | A,B,replay | 1,225 | 1,811 | 10 | 0 | 0 |
| `tus6` | 2026-09-09 | A,B,replay | 1,409 | 1,667 | 0 | 0 | 0 |
| `tus7` | 2026-09-09 | A,B,replay | 1,407 | 1,853 | 2 | 0 | 0 |
| `tus8` | 2026-09-09 | A,B,replay | 602 | 432 | 0 | 0 | 0 |
| `tus9` | 2026-09-09 | A,B,replay | 1,901 | 2,234 | 10 | 0 | 0 |
| `tus10` | 2026-09-09 | A,B,replay | 362 | 408 | 3 | 0 | 0 |
| `headers1` | 2026-09-09 | A,B,replay | 200 | 301 | 1 | 0 | 0 |
| `headers2` | 2026-09-09 | A,B,replay | 171 | 197 | 2 | 0 | 0 |
| `gte1` | 2026-09-09 | gte | 399 | 0 | 0 | 0 | 0 |
| `gte2` | 2026-09-09 | gte | 244 | 0 | 0 | 0 | 0 |
| `sweep1` | 2026-09-09 | sweep | 4 | 0 | 0 | 0 | 0 |
| `sweep2` | 2026-09-09 | sweep | 3 | 0 | 0 | 0 | 0 |
| `sweep3` | 2026-09-09 | sweep | 134 | 0 | 0 | 0 | 0 |
| `r1` | 2026-09-09 | R | 0 | 0 | 0 | 134 | 134 |
| `d1` | 2026-09-09 | D | 0 | 0 | 0 | 4 | 4 |
| `p1` | 2026-09-09 | D | 0 | 0 | 0 | 394 | 394 |
| `p1b` | 2026-09-09 | D | 0 | 0 | 0 | 132 | 132 |
| `g1` | 2026-09-09 | G | 0 | 0 | 0 | 2 | 1 |
| `g1p` | 2026-09-09 | G | 0 | 0 | 0 | 262 | 131 |
| `g2` | 2026-09-09 | G | 0 | 0 | 0 | 2 | 1 |
| `g2p` | 2026-09-09 | G | 0 | 0 | 0 | 262 | 131 |
| `g3` | 2026-09-09 | G | 0 | 0 | 0 | 17 | 13 |
| `g3p` | 2026-09-09 | G | 0 | 0 | 0 | 1,989 | 1,503 |
| `g4s` | 2026-09-09 | G | 0 | 0 | 0 | 3 | 3 |
| `g4sp` | 2026-09-09 | G | 0 | 0 | 0 | 130 | 130 |
| `g5` | 2026-09-09 | G | 0 | 0 | 0 | 7 | 5 |
| `g5p` | 2026-09-09 | G | 0 | 0 | 0 | 79 | 57 |
| `g6` | 2026-09-09 | G | 0 | 0 | 0 | 66 | 47 |
| `g6b` | 2026-09-09 | G | 0 | 0 | 0 | 72 | 63 |
| `g6bp` | 2026-09-09 | G | 0 | 0 | 0 | 39 | 30 |
| `g6p` | 2026-09-09 | G | 0 | 0 | 0 | 275 | 186 |
| `a1` | 2026-09-10 | E | 0 | 0 | 0 | 2 | 1 |
| `a1p` | 2026-09-10 | E | 0 | 0 | 0 | 258 | 129 |
| `s1` | 2026-09-10 | G | 0 | 0 | 0 | 10 | 6 |
| `s1p` | 2026-09-10 | G | 0 | 0 | 0 | 391 | 261 |
| `a2` | 2026-09-10 | E | 0 | 0 | 0 | 1 | 0 |
| `a2p` | 2026-09-10 | E | 0 | 0 | 0 | 124 | 0 |
| **total** | | | **17,119** | **20,778** | **283** | **4,655** | **3,362** |

*Generated by `tools/lever_progress.py --render` from `.run/P36/census/lever_census.json` and `.run/P36/delever/ledger.jsonl`; the series lives in `docs/lever-progress.tsv` (R75: published numbers are generated, never typed).*

<!-- END GENERATED -->

---

## 3. How they got in

Nobody sat down to write 34,000 levers. They arrived one bank at a time, over five phases, each time as the cheapest way
past a real wall:

- **Phase 18** researched gcc 2.7.2's register allocator and produced *the pin toolkit* (cookbook §17). It worked: the wave
  close-rate went 33% → 56% → 90% in one phase. Pins were the difference between a wave that banked and a wave that did not.
- **Phases 19–29**, the family campaign, scaled that: one cracked exemplar remapped across up to 134 overlays, and every
  lever in the exemplar was copied with it. **This is why the count is in the tens of thousands and the distinct count is in
  the hundreds** — 12,578 bodies carry class A/B sites, but only 1,758 distinct texts.
- **Phase 23's** local-model tier and **Phase 30–31's** autonomous lanes drafted at a rate no human reviewed line by line;
  a pin that made the byte gate go green was, correctly for those phases, a win.
- **§501-E** (Phase 32) then replaced pins with *launders* on some functions — trading one lever for another. That recipe is
  explicitly out of bounds in Phase 36.

Two facts about that history matter for the argument below. First, **the knowledge needed to remove a lever did not exist
when the lever was added** — the §31 codegen map (Phase 23), the allocation-order reading (`alloc_table.py`, Phase 32) and
the §501-P/Q/R producer censuses all came later. Second, **Phase 32 measured the thing that makes this a debt rather than a
cost**: on the last four functions of the frontier, *every* pin came off byte-identical once the source shape was right
(R73). A pin was rarely load-bearing. It was a shortcut around finding the shape.

---

## 4. How they come off — the ladder, and what each rung is worth

| rung | what it does | cost | measured yield |
|---|---|---|---|
| **A** strip-all | remove every lever in a body at once, compile, compare | 1 compile | see the campaign table above |
| **B** greedy | re-add sites one at a time to find the minimal needed set | ≤ sites+1 compiles | the residue after A |
| **C** exemplar/replay | a multi-copy class judged once, replayed to every copy | 1 compile per copy | most of the fleet's copies |
| **R** recipes | the cookbook's byte-neutral **shape** recipes, mechanically (R2 declaration order · R3 initializer split · R4 one declaration moved through the run · R5 operand order of one commutative operator · R6 a single-set temp inlined at its use · R7 one statement wrapped in a block) | 1 compile per candidate | **134 of 134 bodies in 6.0 min, 3,243 compiles** (batch `r1`) |
| **D** permuter | decomp-permuter seeded with the **lever-free** body against the target bytes | ~12 min per exemplar | **5 of 16 exemplars, 665 of 2,131 bodies behind them, 0.69 h** |
| **E** agents | one agent per surviving class exemplar, with the pack | tokens | Phase 36 T7 |

**RUNG R IS A REPLICATION ENGINE, NOT A DISCOVERY ENGINE — measured, S99.** On a class whose shape rung D had already found it
closed **134 of 134 bodies in 6 minutes**. On 300 residue bodies where nobody had found the shape yet it closed **0 of 300 at
`--cap 40` (12,110 compiles, 4.6 min) and 0 of 300 at `--cap 400` (17,140 compiles, 6.0 min)`**. Two things make that a real
result rather than a budget problem: the instrument was checked on one body by hand (every candidate COMPILES and returns
DIFFERS — nothing was erroring out silently), and 17,140 compiles over 300 bodies is ~57 candidates each, so **the cap was
never the binding constraint** — ten times the depth produced 42% more candidates and closed nothing. The recipe rung banks a
KNOWN shape across a class for free; it has nothing to say about a shape that is not in its list. Growing it means finding
more shapes (rung D, then agents), and harvesting each one back into the rung so it sweeps the population for free.

**The two rungs feed each other.** Rung D's wins are not exotic: each is a small nameable source shape — a statement wrapped
in a block (`flag = 0;` → `do { flag = 0; } while (0);`), a single-set temp inlined at its use. Every one of them became a
rung-R recipe the same session, and rung R then banks the whole class **mechanically, as a one-line diff in the real
source**, where banking the permuter's own output would paste a pycparser-reprinted body into a phase whose entire purpose
is readability. Rung D is the *scout*; rung R is the *harvest*.

**What the residue looks like.** After rungs A–C the survivors split by the *starting distance* of the lever-free body from
the target, not by how many sites they carry: exemplars 8–29 mismatched instructions away closed (5.9 s to 651 s); those
70–276 away did not close in 12 minutes, and every one of those is a body where removing a hand-placed **instruction**
lever changed the instruction *count* and shifted everything after it. None is a wall — they improved 78→9, 52→3, 50→3,
37→2 — they are seeds for a longer run or for an agent.

**An instrument warning that cost two campaigns** (cookbook §454): a search harness whose target is *assembled from a
disassembly listing* is not measuring your code. `objdump` prints the pseudo-instruction `move` for `addu rX,rY,$zero` and
GAS assembles `move` as `or`; a listing's `%hi`/`%lo` pairs come back resolved with no relocation. The scorer read 28 for a
body that was byte-identical, so score 0 was unreachable and two campaigns reported "0 of 16" about a population that was
fine. **Seed any byte search with a body that already matches and require base score 0 before believing a yield.**

---

## 5. The question that outlives the project: prevent, or clean up at the end?

The honest answer is **neither extreme**, and the evidence points at a specific middle.

**What the numbers say.** The mechanical rungs (A/B/C) removed or rewrote **21,061 sites across 17,119 bodies** — the
campaign table's own totals — against **33,957** still standing: **38% of the class A/B population came off with no
understanding at all**, by strip it, compile, compare. Those levers were never load-bearing. They were speculative, added by a drafter that had no
cost signal for adding one, and a *single compile at bank time* would have refused them. That is the strongest measured
claim in this document: **more than a third of the debt would never have existed if banking a function had asked "does it
still match without this?" once.**

**What the history says against blanket prevention.** The pin toolkit is why Phase 18's waves closed at all, and the
knowledge to *replace* a pin with the right source shape did not exist until Phases 23–32. A rule of "no levers, ever"
adopted in Phase 18 would have stalled the project at ~56% for months, in exchange for a debt that a later phase paid off in
weeks with better tools. Deferring was not obviously wrong; **deferring silently was.**

**The rule we would actually adopt from day one** — and the one the day-one kit should carry:

1. **A lever is allowed, and it is a marked, ledgered debt from the moment it is banked.** One comment at the bank site
   naming the class and what it forces (`// !FAKE: pin $16 — without it gcc allocates x to $17`), and a census that counts
   them. Phase 36 had to *re-derive* that reason for 34,091 sites, function by function, years after the fact; writing it
   once at bank time is nearly free and is the difference between a debt and an archaeology project.
2. **The bank-time trial: compile the body once without the lever before accepting it.** One compile. It would have refused
   ~37% of the population at the moment of creation, when the context was hot.
3. **Publish the count as a first-class metric next to the match percentage.** A number nobody publishes is a number nobody
   pays down. This project's lever count was invisible until the phase that removed them.
4. **Levers get the harvest → toolify treatment, exactly like idioms.** When a wave learns the shape that replaces a lever
   class, that shape becomes a mechanical recipe and sweeps the banked population — instead of the lever propagating with
   every family remap (which is how 1,758 distinct bodies became 12,578).
5. **Do NOT block a phase on lever-freedom.** Keep the byte gate as the only gate; let the marker and the count carry the
   debt forward. A cleanup phase with mature tooling is genuinely cheap — rung A/B is a few hours of compute for a third of
   the population, and rung R banks a 134-copy class in six minutes.

**In one line for the kit:** *ban the silence, not the lever.*

---

## 6. For the wiki and the kit

- **Wiki page ("Levers")** — sections 1, 2 and 5 of this document, plus the current chart. The count belongs beside the
  match percentage on the progress page: a project that is 100% matched and 34,091 levers deep is not finished, and saying
  so plainly is the difference between this decomp and the ones the community complains about (`docs/gen3-standards.md`).
- **`decomp-architect/`** — section 5's five rules, as a Phase-1 kernel (a lever is a marked debt; the bank-time trial; the
  published count; harvest→toolify for levers; never block the byte gate on it) with this document's measured numbers as
  the provenance. The taxonomy in section 1 transfers unchanged to any gcc-era PS1 decomp.
- **Parked for the endgame (Drew, 2026-09-09):** train a **gcc 2.7.2 LoRA on the final clean asm/C pairs** and release it for other
  decompilations to use when cracking. Not now, and not on today's corpus: our 363,214 matched pairs are (asm → C-*with*-levers), so
  training on them teaches a model to PRODUCE pins. The corpus worth releasing is the one this phase creates — lever-free C beside its
  bytes — which is another reason to finish the removal before the project ships its dataset.
- **The story** — the arc is: a toolkit that unlocked the project (P18) → a family engine that multiplied it 134× (P19–29) →
  a phase that measured the debt for the first time (P36 T1) → mechanical removal of a third of it (T4) → a scout-and-harvest
  loop for the rest (T6) → zero (T7). The interesting beat is not the cleanup; it is that **the shortcut that made the
  project possible was also the thing it had to spend a whole phase undoing**, and that both were the right call at the time.

---

## 7. Maintenance

Run at the close of every task that changes the count, and at every phase close:

```
.venv/bin/python tools/lever_census.py --sites --check -j 16     # the count, and 0 UNMARKED
.venv/bin/python tools/lever_progress.py --snapshot "T6 r1"      # appends the milestone row, re-renders §2
```

`tools/lever_progress.py --check` fails when the series' last row is not this tree — a stale series is a wrong chart.
