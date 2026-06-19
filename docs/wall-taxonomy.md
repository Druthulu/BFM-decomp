# Wall Taxonomy — the 957 unmatched shared residuals in `ov_SC01_077` (Phase 17 / T1)

> **What:** a full-census classification of every remaining `INCLUDE_ASM` stub in the canonical
> harvest source `ov_SC01_077` by the *blocker class* it hits in the real drafting pipeline —
> so Phase 17 can size each avenue's ceiling and **sequence the levers (biggest first)**.
> **How:** `tools/wall_taxonomy.py` runs `m2c --valid-syntax` → `match_one` (standalone, relocation-masked)
> → for the body-byte-correct subset, `sig_unify` + a full-overlay-TU `cc1`, and labels each stub by the
> first wall it hits (cookbook §14b/§14c/§14e/§15). Deterministic; reproduce with:
>
> ```
> python3 tools/wall_taxonomy.py --jobs 16     # ~22 s; writes .run/wall_taxonomy.json + this table
> ```
>
> **Validated against the bytes (R14):** the **SIG_FIXABLE_KR** bucket was confirmed on the real
> whole-binary byte-gate — the 4 functions the classifier flagged in a 40-stub probe were **exactly** the
> 4 (of 40) that `harvest_verify` verified byte-identical after `sig_unify`; all other buckets correctly
> did **not** byte-match through signature work alone. The classifier's "fixable-now" set = the real
> gate-passing set. (PERMUTER_CLASS is an evidenced *candidate* bucket — see its caveat below — pending T6.)

Baseline at census: fleet 136/136 byte-identical from clean; 54.48% byte-identical-from-source;
`ov_SC01_077` = 957 unmatched shared stubs (each propagates ×134 overlays via `dedup_propagate`).

## The census (957 stubs, ranked by count)

| count | %  | Σnins | bucket | primary avenue |
|------:|---:|------:|--------|----------------|
| 368 | 38% | 25345 | `STRUCTURAL_MISS` | **T4** (rich context) / **T5** (struct) — m2c gets the structure wrong |
| 146 | 15% |  4941 | `PERMUTER_CLASS` | **T6** candidate — near-miss, same instruction count |
|  99 | 10% |  3282 | `LOOSE_TYPING_WALL` | **WALL** — a matched caller passes a contradictory type (§14e) |
|  85 |  8% |  3495 | `MCOMPILE_fnptr-call` | **T4** — type fn-pointer tables in the m2c context (§15 S2) |
|  59 |  6% | 12597 | `M2C_DECOMP_FAIL` | **T4** — feed jump tables to m2c (58/59 are jump-table, §8) \| hard |
|  48 |  5% |  1419 | `SIG_FIXABLE_KR` | **T3** — `sig_unify` resolves it (**gate-proven**) |
|  45 |  4% |  4928 | `MCOMPILE_stack-var` | **T5/T4** — m2c stack/struct recovery |
|  32 |  3% |  4138 | `MCOMPILE_arg-arity` | **T4/T5** — m2c arg-count recovery |
|  21 |  2% |   838 | `MCOMPILE_undeclared-other` | **T4** — undeclared callee/symbol into context |
|  16 |  1% |  2437 | `NONFAITHFUL_DEFER` | **DEFER** — GTE/handwritten/special; not m2c-matchable |
|  14 |  1% |  1382 | `MCOMPILE_m2c-incomplete-arg` | **T4/T5** — m2c incomplete arg recovery |
|  14 |  1% |  2277 | `MCOMPILE_bad-deref` | **T5/T4** — m2c deref'd a non-pointer (`?`/`M2C_UNK`) |
|   8 |  1% |   946 | `MCOMPILE_other` | residual (8 fns; mixed m2c-output errors) |
|   1 |  0% |   204 | `MCOMPILE_bad-switch` | T4/T5 — m2c switch reconstruction |
|   1 |  0% |   160 | `LEAF_READY` | T6/harvest — directly matchable, trivial |
| **957** | | **70871** | | (99.2% carry an actionable label; `DATA_CONFLICT` = **0**) |

Example targets (biggest-first = highest leverage; full per-fn data in `.run/wall_taxonomy.json`):
- `STRUCTURAL_MISS`: `func_80176218`(327), `func_8016A290`(284), `func_8015126C`(254)
- `M2C_DECOMP_FAIL` (jtbl): `func_8017C974`(947), `func_80178D40`(890), `func_8018103C`(579)
- `MCOMPILE_fnptr-call`: `func_8015EA3C`(204), `func_8015D738`(201), `func_8015F448`(188)
- `MCOMPILE_bad-deref`: `func_80144B9C`(**770** — the Phase-15 prime target, all-134), `func_8012D714`(284)
- `PERMUTER_CLASS`: `func_80132288`(97), `func_8013DBE4`(97), `func_80164930`(81)
- `SIG_FIXABLE_KR`: `func_80128AF4`(72), `func_80144458`(64), `func_8017E51C`(58)
- `LOOSE_TYPING_WALL`: `func_80141CA4`(476), `func_80140F00`(128), `func_80155150`(105)

