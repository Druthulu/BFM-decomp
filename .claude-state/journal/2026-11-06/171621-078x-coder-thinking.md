---
ts: 2026-11-07T00:16:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_k7lhOPcsH2TLvRbq9DeV
---
The key differences:
1. tp is in s4 (mine) vs s3 (target) — the pin.
2. `lui a0,0x0; lhu a0,14(a0)` (mine) vs `lhu a0,14(s3)` (target) — so the launder makes tp a register-relative load (s3), while without it the compiler uses the absolute address (lui a0; lhu a0,14(a0)).

So the launder forces tp to stay in a register; without it, the compiler folds &D_80126B58 into each load (absolute addressing). That's 3 extra insns (the lui's).

So the launder's purpose: keep tp in a register rather than folding to absolute addresses. That's the "cse-const-addr" pattern from the walls (launder | func_801497A8 | WALL cse-const-addr — cse folds const addr into lone use).

Hmm, so without the launder, cse folds the const address into each use. With the launder, tp is a separate pseudo.

The launder is `__asm__ __volatile__("" : "=r"(tp) : "0"(tp));` — it makes tp a new pseudo (the asm output). Since the asm is volatile, cse's table is invalidated, and the new tp pseudo's value is unknown → not foldable.

Lever-free: need tp to be a real variable that cse can't fold to the constant address. 

Hmm! But cse folds a constant address into uses when the pseudo holds a constant. To prevent, tp must be multi-set or its value unknown.

Idea: tp is assigned once (`tp = &D_80126B58;`). If it were assigned twice, cse might not fold... Actually cse folds based on the qty: after `tp = &sym`, tp has the constant qty; uses become the constant.

To prevent folding, the value must be unknown at the uses. E.g., if tp is assigned from a *load* (memory), cse can't fold.

Hmm, but we need tp = &D_80126B58.

Wait — what if I use `tp = (u16 *)((u8 *)&D_80126B58);`? Still constant.

Hmm. What about `tp = (u16 *)&D_80126B58; tp = tp + 0;`? combine folds.

What if tp is read from a pointer variable? e.g. `u16 *tp = *(u16 **)&D_80126B58;`? No, wrong value.

Hmm. The target keeps tp in a register (s3) and loads `lhu a0,14(s3)`. So tp is a register holding the address.

The natural way: if tp is used many times, cse might keep it in a register anyway? But cse folds constants regardless.

Hmm, wait — cse's folding of a constant address into a use: `lhu a0,14(a0)` with `lui a0,0x0` (reloc D_80126B58). That's the absolute form. So cse replaced tp with the constant symbol_ref in each use.

To keep tp in a register, the value must not be a known constant at the uses. Options:
- tp assigned in a different block than the uses (cse's equivalence doesn't cross blocks). tp is assigned before `s4 = ...; kind = ...; v1 = func_8012913C(kind);` and the uses are inside `if (v1 != 0) { ... }` — a different block! Hmm, but cse still folded (mine has lui a0). So cse carried the equivalence across the branch? Or the frontend folded.

Hmm, actually the loads `lhu a0,14(a0)` with `lui a0,0x0` — that's cse folding the symbol into the address.

If tp's assignment and uses are in different basic blocks, cse shouldn't carry the constant... but the fold happened. Maybe because `tp` is a single-set pseudo and cse's table persists? Or the *frontend*? No.

Hmm, wait: cse1 processes extended basic blocks. The block structure: `if (v1 != 0)` — the then-block is a new block. But cse may carry the qty if the block is reached via a unique path (the branch). Actually cse_main's `cse_end_of_basic_block` may include the branch target.

Hmm, mine has `lui a0,0x0; lhu a0,14(a0)` — so it folded.

What if I move `tp = (u16 *)&D_80126B58;` INSIDE the `if (v1 != 0)` block, right before the first use? Then the uses are in the same block as the set → cse folds even more.

Hmm, that's worse.

What if tp is assigned in TWO places (multi-set)? E.g.:
```
tp = (u16 *)&D_80126B58;
if (v1 != 0) { ... }
```
What if tp is also assigned later (dead)? cse would still fold the first uses.

Hmm.

OK, what about the C0414 dead-reset trick: `tp = 0;` after its last use. That doesn't affect earlier uses.

