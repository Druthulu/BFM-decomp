# Gen2 idea — a BFM/PSX-gcc-2.7.2 *matching* specialist model

**Status:** design / not started. Captured 2026-06-29. The high-ceiling idea from the cheap-tier thread.

## The gap, and why it's ours to fill

There is **no matching-decompilation LLM** — for MIPS or anything else. The one RE-specific model
family, **LLM4Decompile**, targets **x86** and optimizes for *readable, recompilable, semantically-
equivalent* C (passes the function's tests), **not byte-identical** machine code under a *specific*
ancient compiler. That's the wrong objective for us. The reason no matching model exists is **data**:
the only place (target-asm ↔ byte-exact gcc-2.7.2 C) pairs exist is inside decomp projects' git
histories. The community therefore runs *general* strong coders + deterministic tools (m2c, permuter,
the byte-gate). The real domain "specialist" today isn't an LLM — it's **m2c** (rule-based MIPS→C).

**But we have the data off-the-shelf models lack:** ~1,300 **gate-verified** (asm ↔ byte-matching
gcc-2.7.2 C) pairs in this repo's banked history (plain `src/` defs; more recoverable from deduped
`DEFINE_func_*` macros) — real, clean, byte-exact, specific to our exact
toolchain and this game's idioms. That is precisely the corpus LLM4Decompile had to *synthesize* for
x86, except ours is correct and on-target. So we can *build* the matching specialist that doesn't
exist — narrow domain + high-quality verified data is the ideal setup for a small local model to
beat a frontier generalist **on this one task** (it won't generalize, and doesn't need to).

This is the *right-data* version of the "Opus-distilled Qwen" models: instead of generic reasoning
traces, bake our cookbook's gcc-2.7.2 quirks (regalloc order §17, %lo array-of-struct fold §18,
schedule/loop forms) into the **weights**, not just the prompt.

## Recipe

1. **Corpus** — `tools/export_pairs.py` mines every banked function into `{fn, region, asm, c}`
   JSONL: C from `src/`, the target `.s` recovered from git history (the exact splat format
   `api_draft.py` feeds at inference → train/inference format match). Split ~90/10 train/test by fn.
2. **Base model** — start from a strong local coder: **Qwen2.5-Coder-32B** or **Qwen3.6-35B-A3B**
   (MoE, cheap to serve). Code-pretrained base + our SFT on top.
3. **Fine-tune** — **LoRA SFT** (not full FT): prompt = the drafter prompt (target asm + ghidra-C +
   toolkit, same as `api_draft`/`worker_wave`), completion = the banked C. Rank 16–64, a few epochs.
   Trainable on a rented A100/H100 in hours, or slowly/local for a small rank. Keep the prompt format
   byte-identical to inference.
4. **Eval — free and rigorous** — run the adapter as an `api_draft` arm over a *held-out* frozen
   target set and score with `tools/ab_score.py` (the byte-gate). Compare to the stock base model and
   to Haiku. The gate is the arbiter; no eval guesswork. Iterate rank/epochs/data on that number.
5. **Deploy** — the adapter becomes a cheap-tier `local` arm (LM Studio / llama.cpp serve base+LoRA);
   `api_draft.py` already targets it. Slots straight into the cost-escalation ladder as Tier-0/1.

## Why measure before training

A stock local model test (in progress) tells us the floor. The fine-tune is worth the effort **iff**
the specialist's *gate-true* match rate clears the stock model by enough to matter — which the free
gate eval settles directly. Don't train blind; train against a target number.

### Stock-model floor — measured 2026-06-29 (the result that motivates this)

**Qwen3.6-35B-A3B as a stock drafter fails on the byte-match step**, and this is precisely the gap a
fine-tune fills. On the 20 reach1 functions via `tools/api_draft.py`:
- **Blind harness:** 0/13 (run killed early); mostly compile-fails + near-misses.
- **Fair harness** (inline common.h + live cookbook + corpus examples): *fixed* compilation, but the
  model **stuck at fixed near-misses** — identical closeness across all 4 diff-feedback iterations
  (e.g. func_8013373C = near-4 in blind, curated, AND full cookbook). It cannot act on the
  instruction-level diff to refine.
