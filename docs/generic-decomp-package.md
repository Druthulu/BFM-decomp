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
`corpus` (the coverage oracle) · `seed_ref` / twin join on signature hashes · `family_remap` /
`family_sweep` · `dedup_propagate` (position-locked overlay sharing) · the `-O0`/opt-level carve
chain (`o0_detect`, `o0_subsplit`, `o0_boundary`) · `wall_sweep` (toolchain walls) · the draw
filter · the byte-gate + clean-fleet verifier.

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
