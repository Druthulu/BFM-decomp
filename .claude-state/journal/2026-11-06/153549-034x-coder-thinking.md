---
ts: 2026-11-06T22:35:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QTksZEfirfG3JLBYIwbX
---
This is the tying logic for block-local pseudos. The `combine_regs(r1, r0, ...)` where r0 is the set dest and r1 is an input; if they can be tied, they share a qty.

Key: if s1ang raw and u6 could be tied into the same qty... but u6 is global (used in multiple blocks), so it's not in this block's qty list. `combine_regs` with sreg/ureg where one is global: "Do nothing if SREG already has a quantity or is a register that we don't allocate." So the tie fails, and then "if UREG is a hard reg and SREG is a pseudo, record the hard reg in qty_phys_sugg" — but here both are pseudos.

Hmm.

Let me step back and consider a completely different move family: maybe the answer is to change the code so that `s1ang` raw's pseudo is *not* the one that crosses the call — e.g., by making the loaded value used before the call and the post-call value a *different* pseudo that is born before the call via a copy.

Actually! Here's a thought: what if we compute `u6` BEFORE the call? The target computes `andi $17,$17,0x0fff` after the call, but maybe sched1 could move it before the call? No, the target has it after.

Hmm.

Let me reconsider: is there a way to get the s1ang value into $s1 by making it *not* cross the call but still have the lh before the call? What if the value is stored to the stack before the call and reloaded after? That's what the callee-saved reg does implicitly. Extra instructions.

OK, radically different idea: what if we make d a *local* pseudo by restructuring the code so the division is done in one block? No, the division is in two arms (if/else) and the arms are separate blocks. But d is used in both arms (blocks). If we compute `q = iVar4 / d` before the if? No, the target has div in both arms.

Hmm, what if we make the two divs use *different* variables, each local to its block? Then each would be a local pseudo in its block, and the divisor value would have to be copied into each block... that changes instructions.

What if the divisor `d` were only used in ONE block? It's used in both arms of the if/else, which are separate blocks. Unless we merge the arms: `q = iVar4 / d; if (q == 0) q = (iVar4 >= 0) ? 1 : -1;` — that changes the structure (one div instead of two). The target has two divs (one per arm) with the branch. Actually wait, the target:
```
bltz $3,$L75
div $3,$3,$16
bne $3,$0,$L79
move $2,$3
j $L77
li $3,1
$L75:
div $3,$3,$16
...
```
Two divs. So d is used in two blocks → global.

Hmm.

What if we keep d global but make its live range shorter so it doesn't conflict with $s0 in the early block? d is live from insn 6 because it's assigned at entry. The conflict with r75 ($s0) arises in block 0. If d's live range started after block 0... but the target's `move $16,$5` is at entry.

Wait, actually — what if the `move $16,$5` is not from `d = arg1` at the top but from the cast? The target has `move $16,$5` at insn 6 and `sll $16,$16,16` at insn 57. If the source is `d = arg1` at the top, gcc emits the move at entry. If we instead write `d = (s16)arg1` (cast at entry), we'd get sll at entry, not the target.

Hmm.

Let me look at the problem from the "what would the real source be" angle. The real original C probably was:
```
s32 func_8012B8E4(s32 arg0, s32 arg1) {
    s32 d = arg1;
    s32 s1ang = ...;
    ...
}
```
The original compiler (with -O2) produced d in $s0. Why? Because in the original compilation, there was no pin — the compiler chose $s0 for d naturally. That means in the ORIGINAL compilation, the allocator did give d $s0. So it IS possible with real C! The pin was added by the decomp because their body didn't reproduce it, but the original compiler's register allocation gave d $s0.

So there must be a real-C formulation where d gets $s0. The difference between our body and the original might be subtle (the exact source shape). 

What made d get $s0 in the original? Perhaps s1ang raw was NOT a separate local pseudo in the original — maybe the original source computed `u6 = (s1ang & 0xFFF)` differently, or s1ang was loaded in a way that made it global, or the block structure differed.

Hmm, wait. Actually, maybe in the original, the `lh` for s1ang was NOT live across the call as a local pseudo because the original source had `u6 = (*(s16 *)(*(s32*)(arg0+0x20)+0x12)) & 0xFFF;` inline — but then the lh would be after the call... unless the compiler hoisted it. Hmm, no.

OR: the original had s1ang used in a way that made it global. For example, the original might have had the `if (u6 == u5) return 0;` comparison use s1ang differently.

Let me look at the actual RTL of the target (from the pinned build) to see the exact structure and whether there's any clue about the original source shape. The pinned build's RTL should be identical to the target's RTL (since it compiles byte-identically). The pin forces the register, but the RTL structure (insns) is the target's. So I can compare the pinned RTL with my lever-free RTL. The difference is only the pseudo/register assignment, but the *pseudo structure* (how many pseudos, their live ranges) should reveal what the original source did.

In the pinned RTL: r75 (s1ang raw) is local, 2 refs, crosses 1 call. So even in the target RTL, s1ang raw is a block-local pseudo! And local-alloc would have given it $s0... unless the original compilation didn't have the pin. Wait, the pinned build is OUR build with the pin; its RTL differs from the original's only in the hard-reg assignment, but local-alloc's behavior is affected by the pin.

