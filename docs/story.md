# The story — how Brave Fencer Musashi was decompiled in twelve weeks, by an AI agent under a written constitution

> **What this is.** The narrative of the project from its first commit (2026-06-10) through the public flip (Phase 33,
> September 2026) and into the work after 100 % (Gen3, Phase 35 →), written for someone who wants to know what happened and why, in order. Every section names the record it
> was written from — a PhaseEnd (`phase-ends/`), a decision-log entry (`docs/decision-log.md`, cited by its dated heading),
> a digest row (`docs/story-timeline.md`). The numbers are the repository's own (`docs/progress.json`, the timeline). The
> analytical companion — what we believed, what failed, what it cost, what we would do sooner — is
> [`docs/retrospective.md`](retrospective.md). The chart: [`docs/story-timeline.svg`](story-timeline.svg).
>
> **A note on the record.** Transcripts of the first month were lost; the phases up to Gen1 exit are reconstructed from
> the PhaseEnds, the git history and `docs/history/` (the original brief, the methodology template, the research dump).
> Everything after that is written from files that were kept as it happened.

## 0. The premise

*Brave Fencer Musashi* (Square, PlayStation, 1998) had no public decompilation, no disassembly, no symbol list — a
verified greenfield in June 2026. The owner's original brief (`docs/history/claude-bfm-starting-point.md`) imagined a
recompilation first, to get the game running natively and force the memory map into the open. The plan that actually
ran inverted that: **decompile first, match byte for byte, defer everything else** — because a matching decompilation
needs no recompiler, and the one recomp precedent for a PS1 game had shown that its output does not feed matching work.

Two ideas set the project apart from the start. First, a **constitution**: `PROJECT_CONTEXT.md`, generated from the
ProjectArchitect template (`docs/history/project_architect_v1.3.0.md`), never edited afterwards, with the rules that
kill AI-driven decompilations written down as rules — *bytes are the only truth*, *a match is byte-for-byte or it is not
a match*, *the Ghidra program and the emulator are the oracles, never general knowledge*, *no ROM bytes in git*. Second,
a **cadence**: phases with two human gates each (the plan, the milestone), autonomous execution between them, a
PhaseEnd file at every close, and a session protocol that starts every session by re-reading the rules. The agent —
Claude Code, driving Ghidra over an MCP server — did the work; the owner approved plans and milestones, pushed, and
decided.

## 1. Gen1 — the foundation, in five days (Phases 1–7, 2026-06-10 → 06-15)

*From `phase-ends/PhaseEnd_Phase1.md` … `PhaseEnd_Phase7.md`, `phase-ends/DIGEST.md` §2.*

