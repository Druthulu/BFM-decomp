# Log mining — Phase31-3of3
Files/ranges: `phase-ends/logs/Phase31.md`:5805-8705 (read from 5775 for context)  ·  Lines read: 2931 of 2931 (assigned range 2901 of 2901)
Candidates considered: 30 · NEW: 7 · ALREADY-BANKED: 23

> `$F` below = `docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md
> docs/retrospective.md docs/wave-playbook.md docs/how-to-ai-decomp/*.md decomp-architect/corpus/decomp-kernels.md
> decomp-architect/templates/registry-E.decomp.md phase-ends/DIGEST.md`. Every grep was
> `grep -n -i -c -- '<phrase>' $F` (hit counts per file), followed by reading the surrounding lines of any hit.

## NEW

### C1 — Never wrap a project tool in a `timeout` shorter than its own internal budget; you pre-empt its documented recovery handler and lose its buffered output
- **Evidence:** `phase-ends/logs/Phase31.md:7024-7027` —
  "**Never wrap a project tool in a shorter `timeout` than its own budget.** My `timeout 2400` beat
  `gate_stage`'s 3600 s budget, SIGTERM'd the tree mid-propagation, and Python lost its buffered
  stdout — three gates with NO verdict and three half-applied, never-byte-gated propagations."
- **What happened / what it cost:** The session wrapped each gate in `timeout 2400` while `gate_stage`'s own budget was 3600 s. When `dedup_propagate` ran long the wrapper killed the tree; three gates produced no verdict at all and three propagations were left half-applied and never byte-gated (`:6891-6898`). `gate_stage` has a handler for exactly that state ("*the fleet is HALF-PROPAGATED and the tree is DIRTY. Revert, then re-gate with `--no-propagate`*") and the shorter external deadline pre-empted it. Recovery cost the evening; the documented recovery then ran clean, 5/5 in minutes each.
- **Not banked — greps:** `grep -n -i -c -- 'shorter timeout' $F` → 0; `grep -n -i -c -- 'timeout 2400' $F` → 0; `grep -n -i -c -- 'buffered stdout' $F` → 0; `grep -n -i -c -- 'own budget' $F` → 1 (cookbook:33494, about agents running to their own token budget); `grep -n -i -c -- 'SIGTERM' $F` → 1 (cookbook:2362, run `dedup_propagate` in the background — the opposite direction, no rule about nesting deadlines).
- **Proposed home:** DK (a kernel) — belongs beside the "a slow gate is a bug" / harness-hygiene kernels.
- **Portable because:** every decomp harness wraps long tools (gates, propagation, extraction) in supervisors, CI steps and agent timeouts; a nested deadline that fires before the tool's own defeats every graceful-recovery path the tool was given.

### C2 — A programmatic edit to a long-lived knowledge document silently truncates or duplicates it; verify the sections, never the commit
- **Evidence:** `phase-ends/logs/Phase31.md:6529-6533` —
  "**§429 had been SILENTLY DELETED from the cookbook.** My §428a rewrite wrote `t[:start] + new`
  instead of `t[:start] + new + t[end:]`, truncating everything below it … **When editing a doc by
  index slicing, re-read the tail.**"
