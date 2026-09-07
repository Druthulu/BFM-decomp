# gcc-2.7.2 SCHEDULING + DELAYED-BRANCH pass map — residual → C-lever catalog
**Pass-group: `sched.c` (sched1 pre-reload / sched2 post-reload) + `reorg.c` (dbr) + the MIPS backend hooks.**
Source: `tools/reference/gcc-papermario/` (line numbers below are that tree). Pinned triple: `cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker` (both sched passes AND dbr run at -O2).

> ## ⚠️ SOURCE-VERSION WARNING (Phase 29 SESSION-23, 2026-07-28) — READ BEFORE FOLLOWING ANY CITATION
> **`gcc-papermario` is gcc 2.8.1, NOT 2.7.2** (established Phase 23; vanilla 2.7.2 is staged at
> `tools/reference/gcc-2.7.2/` and `SETUP.md` §5.6 was corrected). The line numbers in this file are
> therefore correct **for the wrong compiler**, and every *behavioural* claim derived from that tree is
> UNVERIFIED for our build until re-derived against `tools/reference/gcc-2.7.2/`.
>
> **This is not hypothetical — one claim is already byte-refuted.** §1 item 7 and §S12 both state that
> the S2 birthing boost requires `SET(REG_pseudo, …)`, and therefore that a `register __asm__` pin on the
> dest kills the boost ("Unpin first"). In real 2.7.2, `birthing_insn_p` (sched.c:2469 [2.7.2]) tests only
> `GET_CODE (SET_DEST (pat)) == REG` — **there is no `>= FIRST_PSEUDO_REGISTER` check anywhere in the
> function**; the discriminator is `reg_n_sets[i] == 1` (sched.c:2490 [2.7.2]). **Hard-reg dests ARE boosted.**
> Both sites are corrected below. We had been advising agents to drop pins for no reason.
>
> **Hand-verified 2.7.2 definition lines** (`grep -n '^<sym> ('`), for the symbols this file leans on:
>
> | symbol | cited here (2.8.1) | **real 2.7.2** |
> |---|---|---|
> | `insn_cost` | 1390 | **1363** |
> | `priority` | 1452 | **1425** |
> | `potential_hazard` | 1345 | **1318** |
> | `rank_for_schedule` | 2414 / 2455 | **2385** (LUID tie-break `return` at **2428**) |
> | `birthing_insn_p` | 2498 | **2469** (`reg_n_sets` test **2490**) |
> | `adjust_priority` | 2534 | **2507** |
> | `schedule_insn` | 2587 | **2557** |
> | `schedule_select` | 2646 | **2616** |
> | `schedule_block` | — | **3144** (`ready[0]` pick at **3747**) |
>
> **The drift is NOT a uniform offset — do not rebase mechanically.** It is ~+27 in `sched.c` but
> **+103** (`combine_regs`, local-alloc.c 1825→1722), **+377** (`allocate_reload_reg`, reload1.c
> 5083→4706) and **+611** (`choose_reload_regs`, reload1.c 5514→4903) elsewhere — large enough that a
> citation can land inside a *different function*, which is exactly how a behavioural claim gets read off
> the wrong code. A screening pass counts **~44 drifted citations across `sched.md`, `regalloc.md` and
> `loop.md`**; that screen is a lower bound, not a precise census. **`regalloc.md` has the worst drift and
> its levers steer the hardest matches — re-derive it before trusting an RC-* mechanism.**
Byte-proofs: dump experiments in `.run/gccmap/exp/` (`run.sh <name>` = full pipeline + `-dS -dR -dd` RTL dumps → `<n>.i.sched/.sched2/.dbr`, final `.dis`), and the real exemplar **func_801770E0: 53→49 mismatch, both jal-slot residuals byte-fixed** (`.run/gccmap/exp/e3.c`).

---

## 0. WHO OWNS WHICH BYTES (attribution — decide this first)

