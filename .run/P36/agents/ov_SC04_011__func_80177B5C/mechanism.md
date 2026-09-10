# func_80177B5C (ov_SC04_011_jr_801734BC.c) — T7 agent c19 — NOT CLOSED, score 2

Start: lever-free score 135 (mine 142 / target 147). Final: **score 2** (147 / 147, ORDER class), `PACK/body.c`
(= `scratch/v19d.c`). No pin, no asm, no volatile, no zero term, no declaration alias. Every register in the function
matches; the only residual is one `or` placed two slots late (see (e)).

## (a) The residual, in one sentence per layer

1. SHAPE (135 -> 61): the target's prologue copies three argument registers into other registers and reads the
   ARGUMENT register for the early uses and the COPY after the loop. That is the K&R narrow-parameter conversion of
   gcc 2.7.2, not the four `yt/tr/xr/yr` copies the lever body laundered.
2. ALLOCATION (61 -> 4): the block-0 locals ca/mk1/cc1 must land in t0/t1/t2, the `(y+1)<<16` value in a1 and the
   cl chain in v1; each depends on which qty local-alloc sees first.
3. SCHEDULE (4 -> 2): `move t6,a1` must be emitted where the body copies `bits`, not in the prologue.
4. SCHEDULE (2, open): `or v0,a1,v0` (the prim-1 p[2] value) must precede `sll v1,t9,6; ori v1,v1,0x4016`.

## (b) Passes and decisions (all read in this function's own dumps under `scratch/dumps_*`)

1. `assign_parms` (function.c, the `nominal_mode != passed_mode` arm): an old-style `s16` parameter arrives in SImode.
   It is copied to an SI temp, and the conversion insn `(set (reg:HI p) (subreg:HI temp))` produces a second pseudo.
   The modes differ, so cse cannot fold the copy. cse substitutes the SI temp into the first extended basic block. The
   loop ends that ebb, so the post-loop uses read the HI pseudo, which lives in a callee-saved register. PROVED:
   142 -> 147 instructions. The sibling `func_80177DA8` (same TU, matched, lever-free) declares `s16 idx` and shows
   the same `move t7,a2; sll a2,a2,16; sra a2,a2,16`.
