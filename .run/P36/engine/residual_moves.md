# Residual classes → source moves (gcc 2.7.2, `-O2 -G0 -mips1 -mcpu=3000 -msoft-float`)

Written 2026-09-09 for the Phase-36 de-lever engine. Every row is a HYPOTHESIS until the engine proves it on bytes; the
"how to test" column is the experiment. Every `file.c:NNN` below is in `tools/reference/gcc-2.7.2/` (the vanilla 2.7.2
subset = the pinned cc1's real source) and was taken from `grep -n` on that tree during this session — none from memory,
none from `gcc-papermario` (2.8.1). Where the Phase-23 map (`docs/gcc-2.7.2-map/`) carries a 2.8.1 number for the same
construct I re-derived it; the map's mechanism claims are cited as "map: file §".

## Preamble — what was read

- Source: `local-alloc.c` (`local_alloc`, `update_equiv_regs`, `block_alloc`, `qty_compare*`, `combine_regs`, `reg_is_born`,
  `wipe_dead_reg`, `find_free_reg`), `global.c` (allocno numbering, `allocno_compare`, `find_reg`, `set_preference`),
  `sched.c` (`init_alias_analysis`, `memrefs_conflict_p`, `true/anti_dependence`, `insn_cost`, `priority`,
  `potential_hazard`, `sched_analyze_1/insn`, `rank_for_schedule`, `birthing_insn_p`, `adjust_priority`, `schedule_insn`,
  `schedule_select`, `schedule_block`, the live-length write-back), `reorg.c` (`fill_simple_delay_slots`,
  `mostly_true_jump`), `combine.c` (`can_combine_p`, `try_combine` bookkeeping, `simplify_rtx` canonicalization),
  `cse.c` (`make_regs_eqv`, `insert_regs`, `canon_reg`, `find_best_addr`, `fold_rtx`, `cse_gen_binary`, `note_mem_written`,
  `invalidate_memory`, the call flush, the LOOP_END EBB break), `reload.c` (`find_reloads` commutative retry),
  `reload1.c` (slot loop, `order_regs_for_reload`, `delete_output_reload`), `regclass.c` (`reg_scan`), `flow.c` (ref /
  death / live-length / loop-depth accounting), `jump.c` (noop moves, `duplicate_loop_exit_test`, cross-jump),
  `expr.c` (`binop:`, `preexpand_calls`), `optabs.c` (`expand_binop` swap), `fold-const.c` (constant-second swap),
  `c-typeck.c` (`build_binary_op` → `fold`), `stmt.c` (`expand_decl`, `expand_decl_init`), `function.c`
  (`assign_parms`), `emit-rtl.c` (`gen_reg_rtx`), `expmed.c` (`expand_mult`), `toplev.c` (pass order),
  `config/mips/{mips.h,mips.c,mips.md}`.
- Map: `docs/gcc-2.7.2-map/README.md`, `regalloc.md`, `sched.md`, `cse_expr.md`, `loop.md`, `cite_overrides.tsv`.
- Cookbook (`docs/matching-cookbook.md`, by `grep -n` + `sed -n`): §501 (A–E, P, Q, R), §454/§454a, §373, §336, §76,
  §137, §153, §175, §176 (A–F), §194 (A, B, D, K), §205, §17a.

## The spine — pass order, and which counters each pass consumes

`toplev.c`: `reg_scan`+`jump_optimize` (:2826-2827) → **cse1** (`cse_main(…, after_loop=0)` :2865, `delete_dead_from_cse`
:2867) → **loop** (:2895) → **cse2** (`after_loop=1` :2926) → **flow** (:2983) → **combine** (:3004) → **sched1** (:3033)
→ `regclass` + **local_alloc** (:3051-3052) → **global_alloc** (:3080) → **reload** (:3082) → **sched2** (:3117) →
`jump_optimize(cross_jump=1, noop_moves=1)` (:3142) → **dbr** (:3167).

The counters that decide registers and order, and who writes them:
- `reg_n_sets`: `regclass.c:1791` (reg_scan) and recounted by flow `flow.c:2065`; read by `birthing_insn_p`
  (`sched.c:2490`), `update_equiv_regs` (`local-alloc.c:1021`), `init_alias_analysis` (`sched.c:426`), combine
  (`combine.c:1561/1764/4277`).
- `reg_n_refs` (LOOP-DEPTH weighted, `flow.c:2067/2315/2501`), `reg_n_deaths` (`flow.c:2101/2533`), `reg_live_length`
  (`flow.c:1684/2073`), `reg_n_calls_crossed` (`flow.c:1650`), `reg_basic_block` (`flow.c:2058-2062/2494-2497`).
- sched1 REWRITES `reg_live_length` and `reg_n_calls_crossed` from its own schedule before local-alloc runs
  (`sched.c:4947`, `:4964`) — every scheduling lever is therefore also an allocation lever.
- `loop_depth` bumps at NOTE_INSN_LOOP_BEG/END in flow (`flow.c:1401/1403/1447/1449`) and in `update_equiv_regs`
  (`local-alloc.c:973-975`).
- Pseudo numbers are minted sequentially by `gen_reg_rtx` (`emit-rtl.c:515-516`): parameters first in parameter order
  (`function.c:3628`), then each local at its DECLARATION (block entry, `stmt.c:3387`), compiler temps as needed.
  Regno order is the allocno order (`global.c:384-397`), the `allocno_compare` tie-break (`global.c:609`), and the
  spill-slot order (`reload1.c:658`).

Two MIPS facts that shape everything: **no `PROMOTE_MODE`** in `config/mips/mips.h` (only a comment at :2622) — a `u8`/`s16`/
`u16` local is a QImode/HImode pseudo and every SImode use goes through a fresh extend temp; and **no `REG_ALLOC_ORDER`** —
both allocators scan hard regs in plain regno order (`local-alloc.c:2158`, `global.c:960`), lowest free wins.

---

## Class 1 — same opcodes, different REGISTERS

### 1a — the caller-saved swap ($2↔$3, $4–$7 permuted)

Who decides a caller-saved (non-call-crossing) register: `local_alloc` for single-block / single-death pseudos
(`local-alloc.c:472`), `global_alloc` for the rest. In local-alloc the decision chain is: **(i)** which pseudos are TIED
into one quantity (`block_alloc` `local-alloc.c:1229-1298` → `combine_regs` :1722), **(ii)** the quantity order
(`qty_sugg_compare` pass for suggested regs :1472; then `qty_compare` :1579 — density `floor_log2(refs)*refs*size /
(death-birth)`, ties by qty number = BIRTH order :1622; for ≤3 quantities the unrolled exchange at :1493-1508 instead of
`qsort` :1512), **(iii)** first-fit over the qty's live window, lowest regno free (`find_free_reg` :2158-2175). A
call-crossing qty excludes all call-used regs (:2106). In global-alloc: priority order (`allocno_compare` `global.c:587-611`),
pass 0 only among `regs_used_so_far` minus registers someone else prefers (:952-953, seeded with call-used regs + every reg
local-alloc took, :352-360), then copy/plain preferences may override the first fit (:1001-1071).

| rank | source move | pass | decision (function, file:line) | mechanism | how to test | conf. |
|---|---|---|---|---|---|---|
| 1 | **Inline a single-set temp at its use** (or the reverse: name an operand in a temp) | local-alloc | `block_alloc` tie loop `local-alloc.c:1229-1298`; `combine_regs` gates :1765 (`reg_qty[ureg] < 0` = not a local qty) and :1855 (must die here); local gate :472 | The result of `a & b`/`a + b` shares a register with the FIRST operand (operand 1 is tried before operand 2, `if (win) break;` :1298) that is a block-local, single-death pseudo dying at that insn. A named temp with any other use is either global (2 deaths / 2 blocks) or not dying → the tie falls through to operand 2 (the constant's `li` pseudo) → `and v0,v1,v0` instead of `and v0,v0,v1`, and the temp is then coloured by global.c AFTER local-alloc took $2. Byte anchor: func_80163EC8 (§454). | Apply, compile the TU through `tools/delever_oracle.py`, score with `tools/masked_diff.py`; expect the dest register to jump from operand-2's to operand-1's colour with no count change. Confirm in `.lreg`: the temp's line gains/loses `used … across …` and appears in local-alloc's list. | H |
| 2 | **Swap the operands of one commutative operator** (`a & b` → `b & a`) — ONLY when both operands are non-constant expressions/registers | expand → local-alloc | `expr.c:6453-6459` (`binop:` evaluates operand 0 then operand 1, then `expand_binop`); `optabs.c:405-418` (swap only if op1 is REG and op0 is not, or `target == op1`, or op0 is CONST_INT); `cse.c:4435-4443`, `:5278-5290` and `combine.c:2973-2985` re-canonicalize only constants/objects; then the tie loop `local-alloc.c:1229-1298` | With two REG operands nothing downstream swaps them, so the C order is the RTL order, which is (a) the EMISSION order of the two operand computations (birth order → qty number → tie-break :1622 / creation order for ≤3 qtys :1493-1508) and (b) which operand the result is tied to. **Caveat (source-proven):** if one operand is an integer constant, `fold-const.c:3179-3189` moves it to the right BEFORE expansion and `optabs.c:416` again — a `const & x` ↔ `x & const` swap is a no-op at the tree. | Same harness; expect the two scratch colours to exchange (and possibly the dest to follow). For the const case the engine should expect NO change — if a change is observed, record it as a refutation of the fold reading (see Open Q1). | H (var/var) · L (const) |
| 3 | **Change declaration SCOPE of a temp** (function-scope → the innermost block / per-arm; or the reverse) | flow → local/global split | `flow.c:2058-2062` (`reg_basic_block`), `:2533` (deaths); gate `local-alloc.c:472`; global marks locally-allocated regs as hard conflicts (`global.c:358-360`) | A variable used in several arms has ≥2 deaths → GLOBAL allocno → allocated after every local qty, cannot be tied, takes what is left. Per-arm declaration → one 1-death pseudo per arm → each ties and first-fits in its own block (§76: four of five decisions in a 1,511-ins function). | Same harness; expect a register-only diff to move or vanish; in `.greg` the variable appears/disappears from `Register dispositions`. | H |
| 4 | **Reuse one variable for two independent computations** (MERGE) or split a reused one (SPLIT) | flow → global; sched1 | deaths `flow.c:2533`; `allocno_compare` `global.c:594-597`; anti/output deps `sched.c:1721-1728` (pseudo arm) | MERGE forces 2 deaths → global allocno + a WAR/WAW chain that serialises the two computations through ONE register (RC-14, S12 — must be `s32`: a HImode temp is folded away by combine). SPLIT gives each computation its own local qty → independent first-fit. | Same; expect a serial vs batched pattern AND the shared register. Attribution: `-fno-schedule-insns` collapses the order half but not the colour half. | H |
| 5 | **Reorder independent statements** (move the def of one operand earlier/later) | sched1 → local-alloc | `rank_for_schedule` LUID tie-break `sched.c:2428` (LUID assigned in source order :2175); qty birth `local-alloc.c:1976-1997` at the first SET in post-sched1 order; tie-break :1622 | Among equal-priority insns sched1 keeps source order; local-alloc numbers quantities in that order; equal-density qtys and the ≤3-qty path allocate in that order → the lowest free reg goes to the earlier-born value. | Same; expect $v0/$v1 (or $a-regs) to swap with no count change when the two defs are latency-equal. If `-fno-schedule-insns` leaves the swap, it was expansion order alone. | M |
| 6 | **Split `T x = e;` into `T x; … x = e;` with the assignment after the whole declaration run** (R3) — or move an init to just before its use | expand order → (5) | `expand_decl_init` `stmt.c:3592-3595` emits the initializer at the declaration point; the pseudo itself exists from `expand_decl` `stmt.c:3387` either way | The pseudo's regno does not move (declaration order), but the SET's position (LUID, birth) does — this is move 5 wearing a declaration costume. It also changes which values are live across the intervening statements (live length, calls crossed). | Same; if the diff is only the birth order the swap closes; if a call sits between, expect a callee-saved/caller-saved flip instead (see 1b). | M |
| 7 | **Wrap one statement in `do { … } while (0)`** | flow (ref weight) + sched1 barrier + cse1 EBB | LOOP notes survive to flow: `flow.c:1401/1403` bump `loop_depth` so every ref INSIDE counts +2 not +1 (`:2067/:2315/:2501`); sched1 treats a mid-block LOOP_BEG/END as a total barrier (`sched.c:2058-2074`, notes captured :2265-2268); cse1 ends its EBB at LOOP_END (`cse.c:8054-8055`, `after_loop=0` at `toplev.c:2865`); loop.c sees a zero-trip loop (`scan_loop` hoists single-set constants to a preheader) | Byte anchor: `flag = 0;` → `do { flag = 0; } while (0);` flipped a callee-saved allocation (§454, RC-5 "scope"). Three separable effects: the ref-weight raises `flag`'s density (RC-15 dial), the barrier pins the statement's position for sched1, and cse1 cannot fold across it. | Same harness, then `tools/cc1_dumps_tu.sh` and compare `.lreg` `Register N used R times` for the wrapped variable (R should rise) and `.sched` for the barrier. A plain `{ stmt; }` is the negative control: BLOCK notes bump nothing (try it FIRST, §454 R7 order). | M |
| 8 | **Give one operand a second read after the insn** (or remove one) — zero-byte `__asm__("" :: "r"(x))` or a real later use | flow → local-alloc | REG_DEAD note placement `flow.c:2511-2533`; `combine_regs` :1855 | Kills/creates the death at the tying insn → flips which operand the result shares (RC-4 un-tie). A real later use also adds a ref (density) and may make the pseudo global (2 deaths). | Same; expect the dest colour to switch operands. | M |
| 9 | **Route a parameter through a body-local copy** (`p1 = param;` mid-body, all uses via `p1`) or the reverse | assign_parms → sched1 head-skip → local-alloc suggestion | head copies `function.c:3628/3679`; bb0 head-skip `sched.c:3189-3210`; hard-reg suggestion `combine_regs` :1798-1822, suggested qtys allocated first :1472; hard conflicts keep $aN busy | The incoming $aN dies at insn ~2 under the head-skip, leaving $aN free for any scratch temp's first fit (and for global pass 0). A mid-body copy keeps $aN live into the contested window → temps are pushed to $v0/$v1 (S13). | Same; expect temps to move off $a-regs onto $v-regs (or back). | H (map-proven) |
| 10 | **Change the width of a local** (`s32` ↔ `u16`/`s16`; never `u8` casually) | expand (mode) → combine → sched1 → local-alloc | no PROMOTE_MODE (`mips.h:2622` comment only); HImode set is a subreg move cse's `insert_regs` does not join to the SImode class (`cse.c:1017-1019` mode test); combine folds `lhu`+`zext` into a fresh temp when the HI var has one use (S12 type trap); sched1 dial §194-D | A narrow local changes WHICH pseudos exist (extend temps), their deaths, and hence every downstream colour. Count-neutral only when no extend is emitted (§194-D); otherwise it is a Class-2 move. | Same; expect register churn confined to the block; if `sll/sra` pairs appear it became Class 2. | M |
| 11 | **Pin the interloper, not the contested value** — `register T tmp __asm__("$N")` on a SHORT-lived neighbour | local-alloc | explicit hard reg: `reg_is_born` :1990-1996 marks it live over its window; suggestion :1798-1822 | A pin reserves the register across the pinned live range only; pinning the value you want moved cascades (RC-5, §176-B4), pinning the short-lived value that stole the register frees it (§176-B2). Pins on $t0 poison the reload pool (`reload1.c:3650-3660`). | Same; sweep the pin register ($5→$4→$3) as §176-B2 did; a monotone response confirms the mechanism. | M (lever the engine is REMOVING — last resort) |
| 12 | **Swap the two operands of a comparison / invert the if** so the load is expanded first or second | expand → sched1 → reload birth | `expr.c` comparison expansion order (operand 0 first, `:5638-5660` region); RC-13 (`regalloc.md` §G) | The operand spelling sets the uids of the compare's feeders; sched1's hazard tie-break then hoists a load INTO another value's window or not → a hard conflict → a different colour. | Same; try both spellings before any allocation verdict (RC-13's rule). | M |

### 1b — the callee-saved bank ORDER ($16–$23 permuted)

The bank order IS the global allocation order: allocnos sorted by `allocno_compare` (`global.c:546` qsort; priority
`floor_log2(n_refs)*n_refs/live_length*10000*size` :594-597; ties by allocno number = regno order :609); each call-crossing
allocno excludes call-used regs (:927) and takes the lowest free callee-saved reg, pass 0 among already-used regs
first (:947-985). Preferences (`set_preference` :1535, copy prefs from `move`s to/from hard regs) can override within the
class (:1001-1071). `tools/alloc_table.py` prints this order straight from the dumps — read it before any move.

| rank | source move | pass | decision | mechanism | how to test | conf. |
|---|---|---|---|---|---|---|
| 1 | **Change a contender's ref count** — add/remove a use, duplicate a case tail instead of merging it (§501-B), reuse a variable (§76), or an input-only `__asm__("" :: "r"(v))` at the right loop depth | flow → global | `flow.c:2067/2315/2501` (`reg_n_refs += loop_depth`); `allocno_compare` `global.c:594-597` | Priority is `floor_log2(R)*R/L`: crossing a power of two in R doubles the multiplier (RC-15); one deleted `sb` (a merged tail, cross-jumped only AFTER allocation, `toplev.c:3142`) dropped a2-raw from 4 refs to 3 and lost it $a3 (§501-B). | Compute both contenders' R,L from `.lreg` (`tools/alloc_table.py`), predict the flip window (§137), apply, gate. | H |
| 2 | **Change a contender's live length** — move its def later / last use earlier (or the reverse); a `volatile` asm read at a chosen point | sched1 → flow/global | `flow.c:1684`; rewritten by sched1 `sched.c:4947`; denominator in `global.c:594-597` | Shorter life → higher density → allocated earlier → lower $s-number. A ~5% change flipped RC-2's exemplar. L is recomputed AFTER sched1, so a source move only works if sched1 keeps it (§137: use a zero-byte read at the point that lands L in the window). | Same; read `;; register N life shortened/extended` in the `.sched` dump to see what sched1 did to your move. | H |
| 3 | **Swap the DECLARATION order of two contenders** (or move one declaration through the run — R2/R4) | expand → global tie-break | `stmt.c:3387` (regno at declaration), `global.c:397` (allocno = regno order), `:609` (tie-break) | Only bites on an EXACT priority tie (int-truncated); then the lower regno wins the lower $s. If densities differ it is a no-op (RC-3's micro-proof). | Same; check `.lreg` first: identical (R,L) pairs ⇒ this move; different ⇒ moves 1/2. | H (tie) · L (otherwise) |
| 4 | **Add or remove a SECOND SET of a single-set constant/address variable** (`x = &SYM; __asm__("" : "=r"(x) : "0"(x));`, or a real re-assignment that cse cannot delete) | local-alloc (`update_equiv_regs`) → global | gate `local-alloc.c:1021` (`reg_n_sets != 1`), penalty `:1064` (`reg_live_length *= 2`) | A single-set pseudo with a REG_EQUIV constant has its live length DOUBLED (priority halved) — a second set forfeits the doubling and ~quadruples priority, rotating the bank (§H.2, RC-7). Two-instruction constants (`lui`+`ori`) get the second set for free after sched1's `try_split` (`sched.c:4830` region; RC-7). NOTE the same knob also blinds sched1's alias oracle (`sched.c:426`) and kills the birthing boost (`sched.c:2490`). | Same; expect the address/const variable to change $s-number and neighbours to shift by one. Count may change (remat lost, §194-K bound 3). | H |
| 5 | **Make or break a call crossing** — move a def/use across a `jal`, or store a value to memory before the call instead of holding it | flow → global | `flow.c:1650` (`reg_n_calls_crossed`), `global.c:927` | A value that crosses no call leaves the callee-saved contest entirely (and vice versa); this renumbers everything below it in the bank. With `flag_caller_saves` ON at -O2 (`toplev.c:3387-3394`, map A23-1) a call-crossing value can also stay in a caller-saved reg with 4-byte-packed save slots (`CALLER_SAVE_PROFITABLE` = `4*calls < refs`, `regs.h`). | Same; read `crosses N calls` in `.lreg`. | H |
| 6 | **Scope a temp per block / per arm** (as 1a-3) | flow → local vs global | `local-alloc.c:472`; `global.c:358-360` | A local qty's register is removed from the global pool; a temp that occupied $s1 as a local allocno pushes every global contender one register up. | Same. | M |
| 7 | **Split a hoisted invariant into N inline expressions** vs one named variable set after a jump (§501-R) | loop → cse → global | `loop.c` movables (`scan_loop`/`move_movables`), `combine_movables`; `cse.c:826-858` canonical choice; density as above | The hoisted temp's ref count (7 weighted) placed it between two hoisted constants (§501-R); a named variable set after a jump is never a movable. | Same; read the `.loop` dump for `moved to` lines and the `.lreg` refs. | M |

### 1c — `$0`-pinned "zero variables" (`register int zr __asm__("$0"); c = a + zr;`) and what replaces them

The `$0`-add (RC-12, `regalloc.md` §G) exists because a plain copy `c = a` never survives as a `move`: cse joins `c` to
`a`'s class (`insert_regs` `cse.c:1025-1032` → `make_regs_eqv` :826; the register with the LATER last mention becomes the
canonical head :846-858) and `canon_reg` (:2532-2575) rewrites the other one's uses, so the copy dies (`delete_dead_from_cse`
`toplev.c:2867` / flow); if it survives cse, local-alloc ties dest to a dying source with `may_save_copy` (`local-alloc.c:1287-1295`)
and the self-move is deleted post-reload (`sched.c:4804-4817`, `jump.c:308`). `(plus a (reg 0))` is not a copy for any of
those passes, and `$0` is fixed so it poisons nothing. Removing the pin therefore produces either Class 2 (the copy
folded, −1) or Class 1 (a different canonical/tie choice → the register flow changes).

