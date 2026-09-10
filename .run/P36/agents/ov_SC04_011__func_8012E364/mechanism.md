# func_8012E364 (src/ov_SC04_011/ov_SC04_011_jr_8012ACE0.c) — T7 reading

**Final score 4** (class ORDER, 67/67 ins), from 25 lever-free / 7 mechanical best.
`PACK/body.c` holds it. NOT a match — the reading below says exactly what the last 4 are.

## (a) The residual in one sentence

At the mechanical best (7) the diff read as two clusters — an association order
(`addu` before `subu`) and the `abs` emitted with gcc's *dest == src* arm (`nop` in the delay
slot) instead of the *dest != src* arm (`move %0,%1`) — but they are ONE decision: local-alloc
ties the abs destination `d` into its dying input `v`, and that tie removes a whole quantity
from block 8, which re-ranks every other quantity in the block and slides the caller-saved bank
down by one register (`arg0` `$a1` instead of `$a2`, `spd` `$a2` instead of `$a3`, the `mfhi`
temp `$a3` instead of `$t0`, `prev` `$v1` instead of `$a1`). Break the tie and all of that
falls into place at once; what is left over is one statement's SCHEDULED position.

## (b) The pass and the decision, from the compiler's source

* `local-alloc.c:1722 combine_regs`, called from `block_alloc` at `local-alloc.c:1295`.
  At `(set (reg d) (abs:SI (reg v)))` it ties `d` into `v`'s quantity unless one of
  - `local-alloc.c:1765` — `reg_qty[v] < 0` (v is not local to the block, or dies more than once);
  - `local-alloc.c:1774/1843` — `reg_qty[d] == -1` / `>= 0` (d is not block-local, or is already born);
  - `local-alloc.c:1854` — `v` has no `REG_DEAD` note on the insn, i.e. **v is still live after the abs**.
  The -2/-1 states are set at `local-alloc.c:475/477`: `reg_basic_block[i] >= 0 &&
  reg_n_deaths[i] == 1` → -2 (a local-alloc candidate), else -1.
