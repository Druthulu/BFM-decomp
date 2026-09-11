# func_8018C14C (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e30)

**Result: NOT closed in plain C. The best lever-free score is 9**, and `body.c` = `body_free.c` (every plain-C spelling of
about 4,300 enumerated floors at 9). **The minimum-lever body scores 0 with levers 2 → 1 + one marked do-while**
(`body_minlever.c`): the `$0` pin on `ent` stays, and the `__asm__ volatile("")` barrier is replaced by a marked
`do { … } while (0)`. Signature unchanged.

## (a) The residual in one sentence
Same count (69/69). In the target the parameter copy for the final call, `move a0,s0`, sits between the 0x6 store (still
through `$s0`) and the 0xC4 load (already through `$a0`). In mine the copy lands before the 0x6 store, so the 0x6 store goes
through `$a0` and the 0xC4 load (scheduled first) through `$s0`.

## (b) The passes and the decisions (read on the `.cse`/`.cse2`/`.sched`/`.lreg` dumps, proven on bytes)
1. **The stores use `$a0` because of `optimize_reg_copy_1`** (`local-alloc.c:700-800`, called from `update_equiv_regs`,
   `local-alloc.c:1003-1007`). The call-argument copy `(set (reg a0) (reg 72))` (insn 153) does not kill r72, so every
   later use of r72 up to its death is rewritten to `$a0`. Which insns become `$a0`-relative is decided by sched1's
   placement of insn 153.
2. **sched1 places 153 too early, and no statement order fixes that.** 153 has priority 7 (its only link is the anti
   dependence on the `RotTransSV` call) and the highest LUID in the block, so in the backward list scheduler it is picked
   as soon as the ready list tops out at 7 (`rank_for_schedule`, `sched.c:2385-2429`). The 0x6 store (88) has priority 8
   (the `lhu 16(sp)` latency) and outranks 153 whenever both are ready, so 153 ends up above 88 (`.sched` trace:
   T-23 picks 88, T-24 picks 153). The 0xC4 load (100, priority 7, not birthing because `t1` is set twice) loses the
   LUID tie to 153, so it lands above the copy. The target needs `88 < 153 < 100`. That order requires 153 to beat 88
   and lose to 100. I found no source spelling that does this inside one scheduling region. This is an argument from the
   trace plus about 2,600 enumerated bodies (`e1/`, `e2/`), not an exhaustive proof: making the 0xC4 load birthing
   (`t1` set once, `e2/T1_*`, `T4_*`) moves it but still floors at 9. A sched region split
   (asm barrier or LOOP notes) cannot place 153 early either, because the copy is always emitted at the call, so it
   lands in the LAST region (`scratch/e3/free_05_05.c`: 4, the copy after the barrier).
3. **The tree's `$0` pin makes `ent` a second pseudo.** `ent = a0 + zr` is not a copy, so cse and cse2 keep it, and it is
   allocated to `$a0` from the call-argument preference. It is defined right after the 0x6 store, and every later access
   goes through it. A plain `ent = a0;` copy survives cse1 only when a LOOP_END note ends the cse block
   (`cse_end_of_basic_block`, `cse.c:8039-8060`, after which `make_regs_eqv`, `cse.c:846-862`, makes `ent` canonical).
   cse2 runs with `after_loop` and ignores the note, so it merges `ent` back into r72 (`.cse2` of
   `scratch/dw/dw_b.c`: reg 75 has 14 references in `.loop` and 1 in `.cse2`, 0 in `.flow`).
4. **The barrier (asm or do-while) fixes the `li 1`/`ori` order.** With the pin and no barrier (`scratch/e4/pinonly.c`,
   and 588 statement orders in `scratch/e5/`), the floor is 7 (ORDER: the `ori` rises above `sh 10`). LOOP notes are a
   full sched barrier (`sched.c:2058-2074`: the next insn depends on every earlier reg and memory reference), so a
   do-while ending after the 0xC4 load reproduces the tree's region split `[lhu16, sh6, ent] | [lhu18, lw C4, sh10] |
   [li1, ori, lhu20, …]` (`.lreg` of `scratch/d_minlever/`).

## (c) The minimum-lever body (`body_minlever.c`, score 0)
```c
        register s32 zr __asm__("$0");  // !FAKE: pin $0 ent — …
        s32 ent = (s32)a0 + zr;
        …
        do {  // !FAKE: do-while — LOOP notes split sched1 (sched.c:2058-2074) …
            *(s16 *)(ent + 0xA) = v[1];
            t1 = *(u32 *)(ent + 0xC4);
        } while (0);
        one = 1;
        t1 |= 2;
        …
