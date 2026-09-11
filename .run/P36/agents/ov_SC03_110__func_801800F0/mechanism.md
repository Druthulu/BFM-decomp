# func_801800F0 (ov_SC03_110_jr_8017FBC8.c) — d11, P36 T7 S104

**Result: score 0, ZERO levers (2 marked barriers → 0), plain C, no goto.** Byte-proven with `delever_search --try`
on all four copies of the class (same text, function renamed):
- src/ov_SC03_110/ov_SC03_110_jr_8017FBC8.c  func_801800F0 — 0 (PACK/body.c)
- src/ov_SC05_001/ov_SC05_001_jr_80183508.c  func_80183A30 — 0 (PACK/scratch/ov_SC05_001__func_80183A30.c)
- src/ov_SC03_112/ov_SC03_112_jr_801817E0.c  func_80181D08 — 0 (PACK/scratch/ov_SC03_112__func_80181D08.c)
- src/ov_SC03_108/ov_SC03_108_jr_8017F83C.c  func_8017FD64 — 0 (PACK/scratch/ov_SC03_108__func_8017FD64.c)

## (a) The residual
The lever-free text was 86 instructions against 96 (COUNT). The if/else + `goto TAIL` spelling of `|vx| < 0xB5` and
`|vy| < 0x8D` leaves each positive arm as `slt; beqz TAIL; j CONT` and each negative arm as `negu; slt; beqz TAIL`,
falling into CONT. Post-reload cross-jump merged the shared `slt; beqz` suffix, so each positive arm became empty and
`bltz` flipped to `bgez`: 2 × 5 instructions lost. The target's two blocks also have OPPOSITE polarity. vx is
`bltz/slti/beqz TAIL/j CONT`. vy is `bltz/slti/bnez BODY/j TAIL`. That polarity difference was the clue.

## (b) The passes and decisions (read in tools/reference/gcc-2.7.2, then checked on the .jump2 dump)
1. **expand**: `do_jump` on a COND_EXPR (expr.c:9124-9147) calls itself on each arm with BOTH labels
   (`if_false ? : drop_through`, `if_true ? : drop_through`). So each arm's comparison is emitted through
   `do_jump_for_compare` (expr.c:9519) as `blt → BODY; j TAIL`: a branch to the true label plus an explicit jump to
   the false label.
2. **jump1**: the negative arm's `bnez BODY; j TAIL; BODY:` is a conditional jump over an unconditional one, so it is
   inverted into `beqz TAIL` (jump.c:1737). The positive arm's `j TAIL` is followed by the negative arm's label, not
   BODY, so it stays `bnez BODY; j TAIL`.
3. **jump2 cross-jump** (toplev.c:3142, find_cross_jump jump.c:2371) never finds a match. The walk back from
   `j TAIL` starts on a `bnez`, where the other side has an `slt` (JUMP_INSN vs INSN, jump.c:2412). The `bnez`'s
   condjump path fails `jump_back_p`. Checked in PACK/scratch/jump2_B.txt: both positive arms are
   `(ne v0 0) → label 117/144; j 208` at jump2.
4. **reorg**: `relax_delay_slots` (reorg.c:3821-3850) looks at `condjump; j`. When `mostly_true_jump` (reorg.c:1335) is
   > 0, which it is for an NE test (:1407), it inverts the condjump and swaps the two targets. The vx arm's `bnez`
   still has an empty slot, so it becomes `beqz TAIL; j CONT` (the target's vx shape). The vy arm's `bnez` already
   holds the `lui 0xb60b` in its delay slot. It is a SEQUENCE, `condjump_p` fails, and the arm keeps `bnez BODY; j TAIL`
   (the target's vy shape). One source construct therefore produces both polarities.
   Claims 1-3 are checked against the .jump2 dump. Claim 4 is inferred from reorg.c plus the final bytes; I did not
   step through `.dbr`.

## (c) The move (one edit)
The if/else + goto chain becomes one structured condition with a **ternary per axis**, and the whole body sits inside
`if (func_8012CBF4(p) & 0x2000) { … }` with no goto or label left:
```c
if ((out.vx >= 0 ? out.vx < 0xB5 : -out.vx < 0xB5)
    && (out.vy >= 0 ? out.vy < 0x8D : -out.vy < 0x8D)) { … }
```
`abs()` or `(v >= 0 ? v : -v) < K` cannot stand in for it. fold turns `A >= 0 ? A : -A` into ABS_EXPR
(fold-const.c:4848-4882, the A-op-0 case at :4864) and that emits the `abssi2` pattern (mips.md:1526, `bgez 1f; subu`), which has different bytes.
Nested ifs (`if (X) if (Y) {…}`) in place of `&&` also score 0 (candC). `&&` was kept because it reads better.

## (d) GENERATOR PROPOSAL
When a function carries `!FAKE: barrier` levers inside a sign-split range test
`if (v >= 0) { if (v >= K) goto/return L; } else { if (-v >= K) goto/return L; }` (in the residual: COUNT short by 5
per test, `bgez` where the target has `bltz … j`), rewrite each test as the ternary condition `(v >= 0 ? v < K : -v < K)`.
Join consecutive tests with `&&` and move the fall-through code into the if body. Drop the barriers and the label.
The first targets to try are the same idiom with a barrier lever in OTHER classes. I have not tested these:
`ov_SC05_003_jr_8017BEBC.c:func_80181CDC` (:5883) and `ov_SC05_005_jr_8017D898.c:func_80181DE4` (:5093), which both
use `return 0` arms. `ov_SC03_105:func_8017FAE8`/`func_80183DA0` have the same test, but their levers are pins and
launders.

## (e) What did not work / was not needed
- body_free (if/else + goto, no barriers): 15. Cross-jump merges both blocks.
- The free sweep (R2–R26, 884 compiles over g6/s7): stuck at 15. Every family mutates the goto text. None of them turns
  a statement chain into a COND_EXPR condition, so the ternary was out of the sweep's reach.

## (f) Where the method fell short
- **This lever was already in the cookbook.** §396(a) and §314b (`ov_SC02_005/func_8018074C`,
  `ov_SC04_002/func_8018691C`) describe "a cross-jump whose suffix is only `slti; beqz` → ternary inside the `if`
  condition". This is at least the third independent discovery. Neither METHOD step 3 nor step 12 points at it. The
  cross-jump bullet in step 3 offers only the two S103 uses (c6/c10) and the barrier/alias. Add §396(a) to step 3's
  cross-jump bullet, and give the sweep the generator in (d).
- §396(a) says `__asm__("")` "does not stop it". Here the tree's two barriers DO reach 0 (body_tree.c scores 0), so
  that sentence is too strong. The barrier works when it sits between the `beqz` and the `j`.
- The residual's hunk view hides the polarity asymmetry between the vx and vy blocks. The whole-function objdump from
  step 1 showed it. Reading reorg's `relax_delay_slots` swap explained how one construct gives both shapes.

## (g) Structs question
No. This lever was about control flow: cross-jump pattern equality after reload, and reorg's swap of a conditional
jump followed by a jump. It had nothing to do with aliasing or scheduling. `out` is already a struct (SVec_80181D08).
A struct type for `param_1` (fields 0x02, 0x06/0x0A/0x0E, 0x20, 0xE4) would make its accesses aggregate
(expr.c:4568-4577). That affects `true_dependence` in sched and store/load forwarding in cse, and neither pass is
involved here. Not tested, because the body already closes with zero levers. Giving `param_1` a struct stays a
readability task, not a matching one.
