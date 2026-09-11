# func_80032A74 (src/800_b_2.c) — S104 agent e31 — CLOSED at 0, ZERO levers (pin $2 + 2 barriers -> 0)

## (a) The residual
Score 11 lever-free, 422 vs 422, three independent defects:
1. (barrier 1) `sw v1,20(s0)` (`ch->unk14 = t32`) sinks below `lui/lbu D_800A4F1E` — the global's load is hoisted over
   the store.
2. (the `$2` pin) the lerp base `addu v1,v1,v0; addiu v1,…; subu a1,a1,v1` where the target has the sum in `$v0`
   (`addu v0,v1,v0`).
3. (barrier 2) `lui/lh D_800A4EF6` hoisted above `ori v0,0x9f; sh zero,12(s1); sh zero,14(s1); sw v0,4(s1)`.

## (b) The passes and the decisions
1+3. sched1 memory dependence, `true_dependence` (sched.c:817-840). A store through a struct field with a varying address
   (`MEM_IN_STRUCT_P` + `rtx_addr_varies_p`, mode not QImode) and a load from a SCALAR global at a fixed address are
   declared independent (sched.c:834-836), so the global's load is free to move above the store. The QImode stores
   (`ch->unk4F`, `ch->unk4E`, `ch->unk52`) are excluded from that exemption (`GET_MODE (mem) != QImode`), which is why
   the hoisted loads stop exactly below them (candidate objdump: `sb s2,82(s0); lui; lh D_800A4EF6; …; sh; sh; sw`).
   The target's order means the stores and the loads DID conflict: either side must lose the struct/scalar pair.
   PROVEN on bytes both ways (below). `MEM_IN_STRUCT_P` comes from a COMPONENT_REF, or for an INDIRECT_REF from
   expr.c:4568-4577 (operand a PLUS_EXPR, or an aggregate type). A cast-wrapped `*(T *)((u8 *)p + K)` has a NOP_EXPR
   (the `(T *)` conversion) as its operand, not a PLUS_EXPR, so it is NOT marked — a plain scalar store that
   conflicts with the global's load (`memrefs_conflict_p` cannot separate `(plus reg K)` from a `symbol_ref`).
   (The flag-level claim is read from expr.c/sched.c and proven on bytes, not traced in the `.sched` dump.)
2. global.c. The tree's `base`, a block-local sum, is tied by local-alloc to its first dying input (the `& 0xFF00` temp
   in `$v1`; `combine_regs` local-alloc.c:1722 — the same decision e23 read in func_800314DC). Writing the sum into `vv`
   (the function's u32 value temp, set 3 more times later) makes it part of a GLOBAL allocno: `.lreg` "Register 86 used
   28 times across 13 insns; dies in 5 places"; `tools/alloc_table.py e1`: r86 priority 86153, FIRST in the `.greg`
   order line, conflicts only `sp`, prefers `v0,v1` -> `$v0` (`allocno_compare` global.c:587-610, `find_reg`).
   Reusing `vol` instead: r96 priority 31372 conflicts `v0,v1` -> not `$v0` (score 3); `h`, `w`, `i2` also 3.

## (c) The moves (all PROVEN on bytes; body.c)
1. `ch->unk14 = t32;` -> `*(s32 *)((u8 *)ch + 0x14) = t32;` (barrier 1 deleted; this alone: 11 -> 6 with move 2).
2. `base = (u18 & 0xFF00) + (s8)u18 * 2; base -= 0x3C00; d -= base;` -> the same with `vv` (pin deleted; 11 -> 8
   alone); the now-unused `s32 base;` deleted.
3. `vo->unk0C = 0; vo->unk0E = 0; vo->unk04 = 0x6009F;` -> the three as `*(u16 *)((u8 *)vo + 0xC) = 0;` etc. (barrier
   2 deleted). Only the `unk04` store cast: 6 (the two `sh zero` then move below the load — they must all conflict).
ALTERNATIVES, also 0 (the likely-original, STRUCTS-phase spellings, scratch/e3.c, scratch/e4.c): keep every store a
field and give the two GLOBALS a struct type instead — `((struct { s16 v; } *)&D_800A4EF6)->v` and
`((struct { u8 v; } *)&D_800A4F1E)->v` (e4, plain C casts), or body-local declarations
`extern struct { s16 v; } D_800A4EF6_s __asm__("D_800A4EF6");` (e3, a declaration alias). A struct-typed load at a fixed
address is `MEM_IN_STRUCT_P` and not varying, so neither exemption clause applies and it conflicts with every store.
A body-local `extern s16 D_800A4EF6[];` is refused ("conflicting types", the TU declares it scalar at file scope).

## (d) GENERATOR PROPOSAL
When a scalar global's `lui/l?` load is hoisted above non-QImode struct-field stores (a zero-byte barrier in the tree
right after the stores), rewrite either the stores as cast byte-offset stores `*(T *)((u8 *)p + K)` or the global's read
through a one-field struct type — every store the target keeps above the load must be rewritten (sched.c:834-836); and
for a sum whose register follows its FIRST operand in mine but its SECOND in the target, assign it into an existing
short-lived multi-set temp of the same width (enumerate the function's temps, keep the one that `alloc_table.py` puts
first with `$v0` free).

## (e) What did not work (bytes)
- Sum destinations: a `u32` copy of the load reused as the sum (e23's func_800314DC shape, `t = u18; t = (t & 0xFF00) +
  …`): 15 (the whole chain mirrors); `gx` 33-37; `qq` 42; `mp` 15; `vol`/`h`/`w`/`i2` 3; the sum in an inner block 11.
- Only `vo->unk04` cast (d2): 6. Body-local array redeclaration: compile error.

## (f) Where the method fell short
The header of this function in the tree (src/800_b_2.c:5145, 5200) already named "sched1 hoisting the D_800A4EF6 `lh`
above the three stores"; METHOD S103 c11 names the channel (aggregate vs scalar in `true_dependence`) for a LOAD; the
QImode exclusion at sched.c:835 was the missing detail that explained why the hoist stopped where it did.

## (g) Structs
YES, and this is the clearest struct case in the TU: both barriers are the struct/scalar alias exemption of
`true_dependence`. Typing the sound-state globals (`D_800A4EF6`, `D_800A4F1E`, and very likely their neighbours
`D_800A4EF0`, `D_800A4EFA`, `D_800A4F19` — one record around `D_800A4EE8`) as fields of a struct makes every such load
`MEM_IN_STRUCT_P` and restores the target's order with the channel/voice stores left as fields (e3/e4 prove it at the
same relocations). The sibling func_8003388C (src/800_b_2.c:6248; its store at :6635, `vo->unk04 = 0x6009F;` + barrier before
`D_800A4EF6 > cmd->unk0C`) carries the identical barrier.