Hmm. What about assigning tp from a *conditional*:
```
tp = (r0 & 1) ? (u16 *)&D_80126B58 : (u16 *)&D_80126B58;
```
jump1/combine merges.

What about making tp's value come from a computed expression: `tp = (u16 *)((u8 *)&D_80126B58 + 0);` → folds.

Hmm. What about using a function that returns the address? No.

Hmm, what about the actual target: `lui s3,0x0; addiu s3,s3,0` — tp is materialized in s3 once, then `lhu a0,14(s3)`. So tp is a register.

For cse to keep it, the pseudo must be non-constant. 

IDEA: what if tp is assigned from a *different* pointer variable that's also used? E.g.:
```
u8 *base = (u8 *)&D_80126B58;
tp = (u16 *)base;
```
Then tp = base (a copy). cse would equate them. Hmm.

IDEA: what if the loads use different index expressions that prevent folding? No, the code is fixed.

Hmm, wait. Let me reconsider: does cse really fold here, or is it the *reload*? The `lui a0,0x0; lhu a0,14(a0)` — this is the standard "load from absolute address" expansion. In gcc 2.7.2, a `symbol_ref` in a MEM address is valid; the assembler emits lui+lo. So cse replaced `(reg tp)` with `(symbol_ref)`.

For cse to not do that, tp's qty must be invalid.

What makes a pseudo's qty invalid? A second set (make_new_qty or invalidate). If tp is set twice, cse's `insert_regs` with modified=1 → make_new_qty. Hmm, but the first set's qty still holds until the second set.

Hmm, so a second set AFTER the uses wouldn't help.

What if the second set is BEFORE the uses but after the first? E.g.:
```
tp = (u16 *)&D_80126B58;
tp = (u16 *)&D_80126B58;   // second set — cse gives tp a new qty, still constant
```
Still constant.

Hmm, what if the second set assigns an unknown value? E.g. `tp = (u16 *)a0;`? Wrong value.

Hmm.

OK, what about this: the target's `lhu a0,14(s3)` and `lhu v0,10(s3)` — tp is used 4 times (14, 10, 10, 10). With 4 uses, cse folds each to an absolute address (3 extra insns: each absolute load needs lui+lhu vs lhu). Actually mine has 3 extra insns (82 vs 79), consistent with 3 of the 4 loads needing an extra lui (one might share).

To keep tp in a register lever-free... 

IDEA: What if tp is used in a *call* argument? No.

IDEA: What if the address is computed at runtime from another pointer? E.g., `tp = (u16 *)((u8 *)&D_80126B58 + (r0 & 0));` — the `& 0` folds.

Hmm, what about `tp = (u16 *)((s32)&D_80126B58 + (r0 - r0));`? combine folds r0-r0? Not necessarily — gcc might not know r0-r0=0 (r0 is a function call result). Hmm! `r0 = rand();` then `r0 - r0` = 0, but the compiler can't prove it (rand has side effects? it's a call, but the value is the same pseudo). Actually `r0 - r0` with the same pseudo → combine simplifies to 0? Probably yes (both operands are the same register).

Hmm.

What about `tp = (u16 *)((u32)&D_80126B58 & 0xFFFFFFFF)`? identity.

OK, let me think about the real source. The target's tp is in s3 and materialized once. What natural C would do that? If tp is assigned once and used 4 times, cse folds the constant. Unless... the compiler's cse doesn't fold because the uses are in a different block and the constant isn't propagated.

Hmm, but mine DID fold. So maybe in the target's source, tp is assigned INSIDE the if-block or after a call that invalidates.

Wait! The launder's effect: it invalidates cse's table (volatile asm). If tp is assigned, then a volatile asm, then used → cse can't fold.

What if I place a CALL between the assignment and the uses? The call `func_8012913C(kind)` is already between! Let me check: 
```
tp = (u16 *)&D_80126B58;
[launder]
s4 = *(s32 *)(a0 + 0x1C);
kind = ...;
v1 = func_8012913C(kind);   // CALL
if (v1 != 0) {
    ...
    fE = tp[7] + ...;   // use
```
So there IS a call between tp's assignment and its uses. And cse STILL folded (mine). So calls don't invalidate pseudo qtys.

