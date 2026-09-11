# func_801818A4 (ov_SC02_031) — P36 S104 d38 — score 0, zero levers (body_free 17 → 0 on the first --try)

## (a) The residual
Score 17, COUNT (mine 38, target 37). The target copies `a1` into `$s0` in the prologue and reads every field through
`$s0`. body_free keeps the pointer in `$v0` for the first block's reads (`move v0,a1`), then copies it late
(`move s0,v0` just before the first `jal`), and uses `$s0` only in the else arm. That is one extra `move`. Because
`$v0` holds the pointer, the loaded halfwords move to `$v1` (the v1->v0 ×7 pairs), and the `move a2,s1` lands in a
different place.

## (b) The pass and the decision (read in the dumps, scratch/dumps_free vs scratch/dumps_c1)
- The .rtl has two pointer pseudos: 73 = `a1` (the parameter copy, insn 6) and 74 = `s0 = 73` (insn 13).
- cse follows the jump. Its first path, `2 to 95`, takes the branch into the else arm, so the extended block covers
  every use. make_regs_eqv (`cse.c:846-856`) makes a new reg the canonical one only if it outlives the block, so 73
  stays canonical and every read of 74 is rewritten to 73, the else arm's insn 68 included.
- cse_main then reprocesses from the start along the fall-through path, `2 to 64` (`cse.c:8352-8355`,
  `val.path_size > 0`). Now 74 outlives the block (its recorded last use, insn 68, lies past uid 64), so 74 becomes
  canonical. The first block's reads are rewritten to 74, and the `(set REG0 REG1)` swap (`cse.c:7440-7474`) turns
  insns 6/13 into `74 = a1; 73 = 74`. Insn 68 keeps reading 73: its block (`66 to 95`) starts at a label with no
  equivalences.
- Result (.cse): one pseudo lives only in block 0 with 5 uses, and one copy crosses the call with 2 uses. cse2 swaps
  the numbers back (.cse2 insn 6 `73 = a1`) but the structure stays. .lreg: "Register 73 used 5 times across 14 insns
  in block 0" gets `Register 73 in 2` from local-alloc (`$v0`). "Register 74 … crosses 1 call" gets 16 from global
  (`$s0`). That produces the late `move s0,v0`.
- With no local (c1): one pseudo, .lreg "Register 73 used 5 times across 18 insns; crosses 1 call", `73 in 16`. It is
  set from `$a1` in the prologue, which is the target's `move s0,a1`.
- Proven on bytes: `--try` = 0 (c1). The two-pass cse reading matches the .cse/.cse2/.lreg/.greg dumps. I did not
  step through regno_last_uid's lifetime in a debugger: that it is not recomputed between the two paths is inferred
  from insn 68 keeping 73.

## (c) The move that closed it
Delete the local `s16 *s0 = (s16 *)a1;` and read through the parameter: `((s16 *)a1)[6]` etc. (PACK/body.c).
Readability alternative, also 0 on both copies: the two stack halves as `SVECTOR a, b;` (the TU's own typedef), with
fields `.vx/.vy/.vz` instead of `stack_buf[0..6]` (scratch/v2.c).

## (d) GENERATOR PROPOSAL
When a local is only ever the cast copy of a parameter (`T *p = (T *)argN;`, never reassigned) and the function
branches, delete the local and substitute `((T *)argN)` at every use. d24's `T x = argN;` rule, extended to CAST
copies. The trigger in the objdump is `move vK,aN` early plus `move sJ,vK` just before a `jal`.

## (e) What did not work
- A body-local struct pointer `struct {…} *r = a1;` with field reads → 17, byte-identical to body_free. The defect is
  the local copy, not the access type.
- Constant returns (d27's move) with no local → 3: `return func_8012DEB8(...) != 0;` loses the shared `sltu` shape.
  Not needed.
- The sweep's best (1, free_004.c) is semantically broken (`return (1)`), not a start. R27's port_002.c is a
  different function (a name collision with ov_SC05_001's func_801818A4).

## (f) Where the method fell short
Nothing in the method was missing: step 15 (d24) already names this move for an uncast parameter copy. But the sweep's
generator evidently matches only `T x = argN;` and not `T *x = (T *)argN;`, so the class sat at 17 (the R10
"param-copy" family does the INVERSE, routing a parameter through a local). The same defect was being papered over
elsewhere by an unmarked `do { … } while (0)` barrier in four same-shape siblings (scratch/copies.md): those
do-whiles are levers that no census counts.

## (g) Structs answer
Partly. Typing `a1` does NOT change the decision: a struct-pointer local scores 17, the same as body_free, because the
defect is cse's two-path canonicalisation of a copied pointer, not an aggregate-vs-scalar dependence. Typing the
STACK buffer as two `SVECTOR`s does not change the bytes (0 either way) but it is the honest shape:
`func_8012DEB8(a0, &a, &b)` takes two 3D points, like its sibling func_8012D714's `u16 a[3], b[3]`. For the structs
phase, `a1`/D_80188DD8 looks like a box `{ s16 ?, ?, x0, x1, ?, ?, z0, z1 }` (fields +4/+6 = x, +12/+14 = z) and
should be a typed parameter, not a cast. Declaring the PARAMETER as that struct pointer is a signature change: the
TU's extern is `(void *, void *)`. It is not needed for the bytes.

## Copies — scratch/copies.md
func_80186B1C (ov_SC02_011, the class's second copy) → 0 with the same text. Four more same-shape siblings lose
their unmarked do-while barriers with the same move: func_801826E8 (ov_SC03_024), func_801865E4 (ov_SC02_011),
func_801848A4 (ov_SC06_000) and func_80188FB4 (ov_SC03_014). All `--try` 0.
