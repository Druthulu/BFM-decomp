# func_80135004 (src/ov_SC04_011/ov_SC04_011_jr_8012ACE0.c): T7 agent c8, S103

**Result: score 0 (89/89 instructions). No pin, no asm, no added volatile, no invented term.** Checked by `--try` twice.
The disassembly of the whole scratch object (every function, words and relocations) is identical to the tree object's,
by `diff` of `objdump -drz` with the file-name line skipped. The coordinator still has to run the whole-object gate.

Two joint moves on `body_free.c`:
1. **Split the reused temps per group.** `u16 a, b;` reused across the x/y/z groups becomes `u16 ax, bx, ay, by, az, bz;`.
2. **Pass `D_801EDA30` straight to the call.** The `d94` local is dropped and the call is written
   `func_80134A74(id, a1v, a2v, D_801EDA30)`, the same spelling the body's second call already used.

Each move alone: the split scores 26 (the block-scoped form in `scratch/vC.c`), the inline scores 16 (`scratch/ab3.c`),
from a start of 26. Together they score 0.
An equivalent form that keeps `d94` also scores 0 (`scratch/m1.c`): write `d94 = D_801EDA30;` AFTER `D_801EDA40 = 0;`.
That form proves the mechanism of move 2 (see (b)).

## (a) The residual in one sentence
The start was one instruction long (90 vs 89) and had the pointer locals permuted: target pb0=t1, pac=a2, pb8=t0,
b=v1, with d94 in a3. The start had pb0=v1, pb8=a3, b=t0. The extra instruction was a load-delay `nop` in group 3 that
the target fills with `andi s1,a0,0xffff`, and the target also hoists the `D_801909C0` load above the RTL prologue.

## (b) The passes and decisions (read in source; each proven on dumps in `scratch/d_*` and on bytes)
1. **Temps reused across groups go to global allocation.** `local-alloc.c:472` admits a pseudo only when
   `reg_n_deaths == 1`. The shared `a`/`b` die 3 times, so they appear in the `.greg` order line (`80 79 …`) and are
   placed after every local pointer. pb0 then took v1 before b could. Split per group, each temp dies once and becomes
   a high-priority local qty (7500/5000), so v0/v1 go to the temps first. The same finding is agent c1's, on sibling
   func_80135168.
2. **Where the `D_801EDA30` load lands decides a3.** With `d94 = D_801EDA30;` written before `D_801EDA40 = 0;`, the load
   is `(set r82 (mem D_801EDA30))` and the call gets a separate copy `(set a3 r82)`. Combine cannot fold the load into
   the copy: `can_combine_p` (`combine.c:914-917`) calls `use_crosses_set_p`, and that returns 1 for a MEM source when
   a memory store lies between (`combine.c:10134`, `mem_last_set > from_cuid`). The store to `D_801EDA40` sits between
   them. The pseudo load then floats late in sched1, pb0's window leaves a3 free, and local-alloc gives pb0 a3 (score 5
   in `scratch/vD.c`).
   With the global passed straight to the call, `calls.c:1626` expands it to a MEM, and because
   `preserve_subexpressions_p` is false outside a loop and MIPS has no SMALL_REGISTER_CLASSES, it is not copied into a
   pseudo (`calls.c:1652-1664`). `calls.c:1881` then emits one insn, `(set (reg:SI 7 a3) (mem D_801EDA30))`. Moving the
   `d94` assignment after the store gives the same insn through combine, because no store is in between any more
   (`scratch/d_m1/t.i.combine` insn 96, and in `d_vC` the two insns 79/95 stay apart).
3. **sched1 places that hard-reg load at the start of its window.** The a3 load's only hard dependences are true deps on
   the three `[0]` stores, which are non-`/s` MEMs. The `/s` stores at offsets 2 and 4 do not conflict with a fixed
   non-struct load (`sched.c:817-841`). In the backward list schedule the load keeps getting "blocked" on the memory
   unit after every other load, so it is placed last in backward order, which is right after the `pb8[0]` store (sched1
   index 12; trace in `scratch/d_ab1/t.i.sched`). The ALU-only `id` zero-extend and the a0 argument copy fill the hazard
   slot at T-7 instead, which pulls them out of group 3.
