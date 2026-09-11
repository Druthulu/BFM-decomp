# func_8017FB10 (ov_SC06_008) — mechanism (P36 S104 d26)

**Result: score 0, ZERO levers.** The `register s32 negdc __asm__("$2")` pin is gone, and so are the `negdc` and `s16 v1`
locals. Proof: `--try` of PACK/body.c prints "score 0 (OTHER; mine 93 ins, target 93) — MATCH". The same edit closes all six
other copies of the class (table at the end). Lever count before → after: 1 → 0 (7 → 0 over the class).

## (a) The residual
Score 8, MIXED. Instruction count and set are the same; in the `& 0x6000` arm the lever-free text issues the `+0xac` counter
load first (`lhu v0`) and the `+0xdc` load second (`lw v1`). The target does the opposite: `lw v0,220` / `lhu v1,172` /
`negu v0` / `addiu v1`, so `-dc` sits in `$v0` and the counter in `$v1`. That is TWO defects stacked on each other, one in the
order and one in the registers. The spellings tried separate them:

| spelling of the arm | sched1 order | local-alloc regs | score |
|---|---|---|---|
| tree/free: `negdc=-dc; v1=ld; v1-=1; st ac; st 14=negdc; if(v1==0)` | lhu first (wrong) | ctr v0 (wrong) | 8 |
| (b) `v1=ld-1; st ac; st 14=-dc; if(v1==0)` | lhu first (wrong) | ctr v0: tie at 10000, born first | 8 |
| (e) `negdc=-dc; st 14; v1=ld; v1-=1; st ac; if(v1==0)` | lw first (right) | ctr v0: pri 22500 vs 13333 | 8 |
| (c) `st 14=-dc; v1=ld-1; st ac; if(v1==0)` | lw first | dc v0: 13333 vs 11666 | **0** |
| **(a) `st 14=-dc; if(--*(s16*)(a0+0xac)==0)`** | lw first | dc v0: 13333 vs 11666 | **0** |

