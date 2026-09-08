# Log mining — Phase29-3of4
Files/ranges: `phase-ends/logs/Phase29.md`:5161-7740  ·  Lines read: 2580 of 2580 (plus 5131-5160 and 7741-7770 read for context only)
Candidates considered: 36 · NEW: 6 · ALREADY-BANKED: 30

Slice content: SESSION-21 T4b→T12, SESSION-22 T13→T30, SESSION-23 T31→T50, SESSION-24 T51→T54
(the family-sweep / decl-axis / codegen-map-audit arc, 82% → 85.7% instr-weighted).

Grep file set used for every "already banked?" test (abbreviated `$F` below):
```
docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md
docs/retrospective.md docs/wave-playbook.md docs/how-to-ai-decomp/*.md
decomp-architect/corpus/decomp-kernels.md decomp-architect/templates/registry-E.decomp.md
phase-ends/DIGEST.md
```

---

## NEW

### C1 — GNU C sources carry form-feed page separators, and `str.splitlines()` splits on them while `grep`/`sed` do not — so any Python line-number checker over compiler source silently drifts, and blames the agents
- **Evidence:** `phase-ends/logs/Phase29.md:6915-6920` —
  > "GNU C sources use **form-feed (`\f`) page separators** — `loop.c` has 47, `cse.c` 36, `reload1.c` 27, `local-alloc.c` 21. **Python's `str.splitlines()` splits on `\f`; `grep`/`sed`/editors do not.** So every line number my checker computed after the first `\f` was shifted (by 20 in local-alloc.c, up to 47 in loop.c) — and 47 is **larger than the checker's own ±40 search window**, which is exactly how a real quote gets reported as FABRICATED."
- **What happened / what it cost:** The checker that validated two whole codegen-map audits (`tools/verify_map_findings.py`) reported "153 NEAR (agents' line arithmetic off by +2..+19)" and "12 FABRICATED" against the audit agents. After the one-line fix (`split("\n")`) the same data reads **180 OK / 0 NEAR / 0 FAB** and **299 OK / 0 NEAR / 0 FAB** — the agents' citations had been exact all along (`6923-6930`). The cost compounded: the false claim was **written into a later agent prompt**, telling agents to be careful about an error that was the instrument's (`6928-6930`), and the follow-up "diagnosis" of the 12 was itself wrong because it grepped the wrong JSON field (`6932-6937`).
- **Not banked — greps:** `grep -n -i -c 'form.feed' $F` → 0; `grep -n -i -c 'splitlines' $F` → 0; `grep -n -i -c 'page separator' $F` → 0; `grep -n -i -c '\\f' $F` → 0. (The adjacent lesson "a wall verdict is only as current as the instrument" is banked at `docs/matching-cookbook.md:10058`, but nothing records this defect or its class.)
- **Proposed home:** accelerator (an instrument-integrity entry) + a one-line note wherever compiler-source citation tooling is described (`docs/how-to-ai-decomp/07-compiler-source.md`).
- **Portable because:** every decomp project that reads a real compiler's source with a Python tool computes line numbers over text that contains `\f`; the failure is silent, it points the blame at the agents, and it survives into the next prompt.

### C2 — Never restructure a proven tool with blind string replaces at the end of a long session; specify it as the next session's first task instead
- **Evidence:** `phase-ends/logs/Phase29.md:6134-6138` —
  > "**⚠️ AND I BROKE `family_sweep` TWICE TRYING TO WIRE THE PARALLEL DEFAULT** (missed import, then a closure-scope error) — on the tool that banked 543 members today. **Reverted, not committed.** Restructuring a proven tool with blind string replaces at the end of a long session is how a working thing gets broken."
