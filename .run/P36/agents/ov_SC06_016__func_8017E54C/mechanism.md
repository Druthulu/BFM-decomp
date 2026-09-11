# func_8017E54C (ov_SC06_016, src/ov_SC06_016/ov_SC06_016_jr_8017C8D0.c) — e24, P36 S104

**Final: score 0, ZERO levers** (the tree's one `__asm__("" ::: "memory")` barrier removed). `body.c` = scratch/c3.c
(scratch/c2.c, the same move keeping the `{ tmp; flag; }` block, also scores 0).

(a) Residual (body_free, score 4, COUNT 112 vs 113): after `D_8019F70C = v0;` the target RE-LOADS the global
(`lui; lh; nop` before `slti 4`), mine re-extends the register it just stored (`sll 16; sra 16`). One instruction missing,
not a register defect.

(b) Pass: cse. The store `(set (mem:HI D_8019F70C) (subreg:HI v0))` is entered into the hash table as a memory
equivalence (`cse.c:7358-7369`, `elt->in_memory`), so the following `(mem:HI D_8019F70C)` read in the SAME basic block is
replaced by the stored register and only the sign extension survives. In the target the read sits in a block that
begins at a CODE_LABEL reached from two predecessors — `cse_end_of_basic_block` stops at every CODE_LABEL
(`cse.c:8039`), so nothing is forwarded and the `lh` stays. The single `sh` in the join block is post-reload
CROSS-JUMP (`find_cross_jump`, `jump.c:2371`) merging the two arms' identical `lui at; sh v0,0(at)` tails AFTER cse ran.

(c) Move (proved on bytes): the original stored the global in EACH arm —
`if (flag != 0 && (flag < 5 || flag == 8)) D_8019F70C += 1; else D_8019F70C += 4;` then `if (D_8019F70C >= 4)`.
The decompiler's single `v0` temp + one store was the post-cross-jump shape read back as source. Also: `flag` must stay
an `s32` local (`s32 flag = *(u8 *)(a0 + 0x5E);`) — testing the `u8` read directly gives `sltiu` for `< 5` (score 1,
scratch/c1.c). The nested `if (flag != 0) { if (<5) … else if (==8) … else … } else …` collapsed to one `&&`/`||`
condition (the target has exactly two arm bodies).

(d) GENERATOR PROPOSAL: when the residual is "target reloads a global/field right after a store (`lui; lh/lw`), mine
re-extends or reuses the register" AND the stored value comes from a temp assigned in several if/else arms, push the
store into every arm (`G = X` per arm, `G += k` when the arm computes `G + k`) and delete the temp — cross-jump
re-merges the stores and the join-block read survives cse.

(e) Not tried/needed: the history's 186 mechanical candidates all stayed at 4 — none moves a STORE across a join.

(f) Method note: COUNT FIRST (step 2) settled it immediately — one missing load = a cse forward, not a register issue.

(g) Structs: no. The defect is block structure (store before vs after a join label), not an aggregate-vs-scalar alias
decision; typing D_8019F70C as a struct field would still be forwarded by cse inside one block.
