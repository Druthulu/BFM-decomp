# func_8016CBC0 (209 ins, ×134 family core) — Fable5 gdb/dump-oracle pass

**Result:** the "coalescing knife-edge" verdict is **REFUTED as named**. gcc-2.7.2 has NO global
coalescing (map key K8), so nothing here is a coalescing decision. The residual is two SEPARATE,
precisely-located compiler decisions — one **CRACKED**, one **crackable-but-RC-6-coupled**:

| root | what | mechanism (exact gcc file:line) | verdict |
|------|------|---------------------------------|---------|
| **A** | mat/i `$s4/$s5` swap | `global.c:594 allocno_compare` density gap at a `floor_log2` boundary | **CRACKED** — pure density dial, byte-zero |
| **B** | vertex-block workhorse (w0→`$a0` vs target `$v1`) | `local-alloc.c:472` single-death gate + destructive tie (`combine_regs`) | **workhorse CRACKED** (scoped-merge) but exposes an RC-6 `$a1` contention |

**Ledger reconciliation (task asked):** BOTH recorded numbers were stale — they were measured
against the now-renamed subdir `ov_SC01_077_after`. Against the CURRENT subdir
`ov_SC01_077_jr_8016AB6C`, the seed `m7`/opus.c scores **match_one positional 151 (length 208), real
aligned-diff 111**. Neither "close=148" (backlog) nor "153 masked" (.opus.md) reproduces; the backlog's
prose ("166/209 aligned, edit-dist ~44") was the honest figure. The `match_one` positional count is
**cascade-inflated whenever the length is wrong** — always cross-check with the aligned differ
(`.run/giants/opus_8016CBC0/adiff.py <t.o> <target.s>`).

## Deliverable drafts (both PIN-FREE, ×134-safe — generic-constraint zero-byte asm only)

- **`func_8016CBC0.fable.c`** (variant **e1**) — **match_one 46/209, correct length**. Root A cracked;
  ONE clean residual (root B, w0-load register). Best next-tier seed by the gate metric.
- **`func_8016CBC0.workhorse.c`** (variant **e4**) — match_one 105/209 (length 210, +1) but **real
  aligned-diff 81** (best) and it **CRACKS the root-B workhorse** (w0 chain lands in `$v1`). Its 105 is
  cascade-inflated by the +1 length. Recommended base for a permuter finish — see root B below.

## The byte-verified lever ladder (match_one positional / real aligned-diff, current subdir)

| variant | change | pos | real | note |
|---------|--------|-----|------|------|
| e0 (=m7 seed) | prior pin-free seed | 151 | 111 | length 208 |
| **e1** | + `__asm__("":: "r"(mat))` density anchor | **46** | 92 | **root A cracked + length→209** |
| e2 | e1 + merge w0/av (vertex-block scope) | 52 | 110 | merge → whole chain to `$a0` (wrong dir) |
| e3 | e1 + per-coord block scope, no merge | 96 | 182 | fragments — scope-without-merge is wrong |
| **e4** | e1 + per-coord **scoped MERGE** | 105 | **81** | **workhorse w0→`$v1` (cracked)**; +1 ins, pv→`$a3` |
| e9 | e4 but coord-z left plain (hybrid) | 96 | 120 | mixing scoped/plain fragments worse |

## ROOT A — CRACKED. The `$s4/$s5` swap is a density gap, NOT coalescing.

From the `m7` `.greg`: callee-saved pseudos `72..78` = col,uv,cnt,vb,**mat(76),i(77)**,ret. Seed
disposition `76 in 21 ($s5)  77 in 20 ($s4)` — i wins `$s4`; target wants mat=`$s4`, i=`$s5`.

`.lreg`: **mat(76) = 7 refs / 163 live; i(77) = 9 refs / 163 live** (identical live_length). Plug into
`allocno_compare` (`tools/reference/gcc-2.7.2/global.c:594`)
`pri = floor_log2(n_refs)*n_refs / live_length * 10000`:
- mat: `floor_log2(7)*7 = 2*7 = 14` → **858**
- i:   `floor_log2(9)*9 = 3*9 = 27` → **1656**

