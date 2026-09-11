# func_8017BEBC (ov_SC06_010_jr_8017A4AC.c) — T7 e14, P36 S104

**Score 0, ZERO levers** (free start 6 = regen best 6). Tree levers: 1 (the `m24` launder after the inner loop) -> 0.
The same move closes the same-TU twin **func_8017CAD4** at 0 (its own pack, same mechanism, one tie window over).

The move (case 6/7, FT3 depth):
```
                 if (g.sz0 > g.sz1) {
                     za = g.sz0;
                     if (za < g.sz2) za = g.sz2;
+                    g.opz = za;
                 } else {
                     za = g.sz1;
                     if (za < g.sz2) za = g.sz2;
+                    g.opz = za;
                 }
-                g.opz = za;
```
plus the launder line deleted (body_free.c is the start). The hand-written guard `i = 0; if (i >= nprim) goto noprim;`
and the `m24` local stay (the frame-slot lever (4) of the header is still real; see (e)).

## (a) The residual
Same 753 instructions, a pure `$s6`/`$s7` swap of the two loop-invariant addresses `&g.sz0` (sp+236) and `&g.sz1`
(sp+240) that the outer loop hoists for `gte_stsz3`/`gte_stsz4` (3 sites: preheader `addiu`, two `swc2` pairs).

## (b) The pass and the decision (read in dumps_free / dumps_tree / probe/dumps_dup_opz3)
1. **global.c `allocno_compare` (global.c:585-607), an int-truncation TIE.** `.lreg`: r237 = `&g.sz0` 7 refs / live 571,
   r239 = `&g.sz1` 7 refs / live 570 (r239 is set one insn later in the preheader, both live to the outer loop's back
   edge). pri = (int)(floor_log2(7)*7/L*10000) = (int)(140000/571) = 245 = (int)(140000/570) -> tie -> allocno number
   -> r237 first -> `$s6` (free `.greg` order `… 319 237 239 …`). Target/tree: live 572/571 -> **244 vs 245** -> r239
   first (tree `.greg` `… 319 239 237 …`). This is cookbook §47's class exactly (the same tie on an earlier renderer).
   Any +1 insn over the whole outer loop at flow time splits it; the launder was an asm insn doing only that (the tree's
   `.loop` says 601 real insns in the outer loop vs 600 free). Window for this pair: N = +1, -1, +3 split; 0, +2, +4 tie.
2. **flow counts insns that post-reload cross-jump later removes.** Storing `g.opz` in each arm gives two identical
   `sw` at the end of the two arms at flow time (flow.c:1660-1684 counts every real insn a live pseudo spans) -> r237/r239
   live 572/571 (probe `live.py`); after reload, `jump_optimize(insns,1,1,0)` (toplev.c:3142) cross-jumps the two
   identical tails (`find_cross_jump`, jump.c:2371) back into one store: `.sched2` has 5 stores to 232(sp) in the
   function, `.jump2` 4 — the free body's count, and the bytes are the free body's instruction stream with the tie
   split. Proven on bytes (score 6 -> 0) and on dumps.

## (c) The move that closed it
- In case 6/7, store the depth `g.opz = za;` at the end of EACH arm of the `g.sz0 > g.sz1` if/else instead of once after
  it (one statement duplicated; the launder deleted).
- Equivalent closes found (all 0, less natural): moving any ONE of the four bounding-box `t32 = sxy[k].v?;` loads into both
  arms of its preceding `if (xb32 < xa32) {…} else {…}` (dupbb0..dupbb3). Doing all four (+4) scores 6 again — the
  tie window, as predicted.

## (d) GENERATOR PROPOSAL
**R-dup-join (cross-jump live-length dial)**: when the residual is a pure callee-saved swap of two allocnos whose `.lreg`
refs are equal and whose `(int)(floor_log2(r)*r*1e4/L)` priorities are EQUAL (the alloc table shows the tie), find every
if/else inside their common live range whose arms both fall to a join followed by a single-insn statement (a store or a
load into a temp), and emit the variant that moves that statement into both arms (+1 flow insn, zero bytes after jump2's
cross-jump). Enumerate one site at a time; +2 re-ties, so never combine two.

## (e) What did not work / what the header claimed
- body_free (launder deleted): 6. Header lever (3) says the launder is needed so the OUTER scan_loop does not re-hoist the
  0x00FFFFFF mask; on the current text that is **stale**: without it the mask stays in the inner preheader (the free body
  differs only in `$s6/$s7`). The `m24` name + in-loop assignment is still needed: the literal (`lit`) is 42, `m24`
  assigned above the outer loop is 48.
- Loop spellings: a `for (i = 0; i < nprim; i++, prim++)` with `m24` set before it: 11 (the mask moves above the guard);
  with `m24 = 0xFFFFFF;` as the loop's first statement: 6 (loop.c hoists it to the inner preheader after the guard — a
  clean alternative to the hand-written guard, but it does not touch the tie); `while` form: 6; `nprim == 0` guard: 24
  (the frame slot of header lever (4)).
- 104 single declaration-width changes (26 locals x s32/u32/s16/u16): best 4 (`lim` as u16 — wrong; its zero-extension is
  the +1, confirming the mechanism, but the load becomes `lhu`); no width move splits the tie cleanly.
- mnc/mxc as ternaries: 16-47; as if/else: 6.

## (f) Where the method fell short / what helped
- The residual looked like a register permutation, and METHOD step 4 sends you to the allocation table; the table did
  show the tie at once, but no METHOD entry says how to add ONE flow insn in plain C. S103 c6 (cross-jump re-merges
  duplicated code after allocation) is the right channel; it is written for ref counts, and it works for live lengths too.
- `tools/alloc_table.py`'s priority column prints the float (245.6 vs 245.2) and hides the int-truncation tie; the order
  line (`237 239`) is what proves it. A column with `(int)` priority would flag ties directly.
- `.loop`'s "real insns" is NOT a proxy for the flow live length (wzh as s16 adds one insn at loop time that is gone
  before flow); read `.lreg`'s `Register N used R times across L insns` (scratch/live.py does it for the two addresses).

## (g) Structs
No. The decision is live-length arithmetic on two hoisted stack addresses. `g` is already a struct and XFT3/XFT4 are
already structs; giving `part`/`prim` or the packet more struct typing changes no insn count over the outer loop at flow
time and no allocno refs, and the `expr.c:4568-4577` aggregate channel (sched/cse memory ordering) is not involved.
Not tested on bytes — the plain-C close made it moot.

## Header note for the coordinator
The TU header over this function says the four levers of func_8017CAD4 "are inherited verbatim and are all load-bearing";
lever (3) is now: "`m24` assigned after the hand-written guard (the literal is re-hoisted); the launder is gone — the
&g.sz0/&g.sz1 allocno tie (§47) is split by storing `g.opz` in each arm of the FT3 depth if/else (+1 flow insn,
cross-jumped away after reload)". CAD4's header ends with "DO NOT add a … slider here: … the tie already falls the
target's way" — no longer true of the current text (both functions needed the +1).
