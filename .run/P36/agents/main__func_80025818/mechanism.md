# func_80025818 (main, src/800.c) — T7 agent e15 (S104)

**Result: score 0, lever-free** on the FIRST `--try` (no pin, no asm except Sony's GTE macros, no volatile, no
do-while added). Levers 1 -> 0 (the NEEDED `__asm__ ("" : "=r"(poly) : "0"(poly))` launder). Signature unchanged.
Whole-object check on the `--try --keep` object: `.text` (101,572 bytes), `.data`, `.rodata` byte-equal to
`.run/P36/delever/baseline/src/800.o`.

The move: walk a local copy of the output pointer instead of the parameter.
```c
    PG3 *p;

    p = poly;
    if (n != 0) {
        do {
            ... every `poly` below is `p` ...
        } while (n != 0);
    }
    return p;
```

## (a) Residual
Free body: 135 vs 134 — one extra `move t5,a0` at entry and `$a3`/`$t1` swapped for the whole loop: the target keeps
the output pointer in `$a3` (its own parameter register) and the `poly + 4` giv in `$t1` (`addiu t1,a3,4`); the free
body copies the pointer to `$t1` and steps the giv in `$a3` (`addiu a3,a3,4`).

## (b) Pass and decision (PROVEN on dumps `scratch/dumps_free/`, `scratch/dumps_p1/` + bytes)
loop.c's biv initial value (`record_initial`, `loop.c:6327`; `valid_initial_value_p`, `loop.c:4120-4150` — a hard
register is valid unless call-clobbered AND a call was seen). With the parameter itself as the biv, `.loop` says
`Biv 75 initialized at insn 10: initial value (reg:SI 7 a3)`, so strength reduction builds the giv's preheader init
from the HARD `$a3` (`giv = $a3 + 4`), which keeps `$a3` live past the parameter copy: the pointer's pseudo then
conflicts with `$a3` and global cannot put it there (the extra `move`). With `p = poly;` the biv is the local:
`Biv 82 initialized at insn 23: initial value (reg/v:SI 75)` — the parameter's PSEUDO — so the giv init reads the
pseudo, `$a3` dies at the parameter copy, and the pointer pseudo is tied back into `$a3`. The launder did the same
thing by making the initial value an `asm_operands` that `valid_initial_value_p` rejects (the tree comment's own
reading, now reached with an ordinary local).

## (c) Move
`PG3 *p; p = poly;` above the `if (n != 0)` guard and `p` for `poly` everywhere after it, `return p;` — the text of
the same-TU byte-twin **func_80024DE8** (src/800.c:15767, `u8 *pkt2 = pkt;`), which is identical to this function's
object code except the prim stride (24 vs 28) and two field offsets (4 words differ of 134; found by diffing the
target's instruction sequence against every function in `800.o`, `scratch/base.dis`, ratio 1.000).

## (d) Generator proposal
When a `"=r"(p) : "0"(p)` launder sits on a pointer PARAMETER that a loop walks (a biv), replace it with a local copy
`T *q = p;` walked instead of the parameter — loop.c then records the biv's initial value as the parameter's pseudo,
not its hard register (`valid_initial_value_p`, `loop.c:4120`), and the giv initialisation no longer extends the
hard register's life; and always diff the target's bytes against every same-TU function first (e10's rule — here the
twin's text closed it with no reasoning).

## (e) What did not work
Nothing else was needed. The sweep's 323 compiles (swap/block/do-while moves) all stayed at 23; `history.txt`
shows no R10 (param-copy) candidate among the best-scoring moves for this function, so whether R10 ran on `poly`
and how it placed the copy is not known from the pack (not investigated).

## (f) Where the method fell short
Nothing: the related-bodies list names the D_800A2B78 siblings but not func_80024DE8 by shape; a mnemonic-sequence
diff against every function in the baseline object (a 20-line script) finds the twin at ratio 1.0. Also: the twin's
comment block still describes an asm "identity no-op" that its body no longer contains — a stale comment; the
`p = poly` copy is what the twin actually uses.

## (g) Structs
No. `poly` is already a `PG3 *` struct pointer and `prim` a struct; the decision is loop.c's biv initial value (a
parameter hard register vs a pseudo), which no aggregate type touches.
