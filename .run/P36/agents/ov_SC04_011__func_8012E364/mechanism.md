# func_8012E364 (src/ov_SC04_011/ov_SC04_011_jr_8012ACE0.c) — T7 agent c22 re-draw

**Final score 4 (ORDER, 67/67). NOT closed.** `PACK/body.c` is still the earlier agent's score-4 body, unchanged. I found
nothing better under the same rules. The earlier agent's files are kept as `scratch/prev_body.c` and
`scratch/prev_mechanism.md`, and its reading of the pass (section (b) there) still holds.

This re-draw contributes two things:
1. A proof, from the scheduler's source and ~63,000 compiles, that the earlier agent's family (the `D_801ED9D8` store
   written after the abs) **cannot** reach 0. Its last 4 are structural, not a missing dial.
2. A deduction from the target's registers about what the original source must have looked like, plus a new family built
   on it (`d` or `v` made block-global, `e2` reusing `a`). That family produces the target's abs arm and `e2 = $a0`, and
   reaches 10 at best (`scratch/best_G_family_k2.c`). The reading of why it stops there is in (d).

## (a) The residual in one sentence

The tail block needs the abs destination `d` ($v0) in a different quantity from its operand `v` ($v1), which selects the
`move` arm of `abssi2` (`mips.md:1526`). At the same time `prev` must be $a1, `e1`/`e2` $a0, flags $v0 and the
`D_801ED9D8` chain $v1, with the `D_801ED9D8` store right after the `addu`, before the flags `ori`/`sh`.

## (b) Passes and decisions (read in `tools/reference/gcc-2.7.2/`)

- The S103 implicit-argument shape (c3/c12) does **not** apply. There is no call of any kind in this function; `abs` is
  the `abssi2` insn. The `$5` pin sits on `prev`, a plain local whose register comes from local-alloc's ordering (below).
  The phantom-reference shape (c20) was checked too. No `reg_n_refs` inflation exists here: combine removes no use.
- **The tie is decided by `combine_regs`, `local-alloc.c:1722`.** When `d` and `v` are both block-local, the only
  refusal left is `local-alloc.c:1854`: no `REG_DEAD` for `v` on the abs, so `v` must be used after it. The other tests
  each fail:
  - `:1765`/`:1774` need `v` or `d` to be non-local.
  - `:1843` needs `d` already born. `d` would need an earlier set in the block that flow does not delete (flow deletes
    dead sets before it counts `reg_n_sets`).
  - Class and mode are `GR_REGS`/SI on both sides.
- **The "use `v` after the abs" route is closed. This is the new proof against the earlier agent's family.**
  - sched1 recomputes death notes after scheduling each block. The later use would have to be the `D_801ED9D8` store X,
    placed after the abs in sched1, and sched2 would then have to hoist X above the abs, the `e2` load and the flags
    `ori`/`sh` to where the target has it.
  - sched1 and sched2 use the same memory-dependence functions (`true/anti/output_dependence`, `sched.c:817-890`).
    `memrefs_conflict_p` (`sched.c:614`) always reports a symbol against a register-based address as a conflict, and the
    `MEM_IN_STRUCT` exemption depends only on MEM flags that both passes share.
  - sched2's register dependences are a superset of sched1's, because pseudos only merge into hard regs.
  - So sched2 can move X only where sched1 could, and the passes differ only in priority. The one sched1-only priority
    term is the birthing boost (`sched.c:2469` `birthing_insn_p`, `:2507` `adjust_priority`, guarded by
    `reload_completed == 0`). It gives the abs `max_priority`, since `d` is set once and live. In a backward list
    schedule the abs is then picked as soon as it is ready and lands after X. That is the opposite of what the route needs.
  - Measured: once X is free of the entity stores (typed-index `MEM_IN_STRUCT` spellings), sched1 hoists it before the
    abs every time, so the tie returns. While X is tied behind them, sched2 cannot hoist it.
- **What this implies about the target.** Both `d` and `v` block-local is impossible, so one of them was block-global in
  the original.
  - If so, `e2` = $a0 cannot come from local-alloc. A local `e2` needs local holders of **both** $v0 and $v1 across its
    life (`d` and `v`). With either one global, local-alloc hands `e2` that free register. So `e2`'s pseudo must be global
    as well.
  - The only $a0 role in other blocks is the `a` temp (the hint value, then the quotient). The original very probably
    reused one temp for hint, quotient and entity pointer.
  - Measured: spelling `e2` as `a` does give `e2 = $a0`.

## (c) Moves tried in the new family (all `--try`, real TU; fast pre-filter `scratch/fast.py`)

