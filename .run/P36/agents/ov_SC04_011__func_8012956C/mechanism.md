# func_8012956C (ov_SC04_011) — T7 agent c24 (S103 re-draw)

**Score 0, no lever of any kind** (`PACK/body.c`). Levers in the tree: pins `$7` temp_a3, `$4` arg0, `$3` s2 and one
`__asm__("")` at the head of `do_default:`. Start `body_free.c` = 11; the S102 agent's best = 4 (its files are kept
as `scratch/prev_body.c` / `scratch/prev_mechanism.md`). The same text, with that overlay's global names, also scores 0 on
the shared sibling `src/shared/ov/func_8012956C__3fa9093d.h` (`scratch/hdr_body.c`).

## (a) The residual in one sentence

Two defects, one per lever group: (1) the `j` into the default block steals the block's first insn
(`j <dflt+4>` + `sll a1,a1,16`) where the target leaves `j <dflt>` + `nop` — the `__asm__("")` faked this; (2) inside the
block the `f38` load is scheduled before `f40` (`lhu a3,4(s0); lhu v0,12(s0)` vs the target's reverse) — the `$7`/`$4`/`$3`
pins faked this. The count is the same (226 ins) in every version: a pure delay-slot plus order residual.

## (b) The passes and the decisions

### Defect 1 — the empty `j` slot is left by reorg's SECOND pass, not a refused steal

Tell-tale in the target: the SAME insn `addiu a1,s4,3` sits in the delay slot of BOTH branches into the default block
(`beq …,case_7FFD` at 0x1490 and `bne …,default` at 0x14a4), while the block itself starts at the `sll`. That is reorg
copying the block's OWN first insn onto every edge into it, which means the source computes `i + 3` INSIDE the default
block, not before the tests (m2c had hoisted it into the dispatch as `a1 = i + 3;` twice, because it read the delay slots).

With the add at the block head (proved in `scratch/dumps_fin/fin.i.sched2`: `code_label 316` → `insn 342 (set a1 (plus s4 3))`
→ `343 ashlsi3` → `348 ashrsi3`; reached by `jump_insn 491` (the `j`) and `jump_insn 496` (the `bne`)), reorg's two passes
(`reorg.c:4326-4332`, `MAX_REORG_PASSES` = 2 at `reorg.c:1089`) do this — read from source, consistent with the bytes,
not traced insn by insn:

1. pass 1, `fill_eager_delay_slots` (`reorg.c:3632`): the `j` (a `condjump_p`, condition `const_true_rtx`) fills from
   its target thread; the label has two users so `own_thread` is 0 → the `addiu` is COPIED (`reorg.c:3430`) and the `j` is
   redirected to a new label before the `sll` (`reorg.c:3615`). The `bne` then owns the (now single-use, barrier-preceded,
   `own_thread_p` `reorg.c:2151`) label and MOVES the original `addiu` into its slot, no redirect. The `beq case_7FFD` got
   nothing in pass 1: its fallthrough thread was the still-unfilled `j` (`stop_search_p`, `reorg.c:675`).
2. pass 2, the `beq case_7FFD` again: its fallthrough thread is now the `j`'s filled SEQUENCE →
   `steal_delay_list_from_fallthrough` (`reorg.c:1699`) takes the `addiu` (a1 is dead at case_7FFD, so it is safe on the
   taken path) and `delete_from_delay_slot` (`reorg.c:1741`) EMPTIES the `j`'s slot. The redirect from pass 1 stays →
   `j <sll>` + `nop`, exactly the target.

With the add in the dispatch (the tree/m2c shape), the `beq`'s slot is filled backward in pass 1 by
`fill_simple_delay_slots`, nothing is left to steal, and the `j` keeps the `sll` it stole → the 2-point residual. The
tree's `__asm__("")` got the `nop` only because an `ASM_INPUT` stops `fill_slots_from_thread` at the first trial
(`stop_search_p`, `reorg.c:696-698`).

The dispatch is a `switch`: the target's compare tree (`beq 0x7FFE`; `slti 0x7FFF`/`beqz`; `beq 0x7FFD` + `j default`;
`bne 0x7FFF → default` + `j end`) is `emit_case_nodes`' balanced tree (`stmt.c:5580`, the `test_label` split `:5640-5658`)
for three single-value cases. The last test comes out as `bne → default; j end` only when `case 0x7FFF: break;` is the
FIRST case in the body: the tree emits `beq → L7FFF; j default` (`stmt.c:5654`) and with `L7FFF` immediately following,
jump.c inverts a conditional jump over an unconditional one (`jump.c:1725-1757`). With `case 0x7FFF` last (`scratch/sw1.c`)
the code keeps `beq → end; j default` → score 7.

### Defect 2 — the `$7` pin was a phantom FOURTH argument

