# func_8018574C — e32 (P36 S104) — CLOSED at 0, zero levers

`body.c` (= `scratch/h1.c` + a comment): `--try` score 0 (49/49). Levers before: 2 (`s0` pin `$16`, a 2-input launder
`__asm__("" : "=r"(t) : "0"(t), "r"(base))` that the lever strip refused). After: 0.
The pack held only `residual.txt` (UNSTRIPPABLE); I wrote the lever-free text by hand (`scratch/free0.c`, pin → plain
`s32 s0 = (s32)a0;`, launder deleted): score 3.

(a) Residual (3): `lhu v1,12(s0); sll v1,v1,16; sra v1,v1,23` vs the target's `lh v1,12(s0); sra v1,v1,7`. The `$s0`
pin was not needed at all (the entity copy lands in `$s0` unpinned; the later `addiu s0,sp,24` for `aux` is the
allocator reusing `$s0`, not a source variable).

(b) Pass: combine merges the `lh`'s sign extension with the following `>> 7` (`(ashiftrt (sign_extend (mem:HI)) 7)` →
`lhu` + `ashift 16` + `ashiftrt 23`). Casting ONE operand at the shift, `(s16)t >> 7`, is the S104 d13 idiom
(`c-typeck.c:2418-2450` short_shift re-extends; cse folds that pair into the load, `cse.c:5577-5667`) — cited from d13,
PROVEN here on bytes only (I did not re-read the combine/cse dumps). The launder's second input (`"r"(base)`, meant to
force the 0x34 load into the `lh` delay slot) is also unnecessary: the scheduler fills the slot by itself once the
shift is two instructions.

(c) Move: `rem = rnd % (t >> 7);` → `rem = rnd % ((s16)t >> 7);`. Plus the lever-free declarations.
`s16 t` (h2), `*(s16 *)(s0 + 0xC) >> 7` inline (h3), loads swapped (h4), `t = … >> 7` at the load (h5): all 3.

(d) GENERATOR PROPOSAL: when the residual is `lhu; sll 16; sra 16+k` against the target's `lh; sra k` and the source
reads `x >> k` of a local loaded from `*(s16 *)`, rewrite the shift as `(s16)x >> k` (and delete any launder whose only
job was to break the lh→sra combine) — d13's rule, which should run on UNSTRIPPABLE-launder bodies too.

(e) Also closed with the SAME move, same TU: `func_80184CA8` (`src/ov_SC03_105/ov_SC03_105_jr_80181C84.c:4826`, 115/115,
its only lever the identical 2-input launder at :4880) → `scratch/cca8_final.c` (score 0, launder deleted, its
two-lever comment replaced by a note on the cast). Listed in `scratch/OTHER_FUNCTIONS.txt`.

(f) Method: the strip refusal (a lever line whose asm takes 2 inputs) left no `body_free.c`, so the free sweep never saw
this body; the fix was a one-token d13 move. A stripper that deletes a whole `__asm__("" : …);` statement regardless of
its operand count would have handed the sweep a 3-off body.

(g) Structs: no — a load width/extension question; a struct field `s16 f0C` read would give the same `lh` and the same
combine merge (the cast at the shift is what matters).
