# func_801ABEE0 (md_SC07_004) — P36 S104 agent e35 — score 29 (lever-free; sweep best 9) -> 0, ZERO levers (was 2 `$17` pins: `ptr1` and the block-local `inner`)

(a) Residual: REG only (70/70): the object pointer sits in `$s1` (target `$s0`), `ptr1` in `$s0` (target `$s1`), the inner
pointer `*(s32 *)(s2 + 0xCC)` in `$v1` (target `$s1` — the SAME register as `ptr1`), and `v1` in `$a0` (target `$v1`).

(b) Pass and decision (`tools/alloc_table.py free|m1 func_801ABEE0 scratch/`):
- The tree pinned two differently-named locals (`ptr1`, `inner`) to `$17`: METHOD d12 — they are ONE original variable
  the decompiler split (the sibling `func_801A9674` in this TU spells it `s1 = *(void **)((s32)s2 + 0xCC); if (s1 != NULL)`).
- Lever-free, `ptr1` (r74: 4 refs, live 9, block 0, crosses 1 call) is BLOCK-LOCAL, so local-alloc hands it `$s0` before
  global runs (`local-alloc.c:2101-2106`), and the object pointer r73 (global, 19 refs, crosses 5 calls) is left `$s1`;
  `inner` is a separate global allocno (r87, pri 13333) that crosses no call and takes `$v1`.
- Merged, `ptr1` (r74: 8 refs, live 15, "dies in 2 places") is global; `.greg` order `96 73 74 78 83 75`: r73 (pri 16521)
  takes `$s0`, r74 (16000) `$s1` (`allocno_compare`, `global.c:594-610`; `find_reg` `:945-990`). `v1` (r78, 2 bytes) then
  falls to `$v1`. Proven on bytes (`--try` 0, 70/70) and on the two allocation tables.

(c) Moves (body.c = scratch/m1.c): `inner` deleted, `ptr1 = *(s32 *)(s2 + 0xCC); if (ptr1 != 0) {...}` in its place; both
pins deleted. Nothing else changed from body_free.c.

(d) GENERATOR PROPOSAL (d12, third confirmation): two locals pinned to the SAME callee-saved register, the second declared
inside a nested block, are one variable — rename the inner one to the outer and delete its declaration; a merge that makes a
block-local pseudo die in two places moves it from local-alloc's `$s0` grab to global's priority order, which is usually the
target's. The free sweep's R18 "bystander" got to 9 by moving a statement; no generator merges two names.

(e) Did NOT work: nothing else was needed; the sweep's best 9 (R18 bystander, R12 `v1` s32, R4 decl moves) all leave the two
pointers as two pseudos.

(f) Method gap: none — `sites.txt` said both `$17` pins were NEEDED, which is the d12 signature; `related.txt`'s sibling
`func_801A9674` shows the reused-`s1` shape in the same TU. First `--try`.

(g) Structs: NO for the lever — a register-allocation decision over two pointer pseudos. `a0` is an actor (pointers at
0xCC/0xD0 to a sprite and a partner actor, `s16` position at 0x6/0xA/0xE, `s32` counter at 0x1C, `s16` timer at 0x84,
a vector at 0xF0) and the sprite has `s16` at 0x8/0xA/0xC (position) and 0x18/0x1A (scale) — `spr = o->partner->spr;`
would read naturally and give the same pseudos. Not tested (nothing left to close).

(h) Joint check (e35): all four e35 body.c files spliced into one copy of the tree TU with the four `extern void func_801A395C`
turned into `extern s32` (`md_SC07_004__func_801A3594/scratch/joint.py` -> `scratch/joint_tu.c`, object `scratch/joint.o`):
each of the four scores 0 through `--try` (whole-TU), and the object's `.text` (sha1 ad583f4dfb0c), `.rodata`, `.data`/`.sdata`/
`.bss`, relocations and symbol table are identical to the baseline snapshot; the only difference is the source-path string.
Gotcha for the next agent: a splice regex `^[^\n;]*\bfn\([^;{]*\)\s*\{` also matches a CALL line ending in `{`
(`if (func_801A3594(...)) {` at :2061) — anchor the definition at column 0 (`^[A-Za-z_]`).
