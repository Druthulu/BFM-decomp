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

## 10. After 100 %: making the code say what it means (Gen3 — Phases 35, 36, 37, 38, 39, 2026-09-08 →)

*From `PhaseEnd_Phase35.md`, `PhaseEnd_Phase36.md`, `PhaseEnd_Phase37.md` and its log (`phase-ends/logs/Phase37.md`), decision log "P35",
"P36 S99/S101/S104/S105", "P37 S106", `docs/levers.md`, `docs/readability.md`; for the migration and Phase 38, the Phase 38 plan's change
lines, its task summaries (T1, T5, T5.1, T6, T7) and logs, and git; for Phase 39, the Phase 39 plan's change lines and its task summaries
(T1–T11, with T7.1). This chapter was advanced at the end of every session (the owner's rule,
2026-09-12) until the migration of 2026-09-29 dropped that duty; since 2026-09-30 it is advanced by every phase's closing work (rule R121).
The numbers are the two Gen3 series'.*

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

The second day (2026-09-12) built that engine — and spent its first hour on an instrument that read the opposite of the truth. The
byte oracle needed a second mode: a correct global-block edit can differ in the object while the linked binary is identical, because only
the *spelling* of a relocation moved (`D_801F8872` versus `D_801F8870` plus two). Rather than re-implement the linker's arithmetic, the
new mode runs the build's own linker on the candidate object against a snapshot of every other object and compares the same hash the gate
compares — ten milliseconds, nothing of the linker's rules re-typed. Its known-true control then reported the two objects *identical*, which
would have meant the previous day's finding was false. It was the snapshot: a control on the previous day had built the binary with the
candidate in place, leaving a linked-identical but differently spelled object in the build directory, and the snapshot refresh had copied it
into the oracle. A clean fleet run, and a refresh that now refuses any object it cannot reproduce from an untouched compile, put the control
where the bytes said. The engine itself — struct spelling on every typed base of a function, the per-site fallback, the levers tried again on
the struct-spelled text, a recipe registry seeded with the three shapes the record had already proved, the declaration solver, the definition
folds — passed a fixture of forty-eight checks against a stub oracle and five against the real one, reproduced the exemplar of the previous
day (one cast kept; a recipe then closed it), took six compiler hints off a function whose struct was already right, and ran its first real
batch: the declarations of one overlay's twenty-seven files, 258 units, 242 made honest, eight marked as the original's own calling
convention, sixteen kept with their reason written down — twice through the 218-binary gate, green both times. It also found, in passing,
that a 78-megabyte ledger from the previous phase had been sitting in the public repository above GitHub's size warning for a day.

The afternoon ran the declaration layer over the whole tree, unattended, in batches of three hundred files, each followed by the
218-binary gate and a commit: seventeen thousand function declarations made to say what their definitions say, thirteen hundred call sites
recognised as the original's own calling convention and marked as such, two hundred data aliases given their real names. Then a batch came
back empty, and the reason was a class nobody had modelled: a hundred and forty-nine functions whose bodies had been *defined* under an alias
name — `aF8012EFB8` bound by an assembler label to `func_8012EFB8` — because the fleet's declarations of the real name had lied about them
and the alias had been the drafter's way around the conflict. Their three and a half thousand callers had been invisible to the census that
counts lying declarations, because it looked for a definition under the real name and found none. Putting each function back under its
name turned out to need a small ladder of its own, learned one failure at a time across five passes: the exact prototype, the promoted one, a
bare `()`, a caller left untouched because its lie is load-bearing, the definition itself spelled in the old K&R style when callers pass more
arguments than its body declares, and a shared header's declaration lifted into the files that include it when the header reaches binaries
where that address is a different function. A hundred and twenty landed; twenty-nine were named and left, most of them because a carved
translation unit holds callers that disagree with the definition inside one file — the original was several files, and only the file-layout
phase can say so.

The next day the declaration layer went to its floor, and the story of that day is the story of five things the instruments could not
see. The morning's first batch drew three hundred files and found nothing to do; the reason was not the code but the engine's index,
which had never looked inside the shared bodies a neighbouring file includes — and since the dedup phase every shared function lives in
exactly such a body, so every level's own shared functions had read as foreign. One loop fixed it, and the next batch alone put ten
thousand declarations right. Then the census itself turned out to be counting wrong: it identified a function by its bare name, and the
game has more than six thousand names that stand for two or three different functions in different levels, so nearly three thousand
correct declarations had been counted as lies. Then a regular expression anchored at the start of a line had missed every function
definition that happened to be indented, and repairing it revealed ten thousand more declarations nobody had known were wrong. Each time,
the number fell by thousands without a new idea, only a repaired instrument: ninety-eight thousand lying declarations at the phase's start,
two thousand one hundred at the day's end, with five thousand more counted apart as the original's own calling convention — a caller
passing fewer arguments than the function takes, proven on the bytes and marked in place — and four hundred as cross-binary calls the
fleet cannot agree about.

