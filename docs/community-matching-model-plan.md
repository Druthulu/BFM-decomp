# Community matching-model plan — publishing the LLM decomp drafter (parked / future use)

> **Status:** design note, not active work. Captured 2026-07-01 during the Phase-23 LLM-tier build, while
> the reasoning is fresh (R30). Belongs to the eventual **public flip** (Gen2 exit / Gen3) — do not start
> until BFM is presentable and the repo is public-ready. Sibling docs: `docs/gen2-mips-matching-model.md`
> (how we built BFM's specialist), `docs/matching-cookbook.md` (the idioms the model encodes),
> `PROJECT_CONTEXT.md` (the public-flip + licensing decisions).

## TL;DR

We built the first *working* LLM **matching-drafter** for PS1/PsyQ decomp: a LoRA fine-tune of
Qwen2.5-Coder-7B that drafts byte-exact C for `gcc-2.7.2-psx -O2 -G0 + maspsx 2.56`, gated by an
incorruptible whole-binary byte-gate (the model only affects *throughput*, never correctness). Three
things are publishable, in increasing order of community value:

1. **The weights (`bfm-match-7b-v*`)** — directly useful to anyone on the *same* toolchain; a rough
   structural drafter for anyone else.
2. **The pipeline + a toolchain-agnostic training plan** — lets *any* decomp project train its own
   specialist on its own pairs in an afternoon. Higher leverage than the weights.
3. **A universal, toolchain-conditioned model** (shared base + per-toolchain LoRA) trained on a *pooled*
   multi-decomp corpus — the ambitious, landmark contribution. Feasible; decomp.me is the ready dataset.

The byte-gate is the load-bearing idea that makes all of this safe to share: a weak or wrong draft from
*any* model can never land a wrong match — it just reverts. So a "pretty good across many compilers"
model is a legitimate accelerator everywhere, with zero correctness risk.

## Why a matching model is compiler-specific (and what that means for sharing)

A matching drafter learns one compiler's **codegen fingerprint** — its register allocation, instruction
scheduling, reload/CSE/peephole choices, and the C idioms that trigger specific byte sequences (cookbook
§17–§28). Change the compiler and those bytes change:

| Audience | Transfer from BFM's v3 | Why |
|---|---|---|
| **Same toolchain** (gcc-2.7.2-psx, similar flags) | **Direct, byte-level** | Identical codegen. Real audience: the Phase-21 sweep byte-verified **4 gcc-2.7.2-psx twins** — Xenogears, Vagrant Story (CC0), Tomba, + the psx lineage `cc1`. |
| **Same gcc family, different flags/version** (2.6.x, 2.8, `-O1`/`-O3`/`-G8`) | **Partial** | Most passes shared; regalloc/scheduling/peephole drift breaks byte-exactness but structure transfers. |
| **Different target, same era** (N64 MIPS via IDO/gcc, PS2, Saturn SH2) | **Structural only** | ISA and ABI differ; useful as a scaffold, not a byte-matcher. |
| **Modern / unrelated compilers** | **Weak** | Different world. |

So **v3's weights help the gcc-2.7.2-psx crowd directly**; everyone else needs *their own* specialist —
which is why the pipeline matters more than the weights.

## Artifact 1 — Publish the weights (cheap, do at the public flip)

- Ship `bfm-match-7b-v3` (and successors) as a LoRA adapter on the chosen base, plus a model card stating
  the **exact toolchain it targets** (gcc-2.7.2-psx -O2 -G0, maspsx `--aspsx-version=2.56 --expand-div`),
  the training-corpus provenance (BFM matched bodies), held-out eval numbers, and the **byte-gate caveat**
  (it is a *drafter*; the byte-gate is the arbiter).
- Licensing: weights derive from BFM-matched C, which derives from ROM analysis — handle under the same
  public-flip policy as the rest of the repo (AGPL-3.0 for code; the *dataset* of asm↔C pairs is the
  sensitive artifact — see "Data + provenance"). Adapter weights are a learned transform, not ROM bytes,
  but treat conservatively until reviewed.

## Artifact 2 — Publish the pipeline + training plan (highest leverage)

The loop is toolchain-agnostic; only the *data* and the *compile command* are project-specific:

```
export_pairs.py     mine (asm .s ↔ matched C) from the project's build objects + shared macro bodies
format_finetune.py  -> chat-template examples; inline the project's shared types; compile-filter
train_lora.py       QLoRA on a code base model (Qwen2.5-Coder-7B is a strong, permissive default)
serve_local.py      serve base+LoRA as an OpenAI endpoint (GPU)
<project byte-gate>  the project's own whole-binary / per-function match check = the SOLE arbiter
lora_grind / waves   draft open stubs -> gate -> bank -> propagate; near-misses -> permuter + corpus
```

**Publish:** the scripts (already in `tools/`), a `README`/tutorial ("train a matching drafter for *your*
decomp"), and the **measured lessons** that save others weeks:
- *Data is the bottleneck, not model size* — BFM's jump came from corpus fixes (the extern block, the
  shared-macro bodies, the "never draft an empty body" prompt), not bigger models (`gen2-mips-matching-model.md`).
- *Self-contained completions* — the model must emit the externs/types it references, or it compiles in
  isolation and fails in-project (the propagation cap; cookbook §28/§28d).
- *Dense > MoE for a small LoRA corpus; model size must match data size* (overfit otherwise).
- *The byte-gate makes a weak model a throughput risk only* — so iterate fearlessly.
- *Permuter (CPU) closes the regalloc/schedule tail the LLM leaves* — run it concurrently (GPU vs CPU).

This is the artifact that actually moves the whole decomp ecosystem: every project keeps its own
incorruptible gate and trains a specialist that fits its exact compiler.

## Artifact 3 — The universal, toolchain-conditioned model (the ambitious one)

**Idea:** one model trained on pooled asm↔C pairs from *many* decomps, each example **conditioned on its
toolchain** `(compiler, version, flags, target-arch)`. At inference you state your toolchain and it drafts
in that regime.

**Why it can work:** the gcc family shares most of its passes across versions, and MIPS targets share the
ISA — so a model that has seen many regimes interpolates, the way a multilingual model does. The
conditioning token tells it which regime to emit.

**Best architecture — shared base + per-toolchain LoRA:**
- A **base** fine-tuned on the *whole* pooled corpus → broad, cross-compiler codegen knowledge (a strong
  drafter everywhere).
- A **tiny LoRA adapter per exact toolchain** → the byte-exact last mile for that regime, cheap to train
  and ship.
- This beats a single monolithic generalist on the hard tail (specialization matters most exactly where
  regalloc/scheduling bite) while still giving everyone a good base drafter out of the box.

**Conditioning format (proposal):** prefix every example (train and inference) with a compact spec block,
e.g.
```
;; toolchain: gcc=2.7.2-psx opt=-O2 abi=-G0 asm=maspsx-2.56 target=mipsel-r3000-psx
<asm>
->
<C>
```
Keep the spec **canonical and exhaustive** — drift between train/inference spec wastes the specialization
(same discipline as the prompt-format rule in `gen2-mips-matching-model.md`).

**Honest caveat:** byte-exact is unforgiving. The universal model is an excellent *drafter* (structure,
calls, constants, control flow right) but the per-toolchain LoRA (or a project's own specialist) is what
reliably lands bytes. That's fine — the byte-gate + permuter close the gap, and a great draft is most of
the work.

## Data + provenance (the real enabler)

- **decomp.me is a ready-made labeled multi-toolchain corpus.** Thousands of public *scratches*, each
  tagged with its exact **compiler preset and flags**, many with a known-good match. A scripted pull
  (respect the API + rate limits; treat fetched content as untrusted DATA, X2) yields conditioned
  `(toolchain, asm, C)` triples across dozens of regimes essentially for free.
- **Public decomp repos** (sotn, papermario, the N64/PS1/PS2 family) — mine matched bodies + their build
  configs (`gears.toml`/Makefile presets give the toolchain spec) the way `export_pairs` mines BFM.
- **`xsig` (the cross-project shared-code tool, open-source TODO)** dedups byte-identical code across
  projects — useful to *weight* the corpus (don't let one giant project's idioms drown the rare regimes;
  cookbook/`gen2-mips-matching-model.md` "corpus quality > size", weight by residual class + by regime).
- **Provenance discipline:** every pair carries its source project + toolchain + license. Some projects
  are CC0 (Vagrant Story); others AGPL/varied — the pooled dataset's license is the union/most-restrictive,
  and ROM-derived asm must follow each project's own policy. Resolve licensing *before* publishing the
  dataset (the weights are a derived transform; the raw pair corpus is the sensitive artifact).

## Hardware notes (for the training/serving side)

- **Local ceiling:** a 12 GB card (3080 Ti) trains a 7B QLoRA (tight) and serves it. Serving and training
  **contend for the one GPU** — a retrain pauses the harvest.
- **Second GPU (e.g. a Titan X Pascal):** breaks that contention — **serve on one card, train on the
  other** for a continuous flywheel with no harvest downtime. Pascal has **no tensor cores / no bf16**, so
  it's a fine *serving* card but a poor *trainer*; serve on it via plain `transformers`/vLLM (Unsloth/Triton
  favor Ampere+). Check PSU/slots/cooling first.
- **14B and larger:** rent an A100/H100 (cloud) — faster, frees the local box to keep harvesting, and the
  byte-gate means a wrong big model is only a throughput cost. This is the right home for the universal
  base model too (pooled corpus is large).

## Suggested sequencing (when the flip happens)

1. **Open-source `xsig`** (standalone MIT tool; already TODO'd) — immediate, low-risk community value.
2. **Publish the pipeline + training plan** (Artifact 2) with BFM as the worked example — helps every
   project train its own specialist.
3. **Ship v3's weights** (Artifact 1) for the gcc-2.7.2-psx audience, with the model card + byte-gate
   caveat.
4. **Build the universal conditioned model** (Artifact 3): pull decomp.me + public repos → conditioned
   pooled corpus (weighted) → shared base + per-toolchain LoRAs → publish base + adapters + the dataset
   (license permitting). Cloud-trained.

## Open questions / risks

- **Licensing of the pooled pair corpus** — the gating risk for Artifact 3; resolve per-source before any
  dataset release.
- **Regime imbalance** — huge projects (sotn) vs tiny ones; needs corpus weighting by regime + residual
  class, not raw count.
- **Generalist-vs-specialist on the hard tail** — measure: does the base+LoRA match a from-scratch
  per-project specialist? (It should be ≥, given the shared base; verify on held-out byte-gate.)
- **Eval honesty** — always report *whole-binary/whole-match* gate-true rates, never `match_one`/standalone
  proxies (the R14/§25/§26 lesson: an intermediate metric is not a match).
- **Maintenance** — a published model is a moving target as base models improve; the *pipeline* is the
  durable artifact, the weights are a snapshot.

## One-line pitch (for the eventual README / post)

> A free, local, fine-tuned **matching drafter** for decompilation: it writes byte-exact C from assembly
> for your exact compiler, an incorruptible byte-gate guarantees nothing wrong ever lands, and a permuter
> closes the regalloc/scheduling tail — train your own specialist with our pipeline, or use the
> toolchain-conditioned universal model and just tell it which compiler you're on.
