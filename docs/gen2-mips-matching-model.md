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

Two forward levers besides fine-tuning:
- **Permuter-seed role:** the model's structurally-correct near-misses are good *permuter seeds* — let
  the 32-thread permuter brute-force the regalloc/schedule precision the model can't. Plays to its
  strength; cheap to test.
- **Cloud cheap tier (Haiku/GLM-5.2)** stays the working low-cost drafter today (the local-free tier
  needs the fine-tune or the seed role to be useful).

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
