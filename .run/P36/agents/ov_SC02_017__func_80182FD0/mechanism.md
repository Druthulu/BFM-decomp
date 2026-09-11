# func_80182FD0 — e9 (P36 T7 S104) — score 10 (sweep best 2) -> 0, ZERO levers
(was: 2 NEEDED `keepalive`s + a NEEDED `volatile s32 *` cast + a REMOVED `$3` pin; ALSO gone: the hand-written GTE asm
with a hard-coded `lui $2,%hi(D_800AF648)` and the hand-merged `lwc2;lwc2;nop;nop;rtps;swc2` block — every GTE op is now
a Sony macro from include/gte_inline.h)

(a) Residual: REG, a v1/a0 permutation in the two screen-bounds tests — the target keeps the projected coordinate `x`
in `v1` and the bound `lim` in `a0`; lever-free swaps them (counts equal, 102/102).

(b) Pass/decision (dump-verified: `scratch/dumps_free`, `dumps_a2`, `dumps_a3`; `tools/alloc_table.py`):
  1. Both tests span a block boundary (the second `slt` sits after the first `beqz`), so `x` and `lim` are global
     allocnos ranked by `allocno_compare` (global.c:594-610, priority = floor_log2(refs)·refs/live). The decompiler
     REUSES `x` and `lim` for both axes: free r76 (`lim`) 6 refs / live 10 = 12000 > r75 (`x`) 6/14 = 8571 -> `lim` is
     allocated first and takes `v1`. One bound per axis (`lim`, `lim2`): each 3 refs / live 5 = 6000 < `x` 8571 ->
     `x` first -> `v1`, the bounds `a0` (a3 table). Splitting `x` instead (a2) leaves `lim` at 12000: 10.
  2. The `volatile` re-read of `+0x1C`: the countdown is `if (t == 0) { walk; t = reload; } t -= 1;` — the join block
     re-reads `+0x1C` (the store in the zero arm is in another basic block, so cse does not forward it), and reorg
     (`fill_slots_from_thread`, reorg.c:3270; `redundant_insn` skips the join's `lw` on the taken path, where `v0`
     already holds it) steals the `addiu -1` into the `bnez` slot — the target's two decrements. Proven on bytes
     (b1/b2/b3 = 0); the reorg reading is from the bytes' shape, not a `.dbr` dump.
  3. GTE setup: a Sony macro with a CONSTANT input `gte_SetRotMatrix(&D_800AF648)` keeps the constant in the
     asm_operands (stmt.c:1556-1569: a `general_operand` constant is not forced into a register), so reload loads it
     into a spill register (reload1.c:3690-3700, the first call-used hard reg no pseudo uses: a2 here, a3 in the siblings func_80181E98/func_8018209C, whose targets do use a3) and sched2
     hoists that `la` into the `lh` delay slot (s4: 12, COUNT 101). Through a local pointer `u8 *m = &D_800AF648;` the
     operand is a pseudo, local-alloc gives it `v0` and the `la` stays right before the loads — the target.

(c) Moves:
  - one bound per axis: `lim2 = (D_800AF7BE >> 1) + 0x20;` for the second test (a3 = 0 alone — the two keepalives gone);
  - the countdown `if (*(s32 *)(param + 0x1C) == 0) { …walk…; *(s32 *)(param + 0x1C) = *(s32 *)(param + 0xDC); }
    *(s32 *)(param + 0x1C) -= 1;` (b1 = 0 — the `volatile` cast and the `v0`/`goto store` gone);
  - the GTE asm -> `gte_SetRotMatrix(m); gte_SetTransMatrix(m);` with `u8 *m = &D_800AF648;` and
    `gte_ldv0(w.v); gte_rtps(); gte_stsxy(w.v); gte_stflg(&w.flag);` (s6/s7/s8 = 0; `m` set before or after the
    table read, or as an initialiser, all 0);
  - readability (all 0): the goto chain -> nested `if`s with `&&` (s1), `buf[3]` -> `struct { s16 v[4]; s32 flag; } w`
    (sibling func_80181E98's shape), `x` inlined as `w.v[0]` / `w.v[1]` (s2/s3), the walk as a `while`.

(d) GENERATOR PROPOSAL: (1) when a keepalive/pin fixes a register swap between two locals that are REUSED across two
parallel statement groups (the same pair of names assigned again for the second axis), split the one with the higher
`allocno_compare` priority (or both) per group — R23 splits one variable at a time and must try each separately;
(2) when a body carries a hand-written GTE asm whose text loads a symbol into a fixed register (`lui $N,%hi(SYM)`),
replace it with the Sony macros fed by a LOCAL pointer (`T *m = &SYM;`) — a direct `&SYM` argument becomes a reload
register instead (try both: the siblings in this TU need the direct form, a3).

(e) Did not work: splitting `x` only (a2: 10); macros with `&D_800AF648` passed directly (s4 12) or
`gte_SetRotTransMatrix(&D_800AF648)` (s5 12). The sweep's R7/R8/R9/R10/R18 moves reached 2 (COUNT) but none
touched the bound variable.

(f) Method: METHOD S103 c1/c8 ("a local REUSED across statement groups … split it") was the row; the allocation table
named WHICH of the two to split in one run. The tree's lever note ("a HARD register that DIES in an insn becomes
local-alloc's suggestion") explained the keepalive, not the swap — the swap was a priority tie-break the pin papered over.
The GTE-macro point came from comparing this TU's three GTE users' targets (a3 vs v0 for the matrix pointer).

(g) Structs: no for the lever (the decision is allocation priority of two scalar locals). The `buf` -> struct `w`
rewrite is byte-neutral here (the GTE macros take the addresses; no aggregate-vs-scalar aliasing decision involved).