Hmm, so the original compiler also saw a block-local s1ang raw crossing a call. And local-alloc would give it $s0 too... unless the original had something else occupying $s0.

Unless the original's d was allocated $s0 by a *different mechanism*: e.g., d was a block-local? No.

Wait, maybe the original source's `d` was NOT a variable at all — maybe the divisor was `arg1` directly, and gcc kept arg1 in $s0? But arg1 is in $a1, and the call clobbers it. If d = arg1 is used after the call, gcc must save it in a callee-saved reg. The `move $16,$5` is that save. If the source used arg1 directly in the divisions, gcc would need to keep arg1 live across the call → it would allocate it to a callee-saved reg. But then the "move" would be `move $16,$5` at entry and the pseudo would be arg1 (global, since used in multiple blocks) — a global pseudo, not local! And global-alloc would give it $s0 if its priority is high.

Hmm interesting! In our body, `d = arg1` creates a copy; d is global. But if we remove the copy and use arg1 directly:
```
s1ang = ...;
u5 = ...;
d = (s16)arg1;   // the cast still needs a temp?
...
q = iVar4 / arg1;
```
Then arg1 is the divisor, live across the call, used in multiple blocks → global. The cast `d = (s16)d` becomes... we need to cast arg1 for the division: `(s16)arg1` in the div? The target does `sll $16,$16,16; sra $16,$16,16` at insn 57-58, storing back into d ($16). So the divisor is a separate variable d = (s16)arg1. Hmm.

But maybe: `arg1 = (s16)arg1;` — reassigning the parameter! Then the divisor is arg1, and the cast writes arg1. The move `move $16,$5` at entry would be... hmm, if arg1 is assigned to $s0 from entry (because it's live across the call and used later), then the prologue would `move $16,$5` and the cast `sll $16,$16,16; sra $16,$16,16`. That matches! And arg1 is a global pseudo (used in multiple blocks) with high priority.

Wait, but reassigning a parameter: `arg1 = (s16)arg1;` — gcc creates a new pseudo for the cast result? The target has the cast result in the SAME reg $16 as the original d. In the pinned build, d is one pseudo (r74) that is cast in place. In the original, if arg1 were reassigned, the cast result might be a new pseudo but coalesced.

Hmm, but our `d = arg1` at entry is exactly this: d is a copy of arg1, and global-alloc coalesces the copy? Actually in our w0, `move $2,$4` and `move $17,$5` — d=r74 gets $s1 with a `move s1,a1`. So the copy is a real move.

If instead we use arg1 directly (no d variable), then there's no copy at entry; arg1 itself would be allocated to $s0 (if global-alloc picks it), and the prologue would `move $16,$5`? No — arg1 arrives in $a1; to put it in $s0, gcc emits `move $16,$5` at the point where arg1's value is needed in $s0. Global-alloc inserts the copy at the start (or wherever). The target's `move $16,$5` at insn 6 is exactly that.

So: using arg1 directly as the divisor, and casting it, might make the divisor pseudo the *argument* pseudo (global), which global-alloc allocates to $s0.

But wait, the cast `d = (s16)d` creates a new value. If we write `arg1 = (s16)arg1;`, gcc may reuse the same pseudo (in-place cast) or create a new one. The target's `sll $16,$16,16; sra $16,$16,16` is an in-place cast of $16. In our pinned build, the cast is in-place too (r74 → r100 temp → r74? Actually insn 57 sets r100 = r74 << 16, insn 58 sets r74 = r100 >> 16, with REG_EQUAL sign_extend(r74)). So the cast reuses d's pseudo. Good.

So candidate w4: remove `d` entirely, use arg1:
```
s32 func_8012B8E4(s32 arg0, s32 arg1) {
    s32 s1ang;
    s32 u5; s32 u6; s32 iVar4; s32 q; s32 t;
    s1ang = ...;
    u5 = ...;
    arg1 = (s16)arg1;   // do-while for the anchor
    ...
}
```
But the do-while anchor: `do { arg1 = (s16)arg1; } while (0);`.

Hmm, but arg1 is a parameter; assigning to it is fine. Let's test. But careful: the do-while on arg1 might change refs.

Actually wait, will this reproduce the target's `move $16,$5` at entry? If arg1 (the pseudo) is global and assigned $s0, then the copy from $a1 to $s0 happens at entry (because the pseudo's live range starts at entry). Yes.

But hold on: does the parameter pseudo get allocated as a global pseudo? Parameters are pseudos that are live at entry. If a parameter is only used in one block it can be local; here arg1 is used across blocks (div in arms) → global.

Let me test w4. Also consider the cast placement: the target's cast is after the ratan2 call (insn 57), before u6. Our source: `do { arg1 = (s16)arg1; } while (0);` at that position.

Let me write it.

Also, there's a subtlety: with `arg1` reused, the div uses `arg1` (the cast value). Let me write:
```
if (iVar4 >= 0) { q = iVar4 / arg1; if (q == 0) q = 1; }
else { q = iVar4 / arg1; if (q == 0) q = -1; }
```

Let me test.
