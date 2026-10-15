<!-- R1 | H1 relaxed while private | | retired | gen3.2: superseded by G12, repo public since 2026-09-08; text rules/gen3.2/R1.md -->
<!-- R2 | All-in-WSL (H2 restatement) | | active | | -->
<!-- R3 | All tooling under `tools/` | | active | | -->
<!-- R4 | Plan mode every phase | | active | | -->
<!-- R5 | No `Co-Authored-By` trailer on commits | | active | | -->
<!-- R6 | Git workflow = Claude commits in WSL, Drew pushes | | active | | -->
<!-- R7 | Effort-map check | | retired | gen3.2: effort toggles retired in PA 3.2; text rules/gen3.2/R7.md -->
<!-- R10 | Multi-datapoint live-RAM verification | | active | | -->
<!-- R12 | No `/tmp`; project-local data only | | active | | -->
<!-- R13 | Proto-provenance & confidence tagging | | active | | -->
<!-- R15 | `config/symbols.us.txt` is the curated, build-valid symbol source | | active | | -->
<!-- R16 | The matching automation flywheel | | active | | -->
<!-- R20 | Private-repo backup policy | | active | | -->
<!-- R23 | Stop the Ghidra MCP before any phase-end/RE-checkpoint commit; commit the DB only if RE work changed it | | active | | -->
<!-- R24 | Per-binary compiler/SDK provenance | | active | | -->
<!-- R27 | Effort-transition discipline | | retired | gen3.2: effort toggles retired in PA 3.2; text rules/gen3.2/R27.md -->
<!-- R32 | Assert your COVERAGE | | active | | -->
<!-- R33 | Derive, don't re-derive | | active | | -->
<!-- R35 | Fix the measuring instrument before trusting its measurement; a probe from a broken tool is not evidence | | active | | -->
<!-- R37 | Probe before costing | | active | | -->
<!-- R41 | Every cost/rate/yield/effort number ships with its denominator | | active | | -->
<!-- R43 | A tool must refuse an input it cannot handle, never process it wrongly | | active | | -->
<!-- R44 | A card may not name a lever the knowledge base does not contain | | active | | -->
<!-- R45 | Draw-time bankability: never draw a card the pipeline cannot bank | | active | | -->
<!-- R46 | A budget is part of the harness, not a constant | | active | | -->
<!-- R54 | A guard downstream of the failure is not a guard, and a guard that is not running is not a guard | | active | | -->
<!-- R57 | An instrument's own write path is part of the instrument | | active | | -->
<!-- R59 | A blanket commit of another lane's mid-gate tree is a race, not a backup | | active | | -->
<!-- R63 | A permuter/waypoint score is not a closeness until its diff is read | | active | | -->
<!-- R70 | A ledger's tie-break is part of the instrument | | active | | -->
<!-- R76 | Rehearse every irreversible repository operation on a scratch copy and prove it pair by pair with POSITIVE assertions | | active | | -->
<!-- R77 | A linked worktree's HEAD is a ref — audit `git worktree list` before any gc or purge | | active | | -->
<!-- R78 | R20 amendment: the text export + checksums + the archive repository are the backup; never `git clean -x` | | active | | -->
<!-- R79 | `pkill -f` never with a literal the calling shell's own command line contains | | active | | -->
<!-- R80 | A checker that widens its document set must classify a missing promised page as PENDING, never BROKEN | | active | | -->
<!-- R84 | An ignore file's directory-form rule is a wall no later block can climb — write the by-contents form first | | active | | -->
<!-- R85 | A check compares two DERIVED figures; a typed figure in a verify line is wrong the day the derived side moves | | active | | -->
<!-- R86 | A dry-run judge is an instrument — negative-control it against a known-PASS run before believing a FAIL | | active | | -->
<!-- R87 | A tool ships with its dictionary row, or the health check fails | | active | | -->
<!-- R88 | Re-run `doc_links --strict` after ANY untrack or archive move, not only after a docs edit | | active | | -->
<!-- R89 | An unattended installer's manifest is specified as a derivable SET | | active | | -->
<!-- R90 | A governance system that keeps transcripts in the repository needs the firewall's class-7 line | | active | | -->
<!-- R91 | A foreign project's path is named in prose, never as a backticked `docs/…` citation | | active | | -->
<!-- R92 | A distillation ships with a coverage check against the populations it claims to distil | | active | | -->
<!-- R93 | The worklogs get one final read at the end of the project, with an "already banked?" grep per candidate | | active | | -->
<!-- R94 | A snapshot instrument never `.strip()`s a porcelain listing | | active | | -->
<!-- R112 | A gate's baseline is a snapshot, not the build directory — a clean rebuild never runs where a live scorer reads `build/` | | active | | -->
<!-- R113 | A lever's marker names its PASS and its INSTRUMENT** (R65 for markers), **asserted by an attribution check at the close | | active | | -->
<!-- R114 | A ledger's "done" is per body (unit, function, after-hash), never by text alone | | active | | -->
<!-- R117 | A "stalling?" question is answered with the residue bucketed by what each bucket needs before any plan is proposed | | active | | -->
<!-- R102 | A tool that restores files restores from its own snapshot, never `git checkout` on a tree it did not commit | | active | | -->
<!-- R103 | A failure-cause extractor is negative-controlled against the compiler's real message forms, not against the word "error" | | active | | -->
<!-- R106 | A policy taken on a remembered precedent is a belief — read the target project's tree | | active | | -->
<!-- R97 | "Green" is read from a check's EXIT CODE, never from its last line; every chain sets `pipefail` | | active | | -->
<!-- G1 | Two oracles; guess neither | | active | | | source: decomp-architect -->
<!-- G2 | Oracle precondition | | active | | | source: decomp-architect -->
<!-- G3 | A match is byte-for-byte, and the whole binary still hashes | | active | | | source: decomp-architect -->
<!-- G4 | No unmatched C in a default build | | active | | | source: decomp-architect -->
<!-- G5 | Address provenance and region tags | | active | | | source: decomp-architect -->
<!-- G6 | Never rename blind | | active | | | source: decomp-architect -->
<!-- G7 | Duplicates first | | active | | | source: decomp-architect -->
<!-- G8 | Compiler honesty | | active | | | source: decomp-architect -->
<!-- G9 | Decisive verification is a clean rebuild | | active | | | source: decomp-architect -->
<!-- G10 | A standalone match is not a bank | | active | | | source: decomp-architect -->
<!-- G11 | Pasted assembly is a verbatim, not a bank | | active | | | source: decomp-architect -->
<!-- G12 | No game-derived bytes in any tracked or published artifact, from the first commit | | active | | | source: decomp-architect -->
<!-- G13 | The audit derives its forbidden set and asserts its own coverage | | active | | | source: decomp-architect -->
<!-- G14 | Rehearse every irreversible repository operation | | active | | | source: decomp-architect -->
<!-- G15 | A linked worktree's HEAD is a ref | | active | | | source: decomp-architect -->
<!-- G16 | A probe or guard never writes into the repository it guards | | active | | | source: decomp-architect -->
<!-- G17 | A rewritten history is not private until the host has purged the objects | | active | | | source: decomp-architect -->
<!-- G18 | Never `git clean -x` where irreplaceable data is ignored-but-present | | active | | | source: decomp-architect -->
<!-- G19 | Assert your coverage | | active | | | source: decomp-architect -->
<!-- G20 | Derive, don't re-derive | | active | | | source: decomp-architect -->
<!-- G21 | A second, DISAGREEING oracle — on a schedule | | active | | | source: decomp-architect -->
<!-- G22 | Fix the instrument before trusting its measurement | | active | | | source: decomp-architect -->
<!-- G23 | Probe before costing | | active | | | source: decomp-architect -->
<!-- G24 | Read the recorded verdicts before designing an experiment | | active | | | source: decomp-architect -->
<!-- G25 | Negative-control every new refusal-check | | active | | | source: decomp-architect -->
<!-- G26 | Exonerate the instrument before blaming the subject | | active | | | source: decomp-architect -->
<!-- G27 | Every number ships with its denominator | | active | | | source: decomp-architect -->
<!-- G28 | Refuse unsupported input; a helper refuses an empty work list | | active | | | source: decomp-architect -->
<!-- G29 | A soft error inside a success envelope is that error | | active | | | source: decomp-architect -->
<!-- G30 | A guard that is downstream, or not running, is not a guard; unattended lanes leave evidence | | active | | | source: decomp-architect -->
<!-- G31 | A derived property stored as configuration goes stale | | active | | | source: decomp-architect -->
<!-- G32 | Check against a known-true case first | | active | | | source: decomp-architect -->
<!-- G33 | A verdict names its instrument; never re-implement a gate you have | | active | | | source: decomp-architect -->
<!-- G34 | Measure the steady state; report every lane | | active | | | source: decomp-architect -->
<!-- G35 | Distinguish "judged and failed" from "not judged" | | active | | | source: decomp-architect -->
<!-- G36 | A score is not a closeness until its diff is read | | active | | | source: decomp-architect -->
<!-- G37 | Commit banked work the moment it exists | | active | | | source: decomp-architect -->
<!-- G38 | Draw-time bankability | | active | | | source: decomp-architect -->
<!-- G39 | A budget is part of the harness | | active | | | source: decomp-architect -->
<!-- G40 | Consume every verdict layer | | active | | | source: decomp-architect -->
<!-- G41 | Never key by bare function name | | active | | | source: decomp-architect -->
<!-- G42 | Periodic whole-fleet verification; the baseline before the verdict | | active | | | source: decomp-architect -->
<!-- G43 | Carve state belongs to its binary | | active | | | source: decomp-architect -->
<!-- G44 | A card names only what the knowledge base contains, and carries the banked twin | | active | | | source: decomp-architect -->
<!-- G45 | Harvest before the next wave — a hard gate | | active | | | source: decomp-architect -->
<!-- G46 | Rescan twins after every bank | | active | | | source: decomp-architect -->
<!-- G47 | Agents write their deliverables early | | active | | | source: decomp-architect -->
<!-- G48 | Every excluded population gets its own lane; never stop the drafter to ship a change | | active | | | source: decomp-architect -->
<!-- G49 | Validate the target list; an empty tier terminates the pipeline | | active | | | source: decomp-architect -->
<!-- G50 | Gate the directory, never the verdict list; recover before re-drawing | | active | | | source: decomp-architect -->
<!-- G51 | Read the compiler's source before the first "unsteerable" verdict | | active | | | source: decomp-architect -->
<!-- G52 | A wall verdict names the pass and quotes the dump line | | active | | | source: decomp-architect -->
<!-- G53 | A producer census before any spelling sweep; "PROVED" names its list | | active | | | source: decomp-architect -->
<!-- G54 | Port the banked sibling's spelling before touching a dial | | active | | | source: decomp-architect -->
<!-- G55 | Reproducers before probes; read the allocation order before any register lever | | active | | | source: decomp-architect -->
<!-- G56 | Provenance → archive → link → compiler | | active | | | source: decomp-architect -->
<!-- G57 | Nothing is unmatchable before the lever ladder is exhausted | | active | | | source: decomp-architect -->
<!-- G58 | Published numbers are generated, never typed | | active | | | source: decomp-architect -->
<!-- G59 | The checkpoint is written to be replayed | | retired | gen3.2: session checkpoint retired; TASK_PROGRESS.md handoff (skill §1); text rules/gen3.2/G59.md | source: decomp-architect -->
<!-- G60 | The matching flywheel (the decomp instance of X4) | | active | | | source: decomp-architect -->
<!-- G66 | Consult the tool dictionary before designing or debugging a tool | | active | | | source: decomp-architect -->
<!-- G67 | Translate an inherited idiom through its pass; never copy the lever | | active | | | source: decomp-architect -->
<!-- G61 | The byte gate is the only claim of success | | active | | | source: decomp-architect -->
<!-- G62 | Names and types are evidence-based, never guessed | | active | | | source: decomp-architect -->
<!-- G63 | Outward text is written by a person | | active | | | source: decomp-architect -->
<!-- G64 | No automated traffic against community infrastructure | | active | | | source: decomp-architect -->
<!-- G65 | Agents assist; a person owns | | active | | | source: decomp-architect -->

