# func_80135EB0 (src/ov_SC04_011/ov_SC04_011_jr_80135D20.c): T7 agent c15, S103

**Final score 0** (from 64 COUNT, 276 vs 289; the mechanical search's best was 52): `PACK/body.c`, 289 = 289 ins. Its
`objdump -drz` (words and relocations) is identical to the tree object's, which I dumped before the tree's `build/`
was cleaned mid-run (`scratch/target.dis`, compared with `scratch/last.dis`). The `.rodata` jump table (11 entries,
0x18..0x40) is also identical. It scored 0 on repeated `--try` runs. It has no pin, no `asm`, no added `volatile`, no
`__builtin`, and no zero term.

**One construct needs the coordinator's ruling: a `do { … } while (0)` around the y-outcode `if/else`** (move 4
below). It is not listed in the banned constructs, but it is not inert. It is what ranks `m2` above `arg1` in global
allocation. Without it the best text I found is **score 18** (`PACK/cand_noloop_s18.c`, only the `$s2`/`$s3` swap).
The closest loop-free text is **score 2** (`PACK/cand_noloop_s2_wrongsplit.c`, allocation order right but the
`slt` goes into `$s2`). If the ruling is that the wrapper is a lever in C clothing (METHOD refusal 6), the close is 18,
and the rest of this file still holds.

## (a) The residual in one sentence
Thirteen instructions were missing, from two causes. Eleven went because jump2 cross-jumped case 1 (partly) and case 2
(wholly) into case 6's second-call tail. Two went because sched hoisted the next coordinate group's `lhu` above the
previous group's global stores in the `(m1|m2)==0` block. The register residual (`$s2`↔`$s3`, plus `v0/a1`) is
`allocno_compare` ranking `arg1` (12 refs / 175 live = 2057) above `m2` (6 refs / 141 live = 851).

## (b) Passes and decisions (file:line in tools/reference/gcc-2.7.2)

1. **Cross-jump, jump2 (`toplev.c:3142`, `jump_optimize(insns,1,1,0)`).** For a simplejump, `find_cross_jump`
   (`jump.c:2370`) first compares against the code falling into the label, with minimum 1 (`jump.c:1978`). It then walks
   the `jump_chain` of every other jump to that label, with minimum 2, **but only when `INSN_UID(label) < max_uid`**
   (`jump.c:1985`). `max_uid` is fixed at entry (`jump.c:174`), so jumps to a label that jump2 itself created never
   search the chain. In the free text each case did `r = call; goto done;` to a source label (an old uid). Case 1 and
   case 2 found case 6's `sra; call` (2 insns) through the chain and merged. **Proved on dumps.** In the final text,
   4 unconditional jumps target label 934 in `.jump2`; that is a new uid, above `.sched2`'s max of 932. The
   `func_801365B8` call count is 6 in `.sched2` and 6 in `.jump2` (nothing merged). `func_80136334` goes 5 → 3 (case 4
   and case 8 merged, as in the target).
   The label is new because each case now carries its own `if (v0 != 0) goto ret1; goto AFTER` test. Its fallthrough
   comparison against case 10's identical test (which falls into AFTER) succeeds on the condjump alone, and
   `do_cross_jump` makes `get_label_before` a fresh label. The comparison then stops at the call (f1 ≠ f2 by
   `SYMBOL_REF` pointer, `jump.c:3991`).
   **The case-4 → case-8 merge needs the opposite: a shared old label.** Case 4 is first in the stream. With its own
   test, it would merge into case 10's `call f2` through the fallthrough comparison (bytes: `n2.c`, `j 59c; sra`). With
   `r = f2(..); goto test;`, where `test:` sits right after case 8's call, its fallthrough comparison meets case 8's
   `sra; call` and merges there. Case 8 then merges into case 10's call once `test` itself has been cross-jumped into
   `goto Lnew`. The result is the target's `j 568; sll` → `j 5a8; sra` → `jal` chain (`n3.c`, bytes).
   `return 1` inline instead of `goto ret1` fails (`n1.c`, 135). `if (c) return 1; break;` expands to
   `if (!c) goto AFTER; v0=1; goto RET`. After the RET cross-jump the tail is `beqz → AFTER; j R1`, and the
   jump-around-jump inversion never fires because AFTER does not follow.
