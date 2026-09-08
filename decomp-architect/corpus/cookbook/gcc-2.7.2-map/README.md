# The gcc-2.7.2 codegen map — pass → residual → C-lever catalogue

**What this is.** A catalogue of the pinned compiler's behaviour, organised by optimisation pass: for each residual
pattern a near-miss diff can show, the mechanism in the compiler's own source that produces it, and the C-level lever
that moves it — each lever **byte-proven** on a named function with the diff before and after. It was written in
Phase 23 by four frontier-class agents reading the gcc 2.7.2 passes directly, after six phases in which the same
residuals had been called "unsteerable"; it is the artifact that lets a mid-tier agent, or a local model, apply
compiler-internal levers without reading 80,000 lines of source. The index and triage table live in the cookbook
([`docs/matching-cookbook.md`](../matching-cookbook.md) §31); the method is chapter 07 of the how-to
([`docs/how-to-ai-decomp/07-compiler-source.md`](../how-to-ai-decomp/07-compiler-source.md)).

## The files

| File | Pass group (source files) | Catalogue | Size |
|---|---|---|---|
| [`sched.md`](sched.md) | scheduling: `sched.c` (sched1 pre-reload / sched2 post-reload) + `reorg.c` (delayed-branch) + the MIPS backend hooks (`config/mips/mips.c`, `mips.h`) | S1–S13 (LUID = source order, the birthing boost in both directions, the load-gap filler, the bb0 head-skip, the reused-temp fence …), D1–D5 (delay-slot content, eligibility, eager steal, thread copies, merged exits); the S11/RC-6 verdict downgrade | 266 lines |
| [`regalloc.md`](regalloc.md) | register allocation + reload: `local-alloc.c`, `global.c`, `reload.c`, `reload1.c` (with `flow.c`, `function.c`, `caller-save.c`) | §A the eight knobs everything reduces to; §B RC-1…RC-15 (spill-slot shape = declaration order, wrong value spilled, callee-saved order, coalescing, pin side-effects, pressure lock, remat-vs-spill, reload artifacts, the preference cascade, the 3-qty sort bug, the `$0`-add opaque copy …); §C the tells; §D the triage order; §E the experiment record; §F–§H the later extensions incl. the `reg_renumber`-swap oracle | 286 lines |
| [`loop.md`](loop.md) | the loop optimiser: `loop.c` (biv/giv detection, `combine_givs`, strength reduction, hoisting/preheader, biv elimination, reversal) | L1–L8 (IV count/anchor, index-biv elimination, loop reversal, hoisting and the inline limit, final-value compensation, giv-add order, invalid loops, increment position) | 369 lines |
| [`cse_expr.md`](cse_expr.md) | common-subexpression elimination + expression emission: `cse.c`, `expr.c`, `function.c` (with `calls.c`, `stmt.c`) | cross-call ADDRESS caching (hoist-vs-remat — the class that blocked the 400-instruction giants), cross-call VALUE CSE (the phantom callee-saved register), the `/s` (`MEM_IN_STRUCT_P`) aliasing model in all four arms and its store-side flush lever, the temp-slot and stack-layout rules | 389 lines |
| [`t7g-giant-harvest.md`](t7g-giant-harvest.md) | a Phase-24 session harvest (levers found while cracking the giants; a permuter tool fix) | **a log, not a primary reference**: where it disagrees with the three audited files above, those win | 351 lines |

## How to use it

1. Read the **tell** off the near-miss diff (`match_one` / `rtu_match` output, or the RTL dumps): a temporary in a
   spill slot = a reload artifact; "every small edit moves 20+ instructions" = a pressure lock → the permuter; a load
   stuck below a `x = 0` store while offset loads float = the `/s` flag; a phantom seventh callee-saved register held
   across the function = cross-call CSE; a prologue initialisation in the wrong order = the birthing boost. Each
   catalogue carries its full tells table.
2. Look up the class's lever in the catalogue, apply it to the C, gate. The condensed triage table:

| Pass group | STEERABLE (a byte-proven lever exists) | INTRINSIC → the permuter |
|---|---|---|
| scheduling | S1 source order; S2 birthing boost (create or kill a sink); S4/5/6 load-gap filler, memory-unit spacing, hazard front-move; S7 prologue saves; D1–D3 delay-slot content / eligibility / eager steal | S3 load/mul chain-priority sink; S11 the LUID⊗allocation knife-edge — **downgraded**: try the S12 reused-temp fence and S13 head-skip escape first |
| regalloc / reload | RC-1 spill-slot shape (declaration order); RC-2 wrong value spilled (allocno density); RC-3 callee-saved order; RC-4 coalescing un-tie; RC-5 pin side-effects; RC-7 remat-vs-spill; RC-8 reload artifacts; RC-9 cross-block copy | RC-6 pressure lock (its true form); the local-vs-global allocation tie |
| loop | L1 IV count/anchor; L2 index-biv elimination; L3 reversal; L4 hoisting/preheader; L7 invalid loop; L8 increment position | L5 final-value compensation; L6 giv-add order |
| cse / expr | cross-call address caching (nested-block pointer + a post-call `volatile` re-set); cross-call value CSE; the `/s` model + store-side flush; stack layout | the 1,000-instruction table flush (giants); `QImode` never gets `/s` |

