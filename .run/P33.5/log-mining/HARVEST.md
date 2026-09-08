
=================== Phase15-16: considered 28 · NEW 8 (found 8) · banked 19 · lines read 167 of 167
  C1 — Measure a pipeline's yield on the RESIDUAL, not on already-solved functions: build a known-answer ladder (revert a matched function to a stub and make the pipeline re-derive it), then read the ga
      LOG phase-ends/logs/Phase16.md:36: - **Known-answer ladder (Drew's method), `tools/p16_known_answer.py`:** on 12 already-matched fns (known-reachable answers), **m2c-DIRECT re-derivation = 8/12 = 67%** (macro-only, NO permuter, NO struct types). Remainder: 2 near-misses @15 mismatch (permuter),
  C2 — A search harness (permuter) must compile in the SAME declaration context as the real build; an isolated context does not merely fail to verify, it makes the search converge on the wrong answer
      LOG phase-ends/logs/Phase16.md:71: ## CRITICAL FINDING (Fri 2026-06-19) — the extern-context bug (byte-gate caught a false 42%) - Overnight permuter "closed" 17/40 near-misses (42%) — BUT **0/17 whole-binary-gated.** Root cause: the permuter's `base.c` STRIPPED callee externs → compiled with im
  C3 — Before concluding a drafting pipeline is weak, histogram the compiler's error TEXT: over half of ours were one missing declaration in the shared header, fixed byte-neutrally in one line
      LOG phase-ends/logs/Phase16.md:40: - **393 m2c-target characterization (macro-only, match_one):** 70 direct-MATCH / 106 CC1-fail / 217 near-miss. **CC1-fail breakdown: 58 = `NULL` undeclared (TRIVIAL fix — add to common.h), ~15 stack-struct (sp* vars → --stack-structs), ~10 m2c-incomplete.**
  C4 — Re-run the deterministic declaration-canonicaliser over OLD quarantined drafts after every large bank: a draft's recovery odds rise as the banked corpus grows, and the pile costs nothing to keep
      LOG phase-ends/logs/Phase15.md:57: - 2026-06-17 — **T6 tail: quarantine recovery — fleet 44.64% → 46.27% (+1.63).** `canon_draft_decls` on the combined 505 quarantined (now canonicalizing against the much-larger banked set: 268 decls rewritten) → **47 verified** (1175→1128 stubs) → **42 propaga
  C5 — Write numeric kill-criteria into the plan, before the data exists, for any expensive campaign — and let them fire
      LOG phase-ends/logs/Phase16.md:24: - [ ] **S3** 10-medium validation (Max) → **GATE-B:** ≥6/10 byte-identical; record permuter yield (<4/10 → STOP run)
  C6 — Design an unattended run for a human with no agent session: a STOP file honoured at a safe boundary, a supervisor that tells a clean exit from a crash, a status one-liner — and prove crash-resume
      LOG phase-ends/logs/Phase16.md:89: - **Safe-exit mechanism (REQUIRED).** Driver checks `.run/auto/STOP` at every function boundary; if present → finish current fn's gate+propagate+commit → final heartbeat "stopped safely" → exit 0; supervisor sees STOP + clean exit → does NOT relaunch. **Trigge
  C7 — The permuter's search unit is the C expression: it cannot freeze the instructions you already have right, because register allocation couples them
      LOG phase-ends/logs/Phase16.md:43: - **Drew Q&A (permuter):** not one-shot-from-nothing (m2c draft = the info/jumping-off point); function-by-function not whole-file; permuter hill-climbs (additive) but can't freeze individual instructions (regalloc couples them) — compositional fixes happen at
  C8 — An idempotency guard keyed on PRESENCE freezes every record created before the system matured; key it on COMPLETENESS, or re-audit records written before the last capability jump
      LOG phase-ends/logs/Phase15.md:51: - Minor: the 4 Phase-13/T2 proof groups (E_func_80128EA8/8012A568/80132EC4/80138C30) are at 16 members not 134 (registered before the bulk, so --auto-from skips them) — negligible; top up later if desired.

=================== Phase17-18: considered 32 · NEW 6 (found 6) · banked 26 · lines read 538 of 538
  C1 — Leverage and tractability are ANTI-correlated: the most-duplicated functions are systematically the hardest, so a leverage-first queue front-loads hand-tier work and its early bank rate is not a 
      LOG phase-ends/logs/Phase17.md:247:     goto). **Selection lesson:** low-m2c-mismatch struct = the quirk tail; clean closes = fnptr/relocs-low/     m2c-mis-structured. **Sizing (§6):** tractable easy classes are LOW-reach; ×134 yield is in quirk-heavy     STRUCTURAL_MISS(7.6%)/PERMUTER_CLASS(3.6
  C2 — Another decomp project's `INCLUDE_ASM` is a record of what they did not crack, never proof that a class is uncrackable; cross-project corroboration multiplies confidence in a WRONG verdict as rea
      LOG phase-ends/logs/Phase18.md:52: - [x] **T2 — Xenogears mine ✓ 2026-06-20** (2 bg agents; full synthesis `.run/p18/T2_T3_synthesis.md`).   DECISIVE: Xenogears (independent decomp, IDENTICAL gcc-2.7.2-psx -O2) has **NO C lever** for the call-crossing   $s0/$s1 ORDER class — no `register`, no a
  C3 — Your own corpus of byte-matches is an experiment you have already run on the toolchain: settle "is my rebuilt compiler faithful to the original?" from it before installing the original vendor too
      LOG phase-ends/logs/Phase18.md:64:   invoked: Wine is a heavy install on this WSL (106 pkgs + i386 arch not enabled + wineprefix) and the   divergence question is already closed by stronger evidence: (1) **gcc-2.7.2-psx byte-matches ~700 functions**,   many with call-crossing callee-saved value
  C4 — Accelerate the stage that is actually the bottleneck: a byte-exact search loop costs a compiler invocation plus a whole-binary gate per candidate, so GPU/ML brute force buys nothing
      LOG phase-ends/logs/Phase17.md:96: - **CUDA/ML brute-force:** CUDA can't run gcc-2.7.2; the bottleneck is the gcc compile + the whole-binary gate,   NOT search speed, so raw GPU permutation doesn't apply. The real ML angle = a *learned gcc-2.7.2 codegen   predictor/ranker* (Drew has CUDA + Ligh
  C5 — A contradiction between two entries of your own knowledge base is a work item, not noise: replay the levers you have already written down, under the correct oracle, before commissioning any new r
      LOG phase-ends/logs/Phase18.md:26: ~443–571). Phase 17 used the **wrong oracle** (the permuter's floor-polluted score) — §10:518 says use the object-level metric (`match_one.py`), which was **never applied** to the exemplars. §16 ("not source-steerable") contradicts §10 — Phase 18 reconciles it
  C6 — Scope a research phase by a PER-CLASS VERDICT, not by a percentage: the deliverable is a validated lever or an honest, falsifiable wall verdict for each class
      LOG phase-ends/logs/Phase18.md:93: ## Milestone (knowledge-gated, NOT a fleet-% target) Per-class byte-gated verdict (validated C idiom proven on a known-answer exemplar via `p16_known_answer --gate`, OR honest "unsteerable" verdict naming the exact gcc pass); §10-vs-§16

=================== Phase19-20-22: considered 36 · NEW 2 (found 2) · banked 34 · lines read 187 of 187
  C1 — An open-ended grind phase's milestone is invariants held plus a clean checkpoint, never a percentage target
      LOG phase-ends/logs/Phase19.md:24: -O0 lever banked + recovery tooling proven + toolkit scaled across 2–3 batches of 50, fleet up materially (target +3–5%, ~56.6% → ~60%), 136/136 byte-identical from clean (R22), 0 NON_MATCHING (G4), closed at a clean checkpoint with a Phase-20 backlog.
  C2 — Choose the exemplar for cracking a codegen class by the SIZE of its residual: the rows at a one-instruction decompiler-vs-target mismatch are the cleanest real-function isolates of the class
      LOG phase-ends/logs/Phase20.md:14:       `tools/exemplar_miner.py` → `docs/exemplar_curriculum.md` + `.run/exemplar_routing.json` (reach computed from sigs like dedup_propagate). **835 residual stubs routed:** WAVE 472 (218 reach-134, T6 fuel) · STRUCT 159 · **PINS 114 (45 reach-134)** · STUB 9

=================== Phase21: considered 27 · NEW 3 (found 3) · banked 24 · lines read 799 of 799
  C1 — An unattended agent run that looks throttled is usually blocked on an interactive approval prompt; check the pending prompt before diagnosing the provider
      LOG phase-ends/logs/Phase21.md:731: - **Wave-2 "6.5h" was NOT throttling** — it was idle on a CC **permission prompt** (Drew approved on check-in);   waves 1 & 3 ran in ~25–32 min. (R14: corrected my earlier rate-limit read.)
  C2 — A class-distribution assessor only sees the population that has already been attempted; "analyse ALL remaining work" is a cheap triage pass, not a static analysis
      LOG phase-ends/logs/Phase21.md:63: **THE ONE REAL GAP (the refinement worth making): `--assess` clusters the BACKLOG (already-DRAFTED near-misses), not ALL remaining stubs.** A function's "decomp issue" is only known AFTER a draft attempt (the residual = the class). So "analyze ALL remaining" =
  C3 — Say which currency a wave buys — percentage or idioms — before launching it, and judge it in that currency
      LOG phase-ends/logs/Phase21.md:475: 1. **Waves 17–29 — reach-1 (×1) smallest-first harvest:** ~183 banks but fleet only **+0.06%** — reach-1 fns are overlay-unique → ×1, and the fleet metric counts functions across all 136 binaries. Band climbed 14→75 ins, close-rate fell 0.9→0.33. **LESSON: rea

=================== Phase23-27: considered 22 · NEW 8 (found 8) · banked 14 · lines read 172 of 172
  C1 — Mine new idioms from FRESH cracks, never from the failed backlog: your failure pile only re-teaches you what you already know
      LOG phase-ends/logs/Phase23.md:93: - 2026-07-01 (**evening — T10.6 ≤15 campaign + T10.7/8/9 the OpenRouter/GLM5.2 frontier-model exploration**): CONTEXT CHECKPOINT (85% ctx, wind-down). **T10.6 DONE:** `bulk_harvest.py` ≤15 saturation campaign ran 23 cycles → **1,297 banks, fleet 64.6%, ~92% of
  C2 — Give a drafting model a TARGETED slice of the knowledge base, never the whole thing: full context measurably made the model worse
      LOG phase-ends/logs/Phase23.md:24: - [x] **T2 — Stock-local floor** — Qwen3.6-35B-A3B (LM Studio): structurally smart but **0 reliable byte-matches** (can't refine to byte-exact); format-robust; full-cookbook context made it *worse* (dilution). The floor to beat.
  C3 — Name the drafter's degenerate output in the prompt: an empty body compiles, so "translate EVERY instruction, never an empty body" is a required instruction
      LOG phase-ends/logs/Phase23.md:91: - 2026-06-30 (**8-hour autonomous run, Drew away**): prompt-fix + local serving + corpus-v3 + v3 + big batch. **LM Studio ejected** → built **`tools/serve_local.py`** (Unsloth GPU serving as an OpenAI endpoint; the prebuilt llama-cpp-python CUDA wheel SIGILLs 
  C4 — The output-token cap is a two-sided knob, and both failure modes read as "the model is bad"
      LOG phase-ends/logs/Phase23.md:54: **FIXES ALREADY APPLIED THIS SESSION (don't redo):** `api_draft` max_tokens 4096→**512** (killed the no-stop-token ramble, ~80–130s→~10s on the bad cases); `lora_grind` runs `progress.py --fleet` **only on propagate sweeps** (was every batch = ~14s overhead); 
  C5 — Build the unattended campaign so a crash is a pause: probe the dependency at the top of each cycle, commit per cycle, persist the tried-set
      LOG phase-ends/logs/Phase23.md:92: - 2026-07-01 (**T10 — the phase-separated + parallel-gate harvester, BUILT + MEASURED**): plan-mode Tier-1, harvester-first (Drew picked it over vLLM-first — the exploration showed parallel-gate is the bigger single lever, no install, and unblocks the measurem
  C6 — Prove the aggregate check target is fail-closed before adding checks to it, and give every audit oracle a dependent
      LOG phase-ends/logs/Phase27.md:17: 2. **`make report` is NOT fail-closed — roadmap §5 asserts it is.** `Makefile:9-10` sets `.ONESHELL` with **no `-e`** in `.SHELLFLAGS` (verified via `make -p`: `.SHELLFLAGS := -c`), so the recipe is one `bash -c` and only the **last** command's exit survives. 
  C7 — A document that cites a repository path is an untested claim about the repository; lint it
      LOG phase-ends/logs/Phase27.md:71: - **2026-07-15 · Task 3 (addendum) — the allowlist was still too narrow; cookbook §45 cites untracked files.** While reading the seeds for Task 1 I hit a real defect: **cookbook §45 names `.run/giants/func_80133CD4.fable.c` as its worked example and `.run/gian
  C8 — Assert that the work ledger PARTITIONS the live work, and treat a row the invariant refutes as a lie a fresh session will act on
      LOG phase-ends/logs/Phase27.md:45: - [x] **Task 8 — The byte-gate-honest re-scan + partition + ledger rebuild** `[Max]` — **DONE (deterministic core; the 1,670-triage scoped to P29 — see below).** Built **`worklist --assert-partition`** (R32, the audit's literal prescription — enumerate live st

=================== Phase24: considered 35 · NEW 4 (found 4) · banked 31 · lines read 138 of 138
  C1 — Escalations to the expensive tier run STRICTLY SERIAL with idiom-banking between them; only the tier that cannot learn is run in parallel
      LOG phase-ends/logs/Phase24.md:57: - **T7 (resumed, Drew's choice) — sibling-giant harvest via parallel Opus-Max agents (2026-07-03, IN PROGRESS):** launched 5 Opus agents (one per remaining region-a giant), each applying §32/§34, escalating to Fable5 only on stall. **KEY FINDING (answers the f
  C2 — Inside one leverage class, schedule by MEASURED remaining effort — and pull the payoff-dominating outlier out of that queue for an immediate cheap triage
      LOG phase-ends/logs/Phase24.md:29: > The remaining **~9 reach-134 giants (≥150 ins)** to harvest next session (12 reach-134 giants were stubbed post-T7; **this session's batch = func_801392FC/8013A530/8013AF20**, banked HERE first). **Strategy: closest-to-completion FIRST + fast-track the whale
  C3 — The wall-breaker tier is a MATCH tier, not a PLUMBING tier: work that a deterministic arbiter can judge does not need the expensive model
      LOG phase-ends/logs/Phase24.md:61: - **T7 — giant `func_80129CF8` CRACKED (Fable5) + §32 idiom + banked ×1; ×134 WALL found → Drew chose to build the canonical-decl tool (2026-07-03, `8b48f482f`):** Fable5Max cracked the 191-ins region-a camera giant (match_one MATCH) — struct-base hoisting via
  C4 — When a byte-proven body will not integrate, the repair moves the CALLER's declaration to the definition's signature — never the definition to the caller's — and only where the change is width-com
      LOG phase-ends/logs/Phase24.md:119: - **Straggler/caller reconcile is byte-neutral ONLY on the caller's extern** (width-compatible types; the call site casts/passes-wide). NEVER touch the matched def.

=================== Phase25: considered 34 · NEW 3 (found 3) · banked 31 · lines read 561 of 561
  C1 — Leverage ordering does not predict tractability: carry a MEASURED closeness read per target, and never let (reach × size) stand in for "crackable"
      LOG phase-ends/logs/Phase25.md:473: - **Key findings (frontier data → T6):** (1) **byte-weight ≠ tractability** — `func_8014D3E0` (22 ins × 1997) looked like   the mega-ROI freebie but is a `$sp` stack-switcher, matched only by porting an already-matched sibling (`func_8014D04C`);   the 369-gian
  C2 — A fan-out script generated by the orchestrator runs sandboxed with NO access to the repo: it must be self-contained, so target selection belongs to the wave generator, not the workers
      LOG phase-ends/logs/Phase25.md:487: - **Generated a §12-robust scale-up wave** (`tools/workflows/t5_scaleup.js`: worker_wave's drafter prompt + sequential   waves-of-10 + retry×2, targets embedded — sandbox can't read files). Launched over the 83 ≤149-ins targets.
  C3 — Run reference-compiler dump/inspection passes from a scratch CWD (or set an explicit dump base); a `-da` run with CWD at the repo root silently deposits RTL dumps that later read as committed art
      LOG phase-ends/logs/Phase25.md:337: - Housekeeping: `gccdump.lreg` (repo root) = gcc's DEFAULT RTL dump (dump-base "gccdump", `.lreg` = local-reg   pass; `toplev.c:1973/2077`), left by a one-off `cc1 -da` RTL-inspection run with CWD=root — **not** any   committed tool (grep hits only the gcc sou

=================== Phase26: considered 39 · NEW 3 (found 3) · banked 36 · lines read 1106 of 1106
  C1 — A round-trip selftest is a serialisation check, not a coverage check: it passes by construction when a parser's missed item is absorbed into its neighbour's span. Every partition/rewrite tool nee
      LOG phase-ends/logs/Phase26.md:764:   FIRST token and returned at the first depth-0 `;`, so the def after it was never anchored — absorbed into   the next anchor's preamble. **The selftest was structurally blind** (round-trip = `"\n".join(item_texts)`   stays exact by construction when a miss la
  C2 — A set that gates work must be reconstructible from committed artifacts. A roster kept in gitignored scratch is an unversioned oracle: it is silently wrong for anything it was not named after, and
      LOG phase-ends/logs/Phase26.md:742:   R33 applied to "the purest R33 case in the group" (audit). `jr_inventory`'s `banked` set was filtered by an   **EPHEMERAL, gitignored `.run/banked_func_*.json` roster** — `rm -rf .run`/a fresh clone would blind ALL   banked jr at once, cross-address siblings
  C3 — A guard that is allowed to sit RED and UNWIRED does not exist. A detector's value is zero until it is green on HEAD and called by the standing report — and a docstring claiming it is wired is not
      LOG phase-ends/logs/Phase26.md:101: - [ ] **A9 — `lint_symbol_refs`: a guard allowed to sit red does not exist** `[xHigh]` *(blocked on A2)* — currently **RED** (43 false positives) and **UNWIRED** (`make report` never calls it, though its docstring claims it does). No `__asm__("label")` model; 

=================== Phase28-32: considered 32 · NEW 7 (found 7) · banked 25 · lines read 480 of 480
  C1 — Never round-trip a curated config through a serializer: every oracle you own measures BYTES, so a formatting-destructive write is invisible to all of them
      LOG phase-ends/logs/Phase28.md:181:   - **❌ SELF-INFLICTED #1 — I DESTROYED the registry's documentation (H5), and every gate called it green.** My first cut wrote the registry with `yaml.safe_dump`, which round-tripped the whole file: **47 comment lines → 0** (including the curated Phase-11 hea
  C2 — The file a function lives in is not evidence of its class: read the recorded attribute, never the hosting split
      LOG phase-ends/logs/Phase28.md:182:   - **❌ SELF-INFLICTED #2 — I mis-reported the DIFFs, twice (R14).** (a) I claimed ov_SC07_006's 71 non-banks were *"ALL PLUMBING, ZERO DIFF"* — from reading `head -6` of the classified file and generalizing. It has the same 4 DIFFs; the claim is **false and i
  C3 — Re-verify a task's premise in the code at EXECUTION time: roadmap lines, audit findings, and even an audit's own correction footer go stale — usually the document that named a defect is the first
      LOG phase-ends/logs/Phase28.md:143:   - **R14 on the premise first (twice):** (1) the roadmap's two named grinder bugs are **already fixed** (`e91859fb4`, `4927f38c4`) — stale line. (2) `docs/tooling-audit.md:933-937` **downgraded its own finding** with three corrections: *the prescribed fix is 
  C4 — A hardcoded assumption fixed in one tool survives in its siblings: grep the tree for the literal and fix every twin in the same change
      LOG phase-ends/logs/Phase28.md:36:   - `family_remap.img_path` (`:32-35`) hardcodes `0.4.dec` → `None` for the 4 SC07 overlays → `stream_words`→`None` → `classify_member` → `("LEN",[])` → **member silently dropped as not-templatable**. Twin of the P27 T7 `new_overlay.sh` bug, left in a second t
  C5 — A batch gate that bisects on failure re-runs the singleton against an unchanged baseline: special-case n==1 or pay a duplicate build on the hot path
      LOG phase-ends/logs/Phase28.md:58:   - **Unconditional:** the `--chunk 1` double-build (`harvest_verify.py:199-213`) — the bisect re-runs `attempt()` on the same single element vs an unchanged baseline = a duplicate build. 1.35→1.0 builds/draft = **~26% fewer builds on the hot path**, one line.
  C6 — The generated disassembly tree is shared mutable state: a fleet verify/clean chain and the per-function instruments cannot run at the same time
      LOG phase-ends/logs/Phase32.md:255: - **Gotchas (live):** `make clean` deletes `asm/` — never run rtu_match/twin_rescan/frontier_classify while an R22 chain runs · `gate_main`   rewrites main's `asm/` too · the standalone `cc1_dumps.sh` is not faithful on main TUs (use `cc1_dumps_tu.sh`) · the c
  C7 — Write the phase synthesis in a FRESH session that re-reads the committed state cold; the cold re-read is what catches stale artifacts
      LOG phase-ends/logs/Phase28.md:86: **PhaseEnd_Phase28 is the only remaining work** (Tier-1 Max synthesis — write it in a fresh session with headroom; it re-reads the committed state cold, which is the discipline that caught tonight's stale-map/stale-.md traps). Everything it needs is in this fi

=================== Phase29-1of4: considered 46 · NEW 6 (found 6) · banked 40 · lines read 2580 of 2580
  C1 — A stop/continue instrument must aggregate at exactly the unit the decision is made in; one that averages a finer unit manufactures a false "we are at the floor"
      LOG phase-ends/logs/Phase29.md:1283:   **⚠️ THE FLOOR VERDICT WAS AN ARTIFACT — CORRECTED.** `burndown.py` averaged the last 3 INTER-COMMIT   deltas, but the ROI criterion is per-SESSION yield. Three mid-session snapshots of a **+0.7pp** session   averaged to **+0.23** and printed **"AT THE FLOOR
  C2 — Batch size is a RISK lever, not a token lever: isolated agents cost ~N× one agent whether concurrent or serial, so size a batch by the unverified spend you are willing to lose before the next mea
      LOG phase-ends/logs/Phase29.md:2387: > Batch size is a RISK lever, not a token lever: each agent drafts one fn in its own context, so N > agents cost ~N× one agent whether concurrent or serial (~110k tok/drafted fn, measured s14+s15). > Concurrency buys wall-clock only. Therefore **batches of ~5–
  C3 — A repair/`--recover` mode whose cost is (exceptions × population) must be gated on a MEASURED exception count; for a broadly divergent set, drop rather than recover
      LOG phase-ends/logs/Phase29.md:1635: > **⚠️ INCIDENT (recovered, 0 work lost):** `dedup_propagate --recover` on func_80169228 (many byte-divergent > stragglers) THRASHED >1hr (re-gates the fleet per excluded straggler = quadratic). Killed + reverted 326 > half-mutated files to the committed basel
  C4 — A defect reasoned into a sibling tool is LATENT until a run shows its signature; do not patch it on theory right after that tool produced a clean run
      LOG phase-ends/logs/Phase29.md:1191:   were computable, so they are in the tool, not in prose). **(2) LATENT, evidence-gated:**   `jtbl_family_bank` isolates AROUND THE STUB (the body is spliced later, after `remap_hseq`) — the same   ordering defect just fixed in `harvest_verify`. It did **not**
  C5 — Sweep for orphaned worker processes at every session boundary; a dead-pipe compiler or a self-matching wait loop holds a core forever and nothing reports it
      LOG phase-ends/logs/Phase29.md:1029:   **Housekeeping:** killed an orphaned `cc1` from the Jul-21 session that had been burning a full core for   **13h23m** (pid 104350, dead pipe); committed the 4 wave-4 `.o0` drafts left untracked (R20).
  C6 — Land a pure rename and a semantic/layout change as separate gated edits, so a gate failure attributes itself
      LOG phase-ends/logs/Phase29.md:1959:   **`VECTOR` left UNCHANGED deliberately:** ours is 12B vs PsyQ's 16B (missing the trailing `pad`), and I   first called it dead — **WRONG, it has 1 live use** (`engine_core.h` `gte_ldlv0((VECTOR*)sp)`). vx/vy/vz   offsets already agree so a fix is likely byte

=================== Phase29-2of4: considered 43 · NEW 7 (found 7) · banked 36 · lines read 2580 of 2580
  C1 — A verification flag that short-circuits the tool's WRITE path leaves the stale artefact in place and still exits 0
      LOG phase-ends/logs/Phase29.md:2762:   **⚠️ The sharp edge that hid it:** `worklist.py --assert-partition` **exits at the assertion and never   rewrites the doc** — so "regenerating" with that flag leaves the stale file in place and still exits 0.   (Its own assertion printed "160 live stubs, 160
  C2 — A diagnosis earns belief when it predicts its own RESIDUAL membership, not when it explains the failures already seen
      LOG phase-ends/logs/Phase29.md:3690:   binaries** — `func_80174CB0` VERIFIED in **132**, failed in **3**. The class-A census   (`func_80012ABC`: **73 `s32` vs 7 `s16`**) had predicted the class-B fix would leave exactly the   class-A overlays behind, and it left **3** — the same 3 the original sw
  C3 — Make the DRAFTER run the pre-gate guard and return the NAMED banking prerequisite; a batch of diagnosed candidates is worth far more than a batch of opaque MATCHes
      LOG phase-ends/logs/Phase29.md:5093: **⚠️ These are CANDIDATES, not banks (§58/G3/P9).** `match_one` MATCH is a proxy; the whole-binary byte-gate decides, and an earlier 11-core wave had 9/9 match_one MATCHes all gate-fail on integration. What makes this wave different is that the agents were *to
  C4 — When two blockers are orthogonal, a classifier's if-chain ORDER silently becomes the label — cross-tabulate, never bucket
      LOG phase-ends/logs/Phase29.md:4958: The T2 table above ordered its if-chain with `jr` FIRST, so any family carrying a mid-jr was bucketed as "jr → §81 carve chain" **regardless of whether its exemplar needed a crack at all**. That conflated two orthogonal axes and under-reported the zero-crack p
  C5 — Sequence a phase so the cheapest thing that can invalidate everything below it runs FIRST
      LOG phase-ends/logs/Phase29.md:4322: ### Why T0 leads Not caution — **T0 is the cheapest thing that can invalidate everything below it.** If the families template, T2.2 becomes "crack N exemplars and stamp" and most of that bucket evaporates. If they do
  C6 — A reach-weighted gain figure (size × copies) is not a size; every number must say which of the two it is
      LOG phase-ends/logs/Phase29.md:4775: **⚠️ SIZING TRAP (Drew caught me on this):** `nins × members` is **reach-weighted gain-ins**, NOT a function size. `func_80144090` is **154 ins × 136 copies**, not a 20,944-ins monster. **Always label which one you are quoting.**
  C7 — A repair ladder must probe whether each stage is NEEDED before applying it, or it silently escalates a binary-local bank into a fleet-shared one
      LOG phase-ends/logs/Phase29.md:3377:   **⚠️ HYPOTHESIS TO TEST AFTER R22 — the recovery tool may have taken a FLEET-TIER edit it did not   need.** The bank rewrote `src/shared/engine_core.h` (2 lines, `DEFINE_func_80174C60` +   `DEFINE_func_80174C80`) relaxing `extern s32 func_80174CB0(s32, s32);

=================== Phase29-3of4: considered 36 · NEW 6 (found 6) · banked 30 · lines read 2580 of 2580
  C1 — GNU C sources carry form-feed page separators, and `str.splitlines()` splits on them while `grep`/`sed` do not — so any Python line-number checker over compiler source silently drifts, and blames
      LOG phase-ends/logs/Phase29.md:6915: ### The bug: `splitlines()` vs FORM FEEDS GNU C sources use **form-feed (`\f`) page separators** — `loop.c` has 47, `cse.c` 36, `reload1.c` 27, `local-alloc.c` 21. **Python's `str.splitlines()` splits on `\f`; `grep`/`sed`/editors do not.** So
  C2 — Never restructure a proven tool with blind string replaces at the end of a long session; specify it as the next session's first task instead
      LOG phase-ends/logs/Phase29.md:6134: **⚠️ AND I BROKE `family_sweep` TWICE TRYING TO WIRE THE PARALLEL DEFAULT** (missed import, then a closure-scope error) — on the tool that banked 543 members today. **Reverted, not committed.** Restructuring a proven tool with blind string replaces at the end 
  C3 — An oracle that can always be RUN is not always APPLICABLE: state the applicability precondition beside the recipe, or a coarse run returns a large number that reads as a verdict
      LOG phase-ends/logs/Phase29.md:7359: ### 🔧 MAP REFINEMENT OWED — §H's oracle has an unstated PRECONDITION `regalloc.md` §H presents the swap oracle as the way to "discriminate RC-6 (allocation) from S3 (scheduling) in ONE gdb run". It only works when **the contested registers are held by PSEUDOS*
  C4 — Before a fleet-wide mechanical edit, census the whole population for the exact preconditions the edit assumes; perfect uniformity is the licence to apply it, and non-uniformity is the design inpu
      LOG phase-ends/logs/Phase29.md:7520: ### MEASURED BEFORE BUILDING (R35) Ran the blocker census over all 132 still-stubbed siblings before writing a line. It is **perfectly uniform**, which is the strongest possible signal that one mechanical edit fixes all of them:
  C5 — A status line a script prints unconditionally is not a measurement; derive every conclusion the script emits from the command's own output
      LOG phase-ends/logs/Phase29.md:7496: - **Three unconditional `echo` conclusions** (`[shared clean]`, `[none = ...]`) that asserted things
  C6 — Measure what fraction of a cycle a parallelism knob can actually touch before adopting it: `make -j16` bought 12%, because the build was 5 s of a 16 s per-item cycle and the real cost was a four-
      LOG phase-ends/logs/Phase29.md:6115: **The `-j` theory was WRONG, and measuring said so** (baseline ~18 s/sibling): | | | |---|--:|

=================== Phase29-4of4: considered 36 · NEW 6 (found 6) · banked 30 · lines read 2576 of 2576
  C1 — A clean-looking verdict that appears immediately AFTER your own repair transform is a SUSPECT, not a result: re-measure the artefact the transform produced before routing the residual
      LOG phase-ends/logs/Phase29.md:8207: ### ⚠️ A DEFECT I INTRODUCED, CAUGHT BY MEASURING `func_8016163C` read as a clean **DIFF** after T60 and I reported it as "genuine codegen". It is not. `match_one` says **`SIZE-MISMATCH`: draft 58 ins vs target 78** (Δ−20, ratio 0.74, bucket `redraft`).
  C2 — Classify a harness fix as a LOGIC defect or a PATH-REACHABILITY gap and price it accordingly: only the logic defect generalises
      LOG phase-ends/logs/Phase29.md:9957: ### THE BLAST-RADIUS PATTERN, NOW FOUR DATA POINTS | lever | members | kind | |---|---|---|
  C3 — A wrong prescription left in the knowledge base is worse than no entry: when evidence refutes an entry you wrote, correct THAT entry in place, in the same session, carrying the refutation
      LOG phase-ends/logs/Phase29.md:9029: **Reverted** (`git checkout -- src/`, tree clean, nothing committed). Cookbook **§116 corrected in place** — it now carries the refutation and the corollary, because a wrong prescription left in the cookbook is worse than no entry: the next session would have 
  C4 — A name grep is not a "defined / banked here" oracle: a DECLARATION carrying the name reads as a definition; use the structured stub oracle, and believe the pipeline's map over your own check
      LOG phase-ends/logs/Phase29.md:8080: ### FIRST, A CORRECTION TO MY OWN T58 REPORT (R14) I said "7 remaining families all have banked exemplars". **Wrong — there were 5.** `0x80175820` (276 members) and `0x8016ec0c` (138) have **no matched exemplar anywhere**: both are INCLUDE_ASM
  C5 — A yield estimator that counts "unclaimed at the moment it runs" over-projects: it ranks correctly and overstates absolutely; never plan off its absolute numbers
      LOG phase-ends/logs/Phase29.md:9350: ### ⚠️ MY `new_distinct` ESTIMATOR OVER-PROJECTS ~2× (R14) I priced these two families at 130 + 129 = **259** new distinct; the measured gain is **125**. The estimator counts a family's h_exact classes that have no matched instance *at the time it runs*, so
  C6 — Declare a mechanical lever SPENT only on a positive, three-part measurement — every built lever applied and returning zero, the residue split by structure, and the decay curve priced against what
      LOG phase-ends/logs/Phase29.md:10300: The final four days decayed **+2.7 → +2.2 → +0.6 → +0.3pp/day with every lever this phase built applied** — and T98 characterised the residue as **80 families / 960 members / 173 distinct** (29 all-STRUCT refused by design + 51 gate-failing at ~3 distinct per 

=================== Phase30-1of2: considered 50 · NEW 13 (found 13) · banked 37 · lines read 2684 of 2684
  C1 — An instrument's refusal is a FINDING, not an obstacle: overriding it means explaining why the instrument is wrong, never finding another route
      LOG phase-ends/logs/Phase30.md:1369: 4. **VALIDATE:** `tools/validate_targets.py --targets <file> --out clean.json`. Schema needs    `name` + `binary`. It fails closed; **an instrument's refusal is a finding, not an obstacle** —    S46 routed around it and lost 87 of 119 agents.
  C2 — Prose in an agent prompt is not enforcement: snapshot `git status` around every agent and name the offender
      LOG phase-ends/logs/Phase30.md:449: > **3. An agent wrote a TRACKED file** (`src/shared/engine_types.h`, added a typedef) despite the > prompt forbidding it twice. `gate_lane`'s entry guard refused to gate on a tree it did not own — > caught before any commit, cost one gate cycle. **Prose is not
  C3 — Read the FIRST ten results of a long run before trusting the other 190; and negative-control any NEW REFUSAL against everything that already succeeded
      LOG phase-ends/logs/Phase30.md:250: ## 🔑 THE ONE THING TO CARRY FORWARD **Three runs launched at scale, three stopped early — and every stop was right.** The verdicts the tools already write (`harvest_failed.<binary>.classified.txt`) named each defect within the first
  C4 — When a tool is repaired, every verdict it produced becomes a hypothesis again — but re-gate only the drafts the repair's BLAST RADIUS plausibly touched, not the whole ledger
      LOG phase-ends/logs/Phase30.md:2481: claim is suspect: **when a tool is repaired, every verdict it produced becomes a HYPOTHESIS again.** The backlog's `closeness` values and residual classes were produced by tooling that has changed materially this session (§143 alone). **Re-measure before respe
  C5 — A ledger row with no draft artifact is a rumour, not a result
      LOG phase-ends/logs/Phase30.md:2352: **Treat the 14 as UNVERIFIED; start from the committed 63/47 drafts; purge the row if it cannot be reproduced.** General rule worth adopting: *a backlog row with no draft artifact is a rumour, not a result* — `backlog.py log` should require a draft path or mar
  C6 — Check group identity from the signature files BEFORE probing a family: if the members are structurally identical, a 0% result is a compile-error CERTAINTY, not evidence about codegen
      LOG phase-ends/logs/Phase30.md:168:       **🚨 STANDING PRE-PROBE RULE:** check h_norm identity across a family's members from the sig       files BEFORE probing. If members are h_norm-identical, a 0% is a **compile-error certainty**,       not evidence about codegen. And **read `.run/hseq_failed
  C7 — Never test a helper by importing its module: a tool with no `__main__` guard runs its whole pipeline on import
      LOG phase-ends/logs/Phase30.md:2163: ## 🧰 HAZARD INTRODUCED-AND-DOCUMENTED THIS SESSION `tools/harvest_verify.py` has **no `if __name__ == '__main__'` guard**: `import harvest_verify` runs a full build, splices drafts, and overwrites `.run/harvest_*.txt`. I tripped it unit-testing
  C8 — When A/B-ing a harness knob (model, effort, reasoning level), ship a POSITIVE CONTROL that the knob actually moved
      LOG phase-ends/logs/Phase30.md:1541: 3. **The effort/model experiment Drew raised** (design in the S46 log below): a 3-way on ONE target    list in the ≥50-ins band — Sonnet-default vs Fable-low vs Opus-default — with a **positive    control that the effort knob actually moved** (compare per-agen
  C9 — Keep the wave harness IN THE REPO with its contracts; a harness rebuilt from memory each run silently goes stale
      LOG phase-ends/logs/Phase30.md:688: **THE HARNESS IS NOW IN THE REPO** (`tools/wave/crack_wave.js` + README, `54de1bf24`). It had lived only in the workflow scratch dir, so each wave rebuilt it from memory — which is how its cookbook citation list went stale at §162 while §163 (5) and §164 (82) 
  C10 — Do not cross-price two economies: a conversion rate measured on the RESIDUE QUEUE does not price a FRESH wave
      LOG phase-ends/logs/Phase30.md:899: it rather than my framing. **From here the mover is volume with multipliers, not more plumbing.** Corollary it also corrected: **do not cross-price the two economies** — 5:1 is a property of the RESIDUE QUEUE, while a FRESH wave converted 81% (and stored MATCH
  C11 — Derive the target pool from the BUILD'S OWN INVARIANT, not from a reach/similarity metric — reach ranked the most-DONE work first
      LOG phase-ends/logs/Phase30.md:1810: ## 🎯 THE CORRECTED FRONTIER DEFINITION (the session's most useful output) **Reach-141 identifies the most-DONE work, not the most valuable** — those are the shared engine functions banked over 29 phases, present in each overlay as `DEFINE_func_*` macros (~1,61
  C12 — A metric that re-parses source is blind to a body banked through an `#include`; trust the metrics derived from the stub oracle
      LOG phase-ends/logs/Phase30.md:2589: ## 📌 A METRIC SHAPE WORTH KNOWING (R30) A body banked by `#include`-ing a shared header is **invisible to fn-count's NUMERATOR** (the definition is not in the `.c`) while its stub leaves the denominator — the whale bank moved fn-count
  C13 — Keep a glossary line for any term two documents use in OPPOSITE senses
      LOG phase-ends/logs/Phase30.md:1343: 4. **"ZERO-CRACK" MEANS OPPOSITE THINGS** in roadmap §3 T3 ("61 zero-crack = propagation-only") and    in the current map/this file (zero-crack = needs its FIRST crack). **30× mis-scope risk.** One    glossary line in `family-hseq.md` fixes it. Roadmap v2 has 

=================== Phase30-2of2: considered 44 · NEW 6 (found 6) · banked 38 · lines read 2684 of 2684
  C1 — Drafting agents must never be able to write the build tree; every agent artifact lands in a scratch directory, so a killed or racing campaign costs build cycles and zero work
      LOG phase-ends/logs/Phase30.md:4017: - Corollary proven twice: **agents must only ever write `.run/`** — that is why both incidents cost   build cycles and zero work.
  C2 — A stored verdict can be stale because the INSTRUMENT changed, not the draft: re-gate the drafts a tool repair plausibly touched, scoped by the repair's blast radius — never the whole ledger
      LOG phase-ends/logs/Phase30.md:4660: 2. **Whole-payload averaging DILUTES code.** A real overlay is code + a large data tail, so its
  C3 — Count agent completions from the run journal's result records, never from artifact existence: an agent writes its deliverable early and then iterates, so the file proves nothing
      LOG phase-ends/logs/Phase30.md:4001:    *(Counting note, R14: my first count said "2 remaining" because I measured draft-FILE existence.    An agent writes its draft early and then iterates, so a file proves nothing about completion —    the journal's `result` records are the truth. Drew's "12" w
  C4 — A derived claim outranks a heuristic verdict; when two heuristics disagree, take the UNION and queue the disagreements — under-reporting hides work, over-reporting only costs review
      LOG phase-ends/logs/Phase30.md:4657: **L2, the SECOND DISAGREEING ORACLE (R34), earned its keep immediately — it found two L1 defects:** 1. **A claim outranks a heuristic.** I let the statistical verdict override a SHA match, so claimed    binaries were being filed as `classified-data`. Onboarded
  C5 — A failure that will not reproduce earns a negative-control-proven DETECTOR, not a speculative fix; and every abort path must PROVE its revert by diffing the worktree against a baseline captured a
      LOG phase-ends/logs/Phase30.md:4064: checked out. **I did not "fix the bug"; I made the next occurrence name itself.**
  C6 — Never let model-authored prose reach the shell inside double quotes: a backticked command in a `git commit -m` message EXECUTED
      LOG phase-ends/logs/Phase30.md:2893: 4. **A backticked `` `make extract` `` in a `-m` commit message EXECUTED** — corrupted the message    and ran a real extract. Use quoted heredocs. (No damage; re-committed.)

=================== Phase31-1of3: considered 52 · NEW 12 (found 12) · banked 40 · lines read 2902 of 2902
  C1 — More output-token budget is NOT more quality; measure it as a paired A/B and treat truncation as recoverable, not as a defect signal
      LOG phase-ends/logs/Phase31.md:2292: snapshot-restore per draft under per-binary locks. **BANKABLE: 8k 10/10 · 16k 10/10 · 24k 8/10 · 32k 8/10** (big arms: two budget-never-converged NO-DRAFTs plus the 55-ins fn BYTE-DIFF in both). Truncated turns 6/1/0/0 — truncation recovers across the turn loo
  C2 — In a pipelined drafter/gater, "still open" is not "not yet attempted": consecutive waves re-drafted the wave still in flight
      LOG phase-ends/logs/Phase31.md:258: 3. **Every second wave re-drafted the wave still in flight** — `--retry-unbanked` returns still-open    cards and the pre-draw runs WHILE a wave drafts, so ck->cl were 239/239 identical, co->cp 238/238.    Yield alternated 47.6% / 3.8% / 35.3% / 3.6%. Fixed by
  C3 — Snapshot every target's disassembly BEFORE gating: a successful bank prunes it, and every downstream step needs both sides
      LOG phase-ends/logs/Phase31.md:1612: * Snapshot every target's `.s` BEFORE gating — banking prunes it and recovery/harvest need both sides.
  C4 — Draft first, then carve: a build-unit split is only safe when the new unit is immediately populated with proven bodies
      LOG phase-ends/logs/Phase31.md:922:    6,414 ins, zero drafting). **Draft-first ordering is what makes carves safe: populated-at-carve    is 137/137; stubs-in-new-object was 1/4 and 2/2.**
  C5 — A cracked idiom transfers WITHIN its family and not across it: price a lane by families, not by class size
      LOG phase-ends/logs/Phase31.md:1300:    **11 turns/3 oracle MATCH** -> cross-family **56 turns/0 compiles, FAILED**. So jtbl costs ~40    turns of learning **per family** (191 families), not per class. The jtbl quest is a project, not    a lane — defer it.
  C6 — Sibling count and never-drafted count are different denominators; conflating them overstated the free-remap leverage ~3× and hid that the remaining mass was singletons
      LOG phase-ends/logs/Phase31.md:298:   measures: 3,106 open instances · 2,245 open skeletons · 1,772 groups, of which **480 are   multi-member holding 1,334 siblings** and **1,292 are SINGLETONS carrying 57% of the open   instruction mass**. My "~3,900 siblings behind ~334 skeletons" conflated tw
  C7 — "Never write the tree" in a drafting prompt is a request, not an enforcement
      LOG phase-ends/logs/Phase31.md:2879: * **A wave agent WROTE to `src/` and then `git checkout`-reverted it** (SYS_OBJ_2264, self-reported).   It was harmless ONLY because R42 meant every bank was already committed. The prompt's "never modify   src/" is a request, not an enforcement — candidate: *a
  C8 — A free or preview model tier can be withdrawn mid-campaign without notice; a fleet-wide 404 is an epoch event, not N model failures
      LOG phase-ends/logs/Phase31.md:2319: ### THE OX WINDOW CLOSED — 2026-08-26 07:55 (probed: HTTP 404 on stealth/ox-alpha; stealth/* gone from the model list) The free-drafting era ended mid-m0b (its 29 agents all 404'd at turn 0 — a harness-epoch event, not 29 model failures, R40). THE GOAL BEAT TH
  C9 — A metered API key's own cap is a separate limit from the account's credit
      LOG phase-ends/logs/Phase31.md:2380: **DeepSeek push paused by a KEY CAP, not the budget (10:4x, R40-corrected):** the OpenRouter key carries a $60 LIFETIME limit; usage hit $60.21 mid-ds2 and every request 403s ("Key limit exceeded (total limit)") while the ACCOUNT still holds ~$10.6 credit. ds1
  C10 — Incremental gates never exercise the extraction/regeneration step, so regeneration rot is undated and invisible for weeks
      LOG phase-ends/logs/Phase31.md:2376: nothing — a fresh-eyes day-session surgery. The general lesson repeats §61c with a new edge: INCREMENTALLY-GREEN HIDES EXTRACT ROT — a periodic `make extract` sweep per binary (not just check-all builds) would have dated defect (a) precisely.
  C11 — A probe that splices the tree in order to measure it must restore it, or the progress oracle counts the splices as banks
      LOG phase-ends/logs/Phase31.md:2598: next pass / T6. Instrument lessons of the task: a stale classification file re-labels every fn "CARVE-REFUSED" until re-gated (verify from the gate, not the ledger); an autopsy script without its scratch dir leaves TUs spliced and `corpus` then reads them as b
  C12 — Keep prompt/law text in data, not inside the launcher's source template
      LOG phase-ends/logs/Phase31.md:1702: * A wave script's LAWS block is a JS template literal: **backticks inside the law text terminate it**.   Wave U's first launch died on exactly that; write law text with single quotes.

=================== Phase31-2of3: considered 52 · NEW 11 (found 11) · banked 41 · lines read 2902 of 2902
  C1 — The health suite must assert that a tool DID ITS WORK, not only that the data is intact: zero inputs, an impossible wall-clock and a missing persistent effect are each a DEFECT, not a result
      LOG phase-ends/logs/Phase31.md:5122: **ITEMS 2+3 — `tools/work_evidence.py`, wired and negative-controlled.** One module, three assertions, all about OBSERVABLE CONSEQUENCE rather than internal state: * `assert_inputs` — zero readable inputs is a DEFECT, not a zero-yield result. **"0 of 0" is a f
  C2 — A health check that cannot finish is not a check: keep the health target sampled and fast, and put the exhaustive form behind its own name
      LOG phase-ends/logs/Phase31.md:5175: - **S70 — `make tools-health` WAS UNRUNNABLE AND IS NOW 333s GREEN.** Drew: *"this is a tools health   test, not a full regression test."* Correct — `audit-cdecl` re-parsed **every declaration in all   4,168 TUs** and handed each to real gcc: **~787s of pure-P
  C3 — "Independent" names the INSTRUMENT, not the input: two refusals of two separately-written drafts from one tool is one test repeated
      LOG phase-ends/logs/Phase31.md:3589: **"Independent" means a DIFFERENT INSTRUMENT, not a different input.** Two runs of one tool on two drafts is one test repeated. R40, sharpened.
  C4 — A drafting agent must run where it CANNOT write the source tree; "never modify src/" in a prompt is a request, not an enforcement
      LOG phase-ends/logs/Phase31.md:2879: * **A wave agent WROTE to `src/` and then `git checkout`-reverted it** (SYS_OBJ_2264, self-reported).   It was harmless ONLY because R42 meant every bank was already committed. The prompt's "never modify   src/" is a request, not an enforcement — candidate: *a
  C5 — A proven transform that is not a rung of the ladder the agents' drafts actually pass through does not exist for those drafts
      LOG phase-ends/logs/Phase31.md:3810: `scope_data_externs.fix()` (§8d) has been byte-proven since Phase 26 and is used by `family_sweep` / `bank_exemplar` / `jtbl_family_bank` — but **nothing in `gate_stage`'s ladder ever called it**, so a draft written by a wave agent had never seen it. Built as 
  C6 — The knowledge-harvest selector must be able to see FAILED attempts; a filter that can only read banked work learns from the easy half
      LOG phase-ends/logs/Phase31.md:3236: 5. **The distill novelty selector was INVERTED** (`91e624c04`): `'no cookbook lever'` matched "no    cookbook lever *needed*" (a TRIVIAL note) and was the only pick of 24, while three multi-lever    notes went unseen — **and it structurally could not see UNBAN
  C7 — A refusal names the branch the caller entered, not the subject — make the applier consult the classifier it already has
      LOG phase-ends/logs/Phase31.md:3346: 4. `--probe-only` crashed for `--funcs`/`--auto` (exec'd before staging). 5. The distill novelty selector was INVERTED (its only pick of 24 was a "nothing to learn here" note)    and could not see UNBANKED fns at all — where the hardest functions write their r
  C8 — Every status claim in an agent's context must be expiry-checked against live state, or agents will report it back to you as an observation
      LOG phase-ends/logs/Phase31.md:5394: 5. **stale BASELINE-RED verdict** — OPEN. THREE agents reported a red baseline on binaries I verified    BYTE-IDENTICAL; the third revealed the source: *"the pack's last gate verdict was BASELINE-RED"* —    they read it off the card. Cost me two phantom-regres
  C9 — A validity stamp must be honoured by every downstream consumer; and a wrong write-side label cannot be repaired by a correct read key
      LOG phase-ends/logs/Phase31.md:5437:   * **#4 SYMBOL MISMATCHES — sound=True, SHIPPED.** `gate_feedback` gated on `shape=='MATCH'` when     reloc_identity's binding condition is **`aligned`** (shape AND equal reloc-stream lengths). Below     that bar reloc_identity itself downgrades status to `MI
  C10 — Yield is clustered by binary, not spread over the fleet: draw per-binary once two independent lanes concentrate in the same place
      LOG phase-ends/logs/Phase31.md:5040: **20 of 52 twin remaps banked (38%)**, well above §398's ~15% straight-through — and **all 20 in `ov_SC06_011`**, the same binary that carried 15 of the 21 standalone banks. Two lanes, same concentration: `ov_SC06_011` is simply a binary whose open tail is hig
  C11 — (minor) A build-system conditional that expands at PARSE time makes its own negative control vacuous
      LOG phase-ends/logs/Phase31.md:5155:   *Make gotcha worth keeping: my first patch used `ifeq ($(filter $*,...))`, which make evaluates at   PARSE time when `$*` is empty — it would have silently always taken the maspsx branch and the   "byte-inert" result would have been vacuous. `$(if ...)` expa

=================== Phase31-3of3: considered 30 · NEW 7 (found 7) · banked 23 · lines read 2931 of 2931
  C1 — Never wrap a project tool in a `timeout` shorter than its own internal budget; you pre-empt its documented recovery handler and lose its buffered output
      LOG phase-ends/logs/Phase31.md:7024: * **Never wrap a project tool in a shorter `timeout` than its own budget.** My `timeout 2400` beat   `gate_stage`'s 3600 s budget, SIGTERM'd the tree mid-propagation, and Python lost its buffered   stdout — three gates with NO verdict and three half-applied, n
  C2 — A programmatic edit to a long-lived knowledge document silently truncates or duplicates it; verify the sections, never the commit
      LOG phase-ends/logs/Phase31.md:6529: 1. **§429 had been SILENTLY DELETED from the cookbook.** My §428a rewrite wrote    `t[:start] + new` instead of `t[:start] + new + t[end:]`, truncating everything below it. §429    ("every held pointer needs its own local") was gone for the rest of the session
  C3 — The live hand-off block must be strictly APPENDED at the end of its file: file order is the only recency signal a fresh session has
      LOG phase-ends/logs/Phase31.md:6126: > **The "last block is the live one" rule was BROKEN when this session started** — S70 FINAL-5 sat > below S71 CLOSE in file order while being a day older. This block is appended at the END, which > restores the rule. Keep appending.
  C4 — A long stateless batch must persist each confirmed result the moment it is confirmed
      LOG phase-ends/logs/Phase31.md:7121: 3. **`gate_main` writes banks only at the END.** `try_batch` is stateless — every attempt is    `git checkout` main's TUs → `make extract` → substitute → build — so a 34-minute bisection holds    its result in memory and a kill loses all of it. Writing each co
  C5 — "Idempotent by SKIPPING" seals an artifact against later evidence; make regenerated artifacts idempotent by REPLACEMENT
      LOG phase-ends/logs/Phase31.md:6171: * **`journal_notes.py`** — was idempotent by SKIPPING, so a pack with one old note could never   receive a newer one, and `claude_wave_packs` calls it at build time, so **every pack with any   history was sealed against later evidence**. Now idempotent by repl
  C6 — A verification target too slow to complete is not a check: sample it by default and keep the exhaustive form as a separate target
      LOG phase-ends/logs/Phase31.md:6027: * `make tools-health` — was UNRUNNABLE (>15 min, never once completed). `audit-cdecl` was a full-corpus   regression test in a health target (~787s of pure-Python collection before the first cc1 call). Now   sampled (`CDECL_AUDIT_TUS ?= 60`, 61s); `audit-cdecl
  C7 — Never adopt a subagent's worktree wholesale: it is a snapshot of an older tree and may predate a bank; re-gate its artifacts against HEAD
      LOG phase-ends/logs/Phase31.md:6808: * **Never adopt an agent's worktree wholesale.** One predated a bank of `func_8017F9C0`; copying its   TU would have destroyed it. Re-gate against HEAD with the fixed tools instead.

=================== Phase33: considered 37 · NEW 16 (found 16) · banked 21 · lines read 1372 of 1372
  C1 — A Ghidra script directory compiles as ONE bundle: a single non-compiling script disables every script in it
      LOG phase-ends/logs/Phase33.md:186:   with '.'; `resident_funcs.txt` from the ELF = 1,304 entries). **Blocker found:** in the resident rebuild the runs after the   import failed with `Failed to get OSGi bundle containing script: …/tools/ghidra_scripts/ApplySymbols.java` (same for   ExportAnnotat
  C2 — Ghidra refuses a project path containing a component that starts with `.` — a scratch project cannot live under `.run/`
      LOG phase-ends/logs/Phase33.md:185:   step works: the scratch project must live under `build/ghidra_rebuild/proj` — Ghidra refuses a path component starting   with '.'; `resident_funcs.txt` from the ELF = 1,304 entries). **Blocker found:** in the resident rebuild the runs after the
  C3 — `git check-ignore` is SILENT for tracked paths: an ignore-coverage audit run before the untracking passes vacuously
      LOG phase-ends/logs/Phase33.md:236:   project-authored inside a purged dir — CHECKSUMS had moved in B4); ignore coverage proven with `git check-ignore   --no-index` on every path (the plain form is BLIND to tracked files — it reported nothing); **control: main byte-identical
  C4 — A coverage instrument that infers its denominator from OPEN work INVERTS at 100% — carry the scanned denominator in the artifact, and test the instrument at both endpoints
      LOG phase-ends/logs/Phase33.md:126: - **2026-09-06 (S86) — A4 (family map regen → instrument fix, R35).** Regenerating `.run/family_hseq.json` made the   `audit-binaries` warning WORSE (6 → 217 "missing"): at 100% the map's `families` list is empty and CHECK 4 inferred coverage   from family mem
  C5 — An annotator that writes into the text it reads must never treat its own output as evidence
      LOG phase-ends/logs/Phase33.md:499:   lines — the input to an override). **Three instrument defects, found by its own controls/verify before any tag was written   (R39/R57):** (1) span pairing inside a ±160-char window inverted the backtick pairs and dropped the identifiers right   next to a cit
  C6 — Regex-extracted evidence needs a structural marker, or prose becomes data
      LOG phase-ends/logs/Phase33.md:503:   caught by `--verify`. Bare ALL-CAPS prose words (`NOT`, `AND`, `DEST`) had also passed as evidence: identifiers now need an   underscore, as every real gcc macro/function cited has. **Final census:** `[2.7.2]` 79 · `[2.8.1 pm]` 55 · `[repo]` 1 ·
  C7 — `objdump -dr` interleaves relocation records only for OBJECT files; a linked ELF lists them separately and shifts the address column
      LOG phase-ends/logs/Phase33.md:526:   **8/8 OK**. Two gotchas, recorded: `objdump -dr` interleaves relocation records only for OBJECT files — a linked ELF lists   them separately (`-r`, section-relative offsets), so the generator merges them into the listing in the object-listing   format; and a
  C8 — A derive-then-apply pipeline over a live repository needs a freshness guard, and a stated sequencing law
      LOG phase-ends/logs/Phase33.md:285:   added to `run_filter.py`: it refuses a dictionary whose main count/HEAD differ from the clone's (a stale dictionary would   drop rows from the public map; trial #2 matched by construction). **Sequencing law for C4:** the dictionary + ids are   rebuilt from t
  C9 — A content-hash "no ROM bytes" audit collides on zero-length files
      LOG phase-ends/logs/Phase33.md:205:   TUs from `<alias>_SRC_DIR` with nested pruning, skips DERIVED: 70 LINKED + 47 INCLUDE_ASM, -O0 TUs compiled at -O0;   measured PR scope 54/54 in 1.6 s, **fleet 4,170/4,170 in 123 s at -j32, failed 0**; unknown alias refused);   `.github/workflows/no-rom.yml`
  C10 — `git push --mirror` does not push `refs/stash`
      LOG phase-ends/logs/Phase33.md:295:   **private, not a fork, no parent**; `git ls-remote archive` == local refs except **`refs/stash`, which `--mirror` does not   push** (the bundle holds it; Drew may push it as a branch). C4c: FINAL dictionary on the committed tip (4,422 commit objects,
  C11 — Route a host purge request through the flow that actually exists; the obvious form is a trap
      LOG phase-ends/logs/Phase33.md:635: - **2026-09-07 (S89) — C10: the GitHub Support ticket is FILED — #4736982** (`https://support.github.com/ticket/personal/0/4736982`,   Drew, via the Support portal's **Virtual Agent "Clear cached views"** flow — the route that actually works: Repositories form
  C12 — A host feature can be gated on the very flip it was meant to precede: read the settings page, don't infer
      LOG phase-ends/logs/Phase33.md:692:   ~~The wiki can be pushed NOW~~ — **WRONG (R14, corrected minutes later):** GitHub's settings page reads "Upgrade or make this   repository public to enable Wikis"; on the free plan wikis exist only on public repos, so the wiki waits for the flip. `wiki_sync.
  C13 — A public scratch service's compiler image is NOT your pinned toolchain; rebuild it locally and prove byte-identity before asking for a preset
      LOG phase-ends/logs/Phase33.md:645:   is old-gcc **0.13** + maspsx **`86ccd7d8`** (not our 0.17 + `874855c5` — SETUP's "same pinned commit we use" was stale; three   rows corrected, R14) with `as` = a maspsx `--run-assembler` wrapper (so `-Wa,--aspsx-version=2.56,--expand-div` reaches   maspsx);
  C14 — A miner over your own records finds only what its pattern anticipates: measure the widened pattern's yield
      LOG phase-ends/logs/Phase33.md:429: - **2026-09-07 (S87, Max) — F2 the retrospective.** `tools/mine_hindsight.py` (stdlib; the decision-log's `Hindsight`   bullets AND `### Hindsight` sections — 19 over 79 entries after widening the pattern, the first cut found 11 —, the two   "What we believed"
  C15 — A harness's low-memory guard silently kills a long BACKGROUND job — and workers from closed phases survive for days
      LOG phase-ends/logs/Phase33.md:508:   `doc_links --strict` PASS (41 documents, 301 links, 0 broken). Gotcha, recorded: the first tools-health run was KILLED by the   harness's low-memory guard during the report step (a transient spike; 29 GB available afterwards) — and the process table   held *
  C16 — A `cd` in one agent shell call persists into the next
      LOG phase-ends/logs/Phase33.md:660:   SETUP §6.5 rewritten + 2 inventory rows + the P33 E1 section + ledger row 14. Gotcha, recorded: a `cd` in one Bash call   persists into the next — the first download landed inside `tools/maspsx/` (moved out; submodule clean). Commit: see below.

=================== Phase7: considered 28 · NEW 5 (found 5) · banked 23 · lines read 201 of 201
  C1 — A decompiler's `unaff_<reg>` output means it decompiled ONE entry path of a multi-entry function and handed you a fragment; that is an instrument limit, never evidence the function is hard
      LOG phase-ends/logs/Phase7.md:109:   **(session G cont.)** Then the 4 jtbl loaders: **CdReadStateMachine / CdReadSectorReadyCB / StreamLoadStateMachine NON_MATCHING-drafted** (faithful translations of the Ghidra decompile; all valid C under `-DNON_MATCHING`, verified via a cpp→cc1 syntax check;
  C2 — A milestone counted in "matched functions" must exclude the splitter's auto-generated empty bodies; define the bar on substantive matches at the moment you set it
      LOG phase-ends/logs/Phase7.md:12: - **≥25 = real substantive matches** (the 42 splat-auto empties do NOT count). 14 real now → need ≥11 more.
  C3 — Duplicate/family census run before the vendor library is linked out is contaminated: the duplicate groups are library fragments and epilogues, not game functions
      LOG phase-ends/logs/Phase7.md:26: - [x] **Task 4 — Harvest to ≥25 real** ✓ DONE. **36 real matches** (14 + 22 trivial accessor leaves: getters/setters of globals, one mask, one two-store), build BYTE-IDENTICAL → all 22 byte-perfect. **≥25 bar PASS** (margin 36/25). `.run/harvest.py` = the appl
  C4 — A byte-identical baseline is only proven when the whole gate is green from clean across several INDEPENDENT sessions; one green run hides a nondeterministic extract
      LOG phase-ends/logs/Phase7.md:75: NOTE: Gen1 exit needs ≥3 SESSIONS of green `make check` — **satisfied** (A, B, C, D, E, F, +G); Tasks 6/7 pending.
  C5 — When a foundation task hits a structural wall mid-phase, reorder: bank the tractable wins first and re-scope the wall as its own focused sub-project
      LOG phase-ends/logs/Phase7.md:3: **Status:** Plan APPROVED 2026-06-14. **REORDERED 2026-06-14** (Drew): bank non-switch wins first; the rodata-island foundation + LZSS match are DEFERRED to a focused sub-project after the easier tasks.

=================== Phase8-13: considered 38 · NEW 4 (found 4) · banked 34 · lines read 400 of 400
  C1 — A toolchain/SDK-version detector's verdict is a HYPOTHESIS until a placement COUNT backs it; when a version stamp and a byte-probe disagree, the probe wins — and the refuted stamp must be un-bank
      LOG phase-ends/logs/Phase10.md:44: ## Key finding (T4, 2026-06-15) — resident is PsyQ **4.7.0**, not 4.0.0 DetectPsyQ on the imported resident program reports **PsyQ Version = 470** (the EXE is 4.0.0); the import associated a `psyq470` source archive alongside `psyq400`; the one PsyQ-signature 
  C2 — Histogram a secondary binary's `jal` targets BY ADDRESS RANGE before assuming it carries its own copy of anything
      LOG phase-ends/logs/Phase12.md:45:   - **Ghidra verification (Drew-requested, G1 — CONFIRMS the pivot):** switched the headless MCP to the `resident` program (296 funcs); decompiled a sample. `FUN_800cf854` = game-global accessor (`return DAT_800ae6bf != 0`); `DsMix` = `{FUN_800d1bf8(); return 
  C3 — A raw blob's load address is a hypothesis; the free confirmation is arithmetic against the NEXT known segment's base
      LOG phase-ends/logs/Phase10.md:13: - Load **vram 0x800CEDF8** (Phase-3 T6b proven); `VRAM_BASE`=0x800CEDF8 (fileoff 0→vram). Computed **end vram 0x80128154** (4 B under overlay slot 0x80128158 — boundary corroboration).
  C4 — ⚠ LOW VALUE, recommend dropping: during a parameterization refactor whose oracle is a byte-locked binary, generalize only what a second target actually needs
      LOG phase-ends/logs/Phase9.md:26: - [x] **T1** — Makefile data block (BINARIES/main_*/aliases; wrapped 9 integrate blocks in `ifeq ($(BINARY),main)`). DONE: aliases resolve byte-identically; `BINARY=bogus` errors; clean build ⇒ `143dbb89` + report 52/959/7/50.24%. **Refinement vs plan:** SDK-r

TOTAL over 21 slices: considered 777 · NEW 143 · already-banked 633 · lines read 30540