- **What happened / what it cost:** Two separate breakages of the single tool that had banked 543 of the day's members; both reverted, the work lost. The same session then twice more deferred structural work for the same stated reason — the `--allow-pins` default flip (`6178-6180`: "deliberately NOT done here, at the end of a long session, because that is exactly how `family_sweep` got broken twice today") and the `--span-tables` archaeology (`6352-6353`) — and both landed cleanly when done fresh. It recurs at `7713-7714`: a deleted `last_err` initializer during a refactor, caught only by re-reading the diff before running.
- **Not banked — greps:** `grep -n -i -c 'end of a long session' $F` → 1 (`docs/decision-log.md:1259`, and there it is an *excuse* for a stale measurement, not a rule about tool surgery); `grep -n -i -c 'structural.*refactor.*session' $F` → 0; `grep -n -i -c 'tired context' $F` → 0; `grep -n -i -c 'late in.*session' $F` → 1 (`docs/accelerators.md:423`, about building a tool late in the *project*, not in a session).
- **Proposed home:** G (a rule) or a kernel — a session-hygiene law beside "commit banked work immediately".
- **Portable because:** every agent-driven project accumulates one or two tools the whole pipeline depends on, and the temptation to "just wire it up" arrives exactly when context is exhausted and the diff is no longer being read.

### C3 — An oracle that can always be RUN is not always APPLICABLE: state the applicability precondition beside the recipe, or a coarse run returns a large number that reads as a verdict
- **Evidence:** `phase-ends/logs/Phase29.md:7359-7364` —
  > "`regalloc.md` §H presents the swap oracle as the way to 'discriminate RC-6 (allocation) from S3 (scheduling) in ONE gdb run'. It only works when **the contested registers are held by PSEUDOS**. Check the `.greg` RTL first: if the diff's registers appear as `(reg/v:SI N <name>)` with N < 68, they are hard already and the oracle cannot move them — a coarse swap will return a large, meaningless number (345 here) that looks like a verdict and is not one."
