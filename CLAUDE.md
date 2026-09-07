# CLAUDE.md — Brave Fencer Musashi Decompilation

Matching decompilation of **Brave Fencer Musashi** (PS1, SLUS-00726 USA). Goal: byte-for-byte identical binaries from C source.

## Session Start Protocol — Do This First, Every Session

**Budget: the whole protocol should cost about 100k tokens plus the verbatim checkpoint block** (Drew, 2026-09-05; R64
candidate). Read these files in this order — nothing else at session start:

1. Read `PROJECT_CONTEXT.md` in full (the permanent constitution: rules, protocols, roadmap).
2. Read `phase-ends/DIGEST.md` in full — every phase's synopsis, every rule's full text (R1–R64), the corrections that
   supersede parts of PROJECT_CONTEXT.md, and the doc map. It REPLACES reading every PhaseEnd (the PhaseEnds are still
   kept forever — read an older one on demand when a synopsis is not enough; **never** read `phase-ends/logs/` at
   session start, R19).
3. Read the **three most recent** `phase-ends/PhaseEnd_*.md` in full, in numeric order.
4. Read `phase-ends/CURRENT_PHASE.md` in full if it exists (the in-phase state).
5. For matching phases (Phase 6+): read `docs/matching-cookbook.md`'s first ~120 lines (the pinned triple + §1–§3) and its
   most recent § only, and `docs/SETUP.md` §5.4 (the pinned triple). The cookbook is 3.5 MB and `docs/cookbook-index.md`
   is 566 KB: grep them by §/symptom during matching, never read them whole. The knowledge base is a **compounding
   flywheel** — consult it before each match, and after each match feed the generalizable lesson back into BOTH the
   cookbook AND the tooling (`tools/permuter/` recipes, the m2c `--context`) so future similar functions one-shot.

After reading, state the following and nothing else, in this order:
- Current phase number and name; which tasks in the current phase are already complete; which single task is NEXT
- The recommended **effort level** for that NEXT task per `docs/effort-map.md`, and confirm the developer has it set
- Every AI Collaboration Rule from `PROJECT_CONTEXT.md` (P/G/H/X) plus every R-rule, **in full text**, transcribed from
  `phase-ends/DIGEST.md` §3
- **The last `## 🛑 SESSION CHECKPOINT` block of `phase-ends/CURRENT_PHASE.md`, reproduced VERBATIM and in full** — not
  summarized. That block is written to be replayed: it is the complete seed for this session and it is the ONLY in-phase
  context this session inherits from the previous one.

Then wait for the developer to confirm before doing anything. Do not summarize the project. Do not list all remaining
tasks. Do not start working. State what is next, list the rules, replay the checkpoint, and wait.

---

## Mandatory Behavior — Violations Are Never Acceptable

These rules govern every session. They are not suggestions.

**1. One task at a time.** Present one task. Wait for the developer to confirm completion. Then present the next. The only permitted grouping: up to 3 pure terminal commands with no decision-making (`mkdir`, `git init`, `dotnet restore`). If a step involves writing a file, making a design choice, or producing code, it is its own task. Presenting an entire phase checklist as implementation — or even half of one — is a violation regardless of how "simple" the tasks appear.

**2. Stop at phase end.** When a phase milestone is confirmed complete, create the PhaseEnd file using the Write tool and stop. Do not preview the next phase. Do not start the next phase. Do not discuss what comes next. End your message with the 🛑 stop instruction inside the PhaseEnd file and nothing more.

**3. Phase Start Protocol.** When beginning a new phase: follow the Reasoning & Model Protocol below to request the right settings, analyze the phase checklist against previous work and overall scope, present a task-by-task plan with any adjustments and reasoning, wait for the developer to approve or modify the plan, then switch to one-task-at-a-time execution.

**4. Files on disk, not chat.** All code, configuration, and PhaseEnd content are written to disk using the Write or Edit tools. Never paste code or PhaseEnd content inline in chat as the deliverable. Chat contains reasoning, explanations, and questions only. Source files, test files, and PhaseEnd markdown files are always written to the filesystem.

**5. Explain before coding.** Before writing any class, module, or function, state the design approach: what the component needs to do, any non-obvious decisions, and why this solution over alternatives. Only write code after that reasoning is stated. If a decision is trivial, say so briefly — but if there is a real choice, show the thinking.

**6. Never overwrite blind.** Before overwriting any existing file, read the current version from disk first. State what will change and why before applying edits. Preserve all existing comments and doc-style headers — never silently drop them during a rewrite.

**7. Mid-phase rules check.** After completing every 4 tasks within a single phase, pause and re-read this rules section before continuing. State: "Rules check — re-read complete. Continuing with [next task]."

**8. Verify every checkbox before closing a phase.** Before marking any phase complete, explicitly verify every checkbox in that phase's checklist — including wiring steps like DI registrations, config bindings, and integration tasks. The phase milestone must be explicitly reached and confirmed by the developer before the PhaseEnd file is created.

---

## Fail-safe hard rules (duplicated from PROJECT_CONTEXT.md in case the above is ever skipped)

- **Never commit ROM-derived content.** The game dump, `disks/`, `asm/`, `assets/`, `build/`, `expected/`, extracted `.CD` contents, and the Ghidra project stay out of git. Review `git status` before every commit.
- **Never edit `PROJECT_CONTEXT.md`.** It is permanent and static. Corrections and state go in `phase-ends/`.
- **Never `git clean -x` / `git clean -fdx` in this tree.** Since Phase 33 C3 (2026-09-06) the Ghidra project (`ghidra/`), the RAM dumps (`dumps/*.bin`), the PsyQ SDK (`tools/psyq/`), the session archive and the extension zips are IGNORED BUT PRESENT on disk — a `-x` clean deletes the reverse-engineering database. `make clean` is the only clean. (Regenerable in principle from `config/ghidra/` + the disc via `tools/ghidra_rebuild.sh`, but the dumps are not.)
- **A "match" is byte-for-byte assembly equality AND the full-binary SHA1 check staying green.** Never report a functionally-equivalent function, a passing-looking build, or any unverified outcome as done.

