# func_801F2348 (md_SC03_076_jr_801F218C.c) — P36 T7 S104 agent d9

**Result: score 0, plain C, zero levers** (tree: 1 NEEDED `__asm__("")` barrier → 0). Also scores 0 on all five
copies of the text (see "Family" below) — 6 barriers → 0.

## (a) The residual
COUNT, 32 vs 34 ins: the third arm (`if (func_80029178(250) & 0xFF) t = 0; else t = 1;`) compiled to a store-flag
`sltiu v0,v0,1` where the target keeps `bnez v0,join / move v0,zero (delay) / li v0,1`. Nothing about registers: an
if/else was converted into straight-line code before cse ran.

## (b) The pass and the decision (read, and PROVED on the .rtl/.jump dumps of both spellings)
First jump pass, two cooperating transforms in `jump_optimize`:
1. `jump.c:699-795` "Simplify `if (...) x = a; else x = b;` → `x = b; if (...) x = a;`". INSN = the `goto join` after
   `t = 0`; TEMP2 = `t = 1` (the next active insn, right before `join`); TEMP = the condjump around `t = 0`. All of
   `:727-771` holds, the use scan finds the single use, `no_labels_between_p (p, insn)` (`jump.c:805`) holds, so `t = 1`
   is hoisted above the condjump (new insn uid 100 in `free.i.jump`).
2. `jump.c:1015-1300` store-flag case 1 ("x = a; if (...) x = b; and either A or B is zero"): now the condjump is
   followed by `t = 0` (`GET_CODE (temp) == INSN`, `jump.c:1019`) and falls into `join`, `reg_set_last` finds `t = 1`
   (CONST_INT), so with BRANCH_COST 1 (`config/mips/mips.h:2935`, R3000) it still fires via the A/B-zero test and emits
   `t = (r80 == 0)` (`xor`/`ltu` insns 102/104/106) — the `sltiu`.
The tree's `__asm__("")` before `t = 1` worked by making TEMP2 an ASM_INPUT insn (single_set fails, transform 1 dies,
so transform 2 never sees the `x = a; if … x = b` shape).

## (c) The move that closed it
Rewrite the goto chain as the structured `||` the sibling `func_801F0904` (md_SC05_026, lever-free) uses:

    if ((u32)(x - 200) < 100) {
        t = 0;
    } else if (x < 300 || (func_80029178(250) & 0xFF) == 0) {
        t = 1;
    } else {
        t = 0;
    }

`x < 300` now jumps INTO the `t = 1` arm, so a code_label sits between the `(f & 0xFF) != 0` condjump and `t = 1`.
In `a.i.jump` the order is `jump 37 → label 40 → t=1 (44) → goto join (46) → label 48 → t=0 (52) → join`:
- transform 1 at jump 46: TEMP (via `prev_active_insn`, which skips label 40) = jump 37, the use scan stops at it,
  `p = PREV_INSN (jump 37)`, and `no_labels_between_p (p, insn)` (`jump.c:805`) FAILS on label 40 — no hoist;
- transform 2 at jump 37: `next_nonnote_insn` is label 40, `GET_CODE (temp) == INSN` (`jump.c:1019`) FAILS.
The branch survives; reorg then fills the delay slots exactly as the target (`move v0,zero` / `li v0,1`).
Proved: score 0 on `--try` (34/34 ins), dumps in `scratch/dumps_free/` vs `scratch/dumps_a/`.

The tail (`p`/`v` loaded per arm) must stay as the tree has it: folding `p` into one `*(s32 *)(D_801EF3EC + 4) = v`
scores 13 (the per-arm `lw` of D_801EF3EC is in the bytes).

## (d) Generator proposal
When a NEEDED `__asm__("")` barrier sits immediately before a constant store `t = K` that is the fall-through arm of
a `goto join` chain (or a `? : ({ __asm__(""); K; })` ternary), and an EARLIER arm of the chain stores the same `K`,
merge those two arms into one `else if (A || !B) t = K;` so the earlier test enters the K-arm through a label —
the label between the condjump and the store blocks jump.c's if/else hoist (`:805`) and its store-flag conversion
(`:1019`).

## (e) What did not work (bytes)
- body_free.c and the whole free sweep (R7 blocks/do-while, R12 widths u16/s16/u8): 6 — none touches the jump shape.
- `t = (u32)(x-200) >= 100 && (x < 300 || !(f & 0xFF));` : 15 (TRUTH_ANDIF expansion `t = 0; …; t = 1` keeps t
  live across the call → s0 and a frame slot).
- the nested ternary `t = c1 ? 0 : (c2 ? 1 : (!(f & 0xFF) ? 1 : 0));` : 4 (the innermost `?:` is its own if/else with
  no incoming label, so the store-flag still fires).
- the `func_801F098C` goto spelling (`else if (x >= 300) { if (f & 0xFF) goto z; t = 1; } else t = 1; … z: t = 0;`)
  also scores 0 — a second valid spelling; the `||` one is chosen as the more readable.

## (f) Where the method fell short
Nothing structural: METHOD step 3's "READ LEVER-FREE BODIES that share your callees" was the whole crack —
`related.txt` did not list `func_801F0904` (another overlay, md_SC05_026), but the R71 grep for
`func_80029178(250|0xFA)` + `+ 4) =` across src/ found it at once. Suggest related.txt search the WHOLE tree for
bodies sharing the same (callee, constant-argument) pair, not only the same overlay. Also: the free sweep has no
generator that re-shapes a goto chain into `||`; all its moves were declaration-level and could not reach a jump.c
decision.

## (g) Structs question
No. The lever steered a first-jump-pass control-flow decision (`jump.c:727-805`, `:1015-1019`), which looks only at
insn/label adjacency and SET shapes on a pseudo; the global `D_801EF3EC` (a pointer whose +4 field receives a
handler/table address) does not take part — the `t` flag is a scalar computed from call results. Typing
`D_801EF3EC` as `struct { s32 f0; void *f4; } *` would only change the final store `*(s32 *)(p + 4) = v`, which
already matches. Not tested on bytes because the plain-C close made it moot.

## Family (all `--try` score 0, bodies in `scratch/c/`)
| function | TU | tree lever | candidate file |
|---|---|---|---|
| func_801F2348 | md_SC03_076_jr_801F218C.c | 1 barrier | `body.c` |
| func_801F23D0 | md_SC03_076_jr_801F218C.c | 1 barrier | `scratch/c/sib_23D0.c` (D_801F3830/D_801F3864) |
| func_801EAA7C | md_SC04_027_jr_801EA8C0.c | 1 barrier | `scratch/c/sib_EAA7C.c` (D_801EBD50/D_801EBD90/D_801E7AAC) |
| func_801E5514 | md_SC03_135_jr_801E5358.c | 1 barrier | `scratch/c/sib_E5514.c` (D_801E67E8/D_801E6828/D_801E256C) |
| func_801EAB04 | md_SC04_027_jr_801EA8C0.c | 1 barrier memory (ternary) | `scratch/c/sib_EAB04.c` |
| func_801E559C | md_SC03_135_jr_801E5358.c | 1 barrier (ternary) | `scratch/c/sib_E559C.c` |
