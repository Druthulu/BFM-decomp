# ov_SC04_011:func_801397B0 — T7 agent c21 (re-draw)

**Final: score 0.** 89 of 89 instructions, byte-identical. The official `--try … body.c --body` prints `score 0 … MATCH`.
No pin, no asm, no added volatile, no zero term, no reassignment. There is one `do { } while (0)`, and its job is
proven to be the loop-depth REFERENCE WEIGHT, not a barrier (see (b)). This is the same move as the a4 and c15
precedents in `docs/levers.md` (126 and 128 bodies). About 950 compiles.

The earlier agent's files are kept in `scratch/prev_body.c` and `scratch/prev_mechanism.md` (S102 a3, score 2 ORDER).

`body.c` is `body_free.c` with one change: the eight sprite-field stores from `cx` to `h` (buf+0x10 … buf+0x0A) are
wrapped in a single `do { … } while (0)`. No statement moves and no new variable.

An alternative close is also byte-proven. It needs three edits: the tpage value goes into a temp `tp`, its store moves
below `b1A8 = …`, and `b1A8 = …` alone is wrapped. It is kept in `scratch/body_dw4_alt.c` (= `scratch/diag_dw4.c`),
score 0.

## (a) The residual in one sentence

This is a local-alloc priority inversion between two quantities in block 0, competing for `$4`:

- **chain** Q0 = {r85 `lbu`, r86 `addiu -1`, r74 `off`, r76 `b1A8`}. `combine_regs` ties it (local-alloc.c:1722; the
  death test is at :1855). 10 refs, life 4→48 (44). Priority `floor_log2(10)·10/44` = **6818**.
- **t2** Q2 = {r78 `lh 2(a2)`, r98 `&0x200`, r100 `<<2`}. 7 refs, life 16→36 (20). Priority `2·7/20` = **7000**.

`qty_compare_1` (local-alloc.c:1598) sorts t2 first, and `find_free_reg` (:2158-2175, lowest regno) gives it `$4`,
because `$v0`/`$v1` are held by the hi/lo quantities. The target has these two the other way round.

## (b) The pass, the decision, and why only the reference count can move (file:line; each point says what proved it)

1. **The composition is fixed by the target's registers** (reasoned from the tie rules and checked against every
   dump). The target keeps `lbu/addiu/sll/addu a0,a0,v0/lhu 0(a0)/lhu 2(a0)` in one register, so the chain is one
   quantity. `andi a1,a1,0x200` overwrites t2, so r98 ties into t2 at its death. Any split puts a piece into `$v0`
   first. For example, r98+r100 as their own quantity has priority 20000 and gets `$v0` over [32,36).
2. **The lives are fixed by the target's final ORDER** (reasoned from sched.c and checked on sched1/sched2 dumps of
   ten variants). sched2 keeps sched1's relative order in two cases:
   - equal-priority insns, through the LUID tie-break (sched.c:2428);
   - memory pairs that conflict in sched2. With hard-register addresses `reg_known_value` no longer applies
     (sched.c:419-438), so everything aliases the stack.

   So every insn inside the chain life [lbu … lhu 2(a0)] and the t2 life [lh 2 … or] in sched1 is also inside it in
   the target. I checked every movable candidate:
   - the zero `sw`: `lbu` is QImode, so it always conflicts (sched.c:817/845 clauses need non-QI). If `lh 2` is made
     independent (v6), sched2 puts the `sw` in the lh→andi latency slot, because it is the only ready insn at T-41.
     Score 2.
   - `la D_80190AB8` inside the t2 life: sched2's LUID puts it before the `or`. Seen in w4.
   - T2.y hoisted over the cx store: the `nop` slot gets filled (v8/v9). Score 6.

   Measured with `scratch/qsim.py`, a qty-level simulator of `block_alloc` tying plus `qty_compare`: every variant
   keeps chain len 44 and t2 len 20.
3. **So only `reg_n_refs` is free** (proven on bytes). flow counts it before combine: `flow.c:2067` for sets,
   `:2501` for uses, `+= loop_depth` (`:1401/1403` on LOOP notes). No later pass lowers it. In the close, the two
   `b1A8` loads sit inside a zero-trip loop:
   - `.lreg` for r76 goes from `used 3 times` to `used 5 times`;
   - chain goes from 10 to 12 refs, which gives priority 8181 > 7000;
   - chain is allocated first and gets `$4`, and t2 gets `$5`.

   Chain len 44 and t2 len 20 do not change, so the LOOP-note barrier (sched.c:2058-2074) moved nothing.
   **Negative control:** the same eight statements in a plain `{ }` score 12 (`scratch/ctrl_block.c`).

