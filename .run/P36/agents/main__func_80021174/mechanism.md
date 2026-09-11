# func_80021174 (main, src/800.c) — T7 agent e10 (S104)

**Result: score 0, lever-free.** Levers 4 -> 0: the NEEDED `$2` pin on `ret`, plus the three `!FAKE: gte direct`
asm statements (extra `"memory"` clobbers) are now the shared Sony-named macros `gte_SetRotTransMatrix`,
`gte_ldlv0`, `gte_rtps` from `include/gte_inline.h`; the `p_a3` temp is gone. Signature unchanged. Whole-object
check on the `--try --keep` object: `.text`, `.data`, `.rodata` byte-equal to `.run/P36/delever/baseline/src/800.o`.

`body.c` gives the GTE results a body-local struct (`struct { s16 sx, sy; s32 flag; s32 otz; } r;` — names from what
`gte_stsxy`/`gte_stflg`/`gte_stszotz` store); the `s32 sp[4]` + `((s16 *)sp)[0]` spelling with the same control flow
(`scratch/s/u1.c`) is also 0, and a 16-byte struct (`st1.c`) too. The deciding move is the control flow:

```c
    if (r.flag < 0) {
        return 0;
    }
    lim = (s16)a0;
    if (-lim < r.sx && r.sx <= lim && -(a0 >> 16) < r.sy && r.sy <= (a0 >> 16)) {
        return 1;
    }
    return 0;
```

## (a) Residual
Every register shifted by one: the free body's compare temps took `$v0` (the target's `$v1`), `lim`/`x` took
`$a1`/`$v1` (target `$a2`/`$a1`), the reload register for the matrix pointer was `$a2` (target `$a3` — the first
never-live call-clobbered register), and the result was built in a shared cross-jumped `move v0,zero` stub plus
`j`/`xori` instead of ONE `move v0,zero` in the first range test's delay slot and `slt v0; xori v0` falling into the
epilogue. Count 67 vs 68.

## (b) Pass and decision (PROVEN on dumps `scratch/dumps_u1/` + bytes)
The target's `$v0` is the HARD return register live across the three range tests at local-alloc time, so every
block-local temp avoids it and takes `$v1` (`;; Register 84/88/94 in 3.` in `f.lreg`), which pushes `lim`/`x` to
`$a2`/`$a1` and reload's spill register to `$a3`. The tree faked that with `register s32 ret __asm__("$2")`.
The plain-C source that produces it is `if (A && B && C && D) return 1; return 0;`:
* expand gives `if (!A) goto L; … if (!D) goto L; $2 = 1; goto RET; L: $2 = 0; RET:` (the return value is set
  straight into `(reg:SI 2)` by `expand_value_return`; a `return A && B …` VALUE instead goes through a pseudo,
  expr.c:2609-2621 "Don't move directly into a return register", which is why `return A && …;` scored 19-23);
* jump1's first if-conversion (jump.c:725-830; MIPS has no SMALL_REGISTER_CLASSES, so `x` may be the hard `$2`) hoists
  `$2 = 0` to just before the FIRST condjump of the `&&` chain (it walks back over all four jumps to label L,
  jump.c:767-800) — `f.jump` insn 113 before jump_insn 66;
* the store-flag conversion (jump.c:1012-1210, `reg_set_last` finds the constant 0) turns the last `if (!D) $2 = 1`
  into `$2 = (hi >= y)` (`slt`/`xori`) — `f.jump` insn 119.
The `r.flag < 0` test must stay a separate `return 0;` (inside the chain the `$2 = 0` would be hoisted above the
flag's own load, which the target keeps in `$v0`).

## (c) Moves
1. The early-return chain `ret = 0; if (x <= -lim) return ret; … return !(a0 < y);` -> ONE `if (…&&…&&…&&…) return 1;
   return 0;` with each test written in its true sense (`-lim < x`, `x <= lim`, `-hi < y`, `y <= hi`) -> 0.
2. `a0 >> 16` written in place (a hoisted `a0 >>= 16;` = 7: it moves the shift out of the second test's delay slot).
3. Readability: gte macros by name, the stack result as a struct.

## (d) Generator proposal
When a `$2`-pinned `ret` is set to a constant and returned from several early exits and finally set to a comparison,
rewrite the exits as one `if (c1 && c2 && … && cn) return 1; return 0;` (each exit condition negated) — jump1 hoists
the hard-register clear above the chain and store-flags the last test (jump.c:725-830, :1012-1210), which is exactly
what the pin was forcing; do NOT use `return c1 && …` (expr.c:2609 routes a returned value through a pseudo).

## (e) What did not work
`return A && B && C && D` (c2) = 19 (result in a pseudo `$a2`, copied); `ret = 0; if (A && B && C) ret = D; return
ret;` (s1) = 17 (same: `ret` is a global pseudo, local temps grab `$v0` first); `if (sp[1] >= 0) {…}` nesting (s2) =
35; `||` of the failing tests (s5) = 34; the tree's early returns with an unpinned `ret` (s8) = 35; `ret` widths
u8/s8/u16/s16/u32 = 17-20 (`scratch/t/`).

## (f) Where the method fell short
Step 15 (d27) says "a pinned RESULT local `r = 0; if (A) r = (B); return r;` -> return constants `if (A && B) return 1;
return 0;`" — this is the same crack; it applied here with a four-term chain and the first exit kept separate. The
residual's register permutation (every register off by one) is the signature to key on: a hard register occupied
across blocks at local-alloc time, not a priority question — `alloc_table.py` would not have shown it.

## (g) Structs
Tested on bytes: a body-local struct for the GTE output (`sx, sy, flag, otz`) instead of `s32 sp[4]` + `(s16 *)`
casts compiles to the same bytes (12- and 16-byte versions both 0). It did not change any pass decision here — the
lever was the return-register lifetime (jump1), not an aggregate/scalar memory dependence; the struct is readability.