| Stage | What it decides | Tell |
|---|---|---|
| **sched1** (`schedule_block`, pre-reload) | order of insns within each bb, on **pseudos** — this order becomes sched2's LUID (tie-break) input | `.i.sched` dump |
| reload/local-alloc | scratch-register assignment **follows sched1's insn order** (fixing order usually fixes $v1/$a2/$t0 rotations for free) | |
| **sched2** (post-reload) | final order incl. **RTL prologue/epilogue saves** (MIPS prologue IS RTL: `mips.md:6490 define_expand "prologue"` → `mips.c:mips_expand_prologue`/`save_restore_insns:4955`) | `.i.sched2` dump |
| **dbr** (`reorg.c:dbr_schedule:4408`) | delay-slot contents, join-block steals, jump threading | `.i.dbr`; cc1 asm: filled slot = wrapped `.set noreorder/nomacro` (`mips.c:3983 [2.8.1 pm] '%*'`) |
| **maspsx** (`--aspsx-version=2.56`) | inserts the explicit `nop` after every UNfilled branch (`# DEBUG: branch/jump`) | |
| **gas -O1** | **NOTHING** — it never branch-swaps here (maspsx already nop'd every open slot). Also expands `-G0` macro loads/stores (`lw r,SYM` → `lui $at + lw`) | `lui $1(at)` pairs in .dis = assembler macro, not cc1 |

**Consequence: every useful delay-slot byte is gcc-dbr's choice; every slot `nop` means dbr found nothing ELIGIBLE (see D2) — gas/maspsx never improve a slot.**

The scheduler **never moves an insn across a basic-block boundary** (gcc-2.7.2 has no interblock scheduling). Any cross-bb code motion in a diff = dbr (steal/copy) or jump-opt, never sched.

---

## 1. THE PICK ALGORITHM (exhaustive — how one bb gets its order)

`schedule_block` (sched.c:3172 [2.7.2]) schedules each bb **BACKWARD** (from the tail): *picked early = placed late*.

1. **Dependences** (`sched_analyze:2190`): true/anti/output on regs; memory via `pending_read/write` lists + `memrefs_conflict_p:627` (same-base different-const-offset stores DON'T conflict → mutually reorderable); every MEM op and every reg dep on a CALL: calls flush the pending lists (`flush_pending_lists:1647`) → **no memory op ever crosses a call**; `MEM_IN_STRUCT_P` (`/s`) enters via `true/anti/output_dependence:829-907` (the §30 store-vs-load flag).
2. **Latency** (`insn_cost:1390`→**2.7.2 :1363** + `mips.md` function units): load **2** (r3000), xfer 2, store 1, ALU 1, imul **12**, idiv **35**, call result **1** (no unit). `mips.h:3204 [2.8.1 pm] ADJUST_COST`: **anti/output dep cost = 0 → clamped to 1 (LINK_COST_FREE)**. A dep INTO a `USE` insn is also cost-free (sched.c:1419 [2.7.2] — arg setup overlaps the call).
   **[A23] `insn_cost` is DEP-KIND-BLIND in 2.7.2** — it has no `REG_DEP_ANTI` zero-case (added in ≥2.8), so an anti-dep of a latency-2 load still contributes **+1** to priority rather than 0. Consequence for the §4 aliasing levers: **restoring `/s` anti edges is NOT free — it RE-GROUPS downstream stores.** Budget for that before using `/s` to steer.
3. **Priority** (`priority:1452`) = longest-chain-from-bb-top: `pri(insn) = max over LOG_LINKS preds of (pri(pred) + cost(pred) − 1)`, min 1. So: **all-latency-1 code ties at pri 1**; each load on the path adds **+1**, imul +11, idiv +34; anti/output links propagate the pred's priority unchanged (+0). Priorities can only be RAISED by C edits, never lowered.
4. **Ready list** = insns whose successors are all scheduled. Sort (`rank_for_schedule:2414`), pick `ready[0]`:
   1. **highest INSN_PRIORITY**;
   2. **class vs last-scheduled insn**: prefer class 3 = {no link to it, OR link cost ≤1} over class 1 = {true-data-dep with cost >1}. On MIPS, ADJUST_COST makes every anti/output link class 3, so this only demotes candidates that FEED the just-placed insn through a load/mul/div latency ("don't place a load directly before its consumer");
   3. **highest LUID first** (= placed later) → forward order among full ties = **ascending LUID = source order** (sched1) / **= sched1-output order** (sched2). This is the stable tie-break.
5. **`schedule_select:2646`** (runs because MAX_BLOCKAGE>1 on MIPS): within an equal-priority group, (a) function-unit-blocked insns are queued (`actual_hazard`) — observed: two memory ops back-to-back get spaced when an alternative exists (t1 dump: `;; blocking insn 14 for 1 cycles`); (b) among the rest, **the insn with the largest `potential_hazard:1345` goes first** — memory/imuldiv-unit users beat plain ALU insns *even against the LUID rule* (t4 dump: `;; insn 20 has a greater potential hazard`). This is a 4th rank rule the cookbook §25 summary lacked.
6. **Launch/queue** (`schedule_insn:2587`): when a pred's last successor is scheduled, it becomes ready — but if the link cost >1 (load feeding the just-scheduled consumer) it is **queued `cost` cycles**: one independent insn gets wedged between a load and its consumer whenever one is ready; if none, they stay adjacent.
7. **`adjust_priority:2534` (2.7.2: **2507**) — THE BIRTHING BOOST (pre-reload ONLY, `reload_completed==0`)**: on becoming ready, an insn whose pattern is `SET(REG, …)` — **any REG, pseudo OR hard; CORRECTED 2026-07-28, there is no `>= FIRST_PSEUDO_REGISTER` test in the function** — with the dest live and **`REG_N_SETS(dest)==1`** (`birthing_insn_p:2498`; 2.7.2: **2469**, the `reg_n_sets` test at **2490**) has its priority raised to `max_priority` (≈ the launching insn's) → it wins every tie → **single-set defs sink to just before their first consumer**. Dump tell: `(7f000001)` priorities in the ready list. NB: REG_N_SETS is counted **after cse/flow** — a source-level 2nd assignment that cse copy-propagates or flow dead-store-eliminates does NOT kill the boost (proof: `exp/t5.c`, `exp/t6.c` — both still boosted).
8. Special pins: **bb0 head-skip** (sched.c:3218-3244 [2.8.1 pm]): the leading run of `pseudo = hard-arg-reg` param copies is excluded from scheduling (stays first, in arg order). **Tail pin** (3313-3360): trailing JUMP/CALL/USE insns stay at bb end (TAIL_PRIORITY). `SCHED_GROUP_P`: a call + its immediately-preceding `USE argreg` insns move as one unit.
9. **sched2 differences**: no boost, no head-skip; hard-reg anti/output webs (scratch reuse) now pin most of sched1's order in place; **nop-moves are deleted** (sched.c:4926 [2.8.1 pm]); RTL prologue ~~/epilogue~~ saves are now in the pool (see S7) — **[A23] PROLOGUE ONLY; the epilogue expander is dead on MIPS in 2.7.2, so epilogue restores never enter sched2's pool.** sched2's LUID = sched1's output order → **pre-reload placement persists**.

---

## 2. RESIDUAL CLASSES — sched (S*) then dbr (D*)

### S1 — Equal-priority straight-line order ≠ target ⇒ STEERABLE: statement order IS the schedule
- **Decision point:** `rank_for_schedule:2455` LUID tie-break (rule 4.iii above).
- **When:** all-latency-1 runs (no load/mul feeding the block's values): everything ties at pri 1 (or all-boosted ties at max) → final order = source statement order, and within one statement = expansion order.
- **Lever:** reorder C statements to the target's asm order. **You can TRANSCRIBE the target block back into statement order** (each insn run = one statement; early-materialized big constants = explicit locals at the transcription point). Byte-proven: exp/e4→e5 reproduced the target's destructive `pCval` cluster (`addiu $s1,$s1,-5 / sll / andi $s2 / or`) and const-cluster order exactly by transcription.
- **Caveat:** transcription edits can shift register allocation (see S11) — change ONE statement group at a time, re-scoring each step.

### S2 — Single-set def sinks to its consumer / multi-set def stays at source position (the BIRTHING BOOST, both directions) ⇒ STEERABLE
- **Decision point:** `adjust_priority:2534` + `birthing_insn_p:2498` (pre-reload only).
- **Kill the boost** (def sits too LATE, want it at source position): add a 2nd SET that survives cse — the §30 #3 re-tie `__asm__("" : "=r"(x) : "0"(x))` in a LATER bb, or the end-of-function dead-`volatile` `__asm__ volatile("":"=r"(x))` for spilled pseudos (both cookbook-proven). A plain C reassignment does NOT work if cse/flow can eliminate it (t5/t6 proofs).
- **CREATE the boost** (def sits too EARLY, target has it sunk): make the value a **fresh single-set local** instead of reusing a multi-set variable.
- **BYTE-PROVEN REAL EXEMPLAR — func_801770E0 (53→49, `exp/e3.c`):** the target fills both `jal func_801783D0` delay slots with the previous call's result save (`addu $s0,$v0,$zero`) and hoists `li $a1,4` early. The draft chained `uVar2 = f(uVar2,…)` (6 sets → no boost → the save-copy stayed at its post-call source position → `li` landed in the slot). Fix:
  ```c
  /* BEFORE (draft, slot wrong):            AFTER (matches target):        */
  uVar2 = f(uVar2, …, 0x6e163858);          u4 = f(uVar2, …, 0x6e163858);
  sVar1 = func_801783D0(D_8011F830, 4);     sVar1 = func_801783D0(D_8011F830, 4);
  uVar2 = func_801777BC(uVar2, sVar1, …);   u5 = func_801777BC(u4, sVar1, …);
  sVar1 = func_801783D0(D_8011F82E, 4);     sVar1 = func_801783D0(D_8011F82E, 4);
  puVar3 = func_801777BC(uVar2, sVar1, …);  puVar3 = func_801777BC(u5, sVar1, …);
  ```
  (`void *u4, *u5;` fresh, single-set → boost → each save sinks below the arg setup to just before the jal → dbr slots it, D1.) Dump-level proof: e0 trace `T-100: ready {85,93} → picked 93 (li)` vs t4 trace `T-6: ready {14,22} → picked 14 (move)`.
- **Corrects** the draft-header verdict "reorg's pick is unsteerable / register pins don't change it" — the pick was never reorg's: it's sched1's boost deciding ADJACENCY (see D1). Pins can't affect it; REG_N_SETS can.

### S3 — Load/mul-fed chain sinks below lower-priority stores ⇒ INTRINSIC (permuter / re-decomposition)
- **Decision point:** `priority:1452` — a chain fed by a load is pri+1 (imul +11), and priority DOMINATES the LUID tie-break; no statement order can override it, and C cannot LOWER a priority.
- **Example:** func_801770E0's GPU store block: the `lhu D_8011F830 → ×10355 magic-mult chain → sw p[3]` has pri 4-5 vs the other stores' pri 3 (e5d.i.sched2 dump) → the whole chain + its store sink below the pri-3 stores; the TARGET has the chain mid-block, which under this compiler requires the surrounding chains to carry equal priority — a different expression decomposition, not reachable by reordering the draft's statements (draft note's 3975-perm search corroborates).
- **Verdict:** route to decomp-permuter (it can permute decomposition, not just statements), or hand re-derive the original decomposition. When attacking by hand: equalize priorities (give sibling chains the same +1 sources) rather than trying to demote the sinking chain.

### S4 — One insn wedged between a load and its consumer ⇒ STEERABLE (filler choice)
- **Decision point:** `schedule_insn:2632` queue (cost-2 link) + rank rules for what fills the gap.
- The gap EXISTS iff some independent insn is ready at that tick; WHICH insn = rank rules (priority, then potential-hazard, then LUID). Lever: statement order picks the filler among equal-priority candidates; adding/removing an independent statement adds/removes the gap. (t1: `z=a+b` wedged between `lw` and `addiu`.)

### S5 — Memory ops spaced apart / load pulled ahead among ties ⇒ mostly INTRINSIC mechanics, filler STEERABLE
- **Decision points:** `schedule_select:2646` (`actual_hazard` queues a 2nd memory op scheduled back-to-back when an alternative exists — t1 `blocking insn 14 for 1 cycles`) and `potential_hazard:1345` (among an equal-priority ready group, memory/imuldiv users are moved to the FRONT, overriding LUID — t4 `insn 20 has a greater potential hazard`).
- Diagnosis: adjacent `sw;sw` in your build where the target interleaves a compute (or vice versa) — check whether an independent insn was READY (dump) — steer by making one available/unavailable at that tick (statement order).

### S6 — "Independent insn separates address-gen from use" / copy placed between ⇒ mechanics of the class rule
- **Decision point:** `rank_for_schedule:2428-2452` class 3 > class 1. On MIPS anti/output are ALWAYS class 3 (ADJUST_COST) — only true-data-deps through latency>1 (loads, mul/div) are demoted. Explains the recurring "unrelated move sits between `addiu $x` and `lw …($x)`" target shapes. Steer via which independents are available (statement order).

### S7 — Prologue~~/epilogue~~ save~~/restore~~ interleave ⇒ sched2 artifact, body-side STEERABLE
> **[A23] RE-SCOPED, not deleted (audit 2026-07-28).** The **prologue** half is CONFIRMED: the MIPS
> prologue really is RTL, so its saves are in sched2's pool. The **epilogue** half is FALSE for our
> build — `grep -n 'define_expand "epilogue"' config/mips/mips.md` finds only a DEAD entry, and
> `thread_prologue_and_epilogue_insns` (`function.c:5515 [2.7.2]`) is split by two independent guards
> (`HAVE_prologue` / `HAVE_epilogue`), so the epilogue restores are NOT scheduled RTL here.
> **Do not look for epilogue-restore interleave as a sched2 artifact — it cannot occur.**
- MIPS prologue is **RTL**: saves emitted `$ra` down to `$s0` (**descending regno**, `save_restore_insns:5077`), sp-adjust first. sched2 weaves body insns among them under the same rank rules (anti-deps: `sw $sN` must precede the first body write of `$sN`).
- Target tell: `sw $s1` far from `sw $ra/$s5/$s4` (pulled by an early body overwrite of `$s1`); a callee-save `sw` in a branch/call delay slot (dbr backward-fill, exp/t2 f2: `bne…; sw $31,20($sp)`).
- The saves' RELATIVE order is fixed (descending regno) — if the target shows otherwise it's sched2 weaving, steered by the body insns' priorities/LUIDs, not by any prologue-side lever.

### S8 — Leading param copies never scheduled (bb0 head-skip)
- sched.c:3218-3244 [2.8.1 pm] (pre-reload, bb0): the leading run of `pseudo = $a0..$a3` copies is pinned in arg order. Anything before the first non-param-copy insn is immovable — don't fight it; it also anchors LUIDs for the block below.

### S9 — sched1 order persists through sched2 (the LUID relay)
- sched2's LUIDs are sched1's OUTPUT order; post-reload scratch anti-webs freeze most of it. So: **diagnose order residuals in `.i.sched` (sched1) first**; sched2-only deltas are basically prologue weave (S7) + reload-insn placement + deleted nop-moves. (This is why `-fno-schedule-insns2` rarely changes anything but prologue weave, and why "the register allocation follows the schedule" — S11.)

### S10 — `-fno-schedule-insns` diffing (diagnostic lever, not a fix)
- Rebuild the one file with `-fno-schedule-insns` / `-2` variants in the exp harness to attribute a residual: unchanged ⇒ dbr/jump/expansion-order artifact; changed ⇒ sched. (The known dbr source-invariance finding used exactly this.)

### S11 — THE COUPLING WALL (why some scheduler levers explode) ⇒ characterized; treat as CONSTRAINT
- Register allocation (local-alloc scratch order + global-alloc `allocno_compare` density sort) consumes sched1's output order AND the ref/set counts your lever edits change. On a knife-edge allocation (func_801571C4's LUID-tie⊗global-alloc flip; func_801770E0's flat 3-callee alloc), ANY lever that adds refs/sets or shifts live-range lengths flips the allocation and explodes the diff (byte-shown: `exp/e2.c` — destructive updates on the pinned/param vars → param_2 fell out of $s2, +2 insns, 143 off).
- **Protocol:** (1) pin the callee-saved homes FIRST (§17 `register … __asm__("$16")`) so scheduling levers can't cascade the alloc; (2) apply ONE S1/S2 lever at a time, re-score; (3) never destructively reassign a PINNED variable mid-function (splits its live range around the pin — e2 proof); (4) if every lever flips the alloc → genuine permuter fuel (this, not "unsteerable scheduling", is what the fn-header verdicts usually mean).
- func_801571C4 remains the canonical intrinsic exemplar of LUID-lever ⊗ alloc coupling: every LUID-raising construct shrinks a live range → `allocno_compare` order flips. Route to permuter; revisit only with pins-first protocol.

### D1 — Delay-slot content = the nearest ELIGIBLE insn above the branch/call ⇒ STEERABLE via S1/S2 (adjacency)
- **Decision point:** `fill_simple_delay_slots:3083` — backward scan from the slot-owner; FIRST eligible candidate wins. `needed` for a CALL is computed WITHOUT delayed effects (reorg.c:3080-3081 [2.7.2]) → **arg-reg setups are eligible for their own call's slot** (`li $a1,4`, `move $a0,$sX` — the classic jal-slot fills); for a cond-branch the condition-feeding insn is excluded (it's `needed`).
- So the residual "wrong insn in the jal/branch slot" is really "wrong insn ADJACENT to it pre-dbr" ⇒ fix with S2 (boost) / S1 (LUID). **Byte-proven: func_801770E0 both slots (S2 above).**
- Also fills `j $31` slots with the return-value insn (t1) and branch slots with prologue saves (t2 f2).

### D2 — Slot stays `nop` ⇒ ELIGIBILITY map (usually INTRINSIC, occasionally steerable by re-forming the candidate)
`eligible_for_delay` = `define_delay` (mips.md:119): slot insn must have **`dslot == no` AND `length == 1`**. Therefore NEVER in a gcc slot:
  - **loads** (lw/lh/lbu/…), `mfhi/mflo` (hilo), fcmp/xfer — `dslot=yes` (mips.md:73). **Verified against the whole game asm: 0 loads/mfhi/mflo in any delay slot** (ov_SC01_077 + resident nonmatchings), while register/frame stores are common slot fills (sw 464 / sh 429 / sb 91 — backward-filled, D1: only the EAGER steal excludes stores, not backward fill). Real slot histogram: nop 3009, addu 2125, addiu 1430, sw 464, sh 429, sll 143, slti 120, lui 104, sb 91, andi 86 …;
  - **`-G0` macro-form global load/store** (`sw $r,SYM` / `lw $r,SYM` kept whole = length 2; exp/t2 f1: `beqz; nop` even though `sw $5,A` follows). The cse-split form (`lui %hi` + `sw %lo(...)`) is two length-1 insns and eligible in principle (no target occurrence found in ov_SC01_077 — treat as theoretical);
  - multi-insn expansions (large-const `li` = length 2, div sequences, `asm multi`);
  - anything conflicting with the branch condition / call's `set`.
- Slot-owner side: branches, jumps, calls each have exactly 1 slot (`num_delay_slots > 0`); jr $31 included.
- If no backward candidate AND no eager/target steal qualifies (D3) → maspsx `nop`. A target `nop` you can't reproduce = you HAVE an eligible adjacent insn the target didn't → S1/S2 to move it away, or your candidate differs in form (macro vs split).

### D3 — Join/target-block head insn in a conditional branch's slot (the STEAL) ⇒ shape- and polarity-STEERABLE
- **Decision point:** `fill_eager_delay_slots:3849` → `fill_slots_from_thread:3454`, direction picked by `mostly_true_jump:1352`; runs only if D1 backward-fill found nothing (fill order per pass: simple(calls) → simple(jumps) → eager → relax, ×2 — reorg.c:4559 [2.8.1 pm]).
- **Prediction ladder** (`mostly_true_jump`): branch-out-of-loop → very-unlikely; target preceded by LOOP_BEG → very-likely (loop-back); fallthrough/target rarity (RETURN-reachability) comparison; then **EQ→not-taken, NE→taken, `<0`/`<=0`→not-taken, `>=0`/`>0`→taken**; else backward=taken / forward=not-taken. Predicted-taken ⇒ steal from TARGET thread first; else FALLTHROUGH thread.
- **Eligibility in a NON-ANNULLED slot (MIPS1 has NO annulled slots — `branch_likely=no` at -mips1, mips.md:96/121, so `eligible_for_annul_* = 0` always):** candidate must not conflict with insns skipped, must NOT set anything live at the OPPOSITE thread, and `!may_trap_p` ⇒ **a STORE can never be eager-stolen** (memory is always in `opposite_needed`, `mark_target_live_regs:2722`) and loads are out anyway (D2). Register sets qualify iff the dest is DEAD on the opposite path (e.g. overwritten there — exp/t3 g3/g4: both arms' `addiu $2,…` — the slot executes on BOTH paths and the fallthrough overwrite masks it).
- **MOVE vs COPY** (`own_thread_p:2195`): thread owned (label used once && preceded by BARRIER — i.e. only reachable via this branch) ⇒ insn MOVED out of the thread (deleted there) and the branch redirected past it — this is the "join-block first statement stolen and deleted" case, which requires the 'join' to have NO fallthrough predecessor. Not owned ⇒ insn **COPIED** (`copy_rtx`, code GROWS) and the branch redirected to `label+4` — tell: branch target = join label + one insn, with the same insn duplicated in the slot.
- **Levers:** (a) **branch polarity** (§3-T4) flips prediction AND thread choice → moves the slot fill to the other arm (t3 g3 vs g4: `c==0` vs `c!=0` swap which `addiu` sits in the slot); (b) **provide a backward candidate** — an independent statement placed before the branch preempts the eager steal entirely (D1 runs first); (c) **join-head statement choice** — make the join's first statement a store/macro/load (ineligible → nop) or a dead-dest reg op (eligible); (d) the steal itself is sched-invariant (survives `-fno-schedule-insns`) — if the target shows a steal you can't get, fix CFG shape/polarity, not statement order.
- **relax_delay_slots:3969** afterwards: threads jump-to-jump, deletes jumps-to-next, inverts a cond-jump over an unconditional (reorg.c:4224 [2.8.1 pm]), redirects a branch past a target-head insn redundant with its slot (`redundant_insn:1989`) — tells: "branch to label+4", inverted-polarity-with-swapped-targets vs your draft.

### D4 — Slot insn reads the WRONG source register (pre-copy operand) ⇒ recognize, then reshape
- **Decision point:** reorg.c:3689-3701 [2.8.1 pm] — if a thread starts `reg2=reg1; use reg2…`, dbr rewrites the use to `reg1` (validate_replace_rtx) so the use becomes slot-fillable next iteration. Tell: slot insn operand = the copy's SOURCE where the join code uses the DEST. If the target lacks this rewrite, your thread has an extra head copy the target didn't (reshape the join head).

### D5 — Two identical return/exit paths merged vs kept separate
- `fill_simple` case reorg.c:3277 [2.8.1 pm]: when the scan stops at `j SAME_TARGET`, the branch copies the insn AT the shared target into its slot and both jumps get redirected — one shape of the cross-jump/§10 family, plus optimize_skip is dead on MIPS1 (annul-only). See cookbook §5a/§10 for the cross-jump side (jump.c territory, not this pass-group).

---

## 3. DIAGNOSTIC TELLS (fast triage)

| Tell in the diff | Meaning | Go to |
|---|---|---|
| Same insns, permuted, all latency-1 | LUID/source order | S1 |
| A single-def copy/const sits at source position in yours, sunk-to-use in target (or vice versa) | birthing boost | S2 (real proof: func_801770E0) |
| `li`/`move` swapped between "just before jal" and "in the jal slot" | S2 + D1 adjacency | S2/D1 |
| A load+arith chain block sits later in yours than target, past cheaper stores | chain-priority sink | S3 (intrinsic → permuter) |
| `nop` in your slot, useful insn in target's (or reverse) | eligibility (macro/length/dslot) or adjacency | D2, then S1/S2 |
| Store-to-global in target slot, `nop` in yours | your store kept -G0 macro form (length 2); target had split `%lo` form | D2 |
| Branch targets `label+4` / duplicated insn in slot + at target | eager COPY-steal | D3 |
| Insn present in target's slot but MISSING from its join block | own-thread MOVE steal | D3 |
| Slot insn operand uses pre-copy register | dbr copy-forwarding | D4 |
| Opposite branch polarity + swapped arms | jump-opt/relax inversion or prediction-side steer | D3 |
| Callee-save `sw` interleaved with body / in a slot | sched2 RTL-prologue weave | S7 |
| `$at (`$1`) in any pair | assembler macro expansion, not cc1 | §0 |
| Adjacent memory ops in yours, spaced in target (or vice versa) | memory-unit hazard spacing / filler availability | S5/S4 |
| Everything fixable flips regalloc when you try | coupling knife-edge | S11 protocol |

**Dump tells** (`.run/gccmap/exp/run.sh`): `(7f000001)` in a ready list = boosted insn; `;; blocking insn N for K cycles` = unit hazard queue; `;; insn N has a greater potential hazard` = rank rule 4/S5; `;; launching N before M` = queue release. Priorities/ref_counts table at each bb head; sched1 vs sched2 = `.i.sched` vs `.i.sched2`.

---

## 4. APPLICATION RECIPE (for a cheap agent)
1. Attribute the residual (§0 table): `$at`? macro. Slot? dbr. Cross-bb? not sched. Else sched.
2. For sched residuals: reproduce with `exp/run.sh`, read `.i.sched` priorities at the bb; equal-pri ⇒ S1 (reorder statements toward target, transcribing the target block as statement order); single-set-vs-multi-set placement ⇒ S2 (fresh local / re-tie); pri differs via load/mul chain ⇒ S3 (permuter).
3. For slot residuals: identify the target's slot insn; if it's an insn from ABOVE ⇒ make it the adjacent one (S1/S2); if from the TARGET thread ⇒ D3 (polarity/CFG/eligibility); if `nop` mismatch ⇒ D2 eligibility.
4. Pin callee-saved homes before applying levers on a near-miss (S11); one lever per iteration; `match_one` after each.
5. Feed any NEW residual class back into this file + cookbook.

## 5. Exemplar artifacts (byte-proofs)
- `exp/t1.c` — load-gap fill (S4), priorities, `j $31` slot backward fill, unit blocking (S5).
- `exp/t2.c` — f1: macro-store ineligibility → nop (D2); f2: prologue-save slot fill (S7/D1); maspsx nop attribution (§0).
- `exp/t3.c` — g1/g3/g4: eager steal, dead-on-opposite, polarity flip (D3).
- `exp/t4.c`/`t5.c`/`t6.c` — S2 boost mechanics + the cse-defeats-multi-set caveat; sched1-output = sched2-LUID (S9).
- `exp/e0..e5.c` — func_801770E0 series: e3 = **53→49 byte-proven S2 lever** (use as the draft base); e4/e5 = target-transcription method (S1) reproducing the pCval/const clusters, and the S3 intrinsic wall (mult-chain pri 4 vs stores 3, `e5d.i.sched2`); e2 = the S11 cascade counterexample.

---

## 6. Phase-24 T5b extension — the S11 crack (func_8014E048 case study, 35→MATCH banked)

### S12 — Load BATCHING vs PAIRING: the reused-s32-temp FENCE ⇒ STEERABLE (was "S11 intrinsic")
- **Symptom:** target pairs `lhu;lhu;[gap];subu / lhu;lhu;[gap];subu`; your draft batches all 4 loads then
  both subus — invariant under statement order AND pins (the loads are independent; the scheduler hoists them).
- **Mechanism:** independence is a SOURCE property. **Reusing ONE variable pair across both load pairs**
  (`w0 = p3[0]; w1 = p2[0]; dx = w0 - w1; w0 = p3[2]; w1 = p2[2]; dz = w0 - w1;`) puts an output-dep
  (set₂ after set₁) and an anti-dep (set₂ after `subu`'s reads) on the second pair — sched1 CANNOT batch.
  The shared pseudos then take ONE scratch each for both pairs (v1/v0), and reload/sched2's hard-reg
  anti-webs lock the pairing through to the bytes.
- **THE TYPE TRAP (why u16 temps do NOT work):** gcc-2.7.2 MIPS does not promote small vars — `u16 w0` stays
  an HImode pseudo, and **every use site zero-extends through a FRESH SImode temp**; combine then folds each
  `lhu`+`zext` into the fresh temp and the shared HI var VANISHES (deps gone, batching returns). The reused
  temps must be **s32** (`w0 = p3[0]` zero-extends directly into the var's own SI pseudo; multi-set +
  multi-use survives combine). Byte-proof: `exp/e1b.c` (u16, still batched) vs `exp/e1c.c` (s32, PAIRED).
- **Pin interaction (CORRECTED 2026-07-28 — the old text was FALSE for 2.7.2):** a `register __asm__`
  pin on the subu DEST is a hard reg → `qty_phys_copy_sugg` pulls a load temp INTO the pinned reg
  (`lhu s0`). ~~and the dest fails `birthing_insn_p` (needs `SET(REG_pseudo,…)`) → no S2 boost. Unpin
  first;~~ **That reasoning does not hold.** `birthing_insn_p` (2.7.2 sched.c:2469 [2.7.2]) tests only
  `GET_CODE (SET_DEST (pat)) == REG` — hard regs qualify — and gates on `reg_n_sets[i] == 1` (2490).
  A pinned dest is boost-ELIGIBLE; the boost is lost only if the value is SET more than once (e.g. a
  `lui`+`ori` constant pair, which is two sets, vs a single-insn constant). **So do NOT unpin
  reflexively** — check `reg_n_sets` instead. The fence still does the pairing.

### S13 — bb0 head-skip ESCAPE: body-local param copies steer BOTH the schedule and the scratch contest
- **Mechanism:** assign_parms emits param copies at the function head; sched1's bb0 head-skip (S8) pins them
  FIRST, so the incoming hard arg regs die at insn ~2-4 — leaving them FREE for find_reg's pass-0
  "already-dirty" first-fit (a scratch temp can grab $a0). **Routing a param through a local taken
  mid-body** (`p1 = param_1;` after the deltas; all uses via `p1`) dissolves the head copy (local-alloc ties
  the once-used incoming pseudo to its arg reg) and materializes the REAL copy at its statement position:
  the hard arg reg now stays live INTO the temps' windows → **hard-reg conflict** → the temps are steered
  to v0/v1 (byte-proof: `exp/e1f.c` — w-temps flipped a0/v0 → v1/v0 = target). The copy is a boosted
  single-set move that sched wedges into a load-use gap (S4 filler).
- **Wedge-slot steering (which gap it fills):** backward scheduling fills the FIRST-backward stall, so
  statement position (LUID) alone cannot move the wedge to an earlier gap. A **zero-byte volatile-asm
  dead-read** (`__asm__ __volatile__("" :: "r"(p1))`) placed between the pairs creates a true-dep that
  confines the copy to the earlier region → it fills the pair-1 gap and the pair-2 gap gets the gas nop
  (byte-proof: `exp/e1j.c`). **Ref-count side effect (K2!):** the dead-read is +1 ref on its operand and can
  flip a callee-saved density contest (e1j: param_2 lost s3 to p1). Counter-lever: read BOTH contested
  variables in the one asm (`:: "r"(p1), "r"(param_2)`) to preserve their relative densities
  (byte-proof: `exp/e1k.c` = the full MATCH).
- **cse-opacity for pointer copies:** a plain `p3 = param_3;` copy gets copy-propagated by cse into nearby
  uses (the copy floats/dissolves). When the copy must materialize AND dominate all uses (`addu a3,a2` with
  every load via a3), emit it as an **asm-copy**: `__asm__("addu %0,%1,$zero" : "=r"(p3) : "r"(param_3))`
  (+ a `register __asm__("$7")` pin on the dest when the target names the reg). cse cannot see through an
  asm. Byte-proof: `exp/e1i.c`.

### Case-study ledger (func_8014E048, all in `.run/gccmap/exp/`)
e1a (unpin only): contest lands s0-s4 naturally; the `(short)var` promoted-HI store-copy appears; loads
still batch. e1b (u16 reused temps): S12 type trap — still batched. e1c (s32 temps): **PAIRED**, 28→19.
e1d (+s32 sVar7, extend-at-def): 16. e1f (+p1 body-local): w-temps v1/v0. e1h (+a3 pin): b-block scratch
chain matches. e1i (+asm-copy, p1 between pairs): **4-off**. e1j (+RC-4b a0-pinned store temp + dead-read
fence): 19 (density flip). e1k (+two-input dead-read): **MATCH (143/143), whole-binary banked**.
