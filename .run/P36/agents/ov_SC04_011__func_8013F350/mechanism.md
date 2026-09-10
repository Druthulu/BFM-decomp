# func_8013F350 (ov_SC04_011) — T7 agent c28 (re-draw after b9; b9's text is in scratch/prev_mechanism.md, prev_body.c)

**Result: NOT closed. Best honest score 42** (`PACK/body.c` = b9's tail move alone: `off = st << 1;` above
`p2e`/`p3e`, `u16 pad`, plain `chg = 0;`). b9's 16 is still in `scratch/prev_body.c`. It needs two compensating
moves (`s32 pad` and `do { chg = 0; } while (0)`), so it is not claimed. The brief asked one question: can c11's
derived-pointer / cse2-only re-association keep the `&D_8011511C` base? **No. It fails for two independent
reasons, and the second one also defeats the banned `do { } while (0)`.** All scratch is in `scratch/c28/`
(`run.sh <body> <tag> dump` = `--try` + splice into `tu_free.c` + `tools/cc1_dumps_tu.sh`).

## (a) The residual in one sentence

The tail is byte-identical (b9's move holds). The whole remaining distance is the head. The target holds
`&D_8011511C` in `$a1` for three accesses: `lhu 0($a1)` in BB0, `lhu 4($a1)` in BB1 (the fall-through of
`beqz pad`), and `sh 4($a1)` in the inner-else block (target of `bne pad,prev`). Plain C folds all three to
absolute `lui/%lo` and deletes the pointer. That is 6 instructions where the target has 5. The +1 shifts every
later `j` target, and those shifts make up almost all of the 42.

## (b) Pass and decision, file:line (read in `tools/reference/gcc-2.7.2/`, checked in this function's dumps)

1. **c11's mechanism, confirmed here.** `fold_rtx` tries its associative rewrite before constant folding
   (`cse.c:5580-5667`, `lookup_as_function` `:1224`; `fold_rtx(REG)` returns the REG unchanged, `:4807`). So an
   address `(plus X c)` whose register X holds `(plus pd K)` in its class becomes `(plus pd K+c)` and is NOT folded,
   even though pd's `qty_const` is known. `find_best_addr` applies that fold once per processing of the insn
   (`cse.c:2663-2665`). The next time any cse pass processes `(plus pd K+c)`, pd's class has no PLUS, so
   `simplify_binary_operation` folds it to `const(D_8011511C+4)`.
2. **Obstacle 1: no cse1-only block boundary exists in plain C.** The base is set in BB0, and the offset-4 read is in
   BB1, which is the fall-through of BB0's branch. cse ends an extended block only at a CODE_LABEL, at
   `NOTE_INSN_LOOP_END` (cse1 only, `cse.c:8039-8055`), or at SETJMP. BB1 has no label: nothing jumps to 0x30 in the
   target. The head contains no loop and no single-set if/else that the post-cse1 jump pass could fold. So in both
   passes the derived pointer and the access sit in the base's extended block. Association then happens in cse1,
   and cse2 re-folds the result. Proven: h1 (`pe = pd + 1; pe[1]`), h2 (pe declared in the then-block), h3
   (`(&D_8011511C)[2]`, c9's forced-constant spelling), and h4 (base derived from `&D_8011511A`) all score **42**,
   the same as the start.
3. **Obstacle 2 (new): cse2 processes the READ's block twice.** With `-fcse-follow-jumps`, the inner `bne` is a
   followable TAKEN branch: its target label has one use and a BARRIER before it (`cse.c:8098-8124`). So cse2 walks
   the head as the paths `[T]`, `[N,T]` and `[N,N]` (`.cse2`: "Processing block from 2 to 99 / 2 to 88 / 2 to 73").
   It rescans from insn 2 each time, and BB1 lies on both `N` paths. Path `[N,T]` associates the read to
   `(plus pd 4)` and writes it into the insn (`validate_change(...,0)`). Path `[N,N]` then sees `(plus pd 4)` with pd
   known and folds it. The store sits in the TAKEN block, which is scanned once, so it survives.
   **Byte proof** (all with a banned cse1 split, `do { pe = pd + 1; pad = *pd; chg = 0; } while (0);`):
   - `d1` → 27. `.cse` keeps both accesses as `(plus (reg 74) 2)`. `.cse2` turns the store (insn 77) into
     `(plus (reg 72) 4)` (**kept, `sh 4($a1)`**) and the read (insn 39) into `const(D_8011511C+4)` (**folded**).
   - `d6` (diagnostic): the same body plus a NEW read `pe[2]` inside the single-path store block. It compiles to
     `lhu $2,6($5)`, register-relative, in the same compile where the BB1 read folds. So what decides it is how many
     times the block is scanned, not whether the access is a read or a store.
   - `d4`: a second banned `do { } while (0)` around the inner then-arm scores 10, and the read is **still folded**
     (the LOOP_END note is not the insn right before the label, so the branch stays followable).
   The only way to keep a read that lies on two cse2 paths is to have the base's constant unknown there. That needs
   an asm output with no REG_EQUAL (the tree's launder). A chain of derived pointers (X → Y → pd, one association
   per scan) collapses as well, because every chain link's own set is re-associated in path 1, and `src_folded`
   wins cost ties (`cse.c:6781-6789`). Only the chosen source is re-inserted into the class (`cse.c:7197-7217`, with
   `sets[i].src` updated at `:6910`).

## (c) The source moves

1. `off = st << 1;` hoisted above `p2e`/`p3e` (b9's tail move, re-verified): the plain-C replacement for the `$4` pin.
2. Nothing closes the head. `u16 pad` and plain `chg = 0;` stay as they are (b9's `s32 pad` / `do{}while(0)` are
   compensating errors, refused). **The `$5` pin + launder is irreducible in plain C**. Even the banned
   do-while(0) split cannot keep the BB1 read, and b9 already showed the `$5` pin is separately needed for
   the register 3-cycle (score 9 with the launder).

## (d) Generator proposal

**When the lever is a launder on a global base and the target reads `k($base)` in a block that lies on two or more
cse2 paths (the access insn's uid falls in two `.cse2` "Processing block from S to E" ranges with the same S),
mark the lever IRREDUCIBLE and skip the derived-pointer (c11) and forced-constant (c9) rewrites. Try them only when
every base-relative access sits in a block that cse2 scans once (a TAKEN-branch target, or after a multi-use
join), and when a cse1-only boundary exists between the base's set and those accesses.** The detector is mechanical:
it needs one `.cse2` dump of the lever-free body and the uid of each folded access.

## (e) What did not work (every number is a `--try` score)

| body | score | why |
|---|---|---|
| `base.c` = `PACK/body.c` (b9 tail move, honest) | **42** | head folded, 491 ins |
| h1 `pe = pd + 1`, `pe[1]` read+store | 42 | cse1 associates, cse2 folds |
| h2 same, `pe` declared inside the then-block | 42 | same EBB |
| h3 `(&D_8011511C)[2]` (c9 forced-constant) | 42 | `use_related_value` (`cse.c:1781`) gives `(plus pd 4)` in cse1, cse2 folds |
| h4 base derived from `&D_8011511A` | 42 | same |
| d2 banned `do{pad=*pd;chg=0;}while(0)`, no derived ptr | 34 | pd is known again in cse2, folds |
| d1 banned split + `pe` | 27 | store kept, read folded (two cse2 paths) |
| d4 d1 + second banned do-while | 10 | read still folded; the count is compensated elsewhere |
| d6 diagnostic read in the store block | 30 | that read stays `6($5)` (single path) |

## (f) Where the method fell short

- The c11 recipe ("the FIRST cse pass must not see the late reads; the second re-associates") is incomplete. It
  also requires that **the second pass scans the access exactly once**. Path following rescans a fall-through
  block once per downstream branch outcome. c11's late reads happened to lie on a single path. The METHOD line for
  c11 should say this, and the `.cse2` "Processing block" lines are the check.
- `residual_moves.md` / METHOD have no entry for "cse path multiplicity". It is a cse-internal fact that neither the
  allocation table nor the residual shows. The per-insn detector in (d) would have settled this pack in one compile.
