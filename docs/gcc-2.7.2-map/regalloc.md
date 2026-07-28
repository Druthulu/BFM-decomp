# gcc-2.7.2 REGISTER ALLOCATION + RELOAD → residual→C-lever catalog
**Pass group:** `local-alloc.c` (2491) · `global.c` (1714) · `reload.c` (6204) · `reload1.c` (8626), in `tools/reference/gcc-papermario/`.
**Produced:** 2026-07-02 (Phase 23), by source read + `-da` RTL dumps + byte experiments via
`tools/match_one.py <fn> --c FILE --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077`.
**Prime exemplar:** `func_801571C4` (198 ins, `.run/fable/func_801571C4.c`, baseline 11-off); experiment variants in `.run/gccmap/` (`exp1_slotorder.c`, `exp1c_declorder.c`, `exp2_defmove.c`), RTL dumps in `.run/gccmap/dumps/`.
**How to use:** read §A once (the 8 knobs), then triage a diff with §C (tells) → apply the §B lever for the matched class. A cheap agent should never need the gcc source again for these classes.

> ## ⚠️ SOURCE-VERSION AUDIT (Phase 29 SESSION-23, 2026-07-28) — READ BEFORE TRUSTING A CITATION
> **This file was written against `tools/reference/gcc-papermario/`, which is gcc 2.8.1 — NOT our
> 2.7.2** (established Phase 23; vanilla 2.7.2 is staged at `tools/reference/gcc-2.7.2/`). Line
> numbers throughout are therefore for the WRONG COMPILER, and the drift is **large and non-uniform**
> (`combine_regs` +103, `allocate_reload_reg` +377, `choose_reload_regs` +611) — big enough to land
> *inside a different function*. **Re-derive with `grep -n '^symbol ('` before citing anything here;
> do NOT rebase mechanically.**
>
> **The audit:** all 184 citations and claims were re-derived against the real 2.7.2 source by 5
> parallel agents; every REFUTED claim then went to an independent agent whose job was to *refute the
> refutation*, defaulting to upholding the map. Result: **119 CONFIRMED · 40 LINE-DRIFT (mechanism
> intact, number wrong) · 21 raised as REFUTED, of which 14 were OVERTURNED and only 7 stand · 4
> unverifiable.** So **the model in this file is overwhelmingly sound — do not delete levers.** The
> seven real corrections are marked **[A23]** inline below. Two were byte-proven against the real
> `cc1`, not just read.
>
> **The 7 corrections, in descending consequence:**
> 1. **K4 `flag_caller_saves` is ON, not off** (`toplev.c:3387-3394` sets it at `optimize >= 2`;
>    proven by compiling with/without `-fno-caller-saves` on the pinned cc1 → different code). A
>    call-crossing value is NOT restricted to `$s0-$s7`-or-spill. **Diagnostic that was missing:
>    caller-save slots are 4-BYTE-PACKED (16,20,24,28) while reload spill slots are 8-ROUNDED
>    (16,24,32) — misreading one for the other sends you to RC-1 and decl reordering, the wrong lever.**
> 2. **RC-7's premise is false: `&sp_buffer` is NOT a "rematerializable constant".** `CONSTANT_P`
>    (`rtl.h:237-240`) admits only LABEL_REF/SYMBOL_REF/CONST_INT/CONST_DOUBLE/CONST/HIGH — a frame
>    address is `(plus (reg vsv) K)`, a PLUS, which never qualifies, so it gets a real slot + `lw`.
>    Only SYMBOL_REF/CONST_INT equivalences get the no-slot remat. *(Independently corroborated by a
>    byte-test the same day: the cse_expr.md §2 remat recipe provably fails to dissolve a frame-address
>    hoist seeded by a struct copy — see `.run/near6/f132F40_v*.c`.)*
> 3. **The "init MOVED to just before its use" pass does not exist in 2.7.2.** That is 2.8.1-only
>    (papermario `local-alloc.c:1236-1265`); 2.7.2's `update_equiv_regs` substitutes the equivalence
>    into the use and **DELETES** the init (`local-alloc.c:1090-1116`). The diagnostic built on it
>    tests for a pass we do not have.
> 4. **K2 refs are LOOP-DEPTH-WEIGHTED**, not per-insn-mention: `flow.c` does
>    `reg_n_refs[regno] += loop_depth`. Hand-computed densities are wrong inside loops — read the
>    `.lreg` number instead.
> 5. **K1: qty numbers come from BIRTH order, not regno order.** `alloc_qty`/`next_qty++` run during
>    the forward block scan (`local-alloc.c:284`). Regno order governs allocnos and spill slots only.
> 6. **RC-15/K2: `allocno_live_length` is the DENOMINATOR** (`global.c:594-597`) — priority is a
>    *density* (refs per insn of life), so a LONGER live range LOWERS priority. The map had the sign
>    of that term wrong.
> 7. **Pins do NOT kill the sched S2 birthing boost** (see §F below, and the same correction landed in
>    `sched.md` the same day). `birthing_insn_p` (`sched.c:2469`) tests only
>    `GET_CODE (SET_DEST (pat)) == REG` — hard regs qualify; the discriminator is `reg_n_sets == 1`
>    (`:2490`). Decisive: `sched.c:423` in the SAME FILE *does* add
>    `>= FIRST_PSEUDO_REGISTER` when it wants pseudos only, so the omission at `:2478` is deliberate.
>
> **Hand-verified 2.7.2 anchors** (`grep -n '^sym ('`): `allocno_compare` **586** (priority expr
> 594-597, tie-break `return *v1 - *v2` **609**) · `find_reg` **904** · `global_conflicts` **613** ·
> `update_equiv_regs` **947** · `block_alloc` **1123** · `combine_regs` **1722** · `alloc_qty` **279**
> · `find_free_reg` **2072** · `alter_reg` **2309** · `allocate_reload_reg` **4706** ·
> `choose_reload_regs` **4903** · `validate_equiv_mem` **559**.

---

## §A The decision machinery — 8 knobs everything below reduces to

Pass order (relevant slice): `flow → combine → sched1 → local_alloc → global_alloc → reload → sched2 → dbr`.
**sched1 rewrites the life data regalloc consumes** (`sched.c:5067` `REG_LIVE_LENGTH(regno) = sched_reg_live_length[regno]`) — this is the exact channel by which instruction placement flips allocation (K2 below). Any scheduling lever (cookbook §30 birthing-boost, statement order) is therefore ALSO a regalloc lever, and vice versa.

