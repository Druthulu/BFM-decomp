# func_8013F350 (ov_SC04_011) — T7 agent c49, minimum-lever task (after b9 and c28)

Earlier readings are kept: c28 in `scratch/c28_mechanism.md` / `scratch/c28_body.c`, b9 in
`scratch/prev_mechanism.md` / `scratch/prev_body.c`. All of c49's scratch is in `scratch/c49/`.
`run.sh <body> <tag> [dump]` runs `--try`. With `dump` it also splices the body into `tu_free.c` and runs
`tools/cc1_dumps_tu.sh`.

**Result: score 0, with 2 levers kept (down from the tree's 3).** `PACK/body.c` is c28's plain-C body (b9's tail
move, `off = st << 1;` hoisted above `p2e`/`p3e`, with the `$4` pin gone) plus the tree's two head levers, unchanged
in meaning and re-marked:

```
register u16 *pd __asm__("$5") = &D_8011511C;  // !FAKE: pin $5 — global.c allocno_compare (:594-603) ranks pd ... (P36 S103 c49 minimum-lever)
__asm__("" : "=r"(pd) : "0"(pd));  // !FAKE: launder pd — keeps &D_8011511C out of cse so find_best_addr cannot fold pd[2] (cse.c:2663) on either .cse2 path (cse.c:8098-8124); proved irreducible in plain C (S103 c28) (P36 S103 c49 minimum-lever)
```

The launder is written in the brief's minimal form, without `__volatile__`. It scores the same as the tree's
`__asm__ __volatile__` form (0 with the pin, 9 without it). There is no other change. `u16 pad` and plain `chg = 0;`
are kept, so neither of b9's compensating moves is used.

## Single-lever table (every number is a `--try` score on c28's plain-C body)

| levers kept | score | class |
|---|---|---|
| none (c28's body) | 42 | COUNT, 491 vs 490: the head is folded to `lui/%lo` |
| pin `$5` only | 42 | COUNT: the pinned pd is still a known constant to cse, so it folds the same way |
| launder only (`__volatile__` form) | 9 | REG-caller: `v1->a1 x6, a1->a0 x4, a0->v1 x3` |
| launder only (plain `__asm__` form) | 9 | same |
| launder + pin `$4` on `pad` (the alternative single pin) | 10 | REG-caller: pd still takes `$v1` |
| **launder + pin `$5` on `pd`** (either launder form) | **0** | MATCH, 490 = 490 |

Plain-C probes on the launder-only body, looking for a replacement for the pin: `chg = 0;` before the launder
scored 15. `pd[2] == pad` swapped scored 9. `pad` declared before `ps` scored 9, and declared first scored 9.

## (a) The residual in one sentence

With the launder alone, the head keeps the base in a register, but three pseudos that all conflict with each other
are coloured in a 3-cycle. Mine: pd `$v1`, pad `$a1`, zext(pad) `$a0`. Target: pd `$a1`, pad `$a0`,
zext `$v1`. That cycle is all of the 9.

## (b) Pass and decision (read in `tools/reference/gcc-2.7.2/global.c`, checked in `dumps_lo` / `dumps_both`)

The three pseudos are r72 (pd), r76 (pad, HImode) and r91 (`zero_extend` of pad, used by both `beqz` and `bne`).
All three are global allocnos. Each one conflicts with the other two and with `$v0` (`.greg`: `72 conflicts: 72 76
90 91 2 29`, and the same for 76 and 91). The ranking is `allocno_compare` (`global.c:594-603`), which computes
`floor_log2(refs)*refs/live*10000`:

- r72 pd: 6 refs, 9 insns, **13333**. The refs are the init, the asm output and input, `*pd`, `pd[2]`, and the store.
- r91 zext: 3 refs, 4 insns, **7500**.
- r76 pad: 4 refs, 13 insns, **6154**.

`.greg` order: `83 72 … 91 … 76`. MIPS gcc 2.7.2 has no `REG_ALLOC_ORDER`, so `find_reg` scans by regno
(`global.c:960-990`). pd takes the first free register after `$v0`, which is `$v1`. The zext takes `$a0`, and pad
takes `$a1`. The pin removes pd from global allocation. The order line in `dumps_both` has no 72, so the zext gets
`$v1`, pad gets `$a0`, and pd keeps `$a1`, which is the target's colouring (verified in `dumps_both/both.i.greg`
insns 13/18).

**Why no plain-C move replaces the pin (a reading, only partly byte-tested):**
1. *Order.* pd would have to rank below pad's 6154. With refs ≥ 6 (the launder alone contributes 2), that needs
   more than 19.5 live insns. pd's whole life is the head: BB0, BB1 and the store block, about 9 insns. The zext
   (3 refs, 4 insns) and pad cannot be pushed above 13333 either. `global.c:604` breaks ties by allocno number
   only when priorities are equal, so declaration order is dead. Byte-tested: two declaration-order probes both
   scored 9.
2. *Preference.* `find_reg` would give pd `$a1` if pd preferred `$a1` (`hard_reg_{copy_,}preferences`), or if
   `$v1` and `$a0` were both in `regs_someone_prefers` (`global.c:953`, built in `prune_preferences`
   `:844-880` from lower-priority conflicting allocnos). Preferences come only from `set_preference`
   (`global.c:1535`). That function needs an insn whose SET has a hard or local-allocated register on one side
   and the allocno (or `XEXP(src,0)` of it) on the other. In the head, pd's only such insn is
   `(set r76 (mem pd))`, and r76 is itself global. The zext appears only in a SET from r76 and in jumps. Pad's
   only candidate is `(set v0-temp (and (subreg r76) 0xF000))`, which prefers `$v0`, and pad conflicts with `$v0`,
   so `prune_preferences` removes it. Creating a `$a1` preference would need a real `move $a1,pd`, meaning a call
   argument inside pd's life. The head has no call, and the calls after it would make pd live across them
   (callee-saved plus extra copies). Not byte-tested beyond the probes above: no zero-byte spelling exists to
   test.

The launder stays for c28's reason, re-proved here as "pin only = 42". A pin does not hide the constant from cse.
`find_best_addr` folds `pd[2]` (`cse.c:2663-2665`), and the BB1 read lies on two `.cse2` paths
(`cse.c:8098-8124`), so the read is re-folded even when cse1 is split away from it.

## (c) The source moves

1. `off = st << 1;` hoisted above `p2e`/`p3e`. This is b9's move and replaces the `$4` pin in plain C.
2. The tree's head levers are kept: the `$5` pin on pd and the launder on pd (now the non-volatile form). They are
   re-marked with the pass each one fakes.

## (d) Generator proposal

When a laundered or pinned base leaves a REG-caller k-cycle among m ≥ 3 mutually conflicting global allocnos
inside one if/else head, compute `allocno_compare` for each of them from `.lreg`. If the target colouring needs
the highest-priority one to be skipped, and none of them has a zero-byte `set_preference` source (check that every
SET naming them has only global allocnos on the other side), mark the pin on the top-priority allocno IRREDUCIBLE
and keep exactly that one pin. The other allocnos then follow from the regno scan. This is mechanical: one `.lreg`
and one `.greg` dump plus the arithmetic in (b).

## (e) What did not work

See the table above. A pin on `pad` (`$4`) instead of pd leaves pd first in the order and in `$v1` (score 10).
Moving `chg = 0;` in front of the launder lengthens nothing useful and scores 15. c28's head experiments (h1-h4 and
d1-d6 in `scratch/c28_mechanism.md`) cover the launder side.

## (f) Where the method fell short

- `alloc_table.py` printed the three head allocnos correctly (pri 13333 / 7500 / 6154), but it cannot say which
  pseudo is which source variable. I mapped r72/r76/r91 by reading the `.lreg` insns 8-18 by hand. A column with
  the first SET insn's source (`symbol_ref D_8011511C`, `mem (reg 72)`, `zero_extend r76`) would have made that
  immediate.
- A "minimum lever" task goes faster as a single ablation grid run first: {none, each lever alone, all} on the
  plain-C body. That is four compiles, and it settled the minimum set before any reading. `tools/delever_search.py`
  could print this grid itself.
