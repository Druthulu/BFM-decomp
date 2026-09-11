# func_80183E20 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e11)

**Result: score 0 in plain C, on the first `--try`.** No pin, no asm, no added volatile. Levers go from 1 to 0 (the
`__asm__("":::"memory")` barrier at tree line 7408). Signature unchanged. No other copy of the class in `src/` (grep of
`a0 + 0x60) = 0;` with a 0x76/0xFF7F neighbour finds only this one).

## (a) The residual in one sentence
Same count (34/34). The target RELOADS the field it has just stored (`sh v0,118(a0); lh v1,118(a0)`). Mine has
`sll v0,v0,16` instead: cse forwarded the stored value into the `(s16)` test, so no load is left.

## (b) The pass and the decision (proven on bytes)
The original stored the global flag BEFORE it read the field back. Two passes are involved:
- **cse forgets the field at the scalar store.** A store to the fixed address `D_801EFD40` goes through
  `note_mem_written` (`cse.c:7539-7578`). Its address does not vary, so it only sets `writes.var`.
  `invalidate_memory` (`cse.c:1701-1720`) then removes every in-memory table entry whose address DOES vary
  (`cse_rtx_addr_varies_p`, `cse.c:2474`). `a0+0x76` varies, so its entry is removed. The load after the flag
  store now finds nothing to forward, and the `lh` survives.
- **sched1 hoists the load back above the flag store.** `true_dependence` (`sched.c:817-839`) drops the
  store→load dependence when the load is `MEM_IN_STRUCT_P` with a varying address and the store is a scalar with a
  fixed address (the second `! (...)` clause). expand_expr sets `MEM_IN_STRUCT_P` on an INDIRECT_REF whose operand
  is a PLUS_EXPR (`expr.c:4569-4577`). `((s16 *)a0)[0x3B]` gives exactly that. `*(s16 *)((u8 *)a0 + 0x76)` is a
  NOP_EXPR around the PLUS, so it is not marked, and the load stays below the store.

## (c) The move that closed it
```c
        *(u16 *)((u8 *)a0 + 0x76) = v0 - v1;
        D_801EFD40 = flags & 0xFF7F;          /* flag store moved BEFORE the reload */
        if (((s16 *)a0)[0x3B] < 0) {          /* array-indexed reload: in-struct MEM */
            *(u16 *)((u8 *)a0 + 0x76) = 0;
        }
```
The `v1b` temp is gone, and so is the `v0 = v0 - v1;` self-update (it is now stored directly). Both moves are needed:
- cast-style reload after the flag store (`scratch/v_cast.c`): score 5, 35 ins. The `lh` is kept but sched cannot
  lift it above `sh D_801EFD40`.
- indexed reload read into a temp BEFORE the flag store (`scratch/v_before.c`): score 5. This is the free body's
  residual exactly: cse forwards.

## (d) Generator proposal
When the target has `sw/sh X,K(rA); l[hw] rB,K(rA)` (a store immediately reloaded) and mine forwards the value
(a missing load, often an extra `sll`/`sra` or `move`), look for a later store to a GLOBAL scalar in the same block.
Move that store textually between the field store and the field read, and respell the read as an array index
`((T *)p)[K/sizeof(T)]` (or a struct field). This replaces the `"memory"` barrier lever.

## (e) What did NOT work
Recorded under (c). The sweep's best was 2 (R7 do-while + R9 swap). Neither move reaches this, because no generator
changes a cast deref into an index expression.

## (f) Where the method fell short
Nothing blocked. What found it was the S103 c11 note in METHOD step 3 ("`p[i]` is an aggregate access that
`true_dependence` treats as independent of a scalar store; a cast-wrapped byte-offset read is not marked") plus
reading the target order (`lh` BEFORE the flag's `andi`/`sh`). No dumps were needed.

## (g) Structs question
Yes, and here it is the whole answer. A struct type for `a0` (`struct { … u16 f60 @0x60; … s16 f76 @0x76; }`, with
`a0->f76` as a COMPONENT_REF) makes the reload an in-struct MEM: the COMPONENT_REF case sets `MEM_IN_STRUCT_P`
(`expr.c:4873/4888`). The array index sets the same flag through `expr.c:4569`, so it is the same channel. Not tested with a struct declaration. The array index already proves the channel
on bytes, and a struct field would take the same `true_dependence` clause.

Files: `body.c` (score 0), `scratch/v_cast.c`, `scratch/v_before.c` (both score 5, the two halves of the proof).