---

## Environment

- Ghidra MCP server config: `.mcp.json` (GhidrAssistMCP, SSE on `http://127.0.0.1:8080/sse`). Ghidra must be running with `SLUS_007.26` open in CodeBrowser before any reverse-engineering work — verify with a cheap MCP call first.
- Builds, splat, and asm-differ run **only in the WSL2 clone** (`~/bfm-decomp`, ext4) — never on `/mnt/z`, never in this Windows tree. Invoke via `wsl.exe` per `docs/SETUP.md`.
- Volatile facts (tool versions, URLs, commands): `docs/SETUP.md`. File formats: `docs/formats.md`. Address ledger: `docs/memory-map.md`.

---


## Reasoning & Model Protocol

Effort is set with `/effort` on the ladder `low / medium / high / xHigh / Max` (this is *depth* — how hard one agent reasons). **Max** = deepest single-agent reasoning, **session-only** (re-apply each session; xHigh is the highest level that persists). **Ultracode is NOT a deeper level** — it runs at xHigh and adds multi-agent orchestration (breadth, not depth); also session-only. **The project default working level is Max** (usage is not a constraint; the only downside is mild overthinking/latency on trivial tasks); drop to xHigh only for routine work when faster turns are wanted, and **never globally enable Ultracode for the deep tasks** (it would cap them at xHigh). Breadth is applied surgically — Claude proposes a Workflow fan-out for genuinely parallel tasks.

**Effort-map check (rule — formalized as R7 at PhaseEnd_Phase2):** the full task→effort map, the Max-vs-Ultracode decision rule, verified harness mechanics, and per-phase guidance live in `docs/effort-map.md` (evolvable; it governs where this section's tier language differs). Before each Phase Start plan, state the recommended effort for *planning that phase* per that file and confirm the developer has it set; annotate every task in the phase plan with its effort level; restate the recommended effort whenever you present the NEXT task. The complexity tiers below map onto the ladder.

**Tier 1 — Mandatory deep reasoning. STOP and request the change.**

These tasks always require maximum reasoning. Before starting, state:

> 🟡 This is a Tier 1 task — [reason]. Confirm **effort: Max** is set (deepest single-agent reasoning — the project default for substantive work; Ultracode/parallel fan-out is for *breadth* tasks, not these). Confirm when ready.

Wait for the developer to confirm before proceeding. Tier 1 tasks include:
- Phase Start planning (analyzing the phase checklist against previous work)
- PhaseEnd file creation (synthesizing the phase's work, deviations, rule candidates)
- Architectural decisions affecting multiple files or components
- Non-obvious debugging where root cause is unclear
- Any task with multiple valid approaches where the choice has lasting consequences

**After the Tier 1 task completes:** remind the developer to drop back down. State:

> 🟡 Tier 1 task complete. Max stays the default; drop to **effort: xHigh** only if the next task is routine and you want faster turns (see `docs/effort-map.md`).

**Tier 2 — Recommended, let the developer decide.**

These tasks benefit from extra reasoning but aren't always critical. Before starting, state:

> 🟡 This task would benefit from increased reasoning — [reason]. Consider bumping to **effort: xHigh**. Want to adjust before I start?

Wait for the developer's response before proceeding. Tier 2 tasks include:
- Multi-file features (touching 3+ files coordinated)
- Complex business logic with multiple edge cases
- Comprehensive test suites
- Any task where you're uncertain about the best approach

**Tier 3 — Proceed normally, no change needed.**

Don't prompt for these. Just proceed with whatever settings are active. Tier 3 tasks include:
- Single-file implementations with clear requirements
- Simple CRUD or boilerplate
- Terminal commands
- Small edits, renames, config changes
- Tasks where the design was already decided in the phase plan

**Critical:** Never skip the stop-and-wait for Tier 1. If you realize mid-task that a task is more complex than expected and should have been Tier 1, say so — the developer can stop the response and restart with the right settings. Do not silently power through complex tasks at low reasoning and report afterward that "this was tricky."

---

## Phase Boundary Protocol

When a phase milestone is confirmed complete:

1. State: "🟡 PhaseEnd creation is a Tier 1 task. Confirm when ready."
2. Wait for confirmation.
3. Create the `PhaseEnd_Phase[N].md` file using the Write tool, taking time to reason carefully about the phase as a whole.
3b. Append the phase's synopsis and its ratified rules to `phase-ends/DIGEST.md` (the session-start digest; a P7 checkbox — a PhaseEnd without its digest entry is not closed).
4. Final message: "PhaseEnd file created. Commit the file and start a new Claude Code session for the next phase."
5. HARD STOP. Do not preview the next phase. Do not continue working. Do not suggest what comes next.

---

## Project-Specific Constraints

- **Document disabled logic.** When disabling or commenting out any logic based on evidence, leave a structured comment:
  ```
  // DISABLED: [name] — [date or phase]
  // Original intent: [what it was supposed to do]
  // Why disabled: [specific evidence — backtest/live numbers]
  // Re-enable if: [specific observable condition]
  ```

---

## Reminders

- The Project Context file is permanent and static. Never edit it. Current version and phase status live in the most recent PhaseEnd file.
- All PhaseEnd files are kept for the life of the project. None are discarded.
- The PhaseEnd file is the deliverable that ends a phase. After it is committed, the next session reconstructs full state by reading the context file plus all PhaseEnd files.