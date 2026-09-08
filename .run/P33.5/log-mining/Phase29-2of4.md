# Log mining — Phase29-2of4
Files/ranges: `phase-ends/logs/Phase29.md:2581-5160` (read 2551–5195 incl. ±30 context; reported range only)  ·  Lines read: 2580 of 2580
Candidates considered: 43 · NEW: 7 · ALREADY-BANKED: 36

Slice content: SESSION-17 → SESSION-21 of Phase 29 (the giant/permuter loop, the §73–§91 declaration-plumbing
harvest, the T0 frontier survey, the family-exemplar mass wave). The cookbook covers this stretch densely
(§66d–§91 were distilled in-session under R30), so nearly every *matching* lesson here is already banked; what
survives the greps is planning-, ledger- and prompt-shaped.

## NEW

### C1 — A verification flag that short-circuits the tool's WRITE path leaves the stale artefact in place and still exits 0
- **Evidence:** `phase-ends/logs/Phase29.md:2762-2765` —
  > "**⚠️ The sharp edge that hid it:** `worklist.py --assert-partition` **exits at the assertion and never
  > rewrites the doc** — so "regenerating" with that flag leaves the stale file in place and still exits 0.
  > (Its own assertion printed "160 live stubs, 160 rows → PARTITION OK" while the doc it left behind said 223.)"
- **What happened / what it cost:** The decision spine (`docs/worklist.md` + `.run/fuel_manifest.json`) was **9 days
  stale**, claiming 223 live stubs / 870,668 ins where the truth was 160 / 583,077, and it ranked **three
  already-banked functions in its top 7**. The session had "regenerated" it — with the assert flag on, which
  never reached the write. The two contradictory numbers were on screen simultaneously and the exit code was 0.
  Once actually regenerated, the top of the spine changed the whole plan (integration, not the giants).
- **Not banked — greps:** `grep -n -i 'assert-partition' <all 22 distilled files>` → 0;
  `grep -n -i 'exits at the assertion' …` → 0; `grep -n -i 'never rewrites the doc' …` → 0;
  `grep -n -i 'still exits 0' …` → 0. (`grep -n -i 'plan.*stale' …` → 1, `docs/matching-cookbook.md:2509`, a
  volatile-frame codegen idiom — unrelated.) The nearest banked kin, DK-19 / R32, is about a tool asserting its
  *denominator*; nothing records a verification flag suppressing the tool's primary side effect.
- **Proposed home:** DK (a kernel), sibling to DK-19 — *"a --check/--assert mode must be additive to the write,
  never a substitute for it; a regeneration that printed a verdict and wrote nothing is indistinguishable from a
  regeneration that ran."*
- **Portable because:** every project grows `--dry-run`/`--check`/`--assert` variants of its generators, and the
  plan is read off the generated artefact — the failure is in the flag design, not in MIPS or gcc.

### C2 — A diagnosis earns belief when it predicts its own RESIDUAL membership, not when it explains the failures already seen
- **Evidence:** `phase-ends/logs/Phase29.md:3690-3695` —
  > "The class-A census (`func_80012ABC`: **73 `s32` vs 7 `s16`**) had predicted the class-B fix would leave exactly
  > the class-A overlays behind, and it left **3** — the same 3 the original sweep's blocker breakdown named…
  > **A measurement that predicts its own residual to the overlay is the strongest evidence this session produced
  > that the classes are real and not a story fitted to the failures.**"
- **What happened / what it cost:** The same session had twice built plausible blocker taxonomies that were stories
  fitted to the failures (`3603-3607`: "I ALMOST GENERALIZED FROM ONE SAMPLE"; `3614-3625`: the full-sweep census
  *reversed* the ranking, the win ranked first was worth 3 overlays and the one ranked third was worth 132). The
  cheap discriminator that settled it was forward: state, before the fix, exactly which members the fix will *not*
  clear — then count them.
- **Not banked — greps:** `grep -n -i 'predicts its own residual' <all>` → 0;
  `grep -n -i 'story fitted' …` → 0; `grep -n -i 'fitted to the failure' …` → 0;
  `grep -n -i 'predicted the residual' …` → 1 (`docs/matching-cookbook.md:24094`, one instance of a codegen tell,
  not the epistemic rule); `grep -n -i 'strongest evidence' …` → 2 (both byte-evidence for specific codegen laws).
