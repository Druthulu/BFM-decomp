---
ts: 2026-11-06T02:55:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_k0agWyBarliKRn6SckmI
---
Initial RTL: insn 181 loads unk1C into pseudo 136. cse1 forwards it (replaces 136 with 135). The barrier insn between 178 and 181 prevented cse from forwarding.

So we need cse1 to not forward the store into the load. cse1's forwarding: after insn 178 (store to mem 28), it records the memory location's value (135). Then insn 181 loads mem 28 → cse replaces with 135.

To break: make the load's address not equal to the store's address in cse's view, or invalidate the memory entry with an intervening store.

Idea: insert a store to another memory location between them that cse can't prove doesn't alias. cse invalidates memory entries on a store if the addresses might alias (write_dependence_p). If we insert a store to an address cse can't distinguish, the memory entry is invalidated → the load is kept. The extra store must then be removed or emit no bytes.

What if the extra store is to a *local variable* (stack)? cse would see the store to (plus sp K); does that invalidate the unk1C entry? `write_dependence_p` for two MEMs with different bases (sp vs s1) → `fixed_scalar_and_varying_struct_p` etc. If the local is a scalar and the other is a struct member, cse may consider them non-aliasing (fixed scalar vs struct). Hmm.

What if the extra store is to a *global* symbol (fixed address)? A store to D_800AF7BE (a u16 global) between them: cse's memory entry for unk1C (a varying struct member) vs a fixed global store — the classic `fixed_scalar_and_varying_struct_p` says a varying struct access may alias anything, so the store would invalidate the entry → reload! And the extra store emits an instruction (sh) — but if it's a *dead* store, flow might delete it before codegen? flow's dead-store elimination for memory: gcc 2.7.2's flow.c does delete dead stores to *pseudos*, not memory (no DSE for memory in 2.7.2? Actually flow.c has "dead store elimination" only for registers). So the store would remain → extra instruction. ✗

Unless the store is to a local variable that flow deletes. Let me test: insert `flag = 0;` between the two statements (flag is a local s32, dead after the condition). The store to flag is to the stack; flow would delete a dead store to a local (flow.c does eliminate dead stores to pseudo registers, and a stack slot store is a memory store, not a pseudo). Hmm, a local variable's address is taken? flag is used via `gte_stflg(&flag)` so its address is taken → it's a memory location, not a pseudo. A dead store to it might not be eliminated.

What about a local variable whose address is NOT taken: e.g., a new `s32 d;` local never used → the store `d = 0;` would be to a stack slot (memory) — dead but not eliminated (no memory DSE). Hmm. Unless the local is in a register (optimized away entirely): `s32 d = 0;` unused → the front end/flow deletes the assignment entirely (no RTL). If we make it `d = something;` where d is unused, the compiler deletes it as dead code before cse. So no effect.

The C0414 dead-reset works for *register* equivalences (p = expr; ...; p = 0). For memory, we'd need a store that cse sees but codegen removes. 

Hmm, what about a store to a *global* whose value is a constant and the global is later read... no.

Alternative: make the load's address expression different but codegen the same, and cse can't equate. Earlier h1-h7 failed because the address rtx simplified to the same. What if we use an *index variable* that cse can't fold to a constant? E.g.:
```
s32 idx = 0;   // in a register
...
*(s32*)(arg0 + 0x1C + idx) -= 1;
```
cse might know idx = 0 (constant propagation) and fold. If idx is loaded from a global that cse can't know... that changes code.

What about making the store go through one base and the load through another register that is known equal only after register allocation? cse would see two different pseudos: e.g., `u8 *p = arg0;` then store via `((Unk*)arg0)->unk1C` and load via `((Unk*)p)->unk1C`. cse's copy propagation: does cse 2.7.2 propagate register copies? cse.c does record REG_EQUAL/REG_EQUIV and can substitute; a simple copy `p = arg0` creates a SET and cse may treat p as equivalent to arg0 for the address? cse handles arithmetic expressions; two MEM addresses (reg p) and (reg arg0) — cse's memory entry is keyed by the address expression; after copy propagation p→arg0, the addresses match. gcc cse does "record_jump_equiv" and "cse_insn" with `reg_eqv_table`? I think cse 2.7.2 does propagate REG_EQUAL values (constants/expressions) but not arbitrary register copies? Actually cse's `cse_insn` uses `struct table_elt` and for a SET of a pseudo to another pseudo, it records the source as the "equivalent" of the dest, and later uses of the dest can be replaced by the source. So p would be replaced by arg0 → same address.

Hmm, h3/h4 tried pointers; still forwarded.

What if we use a `volatile`-free trick: make the load happen through a *different* MEM mode that codegen emits as lw: e.g., load via an `s32` from a `u32` lvalue — same mode SI.

What about the target's actual source: maybe the original code was:
```
((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC;
func_801820E4(arg0);   // no
```
No.

Wait — maybe the original source had the two statements in different *cases* of the switch or after a label that is a branch target, so cse's EBB was split. Let me look at the target: the store at 209c and the load at 20a0 are adjacent. cse works on EBBs: the label at 2094 is a branch target (beq v1,v0,2094), so the EBB starts at 2094. Both statements are in that EBB → forwarding possible.

But hold on: in the target, is there a label between 209c and 20a0? No (adjacent instructions).