## (c) The move — one line

- Wrap the eight fixed-field stores (`cx`, `cy`, `b`, `g`, `r`, `y`, `w`, `h`) that read `b1A8` in
  `do { … } while (0)`. The two loads of a chain member are counted at loop_depth 2, and that pushes the chain's
  density past t2's.

## (d) GENERATOR PROPOSAL (one sentence)

> For a REG-caller residual whose instruction ORDER already matches, compute the quantity-level priorities
> (`qsim.py`). If the quantity that must win is short on refs, wrap in `do { } while (0)` every contiguous statement
> range that references ANY member of that quantity and none of the rival's. Include members tied in by
> `combine_regs`, not just the pinned variable. Also include ranges whose insns are contiguous in the target stream.

Two concrete notes for the generator:
- R7's wrap generator is anchored on the lever's variable (`off`, at delever.py:2448). It enumerated 60 ranges over
  `off` and never tried a range over `b1A8`, which is the same quantity after tying.
- My sweep of all 529 contiguous wraps in two statement orders (`scratch/wr_results.txt`) found 22 closes. In the
  unmodified order the only closes are [cx..h] and its supersets up to the `vv` store. A barrier-sensitive range
  scores 2–9, not 12, and that is the signature of a flip plus a stranded insn.

## (e) What did NOT work (byte evidence, all `--try`)

| tried | best | why |
|---|---|---|
| MEM-flag spellings. A struct sprite makes every store IS, so everything conflicts | 12 | same sched1 → same lives |
| `((s16*)b164)[1]` (IS) for T1.y (v6) / both (v5, v10 struct ptr) | 2 | flip via sched1, but `sw` lands in sched2's T-41 slot |
| IS spelling for T2 loads (v8, v9) / T1+T2 (v4) | 6 / 8 | T2.y fills the cx `nop` in both passes |
| cast buf with struct loads (gen matrix) | 31–73 | loads fill every nop (COUNT) |
| 288 spellings: 6 index forms × 6 tpage forms × t2/t0 width × zero-store position (`scratch/g2`) | 12 | refs are invariant under copy and temp spellings, because combine moves references and does not delete them |
| 80 widths s32/s16/u16 for t2, t0, hi, lo | 9 | changes hi/lo quantities and adds extends (COUNT/MIXED) |
| `s16 off`, `short off` | 12 | cse folds the HI copy (k1, k2) |
| `register` on each local; inline tpage helper | 12 | no RTL change |
| t2 reused as the OT pointer (global pseudo) | 11–15 | chain does get `$4`, but b164 then takes `$5`, so t2 must stay local |
| one b164 initializer; `b1A8 = b1A8 + off` forms; a pointer `p` reused for both tables | 9–20 | la not boosted, or a global `p` |
| do-while over the first four statements | 22 | too much weight, and loop/cse changes codegen |

## (f) Where the method fell short

1. **The earlier reading's disjunction was right, but its search was one-sided.** a3 concluded "a fourth reference
   at flow time (a loop note or a combine-deleted insn)". It then enumerated wraps only over `off`. The deciding
   extension is "any member of the tied quantity". `tools/alloc_table.py` prints per-register rows, so it cannot show
   that `b1A8` IS the chain.
2. **alloc_table needs a quantity mode.** `scratch/qsim.py` (about 90 lines) reproduces `block_alloc` tying and
   `qty_compare` from the `.lreg` dump. Its output matched every flip I made (v4, v5, v6, v8, w4, dw4, final).
   Per-register priorities mis-rank this pair: r74 1875 vs r78 3333 in alloc_table, while the real quantities are
   6818 vs 7000.
3. **The METHOD's "one-store ORDER residual" framing points the wrong way here.** The ORDER residual of the score-2
   body cannot be repaired by moving the store (proof in (b)2). The real defect is the refs. A rule: when a flip
   always strands one insn, check first whether the lives are pinned by the target order. If they are, stop moving
   statements and go to refs.
4. **Parallel `--try` on the same function collides.** `.run/P36/engine/score/<fn>/` is shared, so two of my own
   runs clashed (a COMPILE-ERROR that went away on retry). Batch scoring must be serial per function.
