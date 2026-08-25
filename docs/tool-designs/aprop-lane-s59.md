# A-prop lane S59 — the measured decomposition, the fixes, and the honest ceiling

**Mission:** the free A-prop lane (`family_cousins --aprop-cards` → `aprop_autodraft` →
`reloc_identity` → stage → `sweep_parallel`) staged ~117 drafts a pass and banked **zero across
three consecutive passes**. Get the population banking, or name the ceiling with the residual
sized. Everything below is measured; every rate carries its denominator (R41/R32).

**Headline: 64+ functions banked this session, all byte-proven (whole-binary SHA green), zero
model tokens** — from a lane that had banked 0 in its last three passes. Sweep-by-sweep and
class-by-class accounting below; the final sweep's count is in the session log
(`.run/s59_aprop2/`).

## 1. Baseline — what the 0-bank passes actually were

The 21:04 pass (the last pre-fix run): **182 drafted / 117 staged (reloc `AGREE`) / 0 banked.**
Re-aggregating that pass's own per-binary ledgers (`.run/auto/bulk/*.backlog.jsonl`, rows
timestamped 21:04–21:29) over the 117 staged drafts:

| class | n/117 | meaning |
|---|---|---|
| `near` with real closeness (1–80, median 2) | **82** | the compiled body genuinely differs from the target |
| `failed` (won't compile standalone) | **19** | match_one's post-gate label; the real TU failure often differs |
| `near` closeness **0** | **16** | match_one says MATCH, the whole-binary gate rejected — TU integration |
| not gated at all | **0** | every staged draft reached the gate |

Three structural facts fall out:

* **Nothing was invisible.** The "`drafts: 0`" probe result was the *triage harness* racing
  itself: `.run/s59_aprop/triage.sh` keys its scratch dir by **function name only**
  (`d=".run/s59_aprop/$fn"`), and two concurrent triage runs shared
  `.run/s59_aprop/func_80162CCC` — run 1's third spec `rm -rf`'d it between run 2's `cp` and
  gate_stage's glob (run 1's own log shows the tell: `draft missing` for the spec that emptied
  it). The lane's sweep accounting balances exactly: banked+notbanked = drafts staged, and
  `ov_MAIN_012.failed.txt` from the same pass lists `func_80162CCC` — gated, `near 0`.
* **The lane was re-burning 82 hopeless builds every 45 minutes.** The staging filter took
  `status == AGREE` alone. reloc `AGREE` says the *symbols* agree; `shape == MATCH` says the
  *instructions* do. 82 of the 117 were `AGREE`/shape-`DIFF` — already refuted by match_one, a
  whole-binary build each, forever.
* **The 0 banks were several separate defects, not one** — broken down and fixed below.

## 2. The defect classes, each byte-diagnosed before its fix

### 2a. near-0 / TU-integration: the `(void)`-decl + empty-call wall → K&R definitions

Reproduced on `ov_MAIN_012/func_80162CCC` in the real TU via `rtu_match`:

1. As staged (ANSI def `void f(u8 *a0)`): `conflicting types` — the home TU declares
   `extern void func_80162CCC(void);` (twice), and engine_core.h carries **42 more** inside
   `DEFINE_` macros the TU instantiates — every banked shared caller calls it K&R-style with no
   args.
2. With the gate's arity pre-pass applied (54 decls → no-proto): the decls no longer conflict,
   but the TU's own **empty call sites** now die against the ANSI definition's prototype:
   `too few arguments` (t.c:6670, 6746). This is why the pre-pass fired in every 0-bank pass and
   still banked nothing.
3. With the definition converted to **K&R** (`void func_80162CCC(a0) u8 *a0; {…}`, §99) + the
   same pre-pass: **`MATCH (23 ins)`**, then BANKED byte-identical at the whole-binary gate.

**Fix:** `aprop_autodraft.kr_definition` — definitions are K&R when all params are
promotion-safe (narrow by-value params keep ANSI, §43/§102). Cookbook §272.

### 2b. The closeness-2 cluster (35 of the 82): one ordinal-pairing defect

Every closeness-2 residual was the same two instructions crosswise —
`*(p + 3) = 2` drafted for a target of `*(p + 2) = 3`. Two stacked causes in
`family_remap._ordinal_edits` (§T87): the per-*spelling* scan exposed only the offset token to
the pairing, and text order ≠ emission order for `*(p + OFF) = VAL`. **No static pairing is
right for every shape** → `_ordinal_candidates` emits every order-preserving assignment and
`aprop_autodraft` adjudicates them with **match_one at draft time**. This also un-skipped the
~50 members the single guess had refused as `asm-ambiguous` forever. **29 of the 35 banked in
sweep 1.** Cookbook §271.

### 2c. The declaration layer: five distinct lookup bugs, all measured