`func_801299C8` is a 3-parameter K&R function (`src/shared/ov/func_801299C8__f9a41b0d.h:3`: `(arg0, arg1, arg2)`); the
body called it through a cast `(void (*)(s32, s32, void *, s32))` with `temp_a3 = base->f38` as a 4th argument — m2c
reading `$a3` still holding `f38` at the `jal`. That argument adds a `(set (reg:SI 7 a3) (reg/v:SI 78))` copy before the
call and turns the f38 load into an SImode `zero_extend` load with two consumers (the add and the copy):
`scratch/dumps_t4/t4.i.sched` shows sched1 (`sched.c:2385` `rank_for_schedule`, priorities `sched.c:1425`) putting it first
(`insn 327` before `330`), where the 3-argument form has four plain HImode loads in source order f40, f38, f42, f3A
(`scratch/dumps_fin/fin.i.sched`, `insn 319 321 328 330`). The allocator still puts the f38 temp in `$a3` on its own. The
`$4`/`$3` pins were pinning the same pseudos into the argument/temp registers the phantom copy displaced.

Byte proof (each on the switch body): 4 args via `temp_a3` → 2 (`v_t4.c`, exactly the lhu swap); 4 args with `base->f38`
inline → 12 (`v_nat4.c`); 3 args → **0** (`v_nat3.c`, `v_a1_3.c`).

## (c) The source moves (11 → 0)

1. **Call `func_801299C8` at its real arity, with its argument computed where it is used:**
   `func_801299C8(D_801F1620, (s16)(i + 3), base);` — no cast, no 4th argument, no `a1`/`arg0`/`temp_a3`/`s`/`s2`/`t6`
   locals; the two field sums are written directly: `base->f1C = base->f40 + base->f38; base->f1E = base->f42 + base->f3A;`
   (the `(s16)` cast is the same one the 0x7FFE case already carries: the K&R callee takes an `s16`).
2. **The `goto` dispatch is a `switch (base->f34)`**, cases in the order `0x7FFF` (empty, `break`), `0x7FFD`, `0x7FFE`,
   `default`; `code`, the labels and every `goto` disappear.

Move 1 alone, kept inside the goto form, also scores 0 (`scratch/goto_nat2.c`) — but only because the dispatch's two
`a1 = i + 3;` become dead assignments, which the rules refuse; dropping them is what the switch spelling does. Move 2
alone (the switch with the old default block) scores 2 (`scratch/sw2.c`).

## (d) GENERATOR PROPOSAL

> **R24 `delay_slot_duplicate_sinks`** — when the TARGET shows one identical instruction in the delay slots of EVERY
> branch into a block (and the body assigns that value in the dispatch before those branches), move the assignment into
> the block's head — inline it into its single use when it has one — and delete the dispatch copies; when the dispatch is
> an m2c compare tree over one value (`==` k, `<` k+1, `==` k-1 …), re-spell it as a `switch`, trying each case's position
> (an empty `break` case first reproduces `bne → default; j end`).
>
> **R25 `arity_trim`** — for every call through a function-pointer cast, compare the argument count with the callee's
> real definition (grep `src/` and `src/shared/`); if the call passes MORE, drop the extras (and their temps) and call it
> directly. A `$4`–`$7` pin on a temp that is also a trailing argument is the symptom.

## (e) What did not work / earlier claims refuted (R14)

| claim or try | result |
|---|---|
| S102: "`fill_slots_from_thread` declined at the first trial; the only lever-free `nop` is a load at the block head" | refuted: the steal happens in pass 1 and pass 2's `steal_delay_list_from_fallthrough` empties the slot; a plain `addiu` heads the block |
| S102: "`x = A; x += B` → `x = A + B` removes the copies that confuse sched1" (11 → 4) | partly: it removed the `$3` copy; the remaining lhu swap was the phantom 4th argument (`v_t4.c` = 2 even with the fused sums) |
| switch with `case 0x7FFF: break;` last | 7 (`beq → end; j default` not inverted) |
| switch + S102's default block (4-arg call, pinned temps unpinned) | 2 (lhu swap) |
| switch + S102's original three-temp accumulate spelling | 9 |
| goto form + 3-arg call with `a1` | 2 (the `j` steal stays) |

## (f) Where the method fell short

* The residual printed the delay-slot hunk as `j`/`sll` vs `j`/`nop` and nothing pointed at the **other** delay slots,
  which were EQUAL in both versions and so never printed — but the fact that decided it was in them (the same `addiu`
  on both edges into the block). Reading the whole objdump (METHOD step 1) found it; a classifier rule "identical insn in
  the delay slots of all predecessors of a block → the source computes it in the block" would have found it mechanically.
* `sites.txt` called the `__asm__("")` a barrier; its real job was a reorg `stop_search_p`, and the missing source fact
  was *where a value is computed*, not a barrier. A `__asm__("")` at a block head whose first insn is also in the delay
  slots of the branches into the block should be classified as "delay-slot" and routed to R24.
* The brief's arity hint was exactly right, in the less common direction: the call passed MORE than the callee's arity
  (m2c reads a live `$a3` as an argument). Worth adding "or more" to the METHOD line.
* Propagation: `if (code == 0x7FFD)` appears in 134 files under `src/` (`grep -rl 'if (code == 0x7FFD)' src/`, e.g.
  `ov_SC03_099.c:524`), plus the shared header above; `hdr_body.c` shows the header closes with the same text. Not every
  hit has been checked to be this exact body.