- **Proposed home:** DK (a kernel) — pairs with DK-61 ("a known-true case before reading any instrument's output"):
  *before* acting on a classification, have it name the members it predicts will still refuse, and check that set.
- **Portable because:** it is a falsification protocol for any bucketing of failures — blocker classes, error
  taxonomies, model-failure clusters — and it costs one grep more than the taxonomy already cost.

### C3 — Make the DRAFTER run the pre-gate guard and return the NAMED banking prerequisite; a batch of diagnosed candidates is worth far more than a batch of opaque MATCHes
- **Evidence:** `phase-ends/logs/Phase29.md:5093-5096` —
  > "**⚠️ These are CANDIDATES, not banks** … an earlier 11-core wave had 9/9 match_one MATCHes all gate-fail on
  > integration. What makes this wave different is that the agents were *told* to run `symcheck` and report the
  > blocker — so instead of 8 opaque MATCHes we have 8 diagnosed ones."
- **What happened / what it cost:** The wave prompt (`4907-4915`) made a `symcheck` run mandatory on any claimed
  MATCH and asked for the blocker by name. The result table at `5098-5107` gives, per exemplar, the exact banking
  prerequisite — and reading down it revealed that **six of eight were blocked on one mechanical lever** standing
  in front of ~153,596 templatable instructions (`5109-5112`). Without the reported blockers that batch would have
  read as eight unrelated integration failures.
