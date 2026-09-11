# func_8018003C (ov_SC02_016_jr_8017DC70.c): P36 S104 agent d24. Score 36 to 0, zero levers, 4 copies

**Result: score 0 in plain C.** No pin, no asm, no volatile, no do-while, no dead initialiser. The first `--try` of a
natural rewrite scored 0 (`scratch/n1.c`). `PACK/body.c` is the same text with the timer given its own name. I checked
the bytes separately: `objdump -drz` of the `--keep` object equals the baseline snapshot, relocations included. Levers
before and after: 4 pins ($17, $5, $6, $0) and the `a0 = s0 + zr` launder go to 0.

## (a) The residual in one sentence
The lever-free text had 44 instructions against the target's 42. The two `func_801292C8(p)` call sites loaded `$a0`
from different callee-saved registers (`move a0,s1` against `move a0,s0` after a `move s0,s1`), so the post-reload
cross-jump could not merge them into the target's single `jal func_801292C8; move a0,s1` tail. On top of that,
`a1/a2/v0/v1` were permuted in the vector-add block.

## (b) The passes and decisions (proved on bytes by ablation: every row below is one move reverted from body.c)
| move reverted (file in scratch/)                     | score | pass / decision |
|------------------------------------------------------|-------|-----------------|
| `s32 s1 = arg0;` parameter copy (H.c)                | 19 COUNT | **cse1 `make_regs_eqv` (`cse.c:846-862`)**. The param pseudo (73) stays canonical over the copy (72) through block 0 and the then-arm. The else-arm, which cse processes as a new path at label 80, reads 72. `.i.cse` lines: insns 13-43, 62, 74 use 73, and insns 84, 94, 101 use 72. `.lreg`: 72 "crosses 2 calls", 73 "crosses 1 call". Two call-crossing pseudos take two `$sN`, the two `func_801292C8` tails differ, and **`find_cross_jump` (`jump.c:2371`)** cannot merge them, which gives 2 extra instructions. This is the same mechanism as S104 d17's note. |
| call through `((void (*)(void))func_8012931C)()` (A.c) | 4 REG | Passing `arg0` costs 0 bytes. The copy `(set a0 s1)` survives greg (`.i.greg` insn 41) and **jump2 deletes it as already-equivalent (`jump.c:437-462`, `find_equiv_reg`)**. But `$a0` stays live from entry to the call, so local-alloc can't give it to the `+0x30` temp, and the temps land in `a1/a2` as in the target. Without the argument, `$a0` is free and the temps take `a0/a1`. This matches S103 c35 / generator R19. |
| body_free's hoisted temps `v0,v1,a1,a2` with `v0` reused (C.c) | 12 REG | This is local-alloc quantity order. `v0` holds two values ("dies in N places", refused by `local-alloc.c:472`). With `x += y` written directly, every load and sum is a single-use pseudo, and the birth order gives `v0/v1` then `a1/a2`. **Not proven in the dumps**: only the byte result was checked. |
| `a0 = s0 + 0;` second name for `obj` (B.c)          | 0     | Harmless. cse folds it, so it was never the defect. The tree's `$0` pin was faking nothing that plain C needs. |
| body_free with only the call fixed (D.c) / only the copy removed (F.c) / both (E.c) | 36 / 36 / 36 | This shows the **parameter copy is the dominant defect**. Every body that keeps `s1 = arg0` stays at the COUNT gap, whatever else changes. |

## (c) The source moves that closed it (joint: all three are needed, and each alone is worse)
1. Delete the parameter copy `s32 s1 = arg0;` and use `arg0` directly (jumps 36 to 0 when combined with 2 and 3).
2. Call `func_8012931C((struct vec *)arg0)` at its real arity, not through a zero-argument cast.
3. Write the vector add as three `*(s32 *)(arg0 + K) += *(s32 *)(arg0 + K + 0x1C);` statements instead of hoisted,
   reused temps.