- **K1 — Pseudo creation order.** Params get pseudos first, in PARAMETER-LIST order (`function.c:assign_parms`); then user locals in **DECLARATION order** (pseudo made when the decl is expanded at block entry — **NOT at first assignment**; byte-proven, §B RC-1); compiler temporaries interleave at first need. Creation order is the tie-break for K2, the qty tie-break (`local-alloc.c:1745`→2.7.2 `qty_compare_1`, `return q1 - q2`), the allocno tie-break (`global.c:616`→**2.7.2 :609** `return *v1 - *v2`), and the **spill-slot order** (K7). **[A23] "creation order (= regno order)" is only half right:** qty numbers are handed out by `alloc_qty`/`next_qty++` during `block_alloc`'s FORWARD block scan (`local-alloc.c:284`, scan starts `:1165-1169`) — i.e. **BIRTH order**, which equals regno order only when the pseudos are first touched in declaration order. Regno order genuinely governs allocnos (`global.c:397`) and spill slots (K7).
- **K2 — Density priority.** Both allocators use the same formula:
  `pri = (int)(((double)(floor_log2(n_refs) * n_refs) / live_length) * 10000 * size)` — `global.c:594 allocno_compare` (per-allocno, REG_LIVE_LENGTH from flow/sched1) and `local-alloc.c:1727 QTY_CMP_PRI` (per-qty, birth→death insn indices). Higher density allocates FIRST. It is `int`-truncated; exact ties fall back to creation order (K1). **Shrinking a live range raises priority** — **[A23] `allocno_live_length` is the DENOMINATOR** (`global.c:594-597`), so priority is a *density* and a LONGER live range LOWERS it; that is why shrinking works. **[A23] refs are LOOP-DEPTH-WEIGHTED, NOT per-insn-mention**: `flow.c` does `reg_n_refs[regno] += loop_depth`, so a mention inside a loop counts for more than one. **Hand-computing a density inside a loop gives the wrong answer — read the `.lreg` `Register N used R times across L insns` line instead.** Moving a def later (or a last use earlier) is still the lever.
