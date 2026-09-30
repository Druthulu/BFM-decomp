# Generation 1 — 1

Goal: legacy project layout, migrated to PA3.
Done-criteria: PA3 migration commit present; LEGACY_INDEX.md has entries.

## Phases

<!-- Line grammar (parsed by launch.py, genend_index.py, plan_edit.py gen-close):
     - <G>.<n> <name> | milestone: … | scope: … | depends: — | status: open|closed | phase-end: phase-ends/PhaseEnd_Phase<N>.md
     Order = build order. `depends:` names phase ids or `—`. Only plan_edit.py gen-close|gen-open flips `status:`. -->

- 1 PhaseEnd — Phase 1: Repo governance + WSL RE stack + first i | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase1.md
- 2 PhaseEnd — Phase 2: Deterministic disc & .CD extraction pipe | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase2.md
- 3 PhaseEnd — Phase 3: File-loader & overlay-map RE (+ PCSX-Red | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase3.md
- 3.5 PhaseEnd — Phase 3.5: Prototype Research Spike | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase3_5.md
- 4 PhaseEnd — Phase 4: Matching-build toolchain (WSL) | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase4.md
- 5 PhaseEnd — Phase 5: splat config + build skeleton (all-asm b | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase5.md
- 6 PhaseEnd — Phase 6: Compiler fingerprint + first matched fun | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase6.md
- 7 PhaseEnd — Phase 7: Matching loop at scale + Gen1 close-out | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase7.md
- 8 PhaseEnd — Phase 8: Finish the EXE — remaining PsyQ librarie | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase8.md
- 9 PhaseEnd — Phase 9: Binary-agnostic toolchain refactor | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase9.md
- 10 PhaseEnd — Phase 10: Resident engine blob — splat config + a | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase10.md
- 11 PhaseEnd — Phase 11: Cross-binary dedup pipeline | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase11.md
- 12 PhaseEnd — Phase 12: Key engine systems (resident harvest, s | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase12.md
- 13 PhaseEnd — Phase 13: Representative location overlays (end-t | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase13.md
- 15 PhaseEnd — Phase 15: Overlay long-tail (fleet harvest + dete | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase15.md
- 16 PhaseEnd — Phase 16: Struct-heavy shared core — the loose-ty | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase16.md
- 17 PhaseEnd — Phase 17: Raise the harness ceiling, then gate th | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase17.md
- 18 PhaseEnd — Phase 18: Compiler-quirk research → the matching  | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase18.md
- 19 PhaseEnd — Phase 19: Scale the toolkit (wave-harvest at scal | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase19.md
- 20 PhaseEnd — Phase 20: Close the propagation cap, crack the gc | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase20.md
- 21 PhaseEnd — Phase 21: The Automation Manager (built, run, and | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase21.md
- 22 PhaseEnd — Phase 22: Hand-grind the giants (×134) — banked t | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase22.md
- 23 PhaseEnd — Phase 23: The offline LLM matching tier → the Fab | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase23.md
- 24 PhaseEnd — Phase 24: Permuter overhaul · integration-recover | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase24.md
- 25 PhaseEnd — Phase 25: The structural-family endgame → the gia | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase25.md
- 26 PhaseEnd — Phase 26: The Family-Endgame → the tooling-integr | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase26.md
- 27 PhaseEnd — Phase 27: The Fable5 Farewell Sprint + the Honest | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase27.md
- 28 PhaseEnd — Phase 28: The Endgame Engine → the instrument-rep | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase28.md
- 29 PhaseEnd — Phase 29: The Family Campaign (cores + members) — | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase29.md
- 30 PhaseEnd — Phase 30 The Recovery & Concentration Campaign (o | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase30.md
- 31 PhaseEnd — Phase 31: The Frontier Atlas & Wide-Tolerance Cam | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase31.md
- 32 PhaseEnd — Phase 32: The Last 21 + the Parked 5 — the fronti | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase32.md
- 33 PhaseEnd — Phase 33: 100% verification + the publishing surf | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase33.md
- 33.5 PhaseEnd — Phase 33.5: Docs consolidation, the wiki as sourc | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase33.5.md
- 34 PhaseEnd — Phase 34: The flip and the Gen2 exit — the reposi | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase34.md
- 35 PhaseEnd — Phase 35: Gen3 opens — the dedup phase, "one sour | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase35.md
- 36 PhaseEnd — Phase 36: Levers off — every compiler-forcing con | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase36.md
- 37 PhaseEnd — Phase 37: the structs phase, part one — the censu | milestone: — | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase37.md
- 37.5 PA3 migration | milestone: migration complete | scope: — | depends: — | status: closed | phase-end: phase-ends/PhaseEnd_Phase37.5.md

## Ordering rationale

- Legacy phases in their original order; the migration phase closes the generation.

## Standing constraints

- Stdlib only.

## Changes

<!-- - <date> planner|developer: <what> — <why> -->
