# Log mining — Phase29-1of4
Files/ranges: `phase-ends/logs/Phase29.md:1-2580` (read through :2619 for context; only :1-2580 reported)  ·  Lines read: 2580 of 2580
Candidates considered: 46 · NEW: 6 · ALREADY-BANKED: 40

Grep set used for every "already banked?" test (abbreviated `<all>` below):
`docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md docs/retrospective.md docs/wave-playbook.md docs/how-to-ai-decomp/*.md decomp-architect/corpus/decomp-kernels.md decomp-architect/templates/registry-E.decomp.md phase-ends/DIGEST.md`
(the 3.5 MB cookbook was only ever grepped, never read).

## NEW

### C1 — A stop/continue instrument must aggregate at exactly the unit the decision is made in; one that averages a finer unit manufactures a false "we are at the floor"
- **Evidence:** `phase-ends/logs/Phase29.md:1283-1288` —
  "`burndown.py` averaged the last 3 INTER-COMMIT deltas, but the ROI criterion is per-SESSION yield. Three mid-session
  snapshots of a **+0.7pp** session averaged to **+0.23** and printed **"AT THE FLOOR — consider closing P29"**.
  **I nearly closed the phase on it.**"
- **What happened / what it cost:** The phase's exit condition was "per-session yield floors out", but the instrument built
  to decide it sampled at commit granularity, so one productive session read as three weak ones and printed a close-the-phase
  verdict that was believed until re-derived. Fixed by an explicit `--session-close` boundary marker plus an honest
  "0 SESSION-to-SESSION delta(s) logged — need >=3" output, and thereafter every checkpoint had to carry "DO NOT close
  P29 on ROI — the floor is undetermined". The same granularity error recurred (`:1918-1921`, a `--session-close` logged
  mid-session by mistake), i.e. it is a repeating shape, not a one-off.
- **Not banked — greps:** `grep -rn -i -c 'burndown' <all>` → 0; `grep -rn -i -c 'per-session yield' <all>` → 0;
  `grep -rn -i -c 'stopping criterion' <all>` → 0; `grep -rn -i -c 'at the floor' <all>` → 1 (cookbook:30292, a scheduler
  prologue "floor", unrelated); `grep -rn -i 'burn-down' <all>` → 2 (decision-log:1680 records the phase's *state*,
  "the burn-down floor is still undetermined", never the lesson).
- **Proposed home:** DK (a kernel), with an accelerators cross-reference
- **Portable because:** every long decomp needs a "when do we stop this track" instrument, and the failure mode — sample at
  commit/day granularity, decide at session/phase granularity — is independent of console, compiler and harness.

### C2 — Batch size is a RISK lever, not a token lever: isolated agents cost ~N× one agent whether concurrent or serial, so size a batch by the unverified spend you are willing to lose before the next measured yield
- **Evidence:** `phase-ends/logs/Phase29.md:2387-2392` —
  "Batch size is a RISK lever, not a token lever: each agent drafts one fn in its own context, so N agents cost ~N× one
  agent whether concurrent or serial (~110k tok/drafted fn, measured s14+s15). Concurrency buys wall-clock only.
  Therefore **batches of ~5–6**: ~600k tokens of exposure per batch, a measured yield before committing the next,
  and a clean stop at any boundary."
- **What happened / what it cost:** This was written after waves of 24 drafters repeatedly produced high draft counts with
  low bank rates (`:1973-1980` 24 drafters → 6 banked; `:2478-2489` a queued wave with **no fuel at all**), i.e. large
  batches bought no efficiency and lost a full batch of exposure per bad premise. The rule pairs with the measured unit
  cost (~110k tok per drafted function; ~460k per banked function before recovery, ~200k after) so batch size becomes a
  budget decision rather than a habit.
- **Not banked — greps:** `grep -rn -i -c 'risk lever' <all>` → 0; `grep -rn -i -c 'concurrency buys' <all>` → 0;
  `grep -rn -i -c 'wall-clock only' <all>` → 0; `grep -rn -i 'batch size' <all>` → 2 (decision-log:2333 / cookbook:16413,
  both making the *different* point that batch size was not the yield discriminator).
  Nearest neighbours checked and distinct: `docs/how-to-ai-decomp/08-models-and-budgets.md:31-33` ("budget per lane";
  "concurrency is a budget" = provider rate limits) and `:70-71` in chapter 08 ("isolated agents for breadth, never serial
  in the main loop" = the orchestrator's quadratic context) — neither states the exposure-sizing rule.
- **Proposed home:** DK (a kernel) or `docs/how-to-ai-decomp/08-models-and-budgets.md` Budgets section
- **Portable because:** it is a property of per-agent isolation and of any pay-per-token fan-out, and it converts "how big a
  wave?" from taste into an explicit loss cap.

### C3 — A repair/`--recover` mode whose cost is (exceptions × population) must be gated on a MEASURED exception count; for a broadly divergent set, drop rather than recover
- **Evidence:** `phase-ends/logs/Phase29.md:1635-1639` —
  "`dedup_propagate --recover` on func_80169228 (many byte-divergent stragglers) THRASHED >1hr (re-gates the fleet per
  excluded straggler = quadratic). Killed + reverted 326 half-mutated files … **LESSON: --recover is only for a FEW
  stragglers; a broadly-divergent family must be dropped or capped, never --recover'd.**"
