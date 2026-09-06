# md_MAIN_003:func_800CF3E8 (469 ins) — Fable T5x: **MATCH** (leaf `match_one` 469/469, real-TU `rtu_match` MATCH)

Draft: `.run/P32/t5x/fable/func_800CF3E8.c` (= work `v_X5.c`). Alternate byte-identical drafts: `v_C1.c` (adds the S83 pointer
launder), `v_X4.c` (tag read spelled at the chain). Baseline reproduced first: prior best 27 @ 469; S83 launder variant 79 @ 470.
Relocation audit: all 20 data symbols present with the target's exact counts (`relocs_mine.txt` vs `relocs_target.txt` in the work dir).

## The mechanism, as READ from the dumps (all in `.run/P32/t5x/work/func_800CF3E8/rtl_*/t.i.{sched,sched2,lreg}`)
Both prior reports located the residual in the right window (the p6 tag load at 380 vs 399/384) but attributed the placement to
cse/sched1 alone. The dumps show THREE passes each contributing one defect, and the row closes only when all three are fixed:

1. **sched1: the tag load was BIRTHING-BOOSTED.** In the launder variant's `-dS` the load (insn 1182) is `7f000001` in the
   ready list at T-73 and is picked the instant its consumer is placed — `adjust_priority` (sched.c:2507) → `birthing_insn_p`
   (:2469, `reg_n_sets == 1`, dest live). A boosted load sinks to just before its use; NO source spelling moves it while the boost
   is alive (this is why S83's 14-position `tag6` birth sweep and the 32-position hoist sweep were inert).
   **Lever: a second LIVE set of the loaded pseudo — `tag6 = *(u32*)p6; … tag6 &= 0xFF000000;`** (compound assignment reuses the
   variable's pseudo as the `and`'s dest: `(set (reg 81) (and (reg 81) (reg mhi)))`). reg_n_sets = 2 → priority 6 in `-dS`
   (`v_A` trace: "1121 (6)"), and sched1's output becomes `sb len, [tpage addr], sw tpage, lw tag, lui m24, sb code, lbu, ori m24,
   x0 y0 u0 v0 clut w h, colour×3, sll, la, addu ot, lui mhi, lw *ot, and tag, and otv, or, sw` — the tag load is now ahead of
   `sb code`/`lbu` in LUID order. (Same gate as §501-C/§501-D; the compound form keeps the variable single-death/local, unlike the
   `__asm__ volatile("" : "=r"(x))` dial, which measured 39 here — it makes the tag a 2-death global allocno.)

2. **sched2 decides the FINAL slot, not sched1.** Post-reload both the load `(mem:SI (reg 3))` and the field stores
   `(mem/s (plus (reg 3) N))` share the hard base, `memrefs_conflict_p` disambiguates, and the unit-hazard rule "a load is blocked
   for 1 cycle right after a store" (`-dR`: `blocking insn 1182 for 1 cycles` at every store pick) walks the load upward past every
   consecutive store; it stops where it loses a LUID tie to `lbu`(1130)/`sb code`(1125) — which is exactly what (1) fixes.
   Two more sched2 facts, both byte-verified:
   * the S83 +1 `nop` was the ot-USE phantom `__asm__("" :: "r"(ot))` (insn 1179): in sched2 it ties `and tag` at priority 7,
     wins on LUID (sched1 parked it at the block end), and is picked between `lw *ot` and `and otv` — a zero-byte insn filling the
     load-delay slot in the MODEL only, so gas emits a real nop. **Remove it** (re-adding it: 70 @ 470, ablation X2).
   * `lui m24` lands at 378 (between `sb $a2,3($v1)` and `sw tpage`) purely from its sched2 anti-dependence on `$a2` (c5's last
     use) + the ALU-vs-memory hazard order — which requires m24 to BE in `$a2`, i.e. the allocation below. The fence
     `__asm__("")` after the tpage store must go (everything after a traditional asm depends on it, so `lui m24` could never reach
     378; re-adding it: 8 @ 469, ablation X3). The fence BEFORE p6's birth stays (removing it: 461 @ 471, ablation X6).

3. **local-alloc: m24 must out-rank mhi.** `qty_compare` (local-alloc.c:1579) = `floor_log2(n_refs)·n_refs·size/(death−birth)`
   with birth/death from the POST-sched1 positions and `n_refs` from flow (flow.c:2067/2315/2501/2711 — written BEFORE combine;
   combine.c:56 documents that it does not adjust them). With the hand-written `(x & 0xFF000000) | (y & 0xFFFFFF)` macro both
   masks have 13 refs; mhi's boosted `lui` sinks to the chain (born at 344) while m24's is born at 327, so mhi's range is 16
   shorter → mhi is allocated first and takes the lowest free register `$a2` (`v_A` lreg: `Register 452 in 6`, m24 `455 in 10`,
   tag `81 in 8`) — the target needs m24→`$a2`, mhi→`$t0`, tag→`$t2`.
   **Lever: spell the OT link the way libgpu does — the `P_TAG` bitfield `setaddr(p, getaddr(ot)); setaddr(ot, p)`.**
   `store_fixed_bit_field` (expmed.c) re-masks the already-masked value with `0xFFFFFF` (`must_and`), an `and` that cse cannot
   fold (both operands are registers) and combine removes later — but flow has already counted it: m24 gets 3 refs per prim
   instead of 2 (18–19 total, floor_log2 = 4) and its priority roughly doubles → allocated before mhi → `$a2`; mhi then takes
   `$t0`; the tag (range [380,401], overlapping 0xDC/mhi in `$t0`) takes `$t2`; every block-head constant keeps its register.
   Measured: bitfield on prims 5..1 (p6 kept manual): 74 → **2**; the same draft with the manual macro on all six: 74 (B5).
   §364's -O2 warning (a `/s` tag store lets cse drop the OT re-read) does not bite here because BOTH sides of the link are
   `P_TAG` accesses, so the `*ot` re-read is `/s` too and is invalidated correctly — the 469-instruction count is preserved.

4. The last 2 rows (p5 `x0`/`y0` order, 362/363) were the baseline's deliberate `y0; x0` source swap for the old basin; natural
   order (`x0; y0`) closes it: 2 → **MATCH**. (S83 measured the swap at 31 — in the old basin, where it was paid for elsewhere.)

## Ablations on the MATCH (leaf match_one; every one re-measured, not inferred)
| change | result | meaning |
|---|---|---|
| X1: `(tag6 & 0xFF000000)` instead of `tag6 &= …` | 89 @ 469 | the second SET (boost kill) is load-bearing |
| X2: re-add `__asm__("" :: "r"(ot))` | 70 @ 470 | the phantom steals the load-delay slot in sched2 |
| X3: re-add `__asm__("")` after the tpage store | 8 @ 469 | blocks `lui m24` from reaching 378 |
| X4: tag read spelled at the chain (after `ot = …`) | MATCH | source position of the read is NOT load-bearing once un-boosted |
| X5: drop the S83 pointer launder | MATCH (delivered) | with the read spelled before the field stores, the pseudo-base deps pin it anyway |
| X6: drop the fence before p6's birth | 461 @ 471 | §194-A fence still load-bearing |
| B5: manual mask macro on all six prims | 74 @ 469 | the bitfield's redundant `and` (m24 refs) is load-bearing |
| V1/V2: `__asm__ volatile("" : "=r"(tag6))` instead of `&=` | 39 @ 469 | 2-death → global allocno; different basin |

## For the cookbook (proposed §500-H amendment / new §)
* "A load through a pinned base is scheduled late" has THREE owners: sched1's birthing boost (kill with a second live set of the
  loaded variable — compound assignment, zero bytes), sched2's load-after-store hazard walk (the final slot; LUID ties with
  neighbouring memory ops decide where it stops), and local-alloc's `qty_compare` (register roles follow the ranges the new
  order creates). Read `-dS` for `7f000001` on the load, `-dR` for `blocking insn N`, `-dl` for `Register N in R`.
* A zero-byte `__asm__("" :: "r"(x))` USE is not free in the scheduler: it occupies a cycle and can fill a load-delay slot in
  the model only → a real nop from gas. Check the `-dR` ready list around every `lw`/`and` pair before keeping one.
* `reg_n_refs` is flow's count and survives combine: any RTL redundancy that only combine removes (a bitfield's `must_and`
  re-mask, expmed.c `store_fixed_bit_field`) still weights local-alloc's priority. The libgpu `P_TAG` bitfield `addPrim` is
  therefore not just an operand-order lever (§364) but a REGISTER-PRIORITY lever at -O2 for the 0xFFFFFF mask.
