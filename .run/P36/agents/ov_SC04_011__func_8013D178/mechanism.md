# func_8013D178 — agent c16 (P36 T7, S103) — CLOSED, score 72 -> 0, lever-free

## (a) The residual in one sentence
Same 110 instructions; a pure `$a0<->$a1` swap across all nine identical groups: the lever-free body put the
pointer `p` in `$a0` and the zero-extended target byte `t` in `$a1`, and the original has `t` in `$a0` and `p` in `$a1`
(`v` sits in `$v1` and the `andi` temp in `$v0` in both). COUNTED FIRST: 110 vs 110, same mnemonics, registers only.

## (b) The pass and the decision (read, then proven on bytes)
Global allocation order, `global.c:587-610` `allocno_compare`: priority = `floor_log2(refs) * refs / live * 10000`,
highest first; `find_reg` (`global.c:945-980`) then hands each allocno the lowest free hard reg, skipping in pass 0
any reg a conflicting allocno prefers (`regs_someone_prefers`, `global.c:953`) — which is why `v` skips `$v0` (the
per-group `zero_extend` temp prefers `$v0`) and lands in `$v1`. After `v`, whoever is allocated NEXT among {t-temps, p}
takes `$a0`, the other `$a1`.

`tools/alloc_table.py` on the lever-free body (`scratch/dumps_free`):
- r72 `v` (one pseudo, all nine groups): refs 36, live 72, pri 25000 -> `$v1`
- r74 `p` (ONE pseudo reused by all nine groups): refs 36, live 99, pri **18181** -> allocated 2nd -> `$a0`
- r76/r83/... the per-group `zero_extend` of `t` (combine folded the QI `t` into the load): refs 3, live 4, pri **7500** -> `$a1`

So `p` outranks the nine t-temps only because it is ONE allocno carrying 36 refs (`floor_log2(36) = 5`).

## (c) The move that closed it
Give each group its own block-scoped pointer (`{ u8 *p = &D_801F1558; u8 v = *p, t = D_801F15F8; ... }`). Nine `p`
allocnos of refs 4 / live 22 -> pri **3636**, now BELOW the t-temps' 7500: the t-temps take `$a0`, the pointers `$a1`.
Proven on the dump of the matching body (`scratch/dumps_final`, `.greg` order line: v's 10000, t-temps 7500, p's 3636;
dispositions `72 in 5`, `76 in 4`, `73 in 3`). Byte-proven variants, all score 0:
- `b1`: ONLY `p` block-scoped, `v`/`t` left function-scoped -> 0 (so the split of `p` alone is the whole mechanism);
- `b2`: `p` and `t` block-scoped -> 0;
- `b3` / `body.c`: all three block-scoped -> 0 (chosen: each group self-contained; the nine duplicated
  `extern unsigned char D_801F15F8, ...` lines collapsed to one line per array — declarations, byte-neutral, re-tried: 0).

## (d) GENERATOR PROPOSAL
When a REG residual is a swap between a function-scoped local that is re-assigned at the head of N repeated statement
groups and a per-group compiler temp, rewrite the local as one block-scoped declaration per group
(`{ T x = init; ...group... }`): its refs drop by N (and `floor_log2` with them), so its global priority falls below the
temps' — check the sign with `alloc_table.py` first (single-allocno pri vs. temp pri must flip to the target's order).
This is generator R23 (split a reused local) extended from local-alloc to GLOBAL allocnos: the local here spans blocks,
so `local-alloc.c:472` is not involved; the lever is `allocno_compare` arithmetic.

## (e) What did not work (byte evidence)
- `s32 t` / `u32 t` (t becomes a real 27-ref allocno, pri 30000, outranks `v`): score 72, now `v`<->`t` swapped
  (`a0->v1 x36`), `p` correctly in `$a1` — right direction for `p`, wrong for `v`.
- statement reorders (`t = C; p = &A; v = *p;`, `p = &A; t = C; v = *p;`) with `u8`/`s32`/`u32` t: all 72.
- `u16 t`, `s32 v`, `s32 v, t`: 81.
- The brief's leads did not apply: there are NO calls in this function, so the "`$5` pin = dropped call argument" and the
  implicit-`$a1`-reader (c3/c12) entries are irrelevant; nor was c11's "reuse one temp across blocks" (the opposite move
  closed it here: UN-reuse `p`).
- The mechanical search's R4 decl-move and R7 block moves (history.txt, all 72) move/wrap declarations but never split
  one reused variable into per-group variables.

## (f) Where the method fell short / what worked
- The allocation table (step 4 / PROMPT step 1) settled it on first read: three priorities, one inequality. Total ~12
  compiles. The METHOD's c1/c8 entry ("a local REUSED across statement groups ... split it") points at the right move
  but frames it as a local-alloc refusal (`local-alloc.c:472`); here the reused local is a global allocno and the
  mechanism is priority dilution by `floor_log2(refs)` — worth a sentence in the addendum.
- `tools/cc1_dumps_tu.sh` fails on this TU (`#include "../shared/engine_prelude.h"` needs `-Isrc/<overlay>` on the
  cpp line; it refuses with CPP-EMPTY). Worked around with `scratch/dump.sh` (same cc1 flags + `-Isrc/ov_SC04_011`).
