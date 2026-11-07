---
ts: 2026-11-06T13:24:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_27VIz9s3HBLjcKcrwkWl
---
Not tied: extra insns (147 vs 144). So local-alloc didn't coalesce.

Let me reconsider. Maybe the mechanism to force early scheduling is a *dependency* the other way: make the s0 chain's first insn depend on the addiu. If `s0 &= 0x1F` depended on nn... e.g., compute `t = (t & 0x1F) - 0x50;` — no.

What if we reorder the source so `nn = (s32)buf;` comes AFTER the s0 chain but the call uses nn — v09 scored 2, same. So sched1's placement is source-independent.

Hmm, what about giving the addiu a use immediately after it that's cheap: e.g., `nn = (s32)buf; t = t;` no.

Think about what sched1 priority means: it schedules insns with the highest "priority" first, and emits them in the order scheduled (backward list scheduling: the highest priority is emitted last?). In Haifa sched, it's a forward list scheduler: it repeatedly picks the highest-priority ready insn and emits it. So the low-priority addiu is picked late → emitted late.

To make it emitted early, its priority must be high. Priority = max over successors of (priority + latency) or based on the "rank" (the critical path length to the end of the block). An insn with a long dependency chain after it gets high priority. The addiu has a successor: the jal (the call uses $5). The jal is a CALL_INSN — probably the end of the block; the call's priority is high? Hmm.

Alternatively, the target's order might be achieved by scheduling the *s0 chain* differently: if the s0 chain insns are scheduled late (low priority), then addiu comes first. In mine, the s0 chain is scheduled before the addiu. The chain's first insn `andi s0,s0,0x1f` depends on the move s0,v0 (from rand). Hmm.

What raises the s0 chain's priority? Its results are used by the store d[2]=s0 and the call? The call uses aa, nn only.

Hmm, wait. In the target, the s0 chain comes after the addius. In mine too (addiu a0 at 37e8, then andi). So only the a1 addiu differs.

What if we introduce a *dependence* from the addiu to the s0 chain by making nn's value participate in a dead computation that gets deleted? E.g.:
```
nn = (s32)buf;
if (nn == 0) { }   // no code
```
No dependence.

What about using the pinned nn in an expression that's folded: `nn = (s32)buf; s0 = s0 & (0x1F | (nn & 0));` — nn & 0 folds to 0 at tree level, no dependence.

What if we write `s0 &= 0x1F;` as `s0 &= (0x1F + (nn - nn));`? At tree level, nn-nn isn't folded (nn is a variable, but gcc may fold x-x to 0? fold does fold x-x to 0 for non-volatile? It does "A - A -> 0" maybe). If it folds, no dep. If not folded, it emits subu (extra insn).

Hmm.

Alternative: maybe the correct lever is not about the addiu but about the *call*. In the target, the jal is preceded by the addiu a1. What if in mine the jal itself was moved? No.

Let me look at the RTL to understand: maybe use tools/cc1_dumps_tu.sh to dump the sched1 pass for both bodies and see. That's heavy but gives the answer. Disk: dumps go under my item dir, delete after.

Actually, maybe simpler: check whether sched1 or sched2 did it by looking at the difference between sched1 output and final. If the barrier's effect is in sched1 (the asm creates deps at sched1), removing it changes sched1. The MIPS also has sched2 (post-reload). Both could sink the addiu.

Let me think about what else creates a full register-clobber dependency at sched1 with zero code: the ASM_OPERANDS with MEM_VOLATILE. A real-C alternative... hmm.

What about the `d[2] = s0` store: in the target it's in the jal's delay slot. Fine.

New idea: make the addiu a1 *not sinkable* because it's inside a block that ends right after it. If `nn = (s32)buf;` were the last statement of a basic block, the addiu can't move past the block end. A basic block ends at a conditional jump or a label. What creates a basic block boundary in the middle with zero code? A CODE_LABEL that is the target of a jump! But a label alone (fallthrough) doesn't split the block.

Hmm, what about putting the s0 chain in an `if` whose condition is always true but not foldable, e.g. `if (nn != 0)`? nn is the stack address, nonzero but gcc doesn't know... Actually gcc knows `buf`'s address is nonzero? It might. `if (buf != 0)` → the array address is nonzero, gcc may fold it (a local array address is never null). Hmm, but `if (nn != 0)` where nn is s32 — gcc could know nn = (s32)buf, and &buf != 0, so fold. If not folded, we get a branch + label = extra code (bnez + nop).

Not good.

OK, let me use the dumps to see what actually happens. tools/cc1_dumps_tu.sh — let me check its usage.