- **Not banked — greps:** `grep -n -i 'report the blocker' <all>` → 0; `grep -n -i 'diagnosed ones' …` → 0;
  `grep -n -i 'opaque MATCH' …` → 0; `grep -n -i 'mandatory .*symcheck' …` → 0;
  `grep -n -iE 'agent (must|runs|shall)|pre-gate' docs/wave-playbook.md docs/how-to-ai-decomp/0{4,5}-*.md` → 1
  (`docs/how-to-ai-decomp/05-cards-lanes-waves.md:127` — the *reconcile lane*, a separate post-draft agent per gate
  group, not a requirement on the drafter's own return). `§67a` (`docs/matching-cookbook.md:5439`) banks the guard
  as a tool; nothing banks it as a drafter-return contract.
- **Proposed home:** wave playbook / how-to chapter 05 (card & return schema), plus a G-rule: *a drafter's return
  is `MATCH + guard verdict + named banking prerequisite`, or it is not a return.*
- **Portable because:** it is a prompt/return-schema rule for any parallel drafting harness — the marginal cost is
  one deterministic tool run per agent, and it converts a batch's failures into a single sortable column.

### C4 — When two blockers are orthogonal, a classifier's if-chain ORDER silently becomes the label — cross-tabulate, never bucket
- **Evidence:** `phase-ends/logs/Phase29.md:4958-4960` —
  > "The T2 table above ordered its if-chain with `jr` FIRST, so any family carrying a mid-jr was bucketed as
  > "jr → §81 carve chain" **regardless of whether its exemplar needed a crack at all**. That conflated two
  > orthogonal axes and under-reported the zero-crack pool by 15 families."
- **What happened / what it cost:** The primary axis is *does the exemplar need a CRACK?*; the sweep path (plain vs
  carve chain) is orthogonal to it. Bucketing on first-match collapsed them and hid **15 families / 123,482
  templatable ins** of no-drafting work — the pool read as 45 fams / 85,017 ins instead of 60 / 208,499
  (`4965-4982`). The log itself names the recurrence: this is the same shape as the previous session's "FREE"
  label — *"a classification presented as a route"* (`4985-4987`).
- **Not banked — greps:** `grep -n -i 'classification.*route' <all>` → 0; `grep -n -i 'orthogonal axes' …` → 0;
  `grep -n -i 'if-chain' …` → 3 (all `§222`, the switch-vs-if-chain *codegen* idiom);
  `grep -n -i 'cross-tabulat|cross tab' …` → 1 (`docs/matching-cookbook.md:30650`, a jump-table reading technique).
  `§136h` banks *"do not price a pool without probing a member"*; nothing banks the bucketing defect that produced
  the pool's shape in the first place.
- **Proposed home:** DK (a kernel), next to DK-19 — *"a routing table's rows are its if-chain's order; if two
  conditions can hold at once, emit a cross-tab and let the reader see both."*
- **Portable because:** every triage script anywhere is an if-chain over overlapping predicates, and the cost is
  paid in work that never gets planned rather than in a visible error.

### C5 — Sequence a phase so the cheapest thing that can invalidate everything below it runs FIRST
- **Evidence:** `phase-ends/logs/Phase29.md:4322-4327` —
  > "Not caution — **T0 is the cheapest thing that can invalidate everything below it.** If the families template,
  > T2.2 becomes "crack N exemplars and stamp" and most of that bucket evaporates. If they do not, we grind
  > *knowingly* instead of hopefully. R35 exists because this project has scoped whole phases against broken
  > readings twice; P26 spent its longest phase on a thesis its own tools had already refuted."
- **What happened / what it cost:** The open question (do the remaining functions cluster into templatable families?)
  had **flipped three times, every time on TOOLING, never on the compiler** (`4296-4305`) — P25 yes, P26 byte-refuted
  at ≈0%, P28 found the refuting probe had a missing carve and the same family banked 89%, P29 found the residual
  was an `-O0` compile-flag artefact. It cost **zero agent tokens** to re-measure, and it decided the method for the
  largest remaining bucket. Running it first is what made the rest of the plan honest.
- **Not banked — greps:** `grep -n -i 'cheapest thing that can invalidate' <all>` → 0;
  `grep -n -i 'invalidate everything below' …` → 0; `grep -n -i 'sequence.*cheapest|order the work so' …` → 0;
  `grep -n -i 'order for discovery' …` → 0. Adjacent but different: `R35` (`phase-ends/DIGEST.md:212`, fix the
  instrument before trusting it) and `§3-The` (`docs/cookbook-index.md:1571`, triage cheapest-first *within* a
  function's levers) — neither is a phase-ordering rule.
- **Proposed home:** DK (a kernel) or a G-rule for phase planning — *"rank a phase's tasks by (cost) ÷ (how much of
  the plan below them the result could delete); the cheapest high-invalidation measurement is task 1."*
- **Portable because:** it is pure plan structure — it applies to any long project whose method choice depends on an
  unmeasured property of the remaining work.

### C6 — A reach-weighted gain figure (size × copies) is not a size; every number must say which of the two it is
- **Evidence:** `phase-ends/logs/Phase29.md:4775-4777` —
  > "**⚠️ SIZING TRAP (Drew caught me on this):** `nins × members` is **reach-weighted gain-ins**, NOT a function
  > size. `func_80144090` is **154 ins × 136 copies**, not a 20,944-ins monster. **Always label which one you are
  > quoting.**"
- **What happened / what it cost:** The endgame map's whole bucket table was priced in gain-ins, and a 154-instruction
  function sat in it reading like a 20,944-instruction monster — which mis-prices the *effort* by two orders of
  magnitude while the *value* is right. The same conflation runs through the pool tables in this slice (`4370-4376`,
  `4991-5006`), where "208,499 ins" is repeatedly cautioned against being read as available work.
- **Not banked — greps:** `grep -n -i 'gain-ins' <all>` → 0; `grep -n -i 'label which one you are quoting' …` → 0;
  `grep -n -i 'not a function size' …` → 0; `grep -n -i 'reach-weighted' …` → 1
  (`docs/matching-cookbook.md:4613`, uses the term in passing, carries no warning). Adjacent: `R41` /
  `DK-60` (`decomp-architect/corpus/decomp-kernels.md:752`) require a *denominator* on every rate — this is a
  different defect, a **product read as a magnitude**, and neither R41 nor DK-60 names it.
- **Proposed home:** accelerator, or an extension line on DK-60 — *"a weighted total names its weight; size × copies
  is never quoted without the multiplier visible."*
- **Portable because:** any decomp/port with duplicated code (overlays, statically-linked libraries, templated
  families) prices work as size × instances, and effort tracks the size while value tracks the product.

### C7 — A repair ladder must probe whether each stage is NEEDED before applying it, or it silently escalates a binary-local bank into a fleet-shared one
- **Evidence:** `phase-ends/logs/Phase29.md:3377-3388` —
  > "**⚠️ HYPOTHESIS TO TEST AFTER R22 — the recovery tool may have taken a FLEET-TIER edit it did not need.**
  > … So the relaxation looks unnecessary, and it converted a T1 binary-local bank into a **T2 fleet-shared** one
  > (blast radius 138 overlays, R22 mandatory) for nothing. … **`recover_integration` should probe whether a stage
  > is NEEDED before applying it** — an unrequested tier escalation is exactly the class R32–R35 exist to catch."
- **What happened / what it cost:** Banking one 123-instruction function rewrote `src/shared/engine_core.h` (2 lines)
  plus two overlay files, relaxing a prototype whose conflict belonged to the *old, discarded* drafts — the banked
  definition already agreed with it. The price of an unneeded T2 write is a mandatory full-fleet R22 cycle and a
  138-overlay blast radius. The same session shows the other half of the bill: the ladder's stages left byte-neutral
  edits behind on 0-bank runs (`4473-4481`, `4635-4639`) because "byte-safe" was standing in for "wanted".
- **Not banked — greps:** `grep -n -i 'probe whether a stage is needed' <all>` → 0;
  `grep -n -i 'edit it did not need' …` → 0; `grep -n -i "unnecessary.*fleet.*edit" …` → 0;
  `grep -n -i 'tier escalation' …` → 1 (`docs/decision-log.md:281`, a *model* escalation ladder). The closest banked
  item is `§89a` (`docs/matching-cookbook.md:6766`, "MEASURE the write set; do not assert its tier") — which detects
  the escalation *after* the tool has taken it; nothing requires the tool to establish a stage's necessity first.
- **Proposed home:** DK (a kernel) or a G-rule, as the precondition half of §89a — *"a repair stage runs only after
  its blocker is observed; a ladder that applies stages unconditionally buys the widest blast radius it can reach."*
- **Portable because:** any automated fixer with a ladder of increasingly-invasive transforms (codemods, lint
  autofix, migration tools) has the same shape: the cheapest stage is skipped, the widest is applied, and the
  verification cost scales with the widest write actually taken.

## ALREADY-BANKED (one line each)
- Assert on the expected SUCCESS STRING, never `$?` after a pipe (`head`'s rc read as `make`'s → a false BYTE-IDENTICAL report) — lives at `docs/matching-cookbook.md:6619` (§85)
- A comparison tool must share its reference oracle's index space exactly (`objdump -dr` elides identical runs; use `-drz`) — `docs/matching-cookbook.md:6806` (§90a)
- Little-endian hex text in a `.s` word field must be byte-swapped before comparison — `docs/matching-cookbook.md:6806ff` (§90a)
- A helper that cannot answer returning an empty set (a library call gated on a CLI-only global) — `decomp-architect/corpus/decomp-kernels.md:896`, `docs/how-to-ai-decomp/02-byte-gate.md:30` (R32/R43/G28)
- A warning that fires on ambiguity is noise, not a signal (~90 spurious fires across 38 tables) — `docs/matching-cookbook.md:6869`
- A do-not-re-buy entry is scoped to its BASE; re-run the negative list after the base moves — `docs/matching-cookbook.md:6304`, `:6316` (§80)
- Crack the smaller family member first; it is a lever library for the larger one — `docs/matching-cookbook.md:6252`
- Budget two passes at behemoth size; a 99% round-1 is on-plan, not a stall — `docs/matching-cookbook.md:6355`
- Templatability is PER-FAMILY: a sample straddling families reports their average and hides bimodality; probe one member then sweep or skip — `docs/matching-cookbook.md:6623`, `:6658` (§86)
- "Byte-neutral" is not "wanted": on a 0-bank group restore the snapshot unconditionally — `docs/matching-cookbook.md:6823` (§90b)
- One member's error names one blocker, not the blocker set — collect the classifier's line across the whole sweep — `docs/matching-cookbook.md:5979` (§75a)
- A diagnostic that asserts the WRONG cause redirects every later session (a mislabelled skip cost ~4 phases of a known mechanical win) — `docs/matching-cookbook.md:5579` (§68)
- Draft QA happens after the wave returns, never during; a stored MATCH is a claim with a timestamp — `docs/matching-cookbook.md:6849`, `:6691` (§90d/§87)
- An agent's CONCLUSION and its EVIDENCE fail independently — re-derive the premise, design the fix yourself — `docs/matching-cookbook.md:6851` (§90e)
- Prefer a bound the program itself declares (the owning function's `sltiu`) over a heuristic boundary — `docs/matching-cookbook.md:6858` (§90e)
- An unverified inherited premise is a hypothesis to test, not a foundation — flagging it costs nothing — `docs/matching-cookbook.md:6470-6472`
- Target byte-VARIANT families to move RE-completeness; high-reach h_exact families move only the display metric — `docs/matching-cookbook.md:6903`
- Count banks from the SOURCE (stub count), never from a tool's own tally — `phase-ends/DIGEST.md:226` (R42)
- 44% of the "near-miss" backlog were partial drafts misfiled with a closeness score; re-gate a sample before planning against any stored-draft pool — `docs/matching-cookbook.md:6695`, `:6697` (§87)
- 91% of the open backlog carried no class label, so the grinder searched undirected — `decomp-architect/corpus/decomp-kernels.md:219`, `docs/how-to-ai-decomp/03-bootstrap-order.md:87`
- `residual_class`'s "structural ⇒ permuter CPU is waste" is measurably false for schedule permutations; instruction-count equality is the tell — `docs/matching-cookbook.md:5525`, `:5549-5551` (§66d-5)
- Read the ILS per-cycle series, never the final best: a repeated score is converged, a still-falling one is budget-limited — `docs/matching-cookbook.md:5344` (§66d-3)
- Profile diversity is a ~0-token lottery ticket, not expected yield (3-for-3 on one giant, 0-for-1 on the next) — `docs/matching-cookbook.md:5525ff` (§66d-4)
- Check every search pass's diff for operand-order regressions — a search cannot see that one of its own edits is locally wrong — `docs/matching-cookbook.md:5501`
- `pgrep -f` self-matches the waiter's own command line; use a captured PID or a bracketed pattern — `docs/wave-playbook.md:721`, `docs/accelerators.md:196`, `phase-ends/DIGEST.md:295` (R79)
- A half-done declaration axis is a guaranteed break, not a smaller win; `0 sites remaining` is the completion assertion — `docs/matching-cookbook.md:6611` (§85)
- A guard defending a crash that was already fixed refuses real work (the §42e pin guard refused 63% of a pool, 0 crashes when overridden) — `docs/matching-cookbook.md:6623-6628` (§86)
- When asking "was this attempted?", glob every draft directory — a hand-listed pair lied in both directions — `docs/cookbook-index.md:1349` (§66c)
- Absolute include paths break a stranger's build and are invisible to every byte gate — `docs/how-to-ai-decomp/11-publishing.md:71`, `docs/matching-cookbook.md:6172` (§77)
- A headline number's denominator can carry an already-done population (main's 59,765 = game code + linked library) — `decomp-architect/corpus/decomp-kernels.md:392` (DK-30)
- A ranked "free" pool's top entries are precisely the known refusers; a byte-derived claim is a prediction, not a bank — `docs/matching-cookbook.md:9274` (§136h), `decomp-architect/corpus/decomp-kernels.md:282` (DK-20)
- Embed each callee's canonical signature in the drafter prompt (33% → 56% → 90% match_one, and the gap is declaration plumbing) — `docs/matching-cookbook.md:1470`, `:4406` (§58)
- Every extraction tool carries a narrow hard-coded preamble set; diff the exemplar's preamble against what the tool emitted, and carry the MINIMAL transitive closure — `docs/matching-cookbook.md:6118` (§77)
- Run the symbol-set guard before paying for a gate; `match_one`/`rtu_match` compile but never link, so an invented extern reads as MATCH — `docs/matching-cookbook.md:5439` (§67a), §87
- Bare `harvest_verify` is the last rung, not the ladder — `docs/matching-cookbook.md:6529` (§84)
- MEASURE the write set; do not assert its tier — `docs/matching-cookbook.md:6766` (§89a)
- A ledger keyed inconsistently on address vs name yields two "best" records for one function — `docs/matching-cookbook.md:10301` (§3-B)
- Make the tool state its own denominator / a generated artefact must derive every scope figure it prints — `decomp-architect/corpus/decomp-kernels.md:263` (DK-19), `:392` (DK-30)