The parked signature changes from the levers phase landed the same day, and each taught something. The function whose pins had faked a
missing argument in a hundred and thirty-two levels was one body over per-level data; renaming its data symbol to each level's own, by
order of appearance, closed all of them in one judged unit and took two hundred and sixty-four pins off the count. Another needed its three
zero-argument callers rewritten in the same unit as its definition — the pin had been the argument all along, and where the caller had
compared a value before the call, spelling that value as a local put it exactly where the pin had forced it, in the first argument
register. A third needed nothing but its return type: a function that falls off the end, declared to return an integer, keeps the
compiler from stealing an instruction into a branch's delay slot. The levers count fell from four thousand and ten to three thousand seven
hundred and thirty. One mistake of the day was mine: a restore run against a judge that had not yet finished stopping, which split a
batch's bookkeeping — erased cleanly, and the rule written down: wait for the exit.

That night the declaration layer was called at its floor and the phase's fourth task closed: about 107,000 declarations made to say
what their definitions say, 1,796 lying declarations left over 76 callees (98,648 over 1,609 at the phase's start), 5,262 call sites
counted apart as the original's own calling convention and 418 as cross-binary calls, 133 of 149 alias-defined functions back under
their names, ten of twelve parked signatures landed, and the levers at 3,730. Of the 1,796, 1,537 were judged a floor only the types
could lower: a declaration cannot name a type its file cannot see. The checkpoint said the next task — one definition per struct type —
would open in a fresh session. It did not open for seventeen days. The record says only that the phase sat at that boundary with a clean
tree; it does not say why. On 2026-09-29 the owner re-scoped Phase 37 to the work already done (its tasks T0–T4) and carried the six
unstarted tasks to the next phase word for word, so that the repository could change its working method between phases rather than in
the middle of one. Phase 37 closed as v2.3.0 with the 218-binary gate green, and no tag.

**The migration (2026-09-29, recorded as Phase 37.5).** The new method, Project Architect 3.0, replaced the long session-start reading with
a written plan per phase, tasks that each run in a fresh context and end in a log and a short summary, and a one-page card of standing
facts. One commit of 777 files installed it and moved the old operating documents — the setup reference, the 3.5-megabyte matching
cookbook and its index, the effort map — into `docs/retired/`, where nothing loads them. Four things broke, and each was found only when
something used it. The project's own tools still read the retired documents: the health chain's tool census took its tool table from the
old setup file, a link checker and the wiki renderer pointed at it, and 36 links in the wiki, the README and the how-to pages led nowhere;
the next phase's first task found four red health items with this one cause and repaired them as one defect. The new launcher, which
sorts the closing reports by phase number, crashed: the half-phase from the first week is filed as `3_5`, with an underscore, beside
`33.5` and `37.5` with dots, and the sort ended up comparing a number with a string. The migration had normalised none of the ids; the
router could not build its starting state after the next plan was approved, and the fix — a sort that splits every id the same way — was
made outside the task loop and reported upstream. The migration's ignore file gained a bare `.run/` line, which overrides the older lines
that let chosen per-phase evidence under `.run/` be committed; from then on a census snapshot could be committed only by forcing it
(the next phase met this as a commit helper's refusal). And the duty to advance this chapter and the retrospective at the end of every
session had lived in the old method's memory and checkpoint routine; the migration carried it nowhere, and the next phase ran to its
milestone with neither document touched. It came back the day after as rule R121, which hands it to every phase's closing work; this
part of the chapter was written under it.

**Phase 38 (2026-09-29 → 09-30) took up the carried task: one canonical definition per struct type.** Its first task repaired the
migration (above), proved the gate green, re-took the byte oracle's baseline and measured the ground: 7,255 struct definitions — 1,179
in the canonical header, 4,085 at file scope in `.c` files, 1,904 inside functions, 87 in other headers — in 206 classes of duplicates
over 2,823 names, 40 "variant camps" (one name, several layouts), 141 canonical names nothing used, 26 legacy padding names, and the
1,796 lying declarations. The second built the instrument the milestone would be read by, a `--check-structs` mode of the census, and
its known-true case was that the starting tree fails with exactly those counts; it did, adding 1,106 declarations the engine had kept
because a type was not visible. The third and fourth designed the three largest types — the entity, a 0x10C-byte block and the player
block — into a new canonical header and folded their local copies onto it, every batch judged on the bytes.

The fifth task, the long tail, did the mechanical part in one night — 1,308 types lifted into the canonical header, the padding names to
0, the 40 variant camps to 0 by renaming each divergent local copy, 314 dead definitions deleted — and then stopped and asked, because
three of the gate's counts could not reach zero without breaking the plan's own words. The duplicate count included every opaque layout
twin: two placeholder-named structs with the same shape and no evidence that they are the same thing. Reaching 0 would have meant
folding, for one example, 293 opaque eight-byte structs into one — "one name per layout", which the project's naming law forbids — while
the same task said such twins stay apart and are listed. The outside-the-canonical-files count included 1,774 structs declared together
with a variable inside one function (a stack frame, local by nature), and the lifting tool could reach only one kind of file scope. The
dead-name count ignored uses inside the canonical header itself, so 114 of its 134 "dead" names were members of live types; deleting one
single-letter type had broken a level. The census defined the milestone's zero as impossible, and the plan had asked for it anyway: the
second task's known-true case had proved that the gate fails on the starting tree, and no one had asked whether it could pass on the
intended one.

The question went to the plan's critic, which reopened the task as T5.1 with the gate reading fixed, and the owner set that reading on
09-30: a duplicate class still counts if its names are meaningful, or if it is a placeholder class not listed in a new record,
`docs/struct-twins.md`, with per-class evidence from the struct map; a stack frame declared with its variable is reported, not counted;
a canonical type used only inside another canonical type is alive. The milestone's own line stayed as written. The reasoning between the
question and the answer was spoken rather than written: the plan keeps the decision as one change line, the fifth task's log keeps the
conflict, and the discussion record opened that day is an empty template. What is said here is what those support.

T5.1 took two attempts (the first handed off without leaving its progress file on disk) and ten coder runs, one of them red and
reverted, and three things that had looked right failed on the way. The census counted a struct's tag and its typedef as two names,
because C keeps them in two namespaces; the fifth task had split nine such pairs to satisfy it, and T5.1 taught the census that one
definition's tag and typedef are one name. The layout hash that defines "the same layout" ignored alignment attributes, and the gate
said so twice: folding a class whose members differed only by `packed` or `aligned` turned 142 of the 218 binaries red, and folding a
packed four-byte struct onto its natural twin turned 148 red; the hash now carries those attributes, and two definitions that differ only
in them are different types. And a fold by layout alone was not safe even then: a member name the canonical type spells at another
offset compiles without a word from the compiler and reads the wrong field — a trial fold of that kind failed 142 binaries, and only the
byte gate saw it. At the close every definition outside the canonical files had moved in (1,684 to 0), every meaningful-name class was
folded, 942 placeholder names whose uses showed them to be one type were folded, and 53 placeholder classes were listed — 44 with
evidence that they are separate, 9 with no use-site evidence either way, among them the shapes of Sony's `RECT`, `SVECTOR` and `DVECTOR`.
Six layouts took Sony's own SDK names, three unused names were kept with their reason, and the 0x10C block's split was confirmed, with no
unions.

The sixth task put the declarations on the canonical types: nine redraw cycles, each through the gate, took the 1,106 hidden-type
declarations to 0 and the "conflicting types" from 160 to 18 — all 18 stale rows of the engine's ledger whose source is already right,
because the engine writes no new row for a unit it finds nothing to fix in. The shared-body conflicts went from 44 (the plan's 45 had
counted a header line) to 40, each with its diagnostic. The seventh ran the gate on a fresh census on 09-30: exit 0, and 218 of 218
binaries identical. From the phase's start to its end, struct definitions went from 7,255 to 1,650; duplicate classes from 206 to 53, all
of them listed twins; file-scope definitions in `.c` files from 4,085 to 0; variant camps from 40 to 0; dead canonical names from 141 to 0
(three kept with their cause); legacy padding names from 26 to 0; hidden-type declarations from about 1,106 to 0. Lying declarations fell
from 1,796 over 76 callees to 229 over 24 — the census's `decls.lying` field at both ends, which the new gate prints as
`types_floor_lying`; it is not the 98,648-to-1,796 series quoted above for Phase 37, nor the plan's 1,537 "types floor", and it is a
different count from the hidden-type declarations, which are read from the engine's ledger. The levers stayed at 3,730: the phase moved no
compiler pins, and none was asked of it.

**Phase 39 (2026-10-01 → 10-03), the cast campaign.** With one definition per struct type in place, the phase took up the casts. A *raw
cast dereference* is a place where the code reads or writes memory through a pointer cast — `*(T *)(p + k)` — where the original
almost certainly wrote a field of a structure. The census counts four forms: P, pointer arithmetic on a base (`*(T *)(base + k)`); I, a
cast on a bare name (`*(T *)name`); X, an indexed cast (`((T *)e)[i]`); and M, the decompiler's own `M2C_FIELD(` macro. The first task
counted 502,983 of them in 69,492 functions — P 408,974, I 60,666, X 13,800, M 19,543 — repaired a red health item it found on the
first day (a harness tool missing from the tool dictionary), and retired the 18 stale "conflicting types" rows the previous phase had left.
The second built the gate. Because in gcc 2.7.2 the spelling of a struct access is a per-access byte dial, some casts must stay; a *kept
cast* is now one the bytes need, spelled by one of five registered macros in `include/common.h` — `CAST_WIDTH`, `CAST_SIGN`, `CAST_ALIAS`,
`CAST_MISALIGNED`, `CAST_NONSTRUCT`, each proven on the bytes — and backed by a ledger row that names its cause. That pairing was written
down as binding: a kept cast is a registered macro plus a ledger row, never a bare cast.

The third task ran the struct-spelling rung over the overlays: three expert attempts, two of them handed off, about eight coder runs and 61
batches, each through the 218-binary gate. Overlay P casts went from 387,001 to 238,399 (−148,602, all now member accesses), 20,390 sites
took a kept-cast macro, and 34,131 bodies the engine could not redraw were written into the restructuring ledger with their cause. One
cause grew to dominate: TYPE-NOT-CANONICAL, a base whose type the struct map knows but for which no canonical definition exists, so there
is no member to spell. It covered 234,400 of the overlay sites. On the way one fan-out added seventeen fields to a single header type, and
one coder's hand-back was lost with the attempt that had spawned it.

The fourth task met the wall the third had shown. Its done-when asked for P and X raw at zero across the fleet, apart from non-struct
bases, and the residue was overwhelmingly TYPE-NOT-CANONICAL: the struct map names 18,526 types and 1,650 are defined. The critic sent the
question to the owner, who chose on 2026-10-02 what the plan now calls *reading A*: a raw site may stay if the ledger records, for that
site, why — it is *residue*, and the ledger entry is its receipt. The gate became "no uncovered residue" rather than "no raw casts"; the
literal zero, *reading B*, was deferred to a later phase. This was the failure the Phase 38 close had written down — test each milestone
count against its instrument on the planning tree, in both directions — met again in the next plan. A new task, T10, made the coverage
check honest. The old check called a function covered if it had *any* ledger row; matching site by site exposed 14,296 uncovered overlay
sites in 4,234 functions (plus 281 in code modules and 3 in the executable), all closed with ledger-only rows. It also sized the wall:
281,252 TYPE-NOT-CANONICAL sites over 13,081 map types, half of them on 81 types, 80 % on 579, 95 % on 4,384. Many of the top types recur
in 123 to 131 functions, which suggests — an inference, not yet checked — one overlay struct copied into each overlay family under a
hash name, so the next phase should look for twins before defining each one.

The fifth task took the I and M forms by a recipe ladder that turns globals into typed externs, mostly `extern T X[]`, and its yield was
low: about 1,676 sites drawn against about 48,000 left as residue, the biggest refusals being a global with no scalar extern to give it
(18,945) and a width the extern could not carry (10,186). Its first expert handed off with a detached batch cycle still running, and the
next coder refused to race that orphan rather than kill it. Mid-phase the owner added a rule: every task that moves the census also
records a readability snapshot, the timeline and the README in its own commit. The catch-up task (T11) found that the batch script had
been refreshing the wrong census directory, so the readability series had refused its snapshot on every batch of the phase without
anyone seeing; the closing task repaired the script.

The sixth task took the *lying declarations* — call declarations that do not match their callee's definition, by an empty K&R list or a
narrower type — from 229 over 24 callees to 11 over 3, and wrote all 11 into the ledger (four rows). Seventeen of the 24 callees had been
invisible to the planner for the same reason Phase 37 met: they are defined under `aF<address>` assembler-label aliases and the plan had
keyed them by their real names. The eleven that remain are facts of the source: callers that use the result of a call with no arguments,
where a prototype would not compile, and one object whose prototype differs.

The seventh task met the same planning failure a second time. It asked for "direct GTE statements = 0" — GTE is the PlayStation's
geometry coprocessor, whose instructions the code writes as inline assembly — and the lever census, as the plan read it, counted calls of
the header's own GTE macros as direct, so zero would have meant no GTE in any function at all, against the same task's aim of one spelling
in the header. The critic reopened it as T7.1 with the predicate the census's own documentation defines (direct means not through a
`gte_inline.h` macro), leaving the milestone's words unchanged. Read that way the count went from 492 to 0 (477 inline, 15 through
per-file macros); per-file GTE macro definitions went from 150 to 0; the header grew from 51 to 82 definitions, 68 canonical, 11 variants
that differ only in what they declare clobbered — a scheduling steer, marked `// !FAKE:` — and 2 aliases. (Counted the unfiltered way,
"direct" had been 6,733.) The eighth task tried to take the *levers* off again — a lever is a register pin or an asm statement that forces
the compiler to match, marked `// !FAKE:` — over every function the phase had touched. GTE levers went from 434 to 91 and asm statements
from 1,409 to 1,405; not one of the 1,868 register pins came off, because the byte oracle judged every one needed. One pass regressed 343
GTE statements back to inline assembly and was consolidated again. What remains is now a ledger of causes, `config/lever_residue.tsv`,
2,433 rows over 3,528 sites — a head class of 1,066, 589 singletons with no shared lever, 548 missing parameters, 157 asm macro
definitions, 60 GTE clobber steers, 13 whole-body asm routines — with 70 rows flagged for an agent in the next phase. The levers count
(register pins plus asm statements) went from 3,730 to 3,364.

