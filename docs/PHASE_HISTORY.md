# Phase history

Built by `tools/phaseend_index.py history` from the PhaseEnds and rebuilt at each close; never edited by hand. Each phase's PhaseEnd holds the rest.

## Phases

- 1 | 2026-06-13 | Repo governance + WSL RE stack + first import
- 2 | 2026-06-13 | Deterministic disc & .CD extraction pipeline
- 3 | 2026-06-14 | File-loader & overlay-map RE (+ PCSX-Redux harness)
- 3.5 | 2026-06-14 | Prototype Research Spike
- 3.38 | 2026-09-30 | Struct unification | Phase 3.38 was the second half of the "structs" work in the readability generation: the game's C already compiles to the original bytes, and this phase made its data types readable by giving every st…
- 3.39 | 2026-10-02 | Casts to declared data | Phase 3.39 was the cast campaign: the decompiled C still read memory through raw pointer arithmetic such as `*(s16 *)(p + 0x10)`, and the goal was that every such "raw cast" either becomes a named st…
- 3.40 | 2026-11-07 | Residue lane | Phase 3.40 gave the struct types left undecided after 3.39 their single agreed definitions, and made every remaining compiler hint justify itself.
- 3.41 | 2026-11-08 | Types validated and mirrored | Phase 3.41 made the type checks meaningful and mirrored the canonical types into Ghidra.
- 4 | 2026-06-14 | Matching-build toolchain (WSL)
- 5 | 2026-06-14 | splat config + build skeleton (all-asm byte-match)
- 6 | 2026-06-14 | Compiler fingerprint + first matched functions
- 7 | 2026-06-15 | Matching loop at scale + Gen1 close-out
- 8 | 2026-06-15 | Finish the EXE — remaining PsyQ libraries + final harvest
- 9 | 2026-06-15 | Binary-agnostic toolchain refactor
- 10 | 2026-06-15 | Resident engine blob — splat config + all-asm byte-match | The game's permanent "engine" — the always-loaded chunk of code that holds the script system and the sound driver — now rebuilds perfectly, byte-for-byte, from our own source files.
- 11 | 2026-06-16 | Cross-binary dedup pipeline | We taught our build system a new trick: spotting when the *same* piece of game code shows up in more than one part of the game, so we only have to figure it out once and reuse it everywhere.
- 12 | 2026-06-16 | Key engine systems (resident harvest, script/event, save, SQV) | The game's permanent "engine" went from essentially nothing decompiled to 86% rebuilt, bit-for-bit, from our own source code — in a single session.
- 13 | 2026-06-16 | Representative location overlays (end-to-end + fleet runbook) | The game's first playable "level" now rebuilds perfectly, bit-for-bit, from our own source and is about a quarter decompiled — and so do a duplicate level and a big open level, so six pieces of the g…
- 15 | 2026-06-18 | Overlay long-tail (fleet harvest + deterministic recovery) | The game's 134 "levels" are now all wired into our build, and 136 separate pieces of the game rebuild perfectly, bit-for-bit, from our own source — up from 6 at the start of this phase.
- 16 | 2026-06-19 | Struct-heavy shared core — the loose-typing wall + pivot | We tried to automatically reconstruct the game's hardest remaining code — the shared "engine" functions used by every level — by having a decompiler write C, a brute-force tool fix the small details,…
- 17 | 2026-06-20 | Raise the harness ceiling, then gate the compute run | We spent this phase trying to make our automatic game-code-matching dramatically more productive.
- 18 | 2026-06-20 | Compiler-quirk research → the matching TOOLKIT, taught to waves at scale | This phase started as "study the 1990s compiler so we can copy its quirks," and it paid off: we read the actual compiler's source code and a sister Square game (Xenogears) built with the *exact same*…
- 19 | 2026-06-20 | Scale the toolkit (wave-harvest at scale + cheap front-loaded levers) | This phase was about scaling up the function-matching machine we built last phase.
- 20 | 2026-06-21 | Close the propagation cap, crack the gcc residual classes, then scale the waves | This phase squeezed the remaining easy wins out of the game's shared engine code and, just as importantly, *proved which "easy wins" were actually mirages.* We built a tool that auto-fixes a common r…
- 21 | 2026-06-26 | The Automation Manager (built, run, and its ceiling byte-proven) | Over about ten sessions we built and ran an "automation factory" for reconstructing the game's code: swarms of AI agents draft the C, a token-free brute-forcer polishes the near-misses, and an automa…
- 22 | 2026-06-29 | Hand-grind the giants (×134) — banked the tractable tail; the irreducible giants byte-deferred | This phase was the "hand-finish the giant functions" plan from the end of Phase 21.
- 23 | 2026-07-02 | The offline LLM matching tier → the Fable5 wall-breaker + the gcc-2.7.2 codegen map | This was the phase where the project cracked its hardest problem.
- 24 | 2026-07-08 | Permuter overhaul · integration-recovery · the giant endgame (all matched giants ×134) + the structural-family reframe | This phase finished the "giant" functions — the biggest, most-reused pieces of the game's engine — and stamped every one that can be matched into all 134 levels, bit-for-bit.
- 25 | 2026-07-11 | The structural-family endgame → the giant endgame + the h_seq family reframe | This was a huge, multi-day push, and it ended on a discovery that changes the whole finish line.
- 26 | 2026-07-15 | The Family-Endgame → the tooling-integrity audit + the §52 discovery-flywheel (mechanical harvest byte-proven exhausted) | This was the longest stretch of the project, and it ended by *changing what we believe about the finish line*.
- 27 | 2026-07-15 | The Fable5 Farewell Sprint + the Honest Frontier | This was a "fix the instruments, then look" phase — and looking through honest instruments changed the picture three ways.
- 28 | 2026-07-16 | The Endgame Engine → the instrument-repair phase (every "wall" was our tooling) | This phase was supposed to measure one number — how often the "same function, slightly different per level" pattern can be rebuilt automatically — and build a tool around it.
- 29 | 2026-07-30 | The Family Campaign (cores + members) — the biggest gain in project history, and the engine honestly spent | This phase was the big harvest.
- 30 | 2026-08-14 | The Recovery & Concentration Campaign (overlays to their ceiling) | This phase took the game's hundreds of level files from "mostly translated" to "nearly finished" — 95.3% of all the game's code now rebuilds byte-for-byte from our C source, checked against the origi…
- 31 | 2026-09-05 | The Frontier Atlas & Wide-Tolerance Campaign (main to 95%, the fleet to 100.0%, and the last 21) | This phase started with about twelve thousand functions of the game still un-translated and ended with twenty-one.
- 32 | 2026-09-06 | The Last 21 + the Parked 5 — the frontier emptied (every game-code function in every binary is byte-identical C) | This short phase finished the translation.
- 33 | 2026-09-07 | 100% verification + the publishing surface + the releases — everything before the flip (re-chartered close) | This phase took a finished-but-private translation and made it ready to publish.
- 33.5 | 2026-09-08 | Docs consolidation, the wiki as source of truth, the tracked-`.run/` prune, the memory reconciliation, and the day-one decomp kit (sub-phase before the flip) | This short phase tidied the project for its public release and packaged what it learned.
- 34 | 2026-09-08 | The flip and the Gen2 exit — the repository public, the boards and the wiki live, the outreach sent, the tree shaped for readers | Today the project went public.
- 35 | 2026-09-08 | Gen3 opens — the dedup phase, "one source per unique function" | This phase made the code say each thing once.
- 36 | 2026-09-11 | Levers off — every compiler-forcing construct out of the matched C, to its measured floor | When this decompilation reached 100 %, thousands of its functions still carried little hacks — instructions to the compiler that forced a particular register or ordering so the bytes would match — th…
- 37 | 2026-09-29 | the structs phase, part one — the census, the struct map, the engine and the declaration layer to its ledgered floor | The decompiled C still treated most game data as raw memory — "read two bytes at offset 0x34 of this pointer" — instead of named structs, and a hundred thousand of its function declarations described…
- 37.5 | 2026-09-29 | PA3 migration | Automated migration from PA2 to PA3.