2. `u8 m = n` (the sibling's spelling): a QImode copy survives cse and gives `bnez v0 / move a3,v0`.
3. `x1 = (u16)(x - 3)`: the front end narrows the truncation, so the add is done on the SI temp and a single `andi`
   follows it. `(x - 3) & 0xFFFF` on an `s16 x` makes cse share one sign extension between x1 and x2 (2 extra insns).
   `u16 x1` puts the `andi` at the use instead.
4. sched1 birthing (`sched.c:2469` `birthing_insn_p`, `adjust_priority` `:2507`, `LAUNCH_PRIORITY` `:187/:3902`):
   when a single-set REG def's consumer is scheduled (backward), the def is launched right before that consumer. A
   multi-set def (or a SUBREG-dest def) keeps priority 1 or 2 and sinks by LUID. The post-loop `cs/cl/uv` REUSED in
   body_free were multi-set, so sched1 hoisted them above the tag store. One name per value (`cs2`, `cl2`, `tt2`)
   gives the target's post-loop order. PROVED.
5. local-alloc (`block_alloc`, `qty_compare_1` `local-alloc.c:1598`, `combine_regs` `:1722`): a qty's priority is
   floor_log2(refs)*refs/len, and phase 2 gives each qty the lowest free register over its life.
   - `yt <<= 16` made yt one global for two values. With `yl = yt << 16` for the loop, the block-0 `yt` is a local qty
     that takes a0 and blocks a0 for the rest of block 0. PROVED.
   - `c0 = yt + 1; c0 <<= 16;` (in place, multi-set, block-local): the `(y+1)<<16` value is one qty
     {c0, `c0 | x2`}, which lands in a1 once v0/v1/a0 are busy. PROVED (score 35 -> 4 with the next move).
   - `c = v << 6; c |= 0x4016; cl = c << 16;` (c multi-set, block-local): c's two defs do not launch, so sched1
     places them early and c's qty is LONG. Its priority 2*4/12 = 6667 then falls below the x1/w qty (20000), which
     takes v0 first, so c lands in v1. `set_preference` (`global.c:1535`) on `cl = c << 16` gives the global cl a v1
     preference. Through `regs_someone_prefers` (`global.c:953`), the giv and q then skip v1 (target a1/a2), and cl gets
     v1. PROVED: every register matches at score 4.
6. The `bits` copy: with `u16 bits` the HImode conversion is emitted in the prologue (LUID 2). The target has
   `move t6,a1` after the mk1/cc1 constants, which is the tree's `bb = bits` position. `u32 bits` plus a `u16 bb = bits`
   local at that statement puts the only copy there, and the prologue copy of a1 becomes a no-op. PROVED (4 -> 2).

## (c) The source moves (each measured on bytes, in this order)

- K&R `s16 tbli; s16 x; s16 y;`; delete the `tr/xr/yr/yt` copies. 142 -> 147 insns.
- `u8 m; m = n;` with `nv = ((m * 8) + 8) | 0x4000`; `n = (u32)(bb << 16) >> 28`.
- `x1 = (u16)(x - 3); x2 = (u16)(x + 5);`, and post-loop `(u16)(x + 0x2A)`, `(u16)(x + 0x32)`.
- post-loop: one name per value (`cs`, `cs2`, `cl2`, `tt`, `tt2`).
- `yl = yt << 16` for the loop (yt stays block-local).
- `c0 = yt + 1; c0 <<= 16;` then `p[2] = c0 | x1` / `p[2] = c0 | x2`.
- `c = v << 6; c |= 0x4016; cl = c << 16;`.
- `u32 bits` + `u16 bb; bb = bits;` right after `cc1 = ...` (the loop uses bb).

## (d) Generator proposals

- (params) When the target's prologue copies `$aN` into another register AND the early uses read `$aN` while the
  post-loop uses read the copy, declare that K&R parameter `s16`/`u16` and delete the body's copy variable. The same
  holds for a stack argument: `lw aK; move sJ,aK; sll/sra aK` is a narrow 5th parameter.
- (sched1 hoist) When a post-block def (`x = ...; ... x |= ...`) lands ABOVE the target's first store, split the
  reused name into one name per value, so each def is single-set and launches at its consumer (`sched.c:2469`).
- (local v1-by-length) When a two-insn temp chain lands in v0 but the target has it in v1 while v0 holds a longer
  value: make the chain's variable multi-set (`c = a; c |= K;`) so its defs do not launch. The qty becomes long and
  falls below the v0 holder in `qty_compare_1`.
- (copy position) When a parameter copy `move tN,aK` sits later than the prologue in the target, declare that
  parameter at full width and copy it into a narrow local at the statement where the target does the move.

## (e) The open residual (score 2), and why it resists

Target `... sll a1,a1,16; or v0,a1,v0; sll v1,t9,6; ori v1,v1,0x4016; sll v1,v1,16; sw v0,8(t3)`; mine puts the
`or` after the `ori`. This is sched2 (post-reload), T-19 and T-20 of its backward list. `or` (88) and `ori` (84), then
`or` and `sll` (82), are both priority 2 and class 3, and store hazards are not involved. `rank_for_schedule`
(`sched.c:2385`) then falls to INSN_LUID, which is sched1's output order, where my 82/84 precede 88. The target
needs 82 and 84 AFTER 88 in sched1's output.

Why that is not reachable with a single-set prim-1 value: when sched1 schedules the p[2] store (backward), the
`or`'s dest is a single-set live REG, so it launches immediately. So 88 always sits directly before the store 90
(`scratch/dumps_l` shows `64 65 88 90`). If c's chain comes after 88, it therefore starts after 90. It cannot then
overlap any v0 holder that local-alloc places first, and its temps take v0 (proved: v8a, v10c, v20a/b/c all
give cl temps in v0, or 2 again). The lever body escaped this with the launder on `w`: an asm output makes w
multi-set, so 88 does not launch, and sched1 keeps `w; cl chain; st` in source order. It also escaped with the `cl`
pin: `combine_regs`' hard-reg arm gives the temp qty a v1 suggestion (phase 1, `local-alloc.c:1463-1475`). Every
natural way I found to make the p[2] value multi-set fails:
- `x1 |= c0`: x1's defs float to the top, and x1's qty loses v0.
- `w = x1; w |= c0` and `w = c0; w |= x1`: cse and flow delete the dead copy before sched, so reg_n_sets is 1 again.
  All four spellings, in three placements each, score 2 (`scratch/v22*.c`).
- A post-loop reuse of w: w becomes global, and the cl temps take v0 (score 70).

## (f) What did not work (byte evidence, `scratch/`)

- u16 bits alone (v1): 130. `(x - 3) & 0xFFFF` with s16 x (v2): 150 insns. `u16 x1` (v3b): 159.
- body_free's reuse structure with lever-free params (v13a/v14a): 114-126; the post-loop defs sink.
- In-place `cl` (`cl = v << 6; cl |= 0x4016; cl <<= 16`, global, v12*/v14*): no local temps, so cl has no v1
  preference; the giv/q take v1 (90-120).
- u16 `c` (v21*): 76 (combine removes c; the chain becomes SI temps that launch and take v0).
- Search: three annealing searches over statement order and spelling options (the `srch*.py` harness in `scratch/`,
  scored by `scratch/fast.py`, which runs the TU recipe's own pipeline on a minimal TU and `delever_search.classify`).
  They found the in-place `c0`, the multi-set `c`, and `c0 |= x2` structures, and hit a floor at 2. A final pass over
  x1/w/c0/c spelling variants is recorded in `scratch/s7_*.log`.

## (g) Where the method fell short

- The lever body's `.sched` dump (`scratch/dumps_tree`) was the single most useful file. It shows the sched1 order
  that produces the target. A launder/pin body is a working oracle for ORDER even when its registers are forced.
  Proposal: dump the tree body first and diff its sched1 order against the candidate's.
- `alloc_table.py` only covers global allocnos. The decisive facts here were local-alloc qty priorities and phase-1
  suggestions, which `lpri.py` (c1/c8) approximates but which do not include tied qtys. Proposal: print tied qtys and
  their combined refs/len, and flag qtys that carry a hard-reg suggestion.
- An order search is cheap here: 0.12 s per candidate with a minimal TU and the TU recipe's pipeline (`fast.py`),
  and it is parallel-safe. It found two structural moves I had not predicted, in about 10 minutes across 12 seeds.
  Proposal: make that scorer a tool (`delever_search --try` serialises on one per-function scratch object).
