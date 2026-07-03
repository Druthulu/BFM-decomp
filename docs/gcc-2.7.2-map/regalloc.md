# gcc-2.7.2 REGISTER ALLOCATION + RELOAD → residual→C-lever catalog
**Pass group:** `local-alloc.c` (2491) · `global.c` (1714) · `reload.c` (6204) · `reload1.c` (8626), in `tools/reference/gcc-papermario/`.
**Produced:** 2026-07-02 (Phase 23), by source read + `-da` RTL dumps + byte experiments via
`tools/match_one.py <fn> --c FILE --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077`.
**Prime exemplar:** `func_801571C4` (198 ins, `.run/fable/func_801571C4.c`, baseline 11-off); experiment variants in `.run/gccmap/` (`exp1_slotorder.c`, `exp1c_declorder.c`, `exp2_defmove.c`), RTL dumps in `.run/gccmap/dumps/`.
**How to use:** read §A once (the 8 knobs), then triage a diff with §C (tells) → apply the §B lever for the matched class. A cheap agent should never need the gcc source again for these classes.

---

## §A The decision machinery — 8 knobs everything below reduces to

Pass order (relevant slice): `flow → combine → sched1 → local_alloc → global_alloc → reload → sched2 → dbr`.
**sched1 rewrites the life data regalloc consumes** (`sched.c:5067` `REG_LIVE_LENGTH(regno) = sched_reg_live_length[regno]`) — this is the exact channel by which instruction placement flips allocation (K2 below). Any scheduling lever (cookbook §30 birthing-boost, statement order) is therefore ALSO a regalloc lever, and vice versa.

- **K1 — Pseudo creation order.** Params get pseudos first, in PARAMETER-LIST order (`function.c:assign_parms`); then user locals in **DECLARATION order** (pseudo made when the decl is expanded at block entry — **NOT at first assignment**; byte-proven, §B RC-1); compiler temporaries interleave at first need. Creation order (= regno order) is the tie-break for K2, the qty tie-break (`local-alloc.c:1745` `return q1 - q2`), the allocno tie-break (`global.c:616` `return v1 - v2`), and the **spill-slot order** (K7).
- **K2 — Density priority.** Both allocators use the same formula:
  `pri = (int)(((double)(floor_log2(n_refs) * n_refs) / live_length) * 10000 * size)` — `global.c:594 allocno_compare` (per-allocno, REG_LIVE_LENGTH from flow/sched1) and `local-alloc.c:1727 QTY_CMP_PRI` (per-qty, birth→death insn indices). Higher density allocates FIRST. It is `int`-truncated; exact ties fall back to creation order (K1). **Shrinking a live range raises priority** — refs are per-insn-mention, so moving a def later (or a last use earlier) is the lever.
- **K3 — Hard-reg scan order.** MIPS defines **no REG_ALLOC_ORDER** (`config/mips/mips.h`) → every scan is plain regno order: `$v0,$v1,$a0..$a3,$t0..$t7,$s0..$s7,$t8,$t9,$fp`. First fit wins. So: first callee-saved allocno → `$s0`, next → `$s1`, …; local temps → lowest free scratch (`local-alloc.c:2176 find_free_reg`, over the qty's birth–death window `regs_live_at`).
- **K4 — Call-crossing ⇒ callee-saved only.** `global.c:917-922` / `local-alloc.c:2205-2209`: an allocno/qty with `calls_crossed > 0` excludes ALL of `call_used_reg_set` ($v0–$t9). PSX gcc has `flag_caller_saves` off → no save/restore fallback. Whether a value crosses a call is decided purely by def/last-use placement in the (post-sched1) insn stream.
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
- **Decision points:** `local-alloc.c:1007 update_equiv_regs` + `reload1.c:2471 alter_reg` no-slot path. A single-set pseudo equal to a constant/stable-MEM gets `REG_EQUIV` → if it fails to get a hard reg, reload substitutes the equivalence per-use (**no slot, no lw**: `reg_equiv_constant`/`reg_equiv_memory_loc`). `&sp_buffer` (an `addiu $sp,off` value) is such a constant.
- **The call killer:** `validate_equiv_mem` (`local-alloc.c:583`) rejects a MEM equivalence if ANY call occurs between the load and the reg's death (non-`RTX_UNCHANGING_P`) → a stack-local's VALUE loaded before a call can't be rematerialized from its home slot; it must hold a reg or spill to a NEW slot. Address-CONSTANTS survive calls; MEM-values don't. This asymmetry explains the whole class.
- **Lever (byte-proven, cookbook §17, func_8012B4B8 88→52):** pass a stack buffer as a decayed **array** (`T buf[N]`, pass `buf`) — the address stays a rematerializable constant, `addiu $sp` re-emitted per call, no callee-saved consumed. Any address-taken form (`&struct`, `mtx.w`, `*(T*)arr`) forces the address into a pseudo that crosses calls → callee-saved + bigger frame.
- **Priority side-effect to know:** an equiv-reg's `REG_LIVE_LENGTH` is **doubled** (`local-alloc.c:1153`) — deliberately halving its K2 priority ("reload can always recreate it"). So a single-set address/constant var LOSES callee-saved races on purpose. If the target holds such a value in $sN anyway, your draft must defeat the equiv: give the var a **second set** (`REG_N_SETS != 1` fails the `update_equiv_regs` gate) — the same REG_N_SETS knob as §30's birthing-boost, one pass earlier. Also: a set-once-used-once non-block-local pseudo gets its init MOVED to just before its use (`:1230-1270`, `LIVE_LENGTH=2, calls_crossed=0`) — if the target shows the init far from the use (or vice versa), this pass did/didn't fire; check REG_N_REFS==2.

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