```
Levers before → after: 2 (the `$0` pin and one `__asm__ volatile("")`) → 1 (the pin) plus one marked do-while. Four
do-while placements score 0 (`scratch/e4/dw_00_02`, `dw_02_02` (an empty `do {} while (0);` at the old barrier line),
`dw_02_05`, `dw_02_06`). Without the pin, every do-while placement floors at 4 (`scratch/e3/`, 153 placements).

## (d) Generator proposal
When an `asm volatile("")` barrier lever is judged NEEDED, try an empty or one-statement `do { … } while (0)` (marked) at
the barrier's line and at each neighbouring statement boundary. Its LOOP notes are the same sched1 barrier
(`sched.c:2058-2074`), and it turns an `asm` lever into an allowed, marked construct. For the family "call-argument copy
between two uses of the parameter": no plain-C move exists (see (b)2). It needs a second pseudo, which is a pin today or,
in the structs phase, possibly a real second variable with a different provenance.

## (e) What did NOT work (byte evidence, `scratch/`)
- 1,260 orders of the load/ori/`v[2]`/`one` statements (`e1/`), and 1,344 more across `t1` set once or twice, a separate
  `t2`, `one` as a variable or literal, `v2` as `s32`/`u16`/direct (`e2/`): all ≥ 9.
- The natural in-order spelling (the 0x6/0xA/0xE stores together, `|= 2` in place, as the sibling `func_8018BD18`
  writes them) (`c2/a.c`): 20. It shows the 0xE store is last only because of its high sched priority. It does not
  close.
- Pin-free do-while placements (`e3/`): best 4. `ent = a0` inside or before a do-while (`dw/`): 7. cse2 re-merges `ent`.
- The pin alone, 588 orders (`e5/`): 7.

## (f) Where the method fell short
- The first 2,600 enumerated bodies were spent before I read the `.sched` ready-list trace closely enough to see that
  the copy's LUID tie makes the target order unreachable. Reading the trace first ("which insn wins each tie, and can a
  source change alter priority, class or LUID for it?") would have skipped most of them. The deciding facts were
  `rank_for_schedule`'s LUID tie-break plus the copy being emitted at the call.
- METHOD has no entry for `optimize_reg_copy_1` rewriting later uses to the argument register, which is the
  mechanism behind "the stores after the copy use `$aN`". It belongs next to S103 c11.

## (g) Structs question
Plausibly yes, and it is the only way I can see to drop the pin. The pin exists to make `ent` a second pointer that cse
cannot fold into the parameter. If the original accessed the tail fields through a different typed pointer to the
same object (for example a `struct Actor *` cast of `a0` passed to an inlined initialiser, or a sub-struct pointer such as
`&a0->coll`), the pointer might not be a plain copy of the parameter, and sched1's memory disambiguation would see two
bases. This is speculation: whether cse folds such a pointer back into the parameter was not checked. Candidate struct: the actor with
`+0x06/0x0A/0x0E` s16 position, `+0x58` anim pointer, `+0x5C` s16, `+0x75` u8, `+0xAE` s16, `+0xB4` s32, `+0xBC`
callback pointer, `+0xC0/0xC1` u8 flags, `+0xC4` u32 flags. A struct type alone on the same pointer would not help: the
defect is which pseudo holds the base (the `optimize_reg_copy_1` rewrite), not `MEM_IN_STRUCT_P`. Not tested.

Files: `body.c` (= `body_free.c`, score 9, the best lever-free text), `body_minlever.c` (score 0, 1 pin + 1 marked do-while),
`scratch/e1`-`e5/` (enumerations with `scores.txt`), `scratch/dw/`, `scratch/c1`, `c2/`, dumps in `scratch/d_*/`,
helpers `scratch/{try.sh,ptry.sh,dump.sh,splice.py,gen*.py}`.
