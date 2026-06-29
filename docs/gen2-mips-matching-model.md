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
