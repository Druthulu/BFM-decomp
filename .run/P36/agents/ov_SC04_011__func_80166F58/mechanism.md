# func_80166F58 (ov_SC04_011 / src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c) — T7 residue

**Status: NOT CLOSED. Best score 4 (COUNT; mine 67 ins, target 69).** Start was 4; the mechanical
search (g3/g4s/g5/s1/s2/s4/s7, 2,625 compiles) never moved it. This session added ~300 more compiles
of hand-reasoned spellings and found the *shape* (a 69-instruction candidate, score 21) but not the
bytes.

## (a) The residual in one sentence

The target sign-extends each of the two `short`-valued arguments **into its own arrival register and
then copies that register to the callee-saved one** (`sll a1,a1,16 ; sra a1,a1,16 ; move s4,a1`),
while every lever-free spelling I could reach folds the extension straight into the callee-saved
register (`sll a1,a1,16 ; sra s4,a1,16`) — two instructions short, twice.

```
target                     mine
sll  a1,a1,0x10            sll  a1,a1,0x10
sra  a1,a1,0x10            sra  s4,a1,0x10     <- one insn does both
move s4,a1
sll  a2,a2,0x10            sll  a2,a2,0x10
sra  a2,a2,0x10            sra  s1,a2,0x10
move s1,a2
```

## (b) The pass and the decision, read from the compiler's own source

The missing instruction is a **reg-reg copy that `combine` deletes**, and the reason it can always be
deleted is a **`cse` canonicalisation** that removes the only thing that could have kept it.

**Step 1 - expand produces three insns** for `t = (short)param_2; p2 = t;`

```
(insn 25 (set (reg 83)      (ashift:SI   (reg 5 a1) (const_int 16))))
(insn 26 (set (reg/v:SI 76) (ashiftrt:SI (reg 83)   (const_int 16))))   ; t
(insn 29 (set (reg/v:SI 77) (reg/v:SI 76)))                             ; p2 = t
```

**Step 2 - `combine.c:try_combine` takes i2 = insn 26, i3 = insn 29**, substitutes and deletes i2.
`can_combine_p` (`tools/reference/gcc-2.7.2/combine.c:900-960`) is satisfied because i2's destination
is a pseudo carrying a `REG_DEAD` note at i3 - **its only use is the copy**. Proven on RTL: with `-dc`
on the real spliced TU, insn 29 is a `NOTE_INSN_DELETED` in `t.i.combine` while insn 26 survives
carrying `(expr_list:REG_DEAD (reg:SI 83) ...)`. The copy is gone long before register allocation, so
no declaration order, statement order or block wrap - everything rungs g3-g5 and s1-s7 generate - can
bring it back. That is why 2,625 mechanical compiles all sat at 4.

**Step 3 - the obvious defence, a second use, is taken away by `cse`.** Give the extended value a
second use *after* the copy and combine should be blocked (no `REG_DEAD` at i3). It is not, because
`cse.c:canon_reg` rewrites that later use onto the **copy's destination**: `p2 = param_2` puts both
registers in one quantity and the subsequent `eq = (param_2 == param_3)` is emitted reading `p2`, not
`param_2`. Proven on the emitted registers, not inferred - for

```c
param_2 = ((short)param_2); param_3 = ((short)param_3);
p2 = param_2; p3 = param_3; eq = (param_2 == param_3);
```

cc1 emits `sll $5,$5,16 ; sll $6,$6,16 ; sra $20,$5,16 ; sra $17,$6,16 ; xor $2,$20,$17` - the `xor`
reads `$20/$17`, the copies' destinations, so the parameter is back to one use and combine merges. 67
instructions.

**Step 4 - and that gives the one spelling that works.** Put the second use *before* the copy, where
`cse` has no copy to canonicalise onto:

```c
param_2 = ((short)param_2);
param_3 = ((short)param_3);
eq = (param_2 == param_3);   /* the second use - must come BEFORE the copies */
p2 = param_2;
p3 = param_3;
```

cc1 now emits `sll $5,$5,16 ; sra $5,$5,16 ; sll $6,$6,16 ; sra $6,$6,16 ; xor $2,$5,$6 ;
move $20,$5 ; move $19,$6` - **the target's in-place extension and both copies, at the target's
instruction count of 69.** It still scores 21, because the `xor` sits *before* the copies and reads
`a1,a2` where the target's sits *after* them and reads `s4,s1`, and that one-instruction difference in
where the two long-lived values are born rotates the callee-saved seats by one
(`s1->s2, s2->s3, s3->s1`, ten instructions).

