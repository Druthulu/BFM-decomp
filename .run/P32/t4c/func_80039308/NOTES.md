# main:func_80039308 (src/800_c.c, 518 ins) — T4b HAND PASS, S84 (2026-09-06) — PLATEAU at 4 (verdict, not a bank)

Current best draft: `.run/P32/t5x/fable/func_80039308.c` — rtu DIFF 4 in the real TU (rows 49/50 preheader swap, rows 412/415
`lhu/sh $t0` vs `$s7`). Fable's Y4 (`.run/P32/t5x/work/func_80039308/v_Y4.c`, direct `*(s16 *)(p + 6) = arg1`) is REGISTER-EXACT on
412/415 (`lhu $s7,X($sp)` / `sh $s7`) and is the natural spelling; its residual is the frame: target `[arg1 spill @0x0][8 bytes, no
traffic @0x8][cnt @0x10]` (frame 0x40), Y2 gives `[arg1 @0][cnt @8]` (0x38), Y4's dead `u16 sav[4]` lands at 0x0 and pushes arg1 to 0x8.

## The phantom slot — producer census (§501-M applied; every row read from the dumps)
The draft's `.greg`: `Spilling reg 23. Register 95 now on stack.` then `Spilling reg 65.` — `cnt` (95) is global-allocated to `$s7`,
`order_regs_for_reload` picks `$s7` as the GR spill register (the least-used register in a function that uses every GPR), `spill_hard_reg`
evicts 95 (its retry fails: it conflicts with 50 allocnos and `$v0/$v1/$a0/$a1/$s2`), `alter_reg(95, 23)` → `spill_stack_slot[23]` = cnt's
slot, allocated AFTER the initial `alter_reg` loop. So the target's `[arg1 @0][X @8][cnt @0x10]` needs X allocated between the initial
loop's arg1 slot and the `$s7` eviction — i.e. an INITIAL-LOOP slot (any regno > 73) with no traffic, or a main-loop slot before the
first spill (reload1.c:879). Refuted on this function:
| producer | why not here |
|---|---|
| caller-save area (caller-save.c:249) | leaf function, 0 calls → every `reg_n_calls_crossed` = 0 → `caller_save_needed` never set |
| `spill_stack_slot[65]` (a LO-evicted product whose retry fails) | GR_REGS is spilled before LO_REG (draft trace), so it would land AFTER cnt's slot; and a product's alternate class is `GR_REGS` (C3: two overlapping products → `mflo $a1`/`$v1`, both allocated) |
| reload1.c:879 (invalid REG_EQUIV address) | needs an UNALLOCATED single-block pseudo with a MEM equivalence through a spilled pseudo; local-alloc allocates every single-block pseudo here (the `k2 = sav[0]` temp gets `$t0` — `$t0` is free at idx 444 because s18 dies at 443) |
| expand-time local (`u16 sav[4]`, `pad[2]`) | precedes every reload slot: Y1/Y3/Y4 measured arg1 at 0x10/0x8 |
| global's local-alloc kick-out (global.c:1100–1160) leaving an unallocated local | its traffic would be visible unless def/use are adjacent through `$s7`; the only adjacent `$s7` pairs are the six `mflo $s7` products, which are LO-class global allocnos (not local qtys) — and C3 shows products never fail |
| combine ghost (newi2pat split → `ST_REGS or none`) | needs a signed narrow load whose narrow value is still live: all 13 `lh` in the target are single-use (`bne`, `mult`, `sll`, `addiu`, `slti` consumers), `pan`'s four uses sit in four blocks (a HImode `pan` would leave real `sll/sra` in the arms — the target has none), no `lb`; `b4`'s `lbu` folds to the `addu $v1,$s4,$zero` copy via `nonzero_bits` (2-insn merge, refs zeroed) |
`tools/ghost_census.py` on the draft, Y2, Y4 and C3: no ghosts. **Verdict: the phantom slot's producer is not identified; the Y4 form is
the natural one and the whole 412/415 residual is this slot's offset.**

## Rows 49/50 (`addiu $s3,$zero,2` before `sll $s2,$s5,8`)
Read from `.loop`: both are `move_movables` hoists in the target — the `2` (first used in the innermost loop's `*t1 == 2` compare) precedes
`vbase = b2 * 0x100` because movables are spliced in body order, so the original computed `vol = b2 * 0x100` IN THE BODY (hoisted), not in
the preheader. Fable's X2 (unpinned vbase in the body) measured 515 ins / 495: the `$18` pin is load-bearing for the callee-saved bank once
vbase is a hoisted movable; the steering of a hoisted invariant to `$s2` without a pin (§501-E launders) is the open lever.

## Measured this session
| variant | change | result |
|---|---|---|
| c0 (draft) | — | 4; frame 0x40 = sav[8] 16 + cnt 8; no ghosts; `Spilling reg 23` evicts 95 |
| cY4 / cY2 | Fable's direct-arg1 forms | frame 0x40 (`sav[4]` at 0x0) / 0x38; unallocated at reload entry = {73, 95}; no ghosts |
| c3_twoprod | Y2 + `pa = v*A; pb = v*B;` before both shifts | 434 ins, frame 0x38, products in `$a1`/`$v1` (alternate class wins), no slot |

Next levers (not tried): a movable-invariant `vol = b2 * 0x100` in the body with §501-E launders to hold `$s2`; for the slot, a
register-only 3-insn chain that combine folds into one insn with a live head (path (b), §501-M) — no such chain exists in this
function's target shape (every `and/sll/addu` triple is already at its folded form).
