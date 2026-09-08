# Log mining — Phase17-18
Files/ranges: `phase-ends/logs/Phase17.md`:1-301 · `phase-ends/logs/Phase18.md`:1-237  ·  Lines read: 538 of 538
Candidates considered: 32 · NEW: 6 · ALREADY-BANKED: 26

Grep denominator for every "not banked" test below (the brief's file set, expanded):
`docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md docs/retrospective.md
docs/wave-playbook.md docs/how-to-ai-decomp/*.md decomp-architect/corpus/decomp-kernels.md
decomp-architect/templates/registry-E.decomp.md phase-ends/DIGEST.md` — referred to below as `$F`.

## NEW

### C1 — Leverage and tractability are ANTI-correlated: the most-duplicated functions are systematically the hardest, so a leverage-first queue front-loads hand-tier work and its early bank rate is not a harness fault
- **Evidence:** `phase-ends/logs/Phase17.md:247-249` —
  > **Sizing (§6):** tractable easy classes are LOW-reach; ×134 yield is in quirk-heavy
  > STRUCTURAL_MISS(7.6%)/PERMUTER_CLASS(3.6%).

  corroborated at `phase-ends/logs/Phase17.md:297-300`: *"the layer makes the high-reach circular targets declarable but they are the gcc-quirk tail … Wave yield is quirk-tail-limited (~2-4% fleet), NOT ~2×."*
- **What happened / what it cost:** Phase 17 hand-matched the 4 highest-reach (reach-134) targets after building the canonical-sig layer for them and banked **0 of 4** — every one was regalloc/hoist/layout-bound (`Phase17.md:286-296`). The same session's cheap closes were the *low*-reach classes (fn-ptr, low-reloc, badly-structured decompiles). Two sessions of top-of-queue effort produced one banked reach-134 function while the tractable set sat below it, and the phase's projected wave yield had to be re-cut from "~2×" to "quirk-tail-limited".
- **Not banked — greps:** `grep -n -i 'tractable.*low.reach' $F` → 0; `grep -n -i 'leverage.*anti' $F` → 0; `grep -n -i 'highest.reach.*hardest' $F` → 0; `grep -n -i 'easiest.*lowest.value' $F` → 0. Nearest hit is the *prescription* `docs/how-to-ai-decomp/03-bootstrap-order.md:93` ("Order by leverage, not difficulty … highest (reach × size) first") — it tells you to sort that way but nowhere records that the sort is also a difficulty sort, nor what to expect from it.
- **Proposed home:** DK (a kernel), appended as the empirical half of the leverage-first ordering already in chapter 03.
- **Portable because:** in any duplicated-binary project (overlays, statically linked libraries, multi-build ROMs) the most-shared code is the engine core — bigger, call-heavier, more optimized — so ROI-first and easy-first are opposite orders on every target, and a leverage-first lane will look like a failing lane for its first stretch.

### C2 — Another decomp project's `INCLUDE_ASM` is a record of what they did not crack, never proof that a class is uncrackable; cross-project corroboration multiplies confidence in a WRONG verdict as readily as a right one
- **Evidence:** `phase-ends/logs/Phase18.md:52-54` —
  > DECISIVE: Xenogears (independent decomp, IDENTICAL gcc-2.7.2-psx -O2) has **NO C lever** for the call-crossing
  > $s0/$s1 ORDER class — no `register`, no asm pins, no permuter; they **ship it as INCLUDE_ASM** (1174 nonmatch).

  and the reversal at `phase-ends/logs/Phase18.md:136-138`: *"The T1-T5 'regalloc-order = UNSTEERABLE' verdict was **WRONG** (P9/R14 self-correction — I'd skipped the most direct lever). **Explicit register pinning works**."*
- **What happened / what it cost:** the sibling project's give-up point was treated as independent confirmation and hardened a wrong verdict through T2, T3, T4 and T5 — it was written into the cookbook (§17 and the §16 reconcile), and it re-scoped the *next* phase to "triage-and-stub the unsteerable" (`Phase18.md:80-82`). One directive to try pins reversed it in a session: `func_8012B8E4` went 21 → MATCH and propagated ×134 (`Phase18.md:139-143`). The cheapest lever in the toolkit was skipped because two independent sources agreed there was none.
- **Not banked — greps:** `grep -n -i 'include_asm.*proof' $F` → 0; `grep -n -i 'sibling project.*gave up' $F` → 0; `grep -n -i 'another project.*impossible' $F` → 0; `grep -n -i 'corroborat.*wrong verdict' $F` → 0. The corrected *fact* exists only as a parenthetical about this one class (`docs/matching-cookbook.md:1420`, "Xenogears ships this class as INCLUDE_ASM only because they hadn't found the pin lever"); the records elsewhere say only the positive half — mine sibling projects for idioms (`decomp-kernels.md:196`, `03-bootstrap-order.md:89`, `07-compiler-source.md:99`).
- **Proposed home:** DK (a kernel) or a G-rule attached to G51/G52 — the evidence rule for cross-project inputs: a sibling's matched code is positive evidence; a sibling's unmatched code is no evidence.
- **Portable because:** every mature decomp scene has neighbours on the same compiler, and their `NONMATCHING`/`INCLUDE_ASM` lists are the first thing an agent finds and the easiest thing to mistake for a proof of impossibility.

### C3 — Your own corpus of byte-matches is an experiment you have already run on the toolchain: settle "is my rebuilt compiler faithful to the original?" from it before installing the original vendor toolchain
- **Evidence:** `phase-ends/logs/Phase18.md:64-70` —
  > Plan escape clause invoked: Wine is a heavy install on this WSL (106 pkgs + i386 arch not enabled + wineprefix)
  > and the divergence question is already closed by stronger evidence: (1) **gcc-2.7.2-psx byte-matches ~700 functions**,
  > many with call-crossing callee-saved values → its global register allocation IS faithful to the original compiler
- **What happened / what it cost:** a whole planned task (W1) existed to run the real `CC1PSX.EXE`/`ASPSX.EXE` under Wine to test whether the compiler *build* explained the residual. It was dropped and answered for free from three existing sources: ~700 already-matching functions (many exercising the exact pass under suspicion — a divergent compiler would have broken them), a directly-tested sibling `cc1` build that diverged and was *worse* (32 vs 21 mismatches), and the sibling project's era toolchain. The install was never done and the verdict has held since.
- **Not banked — greps:** `grep -n -i 'build divergence' $F` → 0; `grep -n -i 'original compiler binary' $F` → 0; `grep -n -i 'existing matches.*compiler.*faithful' $F` → 0; `grep -n -i 'ruled out by proxy' $F` → 0; `grep -n -i 'wine\b' $F` → 0. The records cover choosing and pinning the compiler triple (`03-bootstrap-order.md:24`) but never say that the accumulating match corpus is itself the evidence about the toolchain.
- **Portable because:** every decomp runs on a rebuilt or substituted compiler and every one of them eventually asks "is my build the original build?"; the answer is a free query against work already banked, and the alternative is a day of emulation plumbing. The construction generalizes: **pick the suspect pass, count how many existing matches exercise it.**
- **Proposed home:** accelerator (a "do this instead" with a measured saving), cross-referenced from chapter 07.

### C4 — Accelerate the stage that is actually the bottleneck: a byte-exact search loop costs a compiler invocation plus a whole-binary gate per candidate, so GPU/ML brute force buys nothing
- **Evidence:** `phase-ends/logs/Phase17.md:96-99` —
  > **CUDA/ML brute-force:** CUDA can't run gcc-2.7.2; the bottleneck is the gcc compile + the whole-binary gate,
  > NOT search speed, so raw GPU permutation doesn't apply. The real ML angle = a *learned gcc-2.7.2 codegen
  > predictor/ranker* … a high-risk, months-long research wildcard … NOT the plan.
- **What happened / what it cost:** the project owner had the GPU and the ML skills, and the proposal was live enough to be written into the phase's deferred list. Naming the per-candidate cost (a serial cc1 run plus a link and hash of the whole binary) killed it in one paragraph and redirected the same instinct at the only place a learned model could sit — ranking candidate C shapes — which was correctly parked as research, not plan. It also records that no off-the-shelf byte-exact MIPS/gcc decompiler exists, so "just use an ML decompiler" is answered too.
- **Not banked — greps:** `grep -n -i 'cuda' $F` → 0; `grep -n -i 'search speed' $F` → 0; `grep -n -i 'bottleneck is the compile' $F` → 0; `grep -n -i 'gpu-hours\|gpu accelerat' $F` → 1 (`docs/decision-log.md:99`, about renting a bigger GPU for *fine-tuning a 7B drafter* — a different subject).
- **Proposed home:** DK (a kernel) — a one-line refutation to hand a future project the first time hardware is proposed as the answer.
- **Portable because:** the proposal is perennial (GPUs, ML decompilers, "just brute force it") and the refutation is architectural, not BFM-specific: the inner loop is a serial, CPU-bound, host-toolchain compile plus a link, and neither moves to a GPU.

### C5 — A contradiction between two entries of your own knowledge base is a work item, not noise: replay the levers you have already written down, under the correct oracle, before commissioning any new research
- **Evidence:** `phase-ends/logs/Phase18.md:26-29` —
  > Phase 17 used the **wrong oracle** (the permuter's floor-polluted score) — §10:518 says use the
  > object-level metric (`match_one.py`), which was **never applied** to the exemplars. §16 ("not
  > source-steerable") contradicts §10 — Phase 18 reconciles it. So: **existing-knowledge-first**
- **What happened / what it cost:** two sections of the cookbook had said opposite things about the same class for a whole phase — §10 documented C-level levers with a committed worked example, §16 declared the class not source-steerable — and nothing detected it, because the §16 verdict had been produced with an instrument §10 itself warns against. The first task of Phase 18 was simply to replay §10's documented lever under the right oracle: it closed 24 → 21 mismatches immediately (`Phase18.md:42-44`), a real win that had been sitting written down and unused. Phase 17's strategic conclusion ("the harness ceiling did NOT rise") had been drawn on top of it.
- **Not banked — greps:** `grep -n -i 'two sections contradict\|sections contradict' $F` → 0; `grep -n -i 'knowledge base.*contradict' $F` → 0; `grep -n -i 'replay.*documented lever' $F` → 0; `grep -n -i 'existing-knowledge-first' $F` → 0. `grep -n -i 'contradict' $F` → 11, all about *code* contradicting itself (a draft vs a header, a declaration vs a definition, a card vs the bytes), none about two knowledge-base entries disagreeing.
- **Proposed home:** DK (a kernel) for chapter 06 (the knowledge base) — the maintenance half of a compounding cookbook: entries are written by different sessions under different instruments, so a growing base acquires contradictions by construction, and each one is a lead.
- **Portable because:** any project whose knowledge base is written incrementally by agents will hold entries that disagree; the disagreement always encodes an instrument change or a missing lever, and it is the cheapest research a session can do.

### C6 — Scope a research phase by a PER-CLASS VERDICT, not by a percentage: the deliverable is a validated lever or an honest, falsifiable wall verdict for each class
- **Evidence:** `phase-ends/logs/Phase18.md:93-96` —
  > ## Milestone (knowledge-gated, NOT a fleet-% target)
  > Per-class byte-gated verdict (validated C idiom proven on a known-answer exemplar via
  > `p16_known_answer --gate`, OR honest "unsteerable" verdict naming the exact gcc pass)

  set at the gate as `phase-ends/logs/Phase18.md:18-19`: *"Knowledge-gated milestone (validated idiom OR honest verdict per class) + a bounded quirk-tail demonstration. The full tractable-247 harvest wave is **deferred to Phase 19**."*
- **What happened / what it cost:** Phase 17 was scoped as a percentage phase — five avenues, each a candidate match-% lever — and four of the five returned ~0 (`Phase17.md:47-50`: T2 = 0 functions, T4/T5 byte-neutral, T6 = 0 whole-binary), so a phase of real work read as a failure and ended in a NO-GO. Phase 18 was scoped knowledge-gated on the same wall and produced the transferable toolkit *and* the throughput: the wave close-rate went 33% → 56% → 90% match_one as the toolkit entered the prompt, and the session arc banked 55.58% → 56.64% (`Phase18.md:126-134`). Same wall, same models; the difference was what the phase was allowed to deliver.
- **Not banked — greps:** `grep -n -i 'knowledge-gated' $F` → 0; `grep -n -i 'milestone.*per-class' $F` → 0; `grep -n -i 'research phase.*milestone' $F` → 0; `grep -n -i 'not a fleet-% target\|not a percentage' $F` → 0. The governance chapter requires a milestone be observable and machine-checkable (`docs/how-to-ai-decomp/01-governance.md:50`, G3/P9 at `:27`) and G52 requires a wall verdict to name the pass (`decomp-architect/templates/registry-E.decomp.md:329`) — but nothing says a phase may be *scoped* on verdicts, which is what makes the honest negative a deliverable instead of a failure.
- **Proposed home:** DK (a kernel) or a G-rule for chapter 01 — a phase-scoping form, alongside the plan/milestone gates.
- **Portable because:** every matching decomp hits a stretch where the remaining work is compiler research; percentage milestones there either fail or divert the phase into easy wins, and a per-class verdict is both achievable and the thing that compounds (the toolkit that raises every later wave).

## ALREADY-BANKED (one line each)
- Parallel drafters declare a shared callee two ways; the whole standalone-match-vs-bank gap was compile conflicts with zero codegen mismatches — lives at `docs/how-to-ai-decomp/02-byte-gate.md:54-57` (and `docs/matching-cookbook.md:1377`).
- Gate one draft at a time when the failure class is declaration conflicts, so a clash cannot mask good drafts (`--chunk 1`) — `docs/how-to-ai-decomp/02-byte-gate.md:56`.
- A relocation-masked isolated per-function oracle cannot certify a whole-binary match; a permuter driven by it banks ~0 — `docs/matching-cookbook.md:15062` and `:4059`.
- The canonical-sig layer's projected "~2× lever" shrank to 7% once the sample that produced it was banked (re-size a lever after the measurement's own work lands) — `docs/matching-cookbook.md:1386`.
- The wave pipeline is draft → mandatory declaration-normalisation → byte-gate → propagate (a recovery pass becomes mandatory once the shared TU carries a canonical block) — `docs/matching-cookbook.md:1384-1385`.
- Re-run the oracle AFTER the canonical retype — normalisation can itself change codegen — `docs/matching-cookbook.md:1476-1481`.
- Fix arity/void callee conflicts with codegen-neutral call-site casts, not redeclaration — `docs/matching-cookbook.md:1474-1481`.
- Teaching the current toolkit (and each callee's canonical signature) in the per-target wave prompt lifted the close rate 33% → 56% → 90% on the same models — `docs/matching-cookbook.md:1467-1472`.
- `register __asm__` pins + a scheduling barrier crack the call-crossing register-ORDER class; the "unsteerable" verdict was a missing lever — `docs/matching-cookbook.md:1396-1420`, `decomp-architect/templates/registry-E.decomp.md:322` (G51).
- Array-decay (pass `buf`, not `&buf`/`buf.w`/`*(T*)buf`) forces rematerialization instead of a callee-saved hoist — `docs/matching-cookbook.md:1423-1425`.
- The permuter cannot help a pinned function (pycparser rejects `register __asm__`) — `docs/matching-cookbook.md:1370`.
- Census the residual/corpus shape with validated instruments before choosing a strategy, and validate the classifier against the arbiter on a known-true case (the wall taxonomy, and its byte-refuted "LOOSE_TYPING_WALL" class) — `decomp-architect/corpus/decomp-kernels.md:108` (DK-8), `decomp-architect/templates/registry-E.decomp.md:211`.
- Struct/type recovery is byte-neutral for matching (0 better / 10 same / 2 worse) but essential for hand-writing and comprehension — `decomp-architect/corpus/decomp-kernels.md:808-813`.
- A blanket canonical header imposed over a correct draft is destructive — canonicalise surgically, per callee — `docs/decision-log.md:1356-1364`, `docs/how-to-ai-decomp/10-integration-and-propagation.md:16`.
- Probe before costing: ground a lever's estimate on one instance before scaling or committing a long run (the 5-day unattended run that would have banked ~0) — `decomp-architect/templates/registry-E.decomp.md:160` (G23), `docs/how-to-ai-decomp/04-oracles-and-instruments.md:56` (R37).
- Order by leverage (reach × size), not by difficulty — `docs/how-to-ai-decomp/03-bootstrap-order.md:93`.
- The mismatch count does not predict which draft banks — `docs/matching-cookbook.md:35838`.
- Bulk-cache the decompiler's output with a headless batch pre-pass instead of driving the interactive server per function — `docs/matching-cookbook.md:1372`.
- Per-file `-O0` modules are a real class and need their own split file — `phase-ends/DIGEST.md:51`, `docs/cookbook-index.md:857` (§18).
- A verdict produced in an isolated environment describes the environment; gitignored inputs are missing there (the background-worktree isolation that had to be disabled before Phase 17 could start) — `decomp-architect/corpus/decomp-kernels.md:291-297` (DK-21).
- A harness/argument channel that silently drops what you passed it (the wave `args` channel that would not transit arrays, so targets had to be embedded) — `decomp-architect/corpus/decomp-kernels.md:263` (DK-19) and `:306`.
- The emulator is the runtime oracle, with multi-datapoint verification, for recovering a live struct's fields — `decomp-architect/templates/registry-E.decomp.md:20`, `phase-ends/DIGEST.md:166` (R10).
- Seed the knowledge base from sibling projects on the same compiler (the positive half of C2) — `decomp-architect/corpus/decomp-kernels.md:196`, `docs/how-to-ai-decomp/03-bootstrap-order.md:89`.
- A wall verdict names the pass and quotes the dump line — `decomp-architect/templates/registry-E.decomp.md:329` (G52), `docs/how-to-ai-decomp/07-compiler-source.md:88`.
- Sanity-check the OUTCOME metric (fleet %), never only the gate — `docs/matching-cookbook.md:1307`.
- Widening a discarding caller's `extern void` → `s32` is byte-neutral and dissolves the return-type conflict — `docs/matching-cookbook.md:2408`, `:615`.
