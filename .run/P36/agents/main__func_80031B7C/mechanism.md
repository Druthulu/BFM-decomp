# func_80031B7C (src/800_b_2.c) — S104 agent e16 — CLOSED at 0, ZERO levers (1 pin -> 0)

## (a) The residual
Score 18, COUNT, 27 vs 25. Mine keeps TWO loop registers for the record pointer — the walked pointer (used by the
`sh` at offset 0) and a second one `addiu v1,a0,2` that carries the `+2/+3/+4` byte reads and the `sb` — and steps
both; the target walks ONE pointer `$v1` with every access an offset from it (`lbu 4/2/3(v1)`, `sb 2(v1)`, `sh 0(v1)`).
The counter/constant register shuffle (`a0/a2/a1` vs `a1/a3/a2`) is fallout of the extra pseudo.

## (b) The pass and the decision (PROVEN on the `.loop` dump, scratch/dumps_free)
loop.c strength reduction. The `-dL` dump of the lever-free do-while says:
`Cannot eliminate biv 75: biv used in insn 44.` (the pointer, used directly by `*(u16 *)v1 = …`) and
`giv at 41 reduced to (reg:SI 84)` with the givs at 34/29/24 combined into it — the `p+2` address giv
(`record_giv` loop.c:4341, `combine_givs` loop.c:5494) gets its own register while the biv stays live.
The tree's `$3` pin worked because loop.c never treats a hard register as a biv. The target was never strength-reduced
at all: it was not a LOOP to loop.c. `loop_optimize` counts `NOTE_INSN_LOOP_BEG` notes and returns when there are none
(loop.c:352-361, "Don't waste time if no loops"); those notes come only from `expand_start_loop` (stmt.c:2171), i.e.
from `for`/`while`/`do`. A backward `goto` emits no note. The constants `1` and `0x7FFF` sit in registers set before the
loop in the target — with no loop.c there is no invariant motion, so the source itself held them in locals (a body with
the constants written inline at the stores scores 10: they are materialised inside the loop).

## (c) The move that closed it (PROVEN on bytes)
The do-while written as the backward `goto` loop it compiles like:
```c
void func_80031B7C(void) {
    s32 i = 0;
    s32 one = 1;
    s32 full = 0x7FFF;
    u8 *p = D_800A49D2;

loop:
    if (p[4] && !p[2] && p[3]) {
        p[2] = one;
        *(u16 *)p = full;
    }
    p += 0x54;
    i++;
    if (i < 8) goto loop;
}
```
Also byte-neutral (all tested at 0): the decompiler names `a0/a2/a1/v1` renamed; `u8 a2`/`u16 a1` widened to `s32`
(the stores truncate either way); `()` -> `(void)` (the TU's own prototype at src/800_b_2.c:2049 is `(void)`).
`if (++i < 8) goto loop;` with the pointer declared first scores 4 (ORDER) — keep `i++;` as its own statement.

## (d) GENERATOR PROPOSAL
When a COUNT residual inside a loop is an extra `addiu rX,rP,K` before the loop plus a second stepped pointer, and the
`-dL` dump says "Cannot eliminate biv" for the pointer, AND the target hoists nothing that the source does not already
hold in a local, rewrite the `do { … } while (c);` as `label: … if (c) goto label;` — no LOOP_BEG note, no loop.c
(loop.c:352-361). The tell in the tree: a `$N` pin on the walked pointer of a do-while whose "constants" are locals
initialised at the top (the decompiler's rendering of registers loaded before a non-loop.c loop).

## (e) What did not work (bytes)
- Every structured spelling keeps loop.c: a `for` with inline constants 17, `D_800A49D2[i * 0x54 + K]` indexing 21
  (three givs), `while (1) { … if (i >= 8) break; }` 18 (still a loop note), the sweep's best (do-while block) 15.
- The goto loop with `1`/`0x7FFF` inline at the stores: 10 (COUNT 24 — no loop.c means no hoisting, so the constants are
  rematerialised in the body).

## (f) Where the method fell short
METHOD §14 says "goto chain -> STRUCTURED" (four closes); this one is the INVERSE — a structured loop that the original
wrote as a backward goto. No generator emits a goto loop, and the `.loop` dump's "Cannot eliminate biv" line is the
only place that points at it; the reading "the target has NO loop optimisation at all" (no hoisting, no reduction)
is the check that distinguishes it from the S103 c2 `q = p + k` case.

## (g) Structs
No. Giving `D_800A4988` its 0x54-byte record type (u16 @0x4A, u8 @0x4C/0x4D/0x4E) would not remove the biv's direct use
(the u16 field at the pointer's own offset) nor the loop note; the decision is loop.c's biv elimination, not an
aggregate/scalar alias question. Byte-wise a struct pointer would also have to start at `D_800A49D2` (the relocation's
symbol) to stay identical before linking.
