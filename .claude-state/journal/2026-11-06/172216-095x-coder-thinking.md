---
ts: 2026-11-07T00:22:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bRtqskQergHv5uOVtYbV
---
Several still 2 (n04, n06, n07). No improvement below 2.

The residual is the reorg delay-slot duplication. This is likely a `reorg-*` wall.

Let me try a couple more specific ideas:
- What if I put the max comparison in a separate scope / add a `do{}while(0)` around the abs block? C0535 says do-while splits cse1 EBB. Hmm, that could change the delay-slot fill.

Actually, the issue is reorg (after sched2). Let me think about what makes reorg not duplicate the slt.

reorg's delay-slot filling: for a branch, it looks at the target insn and the fall-through insn. It fills the delay slot from the target if the target insn is "safe" (not dependent on the branch). Here the target is the slt; it's safe, so it's duplicated/moved.

In the target, the branch target is the asm insn (which can't go in a delay slot) → nop.

Lever-free: I need an insn at the branch target that can't be in a delay slot. Only an asm or a jump can't. Hmm.

Alternatively, make the slt dependent on the branch somehow. 

Hmm, what if the max is a conditional that jumps? `if (iVar5 < iVar4) iVar5 = iVar4;` compiles to slt+beqz. The branch target of the bgez is the slt. 

What if I reorder so that the bgez's target is the `beqz` instead of the slt? E.g., if the slt could be sunk into the negu path... 

Hmm, what if the abs is written as:
```
if (iVar4 < 0) iVar4 = -iVar4;
```
and then the max. What if instead:
```
iVar4 = iVar4 < 0 ? -iVar4 : iVar4;
```
That's n02 → 118 insns (an extra move). No.

OK, this is a reorg-level wall. Given the time, let me stop here.

Actually, hold on — maybe I should try the `do{}while(0)` trick around the abs/max to split the block. Let me try:
```
if (iVar4 < 0) { iVar4 = -iVar4; }
do {
    if (iVar5 < iVar4) iVar5 = iVar4;
} while (0);
```
and with the // !FAKE: do-while comment. The brief allows do-while with the comment.

Let me test a couple.

Also: what about wrapping the abs in do-while?

Let me try 4 variants.
