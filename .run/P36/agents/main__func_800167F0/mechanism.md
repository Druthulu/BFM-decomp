# func_800167F0 (main, src/800.c) — T7 agent e25 (S104)

**Result: score 0, lever-free** (no pin, no asm, no volatile, no do-while, no goto). Levers 3 -> 0 (the NEEDED `$0` pin,
the NEEDED `$3` pin, the NEEDED `"memory"` barrier). Signature unchanged. **The same text closes the class's other copy
func_80016978** (callee `func_80016224` -> `func_80016450`): `--try` score 0 (`scratch/c3_twin.c`).

```c
s32 func_800167F0(s32 arg0) {
    u16 x = arg0;
    u8 *base = D_800AF630;
    s32 mask = arg0 & 3;
    u32 raw;
    u32 v;
    u32 level;

    if (mask == 0) {
        D_800AF7CE += D_80062BA0[D_800B9A18];
    } else {
        D_800AF7CE += D_80062BA0[mask];
    }
    raw = *(u16 *)(base + 0x19E);
    if (raw >= 0xFF) {
        v = 0xFF;
    } else {
        v = raw;
    }
    level = (x < 4) ? 0xFF - v : v;
    func_80016224(level & 0xFF, 0);
    return *(u16 *)(base + 0x19E) >= 0xFF;
}
```

## (a) Residual
Free body: 12, COUNT 41 vs 49 — the two table reads merged into one (the target keeps one `lui/addu/lbu` per arm + a
`j`/`nop`), the `lhu 414(s0)` hoisted over the `sh D_800AF7CE`, the mask in `v0` instead of `a0`, and the target's
`lhu v0,414(s0); nop; move a0,v0` copy missing (mine loads straight into `a0`). The sweep's best (u16 `x`) = 5.

## (b) Passes and decisions — four independent decisions, one per move
1. **sched1 known-value alias** (e20's func_800168C4 reading, re-used unchanged): `base` is set once to `&D_800AF630`,
   `canon_rtx` substitutes it (`sched.c:371-376`), `memrefs_conflict_p` compares two different constant symbols -> no
   conflict (`sched.c:776-779`), so the `lhu 414(base)` (== `D_800AF7CE`, 0x800AF630 + 0x19E) is hoisted over the store.
   The `+=` written in EACH arm puts the join label between the store and the load; jump2's post-reload cross-jump
   (`jump.c:2371`) re-merges the identical `lhu/addu/sh` tails (the target's `j 4448`). PROVEN on bytes (a1.c: the
   store order is right as soon as the store is per arm).
2. **cse folds a same-width parameter copy** (S103 c4 rule, `cse.c:7440-7474`): with `s32 x = arg0` the parameter
   pseudo and `x` become one pseudo (`.lreg`: register 72 gone, 73 lives 19 insns — `scratch/dumps_s32_s32_0`), so the
   parameter lives to the late `x < 4`, the mask needs a fresh register (`v0`), the zero arm's `D_800B9A18` index lands
   in `v0` too, and jump2's cross-jump merges the two `lui/addu/lbu` index tails (a1.c/a2.c: 43 ins, one `lbu`). With
   `u16 x` the copy is a HImode SUBREG move that survives (`dumps_u16_s32_0`: reg 72 "used 3 times … in block 0"), the
   parameter dies at the mask, the mask takes `a0`, the arms' indices differ (`v0` vs `a0`) and nothing merges.
   PROVEN on bytes: every `s32`/`u32` `x` in the 100-body sweep `scratch/g2/` scores 8-10, every `u16`/`s16` 0-2.
3. **sched1 birthing priority** (`birthing_insn_p` `sched.c:2477-2490`, `adjust_priority` `:2530-2537`): `arg0 &= 3`
   sets the parameter pseudo a second time (`reg_n_sets` 2), so it is not "birthing" while the `la base` (set once) is
   and gets `max_priority` (`dumps_b2/b2.i.sched` block 0: insn 13 at 7f000001, insn 15 at 1) — the `andi` then sits
   before the `la`. A separate `s32 mask = arg0 & 3` births too; the three tied insns fall to the LUID tie-break
   (`rank_for_schedule` `sched.c:2432`, `dumps_u16_s32_0`: "10 13 15 (7f000001), now 15 13 10") = source order, so the
   declaration order `x`, `base`, `mask` is load-bearing (order 1 `base` first = 2). PROVEN (dumps + bytes).
4. **jump1 hoists the else-arm copy; local-alloc refuses the tie** — `if (raw >= 0xFF) v = 0xFF; else v = raw;` is
   rewritten by jump.c's first transform (`jump.c:725-830`) to `v = raw` above the condjump (`dumps_u16_s32_0` `.lreg`
   insn 118, a new uid). `raw` is local (block 3), `v` is set in two blocks (global), so `combine_regs` refuses the tie
   (`local-alloc.c:1773-1774`) and the `move a0,v0` survives. `v = load; if (v >= 0xFF) v = 0xFF;` (c4.c) loads into the
   global pseudo directly = 3. PROVEN on bytes (c4.c 3, c3.c 0); the tie refusal is read from the `.lreg`, not traced.
