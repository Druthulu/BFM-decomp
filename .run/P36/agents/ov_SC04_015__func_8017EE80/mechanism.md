# func_8017EE80 (ov_SC04_015_jr_8017AE2C.c) — e33, P36 T7 S104 — SCORE 0, ZERO levers (was 1 pin)

(a) Residual (score 23, 106 vs 102 ins): one extra callee-saved register (`$s5`, frame 72 vs 64) and an extra
`addiu s4,s4,8` per iteration: the tree walks TWO pointers (`s3` and `s2 = s3 + 6`, both `+= 8`), and loop strength
reduction kept both as bivs plus a third reduced giv (`s2 = s3 + 4`).

(b) Pass: loop.c strength reduction (S103 c2): a second walked pointer is a second biv that cannot be eliminated;
the target has ONE biv (`s3`) and one combined giv `s3 + 6` (the textually LAST field read, `e[3]`, becomes the base —
`record_giv` prepends, loop.c:4421; `combine_givs` loop.c:5494), with `e[1]`/`e[2]` read at `-4/-2` off it.

(c) Moves (proven, --try 0):
1. delete the second walked pointer: `s2` gone, its reads written off the one pointer (`e + 2`, `e + 4`, `e + 6`) — this
   alone scores 0 on the tree's text (scratch/v/A.c).
2. readability: the `goto next` → a structured `if (i != 0x20) { … }`; the decompiler temps `v0`/`v1` dropped; the
   `s4 = a0` copy deleted; the slot store `*(u16 *)(slot + 8) = e[2]` BEFORE `*(s32 *)(slot + 0x10) = a0` (else score 4:
   the `sw s4,16(s0)` moves into the load delay slot — sched1 tie order, sched.c:2428 LUID).
3. the pointer is `u8 *e` with cast reads `*(u16 *)(e + 2)` — NOT `u16 *e` with `e[1]` (score 2): `e[k]` is an
   INDIRECT_REF of a PLUS_EXPR, marked MEM_IN_STRUCT_P (expr.c:4568-4575); `true/anti_dependence` then call it
   independent of the scalar stack store `*(u32 *)&buf[8] = 0` (fixed address, not in-struct), so sched1 hoists that
   `sw zero,32(sp)` above the `e[2]` load. A cast of a pointer sum is a NOP_EXPR operand → not in-struct → the store
   stays after the load, as in the target.

(d) GENERATOR PROPOSAL: when a pinned/extra callee-saved register is a second pointer initialised `q = p + K` and
stepped with `p`, delete `q` and rewrite every `*(T *)(q + d)` as `*(T *)(p + K + d)` (cast form, keeping the int/u8
base so the reads are not MEM_IN_STRUCT); R-family "walked-pointer merge" (S103 c2) should run BEFORE the pin removal
is judged, and must keep the cast spelling rather than typed-array indexing.

(e) Did not work: typed `u16 *e` / `s16 *e` with `e[k]` (4 → 2 after the store swap); struct type on `e` only (2, the
same MEM_IN_STRUCT channel). The sweep never reached it (every generator stayed at 23: none deletes a walked pointer).

(f) Method: step 3's S103 c2 entry described this exactly; reading it first closed it on the first --try.

(g) STRUCTS — tested on bytes: `struct { s16 x, y, z, last; } *e` ALONE scores 2 (its field reads become in-struct and
the scalar stack store `*(u32 *)&buf[8] = 0` is hoisted over them); giving `buf` a struct type too
(`struct { u16 h[8]; s32 w; } buf;`, `buf.w = 0`, `func_8012C51C(&buf, a0)`) scores 0 again — both sides in-struct →
the conflict test falls back to `memrefs_conflict_p` (sp vs a pseudo = may alias). So structs are right here only if
applied to BOTH the table entry and the call's argument block: body_struct.c holds that 0-scoring struct version.
A struct phase that types one side only will regress this function by one delay-slot move.

Copies in other TUs: none (`grep -rn '= 0x3DB;' src/` → this TU only).
Files: body.c (plain C, 0), body_struct.c (body-local structs, 0), scratch/v/*.c (variants).