- **What happened / what it cost:** The recovery flag exists to rescue a handful of exceptions; run against a family whose
  members genuinely diverge, it re-validated the whole fleet once per exception, burned over an hour, and left 326
  half-mutated files that had to be reverted to the committed baseline. Nothing was lost only because the banks had been
  committed before the propagate. Later sessions consistently *dropped* stragglers instead (`:1710-1712`, five dropped,
  "`--recover` is the documented thrash hazard and was NOT used").
- **Not banked — greps:** `grep -rn -i -c 'thrash' <all>` → 0; `grep -rn -i -c 'quadratic thrash' <all>` → 0;
  `grep -rn -i -c 'half-mutated' <all>` → 0; `grep -rn -i -c 're-gates the fleet' <all>` → 0.
  (`--recover` itself appears 11× in the cookbook, always as *how to use it* — e.g. `:2451`, `:2471`, `:2499`, `:4193` —
  never with its complexity or its stop condition. `straggler` hits in wave-playbook/how-to are about wave tails.)
- **Proposed home:** accelerator (with a cookbook cross-reference at the §55b propagation law)
- **Portable because:** every mass-application tool acquires an "and fix up the exceptions" mode, and the shape
  (per-exception full re-validation) is the default naive implementation on any project.

### C4 — A defect reasoned into a sibling tool is LATENT until a run shows its signature; do not patch it on theory right after that tool produced a clean run
- **Evidence:** `phase-ends/logs/Phase29.md:1191-1196` —
  "`jtbl_family_bank` isolates AROUND THE STUB … the same ordering defect just fixed in `harvest_verify`. It did **not**
  fire across 274 swept siblings this session … so it is latent, not universal; fixing it on theory after a 274/274 run
  would be the very error this phase keeps catching. **Fix it when a sweep fails with the signature (isolation fires →
  gate DIFF), not before.**"
- **What happened / what it cost:** After root-causing a real ordering bug (the transform must follow the splice) the same
  shape was visible by inspection in a second tool that had just completed 274/274 siblings byte-identical. The judgement
  recorded is to *name the signature and wait* rather than mutate a currently-correct mass tool — the phase had repeatedly
  paid for edits made on theory (e.g. the fleet-wide `--revert` that broke 138/140, `:97-105`).
- **Not banked — greps:** `grep -rn -i -c 'latent, not universal' <all>` → 0; `grep -rn -i -c 'on theory' <all>` → 0;
  `grep -rn -i -c 'fix it when.*fires' <all>` → 0; `grep -rn -i 'did not fire' <all>` → 2 (cookbook:7615 and :21268, both
  about a compiler mechanism not firing, not about deferring a tool fix).
- **Proposed home:** DK (a kernel) — it is the deliberate counterweight to "fix the class, not the instance"
- **Portable because:** every project reaches the moment where one fixed tool implies a bug in its sibling, and the choice
  between speculative patch and signature-triggered patch is the same on any codebase.

### C5 — Sweep for orphaned worker processes at every session boundary; a dead-pipe compiler or a self-matching wait loop holds a core forever and nothing reports it
- **Evidence:** `phase-ends/logs/Phase29.md:1029-1030` — "killed an orphaned `cc1` from the Jul-21 session that had been
  burning a full core for **13h23m** (pid 104350, dead pipe)"; and `:1289-1292` — "I left two `while pgrep -f <pat>; do
  sleep; done` waiters spinning (one for 4 h) — they self-match their own `bash -c` command line and can never exit."
- **What happened / what it cost:** Two independent leak shapes in one phase — a compiler child left alive by a killed
  parent's dead pipe, and shell wait-loops that can never terminate because their pattern matches themselves — each
  silently consuming a core across sessions on a machine whose parallelism is the project's throughput. Neither is
  reported by any gate, health check or tool: the tree is clean, the fleet is green, and the box is just slower.
- **Not banked — greps:** `grep -rn -i 'orphan' <all> | grep -iE 'process|cc1|worker|pid|core|cpu'` → 0 relevant (all 89
  cookbook hits are orphan *registers/slots/notes*); `grep -rn -i -c 'leftover process' <all>` → 0;
  `grep -rn -i -c 'ps aux' <all>` → 0; `grep -rn -i -c 'consuming a core' <all>` → 0. (`R79`/`accelerators.md:197` cover
  `pkill -f` killing the *calling shell*, and cookbook:5328 covers a `pkill` pattern killing *sibling runs* — neither is
  the leaked-process sweep.)
