# func_800CF408 (md_MAIN_007, 178 ins) — S83 pointer (residual 49: [permuter] 3 hunks; the diff starts at idx 3 with the
0xFFFFFF mask in $t1 vs $t3 and the prologue save/constant order)
Prior: .run/P32/t3/reports/func_800CF408__opus__*.md; §500-C (§351 family: func_8001212C -O0 / func_8017DD04 -O2 exemplars;
the two LENGTH-bearing pins tp=$17 shared by 0xE1000087/97, ob=$10). Same prologue-weave class as func_800CD92C: the target
loads the mask (0xFFFFFF) into $t1 FIRST, then saves $s1 and loads 0xE1000087 into it, then saves $s5… — constant loads
interleaved with the saves in the order of the CALLEE-SAVED register numbers they target, small constants after. The draft's
pins reproduce the registers but not the order → unpin and let global-alloc choose (the pins are the order's enemy: a hard
reg constant has no allocno priority for sched2's prologue weave).