* `mips.md:1526 abssi2` (`"=d"` / `"d"`, a 3-instruction `multi` that emits its own branch and
  fills its own slot) reads the tie back out at assembly time:
  `REGNO(op0) == REGNO(op1)` → `bgez %1,1f%#\n\tsubu %0,%z2,%0` (the `%#` becomes maspsx's `nop`);
  otherwise `%(bgez %1,1f\n\tmove %0,%1\n\tsubu %0,%z2,%0\n1:%)`. The target is the second arm.
* `local-alloc.c:1579 qty_compare` — priority `log2(n_refs)*n_refs*size / (death-birth)` — is why
  the tie moves everything else. Tied, the quantity `{D-load, tmp, v, d}` carries `n_refs` 10 and
  outranks `flags` (`n_refs` 4), so it takes `$v0` first. Untied, `flags` (pri 2.0) goes first at
  `$v0`, the `{D-load, tmp, v}` chain (pri ~1.55) takes `$v1`, `d` (pri 1.0) takes `$v0` again
  after `flags` has died, `e1`/`e2` take `$a0`, and `prev` — now the lowest-priority quantity of
  the block — is left `$a1`. `global.c` then sees one more hard-reg conflict for `arg0`
  (measured in the `.greg` dumps: `73 conflicts: … 2 3 4` tied vs `… 2 3 4 5` untied) and moves it
  to `$a2`, `spd` to `$a3`, the `mfhi` temp to `$t0`.
* `sched.c:2427 rank_for_schedule` — the tie-break is `INSN_LUID` descending, i.e. **source order
  is preserved whenever priority and class tie**, which is why every remaining question here is a
  question about the order of the statements in the C.

## (c) The move

ONE statement moved, nothing else touched:

```c
    flags = *(u16 *)(e1 + 0x2C);
-   D_801ED9D8 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;
    e2 = *(s32 *)(arg0 + 0x20);
    d = __builtin_abs(v);
    *(s16 *)(e2 + 0x1C) = d;
    *(s16 *)(e2 + 0x18) = d;
+   D_801ED9D8 = v;
```

`D_801ED9D8 = v;` is now the LAST use of `v`, so `v` has no `REG_DEAD` note on the abs insn,
`combine_regs` refuses (`local-alloc.c:1854`), and `d` stays a block-local quantity of its own.
The `.greg` dump of this body has the target's allocation exactly — `74(prev) in 5, 75(flags) in
2, 78(v) in 3, 79(d) in 2, 81(e1) in 4, 82(e2) in 4` — and every one of the 67 instructions'
registers matches. 25 → 4.

The two-`sh` sandwich is load-bearing: the store must sit after at least one of the entity stores
or sched1 hoists it back above the abs (measured: with the store immediately after the abs,
score 16 and the `nop` arm returns — the store has no consumer, so sched gives it the lowest
priority and pushes it to the front of the block; only a memory op it may not cross holds it).

## (d) What the last 4 are, and why this spelling is not the original

The whole residual is the position of `lui at,0x0 / sw v1,0(at)`: mine emits it at 61-62 (last),
the target at 53-54 (right after the `addu`, before `ori/sh` of the flags word). That position is
forced by the memory output-dependence chain: the target's D_801ED9D8 store precedes the
`sh …44(a0)` flags store, so in the ORIGINAL source `D_801ED9D8 = v;` comes BEFORE
`*(u16 *)(e1 + 0x2C) = flags | 0x10;` — which is where `body_free.c` already has it, and which
makes the abs the last use of `v`. So the original breaks the tie some OTHER way, and I did not
find it. Everything else about the original is now pinned down: `d` is a block-local,
single-set, single-death quantity that is NOT tied to `v` — so the untie is neither
`reg_qty[v] < 0` nor `reg_qty[d] != -2` (both of those force one of the two into `global_alloc`
and measurably land it on `$a1`/`$a0`, never the target's `$v0`; see (e)).

## (e) Measured negatives (all on bytes, all 67/67 ins unless noted)

| spelling | score | abs delay slot |
|---|---|---|
| `body_free.c` (lever-free start) | 25 | `nop` |
| mechanical best (`R5 swap + @786`, `R7 do-while @790`) | 7 | `nop` |
| `v = D_801ED9D8 + spd - prev;` (assoc; every register right except the abs) | 9 | `nop` |
| `v = spd + (D_801ED9D8 - prev);` / `spd - prev + D…` / `(spd + D…) - prev` | 19 / 17 / 7 | `nop` |
| R13 reassociation composed with R8's common-subexpression form (the S101 suggestion) | ≥ 7 | `nop` |
| hand-rolled abs (`d = v; if (d<0) d = -d;`, `if/else`, ternary, `abs()`) | 25 | `nop` (all fold to abssi2's dest==src arm) |
| `s16`/`u16`/`u32`/`s8` `d` | 25/25/25/30 | `nop` |
| abs inlined at both stores (cse names it once) | 25 | `nop` |
| `e2` inlined at both stores | 27 (69 ins) | `nop` |
| **`prev` reused as the abs destination** (2 deaths → `reg_qty=-1` → untied) | **5** | `move a1,v1` (d global → `$a1`) |
| `d` reused as the flags temp (`d = *(u16*)(e1+0x2C); … d = abs(v);`) | 10 | `move a1,v1` |
| `d` merged into `a` / `arg0` / `diff` / `e1` | 19 / 19 / 23 / 28 | `move a0,v1` / `move a1,v1` / `nop` / `move a1,v1` |
| `v` made multi-death (`v = D_801ED9D8; v = v - prev + spd;`) | 14 | `move v0,a1` (d local → `$v0` ✓, v global → `$a1` ✗) |
| `v` carrying the D_801ED9D8 value through the whole smoothing chain | 26 | `move v0,a1` |
| `v = D_801ED9D8 - prev; v = v + spd;` (split) | 25 | `nop` — gcc emits NO `REG_DEAD` for a reg that is used **and set** by the same insn, so the split does not create a second death |
| every extra "earlier life" for `v`/`d` that constant-propagates or is dead (`d = 0;`, `d = e2;`, `v = 0x1000` in the `a == 0` block, `v = diff>>2` inside the if) | 25-32 | `nop` — folded away before local-alloc |
| all 92 topological orders of the 7 tail statements with the store BEFORE the abs | ≥ 15 | `nop` |
| all orders with the store between the abs and the first `sh` | ≥ 15 | `nop` (sched1 hoists it) |
| beam over statement moves, decl moves/order, commutative swaps, widths, block/do-while, merges, splits, abs re-spellings — 5,776 + 7,000 compiles from the 4/5/14/15/25 seeds, depth 3 | 4 | — |

## (f) GENERATOR PROPOSAL (one sentence)

**When the diff is the `abssi2` delay-slot pair — mine `bgez X,…; nop; negu X,X` against the target's
`bgez X,…; move Y,X; negu Y,Y` (equivalently: a same-length REG residual whose only extra word is a
`nop` where the target has a `move`) — move the abs's operand's OTHER use (the statement that reads
it besides the abs) to AFTER the abs statement, keeping at least one store between them, and if that
is refused, rename the abs's destination onto a local that is already assigned elsewhere in the
body**; the first form is the byte-proven one (25 → 4 here) and it is the generic
"last-use-after-the-consumer" edit for every `combine_regs` tie, not just `abs`.

Implementation sketch for `tools/delever.py` (a new family, call it R19 `last_use_moves`): for each
statement `T = f(V);` whose RHS mentions a local `V`, enumerate the other statements that read `V`
and emit one candidate per legal later slot for each of them (the slot must keep at least one
memory-writing statement between the moved statement and `T`, or sched1 hoists it back).
A cheaper, purely diff-driven trigger: the residual has `mine[i] == "nop"` and
`target[i] == "move rA,rB"` with `mine[i+1] == "negu rB,rB"` and `target[i+1] == "negu rA,rA"`.

## (g) Where the method fell short

1. **The pack's `history.txt` names moves, not scores per cluster.** The mechanical best (7) hid the
   fact that its two clusters were one decision; `--explain --path` showed the diff but not that
   `arg0`'s `$a1`/`$a2` split (visible only at score 25) is the SAME tie. Reading the `.greg`
   `conflicts:` line for the incoming-parameter pseudo was what tied them together — that line
   should be part of what `--explain` prints for a REG-class residual.
2. **The generator registry has no VARIABLE-MERGE and no LAST-USE-MOVE family.** Both were needed
   here: the merge family found the untie (score 5) and the last-use move found the answer (4).
   R13/R8, which the brief suggested composing, cannot reach either: they never change which
   statement is a value's last use.
3. `delever_search --try` serialises on one scratch directory per `(alias, fn)`, so a private
   copy of the compile (0.26 s vs 0.85 s, and parallel-safe) had to be written before any real
   search was possible — 14 compiles in the time of one. That belongs in the tool.
4. The beam I ran kept a frontier of six score-4 siblings for three levels: **a beam must
   de-duplicate on the residual's DIFF SIGNATURE, not on the score**, or a plateau eats the budget.