- **K3 — Hard-reg scan order.** MIPS defines **no REG_ALLOC_ORDER** (`config/mips/mips.h`) → every scan is plain regno order: `$v0,$v1,$a0..$a3,$t0..$t7,$s0..$s7,$t8,$t9,$fp`. First fit wins. So: first callee-saved allocno → `$s0`, next → `$s1`, …; local temps → lowest free scratch (`local-alloc.c:2176 find_free_reg`, over the qty's birth–death window `regs_live_at`).
- **K4 — Call-crossing ⇒ callee-saved only.** `global.c:917-922` / `local-alloc.c:2205-2209`: an allocno/qty with `calls_crossed > 0` excludes ALL of `call_used_reg_set` ($v0–$t9) **on the first attempt**. ~~PSX gcc has `flag_caller_saves` off → no save/restore fallback.~~ **[A23] FALSE — `flag_caller_saves` is ON for us.** `toplev.c:3387-3394` sets it inside `if (optimize >= 2)` and we build `-O2`; byte-proven on the pinned `cc1` (compiling a pressure-heavy function with vs without `-fno-caller-saves` gives different code; the `-O2` default emits `sw $3/$8/…` immediately before `jal` and matching `lw`s after — artifacts in `.run/regalloc_audit/A-machinery/{cs.c,on.s,off.s}`). So when `CALLER_SAVE_PROFITABLE(REFS,CALLS)` = `4*calls < refs` (`regs.h:165`) holds, `global.c` / `local-alloc.c` **retry with `accept_call_clobbered=1`** and a call-crossing value CAN live in a caller-saved reg with save/restore around the call.
  **[A23] THE DIAGNOSTIC THIS FILE WAS MISSING — caller-save slots are 4-BYTE-PACKED (0x10,0x14,0x18,0x1C), reload spill slots are 8-ROUNDED (0x10,0x18,0x20).** A packed run of `sw`/`lw` hugging a `jal` is a caller-save, NOT a spill: reading it as RC-1 and starting to reorder declarations pulls entirely the wrong lever.
  Whether a value crosses a call is still decided purely by def/last-use placement in the (post-sched1) insn stream.
- **K5 — Two-pass frugality + preferences.** `global.c:900 find_reg`: pass 0 excludes regs not in `regs_used_so_far` ("never allocate a register for the FIRST time in pass 0", `:945-948`) and regs someone else prefers; pass 1 opens fresh regs. ⇒ gcc reuses already-dirty regs before opening a new callee-saved (minimal `.mask`). Copy preferences (`global.c:1538 set_preference`, from moves to/from hard regs — param copies, retval copies, pinned-var copies) can override the scan-order winner within the class (`:1000-1065`). Local-alloc analog: a move touching a hard reg records `qty_phys_copy_sugg` (`local-alloc.c:1905-1945`), and suggested qtys are allocated before all others (`:1593-1625`, fewest-suggestions-first).
- **K6 — The eviction rules ("something else spills").** `global.c:1105-1160`: an allocno that finds no free reg may KICK OUT everything local-alloc put in some call-clobbered reg, iff `local_reg_n_refs[r]/local_reg_live_length[r] < allocno_n_refs/allocno_live_length` — scanning from the HIGHEST regno down. Reload's version: `reload1.c:3840 order_regs_for_reload` sorts spill candidates by total pseudo refs; the least-referenced reg is confiscated and its pseudos go to `retry_global_alloc`/stack.
- **K7 — Spill slots.** `reload1.c:779` assigns slots by looping pseudos in **regno order** (= K1 creation order) through `alter_reg` (`:2471`): one fresh slot per spilled pseudo (never shared for `from_reg == -1`), `total_size = MAX(inherent, reg_max_ref_width)`; if a narrow pseudo (HImode u16) is ever referenced via `subreg:SI`, `reg_max_ref_width=4 ≠ 2` → `assign_stack_local(size, -1)` → `function.c:697-700`: align/round to `BIGGEST_ALIGNMENT/8 = 8` (`mips.h:1271`) → the **8-rounded slot** (0x20, 0x28, …). A pseudo with `reg_equiv_constant`/`reg_equiv_memory_loc` gets **no slot** (rematerialized) — see RC-7.
- **K8 — Local vs global split & tying.** local-alloc handles only pseudos with `REG_BASIC_BLOCK >= 0 && REG_N_DEATHS == 1` (`local-alloc.c:472`) — single-block, dies once. It TIES (coalesces) op0's dest into a dying input at the dest's FIRST set (`:1360-1450` → `combine_regs :1825`; conditions: dest has no qty yet, input dies here, classes/modes compatible). **global.c has NO coalescing at all** — only the K5 preferences. ⇒ any cross-block register sharing in the target means the ORIGINAL RTL had one pseudo there: your C must express it as ONE variable (or an in-place update), not a copy.

**Reload's own knobs (all downstream consequences):**
- Spill/reload reg identity = the **first wholly-UNUSED call-clobbered reg in regno order** (`order_regs_for_reload :3922-3932` unused+call_used first, then unused callee-saved, then by ascending use count `hard_reg_use_compare :3822`). In arg/temp-busy functions that is **$t0** — hence the `lhu/sh $t0` tell. Explicitly-used regs (from `register __asm__` pins!) get `uses += large+1` AND `bad_spill_regs` (`:3900-3915`) → **a pin on $t0 moves every reload artifact to $t1 function-wide** (byte-verified, §B RC-5: "Spilling reg 8" → "Spilling reg 9").
- With ≥2 spill regs, per-insn choice is **round-robin** from `last_spill_reg` (`allocate_reload_reg :5083`) — history-dependent: one extra/missing reload upstream rotates every later reload-reg choice. Don't chase these; fix the upstream count.
- **Inheritance:** a later input reload of the same pseudo reuses the still-live spill reg with NO new `lw` (`choose_reload_regs :5514-5590`, `reg_last_reload_reg`/`reg_reloaded_contents`; invalidated at labels/jumps and at any clobber of the spill reg).
- **delete_output_reload** (`:7274`): the `sw` back to the slot is deleted when the pseudo is dead after the insn and unmentioned in between — why a final-use spill access can be load-only, and why a dead-at-end pseudo's re-set emits nothing (571C4 idiom 2).
- Reload insns for one insn are emitted bucketed by type and **operand number** (`emit_reload_insns :5977`) → the `lw/lhu` order before an insn follows source operand order.

---

## §B Residual-class catalog

### RC-1 — Spill-slot offsets wrong / swapped (`sh $t0,0x28` vs target `0x20`) — **STEERABLE**
- **Decision point:** `reload1.c:779` slot loop (regno order) + K1 creation order.
- **Lever: reorder the DECLARATIONS of the spilled locals** (and, for param-fed spills, know that the surviving pseudo order is the PARAMETER order). Statement/assignment order is a **NO-OP** for declared locals — pseudos exist before the first statement runs.
- **Byte-proof (func_801571C4):** swapping the two assignments `local_40 = a2; local_38 = a10;` → **identical bytes** (11-off, unchanged; `exp1_slotorder.c`); pseudo stats in `.lreg` identical. Swapping the two **declarations** `u16 local_40; u16 local_38;` → 15-off with EXACTLY the four slot accesses flipped `0x20↔0x28` (idx 20/23/97/145; `exp1c_declorder.c`). So: to move a spill slot, move the decl.
- **Slot SHAPE (8-rounding + $t0 access) — the companion lever (already proven in the 571C4 draft):** a value the target accesses as `lhu/sh $t0, 8-rounded-slot` must be a **plain u16/s16 local** (a genuinely SPILLED pseudo, K7); a value accessed via `$v0`-line scratch regs is a **local-alloc temp**; a value with per-use `addiu $sp` address math is a **source-level MEM** (array/struct). Choosing the C shape chooses the class — a Ghidra-draft `*(u16*)&sp[..]` MEM shape can NEVER reproduce a spilled-pseudo access pattern.

### RC-2 — Wrong value spilled / wrong value in a callee-saved ("$aN spilled", value stuck on stack) — **STEERABLE, double-edged**
- **Decision point:** `global.c:594 allocno_compare` density (K2) + `find_reg` eviction (K6); live lengths written by sched1 (`sched.c:5067`).
- **Lever: move the def later / the last use earlier (in source order) to SHRINK the pseudo's live range and raise its priority** — or the reverse to lower it. Every insn the range crosses counts; crossing/not-crossing a call also flips K4 eligibility entirely.
- **Byte-proof (func_801571C4, `exp2_defmove.c`):** moving `local_40 = a2;` from before to after the first call shrank reg88's range 94→89 insns → its priority rose past the marginal allocno → **it flipped from SPILLED to $s7** and evicted the `a3` param to the stack (`sw $a3,0x20($sp)/lw $a1,0x20($sp)` in the diff; dispositions in `dumps/exp2.i.greg`: base has no `88 in …` + `77 in 30`; exp2 has `88 in 23` + 77 gone). match_one 11 → 137 mismatched. **Read the direction from the dumps, not by guessing:** `.lreg` lines `Register N used R times across L insns` give you every contender's (R, L); compute `floor_log2(R)*R/L` to see who is marginal and how far. A ~5% length change flipped this one.
- **Coupling warning:** any construct that changes an insn's position for the scheduler (comma-defs, extra temps, barriers) changes L for every pseudo whose range spans it. This is why §30's zero-code `__asm__` re-tie can still flip allocation: it adds a REF and (if placed inside a range) lengthens nothing but raises R. 571C4 idiom 2's margin note stands: the same dead-asm trick was priority-safe on `local_40` but flipped the allocation when applied to `local_38` — **after every such edit, re-run match_one; check the dumps if it exploded.**

### RC-3 — Callee-saved ORDER permutation ($s0/$s1/$s2 assignments shuffled) — **STEERABLE**
- **Decision point:** allocation ORDER = descending K2 priority; each takes the lowest free callee-saved (K3), pass-0/1 (K5); ties → creation order (`global.c:616`).
- **Primary lever (byte-proven, cookbook §17): `register s32 v __asm__("$16..$23")` pins on each call-crossing value**, mapped from the target `.s` (flagship func_8012B8E4, ×134). Pins short-circuit the whole priority contest.
- **Zero-cost pre-check before pinning:** if two contenders' `.lreg` (refs, live-length) are IDENTICAL, the swap is a pure K1 tie — **swap their declaration order** instead of pinning (no `regs_explicitly_used` side effects, RC-5). If densities differ, a decl swap does nothing (verified: unequal-density micro-case is order-stable) — use pins or RC-2 range shaping.
- **Diagnostic:** allocation order is readable directly: in the target prologue, the FIRST-allocated allocno is the one in $s0, etc. Compare with your draft's `.greg` "Register dispositions" line to see which pseudo won each hard reg.

### RC-4 — Copy-coalescing: a `move` vanishes into an operand, or arithmetic routes through the copy's reg — **STEERABLE**
- **Decision point:** `local-alloc.c:1825 combine_regs` tying (K8): at the dest's first set, if a source operand DIES there, they share a qty.
- **Lever (byte-proven, cookbook §25, func_80128ED8):** (a) **pin the preserve-copy to the target's register** — a hard-reg dest can't be tied (`combine_regs` refuses hard↔hard and only *suggests* for hard↔pseudo) → the copy materializes separately, exactly where the target has it; (b) **route the dependent arithmetic through a dead, target-scratch-pinned temp** so the result lands in the target's scratch instead of the copy's reg.
- **Un-tying without pins:** the tie needs (dest-first-set ∧ source-dies-here). Either give the source a later use (kills the REG_DEAD) or give the dest an earlier set (kills first-set). A dead second read of the source after the copy (`__asm__ volatile("" :: "r"(src))` — zero code) breaks the tie at zero cost, but counts a ref (RC-2 margin check applies).
- **Reverse direction (target DID tie, your draft has an extra `move`):** express the two C variables as ONE (reuse the variable in place) so expand emits a single pseudo — per K8 global has no coalescing, so a cross-block "merge" can only come from a shared pseudo in the original source shape.

### RC-5 — Pin side-effects: when a `register __asm__` pin is byte-clean vs when it cascades — **characterization (the §17 caveat map)**
A pin makes every ref of the variable an explicit HARD reg from RTL-expansion onward. Four separable side-effect channels — check each against the target before pinning:
1. **The init copy.** `pinned = expr` computes DIRECTLY into the hard reg (no copy). `pinned = other_var` emits a real `move` — it dissolves only if local-alloc can put `other_var` in the same reg (block-local, dies at the copy, window free → self-move deleted). If the source is call-crossing/multi-use, the move STAYS. ⇒ **pin is byte-clean iff the target shows the same copy** (e.g. the ABI param save `move $s0,$a0`) **or the source qualifies for the dissolve.** The 571C4-P6/func_801770E0 "pin-copy insns the target lacks" cases are exactly pins whose init source was a value the target's allocator had tied.
2. **Reload-pool poisoning (byte-verified, `dumps/exp3.c`):** `regs_explicitly_used[r]` → `bad_spill_regs` (`reload1.c:3900-3915`). A dead top-of-function pin of `$8` flipped the dump from "Spilling reg 8" to "Spilling reg 9" — every `lhu/sh $t0` became `$t1` **function-wide**. ⇒ never pin the function's reload reg (usually $t0) unless the target shows non-$t0 reloads; conversely, if the TARGET reloads via $t1 while YOUR draft says $t0, the original source likely used $t0 explicitly — or another spill preceded (round-robin).
3. **Pass-0 availability shift:** an explicit `$sN` sets `regs_ever_live[N]` → `$sN` is "already dirty" in `find_reg` pass 0 → OTHER allocnos that don't conflict may now grab it earlier, re-shuffling the whole callee-saved order. This is why over-pinning "2/3/9 winners" cascades (571C4 header): each pin re-ranks the remaining contest.
4. **Range blocking:** the pinned reg is live (for local-alloc) over the pinned var's def→last-use; if the target reuses that architectural reg for another value inside your pin's scope, that value is forced elsewhere (func_801770E0: scratch pins cost `pCval` its `$s1` reuse → fresh `$s6` + frame change). **Lever: narrow the pin's scope** — inner-block `{ register … }` or reuse an already-dead pinned temp (§25's proven move).
**Verdict rule:** pin exactly the registers whose target live ranges you can see, one at a time, re-running match_one after each; a pin that regresses the count is hitting channel 2/3/4 — remove it and treat via RC-2/RC-4 levers or RC-6.

