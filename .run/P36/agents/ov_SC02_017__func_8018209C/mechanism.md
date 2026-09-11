# func_8018209C — e9 (P36 T7 S104) — score 29 (sweep best 29) -> 0, ZERO levers — a SIGNATURE change (returns s32)
(was: NEEDED `$7` pin on the matrix pointer `g`, a NEEDED end-of-function `keepalive` of `rv`, and a marked
"gte direct" asm with an extra `memory` clobber)

(a) Residual: COUNT 122 vs 129 + `v0 -> a3` on the matrix pointer. Three defects: (1) the D_800AF648 pointer is in `v0`,
the target loads it into `a3`; (2) every early-exit branch lacks the target's `move v0,zero` in its delay slot and the
final `li v0,1`s are missing — the function RETURNS 0/1 in `v0`, which a `void` definition deletes; (3) the second
`|y| < 0x8D` sign-split test is merged into a conditional negate (-5 insns), exactly func_80181E98's residual.

(b) Pass/decision (bytes + the siblings' dumps; this function is a near-twin of func_80181E98, closed by e7 this session):
  1. `gte_SetRotMatrix(&D_800AF648)` with the address passed DIRECTLY keeps the constant in the asm_operands
     (stmt.c:1556-1569 — a `general_operand` constant is not forced into a register); reload loads it into a spill
     register, `a3` here (the first call-used hard register no allocated pseudo uses — `order_regs_for_reload`, reload1.c:3690-3700; a0-a2 carry func_8012F214's arguments) — the
     target. Through a variable (`g = &D_800AF648`) the operand is a pseudo that local-alloc puts in `v0`; the tree
     pinned it to `$7`. (The inverse holds in func_80182FD0, whose target has `v0`: there a local pointer is right.)
  2. The `v0` stores are return values: with `s32` + `return 0;` / `return 1;` every exit sets `v0`; a `void` body has
     no consumer and they are deleted (the tree's `__asm__("" : : "r"(rv))` kept them alive).
  3. Post-reload cross-jump (toplev.c:3142, `find_cross_jump` jump.c:2371): with a shared `rv = 0; goto out;` the
     sign-split arms end identically and merge; one `if` with a ternary condition and an INLINE `return 0;` puts the
     return block between arm 2 and the pass label (`do_jump` COND_EXPR, expr.c:9124-9150), so cross-jump fails on its
     first comparison (jump.c:2469-2470) — see e7's func_80181E98 mechanism.md for the dump evidence; not re-dumped here.

(c) Moves (e7's func_80181E98 body ported: D_8018E564 -> D_8018E56C, the tail `if (func_80013478(…) <= 0x41010)
func_8002D4C8(0xB67, 0); return 1;`, the tree's `SV_8018209C`/`RES_8018209C` locals kept):
  - the hand-written GTE pair + `g` -> `gte_SetRotMatrix(&D_800AF648); gte_SetTransMatrix(&D_800AF648);`;
  - the goto chain -> structured `if (t >= 0xAB || (res.y >= 0 ? res.y >= 0x83 : -res.y >= 0x83)) { …second
    projection…; if (…) return 0; if (t >= 0x105 || (res.y >= 0 ? res.y >= 0x8D : -res.y >= 0x8D)) return 0; }`,
    with `t = res.x; if (t < 0) t = -t;` for the x axis;
  - `void` -> `s32` with inline `return 0;` / `return 1;`.

  DELIVERED THREE WAYS (all `--try` 0):
  - `body.c` — ZERO levers, bankable WITHOUT a TU edit: `s32 func_8018209C_impl(void *arg0) __asm__("func_8018209C");`
    + the definition under that name — the same declaration alias this TU already uses for func_80181E98 (`TU RECONCILE`
    at ov_SC02_017_jr_8017DF34.c:5207); it sidesteps the file-scope `extern void func_8018209C(void *a0);` (TU:5146).
  - `scratch/body_s32_plain.c` + `scratch/tu_s32.c` — the PARKED signature change proper: `s32 func_8018209C(void *arg0)`
    with TU:5146 changed to `extern s32 func_8018209C(void *a0);` (whole-TU `--try`: func_8018209C 0 and its only
    caller func_80181CF0 0). ov_SC02_017_jr_80186C64.c:2913/2923 carry the same stale `void` extern (another TU, no
    bytes depend on it).
  - `body_minlever_void.c` — the minimum-lever body under the current `void` prototype: 1 marked keepalive
    (`// !FAKE: keepalive — the s32 return value under the TU's void prototype (P36 S104 e9 minimum-lever)`), 3 -> 1.

(d) GENERATOR PROPOSAL: when a function's text is a near-copy of an already-closed sibling in the same TU (here: same
callees func_8012F214/func_80013478/func_8002D4C8, same GTE sequence, only a `D_` table and the tail differ), port the
sibling's closed body first (R27 "port" already does this across TUs; it should also take same-TU twins closed in the
current session); and a `keepalive` of a result variable at the end of a `void` function = an `s32` return.

(e) Did not work / not tried: the sweep's 184 compiles all stayed at 29 (no generator changes the return type or the
goto structure). The `g` variable spelling (body_free) puts the pointer in `v0` — the residual's `v0 -> a3`; only the direct constant gives a3.

(f) Method: METHOD d29 ("a `void` function whose last statement is a keepalive of `v0` RETURNS it") + S104 (d11) and e7's
inline-return finding covered it; the time went into noticing the twin. A same-TU "closed this session" list in the
pack (e7's mechanism.md paths were in my brief) is what made it a two-compile close.

(g) Structs: no. The decisions are asm-operand expansion/reload (the matrix pointer), the return type, and block
layout/cross-jump; `res`/`vin`/`w` are already struct-typed locals.