**The trap is closed on both sides, and the sweep measures it exactly.** Over the 40-candidate
statement-order x `eq`-operand sweep (`PACK/v/sweep.py`): every ordering with the second use after
*both* copies measured **67** instructions (score 4-11); every ordering with it between them measured
**68** (one copy survives, score 16-24); only the four orderings with it before both measured **69**
(score 21-24). A further 240-candidate sweep over all declaration orders and both initialiser orders
(`PACK/v/sweep2.py`) moved the 69-instruction score not at all - every one of the 480 results is 21.
The second use and the register the `xor` reads are the same knob, and they want opposite settings.

## (c) The move(s) that got closest

- `param_2 = ((short)param_2);` / `param_3 = ((short)param_3);` — the extension written back into the
  parameter instead of into the destination local (blocks nothing on its own).
- `eq = (param_2 == param_3);` placed **before** `p2 = param_2; p3 = param_3;` — the second use that
  denies `can_combine_p` its `REG_DEAD` note. Score 21 at the correct 69 instructions.

Best *score* remains the untouched lever-free text (4). `PACK/body.c` holds that text (the score-4
body, with the stale `// !FAKE:` comment on the `p3` line dropped); the 69-instruction candidate is
`PACK/v/h12.c`.

## (d) GENERATOR PROPOSAL

**R19 "second use before the copy"** — when the residual is COUNT and the missing instructions are a
reg-reg `move Sx,aN` paired with a target `sra aN,aN,K` that mine emits as `sra Sx,aN,K` (an extension
folded into its consumer), rewrite the statement `V = (T)param_N;` as `param_N = (T)param_N;` and
insert/relocate the *first* later statement that reads `V` to read `param_N` and to sit **before**
`V = param_N;` — one candidate per such statement, ranked by whether the instruction count reaches the
target's.

This is new against the four docstrings I read in `tools/delever.py`: `sink_merges` (R15) sinks a
statement to its use, `constant_holders` (R16) parks a literal in a named local, `constant_run_splits`
(R17) splits a run of constant stores, `bystander_moves` (R18) walks an unrelated statement past its
neighbours. All four move *whole statements*; none of them changes which variable an assignment writes
to, and none of them targets `combine`'s `REG_DEAD` precondition — R19 is a use-count move, not a
placement move.

## (e) What did NOT work, with the byte evidence

1. **`short param_2, short param_3` in a prototype-style definition (generator R14).**
   Two independent reasons, both measured:
   - *Unbankable here.* This TU declares the function twice at file scope **after** the definition —
     `src/ov_SC04_011/ov_SC04_011_jr_8015C32C.c:5568` and `:5597`,
     `extern s32 func_80166F58(s32, s32, s32, s32);`. Narrowing a parameter in the definition gives
     `conflicting types for 'func_80166F58'` (cc1 hard error, reproduced on the spliced TU:
     `...:5563: conflicting types` / `:5117: previous declaration`). A body-only bank cannot touch
     lines 5568/5597, so a width-based spelling is out of scope by construction, exactly as the brief
     warned.
   - *And it would not have worked anyway.* Compiling that definition regardless (cc1 emits the
     function before it reaches the conflicting declaration) gives
     `sll $5,$5,16 ; sra $20,$5,16` — **the same 67-instruction merged form**, not the target's
     three insns. So on this body the R14 mechanism is refuted on bytes, not merely unbankable.
2. **Old-style (K&R) definition with `short param_2; short param_3;`** — legal here (default argument
   promotion makes it compatible with the later `(s32,s32,s32,s32)` prototypes, and it compiles
   clean), and it does take `assign_parms`' `did_conversion` path
   (`tools/reference/gcc-2.7.2/function.c:3644-3675`). **Score 4, unchanged.** The `-dr` dump shows
   why: MIPS in gcc 2.7.2 **does not define `PROMOTE_MODE`** (only `PROMOTE_PROTOTYPES`,
   `config/mips/mips.h:1153`), so the parameter pseudo is created in `HImode`
   (`(set (reg/v:HI 73) (subreg:HI (reg:SI 74) 0))`) and the conversion at entry is a free truncation;
   the sign extension still happens at the *use*, with the consumer as its destination. The brief's
   claim that a `short` parameter is "sign-extended IN PLACE (`sra a1,a1,16`) before any copy" does
   not hold for this compiler configuration.