L1 | offline-tooling-first | legacy,memory | active | legacy memory offline-tooling-first.md

L2 | lever-removal-is-a-tracked-series | legacy,memory | active | legacy memory lever-removal-is-a-tracked-series.md

L3 | decomp-accelerator-ledger | legacy,memory | active | legacy memory decomp-accelerator-ledger.md

L4 | verify-blast-radius-not-just-defect | legacy,memory | active | legacy memory verify-blast-radius-not-just-defect.md

R98 | Known-opposite check before a none/external/already-done verdict settles | - | active | PhaseEnd_Phase37 candidate, ratified 2026-09-29

R99 | Key by (binary, address, body) in indexes, maps and censuses | - | active | PhaseEnd_Phase37 candidate, ratified 2026-09-29

R100 | One done-filter function shared by every side | - | active | PhaseEnd_Phase37 candidate, ratified 2026-09-29

R101 | Bucket the remainder before a cycle stops | - | active | PhaseEnd_Phase37 candidate, ratified 2026-09-29

R104 | A signature change is one judged unit | - | active | PhaseEnd_Phase37 candidate, ratified 2026-09-29

R105 | No carry-audit section means audit blocked | - | active | PhaseEnd_Phase37 candidate, ratified 2026-09-29

R118 | Tool stop: SIGINT, wait, then restore | - | active | PhaseEnd_Phase37 candidate, ratified 2026-09-29