* **Wrong scope:** the destination text was the whole binary concatenated; C scope is the TU.
  → home TU only, with `DEFINE_x()` instantiations *expanded* (`dest_scope`) — the decls that
  matter live inside engine-core macros.
* **Wrong direction:** the destination spelling was adopted even where the seed body cannot
  compile against it (void-return read as a value: 42 drafts; prototype vs K&R-sloppy empty
  calls: 15 drafts) → body-compatibility guards; the seed's spelling is what preserves bytes.
* **Wrong name:** for a RENAMED symbol the destination was searched for the *seed's* name, which
  it cannot contain — the destination preference silently never applied to renamed data symbols
  (`D_801B9DF8` shipped as the seed's `short` against the TU's file-scope `s32`).
* **Wrong scope again:** the flat regex adopted *block-scope* externs from inside banked bodies
  as "the destination spelling" → `dest_scope` is brace-masked to file scope; and a
  body-embedded block extern that diverges from file scope is rewritten to the destination
  spelling when every use is address-only (type is codegen-irrelevant for `&sym`).
* **Fake rescue:** "the destination already declares it" was satisfied by the TU's own
  `INCLUDE_ASM("…", sym);` stub line and by bare *call* statements — so drafts taking a
  function's address shipped with no extern at all (`undeclared`, func_80180F1C). The rescue
  now demands a real declaration/definition; plus a synthesized no-proto
  `extern void f();` tier for functions whose call value the body never reads, and a
  borrow-from-sibling-TU tier ("which TU may conflict" ≠ "where a guess may come from").

### 2d. Staging/repair plumbing

* Stage only `status ∈ {AGREE, UNRESOLVED} ∧ shape == MATCH`, keyed **(binary, fn)** — function
  names collide across binaries (three overlays each carry a `func_8013BCDC`).
* `reloc_identity --fix` had the same fn-keyed rowmap bug (2 of 4 repairs hit the wrong binary's
  draft: "no textual occurrence"). Keyed correctly: **4/4 repaired to AGREE/MATCH**. Wired into
  the lane (repair + re-check + stage in the same pass).
* `tools/rtu_second_chance.py` (new): a standalone COMPILE-FAIL is the wrong oracle for a
  TU-destined draft — re-judged in the real TU via rtu_match, **7 of 27 were byte-MATCHes**,
  previously dropped unjudged. Wired into the lane. Cookbook §273.
* `tools/fix_tu_ret_decls.py` (new): the RETURN-TYPE half of the stale-decl wall. The TU
  forward-declares `extern void f(void);` for a definition that returns `s32`; the arity
  pre-pass relaxes the parens, never the return. Retyping the TU's own decls to
  `extern s32 f();` (byte-neutral — declared-void callers ignore `$v0`; fix_header_decl's
  argument, TU-scoped/T1) with journaled edits kept only where the gate pays: **14/30 banked.**
  Wired into the lane's post-sweep step.

## 3. The fixed pipeline, measured end-to-end

Population at run time: **325 families / 973 open members** (the pool refills as waves bank).

