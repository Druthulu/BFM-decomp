# func_80188DF4 (ov_SC03_091_jr_8018326C.c) — P36 S104 agent d29

**Result: score 0, ZERO levers, plain C.** Six TUs checked (the brief said 3 copies share the text; the other three have the
same keepalive under other names in other TUs). All six come back byte-identical on the WHOLE object (`objdump -s -r` of every
section plus relocations, md5 against `.run/P36/delever/baseline/`). Negative control: `return 1` → `return 2` gives score 2 and
"object differs".

**The one non-body edit the bank needs:** the TU's file-scope prototype `extern void func_80188DF4(s32);` (line 6158) becomes
`extern s32 func_80188DF4(s32);`. `--try … --body` cannot test this because the old prototype conflicts with the new
definition (`conflicting types`), so every copy below was scored as a WHOLE-TU candidate (`--try TU FN FILE` without
`--body`). The spliced TUs are `scratch/tu_<ov>__<fn>.c`, the splicer is `scratch/splice2.py`.

## (a) The residual in one sentence
There was no residual in the body. The function RETURNS a value (`li v0,1` on the two early exits, `move v0,zero` on the
others, no reader after them in the function) and the tree declared it `void`, so a keepalive
`__asm__ volatile("" : : "r"(v0))` at `END:` was faking `return v0;`. The pack builder could not strip it (residual.txt:
`UNSTRIPPABLE … expected an asm statement`, probably because removing it leaves `END:` directly before `}`, which is not valid
C), so the pack held only residual.txt.

## (b) The pass and the decision
- In a `void` function `v0 = 1` / `v0 = 0` are dead stores. flow.c's final life pass deletes them: `insn_dead_p`
  (`flow.c:1705`), applied at `flow.c:1479-1492` (the insn becomes `NOTE_INSN_DELETED`). The asm made `v0` live to the end,
  so the stores stayed. That is the whole reason the byte oracle judged the keepalive NEEDED.
- With an `s32` return type, `return E;` goes through `c_expand_return` (`c-typeck.c:6473`) → `expand_return`
  (`stmt.c:2590`) → `expand_value_return` into `DECL_RTL (DECL_RESULT)` = `$2` (`stmt.c:2873`), and the exit keeps `$2` live
  with a USE. The same stores survive with nothing faked.
- The only caller (`func_80188304`, same TU) discards the result either way. On MIPS a discarded return value costs no
  instruction, and whole-object identity proves the caller is unchanged.

## (c) The move(s) that closed it
1. Return type `void` → `s32` (definition AND the file-scope `extern` prototype).
2. The keepalive → `return`: structured `return 1;` / `return 0;` in place of the `goto END` / `goto SET0` chain.
Byte-proven on three spellings, all score 0: (i) `body.c`, a structured `s32 *p` body in the house style of the lever-free
sibling `func_80188284` right above it in the same TU; (ii) `scratch/v_donor_struct.c`, a straight port of the lever-free
SAME-SHAPE function `func_801805C8` in `src/ov_SC03_095/ov_SC03_095_jr_8017BEBC.c:4905` (a body-local `{ s32 w0, w1; }`
struct); (iii) `scratch/v_goto.c`, the tree's own goto text unchanged except `s32` and `return v0;` in place of the asm.
So (iii) shows that move 1 alone closes it: the goto→structured rewrite is readability only.

## (d) GENERATOR PROPOSAL
When a `!FAKE: keepalive` asm `__asm__ volatile("" : : "r"(X))` is the LAST statement of a `void` function (at its final
label/epilogue) and X is assigned constants/values on every path: change the return type to `s32`, replace the asm with
`return X;`, rewrite the TU's file-scope `extern void fn(...)` prototype(s) to `extern s32 fn(...)` (keep the parameter list
exactly, including an empty `()`), and score the WHOLE TU (not `--body`), then check the callers' bytes are unchanged.
Grep: `grep -rn -B1 '^}' src/ | grep 'asm volatile("" : : "r"'`, cross-checked against definitions that start with `void`.

