# func_801AE82C (md_SC07_004) — P36 S104 agent e27 — score 9 (lever-free; sweep best 5) -> 0, ZERO levers (was 1 `$0` pin + a dead `frame_pad[1]` keepalive)

(a) Residual: 32 vs 33 ins + registers: the target loads the s16 field (`lh v0,12(v1)`), COPIES it (`move a1,v0`), tests the
original (`slti v0,v0,4096`) and adds from the copy (`addiu v0,a1,1024` in the `beqz` slot); lever-free, `w = t + 0` folds, so
there is no copy, and the object pointer moves `$v1 -> $a1`. The tree faked the copy with `w = t + zr` and the 8-byte frame
with `s32 frame_pad[1]; (void)&frame_pad;`.

(b) Pass and decision — the SAME mechanism e8 proved on func_801AB54C (its mechanism.md (b)), re-read on this body's dumps
(`scratch/dumps_final/`):
- The natural compound `if (F < K) { F += ADD; G = F; }` on the s16 field gives the field one HImode load; the test reads its
  sign extension, the `+=` reads `(subreg:SI (reg:HI))`. combine folds the load into the extension (`lh`) and rewrites the
  HImode value as `(set (reg:HI 77) (subreg:HI (reg:SI 78) 0))` (final.i.combine insn 32). Its SET_SRC is a SUBREG, so
  local-alloc's `optimize_reg_copy_1` is never called for it (`local-alloc.c:1004-1006` wants a REG source): the `slt` keeps
  reading 78 (v0) and the add reads 77 (a1) — the target's `move a1,v0`. `G = F` re-reads the field and cse forwards the stored
  value, so both `sh` store the one `v0`.
- Frame: a dead shift temp survives combine as a counted pseudo with no hard register (`.lreg` "Register 79 used 2 times across
  2 insns in block 2; ST_REGS or none", no disposition in `.greg`) -> reload gives it a slot: final.s `.frame $sp,32 # vars= 8`.
  The pad is not needed; WITH it the frame is 8 bytes too big (every `_1` variant scores 4).
Proven on bytes (`--try` 0, 33/33) and on dumps (insn 32, reg 79, the frame line).

(c) Moves (body.c = scratch/g/final.c, score 0):
1. `t = F; w = t + zr; if (t < 0x1000) { t = w + 0x400; F = t; G = t; }` -> `if (F < 0x1000) { F += 0x400; G = F; }` (test the
   memory, compound-assign it) — `t`, `w` and the pin deleted;
2. `frame_pad` and its keepalive deleted;
3. readability: `cnt` deleted (`if (*(s32 *)(a0 + 0x1C) != 0) *(s32 *)(a0 + 0x1C) -= 1;` — the counter test as the sibling
   func_801AE8B0 reads it), the nested else folded into `else if`, `v1` renamed `p`. Enumeration (scratch/g/, 16 bodies:
   cnt/decrement x else-if/nested/`G = F += K`/stores swapped x pad): all 8 pad-free bodies score 0, all 8 padded score 4.

(d) GENERATOR PROPOSAL: e8's rule applies verbatim and should become one: when a `$0` pin makes a copy `w = t + zr` of a value
just loaded from a 16-bit field, the test reads `t` and the stores back to that field read `w + K`, rewrite the group as
`if (FIELD < LIMIT) { FIELD += K; OTHER = FIELD; }` and delete the temps AND any dead `pad[N]` keepalive (let the dump decide
the frame). Two bodies in md_SC07_004 now close with it (func_801AB54C, func_801AE82C).

(e) Did NOT work: the free sweep's best 5 (R12 width t/w -> u16/s16: the copy survives only as a SUBREG move but the pad keeps
the frame wrong and the order differs); every padded variant of the closing text scores 4 (frame +8).

(f) Method gap: none new — e8's (f) already named it: no generator rewrites `v = F; if (v < K) F = v + A` back to
`if (F < K) F += A`, and none deletes a `pad[N]` keepalive together with the temps. Reading the SIBLING'S mechanism.md
(e8's func_801AB54C) closed this on the first batch — worth a METHOD line: "a TU-mate's closed mechanism with the same
residual shape (`lh; move; slti; addiu …,copy,K`) is the first thing to try".

(g) Structs: NO for the lever (combine's HImode subreg copy vs `optimize_reg_copy_1`, not a memory-ordering question).
Readability yes: `a0` as an object (u16 at 0x2, s32 counter at 0x1C, pointer at 0x34 to a sprite with s16 at 0xC/0x10) —
`if (o->sprite->f0C < 0x1000) { o->sprite->f0C += 0x400; o->sprite->f10 = o->sprite->f0C; }` — plausibly byte-identical (a
COMPONENT_REF gives the same HImode MEM), not tested.

(h) Joint check (e27): the three e27 body.c files (func_801AC9CC, func_801AD068, func_801AE82C) spliced into one copy of the tree TU and compiled through the recipe (`md_SC07_004__func_801AC9CC/scratch/joint.py` -> `scratch/joint/joint.o`): `.text` sha1 ad583f4dfb0c and `.rodata` identical to the baseline snapshot, relocations and symbol table identical; the only byte difference is the source-path string in `.strtab`.