- **Full vs curated cookbook:** full (whole 192k-char file, ~58k-tok prompt) was **worse and 2.3×
  slower** than the curated matching-only subset — attention dilution, gate-confirmed. More context
  is not the lever.

Diagnosis: the model gets the *structure* right (correct control flow, field semantics) but misses
gcc-2.7.2 **precision** — element-vs-byte offset scaling, `lh`/`lhu` signedness, an extra `move`,
frame size — and can't self-correct from the diff. That precision is exactly what `src/`-pair LoRA
bakes into weights. **The stock floor is ~0 reliable banks; that is the number to beat.** (Contrast:
Haiku, a frontier *small* model, reliably matched the ≤52-ins bulk — so the gap is capability, not task.)

### Pilot RESULT — measured 2026-06-29 (NEGATIVE on meaningful functions)

7B QLoRA (Qwen2.5-Coder-7B, 3 epochs) on 638 compile-filtered pairs, evaluated on 75 held-out banked
fns (`tools/eval_lora.py`, gate-true):
- **≤5-ins trivial: 39/41 MATCH (95%)** — memorized the leaf-function pattern.
- **≥6 ins: 0/34. Meaningful (>15 ins): 0/24** — same as stock-local.
- Near-misses are **FAR, not close**: `near N ≈ nins` (all instructions mismatch → structurally-wrong
  output), only 1/33 non-trivial within 5 of a match. So it's NOT "one epoch away."

