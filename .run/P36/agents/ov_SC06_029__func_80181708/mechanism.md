# func_80181708 (ov_SC06_029) — agent e22, P36 S104

**Result: score 0, ZERO levers (the $3 pin and the `__asm__("")` barrier both gone). Levers 2 -> 0.**
The body uses two body-local STRUCT typedefs (`SV` = {vx,vy,vz,pad} for the two SVECTOR-pointer globals, `OB` for the
object at `param_1`) and two body-local array-typed DECLARATION aliases of the s16 globals
(`extern s16 D_801904C6_a[] __asm__("D_801904C6");`, same for `D_801904CE`). No pin, no asm statement, no volatile,
no signature change. The file-scope equivalent of the aliases is `extern s16 D_801904C6[];` / `D_801904CE[]` in the TU
(a declaration-type change outside the body — the STRUCTS phase can make it and drop the aliases).

## (a) The residual
Lever-free: score 26 (COUNT, 66 vs 65). Two independent defects:
1. block 0: `psVar1`/`psVar2` land in v1/a0 where the target has a1/v1; with psVar2 in a0 sched2 cannot hoist its load
   above `move s0,a0`, so the prologue interleave differs (+1 ins).
2. after call 1: sched1 order `sll, sra, lw 76, lw t, addu, sw` vs the target's `sll, lw 76, sra, addu, lw t, sw`, so
   the reloaded `D_801DFD90` (t) is born while the `sra` result still holds v0 and takes a1 instead of v0.

## (b) The pass and the decision (read, then proven on bytes)
- sched.c:817-839 `true_dependence` / :845-861 `anti_dependence`: a MEM_IN_STRUCT access at a VARYING address never
  conflicts with a NON-struct access at a FIXED address. expr.c:4568-4577 sets MEM_IN_STRUCT for an INDIRECT_REF of a
  PLUS_EXPR or an aggregate; `*(s32 *)(param_1 + K)` is a NOP_EXPR of an int sum -> NOT struct; `((OB *)param_1)->xK`
  -> struct; `D_801DFD8C` (s32 scalar) -> non-struct fixed; `D_801904C6` as `s16` -> non-struct fixed, as `s16[]`
  element -> struct fixed.
- With the stores struct-varying, the loads of the two pointer globals (non-struct fixed) lose every memory edge:
  sched1 (backward, birthing boost sched.c:2469-2544 since each is set once) places `p2 = D_801DFD90` right before its
  first use, so p2's quantity is born late: local-alloc `qty_compare_1` (local-alloc.c:1598) ranks p2 (3 refs, short
  life) ABOVE p1 (4 refs over 22 numbers, 3636) -> p2 takes v1 first; p1 then finds v0 (temps), v1 (p2), a0 (the
  `D_801904C6` arg load precedes p1's death) busy and takes a1 — the target's assignment. sched2 then hoists both loads
  above the prologue (no memory or register edge left), exactly the target's first four instructions.
- The same independence lets the `D_801DFD90` reload after call 1 and the `D_801DFD8C` reload after call 2 schedule
  above the `x4C`/`x40` stores (the target's order; the free body only got it by writing the loads first).
- The `D_801904C6`/`D_801904CE` argument loads must STAY behind the object stores (target: after `sw 68(s0)` / after
  `sw 76(s0)`): with struct-varying stores that needs the loads to be struct too -> the array-typed alias. Without the
  aliases (n5) the arg load floats to just after `move s0,a0` (sched2) and the score is 21; one alias alone 10-11.

## (c) The moves (all needed; single steps score worse)
1. object stores/loads through a struct type: `((OB *)param_1)->x48 = ...` (MEM_IN_STRUCT varying).
2. the two pointer globals read directly (`((SV *)D_801DFD90)->vy`) instead of via the `t`/`psVar5` temps, and `SV`
   field access for the pointed-to vectors (readability; `p1[0]`/`p1[2]` score the same — n4 = 0 too).
3. `D_801904C6`/`D_801904CE` read as elements of an array-typed declaration (struct-FIXED), keeping them behind the stores.
4. `+=` with the `(s16)` cast inline instead of `sVar4`/`acc` temps (the barrier's job — acc before the t load — falls
   out of the dependence graph once the loads are free).

## (d) Generator proposal
When a register/ORDER residual involves loads of GLOBALS that the target hoists above stores through a parameter
pointer (or leaves behind them), rewrite each access's MEM_IN_STRUCT class to match: object fields through a struct
cast (`((T *)p)->f`), global scalars as plain names (non-struct fixed), and globals the target keeps ordered after the
stores as array elements (`extern T G_a[] __asm__("G")`, struct fixed) — enumerate the 2^k struct/non-struct choices
per access group, it is a small search that no current generator (R2-R41) spans.

## (e) Tried and failed (bytes)
- n1 (inline temps, all `*(s32 *)(p+K)` casts) 28; n2 (struct `OB *o = (OB *)param_1;` local + SV) 28 — the arg loads
  float to the top; n3 (struct only on x4C) 48; n10 (n11 with `OB *o` as a local) 9 — the separate local costs a
  copy; n12 (`(*(s16 (*)[1])&D_801904C6)[0]`, no alias) 21 — the ARRAY_REF of a cast ADDR_EXPR is not marked;
  n6 (`(&D_801904C6)[0]`) 21 — fold removes `+ 0`.
- The s104_all regen best was 7 (a marked do-while around one store) and history's best 2 (do-while + inline t).

## (f) Where the method fell short
Step 12-16 name the aggregate channel only for ONE lever class (a table load hoisted over a store). Here it closed a
pin AND a barrier: the register residual was a sched1 ORDER consequence (births/deaths feeding qty_compare), and
the order was set by memory dependence edges. The allocation table (and localalloc_sim) explained the v1/a0 choice
but could not suggest the fix; reading the sched1 ready-list trace for WHY `lw D_801DFD90` only became ready after
the first store (an anti-dependence edge) was the step that found it.

## (g) Structs — YES, this is the structs channel, proven on bytes
`param_1` is an object with s32 fields at 0x3C/0x40/0x44/0x48/0x4C/0x50; `D_801DFD8C`/`D_801DFD90` are `SVECTOR *`
(set in func_80180F08 to `&D_801904D4[0]` / `[2]` of an s32 array = 8-byte SVECTORs); `D_801904C6`/`D_801904CE` are
s16 members of an aggregate (8 bytes apart — plausibly the `pad` of two SVECTORs at D_801904C0/C8, or two fields of one
struct). Giving these their struct types is exactly what moves the sched.c dependence decision; with file-scope types
the two aliases disappear.