R119 | Snapshot/refresh helpers refuse empty or shrunken input | - | active | PhaseEnd_Phase37 candidate, ratified 2026-09-29

R120 | Issue reply drafts are never committed or mentioned in commit text | - | active | developer 2026-09-30

R121 | Phases name the counts they move and publish them at close | - | active | developer 2026-09-30

R122 | Tier-2 struct twins are folded on evidence or listed with a cause | structs,census,twins | active | PhaseEnd_Phase3.38 binding (T5.1)

R123 | Kept casts and lying declarations stay only with a ledger row | casts,lying,ledger,macros | active | PhaseEnd_Phase3.39 binding

R124 | Raw cast residue is covered per site by a cause-named RESIDUAL row | casts,residue,ledger,restruct | active | PhaseEnd_Phase3.39 binding

R125 | GTE asm in bodies is spelled only through gte_inline.h | gte,asm,levers,headers | active | PhaseEnd_Phase3.39 binding

R126 | Lever residue is a ledger, gated by --strict --residue | levers,pins,asm,residue,ledger | active | PhaseEnd_Phase3.39 binding

R127 | A tool change ships with its wiring and docs; no audit fan-outs | tools,docs,wiring | active | legacy memory, Drew 2026-09-02

R128 | Phase records keep the narrative axis for the retrospective | phase-end,logs,retrospective | active | legacy memory, Drew 2026-08-31