| rank | source move (replacement for the `$0` pin) | pass | decision | mechanism | how to test | conf. |
|---|---|---|---|---|---|---|
| 1 | **Declare the copy's destination 16-bit** (`s16`/`u16 v = t;`) when it feeds ≥2 consumers (§194-B) | expand → cse → combine | HImode dest: `insert_regs` mode test `cse.c:1017-1019` refuses to join the class; combine cannot fold a 2-use HI subreg (`can_combine_p` needs the def dead at i3, `combine.c:1458`); the extend at each `sh` use is free | The narrow copy is a mode-changing set that is neither a cse equivalence nor a single-use combine candidate, so it is emitted as `addu v,t,$zero` — the same bytes the pin produced. Bound: ≥2 surviving consumers; the SOURCE must stay 32-bit. | Same harness; expect count parity with the pinned draft and the copy in place; `s32` control must lose the copy (−1). | H (byte-proven idiom, mechanism partly source-verified) |
| 2 | **Re-set the SOURCE after the copy** so its class is stale at the later use (`a = …` a real second assignment, or the dead-reset `a = 0;` right after the last use — §373) | cse | `reg_tick`/invalidate on a SET (`cse.c` `cse_insn` tail :7250-7262) ; `make_regs_eqv` head rule :846-858 | If `a` is re-set between the copy and `c`'s uses, `c` cannot be replaced by `a`; if `c` is the head, `a`'s later uses are rewritten to `c` and the copy still stands. | Same; expect the copy to survive; if flow deletes the dead reset it costs zero bytes (§373's law). | M |
| 3 | **Put a real CODE_LABEL (join) between the copy and its use** — an `if/else` diamond so the merge label is barrier-preceded (§H.1), not a bare `goto L; L:` (deleted by jump1, §194-N) | cse | `new_basic_block` `cse.c:766` (table flushed at every label); -O2 `follow_jumps`/`skip_blocks` extend EBBs only along the taken/skipped path (`toplev.c:3389-3390`, `cse.c:8118/8150`) | The class dies at the label, so the use after the join keeps reading `c`. | Same. | M |
| 4 | **`__asm__("addu %0,%1,$zero" : "=r"(c) : "r"(a))`** (S13 asm-copy) | expand | asm is opaque to cse (`rtx_cost` ASM_OPERANDS = 1000, `cse.c:720-724`) and non-combinable (`can_combine_p` `combine.c:868-870`) | Same bytes as the pin, but a `#APP` marker blocks maspsx's delay-slot hop (RC-11 caveat) and is what the engine is trying to remove. | Only as a control. | — |
| 5 | **Accept the fold and fix the register flow instead** — when the target has NO copy, the draft's zero-variable was compensating for a different canonical choice: make `a`'s last mention the later one (or `c`'s) so cse picks the target's head | cse | `make_regs_eqv` `cse.c:846-858` (`regno_last_uid[new] > regno_last_uid[firstr]` and beyond the block) | Which of `a`/`c` survives decides which register every downstream use reads. | Same; expect −1 count AND the target's registers. | M |

---

## Class 2 — a different instruction COUNT

One side has a `move`/`addu rX,rY,$zero`, an `addiu`, an `lh`/`lw`, an `la` (`lui`+`addiu`), an `sll/sra` pair, or a
`sw` the other does not. Sub-families, each with its own pass.

| rank | source move | pass | decision | mechanism | how to test | conf. |
|---|---|---|---|---|---|---|
| **Copies (`move` / `addu rX,rY,$zero`)** | | | | | | |
| 1 | **Inline the single-set temp at its use / name a subexpression in a temp** | cse → local-alloc | `cse.c:1025-1032` + `:2532-2575` (copy dissolves), `local-alloc.c:1287-1295` (tie), self-move deleted `sched.c:4804-4817` / `jump.c:308` | A copy survives only when neither cse can rewrite one side's uses nor local-alloc can tie (both live afterwards, or a label/re-set between). Naming a value that the target computed in place, or inlining one the target copied, is ±1. | Same harness; expect ±1 with the rest shifting; `-fno-schedule-insns` attribution irrelevant (this is cse/alloc). | H |
| 2 | **Narrow the copy's destination to 16 bits with ≥2 consumers** (1c-1) or widen it to 32 to lose the copy | expand/cse/combine | as 1c-1 | The width lever is the pin-free way to KEEP a copy the target has. | Same; `u16` and `s16` equivalent, `s32` loses it, `(s16)` cast on an `s32` adds `sll/sra` (+1, wrong family). | H |
| 3 | **Make the destination variable in-place (`v = -v`) instead of `t2 = cond ? -t1 : t1`** (RC-9) | global (no coalescing) | `global.c` has no coalescing; only `set_preference` :1535 | A cross-block copy the target lacks means the original used ONE variable. | Same; expect −1 and the phi `move` gone. | H |
| 4 | **Chain assignments `*b = *a = v;`** (§205) vs two statements | expand (one expression) → sched2 LUID | `expr.c` `expand_assignment` with `want_value` keeps both stores in one RTL run; §194-F: `if ((*p = v = f()) == 0)` SPLITS a pseudo | Count-neutral usually, but the chained form changes which pseudo carries the value between stores (a copy may appear/disappear) and the LUID span. | Same; expect a `move` to appear/vanish or an arg copy to move (Class 3). | M |
| 5 | **Split a `%` into quotient form `x - (x/K)*K`** or `&` vs `%` for power-of-two divisors (§176-E) | expand (`expand_divmod`) | `expmed.c` division expansion; `x*2` vs `x<<1` is NEUTRAL (`expand_mult` `expmed.c:2136` → `synth_mult` :1898 picks the shift; cse `rtx_cost` :700-706 treats MULT by 2^n as a shift) | Signed `%` emits the sign-correction sequence; the quotient form gives the intermediate its own pseudo (caller-saved) instead of coalescing into the callee-saved result → reorg can duplicate the `sra` into the slot. | Same; expect ±N instructions matching the target's sign-fix dance. | H |
| **Address materialization (`la` = `lui`+`addiu`, `addiu rX,rY,K`, `addiu $aN,$sp,K`)** | | | | | | |
| 6 | **Give the address a pointer local used ≥2× in one EBB, or remove it** (`p = &D_x; … p->f … p->g`) | cse (`find_best_addr`) → global | `cse.c:2622-2700`: an address in the table is replaced by the cheapest equivalent — `ADDRESS_COST(REG)=1` (`mips.h:2895`) vs `SYMBOL_REF` = 2 unless `SYMBOL_REF_FLAG` (`mips.c:1600-1620`) → every `(mem (symbol))` in the EBB becomes `(mem (reg))`; the pseudo then survives calls (`invalidate_for_call` kills hard regs only, `cse.c:1725`) and crosses them in an $s-reg | One `la $sN,SYM` + `lw 0($sN)` per use vs a macro `lw $r,SYM` per use: the count differs by 1 per shared address and the $s-bank grows (§153's symptom; `cse_expr.md` §2/§3). Kill it with the §373 dead-reset or the §153 launder; create it with a pointer local / a second `&SYM` argument in the same EBB. | Same; expect ±1 `la` and one $s-reg more/less; `.cse` dump shows the `(mem (reg N))` substitution. | H |
| 7 | **Nested-block pointer local + post-call `__asm__ __volatile__("" : "=r"(q))` for a frame address** (`cse_expr.md` §2) | cse | volatile SET's dest invalidated (`cse.c:7110-7114` map), `CONSTANT_P` excludes `(plus fp K)` (`rtl.h:237-240`) so it can never remat via `update_equiv_regs` :1031 | Per-site `addiu $aN,$sp,K` vs one hoisted `addiu $sN,$sp,K` + `move`s. Boundary: a struct block-copy of the same local re-seeds the class (§176-D2). | Same; expect −1 per call site and one fewer $s-reg. | H (map byte-proven) |
| 8 | **Pass a stack buffer as a decayed array (`T buf[N]`, pass `buf`) rather than `&s`/`*(T*)arr`** (RC-7) | cse/reload | `CONSTANT_P` gate `local-alloc.c:1031`; `rtl.h:237-240` | Only SYMBOL_REF/CONST_INT equivalences get slot-less rematerialization; a frame address never does — but the array-decay form keeps the address inline in the arg load. | Same; expect the per-call `addiu $sp` to appear and an $s-reg to vanish. | M |
| 9 | **Use an offset pointer temp `q = p + K` at ≥2 sites vs `*(T*)(p+K)` per site** | combine | `can_combine_p` `combine.c:803-900` + `try_combine`'s `added_sets_2 = ! dead_or_set_p (i3, i2dest)` (:1458): a def is merged into its use only when it dies there | A single-use address computation folds into the MEM offset (0 insns); a 2-use one stays as one `addiu` (+1). | Same; expect ±1 `addiu`. | H |
| 10 | **Two walked pointers vs one base + offsets** (L1) / bare `*q` vs `*(T*)q` (L1-4) | loop | `basic_induction_var` `loop.c:4819`, `combine_givs` :5494, `find_mem_givs` :4198 exclusion, giv init `:5556` (`if (reg != result) emit_move_insn`) | Each separately-incremented pointer is a biv (+1 `addiu` per iteration); a bare deref keeps a biv alive beside the combined giv (+1); the giv-init `addu dst,base,$zero` exists only when the init is not coalesced (§34 fence). | Same; read the `.loop` dump for `possible biv` / `combined with` lines. | H (map byte-proven) |
| 11 | **Write the loop limit inline in guard and condition vs a cached `end` local** (L4) | loop | `move_movables` `loop.c:1529`, threshold `scan_loop` :532 (29 with a call / 58 without), single-use substitution :735 | Inline invariants become movables hoisted to the preheader (+copies); a cached local computes once (fewer insns, different regalloc). `__asm__("")` pads count as real insns for the threshold (§501 law 2). | Same; `.loop` dump `moved to` / `not desirable`. | H |
| **Reloads and re-loads (`lh`/`lw`/`sw` present on one side)** | | | | | | |
| 12 | **Spell the store as bare `*p = v` (flushes the whole cse memory table) vs `p->f = v` / `p[k] = v` (kills only varying/struct entries)**; `u8` stores flush everything | cse | `note_mem_written` `cse.c:7539-7580` (`all=1` unless `MEM_IN_STRUCT_P || PLUS` and not QImode), `invalidate_memory` :1701-1720 | Whether a global re-loads after a pointer store (+1 `lw`/`lh`) is decided by the store's spelling, not the scheduler. | Same; expect ±1 load after the store. | H |
| 13 | **Put a call (or remove one) between two reads of the same memory** | cse | `cse.c:7241-7247` (`invalidate_memory(&everything)` for a non-const call) | Any call kills every cached load; pseudos survive (`invalidate_for_call` :1725 kills hard regs only). | Same. | H |
| 14 | **Keep two uses of a spilled value in one label-free run** (e.g. §16 shared-ret0 `goto`) | reload | inheritance `choose_reload_regs` `reload1.c:4903` (`reg_last_reload_reg` :83, reset at labels/jumps :3969-3990); `delete_output_reload` :6890-6912 (deleted only if no label/jump intervenes) | A second `lw` of a spilled pseudo, or the `sw` back to its slot, exists only when a label/jump separates the uses. | Same; expect ±1 reload. | M |
| 15 | **Declaration order of spilled locals** (RC-1) and the width that forces `reg_max_ref_width` 8-rounding | reload | slot loop `reload1.c:658` in regno order → `alter_reg` :2309; K7 | Moves slot OFFSETS, not counts — but a narrow local referenced through `subreg:SI` changes the slot shape, and a §501-Q self-update ghost (`combine.c:2306-2313`: bookkeeping skipped when `i2dest_in_i2src`) mints an 8-byte no-traffic slot. | Same; `tools/ghost_census.py` on the dumps. | H (offsets) |
| **Extends and narrow arithmetic (`sll/sra`, `andi 0xffff`, `sll 16/sra 16`)** | | | | | | |
| 16 | **Change a local's width/signedness** (`s32` ↔ `s16`/`u16`; `u8` is a semantic change) | expand → combine | no PROMOTE_MODE; `(s16)` cast on an SImode local emits `sll/sra` (+1, §194-B); `u16` load + arithmetic in the narrow local re-plans the block (§194-D, count-neutral) | The width decides whether an extend is emitted, where, and whether combine can fold it into the load (`lhu`/`lh` selection is the SOURCE deref width, a separate axis). | Same; sweep width per local, one axis at a time. | H |
| 17 | **Cast at the use vs at the def** (`s32 x = (s16)load;` vs `(s16)x` at each use) | expand/combine | as 16 | Decides ONE extend at the def vs N at the uses (or none, if each use folds). | Same. | M |
| **Control-flow-created counts** | | | | | | |
| 18 | **`for`/`while` ↔ `do … while`** (exit test at top vs bottom) | jump1 | `duplicate_loop_exit_test` `jump.c:2131` (copies the exit test to the entry when no call/label/nested loop is inside) | The duplicated guard is +N instructions; a `do…while` has none. | Same; expect the guard block to appear/vanish. | H |
| 19 | **Duplicate case tails vs merging them with a `goto`** (§501-B); a zero-byte barrier at the BOTTOM of a twin (§336) | jump2 cross-jump (post-reload) | `find_cross_jump` `jump.c:2371` walks BACKWARD from the converging jump; `toplev.c:3142` (`cross_jump=1` after reload) | Merging happens after allocation — the duplicated source keeps each tail's refs (Class 1b) and cross-jump then deletes the identical tails; a C-level merge deletes them before flow. | Same; the count is equal either way but registers differ (1b-1); a barrier at the wrong end is walked past. | H |
| 20 | **Add `case 0: return;` (a third case node) / drop one** (§339) | expand (`emit_case_nodes`) | `stmt.c` case-node emission: the low-bound `slti/bnez` is omitted with exactly two nodes | ±2 instructions in the switch head. | Same. | H |

---

## Class 3 — the same multiset in a different ORDER

sched1 (`schedule_block` `sched.c:3144`) is a BACKWARD list scheduler per basic block: it picks `ready[0]` (:3747) after
sorting by `rank_for_schedule` (:2385): (i) highest `INSN_PRIORITY` (:2395; `priority` :1425 = longest latency chain from
the block top via LOG_LINKS, formula :1490 `pri(pred) + cost(pred) − 1`; load cost 2, ALU 1, anti/output cost 0→1 via
`ADJUST_COST` `mips.h:2944-2946` and `insn_cost` :1408-1418; a dependence INTO a `USE`/asm is free :1394-1396), (ii) class
vs the last-scheduled insn (:2398-2421 — an insn feeding the just-placed one through a cost>1 link is demoted), (iii)
**LUID = source order** (:2428, assigned at :2175). `schedule_select` (:2616) then queues unit-blocked insns and moves the
largest `potential_hazard` (:1318) to the front within an equal-priority group. `adjust_priority` (:2507, pre-reload only)
boosts a ready single-set SET whose dest is live to `max_priority` (:2540-2546 → `birthing_insn_p` :2469, `reg_n_sets == 1`
at :2490, hard regs included) — the boost sinks single-set defs to just above their first consumer. sched2 reruns with
hard registers (no boost), and its LUIDs are sched1's output. `reorg.c` fills a slot from the nearest ELIGIBLE insn ABOVE
the branch/call (`fill_simple_delay_slots` :2799, backward scan :2907-2950), else steals from a thread by prediction
(`mostly_true_jump` :1335).

| rank | source move | pass | decision | mechanism | how to test | conf. |
|---|---|---|---|---|---|---|
| 1 | **Reorder independent statements to the target's order** (transcribe the target block; one statement group at a time) | sched1 | `rank_for_schedule` LUID tie-break `sched.c:2428`; LUID :2175 | Among equal-priority, class-equal insns the schedule IS source order (S1). Attribution first: if `-fno-schedule-insns` keeps the pair in source order the order was fixed at expansion (§76) and this IS the lever. | Compile through the oracle; expect the reorder to close with no register change. If registers churn, the move also changed births (Class 1a-5) — apply RC-3 pins-first protocol or accept. | H |
| 2 | **Make a value single-set (fresh local) to CREATE the birthing boost, or give it a second set to KILL it** (`__asm__ volatile("" : "=r"(x))` after its last use, `x = x` will not do — cse deletes it; a `lui`+`ori` constant is already 2 sets) | sched1 | `adjust_priority` :2540-2546, `birthing_insn_p` :2469/:2490; `reg_n_sets` counted post-cse (`flow.c:2065`) | A single-set def is boosted to max priority when it becomes ready → placed just above its consumer (a `li`/`move` sinks into the jal-adjacent position and dbr slots it, D1); a multi-set def stays at its LUID position. §501-D: ONE value-returning call in a function makes that call birthing for `$v0`. | Same; `.sched` dump shows `(7f000001)` priorities. Expect a def to move between "source position" and "just above its use", and a jal/branch slot to change (D1). | H |
| 3 | **Move a statement above/below a call** (a store the target fills into the jal slot must be written BEFORE the call) | reorg | `fill_simple_delay_slots` backward scan :2907-2950 (never hoists an insn emitted after the call into its slot); calls flush memory deps `sched.c:1748` | §176-A: an arg-register-addressed store in a `jal` slot proves the statement precedes the call. | Same; expect the slot content and a `nop` to swap. | H |
| 4 | **Wrap one statement in `do { } while (0)`** (loop-note barrier) or place a zero-byte `__asm__ __volatile__("")` AFTER the defining statement (§194-A) | sched1 | `sched.c:2058-2074` (LOOP_BEG/END in mid-block: every reg dep + `flush_pending_lists`), `:1957` (`code != ASM_OPERANDS || MEM_VOLATILE_P` — a volatile asm or colon-less `asm("")` is the same two-sided barrier; a non-volatile `asm("" ::: "memory")` is NOT) | A two-sided barrier at its own position: everything above it emits first. The `do…while(0)` form is barrier + ref-weight + cse1 break in one (see 1a-7); the bare `asm` is barrier only. Neither can raise a priority (§373-3: an asm's own priority is always 1). | Same; expect a computation to move to the head of its block. Precondition: nothing else left above the barrier. | H (asm) · M (do-while) |
| 5 | **Give the store's pointer a second set** (`p = &SYM; __asm__("" : "=r"(p) : "0"(p));`) to blind the alias oracle; or reverse a false edge by swapping the load/store source order (§340) | sched1 alias analysis | `init_alias_analysis` `sched.c:399-438` (`reg_known_value` only for single-set REG_EQUAL pseudos, gate :426), `canon_rtx` :371, `memrefs_conflict_p` :614, `true/anti_dependence` :817/:845 | With one set the store's `(mem (reg p))` is canonicalized to the symbol and proved disjoint → loads hoist over it; with two sets the oracle gives up → an anti-dependence pins the store first (§194-K). Direction = source order. | Same; `.sched` LOG_LINKS on the loads appear. Count may change by the remat coupling (`local-alloc.c:1021`). | H |
| 6 | **Grant or deny `/s` (`MEM_IN_STRUCT_P`)** — `((struct{s32 f;}*)p)->f` / `q[k]` grants, bare `*p` / `*(T*)(p+k)` denies; never on `u8` | sched1 (and cse store-flush) | `true_dependence`/`anti_dependence` escape clauses `sched.c:831-838` / `:855-862` (`/s` + varying + non-QImode vs fixed non-`/s`); setters in `expr.c` (`expr.c:4568` INDIRECT_REF PLUS rule per `cite_overrides.tsv`; member refs unconditional) | Decides whether a pointer load/store may cross a fixed-symbol store/load (§30 both directions). Anti edges are NOT free in 2.7.2 (`insn_cost` has no anti case) — restoring them re-groups downstream stores. | Same; expect a load to float over / stick under a store. | H (map byte-proven) |
| 7 | **Reuse one `s32` temp pair across two load pairs** (S12 fence) vs fresh temps | sched1 | WAR/WAW deps on pseudos `sched.c:1721-1728`; HImode temps vanish via combine (type trap) | Forces pairing (`lhu;lhu;subu / lhu;lhu;subu`) instead of batching all loads. | Same. | H |
| 8 | **Change the declared width of a local that RECEIVES a computed value** (`u16 b = load + K` vs `s32`) | sched1 (mechanism open) | attribution only: `-fno-schedule-insns` converges the spellings (§194-D); `birthing_insn_p` refuted as the cause | Count-neutral block re-plan; fires only where sched1 has freedom. | Same; sweep width; state "sched1 owns it". | M |
| 9 | **Make a call's argument a temp / hoist a call out of an expression** | expand (`preexpand_calls`) → LUID | `expr.c:8672-8730`: every CALL_EXPR inside an expression is expanded BEFORE the rest of the expression (`binop:` calls it first :6454) | `x = a + f(b)` evaluates `f(b)` first, then loads `a` — naming `f(b)` in a temp or naming `a` first changes the emission order and the pseudo births around the call. | Same; expect operand loads to move across the call. | M |
| 10 | **Swap the arms of an if/else or invert the condition** | expand → jump → reorg | `do_jump` polarity; `invert_jump` `jump.c:3594`; prediction ladder `mostly_true_jump` `reorg.c:1335-1435` (EQ→not-taken, NE→taken, loop-exit unlikely…); `own_thread_p` :2151 (MOVE vs COPY steal) | Polarity picks the fall-through arm (the one that coalesces to nothing, §501-P), the eager-steal thread (D3), and cross-jump identity. | Same; expect the slot fill to move to the other arm or a `label+4` target to appear/vanish. | H |
| 11 | **Change the join block's FIRST statement** (a store/load/macro is slot-ineligible; a dead-dest reg op is eligible) | reorg | `eligible_for_delay` (`mips.md:125-140` `define_delay`: `dslot == no`, length 1); `mark_target_live_regs` :2441 | A `nop` in the target's slot where you fill one (or vice versa) is eligibility, not order. | Same. | H |
| 12 | **Move a hard-register-pinned value's def around a call → UNPIN it** (§176-C) | sched1 | `sched_analyze_1` hard-reg arm `sched.c:1704-1707` tests `call_used_regs[i]` with `i` the sub-word index (always 0 = `$zero`, call-used) → EVERY hard-reg SET gets an anti-dep on the last call; pseudo arm :1732-1733 is gated on `reg_n_calls_crossed == 0` | A pinned def can never schedule above a preceding call; a pseudo can. | Same; expect the def to rise above the call once unpinned. | H |
| 13 | **Keep the incoming arg regs busy / free** (1a-9) to change which independent insn is READY for the load-gap (S4) and which fills the hazard spacing (S5) | sched1 | `schedule_insn` queue :2600-2602 (cost-2 link → queued one cycle; a ready independent insn wedges in), `schedule_select` :2616-2700 | The gap exists iff something independent is ready; statement order/availability picks the filler. | Same. | M |
| 14 | **Prologue weave** — nothing prologue-side; change the body insn that first writes `$sN` | sched2 | MIPS prologue is RTL, saves emitted descending regno (`mips.c` `save_restore_insns`), woven by sched2 under the same rules; epilogue is NOT scheduled (map A23) | An early body write of `$s1` pulls `sw $s1` down/up. | Same. | M |

---

## What the engine should classify from the masked instruction diff

Work on the masked diff (`tools/masked_diff.py`), per contiguous residual window, in this order:

1. **Count test.** `len(mine) != len(target)` in the window ⇒ **Class 2**. Identify the extra/missing opcode:
   - `addu rX,rY,$zero` / `move` → copies family (rows 1–5; try 1, then 2, then 3).
   - `lui`+`addiu` / `la` or a second `addiu rX,rY,K` → address family (rows 6–11; try 6/9 first if the operand is a symbol
     or a `p+K`, 7/8 if `$sp`-relative, 10/11 if inside a loop).
   - `lw`/`lh`/`lhu`/`sw` to a `$sp` slot → reload family (rows 14–15); to a symbol or pointer → cse family (12–13).
   - `sll 16`/`sra 16`/`andi 0xffff` → width family (16–17).
   - a whole guard/test block or a switch head → control family (18–20).
2. **Multiset test.** Same length and the sorted opcode+immediate multisets are equal but registers differ ⇒ **Class 1**.
   - Only $16–$23 differ (a permutation) ⇒ **1b**: run `tools/alloc_table.py` on the dumps, compute R,L for the
     contenders, pick 1b-1/2 (density) or 1b-3 (exact tie) or 1b-4 (a single-set const/address among them).
   - $2/$3 or $4–$7 differ, callee-saved identical ⇒ **1a**: if the window contains a 3-operand ALU whose dest matches a
     different operand's register on each side (`op d,d,x` vs `op d,x,d`) ⇒ tie (1a-1, 1a-2 for var/var, 1a-8); if a
     temp's register is reused/not reused across two computations ⇒ 1a-3/1a-4; if the two values are born in
     different order ⇒ 1a-5/1a-6; if the window sits inside a call's arg setup ⇒ 1a-9.
   - a `move` present on both sides but with a swapped source/dest role ⇒ **1c** (cse canonical choice, 1c-5).
   - The `reg_renumber`-swap oracle (`tools/oracle/reg_renumber_swap.sh`) discriminates "allocation caused the reorder"
     from "the schedule is independent" in one run — check the `.greg` operand is a PSEUDO first (map §H precondition).
3. **Order test.** Same multiset, same registers per instruction (modulo the register renaming implied by the order)
   ⇒ **Class 3**. Attribute first: recompile with `-fno-schedule-insns` (sched1) and `-fno-schedule-insns2`; if neither
   changes the residual it is expansion order or dbr (rows 1, 3, 9–11); if sched1 owns it:
   - a single def far from / adjacent to its consumer on one side ⇒ boost (row 2);
   - a load/store group swapped as blocks with a pointer base ⇒ alias oracle (row 5) or `/s` (row 6);
   - loads batched vs paired ⇒ row 7;
   - a computation your draft emits late that the target emits first at the block head ⇒ barrier (row 4);
   - a store/`li`/`move` in one side's delay slot and a `nop` in the other ⇒ D1/D2 (rows 3, 11) — fix adjacency, not the slot.
4. **Coupling rule.** Every Class-3 move that changes a live length or a ref count re-runs Class 1 (sched1 writes
   `reg_live_length`, `sched.c:4947`); every Class-1 move that changes `reg_n_sets` re-runs Class 3 (the boost) AND the
   alias oracle AND the remat gate. The engine should therefore score the WHOLE function after each move, never the window.

---

## Open questions / things I could not settle from the source

1. **The `const & var` swap anchor vs `fold-const.c:3179-3189`.** The source says `build_binary_op` (`c-typeck.c:2698`
   `folded = fold (result)`) moves an INTEGER_CST left operand of `&`/`|`/`^`/`+`/`*` to the right before expansion, and
   `optabs.c:416` would swap a CONST_INT op0 again — so swapping `~0x20 & x` ↔ `x & ~0x20` should be byte-neutral. The
   measured fact (a swap of one `&` closed func_80163EC8's `lw/li/and` residual) is therefore either (a) a swap of two
   NON-constant operands, (b) a swap applied together with the temp inlining §454 records for the same function, or (c) a
   path I did not find. **Test:** compile `int f(int *p){return *(p+17) & -33;}` and its swapped twin standalone through
   `match_one`-style byte compare; then the same with `int m = ...; return m & x;` (var/var). If (a)/(b) hold, the engine's
   `perm_commutative` should be restricted to var/var operands (cse profile weight 40 vs regalloc 2, §454, is then explained).
2. **`do { } while (0)` — which of the three effects closed func_80135D20?** Flow's ref weighting (`flow.c:1401`), sched1's
   loop-note barrier (`sched.c:2058`), and cse1's EBB break (`cse.c:8054`) are all live for a zero-trip loop provided the
   LOOP notes survive jump1; I did not verify in `jump.c` that a `do…while(0)` (constant-false exit, back-jump deleted) keeps
   its NOTE_INSN_LOOP_BEG/END. **Test:** `-da` on the micro-case; grep the `.jump`/`.flow` dumps for the notes; compare
   `.lreg` refs of the wrapped variable against the `{ }` control.
3. **The ≤3-quantity sort (`local-alloc.c:1493-1508`).** The map calls it a bug (creation order wins when qty 1 is best).
   Reading the two exchanges: `(0,1)` then `(1,2)` then `(0,1)` again is a correct 3-element sort for the FIRST switch (the
   suggestion pass) and the second; I could not confirm the claimed mis-ordering without running it. Treat RC-11's decoy
   trick as a measured effect, not a proven mechanism.
4. **Whether `expand_decl_init` vs a separate assignment differ when ADJACENT.** Both go through `expand_assignment`
   (`stmt.c:3592-3595`); the only difference I can find is emission position. If the engine sees R3 close a body with no
   intervening statement, something else (a `NOTE_INSN` boundary or `TREE_USED`) is at work — record it.
5. **`mips_address_cost` for `SYMBOL_REF`** returns 1 when `SYMBOL_REF_FLAG` is set (`mips.c:1600-1620`); under `-G0` I did
   not confirm which symbols carry the flag (it marks small-data/`gp`-relative symbols). If any do, `find_best_addr` will
   NOT replace them with a register (cost tie → keeps the higher `rtx_cost` form) — the address-sharing lever (Class 2 row 6)
   would then be selective. Test on one `D_*` global vs one `.sbss` symbol.
6. **The reload commutative retry (`reload.c:3273-3303`)** can in principle print `and d,x,y` as `and d,y,x` post-allocation
   when the swapped alternative wins; for `andsi3`'s `"%d,d"/"d,K"` both orders of two registers tie on alternative 0 and the
   unswapped one is kept, so I rate it inert here — unverified on bytes.

## Contradictions between the source and the project's map (for the map's own ledger)

- `regalloc.md` §A K1 still says "creation order (= regno order)" is the qty tie-break; `local-alloc.c:1622` breaks ties on
  qty NUMBER, which is BIRTH order in the post-sched1 stream (`reg_is_born` :1976-1997) — the map's own [A23] item 5 already
  says so; the two sentences coexist. This file uses birth order throughout.
- `regalloc.md` RC-4 cites `combine_regs` at `:1825` — that is the 2.8.1 line; vanilla is `:1722` (tie test `:1855`, hard-reg
  suggestion `:1798/:1824`).
- `sched.md` §1.1 says the LOOP notes matter only for `reg_n_refs`; `sched.c:2058-2074` shows a mid-block LOOP_BEG/END is
  also a FULL scheduling barrier — relevant to the `do…while(0)` lever the engine found.
- `cse_expr.md` §1's class-killer table says a volatile asm invalidates NOTHING; `cse.c:7250-7262` invalidates every SET dest
  (the map's own [A23] correction) — consistent with §373/§153 levers, inconsistent with that row.
- `loop.md` L0 states args expand right-to-left in one place and the [A23] correction says left-to-right; `calls.c:1330`
  and `:1850` iterate `i = 0 … num_actuals` (ascending), supporting left-to-right.

## Verified anchors (all `tools/reference/gcc-2.7.2/`, from `grep -n` this session)

`toplev.c` 2826-2827 2865 2867 2895 2926 2983 3004 3033 3051-3052 3080 3082 3117 3142 3167 · `fold-const.c` 3179-3189 ·
`c-typeck.c` 1901 2698 · `expr.c` 4568 6453-6459 8672-8730 · `optabs.c` 399-418 · `cse.c` 683 720-724 766 826 846-858 1007
1017-1019 1025-1032 1701 1725 2532 2622 4435-4443 5231-5290 7241-7247 7250-7262 7539-7580 8054-8055 · `combine.c` 803 868-870 1191 1458
2306-2313 2973-2985 · `reload.c` 3273-3303 3345-3360 · `local-alloc.c` 279 472 947 973-975 1021 1064 1080-1084 1090-1116
1123 1229 1241 1287-1298 1472 1493-1512 1579 1622 1722 1765 1798 1824 1855 1954 1976 2013 2073 2106 2158 2175 ·
`global.c` 277 352-360 384-397 546 587-611 904 927 947-985 1001-1071 1102-1160 1535 · `regclass.c` 1791 · `flow.c`
1401 1403 1447 1449 1650 1684 2058-2073 2101 2315 2501 2533 · `sched.c` 371 399 426 614 817 845 1318 1363 1394-1396
1408-1418 1425 1490 1704-1707 1721-1733 1748 1957 2058-2074 2175 2265-2268 2385 2395 2398-2421 2428 2469 2490 2507
2540-2546 2557 2572-2575 2600-2602 2616 3144 3189-3210 3272-3330 3747 4804-4817 4830 4947 4964 · `reorg.c` 1335 2151 2441
2799 2907 3257 3632 3748 · `reload1.c` 658 2309 3591 3606 3645-3660 4706 4903 6890-6912 · `jump.c` 138 308 2131 2371 3594
· `stmt.c` 3316 3357-3364 3387 3551 3592-3595 · `function.c` 3157 3628 3679 · `emit-rtl.c` 460 515-516 · `expmed.c`
1898 2136 · `config/mips/mips.h` 1179 2622 2895 2944-2946 · `config/mips/mips.c` 1600 · `config/mips/mips.md` 125-140
1846-1856.

## Verification ledger (the engine's byte record against this map — appended by the coordinator, S101 2026-09-09)

| claim | test | result |
|---|---|---|
| 1a-2 / open Q1: a CONSTANT-operand commutative swap is a tree-level no-op (fold), a var/var swap is not | `.run/P36/engine/micro/c1.c` vs `c2.c` through `tools/permuter/compile.sh`, `masked_diff.diff_object_object` per function | **VERIFIED.** `*(p+17) & -33` ≡ `-33 & *(p+17)` (0 of 4 words); `m & x` vs `x & m` and `*(p+17) & x` vs `x & *(p+17)` differ in ONE word each (`and v0,v0,a1` vs `and v0,a1,v0`). R5 no longer generates a constant-operand swap. |
| 1a-7 / open Q2: which of the three `do { } while (0)` effects flips the allocation, and do the LOOP notes survive jump1 | the real TU of `func_80135D20` in three spellings (`flag = 0;` / `{ flag = 0; }` / `do { flag = 0; } while (0);`) through cpp + cc1 with `-dl -dS -dc -dg -dj -df` (`.run/P36/engine/micro/dowhile/`) | **VERIFIED: the ref weight.** The plain block changes nothing but label numbers; the do-while swaps `$17`/`$18` in the prologue and body, the `.jump` dump carries 15 LOOP-note mentions vs 12 (the notes survive jump1), the `.flow` dump 5 vs 4, and the `.lreg` "used N times across M insns" multiset differs in exactly one register: `used 5 times across 39 insns` → `used 6 times across 39 insns` (+1 = the set inside the zero-trip loop counted at loop_depth 1, `flow.c:1401/2067`). The barrier and the cse1 EBB break are present but not what moved this body. |
| 1c-1 / 2-2: a 16-bit copy destination keeps the copy as `move` | `delever_search --explain … --path "R12 width ang s32->u16"` and `"R12 width a s32->u16/s16"` on `func_80148D44`/`func_80148E54` (one surviving copy, `andi a0` then `move s0,a0`) | **NOT REACHED here:** score 6 unchanged for every width on either side of the copy — combine folds the narrowing of a value already masked to 12 bits (nonzero_bits), so the copy dissolves regardless. The bound in the row ("≥2 consumers, the SOURCE 32-bit") is necessary but not sufficient when the value's known bits fit the narrow mode. |
