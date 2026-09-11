# func_80034844 (src/800_b_2.c) — S104 agent e23 — CLOSED at 0, ZERO levers (1 pin -> 0)

## (a) The residual
Score 14, COUNT 27 vs 25: mine keeps THREE loop pointers (the record pointer `a0`, the decompiler's `v1 = p + 0x1A` and a
loop.c giv `v1 = a0 + 22` for the `-4` store), the target TWO (`a0` for the `lhu 0(a0)` test and one `v1 = a0 + 26` that
carries every other access: `lbu 29(v1)`, `sb -4(v1)`, `sh 0(v1)`). The `a1/a2/a3/t0/t1` shuffle is fallout.

## (b) The pass and the decision
loop.c strength reduction (the S103 c2 class): the decompiler's second walked pointer `v1` is a second BIV (stepped by
its own `+= 0x54`), so loop.c reduces `v1 - 4`/`v1 + 0x1D` addresses as givs of THAT biv and keeps both bivs — one
extra register and one extra `addiu` per iteration. With ONE walked pointer `p`, the three addresses `p+0x37`, `p+0x16`,
`p+0x1A` are givs of the single biv `p` (`record_giv` loop.c:4341) and `combine_givs` (loop.c:5494) merges them into one
reduced register (`p + 26`, the target's `v1`); `p` itself stays because it is used directly (`lhu 0(p)`, "Cannot
eliminate biv"). Bytes PROVEN; the dump reading is by analogy with S103 c2 / e16's func_80031B7C, not re-dumped.

## (c) The move that closed it (PROVEN on bytes)
Delete the second pointer `v1` and the constant locals; write the loop as a plain `for` over ONE pointer:
```c
u8 *p = (u8 *)D_800A46E8;
s32 i;
for (i = 0; i < 8; i++, p += 0x54) {
    if (*(u16 *)p == 5 && !(p[0x37] & 2)) {
        p[0x16] = 1;
        *(u16 *)(p + 0x1A) = 0x220;
    }
}
```
Also 0 (not delivered, less readable): e16's func_80031B7C shape — keep `q = p + 0x1A` and the constant locals and write
the do-while as a backward `goto` loop (no LOOP_BEG note, no loop.c, loop.c:352-361) (scratch/goto.c, first
`--try`). The structured `for` is preferred: both close, and the `for` needs no labels and no hoisted-constant locals
(loop.c's invariant motion hoists `5`, `1`, `0x220` itself).

## (d) GENERATOR PROPOSAL
When a COUNT residual inside a loop is an extra `addiu rX,rP,K` before the loop + an extra stepped register, and the body
walks a decompiler-introduced `q = p + K` alongside `p`: delete `q`, rewrite every `q[j]` as `p[K + j]` (R-family "one
biv"), and drop the constant-holding locals — a generator can do this purely textually (S103 c2, d16, d18 again).

## (e) What did not work (bytes)
- The tree's do-while with the pin removed (body_free.c, `while`): 14; the same text as `do { } while (i < 8)`: 14 —
  any structured loop that keeps `q` as its own stepped variable keeps two bivs.

## (f) Where the method fell short
It did not: METHOD step 3 (S103 c2) names this class exactly; the brief's e16 goto-loop reading (func_80031B7C) also
closes it, so this TU has two families that both reach these bytes — the one-biv `for` is the readable one.

## (g) Structs
Not needed. A 0x54-byte record type for `D_800A46E8` (u16 type @0, u8 @0x16, u16 @0x1A, u8 @0x37) would spell the four
accesses as fields of `p->` at the same `(mem (plus p K))` addresses — the same givs of the same biv, so it would compile
identically; it is a readability upgrade for the STRUCTS phase, not a decision changer.
