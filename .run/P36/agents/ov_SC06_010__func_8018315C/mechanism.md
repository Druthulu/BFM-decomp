# func_8018315C — CLOSED, score 0 (257/257, relocations identical) — T7 agent c52, S103

Same mechanism and same one-line move closed the three siblings in this TU:
func_80184394 (198/198), func_801848A4 (274/274), func_80184EFC (273/273) — see their mechanism.md.

## (a) The residual in one sentence
COUNT, two instructions missing: the target builds `&D_800AF648` twice (`lui a0 / addiu a0` before `jal func_8004914C`
AND again before `jal func_800491AC`); the lever-free text builds it ONCE into callee-saved `$s0` (`lui s0 / addiu s0`)
and copies `move a0,s0` before each call. (The `li a0,641` in the loop's delay slot and the shifted branch targets
are knock-on effects of the same two instructions.)

## (b) The pass and the decision (read in source, proven in dumps)
- `.rtl`: two separate pseudos, `(set (reg 126) (symbol_ref "D_800AF648"))` insn 279 and `(set (reg 127) (symbol_ref
  "D_800AF648"))` insn 288.
- `.cse`: insn 288 is GONE and the second call's `a0` is set from `reg 126` — cse found the second `symbol_ref` in the
  same equivalence class as reg 126 and replaced it with the cheapest valid equivalent (`cse.c:6722-6803`, "Find the
  cheapest valid equivalent"), the now-dead set was deleted (`delete_dead_from_cse`, `cse.c:8684`). reg 126 now lives
  across the call to func_8004914C → global.c gives it a call-saved register ($s0).
- Why the alias defeats it: cse hashes and compares a `SYMBOL_REF` BY THE NAME POINTER — `canon_hash`
  `cse.c:1937` (`hash += ... XSTR (x, 0)`), `exp_equiv_p` `cse.c:2107` (`return XSTR (x, 0) == XSTR (y, 0);`). A
  declaration with an asm label gets a fresh `"*D_800AF648"` name string from `make_decl_rtl` (`varasm.c:479-485`),
  so its `symbol_ref` is never equivalent to the plain one; both loads stay in `$a0`, and the assembler emits the
  same symbol (the `*` means verbatim) — relocations `R_MIPS_HI16/LO16 D_800AF648` ×2 are identical to the baseline.
  PROVEN on bytes (score 0, objdump -drz incl. relocs identical to `.run/P36/delever/baseline/...o`) and in the
  `.rtl`/`.cse` dumps (`scratch/dumps_plain/`).
- What the `$4` pin was faking: a hard register `(reg:SI 4)` is not a cse-replaceable pseudo home for a value living
  across a call, so the pinned first load stayed in `$a0` and the second was rebuilt.

## (c) The source move that closed it
Body-local declaration alias (class E), the second use only:
```c
    extern u8 D_800AF648;
    extern u8 D_800AF648_b __asm__("D_800AF648");
    ...
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648_b);
```
(the `{ void *r4; r4 = &D_800AF648; f(r4); }` blocks of body_free.c become plain calls). Nothing outside the body changes.

## (d) GENERATOR PROPOSAL
When the residual is COUNT −2 with `lui sK / addiu sK` (once) + `move a0,sK` (twice) in mine versus `lui a0 / addiu a0`
twice in the target (i.e. the same `&SYM` passed to two consecutive calls, or any `&SYM` used on both sides of a call),
rewrite the SECOND `&SYM` as `&SYM_b` and add `extern T SYM_b __asm__("SYM");` at the top of the body — and apply it
directly to every `register void *r4 __asm__("$4"); r4 = &SYM; f(r4);` pin: the tree still holds **111** such pins,
**all of them `&D_800AF648`** (`grep -rn 'register void \*r4 __asm__("\$4"); r4 = &' src`), 93 immediately followed by
the paired `func_800491AC` call — the exact shape of these four; the alias idiom is already banked lever-free at ~10
sites (e.g. src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c:5335).

## (e) What did not work / controls
- `func_8004914C(&D_800AF648); func_800491AC(&D_800AF648);` (plain, no alias): score 11, the same COUNT residual —
  the `{void *r4 ...}` blocks are irrelevant; only symbol identity matters.
- The history's 887 mechanical compiles (R5/R7/R8/R17/R18) all stayed at 11: none of them changes the `symbol_ref`'s
  identity, and cse merges it regardless of temps, blocks or order.
- Side note (not a flagged lever, left as body_free.c has it): inlining `s32 flg = 0x3000;` into
  `func_8002D4C8(0x961, (ax | 0x3000 | x) & 0xFFFF)` scores 6 (REG-caller: v1/a2/a1 permutation), so that named
  constant is load-bearing in this spelling.

## (f) Where the method fell short
Nothing — the brief's own pointer (R26/c45, the address-alias move) closed it on the first `--try`. The residual text is
unambiguous once counted: `lui s0 / addiu s0` + two `move a0,s0` versus two `lui a0/addiu a0` is the signature. The
delever oracle's `NEEDED pin $4` label hid it: the generator that R19 grew for cast arity should grow this one for
"a `$4` pin whose value is `&SYM`" — it is a symbol-identity lever, not a register lever.