| stage | n | of |
|---|---|---|
| drafted | **151** | 973 members |
| — refused, named (§5) | 822 | 973 |
| reloc verdicts | AGREE 99 · COMPILE-FAIL 27 · MISMATCH 4 · MISMATCH? 6 · UNRESOLVED 15 | 151 |
| sweep 1 (AGREE ∧ MATCH) | **38 banked** / 80 staged | — |
| sweep 2 (rtu-rescue + UNRESOLVED/MATCH + repairs + K&R'd leftovers) | **12 banked** / 33 staged | — |
| TU-retype pass (fresh near-0 rejects) | **14 banked** / 30 tried | — |
| sweep 3 (decl-layer refixes of the 12 stranded void-def members) | see `.run/s59_aprop2/sweep3.log` | 9 staged |
| **session total** | **64+ banked, byte-proven, zero model tokens** | |

Sweep-1 attribution against the baseline classes: 29 ordinal-cluster, 4 near-0/K&R, 5 new.
Sweep-2 attribution: 6 rtu-second-chance (of 7), 6 UNRESOLVED/MATCH (of 15).

## 4. The near-miss taxonomy (mission item 4), honestly

The 19 AGREE/shape-DIFF drafts of the fixed batch, classified from the bytes
(match_one + `residual_class`; `.run/s59_aprop2/near_class.json`):

* **11 × IMM tier-2** (closeness 1–2, `IMM-VALUE`/`IMM-OFFSET`): the member differs in a literal
  no candidate pairing can produce — the constant is *folded* (a `lui` const-hi, a field offset
  with no C token). Real edits; permuter/tier-2 fuel — not plumbing.
* **8 × structurally different** (closeness 7–39, `UNKNOWN`): extra branch arms, different
  prologues, one two-instruction stub seed against a member with a real body. **Wrong family
  members** — §168 law 1 (*a cousin is a seeded crack, never a remap*); the Phase-26 correction
  stands: h_seq predicts, the gate refuses. The cards should carry this verdict so no lane
  re-drafts them mechanically.
* `ov_SC02_000/func_801803D0` (the probe's closeness-22 case) drafts shape-MATCH under the fixed
  tool — its "genuinely different body" was the *declaration layer* distorting codegen, not a
  wrong family.

## 5. The honest ceiling

**"117/117" was never the real question** — the 117 was a *stage count*, and 82 of it was
provably unbankable as staged (shape-DIFF). The honest population is the **973 open members** a
pass sees. After all S59 fixes, the evidence supports:

* **~120 gate-worthy drafts per pass** (80 + 33 + 9 this session), of which **64+ banked** —
  and the classes that banked are now *automatic in the lane*, so the next refill of the pool
  (new exemplars from waves) converts at the new rate instead of 0%.
* The refusals, named and sized (fixed run's own ledger):
  * **169 STRUCT** members — register/opcode drift; needs a real crack. Out of mechanical-remap
    scope *by design* (§168 law 1 / the Phase-26 h_seq correction).
  * **121 "no seed decl"** — the referenced symbol has no extern spelling anywhere in the seed
    OR the destination binary (the borrow tier recovered only 4). These need type *inference*
    from usage, not lookup — a different tool.
  * **~150 pre-check refusals** (arity/undefined-data conflicts, historically negative-controlled
    as real build failures) + **44 seed-body-not-extractable** + **~73 IMM-unresolved**
    (multi-target / non-imm-op / not-in-C — includes the 16 branch-offset "op=0x4" members that
    are STRUCT in disguise) + **6 verbatim-asm seeds** (§265 — deliberately refused: propagating
    a transcribed-instructions body would count as "matched" while decompiling nothing).
* Residuals still open inside the gate-worthy slice: 12 MISMATCH?/UNRESOLVED-not-banked +
  4 repaired-but-refused + ~8 near-0s the retype pass could not cure (freshly-spliced `(void)`
  preambles suspected — the same mechanism as the SC07_010 incident below).

**Ceiling verdict:** with the S59 fixes the mechanically-reachable slice of the A-prop
population is roughly **⅛ of the open members per pass (~120 of 973), banking at ~50–60%**, and
that yield now repeats automatically as waves refill the pool. The remaining ~850 are not
plumbing: they are real cracks (STRUCT + wrong-family), real type-inference (no-decl), or real
edits (IMM tier-2) — each named above with its size. A claim of 117/117 (or 973/973) from this
lane alone would be false; the defensible statement is *the lane no longer wastes a single build
on a draft its own oracles refute, and everything its four verdict layers agree on, banks.*

## 6. Incidental finds (pre-existing, surfaced by the S59 scoped R22)

The engine_core.h no-proto keeps are a T2 write, so the 141 binaries whose TUs instantiate the
23 edited DEFINE macros were SHA-checked (45 by sweep-1's own gates, 96 explicitly): **94/96
green; 2 pre-existing REDs found** (provenance: byte-identical to commits from hours before this
session; my diff names only `func_80162CCC`):

* `ov_SC07_010` — the 14:57 maintenance commit banked `func_8017F2BC`'s `(s16*)` definition into
  a TU carrying an earlier draft-preamble `extern void func_8017F2BC(void);` — the committed
  state cannot compile (cc1 trio-repro: composite type keeps the prototype through a no-proto
  redeclaration), i.e. **the final tree state was never built** — a §61 undo-scope/splice-order
  hazard in the gate internals, witnessed from the outside. Fixed (one no-proto edit,
  SHA-verified green, committed).
* `ov_SC07_002` — `jtbl_rodata_pads: consumed 1 rodata .align but 2 pad specs — table-count
  drift vs the carve` in `ov_SC07_002_jr_8017C8D0.c`. A jtbl carve/config drift, unrelated to
  this lane; left RED and **named here rather than papered over** — needs the jtbl tooling
  owner.

The "how did that pass report green" question for commit:2694 is open and belongs to gate_stage's
splice/undo ordering; the arity journals of that pass contain no entry for func_8017F2BC, so the
`(void)` decl was reintroduced by a later splice or restore *after* the last green build.

## 7. What is now automatic in the lane (`.run/maintenance.sh`)

drafts (K&R + candidate-adjudicated IMM + 6-tier decls) → reloc → `--fix` repair + re-check →
stage on `{AGREE,UNRESOLVED} ∧ shape==MATCH` keyed (binary,fn) → rtu second chance for
standalone COMPILE-FAILs → recover_rejects → sweep → **fix_tu_ret_decls on fresh near-0
rejects** → commit. Every drop is counted and named at each stage (R32).

Cookbook: §270 (the four-verdict law), §271 (ordinal candidates), §272 (K&R the definition),
§273 (the wrong-oracle law). Session scratch: `.run/s59_aprop2/`.
