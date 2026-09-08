# 01 — Governance: a constitution, two gates, and a checkpoint written to be replayed

The documented way agentic reverse-engineering projects die is not bad code. It is *fake success* — stubs reported as
matches, "functionally equivalent" redefined as done, a green light obtained by moving the goalposts — plus context
drift across sessions. BFM's governance was designed against exactly those, and it is what let roughly 99% of the
work be the agent's over 33 phases and some 87 sessions without a single redefined milestone. This chapter is the
framework as it was actually run; the template it came from is published as
[ProjectArchitect](https://github.com/Druthulu/ProjectArchitect).

## The three layers of the record

| Layer | File(s) | Mutability | Holds |
|---|---|---|---|
| **The constitution** | [`PROJECT_CONTEXT.md`](../../PROJECT_CONTEXT.md) | **never edited** after generation (rule P1) | the rules, the protocols, the roadmap, the key decisions with their rejected alternatives, the philosophy ("bytes are the only truth") |
| **The living record** | [`phase-ends/`](../../phase-ends/): one `PhaseEnd_Phase<N>.md` per phase, `CURRENT_PHASE.md` while a phase is open, the digest, the archived logs | append-only | what each phase built, verified and deviated from; the rules it added; the corrections to the constitution |
| **The evolvable references** | `docs/` — the setup reference, the cookbook, the memory map, the decision log, the playbooks | freely edited, kept current in the same change as the thing they describe (R21) | volatile facts: versions, commands, addresses, idioms |

A correction to the constitution is recorded in the current phase's log and PhaseEnd, never in the constitution. The
digest ([`phase-ends/DIGEST.md`](../../phase-ends/DIGEST.md)) collects every such correction in one place, so a reader
of the constitution knows which paragraphs have been superseded and by what.

## Rules that accumulate

The constitution ships with 25 rules in four groups — process (P), ground truth (G), hygiene (H), communication (X).
The ones that mattered most in practice:

- **G3 / P9** — a match is byte-for-byte *and* the whole-binary hash stays green; only observable, machine-checkable
  outcomes count as success; failures are reported as failures, with the output.
- **G1 / G2** — the disassembler and the emulator are the oracles; never speculate from general knowledge; ping the
  oracle before any RE task.
- **P3** — two gates per phase, autonomy between them.
- **P10** — rules accumulate: at every PhaseEnd the agent proposes rules from the phase's corrections and repeated
  mistakes, each with a one-line justification; the human approves, modifies or rejects.

By the close there were 73 numbered rules (`R1…R73`), each born from a specific cost. A rule is not a platitude; it
names the failure and the instrument. Examples: *R42 — commit banked work the moment it exists, before the next command
that can touch the source (a gate is one)* — written after a gate destroyed 61 uncommitted banks; *R53 — verify a build
from its exit code, not its output file* — a failed build leaves the previous binary in place, and `sha1sum` reads green;
*R64 — the session-start digest and the verbatim checkpoint replay* — written when the start protocol had grown to 150k
tokens. The full text of every rule is in the digest.

## The phase cadence

```
plan (Max effort, plan mode)  ─►  GATE 1: the human approves the task-by-task plan
   ─►  autonomous execution: one task at a time, one commit per task after the phase log is updated,
        a rules re-read every four tasks, stop conditions only for: a check failing twice with different
        claimed causes · a rule violation · a git operation that would add ROM bytes or rewrite history ·
        a plan change · a dependency the human must restart
   ─►  GATE 2: the milestone demonstrated with its observable proof; the human confirms
   ─►  the PhaseEnd file (build log · deviations table · rules proposed · changelog · plain-English recap)
        + the digest entry; the log archived; HARD STOP; a fresh session for the next phase
```

The gates are where a wrong *direction* gets caught; the byte gate is where a wrong *result* gets caught. Both are
needed: every strategic reversal in the project — the re-charter of a 30-session phase, the directive that nothing but
the vendor's objects and the original hand-written assembly may remain untranslated, the in-place history rewrite —
was a human decision at a gate. Between gates the agent does not ask permission for planned work; it logs after each
task and reports at the milestones the plan named.

**Fresh sessions per phase are deliberate context hygiene**, not a limitation. A phase that outgrows one session (the
campaign phases ran 25–30 sessions each) continues through the checkpoint below.

## The session-start protocol, and its budget

Every session begins by reading, in order: the constitution → the digest (every phase's synopsis, every rule's full
text, the corrections, the document map) → the three most recent PhaseEnds → the open phase's `CURRENT_PHASE.md` → for
matching phases, the pinned toolchain triple and the cookbook's index. Then it states the phase, what is done, the single
next task and its recommended effort, lists every rule in full, replays the checkpoint verbatim — and waits. Budget:
about 100k tokens plus the checkpoint (R64). Before the digest existed the protocol read all 32 PhaseEnds (~150k tokens);
the digest replaced that read without losing a rule.

## The checkpoint: written to be replayed, not summarised

The number-one failure mode of a long multi-session agent project is a fresh session misreading a compressed hand-off.
It happened once early — a session read a summary as "done" and nearly closed an open phase — and the cure became a
discipline: the last block of the open phase's log is a **🛑 SESSION CHECKPOINT** that the next session dumps into its
context verbatim and inherits *nothing else* from. It must therefore carry: the narrative of where things stand with
times and hashes; the exact tool invocations and their gotchas; a file inventory; the carried context for every
remaining task; the environment state; and the single next step. It is refreshed after every further stretch of work
("stale is worse than absent"). A dead session's checkpoint is written by its successor *from the transcripts* — the
agents' final verdicts are recoverable from the harness's subagent logs, and a tool exists to harvest them.

The last thirty sessions of the project resumed from the digest and the checkpoint alone without a single question.

## Effort, and who toggles it

The orchestrating agent's reasoning depth is a setting the human controls, and the project mapped it per task
([`docs/effort-map.md`](../effort-map.md)): the deepest setting for phase plans, PhaseEnds, architectural forks and
non-obvious debugging; the highest *persistent* setting for execution whose design is already settled; multi-agent
breadth (many independent items) for surveys, audits and bulk matching. The rule that made this workable is R27:
**every transition is prompted and waited for** — the agent never launches a fan-out on a verbal yes, and never rolls
into a deep task at a shallow setting. Two failures motivated it, both in one day.

## What the human does

Approves plans and milestones; decides direction at the gates; ratifies rules; pushes (R6 — the agent commits, the
human pushes; every irreversible or outward action — a force-push, a repository flip, a message to another project —
is the human's, announced with its exact command and its check, and the session waits for the word that it ran).
Everything else is the agent's.

## The perishable "why"

Two records exist because a fresh session inherits only compressed summaries. The **decision log**
([`docs/decision-log.md`](../decision-log.md), R31) captures every strategic pivot *while fresh*: the context and belief,
what failed, the pivot, the measurement-grounded why, and a hindsight "better path". The **accelerators ledger**
([`docs/accelerators.md`](../accelerators.md)) records each late discovery with when it was found, when it *could* have
been found, and what it would have saved. Both were written during the sessions that learned the lesson (R30), never
backfilled. The retrospective and these chapters were assembled from them, with `file:line` anchors — the project's first
month of transcripts was lost, and everything from that month had to be reconstructed from the files; nothing after it
needed reconstruction. Keep the record in files, not in the conversation.

## What it cost

- The start protocol: ~100k tokens per session (~150k before the digest).
- The per-task commit + log discipline: a few minutes per task; it is what made the retrospective possible and what let
  a bad scaffold be a one-command revert (H4: in-place tools run only on a clean tree).
- The human's time: plan approvals, milestone confirmations, pushes, and the handful of directional decisions — the
  project's own estimate is that ~99% of the work was the agent's.