3. **Before any register lever, read the allocation order** (`tools/alloc_table.py` over the pass dumps) — every
   `register … __asm__` pin the last functions of the project carried came off byte-identical once the source shape
   was right; pins are symptoms (R73). **Before any "wall" verdict, name the pass and quote the dump line** (R65), and
   write the producer census against a NAMED list (R69) — two written proofs of unmatchability were each one producer
   short.

## The byte-proof method

Every lever in these files was validated the same way: compile the exemplar with the pinned triple
(`gcc-2.7.2-psx cc1 -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker` → maspsx `--aspsx-version=2.56
--expand-div` → GNU `as`) and compare relocation-masked bytes to the original with [`tools/match_one.py`](../../tools/match_one.py)
(or, in the real translation unit, `rtu_match.py`); the experiment C files and RTL dumps are kept under `.run/gccmap/`
(scratch). The instruments that grew around the map: `tools/cc1_dumps_tu.sh` (per-pass RTL dumps from the *real*
translation unit — the standalone compile is not faithful on the executable's units; `-dL` for the loop pass),
`tools/alloc_table.py` (the global allocator's priorities and hard registers per pseudo), `tools/ghost_census.py`
(frame and spill-slot census from the dumps), and the one-second **reproducer battery**: five-line functions that
isolate one mechanism, compiled with dumps, before any probe of the 500-instruction function.

## Provenance — read this before following a line number

**Two source trees, gitignored under `tools/reference/` (SETUP §5.6):**

- **`gcc-2.7.2/`** — the vanilla GNU release, **the real source of the pinned `cc1`**: a subset of 18 `.c` files plus
  `config/mips/` (`sched.c`, `reorg.c`, `local-alloc.c`, `global.c`, `reload.c`, `reload1.c`, `loop.c`, `cse.c`,
  `expr.c`, `function.c`, `calls.c`, `stmt.c`, `combine.c`, `toplev.c`, `flow.c`, `expmed.c`, `caller-save.c`,
  `integrate.c`, `optabs.c`, `varasm.c`, `recog.c`, the headers), staged from `ftp.gnu.org/old-gnu/gcc/gcc-2.7.2.tar.gz`
  (sha256 `7cd8bce5c3aeec59a72ecc2d3d5123864a817b14cdbd0680b1a969c3bccc5da5`; GPL-2.0). Re-fetch the tarball and copy the
  files you need; the whole tree is not required.
- **`gcc-papermario/`** — `pmret/gcc-papermario` at `a6afc2afbcaf6682930141d526afdc95801fc2fd`, source files at the
  repository root. **It is gcc 2.8.1, not 2.7.2** — a fact established in Phase 23 after the map had been written
  against it. The difference is *behavioural* (2.8.1 disables biv-elimination paths that are live in the real 2.7.2
  `cc1`) and the line-number drift is large and non-uniform: `combine_regs` +103, `allocate_reload_reg` +377,
  `choose_reload_regs` +611 — enough to land inside a different function.

**The Phase-29 audit (2026-07-28).** All 184 citations and claims of the three primary files were re-derived against
the vanilla 2.7.2 source by five parallel agents; every refuted claim then went to an independent agent whose job was
to refute the refutation, defaulting to upholding the map. Result: **119 confirmed · 40 line-drift (mechanism intact,
number wrong) · 21 raised as refuted, of which 14 were overturned and 7 stand · 4 unverifiable.** The model is
overwhelmingly sound — do not delete levers — but a line number may belong to either tree. Each file carries its own
audit banner with the specifics (`cse_expr.md` had the most errors; one `sched.md` claim about the birthing boost and
register-asm pins was byte-refuted and corrected).

**Every citation is tagged with its tree.** `tools/gccmap_cites.py` derives, for every `file.c:NNN` cite in these
files, which tree the number belongs to, and writes the tag after the cite:

| Tag | Meaning | Count |
|---|---|---|
| `[2.7.2]` | the cited construct sits at that line in the vanilla 2.7.2 subset — verified against the tree | 79 |
| `[2.8.1 pm]` | the cited construct sits at that line in gcc-papermario; the 2.7.2 line differs (re-derive with `grep -n` before citing) | 55 |
| `[repo]` | a project file (`src/shared/engine_core.h`), not gcc | 1 |

The derivation is from the trees, never typed: quoted source snippets and C identifiers in the citing sentence are
searched near the cited line in each tree (function extents for cites inside long bodies; the nearer tree wins, an
equal distance means the line is equally valid in 2.7.2); the author's own cues (`papermario …`, `→2.7.2 :NNN`)
break ties and fail loudly when they contradict the evidence; the 20 cites the evidence cannot settle (18 with no usable evidence near them, 2 where the two trees tie) carry a human
verdict with its reason in [`cite_overrides.tsv`](cite_overrides.tsv). Six known-true cases recorded in the map's own
text are the tool's controls (`--controls`, 6/6); `--verify` re-derives every tag; `--check` (textual, in
`make tools-health` and CI) refuses an untagged cite or a stale override. 135 cites across the five files.

## Related

- Cookbook §31 (the index and triage), §17 (the register-pin toolkit), §30 (the `/s` flag), §34 (the 3-qty sort bug),
  §501 (the twelve dump-read laws and the two overturned proofs).
- [`docs/accelerators.md`](../accelerators.md) A4 — "read the compiler's source once, into a codegen map" (found Phase 23,
  available from Phase 6).
- [`docs/how-to-ai-decomp/07-compiler-source.md`](../how-to-ai-decomp/07-compiler-source.md) — the method for the next project.
