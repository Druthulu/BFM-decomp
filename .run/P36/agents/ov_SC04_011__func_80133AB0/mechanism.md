# func_80133AB0 (ov_SC04_011) — mechanism

**Final score 0** (from 24; the mechanical search's best was 17). `mine 137 ins, target 137`, byte-identical
(`--try` MATCH, and the objdump words of the candidate object equal the tree object's word for word).
Harness calibrated first: `body_tree.c` scores 0 through the same `--try`. Text: `PACK/body.c`.
No register pin, no `asm`, no `volatile`, no zero term (the free body's two `+ 0` terms are gone too).

## (a) The residual in one sentence

COUNT, not registers: the lever-free body is **six instructions short** (131 vs 137) because six
register-to-register copies/recomputations that the target keeps were folded away by cse:
`move t0,a1` + `andi v0,t0,0xffff` (X kept whole and re-masked at the `cell` computation),
`move a0,v0` + `andi v0,a0,0xffff` (the same for Y), `move a0,v0` after `andi v0,v1,0x8000` (the flag
bit kept in a second register), and `move v0,s1` before the loop test's `andi` (the counter's old value
copied before the decrement). Every register-pair difference in `residual.txt` is fallout of those six.

## (b) The pass and the decision, `file:line`

All six are one decision in **cse**, fed by one fact of the MIPS port: gcc 2.7.2's `config/mips/mips.h` defines
**no `PROMOTE_MODE`** (the only mention is a comment, `mips.h:2622`), so a `u16` local is a **HImode pseudo**
(`(reg/v:HI n)` in the `.rtl` dump), not an SImode one.

1. **X / Y (4 instructions).** In the free body `Xc = X` is a same-mode SI copy. `make_regs_eqv`
   (`tools/reference/gcc-2.7.2/cse.c:846-857`) makes the longer-lived `Xc` the qty's canonical register, and
   the `(set REG0 REG1)` special case (`cse.c:7440-7474`) rewrites the producing `subu` to set `Xc` directly;
   `(Xc & 0xffff)` in the `cell` expression then canonicalises to the `(and X 65535)` already computed for the
   bounds test (cse follows the fall-through jump, `-O2` sets `flag_cse_follow_jumps`) and is reused: one
   `andi`, no copy. With **`u16 Xc`** the copy is `(set (reg/v:HI 89) (subreg:HI (reg/v:SI 86) 0))` — the
   source is a SUBREG, so the `cse.c:7455` `GET_CODE (SET_SRC) == REG` gate fails and no swap happens — and
   the later use expands as `(zero_extend:SI (reg/v:HI 89))` (`zero_extendhisi2`), a different expression
   from `(and:SI (reg 86) 65535)`, so cse cannot reuse it. The HI pseudo lives across the bounds branch →
   `move t0,a1` survives and a second `andi` is emitted at the use. Exactly the target. (Proved in the
   `.cse` dumps, `scratch/fin.cse:183,316` vs `scratch/free.cse`.)
2. **The flag bit (1 instruction + an operand order).** Free body: `hib = raw & 0x8000; harg = hib;` with
   `int harg` — same qty; `make_regs_eqv` promotes `harg` (it lives past the if/else to the `or`) and
   `cse.c:7440-7474` retargets `andi` into `harg`: the branch then tests `harg` itself, `andi a0,v1,0x8000;
   bnez a0`, no copy, and `or a0,s7,a0`. With **`u16 harg`** the copy is again a SUBREG move
   (`scratch/fin.cse:447-448`), the branch keeps testing `hib` (`andi v0,v1,0x8000; bnez v0`) and the copy
   rides the delay slot (`move a0,v0`); the `ior` now reads `(subreg:SI (reg/v:HI 99))` first, giving the
   target's `or a0,a0,s7`. (Proved: this move alone takes 24 → 20.)
3. **The loop counter (1 instruction).** `expand_increment` (`expr.c:8482`): for a post-decrement it
   queues a single `addsi3` when the mode has an add pattern (`expr.c:8631-8641`, `enqueue_insn`) — `int cnt`
   does, so the test reads `cnt` before the queued decrement: `andi v0,s1,0xffff`. **`u16 cnt`** is HImode and
   MIPS has no `addhi3` (`mips.md:365` defines only `addsi3`), so `icode == CODE_FOR_nothing` and the code
   falls to `expr.c:8645-8647`: `temp = value = copy_to_reg (op0)` — the old value is copied to a fresh
   pseudo, the decrement is widened (`OPTAB_LIB_WIDEN`) and stored back into `cnt`, and the test reads the
   copy (`scratch/fin.cse` insns 183/189/190). cse cannot substitute `cnt` for the copy because `cnt` is
   reassigned in between, and combine cannot fold the copy into the `zero_extend` because its source is
   set between the two insns (`combine.c:914-917`, `use_crosses_set_p`). Result `move v0,s1; andi
   v0,v0,0xffff; bnez; addiu s1,s1,-1` — the target. It also drops the free body's `(cnt-- + 0) & 0xffff`
   zero term: the mask is now the implicit `zero_extendhisi2` of a `u16`.

## (c) The source moves (one line each)

1. `int harg` → `u16 harg` (and `harg = hib + 0` → `harg = hib`) — the flag copy survives (24 → 20).
2. `u32 Xc, Yc` → `u16 Xc, Yc`, and `cell = (Yc & 0xffff) * map->w + (Xc & 0xffff)` → `cell = Yc * map->w + Xc`
   — the X/Y copies and their second `andi` survive (20 → 7).
3. `int cnt` → `u16 cnt`, and `while (((cnt-- + 0) & 0xffff) != 0)` → `while (cnt-- != 0)` — the counter's
   old-value copy survives (7 → **0**). (`u32 cnt; u16 rem; for (;;) { rem = cnt--; if (rem == 0) break; …`
   also scores 0 — the sibling `func_801345F8`'s spelling — but the one-variable form is simpler.)

Every move is a **declaration width**, and each one's width is what the bytes prove: the value is 16-bit
(`lhu` source for `cnt`, `& 0xffff` everywhere for X/Y, `(s16)` at the call for `harg`).
Each alone on `body_free.c` (byte-measured): `u16 Xc, Yc` 24 → **14** (the best single move), `u16 harg`
24 → 20, `u16 cnt` 24 → 22; the three together → 0. Deleting the `& 0xffff` at the `cell` use is
**cosmetic**: `(Yc & 0xffff) * map->w + (Xc & 0xffff)` with `u16 Xc, Yc` also scores 0 (fold of
`zero_extend` & 65535), and dropping the masks with `u32 Xc, Yc` scores 17 — the width is the whole move.

## (d) Generator proposal

**`delever.narrow_copy` (R12-width, targeted):** when the residual is COUNT with the target LONGER by a
`move rA,rB` that sits right after rB's producer (or in the delay slot of the branch that tests rB) and
the value is later consumed through `andi …,0xffff` / `sll/sra 16` / a `(s16)`/`(u16)` cast — or the lever
is `x + zr` / `asm("addu %0,%1,$zero")` feeding a variable used only masked — **re-declare the copy's
destination as `u16`/`s16`** (splitting it out of a comma declarator list if needed; the now-redundant
`& 0xffff` at its uses may stay or go — byte-neutral here): a HImode destination makes the
copy a SUBREG move that `cse.c:7440-7474` cannot fold and makes the later use a `zero_extend` cse cannot
match against the `and`. For a **post-increment/decrement counter** whose test is `move vX,sN; andi vX,vX`
(copy then mask), declare the counter `u16`/`s16`: no `addhi3` on MIPS forces `expr.c:8645` `copy_to_reg`.

Same-TU evidence that this is a family: `func_801345F8` (lines ~2656-2705 of this TU, matched lever-free)
is spelled exactly this way (`u16 uVar6 = c1`, `u16 harg = hi`, `u16 rem = cnt--`), and
`func_80134A74` in the same TU carries the **same four levers** (`uVar6c = uVar6 + zr`, `asm addu uVar2c`,
`hic = hi + zr`, the `m = n; n--` loop with `n` pinned) — it is the next candidate for this exact rewrite
(not attempted here, out of scope). This body is also a shared header,
`src/shared/ov/func_80133AB0__49df14d8.h` (h_exact 49df14d8, included by ov_SC04_021 / ov_SC05_019 /
ov_SC03_126 and more), and the `X = …>> 7) & 0x1ff) - map->ox` shape appears in ~20 `*_jr_8012ACE0.c` TUs.

## (e) What did not work / was not needed

* `while ((rem = cnt--) != 0)` with `u16 rem`, `int cnt` — 13: the copy survives but the `while` loses its
  rotated form (a `beqz` entry guard in place of the `j` to the bottom test). `while ((u16)cnt-- != 0)` — 13,
  the same shape. Only a `u16` counter *itself* (or the sibling's `for(;;){rem=cnt--;if(rem==0)break;`) keeps
  the `j`-to-test loop and gets the copy.
* The mechanical search found `harg` → `u16` (20) and `harg`+`cnt` → `u16` (17), but its trace never names
  `Xc`/`Yc` — yet `u16 Xc, Yc` alone is the best single move on the free body (24 → 14). Hypothesis (NOT
  proven, I did not read the generator): R12 cannot retype one name out of a comma declarator list —
  `Xc, Yc` share `u32 X, Y, cell, Xc, Yc;` with three names that must stay `u32`, while every name the trace
  did retype (`harg`, `cnt`, `ret`) sits alone on its line.

## (f) Where the method fell short

* The method held here: COUNT FIRST (131 vs 137) → six missing copies, all the same shape → one hypothesis
  (the copy destination's mode); the allocation table was never needed. The decisive shortcut was the **same-TU sibling** `func_801345F8`, which is not in
  `neighbours.txt` as a crack (its header is a stale `@stuck:` 26-mismatch note — the function is now matched
  and lever-free) but whose *body* spells the answer: `neighbours.txt` carries only comment headers, and
  here the header was wrong while the code was right. **Recommend: `neighbours.txt` should also list the
  lever-free matched bodies that share a global / a callee / an expression shape with the target** (this one
  shares `D_801EDA40`, the `>> 7 & 0x1ff` shape and the `0x8000`/`0x7fff`·22 dispatch).
* The R12 width generator should split a comma declarator list when it retypes one of its names (see (e));
  that one missing capability is the likely reason a 3-move, all-width close stayed at 17 in the search.

## Paths

* `PACK/body.c` — score 0 text.
* `PACK/mechanism.md` — this file.
* `PACK/scratch/` — `t.sh` (score), `dis.sh` (candidate disassembly), `mkdump.sh` (real-TU cc1 dumps),
  `v/` (candidates), `dumps/dumps_{fin,free}` and the cut `fin.cse` / `free.cse` / `*.rtl`.
