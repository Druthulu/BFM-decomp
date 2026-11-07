---
ts: 2026-11-06T22:34:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_v40FVLd0lIa3S2J9VNLc
---
This is the path-following logic. The cse pass processes an EBB by following a path; at a branch, it may follow the taken path. The key question: after the `bne $17,$4,$L72`, does cse follow into $L72 with the table intact? It follows jumps if the label has a single reference. So yes, it merges across the branch.

But if the second use is in a block with multiple predecessors (a label with multiple refs), cse stops (new_basic_block). So placing the second s1ang use in a merge block (e.g., after the two ifs) might avoid merging.

Let me look at the structure: 
```
iVar4 = u5 - u6;                       // block 2
if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }   // block 3/4
if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }  // block 5/6
if (iVar4 >= 0) { q = iVar4 / d; ... }
```
The merge point of the first if is the start of the second if — which is a label with 2 predecessors. cse's table would be reset there (new_basic_block when reaching a label with >1 use). So a use of s1ang in the second if's condition/body would be a separate basic block → s1ang raw global.

So: use `(s1ang & 0xFFF)` in the second if block, e.g.:
```
if (iVar4 < -0x800) { t = (s1ang & 0xFFF) - 0x1000; iVar4 = u5 - t; }
```
But then u6 = s1ang & 0xFFF computed in block 0 (for the compare and first arm), and again in the second if block. The second andi is in a different basic block, so cse won't merge. This adds an instruction (extra andi) → 76 ins, not matching. Unless the extra andi is folded... no, it's a real instruction.

Hmm. Unless the *first* computation is eliminated instead. What if we DON'T compute u6 in block 0 for the compare, but use s1ang raw in the compare and compute u6 later? The compare `if (u6 == u5) return 0;` needs the &0xFFF. In the target, `andi $17,$17,0x0fff` is in block 0 before the bne. So the andi must be in block 0.

So u6 must be computed in block 0, and its use in block 0 (compare). For s1ang raw to be global, s1ang must be used in another block without cse merging. Any such use needs its own instruction → 76+.

Unless the extra use replaces an existing instruction. Hmm: in the second if, `t = u6 - 0x1000` uses u6. If we write `t = (s1ang & 0xFFF) - 0x1000`, that's an extra andi. But if instead we could make the *existing* andi be in the second block and the compare use... no.

What if u6's computation is moved to block 2 (after the compare)? The compare needs it. 

What if the compare compares raw s1ang to u5 with the mask applied to u5 instead? `if ((s1ang & 0xFFF) == u5)` — same.

Hmm, alternatively: what if s1ang raw is used in the compare *unmasked* and u6 elsewhere? The compare is `u6 == u5` where u6 = s1ang & 0xFFF. We could write `if (s1ang == u5)` only if s1ang were already masked — but the target has the andi.

Hmm, what if we write `u6 = s1ang & 0xFFF; if (u6 == u5) ...` and then use s1ang raw in a later block in a *dead* computation that flow deletes? Flow (dead code elimination) runs after cse. If cse doesn't merge (different block), the instruction exists until flow; flow deletes dead code. But flow doesn't run on RTL values? It does (flow.c does dead code elimination). But the register allocator (global-alloc) runs after flow, so if flow deletes the dead use, s1ang raw dies there → local again? Actually the local/global decision is made by local-alloc based on the RTL at that point (after flow). If flow removes the use, s1ang is local again.

Hmm, but the register-allocation "local" property is determined in local-alloc by scanning refs. If the dead use is deleted before, no good.

What if the extra use is in a block reachable from multiple preds and is *not* dead but folded by combine into an existing instruction? Combine runs early (before cse2? order: combine, cse, ...). Hmm.

Let me reconsider. Maybe there's a fundamentally different approach: change the *block structure* so that the s1ang raw load and its use (the andi) are in *different* basic blocks, making s1ang global naturally, while keeping the instruction sequence identical.

In the target: block 0 contains the lh (insn 20) and the andi (insn 69) and the bne (insn 72). The andi is in block 0 because the bne uses its result.

What if the source's `if (u6 == u5) return 0;` is compiled as a branch where u6 is computed in a *predecessor* block... it's the same block.

Hmm. What if we split block 0 with an `if` that doesn't add instructions? E.g., `if (arg0) { ... }` — adds a test/branch.

Hmm.

Wait, maybe I'm wrong that s1ang must be $s1 in the target due to the pin. Let me reconsider: what if there's a real-C way to make the divisor d get $s0 that doesn't involve s1ang at all — e.g., make d's pseudo *preferred* to $s0 through a copy? Global-alloc preference: r77 prefers 16 because of the dying input. Could d get a preference for $s0? Preferences come from copies/insns. d = arg1 (from $a1) → prefers $a1, not $s0. If we could make d the output of an insn whose input dies in $s0... like a copy from a variable in $s0. But the only $s0 thing is... nothing.

