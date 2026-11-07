---
ts: 2026-11-06T23:51:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XiAqaXU7NEiIUoqZEaK3
---
Interesting!
- G (pin removed, launder kept): score 14, REG-callee, 161 insns — so the copy is right, but the callee-saved reg assignment differs (s3/s4 swap).
- H (pin kept, launder removed): score 5, 160 insns — only the missing move.

So the two are independent. The launder removal costs 5 (the missing copy). The pin removal costs 14 (reg swap).

So for the pin: with pin, mode is s3 and base s4. Without, base s3, mode s4. Need to flip allocation order.

And for the launder: need the copy.

Since these are independent, solve each.

Launder → copy: need a C construct producing the copy. The asm works because cse's table is invalidated (an asm has no recognizable pattern; cse's `invalidate_from...`? Actually an asm invalidates everything). 

Wait — actually let me reconsider. `__asm__("" : "=r"(q) : "0"(q))`: this is a real insn with a SET of q. cse sees `set (reg q_new) (asm_operands ...)`. Since q_new is set to an unrecognizable value, q_new gets a new qty (unknown). Then `p = q_new`: make_regs_eqv(p, q_new) — q_new HAS a valid qty (new). So p becomes eqv to q_new. Hmm, then p's uses → q_new. That would still merge!

Unless... the asm's output operand is an *output* that cse treats as a hard register clobber? Hmm.

Wait, but empirically the asm DOES produce the copy (G_nopin has 161 insns and the right move). So cse did not merge. Why?

Because the asm insn sets q_new from an *asm_operands* — cse's cse_insn processes it: the destination is a register, source is ASM_OPERANDS (not a reg or constant). It calls make_new_qty for the dest? Then `p = q_new` would make_regs_eqv(p, q_new)...

Hmm, unless the order is: q_old = &sym (q_old gets the address qty). asm: q_new = asm(q_old). cse processes: destination q_new, source asm_operands → make_new_qty(q_new). Then p = q_new → make_regs_eqv(p, q_new). Both eqv. Then uses of p replaced by the canonical. Hmm, that should merge.

Unless cse treats asm insns as invalidating the whole table (`insn_invalidates_p` for volatile asm) — `__asm__("" : "=r"(q) : "0"(q))` without volatile... but it's an asm with no side effects? GCC treats all asm as having side effects unless volatile? Actually basic asm is volatile by default; extended asm without volatile can be optimized. Hmm.

Whatever — empirically the copy appears. Let me find a C construct. 

Idea: use a *call* that invalidates the table. But we can't add a call.

Idea: make q's value come from a place cse can't track: e.g. `q = (s32 *)&D_800C7C64 - 1;`? The reloc would be D_800C7C64 with offset -4. Different bytes. No.

Idea: `q = &D_800C7C60; q = (s32 *)((u32)q);` — identity cast, frontend folds.

Hmm what about a *union*:
```
union { s32 *p; u32 u; } cv;
cv.p = &D_800C7C60;
q = cv.p;
```
Memory round trip (store+load) — extra insns.

What about making q a function-scope variable assigned before the call? A_hoist tried that; still folded. Because cse followed the straight-line path.

What if the copy is in a block cse reaches via a *different* path? E.g. the address set in the entry block, and the copy inside the then-arm after a branch — cse follows the taken path and keeps equivalences (it does `record_jump_equiv` and follows the branch). Hmm, so it follows.

But cse does NOT follow a branch that's not part of the path... Actually cse_main processes the "extended basic block" paths; for each block it may start a new cse_basic_block from the block start (table cleared) when the predecessor's end state isn't unique.

The `if (func_8002F658() != val || mode >= 0)` has two predecessors for the then-arm? No, the then-arm has one predecessor (the branch), but the entry block ends with the call + comparison, and the branch is conditional. cse_main's `cse_end_of_basic_block` decides. It could either continue through the branch (taken path) or stop. For a conditional branch with an else, cse typically stops at the branch (since the block has a branch, `cse_end_of_basic_block` returns the end of the block). So the then-arm is a NEW cse_basic_block with a cleared table!

But A_hoist still folded. Hmm, why? Maybe because the *frontend* (expand) already folded `p = q` — no, expand wouldn't.

OR maybe cse2/combine did it. Let me reconsider: cse1 might not merge across blocks, but then combine merges `p = q` with the store if p dies... p doesn't die. Hmm.

Actually wait — maybe the frontend's `store_expr` for `p = q` where q is a variable: it emits `(set (reg p) (reg q))`. Then in cse1 (if same block) merges. In A_hoist, different blocks → cse1 doesn't merge. Then what removed the copy? 

Hmm, in A_hoist the count is 160 = no copy. Maybe the register allocator coalesced p and q (they're copies, so local/global-alloc can assign them the same register, and the copy `move a3,v0` becomes `move a3,a3` which is deleted by... combine? or by the `reg_dead` copy propagation). Yes! Even without cse, the copy `p = q` where p and q can be allocated the same register becomes a redundant move. Copy coalescing: global-alloc/local-alloc uses `reg_alloc` and copies get the same reg when possible. So the move disappears.

In the target, q=v0 and p=a3 — different registers. Why couldn't they coalesce? Because p is used across a call? No... p is live across the CdReadRequest call? p is passed TO the call, so it dies at the call. q dies at the copy. So both short-lived. They could share.

Unless the copy is NOT a plain copy but something that prevents coalescing. Hmm, but the asm version keeps them separate because the asm's output register is constrained? The asm output "=r" allows any reg.

Hmm, wait. Let me reconsider: with the asm, q_new is set by an asm insn. GCC's register allocator won't coalesce a copy with a register that is set by an asm? Actually, it might. But the asm insn itself forces q_new into a register that must be... the asm output "=r" is a pseudo that gets a hard reg. And `p = q_new`. Local-alloc might tie them (copies get tied). But apparently not.

Hmm, alternatively the reason is scheduling: v0 and a3.

Let me look at this from a different angle: what if I keep the copy but force p and q to different regs by giving them different live ranges? E.g. make q live across something.

OK, let me try the empirical route more broadly. Let me generate a set of candidates that:
1. make q live longer (used after the copy)
2. make p and q different modes
3. use a struct field for the address
4. use `q = &D_800C7C60; p = q;` with q declared as `s32 *const q`? const might change things.
5. Assign the address to a `u32` and then to p via a conditional.

Actually here's a thought: what if we make the address come from a *pointer variable that already exists*, e.g. `base`? No, different symbol.

Another thought: what if the extra `move` is not a coalesced copy but a *store-address* materialization? E.g. if the C is:
```
s32 *q = &D_800C7C60;
p = q;
```
but q is `register s32 *q`? no, register vars are banned.

Hmm hold on, let me reconsider the whole thing. Maybe the launder is load-bearing because of the *scheduling* (sched1), not cse. Let me look at the diff H_nolau vs target: score 5, 160 vs 161. Let me see the actual diff.
