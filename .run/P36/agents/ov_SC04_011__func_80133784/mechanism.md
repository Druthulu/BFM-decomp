# func_80133784 (ov_SC04_011) — mechanism

**Final score 2** (from 21; the mechanical search's best was 12). `mine 203 ins, target 203`, one
two-instruction residual left. Text: `PACK/body.c`. Harness calibrated first (R39): the tree's own
`body_tree.c` scores **0** through the same `--try` path, so the instrument was measuring this function.

## (a) The residual in one sentence

The lever-free body is two instructions SHORT of the target (201 vs 203) because two register-to-register
copies the target keeps are coalesced away (`sltiu v0,v0,1` + `move s2,v0`, and `move v1,v0` after the
loop's call), and — before those are even reachable — mine hoists the call argument's sign-extension `sll`
out of the loop and swaps two pairs of callee-saved registers (`arg0s`/flag, counter/accumulator).

Four independent defects, four different passes. Each was read from the compiler source, then proven on bytes.

## (b) The passes and the decisions, with `file:line`

### 1. The hoisted `sll` and the `$s2`/`$s5` swap — `loop.c`

`loop_optimize` only sees a loop where the RTL carries `NOTE_INSN_LOOP_BEG`/`NOTE_INSN_LOOP_END`, and those
notes are emitted **only** by the statement expanders (`stmt.c: expand_start_loop` emits the note then the
start label; `expand_end_loop` emits `NOTE_INSN_LOOP_END`). Inside such a loop the first call argument's
`(ashift (reg arg0s) 16)` is invariant — `invariant_p`'s REG case returns `n_times_set[REGNO] == 0`
(`tools/reference/gcc-2.7.2/loop.c:2745-2751`, the same place that makes a **hard** register never invariant,
because `loop.c:595-596` forces `n_times_set[i] = 1` for every hard reg: that is exactly what the tree's
`register s16 arg0s __asm__("$21")` pin was buying). `scan_loop` therefore records the `sll` as a movable
(`loop.c:645-710`; the dest is a compiler temp, so the `! REG_USERVAR_P && ! REG_LOOP_TEST_P` arm of the
three-way gate at `loop.c:694-700` passes), and `move_movables` hoists it into the preheader —
`loop.c:1631` `threshold * savings * m->lifetime >= insn_count`, and with a call in the loop
`threshold = 1 * (1 + n_non_fixed_regs)` (`loop.c:532`) is ~60 against an `insn_count` of ~15, so the test
never fails. Allocation then ties `arg0s` to the hoisted temp (`sll s2,s2,0x10` destroys the variable,
which is legal because every later use goes through the shifted value), and the flag/`arg0s` priorities swap.

**Move:** write the loop as `loop: { … if (oldc < 5) goto loop; }`. A label+`goto` loop carries no loop
notes, `loop_optimize` never registers a loop object, and the `sll` stays at the branch target exactly where
the target has it. PROVEN: the six diffs at indices 22/25/56/103/109/117 all vanish.
Controls: `while (1) {…break;}`, `do {…} while (s3++ < 5)` and `for (;;)` were each tried — **all three hoist**
(score 21); only the goto form does not. This is the *reverse* of cookbook §176 (`func_80186A04`, where a
goto-loop was rewritten as a `for` to GET the hoist).

### 2. The missing `move v1,v0` after the loop's call — `global.c: find_reg`

A call result reaches its pseudo through a real copy insn `(set p (reg:SI 2))`. Combine cannot delete it
(the pseudo has two uses), so it survives or dies purely by allocation: local-alloc's `combine_regs`
records `qty_phys_sugg` for a hard-reg source (`local-alloc.c`, the `if (ureg < FIRST_PSEUDO_REGISTER)`
arm), and for a *global* allocno `global.c: find_reg` follows `hard_reg_copy_preferences`. With a
dedicated `ret` variable that preference is free and the copy is coalesced into `$v0`. The function's
other call (`func_80047D3C`) already emits `move v1,v0` in **both** mine and the target, because that
result's live range does conflict with `$v0`.

**Move:** use **one variable `r` for both call results**. One allocno now spans both call sites, `$v0` is
no longer free across it, `find_reg` gives it `$v1`, and the copy out of the return register survives at
*both* sites — which is what the target has. PROVEN: 19 → 15, the whole loop region matches.

### 3. The missing `move s2,v0` on the flag — `combine.c: try_combine`

The dumps settle this one. In my body `.combine` holds a single
`(insn 128 (set (reg/v:SI 76) (eq:SI (reg:SI 118) (const_int 0))) 236 {seq_si_zero})` — combine merged
`(set r119 (eq r118 0))` with the copy `(set r76 r119)`; in `body_tree`'s dump the same two insns survive
with the `asm` wedged between them. Any *same-mode* copy whose source dies at the copy is merged
(`can_combine_p` `combine.c:803-…` lets it through: same block, LOG_LINK present, source dies, and
`INSN_CUID (i2) < last_call_cuid` does not apply because no call separates them).

**Move (partial):** declare the flag `u16`. The store is then a HImode subreg store that combine cannot
fold into the SImode `seq`, so `sltiu v0,v0,1 ; move s2,v0` comes out byte-exact. **Cost:** the loop test
`if (s2 != 0)` needs a zero-extension `andi v0,s2,0xffff`, and it lands in a delay slot that the target
fills with `nop` — this is the entire residual 2.

### 4. The prologue order of the two zero-inits / the `$s3`/`$s4` swap — `global.c: allocno_compare` + `flow.c`

`allocno_compare` ranks by `floor(log2 refs) * refs / live_length * 1e4` and breaks ties by allocno number
(declaration order — the counter is declared before the accumulator). The emitted order of
`move s3,zero` / `move s4,zero` (and of their prologue `sw`s, which sched2 pairs with them) follows the
**source** order of the two initialisers, so the source must read `s3 = 0; s4 = 0;`.

In a real `while` loop `flow.c:2071` (`reg_n_refs[regno] += loop_depth`) weights in-loop references ×2:
counter 1+3×2 = **7 refs**, accumulator 1+2×2+1 = **6** — measured with `tools/alloc_table.py`
(`free`: r77 7/89 = 1573, r78 6/87 = 1379) and the counter wins. In the goto loop there is no loop depth,
both have **4 refs**, and with the counter born one insn earlier its live length is 91 vs 89
(`u2`: r77 4/91 = 879.1, r78 4/89 = 898.9) — so the accumulator wins and takes `$s3`.

**Move:** hoist two repeated integer literals into named locals at the head of the `after:` block
(`lim = -0xBCB`, used twice; `mask = 0xFFFF`). `flow_analysis` runs **once, before combine**
(`toplev.c:2983` vs `:3004`), so those two sets are counted in `reg_live_length` even though cse/combine
fold them away and no instruction is emitted for them. The accumulator's live length goes 89 → **91** =
the counter's; the tie then breaks by allocno number in the counter's favour and it takes `$s3`.
PROVEN: 6 → 2, the prologue diff disappears, instruction count unchanged at 203.

## (c) The source moves (one line each)

1. `while (1) { … }` → `loop: { … if (oldc < 5) goto loop; }` — kills `loop.c`'s invariant hoist of the
   call argument's `sll` (21 → 22 alone, but it fixes 6 later diffs).
2. One variable `r` for **both** call results instead of `r` + `ret`/`ret0`/`retc` — makes the loop call's
   result land in `$v1`, so `move v1,v0` survives (19 → 15).
3. `s32 s2` → `u16 s2` — the HImode subreg store blocks `try_combine`, so `move s2,v0` survives (15 → 6).
4. `lim = -0xBCB` / `mask = 0xFFFF` hoisted into locals at the head of `after:` — pads the accumulator's
   flow-time live length by 2 at zero instruction cost, flipping `allocno_compare` (6 → **2**).

(Also: init order stays the natural `s1, s3, s4, s2`; `dx, dy, dz` dropped; `zt` inlined — all byte-neutral.)

## (d) Generator proposals

**Primary — `delever.deloop` (the reverse of the `for`-loop rewrite):** when the residual shows a
loop-invariant sub-expression of a call argument (typically an `sll`/`sra` of a callee-saved register)
sitting in the loop **preheader** in mine but at the **branch target** in the target, together with a
register swap involving that same register, rewrite the `while`/`for`/`do` loop as a label plus `goto` so
no `NOTE_INSN_LOOP_BEG` is emitted and `loop.c` cannot register a loop at all.

Two more, each byte-proven here:

* **`delever.share_call_result`:** when the diff is a missing `move <reg>,v0` immediately after a call,
  assign that call's result to a variable **already used for another call's result** in the same function —
  one allocno spanning both sites loses `$v0` and the copy survives at both.
* **`delever.liveness_pad`:** when two allocnos with equal `n_refs` are within a few live-length units in
  `allocno_compare` and the wrong one is allocated first, hoist a **repeated integer literal** into a named
  local declared at the head of the block where the allocno that must win is still live; `flow` runs once
  before combine, so the set counts in `reg_live_length` while cse/combine delete it (zero bytes). One unit
  per surviving literal; a literal whose only use is in a *nearby* block is folded early and buys nothing —
  `-0xBCB` (two uses) and `0xFFFF` (used in the far `store_out` block) each bought 1, `-0x578`, `0x4000`,
  `0x8000` and a hoisted `0` bought nothing.

## (e) What did NOT work, with byte evidence

* Ten spellings of the flag assignment with an `s32` flag — `s2 = (sz==0)`, `!sz`, `(sz?0:1)`, `(s16)/(u8)`
  casts, a named `zt` at function scope, `zt` with two sets, a dead second consumer, splitting the
  `&&` so the store lands in another block, a `goto`-split, a duplicated guard — **all score 19** (or worse):
  combine merges every same-mode copy whose source dies. Only a mode change blocks it.
* `do {…} while (s3++<5)`, `for (;;)`, `while(1)` — all hoist the `sll` (21). `arg0s = arg0s;` and
  `arg0s = a0v;` inside the loop do not defeat `invariant_p`: jump.c deletes the no-op move and cse
  propagates the copy's source, so the `sll` is invariant again (21).
* `do { … } while (0)` wedged inside the goto loop to buy back `flow`'s loop-depth ref weighting: the refs
  do inflate (r77 7/89, r78 6/87, verified in `alloc_table`) but the allocation rotates three ways
  (counter→`$s4`, accum→`$s2`, flag→`$s3`) — **26**, worse than doing nothing.
* All 24 permutations of the four zero-initialisers, on four different bases: the emitted prologue order
  always follows the source order, so no permutation gives both the right order and the right registers
  (best 6 either way).
* Swapping the `||` in the `after:` test (`D_801EDA3C` first) does buy the tie (both live lengths 91) and
  fixes the prologue — but reorders five instructions: net **10**, no gain. That measurement is what
  identified "+2 live units on the accumulator" as the actual requirement.
* Widths of `s1`, `s3`, `s4`, `a0v`, `arg0s`, `ret`, `retc`, `zt` (s8/u8/s16/u16/s32/u32): none helped;
  `s16 ret` gives `sll/sra` (2 insns) where the target wants one `move`.

## (f) Where the method fell short

* **`sites.txt` is a decoy at the shape level.** It listed 7 NEEDED sites; none of them named what actually
  had to change. One source-shape move (the goto loop) retired three of them at once, and the two
  `instruction addu` sites turned out to be two *different* mechanisms (allocation for one, combine for the
  other) that look identical in the table.
* **The residual text cannot separate "instruction missing" from "registers wrong".** Counting first
  (201 vs 203) and mapping each diff hunk to an index in the target's own `objdump` was what made the four
  defects separable. Recommend the pack print the target's disassembly of the function alongside `residual.txt`.
* **`alloc_table.py` was decisive but only after I stopped reading it as a ranking and started doing
  arithmetic on it.** The winning move came from "I need +2 live-length units on r78", which the table
  gives directly. A `--diff` mode (two tags side by side, priorities and live lengths only) would have
  saved most of the search.
* **The knowledge base has the `for`-rewrite direction but not the `goto`-rewrite direction.** Cookbook §176 documents
  turning a goto-loop into a `for` to *obtain* a hoist; the inverse — de-looping to *defeat* one — is the move
  that unlocked this body and should be banked next to it.

## Paths

* `PACK/body.c` — the best text (score 2).
* `PACK/mechanism.md` — this file.
* `PACK/scratch/` — the probe harness (`t.sh`, `mkdump.sh`, `dis.sh`, `sweep.py`, `probe.py`, `cut.py`),
  every candidate under `PACK/scratch/v/`, and the cc1 pass dumps under `PACK/scratch/dumps/`.