## This generation's recaps (3, newest first)

### 3.41: Types validated and mirrored (2026-11-08)

Phase 3.41 made the type checks meaningful and mirrored the canonical types into Ghidra. `type_census --check` used to fail on all ~176k raw casts, so it could never pass. It now asserts the done-criteria: no unlisted duplicate struct layouts, no definitions outside the canonical headers, no dead names, controls 4/4, and no unledgered lying declaration. Raw casts are still printed and stay gated by `--check-casts --residue`, and the check runs inside `make tools-health`. Return-type lies, where a declaration's return type disagrees with the definition, are now detected. They went from 273 functions over 100,266 declaration lines to 19 functions over 9,302 lines. Each of the 19 is a width or sign mismatch kept in config/lying_exceptions.tsv with the instruction that moves. `lever_census --check` now requires every `// !FAKE:` marker to name its instrument (1,853 attributed, 0 bare). A new tool, tools/ghidra_types.py, writes 7,151 canonical types (structs, typedefs, unions) from the headers into per-program Ghidra rows. Their field offsets and sizes equal gcc's, a staleness `--check` sits in tools-health, and all six rebuild proofs pass. The live Ghidra database holds the types, and the developer confirmed COORD2_8001EFE0 is right. Three 3.40 tool bugs were fixed. The readability series and README graph now show return lies, and the day-1 guide teaches one shared prototype header. Story §10, retrospective §7 and the wiki run to Phase 41.

