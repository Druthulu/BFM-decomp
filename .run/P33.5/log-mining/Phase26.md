# Log mining — Phase26
Files/ranges: phase-ends/logs/Phase26.md:1-1106  ·  Lines read: 1106 of 1106
Candidates considered: 39 · NEW: 3 · ALREADY-BANKED: 36

> Grep target set (used for every candidate below, referred to as `$F`):
> `docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md docs/retrospective.md
> docs/wave-playbook.md docs/how-to-ai-decomp/*.md decomp-architect/corpus/decomp-kernels.md
> decomp-architect/templates/registry-E.decomp.md phase-ends/DIGEST.md`
>
> Note on the slice: Phase 26 contains the inserted tooling-integrity half-phase (26-A), which was *itself* a
> distillation exercise — cookbook §51 (LAWS 1–11), R32/R33/R34 and ~15 decision-log entries were written live
> during it (R30). The banked-rate is therefore very high by design: nearly every "audit thesis" line in the log
> already has a home. The three below are the ones that were fixed but never generalised.

## NEW

### C1 — A round-trip selftest is a serialisation check, not a coverage check: it passes by construction when a parser's missed item is absorbed into its neighbour's span. Every partition/rewrite tool needs an independent detector of items it failed to anchor.
- **Evidence:** `phase-ends/logs/Phase26.md:764-773` —
  > "**The selftest was structurally blind** (round-trip = `"\n".join(item_texts)` stays exact by construction when a miss lands in a preamble — a *serialisation* check, not *coverage*). … **R32 coverage oracle** `hidden_definitions()` wired into `selftest` (independent detector of `func_XXXX(...){` bodies not anchored) — the selftest is now a coverage check."
