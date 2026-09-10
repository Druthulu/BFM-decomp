# func_8013D8FC (ov_SC04_011_jr_8013C98C.c): mechanism (T7 agent c2, P36 S103)

**Result: score 0 (MATCH, 45/45 instructions) with no pin, no asm, no volatile, and no invented term.**
`PACK/body.c` is the lever-free, struct-typed `while` loop.

## (a) The residual in one sentence
The lever-free compile has one extra walked pointer: mine keeps THREE loop pointers (`p` in $s1, `psVar2` =
p+10 in $s2, and a new reduced giv = p+8 in $s0). That costs one extra `addiu` per iteration, one extra
callee-saved register ($s4, frame 0x2C to 0x28 for $ra), and the loads come out re-based. The target has two:
`p` ($s1) and ONE reduced giv p+10 ($s0) that every field access is offset from (-6, -4, -2, 0, +2).
This was an instruction-COUNT residual (48 vs 45). It was never a register residual, so I did not use the
allocation table.

## (b) The pass and the decision (loop.c, strength_reduce)
- `-dL` dump of the lever-free text (PROVED, `scratch/d_free/t.i.loop`): `Reg 73: biv verified` and `Reg 72: biv
  verified` give two bivs, psVar3 and psVar2, each `+16`. For biv 73 (psVar2), the four `psVar2[-k]` / `psVar2+1`
  address givs are combined into the giv at insn 62 (`psVar2[-1]` of `buf[2]`, which is p+8) and reduced to a
  new reg 93. Then `Cannot eliminate biv 73: biv used in insn 67`: `psVar2[0]` is a bare `(mem (reg 73))`, which
  is not a giv, so it keeps the biv alive beside the reduced giv. The result is three pointers.
- `-dL` dump of the match (PROVED, `scratch/d_d/t.i.loop`): there is one biv (reg 72). Its six address givs
  (insns 37/44/49/54/59) are all `combined with giv at 64`, the `p->h` load at p+10, and that giv is reduced to
  reg 94.
- Why p+10 is the combine target: `record_giv` PREPENDS each new giv (`loop.c:4421-4422`,
  `v->next_iv = bl->giv; bl->giv = v;`), and `combine_givs` (`loop.c:5494`) walks `g1` from the list head. The
  first `g1` that can absorb the others wins (`combine_givs_p` `loop.c:5458`, via `express_from` plus
  `memory_address_p`). So **the last address giv in insn order becomes the reduced register**. The target's
  last field read is `h` (p+10), which only holds if `data + w` is computed BEFORE the four `buf` stores.
  PROVED on bytes: with the call argument written inline after the stores (`scratch/e.c`), the score is 19.
  `scratch/a.c` (same order, cmd re-read) scored 34 and reduced p+12 instead.
- The tree's `$16` pin works for a different reason: a hard register is never a biv candidate (strength_reduce
  works on pseudos), so psVar2 kept every access relative to itself. That is consistent with the bytes, but I
  did not read the exclusion line, so it is NOT PROVED from source.
- The project map already has this: `.run/P36/engine/residual_moves.md` row 142 (L1, "Two walked pointers vs
  one base + offsets"). This body is a byte-proven instance of it.

## (c) The source move(s) that closed it
1. Collapse the second walked pointer into offsets from the first. `psVar2 = psVar3 + 5; ... psVar2 += 8` goes
   away, and every `psVar2[i]` becomes `psVar3[i+5]`. On the first try this alone scored 0 (`scratch/b.c`,
   which keeps the Ghidra c9/cff shape).
2. For readability, and still 0: type the pointer as the TU's existing `Cmd_8013D53C` record (the one its sibling
   `func_8013D53C` walks). Drop the hoisted-constant locals `c9`/`cff`, since loop.c hoists 9/0xff into $s3/$s2
   by itself. Write the loop as a plain `while (p->cmd != 0xff)` (`scratch/c.c`: do-while with cmd local = 0;
   `scratch/d.c` = `body.c`: while = 0). Compute `data = p->data + p->w` before the four `buf` stores (this order
   is load-bearing, see (b)).

## (d) Generator proposal
When a lever-free loop body walks two pointers by the same stride, and one is initialised as `q = p + k` (the
residual is COUNT, +1 `addiu` in the loop, +1 callee-saved, and the tree's lever is a pin on `q`), delete `q` and
rewrite every `q[i]` / `q + i` as `p[i + k]` / `p + i + k`. As a second step, if the reduced giv lands on the
wrong field, hoist the statement whose address should be the reduced register so it is textually LAST among the
address uses (combine_givs picks the last-recorded giv).

## (e) What did not work
- `scratch/a.c`: struct pointer with buf stores before `data + w`, and cmd re-read at the top. Score 34: the
  reduced giv is p+12, and the loop test reloads `cmd` (lhu + nop) instead of carrying it.
- `scratch/e.c`: `body.c` with `p->data + p->w` inline in the call, i.e. after the stores. Score 19 (48 ins).
- The mechanical search (history.txt, about 3,500 compiles, best 17) never had this move. Its R-moves swap
  statements, change widths and inline constants. None of them merges two bivs, so it could not reach a count
  residual that is a whole extra induction variable.

## (f) Where the method fell short / what helped
- Dumping the whole function (METHOD step 1) settled it at once. The lever-free asm shows three `addu $N,$17,…`
  pointer inits and two `addu …,16` increments in the loop. The hunk view scatters those across delay slots.
- COUNT FIRST (step 2) was right: this is an extra induction variable, not a register choice, so the
  allocation table would have been the wrong instrument.
- neighbours.txt had nothing for this function. What helped was reading the sibling `func_8013D53C` in the TU:
  it walks the same `D_801EDABC` list as a `Cmd_8013D53C *` with `while (cmd != 0xFF) { if (cmd == 9) … arg0++; }`.
  That suggested the single-pointer shape and the struct type. **Suggestion for the pack builder:** also list the
  bodies of TU functions that touch the same global (the PROMPT's grep step), not only the comment headers.
- `-dL` is not in the brief's dump flag list (`-dl -dg -dS -dc -dj -df`). For any COUNT residual inside a loop,
  add `-dL`: the `.loop` dump's `biv verified` / `combined with` / `reduced to` / `Cannot eliminate biv` lines
  named the defect exactly.

## Files
- `body.c`: the final body (score 0).
- `scratch/b.c`: minimal-diff close (Ghidra shape, c9/cff kept, one pointer), score 0.
- `scratch/c.c`: struct + do-while, score 0. `scratch/d.c` = body.c.
- `scratch/a.c` (34), `scratch/e.c` (19): negative controls for the giv-order claim.
- `scratch/cc.sh`: splices a body into tu_free.c and compiles it with dumps into `scratch/d_<tag>/`.
  `d_free/` and `d_d/` hold the `.loop` dumps quoted above.
