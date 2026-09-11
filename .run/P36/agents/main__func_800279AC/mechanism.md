# func_800279AC (main, src/800.c) — T7 agent e25 (S104)

**Result: score 0, lever-free** (no pin, no launder, no barrier, no volatile, no do-while, no goto). Levers 2 -> 0 (the
NEEDED `"=r"(prim) : "0"(prim)` launder and the NEEDED `"memory"` barrier before the OT link). Signature unchanged. The
only asm is the TU's Sony GTE macros. No other copy of the class exists (`grep` over `src/`).

```c
LineG4 *func_800279AC(SrcQ *src, Vtx8 *vb, s32 unused, LineG4 *prim, s32 n, s32 shift, u32 *ot)
{
    struct { s32 flag, otz, sz0, sz1, sz2, sz3; } g;
    LineG4 *p = prim;
    s32 m, k;

    for (; n != 0; n--, src++) {
        ... (the tree's loop, with flag/otz/sz[i] -> g.flag/g.otz/g.szi and prim -> p; see body.c)
    }
    return p;
}
```

## (a) Residual
Free body: 26, same count (145) — `prim` and its `+4` giv swapped (`t1`/`a3` vs the target's `a3`/`t1`, 15 register
pairs) and the `otz` reload (`lw a0,4(sp)`) hoisted into the `prim->rgb0` chain (the target finishes `sw v1,0(t1)`
before loading `otz`). The sweep's best (R10 param copy) = 11: only the `otz` hoist left.

## (b) Passes and decisions — two, one per lever
1. **loop.c takes the biv's initial value from a HARD register** (the launder's own comment had it right): the backwards
   search from `loop_start` (`loop.c:3453-3463`, stopping at the first label) finds the parameter copy `(set prim (reg
   $a3))` through `record_initial` (`loop.c:6327`); `valid_initial_value_p` accepts a call-used hard register when no
   call intervenes (`loop.c:4120-4146`), so `bl->initial_value = (reg $a3)` (`loop.c:3509`) and the `+4` giv is
   initialised from `$a3` itself; `$a3` then lives past the copy, conflicts with `prim`'s pseudo, and the two swap.
   With `LineG4 *p = prim;` walking the loop the biv is `p`, its initial value is `prim`'s PSEUDO: `.loop` dumps —
   `dumps_s2` (no copy) "Biv 75 initialized at insn 10: initial value (reg:SI 7 a3)"; `dumps_s1` (copy) "Biv 79
   initialized at insn 23: initial value (reg/v:SI 75)". PROVEN (dumps + bytes: 26 -> 11; with the struct 17 -> 0).
2. **sched1's struct-vs-scalar alias exception** (`true_dependence`, `sched.c:817-839`): the `prim->rgb0` store is a
   `MEM_IN_STRUCT` SImode reference at a varying address, the scalar `otz` load `(mem:SI (plus $fp 4))` is
   non-struct at a fixed address -> "can never conflict" (`sched.c:834-836`) -> the load is hoisted above the store
   (`dumps_pc1/pc1.i.sched`: insn 248, the `otz` load, carries NO link to store 244 and sits above it). With the GTE
   scratch words in one local struct, `g.otz` is `(mem/s:SI (plus $fp 4))` (`expr.c:4568-4577`), the exception no
   longer applies, `memrefs_conflict_p` cannot separate `$fp+4` from a register base, and the load keeps a true
   dependence on the store (`dumps_s1/s1.i.sched`: insn 240 `(mem/s:SI …4)` with `insn_list 236`, the rgb0 store).
   PROVEN (dumps + bytes: 11 -> 0 in `scratch/s1.c`).

## (c) Moves (joint; each alone leaves 11 / 17)
1. `s32 flag; s32 otz;` + the block-local `s32 sz[4];` -> one `struct { s32 flag, otz, sz0, sz1, sz2, sz3; } g;` — the
   layout the target's frame already shows (flag 0, otz 4, sz 8-20), and the SAME declaration the TU's lever-free
   siblings func_80027D20 (`src/800.c:18185`), func_80027F4C (`:18244`) and the one at `:16526` already carry.
2. the launder -> `LineG4 *p = prim;` walked by the loop (`p->…`, `p++`, `return p;`).

## (d) Generator proposal
When a `"memory"` barrier separates a struct-field store through a pointer from a reload of an address-taken scalar
local (a GTE `gte_stotz(&otz)` slot), gather the address-taken scalars into one body-local struct in frame order
(`struct { s32 flag, otz, sz0…; } g;`); when a launder `"=r"(p) : "0"(p)` re-ties a pointer parameter that a loop walks,
walk a local copy of the parameter instead (`T *q = p;` — the biv's initial value becomes a pseudo, `loop.c:3509`).

## (e) What did not work
`scratch/pc1.c` (the param copy, scalar `otz`) = 11; `scratch/s2.c` (the struct, no param copy) = 17. Not tried: a
cast scalar store `*(u32 *)((u8 *)p + 4) = …` for rgb0 (it would also defeat the exception — both non-struct — but is
the less natural spelling and the struct closed first).

## (f) Where the method fell short
Steps 1-16 have the aggregate-vs-scalar channel for a TABLE READ (S103 c11, `p[i]` vs a cast) but not for a stack
scratch SLOT: "a scalar local whose address is passed to an asm macro reloads ahead of a struct store — put the
address-taken locals in one struct" is worth a line. grep-ing the TU for the other functions that call the same GTE
macros (`gte_stsz4`, `gte_stotz`) found the struct `g` in three siblings in one command.

## (g) Structs
**Yes — here the struct IS the close.** Which: the GTE scratch block `struct { s32 flag, otz, sz0, sz1, sz2, sz3; }` (a
local; the TU spells it three more times — a shared typedef for the struct phase). Why: `true_dependence`'s exception
(`sched.c:834-836`) frees a scalar fixed-address load from a struct store; making the load a struct field (`/s`,
`expr.c:4568-4577`) keeps the dependence the barrier faked. `LineG4`/`SrcQ` were already structs. Tested on bytes with a
body-local declaration: 11 -> 0.