3. **`param_2 = (short)param_2; p2 = param_2;`** (extension written into the parameter, single use)
   — score 4. `cse` leaves it, `combine` merges it.
4. **`short t2; t2 = param_2; p2 = t2;`** (a narrow local as the intermediate) — score 4, both
   orderings. Same reason: HImode local, extension at the use.
5. **`p2 = ((param_2 << 16) >> 16);`** and **`int p2 = ((short)param_2);`** (declaration with
   initialiser) — score 4 each.
6. **Removing `eq` and writing `p2 != p3` inside the loop condition** (the hypothesis that `eq` is
   gcc's own loop-invariant hoist) — **refuted: 63 instructions, score 30.** gcc does not hoist it; it
   branches in the loop. The explicit `eq` local is load-bearing.
7. **`eq` computed from the parameters *after* the copies** (`A B C D E`) — 67 instructions, score 6;
   **between the two copies** (`A B C E D`) — 68 instructions, score 17, exactly one copy surviving.
   The full 40-candidate order x operand sweep is `PACK/v/sweep.py`, the 240-candidate declaration
   order sweep `PACK/v/sweep2.py`.
8. **Searching the whole tree for a lever-free precedent.** I disassembled all 4,284 objects under
   `build/src` looking for `sra aN,aN,0x10` followed within three instructions by `move sX,aN`
   (`PACK/v/../scan` logic, run from the scratchpad). **Exactly one function in the entire binary has
   this shape: func_80166F58 itself** (found in `build/src/ov_SC03_099/ov_SC03_099_jr_8015C32C.o`, a
   levered twin). There is no banked exemplar to copy from — which is consistent with 125 copies of
   this one body being the whole population.

9. **Loop-invariant placements** (the hypothesis that `loop.c:move_movables` hoists a copy out and
   leaves one behind, `tools/reference/gcc-2.7.2/loop.c:1673-1702`): the two extensions inside the
   loop (64 ins, score 33), `eq` inside the loop (67, score 4), the two copies inside the loop
   (67, score 18), the copies inside with `eq` outside (67, score 18). gcc hoists them and `combine`
   merges them in the preheader exactly as before. Refuted.
10. **The second use placed across a basic-block boundary** (`param_2` read once inside the loop so
   `cse` cannot canonicalise it onto `p2`) — 67 instructions, score 23. `cse`'s extended basic block
   reaches into the loop head and folds it anyway.
11. **`register int p2` / initialiser-form declarations / `unsigned` destinations / reordered
   declarations** — no effect on the score at all (480 results, all 21 or all 4 within their shape).

## (f) Where the method fell short

- **The brief's history was wrong on the mechanism and it cost the first third of the session.** R14
  was presented as established for *this* function; it is refuted on bytes here (see e.1/e.2), and the
  `PROMOTE_MODE` premise it rests on is not true of gcc 2.7.2/MIPS. Checking the premise against
  `config/mips/mips.h` takes one grep and should be step 0 of any width-based hypothesis.
- **The residual print hides the shared prefix.** The diff showed only the two `sra` lines, so the
  `sll` that precedes each of them (and is *also* in-place in both streams) had to be recovered by
  hand from `objdump` before the shape was readable. A residual that printed the matching neighbours
  would have named "extension folded into its consumer" immediately.
- **`--try` reports only the first line usefully; a `COMPILE-ERROR` is truncated to 300 characters of
  *warnings*.** The real diagnostic (`conflicting types`) was 120 lines further down and had to be
  reproduced by hand with `mipsel-linux-gnu-cpp -Isrc/ov_SC04_011 | cc1`. Surfacing the last error
  line rather than the first 300 characters would have made finding e.1 instant.
- **`--try` and the search share one scratch directory per pack**, so a sweep script and an
  interactive `--try` cannot run concurrently. A per-invocation scratch would let an agent explore
  while a sweep runs.
- **The score is not monotone in structure.** The candidate with the *right instruction count* scores
  21 while the one with two missing instructions scores 4, so a hill-climb on this score can never
  reach the answer from the start point — it has to cross a scoring valley. A secondary key
  (|count difference|, then edit distance) would have let the mechanical search find `h12` itself.