- **What happened / what it cost:** The `reg_renumber`-swap gdb oracle was built, negative-controlled (a no-op `31↔31` swap reproduced the baseline 13 mismatches exactly, `7328-7329`) and run on the project's single largest prize (51,198 templated instructions). Both contested swaps returned 345 and 97 — numbers that look like allocation verdicts. They were artifacts: `reg_renumber` maps only pseudos (≥ `FIRST_PSEUDO_REGISTER` = 68) and the contested value was already in a hard register at `.greg` time (`7348-7351`). The oracle's framing of the residual was refuted, not confirmed, and the map's §H had to gain a precondition it never stated.
- **Not banked — greps:** `grep -n -i -c 'unstated precondition' $F` → 0; `grep -n -i -c 'looks like a verdict' $F` → 0; `grep -n -i -c 'swap oracle' $F` → 1 (`docs/matching-cookbook.md:3326` — cites the oracle's *result* on another function, states no precondition); `grep -n -i -c 'applicability' $F` → 0. (The negative-control half IS banked, 41 hits for "negative control"; the applicability half is not.)
- **Proposed home:** DK (a kernel) — an oracle-design law next to "negative-control the instrument first".
- **Portable because:** any instrument that reports a scalar will report one when it is structurally inapplicable; the number is then indistinguishable from a measurement, and it is the shape that gets a function written off.

### C4 — Before a fleet-wide mechanical edit, census the whole population for the exact preconditions the edit assumes; perfect uniformity is the licence to apply it, and non-uniformity is the design input
- **Evidence:** `phase-ends/logs/Phase29.md:7520-7531` —
  > "### MEASURED BEFORE BUILDING (R35) — Ran the blocker census over all 132 still-stubbed siblings before writing a line. It is **perfectly uniform**, which is the strongest possible signal that one mechanical edit fixes all of them: … | with the file-scope blocker | **132 of 132**, 0 without | … | file-scope decl statements per (TU, sym) | **exactly 1** — never ambiguous | | file-scope references BELOW the decl | **0** — so the deletion is always safe |"
- **What happened / what it cost:** Every column of that census is a precondition the tool would otherwise have had to guess or guard: "exactly 1 decl" removes an ambiguity branch, "0 references below" is what makes the deletion safe. The tool then applied to 132 files with a diff **uniform to the line (+11/−3)** and banked 132/132 on the follow-up sweep (`7562`, `7599`). The counter-case is in the same slice: `func_80135260`'s family was assumed to share `func_80177DA8`'s blocker without a census and the inference was **WRONG** — "same SC07-only signature, different cause" (`7421-7423`).
- **Not banked — greps:** `grep -n -i -c 'census.*before building' $F` → 0; `grep -n -i -c 'perfectly uniform' $F` → 0; `grep -n -i -c 'one mechanical edit' $F` → 0; `grep -n -i -c 'population.*before' $F` → 4 (`registry-E.decomp.md:172` is regression control — run a new refusal over the population that already SUCCEEDED; `03-bootstrap-order.md:121` is lane staffing; neither is a pre-edit precondition census). `docs/matching-cookbook.md:7341` (§103) banks this lever's *two-step byte verification* and its refusal conditions but not the census. R37/G23 ("probe before costing") grounds an *estimate* on one instance — the opposite direction from censusing all of them.
- **Proposed home:** G (a rule) — beside the two-step verify in §103, or a kernel on fleet-wide edits.
- **Portable because:** any decomp reaches a point where one declaration-shaped edit must be applied across hundreds of files; the census is cheap, it converts every guard the tool would need into a proven fact, and its absence is what turns a mechanical edit into a half-axis.

### C5 — A status line a script prints unconditionally is not a measurement; derive every conclusion the script emits from the command's own output
- **Evidence:** `phase-ends/logs/Phase29.md:7496` —
  > "**Three unconditional `echo` conclusions** (`[shared clean]`, `[none = ...]`) that asserted things the command output contradicted."
- **What happened / what it cost:** Listed by the session itself under "MY ERRORS THIS SESSION (recorded, not buried)", alongside the form-feed bug and two truncated-output reads, under one stated common thread: "**inference from partial output instead of measuring.** Every one was caught by measuring; none by re-reading" (`7499-7500`). No instance is costed individually, so this is the weakest of the six — but the shape is exact and unbanked: a hand-written driver script that prints `[shared clean]` after a command, rather than from it, manufactures a clean verdict on a dirty tree.
- **Not banked — greps:** `grep -n -i -c 'unconditional echo' $F` → 0; `grep -n -i -c 'echo \[' $F` → 0; `grep -n -i -c 'asserted.*contradicted' $F` → 0; `grep -n -i -c 'always prints' $F` → 1 (`docs/wave-playbook.md:80` — a NOTE line that deliberately always prints, the opposite point). The nearest banked rules are "count banks from the SOURCE" (`phase-ends/DIGEST.md:226`) and R66 "write 'banked' only from the tool's printed success line" (`decomp-kernels.md:878`) — both about trusting a *tool's* output, not about a driver script fabricating one.
- **Proposed home:** accelerator (an instrument-integrity entry), or fold as a clause into the existing R66 line.
- **Portable because:** ad-hoc driver scripts are written in every session of an agent-run project, and an unconditional conclusion line is the cheapest possible way to make a red run read green.

### C6 — Measure what fraction of a cycle a parallelism knob can actually touch before adopting it: `make -j16` bought 12%, because the build was 5 s of a 16 s per-item cycle and the real cost was a four-stage retry ladder
- **Evidence:** `phase-ends/logs/Phase29.md:6115-6124` —
  > "**The `-j` theory was WRONG, and measuring said so** (baseline ~18 s/sibling): | `make extract` + `make build`, cold | **~5 s of the 16 s** | | one sibling end-to-end, serial | 16 s | | one sibling end-to-end, `-j16` | **14 s (12%)** | … Make is not the bottleneck. The per-sibling loop tries **up to FOUR stages** (raw → scoped → recovered → reconciled) and **each runs its own `make build`** … `-j16` kept (free, safe, committed) — but it is a 12% win, not 8×."
- **What happened / what it cost:** The session opened this task believing `-j` was the missing 8-16× lever (Drew asked why it wasn't being used). Measuring located the cost in the per-item *ladder*, not the compiler, and located the real 8-16× lever in cross-sibling parallelism — which was then found to be blocked by a specific hazard (`revert()` restores `config/` from git and `config/overlays.mk` is SHARED, so a concurrent revert clobbers peers' carve entries, `6126-6132`). Three sweeps totalling 543 members had already run serially in that session (`6109-6113`).
- **Not banked — greps:** `grep -n -i -c 'not the bottleneck' $F` → 0; `grep -n -i -c 'where the time' $F` → 0; `grep -n -i -c 'each runs its own' $F` → 0; `grep -n -i -c '8-16×' $F` → 1 (`docs/matching-cookbook.md:7287`, §101's stale-default table — it banks *that the parallel farm existed and was never wired*, not the measurement that the obvious knob was worth 12% and why). `docs/accelerators.md:112` (A8) banks processes-vs-threads, longest-first and per-item search, but not "profile the cycle before turning the knob".
- **Proposed home:** accelerator — an addendum to A8.
- **Portable because:** every fleet-scale decomp hits the same instinct (add `-j`), and the same true answer (the per-item retry ladder, not the compiler, dominates); the measurement takes minutes and redirects the whole optimisation.

---

## ALREADY-BANKED (one line each)

- Re-derive an agent's premise, not just its fix — its conclusion and its evidence fail independently (T4b) — lives at `docs/matching-cookbook.md:6800` (§90e).
- The program declares its own table length (`sltiu N`): prefer an exact self-declared bound to a heuristic, and a warning that fires on ambiguity is noise — `docs/matching-cookbook.md:6800` (§90e).
- The single-table-predecessor inference (a single-table carve's span start IS its table start) — `docs/matching-cookbook.md:8616` (§8e-2, pre-existing).
- Templatability is a per-FAMILY property, bimodal, never a blended rate over a pool — `docs/how-to-ai-decomp/09-economics.md:120` and cookbook §86 (`docs/matching-cookbook.md:6623`).
- Pick targets by the metric you mean to move: byte-VARIANT families move RE-completeness, h_exact families move only the display number — `docs/matching-cookbook.md:7715` (§111).
- Neither "always ladder" nor "never ladder": a verdict from a ladder is a verdict from the ladder; re-run a stubborn reject through the bare gate — `docs/matching-cookbook.md:34698`.
- The bare gate banks better and cleans up worse (no snapshot/restore) — always diff the tree after one — `docs/matching-cookbook.md:8125` (§122 law 2).
- Isolate the pipeline stage; `set -o pipefail` attributes the failure to the LAST stage in the pipe — `docs/matching-cookbook.md:6956` (§93).
- Splice once and dump EVERY cc1 error rather than peeling one conflict per gate cycle — `docs/matching-cookbook.md:7049`.
- gcc-2.7.2 prints hard errors with no `error:` prefix, so a naive grep finds nothing — `docs/matching-cookbook.md:11816` and `:30932`.
- A refused pre-step whose return code is ignored manufactures codegen-flavoured verdicts, and one refusal counted N times inflates the wall count — `docs/matching-cookbook.md:7100` (§97).
- A tool that swallows the underlying error returns a bare fail that reads as a wall — `docs/retrospective.md:47` and `docs/matching-cookbook.md:9730`.
- Diff a rewriting tool's OUTPUT against its INPUT before trusting it — the gate would only have said PLUMBING — `docs/matching-cookbook.md:7234`.
- A completion assertion must be a DELTA; an absolute "at least one exists" check passes vacuously — `docs/matching-cookbook.md:7388` (§103).
- An assertion must be exact about its DOMAIN, not just its condition (it cried wolf on its own by-design skip) — `docs/matching-cookbook.md:7184`.
- PLAN → VALIDATE → WRITE: a refusal path that aborts mid-write creates the half-axis it exists to prevent — `docs/matching-cookbook.md:7187`.
- A PLUMBING verdict is about the DECLARATIONS, never the BODY; a PLUMBING pool is an upper bound on recoverable work, not a count of it — `docs/matching-cookbook.md:7306` (§102).
- A negative that MOVES the failure class is a result, not a null — `docs/matching-cookbook.md:6040`.
- The STALE DEFAULT class: a guard whose cause was removed is a silent skip wearing a safety label (137 skipped, 133 bank) — `docs/matching-cookbook.md:7279` (§101).
- "The fix exists, it just isn't reachable by default" — a lever wired into ONE gate path is a lever most families cannot reach — `docs/matching-cookbook.md:7547` (§107) and §101's table row at `:7287`.
- Before editing anything shared, ask what the smallest scope is that still travels with the body (K&R def / block-scope typedef beat a 524-site conform) — `docs/matching-cookbook.md:7250` (§100) and `:7201` (§99), law at `:7276`.
- A TU that DEFINES a function owns its own declarations; a fleet-wide axis is meaningful only for CONSUMING TUs — `docs/matching-cookbook.md:7147` (§98).
- Persist the MEASUREMENT, derive the POLICY; and prove the re-derivation faithful (1610/1610, table unchanged) BEFORE editing the table — `docs/matching-cookbook.md:7504` (§106).
- A classifier's route that contradicts the knowledge base wastes search CPU (ADDRESSING → permuter, three targets under-delivered) — `docs/matching-cookbook.md:7530` (§106).
- A revert must run on EVERY exit — success, gate-fail, refusal AND the throw; untracked residue survives `git checkout --` — `docs/matching-cookbook.md:7465` (§105).
- Match on masked text, emit by span from the original; a warning that fires 137/137 and is right 0 times masks real causes — `docs/matching-cookbook.md:7429` (§104).
- The codegen map cited the WRONG compiler (2.8.1 vs 2.7.2), drift is not uniform, and each refutation was challenged by an independent agent (119/40/7 of 21) — `docs/how-to-ai-decomp/07-compiler-source.md:44-48`.
- An incremental build pass does not refute a clean-tree failure — `docs/matching-cookbook.md:7197`.
- Truncated output is not exhaustive output (`head -8` of 31 hid the MATCH); and re-measure every stored draft, never a sample — `docs/matching-cookbook.md:10051` and `:10058` (§146).
- A shared scratch directory is a shared blast radius — one subdirectory per agent — `docs/accelerators.md:732`, `docs/matching-cookbook.md:37026`.
- A scoped `git add` is an unverified assertion about a change set's boundary — use `git add -A src/ config/` for a carve bank — `docs/matching-cookbook.md:4523`.
- Two residuals that move in opposite directions under every lever are two symptoms of one starved resource — solve them together — `docs/matching-cookbook.md:34012`.
- A function's past-attempt journal travels with it and prices the next attempt — banked as `past-attempt` history in `docs/wave-playbook.md`, `docs/how-to-ai-decomp/05-cards-lanes-waves.md`, `decomp-architect/corpus/decomp-kernels.md`.
- Never write an unverified diagnosis into an agent's brief as fact — it inherits your wrong search space — `docs/matching-cookbook.md:6979` (§93).
- A draft header's own assertion is a claim, not a fact (R14: verify summaries against the bytes) — `phase-ends/DIGEST.md:174`.
- A verdict says what it was proved against (the honest-coverage-gap habit) — `phase-ends/DIGEST.md` and `docs/how-to-ai-decomp/07-compiler-source.md` (R69/R65).
- Count banks from the SOURCE, never from the report (a diagnostic that prints only failures hides its own successes) — `phase-ends/DIGEST.md:226`, `decomp-architect/templates/registry-E.decomp.md:240`.
- Regenerate the family map after every bank before sweeping — memory `crack-wave-sweep-map-regen`, cited as "the documented regen step" in the log itself at `5240-5244`.
- The -O0 cluster is OVERLAY-LOCAL, so discount an `_o0` exemplar's headline family reach — `docs/matching-cookbook.md:628`, `:1551`, `docs/decision-log.md:1251-1305`.
- A counterfactual byte-gated on a reproduced blocker is the evidence a stage works — `docs/matching-cookbook.md:7405` (§103, AUTOMATED).
