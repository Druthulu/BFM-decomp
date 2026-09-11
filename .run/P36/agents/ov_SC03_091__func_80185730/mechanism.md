# func_80185730 (ov_SC03_091_jr_8018326C.c) — P36 S104 agent e36

**Result: score 0, ZERO levers, plain C — but it needs a SIGNATURE change (return type), so: PARKED per S104 (d29).**
Levers 2 → 0 (the `$2` pin and the end-of-function keepalive, both NEEDED). 52/52 ins. The WHOLE object is identical to the
baseline snapshot (`objdump -s -r` md5 `12d084b9…` both for `scratch/s1.o` and `scratch/s2.o`; `nm` identical).

The function RETURNS its first argument (the out-buffer pointer) in `$v0`. The tree declared it `void`, so a `$2`-pinned
`dst = a0` plus a keepalive faked `return a0;`. Two byte-proven spellings, both 0, both done with the TU's existing
DEF-SIDE ALIAS idiom (§37/§124, the same one `aF8018632C` uses 500 lines below) so that the three file-scope/body-local
`extern void func_80185730();` K&R prototypes (TU:3699, :3769, :3838) and their callers stay untouched:

- `PACK/body.c` (= `scratch/s2.c`): `s32 *aF80185730(s32 *a0, s32 a1, s32 a2) __asm__("func_80185730");` — the body is
  `body_free.c` with `dst` deleted and the tail `*a0 = sp20; return a0;`. Parameter list unchanged.
- `scratch/s1.c`: a small struct returned BY VALUE — `struct R4 { s32 w; }; struct R4 aF80185730(s32 a1, s32 a2)`,
  `struct R4 sp20;` and `return sp20;`. With gcc's pcc struct return the caller passes the result address in `$a0` and the
  callee returns it in `$v0` (`function.c` expand_function_end), which is byte-for-byte the same function. This reading
  explains WHY the callers pass a buffer first and never read `$v0`; which one the original was cannot be told from this
  function's bytes (the callers are the same either way).

## (a) The residual
Same 52 ins; the tail. Mine `lw v0,32(sp); nop; sw v0,0(s3)`, target `lw v1,32(sp); move v0,s3; sw v1,0(v0)`: the target
copies `a0` into `$v0` and stores THROUGH `$v0`. In a `void` function nothing is live in `$v0` at the exit, so the copy is dead.

## (b) The pass and the decision (read in `scratch/dumps_s2/s2.i.{rtl,sched,lreg,greg}`; free body in `scratch/dumps_free/`)
1. `return a0;` expands to `(set (reg/i:SI 2) (reg/v:SI 72))` + `(use (reg 2))` (insns 123/124, `.rtl`) — `$v0` live to the end.
2. sched1 (`.sched`) puts insn 123 ABOVE the store 120: the store waits on the `lw` 118 (load latency), the copy is ready at
   once (`rank_for_schedule`, sched.c). Order becomes `lw; $v0 = a0; sw`.
3. local-alloc's `update_equiv_regs` calls `optimize_reg_copy_1` (`local-alloc.c:1003-1007` → `:700-760`) for the copy
   `$v0 = r72` whose source does not die there: r72 dies in the very next insn (the store), so its use is replaced by the
   DESTINATION — `(set (mem:SI (reg/i:SI 2)) (reg 96))` in `.lreg`. MIPS has no SMALL_REGISTER_CLASSES (`local-alloc.c:710`),
   so the hard-reg destination is accepted. That is exactly the target's `move v0,s3; sw v1,0(v0)`.
The pin + keepalive reproduced step 1 by hand. All three steps are read in the dumps; the close is proven on bytes.

## (c) The moves
1. Return type `void` → `s32 *` (or the struct-by-value return), via a def-side alias `aF80185730 __asm__("func_80185730")`.
2. `dst = (s32)a0; *(s32 *)dst = sp20; asm keepalive` → `*a0 = sp20; return a0;` (delete `dst` and its pin).

## (d) Generator proposal
When a `void` function ends `register … x __asm__("$2"); x = <param or value>; …; __asm__ volatile("" : : "r"(x));`, the
function returns x: emit `return x;` with the return type widened, and — when the TU carries a conflicting `extern void`
prototype for it — spell the definition with the def-side alias (`T aF<addr>(…) __asm__("func_<addr>");`) so `--body`
scores it without any prototype edit; for a `$2` = first-parameter return also try the struct-by-value spelling (drop
`a0`, return the struct). This is d29's keepalive rule generalised from "last statement is `asm "r"(v0)`" to "a `$2` pin +
a keepalive of it".

## (e) What did not work / notes
- The sweep's best (R12 `dst` → u16, score 1) was a width accident, not the mechanism.
- The SIBLING family `func_80180200` (ov_SC03_099, 10 members; no `func_801858AC` call, `rv = sp20; *a0 = rv; rv = a0;`)
  does NOT close with either spelling: `scratch/sib_a.c` (struct) and `sib_b.c` (`s32 *`) both score 4 — its target stores
  through `s0` and copies `move v0,s0` AFTER the store (`lw v0; nop; sw v0,0(s0); … move v0,s0`), the shape a plain return
  gives here. Its tree comment (4) records that the unpinned return gives this function's shape. Not pursued (other class).

## (f) Where the method fell short
Nothing; d29's rule (step 15) pointed straight at it. The pack builder's `body_free.c` stripped the pin and the keepalive
but kept `void`, so every generator family scored the dead-store shape. A pin on `$2` + a keepalive at the end is the
second spelling of "this function returns a value" (d29 met the first: a keepalive of an assigned `v0`).

## (g) Structs
Here the struct question has a concrete answer: the struct-by-value spelling (`scratch/s1.c`) closes at 0 and would explain
the hidden-pointer calling convention (callers pass a buffer first and ignore `$v0`). It does not change any pass decision
against the `s32 *` spelling (same RTL tail), so it is a naming/type choice for the STRUCTS phase, not a byte lever. The
field records: `a1` is an actor (`+0x4` position record passed to `func_8012B77C`, `+0x88` s16[3] home position,
`+0xDC` s32 flag, `+0x100` s16), `sp10` is a 16-byte record with s16 fields at +2/+6/+0xA (func_8012B77C's "to"),
`D_80126CBA - 6` = `D_80126CB4` is a global s16[3] position.

## Copies (same class; each `--try` 0 with this text, callee and names swapped)
| function | TU | file (`s32 *` return) | struct-return file |
|---|---|---|---|
| func_80185730 | src/ov_SC03_091/ov_SC03_091_jr_8018326C.c | PACK/body.c | scratch/s1.c |
| func_80184BAC | src/ov_SC03_089/ov_SC03_089_jr_8017CA80.c | scratch/copyp_func_80184BAC.c | scratch/copy_func_80184BAC.c |
| func_80184888 | src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c | scratch/copyp_func_80184888.c | scratch/copy_func_80184888.c |
| func_8018271C | src/ov_SC03_104/ov_SC03_104_jr_80182038.c | scratch/copyp_func_8018271C.c | scratch/copy_func_8018271C.c |
The copies carry body-local `extern`s for their callee, `D_80126CBA` and `func_8012B77C` (compatible with any file-scope ones).
Only this TU's copy was checked whole-object.
