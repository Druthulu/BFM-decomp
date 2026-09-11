# func_8018431C (src/ov_SC03_104/ov_SC03_104_jr_80182038.c) — CLOSED, score 0 (agent c38, S103)

Final body: `PACK/body.c` (= `scratch/c/v10.c`). Byte-identical per `--try` (score 0) and per a full `objdump -drz` diff of
the `--keep` candidate object against `.run/P36/delever/baseline/src/ov_SC03_104/ov_SC03_104_jr_80182038.o` (relocations
included). No pin, no asm, no volatile, no new local: the `dptr` local is GONE.
The same move with the local kept (`dptr = D_801C00F0; *(u32 *)(s1 + 0x20) = (s32)dptr;` first) also scores 0
(`scratch/c/v9.c`); v10 was kept because it is shorter and reads the way the rest of the block does.

## (a) Residual
150 vs 150, same registers. ONE instruction (the `la $a0,D_801C00F0` pair, `lui`+`addiu`) sits 5 slots lower in mine:
after `li v0,120` instead of right after the `jal func_8001CF00` / `move a0,s1`. COUNT first: nothing missing, nothing
extra, no register differs, so this is a scheduling residual. Arities checked first as the brief asks: every callee's real
definition (`src/800.c`, `src/800_b_2.c`, `src/shared/ov/*.h`) matches the call; no casts in this body.

## (b) Pass and decision (read in `scratch/dumps_f0` vs `scratch/dumps_tr` vs `scratch/dumps_v10`)
- **sched1, the birthing boost.** `schedule_insn` gives each newly-ready insn `adjust_priority` (sched.c:2507);
  `birthing_insn_p` (sched.c:2469, gate `:2489-2490`) returns true for a SET of a live REG with `reg_n_sets == 1`, and the
  insn is raised to `max_priority` = LAUNCH_PRIORITY 0x7f000001 (sched.c:2572-2575, 187). sched1 schedules BACKWARD, so a
  boosted def is emitted immediately above the consumer that made it ready. In `body_free` the address pseudo (reg 103) is
  single-set and its only in-block consumer is the `sw` to `+0x20`, the 4th store: `.sched` shows
  `ready list at T-11: … 131 (7f000001)`, so the `la` lands just above that `sw`.
- The tree's `register … __asm__("$4")` pin faked the fix: a hard register has `reg_n_sets > 1` (every call's argument
  setup sets `$4`, flow.c:2047), so the pinned `la` is never boosted (`.sched` of the pinned copy: `131 (1)`) and falls to
  its LUID position, first in the block. A scratch-only re-tie `__asm__("" : "=r"(dptr) : "0"(dptr))` after the load
  (reg_n_sets 1→2) also scores 0 (`scratch/c/proof_retie.c`): that proves the boost is the whole residual. It is a lever,
  not a close.
- **sched2 decides where the stores end up.** After reload there is no boost (`reload_completed`), and among ready insns
  of equal priority `schedule_select` (sched.c:2616, choice `:2657-2670`) takes the one with the largest
  `potential_hazard` (memory-unit spacing). That is what spaces the independent `s1`-relative stores between the
  `li`s: in `.sched2` for v10, `insn 132 has a greater potential hazard` pulls the `sw +0x20` back into the store run,
  in 4th place, where the target has it. So the store's SOURCE position does not survive; the `la`'s sched1 position does,
  because sched2's LUID tie-break (sched.c:2425-2428) reads sched1's output order.

## (c) Move
Write the `+0x20` store FIRST after `func_8001CF00(s1)`, storing the symbol directly:
`*(u32 *)(s1 + 0x20) = (s32)D_801C00F0;`, and pass `D_801C00F0` to `func_800233CC` directly (cse gives both uses one
pseudo). The boosted `la` is now emitted above the FIRST store, i.e. at the top of the block, and sched2 moves the `sw`
back to 4th. One statement moved, one local deleted.

## (d) Generator proposal
When a single-set constant/address load (`la`/`li`) sits LOWER in its block than the target and its first in-block
consumer is one of a run of independent stores, move that consumer store to the head of the run (folding the variable into
it if that is its only other use): sched1's birthing boost puts a single-set def directly above its first-scheduled
consumer, and sched2's potential-hazard selection re-spaces the stores, so only the def's position changes.

## (e) What did not work (byte evidence, all `scratch/c/`)
- v1 (reuse the parameter `a0` as the pointer, for a second set): 4. combine merged the entry copy into `s2 = a0` and
  deleted it, so reg_n_sets was 1 again.
- v2 (share one `s32` temp between the pointer and `func_800291B4`'s result): 4. combine.c folded the call-result copy
  into its one use (the `& 0xFF` test), which deleted the second set.
- v3 (share `p` from the other branch): 71. The one pseudo now crosses `func_8001CB6C` and needs a callee-saved register.
- v4 (symbol used directly, store left 4th): 4. v5 (assign before the call): 19, it crosses the call.
- v6 (`dptr = s1` as `func_8001CB6C`'s argument in the other branch) and v7 (a repeated `dptr = D_801C00F0` before the
  call): 4. cse canonicalises / deletes both second sets (make_regs_eqv cse.c:846-862; a no-op set).
- v8 (re-read `*(u32 *)(s1 + 0x20)` for the call): 14, 151 instructions. One extra instruction appears; I did not dump it
  to see whether that is an unforwarded `lw`.

## (f) Method notes
- My first prediction was WRONG and the bytes corrected it: I reasoned that moving the store would move the `sw` in the
  output, since sched1 keeps independent stores in LUID order. That holds for sched1 only; sched2's
  `schedule_select` hazard choice re-spaces them. The move I had written off as "breaks the store order" was the close.
  Lesson for the method: on an ORDER residual, read BOTH `.sched` and `.sched2` traces (`grep 'ready list at\|hazard'`
  inside the block) before ruling out a statement move. A sched1-only argument proves nothing about the final order.
- 8 copies of this body (siblings in ov_SC03_089/090/091/092/097/101, ov_SC02_028) carry the identical `dptr` pin; the
  same move should close all of them (not tested — read-only brief).
