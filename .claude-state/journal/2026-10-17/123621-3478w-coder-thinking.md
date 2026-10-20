---
ts: 2026-10-17T18:36:21.130Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac81395c556dc97c0
model: claude-opus-5-5[1m]
effort: medium
turnId: 2749fb46-32ea-40ac-942d-d9e5fb5596d6
---
I'm puzzling over why the first block's swap still happened despite the lim dependency — maybe lim is a constant address whose set instruction got deleted or moved by cse, which would explain the discrepancy in the second block where t got a1 instead of v1.

The tie between t and puVar2 only occurs in local-alloc when t dies at the copy and puVar2 is "born" there, but since puVar2 is a global pseudo (handled by greg, not local-alloc), that tie shouldn't normally apply — unless combine is merging the load and copy instructions across the three-instruction window, folding them into a direct load into puVar2 once t dies. That would explain why block one shows the merged form while block two, with an intervening store, doesn't get the same treatment.

In the second block, combine likely can't merge the load and copy because a memory store sits between them — combine won't move a memory load past a store. So I need to figure out what intervening store exists in block one that would normally block this too, since block one also ends up storing through puVar4 after computing it from the loaded value. The target's addiu for puVar4 reads directly from the already-allocated register rather than through t, which doesn't match a straightforward combine merge, so maybe the real blocker is something else, like a store into param_1 structure fields occurring between the load and copy in one block but not the other.

Looking more carefully, the real distinguishing factor could be which register combine picks for the intermediate temp, or whether combine's rules about intervening stores and reused destinations actually explain why one block merges and the other doesn't.

I'm also considering statement ordering constraints: stores occurring before the calls in block 1 must stay in source order relative to those calls, so I need to trace which stores happen in that block after the func_80017E68 call.

Looking at the conditional store into offset 0xcc, since it reuses the temp `t`, that temp gets used twice — meaning the register copy to `puVar2` would survive like the c4 case, but then CSE likely canonicalizes later uses of `t` to `puVar2` via `make_regs_eqv`, since `puVar2` outlives the block while `t` doesn't.

So I'm checking whether combine could still merge this across the join point. Combine doesn't operate across block boundaries or code labels, so if `t`'s later use sits in a different extended basic block, that merge path should fail — which is exactly the gap I need.

Now I'm comparing the instruction order against the target: a load into v0, then lui/addiu building an address into s5, then moving v0 into s1. I want to figure out where `lim` gets set in my version to see if it lines up with that same address pattern.

I'm also considering whether combine avoids merging the copy because the destination is a user variable, which might explain why GCC keeps these as separate instructions rather than folding them together.

With time running short, I want to try a couple more block combinations—block 1's pointer increment pattern paired with block 2's store, and checking why `t` ends up assigned different registers (a1 vs v1) across blocks, possibly due to local-alloc ordering quirks.