- **What happened / what it cost:** `overlay_src_split.py` — the parser that repartitions overlay `.c` files for TU isolation, i.e. a tool in the byte-changing path — shipped with a fleet-wide selftest that read **404/404 files, 341,902 items, round-trip exact** (`:564`). It was green while `scan_construct`'s `force_decl` latch silently swallowed **2 real function definitions** on lines shaped `extern A; extern B; void f(){...}`, absorbing them into the next anchor's preamble. Because the round-trip re-joins whole-line chunks, the join stayed byte-exact and the miss was undetectable by the test that existed. It survived from session 5 to session 13 (the audit) and was found only by writing a second, independent detector; the audit's own line refs were stale, so the real cases had to be re-found by the new oracle (`:774-777`).
- **Not banked — greps:** `grep -n -i 'selftest\|self-test' $F` → 3 (a render selftest's reachability assert; a `--selftest` known-true case; a fleet-wide self-test catch — none about round-trip blindness); `grep -n -i 'round-trip\|roundtrip' $F` → 12 (all about splat round-tripping bytes, cdecl declarations round-tripped through gcc, or wiki row round-trips); `grep -n -i 'is not a coverage\|coverage check' $F` → 2 (both the P31 S80 K&R backlog refusal, a different subject); `grep -n -i 'masquerad' $F` → 4 (build-integration walls, byte-gate optimism, wrong TYPE as codegen residual); `grep -n -i 'structurally blind' $F` → 7 (all R34: an *oracle* blind to an error class ⇒ add a second oracle — the prescription, not this test-design failure mode).
- **Proposed home:** DK (a kernel), sitting beside R32/R34 — closest existing text is R32, which says assert coverage against an over-approximating candidate set; this says *which* test cannot be that assertion, and why.
- **Portable because:** every decomp builds source-partitioning / draft-splicing / TU-rewriting tools, and the obvious test for all of them is "re-emit the input and diff". That test is green for the whole class of merge/absorption defects, which are exactly the ones that silently move bytes.

### C2 — A set that gates work must be reconstructible from committed artifacts. A roster kept in gitignored scratch is an unversioned oracle: it is silently wrong for anything it was not named after, and a `rm -rf` scratch or a fresh clone blinds it completely.
- **Evidence:** `phase-ends/logs/Phase26.md:742-748` —
  > "`jr_inventory`'s `banked` set was filtered by an **EPHEMERAL, gitignored `.run/banked_func_*.json` roster** — `rm -rf .run`/a fresh clone would blind ALL banked jr at once, cross-address siblings (roster named after the exemplar) were structurally invisible, and non-leader banked jr were missed. **FIX … `banked` is now DERIVED FROM THE IMAGE** … (config + image, both durable)."
- **What happened / what it cost:** the tool that decides which functions already own a jump-table carve — the input to every isolation, and therefore to the ×134 economic engine — trusted a scratch file. Two silent narrowings followed from the roster's *shape*, not from a parse bug: it was keyed on the exemplar's name, so every cross-address sibling was invisible, and non-leader banked functions were dropped. Deriving `banked` from the committed config plus the built image instead, and adding an R32 assertion that every committed carve resolve to exactly one owner, made the fleet run **134/134 OK, 0 false aborts, 1336 banked jr == 1336 carves** — and immediately found the cross-address sibling (`func_8017FCB0`) and three non-leader overlays the roster had missed (`:753-758`).
- **Not banked — greps:** `grep -n -i 'ephemeral' $F` → 0; `grep -n -i 'gitignored' $F` → 8 (worktree isolation missing a gitignored signature registry — DK/accelerator #19; publishing; the `.run/` policy line — none about a roster as an authoritative set in the main tree); `grep -n -i 'roster' $F` → 1 (`docs/matching-cookbook.md:24906`, a parenthetical "the removed `INCLUDE_ASM` lines are the ground truth — no roster, no ledger" inside §262's lane-yield size-matching argument; it uses the instinct, it does not record the lesson); `grep -n -i 'source of truth' $F` → 8 (wiki/docs governance, licence provenance, §436's "wrong source of truth" = a stale asm directory vs the config, a different mechanism).
- **Proposed home:** G (a rule) or DK — the operational half of R33: *derive from committed state*, stated about persistence rather than about re-parsing.
- **Portable because:** every agent-driven decomp accumulates a `.run/`-style gitignored scratch tree, and JSON rosters written there are the cheapest way to remember what has been done. The failure is invisible in the tree that wrote them and total in every other tree.

### C3 — A guard that is allowed to sit RED and UNWIRED does not exist. A detector's value is zero until it is green on HEAD and called by the standing report — and a docstring claiming it is wired is not wiring.
- **Evidence:** `phase-ends/logs/Phase26.md:101` and `:851-853` —
  > "**A9 — `lint_symbol_refs`: a guard allowed to sit red does not exist** … currently **RED** (43 false positives) and **UNWIRED** (`make report` never calls it, though its docstring claims it does)."
  > "The ONLY detector for the R22 rename-drift failure mode (a symbols rename leaves a `func_<ADDR>` ref dangling; a clean build fails, an incremental masks it — **undetected Phase 21→23**). Was RED (262 FPs) + UNWIRED."
- **What happened / what it cost:** the project's only detector for symbol-rename drift existed, in tree, for the whole period in which that exact failure mode went undetected across three phases. It was never deleted and never fixed — it sat red, so its output was ignored, and it sat unwired, so nothing produced output to ignore. Closing it took fixing three blind spots (it never scanned `src/shared/*.h`, where `engine_core.h`'s 10k+ tokens are; it unioned two symbol files instead of using each binary's own splat stack; and **all 262 false positives were one modelled class**, the `__asm__("memcpy")` asm-label binding), a negative control proving it still fires, and then wiring it fail-closed into `make report` (`:853-858`).
- **Not banked — greps:** `grep -n -i 'sit red\|sits red\|allowed to be red\|RED and UNWIRED' $F` → 0; `grep -n -i 'unwired\|not wired' $F` → 5 (an unwired SDK object, an unwired h_exact pool, "the fix already existed and was simply not wired in" — about a *fix*, not a standing guard, and with no rule attached); `grep -n -i 'only detector\|docstring claim' $F` → 0; `grep -n -i 'false positives' $F` → 8 (R39 — *negative-control a NEW refusal-check*, which governs a check's introduction, not the standing state of one already red).
- **Proposed home:** G (a rule), next to R39 — R39 says a new check must be negative-controlled to zero FPs; this says an *existing* check that is red or uncalled must be fixed-and-wired or deleted, never left as a note.
- **Portable because:** every long decomp accumulates half-finished lint/consistency tools, and the standing report is the only place a check is actually read. The cost shape (the one detector for a live failure mode, dormant across three phases) transfers to any project with a CI-style report and a tool directory.

## ALREADY-BANKED (one line each)

- A tool that cannot bank a function is indistinguishable, in every log, from a function that cannot be banked — lives at `docs/matching-cookbook.md:3934`
- A loud failure that nobody counts is exactly as invisible as a silent one (R32's corrected form) — lives at `docs/matching-cookbook.md:3739`, `phase-ends/DIGEST.md:208`
- A fix is not landed until its caller stops overriding it (grep every call site after fixing a scanner) — lives at `docs/matching-cookbook.md:3916` (§51g LAW 11)
- A check applied outside its valid domain does not become more thorough — it becomes noise (the 914-vs-193 near miss) — lives at `docs/matching-cookbook.md:3758`
- A second, disagreeing oracle beats a better assertion when an oracle is structurally blind (R34) — lives at `phase-ends/DIGEST.md:211`, `docs/decision-log.md:878`
- A symbol whose address falls inside another binary's vram window must never enter that binary's symbol stack — lives at `docs/decision-log.md:896`
- A stale object gives a FALSE PASS: `.o ← .s` is not a dependency make sees, so an incremental build "verifies" a broken config change; a rule a human must remember is not a gate — lives at `docs/matching-cookbook.md:3761-3767`
- gcc-2.7.2 does not prefix errors with `error:`; grep the diagnostic text, not the word "error" — lives at `docs/matching-cookbook.md:545`
- Triage rule: "wrong BYTES" → read the compiler source; "won't COMPILE" → read your own tooling (R17) — lives at `docs/decision-log.md:528`
- Every recovery pass is a FALLBACK, never unconditional (gate raw first, reconciled only on failure) — lives at `docs/matching-cookbook.md:2928`
- `match_one closeness==0` (isolated, reloc-masked) systematically overstates whole-binary bankability — lives at `docs/accelerators.md:365-370`, `docs/decision-log.md:1017`
- Force a newly-built mechanism's un-built sub-case out on cheap targets first: de-risking and building-the-missing-piece are the same move — lives at `docs/decision-log.md:413-422`
- Don't grind the light tail because it "feels productive"; the cheap tier is a means (harden the pipeline), not the objective — lives at `docs/decision-log.md:419-421`
- `--no-propagate` on every per-group gate; commit the cheap verified banks before the expensive fleet-wide propagate, which mutates before it gates and dies mid-mutation on a timeout — lives at `docs/matching-cookbook.md:4155-4166` (§55b)
- A checker that checked nothing must never read as a pass; a tool written against one binary carries an untested hypothesis about every other — lives at `docs/matching-cookbook.md:18450` (§192b)
- The adjudicator must be the compiler that compiles your code — not the standard, not the gcc on PATH — lives at `docs/matching-cookbook.md:3873` (§51g LAW 9)
- Probe the compiler for FACTS (four three-line probes, 90 s) before accepting a documented dead-end's premise — lives at `docs/matching-cookbook.md:3894-3898`
- Hand-maintained models of the corpus layout DECAY measurably as the corpus is restructured, and an un-nominated target produces silence, not an error — lives at `docs/decision-log.md:788-798`
- Audit the SELECTION tools before fixing anything on top of them: a hole there makes work invisible to planning — lives at `docs/decision-log.md:715-721`
- A target-ranking document sorted on already-matched work is majority-fiction (62% of the advertised byte-weight was phantom) — lives at `docs/decision-log.md:812`, `docs/matching-cookbook.md:3683`
- Making a parser see more ARMS dormant downstream transforms; migrate consumers one at a time, byte-gated — lives at `docs/decision-log.md:958-961`
- Pair every auditor finding with an adversarial skeptic told to refute it (32 raised → 28 survived, 4 refuted, 16 downgraded) — lives at `docs/matching-cookbook.md:3708`, `docs/decision-log.md:783`
- Audit scope filter: "does it PARSE something, and does it GATE or SELECT work?" — not all 82 tools — lives at `docs/decision-log.md:719`
- The frontier model DISCOVERS a class; the cheap agents APPLY it — lives at `docs/matching-cookbook.md:3555`, `:3991`, `docs/decision-log.md:1058`
- Run deterministic parallel shell jobs, not agents, for a gate re-test (agents are wasted running a shell gate) — lives at `docs/decision-log.md:1020`, `:2403`
- Prefer a transformation correct BY CONSTRUCTION (never worse than raw, conflict-free forward-carry) over one that needs an oracle to dodge conflicts — lives at `docs/decision-log.md:559`, `docs/matching-cookbook.md:483`, `:533`
- A tool whose per-item revert restores from HEAD must refuse a dirty tree (commit each family before sweeping the next) — lives at `docs/matching-cookbook.md:499`, `:4524`; R42 in `docs/how-to-ai-decomp/01-governance.md:37`
- Profile and parallelise the fleet verification harness — a slow gate is a bug; it runs on every commit and compounds — lives at `decomp-architect/corpus/decomp-kernels.md:432-444` (DK-33), `docs/how-to-ai-decomp/02-byte-gate.md:48`
- The "reach-1 unique tail" was largely a reloc-tracker blind spot in our own normalisation, not unique code — lives at `docs/matching-cookbook.md:2653` (§40b), `docs/decision-log.md:264`
- The byte-gate happily banked a phantom function splat invented (`void listCdBuffer(void) {}` — byte-correct, gate-green, fictitious) — lives at `docs/decision-log.md:890`
- A dropped prototype is a silent byte-changer in C89 (implicit `int f()`, and return type drives delay-slot fill) — lives at `docs/matching-cookbook.md:6399-6400`
- A GO/NO-GO validation harvest on a zero-crack corpus (families whose exemplar is already matched) before scaling the engine; check every instrument against a known-true case — lives at `docs/decision-log.md:281`, `:292`, `:317`; `decomp-architect/corpus/decomp-kernels.md:762` (DK-61)
- An audit that is a prerequisite to the live milestone runs as an INSERTED half-phase, not as a new phase and not by closing the current one early — lives at `docs/decision-log.md:737-754`
- Don't trust a handoff's diagnosis — reproduce one case by hand (R14); the sharper picture was a smaller, safer fix — lives at `docs/decision-log.md:532`
- Agents die to usage limits; write deliverables early and treat the limit as a wall class (R67) — lives at `phase-ends/DIGEST.md:266`, `docs/how-to-ai-decomp/08-models-and-budgets.md:42`
- A fleet verification (`make clean` + extract) rewrites the shared `asm/` tree that running workers read — never run it under them — lives at `docs/wave-playbook.md:621`, `docs/accelerators.md:464-468`
