# func_80032A74 (main/800_b_2, 422 ins) — hand-crack notes, S83 T4b

**State.** S79w draft (leaf 1: idx 244 `lh` vs target `lhu`); synced TU-clean copy `.run/P32/t4/drafts/func_80032A74_tuclean.c`
(rtu DIFF 1). The `lhu` respelling (`.run/P32/t4b/func_80032A74/lhu.c`) is byte-exact in all 422 instructions EXCEPT the frame:
vars 56 vs 64 (frame 0x70 vs 0x78; 22 rows are the shifted stack offsets). So the WHOLE residual is 8 frame bytes with no code.

**What the S79 analysis proved.** The 8 bytes cannot be a declared local (pads land before the a0/a1/a2 reload spills at
0x30/0x38/0x40 and move them). An `lh`-orphan (§172 producer 2) buys them but forces `lh`. `zero_extendhisi2` never orphans.

**Refined mechanism (source-read, S83): §172 producer 3 = a TRANSIENT caller-save area, and its order is right.**
`reload1.c` reload loop, per iteration: compute needs → `setup_save_areas()` (caller-save.c:249: for every call-used hard reg
currently holding a call-crossing pseudo, `assign_stack_local(SImode, 4, 0)`) → THEN choose spill regs and `spill_hard_reg`.
The draft's .greg shows `Spilling reg 8` ($t0) at iteration 1 (a GR_REGS reload for insn 17). So a pseudo P that global/local
placed in $t0 with caller-save gets a 4-byte area at iteration 1 and is evicted the same iteration; the area stays
allocated and unreferenced. The three param slots (72/73/74: `reg_renumber = -1` from global, alter_reg BEFORE the loop) sit
at 0x30/0x38/0x40; the area lands next at 0x48 — the target's never-referenced slot. vars 56 + 4 = 60 → MIPS_STACK_ALIGN → 64.
For the code to stay identical, P must need NO stack slot after eviction: a rematerialisable pseudo (`symbol_ref`/constant,
REG_EQUIV) — the draft's 81/82/83 (`tA`/`tB`/`vB` addresses) are exactly that class but cross 7 calls with 3 weighted refs.
Profitability rule: `CALLER_SAVE_PROFITABLE(refs, calls) = 4*calls < refs` (regs.h:165; global.c:1083 retry; local-alloc.c:2209),
refs weighted by `loop_depth` (flow.c:2067 etc.; the `for(;;)` body is depth 2).

**What to search (a Fable-budget job, ~30 compiles, oracle = `.frame` vars in `tools/cc1_dumps.sh` + match_one):** a
block-local, rematerialisable value (a global's ADDRESS or an integer constant) that in the original source was held in one
variable across exactly ONE call with ≥3 uses in the loop body (2·3 = 6 > 4) — e.g. an address passed to two calls that
bracket a third call, or a constant stored before and after a call. Every such candidate the draft currently re-materialises
per use (two pseudos, no call crossed). Tell: the target's code is already identical, so the variant must change NO instruction
— only `vars=` (56 → 64) and the 22 offset rows. Candidates NOT to pursue: `D_800A46A2` (it is an `lh` VALUE, not an address),
the param pseudos (15/3/8 refs vs 7 calls — unreachable), anything declared as a local (wrong stratum).
