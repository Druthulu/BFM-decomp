# SETUP.md — Environment Setup & Daily Operations Reference

> **This file is the EVOLVABLE reference layer.** Unlike `PROJECT_CONTEXT.md` (permanent, never edited), this document holds volatile facts — pinned versions, URLs, commands, ports — and **may be updated freely** as tools move. Note each change in the active phase log (`CURRENT_PHASE.md`). Items marked **TBD** / **UNVERIFIED** / **JP-only — re-derive for US** are honest gaps: confirm before relying on them, then update this file.

Last full revision: 2026-06-10 (initial authoring, pre-Phase-1 — nothing below is installed yet except the repo itself; same-day conversion to the all-in-WSL / Linux-first architecture — everything now runs inside a single WSL2 Ubuntu 24.04 clone, no Windows/WSL split).
**Refresh 2026-09-07 (P33 D4, the public-clean pass):** the repository is PUBLIC from Phase 33 (in-place flip with the full, rewritten history — `docs/public-flip-runbook.md`); H1 is in force again (no ROM-derived bytes in git); every "private repo / vendored / mirror" passage below was reviewed and rewritten or dated as history; the canonical remote is `https://github.com/Druthulu/BFM-decomp.git`.
**Refresh 2026-06-15:** added a tooling/MCP-lifecycle/session-hooks/backup-posture pass after the doc had drifted past the as-built reality — new §1a (`.run/` scratch), §2.8 (MCP lifecycle, persistence model & session hooks), a `## Tooling inventory` table, and a `## Backup & private-repo posture` section. Rule **R21** (added this session) now requires keeping THIS file current whenever tooling / MCP / hooks / env change.