The first week built the ground everything else stood on. Ghidra 12.1 with the PlayStation loader and the MCP server;
a deterministic extractor for the disc (`tools/bfm_extract/`) that walks the ISO, the `.CD` containers, the PAC archives
and the LZSS streams into 1,801 manifest-tracked files, byte-validated against the community's reference extractor;
the file loader reverse-engineered — a hand-rolled CD reader driven by a location table, the LZSS staging buffer, the
resident engine blob at `0x800CEDF8` and the location overlays at `0x80128158`, every load address **proven byte-identical
against a live PCSX-Redux RAM dump** (`docs/memory-map.md`); a half-phase spike on the two prototype builds that
returned a clean NO-GO (no symbols, three functions' difference — kept as assets, not leads).

Then the build: splat, the era's GCC 2.7.2 `cc1`, maspsx to reproduce Sony's assembler, GNU binutils — and on 2026-06-14
the first byte-identical `SLUS_007.26` from disassembly alone, SHA1 `143dbb89…`. The compiler triple was **pinned by
fingerprint evidence** the same day (`-O2 -G0 -mips1 -mcpu=3000 …`, `--aspsx-version=2.56 --expand-div` — the last flag
turned out to be mandatory), fourteen functions matched, the LZSS decompressor among them, and the matching cookbook
opened its first page. Phase 7 industrialised the loop (difficulty ranking, duplicate reports, progress scripts), linked
the first real PsyQ library objects byte-identical, and declared **Gen1 EXIT** on 2026-06-15 with 43 matched functions.

## 2. The fleet, and the first ceiling (Phases 8–20, 2026-06-15 → 06-21)

*From `PhaseEnd_Phase8.md` … `PhaseEnd_Phase20.md`; timeline rows 06-15 → 06-21.*

The game's code is not in the executable. It is in the resident engine blob and in 134 location overlays streamed from
the disc — so the toolchain became binary-agnostic (one parameterized pipeline builds any binary), the resident blob
became the second byte-identical binary, and within four days **all 134 overlays were onboarded as byte-identical build
targets**, 136 binaries in all. The single most consequential discovery of the month followed: the overlays share
enormous amounts of code. A cross-binary deduplication pipeline (`tools/sig_image.py`, `config/dedup.us.yaml`,
`src/shared/`) found some 9,000 byte-identical function groups; **match once, share everywhere** took the fleet from 3.8%
to 54% of functions in a single phase (Phase 15, `PhaseEnd_Phase15.md`).

Then the wall. Phase 16 is a PIVOT in the record: the decompiler-and-permuter loop could not crack the loose-typed engine
core — about 3% of it. Phase 17 showed the obstacle was not signatures or types but the compiler's own code generation.
Phase 18 answered with research into the compiler's quirks and the register-pin toolkit (cookbook §17); wave close rates
went from a third to nine in ten. Phases 19–20 scaled the waves and found the next limit: **propagation** — getting a
matched body accepted by 134 translation units was harder than matching it (`PhaseEnd_Phase19.md`,
`PhaseEnd_Phase20.md`). By 06-21 the fleet stood at 58.8% of functions.

## 3. The breakthrough: reading the compiler (Phases 21–24, 2026-06-26 → 07-08)

*From `PhaseEnd_Phase21.md` … `PhaseEnd_Phase24.md`; `docs/gcc-2.7.2-map/`; cookbook §31.*

Phase 21 built the automation manager (gates, worker waves, a grinder, an orchestrator, a backlog ledger) and measured
the automated ceiling honestly; a five-scout sweep found no external shortcut. Phase 22 tried a local-model tier and
banked the tractable giants. Phase 23 is the one the project calls **THE BREAKTHROUGH**: the local 7B tier saturated the
small functions for free, and — decisively — a Fable-class agent **reading the gcc 2.7.2 source** explained the residuals
that had been called "unsteerable": which pass emitted which odd instruction and why. The result is the codegen map
(`docs/gcc-2.7.2-map/`), organised by compiler pass, and the discovery that a "reference" compiler the community used was
actually gcc 2.8.1 — the vanilla 2.7.2 source was staged instead. Phase 24 overhauled the permuter (a masked scorer, class
weights, warm restarts), built the integration-recovery tools, and matched every giant, including a 770-instruction
whale, across all 134 overlays. 66% of functions.

## 4. Families, and the instruments (Phases 25–28, 2026-07-11 → 07-16)

*From `PhaseEnd_Phase25.md` … `PhaseEnd_Phase28.md`; decision log 2026-07-08 → 2026-07-16 (the Phase-25/26/27/28
entries); timeline rows 07-11 → 07-16.*

Phase 25 built the family engine: functions that are the same shape across overlays remap mechanically once one exemplar
is cracked. It also changed how progress is measured — from 07-11 the digest carries three metrics (function count,
instruction-weighted, distinct code) because the function count, inflated ×134 by the shared engine, flattered the
work. Then the project turned its instruments on themselves. Phase 26's **tooling-integrity audit** (`decision-log`,
"2026-07-14 (session 9, A2) — The audit found the endgame plan was majority-fiction"; "2026-07-15 (session 13, A10) —
the wall re-test verdict: the broken tools WERE the walls") found that several "compiler walls" were defects in the
project's own scanners, gates and declaration tools, and that a corpus scanner had been silently skipping work. The
rules that came out of it — assert your coverage (R32), derive rather than re-parse (R33), a second disagreeing oracle
(R34), fix the instrument before trusting its measurement (R35) — reshaped every phase after. Phase 27 audited the disc
and found it held **more code than anyone had counted** (140 binaries, plus 39 modules); Phase 28 repaired more
instruments and wired the SC07 pool. On 07-22 the main executable, until then reported separately at under 1%, entered
the fleet denominators — the honest contract, adopted by the owner (`docs/roadmap-to-100.md` §1).

## 5. The family campaign (Phase 29, 2026-07-16 → 07-30)

*From `PhaseEnd_Phase29.md`; decision log 2026-07-16 → 2026-07-27.*

Twenty-five sessions and 552 commits: instruction-weighted 68.9% → 87.5%, distinct code 49.5% → 78.0%. The campaign
ran as waves of drafters over family exemplars, with the whole-binary byte gate as the referee. Its lessons are the
decision log's densest stretch: the swing number that had haunted three phases was an `-O0` compile-flag artifact
("2026-07-16 (Phase 29 Task 1)"); the permuter's problem was targeting, not a missing transform ("2026-07-21"); the
shared byte gate had compared one binary against another binary's hash for a month ("2026-07-22"); a fleet-wide type
lift landed across 154 types with the fleet still 140/140 ("2026-07-23, SESSION-14"); and the efficiency audit's verdict
that became the project's thesis for the rest of the year — **the bottleneck is integration, not idioms** ("2026-07-24,
SESSION-15"). Roadmap v2 (`docs/roadmap-to-100.md`) was adopted at the close.

## 6. Recovery and concentration (Phase 30, 2026-07-30 → 08-14)

*From `PhaseEnd_Phase30.md`; decision log 2026-08-04 → 2026-08-14; timeline rows 08-05, 08-06, 08-14.*

The overlay fleet went from 87.5% to 95.3% instruction-weighted while the denominator itself grew: the definitive disc
audit asserted a *partition* of the disc rather than extending a list ("2026-08-05 (P30 S6/S41)"), and 73 more
code-bearing payloads were onboarded **without an emulator**, their load addresses derived statically from their own
bytes ("2026-08-06 (P30 S44/S45)") — 213 byte-identical binaries by the close. The way work got done changed: the
zero-token mechanical pipeline (auto-drafts, symbol fixes, pre-checks, a lane gate) banked most of the remaining
functions with no agent at all; open stubs fell from 28,296 to 12,059. The one function that refused, `func_8017C294`,
got a mechanism-complete wall dossier instead of another wave ("2026-08-14 (P30 S50-Max)").

## 7. The atlas, the lanes, and the last twenty-one (Phase 31, 2026-08-14 → 09-05)

*From `PhaseEnd_Phase31.md` (and its 8,700-line log, `phase-ends/logs/Phase31.md`); decision log 2026-08-14 →
2026-09-04 (S59–S78); timeline rows 08-14 → 09-05.*

The longest phase: thirty sessions, about 1,660 commits, stubs 12,059 → 21, the fleet to 100.0% instruction-weighted,
the main executable from 1,041 open functions to 12. It was re-chartered at its first gate around a **frontier atlas** —
a per-function feature layer and similarity groups over every open stub, each labelled with the lever it would need —
then run in three shapes: orchestrated waves of six thousand instructions each, **autonomous lanes** (drafter, gater,
maintenance, stall-guard) under a two-workflow budget that banked while nobody watched, and finally a hand-run
completion sprint once the census fit on one page. Its defining discovery is recorded under the heading "EVERY WALL
EXAMINED WAS THE INSTRUMENT" ("S76 (2026-09-03)"): a band of the main executable labelled compiler walls turned out to
be Sony's controller library — the exact February-1998 version was found on the internet and linked in, twelve "walls"
at once ("S78 (2026-09-04)"); a wall was a mislabelled symbol boundary; the permuter had silently never run on a whole
class of drafts; one "finished" function was the original assembly pasted back in — the verbatim class, censused from
the archive tables and reduced to the five genuine hand-written routines. Each repair got a control and a rule.

## 8. The frontier emptied (Phase 32, 2026-09-05 → 09-06)

*From `PhaseEnd_Phase32.md`; decision log P32 S81 → S85; cookbook §501-Q/§501-R.*

Twenty-one functions and five disc files nobody had seen the game load. The five were real code modules, placed from
their own bytes (fleet 213 → 218; disc unclaimed 0 of 220) and adding 33 functions to the list. A one-agent-per-function
pass banked 39; then, on the owner's directive that nothing but Sony's code and the original hand-written assembly may
remain untranslated, the last fifteen: eleven by a Fable pass reading compiler dumps against the gcc source, four by
hand. Two of those four carried formal *proofs* that they could not be matched. Both proofs were right about the
mechanism and wrong about the list — each named every way the compiler could produce the odd byte, and each list was one
producer short (combine's self-update bookkeeping gap, §501-Q; loop.c's user-variable rule with cse's later-mention
canonicalization, §501-R). Five-line reproducers found the missing behaviours in minutes; the last two functions then
matched with no register pins at all. On 2026-09-06 the census read **0 stubs**: every game-code function in all 218
binaries is C, 218/218 byte-identical from a clean rebuild.

## 9. Making it public (Phase 33, 2026-09-06 →)

*From `phase-ends/CURRENT_PHASE.md` (Phase 33), `docs/public-flip-runbook.md`, decision log "P33 S86" and "P33 S87".*

What remained was not matching. The contract was proven once more as one recorded run
([`docs/verification.md`](verification.md)); the build was made a stranger's build (a bootstrap script, disc
extraction verified against the manifest, the optional Sony SDK user-supplied and checksummed, a fresh-clone proof of
218/218 with no SDK); the reverse-engineering database was made regenerable from text; CI was written to keep the tree
ROM-free and compiling. Then the history: the repository had carried game-derived files while private, so its entire
history was rewritten in place — every commit, date and message preserved, the purged paths removed from every
revision, old hashes in historical documents replaced by inert tokens and mapped back at the tip
([`docs/commit-map.tsv`](commit-map.tsv)) — rehearsed twice on a scratch copy (the rehearsal caught two defects that
would have corrupted history), proven pair by pair, and force-pushed. This document, the retrospective, the wiki and the
tooling releases are the last block; the visibility flip waits for GitHub to purge the old objects.

