# func_8003324C (src/800_b_2.c) — S104 agent e31 — CLOSED at 0, ZERO levers (pin $16 + keepalive -> 0)

## (a) The residual
Score 26 lever-free, COUNT 58 vs 54, frame 40 vs 32: mine keeps TWO loop pointers — the walked `p` (`addiu s2,a0,672`,
the call argument) and an address giv `addiu s0,a0,750` carrying the `0x40`/`0x4E` accesses as `-14(s0)`/`0(s0)` —
plus a fourth callee-saved register ($s3). The target walks ONE register `s0` (`lbu 78(s0)`, `sw zero,64(s0)`,
`move a0,s0`) and recomputes `e + i` (`addu v1,s2,s1`) every iteration.

## (b) The pass and the decision (PROVEN on the `-dL` dumps, scratch/dumps_free vs scratch/dumps_f2)
loop.c strength reduction. Lever-free, the walked `p` is a biv USED DIRECTLY (the call argument): `Cannot eliminate biv
86: biv used in insn 81`, and the two field addresses become givs of that biv, combined and reduced to their own register
(`giv at 71 combined with giv at 74`, `giv at 74 reduced to (reg:SI 98)`; `record_giv` loop.c:4341, `combine_givs`
loop.c:5494) — the extra register and the extra `addiu` per iteration. The tree's `$16` pin hid `p` from loop.c (a hard
register is never a biv), and the keepalive only repaired the allocation the pin broke.
With `p[i]` indexed by the counter, every address (`&p[i]`, `p[i].unk40`, `p[i].unk4E`) is a giv of the ONE biv `i`
(`giv reg 98 src reg 77 … mult 84 add (reg/v:SI 76)`), reduced to ONE register stepped by 84 (the target's `s0`); the
`e + i` giv is `not worth while, 0 vs 21`, which is why the target recomputes it each iteration.

## (c) The moves (PROVEN on bytes)
1. The loop over `Ent30D80 *p = base + 0x2A0` indexed by `i`: `p[i].unk40 = 0; if (p[i].unk4E) func_80030D80(&p[i], 0);`
   (no `p++` step), a plain `for (i = 0; i < 8; i++)`. Pin and keepalive deleted.
2. `(e + i)[0xE]` for the flag byte (the tree's `q = e + i; q[0xE]` also 0): `e[i + 0xE]` gives `addu v1,s1,s2`
   (score 1, operand order).
3. Readability (byte-neutral): `code` inlined into the `switch`. Keep `off` computed BEFORE `base`
   (`e = base + (u16)arg0 * 0x54;` in one line scores 6 — the `lui/addiu` schedules above the `andi`, the tree header's
   point 4 still holds).
Also 0 (scratch/g5.c, not delivered): e16's func_80031B7C shape — the tree's walked `p` as a backward `goto` loop (no
LOOP_BEG note, no loop.c, loop.c:352-361). The structured `for` is preferred.

## (d) GENERATOR PROPOSAL
When a pinned walked pointer `p++` in a counted loop is also passed to a call (a biv used directly) and the lever-free
residual shows a second reduced register `addiu sX,base,K2` beside `addiu sY,base,K1`, rewrite the walk as `p[i]` /
`&p[i]` indexed by the loop counter (all addresses become givs of one biv and combine) — the counted-loop twin of S103
c2's "delete q, index by i"; and write `(e + i)[K]` rather than `e[i + K]` when the target's `addu` has `e` first.

## (e) What did not work (bytes)
- `p = (Ent30D80 *)(base + 0x2A0) + i;` recomputed inside the `if` (a per-iteration pointer variable): 23 (COUNT 55).
- The sweep's best (R7 do-while wrappers): 22; width/param-copy/hoist moves: 26.

## (f) Where the method fell short
It did not: the e16/e23 notes (func_80031B7C goto loop, func_80034844 one-biv `for`) named the class, and both
shapes close this one on the first or second `--try`. BONUS (same TU, not in my list, tried in my scratch only):
func_8003350C (src/800_b_2.c:5830, 2 pins + keepalive) is this function's twin and closes at 0 with the same text
(scratch/twin_350C.c: `off = arg0 * 0x54;`, the `p[i]` loop, `func_80030D80(&p[i], arg1)` — the tree's
`t = arg1 << 16; … t >> 16` is just the call's `s16` conversion).

LEAD (not closed, same TU, not in my list): func_80033398 (src/800_b_2.c:5764, 3 pins incl. a `$0` add) is a loop
over the 8 records that calls an INLINED func_8003324C(i) — its bytes are this function's body with the `(u16)i * 0x54`
index. Declaring `inline void func_8003324C(s32 arg0)` (gcc inlines an `inline` function at -O2 and still emits it;
func_8003324C stays at 0) and writing func_80033398 as the e2 func_800348A8 loop
(`for (i = 0; i < 8; i++, p += 0x2A) if ((p[0] & 0x3F) == 1 && p[2] == lo && ((arg0 >> 16) == 0 || p[3] == (arg0 >> 16)))
func_8003324C(i);`) reaches 25 from the start, and `u16 lo = arg0;` alone removes the `$0`-add pin (the parameter
then dies at the hoisted `srl` in `$a0`, the HImode copy keeps `move s7,a0`). Best 23 (whole-TU text,
scratch/tj_D.c: `e = (u8 *)D_800A46E8 + off`, `p = (Ent30D80 *)((u8 *)D_800A46E8 + 0x2A0)`): the remaining defect is that
the target hoists `D_800A46E8 + 0x2A0` itself to `$s8` (`move s0,s8` as the inner giv's start) and rematerialises
`D_800A46E8` inside the loop, while mine hoists `D_800A46E8` and derives `+672` inside. Scoring needs whole-TU `--try`
(no `--body`), because two definitions change.

## (g) Structs
Partly: the close already uses the TU's `Ent30D80` record type for `p` — what decides it is indexing (`p[i]`) rather
than walking (`p++`), which only a record type of the right size (0x54) lets you spell. A `Slot54`-style type for the
`e` record (flags byte array @0xE, u16 type @0) would re-spell `(e + i)[0xE]` without changing any pass decision.