Hmm, what if d is copied from s1ang or a stack value in $s0? No.

Alternatively, could we make the register allocator give $s0 to d by *lowering r75's qty* so that it doesn't take a callee-saved reg at all? r75 crosses a call → must be callee-saved. Unless... the call doesn't clobber it because s1ang raw is used before the call and after? It is live across.

Hmm, what if we split s1ang into two values: one used before the call and one after? The target has ONE lh. If we load s1ang before the call and use it after, one value.

What if the source loads s1ang, uses part of it (e.g., low bits) before the call, and the rest after? The target only uses it after.

Let me look at the target's exact use: `lh $17,18($2)` before the call, `andi $17,$17,0x0fff` after. So one pseudo.

I'm stuck on the direct route. Let me look at what the W50x coder tried and check the notes more carefully... The notes list w1-w7 and MATCH attempts w4/w5/w6. It says "No real-C move removed the $16 conflict. Wall family: global-pri-bank-order / lreg-index-conflict."

Hmm. Maybe the answer is a different real-C move: change the code so that the s1ang load's pseudo is not block-local by making the *ratan2 call* be in a conditional or by moving the s1ang load into a block that has the andi... 

Wait, actually! What if we make the `u5` computation and the s1ang load swap such that the `lh` for s1ang is scheduled before the call but its *source statement* is after the call? No, sched1 won't move loads across calls.

Hmm, what about making the ratan2 call NOT a call in the same block? No.

Let me reconsider the problem statement: "W50x left this header item PARTIAL:pin after 9 tries (keepalive gone, prev_win.c, 0 on 141/141). src still holds the old body (not banked): start from prev_win.c and remove the kept $-pin with new moves; MATCH = keepalive and pin gone, 0 on every includer."

The brief says "start from prev_win.c and remove the kept $-pin with new moves". So the expectation is that new moves can crack it. My job: find a move.

Let me think about local-alloc more. Maybe I can make r75 get $s1 by making its qty LOWER than another local pseudo that takes $s0 and is dead before d's live range... 

OR: make r75 not need a callee-saved reg by making its live range not cross the call. How? If the value is used before the call as well, and after the call the value is *reloaded* from the same address — then there are two loads. But what if the target's `lh $17,18($2)` is exactly one load and the value crosses... 

Hmm, wait. Actually, let me re-examine: maybe the target's s1ang raw is NOT live across the call in the RTL! Let me look at the lreg dump for the pinned version to see r75's refs and whether it crosses the call. Let me check the pin dump's lreg.

Actually in the pin alloc table, r75 s1 and "crosses 1 call" appears? Let me check the pin alloc line: "r75 s1 2857 2 7 0 ; crosses 1 call; GR_REGS or none." Yes, crosses 1 call.

So in the target too, r75 is a local pseudo crossing a call, and local-alloc gave it $s1 because $s0 was pinned.

Hmm OK. So the pin is doing real work: reserving $s0. To crack without a pin, we need another pseudo to occupy $s0 for the whole function without changing the instruction stream. 

What about the *stack pointer*? No.

What about making another global pseudo be assigned $s0 — a global pseudo with high priority that conflicts with d? Then d would go elsewhere. No.

What if we make a global pseudo be assigned $s0 but it's DEAD before d's range? d's range is the whole function.

Hmm, unless we shorten d's live range! What if d is redefined/recomputed later? The target's d is live from entry to the end. But what if we introduce a second variable that is the divisor in later blocks, so d dies early? That would change the code (extra moves).

Hmm.

What about the reverse: make s1ang raw take $s1 by making $s0 "hard-used" in block 0 by a hard register that's live... e.g., if we use $s0 explicitly somewhere as a function call argument? No, that's a lever.

OK, let me look at local-alloc's actual choice logic. Maybe the reg_alloc_order for MIPS puts $s1 before $s0? Let me check mips.h REG_ALLOC_ORDER.

Actually, in the w0 dump, r75 got 16 ($s0) — so $s0 first.

What if the pseudo's register class excludes $s0? E.g., a pseudo that can't use $s0... no.

Hmm, what if we make s1ang raw a *floating point*? No.

Let me look at local-alloc.c `block_alloc` to see if there's a lever like `qty_phys_reg` or preferences.

Actually, here's another thought: local-alloc assigns $s0 to r75. What if r75 has a *copy preference* to $s1 because of how the source is written? Local-alloc's preferences come from `reg_equiv` and from copies (`qty_phys_copy_sugg`). If we write `s1ang = x;` where x is a pseudo in $s1... no.

But wait — maybe we can make s1ang raw prefer $s1 via a *tie* with the u6 pseudo? No.

Let me look at the actual local-alloc code for how it picks a reg.
