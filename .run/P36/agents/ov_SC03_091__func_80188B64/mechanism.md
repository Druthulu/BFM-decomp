# func_80188B64 (ov_SC03_091_jr_8018326C.c) — P36 S104 agent e36

**Result: score 0, ZERO levers, plain C — a SIGNATURE change (return type `void` → `s32`), so PARKED per S104 (d29).**
Levers 1 → 0 (the NEEDED `launder` on `rv`; the `$2` pin was already REMOVED). 45/45 ins; the WHOLE object is identical to
the baseline snapshot (`objdump -s -r` md5 `12d084b9…` for `scratch/b2.o`; `nm` identical). Second `--try`.

`PACK/body.c` (= `scratch/b2.c`): the tree's body unchanged except `s32` return, the launder → `return rv;`, spelled with
the TU's DEF-SIDE ALIAS idiom (`s32 aF80188B64(s32) __asm__("func_80188B64");`, as `aF8018632C` in the same TU) because the
TU declares `extern void func_80188B64(s32 a0);` twice (TU:6250, :6349) and `--body` cannot edit those. A coordinator may
instead change the two prototypes and define `s32 func_80188B64` directly (d29's bank shape); the bytes are the same either
way (the callers at :6314/:6409 discard the result).

## (a) The residual
COUNT −3 (42 vs 45): the target's `if` path carries `j <epilogue>; move v0,zero` and the else arm `li v0,1` — the function
RETURNS 0/1 in `$v0`. In a `void` function both stores of `rv` are dead and flow deletes them (`insn_dead_p`, `flow.c:1705`,
applied `flow.c:1479-1492`); the launder was keeping `rv` alive to fake the return.

## (b) The pass and the decision
d29's mechanism exactly: `return rv;` → `c_expand_return` (`c-typeck.c:6473`) → `expand_return` (`stmt.c:2590`) →
`expand_value_return` into `$2` + a `USE`, so the constant stores survive. Proven on bytes (score 0, whole object).

## (c) The moves
1. Return type `void` → `s32` (def-side alias to dodge the `extern void` prototypes).
2. The launder → `return rv;`. Keep the if/else with `rv` — the structured `if (…) return 0; …; return 1;` (`scratch/b1.c`)
   scores 4: jump.c re-lays the `return 0` arm as a fall-through `j; move v0,zero` at the END instead of after the test, i.e.
   the original was the if/else-assign shape, not early returns.

## (d) Generator proposal
When a `!FAKE: launder` of a local is the last statement of a `void` function and that local is assigned on every path with
nothing reading it: change the return type to `s32`, replace the launder with `return <local>;` (keep the assignment shape;
do NOT convert to early returns), spell it as a def-side alias when the TU carries `extern void` prototypes, then score.
This is d29's rule with "launder of the result local" added to "keepalive of `v0`" (and e36's func_80185730: "$2 pin +
keepalive of a copied parameter").

## (e) What did not work
- `scratch/b1.c` early-return spelling: 4 (the `move v0,zero` arm lands after the call arm). Byte evidence above.
- All of R2–R43 keep `void` (`history.txt`: every family at 4), so the sweep could never reach it.

## (f) Where the method fell short
Nothing — step 15 (d29). The pack builder should flag "launder/keepalive as last statement of a `void` function" as
"missing return value" and emit the `s32` + `return` candidate itself.

## (g) Structs
Neutral. Nothing in the tail is a memory access; the decision is the return type. `arg0` is an actor (`+0x20` sub-object
with an s16 at `+0x12`, `+0x58` a pointer) and `buf1/buf2` are two 8-byte vectors from `func_8012F14C`; a struct would
read better but changes no pass.

## Copies (`--try` 0)
| function | TU | file |
|---|---|---|
| func_80188B64 | src/ov_SC03_091/ov_SC03_091_jr_8018326C.c | PACK/body.c (whole object identical) |
| func_80187CBC | src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c | scratch/copy_func_80187CBC.c (`D_801A906C` for `D_801AC098`; its TU declares `extern void func_80187CBC(s32 a0);` at :7920) |
