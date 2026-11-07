---
ts: 2026-11-06T01:53:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KYZSncHrfBtU84udumEv
---
In v1, at every pass the order is: li 29, store 28, store 244 — i.e., sw then sh. So neither sched1 nor sched2 swapped them. So v1's order is stable.

Hmm, so how does the target get li; sh; sw? The original source must have written sh before sw. So the original source order is sh;sw (like our src), and the merge must be prevented some other way.

OK so back to: with source order sh;sw, the merge happens. Need to break it.

Let me look at the problem from the "dec block" side once more. What if the dec block in the original source was NOT `unk1C--` at the end of a return block, but rather the store was in a different position? Target dec: lw; nop; addiu; j; sw(delay). Hmm.

What if the original dec block's store had a *different pseudo* that got the same hard reg v0 but... at jump2 regs are hard. No.

Wait — maybe I should check whether find_cross_jump's rtx_renumbered_equal_p compares the MEM's `MEM_IN_STRUCT_P`/alias set. No.

Hmm, but hold on: rtx_renumbered_equal_p for MEM: it compares the address expression and the MEM's mode and alias. The two MEMs: one is `mem/s:SI` (in-struct) and the other also `mem/s:SI`? In the orig dump both showed mem/s:SI. Yes.

New idea: what if the original zero block's store was the LAST statement but the block was NOT the last block — i.e., the function had a trailing `return;` after the zero block *inside a separate block* that the compiler placed... no.

Let me look at the actual target's function layout once more. Actually, maybe the original source used a `switch` statement! The `t == 0`, `t >= 0x1E` structure could be a switch with cases. In a switch, gcc emits a jump table or comparisons; the zero block could be the `default:` case placed at the end, and the switch's dispatch... Hmm, the target has comparisons (beqz, slti), not a table (only 2-3 cases? t==0, t>=0x1E, else). A switch on t with cases 0 and >=30? Unlikely.

Alternatively the original might be:
```
if (t != 0) {
   ...dec...;
   return;
}
...zero...;
```
Same shape.

Hmm, what about this: the original zero block's final store might have been `unk1C = 0x1D;` followed by a *call* that got inlined? No.

Let me reconsider the possibility that the target was built where the zero block's store is NOT the same instruction because of a different *offset representation*: e.g., in the original, the zero store might be `((Unk*)a0)->unk1C = 0x1D;` where a0 is the parameter directly (not s0). At jump2 the base would be a0 ($4) or s0? The target shows s0. If the function's parameter were used directly, gcc would copy it to s0 at the prologue (it does: move s0,a0) and use s0. Same.

What if dec's store used a0 and zero's used s0? Target both s0.

OK, let me try to find the answer by checking whether the ORIGINAL target's jump2 merge would have been prevented by the *dec* block's jump being a different insn: what if dec's jump at jump2 was `j` to a label that is NOT the epilogue but a nearby label, and the epilogue is reached by fallthrough from that label? E.g., a label between dec's store and the epilogue. The final asm has dec's j targeting 180c (epilogue). Hmm.

What if the original dec block ended with `return;` but the *return label* was reached via a jump to a label placed right before the epilogue, and the zero block fell into the same label? Same.

Hmm, let me look at whether there's a *label* in the target at 180c that's targeted by many jumps — yes, all returns j 180c.

Let me try yet another idea: make zero's store insn differ by making the *dec* store's MEM non-in-struct (MEM_IN_STRUCT_P affects only scheduling). No.

What about making the zero store use a different addressing mode: e.g., `*(s32 *)(a0 + 0x1C) = 0x1D;` (v4, scored 9, still merged) — same RTL.

What about `((Unk*)a0)->unk1C = 0x1D;` where unk1C is declared as a different type, e.g., `u32`? Same.

OK, let me look at the barrier from another angle: maybe the original C had a `return;` in the zero block AND the merge was prevented because the zero block's trailing jump was NOT deleted in the first pass — because the *return label* was not immediately after the jump: there might have been *other code* after the zero block at the RTL level that final/reorg moved or deleted. What code? The function's epilogue is generated in final. But what about the `(note NOTE_INSN_FUNCTION_END)`? Notes are skipped.

Hmm, what if the zero block's trailing return jump targeted a label that is followed by an INSN (e.g., a `(use (reg 31))` emitted by expand_function_end for the return value)? Our function is void.

WAIT. What about the `pad[8]` dead local? No.

Hmm, let me look at how the OTHER 4 items' functions are structured — maybe one of them has a similar pattern and a known crack. But first, let me check if maybe the merge can be avoided by making the dec block's store NOT immediately before its jump: if dec's block had the store then an insn that emits nothing... same problem.

Let me try: make the zero block's store come from a *different* pseudo than the li by using a variable that is live elsewhere, so that at jump2 the store's source is not v0? No, target requires v0.

Hmm, what about making the zero store's address use `(plus (reg s0) (const 28))` vs dec's `(plus (reg s0) (const 28))` — same.

I wonder if the original source's dec block was written with a *different variable* for the decrement, e.g.:
```
t = ((Unk*)a0)->unk1C - 1;
((Unk*)a0)->unk1C = t;
```
Same.

OK, let me look at the problem completely differently: maybe the merge is caused by a *specific* aspect of our reconstruction that the original didn't have: the `t` variable. In our src, `t = unk1C; if (t == 0) goto zero; if (t >= 0x1E) goto dec;`. The zero block is at the end. Fine.

What if the original source used a *switch* on t? Not.

Let me look at the other 4 items first — maybe they're easier, and I can come back. Time is a concern: ~1 hour spent on item 1. Let me check the other items' sizes and kinds. All barrier. Let me quickly assess them and maybe knock out easier ones, then return to item 1.

Actually, the budget says 20-30 min per item; I've spent ~50 min on item 1. I should record progress and move on, but the instruction says "past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries". I have ~12 scored tries on item 1. I need ≥30 scored tries for a WALL. Hmm.

Let me generate 20+ variants quickly for item 1 and score them in one batch (each ~1.5 s → 30 s). That gets me to the WALL threshold if nothing works, and might find the crack.

Variants to try (systematic):
1. do-while around the whole zero tail (C0535) — splits cse1 EBB.
2. do-while around the store.
3. do-while around sh+store.
4. `t = 0x1D;` before the if, store t.
5. `v = 0x1D;` (s16).
6. store via pointer variable p.
7. `unk1C = (s32)0x1D;`
8. `unk1C = 0x1D | 0;`
9. `unk1C = 0x1D + 0;`
10. reorder sh before store but insert a `do{}while(0)` between.
11. `if (unk1C != 0x1D) unk1C = 0x1D;`? changes code.
12. `unk1C = 0x1D; if (0) return;`
13. goto to a label after the store.
14. `unk1C = 0x1D; { }`
15. wrap zero's last two statements in a do-while with a break.
16. Use `unk1C = 0x1D, sh = 0;` comma?
17. Store order sh;store but add `do { } while (0)` after the store.
18. `unk1C = 0x1D; return;` inside `do { ... } while (0)`.
19. Make dec's store via `((Unk*)a0)->unk1C -= 1;` (compound).
20. dec: `t = unk1C; unk1C = t - 1;`
21. zero: `t = 0x1D; ... unk1C = t;` with t used in the sh too?
22. zero block written before dec in source? changes layout.

Let me also reconsider the "sched1 fence" comment in the TU at line 4216: "`__asm__ __volatile__("");` before `one = 1;` -- zero-byte sched1 fence". Not relevant.

Let me batch-generate and score ~22 variants.