- **What happened / what it cost:** One index-slice rewrite dropped the whole tail of the 3.5 MB cookbook; §429 was gone for the rest of the session and had to be restored from an old commit. The same class recurred twice more: `:7307-7308` "**§462, §463 and §464 silently vanished from the cookbook** after their commits. Restored; … **Verify each section, not the commit.**", and `:8351-8352` "the S78 and S79 blocks share every section heading, and `str.index` on a heading **duplicated a region twice this session**". Sections written that day were the same ones cracking functions that afternoon, so the loss was live knowledge, not archive.
- **Not banked — greps:** `grep -n -i -c -- 'index slicing' $F` → 0; `grep -n -i -c -- 're-read the tail' $F` → 0; `grep -n -i -c -- 'verify each section' $F` → 0; `grep -n -i -c -- 'duplicated a region' $F` → 0; `grep -n -i -c -- 'silently deleted' $F` → 1 and `'silently vanished'` → 1 (cookbook:27967 a DCE'd inline-asm draft; cookbook:35044 nop-padded tails vanishing from a disassembly — neither is about editing the knowledge base).
- **Proposed home:** G (a rule) for the knowledge-base chapter — the flywheel's own write path needs a read-back assertion.
- **Portable because:** any project whose knowledge base is one enormous append-only markdown file will edit it by offset with a script or an agent; the failure is silent, the loss is the most recent (most valuable) content, and the commit looks perfect.

### C3 — The live hand-off block must be strictly APPENDED at the end of its file: file order is the only recency signal a fresh session has
- **Evidence:** `phase-ends/logs/Phase31.md:6126-6128` —
  "> **The \"last block is the live one\" rule was BROKEN when this session started** — S70 FINAL-5 sat
  > below S71 CLOSE in file order while being a day older. This block is appended at the END, which
  > restores the rule. Keep appending."
- **What happened / what it cost:** Checkpoint blocks were written into the phase log in a place other than the end, so a newer block sat *above* an older one. A fresh session that follows the standing "read the last 🛑 block" instruction would have inherited a day-old state as current. The fix was mechanical (always append) plus, later in the file, an editing rule for the same file: `:8459-8460` "EDIT THE LIVE BLOCK THROUGH A SLICE FROM ITS OWN HEADER (`s.rindex('## 🛑 SESSION CHECKPOINT — S79')`), the blocks share headings".
- **Not banked — greps:** `grep -n -i -c -- 'last block is the live one' $F` → 0; `grep -n -i -c -- 'SUPERSEDES every earlier block' $F` → 0; `grep -n -i -c -- 'supersedes' $F` → 9 (cookbook/playbook/decision-log, all about one cookbook section superseding another); `grep -n -i -c -- 'checkpoint block' $F` → 1 (registry-E:374 G59 — the checkpoint is written to be replayed: content, not position); `grep -n -i -c -- 'last block' $F` → governance:77 states the discipline but not the ordering invariant or its failure.
- **Proposed home:** G (a rule) — a one-line amendment to G59.
- **Portable because:** every long agent project hands off through an append-only log; the "read the last block" convention is worthless the moment anything is inserted, and the failure is invisible to the writer and fatal to the reader.

### C4 — A long stateless batch must persist each confirmed result the moment it is confirmed
- **Evidence:** `phase-ends/logs/Phase31.md:7121-7124` —
  "**`gate_main` writes banks only at the END.** `try_batch` is stateless — every attempt is
  `git checkout` main's TUs → `make extract` → substitute → build — so a 34-minute bisection holds
  its result in memory and a kill loses all of it. Writing each confirmed match immediately is the
  single highest-value gate improvement available."
- **What happened / what it cost:** main's gate re-derives its whole world per attempt and only commits at the end, so a bisection that takes over half an hour is one interruption away from total loss — and interruptions were routine that week (context exhaustion, an over-short `timeout`, a harness kill). The session named it the highest-value gate improvement on the board, and the durability journal shipped a session later (`:7288` "`gate_main` (durability journal + verbatim refusal)").
- **Not banked — greps:** `grep -n -i -c -- 'writes banks only at the end' $F` → 0; `grep -n -i -c -- 'holds its result in memory' $F` → 0; `grep -n -i -c -- 'durability journal' $F` → 0; `grep -n -i -c -- 'a kill loses' $F` → 0; `grep -n -i -c -- 'try_batch' $F` → 1 (accelerators:238, the `try_batch([])` NULL-INPUT control — a different lesson).
- **Proposed home:** DK (a kernel) — a design property of any expensive gate.
- **Portable because:** every byte-gate loop on a large binary is minutes-to-hours per batch and runs inside agent sessions that die; a result that exists only in a process's memory is a result you will pay for twice.

### C5 — "Idempotent by SKIPPING" seals an artifact against later evidence; make regenerated artifacts idempotent by REPLACEMENT
- **Evidence:** `phase-ends/logs/Phase31.md:6171-6174` —
  "**`journal_notes.py`** — was idempotent by SKIPPING, so a pack with one old note could never
  receive a newer one, and `claude_wave_packs` calls it at build time, so **every pack with any
  history was sealed against later evidence**. Now idempotent by replacement."
- **What happened / what it cost:** The project's whole flywheel thesis is that each session's new evidence reaches the next wave's packs. A skip-if-present idempotence guard meant that any target that had ever received a note was frozen at its FIRST note — silently, at pack-build time, for every historical target. The fix paid within the hour: "the §428 escalation note reached `func_8001B0D4`'s pack only because of this" (`:6174-6175`).
- **Not banked — greps:** `grep -n -i -c -- 'idempotent by skipping' $F` → 0; `grep -n -i -c -- 'idempotent by replacement' $F` → 0; `grep -n -i -c -- 'sealed against' $F` → 0; `grep -n -i -c -- 'idempoten' $F` → 15 (playbook:308 "back-fill … (idempotent)", cookbook:33397 "Idempotent (never appends twice)", etc. — all assert idempotence as a virtue, none records that the skipping form freezes stale content).
- **Proposed home:** G (a rule) or a kernel line beside the pack/journal machinery.
- **Portable because:** every AI-decomp harness regenerates derived context (packs, briefs, notes, indexes) and reaches for an idempotence guard; the skipping form is the obvious one and it silently converts a compounding knowledge loop into a write-once one.

### C6 — A verification target too slow to complete is not a check: sample it by default and keep the exhaustive form as a separate target
- **Evidence:** `phase-ends/logs/Phase31.md:6027-6029` —
  "**`make tools-health`** — was UNRUNNABLE (>15 min, never once completed). `audit-cdecl` was a
  full-corpus regression test in a health target (~787s of pure-Python collection before the first
  cc1 call). Now sampled (`CDECL_AUDIT_TUS ?= 60`, 61s); `audit-cdecl-full` keeps the exhaustive
  form. **333s green.**"
- **What happened / what it cost:** The project's own tool-health gate had never once run to completion, so every tool defect it would have caught shipped unchecked — in a phase whose defining finding was that essentially every "codegen wall" was an instrument defect. The remedy was not a faster machine but a split: sample in the health target, keep the exhaustive run behind its own name.
- **Not banked — greps:** `grep -n -i -c -- 'unrunnable' $F` → 0; `grep -n -i -c -- 'never once completed' $F` → 0; `grep -n -i -c -- 'a health target' $F` → 0; `grep -n -i -c -- 'too slow' $F` → 0; `grep -n -i -c -- 'audit-cdecl' $F` → 2 (decision-log:1574, cookbook:3870 — both about what the check *does*, not about it being unrunnable). The nearest banked relative is `decomp-kernels.md:439` "a slow gate is a bug", which is about gate throughput, not about a verification target that has literally never finished and therefore verifies nothing.
- **Proposed home:** accelerator (or a clause appended to the "a slow gate is a bug" kernel).
- **Portable because:** every decomp grows a `tools-health`/CI aggregate; the temptation to put the exhaustive corpus regression inside it is universal, and the failure mode is a green-looking check nobody has ever seen finish.

### C7 — Never adopt a subagent's worktree wholesale: it is a snapshot of an older tree and may predate a bank; re-gate its artifacts against HEAD
- **Evidence:** `phase-ends/logs/Phase31.md:6808-6809` —
  "**Never adopt an agent's worktree wholesale.** One predated a bank of `func_8017F9C0`; copying its
  TU would have destroyed it. Re-gate against HEAD with the fixed tools instead."
- **What happened / what it cost:** Drafting agents ran in git worktrees provisioned at their launch time. Merging a finished agent's TU back wholesale would have reverted a function banked in the main tree after that worktree was cut — a silent destruction of byte-proven work that no gate would have flagged (the merged TU builds fine, it just loses a match). The safe move is to take only the agent's draft artifact and re-gate it against current HEAD.
- **Not banked — greps:** `grep -n -i -c -- "agent's worktree" $F` → 0; `grep -n -i -c -- 'predated' $F` → 0; `grep -n -i -c -- 're-gate against HEAD' $F` → 0; `grep -n -i -c -- 'adopt.*worktree' $F` → 1 (accelerators:715-718 — `parallel_gate` banking *into* its worktree and adopting nothing, the opposite direction); `grep -n -i -c -- 'stale worktree' $F` → 3 (DIGEST:291 / registry-E:117, R77: worktrees pinning old commits through a `gc` — a git-hygiene lesson, not a merge-safety one).
- **Portable because:** worktree-per-agent is the standard way to parallelise gating, banking continues in the main tree while agents run, and "just take the agent's tree" is the obvious integration shortcut.

## ALREADY-BANKED (one line each)
- A byte gate is a null oracle for "is this C?" — a verbatim `__asm__` body matches by construction and a scoper ranks it highest-value — lives at `decomp-architect/corpus/decomp-kernels.md:384` (DK-29), `docs/how-to-ai-decomp/12-failure-museum.md:24`, `docs/accelerators.md:702`.
- A documented lever wired into no code path runs for zero targets (`neighbor_ref`, the misplaced laws file) — lives at `docs/wave-playbook.md:231`, `decomp-architect/corpus/decomp-kernels.md:504` (DK-39), `docs/how-to-ai-decomp/12-failure-museum.md:29`.
- A law from a NEAR is a hypothesis; a law from a MATCH is evidence — lives at `docs/matching-cookbook.md:34101`.
- A yield table is evidence; the story about WHY needs its own negative control (§479 rewritten three times in a day) — lives at `docs/decision-log.md:3063`, `docs/matching-cookbook.md:35860`.
- Partition along the structure the original PRODUCER used (symbols), not the one your measurement grouped by (bases) — turned a certified wall into six pieces — lives at `docs/accelerators.md:673-677`.
- Provenance → archive → link → compiler, in that order: a "compiler wall" in bytes no archive you hold can place is a provenance question first — lives at `docs/matching-cookbook.md:36175`, `docs/retrospective.md:31`.
- Reconcile a headline % against its independently-derived remainder; a snapshot denominator drifts (main 59.8% → 91.8%) — lives at `docs/decision-log.md:3109-3113`.
- §474 as the template for a wall claim (name the pass, cite file:line, measure each escape); a NEAR citing a pass + file:line is a wall-proof candidate, not a redraft — lives at `docs/matching-cookbook.md:35577`, `docs/decision-log.md:3028`.
- Triage is free: read the draft's own header before aiming anything at it; the mismatch count predicts nothing — lives at `docs/matching-cookbook.md:35864`.
- When you fix a blindness, enumerate the consumers (the 4th consumer of the verbatim blindness; two worktree provisioners with no shared list) — lives at `docs/matching-cookbook.md` "enumerate the consumers" / "fourth consumer", `docs/decision-log.md` "found twice".
- Assert the scan measured something — a bare `except: continue` gave a confident FALSE verdict over 2,603/2,603 — lives at `docs/matching-cookbook.md:8351` (§126a) and `:34714`.
- A failing gate must preserve its artifact BEFORE any control or cleanup rebuilds over it (the R40 control in the wrong order parked 11 functions) — lives at `docs/matching-cookbook.md` ("save its artifact" / "before any control"), `docs/decision-log.md` (red image).
- A uniform failure shape across independent drafts (same delta, same first mover) is a LAYOUT signature, not N codegen walls — lives at `docs/matching-cookbook.md:33892`.
- Positive-control a fix against a deliberately broken input, not only negative-control it on the unchanged population — lives at `docs/matching-cookbook.md:34758-34760`, `docs/decision-log.md:3191`.
- A second, independent oracle is the only thing that can see a class its sibling is structurally blind to (and it must derive from different evidence) — lives at `docs/decision-log.md:826-830, 873-876`, `docs/matching-cookbook.md:3751`.
- Every bank cascades: it gives the TU a real definition that contradicts the stale `extern` later drafts carry — re-run the sync, do not conclude the draft went bad — lives at `docs/wave-playbook.md` / `docs/matching-cookbook.md` ("every bank gives its TU").
- A tool reading text it should not (comment prose as code, a mid-line block comment, dead `#ifdef` branches as live) was the phase's dominant defect class — lives at `docs/matching-cookbook.md:34446-34453` (§437) and `:34681-34685`.
- Per-TU optimisation-level / build-config gaps block byte-correct bodies (a `-O0` island; `$(filter)`'s exact stem match) — lives at `docs/matching-cookbook.md` ("build-config gap", "compiler-inexpressible") and the -O0 material in `docs/accelerators.md` / `docs/how-to-ai-decomp/03-bootstrap-order.md`.
- A gate's verdict parser is a witness, not a judge (a pre-existing warning read as the error) — lives at `docs/matching-cookbook.md:36363`.
- `config/overlays.mk` + the splat yamls are shared carve STATE; a rejected gate damaged them while `git status src/` said nothing was wrong — lives at `phase-ends/DIGEST.md:245` (R60), `decomp-architect/templates/registry-E.decomp.md:273` (G43), `docs/matching-cookbook.md:34729` (§444).
- Never kill a running workflow to relaunch it differently — add the new tier alongside the dying agents — lives at `docs/wave-playbook.md:554`.
- Run the reject to ground before respelling the body; a reject whose cause you have not named is not evidence about the C — lives at `docs/matching-cookbook.md:34411-34414`.
- Usage limits are a wall class: three frontier agents died on an account-wide limit; check the quota before routing a wave, and treat the death as an instrument failure — lives at `docs/how-to-ai-decomp/08-models-and-budgets.md:42-44`, `docs/wave-playbook.md:507`.
- A claim about another project (the sotn duplicate-function precedent) resting on your own paraphrase must be verified at the source before it becomes doctrine — lives at `docs/decision-log.md:2934-2936`.
- An empty draw pool read as coverage (`draw_waves --main` never iterated main at all) — lives at `docs/decision-log.md:2972`, `:2769-2771`.
- Probe one instance before pricing (the assumed 1–2 min gate cycle measured 16 s) — lives at `phase-ends/DIGEST.md:216` (R37).
- A masked score is not a closeness until the diff is read; agent-tool drafters outlive their session and their verdict is the transcript's last JSON — lives at `phase-ends/DIGEST.md:251` (R63) / `decomp-architect/templates/registry-E.decomp.md:231` (G36), `docs/accelerators.md:720`, `docs/matching-cookbook.md` ("last JSON").