Milestone gate at f4b1fbad3d, from a clean tree: R22 218/218 run alone; tools-health OK; type_census --check --check-structs --check-casts --residue rc 0; lever_census --check --strict --residue rc 0; doc_links --strict 0; ghidra_rebuild --proof PROOF PASS for all six programs.

Open items:
- The developer pushes the archive clone (b9534ed) and the repo.
- The MCP Ghidra is stopped; restart it with tools/ghidra_mcp_start.sh, then the developer runs /mcp.
- .run/P41 holds ~2.4 GB of scratch plus the 1 GB ghidra.bak, which the developer keeps for now.
- For 3.43: 37 s32 definitions with no return statement, and the 9 expand-hardreg-var wall tags.
- The PA3 wait-for bug report is the developer's to file.

### 3.40: Residue lane (2026-11-07)

Phase 3.40 gave the struct types left undecided after 3.39 their single agreed definitions, and made every remaining compiler hint justify itself. A compiler hint here means a pin (forcing a value into a specific register) or a piece of inline asm. Undecided struct-type cast sites (TNC) went from 291,819 to 0, counting both the planned band and the "drift" types the sweeps created. The rare tail is recorded under its own cause, TYPE-BELOW-BAND: 5,871 sites, under the frozen cap of 6,976. Disagreeing function declarations went from 11 to 0, and 162 pins became declared parameters. A DeepSeek crack wave freed 220 functions of their hints, and 18 shared head classes cracked and were copied into every overlay that uses them. Hint sites went from 3,364 to 1,853, and ledger rows from 2,433 to 1,180. Every surviving row now names its wall, the gcc pass plain C cannot steer, from the vocabulary in config/lever_walls.tsv, and lever_census enforces it. The milestone gate passed in full at aace727c4c from a clean tree: check-casts --residue rc 0 (lying 0, unbacked 0, uncovered 0), check-structs OK, strict lever census OK (unwalled 0), lever_census --check 0 unmarked, R22 218/218, tools-health OK. Ledger backups (tools/ledger_backup.py), story §10, retrospective §7, the wiki and the graphs are done. Open items: the developer pushes the archive clone (one commit ahead); the census does not detect return-type lies (e.g. func_8016130C has 1,213 void declarations against an s32 definition; C0543); the public delever copy drops the C before/after text (the archive keeps it); three tool bugs from T21 (type_census --no-cache crash, struct_twins' stale default census, lift_types --fold's leftover comment); 9 expand-hardreg-var tags from T20 need a second look; func_80177B5C stays a lever by choice.

