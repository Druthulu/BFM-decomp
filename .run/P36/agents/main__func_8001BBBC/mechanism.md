# func_8001BBBC (src/800.c) — e29, P36 S104 — SCORE 6 lever-free (tree: 3 pins + 1 asm launder); not closed

Best body: `body.c` (= scratch/f6.c): plain field stores in the target's order, then the addPrim tail spelled with
EXPLICIT masks on plain `u32` words (`*(u32 *)p = (*(u32 *)p & 0xFF000000) | (ot[1] & 0xFFFFFF); D_800A5E60 = p + 0x14;
ot[1] = (ot[1] & 0xFF000000) | ((u32)p & 0xFFFFFF);`). The pack had no body_free (the lever strip was refused on the
tree's asm line whose comment opens a block comment); the start was the tree minus levers = 46.

(a) Residual (6): the 0xE1000040 draw-mode word takes `v1` (target `t2`) because its store (`sw …,4(p)`) is scheduled
before the `lw 0(p)` tag read (target: after `sh a0,12(p)` / `lui a0,0xff00`, so the constant lives long and local-alloc
gives it t2); and the len-byte `li v0,4` lands after the mask's `ori` (target: between `lui t1,0xff` and `ori`).

(b) Passes: sched1 (sched.c) — the E1 store's placement comes from the priority/LUID order of the ready list
(`scratch/f6_fn.sched`); the `li 4` is a single-set temp, boosted by `birthing_insn_p` (sched.c:2468-2490) so it sinks
below the mask's split pair (the tree header's reading, sched.c:2428 / try_split sched.c:4830). Local-alloc then
assigns by life (qty order), so the E1 register follows the store position.
Proven on bytes: (1) the PsyQ-style bitfield `PTag { addr:24; len:8 }` tail (f1-f5, 36-38) is WORSE than the
plain-mask tail (f6, 6): the bitfield store to `*p` is MEM_IN_STRUCT with a varying address, so sched.c:830-835
(true/output dependence) treats it as independent of the scalar `D_800A5E60` store and lets that store float above the
tag store; the target keeps them in source order (plain word accesses). (2) 48 store orders of x/mode/rgb/y
(scratch/perm/) all score 6-7: the E1 store position is not a source-order effect.

(c) Moves 46 -> 6: drop the four named temps (`tblAddr/tmp/val/m24/mFF/tag0`), write each field store once with its
expression inline (`a0 - 0xA0`, `a1 - 0x78`), `ot = (u32 *)(D_800A6610 + (D_800B9A02 << 14))`, and the explicit-mask tail.

(d) GENERATOR PROPOSAL: for an addPrim tail, try the plain-mask word spelling before a bitfield struct when the global
cursor store must stay AFTER the packet-tag store (a struct store with a varying address is independent of a scalar
store in sched.c true_dependence).

(e)/(f) Not reached: the E1 store placement and the `li 4` interleave (the tree needed a multi-set pinned `tmp` for the
4 and an asm re-tie splitting the mask). Unfinished — stopped at the agent's context budget; next step: read
scratch/f6_fn.sched around the E1 store (insns 22/24 = the split lui/ori pair; boosted at T-16/T-17) and try the E1 word
through a u32 local set once vs twice, and the len byte through a variable reused for the 0x62 code byte (a multi-set
temp without a pin).

(g) Structs: a struct is the WRONG direction for the tail here (measured, f1-f5 vs f6: 36 vs 6) — the aggregate
(MEM_IN_STRUCT) access frees the scalar global store to move, sched.c:830-835. For the field stores (+3..+18) a TILE-like
struct would be neutral (no loads between them).