## (e) What did not work / was not needed
Nothing failed. The first `--try` of the ported donor with `--body` was a COMPILE-ERROR (the `extern void` prototype
conflict), not a byte difference. The first whole-TU `--try` scored 0. No allocation table and no dumps were needed: the
residual was a type, not a pass decision.

## (f) Where the method fell short
- The pack was empty apart from `residual.txt` (UNSTRIPPABLE). The pack builder should recognise an end-of-function
  keepalive in a `void` function as "missing return value" and emit the `s32` + `return X;` rewrite as body_free.c.
- None of the generator families R2–R34 can reach this. Each one works on the body text through `--body`, and the fix needs a
  file-scope prototype edit. The regen dir's 74 `free_*.c` all keep `void` (free_000 even reads the uninitialised `v0`).
- METHOD step 12 (d2/d6: "grep the WHOLE `src/` for other definitions") found it in one grep: the lever-free `s32`
  `func_801805C8` (ov_SC03_095) gave away the return type. A distinctive-literal grep (`0x40000000` + `0xE0` + `0xCC`)
  across `src/` turned up 42 definitions of this family, 6 of them carrying the same keepalive.

## (g) Structs answer
A struct is not the missing piece here. The plain `s32 *p` body (`body.c`, `p += 2`, `p[1]`) and the body-local
`struct { s32 w0; s32 w1; }` port (`p + 1`, `->w1`) produce identical bytes. Nothing in this function turns on the
aggregate-vs-scalar channel (`expr.c:4568-4577`): the only store/load pairs are `a0+0xD0`/`a0+0xE0` vs `p[0]`/`p[1]`, and
the target's order (`lw p[0]; sw 0xD0; sw 0xE0; lw p[1]`) comes out the same both ways. For documentation, the command
record is plausibly `struct { s32 flags_or_count; s32 arg; }` (bit 30 = loop back to the list head at +0xCC, sign bit = end
of list), walked by an actor pointer at +0xD0, with a countdown at +0xE0. I tested this on bytes (both spellings score 0).

## Copies table (all score 0, whole object identical to baseline)
| function | TU | body file | spliced TU | prototype change |
|---|---|---|---|---|
| func_80188DF4 | src/ov_SC03_091/ov_SC03_091_jr_8018326C.c | PACK/body.c (= scratch/ov_SC03_091__func_80188DF4.body.c) | scratch/tu_ov_SC03_091__func_80188DF4.c | `extern void func_80188DF4(s32);` → `s32` (l.6158) |
| func_80187F4C | src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c | scratch/ov_SC03_090__func_80187F4C.body.c | scratch/tu_ov_SC03_090__func_80187F4C.c | `extern void func_80187F4C(s32);` → `s32` (l.7823) |
| func_80182000 | src/ov_SC03_093/ov_SC03_093_jr_8017D898.c | scratch/ov_SC03_093__func_80182000.body.c | scratch/tu_ov_SC03_093__func_80182000.c | `extern void func_80182000(s32 a0);` → `s32` (l.4470) |
| func_80183A3C | src/ov_SC03_094/ov_SC03_094_jr_8017BEBC.c | scratch/ov_SC03_094__func_80183A3C.body.c | scratch/tu_ov_SC03_094__func_80183A3C.c | `extern void func_80183A3C();` → `extern s32 func_80183A3C();` (l.6550) |
| func_80180148 | src/ov_SC03_096/ov_SC03_096_jr_8017BEBC.c | scratch/ov_SC03_096__func_80180148.body.c | scratch/tu_ov_SC03_096__func_80180148.c | `extern void func_80180148();` → `s32` (l.4218) |
| func_80184D28 | src/ov_SC03_097/ov_SC03_097_jr_80182B9C.c | scratch/ov_SC03_097__func_80184D28.body.c | scratch/tu_ov_SC03_097__func_80184D28.c | none (already `extern s32 func_80184D28();`); `--body` works directly |

The tree line numbers are as of HEAD b27c987ba. The spliced TUs carry the rest of each TU as it stood when I scored it, so
bank from the body files plus the one-line prototype edit, not by copying the spliced TUs over the tree.
