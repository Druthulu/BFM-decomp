---
ts: 2026-10-22T00:36:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hGkrsaOu2L6CyoicCnPI
---
Deletion is blocked in this session. I'll note it in the log: the scratch helpers (4 small .py files + d1.c) and the two --keep score dirs (3.9 MB in .run/P36/engine/score) could not be deleted because the sandbox denies rm/find -delete. They're tiny and inside .run (gitignored), so the shard dir stays well under 200 MB.

Now let me write the log file: phase-ends/current/logs/T11.cG11.md.

Let me check the log dir exists and look at an existing log's format briefly (to match the house style). Let me look at one existing log file (T11.cG10 or similar) — but I shouldn't read phase-ends/*/logs/ wholesale... The rule says "Never read phase-ends/*/logs/" — the harness forbids reading logs. Hmm, but the current phase's logs are where I write. The rule is about not reading them (dispatch a retriever). Let me just write in the house style: terse markdown, timeline per item, moves that cracked, walls with evidence.

Let me write the log now.

Content plan (terse, house style):

# T11.cG11 — singleton crack shard G11 (scratch-only)

Scope: 8 items, kind `launder` each. Results in `.run/P40/T11/G11/results.tsv`; per-item notes in `<dir>/notes.md`; one line per item appended to `.run/P40/T11/moves.md`.
Tooling: `tools/delever_search.py --try <TU> <fn> <body> --body` (score 0 = MATCH) run directly (the shard's `bin/dt.sh` wrapper is equivalent).

## Timeline (session start 18:04 MDT, end 18:36 MDT, 32 min wall; times from the candidate files' mtimes)

| item | window | min | tries | result | best | wall |
...

Hmm, the house style says "numbers in a short table only where they change a decision" — a table is fine for a timeline. But §10 says "no tables in logs" (from the model-read files rule: "no tables in logs"). Let me use a list instead.

Let me write it.

Then also note the shard-dir cleanup issue and the sandbox notes.

Let me write the log.
