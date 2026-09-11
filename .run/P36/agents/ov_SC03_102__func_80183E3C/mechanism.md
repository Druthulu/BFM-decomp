# func_80183E3C (ov_SC03_102_jr_8017BEBC.c) — T7 agent c45, S103

**Result: score 0** (147/147 ins). Checked three ways: `--try … --body` gives MATCH; the candidate object's
`objdump -drz` of the function, relocations included, is identical to the baseline
(`.run/P36/delever/baseline/…jr_8017BEBC.o`); and the candidate's whole `.text` is byte-identical to the baseline's
`.text` (cmp). The symbol table still has one `D_800AF648` entry, and no relocation names the alias.
The body has no register pin, no asm statement, no added volatile. The one non-plain construct is a body-local
**declaration alias** (`extern u8 D_800AF648_b __asm__("D_800AF648");`), which METHOD_S103 allows as a declaration
alias. A pure-C alternative that needs a change outside the body is under (c2).

## (a) The residual in one sentence
The lever-free build puts `&D_800AF648` in one pseudo that lives across the `func_8004914C` call. That pseudo takes
`$s0`, pushes `a0`'s home from `$s0` to `$s1` (the 17 `s1->s0` pairs) and adds a saved register (frame 0x40 vs 0x38).
The target instead loads `lui/addiu $a0,D_800AF648` afresh before each call. The instruction count was the same by
coincidence: 2+2 `la` in the target against 1 `la` + 2 `move` + 1 extra save/restore pair in the build.

## (b) Pass and decision (read in the source, proved on bytes)
- `calls.c:1654-1664`: a register argument whose value is not a REG and costs more than 2 is copied into a pseudo,
  because `preserve_subexpressions_p()` is true at -O2 (flag_expensive_optimizations). So each
  `func(&D_800AF648)` becomes `(set (reg P) (symbol_ref "D_800AF648")) ; (set (reg 4) (reg P))`. Seen in the `.rtl`
  dump: pseudos 83 and 84.
- cse unifies P84 with P83 because a SYMBOL_REF hashes and compares **by string pointer**: `cse.c:1937-1939`
  (`canon_hash`, which adds `XSTR (x, 0)` as an address) and `cse.c:2107-2108` (`exp_equiv_p`:
  `XSTR (x, 0) == XSTR (y, 0)`). The `.cse` dump shows insn 46 deleted and insn 48 reading `(reg 83)`. P83 now crosses
  the call, and global alloc gives it a callee-saved register.
- A declaration with an asm label gets a **freshly allocated** name string, `"*" + asmspec`: `varasm.c:479-486`
  (`make_decl_rtl`). So `&D_800AF648_b` is a SYMBOL_REF that is not equivalent to `&D_800AF648` inside cse. The two
  pseudos stay single-use, combine folds each one into `(set (reg 4) (symbol_ref))`, and each call gets its own
  `la $a0`. The assembler strips the `*`, so the relocation still names `D_800AF648` (checked: relocations identical).

## (c) The move that closed it
```c
func_8004914C(&D_800AF648);
{
    extern u8 D_800AF648_b __asm__("D_800AF648");
    func_800491AC(&D_800AF648_b);
}
```
(replaces the `$a0` pin on the first call and the `void *r4` scopes).

### (c2) Pure-C alternative, which needs a change OUTSIDE the body (proved on bytes)
Add a file-scope `static inline void set_mtx(void *m) { func_8004914C(m); func_800491AC(m); }` and call
`set_mtx(&D_800AF648);`. This gives score 0 for this function. The same TU spelling
(`../ov_SC03_102__func_80183A2C/scratch/inl2_tu.c`, one helper used by both c45 functions) also scores 0 for
func_80183A2C, and the whole `.text` is identical to the baseline (the helper is fully inlined and not emitted).
Mechanism: `integrate.c:1442-1457` maps a constant argument through `const_equiv_map`, so each use of `m` becomes
`(set (reg 4) (symbol_ref))` directly. The parameter pseudo's own set is then unused, and `jump.c:537-553`
(regscan-time deletion of a set whose register is never used) removes it before cse. cse then has no pseudo to put
back, because `$a0` is invalidated by the call. This is probably the original shape: 136 sites fleet-wide
(`git grep -c 'register void \*r4 __asm__("$4"); r4 = &D_800AF648'`) carry this pin, which fits a
SetRotMatrix/SetTransMatrix-style helper.

## (d) Generator proposal
When the diff shows `la $sN,SYM` + N × `move $aK,$sN` where the target has N × `la $aK,SYM` (an address passed to
successive calls), keep the first site as written and route each later site through its own body-local asm-label
declaration alias of SYM (`extern T SYM_b __asm__("SYM");`), or, at the TU level, turn the repeated call group into
one `static inline` helper that takes the address as a parameter. This is fleet-wide: the `$a0`-pin
`&D_800AF648` idiom has 136 sites.

## (e) What did not work
- Plain `func_8004914C(&D_800AF648); func_800491AC(&D_800AF648);`: score 38, identical to the lever-free start (cse
  merges; `.cse` dump). Cookbook §153 lists 14 further respellings that all hoist.
- The mechanical search (history.txt) best was 29, from param-width moves that do not touch the cause.

## (f) Where the method fell short
- The residual reads as a REGISTER class (`s1->s0 x17`) with an equal count, but the defect is cse unifying one
  constant (see the COUNT FIRST rule: 2+2 `la` vs 1 `la` + 2 `move` + a save pair only cancel by coincidence).
- The cookbook §153 says "this class is not reachable by respelling" and lists 14 probes. It never tried a
  declaration alias or an inline helper. That makes it a claim the bytes refuted, like the `@stuck:` notes.
- The census claim for this pair (func_8012B608 called with 4 arguments) does not apply to func_80183E3C, which does
  not call func_8012B608. See the func_80183A2C mechanism for that check.
