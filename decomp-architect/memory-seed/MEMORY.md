# Memory Index

<!-- decomp-architect memory seed. The kit's installer writes each file below into the project's memory directory
(`.claude-state/memory/`, the one ProjectArchitect 2.0 configured) and APPENDS these rows to the MEMORY.md that
ProjectArchitect's seed already created. Each file is a working agreement or a harness fact learned on a finished,
byte-identical decompilation; the domain rules proper live in the rules registry (canonical) and these are the
fast-loading complement. Files tagged `upstream: PA` in their frontmatter are harness-generic and belong in
ProjectArchitect's own seed once it takes them. -->

## Already provided by ProjectArchitect 2.0's seed (cited, not duplicated)
`who-is-dev` · `project-governance-system` · `autonomous-within-phases` · `build-tasklist-after-plan-approval` ·
`capture-knowledge-before-fresh-session` · `clarify-misconception-before-costly-action` · `justify-new-tools-before-adopting` ·
`dont-block-loop-with-askuserquestion` · `no-commit-co-author` · `commit-per-task-user-pushes` · `plain-english-recap` ·
`session-start-rules-in-full` · `worklogs-reference-only` · `keep-ops-current` · `effort-discipline` ·
`effort-prompt-ultracode-on-breadth` — and the repository-resident state itself (`.claude-state/`, registry rule H8).

## The decomp seed
- [The byte gate is the only claim](the-byte-gate-is-the-only-claim.md) — "matched" means byte-identical output AND a green whole-binary hash; nothing functionally equivalent counts; "banked" is written from a tool's printed line
- [The matching flywheel](the-matching-flywheel.md) — consult the knowledge base before every match, feed the generalizable lesson back into BOTH the cookbook and the tooling after it
- [MCP reconnect after restart](mcp-reconnect-after-restart.md) — after restarting the disassembler's MCP server or switching the served program, pause and ask the developer to reconnect the client; the agent cannot
- [Offline tooling first](offline-tooling-first.md) — every COMPUTABLE step becomes a deterministic zero-token tool; keep deterministic recovery and search separate; ask "is this residual computable?" before reaching for a model
- [A slow gate is a bug](a-slow-gate-is-a-bug.md) — banking, not drafting, is the bottleneck; nothing in the gate is serial; pass `-j` to every build; measure the gate before fearing it
- [Breadth is isolated agents](breadth-is-isolated-agents.md) — the main loop's context accumulates roughly quadratically; N isolated agents cost about linearly and run in parallel; hand-by-main-loop wins only for a handful
- [Route by measured difficulty](route-by-measured-difficulty.md) — tier drafters by a cliff you measured on your own corpus; escalate sooner; the strongest model is for new wall classes, never for reviewing a corpus
- [One runbook is the procedure](one-runbook-is-the-procedure.md) — one document is the operating procedure for the campaign loop, read before every run, kept current in the same change; a superseded runbook gets a banner
- [Keep an accelerator ledger](keep-an-accelerator-ledger.md) — every late discovery that would have sped earlier work is recorded with when it was found, when it could have been, and what it would have saved
- [Checkpoint means everything is already in a file](checkpoint-means-everything-is-already-in-a-file.md) — a checkpoint is the LAST thing written; a good commit message is not in the load order; the sweep before the block
- [A PhaseEnd carries the narrative axis](phaseend-carries-the-narrative-axis.md) — what was believed, what failed and why it looked right, what it cost, what to do sooner — because transcripts die and the retrospective is rebuilt from the files
- [Tool change ships with its consumers and docs](tool-change-ships-with-its-consumers-and-docs.md) — the commit that adds a tool also wires its callers and adds its ops row; integrating an agent's tool change IS a tool change; no end-of-session audits
- [No sleep-polling background tasks](no-sleep-polling-background-tasks.md) — the harness re-invokes on completion; one sanity check after launch, then wait
- [Long checks run in the foreground](long-checks-run-in-the-foreground.md) — a background long verification can be killed by the harness's memory guard; run it in the foreground with a timeout; check for orphaned workers
- [Resume means resume the run](resume-means-resume-the-run.md) — replay interrupted work so it finishes itself, same run, same agent, transcript intact; never re-plan or re-route on your own inference
- [Answer before grinding in live co-op](answer-before-grinding-in-live-coop.md) — only the final message of a turn is guaranteed to be seen; end the turn with the answer the person is waiting on before starting long work