i allocates first (higher density) → takes the lower reg `$s4`. The gap is NOT a tie and NOT
coalescing — it is the **`floor_log2` step**: 7→8 refs crosses `2^3=8`, doubling the multiplier from
×2 to ×3. To flip, mat needs `floor_log2*refs ≥ 27`; mat=8 gives 24 (still loses!), mat=9 gives 27 = a
TIE, which mat then wins by the creation-order tie-break (`global.c:616 return v1-v2`, and 76<77).

**The dial:** `__asm__("" :: "r"(mat));` placed inside the outer-loop `if (e->active)` body. That block
is at **loop_depth 2** (function=1, outer do-while=2; inner do-while=3), and `flow.c:2067`
`reg_n_refs[regno] += loop_depth` → mat's ref count rises **7→9**. Zero bytes (input-only asm), ×134-
safe. Result: `76 in 20 ($s4)  77 in 21 ($s5)` — exact. Side benefit: it also repaired the 208→209
length (the swap had been perturbing the tail schedule).

**This retires the "coalescing knife-edge" name for root A**: it is the same `allocno_compare` density
dial as cookbook §47/§48-A, just gated by the `floor_log2` boundary rather than an int-truncation tie.

## ROOT B — the workhorse. Crackable, but the crack is RC-6-coupled.

The target keeps `w0 → (short)w0 → sum → av` all in ONE workhorse `$v1` for every coordinate (a
per-coord in-place accumulator). The seed/e1 keeps `av` in `$v1` (correct) but the raw `w0` load in
`$a0` (wrong). **Why:** `w0` is ONE C variable reused across the 3 unrolled coordinates → `.lreg`
"Register 109 … dies in 3 places" → `REG_N_DEATHS = 3 ≠ 1` fails the local-alloc gate
(`local-alloc.c:472`) → `w0` becomes a **GLOBAL allocno**. gcc-2.7.2 global-alloc has **no coalescing
(K8)**, so `w0` cannot tie into the `$v1` av-chain; it gets its own reg. Confirmed from the conflict
matrix: `109` conflicts with hard regs `2 (v0)` and `3 (v1)` (scratch pressure across its multi-coord
range) → first-fit `$a0`.

**The crack (workhorse.c / e4):** give each coordinate its own block-scoped, MERGED accumulator —
`{ s32 w0 = *(u16*)(pv+K); s32 w3; store w0; w3=…; store w3; w0 = (u32)((short)w0+(short)w3)>>1;
store w0; store w0; }`. Now each coord's accumulator is **single-death → a LOCAL qty**, and the store-
before-sign-extend order makes `w0` die into its own in-place update → the local-alloc **destructive
tie fires** → the whole chain sits in one workhorse reg = **`$v1`, matching the target** (verified: e4
loads are `lhu v1,0(a1)`). This is **§48-A3 (block-scoped per-arm temps) + §45-Lever-A (merged
accumulator) COMBINED on loop-unrolled coordinates** — a new composite.

**Why e4 is not yet a match — the RC-6 coupling:** the per-coord scoped-merge, applied to the LAST
(coord z, highest-pressure — it also carries the 6 colour stores + the `uvm<<16` bgez test), makes
coord-z's accumulator a high-priority local that grabs **`$a1`** (its `.greg` pri = `4*18/18 = 40000`),
**evicting `pv`** (pseudo 101, pri `5*42/63 = 33333`) to `$a3`. So all 12 vertex loads read `(a3)`
instead of the target's `(a1)`, plus one delay-slot fill flips (+1 ins). Every attempt to relieve it
moved 20+ instructions discontinuously (e2/e3/e9 above; a `pv` density anchor needs +9 refs to out-
rank the coord-z accumulator — 3 depth-3 anchors, itself perturbing). This is textbook **RC-6 / §31
S11 coupling at `global.c` `find_reg` first-fit** — NOT a coalescing decision. It is the genuine wall
for the single-C-lever tier; a **decomp-permuter seeded from workhorse.c** (localized `$a1` contention,
workhorse already correct) is the right next move, OR a gdb patch of `find_reg`'s grant for the pv vs
coord-z-accumulator allocnos to confirm the minimal steer.

