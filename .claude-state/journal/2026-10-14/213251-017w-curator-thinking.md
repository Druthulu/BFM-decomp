---
ts: 2026-10-15T03:32:51.293Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a705ed8352fdd0106
model: claude-opus-5-5[1m]
effort: medium
turnId: 7a67f1a0-185f-485c-896e-f31712674803
---
I don't see autoMemoryDirectory in the settings grep, so I'll just note that Claude's state (memory, transcripts) lives in-repo under `.claude-state/`, since the memory directory is evidently `.claude-state/memory`. This detail is marginal for every agent, so I'll keep the note brief and lean toward the repo being self-contained.

The generated directories—`asm/`, `build/`, `extracted/`—plus the census/report outputs should be described generically, and I want to check these exist and reference docs/tool-index.md for the tools row. Now I'm planning the card edits: I'll run the real card refresh after the dry run, routing mcp-reconnect-after-restart to ops for the full lifecycle detail while keeping a short Developer-line pointer in the card, and handling tool-change-updates-siblings-and-docs and phaseend-verbosity through rules_add with clean text since their old bodies reference now-removed files.

Looking at §7, I'm adding R127 for the tool-change rule, capturing that wiring sibling tools, counting agent-driven changes, and answering from actual work (not audit fan-outs) deserves its own entry, complementing R87 on tools shipping with their dictionary row. Then R128 covers phase-end verbosity — phase records should carry the narrative axis (dead ends with reasoning, costs, withdrawn claims, dates) — and I'm confirming the full retrospective story is still a future project separate from BFM. For memory keeps, there's likely nothing new under policy item 4, so MEMORY.md reindex just keeps the archive pointer. Finally I'm resolving contradictions: R1 on private ROM content being committable is superseded by G12 and the 2026-09-08 public flip, so I'm demoting R1 and archiving the rom-content-git-policy memory.

Now I'm working through more contradictions — phase-end verbosity narrative content stays as a rule placed in PhaseEnd/log while checkpoint parts get dropped; dedup-backlog-leave-it already reversed itself in Phase 35; the subagent model ladder loses to the "NO SONNET" supersession and 3.2 roles standing; effort-doctrine loses to the skill's "never /effort"; and capture-knowledge-before-fresh-session gets archived since its spirit lives in skill §7. I'm demoting R1, R7, and R27, confirming R4's plan-mode gate stays consistent, and now checking whether G59's "checkpoint is written to be replayed" rule is stale since the checkpoint mechanism was retired — need to read G59 directly, while G47 and G48 look fine as is.
