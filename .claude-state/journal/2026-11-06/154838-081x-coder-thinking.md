---
ts: 2026-11-06T22:48:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QcrubUC45N33H4EMpkhT
---
w8=49, w9=38. Hmm.

The missing instruction (74 vs 75) is the arg0 copy. That's the key: the mask-in-place kills the arg0 copy. In w0 (u6, do-while cast), we had 75 ins with the arg0 copy.

So the mask-in-place (or rather, globalising s1ang) causes the arg0 copy to disappear. Why? Because the arg0 pseudo (r72) is no longer tied with the pointer; it stays in $a0.

The tie requires the arg0 pseudo to die at the lw. In w0, sched1 ordered the lw after the lh uses. In w6/w7, sched1 ordered the lw first.

Why does sched1 order the lw first when s1ang is global? Hmm, sched1 runs before local-alloc; the RTL it sees has the same insns. The difference: the mask-in-place changes the *dependency* of the s1ang mask insn: in w0, `u6 = s1ang & 0xFFF` (a separate pseudo); in w6, `s1ang = s1ang & 0xFFF` (self). Both depend on the s1ang load. Hmm.

Actually, the scheduler's priority function might differ. Let me look at the sched1 dump for w0 vs w6 to see the insn priorities.

Actually, maybe I can force the schedule with a different trick: make the arg0 pseudo die at the lw by ensuring the lh uses are scheduled before it. The order is determined by sched1's priorities. Hmm.

Alternatively: maybe the arg0 copy can be forced by writing the source so arg0 is used only once after a copy... 

Hmm, let me think about the target's arg0 copy: `move $2,$4` at entry, then `lh $3,14($2)`, `lh $5,6($2)`, `lw $2,32($2)`. So the arg0 pseudo (r72) is copied to $v0 and tied with the pointer.

In w0 (u6, do-while), the same happens. In w6 (mask-in-place), it doesn't.

What if I combine: keep the u6 variable (like w0) AND globalise s1ang via mask-in-place on a *copy*? E.g.:

```
s1ang = *(s16 *)(...);
u5 = ...;
do { d = (s16)d; } while (0);
u6 = s1ang & 0xFFF;
s1ang = s1ang & 0xFFF;   // reassign for globalisation
if (u6 == u5) return 0;
iVar4 = u5 - u6;
...
```
Here the load pseudo is used in block 0 (u6 and the reassign). The reassignment is in block 0 too. s1ang is used later? If the arms use u6, then s1ang (reassigned) is unused → flow deletes it. Hmm.

What if the arms use s1ang (reassigned)? Then the load pseudo is used only in block 0 (u6 + the reassign) → local again.

Hmm.

What if the mask-in-place happens in a LATER block, so the load pseudo is used in block 0 (u6) and block 2 (s1ang = s1ang & 0xFFF)? Then it's global. The extra andi in block 2... cse2 might merge it (same EBB? block 2 is the branch target of block 0's bne — cse follows the branch if the label has a single ref → same EBB → merges). Hmm.

Unless the second use is in a block with multiple preds (the second if). Then the load pseudo is global but there's an extra andi.

OK, let me reconsider the arg0 copy issue. Maybe it's not about the globalisation per se but about the *mask-in-place* changing the RTL such that the pointer load gets a REG_EQUIV and the schedule changes. Let me look at the w6 lreg insns 16-25 vs w0.

In w0: insn 16 = lw pointer with REG_DEAD r72 (arg0 dies).
In w6: insn 16 = lw pointer with REG_EQUIV and r72 NOT dead (r72 used later).

Let me look at the exact RTL. w6 line ~155: `(insn 16 59 20 (set (reg:SI 80) (mem:SI (plus (reg/v:SI 72) ...)))` with REG_EQUIV. And the REG_DEAD r72 is at insn 184.

So in w6, sched1 ordered: lw (16), then lh 14 (59?), lh 6... wait, the insn numbers: 59 is the lh 14? Let me look at the order.

Actually, the schedule difference: in w0, the lh uses come before the lw; in w6, the lw comes first.

Why would sched1 differ? The scheduler's insn priorities depend on the data dependencies and the "priority" (critical path length to the end). The mask-in-place changes the dependency graph slightly: in w0, the s1ang load feeds u6 (and); in w6, it feeds the self-and. Both similar.

Hmm, maybe the difference is the REG_EQUIV: cse created a REG_EQUIV for the pointer load in w6 because the source `*(s32 *)(arg0 + 0x20)` is used once... Hmm.

Actually wait — maybe the difference is in the ORDER OF STATEMENTS. In w0 and w6, the source order is the same: d=arg1; s1ang=load; u5=call...; cast; u6/mask.

Hmm, let me look at the sched1 dump for both to understand. Let me check the sched dump format.