### 3.39: Casts to declared data (2026-10-02)

Phase 3.39 was the cast campaign: the decompiled C still read memory through raw pointer arithmetic such as `*(s16 *)(p + 0x10)`, and the goal was that every such "raw cast" either becomes a named struct member or global, or is kept on purpose with a written reason. Early on the sweep hit a wall: about 292,000 sites point into structs that have no single agreed definition yet, so the plan was changed (the "replan", reading A, 2026-10-02) to accept those sites as recorded residue, each one listed in the restruct ledger with its cause, and to leave giving those structs their canonical definitions to Phase 3.40. Under that reading the phase delivered: zero uncovered raw casts, every intentional cast spelled by one of five registered macros backed by a ledger row, lying function declarations cut from 229 to 11 (all ledgered), GTE (the PlayStation geometry coprocessor) instructions spelled one way through one header, and every remaining compiler-steering "lever" (pins and inline asm) listed in a lever residue file. All 218 game binaries still rebuild byte-identical. Raw cast counts fell from 503,016 to 336,219 overall.

Milestone verification, all at commit 78a8415257 from a clean source tree (only an unrelated discussion index line and an untracked agent file were dirty; gate outputs were restored after the run, not committed):
- `PY tools/type_census.py --check-casts --residue` exit 0: uncovered P=0 I=0 X=0 M=0, unbacked macros 0, lying 11 (ledgered 11) (.run/logs/p339_c1_casts.log).
- `PY tools/restruct.py --rung S --check-residue --only <seg>` exit 0 for `ov_*`, `md_*`, `main`, `src/shared/*`: uncovered 0 sites / 0 bodies each (.run/logs/p339_c2_resid.log).
- `PY tools/lever_census.py --check --strict --residue config/lever_residue.tsv` exit 0: residue 3528, residue-unused 0, direct GTE in bodies 0 (.run/logs/p339_c2_resid.log).
- `make clean && make extract-all JOBS=16 && make check-all JOBS=16` exit 0: `check-all: 218 passed, 0 failed of 218` (.run/logs/p339_c4_r22.log).
- `PY tools/phaseend_index.py verify` printed RED (0/1) (.run/logs/p339_close_verify.log): it parsed the whole multi-command `verified by` text as one clause and expected the check-all line in the first command's output. Its first command exited 0. Each clause was then run alone, and every one was green (above).

### 3.38: Struct unification (2026-09-30)

Phase 3.38 was the second half of the "structs" work in the readability generation: the game's C already compiles to the original bytes, and this phase made its data types readable by giving every struct (a C record type) one definition in a small set of shared header files instead of thousands of private copies. It started from 7,255 struct definitions with 206 groups of duplicates and 40 names that meant different things in different files, and ended with 1,650 definitions, all in the canonical headers except records declared inside function bodies, with no unexplained duplicates. The two biggest types, a 0x24C-byte entity record and a 0x10C-byte record used across the engine, were designed once in `include/struct_types.h` and folded in wherever the byte check allowed; the 53 duplicate groups that remain have no evidence that they are the same type and are listed with their reason in `docs/struct-twins.md`. Along the way the function declarations were rebuilt on the new types, which took the declarations that could not see their types from 1,106 to 0 and the declarations that disagree with their function from 1,796 to 229. Every change was checked by recompiling all 218 game binaries and comparing them byte for byte, and the phase closed with that check and the struct census both green.