## 10. After 100 %: making the code say what it means (Gen3 — Phases 35, 36, 37, 2026-09-08 →)

*From `PhaseEnd_Phase35.md`, `PhaseEnd_Phase36.md`, `phase-ends/CURRENT_PHASE.md` (Phase 37), decision log "P35", "P36 S99/S101/S104/S105",
"P37 S106", `docs/levers.md`, `docs/readability.md`. This chapter is advanced at the end of every session (the owner's rule, 2026-09-12); the
numbers are the two Gen3 series'.*

A hundred percent is a byte statement, not a code statement. The tree that rebuilt 218 binaries byte for byte was still the tree a machine had
drafted at speed: every shared engine function lived as a macro instantiated per level, tens of thousands of register pins and inline-asm
hints forced the compiler where a reading would have found the source shape, half a million memory accesses were raw pointer casts where the
original had structures, and almost every function was still called `func_80xxxxxx`. The owner set the order of the third generation on
2026-09-08 — dedup, then pins, then structs, then names, one phase each — with the standard read from sotn-decomp's style guide as data: a
human maintainer's code, names only with evidence, fakes marked, nothing forced silently ([`docs/gen3-standards.md`](gen3-standards.md)).

**Phase 35 (three sessions, 2026-09-08) made the code say each thing once.** The 3,516 macro bodies became 3,175 plain-C headers included at each
site — sotn's own shape, read from its tree after a remembered precedent had said the opposite (decision log "P35"); the five identical-payload
overlay twins were folded onto one source directory each; the same-address duplicate backlog fell from 4,755 copies to 160, each remainder
ledgered with the compiler's diagnostic; and the invariant "one source per unique function" became a health-chain gate with a second,
disagreeing oracle — which found 38 functions whose bytes vary per overlay through the declaration environment, a tier the first oracle could
never have seen. One session died at 91 % context without a checkpoint and the next rebuilt its state from the transcript; the tool that did
the sharing was caught making four kinds of mistake by its own gates.

**Phase 36 (nine sessions, 2026-09-09 → 09-11) took the levers off.** A self-asserting census counted 53,234 compiler-forcing sites — 37,720
register pins and 15,514 asm statements — in 15,679 matched bodies, and found on the way 44 whole-body assembly routines hiding inside C shells
that the file-scope detector had never seen. The removal was a ladder: a byte oracle on the build's own recipes; a mechanical strip that took
37 % of the sites with no understanding at all (they had never been load-bearing — a single compile at bank time would have refused them);
one header for 9,102 per-unit GTE macro definitions; recipes; a permuter rung that could replicate a known shape 134 times but discover none;
an object-scored guided search; and then some two hundred agent readings of gcc 2.7.2's own source, one agent per class and later one per
translation unit, closing 56 of 56 in the last session. The biggest single class turned out not to be codegen at all: 16,759 call declarations
that lied about their callee's arity, deleting an instruction the pin then faked, repaired free in an afternoon. The phase stopped at 4,010
sites (−92.5 %), every survivor marked with the compiler pass that needs it and the instrument that judged it, because the last third of the
residue was signatures, struct types, carved data and one GTE spelling — the next phase's material — and the owner amended the milestone from
"zero" to "every survivor named for the structs phase". The doctrine it left for the next project's first day: *ban the silence, not the
lever* ([`docs/levers.md`](levers.md) §5).

**Phase 37 (open, 2026-09-11 →) is the structs phase**, and its first day changed what the charter believed. The handoff had carried Phase 17's
verdict — types are a comprehension lever, struct-ification is byte-neutral — for two months while the tree's own compiler map said the
opposite: in gcc 2.7.2 a struct member access carries a flag the scheduler and the common-subexpression pass read, and a cast on a pointer sum
does not, so spelling a cast as a member can move instructions. The plan was built on that fact (every struct edit gated like a match), the
owner chose the strictest stop rule again — grind the casts, the lying declarations and the levers to zero, each zero defined so it is
honest — and the first two tasks measured the ground: a type census with a coverage assertion (503,016 raw dereferences in four forms, not
the 411,850 one regex saw; 7,255 struct definitions, 6,000 of them hidden inside single files; the lever finish line 10,700 once inline GTE
statements are counted), a struct map clustering every cast into the 18,760 types the code needs, and a byte probe that priced the campaign:
rewriting casts as members leaves 91 % of functions untouched, a per-site fallback closes the rest keeping 27 casts in 716, and the
definition's own signature is a free declaration in 93 % of cases with no surprises. The layout engine agrees with the real compiler on
5,283 definitions. The engine that does this at fleet scale is the next task.

## 11. By the numbers

| | |
|---|---|
| Duration | 2026-06-10 → 2026-09-07: 12 weeks; 33 phases (+ a spike and an inserted audit half-phase); 32 PhaseEnds; ~87 sessions |
| Commits | ≈4,040 on `main` (78 distinct days) |
| Binaries byte-identical | 218 / 218 — the EXE, the resident engine, 138 location overlays, 78 code modules |
| Functions | 363,214 / 363,214 byte-identical; 360,737 in C (255,632 of them shared bodies via 2,220 dedup groups); 1,256 Sony library functions linked; 5 hand-written-assembly bodies kept verbatim; 0 stubs |
| Instructions | 13,492,113 / 13,492,113 (100.0%); distinct code 5,820,205 / 5,820,205; main game code 45,150 / 45,150 |
| Knowledge base | the matching cookbook (§1–§501 and sub-sections, 3.5 MB), the gcc-2.7.2 codegen map, 79 decision-log entries, 73 numbered rules (+ the constitution's 25) |
| Tooling | ≈235 Python tools, 25 shell tools, 12 Ghidra scripts — the extractor, the byte gate, the dedup engine, the family engine, the atlas, the lanes, the rewrite package |
| **After 100 % (Gen3, snapshot 2026-09-12)** | dedup: 0 macro bodies, 3,175 shared headers, one source per unique function (P35) · levers: 53,234 → 4,010 marked sites, +6,717 inline GTE statements counted from P37 (`docs/levers.md`) · struct debt: 503,016 raw dereferences in 69,497 functions, 7,255 struct definitions over 527 layouts, 98,648 lying declarations (`docs/readability.md`) · the chart's lower panel |

*Every number above is generated or counted from the repository; the timeline behind the chart is
[`docs/story-timeline.md`](story-timeline.md).*
