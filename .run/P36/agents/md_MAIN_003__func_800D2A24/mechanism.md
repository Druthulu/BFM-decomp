# func_800D2A24 — score 0, ZERO levers, but a SIGNATURE change (PARKED per METHOD step 15 d29 / Drew S104 (d))

(a) Residual (start 4, COUNT): the target sets `$v0` on both exits (`move v0,zero; j <epilogue>` / `li v0,1`); a `void` body cannot
    emit them, so the tree used a `$2` pin + two keepalive asms.

(b) The function RETURNS s32 (1 = stream marker byte `*p & 0x10` seen, 0 = `CdRead2` failed). The TU's own forward declaration at
    `src/md_MAIN_003/md_MAIN_003_jr_800D1E18.c:338` is `extern void func_800D2A24();` (its sole caller func_800D2454 discards the
    result), so the `void` definition was forced by `conflicting types`. Nothing in any pass is at issue: it is `return 1;`/`return 0;`
    in an `s32` function (expand_return → `$v0`), exactly the header comment's own diagnosis.

(c) Move: `s32 func_800D2A24(s32 a0)` with `return 1;` in the `if (*p & 0x10)` arm and `return 0;` at the end; the retry/for/goto
    shape kept as the tree has it. REQUIRES line 338 to become `extern s32 func_800D2A24();` (the K&R `()` stays). Proven on bytes
    through a whole-TU `--try` (`scratch/tu_sig.c` = the tree's TU with that one extern edited and this body spliced): the function
    scores 0, the caller func_800D2454 scores 0, and the whole object's disassembly+relocs are identical to the baseline
    (`diff` of the two `objdump -drz` outputs is empty apart from the file names).
    NOT proven / not attempted: a plain-C `void` spelling — none exists; the bytes ARE a return value.

    Tried first: the same body as nested `do { p = …; do { … } while (r == 0); } while (CdRead2(…) == 0);` — score 12: the
    structured loop lets loop.c hoist `p = D_800EC9E8` and swaps `$s0/$s1`; the goto/`retry:` text is the target's shape.

(d) GENERATOR PROPOSAL: a `void` function whose lever set is exactly {`register v0 __asm__("$2")`, keepalive-of-v0 before each
    `return`} is an `s32` function: rewrite each `v0 = K; asm; return;` to `return K;`, change the return type, and edit the TU's
    (or the header's) forward declaration to match — a signature-change class the bank must be told to accept (R-rule pending).

(e) Nothing else tried; the class is closed by the type.

(f) Method: `--try --body` cannot test a signature change (the extern lives outside the body span); a whole-TU candidate file
    (`--try TU FN FILE` without `--body`) can, and the caller can be scored from the same file — worth a line in PROMPT.md.

(g) STRUCTS: no struct question here (one global pointer `D_800EC9E8`, no pass decision involved). Levers 3 → 0, at the price of one
    declaration line outside the body (line 338).
