# answers.md — the unattended answers for the decomp-architect dry-run (P33.5 task 13, fixture; fictional game).
# Format: KEY: value — one per line; the kit's SETUP Step 2 reads the thirteen keys plus INSTALL_DATE.

GAME_TITLE: Starfall Courier
PLATFORM: PlayStation
GAME_SERIAL: SLUS-99999 (USA)
TARGET_BINARY: SLUS_999.99
DUMP_PATH: /nonexistent/starfall-courier-usa.bin
CONTAINER_LAYOUT: one data track; the game code lives in compressed archive entries inside three container files, streamed into high RAM as position-locked overlays
SDK_EVIDENCE: nine vendor-library version stamps in the executable (eight at 4.0, one at 4.2); the loader detected SDK 4.0
COMPILER_FAMILY: the gcc 2.7.x era that shipped with the vendor SDK (candidates: two gcc 2.7.2 builds; assembler compatibility versions 2.5x to 2.6x)
COMMUNITY_WORK: none found on 2026-09-07
PROJECT_GOALS: a byte-identical rebuild of every binary on the disc from C source, verified by a hash inside every build, then a source a human maintainer would call finished
LICENSE_CHOICE: AGPL-3.0 for the project's own tools, build system and documents; no license asserted over src/
AI_DISCLOSURE: This project is carried by an AI coding agent under a human-governed phase process; every match is proven by a whole-binary hash and every name is evidence-based.
PUBLIC_OR_PRIVATE: private until the contract run; the ROM firewall applies from the first commit either way
INSTALL_DATE: 2026-09-07

## For ProjectArchitect's own installer (answered by the installing agent, never by a human)
PA_PATH: A (a new, empty repository)
PA_DEV_INTERVIEW: advanced developer; domain = matching decompilation of console games; solo; autonomous within phases, recommendation-first options, breadth fan-out welcome
PA_INTAKE: read decomp-architect/intake.decomp.md and generate from it; the game-specific FILL items are the values above; the Build Roadmap is its Part B; registry §E gets only the one-line pointer of its Part D; the CLAUDE.md fail-safes are the four its Part D names
PA_GATE1_REVIEW: nothing to adjust — generate as the intake says
PA_GATE2_EFFORT: effort Max is already set for this run — proceed, and log "Gate 2 toggle skipped (unattended dry-run)" as a deviation
PA_HOME_DIRECTORY_STEP: SKIP ENTIRELY — write nothing under ~/.claude (no statusline, no user settings); log the skip as a deviation
