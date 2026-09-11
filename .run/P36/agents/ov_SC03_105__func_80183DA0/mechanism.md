# func_80183DA0 — e32 (P36 S104) — CLOSED at 0, zero levers

Final body: `body.c` (= `scratch/f4.c`). `--try` score 0 (82/82 ins).

(a) Residual: lever-free start scored 23 — `lvl` (the pan level, `li s1,7` / `move s1,v0` / `sll a1,s1,8`) sat in a
call-clobbered register (no `s1` save, frame 40 not 48), and the clamp tests read the level through `lvl` itself
instead of the pre-copy sum (`addu v0,s1,v0; move s1,v0; sll v0,v0,16`).

(b) Passes:
- `lvl` in `$s1`: the target's level lives ACROSS the `func_8012EFB8` call — i.e. `lvl = 7` is written BEFORE the call
  (next to `val = 0x7F`); sched1 then sinks the `li` below the call (it has no consumer in the block) and reorg puts
  it in the `bltz` delay slot, so its position in the bytes is the same as in a post-call spelling. flow counts the call
  crossing before sched1 runs → callee-saved (`global.c` `find_reg` skips call-used regs for a call-crossing allocno).
  PROVEN on bytes (23 → 4).
- the copy `move s1,v0`: with an `s32` level, `n = lvl + q; lvl = n; if ((s16)n …)` makes cse put `lvl` at the head of
  the quantity (it lives longer and beyond the block, `cse.c:846-862`) so the tests read `lvl` and combine folds the sum
  into `lvl` (no copy). Declaring the level **`s16`** makes the `+=` a HImode store: expand computes the SImode sum in a
  temp and stores its low part into the HImode pseudo — a SUBREG move that survives (S103 c4, `cse.c:7440-7474` folds only
  same-mode REG copies), and the `< 0` / `>= 0x10` tests extend from the temp. PROVEN (4 → 2).
- the last 2: `(lvl << 8)` on an `s16` promotes and sign-extends (`sll 16; sra 8`). Spelling the packing as ONE
  `(u16)( … )` cast over the whole argument lets `convert_to_integer` (c-convert/convert.c) push the truncation through
  the IOR and the constant left shift, so `(u16)lvl << 8` needs no extension — the `& 0xFFFF` spelling does not narrow
  (BIT_AND is not distributed). This is the fleet's own packing idiom (`func_8002D4C8(a1, (u16)(vol | ((pan << 8) |
  0x3000)))` in ov_SC04_005 / ov_SC06_032). PROVEN (2 → 0). `(u16)(val | (lvl << 8) | 0x3000)` without the inner
  parentheses is ORDER 2 (the `ori` moves: fold associates the constant differently); `(u16)((lvl<<8)|0x3000|val)` is 1
  (`or` operands swapped).

(c) Moves (each proven on bytes):
1. `lvl = 7;` moved above the call (beside `val = 0x7F`). 23 → 4.
2. `s32 lvl` → `s16 lvl`; `n = lvl + t / 0x14; lvl = n; if ((s16)n …)` → `lvl += out.vx / 0x14; if (lvl < 0) … else if
   (lvl >= 0x10)`. 4 → 2.
3. `r = (lvl << 8) | 0x3000; func_8002D4C8(0x730, (val | r) & 0xFFFF);` →
   `func_8002D4C8(0x730, (u16)(val | ((lvl << 8) | 0x3000)));`. 2 → 0.
4. Readability (holds 0): the goto chain (`goto tail` / `goto zero`) → one structured test with a ternary per sign
   (S104 d11): `if (out.vx >= 0 ? out.vx < 0x140 : -out.vx < 0x140) { sv = (s16)val; … } else { val = 0; }`.
   Dropped the dead `n`, `t`, `r`.
   `sv = (s16)val;` must stay BEFORE the inner `if` (it is the `sll v0,s0,16` reorg copies into both test delay slots);
   `s16 val` instead of the cast is 21 (s0/s1 swap), `val = (s16)val - …` inside each arm is 18.
   The inverted spelling (`if (… >= 0x140) val = 0; else {…}`) is 14 (block order flips).

(d) GENERATOR PROPOSAL: when a `lvl = K;` constant initialiser sits right AFTER a call and the residual shows that
local in a call-clobbered reg where the target uses a fresh `$sN` (+1 saved reg, +8 frame), move the initialiser above
the call; and when the residual shows a missing `move sK,vN` between a sum and its `(s16)` test, retype the summed local
`s16` (and rewrite `n = lvl + q; lvl = n; (s16)n` as `lvl += q; lvl`), then fold any `(X | (lvl << K) | C) & 0xFFFF`
packing into one `(u16)(X | ((lvl << K) | C))` cast.

(e) Did not work: `lvl = n = …` (4), a separate `sv = (s16)n` before the copy (8), `else lvl = n` arm (6), `s16`/`u16`
on `n` only (15/16 with the old spelling); `((u16)lvl << 8)` (2), `(u16)(lvl << 8)` + `& 0xFFFF` (1, double andi).

(f) Method: the levers (pin `$17` + a launder on `n`) each faked ONE of these two facts (call crossing, a surviving
subreg copy); no generator moves an initialiser across a call or retypes a local AND rewrites its uses jointly.

(g) Structs: no. `pos`/`out` are already a struct type (SVec_80183DA0); the levers were about a local's WIDTH and
its position relative to the call, not about memory accesses.

Other copies: none found (grep of `0x7F / 0x140`, `lvl = 7;`, `-out.vx >= 0x140` over src/). The ov_SC05_003 /
ov_SC05_005 `func_80181CDC` / `func_80181DE4` share the `lvl`/`0x3000` tail (`lvl = n + zr` with a `$0` pin) — a
different body (`/ 0x19`, `> 0xF`), not tried here (outside my TU).