4. **local-alloc (`qty_compare_1`, `local-alloc.c:1598`; `find_free_reg`, `:2073`).** Hard a3 is now live from index 12
   to the call, so it is busy through the windows of both pb0 and pb8. Group 3's pb0-store→pb8-store gap shrank from 6
   insns to 4 (id and the a0 copy left it), so pb8's length is 32 against pb0's 34. The priorities
   (`scratch/../../ov_SC04_011__func_80135168/scratch/lpri.py` on `d_ab1`) are pac 12/48 = 2500, pb8 8/32 = 2500 and
   pb0 8/34 = 2352. pac and pb8 tie, and pac wins the tie on its lower qty number. So pac takes a2 (the incoming p2 is
   dead after `move s0,a2`), pb8 takes t0 (a3 is busy), and pb0 takes t1. That is the target. The prologue hoist of
   `lw t1` and the `andi` filling the group-3 delay slot then come out of sched2 without further changes.

## (c) The moves that closed it
- `u16 a, b;` → `u16 ax, bx, ay, by, az, bz;`, one pair per x/y/z statement group. Per-group block-scoped
  `{ u16 a, b; … }` also works (`scratch/w1.c`).
- `d94 = D_801EDA30; … func_80134A74(id, a1v, a2v, d94)` → `func_80134A74(id, a1v, a2v, D_801EDA30)`. The alternative
  is to keep `d94` but assign it after `D_801EDA40 = 0;` (`scratch/m1.c`).
- **Not needed here:** c1's `((H16 *)&D_801EDA40)->h = 0;` member-store move. With the two moves above, the plain store
  scores 0 (`scratch/ab1.c`), and with the store move plus the split but d94 left in place the score is 5.

## (d) Generator proposal
When a call argument is a plain global (or any MEM) that the body first loads into a local, and a memory store sits
between that load and the call, try passing the global directly in the call, or moving the local's assignment below
the last store. The argument then becomes a single `(set (reg argN) (mem))` insn (`calls.c:1881`, or combine once
`combine.c:10134` no longer refuses). That insn blocks argN through the preceding stores and reshuffles local-alloc for
every pointer live there. Score it jointly with the per-group temp split (R-split) whenever the residual is a pointer
permutation that involves an argument register.

## (e) What did not work (byte evidence, `scratch/*.c`)
- `vA`: hoisting `d94 = D_801EDA30;` to the top of the unsplit body scores 24.
- `vB`/`vB2`: dropping the a/b temps and re-reading `p2[i]`/`p1[i]` scores 39/41 and adds 10 instructions (the stores
  may alias the params, so the loads are repeated).
- `vC2`/`vD2`: the split plus d94 at the top scores 16. a3 is blocked from index 5, but that puts the d94 load into
  group 1's pb0→pb8 gap, pb0 and pb8 tie on length 34, and pb0 wins the tie: t0/t1 are swapped, and there is an extra
  `nop`.
- `battery.py` (42 compiles): moving `id = …` to every slot changes nothing. Moving `d94 = …` gives only two outcomes:
  before the `[0]` stores gives 16 (the swap), anywhere after them gives 5 (pb0 = a3), because sched1 re-floats the
  pseudo load late.
- `u_*.c`: an `arg0` param of type `u16` changes nothing (16/5/16).
- `w2.c`: also inlining `pac[0]`/`pac[2]` into the call scores 4 (ORDER).

## (f) Where the method fell short
- The coordinator's relay of c1's result (the temp split) was worth a lot: it took me from 26 to 16 or 5 at once. The
  local-qty priority script (c1's `lpri.py`) is what exposed the pb0/pb8 tie at 34/34. alloc_table's global-formula
  priority (5000/4444) would not have shown it. The engine needs a local-alloc priority column.
- The count gap (90 vs 89) was NOT a missing-instruction defect. It was a scheduling consequence of the register
  permutation (a3 held by pb8 kept the d94 load out of the delay slot). "Count first" still helps, but a ±1 count gap
  next to a register permutation should be read as schedule, not as cse.
- The battery over statement slots showed that source position is not what decides here, because sched1 re-floats a
  pseudo load. What decides is whether the argument reaches the call as a pseudo copy or as a direct hard-reg load.
  The mechanical search has no move for "inline a local into its single call-argument use" or for "move a load below a
  store". That is a new move family (see (d)).
