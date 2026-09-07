# The matching-drafter pipeline — a fine-tuned local model that writes byte-exact C, and what it measured

> **Status (P33 E6, 2026-09-07).** The write-up of BFM-decomp's *matching drafter*: a LoRA fine-tune of a small local
> code model that drafts C for one exact toolchain (gcc-2.7.2-psx `-O2 -G0`, maspsx 2.56), gated by the project's
> whole-binary byte gate so that a wrong draft can never land. Built and measured in Phases 22–25 (2026-06-29 → 07-08),
> frozen at its third version, and off the endgame's critical path from 2026-07-08. The pipeline scripts are in
> `tools/` and are published with the repository; **the paired dataset (`datasets/match_pairs/`, assembly ↔ matched C,
> ROM-derived) and the adapter weights (`models/`, a transform of that dataset) are NOT published** — both directories
> are gitignored, and their release is a separate licensing decision for Gen3. The design notes this distils are
> [`docs/gen2-mips-matching-model.md`](gen2-mips-matching-model.md) (how it was built, every measurement) and
> [`docs/community-matching-model-plan.md`](community-matching-model-plan.md) (what a community release would look
> like); the drafting loops it plugs into are cookbook §12 (the parallel-draft + byte-gate harvest) and §500 (the
> one-agent-per-function pass).

## 1. The idea, and why it is safe

There is no matching-decompilation model: the one reverse-engineering model family targets x86 and optimises for
readable, semantically equivalent C, not byte-identical output under a specific 1990s compiler. The reason is data —
the only place (target assembly ↔ byte-exact C) pairs exist is inside decompilation projects' histories. BFM had
~1,300 such pairs by Phase 22 (later ~2,900 with the shared macro bodies), each gate-verified, each specific to the
exact toolchain. That is the corpus a specialist needs and a generalist lacks.

What makes a weak or wrong model *safe* to use at all is the project's byte gate: the model only affects
**throughput**, never correctness — a draft is substituted into the real translation unit, the binary is rebuilt, and
it is kept only if the SHA1 still matches ([the matching workflow](wiki/The-matching-workflow.md)). So the model can be
small, local, free and frequently wrong, and still bank thousands of functions.

## 2. The pipeline (toolchain-agnostic; only the data and the compile command are project-specific)

```
tools/export_pairs.py     mine (asm .s ↔ matched C) pairs from the project's banked functions — plain `src/` definitions
                          AND the shared `DEFINE_func_*` macro bodies — with the `extern` block each definition carries
tools/format_finetune.py  chat-template examples; the project's shared types inlined; a compile filter (self-contained?)
tools/train_lora.py       QLoRA on a code base model (Qwen2.5-Coder-7B: dense, permissive, fits a 12 GB card)
tools/eval_lora.py        held-out, GATE-TRUE evaluation: the adapter drafts unseen banked functions; the gate decides
tools/serve_local.py      serve base + adapter as an OpenAI-style endpoint (GPU; Unsloth/transformers)
tools/api_draft.py        the drafter client (the LEAN prompt; the same prompt for every tier — local, cheap-cloud, frontier)
tools/lora_grind.py       draft open stubs → gate → bank → propagate (interleaved; the first production loop)
tools/bulk_harvest.py     the phase-separated loop: (A) bulk-draft on the GPU, (B) parallel per-binary byte gates on the
                          CPU, (C) dedupe once + one commit
tools/ab_score.py, tools/workflows/ab_match.js   controlled A/B of two drafter arms on a fixed target set, gate-scored
tools/grinder.py          the permuter over the near-misses the model leaves (CPU, concurrent with the GPU)
```

Two disciplines that the measurements below justify: **the prompt format at training time is byte-identical to the
prompt at inference** (any drift wastes the specialisation), and **every evaluation number is gate-true** — a
whole-binary match, never a standalone `match_one` proxy (which over-counts about 2×).

## 3. What it measured, in order

| Step (date) | Corpus | Result (gate-true unless stated) | What it taught |
|---|---|---|---|
| Stock local model floor (06-29) | — (Qwen3.6-35B-A3B, prompt only) | ~0 reliable banks: structure right, gcc-2.7.2 precision wrong (offset scaling, `lh`/`lhu`, an extra `move`, the frame size); a full-cookbook prompt was worse and 2.3× slower than a curated subset | more context is not the lever; precision must be in the weights |
| v1: 7B QLoRA, 3 epochs (06-29) | 638 compile-filtered pairs (297 trivial) | ≤5 ins **39/41**; ≥6 ins **0/34**; near-misses FAR (`near N ≈ nins`) | the compile filter had thrown out the 536 hard functions; a 7B memorised the leaf pattern |
| corpus-v2: the `extern` block captured (06-29) | 1,111 pairs, non-trivial 257 → 813; standalone compile 52% → 92% | 6–15 ins **85% (23/27)**; 16–40 ins 13% (3/22); >40 ins 0/10 (compile-fail: struct types) | **data quality was the bottleneck, not the model** |
| The 0/222 broad run (06-30) | v2 | banked **0/222** across 25 overlays | two harness bugs (a SHA string with its filename; hardcoded per-binary paths) — not the model; fixed with a loud negative-control guard (R40) |
| First trustworthy open-stub signal (06-30) | v2 | **7/15 (47%)** on the smallest open stubs of one overlay; 4 near-misses at closeness 1 | most small open stubs are overlay-unique (×1) — a bank-*rate* lever, not a fleet-% lever |
| reach ≥ 2 targeting (06-30) | v2 | **0/15** on shared functions; the model drafted `return 1` and `sw` setters as *empty* bodies | 96.6% of the corpus was overlay-unique inline definitions — the shared setters were never seen |
| corpus-v3: + 1,623 shared macro bodies; struct types inlined; the "never an empty body" prompt clause (06-30) | 2,891 pairs (2,534 train / 291 test), 97.8% compile | held-out **23/40 (57.5%)**; production: **~352 banks** + 45 new shared groups, fleet 63.67% → 63.82% (+502 functions), 136/136 clean, $0 | the previously impossible setter/leaf class banked; the flywheel (banks → corpus → retrain) closed |
| `bulk_harvest` phase separation (07-01) | v3 | **52/80 = 65%** on fresh ≤15-ins stubs across 50 overlays; gate 0.4 s/fn amortised (≈75× the interleaved loop); drafting 13.5 s/fn = 97% of wall clock | the bottleneck moved from gating to inference; batched serving became justified |
| GLM5.2 (cloud reasoning model) A/B on the hard band 16–22 ins (07-01) | v3 vs GLM | `match_one` 1/18 vs **10/18**; banks 1/18 vs **3/18** (+1 by reconciliation); ~$1.25 total | a better drafter's bodies were right and *still* did not bank: the **def-side declaration wall** caps every drafter (7 of 10 stranded); the reasoning model given the wall directly banked 1/7 |
| v4: retrain on the post-giant corpus (07-08) | 3,574 pairs (+994 medium, +597 large) | easy tie (5/5 both); medium **v3 better** (v4 farther, 4 compile-fails); hard 0/10 both | **discard v4** — the 7B is capacity-bound; over-length examples had trained on cut-off completions |
| Cheap-tier A/B (Phase 22) | Haiku drafters under an Opus orchestrator | same match rate as Opus on ≤ ~50-ins functions at ≈4.8× lower cost per match | the model ladder: Haiku → Sonnet → Opus → frontier only for a new wall class |

