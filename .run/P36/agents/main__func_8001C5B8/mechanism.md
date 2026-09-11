# func_8001C5B8 (main, src/800.c) — T7 agent e20 (S104)

**Result: score 0, lever-free** on the first `--try` of the port (no pin, no asm, no volatile, no do-while added).
Levers 2 -> 0 (the NEEDED `$17` pin on `obj` and the NEEDED `"=r"(entry) : "0"(entry)` launder). Signature unchanged.
Whole-object check on the `--try --keep` object: `.text` (101,572 bytes), `.data`, `.rodata` byte-equal to
`.run/P36/delever/baseline/src/800.o` (`scratch/cmpobj.sh`).

This function is the byte-twin of **func_8001C320** (same TU, closed by me in this batch,
`.run/P36/agents/main__func_8001C320/mechanism.md`): identical text except the constant stored at `obj + 2` (8 vs 1 —
the target's extra `li v0,8`, 75 vs 74 instructions) and `GsMapModelingData`'s declared parameter (`unsigned long *`).
The residual printed here is the same 24 hunk-for-hunk.

```c
    unsigned long *tmd;
    ...
    ((void (*)(s32))func_8001C9D0)(a0);
    *(u16 *)a0 = 1;
    *(u16 *)(a0 + 2) = 8;
    ...
                tmd = (unsigned long *)(*(s32 *)a1 & 0x80FFFFFF);
                tmd++;
                a1 += 4;
                GsMapModelingData(tmd);
                ...
                GsLinkObject5(tmd + 2, ...);
```

## (a) Residual
As func_8001C320: `obj`/`a1` swapped between `$s2`/`$s1` (and the loop's hoisted mask with them), and `entry + 4` not
materialised (the free body passes `s0 + 4` / `s0 + 12`, the target `s0` / `s0 + 8`). COUNT 74 vs 75.

## (b) Passes and decisions (proven on func_8001C320's dumps; the two bodies compile identically modulo the constant)
1. cse's re-association (`fold_rtx`, `cse.c:5582-5665`) folds `entry + 8` through the and-result's own pseudo to
   `+ 12`, leaving `entry` single-use for combine; `tmd = x & mask; tmd++;` (one variable set twice) gives cse no
   second register to re-associate through.
2. `allocno_compare` (`global.c:594-607`): the object parameter at 7 refs ranks below `a1`; passing it to
   `func_8001C9D0` (whose body stores through `$a0`) adds a ref at zero bytes, 7 -> 8 crosses `floor_log2`, and the
   object takes `$s1`.

## (c) Moves (joint, the func_8001C320 port)
1. `entry = (x & 0x80FFFFFF) + 4;` -> `tmd = (unsigned long *)(x & 0x80FFFFFF); tmd++;`, `entry + 8` -> `tmd + 2`.
2. `func_8001C9D0();` -> `((void (*)(s32))func_8001C9D0)(a0);`, `obj` -> `a0`.

## (d) Generator proposal
Diff every closed body's object code against the TU's still-open functions and port the closed TEXT to any function
whose instruction sequence differs only in immediates (here one `li` constant): e10's/e15's same-TU-twin rule, applied
to twins closed in the SAME batch.

## (e) What did not work
Nothing else was needed. The sweep's best 11 (`R12 width obj s32->s16`) is a compensating width change.

## (f) Where the method fell short
Nothing: the pair was visible in the residuals (identical hunks) before any dump.

## (g) Structs
Same answer as func_8001C320: the object (`+0x00/+0x02/+0x2E` u16, `+0x20/+0x24` pointers, `+0x30` coordinate block)
and the `D_800AF630` state block (`+0x198`, `+0x19C`) would read better as structs, but neither deciding pass (cse
re-association through a register, the allocno ref count) involves an aggregate access.