- **Proposed home:** accelerator (a session-boundary checklist item, next to the tree-clean / fleet-green checks)
- **Portable because:** any project that spawns compilers, searches or workers from an agent harness leaks them the same
  way, and the cost scales with how much of the schedule is CPU-bound.

### C6 — Land a pure rename and a semantic/layout change as separate gated edits, so a gate failure attributes itself
- **Evidence:** `phase-ends/logs/Phase29.md:1959-1962` — "`VECTOR` left UNCHANGED deliberately: ours is 12B vs PsyQ's 16B …
  vx/vy/vz offsets already agree so a fix is likely byte-neutral, but it is a LAYOUT change and must not be bundled with a
  rename (an R22 failure would then be ambiguous about which caused it). Own commit, later."
- **What happened / what it cost:** In the same task a 205-file pure rename (swapping which name carries the true PsyQ
  `MATRIX` layout) went through the full-fleet gate green, precisely because it was *only* a rename; the layout question was
  deferred to its own gated change. Recorded as a rule rather than a cost — the phase had, however, just paid for the
  opposite shape (`:1680-1685`, a type selector that changed layout for 103 overlays under an edit believed to be a
  consistency fix, caught only by the full-fleet gate at 37/140).
- **Not banked — greps:** `grep -rn -i -c 'bundle.*rename' <all>` → 0; `grep -rn -i -c 'rename.*layout change' <all>` → 0;
  `grep -rn -i -c 'one variable at a time' <all>` → 0; `grep -rn -i -c 'ambiguous.*R22' <all>` → 0; `grep -rn -i 'own commit'
  <all>` → 5 (all unrelated: decision-log:3463 the purge commit, cookbook:8680 `tables=` authority, etc.).
- **Proposed home:** G (a rule) or the byte-gate how-to chapter
- **Portable because:** it is a property of any single-bit oracle (byte-identical / not): two changes in one gated edit make
  a red result uninterpretable, and byte-neutral refactors are exactly where the temptation to bundle appears.