Also: the `a0 = s0 + zr` launder is gone (`obj` is one variable), and the goto-free if/else is kept. The `||` form
(`scratch/G.c`: `if (func_80128ED8(...) != 0 || (*(s32 *)(arg0 + 0x1C) != 0 && --*(s32 *)(arg0 + 0x1C) == 0))`) also
scores 0, so pick either for readability.

## (d) Generator proposal
When a COUNT residual shows two call sites of the same callee whose `$a0` loads come from different `$sN` (a missed
cross-jump) and the body opens with `T x = argN;`, delete the copy and rename `x` to `argN` throughout. Apply it jointly
with R19 (call at real arity) and an "inline single-use temps into `+=`" rewrite. Each of the three alone scores worse
than the three together, so a single-move beam never finds it. The sweep's best was 9 because no family deletes a
parameter copy.

## (e) What did not work / what the sweep missed
- The regen best (9) kept `s1 = arg0` in every candidate, so the COUNT gap could never close (ablation H: the copy alone
  = 19).
- Porting the two same-name `func_8018003C` definitions in other binaries was not attempted. The brief says they scored
  ~50, and the copies grep shows this class's real siblings are `func_80187CE8`, `func_80182EB0` and `func_80181D9C`.
  Those are all the same tree text, and all close with this body.

## (f) Where the method fell short
It didn't fall short. Reading the pack plus S104 d17's "delete the hoisted parameter copy" note predicted the close,
and the first natural rewrite matched. The one gap: `history.txt` and the regen families never try deleting a
`T x = argN;` prologue copy. That copy is a decompiler artefact (m2c names the saved register `s1`) and appears in many
tree bodies, so it's worth a generator (d).

## (g) Structs answer
Structs are **not needed** for this class. The levers were decompiler artefacts: the param copy, the zero-arg cast and
the hoisted temps. They weren't struct-shaped pass decisions. Structs are **compatible**, though, and I tested this on
bytes:
- `scratch/struct2.c`: `struct m8018003C { u8 pad0[0x10]; s32 vx, vy, vz /*0x10*/; s32 timer /*0x1C*/; s32 obj /*0x20*/; s32 hit[2] /*0x24*/; s32 ax, ay, az /*0x2C*/; }`
  as the **parameter type**, with `obj` as `struct { u8 pad0[0x18]; u16 unk18, unk1A; } *`, scores **0**. The
  aggregate (MEM_IN_STRUCT_P) accesses did not change sched1's order here, because there is no scalar store for a load
  to pass.
- `scratch/struct.c`: the same struct reached through a body-local `p = (struct m8018003C *)arg0;` scores **19**,
  exactly the param-copy defect of ablation H. So a struct retype must change the **parameter's** type, not add a typed
  local copy. Banking the struct form would also mean updating `extern void func_8018003C(s32 arg0);` in
  `src/ov_SC02_016/ov_SC02_016_jr_801810C8.c:2750`, so the plain `s32 arg0` body is the one to bank now.
- The layout agrees with `func_8012931C(struct vec *)`, which does `unk4 += unk10`, `unk8 += unk14` and
  `unkC += unk18`. This function first does `unk10 += (0x2C)`, `unk14 += (0x30)` and `unk18 += (0x34)`, which reads as
  velocity += acceleration and then position += velocity. So `struct vec` extended with a timer at 0x1C, a sub-object
  at 0x20, a hit box at 0x24 and acceleration at 0x2C is a candidate for the structs phase.

## Copies (same text, name swapped, each `--try` = 0): see `scratch/copies.md`
| function | TU | file |
|---|---|---|
| func_8018003C | src/ov_SC02_016/ov_SC02_016_jr_8017DC70.c | PACK/body.c |
| func_80187CE8 | src/ov_SC02_011/ov_SC02_011_jr_80183178.c | PACK/scratch/copy_func_80187CE8.c |
| func_80182EB0 | src/ov_SC02_017/ov_SC02_017_jr_8017DF34.c | PACK/scratch/copy_func_80182EB0.c |
| func_80181D9C | src/ov_SC03_029/ov_SC03_029_jr_8017FF7C.c | PACK/scratch/copy_func_80181D9C.c |
