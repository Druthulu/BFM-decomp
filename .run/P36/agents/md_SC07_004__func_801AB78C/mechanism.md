# func_801AB78C (md_SC07_004) — P36 S104 agent e8 — score 9 (lever-free) -> 0 with ZERO levers (was 1 `$3` pin)

(a) Residual: 37 vs 35 ins. Lever-free, the second read of the counter is `lbu v0; andi v0,v0,0xff` (a redundant
re-zero-extension) and `b = t` is an extra `move` + a `nop`; the target is `lbu v1; beqz v1; addiu v0,v1,-16 (slot);
bgez v0; move v1,v0 (slot); move v1,zero; sb v1` — no `andi`, and the stored value shares the loaded value's register.

(b) Pass and decision (dumps `scratch/T6_vol_u8_s16_{cse,combine}.txt` vs `scratch/T6_vol_u8_s32_*`):
- The `andi` is a `zero_extendqisi2` (insn 52) combine could not fold. combine substitutes an insn into its user only when
  its destination dies there; `zero_extend:SI (reg:QI b)` is foldable away (the load is `lbu`, `LOAD_EXTEND_OP (QImode) =
  ZERO_EXTEND`, so the upper bits are known zero — `nonzero_bits`) ONLY into a single user. With `s32 t`, cse commons the
  test's `zero_extend:SI b` and the subtraction's into ONE pseudo (u8_s32 .combine: insn 52 feeds both the `beqz` and
  `t = 85 - 16`), so it has two users and survives as `andi`.
- With `s16 t`, `b - 0x10` is expanded through `zero_extend:HI (reg:QI b)` (insn 57, a DIFFERENT expression, so cse does not
  common it with the test's `zero_extend:SI`); each extension has one user, combine folds both (u8_s16 .combine: the test reads
  `(subreg:SI (reg:QI 74))`, the add reads it too), and the `(s16)` re-extension of `t` before the `t < 0` test is dropped
  (sign-bit copies of `zext(QI) - 16` >= 17, `combine.c:7926-7942`). `b = t` is then a QImode subreg copy
  (`(set (reg:QI 74) (subreg:QI (reg:SI 87)))`, insn 64) printed as `move v1,v0` in the bgez slot.
- `u8 b` puts the loaded value, the clamped value and the store in ONE QImode variable (74), set three times — the target's
  single `$v1`; the tree's `$3` pin was forcing that sharing on an s32 `b`.

(c) Moves (joint, proven — body.c, score 0):
1. `b` declared `u8` (the width of the object it loads and stores), `t` declared `s16`;
2. `t = b - 0x10;` moved inside `if (b != 0)` (the tree computed it before the test; with u8/s16 at the old position = >6);
3. `*p = (u8)b;` -> `*p = b;` (b is already u8). The pre-existing `volatile u8 *p` stays (allowed; without it cse forwards
   the first read across the u16 stores and the second `lbu` + test vanish — best non-volatile spelling 9).
Also 0: the if/else form `if (t < 0) b = 0; else b = t;` (`scratch/y/T4_vol_u8_s16.c`). 300-body sweep
(`scratch/sweep_b.py`, 10 tail shapes x widths x volatile/plain): exactly these two at 0; next best 3.

(d) GENERATOR PROPOSAL: when the residual has an extra `andi 0xff`/`andi 0xffff` right after an `lbu`/`lhu` whose value
feeds both a test and an arithmetic, declare the loaded local at the load's width (`u8`/`u16`) and the arithmetic's result
at the NEXT width up (`s16` for a `u8`), so each extension is a different RTL expression with one user; try moving the
arithmetic inside the test it follows.

(e) Did NOT work: the free sweep's best 7 (R6 inline b, R12 b->u16/s16 alone, R12 t alone); in my sweep, u8 b with s32 t
= 4 (the andi: one shared zero_extend), s16/u16 b = 3 (no andi but the store takes an extra register), s8 anything >= 5,
and every non-volatile spelling >= 9.

(f) Method gap: METHOD 14's "declare y at the width the bytes prove" was right but needed TWO widths chosen jointly plus a
statement move (the sweep's R12 changes one declaration at a time and R9 did not move `t` into the if). The deciding fact
(cse commoning two zero_extends of different users) is only visible by diffing `.cse` against `.combine` on the two widths.

(g) Structs: NO for this lever — the decision is cse/combine over a scalar QImode local. `a0` as a struct (0x20 pointer to a
sub-object with u16 0x18/0x1A) would read better for the two u16 updates, and D_801F88BA is a lone u8 counter; not tested
(nothing left to close).

(h) Joint check (e8): all four e8 body.c files spliced into one copy of the tree TU (`md_SC07_004__func_801AB78C/scratch/splice4.py` -> `scratch/tu_all4.c`): each of the four scores 0, and the whole object is sha1-identical to the baseline per section (.text ad583f4dfb0c, .rodata, .data/.sdata/.bss) with .rel.text identical.