| body (scratch/) | what | score |
|---|---|---|
| `c10.c` / `best_G_family_c10.c` | `d = (-diff) / 4; D_801ED9D8 += d;` in the else-if arm (d block-global) + `e2` spelled `a` | 15. Abs arm, `d`, `v`, flags and `e2` all right. **Only `prev` is wrong ($v0 for $a1)**, and arg0/spd/mfhi cascade one register down |
| `k2.c` / `best_G_family_k2.c` | c10 + a named `cur = D_801ED9D8;` + `flags |= 0x10;` + the store order below | **10**. `prev`/`e1` swap $a0/$a1, and the `D_801ED9DC` store comes out after the flags `sh` |
| `r6.c` | `v = D_801ED9D8; … v = v - prev + spd;` (v two deaths → global) + `e2` = `a` | 13. `v`/`prev` swap $a1/$v1 |
| `r1.c` | `v` reused as the last entity pointer (global) + `e2` = `a` | 16-18 |
| `v1.c` | `v` reused for the block-2 `D_801ED9D8` value (the natural global `v`, and $v1 in both blocks in the target) | 26. `v` has two sets, so its block-2 load loses the birthing boost and sched1 hoists it above the division temps (conflicts with $v0/$v1, lands in $a1) |
| `c6.c` | `diff` and `d` merged | 14. The block-2 load schedule breaks the same way |

## (d) Why the new family stops at 10

Take the k-family: `d` global and `e2` = `a`. For the target allocation, local-alloc's `qty_compare`
(`local-alloc.c:1579`, `floor_log2(refs)·refs/(death-birth)`) must give three things at once:
- flags (4 refs) before the chain `{cur, t, v}` (7 refs), which needs `L_chain > 1.75·L_flags`;
- `e1` (3 refs) before `prev` (2 refs), which needs `L_e1 < 1.5·L_prev`;
- the flags `lhu` inside `prev`'s life.

Working through the arithmetic gives one sched1 order that satisfies all three: prev load, `D_801ED9D8` load,
`e1` load, `D_801ED9DC` store, `lhu`, `subu`, `addu`, X, `ori`, `sh`. sched1 cannot produce it:
- The `D_801ED9D8` load is boosted (single-set), and in backward scheduling it becomes ready in the same cycle as the
  `D_801ED9DC` store (`scratch/dumps_k4/fn.sched`, T-14). The boost wins, so the load always lands after the store.
- With the load there, the chain priority is 0.875 against flags' 0.8, so the chain takes $v0.
- Un-boosting the load (a multi-set `cur`/`v`) makes `v` global, and `prev` loses its $v1 holder.

The 1,955-order search (`search9.py`) and its role check (`roles.py`) found no order where all three hold: 34
candidates get `prev` = $a1 and `e1` = $a0, but every one of them has flags and chain swapped.

## (e) Measured negatives (compile counts; fast scorer = the .s text against the tree body's, calibrated 0/2/4/23 on the known bodies)

- Earlier-agent family × `MEM_IN_STRUCT` on each entity access (typed-index spellings) × every legal statement order:
  `search1` (896 compiles), `search2` (29,568), `search2b` (16,128). Best fast 2, which is the earlier agent's body.
- G1 (`v` global by reuse) × orders: `search3` (17,024), `search5` (918), `search10` (1,955). Best fast 8-15.
- k-family: `search6` (296), `search7` (761), `search8` (392), `search9` (1,955). Best official 10.
- Hand-rolled abs in branch form (`d = v; if (v < 0) d = -d;` and 6 other spellings): 28. cse makes the copy's
  destination canonical (`make_regs_eqv`, `cse.c:846-862`), so both the test and the negate read `d` and the copy
  coalesces.
- `d` reused for the final 0x1000 (`g1`/`g2`): the constant propagates and the second set disappears. `d` reused as the
  block-2 counter (`c1`-`c4`): the preference ties it to $v1 anyway.

## (f) GENERATOR PROPOSAL (one sentence)

When the residual is the `abssi2` delay-slot pair (mine `nop`, target `move rD,rS`), first rule out "both locals" as the
earlier agent's last-use move tried, then enumerate block-global reuses: re-spell the abs operand or destination as an
existing local whose other-block role has the same target hard register ($v1 for the operand, $v0 for the destination),
and reuse an `$a0` temp for any pointer whose local allocation loses its holder. Score each with the allocation table
before compiling.

## (g) Where the method fell short

1. `delever_search --try` cannot be driven in bulk, so the searches ran on a private pre-filter (`scratch/fast.py`: cpp
   + cc1 only, .s text against the tree body's, about 0.4 s and parallel-safe). The tool should offer this.
2. There is no simulator for local-alloc on a **given** sched1 order. The priority inequalities in (d) were worked by hand
   from the `.lreg`/`.sched` dumps. A `lalloc_sim.py` that takes a block's insn order and prints qtys, ties and
   registers would turn "which sched1 order do we need" into arithmetic, and "can sched1 produce it" into a dump check.
3. The METHOD's two new shapes (implicit argument, phantom reference) did not apply. The brief's pointer toward the
   `$5` pin as an argument register was a false lead for a call-free function. Packs should say "no calls" up front.
