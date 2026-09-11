# func_801836D4 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e30)

**Result: score 0 in plain C.** No pin, no asm, no added volatile. Levers go from 2 to 0 (the `$3` pin on `b`, the `$2` pin
on `tw`). Signature unchanged. No copy of the class elsewhere in `src/` that I found (the `0xEC/0xEE/0xF0` triple plus the
`buf[16]` scratch occurs only here).

## (a) The residual in one sentence
Two defects. The target keeps a copy `move a1,v0` (the `s16` copy of the `lh` value, used by the `xor`) that the free body
loses (59 vs 60). Under that, the `a1`-relative load `b` is in `a1` in mine and in `v1` in the target (6 insns).

## (b) The passes and the decisions (proven on the `.cse`/`.lreg`/`.greg`/`.jump2` dumps and bytes)
1. **The missing copy is cse's paradoxical-SUBREG fold.** The free body has `t16 = tw;` in the join block. The `xor`
   reads `(subreg:SI (reg:HI t16))`. In the same cse block (`Processing block from 130 to 157`), `fold_rtx`'s SUBREG
   case (`cse.c:4836-4870`, "these SUBREGs just say how to treat the register") finds `t16` equivalent to
   `(subreg:HI tw)` and returns `tw` itself. `t16` dies unused, and `tw` must live until the `xor`. The `.cse` dump
   shows `(xor:SI (subreg:SI (reg/v:HI 76)) (reg/v:SI 78))`.
2. **`b` in `a1` is global.c's `expand_preferences`.** `b` is shared by the three cases, so it is a global allocno
   (it dies in 3 places). Its load `(set (reg b) (mem (plus r73 6)))` is where the `a1` parameter pseudo r73 dies, and the
   two do not conflict. `expand_preferences` (`global.c:780-822`) therefore merges r73's `a1` preference into `b`.
   `b` has the highest priority (20000, `.greg` order `74 …`), so it takes `a1`.
3. **Per-case locals put `b` in `v1` only with THREE quantities in the case block.** With `a`/`b` block-local (split or
   inlined into the subtraction), local-alloc ranks two quantities and `b` wins on priority (shorter life), so it takes
   `v0` and `a` takes `v1` (score 9, the swap). local-alloc's hand-written 3-quantity order (`local-alloc.c:1486-1500`)
   compares qty 0/1, then 1/2, then 0/1 AGAIN. With exactly three quantities where qty 1 beats qty 0 but not qty 2, the
   final order puts qty 0 (`a`) first. `tools/localalloc_sim.py` on the winning `.lreg` shows it: block 8, qtys
   `q0 r84 5000 → v0, q1 r85 10000 → v1, q2 r83 7500 → v0`, and `mismatches vs dump: 0`. The third quantity is the
   case's own `tw` (`s32`, the `lh`), which is local ONLY when the case also tests it (`if (tw == 0)` inside the case).
4. **The case-local copy survives, and cross-jump merges the three tails.** `t16 = tw;` now sits in the case block. The
   `xor` is in the join block, which is a new cse block, so fold (1) has no equivalence to use and the copy stays. After
   reload the three case tails (`nop; beqz v0,ret1; move a1,v0`) are identical, and jump2's cross-jump
   (`jump.c:2371`) merges them into the one sequence the target has. The `a1` copies counted per dump: `.greg` 5,
   `.sched2` 5, `.jump2` 3, `.dbr` 2.

## (c) The moves that closed it (joint)
Each case declares its own `s32 tw`, copies it into `t16`, and tests it there. The two `u16` locals are inlined into the
subtraction (a block-local `u16 a`, `u16 b` pair also scores 0: `scratch/c6/block_block_copy_test.c`).
```c
    case 0: {
        s32 tw;

        diff = *(u16 *)((s32)a0 + 0xE4) - *(u16 *)((s32)a1 + 0x6);
        buf[0] = diff;
        tw = *(s16 *)((s32)a0 + 0xEC);
        t16 = tw;
        if (tw == 0) {
            return 1;
        }
        break;
    }
    ...   /* cases 1, 2 the same with 0xE6/0xA/0xEE and 0xE8/0xE/0xF0 */
    default:
        goto default_case;
    }

    if (diff == 0) goto ret1;
    xr = diff ^ t16;
    if (xr >= 0) goto default_case;
ret1:
    return 1;
default_case:
    return *(s16 *)((s32)a0 + 0xEA) == 0;
```
The copy must come BEFORE the test (`*_test_copy` variants score 9). A fully structured tail (`return` in the default,
`if (diff != 0) {…}`) changes the block layout and scores 9-17 (`scratch/c7/struct*`). The label tail stays.

## (d) Generator proposal
When a `switch` whose cases each load a value that is tested after the join (`lh vN; j join … join: beqz vN; move aK,vN`)
leaves a copy missing and a register swapped, sink the join-point test and copy INTO every case, on a case-local variable
(`{ T v = load; keep = v; if (v == 0) return/goto; } break;`). Cross-jump re-merges the identical tails after reload, the
fold moves out of cse's reach, and the case block gains a quantity (which can flip local-alloc's 3-quantity order).
No generator today moves a statement across the switch join.

## (e) What did NOT work (byte evidence, all in `scratch/`)
- `s16 tw` with no `t16` (`c1/v1.c`): 14. The load becomes `lhu` and the copy is still missing.
- Tail restructurings with the copy in the join (`c3/goto_before, or_after, or_xr, nest, reuse_tw*`): 12-14. Same
  cse block, so the fold happens.
- The copy in each case with the test still at the join (`c3/case_copy.c`): 6, count right, `b` still in `a1`
  (`expand_preferences`).
- Widths of `a`/`b` (`c4/w_*`): 6. Splitting `a`/`b` per case with 2 quantities (`c5/ab_*`): 9 (swapped) or 6 (right
  registers but `b`'s load first).
- The sweep's best was 12 (R12 `t16` s16->u8 + R9).

## (f) Where the method fell short
- The tree header blamed local-alloc coalescing for the missing copy. It was the cse SUBREG fold, which one `.cse` dump
  showed. The header's claims should be treated as @stuck-style claims.
- `tools/localalloc_sim.py` confirmed the 3-quantity order after the fact. The deciding idea came from METHOD S104 d5/d21
  ("a block with exactly 3 quantities is allocated in BIRTH order — add or remove a quantity"). Its usage line needs the
  uid of an insn IN the block (it crashes with an IndexError on a uid outside the function's insn list, which is how
  I first mis-called it).
- A 12-body structural batch (a/b global/block/inline × tw global/block × copy/test order) found the close in one run.

## (g) Structs question
Partly, for readability only. `a0` is an actor with a per-axis triple at `+0xE4/E6/E8` (target position), a direction
triple at `+0xEC/EE/F0`, an axis selector at `+0xE2` and a timer at `+0xEA`. `a1` has a position at `+6/+A/+E`. With
arrays (`a0->tgt[axis]`, `a0->dir[axis]`, `a1->pos[axis]`) the switch could even become one indexed body, but that would
change the code (the target has a real 3-way switch). None of the decisions here (cse's SUBREG fold, expand_preferences,
local-alloc's quantity order, cross-jump) depend on MEM_IN_STRUCT_P, so a struct type would not have removed a lever.
Not tested.

Files: `body.c` (score 0, `= scratch/c7/goto_r1.c`), `scratch/c6/` and `scratch/c7/` (batches with `scores.txt`),
`scratch/c1`-`c5/` (the failures above), `scratch/d_free/`, `scratch/d_cc/`, `scratch/d_win/` (dumps).
