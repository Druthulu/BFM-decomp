# func_8001C320 (main, src/800.c) — T7 agent e20 (S104)

**Result: score 0, lever-free** (no pin, no asm, no volatile, no do-while added). Levers 2 -> 0 (the NEEDED `$17` pin on
`obj` and the NEEDED `"=r"(entry) : "0"(entry)` launder); the REMOVED `$19`/`$20` pins were already gone. Signature
unchanged. Whole-object check on the `--try --keep` object: `.text` (101,572 bytes), `.data`, `.rodata` byte-equal to
`.run/P36/delever/baseline/src/800.o` (`scratch/cmpobj.sh`).

The decisive text (`body.c` = `scratch/e/T1.c`):
```c
    u32 *tmd;                                   /* was s32 entry */
    ...
    ((void (*)(s32))func_8001C9D0)(a0);         /* was func_8001C9D0(); + `obj = a0;` */
    *(u16 *)a0 = 1;                             /* every obj -> a0 */
    ...
            do {
                tmd = (u32 *)(*(s32 *)a1 & 0x80FFFFFF);
                tmd++;                          /* skip the TMD ID word (Sony's sample: dop++) */
                a1 += 4;
                GsMapModelingData(tmd);
                ...
                GsLinkObject5(tmd + 2, ...);    /* skip flags + nobj */
```

## (a) Residual
Free body: 24, COUNT 73 vs 74 — `obj` (a0) and `a1` swapped between `$s2`/`$s1` for the whole function (the loop's
hoisted `0x80FFFFFF` mask, which re-uses the dead `obj` register, swapped with them), and the loop's `entry + 4` was not
materialised: the target keeps `s0 = (x & mask) + 4` across `GsMapModelingData` and passes `s0` / `s0 + 8`; the free body
keeps `s0 = x & mask` and passes `s0 + 4` / `s0 + 12`.

## (b) Passes and decisions (PROVEN on spliced-TU dumps `scratch/dumps_free/`, `dumps_A/`, `dumps_T1/` + bytes)
1. **cse's re-association of the second use** (`fold_rtx`, `cse.c:5582-5665`: `(plus R C1)` with R known as
   `(plus R0 C2)` becomes `(plus R0 C1+C2)`). With `entry = (x & mask) + 4` the and-result has its own pseudo 87 and
   `entry + 8` is folded to `(plus (reg 87) 12)` (`free.cse.txt` insn 104); `entry` is left with one use (the call
   argument) and combine merges it into the `$a0` copy -> `addiu a0,s0,4` + `addiu a0,s0,12`. Written as two
   assignments to ONE variable (`tmd = x & mask; tmd++;`) the add's operand is the variable's own old value, whose
   expressions cse invalidates when the variable is re-set, so `lookup_as_function` finds nothing: `A.cse.txt` insn
   keeps `(plus (reg/v 77) 8)` — the target's `move a0,s0` / `addiu a0,s0,8`. (19 with this alone: count now 74 = 74.)
2. **allocno priority crossing a power of two** (`allocno_compare`, `global.c:594-607`: `floor_log2 (refs) * refs /
   live`). `alloc_table.py A`: `obj` r72 refs 7, live 19, priority 7368 < `a1` r73 refs 12, live 47, 7659 -> `a1` is
   allocated first and takes `$s1`. Passing the object to `func_8001C9D0` — which really takes it: its body stores 17
   fields through `$a0` (`objdump func_8001C9D0`), and the TU's siblings func_8001C8C4 (src/800.c:9440) and
   func_8001C6E4 call it the same way `((void (*)(s32))func_8001C9D0)(a0)` — adds ONE ref at zero bytes (`$a0` already
   holds it): refs 8, live 20, `floor_log2` 2 -> 3, priority 12000 > 7500 (`alloc_table.py T1`), so the object gets
   `$s1` and `a1` `$s2`. Neither move alone closes: move 2 alone = 6 (`scratch/e/G0.c`), move 1 alone = 19 (`A.c`).
   `obj` kept as a copy of `a0` with the call passing `obj` is also 0 (`E.c`); body.c drops the copy (d24).

## (c) Moves (joint)
1. `entry = (x & 0x80FFFFFF) + 4;` -> `tmd = (u32 *)(x & 0x80FFFFFF); tmd++;` and `(u32 *)(entry + 8)` -> `tmd + 2`
   (the Sony TMD-walk idiom: skip the ID word, map, link the object table after flags + nobj).
2. `func_8001C9D0();` -> `((void (*)(s32))func_8001C9D0)(a0);` (the callee's real argument, as two same-TU siblings pass
   it) and `obj` replaced by `a0`.

## (d) Generator proposal
When the target materialises `v = e + K` in a register and uses `v` and `v + K2` but yours passes `e + K` / `e + K+K2`
(a missing add + a re-folded offset), split the initialiser into `v = e; v += K;` (cse re-associates only through a
DIFFERENT pseudo, `cse.c:5582`); and when a parameter-vs-parameter callee-saved swap has the loser at refs `2^k - 1`,
pass it to a call that really takes it (a `(void)`-declared callee whose body reads `$a0`) — one ref crosses
`floor_log2` (`global.c:594`).

## (e) What did not work
`B`/`C`/`D` (the and/add split in other orders, `a1 += 4` between) = 19, like `A`: all fix the count only. `F` (`a0`
direct, no call argument) = 19 and `H` (`obj = a0;` after the call) = 19: neither adds a ref. The sweep's best 10
(`R12 width obj s32->u16 + R9 swap`) was a width change on the object pointer — compensating errors, not a spelling.

## (f) Where the method fell short
Nothing major: S103 c10 ("pass the parameters through to a callee at its REAL arity") and d24 are this crack; what
made it quick was reading the CALLEE's bytes (`func_8001C9D0` stores through `$a0`, so its `(void)` prototype is
wrong) and the TU siblings that already cast-call it with `a0`. Worth a generator: for every call to a `(void)`
function whose body reads `$a0`-`$a3` before writing them, propose the cast-call with the caller's live value.

## (g) Structs
Plausible but not needed: `obj` is a GsCOORDINATE/object block (`+0x00`/`+0x02` u16 flags, `+0x20` `+0x24` pointers,
`+0x2E` u16, `+0x30` a GsCOORDINATE2 passed to func_80052D90/func_80054514) and `work` is the `D_800AF630` state block
(`+0x198` pointer, `+0x19C` u16 counter). Field accesses would not change either decision (cse's re-association of a
REGISTER sum and the allocno ref count); `tmd` as `u32 *` is already the pointer type the TMD idiom wants. The
parameter type `s32 a0` stays (a struct pointer parameter would be a signature change — parked for the struct phase).