2. **sched1/sched2 memory dependence, `true_dependence` (`sched.c:817-835`).** A `MEM_IN_STRUCT_P` load at a varying
   address (`ac[2]`, an INDIRECT_REF of a PLUS_EXPR, `expr.c:4568`) is assumed not to conflict with a *non*-struct
   store at a fixed address (`D_801152AA = 0` through a scalar `extern s16`). So the scheduler hoisted `lhu c1` and
   `lhu ac[1]` over those stores. Declaring the stores' objects as arrays/structs (`extern s16 D_801152AA[]`, `x[0]`,
   `((SVECTOR *)D_80126720)->vx`; ARRAY_REF/COMPONENT_REF set `MEM_IN_STRUCT_P`, `expr.c:4888`) makes the dependence
   real. Proved on bytes: `n3` 51 → `f1` 35 (AA/AC/22/24 as arrays: registers and group 2/3 fixed) → `g5` 18
   (D_80126720 through `SVECTOR *`). `((s16 *)D_80126720)[0]` does not work: `+0` folds, so there is no PLUS
   (`g1`, 35). A block-scope `extern s16 D_80126720[]` is an error (a file-scope `u8[]` is in scope).
3. **Global allocation order, `allocno_compare` (`global.c:596-610`), priority `floor_log2(refs)*refs/live`.** The
   target needs `m2` (r79) before `arg1` (r74): `arg0 $s0`, sext temps `$s1`, `m2 $s2`, `arg1 $s3`. `arg1` has
   12 flow refs, fixed by the 11 reads plus the set. It cannot drop below 3·12/176 = 2045. `m2` needs 10 refs at live
   ~142 (3·10/142 = 2112).
   `reg_n_refs` is counted by flow (`flow.c:2067`, `+= loop_depth`) **before combine**. So an insn that combine later
   merges away still counts. `m2 = -(xA < t3); m2 &= 0x20;` gives three m2 refs at flow (`neg`, then `and` use+set).
   combine folds `(and (neg T) 32)` into `(ashift T 5)` with T's `slt` kept in its own pseudo, which is the target's
   `slt v0; sll s2,v0,5` (bytes: `e0`, 18, m2 8 refs = 1678). Wrapping the `if/else` in `do {} while (0)` puts the
   `else` chain at loop depth 2 (`flow.c:1401` bumps depth at LOOP notes). That gives 1 + 2·3 + 4 = **11 refs =
   2307.7 > 2045.5**. The then-branch set lands outside the notes after jump opt, which is why it counts once. The
   alloc tables are in `scratch/dumps_*` via `pri.sh`; `alloc_table.py` coverage was OK on every run.

## (c) The source moves (one line each, from body_free.c)
1. Each case: `if (callee(...) != 0) goto ret1; break;`, with `ret1: return 1;` at the function end. `default: goto ret1;`
   is required: `default: return 1;` scores 29.
2. Case 4: `r = func_80136334(...); goto test;`. Case 8: `r = func_80136334(...); test: if (r != 0) goto ret1; break;`.
   `ret0: return 0;` stays between case 8 and case 10, and the post-switch y-part does `goto ret0`. This removes the
   free text's `q`/`sv`/`w` trick and the `$5` pin.
3. `extern s16 D_801152AA[]` (also AC/22/24) written `X[0] = …`, and `((SVECTOR *)D_80126720)->vx = h0;`. This removes
   both scheduling barriers.
4. y-outcode: `do { if (t3 < y0) m2 = 0x10; else { m2 = -(y1 < t3); m2 &= 0x20; } } while (0);`. This removes the
   `$19` pin. **This is the move that needs a ruling.**
5. Readability, re-proved at 0: the `arg1_` copy is gone (the parameter is used directly, `r2.c`).