**The strategic conclusion** (decision log, "2026-07-08 · Phase 25 — the local-7B tier is capacity-bound and off the
endgame critical path"): the engine that finished the project was *frontier crack → deterministic propagation
(families, dedup) → byte gate*, with the permuter softening the tail; the local model stayed a frozen $0 mop-up for
the ≤ ~15-instruction setter/leaf tail. A real capability jump needs a bigger base (14B four-bit on the card, 32B in
the cloud) or the frontier tier — not more data on a 7B.

## 4. The lessons, stated portably

- **Data is the bottleneck, not model size.** Every jump came from the corpus: the `extern` block (v2), the shared
  macro bodies and inlined struct types (v3), one prompt clause. Retraining on more but harder data regressed (v4).
- **Completions must be self-contained** — the model emits the `extern`s and types it references, or it compiles in
  isolation and fails in the real translation unit (the integration cap every drafter shares — see
  [chapter 10](how-to-ai-decomp/10-integration-and-propagation.md)).
- **Corpus quality > size; weight by regime and residual class**, not by count — one overlay-unique pattern drowned
  the shared setters until the shared bodies were mined explicitly.
- **Dense beats MoE for a small LoRA corpus; the model size must match the data size** (a 7B on 638 examples
  memorised; on 2,891 it generalised; on 3,574 harder ones it saturated).
- **Drop over-length examples rather than train on truncated ones; train at the context you infer at** (v4's medium
  regression traced to completions cut at `maxlen`).
- **The byte gate turns model quality into a throughput question** — iterate fearlessly, and never let an
  intermediate metric stand in for the gate (R14, R63).
- **Exonerate the harness before the model** (R40): the 0/222 that nearly enshrined "the tail is exhausted" was two
  bugs in the gate's caller.
- **Route by measured difficulty; run the permuter concurrently** (GPU drafts, CPU permutes) on the close near-misses
  the model leaves; target shared functions deliberately (×reach), and expect the declaration wall to cap any drafter.

## 5. Hardware, as used

A single 12 GB consumer card (RTX 3080 Ti) trained the 7B QLoRA (≈2 h for 3 epochs at batch 1 / maxlen 2048, VRAM-tight)
and served it (Unsloth/transformers; the prebuilt llama.cpp CUDA wheels crashed on a CPU without AVX-512). Serving and
training contend for the one GPU — a retrain pauses the harvest; a second card breaks that. 14B and above: rent an
A100/H100 — the byte gate means a wrong big model is only a throughput cost.

## 6. Train one for your own project

1. Have the byte gate and at least a few hundred gate-verified pairs (the pipeline mines them from your banked sources).
2. `export_pairs` with the declarations each body needs; `format_finetune` with your shared types inlined; keep the
   compile filter and *count what it drops* — the dropped set is where your hard functions are.
3. Fix the prompt format once; use it for training, evaluation and production alike.
4. QLoRA a dense 7B; evaluate **gate-true on held-out functions** before any production run; compare against the
   stock model and against a cheap cloud tier on the same targets (`ab_score`).
5. Run it as the lowest rung of a model ladder, phase-separated (bulk draft, parallel gate, one commit), on the
   population it wins (small, overlay-unique, leaf/setter); hand its close near-misses to the permuter; retrain only
   when the corpus changes in *kind*, not size.

## 7. What is and is not published

Published with the repository: every script above, this write-up, the design notes. **Not published:** the pair
dataset (assembly from the game ↔ matched C — ROM-derived; `datasets/`, gitignored) and the adapter weights (`models/`,
gitignored; a learned transform of that dataset, treated conservatively). A community release — weights with a model
card naming the exact toolchain, a toolchain-agnostic training tutorial, and the ambitious *toolchain-conditioned*
universal model trained on pooled multi-project pairs (decomp.me is the ready labelled corpus) — is designed in
[`docs/community-matching-model-plan.md`](community-matching-model-plan.md) and parked for Gen3, gated on resolving
the licensing of pooled ROM-derived pairs per source project.
