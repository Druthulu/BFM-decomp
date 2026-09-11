# func_80180598 (ov_SC01_080_jr_8017AE2C.c) — e19, P36 S104 T7

**Final: score 0, plain C, ZERO levers** (tree: 2 pins `$16`/`$17`; before → after = 2 → 0). `body.c` = `scratch/c5.c` with the locals renamed (`s1`→`obj`, `v0`→`ret`, `t`→`v`; declaration order kept), re-scored 0.

(a) Residual: lever-free text had an extra callee-saved `$s2` (the `param_1 = arg0` copy) and, once that copy was
deleted, `arg0`/`iVar1` swapped `$s0`/`$s1` with the branch test and the `+0x20` store reading the callee-saved copy
instead of `$v0`.

(b) Mechanism (proven on bytes + dumps `scratch/dumps_c5`, `scratch/dumps_vb`):
- The copy `s1 = v0;` must sit IMMEDIATELY after the call-result assignment, BEFORE `*(arg0 + 0x20) = v0;`. Then the
  call-result pseudo keeps the store and the `!= 0` test (short life → local-alloc ties it to `$v0`), and the copy keeps
  only the else-block uses (3 refs), whose `allocno_compare` priority (`global.c:594-607`) falls below `arg0`'s → `arg0`
  gets `$s0`. Store first, copy second (`scratch/vb.c`, score 17): cse makes the longer-lived copy the class head
  (`make_regs_eqv`, `cse.c:846-862`), the test reads it, combine folds the remaining copy into the test, and ONE pseudo
  with every ref (priority 14285 > arg0's 11379, `tools/alloc_table.py`) takes `$s0`. With the copy adjacent, cse's
  `(set REG0 REG1)` swap (`cse.c:7440-7474`, needs the previous insn to set REG1) fires instead and two pseudos survive
  into combine (`.combine`: insn 16 `73 <- 74`, test/store on 74).
- `param_1 = arg0` deleted: the copy costs a third callee-saved register (`scratch/vd.c`, score 17 with everything else right).
- The lh temp `t` (tree's `v0`) stays: inlining it into `D_80127190 = …` reorders the stores (`scratch/c4.c`, score 10, sched).

(c) Moves: delete `param_1 = arg0` (use `arg0`); write the copy `s1 = v0;` directly after `v0 = func_8012C1B8();` and before
the `+0x20` store (the shape of the matched siblings func_8018045C and ov_SC01_077 func_80186434); keep the lh temp. The
if/else form (`scratch/va.c`) and the early-`return` form (`scratch/c5.c`, delivered — matches func_8018045C) both score 0.

(d) GENERATOR PROPOSAL: when a call result is stored and tested and also copied to a local used after the test, and the
residual is a callee-saved swap between that copy and a parameter, move the copy statement to the line directly after the
call assignment (before the store) and drop any `param = argN` copy.

(e) Did not work: copy after the store (17); keeping `param_1 = arg0` (17); inlining the lh temp (10); reusing `v0` for the
lh value (18 — v0 multi-death). The sweep's best (R12 width + R9 swap, 2) was a narrower-param hack, not needed.

(f) Method: step 12's "port the matched sibling" (func_8018045C, same TU, identical prologue bytes) closed it on the
fourth `--try`; the sweep never tried moving a copy ACROSS a store (R9 swaps adjacent statements only on the wrong pair).

(g) Structs: no. The decision is cse's copy-swap adjacency and pseudo refs; a struct type for `arg0` would not change which
insn precedes the copy. Not tested (nothing to test — 0 in plain C).

Other copies: none with this residual (grep of the `ret = func_8012C1B8(); … iVar1 = ret;` shape: the two others,
func_8017DCF8 here and ov_SC01_077 func_80186434, already spell the copy BEFORE the store and are lever-free — the
corroboration).
