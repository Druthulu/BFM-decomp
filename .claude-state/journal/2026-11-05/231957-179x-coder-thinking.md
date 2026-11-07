---
ts: 2026-11-06T06:19:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l7DvVN8IZFrL1EsLmEjq
---
The RTL: insn 137 loads `mem[reg72 + 256]` where reg72 = the parameter (in $16). So the base IS reg72 (the parameter in $16).

But the final asm shows `lh v0,256(a0)`. So a later pass (regmove or local-alloc) changed it.

Hmm, maybe regmove: it sees `move a0,s0` (insn 125: a0 = reg72) and rewrites uses of reg72 in the same block to a0 to eliminate the move. That's regmove's "copy propagation".

In the target, reg72 is a hard reg ($16), so regmove can't rewrite it.

To prevent regmove from rewriting, the copy `a0 = reg72` must not be eliminable... or the use must be in a different block.

Hmm, insn 125 (a0 = reg72) is in the same block as insn 137 (the load). regmove sees both and rewrites the load's base to a0.

Wait, but then the `move a0,s0` would be eliminated (dead). But the asm still has `move a0,s0` at 292c — because a0 is also used for the call args (the sw at 2950). So the move stays, and the load got rewritten to a0 as well.

To prevent the rewrite, the load could be in a different basic block. The last block is one block. Hmm.

What if I split the block with a do-while(0) between the copy and the load? u1 wrapped the load in a do-while → 66 ins, score 6 (an extra instruction appeared?). Hmm.

What if I put the `pa0 = a0` copy AFTER the load (so the copy is later)? u2 did that → 1. Maybe sched1 moved the copy earlier anyway (scheduling doesn't move it across the load? it can).

Hmm.

What if the copy is `pa0 = a0` but the load's base is a *different* pseudo that regmove can't touch (e.g., a hard reg)? We can't use hard regs.

Hmm.

What if the last block's pointer access uses a *different* expression that regmove can't rewrite, like `(s32)a0 + 0`? folds.

Hmm. What about making the call arg `a0` not come from reg72 but from a *different* value? E.g., if the call's argument were `pa0` (a variable) and the load's base were the parameter, regmove would still see a0 = reg72.

What if the call's argument is passed as `(void *)(s32)a0` but there are two different copies... 

Hmm, what if the last block has NO call-arg copy from reg72? The call `func_8012AD50((void *)pa0)` requires a0 = pa0. If pa0 were in a different register (not a0), then a0 = pa0 would be a move from that reg. Then the load's base (reg72) wouldn't be copied to a0... but the call still needs a0 = pa0.

Hmm, in the target, pa0 is in $4 (a0) and the move is `move a0,s0` (from s0). The load uses s0.

So the difference: in the target, regmove doesn't rewrite the hard reg.

For a lever-free body: can I make regmove not rewrite? regmove's `copy_src_to_dest` rewrites uses of the source in the same block if it's profitable and the register isn't needed. Hmm.

What if the load's base pseudo is used *after* the copy in a way that keeps it alive... it is (reg72 is used across the function).

Hmm, regmove might only rewrite if the source (reg72) dies after the block? No, reg72 is live across the whole function.

Actually, regmove's optimization: it tries to remove the copy `a0 = reg72` by making reg72's uses in the block use a0 instead, and then the copy becomes dead. But here the copy is needed for the call (a0's value at the call). Hmm.

Wait, maybe it's not regmove. Let me check the s5 .s vs .lreg — the register assignment in lreg shows reg72 in $16. The final asm uses a0 for the load. So between lreg and the final asm, something changed. That's reload/regmove.

Hmm, actually — maybe the load `lh v0,256(a0)` is not using a0 as the base of reg72 but as a *reload* of something? No.

Let me look at the s5 .s (the cc1 asm output) around the load. Hmm, that's the same.

OK, let me try a different approach: what if the load's base is a *fresh pseudo* that's not the parameter, allocated to $16? For example:

```c
{
    s32 v0, v1;
    s32 pa0;
    s32 *p = (s32 *)a0;      // hmm
```

Hmm.

Actually — what if I put the unk100 access in the *same* expression as the pointer arithmetic, so the compiler uses the same base? Hmm.

Let me try: `v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4) + (s32)&D_80184CCC[0];` — inline the v1. Hmm.

Or: what if the order is: compute the pointer arithmetic FIRST (using a0), then the unk100 load from s0? The target has: move a0,s0; lui v1; addiu v1; lh v0,256(s0). So v1 (D_80184CCC) is loaded before the unk100 load.

Hmm.

Let me try making the unk100 load happen *before* the v1 symbol load:
```c
v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4);
v1 = (s32)&D_80184CCC[0];
v0 += v1;
```
That might change the scheduling: the load would be first in the block, before the a0 copy? The a0 copy (pa0 = a0) is first in the source.

Hmm.

Let me try a few variants:
- x1: `u = ((Unkstruct_800B5CB8 *)(s32)a0)->unk100;` as the FIRST statement of the block (before pa0 = a0).
- x2: put the pa0 copy at the very end (just before the call).

Let me test.