## (b) The passes and decisions (read in the source, proven on dumps of a mini-TU that reproduces both scores)
1. **ORDER — sched1's tie-break by original insn order**, `rank_for_schedule`, `sched.c:2425-2428`
   (`return INSN_LUID (tmp) - INSN_LUID (tmp2)`). The block is scheduled BACKWARD from the `bnez`. Both chains have priority 2
   (the `.sched` dump: `insn[164]` lw pri 1, `neg` pri 2, `lhu` pri 1, `addiu` pri 2, both stores pri 2). When the `+0x14`
   store is textually AFTER the `+0xac` store (the decompiler's order), it has the higher luid, so the backward list takes it
   first (T-2: `now 181 179 176`); the `-dc` chain then becomes ready early (T-4) and its `lw` is placed LATER in forward
   order (T-7), behind the `lhu` (T-8). With the store written first, the counter's `sll`/`sh`/`addiu` win the ties, the
   `-dc` chain is pushed toward the block's top, and the `lw` goes first (`.sched`: T-8 picks 163 = the lw). Proven: free
   and (b) schedule lhu-first, (a)(c)(e) lw-first.
2. **REGISTERS — local-alloc's quantity priority**, `qty_compare`, `local-alloc.c:1578-1594`
   (`floor_log2(refs)·refs·size / (death − birth)`), case 2 of the small sort `local-alloc.c:1486-1500` (ties keep birth
   order). The refs are flow's `reg_n_refs` (`flow.c:2067/2315/2501`), copied into the quantity at `alloc_qty`
   (`local-alloc.c:297`) and summed over tied registers by `combine_regs` (`local-alloc.c:1870`) — and flow counts them
   BEFORE combine collapses the insns. The decompiler's `s16 v1` user variable is SET TWICE (`v1 = load; v1 -= 1;`) and read
   twice, so pseudo 73 carries 4 refs even though combine leaves only a load and a subreg use: the counter quantity sums 9
   refs → `3·9/12·10000 = 22500`, beating the `-dc` quantity's `2·4/6·10000 = 13333`, and it takes `$v0` first (spelling e).
   Written as a pre-decrement (or a single-set `v1 = ld - 1`) the counter's quantity is fresh temporaries with 7 refs →
   `2·7/12·10000 = 11666 < 13333`, so `-dc` takes `$v0`. Proven with the `.lreg` dumps + the validated local-alloc simulator
   (`.run/P36/agents/ov_SC05_018__func_801837E8/scratch/lsim3.py`, "mismatches vs dump: 0" on a, b, c, e).
   Spelling (b) shows the second half on its own: equal priorities (10000/10000) fall back to birth order, and the
   mis-scheduled `lhu` is born first.

Both conditions are needed; the pin was covering both at once (a hard register fixed on `negdc` makes local-alloc skip it,
and the arm's registers then fall out regardless of the order it was scheduled in).

## (c) The move (one edit, two causes)
The decompiler's split statements
```
negdc = -*(s32 *)(a0 + 0xdc);
v1 = *(u16 *)(a0 + 0xac);
v1 -= 1;
*(s16 *)(a0 + 0xac) = v1;
*(s32 *)(a0 + 0x14) = negdc;
if (v1 == 0) func_8012C218((void *)a0);
```
become the original's two statements
```
*(s32 *)(a0 + 0x14) = -*(s32 *)(a0 + 0xdc);
if (--*(s16 *)(a0 + 0xac) == 0) {
    func_8012C218((void *)a0);
}
```
with the `negdc` and `s16 v1` declarations deleted. The rest of the body is untouched (header comment in the tree stays
accurate: "decrement the +0xac counter (signed s16 compare-to-zero on the POST-decrement value)").

## (d) Generator proposal
When a register residual in one block swaps two values that are each loaded, modified and stored back to memory, and the body
spells one of them as `v = *p; v -= K; *p = v; … if (v == 0)` through a named local, fold it to `if ((*p -= K) == 0)` /
`if (--*p == 0)` and move every independent store of the OTHER value to before it (a "collapse load-modify-store local into
the condition + hoist the sibling store" rule: the collapse fixes flow's inflated ref count, the hoist fixes sched1's luid
tie-break).

## (e) What did not work (bytes)
- (b) collapse without the reorder: 8 (order still wrong; equal priorities → birth order).
- (e) reorder without the collapse (store of `negdc` first, `v1` kept as a twice-set local): 8 (order right, the counter wins
  `$v0` on 22500 vs 13333).
- (f) `v1 = ld;` hoisted above the `-dc` store, `v1 -= 1` after: 8.
- (g) the whole arm as one comma-expression condition: 9 (COUNT, one extra instruction).
- History's generators (R2–R34) reached 2 by swaps of the existing split statements; none collapses `v1 = ld; v1 -= 1; st`
  into a pre-decrement, so the ref count stayed inflated.

## (f) Where the method fell short
- The residual text and `alloc_table.py` would have pointed at a register pin; the separating experiment was four spellings
  of the arm (b/c/e/a) — a 2×2 over "store order" × "collapsed counter". That grid, not the allocation table, split the
  ORDER defect from the PRIORITY defect in one minute.
- The brief said "3 copies"; `grep` of the distinctive `+= *(u16 *)(a0 + 0xfc);` line finds SEVEN (this one plus six in
  ov_SC06_010/018/022/024/032/033), all pinned identically, all closed by the same text.
- The regen directory has no score index, so "start from its lowest-scoring file" meant re-scoring 203 files; I started from
  `body_free.c` instead and the first spelling closed.

## (g) Structs answer
No — a struct type does not reach either decision here, and the bytes say so. A body-local
`struct Obj { u8 pad0[0x14]; s32 f14; …; s16 fac; …; s32 fdc; } *o = (struct Obj *)a0;` with field accesses leaves the
decompiler's split text at **8** and the collapsed text at **0** (`PACK/scratch/c/s_free.c`, `s_a.c`). The only channel a
struct opens is `MEM_IN_STRUCT_P` in `true_dependence` (sched/cse store-vs-load aliasing, `expr.c:4568-4577`); here there is no
dependence to break — the `+0x14` store and the `+0xac` load share a base with disjoint offsets, so `memrefs_conflict_p`
already calls them independent. The decisions are the luid tie-break and flow's ref count, both fixed by the statement shape.
For naming later: `+0x14` s32 (a velocity/speed mirrored into `+0xdc`), `+0xac` s16 hit counter, `+0x1c` s32 countdown,
`+0x20` sub-object pointer with s16 `+0x10/+0x12/+0x14`.

## Copies (the same text, `--try` score 0 each; bodies in PACK/scratch/)
| function | TU | file |
|---|---|---|
| func_8017FB10 | src/ov_SC06_008/ov_SC06_008_jr_8017C294.c | PACK/body.c |
| func_8018C608 | src/ov_SC06_032/ov_SC06_032_jr_80182890.c | PACK/scratch/func_8018C608.c |
| func_80181FC4 | src/ov_SC06_010/ov_SC06_010_jr_8017A4AC.c | PACK/scratch/func_80181FC4.c |
| func_8018EC50 | src/ov_SC06_024/ov_SC06_024_jr_80186F00.c | PACK/scratch/func_8018EC50.c |
| func_8017F91C | src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c | PACK/scratch/func_8017F91C.c |
| func_801902A8 | src/ov_SC06_033/ov_SC06_033_jr_8018D98C.c | PACK/scratch/func_801902A8.c |
| func_8018C778 | src/ov_SC06_022/ov_SC06_022_jr_80184A28.c | PACK/scratch/func_8018C778.c |

Each copy keeps its own tree text (K&R header in ov_SC06_032, its own `D_` table symbol, the body-local `extern` where the tree
had one, the cast call spelling in ov_SC06_024); only the arm is replaced and `s16 v1;` deleted.
