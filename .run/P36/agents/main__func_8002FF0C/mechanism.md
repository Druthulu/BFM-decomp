# func_8002FF0C (src/800_b_2.c) — S104 agent e31 — ZERO-lever close PARKED (identical only after LINKING, body.c, score 6 = relocations only); MINIMUM-LEVER body at 0 (body_minlever.c: 3 levers -> 2 marked do-whiles)

## (a) The residual
Score 27 lever-free (COUNT 162 vs 166), three independent defects, one per tree barrier:
1. (barrier 1, the one e23 met in func_800301C8) in the `v1 != D_80064D4A[…]` arm the target keeps
   `lh; nop; sll; sh -1 -> D_800C532A[t]; sh 0 -> D_800A4644+i; sh 0 -> D_800A4648+i`; mine fills the load-delay `nop`
   with the zero stores and sinks the D_800C532A store to the end.
2. (barrier 2) the target keeps `sw s3 -> D_800A464C+idx24` BEFORE `lbu D_80064D4E[j12]` (a `nop` after the `lbu`);
   mine sinks the store into the load-delay slot.
3. (barrier 3, the `"memory"` clobber) the target RE-READS `D_800A46D2` (`lui a0; lh a0`) for the `func_800419B0`
   argument; mine forwards `r` (`sra a0,v0,16`) — 2 instructions missing.

## (b) The passes and the decisions
1+2. sched1 dependence, `memrefs_conflict_p` (sched.c:614ff). Both addresses of each pair are `(plus reg symbol_ref)`
   with DIFFERENT symbols and different registers: `find_symbolic_term` (sched.c:561) returns each symbol and
   `rtx_equal_for_memref_p` says they differ -> no conflict (sched.c:700-707) -> the scheduler reorders by priority
   (the struct/scalar flags of `true_dependence`, sched.c:834-839, only ever REMOVE a conflict, so no cast or struct
   flag can add one here). A CONST address `(const (plus sym K))` makes `find_symbolic_term` return 0 (CONST is class
   'o') -> conflict -> source order kept. The target was compiled from exactly that: field accesses at nonzero offsets
   into one record array (the D_800A463C/D_800A4640 0x18-byte records). PROVEN on bytes (body.c).
3. cse store-to-load forwarding. The scalar `D_800A46D2 = r` records `(mem:HI (symbol_ref D_800A46D2)) = r`; the
   `*(s16 *)(w + 0xA) = r` store has a PLUS address, so `note_mem_written` (cse.c:7564-7576) invalidates only nonscalar
   memory and the scalar entry survives — the later read is replaced by `r`. PROVEN on the `.cse` dumps
   (scratch/dumps_mlv vs dumps_t3f): a read through a struct-typed pointer is expanded through `memory_address`, which
   forces the constant address into a pseudo when optimising (explow.c, `force_reg` of a CONSTANT_ADDRESS_P address;
   `.rtl` insn 251 `(set (reg 151) (symbol_ref D_800A46D2))`, insn 253 `(mem/s:HI (reg 151))`); cse's table holds the
   store under a different address rtx, so no forwarding, and combine folds the single-use pseudo back into `lui/lh`.
   A struct type on BOTH the store and the read (scratch/v1.c, v4.c) shares the pseudo and prints `la`: 7.

## (c) The moves
- Barrier 3, ZERO levers, pre-link (both bodies): the argument read written
  `func_800419B0(((struct { s16 v; } *)&D_800A46D2)->v)` (scratch/v2.c) — or with a body-local struct declaration
  `extern struct { s16 v; } D_800A46D2_s __asm__("D_800A46D2");` used for the READ only (scratch/v5.c, 0). This is a
  type-punned read of the global; flag it for the coordinator's judgment — it stands in for the STRUCTS-phase field
  access (below), it is not an alias variable.
- Barriers 1+2, ZERO levers, PARKED (body.c, identical only after LINKING; `objdump -dr` diff vs the baseline object:
  only the three relocations `D_800A4640+4/+8/+0xC` vs `D_800A4644/8/C`, scratch/body_link.o):
  `D_800A4640[b].unk04 = 0; D_800A4640[b].unk08 = 0;` (e23's func_800301C8 spelling, TU type `Rsc24`) and
  `*(s32 *)&D_800A4640[b].unk0C = a1;` (Rsc24 types 0x0C as `s16`; the bytes store an `s32` there).
- Barriers 1+2, pre-link (body_minlever.c, score 0): each wrapped in a marked `do { … } while (0);` (a LOOP note in
  mid-block: sched.c:2058-2074 makes the next insn depend on every earlier set/use and flushes the pending memory
  lists). Lever count 3 (2 barriers + 1 memory clobber) -> 2 marked do-whiles (0 once the field spelling may change
  relocations).

## (d) GENERATOR PROPOSAL
When a barrier in the tree separates two memory references whose addresses are both `(plus reg symbol)` with DIFFERENT
per-field `D_` symbols that sit within one record stride of a common base, re-spell the later reference as a field
of the base record (`D_BASE[i].fieldK`, K != 0) and score with relocations normalised — this is not reachable pre-link;
and when a `"memory"` clobber only forces a scalar global to be re-read after a PLUS-address store, read that global
once through a struct-typed pointer (`((struct { T v; } *)&G)->v`) at the re-read site only.

## (e) What did not work (bytes)
- Barrier 3: struct cast on both store and read (v1) 7; `s16 *dst = (s16 *)(w + 0xA); *dst = r;` (v3) 8.
- Barrier 2: the D_800A464C store moved before `D_800A46BC = a1` (w2) 4 — it is then ordered by the scalar store's
  output dependence, but BEFORE it (ORDER); the D_80064D4E load read through a struct cast (w3) 10 (struct flags cannot
  create a conflict).
- Only barrier 1 wrapped (mlv_b) 10; everything lever-free pre-link (free_all) 23.

## (f) Where the method fell short
e23's note named barrier 1 exactly and its struct close transferred on the first try; the new part is that barrier 2 is
the same class (a second pair of different-symbol addresses) and that barrier 3 is a cse forwarding question whose
answer is where expand puts the address (explow.c `memory_address`), not the MEM_IN_STRUCT flag. The byte oracle still
has no relocation-normalised mode; with one this function would bank at zero levers.

## (g) Structs
YES — all three levers are struct questions. The D_800A463C..D_800A4650 per-field symbols are one 0x18-byte record
array (0x00 D_800A463C s32/ptr, 0x04 D_800A4640 s16, 0x06 D_800A4642 s16, 0x08 D_800A4644 s16, 0x0C D_800A4648 s16,
0x10 D_800A464C s32, 0x14 D_800A4650 u8 — the TU's `Rsc24` at D_800A4640 has 0x0C as `s16 unk0C/unk0E`, which the
s32 store contradicts), and D_800A46CC/CE/D0/D2 are fields of the same record block (q - 0x96 = D_800A4638 is how the
target derives D_800A4642 from the D_800A46CE pointer — cse related-value only fires on ONE base symbol, so the original
addressed both through one symbol). Retiring the per-field symbols for field accesses removes both do-whiles (CONST
addresses conflict in `memrefs_conflict_p`) and gives the D_800A46D2 read its natural struct form.