The milestone ran on 3a9377c926 under reading A and was green. From the Phase 37 baseline to the close, raw casts went from 503,016 to
336,219: P 409,007 → 257,470, I 60,666 → 49,831, X 13,800 → 13,790, M 19,543 → 15,128, with no uncovered site in any form. The X form
barely moved because its indexed sites sit on bases with no canonical type. Kept casts number 20,963, every one backed — CAST_WIDTH 10,410,
CAST_SIGN 8,429, CAST_ALIAS 1,173, CAST_MISALIGNED 624, CAST_NONSTRUCT 327. The covered residue is led by TYPE-NOT-CANONICAL at 291,819
sites, then the I/M extern refusals (18,945 and 10,186). Seven P sites respelled after T10 came up uncovered at the gate and were closed
with ledger-only rows. Struct definitions stayed at 1,650, and all 218 binaries stayed identical through every batch. Two marks on the
record: one commit (3f547f1152) took in about 794,000 lines of census scratch, removed from tracking by the next but kept by history; and
the gate's census and the series' census still disagree by about five P sites (257,470 against 257,475), not investigated. What the
phase leaves for the next is plain from its residue: the casts that remain are a definitions problem, not a spelling problem.

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
| **After 100 % (Gen3, snapshot at the P39 close)** | dedup: 0 macro bodies, 3,175 shared headers, one source per unique function (P35) · levers: 53,234 at the P36 start → 3,730 at the P38 close → 3,364 (1,868 register pins + 1,496 asm statements), every survivor in `config/lever_residue.tsv` (2,433 rows over 3,528 sites; `docs/levers.md`) · raw cast dereferences per form, P37 baseline → P39 close: P 409,007 → 257,470, I 60,666 → 49,831, X 13,800 → 13,790, M 19,543 → 15,128 (503,016 → 336,219), every remaining site ledgered with its cause, 291,819 of them TYPE-NOT-CANONICAL (0 uncovered) · 20,963 kept casts in five registered macros, all backed · lying declarations 229 over 24 callees → 11 over 3, all ledgered · 1,650 struct definitions (7,255 at the P38 start; 53 duplicate classes listed in `docs/struct-twins.md` at the P38 close) · the chart's lower panel |

*Every number above is generated or counted from the repository; the timeline behind the chart is
[`docs/story-timeline.md`](story-timeline.md).*
