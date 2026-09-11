# func_801805EC (ov_SC02_027) — agent e18, P36 T7 S104 — score 0, ZERO levers (1 → 0)

(a) Residual: score 7 (COUNT, 67 vs 68) — after the u16 store `obj->0x14 += a0->0x2A - cam->0x12` the target RELOADS
the global pointer `D_80126B78` (`lui/lw`) before re-reading `cam->0x12` for `a0->0x2A = cam->0x12`; the lever-free body
keeps the first load in a register (`a2`) and reloads only the field. The tree faked the reload with
`__asm__ __volatile__("" ::: "memory")` before the second statement.

(b) Pass and decision (proved on the dumps `scratch/dumps_free`, `dumps_u7`, `dumps_t1`):
- cse.c `note_mem_written` (cse.c:7539-7578): the store `(mem:HI (plus (reg obj) 20))` has a varying PLUS address, so it
  sets only `nonscalar`, not `all` (cse.c:7571-7574); `invalidate_memory` (cse.c:1701-1717) then drops only in-struct or
  varying-address entries. The first `D_80126B78` read is `(mem:SI (symbol_ref))` — scalar, fixed address — so it
  survives, and the second read (same hash key) is replaced by its register.
- The close gives the pre-store read a DIFFERENT KEY: through `s32 **cam = &D_80126B78;` the read is `(mem:SI (reg cam))`
  (the .cse dump shows cse leaves the register address, `find_best_addr` finds no cheaper form), the post-store read
  stays `(mem:SI (symbol_ref D_80126B78))` and is not found → the target's `lui/lw` reload (insn 79 survives cse).
  Byte-proved: `--try` 0. Both reads through `*cam` (u6) re-merge them (score 7) — the reads must stay two spellings.
- The natural original (tested, identical ONLY AFTER LINKING): `D_80126B78` is the field at +0x20 of the struct global at
  `D_80126B58` (cleared as 0x254 bytes by the `_after` TUs, `D_80126B78[0] = &D_800AFAE8`). Every read written
  `((struct Game *)&D_80126B58)->cam` (scratch/parked_struct_global_D_80126B58.c, = g1.c) gives the target's
  instruction stream exactly (COMPONENT_REF → MEM_IN_STRUCT_P, expr.c; the u16 store's `nonscalar` invalidates in-struct
  entries, cse.c:1715); the only diffs are the relocations `lw v0,32(v0)` against D_80126B58 vs `lw v0,0(v0)` against
  D_80126B78 (score 6) — PARKED for the structs phase.

(c) Move: add `s32 **cam = &D_80126B78;` and write the pre-store read as `*(u16 *)((u8 *)*cam + 0x12)`; delete the barrier.
Other plain-C spellings that also score 0 (the same key split): `((struct { u8 *p; } *)&D_80126B78)->p` (t1.c),
`(*(u8 *(*)[1])&D_80126B78)[0]` (u1.c), `u8 **cam = (u8 **)&D_80126B78` (u3/u7.c). REFUSED: `*(s32 **)((u8 *)&D_80126B78 + 0)`
(s2.c, 0 — an identically-zero term, step 6).

HONEST CAVEAT for the coordinator: the body reads the same global two ways (once through `cam`, once directly). It is plain
C with no forcing construct from the refused list, but the asymmetry is what the bytes need; the symmetric reading is the
struct-global text above, which needs the TU's `D_80126B78` accesses to become `D_80126B58` field accesses (structs phase).

(d) GENERATOR PROPOSAL: when the target RELOADS a global pointer (`lui/lw` of the same symbol again) after a store through
a `base + K` address and a `"memory"` barrier sits before the reload, rewrite the read(s) BEFORE the store through a local
pointer to the global (`T **g = &SYM; … *g`) and leave the reads after it direct — cse keys the two loads differently
(cse.c:7571-7574 / :1701-1717); in the structs phase, replace both with the enclosing struct global's field.

(e) Did NOT work: `p = (u16 *)(obj + 0x14); *p = …` (p1–p3, 7: cse folds the store address back to a PLUS before
`note_mem_written`); `((s32 **)&D_80126B78)[0]` (s1/s3, 7: `&D + 0` folds to the bare symbol); the struct/array/`*cam` view on
BOTH field reads (t2 7, u6 7, u2 7; t3/u4 34-36: `&D_80126B78` is kept in a register); body-local `extern s32 *D_80126B78[1];`
(a1: conflicting types with the TU's file-scope `extern s32 *D_80126B78;`).

(f) Method: the brief's hint list (e12 "a derived pointer that cse keeps as a register address", e11 "reload spelled as an
array index") pointed straight at this; the step-3 list has no entry for "a missing RELOAD of a global after a store" —
propose adding cse.c:7571-7574 (a PLUS-address store invalidates only in-struct/varying entries) to it.

(g) Structs: YES — this is the case. A struct type for the global block at `D_80126B58` with the camera pointer at +0x20
(`struct Game { u8 pad[0x20]; u8 *cam; … }`) makes each read a COMPONENT_REF (MEM_IN_STRUCT_P), which is exactly the
flag cse's store invalidation keys on (cse.c:1715); tested with a body-local struct view (g1.c): instruction-identical,
relocation symbol D_80126B58+0x20 instead of D_80126B78 → identical after linking only.

Copies closed with the same text: src/ov_SC03_102/ov_SC03_102_jr_8017BEBC.c func_8018110C (`--try` 0,
scratch/copy_SC03_102_func_8018110C.c, barrier removed).
