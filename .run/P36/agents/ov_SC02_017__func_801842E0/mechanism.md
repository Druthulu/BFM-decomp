# func_801842E0 — e13 (P36 T7 S104) — score 34 (sweep best 20) -> 0, ZERO levers (was: NEEDED pins `$3`, `$5` + a NEEDED `launder`)

(a) Residual: 86/86 insns, two defects. (1) A register permutation over the whole function: the main value `t`
(the `D_800B99DA` stamp, then the call result / `D_8018EF84`, then the volume) sits in `a1` instead of `v1` (x25) and the
second variable (`(s16)D_80126B62`, then `D_8018EF84`) in `v1` instead of `a0` (x13). (2) ORDER at the tail: the target
emits `li a0,1509; ori a1,v1,0x1000; andi a1,a1,0xffff; jal`, the lever-free text puts `li a0,1509` after the `ori`.

(b) Pass/decision (dump-verified: `scratch/dumps_b0` (body_free, 34), `dumps_f1` (b0 + move 1, 2), `dumps_f3` (b0 + both, 0);
`tools/alloc_table.py`):
  1. global.c preferences. `t = a0 - t; t -= 0x10000;` sets `t` from `(minus a0 t)` — `set_preference`
     (global.c:1535; for a non-copy the source is `XEXP (src, 0)` = `a0`, a global pseudo, so no hard-register
     preference) — then from `t + K` (itself). The only hard preference `t` (r72) gets is `a1`, from `a1p = t | 0x1000`
     (a1p is local-allocated into `a1`): b0 table "r72 prefers a1" -> `find_reg` gives `a1`. Written as ONE expression
     `t = a0 - t - 0x10000;`, expand makes the inner difference a fresh block-local temp (f1 r89, local-alloc puts it in
     `v1`) and `t = r89 + K` adds the preference `v1`: f1 "r72 prefers v1,a1". `find_reg`'s preference scan runs from hard
     reg 0 upward (global.c:1039-1068), so `v1` (3) wins over `a1` (5). With `t` in `v1` for its whole life, the other
     global (r73, `a0`) now conflicts with `v1` (f1 "r73 conflicts v0,v1") and takes `a0` — both halves of the permutation
     close with this one move (34 -> 2). Same channel as e7's func_801831FC (a second preference from a fresh temp).
  2. sched1's birthing boost. `a1p = t | 0x1000; a1p = (u16)a1p;` sets `a1p` twice (`reg_n_sets == 2`), so the `ori`
     is not a birthing insn (`birthing_insn_p`, sched.c:2469-2490) and gets no `adjust_priority` boost
     (sched.c:2507-2547): f1 `.sched` block 17 `ready list at T-3: 187 (1) 182 (1), now 187 182` — the `li a0,1509`
     (187) takes the later slot. With one set (`a1p = t | 0x1000; func_8002D4C8(0x5E5, (u16)a1p);`, or the value
     inline) the `ori` is birthing: f3 `T-3: 183 (1) 179 (7f000001), now 179 183` — the `ori` goes last, `li a0` first
     = the target. The tree's launder on `a0 = 0x5E5` faked the same reordering.

(c) Moves — the minimum proof (b0 + two edits = `scratch/f3.c`, 0):
  - `t = a0 - t; t -= 0x10000;` -> `t = a0 - t - 0x10000;` (alone: 34 -> 2);
  - the call's `u16` narrowing at the call, not as a second assignment (`a1p = (u16)a1p;` deleted; f4 with only the
    `a0 = 0x5E5` temp removed stays 2, f3 = 0).
  body.c (`scratch/n3.c`, 0) is the readable text built around those two facts: `D_8018EF84` read at each use, the
  `(s16)D_80126B62` in its own `s32 y`, `if (t < 0) t = -t; t = t * 127 / D_8018EF84;` for the hand-expanded
  abs/shift-subtract, `t /= 2` for the hand-rolled `(u32)t >> 31` rounding shift, and
  `func_8002D4C8(0x5E5, (u16)(t | 0x1000));` (the spelling func_801831FC uses for the same call). The nested
  `if (y >= -0x7FF) … else if (y < -0xC00) …` with the duplicated `t = D_8018EF84;` is kept: `||` lets gcc fold the
  two tests into one unsigned range check (n1/A7: 6/10, `addiu 3072; andi 0xffff; sltiu 1025`).
  Ablations from body.c (`scratch/abl/`, all proven on bytes): the split subtraction 33; the hand abs 12;
  `t = t * 127; t = t / D;` 3; the call temps (`a0 = 0x5E5; a1p = …; a1p = (u16)a1p;`) 2; the hand `/2` 1; `||` range 10;
  `s16 y = D_80126B62` 10 (`lhu; sll; sra` — S104 d13's re-extension; `(s16)` into an `s32` gives `lh`). Neutral (0):
  a `lim = D_8018EF84` local, or reusing `y` for it.

(d) GENERATOR PROPOSAL: when a variable is updated by two consecutive statements (`t = a - t; t -= K;`, `t = f(t); t op= K;`)
and the residual is a whole-function register swap of that variable, fold them into one expression (`t = a - t - K;`)
— the inner temp's local-alloc register becomes `t`'s first global preference (global.c:1535, :1039-1068); and when a
call argument is narrowed by a second assignment (`x = e; x = (u16)x; f(…, x)`) with an ORDER residual on the
neighbouring argument's `li`, move the cast into the call (one set -> sched1-birthing, sched.c:2469-2490).

(e) Did not work: n1 (`||` range test) 6; n2/n4 (`s16 y`) 10; every ablation above. The sweep's best (R12 width + R6
inline, 20) touched neither the two-statement update nor the second set of `a1p`.

(f) Method: the allocation table's "prefers" column (b0 `a1` only, f1 `v1,a1`) and the `.sched` ready-list lines gave
both mechanisms in two dumps, but the close came first from writing the natural C (n1 = 6 on the first try) and then
ablating it — a residual of 34 with a clean permutation looked like a priority problem and was a preference problem.
The METHOD rows for "a hand-rolled shift as a real division" (e7 func_801831FC) and "narrow at the call" were the
right ones; neither is needed for the bytes here (f3 keeps the hand shapes), they are readability.

(g) Structs: no. Both decisions are about scalar locals (a global allocno's copy preference; sched1's set count). The
body touches only globals and two `SV3_8012CC88` stack vectors, which are already struct-typed.