So how did the original avoid forwarding?! Unless the original's store and load were NOT the same address from cse's view. E.g., the original might have used a *different struct type* for one of them, giving a different MEM alias but the same offset. cse's forwarding requires `rtx_equal_p` of the addresses (or true_dependence). Two MEMs `(mem/s:SI (plus (reg) 28))` and `(mem/s:SI (plus (reg) 28))` are equal. If one is `(mem:SI (plus (reg) 28))` (not in-struct), the rtx differs only in the in_struct flag — cse's `exp_equiv_p`/`rtx_equal_p` ignores flags? `rtx_equal_p` compares the code, mode, and operands; the in_struct flag is not compared (it's a bit in the rtx header). So equal.

What if the modes differ: store SI, load SI. Same.

Hmm, what if the original's reload was forced by a *register pressure* effect? No.

What if the original's store and load were separated by a `goto` label that is a branch target — e.g., the `while` loop's exit label. Look at the target: 2064 lh v1,6(s0) ... loop; 2094 is the loop exit label. The store is at 209c AFTER the label. Hmm.

What if in the original, the store `unk1C = unkDC` was BEFORE the loop and the load after? Target order says store at 209c, after the loop. So no.

Let me reconsider: maybe cse's forwarding in our build happens in cse1 because of a *different* pass order: the barrier is an insn; without it, cse1 forwards. In the original, the same C would also forward... unless the original's RTL had the two statements in different EBBs because of a label. Since the target's asm has them adjacent, the label would have to be removed by jump2 before final but present during cse1. Labels are deleted by the FIRST jump pass (before cse1) if unreferenced. So a label present at cse1 must be referenced by a branch that exists at cse1 and is later removed. Which pass removes branches after cse1? loop_optimize, cse2, jump passes, sched2, reorg.

Hmm! What if the original code had a `goto` out of the while loop that jump2/loop removes? 

Let me look at the target's loop: `if (unk6 != 0xFF) { do { func(...); s0 += 8; } while (unk6 != 0xFF); }`. The `do-while` loop's condition. In the target asm: 2064 lh v1,6(s0); 2068 li v0,255; 206c beq v1,v0,2094; 2074 li s2,255; 2078 jal; 2080 addiu s0,8; 2084 lh v0,6(s0); 208c bne v0,s2,2078; 2094 ...

Hmm, the loop was unrolled/peeled? There's a beq before the loop (the if) and a bne back-edge.

What if the original source's else branch was structured so that the store `unk1C = unkDC` was inside a block that is the target of a goto from the loop? no.

OK, let me look at this from the cse.c source: does cse1 forward across a `(note LOOP_END)` or a label? It works per EBB, and EBBs end at labels that are jump targets and at barriers. The loop end note doesn't split. The label 173/189 after the loop is a jump target (the beq) → EBB boundary at 2094. So the store/load are in the same EBB after 2094.

Hmm, unless the original had ANOTHER label between them, e.g., a label that is a jump target from within the same block. 

Let me look at the target asm for any branch targeting 20a0 or 209c: branches listed: 202c beqz→20b0, 203c beqz→20b0, 204c bltz→20b0, 205c bnez→20ac, 206c beq→2094, 208c bne→2078, 20b0... None target 20a0. So no label between.

I'm stuck on the mechanism again. Given the moves.md line 37: "cse-store-forward — cse1 forwards the sh value into the reload after `*p -= 16` in one ebb; only a barrier/volatile stops it (W06)" — this is the same wall family and it was a WALL.

Let me try a few more variants and then WALL:
- Insert a *call* between? no.
- Use `flag` as a temp to force a barrier? 
- Try the dead-reset on the *pointer*: `s32 *p = &unk1C; *p = unkDC; ...; p = 0; ...; *p2 -= 1;`? Hmm.

Actually — here's an idea based on C0414: use a *pointer variable* for the store and reset it to 0, then reload via a fresh pointer. cse's forwarding is based on the memory address; if the store's address is `(reg p)` and the load's address is `(reg q)`, cse can't equate them if p and q are not known equal. If p = arg0+0x1C and q = arg0+0x1C, cse sees both as (plus arg0 28)? The front end would emit p = arg0 + 28 (addiu) and q = arg0 + 28 (addiu). With reload folding, both might fold into the memory operands → lw/sw 28(s1) — target bytes! But cse might still see the two addresses as equal (both (plus reg 28) with different pseudos p/q; cse's table is keyed by expression with register numbers; p and q are different pseudos → different expressions → no forwarding!). And reload folds each into the memory operand (base s1 + 28). But wait, would reload fold BOTH? The store's address (reg p) where p = s1+28: reload's `find_reloads` can fold a base+offset into the memory operand if the register dies or is used once? gcc 2.7.2 reload does this via `find_reloads_address` and the "reload inheritance" — it folds a REG_EQUIV/known offset if the pseudo was assigned a register plus a constant. If p is used once, it can fold.

This is exactly h1/h5 (a pointer to the field for the decrement) — which gave 105 (forwarded). Hmm, but in h1 the store was via the struct and the load via the pointer: cse saw the load address as (reg p) and the store as (plus s1 28). It still forwarded?? That means cse equated p with s1+28 (maybe via copy propagation of the pointer assignment). Or the forwarding happened at the RTL level before cse: maybe `combine` or the front end? The .cse dump is after cse1; but the forwarding could have happened in `combine` (before cse1). Let me check the .combine dump for the sequence. The dumps include .combine. If combine did it, then a different approach is needed.

Let me check the combine dump.
