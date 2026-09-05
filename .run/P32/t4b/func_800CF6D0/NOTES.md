# func_800CF6D0 (md_MAIN_007, 249 ins) — S83 pointer (residual 137 at exact length: sched1 rank_for_schedule last-insn-CLASS
tie + a $t1<->$t3 swap of the two masks; prologue constant order idx 3–16 like func_800CF408/func_800CD92C)
Prior: .run/P32/t3/reports/func_800CF6D0__opus__*.md; §500-C (tpage-before-len field order is the only one of 19 that hoists
the five tpage constants; `arg1 += 0x100` in place; the decomp-permuter's 122 was semantically wrong). The SAME two levers as
its siblings (mask register order $t1 vs $t3 = which mask is born first; prologue weave) account for the head; the 5-of-6
block QImode/HImode store grouping is sched1 priority: stores of equal priority are ordered by LUID — the target's source order
within each block is [tag word, QImode fields, the two loads, HImode fields]; write the fields in that order per block.
