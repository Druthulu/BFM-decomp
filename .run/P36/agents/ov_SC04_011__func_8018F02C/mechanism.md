# func_8018F02C (ov_SC04_011, TU ov_SC04_011_jr_8017D494.c) — T7 agent c44

**Result: score 0, lever-free.** No register pin, no asm, no added volatile, no do-while, no invented term. The change is
inside the function body only: the three hand-written OT links become the libgpu `P_TAG` bitfield stores
(`addPrim` = `setaddr(p, getaddr(ot)), setaddr(ot, p)`), and the two `tv`/`tv2` temporaries disappear. `P_TAG` is the
existing `src/shared/engine_types.h:517` typedef, already visible in this TU. Whole-object check on the `--try --keep`
object: `objdump -drz` of the ENTIRE `.o` is identical to `.run/P36/delever/baseline/src/ov_SC04_011/
ov_SC04_011_jr_8017D494.o`, and `.text` compares equal with `cmp`. func_8017D494 (agent c37's) is untouched.

**Class propagation, checked by `--try` (function-level, score 0 in every one):** the same text (renamed; the two md/SC03
copies also keep their body-local `extern short D_800B9A02;`) scores 0 in all six other copies. They are
`func_8017F8A8` (ov_SC04_016), `func_801AF368` (md_SC07_004), `func_8017E2EC` (ov_SC03_114), `func_80187B34`
(ov_SC06_000), `func_80181658` (ov_SC06_006) and `func_8018CD04` (ov_SC06_018). The texts are
`scratch/port_<fn>.c`. md_SC07_004 already spells a sibling (lines 4090-4095) with exactly this `P_TAG` form.

## (a) The residual in one sentence

Same count (296/296), registers only. The `tv` word of the pkt/p1 links sat in `$a0` where the target has `$v1`. The
`tv2` word of the p2 link sat in `$v1` where the target has `$a0`. That knocked on to `p1` `t2→t3`, the flag `t1→t2`,
`pkb` `a0→a1` and `p2` `a1→t1`, plus one sched2 reorder (`lw a0,48(a1)` above `or`) that only works with the target's
registers.

## (b) The passes and the decisions (proven in dumps and on bytes)

* **The hand-written links reuse one user variable.** `tv = RW32(pkt); … tv = RW32(p1);` sets `r83` twice in block 9
  ("dies in 2 places"). Local-alloc refuses a register that dies more than once (local-alloc.c:472), so `tv` becomes a
  GLOBAL allocno. Global allocation runs after local-alloc has already handed `$v0/$v1` to the block's short temps
  (the `lhu 100(sp)` temp `r198` got `$v1`). `tv`'s conflicts are then `v0,v1` (alloc_table: `r83 … conflicts
  v0,v1,sp`), and `find_reg` gives it `$a0`.
* **`tv2 = RW32(p2)` is a single-set user variable.** Its load is a "birthing" insn: a REG set once and live after
  it, so `birthing_insn_p` holds (sched.c:2468-2499). `adjust_priority` (sched.c:2539-2545) lifts it to `max_priority`
  as soon as it is ready in the backward list scheduler, so sched1 places it right before its consumer, after the
  `0xE1000000` store (`dumps_free/free.i.sched`: 526 527 529 530 532 **535** 541). Its range then misses the
  `lui 0xe100` temp's `$v1`, and local-alloc gives it `$v1` (`localalloc_sim … 535`: q4 = r84,r231,r236 → v1, matches
  the dump).
* **The bitfield store expands differently** (`store_fixed_bit_field`, expmed.c:556, :664-706). It emits the VALUE
  (the `getaddr(ot)` extract: `lw otp; and 0xFFFFFF`) first. Then the destination is masked through `expand_binop`
  with the forced-register word as the subtarget (expmed.c:690-702), so ONE fresh pseudo is set three times: load,
  `and 0xFF000000`, `ior` (`dumps_f1/f1.i.sched` insns 550/556/557 all set `r236`). Two things follow:
  1. Each link's word is a NEW block-local pseudo with a single death, so local-alloc takes it. In block 9 the pkt word
     `r204` (q31) gets `$v1` and the `lhu` temp `r196` (q30) gets `$a0`, which is the target's pair (`localalloc_sim
     f1.i.lreg … 457`, 0 mismatches). `tv` is no longer a global allocno, and the global order resettles to the
     target's `p1=t3, flag=t2, pkb=a1, p2=t1`.
  2. The p2 word's pseudo is set 3 times, so `reg_n_sets == 1` fails in `birthing_insn_p` (sched.c:2489) and the boost
     is gone. sched1 then schedules the load by critical path alone and hoists it directly under the `sb 51(pkb)` it
     depends on (f1 order: 532 **550** 534 535 537 538 540). Its range covers the E1 chain (`$v0`) and the `lui` temp
     (`$v1`), so local-alloc gives it `$a0` (`localalloc_sim … 550`: q2 = r236 → a0). sched2 then produces the
     target's `lui v1; lw a0,48(a1); or v0,v0,v1`.

## (c) The source move that closed it

One move, applied at all three links (score 24 → **0**, `scratch/f1.c` = `body.c`):

```c
((P_TAG *)pkt)->addr = ((P_TAG *)otp)->addr;   /* was tv = RW32(pkt); RW32(pkt) = (tv & 0xFF000000) | (RW32(otp) & 0xFFFFFF); */
((P_TAG *)otp)->addr = (u32)pkt;
((P_TAG *)p1)->addr  = ((P_TAG *)otp)->addr;
…
((P_TAG *)otp)->addr = (u32)p1;
…
    ((P_TAG *)p2)->addr = ((P_TAG *)otp)->addr;
    ((P_TAG *)otp)->addr = (u32)p2;
```

Partial controls: the pkt/p1 links only (`tv2` kept) = 43 (`f2.c`). The p2 link only (`tv` kept) = 6 (`f3.c`, REG). It
is a joint close: each half needs the other's register picture. Also proven: `((P_TAG *)p2)->len = 1` in place of
`*(u8 *)(p2 + 3) = 1` (libgpu `setlen`) is still 0 (`f4.c`). I kept the smaller diff in `body.c`.

## (d) GENERATOR PROPOSAL

When a function hand-writes the OT link `(X & 0xFF000000) | (Y & 0xFFFFFF)` through a named temporary (and especially
when the tree pins that temporary to `$3`/`$4`), rewrite every link as the `P_TAG` bitfield pair
`((P_TAG *)p)->addr = ((P_TAG *)ot)->addr; ((P_TAG *)ot)->addr = (u32)p;` and delete the temporary. The bitfield
expansion gives a fresh, multiply-set, block-local pseudo per link. That puts the word in local-alloc's hands and
switches off sched1's birthing boost (sched.c:2489). This is cookbook §364 / src/800.c:14904's "OT link is a P_TAG"
crack, now shown to retire `$3`/`$4` pins. A grep for `0xFF000000) |` beside `& 0xFFFFFF` over the pinned residue would
list the class.

## (e) What did not work / what the search could not see

* The mechanical search (24 → 24 over ~1150 compiles) inlined `tv2` (R6), narrowed it, and moved declarations. Every
  hand-written mask/or spelling keeps the dest-first operand order and a single-set temp, so none of them reaches this.
  Declaration order is provably dead here: `tv`'s allocno priority (8000) differs from its rivals, global.c:604-610.
* `f2.c` (43) shows the pkt/p1 bitfield alone is WORSE. Scored one link at a time, the move would have been abandoned.
  METHOD §5 (joint edits) applied.

## (f) Where the method fell short

* The brief's `$3`/`$4` pin checklist (call arity, implicit handler arguments, a pointer carried to a join) did not
  cover this. The pins were compensating for an EXPANDER shape (bitfield insert vs hand mask). The answer was already in
  the tree three times: func_8018EBCC's header in this very TU (lever A, "THE OT LINK IS THE libgpu P_TAG BITFIELD"),
  src/800.c:14904, and md_SC07_004:4090. Grepping the TU's own `@crack`-style prose for the idiom the body spells by
  hand (`0xFF000000`) found it faster than the allocation table did. Suggest a `neighbours.txt` line for "headers in
  this TU that mention a constant your body uses".
* `alloc_table.py` + `localalloc_sim.py` were decisive for EXPLAINING the close after it happened: the 0-mismatch
  simulation of blocks 9 and 10 is the proof above.
