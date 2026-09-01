# The Generic Decomp Package — what a NEW decompilation should inherit on day one

> **Status: the thesis, recorded S68 (2026-08-31) by Drew, from hindsight over this project.**
> Feeds the endgame deliverables (the retrospective + the public "how to AI-decomp" wiki).
> This is NOT a plan for BFM. It is what the NEXT project starts with instead of starting empty.

## The claim

This project spent most of its life **brute-forcing functions and then widening tooling whenever a
new idiom revealed a population the tooling could not see.** In hindsight that order is backwards.
A new decomp should spend its FIRST phases building the wide tooling and seeding the knowledge base,
and only then start cracking — because every tool built early pays on every function afterwards,
while every function cracked early pays once.

The evidence is this project's own zero-token banks: whole classes (twins, families, siblings,
cousins, `-O0` carves, propagation, stranded boundaries) that cost nothing per function ONCE the
tool existed — and that were invisible until an idiom taught us to look.

## What the next project inherits, and does BEFORE cracking

**1. The knowledge base, seeded from sources that exist before any match does.**
* Mine the actual COMPILER SOURCE for the target triple. This project's highest-value late idioms
  (§368 reload-remat, §372 copy-capture, §370's `schedule_select` bound, §373's `pri(asm)=1`) came
  from reading `gcc-2.7.2`'s own passes — `reload1.c`, `cse.c`, `local-alloc.c`, `sched.c`,
  `stmt.c`. **None of that required a single matched function.** It could have been mined in week 1.
* Mine SIBLING PROJECTS on the same compiler (this project used Vagrant Story / sotn-decomp).
* Carry `docs/matching-cookbook.md` (399 sections) + `cookbook-index.md` (the symptom→section table)
  across as the starting corpus, adapted for the new triple rather than rebuilt.

**2. The structural tooling, before the first crack.**
The families/twins/dedup layer is what converts one crack into N banks. In BFM this arrived late and
retroactively harvested thousands of instructions. Port it first:
`corpus` (the coverage oracle) · `seed_ref` (exact-hash twin join **AND its `--near` edit-distance
band — see 2b**) · `family_remap` /
`family_sweep` · `dedup_propagate` (position-locked overlay sharing) · the `-O0`/opt-level carve
chain (`o0_detect`, `o0_subsplit`, `o0_boundary`) · `wall_sweep` (toolchain walls) · the draw
filter · the byte-gate + clean-fleet verifier.

**2b. THE SIMILARITY JOIN MUST BE A BAND, NOT A POINT (P31 S69 — port this, it is cheap and it
compounds).** A twin oracle keyed on an exact signature hash answers only *"is there a byte-identical
copy?"*. That is the wrong question for a frontier. The right one is *"is there anything CLOSE?"*, and
the difference is not marginal:

| tier | reachable open stubs with a banked match |
|---|---|
| exact hash (d=0) — where this project sat for 60+ sessions | **22 of 352 (6%)** |
| edit-distance band to d<=25 (`seed_ref --near`) | **75 of 352 (21%)** |

**A 3.4x widening, found in one agent-run, on a corpus we thought was fully mined.** 31 of the new
rows were PURE reloc-only twins of already-banked bodies — free work that had been sitting invisible;
8 banked the same day at ~0 agent tokens. The root cause was a normalizer that under-matched by
design (§389): safe for dedup, silently lossy as a frontier join.

For a NEW decomp this matters *more* than it did here, because the band pays from the very first
banks: every function you crack immediately becomes a potential exemplar for everything within a few
instructions of it, and you never accumulate the invisible-singleton debt this project spent a
session recovering. Build the near tier at the same time as the exact tier — not sixty sessions
later. Concretely: normalize relocations out of the instruction stream, prefilter soundly on
length/opcode-histogram so no true pair can be lost, then edit-distance the survivors; assert the
population (R32), cross-check that the band reproduces every exact-hash pair (R34), and control
against random pairs for the base rate (R39: 1.17% here).

**And audit every hash you own for BOTH questions.** Dedup wants under-matching; a frontier join
wants over-matching. One hash cannot serve both error directions, and the failure is silent.

**Rank the band by WORK, not by distance, and stop building scanners once it is dry.** Two findings
that cost a session here and are free to inherit:

* *A deletion is free, a substitution is thought* (§390). Edit distance ranked a 5-substitution twin
  above a pair that was the same C minus one trailing statement — the second banked at closeness 0.
  Order candidates by (substitutions + regions, coverage); use distance only as a filter. And filter
  LOOKALIKES at `r = d/min(nins) >= ~0.3`: 17 of 30 "cousins" here were two different functions
  sharing boilerplate, and a wrong twin is worse than no twin because the agent believes it.
* *Know when to stop.* After the reloc-only class, three fleet-wide probes returned **0 new / 9 / 2**.
  The similarity well runs dry fast. In the same session the INTEGRATION levers — making an
  already-correct body compile inside its real translation unit (§376/§378) — banked an order of
  magnitude more. **Budget accordingly: scanners early, integration forever.**

**3. The differential-oracle harness (accelerators #15) — the one that works at 0%.**
Two independent paths per question, disagreement fails loudly, on a schedule.

**4. The periodic widening review (Drew's addition, and the part this project did only by accident).**
At every session/phase close: review the tooling against the idioms learned that phase and ask
**"which scanner's denominator just got wider?"** New idioms do not only make the next crack easier —
they retroactively convert already-open functions into free banks, but ONLY if a tool is widened to
see them. S68's §332 sweep is the worked example.

## The order this implies

    phase 0   compiler-source + sibling-project idiom mining -> seed the cookbook
    phase 1   structural tooling: corpus, families, twins, dedup, carves, walls, byte gate
    phase 2   the differential-oracle harness + the draw filter
    phase 3   FIRST cracks — and from here every crack feeds the widening review
    ...       every phase close: idioms -> tooling widening -> free banks

## The honest caveat

Tooling-first does not remove the hard tail. This project's remaining frontier at S68 was **418
functions / 62,717 instructions**, of which only ~5% was mechanically free and 947 instructions were
*permanently* unbankable from C (toolchain walls). The structural work — §366 case-label unstacking,
§368's uncolorable local, §358's unreferenced aggregate — needed genuine reasoning and always will.
**Tooling-first makes the cheap half nearly free and stops the waste; it does not shrink the hard
half.** Sell it as that and it is true; sell it as "no hand-cracking" and it is not.

## Where the pieces live today

`docs/matching-cookbook.md` + `docs/cookbook-index.md` (the knowledge) ·
`docs/accelerators.md` (hindsight tools, #15 is the day-one one) ·
`docs/wave-playbook.md` (the running procedure, each guard paired with the measurement that earned it) ·
`docs/decision-log.md` (WHY each pivot happened) · `tools/` (the toolset) ·
`phase-ends/` (the build history the retrospective is reconstructed from).
