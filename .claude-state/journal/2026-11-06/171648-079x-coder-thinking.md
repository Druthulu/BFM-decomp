---
ts: 2026-11-07T00:16:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lO6wVgDF66BXQOLNbBcz
---
- nopin (launder kept): score 15, 79 insns (same count!). Pairs: s1->s3 x7, s3->s2 x4, s2->s1 x3. So a 3-cycle s1→s3, s3→s2, s2→s1. tp: mine s3? Let me decode: target tp=s3. mine's s1→target s3 x7 (7 occurrences) — so mine's s1 is tp. mine's s3→target s2, mine's s2→target s1.

So with the launder kept, mine: tp=s1, ?=s3, ?=s2. Target: tp=s3, ?=s2, ?=s1.

So the register cycle is (s1→s3, s3→s2, s2→s1) — a 3-cycle.

- nolau (pin kept): score 18, 82 insns (3 extra). Pairs: s1->s2 x4, s2->s1 x3 — just a swap. So the pin fixes tp=s3 but the s1/s2 swap remains.

So:
1. The launder (const-addr folding) is the 3-insn issue.
2. The pin (tp=s3) is the 3-cycle issue.

Hmm. Both needed.

Let me think about the register allocation. Let me get the allocno table. The includer: src/ov_SC02_000/ov_SC02_000_jr_80187B40.c. Only 2 includers.

Let me dump. Actually, let me first try the "block with 2 predecessors" idea for the launder.

Hmm, but the pin is also a wall (3-cycle). Let me check whether the 3-cycle would resolve if the launder were fixed (the allocation changes).

Let me think about the variables: tp, s4, v1, r0, r2, r3, s1, fE, kind.

Target regs: tp=s3, s4=?, s1=?, ... Let me get the target assembly.

Let me disassemble the target object. Find it: build/src/ov_SC02_000/ov_SC02_000_jr_80187B40.o.

Actually, let me first try the launder fix ideas:
1. Add a second path to the use block (goto/label).
2. Make tp assigned inside a loop.

Hmm, actually, let me reconsider. The const-addr fold: mine has `lui a0,0x0; lhu a0,14(a0)`. The target has `lhu a0,14(s3)`.

What if tp is used via a *different expression* that cse can't fold, e.g. `*(u16 *)((u8 *)tp + 14)`? Same.

Hmm. What if tp is `u16 *tp = (u16 *)&D_80126B58;` but I add a real second set of tp with the same value from a *different* symbol expression? No, the value must be the same address.

Hmm, what about: `tp = (u16 *)&D_80126B58;` and later `tp = (u16 *)((s32)tp + 0);`? fold.

Let me think about cse's constant folding more carefully: cse records `(set (reg tp) (const (addr ...)))` — actually a symbol_ref isn't a CONST; it's a SYMBOL_REF. cse handles `(set reg (symbol_ref))` by recording the symbol_ref as a "constant" qty (qty_const). Then a use `(mem (plus (reg tp) 14))` gets folded via find_best_addr.

For the fold to be prevented, tp's qty must not be a constant. If tp is set twice (multi-set) within the block, cse's insert_regs(modified=1) → make_new_qty (unknown). But the second set must be BEFORE the uses.

What if I write:
```
tp = (u16 *)&D_80126B58;
s4 = *(s32 *)(a0 + 0x1C);
tp = (u16 *)&D_80126B58;   // 2nd set, same value
kind = ...;
```
cse: at the 2nd set, insert_regs(tp, classp, modified=1) → make_new_qty? Hmm, if the value is the same symbol, cse might still record it as constant. make_new_qty then the set records the symbol again. So tp is still constant.

Hmm.

What if the 2nd set uses a *computed* value that cse can't fold but equals the address? E.g. `tp = (u16 *)((u8 *)&D_80126B58 + (r0 & 0));` — hmm, `r0 & 0` = 0, combine folds.

What about `tp = (u16 *)((s32)&D_80126B58 | 0);` fold.

Hmm.

OK, different idea: what if the loads use tp in a context where cse's find_best_addr can't fold because the offset is variable? No, offsets are constants.

What if tp is *not* a single-set variable: e.g., declared as a parameter? No.

Hmm, what about the "dead-reset" C0414 applied to tp? The classic use: `p = expr; f(p); p = 0;` — the reset invalidates the equivalence AFTER the use. Not before.

Hmm, but the C0414 doc says: "To stop cse merging two computations of the same address/expression (the classic case: `&local` passed to two calls)". Here we want to stop cse folding the address into the loads.

Hmm, what if the address is computed via a local variable's address? No.

OK, let me look at the actual C: `tp = (u16 *)&D_80126B58;`. What if the original used `D_80126B58` as an array: `u16 *tp = &D_80126B58;`. Same.

Hmm. What if the original source accessed the globals directly (D_80126B58 + offsets) and the compiler... no, then there'd be no tp.

Let me try the "2 predecessors" idea: restructure the if so the use block has 2 predecessors. Actually, cse's extended basic block follows a path; if the block has 2 predecessors, cse processes it from each path or starts fresh.

Hmm, in gcc 2.7.2 cse_main, `cse_end_of_basic_block` computes the path; for blocks with multiple predecessors it starts a new cse_basic_block. Let me look at how it decides.

Actually, easier: empirical. Let me try:
```
if (v1 != 0) {
    ...uses...
}
```
vs
```
if (v1 == 0) goto done;
...uses...
done:
```
The goto form makes the uses block have 1 predecessor (the branch) too. Hmm.

What about a do-while(0)? The C0535 trick splits an EBB. A do{}while(0) around the uses creates a label/block boundary... but do-while(0) is removed by jump1.

Hmm.

Let me try: put the tp assignment in a different block than the uses by using an if/else:
```
if (v1 != 0) { ... } else { }
```
no.

OK, what about this: since the launder's effect is to make tp a "register variable", maybe I can achieve it by making tp's address *not* a simple symbol. E.g.:
```
u16 *tp;
tp = (u16 *)((u8 *)&D_80126B58 + 0);
```
fold.

Hmm, what if I use a *cast through a different type* that gcc doesn't fold: `tp = (u16 *)(s32)&D_80126B58;` — a symbol_ref → s32 cast → pointer. gcc might fold.

Let me just test a batch of ideas:
1. `tp = (u16 *)((s32)&D_80126B58);`
2. `tp = &D_80126B58; tp = (u16 *)((u8 *)tp + 0);`
3. goto restructure
4. do-while around uses
5. tp assigned twice
6. `tp = (u16 *)(&D_80126B58[0]);`

Let me generate and score.

Actually, before that, let me reconsider the overall goal. Both the launder AND the pin are needed for 0. The pin is a 3-cycle allocation issue. Even if I fix the launder, the pin remains. Hmm.

But wait: nopin (launder kept) = 15 with 79 insns and a 3-cycle. If I fix the launder lever-free, maybe the allocation changes and the 3-cycle resolves.

Let me first see the allocno table for this function to understand the 3-cycle.

Let me dump. The includer is src/ov_SC02_000/ov_SC02_000_jr_80187B40.c.

Let me use the splice script. I'll adapt (the header is func_80188790.h).