Root cause = the corpus: the compile-filter (needed because bare `src/` defs don't compile standalone)
**threw out the 536 harder functions** (globals/structs), starving the model of non-trivial signal;
638 examples with 297 trivial → a 7B overfit the easy pattern. **The fix that filter requires is the
same one the corpus needs: self-contained completions WITH externs (corpus-v2), which recovers the hard
functions AND makes them trainable.** Until that's done, the fine-tune verdict is unproven, not refuted —
but the far near-misses suggest data quality/coverage (and likely a bigger base) are the real levers,
not epochs. Cheap-cloud (Haiku/GLM) remains the working tier meanwhile.

### Corpus-v2 RESULT — measured 2026-06-29 (POSITIVE: data was the bottleneck)

Fix: `export_pairs` now captures the `extern <type> D_xxx;` block the src declares immediately above
each def (correct byte-verified types) → self-contained completions, standalone-compile 52%→92%,
training set 638→1111 with non-trivial examples 257→813. Retrained the SAME 7B; held-out gate-true eval:

| band | v1 | v2 |
|---|---|---|
| 6–15 ins | 0% | **85% (23/27)** |
| 16–40 ins | 0% | 13% (3/22) |
| >40 ins | 0% | 0% (10 compile-fail = need struct types) |
| non-trivial (>5) | 0/34 | **26/73** |
| meaningful (>15) | 0/24 | 3/46 |

**Conclusion: corpus quality was the bottleneck, not the model or the task.** A free local 7B now
byte-matches trivial + small-medium (≤15 ins) functions at 85–93% — a real Tier-0 for the bulk,
rivaling Haiku on that band at $0. Limits: ≥16 ins falls off (7B capacity), giants compile-fail (the
extern-capture covers globals but not struct *types* → corpus-v3 = also emit the struct defs each fn
needs). Decision gate (staggered plan) = GO: scale to a cloud-trained dense 14–32B to extend the band
upward. Caveat: this eval is held-out BANKED (objdump format); production on OPEN stubs still needs the
.s-format alignment (spimdisasm). Tooling: format_finetune→train_lora→eval_lora; serve via LM Studio
(GPU) — Unsloth's bundled llama.cpp is CPU-only.

Two forward levers besides fine-tuning:
- **Permuter-seed role:** the model's structurally-correct near-misses are good *permuter seeds* — let
  the 32-thread permuter brute-force the regalloc/schedule precision the model can't. Plays to its
  strength; cheap to test.
- **Cloud cheap tier (Haiku/GLM-5.2)** stays the working low-cost drafter today (the local-free tier
  needs the fine-tune or the seed role to be useful).

### T7 RESULT — the broad-rotation gate debugged 2026-06-30 (0/222 was TWO harness bugs, not the model)

The 500-fn calibration run (`lora_grind`) banked **0/222** across ov_SC01_000→ov_SC02_005 while the
model banked ~18% on ov_SC01_077. Root-caused (R14 — by reading the code + the run's own backlog,
which resolved a direct contradiction between two scout agents) to **two independent bugs in
`lora_grind`'s use of `gate_stage.run_gate`**, NOT model quality:
- **Bug A — good_sha format:** `lora_grind.good_sha()` returned the whole sha1sum line `"<sha>  <name>"`;
  `harvest_verify` compares it against a bare `sha1()` → never equal → **0 banks for EVERY binary
  including 077**. So the "077 0/12" in that run was a *bug artifact*, not an exhausted tail (a claim I
  nearly enshrined before reading the `.sha` format — the R14 payoff).
- **Bug B — path mis-resolution:** the gate call passed only `binary`+`good_sha`, leaving
  `src`/`asm`/`out` at the hardcoded ov_SC01_077 defaults → non-077 drafts dropped at the 077 stub-filter
  → 0 banks, **silently**, and the backlog near-miss classes were contaminated by the mis-resolved asm
  (so that run's "199 compile-fail" breakdown was untrustworthy for non-077 fns).

Fix (`tools/gate_stage.py`): `run_gate` now resolves `src`/`asm`/`out`/`good_sha` from `binary` when
unset (binary-agnostic — the Phase-9 "no silent default an overlay inherits" discipline; good_sha
normalized to the bare hash) + a **loud negative-control guard** (warns when 0 drafts are stubs in the
binary's own sources — the silent-0 can never recur). `lora_grind.good_sha` also fixed at source.
Byte-neutral (check-all 136/136); zero `lora_grind` logic change beyond the one-line good_sha fix.

**The first trustworthy on-OPEN-stubs signal (ov_SC01_000 spot-run, 15 smallest ≤15-ins stubs):**
- **Gate-banked 7/15 (47%) byte-identical** (check-all 136/136, auto-committed). Proxy `match_one`:
  6 leaf-exact + 1 recovered via the TU-plumbing pipeline. Backlog (now correctly classified): 6
  near-misses — **four at closeness=1** (prime grinder/permuter fuel) — + 2 standalone-compile-fails
  (struct types → corpus-v3). The 0/222 was 100% the bugs; the model is a strong Tier-0 on the small
  open-stub tail **fleet-wide**, the production number the corpus-v2 caveat (above) flagged as unmeasured.

**ROI finding (the sizing input):** of the 7 banks, **6 are reach-1 (overlay-UNIQUE, ×1)** and 1 is
reach-2. The broad rotation's small non-077 stubs are predominantly overlay-unique → **high bank-RATE,
low fleet-% ROI** (each ×1; the fleet % barely moved, +8 fns). The fleet-% levers are therefore
**reach≥2 targeting** (the ×134 multiplier — a `lora_grind`/`wave_targets` `--min-reach` filter, T9) and
the canonical-site (077) harvest, plus **corpus-v3** for the struct compile-fails (T8) — NOT a blind
broad rotation. A broad ≤15-ins run remains worthwhile for per-overlay completeness, corpus growth
(retrain fuel), and seeding the permuter grinder with the close=1 near-misses.

## Open questions / notes

- **Corpus quality > size.** ~1,700 verified pairs is plenty for LoRA; dedup near-identical reach
  copies so the model doesn't overfit one idiom. Consider weighting by residual class (cookbook
  taxonomy) so under-represented quirks (schedule, IV-combine) aren't drowned by plumbing.
- **Format discipline:** train on the literal `.s` + the C as `api_draft` will present them. Any drift
  between train and inference prompt format wastes the specialization.
- **It won't generalize** beyond BFM/gcc-2.7.2 — that's the point. It's a drafter for *this* project.
- **Repo placement:** build it IN this repo (the git history + asm/src are the essential context the
  exporter reads). Tooling + this doc on `main`; the dataset JSONL and any GGUF/LoRA weights go in a
  **gitignored** dir (`datasets/`, `models/`) per R20 (large binaries stay out of git). No branch or
  worktree needed — the work is purely additive.

## Artifacts
- `tools/export_pairs.py` — corpus miner (this doc's step 1)
- `datasets/match_pairs/` — exported JSONL (gitignored)
- eval: reuse `tools/api_draft.py` + `tools/ab_score.py`
