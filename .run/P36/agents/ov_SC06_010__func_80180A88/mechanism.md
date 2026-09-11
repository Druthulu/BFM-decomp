# func_80180A88 (ov_SC06_010_jr_8017A4AC.c) — T7 e14, P36 S104

**Score 0, ZERO levers** (free start 98 = regen best 98). Tree levers: 1 pin ($16 on `p`) -> 0 (the `q` $6 pin was
already REMOVED). No copies elsewhere (`p - 0x2A`, `func_8017F098(0xA) + 0xB00` occur only in this TU).

The move (case 1 only; case 0 untouched): each of the 12 object set-ups gets its OWN block-scoped pointer, and the
comma-expression argument becomes two statements:
```
        {
            s16 *p = &D_801B25CC;
            s32 *obj;

            *p = func_8017F098(0) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_801968BC, (s32)obj);
        }
        … ×12
```
(the function-scope `s16 *p; s16 *q;` deleted; the calls use the TU's own prototypes, no casts of the callee).

## (a) The residual
411/411 instructions; a pure `$s0`/`$s1` swap across case 1 (98 = 96 + 15 register pairs): the target keeps each block's
object pointer `p` in `$s0` and the shared `&D_801B2C10` (first argument of all 12 `func_8017CAD4` calls, materialised
once) in `$s1`; the free body has them the other way round.

## (b) The pass and the decision (dumps under scratch/dumps_free, dumps_tree, dumps_c4)
local-alloc's eligibility test, `local-alloc.c:470-477`: only a pseudo that lives in one basic block AND dies exactly once
(`reg_n_deaths[i] == 1`) gets a quantity. Case 1 is one basic block (calls do not end blocks in 2.7.2 flow). Free
`.lreg`: `p` = r72 "used 72 times across 121 insns in block 4; **dies in 12 places**" -> refused, left to global;
`&D_801B2C10` = r155 "13 times across 290 insns in block 4, dies once" -> local-alloc gives it `$16` (".. Register 155 in
16."); global then allocates r72 (`.greg` order `72 245`, conflicts include s0) -> `$17`. The tree's `$16` pin on `p`
occupied `$16` first, so r154 got `$17` (tree `.lreg`: "Register 154 in 17.").
Block-scoped `p` (body.c): twelve pseudos r147, r156, …, r246, each "6 times across 20 insns, crosses 1 call", each dying
once -> all local; `qty_compare_1` (local-alloc.c:1598, priority floor_log2(refs)*refs/live) ranks them (6 refs/20)
above r154 (13/290), so each takes `$16` and r154 gets `$17` (dumps_c4 `.lreg`: "Register 147 in 16." … "Register 154 in
17."). Proven on bytes (98 -> 0) and dumps.

The comma-expression's `q` was the second half: with the plain store `*(s32 *)(p - 0x2A) = 0;` written BEFORE the
argument is computed, cse knows `p` = `&D_801B25CC` and folds the store to an absolute address (`lui at; sw zero,-84(at)`,
+1 insn per block, 423 vs 411; `find_best_addr`, cse.c:2622, the constant is cheaper than reg+offset once the base is
known constant); computing the object pointer into its own variable first (`obj = (s32 *)(p - 0x2A); *obj = 0;`) keeps
the store register-based (`sw zero,-84(s0)`) as in the target. Proven on bytes only (blockscope_clean 38/423 ins vs C4 0);
the cse attribution is a hypothesis — not dumped.

## (c) The moves
- One block-scoped `s16 *p` per object instead of one function-scope `p` reused 12 times (local-alloc.c:471).
- The third argument named: `obj = (s32 *)(p - 0x2A); *obj = 0;` then pass `obj` (replaces the comma expression + `q`).

## (d) GENERATOR PROPOSAL
**R-scope-per-group**: when the residual is a callee-saved swap in which a pointer that is RE-ASSIGNED at the head of each of
N repeated statement groups (`.lreg`: "dies in N places", N > 1) loses `$s0` to a long-lived single-death constant/address
pseudo, wrap each group in `{ }` with its own declaration of the pointer (`T *p = X_k;`) and delete the function-scope one
(R23 "split one name per value" but with block scope and an initialiser — the tree text reuses the name, so R23's rename
did not fire across 12 identical groups).

## (e) What did not work (bytes)
- body_free: 98. Function-scope `p` with the clean statements (shared_clean): 136; with `obj` (C4_shared): 122.
- Block scope but the store written first on `p - 0x2A` (blockscope_clean): 38 (the absolute-address fold above);
  writing the store after the call (C5): 57 (ORDER).
- Also 0: the tree's comma text with twelve names `p0..p11` (split_names), block-scoped `p, q` with the tree's comma
  text (blockscope_tree), and `q = p - 0x2A; *(s32 *)q = 0;` (C1) / a comma with `q` (C3). body.c is C4 (the most readable).

## (f) Where the method fell short / what helped
- METHOD step 3 (S103 c1/c8: "a local REUSED across statement groups dies more than once and is refused by local-alloc —
  split it") named the fix exactly; the `.lreg` line "dies in 12 places" is the tell. The generators could not reach it
  because they split per statement, and the comma expression with an assignment inside `*(p = &D) = …` hid the
  re-assignment from a textual split.
- The allocation table showed only two global allocnos (72 245); the decisive fact (r155 local in `$16`) is in `.lreg`'s
  "Register N in 16." lines, not in the table.

## (g) Structs
Plausibly the ORIGINAL shape, but not an object-exact one. Each group addresses one 0x58-byte object: `p - 0x2A` = the
object base (`D_801B2578`, `D_801B25D0`, … — the same objects case 0 passes to `func_8017CA80`), `p - 0x28` = +0x4,
`p - 2` = +0x50, `p` = +0x54 (s16), and case 0 writes +0x1C/+0x20 (-0x480 / 0x5F0) and bumps +0x54. An
`extern struct { s32 f0; s32 f4[…]; … s32 f50; s16 f54; } objs[12];` would make the body a readable per-object block
(`o = &objs[k]; o->f54 = …; func_80049CAC(&o->f50, &o->f4); o->f0 = 0; func_8017CAD4(…, o);`) with the same allocation
decision (one pointer per group), but its relocations would be against the array symbol + offset instead of the
`D_801B25CC`-style field symbols the object file has — identical only after LINKING, so parked for the structs phase.
The `expr.c:4568-4577` aggregate channel does not bear on this lever (the decision is local-alloc eligibility). Not tested.
