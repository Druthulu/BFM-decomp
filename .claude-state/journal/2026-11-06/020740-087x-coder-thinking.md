---
ts: 2026-11-06T09:07:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vhGMqPZMeryvuXcw54zU
---
Pass order:
- 2827: jump1 (jump_optimize(insns,0,0,1))
- 2865: cse1
- 2895: loop
- 2923: jump (again)
- 2926: cse2
- (combine around 2940?)
- 2983: flow_analysis
- 3028: sched (before alloc)
- 3052: local_alloc
- 3080: global_alloc
- 3105: sched2
- 3142: jump_optimize(insns,1,1,0) — the final jump2 AFTER flow!

So jump2 runs AFTER flow_analysis. If a branch (and its condition computation) is removed by jump2, the product would survive flow!

So: if we can make a *conditional branch* on the product that flow sees as a use, and that jump2 later removes (because the branch is redundant, e.g. a jump to the next instruction), the multiply would remain while the branch disappears!

What branches does jump2 remove? A conditional branch whose target is the next instruction (a redundant branch) — jump_optimize's `delete_jump`/`thread_jump` handles `if (cond) goto L; L:` (the label immediately follows). Does jump1 remove those? jump1 also runs `jump_optimize(insns,0,0,1)` and would remove it early. Hmm, jump1 is before cse1, so a branch to the next instruction would be removed there, before flow. Unless the branch becomes redundant only later.

Alternatively, a conditional branch whose two targets are the same? jump removes.

What about a branch that jump2 removes due to a comparison being against a known value... no.

Hmm, but here's a better one: **jump2's `delete_dead_jumptables`** or the removal of a jump that is the target of... 

What about a branch on a *constant* condition that survives to RTL? E.g., `if ((a[2]-z)*buf[5] == (a[2]-z)*buf[5]) ...` — cse folds to `if (1)`.

What about `while (product) { break; }`? The loop: the condition is tested, and if false, exit; the body is `break`. The loop optimizer might turn it into `if (!product) goto end; goto end;`? Both targets same → the branch is removed? Possibly the loop is simplified to nothing after flow? The loop optimizer runs before cse2/flow though.

Hmm, what about a branch whose condition involves the product and whose target is the fallthrough (redundant)? gcc wouldn't emit it.

What about a **`goto` that jump2 removes**: an unconditional jump to the next label — jump1 removes.

Hmm, what about the branch being removed by **reorg/dbr** (after flow, before output)? The dbr pass fills delay slots; it doesn't remove branches.

What about **`delete_trivially_dead_insns`** or the `jump2` `thread_jump` pass which can redirect jumps and delete dead code? jump2 can delete a jump that becomes redundant after threading.

Idea: create a branch that jump2 deletes due to `thread_jump`. Hard to control.

Alternative: a branch that is removed by **combine** (after cse2, before flow)? Combine runs before flow, so no.

Hmm, what about the branch being removed by **flow itself**? flow only deletes dead sets, not branches.

OK, what about `jump_optimize(insns, 1, 1, 0)` at 3142 — after sched2, before final. It does `delete_dead_jumptables`, `thread_jump`, etc. If a conditional branch on the product is threaded into an unconditional jump... The product's multiply would still be in the code (the branch's condition computation might be deleted if the branch becomes unconditional! `delete_jump` removes the condition computation? It deletes the insns computing the condition if they become dead — but that's `delete_insn` + `delete_computation` which removes the whole computation including the multiply!). Hmm, jump2's `delete_computation` would remove the multiply.

So even if the branch is removed after flow, the condition computation is deleted too.

Unless the branch is removed in a way that leaves the computation: `delete_insn` on the jump only, with the condition computation still "used" elsewhere? no.

OK, that route is dead.

Let me try a different one: the `(use)` insn that combine creates for REG_DEAD at a code label — we saw it survives to lreg/sched in item 2! If a USE of the product's register survives to the final code, the register is live and the computation stays. How to create such a USE with real C? Combine creates it when a REG_DEAD note can't be placed. That's triggered by the shape of the RTL, not directly by C.

Hmm, in item 2's c1, the USE of reg78 was created by combine at a label and survived to lreg/sched. Yet the copy was still merged. The USE didn't keep the *copy* alive because the copy's destination value came from the merged neg.

For our case: if a USE of the product's register is created at a label, the register is live there → the multiply is kept! How to get combine to create a USE for the product's temp? The REG_DEAD note situation arises when a value dies at a code label. E.g.:

```c
tt = product;
if (cond) { ... }
// tt used after?
```
Hmm.

Actually, item 2's USE came from a REG_DEAD note of reg78 at the label 128, created by combine while merging. The USE was of the *variable* whose death was being tracked. It didn't emit code but kept the register live.

For our product: we need a variable tt = product, dying at a label, with combine inserting a USE at the label. Then tt is live at the label → the multiply kept. And the USE emits no bytes. But how do we get a REG_DEAD at a label from C?

In item 2, the REG_DEAD of reg78 (val) at label 128 was the death of val's *previous* value at the start of the else block (val was assigned in the then block and used in the else... no). Hmm.

This is getting deep. Given time constraints (~15 min now), let me try a couple of concrete candidates:

A) `tt = product;` then later `if (cond) { tt = 0; }` and use tt after? That's a real use → kept but maybe with no extra insns if the use is a merge... 

Hmm, let me think about the actual target again: t1 = $9. If tt is live at a label, the RA would keep it in a callee-saved reg or a caller-saved one; the target has t1 (caller-saved) and the value dies quickly. A USE at a nearby label (within the same block region) could keep t1.

Concretely: 
```c
tt = (a[2]-z)*buf[5];
gte_ldv3c(&v[0]);
... GTE ...
if (tt) { }     // empty -> removed at tree level
```
No.

What about:
```c
tt = product;
if (cull) { ... }   // some branch; tt dies at the label?
```

Honestly, this is speculative. Let me instead test a few branch-based variants to see the scores, and check the dumps for whether the multiply survives when a branch is present:

v31: `if ((a[2]-z)*buf[5]) { cull = 1; }` — changes cull but cull is reset later? In the source, `cull = 0; if (mx < -0xA0 ...) cull = 1;` comes AFTER the asm. So `if (product) cull = 1;` before `cull = 0;` would be dead (cull overwritten) → the branch might be removed. Let me test: the branch condition uses the product; gcc might keep the branch (a store to cull is dead → the whole if removed? jump.c removes an if whose body is dead? The body is a store to a dead variable → flow deletes the store but the branch remains? cse/flow might remove the empty branch?).

v32: `if ((a[2]-z)*buf[5] > 0) { z = z; }` — empty body.
v33: `while ((a[2]-z)*buf[5]) { break; }` — loop.
v34: `if ((a[2]-z)*buf[5] == 0) goto L2; ... L2:` — branch.

Let me test these 4 quickly and look at the diffs. If any keeps the multiply with only a small diff, I can iterate. Time: 02:08 now; 20 min at 02:14. I'll do this batch and then finish.