### RC-6 — Pressure-locked flat allocation (coalescing knife-edge) — **INTRINSIC → decomp-permuter (with a stabilizing pin)**
- **What it is:** straight-line, high-pressure code whose values chain through calls (`v = f(v,…)` repeatedly) with register pressure ≈ available regs. Every dest ties to a dying input (K8), so the allocation is one long tie-chain; `block_alloc` indexes births/deaths by insn number, so ANY source edit (barrier, temp, reorder) moves REG_DEAD notes → different ties → different `regs_used_so_far` → different global pass-0 → different reload order. The whole solution re-derives; there is no local fix.
- **Why it's intrinsic:** the residual is not a mis-decision to steer — the regalloc is EXACT (func_801770E0, func_8014EA4C both have every register right) — it's that the remaining schedule diff cannot be touched without collapsing the allocation. The C-source space around the target is discontinuous.
- **Route:** decomp-permuter, after **pinning ONE anchor value to stabilize the callee-saved core** (byte-banked finding on func_801770E0: `register u32 param_2 __asm__("$18")` holds param_2→$s2 so the permuter can perturb scheduling without the alloc cascading). Exemplars: func_801770E0 (53-off floor, all toolkit levers fail with cascades), func_8014EA4C residual-B (abs phi-copy, 22 formulations swept, every pressure-changing form triggers DSE→frame shrink).
- **Recognize it:** match_one diff where registers/opcodes are all correct but a block of insns is PLACED differently, AND every small C edit changes 20+ instructions instead of 1-3. Two probes = enough; don't grind.

