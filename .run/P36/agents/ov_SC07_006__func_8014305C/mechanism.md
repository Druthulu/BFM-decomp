# func_8014305C (ov_SC07_006_jr_80140608.c) — CLOSED, score 0, no lever

## (a) Residual (lever-free start, score 12, COUNT 41 vs 38)
Two defects. The three EXTRA instructions (`sw s2` / `move s2,s0` / `lw s2`) are a third callee-saved register
holding a second copy of the parameter (`s0_param = param_1`), and the store/test of the call result ran on a
callee-saved register instead of `$v0` (target: `move s1,v0; bnez v0; sw v0,32(s0)`). Not the S103 c2 twin-biv
shape (there is no loop); a copy-survival + expand-shape residual.

## (b) Passes and decisions (dumps read; the closing claims PROVEN on bytes)
1. **The parameter copy (+3 insns).** `.rtl`: `72 = a0` (param_1), `73 = 72` (s0_param). The first `.cse` path
   (2→87, following the jump) makes 73 the class head (`make_regs_eqv`, `cse.c:853-858`: it lives beyond the block and
   longer) and applies the `(set REG0 REG1)` swap (`cse.c:7440-7474`) → `73 = a0; 72 = 73`; the separate second
   processing of the arms canonicalises differently, so after cse the then-arm/store read 72 and the else-arm reads 73.
   Both pseudos are live across the branch and across calls → two callee-saved registers ($s0, $s2), copy survives.
   Deleting `s0_param` (use `param_1` directly, as both siblings do) removes it. PROVEN (a1: 38 ins).
2. **The `$v0` store/test (+ the $16/$17 pin roles).** With statement form `iVar2 = call();`, the lhs is a
   VAR_DECL, so `expand_call` gets `iVar2` as its target and emits `74 = v0` directly (`calls.c:2031-2039`); every
   later reader (store, test, else-arm) reads one user pseudo that crosses a call → `$s`-reg, and the test becomes
   `bnez s0` (a1: score 14, registers permuted).
   With the combined form `*(int *)(param_1 + 0x20) = iVar2 = call();` the OUTER lhs is an INDIRECT_REF, so
   `expand_expr` MODIFY_EXPR calls `preexpand_calls` first (`expr.c:6199-6202`), which expands the call with a NULL
   target (`expr.c:8699`) → `target = copy_to_reg (valreg)` (`calls.c:2114`) = a fresh non-user pseudo 75. The inner
   assignment's `store_expr` then sees temp 75 != target 74 with `want_value` → `dont_return_target`
   (`expr.c:2824-2829`), emits `74 = 75` and RETURNS 75 (`expr.c:2951-2952`), so the outer store is `*(p+0x20) = 75`.
   `.rtl` of the closed body: `75 = v0; 74 = 75; mem = 75; if (74 ...)`; by `.lreg` the test also reads 75, 75 is
   block-local and dies at the branch → local-alloc ties it to `$v0` (`;; Register 75 in 2`), and the user variable 74
   is the copy that crosses `func_8001CA1C` → `$s1`. That is exactly the target's `move s1,v0; bnez v0; sw v0`.
   PROVEN (a2: score 0).

## (c) The moves (R71 — a banked sibling's spelling; closed on the 2nd `--try`)
- Delete `s0_param`; use `param_1` directly (removes the third callee-saved register).
- Delete `s1_copy`; write the store and the call as one combined assignment
  `*(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))func_8012C1B8)();` and use `iVar2` in the else-arm.
Ported from `func_80142E38` (same TU, line 1752; the same five callees, lever-free). The tree's header for this
function ("$16=param pin; explicit $17 copy of the call result ... store BEFORE the s1 copy") describes the levers
and is now stale; the neighbour note on `func_80142DC4`'s family ("combined store-assign `*(p)=v0=call()` keeps
test/store on $v0, copy to $s0 for the else") is the correct reading.

## (d) Generator proposal
When a call result is stored to memory and tested in `$v0` but the else-arm reads it from a callee-saved copy
(`move sK,v0; bnez v0; sw v0,..`), fold `x = call(); *(mem) = x; [y = x;]` into `*(mem) = x = call();`
(preexpand_calls gives the call a block-local temp that local-alloc ties to $v0, the user variable becomes the
surviving copy) — and, separately, when a parameter is copied into a local at entry, substitute the parameter
(delete the copy) before any register dial.

## (e) What did not work (byte evidence)
- body_free (explicit statements, `s0_param` copy kept): 12, COUNT 41/38.
- a1 = body_free minus `s0_param` (explicit `iVar2 = call(); store; s1_copy = iVar2;`): 14, 38/38, the call result
  on `$s0` for the test/store (s1<->s0 permutation, `bnez s0`). The count was fixed; the expand shape was not.
- The mechanical search reached 2 only with a `do { } while (0)` around the call (history.txt, R7 do-while @1845) —
  the banned barrier, and the same trick the lever-free sibling func_80142EC0 still carries
  (`do { ret = func_8012C1B8(); } while (0);`). That sibling is very likely closable the same way (combined
  store-assign), not tested — it is not my function.

## (f) Where the method fell short
Nothing structural: related.txt listed func_80142E38 (third entry) and neighbours.txt carried the one-line crack in
English. The brief's steer (R22 twin bivs) did not apply — no loop; COUNT the extra insns first: they were one
extra callee-saved register's save/copy/restore, i.e. one surviving copy, not a per-iteration step. The engine's
move set has no "merge `x = call(); *m = x;` into `*m = x = call();`" (the inverse of its split moves).
