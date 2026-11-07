---
ts: 2026-11-06T22:34:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KauluS0uTSpk5mopfUXi
---
So `qty_phys_sugg` gets set when a pseudo is used with a hard reg in a *tieable* operand. For the `lh` (extendhisi2_internal), the destination is the only reg. Hmm.

But here's an idea: if s1ang raw is used in an insn together with a hard register (e.g., in an operation where one operand is a hard reg), local-alloc would suggest that hard reg. Which hard reg could suggest $s1? Hmm.

Alternatively, the "copy suggestion": if s1ang raw is the source of a copy to a hard reg... e.g., if s1ang is used as an argument to a call, it'd be tied to $a0 etc.

Hmm.

What about `qty_phys_copy_sugg`: if a pseudo is copied from a hard reg, it suggests that hard reg. For example, `s1ang = D_80126CB8;` (a global load) — no.

What if we write the s1ang load so it's an operand of an insn that also has a hard reg operand in a tieable position? E.g., an add with a constant? No.

Hmm, this is getting deep. Let me reconsider the block_alloc order: "Order the qtys so we assign them registers in order of decreasing length of life" — qty_compare: higher priority = more refs * log2(refs) * size / lifetime. So shorter-lived, more-referenced gets allocated first. r75 (2 refs, 7 insns) vs other block-0 locals. If another block-0 local has higher priority and takes $s0... but conflict with d.

Wait, actually — maybe there's a local pseudo in block 0 that is NOT live across the call and takes a caller-saved reg. That doesn't help.

Hmm, hold on. Let me reconsider the constraint: d conflicts with $s0 if a local pseudo has $s0 at any point during d's live range. But what if the local pseudo with $s0 is in a block where d is NOT live? d's live range is from insn 6 to the end... but maybe not! Let me check d's live range in the lreg dump: d = r74, "9 times across 27 insns; dies in 3 places; crosses 1 call". d is live in blocks 0,2,3,4,5,6,7,9. It's used in the divs.

Hmm, block 1 (the return arm) — d isn't live there. Block 8, 10, 11, 12 — d not live.

So a local pseudo in block 1 (return arm) could take $s0 without conflicting d? Block 1 is the `return 0` arm — it has `move $2,$0` and the jump. No pseudo there.

Block 8/10/11/12 are the epilogue/tail blocks. Hmm.

What about the return-0 block: it's block 1, which contains insn 74-76. In w0, is there a pseudo there? No.

Hmm, what about making the s1ang raw pseudo be in block 1? No.

OK, let me try yet another angle: what if we make the s1ang raw value *not* cross the call by making the ratan2 call's arguments not depend on... no, the call is between.

What if the call is moved before the s1ang load by source order? The target order: s1ang load is before the call. Hmm, but wait — is that really required by the target? Let me re-read the target asm:

```
lh $3,14($2)
lh $4,D_80126CB8
lh $5,6($2)
lw $2,32($2)
subu $4,$3,$4
lh $3,D_80126CB4
lh $17,18($2)
jal ratan2
subu $5,$3,$5
```
Yes, `lh $17,18($2)` (s1ang) is before the jal. This is because the source loads s1ang before computing u5, and sched1 interleaves them.

If we moved the s1ang load after the ratan2 call in source, sched1 might hoist it before the call? sched1 can move loads within a basic block if no memory dependence. The call is a memory barrier, but the `lh` from arg0's structure could be hoisted above the call if there's no aliasing store. Actually, sched1 in gcc 2.7.2 does not move insns across calls? Let me check: calls have `REG_DEP_ANTI` etc. Sched1 treats calls as... Let me test empirically: write the source with the s1ang load AFTER the u5 computation and see if the lh ends up before or after the call.

If sched1 hoists the lh before the call, then we get the target order but s1ang raw is defined after the call in RTL order... no wait, if sched1 moves it, the pseudo's live range in the RTL *before* sched1 determines local-alloc (local-alloc runs before sched1? Pass order: local-alloc and global-alloc run before sched1? Let me check: GCC 2.7.2 pass order: ... jump_opt, cse, loop, cse, ... then `local_alloc`, `global_alloc`, ... then `sched`. Actually sched (sched1) runs BEFORE register allocation! In GCC, the first scheduler runs before reload/regalloc. Let me check toplev.c pass order.

In gcc 2.7.2 toplev.c: `{ "sched", sched, 0 }` appears before `{ "lreg", local_alloc, 0 }`? Let me grep.