Hmm. OK.

So the launder (volatile asm) is what stops the folding.

Lever-free alternative: hmm.

What if tp is declared `volatile u16 *tp`? That's a volatile qualifier — a barrier lever, not allowed.

What if tp is assigned from a `register` variable? no.

Hmm. What if the address is loaded from memory: `tp = *(u16 **)&some_global;`? That changes the code (an extra load).

Hmm, what if we use the address as a *parameter-like* value...

OK, what about this: the C could compute tp inside the if:
```
if (v1 != 0) {
    tp = (u16 *)&D_80126B58;
    ...
}
```
Then tp is set in the same block as the uses → cse folds (constant). Worse.

What if tp is assigned BEFORE the call and the call is opaque? No.

Hmm, let me look at the target's actual code to see how tp is used:
`lhu a0,14(s3)` — s3 = tp. So tp is a register.

What if the original C declared tp as a local initialized from the address and the compiler chose a register because the address is used 4 times and cse's `find_best_addr` decided a register is better? Hmm, cse's `find_best_addr` (cse.c:2656) is about addresses within MEM. Hmm.

Actually, maybe the difference: cse folds the constant only if the load is the *first* use in a block. In mine, all 4 loads got the absolute form. In the target, all 4 use s3.

Hmm, what if the launder's real purpose is to make tp a *multi-set* pseudo (the asm sets it), so cse's table has tp with an unknown qty.

Lever-free multi-set with unknown value: what C assigns tp twice, the second time with a value cse can't track but which equals the address at runtime? 

E.g.:
```
tp = (u16 *)&D_80126B58;
...
tp = (u16 *)((u32)tp);   // identity cast — frontend folds
```
Hmm.

What about:
```
tp = (u16 *)&D_80126B58;
tp = (u16 *)((u8 *)tp + 0);
```
combine folds.

Hmm, what about making tp a function-scope variable that's assigned in one branch and used in another, so cse's table at the use has no qty? 

Wait — actually, here's a thought: cse folds a constant into a use only within the same *extended basic block*. If tp is assigned in block A and used in block C (after a join), cse should NOT know the constant. Unless the frontend/expand already folded it.

Hmm, but the fold DID happen in mine. Let me check where the fold occurs: maybe it's not cse but the *tree/expand* stage. In gcc 2.7.2, `expand_expr` for `tp[7]` where tp is a local var... the frontend wouldn't know tp's value (it's a variable).

Hmm, but cc1's `expand_assignment`/`expand_expr` doesn't do constant propagation.

So it's cse. And cse folded across blocks. That means cse's extended basic block covers the assignment and the uses (the path through the branch).

Hmm, and the launder (volatile asm) breaks the path.

Lever-free: what breaks the cse path? A volatile asm (banned), a function call that... no.

Hmm, what about a LABEL/jump target between? cse starts a new block at a label reached from multiple paths. The `if (v1 != 0)` block is reached from one path (the branch), so cse follows it.

What if I add a second path to the block? E.g., a goto/label structure where the use block has 2 predecessors. Then cse would start fresh at the label, and tp's constant wouldn't be known.

Hmm! That's the "goto chain → structured C" lever. Let me think:

```
tp = (u16 *)&D_80126B58;
...
if (v1 != 0) {
    ...uses...
}
```
The then-block has one predecessor. If I restructure so the uses are in a block with 2 predecessors, cse clears.

For example:
```
if (v1 != 0) {
    goto use;
}
goto done;
use:
    ...uses...
done:
```
Hmm, jump1 would optimize the goto.

Alternatively, the C structure with a `while` loop? The uses are in a block reached by a loop back-edge.

Hmm, this is speculative. Let me first check: is the pin part fixable? tp=s3 (target) vs s4 (mine). And the other regs s1↔s2.

Let me look at the register pairs: s1->s2 x4, s4->s3 x4, s2->s1 x3, s3->s4 x2. So mine's s1 = target's s2, mine's s4 = target's s3, mine's s2 = target's s1, mine's s3 = target's s4.

So two swaps: (s1,s2) and (s3,s4). tp: mine s4 → target s3.

Hmm.

Let me test: with the launder kept (pin removed), what's the score? And with the pin kept (launder removed)?

Let me do that isolation.