5. (spelling, not a pass) `level = (x < 4) ? 0xFF - v : v; f(level & 0xFF, 0)` — inlining the ternary into the call
   lets fold turn `(0xFF - v) & 0xFF` into `nor` (c1.c: 5) and an `if (x < 4) v = 0xFF - v;` re-uses `v` (c2.c: 5); the
   comparison must stay unsigned (`s32 raw >= 0xFF` gives `slti`).

## (c) Moves (joint; each alone leaves 2-10)
1. `D_800AF7CE = D_800AF7CE + v1;` after the join -> `D_800AF7CE += D_80062BA0[…];` in each arm (barrier and `$3` pin gone).
2. `s32 x = arg0 + zr;` -> `u16 x = arg0;` (the `$0` pin gone; `(x & 0xFFFFU)` -> `x`).
3. keep `s32 mask = arg0 & 3;` as a separate once-set local, declared after `x` and `base`.
4. `a0 = raw + zr; if (a0 >= 0xFF) a0 = 0xFF;` -> `if (raw >= 0xFF) v = 0xFF; else v = raw;` (the second `$0` pin gone).

## (d) Generator proposal
When a `$0`-pin copy `y = x + zr` feeds a later narrow use (`y & 0xFFFF`), declare `y` at that width (a SUBREG copy cse
cannot fold); when a `$0`-pin copy `a = raw + zr; if (a >= K) a = K;` is followed by the target's `move` after the load,
write it as `if (raw >= K) a = K; else a = raw;` (jump1 hoists the else copy into a global pseudo); and when a store after
an if/else join is followed by a barrier-guarded load through a set-once symbol pointer, sink the store into both arms.

## (e) What did not work
`arg0 &= 3` in place (e20's spelling) with any `x` width = 2 at best (the `andi` above the `la`, move 3). `g1/` (1000
bodies: two declaration orders x five mid-sections x widths): 44 at 2, none at 0 — all with `arg0 &= 3`. Every `s32`/`u32`
`x` = 8-10 (move 2). `c4.c` (no `raw`) = 3; `c1.c` (ternary inlined into the call, signed `raw`) = 5; `c2.c` = 5.

## (f) Where the method fell short
Nothing missing from steps 1-16: the lead (e20's per-arm store), step 3's width rule (S103 c4) and step 12's birthing
rule (d8) were each one move; the enumerator (`scratch/run.sh`, 12-way parallel `--try`) found the joint combination
in 100 compiles once the moves were known. e20's (f) note — "a load through a set-once symbol pointer hoisted over a
store to another symbol = sched1 known-value alias; the fix is a block boundary" — deserves a numbered step.

## (g) Structs
Not for this lever — the deciding alias test is `memrefs_conflict_p`'s two-constant-symbol compare after `canon_rtx`
(`sched.c:776`), which runs regardless of MEM_IN_STRUCT_P (e20's reading, not re-tested here). The struct fact for the
struct phase: `D_800AF7CE` IS `D_800AF630 + 0x19E` (the field `base + 0x19E` this body reads), so a struct type for
`D_800AF630` with a `u16 f_19E` field, and the `D_800AF7CE` global retired into it, is the honest shape — but a store
through `D_800AF630.f_19E` would then ALIAS the load and let sched1 keep the order without the per-arm store; whether
the original wrote the store through the struct is untested (it would change the relocations, `D_800AF7CE` vs
`D_800AF630+0x19E`, so the bytes are identical only after LINKING — not tried).
