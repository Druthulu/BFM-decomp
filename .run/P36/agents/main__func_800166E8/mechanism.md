# func_800166E8 (main, src/800.c) — T7 agent e15 (S104)

**Result: score 0, lever-free** (no pin, no asm, no volatile, no do-while, no goto, no dead array). Levers 2 -> 0 (the
NEEDED `$2` pin and the NEEDED `__asm__ volatile("")` barrier), and the dead `s32 local_buffer[2]` frame pad is gone
too. Whole-object check on the `--try --keep` object: `.text` (101,572 bytes), `.data`, `.rodata` byte-equal to
`.run/P36/delever/baseline/src/800.o`.

```c
void func_800166E8(void *a0, int a1) {
    u8 *p = a0;

    while (a1-- != 0) {
        *p++ = 0;
    }
}
```
The parameter's type changes spelling from `s32` to `int` — the same type (`include/common.h:21 typedef int s32;`),
so the ABI and every caller are unchanged (no caller in `src/`); it is not a signature change in C terms. If the
project prefers to keep `s32 a1`, `scratch/w4.c` (`u32 n = a1; while (n-- != 0)`) and `scratch/x1.c`
(`int n = a1;`) are also 0; `scratch/w2.c` (`u8 *a0, u32 a1` — a bzero signature) is 0 but a real signature change.

## (a) Residual
The tree's text was the decompiler's rotated loop (`if (a1 == 0) goto skip; v0 = a1 - 1; v1 = -1; do {...} while
(v0 != v1);`) with `v0` pinned to `$2` and a barrier; unpinned, the counter is tied to `$a1` (`addiu a1,a1,-1`,
`bne a1,v0`) where the target keeps `a1` intact and counts in `$v0` against `-1` in `$v1`. Score 6, 11 = 11.

## (b) Pass and decision (PROVEN on bytes + dumps `scratch/dumps_w4/`, `scratch/dumps_w5/`, `scratch/mini/`)
1. **fold's post-decrement rewrite** (`fold-const.c:4399-4413`): `n-- != 0` becomes `--n != -1` — the target's
   shape exactly (`addiu v0,a1,-1` as the new counter, compare with `-1` in `$v1`, the entry test `a1 == 0` after
   combine). It fires only when the comparison's operand IS the `POSTDECREMENT_EXPR`; comparisons strip only
   same-type-node NOPs (`STRIP_TYPE_NOPS`, `fold-const.c:3146-3150`). With a `s32` counter the operand arrives wrapped
   in a conversion between the typedef variant and `int` (`c-convert.c:68-69` builds a NOP_EXPR whenever the main
   variants agree but the nodes differ) and the rewrite does not fire: `.jump` shows `77 = n; n = n - 1; if (77 == 0)`
   (dumps_w5) — a saved copy, the free sweep's shape. With `int n` or `u32 n` it fires (dumps_w4: `n = n - 1;
   78 = -1; if (n == 78)`). Byte-proven in isolation, `scratch/mini/m3.c`: `void a(u8 *p, s32 n)` vs
   `void b(u8 *p, int n)`, identical text otherwise — frame 0 / 7 ins vs frame 8 / the target's 11. Which front-end
   routine adds the NOP is NOT traced (`(s32)0` on the literal, `scratch/x4.c`, still fails, so it is not only
   `common_type`'s int-over-typedef choice, c-typeck.c:296-301; `shorten_compare` lives in c-common.c, not in
   `tools/reference/`).
2. **The 8-byte frame without any local** (PROVEN on `dumps_w4/w4.i.combine` + `.lreg`): combine merges insns 47
   (`n = n - 1`), 48 (`78 = -1`), 49 (`if (n == 78)`) into a split pair (`75 = a1 - 1`; `if (a1 == 0)`); the dead
   constant pseudo 78 keeps its counts (`combine.c:2306`, newi2pat case — e10's func_80020598 mechanism), `.lreg`:
   `Register 78 used 2 times across 2 insns in block 0; dies in 0 places; ST_REGS or none` — no hard register, so
   reload gives it a stack slot (`reload1.c:2331-2352`): `addiu sp,sp,-8`. The tree's `s32 local_buffer[2]` was
   compensating for exactly this slot (with both, the frame is 16: `scratch/v8.c`, score 2).

## (c) Moves
1. The goto + do-while text -> `while (a1-- != 0) *p++ = 0;` (structured, S104 step 14).
2. The counter typed `int` (or `u32`), not `s32` — joint with 1; `s32` = 9 (`scratch/w5.c`).
3. Delete `s32 local_buffer[2];` (the phantom slot of 78 supplies the frame) — joint with 1+2; kept = 2.

## (d) Generator proposal
When a lever-free body is a rotated count-down loop (`if (n == 0) goto out; v = n - 1; do {...; v--;} while (v !=
-1);`), rewrite it as `while (n-- != 0) {...}` with the counter declared `int` (or `u32`) — a `s32`-typedef counter
blocks fold's `n-- != C` -> `--n != C-1` rewrite (`fold-const.c:4399`) — and drop any dead `pad[]` whose size equals
the phantom constant slot combine leaves (`combine.c:2306`).

## (e) What did not work
`scratch/v1.c`-`v7.c`: `while (a1-- != 0)` on the `s32` param (9), a `s32 n` copy (7), `for (n = a1; n != 0; n--)`
(6), the decompiler's `if/do-while` without pins (9), `while (v0 != -1)` (5); `scratch/v8.c` `u32` with the dead
array kept (2, frame 16). The sweep's 98 compiles (width/inline/swap/decl moves) all stayed at 6: no generator
rewrites a do-while into a `while (n--)` or changes `s32` to `int`.

## (f) Where the method fell short
The residual looked like a register lever (a1 vs v0) but the decision was a TREE-level fold before RTL exists; no
step names fold-const.c. Worth adding: "a count-down loop compared with `-1` in the target = `while (n-- != 0)`
folded; the typedef of the counter matters (`int`/unsigned yes, `s32` no)". A tool that greps the project for
`s32 n; while (n-- ...)` bodies still carrying levers would find siblings.

## (g) Structs
No. There is no aggregate access; the deciding facts are a tree fold (the counter's type node) and combine's
phantom pseudo. Typing `a0` as a struct pointer would not touch either.
