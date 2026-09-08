# pa-overlays.md — the fenced blocks decomp-architect appends to ProjectArchitect's stamped files

> **How SETUP uses this file.** Each block below is headed by its **target file**, its **marker** (the heading line the
> installer greps for to make the step idempotent) and the **step** that applies it. The installer appends the block's
> body verbatim to the target (or creates the target when the block says so), fills the copy-time placeholders, and
> writes literal `TODO(phase-N)` text where a generation-time value does not exist yet. Nothing already in a target is
> edited — ProjectArchitect's stamped content stays byte-identical above the marker. The blocks are the shape the source
> project's governance converged on over thirty-three phases, de-specialised.

---

## Block 1 — `phase-ends/DIGEST.md` (CREATE at Step 8; the session-start digest)

Marker: `# phase-ends/DIGEST.md — the session-start digest`

````markdown
# phase-ends/DIGEST.md — the session-start digest (every phase in one page)

> **Purpose.** The Session Start Protocol reads the constitution, the registry (every rule in full), THIS file, the
> three most recent PhaseEnds in full, and `CURRENT_PHASE.md`; it does not read every PhaseEnd once more than three
> exist. This file therefore carries a synopsis of every phase and the corrections that supersede parts of the
> permanent constitution. The PhaseEnd files stay the durable record — read an older one on demand when a synopsis
> is not enough. **Maintenance:** at every PhaseEnd, append that phase's synopsis here (a phase-close checkbox).
> This file is DERIVED from the PhaseEnds and may be corrected; the constitution is never edited.
> Installed by decomp-architect on {{INSTALL_DATE}}.

## 0. Where the project stands (at the latest PhaseEnd — the live state is in CURRENT_PHASE.md)
(one paragraph, rewritten at every PhaseEnd: the last milestone met, the numbers as generated, what is next)

## 1. Corrections and supersessions of the constitution recorded in PhaseEnds
(one bullet per correction: what the constitution says, what is true now, which PhaseEnd recorded it)

## 2. Phase synopses (what each phase delivered, its key finding, the rules it added)
**P0 (date, version) Governance install + the decomp kit.** …
(one paragraph per phase, appended at its close)

## 3. Where things live (the document map a session needs)
(the wiki's reference index first; then the files a session touches most: the ops reference, the cookbook and its
index, the codegen map, the wave runbook, the effort map, the decision log, the accelerators, the address ledger,
the formats, the pinned-walls list, the archived worklogs — on demand only)
````

---

## Block 2 — `phase-ends/CURRENT_PHASE.md` (APPEND to ProjectArchitect's template at Step 8; the replayable checkpoint)

Marker: `## 🛑 SESSION CHECKPOINT`

*Appended to `phase-ends/CURRENT_PHASE.template.md` so every phase's working file ends with it; the block is REWRITTEN
after every task (the per-task log entry above it is appended, the block is replaced). A fresh session replays it
verbatim and inherits nothing else.*

````markdown
## 🛑 SESSION CHECKPOINT — Tasks [done] ✓; NEXT = task [N] ([one line]; **[effort]** — prompt the developer)

### 0. How to use this block
You are a FRESH SESSION that has read the constitution, the registry, `phase-ends/DIGEST.md`, the three most recent
PhaseEnds and this file, and nothing else. Replay this block verbatim, state phase / done / NEXT / effort, recite the
rules, then WAIT for the developer. Rebuild the harness task list from the checklist above, marking the done tasks
completed and task [N] in progress.

### 1. Where we are
[Phase, version, gate-1 date and effort setting; baseline HEAD and every task's commit hash; the fleet's green count
from the last clean run ("tree-clean" and "fleet-green" are different invariants — quote both); what is tracked and
what is scratch; what is ALREADY banked for later tasks (so nothing is redone); what is running in the background
(or "nothing"); the session number; the developer's effort at the end of the last session and the effort the next
task needs.]

### 2. What NEXT does (task [N], **[effort]**) — exact steps
Read first: [every file, with the section to read and why].
Write / run: [numbered steps with the exact commands, their gotchas, and the expected outputs].
Verify: [the exact checks and their expected literal results]. Log + checkpoint; commit by explicit path. [The effort
transition after this task, if any — prompt the developer.]