### RC-7 — Rematerialization vs spill/hoist (per-use `addiu $sp` vs callee-saved base; constant re-`li` vs slot) — **STEERABLE**
- **Decision points:** `local-alloc.c:1007 update_equiv_regs` + `reload1.c:2471 alter_reg` no-slot path. A single-set pseudo equal to a constant/stable-MEM gets `REG_EQUIV` → if it fails to get a hard reg, reload substitutes the equivalence per-use (**no slot, no lw**: `reg_equiv_constant`/`reg_equiv_memory_loc`). ~~`&sp_buffer` (an `addiu $sp,off` value) is such a constant.~~
  **[A23] FALSE, and load-bearing — a FRAME ADDRESS IS NEVER `CONSTANT_P`.** `rtl.h:237-240` admits only `LABEL_REF | SYMBOL_REF | CONST_INT | CONST_DOUBLE | CONST | HIGH`. `&sp_buffer` is `(plus (reg virtual-stack-vars) K)` — a PLUS — so it fails the `CONSTANT_P` gates at `local-alloc.c:1031` and `reload1.c:566`, keeps only a **REG_EQUAL** note (never promoted to REG_EQUIV), and therefore gets a **real slot + `lw`** if it loses its register. Only `SYMBOL_REF`/`CONST_INT` equivalences get the no-slot remat. *(Corroborated by byte-test, same day: `cse_expr.md` §2's remat recipe demonstrably fails to dissolve a frame-address hoist seeded by a struct-copy source address — 47→40 mismatches, never 0, across three kill placements; ladder at `.run/near6/f132F40_v1..v6.c`.)* **Consequence: do not reach for RC-7 to make a frame address remat — that is a different mechanism from the constant case, and the sentence below about decayed arrays is the part that actually works.**
- **The call killer:** `validate_equiv_mem` (`local-alloc.c:583`) rejects a MEM equivalence if ANY call occurs between the load and the reg's death (non-`RTX_UNCHANGING_P`) → a stack-local's VALUE loaded before a call can't be rematerialized from its home slot; it must hold a reg or spill to a NEW slot. Address-CONSTANTS survive calls; MEM-values don't. This asymmetry explains the whole class.
- **Lever (byte-proven, cookbook §17, func_8012B4B8 88→52):** pass a stack buffer as a decayed **array** (`T buf[N]`, pass `buf`) — the address stays a rematerializable constant, `addiu $sp` re-emitted per call, no callee-saved consumed. Any address-taken form (`&struct`, `mtx.w`, `*(T*)arr`) forces the address into a pseudo that crosses calls → callee-saved + bigger frame.
- **Priority side-effect to know:** an equiv-reg's `REG_LIVE_LENGTH` is **doubled** (`local-alloc.c:1153`) — deliberately halving its K2 priority ("reload can always recreate it"). So a single-set address/constant var LOSES callee-saved races on purpose. If the target holds such a value in $sN anyway, your draft must defeat the equiv: give the var a **second set** (`REG_N_SETS != 1` fails the `update_equiv_regs` gate) — the same REG_N_SETS knob as §30's birthing-boost, one pass earlier. ~~Also: a set-once-used-once non-block-local pseudo gets its init MOVED to just before its use (`:1230-1270`, `LIVE_LENGTH=2, calls_crossed=0`) — if the target shows the init far from the use (or vice versa), this pass did/didn't fire; check REG_N_REFS==2.~~
  **[A23] REMOVED — that pass does not exist in gcc 2.7.2.** The cited `:1230-1270` is papermario/**2.8.1** `local-alloc.c:1236-1265`. Vanilla 2.7.2's `update_equiv_regs` (**:947-1117**) substitutes the equivalence into the use and **DELETES the initializing insn** (`:1090-1116`) — it never relocates it. **So "init far from its use" tells you nothing about this pass; do not use it as a diagnostic.**
- **2-INSTRUCTION CONSTANTS get the second set FOR FREE → they escape the doubling (Phase 24 T7, byte-proven func_8013AF20, gdb-verified):** sched1 pre-reload-splits every insn (`sched.c:4830 try_split`) → mips.md:3208 `large_int` define_split turns `li BIG` into lui + ori = `reg_n_sets==2` → fails the single-set gate (`local-alloc.c:1021`, vanilla line) → **no ×2 penalty**. A lui+ori const (`0x00ffffff`) therefore out-prioritizes every same-ref 1-instruction const (addiu-able or lui-only, whose LL doubled) and allocates FIRST. When a preheader const-register contest looks "impossible by density", check the contenders' instruction counts before anything else (gdb: `((short*)reg_n_sets)[N]` at `update_equiv_regs`). Full chain: cookbook §36.

### RC-8 — Reload artifacts: reg identity, missing/extra `lw`, missing `sw`, reload order — **DETERMINED (fix upstream, don't chase)**
These are pure consequences; a diff here means an UPSTREAM divergence (slot count/shape, block structure), except the listed direct levers:
- **$t0 vs $tN identity:** K6/RC-5(2). Deterministic given which regs the fn uses. If the whole function's reload regs are off-by-one ($t1 where $t0 expected), something in your draft explicitly uses $t0 (a pin) or uses one MORE simultaneous spill reg.
- **Second load of a spilled var missing in the target:** reload **inheritance** (`:5514`) — the target's two uses sit in one extended-bb run with the spill reg untouched. If YOUR draft re-loads, your uses are separated by a label/jump or by a reload-reg-clobbering insn — restructure the branch (e.g. §16 shared-ret0 goto keeps a run unbroken) rather than fighting the `lw`.
- **Store back to slot missing:** `delete_output_reload :7274` — the pseudo was dead. Your extra `sw` means your pseudo has a LATER ref the target's doesn't (often a duplicated use you added). Conversely 571C4 idiom 2 exploits it: a dead `__asm__ volatile("" : "=r"(x))` re-set emits nothing precisely because of this deletion.
- **Reload `lw` order before one insn:** operand order (`emit_reload_insns :5977`) — swap the source operands.
- **$t0/$t1 alternation flipped mid-function:** round-robin `last_spill_reg` state (`:5083`) — count reloads upstream of the flip; you have one extra/missing reload event earlier. Fix that; never pattern-match the rotation itself.

### RC-9 — Cross-block copy the target folded (phi-style `move` your draft can't remove) — **STEERABLE in C-shape, else permuter**
- **Mechanism:** per K8, global-alloc cannot coalesce. If the target computes a value in-place across blocks (e.g. in-place negate for `abs`) where your draft has `t2 = cond ? -t1 : t1`-shaped RTL, no allocator setting will merge them — the ORIGINAL C had one variable mutated in place.
- **Lever:** rewrite as a single variable updated in place (`if (v < 0) v = -v;`), matching def/use block structure to the target's.
- **Limit (the 8014EA4C wall):** when every single-variable form ALSO perturbs frame/pressure (dead-store elimination of an init memcpy, frame shrink), the class degenerates to RC-6 → permuter. Probe 3-4 in-place forms; if each is frame-fragile, stop.

---

## §C Diagnostic tells (read these off the match_one diff / dumps first)

| Tell | Meaning | Class |
|---|---|---|
| `lhu/sh $t0, N($sp)`, N in 8-rounded run (0x20,0x28,…) | reload access to a SPILLED pseudo (u16 w/ subreg:SI widening) | RC-1 |
| same-slot accesses but offsets swapped vs target | pseudo creation (DECLARATION) order differs | RC-1 |
| value accessed via `$v0/$v1/$aN` scratch | local-alloc temp (single-block, dies once) — NOT a spill | RC-1/RC-4 |
| per-use `addiu $rX,$sp,off` at each call | rematerialized address constant (array-decay shape) | RC-7 |
| `sw $aN,slot / lw` of an incoming param | a param allocno LOST the callee-saved race (priority flip) | RC-2 |
| whole $s-assignment permuted, insns otherwise right | allocation-order permutation | RC-3 |
| copy emitted before its source's other use, use reads the copy's reg | local-alloc TIE (coalescing) | RC-4 |
| your draft has `move` the target lacks (same block) | target tied them / your pin blocked a tie | RC-4/RC-5 |
| ALL reload regs shifted $t0→$t1 | explicit use (pin) of $t0 poisoned the pool | RC-5 |
| pin added → 20+ insn regression | pass-0 shift / range blocking cascade | RC-5→RC-6 |
| regs+opcodes exact, block placement off, every edit explodes | pressure-lock | RC-6 |
| target lacks a 2nd `lw` of a spilled var | reload inheritance (unbroken run) | RC-8 |
| target lacks the `sw` back to slot | delete_output_reload (pseudo dead) | RC-8 |
| `move $vN,$sN`-style copy into a call-crossing reg missing | equiv-reg init got MOVED to its use / replaced | RC-7 |

**Dump crib (get these free from `cc.sh`-style compile with `-da`):** `.lreg` → `Register N used R across L insns; crosses C calls` (K2 inputs per pseudo); `.greg` header → `;; Register dispositions: <pseudo> in <hardreg>` (who won what; missing pseudo = spilled), `Spilling reg N.` (reload reg identity), `;; N conflicts/preferences` lines. Hard-reg numbers: 2=$v0 3=$v1 4-7=$a0-$a3 8-15=$t0-$t7 16-23=$s0-$s7 24/25=$t8/$t9 29=$sp 30=$fp/$s8 31=$ra.

---

## §D Triage order for a "regalloc"-class near-miss

1. **Slot offsets off?** → reorder declarations (RC-1). Slot access SHAPE wrong ($t0 vs $v0 vs addiu)? → change the C storage shape (RC-1/RC-7).
2. **Wrong value spilled / param evicted?** → dump `.lreg`, compute densities, shift the marginal def/use (RC-2). Iterate — 1 statement at a time.
3. **$s-order permuted?** → equal densities: decl-order swap; else pins per target map (RC-3), ONE at a time with the RC-5 checklist.
4. **Stray/missing `move`?** → tie analysis (RC-4), or single-variable rewrite for cross-block (RC-9).
5. **Reload artifact diffs?** → almost always upstream; use RC-8 to find WHICH upstream cause.
6. **Everything right but placement, edits explode?** → RC-6: stabilizing pin + decomp-permuter. Stop hand-grinding after 2 probes.

## §E Experiment record (reproducibility)
All vs `func_801571C4` target, baseline draft `.run/fable/func_801571C4.c` = 11-off (prologue position ripple only).
- **EXP-1** `exp1_slotorder.c` (swap assignments): 11-off, byte-identical diff → statement order is dead. **EXP-1c** `exp1c_declorder.c` (swap decls): 15-off, new mismatches EXACTLY idx 20/23/97/145 = the 0x20↔0x28 slot accesses.
- **EXP-2** `exp2_defmove.c` (def after call): 137-off; `dumps/exp2.i.greg` shows reg88 gained `in 23` ($s7) at live length 94→89 and the a3-param pseudo lost its reg (spilled; `sw $a3,0x20($sp)` in diff).
- **EXP-3** `dumps/exp3.c` (dead `$8` pin at fn top): `.greg` "Spilling reg 8" → "Spilling reg 9"; all reload accesses moved to $t1.
- Micro tie-probe (`dumps/tie1.c/tie2.c`): unequal-density pair is order-stable under statement swap (confirms decl-order lever only bites on exact K2 ties).
Cited proofs from earlier sessions: func_8012B8E4 (§17 pins), func_80128ED8 (§25 tie pins), func_8012B4B8 (§17 array-decay), func_801770E0 + func_8014EA4C (RC-6 walls, `.run/toolkit/`), func_801571C4 header idioms 1-2 (`.run/fable/`).

---

## §F Phase-24 T5b extension — preference mechanics + the S11/RC-6 verdict downgrade

### RC-10 — The PREFERENCE CASCADE (why a scratch temp chases a specific arg reg) — read it, then steer around it
- **set_preference (global.c) unwraps ONE expression level:** for `(set DEST (op X ...))` where the insn pairs
  a HARD reg with a pseudo, the pseudo gets a preference bit — through `minus`/`ashiftrt`/any first-operand
  expression, not just copies. So `(set (reg $a1) (ashiftrt t 16))` makes t prefer $a1 (observed: the
  ratan2-arg extend temps, `109 preferences: 5`).
- **expand_preferences merges through DEATHS:** when allocno A dies in an insn that SETS allocno B and they
  don't conflict, their preference sets IOR **both ways**. Preferences therefore flow BACKWARD through
  dying-def chains (arg-reg ← extend-temp ← variable ← the temps that died into it). A conflict between the
  two allocnos BLOCKS the merge (the pair-1 subu's operands conflict its dest — re-born later — so that link
  is naturally blocked; the final subu's operands don't).
- **find_reg grant order:** pass 0 scans only `regs_used_so_far` minus `regs_someone_prefers[allocno]`
  (prefs of LOWER-priority conflicting allocnos, pruned of each allocno's own hard-reg conflicts) — the
  "reuse already-dirty regs" frugality is why a free incoming arg reg ($a0 after an early param-copy death)
  gets grabbed by a high-priority scratch temp. Pass 1 opens fresh regs (plain regno scan). THEN copy-prefs
  and plain prefs OVERRIDE the first-fit if the preferred reg merely doesn't conflict.
- **Levers (byte-proven, func_8014E048):** (1) keep the incoming arg regs BUSY through the contested windows
  via body-local param copies (sched.md S13) — a hard-reg conflict beats every preference; (2) rebalance a
  K2 density race that a dead-read disturbed by reading BOTH contestants in the one asm; (3) when the target
  shows a copy that cse would dissolve, use the asm-copy form (sched.md S13).

### RC-6/S11 — VERDICT DOWNGRADED (Phase 24 T5b): "intrinsic → permuter" was map-incompleteness
`func_8014E048` (35-off, "S11 LUID⊗alloc coupling, not source-steerable, permuter seed" — and still 28-off
after the §31-directed permuter) is **MATCHED and whole-binary BANKED** by composing: the S12 reused-s32-temp
fence + S13 body-local param copies + the asm-copy + an RC-4b target-scratch-pinned store temp + a two-input
dead-read fence + s32-with-(s16)-cast-at-def vars. **Rule of thumb going forward:** an "S11/RC-6 intrinsic"
verdict is trustworthy only after (a) auditing PINS (~~they kill the S2 boost and~~ **[A23] they do NOT kill the S2 boost — `birthing_insn_p`, 2.7.2 `sched.c:2469`, tests only `GET_CODE (SET_DEST (pat)) == REG`, so HARD regs qualify; the real gate is `reg_n_sets == 1` at `:2490`. Decisive: `sched.c:423` in the same file DOES add `>= FIRST_PSEUDO_REGISTER` where it wants pseudos only, so the omission is deliberate. Same correction landed in `sched.md` §1.7/§S12 the same day. Check the SET COUNT, not the pin**) and they add suggestion-ties,
(b) trying the S12 fence for any load-batching residual, (c) trying S13 for scratch-identity/wedge residuals.
True RC-6 (every edit explodes 20+ insns) still exists — but the class is SMALLER than Phase-21..23 believed.
The promoted-HI store-copy law also falls out: `b[0] = (short)dx` with dx a PSEUDO emits copy+sh (the HI temp
is real); with dx PINNED (hard reg) the subreg folds and the copy vanishes — another reason pinned drafts
diverge from the original's unpinned shape.

### RC-11 — The 3-qty local-alloc SORT BUG + the zero-byte asm allocation toolkit (Phase 24 T5, cookbook §34) — **STEERABLE (decoy qty / dummies)**
`local-alloc.c:1441-1463`/:1494-1516: for a block with **≤3 local register quantities** the unrolled compare switch compares *fixed qty numbers* (`qty_compare(0,1),(1,2),(0,1)`) but exchanges *order slots* — when `pri(q1)` is highest the third compare re-fires and undoes the first swap, so **≤3-qty blocks allocate in qty-CREATION order, not density order** (≥4 qtys → qsort, correct). A genuine gcc-2.7.2 bug. Symptom: a low-density local grabs a reg the density order would deny. **Fix:** a **zero-instruction decoy qty** (`asm("":"=r"(decoy):"r"(x)); asm("" :: "r"(decoy));`) bumps the block to 4 qtys → the qsort path → correct density first-fit (`find_reg`, `global.c:904`; `regs_used_so_far` pre-seeded with call-used regs, `global.c:352-355`).
**The zero-byte asm toolkit** (allocation/schedule dials that emit NOTHING; the byte-gate certifies): **input-only** `asm("" :: "r"(v))` floats to v's def (ref/density dial); **multi-input** `asm("" :: "r"(a),"r"(b))` anchors at the latest def (lifetime-extender / joint-release → `rank_for_schedule` class rule `sched.c:2385`); **def+use pair** mints the decoy qty above. gdb-on-cc1 (`find_free_reg`/`post_mark_life`) settles the real qty order when hand-modeling stalls. Cite vanilla `tools/reference/gcc-2.7.2/local-alloc.c`.

---

## §G Phase-24 T7 extension — the func_8013A530 clamp crack (RC-6 "reload-pressure" downgraded again; 3 new levers)
Exemplar: `func_8013A530` (204 ins, close=10 "RC-6 reload-pressure" → MATCH, `.run/t7/func_8013A530.c`; dumps/variants `.run/t7/fable/a530/`). The "pressure" was three separable, steerable decisions:

### RC-12 — The $0-ADD OPAQUE COPY: force a live `move` that neither cse nor combine can remove/reverse — **STEERABLE (new tool)**
- **Problem shape:** target keeps `load→rA` and `copy rC=rA` as TWO live regs, compares reading rA, arithmetic reading rC. A pseudo copy `int c = a;` is destroyed by canon (`cse.c:826 make_regs_eqv` head-promotion + `canon_reg` rewriting every pseudo use); with `a` pinned, combine instead REVERSES it (load absorbed into the pseudo via the added-sets path, the pin becomes the copy dest, 1 insn short). No plain-C spelling survives both.
- **Lever:** `register int zr __asm__("$0"); c = a + zr;` — RTL `(plus rA (reg 0))`: not a reg-reg set (no qty merge, no canon), not load-absorbable (no extend+plus pattern), assembles to the byte-identical `addu $rC,$rA,$zero`. $0 is fixed → no regs_explicitly_used/bad_spill side channels (unlike any real-reg pin).
- Alternative for the same class: the S13 asm-copy (`asm("":"=r"(c):"0"(a))`, reload materializes the tie-move) — but its `#APP` markers constrain placement (see below); the $0-add is a real, freely schedulable insn. Prefer $0-add.

### RC-5 channel 2 EXTENDED — pins poison `retry_global_alloc`, moving registers function-wide where the pinned var is DEAD
- `regs_explicitly_used → bad_spill_regs` (`reload1.c:3900-15`) affects not only the spill-reg identity but the **reload-driven allocation retry**: an allocno that failed main `find_reg` (here: the div-magic `Need 1 reg of class LO_REG/MD_REGS` spill path) is re-allocated by `retry_global_alloc` with bad_spill_regs forbidden. Seed: `$v1`/`$v0` pins → CASE1's 2nd-product "Register 178 now in 10" (`mflo $t2`); unpinned → "now in 3" (`mflo $v1`). **Tell:** a scratch-reg diff in a region where no pinned var is live + a `Spilling reg N` line in `.greg` → audit pins, not liveness.

### RC-13 — Reload-birth vs pin/pseudo death is set by CONDITION OPERAND ORDER (sched1 backward + mem-unit hazard), not by allocation
- The clamp's after-store reload `lh` is hoisted by sched1 (backward list scheduler; `blocking insn N for 1 cycles` mem-unit hazard against the `sh`; boosted-group ties break toward higher uid) to the block TOP when the condition is spelled `(int)mem < x` (mem expands first, lowest uids) — birthing the reload INSIDE the previous value's live window → hard conflict → the "reload-pressure" mis-allocation. Spelling the SAME canonical slt as `x > (int)mem` mirrors the uids (the else-arm's natural order) and keeps the lh below the killing insn → both values share the reg disjointly. **Zero-byte, zero-semantic lever; check both spellings before any RC-6 verdict.**

### RC-11 toolkit CAVEAT — `#APP` blocks the maspsx/ASPSX-2.56 delay-slot hop
cc1 emits `[lh;lh;addu;slt;beqz]`; the target's `[..;slt;beqz;addu-in-slot]` + load-delay nop layout is made by **maspsx** hopping the eligible addu over the slt into the branch slot. Any zero-byte asm dummy between the addu and the branch emits `#APP/#NO_APP` and kills the hop (costs exactly 1 insn + a cascade). **Placement rule:** park density/lifetime dummies inside an arm, as a 2-input `asm("" :: "r"(v),"r"(t))` anchored at a local def — never in a block tail the assembler must reorder. (Density effect proven: +1 ref lifted the allocno from 3/10 to 8/11 `allocno_compare` priority, flipping the $v1/$a0 grant order.)

### local-alloc suggestion note (companion to K5) — a dying pinned reg SUGGESTS itself into the next dest
A compare/arith result qty whose insn kills a HARD (pinned) input records `qty_phys_sugg`; suggested qtys allocate FIRST trying only that reg (`local-alloc.c:1593-1625`) — the else-compare's slt temp took the dying fc pin's $a1 over free $v0. A zero-byte keepalive read of the pinned var AFTER the insn removes the death → no suggestion → plain first-fit. **Tell:** a scratch result landing in an arg/pinned reg that dies in the same insn.

## §H Phase-27 Fable5 wave — the reg_renumber-swap oracle + 3 more RC-6 downgrades (2026-07-15)

Three seed cracks (`.run/giants/{func_8014D820,func_801670E4,func_8016CBC0}.fable.md`) continuing the §F/§G theme — an "RC-6 intrinsic" verdict is usually map-incompleteness. The durable output is one **diagnostic** and two **levers**.

### THE reg_renumber-SWAP ORACLE — discriminate RC-6 (allocation) from S3 (scheduling) in ONE gdb run
The single highest-value tool of the wave. When a residual is "register identity AND an instruction reordering" you cannot tell from the diff whether the reorder is a *scheduling* decision (S3, C often can't move it) or a mere *consequence* of the register grant (fix the regs and the schedule follows). Test it directly: break at `reload` entry, patch `reg_renumber` (a `short*`; find its address in the cc1 map) to swap the two contested hard regs, let compilation finish, and diff. **If the block goes byte-exact (schedule included), the residual is 100% ALLOCATION** — the reorder was a consequence, route to the density/lifetime levers, NOT to a scheduling lever or the permuter's schedule mode. (`func_801670E4`: the seed called its dominant residual an S3 `sched.c` priority wall — "C cannot lower a priority"; the swap oracle emitted the store-before-load target byte-exact, proving it was pure register 2-coloring. Generalizable: **store-before-load reordering is often a CONSEQUENCE of register identity, not a scheduling cause — swap-oracle it before invoking S3/S4.**)

### RC-14 — reused-load-temp SERIALIZATION (the MERGE pole; pin-free, cheap-Opus-applicable)
To reproduce a target that **serializes** two independent load-fed computations through the same 2 scratch regs (target reuses `$v0/$v1` across dx and dz), reuse ONE set of named C temps (`t0,t1`) across both computations. Because gcc-2.7.2 has no coalescing (K8), the read-before-second-write anti-dependence forces the serial load schedule AND the register reuse. This is §45-Lever-A (merged accumulators) applied to *load temps*, and the MERGE pole of the SPLIT↔MERGE duality (§44-Lever-3 SPLITs a reused output pointer for per-tail first-fit; RC-14 MERGEs load temps for the shared-reg serial schedule). Byte-proven `func_8014D820` block-0 261→110. Companion: **route a param through a plain `self = param` local** to land its callee-saved copy INSIDE the entry block (vs a copy-at-head) — measured 287→110.

### RC-15 — the DENSITY DIAL across a floor_log2 boundary (the ref-count axis of RC-6)
`global.c:594 allocno_compare` priority ≈ `live_length << floor_log2(n_refs)`. When two allocnos tie on live_length and differ by one `n_refs` step that **crosses a power-of-2** (7→8, 15→16 …), the multiplier doubles and the density order flips — deciding which wins the callee-saved reg by creation order. Dial it with an **input-only anchor at the right loop depth**: `__asm__("":: "r"(v))` inside a `loop_depth`-2 body adds `reg_n_refs += 2` (flow.c:2067), lifting the target var across the boundary. This is the ref-count-axis companion to §47's live-length slider, and it **subsumes the "coalescing knife-edge" mislabel** for callee-saved swaps (there is no coalescing in gcc-2.7.2, K8 — the "knife-edge" was always this density tie). Byte-proven `func_8016CBC0` root-A byte-zero. (The `#APP` placement caveat from RC-11 applies: anchor at a local def inside an arm, never in a reorderable block tail.)

### The local-vs-global allocation tie (a named RC-6 sub-class, honest wall for the C tier)
A reused scalar (2+ deaths → GLOBAL allocno) loses `$v0` to a single-use sibling (1 death → LOCAL allocno) purely because **local-alloc runs before global-alloc** (`local-alloc.c` single-death gate), so the local grabs the low reg first and the global takes what's left — the opposite of the target's equally-valid 2-coloring. No pin-free C spelling reaches it (block-confined globalization has no legal spelling: cross-block → call-crossing; asm → #APP perturbation). This is a *genuine* residual for the cheap tier → decomp-permuter (its temp-merge randomizers are the only automated path) or an accepted honest stub. `func_801670E4` region B (17 diffs) is the exemplar. **But note it is a precisely-named allocator tie, not a "whole-function permutation" — the swap oracle tells you which you have.**