## ALREADY-BANKED (one line each)
- A shared fixed scratch path silently clobbers itself under parallelism (14 of 1,752 drafts lost, invisibly, in every parallel wave ever run) — `docs/matching-cookbook.md:4499` and `:9058`
- Wrapper/pipeline exit status lies (`| tail` masks make; `grep -c` returns 1 on no match); read the gate's own output line — `docs/matching-cookbook.md:6620`, §93 `:6956`, §136a `:9010`
- "Twice, identically" is two reads of one contaminated state, not a replication; re-apply a fault from a known-clean tree before recording it as a mechanism — `docs/decision-log.md:1457-1493`
- A failure classifier that scans whole stderr latches onto a benign warning and returns a CONSTANT label, which carries no information — `docs/matching-cookbook.md:4840`
- An undo whose scope is narrower than the stage's write scope destroys work no byte-gate can see; declare and assert each stage's blast radius — `docs/matching-cookbook.md:4864`, `:5075`; `decomp-architect/corpus/decomp-kernels.md:878`
- A per-item gate is structurally blind to shared-state damage (it was RIGHT about its one binary while 137 were broken) — same blast-radius entries, `docs/matching-cookbook.md:4864`
- A truthy `or DEFAULT` fallback made the gate compare one binary against another's hash for a month; two callers of one oracle that disagree ARE the bug report — `docs/decision-log.md:1499-1530`
- Rank remaining work by LIVE (still-open) siblings, not by total reach; `nins×reach` over-counts — `docs/decision-log.md:1636-1672`
- Reconcile toward the byte-truth, not toward the incumbent declaration (the header was the simplified side) — `docs/matching-cookbook.md:4920`; and a shared-header edit is fleet-blind under a per-binary gate — `docs/decision-log.md` §63 UPDATE entries
- A drafting agent must copy its winner back to a canonical path with an existence check (24 winners nearly lost to scratch filenames; recovered from transcripts) — `docs/how-to-ai-decomp/05-cards-lanes-waves.md`, `docs/wave-playbook.md`, `docs/accelerators.md` (`agent_drafts_restore`)
- A pre-filter is evidence ONLY about what it filtered — pre-filter on a unit that FAILED — `docs/decision-log.md:1868`
- R14 applies to your own 3-line scripts: two produced false evidence before any project tool did — `docs/decision-log.md:1867`
- Different types sharing one identifier must be UNIQUIFIED, never merged to a canonical layout (merging broke 103 overlays); types-first does not help matching, a draft-time naming convention (address-suffix inventions; forbid bare generic names) would have saved a session; seed the documented SDK types on day one — `docs/decision-log.md:1875-1903`, kernels `:798-815`
- The carve must FOLLOW the splice — and so must the isolation — `docs/matching-cookbook.md:4699`, `:4836`, `:4869`
- The widest write in a pipeline is the one most likely to be undeclared, and a containment guard measured from `git status` is blind once anything commits — cookbook §66a
- A metric scraped from another tool's prose goes NULL silently on a label change (50 commits recorded `fleet None%`) — cookbook §66b
- A selection tool whose candidate set derives from the wrong directory manufactures both false work and false exhaustion — `docs/matching-cookbook.md:5263` (§66c)
- `pkill -f <pattern>` matches every concurrent run and silently kills siblings — `docs/matching-cookbook.md:5328`; the self-kill variant `docs/accelerators.md:197`, `phase-ends/DIGEST.md:295` (R79)
- A carried "do not re-derive" claim can be inverted and its preserved probes vacuous; a probe whose output does not contain the phenomenon proves nothing — `docs/decision-log.md:1369-1403`
- Blockers STACK and the compiler reveals only the FIRST; route by the static oracle's complete list — `docs/matching-cookbook.md:5058`, `:8843`
- Persist a search's winner durably BEFORE the step that consumes it; a tool that has been failing for a long time accretes latent bugs on its success path, so budget for the first success to fail — `docs/matching-cookbook.md:4539-4542`
- Two implementations of one capability, the outer one ineffective AND destructive → delete, don't patch — `docs/matching-cookbook.md:4837`
- Staging ≠ banking; a classifier's `n_templatable`/PURE verdict is a PREDICTION the gate is free to refuse — `docs/matching-cookbook.md:4364-4368`; "is a PREDICTION" also in `docs/accelerators.md`, kernels
- Ladder/scratch dirs that ACCUMULATE across runs silently widen a stage's input set (it banked a function it was never asked to try) — `docs/matching-cookbook.md` ("accumulates across runs", "banked a function it was never asked")
- A revert that restores tracked config but not derived artifacts leaves a tree GIT-CLEAN BUT UNBUILDABLE; a reverted config needs a re-extract — `phase-ends/DIGEST.md:191`, `decomp-architect/templates/registry-E.decomp.md:72`, `docs/accelerators.md:445`
- Regenerate digests on a clean tree — `docs/matching-cookbook.md:5248`
- Cracking GENERATES sweep fuel (sweeps only pay riding a fresh ×1 crack) — and it is family-specific, not a blanket ×N — `docs/decision-log.md:1543-1561`
- Census the corpus SHAPE (duplication, families, reach × size, the unique tail) before choosing a strategy; the ×N economics end and a ×1 tail remains — kernels DK-8 `decomp-architect/corpus/decomp-kernels.md:108-118`
- Attemptable work is bounded by decompiler-cache coverage; high-reach fuel is created by a per-target import (greedy cover), not found — `docs/decision-log.md:1639-1641`, `:1731-1740`
- Never foreground-build while a background clean-fleet verification runs (phantom pass); isolate builds — `docs/how-to-ai-decomp/02-byte-gate.md:43-45`, cookbook concurrent-splice entries `:27784`, `:28729`
- An A/B whose treatment arm receives already-treated input establishes nothing (the ablation is confounded) — `docs/matching-cookbook.md:12938`, `:14277`, `:15921`
- A wrapper that swallows its child's diagnostics makes the failure undiagnosable (swallowed-error class) — `docs/retrospective.md:47`, `docs/how-to-ai-decomp/02-byte-gate.md:30`, `docs/decision-log.md:1141`
- A relocation-masked proxy oracle's validity is CLASS-DEPENDENT (trust it for self-decl fixes, distrust it for callee ones) — cookbook §65c
- A shared-state wall can have a per-unit local escape (de-macroize the instantiation in this overlay's own TU) — cookbook §65b, and the §20 DEF-conflict refutation
- The wave bottleneck is INTEGRATION, not idioms (~92% of drafts byte-correct, ~27% banked) — kernels DK-7 `decomp-architect/corpus/decomp-kernels.md:96-106`
- A tool that cannot handle a class must REFUSE loudly and say that a 0% from that path is a TOOL ARTIFACT, not a wall — R43 / `phase-ends/DIGEST.md`
- Read the FINAL SHA, not the verified count: `None` = no image; a real hash ≠ locked = the edit moved bytes — cookbook §65f
- A "byte-neutral" transform measured neutral 14 of 15 times is not byte-neutral — cookbook §65f
- Commit the cheap verified banks BEFORE the expensive propagate, or a propagate failure takes the banks with it — cookbook §55b (and R42 in `phase-ends/DIGEST.md`)
- Trust the SOURCE, not the report (`grep INCLUDE_ASM`, never the tool's "banked: N") — cookbook §55b trap 4, R66/`phase-ends/DIGEST.md`