## Aggregated by primary lever (this is the sequencing driver)

| count | %  | Σnins | lever |
|------:|---:|------:|-------|
| **639** | **67%** | 39204 | **T4** (rich context: struct + fn-ptr-table + jump-table + plain), with **T5** the struct input to ~474 of them |
| 146 | 15% |  4941 | **T6** (decomp-permuter) — 146 candidates (**101 are ≤4-mismatch near-certain**; 19 likely 5–8; 26 speculative 9–16) |
|  99 | 10% |  3282 | **WALL** (loose typing) — documented dead-end; T5's *correct* struct types may dissolve a subset (§14e) |
|  48 |  5% |  1419 | **T3** (`sig_unify`) — gate-proven immediate wins |
|  16 |  1% |  2437 | **DEFER** (non-faithful: GTE/handwritten/special) |
|   9 |  1% |  1106 | residual / trivial |
|   **0** | **0%** | 0 | **T2** (DATA-symbol byte-array header) — **no addressable functions** |

**Giants (106 functions > 150 ins, the ~3.4 MB highest-leverage targets):** 30 are `M2C_DECOMP_FAIL`
(jump-table → **T4 jtbl context**), 28 `STRUCTURAL_MISS` (**T4/T5**), 12 `arg-arity`, 12 `stack-var`,
6 `NONFAITHFUL_DEFER`, 5 `bad-deref`, 4 `fnptr-call`, rest scattered. **The giants are unlocked by T4
(jump-table + struct context), not by T3 or T6.**

## What this means for sequencing (T1's purpose)

1. **SKIP T2 (the DATA-symbol byte-array header).** The census finds **0** data-symbol-conflict functions.
   The cookbook flagged this as "the next yield-limiter" (§14c-c) when Phase 16 jumped past it — but
   `sig_unify` (which canonicalizes data externs) plus the prior harvest already absorbed it. Building a
   universal `extern u8 D_X[]` header would address nothing. **Document the finding; do not build T2.**

2. **Bank T3's 48 gate-proven `SIG_FIXABLE_KR` wins first** — deterministic, byte-gate-verified, cheap; a
   clean opening (~5% of residuals, ×134 each). Extend `sig_unify` coverage / wire it into a propagation pass.

3. **Lead with T4 (the rich-context generator) as the primary lever** — it addresses **67%** of residuals
   and **all 30 jump-table giants**. Build it with three context sources, in value order:
   - **(a) jump-table data** → unlocks `M2C_DECOMP_FAIL` (59, incl. the 947/890/579-ins giants). m2c
     literally errors "jump table is not provided"; the §8 rodata/jtbl machinery already exists.
   - **(b) struct types** (T5's output) → the 474 `STRUCTURAL_MISS`/`bad-deref`/`stack-var`/`arg-arity` set,
     incl. `func_80144B9C` (770). **T5 (struct inference + emulator field-typing) is T4's enabling input —
     run them together**, not as separate sequential avenues.
   - **(c) fn-pointer-table types** → the 85 `MCOMPILE_fnptr-call` ("called object is not a function").

4. **T6 (permuter) is the byte-closer, validated early.** 146 candidates (101 near-certain ≤4-mismatch).
   Critically, T4 will **convert `STRUCTURAL_MISS` into `PERMUTER_CLASS`** (better m2c structure → only
   regalloc/schedule left), *growing* T6's addressable set. Confirm the bucket is real on the known-answer
   ladder (`p16_known_answer --gate`) before projecting its yield (the only unverified bucket here).

5. **The wall is ~99 `LOOSE_TYPING_WALL` (+ the arity subset).** Phase 16's loose-typing finding, now
   quantified at ~10–13%. No clean deterministic fix; the only lever is T5's *correct* struct types possibly
   making some call sites type-consistent (§14e hypothesis — test, don't assume). Plus 16 `NONFAITHFUL_DEFER`.

**Net:** the deterministic ceiling (T3 `sig_unify`, no permuter) is ~5%, matching Phase 16. The *eureka*
lever is **T4+T5 (context+struct)** at 67% reach, with **T6** closing the regalloc residual — not T2 (empty)
and not signature work alone. This reorders the plan's avenues to **T3 (free wins) → T4+T5 (build together)
→ T6 (validate + close) ; T2 skipped**.

## Reproduce / maintain

- `python3 tools/wall_taxonomy.py --jobs 16` — full census → `.run/wall_taxonomy.json` + the table above.
- `--limit N` probes the classifier on the first N stubs; `--no-step3` skips the TU-context conflict sub-split.
- The tool is read-only on tracked files (step 3 uses throwaway `src/ov_SC01_077/_wt_*.c` copies, auto-removed).
- Re-run after any harvest wave to watch buckets drain and re-rank the remaining avenues.