## Cookbook-worthy findings (the highest-value output — "Fable5 DISCOVERS, cheap-Opus APPLIES")

1. **DENSITY DIAL ACROSS A `floor_log2` BOUNDARY (new, byte-proven, root A).** When two equal-
   live_length call-crossing allocnos tie-break wrong, don't reach for pins — compute
   `floor_log2(refs)*refs` for each. If the loser is one `floor_log2` step below (e.g. 7 refs vs 9:
   `2*7=14` vs `3*9=27`), you cannot win by matching refs alone (8 refs = `3*8=24` STILL loses); you
   must **reach the next integer of `floor_log2*refs` and then win the creation-order tie**. The dial
   is an **input-only `__asm__("":: "r"(v))` placed at the loop depth that supplies the needed
   `reg_n_refs += loop_depth` increment** (`flow.c:2067`): depth-2 gives +2 per anchor, depth-3 gives
   +3. Zero bytes, ×134-safe. This generalises §47's ±1 live-length slider to the ref-count axis and
   subsumes the "coalescing knife-edge" mislabel whenever the residual is a callee-saved swap.

2. **SCOPED-MERGE = §48-A3 ⊕ §45-Lever-A, for LOOP-UNROLLED coordinates (new composite).** A workhorse
   register the target holds across an in-place `load→store→transform` chain, but which your draft
   splits because the driving variable is reused across N unrolled iterations (→ multi-death → GLOBAL
   → no tie): **wrap each iteration in its own `{ }` with a fresh merged accumulator** (`s32 acc =
   load; store acc; acc = f(acc,…); store acc;`). Single-death per iteration → LOCAL qty → the store-
   before-transform order fires the destructive tie → the whole chain collapses into the one workhorse
   reg. Verified to move `w0` from `$a0` to the target's `$v1` across all coordinates. **Caveat
   (also proven):** applying it to the highest-pressure iteration can make its accumulator out-price a
   held pointer for a shared reg (RC-6). Apply, then read `.greg` dispositions for collateral before
   claiming the match.

3. **"MERGE" HAS A DIRECTION, AND IT IS THE OPPOSITE OF NAIVE (root B negative result).** Merging at
   the WRONG scope backfires: merging `w0/av` at *vertex-block* scope (multi-death, still GLOBAL) drags
   the WHOLE chain onto `w0`'s reg `$a0` (e2, regressed) — the reverse of the goal. The merge only
   helps when it is ALSO single-death-scoped. Confirms §44/§45's "each giant is its own class": the
   merge and the block-scope are ONE lever, not two.

4. **`match_one` positional count is untrustworthy at wrong length — gate on the aligned differ.**
   e4's real closeness (81 aligned) beats e1's (92) yet e4's positional (105) looks far worse than e1's
   (46), purely from a +1 length cascade. The ledger disagreements on this function trace to exactly
   this. Rule: read `adiff.py`, not the positional headline, when the length is off by any amount.

## Method / reproducibility
- Iterate: `bash .run/giants/fable_8016CBC0/chk.sh <c> <tag>` (prints match_one positional + the
  aligned real-diff). Variants preserved in `.run/giants/fable_8016CBC0/e{0..10}_*.c`.
- Dumps: `bash .run/giants/dump.sh <c> <prefix>` (pinned triple + `-dS -dR -dj -dc -dg -dl -dd`) →
  read `.i.lreg` (per-pseudo refs/live_length/deaths) and `.i.greg` (dispositions + conflict matrix).
  Root A and root B were both settled from these dumps + `tools/reference/gcc-2.7.2/{global,flow,
  local-alloc}.c` — NO gdb run was needed (the dumps carried the decision). The gdb oracle
  (`find_reg @ 0x0814c8ca`, `find_free_reg @ 0x08149ad0` in this cc1) remains the fallback to confirm
  the pv-vs-coord-z `find_reg` grant for a permuter-free root-B close.
- Gate reminder: a `match_one` result is a CANDIDATE; finish any bank on the whole-binary byte-gate.