### 3. Standing facts for every task of this phase
- One commit per task, after this file's log line; commit by explicit path; no trailers; the developer pushes.
- [the phase's invariants: what is never edited, what is never run, the checks that must stay green, the vocabulary]
````

---

## Block 3 — `phase-ends/PhaseEnd.template.md` (APPEND at Step 8; the narrative axis)

Marker: `## What we believed, what failed and why it looked right, what it cost, and what we would do sooner`

*Appended to ProjectArchitect's PhaseEnd template between "Rules Added This Phase" and "PhaseEnd Changelog". The
source project's retrospective was rebuilt from exactly this section of every PhaseEnd because the transcripts of its
first month were lost; the terse "what changed" record survives a context boundary, the WHY does not.*

````markdown
## What we believed, what failed and why it looked right, what it cost, and what we would do sooner

*(For the retrospective. Narrative, not a table; every cost with its denominator; the detail is in the decision log.)*

- **Believed:** [what the phase assumed at its plan]. **True / false:** [what was actually the case]. **Sooner:** [what
  would have found it earlier — a control, a tool, an order of work].
- **Failed, and why it looked right:** [the failure; the reason it was not caught the same day].
- **Cost:** [tokens, sessions, rework — of what].
````

---

## Block 4 — `docs/effort-map.md` (APPEND at Step 8; the decomp per-phase rows)

Marker: `## Per-phase effort map (decomp ladder — decomp-architect)`

````markdown
## Per-phase effort map (decomp ladder — decomp-architect, installed {{INSTALL_DATE}})

*The Max shortlist is the set of judgments whose silent error would poison everything downstream; the rest of a phase
runs at the baseline; breadth is the same analysis across many independent items.*

| Phase | Mandatory-Max tasks | Fine at xHigh | Breadth (fan-out) |
|---|---|---|---|
| Phase Start (any) | the plan itself (always Max) | — | wide surveys feeding the plan |
| 1 extraction + manifest | the container/compression semantics when they are ambiguous | the extractor, the manifest, the cross-validation | a fleet-wide format audit |
| 2 oracles + load map | every load-address derivation; the segmentation decision (the forced boundaries) | the database import, the text export, the emulator bridge | a survey of every payload's loader route |
| 3 the all-assembly baseline | the linker-script/layout diagnosis when the first link is red | the build pipeline, the contracts | — |
| 4 the compiler pinned | **the fingerprint verdict** (the triple, the flags, per-module variation) | the probe wrappers, the differ wiring | the candidate ladder run as parallel probes |
| 5 census + harness | the census's shape reading (what the strategy will be built on) | the scanners, the reports | the fleet-wide census; the differential harness's pairs |
| 6 the multipliers | the reconcile ladder's design; any "class is dead" verdict | signatures, propagation, families, carves | mass propagation and remaps |
| 7 the map + the permuter | **reading the compiler's source into the map**; the plateau classifier's classes | the dump scripts, the permuter wiring | probes across many constructs |
| 8 the campaign | the routing cliff; **every wall verdict**; the harvest distillation's vocabulary | cards, packs, lanes, gates, recovery | bulk drafting; the harvest over a wave's reports |
| 9 publish | the contract run's design; any irreversible repository operation (rehearsed) | the publisher, the badges, the README | the fresh-clone proof on a second machine |
| 10 readability | struct unification decisions; every name that asserts meaning | pins-off by family; formatting | family-batched pin removal, gated |
````

---

## Block 5 — the cookbook `docs/{{COOKBOOK_NAME}}` (APPEND at Step 8; the entry shape and the triage table)

Marker: `## The decomp entry shape (decomp-architect)`

````markdown
## The decomp entry shape (decomp-architect, installed {{INSTALL_DATE}})

Every idiom entry is byte-proven on a named function and carries four parts:

1. **The residual** — what the diff looks like (the tell): the instruction, its position, the register, the count.
2. **The mechanism** — which compiler pass produces it and why, with the dump line that shows it (a verdict without a
   pass and a dump line is a hypothesis).
3. **The lever** — the C-level change that moves it, stated as a shape (never a register pin as the answer; a pin is a
   symptom). Before a lever enters this file, strip it from the accepted body and recompile: about one credited lever in
   three is inert.
4. **The byte proof** — the function, the diff before and after, the compilation the claim survived (standalone /
   real translation unit / whole-binary).

Pinned context for every entry: the toolchain triple `{{TOOLCHAIN_TRIPLE}}` (TODO until Phase 4); the SDK evidence
({{SDK_EVIDENCE}}); the target's calling convention and register roles (TODO(phase-4)).

### The triage table (symptom → section) — the index a worker greps

| Tell in the diff | Likely mechanism | Lever family | Section |
|---|---|---|---|
| a temporary in a spill slot | a reload artifact | reshape the live range; declaration order | TODO |
| every small edit moves 20+ instructions | a register-pressure lock | hand to the permuter | TODO |
| a load stuck below a store while other loads float | an aliasing decision | the source's aliasing facts | TODO |
| a phantom callee-saved register | cross-call value caching / the allocation order | count the uses; re-shape | TODO |
| a shift off by ×4 against the target | the scaffold's pointer arithmetic | cast through a byte pointer | TODO |
| a branch's arms swapped | branch polarity | put the fall-through block in the `if` | TODO |
| a cross-jumped tail merged or not merged | the cross-jump count law | shape the shared block count | TODO |

*(Grow this table as the cookbook grows; a tool asserts every section is indexed and every index entry resolves.)*
````

---

## Block 6 — `docs/wave-playbook.md` (CREATE at Step 6; the campaign procedure skeleton)

Marker: `# The wave playbook — the operating procedure for the matching campaign`

````markdown
# The wave playbook — the operating procedure for the matching campaign

> ONE document is the procedure: read it before every run, keep it current in the same change as any tool it names;
> a superseded procedure gets a banner. Each guard below is paired with the MEASUREMENT that earned it — fill the
> measurement column from your own waves; the source project's are in the kit's methodology (the calibration fences).
> Created by decomp-architect on {{INSTALL_DATE}}.

| # | Step | The guard | The measurement that earned it |
|---|---|---|---|
| 0 | Preconditions | tree clean; the last clean fleet run green | (fill) |
| 1 | Draw | exclude what cannot bank; audit the exclude list first (it records what the TOOLING could not do); rank by open templatable instructions; know face mass vs delivered mass | (fill) |
| 2 | Cards | the banked twin found over the WHOLE world goes on the card; a card names only levers the base contains | (fill) |
| 3 | Packs | one per target + the shared laws file, at the paths the drafting prompt reads | (fill) |
| 4 | Validate | never hand-type a target; assert every target is still open at draw time; near-misses to the permuter first | (fill) |
| 5 | Draft | one agent per target, model by measured size, streaming not batched; the wave's difficulty is a draw-time knob | (fill) |
| 6 | Gate | everything in parallel (worktrees; the executable by a clean rebuild); gate the DIRECTORY, never the verdict list; assert banked + failed + no-verdict == drafts | (fill) |
| 6b | Reconcile | one deterministic pass over each gate group's slate BEFORE the rebuild | (fill) |
| 7 | After ANY bank | the twin rescan, then commit | (fill) |
| 8 | Harvest — a hard gate | every idiom into the cookbook + index; every mechanical idiom into a sweep that banks the free functions; the widening review | (fill) |
| 9 | Verify the fleet | a clean rebuild of everything; read the exit code | (fill) |
| 10 | Checkpoint | refresh the replayable block; stale is worse than absent | (fill) |

Then **recover** before re-drawing: triage the gate's failures into body and plumbing; bank the plumbing rejects through
the reconcile ladder without a redraft; the gate number is not the close rate until recovery has run.
````

---

## Block 7 — `config/decomp-hooks.snippet.json` and `config/mcp.json.template` (CREATE at Step 8; activated at Phase 2)

*ProjectArchitect already wrote the `SessionEnd` backup hook into `.claude/settings.json`. The kit does NOT merge a hook or an
MCP entry at Phase 0.5 — a hook that runs a stub every session and an MCP client entry pointing at nothing would only add
noise and prompts. It installs the two snippets below as config templates; Phase 2 (the oracles) writes the server-start
script, merges the hook (add only absent keys, validate the JSON afterwards) and copies the MCP template to `.mcp.json` with
the real loopback endpoint. Generation-time values are written as `TODO(phase-2)` at install.*

````json
{
  "hooks": {
    "SessionStart": [
      {
        "hooks": [
          {
            "type": "command",
            "command": "bash \"$CLAUDE_PROJECT_DIR\"/tools/disassembler_mcp_start.sh"
          }
        ]
      }
    ]
  }
}
````

````json
{
  "mcpServers": {
    "disassembler": {
      "type": "sse",
      "url": "{{DISASSEMBLER_MCP}}"
    }
  }
}
````
