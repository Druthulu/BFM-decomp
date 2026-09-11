# func_8017F600 (ov_SC06_010_jr_8017A4AC.c) — T7 e26, P36 S104

**Score 0, ZERO levers** (free start 18 = regen best 18). Tree levers: 4 (two `$2` pins on `val`, two `asm("")`
barriers) + 1 unmarked dead `s32 pad_[4]` -> 0. **Same mechanism and same text as func_8017F438** (its pack's
mechanism.md has the full reading: `.run/P36/agents/ov_SC06_010__func_8017F438/mechanism.md`).

The move (both flag-mirror blocks at the end of the function), plus `pad_[4]`, `q`, `uVar1`, `val` deleted:
```
-        q = *(s32 *)(s0 + 0x20);
-        if (*(s32 *)(q + 4) < 0) { u32 val; val = *(u32 *)(p + 4); uVar1 = val | 0x80000000; }
-        else { uVar1 = *(u32 *)(p + 4) & 0x7FFFFFFF; }
-        *(u32 *)(p + 4) = uVar1;
+        if (*(u32 *)(*(s32 *)(s0 + 0x20) + 4) & 0x80000000) {
+            *(u32 *)(p + 4) |= 0x80000000;
+        } else {
+            *(u32 *)(p + 4) &= 0x7FFFFFFF;
+        }
```

## (a) The residual
222/222 instructions; in each `< 0` arm the load took `$v1` and the constant `$v0`; the target has the constant
`lui v1,0x8000` in the `bgez` delay slot and the load in `$v0`.

## (b) The pass and the decision (proven on bytes; dumps taken on func_8017F438, the same block text)
With the mask test the constant is loaded BEFORE the branch (the AND's operand), cse hands the arm's `|=` the same
pseudo, combine turns the `(eq (and x 0x80000000) 0)` test into `bgez` but keeps the constant (still used in the arm),
and reorg's `fill_simple_delay_slots` puts it in the slot from before the branch (reorg.c:2799ff.); the arm keeps one
quantity (the load) -> `$v0`. combine's `(use)` of the deleted AND result (combine.c:10831-10845) gets a stack slot in
reload: the 16 frame bytes the dead `pad_[4]` was faking (with the pad: frame 72 vs 56, score 10 — scratch/v_pad.c).

## (c) The moves
- `if (*(u32 *)(*(s32 *)(s0 + 0x20) + 4) & 0x80000000)` for both tests; delete `pad_[4]`.
- Readability (0 as well): `|=` / `&=` on the field; `q`, `uVar1`, `val` deleted.

## (d) GENERATOR PROPOSAL
R-bittest-mask (see func_8017F438): a sign test followed by a set/clear of bit 31 in the same if -> test with the mask
`& 0x80000000`; also emit the variant without a dead `pad[N]`.

## (e) What did not work
- body_free: 18; every R2–R38 family: 18 (history.txt). The bit test with the pad kept: 10 (frame only).

## (f) Where the method fell short
Same as func_8017F438 — the delay-slot `lui` is invisible in the residual's hunk; the whole objdump shows it.

## (g) Structs
No — the condition's spelling decides it (see func_8017F438 (g)). `nv[4]` is the VECTOR-like normal buffer for
`VectorNormalSS`; typing it as an SVECTOR would not touch the flag-mirror blocks.
