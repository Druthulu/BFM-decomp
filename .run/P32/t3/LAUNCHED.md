# T3 wave — launched 2026-09-05 (session 7beebba8-05e9-4d18-98ea-ce208f45370f), one Agent-tool subagent per function
Running (20): OPUS md_SC03_054:func_801EF6D8 · main:func_80039308 · ov_SC03_105:func_80185810 · md_MAIN_003:func_800CF3E8 ·
  ov_SC07_002:func_8017DC80 · resident:func_800D06E8 · main:func_80023BF0 · md_MAIN_007:func_800CF6D0 · md_MAIN_009:func_800CD92C ·
  md_MAIN_007:func_800CF408 · md_MAIN_009:func_800CD674 · main:func_80015B6C · main:func_80039B20 · main:func_80038698 ·
  main:func_8002FDE8 · main:func_8001BC6C | SONNET md_SC03_054:func_801EF558 · md_SC03_053:func_801EF7E4 · md_MAIN_007:func_800CEE2C |
  HAIKU md_SC03_053:func_801EF49C
Queued (27): pending_launch.txt. Drafts land in .run/P32/t3/{opus,sonnet,haiku}/<fn>.c; each agent's final message ends with one JSON verdict.
Recovery if this session dies: verdicts = the LAST JSON object in each transcript —
  .venv/bin/python tools/agent_verdicts.py /tmp/claude-1000/-home-musashi-bfm-decomp/7beebba8-05e9-4d18-98ea-ce208f45370f/tasks/*.output --append .run/P32/t3/verdicts.jsonl
Per result (never in bulk): grep the draft for .ent/.word (verbatim = not a match) -> rtu_match in the real TU -> gate
  (parallel_gate --r22 for md_/ov_/resident; gate_main --apply for main) -> commit per bank (R42) -> twin_rescan.

## STATE at the 2026-09-05 09:30 MDT checkpoint (written by the successor session e40106e1 — the launching coordinator
## overflowed at 07:07Z, four minutes after its 9th bank commit; see phase-ends/CURRENT_PHASE.md 🛑 for the resume order)
- 31 of 47 launched (16 Opus / 4 Sonnet incl. one escalation / 11 Haiku); 17 Haiku rows still queued in pending_launch.txt.
- Verdicts: 20 MATCH / 9 NEAR / 2 FAIL → .run/P32/t3/verdicts.jsonl (31 rows, rebuilt from tasks/a*.output only).
- Banked in the producing session (10 fns, 9 commits 4ecedb40b..0240fa5f6): func_801EF558 · func_801EF49C · func_800D06E8 ·
  func_80039B20 · func_801EF6B0 + func_801EF95C · func_801EF624 · func_800CEE2C · func_80023BF0 · func_80038698.
- MATCH, verified by the successor with rtu_match in the real TU, NOT yet banked: main func_80015B6C (120) · main func_8002FDE8 (73)
  · md_SC03_054 func_801EF6D8 (604, six jtbls → carve) · md_SC03_053 func_801EF734 (44) + func_801EF7E4 (72) · md_MAIN_007
  func_800CF148 (33) · func_800CF2BC (32) · func_800CEEFC (25) · func_800CEF94 (25) · func_800CF068 (21); func_800CF3B0 (22) is
  leaf-exact behind the TU's `extern void func_800CF3B0(void*,void*,void*)` (fix the decl first).
- NEAR (exact length): func_800CD674 2 · func_8001BC6C 6 · func_800CD92C 15 · func_80039308 17 · func_800CF3E8 27 · func_80185810 35
  · func_8017DC80 46 · func_800CF408 49 · func_800CF6D0 137. FAIL: haiku func_801EF734 (superseded by the Sonnet MATCH), func_800CF3B0 (decl).
- The opus deliverables were swept into .run/P32/t3/opus/_scratch/ by one agent's tidy-up at 07:52Z; restored to the contract
  paths 09:2x MDT and re-verified. Drafts + ledger are now git-tracked (.gitignore allowlist).