## (d) Generator proposals
- **R-crossjump-freshlabel:** use this when the target keeps N byte-identical `…; jal F; sra; j L` case tails that mine
  folds together (mine shows `j` stubs into another case's tail), and the source joins them with `r = F(); goto done;`
  at a shared test. Give each case its own `if (F(...)) goto ret1; break;`. The join label is then minted inside jump2,
  and `jump.c:1985` never chain-searches it. The inverse rule: when the target *has* a partial merge that mine lacks
  (case 4 → case 8's `sra`), route both through one old source label placed directly after the merge target's call.
  Test: count `jal` per symbol in `.sched2` vs `.jump2`, and check the join label's uid against `.sched2`'s max uid.
- **R-sched-instruct:** use this when the target keeps a pointer load (`p[k]`) after stores to scalar globals and mine
  hoists it above them. Declare the scalar as `extern T x[]` and write `x[0]`, or store through
  `((STRUCT *)sym)->field`. That makes the store `MEM_IN_STRUCT_P`, and `sched.c:817` keeps the dependence. It costs no
  bytes, and the relocation symbol is unchanged.
- **R-flowref-chain:** use this on a callee-saved order swap where the loser is short a few refs and one of its sets
  is `x = (c) << k` / `x = c ? 2^k : 0`. Split it into `x = -(c); x &= 2^k;`. That adds 2 flow refs, which combine
  folds back into `sll` with the `slt` still in its own register. **Do not** use `x = c; x <<= k;` or
  `x = c; x = -x; x &= m;`: the chain then lives in `x` and the `slt` lands in the callee-saved register (`vb` 3,
  `f0` 2). A `do {} while (0)` doubles refs inside it. It closes, but it is a ruling call.

## (e) What did not work (byte evidence, scratch/v/)
- Per-case `if (…) return 1; break;` (`n1`, 135). All cases through `goto ret1`, including case 4 with its own test
  (`n2`, 60: case 4 merges into case 10's call).
- m2 spellings: 3-way if (`w1`), ternary (`x5`), `* 0x20` (`x6`), `m2 = 0; if … m2 |= 0x20` (`x3`), single-expression
  `-(c) & 0x20` (`x8`). All stay at 6 refs (cse/jump1 fold them before flow). Pre-init `m2 = 0x10; if (!…)` (`w6`, 46)
  and `m2 = 0; if … else if …` (`w5`, 35) change the code. `s16/u16/u8/s8 m2` (29, +1 ins). The y-part as
  `switch (m2)` with a default (`y1`) gives the same code and the same refs.
- Chains that raise refs but put the chain in m2's register: `m2 = xA < t3; m2 <<= 5` (cse uses m2 as the store-flag
  subtarget, so `lh s2`, 3). `m2 = t3 > xA; m2 = -m2; m2 &= 0x20` (combine's split reuses i2dest = m2, so `slt s2`, 2).
- The then-branch as a chain (`m2 = -(t3 < y0); m2 &= 0x10`): cse folds it with the branch condition (`t1-t3`, 18).
- `do {} while (0)` around regions holding the accept block (`d1/d4/d5`, 335-345: jump opt moves the accept block to
  the end). Around the p0 outcode from `t1` (`d3`, 39: the loop note blocks the first `D_801909BC` load from rising
  into the prologue).
- Accept/reject spellings `m1 == 0 && m2 == 0` (`b1`, 32) and the distributed reject test (`b3`, `b4`).
- `s16 arg1` local (`a1_s16`): same bytes, but 12 refs all the same. `arg1` cannot drop below `log2 = 3`.

## (f) Where the method fell short
- **The residual mixed three mechanisms**, and the count view alone did not say which instructions were missing. The
  whole-function dump against mine did: the `jump table` targets (`.rodata`) showed case 2 pointing into case 6.
  Reading `.rodata` beside the text should be step 1 for any switch function.
- **The alloc table gave the arithmetic, but nothing in the kit says where zero-byte refs come from.** The two I found
  are that flow counts refs before combine (a combine-merged chain adds refs) and loop-depth weighting. The METHOD's
  list has passthrough args (c10) and cross-jumped duplicates. Both of these belong in `residual_moves.md` next to them.
- The tree's build directory disappeared mid-run (another process). Dump the tree object into `PACK/scratch/` first,
  as METHOD step 1 says.

## Paths
- `PACK/body.c`: the score-0 text (= `scratch/v/r2.c`, plus a comment on the do-while).
- `PACK/cand_noloop_s18.c`: the same without the do-while (18). `PACK/cand_noloop_s2_wrongsplit.c` (2).
- `PACK/scratch/`: `t.sh` (score + candidate disassembly), `dump.sh` (cc1 dumps of the last `--try` TU), `pri.sh`
  (score + alloc table), `fx.sh`, `v/` (every candidate), `target.dis`, `dumps_*`.
